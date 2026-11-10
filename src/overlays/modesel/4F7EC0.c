#include "common.h"
#include "game/vibrator.h"
#include "game/mallocblock.h"
#include "game/hmfmath.h"
#include "game/lightdebug.h"
#include "overlays/minigame.h"
#include "math.h"

typedef struct UnkModeSel {
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
} UnkModeSel;

typedef struct UnkModeSel2 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    s32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    u8 unk_18;
    u8 unk_19[3];
} UnkModeSel2; // sizeof 0x1C

typedef struct UnkModeSel3 {
    Vec pos;
    Vec at;
    Vec up;
} UnkModeSel3; // sizeof 0x24

// Parallel to UnkModeSel: two float triples indexed with the same 0x2C stride.
// The tail is unreferenced padding that brings each element up to 0x2C.
typedef struct UnkModeSel4 {
    f32 unk_00;
    f32 unk_04;
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s32 unk_18[5];
} UnkModeSel4; // sizeof 0x2C

// One entry per player slot; the object is the spinner for that player.
typedef struct UnkModeSel5 {
    s32 unk_00;
    s32 unk_04;
    omObjData *unk_08;
    Vec unk_0C;
} UnkModeSel5; // sizeof 0x18

typedef struct UnkModeSel6 {
    omObjData *unk_00;
    s32 unk_04;
    s32 unk_08;
    Vec pos;
    Vec at;
    Vec up;
} UnkModeSel6; // sizeof 0x30

typedef struct UnkModeSel7 {
    omObjData *obj;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    Vec unk_10;
    Vec unk_1C;
} UnkModeSel7; // sizeof 0x28

// Accumulated spin angle: added to as a float by func_8010B940_modesel, but reset
// and read as a raw word by func_8010B804_modesel and func_8010B824_modesel.
typedef union UnkModeSelAngle {
    s32 word;
    f32 angle;
} UnkModeSelAngle; // sizeof 0x4

// One entry per spinning star (model indices 7 to 9) and its shadow.
typedef struct UnkModeSelStar {
    HmfMotionNode *star;
    HmfMotionNode *shadow;
    f32 x;
    f32 y;
    f32 z;
    f32 scale;
    UnkModeSelAngle rot;
} UnkModeSelStar; // sizeof 0x1C

// Summary of the saved party mode board, copied from the loaded save.
typedef struct UnkModeSelBoardSave {
    s32 chr[4];
    s32 cpu[4];
    s32 gameLength;
    s32 currentTurn;
    s32 totalTurns;
} UnkModeSelBoardSave; // sizeof 0x2C

// Summary of the saved story mode board, copied from the loaded save.
typedef struct UnkModeSelStorySave {
    s32 chr[2];
    s32 cpu[2];
    s32 gameLength;
    s32 currentTurn;
    s32 totalTurns;
} UnkModeSelStorySave; // sizeof 0x1C

extern UnkModeSelStar D_80110B18_modesel[3];
extern s32 D_8010F2C8_modesel;
extern s32 D_80110BD8_modesel;
extern s16 D_80110BDA_modesel;
// Position tables, one entry per spinner position.
extern Vec D_8010F2CC_modesel[];
extern Vec D_8010F304_modesel[];
extern u8 D_8010F2A0_modesel[];
extern u8 D_8010F2B0_modesel[];
// the one-column second dimension keeps these indexed stores addressing the array base symbolically
extern s16 D_8010FE10_modesel[0x40][1];
extern UnkModeSel D_8010FE90_modesel[0x40];
extern UnkModeSel4 D_8010FEA0_modesel[0x40];
extern UnkModeSel2 D_8010F710_modesel[0x40];
extern s16 D_80110990_modesel;
extern u16 D_80110992_modesel;
extern s16 D_80110998_modesel[0x20][6];
extern s32 D_8011099C_modesel[0x20][3];
extern s32 D_801109A0_modesel[0x20][3];
extern UnkModeSel7 D_80110C10_modesel;
extern UnkModeSel6 D_80110C38_modesel;
extern UnkModeSel5 D_80110C68_modesel[3];
extern UnkModeSel3 D_80110BE8_modesel;
extern Vec D_80110CB0_modesel;
extern Vec D_80110CBC_modesel;
extern f32 D_80110CD4_modesel;
// Start and end positions for the model 10 hop animation.
extern Vec D_80110CD8_modesel[2];
// Three interleaved parallel arrays covering the same 21 slots; each element is 0xC bytes apart.
extern s32 D_80110CF0_modesel[][3];
extern s32 D_80110CF4_modesel[][3];
extern omObjData *D_80110CF8_modesel[][3];
extern s32 D_80110DEC_modesel;
extern Process *D_80110BDC_modesel;
extern Process *D_80110BE0_modesel;
extern s16 D_8010F296_modesel;
extern omObjData *D_80110BD0_modesel;
extern HmfMotionNode *D_80110BD4_modesel;
extern f32 D_8010F2BC_modesel;
extern f32 D_8010F2C0_modesel;
extern f32 D_8010F2C4_modesel;
extern s32 D_80110B70_modesel[6];
extern UnkModeSelBoardSave D_80110B88_modesel;
extern UnkModeSelStorySave D_80110BB4_modesel;
extern u32 D_8010F2F0_modesel[];
extern Vec D_8010F3B0_modesel;
extern Vec D_8010F3BC_modesel;
extern Vec D_8010F3C8_modesel;
extern u8 D_800D2132_main;

void func_801059D0_modesel(void);
void func_80105C7C_modesel(void);
void func_80105F84_modesel(s32);
void func_80105FB4_modesel(s32);
void func_80106234_modesel(void);
void func_801074AC_modesel(void);
void func_80107CB0_modesel(void);
void func_801074F0_modesel(s32);
void func_80108A94_modesel(s32);
s32 func_80108AE0_modesel(Vec *, Vec *, Vec *);
void func_8010ACA8_modesel(omObjData *);
f32 func_8010EC74_modesel(f32, f32);

void func_8010601C_modesel(s32, s32, s32);
void func_801063A4_modesel(s32);
void func_80107CEC_modesel(void);
void func_8010B790_modesel(s32, f32, f32, f32, f32);
void func_8010B75C_modesel(s32, f32, f32, f32, f32);
void func_8010B824_modesel(s32);
void func_8010E000_modesel(s32, s32 *, s32 *);
void func_8010ECAC_modesel(omObjData *);
void func_80106A38_modesel(s32, s32, s16);
void func_80108F8C_modesel(Vec *, Vec *, Vec *);
void func_80109290_modesel(omObjData *);
void func_8010A420_modesel(omObjData *);
void func_8010A674_modesel(omObjData *);
void func_8010A84C_modesel(omObjData *);
void func_8010AAC0_modesel(omObjData *);
void func_8010ADC8_modesel(omObjData *);
void func_8010E5F0_modesel(omObjData *);
void func_80109BC0_modesel(omObjData *);
void func_801096D4_modesel(omObjData *);
void func_8010E138_modesel(s32, f32 *, f32 *, f32 *);
void func_8010E3A4_modesel(s32, f32);
s32 func_80109A58_modesel(s32);
s32 func_8010C094_modesel(void);
void func_8010C874_modesel(void);
void func_8010CA30_modesel(void);
void func_8010CB34_modesel(void);
void func_8010E280_modesel(s32, s32);
void func_8010DC6C_modesel(s32);
void func_80106BA0_modesel(s32 index, u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
void func_8010DE88_modesel(s32);
void func_80108FD0_modesel(omObjData *);
void func_80106074_modesel(s32, s32 *, s32 *);
void func_80109DB8_modesel(omObjData *);
void func_8010A068_modesel(omObjData *);
void func_8010A1C4_modesel(omObjData *);
void func_8010B804_modesel(s32, s32);
void func_8010B940_modesel(s32, f32);
void func_8010E558_modesel(s32);
void func_801094F0_modesel(Vec *, Vec *, f32, Vec *);
s32 func_80106DEC_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 func_80106F38_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 func_801070A0_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style);
s32 func_80107248_modesel(u32 message, s16 x, s16 y, s16 style);
s32 func_80107314_modesel(u32 message, s16 x, s16 y, s16 style);
s32 func_801073E0_modesel(u32 message, s16 x, s16 y, s16 style);
s32 func_8010F204_modesel(s32);
s32 func_8010CD00_modesel(s32, s32);
s32 func_8010D8DC_modesel(s32, s32);
void func_8010DF70_modesel(void);
void func_8010DFB4_modesel(void);
void func_8010DFD0_modesel(s32);
void func_8010E6D8_modesel(s32);
void func_8010EC40_modesel(void);
void func_8010ED00_modesel(void);

void func_801059D0_modesel(void) {
    Vec position;
    Vec target;
    Vec up;

    omInitObjMan(0x40, 0x20);
    func_800142A0_main(0x20);
    func_8004A208_main();
    func_8000B5F0_main(1);
    position = D_8010F3B0_modesel;
    target = D_8010F3BC_modesel;
    up = D_8010F3C8_modesel;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 41.0f, 80.0f, 8000.0f);
    Hu3DCameraPosSetV(0, &position, &target, &up);
    func_80030030_main(1.0f);
    if (func_800465D0_main()) {
        HuAudSeqStop();
    }
    pfInit();
    HuWinInit();
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0, 0, 0);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(1, 0.0f, 64.0f, 192.0f);
    D_800D2132_main = 0;
    _ClearFlag(0xD);
}

void func_80105BD8_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

void func_80105BFC_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}

// Code matches, but the target is followed by 0x10 alignment padding, which suggests
// a file boundary at func_80105C50_modesel.
#ifdef NON_MATCHING
void func_80105C20_modesel(void) {
    func_801059D0_modesel();
    func_80107CB0_modesel();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105C20_modesel);
#endif

void func_80105C50_modesel(void) {
    func_80105C7C_modesel();
    func_80106234_modesel();
    func_801074AC_modesel();
}

void func_80105C7C_modesel(void) {
    UnkModeSel2 *p;
    f32 zero;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010F710_modesel); i++) {
        D_8010FE10_modesel[i][0] = -1;
        D_8010F710_modesel[i].unk_00 = -1;
        // only these two of the seven field stores go through the pointer, the rest stay symbolic
        p = &D_8010F710_modesel[i];
        p->unk_08 = 0;
        D_8010F710_modesel[i].unk_04 = 0;
        zero = 0.0f;
        p->unk_10 = zero;
        D_8010F710_modesel[i].unk_0C = zero;
        D_8010F710_modesel[i].unk_14 = zero;
        D_8010F710_modesel[i].unk_18 = 0xFF;
    }
}

s16 func_80105D10_modesel(s32 arg0) {
    return D_8010FE10_modesel[arg0][0];
}

s16 func_80105D24_modesel(s32 arg0) {
    return D_8010F710_modesel[arg0].unk_00;
}

void func_80105D40_modesel(s32 arg0, s32 arg1) {
    D_8010FE10_modesel[arg0][0] = func_8000B838_main(arg1);
}

void func_80105D78_modesel(s32 arg0) {
    if (D_8010FE10_modesel[arg0][0] != -1) {
        HuSprAnimKill(D_8010FE10_modesel[arg0][0]);
    }
    D_8010FE10_modesel[arg0][0] = -1;
}

void func_80105DD0_modesel(s32 arg0, s16 arg1) {
    D_8010F710_modesel[arg0].unk_00 = espEntry(D_8010FE10_modesel[arg1][0], 0, 0);
    func_8010601C_modesel(arg0, 0xA0, 0x78);
}

void func_80105E38_modesel(s32 arg0) {
    if (D_8010F710_modesel[arg0].unk_00 != -1) {
        espKill(D_8010F710_modesel[arg0].unk_00);
    }
    D_8010F710_modesel[arg0].unk_00 = -1;
}

void func_80105EA8_modesel(s32 arg0, s32 arg1) {
    func_80105D40_modesel(arg0, arg1);
    func_80105DD0_modesel(arg0, arg0);
}

void func_80105EDC_modesel(s32 arg0, s32 arg1) {
    func_80105EA8_modesel(arg0, arg1);
    espAttrSet(D_8010F710_modesel[arg0].unk_00, 0x4000);
}

void func_80105F20_modesel(s32 arg0) {
    func_80105E38_modesel(arg0);
    func_80105D78_modesel(arg0);
}

void func_80105F4C_modesel(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        func_80105F20_modesel(i);
    }
}

void func_80105F84_modesel(s32 arg0) {
    espDispOn(D_8010F710_modesel[arg0].unk_00);
}

void func_80105FB4_modesel(s32 arg0) {
    espDispOff(D_8010F710_modesel[arg0].unk_00);
}

void func_80105FE4_modesel(s32 arg0) {
    func_80105F84_modesel(arg0);
}

void func_80106000_modesel(s32 arg0) {
    func_80105FB4_modesel(arg0);
}

