#include "common_duel.h"
#include "game/board.h"
#include "ovl_81.h"

typedef struct UnkC5770 {
    /* 0x00 */ s32 state;
    /* 0x04 */ char unk_04[0xC];
} UnkC5770; // sizeof 0x10

typedef struct UnkC5770Rect {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} UnkC5770Rect; // sizeof 0x8

extern u32 D_800D2094_main;
extern UnkData_CD0A0 D_800CC4A0_main;
extern s8 D_800CC3E0_main[];
u8 D_80100E50_name_81[] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 0 };
u8 D_80100E5C_name_81[] = { 49, 50, 51, 53, 55, 56, 57, 0 };
u8 D_80100E64_name_81[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
    2, 3, 4, 5, 6, 7, 8, 9, 11,
    1, 2, 3, 4, 5, 6, 7, 8, 9, 11,
    0
};
u8 D_80100E84_name_81[] = { 5, 3 };
u8 D_80100E88_name_81[] = { 5, 1, 2, 1 };
UnkC5770Rect D_80100E8C_name_81[] = {
    { 60, 328, 200, 20 },
    { 60, 348, 200, 20 },
    { 60, 368, 200, 20 },
    { 60, 388, 200, 20 },
    { 60, 408, 200, 20 },
};
UnkC5770Rect D_80100EB4_name_81[] = {
    { 95, 330, 130, 20 },
    { 95, 354, 130, 20 },
    { 95, 378, 130, 20 },
};
u8 D_80100ECC_name_81[] = { 50, 34 };
u8 D_80100ED0_name_81[] = { 50, 80 };
u8 D_80100ED4_name_81[] = { 20, 24 };
u8 D_80100ED8_name_81[] = { 114, 116 };
s8 D_80100EDC_name_81[][2] = { { 1, 0 }, { 9, 15 }, { 11, 8 }, { 13, 0 } };
s32 D_80100EE4_name_81[] = { 0x4700, 0x1F20 };
// Indexed by minigame number - 1.
u8 D_80100EEC_name_81[] = {
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 6, 6, 7, 7, 7
};
u32 D_80100F38_name_81 = 0;
s32 D_80100F3C_name_81 = 0;
DuelHelpWin *D_80100F40_name_81 = NULL;
Object *D_80100F44_name_81 = NULL;
s32 D_80100F48_name_81[2] = { 0 }; /* Unreferenced. */
f32 D_80100F50_name_81[2][2] = { { 70.0f, 64.0f }, { 250.0f, 160.0f } };

extern UnkC5770B70 D_80102B70_name_81[5];
extern omObjData *D_80102BA4_name_81;
extern s8 D_80102BA8_name_81[5];
extern s8 D_80102BAD_name_81;
extern s8 D_80102BAE_name_81;
extern s16 D_80102BB0_name_81;
extern s16 D_80102BB2_name_81;
extern s16 D_80102BB4_name_81;
extern s16 D_80102BB6_name_81;
extern s32 D_80102BB8_name_81;
extern s16 D_80102BC0_name_81[2];
extern s16 D_80102BC4_name_81[2][2];
extern omObjData *D_80102BCC_name_81[2];
extern u8 D_80102BD4_name_81;
extern f32 D_80102BD8_name_81[2][2];

extern Object *func_800EED24_name_81(void);
extern void func_800E363C_name_81(s32 arg0, Vec *pos);
extern s32 func_800EAA7C_name_81(s32 spaceType);
extern s32 func_800E3858_name_81(void);
extern void func_800E3868_name_81(void);
extern void func_800F66BC_name_81(s32 arg0);
extern s32 func_800F6CA0_name_81(void);
extern void func_800F6CEC_name_81(void);
extern void func_800F6F84_name_81(void);

void func_800DF49C_name_81(void);
void func_800DF594_name_81(s32 arg0);
void func_800DFBF4_name_81(void);
void func_800E03F0_name_81(void);
void func_800E08D8_name_81(void);
void func_800E0D64_name_81(s32 arg0);
void func_800E0E70_name_81(s32 arg0, s32 coins, s32 arg2, s32 arg3);

void func_800DD9A0_name_81(void) {
    if (D_800D2094_main >= (D_80100F38_name_81 + 4)) {
        HuAudFXPlay(0x104);
        D_80100F38_name_81 = D_800D2094_main;
    }
}

