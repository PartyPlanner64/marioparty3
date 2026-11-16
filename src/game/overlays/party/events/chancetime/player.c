#include "common.h"
#include "chancetime.h"

extern s32 chancetime_playerEnterF;
extern s32 chancetime_playerEnterDoneF;
extern s8 chancetime_hitBlockNo;
extern s16 chancetime_playerAnimTbl[3];
extern ChanceTimeObjState chancetime_playerWork;
extern s32 omCharModelNoTbl[][6];

void chancetime_PlayerIdle(omObjData *object);
void chancetime_PlayerDestroy(void);
void chancetime_PlayerWalkIn(omObjData *object);
void chancetime_PlayerTurn(omObjData *object);
void chancetime_PlayerBlockGrow(omObjData *object);
void chancetime_PlayerHit(omObjData *object);

s32 chancetime_playerHitDoneF = 0;
f32 chancetime_playerWalkX = 360.0f;
f32 chancetime_playerTurnRot = 0.0f;
f32 chancetime_blockScale = 0.2f;

void chancetime_PlayerProc(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 6, 10, -1, NULL);
    chancetime_playerWork.obj = obj;
    chr = GwPlayer[chancetime_playerOrderTbl[0]].chr;

    obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][2], 0x2A9);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelPosSet(obj->model[1], 360.0f, 0.0f, -50.0f);
    Hu3DModelRotSet(obj->model[1], 0.0f, -90.0f, 0.0f);
    Hu3DModelAttrSet(obj->model[1], 4, 4);
    Hu3DModelCameraSet(obj->model[1], 2);

    obj->model[2] = Hu3DModelRead(9, 0x2B9);
    Hu3DModelPosSet(obj->model[2], 360.0f, -10.0f, -50.0f);
    Hu3DModelScaleSet(obj->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(obj->model[2], 4, 4);
    Hu3DModelCameraSet(obj->model[2], 2);

    obj->model[3] = Hu3DModelRead(0x1C000B, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 180.0f, 220.0f, 0.0f);
    Hu3DMotionAttrSet(obj->model[3], 2, 0);
    Hu3DModelScaleSet(obj->model[3], 0.7f, 0.7f, 0.7f);
    Hu3DModelAttrSet(obj->model[3], 4, 4);
    Hu3DModelCameraSet(obj->model[3], 2);

    obj->model[4] = Hu3DModelRead(0x5D0008, 0x2B9);
    Hu3DModelPosSet(obj->model[4], 180.0f, 220.0f, 0.0f);
    Hu3DModelAttrSet(obj->model[4], 4, 4);

    chancetime_playerAnimTbl[0] = CharAnimCreate(obj->model[1], 2, chr, CharMotionDataNumGet(chr, 0xA4));
    chancetime_playerAnimTbl[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    chancetime_playerAnimTbl[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA6));
    Hu3DModelDynamicFree(obj->model[1]);
    CharAnimSet(obj->model[1], 2, GwPlayer[chancetime_playerOrderTbl[0]].chr, chancetime_playerAnimTbl[0]);

    omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 1));
    omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x2F));
    omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 4, CharMotionDataNumGet(chr, 0x36));
    omObjMotionRead(obj, 5, CharMotionDataNumGet(chr, 0x2B));
    omObjMotionRead(obj, 6, CharMotionDataNumGet(chr, 0x1F));
    Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, chancetime_PlayerDestroy);
    chancetime_playerWork.func = chancetime_PlayerIdle;

    while (TRUE) {
        chancetime_playerWork.func(obj);
        HuPrcVSleep();
    }
}

void chancetime_PlayerIdle(omObjData *object) {
}

void chancetime_PlayerDestroy(void) {
}

void chancetime_PlayerWalkIn(omObjData *object) {
    s16 done = FALSE;

    chancetime_playerWalkX -= 25.0f;
    if (chancetime_playerWalkX <= 180.0f) {
        chancetime_playerWalkX = 180.0f;
        done = TRUE;
    }
    Hu3DModelPosSet(object->model[1], chancetime_playerWalkX, 0.0f, -50.0f);
    Hu3DModelPosSet(object->model[2], chancetime_playerWalkX, -10.0f, -50.0f);
    if (done == TRUE) {
        chancetime_playerWalkX = 360.0f;
        chancetime_playerWork.func = chancetime_PlayerTurn;
    }
}

void chancetime_PlayerTurn(omObjData *object) {
    s16 done = FALSE;

    chancetime_playerTurnRot += 8.0f;
    if (chancetime_playerTurnRot >= 90.0f) {
        chancetime_playerTurnRot = 90.0f;
        done = TRUE;
    }
    Hu3DModelRotSet(object->model[1], 0.0f, chancetime_playerTurnRot + -90.0f, 0.0f);
    if (done == TRUE) {
        chancetime_playerTurnRot = 0.0f;
        chancetime_playerEnterF = 0;
        chancetime_playerEnterDoneF = done;
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[0]].motId, 0, 30, 2);
        Hu3DModelScaleSet(object->model[3], 0.2f, 0.2f, 0.2f);
        Hu3DMotionAttrSet(object->model[3], 2, 0);
        Hu3DMotionAttrSet(object->model[3], 1, 1);
        Hu3DModelAttrSet(object->model[3], 4, 0);
        Hu3DModelPosSet(object->model[4], Hu3DData[object->model[3]].pos.x, Hu3DData[object->model[3]].pos.y,
                        Hu3DData[object->model[3]].pos.z);
        Hu3DModelAttrSet(object->model[4], 4, 0);
        Hu3DMotionAttrSet(object->model[4], 2, 0);
        Hu3DMotionAttrSet(object->model[4], 1, 0);
        chancetime_playerWork.func = chancetime_PlayerBlockGrow;
    }
}

