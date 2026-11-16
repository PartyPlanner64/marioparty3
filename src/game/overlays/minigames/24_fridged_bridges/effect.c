#include "common.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "fridged_bridges.h"

#define CLAMP_S16(x)            \
    if ((x) > 0x7FFF) {         \
        (x) = 0x7FFF;           \
    } else if ((x) < -0x8000) { \
        (x) = -0x8000;          \
    }

// Small object that keeps a player's camera center glued to that player's object.
typedef struct FridgedBridgesCameraTarget {
    /* 0x00 */ u16 playerId;
    /* 0x04 */ omObjData *playerObj;
} FridgedBridgesCameraTarget; // sizeof 0x8

extern s16 m236_cameraBitTbl[4];
extern s16 m236_effMdlTbl[1][12];
extern u16 m236_effUseTbl[1][12];
extern omObjData *m236_effObj;
extern FridgedBridgesCamCollWork m236_camCollWorkTbl[4];

extern f32 CFanLenM[];
extern CollisionGrid *MapCollData;
extern s32 Hu3DCurAttr;
extern HuCamera *Hu3DCurCamera;
extern s16 Hu3DCamMtxNo;
extern Mtx *MTXBuf;
extern s16 MTXBufNum;
extern f32 CFanOfsM[];

void m236_CameraTargetObjMain(omObjData *arg0);
void m236_EffObjMain(omObjData *arg0);
void m236_ModelMtxGet(HmfModel *model, HuMtx4F mtx);
void m236_CullBatchAdd(u16 index, FridgedBridgesCamCollWork *work, HmfData *hmf, u16 object);

// Effect model file, object function and lifetime for each effect type. These
// are separate arrays of one entry each.
s32 m236_effMdlFileTbl[1] = { 0x0045000C };
omObjFunc m236_effFuncTbl[1] = { m236_EffObjMain };
s32 m236_effTimeTbl[1] = { 35 };

void m236_OvlReturn(void) {
    omOvlReturnEx(1);
}

void m236_CameraTargetCreate(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR(arg0, FridgedBridgesPlayer);
    omObjData *obj = omAddObj(0x32, 0, 0, -1, m236_CameraTargetObjMain);
    FridgedBridgesCameraTarget *target;

    player->unk_2C = obj;
    target = HuMemAllocTag(sizeof(FridgedBridgesCameraTarget), TAG_OVERLAY);
    obj->data = target;
    target->playerId = player->playerId;
    target->playerObj = arg0;
    obj->work[0] = 0;
}

void m236_CameraTargetObjMain(omObjData *arg0) {
    FridgedBridgesCameraTarget *target = arg0->data;

    if (arg0->work[0] != 0) {
        CenterM[target->playerId].x = target->playerObj->trans.x;
        CenterM[target->playerId].z = target->playerObj->trans.z;
    }
}

// Preloads the pool of effect models used by m236_EffCreate.
void m236_EffInit(void) {
    s32 i;
    s32 j;

    m236_effObj = omAddObj(60, 0, 0, -1, NULL);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 12; j++) {
            m236_effMdlTbl[i][j] = Hu3DModelRead(m236_effMdlFileTbl[i], 0x68D);
            m236_effUseTbl[i][j] = 0;
        }
    }
}

// Spawns an effect of the given type from the model pool, in the given player's camera.
omObjData *m236_EffCreate(u16 type, u16 playerId, f32 x, f32 y, f32 z) {
    omObjData *obj;
    s16 model;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (m236_effUseTbl[type][i] == 0) {
            break;
        }
    }
    if (i == 12) {
        return NULL;
    }
    model = m236_effMdlTbl[type][i];
    m236_effUseTbl[type][i] = 1;
    obj = omAddObj(60, 1, 0, -1, m236_effFuncTbl[type]);
    obj->model[0] = model;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, 0);
    Hu3DModelCameraSet(obj->model[0], m236_cameraBitTbl[playerId]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    omSetTra(obj, x, y, z);
    omSetSca(obj, 2.0f, 1.0f, 2.0f);
    obj->work[0] = m236_effTimeTbl[type];
    obj->work[1] = i;
    return obj;
}

void m236_EffObjMain(omObjData *arg0) {
    if (--arg0->work[0] == 0) {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m236_effUseTbl[0][arg0->work[1]] = 0;
        omDelObj(arg0);
    }
}

