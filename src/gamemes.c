#include "game/gamemes.h"
#include "game/audio.h"
#include "game/sprite.h"
#include "game/gamework_data.h"
#include "math.h"
#include "stdarg.h"
#include "gcc/string.h"
#include "include_asm.h"

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
extern s8 HmfPauseF;

s32 func_80037574_main(GAMEMES *gMes, Gfx **);
s32 func_80037878_main(GAMEMES *gMes, Gfx **);
s32 func_80037C44_main(GAMEMES *gMes, Gfx **);
s32 func_8003843C_main(GAMEMES *gMes, Gfx **);
s32 func_80038934_main(GAMEMES *gMes, Gfx **);
s32 func_80038D78_main(GAMEMES *gMes, Gfx **);
s32 func_800392AC_main(GAMEMES *gMes, Gfx **);
s32 func_8003966C_main(GAMEMES *gMes, Gfx **);
s32 func_80039A6C_main(GAMEMES *gMes, Gfx **);
s32 func_80039E80_main(GAMEMES *gMes, Gfx **);
s32 func_8003A2EC_main(GAMEMES *gMes, Gfx **);
s32 func_8003B14C_main(GAMEMES *gMes, Gfx **);
s32 func_8003B7E8_main(GAMEMES *gMes, Gfx **);
s32 func_8003BB84_main(GAMEMES *gMes, Gfx **);
s32 func_8003C248_main(GAMEMES *gMes, Gfx **);
s32 func_8003C644_main(GAMEMES *gMes, Gfx **);
s32 func_8003CA24_main(GAMEMES *gMes, Gfx **);
s32 func_8003CE20_main(GAMEMES *gMes, Gfx **);
s32 func_8003D134_main(GAMEMES *gMes, Gfx **);
s32 func_8003D4DC_main(GAMEMES *gMes, Gfx **);
s32 func_8003D890_main(GAMEMES *gMes, Gfx **);
s32 func_8003DC88_main(GAMEMES *gMes, Gfx **);
s32 func_8003DE60_main(GAMEMES *gMes, Gfx **);
s32 func_8003E4A4_main(GAMEMES *gMes, Gfx **);
s32 func_8003EBC8_main(GAMEMES *gMes, Gfx **);
s32 func_8003EE98_main(GAMEMES *gMes, Gfx **);
s32 GMesTimerExec(GAMEMES *gMes, Gfx **);
s32 func_8003F604_main(GAMEMES *gMes, Gfx **);
s32 func_8003FD34_main(GAMEMES *gMes, Gfx **);
s32 func_8003FFD0_main(GAMEMES *gMes, Gfx **);
s32 func_80040290_main(GAMEMES *gMes, Gfx **);
s32 func_800407B8_main(GAMEMES *gMes, Gfx **);
s32 func_80040CF4_main(GAMEMES *gMes, Gfx **);
s32 func_80041700_main(GAMEMES *gMes, Gfx **);
s32 func_80041B68_main(GAMEMES *gMes, Gfx **);
s32 func_80042AC8_main(GAMEMES *gMes, Gfx **);
s32 func_800440D4_main(GAMEMES *gMes, Gfx **);
s32 func_800448C0_main(GAMEMES *gMes, Gfx **);
s32 func_800452C4_main(void);
s32 func_80045314_main(void);
s32 func_80036610_main(void);
void func_800452BC_main(s32 mgIndex);
s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 arg2, s16 arg3, s16 arg4);

extern u16 D_800D530C_main;
extern u16 D_800D1100_main;
extern u8 D_800D6A58_main;
extern s8 D_800B1A50_main;
extern u8 gMesCloseF;
extern u8 D_800B1A52_main;
extern s8 gMesTimerId;
extern u16 D_800B1A54_main;
extern s16 D_800B1A58_main[];
extern s16 D_800B1A70_main[];
extern s16 D_800B1A88_main[];
extern s16 D_800B1AC0_main[];
extern s16 D_800B1AF8_main[];
extern s16 D_800B1B30_main[];
extern s16 D_800B1B50_main[];
extern s16 D_800B1B70_main[];
extern GAMEMES gMesData[];
extern GMesChar D_800B1BC0_main[32];
extern Vec2f D_800A1380_main[];
extern s32 omovl;