void func_800DD9EC_name_81(omObjData *arg0) {
    UnkC5770B70 *entry;
    s32 i;
    s16 new_var;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.1f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                    new_var = 0xE0;
                    entry = &D_80102B70_name_81[i];
                    HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                    HuWinScaleSet(entry->windowId, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                HuSprPosSet(D_80102BB0_name_81, 0, 0xA0, D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var));
                HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 5;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 10.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                new_var = 0xE0;
                entry = &D_80102B70_name_81[i];
                HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                HuWinScaleSet(entry->windowId, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            HuSprPosSet(D_80102BB0_name_81, 0, 0xA0, D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var));
            HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                func_800DD9A0_name_81();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = func_800EFE20_name_81(D_80100E84_name_81[D_80102BAD_name_81]);
                arg0->work[3] = 0;
                func_800DF49C_name_81();
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if (arg0->work[3] != 0 && arg0->scale.x <= 0.08f) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y == 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % D_80100E84_name_81[D_80102BAD_name_81];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                    }
                }
                func_800DD9A0_name_81();
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                entry = &D_80102B70_name_81[i];
                if (i == arg0->work[1]) {
                    HuWinBGColSet(entry->windowId, 0, 0xC8, 0);
                    HuWinBGTPLvlSet(entry->windowId, 0x100);
                    HuWinPriSet(entry->windowId, 0x2328);
                } else {
                    HuWinBGColSet(entry->windowId, 0x40, 0x40, 0x80);
                    HuWinBGTPLvlSet(entry->windowId, 0);
                    HuWinPriSet(entry->windowId, 0x2710);
                }
            }

            if (arg0->work[1] == arg0->work[2] || arg0->scale.x < 1.0f) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if (arg0->work[1] == arg0->work[2] && arg0->work[3] == 0 && arg0->scale.z + 0.08f >= 1.0f) {
                    if ((rand8() & 0xF) || arg0->scale.y == 1.0f || arg0->work[1] == 0) {
                        if (GwSystem.show_minigame_explanations == FALSE || GwSystem.current_board_index == 6) {
                            HuAudFXPlay(0x105);
                        } else {
                            HuAudFXPlay(0x112);
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 60;
                        func_8005D2D4_main(D_80102B70_name_81[arg0->work[1]].windowId);
                        HuWinHomeClear(D_80102B70_name_81[arg0->work[1]].windowId);
                        HuWinMesSet(D_80102B70_name_81[arg0->work[1]].windowId,
                                    D_80100EE4_name_81[D_80102BAD_name_81] + D_80102BA8_name_81[arg0->work[1]] - 1,
                                    HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(D_80102B70_name_81[arg0->work[1]].windowId, 1);
                        func_8005C154_main(D_80102B70_name_81[arg0->work[1]].windowId, 0xA0, 0xA0, 0xA0);
                        HuWinBGColSet(D_80102B70_name_81[arg0->work[1]].windowId, 0xFE, 0xFF, 0xD0);
                        HuWinMesSpeedSet(D_80102B70_name_81[arg0->work[1]].windowId, 0);
                    } else {
                        arg0->scale.y = 1.0f;
                        arg0->work[2]--;
                        if (arg0->work[2] >= 0x80U) {
                            arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                D_800CC4A0_main.recentMinigames[D_80102BAD_name_81][D_800CC3E0_main[D_80102BAD_name_81]] = D_80102BA8_name_81[arg0->work[2]];
                D_800CC3E0_main[D_80102BAD_name_81]++;
                D_800CC3E0_main[D_80102BAD_name_81] = D_800CC3E0_main[D_80102BAD_name_81] % D_80100E88_name_81[D_80102BAD_name_81 + D_80102BAE_name_81];
                GWMgNoSet(D_80102BA8_name_81[arg0->work[2]]);
                if (GwSystem.current_board_index != 6 || D_80102BAD_name_81 == 1) {
                    func_800E3868_name_81();
                    func_800DF210_name_81();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }

    if (D_80102BB4_name_81 != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*D_80100EDC_name_81[i]); i++) {}

        HuSprPosSet(D_80102BB4_name_81, 0, D_80100ED0_name_81[D_80102BAD_name_81] + D_80100EDC_name_81[i][1],
                    D_80100ED8_name_81[D_80102BAD_name_81] + D_80100ED4_name_81[D_80102BAD_name_81] * arg0->work[1]);
    }
}

void func_800DE4D0_name_81(omObjData *arg0) {
    UnkC5770B70 *entry;
    s32 i;
    s32 rnd;
    s16 new_var;

    switch (arg0->work[0]) {
        case 3:
            break;
        case 0:
            if (arg0->work[1] == 0) {
                arg0->scale.y += 0.25f;
                if (arg0->scale.y > 1.0f) {
                    arg0->scale.y = 1.0f;
                }
                for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                    new_var = 0xE0;
                    entry = &D_80102B70_name_81[i];
                    HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                    HuWinScaleSet(entry->windowId, 0.0f, arg0->scale.y);
                }

                new_var = 0xE0;
                HuSprPosSet(D_80102BB0_name_81, 0, 0xA0, D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var));
                HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);
                if (arg0->scale.y >= 1.0f) {
                    arg0->work[0] = 4;
                    arg0->work[1] = 0;
                }
            } else {
                arg0->work[1] -= 1;
            }
            break;
        case 4:
            if (arg0->work[1] != 0) {
                arg0->work[1] -= 1;
                break;
            }

            arg0->scale.x += 30.0f;
            if (arg0->scale.x > 90.0f) {
                arg0->scale.x = 90.0f;
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                new_var = 0xE0;
                entry = &D_80102B70_name_81[i];
                HuWinPosSet(entry->windowId, entry->x + (entry->w / 2), entry->y + ((entry->h / 2) - new_var));
                HuWinScaleSet(entry->windowId, sindf(arg0->scale.x), arg0->scale.y);
            }

            new_var = 0xE0;
            HuSprPosSet(D_80102BB0_name_81, 0, 0xA0, D_80102B70_name_81[0].y + (D_80100ECC_name_81[D_80102BAD_name_81] - new_var));
            HuSprScaleSet(D_80102BB0_name_81, 0, sindf(arg0->scale.x), arg0->scale.y);

            if (arg0->scale.x >= 90.0f) {
                func_800DD9A0_name_81();
                arg0->work[0] = 1;
                arg0->scale.x = 1.0f;
                arg0->scale.z = -1.0f;
                arg0->scale.y = 0.0f;
                arg0->work[1] = 0;
                arg0->work[2] = func_800EFE20_name_81(D_80100E84_name_81[D_80102BAD_name_81]);
                arg0->work[3] = 0;
                func_800DF49C_name_81();
                D_80100F40_name_81 = func_800E1824_name_81(1, 0xC0, 1);
                D_80100F3C_name_81 = 0;
            }
            break;
        case 1:
            arg0->scale.z += arg0->scale.x;

            if (arg0->scale.z >= 1.0f) {
                if (arg0->work[3] != 0 && arg0->scale.x <= 0.08f) {
                    arg0->work[3]--;
                }
                arg0->scale.z -= 1.0f;
                if (arg0->scale.y >= 0.0f) {
                    arg0->work[1]++;
                    arg0->work[1] = arg0->work[1] % D_80100E84_name_81[D_80102BAD_name_81];
                } else {
                    arg0->work[1]--;
                    if (arg0->work[1] >= 0x80U) {
                        arg0->work[1] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                    }
                }
                func_800DD9A0_name_81();
            }

            for (i = 0; i < D_80100E84_name_81[D_80102BAD_name_81]; i++) {
                entry = &D_80102B70_name_81[i];
                if (i == arg0->work[1]) {
                    HuWinBGColSet(entry->windowId, 0, 0xC8, 0);
                    HuWinBGTPLvlSet(entry->windowId, 0x100);
                    HuWinPriSet(entry->windowId, 0x2328);
                } else {
                    HuWinBGColSet(entry->windowId, 0x40, 0x40, 0x80);
                    HuWinBGTPLvlSet(entry->windowId, 0);
                    HuWinPriSet(entry->windowId, 0x2710);
                }
            }

            if (D_80100F3C_name_81 == 0) {
                if (func_800F37B8_name_81(GwSystem.current_player_index) != 0) {
                    D_80100F3C_name_81 = 1;
                } else if (D_800C9520_main[GwPlayer[GwSystem.current_player_index].pad] & A_BUTTON) {
                    D_80100F3C_name_81 = 1;
                }
                break;
            }

            if (arg0->work[1] == arg0->work[2] || arg0->scale.x < 1.0f) {
                arg0->scale.x -= 0.02;
            }

            if (arg0->scale.x <= 0.08f) {
                arg0->scale.x = 0.08f;
                if (arg0->work[1] == arg0->work[2] && arg0->work[3] == 0 && arg0->scale.z + 0.08f >= 1.0f) {
                    if (arg0->scale.y != 0.0f) {
                    selected:
                        HuAudFXPlay(0x105);
                        switch (D_80102BA8_name_81[arg0->work[2]]) {
                            case 1:
                            case 6:
                                func_800FFAE0_name_81(-1, 4);
                                break;
                            case 2:
                            case 5:
                            case 7:
                            case 8:
                                func_800FFAE0_name_81(-1, 2);
                                break;
                            case 9:
                                func_800FFAE0_name_81(-1, 1);
                                break;
                            case 10:
                                func_800FFAE0_name_81(-1, 3);
                                break;
                        }

                        arg0->work[0] = 2;
                        arg0->work[3] = 60;
                        func_8005D2D4_main(D_80102B70_name_81[arg0->work[1]].windowId);
                        HuWinHomeClear(D_80102B70_name_81[arg0->work[1]].windowId);
                        HuWinMesSet(D_80102B70_name_81[arg0->work[1]].windowId,
                                    D_80100EE4_name_81[D_80102BAD_name_81] + D_80102BA8_name_81[arg0->work[1]] - 1,
                                    HUWIN_POS_CENTER, 4);
                        HuWinMesColSet(D_80102B70_name_81[arg0->work[1]].windowId, 1);
                        func_8005C154_main(D_80102B70_name_81[arg0->work[1]].windowId, 0xA0, 0xA0, 0xA0);
                        HuWinBGColSet(D_80102B70_name_81[arg0->work[1]].windowId, 0xFE, 0xFF, 0xD0);
                        HuWinMesSpeedSet(D_80102B70_name_81[arg0->work[1]].windowId, 0);
                    } else {
                        rnd = func_800EFE20_name_81(100.0f);
                        if (rnd < 15) {
                            goto selected;
                        } else if (rnd < 65) {
                            arg0->scale.y = 1.0f;
                            arg0->work[2] += 1;
                            arg0->work[2] = arg0->work[2] % D_80100E84_name_81[D_80102BAD_name_81];
                        } else if (rnd < 85) {
                            arg0->scale.y = 1.0f;
                            arg0->work[2] += 2;
                            arg0->work[2] = arg0->work[2] % D_80100E84_name_81[D_80102BAD_name_81];
                        } else if (rnd < 95) {
                            arg0->scale.y = -1.0f;
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                            }
                        } else {
                            arg0->scale.y = -1.0f;
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                            }
                            arg0->work[2]--;
                            if (arg0->work[2] >= 0x80U) {
                                arg0->work[2] = D_80100E84_name_81[D_80102BAD_name_81] - 1;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            if (arg0->work[3] != 0) {
                arg0->work[3]--;
            } else {
                D_800CC4A0_main.recentMinigames[D_80102BAD_name_81][D_800CC3E0_main[D_80102BAD_name_81]] = D_80102BA8_name_81[arg0->work[2]];
                D_800CC3E0_main[D_80102BAD_name_81]++;
                D_800CC3E0_main[D_80102BAD_name_81] = D_800CC3E0_main[D_80102BAD_name_81] % D_80100E88_name_81[D_80102BAD_name_81 + D_80102BAE_name_81];
                GWMgNoSet(D_80102BA8_name_81[arg0->work[2]]);
                if (GwSystem.current_board_index != 6 || D_80102BAD_name_81 == 1) {
                    func_800E1854_name_81(D_80100F40_name_81);
                    func_800DF210_name_81();
                }
            }
            arg0->rot.z += 1.0f;
            if (arg0->rot.z >= 13.0f) {
                arg0->rot.z -= 13.0f;
            }
            break;
    }

    if (D_80102BB4_name_81 != -1) {
        for (i = 0; !(arg0->rot.z < (f32)*D_80100EDC_name_81[i]); i++) {}

        HuSprPosSet(D_80102BB4_name_81, 0, D_80100ED0_name_81[D_80102BAD_name_81] + D_80100EDC_name_81[i][1],
                    D_80100ED8_name_81[D_80102BAD_name_81] + D_80100ED4_name_81[D_80102BAD_name_81] * arg0->work[1]);
    }
}

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

void func_800DF210_name_81(void) {
    UnkC5770B70 *entry;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80102B70_name_81); i++) {
        entry = &D_80102B70_name_81[i];
        if (entry->windowId != -1) {
            HuWinKill(entry->windowId);
            entry->windowId = -1;
        }
    }

    if (D_80102BA4_name_81 != NULL) {
        omDelObj(D_80102BA4_name_81);
        D_80102BA4_name_81 = NULL;
    }

    if (D_80102BB0_name_81 != -1) {
        HuSprGrpKill(D_80102BB0_name_81);
        D_80102BB0_name_81 = -1;
    }

    if (D_80102BB2_name_81 != -1) {
        HuSprAnimKill(D_80102BB2_name_81);
        D_80102BB2_name_81 = -1;
    }

    if (D_80102BB4_name_81 != -1) {
        HuSprGrpKill(D_80102BB4_name_81);
        D_80102BB4_name_81 = -1;
    }

    if (D_80102BB6_name_81 != -1) {
        HuSprAnimKill(D_80102BB6_name_81);
        D_80102BB6_name_81 = -1;
    }
}

