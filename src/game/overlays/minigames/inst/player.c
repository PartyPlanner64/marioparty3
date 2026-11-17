#include "common.h"
#include "inst.h"
#include "game/hmfmath.h"

extern u8 mgPlayerTeam[];
extern s8 inst_playerOrderTbl[4];
extern s8 inst_mgType;
extern u8 inst_plateColorTbl[4];
extern s8 inst_itemPrizeTbl[5];
extern const char *inst_chrNodeNameTbl[8];
extern s32 inst_plateFileTbl[4];
extern const char *inst_plateHookNameTbl[4];
extern s16 inst_chrMdlTbl[4];
extern s32 inst_playerCloseF;
extern s32 inst_playerOpenCnt;
extern s32 inst_playerCloseCnt;
extern f32 inst_cameraTilt;
extern omObjData *inst_playerObj;
extern InstModelHooks *inst_hookTbl[][2];
extern InstObjectState inst_boxWork;
extern HuMtx4F inst_playerMtx;
extern s8 inst_introSkipF;
extern s8 inst_openF;
extern s8 inst_openDoneF;
extern void (*inst_playerFunc)(omObjData *);

static const s32 inst_chrMdlFileTbl[] = {
    0x17002E, 0x17002F, 0x170030, 0x170031, 0x170032, 0x170033, 0x170034, 0x170035,
};
static const s32 inst_itemMdlFileTbl[] = {
    0x170038, 0x170039, 0x17003A, 0x17003B, 0x17003C, 0x17003D, 0x17003E, 0x17003F,
    0x170040, 0x170041, 0x170042, 0x170045, 0x170044, 0x170043, 0x170046,
};

const char inst_chrNode13Name[] = "y002_13-grid1";
const char inst_chrNode12Name[] = "y002_12-grid1";
const char inst_chrNode11Name[] = "y002_11-grid1";
const char inst_chrNode10Name[] = "y002_10-grid1";
const char inst_chrNode09Name[] = "y002_09-grid1";
const char inst_chrNode08Name[] = "y002_08-grid1";
const char inst_chrNode07Name[] = "y002_07-grid1";
const char inst_chrNode06Name[] = "y002_06-grid1";
const char inst_plateHookLastName[] = "hook_last";
const char inst_plateHookMidoriName[] = "hook_midori";
const char inst_plateHookAkaName[] = "hook_aka";
const char inst_plateHookAoName[] = "hook_ao";

s32 inst_BoxMotionEndCheck(void);
void inst_PlateColorSet(void);
void inst_BoxMotionRevStart(void);
void inst_PlayerOpenWait(omObjData *object);
void inst_PlayerOpenNow(omObjData *);
void inst_PlayerBoxFollow(omObjData *);
void inst_PlayerOpenStart(omObjData *); /* extern */
void inst_PlayerOpen(omObjData *);
void inst_PlayerIdle(omObjData *object);
void inst_PlayerClose(omObjData *);

