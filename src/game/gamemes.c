#include "game/gamemes.h"
#include "game/audio.h"
#include "game/sprite.h"
#include "game/gamework_data.h"
#include "game/data.h"
#include "humath.h"
#include "stdarg.h"
#include "gcc/string.h"
#include "include_asm.h"
#include "macros.h"
#include "game/window.h"
#include "game/malloc.h"

/* Per-character animation work for the GMES_MES_3..10 / 14..21 message families. */
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 startX;
    /* 0x0C */ f32 startY;
    /* 0x10 */ f32 endX;
    /* 0x14 */ f32 endY;
    /* 0x18 */ f32 velX;
    /* 0x1C */ f32 velY;
    /* 0x20 */ f32 scaleX;
    /* 0x24 */ f32 scaleY;
    /* 0x28 */ f32 angle;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ u8 alpha;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ u32 time;
} GMesChar; // Size 0x3C

extern Gfx *gMainGfxPos;
extern s8 Hu3DPauseF;


extern u16 omSysExitReq;
extern u16 omMgActiveF;
extern u8 omSysPauseDisableF;

// unreferenced
u8 gMesUnkTbl[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01,
    0xFF, 0x01, 0x00, 0x00, 0x03, 0x01, 0x01, 0x03, 0x01, 0x03, 0xFF, 0x03, 0x01, 0x01, 0x03, 0x00,
    0x03, 0x03, 0xFF, 0x00, 0x00, 0x00, 0x03, 0x00, 0x03, 0x01, 0x02, 0x00, 0xFF, 0x03, 0x03, 0x03,
    0x03, 0x00, 0x01, 0x02, 0x01, 0x01, 0x01, 0x03, 0x03, 0x01, 0x03, 0x03, 0x00, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x02, 0x03, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x02, 0x02,
};

static u8 gMesKanaTbl[] = {
    0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0,
    0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0x86, 0xBD, 0x87, 0x88,
    0x89, 0x8A, 0x8B, 0x8F, 0x8C, 0x8D, 0x8E,
};

static u8 gMesKanaDakuTbl[] = {
    0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
};

// "START" character start positions
static Vec2f gMesStart4CharPos[] = {
    { -248.0f, -208.0f }, { 248.0f, 208.0f }, { 248.0f, -240.0f }, { -248.0f, 32.0f }, { -248.0f, -98.0f }, { 0.0f, 0.0f },
};

/* volatile is required to match: CreateFontChar's search loop re-extends each loaded byte (lbu + andi). */
volatile u8 gMesKanjiTbl[] = {
    0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xD1,
    0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1,
    0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
};

// "FINISH" character start positions
static Vec2f gMesFinish15CharPos[] = {
    { -256.0f, 0.0f }, { 256.0f, 216.0f }, { 256.0f, -60.0f }, { -256.0f, 24.0f },
    { 64.0f, -216.0f }, { -256.0f, -216.0f }, { 0.0f, 0.0f },
};

static s8 gMesUnkF;
static u8 gMesCloseF;
static u8 GameMesDebugF;
static s8 gMesTimerId;
static u16 GameMesTime;
static s16 gMesImageAnim[9];
static s16 gMesImageAnimAlt[9];
/* Character sprite tables; the CreateFontChar asm indexes them by character code (see undefined_syms.txt).
 * Global for that alias, and aligned to match the placement they get as statics. */
s16 gMesFontLowerAnim[27] BSS ALIGNED(8);
s16 gMesFontUpperAnim[27] BSS ALIGNED(8);
s16 gMesFontUpperAltAnim[27] BSS ALIGNED(8);
static s16 gMesFontKanaAnim[16];
static s16 gMesFontKanaAltAnim[16];
static s16 gMesFontKanjiAnim[37];
static GMesChar gMesCharData[32];
extern GAMEMES gMesData[];
extern s32 omovl;

s32 GMesMgNoGet(void) {
    return GwSystem.minigame_index;
}

void GMesInit(void) {
    s16 i;

    gMesUnkF = 0;
    for (i = 0; i < 8; i++) {
        gMesData[i].mesNo = 0;
    }
    for (i = 0; i < 9; i++) {
        gMesImageAnim[i] = gMesImageAnimAlt[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        gMesFontLowerAnim[i] = gMesFontUpperAnim[i] = gMesFontUpperAltAnim[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        gMesFontKanaAnim[i] = gMesFontKanaAltAnim[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        gMesFontKanjiAnim[i] = -1;
    }
    gMesCloseF = FALSE;
    gMesTimerId = -1;
    GameMesDebugF = 0;
}

void GMesExec(Gfx **arg0) {
    s16 result = FALSE;
    s16 i, j;

    if (Hu3DPauseF != 0 && !gMesCloseF) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (gMesData[i].stat != GMES_STAT_NONE) {
            GAMEMES *gMes = &gMesData[i];

            switch (gMes->mesNo) {
                case GMES_MES_0:
                    result = GameMesStart0Exec(gMes, arg0);
                    break;
                case GMES_MES_1:
                    result = GameMesStart1Exec(gMes, arg0);
                    break;
                case GMES_MES_2:
                    result = GameMesStart2Exec(gMes, arg0);
                    break;
                case GMES_MES_3:
                    result = GameMesStart3Exec(gMes, arg0);
                    break;
                case GMES_MES_4:
                    result = GameMesStart4Exec(gMes, arg0);
                    break;
                case GMES_MES_5:
                    result = GameMesStart5Exec(gMes, arg0);
                    break;
                case GMES_MES_MG_START:
                    result = GameMesMgStartExec(gMes, arg0);
                    break;
                case GMES_MES_7:
                    result = GameMesStart7Exec(gMes, arg0);
                    break;
                case GMES_MES_8:
                    result = GameMesStart8Exec(gMes, arg0);
                    break;
                case GMES_MES_9:
                    result = GameMesStart9Exec(gMes, arg0);
                    break;
                case GMES_MES_10:
                    result = GameMesStart10Exec(gMes, arg0);
                    break;
                case GMES_MES_11:
                    result = GameMesFinish11Exec(gMes, arg0);
                    break;
                case GMES_MES_12:
                    result = GameMesFinish12Exec(gMes, arg0);
                    break;
                case GMES_MES_13:
                    result = GameMesTimeUpExec(gMes, arg0);
                    break;
                case GMES_MES_14:
                    result = GameMesFinish14Exec(gMes, arg0);
                    break;
                case GMES_MES_15:
                    result = GameMesFinish15Exec(gMes, arg0);
                    break;
                case GMES_MES_16:
                    result = GameMesFinish16Exec(gMes, arg0);
                    break;
                case GMES_MES_MG_FINISH:
                    result = GameMesMgFinishExec(gMes, arg0);
                    break;
                case GMES_MES_18:
                    result = GameMesFinish18Exec(gMes, arg0);
                    break;
                case GMES_MES_19:
                    result = GameMesFinish19Exec(gMes, arg0);
                    break;
                case GMES_MES_20:
                    result = GameMesFinish20Exec(gMes, arg0);
                    break;
                case GMES_MES_21:
                    result = GameMesFinish21Exec(gMes, arg0);
                    break;
                case GMES_MES_MG_LOSER:
                    result = GameMesMgLoserExec(gMes, arg0);
                    break;
                case GMES_MES_24:
                    result = GameMes24Exec(gMes, arg0);
                    break;
                case GMES_MES_25:
                    result = GameMes25Exec(gMes, arg0);
                    break;
                case GMES_MES_TIMER:
                    result = GMesTimerExec(gMes, arg0);
                    break;
                case GMES_MES_MG_RECORD:
                    result = GameMesMgRecordExec(gMes, arg0);
                    break;
                case GMES_MES_31:
                    result = GameMesTimeUp2Exec(gMes, arg0);
                    break;
                case GMES_MES_33:
                    result = GameMesGoalExec(gMes, arg0);
                    break;
                case GMES_MES_29:
                    result = GameMesGameOverExec(gMes, arg0);
                    break;
                case GMES_MES_28:
                    result = GameMesReadyGoExec(gMes, arg0);
                    break;
                case GMES_MES_MG_DRAW:
                    result = GameMesMgDrawExec(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNER:
                    result = GameMesMgWinnerExec(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_2:
                    result = GameMesMgWinners2Exec(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_3:
                    result = GameMesMgWinners3Exec(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_4:
                    result = GameMesMgWinners4Exec(gMes, arg0);
                    break;
                case GMES_MES_36:
                    result = GameMesGotItemExec(gMes, arg0);
                    break;
                case GMES_MES_37:
                    result = GameMesGotItem2Exec(gMes, arg0);
                    break;
            }
            gMes->time++;
            if (gMes->time >= 0x4000) {
                gMes->time = 0x2000;
            }
            if (result == FALSE) {
                gMes->stat = GMES_STAT_NONE;
                if (GameMesDebugF == 0) {
                    for (j = 0; j < GMES_MAX; j++) {
                        if (gMesData[j].stat != GMES_STAT_NONE && gMesData[j].mesNo != GMES_MES_TIMER) {
                            break;
                        }
                    }
                    if (j == GMES_MAX) {
                        GameMesStub();
                    }
                }
            }
        }
    }
}

s16 GMesCreate(s16 mesNo, ...) {
    GAMEMES *gMes;
    va_list args;
    s32 chr;
    s16 mesId;
    s16 i;

    va_start(args, mesNo);
    for (mesId = 0; mesId < GMES_MAX; mesId++) {
        if (gMesData[mesId].stat == GMES_STAT_NONE) {
            break;
        }
    }
    if (mesId == GMES_MAX) {
        return GMES_ID_NONE;
    }
    gMes = &gMesData[mesId];
    gMes->stat = GMES_STAT_EXIST;
    gMes->mesNo = mesNo;
    gMes->time = 0;
    gMes->pos.x = 160.0f;
    gMes->pos.y = 120.0f;
    gMes->scale.y = 1.0f;
    gMes->scale.x = 1.0f;
    gMes->angle = 0;
    gMes->tpLvl = 0xFF;
    gMes->timeMax = 0x3C;
    gMes->unk0E = 0;
    gMes->unk0C = 0;
    gMes->work = 0;
    gMes->subMode = 0;
    gMes->unk10 = gMes->unk14 = 0.0f;
    for (i = 0; i < GMES_STRMAX; i++) {
        gMes->strSprId[i] = gMes->strGId[i] = HUSPR_NONE;
    }
    switch (mesNo) {
        case GMES_MES_0:
        case GMES_MES_1:
        case GMES_MES_2:
        case GMES_MES_11:
        case GMES_MES_12:
        case GMES_MES_13:
        case GMES_MES_31:
        case GMES_MES_33:
            gMes->timeMax = 0x2D;
            break;
        case GMES_MES_MG_DRAW:
            gMes->timeMax = 0x82;
            break;
        case GMES_MES_MG_RECORD:
            gMes->pos.x = 160.0f;
            gMes->pos.y = 180.0f;
            break;
        case GMES_MES_MG_WINNER:
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->pos.y = GameMesOvlTypeGet();
            gMes->timeMax = 0x78;
            break;
        case GMES_MES_29:
        case GMES_MES_36:
        case GMES_MES_37:
            gMes->timeMax = 0x78;
            break;
        case GMES_MES_MG_LOSER:
            gMes->unk0E = chr = va_arg(args, s32);
            break;
        case GMES_MES_24:
        case GMES_MES_25:
            gMes->unk1C = va_arg(args, s32);
            gMes->pos.x = va_arg(args, s32);
            gMes->pos.y = va_arg(args, s32);
            gMes->scale.x = va_arg(args, f64);
            gMes->scale.y = va_arg(args, f64);
            gMes->unk02 = va_arg(args, s32);
            break;
        case GMES_MES_TIMER:
            gMesTimerId = mesId;
            gMes->subMode = va_arg(args, s32);
            gMes->pos.x = va_arg(args, s32);
            gMes->pos.y = va_arg(args, s32);
            gMes->pos.x = 160.0f;
            gMes->pos.y = 28.0f;
            break;
        case GMES_MES_MG_WINNERS_2:
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->timeMax = 0x78;
            break;
        case GMES_MES_MG_WINNERS_3:
            gMes->work = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->pos.y = GameMesOvlOfsGet();
            gMes->timeMax = 0x78;
            break;
        case GMES_MES_MG_WINNERS_4:
            gMes->subMode = chr = va_arg(args, s32);
            gMes->work = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->timeMax = 0x78;
            break;
    }
    GameMesTime = 0x5A;
    va_end(args);
    return mesId;
}

s32 GMesStatGet(void) {
    s16 stat;
    s16 i;

    for (i = 0, stat = GMES_STAT_NONE; i < GMES_MAX; i++) {
        if (gMesData[i].mesNo != GMES_MES_TIMER) {
            stat |= gMesData[i].stat;
        }
    }
    return stat;
}

u8 GMesStatIdGet(s16 i) {
    return gMesData[i].stat;
}

void GMesTimeMaxSet(s16 i, s16 value) {
    if (value == -1) {
        value = 0x7FFF;
    }
    gMesData[i].timeMax = value;
}

void GMesPosSet(s16 i, f32 x, f32 y) {
    gMesData[i].pos.x = x;
    gMesData[i].pos.y = y;
}

void GMesKill(s16 i) {
    if (gMesData[i].stat != GMES_STAT_NONE) {
        gMesData[i].stat = GMES_STAT_KILL;
    }
}

void GMesClose(void) {
    gMesTimerId = -1;
    gMesCloseF = TRUE;
    GMesExec(&gMainGfxPos);
    gMesCloseF = FALSE;
    GameMesStub();
    GameMesDebugF = 0;
}

s32 GameMesKillCheck(void) {
    s32 stat;
    s16 countdown;

    if (Hu3DPauseF != 0) {
        return TRUE;
    }
    if (omSysExitReq != 0) {
        return TRUE;
    }
    stat = GMesStatGet();
    if (stat == GMES_STAT_NONE || (stat & GMES_STAT_TIMEEND) != 0) {
        countdown = GameMesTime - 1;
        GameMesTime = countdown;
        if (countdown < 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void GMesMaxWaitSet(s16 countdown) {
    GameMesTime = countdown;
}

void GameMesStub(void) {
    s16 i;

    for (i = 0; i < 9; i++) {
        if (i == 2 && gMesTimerId != -1) {
            continue;
        }
        if (gMesImageAnim[i] != -1) {
            HuSprAnimKill(gMesImageAnim[i]);
        }
        if (gMesImageAnimAlt[i] != -1) {
            HuSprAnimKill(gMesImageAnimAlt[i]);
        }
        gMesImageAnim[i] = gMesImageAnimAlt[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        if (gMesFontLowerAnim[i] != -1) {
            HuSprAnimKill(gMesFontLowerAnim[i]);
        }
        if (gMesFontUpperAnim[i] != -1) {
            HuSprAnimKill(gMesFontUpperAnim[i]);
        }
        if (gMesFontUpperAltAnim[i] != -1) {
            HuSprAnimKill(gMesFontUpperAltAnim[i]);
        }
        gMesFontLowerAnim[i] = gMesFontUpperAnim[i] = gMesFontUpperAltAnim[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        if (gMesFontKanaAnim[i] != -1) {
            HuSprAnimKill(gMesFontKanaAnim[i]);
        }
        if (gMesFontKanaAltAnim[i] != -1) {
            HuSprAnimKill(gMesFontKanaAltAnim[i]);
        }
        gMesFontKanaAnim[i] = gMesFontKanaAltAnim[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        if (gMesFontKanjiAnim[i] != -1) {
            HuSprAnimKill(gMesFontKanjiAnim[i]);
        }
        gMesFontKanjiAnim[i] = -1;
    }
}

void GMesSprKill(GAMEMES *gMes) {
    s16 i;

    for (i = 0; i < 16; i++) {
        if (gMes->strGId[i] != -1) {
            HuSprGrpKill(gMes->strGId[i]);
        }
        if (gMes->strSprId[i] != -1) {
            HuSprAnimKill(gMes->strSprId[i]);
        }
    }
}

s32 GameMesStart0Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len = strlen("START");
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, "START", 1, -1, -1);
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 0.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 0);
            }
            gMes->subMode = 1;
            break;
        case 1:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, gMes->time * 0.05f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->time * 12);
            }
            if (gMes->time >= 20) {
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            }
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 3;
                gMes->work = 0;
            }
            break;
        case 3:
            gMes->stat = GMES_STAT_TIMEEND;
            gMes->work += 6;
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, cosdf(gMes->work));
            }
            if (gMes->time >= gMes->timeMax) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                }
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            omSysPauseDisableF = 0;
            omMgActiveF = 1;
            result = FALSE;
            break;
    }
    if (gMes->time == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->time == 38) {
        GameMesMgStub(GMesMgNoGet());
    }
    return result;
}

s32 GameMesStart1Exec(GAMEMES *gMes, Gfx **gfx) {
    char *str = "START";
    s32 len = strlen(str);
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 3;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, str, 1, -1, -1);
            gMes->scale.y = gMes->scale.x = 0.3f;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            gMes->tpLvl = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->subMode = 1;
            gMes->work = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->scale.x = gMes->unk10 + 0.3f;
            gMes->scale.y = gMes->unk10 + 0.3f;
            gMes->pos.y = 120.0f - sindf(gMes->work) * 20.0f;
            gMes->tpLvl += 12;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->work += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->time >= 20) {
                gMes->subMode = 2;
                HuSprPosSet(gMes->strGId[0], 0, 160, 120);
                for (i = 0; i < len; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            }
            break;
        case 2:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            omSysPauseDisableF = 0;
            omMgActiveF = 1;
            result = FALSE;
            break;
    }
    if (gMes->time == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->time == 38) {
        GameMesMgStub(GMesMgNoGet());
    }
    return result;
}

