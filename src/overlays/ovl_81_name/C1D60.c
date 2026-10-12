#include "common.h"
#include "ovl_81.h"

typedef struct UnkNameDicePrcData {
    /* 0x00 */ s32 playerIndex;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkNameDicePrcData; // sizeof 0x10

extern u8 D_80105554_name_81;
extern u8 D_80105555_name_81;
extern f32 D_80105708_name_81;

void func_800DC0EC_name_81(void);

void func_800D9F90_name_81(s32 playerIndex) {
    UnkDiceRelated *dice = &D_800CDBD0_main[playerIndex];

    if (dice->unk28 == -1 && dice->dice->work[0] == 1) {
        if (dice->unk_0A == 1) {
            dice->unk28 = HuAudFXPlay(0x1D5);
        } else {
            dice->unk28 = HuAudFXPlay(0x100);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DA00C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DA460_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DA85C_name_81);

void func_800DAAB0_name_81(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < DICE_TOTAL; j++) {
            D_800CDBD0_main[i].rollValue[j] = 0;
            D_800CDBD0_main[i].predecidedRollValue[j] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DAB1C_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DABE0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DADA0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB148_name_81);

void func_800DB38C_name_81(s32 playerIndex) {
    UnkDiceRelated *dice = &D_800CDBD0_main[playerIndex];

    if (dice->omObj != NULL) {
        omDelObj(dice->omObj);
        dice->omObj = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB3E0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB4DC_name_81);

void func_800DB544_name_81(s32 arg0) {
    if (D_800CDBD0_main[arg0].unk_16 != -1) {
        func_8001C258_main(D_800CDBD0_main[arg0].unk_16, 4, 4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB58C_name_81);

void func_800DB5AC_name_81(s32 playerIndex) {
    if (D_80105555_name_81 && D_800CDBD0_main[playerIndex].unk_16 != -1) {
        func_8001C258_main(D_800CDBD0_main[playerIndex].unk_16, 4, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB600_name_81);

void func_800DB624_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].unk_09 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DB648_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DBAB0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DBD88_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DBEB0_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DBEF0_name_81);

void func_800DBFF8_name_81(void) {
    D_80105554_name_81 = 1;
    D_80105708_name_81 = 250.0f;
}

s32 func_800DC018_name_81(s32 arg0) {
    if (~D_800CDBD0_main[arg0].unk_16) {
        return 1;
    } else {
        return 0;
    }
}

void func_800DC044_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].rollValue[D_800CDBD0_main[arg0].rollValueIdx] = arg1;
}

void func_800DC07C_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].predecidedRollValue[D_800CDBD0_main[arg0].rollValueIdx] = arg1;
}

s8 func_800DC0B4_name_81(s32 arg0) {
    return D_800CDBD0_main[arg0].rollValue[D_800CDBD0_main[arg0].rollValueIdx];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC0EC_name_81);

Process *func_800DC324_name_81(s32 playerIndex) {
    Process *process;
    UnkNameDicePrcData *work;

    process = omAddPrcObj(func_800DC0EC_name_81, 0, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(UnkNameDicePrcData));
    process->user_data = work;
    work->playerIndex = playerIndex;
    work->state = 0;
    return process;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC384_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC390_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC3A0_name_81);

void func_800DC3AC_name_81(s32 playerIndex) {
    UnkDiceRelated *dice = &D_800CDBD0_main[playerIndex];

    if (dice->unk28 != -1) {
        HuAudFXStop(dice->unk28);
        dice->unk28 = -1;
    }
    dice->unk2A = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC410_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC4B4_name_81);

void func_800DC4C0_name_81(s32 arg0, s8 arg1) {
    D_800CDBD0_main[arg0].rollValueIdx = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC4E4_name_81);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_81_name/C1D60", func_800DC5CC_name_81);
