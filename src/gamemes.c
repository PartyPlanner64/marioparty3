#include "game/gamemes.h"
#include "game/audio.h"
#include "game/sprite.h"
#include "game/gamework_data.h"
#include "game/data.h"
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
s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4);
s16 func_8003A3C4_main(GAMEMES *gMes, u8 *str, u8 flags, s16 x, s16 arg4, f32 scaleX, f32 scaleY);
s16 func_8005B5EC_main(u8 *str);
s32 func_8003B4D8_main(GAMEMES *gMes, s32 fileNo, s32 seNo);
s32 func_8003C058_main(GAMEMES *gMes);
void func_8003DCA4_main(GAMEMES *gMes, s32 fileNo);
u32 func_8003A81C_main(u8 *str, u8 flags);
s32 func_8003A9C8_main(u8 *str, s32 flags, s32 *idx);
s32 func_8003AC9C_main(u8 *str, s32 mode, u8 flags, s32 *width);
s16 func_8003AE44_main(s16 fileNo);
s16 func_8003AE9C_main(u8 c, u8 flags);
s32 func_80045208_main(u8 *dst, u8 *src);
u16 func_800450B8_main(u16 code);
u8 func_8005FA90_main(u8 *str);
void *HuMemMemoryAllocPerm(u32 size);
void HuMemMemoryFreePerm(void *ptr);

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
extern Vec2f D_800A13D8_main[];
extern u8 D_800A13B0_main[];
extern char *D_800A1410_main[];
extern u8 D_800A1334_main[];
extern u8 D_800A136C_main[];
extern s32 omovl;
extern s32 D_800A1434_main[5][2];
extern s32 D_800A145C_main[5][2];
extern s32 D_800A1484_main[5][2];
extern u8 D_800A14AC_main[];
extern u8 D_800A1500_main[];
extern u8 D_800A1554_main[];
extern u8 D_800A156C_main[];

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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
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
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 2;
                HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
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
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
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
                HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                for (i = 0; i < len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -3.0f;
                HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
                gMes->unk08 = 3;
            }
            break;
        case 3:
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->angle = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->startX = chr->x = D_800A1380_main[i].x;
                chr->startY = chr->y = D_800A1380_main[i].y;
                chr->endX = i * 22 - (len - 1) * 11;
                chr->endY = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
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
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = -120.0f - i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
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
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 144.0f + i * 7.2000003f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
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
                    HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
                }
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
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
            HuSprPosSet(gMes->strGId[0], 0, 0, 0);
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
            HuSprPosSet(gMes->strGId[0], 0, x, y);
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

s16 func_8003A308_main(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4) {
    s16 i;

    for (i = 0; i < GMES_STRMAX; i++) {
        gMes->strSprId[i] = gMes->strGId[i] = HUSPR_NONE;
    }
    return func_8003A37C_main(gMes, str, flags, arg3, arg4);
}

s16 func_8003A37C_main(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4) {
    return func_8003A3C4_main(gMes, (u8 *)str, flags, arg3, arg4, 1.0f, 1.0f);
}

#ifdef NON_MATCHING
/* Unused arg4 is loaded into a saved register and charW is copied between registers in the target. */
s16 func_8003A3C4_main(GAMEMES *gMes, u8 *str, u8 flags, s16 x, s16 arg4, f32 scaleX, f32 scaleY) {
    s16 animId = -1;
    s16 len;
    s16 i;
    s16 grp;
    s16 member;
    s16 width;
    s32 charW;
    s16 y;
    u32 code;
    u8 *p;

    len = func_8005B5EC_main(str);
    for (i = 0; i < GMES_STRMAX; i++) {
        if (gMes->strSprId[i] == HUSPR_NONE && gMes->strGId[i] == HUSPR_NONE) {
            break;
        }
    }
    grp = gMes->strGId[i] = HuSprGrpCreate(len + 1, 5);
    charW = (flags & 1) ? 22 : 15;
    width = 0;
    for (p = str; *p != 0; p++) {
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
    for (member = 1; *str != 0; member++) {
        code = func_8003A81C_main(str, flags);
        animId = code >> 16;
        func_80055024_main(grp, member, animId, code & 0xFF);
        y = 0;
        if (*str >= 0xD0 && *p < 0xF0) {
            y = -2;
        }
        HuSprPosSet(grp, member, x, y);
        func_80055458_main(grp, member, 255);
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
        func_800554C4_main(grp, member, 0);
        str += (str[1] == 0x80 || str[1] == 0x81);
        str++;
    }
    func_80055024_main(grp, 0, animId, 0);
    HuSprAttrSet(grp, 0, 0x8000);
    func_800554C4_main(grp, 0, -1);
    return i;
}
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003A3C4_main);
#endif

u32 func_8003A81C_main(u8 *str, u8 flags) {
    u8 c = str[0];
    s32 idx = 0;
    s32 type;
    s16 animId;

    type = func_8003A9C8_main(str, 0, &idx);
    if (type == 2) {
        if (flags & 1) {
            if (D_800B1A70_main[2] == -1) {
                animId = D_800B1A70_main[2] = func_8003AE44_main(0x87);
            } else {
                animId = D_800B1A70_main[2];
            }
        } else {
            if (D_800B1A58_main[2] == -1) {
                animId = D_800B1A58_main[2] = func_8003AE44_main(0x86);
            } else {
                animId = D_800B1A58_main[2];
            }
        }
    } else if (type == 4) {
        if (D_800B1A58_main[4] == -1) {
            animId = D_800B1A58_main[4] = func_8003AE44_main(0x88);
        } else {
            animId = D_800B1A58_main[4];
        }
    } else if (type == 5) {
        if (D_800B1A58_main[5] == -1) {
            animId = D_800B1A58_main[5] = func_8003AE44_main(0x89);
        } else {
            animId = D_800B1A58_main[5];
        }
    } else if (type == 6) {
        if (D_800B1A58_main[6] == -1) {
            animId = D_800B1A58_main[6] = func_8003AE44_main(0x8A);
        } else {
            animId = D_800B1A58_main[6];
        }
    } else if (type == 7) {
        if (D_800B1A58_main[7] == -1) {
            animId = D_800B1A58_main[7] = func_8003AE44_main(0x8B);
        } else {
            animId = D_800B1A58_main[7];
        }
    } else if (type == 8) {
        animId = func_8003AE9C_main(c, flags);
    } else if (type == 0) {
        animId = func_8003AE9C_main(c, flags);
    } else if (type == 1) {
        animId = func_8003AE9C_main(c, flags);
    } else {
        idx = 0;
        animId = func_8003AE9C_main(c, flags);
    }
    return (animId << 16) | idx;
}