void func_8010601C_modesel(s32 arg0, s32 arg1, s32 arg2) {
    D_8010F710_modesel[arg0].unk_04 = arg1;
    D_8010F710_modesel[arg0].unk_08 = arg2;
    espPosSet(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

void func_80106074_modesel(s32 arg0, s32 *x, s32 *y) {
    *x = D_8010F710_modesel[arg0].unk_04;
    *y = D_8010F710_modesel[arg0].unk_08;
}

void func_801060A4_modesel(s32 arg0, f32 arg1, f32 arg2) {
    D_8010F710_modesel[arg0].unk_0C = arg1;
    D_8010F710_modesel[arg0].unk_10 = arg2;
    espScaleSet(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

void func_801060F4_modesel(s32 arg0, u16 arg1) {
    espTPLvlSet(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_8010612C_modesel(s32 arg0, u16 arg1) {
    espAttrSet(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_80106160_modesel(s32 arg0, u16 arg1) {
    espAttrReset(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_80106194_modesel(s32 arg0, u16 arg1) {
    espPriSet(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_801061C8_modesel(s32 arg0, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_8010F710_modesel[arg0].unk_00, 1);
    espBankSet(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

void func_80106234_modesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010FE90_modesel); i++) {
        D_8010FE90_modesel[i].unk_00 = -1;
        D_8010FE90_modesel[i].unk_02 = -1;
    }
}

void func_80106280_modesel(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = func_8000B108_main(arg1, arg2);

    D_8010FE90_modesel[arg0].unk_00 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void func_8010631C_modesel(s32 arg0, s32 arg1, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(arg1);
    D_8010FE90_modesel[arg0].unk_02 = Hu3DMotionCreate(data, (s16)arg2);
    DataClose(data);
}

void func_801063A4_modesel(s32 arg0) {
    if (D_8010FE90_modesel[arg0].unk_00 != -1) {
        Hu3DModelKill(D_8010FE90_modesel[arg0].unk_00);
        D_8010FE90_modesel[arg0].unk_00 = -1;
    }
    if (D_8010FE90_modesel[arg0].unk_02 != -1) {
        Hu3DMotionKill(D_8010FE90_modesel[arg0].unk_02);
        D_8010FE90_modesel[arg0].unk_02 = -1;
    }
}

void func_80106454_modesel(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        func_801063A4_modesel(i);
    }
}

s16 func_8010648C_modesel(s32 arg0) {
    return D_8010FE90_modesel[arg0].unk_00;
}

s16 func_801064B0_modesel(s32 arg0) {
    return D_8010FE90_modesel[arg0].unk_02;
}

void func_801064D4_modesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_8010FE90_modesel[arg0].unk_1C = arg1;
    D_8010FE90_modesel[arg0].unk_20 = arg2;
    D_8010FE90_modesel[arg0].unk_24 = arg3;
    Hu3DModelRotSet(D_8010FE90_modesel[arg0].unk_00, arg1, arg2, arg3);
}

void func_8010653C_modesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_8010FE90_modesel[arg0].unk_04 = arg1;
    D_8010FE90_modesel[arg0].unk_08 = arg2;
    D_8010FE90_modesel[arg0].unk_0C = arg3;
    Hu3DModelPosSet(D_8010FE90_modesel[arg0].unk_00, arg1, arg2, arg3);
}

void func_801065B0_modesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_8010FEA0_modesel[arg0].unk_00 = arg1;
    D_8010FEA0_modesel[arg0].unk_04 = arg2;
    D_8010FEA0_modesel[arg0].unk_08 = arg3;
    Hu3DModelScaleSet(D_8010FE90_modesel[arg0].unk_00, arg1, arg2, arg3);
}

void func_80106618_modesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_8010FE90_modesel[arg0].unk_04;
    *arg2 = D_8010FE90_modesel[arg0].unk_08;
    *arg3 = D_8010FE90_modesel[arg0].unk_0C;
}

void func_8010666C_modesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_8010FE90_modesel[arg0].unk_1C;
    *arg2 = D_8010FE90_modesel[arg0].unk_20;
    *arg3 = D_8010FE90_modesel[arg0].unk_24;
}

void func_801066B4_modesel(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_8010FEA0_modesel[arg0].unk_00;
    *arg2 = D_8010FEA0_modesel[arg0].unk_04;
    *arg3 = D_8010FEA0_modesel[arg0].unk_08;
}

void func_801066FC_modesel(s32 arg0) {
    func_8001C258_main(D_8010FE90_modesel[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010673C_modesel(s32 arg0) {
    func_8001C258_main(D_8010FE90_modesel[arg0].unk_00, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010677C_modesel(s32 arg0, s32 arg1) {
    func_8001C814_main(D_8010FE90_modesel[arg0].unk_00, -1, arg1);
}

void func_801067C0_modesel(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    Hu3DMotionShiftSet(D_8010FE90_modesel[arg0].unk_00, D_8010FE90_modesel[arg1].unk_02, arg2, arg3, arg4);
}

void func_80106830_modesel(s32 arg0, s32 arg1) {
    func_8001C814_main(D_8010FE90_modesel[arg0].unk_00, arg1, 0);
}

void func_80106874_modesel(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())Hu3DMotionSpeedSet;

    setModelScale(D_8010FE90_modesel[arg0].unk_00);
}

void func_801068AC_modesel(s32 arg0, u32 arg1) {
    Hu3DMotionTimeSet(D_8010FE90_modesel[arg0].unk_00, arg1);
}

void func_80106910_modesel(s32 arg0) {
    while (Hu3DData[D_8010FE90_modesel[arg0].unk_00].motTime !=
           D_800CCF58_main[Hu3DData[D_8010FE90_modesel[arg0].unk_00].motId].unk02) {
        HuPrcVSleep();
    }
}

s32 func_801069B0_modesel(s32 arg0) {
    s16 modelId = D_8010FE90_modesel[arg0].unk_00;

    return Hu3DData[modelId].motTime == D_800CCF58_main[Hu3DData[modelId].motId].unk02;
}

void func_80106A38_modesel(s32 arg0, s32 arg1, s16 arg2) {
    s16 modelId = func_8010648C_modesel(arg0);
    s16 parentModelId = func_801064B0_modesel(arg1);

    Hu3DMotionSet(modelId, parentModelId);
    func_8001C814_main(modelId, -1, arg2);
}

void func_80106AA8_modesel(void) {
    // The original call omits the resource id.
    D_80110990_modesel = ((s16 (*)())func_8000B838_main)();
    D_80110992_modesel = espEntry(D_80110990_modesel, 0, 0);
    espAttrSet(D_80110992_modesel, 0x4000);
    espPosSet(D_80110992_modesel, 0xA0, 0x78);
}

void func_80106B0C_modesel(void) {
    espKill(D_80110992_modesel);
    HuSprAnimKill(D_80110990_modesel);
}

u32 func_80106B38_modesel(u32 arg0) {
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

#ifdef NON_MATCHING
// Code matches except for register allocation of the parameters and text.
void func_80106BA0_modesel(s32 index, u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s32 window;
    u32 text;

    switch (style) {
        case 1:
            text = func_80106B38_modesel(message);
            window = func_80106F38_modesel(text, x, y, width, height, style);
            break;
        case 2:
            text = func_80106B38_modesel(message);
            window = func_801070A0_modesel(text, x, y, width, height, style);
            break;
        case 3:
            text = func_80106B38_modesel(message);
            window = func_80107248_modesel(text, x, y, style);
            break;
        case 4:
            text = func_80106B38_modesel(message);
            window = func_80107314_modesel(text, x, y, style);
            break;
        case 5:
            text = func_80106B38_modesel(message);
            window = func_801073E0_modesel(text, x, y, style);
            break;
        case 0:
        default:
            text = func_80106B38_modesel(message);
            window = func_80106DEC_modesel(text, x, y, width, height, style);
            break;
    }
    if (text > 0x80000000U) {
        D_8011099C_modesel[index][0] = text;
    }
    D_80110998_modesel[index][0] = window;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106BA0_modesel);
#endif

s32 func_80106DEC_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    func_8005B63C_main(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    func_80060144_main(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    func_8005C154_main(window, 192, 192, 192);
    HuWinBGColSet(window, 0, 64, 64);
    HuWinMesColSet(window, 7);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 func_80106F38_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 4);

    func_8005B63C_main(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    HuWinBGTPLvlSet(window, 255);
    func_80060144_main(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_8005C154_main(window, 192, 192, 192);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 1);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 func_801070A0_modesel(u32 message, s16 x, s16 y, s16 width, s16 height, s16 style) {
    s16 window = HuWinCreate(x, y, width, height, 0, 8);

    func_8005B63C_main(window, -1, HUWIN_ATTR_NOCANCEL | HUWIN_ATTR_KEYLOCK);
    HuWinMesSpeedSet(window, 0);
    func_80060144_main(window);
    HuWinPriSet(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesPalSet(window, 5, 0, 176, 192);
    HuWinMesPalSet(window, 7, 255, 255, 255);
    HuWinMesPalSet(window, 0, 0, 0, 0);
    HuWinMesPalSet(window, 3, 0, 0, 0);
    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_8005C154_main(window, 192, 192, 0);
    HuWinBGColSet(window, 255, 255, 255);
    HuWinMesColSet(window, 6);
    HuWinHomeClear(window);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 func_80107248_modesel(u32 message, s16 x, s16 y, s16 style) {
    s16 window = func_80060880_main(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_80060C14_main(window, 1);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 func_80107314_modesel(u32 message, s16 x, s16 y, s16 style) {
    s16 window = func_80060880_main(x, y, 20);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    func_80060C14_main(window, 0);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

s32 func_801073E0_modesel(u32 message, s16 x, s16 y, s16 style) {
    s16 window = func_80060880_main(x, y, 19);

    HuWinMesPalSet(window, 2, 255, 64, 64);
    HuWinMesPalSet(window, 4, 96, 255, 64);
    HuWinMesPalSet(window, 6, 255, 255, 64);
    HuWinActivePlayerSet(window, HUWIN_PLAYER_1);
    func_80060C14_main(window, 0);
    HuWinMesSet(window, message, -1, -1);
    return window;
}

void func_801074AC_modesel(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80110998_modesel[i][0] = -1;
        D_8011099C_modesel[i][0] = 0;
    }
}

void func_801074F0_modesel(s32 arg0) {
    if (D_801109A0_modesel[arg0][0] == 3) {
        func_80060EA8_main(D_80110998_modesel[arg0][0], 1);
        HuWinExCleanup(D_80110998_modesel[arg0][0]);
    } else {
        HuWinDispOff(D_80110998_modesel[arg0][0]);
        HuWinKill(D_80110998_modesel[arg0][0]);
        D_80110998_modesel[arg0][0] = -1;
    }
    if (D_8011099C_modesel[arg0][0] != 0) {
        func_80019C00_main((void *)D_8011099C_modesel[arg0][0]);
        D_8011099C_modesel[arg0][0] = 0;
    }
}

void func_801075D4_modesel(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        if (D_80110998_modesel[i][0] != -1) {
            func_801074F0_modesel(i);
        }
    }
}

void func_80107638_modesel(s32 arg0, f32 arg1, f32 arg2) {
    HuWinScaleSet(D_80110998_modesel[arg0][0], arg1, arg2);
}

void func_80107668_modesel(s32 arg0, f32 arg1, f32 arg2) {
    HuWinPosSet(D_80110998_modesel[arg0][0], arg1, arg2);
}

void func_801076D0_modesel(s32 arg0) {
    HuWinDispOn(D_80110998_modesel[arg0][0]);
}

void func_80107700_modesel(s32 arg0) {
    HuWinDispOff(D_80110998_modesel[arg0][0]);
}

void func_80107730_modesel(s32 arg0, u32 message) {
    u32 text;

    HuWinHomeClear(D_80110998_modesel[arg0][0]);
    if (D_8011099C_modesel[arg0][0] != 0) {
        func_80019C00_main((void *)D_8011099C_modesel[arg0][0]);
        D_8011099C_modesel[arg0][0] = 0;
    }
    text = func_80106B38_modesel(message);
    if (text > 0x80000000U) {
        D_8011099C_modesel[arg0][0] = text;
    }
    HuWinMesSet(D_80110998_modesel[arg0][0], text, -1, -1);
}

void func_801077FC_modesel(s32 arg0, s8 arg1, u32 arg2) {
    func_800601BC_main(D_80110998_modesel[arg0][0], arg2, arg1);
}

s32 func_80107838_modesel(s32 arg0, s16 arg1, s32 arg2) {
    return HuWinChoiceGet(D_80110998_modesel[arg0][0], arg1, arg2);
}

s16 func_80107870_modesel(s32 arg0) {
    return D_80110998_modesel[arg0][0];
}

void func_8010788C_modesel(s32 arg0) {
    while (HuWinStatGet(D_80110998_modesel[arg0][0]) != 0) {
        HuPrcVSleep();
    }
}

void func_801078E0_modesel(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_8010791C_modesel(s32 arg0, s16 arg1) {
    HuWinPriSet(D_80110998_modesel[arg0][0], arg1);
}

u16 func_80107954_modesel(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & (A_BUTTON | B_BUTTON | START_BUTTON | R_TRIG)) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & Z_TRIG) {
            camera = Hu3DData[gCameraList[0].unk4].hmf->unkBC;
            sprintf(text, "POS:%4.2f,%4.2f,%4.2f", camera->unk08, camera->unk0C, camera->unk10);
            print8(16, 180, text);
            sprintf(text, "A T:%4.2f,%4.2f,%4.2f", camera->unk14, camera->unk18, camera->unk1C);
            print8(16, 190, text);
            sprintf(text, "U P:%4.2f,%4.2f,%4.2f", camera->unk20, camera->unk24, camera->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, "%d", value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_80107B08_modesel(void) {
    s16 i;
    s16 count;
    s16 pad;
    s16 player;

    for (i = 0; i < 4; i++) {
        GwPlayer[i].pad = 0xFF;
    }
    for (i = 0, count = 0; i < 4; i++) {
        if (CheckControllerRead(i)) {
            GwPlayer[count].pad = i;
            count++;
        }
    }
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].pad == 0xFF) {
            for (pad = 0; pad < 4; pad++) {
                for (player = 0; player < 4; player++) {
                    if (GwPlayer[player].pad == pad) {
                        break;
                    }
                }
                if (player == 4) {
                    break;
                }
            }
            GwPlayer[i].pad = pad;
        }
    }
}

void func_80107CB0_modesel(void) {
    func_80105C50_modesel();
    D_80110BDC_modesel = omAddPrcObj(func_80107CEC_modesel, 0x5000, 0x2000, 0);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F454_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107CEC_modesel);

void func_801088AC_modesel(void) {
    Hu3DCameraPerspectiveSet(0, D_8010F2BC_modesel, D_8010F2C0_modesel, D_8010F2C4_modesel);
    while (1) {
        func_80108A94_modesel(0);
        HuPrcVSleep();
    }
}

void func_801088F8_modesel(void) {
    do {
        func_80108F8C_modesel(&D_80110BE8_modesel.pos, &D_80110BE8_modesel.at, &D_80110BE8_modesel.up);
        HuPrcVSleep();
    } while (1);
}

void func_8010893C_modesel(Process *arg0) {
    Vec pos;
    Vec at;
    Vec up;

    func_80108AE0_modesel(&pos, &at, &up);
    func_80108F8C_modesel(&pos, &at, &up);
    omDelPrcObj(arg0);
}

Process *func_8010899C_modesel(void) {
    func_80108AE0_modesel(&D_80110BE8_modesel.pos, &D_80110BE8_modesel.at, &D_80110BE8_modesel.up);
    return omAddPrcObj(func_801088F8_modesel, 0x5000, 0x1800, 0);
}

void func_801089DC_modesel(Vec *pos, Vec *at, Vec *up) {
    HuVecCopy3F(pos, &D_80110BE8_modesel.pos);
    HuVecCopy3F(at, &D_80110BE8_modesel.at);
    HuVecCopy3F(up, &D_80110BE8_modesel.up);
}

void func_80108A34_modesel(Vec *pos, Vec *at, Vec *up) {
    HuVecCopy3F(&D_80110BE8_modesel.pos, pos);
    HuVecCopy3F(&D_80110BE8_modesel.at, at);
    HuVecCopy3F(&D_80110BE8_modesel.up, up);
}

void func_80108A94_modesel(s32 arg0) {
    Vec pos;
    Vec at;
    Vec up;

    func_80108AE0_modesel(&pos, &at, &up);
    func_80108F8C_modesel(&pos, &at, &up);
}

s32 func_80108AE0_modesel(Vec *pos, Vec *at, Vec *up) {
    HmfData_UnkBC *cam;
    f32 angle;
    f32 dx, dy, dz;
    f32 upX, upY, upZ;
    f32 length;

    cam = Hu3DData[gCameraList->unk4].hmf->unkBC;
    pos->x = cam->unk08;
    pos->y = cam->unk0C;
    pos->z = cam->unk10;
    at->x = cam->unk14;
    at->y = cam->unk18;
    at->z = cam->unk1C;
    angle = -90.0f;
    dx = at->x - pos->x;
    dy = at->y - pos->y;
    dz = at->z - pos->z;
    length = dx * dx + dy * dy + dz * dz;
    length = HuSqrtf(length);
    dx /= length;
    dy /= length;
    dz /= length;
    upX = dy * dz - dz * (dy + 1.0f);
    upY = dz * dx - dz * dx;
    upZ = dx * (dy + 1.0f) - dy * dx;
    up->x = upX * (dx * dx + (1.0f - dx * dx) * cosdf(angle)) +
            upY * (dx * dy * (1.0f - cosdf(angle)) - dz * sindf(angle)) +
            upZ * (dx * dz * (1.0f - cosdf(angle)) + dy * sindf(angle));
    up->y = upX * (dx * dy * (1.0f - cosdf(angle)) + dz * sindf(angle)) +
            upY * (dy * dy + (1.0f - dy * dy) * cosdf(angle)) +
            upZ * (dy * dz * (1.0f - cosdf(angle)) - dx * sindf(angle));
    up->z = upX * (dx * dz * (1.0f - cosdf(angle)) - dy * sindf(angle)) +
            upY * (dy * dz * (1.0f - cosdf(angle)) + dx * sindf(angle)) +
            upZ * (dz * dz + (1.0f - dz * dz) * cosdf(angle));
    return 1;
}

void func_80108F8C_modesel(Vec *pos, Vec *at, Vec *up) {
    Hu3DCameraPosSetV(0, pos, at, up);
    Hu3DCamUpdateMtx(0);
}

void func_80108FC4_modesel(void) {
    D_80110C10_modesel.obj = NULL;
}

void func_80108FD0_modesel(omObjData *obj) {
    Vec camPos;
    Vec at;
    Vec up;
    Vec start;
    Vec end;
    Vec pos;
    f32 t;
    f32 s;

    HuVecCopy3F(&start, &D_80110C10_modesel.unk_10);
    HuVecCopy3F(&end, &D_80110C10_modesel.unk_1C);
    t = (f32)D_80110C10_modesel.unk_04 / (f32)D_80110C10_modesel.unk_08;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        s = 1.0f;
    } else {
        s = sindf(t * 90.0f);
    }
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * s, start.y + (end.y - start.y) * s,
                 start.z + (end.z - start.z) * s);
    func_801089DC_modesel(&camPos, &at, &up);
    if (D_80110C10_modesel.unk_04 > D_80110C10_modesel.unk_08) {
        omDelObj(obj);
        func_80108A34_modesel(&camPos, &end, &up);
        D_80110C10_modesel.obj = NULL;
    } else {
        D_80110C10_modesel.unk_04++;
        func_80108A34_modesel(&camPos, &pos, &up);
    }
}

void func_80109154_modesel(void) {
    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    D_80110C10_modesel.obj = NULL;
}

omObjData *func_80109188_modesel(s32 arg0, s32 arg1) {
    omObjData *obj;
    Vec pos;
    Vec at;
    Vec up;
    Vec target;

    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    obj = omAddObj(6, 0, 0, -1, func_80108FD0_modesel);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_80110C10_modesel.obj = obj;
    D_80110C10_modesel.unk_04 = 0;
    D_80110C10_modesel.unk_08 = arg1;
    D_80110C10_modesel.unk_0C = arg0;
    func_801089DC_modesel(&pos, &at, &up);
    HuVecCopyXYZ(&D_80110C10_modesel.unk_10, at.x, at.y, at.z);
    if (arg0 < 0) {
        target.x = 0.0f;
    } else {
        func_8010E138_modesel(arg0, &target.x, &target.y, &target.z);
    }
    target.y = at.y;
    target.z = at.z;
    HuVecCopyXYZ(&D_80110C10_modesel.unk_1C, target.x, target.y, target.z);
    return obj;
}

void func_80109290_modesel(omObjData *obj) {
    Vec pos;
    Vec at;
    s32 timer = D_80110C38_modesel.unk_04;
    f32 shake;

    HuVecCopy3F(&pos, &D_80110C38_modesel.pos);
    HuVecCopy3F(&at, &D_80110C38_modesel.at);
    if (timer > 32) {
        omDelObj(obj);
        D_80110C38_modesel.unk_00 = NULL;
        timer = 0;
    } else {
        D_80110C38_modesel.unk_08 = ~D_80110C38_modesel.unk_08;
        if (D_80110C38_modesel.unk_08 != 0) {
            shake = rand8();
        } else {
            shake = -(f32)rand8();
        }
        shake = shake * (1.0f / 255.0f) * ((1.0f - timer * (1.0f / 32.0f)) * 0.8f + 0.2f);
        pos.y += shake * 40.0f;
        at.y += shake * 40.0f;
    }
    func_80108A34_modesel(&pos, &at, &D_80110C38_modesel.up);
    D_80110C38_modesel.unk_04 = timer + 1;
}

void func_80109408_modesel(void) {
    if (D_80110C38_modesel.unk_00 != NULL) {
        omDelObj(D_80110C38_modesel.unk_00);
        D_80110C38_modesel.unk_00 = NULL;
    }
}

void func_80109444_modesel(void) {
    D_80110C38_modesel.unk_00 = omAddObj(6, 0, 0, -1, func_80109290_modesel);
    D_80110C38_modesel.unk_04 = 0;
    func_801089DC_modesel(&D_80110C38_modesel.pos, &D_80110C38_modesel.at, &D_80110C38_modesel.up);
    D_80110C38_modesel.unk_08 = 1;
}

f32 func_801094A8_modesel(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return -(atan2df(arg3 - arg1, arg2 - arg0) - 90.0f);
}

#ifdef NON_MATCHING
void func_801094F0_modesel(Vec *from, Vec *to, f32 t, Vec *out) {
    f32 fromAngle;
    f32 toAngle;
    f32 endAngle;
    f32 angle;

    fromAngle = func_801094A8_modesel(0.0f, 0.0f, from->x, from->z);
    if (fromAngle < 0.0f) {
        fromAngle += 360.0f;
    }
    toAngle = func_801094A8_modesel(0.0f, 0.0f, to->x, to->z);
    if (toAngle < 0.0f) {
        toAngle += 360.0f;
    }
    if (-from->z * to->x + from->x * to->z > 0.0f) {
        if (toAngle - fromAngle < 0.0f) {
            endAngle = toAngle;
        } else {
            endAngle = toAngle - 360.0f;
        }
        angle = (endAngle - fromAngle) * t + fromAngle;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
    } else {
        if (0.0f < toAngle - fromAngle) {
            endAngle = toAngle;
        } else {
            endAngle = toAngle + 360.0f;
        }
        angle = (endAngle - fromAngle) * t + fromAngle;
        if (360.0f < angle) {
            angle -= 360.0f;
        }
    }
    out->x = sindf(angle);
    out->y = 0.0f;
    out->z = cosdf(angle);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801094F0_modesel);
#endif

void func_801096D4_modesel(omObjData *obj) {
    Vec pos, at, up, direction, startAt, endAt, startDir, endDir;
    f32 t, clamped, startLength, angleT;

    t = (f32)D_80110C10_modesel.unk_04 / D_80110C10_modesel.unk_08;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 1.0f) {
        clamped = 1.0f;
    } else {
        clamped = t;
    }
    func_801089DC_modesel(&pos, &at, &up);
    HuVecCopy3F(&startAt, &D_80110C10_modesel.unk_10);
    HuVecCopy3F(&endAt, &D_80110C10_modesel.unk_1C);
    HuVecCopyXYZ(&at, (endAt.x - startAt.x) * clamped + startAt.x,
                 (endAt.y - startAt.y) * clamped + startAt.y,
                 (endAt.z - startAt.z) * clamped + startAt.z);
    HuVecCopyXYZ(&startDir, startAt.x - pos.x, 0.0f, startAt.z - pos.z);
    HuVecCopyXYZ(&endDir, endAt.x - pos.x, 0.0f, endAt.z - pos.z);
    angleT = sindf(clamped * 90.0f);
    func_801094F0_modesel(&startDir, &endDir, angleT, &direction);
    startLength = HuVecGetLength3F(&startDir);
    t = (HuVecGetLength3F(&endDir) - startLength) * angleT + startLength;
    HuVecCopyXYZ(&at, t * direction.x + pos.x, (endAt.y - startAt.y) + startAt.y, t * direction.z + pos.z);
    if (D_80110C10_modesel.unk_04 > D_80110C10_modesel.unk_08) {
        omDelObj(obj);
        func_80108A34_modesel(&pos, &D_80110C10_modesel.unk_1C, &up);
        D_80110C10_modesel.obj = NULL;
    } else {
        D_80110C10_modesel.unk_04++;
        func_80108A34_modesel(&pos, &at, &up);
    }
}

omObjData *func_80109968_modesel(s32 arg0, s32 arg1) {
    omObjData *obj;
    Vec pos;
    Vec at;
    Vec up;

    if (D_80110C10_modesel.obj != NULL) {
        omDelObj(D_80110C10_modesel.obj);
    }
    obj = omAddObj(6, 0, 0, -1, func_801096D4_modesel);
    obj->work[0] = 0;
    obj->work[1] = 0;
    D_80110C10_modesel.obj = obj;
    D_80110C10_modesel.unk_04 = 0;
    D_80110C10_modesel.unk_08 = arg1;
    D_80110C10_modesel.unk_0C = arg0;
    func_801089DC_modesel(&pos, &at, &up);
    HuVecCopy3F(&D_80110C10_modesel.unk_10, &at);
    if (arg0 < 0) {
        at.x = 0.0f;
    } else {
        func_8010E138_modesel(arg0, &at.x, &at.y, &at.z);
    }
    HuVecCopyXYZ(&D_80110C10_modesel.unk_1C, at.x, at.y, at.z);
    return obj;
}

s32 func_80109A58_modesel(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;

    stickX = D_800CBB6E_main[arg0];
    stickY = D_800D20A1_main[arg0];
    if (D_8010F2C8_modesel != 0) {
        if ((stickX == 0) & (stickY == 0)) {
            D_8010F2C8_modesel = 0;
        }
        return 0;
    }
    if ((stickX != 0) | (stickY != 0)) {
        absX = __builtin_abs(stickX);
        absY = __builtin_abs(stickY);
        if (absY < absX) {
            if (absX > absY * 2) {
                if (stickX < 0) {
                    D_8010F2C8_modesel = 0x200;
                } else {
                    D_8010F2C8_modesel = 0x100;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    D_8010F2C8_modesel = 0xA00;
                } else {
                    D_8010F2C8_modesel = 0x900;
                }
            } else {
                if (stickX < 0) {
                    D_8010F2C8_modesel = 0x600;
                } else {
                    D_8010F2C8_modesel = 0x500;
                }
            }
        } else {
            if (absY > absX * 2) {
                if (stickY < 0) {
                    D_8010F2C8_modesel = 0x400;
                } else {
                    D_8010F2C8_modesel = 0x800;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    D_8010F2C8_modesel = 0xA00;
                } else {
                    D_8010F2C8_modesel = 0x900;
                }
            } else {
                if (stickX < 0) {
                    D_8010F2C8_modesel = 0x600;
                } else {
                    D_8010F2C8_modesel = 0x500;
                }
            }
        }
    }
    return D_8010F2C8_modesel;
}

void func_80109B74_modesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80110C68_modesel[i].unk_08 = NULL;
        D_80110C68_modesel[i].unk_04 = 0;
        D_80110C68_modesel[i].unk_00 = 0;
    }
}

#ifdef NON_MATCHING
// The float multiply operands for the sindf argument are emitted in the opposite order.
void func_80109BC0_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 wave = sindf(timer * (360.0f / 255.0f));

    func_8010648C_modesel(index);
    func_8010B75C_modesel(index, 0.0f, wave * 8.0f + 8.0f + 8.0f, 0.0f, wave * 16.0f + 20.0f);
    obj->work[1] = timer + 4;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109BC0_modesel);
#endif

void func_80109C8C_modesel(s32 arg0) {
    s32 i = arg0 - 7;

    if (D_80110C68_modesel[i].unk_08 != NULL) {
        omDelObj(D_80110C68_modesel[i].unk_08);
    }
    D_80110C68_modesel[i].unk_08 = NULL;
}

omObjData *func_80109CEC_modesel(s32 arg0) {
    s32 i = arg0 - 7;
    omObjData *obj;

    if (D_80110C68_modesel[i].unk_08 != NULL) {
        func_80109C8C_modesel(arg0);
    }
    obj = omAddObj(6, 0, 0, -1, func_80109BC0_modesel);
    D_80110C68_modesel[i].unk_08 = obj;
    obj->work[0] = arg0;
    obj->work[1] = rand8();
    D_80110C68_modesel[i].unk_00 = 0;
    D_80110C68_modesel[i].unk_04 = 0;
    return obj;
}

#ifdef NON_MATCHING
// Float register allocation differs for the clamped scale.
void func_80109DB8_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 i = index - 7;
    s32 timer = obj->work[1];
    f32 t = 1.0f - timer * 0.1f;
    f32 scale = (t < 0.0f) ? 0.0f : t;

    func_8010B75C_modesel(index, 0.0f, (D_80110C68_modesel[i].unk_0C.y - 10.0f) * scale + 10.0f, 0.0f, 0.0f);
    if (timer < 10) {
        timer++;
    }
    obj->work[1] = timer;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109DB8_modesel);
#endif

omObjData *func_80109E90_modesel(s32 arg0) {
    s32 i = arg0 - 7;
    omObjData *obj = D_80110C68_modesel[i].unk_08;
    f32 wave;

    if (obj != NULL) {
        wave = (s32)obj->work[1];
        wave = sindf(wave * (360.0f / 255.0f));
        HuVecCopyXYZ(&D_80110C68_modesel[i].unk_0C, 0.0f, wave * 8.0f + 8.0f + 8.0f, 0.0f);
        omDelObj(D_80110C68_modesel[i].unk_08);
    } else {
        HuVecCopyXYZ(&D_80110C68_modesel[i].unk_0C, 0.0f, 0.0f, 0.0f);
    }
    D_80110C68_modesel[i].unk_08 = omAddObj(6, 0, 0, -1, func_80109DB8_modesel);
    D_80110C68_modesel[i].unk_04 = 0;
    // Writes to the previous (possibly deleted) object rather than the new one.
    obj->work[0] = arg0;
    return obj;
}

// Toggles the spinner's model when work[1] wraps over its 0..200 range: the
// second argument to func_8010677C_modesel is the model's visibility.
void func_80109FCC_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];

    if (timer == 200) {
        func_8010677C_modesel(index, 0);
    } else if (timer == 0) {
        func_8010677C_modesel(index, 1);
    }
    timer += 4;
    obj->work[1] = timer;
}

void func_8010A020_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_80109FCC_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
}

void func_8010A068_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * (1.0f / 255.0f);
    Vec pos;
    f32 shadowY;

    pos.x = D_8010F2CC_modesel[index - 7].x;
    pos.y = D_8010F2CC_modesel[index - 7].y;
    pos.z = D_8010F2CC_modesel[index - 7].z;
    pos.y -= t * 400.0f;
    func_8010653C_modesel(index, 0.0f, 0.0f, 0.0f);
    shadowY = pos.y + 20.0f - 12.0f;
    if (shadowY < 0.0f) {
        shadowY = 0.0f;
    }
    func_8010B790_modesel(index, pos.x, pos.y, pos.z, shadowY);
    func_8010B804_modesel(index, 0);
    func_8010B824_modesel(index);
    timer += 20;
    if (timer == 100) {
        // Empty in the original; the comparison is still emitted.
    } else if (timer >= 256) {
        omDelObj(obj);
        func_801066FC_modesel(index);
    }
    obj->work[1] = timer;
}

void func_8010A1C4_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    Vec pos;
    f32 shadowY;

    pos.x = D_8010F2CC_modesel[index - 7].x;
    pos.y = D_8010F2CC_modesel[index - 7].y;
    pos.z = D_8010F2CC_modesel[index - 7].z;
    func_8010653C_modesel(index, 0.0f, 0.0f, 0.0f);
    shadowY = pos.y + 20.0f - 12.0f;
    if (shadowY < 0.0f) {
        shadowY = 0.0f;
    }
    func_8010B790_modesel(index, pos.x, pos.y, pos.z, shadowY);
    func_8010B804_modesel(index, 0);
    func_8010B824_modesel(index);
    timer++;
    if (timer > 20) {
        HuAudFXPlay(0x2E2);
        obj->func = func_8010A068_modesel;
        obj->work[1] = 0;
    }
    obj->work[1] = timer;
}

void func_8010A2E8_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    Vec pos;

    pos.x = D_8010F2CC_modesel[index - 7].x;
    pos.y = D_8010F2CC_modesel[index - 7].y;
    pos.z = D_8010F2CC_modesel[index - 7].z;
    func_8010653C_modesel(index, 0.0f, 0.0f, 0.0f);
    func_8010B790_modesel(index, pos.x, pos.y, pos.z, pos.y + 20.0f - 12.0f);
    func_8010B940_modesel(index, 35.5f);
    func_8010B824_modesel(index);
    timer += 20;
    if (timer >= 256) {
        timer = 0;
        D_8010F2CC_modesel[index - 7].x = pos.x;
        D_8010F2CC_modesel[index - 7].y = pos.y;
        D_8010F2CC_modesel[index - 7].z = pos.z;
        obj->func = func_8010A1C4_modesel;
    }
    obj->work[1] = timer;
}

void func_8010A420_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * (1.0f / 255.0f);
    f32 s = (t < 1.0) ? t : 1.0f;
    f32 u = s * -5.0f * (s - 1.2f);
    Vec start;
    Vec end;
    Vec pos;

    start.x = D_8010F2CC_modesel[index - 7].x;
    start.y = D_8010F2CC_modesel[index - 7].y;
    start.z = D_8010F2CC_modesel[index - 7].z;
    HuVecCopyXYZ(&end, 0.0f, 200.0f, 300.0f);
    pos.x = start.x + (end.x - start.x) * t;
    pos.y = start.y + (end.y - start.y) * u;
    pos.z = start.z + (end.z - start.z) * t;
    func_8010653C_modesel(index, 0.0f, 0.0f, 0.0f);
    func_8010B790_modesel(index, pos.x, pos.y, pos.z, pos.y + 20.0f - 12.0f);
    func_8010B940_modesel(index, 35.5f);
    func_8010B824_modesel(index);
    timer += 12;
    if (timer >= 256) {
        obj->work[1] = 0;
        D_8010F2CC_modesel[index - 7].x = pos.x;
        D_8010F2CC_modesel[index - 7].y = pos.y;
        D_8010F2CC_modesel[index - 7].z = pos.z;
        obj->func = func_8010A2E8_modesel;
    } else {
        obj->work[1] = timer;
    }
}