s32 func_80036610_main(void) {
    return GwSystem.minigame_index;
}

void GMesInit(void) {
    s16 i;

    D_800B1A50_main = 0;
    for (i = 0; i < 8; i++) {
        gMesData[i].mesNo = 0;
    }
    for (i = 0; i < 9; i++) {
        D_800B1A58_main[i] = D_800B1A70_main[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        D_800B1A88_main[i] = D_800B1AC0_main[i] = D_800B1AF8_main[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        D_800B1B30_main[i] = D_800B1B50_main[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        D_800B1B70_main[i] = -1;
    }
    gMesCloseF = FALSE;
    gMesTimerId = -1;
    D_800B1A52_main = 0;
}

void GMesExec(Gfx **arg0) {
    s16 result = FALSE;
    s16 i, j;

    if (HmfPauseF != 0 && !gMesCloseF) {
        return;
    }
    for (i = 0; i < 8; i++) {
        if (gMesData[i].stat != GMES_STAT_NONE) {
            GAMEMES *gMes = &gMesData[i];

            switch (gMes->mesNo) {
                case GMES_MES_0:
                    result = func_80037574_main(gMes, arg0);
                    break;
                case GMES_MES_1:
                    result = func_80037878_main(gMes, arg0);
                    break;
                case GMES_MES_2:
                    result = func_80037C44_main(gMes, arg0);
                    break;
                case GMES_MES_3:
                    result = func_8003843C_main(gMes, arg0);
                    break;
                case GMES_MES_4:
                    result = func_80038934_main(gMes, arg0);
                    break;
                case GMES_MES_5:
                    result = func_80038D78_main(gMes, arg0);
                    break;
                case GMES_MES_MG_START:
                    result = func_800392AC_main(gMes, arg0);
                    break;
                case GMES_MES_7:
                    result = func_8003966C_main(gMes, arg0);
                    break;
                case GMES_MES_8:
                    result = func_80039A6C_main(gMes, arg0);
                    break;
                case GMES_MES_9:
                    result = func_80039E80_main(gMes, arg0);
                    break;
                case GMES_MES_10:
                    result = func_8003A2EC_main(gMes, arg0);
                    break;
                case GMES_MES_11:
                    result = func_8003B14C_main(gMes, arg0);
                    break;
                case GMES_MES_12:
                    result = func_8003B7E8_main(gMes, arg0);
                    break;
                case GMES_MES_13:
                    result = func_8003BB84_main(gMes, arg0);
                    break;
                case GMES_MES_14:
                    result = func_8003C248_main(gMes, arg0);
                    break;
                case GMES_MES_15:
                    result = func_8003C644_main(gMes, arg0);
                    break;
                case GMES_MES_16:
                    result = func_8003CA24_main(gMes, arg0);
                    break;
                case GMES_MES_MG_FINISH:
                    result = func_8003CE20_main(gMes, arg0);
                    break;
                case GMES_MES_18:
                    result = func_8003D134_main(gMes, arg0);
                    break;
                case GMES_MES_19:
                    result = func_8003D4DC_main(gMes, arg0);
                    break;
                case GMES_MES_20:
                    result = func_8003D890_main(gMes, arg0);
                    break;
                case GMES_MES_21:
                    result = func_8003DC88_main(gMes, arg0);
                    break;
                case GMES_MES_MG_LOSER:
                    result = func_8003E4A4_main(gMes, arg0);
                    break;
                case GMES_MES_24:
                    result = func_8003EBC8_main(gMes, arg0);
                    break;
                case GMES_MES_25:
                    result = func_8003EE98_main(gMes, arg0);
                    break;
                case GMES_MES_TIMER:
                    result = GMesTimerExec(gMes, arg0);
                    break;
                case GMES_MES_MG_RECORD:
                    result = func_8003F604_main(gMes, arg0);
                    break;
                case GMES_MES_31:
                    result = func_8003FD34_main(gMes, arg0);
                    break;
                case GMES_MES_33:
                    result = func_8003FFD0_main(gMes, arg0);
                    break;
                case GMES_MES_29:
                    result = func_80040290_main(gMes, arg0);
                    break;
                case GMES_MES_28:
                    result = func_800407B8_main(gMes, arg0);
                    break;
                case GMES_MES_MG_DRAW:
                    result = func_80041700_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNER:
                    result = func_8003DE60_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_2:
                    result = func_80040CF4_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_3:
                    result = func_80041B68_main(gMes, arg0);
                    break;
                case GMES_MES_MG_WINNERS_4:
                    result = func_80042AC8_main(gMes, arg0);
                    break;
                case GMES_MES_36:
                    result = func_800440D4_main(gMes, arg0);
                    break;
                case GMES_MES_37:
                    result = func_800448C0_main(gMes, arg0);
                    break;
            }
            gMes->unk04++;
            if (gMes->unk04 >= 0x4000) {
                gMes->unk04 = 0x2000;
            }
            if (result == FALSE) {
                gMes->stat = GMES_STAT_NONE;
                if (D_800B1A52_main == 0) {
                    for (j = 0; j < GMES_MAX; j++) {
                        if (gMesData[j].stat != GMES_STAT_NONE && gMesData[j].mesNo != GMES_MES_TIMER) {
                            break;
                        }
                    }
                    if (j == GMES_MAX) {
                        func_80037258_main();
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
    gMes->unk04 = 0;
    gMes->unk60 = 160.0f;
    gMes->unk64 = 120.0f;
    gMes->unk6C = 1.0f;
    gMes->unk68 = 1.0f;
    gMes->unk70 = 0;
    gMes->unk03 = 0xFF;
    gMes->unk06 = 0x3C;
    gMes->unk0E = 0;
    gMes->unk0C = 0;
    gMes->unk0A = 0;
    gMes->unk08 = 0;
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
            gMes->unk06 = 0x2D;
            break;
        case GMES_MES_MG_DRAW:
            gMes->unk06 = 0x82;
            break;
        case GMES_MES_MG_RECORD:
            gMes->unk60 = 160.0f;
            gMes->unk64 = 180.0f;
            break;
        case GMES_MES_MG_WINNER:
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk64 = func_800452C4_main();
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_29:
        case GMES_MES_36:
        case GMES_MES_37:
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_LOSER:
            gMes->unk0E = chr = va_arg(args, s32);
            break;
        case GMES_MES_24:
        case GMES_MES_25:
            gMes->unk1C = va_arg(args, s32);
            gMes->unk60 = va_arg(args, s32);
            gMes->unk64 = va_arg(args, s32);
            gMes->unk68 = va_arg(args, f64);
            gMes->unk6C = va_arg(args, f64);
            gMes->unk02 = va_arg(args, s32);
            break;
        case GMES_MES_TIMER:
            gMesTimerId = mesId;
            gMes->unk08 = va_arg(args, s32);
            gMes->unk60 = va_arg(args, s32);
            gMes->unk64 = va_arg(args, s32);
            gMes->unk60 = 160.0f;
            gMes->unk64 = 28.0f;
            break;
        case GMES_MES_MG_WINNERS_2:
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_WINNERS_3:
            gMes->unk0A = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk64 = func_80045314_main();
            gMes->unk06 = 0x78;
            break;
        case GMES_MES_MG_WINNERS_4:
            gMes->unk08 = chr = va_arg(args, s32);
            gMes->unk0A = chr = va_arg(args, s32);
            gMes->unk0C = chr = va_arg(args, s32);
            gMes->unk0E = chr = va_arg(args, s32);
            gMes->unk06 = 0x78;
            break;
    }
    D_800B1A54_main = 0x5A;
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

u8 func_800370A4_main(s16 i) {
    return gMesData[i].stat;
}

void func_800370D0_main(s16 i, s16 value) {
    if (value == -1) {
        value = 0x7FFF;
    }
    gMesData[i].unk06 = value;
}

void GMesPosSet(s16 i, f32 x, f32 y) {
    gMesData[i].unk60 = x;
    gMesData[i].unk64 = y;
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
    func_80037258_main();
    D_800B1A52_main = 0;
}

s32 func_800371DC_main(void) {
    s32 stat;
    s16 countdown;

    if (HmfPauseF != 0) {
        return TRUE;
    }
    if (D_800D530C_main != 0) {
        return TRUE;
    }
    stat = GMesStatGet();
    if (stat == GMES_STAT_NONE || (stat & 2) != 0) {
        countdown = D_800B1A54_main - 1;
        D_800B1A54_main = countdown;
        if (countdown < 0) {
            return FALSE;
        }
    }
    return TRUE;
}

void func_8003724C_main(s16 countdown) {
    D_800B1A54_main = countdown;
}

void func_80037258_main(void) {
    s16 i;

    for (i = 0; i < 9; i++) {
        if (i == 2 && gMesTimerId != -1) {
            continue;
        }
        if (D_800B1A58_main[i] != -1) {
            HuSprKill(D_800B1A58_main[i]);
        }
        if (D_800B1A70_main[i] != -1) {
            HuSprKill(D_800B1A70_main[i]);
        }
        D_800B1A58_main[i] = D_800B1A70_main[i] = -1;
    }
    for (i = 0; i < 27; i++) {
        if (D_800B1A88_main[i] != -1) {
            HuSprKill(D_800B1A88_main[i]);
        }
        if (D_800B1AC0_main[i] != -1) {
            HuSprKill(D_800B1AC0_main[i]);
        }
        if (D_800B1AF8_main[i] != -1) {
            HuSprKill(D_800B1AF8_main[i]);
        }
        D_800B1A88_main[i] = D_800B1AC0_main[i] = D_800B1AF8_main[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        if (D_800B1B30_main[i] != -1) {
            HuSprKill(D_800B1B30_main[i]);
        }
        if (D_800B1B50_main[i] != -1) {
            HuSprKill(D_800B1B50_main[i]);
        }
        D_800B1B30_main[i] = D_800B1B50_main[i] = -1;
    }
    for (i = 0; i < 37; i++) {
        if (D_800B1B70_main[i] != -1) {
            HuSprKill(D_800B1B70_main[i]);
        }
        D_800B1B70_main[i] = -1;
    }
}

void GMesSprKill(GAMEMES *gMes) {
    s16 i;

    for (i = 0; i < 16; i++) {
        if (gMes->strGId[i] != -1) {
            HuSprGrpKill(gMes->strGId[i]);
        }
        if (gMes->strSprId[i] != -1) {
            HuSprKill(gMes->strSprId[i]);
        }
    }
}

s32 func_80037574_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len = strlen("START");
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, "START", 1, -1, -1);
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 0.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 0);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, gMes->unk04 * 0.05f);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk04 * 12);
            }
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            }
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 3;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            gMes->stat = 2;
            gMes->unk0A += 6;
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, cosdf(gMes->unk0A));
            }
            if (gMes->unk04 >= gMes->unk06) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return result;
}

