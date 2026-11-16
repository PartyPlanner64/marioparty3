#include "common_duel.h"
#include "ovl_81.h"

extern s16 mbdWinId;

s16 mbdDlgWinTabWidth = 0;
s16 mbdDlgWinAllKeyF = 0;

void MBDWinComKeyAllWait(s16);
void MBDWinComKeyAllWaitKeep(s16);
void MBDWinComKeyWait(s16, s32);
void MBDWinComKeyWaitKeep(s16, s32);
void MBDDlgWinExecY(s16 arg0, s32 arg1, s32 arg2);

void MBDWinIdKeyWait(s16 arg0) {
    if (mbdDlgWinAllKeyF != 0) {
        MBDWinComKeyAllWait(arg0);
        return;
    }
    MBDWinComKeyWait(arg0, GwSystem.current_player_index);
}

void MBDWinIdPlayerKeyWaitKeep(s16 arg0, s32 arg1) {
    if ((GwSystem.current_player_index == 4) || (mbdDlgWinAllKeyF != 0)) {
        MBDWinComKeyAllWaitKeep(arg0);
        return;
    }
    MBDWinComKeyWaitKeep(arg0, arg1);
}

s16 MBDWinCreate(s16 arg0, s16 *arg1, s16 arg2) {
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

    if (winPauseF == 0) {
        HuWinAttrSet(result, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    return result;
}

void MBDWinOpen(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbdWinId = temp_v0;

    if (winPauseF == 0) {
        HuWinAttrSet(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void MBDWinInsertOpen(s32 arg0, char *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s16 sp18[2];
    s16 temp_v0;

    // if arg isn't a pointer, treat as ID and return pointer to message from dynamic memory
    if (arg1 != NULL) {
        HuWinInsertMesSizeGet((u32)arg1, 0);
    }
    if (arg2 != 0) {
        HuWinInsertMesSizeGet(arg2, 1);
    }
    if (arg3 != 0) {
        HuWinInsertMesSizeGet(arg3, 2);
    }
    if (arg4 != 0) {
        HuWinInsertMesSizeGet(arg4, 3);
    }
    if (arg5 != 0) {
        HuWinInsertMesSizeGet(arg5, 4);
    }

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbdWinId = temp_v0;

    if (winPauseF == 0) {
        HuWinAttrSet(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
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

void MBDWinKeyWaitKeep(s32 arg0) {
    MBDWinIdPlayerKeyWaitKeep(mbdWinId, arg0);
}

void MBDWinClose(void) {
    HuWinExAnimOut(mbdWinId, 0);
    HuWinKill(mbdWinId);
}

void MBDDlgResultWinExec(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    mbdDlgWinId = temp_v0;

    if (winPauseF == 0) {
        HuWinAttrSet(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
    MBDWinIdKeyWait(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MBDDlgWinExecY(s16 arg0, s32 arg1, s32 arg2) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBDWinCreate(arg0, sp10, arg2);
    mbdDlgWinId = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
    MBDWinIdKeyWait(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MBDDlgWinExec(s16 arg0, s32 arg1) {
    MBDDlgWinExecY(arg0, arg1, -1);
}

void MBDDlgWinExecAllKey(s16 arg0, s32 arg1) {
    mbdDlgWinAllKeyF = 1;
    MBDDlgWinExecY(arg0, arg1, -1);
    mbdDlgWinAllKeyF = 0;
}

void MBDDlgWinExecYAllKey(s16 arg0, s32 arg1, s16 arg2) {
    mbdDlgWinAllKeyF = 1;
    MBDDlgWinExecY(arg0, arg1, arg2);
    mbdDlgWinAllKeyF = 0;
}

void MBDDlgWinCreate(s16 arg0, s32 arg1) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBDWinCreate(arg0, sp10, -1);
    mbdDlgWinId = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void MBDDlgWinOpen(void) {
    HuWinExAnimIn(mbdDlgWinId);
}

void MBDDlgWinClose(void) {
    HuWinExAnimOut(mbdDlgWinId, 0);
}

void MBDDlgWinKill(void) {
    HuWinKill(mbdDlgWinId);
}

void MBDDlgWinInsertCreateY(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
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
    temp_v0 = MBDWinCreate(arg0, sp10, arg7);
    mbdDlgWinId = temp_v0;
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
    if (mbdDlgWinTabWidth != 0) {
        HuWinTabWidthSet(temp_v0, mbdDlgWinTabWidth);
    }
    HuWinMesSet(temp_v0, arg1, -1, -1);
    if (arg0 == -1) {
        HuWinExAnimIn(temp_v0);
    } else {
        HuWinExAnimIn(temp_v0);
    }

    MBDWinIdPlayerKeyWaitKeep(temp_v0, GwSystem.current_player_index);
}

void MBDDlgWinInsertCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    MBDDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
}

void MBDDlgWinInsertCreateAllKey(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    mbdDlgWinAllKeyF = 1;
    MBDDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
    mbdDlgWinAllKeyF = 0;
}

void MBDDlgWinInsertCreateYAllKey(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s16 arg7) {
    mbdDlgWinAllKeyF = 1;
    MBDDlgWinInsertCreateY(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    mbdDlgWinAllKeyF = 0;
}

void MBDDlgWinMesWait(void) {
    winData[mbdDlgWinId].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    MBDWinIdPlayerKeyWaitKeep(mbdDlgWinId, GwSystem.current_player_index);
}

void MBDDlgWinMesWaitAllKey(void) {
    mbdDlgWinAllKeyF = 1;
    winData[mbdDlgWinId].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    MBDWinIdPlayerKeyWaitKeep(mbdDlgWinId, GwSystem.current_player_index);
    mbdDlgWinAllKeyF = 0;
}

void MBDDlgWinTabWidthSet(s32 arg0) {
    mbdDlgWinTabWidth = arg0;
}

void MBDDlgWinParamReset(void) {
    mbdDlgWinTabWidth = 0;
    mbdDlgWinAllKeyF = 0;
}
