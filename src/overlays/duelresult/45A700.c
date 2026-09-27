#include "common.h"
#include "mallocblock.h"

// Work area allocated by func_8010ABE0 and stored at the process's user_data
// (see Process.user_data). Total size is 0x4C; fields are added as functions
// are decompiled.
typedef struct DuelResultWork {
    /* 0x00 */ u32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ char unk_24[0x28];
} DuelResultWork; // sizeof 0x4C

void func_8010C8E0_duelresult(void);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010ABE0_duelresult);

void func_8010AC6C_duelresult(DuelResultWork *arg0, u32 arg1) {
    arg0->unk_00 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010AC74_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010AC84_duelresult);

void func_8010AC94_duelresult(DuelResultWork *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010AC9C_duelresult);

s16 func_8010ACB4_duelresult(DuelResultWork *arg0) {
    return arg0->unk_04;
}

void func_8010ACBC_duelresult(DuelResultWork *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010ACC4_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010BDA4_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010C13C_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010C21C_duelresult);

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010C72C_duelresult);

void func_8010C880_duelresult(void) {
    Process *process = omAddPrcObj(func_8010C8E0_duelresult, 0x3F00, 0x2000, 0);
    DuelResultWork *work = HuMemAllocTag(sizeof(DuelResultWork), 0x7918);

    process->user_data = work;
    work->unk_18.x = 0.0f;
    work->unk_18.y = 100.0f;
    work->unk_18.z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/duelresult/45A700", func_8010C8E0_duelresult);