s32 GameMesStart2Exec(GAMEMES *gMes, Gfx **gfx) {
    char *str = "START";
    s32 len = strlen(str);
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, str, 1, -1, -1);
            gMes->scale.y = gMes->scale.x = 0.3f;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 40.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 0);
            }
            gMes->subMode = 1;
            gMes->work = 0;
            gMes->unk0C = 0;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            gMes->scale.x = gMes->unk10 + 0.3f;
            gMes->scale.y = gMes->unk10 + 0.3f;
            gMes->pos.x = 160.0f;
            gMes->pos.y += gMes->unk14;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, sindf(gMes->unk0C) * 255.0f);
            }
            gMes->unk0C += 6;
            gMes->unk10 += 0.7f / 15;
            gMes->unk14 += 0.8f;
            if (gMes->pos.y >= 120.0f) {
                gMes->pos.y = 120.0f;
                gMes->unk14 = -5.0f;
                HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
                for (i = 0; i < len; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                gMes->subMode = 2;
            }
            break;
        case 2:
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            gMes->pos.y += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->pos.y >= 120.0f) {
                gMes->pos.y = 120.0f;
                gMes->unk14 = -3.0f;
                HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
                gMes->subMode = 3;
            }
            break;
        case 3:
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            gMes->pos.y += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->pos.y >= 120.0f) {
                gMes->pos.y = 120.0f;
                HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
                gMes->subMode = 4;
            }
            break;
        case 4:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            omSysPauseDisableF = 0;
            omMgActiveF = 1;
            result = FALSE;
            break;
    }
    if (gMes->time == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->time == 38) {
        GameMesMgStub(GMesMgNoGet());
    }
    return result;
}

/*
 * Shared state handling for the GMES_MES_3..10 "START" variants. State 0 resets the
 * per-character work and builds the string sprites, state 6 tears everything down.
 * The callers implement the remaining states (1: animate in, 2: hold, 5: shrink out).
 * The empty cases are needed for the compiler to emit the original jump tables.
 */
s32 GameMesStartStrCreate(GAMEMES *gMes) {
    s32 len = strlen("START");
    s32 result;
    s32 i;
    GMesChar *chr;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 6;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            for (i = 0; i < 32; i++) {
                chr = &gMesCharData[i];
                chr->x = chr->y = chr->velX = chr->velY = chr->angle = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 128;
                chr->unk34 = 0;
                chr->time = 0;
            }
            GameMesStrCreate(gMes, "START", 1, -1, -1);
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
            }
            gMes->time = gMes->work = gMes->unk0C = gMes->unk0E = 0;
            gMes->timeMax = 0;
            gMes->pos.x = gMes->pos.y = 0.0f;
            gMes->scale.x = gMes->scale.y = 1.0f;
            gMes->angle = 0.0f;
            gMes->unk1C = 0;
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            GMesSprKill(gMes);
            omSysPauseDisableF = 0;
            omMgActiveF = 1;
            result = FALSE;
            break;
    }
    if (gMes->time == 60) {
        HuAudFXPlay(0x251);
    }
    if (gMes->time == 80) {
        GameMesMgStub(GMesMgNoGet());
    }
    return result;
}

