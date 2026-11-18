#include "common.h"
#include "game/hmfmath.h"
#include "game/overlays/minigame.h"
#include "game/hmfcoll.h"

extern f32 CFanOfs;
extern f32 CFanLen;

extern void (*const mstory2_sceneCreateTbl[])(void);
extern const s32 mstory2_sceneFlagTbl[];
extern s16 mstory2_sceneNo;
extern s16 mstory2_padNo;
extern s16 mstory2_winId;
extern u16 mstory2_backSpr;
extern s16 mstory2_backMdl;
extern s32 mstory2_stampNo;
extern s16 mstory2_stampCardSprTbl[8];
extern s16 mstory2_stampSparkSprTbl[8];
extern s16 mstory2_stampFadeSpr;
extern const s32 mstory2_stampSprFileTbl[7];
extern const s16 mstory2_stampPosTbl[][2];
extern s16 mstory2_playerOrderTbl[4];

void mstory2_SceneInit(void);
void mstory2_SceneObjMain(omObjData *obj);
void mstory2_ExitObjMain(omObjData *obj);
void mstory2_BackCreate(void);
void mstory2_ExitWaitObjMain(omObjData *);
void mstory2_ExitWipeObjMain(omObjData *);
void mstory2_WinCreate(void);
void mstory2_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory2_ObjPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void mstory2_ObjRotMoveV(omObjData *obj, Vec *pos, s32 frames);
s32 mstory2_MotionEndCheck(s16 model);
void mstory2_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory2_ObjTargetFace(omObjData *obj, omObjData *target);
void mstory2_StampCardProc(void);
void mstory2_StampCardDestroy(void);
void mstory2_ObjPosMoveAccel(omObjData *obj, Vec *target, s32 frames, s32 faceDir);
void mstory2_Scene0Create(void);
void mstory2_Scene1Create(void);
void mstory2_Scene2Create(void);
void mstory2_Scene3Create(void);
void mstory2_Scene4Create(void);

Vec mstory2_cameraPos = { 14.0f, 193.0f, 1400.0f };
Vec mstory2_cameraTarget = { -25.0f, 0.0f, -650.0f };
Vec mstory2_cameraUp = { 0.0f, 1.0f, -0.0001f };
s16 mstory2_skipOnF = 0;
s16 mstory2_sceneState = 0;
s16 mstory2_stageGotoF = 0;
s32 mstory2_stampCardDoneF = 0;

void mstory2_ObjectSetup(void) {
    mstory2_SceneInit();
}

void mstory2_LightInit(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void mstory2_CameraObjMain(omObjData *obj) {
    CFan.x = mstory2_cameraPos.x;
    CFan.z = mstory2_cameraPos.z;
    CFan.angle = 0.0f;
    CFan.shape.spread = 35.0f;
    CFan.shape.length = CFanLen;
    CFan.shape.offset = CFanOfs;
    Hu3DCameraPosSetV(0, &mstory2_cameraPos, &mstory2_cameraTarget, &mstory2_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void mstory2_CameraInit(void) {
    omObjData *obj;

    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, mstory2_CameraObjMain);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mstory2_CameraObjMain(obj);
}

void mstory2_WinInit(void) {
    HuWinInit();
}

void mstory2_PlayerOrderInit(void) {
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                mstory2_playerOrderTbl[count++] = i;
            }
            if (count >= 4) {
                return;
            }
        }
        if (count >= 4) {
            return;
        }
    }
}

void mstory2_SceneInit(void) {
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    mstory2_LightInit();
    mstory2_CameraInit();
    mstory2_WinInit();
    mstory2_PlayerOrderInit();
    mstory2_sceneNo = GwPlayer[0].coin;
    if (mstory2_sceneNo >= 5) {
        mstory2_sceneNo = 4;
    }
    omAddObj(0, 0, 0, -1, mstory2_SceneObjMain);
    omAddObj(0, 0, 0, -1, mstory2_ExitObjMain);
    mstory2_BackCreate();
    if (mstory2_sceneNo != 0) {
        if (_CheckFlag(mstory2_sceneFlagTbl[mstory2_sceneNo])) {
            mstory2_skipOnF = 1;
        } else {
            _SetFlag(mstory2_sceneFlagTbl[mstory2_sceneNo]);
        }
    }
    for (mstory2_padNo = 0; mstory2_padNo < 4; mstory2_padNo++) {
        if (CheckControllerRead(mstory2_padNo)) {
            break;
        }
    }
    if (mstory2_padNo >= 4) {
        mstory2_padNo = 0;
    }
    mstory2_sceneCreateTbl[mstory2_sceneNo]();
    WipeCreateIn(WIPE_STARS, 16);
}

void (*const mstory2_sceneCreateTbl[])(void) = { mstory2_Scene0Create, mstory2_Scene1Create, mstory2_Scene2Create, mstory2_Scene3Create, mstory2_Scene4Create };