s32 func_8003A9C8_main(u8 *str, s32 flags, s32 *idx) {
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
                    if (c == D_800A136C_main[i]) {
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
                if (c == D_800A1334_main[i]) {
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
                    if (c == D_800A136C_main[i]) {
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
                if (c == D_800A1334_main[i]) {
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

s32 func_8003AC9C_main(u8 *str, s32 mode, u8 flags, s32 *width) {
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

s16 func_8003AE44_main(s16 fileNo) {
    void *data = DataReadTemp(fileNo | 0xC0000);
    s16 animId = HuSprAnimRead(data);

    DataCloseTemp(data);
    return animId;
}

#ifdef NON_MATCHING
/* Only diff: target has an extra andi 0xFF after the lbu from D_800A13B0_main in the search loop,
   as if the loaded byte were kept live past the comparison. */
s16 func_8003AE9C_main(u8 c, u8 flags) {
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
            animId = &D_800B1AF8_main[c - 'A'];
        } else {
            fileNo = 0xC0000 + (c - 'A');
            animId = &D_800B1AC0_main[c - 'A'];
        }
    } else if (c >= 'a' && c <= 'z') {
        fileNo = 0xC0025 + (c - 'a');
        animId = &D_800B1A88_main[c - 'a'];
    } else if ((c >= 0x90 && c <= 0xAF) || (c >= 0xD0 && c <= 0xEF)) {
        for (idx = 0; idx < 36; idx++) {
            if (c == D_800A13B0_main[idx]) {
                break;
            }
        }
        fileNo = 0xC0061 + idx;
        animId = &D_800B1B70_main[idx];
    } else if (flags & 1) {
        fileNo = 0xC0059 + idx;
        animId = &D_800B1B50_main[idx];
    } else {
        fileNo = 0xC001A + idx;
        animId = &D_800B1B30_main[idx];
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
#else
INCLUDE_ASM("asm/nonmatchings/gamemes", func_8003AE9C_main);
#endif

void func_8003B128_main(GAMEMES *gMes) {
    GMesSprKill(gMes);
    func_80037258_main();
}

s32 func_8003B14C_main(GAMEMES *gMes, Gfx **gfx) {
    return func_8003B4D8_main(gMes, 0xC0090, 0x253);
}

s32 func_8003B170_main(GAMEMES *gMes, char *str, s32 seNo) {
    f32 len = strlen(str);
    f32 i;
    f32 t;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, str, 1, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, 160, gMes->unk64);
        gMes->unk08 = -1000;
        gMes->unk0A = 300;
        HuAudFXPlay(seNo);
        D_800D6A58_main = 1;
        D_800D1100_main = 0;
    }
    if (gMes->unk04 > gMes->unk06 || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->unk04 > gMes->unk06 - 10) {
        gMes->stat = 2;
        t = gMes->unk04 - (gMes->unk06 - 10);
        for (i = 0.0f; i < len; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, 1.8f - t / 6.0f, 1.8f - t / 6.0f);
            func_80055458_main(gMes->strGId[0], i + 1, 255.0f - t * 25.5f);
        }
        gMes->unk08 += gMes->unk0A;
        gMes->unk64 += gMes->unk08 / 100.0f;
        HuSprPosSet(gMes->strGId[0], 0, 160, gMes->unk64);
        return TRUE;
    }
    for (i = 0.0f; i < len; i++) {
        HuSprScaleSet(gMes->strGId[0], i + 1, 1.8f, 1.8f);
    }
    return TRUE;
}

s32 func_8003B4D8_main(GAMEMES *gMes, s32 fileNo, s32 seNo) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, fileNo);
            HuAudFXPlay(seNo);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
            gMes->unk03 = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk60 += 8.0f;
            gMes->unk64 -= 6.0f;
            gMes->unk6C = gMes->unk68 -= 0.06f;
            gMes->unk03 -= 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            if (gMes->unk04 >= 40) {
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
            }
            break;
        case 3:
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 func_8003B7E8_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, 255);
            }
            gMes->unk08 = 1;
            gMes->unk0A = 0;
            gMes->unk0C = 0;
            gMes->unk0E = 9;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk68 = 1.0f - gMes->unk10;
            gMes->unk6C = 1.0f - gMes->unk10;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f - sindf(gMes->unk0A) * 50.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            gMes->unk0A += gMes->unk0E;
            gMes->unk0C += 4;
            gMes->unk10 += 0.035f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            if (gMes->unk04 >= gMes->unk06) {
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    return result;
}

s32 func_8003BB84_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0090);
            HuAudFXPlay(0x253);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, 255);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            if (gMes->unk04 >= 10) {
                gMes->unk08 = 2;
                gMes->unk14 = -4.0f;
            }
            break;
        case 2:
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -6.0f;
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk64 += gMes->unk14;
            gMes->unk14 += 1.5f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk64 >= 120.0f) {
                gMes->unk64 = 120.0f;
                gMes->unk14 = -10.0f;
                gMes->unk10 = 0.0f;
                gMes->unk08 = 4;
                gMes->unk0A = 0;
                gMes->unk0C = 0;
            }
            break;
        case 4:
            gMes->unk64 += gMes->unk14;
            gMes->unk10 += 0.7f / 12;
            gMes->unk68 = 1.0f - gMes->unk10;
            gMes->unk6C = 1.0f - gMes->unk10;
            gMes->unk0C += 7;
            gMes->unk14 += 1.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, cosdf(gMes->unk0C) * 255.0f);
            }
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
            }
            gMes->unk0A++;
            if (gMes->unk0A >= 12) {
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
                }
                gMes->unk08 = 5;
            }
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 6;
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
s32 func_8003C058_main(GAMEMES *gMes) {
    s32 len = strlen("FINISH");
    s32 result;
    s32 i;
    GMesChar *chr;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 6;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            for (i = 0; i < 32; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = chr->y = chr->velX = chr->velY = chr->angle = chr->unk2C = 0.0f;
                chr->scaleX = chr->scaleY = 1.0f;
                chr->alpha = 255;
                chr->unk34 = 0;
                chr->time = 0;
            }
            gMes->unk04 = gMes->unk0A = gMes->unk0C = gMes->unk0E = 0;
            gMes->unk06 = 0;
            gMes->unk60 = gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            gMes->unk70 = 0.0f;
            gMes->unk1C = 0;
            func_8003A37C_main(gMes, "FINISH", 1, -1, -1);
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 0.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 0);
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
    if (gMes->unk04 == 0) {
        HuAudFXPlay(0x253);
    }
    return result;
}