s32 GameMesStart3Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len = strlen("START");
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesStartStrCreate(gMes);
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->angle = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                HuSprAttrSet(gMes->strGId[0], i + 1, 2);
            }
            gMes->subMode = 1;
            break;
        case 1:
            chr = &gMesCharData[0];
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->time > 10) {
                chr->angle += 18.0f;
                if (chr->angle > 360.0f) {
                    chr->angle -= 360.0f;
                }
                scale = cosdf(chr->angle);
                if (scale < 0.0f) {
                    scale = -scale;
                    for (i = 0; i < len; i++) {
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                } else {
                    for (i = 0; i < len; i++) {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                }
            } else {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            for (i = 0; i < len; i++) {
                HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart4Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;
    f32 t;

    result = GameMesStartStrCreate(gMes);
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->startX = chr->x = gMesStart4CharPos[i].x;
                chr->startY = chr->y = gMesStart4CharPos[i].y;
                chr->endX = i * 22 - (len - 1) * 11;
                chr->endY = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            gMes->unk0C = 0;
            gMes->work = 0;
            break;
        case 1:
            if (gMes->time > 60) {
                gMes->subMode = 2;
                gMes->unk0C = 0;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    t = 0.0f;
                    if (gMes->time > 30.0f / len * i) {
                        if (chr->time > 30) {
                            t = 1.0f;
                        } else {
                            t = chr->time * (1.0f / 30.0f);
                            chr->time++;
                        }
                    }
                    chr->x = t * (chr->endX - chr->startX) + chr->startX;
                    chr->y = t * (chr->endY - chr->startY) + chr->startY;
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart5Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesStartStrCreate(gMes);
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                HuSprAttrSet(gMes->strGId[0], i + 1, 2);
            }
            gMes->subMode = 1;
            gMes->unk0E = 0;
            gMes->unk0C = 0;
            gMes->work = 0;
            break;
        case 1:
            if (gMes->time > 60) {
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->time > 10) {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    if (gMes->time - 10 > 50.0f / len * i) {
                        if (chr->time > 50.0f / len) {
                            scale = 1.0f;
                            chr->angle = 0.0f;
                        } else {
                            chr->time++;
                            chr->angle += 18.0f;
                            if (chr->angle > 360.0f) {
                                chr->angle -= 360.0f;
                            }
                            scale = cosdf(chr->angle);
                        }
                    } else {
                        chr->time = 0;
                        chr->angle = 180.0f;
                        scale = -1.0f;
                    }
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                }
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->time = 0;
                    HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesMgStartExec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesStartStrCreate(gMes);
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.3f, 0.3f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 128);
            }
            gMes->subMode = 1;
            break;
        case 1:
            if (gMes->time > 60) {
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->time > 38) {
                scale = 1.0f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else if (gMes->time > 30) {
                scale = 1.5f - (gMes->time - 30.0f) * 0.5f * 0.125f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else if (gMes->time > 10) {
                scale = (gMes->time - 10) * 1.2f * 0.05f + 0.3f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else {
                scale = 0.3f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            }
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart7Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesStartStrCreate(gMes);
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = -120.0f - i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            if (gMes->time > 60) {
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->work == 0) {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    if (chr->unk34 == 0) {
                        chr->velY += 0.71999997f;
                        chr->y += chr->velY;
                        if (chr->y > 0.0f) {
                            chr->y = chr->velY = -chr->velY * 0.5f;
                            chr->unk34 = 1;
                        }
                    } else {
                        chr->velY += 0.71999997f;
                        chr->y += chr->velY;
                        if (chr->y > 0.0f) {
                            chr->y = 0.0f;
                            chr->velY = 0.0f;
                        }
                    }
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart8Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesStartStrCreate(gMes);
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 144.0f + i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            if (gMes->time > 60) {
                gMes->subMode = 2;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->work == 0) {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    if (chr->unk34 == 0) {
                        chr->velY += -0.71999997f;
                        chr->y += chr->velY;
                        if (chr->y < 0.0f) {
                            chr->y = chr->velY = chr->velY * 0.5f;
                            chr->unk34 = 1;
                        }
                    } else {
                        chr->velY += 0.71999997f;
                        chr->y += chr->velY;
                        if (chr->y > 0.0f) {
                            chr->y = 0.0f;
                            chr->velY = 0.0f;
                        }
                    }
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart9Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;
    f32 t;
    f32 startX, startY;
    f32 endX, endY;
    f32 left, right;
    f32 top, bottom;
    f32 x, y;

    endY = endX = startX = startY = 0.0f;
    result = GameMesStartStrCreate(gMes);
    t = 1.0f;
    left = 55.0f;
    right = 265.0f;
    top = 12.0f;
    bottom = 228.0f;
    len = strlen("START");
    switch (gMes->subMode) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 128);
            }
            HuSprPosSet(gMes->strGId[0], 0, 0, 0);
            gMes->subMode = 1;
            gMes->work = 0;
            gMes->unk0C = 0;
            break;
        case 1:
            if (gMes->work < 4) {
                if (gMes->work == 0) {
                    startX = left;
                    startY = top;
                    endX = right;
                    endY = (bottom - startY) * 0.5f;
                    if (gMes->unk0C < 5) {
                        t = gMes->unk0C * 0.2f;
                        gMes->unk0C++;
                    } else {
                        gMes->work = 1;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->work == 1) {
                    startX = right;
                    startY = (bottom - top) * 0.5f;
                    endX = (startX - left) * 0.5f;
                    endY = bottom;
                    if (gMes->unk0C < 7) {
                        t = gMes->unk0C * (1.0f / 7.0f);
                        gMes->unk0C++;
                    } else {
                        gMes->work = 2;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->work == 2) {
                    startX = (right - left) * 0.5f;
                    startY = bottom;
                    endX = left;
                    endY = 120.0f;
                    if (gMes->unk0C < 8) {
                        t = gMes->unk0C * 0.125f;
                        gMes->unk0C++;
                    } else {
                        gMes->work = 3;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->work == 3) {
                    startX = left;
                    startY = 120.0f;
                    endX = 160.0f;
                    endY = 120.0f;
                    if (gMes->unk0C < 10) {
                        t = gMes->unk0C * 0.1f;
                        gMes->unk0C++;
                    } else {
                        gMes->work = 4;
                        gMes->unk0C = 0;
                    }
                }
                x = (endX - startX) * t + startX;
                y = (endY - startY) * t + startY;
            } else {
                x = 160.0f;
                y = 120.0f;
                gMes->subMode = 2;
                gMes->unk0C = 0;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->alpha = 255;
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, x, y);
            break;
        case 2:
            if (gMes->time >= 90) {
                gMes->subMode = 5;
                gMes->work = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->work < 6) {
                scale = cosdf(gMes->work * 15.0f);
                gMes->work++;
            } else {
                scale = 0.0f;
                gMes->subMode = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = GMES_STAT_TIMEEND;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesStart10Exec(GAMEMES *gMes, Gfx **gfx) {
    return GameMesStart9Exec(gMes, gfx);
}

s16 GameMesStrInit(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4) {
    s16 i;

    for (i = 0; i < GMES_STRMAX; i++) {
        gMes->strSprId[i] = gMes->strGId[i] = HUSPR_NONE;
    }
    return GameMesStrCreate(gMes, str, flags, arg3, arg4);
}

s16 GameMesStrCreate(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4) {
    return GameMesStrCreateScale(gMes, (u8 *)str, flags, arg3, arg4, 1.0f, 1.0f);
}

s16 GameMesStrCreateScale(GAMEMES *gMes, u8 *str, u8 flags, s16 x, s16 y, f32 scaleX, f32 scaleY) {
    s16 grp;
    s16 animId = -1;
    s16 len;
    s16 i;
    s16 member;
    s16 width;
    s16 charW;
    s16 ofsY;
    u32 code;
    u8 *p;

    len = HuWinStrLen(str);
    for (i = 0; i < GMES_STRMAX; i++) {
        if (gMes->strSprId[i] == HUSPR_NONE && gMes->strGId[i] == HUSPR_NONE) {
            break;
        }
    }
    grp = gMes->strGId[i] = HuSprGrpCreate(len + 1, 5);
    charW = (flags & 1) ? 22 : 15;
    for (p = str, width = 0; *p != 0; p++) {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 0xD0 && *p <= 0xEF)) {
            width += 10;
        } else if (*p == 0x5C) {
            width += (charW == 15) ? 4 : 8;
        } else if (*p == 0x10 || *p == 0x20) {
            width += (charW == 15) ? 8 : 11;
        } else {
            width += charW;
        }
    }
    if (x == -1) {
        x = -(width / 2) + (charW * scaleX) / 2.0f;
    } else {
        x = -x * scaleX;
    }
    if (y == -1) {
        y = 0;
    } else {
        y = -y * scaleY;
    }
    for (member = 1; *str != 0; member++) {
        code = GameMesCharCreate(str, flags);
        animId = code >> 16;
        HuSprGrpMemberSet(grp, member, animId, code & 0xFF);
        ofsY = 0;
        if (*str >= 0xD0 && *p < 0xF0) {
            ofsY = -2;
        }
        HuSprPosSet(grp, member, x, ofsY);
        HuSprTPLvlSet(grp, member, 255);
        HuSprPriSet(grp, member, 5);
        HuSprAttrReset(grp, member, 0xFFFF);
        HuSprAttrSet(grp, member, 0x1008);
        if ((*str >= 'a' && *str <= 'z') || (*str >= 0xD0 && *str <= 0xEF)) {
            x += 10;
        } else if (*str == 0x5C) {
            x += (charW == 15) ? 8 : 12;
        } else if (*str == 0x10 || *str == 0x20) {
            x += (charW == 15) ? 8 : 11;
        } else {
            x += charW * scaleX;
        }
        HuSprParentSet(grp, member, 0);
        if (str[1] == 0x80 || str[1] == 0x81) {
            str++;
        }
        str++;
    }
    HuSprGrpMemberSet(grp, 0, animId, 0);
    HuSprDispOff(grp, 0);
    HuSprParentSet(grp, 0, -1);
    return i;
}

u32 GameMesCharCreate(u8 *str, u8 flags) {
    u8 c = str[0];
    s32 idx = 0;
    s32 type;
    s16 animId;

    type = GameMesCharFileGet(str, 0, &idx);
    if (type == 2) {
        if (flags & 1) {
            if (gMesImageAnimAlt[2] == -1) {
                animId = gMesImageAnimAlt[2] = GameMesAnimRead(0x87);
            } else {
                animId = gMesImageAnimAlt[2];
            }
        } else {
            if (gMesImageAnim[2] == -1) {
                animId = gMesImageAnim[2] = GameMesAnimRead(0x86);
            } else {
                animId = gMesImageAnim[2];
            }
        }
    } else if (type == 4) {
        if (gMesImageAnim[4] == -1) {
            animId = gMesImageAnim[4] = GameMesAnimRead(0x88);
        } else {
            animId = gMesImageAnim[4];
        }
    } else if (type == 5) {
        if (gMesImageAnim[5] == -1) {
            animId = gMesImageAnim[5] = GameMesAnimRead(0x89);
        } else {
            animId = gMesImageAnim[5];
        }
    } else if (type == 6) {
        if (gMesImageAnim[6] == -1) {
            animId = gMesImageAnim[6] = GameMesAnimRead(0x8A);
        } else {
            animId = gMesImageAnim[6];
        }
    } else if (type == 7) {
        if (gMesImageAnim[7] == -1) {
            animId = gMesImageAnim[7] = GameMesAnimRead(0x8B);
        } else {
            animId = gMesImageAnim[7];
        }
    } else if (type == 8) {
        animId = CreateFontChar(c, flags);
    } else if (type == 0) {
        animId = CreateFontChar(c, flags);
    } else if (type == 1) {
        animId = CreateFontChar(c, flags);
    } else {
        idx = 0;
        animId = CreateFontChar(c, flags);
    }
    return (animId << 16) | idx;
}

s32 GameMesCharFileGet(u8 *str, s32 flags, s32 *idx) {
    u16 c = str[0];
    u8 next = str[1];
    s32 i;

    *idx = 0;
    if (c >= 'A' && c <= 'Z') {
        *idx = c - 'A';
        return 0;
    }
    if (c >= 'a' && c <= 'z') {
        *idx = c - 'a';
        return 1;
    }
    if (c >= '0' && c <= '9') {
        *idx = c - '0';
        return 2;
    }
    if (flags == 0) {
        if (c >= 0x86 && c <= 0xBD) {
            if (next == 0x80 || next == 0x81) {
                for (i = 0; i < 20; i++) {
                    if (c == gMesKanaDakuTbl[i]) {
                        break;
                    }
                }
                if (next == 0x81) {
                    i += 5;
                }
                *idx = i;
                return 5;
            }
            for (i = 0; i < 55; i++) {
                if (c == gMesKanaTbl[i]) {
                    break;
                }
            }
            *idx = i;
            return 4;
        }
        if (c >= 0xC6 && c <= 0xFD) {
            c -= 0x40;
            if (next == 0x80 || next == 0x81) {
                for (i = 0; i < 20; i++) {
                    if (c == gMesKanaDakuTbl[i]) {
                        break;
                    }
                }
                if (next == 0x81) {
                    i += 5;
                }
                *idx = i;
                return 7;
            }
            for (i = 0; i < 55; i++) {
                if (c == gMesKanaTbl[i]) {
                    break;
                }
            }
            *idx = i;
            return 6;
        }
    } else {
        if (c >= 0x90 && c <= 0xAF) {
            return 8;
        }
        if (c >= 0xD0 && c <= 0xEF) {
            return 8;
        }
    }
    switch (c) {
        case 0x7D:
            *idx = 6;
            break;
        case 0x5C:
            *idx = 5;
            break;
        case 0x82:
            *idx = 10;
            break;
        case 0x84:
            *idx = 2;
            break;
        case 0x85:
            *idx = 7;
            break;
        case 0xC2:
            *idx = 1;
            break;
        case 0xC4:
            *idx = 1;
            break;
        case 0xC3:
        case 0xC5:
            *idx = 3;
            break;
        case 0xC6:
            *idx = 8;
            break;
        case 0xC7:
            *idx = 9;
            break;
        case 0x3D:
            *idx = 4;
            break;
    }
    return 3;
}

s32 GameMesCharWidthGet(u8 *str, s32 mode, u8 flags, s32 *width) {
    s32 c = str[0];
    u8 next = str[1];
    s32 w;

    w = (flags & 1) ? 22 : 15;
    *width = w;
    if (c >= 'A' && c <= 'Z') {
        *width = w;
        return 0;
    }
    if (c >= 'a' && c <= 'z') {
        *width = 10;
        return 1;
    }
    if (c >= '0' && c <= '9') {
        *width = w;
        return 2;
    }
    if (mode == 0) {
        if (c >= 0x86 && c <= 0xBD) {
            if (next == 0x80 || next == 0x81) {
                *width = w;
                return 5;
            }
            *width = w;
            return 4;
        }
        if (c >= 0xC6 && c <= 0xFD) {
            if (next == 0x80 || next == 0x81) {
                *width = w;
                return 7;
            }
            *width = w;
            return 6;
        }
    } else {
        if (c >= 0x90 && c <= 0xAF) {
            *width = w;
            return 8;
        }
        if (c >= 0xD0 && c <= 0xEF) {
            *width = w;
            return 8;
        }
    }
    switch ((u16)c) {
        case 0x10:
        case 0x20:
            *width = (flags & 1) ? 8 : 11;
            break;
        case 0x3D:
            break;
        case 0x5C:
            if (str[0] == 0x5C) {
                *width = (flags & 1) ? 4 : 8;
            }
            break;
        case 0x7D:
            break;
        case 0x82:
            break;
        case 0x84:
            break;
        case 0x85:
            break;
        case 0xC2:
            break;
        case 0xC3:
            break;
        case 0xC4:
            break;
        case 0xC5:
            break;
        case 0xC6:
            break;
        case 0xC7:
            break;
    }
    return 3;
}

s16 GameMesAnimRead(s16 fileNo) {
    void *data = DataReadTemp(fileNo | 0xC0000);
    s16 animId = HuSprAnimRead(data);

    DataCloseTemp(data);
    return animId;
}

s16 CreateFontChar(u8 c, u8 flags) {
    s16 *animId;
    s32 fileNo;
    s32 idx;
    void *data;
    s16 id;

    idx = 0;
    switch (c) {
        case 0x7D:
            idx = 6;
            break;
        case 0x5C:
            idx = 5;
            break;
        case 0x82:
            idx = 10;
            break;
        case 0x84:
            idx = 2;
            break;
        case 0x85:
            idx = 7;
            break;
        case 0xC2:
        case 0xC4:
            idx = 1;
            break;
        case 0xC3:
        case 0xC5:
            idx = 3;
            break;
        case 0xC6:
            idx = 8;
            break;
        case 0xC7:
            idx = 8;
            break;
        case 0x3D:
            idx = 4;
            break;
    }
    if (c >= 'A' && c <= 'Z') {
        if (flags & 1) {
            fileNo = 0xC003F + (c - 'A');
            animId = &gMesFontUpperAltAnim[c - 'A'];
        } else {
            fileNo = 0xC0000 + (c - 'A');
            animId = &gMesFontUpperAnim[c - 'A'];
        }
    } else if (c >= 'a' && c <= 'z') {
        fileNo = 0xC0025 + (c - 'a');
        animId = &gMesFontLowerAnim[c - 'a'];
    } else if ((c >= 0x90 && c <= 0xAF) || (c >= 0xD0 && c <= 0xEF)) {
        for (idx = 0; idx < 36; idx++) {
            if (c == gMesKanjiTbl[idx]) {
                break;
            }
        }
        fileNo = 0xC0061 + idx;
        animId = &gMesFontKanjiAnim[idx];
    } else if (flags & 1) {
        fileNo = 0xC0059 + idx;
        animId = &gMesFontKanaAltAnim[idx];
    } else {
        fileNo = 0xC001A + idx;
        animId = &gMesFontKanaAnim[idx];
    }
    if (*animId != -1) {
        return *animId;
    }
    data = DataReadTemp(fileNo);
    id = HuSprAnimRead(data);
    *animId = id;
    DataCloseTemp(data);
    return id;
}

void GMesSprClose(GAMEMES *gMes) {
    GMesSprKill(gMes);
    GameMesStub();
}

s32 GameMesFinish11Exec(GAMEMES *gMes, Gfx **gfx) {
    return GameMesImageExec(gMes, 0xC0090, 0x253);
}

s32 GameMesStrPopExec(GAMEMES *gMes, char *str, s32 seNo) {
    f32 len = strlen(str);
    f32 i;
    f32 t;

    if (gMes->time == 0) {
        GameMesStrCreate(gMes, str, 1, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, 160, gMes->pos.y);
        gMes->subMode = -1000;
        gMes->work = 300;
        HuAudFXPlay(seNo);
        omSysPauseDisableF = 1;
        omMgActiveF = 0;
    }
    if (gMes->time > gMes->timeMax || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->time > gMes->timeMax - 10) {
        gMes->stat = GMES_STAT_TIMEEND;
        t = gMes->time - (gMes->timeMax - 10);
        for (i = 0.0f; i < len; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, 1.8f - t / 6.0f, 1.8f - t / 6.0f);
            HuSprTPLvlSet(gMes->strGId[0], i + 1, 255.0f - t * 25.5f);
        }
        gMes->subMode += gMes->work;
        gMes->pos.y += gMes->subMode / 100.0f;
        HuSprPosSet(gMes->strGId[0], 0, 160, gMes->pos.y);
        return TRUE;
    }
    for (i = 0.0f; i < len; i++) {
        HuSprScaleSet(gMes->strGId[0], i + 1, 1.8f, 1.8f);
    }
    return TRUE;
}

s32 GameMesImageExec(GAMEMES *gMes, s32 fileNo, s32 seNo) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, fileNo);
            HuAudFXPlay(seNo);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            gMes->scale.x = 1.0f;
            gMes->scale.y = 1.0f;
            gMes->angle = 0.0f;
            gMes->tpLvl = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->angle);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
            }
            gMes->subMode = 1;
            break;
        case 1:
            if (gMes->time >= 25) {
                gMes->subMode = 2;
            }
            break;
        case 2:
            gMes->pos.x += 8.0f;
            gMes->pos.y -= 6.0f;
            gMes->scale.y = gMes->scale.x -= 0.06f;
            gMes->tpLvl -= 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
            }
            if (gMes->time > gMes->timeMax - 10) {
                gMes->stat = GMES_STAT_TIMEEND;
            }
            if (gMes->time >= 40) {
                gMes->subMode = 3;
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 GameMesFinish12Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->scale.x = 1.0f;
            gMes->scale.y = 1.0f;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, 255);
            }
            gMes->subMode = 1;
            gMes->work = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->time >= 25) {
                gMes->subMode = 2;
            }
            break;
        case 2:
            gMes->scale.x = 1.0f - gMes->unk10;
            gMes->scale.y = 1.0f - gMes->unk10;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f - sindf(gMes->work) * 50.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            gMes->work += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->time > gMes->timeMax - 10) {
                gMes->stat = GMES_STAT_TIMEEND;
            }
            if (gMes->time >= gMes->timeMax) {
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, 0);
                }
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 GameMesTimeUpExec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->scale.x = 1.0f;
            gMes->scale.y = 1.0f;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, 255);
            }
            gMes->subMode = 1;
            break;
        case 1:
            if (gMes->time >= 10) {
                gMes->subMode = 2;
                gMes->unk14 = -4.0f;
            }
            break;
        case 2:
            gMes->pos.y += gMes->unk14;
            gMes->unk14 += 1.5f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            if (gMes->pos.y >= 120.0f) {
                gMes->pos.y = 120.0f;
                gMes->unk14 = -6.0f;
                gMes->subMode = 3;
            }
            break;
        case 3:
            gMes->pos.y += gMes->unk14;
            gMes->unk14 += 1.5f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            if (gMes->pos.y >= 120.0f) {
                gMes->pos.y = 120.0f;
                gMes->unk14 = -10.0f;
                gMes->unk10 = 0.0f;
                gMes->subMode = 4;
                gMes->work = 0;
                gMes->unk0C = 0;
            }
            break;
        case 4:
            gMes->pos.y += gMes->unk14;
            gMes->unk10 += 0.7f / 12;
            gMes->scale.x = 1.0f - gMes->unk10;
            gMes->scale.y = 1.0f - gMes->unk10;
            gMes->unk0C += 7;
            gMes->unk14 += 1.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            if (gMes->time > gMes->timeMax - 10) {
                gMes->stat = GMES_STAT_TIMEEND;
            }
            gMes->work++;
            if (gMes->work >= 12) {
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, 0);
                }
                gMes->subMode = 5;
            }
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 6;
            }
            break;
        case 6:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

