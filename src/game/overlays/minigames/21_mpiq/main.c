#include "common.h"
#include "math.h"
#include "game/printfunc.h"
#include "game/mallocblock.h"
#include "game/messdata.h"
#include "game/esprite.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "gcc/memory.h"
#include "game/window.h"
#include "game/overlays/minigame.h"

// Work for the buzzer blocks above each player, allocated in m233_BlockCreateAll
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ u32 flags;
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 index;
    /* 0x1C */ f32 scale;
    /* 0x20 */ s32 counter;
    /* 0x24 */ s16 unk_24;
} MpiqBlockWork; // Size 0x28

typedef struct {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 rotY;
    /* 0x0C */ s32 flags;
} MpiqHostWork; // Size 0x10

// CPU input timing for each player, set up in m233_ComInputSet
typedef struct {
    /* 0x00 */ s32 delay;
    /* 0x04 */ s32 hold;
    /* 0x08 */ u16 button;
} MpiqComInput; // Size 0xC

// Data of the objects registered in mgMapObjTbl
typedef struct {
    /* 0x00 */ MgMapWork header;
    /* 0xB0 */ void *unkB0;
} MpiqStageData; // Size 0xB4

// Work for the meter objects created in m233_MeterCreateAll
typedef struct {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 x;
    /* 0x0C */ char unk_0C[0xC];
    /* 0x18 */ f32 posY[4]; // [0] is the base model, [1..3] are the bars
    /* 0x28 */ f32 barScale[3];
    /* 0x34 */ char unk_34[4];
    /* 0x38 */ s32 stage;
    /* 0x3C */ s32 flags;
    /* 0x40 */ s32 index;
} MpiqMeterWork; // Size 0x44

// Work for the A/B/C choice sign object created in m233_ChoiceCreate
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ s32 flags;
    /* 0x0C */ f32 scale;
} MpiqChoiceWork; // Size 0x10

// Work for the stun effect object created in m233_StunCreate
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 timer;
} MpiqStunWork; // Size 0x8

// Sprite IDs for the A/B/C choice images created in m233_ChoiceCreate
typedef struct {
    /* 0x00 */ u16 espIds[3];
    /* 0x06 */ s16 imageIds[3];
} MpiqChoiceSpr; // Size 0xC

extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;

MinigameFlow m233_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_NONE, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    60, 900, -1, 75, 135
};
f32 m233_playerScreenXTbl[4] = { 64.0f, 128.0f, 192.0f, 256.0f };
s32 m233_choiceNo = -1;
s32 m233_insertAnswerTbl[17] = { 5, 5, 5, 5, 5, 5, 10, 10, 10, 10, 10, 10, 10, 10, 20, 30, 0 };

f32 m233_stageScale BSS;
s32 m233_cameraNo BSS;
u8 m233_setupF BSS;
s16 m233_setupCnt BSS;
s32 m233_answerPlayer BSS;
s16 m233_quizFlag BSS;
s16 m233_buzzLockF BSS;
u8 m233_buzzLockPad[4] BSS; /* Unreferenced. */
s32 m233_scoreTbl[4] BSS;
s32 m233_winner BSS;
u16 m233_judgeSprTbl[2] BSS;
u16 m233_logoSpr BSS;
u16 m233_logoBackSpr BSS;
u8 m233_logoBackSprPad[4] BSS; /* Unreferenced. */
s32 m233_playerFlagTbl[4] BSS;
s32 m233_endlessF BSS;
s32 m233_questionNoBase BSS;
s16 m233_questionWin BSS;
u8 m233_questionWinPad[4] BSS; /* Unreferenced. */
MpiqComInput m233_comInputTbl[4] BSS;
s16 m233_correctChoiceTbl[10] BSS;
s16 m233_questionNo BSS;
s32 m233_questionMesTbl[10] BSS;
omObjData *m233_hostObj BSS;
u8 m233_hostObjPad[4] BSS; /* Unreferenced. */
omObjData *m233_standObjTbl[4] BSS;
s32 m233_standFlagTbl[4] BSS;
s32 m233_standLevelTbl[4] BSS;
f32 m233_standHeightTbl[4] BSS;
omObjData *m233_blockObjTbl[4] BSS;
omObjData *m233_hitEffObj BSS;
omObjData *m233_stunObj BSS;
omObjData *m233_meterObjTbl[4] BSS;
omObjData *m233_choiceObj BSS;
MpiqChoiceSpr m233_choiceSpr BSS;
s32 m233_countdown BSS;
s16 m233_questionWinNo BSS;
s32 m233_choiceTbl[10][4] BSS;
s16 m233_questionFlagTbl[12] BSS;
s16 m233_insertMesTbl[10] BSS;
s32 m233_boardPickCnt BSS;
s32 m233_choiceUnitMesTbl[10] BSS;
s32 m233_boardPickTbl[1] BSS;
s32 m233_boardPickWrongTbl[2] BSS;
s32 m233_boardPickNo BSS;
u8 m233_boardPickPad[8] BSS; /* Unreferenced. */
s32 m233_answerBuf[256] BSS;
s32 m233_answerValue BSS;
u8 m233_answerValuePad[12] BSS; /* Unreferenced. */
s32 m233_endlessQuestionNo BSS;

// Aliases into the variables above, see undefined_syms.txt.
extern s16 m233_answerPlayerS16;
extern u16 m233_choiceSprTbl[3];
extern s16 m233_choiceSprAnimTbl[3];
extern s16 m233_countdownS16;

