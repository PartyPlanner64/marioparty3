#include "common.h"
#include "inst.h"

extern InstMessageInfo D_800A6D40_main[];
extern u16 D_800CC698_main;
extern omObjData *D_8010DCA0_inst;
extern s32 D_8010D5B4_inst;
extern s32 D_8010D5B8_inst;
extern s16 D_8010D5BA_inst;
extern u16 D_8010DCC0_inst[2];
extern u16 D_8010DCC4_inst[3];
extern s8 D_8010D411_inst;
extern s8 D_8010D40B_inst;
extern s8 D_8010D5B1_inst;
extern s8 D_8010DCD4_inst;
extern s32 D_8010DCCC_inst;
extern InstMessageInfo *D_8010DCD0_inst;
extern s8 D_8010D400_inst[4];
extern s8 D_8010D406_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst;
extern s32 D_8010D440_inst;
extern s8 D_8010D5B0_inst;
extern void (*D_8010DCA4_inst)(s32);
extern UnkInstWin D_8010DCA8_inst;
extern GAMEMES D_8010DCD8_inst;
extern GAMEMES D_8010DD50_inst;

const InstSpritePos D_8010DAF8_inst[3] = {{0, 95}, {0, 105}, {0, 115}};
const s16 D_8010DB04_inst[2][3] = {
    {0x3900, 0x3901, 0x3902},
    {0x3908, 0x3909, 0x390A},
};
const s16 D_8010DB10_inst[2][3] = {
    {0x3910, 0x3912, 0x3914},
    {0x390C, 0x390D, 0x390E},
};
const s16 D_8010DB1C_inst[] = {0x3904, 0x3905, 0x3906, 0x0000};
const s16 D_8010DB24_inst[2][3] = {
    {0x3803, 0x3804, 0x3805},
    {0x380A, 0x380B, 0x380C},
};
const s16 D_8010DB30_inst[] = {0x3811, 0x3812, 0x3813, 0x0000};

s16 GameMesStrCreate(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4);

void espAttrSet(u16 arg0, u16 arg1);
void espTPLvlSet(u16 spriteId, s16 arg1);
void espBankSet(u16, s32, s32);
void func_8010CDE4_inst(const char *, s32, s32);
void func_8010CF14_inst(void);
void func_8010CFF4_inst(void);
void func_8010CC14_inst(void);
void func_8010C8B4_inst(void);
void func_8010BE28_inst(void);

void func_8010C124_inst(s32);
void func_8010C5C4_inst(s32 arg0);
void func_8010CBB8_inst(s32);
void func_8010D1D4_inst(void);
u16 func_8010C8E0_inst(s32);
void func_8010D044_inst(void);
void func_8010CED0_inst(s32, s32);
void func_80060DEC_main(s32 win_id);
void func_8010BE78_inst(s32 arg0); /* extern */