/*
 * Shared state handling for the GMES_MES_14..21 "FINISH" variants. State 0 resets the
 * per-character work and builds the string sprites, state 6 tears everything down.
 * The callers implement the remaining states (1: animate in, 2: hold, 5: animate out).
 */
s32 GameMesFinishStrCreate(GAMEMES *gMes) {
    s32 len = strlen("FINISH");
    s32 result;
    s32 i;
    GMesChar *chr;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 6;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            for (i = 0; i < 32; i++) {
                chr = &gMesCharData[i];
                chr->x = chr->y = chr->velX = chr->velY = chr->angle = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 255;
                chr->unk34 = 0;
                chr->time = 0;
            }
            gMes->time = gMes->work = gMes->unk0C = gMes->unk0E = 0;
            gMes->timeMax = 0;
            gMes->pos.x = gMes->pos.y = 0.0f;
            gMes->scale.x = gMes->scale.y = 1.0f;
            gMes->angle = 0.0f;
            gMes->unk1C = 0;
            GameMesStrCreate(gMes, "FINISH", 1, -1, -1);
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 0.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 0);
            }
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time == 0) {
        HuAudFXPlay(0x253);
    }
    return result;
}

s32 GameMesFinish14Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->angle += 42.0f;
                    if (chr->angle > 360.0f) {
                        chr->angle -= 360.0f;
                    }
                    scale = cosdf(chr->angle);
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                }
            }
            scale = gMes->unk0C / 30.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            gMes->unk0C++;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f - scale * 180.0f * scale;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish15Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->startX = chr->x = gMesFinish15CharPos[i].x;
                chr->startY = chr->y = gMesFinish15CharPos[i].y;
                chr->endX = i * 22 - (len - 1) * 11;
                chr->endY = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->endX, chr->endY);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    t = 0.0f;
                    if (gMes->time > 20.0f / len * i + 30.0f) {
                        if (chr->time > 20) {
                            t = 1.0f;
                        } else {
                            t = chr->time * 0.05f;
                            chr->time++;
                        }
                    }
                    chr->x = t * (chr->startX - chr->endX) + chr->endX;
                    chr->y = t * (chr->startY - chr->endY) + chr->endY;
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish16Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->angle += 42.0f;
                    if (chr->angle > 360.0f) {
                        chr->angle -= 360.0f;
                    }
                    scale = cosdf(chr->angle);
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                }
            }
            scale = gMes->unk0C / 30.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            gMes->unk0C++;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f + scale * 180.0f * scale;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesMgFinishExec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    f32 scale;
    f32 t;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 225);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else if (gMes->time > 50) {
                t = (gMes->unk0C - 20.0f) / 10.0f;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                gMes->unk0C++;
                scale = 1.5f - t * 1.4f * t;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else {
                t = gMes->unk0C / 20.0f;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                gMes->unk0C++;
                scale = t * t * 0.5f + 1.0f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            }
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish18Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                t = 0.0f;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    if (gMes->time > 10.0f / len * i + 30.0f) {
                        if (chr->time > 25) {
                            t = 1.0f;
                        } else {
                            t = chr->time * 0.04f;
                            chr->time++;
                        }
                        if (t > 1.0f) {
                            t = 1.0f;
                        }
                    }
                    chr->y = -t * t * 180.0f;
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish19Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 3:
            break;
        case 4:
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            /* fallthrough */
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                t = 0.0f;
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    if (gMes->time > 10.0f / len * i + 30.0f) {
                        if (chr->time > 25) {
                            t = 1.0f;
                        } else {
                            t = chr->time * 0.04f;
                            chr->time++;
                        }
                        if (t > 1.0f) {
                            t = 1.0f;
                        }
                    }
                    chr->y = t * t * 180.0f;
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish20Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = GameMesFinishStrCreate(gMes);
    len = strlen("FINISH");
    switch (gMes->subMode) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &gMesCharData[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 225);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->subMode = 2;
            break;
        case 2:
            if (gMes->time >= 30) {
                gMes->subMode = 5;
                gMes->unk0C = 0;
                gMes->work = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            if (gMes->time > 60) {
                for (i = 0; i < len; i++) {
                    HuSprDispOff(gMes->strGId[0], i + 1);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->subMode = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &gMesCharData[i];
                    chr->angle += 28.0f;
                    if (chr->angle > 360.0f) {
                        chr->angle -= 360.0f;
                    }
                    scale = cosdf(chr->angle);
                    if (scale < 0.0f) {
                        scale = -scale;
                        HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    } else {
                        HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                        HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, scale);
                    }
                }
            }
            scale = gMes->unk0C / 30.0f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            gMes->unk0C++;
            gMes->pos.x = 160.0f - ((len + 2) * 11 + 240) * scale;
            gMes->pos.y = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, 120);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 GameMesFinish21Exec(GAMEMES *gMes, Gfx **gfx) {
    return GameMesFinish20Exec(gMes, gfx);
}

