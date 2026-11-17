#include "common.h"
#include "game/hmfmath.h"

extern f32 CFanOfs;
extern f32 CFanLen;

extern void (*const mstory3_sceneCreateTbl[])(void);
extern const s32 mstory3_sceneFlagTbl[];
extern s16 mstory3_padNo;
extern s16 mstory3_winId;
extern u16 mstory3_backSpr;
extern s16 mstory3_backMdl;
extern s32 mstory3_stampNo;
extern s16 mstory3_stampCardSprTbl[8];
extern s16 mstory3_stampSparkSprTbl[8];
extern s16 mstory3_stampFadeSpr;
extern const s32 mstory3_stampSprFileTbl[7];
extern const s16 mstory3_stampPosTbl[][2];
extern s16 mstory3_playerOrderTbl[4];

void mstory3_SceneInit(void);
void mstory3_SceneObjMain(omObjData *obj);
void mstory3_ExitObjMain(omObjData *obj);
void mstory3_BackCreate(void);
void mstory3_ExitWaitObjMain(omObjData *);
void mstory3_ExitWipeObjMain(omObjData *obj);
void mstory3_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory3_HmfAnimSet(s16 model, s16 arg1, s16 arg2);
void mstory3_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory3_MotionEndWait(s16 model);
void mstory3_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
s32 mstory3_MotionEndCheck(s16 model);
void mstory3_ObjTargetFace(omObjData *obj, omObjData *target);
void mstory3_StampCardProc(void);
void mstory3_StampCardDestroy(void);
void mstory3_ObjPosMoveAccel(omObjData *obj, const Vec *target, s32 frames, s32 faceDir);
void mstory3_Scene1Create(void);
void mstory3_Scene0Create(void);

Vec mstory3_cameraPos = { 14.0f, 193.0f, 1400.0f };
Vec mstory3_cameraTarget = { -25.0f, 0.0f, -650.0f };
Vec mstory3_cameraUp = { 0.0f, 1.0f, -0.0001f };
s16 mstory3_skipOnF = 0;
s16 mstory3_sceneState = 0;
s32 mstory3_stampCardDoneF = 0;

void mstory3_ObjectSetup(void) {
    mstory3_SceneInit();
}

void mstory3_LightInit(void) {
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void mstory3_CameraObjMain(omObjData *obj) {
    CFanParam[0] = mstory3_cameraPos.x;
    CFanParam[1] = mstory3_cameraPos.z;
    CFanParam[-1] = 0.0f;
    CFanParam[2] = 35.0f;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &mstory3_cameraPos, &mstory3_cameraTarget, &mstory3_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void mstory3_CameraInit(void) {
    omObjData *obj;

    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    obj = omAddObj(0x7FDA, 0, 0, -1, mstory3_CameraObjMain);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mstory3_CameraObjMain(obj);
}

void mstory3_WinInit(void) {
    HuWinInit();
}

void mstory3_PlayerOrderInit(void) {
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                mstory3_playerOrderTbl[count++] = i;
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

void (*const mstory3_sceneCreateTbl[])(void) = { mstory3_Scene0Create, mstory3_Scene1Create };

const s32 mstory3_sceneFlagTbl[] = { 61, 59 };

void mstory3_SceneInit(void) {
    s16 chapter;

    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    mstory3_LightInit();
    mstory3_CameraInit();
    mstory3_WinInit();
    mstory3_PlayerOrderInit();
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    omAddObj(0, 0, 0, -1, mstory3_SceneObjMain);
    omAddObj(0, 0, 0, -1, mstory3_ExitObjMain);
    mstory3_BackCreate();
    if (_CheckFlag(mstory3_sceneFlagTbl[chapter])) {
        mstory3_skipOnF = 1;
    } else {
        _SetFlag(mstory3_sceneFlagTbl[chapter]);
    }
    for (mstory3_padNo = 0; mstory3_padNo < 4; mstory3_padNo++) {
        if (CheckControllerRead(mstory3_padNo)) {
            break;
        }
    }
    if (mstory3_padNo >= 4) {
        mstory3_padNo = 0;
    }
    mstory3_sceneCreateTbl[chapter]();
    WipeCreateIn(WIPE_STARS, 16);
}

void mstory3_SceneObjMain(omObjData *obj) {
    s16 state = mstory3_sceneState;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                state++;
            }
            break;
        case 2:
            if (mstory3_skipOnF == 1 && (HuPadBtnDown[mstory3_padNo] & START_BUTTON)) {
                state++;
            }
            break;
        case 3:
            obj->func = mstory3_ExitWipeObjMain;
            state++;
            break;
        default:
            obj->func = mstory3_ExitWipeObjMain;
            break;
    }
    mstory3_sceneState = state;
}

void mstory3_SceneEnd(void) {
    mstory3_sceneState = 3;
}

void mstory3_ExitWaitObjMain(omObjData *obj) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        HuWinAllKill();
        SLCommonSet(1);
        omOvlReturnEx(1);
    }
}