// Updates each player's camera from CenterM/CRotM/CZoomM.
void m236_CameraOutView(omObjData *arg0) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rotX;
    f32 rotY;
    u8 i;

    for (i = 0; i < arg0->work[0]; i++) {
        rotX = CRotM[i].x;
        rotY = CRotM[i].y;
        pos.x = sindf(rotY) * cosdf(rotX) * CZoomM[i] + CenterM[i].x;
        pos.y = -sindf(rotX) * CZoomM[i] + CenterM[i].y;
        pos.z = cosdf(rotY) * cosdf(rotX) * CZoomM[i] + CenterM[i].z;
        at.x = CenterM[i].x;
        at.y = CenterM[i].y;
        at.z = CenterM[i].z;
        up.x = sindf(rotY) * sindf(rotX);
        up.y = cosdf(rotX);
        up.z = cosdf(rotY) * sindf(rotX);
        m236_camCollWorkTbl[i].fan.x = pos.x;
        m236_camCollWorkTbl[i].fan.z = pos.z;
        m236_camCollWorkTbl[i].fan.angle = CRotM[i].y;
        m236_camCollWorkTbl[i].fan.shape.spread = gCameraList[i].fov;
        m236_camCollWorkTbl[i].fan.shape.length = CFanLenM[i];
        m236_camCollWorkTbl[i].fan.shape.offset = CFanOfsM[i];
        Hu3DCameraPosSetV(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
    }
}

// Copy of Hu3DModelMtxGet.
void m236_ModelMtxGet(HmfModel *model, HuMtx4F mtx) {
    HmfSkeletonNode *node;
    HuMtx4F temp;

    Hu3DCurAttr = model->attr;
    guMtxL2F(mtx, &Hu3DCurCamera->mtxs[Hu3DCamMtxNo].lookAtMtx);
    if (model->pos.x != 0.0f || model->pos.y != 0.0f || model->pos.z != 0.0f) {
        mtxTransCat(mtx, model->pos.x, model->pos.y, model->pos.z);
    }
    if (model->rot.x != 0.0f || model->rot.y != 0.0f || model->rot.z != 0.0f) {
        mtxRotCat(mtx, model->rot.x, model->rot.y, model->rot.z);
    }
    if (model->scale.x != 1.0f || model->scale.y != 1.0f || model->scale.z != 1.0f) {
        mtxScaleCat(mtx, model->scale.x, model->scale.y, model->scale.z);
    }
    mtxCat(model->mtx, mtx, mtx);
    node = model->hmf->unk68;
    guMtxIdentF(temp);
    if (node->unk08.x == 0.0f || node->unk08.y == 0.0f || node->unk08.z == 0.0f) {
        mtxTransCat(temp, node->unk08.x, node->unk08.y, node->unk08.z);
    }
    if (node->unk14.x == 0.0f || node->unk14.y == 0.0f || node->unk14.z == 0.0f) {
        mtxRotCat(temp, node->unk14.x, node->unk14.y, node->unk14.z);
    }
    if (node->scale.x != 1.0f || node->scale.y != 1.0f || node->scale.z != 1.0f) {
        mtxScaleCat(temp, node->scale.x, node->scale.y, node->scale.z);
    }
    guMtxCatF(temp, mtx, mtx);
    guMtxF2L(mtx, &MTXBuf[MTXBufNum]);
}