void GameMesImageCreate(GAMEMES *gMes, s32 fileNo) {
    void *data;
    s16 sprId0;
    s16 sprId1;
    s16 grp;

    data = DataReadTemp(fileNo);
    sprId0 = gMes->strSprId[0] = HuSprAnimRead(data);
    DataCloseTemp(data);
    data = DataReadTemp(fileNo + 1);
    sprId1 = gMes->strSprId[1] = HuSprAnimRead(data);
    DataCloseTemp(data);
    grp = gMes->strGId[0] = HuSprGrpCreate(2, 5);
    HuSprGrpMemberSet(grp, 0, sprId0, 0);
    HuSprTPLvlSet(grp, 0, 255);
    HuSprPriSet(grp, 0, 5);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPosSet(grp, 0, 160, gMes->pos.y);
    HuSprParentSet(grp, 0, -1);
    HuSprGrpMemberSet(grp, 1, sprId1, 0);
    HuSprTPLvlSet(grp, 1, 255);
    HuSprPriSet(grp, 1, 6);
    HuSprAttrReset(grp, 1, 0xFFFF);
    HuSprAttrSet(grp, 1, 0x1008);
    HuSprColorSet(grp, 1, 69, 2, 133);
    HuSprParentSet(grp, 1, 0);
}

// The following data is defined here rather than at the top of the file so that the
// name strings are placed in the middle of this file's .rodata.
static char *gMesCharNameTbl[] = {
    " MARIO ", " LUIGI ", " PEACH ", " YOSHI ", " WARIO ", "\t DK\t  ", " WALUIGI ", " DAISY ", "  ALL\t",
};

static s32 gMesWinnerPos0[5][2] = {
    { 30, 45 }, { 265, 45 }, { 30, 200 }, { 265, 200 }, { 170, 120 },
};

static s32 gMesWinnerPos1[5][2] = {
    { 105, 95 }, { 235, 95 }, { 105, 150 }, { 235, 150 }, { 170, 120 },
};

static s32 gMesWinnerPos2[5][2] = {
    { 90, 95 }, { 250, 95 }, { 90, 150 }, { 250, 150 }, { 170, 120 },
};

// がぎぐげござじずぜぞだぢづでどばびぶべぼガギグゲゴザジズゼゾダヂヅデドバビブベボ
static u8 gMesDakuTbl[] = "\x82\xAA\x82\xAC\x82\xAE\x82\xB0\x82\xB2\x82\xB4\x82\xB6\x82\xB8\x82\xBA\x82\xBC\x82\xBE\x82\xC0\x82\xC3\x82\xC5\x82\xC7\x82\xCE\x82\xD1\x82\xD4\x82\xD7\x82\xDA\x83\x4B\x83\x4D\x83\x4F\x83\x51\x83\x53\x83\x55\x83\x57\x83\x59\x83\x5B\x83\x5D\x83\x5F\x83\x61\x83\x64\x83\x66\x83\x68\x83\x6F\x83\x72\x83\x75\x83\x78\x83\x7B";

// かきくけこさしすせそたちつてとはひふへほカキクケコサシスセソタチツテトハヒフヘホ
static u8 gMesDakuBaseTbl[] = "\x82\xA9\x82\xAB\x82\xAD\x82\xAF\x82\xB1\x82\xB3\x82\xB5\x82\xB7\x82\xB9\x82\xBB\x82\xBD\x82\xBF\x82\xC2\x82\xC4\x82\xC6\x82\xCD\x82\xD0\x82\xD3\x82\xD6\x82\xD9\x83\x4A\x83\x4C\x83\x4E\x83\x50\x83\x52\x83\x54\x83\x56\x83\x58\x83\x5A\x83\x5C\x83\x5E\x83\x60\x83\x63\x83\x65\x83\x67\x83\x6E\x83\x71\x83\x74\x83\x77\x83\x7A";

// ぱぴぷぺぽパピプペポ
static u8 gMesHandakuTbl[] = "\x82\xCF\x82\xD2\x82\xD5\x82\xD8\x82\xDB\x83\x70\x83\x73\x83\x76\x83\x79\x83\x7C";

// はひふへほハヒフヘホ
static u8 gMesHandakuBaseTbl[] = "\x82\xCD\x82\xD0\x82\xD3\x82\xD6\x82\xD9\x83\x6E\x83\x71\x83\x74\x83\x77\x83\x7A";

s32 GameMesMgWinnerExec(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    f32 nameLen = strlen(gMesCharNameTbl[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 total;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0E], 1, -1, -1, 1.0f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)wonStr, 1, -1, -1, 1.0f, 1.0f);
            total = nameLen + wonLen + 1.0f;
            gMes->work = 160.0f - total * 17.6f / 2.0f + nameLen * 17.6f / 2.0f;
            gMes->pos.x = gMes->work;
            gMes->scale.x = gMes->scale.y = 1.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < nameLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
            }
            gMes->unk0C = 160.0f - total * 17.6f / 2.0f + (nameLen * 17.6f + 17.6f) + wonLen * 17.6f / 2.0f;
            gMes->pos.x = gMes->unk0C;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
            }
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            gMes->pos.y += sindf(gMes->unk14);
            gMes->pos.x = gMes->unk0C + sindf(gMes->unk10);
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 5;
            }
            if (gMes->time > gMes->timeMax - 10) {
                scale = (gMes->timeMax - gMes->time) / 10.0f * 0.8f;
                for (i = 0.0f; i < nameLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
                for (i = 0.0f; i < wonLen; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, scale, scale);
                }
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesMgLoserExec(GAMEMES *gMes, Gfx **gfx) {
    char lostStr[] = "LOST";
    f32 nameLen = strlen(gMesCharNameTbl[gMes->subMode]);
    f32 lostLen = strlen(lostStr);
    f32 x;
    s16 i;

    if (gMes->time == 0) {
        GameMesStrCreate(gMes, gMesCharNameTbl[gMes->subMode], 1, -1, -1);
        GameMesStrCreate(gMes, lostStr, 1, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, (320.0f - (nameLen + lostLen + 1.0f) * 24.0f) / 2.0f + nameLen * 24.0f / 2.0f, gMes->pos.y + 40.0f);
        HuSprPosSet(gMes->strGId[1], 0, 320.0f - (320.0f - (nameLen + lostLen + 1.0f) * 24.0f) / 2.0f - lostLen * 24.0f / 2.0f, gMes->pos.y + 40.0f);
        for (i = 0; i < nameLen; i++) {
            HuSprDispOff(gMes->strGId[0], i + 1);
        }
        for (i = 0; i < lostLen; i++) {
            HuSprDispOff(gMes->strGId[1], i + 1);
        }
        gMes->work = 0;
    }
    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->time > 80) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    if (gMes->time > 50) {
        if (++gMes->work & 0x40) {
            x = (u16)gMes->work % 32;
            x = cosdf(x * 11.612904f) * 55.0f + 200.0f;
            for (i = 0; i < nameLen; i++) {
                HuSprTPLvlSet(gMes->strGId[0], i + 1, x);
            }
            for (i = 0; i < lostLen; i++) {
                HuSprTPLvlSet(gMes->strGId[1], i + 1, x);
            }
        }
        return TRUE;
    }
    x = gMes->time;
    if (x <= 30.0f) {
        for (i = 0; i < nameLen; i++) {
            HuSprDispOn(gMes->strGId[0], i + 1);
            HuSprTPLvlSet(gMes->strGId[0], i + 1, x * 8.5f);
        }
    }
    x = gMes->time - 20;
    if (x <= 30.0f && x > 0.0f) {
        for (i = 0; i < lostLen; i++) {
            HuSprDispOn(gMes->strGId[1], i + 1);
            HuSprTPLvlSet(gMes->strGId[1], i + 1, x * 8.5f);
        }
    }
    return TRUE;
}

s32 GameMes24Exec(GAMEMES *gMes, Gfx **gfx) {
    char *str;
    f32 scale;
    f32 i;

    if (gMes->time == 0) {
        str = HuMemMemoryAllocPerm(256);
        GameMesStrConv((u8 *)str, (void *)gMes->unk1C);
        GameMesStrCreate(gMes, str, gMes->unk02, -1, -1);
        gMes->subMode = strlen(str);
        HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
        HuMemMemoryFreePerm(str);
    }
    if (gMes->time > gMes->timeMax || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->time < 14) {
        scale = sindf(gMes->time * 10.0f) + (1.0f - sindf(130.0f));
        for (i = 0.0f; i < gMes->subMode; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, scale * gMes->scale.y);
        }
    }
    if (gMes->time > gMes->timeMax - 10) {
        gMes->stat = GMES_STAT_TIMEEND;
        scale = cosdf((gMes->time - (gMes->timeMax - 10)) * 9.0f);
        for (i = 0.0f; i < gMes->subMode; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, scale * gMes->scale.y);
        }
    }
    return TRUE;
}

