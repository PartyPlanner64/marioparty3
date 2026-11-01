#include "common.h"
#include "game/pad.h"

extern s32 D_800B1A30_main;

void GWInit(void) {
    GW_COMMON *gw = &GwCommon;

    bzero(&GwCommon, sizeof(GwCommon));
    bzero(&GwStory, sizeof(GwStory));

    gw->unk_00 = 0x91;
    GwSystem.current_board_index = 0;
    GwSystem.minigame_index = 0;
}

void GWMgNoSet(s8 arg0) {
    GwSystem.minigame_index = arg0;
}

// bit position to byte + bit position
void GWMgBitGet(s16 bitPos, s16 *byteIdx, s16 *bitIdx) {
    s16 pos;

    if (bitPos < 0 && GwSystem.minigame_index > 0) {
        pos = GwSystem.minigame_index - 1;
    } else {
        if (bitPos < 0) {
            pos = 0;
        } else {
            pos = bitPos;
        }
    }

    *byteIdx = pos / 8;
    *bitIdx = pos % 8;
}

// set bit
void GWMgUnlockSet(s16 bitPos) {
    s16 outBytePos;
    s16 outBitPos;

    GWMgBitGet(bitPos, &outBytePos, &outBitPos);
    GwCommon.mgUnlock[outBytePos] |= (1 << outBitPos);
}

// clear bit
void GWMgUnlockReset(s16 bitPos) {
    s16 outBytePos;
    s16 outBitPos;

    GWMgBitGet(bitPos, &outBytePos, &outBitPos);
    GwCommon.mgUnlock[outBytePos] &= ~(1 << outBitPos);
}

// check bit
s16 GWMgUnlockCheck(s16 arg0) {
    s16 sp10;
    s16 sp12;

    GWMgBitGet(arg0, &sp10, &sp12);
    return GwCommon.mgUnlock[sp10] & (1 << sp12);
}

void GWMgRecordSet(s16 arg0, u32 arg1) {
    if (_CheckFlag(FLAG_MG_PRACTICE) == 0) {
        GwCommon.mgRecord[arg0] = arg1;
    }
}

u16 GWMgRecordGet(s16 arg0) {
    return GwCommon.mgRecord[arg0];
}

void GWBoardNoSet(s8 boardIndex) {
    GwSystem.current_board_index = boardIndex;
}

u8 *GWBoardRecordGet(s16 arg0) {
    s16 idx = arg0;

    if (arg0 < 0) {
        idx = GwSystem.current_board_index;
    }

    if (GwSystem.playMode & 1) {
        return (u8 *)&GwCommon.unk_1D[2] + idx * 9;
    }
    return (u8 *)&GwCommon.unk_1D[0x38] + idx * 9;
}

u8 GWPlayNumGet(s16 arg0) {
    return *GWBoardRecordGet(arg0);
}

void GWPlayNumInc(s16 arg0) {
    s16 idx = arg0;
    u8 *record = GWBoardRecordGet(arg0);

    if (arg0 < 0) {
        idx = GwSystem.current_board_index;
    }

    if (idx < 8) {
        s16 num = *record + 1;
        u32 inc = num;
        u32 offset = 0;

        if (inc > 999) {
            num = 999;
        }

        // offset cancels out, but its zero init survives as the dead move that
        // fills the clamp branch's delay slot.
        *record = num + offset - offset;
    }
}

void GWCharPlayNumInc(s16 boardNo, s16 charNo) {
    u8 *record = GWBoardRecordGet(boardNo);

    if (boardNo < 0) {
        boardNo = GwSystem.current_board_index;
    }

    if (boardNo < 8) {
        record += charNo;
        if (record[1] < 99) {
            record[1]++;
        }
    }
}

s32 func_80035E3C_main(s16 arg0) {
    // 0x18 of stack is reserved but unused in the original; the array keeps the frame.
    s32 buf[6];

    GWBoardRecordGet(arg0);
    return 0;
}

void func_80035E60_main(s16 arg0) {
    u8 *record = GWBoardRecordGet(arg0);
    *record = *record;
}

void func_80035E88_main(s16 arg0) {
    u8 *record = GWBoardRecordGet(arg0);
    *record = *record;
}

s32 _CheckFlag(s32 flag) {
    return GwCommon.flag[flag / 8] & (1 << flag % 8);
}

void _SetFlag(s32 flag) {
    GwCommon.flag[flag / 8] |= (1 << flag % 8);
}

void _ClearFlag(s32 flag) {
    GwCommon.flag[flag / 8] &= ~(1 << flag % 8);
}

s32 GWBoardFlagCheck(s32 flag) {
    return GwSystem.data_flags[flag / 8] & (1 << flag % 8);
}

void GWBoardFlagSet(s32 flag) {
    GwSystem.data_flags[flag / 8] |= (1 << flag % 8);
}

void GWBoardFlagClear(s32 flag) {
    GwSystem.data_flags[flag / 8] &= ~(1 << flag % 8);
}

void GWContErrorSet(void) {
    if (CheckControllerRead(0) != FALSE) {
        D_800B1A30_main = TRUE;
        return;
    }
    D_800B1A30_main = FALSE;
}

s32 GWContErrorGet(void) {
    return D_800B1A30_main;
}