s32 func_8003C248_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
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
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f - scale * 180.0f * scale;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_8003C644_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->startX = chr->x = D_800A13D8_main[i].x;
                chr->startY = chr->y = D_800A13D8_main[i].y;
                chr->endX = i * 22 - (len - 1) * 11;
                chr->endY = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->endX, chr->endY);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    t = 0.0f;
                    if (gMes->unk04 > 20.0f / len * i + 30.0f) {
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

s32 func_8003CA24_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                chr->angle = chr->unk2C = 180.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
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
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f + scale * 180.0f * scale;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_8003CE20_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    f32 scale;
    f32 t;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            for (i = 0; i < len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 225);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else if (gMes->unk04 > 50) {
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

s32 func_8003D134_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                t = 0.0f;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    if (gMes->unk04 > 10.0f / len * i + 30.0f) {
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

s32 func_8003D4DC_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 t;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, chr->scaleX, chr->scaleY);
                func_80055458_main(gMes->strGId[0], i + 1, chr->alpha);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 3:
            break;
        case 4:
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            /* fallthrough */
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                t = 0.0f;
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
                    if (gMes->unk04 > 10.0f / len * i + 30.0f) {
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

s32 func_8003D890_main(GAMEMES *gMes, Gfx **gfx) {
    s32 len;
    s32 result;
    s32 i;
    GMesChar *chr;
    f32 scale;

    result = func_8003C058_main(gMes);
    len = strlen("FINISH");
    switch (gMes->unk08) {
        case 0:
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            for (i = 0; i < len; i++) {
                chr = &D_800B1BC0_main[i];
                chr->x = i * 22 - (len - 1) * 11;
                chr->y = 0.0f;
                HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[0], i + 1, 225);
                HuSprPosSet(gMes->strGId[0], i + 1, chr->x, chr->y);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk08 = 2;
            break;
        case 2:
            if (gMes->unk04 >= 30) {
                gMes->unk08 = 5;
                gMes->unk0C = 0;
                gMes->unk0A = 0;
            }
            HuSprPosSet(gMes->strGId[0], 0, 160, 120);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            gMes->stat = 2;
            if (gMes->unk04 > 60) {
                for (i = 0; i < len; i++) {
                    HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                gMes->unk0C = 0;
                gMes->unk08 = 6;
            } else {
                for (i = 0; i < len; i++) {
                    chr = &D_800B1BC0_main[i];
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
            gMes->unk60 = 160.0f - ((len + 2) * 11 + 240) * scale;
            gMes->unk64 = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, 120);
            break;
        case 6:
            break;
        case 7:
            break;
    }
    return result;
}

s32 func_8003DC88_main(GAMEMES *gMes, Gfx **gfx) {
    return func_8003D890_main(gMes, gfx);
}

void func_8003DCA4_main(GAMEMES *gMes, s32 fileNo) {
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
    func_80055024_main(grp, 0, sprId0, 0);
    func_80055458_main(grp, 0, 255);
    HuSprPriSet(grp, 0, 5);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPosSet(grp, 0, 160, gMes->unk64);
    func_800554C4_main(grp, 0, -1);
    func_80055024_main(grp, 1, sprId1, 0);
    func_80055458_main(grp, 1, 255);
    HuSprPriSet(grp, 1, 6);
    HuSprAttrReset(grp, 1, 0xFFFF);
    HuSprAttrSet(grp, 1, 0x1008);
    HuSprColorSet(grp, 1, 69, 2, 133);
    func_800554C4_main(grp, 1, 0);
}

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A76F8_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7700_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7708_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7714_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A771C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7724_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A772C_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A7734_main);

INCLUDE_RODATA("asm/nonmatchings/gamemes", D_800A773C_main);

s32 func_8003DE60_main(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    f32 nameLen = strlen(D_800A1410_main[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 total;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0E], 1, -1, -1, 1.0f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)wonStr, 1, -1, -1, 1.0f, 1.0f);
            total = nameLen + wonLen + 1.0f;
            gMes->unk0A = 160.0f - total * 17.6f / 2.0f + nameLen * 17.6f / 2.0f;
            gMes->unk60 = gMes->unk0A;
            gMes->unk68 = gMes->unk6C = 1.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < nameLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, 255);
            }
            gMes->unk0C = 160.0f - total * 17.6f / 2.0f + (nameLen * 17.6f + 17.6f) + wonLen * 17.6f / 2.0f;
            gMes->unk60 = gMes->unk0C;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, 255);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            gMes->unk64 += sindf(gMes->unk14);
            gMes->unk60 = gMes->unk0C + sindf(gMes->unk10);
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                scale = (gMes->unk06 - gMes->unk04) / 10.0f * 0.8f;
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
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_8003E4A4_main(GAMEMES *gMes, Gfx **gfx) {
    char lostStr[] = "LOST";
    f32 nameLen = strlen(D_800A1410_main[gMes->unk08]);
    f32 lostLen = strlen(lostStr);
    f32 x;
    s16 i;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, D_800A1410_main[gMes->unk08], 1, -1, -1);
        func_8003A37C_main(gMes, lostStr, 1, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, (320.0f - (nameLen + lostLen + 1.0f) * 24.0f) / 2.0f + nameLen * 24.0f / 2.0f, gMes->unk64 + 40.0f);
        HuSprPosSet(gMes->strGId[1], 0, 320.0f - (320.0f - (nameLen + lostLen + 1.0f) * 24.0f) / 2.0f - lostLen * 24.0f / 2.0f, gMes->unk64 + 40.0f);
        for (i = 0; i < nameLen; i++) {
            HuSprAttrSet(gMes->strGId[0], i + 1, 0x8000);
        }
        for (i = 0; i < lostLen; i++) {
            HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
        }
        gMes->unk0A = 0;
    }
    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->unk04 > 80) {
        gMes->stat = 2;
    }
    if (gMes->unk04 > 50) {
        if (++gMes->unk0A & 0x40) {
            x = (u16)gMes->unk0A % 32;
            x = cosdf(x * 11.612904f) * 55.0f + 200.0f;
            for (i = 0; i < nameLen; i++) {
                func_80055458_main(gMes->strGId[0], i + 1, x);
            }
            for (i = 0; i < lostLen; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, x);
            }
        }
        return TRUE;
    }
    x = gMes->unk04;
    if (x <= 30.0f) {
        for (i = 0; i < nameLen; i++) {
            HuSprAttrReset(gMes->strGId[0], i + 1, 0x8000);
            func_80055458_main(gMes->strGId[0], i + 1, x * 8.5f);
        }
    }
    x = gMes->unk04 - 20;
    if (x <= 30.0f && x > 0.0f) {
        for (i = 0; i < lostLen; i++) {
            HuSprAttrReset(gMes->strGId[1], i + 1, 0x8000);
            func_80055458_main(gMes->strGId[1], i + 1, x * 8.5f);
        }
    }
    return TRUE;
}