void func_800DF348_name_81(void) {
    void *data;

    if (D_80102BB0_name_81 == -1) {
        D_80102BB0_name_81 = HuSprGrpCreate(1, 0);
        if (D_80102BAD_name_81 == 1) {
            data = DataRead(0x130106);
        } else {
            data = DataRead(0x130116);
        }
        D_80102BB2_name_81 = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80102BB0_name_81, 0, D_80102BB2_name_81, 0);
        HuSprPriSet(D_80102BB0_name_81, 0, 0x4770);
        HuSprAttrSet(D_80102BB0_name_81, 0, 0x1000);
        HuSprPosSet(D_80102BB0_name_81, 0, 0xA0, D_80100ECC_name_81[D_80102BAD_name_81] + D_80102B70_name_81[0].y);
        if (D_80102BAD_name_81 != 1) {
            HuSprColorSet(D_80102BB0_name_81, 0, 0xD7, 0x3D, 0xBE);
        } else {
            HuSprColorSet(D_80102BB0_name_81, 0, 0, 0x64, 0);
        }
    }
}

void func_800DF49C_name_81(void) {
    s32 files[2] = { 0x130210, 0x130105 };
    void *data;

    if (D_80102BB4_name_81 == -1) {
        D_80102BB4_name_81 = HuSprGrpCreate(1, 4);
        data = DataRead(files[D_80102BAD_name_81]);
        D_80102BB6_name_81 = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(D_80102BB4_name_81, 0, D_80102BB6_name_81, 0);
        HuSprPriSet(D_80102BB4_name_81, 0, 0x100);
        HuSprAttrSet(D_80102BB4_name_81, 0, 0);
        HuSprPosSet(D_80102BB4_name_81, 0, D_80100ED0_name_81[D_80102BAD_name_81], 0x9A);
    }
}

