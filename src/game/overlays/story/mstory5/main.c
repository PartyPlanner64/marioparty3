#include "common.h"
#include "game/hmfmath.h"
#include "game/hmfcoll.h"

extern f32 CFanOfs;
extern f32 CFanLen;

extern s16 mstory5_winId;
extern s16 mstory5_backMdl;
extern s32 mstory5_padNo;
extern void (*const mstory5_sceneCreateTbl[])(void);
extern const s32 mstory5_sceneFlagTbl[];
extern u16 mstory5_backSpr;
extern s32 mstory5_stampNo;
extern s16 mstory5_stampCardSprTbl[8];
extern s16 mstory5_stampSparkSprTbl[8];
extern s16 mstory5_stampFadeSpr;
extern const s32 mstory5_stampSprFileTbl[7];
extern const s16 mstory5_stampPosTbl[][2];

s32 mstory5_sceneState = 0;
s32 mstory5_skipOnF = 0;
s8 mstory5_exitF = 0;
Vec mstory5_cameraPos = { 14.0f, 193.0f, 1400.0f };
Vec mstory5_cameraTarget = { -25.0f, 0.0f, -650.0f };
Vec mstory5_cameraUp = { 0.0f, 1.0f, -0.0001f };
s32 mstory5_stampCardDoneF = 0;

void mstory5_Scene1Create(void);
void mstory5_Scene0Create(void);
void mstory5_StampCardProc(void);
void mstory5_StampCardDestroy(void);
void mstory5_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory5_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void mstory5_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory5_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);
void mstory5_MotionEndWait(s16 model);
s32 mstory5_MotionEndCheck(s16 model);
void mstory5_ObjForwardMove(omObjData *obj, f32 speed, s16 frames);
void mstory5_ObjPosMoveAccelXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir);
void mstory5_SceneObjMain(omObjData *obj);
void mstory5_ExitObjMain(omObjData *obj);
void mstory5_BackCreate(void);
void mstory5_CameraObjMain(omObjData *obj);

void mstory5_ObjectSetup(void) {
    omObjData *obj;
    s16 chapter;

    Hu3DSprModelInit(60);
    omInitObjMan(30, 30);
    HuWinInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, mstory5_CameraObjMain);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mstory5_CameraObjMain(obj);
    omAddObj(0, 0, 0, -1, mstory5_SceneObjMain);
    omAddObj(0, 0, 0, -1, mstory5_ExitObjMain);
    mstory5_BackCreate();
    for (mstory5_padNo = 0; mstory5_padNo < 4; mstory5_padNo++) {
        if (CheckControllerRead(mstory5_padNo)) {
            break;
        }
    }
    if (mstory5_padNo >= 4) {
        mstory5_padNo = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    mstory5_sceneCreateTbl[chapter]();
    if (_CheckFlag(mstory5_sceneFlagTbl[chapter])) {
        mstory5_skipOnF = 1;
    } else {
        _SetFlag(mstory5_sceneFlagTbl[chapter]);
    }
    WipeCreateIn(WIPE_STARS, 16);
}

void (*const mstory5_sceneCreateTbl[])(void) = { mstory5_Scene0Create, mstory5_Scene1Create };

const s32 mstory5_sceneFlagTbl[] = { 58, 60 };

