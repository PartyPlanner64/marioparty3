#include "common.h"
#include "game/gamemes.h"

typedef struct {
    s16 curGroup;       /* 0x00 */
    s16 unk_02[0xB];    /* 0x02 */
    s16 spriteGroup[4]; /* 0x18, unknown size */
    s16 unk_20[0x1C];   /* 0x20 */
    Vec2f pos;          /* 0x58 */
} UnkInst;              /* unknown size */

typedef struct {
    s16 curGroup;       /* 0x00 */
    s16 mainMembers[3]; /* 0x02 */
    s16 helpMembers[2]; /* 0x08 */
    s16 member;         /* 0x0C */
} UnkInstWin;           /* sizeof 0x0E */

typedef struct {
    s32 overlay;
    u8 minigameType;
    u8 unk05;
    u16 flags;
    s16 message;
    s16 unk_0A[4];
    s16 finalMessage;
} InstMessageInfo;

typedef struct {
    s16 unk_00;
    s16 x;
} InstSpritePos;

extern u8 D_800CB8B1_main[];
extern s32 D_8010D5B4_inst;
extern s32 D_8010D5B8_inst;
extern s16 D_8010D5BA_inst;
extern u16 D_8010DCC0_inst[2];
extern u16 D_8010DCC4_inst[3];
extern InstSpritePos D_8010DAF8_inst[3];
extern s8 D_8010D411_inst;
extern s8 D_8010D40B_inst;
extern s16 D_8010DB04_inst[];
extern s16 D_8010DB0A_inst[];
extern s16 D_8010DB10_inst[];
extern s16 D_8010DB16_inst[];
extern s16 D_8010DB1C_inst[];
extern s16 D_8010DB24_inst[];
extern s16 D_8010DB2A_inst[];
extern s16 D_8010DB30_inst[];
extern s8 D_8010D5B1_inst;
extern s8 D_8010DCD4_inst;
extern s32 D_8010DCCC_inst;
extern InstMessageInfo *D_8010DCD0_inst;
extern s8 D_8010D400_inst[7];
extern s8 D_8010D406_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D409_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D554_inst[4];
extern s32 D_8010D440_inst;
extern s32 D_8010D558_inst;
extern omObjData *D_8010DC90_inst;
extern s16 *D_8010D4C0_inst[][2];
extern s8 D_8010D550_inst;
extern s8 D_8010D551_inst;
extern s8 D_8010D5B0_inst;
extern void (*D_8010DC94_inst)(omObjData *);
extern void (*D_8010DCA4_inst)(s32);
extern UnkInstWin D_8010DCA8_inst;
extern GAMEMES D_8010DCD8_inst;
extern GAMEMES D_8010DD50_inst;
extern UnkInst D_8010DCE0_inst;
extern UnkInst D_8010DD58_inst;

s32 func_8003A37C_main(GAMEMES *, const char *, s32, s32, s32);

void func_8010AC30_inst(omObjData *); /* extern */
void func_8010AD78_inst(omObjData *);
void func_8010B2A4_inst(omObjData *);
void func_8010C124_inst(s32);
u16 func_8010C8E0_inst(s32);
void func_8010D044_inst(void);
void func_8010CED0_inst(s32, s32);
void func_80060DEC_main(s16);
void func_8010BE78_inst(s32 arg0); /* extern */

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A1D0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010A750_inst);

void func_8010AC04_inst(void) {
    if (D_8010D550_inst == 1) {
        D_8010DC94_inst = func_8010AC30_inst;
    }
}

void func_8010AC30_inst(omObjData *object) {
    s32 i;
    s16 *models;

    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models[0]; i++) {
        func_8001C258_main(object->model[i + 5], 4, 0);
        func_8001C6A8_main(object->model[i + 5], 0);
        func_8001C814_main(object->model[i + 5], 1, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models[0]; i++) {
        func_8001C258_main(object->model[i + 15], 4, 0);
        func_8001C6A8_main(object->model[i + 15], 0);
        func_8001C814_main(object->model[i + 15], 1, 0);
    }
    D_8010DC94_inst = func_8010AD78_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010AD78_inst);

void func_8010B038_inst(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9C8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010D9E8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA34_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA44_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA54_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA64_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA74_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA84_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DA94_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAA4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAB0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DABC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAC8_inst);

void func_8010B040_inst(void) {
    s32 i;

    switch (D_8010D40A_inst) {
        case 0:
        case 1:
        case 2:
            for (i = 0; i < 4; i++) {
                if (D_800CB8B1_main[D_8010D400_inst[i]] == 0) {
                    D_8010D554_inst[i] = 0;
                } else {
                    D_8010D554_inst[i] = 1;
                }
            }
            break;
        case 3:
        case 4:
        case 5:
        case 7:
            D_8010D554_inst[0] = 2;
            D_8010D554_inst[1] = 2;
            D_8010D554_inst[2] = 2;
            D_8010D554_inst[3] = 2;
            break;
        case 8:
            D_8010D554_inst[0] = 3;
            D_8010D554_inst[1] = 3;
            D_8010D554_inst[2] = 3;
            D_8010D554_inst[3] = 3;
            break;
    }
}

