#include "common.h"
#include "overlays/option.h"
#include "mallocblock.h"

extern Vec D_801146BC_option;
extern Vec D_801146C8_option;
extern Vec D_801146D4_option;
extern Vec D_801146E0_option;
extern Vec D_80114674_option;
extern Vec D_80114680_option;
extern OptSprSlot D_80114EF0_option[0x40];
extern OptSpr D_801147F0_option[0x40];
extern UnkOption D_80114F70_option[0x40];
extern s16 D_80115A70_option;
extern u16 D_80115A72_option;
extern OptWinEntry D_80115A78_option[0x20];
extern u8 D_800D09A8_main;
extern s32 D_801139D0_option;

void func_801133BC_option(s32, u32);
void func_80113368_option(s32, s32 *, s32 *);
void func_8011323C_option(s32);
void func_80113258_option(s32);
void func_80113490_option(s32);
void func_80113424_option(s32);
s32 func_801130E8_option(s32);
void func_801133EC_option(s32);
void func_8000BBFC_main(u16, s16);
void func_8000BD94_main(u16, s32, s32);
void func_8000BDDC_main(u16, s32);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BE5C_main(u16, f32, f32);
void func_80033910_main(HmfData *);
void func_80112F48_option(s32, s32, f32, f32, f32);
void func_8011331C_option(s32, s32, u16);
void func_801132AC_option(s32, s32);
void func_801132C8_option(s32, s32);
void func_801132E4_option(s32, u32);
void func_80112EB8_option(s32, s32, f32, f32, f32);
void func_80112FF4_option(s32, s32, f32, f32, f32);
void func_80112FD8_option(s32, s32, s32);
void func_80106508_option(Vec *, Vec *, Vec *);
void func_80113088_option(void);
void func_80105FF8_option(Vec *, Vec *, Vec *);
void func_80113274_option(s32, f32 *, f32 *, f32 *);
void func_80113290_option(s32, f32, f32, f32);
void func_80105E40_option(void);
void func_80112060_option(void);
void func_8011053C_option(s32, s32, s32);
void func_8011019C_option(void);
void func_80110754_option(void);
void func_801119CC_option(void);
void func_8011083C_option(s32, s32, s32);
void func_801110C0_option(s32, u32, s32, s32, u16, u16, s16);
void func_80111A10_option(s32);
void func_80111C50_option(s32, u32);
void func_80112028_option(s32, s32, s32);
void func_801130CC_option(void);
s32 func_80113218_option(s32);
void func_80113338_option(s32, s32, s16, s16, u16);
void func_80113384_option(s32);
void func_801133A0_option(s32);
void func_80113408_option(s32, u32);
void func_80113440_option(s32);
s32 func_8011345C_option(s32);
void func_801123D8_option(void);
void func_80113300_option(s32);
void func_80112A44_option(void);
void func_80105D10_option(void);
void func_80105D5C_option(f32 fov, f32 nearPlane, f32 farPlane);
void func_80105DA0_option(s32 camId, f32 fov);
void func_80105F08_option(f32 fov);

void func_80110170_option(void) {
    func_8011019C_option();
    func_80110754_option();
    func_801119CC_option();
}

void func_8011019C_option(void) {
    s32 i;
    OptSpr *p;
    f32 zero;

    for (i = 0; i < ARRAY_COUNT(D_801147F0_option); i++) {
        D_80114EF0_option[i].espriteSlot = -1;
        D_801147F0_option[i].espriteSlot = -1;
        p = &D_801147F0_option[i];
        zero = 0.0f;
        p->unk_08 = 0;
        D_801147F0_option[i].unk_04 = 0;
        p->unk_10 = zero;
        D_801147F0_option[i].unk_0C = zero;
        D_801147F0_option[i].unk_14 = zero;
        D_801147F0_option[i].unk_18 = -1;
    }
}

s16 func_80110230_option(s32 arg0) {
    return D_80114EF0_option[arg0].espriteSlot;
}

s16 func_80110244_option(s32 arg0) {
    return D_801147F0_option[arg0].espriteSlot;
}

void func_80110260_option(s32 arg0, s32 arg1) {
    D_80114EF0_option[arg0].espriteSlot = func_8000B838_main(arg1);
}

void func_80110298_option(s32 arg0) {
    if (D_80114EF0_option[arg0].espriteSlot != -1) {
        HuSprKill(D_80114EF0_option[arg0].espriteSlot);
    }
    D_80114EF0_option[arg0].espriteSlot = -1;
}

