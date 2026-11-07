#include "common.h"
#include "overlays/minigame.h"

// Per-minigame-field work allocated in func_800E9C20_minigame, stored at D_800EBDF4_minigame
typedef struct D_800EBDF4_minigame_Entry {
    /* 0x00 */ s16 *unk_00;
    /* 0x04 */ s16 *unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u16 unk_16;
} D_800EBDF4_minigame_Entry; // Size 0x18

extern s16 D_800EBDF0_minigame;
extern D_800EBDF4_minigame_Entry *D_800EBDF4_minigame;
extern s16 D_800EBDF8_minigame;
extern s16 D_800EBDFA_minigame;
extern u16 D_800EBDFC_minigame;

void func_800E9C20_minigame(s16 count, u16 length) {
    s32 i;
    s32 j;

    D_800EBDF0_minigame = count;
    D_800EBDFC_minigame = length;
    D_800EBDF4_minigame = HuMemAllocTag(count * sizeof(D_800EBDF4_minigame_Entry), 0x7918);
    D_800EBDF8_minigame = func_8000B838_main(0x210018);
    D_800EBDFA_minigame = func_8000B838_main(0x210019);
    for (i = 0; i < count; i++) {
        D_800EBDF4_minigame[i].unk_00 = HuMemAllocTag(length * sizeof(s16), 0x7918);
        D_800EBDF4_minigame[i].unk_04 = HuMemAllocTag(length * sizeof(s16), 0x7918);
        D_800EBDF4_minigame[i].unk_16 = 0;
        D_800EBDF4_minigame[i].unk_14 = 0;
        for (j = 0; j < length; j++) {
            D_800EBDF4_minigame[i].unk_00[j] = espEntry(D_800EBDF8_minigame, 0, 0);
            D_800EBDF4_minigame[i].unk_04[j] = espEntry(D_800EBDFA_minigame, 0, 0);
        }
        func_800E9F40_minigame(i, 24, 16, 0);
        func_800EA0FC_minigame(i, 0.0f, 100.0f);
        func_800EA178_minigame(i, 0.0f);
        func_800EA1E4_minigame(i, 0x8000);
        func_800EA444_minigame(i);
    }
}

void func_800E9E28_minigame(void) {
    s32 i;
    s32 j;

    for (i = 0; i < D_800EBDF0_minigame; i++) {
        for (j = 0; j < D_800EBDFC_minigame; j++) {
            espKill(D_800EBDF4_minigame[i].unk_00[j]);
            espKill(D_800EBDF4_minigame[i].unk_04[j]);
        }
        HuMemFree(D_800EBDF4_minigame[i].unk_00);
        HuMemFree(D_800EBDF4_minigame[i].unk_04);
    }
    HuSprAnimKill(D_800EBDF8_minigame);
    HuSprAnimKill(D_800EBDFA_minigame);
}

void func_800E9F40_minigame(s16 arg0, s16 x, s16 y, s16 arg3) {
    D_800EBDF4_minigame_Entry *entry = &D_800EBDF4_minigame[arg0];
    s32 i;

    switch (arg3) {
        case 0:
            for (i = 0; i < D_800EBDFC_minigame; i++) {
                espPosSet(entry->unk_00[i], x + 5 + i * 10, y + 5);
                espPosSet(entry->unk_04[i], x + 5 + i * 10, y + 5);
            }
            break;
        case 1:
            for (i = D_800EBDFC_minigame - 1; i >= 0; i--) {
                espPosSet(entry->unk_00[i], x + 5 + (D_800EBDFC_minigame - 1 - i) * 10, y + 5);
                espPosSet(entry->unk_04[i], x + 5 + (D_800EBDFC_minigame - 1 - i) * 10, y + 5);
            }
            break;
    }
}

void func_800EA0FC_minigame(s16 arg0, f32 arg1, f32 arg2) {
    D_800EBDF4_minigame[arg0].unk_08 = arg1;
    D_800EBDF4_minigame[arg0].unk_0C = arg2;
}

void func_800EA128_minigame(s16 arg0, f32 arg1) {
    D_800EBDF4_minigame[arg0].unk_10 = arg1;
    if (!(D_800EBDF4_minigame[arg0].unk_14 & 1)) {
        func_800EA2A8_minigame(arg0);
    }
}

void func_800EA178_minigame(s16 arg0, f32 arg1) {
    f32 range = D_800EBDF4_minigame[arg0].unk_0C - D_800EBDF4_minigame[arg0].unk_08;

    D_800EBDF4_minigame[arg0].unk_10 = (arg1 - D_800EBDF4_minigame[arg0].unk_08) / range;
    if (!(D_800EBDF4_minigame[arg0].unk_14 & 1)) {
        func_800EA2A8_minigame(arg0);
    }
}

void func_800EA1E4_minigame(s16 arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < D_800EBDFC_minigame; i++) {
        espPriSet(D_800EBDF4_minigame[arg0].unk_00[i], (u16)(arg1 + 1));
        espPriSet(D_800EBDF4_minigame[arg0].unk_04[i], (u16)arg1);
    }
}

void func_800EA2A8_minigame(s16 arg0) {
    D_800EBDF4_minigame_Entry *entry = &D_800EBDF4_minigame[arg0];
    f32 count;
    f32 step;
    f32 frac;
    s32 filled;
    s32 i;

    entry->unk_14 &= ~1;
    if (entry->unk_14 & 2) {
        return;
    }
    count = D_800EBDFC_minigame;
    filled = count * entry->unk_10;
    step = 1.0f / count;
    frac = (entry->unk_10 - step * filled) / step;
    for (i = 0; i < D_800EBDFC_minigame; i++) {
        espDispOn(entry->unk_00[i]);
        if (i < filled) {
            espDispOn(entry->unk_04[i]);
            espTPLvlSet(entry->unk_04[i], 256);
        } else if (i == filled) {
            espDispOn(entry->unk_04[i]);
            espTPLvlSet(entry->unk_04[i], frac * 256.0f);
        } else {
            espDispOff(entry->unk_04[i]);
        }
    }
}

void func_800EA444_minigame(s16 arg0) {
    s32 i;

    D_800EBDF4_minigame[arg0].unk_14 |= 1;
    for (i = 0; i < D_800EBDFC_minigame; i++) {
        espDispOff(D_800EBDF4_minigame[arg0].unk_00[i]);
        espDispOff(D_800EBDF4_minigame[arg0].unk_04[i]);
    }
}

void func_800EA518_minigame(void) {
    D_800EBDF4_minigame_Entry *entry;
    s32 i;
    s32 j;

    for (i = 0; i < D_800EBDF0_minigame; i++) {
        entry = &D_800EBDF4_minigame[i];
        if (entry->unk_14 & 1) {
            continue;
        }
        if (entry->unk_10 >= 1.0f) {
            if (!(entry->unk_14 & 2)) {
                entry->unk_14 |= 2;
                entry->unk_16 = 0;
            }
            if (entry->unk_16 < 2) {
                for (j = 0; j < D_800EBDFC_minigame; j++) {
                    espDispOff(entry->unk_04[j]);
                }
            } else {
                for (j = 0; j < D_800EBDFC_minigame; j++) {
                    espDispOn(entry->unk_04[j]);
                }
            }
            entry->unk_16 = (entry->unk_16 + 1) & 3;
        } else if (entry->unk_14 & 2) {
            entry->unk_14 &= ~2;
            func_800EA2A8_minigame(i);
        }
    }
}