void mstory3_ExitWipeObjMain(omObjData *obj) {
    WipeCreateOut(WIPE_STARS, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    obj->func = mstory3_ExitWaitObjMain;
}

void mstory3_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        obj->func = mstory3_ExitWipeObjMain;
    }
}

void mstory3_WinCreate(void) {
    s16 comKeys[4] = { 0, 0, 0, 0 };
    s16 playerBits[4] = { 1, 2, 4, 8 };

    mstory3_winId = HuWinExCreateStyled(160, 194, 20);
    comKeys[mstory3_padNo] = HUWIN_COMKEY_PAD;
    HuWinAttrSet(mstory3_winId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_NONE);
    HuWinActivePlayerSet(mstory3_winId, playerBits[mstory3_padNo]);
    HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
}

const s32 mstory3_stampSprFileTbl[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };

const s16 mstory3_stampPosTbl[7][2] = {
    { 57, 20 },
    { 129, 36 },
    { 200, 22 },
    { 215, 91 },
    { 150, 124 },
    { 81, 105 },
    { 12, 122 },
};

void mstory3_WinOpen(void) {
    HuWinHomeClear(mstory3_winId);
    HuWinExOpen(mstory3_winId, 1);
}

void mstory3_WinClose(void) {
    HuWinExClose(mstory3_winId, 1);
}

void mstory3_WinMesExec(s32 mess) {
    HuWinMesSet(mstory3_winId, mess, -1, -1);
    while (HuWinStatGet(mstory3_winId) != 0) {
        HuPrcVSleep();
    }
}

void mstory3_WinMesChrNameExec(s32 mess) {
    HuWinMesSet(mstory3_winId, mess, -1, -1);
    HuWinInsertMesSet(mstory3_winId, GwStory.unk1 + 0x1C00, 0);
    while (HuWinStatGet(mstory3_winId) != 0) {
        HuPrcVSleep();
    }
}

s16 mstory3_WinChoiceGet(void) {
    return HuWinChoiceGet(mstory3_winId, 0, 1);
}

void mstory3_BackSprDispOn(void) {
    espDispOn(mstory3_backSpr);
}

void mstory3_BackSprDispOff(void) {
    espDispOff(mstory3_backSpr);
}

void mstory3_BackMotionStart(void) {
    Hu3DMotionAttrSet(mstory3_backMdl, 4, 0);
    Hu3DMotionAttrSet(mstory3_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory3_backMdl, 0.0f);
    Hu3DMotionSpeedSet(mstory3_backMdl, 2.0f);
}

void mstory3_BackMotionReverse(void) {
    Hu3DMotionAttrSet(mstory3_backMdl, 4, 4);
    Hu3DMotionAttrSet(mstory3_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory3_backMdl, Hu3DData[mstory3_backMdl].motTime);
}

void mstory3_BackRotExec(void) {
    s16 i = 0;

    Hu3DData[mstory3_backMdl].rot.y += -10.6f;
    while (i < 5) {
        Hu3DData[mstory3_backMdl].rot.x += 17.84f;
        HuPrcVSleep();
        i++;
    }
}

void mstory3_BackCreate(void) {
    mstory3_backSpr = espEntry(HuSprAnimDataRead(0x1D0012), 0, 0);
    espPosSet(mstory3_backSpr, 160, 120);
    espAttrSet(mstory3_backSpr, 0x4000);
    mstory3_backMdl = Hu3DModelRead(0x1D0014, 0x2B9);
    Hu3DModelPosSet(mstory3_backMdl, 591.7f, -81.0f, -1305.7f);
    Hu3DMotionAttrSet(mstory3_backMdl, 2, 0);
    Hu3DMotionAttrSet(mstory3_backMdl, 1, 1);
}

void mstory3_StampCardStart(s32 arg0) {
    mstory3_stampNo = arg0;
    mstory3_stampCardDoneF = 0;
    omAddPrcObj(mstory3_StampCardProc, 0x1000, 0x800, 0);
}