void func_8010A62C_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A420_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
}

#ifdef NON_MATCHING
void func_8010A674_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 bob;
    f32 angle;
    f32 diff;
    Vec pos;
    Vec base;
    Vec camPos;
    Vec camAt;
    Vec camUp;
    f32 x;
    f32 y;
    f32 z;

    bob = sindf(timer * 1.4117647f);
    HuVecCopy3F(&base, &D_80110CB0_modesel);
    HuVecCopyXYZ(&pos, base.x, base.y + bob * 5.0f * 5.0f, base.z);
    func_8010653C_modesel(index, pos.x, pos.y, pos.z);
    timer++;
    func_801089DC_modesel(&camPos, &camAt, &camUp);
    func_80106618_modesel(10, &x, &y, &z);
    angle = D_80110CD4_modesel;
    diff = func_8010EC74_modesel(camPos.x - x, camPos.z - z);
    diff -= angle;
    if (diff < -2.0f) {
        angle -= 2.0f;
    }
    angle = (angle < 0.0f) ? angle + 360.0f : angle;
    angle = (diff > 2.0f) ? angle + 2.0f : angle;
    angle = (angle > 360.0f) ? angle - 360.0f : angle;
    D_80110CD4_modesel = angle;
    func_801064D4_modesel(10, 0.0f, angle, 0.0f);
    obj->work[1] = timer;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A674_modesel);