void m233_MainObjMain(omObjData *obj);
void m233_ExitObjMain(omObjData *obj);
void m233_Player0ObjInit(omObjData *obj);
void m233_Player1ObjInit(omObjData *obj);
void m233_Player2ObjInit(omObjData *obj);
void m233_Player3ObjInit(omObjData *obj);
void m233_PlayerInit(omObjData *obj, s32 index);
void m233_PlayerObjMain(omObjData *obj);
s32 m233_BuzzLockGet(void);
void m233_StageCreate(void);
void m233_LogoPulseCreate(void);
void m233_LogoInProc(void);
void m233_StandCreateAll(void);
void m233_StandObjMain(omObjData *obj);
void m233_BlockCreateAll(void);
void m233_BlockObjMain(omObjData *obj);
void m233_HitEffCreate(void);
void m233_HitEffObjMain(omObjData *obj);
void m233_HitEffStart(f32 x, f32 y, f32 z);
void m233_StunCreate(void);
void m233_StunObjMain(omObjData *obj);
void m233_MeterCreateAll(void);
void m233_MeterObjMain(omObjData *obj);
void m233_HostCreate(void);
void m233_HostObjMain(omObjData *obj);
void m233_CameraInit(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void m233_ChoiceCreate(void);
s16 m233_ObjHitCheck(omObjData *objA, omObjData *objB);
void m233_ComInputProc(void);
void m233_ChoiceObjMain(omObjData *obj);
void m233_ChoiceSelectProc(void);
void m233_QuestionTblCreate(void);
s32 m233_PlayerOnStandCheck(s32 index);
s32 m233_QuestionCheck(s32 index, s32 question);
void m233_QuestionInsertSet(s32 index);
void m233_AnswerCalc(s32 index);
s16 m233_ChoiceGet(s32 index, s32 answer);
s32 m233_ChoiceChrGet(s32 index);
s32 m233_ChoiceNumGet(s32 index, s32 range, s32 base, s32 scale);
void m233_QuizProc(void);
void m233_WinPauseObjMain(omObjData *obj);
s16 m233_QuestionWinCreate(void);
void m233_CountdownProc(void);
void m233_BuzzObjMain(omObjData *obj);
s16 m233_ChoiceWinCreate(void);

void m233_ObjectSetup(void) {
    omObjData *obj;

    omInitObjMan(40, 20);
    MapCollInit(16);
    Hu3DQuadPoolInit(&mgQuadPool, 64);
    Hu3DSprModelInit(64);
    HuAudCharVoiceInit();
    omGameSysInit();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m233_CameraInit(2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 420.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    MgFlowInit(&m233_mgFlow);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    mgMapObjNum = 0;
    mgPlayerObjNum = 0;
    MgPlayerParamReset();
    mgPlayerFallMax = 1.0f;
    m233_endlessF = 0;
    m233_endlessQuestionNo = 58;
    MgShadowAltSet(1);
    HuWinInit();
    m233_StageCreate();
    m233_StandCreateAll();
    m233_questionWin = -1;
    omSetStatBit(omAddObj(0x5000, 0, 0, -1, m233_WinPauseObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(4, 10, 60, -1, m233_Player0ObjInit);
    omAddObj(4, 10, 60, -1, m233_Player1ObjInit);
    omAddObj(4, 10, 60, -1, m233_Player2ObjInit);
    omAddObj(4, 10, 60, -1, m233_Player3ObjInit);
    m233_buzzLockF = 1;
    m233_ChoiceCreate();
    m233_questionNoBase = 0;
    m233_QuestionTblCreate();
    omAddPrcObj(m233_QuizProc, 0x5000, 0x1000, 0);
    m233_HostCreate();
    m233_MeterCreateAll();
    omAddPrcObj(m233_LogoInProc, 0x4700, 0x1000, 0);
    omAddObj(0x5000, 0, 0, -1, m233_MainObjMain);
    m233_BlockCreateAll();
    m233_HitEffCreate();
    m233_StunCreate();
    m233_setupF = 0;
    m233_setupCnt = 0;
    mgFieldStat = 0;
    mgFlowSeqNo = 49;
    mgFlowSeqTime = 60;
}

void m233_MainObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (MgFlowMain(obj)) {
        case 0:
        case 1:
        case 2:
        case 4:
            break;
        case 3:
            if (m233_winner != -1) {
                m233_mgFlow.resultType = MG_RESULT_WIN_1;
                m233_mgFlow.winners[0] = m233_winner;
            } else {
                m233_mgFlow.resultType = MG_RESULT_DRAW;
            }
            break;
        case 5:
            if (m233_winner != -1) {
                GwPlayer[m233_winner].bonusCoin += 10;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            obj->func = m233_ExitObjMain;
            break;
    }
}

void m233_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        GMesClose();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void m233_Player0ObjInit(omObjData *obj) {
    m233_PlayerInit(obj, 0);
}

void m233_Player1ObjInit(omObjData *obj) {
    m233_PlayerInit(obj, 1);
}

void m233_Player2ObjInit(omObjData *obj) {
    m233_PlayerInit(obj, 2);
}

void m233_Player3ObjInit(omObjData *obj) {
    m233_PlayerInit(obj, 3);
}

void m233_PlayerInit(omObjData *obj, s32 index) {
    Vec2f screenPos;
    Vec pos;
    s32 motion0[8] = { 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B };
    s32 motion1[8] = { 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B };
    s32 motion2[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
    s32 motion3[8] = { 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37 };
    s32 motion4[8] = { 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F };
    s32 motion5[8] = { 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C };
    s32 motion6[8] = { 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D };
    s32 motion7[8] = { 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E };
    s32 motion8[8] = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
    s32 motion9[8] = { 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A };
    s32 motion10[8] = { 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15 };
    s32 motion11[8] = { 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23 };
    MgPlayerWork *data;
    s32 chr;
    s32 model;
    s32 motion;
    s32 attr1;
    s32 attr2;

    mgPlayerObjTbl[mgPlayerObjNum++] = obj;
    model = omCharModelNoTbl[GwPlayer[index].chr][0];
    motion = omCharModelNoTbl[GwPlayer[index].chr][1];
    attr1 = 0x20AB9;
    attr2 = 0x20A99;
    MgPlayerCreate(obj, model, motion, index, attr1, attr2);
    data = obj->data;
    chr = GwPlayer[index].chr;
    MgPlayerMotLoad(obj, 0, CharMotionDataNumGet(chr, motion0[chr]), 1, 0);
    MgPlayerMotLoad(obj, 6, CharMotionDataNumGet(chr, motion1[chr]), 1, 19);
    MgPlayerMotLoad(obj, 21, CharMotionDataNumGet(chr, motion2[chr]), 0, 0);
    MgPlayerMotLoad(obj, 14, CharMotionDataNumGet(chr, motion3[chr]), 1, 120);
    MgPlayerMotLoad(obj, 13, CharMotionDataNumGet(chr, motion4[chr]), 1, 120);
    MgPlayerMotLoad(obj, 38, CharMotionDataNumGet(chr, motion5[chr]), 0, 0);
    MgPlayerMotLoad(obj, 39, CharMotionDataNumGet(chr, motion6[chr]), 0, 0);
    MgPlayerMotLoad(obj, 40, CharMotionDataNumGet(chr, motion7[chr]), 0, 0);
    MgPlayerMotLoad(obj, 41, CharMotionDataNumGet(chr, motion8[chr]), 0, 0);
    MgPlayerMotLoad(obj, 42, CharMotionDataNumGet(chr, motion9[chr]), 0, 0);
    MgPlayerMotLoad(obj, 43, CharMotionDataNumGet(chr, motion10[chr]), 1, 0);
    MgPlayerMotLoad(obj, 33, CharMotionDataNumGet(chr, motion11[chr]), 1, 0);
    screenPos.x = m233_playerScreenXTbl[index];
    screenPos.y = 180.0f;
    Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
    omSetTra(obj, pos.x, 0.0f, 0.0f);
    obj->trans.x = pos.x;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.y = 180.0f;
    MgPlayerMapAttrSet(obj, 0, 1);
    MgPlayerMapAttrSet(obj, 1, 2);
    MgPlayerMapAttrSet(obj, 2, 2);
    MgPlayerMapAttrSet(obj, 3, 2);
    MgPlayerMapAttrSet(obj, 4, 2);
    MgPlayerMotSet(obj, 0);
    m233_scoreTbl[index] = 0;
    m233_playerFlagTbl[index] = 0;
    data->unk104[2] = m233_BuzzLockGet;
    obj->func = m233_PlayerObjMain;
}

void m233_PlayerObjMain(omObjData *obj) {
    MgPlayerWork *data = obj->data;
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    HuPadStkX[data->unk57] = 0;
    HuPadStkY[data->unk57] = 0;
    if (m233_playerFlagTbl[data->unk59] & 1) {
        HuPadBtn[data->unk57] = 0;
        HuPadBtnDown[data->unk57] = 0;
    }
    if (m233_buzzLockF == 1 && !(GwPlayer[data->unk59].stat & 1)) {
        HuPadBtn[data->unk57] &= ~A_BUTTON;
        HuPadBtnDown[data->unk57] &= ~A_BUTTON;
    }
    MgPlayerObjMain(obj);
    data->unk60 = 0;
    obj->trans.x = x;
    obj->trans.z = z;
}

s32 m233_BuzzLockGet(void) {
    return m233_buzzLockF;
}

void m233_ComInputSet(s32 index) {
    u16 buttons[3] = { 0x8000, 0x4000, 0x2000 };
    s32 offset;
    s32 holdRange;
    s32 holdBase;
    s32 accuracy;
    void *mes;
    s32 base;
    s32 choice;
    s32 range;

    accuracy = 0;
    mes = MessDataMesGet((void *)m233_questionMesTbl[m233_questionNo]);
    base = HuWinStrLen(mes) * 5 - 40;
    holdBase = 0;
    holdRange = 0;
    offset = 0;
    range = 0;
    m233_comInputTbl[index].button = 0;
    switch (GwPlayer[index].cpu_difficulty) {
        case 0:
            range = 60;
            offset = 90;
            holdRange = 2;
            holdBase = 8;
            accuracy = 1;
            break;
        case 1:
            range = 75;
            offset = 60;
            holdRange = 6;
            holdBase = 4;
            accuracy = 3;
            break;
        case 2:
            range = 90;
            offset = 30;
            holdRange = 8;
            holdBase = 2;
            accuracy = 5;
            break;
        case 3:
            range = 105;
            offset = 0;
            holdRange = 9;
            holdBase = 1;
            accuracy = 8;
            break;
    }
    m233_comInputTbl[index].delay = base + offset + (rand8() % (range + 1) - (range >> 1));
    if (m233_comInputTbl[index].delay <= 30) {
        m233_comInputTbl[index].delay = 30;
    }
    m233_comInputTbl[index].hold = (rand8() % holdRange + holdBase) * 10;
    if ((u8)(rand8() % 10) == 0 ? accuracy >= 2 : accuracy > 0) {
        m233_comInputTbl[index].button = buttons[m233_correctChoiceTbl[m233_questionNo]];
    } else {
        choice = (u8)(rand8() % 3);
        if (choice == m233_correctChoiceTbl[m233_questionNo]) {
            choice = (choice + 1) % 3;
        }
        m233_comInputTbl[index].button = buttons[choice];
    }
    MessDataMesFree(mes);
}

void m233_ComInput(s32 index) {
    MgPlayerWork *data = mgPlayerObjTbl[index]->data;

    if (m233_playerFlagTbl[index] & 1) {
        return;
    }
    if (m233_buzzLockF == 0 && m233_comInputTbl[index].delay != 0) {
        m233_comInputTbl[index].delay--;
        if (m233_comInputTbl[index].delay == 0) {
            HuPadBtn[data->unk57] |= A_BUTTON;
            HuPadBtnDown[data->unk57] |= A_BUTTON;
        }
    } else if (index == m233_answerPlayer && m233_comInputTbl[index].hold != 0) {
        m233_comInputTbl[index].hold--;
        if (m233_comInputTbl[index].hold == 0) {
            HuPadBtn[data->unk57] |= m233_comInputTbl[index].button;
            HuPadBtnDown[data->unk57] |= m233_comInputTbl[index].button;
        }
    }
}

void m233_StageCreate(void) {
    omObjData *obj;
    MpiqStageData *work;
    u16 sprite;

    obj = omAddObj(5, 2, 0, -1, NULL);
    work = HuMemAllocTag(sizeof(MpiqStageData), TAG_OVERLAY);
    obj->data = work;
    obj->model[0] = 0;
    m233_stageScale = 1.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = obj;
    memset(obj->data, 0, sizeof(MpiqStageData));
    work->header.unk03 = 1;
    work->header.unk08 = 0.5f;
    work->header.unk04 = 0;

    sprite = espEntry(HuSprAnimDataRead(0x420000), 0, 1);
    espAttrSet(sprite, 0x4008);
    espPosSet(sprite, 160, 120);
    espDispOn(sprite);
    espScaleSet(sprite, 1.0f, 1.0f);
    espPriSet(sprite, 255);

    m233_judgeSprTbl[0] = espEntry(HuSprAnimDataRead(0x42000C), 0, 1);
    espAttrSet(m233_judgeSprTbl[0], 0x4008);
    espPosSet(m233_judgeSprTbl[0], 158, 86);
    espDispOff(m233_judgeSprTbl[0]);
    espScaleSet(m233_judgeSprTbl[0], 1.0f, 1.0f);
    espPriSet(m233_judgeSprTbl[0], 3);

    m233_judgeSprTbl[1] = espEntry(HuSprAnimDataRead(0x42000D), 0, 1);
    espAttrSet(m233_judgeSprTbl[1], 0x4008);
    espPosSet(m233_judgeSprTbl[1], 158, 86);
    espDispOff(m233_judgeSprTbl[1]);
    espScaleSet(m233_judgeSprTbl[1], 1.0f, 1.0f);
    espPriSet(m233_judgeSprTbl[1], 3);

    m233_logoSpr = espEntry(HuSprAnimDataRead(0x420001), 0, 1);
    espAttrSet(m233_logoSpr, 0x4008);
    espPosSet(m233_logoSpr, 160, -90);
    espDispOn(m233_logoSpr);
    espScaleSet(m233_logoSpr, 1.0f, 1.0f);
    espPriSet(m233_logoSpr, 254);

    m233_logoBackSpr = espEntry(HuSprAnimDataRead(0x420002), 0, 1);
    espAttrSet(m233_logoBackSpr, 0x4008);
    espPosSet(m233_logoBackSpr, 160, -90);
    espDispOn(m233_logoBackSpr);
    espScaleSet(m233_logoBackSpr, 1.0f, 1.0f);
    espTPLvlSet(m233_logoBackSpr, 230);
    espPriSet(m233_logoBackSpr, 255);

    m233_LogoPulseCreate();
    obj->func = NULL;
}

void m233_LogoInProc(void) {
    Vec2f screenPos;
    Vec pos;
    s32 i;
    s32 offset;

    HuPrcSleep(15);
    HuAudFXPlay(0x413);
    for (i = 0; i < 30; i++) {
        screenPos.x = 260.0f;
        screenPos.y = (i - 30.0f) * 4.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        m233_hostObj->trans.y = pos.y;
        offset = (30 - i) * 6;
        espPosSet(m233_logoSpr, 160, 90 - offset);
        espPosSet(m233_logoBackSpr, 158, 82 - offset);
        HuPrcVSleep();
    }
    espPosSet(m233_logoSpr, 160, 84);
    espPosSet(m233_logoBackSpr, 158, 78);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 94);
    espPosSet(m233_logoBackSpr, 158, 88);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 88);
    espPosSet(m233_logoBackSpr, 158, 82);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 92);
    espPosSet(m233_logoBackSpr, 158, 86);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 89);
    espPosSet(m233_logoBackSpr, 158, 83);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 91);
    espPosSet(m233_logoBackSpr, 158, 85);
    HuPrcVSleep();
    espPosSet(m233_logoSpr, 160, 90);
    espPosSet(m233_logoBackSpr, 158, 84);
    omDelPrcObj(NULL);
}