void func_801102F0_option(s32 arg0, s16 arg1) {
    D_801147F0_option[arg0].espriteSlot = InitEspriteSlot(D_80114EF0_option[arg1].espriteSlot, 0, 0);
    func_8011053C_option(arg0, 0xA0, 0x78);
}

void func_80110358_option(s32 arg0) {
    if (D_801147F0_option[arg0].espriteSlot != -1) {
        func_8000C184_main(D_801147F0_option[arg0].espriteSlot);
    }
    D_801147F0_option[arg0].espriteSlot = -1;
}

void func_801103C8_option(s32 arg0, s32 resourceId) {
    func_80110260_option(arg0, resourceId);
    func_801102F0_option(arg0, arg0);
}

void func_801103FC_option(s32 arg0, s32 resourceId) {
    func_801103C8_option(arg0, resourceId);
    func_8000BC48_main(D_801147F0_option[arg0].espriteSlot, 0x4000);
}

void func_80110440_option(s32 arg0) {
    func_80110358_option(arg0);
    func_80110298_option(arg0);
}

void func_8011046C_option(void) {
    s32 i;
    for (i = 0; i < ARRAY_COUNT(D_801147F0_option); i++) {
        func_80110440_option(i);
    }
}

void func_801104A4_option(s32 arg0) {
    func_8000BB54_main(D_801147F0_option[arg0].espriteSlot);
}

void func_801104D4_option(s32 arg0) {
    func_8000BB94_main(D_801147F0_option[arg0].espriteSlot);
}

void func_80110504_option(s32 arg0) {
    func_801104A4_option(arg0);
}

void func_80110520_option(s32 arg0) {
    func_801104D4_option(arg0);
}

void func_8011053C_option(s32 arg0, s32 arg1, s32 arg2) {
    D_801147F0_option[arg0].unk_04 = arg1;
    D_801147F0_option[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

void func_80110594_option(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = D_801147F0_option[arg0].unk_04;
    *arg2 = D_801147F0_option[arg0].unk_08;
}

void func_801105C4_option(s32 arg0, f32 arg1, f32 arg2) {
    D_801147F0_option[arg0].unk_0C = arg1;
    D_801147F0_option[arg0].unk_10 = arg2;
    func_8000BE5C_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

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

void func_801106E8_option(s32 arg0, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_801147F0_option[arg0].espriteSlot, 1);
    func_8000BD94_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

void func_80110754_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114F70_option); i++) {
        D_80114F70_option[i].unk_00 = -1;
        D_80114F70_option[i].unk_02 = -1;
    }
}

void func_801107A0_option(s32 arg0, s32 arg1, s32 arg2) {
    s16 model;

    model = func_8000B108_main(arg1, arg2);
    D_80114F70_option[arg0].unk_00 = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.0f, 1.0f, 1.0f);
}

void func_8011083C_option(s32 arg0, s32 resourceId, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(resourceId);
    D_80114F70_option[arg0].unk_02 = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_801108C4_option(s32 arg0) {
    if (D_80114F70_option[arg0].unk_00 != -1) {
        func_8001ACDC_main(D_80114F70_option[arg0].unk_00);
        D_80114F70_option[arg0].unk_00 = -1;
    }
    if (D_80114F70_option[arg0].unk_02 != -1) {
        func_8002D4B8_main(D_80114F70_option[arg0].unk_02);
        D_80114F70_option[arg0].unk_02 = -1;
    }
}

void func_80110974_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114F70_option); i++) {
        func_801108C4_option(i);
    }
}

s16 func_801109AC_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_00;
}

s16 func_801109D0_option(s32 arg0) {
    return D_80114F70_option[arg0].unk_02;
}

void func_801109F4_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_1C = arg1;
    D_80114F70_option[arg0].unk_20 = arg2;
    D_80114F70_option[arg0].unk_24 = arg3;
    Hu3DModelRotSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110A5C_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_04 = arg1;
    D_80114F70_option[arg0].unk_08 = arg2;
    D_80114F70_option[arg0].unk_0C = arg3;
    Hu3DModelPosSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110AD0_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80114F70_option[arg0].unk_10 = arg1;
    D_80114F70_option[arg0].unk_14 = arg2;
    D_80114F70_option[arg0].unk_18 = arg3;
    Hu3DModelScaleSet(D_80114F70_option[arg0].unk_00, arg1, arg2, arg3);
}

