#include "common_duel.h"
#include "ovl_81.h"
#include "game/malloc.h"

extern u8 omAllPauseF;
extern s16 mbMesNum;

s32 D_80100F60_name_81[] = {
    0x00001D00,
    0x00001D01,
    0x00001D02,
    0x00001D03,
    0x00001D04,
    0x00001D05,
    0x00001D06,
    0x00001D07,
    0x00001D08,
    0x00001D09,
    0x00001D0A,
    0x00001D0B,
    0x00001D0C,
    0x00001D0D,
    0x00001D0E,
    0x00001D0F,
    0x00001D10,
    0x00001D11,
    0x00001D12,
    0x00001D13,
    0x00001D14,
    0x00001D15,
    0x00003018,
    0x00003019
};

static void func_800E1560_name_81(DuelHelpWin *arg0) {
    s16 sp18[2];

    if (arg0->unk_10 != NULL) {
        HuWinInsertMesSizeGet((u32)arg0->unk_10, 0);
    }

    HuWinMesMaxSizeGet(1, sp18, D_80100F60_name_81[arg0->unk_00]);
    if (arg0->unk_02 == -1) {
        arg0->winID = HuWinCreate(0xA0 - sp18[0] / 2, arg0->unk_04, sp18[0], sp18[1], 0, 0);
    } else {
        arg0->winID = HuWinCreate(arg0->unk_02, arg0->unk_04, sp18[0], sp18[1], 0, 4);
    }

    if (arg0->unk_10 != NULL) {
        HuWinInsertMesSet(arg0->winID, (u32)arg0->unk_10, 0);
    }
    HuWinPriSet(arg0->winID, 5);
    HuWinBGTPLvlSet(arg0->winID, 0);
    HuWinMesSpeedSet(arg0->winID, 0);
    HuWinAttrSet(arg0->winID, HUWIN_ATTR_NONE, HUWIN_ATTR_OUTLINE);
    HuWinMesSet(arg0->winID, D_80100F60_name_81[arg0->unk_00], -1, -1);
}

static void func_800E1694_name_81(DuelHelpWin *arg0) {
    HuWinKill(arg0->winID);
    arg0->winID = -1;
}

static void func_800E16C4_name_81(omObjData *arg0) {
    DuelHelpWin *temp_a0;

    temp_a0 = (DuelHelpWin *)arg0->data;
    if ((temp_a0->unk_01 == 1) && (omAllPauseF != 0)) {
        if (temp_a0->winID >= 0) {
            func_800E1694_name_81(temp_a0);
        }
    } else if (temp_a0->winID < 0) {
        func_800E1560_name_81(temp_a0);
    }
}

DuelHelpWin *func_800E172C_name_81(s16 arg0, s16 arg1, s16 arg2, u16 arg3) {
    DuelHelpWin *temp_v0;
    char *temp_v0_3;
    omObjData *temp_v0_2;

    temp_v0 = HuMemMemoryAllocTemp(sizeof(DuelHelpWin));
    if (temp_v0 != NULL) {
        temp_v0->unk_00 = arg0;
        temp_v0->unk_02 = arg1;
        temp_v0->unk_04 = arg2;
        temp_v0->unk_01 = arg3;
        temp_v0_2 = omAddObj(0x100, 0, 0, -1, func_800E16C4_name_81);
        temp_v0->unk_08 = temp_v0_2;
        temp_v0_2->data = temp_v0;
        omSetStatBit(temp_v0->unk_08, OM_STAT_NOALLPAUSE);
        temp_v0->winID = -1;
        if (arg0 != 6) {
            temp_v0->unk_10 = NULL;
        } else {
            temp_v0_3 = HuMemMemoryAllocTemp(8);
            temp_v0->unk_10 = temp_v0_3;
            sprintf(temp_v0_3, "\x03%2d\x08", mbMesNum);
            return temp_v0;
        }
    }
    return temp_v0;
}

DuelHelpWin *func_800E1824_name_81(s16 arg0, s16 arg1, u16 arg2) {
    return func_800E172C_name_81(arg0, -1, arg1, arg2);
}

void func_800E1854_name_81(DuelHelpWin *arg0) {
    if (arg0 != NULL) {
        arg0->unk_08->data = NULL;
        omDelObj(arg0->unk_08);
        if (arg0->winID >= 0) {
            HuWinKill(arg0->winID);
            if (arg0->unk_10 != NULL) {
                HuMemMemoryFreeTemp(arg0->unk_10);
            }
        }
        HuMemMemoryFreeTemp(arg0);
    }
}