void func_800DF594_name_81(s32 arg0) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    UnkC5770Rect *rects[2] = { D_80100E8C_name_81, D_80100EB4_name_81 };
    u8 *mgLists[4] = { D_80100E50_name_81, D_80100E64_name_81, D_80100E5C_name_81, D_80100E64_name_81 };
    u8 mgCounts[4] = { 10, 30, 7, 30 };
    s32 winStyles[2] = { 5, 20 };
    UnkC5770B70 *entry;
    omObjData *obj;
    s32 listOffset;
    s32 i;
    s32 j;
    s32 k;
    s32 type;

    type = arg0; // A separate copy of arg0 is needed for regalloc.
    D_80102BAD_name_81 = type;
    listOffset = (_CheckFlag(0x20) != 0) * 2;
    D_80102BAE_name_81 = listOffset;

    for (i = 0; i < D_80100E84_name_81[type]; i++) {
        entry = &D_80102B70_name_81[i];
        entry->x = rects[type][i].x;
        entry->y = rects[type][i].y;
        entry->w = rects[type][i].w;
        entry->h = rects[type][i].h;

        entry->windowId = HuWinCreate(entry->x + (entry->w / 2), entry->y + (entry->h / 2), entry->w, entry->h, 0, winStyles[type]);
        HuWinPriSet(entry->windowId, 0x2328);
        func_80060144_main(entry->windowId);
        HuWinCenterPosSet(entry->windowId, entry->w / 2, entry->h / 2);
        HuWinBGTPLvlSet(entry->windowId, 0);

        while (1) {
            D_80102BA8_name_81[i] = mgLists[type + listOffset][func_800EFE20_name_81(mgCounts[type + listOffset])];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (D_80102BA8_name_81[j] == D_80102BA8_name_81[i]) {
                    break;
                }
            }
            if (j != i) {
                continue;
            }

            if (type != 1) {
                for (k = 0; k < D_80100E88_name_81[type + listOffset]; k++) {
                    if (D_80102BA8_name_81[i] == D_800CC4A0_main.recentMinigames[type][k]) {
                        break;
                    }
                }
                if (k != D_80100E88_name_81[type + listOffset]) {
                    continue;
                }
            } else {
                switch (D_80102BA8_name_81[i]) {
                    case 1:
                        if (player->star == 5) {
                            continue;
                        }
                        break;
                    case 2:
                        if (GwPlayer[0].clink == GwPlayer[1].clink && GwPlayer[0].cidx == GwPlayer[1].cidx) {
                            continue;
                        }
                        break;
                    case 3:
                        if (GwPlayer[GwSystem.current_player_index].coin == 0) {
                            continue;
                        }
                        break;
                    case 7:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 8:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 1) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 1) {
                            continue;
                        }
                        /* fallthrough */
                    case 9:
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 10:
                        if (func_800EAA7C_name_81(GwPlayer[GwSystem.current_player_index].chr + 11) != 0) {
                            break;
                        }
                        /* fallthrough */
                    case 6:
                        if (func_800EAA7C_name_81(GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr + 11) == 0) {
                            continue;
                        }
                        break;
                }
            }

            func_8005D2D4_main(entry->windowId);

            if (D_80102BAD_name_81 != 1 && GWMgUnlockCheck(D_80102BA8_name_81[i] - 1) == FALSE) {
                HuWinMesSet(entry->windowId, 0x4748, HUWIN_POS_CENTER, 4);
            } else {
                do { // Needed for regalloc.
                    HuWinMesSet(entry->windowId, D_80100EE4_name_81[type] + D_80102BA8_name_81[i] - 1, HUWIN_POS_CENTER, 4);
                } while (0);
            }

            HuWinMesColSet(entry->windowId, D_80100EEC_name_81[D_80102BA8_name_81[i] - 1]);
            HuWinMesSpeedSet(entry->windowId, 0);
            break;
        }
    }

    if (D_80102BAD_name_81 != 1) {
        obj = omAddObj(-0x8000, 0, 0, -1, func_800DD9EC_name_81);
        D_80102BA4_name_81 = obj;
        obj->work[1] = 5;
    } else {
        obj = omAddObj(-0x8000, 0, 0, -1, func_800DE4D0_name_81);
        D_80102BA4_name_81 = obj;
        obj->work[1] = 0;
    }
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    func_800DF348_name_81();
}