void func_80110B38_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg1 = D_80114F70_option[arg0].unk_04;
    *arg2 = D_80114F70_option[arg0].unk_08;
    *arg3 = D_80114F70_option[arg0].unk_0C;
}

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

void func_80110CE0_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4) {
    func_8001C624_main(D_80114F70_option[arg0].unk_00, D_80114F70_option[arg1].unk_02, arg2, arg3, arg4);
}

void func_80110D50_option(s32 arg0, s32 arg1) {
    func_8001C814_main(D_80114F70_option[arg0].unk_00, arg1, 0);
}

void func_80110D94_option(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_80114F70_option[arg0].unk_00);
}

void func_80110DCC_option(s32 arg0, u32 arg1) {
    func_8001C6A8_main(D_80114F70_option[arg0].unk_00, arg1);
}

void func_80110E30_option(s32 arg0) {
    while (HmfModelData[D_80114F70_option[arg0].unk_00].unk40 != D_800CCF58_main[HmfModelData[D_80114F70_option[arg0].unk_00].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80110ED0_option(s32 arg0) {
    s16 modelId = D_80114F70_option[arg0].unk_00;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void func_80110F58_option(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = func_801109AC_option(arg0);
    s16 parentModelId = func_801109D0_option(arg1);

    func_8001F304_main(modelId, parentModelId);
    func_8001C814_main(modelId, -1, arg2);
}

void func_80110FC8_option(void) {
    // The original call omits the resource id.
    D_80115A70_option = ((s16 (*)())func_8000B838_main)();
    D_80115A72_option = InitEspriteSlot(D_80115A70_option, 0, 0);
    func_8000BC48_main(D_80115A72_option, 0x4000);
    func_8000BBD4_main(D_80115A72_option, 0xA0, 0x78);
}

void func_8011102C_option(void) {
    func_8000C184_main(D_80115A72_option);
    HuSprKill(D_80115A70_option);
}

u32 func_80111058_option(u32 arg0) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/option/53DCA0", func_801110C0_option);

s32 func_8011130C_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_8005BEE0_main(winID, 255);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C154_main(winID, 192, 192, 192);
    func_8005FBF8_main(winID, 0, 64, 64);
    func_8005C02C_main(winID, 7);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111458_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 4);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_8005BEE0_main(winID, 255);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C060_main(winID, 5, 0, 176, 192);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005C154_main(winID, 192, 192, 192);
    func_8005FBF8_main(winID, 255, 255, 255);
    func_8005C02C_main(winID, 1);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_801115C0_option(s32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 winID;

    winID = func_8005A968_main(x, y, width, height, 0, 8);
    func_8005B63C_main(winID, -1, 17);
    func_8005BDFC_main(winID, 0);
    func_80060144_main(winID);
    func_8005BE30_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005C060_main(winID, 5, 0, 176, 192);
    func_8005C060_main(winID, 7, 255, 255, 255);
    func_8005C060_main(winID, 0, 0, 0, 0);
    func_8005C060_main(winID, 3, 0, 0, 0);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005C154_main(winID, 192, 192, 0);
    func_8005FBF8_main(winID, 255, 255, 255);
    func_8005C02C_main(winID, 6);
    func_8005D294_main(winID);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111768_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 19);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_80060C14_main(winID, 1);
    func_8005FE54_main(winID, 1);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111834_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 20);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_80060C14_main(winID, 0);
    func_8005FE54_main(winID, 1);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

s32 func_80111900_option(s32 message, s16 x, s16 y) {
    s16 winID;

    winID = func_80060880_main(x, y, 19);
    func_8005C060_main(winID, 2, 255, 64, 64);
    func_8005C060_main(winID, 4, 96, 255, 64);
    func_8005C060_main(winID, 6, 255, 255, 64);
    func_8005FE54_main(winID, 1);
    func_80060C14_main(winID, 0);
    func_8005B43C_main(winID, message, -1, -1);
    return winID;
}

void func_801119CC_option(void) {
    s32 i;

    for (i = 0; i < 0x20; i++) {
        D_80115A78_option[i].winID = -1;
        D_80115A78_option[i].unk_04 = 0;
    }
}

void func_80111A10_option(s32 arg0) {
    if (D_80115A78_option[arg0].unk_08 == 3) {
        func_80060EA8_main(D_80115A78_option[arg0].winID, 1);
        func_800610E0_main(D_80115A78_option[arg0].winID);
    } else {
        func_8005FE90_main(D_80115A78_option[arg0].winID);
        func_8005F364_main(D_80115A78_option[arg0].winID);
        D_80115A78_option[arg0].winID = -1;
    }
    if (D_80115A78_option[arg0].unk_04 != NULL) {
        func_80019C00_main(D_80115A78_option[arg0].unk_04);
        D_80115A78_option[arg0].unk_04 = NULL;
    }
}

void func_80111AF4_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80115A78_option); i++) {
        if (D_80115A78_option[i].winID != -1) {
            func_80111A10_option(i);
        }
    }
}