#endif

void func_8010A84C_modesel(omObjData *obj) {
    Vec pos;
    Vec start;
    Vec end;
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * 0.05f;
    f32 s;
    f32 u;

    s = (1.0f < t) ? 1.0f : t * t;
    u = s * -3.0f * (s - 1.3333334f);
    HuVecCopy3F(&start, &D_80110CB0_modesel);
    HuVecCopy3F(&end, &D_80110CBC_modesel);
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * s, start.y + (end.y - start.y) * u,
                 start.z + (end.z - start.z) * s);
    func_8010653C_modesel(index, pos.x, pos.y, pos.z);
    if (timer > 20) {
        obj->func = func_8010A674_modesel;
        HuVecCopy3F(&D_80110CB0_modesel, &pos);
        timer = 0;
    } else {
        timer++;
    }
    obj->work[1] = timer;
}

omObjData *func_8010A9B8_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A84C_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    func_80106618_modesel(arg0, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    HuVecCopyXYZ(&D_80110CBC_modesel, 0.0f, 25.0f, 300.0f);
    D_80110CD4_modesel = 0.0f;
    return obj;
}

omObjData *func_8010AA48_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A674_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    func_80106618_modesel(arg0, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    D_80110CD4_modesel = 0.0f;
    return obj;
}

void func_8010AAC0_modesel(omObjData *obj) {
    Vec start;
    Vec end;
    Vec pos;
    s32 index = obj->work[0];
    s32 timer = obj->work[1];
    f32 t = timer * 0.05f;

    HuVecCopy3F(&start, &D_80110CB0_modesel);
    HuVecCopy3F(&end, &D_80110CBC_modesel);
    HuVecCopyXYZ(&pos, start.x + (end.x - start.x) * t, start.y + (end.y - start.y) * t,
                 start.z + (end.z - start.z) * t);
    func_8010653C_modesel(index, pos.x, pos.y, pos.z);
    if (timer < 21) {
        timer++;
    }
    obj->work[1] = timer;
}

