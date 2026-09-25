#include "common.h"
#include "game/vibrator.h"
#include "mallocblock.h"

#define UNK_VALUE 0x91

typedef struct UnkFileSelect2 {
    s16 unk_00;
    u32 unk_04; // can be messageID or message pointer
    void *unk_08;
} UnkFileSelect2;

typedef struct UnkFileSelect {
    u8 unk_00;
    u8 unk_01[0xB];
    char unk_0C[0x78];
} UnkFileSelect; // sizeof 0x84

typedef struct UnkFileName {
    u8 unk_00[0xB];
} UnkFileName; // sizeof 0xB

typedef struct UnkFileSelect3 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    s32 unk_28;
} UnkFileSelect3;

typedef struct UnkFileSelect4 {
    s16 unk_00;
    u16 unk_02;
    s32 unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s8 unk_18;
    u8 unk_19[3];
} UnkFileSelect4; // sizeof 0x1C

typedef struct UnkFileSelect5 {
    omObjData *unk_00;
    char unk_04[0x58];
} UnkFileSelect5; // sizeof 0x5C

void func_80105FBC_filesel(s32, s32, s32);
void func_801076D0_filesel(s32, u32);
s32 func_80108834_filesel(void);
void func_8010AB1C_filesel(s32, u32);
void func_8010AB58_filesel(s32, u32);
void func_8010AB60_filesel(s32, u32);
void func_8010FC58_filesel(omObjData *object);
void func_80110FB0_filesel(u32);
void func_801110F0_filesel(u32);
void func_8011139C_filesel(s32);
s32 func_80111B14_filesel(s32);
u32 func_80106AD8_filesel(u32);
s32 func_8010AC58_filesel(s32);
s32 func_80112494_filesel(s32, u8 *);
void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BCC8_main(u16, s32);
void func_8000BE5C_main(u16, f32, f32);

extern u16 D_800D1244_main;
extern UnkFileSelect D_801142DC_filesel[3];
extern u8 D_80114490_filesel[0x20];
extern UnkFileSelect2 D_80114158_filesel[0x20]; // sizeof 0xC
extern UnkFileSelect3 D_80113650_filesel[0x40];
extern UnkFileSelect4 D_80112ED0_filesel[0x40];
extern s16 D_801135D0_filesel[0x40];
extern Process *D_80114504_filesel;
extern UnkFileSelect5 D_80114598_filesel[3];
extern u8 *D_801127FC_filesel[];
extern u8 *D_80112844_filesel[];
extern u8 *D_8011288C_filesel[];
extern s16 D_80114150_filesel;
extern u16 D_80114152_filesel;
extern s32 D_801146D8_filesel;

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801059D0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105BC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105BF0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105C1C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105CB0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105CC4_filesel);

void func_80105CE0_filesel(s32 arg0, s32 arg1) {
    D_801135D0_filesel[arg0] = func_8000B838_main(arg1);
}

void func_80105D18_filesel(s32 arg0) {
    if (D_801135D0_filesel[arg0] != -1) {
        HuSprKill(D_801135D0_filesel[arg0]);
    }
    D_801135D0_filesel[arg0] = -1;
}

void func_80105D70_filesel(s32 arg0, s16 arg1) {
    D_80112ED0_filesel[arg0].unk_00 = InitEspriteSlot(D_801135D0_filesel[arg1], 0, 0);
    func_80105FBC_filesel(arg0, 0xA0, 0x78);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105DD8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105E48_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105E7C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105EC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105EEC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105F24_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105F54_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105F84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105FA0_filesel);

void func_80105FBC_filesel(s32 arg0, s32 arg1, s32 arg2) {
    D_80112ED0_filesel[arg0].unk_04 = arg1;
    D_80112ED0_filesel[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_80112ED0_filesel[arg0].unk_00, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106014_filesel);

void func_80106044_filesel(s32 arg0, f32 arg1, f32 arg2) {
    D_80112ED0_filesel[arg0].unk_0C = arg1;
    D_80112ED0_filesel[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_80112ED0_filesel[arg0].unk_00, arg1, arg2);
}

void func_80106094_filesel(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_80112ED0_filesel[arg0].unk_00, arg1);
}