void m233_LogoPulseObjMain(omObjData *obj);

void m233_LogoPulseCreate(void) {
    omObjData *obj = omAddObj(5, 0, 0, -1, m233_LogoPulseObjMain);
    f32 *angle = HuMemAllocTag(sizeof(f32), TAG_OVERLAY);

    obj->data = angle;
    *angle = 0.0f;
}

void m233_LogoPulseObjMain(omObjData *obj) {
    f32 *angle = obj->data;
    f32 scale = sindf(*angle) * 0.02f + 1.02;

    espScaleSet(m233_logoSpr, scale, scale);
    *angle += 5.0f;
    if (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
}

void m233_StandCreateAll(void) {
    Vec2f screenPos;
    Vec pos;
    f32 heights[3] = { 47.0f, 94.0f, 141.0f };
    omObjData *obj;
    MpiqStageData *work;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 2, 0, -1, m233_StandObjMain);
        obj->data = HuMemAllocTag(sizeof(MpiqStageData), TAG_OVERLAY);
        m233_standObjTbl[i] = obj;
        work = obj->data;
        work->unkB0 = HuMemAllocTag(0x14, TAG_OVERLAY);
        if (i == 0) {
            obj->model[0] = Hu3DModelRead2(0x42000E, 0x29D);
        } else {
            obj->model[0] = Hu3DModelLink(m233_standObjTbl[0]->model[0]);
        }
        m233_stageScale = 1.0f;
        screenPos.x = m233_playerScreenXTbl[i];
        screenPos.y = 180.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, 0.0f, 0.0f);
        mgMapObjTbl[mgMapObjNum++] = obj;
        memset(obj->data, 0, sizeof(MpiqStageData));
        work->header.unk03 = 1;
        work->header.unk08 = 0.5f;
        work->header.unk04 = i + 1;
        MgMapBlockSet(obj, 0.0f, 100.0f, -100.0f, -100.0f, 100.0f, 100.0f);
        m233_standFlagTbl[i] = 0;
        m233_standLevelTbl[i] = 0;
    }
    for (j = 0; j < 3; j++) {
        m233_standHeightTbl[j] = heights[j];
    }
    obj->func = m233_StandObjMain;
}

void m233_StandObjMain(omObjData *obj) {
    MpiqBlockWork *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == m233_standObjTbl[i]) {
            break;
        }
    }
    if (m233_standFlagTbl[i] & 1) {
        obj->trans.y += 4.7f;
        work = m233_blockObjTbl[i]->data;
        work->y += 4.7f;
        if (obj->trans.y >= m233_standHeightTbl[m233_standLevelTbl[i] - 1]) {
            obj->trans.y = m233_standHeightTbl[m233_standLevelTbl[i] - 1];
            work->unk_0C = work->y;
            m233_standFlagTbl[i] &= ~1;
        }
    }
}

void m233_StandRaise(s32 index, s32 value) {
    m233_standLevelTbl[index] = value;
    m233_standFlagTbl[index] |= 1;
}

void m233_BlockCreateAll(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *obj;
    MpiqBlockWork *work;
    s32 i;
    s32 attr = 0x699;
    s32 attr2 = 0xA89;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(10, 3, 0, -1, m233_BlockObjMain);
        m233_blockObjTbl[i] = obj;
        obj->data = HuMemAllocTag(sizeof(MpiqBlockWork), TAG_OVERLAY);
        work = obj->data;
        if (i == 0) {
            obj->model[0] = Hu3DModelRead2(0x42000B, attr);
            obj->model[1] = Hu3DModelRead2(0x42000F, attr2 | 4);
            Hu3DModelTPLvlInit(obj->model[1]);
            obj->model[2] = Hu3DModelRead(0x5D0008, attr | 4);
        } else {
            obj->model[0] = Hu3DModelLink(m233_blockObjTbl[0]->model[0]);
            obj->model[1] = Hu3DModelLink(m233_blockObjTbl[0]->model[1]);
            obj->model[2] = Hu3DModelLink(m233_blockObjTbl[0]->model[2]);
        }
        Hu3DMotionAttrSet(obj->model[0], 1, 1);
        screenPos.x = m233_playerScreenXTbl[i];
        screenPos.y = 52.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, pos.y, 0.0f);
        work->x = pos.x;
        work->y = pos.y;
        work->unk_0C = pos.y;
        work->flags = 0;
        work->unk_08 = 0.0f;
        work->index = i;
        work->unk_24 = 0;
        Hu3DModelPosSet(obj->model[1], work->x, work->y, 0.0f);
    }
}

