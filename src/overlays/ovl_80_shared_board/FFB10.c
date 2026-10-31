#include "common.h"
#include "game/board.h"
#include "101840.h"

extern s16 D_80101480_shared_board;
extern s16 D_80101482_shared_board;

static void func_800EBEF0_shared_board(s16 arg0) {
    if ((GwSystem.current_player_index == 4) || (D_80101482_shared_board != 0)) {
        func_800EE2A4_shared_board(arg0);
        return;
    }
    func_800EDC58_shared_board(arg0, GwSystem.current_player_index);
}

static void func_800EBF48_shared_board(s16 arg0, s32 arg1) {
    if ((GwSystem.current_player_index == 4) || (D_80101482_shared_board != 0)) {
        func_800EE2C0_shared_board(arg0);
        return;
    }
    func_800EDC74_shared_board(arg0, arg1);
}

void func_800EBF98_shared_board(s16 arg0, s32 arg1) {
    if ((GwSystem.current_player_index == MB_MAX_PLAYERS) || (D_80101482_shared_board != 0)) {
        func_800EE2A4_shared_board(arg0);
        return;
    }
    func_800EDC58_shared_board(arg0, arg1);
}

s16 MBWinCreate(s16 arg0, s16 *arg1, s16 arg2) {
    s32 result;

    if (arg2 == -1) {
        if (arg0 == arg2) {
            result = HuWinExCreate(-1, 0, 0, arg1[0], arg1[1], 2);
        } else {
            result = HuWinExCreate(arg0, 0, 0, arg1[0], arg1[1], 2);
        }
    } else {
        if (arg0 == -1) {
            result = HuWinExCreate(-1, 0xA0 - arg1[0] / 2, arg2, arg1[0], arg1[1], 0);
        } else {
            result = HuWinExCreate(arg0, 0xA0 - arg1[0] / 2, arg2, arg1[0], arg1[1], 0);
        }
    }

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(result, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    return result;
}

void MBWinOpen(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbWinId = temp_v0;

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void MBWinInsertOpen(s32 arg0, char *arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5) {
    s16 sp18[2];
    s16 temp_v0;

    // if arg isn't a pointer, treat as ID and return pointer to message from dynamic memory
    if (arg1 != NULL) {
        HuWinInsertMesSizeGet((u32)arg1, 0);
    }
    if (arg2 != NULL) {
        HuWinInsertMesSizeGet(arg2, 1);
    }
    if (arg3 != NULL) {
        HuWinInsertMesSizeGet(arg3, 2);
    }
    if (arg4 != NULL) {
        HuWinInsertMesSizeGet(arg4, 3);
    }
    if (arg5 != NULL) {
        HuWinInsertMesSizeGet(arg5, 4);
    }

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbWinId = temp_v0;

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }
    if (arg1 != NULL) {
        HuWinInsertMesSet(temp_v0, (u32)arg1, 0);
    }
    if (arg2 != 0) {
        HuWinInsertMesSet(temp_v0, arg2, 1);
    }
    if (arg3 != 0) {
        HuWinInsertMesSet(temp_v0, arg3, 2);
    }
    if (arg4 != 0) {
        HuWinInsertMesSet(temp_v0, arg4, 3);
    }
    if (arg5 != 0) {
        HuWinInsertMesSet(temp_v0, arg5, 4);
    }
    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void func_800EC39C_shared_board(s32 arg0) {
    func_800EBF48_shared_board(mbWinId, arg0);
}

void func_800EC3C0_shared_board(s32 arg0) {
    func_800EBF98_shared_board(mbWinId, arg0);
}

void func_800EC3E4_shared_board(void) {
    HuWinExAnimOut(mbWinId, 0);
    HuWinKill(mbWinId);
}

void MBDlgResultWinExec(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbDlgWinId = temp_v0;

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
    func_800EBEF0_shared_board(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MBDlgWinExecY(s16 arg0, s32 arg1, s32 arg2) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
    func_800EBEF0_shared_board(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MBDlgWinExec(s32 arg0, s32 arg1) {
    MBDlgWinExecY(arg0, arg1, -1);
}

void func_800EC5B4_shared_board(s16 arg0, s32 arg1) {
    D_80101482_shared_board = 1;
    MBDlgWinExecY(arg0, arg1, -1);
    D_80101482_shared_board = 0;
}

void func_800EC5EC_shared_board(s16 arg0, s32 arg1, s16 arg2) {
    D_80101482_shared_board = 1;
    MBDlgWinExecY(arg0, arg1, arg2);
    D_80101482_shared_board = 0;
}

void MBDlgWinCreate(s32 arg0, s32 arg1) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBWinCreate(arg0, sp10, -1);
    mbDlgWinId = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void func_800EC6A8_shared_board(void) {
    HuWinExAnimIn(mbDlgWinId);
}

void MBDlgWinClose(void) {
    HuWinExAnimOut(mbDlgWinId, 0);
}

void MBDlgWinKill(void) {
    HuWinKill(mbDlgWinId);
}

void MBDlgWinInsertCreateY(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
    s16 sp10[2];
    s16 temp_v0;

    if (arg2 != 0) {
        HuWinInsertMesSizeGet(arg2, 0);
    }
    if (arg3 != 0) {
        HuWinInsertMesSizeGet(arg3, 1);
    }
    if (arg4 != 0) {
        HuWinInsertMesSizeGet(arg4, 2);
    }
    if (arg5 != 0) {
        HuWinInsertMesSizeGet(arg5, 3);
    }
    if (arg6 != 0) {
        HuWinInsertMesSizeGet(arg6, 4);
    }

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBWinCreate(arg0, sp10, arg7);
    mbDlgWinId = temp_v0;

    if (arg2 != 0) {
        HuWinInsertMesSet(temp_v0, arg2, 0);
    }
    if (arg3 != 0) {
        HuWinInsertMesSet(temp_v0, arg3, 1);
    }
    if (arg4 != 0) {
        HuWinInsertMesSet(temp_v0, arg4, 2);
    }
    if (arg5 != 0) {
        HuWinInsertMesSet(temp_v0, arg5, 3);
    }
    if (arg6 != 0) {
        HuWinInsertMesSet(temp_v0, arg6, 4);
    }
    if (D_80101480_shared_board != 0) {
        func_8005E1A8_main(temp_v0, D_80101480_shared_board);
    }

    HuWinMesSet(temp_v0, arg1, -1, -1);

    if (arg0 == -1) {
        HuWinExAnimIn(temp_v0);
    } else {
        HuWinExAnimIn(temp_v0);
    }

    func_800EBF48_shared_board(temp_v0, GwSystem.current_player_index);
}

void MBDlgWinInsertCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    MBDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
}

void func_800EC92C_shared_board(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6) {
    D_80101482_shared_board = 1;
    MBDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
    D_80101482_shared_board = 0;
}

void func_800EC980_shared_board(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
    D_80101482_shared_board = 1;
    MBDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    D_80101482_shared_board = 0;
}

void func_800EC9DC_shared_board(void) {
    winData[mbDlgWinId].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    func_800EBF48_shared_board(mbDlgWinId, GwSystem.current_player_index);
}

void func_800ECA38_shared_board(void) {
    D_80101482_shared_board = 1;
    winData[mbDlgWinId].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    func_800EBF48_shared_board(mbDlgWinId, GwSystem.current_player_index);
    D_80101482_shared_board = 0;
}

void func_800ECAA8_shared_board(s32 arg0) {
    D_80101480_shared_board = arg0;
}

void func_800ECAB4_shared_board(void) {
    D_80101480_shared_board = 0;
    D_80101482_shared_board = 0;
}
