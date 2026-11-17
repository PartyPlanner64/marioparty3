#include "common.h"
#include "game/hmfmath.h"

extern f32 CFanOfs;
extern f32 CFanLen;

extern s16 mstory4_winId;
extern s16 mstory4_backMdl;
extern s32 mstory4_padNo;
extern u16 mstory4_backSpr;
extern s32 mstory4_stampNo;
extern s16 mstory4_stampCardSprTbl[8];
extern s16 mstory4_stampSparkSprTbl[7][8];
extern s16 mstory4_stampFadeSpr;
extern const s32 mstory4_stampSprFileTbl[7];
extern const s16 mstory4_stampPosTbl[][2];
extern s32 mstory4_playerOrderTbl[4];
extern void (*const mstory4_sceneCreateTbl[])(void);
extern const s32 mstory4_sceneFlagTbl[];

s32 mstory4_sceneState = 0;
s32 mstory4_mbdBackF = 0;
s32 mstory4_skipOnF = 0;
s8 mstory4_exitF = 0;
Vec mstory4_cameraPos = { 14.0f, 193.0f, 1400.0f };
Vec mstory4_cameraTarget = { -25.0f, 0.0f, -650.0f };
Vec mstory4_cameraUp = { 0.0f, 1.0f, -0.0001f };
s32 mstory4_stampCardDoneF = 0;

void mstory4_Scene0Create(void);
void mstory4_Scene1Create(void);
void MBDBackKill(void);
void MBDBackClose(void);
void mstory4_StampCardProc(void);
void mstory4_StampCardDestroy(void);
void mstory4_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory4_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory4_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void mstory4_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
s32 mstory4_MotionEndCheck(s16 model);
void mstory4_SceneObjMain(omObjData *obj);
void mstory4_ExitObjMain(omObjData *obj);
void mstory4_BackCreate(void);
void mstory4_CameraObjMain(omObjData *obj);
void mstory4_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames);