void m233_BlockObjMain(omObjData *obj) {
    f32 bounce[12] = { 0.0f, 10.0f, 25.0f, 40.0f, 52.0f, 50.0f, 50.0f, 48.0f, 38.0f, 29.0f, 25.0f, 160.0f };
    MpiqBlockWork *work = obj->data;
    f32 limit;
    s16 model;
    s32 i;

    obj->trans.y = work->y;
    if (work->flags & 1) {
        work->y -= work->unk_08;
        work->unk_08 += 8.0f;
        limit = m233_standObjTbl[work->index]->trans.y + 30.0f;
        if (work->y <= limit) {
            work->y = limit;
            work->flags &= ~1;
            work->flags |= 2;
            m233_HitEffStart(obj->trans.x, obj->trans.y - 50.0f, obj->trans.z);
        }
    }
    if (work->flags & 2) {
        work->y += 16.0f;
        if (work->y >= work->unk_0C) {
            work->y = work->unk_0C;
            work->flags &= ~2;
        }
    }
    if (work->flags & 8) {
        Hu3DMotionAttrSet(obj->model[0], 4, 4);
        work->flags &= ~8;
    }
    if (work->flags & 0x10) {
        if (--work->timer == 12) {
            Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        model = obj->model[2];
        if (Hu3DData[model].motTime >= Hu3DMotion[Hu3DData[model].motId].unk02) {
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            work->flags &= ~0x10;
        }
    }
    if (work->flags & 0x20) {
        work->timer--;
        Hu3DModelScaleSet(obj->model[1], work->scale, work->scale, work->scale);
        Hu3DModelPosSet(obj->model[1], work->x, work->y + bounce[7 - work->timer], 0.0f);
        Hu3DModelTPLvlSet(obj->model[1], work->counter);
        work->scale += 0.2f;
        work->counter -= 35;
        if (work->timer == 0) {
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            work->flags &= ~0x20;
        }
    }
    if (m233_ObjHitCheck(obj, mgPlayerObjTbl[m233_answerPlayer])) {
        if (work->flags & 3) {
            if (work->unk_24 == 0) {
                _HuAudPlayerFXPlay(0x411, m233_answerPlayerS16);
                work->unk_24 = 1;
            }
            MgPlayerSquashSet(mgPlayerObjTbl[m233_answerPlayer], 1);
            omVibrate(m233_answerPlayerS16, 20, 0, 20);
        } else if (m233_buzzLockF == 0) {
            Hu3DMotionAttrSet(obj->model[0], 4, 0);
            Hu3DMotionAttrSet(obj->model[0], 1, 0);
            MgPlayerMotSwap(mgPlayerObjTbl[m233_answerPlayer], 0x26, 0);
            m233_buzzLockF = 1;
            for (i = 0; i < 4; i++) {
                MgPlayerVelYSet(mgPlayerObjTbl[i], 1000.0f);
            }
            work->flags |= 0x20;
            work->timer = 7;
            Hu3DModelAttrSet(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            work->scale = 1.0f;
            work->counter = 255;
        }
    } else {
        work->unk_24 = 0;
    }
}

void m233_BlockDrop(s32 index) {
    MpiqBlockWork *work = OM_GET_DATA_PTR(m233_blockObjTbl[index], MpiqBlockWork);
    work->flags |= 1;
    work->unk_08 = 4.0f;
    work->index = index;
}

void m233_BlockMotStop(s32 index) {
    OM_GET_DATA_PTR(m233_blockObjTbl[index], MpiqBlockWork)->flags |= 8;
}

void m233_BlockEffStartAll(void) {
    omObjData *obj;
    MpiqBlockWork *work;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = m233_blockObjTbl[i];
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z + 200.0f;
        work = obj->data;
        work->flags |= 0x10;
        work->timer = 15;
        Hu3DModelPosSet(m233_blockObjTbl[i]->model[2], x, y, z);
        Hu3DModelScaleSet(m233_blockObjTbl[i]->model[2], 1.0f, 1.0f, 1.0f);
        Hu3DModelAttrSet(m233_blockObjTbl[i]->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void m233_HitEffCreate(void) {
    omObjData *obj;
    s32 *flags;

    obj = omAddObj(0xFF, 1, 0, -1, m233_HitEffObjMain);
    m233_hitEffObj = obj;
    flags = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);
    obj->data = flags;
    *flags = 0;
    *obj->model = Hu3DModelRead(8, 0x69D);
}

void m233_HitEffObjMain(omObjData *obj) {
    s32 *flags = obj->data;
    s16 model;

    if (*flags & 1) {
        model = obj->model[0];
        if (Hu3DData[model].motTime >= Hu3DMotion[Hu3DData[model].motId].unk02) {
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            *flags &= ~1;
        }
    }
}

void m233_HitEffStart(f32 x, f32 y, f32 z) {
    omObjData *obj = m233_hitEffObj;
    s32 *flags = obj->data;

    *flags |= 1;
    Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DMotionTimeSet(m233_hitEffObj->model[0], 0.0f);
    omSetTra(m233_hitEffObj, x, y, z);
}

void m233_StunCreate(void) {
    omObjData *obj;
    MpiqStunWork *work;

    obj = omAddObj(0xFF, 1, 0, -1, m233_StunObjMain);
    m233_stunObj = obj;
    work = HuMemAllocTag(sizeof(MpiqStunWork), TAG_OVERLAY);
    obj->data = work;
    work->flags = 0;
    obj->model[0] = Hu3DModelRead(0x230009, 0x69D);
    Hu3DModelScaleSet(obj->model[0], 1.5f, 1.5f, 1.5f);
    work->timer = 0;
}

void m233_StunObjMain(omObjData *obj) {
}

void m233_StunStart(s32 index) {
    f32 heights[8] = { 100.0f, 110.0f, 100.0f, 110.0f, 100.0f, 120.0f, 110.0f, 100.0f };
    omObjData *player = mgPlayerObjTbl[index];
    s32 chr = GwPlayer[index].chr;
    f32 x = player->trans.x;
    f32 y = player->trans.y + heights[chr];
    f32 z = player->trans.z;
    omObjData *obj = m233_stunObj;
    MpiqStunWork *work = obj->data;

    work->flags |= 1;
    if (work->timer == 0) {
        Hu3DModelAttrSet(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DMotionTimeSet(m233_stunObj->model[0], 0.0f);
        Hu3DMotionAttrSet(m233_stunObj->model[0], 2, 2);
    }
    omSetTra(m233_stunObj, x, y, z);
    work->timer++;
}

void m233_StunEnd(void) {
    MpiqStunWork *work = OM_GET_DATA_PTR(m233_stunObj, MpiqStunWork);

    if (--work->timer == 0) {
        Hu3DModelAttrSet(*m233_stunObj->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->flags &= ~1;
    }
}

void m233_MeterCreateAll(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *obj;
    MpiqMeterWork *work;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 5, 0, -1, m233_MeterObjMain);
        m233_meterObjTbl[i] = obj;
        obj->data = HuMemAllocTag(sizeof(MpiqMeterWork), TAG_OVERLAY);
        work = obj->data;
        omSetSca(obj, 2.0f, 3.0f, 2.0f);
        if (i == 0) {
            obj->model[0] = Hu3DModelRead(0x42000A, 0x6B9);
            obj->model[1] = Hu3DModelRead(0x420007, 0x6BD);
            obj->model[2] = Hu3DModelRead(0x420008, 0x6BD);
            obj->model[3] = Hu3DModelRead(0x420009, 0x6BD);
            obj->model[4] = Hu3DModelRead(0x420006, 0x6B9);
        } else {
            obj->model[0] = Hu3DModelLink(m233_meterObjTbl[0]->model[0]);
            obj->model[1] = Hu3DModelLink(m233_meterObjTbl[0]->model[1]);
            obj->model[2] = Hu3DModelLink(m233_meterObjTbl[0]->model[2]);
            obj->model[3] = Hu3DModelLink(m233_meterObjTbl[0]->model[3]);
            obj->model[4] = Hu3DModelLink(m233_meterObjTbl[0]->model[4]);
        }
        work->stage = 0;
        work->flags = 0;
        screenPos.x = m233_playerScreenXTbl[i];
        screenPos.y = 180.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, -144.0f, 0.0f);
        omSetSca(obj, 2.0f, 4.0f, 2.0f);
        work->x = pos.x;
        work->posY[0] = 0.0f;
        Hu3DModelPosSet(obj->model[4], pos.x, work->posY[0], work->posY[0]);
        Hu3DModelScaleSet(obj->model[4], 2.0f, 1.0f, 2.0f);
        for (j = 0; j < 3; j++) {
            Hu3DModelScaleSet(obj->model[j + 1], 2.0f, 2.0f, 2.0f);
            work->posY[j + 1] = j * 50.0f - 44.0f;
            Hu3DModelPosSet(obj->model[j + 1], pos.x, work->posY[j + 1], 0.0f);
            work->barScale[j] = 0.0f;
        }
    }
}

void m233_MeterObjMain(omObjData *obj) {
    MpiqMeterWork *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == m233_meterObjTbl[i]) {
            break;
        }
    }
    work = obj->data;
    for (i = 0; i < 3; i++) {
        Hu3DData[obj->model[i + 1]].scale.y = work->barScale[i];
    }
    if (work->flags & 1) {
        work->barScale[work->stage] += 0.2f;
        Hu3DData[obj->model[4]].pos.y = m233_standObjTbl[m233_answerPlayer]->trans.y;
        if (work->barScale[work->stage] >= 2.0f) {
            work->barScale[work->stage] = 2.0f;
        }
        if (!(m233_standFlagTbl[work->index] & 1)) {
            work->stage++;
            work->flags &= ~1;
        }
    }
}

void m233_MeterAdd(s32 index) {
    MpiqMeterWork *work = m233_meterObjTbl[index]->data;

    work->flags |= 1;
    work->index = index;
    Hu3DModelAttrSet(m233_meterObjTbl[index]->model[work->stage + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    _HuAudPlayerFXPlay(0x410, index);
    omVibrate(index, 10, 0, 10);
}

void m233_HostCreate(void) {
    Vec pos;
    Vec2f screenPos;
    omObjData *obj;
    MpiqHostWork *work;

    obj = omAddObj(10, 1, 1, -1, m233_HostObjMain);
    obj->data = HuMemAllocTag(sizeof(MpiqHostWork), TAG_OVERLAY);
    m233_hostObj = obj;
    work = obj->data;
    obj->model[0] = Hu3DModelRead(0xA005D, 0x6D9);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    screenPos.x = 260.0f;
    screenPos.y = -120.0f;
    Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
    omSetTra(obj, pos.x, pos.y, 200.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.1f, 1.1f, 1.1f);
    omObjMotionRead(obj, 0, 0xA005F);
    omObjMotionRead(obj, 1, 0xA0060);
    omObjMotionRead(obj, 2, 0xA0061);
    Hu3DMotionModelSet(obj->model[0], obj->motion[0]);
    Hu3DMotionAttrSet(obj->model[0], 2, 2);
    work->rotY = 0.0f;
}

void m233_HostObjMain(omObjData *obj) {
    MpiqHostWork *work = obj->data;
    s16 model;

    omSetRot(obj, 0.0f, work->rotY, 0.0f);
    if (work->flags & 1) {
        model = obj->model[0];
        if (Hu3DData[model].motTime >= Hu3DMotion[Hu3DData[model].motId].unk02) {
            Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 0);
            Hu3DMotionAttrSet(obj->model[0], 2, 2);
            work->flags &= ~1;
        }
    }
    if (work->flags & 4) {
        work->rotY -= 12.0f;
        if (work->rotY <= -120.0f) {
            work->rotY = -120.0f;
            work->flags &= ~4;
        }
    }
    if (work->flags & 2) {
        work->rotY += 12.0f;
        if (work->rotY >= 0.0f) {
            work->rotY = 0.0f;
            work->flags &= ~2;
        }
    }
}

void m233_HostTurnSet(s32 flags) {
    MpiqHostWork *work = OM_GET_DATA_PTR(m233_hostObj, MpiqHostWork);
    work->flags &= ~2;
    work->flags &= ~4;
    work->flags |= flags;
}

s16 m233_ObjHitCheck(omObjData *objA, omObjData *objB) {
    s32 result = 0;
    f32 ax = objA->trans.x;
    f32 ay = objA->trans.y;
    f32 bx = objB->trans.x;
    f32 by = objB->trans.y;

    if (HuSqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) < 150.0f) {
        result = 1;
    }
    return result;
}