s32 GameMes25Exec(GAMEMES *gMes, Gfx **gfx) {
    char *str;
    f32 i;

    if (gMes->time == 0) {
        str = HuMemMemoryAllocPerm(256);
        GameMesStrConv((u8 *)str, (void *)gMes->unk1C);
        GameMesStrCreate(gMes, str, gMes->unk02, -1, -1);
        gMes->subMode = strlen(str);
        HuMemMemoryFreePerm(str);
    }
    if (gMes->time > gMes->timeMax || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
    HuSprZRotSet(gMes->strGId[0], 0, gMes->angle);
    for (i = 0.0f; i < gMes->subMode; i++) {
        HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.y);
        HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
    }
    return TRUE;
}

s32 GMesTimerExec(GAMEMES *gMes, Gfx **arg1) {
    f32 temp_f22;
    u8 temp_s2;
    u8 temp_s0;

    if (gMes->time == 0) {
        GameMesStrCreate(gMes, "99", 0, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
        HuSprTPLvlSet(gMes->strGId[0], 1, 0x100);
        HuSprTPLvlSet(gMes->strGId[0], 2, 0x100);
        gMes->work = 0;
    }
    temp_s2 = gMes->subMode % 100;
    temp_s0 = temp_s2 / 10;
    if (temp_s0 == 0) {
        HuSprDispOff(gMes->strGId[0], 1);
    } else {
        HuSprDispOn(gMes->strGId[0], 1);
    }
    HuSprBankSet(gMes->strGId[0], 1, temp_s0, 0);
    HuSprAnimModeSet(gMes->strGId[0], 1, HUSPR_ANIM_MODE_BANK);
    temp_s0 = temp_s2 % 10;
    HuSprBankSet(gMes->strGId[0], 2, temp_s0, 0);
    HuSprAnimModeSet(gMes->strGId[0], 2, HUSPR_ANIM_MODE_BANK);
    switch (gMes->work) {
        case 0:
            if (gMes->time < 14) {
                temp_f22 = sindf(gMes->time * 10.0f) * 5.0f + (1.0f - sindf(130.0f) * 5.0f);
                HuSprScaleSet(gMes->strGId[0], 1, temp_f22, temp_f22);
                HuSprScaleSet(gMes->strGId[0], 2, temp_f22, temp_f22);
            } else {
                gMes->work = 1;
            }
            break;
        case 1:
            if (gMes->unk0E != gMes->subMode && gMes->subMode < 6) {
                gMes->unk0C = 0;
                if (gMes->subMode != 0) {
                    gMes->work = 3;
                    HuAudFXPlay(8);
                }
            } else {
                HuSprTPLvlSet(gMes->strGId[0], 1, 0x100);
                HuSprTPLvlSet(gMes->strGId[0], 2, 0x100);
            }
            break;
        case 2:
            if (gMes->unk0C < 10) {
                HuSprTPLvlSet(gMes->strGId[0], 1, 230 - gMes->unk0C * 23);
                HuSprTPLvlSet(gMes->strGId[0], 2, 230 - gMes->unk0C * 23);
            } else {
                gMes->work = 1;
                gMes->stat = GMES_STAT_KILL;
            }
            gMes->unk0C++;
            break;
        case 3:
            if (gMes->unk0C < 11) {
                temp_f22 = 1.0f + sindf(gMes->unk0C * 18.0f);
                HuSprScaleSet(gMes->strGId[0], 1, temp_f22, temp_f22);
                HuSprScaleSet(gMes->strGId[0], 2, temp_f22, temp_f22);
                temp_f22 = 230.0f - sindf(gMes->unk0C * 18.0f) * 60.0f;
                HuSprTPLvlSet(gMes->strGId[0], 1, temp_f22);
                HuSprTPLvlSet(gMes->strGId[0], 2, temp_f22);
            } else {
                gMes->work = 1;
            }
            gMes->unk0C++;
            break;
    }
    gMes->unk0E = gMes->subMode;
    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        gMesTimerId = -1;
        return FALSE;
    }
    return TRUE;
}

// GMesUpdate? GMesTimerUpdate? GMesTimerSet?
void GMesTimerValueSet(s16 arg0) {
    if (gMesTimerId < 0 || arg0 < 0) {
        return;
    }
    gMesData[gMesTimerId].subMode = arg0;
}

// GMesTimerKill?
void GMesTimerEnd(void) {
    if (gMesTimerId < 0) {
        return;
    }
    gMesData[gMesTimerId].work = 2;
    gMesData[gMesTimerId].unk0C = 0;
}

s32 GameMesMgRecordExec(GAMEMES *gMes, Gfx **gfx) {
    char *newStr = "NEW";
    char *recordStr = "RECORD";
    s32 newLen;
    s32 recordLen;
    s32 result;
    s32 i;
    f32 x;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    newLen = strlen(newStr);
    recordLen = strlen(recordStr);
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, newStr, 1, -1, -1);
            GameMesStrCreate(gMes, recordStr, 1, -1, -1);
            gMes->scale.x = gMes->scale.y = 0.5f;
            x = 160.0f - ((newLen + recordLen + 1) * 11 * gMes->scale.x - newLen * 11 * gMes->scale.y);
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x - 160.0f + x, gMes->pos.y);
            gMes->tpLvl = 0;
            for (i = 0; i < newLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            x = (newLen + recordLen + 1) * 11 * gMes->scale.x - recordLen * 11 * gMes->scale.y + 160.0f;
            gMes->angle = 0.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x - 160.0f + x, gMes->pos.y);
            HuSprZRotSet(gMes->strGId[1], 0, gMes->angle);
            for (i = 0; i < recordLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->subMode = 1;
            gMes->unk10 = 90.0f;
            break;
        case 1:
            gMes->unk10 += 21.0f;
            gMes->scale.x += 0.016666668f;
            gMes->scale.y = 1.0f - sindf(gMes->unk10) * 0.5f;
            x = 160.0f - ((newLen + recordLen + 1) * 11 * gMes->scale.x - newLen * 11 * gMes->scale.x);
            gMes->angle += 12.0f;
            gMes->tpLvl += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x - 160.0f + x, gMes->pos.y);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->angle);
            for (i = 0; i < newLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            x = (newLen + recordLen + 1) * 11 * gMes->scale.x - recordLen * 11 * gMes->scale.x + 160.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x - 160.0f + x, gMes->pos.y);
            for (i = 0; i < recordLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            if (gMes->time >= 30) {
                gMes->stat = GMES_STAT_TIMEEND;
                HuSprZRotSet(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < newLen; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0; i < recordLen; i++) {
                    HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
                }
                gMes->work = 30;
                gMes->subMode = 2;
            }
            break;
        case 2:
            if (--gMes->work == -1) {
                gMes->work = 255;
                gMes->subMode = 3;
            }
            break;
        case 3:
            gMes->work -= 16;
            if (gMes->work <= 0) {
                gMes->work = 0;
                gMes->subMode = 4;
            }
            for (i = 0; i < newLen; i++) {
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->work);
            }
            for (i = 0; i < recordLen; i++) {
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->work);
            }
            if (gMes->time > 60) {
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time == 10) {
        HuAudFXPlay(0x252);
    }
    if (gMes->time >= 56) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesTimeUp2Exec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 3;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0092);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            gMes->scale.x = 1.0f;
            gMes->scale.y = 1.0f;
            gMes->tpLvl = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
            }
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->scale.y = gMes->scale.x = sindf(gMes->unk10) * 0.2f + 1.0f;
            gMes->unk10 += 15.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
            }
            if (gMes->time > gMes->timeMax - 10) {
                gMes->stat = GMES_STAT_TIMEEND;
                gMes->tpLvl -= 25;
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
                }
            }
            if (gMes->time > gMes->timeMax) {
                gMes->subMode = 3;
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 GameMesGoalExec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 3;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0094);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            gMes->scale.x = 1.0f;
            gMes->scale.y = 1.0f;
            gMes->tpLvl = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
            }
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->time >= 10) {
                gMes->subMode = 2;
            }
            break;
        case 2:
            gMes->scale.y = gMes->scale.x = sindf(gMes->unk10) * 0.3f + 1.0f;
            gMes->unk10 += 20.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
            }
            if (gMes->time >= 40) {
                gMes->tpLvl -= 51;
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
                }
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->stat = GMES_STAT_TIMEEND;
                gMes->subMode = 3;
                for (i = 0; i < 2; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 GameMesGameOverExec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;
    f32 t;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0098);
            HuSprColorSet(gMes->strGId[0], 1, 69, 2, 133);
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 0.0f, 2.0f);
            }
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->scale.x = sindf(gMes->unk10);
            gMes->scale.y = 2.0f - (1.0f - cosdf(gMes->unk10));
            gMes->unk10 += 9.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
            }
            if (gMes->time < 10) {
                break;
            }
            gMes->subMode = 2;
            gMes->unk10 = 90.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
            }
            /* fallthrough */
        case 2:
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
            }
            gMes->scale.x = 1.5f - (sindf(gMes->unk10) < 0.0f ? -sindf(gMes->unk10) : sindf(gMes->unk10)) * 0.5f;
            gMes->scale.y = (sindf(gMes->unk10) < 0.0f ? -sindf(gMes->unk10) : sindf(gMes->unk10)) * 0.7f + 0.3f;
            gMes->unk10 += 12.0f;
            if (gMes->time >= 25) {
                for (i = 0; i < 2; i++) {
                }
                gMes->subMode = 3;
                gMes->unk10 = 0.0f;
            }
            break;
        case 3:
            gMes->tpLvl = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->time > gMes->timeMax - 10) {
                t = (gMes->timeMax - gMes->time) / 10.0f;
            } else {
                t = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl * t);
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time == 10) {
        HuAudFXPlay(0x24F);
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesReadyGoExec(GAMEMES *gMes, Gfx **gfx) {
    char *readyStr = "READY";
    char *goStr = "GO\xC4";
    s32 readyLen;
    s32 goLen;
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 6;
    }
    result = TRUE;
    readyLen = strlen(readyStr);
    goLen = strlen(goStr);
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, readyStr, 1, -1, -1);
            GameMesStrCreate(gMes, goStr, 1, -1, -1);
            gMes->scale.x = 0.5f;
            gMes->tpLvl = 0;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            for (i = 0; i < goLen; i++) {
                HuSprDispOff(gMes->strGId[1], i + 1);
            }
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            gMes->subMode = 1;
            gMes->unk0C = 0;
            gMes->work = 0;
            break;
        case 1:
            gMes->scale.x += 0.1f;
            gMes->tpLvl += 25;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            if (gMes->time >= 10) {
                for (i = 0; i < readyLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.5f, 1.5f);
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                gMes->subMode = 2;
            }
            break;
        case 2:
            if (gMes->time >= 35) {
                gMes->subMode = 3;
            }
            break;
        case 3:
            gMes->scale.x += 0.05f;
            gMes->tpLvl -= 51;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            if (gMes->time >= 40) {
                for (i = 0; i < readyLen; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 0);
                }
                gMes->subMode = 4;
            }
            break;
        case 4:
            gMes->scale.x = gMes->scale.y = sindf(gMes->work * 15) * 3.0f;
            for (i = 0; i < goLen; i++) {
                HuSprDispOn(gMes->strGId[1], i + 1);
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.x, gMes->scale.y);
            }
            gMes->work++;
            if (gMes->time >= 50) {
                GameMesMgStub(GMesMgNoGet());
                gMes->subMode = 5;
                gMes->tpLvl = 255;
            }
            break;
        case 5:
            gMes->stat = GMES_STAT_TIMEEND;
            gMes->tpLvl -= 51;
            for (i = 0; i < goLen; i++) {
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            gMes->unk0C++;
            if (gMes->time >= 55) {
                for (i = 0; i < goLen; i++) {
                    HuSprDispOff(gMes->strGId[1], i + 1);
                }
                gMes->subMode = 6;
            }
            break;
        case 6:
            GMesSprKill(gMes);
            omSysPauseDisableF = 0;
            omMgActiveF = 1;
            result = FALSE;
            break;
    }
    return result;
}

