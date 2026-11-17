#include "common.h"
#include "game/hmfmath.h"

extern f32 CFanOfs;
extern f32 CFanLen;

extern s16 mstory1_winId;
extern s16 mstory1_backMdl;
extern u16 mstory1_backSpr;
extern s32 mstory1_padNo;
extern s32 mstory1_stampNo;
extern s16 mstory1_stampCardSprTbl[8];
extern s16 mstory1_stampSparkSprTbl[8];
extern s16 mstory1_stampFadeSpr;
extern const s32 mstory1_stampSprFileTbl[7];
extern const s16 mstory1_stampPosTbl[][2];

s32 mstory1_sceneState = 0;
s32 mstory1_skipOnF = 0;
s8 mstory1_exitF = 0;
Vec mstory1_cameraPos = { 14.0f, 193.0f, 1400.0f };
Vec mstory1_cameraTarget = { -25.0f, 0.0f, -650.0f };
Vec mstory1_cameraUp = { 0.0f, 1.0f, -0.0001f };
s32 mstory1_stampCardDoneF = 0;

void mstory1_StampCardProc(void);
void mstory1_StampCardDestroy(void);
void mstory1_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames);
void mstory1_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void mstory1_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void mstory1_ObjRotMoveV(omObjData *obj, const Vec *pos, s32 frames);
s32 mstory1_MotionEndCheck(s16 model);
void mstory1_WinCreate(void);

