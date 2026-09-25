#include "common.h"
#include "game/vibrator.h"
#include "mallocblock.h"

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

// Accumulated spin angle: added to as a float by func_8010B940_modesel, but reset
// and read as a raw word by func_8010B804_modesel and func_8010B824_modesel.
typedef union UnkModeSelAngle {
    s32 word;
    f32 angle;
} UnkModeSelAngle; // sizeof 0x4

extern s32 D_80110B20_modesel[][7];
extern s32 D_80110B24_modesel[][7];
extern s32 D_80110B28_modesel[][7];
extern f32 D_80110B2C_modesel[][7];
extern UnkModeSelAngle D_80110B30_modesel[][7];
extern u8 D_8010F2A0_modesel[];
extern s16 D_8010FE10_modesel[0x40];
extern UnkModeSel D_8010FE90_modesel[0x40];
extern UnkModeSel4 D_8010FEA0_modesel[0x40];
extern UnkModeSel2 D_8010F710_modesel[0x40];
extern s16 D_80110990_modesel;
extern u16 D_80110992_modesel;
extern s16 D_80110998_modesel[0x20][6];
extern s32 D_8011099C_modesel[0x20][3];
extern omObjData *D_80110C10_modesel;
extern UnkModeSel6 D_80110C38_modesel;
extern UnkModeSel5 D_80110C68_modesel[3];
extern UnkModeSel3 D_80110BE8_modesel;
extern f32 D_80110CB0_modesel[3];
extern Vec D_80110CBC_modesel;
extern f32 D_80110CD4_modesel;
extern f32 D_80110CD8_modesel[3];
extern Vec D_80110CE4_modesel;
// Three interleaved parallel arrays covering the same 21 slots; each element is 0xC bytes apart.
extern s32 D_80110CF0_modesel[][3];
extern s32 D_80110CF4_modesel[][3];
extern omObjData *D_80110CF8_modesel[][3];
extern s32 D_80110DEC_modesel;

void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BCC8_main(u16, s32);
void func_8000BD94_main(u16, s32, s32);
void func_8000BE5C_main(u16, f32, f32);
void func_8010601C_modesel(s32, s32, s32);
void func_80106A38_modesel(s32, s32, s16);
void func_80108F8C_modesel(Vec *, Vec *, Vec *);
void func_80109290_modesel(omObjData *);
void func_8010A420_modesel(omObjData *);
void func_8010A674_modesel(omObjData *);
void func_8010AAC0_modesel(omObjData *);
void func_8010ADC8_modesel(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801059D0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105BD8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105BFC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105C20_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105C50_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105C7C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105D10_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105D24_modesel);

void func_80105D40_modesel(s32 arg0, s32 arg1) {
    D_8010FE10_modesel[arg0] = func_8000B838_main(arg1);
}

void func_80105D78_modesel(s32 arg0) {
    if (D_8010FE10_modesel[arg0] != -1) {
        HuSprKill(D_8010FE10_modesel[arg0]);
    }
    D_8010FE10_modesel[arg0] = -1;
}

void func_80105DD0_modesel(s32 arg0, s16 arg1) {
    D_8010F710_modesel[arg0].unk_00 = InitEspriteSlot(D_8010FE10_modesel[arg1], 0, 0);
    func_8010601C_modesel(arg0, 0xA0, 0x78);
}

void func_80105E38_modesel(s32 arg0) {
    if (D_8010F710_modesel[arg0].unk_00 != -1) {
        func_8000C184_main(D_8010F710_modesel[arg0].unk_00);
    }
    D_8010F710_modesel[arg0].unk_00 = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105EA8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105EDC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105F20_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105F4C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105F84_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105FB4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80105FE4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106000_modesel);