void inst_PlayerMain(void) {
    omObjData *object;
    InstModelHooks *models;
    s32 i;
    s32 player;

    object = omAddObj(21, 30, 1, -1, NULL);
    inst_playerObj = object;
    inst_PlateColorSet();
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        object->model[i + 1] = Hu3DModelRead3(inst_plateFileTbl[inst_plateColorTbl[i]], 0x1AB9);
    }
    object->model[5] = Hu3DModelRead3(0x170036, 0x16B9);
    for (i = 1; i < models->count; i++) {
        object->model[i + 5] = Hu3DModelLink(object->model[5]);
    }
    for (i = 0; i < models->count; i++) {
        player = inst_playerOrderTbl[i];
        inst_chrMdlTbl[i] = Hu3DModelRead3(inst_chrMdlFileTbl[GwPlayer[player].chr], 0x1AB9);
        Hu3DModelObjCopy(inst_chrMdlTbl[i], inst_chrNodeNameTbl[GwPlayer[player].chr],
                           object->model[i + 1], inst_plateHookNameTbl[inst_plateColorTbl[i]]);
        Hu3DModelAttrSet(inst_chrMdlTbl[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(object->model[i + 1], 0);
        Hu3DMotionAttrSet(object->model[i + 1], 2, 0);
    }
    object->trans.x = 0;
    object->trans.y = 0;
    object->trans.z = 0;
    for (i = 0; i < models->count; i++) {
        Hu3DModelPosSet(object->model[i + 1], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 1], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionAttrSet(object->model[i + 1], 1, 1);
        Hu3DModelPosSet(object->model[i + 5], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 5], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionAttrSet(object->model[i + 5], 1, 1);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        object->model[i + 10] = Hu3DModelRead3(inst_itemMdlFileTbl[inst_itemPrizeTbl[i]], 0x1AB9);
    }
    if (models->count > 0) {
        object->model[15] = Hu3DModelRead3(0x170037, 0x16B9);
        for (i = 1; i < models->count; i++) {
            object->model[i + 15] = Hu3DModelLink(object->model[15]);
        }
    }
    for (i = 0; i < models->count; i++) {
        Hu3DModelPosSet(object->model[i + 10], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 10], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(object->model[i + 10], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionAttrSet(object->model[i + 10], 1, 1);
        Hu3DModelPosSet(object->model[i + 15], 0, 0, 0);
        Hu3DModelScaleSet(object->model[i + 15], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DMotionAttrSet(object->model[i + 15], 1, 1);
    }
    inst_playerFunc = inst_PlayerBoxFollow;
    while (1) {
        inst_playerFunc(object);
        HuPrcVSleep();
    }
}

void inst_PlayerBoxFollow(omObjData *object) {
    omObjData *source;
    HmfModel *model;
    f32 duration;
    f32 time;
    InstModelHooks *models;
    s8 i;

    source = inst_boxWork.object;
    duration = Hu3DMotion[Hu3DData[source->model[0]].motId].unk02;
    time = Hu3DData[source->model[0]].motTime;
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        model = &Hu3DData[object->model[i + 1]];
        Hu3DModelObjMtxFrameGet(source->model[0], time, models->nodes[i], &model->mtx);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        model = &Hu3DData[object->model[i + 10]];
        Hu3DModelObjMtxFrameGet(source->model[0], time, models->nodes[i], &model->mtx);
    }
    if (inst_BoxMotionEndCheck() == 1) {
        models = inst_hookTbl[inst_mgType][0];
        for (i = 0; i < models->count; i++) {
            Hu3DMotionTimeSet(object->model[i + 1], 0);
            Hu3DMotionAttrSet(object->model[i + 1], 1, 0);
            Hu3DData[object->model[i + 1]].rot.x = 0;
            Hu3DModelObjMtxFrameGet(source->model[0], duration, models->nodes[i], &inst_playerMtx);
            Hu3DModelPosSet(object->model[i + 5], inst_playerMtx[3][0] * 0.5f, inst_playerMtx[3][1] * 0.5f,
                            inst_playerMtx[3][2] * 0.5f);
        }
        models = inst_hookTbl[inst_mgType][1];
        for (i = 0; i < models->count; i++) {
            Hu3DMotionTimeSet(object->model[i + 10], 0);
            Hu3DMotionAttrSet(object->model[i + 10], 1, 0);
            Hu3DData[object->model[i + 10]].rot.x = 0;
            Hu3DModelObjMtxFrameGet(source->model[0], duration, models->nodes[i], &inst_playerMtx);
            Hu3DModelPosSet(object->model[i + 15], inst_playerMtx[3][0] * 0.5f, inst_playerMtx[3][1] * 0.5f,
                            inst_playerMtx[3][2] * 0.5f);
        }
        if (inst_playerCloseF == 0) {
            if (inst_introSkipF == 0) {
                inst_playerFunc = inst_PlayerOpenWait;
            } else {
                inst_playerFunc = inst_PlayerOpenNow;
            }
        } else {
            inst_playerFunc = inst_PlayerIdle;
        }
    }
}

void inst_PlayerOpenWait(omObjData *object) {
    if (inst_openF == 1) {
        inst_playerFunc = inst_PlayerOpenStart;
    }
}

void inst_PlayerOpenStart(omObjData *object) {
    s32 i;
    InstModelHooks *models;

    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        Hu3DModelAttrSet(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 5], 0);
        Hu3DMotionAttrSet(object->model[i + 5], 1, 0);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        Hu3DModelAttrSet(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 15], 0);
        Hu3DMotionAttrSet(object->model[i + 15], 1, 0);
    }
    inst_playerFunc = inst_PlayerOpen;
}