s32 func_80037878_main(GAMEMES *gMes, Gfx **gfx) {
    char *str = "START";
    s32 len = strlen(str);
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 3;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str, 1, -1, -1);
            gMes->unk6C = gMes->unk68 = 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk03 = 0;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk68 = gMes->unk10 + 0.3f;
            gMes->unk6C = gMes->unk10 + 0.3f;
            gMes->unk64 = 120.0f - sindf(gMes->unk0A) * 20.0f;
            gMes->unk03 += 12;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 2;
                func_80054904_main(gMes->strGId[0], 0, 160, 120);
                for (i = 0; i < len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            }
            break;
        case 2:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return result;
}

s32 func_80037C44_main(GAMEMES *gMes, Gfx **gfx) {
    char *str = "START";
    s32 len = strlen(str);
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, str, 1, -1, -1);
            gMes->unk6C = gMes->unk68 = 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 40.0f;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, 0);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            gMes->unk68 = gMes->unk10 + 0.3f;
            gMes->unk6C = gMes->unk10 + 0.3f;
            gMes->unk60 = 160.0f;
            gMes->unk64 += gMes->unk14;
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, sindf(gMes->unk0C) * 255.0f);
            }
            gMes->unk0C += 6;
            gMes->unk10 += 0.7f / 15;
            gMes->unk14 += 0.8f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -5.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                for (i = 0; i < len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -3.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                gMes->unk08 = 3;
            }
            break;
        case 3:
            func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                gMes->unk08 = 4;
            }
            break;
        case 4:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 38) {
        func_800452BC_main(func_80036610_main());
    }
    return result;
}