void m233_CameraInit(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    CamSetupInit(1);
    m233_cameraNo = CamSetupMapCullAdd();
    ScissorSet(m233_cameraNo, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(m233_cameraNo, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCameraPerspectiveSet(m233_cameraNo, 30.0f, 80.0f, 8000.0f);
}

void m233_ChoiceCreate(void) {
    s32 images[3] = { 3, 4, 5 };
    omObjData *obj;
    MpiqChoiceWork *work;
    s32 i;

    obj = omAddObj(10, 0, 0, -1, m233_ChoiceObjMain);
    obj->data = work = HuMemAllocTag(sizeof(MpiqChoiceWork), TAG_OVERLAY);
    m233_choiceObj = obj;
    work->flags = 0;
    work->scale = 0.0f;
    work->x = 0.0f;
    work->y = 0.0f;
    for (i = 0; i < 3; i++) {
        m233_choiceSprAnimTbl[i] = HuSprAnimDataRead(images[i] | 0x420000);
        m233_choiceSprTbl[i] = espEntry(m233_choiceSprAnimTbl[i], 0, 1);
        espAttrSet(m233_choiceSprTbl[i], 8);
        espPosSet(m233_choiceSprTbl[i], 160, 120);
        espDispOn(m233_choiceSprTbl[i]);
        espScaleSet(m233_choiceSprTbl[i], 1.0f, 1.0f);
        espPriSet(m233_choiceSprTbl[i], 255);
    }
    omAddPrcObj(m233_ChoiceSelectProc, 0x4800, 0, 0);
    omAddPrcObj(m233_ComInputProc, 0x5100, 0, 0);
}

void m233_ComInputProc(void) {
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].stat & 1) {
                HuPadBtn[GwPlayer[i].pad] &= ~(A_BUTTON | B_BUTTON | Z_TRIG);
                HuPadBtnDown[GwPlayer[i].pad] &= ~(A_BUTTON | B_BUTTON | Z_TRIG);
            }
            if (MgFlowStatGet() == MG_STATE_PLAY && (GwPlayer[i].stat & 1)) {
                m233_ComInput(i);
            }
        }
        HuPrcVSleep();
    }
}

void m233_ChoiceObjMain(omObjData *obj) {
    MpiqChoiceWork *work = obj->data;
    s32 i;

    if (work->flags & 4) {
        espDispOn(m233_choiceSprTbl[0]);
    } else {
        espDispOff(m233_choiceSprTbl[0]);
    }
    if (work->flags & 8) {
        espDispOn(m233_choiceSprTbl[1]);
    } else {
        espDispOff(m233_choiceSprTbl[1]);
    }
    if (work->flags & 0x10) {
        espDispOn(m233_choiceSprTbl[2]);
    } else {
        espDispOff(m233_choiceSprTbl[2]);
    }
    for (i = 0; i < 3; i++) {
        espPosSet(m233_choiceSprTbl[i], work->x, work->y);
        espScaleSet(m233_choiceSprTbl[i], work->scale, work->scale);
    }
    if (work->flags & 1) {
        work->scale += 0.2f;
        if (work->scale >= 1.0f) {
            work->scale = 1.0f;
            work->flags &= ~1;
        }
    }
    if (work->flags & 2) {
        work->scale -= 0.2f;
        if (work->scale <= 0.2f) {
            work->scale = 0.2f;
            work->flags &= ~0x1E;
            m233_quizFlag &= ~0x20;
        }
    }
}

