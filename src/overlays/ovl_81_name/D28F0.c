#include "common_duel.h"
#include "ovl_81.h"

extern s16 D_80105712_name_81;

void func_800EF3B4_name_81(s16);
void func_800EF3D0_name_81(s16);
void func_800EED68_name_81(s16, s32);
void func_800EED84_name_81(s16, s32);
void func_800EB094_name_81(s16 arg0, s32 arg1, s32 arg2);

void func_800EAB20_name_81(s16 arg0) {
    if (D_801011D2_name_81 != 0) {
        func_800EF3B4_name_81(arg0);
        return;
    }
    func_800EED68_name_81(arg0, GwSystem.current_player_index);
}

void func_800EAB6C_name_81(s16 arg0, s32 arg1) {
    if ((GwSystem.current_player_index == 4) || (D_801011D2_name_81 != 0)) {
        func_800EF3D0_name_81(arg0);
        return;
    }
    func_800EED84_name_81(arg0, arg1);
}

s16 func_800EABBC_name_81(s16 arg0, s16 *arg1, s16 arg2) {
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

void func_800EAD08_name_81(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    D_80105712_name_81 = temp_v0;

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void func_800EADBC_name_81(s32 arg0, char *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
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
    D_80105712_name_81 = temp_v0;

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

void func_800EAF70_name_81(s32 arg0) {
    func_800EAB6C_name_81(D_80105712_name_81, arg0);
}

void func_800EAF94_name_81(void) {
    HuWinExAnimOut(D_80105712_name_81, 0);
    HuWinKill(D_80105712_name_81);
}

void func_800EAFC4_name_81(s32 arg0) {
    s16 sp18[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp18, arg0);
    temp_v0 = HuWinExCreate(-1, 0, 0, sp18[0], sp18[1], 2);
    D_8010555C_name_81 = temp_v0;

    if (D_800CB99C_main == 0) {
        func_8005B63C_main(temp_v0, HUWIN_ATTR_PAUSE, HUWIN_ATTR_PAUSE);
    }

    HuWinMesSet(temp_v0, arg0, -1, -1);
    HuWinExAnimIn(temp_v0);
    func_800EAB20_name_81(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void func_800EB094_name_81(s16 arg0, s32 arg1, s32 arg2) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = func_800EABBC_name_81(arg0, sp10, arg2);
    D_8010555C_name_81 = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
    func_800EAB20_name_81(temp_v0);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void func_800EB140_name_81(s16 arg0, s32 arg1) {
    func_800EB094_name_81(arg0, arg1, -1);
}

void func_800EB164_name_81(s16 arg0, s32 arg1) {
    D_801011D2_name_81 = 1;
    func_800EB094_name_81(arg0, arg1, -1);
    D_801011D2_name_81 = 0;
}

void func_800EB19C_name_81(s16 arg0, s32 arg1, s16 arg2) {
    D_801011D2_name_81 = 1;
    func_800EB094_name_81(arg0, arg1, arg2);
    D_801011D2_name_81 = 0;
}

void func_800EB1D8_name_81(s16 arg0, s32 arg1) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = func_800EABBC_name_81(arg0, sp10, -1);
    D_8010555C_name_81 = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
}

void func_800EB258_name_81(void) {
    HuWinExAnimIn(D_8010555C_name_81);
}

void func_800EB278_name_81(void) {
    HuWinExAnimOut(D_8010555C_name_81, 0);
}

void func_800EB29C_name_81(void) {
    HuWinKill(D_8010555C_name_81);
}

void func_800EB2BC_name_81(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7) {
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
    temp_v0 = func_800EABBC_name_81(arg0, sp10, arg7);
    D_8010555C_name_81 = temp_v0;
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
    if (D_801011D0_name_81 != 0) {
        func_8005E1A8_main(temp_v0, D_801011D0_name_81);
    }
    HuWinMesSet(temp_v0, arg1, -1, -1);
    if (arg0 == -1) {
        HuWinExAnimIn(temp_v0);
    } else {
        HuWinExAnimIn(temp_v0);
    }

    func_800EAB6C_name_81(temp_v0, GwSystem.current_player_index);
}

void func_800EB49C_name_81(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
}

void func_800EB4DC_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    D_801011D2_name_81 = 1;
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, -1);
    D_801011D2_name_81 = 0;
}

void func_800EB530_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s16 arg7) {
    D_801011D2_name_81 = 1;
    func_800EB2BC_name_81(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    D_801011D2_name_81 = 0;
}

void func_800EB58C_name_81(void) {
    winData[D_8010555C_name_81].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    func_800EAB6C_name_81(D_8010555C_name_81, GwSystem.current_player_index);
}

void func_800EB5E8_name_81(void) {
    D_801011D2_name_81 = 1;
    winData[D_8010555C_name_81].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    func_800EAB6C_name_81(D_8010555C_name_81, GwSystem.current_player_index);
    D_801011D2_name_81 = 0;
}

void func_800EB658_name_81(s32 arg0) {
    D_801011D0_name_81 = arg0;
}

void func_800EB664_name_81(void) {
    D_801011D0_name_81 = 0;
    D_801011D2_name_81 = 0;
}