void func_8010B0FC_inst(void) {
    D_8010D550_inst = 1;
}

s32 func_8010B10C_inst(void) {
    return D_8010D550_inst;
}

s32 func_8010B118_inst(void) {
    return D_8010D551_inst;
}

void func_8010B124_inst(void) {
    s8 i;
    omObjData *object = D_8010DC90_inst;
    s16 *models;

    D_8010D558_inst = 1;
    models = D_8010D4C0_inst[D_8010D40A_inst][0];
    for (i = 0; i < models[0]; i++) {
        func_8001C814_main(object->model[i + 5], 1, 0);
        func_8001C814_main(object->model[i + 5], 4, 4);
        func_8001C258_main(object->model[i + 5], 4, 0);
    }
    models = D_8010D4C0_inst[D_8010D40A_inst][1];
    for (i = 0; i < models[0]; i++) {
        func_8001C814_main(object->model[i + 15], 1, 0);
        func_8001C814_main(object->model[i + 15], 4, 4);
        func_8001C258_main(object->model[i + 15], 4, 0);
    }
    D_8010DC94_inst = func_8010B2A4_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B2A4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B628_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010B990_inst);

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

#ifdef NON_MATCHING
/* Near match: the final window-state assignment uses v0 instead of v1. */
void func_8010BE78_inst(s32 arg0) {
    s32 i;
    s16 *y;
    u16 *sprites;
    InstSpritePos *positions;

    if (D_8010D408_inst == 0) {
        func_8000BBD4_main(D_8010DCC0_inst[0], 160, *(y = &D_8010D5BA_inst));
        func_8010CED0_inst(160, *y);
        if (D_8010D40A_inst == 3) {
            func_8000BBD4_main(D_8010DCC0_inst[1], 160, *y + 22);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                func_8000BBD4_main(sprites[i], positions[i].x, D_8010D5BA_inst + 22);
            }
        }
        D_8010D5B4_inst++;
        D_8010D5B8_inst = sindf(D_8010D5B4_inst * 6) * 96.0f + -64.0f;
        if (D_8010D5B4_inst < 15) {
            return;
        }
        D_8010D5B4_inst = 0;
        D_8010D5B8_inst = -64;
        func_8000BBD4_main(D_8010DCC0_inst[0], 160, 32);
        func_8010CED0_inst(160, 32);
        if (D_8010D40A_inst == 3) {
            func_8000BBD4_main(D_8010DCC0_inst[1], 160, 54);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                func_8000BBD4_main(sprites[i], positions[i].x, 54);
            }
        }
    } else {
        func_8000BBD4_main(D_8010DCC0_inst[0], 160, 32);
        func_8010CED0_inst(160, 32);
        if (D_8010D40A_inst == 3) {
            func_8000BBD4_main(D_8010DCC0_inst[1], 160, 54);
            for (i = 0, sprites = D_8010DCC4_inst, positions = D_8010DAF8_inst; i < 3; i++) {
                func_8000BBD4_main(sprites[i], positions[i].x, 54);
            }
        }
        func_80060DEC_main(D_8010DCA8_inst.curGroup);
        D_8010D440_inst = 1;
    }
    func_8010D044_inst();
    D_8010DCA4_inst = func_8010C124_inst;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010BE78_inst);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DAF8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB04_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB10_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB1C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB24_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4E3390", D_8010DB30_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4E3390", func_8010C124_inst);

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

void func_8010C5C4_inst(void) {
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
                            message = D_8010DB0A_inst[i];
                            break;
                        case 4:
                            message = D_8010DB10_inst[i];
                            message += D_8010D411_inst != 2;
                            break;
                        case 3:
                            message = D_8010DB16_inst[i];
                            break;
                        case 7:
                            if (D_8010D40B_inst == 70) {
                                message = D_8010DB2A_inst[i];
                            } else {
                                message = D_8010DB30_inst[i];
                            }
                            break;
                        case 8:
                            message = D_8010DB24_inst[i];
                            break;
                        case 0:
                        case 1:
                        case 2:
                        case 6:
                        default:
                            message = D_8010DB04_inst[i];
                            break;
                    }
                    break;
            }
            func_8005B43C_main(D_8010DCA8_inst.curGroup, message, -1, -1);
            while (func_8005E0C0_main(D_8010DCA8_inst.curGroup) != 0) {
                if (func_8010C55C_inst() != 0) {
                    return;
                }
            }
        }
        message = D_8010DCD0_inst->finalMessage;
        if (D_8010D40A_inst == 4) {
            message += D_8010D411_inst != 2;
        }
        func_8005B43C_main(D_8010DCA8_inst.curGroup, message, -1, -1);
        while (func_8005E0C0_main(D_8010DCA8_inst.curGroup) != 0) {
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
    TextWindow *window = &D_800CC69C_main[D_8010DCA8_inst.curGroup];
    s16 member = D_8010DCA8_inst.member;

    func_80055024_main(window->unk_6C, member, window->unk_6E[member], arg0 & 0xFF);
}