void inst_PlayerOpen(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s8 i;

    duration = Hu3DMotion[Hu3DData[object->model[5]].motId].unk02 - 20.0f;
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, (1.0f / duration) * inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 1]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 1]].mtx);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, (1.0f / duration) * inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 10]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 10]].mtx);
    }
    inst_playerOpenCnt++;
    if (inst_playerOpenCnt >= duration) {
        inst_playerFunc = inst_PlayerIdle;
        inst_openDoneF = 1;
        inst_playerOpenCnt = 0;
    }
}

void inst_PlayerIdle(omObjData *object) {
}

void inst_PlateColorSet(void) {
    s32 i;

    switch (inst_mgType) {
        case 0:
        case 1:
        case 2:
            for (i = 0; i < 4; i++) {
                if (mgPlayerTeam[inst_playerOrderTbl[i]] == 0) {
                    inst_plateColorTbl[i] = 0;
                } else {
                    inst_plateColorTbl[i] = 1;
                }
            }
            break;
        case 3:
        case 4:
        case 5:
        case 7:
            inst_plateColorTbl[0] = 2;
            inst_plateColorTbl[1] = 2;
            inst_plateColorTbl[2] = 2;
            inst_plateColorTbl[3] = 2;
            break;
        case 8:
            inst_plateColorTbl[0] = 3;
            inst_plateColorTbl[1] = 3;
            inst_plateColorTbl[2] = 3;
            inst_plateColorTbl[3] = 3;
            break;
    }
}

void inst_OpenStart(void) {
    inst_openF = 1;
}

s32 inst_OpenCheck(void) {
    return inst_openF;
}

s32 inst_OpenDoneCheck(void) {
    return inst_openDoneF;
}

void inst_PlayerCloseStart(void) {
    s8 i;
    omObjData *object = inst_playerObj;
    InstModelHooks *models;

    inst_playerCloseF = 1;
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        Hu3DMotionAttrSet(object->model[i + 5], 1, 0);
        Hu3DMotionAttrSet(object->model[i + 5], 4, 4);
        Hu3DModelAttrSet(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        Hu3DMotionAttrSet(object->model[i + 15], 1, 0);
        Hu3DMotionAttrSet(object->model[i + 15], 4, 4);
        Hu3DModelAttrSet(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    inst_playerFunc = inst_PlayerClose;
}

void inst_PlayerClose(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s8 i;

    duration = Hu3DMotion[Hu3DData[object->model[5]].motId].unk02 - 20.0f;
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, (1.0f / duration) * inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 1]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 1]].mtx);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, (1.0f / duration) * inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 10]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 10]].mtx);
    }
    inst_playerCloseCnt++;
    if (inst_playerCloseCnt == duration) {
        models = inst_hookTbl[inst_mgType][0];
        for (i = 0; i < models->count; i++) {
            Hu3DModelAttrSet(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        models = inst_hookTbl[inst_mgType][1];
        for (i = 0; i < models->count; i++) {
            Hu3DModelAttrSet(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        inst_BoxMotionRevStart();
        inst_playerFunc = inst_PlayerBoxFollow;
        inst_playerCloseCnt = 0;
    }
}

void inst_PlayerOpenNow(omObjData *object) {
    HuMtx4F rotation;
    HuMtx4F matrix;
    f32 duration;
    InstModelHooks *models;
    s32 i;

    duration = Hu3DMotion[Hu3DData[object->model[5]].motId].unk02;
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        Hu3DModelAttrSet(object->model[i + 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 5], duration);
        Hu3DMotionAttrSet(object->model[i + 5], 1, 0);
    }
    models = inst_hookTbl[inst_mgType][1];
    duration = Hu3DMotion[Hu3DData[object->model[15]].motId].unk02;
    for (i = 0; i < models->count; i++) {
        Hu3DModelAttrSet(object->model[i + 15], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(object->model[i + 15], duration);
        Hu3DMotionAttrSet(object->model[i + 15], 1, 0);
    }
    models = inst_hookTbl[inst_mgType][0];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 1]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 1]].mtx);
    }
    models = inst_hookTbl[inst_mgType][1];
    for (i = 0; i < models->count; i++) {
        HuMtxRotXF(rotation, inst_cameraTilt);
        mtxCopy(matrix, Hu3DData[object->model[i + 10]].mtx);
        mtxCat(rotation, matrix, Hu3DData[object->model[i + 10]].mtx);
    }
    inst_playerFunc = inst_PlayerIdle;
}