s32 GameMesMgWinners2Exec(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    f32 name1Len = strlen(gMesCharNameTbl[gMes->unk0C]);
    f32 name2Len = strlen(gMesCharNameTbl[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreate(gMes, wonStr, 1, -1, -1);
            gMes->pos.x = 80.0f;
            gMes->pos.y = 0.0f;
            gMes->scale.x = gMes->scale.y = 1.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
            }
            gMes->pos.x = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->pos.x = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprDispOff(gMes->strGId[2], i + 1);
            }
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 1.5f;
            break;
        case 1:
            gMes->unk10 += gMes->unk14;
            gMes->pos.y += gMes->unk10;
            gMes->pos.x = 80.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            gMes->pos.x = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->pos.x = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            if (gMes->time >= 15) {
                gMes->subMode = 2;
                gMes->unk10 = -12.0f;
                gMes->unk14 = 1.0f;
            }
            break;
        case 2:
            gMes->unk10 += gMes->unk14;
            gMes->pos.y += gMes->unk10;
            gMes->pos.x = 80.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            gMes->pos.x = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->pos.x = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            if (gMes->time >= 25) {
                gMes->subMode = 3;
                gMes->work = gMes->pos.y;
            }
            break;
        case 3:
            gMes->pos.x = 170.0f;
            gMes->pos.y = 145.0f;
            gMes->scale.x = gMes->scale.y = 1.0f;
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, 255);
                HuSprDispOn(gMes->strGId[2], i + 1);
            }
            gMes->subMode = 4;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 4:
            gMes->pos.x = sindf(gMes->unk10) + 160.0f;
            gMes->pos.y = sindf(gMes->unk14) + 145.0f;
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 5;
            }
            if (gMes->time > gMes->timeMax - 10) {
                scale = (gMes->timeMax - gMes->time) / 10.0f;
                for (i = 0.0f; i < name1Len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < wonLen; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, scale);
                }
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesMgDrawExec(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;
    f32 t;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 3;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesImageCreate(gMes, 0xC0096);
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->pos.x = 160.0f;
            gMes->pos.y = 120.0f;
            gMes->scale.x = gMes->scale.y = 0.5f;
            gMes->angle = 0.0f;
            gMes->tpLvl = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->angle);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl);
            }
            gMes->subMode = 1;
            break;
        case 1:
            gMes->scale.y = gMes->scale.x += 0.05f;
            gMes->angle += 36.0f;
            HuSprZRotSet(gMes->strGId[0], 0, gMes->angle);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->scale.x, gMes->scale.y);
            }
            if (gMes->time >= 10) {
                HuSprZRotSet(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < 2; i++) {
                    HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
                }
                gMes->subMode = 2;
                gMes->unk10 = 0.0f;
            }
            break;
        case 2:
            gMes->tpLvl = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->time > gMes->timeMax - 10) {
                t = (gMes->timeMax - gMes->time) / 10.0f;
            } else {
                t = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                HuSprTPLvlSet(gMes->strGId[0], i, gMes->tpLvl * t);
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time == 30) {
        HuAudFXPlay(0x255);
    }
    if (gMes->time == gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesMgWinners3Exec(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    s32 startPos[4][2] = { { 95, 80 }, { 210, 80 }, { 155, 140 }, { 170, 145 } };
    s32 endPos[4][2] = { { 240, 117 }, { 80, 117 }, { 160, 80 }, { 160, 145 } };
    s32 dx;
    s32 dy;
    f32 name1Len = strlen(gMesCharNameTbl[gMes->work]);
    f32 name2Len = strlen(gMesCharNameTbl[gMes->unk0C]);
    f32 name3Len = strlen(gMesCharNameTbl[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->work], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreate(gMes, wonStr, 1, -1, -1);
            gMes->pos.x = startPos[0][0];
            gMes->pos.y = startPos[0][1] + gMes->pos.y;
            gMes->scale.x = gMes->scale.y = 0.5f;
            gMes->tpLvl = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = startPos[1][0];
            gMes->pos.y = startPos[1][1];
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = startPos[2][0];
            gMes->pos.y = startPos[2][1];
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, gMes->tpLvl);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprDispOff(gMes->strGId[3], i + 1);
            }
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            dx = endPos[0][0] - startPos[0][0];
            dy = endPos[0][1] - startPos[0][1];
            gMes->pos.x = startPos[0][0] + gMes->unk10 / 30.0f * dx;
            gMes->pos.y = startPos[0][1] + gMes->unk10 / 30.0f * dy;
            gMes->scale.x = gMes->scale.y = gMes->unk10 / 30.0f * 0.5f + 0.5f;
            gMes->tpLvl += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            dx = endPos[1][0] - startPos[1][0];
            dy = endPos[1][1] - startPos[1][1];
            gMes->pos.x = startPos[1][0] + gMes->unk10 / 30.0f * dx;
            gMes->pos.y = startPos[1][1] + gMes->unk10 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            dx = endPos[2][0] - startPos[2][0];
            dy = endPos[2][1] - startPos[2][1];
            gMes->pos.x = startPos[2][0] + gMes->unk10 / 30.0f * dx;
            gMes->pos.y = startPos[2][1] + gMes->unk10 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, gMes->tpLvl);
            }
            gMes->unk10 += 1.0f;
            if (gMes->time >= 30) {
                for (i = 0.0f; i < name1Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[2], i + 1, 255);
                }
                gMes->subMode = 2;
            }
            break;
        case 2:
            gMes->pos.x = startPos[3][0];
            gMes->pos.y = startPos[3][1];
            gMes->scale.x = gMes->scale.y = 1.0f;
            HuSprPosSet(gMes->strGId[3], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->scale.x, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[3], i + 1, 255);
                HuSprDispOn(gMes->strGId[3], i + 1);
            }
            gMes->subMode = 3;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 3:
            gMes->pos.x = endPos[3][0] + sindf(gMes->unk10);
            gMes->pos.y = endPos[3][1] + sindf(gMes->unk14);
            HuSprPosSet(gMes->strGId[3], 0, gMes->pos.x, gMes->pos.y);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->time > gMes->timeMax - 10) {
                scale = (gMes->timeMax - gMes->time) / 10.0f;
                for (i = 0.0f; i < name1Len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, 0.8f, scale * 0.8f);
                }
                for (i = 0.0f; i < wonLen; i++) {
                    HuSprScaleSet(gMes->strGId[3], i + 1, 1.0f, scale);
                }
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 5;
            }
            break;
        case 4:
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesMgWinners4Exec(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    s32 dx;
    s32 dy;
    f32 name1Len = strlen(gMesCharNameTbl[gMes->subMode]);
    f32 name2Len = strlen(gMesCharNameTbl[gMes->work]);
    f32 name3Len = strlen(gMesCharNameTbl[gMes->unk0C]);
    f32 name4Len = strlen(gMesCharNameTbl[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk10 = 5.0f;
    }
    result = TRUE;
    switch ((s32)gMes->unk10) {
        case 0:
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->subMode], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->work], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)gMesCharNameTbl[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            GameMesStrCreateScale(gMes, (u8 *)wonStr, 1, -1, -1, 0.8f, 1.0f);
            gMes->pos.x = gMesWinnerPos0[0][0];
            gMes->pos.y = gMesWinnerPos0[0][1];
            gMes->scale.x = gMes->scale.y = 0.5f;
            gMes->tpLvl = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = gMesWinnerPos0[1][0];
            gMes->pos.y = gMesWinnerPos0[1][1];
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = gMesWinnerPos0[2][0];
            gMes->pos.y = gMesWinnerPos0[2][1];
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = gMesWinnerPos0[3][0];
            gMes->pos.y = gMesWinnerPos0[3][1];
            HuSprPosSet(gMes->strGId[3], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name4Len; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[3], i + 1, gMes->tpLvl);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprDispOff(gMes->strGId[4], i + 1);
            }
            gMes->unk10 = 1.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            dx = gMesWinnerPos1[0][0] - gMesWinnerPos0[0][0];
            dy = gMesWinnerPos1[0][1] - gMesWinnerPos0[0][1];
            gMes->pos.x = gMesWinnerPos0[0][0] + gMes->unk14 / 30.0f * dx;
            gMes->pos.y = gMesWinnerPos0[0][1] + gMes->unk14 / 30.0f * dy;
            gMes->scale.x = gMes->scale.y = gMes->unk14 / 30.0f * 0.5f + 0.5f;
            gMes->tpLvl += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            dx = gMesWinnerPos1[1][0] - gMesWinnerPos0[1][0];
            dy = gMesWinnerPos1[1][1] - gMesWinnerPos0[1][1];
            gMes->pos.x = gMesWinnerPos0[1][0] + gMes->unk14 / 30.0f * dx;
            gMes->pos.y = gMesWinnerPos0[1][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            dx = gMesWinnerPos1[2][0] - gMesWinnerPos0[2][0];
            dy = gMesWinnerPos1[2][1] - gMesWinnerPos0[2][1];
            gMes->pos.x = gMesWinnerPos0[2][0] + gMes->unk14 / 30.0f * dx;
            gMes->pos.y = gMesWinnerPos0[2][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, gMes->tpLvl);
            }
            dx = gMesWinnerPos1[3][0] - gMesWinnerPos0[3][0];
            dy = gMesWinnerPos1[3][1] - gMesWinnerPos0[3][1];
            gMes->pos.x = gMesWinnerPos0[3][0] + gMes->unk14 / 30.0f * dx;
            gMes->pos.y = gMesWinnerPos0[3][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[3], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < name4Len; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[3], i + 1, gMes->tpLvl);
            }
            gMes->unk14 += 1.0f;
            if (gMes->time >= 30) {
                for (i = 0.0f; i < name1Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[2], i + 1, 255);
                }
                for (i = 0.0f; i < name4Len; i++) {
                    HuSprTPLvlSet(gMes->strGId[3], i + 1, 255);
                }
                gMes->unk10 = 2.0f;
            }
            break;
        case 2:
            gMes->pos.x = gMesWinnerPos0[4][0];
            gMes->pos.y = gMesWinnerPos0[4][1];
            gMes->scale.x = gMes->scale.y = 1.0f;
            HuSprPosSet(gMes->strGId[4], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[4], i + 1, gMes->scale.x * 0.8f, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[4], i + 1, 255);
                HuSprDispOn(gMes->strGId[4], i + 1);
            }
            gMes->unk10 = 3.0f;
            gMes->unk14 = 0.0f;
            break;
        case 3:
            dx = gMesWinnerPos2[0][0] - gMesWinnerPos1[0][0];
            dy = gMesWinnerPos2[0][1] - gMesWinnerPos1[0][1];
            gMes->pos.x = gMesWinnerPos1[0][0] + gMes->unk14 / 10.0f * dx;
            gMes->pos.y = gMesWinnerPos1[0][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            dx = gMesWinnerPos2[1][0] - gMesWinnerPos1[1][0];
            dy = gMesWinnerPos2[1][1] - gMesWinnerPos1[1][1];
            gMes->pos.x = gMesWinnerPos1[1][0] + gMes->unk14 / 10.0f * dx;
            gMes->pos.y = gMesWinnerPos1[1][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            dx = gMesWinnerPos2[2][0] - gMesWinnerPos1[2][0];
            dy = gMesWinnerPos2[2][1] - gMesWinnerPos1[2][1];
            gMes->pos.x = gMesWinnerPos1[2][0] + gMes->unk14 / 10.0f * dx;
            gMes->pos.y = gMesWinnerPos1[2][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->pos.x, gMes->pos.y);
            dx = gMesWinnerPos2[3][0] - gMesWinnerPos1[3][0];
            dy = gMesWinnerPos2[3][1] - gMesWinnerPos1[3][1];
            gMes->pos.x = gMesWinnerPos1[3][0] + gMes->unk14 / 10.0f * dx;
            gMes->pos.y = gMesWinnerPos1[3][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[3], 0, gMes->pos.x, gMes->pos.y);
            gMes->unk14 += 1.0f;
            if (gMes->time >= 40) {
                gMes->unk10 = 4.0f;
                gMes->unk14 = 0.0f;
                gMes->unk18 = 0.0f;
            }
            break;
        case 4:
            gMes->pos.x = gMesWinnerPos1[4][0] + sindf(gMes->unk14);
            gMes->pos.y = gMesWinnerPos1[4][1] + sindf(gMes->unk18);
            HuSprPosSet(gMes->strGId[4], 0, gMes->pos.x, gMes->pos.y);
            gMes->unk14 += 90.0f;
            gMes->unk18 += 45.0f;
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk18 >= 360.0f) {
                gMes->unk18 = 0.0f;
            }
            if (gMes->time > gMes->timeMax - 10) {
                scale = (gMes->timeMax - gMes->time) / 10.0f;
                for (i = 0.0f; i < name1Len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale * 0.8f, 0.8f);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, scale * 0.8f, 0.8f);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, scale * 0.8f, 0.8f);
                }
                for (i = 0.0f; i < name4Len; i++) {
                    HuSprScaleSet(gMes->strGId[3], i + 1, scale * 0.8f, 0.8f);
                }
                for (i = 0.0f; i < wonLen; i++) {
                    HuSprScaleSet(gMes->strGId[4], i + 1, scale, 1.0f);
                }
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->unk10 = 5.0f;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesGotItemExec(GAMEMES *gMes, Gfx **gfx) {
    char *gotStr = "GOT";
    char *itemStr = "ITEM\xC4";
    s32 result;
    s32 gotLen;
    s32 itemLen;
    s32 i;
    f32 alpha;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 4;
    }
    result = TRUE;
    gotLen = strlen(gotStr);
    itemLen = strlen(itemStr);
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, gotStr, 1, -1, -1);
            GameMesStrCreate(gMes, itemStr, 1, -1, -1);
            gMes->scale.x = gMes->scale.y = 0.5f;
            gMes->pos.x = cosdf(0.0f) * 55.0f + 149.0f;
            gMes->pos.y = sindf(0.0f) * 55.0f + 120.0f;
            gMes->tpLvl = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = cosdf(180.0f) * 55.0f + 149.0f;
            gMes->pos.y = sindf(180.0f) * 55.0f + 120.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, 0);
            }
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 180.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->unk14 += 12.0f;
            gMes->scale.y = gMes->scale.x += 0.033333335f;
            gMes->pos.x = cosdf(gMes->unk10) * 55.0f + 149.0f;
            gMes->pos.y = sindf(gMes->unk10) * 55.0f + 120.0f;
            gMes->tpLvl += 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->pos.x = cosdf(gMes->unk14) * 55.0f + 149.0f;
            gMes->pos.y = sindf(gMes->unk14) * 55.0f + 120.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            if (gMes->time >= 15) {
                gMes->subMode = 2;
                gMes->unk10 = 630.0f;
            }
            break;
        case 2:
            gMes->scale.y = gMes->scale.x = sindf(gMes->unk10) * 0.1f + 1.1f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
            }
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.x, gMes->scale.x);
            }
            if (gMes->time >= 35) {
                for (i = 0; i < gotLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                for (i = 0; i < itemLen; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                }
                gMes->subMode = 3;
            }
            break;
        case 3:
            if (gMes->time > gMes->timeMax - 10) {
                alpha = (gMes->timeMax - gMes->time) / 10.0f * 255.0f;
                for (i = 0; i < gotLen; i++) {
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, alpha);
                }
                for (i = 0; i < itemLen; i++) {
                    HuSprTPLvlSet(gMes->strGId[1], i + 1, alpha);
                }
            }
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time == 1) {
        HuAudFXPlay(0x260);
    }
    if (gMes->time > gMes->timeMax - 5) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