void func_800DFBF4_name_81(void) {
    GW_PLAYER *player = MBDGetPlayerStruct(CUR_PLAYER);
    UnkC5770Rect *rects[2] = { D_80100E8C_name_81, D_80100EB4_name_81 };
    u8 *mgLists[4] = { D_80100E50_name_81, D_80100E64_name_81, D_80100E5C_name_81, D_80100E64_name_81 };
    u8 mgCounts[4] = { 10, 30, 7, 30 };
    s32 winStyles[2] = { 5, 20 };
    UnkC5770B70 *entry;
    omObjData *obj;
    s32 listOffset;
    s32 i;
    s32 j;
    s32 k;
    s32 arg0;

    arg0 = D_80102BB8_name_81;
    D_80102BAD_name_81 = arg0;
    listOffset = (_CheckFlag(0x20) != 0) * 2;
    D_80102BAE_name_81 = listOffset;
    if (D_80100F44_name_81 != NULL) {
        Hu3DMotionSpeedSet(D_80100F44_name_81->omObj1->model[0], 2.0f);
    }

    for (i = 0; i < D_80100E84_name_81[arg0]; i++) {
        entry = &D_80102B70_name_81[i];
        entry->x = rects[arg0][i].x;
        entry->y = rects[arg0][i].y;
        entry->w = rects[arg0][i].w;
        entry->h = rects[arg0][i].h;

        entry->windowId = HuWinCreate(entry->x + (entry->w / 2), entry->y + (entry->h / 2), entry->w, entry->h, 0, winStyles[arg0]);
        HuWinPriSet(entry->windowId, 0x2328);
        func_80060144_main(entry->windowId);
        HuWinCenterPosSet(entry->windowId, entry->w / 2, entry->h / 2);
        HuWinBGTPLvlSet(entry->windowId, 0);
        HuPrcVSleep();

        while (1) {
            D_80102BA8_name_81[i] = mgLists[arg0 + listOffset][func_800EFE20_name_81(mgCounts[arg0 + listOffset])];

            for (j = 0; j < i; j++) {
                if (j == i) {
                    continue;
                }
                if (D_80102BA8_name_81[j] == D_80102BA8_name_81[i]) {
                    break;
                }
            }
            if (j != i) {
                continue;
            }

            if (arg0 != 1) {
                for (k = 0; k < D_80100E88_name_81[arg0 + listOffset]; k++) {
                    if (D_80102BA8_name_81[i] == D_800CC4A0_main.recentMinigames[arg0][k]) {
                        break;
                    }
                }
                if (k != D_80100E88_name_81[arg0 + listOffset]) {
                    continue;
                }
            } else {
                switch (D_80102BA8_name_81[i]) {
                    case 1:
                        if (player->star == 5) {
                            continue;
                        }
                        break;
                    case 2:
                        if (GwPlayer[0].clink == GwPlayer[1].clink && GwPlayer[0].cidx == GwPlayer[1].cidx) {
                            continue;
                        }
                        break;
                    case 3:
                        if (GwPlayer[GwSystem.current_player_index].coin == 0) {
                            continue;
                        }
                        break;
                    case 7:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 2) {
                            continue;
                        }
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 8:
                        if (player->stats.partners.frontID != -1 && player->stats.partners.frontPoweredUp == 1) {
                            continue;
                        }
                        if (player->stats.partners.backID != -1 && player->stats.partners.backPoweredUp == 1) {
                            continue;
                        }
                        /* fallthrough */
                    case 9:
                        if (player->stats.partners.frontID == -1 && player->stats.partners.backID == -1) {
                            continue;
                        }
                        break;
                    case 10:
                        if (func_800EAA7C_name_81(GwPlayer[GwSystem.current_player_index].chr + 11) != 0) {
                            break;
                        }
                        /* fallthrough */
                    case 6:
                        if (func_800EAA7C_name_81(GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr + 11) == 0) {
                            continue;
                        }
                        break;
                }
            }

            func_8005D2D4_main(entry->windowId);

            if (D_80102BAD_name_81 != 1 && GWMgUnlockCheck(D_80102BA8_name_81[i] - 1) == FALSE) {
                HuWinMesSet(entry->windowId, 0x4748, HUWIN_POS_CENTER, 4);
            } else {
                do { // Needed for regalloc.
                    HuWinMesSet(entry->windowId, D_80100EE4_name_81[arg0] + D_80102BA8_name_81[i] - 1, HUWIN_POS_CENTER, 4);
                } while (0);
            }

            HuWinMesColSet(entry->windowId, D_80100EEC_name_81[D_80102BA8_name_81[i] - 1]);
            HuWinMesSpeedSet(entry->windowId, 0);
            break;
        }
        HuPrcVSleep();
    }

    if (D_80102BAD_name_81 != 1) {
        obj = omAddObj(-0x8000, 0, 0, -1, func_800DD9EC_name_81);
        D_80102BA4_name_81 = obj;
        obj->work[1] = 5;
    } else {
        obj = omAddObj(-0x8000, 0, 0, -1, func_800DE4D0_name_81);
        D_80102BA4_name_81 = obj;
        obj->work[1] = 0;
    }
    obj->work[0] = 3;
    obj->trans.y = 0.0f;
    obj->rot.z = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    func_800DF348_name_81();
    if (D_80100F44_name_81 != NULL) {
        Hu3DMotionSpeedSet(D_80100F44_name_81->omObj1->model[0], 1.0f);
    }
    omDelPrcObj(NULL);
}