void func_8010CC14_inst(void) {
    s8 i;
    s32 pads;

    for (i = 0; i < 4; i++) {
        func_8005B6BC_main(D_8010DCA8_inst.curGroup, GwPlayer[D_8010D400_inst[i]].chr + 0x1C00, i);
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
    func_8005FE54_main(D_8010DCA8_inst.curGroup, pads);
}

void func_8010CDE4_inst(const char *message, s32 x, s32 y) {
    char *text = func_800364DC_main((char *)message);

    D_8010DCD8_inst.unk08 = -1;
    D_8010DCD8_inst.unk08 = func_8003A37C_main(&D_8010DCD8_inst, text + 1, 0, -1, -1);
    D_8010DCD8_inst.unk60 = (s16)x;
    D_8010DCD8_inst.unk64 = (s16)y;
    func_80054904_main(D_8010DCD8_inst.strGId[D_8010DCD8_inst.unk08], 0, D_8010DCD8_inst.unk60,
                       D_8010DCD8_inst.unk64);
    func_800365E8_main(text);
}

void func_8010CED0_inst(s32 x, s32 y) {
    func_80054904_main(D_8010DCE0_inst.spriteGroup[D_8010DCE0_inst.curGroup], 0, x, y);
}

void func_8010CF14_inst(void) {
    D_8010DD50_inst.unk08 = func_8003A37C_main(&D_8010DD50_inst, "PRACTICE", 0, -1, -1);
    D_8010DD50_inst.unk60 = 216.0f;
    D_8010DD50_inst.unk64 = 90.0f;
    func_80054904_main(D_8010DD50_inst.strGId[D_8010DD50_inst.unk08], 0, 216, 90);
}

void func_8010CF98_inst(void) {
    D_8010DD58_inst.pos.x = 216.0f;
    D_8010DD58_inst.pos.y = 90.0f;
    func_80054904_main(D_8010DD58_inst.spriteGroup[D_8010DD58_inst.curGroup], 0, 0xD8, 0x5A);
}

void func_8010CFF4_inst(void) {
    D_8010DD58_inst.pos.x = 512.0f;
    D_8010DD58_inst.pos.y = 512.0f;
    func_80054904_main(D_8010DD58_inst.spriteGroup[D_8010DD58_inst.curGroup], 0, 0x200, 0x200);
}

void func_8010D044_inst(void) {
    TextWindow *window = &D_800CC69C_main[D_8010DCA8_inst.curGroup];
    s8 i;

    if (D_8010D409_inst != 1) {
        func_8010CFF4_inst();
        HuSprAttrReset(window->unk_6C, D_8010DCA8_inst.member, 0x8000);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprAttrReset(window->unk_6C, D_8010DCA8_inst.mainMembers[i], 0x8000);
            }
        }
        for (i = 0; i < 2; i++) {
            HuSprAttrSet(window->unk_6C, D_8010DCA8_inst.helpMembers[i], 0x8000);
        }
        D_8010DCCC_inst = D_8010DCD0_inst->message;
        if ((D_8010D40A_inst == 4) && (D_8010D411_inst != 2)) {
            D_8010DCCC_inst++;
        }
        func_8005B43C_main(D_8010DCA8_inst.curGroup, D_8010DCCC_inst, -1, -1);
        func_8010CBB8_inst(0);
        D_8010DCD4_inst = 0;
        D_8010D5B1_inst = 0;
    }
}

void func_8010D1D4_inst(void) {
    TextWindow *window = &D_800CC69C_main[D_8010DCA8_inst.curGroup];
    s8 i;
    s32 message;

    if (D_8010D409_inst != 1) {
        func_8010CF98_inst();
        for (i = 0; i < 2; i++) {
            HuSprAttrReset(window->unk_6C, D_8010DCA8_inst.helpMembers[i], 0x8000);
        }
        HuSprAttrSet(window->unk_6C, D_8010DCA8_inst.member, 0x8000);
        for (i = 0; i < 3; i++) {
            if (i != 1) {
                HuSprAttrSet(window->unk_6C, D_8010DCA8_inst.mainMembers[i], 0x8000);
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
                        message = D_8010DB0A_inst[0];
                        break;
                    case 4:
                        message = D_8010DB10_inst[0];
                        message += D_8010D411_inst != 2;
                        break;
                    case 3:
                        message = D_8010DB16_inst[0];
                        break;
                    case 7:
                        if (D_8010D40B_inst == 70) {
                            message = D_8010DB2A_inst[0];
                        } else {
                            message = D_8010DB30_inst[0];
                        }
                        break;
                    case 8:
                        message = D_8010DB24_inst[0];
                        break;
                    case 0:
                    case 1:
                    case 2:
                    case 6:
                    default:
                        message = D_8010DB04_inst[0];
                        break;
                }
                break;
        }
        func_8005B43C_main(D_8010DCA8_inst.curGroup, message, -1, -1);
        D_8010D5B1_inst = 1;
    }
}