void func_8010B990_inst(void) {
    s32 digits[3];
    s32 i;
    s32 score;
    s32 sprite;
    s16 slot;
    omObjData *object;
    const InstSpritePos *positions;
    u16 *sprites;

    object = omAddObj(20, 5, 0, -1, NULL);
    D_8010DCA0_inst = object;
    D_8010DCD0_inst = &D_800A6D40_main[D_8010D40B_inst];
    D_8010DCC0_inst[0] = espEntry(func_8000B838_main(0x170008), 0, 1);
    espAttrSet(D_8010DCC0_inst[0], 0x1000);
    espTPLvlSet(D_8010DCC0_inst[0], 255);
    espPosSet(D_8010DCC0_inst[0], 160, -100);
    func_8010CDE4_inst((const char *)(D_8010D40B_inst + 0x4700), 160, -100);
    func_8010CF14_inst();
    func_8010CFF4_inst();
    if (D_8010D40A_inst == 3) {
        D_8010DCC0_inst[1] = espEntry(func_8000B838_main(0x17000E), 0, 1);
        espAttrSet(D_8010DCC0_inst[1], 0x1000);
        espTPLvlSet(D_8010DCC0_inst[1], 255);
        espPosSet(D_8010DCC0_inst[1], 160, -78);
        score = D_800CC698_main;
        sprite = func_8000B838_main(0x1300CF);
        if (score >= 1000) {
            score = 999;
        } else if (score < 0) {
            score = 0;
        }
        digits[0] = score / 100 % 10;
        digits[1] = score / 10 - score / 100 * 10;
        digits[2] = score % 10;
        for (i = 0; i < 3; i++) {
            slot = espEntry(sprite, 0, 0);
            sprites = D_8010DCC4_inst;
            sprites[i] = slot;
            positions = D_8010DAF8_inst;
            espPosSet(sprites[i], positions[i].x, -78);
            espBankSet(sprites[i], (u16)digits[i], 0);
        }
    }
    D_8010DCA8_inst.curGroup = func_80060880_main(72, 188, 7);
    HuWinMesPalSet(D_8010DCA8_inst.curGroup, 2, 0, 255, 255);
    HuWinMesPalSet(D_8010DCA8_inst.curGroup, 4, 96, 255, 64);
    HuWinMesPalSet(D_8010DCA8_inst.curGroup, 6, 255, 255, 64);
    HuWinGet(D_8010DCA8_inst.curGroup)->spacing_x = 1;
    func_8010CC14_inst();
    D_8010DCA8_inst.mainMembers[0] = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x17000B, 60, -33, 0);
    D_8010DCA8_inst.mainMembers[1] = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x170009, 148, -33, 0);
    D_8010DCA8_inst.mainMembers[2] = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x17000A, 200, -33, 0);
    D_8010DCA8_inst.helpMembers[0] = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x17000D, 60, -33, 0);
    D_8010DCA8_inst.helpMembers[1] = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x17000F, 200, -33, 0);
    D_8010DCA8_inst.member = HuWinAnimSet(D_8010DCA8_inst.curGroup, 0x17000C, 38, -33, 0);
    D_8010DCD4_inst = 0;
    D_8010DCCC_inst = D_8010DCD0_inst->message;
    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
        D_8010DCCC_inst++;
    }
    HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
    omPrcSetDestructor(NULL, func_8010C8B4_inst);
    D_8010DCA4_inst = (void (*)(s32))func_8010BE28_inst;
    while (1) {
        D_8010DCA4_inst((s32)object);
        HuPrcVSleep();
    }
}

void func_8010BE28_inst(void) {
    if (D_8010D408_inst == 1) {
        D_8010D5B0_inst = 1;
    }
    if (D_8010D5B0_inst == 1) {
        D_8010DCA4_inst = func_8010BE78_inst;
    }
}

void func_8010BE70_inst(s32 arg0) {
}

void func_8010BE78_inst(s32 arg0) {
    s32 i;
    s32 value;
    s16 *y;
    u16 *sprites;
    const InstSpritePos *positions;

    if (D_8010D408_inst == 0) {
        espPosSet(D_8010DCC0_inst[0], 160, *(y = &D_8010D5BA_inst));
        func_8010CED0_inst(160, *y);
        value = D_8010D40A_inst;
        if (value == 3) {
            espPosSet(D_8010DCC0_inst[1], 160, *y + 22);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, D_8010D5BA_inst + 22);
            }
        }
        D_8010D5B4_inst++;
        D_8010D5B8_inst = sindf(D_8010D5B4_inst * 6) * 96.0f + -64.0f;
        if (D_8010D5B4_inst < 15) {
            return;
        }
        D_8010D5B4_inst = 0;
        D_8010D5B8_inst = -64;
        espPosSet(D_8010DCC0_inst[0], 160, 32);
        func_8010CED0_inst(160, 32);
        value = D_8010D40A_inst;
        if (value == 3) {
            espPosSet(D_8010DCC0_inst[1], 160, 54);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, 54);
            }
        }
    } else {
        espPosSet(D_8010DCC0_inst[0], 160, 32);
        func_8010CED0_inst(160, 32);
        value = D_8010D40A_inst;
        if (value == 3) {
            espPosSet(D_8010DCC0_inst[1], 160, 54);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                espPosSet(sprites[i], positions[i].x, 54);
            }
        }
        func_80060DEC_main(D_8010DCA8_inst.curGroup);
        value = 1;
        D_8010D440_inst = value;
    }
    func_8010D044_inst();
    D_8010DCA4_inst = func_8010C124_inst;
}