/*
 * Shared state handling for the GMES_MES_3..10 "START" variants. State 0 resets the
 * per-character work and builds the string sprites, state 6 tears everything down.
 * The callers implement the remaining states (1: animate in, 2: hold, 5: shrink out).
 * The empty cases are needed for the compiler to emit the original jump tables.
 */
s32 func_80038208_main(GAMEMES *gMes) {
    s32 len = strlen("START");
    s32 result;
    s32 i;
    GMesChar *chr;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 6;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            for (i = 0; i < 32; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = chr->y = chr->velX = chr->velY = chr->angle = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 128;
                chr->unk34 = 0;
                chr->time = 0;
            }
            func_8003A37C_main(gMes, "START", 1, -1, -1);
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
            }
            gMes->unk04 = gMes->unk0A = gMes->unk0C = gMes->unk0E = 0;
            gMes->unk06 = 0;
            gMes->unk60 = gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
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
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 60) {
        HuAudFXPlay(0x251);
    }
    if (gMes->unk04 == 80) {
        func_800452BC_main(func_80036610_main());
    }
    return result;
}

s32 func_8003843C_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len = strlen("START");
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_80038208_main(gMes);
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->angle = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
                HuSprAttrSet(gMes->strGId[0], i + 1, 2);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            chr = &D_800B1BC0_main[0];
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrReset(gMes->strGId[0], i + 1, 2);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->unk04 > 10) {
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
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
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
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_80038934_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;
    f32 t;

    result = func_80038208_main(gMes);
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->startX = chr->x = D_800A1380_main[i].x;
                chr->startY = chr->y = D_800A1380_main[i].y;
                chr->endX = i * 22 - (len - 1) * 11;
                chr->endY = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            gMes->unk0C = 0;
            gMes->unk0A = 0;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                gMes->unk0C = 0;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    t = 0.0f;
                    if (gMes->unk04 > 30.0f / len * i) {
                        if (chr->time > 30) {
                            t = 1.0f;
                        } else {
                            t = chr->time * (1.0f / 30.0f);
                            chr->time++;
                        }
                    }
                    chr->x = t * (chr->endX - chr->startX) + chr->startX;
                    chr->y = t * (chr->endY - chr->startY) + chr->startY;
                    func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_80038D78_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_80038208_main(gMes);
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
                HuSprAttrSet(gMes->strGId[0], i + 1, 2);
            }
            gMes->unk08 = 1;
            gMes->unk0E = 0;
            gMes->unk0C = 0;
            gMes->unk0A = 0;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->unk04 > 10) {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    if (gMes->unk04 - 10 > 50.0f / len * i) {
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
                    chr = &D_800B1BC0_main[i];
                    chr->time = 0;
                    HuSprAttrSet(gMes->strGId[0], i + 1, 2);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_800392AC_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_80038208_main(gMes);
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.3f, 0.3f);
                func_80055458_main(gMes->strGId[0], i + 1, 128);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->unk04 > 38) {
                scale = 1.0f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else if (gMes->unk04 > 30) {
                scale = 1.5f - (gMes->unk04 - 30.0f) * 0.5f * 0.125f;
                for (i = 0; i < len; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
                }
            } else if (gMes->unk04 > 10) {
                scale = (gMes->unk04 - 10) * 1.2f * 0.05f + 0.3f;
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
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_8003966C_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_80038208_main(gMes);
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = -120.0f - i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->unk0A == 0) {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
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
                    func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_80039A6C_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_80038208_main(gMes);
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 144.0f + i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 > 60) {
                gMes->unk08 = 2;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            } else if (gMes->unk0A == 0) {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
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
                    func_80054904_main(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, 160, 120);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_80039E80_main(GAMEMES *gMes, Gfx **gfx) {
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
    result = func_80038208_main(gMes);
    t = 1.0f;
    left = 55.0f;
    right = 265.0f;
    top = 12.0f;
    bottom = 228.0f;
    len = strlen("START");
    switch (gMes->unk08) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 128);
            }
            func_80054904_main(gMes->strGId[0], 0, 0, 0);
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            break;
        case 1:
            if (gMes->unk0A < 4) {
                if (gMes->unk0A == 0) {
                    startX = left;
                    startY = top;
                    endX = right;
                    endY = (bottom - startY) * 0.5f;
                    if (gMes->unk0C < 5) {
                        t = gMes->unk0C * 0.2f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 1;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 1) {
                    startX = right;
                    startY = (bottom - top) * 0.5f;
                    endX = (startX - left) * 0.5f;
                    endY = bottom;
                    if (gMes->unk0C < 7) {
                        t = gMes->unk0C * (1.0f / 7.0f);
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 2;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 2) {
                    startX = (right - left) * 0.5f;
                    startY = bottom;
                    endX = left;
                    endY = 120.0f;
                    if (gMes->unk0C < 8) {
                        t = gMes->unk0C * 0.125f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 3;
                        gMes->unk0C = 0;
                    }
                } else if (gMes->unk0A == 3) {
                    startX = left;
                    startY = 120.0f;
                    endX = 160.0f;
                    endY = 120.0f;
                    if (gMes->unk0C < 10) {
                        t = gMes->unk0C * 0.1f;
                        gMes->unk0C++;
                    } else {
                        gMes->unk0A = 4;
                        gMes->unk0C = 0;
                    }
                }
                x = (endX - startX) * t + startX;
                y = (endY - startY) * t + startY;
            } else {
                x = 160.0f;
                y = 120.0f;
                gMes->unk08 = 2;
                gMes->unk0C = 0;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    chr->alpha = 255;
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
            }
            func_80054904_main(gMes->strGId[0], 0, x, y);
            break;
        case 2:
            if (gMes->unk04 >= 90) {
                gMes->unk08 = 5;
                gMes->unk0A = 0;
            }
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            if (gMes->unk0A < 6) {
                scale = cosdf(gMes->unk0A * 15.0f);
                gMes->unk0A++;
            } else {
                scale = 0.0f;
                gMes->unk08 = 6;
            }
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, scale, scale);
            }
            gMes->stat = 2;
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_8003A2EC_main(GAMEMES *gMes, Gfx **gfx) {
    return func_80039E80_main(gMes, gfx);
}

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A308_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A37C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A3C4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A81C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A9C8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AC9C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AE44_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AE9C_main);

