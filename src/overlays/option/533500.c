#include "common.h"

typedef struct UnkOption {
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
} UnkOption;

typedef struct {
    /* 0x00 */ s16 espriteSlot;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OptSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ s16 winID;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} OptWinEntry; // sizeof 0xC

typedef struct {
    /* 0x00 */ omObjData *prcObj;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec at;
    /* 0x1C */ Vec up;
    /* 0x28 */ f32 fov;
    /* 0x2C */ f32 nearPlane;
    /* 0x30 */ f32 farPlane;
    /* 0x34 */ s16 camId;
    /* 0x38 */ omObjData *obj;
} OptCam; // sizeof 0x3C

extern OptCam D_801146F0_option;
extern s16 D_80114EF0_option[0x40];
extern OptSpr D_801147F0_option[0x40];
extern UnkOption D_80114F70_option[0x40];
extern s16 D_80115A70_option;
extern u16 D_80115A72_option;
extern OptWinEntry D_80115A78_option[0x20];

void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801059D0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105C14_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105C38_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105C5C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105C80_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105CA4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105CC8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105CEC_option);

void func_80105D10_option(void) {
    D_801146F0_option.prcObj = NULL;
    D_801146F0_option.obj = NULL;
    D_801146F0_option.camId = -1;
    D_801146F0_option.fov = 50.0f;
    D_801146F0_option.nearPlane = 80.0f;
    D_801146F0_option.farPlane = 4000.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105D5C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105D74_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105DA0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105E40_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105EB8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105F08_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80105FF8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106508_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106998_option);

void func_80106B78_option(void) {
    if (D_801146F0_option.obj != NULL) {
        omDelObj(D_801146F0_option.obj);
    }
    D_801146F0_option.obj = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106BAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106C7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80106F88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107058_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010737C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010744C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107758_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010778C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801077BC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107AD4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107B08_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107B38_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107B80_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107D64_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A20_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80107F50_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108A68_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108AAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108AF0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108B34_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A4C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A50_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A54_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", jtbl_80113A58_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A80_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A8C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113A98_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AA4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AB0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113ABC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AC8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AD4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AE0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AEC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113AF8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B04_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B10_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80108B58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109504_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801096B8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801096E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109730_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109908_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010998C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109A0C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109B7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109CB0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113B9C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BB4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BC0_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113BCC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109D04_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80109EF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A3E8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A498_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A66C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A8DC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010A940_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CB8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113CD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010AF54_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010B654_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010B68C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010BACC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010BFA4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C04C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C224_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010C3E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010D5B0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010E77C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010E7FC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010E8E0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010F138_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010F914_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010F94C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FA28_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FA7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FB40_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D78_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113DA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_8011421C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FC40_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FDF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FE00_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FE10_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FE84_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FF0C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FF88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FFDC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110018_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110170_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011019C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110230_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110244_option);

void func_80110260_option(s32 arg0, s32 arg1) {
    D_80114EF0_option[arg0] = func_8000B838_main(arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110298_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801102F0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110358_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801103C8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801103FC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110440_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011046C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801104A4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801104D4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110504_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110520_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011053C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110594_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801105C4_option);

void func_80110614_option(s32 arg0, u16 arg1) {
    func_8000BBFC_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_8011064C_option(s32 arg0, u16 arg1) {
    func_8000BC48_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_80110680_option(s32 arg0, u16 arg1) {
    func_8000BC88_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

void func_801106B4_option(s32 arg0, u16 arg1) {
    func_8000BCC8_main(D_801147F0_option[arg0].espriteSlot, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801106E8_option);

void func_80110754_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114F70_option); i++) {
        D_80114F70_option[i].unk_00 = -1;
        D_80114F70_option[i].unk_02 = -1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801107A0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011083C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801108C4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110974_option);

s16 func_801109AC_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_00;
}

s16 func_801109D0_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_02;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801109F4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110A5C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110AD0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110B38_option);

void func_80110B8C_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_1C;
    *arg2 = D_80114F70_option[arg0].unk_20;
    *arg3 = D_80114F70_option[arg0].unk_24;
}

void func_80110BD4_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_10;
    *arg2 = D_80114F70_option[arg0].unk_14;
    *arg3 = D_80114F70_option[arg0].unk_18;
}

void func_80110C1C_option(s32 arg0) {
    func_8001C258_main(D_80114F70_option[arg0].unk_00, 4, 4);
}

void func_80110C5C_option(s32 arg0) {
    func_8001C258_main(D_80114F70_option[arg0].unk_00, 4, 0);
}

void func_80110C9C_option(s32 arg0, s32 arg1) {
    func_8001C814_main(D_80114F70_option[arg0].unk_00, -1, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110CE0_option);

void func_80110D50_option(s32 arg0, s16 arg1) {
    func_8001C814_main(D_80114F70_option[arg0].unk_00, arg1, 0);
}

void func_80110D94_option(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_80114F70_option[arg0].unk_00);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110DCC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110E30_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110ED0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110F58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110FC8_option);

void func_8011102C_option(void) {
    func_8000C184_main(D_80115A72_option);
    HuSprKill(D_80115A70_option);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111058_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801110C0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011130C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111458_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801115C0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111768_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111834_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111900_option);

void func_801119CC_option(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80115A78_option[i].winID = -1;
        D_80115A78_option[i].unk_04 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111A10_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111AF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111B58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111B88_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111BF0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111C20_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111C50_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111D1C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111D58_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111D90_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111DAC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111E00_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111E3C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80111E74_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112028_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112044_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112060_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112084_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011239C_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80114674_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80114680_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801123D8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112A44_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112B08_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112E14_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112EB8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112F48_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112FD8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80112FF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113088_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801130CC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801130E8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113204_option);

s32 func_80113218_option(s32 arg0) {
    return func_801109AC_option(arg0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011323C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113258_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113274_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113290_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801132AC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801132C8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801132E4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113300_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011331C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113338_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113368_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113384_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801133A0_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801133BC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801133EC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113408_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113424_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113440_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011345C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80113490_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146BC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146C8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146D4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_801146E0_option);