void func_801060CC_filesel(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_80112ED0_filesel[arg0].unk_00, arg1);
}

void func_80106100_filesel(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_80112ED0_filesel[arg0].unk_00, arg1);
}

void func_80106134_filesel(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_80112ED0_filesel[arg0].unk_00, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106168_filesel);

void func_801061D4_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80113650_filesel); i++) {
        D_80113650_filesel[i].unk_00 = -1;
        D_80113650_filesel[i].unk_02 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106220_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801062BC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106344_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801063F4_filesel);

s16 func_8010642C_filesel(s32 arg0) {
    return D_80113650_filesel[arg0].unk_00;
}

s16 func_80106450_filesel(s32 arg0) {
    return D_80113650_filesel[arg0].unk_02;
}

void func_80106474_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80113650_filesel[arg0].unk_1C = arg1;
    D_80113650_filesel[arg0].unk_20 = arg2;
    D_80113650_filesel[arg0].unk_24 = arg3;
    Hu3DModelRotSet(D_80113650_filesel[arg0].unk_00, arg1, arg2, arg3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801064DC_filesel);

void func_80106550_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80113650_filesel[arg0].unk_10 = arg1;
    D_80113650_filesel[arg0].unk_14 = arg2;
    D_80113650_filesel[arg0].unk_18 = arg3;
    Hu3DModelScaleSet(D_80113650_filesel[arg0].unk_00, arg1, arg2, arg3);
}

void func_801065B8_filesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80113650_filesel[arg0].unk_04;
    *arg2 = D_80113650_filesel[arg0].unk_08;
    *arg3 = D_80113650_filesel[arg0].unk_0C;
}

void func_8010660C_filesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80113650_filesel[arg0].unk_1C;
    *arg2 = D_80113650_filesel[arg0].unk_20;
    *arg3 = D_80113650_filesel[arg0].unk_24;
}

void func_80106654_filesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80113650_filesel[arg0].unk_10;
    *arg2 = D_80113650_filesel[arg0].unk_14;
    *arg3 = D_80113650_filesel[arg0].unk_18;
}

void func_8010669C_filesel(s32 arg0) {
    func_8001C258_main(D_80113650_filesel[arg0].unk_00, 4, 4);
}

void func_801066DC_filesel(s32 arg0) {
    func_8001C258_main(D_80113650_filesel[arg0].unk_00, 4, 0);
}

void func_8010671C_filesel(s32 arg0, s32 arg1) {
    func_8001C814_main(D_80113650_filesel[arg0].unk_00, -1, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106760_filesel);

void func_801067D0_filesel(s32 arg0, s16 arg1) {
    func_8001C814_main(D_80113650_filesel[arg0].unk_00, arg1, 0);
}

void func_80106814_filesel(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_80113650_filesel[arg0].unk_00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010684C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801068B0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106950_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801069D8_filesel);

void func_80106A48_filesel(void) {
    // The original call omits the resource id.
    D_80114150_filesel = ((s16 (*)())func_8000B838_main)();
    D_80114152_filesel = InitEspriteSlot(D_80114150_filesel, 0, 0);
    func_8000BC48_main(D_80114152_filesel, 0x4000);
    func_8000BBD4_main(D_80114152_filesel, 0xA0, 0x78);
}

void func_80106AAC_filesel(void) {
    func_8000C184_main(D_80114152_filesel);
    HuSprKill(D_80114150_filesel);
}

u32 func_80106AD8_filesel(u32 arg0) {
    char buf[0x100];
    s32 len;
    void *ptr;

    if (0x80000000U < arg0) {
        len = func_800452A0_main(buf, (void *)arg0);
        ptr = HuMemAlloc(len);
        bcopy(buf, ptr, len);
        return (u32)ptr;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106B40_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106D8C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80106ED8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107040_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801071E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801072B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107380_filesel);

void func_8010744C_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114158_filesel); i++) {
        D_80114158_filesel[i].unk_00 = -1;
        D_80114158_filesel[i].unk_04 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107490_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107574_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801075D8_filesel);

