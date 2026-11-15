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

extern s16 D_8010CF48_fridged_bridges[4];
extern s16 D_8010DA30_fridged_bridges[1][12];
extern u16 D_8010DA48_fridged_bridges[1][12];
extern omObjData *D_8010DA88_fridged_bridges;
extern FridgedBridgesCamCollWork D_8010DA90_fridged_bridges[4];

extern f32 CFanLenM[];
extern CollisionGrid *MapCollData;
extern s32 Hu3DCurAttr;
extern HuCamera *Hu3DCurCamera;
extern s16 Hu3DCamMtxNo;
extern Mtx *MTXBuf;
extern s16 MTXBufNum;
extern f32 CFanOfsM[];

void func_8010BE88_fridged_bridges(omObjData *arg0);
void func_8010C178_fridged_bridges(omObjData *arg0);
void func_8010C46C_fridged_bridges(HmfModel *model, HuMtx4F mtx);
void func_8010CDE4_fridged_bridges(u16 index, FridgedBridgesCamCollWork *work, HmfData *hmf, u16 object);

// Effect model file, object function and lifetime for each effect type. These
// are separate arrays of one entry each.
s32 D_8010D240_fridged_bridges[1] = { 0x0045000C };
omObjFunc D_8010D244_fridged_bridges[1] = { func_8010C178_fridged_bridges };
s32 D_8010D248_fridged_bridges[1] = { 35 };

void func_8010BDF0_fridged_bridges(void) {
    omOvlReturnEx(1);
}

void func_8010BE0C_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR(arg0, FridgedBridgesPlayer);
    omObjData *obj = omAddObj(0x32, 0, 0, -1, func_8010BE88_fridged_bridges);
    FridgedBridgesCameraTarget *target;

    player->unk_2C = obj;
    target = HuMemAllocTag(sizeof(FridgedBridgesCameraTarget), TAG_OVERLAY);
    obj->data = target;
    target->playerId = player->playerId;
    target->playerObj = arg0;
    obj->work[0] = 0;
}

void func_8010BE88_fridged_bridges(omObjData *arg0) {
    FridgedBridgesCameraTarget *target = arg0->data;

    if (arg0->work[0] != 0) {
        CenterM[target->playerId].x = target->playerObj->trans.x;
        CenterM[target->playerId].z = target->playerObj->trans.z;
    }
}

// Preloads the pool of effect models used by func_8010BFD0.
void func_8010BEE8_fridged_bridges(void) {
    s32 i;
    s32 j;

    D_8010DA88_fridged_bridges = omAddObj(60, 0, 0, -1, NULL);
    for (i = 0; i < 1; i++) {
        for (j = 0; j < 12; j++) {
            D_8010DA30_fridged_bridges[i][j] = Hu3DModelRead(D_8010D240_fridged_bridges[i], 0x68D);
            D_8010DA48_fridged_bridges[i][j] = 0;
        }
    }
}

// Spawns an effect of the given type from the model pool, in the given player's camera.
omObjData *func_8010BFD0_fridged_bridges(u16 type, u16 playerId, f32 x, f32 y, f32 z) {
    omObjData *obj;
    s16 model;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (D_8010DA48_fridged_bridges[type][i] == 0) {
            break;
        }
    }
    if (i == 12) {
        return NULL;
    }
    model = D_8010DA30_fridged_bridges[type][i];
    D_8010DA48_fridged_bridges[type][i] = 1;
    obj = omAddObj(60, 1, 0, -1, D_8010D244_fridged_bridges[type]);
    obj->model[0] = model;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, 0);
    Hu3DModelCameraSet(obj->model[0], D_8010CF48_fridged_bridges[playerId]);
    Hu3DMotionTimeSet(obj->model[0], 0.0f);
    omSetTra(obj, x, y, z);
    omSetSca(obj, 2.0f, 1.0f, 2.0f);
    obj->work[0] = D_8010D248_fridged_bridges[type];
    obj->work[1] = i;
    return obj;
}

void func_8010C178_fridged_bridges(omObjData *arg0) {
    if (--arg0->work[0] == 0) {
        Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_8010DA48_fridged_bridges[0][arg0->work[1]] = 0;
        omDelObj(arg0);
    }
}

// Updates each player's camera from CenterM/CRotM/CZoomM.
void func_8010C1D8_fridged_bridges(omObjData *arg0) {
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
        D_8010DA90_fridged_bridges[i].fan.x = pos.x;
        D_8010DA90_fridged_bridges[i].fan.z = pos.z;
        D_8010DA90_fridged_bridges[i].fan.angle = CRotM[i].y;
        D_8010DA90_fridged_bridges[i].fan.shape.spread = gCameraList[i].fov;
        D_8010DA90_fridged_bridges[i].fan.shape.length = CFanLenM[i];
        D_8010DA90_fridged_bridges[i].fan.shape.offset = CFanOfsM[i];
        Hu3DCameraPosSetV(i, &pos, &at, &up);
        Hu3DCamUpdateMtx(i);
    }
}

// Copy of Hu3DModelMtxGet.
void func_8010C46C_fridged_bridges(HmfModel *model, HuMtx4F mtx) {
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
void func_8010C738_fridged_bridges(FridgedBridgesCamCollWork *work, HmfModel *model) {
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
    func_8010C46C_fridged_bridges(model, mtx);
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
                    func_8010CDE4_fridged_bridges(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(0, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(0, work, model->hmf, object);
                }
            }
            object = grid->unk_18[cell];
            if (object != -1) {
                if (MapIflnnerTriangle(x0, z0, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(1, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(1, work, model->hmf, object);
                }
            }
            object = grid->unk_1C[cell];
            if (object != -1) {
                if (MapIflnnerTriangle(x0, z0, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z0, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x0, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(2, work, model->hmf, object);
                } else if (MapIflnnerTriangle(x1, z1, tri) == TRUE) {
                    func_8010CDE4_fridged_bridges(2, work, model->hmf, object);
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
void func_8010CDE4_fridged_bridges(u16 index, FridgedBridgesCamCollWork *work, HmfData *hmf, u16 object) {
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