void func_8010C124_inst(s32 arg0) {
    if (D_8010D409_inst == 1) {
        return;
    }
    if (func_8010C8E0_inst(0x10) != 0) {
        func_8010D1D4_inst();
        D_8010DCA4_inst = func_8010C5C4_inst;
        return;
    }
    switch (D_8010DCD4_inst) {
        case 0:
            if (func_8010C8E0_inst(1) != 0) {
                D_8010DCCC_inst = D_8010DCD0_inst->unk_0A[0];
                if (D_8010DCD0_inst->unk_0A[1] < 0) {
                    func_8010CBB8_inst(1);
                    D_8010DCD4_inst = 1;
                } else {
                    func_8010CBB8_inst(3);
                    D_8010DCD4_inst = 3;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
            }
            break;
        case 1:
            if (func_8010C8E0_inst(1) != 0) {
                D_8010DCCC_inst = D_8010DCD0_inst->finalMessage;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst++;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
                func_8010CBB8_inst(2);
                D_8010DCD4_inst = 2;
            }
            break;
        case 3:
            if (func_8010C8E0_inst(1) != 0) {
                if (D_8010DCD0_inst->unk_0A[1] < 0) {
                    D_8010DCCC_inst = D_8010DCD0_inst->finalMessage;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst++;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->unk_0A[1];
                    func_8010CBB8_inst(4);
                    D_8010DCD4_inst = 4;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
            }
            break;
        case 4:
            if (func_8010C8E0_inst(1) != 0) {
                if (D_8010DCD0_inst->unk_0A[2] < 0) {
                    D_8010DCCC_inst = D_8010DCD0_inst->finalMessage;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst++;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->unk_0A[2];
                    func_8010CBB8_inst(6);
                    D_8010DCD4_inst = 6;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
            }
            break;
        case 6:
            if (func_8010C8E0_inst(1) != 0) {
                if (D_8010DCD0_inst->unk_0A[3] < 0) {
                    D_8010DCCC_inst = D_8010DCD0_inst->finalMessage;
                    if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                        D_8010DCCC_inst++;
                    }
                    func_8010CBB8_inst(2);
                    D_8010DCD4_inst = 2;
                } else {
                    D_8010DCCC_inst = D_8010DCD0_inst->unk_0A[3];
                    func_8010CBB8_inst(7);
                    D_8010DCD4_inst = 7;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
            }
            break;
        case 7:
            if (func_8010C8E0_inst(1) != 0) {
                D_8010DCCC_inst = D_8010DCD0_inst->finalMessage;
                func_8010CBB8_inst(2);
                D_8010DCD4_inst = 2;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst++;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
            }
            break;
        case 2:
            if (func_8010C8E0_inst(1) != 0) {
                D_8010DCCC_inst = D_8010DCD0_inst->message;
                if (D_8010D40A_inst == 4 && D_8010D411_inst != 2) {
                    D_8010DCCC_inst++;
                }
                HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
                func_8010CBB8_inst(0);
                D_8010DCD4_inst = 0;
            }
            break;
    }
}

s32 func_8010C55C_inst(void) {
    s32 changed = 0;

    if ((func_8010C8E0_inst(0x10) != 0) && (D_8010D409_inst != 1)) {
        changed = 1;
        func_8010D044_inst();
        D_8010DCA4_inst = func_8010C124_inst;
    }
    HuPrcVSleep();
    return changed;
}

void func_8010C5C4_inst(s32 arg0) {
    s8 i;
    s32 message;

    if (D_8010D409_inst != 1) {
        for (i = 0; i < 3; i++) {
            switch (D_8010D40B_inst) {
                case 8:
                case 16:
                case 27:
                    message = D_8010DB1C_inst[i];
                    break;
                default:
                    switch (D_8010D40A_inst) {
                        case 5:
                            message = D_8010DB04_inst[1][i];
                            break;
                        case 4:
                            message = D_8010DB10_inst[0][i];
                            message += D_8010D411_inst != 2;
                            break;
                        case 3:
                            message = D_8010DB10_inst[1][i];
                            break;
                        case 7:
                            if (D_8010D40B_inst == 70) {
                                message = D_8010DB24_inst[1][i];
                            } else {
                                message = D_8010DB30_inst[i];
                            }
                            break;
                        case 8:
                            message = D_8010DB24_inst[0][i];
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 6:
                        default:
                            message = D_8010DB04_inst[0][i];
                            break;
                    }
                    break;
            }
            HuWinMesSet(D_8010DCA8_inst.curGroup, message, -1, -1);
            while (HuWinStatGet(D_8010DCA8_inst.curGroup) != 0) {
                if (func_8010C55C_inst() != 0) {
                    return;
                }
            }
        }
        message = D_8010DCD0_inst->finalMessage;
        if (D_8010D40A_inst == 4) {
            message += D_8010D411_inst != 2;
        }
        HuWinMesSet(D_8010DCA8_inst.curGroup, message, -1, -1);
        while (HuWinStatGet(D_8010DCA8_inst.curGroup) != 0) {
            if (func_8010C55C_inst() != 0) {
                return;
            }
        }
        while (func_8010C8E0_inst(0x8000) == 0) {
            if (func_8010C55C_inst() != 0) {
                return;
            }
        }
        D_8010D406_inst = 1;
        D_8010DCA4_inst = func_8010BE70_inst;
    }
}

void func_8010C848_inst(void) {
    if (D_8010D408_inst == 0) {
        HuAudFXPlay(0x11D);
        func_80060C14_main(D_8010DCA8_inst.curGroup, 0);
        D_8010D440_inst = 1;
    }
}

void func_8010C890_inst(void) {
    func_80060EA8_main(D_8010DCA8_inst.curGroup, 1);
}

void func_8010C8B4_inst(void) {
    GMesClose();
}

void func_8010C8D0_inst(void) {
    D_8010D5B0_inst = 1;
}

u16 func_8010C8E0_inst(s32 buttons) {
    u16 pressed = 0;
    s8 i;

    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            if (!(GwPlayer[D_8010D400_inst[0]].stat & 1)) {
                pressed = D_800D5558_main[GwPlayer[D_8010D400_inst[0]].pad] & buttons;
            }
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    pressed = D_800D5558_main[GwPlayer[D_8010D400_inst[i]].pad] & buttons;
                    if (pressed != 0) {
                        break;
                    }
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    pressed = D_800D5558_main[GwPlayer[D_8010D400_inst[i]].pad] & buttons;
                    if (pressed != 0) {
                        break;
                    }
                }
            }
            break;
    }
    return pressed;
}