void mstory1_SceneObjMain(omObjData *obj) {
    u32 state = mstory1_sceneState;
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
            if (mstory1_skipOnF == 1) {
                btn = HuPadBtnDown[mstory1_padNo] & START_BUTTON;
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
    mstory1_sceneState = state;
}

void mstory1_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mstory1_exitF == 0) {
            WipeCreateOut(WIPE_STARS, 20);
            HuAudSeqFadeOut(30);
            mstory1_exitF = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void mstory1_BackCreate(void) {
    mstory1_backSpr = espEntry(HuSprAnimDataRead(0x1D0012), 0, 0);
    espPosSet(mstory1_backSpr, 160, 120);
    espAttrSet(mstory1_backSpr, 0x4000);
    mstory1_backMdl = Hu3DModelRead(0x1D0014, 0x2B9);
    Hu3DModelPosSet(mstory1_backMdl, 591.7f, -81.0f, -1305.7f);
    Hu3DMotionAttrSet(mstory1_backMdl, 2, 0);
    Hu3DMotionAttrSet(mstory1_backMdl, 1, 1);
}

void mstory1_BackDispOff(void) {
    Hu3DModelAttrSet(mstory1_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(mstory1_backSpr);
}

void mstory1_BackDispOn(void) {
    Hu3DModelAttrSet(mstory1_backMdl, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(mstory1_backSpr);
}

void mstory1_CameraObjMain(omObjData *obj) {
    CFanParam[0] = mstory1_cameraPos.x;
    CFanParam[1] = mstory1_cameraPos.z;
    CFanParam[-1] = 0.0f;
    CFanParam[2] = 35.0f;
    CFanParam[3] = CFanLen;
    CFanParam[4] = CFanOfs;
    Hu3DCameraPosSetV(0, &mstory1_cameraPos, &mstory1_cameraTarget, &mstory1_cameraUp);
    Hu3DCamUpdateMtx(0);
}

void mstory1_SceneEnd(void) {
    mstory1_sceneState = 3;
}

void mstory1_StampCardStart(s32 arg0) {
    mstory1_stampNo = arg0;
    mstory1_stampCardDoneF = 0;
    omAddPrcObj(mstory1_StampCardProc, 0x1000, 0x800, 0);
}

void mstory1_StampCardProc(void) {
    void *data;
    f32 x;
    f32 y;
    f32 angle;
    f32 tpLvl;
    s32 i;
    s32 j;

    mstory1_stampCardSprTbl[0] = espEntry(HuSprAnimDataRead(0x1D0001), 0, 0);
    espPosSet(mstory1_stampCardSprTbl[0], 160, 120);
    espDispOff(mstory1_stampCardSprTbl[0]);
    for (i = 0; i < 7; i++) {
        mstory1_stampCardSprTbl[i + 1] = espEntry(HuSprAnimDataRead(mstory1_stampSprFileTbl[i]), 0, 0);
        espPosSet(mstory1_stampCardSprTbl[i + 1], mstory1_stampPosTbl[i][0] + 48, mstory1_stampPosTbl[i][1] + 48);
        espAttrSet(mstory1_stampCardSprTbl[i + 1], 8);
        espDispOff(mstory1_stampCardSprTbl[i + 1]);
    }
    data = DataRead(0x1D0002);
    for (i = 0; i < 8; i++) {
        mstory1_stampSparkSprTbl[i] = espEntry(HuSprAnimRead(data), 0, 1);
        x = mstory1_stampPosTbl[mstory1_stampNo][0] + 48;
        y = mstory1_stampPosTbl[mstory1_stampNo][1] + 48;
        angle = i * 45.0f;
        x += cosdf(angle) * 32.0f;
        y -= sindf(angle) * 32.0f;
        espPosSet(mstory1_stampSparkSprTbl[i], x, y);
        espAttrSet(mstory1_stampSparkSprTbl[i], 0x1000);
        espColorSet(mstory1_stampSparkSprTbl[i], 255, 255, 192);
        espAttrSet(mstory1_stampSparkSprTbl[i], 8);
        espScaleSet(mstory1_stampSparkSprTbl[i], 1.5f, 1.5f);
        espTPLvlSet(mstory1_stampSparkSprTbl[i], 255);
        espDispOff(mstory1_stampSparkSprTbl[i]);
    }
    HuMemMemoryFreePerm(data);
    mstory1_stampFadeSpr = espEntry(HuSprAnimDataRead(0x1D0000), 0, 0);
    espPosSet(mstory1_stampFadeSpr, 160, 120);
    espScaleSet(mstory1_stampFadeSpr, 40.0f, 30.0f);
    espAttrSet(mstory1_stampFadeSpr, 0);
    espDispOff(mstory1_stampFadeSpr);
    omPrcSetDestructor(0, mstory1_StampCardDestroy);
    espDispOn(mstory1_stampFadeSpr);
    espTPLvlSet(mstory1_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory1_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory1_stampFadeSpr, 256);
    for (i = 0; i < mstory1_stampNo; i++) {
        espDispOn(mstory1_stampCardSprTbl[i + 1]);
    }
    mstory1_BackDispOff();
    espDispOn(mstory1_stampCardSprTbl[0]);
    HuPrcSleep(30);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory1_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory1_stampFadeSpr);
    espTPLvlSet(mstory1_stampCardSprTbl[mstory1_stampNo + 1], 0);
    espDispOn(mstory1_stampCardSprTbl[mstory1_stampNo + 1]);
    for (j = 0, tpLvl = 0.0f; j < 20; j++) {
        tpLvl += 12.75f;
        espTPLvlSet(mstory1_stampCardSprTbl[mstory1_stampNo + 1], tpLvl);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory1_stampCardSprTbl[mstory1_stampNo + 1], 255);
    espScaleSet(mstory1_stampCardSprTbl[mstory1_stampNo + 1], 1.0f, 1.0f);
    HuAudFXPlay(0x131);
    for (i = 0; i < 8; i++) {
        espBankSet(mstory1_stampSparkSprTbl[i], 0, 0);
        espAnimModeSet(mstory1_stampSparkSprTbl[i], 1);
        espDispOn(mstory1_stampSparkSprTbl[i]);
    }
    HuPrcSleep(20);
    for (i = 0; i < 8; i++) {
        espDispOff(mstory1_stampSparkSprTbl[i]);
    }
    if (mstory1_stampNo == 6) {
        HuPrcSleep(40);
        espDispOn(mstory1_stampFadeSpr);
        espTPLvlSet(mstory1_stampFadeSpr, 0);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory1_stampFadeSpr, i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espTPLvlSet(mstory1_stampFadeSpr, 256);
        HuPrcSleep(3);
        for (i = 0; i < 5; i++) {
            espTPLvlSet(mstory1_stampFadeSpr, 255.0f - i * (1.0f / 8.0f) * 255.0f);
            HuPrcVSleep();
        }
        espDispOff(mstory1_stampFadeSpr);
        HuPrcSleep(80);
    } else {
        HuPrcSleep(60);
    }
    espDispOn(mstory1_stampFadeSpr);
    espTPLvlSet(mstory1_stampFadeSpr, 0);
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory1_stampFadeSpr, i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espTPLvlSet(mstory1_stampFadeSpr, 256);
    espDispOff(mstory1_stampCardSprTbl[mstory1_stampNo + 1]);
    espDispOff(mstory1_stampCardSprTbl[0]);
    mstory1_BackDispOn();
    HuPrcSleep(30);
    for (i = 0; i < mstory1_stampNo; i++) {
        espDispOff(mstory1_stampCardSprTbl[i + 1]);
    }
    for (i = 0; i < 20; i++) {
        espTPLvlSet(mstory1_stampFadeSpr, 255.0f - i * (1.0f / 20.0f) * 255.0f);
        HuPrcVSleep();
    }
    espDispOff(mstory1_stampFadeSpr);
    mstory1_stampCardDoneF = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

s32 mstory1_StampCardDoneCheck(void) {
    return mstory1_stampCardDoneF;
}

void mstory1_StampCardDestroy(void) {
}

void mstory1_StampCardClose(void) {
}

void mstory1_HmfAnimSet(s16 model, s16 animSlot, s16 anim) {
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

void mstory1_WinCreate(void) {
    mstory1_winId = HuWinExCreateStyled(160, 194, 20);
    HuWinActivePlayerSet(mstory1_winId, 1 << mstory1_padNo);
    HuWinInsertMesSet(mstory1_winId, GwStory.unk1 + 0x1C00, 0);
}

void mstory1_WinOpen(void) {
    HuWinHomeClear(mstory1_winId);
    HuWinExOpen(mstory1_winId, 1);
}

void mstory1_WinClose(void) {
    HuWinExClose(mstory1_winId, 1);
}

void mstory1_WinMesExec(s32 mess) {
    HuWinMesSet(mstory1_winId, mess, -1, -1);
    while (HuWinStatGet(mstory1_winId) != 0) {
        HuPrcVSleep();
    }
}

void mstory1_WinMesSet(s32 mess) {
    HuWinMesSet(mstory1_winId, mess, -1, -1);
}

void mstory1_WinMesWait(void) {
    while (HuWinStatGet(mstory1_winId) != 0) {
        HuPrcVSleep();
    }
}

s32 mstory1_PlayerChrCheck(s32 character) {
    return -(character == GwStory.unk1);
}

void mstory1_ObjPosMoveV(omObjData *obj, const Vec *pos, s32 frames) {
    mstory1_ObjPosMoveEx(obj, pos, frames, 1);
}

void mstory1_ObjPosMoveEx(omObjData *obj, const Vec *pos, s32 frames, s32 arg3) {
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

void mstory1_ObjLinkPosMoveV(omObjData *obj, Vec *pos, s32 frames) {
    mstory1_ObjLinkPosMoveEx(obj, pos, frames, 1);
}

void mstory1_ObjLinkPosMoveEx(omObjData *obj, Vec *pos, s32 frames, s32 arg3) {
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

void mstory1_ObjPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory1_ObjPosMoveV(obj, &pos, frames);
}

void mstory1_ObjPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory1_ObjPosMoveEx(obj, &pos, frames, arg3);
}

void mstory1_ObjLinkPosMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory1_ObjLinkPosMoveV(obj, &pos, frames);
}

void mstory1_ObjLinkPosMoveExXYZ(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory1_ObjLinkPosMoveEx(obj, &pos, frames, arg3);
}

void mstory1_ObjRotMoveV(omObjData *obj, const Vec *target, s32 frames) {
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

void mstory1_ObjRotMove(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    mstory1_ObjRotMoveV(obj, &pos, frames);
}

void mstory1_MotionEndWait(s16 model) {
    HuPrcSleep(10);
    while (!mstory1_MotionEndCheck(model)) {
        HuPrcVSleep();
    }
}

s32 mstory1_MotionEndCheck(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && Hu3DMotion[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

void mstory1_ObjForwardMove(omObjData *obj, f32 speed, s16 frames) {
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

const s32 mstory1_stampSprFileTbl[7] = { 0x1D000B, 0x1D000C, 0x1D000D, 0x1D000E, 0x1D000F, 0x1D0010, 0x1D0011 };

const s16 mstory1_stampPosTbl[][2] = {
    { 57, 20 },
    { 129, 36 },
    { 200, 22 },
    { 215, 91 },
    { 150, 124 },
    { 81, 105 },
    { 12, 122 },
};

const s32 mstory1_stampPosPad[3] = { 0 }; /* Unreferenced. */