omObjData *func_8010ABB4_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010AAC0_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    func_80106618_modesel(arg0, &D_80110CB0_modesel.x, &D_80110CB0_modesel.y, &D_80110CB0_modesel.z);
    HuVecCopyXYZ(&D_80110CBC_modesel, 0.0f, -400.0f, 300.0f);
    return obj;
}

void func_8010AC3C_modesel(void) {
    Vec modelPos;
    Vec pos;
    Vec at;
    Vec up;

    func_80106618_modesel(0xA, &modelPos.x, &modelPos.y, &modelPos.z);
    func_801089DC_modesel(&pos, &at, &up);
    func_801064D4_modesel(0xA, 0.0f, func_8010EC74_modesel(pos.x - modelPos.x, pos.z - modelPos.z), 0.0f);
}

#ifdef NON_MATCHING
// The target keeps the model id 10 in a saved register across calls, and float temporaries differ.
void func_8010ACA8_modesel(omObjData *obj) {
    Vec pos;
    s32 model = 10;
    s32 timer = obj->work[0];
    f32 t = timer * (1.0f / 255.0f);

    pos.x = D_80110CD8_modesel[1].x;
    pos.y = D_80110CD8_modesel[1].y - t * 400.0f;
    pos.z = D_80110CD8_modesel[1].z;
    func_8010653C_modesel(model, pos.x, pos.y, pos.z);
    func_8010AC3C_modesel();
    timer += 20;
    if (timer >= 256) {
        omDelObj(obj);
        func_801066FC_modesel(model);
    }
    obj->work[0] = timer;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010ACA8_modesel);
#endif

void func_8010AD74_modesel(omObjData *obj) {
    s32 timer = obj->work[0];

    func_8010AC3C_modesel();
    timer++;
    if (timer >= 31) {
        obj->func = func_8010ACA8_modesel;
        timer = 0;
    }
    obj->work[0] = timer;
}

void func_8010ADC8_modesel(omObjData *obj) {
    Vec pos;
    s32 timer = obj->work[0];
    f32 t = timer * (1.0f / 255.0f);
    f32 s = (t < 1.0) ? t : 1.0f;

    pos.x = (D_80110CD8_modesel[1].x - D_80110CD8_modesel[0].x) * t + D_80110CD8_modesel[0].x;
    pos.y = (D_80110CD8_modesel[1].y - D_80110CD8_modesel[0].y) * s + (1.0f - (s - 0.5f) * 4.0f * (s - 0.5f)) * 80.0f +
            D_80110CD8_modesel[0].y;
    pos.z = (D_80110CD8_modesel[1].z - D_80110CD8_modesel[0].z) * t + D_80110CD8_modesel[0].z;
    func_8010653C_modesel(10, pos.x, pos.y, pos.z);
    func_8010AC3C_modesel();
    timer += 12;
    if (timer >= 256) {
        obj->func = func_8010AD74_modesel;
        timer = 0;
    }
    obj->work[0] = timer;
}

omObjData *func_8010AF18_modesel(void) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010ADC8_modesel);

    func_80106618_modesel(0xA, &D_80110CD8_modesel[0].x, &D_80110CD8_modesel[0].y, &D_80110CD8_modesel[0].z);
    HuVecCopyXYZ(&D_80110CD8_modesel[1], 0.0f, 200.0f, 300.0f);
    obj->work[0] = 0;
    return obj;
}