void func_800E02B4_name_81(s32 arg0) {
    D_80102BB8_name_81 = arg0;
    if (arg0 != 1) {
        omAddPrcObj(func_800DFBF4_name_81, 0, 0, 0);
    } else {
        func_800DF594_name_81(arg0);
    }
}

void func_800E0300_name_81(void) {
    D_80102BA4_name_81->work[0] = 0;
}

void func_800E0310_name_81(u8 *output, s32 count) {
    s8 pool[256];
    s32 i;
    s32 j;
    s32 randIndex;

    for (i = 0; i <= count; i++) {
        pool[i] = i;
    }

    for (i = 0; i <= count; i++) {
        randIndex = func_800EFE20_name_81(count - i + 1);
        output[i] = pool[randIndex];

        for (j = randIndex; j < count; j++) {
            pool[j] = pool[j + 1];
        }
    }
}

void func_800E03F0_name_81(void) {
    Process *process = HuPrcCurrentGet();
    s32 waitTime = 0;
    Object *spinObj = func_800EED24_name_81();
    f32 angle = 360.0f;
    s32 spinning = 0;
    s32 growing = 0;
    s32 hideTimer = 0;
    f32 scale = 0.0f;
    Object *obj;
    UnkC5770 *work;
    HmfModel *model;
    f32 zero;
    s32 i;

    obj = MBDModelFileCreate(0x130204, -1, 1.4f, scale, NULL);
    func_8001C258_main(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    MBDModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &spinObj->coords);
    HuVecCopyXYZ(&obj->scale, scale, 1.0f, 1.0f);
    obj->coords.y += 38.0f;
    work = process->user_data;

    while (TRUE) {
        if (spinning) {
            sincosdf(angle, &Hu3DData[spinObj->omObj1->model[0]].mtx[2][0], &Hu3DData[spinObj->omObj1->model[0]].mtx[2][2]);
            Hu3DData[spinObj->omObj1->model[0]].mtx[0][2] = -Hu3DData[spinObj->omObj1->model[0]].mtx[2][0];

            model = &Hu3DData[spinObj->omObj1->model[0]];
            model->mtx[0][0] = model->mtx[2][2];

            model = &Hu3DData[spinObj->omObj1->model[0]];
            zero = 0.0f;
            model->mtx[3][2] = zero;
            model->mtx[3][1] = zero;
            model->mtx[3][0] = zero;
            model->mtx[2][3] = zero;
            model->mtx[2][1] = zero;
            model->mtx[1][3] = zero;
            model->mtx[1][2] = zero;
            model->mtx[1][0] = zero;
            model->mtx[0][3] = zero;
            model->mtx[0][1] = zero;

            model = &Hu3DData[spinObj->omObj1->model[0]];
            model->mtx[3][3] = 1.0f;
            model->mtx[1][1] = 1.0f;

            if (angle > 0.0f) {
                angle -= 30.0f;
                if (angle <= 270.0f) {
                    growing = 1;
                }
            } else if (++hideTimer >= 2) {
                MBDModelDispOff(spinObj);
            }

            if (growing == 1) {
                HuVecCopyXYZ(&obj->scale, scale, 1.0f, 1.0f);
                scale += 0.12f;
                if (scale > 1.0f) {
                    scale = 1.0f;
                }
            }
        }

        switch (work->state) {
            case 0:
                work->state = 1;
                break;
            case 1:
                HuPrcSleep(1);
                func_800E363C_name_81(0, &obj->coords);
                HuPrcSleep(15);
                work->state++;
                break;
            case 2:
                func_800F66BC_name_81(2);
                func_800F6CEC_name_81();
                work->state++;
                waitTime = 0;
                break;
            case 3:
                if (++waitTime >= 5 && !spinning) {
                    spinning = 1;
                    HuAudFXPlay(0x206);
                }
                if (func_800F6CA0_name_81() == 0) {
                    for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                            break;
                        }
                    }

                    if (i != MBD_MAX_PLAYERS) {
                        for (i = 0; i < MBD_MAX_PLAYERS; i++) {
                            if ((D_800D5558_main[GwPlayer[i].pad] & A_BUTTON) && !(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                                break;
                            }
                        }
                        if (i == MBD_MAX_PLAYERS) {
                            break;
                        }
                    }
                    func_800E0300_name_81();
                    func_800F66BC_name_81(5);
                    work->state++;
                }
                break;
            case 4:
                if (func_800E3858_name_81() == 0) {
                    func_800F6F84_name_81();
                    MBDModelKill(obj);
                    omDelPrcObj(NULL);
                }
                break;
        }

        HuPrcVSleep();
    }
}