u16 func_8010CA74_inst(u16 buttons, s16 wait) {
    s32 cpu = 0;
    u16 pressed = 0;
    s8 i;

    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            cpu = GwPlayer[D_8010D400_inst[0]].stat & 1;
            break;
        case 4:
            if ((GwPlayer[D_8010D400_inst[0]].stat & 1) && (GwPlayer[D_8010D400_inst[1]].stat & 1)) {
                cpu = 1;
            }
            break;
    }
    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & 1)) {
            break;
        }
    }
    if ((i < 4) & (cpu != 1)) {
        pressed = func_8010C8E0_inst(buttons);
    } else if (wait == 0) {
        pressed = 1;
    }
    return pressed;
}

void func_8010CBB8_inst(s32 arg0) {
    TextWindow *window = &winData[D_8010DCA8_inst.curGroup];
    s16 member = D_8010DCA8_inst.member;

    HuSprGrpMemberSet(window->group, member, window->sprite_id[member], arg0 & 0xFF);
}

void func_8010CC14_inst(void) {
    s8 i;
    s32 pads;

    for (i = 0; i < 4; i++) {
        HuWinInsertMesSet(D_8010DCA8_inst.curGroup, GwPlayer[D_8010D400_inst[i]].chr + 0x1C00, i);
    }
    pads = 0;
    switch (D_8010D40A_inst) {
        case 5:
        case 6:
        case 7:
        case 8:
            pads |= 1 << GwPlayer[D_8010D400_inst[0]].pad;
            break;
        case 4:
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    pads |= 1 << GwPlayer[D_8010D400_inst[i]].pad;
                }
            }
            break;
        case 0:
        case 1:
        case 2:
        case 3:
        default:
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[D_8010D400_inst[i]].stat & 1)) {
                    pads |= 1 << GwPlayer[D_8010D400_inst[i]].pad;
                }
            }
            break;
    }
    HuWinActivePlayerSet(D_8010DCA8_inst.curGroup, pads);
}