void func_8010AF90_modesel(void) {
    s16 modelId;

    func_80106280_modesel(0, 0xD0000, 0x2002A9);
    func_8010653C_modesel(0, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(0, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(0, 0);
    func_8010677C_modesel(0, 1);

    func_80106280_modesel(1, 0xD0001, 0x229);
    func_8010653C_modesel(1, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(1, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(1, 0);
    func_8010677C_modesel(1, 1);

    func_80106280_modesel(2, 0xD0002, 0x6A9);
    func_8010653C_modesel(2, 0.0f, 0.0f, -585.0f);
    func_801065B0_modesel(2, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(2, 0);
    func_8010677C_modesel(2, 1);
    {
        char *names[] = { "mario", "luigi", "peach", "yoshi", "wario", "donkey" };
        HmfMotionNode *node;
        s32 i;

        modelId = func_8010648C_modesel(2);
        for (i = 0; i < 6; i++) {
            if (func_800E905C_minigame(i) < 0) {
                node = func_8001D33C_main(modelId, names[i]);
                func_80088800_main(node->unk58, 0.0f, -4000.0f, 0.0f);
            }
        }
    }

    {
        Vec pos;

        HuVecCopyXYZ(&pos, 0.0f, 0.0f, -200.0f);
        pos.z = pos.z - 8.0f - 2.5f;
        func_80106280_modesel(3, 0xD0003, 0x7A9);
        func_8010653C_modesel(3, pos.x, pos.y, pos.z);
    }
    func_801065B0_modesel(3, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(3, 0);
    func_8010677C_modesel(3, 1);

    func_80106280_modesel(4, 0xD0004, 0xAA9);
    func_8010653C_modesel(4, 0.0f, 0.0f, 0.0f);
    func_801065B0_modesel(4, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(4, 0);
    func_8010677C_modesel(4, 1);

    func_80106280_modesel(5, 0xD0005, 0x6A9);
    func_8010653C_modesel(5, 325.0f, 9.5f, 45.0f);
    func_801065B0_modesel(5, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(5, 0);
    func_8010677C_modesel(5, 1);
    D_80110BD4_modesel = func_8001D33C_main(func_8010648C_modesel(5), "taiho");

    func_8010631C_modesel(0x11, 0xD000B, -1);

    func_80106280_modesel(0x12, 0xD000C, 0xAA9);
    func_8010653C_modesel(0x12, 275.0f, 97.0f, 122.5f);
    func_801065B0_modesel(0x12, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(0x12, 0);
    func_8010677C_modesel(0x12, 2);
    func_801066FC_modesel(0x12);

    func_80106280_modesel(7, 0xD0007, 0xAA9);
    func_8010653C_modesel(7, 250.0f, 25.0f, 355.0f);
    func_801065B0_modesel(7, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(7, 1);
    func_80109CEC_modesel(7);
    modelId = func_8010648C_modesel(7);
    D_80110B18_modesel[0].star = func_8001D33C_main(modelId, "star_red");
    D_80110B18_modesel[0].shadow = func_8001D33C_main(modelId, "red_kage");
    func_8010B804_modesel(7, 0);
    func_8010B75C_modesel(7, 0.0f, 16.0f, 0.0f, 20.0f);

    func_80106280_modesel(8, 0xD0008, 0xAA9);
    func_8010653C_modesel(8, -250.0f, 25.0f, 355.0f);
    func_801065B0_modesel(8, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(8, 1);
    func_80109CEC_modesel(8);
    modelId = func_8010648C_modesel(8);
    D_80110B18_modesel[1].star = func_8001D33C_main(modelId, "star_blue");
    D_80110B18_modesel[1].shadow = func_8001D33C_main(modelId, "blue_kage");
    func_8010B804_modesel(8, 0);
    func_8010B75C_modesel(8, 0.0f, 0.0f, 16.0f, 20.0f);

    func_80106280_modesel(9, 0xD0009, 0x6A9);
    func_8010653C_modesel(9, 0.0f, 25.0f, 70.0f);
    func_801065B0_modesel(9, 1.0f, 1.0f, 1.0f);
    func_8010677C_modesel(9, 1);
    func_80109CEC_modesel(9);
    modelId = func_8010648C_modesel(9);
    D_80110B18_modesel[2].star = func_8001D33C_main(modelId, "star_yellow");
    D_80110B18_modesel[2].shadow = func_8001D33C_main(modelId, "yellow_kage");
    func_8010B75C_modesel(9, 0.0f, 0.0f, 16.0f, 20.0f);

    func_80106280_modesel(10, 0xA0122, 0xAA9);
    if (GwStory.unk0 == 12 && func_800465D0_main() == 0) {
        func_8010653C_modesel(10, -300.0f, 225.0f, 300.0f);
        func_8010673C_modesel(10);
    } else {
        func_8010653C_modesel(10, 0.0f, -75.0f, 300.0f);
        func_801066FC_modesel(10);
    }
    func_801065B0_modesel(10, 1.0f, 1.0f, 1.0f);
    func_801068AC_modesel(10, 0);
    func_800461B4_main(func_8010648C_modesel(10));

    func_8010631C_modesel(0x13, 0xA0125, 0);
    func_8010631C_modesel(0x14, 0xA0123, 0);

    func_80106280_modesel(11, 0xD000D, 0x200009);
    func_801068AC_modesel(11, 0);
    func_8010677C_modesel(11, 1);

    func_80106280_modesel(12, 0xD000E, 0x2002B9);
    func_801068AC_modesel(12, 0);
    func_8010677C_modesel(12, 1);

    func_80106280_modesel(13, 0xD000F, 0x2002B9);
    func_801068AC_modesel(13, 0);
    func_8010677C_modesel(13, 1);
}

void func_8010B6B0_modesel(void) {
    func_801063A4_modesel(0);
    func_801063A4_modesel(1);
    func_801063A4_modesel(2);
    func_801063A4_modesel(3);
    func_801063A4_modesel(4);
    func_801063A4_modesel(0x11);
    func_801063A4_modesel(0x12);
    func_801063A4_modesel(5);
    func_801063A4_modesel(7);
    func_801063A4_modesel(8);
    func_801063A4_modesel(9);
    func_80046558_main(func_8010648C_modesel(0xA));
    func_801063A4_modesel(0xA);
    omDelObj(D_80110BD0_modesel);
    func_80109154_modesel();
    func_801063A4_modesel(0xB);
    func_801063A4_modesel(0xC);
}

void func_8010B75C_modesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_8010B790_modesel(arg0, arg1, arg2, arg3, arg4);
    func_8010B824_modesel(arg0);
}

void func_8010B790_modesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    s32 index = arg0 - 7;

    D_80110B18_modesel[index].x = arg1;
    D_80110B18_modesel[index].y = arg2;
    D_80110B18_modesel[index].z = arg3;
    D_80110B18_modesel[index].scale = arg4 < 0.0f ? 0.0f : arg4;
}

void func_8010B804_modesel(s32 arg0, s32 arg1) {
    D_80110B18_modesel[arg0 - 7].rot.word = arg1;
}

void func_8010B824_modesel(s32 arg0) {
    s32 index = arg0 - 7;
    f32 shadowY;

    func_80088800_main(D_80110B18_modesel[index].star->unk58, D_80110B18_modesel[index].x,
                       D_80110B18_modesel[index].y, D_80110B18_modesel[index].z);
    func_800185A4_main(D_80110B18_modesel[index].star->unk58, D_80110B18_modesel[index].rot.angle);
    shadowY = (8.0f < D_80110B18_modesel[index].y) ? 4.0f : -200.0f;
    func_80088800_main(D_80110B18_modesel[index].shadow->unk58, D_80110B18_modesel[index].x, shadowY,
                       D_80110B18_modesel[index].z);
    func_800185A4_main(D_80110B18_modesel[index].shadow->unk58, D_80110B18_modesel[index].rot.angle);
}

void func_8010B940_modesel(s32 arg0, f32 arg1) {
    s32 index = arg0 - 7;

    if (360.0f < arg1) {
        arg1 = 360.0f;
    }
    D_80110B18_modesel[index].rot.angle += arg1;
    if (360.0f < D_80110B18_modesel[index].rot.angle) {
        D_80110B18_modesel[index].rot.angle -= 360.0f;
    }
}

void func_8010B9C4_modesel(void) {
    s16 modelId = func_8010648C_modesel(omovlevtno != 1 ? 0xB : 0xD);

    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    func_80013320_main(modelId, 0);
    Hu3DMotionTimeSet(modelId, 0.0f);
    func_8001C814_main(modelId, 1, 1);
    func_80108AE0_modesel(&D_80110BE8_modesel.pos, &D_80110BE8_modesel.at, &D_80110BE8_modesel.up);
    omAddPrcObj(func_801088AC_modesel, 0x5000, 0x2000, 0);
}

s32 func_8010BA70_modesel(void) {
    s32 cur = 10;
    s32 buttons;
    s32 result;
    s32 confirm;
    s16 modelId;

    if (func_800465D0_main() == 1) {
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            cur = 5;
            func_80107730_modesel(0, 0x3106);
        } else {
            func_80107730_modesel(0, 0x3124);
        }
    } else if (_CheckFlag(0x28)) {
        cur = 5;
        func_80107730_modesel(0, 0x3106);
    } else if (GwStory.unk0 != 12) {
        cur = 7;
        func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
        func_80107730_modesel(0, 0x3135);
        if (GwSystem.playMode & 1) {
            cur = 8;
        }
    }
    func_8010DF70_modesel();
    func_8010DFD0_modesel(cur);
    omDelPrcObj(D_80110BE0_modesel);
    D_80110BE0_modesel = func_8010899C_modesel();
    func_80013350_main(0);
    func_80109188_modesel(cur, 7);
    while (1) {
        buttons = D_800D5558_main[0];
        buttons |= func_80109A58_modesel(0);
        if (buttons & 0x8000) {
            result = func_8010CD00_modesel(cur, buttons);
            if (result >= 0) {
                break;
            }
        } else if (buttons & 0xF00) {
            result = func_8010D8DC_modesel(cur, buttons);
            if (result >= 0) {
                cur = result;
            }
        } else if (buttons & 0x4000) {
            func_80105FB4_modesel(1);
            func_80109188_modesel(10, 8);
            HuPrcSleep(8);
            func_801074F0_modesel(0);
            func_801067C0_modesel(10, 0x13, 8, 8, 2);
            func_80106BA0_modesel(0, 0x3115, 0xA0, D_8010F296_modesel + 4, 0, 0, 3);
            func_8010788C_modesel(0);
            confirm = func_80107838_modesel(0, 1, 0);
            func_801067C0_modesel(10, 0x14, 8, 8, 2);
            if (confirm == 0) {
                HuPrcVSleep();
                result = 16;
                func_80107730_modesel(0, 0x3116);
                func_8010788C_modesel(0);
                break;
            }
            if (func_800465D0_main() == 1) {
                HuWinComKeyWait(-0x8000, 0, 0, 0, 1);
                func_80107730_modesel(0, 0x3101);
            } else if (GwStory.unk0 == 12) {
                func_80107730_modesel(0, 0x3136);
            } else {
                func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
                func_80107730_modesel(0, 0x3134);
            }
            func_8010788C_modesel(0);
            func_8010DC6C_modesel(cur);
            func_80109188_modesel(cur, 8);
            HuPrcSleep(8);
            func_80105F84_modesel(1);
        }
        func_8010DFD0_modesel(cur);
        func_8010E6D8_modesel(cur);
        HuPrcVSleep();
    }
    switch (result) {
        case 0:
            func_80105FB4_modesel(1);
            break;
        case 1:
            func_80105FB4_modesel(1);
            func_80107700_modesel(0);
            func_8010EC40_modesel();
            func_80109188_modesel(-1, 20);
            func_80109E90_modesel(9);
            if (GwStory.unk0 != 12 || func_800465D0_main() != 0) {
                func_8010ABB4_modesel(10);
            }
            HuPrcSleep(20);
            modelId = func_8010648C_modesel(12);
            func_80013320_main(modelId, 0);
            Hu3DMotionTimeSet(modelId, 2.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            func_8001C814_main(modelId, 3, 0);
            HuPrcSleep(20);
            HuAudFXPlay(0x2E1);
            func_80106830_modesel(3, 3);
            HuPrcSleep(30);
            break;
        case 4:
        case 6:
        case 7:
        case 9:
        case 10:
        case 13:
            func_80105FB4_modesel(1);
            func_80107700_modesel(0);
            func_8010EC40_modesel();
            func_8010E558_modesel(cur);
            HuAudFXPlay(0x2E0);
            func_8010A62C_modesel(cur);
            func_80109188_modesel(-1, 20);
            omDelObj(D_80110BD0_modesel);
            if (GwStory.unk0 != 12 || func_800465D0_main() != 0) {
                D_80110BD0_modesel = func_8010ABB4_modesel(10);
            }
            HuPrcSleep(20);
            modelId = func_8010648C_modesel(11);
            func_80013320_main(modelId, 0);
            Hu3DMotionTimeSet(modelId, 0.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            func_8001C814_main(modelId, 3, 0);
            HuPrcSleep(50);
            func_8010ED00_modesel();
            break;
        case 5:
        case 8:
        case 11:
            func_8010E558_modesel(5);
            D_80110BD4_modesel->scale.x = D_80110BD4_modesel->baseScale.x = D_80110BD4_modesel->scale.y =
                D_80110BD4_modesel->baseScale.y = D_80110BD4_modesel->scale.z = D_80110BD4_modesel->baseScale.z =
                    1.0f;
            HuPrcSleep(8);
            func_80106A38_modesel(5, 0x11, 0);
            func_801068AC_modesel(0x12, 0);
            func_8010677C_modesel(0x12, 0);
            func_8010673C_modesel(0x12);
            func_80109154_modesel();
            HuPrcSleep(4);
            HuAudFXPlay(0x2FA);
            func_80109444_modesel();
            func_80106910_modesel(0x12);
            HuPrcSleep(24);
            func_80109408_modesel();
            break;
        case 14:
            func_80105FB4_modesel(1);
            func_80107700_modesel(0);
            func_8010EC40_modesel();
            func_8010E558_modesel(cur);
            omDelObj(D_80110BD0_modesel);
            func_8010AF18_modesel();
            func_80109188_modesel(-1, 20);
            HuPrcSleep(20);
            modelId = func_8010648C_modesel(11);
            func_80013320_main(modelId, 0);
            Hu3DMotionTimeSet(modelId, 0.0f);
            Hu3DMotionSpeedSet(modelId, 0.7f);
            func_8001C814_main(modelId, 3, 0);
            HuPrcSleep(50);
            func_8010ED00_modesel();
            break;
        case 16:
            break;
        default:
            while (1) {
                HuPrcVSleep();
            }
    }
    func_8010DFB4_modesel();
    return result;
}

s32 func_8010C094_modesel(void) {
    s32 x;
    s32 y;
    s32 i;
    s32 chr;
    s32 digit;

    SLLoadBoard();
    x = 0x50;
    y = 0x68;
    func_80105EA8_modesel(10, 0x1F0019);
    func_8010601C_modesel(10, x, y);
    func_80105FB4_modesel(10);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            func_80105EA8_modesel(11, 0x1F0004);
        } else {
            func_80105DD0_modesel(i + 11, 11);
        }
        func_80106194_modesel(i + 11, 5);
        func_8010601C_modesel(i + 11, x + (i - 2) * 16 + 8, y - 0x15);
        chr = D_80110B88_modesel.chr[i];
        func_801061C8_modesel(i + 11, chr, 0);
        func_80105FB4_modesel(i + 11);
        if (i == 0) {
            func_80105EA8_modesel(15, 0x1F0008);
        } else {
            func_80105DD0_modesel(i + 15, 15);
        }
        func_80106194_modesel(i + 15, 5);
        func_8010601C_modesel(i + 15, x + (i - 2) * 16 + 8, y - 9);
        func_80105FB4_modesel(i + 15);
    }
    func_80105EA8_modesel(19, 0x1F000C);
    func_80106194_modesel(19, 5);
    func_8010601C_modesel(19, x, y - 0x24);
    func_801061C8_modesel(19, 0, 0);
    func_80105FB4_modesel(19);
    func_80105EA8_modesel(20, 0x1F000B);
    func_80106194_modesel(20, 5);
    func_8010601C_modesel(20, x, y + 6);
    func_801061C8_modesel(20, GwSystem.current_board_index, 0);
    func_80105FB4_modesel(20);
    func_80105EA8_modesel(21, 0x1F0006);
    func_80106194_modesel(21, 5);
    func_8010601C_modesel(21, x - 0x18, y + 0x1E);
    func_80105FB4_modesel(21);
    func_80105EA8_modesel(22, 0x1F0007);
    func_80106194_modesel(22, 5);
    func_8010601C_modesel(22, x + 8, y + 0x1E);
    digit = D_80110B88_modesel.currentTurn % 10;
    func_801061C8_modesel(22, digit, 0);
    func_80105FB4_modesel(22);
    func_80105DD0_modesel(23, 22);
    func_80106194_modesel(23, 5);
    func_8010601C_modesel(23, x, y + 0x1E);
    digit = D_80110B88_modesel.currentTurn / 10;
    func_801061C8_modesel(23, digit, 0);
    func_80105FB4_modesel(23);
    func_80105EA8_modesel(24, 0x1F0028);
    func_8010601C_modesel(24, x + 0x10, y + 0x1E);
    func_80106194_modesel(24, 5);
    func_80105FB4_modesel(24);
    func_80105DD0_modesel(25, 22);
    func_80106194_modesel(25, 5);
    func_8010601C_modesel(25, x + 0x20, y + 0x1E);
    digit = D_80110B88_modesel.totalTurns % 10;
    func_801061C8_modesel(25, digit, 0);
    func_80105FB4_modesel(25);
    func_80105DD0_modesel(26, 22);
    func_80106194_modesel(26, 5);
    func_8010601C_modesel(26, x + 0x18, y + 0x1E);
    digit = D_80110B88_modesel.totalTurns / 10;
    func_801061C8_modesel(26, digit, 0);
    func_80105FB4_modesel(26);

    SLLoadBoardStory();
    x = 0xF0;
    y = 0x68;
    func_80105DD0_modesel(27, 10);
    func_8010601C_modesel(27, x, y);
    func_80105FB4_modesel(27);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            func_80105EA8_modesel(28, 0x1F0004);
        } else {
            func_80105DD0_modesel(i + 28, 28);
        }
        chr = D_80110BB4_modesel.chr[i];
        func_80106194_modesel(i + 28, 5);
        func_8010601C_modesel(i + 28, x + i * 32 - 0x10, y - 0x15);
        func_801061C8_modesel(i + 28, chr, 0);
        func_80105FB4_modesel(i + 28);
        if (i == 0) {
            func_80105EA8_modesel(30, 0x1F0008);
        } else {
            func_80105DD0_modesel(i + 30, 30);
        }
        func_80106194_modesel(i + 30, 5);
        func_8010601C_modesel(i + 30, x + i * 32 - 0x10, y - 9);
        func_80105FB4_modesel(i + 30);
    }
    x = 0xF0;
    y = 0x68;
    func_80105DD0_modesel(32, 19);
    func_80106194_modesel(32, 5);
    func_8010601C_modesel(32, x, y - 0x24);
    func_801061C8_modesel(32, 1, 0);
    func_80105FB4_modesel(32);
    func_80105EA8_modesel(33, 0x1F000A);
    func_80106194_modesel(33, 5);
    func_8010601C_modesel(33, x, y + 6);
    func_801061C8_modesel(33, GwSystem.current_board_index, 0);
    func_80105FB4_modesel(33);
    func_80105DD0_modesel(34, 21);
    func_80106194_modesel(34, 5);
    func_8010601C_modesel(34, x - 0x18, y + 0x1E);
    func_80105FB4_modesel(34);
    func_80105DD0_modesel(35, 22);
    func_80106194_modesel(35, 5);
    func_8010601C_modesel(35, x + 8, y + 0x1E);
    digit = D_80110BB4_modesel.currentTurn % 10;
    func_801061C8_modesel(35, digit, 0);
    func_80105FB4_modesel(35);
    func_80105DD0_modesel(36, 22);
    func_80106194_modesel(36, 5);
    func_8010601C_modesel(36, x, y + 0x1E);
    digit = D_80110BB4_modesel.currentTurn / 10;
    func_801061C8_modesel(36, digit, 0);
    func_80105FB4_modesel(36);
    if (D_80110BB4_modesel.totalTurns != 20) {
        func_80105EA8_modesel(37, 0x1F0027);
        func_8010601C_modesel(37, x, y + 0x1E);
    } else {
        func_80105EA8_modesel(37, 0x1F0028);
        func_8010601C_modesel(37, x + 0x10, y + 0x1E);
    }
    func_80106194_modesel(37, 5);
    func_80105FB4_modesel(37);
    func_80105DD0_modesel(38, 22);
    func_80106194_modesel(38, 5);
    func_8010601C_modesel(38, x + 0x20, y + 0x1E);
    digit = D_80110BB4_modesel.totalTurns % 10;
    func_801061C8_modesel(38, digit, 0);
    func_80105FB4_modesel(38);
    func_80105DD0_modesel(39, 22);
    func_80106194_modesel(39, 5);
    func_8010601C_modesel(39, x + 0x18, y + 0x1E);
    digit = D_80110BB4_modesel.totalTurns / 10;
    func_801061C8_modesel(39, digit, 0);
    func_80105FB4_modesel(39);
    return 0;
}

void func_8010C874_modesel(void) {
    s32 i;

    func_80105FE4_modesel(10);
    func_80105FE4_modesel(11);
    func_80105FE4_modesel(12);
    func_80105FE4_modesel(13);
    func_80105FE4_modesel(14);
    for (i = 0; i < 4; i++) {
        if (D_80110B88_modesel.cpu[i] != 0) {
            func_80105FE4_modesel(i + 15);
        }
    }
    func_80105FE4_modesel(19);
    func_80105FE4_modesel(20);
    func_80105FE4_modesel(21);
    func_80105FE4_modesel(24);
    if (D_80110B88_modesel.currentTurn / 10 != 0) {
        func_80105FE4_modesel(23);
    }
    func_80105FE4_modesel(22);
    func_80105FE4_modesel(26);
    func_80105FE4_modesel(25);
    func_80105FE4_modesel(27);
    func_80105FE4_modesel(28);
    func_80105FE4_modesel(29);
    for (i = 0; i < 2; i++) {
        if (D_80110BB4_modesel.cpu[i] != 0) {
            func_80105FE4_modesel(i + 30);
        }
    }
    func_80105FE4_modesel(32);
    func_80105FE4_modesel(33);
    func_80105FE4_modesel(34);
    func_80105FE4_modesel(37);
    if (D_80110BB4_modesel.totalTurns == 20) {
        if (D_80110BB4_modesel.currentTurn / 10 != 0) {
            func_80105FE4_modesel(36);
        }
        func_80105FE4_modesel(35);
        func_80105FE4_modesel(39);
        func_80105FE4_modesel(38);
    }
}

void func_8010CA30_modesel(void) {
    func_80106000_modesel(0xA);
    func_80106000_modesel(0xB);
    func_80106000_modesel(0xC);
    func_80106000_modesel(0xD);
    func_80106000_modesel(0xE);
    func_80106000_modesel(0xF);
    func_80106000_modesel(0x10);
    func_80106000_modesel(0x11);
    func_80106000_modesel(0x12);
    func_80106000_modesel(0x13);
    func_80106000_modesel(0x14);
    func_80106000_modesel(0x15);
    func_80106000_modesel(0x16);
    func_80106000_modesel(0x17);
    func_80106000_modesel(0x18);
    func_80106000_modesel(0x19);
    func_80106000_modesel(0x1A);
    func_80106000_modesel(0x1B);
    func_80106000_modesel(0x1C);
    func_80106000_modesel(0x1D);
    func_80106000_modesel(0x1E);
    func_80106000_modesel(0x1F);
    func_80106000_modesel(0x20);
    func_80106000_modesel(0x21);
    func_80106000_modesel(0x22);
    func_80106000_modesel(0x23);
    func_80106000_modesel(0x24);
    func_80106000_modesel(0x25);
    func_80106000_modesel(0x26);
    func_80106000_modesel(0x27);
}

void func_8010CB34_modesel(void) {
    func_80105F20_modesel(0x27);
    func_80105F20_modesel(0x26);
    func_80105F20_modesel(0x24);
    func_80105F20_modesel(0x23);
    func_80105F20_modesel(0x1A);
    func_80105F20_modesel(0x19);
    func_80105F20_modesel(0x17);
    func_80105F20_modesel(0x16);
    func_80105F20_modesel(0x25);
    func_80105F20_modesel(0x18);
    func_80105F20_modesel(0x22);
    func_80105F20_modesel(0x15);
    func_80105F20_modesel(0x21);
    func_80105F20_modesel(0x14);
    func_80105F20_modesel(0x20);
    func_80105F20_modesel(0x13);
    func_80105F20_modesel(0x1F);
    func_80105F20_modesel(0x1E);
    func_80105F20_modesel(0x12);
    func_80105F20_modesel(0x11);
    func_80105F20_modesel(0x10);
    func_80105F20_modesel(0xF);
    func_80105F20_modesel(0x1D);
    func_80105F20_modesel(0x1C);
    func_80105F20_modesel(0xE);
    func_80105F20_modesel(0xD);
    func_80105F20_modesel(0xC);
    func_80105F20_modesel(0xB);
    func_80105F20_modesel(0x1B);
    func_80105F20_modesel(0xA);
}

#ifdef NON_MATCHING
// The 0x4000 cancel path uses a branch-likely here instead of a jump, and the first
// func_8010E000_modesel call does not reuse the constant 14.
s32 func_8010CC38_modesel(void) {
    s32 choice;
    s32 x;
    s32 y;
    s32 buttons;

    func_8010C094_modesel();
    func_8010C874_modesel();
    choice = 14;
    while (1) {
        func_8010E000_modesel(choice, &x, &y);
        func_8010601C_modesel(1, x, y);
        HuPrcVSleep();
        buttons = D_800D5558_main[0];
        buttons |= func_80109A58_modesel(0);
        if (buttons & 0x8000) {
            break;
        } else if (buttons & 0x4000) {
            choice = -1;
            break;
        } else if (buttons & 0xF00) {
            choice = (choice == 14) ? 15 : 14;
            func_8010E280_modesel(1, choice);
        }
    }
    func_8010CA30_modesel();
    func_8010CB34_modesel();
    return choice;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CC38_modesel);
#endif

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CD00_modesel);

s32 func_8010D8DC_modesel(s32 cur, s32 buttons) {
    s32 next = cur;
    s32 unlocked;
    s32 i;

    if (func_800465D0_main() == 1) {
        unlocked = 0;
        if (_CheckFlag(0x16) || _CheckFlag(0x17)) {
            unlocked = 1;
        }
    } else {
        unlocked = _CheckFlag(0x28);
    }
    switch (cur) {
        case 0:
        case 1:
        case 2:
            if (buttons & 0x200) {
                do {
                    D_80110BD8_modesel = (D_80110BD8_modesel - 1 < 0) ? 5 : D_80110BD8_modesel - 1;
                } while (func_800E905C_minigame(D_80110BDA_modesel) < 0);
            } else if (buttons & 0x100) {
                do {
                    D_80110BD8_modesel = (D_80110BD8_modesel + 1 < 6) ? D_80110BD8_modesel + 1 : 0;
                } while (func_800E905C_minigame(D_80110BDA_modesel) < 0);
            } else if (buttons & 0x400) {
                next = 3;
            }
            break;
        case 3:
            if (buttons & 0x800) {
                for (i = 0; i < 6; i++) {
                    if (func_800E905C_minigame(i) >= 0) {
                        next = 2;
                    }
                }
            } else if (buttons & 0x200) {
                next = 8;
                if (func_800465D0_main() == 0) {
                    next = (GwStory.unk0 == 12) ? 10 : 8;
                }
            } else if (buttons & 0x100) {
                next = (unlocked == 0) ? 7 : 5;
            } else if (buttons & 0x400) {
                next = 9;
            }
            break;
        case 4:
        case 5:
            if (buttons & 0x800) {
                next = 3;
            } else if (buttons & 0x200) {
                next = 9;
            } else if (buttons & 0x400) {
                next = 7;
            }
            break;
        case 6:
        case 7:
            if (buttons & 0x800) {
                next = unlocked ? 5 : 9;
            } else if (buttons & 0x200) {
                next = 10;
                if (func_800465D0_main() == 0) {
                    next = (GwStory.unk0 != 12) ? 10 : 8;
                }
            }
            break;
        case 8:
            if (buttons & 0x800) {
                next = 9;
                if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                    next = 10;
                }
            } else if (buttons & 0x100) {
                next = 10;
                if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                    next = 7;
                }
            }
            break;
        case 9:
            if (buttons & 0x800) {
                next = 3;
            } else if (buttons & 0x200) {
                next = 8;
                if (func_800465D0_main() == 0) {
                    next = (GwStory.unk0 == 12) ? 10 : 8;
                }
            } else if (buttons & 0x400) {
                next = 10;
                if (func_800465D0_main() == 0) {
                    next = (GwStory.unk0 != 12) ? 10 : 8;
                }
            } else if (buttons & 0x100) {
                next = (unlocked == 0) ? 7 : 5;
            }
            break;
        case 10:
            if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                if (buttons & 0x800) {
                    next = 9;
                } else if (buttons & 0x200) {
                } else if (buttons & 0x400) {
                    next = 8;
                } else if (buttons & 0x100) {
                    next = 9;
                }
            } else {
                if (buttons & 0x800) {
                    next = 9;
                } else if (buttons & 0x200) {
                    next = 8;
                } else if (buttons & 0x400) {
                } else if (buttons & 0x100) {
                    next = 7;
                }
            }
            break;
    }
    func_8010DE88_modesel(next);
    func_8010DC6C_modesel(next);
    return next;
}

void func_8010DC6C_modesel(s32 arg0) {
    s32 rank;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            rank = func_800E905C_minigame(D_80110BDA_modesel);
            rank = (rank < 0) ? 0 : (rank >= 5) ? 4
                                                : rank;
            func_80107730_modesel(0, 0x3114);
            func_801077FC_modesel(0, 0, D_8010F2F0_modesel[rank]);
            func_801077FC_modesel(0, 1, D_80110BD8_modesel + 0x1C00);
            break;
        case 3:
            func_80107730_modesel(0, 0x3107);
            break;
        case 4:
        case 5:
            func_80107730_modesel(0, 0x3106);
            break;
        case 7:
            if (func_800465D0_main() == 1) {
                func_80107730_modesel(0, 0x3104);
            } else if ((GwSystem.playMode & 2) && GwStory.unk0 != 12) {
                func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
                func_80107730_modesel(0, 0x3135);
            } else {
                func_80107730_modesel(0, 0x3104);
            }
            break;
        case 8:
            if (func_800465D0_main() == 1) {
                func_80107730_modesel(0, 0x3103);
            } else if ((GwSystem.playMode & 1) && GwStory.unk0 != 12) {
                func_801077FC_modesel(0, 0, func_8010F204_modesel(GwStory.unk0) + 0x3127);
                func_80107730_modesel(0, 0x3135);
            } else {
                func_80107730_modesel(0, 0x3103);
            }
            break;
        case 9:
            if (func_800465D0_main() == 0) {
                func_80107730_modesel(0, 0x313E);
            } else {
                func_80107730_modesel(0, 0x3105);
            }
            break;
        case 10:
            if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                func_80107730_modesel(0, 0x3119);
            } else if (func_800465D0_main() == 0) {
                func_80107730_modesel(0, 0x3122);
            } else {
                func_80107730_modesel(0, 0x3124);
            }
            break;
    }
}