void func_8003B128_main(GAMEMES *gMes) {
    GMesSprKill(gMes);
    func_80037258_main();
}

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003B14C_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003B170_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003B4D8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003B7E8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003BB84_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C058_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C248_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003C644_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CA24_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003CE20_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D134_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D4DC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003D890_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003DC88_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003DCA4_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A76F8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7700_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7708_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7714_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A771C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7724_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A772C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7734_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A773C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7744_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003DE60_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003E4A4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003EBC8_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003EE98_main);

s32 GMesTimerExec(GAMEMES *gMes, Gfx **arg1) {
    f32 temp_f22;
    u8 temp_s2;
    u8 temp_s0;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, "99", 0, -1, -1);
        func_80054904_main(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
        func_80055458_main(gMes->strGId[0], 1, 0x100);
        func_80055458_main(gMes->strGId[0], 2, 0x100);
        gMes->unk0A = 0;
    }
    temp_s2 = gMes->unk08 % 100;
    temp_s0 = temp_s2 / 10;
    if (temp_s0 == 0) {
        HuSprAttrSet(gMes->strGId[0], 1, 0x8000);
    } else {
        HuSprAttrReset(gMes->strGId[0], 1, 0x8000);
    }
    func_80055140_main(gMes->strGId[0], 1, temp_s0, 0);
    func_800550F4_main(gMes->strGId[0], 1, 1);
    temp_s0 = temp_s2 % 10;
    func_80055140_main(gMes->strGId[0], 2, temp_s0, 0);
    func_800550F4_main(gMes->strGId[0], 2, 1);
    switch (gMes->unk0A) {
        case 0:
            if (gMes->unk04 < 14) {
                temp_f22 = sindf(gMes->unk04 * 10.0f) * 5.0f + (1.0f - sindf(130.0f) * 5.0f);
                HuSprScaleSet(gMes->strGId[0], 1, temp_f22, temp_f22);
                HuSprScaleSet(gMes->strGId[0], 2, temp_f22, temp_f22);
            } else {
                gMes->unk0A = 1;
            }
            break;
        case 1:
            if (gMes->unk0E != gMes->unk08 && gMes->unk08 < 6) {
                gMes->unk0C = 0;
                if (gMes->unk08 != 0) {
                    gMes->unk0A = 3;
                    HuAudFXPlay(8);
                }
            } else {
                func_80055458_main(gMes->strGId[0], 1, 0x100);
                func_80055458_main(gMes->strGId[0], 2, 0x100);
            }
            break;
        case 2:
            if (gMes->unk0C < 10) {
                func_80055458_main(gMes->strGId[0], 1, 230 - gMes->unk0C * 23);
                func_80055458_main(gMes->strGId[0], 2, 230 - gMes->unk0C * 23);
            } else {
                gMes->unk0A = 1;
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
                func_80055458_main(gMes->strGId[0], 1, temp_f22);
                func_80055458_main(gMes->strGId[0], 2, temp_f22);
            } else {
                gMes->unk0A = 1;
            }
            gMes->unk0C++;
            break;
    }
    gMes->unk0E = gMes->unk08;
    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        gMesTimerId = -1;
        return FALSE;
    }
    return TRUE;
}