s32 func_8003EBC8_main(GAMEMES *gMes, Gfx **gfx) {
    char *str;
    f32 scale;
    f32 i;

    if (gMes->unk04 == 0) {
        str = HuMemMemoryAllocPerm(256);
        func_80045208_main((u8 *)str, (void *)gMes->unk1C);
        func_8003A37C_main(gMes, str, gMes->unk02, -1, -1);
        gMes->unk08 = strlen(str);
        HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
        HuMemMemoryFreePerm(str);
    }
    if (gMes->unk04 > gMes->unk06 || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    if (gMes->unk04 < 14) {
        scale = sindf(gMes->unk04 * 10.0f) + (1.0f - sindf(130.0f));
        for (i = 0.0f; i < gMes->unk08; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, scale * gMes->unk6C);
        }
    }
    if (gMes->unk04 > gMes->unk06 - 10) {
        gMes->stat = 2;
        scale = cosdf((gMes->unk04 - (gMes->unk06 - 10)) * 9.0f);
        for (i = 0.0f; i < gMes->unk08; i++) {
            HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, scale * gMes->unk6C);
        }
    }
    return TRUE;
}

s32 func_8003EE98_main(GAMEMES *gMes, Gfx **gfx) {
    char *str;
    f32 i;

    if (gMes->unk04 == 0) {
        str = HuMemMemoryAllocPerm(256);
        func_80045208_main((u8 *)str, (void *)gMes->unk1C);
        func_8003A37C_main(gMes, str, gMes->unk02, -1, -1);
        gMes->unk08 = strlen(str);
        HuMemMemoryFreePerm(str);
    }
    if (gMes->unk04 > gMes->unk06 || gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        GMesSprKill(gMes);
        return FALSE;
    }
    HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
    HuSprZRotSet(gMes->strGId[0], 0, gMes->unk70);
    for (i = 0.0f; i < gMes->unk08; i++) {
        HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk6C);
        func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
    }
    return TRUE;
}

s32 GMesTimerExec(GAMEMES *gMes, Gfx **arg1) {
    f32 temp_f22;
    u8 temp_s2;
    u8 temp_s0;

    if (gMes->unk04 == 0) {
        func_8003A37C_main(gMes, "99", 0, -1, -1);
        HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
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

s32 func_8003F604_main(GAMEMES *gMes, Gfx **gfx) {
    char *newStr = "NEW";
    char *recordStr = "RECORD";
    s32 newLen;
    s32 recordLen;
    s32 result;
    s32 i;
    f32 x;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    newLen = strlen(newStr);
    recordLen = strlen(recordStr);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, newStr, 1, -1, -1);
            func_8003A37C_main(gMes, recordStr, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            x = 160.0f - ((newLen + recordLen + 1) * 11 * gMes->unk68 - newLen * 11 * gMes->unk6C);
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60 - 160.0f + x, gMes->unk64);
            gMes->unk03 = 0;
            for (i = 0; i < newLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            x = (newLen + recordLen + 1) * 11 * gMes->unk68 - recordLen * 11 * gMes->unk6C + 160.0f;
            gMes->unk70 = 0.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60 - 160.0f + x, gMes->unk64);
            HuSprZRotSet(gMes->strGId[1], 0, gMes->unk70);
            for (i = 0; i < recordLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 90.0f;
            break;
        case 1:
            gMes->unk10 += 21.0f;
            gMes->unk68 += 0.016666668f;
            gMes->unk6C = 1.0f - sindf(gMes->unk10) * 0.5f;
            x = 160.0f - ((newLen + recordLen + 1) * 11 * gMes->unk68 - newLen * 11 * gMes->unk68);
            gMes->unk70 += 12.0f;
            gMes->unk03 += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60 - 160.0f + x, gMes->unk64);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < newLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            x = (newLen + recordLen + 1) * 11 * gMes->unk68 - recordLen * 11 * gMes->unk68 + 160.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60 - 160.0f + x, gMes->unk64);
            for (i = 0; i < recordLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 30) {
                gMes->stat = 2;
                HuSprZRotSet(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < newLen; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0; i < recordLen; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, 255);
                }
                gMes->unk0A = 30;
                gMes->unk08 = 2;
            }
            break;
        case 2:
            if (--gMes->unk0A == -1) {
                gMes->unk0A = 255;
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk0A -= 16;
            if (gMes->unk0A <= 0) {
                gMes->unk0A = 0;
                gMes->unk08 = 4;
            }
            for (i = 0; i < newLen; i++) {
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk0A);
            }
            for (i = 0; i < recordLen; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk0A);
            }
            if (gMes->unk04 > 60) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x252);
    }
    if (gMes->unk04 >= 56) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_8003FD34_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 3;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0092);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk03 = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.2f + 1.0f;
            gMes->unk10 += 15.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                gMes->stat = 2;
                gMes->unk03 -= 25;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, gMes->unk03);
                }
            }
            if (gMes->unk04 > gMes->unk06) {
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
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

s32 func_8003FFD0_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 3;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0094);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = 1.0f;
            gMes->unk6C = 1.0f;
            gMes->unk03 = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            if (gMes->unk04 >= 10) {
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.3f + 1.0f;
            gMes->unk10 += 20.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 >= 40) {
                gMes->unk03 -= 51;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, gMes->unk03);
                }
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->stat = 2;
                gMes->unk08 = 3;
                for (i = 0; i < 2; i++) {
                    func_80055458_main(gMes->strGId[0], i, 0);
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

s32 func_80040290_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;
    f32 t;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0098);
            HuSprColorSet(gMes->strGId[0], 1, 69, 2, 133);
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, 120);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 0.0f, 2.0f);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk68 = sindf(gMes->unk10);
            gMes->unk6C = 2.0f - (1.0f - cosdf(gMes->unk10));
            gMes->unk10 += 9.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 < 10) {
                break;
            }
            gMes->unk08 = 2;
            gMes->unk10 = 90.0f;
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
            }
            /* fallthrough */
        case 2:
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            gMes->unk68 = 1.5f - (sindf(gMes->unk10) < 0.0f ? -sindf(gMes->unk10) : sindf(gMes->unk10)) * 0.5f;
            gMes->unk6C = (sindf(gMes->unk10) < 0.0f ? -sindf(gMes->unk10) : sindf(gMes->unk10)) * 0.7f + 0.3f;
            gMes->unk10 += 12.0f;
            if (gMes->unk04 >= 25) {
                for (i = 0; i < 2; i++) {
                }
                gMes->unk08 = 3;
                gMes->unk10 = 0.0f;
            }
            break;
        case 3:
            gMes->unk03 = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                t = (gMes->unk06 - gMes->unk04) / 10.0f;
            } else {
                t = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                func_80055458_main(gMes->strGId[0], i, gMes->unk03 * t);
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 10) {
        HuAudFXPlay(0x24F);
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_800407B8_main(GAMEMES *gMes, Gfx **gfx) {
    char *readyStr = "READY";
    char *goStr = "GO\xC4";
    s32 readyLen;
    s32 goLen;
    s32 result;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 6;
    }
    result = TRUE;
    readyLen = strlen(readyStr);
    goLen = strlen(goStr);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, readyStr, 1, -1, -1);
            func_8003A37C_main(gMes, goStr, 1, -1, -1);
            gMes->unk68 = 0.5f;
            gMes->unk03 = 0;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            for (i = 0; i < goLen; i++) {
                HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
            }
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            gMes->unk08 = 1;
            gMes->unk0C = 0;
            gMes->unk0A = 0;
            break;
        case 1:
            gMes->unk68 += 0.1f;
            gMes->unk03 += 25;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 10) {
                for (i = 0; i < readyLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.5f, 1.5f);
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            if (gMes->unk04 >= 35) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            gMes->unk68 += 0.05f;
            gMes->unk03 -= 51;
            for (i = 0; i < readyLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 40) {
                for (i = 0; i < readyLen; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 0);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            gMes->unk68 = gMes->unk6C = sindf(gMes->unk0A * 15) * 3.0f;
            for (i = 0; i < goLen; i++) {
                HuSprAttrReset(gMes->strGId[1], i + 1, 0x8000);
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68, gMes->unk6C);
            }
            gMes->unk0A++;
            if (gMes->unk04 >= 50) {
                func_800452BC_main(func_80036610_main());
                gMes->unk08 = 5;
                gMes->unk03 = 255;
            }
            break;
        case 5:
            gMes->stat = 2;
            gMes->unk03 -= 51;
            for (i = 0; i < goLen; i++) {
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            gMes->unk0C++;
            if (gMes->unk04 >= 55) {
                for (i = 0; i < goLen; i++) {
                    HuSprAttrSet(gMes->strGId[1], i + 1, 0x8000);
                }
                gMes->unk08 = 6;
            }
            break;
        case 6:
            GMesSprKill(gMes);
            D_800D6A58_main = 0;
            D_800D1100_main = 1;
            result = FALSE;
            break;
    }
    return result;
}