void func_8010DE88_modesel(s32 arg0) {
    switch (arg0) {
        case 0:
        case 1:
        case 2:
            func_800E905C_minigame(D_80110BDA_modesel);
            func_8010E280_modesel(1, 2);
            break;
        case 3:
            func_80109188_modesel(3, 8);
            func_8010E280_modesel(1, 3);
            break;
        case 4:
        case 5:
            func_80109188_modesel(5, 8);
            func_8010E280_modesel(1, 5);
            break;
        case 7:
            func_80109188_modesel(7, 8);
            func_8010E280_modesel(1, 7);
            break;
        case 8:
            func_80109188_modesel(8, 8);
            func_8010E280_modesel(1, 8);
            break;
        case 9:
            func_80109188_modesel(9, 8);
            func_8010E280_modesel(1, 9);
            break;
        case 10:
            func_800465D0_main();
            func_80109188_modesel(10, 8);
            func_8010E280_modesel(1, 10);
            break;
    }
}

void func_8010DF70_modesel(void) {
    func_80105EA8_modesel(1, 0x88);
    func_80106194_modesel(1, 5);
    func_8010601C_modesel(1, 0xA0, 0x71);
    func_80105F84_modesel(1);
}

void func_8010DFB4_modesel(void) {
    func_80105F20_modesel(1);
}

void func_8010DFD0_modesel(s32 arg0) {
    s32 x;
    s32 y;

    func_8010E000_modesel(arg0, &x, &y);
    func_8010601C_modesel(1, x, y);
}

void func_8010E000_modesel(s32 arg0, s32 *x, s32 *y) {
    Vec pos;
    Vec2f screenPos;
    s32 index = 0;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            index = D_80110BD8_modesel + 8;
            break;
        case 3:
            index = 3;
            break;
        case 4:
        case 5:
        case 6:
            index = 4;
            break;
        case 7:
            index = 0;
            break;
        case 8:
            index = 1;
            break;
        case 9:
            index = 2;
            break;
        case 10:
            if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                index = 7;
            } else {
                index = 6;
            }
            break;
        case 14:
            *x = 0x70;
            *y = 0x3C;
            return;
        case 15:
            *x = 0x110;
            *y = 0x3C;
            return;
    }
    pos.x = D_8010F304_modesel[index].x;
    pos.y = D_8010F304_modesel[index].y;
    pos.z = D_8010F304_modesel[index].z;
    Hu3D3Dto2D(0, &pos, &screenPos);
    *x = screenPos.x;
    *y = screenPos.y;
}