Process *func_800E0888_name_81(void) {
    Process *process = omAddPrcObj(func_800E03F0_name_81, 0, 0x2000, 0x40);
    UnkC5770 *work = HuMemMemoryAlloc(process->heap, sizeof(UnkC5770));

    process->user_data = work;
    work->state = 0;
    return process;
}

void func_800E08D8_name_81(void) {
    func_800E02B4_name_81(1);
    HuPrcVSleep();
    func_800E0300_name_81();
    do {
        HuPrcVSleep();
    } while (D_80102BA4_name_81 != NULL);
    omDelPrcObj(NULL);
}

void func_800E0924_name_81(void) {
    omAddPrcObj(func_800E08D8_name_81, 0, 0x2000, 0);
}

void func_800E0950_name_81(omObjData *arg0) {
    Vec pos;
    Vec2f screenPos;
    s32 i;

    switch (D_80102BD4_name_81) {
        case 1:
            pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
            pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + 30.0f;
            pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
            MBDCamera3Dto2D(&pos, &screenPos);
            break;
        case 0:
            screenPos.x = D_80100F50_name_81[arg0->work[3]][0];
            screenPos.y = D_80100F50_name_81[arg0->work[3]][1];
            break;
        default:
            screenPos.x = D_80102BD8_name_81[arg0->work[3]][0];
            screenPos.y = D_80102BD8_name_81[arg0->work[3]][1];
            break;
    }

    if (arg0->work[0] < 10) {
        if (arg0->rot.x > 0.0f) {
            arg0->trans.y -= 1.5f;
        } else {
            arg0->trans.y += 1.5f;
        }
        HuSprPosSet(D_80102BC0_name_81[arg0->work[3]], 0, screenPos.x, (screenPos.y + arg0->trans.y));
    } else if (arg0->work[0] >= 0x18U) {
        arg0->scale.x += 0.4f;
        arg0->scale.y -= 0.3f;

        if (arg0->scale.x < 0.0f) {
            arg0->scale.x = 0.0f;
        }
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(D_80102BC0_name_81[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    } else if (arg0->work[0] >= 22) {
        arg0->scale.y -= 0.3f;
        if (arg0->scale.y < 0.0f) {
            arg0->scale.y = 0.0f;
        }

        for (i = 1; i < arg0->work[1]; i++) {
            HuSprScaleSet(D_80102BC0_name_81[arg0->work[3]], i, arg0->scale.x, arg0->scale.y);
        }
    }

    if (arg0->work[0] >= 30) {
        func_800E0D64_name_81(arg0->work[3]);
        return;
    }

    arg0->work[0]++;
}

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

void func_800E0D64_name_81(s32 arg0) {
    s32 i;

    if (D_80102BC0_name_81[arg0] != -1) {
        HuSprGrpKill(D_80102BC0_name_81[arg0]);
        D_80102BC0_name_81[arg0] = -1;
    }
    if (D_80102BCC_name_81[arg0] != NULL) {
        omDelObj(D_80102BCC_name_81[arg0]);
        D_80102BCC_name_81[arg0] = NULL;
    }

    for (i = 0; i < 2; i++) {
        if (D_80102BC4_name_81[arg0][i] != -1) {
            HuSprAnimKill(D_80102BC4_name_81[arg0][i]);
            D_80102BC4_name_81[arg0][i] = -1;
        }
    }
}

void func_800E0E38_name_81(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800E0D64_name_81(i);
    }
}

void func_800E0E70_name_81(s32 arg0, s32 coins, s32 arg2, s32 arg3) {
    Vec pos;
    Vec2f screenPos;
    s16 grp;
    s32 x;
    s32 count;
    void *data;
    s32 i;

    if (D_80102BC0_name_81[arg0] == -1) {
        if (coins < -999) {
            coins = -999;
        }
        if (coins > 999) {
            coins = 999;
        }
        if (coins == 0) {
            HuAudFXPlay(0x203);
        }
        D_80102BCC_name_81[arg0] = omAddObj(-0x8000, 0, 0, -1, func_800E0950_name_81);
        D_80102BCC_name_81[arg0]->work[0] = 0;
        D_80102BCC_name_81[arg0]->rot.x = coins;
        D_80102BCC_name_81[arg0]->trans.y = 0.0f;
        D_80102BCC_name_81[arg0]->scale.x = 1.0f;
        D_80102BCC_name_81[arg0]->scale.y = 2.0f;
        D_80102BCC_name_81[arg0]->work[3] = arg0;
        D_80102BCC_name_81[arg0]->work[1] = 6;
        D_80102BC0_name_81[arg0] = grp = HuSprGrpCreate(6, 5);
        data = DataRead(0x130112);
        D_80102BC4_name_81[arg0][0] = HuSprAnimRead(data);
        DataClose(data);

        if (coins > 0) {
            data = DataRead(0x130213);
        } else {
            data = DataRead(0x130214);
        }

        D_80102BC4_name_81[arg0][1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(grp, 1, D_80102BC4_name_81[arg0][0], 0);
        HuSprPriSet(grp, 1, 0x2010);
        HuSprAttrSet(grp, 1, 0x1000);

        count = 2;
        HuSprGrpMemberSet(grp, 2, D_80102BC4_name_81[arg0][1], 0);
        HuSprAnimModeSet(grp, 2, HUSPR_ANIM_MODE_BANK);

        if (coins > 0) {
            HuSprBankSet(grp, count, 10, 0);
        } else {
            HuSprBankSet(grp, count, 11, 0);
        }

        HuSprPriSet(grp, count, 0x2010);
        HuSprAttrSet(grp, count, 0x1000);

        count++;
        coins = (coins < 0) ? -coins : coins;

        if (coins >= 100) {
            HuSprGrpMemberSet(grp, count, D_80102BC4_name_81[arg0][1], 0);
            HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(grp, count, coins / 100, 0);
            HuSprPriSet(grp, count, 0x2010);
            HuSprAttrSet(grp, count, 0x1000);
            count++;
        }

        if (coins >= 10) {
            HuSprGrpMemberSet(grp, count, D_80102BC4_name_81[arg0][1], 0);
            HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(grp, count, (coins / 10) % 10, 0);
            HuSprPriSet(grp, count, 0x2010);
            HuSprAttrSet(grp, count, 0x1000);
            count++;
        }

        coins = coins % 10;

        HuSprGrpMemberSet(grp, count, D_80102BC4_name_81[arg0][1], 0);
        HuSprAnimModeSet(grp, count, HUSPR_ANIM_MODE_BANK);
        HuSprBankSet(grp, count, coins, 0);
        HuSprPriSet(grp, count, 0x2010);
        HuSprAttrSet(grp, count, 0x1000);
        count++;

        if (arg2 == -1 && arg3 == -1) {
            if (D_80102BD4_name_81 != 0) {
                pos.x = GwPlayer[arg0].player_obj->coords.x;
                pos.y = GwPlayer[arg0].player_obj->coords.y + 30.0f;
                pos.z = GwPlayer[arg0].player_obj->coords.z;
                MBDCamera3Dto2D(&pos, &screenPos);
                HuSprPosSet(grp, 0, screenPos.x, screenPos.y);
            } else {
                HuSprPosSet(grp, 0, D_80100F50_name_81[arg0][0], D_80100F50_name_81[arg0][1]);
            }
        } else {
            HuSprPosSet(grp, 0, arg2, arg3);
        }

        x = count - 2;
        x = -(x * 8);

        for (i = 1; i < count; i++) {
            HuSprPosSet(grp, i, x, 0);
            x += 16;
        }

        for (; count < 6; count++) {
            HuSprDispOff(grp, count);
        }
    }
}

void func_800E14B0_name_81(s32 arg0, s32 arg1) {
    D_80102BD4_name_81 = 0;
    func_800E0E70_name_81(arg0, arg1, -1, -1);
}

void func_800E14D8_name_81(s32 arg0, s32 arg1) {
    D_80102BD4_name_81 = 1;
    func_800E0E70_name_81(arg0, arg1, -1, -1);
}

void func_800E1504_name_81(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_80102BD4_name_81 = 2;
    D_80102BD8_name_81[arg0][0] = arg2;
    D_80102BD8_name_81[arg0][1] = arg3;
    func_800E0E70_name_81(arg0, arg1, arg2, arg3);
}