s32 func_80040CF4_main(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    f32 name1Len = strlen(D_800A1410_main[gMes->unk0C]);
    f32 name2Len = strlen(D_800A1410_main[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            func_8003A37C_main(gMes, wonStr, 1, -1, -1);
            gMes->unk60 = 80.0f;
            gMes->unk64 = 0.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, 255);
            }
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, 255);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprAttrSet(gMes->strGId[2], i + 1, 0x8000);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 1.5f;
            break;
        case 1:
            gMes->unk10 += gMes->unk14;
            gMes->unk64 += gMes->unk10;
            gMes->unk60 = 80.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 >= 15) {
                gMes->unk08 = 2;
                gMes->unk10 = -12.0f;
                gMes->unk14 = 1.0f;
            }
            break;
        case 2:
            gMes->unk10 += gMes->unk14;
            gMes->unk64 += gMes->unk10;
            gMes->unk60 = 80.0f;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            gMes->unk60 = 240.0f;
            if (gMes->unk0C == 5) {
                gMes->unk60 = 256.0f;
            }
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            if (gMes->unk04 >= 25) {
                gMes->unk08 = 3;
                gMes->unk0A = gMes->unk64;
            }
            break;
        case 3:
            gMes->unk60 = 170.0f;
            gMes->unk64 = 145.0f;
            gMes->unk68 = gMes->unk6C = 1.0f;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1, 255);
                HuSprAttrReset(gMes->strGId[2], i + 1, 0x8000);
            }
            gMes->unk08 = 4;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 4:
            gMes->unk60 = sindf(gMes->unk10) + 160.0f;
            gMes->unk64 = sindf(gMes->unk14) + 145.0f;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                scale = (gMes->unk06 - gMes->unk04) / 10.0f;
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
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_80041700_main(GAMEMES *gMes, Gfx **gfx) {
    s32 result;
    s32 i;
    f32 t;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 3;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003DCA4_main(gMes, 0xC0096);
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk60 = 160.0f;
            gMes->unk64 = 120.0f;
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk70 = 0.0f;
            gMes->unk03 = 255;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            HuSprZRotSet(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i, gMes->unk03);
            }
            gMes->unk08 = 1;
            break;
        case 1:
            gMes->unk6C = gMes->unk68 += 0.05f;
            gMes->unk70 += 36.0f;
            HuSprZRotSet(gMes->strGId[0], 0, gMes->unk70);
            for (i = 0; i < 2; i++) {
                HuSprScaleSet(gMes->strGId[0], i, gMes->unk68, gMes->unk6C);
            }
            if (gMes->unk04 >= 10) {
                HuSprZRotSet(gMes->strGId[0], 0, 0.0f);
                for (i = 0; i < 2; i++) {
                    HuSprScaleSet(gMes->strGId[0], i, 1.0f, 1.0f);
                }
                gMes->unk08 = 2;
                gMes->unk10 = 0.0f;
            }
            break;
        case 2:
            gMes->unk03 = cosdf(gMes->unk10) * 55.0f + 200.0f;
            gMes->unk10 += 20.0f;
            if (gMes->unk04 > gMes->unk06 - 10) {
                t = (gMes->unk06 - gMes->unk04) / 10.0f;
            } else {
                t = 1.0f;
            }
            for (i = 0; i < 2; i++) {
                func_80055458_main(gMes->strGId[0], i, gMes->unk03 * t);
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 3;
            }
            break;
        case 3:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 30) {
        HuAudFXPlay(0x255);
    }
    if (gMes->unk04 == gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_80041B68_main(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    s32 startPos[4][2] = { { 95, 80 }, { 210, 80 }, { 155, 140 }, { 170, 145 } };
    s32 endPos[4][2] = { { 240, 117 }, { 80, 117 }, { 160, 80 }, { 160, 145 } };
    s32 dx;
    s32 dy;
    f32 name1Len = strlen(D_800A1410_main[gMes->unk0A]);
    f32 name2Len = strlen(D_800A1410_main[gMes->unk0C]);
    f32 name3Len = strlen(D_800A1410_main[gMes->unk0E]);
    f32 wonLen = strlen(wonStr);
    s32 result;
    f32 scale;
    f32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    switch (gMes->unk08) {
        case 0:
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0A], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            func_8003A37C_main(gMes, wonStr, 1, -1, -1);
            gMes->unk60 = startPos[0][0];
            gMes->unk64 = startPos[0][1] + gMes->unk64;
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk03 = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = startPos[1][0];
            gMes->unk64 = startPos[1][1];
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            gMes->unk60 = startPos[2][0];
            gMes->unk64 = startPos[2][1];
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1, gMes->unk03);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprAttrSet(gMes->strGId[3], i + 1, 0x8000);
            }
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            dx = endPos[0][0] - startPos[0][0];
            dy = endPos[0][1] - startPos[0][1];
            gMes->unk60 = startPos[0][0] + gMes->unk10 / 30.0f * dx;
            gMes->unk64 = startPos[0][1] + gMes->unk10 / 30.0f * dy;
            gMes->unk68 = gMes->unk6C = gMes->unk10 / 30.0f * 0.5f + 0.5f;
            gMes->unk03 += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            dx = endPos[1][0] - startPos[1][0];
            dy = endPos[1][1] - startPos[1][1];
            gMes->unk60 = startPos[1][0] + gMes->unk10 / 30.0f * dx;
            gMes->unk64 = startPos[1][1] + gMes->unk10 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            dx = endPos[2][0] - startPos[2][0];
            dy = endPos[2][1] - startPos[2][1];
            gMes->unk60 = startPos[2][0] + gMes->unk10 / 30.0f * dx;
            gMes->unk64 = startPos[2][1] + gMes->unk10 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1, gMes->unk03);
            }
            gMes->unk10 += 1.0f;
            if (gMes->unk04 >= 30) {
                for (i = 0.0f; i < name1Len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    func_80055458_main(gMes->strGId[2], i + 1, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk60 = startPos[3][0];
            gMes->unk64 = startPos[3][1];
            gMes->unk68 = gMes->unk6C = 1.0f;
            HuSprPosSet(gMes->strGId[3], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->unk68, gMes->unk6C);
                func_80055458_main(gMes->strGId[3], i + 1, 255);
                HuSprAttrReset(gMes->strGId[3], i + 1, 0x8000);
            }
            gMes->unk08 = 3;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 0.0f;
            break;
        case 3:
            gMes->unk60 = endPos[3][0] + sindf(gMes->unk10);
            gMes->unk64 = endPos[3][1] + sindf(gMes->unk14);
            HuSprPosSet(gMes->strGId[3], 0, gMes->unk60, gMes->unk64);
            gMes->unk10 += 90.0f;
            gMes->unk14 += 45.0f;
            if (gMes->unk10 >= 360.0f) {
                gMes->unk10 = 0.0f;
            }
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                scale = (gMes->unk06 - gMes->unk04) / 10.0f;
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
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            break;
        case 4:
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_80042AC8_main(GAMEMES *gMes, Gfx **gfx) {
    char wonStr[] = "WON\xC4 ";
    s32 dx;
    s32 dy;
    f32 name1Len = strlen(D_800A1410_main[gMes->unk08]);
    f32 name2Len = strlen(D_800A1410_main[gMes->unk0A]);
    f32 name3Len = strlen(D_800A1410_main[gMes->unk0C]);
    f32 name4Len = strlen(D_800A1410_main[gMes->unk0E]);
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
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk08], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0A], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0C], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)D_800A1410_main[gMes->unk0E], 1, -1, -1, 0.8f, 1.0f);
            func_8003A3C4_main(gMes, (u8 *)wonStr, 1, -1, -1, 0.8f, 1.0f);
            gMes->unk60 = D_800A1434_main[0][0];
            gMes->unk64 = D_800A1434_main[0][1];
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk03 = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = D_800A1434_main[1][0];
            gMes->unk64 = D_800A1434_main[1][1];
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            gMes->unk60 = D_800A1434_main[2][0];
            gMes->unk64 = D_800A1434_main[2][1];
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1, gMes->unk03);
            }
            gMes->unk60 = D_800A1434_main[3][0];
            gMes->unk64 = D_800A1434_main[3][1];
            HuSprPosSet(gMes->strGId[3], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name4Len; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[3], i + 1, gMes->unk03);
            }
            for (i = 0.0f; i < wonLen; i++) {
                HuSprAttrSet(gMes->strGId[4], i + 1, 0x8000);
            }
            gMes->unk10 = 1.0f;
            gMes->unk14 = 0.0f;
            break;
        case 1:
            dx = D_800A145C_main[0][0] - D_800A1434_main[0][0];
            dy = D_800A145C_main[0][1] - D_800A1434_main[0][1];
            gMes->unk60 = D_800A1434_main[0][0] + gMes->unk14 / 30.0f * dx;
            gMes->unk64 = D_800A1434_main[0][1] + gMes->unk14 / 30.0f * dy;
            gMes->unk68 = gMes->unk6C = gMes->unk14 / 30.0f * 0.5f + 0.5f;
            gMes->unk03 += 8;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name1Len; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            dx = D_800A145C_main[1][0] - D_800A1434_main[1][0];
            dy = D_800A145C_main[1][1] - D_800A1434_main[1][1];
            gMes->unk60 = D_800A1434_main[1][0] + gMes->unk14 / 30.0f * dx;
            gMes->unk64 = D_800A1434_main[1][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name2Len; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            dx = D_800A145C_main[2][0] - D_800A1434_main[2][0];
            dy = D_800A145C_main[2][1] - D_800A1434_main[2][1];
            gMes->unk60 = D_800A1434_main[2][0] + gMes->unk14 / 30.0f * dx;
            gMes->unk64 = D_800A1434_main[2][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name3Len; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[2], i + 1, gMes->unk03);
            }
            dx = D_800A145C_main[3][0] - D_800A1434_main[3][0];
            dy = D_800A145C_main[3][1] - D_800A1434_main[3][1];
            gMes->unk60 = D_800A1434_main[3][0] + gMes->unk14 / 30.0f * dx;
            gMes->unk64 = D_800A1434_main[3][1] + gMes->unk14 / 30.0f * dy;
            HuSprPosSet(gMes->strGId[3], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < name4Len; i++) {
                HuSprScaleSet(gMes->strGId[3], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[3], i + 1, gMes->unk03);
            }
            gMes->unk14 += 1.0f;
            if (gMes->unk04 >= 30) {
                for (i = 0.0f; i < name1Len; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0.0f; i < name2Len; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0.0f; i < name3Len; i++) {
                    func_80055458_main(gMes->strGId[2], i + 1, 255);
                }
                for (i = 0.0f; i < name4Len; i++) {
                    func_80055458_main(gMes->strGId[3], i + 1, 255);
                }
                gMes->unk10 = 2.0f;
            }
            break;
        case 2:
            gMes->unk60 = D_800A1434_main[4][0];
            gMes->unk64 = D_800A1434_main[4][1];
            gMes->unk68 = gMes->unk6C = 1.0f;
            HuSprPosSet(gMes->strGId[4], 0, gMes->unk60, gMes->unk64);
            for (i = 0.0f; i < wonLen; i++) {
                HuSprScaleSet(gMes->strGId[4], i + 1, gMes->unk68 * 0.8f, gMes->unk6C);
                func_80055458_main(gMes->strGId[4], i + 1, 255);
                HuSprAttrReset(gMes->strGId[4], i + 1, 0x8000);
            }
            gMes->unk10 = 3.0f;
            gMes->unk14 = 0.0f;
            break;
        case 3:
            dx = D_800A1484_main[0][0] - D_800A145C_main[0][0];
            dy = D_800A1484_main[0][1] - D_800A145C_main[0][1];
            gMes->unk60 = D_800A145C_main[0][0] + gMes->unk14 / 10.0f * dx;
            gMes->unk64 = D_800A145C_main[0][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            dx = D_800A1484_main[1][0] - D_800A145C_main[1][0];
            dy = D_800A1484_main[1][1] - D_800A145C_main[1][1];
            gMes->unk60 = D_800A145C_main[1][0] + gMes->unk14 / 10.0f * dx;
            gMes->unk64 = D_800A145C_main[1][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            dx = D_800A1484_main[2][0] - D_800A145C_main[2][0];
            dy = D_800A1484_main[2][1] - D_800A145C_main[2][1];
            gMes->unk60 = D_800A145C_main[2][0] + gMes->unk14 / 10.0f * dx;
            gMes->unk64 = D_800A145C_main[2][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk60, gMes->unk64);
            dx = D_800A1484_main[3][0] - D_800A145C_main[3][0];
            dy = D_800A1484_main[3][1] - D_800A145C_main[3][1];
            gMes->unk60 = D_800A145C_main[3][0] + gMes->unk14 / 10.0f * dx;
            gMes->unk64 = D_800A145C_main[3][1] + gMes->unk14 / 10.0f * dy;
            HuSprPosSet(gMes->strGId[3], 0, gMes->unk60, gMes->unk64);
            gMes->unk14 += 1.0f;
            if (gMes->unk04 >= 40) {
                gMes->unk10 = 4.0f;
                gMes->unk14 = 0.0f;
                gMes->unk18 = 0.0f;
            }
            break;
        case 4:
            gMes->unk60 = D_800A145C_main[4][0] + sindf(gMes->unk14);
            gMes->unk64 = D_800A145C_main[4][1] + sindf(gMes->unk18);
            HuSprPosSet(gMes->strGId[4], 0, gMes->unk60, gMes->unk64);
            gMes->unk14 += 90.0f;
            gMes->unk18 += 45.0f;
            if (gMes->unk14 >= 360.0f) {
                gMes->unk14 = 0.0f;
            }
            if (gMes->unk18 >= 360.0f) {
                gMes->unk18 = 0.0f;
            }
            if (gMes->unk04 > gMes->unk06 - 10) {
                scale = (gMes->unk06 - gMes->unk04) / 10.0f;
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
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk10 = 5.0f;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_800440D4_main(GAMEMES *gMes, Gfx **gfx) {
    char *gotStr = "GOT";
    char *itemStr = "ITEM\xC4";
    s32 result;
    s32 gotLen;
    s32 itemLen;
    s32 i;
    f32 alpha;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 4;
    }
    result = TRUE;
    gotLen = strlen(gotStr);
    itemLen = strlen(itemStr);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, gotStr, 1, -1, -1);
            func_8003A37C_main(gMes, itemStr, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk60 = cosdf(0.0f) * 55.0f + 149.0f;
            gMes->unk64 = sindf(0.0f) * 55.0f + 120.0f;
            gMes->unk03 = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = cosdf(180.0f) * 55.0f + 149.0f;
            gMes->unk64 = sindf(180.0f) * 55.0f + 120.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, 0);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            gMes->unk14 = 180.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->unk14 += 12.0f;
            gMes->unk6C = gMes->unk68 += 0.033333335f;
            gMes->unk60 = cosdf(gMes->unk10) * 55.0f + 149.0f;
            gMes->unk64 = sindf(gMes->unk10) * 55.0f + 120.0f;
            gMes->unk03 += 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk60 = cosdf(gMes->unk14) * 55.0f + 149.0f;
            gMes->unk64 = sindf(gMes->unk14) * 55.0f + 120.0f;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 15) {
                gMes->unk08 = 2;
                gMes->unk10 = 630.0f;
            }
            break;
        case 2:
            gMes->unk6C = gMes->unk68 = sindf(gMes->unk10) * 0.1f + 1.1f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
            }
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk68, gMes->unk68);
            }
            if (gMes->unk04 >= 35) {
                for (i = 0; i < gotLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                }
                for (i = 0; i < itemLen; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                }
                gMes->unk08 = 3;
            }
            break;
        case 3:
            if (gMes->unk04 > gMes->unk06 - 10) {
                alpha = (gMes->unk06 - gMes->unk04) / 10.0f * 255.0f;
                for (i = 0; i < gotLen; i++) {
                    func_80055458_main(gMes->strGId[0], i + 1, alpha);
                }
                for (i = 0; i < itemLen; i++) {
                    func_80055458_main(gMes->strGId[1], i + 1, alpha);
                }
            }
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 4;
            }
            break;
        case 4:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 == 1) {
        HuAudFXPlay(0x260);
    }
    if (gMes->unk04 > gMes->unk06 - 5) {
        gMes->stat = 2;
    }
    return result;
}