void chancetime_PlayerBlockGrow(omObjData *object) {
    s32 done = FALSE;

    HuPrcSleep(2);
    HuAudFXPlay(0x501);
    do {
        chancetime_blockScale += 0.14f;
        if (chancetime_blockScale >= 0.7f) {
            chancetime_blockScale = 0.7f;
            done = TRUE;
        }
        Hu3DModelScaleSet(object->model[3], chancetime_blockScale, chancetime_blockScale, chancetime_blockScale);
        HuPrcVSleep();
    } while (done != TRUE);
    chancetime_blockScale = 0.0f;
    chancetime_playerWork.func = chancetime_PlayerIdle;
}

void chancetime_PlayerEnterStart(void) {
    omObjData *obj = chancetime_playerWork.obj;

    chancetime_playerEnterF = 1;
    chancetime_playerEnterDoneF = 0;
    Hu3DMotionModelSet(obj->model[1], obj->motion[1]);
    Hu3DMotionAttrSet(obj->model[1], 2, 2);
    Hu3DModelAttrSet(obj->model[1], 4, 0);
    Hu3DModelAttrSet(obj->model[2], 4, 0);
    chancetime_playerWork.func = chancetime_PlayerWalkIn;
}

s32 chancetime_PlayerEnterCheck(void) {
    return chancetime_playerEnterDoneF;
}

void chancetime_PlayerHitStart(s8 arg0) {
    chancetime_hitBlockNo = arg0;
    chancetime_playerWork.func = chancetime_PlayerHit;
}

s32 chancetime_PlayerHitCheck(void) {
    return chancetime_playerHitDoneF;
}

void chancetime_PlayerHit(omObjData *object) {
    s16 player = chancetime_playerOrderTbl[0];
    f32 time;
    s16 done;
    s16 delay;
    u16 btn;

    chancetime_playerHitDoneF = 0;
    // The repeated done checks and the delay/btn temporaries are needed for the original block layout.
    while (TRUE) {
        done = FALSE;
        if (GwPlayer[player].stat & 1) {
            done = TRUE;
        }
        if (done) {
            delay = (u8)(rand8() % 15) + 15;
            HuPrcSleep(delay);
        }
        if (done) {
            break;
        }
        btn = HuPadBtnDown[GwPlayer[player].pad] & 0x8000;
        if (btn) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[5]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    done = FALSE;
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        if (done == FALSE) {
            if (time >= 5.0f) {
                done = TRUE;
                chancetime_ReelStop(chancetime_hitBlockNo);
                Hu3DMotionAttrSet(object->model[3], 2, 0);
                Hu3DMotionAttrSet(object->model[3], 1, 0);
                Hu3DMotionTimeSet(object->model[3], 0.0f);
                Hu3DMotionSpeedSet(object->model[3], 1.2f);
                Hu3DModelAttrSet(object->model[3], 4, 0);
            }
        }
        HuPrcVSleep();
    } while (time >= 0.0f);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[6]].motId, 0, 20, 0);
    Hu3DMotionSpeedSet(object->model[1], 3.0f);
    do {
        time = Hu3DMotionShiftTimeGet(object->model[1]);
        HuPrcVSleep();
    } while (time >= 0.0f);
    time = 0.0f;
    Hu3DModelPosSet(object->model[1], 180.0f, time, -50.0f);
    Hu3DModelPosSet(object->model[3], 180.0f, 220.0f, time);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[0]].motId, 0, 20, 2);
    Hu3DMotionSpeedSet(object->model[1], 1.0f);
    chancetime_playerHitDoneF = 1;
    chancetime_playerWork.func = chancetime_PlayerIdle;
}

void chancetime_PlayerJoyExec(void) {
    omObjData *object = chancetime_playerWork.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x502);
    CharFXPlay(0x274, GwPlayer[chancetime_playerOrderTbl[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[chancetime_playerOrderTbl[0]].chr, chancetime_playerAnimTbl[1]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[2]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void chancetime_PlayerNeutralExec(void) {
    omObjData *object = chancetime_playerWork.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[chancetime_playerOrderTbl[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[chancetime_playerOrderTbl[0]].chr, chancetime_playerAnimTbl[2]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[3]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}

void chancetime_PlayerSadExec(void) {
    omObjData *object = chancetime_playerWork.obj;
    f32 time;
    f32 length;

    HuAudFXPlay(0x503);
    CharFXPlay(0x26B, GwPlayer[chancetime_playerOrderTbl[0]].chr);
    CharAnimSet(object->model[1], 2, GwPlayer[chancetime_playerOrderTbl[0]].chr, chancetime_playerAnimTbl[2]);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[4]].motId, 0, 30, 0);
    HuPrcSleep(30);
    do {
        time = Hu3DData[object->model[1]].motTime;
        length = Hu3DMotion[Hu3DData[object->model[1]].motId].unk02;
        HuPrcVSleep();
    } while (time < length);
}