void func_80107608_filesel(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80114158_filesel[arg0].unk_00, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107670_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801076A0_filesel);

void func_801076D0_filesel(s32 arg0, u32 arg1) {
    u32 temp_v0;

    func_8005D294_main(D_80114158_filesel[arg0].unk_00);
    if (D_80114158_filesel[arg0].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[arg0].unk_04);
        D_80114158_filesel[arg0].unk_04 = 0;
    }

    temp_v0 = func_80106AD8_filesel(arg1);
    // pointer check
    if (temp_v0 > 0x80000000U) {
        D_80114158_filesel[arg0].unk_04 = temp_v0;
    }
    func_8005B43C_main(D_80114158_filesel[arg0].unk_00, temp_v0, -1, -1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010779C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801077D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107810_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010782C_filesel);

void func_80107880_filesel(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801078BC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801078F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107AA8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107C50_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107C84_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107CF8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801083AC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108440_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112A64_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112A68_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010846C_filesel);

s32 func_80108834_filesel(void) {
    s32 i;
    s32 total;

    for (i = 0, total = 0; i < ARRAY_COUNT(D_801142DC_filesel); i++) {
        if (D_801142DC_filesel[i].unk_00 == UNK_VALUE) {
            total++;
        }
    }

    return total;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108878_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801088DC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108A94_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108C34_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108D74_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80108EB8_filesel);

#define CLAMP_BELOW(val, limit) ((val) < (limit) ? (val) : 0)

enum OptionsFileSelect {
    OPTION_FILE0 = 0,
    OPTION_FILE1 = 1,
    OPTION_FILE2 = 2,
    OPTION_FILES_END,
    OPTION_COPY = 3,
    OPTION_ERASE = 4,
    OPTION_FILES_NAME_BEGIN,
    OPTION_FILE0_NAME = 5,
    OPTION_FILE1_NAME = 6,
    OPTION_FILE2_NAME = 7,
    OPTION_MAX = 7,
};