#ifdef NON_MATCHING
// The story check is expected to compile to a branchless store-flag sequence
// (-(GwStory.unk0 == 12) & 7 | 2), but this emits a conditional branch.
void func_8010E138_modesel(s32 arg0, f32 *x, f32 *y, f32 *z) {
    s32 index = 0;

    switch (arg0) {
        case 0:
        case 1:
        case 2:
            index = 5;
            break;
        case 3:
            index = 3;
            break;
        case 4:
        case 5:
        case 6:
            index = 4;
            break;
        case 7:
            index = 0;
            break;
        case 8:
            index = 1;
            break;
        case 9:
            index = 2;
            break;
        case 10:
            if (func_800465D0_main() == 0 && GwStory.unk0 == 12) {
                index = 9;
            } else {
                index = 2;
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            break;
    }
    *x = D_8010F304_modesel[index].x;
    *y = D_8010F304_modesel[index].y;
    *z = D_8010F304_modesel[index].z;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E138_modesel);
#endif

void func_8010E22C_modesel(s32 arg0, s32 arg1) {
    s32 x;
    s32 y;

    func_80106074_modesel(arg0, &x, &y);
    y += arg1;
    func_8010601C_modesel(arg0, x, y);
}

void func_8010E280_modesel(s32 arg0, s32 arg1) {
    s32 endX;
    s32 endY;
    s32 startX;
    s32 startY;
    s32 i;
    f32 t;

    func_8010E000_modesel(arg1, &endX, &endY);
    func_80106074_modesel(arg0, &startX, &startY);
    for (i = 0; i < 8; i++) {
        t = i * (1.0f / 7.0f);
        func_8010E000_modesel(arg1, &endX, &endY);
        func_8010601C_modesel(arg0, startX + t * (endX - startX), startY + t * (endY - startY));
        HuPrcVSleep();
    }
    func_8010601C_modesel(arg0, endX, endY);
}

#ifdef NON_MATCHING
// Float register allocation differs: the target loads the 1.0f constant before the
// sine * 0.1f multiply and keeps the scale in $f4 instead of $f2.
void func_8010E3A4_modesel(s32 index, f32 t) {
    s32 slot = index;
    f32 angle;
    f32 sine;
    f32 scale;

    if (t > 1.0f) {
        t = 1.0f;
    }
    if (t < 0.0f) {
        return;
    }
    angle = t * 360.0f;
    sine = sindf(angle);
    cosdf(angle);
    scale = sine * 0.1f + 1.0f;
    switch (slot) {
        case 2:
            func_801065B0_modesel(index, 1.0f, 1.0f, 1.0f);
            break;
        case 3:
            func_801065B0_modesel(index, scale, scale, 1.0f);
            break;
        case 5:
            scale = sine * 0.3f + 1.0f;
            D_80110BD4_modesel->scale.x = D_80110BD4_modesel->baseScale.x = D_80110BD4_modesel->scale.y =
                D_80110BD4_modesel->baseScale.y = D_80110BD4_modesel->scale.z = D_80110BD4_modesel->baseScale.z =
                    scale;
            break;
        case 7:
        case 8:
        case 9:
            func_8010B940_modesel(index, 180.0f / 23.0f);
            func_8010B824_modesel(index);
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E3A4_modesel);
#endif

void func_8010E50C_modesel(void) {
    s32 i;

    for (i = 0; i < 21; i++) {
        D_80110CF8_modesel[i][0] = 0;
        D_80110CF0_modesel[i][0] = 0;
        D_80110CF4_modesel[i][0] = 0;
    }
}

void func_8010E558_modesel(s32 arg0) {
    if (D_80110CF8_modesel[arg0][0] != NULL) {
        omDelObj(D_80110CF8_modesel[arg0][0]);
    }
    D_80110CF8_modesel[arg0][0] = NULL;
}

void func_8010E5B8_modesel(void) {
    s32 i;

    for (i = 0; i < 21; i++) {
        func_8010E558_modesel(i);
    }
}

void func_8010E5F0_modesel(omObjData *obj) {
    s32 index = obj->work[0];
    s32 slot = index;
    f32 t = (f32)D_80110CF0_modesel[index][0] / D_80110CF4_modesel[index][0];

    if (D_80110CF0_modesel[index][0] <= D_80110CF4_modesel[index][0] - 1) {
        func_8010E3A4_modesel(index, t);
        D_80110CF0_modesel[index][0]++;
    } else {
        func_8010E3A4_modesel(index, t);
        func_8010E558_modesel(slot);
        D_80110CF0_modesel[index][0] = 0;
    }
}

void func_8010E6D8_modesel(s32 arg0) {
    omObjData *obj;

    if (D_80110CF8_modesel[arg0][0] == NULL) {
        obj = omAddObj(6, 0, 0, -1, func_8010E5F0_modesel);
        obj->work[0] = arg0;
        D_80110CF8_modesel[arg0][0] = obj;
        if (arg0 < 10) {
            if (arg0 >= 7) {
                D_80110CF4_modesel[arg0][0] = 45;
            } else {
                D_80110CF4_modesel[arg0][0] = 20;
            }
        } else {
            D_80110CF4_modesel[arg0][0] = 20;
        }
    }
}

void func_8010E790_modesel(Process *arg0) {
    omDelPrcObj(arg0);
    func_80013350_main(0);
}

void func_8010E7B4_modesel(void) {
    s32 i;
    s8 value;

    D_80110B70_modesel[0] = D_80110B70_modesel[1] = D_80110B70_modesel[2] = D_80110B70_modesel[3] =
        D_80110B70_modesel[4] = D_80110B70_modesel[5] = 0;
    if (func_800465D0_main() == 1) {
        SLLoadBoard();
        for (i = 0; i < 4; i++) {
            D_80110B88_modesel.chr[i] = GwPlayer[i].chr;
            D_80110B88_modesel.cpu[i] = GwPlayer[i].stat & 1;
        }
        D_80110B88_modesel.gameLength = (value = GwSystem.current_game_length) >= 3 ? 3 : value;
        D_80110B88_modesel.currentTurn = (value = GwSystem.current_turn) >= 99 ? 99 : value;
        D_80110B88_modesel.totalTurns = (value = GwSystem.total_turns) >= 99 ? 99 : value;
        SLLoadBoardStory();
        for (i = 0; i < 2; i++) {
            D_80110BB4_modesel.chr[i] = GwPlayer[i].chr;
            D_80110BB4_modesel.cpu[i] = GwPlayer[i].stat & 1;
        }
        D_80110BB4_modesel.gameLength = (value = GwSystem.current_game_length) >= 3 ? 3 : value;
        D_80110BB4_modesel.currentTurn = (value = GwSystem.current_turn) >= 99 ? 99 : value;
        D_80110BB4_modesel.totalTurns = (value = GwSystem.total_turns) >= 99 ? 99 : value;
    }
}

void func_8010E984_modesel(void) {
    s32 x;
    s32 y;

    if (func_800465D0_main() == 1) {
        func_80105EA8_modesel(6, 0xD0011);
        func_8010601C_modesel(6, 0x40, 0x1C);
        func_80105FB4_modesel(6);
        HuSprColorSet(func_80105D24_modesel(6), 0, 0xFF, 0xFF, 0);
        func_80105EA8_modesel(7, 0xD0013);
        func_8010601C_modesel(7, 0x40, 0x1C);
        func_80105FB4_modesel(7);
        func_80105EA8_modesel(8, 0xD0014);
        func_8010601C_modesel(8, 0x40, 0x1C);
        func_80105FB4_modesel(8);
        func_80105EA8_modesel(9, 0x1F0004);
        func_8010601C_modesel(9, 0x26, 0x24);
    } else {
        x = 0x40;
        func_80105EA8_modesel(6, 0xD0010);
        func_8010601C_modesel(6, x, 0x26);
        func_80105FB4_modesel(6);
        HuSprColorSet(func_80105D24_modesel(6), 0, 0xFF, 0xFF, 0);
        func_80105EA8_modesel(7, 0xD0012);
        func_8010601C_modesel(7, x, 0x1C);
        func_80105FB4_modesel(7);
        switch (GwStory.unk2) {
            case 0:
                func_80105EA8_modesel(8, 0xD0014);
                y = 0x2E;
                break;
            case 1:
                func_80105EA8_modesel(8, 0xD0015);
                y = 0x2E;
                break;
            case 2:
                func_80105EA8_modesel(8, 0xD0016);
                y = 0x2E;
                break;
            case 3:
                func_80105EA8_modesel(8, 0xD0017);
                y = 0x2E;
                break;
            default:
                func_80105EA8_modesel(8, 0xD0015);
                y = 0x2E;
                break;
        }
        func_8010601C_modesel(8, x + 10, y);
        func_80105FB4_modesel(8);
        func_80105EA8_modesel(9, 0x1F0004);
        func_8010601C_modesel(9, x - 26, y);
        func_801061C8_modesel(9, GwStory.unk1, 0);
    }
    func_80105FB4_modesel(9);
}

void func_8010EBC4_modesel(void) {
    func_80105F20_modesel(6);
    func_80105F20_modesel(7);
    func_80105F20_modesel(8);
    func_80105F20_modesel(9);
}

void func_8010EBF8_modesel(void) {
    func_80105FE4_modesel(6);
    func_80105FE4_modesel(7);
    if (func_800465D0_main() != 1) {
        func_80105FE4_modesel(8);
        func_80105FE4_modesel(9);
    }
}

void func_8010EC40_modesel(void) {
    func_80106000_modesel(6);
    func_80106000_modesel(7);
    func_80106000_modesel(8);
    func_80106000_modesel(9);
}

f32 func_8010EC74_modesel(f32 arg0, f32 arg1) {
    return -(atan2df(arg1, arg0) - 90.0f);
}

void func_8010ECAC_modesel(omObjData *obj) {
    s32 *counter;

    if (D_80110DEC_modesel == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_80110DEC_modesel;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

void func_8010ED00_modesel(void) {
    D_80110DEC_modesel = 0;
    omAddObj(6, 0, 0, -1, func_8010ECAC_modesel);
}

void func_8010ED3C_modesel(void) {
    u16 spriteId;
    s32 i;

    func_80105EA8_modesel(3, 0x140064);
    func_8010601C_modesel(3, 160, 120);
    func_801060A4_modesel(3, 10.0f, 8.0f);
    func_801060F4_modesel(3, 0);
    func_80105FB4_modesel(3);
    spriteId = func_80105D24_modesel(3);
    espColorSet(spriteId, 0, 0, 0);
    espPriSet(spriteId, 0x4BA);
    func_80105EA8_modesel(2, 0xD0018);
    func_8010601C_modesel(2, 160, 120);
    func_801060A4_modesel(2, 1.0f, 1.0f);
    func_80105FB4_modesel(2);
    spriteId = func_80105D24_modesel(2);
    espColorSet(spriteId, 0, 0, 0);
    espPriSet(spriteId, 11);
    func_80105EA8_modesel(4, 0x150003);
    func_8010601C_modesel(4, 28, 120);
    func_80105FB4_modesel(4);
    func_80105EA8_modesel(5, 0x150003);
    func_8010601C_modesel(5, 292, 120);
    func_80105FB4_modesel(5);
    espAttrSet(func_80105D24_modesel(5), 1);
    func_80106000_modesel(1);
    func_80107700_modesel(0);
    func_8010EC40_modesel();
    func_80105F84_modesel(3);
    func_80105F84_modesel(2);
    func_80105FB4_modesel(4);
    func_80105F84_modesel(5);
    for (i = 0; i < 8; i++) {
        func_801060F4_modesel(2, i * (256.0f / 7));
        if (i * (256.0f / 7) < 128.0f) {
            func_801060F4_modesel(3, i * (256.0f / 7));
        } else {
            func_801060F4_modesel(3, 128);
        }
        HuPrcVSleep();
    }
    func_801060F4_modesel(2, 256);
    func_801060F4_modesel(3, 128);
    func_80106BA0_modesel(1, 0x5F01, 0, 16, 304, 208, 0);
    func_8005C154_main(D_80110998_modesel[1][0], 64, 64, 64);
    HuWinMesPalSet(D_80110998_modesel[1][0], 4, 0, 255, 0);
    HuWinMesPalSet(D_80110998_modesel[1][0], 6, 255, 255, 128);
    while (1) {
        if (D_800D5558_main[0] & 0x4000) {
            break;
        }
        if (D_800C9520_main[0] & 0x200) {
            func_80105FB4_modesel(4);
            func_80105F84_modesel(5);
            func_80107730_modesel(1, 0x5F01);
        } else if (D_800D5546_main[0] & 0x100) {
            func_80105F84_modesel(4);
            func_80105FB4_modesel(5);
            func_80107730_modesel(1, 0x5F02);
        }
        HuPrcVSleep();
    }
    func_801074F0_modesel(1);
    for (i = 0; i < 7; i++) {
        func_801060F4_modesel(2, (7 - i) * (255.0f * (1.0f / 7)));
        HuPrcVSleep();
    }
    func_80105FB4_modesel(2);
    func_80105FB4_modesel(3);
    func_80105FB4_modesel(4);
    func_80105FB4_modesel(5);
    func_80105F20_modesel(3);
    func_80105F20_modesel(2);
    func_80105F20_modesel(4);
    func_80105F20_modesel(5);
    func_80105FE4_modesel(1);
    func_801076D0_modesel(0);
    func_8010EBF8_modesel();
}

void func_8010F1F4_modesel(void) {
}

s32 func_8010F1FC_modesel(void) {
    return 1;
}

s32 func_8010F204_modesel(s32 arg0) {
    return D_8010F2A0_modesel[arg0];
}

s32 func_8010F214_modesel(s32 arg0) {
    s32 value = D_8010F2A0_modesel[arg0];

    if (value >= 6) {
        value -= 6;
    }
    return value;
}

s32 func_8010F234_modesel(s32 arg0) {
    s32 value = D_8010F2A0_modesel[arg0];

    return value < 6 ? 1 : 2;
}

u8 func_8010F258_modesel(s32 arg0) {
    return D_8010F2B0_modesel[arg0];
}