void func_8010601C_modesel(s32 arg0, s32 arg1, s32 arg2) {
    D_8010F710_modesel[arg0].unk_04 = arg1;
    D_8010F710_modesel[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106074_modesel);

void func_801060A4_modesel(s32 arg0, f32 arg1, f32 arg2) {
    D_8010F710_modesel[arg0].unk_0C = arg1;
    D_8010F710_modesel[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

void func_801060F4_modesel(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_8010612C_modesel(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_80106160_modesel(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_80106194_modesel(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_8010F710_modesel[arg0].unk_00, arg1);
}

void func_801061C8_modesel(s32 arg0, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_8010F710_modesel[arg0].unk_00, 1);
    func_8000BD94_main(D_8010F710_modesel[arg0].unk_00, arg1, arg2);
}

void func_80106234_modesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_8010FE90_modesel); i++) {
        D_8010FE90_modesel[i].unk_00 = -1;
        D_8010FE90_modesel[i].unk_02 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106280_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010631C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801063A4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106454_modesel);

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
    func_8001C258_main(D_8010FE90_modesel[arg0].unk_00, 4, 4);
}

void func_8010673C_modesel(s32 arg0) {
    func_8001C258_main(D_8010FE90_modesel[arg0].unk_00, 4, 0);
}

void func_8010677C_modesel(s32 arg0, s32 arg1) {
    func_8001C814_main(D_8010FE90_modesel[arg0].unk_00, -1, arg1);
}

void func_801067C0_modesel(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_8010FE90_modesel[arg0].unk_00, D_8010FE90_modesel[arg1].unk_02, arg2, arg3, arg4);
}

void func_80106830_modesel(s32 arg0, s32 arg1) {
    func_8001C814_main(D_8010FE90_modesel[arg0].unk_00, arg1, 0);
}

void func_80106874_modesel(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_8010FE90_modesel[arg0].unk_00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801068AC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106910_modesel);

s32 func_801069B0_modesel(s32 arg0) {
    s16 modelId = D_8010FE90_modesel[arg0].unk_00;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void func_80106A38_modesel(s32 arg0, s32 arg1, s16 arg2) {
    s16 modelId = func_8010648C_modesel(arg0);
    s16 parentModelId = func_801064B0_modesel(arg1);

    func_8001F304_main(modelId, parentModelId);
    func_8001C814_main(modelId, -1, arg2);
}

void func_80106AA8_modesel(void) {
    // The original call omits the resource id.
    D_80110990_modesel = ((s16 (*)())func_8000B838_main)();
    D_80110992_modesel = InitEspriteSlot(D_80110990_modesel, 0, 0);
    func_8000BC48_main(D_80110992_modesel, 0x4000);
    func_8000BBD4_main(D_80110992_modesel, 0xA0, 0x78);
}

void func_80106B0C_modesel(void) {
    func_8000C184_main(D_80110992_modesel);
    HuSprKill(D_80110990_modesel);
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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106BA0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106DEC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80106F38_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801070A0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107248_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107314_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801073E0_modesel);

void func_801074AC_modesel(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80110998_modesel[i][0] = -1;
        D_8011099C_modesel[i][0] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801074F0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801075D4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107638_modesel);

void func_80107668_modesel(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80110998_modesel[arg0][0], arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801076D0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107700_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107730_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801077FC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107838_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107870_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010788C_modesel);

void func_801078E0_modesel(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010791C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107954_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107B08_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107CB0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F454_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80107CEC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801088AC_modesel);

void func_801088F8_modesel(void) {
    do {
        func_80108F8C_modesel(&D_80110BE8_modesel.pos, &D_80110BE8_modesel.at, &D_80110BE8_modesel.up);
        HuPrcVSleep();
    } while (1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010893C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010899C_modesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80108A94_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80108AE0_modesel);

void func_80108F8C_modesel(Vec *pos, Vec *at, Vec *up) {
    Hu3DCamSetPositionOrientation(0, pos, at, up);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80108FC4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80108FD0_modesel);

void func_80109154_modesel(void) {
    if (D_80110C10_modesel != NULL) {
        omDelObj(D_80110C10_modesel);
    }
    D_80110C10_modesel = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109188_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109290_modesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801094A8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801094F0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_801096D4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109968_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109A58_modesel);

void func_80109B74_modesel(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_80110C68_modesel[i].unk_08 = NULL;
        D_80110C68_modesel[i].unk_04 = 0;
        D_80110C68_modesel[i].unk_00 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109BC0_modesel);

void func_80109C8C_modesel(s32 arg0) {
    s32 i = arg0 - 7;

    if (D_80110C68_modesel[i].unk_08 != NULL) {
        omDelObj(D_80110C68_modesel[i].unk_08);
    }
    D_80110C68_modesel[i].unk_08 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109CEC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109DB8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_80109E90_modesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A068_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A1C4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A2E8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A420_modesel);

void func_8010A62C_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A420_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A674_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A84C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010A9B8_modesel);

omObjData *func_8010AA48_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010A674_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    func_80106618_modesel(arg0, &D_80110CB0_modesel[0], &D_80110CB0_modesel[1], &D_80110CB0_modesel[2]);
    D_80110CD4_modesel = 0.0f;
    return obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010AAC0_modesel);