s32 func_800448C0_main(GAMEMES *gMes, Gfx **gfx) {
    char *gotStr = "GOT";
    char *itemStr = "ITEM";
    char *exclStr = "\xC3";
    s32 result;
    s32 gotLen;
    s32 itemLen;
    s32 exclLen;
    s32 i;

    if (gMesCloseF || gMes->stat == GMES_STAT_KILL) {
        gMes->unk08 = 5;
    }
    result = TRUE;
    gotLen = strlen(gotStr);
    itemLen = strlen(itemStr);
    exclLen = strlen(exclStr);
    switch (gMes->unk08) {
        case 0:
            func_8003A37C_main(gMes, gotStr, 1, -1, -1);
            func_8003A37C_main(gMes, itemStr, 1, -1, -1);
            func_8003A37C_main(gMes, exclStr, 1, -1, -1);
            gMes->unk68 = gMes->unk6C = 0.5f;
            gMes->unk60 = 99.0f;
            gMes->unk64 = 45.0f;
            gMes->unk03 = 0;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A = 189;
            gMes->unk0C = 195;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < exclLen; i++) {
                HuSprAttrSet(gMes->strGId[2], 1, 0x8000);
                HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                func_80055458_main(gMes->strGId[2], i + 1, 255);
            }
            D_800D6A58_main = 1;
            D_800D1100_main = 0;
            gMes->unk08 = 1;
            gMes->unk10 = 0.0f;
            break;
        case 1:
            gMes->unk10 += 12.0f;
            gMes->unk6C = gMes->unk68 += 0.033333335f;
            gMes->unk60 = sindf(gMes->unk10) * 20.0f + 94.0f;
            gMes->unk64 += 5.0f;
            gMes->unk03 += 17;
            HuSprPosSet(gMes->strGId[0], 0, gMes->unk60, gMes->unk64);
            for (i = 0; i < gotLen; i++) {
                HuSprScaleSet(gMes->strGId[0], i + 1, gMes->unk68, gMes->unk68);
                func_80055458_main(gMes->strGId[0], i + 1, gMes->unk03);
            }
            gMes->unk0A = sindf(gMes->unk10) * 20.0f + 194.0f;
            gMes->unk0C -= 5;
            HuSprPosSet(gMes->strGId[1], 0, gMes->unk0A, gMes->unk0C);
            for (i = 0; i < itemLen; i++) {
                HuSprScaleSet(gMes->strGId[1], i + 1, gMes->unk6C, gMes->unk6C);
                func_80055458_main(gMes->strGId[1], i + 1, gMes->unk03);
            }
            if (gMes->unk04 >= 15) {
                gMes->unk0A = 330;
                HuSprPosSet(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
                for (i = 0; i < gotLen; i++) {
                    HuSprScaleSet(gMes->strGId[0], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[0], i + 1, 255);
                }
                for (i = 0; i < itemLen; i++) {
                    HuSprScaleSet(gMes->strGId[1], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[1], i + 1, 255);
                }
                for (i = 0; i < exclLen; i++) {
                    HuSprAttrReset(gMes->strGId[2], i + 1, 0x8000);
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                    func_80055458_main(gMes->strGId[2], i + 1, 255);
                }
                gMes->unk08 = 2;
            }
            break;
        case 2:
            gMes->unk0A -= 16;
            HuSprPosSet(gMes->strGId[2], 0, gMes->unk0A, gMes->unk0C);
            if (gMes->unk04 >= 20) {
                gMes->unk08 = 3;
                gMes->unk10 = 630.0f;
            }
            break;
        case 3:
            gMes->unk68 = sindf(gMes->unk10) * 0.5f + 1.5f;
            gMes->unk10 += 36.0f;
            for (i = 0; i < exclLen; i++) {
                HuSprScaleSet(gMes->strGId[2], i + 1, gMes->unk68, gMes->unk68);
            }
            if (gMes->unk04 >= 40) {
                for (i = 0; i < exclLen; i++) {
                    HuSprScaleSet(gMes->strGId[2], i + 1, 1.0f, 1.0f);
                }
                gMes->unk08 = 4;
            }
            break;
        case 4:
            if (gMes->unk04 >= gMes->unk06) {
                gMes->unk08 = 5;
            }
            break;
        case 5:
            GMesSprKill(gMes);
            result = FALSE;
            break;
    }
    if (gMes->unk04 >= 31) {
        gMes->stat = 2;
    }
    return result;
}