void mstory3_StampCardProc(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    mstory3_stampCardSprTbl[0] = espEntry(HuSprAnimDataRead(0x1D0001), 0, 0);
    espPosSet(mstory3_stampCardSprTbl[0], 160, 120);
    espDispOff(mstory3_stampCardSprTbl[0]);
    for (i = 0; i < 7; i++) {
        mstory3_stampCardSprTbl[i + 1] = espEntry(HuSprAnimDataRead(mstory3_stampSprFileTbl[i]), 0, 0);
        espPosSet(mstory3_stampCardSprTbl[i + 1], mstory3_stampPosTbl[i][0] + 48, mstory3_stampPosTbl[i][1] + 48);
        espAttrSet(mstory3_stampCardSprTbl[i + 1], 8);
        espDispOff(mstory3_stampCardSprTbl[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        mstory3_stampSparkSprTbl[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = mstory3_stampPosTbl[mstory3_stampNo][0] + 48;
        y = mstory3_stampPosTbl[mstory3_stampNo][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(mstory3_stampSparkSprTbl[i], x, y);
        espAttrSet(mstory3_stampSparkSprTbl[i], 0x1000);
        espColorSet(mstory3_stampSparkSprTbl[i], 255, 255, 192);
        espAttrSet(mstory3_stampSparkSprTbl[i], 8);
        espScaleSet(mstory3_stampSparkSprTbl[i], 1.5f, 1.5f);
        espTPLvlSet(mstory3_stampSparkSprTbl[i], 255);
        espDispOff(mstory3_stampSparkSprTbl[i]);
    }
    HuMemMemoryFreePerm(data);
    mstory3_stampFadeSpr = espEntry(HuSprAnimDataRead(0x1D0000), 0, 0);
    espPosSet(mstory3_stampFadeSpr, 160, 120);
    espScaleSet(mstory3_stampFadeSpr, 40.0f, 30.0f);
    espAttrSet(mstory3_stampFadeSpr, 0);
    espDispOff(mstory3_stampFadeSpr);
    omPrcSetDestructor(0, mstory3_StampCardDestroy);
    espDispOn(mstory3_stampFadeSpr);
    espTPLvlSet(mstory3_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory3_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory3_stampFadeSpr, 256);
    for (i = 0; i < mstory3_stampNo; i++) {
        espDispOn(mstory3_stampCardSprTbl[i + 1]);
    }
    mstory3_BackSprDispOff();
    espDispOn(mstory3_stampCardSprTbl[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory3_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory3_stampFadeSpr);
    espTPLvlSet(mstory3_stampCardSprTbl[mstory3_stampNo + 1], 0);
    espDispOn(mstory3_stampCardSprTbl[mstory3_stampNo + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(mstory3_stampCardSprTbl[mstory3_stampNo + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory3_stampCardSprTbl[mstory3_stampNo + 1], 255);
    espScaleSet(mstory3_stampCardSprTbl[mstory3_stampNo + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(mstory3_stampSparkSprTbl[i], 0, 0);
        espAnimModeSet(mstory3_stampSparkSprTbl[i], 1);
        espDispOn(mstory3_stampSparkSprTbl[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(mstory3_stampSparkSprTbl[i]);
    }
    if (mstory3_stampNo == 6) {
        HuPrcSleep(40);
        espDispOn(mstory3_stampFadeSpr);
        espTPLvlSet(mstory3_stampFadeSpr, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory3_stampFadeSpr, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(mstory3_stampFadeSpr, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory3_stampFadeSpr, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(mstory3_stampFadeSpr);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(mstory3_stampFadeSpr);
    espTPLvlSet(mstory3_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory3_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory3_stampFadeSpr, 256);
    espDispOff(mstory3_stampCardSprTbl[mstory3_stampNo + 1]);
    espDispOff(mstory3_stampCardSprTbl[0]);
    mstory3_BackSprDispOn();
    HuPrcSleep(30);
    for (i = 0; i < mstory3_stampNo; i++) {
        espDispOff(mstory3_stampCardSprTbl[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory3_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory3_stampFadeSpr);
    mstory3_stampCardDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 mstory3_StampCardDoneCheck(void) {
    return mstory3_stampCardDoneF;
}

void mstory3_StampCardDestroy(void) {
}

void mstory3_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
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

void mstory3_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames) {
    mstory3_ObjPosMoveEx(obj, pos, frames, 1);
}

void mstory3_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void mstory3_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory3_ObjPosMoveV(obj, &pos, frames);
}

void mstory3_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory3_ObjPosMoveEx(obj, &pos, frames, arg3);
}

void mstory3_ObjRotMoveV(omObjData *obj, const Vec *target, s32 frames) {
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

void mstory3_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory3_ObjRotMoveV(obj, &pos, frames);
}

void mstory3_MotionEndWait(s16 model) {
    HuPrcSleep(10);
    while (!mstory3_MotionEndCheck(model)) {
        HuPrcVSleep();
    }
}

s32 mstory3_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void mstory3_ObjForwardMove(omObjData *obj, f32 speed, s16 frames) {
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

void mstory3_ObjBackwardMove(omObjData *obj, f32 speed, s16 frames) {
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

void mstory3_ObjTargetFace(omObjData *obj, omObjData *target) {
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

void mstory3_ObjLinkPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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
            Hu3DModelPosSet(obj->model[2], cur.x, cur.y - 5.0f, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], pos->x, pos->y - 5.0f, pos->z);
    }
    HuPrcVSleep();
}

void mstory3_ObjPosMoveAccel(omObjData *obj, const Vec *target, s32 frames, s32 faceDir) {
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