s32 GameMesGotItem2Exec(GAMEMES *gMes, Gfx **gfx) {
    char *gotStr = "GOT";
    char *itemStr = "ITEM";
    char *exclStr = "\xC3";
    s32 result;
    s32 gotLen;
    s32 itemLen;
    s32 exclLen;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->subMode = 5;
    }
    result = TRUE;
    gotLen = strlen(gotStr);
    itemLen = strlen(itemStr);
    exclLen = strlen(exclStr);
    switch (gMes->subMode) {
        case 0:
            GameMesStrCreate(gMes, gotStr, 1, -1, -1);
            GameMesStrCreate(gMes, itemStr, 1, -1, -1);
            GameMesStrCreate(gMes, exclStr, 1, -1, -1);
            gMes->scale.x = gMes->scale.y = 0.5f;
            gMes->pos.x = 99.0f;
            gMes->pos.y = 45.0f;
            gMes->tpLvl = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->work = 189;
            gMes->unk0C = 195;
            HuSprPosSet(gMes->strGId[1], 0, gMes->work, gMes->unk0C);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            HuSprPosSet(gMes->strGId[2], 0, gMes->work, gMes->unk0C);
            for (i = 0; i < exclLen; i++) {
                HuSprDispOff(gMes->strGId[2], 1);
                HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                HuSprTPLvlSet(gMes->strGId[2], i + 1, 255);
            }
            omSysPauseDisableF = 1;
            omMgActiveF = 0;
            gMes->subMode = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->scale.y = gMes->scale.x += 0.033333335f;
            gMes->pos.x = sindf(gMes->unk10) * 20.0f + 94.0f;
            gMes->pos.y += 5.0f;
            gMes->tpLvl += 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->pos.x, gMes->pos.y);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->scale.x, gMes->scale.x);
                HuSprTPLvlSet(gMes->strGId[0], i + 1, gMes->tpLvl);
            }
            gMes->work = sindf(gMes->unk10) * 20.0f + 194.0f;
            gMes->unk0C -= 5;
            HuSprPosSet(gMes->strGId[1], 0, gMes->work, gMes->unk0C);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->scale.y, gMes->scale.y);
                HuSprTPLvlSet(gMes->strGId[1], i + 1, gMes->tpLvl);
            }
            if (gMes->time >= 15) {
                gMes->work = 330;
                HuSprPosSet(gMes->strGId[2], 0, gMes->work, gMes->unk0C);
                for (i = 0; i < gotLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                    HuSprTPLvlSet(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0; i < itemLen; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                    HuSprTPLvlSet(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0; i < exclLen; i++) {
                    HuSprDispOn(gMes->strGId[2], i + 1);
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                    HuSprTPLvlSet(gMes->strGId[2], i + 1, 255);
                }
                gMes->subMode = 2;
            }
            break;
        case 2:
            gMes->work -= 16;
            HuSprPosSet(gMes->strGId[2], 0, gMes->work, gMes->unk0C);
            if (gMes->time >= 20) {
                gMes->subMode = 3;
                gMes->unk10 = 630.0f;
            }
            break;
        case 3:
            gMes->scale.x = sindf(gMes->unk10) * 0.5f + 1.5f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < exclLen; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->scale.x, gMes->scale.x);
            }
            if (gMes->time >= 40) {
                for (i = 0; i < exclLen; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                }
                gMes->subMode = 4;
            }
            break;
        case 4:
            if (gMes->time >= gMes->timeMax) {
                gMes->subMode = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->time >= 31) {
        gMes->stat = GMES_STAT_TIMEEND;
    }
    return result;
}

void GMesFontMesCreate(const s16 *str, s32 flags) {
    u8 *buf = HuMemMemoryAllocPerm(0x200);
    u8 *c = buf;

    GameMesStrConv(buf, (u8 *)str);
    while (*c != 0) {
        GameMesCharCreate(c, flags);
        c += (c[1] == 0x80 || c[1] == 0x81);
        c++;
    }
    GameMesDebugF = 1;
    HuMemMemoryFreePerm(buf);
}

u16 GameMesCharConv(u16 code) {
    u16 tmp;
    s32 i;

    for (i = 0; gMesDakuTbl[i] != 0; i += 2) {
        tmp = (gMesDakuTbl[i] << 8) | gMesDakuTbl[i + 1];
        if (tmp == code) {
            tmp = (gMesDakuBaseTbl[i] << 8) | gMesDakuBaseTbl[i + 1];
            return (HuWinMesCharConv((u8 *)&tmp) << 8) | 0x80;
        }
    }
    for (i = 0; gMesHandakuTbl[i] != 0; i += 2) {
        tmp = (gMesHandakuTbl[i] << 8) | gMesHandakuTbl[i + 1];
        if (tmp == code) {
            tmp = (gMesHandakuBaseTbl[i] << 8) | gMesHandakuBaseTbl[i + 1];
            return (HuWinMesCharConv((u8 *)&tmp) << 8) | 0x81;
        }
    }
    return HuWinMesCharConv((u8 *)&code) << 8;
}

s32 GameMesStrConv(u8 *dst, u8 *src) {
    u16 code;
    s32 len = 0;
    u8 *p = src;

    while (*p != 0) {
        code = GameMesCharConv((p[0] << 8) | p[1]);
        if (code & 0xFF) {
            dst[0] = code >> 8;
            dst[1] = code;
            dst += 2;
            p += 2;
            len += 2;
        } else {
            *dst++ = code >> 8;
            len++;
            p += 2;
        }
    }
    *dst = 0;
    return len + 1;
}

s32 GameMesStrConv2(void *arg0, void *arg1) {
    return GameMesStrConv(arg0, arg1);
}

void GameMesMgStub(s32 mgIndex) {
}

s32 GameMesOvlTypeGet(void) {
    switch (omovl) {
        case 0x1:
        case 0x2:
        case 0x6:
        case 0x1B:
        case 0x1D:
        case 0x1E:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x34:
        case 0x38:
        case 0x41:
            return 120;
        case 0xF:
            return 190;
        case 0x13:
        case 0x27:
        case 0x2C:
        case 0x43:
            return 160;
        default:
            return 180;
    }
}

s32 GameMesOvlOfsGet(void) {
    switch (omovl) {
        case 2:
            return 20;
        case 3:
            return -20;
        default:
            return 0;
    }
}