void mstory5_SceneObjMain(omObjData *obj) {
    u32 state = mstory5_sceneState;
    s32 btn;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            state += WipeStatGet() == 0;
            break;
        case 2:
            if (mstory5_skipOnF == 1) {
                btn = HuPadBtnDown[mstory5_padNo] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            WipeCreateOut(WIPE_STARS, 20);
            HuAudSeqFadeOut(30);
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    mstory5_sceneState = state;
}

void mstory5_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mstory5_exitF == 0) {
            WipeCreateOut(WIPE_STARS, 20);
            HuAudSeqFadeOut(30);
            mstory5_exitF = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void mstory5_BackMotionStart(void) {
    Hu3DMotionAttrSet(mstory5_backMdl, 4, 0);
    Hu3DMotionAttrSet(mstory5_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory5_backMdl, 0.0f);
    HuAudFXPlay(0x216);
}

void mstory5_BackMotionReverse(void) {
    Hu3DMotionAttrSet(mstory5_backMdl, 4, 4);
    Hu3DMotionAttrSet(mstory5_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory5_backMdl, Hu3DMotion[Hu3DData[mstory5_backMdl].motId].unk02);
}

void mstory5_BackCreate(void) {
    mstory5_backSpr = espEntry(HuSprAnimDataRead(0x1D0012), 0, 0);
    espPosSet(mstory5_backSpr, 160, 120);
    espAttrSet(mstory5_backSpr, HUSPR_ATTR_BG);
    mstory5_backMdl = Hu3DModelRead(0x1D0014, 0x2B9);
    Hu3DModelPosSet(mstory5_backMdl, 591.7f, -81.0f, -1305.7f);
    Hu3DMotionAttrSet(mstory5_backMdl, 2, 0);
    Hu3DMotionAttrSet(mstory5_backMdl, 1, 1);
}

void mstory5_BackDispOff(void) {
    Hu3DModelAttrSet(mstory5_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(mstory5_backSpr);
}

void mstory5_BackDispOn(void) {
    Hu3DModelAttrSet(mstory5_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(mstory5_backSpr);
}

void mstory5_CameraObjMain(omObjData *obj) {
    CFan.x = mstory5_cameraPos.x;
    CFan.z = mstory5_cameraPos.z;
    CFan.angle = 0.0f;
    CFan.shape.spread = 35.0f;
    CFan.shape.length = CFanLen;
    CFan.shape.offset = CFanOfs;
    Hu3DCameraPosSetV(0, &mstory5_cameraPos, &mstory5_cameraTarget, &mstory5_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void mstory5_SceneEnd(void) {
    mstory5_sceneState = 3;
}

void mstory5_StampCardStart(s32 arg0) {
    mstory5_stampNo = arg0;
    mstory5_stampCardDoneF = 0;
    omAddPrcObj(mstory5_StampCardProc, 0x1000, 0x800, 0);
}

void mstory5_StampCardProc(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    mstory5_stampCardSprTbl[0] = espEntry(HuSprAnimDataRead(0x1D0001), 0, 0);
    espPosSet(mstory5_stampCardSprTbl[0], 160, 120);
    espDispOff(mstory5_stampCardSprTbl[0]);
    for (i = 0; i < 7; i++) {
        mstory5_stampCardSprTbl[i + 1] = espEntry(HuSprAnimDataRead(mstory5_stampSprFileTbl[i]), 0, 0);
        espPosSet(mstory5_stampCardSprTbl[i + 1], mstory5_stampPosTbl[i][0] + 48, mstory5_stampPosTbl[i][1] + 48);
        espAttrSet(mstory5_stampCardSprTbl[i + 1], HUSPR_ATTR_FILTER_BILERP);
        espDispOff(mstory5_stampCardSprTbl[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        mstory5_stampSparkSprTbl[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = mstory5_stampPosTbl[mstory5_stampNo][0] + 48;
        y = mstory5_stampPosTbl[mstory5_stampNo][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(mstory5_stampSparkSprTbl[i], x, y);
        espAttrSet(mstory5_stampSparkSprTbl[i], HUSPR_ATTR_XLU);
        espColorSet(mstory5_stampSparkSprTbl[i], 255, 255, 192);
        espAttrSet(mstory5_stampSparkSprTbl[i], HUSPR_ATTR_FILTER_BILERP);
        espScaleSet(mstory5_stampSparkSprTbl[i], 1.5f, 1.5f);
        espTPLvlSet(mstory5_stampSparkSprTbl[i], 255);
        espDispOff(mstory5_stampSparkSprTbl[i]);
    }
    HuMemMemoryFreePerm(data);
    mstory5_stampFadeSpr = espEntry(HuSprAnimDataRead(0x1D0000), 0, 0);
    espPosSet(mstory5_stampFadeSpr, 160, 120);
    espScaleSet(mstory5_stampFadeSpr, 40.0f, 30.0f);
    espAttrSet(mstory5_stampFadeSpr, HUSPR_ATTR_NONE);
    espDispOff(mstory5_stampFadeSpr);
    omPrcSetDestructor(0, mstory5_StampCardDestroy);
    espDispOn(mstory5_stampFadeSpr);
    espTPLvlSet(mstory5_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory5_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory5_stampFadeSpr, 256);
    for (i = 0; i < mstory5_stampNo; i++) {
        espDispOn(mstory5_stampCardSprTbl[i + 1]);
    }
    mstory5_BackDispOff();
    espDispOn(mstory5_stampCardSprTbl[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory5_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory5_stampFadeSpr);
    espTPLvlSet(mstory5_stampCardSprTbl[mstory5_stampNo + 1], 0);
    espDispOn(mstory5_stampCardSprTbl[mstory5_stampNo + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(mstory5_stampCardSprTbl[mstory5_stampNo + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory5_stampCardSprTbl[mstory5_stampNo + 1], 255);
    espScaleSet(mstory5_stampCardSprTbl[mstory5_stampNo + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(mstory5_stampSparkSprTbl[i], 0, 0);
        espAnimModeSet(mstory5_stampSparkSprTbl[i], 1);
        espDispOn(mstory5_stampSparkSprTbl[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(mstory5_stampSparkSprTbl[i]);
    }
    if (mstory5_stampNo == 6) {
        HuPrcSleep(40);
        espDispOn(mstory5_stampFadeSpr);
        espTPLvlSet(mstory5_stampFadeSpr, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory5_stampFadeSpr, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(mstory5_stampFadeSpr, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory5_stampFadeSpr, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(mstory5_stampFadeSpr);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(mstory5_stampFadeSpr);
    espTPLvlSet(mstory5_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory5_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory5_stampFadeSpr, 256);
    espDispOff(mstory5_stampCardSprTbl[mstory5_stampNo + 1]);
    espDispOff(mstory5_stampCardSprTbl[0]);
    mstory5_BackDispOn();
    HuPrcSleep(30);
    for (i = 0; i < mstory5_stampNo; i++) {
        espDispOff(mstory5_stampCardSprTbl[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory5_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory5_stampFadeSpr);
    mstory5_stampCardDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 mstory5_StampCardDoneCheck(void) {
    return mstory5_stampCardDoneF;
}

void mstory5_StampCardDestroy(void) {
}

void mstory5_StampCardClose(void) {
}

void mstory5_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
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

void mstory5_WinCreate(void) {
    mstory5_winId = HuWinExCreateStyled(160, 194, 20);
    HuWinActivePlayerSet(mstory5_winId, 1 << mstory5_padNo);
    HuWinInsertMesSet(mstory5_winId, GwStory.unk1 + 0x1C00, 0);
}

void mstory5_WinOpen(void) {
    HuWinHomeClear(mstory5_winId);
    HuWinExOpen(mstory5_winId, 1);
}

void mstory5_WinClose(void) {
    HuWinExClose(mstory5_winId, 1);
}

void mstory5_WinMesExec(s32 mess) {
    HuWinMesSet(mstory5_winId, mess, -1, -1);
    while (HuWinStatGet(mstory5_winId) != 0) {
        HuPrcVSleep();
    }
}

void mstory5_WinMesSet(s32 mess) {
    HuWinMesSet(mstory5_winId, mess, -1, -1);
}

void mstory5_WinMesWait(void) {
    while (HuWinStatGet(mstory5_winId) != 0) {
        HuPrcVSleep();
    }
}

s32 mstory5_PlayerChrCheck(s32 character) {
    return -(character == GwStory.unk1);
}

void mstory5_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames) {
    mstory5_ObjPosMoveEx(obj, pos, frames, 1);
}

void mstory5_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void mstory5_ObjLinkPosMoveV(omObjData *obj, Vec *pos, s32 frames) {
    mstory5_ObjLinkPosMoveEx(obj, pos, frames, 1);
}

void mstory5_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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
            Hu3DModelPosSet(obj->model[2], cur.x, cur.y, cur.z);
        }
        HuPrcVSleep();
    }
    Hu3DModelPosSet(model, pos->x, pos->y, pos->z);
    HuPrcVSleep();
}

void mstory5_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory5_ObjPosMoveV(obj, &pos, frames);
}

void mstory5_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory5_ObjPosMoveEx(obj, &pos, frames, arg3);
}

void mstory5_ObjLinkPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory5_ObjLinkPosMoveV(obj, &pos, frames);
}

void mstory5_ObjLinkPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory5_ObjLinkPosMoveEx(obj, &pos, frames, arg3);
}

void mstory5_ObjRotMoveV(omObjData *obj, const Vec *target, s32 frames) {
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

void mstory5_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory5_ObjRotMoveV(obj, &pos, frames);
}

void mstory5_MotionEndWait(s16 model) {
    HuPrcSleep(10);
    while (!mstory5_MotionEndCheck(model)) {
        HuPrcVSleep();
    }
}

s32 mstory5_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void mstory5_ObjForwardMove(omObjData *obj, f32 speed, s16 frames) {
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

void mstory5_ObjPosMoveAccelXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 faceDir) {
    Vec start;
    Vec diff;
    Vec vel;
    Vec pos;
    Vec accel;
    Vec target;
    s16 model;
    f32 t;

    target.x = x;
    target.y = y;
    target.z = z;
    model = obj->model[1];
    start.x = Hu3DData[model].pos.x;
    start.y = Hu3DData[model].pos.y;
    start.z = Hu3DData[model].pos.z;
    diff.x = target.x - start.x;
    diff.y = target.y - start.y;
    diff.z = target.z - start.z;
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
        if (pos.x <= target.x) {
            pos.x = target.x;
            pos.y = target.y;
            pos.z = target.z;
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
    Hu3DModelPosSet(model, target.x, target.y, target.z);
    if (obj->model[2] >= 0) {
        Hu3DModelPosSet(obj->model[2], target.x, target.y - 5.0f, target.z);
    }
    HuPrcVSleep();
}

const s32 mstory5_stampSprFileTbl[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };

const s16 mstory5_stampPosTbl[7][2] = {
    { 57, 20 },
    { 129, 36 },
    { 200, 22 },
    { 215, 91 },
    { 150, 124 },
    { 81, 105 },
    { 12, 122 },
};