// TODO: can the gotos be removed?
// main function for handling input when an option hasn't been select yet
u32 func_80109570_filesel(s32 arg0) {
    s32 temp_v0;
    u32 temp_v1;
    s32 animTimerAdjusted;
    s32 animTimer;
    u16 pressedInput;
    s32 cursorIndex;
    u32 selectedOption;
    s32 unkValue;

    animTimer = 0;

    if (arg0 < 0) {
        arg0 = 0;
    }

    selectedOption = arg0;
    cursorIndex = selectedOption;
    unkValue = UNK_VALUE;

    while (1) {
        pressedInput = D_800D1244_main;
        temp_v0 = func_80111B14_filesel(0);
        if (temp_v0 != -1) {
            pressedInput |= temp_v0;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            switch (selectedOption) {
                case OPTION_FILE0:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE1:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_FILE2:
                    RepeatVibrator(0, 5, 0, 5);
                    func_80110FB0_filesel(selectedOption);
                    break;
                case OPTION_COPY:
                case OPTION_ERASE:
                case OPTION_FILE0_NAME:
                case OPTION_FILE1_NAME:
                case OPTION_FILE2_NAME:
                    break;
                default:
                    goto checkIfCursorIndexChanged;
            }
            return selectedOption;
        }
        if ((D_800D5558_main[0] & B_BUTTON)) {
            if (selectedOption > OPTION_MAX) {
                goto checkIfCursorIndexChanged;
            }
        }
        switch (selectedOption) {
            case OPTION_FILE0:
            case OPTION_FILE1:
            case OPTION_FILE2:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    func_801076D0_filesel(4, 0x2A00);
                    func_80110FB0_filesel(selectedOption);
                    cursorIndex = selectedOption + 1;
                    if (pressedInput & L_JPAD) {
                        cursorIndex = selectedOption - 1;
                        // if less than 0, wrap index back around to file index 2
                        if (cursorIndex < 0) {
                            cursorIndex = OPTION_FILE2;
                        }
                    } else {
                        cursorIndex = CLAMP_BELOW(cursorIndex, OPTION_FILES_END);
                    }
                } else if (pressedInput & (U_JPAD | D_JPAD)) {
                    if (pressedInput & U_JPAD) {
                        cursorIndex = OPTION_COPY;
                        if ((temp_v1 - 1) < (OPTION_FILES_END - 1)) {
                            func_801076D0_filesel(4, 0x2A01);
                        } else {
                            func_801076D0_filesel(4, 0x2A03);
                        }
                        func_80110FB0_filesel(selectedOption);
                    } else {
                        if (D_801142DC_filesel[cursorIndex].unk_00 == unkValue) {
                            cursorIndex = selectedOption + OPTION_FILES_NAME_BEGIN;
                            func_80110FB0_filesel(selectedOption);
                        }
                    }
                }
                break;
            case OPTION_COPY:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    if (temp_v1 == 0) {
                        func_801076D0_filesel(4, 0x2A13);
                    } else {
                        func_801076D0_filesel(4, 0x2A07);
                    }
                    cursorIndex = OPTION_ERASE;
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = OPTION_FILE1;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_ERASE:
                temp_v1 = func_80108834_filesel();
                if (pressedInput & (L_JPAD | R_JPAD)) {
                    cursorIndex = OPTION_FILES_END;
                    if ((temp_v1 - 1) < 2) {
                        func_801076D0_filesel(4, 0x2A01);
                    } else {
                        func_801076D0_filesel(4, 0x2A03);
                    }
                }
                if (pressedInput & D_JPAD) {
                    cursorIndex = 2;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
            case OPTION_FILE0_NAME:
            case OPTION_FILE1_NAME:
            case OPTION_FILE2_NAME:
                func_801076D0_filesel(4, 0x2A11);
                if (pressedInput & L_JPAD) {
                    cursorIndex = selectedOption;
                    do {
                        cursorIndex -= 1;
                        if (cursorIndex < OPTION_FILES_NAME_BEGIN) {
                            cursorIndex = 7;
                        }
                    } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                } else {
                    if (pressedInput & R_JPAD) {
                        cursorIndex = selectedOption;
                        do {
                            // if cursor goes over max, wrap around back to file 0 name
                            if (++cursorIndex > OPTION_MAX) {
                                cursorIndex = OPTION_FILE0_NAME;
                            }
                        } while (D_801142DC_filesel[cursorIndex - OPTION_FILES_NAME_BEGIN].unk_00 != unkValue);
                    }
                }
                if (pressedInput & U_JPAD) {
                    cursorIndex = selectedOption - OPTION_FILES_NAME_BEGIN;
                    func_801076D0_filesel(4, 0x2A00);
                }
                break;
        }

    checkIfCursorIndexChanged:
        if (selectedOption != cursorIndex) {
            // animate cursor to new position
            func_8010AB60_filesel(18, cursorIndex);
            selectedOption = cursorIndex;

            if (selectedOption < OPTION_FILES_END) {
                func_801110F0_filesel(selectedOption);
            }
        }
        func_8010AB1C_filesel(18, selectedOption);

        animTimerAdjusted = (animTimer < 0) ? animTimer + 7 : animTimer;
        animTimerAdjusted = (animTimerAdjusted >> 3);
        func_8010AB58_filesel(18, -animTimerAdjusted);

        animTimer = (animTimer < 20) ? animTimer + 1 : 0;

        HuPrcVSleep();
    }
    return selectedOption;
}

s32 func_80109904_filesel(s32 arg0) {
    u8 buf[32]; // TODO: figure out correct type of this
    s32 temp_s0;

    bzero(&buf, sizeof(buf));
    func_80112494_filesel(arg0, buf);
    HuPrcSleep(3);
    func_801076D0_filesel(4, 0x2A11);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

s32 func_80109968_filesel(s32 arg0) {
    s32 temp_s0;

    HuPrcSleep(3);
    temp_s0 = func_8010AC58_filesel(arg0);
    HuPrcSleep(3);
    return temp_s0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801099A8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80109B2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A028_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A680_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A7D8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A978_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AF0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010AB1C_filesel);

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010AB60_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010AC58_filesel);