void func_8010CDE4_inst(const char *message, s32 x, s32 y) {
    char *text = func_800364DC_main((char *)message);

    D_8010DCD8_inst.subMode = -1;
    D_8010DCD8_inst.subMode = GameMesStrCreate(&D_8010DCD8_inst, text + 1, 0, -1, -1);
    D_8010DCD8_inst.pos.x = (s16)x;
    D_8010DCD8_inst.pos.y = (s16)y;
    HuSprPosSet(D_8010DCD8_inst.strGId[D_8010DCD8_inst.subMode], 0, D_8010DCD8_inst.pos.x,
                       D_8010DCD8_inst.pos.y);
    func_800365E8_main(text);
}

void func_8010CED0_inst(s32 x, s32 y) {
    HuSprPosSet(D_8010DCD8_inst.strGId[D_8010DCD8_inst.subMode], 0, x, y);
}

void func_8010CF14_inst(void) {
    D_8010DD50_inst.subMode = GameMesStrCreate(&D_8010DD50_inst, "PRACTICE", 0, -1, -1);
    D_8010DD50_inst.pos.x = 216.0f;
    D_8010DD50_inst.pos.y = 90.0f;
    HuSprPosSet(D_8010DD50_inst.strGId[D_8010DD50_inst.subMode], 0, 216, 90);
}

void func_8010CF98_inst(void) {
    D_8010DD50_inst.pos.x = 216.0f;
    D_8010DD50_inst.pos.y = 90.0f;
    HuSprPosSet(D_8010DD50_inst.strGId[D_8010DD50_inst.subMode], 0, 0xD8, 0x5A);
}

void func_8010CFF4_inst(void) {
    D_8010DD50_inst.pos.x = 512.0f;
    D_8010DD50_inst.pos.y = 512.0f;
    HuSprPosSet(D_8010DD50_inst.strGId[D_8010DD50_inst.subMode], 0, 0x200, 0x200);
}

void func_8010D044_inst(void) {
    TextWindow *window = &winData[D_8010DCA8_inst.curGroup];
    s8 i;

    if (D_8010D409_inst != 1) {
        func_8010CFF4_inst();
        HuSprDispOn(window->group, D_8010DCA8_inst.member);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprDispOn(window->group, D_8010DCA8_inst.mainMembers[i]);
            }
        }
        for (i = 0; i < 2; i++) {
            HuSprDispOff(window->group, D_8010DCA8_inst.helpMembers[i]);
        }
        D_8010DCCC_inst = D_8010DCD0_inst->message;
        if ((D_8010D40A_inst == 4) && (D_8010D411_inst != 2)) {
            D_8010DCCC_inst++;
        }
        HuWinMesSet(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
        func_8010CBB8_inst(0);
        D_8010DCD4_inst = 0;
        D_8010D5B1_inst = 0;
    }
}

void func_8010D1D4_inst(void) {
    TextWindow *window = &winData[D_8010DCA8_inst.curGroup];
    s8 i;
    s32 message;

    if (D_8010D409_inst != 1) {
        func_8010CF98_inst();
        for (i = 0; i < 2; i++) {
            HuSprDispOn(window->group, D_8010DCA8_inst.helpMembers[i]);
        }
        HuSprDispOff(window->group, D_8010DCA8_inst.member);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprDispOff(window->group, D_8010DCA8_inst.mainMembers[i]);
            }
        }
        switch (D_8010D40B_inst) {
            case 8:
            case 16:
            case 27:
                message = D_8010DB1C_inst[0];
                break;
            default:
                switch (D_8010D40A_inst) {
                    case 5:
                        message = D_8010DB04_inst[1][0];
                        break;
                    case 4:
                        message = D_8010DB10_inst[0][0];
                        message += D_8010D411_inst != 2;
                        break;
                    case 3:
                        message = D_8010DB10_inst[1][0];
                        break;
                    case 7:
                        if (D_8010D40B_inst == 70) {
                            message = D_8010DB24_inst[1][0];
                        } else {
                            message = D_8010DB30_inst[0];
                        }
                        break;
                    case 8:
                        message = D_8010DB24_inst[0][0];
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 6:
                    default:
                        message = D_8010DB04_inst[0][0];
                        break;
                }
                break;
        }
        HuWinMesSet(D_8010DCA8_inst.curGroup, message, -1, -1);
        D_8010D5B1_inst = 1;
    }
}