void func_80111B58_option(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BB18_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

void func_80111B88_option(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

void func_80111BF0_option(s32 arg0) {
    func_8005FFA8_main(D_80115A78_option[arg0].winID);
}

void func_80111C20_option(s32 arg0) {
    func_8005FE90_main(D_80115A78_option[arg0].winID);
}

void func_80111C50_option(s32 arg0, u32 arg1) {
    u32 message;

    func_8005D294_main(D_80115A78_option[arg0].winID);
    if (D_80115A78_option[arg0].unk_04 != NULL) {
        func_80019C00_main(D_80115A78_option[arg0].unk_04);
        D_80115A78_option[arg0].unk_04 = NULL;
    }
    message = func_80111058_option(arg1);
    if (message > 0x80000000U) {
        D_80115A78_option[arg0].unk_04 = (void *)message;
    }
    func_8005B43C_main(D_80115A78_option[arg0].winID, message, -1, -1);
}

void func_80111D1C_option(s32 arg0, s8 arg1, u32 arg2) {
    func_800601BC_main(D_80115A78_option[arg0].winID, arg2, arg1);
}

s32 func_80111D58_option(s32 arg0, s16 arg1, s32 arg2) {
    return func_8005E1D8_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

s16 func_80111D90_option(s32 arg0) {
    return D_80115A78_option[arg0].winID;
}

void func_80111DAC_option(s32 arg0) {
    while (func_8005E0C0_main(D_80115A78_option[arg0].winID) != 0) {
        HuPrcVSleep();
    }
}

void func_80111E00_option(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_80111E3C_option(s32 arg0, s16 arg1) {
    func_8005BE30_main(D_80115A78_option[arg0].winID, arg1);
}

u16 func_80111E74_option(s32 value) {
    static const char exitFormat[] = "\n%d\n";
    static const char posFormat[] = "POS:%4.2f,%4.2f,%4.2f";
    static const char atFormat[] = "A T:%4.2f,%4.2f,%4.2f";
    static const char upFormat[] = "U P:%4.2f,%4.2f,%4.2f";
    static const char valueFormat[] = "%d";
    char text[256];
    HmfData_UnkBC *cam;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, exitFormat, value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            cam = HmfModelData[gCameraList->unk4].hmf->unkBC;
            sprintf(text, posFormat, cam->unk08, cam->unk0C, cam->unk10);
            print8(16, 180, text);
            sprintf(text, atFormat, cam->unk14, cam->unk18, cam->unk1C);
            print8(16, 190, text);
            sprintf(text, upFormat, cam->unk20, cam->unk24, cam->unk28);
            print8(16, 200, text);
        } else {
            sprintf(text, valueFormat, value);
            print8(16, 220, text);
        }
        HuPrcVSleep();
    }
    return D_800D5558_main[0];
}

void func_80112028_option(s32 arg0, s32 arg1, s32 arg2) {
    func_8011053C_option(arg0, arg1, arg2);
}

void func_80112044_option(s32 arg0, u16 arg1) {
    func_80110614_option(arg0, arg1);
}

void func_80112060_option(void) {
    func_80110170_option();
    func_80105D10_option();
}

void func_80112084_option(void) {
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;

    func_80112FF4_option(0, 0xE0004, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE0007, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(3, 0xE0009, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(4, 0xE000A, 0.0f, 0.0f, 0.0f);
    func_80110C9C_option(4, 2);
    func_80112FD8_option(6, 0xE0005, 1);
    func_80112FD8_option(7, 0xE0006, 1);
    func_80112EB8_option(9, 0xA0000, -385.0f, -6.25f, -500.0f);
    func_80110AD0_option(9, 0.75f, 0.75f, 0.75f);
    func_80110C9C_option(9, 2);
    func_80112EB8_option(10, 0xA0000, 385.0f, -6.25f, -500.0f);
    func_80110AD0_option(10, 0.75f, 0.75f, 0.75f);
    func_80110C9C_option(10, 2);
    func_80017790_main(func_80113218_option(9), 0, 10, 0xA002A);
    model = func_80113218_option(10);
    func_80017790_main(model, 0, 10, 0xA002A);
    func_80017A84_main(model, 0, 10, 1, 0);
    func_80112FD8_option(11, 0xA001D, 1);
    func_80112FD8_option(12, 0xA001E, 1);
    func_80112FD8_option(13, 0xA001D, 1);
    func_80112FD8_option(14, 0xA001E, 1);
    func_80112FD8_option(15, 0xA0001, 1);
    func_80112EB8_option(20, 9, -385.0f, 0.049999997f, -500.0f);
    func_80112EB8_option(21, 9, 385.0f, 0.049999997f, -500.0f);
    func_80105DA0_option((s16)func_80113218_option(0), 68.0f);
    func_80105D5C_option(68.0f, 45.0f, 3200.0f);
    func_80105F08_option(68.0f);
    pos = D_80114674_option;
    at = D_80114680_option;
    func_80105FF8_option(&cameraPos, &cameraAt, &up);
    func_80106508_option(&pos, &at, &up);
    func_80113088_option();
}

void func_8011239C_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_80114674_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_80114680_option);

void func_801123D8_option(void) {
    static const char parrot[] = "oumu0_1_DEF";
    static const char trumpet[] = "tranpet_DEF";
    static const char drum[] = "doramu2_DEF";
    static const char cymbal[] = "sinbaru_DEF";
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;
    void *data;

    func_80112FF4_option(0, 0xE000D, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE000E, 0.0f, 0.0f, 0.0f);
    func_80112F48_option(2, 0xE0010, -250.0f, 0.0f, -401.15002f);
    func_801109F4_option(2, 0.0f, 10.0f, 0.0f);
    model = func_80113218_option(2);
    data = DataRead(0xE0020);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, (char *)parrot), 1, 0);
    DataClose(data);
    func_8001C448_main(model);
    func_80033910_main(HmfModelData[model].hmf);
    func_80112F48_option(3, 0xE0013, 250.0f, 0.0f, -401.15002f);
    func_801109F4_option(3, 0.0f, -11.0f, 0.0f);
    model = func_80113218_option(3);
    data = DataRead(0xE0021);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, (char *)trumpet), 1, 0);
    DataClose(data);
    data = DataRead(0xE0022);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, (char *)drum), 1, 0);
    DataClose(data);
    data = DataRead(0xE0023);
    func_80032FC0_main(HmfAnimCreate(HmfModelData[model].hmf, data, 0, (char *)cymbal), 1, 0);
    DataClose(data);
    func_8001C448_main(model);
    func_80033910_main(HmfModelData[model].hmf);
    func_80112F48_option(4, 0xE0016, 0.0f, 0.0f, 0.0f);
    func_80112F48_option(5, 0xE0019, 0.0f, 0.0f, 0.0f);
    func_80112FD8_option(17, 0xE0017, 0);
    func_80112FD8_option(18, 0xE0018, 0);
    func_80112FD8_option(19, 0xE001A, 0);
    func_80112FD8_option(20, 0xE001B, 0);
    if (!(D_800D09A8_main & 1)) {
        func_8011331C_option(4, 18, 0);
        func_801132C8_option(4, 7);
        func_801132AC_option(4, 2);
        func_801132E4_option(5, 1);
        func_801132C8_option(5, 7);
        func_801132AC_option(5, 4);
    } else {
        func_8011331C_option(5, 20, 0);
        func_801132C8_option(5, 7);
        func_801132AC_option(5, 2);
        func_801132E4_option(4, 1);
        func_801132C8_option(4, 7);
        func_801132AC_option(4, 4);
    }
    func_80112F48_option(6, 0xE001C, 90.0f, 108.2f, -300.0f);
    func_80112F48_option(7, 0xE001C, -90.0f, 108.2f, -300.0f);
    func_80112EB8_option(8, 0xA00B0, 0.0f, 20.0f, -401.15002f);
    func_80110C9C_option(8, 2);
    func_80017790_main(func_80113218_option(8), 0, 13, 0xA00B7);
    func_80112EB8_option(9, 0xE001E, 0.0f, 0.0f, 0.0f);
    func_80110C9C_option(9, 2);
    func_80112EB8_option(21, 0xE001F, 0.0f, 22.25f, -310.7f);
    func_80110C9C_option(21, 1);
    func_80112FD8_option(10, 0xA00B1, 0);
    func_80110F58_option(8, 10, 2);
    func_80112FD8_option(11, 0xA00B2, 2);
    func_80112FD8_option(12, 0xE000F, 0);
    func_80112FD8_option(13, 0xE0011, 0);
    func_80112FD8_option(14, 0xE0014, 0);
    func_80112FD8_option(15, 0xE0012, 0);
    func_80112FD8_option(16, 0xE0015, 0);
    func_801103C8_option(1, 0x30);
    func_801106B4_option(1, 5);
    func_8011053C_option(1, 160, 113);
    func_801104D4_option(1);
    func_801103C8_option(2, 0xE0024);
    func_801106B4_option(2, 10008);
    func_8011053C_option(2, 160, 113);
    func_801104D4_option(2);
    func_80105DA0_option((s16)func_80113218_option(0), 41.539f);
    func_80105F08_option(41.539f);
    pos = D_801146BC_option;
    at = D_801146C8_option;
    func_80105FF8_option(&cameraPos, &cameraAt, &up);
    func_80106508_option(&pos, &at, &up);
    func_80113088_option();
}