omObjData *func_8010ABB4_modesel(s32 arg0) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010AAC0_modesel);

    obj->work[0] = arg0;
    obj->work[1] = 0;
    func_80106618_modesel(arg0, &D_80110CB0_modesel[0], &D_80110CB0_modesel[1], &D_80110CB0_modesel[2]);
    HuVecCopyXYZ(&D_80110CBC_modesel, 0.0f, -400.0f, 300.0f);
    return obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010AC3C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010ACA8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010AD74_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010ADC8_modesel);

omObjData *func_8010AF18_modesel(void) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010ADC8_modesel);

    func_80106618_modesel(0xA, &D_80110CD8_modesel[0], &D_80110CD8_modesel[1], &D_80110CD8_modesel[2]);
    HuVecCopyXYZ(&D_80110CE4_modesel, 0.0f, 200.0f, 300.0f);
    obj->work[0] = 0;
    return obj;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4C8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4D0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4D8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4E0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4E8_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4F0_modesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/modesel/4F7EC0", D_8010F4F8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010AF90_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010B6B0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010B75C_modesel);

void func_8010B790_modesel(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s32 index = arg0 - 7;

    D_80110B20_modesel[index][0] = arg1;
    D_80110B24_modesel[index][0] = arg2;
    D_80110B28_modesel[index][0] = arg3;
    D_80110B2C_modesel[index][0] = arg4 < 0.0f ? 0.0f : arg4;
}

void func_8010B804_modesel(s32 arg0, s32 arg1) {
    D_80110B30_modesel[arg0 - 7][0].word = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010B824_modesel);

void func_8010B940_modesel(s32 arg0, f32 arg1) {
    s32 index = arg0 - 7;

    if (360.0f < arg1) {
        arg1 = 360.0f;
    }
    D_80110B30_modesel[index][0].angle += arg1;
    if (360.0f < D_80110B30_modesel[index][0].angle) {
        D_80110B30_modesel[index][0].angle -= 360.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010B9C4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010BA70_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010C094_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010C874_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CA30_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CB34_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CC38_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010CD00_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010D8DC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010DC6C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010DE88_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010DF70_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010DFB4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010DFD0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E000_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E138_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E22C_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E280_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E3A4_modesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E5B8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E5F0_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E6D8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E790_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E7B4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010E984_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010EBC4_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010EBF8_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010EC40_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010EC74_modesel);

void func_8010ECAC_modesel(void) {
    s32 *counter;

    if (D_80110DEC_modesel == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_80110DEC_modesel;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010ED00_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010ED3C_modesel);

void func_8010F1F4_modesel(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010F1FC_modesel);

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010F204_modesel);

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

INCLUDE_ASM("asm/nonmatchings/overlays/modesel/4F7EC0", func_8010F258_modesel);