const s32 mstory2_sceneFlagTbl[] = { -1, 0x33, 0x35, 0x37, 0x39 };

void mstory2_SceneObjMain(omObjData *obj) {
    s16 state = mstory2_sceneState;

    switch (state) {
        case 0:
            HuAudSeqPlay(mstory2_sceneNo == 0 ? 0x2C : 0x26);
            state++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                state++;
            }
            break;
        case 2:
            if (mstory2_sceneNo != 0 && mstory2_skipOnF == 1 && (HuPadBtnDown[mstory2_padNo] & START_BUTTON)) {
                state++;
            }
            break;
        case 4:
            mstory2_stageGotoF = 1;
        case 3:
        default:
            obj->func = mstory2_ExitWipeObjMain;
            break;
    }
    mstory2_sceneState = state;
}

void mstory2_SceneEnd(void) {
    mstory2_sceneState = 3;
}

void mstory2_SceneStageGoto(void) {
    mstory2_sceneState = 4;
}

void mstory2_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        if (mstory2_stageGotoF == 0) {
            if (mstory2_sceneNo != 0) {
                SLCommonSet(1);
            }
            omOvlReturnEx(1);
        } else if (mstory2_stageGotoF == 1) {
            MgStoryStageGoto();
        }
    }
}

void mstory2_ExitWipeObjMain(omObjData *obj) {
    WipeCreateOut(WIPE_STARS, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    obj->func = mstory2_ExitWaitObjMain;
}

void mstory2_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        obj->func = mstory2_ExitWipeObjMain;
    }
}