void mstory4_ObjectSetup(void) {
    omObjData *obj;
    s16 chapter;
    s16 count = 0;
    s16 group;
    s16 i;

    for (group = 0; group < 4; group++) {
        for (i = 0; i < 4; i++) {
            if (group == GwPlayer[i].group) {
                mstory4_playerOrderTbl[count] = i;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }
    Hu3DSprModelInit(60);
    omInitObjMan(30, 30);
    HuWinInit();
    CamSetupInit(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 35.0f, 80.0f, 8000.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    obj = omAddObj(0x7FDA, 0, 0, -1, mstory4_CameraObjMain);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    mstory4_CameraObjMain(obj);
    omAddObj(0, 0, 0, -1, mstory4_SceneObjMain);
    omAddObj(0, 0, 0, -1, mstory4_ExitObjMain);
    mstory4_BackCreate();
    for (mstory4_padNo = 0; mstory4_padNo < 4; mstory4_padNo++) {
        if (CheckControllerRead(mstory4_padNo)) {
            break;
        }
    }
    if (mstory4_padNo >= 4) {
        mstory4_padNo = 0;
    }
    chapter = GwPlayer[0].coin;
    if (GwPlayer[0].coin >= 2) {
        chapter = 1;
    }
    mstory4_sceneCreateTbl[chapter]();
    if (_CheckFlag(mstory4_sceneFlagTbl[chapter])) {
        mstory4_skipOnF = 1;
    } else {
        _SetFlag(mstory4_sceneFlagTbl[chapter]);
    }
    WipeCreateIn(WIPE_STARS, 16);
}

void (*const mstory4_sceneCreateTbl[])(void) = { mstory4_Scene0Create, mstory4_Scene1Create };

const s32 mstory4_sceneFlagTbl[] = { 62, 63 };

void mstory4_SceneObjMain(omObjData *obj) {
    u32 state = mstory4_sceneState;
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
            if (mstory4_skipOnF == 1) {
                btn = HuPadBtnDown[mstory4_padNo] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(WIPE_STARS, 20);
            } else {
                WipeCreateOut(WIPE_FADE, 20);
            }
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                if (mstory4_mbdBackF == 1) {
                    MBDBackKill();
                    MBDBackClose();
                }
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    mstory4_sceneState = state;
}

void mstory4_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mstory4_exitF == 0) {
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(WIPE_STARS, 20);
            } else {
                WipeCreateOut(WIPE_FADE, 20);
            }
            mstory4_exitF = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            if (mstory4_mbdBackF == 1) {
                MBDBackKill();
                MBDBackClose();
            }
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void mstory4_BackMotionStart(void) {
    Hu3DMotionAttrSet(mstory4_backMdl, 4, 0);
    Hu3DMotionAttrSet(mstory4_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory4_backMdl, 0.0f);
    HuAudFXPlay(0x217);
}

void mstory4_BackMotionReverse(void) {
    Hu3DMotionAttrSet(mstory4_backMdl, 4, 4);
    Hu3DMotionAttrSet(mstory4_backMdl, 1, 0);
    Hu3DMotionTimeSet(mstory4_backMdl, Hu3DMotion[Hu3DData[mstory4_backMdl].motId].unk02);
}

void mstory4_BackCreate(void) {
    mstory4_backSpr = espEntry(HuSprAnimDataRead(0x1D0012), 0, 0);
    espPosSet(mstory4_backSpr, 160, 120);
    espAttrSet(mstory4_backSpr, HUSPR_ATTR_BG);
    mstory4_backMdl = Hu3DModelRead(0x1D0014, 0x2B9);
    Hu3DModelPosSet(mstory4_backMdl, 591.7f, -81.0f, -1305.7f);
    Hu3DMotionAttrSet(mstory4_backMdl, 2, 0);
    Hu3DMotionAttrSet(mstory4_backMdl, 1, 1);
}

void mstory4_BackDispOff(void) {
    Hu3DModelAttrSet(mstory4_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(mstory4_backSpr);
}

void mstory4_BackDispOn(void) {
    Hu3DModelAttrSet(mstory4_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(mstory4_backSpr);
}

void mstory4_CameraObjMain(omObjData *obj) {
    CFanParam[0] = mstory4_cameraPos.x;
    CFanParam[1] = mstory4_cameraPos.z;
    CFanParam[-1] = 0.0f;
    CFanParam[2] = 35.0f;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &mstory4_cameraPos, &mstory4_cameraTarget, &mstory4_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void mstory4_SceneEnd(void) {
    mstory4_sceneState = 3;
}

void mstory4_StampCardStart(s32 arg0) {
    mstory4_stampNo = arg0;
    mstory4_stampCardDoneF = 0;
    omAddPrcObj(mstory4_StampCardProc, 0x1000, 0x800, 0);
}

void mstory4_StampCardProc(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;
    s32 k;

    mstory4_stampCardSprTbl[0] = espEntry(HuSprAnimDataRead(0x1D0001), 0, 0);
    espPosSet(mstory4_stampCardSprTbl[0], 160, 120);
    espDispOff(mstory4_stampCardSprTbl[0]);
    for (i = 0; i < 7; i++) {
        mstory4_stampCardSprTbl[i + 1] = espEntry(HuSprAnimDataRead(mstory4_stampSprFileTbl[i]), 0, 0);
        espPosSet(mstory4_stampCardSprTbl[i + 1], mstory4_stampPosTbl[i][0] + 48, mstory4_stampPosTbl[i][1] + 48);
        espAttrSet(mstory4_stampCardSprTbl[i + 1], HUSPR_ATTR_FILTER_BILERP);
        espDispOff(mstory4_stampCardSprTbl[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            mstory4_stampSparkSprTbl[j][i] = espEntry(HuSprAnimRead(data), 0, 1);
            x = mstory4_stampPosTbl[j][0] + 48;
            y = mstory4_stampPosTbl[j][1] + 48;
            angle = i * 45.0f;
            x += cosdf(angle) * 32.0f;
            y -= sindf(angle) * 32.0f;
            espPosSet(mstory4_stampSparkSprTbl[j][i], x, y);
            espAttrSet(mstory4_stampSparkSprTbl[j][i], HUSPR_ATTR_XLU);
            espColorSet(mstory4_stampSparkSprTbl[j][i], 255, 255, 192);
            espAttrSet(mstory4_stampSparkSprTbl[j][i], HUSPR_ATTR_FILTER_BILERP);
            espScaleSet(mstory4_stampSparkSprTbl[j][i], 1.5f, 1.5f);
            espTPLvlSet(mstory4_stampSparkSprTbl[j][i], 255);
            espDispOff(mstory4_stampSparkSprTbl[j][i]);
        }
    }
    HuMemMemoryFreePerm(data);
    mstory4_stampFadeSpr = espEntry(HuSprAnimDataRead(0x1D0000), 0, 0);
    espPosSet(mstory4_stampFadeSpr, 160, 120);
    espScaleSet(mstory4_stampFadeSpr, 40.0f, 30.0f);
    espAttrSet(mstory4_stampFadeSpr, HUSPR_ATTR_NONE);
    espDispOff(mstory4_stampFadeSpr);
    omPrcSetDestructor(0, mstory4_StampCardDestroy);
    espDispOn(mstory4_stampFadeSpr);
    espTPLvlSet(mstory4_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory4_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory4_stampFadeSpr, 256);
    for (i = 0; i < mstory4_stampNo; i++) {
        espDispOn(mstory4_stampCardSprTbl[i + 1]);
    }
    mstory4_BackDispOff();
    espDispOn(mstory4_stampCardSprTbl[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory4_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory4_stampFadeSpr);
    espTPLvlSet(mstory4_stampCardSprTbl[mstory4_stampNo + 1], 0);
    espDispOn(mstory4_stampCardSprTbl[mstory4_stampNo + 1]);
    for (k = 0, tpLvl = 0.0f; k < 20; k++) {
        tpLvl += 12.75f;
        espTPLvlSet(mstory4_stampCardSprTbl[mstory4_stampNo + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory4_stampCardSprTbl[mstory4_stampNo + 1], 255);
    espScaleSet(mstory4_stampCardSprTbl[mstory4_stampNo + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(mstory4_stampSparkSprTbl[mstory4_stampNo][i], 0, 0);
        espAnimModeSet(mstory4_stampSparkSprTbl[mstory4_stampNo][i], 1);
        espDispOn(mstory4_stampSparkSprTbl[mstory4_stampNo][i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(mstory4_stampSparkSprTbl[mstory4_stampNo][i]);
    }
    HuPrcSleep(30);
    HuAudFXPlay(0x131);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            espBankSet(mstory4_stampSparkSprTbl[j][i], 0, 0);
            espAnimModeSet(mstory4_stampSparkSprTbl[j][i], 1);
            espDispOn(mstory4_stampSparkSprTbl[j][i]);
        }
    }
    HuPrcSleep(20);
    for (j = 0; j < 7; j++) {
        for (i = 0; i < 8; i++) {
            espDispOff(mstory4_stampSparkSprTbl[j][i]);
        }
    }
    if (mstory4_stampNo != 6) {
        HuPrcSleep(60);
    } else {
        HuPrcSleep(40);
        HuAudFXPlay(0x221);
        for (j = 0; j < 2; j++) {
            espDispOn(mstory4_stampFadeSpr);
            espTPLvlSet(mstory4_stampFadeSpr, 0);
            for (i = 0; i < 7; i++) {
                espTPLvlSet(mstory4_stampFadeSpr, i * (1.0f / 7.0f) * 255.0f);
                HuPrcVSleep();
            }
            espTPLvlSet(mstory4_stampFadeSpr, 256);
            HuPrcSleep(3);
            for (i = 0; i < 7; i++) {
                espTPLvlSet(mstory4_stampFadeSpr, 255.0f - i * (1.0f / 7.0f) * 255.0f);
                HuPrcVSleep();
            }
            espDispOff(mstory4_stampFadeSpr);
            HuPrcSleep(5);
        }
    }
    espDispOn(mstory4_stampFadeSpr);
    espTPLvlSet(mstory4_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory4_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory4_stampFadeSpr, 256);
    espDispOff(mstory4_stampCardSprTbl[mstory4_stampNo + 1]);
    espDispOff(mstory4_stampCardSprTbl[0]);
    mstory4_BackDispOn();
    HuPrcSleep(30);
    for (i = 0; i < mstory4_stampNo; i++) {
        espDispOff(mstory4_stampCardSprTbl[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory4_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory4_stampFadeSpr);
    mstory4_stampCardDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 mstory4_StampCardDoneCheck(void) {
    return mstory4_stampCardDoneF;
}

void mstory4_StampCardDestroy(void) {
}

void mstory4_StampCardClose(void) {
}

void mstory4_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
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

void mstory4_WinCreate(void) {
    mstory4_winId = HuWinExCreateStyled(160, 194, 20);
    HuWinActivePlayerSet(mstory4_winId, 1 << mstory4_padNo);
    HuWinInsertMesSet(mstory4_winId, GwStory.unk1 + 0x1C00, 0);
}

void mstory4_WinOpen(void) {
    HuWinHomeClear(mstory4_winId);
    HuWinExOpen(mstory4_winId, 1);
}

void mstory4_WinClose(void) {
    HuWinExClose(mstory4_winId, 1);
}

void mstory4_WinMesExec(s32 mess) {
    HuWinMesSet(mstory4_winId, mess, -1, -1);
    while (HuWinStatGet(mstory4_winId) != 0) {
        HuPrcVSleep();
    }
}

void mstory4_WinMesSet(s32 mess) {
    HuWinMesSet(mstory4_winId, mess, -1, -1);
}

void mstory4_WinMesWait(void) {
    while (HuWinStatGet(mstory4_winId) != 0) {
        HuPrcVSleep();
    }
}

s32 mstory4_PlayerChrCheck(s32 character) {
    return -(character == GwStory.unk1);
}

void mstory4_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames) {
    mstory4_ObjPosMoveEx(obj, pos, frames, 1);
}

void mstory4_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void mstory4_ObjLinkPosMoveV(omObjData *obj, Vec *pos, s32 frames) {
    mstory4_ObjLinkPosMoveEx(obj, pos, frames, 1);
}

void mstory4_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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

void mstory4_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory4_ObjPosMoveV(obj, &pos, frames);
}

void mstory4_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory4_ObjPosMoveEx(obj, &pos, frames, arg3);
}

void mstory4_ObjLinkPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory4_ObjLinkPosMoveV(obj, &pos, frames);
}

void mstory4_ObjLinkPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory4_ObjLinkPosMoveEx(obj, &pos, frames, arg3);
}

void mstory4_ObjRotMoveV(omObjData *obj, const Vec *target, s32 frames) {
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

void mstory4_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory4_ObjRotMoveV(obj, &pos, frames);
}

void mstory4_MotionEndWait(s16 model) {
    HuPrcSleep(10);
    while (!mstory4_MotionEndCheck(model)) {
        HuPrcVSleep();
    }
}

s32 mstory4_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

const s32 mstory4_stampSprFileTbl[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };

const s16 mstory4_stampPosTbl[][2] = {
    { 57, 20 },
    { 129, 36 },
    { 200, 22 },
    { 215, 91 },
    { 150, 124 },
    { 81, 105 },
    { 12, 122 },
};