// GMesUpdate? GMesTimerUpdate? GMesTimerSet?
void func_8003F578_main(s16 arg0) {
    if (gMesTimerId < 0 || arg0 < 0) {
        return;
    }
    gMesData[gMesTimerId].unk08 = arg0;
}

// GMesTimerKill?
void func_8003F5C0_main(void) {
    if (gMesTimerId < 0) {
        return;
    }
    gMesData[gMesTimerId].unk0A = 2;
    gMesData[gMesTimerId].unk0C = 0;
}

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003F604_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003FD34_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003FFD0_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80040290_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800407B8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A77BC_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", jtbl_800A77C0_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80040CF4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80041700_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7810_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7830_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80041B68_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80042AC8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78C8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78CC_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800440D4_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800448C0_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_80045010_main);

INCLUDE_ASM("asm/nonmatchings/gamemes", func_800450B8_main);

s32 func_80045208_main(void *arg0, void *arg1);
INCLUDE_ASM("asm/nonmatchings/gamemes", func_80045208_main);

s32 func_800452A0_main(void *arg0, void *arg1) {
    return func_80045208_main(arg0, arg1);
}

void func_800452BC_main(s32 mgIndex) {
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A78F4_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", jtbl_800A78F8_main);

s32 func_800452C4_main(void) {
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

s32 func_80045314_main(void) {
    switch (omovl) {
        case 2:
            return 20;
        case 3:
            return -20;
        default:
            return 0;
    }
}