void m233_ChoiceSelectProc(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *player;
    MpiqChoiceWork *work;
    u16 buttons;

    while (TRUE) {
        player = mgPlayerObjTbl[m233_answerPlayer];
        if (m233_buzzLockF == 1 && m233_choiceNo == -1 && (m233_quizFlag & 4) &&
            m233_PlayerOnStandCheck(m233_answerPlayer)) {
            buttons = HuPadBtnDown[GwPlayer[m233_answerPlayer].pad];
            work = m233_choiceObj->data;
            pos.x = player->trans.x;
            pos.y = player->trans.y;
            pos.z = player->trans.z;
            Hu3D3Dto2D(0, &pos, &screenPos);
            work->x = screenPos.x + 28.0f;
            work->y = screenPos.y - 46.0f;
            work->scale = 0.0f;
            if ((buttons & (A_BUTTON | B_BUTTON | Z_TRIG)) == A_BUTTON) {
                m233_choiceNo = 0;
                MgPlayerMotSwap(player, 0x26, 0);
                MgPlayerMotForceSet(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < Hu3DMotion[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                MgPlayerMotForceSet(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 5;
                HuPrcSleep(30);
                work->flags |= 2;
                m233_quizFlag &= ~0x20;
            }
            if ((buttons & (A_BUTTON | B_BUTTON | Z_TRIG)) == B_BUTTON) {
                m233_choiceNo = 1;
                MgPlayerMotSwap(player, 0x26, 0);
                MgPlayerMotForceSet(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < Hu3DMotion[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                MgPlayerMotForceSet(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 9;
                HuPrcSleep(30);
                work->flags |= 2;
                m233_quizFlag &= ~0x20;
            }
            if ((buttons & (A_BUTTON | B_BUTTON | Z_TRIG)) == Z_TRIG) {
                m233_choiceNo = 2;
                MgPlayerMotSwap(player, 0x26, 0);
                MgPlayerMotForceSet(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < Hu3DMotion[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                MgPlayerMotForceSet(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 0x11;
                HuPrcSleep(30);
                work->flags |= 2;
                m233_quizFlag &= ~0x20;
            }
        }
        HuPrcVSleep();
    }
}

void m233_QuestionTblCreate(void) {
    s32 used[64];
    s32 answerUsed[3];
    s32 mes = 0;
    s32 i;
    s32 j;
    s32 question;
    s32 answer;

    for (i = 0; i < 64; i++) {
        used[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        m233_questionFlagTbl[i] = 0;
        while (TRUE) {
            question = rand8() % 64;
            if (m233_endlessF != 0) {
                question = m233_endlessQuestionNo;
                m233_endlessQuestionNo++;
                if (m233_endlessQuestionNo > 64) {
                    m233_endlessQuestionNo = 0;
                }
            }
            if (question >= 36) {
                if (question < 49) {
                    mes = (question - 36) * 2 + 0x5300;
                } else {
                    mes = (question - 49) * 2 + 0x5400;
                }
                m233_questionMesTbl[i] = mes;
                m233_QuestionInsertSet(i);
            }
            if (used[question] == 0 && m233_QuestionCheck(i, question)) {
                if (question < 36) {
                    mes = question * 4 + 0x5500;
                    m233_questionMesTbl[i] = mes;
                    m233_choiceUnitMesTbl[i] = 0x5307;
                }
                if (m233_endlessF == 0) {
                    used[question]++;
                }
                for (j = 0; j < 3; j++) {
                    answerUsed[j] = 0;
                    m233_choiceTbl[i][j] = -1;
                }
                if (question >= 36) {
                    m233_AnswerCalc(i);
                }
                m233_boardPickCnt = 0;
                for (j = 0; j < 3; j++) {
                    while (TRUE) {
                        answer = (u8)(rand8() % 3);
                        if (answerUsed[answer] == 0) {
                            if (question < 36) {
                                m233_choiceTbl[i][j] = mes + 1 + answer;
                            } else {
                                m233_choiceTbl[i][j] = m233_ChoiceGet(i, answer);
                            }
                            if (answer == 0) {
                                m233_correctChoiceTbl[i] = j;
                            }
                            answerUsed[answer]++;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}

s32 m233_QuestionCheck(s32 index, s32 question) {
    s32 list[2][6];
    s32 result = TRUE;
    s32 mes;
    s32 value;
    s32 count;
    s32 pick;
    s32 temp;
    s32 swap;
    s32 i;
    s32 j;

    if (m233_endlessF != 0) {
        return TRUE;
    }
    if (question >= 36) {
        if (question >= 49) {
            if (_CheckFlag(0x1C)) {
                return FALSE;
            }
        }
        if (question < 49) {
            mes = question * 2 + 0x52B8;
        } else {
            mes = question * 2 + 0x539E;
        }
        switch (mes) {
            case 0x5302:
                value = m233_insertMesTbl[index] - 0x1C60;
                count = MgStoryRankGet(value);
                if (count == -1) {
                    return FALSE;
                }
                break;
            case 0x5304:
                if (GWMgUnlockCheck(12) == 0) {
                    result = FALSE;
                }
                break;
            case 0x5306:
                if (GWMgUnlockCheck(34) == 0) {
                    result = FALSE;
                }
                break;
            case 0x5308:
                if (GWMgUnlockCheck(51) == 0) {
                    result = FALSE;
                }
                break;
            case 0x530A:
                if (GWMgUnlockCheck(43) == 0) {
                    result = FALSE;
                }
                break;
            case 0x530C:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(5) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x530E:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(6) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x5310:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(7) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x5312:
            case 0x5314:
                for (i = 0; i < 6; i++) {
                    if (mes == 0x5312) {
                        list[0][i] = GwCommon.boardRecord[0][i].playCount;
                    } else {
                        list[0][i] = GwCommon.boardRecord[1][i].playCount;
                    }
                    list[1][i] = i;
                }
                for (i = 0; i < 6; i++) {
                    for (j = i; j < 6; j++) {
                        if (list[0][j] >= list[0][i]) {
                            swap = list[0][i];
                            list[0][i] = list[0][j];
                            list[0][j] = swap;
                            swap = list[1][i];
                            list[1][i] = list[1][j];
                            list[1][j] = swap;
                        }
                    }
                }
                count = 0;
                for (i = 0; i < 6; i++) {
                    if (list[0][i] == list[0][0]) {
                        count++;
                    }
                }
                if (count >= 5) {
                    return FALSE;
                }
                pick = 0;
                if (count != 0) {
                    pick = rand8() % count;
                }
                m233_boardPickTbl[0] = list[1][pick];
                for (i = 0; i < 2; i++) {
                    do {
                        pick = rand8() % (6 - count) + count;
                        for (j = 0, temp = 0; j < i + 1; j++) {
                            if (list[1][pick] == m233_boardPickTbl[j]) {
                                temp++;
                            }
                        }
                    } while (temp != 0);
                    m233_boardPickTbl[i + 1] = list[1][pick];
                }
                break;
            case 0x5316:
                value = 0;
                for (i = 0; i < 6; i++) {
                    if (GwCommon.boardRecord[0][i].playCount != 0) {
                        list[0][value] = i;
                        value++;
                    }
                }
                if (value == 0) {
                    result = FALSE;
                } else {
                    m233_boardPickNo = list[0][rand8() % value];
                }
                break;
            case 0x5318:
                value = 0;
                for (i = 0; i < 6; i++) {
                    if (GwCommon.boardRecord[1][i].playCount != 0) {
                        list[0][value] = i;
                        value++;
                    }
                }
                if (value == 0) {
                    result = FALSE;
                } else {
                    m233_boardPickNo = list[0][rand8() % value];
                }
                break;
            case 0x5404:
            case 0x5412:
            case 0x5414:
                value = 0;
                for (i = 0; i < 4; i++) {
                    switch (mes) {
                        case 0x5404:
                            count = GwPlayer[i].gamePrize;
                            break;
                        case 0x5412:
                            count = GwPlayer[i].star;
                            break;
                        default:
                            count = GwPlayer[i].coin;
                            break;
                    }
                    if (count == 0) {
                        value++;
                    }
                }
                if (value == 4) {
                    result = FALSE;
                }
                break;
            case 0x5400:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].star;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5402:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].coin;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5406:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.redPrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5408:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.bluePrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x540A:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.hatenaPrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x540C:
                if (GwSystem.bank_coins == 0) {
                    result = FALSE;
                }
                break;
            case 0x541A:
                value = m233_insertMesTbl[index] - 0x1C60;
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].chr == value) {
                        break;
                    }
                }
                if (GwPlayer[i].coin == 0) {
                    result = FALSE;
                }
                break;
            case 0x541C:
                value = m233_insertMesTbl[index] - 0x1C60;
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].chr == value) {
                        break;
                    }
                }
                if (GwPlayer[i].star == 0) {
                    result = FALSE;
                }
                break;
            case 0x5410:
                result = FALSE;
                break;
        }
    } else {
        mes = question * 4 + 0x5500;
        switch (mes) {
            case 0x5578:
                if (GwCommon.boardRecord[0][0].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x557C:
                if (GwCommon.boardRecord[0][1].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5580:
                if (GwCommon.boardRecord[0][2].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5584:
                if (GwCommon.boardRecord[0][3].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5588:
                if (GwCommon.boardRecord[0][4].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x558C:
                if (GwCommon.boardRecord[0][5].playCount == 0) {
                    result = FALSE;
                }
                break;
        }
    }
    return result;
}

void m233_QuestionInsertSet(s32 index) {
    s32 value;

    switch (m233_questionMesTbl[index]) {
        case 0x5300:
            value = rand8() & 0xF;
            m233_insertMesTbl[index] = value + 0x531B;
            m233_questionFlagTbl[index] |= 2;
            break;
        case 0x5302:
            value = (u8)(rand8() % 6);
            m233_insertMesTbl[index] = value + 0x1C60;
            m233_questionFlagTbl[index] |= 2;
            break;
        case 0x5316:
            value = m233_boardPickNo;
            m233_insertMesTbl[index] = value + 0x532B;
            m233_questionFlagTbl[index] |= 2;
            break;
        case 0x5318:
            value = m233_boardPickNo;
            m233_insertMesTbl[index] = value + 0x5331;
            m233_questionFlagTbl[index] |= 2;
            break;
        case 0x541A:
        case 0x541C:
            value = rand8() & 3;
            m233_insertMesTbl[index] = GwPlayer[value].chr + 0x1C60;
            m233_questionFlagTbl[index] |= 2;
            break;
        default:
            m233_insertMesTbl[index] = 0;
            break;
    }
}

void m233_AnswerCalc(s32 index) {
    s32 list[4];
    s32 value;
    s32 other;
    s32 count;
    s32 rank;
    s32 i;

    for (i = 0; i < 256; i++) {
        m233_answerBuf[i] = 0;
    }
    switch (m233_questionMesTbl[index]) {
        case 0x5300:
            m233_questionFlagTbl[index] |= 1;
            value = m233_insertMesTbl[index] - 0x531B;
            m233_answerValue = m233_insertAnswerTbl[value];
            break;
        case 0x5302:
            value = m233_insertMesTbl[index] - 0x1C60;
            rank = MgStoryRankGet(value);
            other = 0x533B;
            m233_answerValue = other - rank;
            if (m233_endlessF != 0) {
                m233_answerValue = 0x5337;
            }
            break;
        case 0x5304:
            m233_questionFlagTbl[index] |= 1;
            m233_answerValue = GWMgRecordGet(0);
            break;
        case 0x5306:
            m233_questionFlagTbl[index] |= 4;
            m233_answerValue = GWMgRecordGet(2);
            break;
        case 0x5308:
            m233_questionFlagTbl[index] |= 32;
            m233_answerValue = GWMgRecordGet(4);
            break;
        case 0x530A:
            m233_questionFlagTbl[index] |= 4;
            m233_answerValue = GWMgRecordGet(3) * 2;
            break;
        case 0x530C:
            m233_questionFlagTbl[index] |= 4;
            m233_answerValue = GWMgRecordGet(5);
            break;
        case 0x530E:
            m233_questionFlagTbl[index] |= 4;
            m233_answerValue = GWMgRecordGet(6);
            break;
        case 0x5310:
            m233_questionFlagTbl[index] |= 4;
            m233_answerValue = GWMgRecordGet(7);
            break;
        case 0x5312:
            m233_answerValue = m233_boardPickTbl[0] + 0x532B;
            break;
        case 0x5314:
            m233_answerValue = m233_boardPickTbl[0] + 0x5331;
            break;
        case 0x5316:
            m233_questionFlagTbl[index] |= 1;
            value = m233_insertMesTbl[index] - 0x532B;
            m233_answerValue = GwCommon.boardRecord[0][value].playCount;
            break;
        case 0x5318:
            m233_questionFlagTbl[index] |= 1;
            value = m233_insertMesTbl[index] - 0x5331;
            m233_answerValue = GwCommon.boardRecord[1][value].playCount;
            break;
        case 0x5400:
            m233_questionFlagTbl[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                value += GwPlayer[i].star & 0x7F;
            }
            m233_answerValue = value;
            break;
        case 0x5402:
            m233_questionFlagTbl[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                value += GwPlayer[i].coin;
            }
            m233_answerValue = value;
            break;
        case 0x5404:
        case 0x5412:
        case 0x5414:
        case 0x5416:
        case 0x5418:
            other = m233_questionMesTbl[index];
            value = 1000;
            if (other == 0x5404 || other == 0x5412 || other == 0x5414) {
                value = 0;
            }
            for (i = 0; i < 4; i++) {
                switch (m233_questionMesTbl[index]) {
                    case 0x5404:
                        other = GwPlayer[i].gamePrize;
                        break;
                    case 0x5412:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    case 0x5416:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    default:
                        other = GwPlayer[i].coin;
                        break;
                }
                if (m233_questionMesTbl[index] == 0x5404 || m233_questionMesTbl[index] == 0x5412 ||
                    m233_questionMesTbl[index] == 0x5414) {
                    if (value < other) {
                        value = other;
                    }
                } else {
                    if (other < value) {
                        value = other;
                    }
                }
            }
            count = 0;
            for (i = 0; i < 4; i++) {
                switch (m233_questionMesTbl[index]) {
                    case 0x5404:
                        other = GwPlayer[i].gamePrize;
                        break;
                    case 0x5412:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    case 0x5416:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    default:
                        other = GwPlayer[i].coin;
                        break;
                }
                if (other == value) {
                    list[count] = i;
                    count++;
                }
            }
            value = rand8() % count;
            m233_answerValue = GwPlayer[list[value]].chr + 0x1C60;
            break;
        case 0x5406:
        case 0x5408:
        case 0x540A:
            m233_questionFlagTbl[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                switch (m233_questionMesTbl[index]) {
                    case 0x5406:
                        value += GwPlayer[i].stats.prize.redPrize & 0x7F;
                        break;
                    case 0x5408:
                        value += GwPlayer[i].stats.prize.bluePrize & 0x7F;
                        break;
                    default:
                        value += GwPlayer[i].stats.prize.hatenaPrize & 0x7F;
                        break;
                }
            }
            m233_answerValue = value;
            break;
        case 0x540C:
            m233_questionFlagTbl[index] |= 1;
            m233_answerValue = GwSystem.bank_coins;
            break;
        case 0x540E:
            m233_questionFlagTbl[index] |= 1;
            m233_answerValue = index + m233_questionNoBase + 1;
            break;
        case 0x5410:
            m233_questionFlagTbl[index] |= 1;
            m233_answerValue = (GwSystem.current_turn + 1) & 0x7F;
            break;
        case 0x541A:
        case 0x541C:
            m233_questionFlagTbl[index] |= 1;
            value = m233_insertMesTbl[index] - 0x1C60;
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].chr == value) {
                    break;
                }
            }
            if (m233_questionMesTbl[index] == 0x541A) {
                m233_answerValue = GwPlayer[i].coin;
            } else {
                m233_answerValue = GwPlayer[i].star & 0x7F;
            }
            break;
    }
    m233_choiceUnitMesTbl[index] = m233_questionMesTbl[index] + 1;
}

s16 m233_ChoiceGet(s32 index, s32 answer) {
    s32 offset;
    s32 value = 0;
    s32 found;
    s32 i;

    if (answer == 0) {
        value = m233_answerValue;
    } else {
        switch (m233_questionMesTbl[index]) {
            case 0x5300:
            case 0x540C:
                value = m233_ChoiceNumGet(index, 11, -5, 1);
                break;
            case 0x5302:
                do {
                    offset = rand8() & 3;
                    if (m233_endlessF != 0) {
                        return offset + 0x5337;
                    }
                    found = 0;
                    for (i = 0; i < 3; i++) {
                        value = offset + 0x5337;
                        if (value == m233_choiceTbl[index][i] || value == m233_answerValue || value < 0) {
                            found++;
                            break;
                        }
                    }
                } while (found != 0);
                break;
            case 0x5304:
                value = m233_ChoiceNumGet(index, 16, -5, 10);
                break;
            case 0x5306:
            case 0x530A:
            case 0x530C:
            case 0x530E:
            case 0x5310:
                value = m233_ChoiceNumGet(index, 9, -3, 60);
                break;
            case 0x5308:
                value = m233_ChoiceNumGet(index, 16, -5, 100);
                break;
            case 0x5312:
                value = m233_boardPickWrongTbl[m233_boardPickCnt] + 0x532B;
                m233_boardPickCnt++;
                break;
            case 0x5314:
                value = m233_boardPickWrongTbl[m233_boardPickCnt] + 0x5331;
                m233_boardPickCnt++;
                break;
            case 0x5316:
            case 0x5318:
            case 0x540E:
            case 0x541C:
                value = m233_ChoiceNumGet(index, 4, -1, 1);
                break;
            case 0x5400:
                value = m233_ChoiceNumGet(index, 5, -2, 1);
                break;
            case 0x5402:
            case 0x541A:
                value = m233_ChoiceNumGet(index, 21, -10, 1);
                break;
            case 0x5404:
            case 0x5412:
            case 0x5414:
            case 0x5416:
            case 0x5418:
                value = m233_ChoiceChrGet(index);
                break;
            case 0x5406:
            case 0x5408:
            case 0x540A:
                value = m233_ChoiceNumGet(index, 7, -3, 1);
                break;
            case 0x5410:
                value = m233_ChoiceNumGet(index, 9, -3, 1);
                break;
        }
    }
    return value;
}

s32 m233_ChoiceChrGet(s32 index) {
    s32 value = 0;
    s32 found;
    s32 chr;
    s32 i;

    do {
        found = 0;
        chr = rand8() & 7;
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].chr == chr) {
                break;
            }
        }
        if (i == 4) {
            value = chr + 0x1C60;
            for (i = 0; i < 3; i++) {
                if (value == m233_choiceTbl[index][i]) {
                    break;
                }
            }
            if (i == 3) {
                found++;
            }
        }
    } while (found == 0);
    return value;
}

s32 m233_ChoiceNumGet(s32 index, s32 range, s32 base, s32 scale) {
    s32 offset;
    s32 tries = 0;
    s32 value;
    s32 found;
    s32 i;

    while (TRUE) {
        offset = (rand8() % range + base) * scale;
        found = 0;
        for (i = 0; i < 3; i++) {
            value = offset + m233_answerValue;
            if (value == m233_choiceTbl[index][i] || value == m233_answerValue || value <= 0) {
                found++;
                break;
            }
        }
        if (found == 0 || (m233_endlessF != 0 && tries == 100)) {
            break;
        }
        tries++;
    }
    return value;
}

void m233_QuizProc(void) {
    s32 counts[4];
    omObjData *player;
    MpiqHostWork *data;
    s32 i;
    s32 round;
    s32 count;
    s32 wins;
    s32 tied;

    while (MgFlowStatGet() != MG_STATE_PLAY) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        counts[i] = 0;
    }
    m233_winner = -1;
    while (1) {
        for (round = 0; round < 10; round++) {
            m233_quizFlag = 0;
            m233_questionNo = round;
            m233_choiceNo = -1;
            for (i = 0; i < 4; i++) {
                m233_ComInputSet(i);
            }
            m233_HostTurnSet(4);
            m233_questionWin = m233_QuestionWinCreate();
            omAddPrcObj(m233_CountdownProc, 0x4900, 0, 0);
            HuPrcVSleep();
            m233_buzzLockF = 0;
            omAddObj(6, 0, 0, -1, m233_BuzzObjMain);
            while (HuWinStatGet(m233_questionWin) != 0) {
                if (m233_quizFlag & 4) {
                    break;
                }
                HuPrcVSleep();
            }
            if (!(m233_quizFlag & 4)) {
                m233_quizFlag |= 0x10;
                while (m233_quizFlag & 0x10) {
                    HuPrcVSleep();
                }
            }
            HuWinKill(m233_questionWin);
            m233_questionWin = -1;
            if (m233_quizFlag & 4) {
                _HuAudPlayerFXPlay(0x40D, m233_answerPlayer);
                PlayerFXPlay(0xCA, m233_answerPlayer);
                m233_questionWin = m233_ChoiceWinCreate();
                m233_HostTurnSet(2);
                m233_quizFlag |= 0x20;
                while (m233_quizFlag & 0x20) {
                    HuPrcVSleep();
                }
                HuWinKill(m233_questionWin);
                m233_questionWin = -1;
                m233_BlockMotStop(m233_answerPlayer);
                player = mgPlayerObjTbl[m233_answerPlayer];
                data = m233_hostObj->data;
                if (m233_choiceNo == m233_correctChoiceTbl[round]) {
                    _HuAudPlayerFXPlay(0x40E, m233_answerPlayer);
                    PlayerFXPlay(0x274, m233_answerPlayer);
                    espDispOn(m233_judgeSprTbl[0]);
                    MgPlayerMotForceSet(player, 0x29);
                    Hu3DMotionShiftSet(m233_hostObj->model[0], Hu3DData[m233_hostObj->motion[1]].motId, 0, 10, 0);
                    data->flags |= 1;
                    HuPrcSleep(30);
                    if (m233_endlessF == 0) {
                        m233_StandRaise(m233_answerPlayer, ++m233_scoreTbl[m233_answerPlayer]);
                        m233_MeterAdd(m233_answerPlayer);
                        HuPrcSleep(30);
                    }
                } else {
                    _HuAudPlayerFXPlay(0x40F, m233_answerPlayer);
                    PlayerFXPlay(0x286, m233_answerPlayer);
                    espDispOn(m233_judgeSprTbl[1]);
                    MgPlayerMotForceSet(player, 0x2A);
                    Hu3DMotionShiftSet(m233_hostObj->model[0], Hu3DData[m233_hostObj->motion[2]].motId, 0, 10, 0);
                    data->flags |= 1;
                    HuPrcSleep(30);
                    m233_BlockDrop(m233_answerPlayer);
                    HuPrcSleep(70);
                    if (m233_choiceNo == -1) {
                        MgPlayerMotSwap(player, 0x26, 0);
                    }
                    MgPlayerMotForceSet(player, 0x2B);
                    m233_playerFlagTbl[m233_answerPlayer] |= 1;
                    counts[m233_answerPlayer] = 2;
                    HuPrcSleep(20);
                    m233_StunStart(m233_answerPlayer);
                }
                espDispOff(m233_judgeSprTbl[0]);
                espDispOff(m233_judgeSprTbl[1]);
            }
            count = 0;
            for (i = 0; i < 4; i++) {
                player = mgPlayerObjTbl[i];
                if (m233_playerFlagTbl[i] & 1) {
                    counts[i]--;
                    if (round == 9) {
                        counts[i] = 0;
                    }
                    if (counts[i] == 0) {
                        MgPlayerMotForceSet(player, 0x21);
                        m233_StunEnd();
                        count++;
                    }
                }
            }
            if (count != 0) {
                HuPrcSleep(30);
            }
            for (i = 0; i < 4; i++) {
                player = mgPlayerObjTbl[i];
                if (m233_playerFlagTbl[i] & 1) {
                    if (counts[i] == 0) {
                        MgPlayerMotForceSet(player, 0);
                        m233_playerFlagTbl[i] &= ~1;
                    }
                }
            }
            HuPrcSleep(30);
            for (i = 0; i < 4; i++) {
                if (m233_scoreTbl[i] == 3) {
                    m233_winner = i;
                }
            }
            if (m233_winner != -1) {
                break;
            }
        }
        if (m233_endlessF == 0) {
            break;
        }
        m233_questionNoBase += 10;
        m233_QuestionTblCreate();
    }
    if (m233_winner == -1) {
        for (round = 0; round < 2; round++) {
            wins = 2 - round;
            tied = 0;
            m233_winner = -1;
            for (i = 0; i < 4; i++) {
                if (m233_scoreTbl[i] == wins) {
                    tied++;
                    m233_winner = i;
                }
            }
            if (tied == 1) {
                break;
            }
            if (tied > 1) {
                m233_winner = -1;
                break;
            }
        }
    }
    MgFlowStatSet(MG_STATE_FINISH);
    m233_BlockEffStartAll();
    m233_HostTurnSet(2);
    for (i = 0; i < 16; i++) {
        for (round = 0; round < 4; round++) {
            mgPlayerObjTbl[round]->rot.y = i * 12 + 180.0f;
        }
        HuPrcVSleep();
    }
    while (mgFlowResultF != 1) {
        HuPrcVSleep();
    }
    for (round = 0; round < 4; round++) {
        if (round == m233_winner) {
            MgPlayerMotForceSet(mgPlayerObjTbl[round], 0xD);
            HuAudCharVoicePlay(omCharModelNoTbl[GwPlayer[round].chr][0] | 0x2F);
        } else {
            MgPlayerMotForceSet(mgPlayerObjTbl[round], 0xE);
        }
    }
    omDelPrcObj(NULL);
}

void m233_BuzzProc(void) {
    s32 pressed[4];
    s32 count;
    s32 i;

    while (!(m233_quizFlag & 2)) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (m233_playerFlagTbl[i] & 1) {
                continue;
            }
            if (HuPadBtnDown[GwPlayer[i].pad] & A_BUTTON) {
                pressed[count++] = i;
                m233_quizFlag &= ~0x10;
                m233_quizFlag |= 4;
            }
        }
        if (count != 0) {
            m233_answerPlayer = pressed[rand8() % count];
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void m233_BuzzObjMain(omObjData *obj) {
    s32 pressed[4];
    s32 count;
    s32 i;

    if (!(m233_quizFlag & 2)) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (HuPadBtnDown[GwPlayer[i].pad] & A_BUTTON) {
                pressed[count++] = i;
                m233_quizFlag &= ~0x10;
                m233_quizFlag |= 4;
            }
        }
        if (count == 0) {
            return;
        }
        m233_answerPlayer = pressed[rand8() % count];
    }
    omDelObj(obj);
}

const char m233_numFmtStr[] = "%d";
const char m233_timeFmtStr[] = "%02d%c%02d%c%02d";
const char m233_decimalFmtStr[] = "%d%c%02d";

s16 m233_QuestionWinCreate(void) {
    s16 size[2];
    char buf[256];
    s32 mes;
    s16 win;

    mes = m233_questionMesTbl[m233_questionNo];
    sprintf(buf, m233_numFmtStr, m233_questionNo + 1 + m233_questionNoBase);
    HuWinInsertMesSizeGet((u32)buf, 1);
    if (m233_questionFlagTbl[m233_questionNo] & 2) {
        HuWinInsertMesSizeGet(m233_insertMesTbl[m233_questionNo], 0);
    }
    HuWinMesMaxSizeGet(1, size, mes);
    win = HuWinCreate(79, 45, 165, 80, 0, 0);
    m233_questionWinNo = win;
    HuWinAttrSet(win, 64, 64);
    HuWinMesSpeedSet(win, 5);
    HuWinDummy(win);
    HuWinBGTPLvlSet(win, 0);
    HuWinActivePlayerSet(win, 1 << GwPlayer[0].pad);
    HuWinInsertMesSet(win, (u32)buf, 1);
    if (m233_questionFlagTbl[m233_questionNo] & 2) {
        HuWinInsertMesSet(win, m233_insertMesTbl[m233_questionNo], 0);
    }
    HuWinHomeClear(win);
    HuWinMesSet(win, mes, -1, -1);
    return win;
}

s16 m233_ChoiceWinCreate(void) {
    s16 size[2];
    char buf[3][256];
    char *bufs[3];
    s32 mes = 0x533C;
    s32 count = 0;
    s32 i;
    s32 value;
    s32 quotient;
    s32 minutes;
    s32 seconds;
    s32 fraction;
    s16 win;

    if (m233_questionFlagTbl[m233_questionNo] & 1) {
        sprintf(buf[0], m233_numFmtStr, m233_choiceTbl[m233_questionNo][0]);
        sprintf(buf[1], m233_numFmtStr, m233_choiceTbl[m233_questionNo][1]);
        sprintf(buf[2], m233_numFmtStr, m233_choiceTbl[m233_questionNo][2]);
        HuWinInsertMesSizeGet((u32)buf[0], 0);
        HuWinInsertMesSizeGet((u32)buf[1], 1);
        HuWinInsertMesSizeGet((u32)buf[2], 2);
        HuWinInsertMesSizeGet(m233_choiceUnitMesTbl[m233_questionNo], 3);
        count = 1;
    }
    if (m233_questionFlagTbl[m233_questionNo] & 4) {
        bufs[0] = buf[0];
        bufs[1] = buf[1];
        bufs[2] = buf[2];
        for (i = 0; i < 3; i++) {
            value = m233_choiceTbl[m233_questionNo][i];
            quotient = value / 3600;
            value %= 3600;
            minutes = value / 60;
            seconds = value % 60;
            fraction = seconds * 100 / 60;
            if (m233_questionMesTbl[m233_questionNo] == 0x530A) {
                fraction = seconds * 99 / 60;
            }
            sprintf(bufs[i], m233_timeFmtStr, quotient, 0x5C, minutes, 0x5B, fraction);
            HuWinInsertMesSizeGet((u32)bufs[i], i);
        }
        count++;
    }
    if (m233_questionFlagTbl[m233_questionNo] & 0x20) {
        bufs[0] = buf[0];
        bufs[1] = buf[1];
        bufs[2] = buf[2];
        for (i = 0; i < 3; i++) {
            value = m233_choiceTbl[m233_questionNo][i];
            quotient = value / 100;
            value %= 100;
            sprintf(bufs[i], m233_decimalFmtStr, quotient, 0x85, value);
            HuWinInsertMesSizeGet((u32)bufs[i], i);
        }
        count++;
    }
    if (count == 0) {
        for (i = 0; i < 3; i++) {
            HuWinInsertMesSizeGet(m233_choiceTbl[m233_questionNo][i], (s8)i);
        }
    }
    HuWinMesMaxSizeGet(1, size, mes);
    win = HuWinCreate(79, 45, 165, 80, 0, 0);
    HuWinAttrSet(win, 64, 64);
    HuWinMesSpeedSet(win, 0);
    HuWinDummy(win);
    HuWinBGTPLvlSet(win, 0);
    HuWinActivePlayerSet(win, 1 << GwPlayer[0].pad);
    count = 0;
    if (m233_questionFlagTbl[m233_questionNo] & 0x21) {
        HuWinInsertMesSet(win, (u32)buf[0], 0);
        HuWinInsertMesSet(win, (u32)buf[1], 1);
        HuWinInsertMesSet(win, (u32)buf[2], 2);
        HuWinInsertMesSet(win, m233_choiceUnitMesTbl[m233_questionNo], 3);
        count = 1;
    }
    if (m233_questionFlagTbl[m233_questionNo] & 4) {
        HuWinInsertMesSet(win, (u32)buf[0], 0);
        HuWinInsertMesSet(win, (u32)buf[1], 1);
        HuWinInsertMesSet(win, (u32)buf[2], 2);
        count++;
    }
    if (count == 0) {
        for (i = 0; i < 3; i++) {
            HuWinInsertMesSet(win, m233_choiceTbl[m233_questionNo][i], i);
        }
        HuWinInsertMesSet(win, m233_choiceUnitMesTbl[m233_questionNo], 3);
    }
    HuWinHomeClear(win);
    HuWinMesSet(win, mes, -1, -1);
    return win;
}

void m233_CountdownProc(void) {
    s32 timer;
    s32 mode;
    s32 i;

    m233_countdown = 5;
    timer = 30;
    while (TRUE) {
        if (m233_quizFlag & 0x10) {
            mode = 1;
            break;
        }
        if (m233_quizFlag & 4) {
            mode = 2;
            break;
        }
        HuPrcVSleep();
    }
    GMesPosSet(GMesCreate(GMES_MES_TIMER, m233_countdown, 160, 28), 154.0f, 28.0f);
    while (m233_countdown > 0) {
        if (--timer == 0) {
            timer = 30;
            m233_countdown--;
        }
        GMesTimerValueSet(m233_countdownS16);
        if (mode == 1 && (m233_quizFlag & 4)) {
            m233_countdown = 5;
            timer = 30;
            mode = 3;
        }
        if (m233_choiceNo != -1 || m233_countdown == 0) {
            break;
        }
        HuPrcVSleep();
    }
    m233_quizFlag = (m233_quizFlag | 2) & ~0x14;
    m233_buzzLockF = 1;
    if (m233_countdown == 0) {
        m233_quizFlag &= ~0x20;
        for (i = 0; i < 4; i++) {
            MgPlayerVelYSet(mgPlayerObjTbl[i], 1000.0f);
        }
    }
    GMesTimerEnd();
    omDelPrcObj(NULL);
}

s32 m233_PlayerOnStandCheck(s32 index) {
    s32 result = 0;
    if (mgPlayerObjTbl[index]->trans.y == m233_standObjTbl[index]->trans.y) {
        result = 1;
    }
    return result;
}

void m233_EndlessDispObjMain(omObjData *obj);

void m233_EndlessDispCreate(void) {
    omObjData *obj = omAddObj(0xA, 0, 0, -1, m233_EndlessDispObjMain);
    s32 *value = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);

    obj->data = value;
    *value = 0;
}

const char m233_endlessStr[] = "ENDLESS";

void m233_EndlessDispObjMain(omObjData *obj) {
    s32 *counter = obj->data;

    if (((*counter += 1) & 0x10) != 0) {
        fontcolor = FONT_COLOR_WHITE;
        sprintf(omDBGStrBuf, m233_endlessStr);
        print8(0xE8, 0x10, omDBGStrBuf);
    }
}

void m233_WinPauseObjMain(omObjData *obj) {
    if (omPauseChk() + omAllPauseF != 0) {
        if (m233_questionWin != -1) {
            HuWinDispOff(m233_questionWin);
        }
    } else if (m233_questionWin != -1) {
        HuWinDispOn(m233_questionWin);
    }
}

const char m233_motionErrorStr[] = "MOTION ERROR! WINNER=%d\n";
const char m233_emptyStr[] = "";

void m233_MotionErrorPrint(void) {
    fontcolor = FONT_COLOR_WHITE;
    sprintf(omDBGStrBuf, m233_motionErrorStr, m233_winner);
    print8(0x20, 0xB0, omDBGStrBuf);
}
