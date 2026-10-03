#include "common.h"
#include "game/board.h"

typedef struct UnkC5770 {
    /* 0x00 */ s32 state;
    /* 0x04 */ char unk_04[0xC];
} UnkC5770; // sizeof 0x10

typedef struct UnkC5770B70 {
    /* 0x00 */ s16 windowId;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ u16 unk_04;
    /* 0x06 */ u16 halfWidth;
    /* 0x08 */ u16 halfHeight;
} UnkC5770B70; // sizeof 0xA

extern void func_800E03F0_name_81(void);
extern void func_800E08D8_name_81(void);
extern u32 D_800D2094_main;
extern u32 D_80100F38_name_81;
extern UnkData_CD0A0 D_800CC4A0_main;
extern u8 D_800CC3E0_main[];
extern UnkC5770B70 D_80102B70_name_81[5];
extern omObjData *D_80102BA4_name_81;
extern s16 D_80102BB0_name_81;
extern s16 D_80102BB2_name_81;
extern s16 D_80102BB4_name_81;
extern s16 D_80102BB6_name_81;
extern s16 D_80102BC0_name_81[2];
extern s16 D_80102BC4_name_81[2][2];
extern omObjData *D_80102BCC_name_81[2];

void func_800DD9A0_name_81(void) {
    if (D_800D2094_main >= (D_80100F38_name_81 + 4)) {
        HuAudFXPlay(0x104);
        D_80100F38_name_81 = D_800D2094_main;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DD9EC_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DE4D0_name_81);

void func_800DF154_name_81(void) {
    s32 category;
    s32 minigameCategoryIndex;

    for (category = 0; category <= 0; category++) {
        for (minigameCategoryIndex = 0; minigameCategoryIndex < PREV_MINIGAME_LIST_LENGTH; minigameCategoryIndex++) {
            D_800CC4A0_main.recentMinigames[category][minigameCategoryIndex] = -1;
        }
        D_800CC3E0_main[category] = 0;
    }
}

void func_800DF1B0_name_81(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        D_80102B70_name_81[i].windowId = -1;
    }
    D_80102BA4_name_81 = NULL;
    D_80102BB2_name_81 = -1;
    D_80102BB0_name_81 = -1;
    D_80102BB6_name_81 = -1;
    D_80102BB4_name_81 = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF210_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF348_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF49C_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023C8_name_81);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_81_name/C5770", D_801023D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DF594_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800DFBF4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E02B4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0300_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0310_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E03F0_name_81);

Process *func_800E0888_name_81(void) {
    Process *process = omAddPrcObj(func_800E03F0_name_81, 0, 0x2000, 0x40);
    UnkC5770 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkC5770));

    process->user_data = work;
    work->state = 0;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E08D8_name_81);

void func_800E0924_name_81(void) {
    omAddPrcObj(func_800E08D8_name_81, 0, 0x2000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0950_name_81);

void func_800E0CEC_name_81(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        D_80102BC0_name_81[i] = -1;
        D_80102BCC_name_81[i] = NULL;
        for (j = 0; j < 2; j++) {
            D_80102BC4_name_81[i][j] = -1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0D64_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0E38_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E0E70_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E14B0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E14D8_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C5770", func_800E1504_name_81);