void func_80112A44_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_801108C4_option(13);
    func_801108C4_option(14);
    func_801108C4_option(15);
    func_801108C4_option(16);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_80112B08_option(void) {
    Vec pos, at, cameraPos, cameraAt, up;
    s16 model;

    func_80112EB8_option(0, 0xE0025, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(1, 0xE0026, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(2, 0xE0027, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(3, 0xE0028, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(4, 0xE0029, 0.0f, 0.0f, 0.0f);
    func_80112EB8_option(5, 0xE002A, 0.0f, 0.0f, 0.0f);
    func_80112FF4_option(6, 0xE002B, 0.0f, 0.0f, 0.0f);
    func_80110C1C_option(6);
    func_80112FF4_option(7, 0xE002C, 0.0f, 0.0f, 0.0f);
    func_80110C1C_option(7);
    func_80112EB8_option(8, 0xA008E, -74.973503f, 56.406998f, -735.0f);
    func_80110C9C_option(8, 2);
    func_80017790_main(func_80113218_option(8), 0, 9, 0xA00A3);
    func_80112EB8_option(9, 0xA00A2, 64.973503f, 60.8265f, -720.0f);
    func_80110C9C_option(9, 2);
    model = func_80113218_option(9);
    func_80017790_main(model, 0, 8, 0xA00A3);
    func_80017A84_main(model, 0, 8, 1, 0);
    func_80112FD8_option(10, 0xA009E, 1);
    func_80110F58_option(8, 10, 2);
    func_80112FD8_option(11, 0xA009F, 1);
    func_80110F58_option(9, 11, 2);
    func_80112FD8_option(12, 0xA008F, 1);
    func_80105DA0_option((s16)func_80113218_option(6), 55.0f);
    func_80105D5C_option(50.0f, 12.0f, 4800.0f);
    func_80105F08_option(50.0f);
    pos = D_801146D4_option;
    at = D_801146E0_option;
    func_80105FF8_option(&cameraPos, &cameraAt, &up);
    func_80106508_option(&pos, &at, &up);
    func_80113088_option();
}

void func_80112E14_option(void) {
    func_801130CC_option();
    func_80105E40_option();
    func_801108C4_option(0);
    func_801108C4_option(1);
    func_801108C4_option(2);
    func_801108C4_option(3);
    func_801108C4_option(4);
    func_801108C4_option(5);
    func_801108C4_option(6);
    func_801108C4_option(7);
    func_801108C4_option(8);
    func_801108C4_option(9);
    func_801108C4_option(10);
    func_801108C4_option(11);
    func_801108C4_option(12);
    func_80110974_option();
    func_8011046C_option();
    func_80111AF4_option();
}

void func_80112EB8_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x2A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80112F48_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x6A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80112FD8_option(s32 arg0, s32 resourceId, s32 arg2) {
    func_8011083C_option(arg0, resourceId, arg2);
}

void func_80112FF4_option(s32 arg0, s32 arg1, f32 x, f32 y, f32 z) {
    func_801107A0_option(arg0, arg1, 0x2002A9);
    func_80110A5C_option(arg0, x, y, z);
    func_80110AD0_option(arg0, 1.0f, 1.0f, 1.0f);
    func_80110DCC_option(arg0, 0);
    func_80110C9C_option(arg0, 1);
}

void func_80113088_option(void) {
    func_801103C8_option(0, 0x88);
    func_801106B4_option(0, 5);
    func_8011053C_option(0, 0xA0, 0x71);
    func_801104D4_option(0);
}

void func_801130CC_option(void) {
    func_80110440_option(0);
}

s32 func_801130E8_option(s32 pad) {
    s32 x, y;
    s32 absX, absY;

    x = D_800CBB6E_main[pad];
    y = D_800D20A1_main[pad];

    if (D_801139D0_option != 0) {
        if ((x == 0) & (y == 0)) {
            D_801139D0_option = 0;
        }
        return 0;
    }
    if ((x != 0) | (y != 0)) {
        absX = __builtin_abs(x);
        absY = __builtin_abs(y);
        if (absY < absX) {
            if (absY * 2 < absX) {
                D_801139D0_option = x < 0 ? 0x200 : 0x100;
            } else if (y > 0) {
                D_801139D0_option = x < 0 ? 0xA00 : 0x900;
            } else {
                D_801139D0_option = x < 0 ? 0x600 : 0x500;
            }
        } else if (absX * 2 < absY) {
            D_801139D0_option = y < 0 ? 0x400 : 0x800;
        } else if (y > 0) {
            D_801139D0_option = x < 0 ? 0xA00 : 0x900;
        } else {
            D_801139D0_option = x < 0 ? 0x600 : 0x500;
        }
    }
    return D_801139D0_option;
}

u16 func_80113204_option(s32 arg0) {
    return (u16)D_800D0590_main[arg0];
}

s32 func_80113218_option(s32 arg0) {
    return func_801109AC_option(arg0);
}

void func_8011323C_option(s32 arg0) {
    func_80110C5C_option(arg0);
}

void func_80113258_option(s32 arg0) {
    func_80110C1C_option(arg0);
}

void func_80113274_option(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    func_80110B38_option(arg0, arg1, arg2, arg3);
}

void func_80113290_option(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_801109F4_option(arg0, arg1, arg2, arg3);
}

void func_801132AC_option(s32 arg0, s32 arg1) {
    func_80110C9C_option(arg0, arg1);
}

void func_801132C8_option(s32 arg0, s32 arg1) {
    func_80110D50_option(arg0, arg1);
}

void func_801132E4_option(s32 arg0, u32 arg1) {
    func_80110DCC_option(arg0, arg1);
}

void func_80113300_option(s32 arg0) {
    func_80110E30_option(arg0);
}

void func_8011331C_option(s32 arg0, s32 arg1, u16 arg2) {
    func_80110F58_option(arg0, arg1, arg2);
}

void func_80113338_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, u16 arg4) {
    func_80110CE0_option(arg0, arg1, arg2, arg3, arg4);
}

void func_80113368_option(s32 arg0, s32 *arg1, s32 *arg2) {
    func_80110594_option(arg0, arg1, arg2);
}

void func_80113384_option(s32 arg0) {
    func_80110504_option(arg0);
}

void func_801133A0_option(s32 arg0) {
    func_80110520_option(arg0);
}

void func_801133BC_option(s32 arg0, u32 arg1) {
    func_801110C0_option(arg0, arg1, 0xA0, 0xC2, 0, 0, 4);
}

void func_801133EC_option(s32 arg0) {
    func_80111A10_option(arg0);
}

void func_80113408_option(s32 arg0, u32 arg1) {
    func_80111C50_option(arg0, arg1);
}

void func_80113424_option(s32 arg0) {
    func_80111BF0_option(arg0);
}

void func_80113440_option(s32 arg0) {
    func_80111C20_option(arg0);
}

s32 func_8011345C_option(s32 arg0) {
    func_80111DAC_option(arg0);
    return func_80111D58_option(arg0, 0, 0);
}

void func_80113490_option(s32 arg0) {
    func_80111DAC_option(arg0);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_801146BC_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_801146C8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_801146D4_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/53DCA0", D_801146E0_option);