u16 func_8010B4D0_filesel(s32 arg0, s32 arg1) {
    u8 *str = D_801127FC_filesel[arg0];

    return (str[arg1 * 2] << 8) | str[arg1 * 2 + 1];
}

u16 func_8010B4FC_filesel(s32 arg0, s32 arg1) {
    u8 *str = D_80112844_filesel[arg0];

    return (str[arg1 * 2] << 8) | str[arg1 * 2 + 1];
}

u16 func_8010B528_filesel(s32 arg0, s32 arg1) {
    u8 *str = D_8011288C_filesel[arg1];

    return (str[arg0 * 2] << 8) | str[arg0 * 2 + 1];
}

void func_8010B554_filesel(u8 *arg0) {
    bzero(D_80114490_filesel, sizeof(D_80114490_filesel));
    bcopy(arg0, D_80114490_filesel, sizeof(D_80114490_filesel));
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B598_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B5D4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B6F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B80C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B18_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B24_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B30_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B3C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B48_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B54_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B60_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B78_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B84_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B90_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112B9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BA8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BB4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BC0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BCC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BD8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BF0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112BFC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C08_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C14_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C20_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C38_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C44_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C50_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C5C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C68_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C74_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C80_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112C98_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112CA4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112CB0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112CBC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112CC8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112CE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D00_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D1C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D38_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B998_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010BDC4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010BE14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010BE30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010C25C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010C688_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D6C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D7C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D8C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112D9C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112DAC_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112DBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010C9B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010CCA8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010D13C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010D660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010DD54_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010DDC0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010DEEC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010DF58_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010DFF4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E1B4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E250_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E740_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E864_filesel);

void func_8010F10C_filesel(void) {
    omDelPrcObj(D_80114504_filesel);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F12C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F168_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F5C8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F65C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112DF8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112E08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F678_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F760_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F844_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F874_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F8A4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010FBE0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010FC58_filesel);

void func_8010FF48_filesel(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010FC58_filesel);

    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010FFA0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801102F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110320_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801103A0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801106FC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8011072C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801107AC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110B4C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110B7C_filesel);

void func_80110C84_filesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80114598_filesel[i].unk_00 = NULL;
    }
}

void func_80110CC0_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].unk_00);
    D_80114598_filesel[arg0].unk_00 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110D0C_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110E70_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110F04_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80110FB0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111004_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801110F0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111144_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8011132C_filesel);

void func_8011139C_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].unk_00);
    D_80114598_filesel[arg0].unk_00 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801113E8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111660_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111790_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111944_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801119F4_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111A08_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111B14_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111C30_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111CBC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111E78_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111FFC_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80112184_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801122B0_filesel);

s32 func_80112494_filesel(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i++) {
        D_801142DC_filesel[arg0].unk_01[i] = arg1[i];
    }

    // terminate string
    D_801142DC_filesel[arg0].unk_01[i] = '\0';
    D_801142DC_filesel[arg0].unk_01[i + 1] = '\0';
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80112508_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80112584_filesel);

s32 func_801125E8_filesel(UnkFileName *arg0) {
    s32 i;
    s32 count;

    for (i = 0, count = 0; i < 10; i += 2) {
        if ((u16)((arg0->unk_00[i] << 8) | arg0->unk_00[i + 1]) == 0) {
            break;
        }
        count++;
    }

    // terminate string
    arg0->unk_00[i + 1] = '\0';
    arg0->unk_00[i] = '\0';
    return count;
}

void func_80112630_filesel(omObjData *arg0) {
    s32 *counter;
    s32 newValue;

    if (D_801146D8_filesel == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_801146D8_filesel;
    if (*counter < 0xB) {
        newValue = *counter + 1;
    } else {
        newValue = 0;
    }
    *counter = newValue;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80112684_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801126C0_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80112758_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112E68_filesel);