void mstory2_WinCreate(void) {
    s16 comKeys[4] = { 0, 0, 0, 0 };
    s16 playerBits[4] = { 1, 2, 4, 8 };

    mstory2_winId = HuWinExCreateStyled(160, 194, 20);
    comKeys[mstory2_padNo] = HUWIN_COMKEY_PAD;
    HuWinAttrSet(mstory2_winId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
    HuWinActivePlayerSet(mstory2_winId, playerBits[mstory2_padNo]);
    HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
}

void mstory2_WinOpen(void) {
    HuWinHomeClear(mstory2_winId);
    HuWinExOpen(mstory2_winId, 1);
}

void mstory2_WinClose(void) {
    HuWinExClose(mstory2_winId, 1);
}

void mstory2_WinMesExec(s32 mess) {
    HuWinMesSet(mstory2_winId, mess, -1, -1);
    while (HuWinStatGet(mstory2_winId) != 0) {
        HuPrcVSleep();
    }
}

void mstory2_WinMesChrNameExec(s32 mess) {
    HuWinMesSet(mstory2_winId, mess, -1, -1);
    HuWinInsertMesSet(mstory2_winId, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(mstory2_winId) != 0) {
        HuPrcVSleep();
    }
}

s16 mstory2_WinChoiceGet(void) {
    return HuWinChoiceGet(mstory2_winId, 0, 1);
}

void mstory2_BackSprDispOn(void) {
    espDispOn(mstory2_backSpr);
}

void mstory2_BackSprDispOff(void) {
    espDispOff(mstory2_backSpr);
}

void mstory2_BackMotionStart(void) {
    HuAudFXPlay(0x216);
    Hu3DMotionAttrSet(mstory2_backMdl, 4, 0);
    Hu3DMotionAttrSet(mstory2_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory2_backMdl, 0.0f);
    Hu3DMotionSpeedSet(mstory2_backMdl, 2.0f);
}

void mstory2_BackMotionReverse(void) {
    Hu3DMotionAttrSet(mstory2_backMdl, 4, 4);
    Hu3DMotionAttrSet(mstory2_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory2_backMdl, Hu3DData[mstory2_backMdl].motTime);
}

void mstory2_BackRotExec(void) {
    s16 i = 0;

    Hu3DData[mstory2_backMdl].rot.y += -10.6f;
    while (i < 5) {
        Hu3DData[mstory2_backMdl].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    }
}

void mstory2_BackCreate(void) {
    mstory2_backSpr = espEntry(HuSprAnimDataRead(0x1D0012), 0, 0);
    espPosSet(mstory2_backSpr, 160, 120);
    espAttrSet(mstory2_backSpr, HUSPR_ATTR_BG);
    mstory2_backMdl = Hu3DModelRead(0x1D0014, 0x2B9);
    Hu3DModelPosSet(mstory2_backMdl, 591.7f, -81.0f, -1305.7f);
    Hu3DMotionAttrSet(mstory2_backMdl, 2, 0);
    Hu3DMotionAttrSet(mstory2_backMdl, 1, 1);
}

void mstory2_StampCardStart(s32 arg0) {
    mstory2_stampNo = arg0;
    mstory2_stampCardDoneF = 0;
    omAddPrcObj(mstory2_StampCardProc, 0x1000, 0x800, 0);
}

void mstory2_StampCardProc(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    mstory2_stampCardSprTbl[0] = espEntry(HuSprAnimDataRead(0x1D0001), 0, 0);
    espPosSet(mstory2_stampCardSprTbl[0], 160, 120);
    espDispOff(mstory2_stampCardSprTbl[0]);
    for (i = 0; i < 7; i++) {
        mstory2_stampCardSprTbl[i + 1] = espEntry(HuSprAnimDataRead(mstory2_stampSprFileTbl[i]), 0, 0);
        espPosSet(mstory2_stampCardSprTbl[i + 1], mstory2_stampPosTbl[i][0] + 48, mstory2_stampPosTbl[i][1] + 48);
        espAttrSet(mstory2_stampCardSprTbl[i + 1], HUSPR_ATTR_FILTER_BILERP);
        espDispOff(mstory2_stampCardSprTbl[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        mstory2_stampSparkSprTbl[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = mstory2_stampPosTbl[mstory2_stampNo][0] + 48;
        y = mstory2_stampPosTbl[mstory2_stampNo][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(mstory2_stampSparkSprTbl[i], x, y);
        espAttrSet(mstory2_stampSparkSprTbl[i], HUSPR_ATTR_XLU);
        espColorSet(mstory2_stampSparkSprTbl[i], 255, 255, 192);
        espAttrSet(mstory2_stampSparkSprTbl[i], HUSPR_ATTR_FILTER_BILERP);
        espScaleSet(mstory2_stampSparkSprTbl[i], 1.5f, 1.5f);
        espTPLvlSet(mstory2_stampSparkSprTbl[i], 255);
        espDispOff(mstory2_stampSparkSprTbl[i]);
    }
    HuMemMemoryFreePerm(data);
    mstory2_stampFadeSpr = espEntry(HuSprAnimDataRead(0x1D0000), 0, 0);
    espPosSet(mstory2_stampFadeSpr, 160, 120);
    espScaleSet(mstory2_stampFadeSpr, 40.0f, 30.0f);
    espAttrSet(mstory2_stampFadeSpr, HUSPR_ATTR_NONE);
    espDispOff(mstory2_stampFadeSpr);
    omPrcSetDestructor(0, mstory2_StampCardDestroy);
    espDispOn(mstory2_stampFadeSpr);
    espTPLvlSet(mstory2_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory2_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory2_stampFadeSpr, 256);
    for (i = 0; i < mstory2_stampNo; i++) {
        espDispOn(mstory2_stampCardSprTbl[i + 1]);
    }
    mstory2_BackSprDispOff();
    espDispOn(mstory2_stampCardSprTbl[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory2_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory2_stampFadeSpr);
    espTPLvlSet(mstory2_stampCardSprTbl[mstory2_stampNo + 1], 0);
    espDispOn(mstory2_stampCardSprTbl[mstory2_stampNo + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(mstory2_stampCardSprTbl[mstory2_stampNo + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory2_stampCardSprTbl[mstory2_stampNo + 1], 255);
    espScaleSet(mstory2_stampCardSprTbl[mstory2_stampNo + 1], 1.0f, 1.0f);
    for (i = 0; i < 8; i++) {
        espBankSet(mstory2_stampSparkSprTbl[i], 0, 0);
        espAnimModeSet(mstory2_stampSparkSprTbl[i], 1);
        espDispOn(mstory2_stampSparkSprTbl[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(mstory2_stampSparkSprTbl[i]);
    }
    if (mstory2_stampNo == 6) {
        HuPrcSleep(40);
        espDispOn(mstory2_stampFadeSpr);
        espTPLvlSet(mstory2_stampFadeSpr, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory2_stampFadeSpr, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(mstory2_stampFadeSpr, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory2_stampFadeSpr, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(mstory2_stampFadeSpr);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(mstory2_stampFadeSpr);
    espTPLvlSet(mstory2_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory2_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory2_stampFadeSpr, 256);
    espDispOff(mstory2_stampCardSprTbl[mstory2_stampNo + 1]);
    espDispOff(mstory2_stampCardSprTbl[0]);
    mstory2_BackSprDispOn();
    HuPrcSleep(30);
    for (i = 0; i < mstory2_stampNo; i++) {
        espDispOff(mstory2_stampCardSprTbl[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory2_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory2_stampFadeSpr);
    mstory2_stampCardDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 mstory2_StampCardDoneCheck(void) {
    return mstory2_stampCardDoneF;
}

void mstory2_StampCardDestroy(void) {
}

void mstory2_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void mstory2_ObjPosMoveV(omObjData *obj, Vec *pos, s32 frames) {
    mstory2_ObjPosMoveEx(obj, pos, frames, 1);
}

void mstory2_ObjPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
    Vec start;
    Vec diff;
    Vec step;
    Vec cur;
    s16 model = obj->model[1];
    f32 i;

    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = pos->x - start.x;
    diff.y = pos->y - start.y;
    diff.z = pos->z - start.z;
    if (arg3 != 0) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    i = frames;
    step.x = diff.x / i;
    step.y = diff.y / i;
    step.z = diff.z / i;
    for (i = 0.0f; i < (f32)frames; i += 1.0f) {
        cur.x = i * step.x + start.x;
        cur.y = i * step.y + start.y;
        cur.z = i * step.z + start.z;
        Hu3DModelPosSet(model, cur.x, cur.y, cur.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], cur.x, -5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, -5.0f, pos->z);
    }
    HuPrcVSleep();
}

void mstory2_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory2_ObjPosMoveV(obj, &pos, frames);
}

void mstory2_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory2_ObjPosMoveEx(obj, &pos, frames, arg3);
}

void mstory2_ObjRotMoveV(omObjData *obj, Vec *target, s32 frames) {
    Vec start;
    Vec delta;
    Vec rot;
    s16 model = obj->model[1];
    f32 t;
    f32 angle;

    start.x = Hu3DData[model].rot.x;
    start.y = Hu3DData[model].rot.y;
    start.z = Hu3DData[model].rot.z;
    delta.x = target->x - start.x;
    delta.y = target->y - start.y;
    delta.z = target->z - start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        angle = 90.0f / frames * t;
        rot.x = sindf(angle) * delta.x + start.x;
        rot.y = sindf(angle) * delta.y + start.y;
        rot.z = sindf(angle) * delta.z + start.z;
        Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(model, target->x, target->y, target->z);
    HuPrcVSleep();
}

void mstory2_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory2_ObjRotMoveV(obj, &pos, frames);
}

void mstory2_MotionEndWait(s16 model) {
    HuPrcSleep(10);
    while (!mstory2_MotionEndCheck(model)) {
        HuPrcVSleep();
    }
}

s32 mstory2_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void mstory2_ObjForwardMove(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x += dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z += dz;
        HuPrcVSleep();
    }
}

void mstory2_ObjBackwardMove(omObjData *obj, f32 speed, s16 frames) {
    f32 dx;
    f32 dz;
    f32 t;

    dx = speed * sindf(Hu3DData[obj->model[1]].rot.y);
    dz = speed * cosdf(Hu3DData[obj->model[1]].rot.y);
    for (t = 0.0f; t < frames; t += 1.0f) {
        Hu3DData[obj->model[2]].pos.x = Hu3DData[obj->model[1]].pos.x -= dx;
        Hu3DData[obj->model[2]].pos.z = Hu3DData[obj->model[1]].pos.z -= dz;
        HuPrcVSleep();
    }
}

void mstory2_ObjTargetFace(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

void mstory2_ObjPosMoveAccel(omObjData *obj, Vec *target, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec vel;
    Vec pos;
    Vec accel;
    s16 model;
    f32 t;

    model = obj->model[1];
    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = target->x - start.x;
    diff.y = target->y - start.y;
    diff.z = target->z - start.z;
    if (faceDir) {
        Hu3DModelRotSet(model, 0.0f, -(atan2df(diff.z, diff.x) - 90.0f), 0.0f);
    }
    t = frames;
    accel.x = diff.x / t / 90.0f;
    accel.y = diff.y / t / 90.0f;
    accel.z = diff.z / t / 90.0f;
    vel.x = diff.x / t;
    vel.y = diff.y / t;
    vel.z = diff.z / t;
    pos.x = start.x;
    pos.y = start.y;
    pos.z = start.z;
    for (t = 0.0f; t < frames; t += 1.0f) {
        if (t < 50.0f) {
            pos.x += vel.x;
            pos.y += vel.y;
            pos.z += vel.z;
        } else {
            pos.x += vel.x += accel.x;
            pos.y += vel.y += accel.y;
            pos.z += vel.z += accel.z;
        }
        if (pos.x <= target->x) {
            pos.x = target->x;
            pos.y = target->y;
            pos.z = target->z;
            Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
            if (obj->model[2] >= 0) {
                Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
            }
            break;
        }
        Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
        if (obj->model[2] >= 0) {
            Hu3DModelPosSet(obj->model[2], pos.x, pos.y - 5.0f, pos.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, target->x, target->y, target->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], target->x, target->y - 5.0f, target->z);
    }
    HuPrcVSleep();
}

const s32 mstory2_stampSprFileTbl[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };

const s16 mstory2_stampPosTbl[7][2] = {
    { 57, 20 },
    { 129, 36 },
    { 200, 22 },
    { 215, 91 },
    { 150, 124 },
    { 81, 105 },
    { 12, 122 },
};
