#include "game/pause.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework_data.h"
#include "game/hu3d.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/mallocblock.h"
#include "include_asm.h"
#include "macros.h"
#include "game/input.h"
#include "common_structs.h"
#include "variables.h"
#include "game/mgdata.h"
#include "game/hmfdraw.h"

// hmfdraw


// LOCAL

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
} D_800B2350_main_Struct; // Size 8


static u8 D_800A1590_main[] = { 0x2F, 0x30, 0x35, 0x6F, 0x36, 0x38, 0x4E, 0x31, 0x9A };
static s16 D_800A159C_main[] = { 655, 655, 628, 628, 619, 619, 655, 655, 655 };
static u8 D_800A15B0_main[] = { 0x2D, 0x11, 0x27, 0x18, 0, 0, 0, 0, 0 };
static u8 D_800A15BC_main[] = { 0x2D, 0x21, 0x2D, 0x15, 0, 0, 0, 0, 0 };
static u8 D_800A15C8_main[] = { 0x00, 0x1E, 0x33, 0x12, 0, 0, 0, 0, 0 };
static u8 D_800A15D4_main[] = { 0x2D, 0x16, 0x2D, 0x0F, 0, 0, 0, 0, 0 };
static u8 D_800A15E0_main[] = { 0x1A, 0x17, 0x30, 0x09, 0, 0, 0, 0, 0 };
static u8 D_800A15EC_main[] = { 0x1E, 0x18, 0x2A, 0x09, 0, 0, 0, 0, 0 };
static u8 D_800A15F8_main[] = { 0x24, 0x1E, 0x33, 0x0C, 0, 0, 0, 0, 0 };
static u8 D_800A1604_main[] = { 0x1E, 0x18, 0x33, 0x12, 0, 0, 0, 0, 0 };
static u8 *D_800A1610_main[] = {
    D_800A15B0_main, D_800A15BC_main, D_800A15C8_main, D_800A15D4_main,
    D_800A15E0_main, D_800A15EC_main, D_800A15F8_main, D_800A1604_main,
};
static u8 D_800A1630_main[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
static s16 D_800B2340_main[3];
static u8 D_800B2346_main[10]; // unreferenced
static D_800B2350_main_Struct D_800B2350_main[8];
static omObjData *D_800B2390_main;
extern u16 D_800CE214_main;
extern Process *pauseProc;
extern s16 D_800D0A38_main;
extern s8 D_800D2132_main;
extern s16 D_800D6ADA_main;

void func_80045350_main(void) {
    s32 var_v1;

    if (D_800A6D44_main[GwSystem.minigame_index - 1].minigameType == 6) {
        return;
    }
    for (var_v1 = 0; var_v1 < 4; var_v1++) {
        GW_PLAYER *temp_v0 = &GwPlayer[var_v1];

        temp_v0->gameCoin = 0;
        temp_v0->bonusCoin = 0;
    }
}

void GameMesPauseCreate(void) {
    pauseProc = omAddPrcObj(ExecPause, 0x3FFF, 0x800, 0);
    omPrcSetStatBit(pauseProc, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void ExecPause(void) {
    void *temp_v0_3;
    s16 sp18[4];
    s16 sp20[2];
    s16 var_s7 = 0;
    s16 var_s6;
    s16 var_s0_3;
    s16 var_s1;
    s16 var_s4;
    s16 var_s2;

    HuPrcSleep(2);
    D_800CB99C_main = 1;
    var_s6 = GwSystem.minigame_index - 1;
    sp18[0] = D_800A6D44_main[var_s6].unk_06;
    sp18[1] = D_800A6D44_main[var_s6].unk_08;
    sp18[2] = D_800A6D44_main[var_s6].unk_0A;
    sp18[3] = D_800A6D44_main[var_s6].unk_0C;
    for (var_s4 = 0; var_s4 < 4; var_s4++) {
        if (sp18[var_s4] == -1) {
            break;
        }
    }
    var_s1 = (var_s4 >= 2) ? 0x41 : 0x6E;
    if (D_800A6D44_main[var_s6].minigameType == 6) {
        var_s1 = 0x8C;
        var_s4 = 0;
    }
    temp_v0_3 = DataRead(0xC008F);
    D_800D0A38_main = HuSprAnimRead(temp_v0_3);
    D_800D6ADA_main = HuSprGrpCreate(1, 5);
    DataClose(temp_v0_3);
    HuSprGrpMemberSet(D_800D6ADA_main, 0, D_800D0A38_main, 0);
    HuSprAttrSet(D_800D6ADA_main, 0, 0x01001000);
    HuSprPosSet(D_800D6ADA_main, 0, 0xA0, var_s1 - 20);
    HuSprPriSet(D_800D6ADA_main, 0, 1);
    for (var_s2 = 0; var_s2 < ARRAY_COUNT(D_800B2340_main) - 1; var_s2++) {
        D_800B2340_main[var_s2] = func_80045B24_main(0x3C, var_s1 + var_s2 * 0x41);
    }
    for (var_s2 = 0; var_s2 < ARRAY_COUNT(D_800B2340_main) - 1; var_s2++) {
        func_80045964_main(D_800B2340_main[var_s2], var_s6);
        if (var_s4 <= var_s2 + var_s7 * 2) {
            HuWinDispOff(D_800B2340_main[var_s2]);
        } else {
            HuWinDispOn(D_800B2340_main[var_s2]);
            HuWinMesSet(D_800B2340_main[var_s2], sp18[var_s2 + var_s7 * 2], -1, -1);
        }
    }
    if (var_s4 < 3) {
        HuWinMesMaxSizeGet(1, sp20, 0x3919);
        D_800B2340_main[2] = var_s0_3 = HuWinCreate((0x140 - sp20[0]) / 2, 0xE0 - sp20[1], sp20[0], sp20[1], 0, 0);
        HuWinMesSet(var_s0_3, 0x3919, -1, -1);
    } else {
        HuWinMesMaxSizeGet(1, sp20, 0x3918);
        D_800B2340_main[2] = var_s0_3 = HuWinCreate((0x140 - sp20[0]) / 2, 0xE0 - sp20[1], sp20[0], sp20[1], 0, 0);
        HuWinMesSet(var_s0_3, 0x3918, -1, -1);
    }
    HuWinMesColSet(var_s0_3, 0);
    HuWinMesSpeedSet(var_s0_3, 0);
    HuWinPriSet(var_s0_3, 0);
    HuWinBGTPLvlSet(var_s0_3, 0xD0);
    HuWinBGColSet(var_s0_3, 0xFF, 0xFF, 0xFF);
    HuPrcVSleep();
    HuAudFXPlay(6);
    D_800D2132_main = 1;
    while (omPauseChk() != 0) {
        if (var_s4 >= 3 && (D_800C9520_main[0] & (L_JPAD | R_JPAD))) {
            var_s7 ^= 1;
            for (var_s2 = 0; var_s2 < 2; var_s2++) {
                func_80045964_main(D_800B2340_main[var_s2], var_s6);
                if (var_s4 <= var_s2 + var_s7 * 2) {
                    HuWinDispOff(D_800B2340_main[var_s2]);
                } else {
                    HuWinDispOn(D_800B2340_main[var_s2]);
                    HuWinMesSet(D_800B2340_main[var_s2], sp18[var_s2 + var_s7 * 2], -1, -1);
                }
            }
        }
        HuPrcVSleep();
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_80045964_main(s16 arg0, s16 arg1) {
    u8 sp10[4];
    s16 var_a2;
    s16 var_a1;
    s16 var_s0;

    var_a2 = 0;
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        for (var_a1 = 0; var_a1 < 4; var_a1++) {
            if (var_s0 == GwPlayer[var_a1].group) {
                sp10[var_a2] = var_a1;
                var_a2++;
            }
        }
        if (var_a2 >= 4) {
            break;
        }
    }
    for (var_s0 = 0; var_s0 < 4; var_s0++) {
        HuWinInsertMesSet(arg0, 0x1C00 + GwPlayer[sp10[var_s0]].chr, var_s0);
    }
}

void func_80045A90_main(void) {
    s16 i;

    HuSprGrpKill(D_800D6ADA_main);
    HuSprAnimKill(D_800D0A38_main);
    if (D_800CE214_main == 0) {
        for (i = 0; i < ARRAY_COUNT(D_800B2340_main); i++) {
            HuWinKill(D_800B2340_main[i]);
        }
    }
    omDelPrcObj(pauseProc);
}

s16 func_80045B24_main(s16 arg0, s16 arg1) {
    TextWindow *temp_v0_2;
    s16 temp_v0;

    temp_v0 = HuWinCreate(arg0, arg1, 0xC8, 0x3C, 0, 0);
    HuWinPriSet(temp_v0, 0);
    temp_v0_2 = &winData[temp_v0];
    temp_v0_2->spacing_x = 0;
    temp_v0_2->spacing_y = 1;
    HuWinMesSpeedSet(temp_v0, 0);
    HuWinBGTPLvlSet(temp_v0, 0xD0);
    HuWinBGColSet(temp_v0, 0x30, 0x40, 0x80);
    HuWinMesPalSet(temp_v0, 2, 0x40, 0xFF, 0xFF);
    return temp_v0;
}

s32 func_80045BF0_main(s32 arg0) {
    u32 var_v0;
    u32 var_v1;

    for (var_v1 = 0; var_v1 < 9; var_v1++) {
        if ((arg0 & 0xFF) == D_800A1590_main[var_v1]) {
            break;
        }
    }
    if (var_v1 >= 9) {
        var_v1 = -1;
    }
    return var_v1;
}

void func_80045C2C_main(void) {
    s32 var_v1;

    D_800B2390_main = NULL;
    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        D_800B2350_main[var_v1].unk00 = -1;
    }
}

// TODO: type of arg1 assumed. Implies unk06 and unk07.
s16 func_80045C64_main(u32 arg0, D_800B2350_main_Struct *arg1) {
    s32 temp_v0;
    s32 var_v1;
    s16 var_a2;
    s16 var_a1;
    s32 temp_a0;

    temp_v0 = func_80045BF0_main(arg0);
    if (temp_v0 < 0) {
        return -1;
    }
    temp_a0 = (arg0 >> 16) & 0xFF;
    for (var_v1 = 0; var_v1 < 8; var_v1++) {
        if (temp_a0 == D_800A1630_main[var_v1]) {
            break;
        }
    }
    if (var_v1 >= 8) {
        return -1;
    }
    temp_a0 = var_v1;
    var_a2 = D_800A159C_main[temp_v0];
    var_a1 = D_800A1610_main[temp_a0][temp_v0];
    var_v1 = var_a1;
    if (var_v1 == 0xFF) {
        var_a1 = -1;
        var_a2 = -1;
    }
    if (arg1 != NULL) {
        arg1->unk00 = var_a2;
        arg1->unk06 = temp_a0;
        arg1->unk07 = var_a1 + 1;
    }
    return var_a1;
}

// https://decomp.me/scratch/TTLIZ
void func_80045D38_main(omObjData *object) {
    s16 seNo;
    s32 i;
    s32 seId;
    u8 player;

    for (i = 0; i < 8; i++) {
        if (D_800B2350_main[i].unk00 < 0) {
            continue;
        }
        if (D_800B2350_main[i].unk07 != 0) {
            D_800B2350_main[i].unk07--;
            continue;
        }
        player = D_800B2350_main[i].unk05;
        if (player < 4) {
            seId = D_800B2350_main[i].unk00 + D_800B2350_main[i].unk06 + 1;
            seNo = func_8004AC98_main(seId, (s8)player);
        } else {
            seId = D_800B2350_main[i].unk00 + D_800B2350_main[i].unk06 + 1;
            seNo = func_8004AC5C_main(seId, object->work[0]);
            if (++object->work[0] >= 4) {
                object->work[0] = 0;
            }
        }
        if (seNo >= 0) {
            if (D_800B2350_main[i].unk02 >= 0) {
                HuAudFXPanning(seNo, D_800B2350_main[i].unk02);
            }
            if (D_800B2350_main[i].unk04 >= 0) {
                HuAudFXVolSet(seNo, D_800B2350_main[i].unk04);
            }
        }
        D_800B2350_main[i].unk00 = -1;
    }
}

omObjData *func_80045ED0_main(s32 arg0) {
    return func_80045F48_main(arg0, -1, -1, -1);
}

omObjData *func_80045EF4_main(u32 arg0, s16 arg1) {
    return func_80045F48_main(arg0, arg1, -1, -1);
}

omObjData *func_80045F1C_main(u32 arg0, s16 arg1, s16 arg2) {
    return func_80045F48_main(arg0, arg1, -1, arg2);
}

omObjData *func_80045F48_main(u32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    D_800B2350_main_Struct sp18;
    omObjData *temp_v0_2;

    if (func_80045C64_main(arg0, &sp18) >= 0) {
        u8 temp_06 = sp18.unk06;

        D_800B2350_main[temp_06].unk00 = sp18.unk00;
        D_800B2350_main[temp_06].unk02 = arg1;
        D_800B2350_main[temp_06].unk04 = arg2;
        D_800B2350_main[temp_06].unk05 = arg3;
        D_800B2350_main[temp_06].unk06 = sp18.unk06;
        D_800B2350_main[temp_06].unk07 = sp18.unk07;
        if (D_800B2390_main == NULL) {
            D_800B2390_main = omAddObj(32000, 0, 0, -1, func_80045D38_main);
            D_800B2390_main->work[0] = 0;
        }
    }
    return D_800B2390_main;
}
