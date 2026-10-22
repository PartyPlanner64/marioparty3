#include "common.h"
#include "game/vibrator.h"
#include "mallocblock.h"

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
    /* 0x18 */ u8 unk_18;
    /* 0x19 */ u8 unk_19[3];
} OptSpr; // sizeof 0x1C

typedef struct {
    /* 0x00 */ s16 espriteSlot;
} OptSprSlot; // sizeof 0x2

typedef struct {
    /* 0x00 */ s16 winID;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
} OptWinEntry; // sizeof 0xC

// One entry per on-screen cursor; the object is the 3D cursor for that slot.
typedef struct {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec unk_18;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ omObjData *obj;
} OptCursor; // sizeof 0x2C

typedef struct {
    /* 0x00 */ Process *prcObj;
    /* 0x04 */ Vec pos;
    /* 0x10 */ Vec at;
    /* 0x1C */ Vec up;
    /* 0x28 */ f32 fov;
    /* 0x2C */ f32 nearPlane;
    /* 0x30 */ f32 farPlane;
    /* 0x34 */ s16 camId;
    /* 0x38 */ omObjData *obj;
} OptCam; // sizeof 0x3C

// Object that keeps an attached 3d model sound playing for a fixed duration.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 playSeNo;
    /* 0x06 */ s16 stopSeNo;
} OptSeObj; // sizeof 0x8

extern OptCam D_801146F0_option;
extern OptCursor D_80114788_option[2];
extern OptSeObj D_801147E0_option;
extern s32 D_801147E8_option;
extern OptSprSlot D_80114EF0_option[0x40];
extern OptSpr D_801147F0_option[0x40];
extern UnkOption D_80114F70_option[0x40];
extern s16 D_80115A70_option;
extern u16 D_80115A72_option;
extern OptWinEntry D_80115A78_option[0x20];
extern u8 D_800D09A8_main;

void func_8000BBFC_main(u16, s16);
void func_8000BD94_main(u16, s32, s32);
void func_8000BDDC_main(u16, s32);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BE5C_main(u16, f32, f32);
void func_80013350_main(s16);
void func_80033910_main(HmfData *);
void func_801059D0_option(void);
void func_80108A68_option(void);
void func_8011053C_option(s32, s32, s32);
s32 func_80113218_option(s32);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801059D0_option);

void func_80105C14_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C38_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

void func_80105C5C_option(void) {
    func_801059D0_option();
    func_80108A68_option();
}

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

void func_80105E40_option(void) {
    if (D_801146F0_option.prcObj != NULL) {
        omDelPrcObj(D_801146F0_option.prcObj);
    } else {
        while (1) {
            HuPrcVSleep();
        }
    }

    if (D_801146F0_option.camId != -1) {
        func_80013350_main(0);
        D_801146F0_option.camId = -1;
    }

    D_801146F0_option.prcObj = NULL;
}

void func_80105EB8_option(void) {
    while (1) {
        Hu3DCamSetPositionOrientation(0, &D_801146F0_option.pos, &D_801146F0_option.at, &D_801146F0_option.up);
        Hu3DCamUpdateMtx(0);
        HuPrcVSleep();
    }
}

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

void func_80109CB0_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            val1 = 0xA0;
            val2 = 0x50;
            break;
        case 1:
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
        case 4:
            val1 = 0xA0;
            val2 = 0x6E;
            break;
        case 5:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

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

void func_8010A8DC_option(s32 arg0, s32 *arg1, s32 *arg2) {
    s32 val1 = 0xA0;
    s32 val2 = 0x78;

    switch (arg0) {
        case 0:
            if (!(D_800D09A8_main & 1)) {
                val1 = 0xE0;
                val2 = 0x38;
            } else {
                val1 = 0xB8;
                val2 = 0x38;
            }
            break;
        case 1:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 2:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 3:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 4:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 5:
            val1 = 0xA0;
            val2 = 0x82;
            break;
        case 6:
        default:
            break;
    }

    *arg1 = val1;
    *arg2 = val2;
}

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

void func_8010FA28_option(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114788_option); i++) {
        omDelObj(D_80114788_option[i].obj);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FA7C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FB40_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D78_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113D90_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_80113DA8_option);

INCLUDE_RODATA("asm/nonmatchings/overlays/option/533500", D_8011421C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FC40_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FDF4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FE00_option);

void func_8010FE10_option(void) {
    s16 modelId;

    if (D_801147E0_option.obj != NULL) {
        modelId = func_80113218_option(2);
        func_80033910_main(HmfModelData[modelId].hmf);
        HuAudFXStop(D_801147E0_option.stopSeNo);
        omDelObj(D_801147E0_option.obj);
        D_801147E0_option.obj = NULL;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FE84_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FF0C_option);

void func_8010FF88_option(void) {
    s32 *counter;

    if (D_801147E8_option == 0) {
        RepeatVibrator(0, 5, 0, 5);
    }

    counter = &D_801147E8_option;
    *counter = (*counter < 11) ? *counter + 1 : 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8010FFDC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110018_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110170_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110230_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110244_option);

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

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801103C8_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801103FC_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110440_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_8011046C_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801104A4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_801104D4_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110504_option);

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110520_option);

void func_8011053C_option(s32 arg0, s32 arg1, s32 arg2) {
    D_801147F0_option[arg0].unk_04 = arg1;
    D_801147F0_option[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_801147F0_option[arg0].espriteSlot, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/option/533500", func_80110594_option);

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

void func_80110CE0_option(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80114F70_option[arg0].unk_00, D_80114F70_option[arg1].unk_02, arg2, arg3, arg4);
}

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

s32 func_80110ED0_option(s32 arg0) {
    s16 modelId = D_80114F70_option[arg0].unk_00;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void func_80110F58_option(s32 arg0, s32 arg1, s16 arg2) {
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

void func_80111B88_option(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80115A78_option[arg0].winID, arg1, arg2);
}

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