// Variant of MapCullFan that batches the visible objects of each of the
// three object layers into a single display list per layer.
void m236_MapCullFanBatch(FridgedBridgesCamCollWork *work, HmfModel *model) {
    Hu3DPoint tri[3];
    HuMtx4F mtx;
    HuMtx4F ident;
    CollisionFanShape *shape;
    CollisionGrid *grid;
    s16 gridIndex;
    s32 value;
    s32 x;
    s32 z;
    s32 cell;
    s32 object;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;
    f32 cellWidth;
    f32 cellDepth;

    model->hmf->unkD0 = model->unkB4;
    shape = &work->fan.shape;
    if (model->unkB4 != NULL) {
        Hu3DLLightSet(model->unkB4);
    }
    gridIndex = model->unk10;
    m236_ModelMtxGet(model, mtx);
    guMtxIdentF(ident);
    /* Dead stores (only the sindf/cosdf calls survive), as in MapCullFan. */
    x0 = MapCollData[gridIndex].width * MapCollData[gridIndex].cellWidth / 2.0f + work->fan.x +
         sindf(work->fan.angle) * shape->offset;
    z0 = MapCollData[gridIndex].depth * MapCollData[gridIndex].cellDepth / 2.0f + work->fan.z +
         cosdf(work->fan.angle) * shape->offset;
    tri[0].y = tri[1].y = tri[2].y = 0;
    value = MapCollData[gridIndex].width * MapCollData[gridIndex].cellWidth / 2.0f + work->fan.x +
            sindf(work->fan.angle) * shape->offset;
    CLAMP_S16(value);
    tri[0].x = value;
    value = MapCollData[gridIndex].depth * MapCollData[gridIndex].cellDepth / 2.0f + work->fan.z +
            cosdf(work->fan.angle) * shape->offset;
    CLAMP_S16(value);
    tri[0].z = value;
    value = tri[0].x - sindf(shape->spread / 2.0f + work->fan.angle) * shape->length;
    CLAMP_S16(value);
    tri[1].x = value;
    value = tri[0].z - cosdf(shape->spread / 2.0f + work->fan.angle) * shape->length;
    CLAMP_S16(value);
    tri[1].z = value;
    value = tri[0].x - sindf(work->fan.angle - shape->spread / 2.0f) * shape->length;
    CLAMP_S16(value);
    tri[2].x = value;
    value = tri[0].z - cosdf(work->fan.angle - shape->spread / 2.0f) * shape->length;
    CLAMP_S16(value);
    tri[2].z = value;
    grid = &MapCollData[gridIndex];
    cellWidth = grid->cellWidth;
    cellDepth = grid->cellDepth;
    work->dlCount[0] = work->dlCount[1] = work->dlCount[2] = 0;
    for (z = 0; z < MapCollData[gridIndex].depth; z++) {
        z0 = z * cellDepth + model->pos.z;
        z1 = z0 + cellDepth;
        for (x = 0; x < grid->width; x++) {
            cell = z * grid->width + x;
            x0 = x * cellWidth + model->pos.x;
            x1 = x0 + cellWidth;
            object = grid->unk_14[cell];
            if (object != -1) {
                if (MapIflnnerTriangle(x0, z0, tri) == TRUE) {
                    m236_CullBatchAdd(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    m236_CullBatchAdd(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    m236_CullBatchAdd(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    m236_CullBatchAdd(0, work, model->hmf, object);
                }
            }
            object = grid->unk_18[cell];
            if (object != -1) {
                if (MapIflnnerTriangle(x0, z0, tri) == TRUE) {
                    m236_CullBatchAdd(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    m236_CullBatchAdd(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    m236_CullBatchAdd(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    m236_CullBatchAdd(1, work, model->hmf, object);
                }
            }
            object = grid->unk_1C[cell];
            if (object != -1) {
                if (MapIflnnerTriangle(x0, z0, tri) == TRUE) {
                    m236_CullBatchAdd(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    m236_CullBatchAdd(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    m236_CullBatchAdd(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    m236_CullBatchAdd(2, work, model->hmf, object);
                }
            }
        }
    }
    // The column counter is reused as the layer index here.
    for (x = 0; x < 3; x++) {
        if (work->dlCount[x] != 0) {
            gSPEndDisplayList(&work->gfx[x][work->dlCount[x]]);
            Hu3DDrawEntryAdd(&work->hmf[x], 0, &MTXBuf[MTXBufNum], ident);
        }
    }
    MTXBufNum++;
}

// Adds an object's display list to the batch for the given layer.
void m236_CullBatchAdd(u16 index, FridgedBridgesCamCollWork *work, HmfData *hmf, u16 object) {
    u16 *count = &work->dlCount[index];

    if (*count == 0) {
        work->hmf[index] = *hmf;
        work->hmf[index].unk3C->unk00[0] = work->gfx[index];
        work->hmf[index].unk10 = 1;
    }
    if (work->dlCount[index] == 0) {
        gSPDisplayList(&work->gfx[index][work->dlCount[index]], *(hmf->unk3C->unk00 + object));
        work->dlCount[index]++;
    }
}