void func_80045010_main(const s16 *str, s32 flags) {
    u8 *buf = HuMemMemoryAllocPerm(0x200);
    u8 *c = buf;

    func_80045208_main(buf, (u8 *)str);
    while (*c != 0) {
        func_8003A81C_main(c, flags);
        c += (c[1] == 0x80 || c[1] == 0x81);
        c++;
    }
    D_800B1A52_main = 1;
    HuMemMemoryFreePerm(buf);
}

u16 func_800450B8_main(u16 code) {
    u16 tmp;
    s32 i;

    for (i = 0; D_800A14AC_main[i] != 0; i += 2) {
        tmp = (D_800A14AC_main[i] << 8) | D_800A14AC_main[i + 1];
        if (tmp == code) {
            tmp = (D_800A1500_main[i] << 8) | D_800A1500_main[i + 1];
            return (func_8005FA90_main((u8 *)&tmp) << 8) | 0x80;
        }
    }
    for (i = 0; D_800A1554_main[i] != 0; i += 2) {
        tmp = (D_800A1554_main[i] << 8) | D_800A1554_main[i + 1];
        if (tmp == code) {
            tmp = (D_800A156C_main[i] << 8) | D_800A156C_main[i + 1];
            return (func_8005FA90_main((u8 *)&tmp) << 8) | 0x81;
        }
    }
    return func_8005FA90_main((u8 *)&code) << 8;
}

s32 func_80045208_main(u8 *dst, u8 *src) {
    u16 code;
    s32 len = 0;
    u8 *p = src;

    while (*p != 0) {
        code = func_800450B8_main((p[0] << 8) | p[1]);
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

s32 func_800452A0_main(void *arg0, void *arg1) {
    return func_80045208_main(arg0, arg1);
}

void func_800452BC_main(s32 mgIndex) {
}

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
