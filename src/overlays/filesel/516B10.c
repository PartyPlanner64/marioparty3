#include "common.h"
#include "game/vibrator.h"
#include "game/gamework_data.h"
#include "mallocblock.h"

#define UNK_VALUE 0x91

typedef struct UnkFileSelect2 {
    s16 unk_00;
    u32 unk_04; // can be messageID or message pointer
    s32 unk_08;
} UnkFileSelect2;

typedef struct UnkFileSelect {
    u8 unk_00;
    u8 unk_01[0xB];
    char unk_0C[0x1C];
    u8 unk_28;
    s32 unk_2C;
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    s32 unk_40;
    s32 unk_44;
    char unk_48[0x14];
    s32 unk_5C;
    s32 unk_60;
    char unk_64[0x14];
    s32 unk_78;
    char unk_7C[4];
    s32 unk_80;
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
    u8 unk_18;
    u8 unk_19[3];
} UnkFileSelect4; // sizeof 0x1C

typedef struct UnkFileSelect5 {
    omObjData *unk_00;
    Vec unk_04;
    Vec unk_10;
    char unk_1C[0x34];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
} UnkFileSelect5; // sizeof 0x5C

typedef struct UnkFileSelect6 {
    omObjData *unk_00;
    s32 unk_04;
    s32 unk_08;
    Vec unk_0C;
    Vec unk_18;
} UnkFileSelect6; // sizeof 0x24

typedef struct FileSelectCameraTransition {
    f32 distance;
    s32 frame;
    s32 duration;
} FileSelectCameraTransition;

typedef struct FileSelectCameraState {
    Vec center;
    Vec rotation;
    FileSelectCameraTransition transition;
} FileSelectCameraState;

void func_801059D0_filesel(void);
void func_801126C0_filesel(s32, u8 *, u8 *);
void func_80112758_filesel(void);
void func_80107C84_filesel(void);
void func_80112184_filesel(s32);
void func_801122B0_filesel(s32);
void func_80111790_filesel(omObjData *);
void func_80107CF8_filesel(void);
void func_801119F4_filesel(void);
void func_80111C30_filesel(void);
s32 func_8010B5D4_filesel(s32, s32, s32, s16 *, s16 *);
void func_8010E250_filesel(Vec *, Vec *, f32, Vec *, Vec *, Vec *);
void func_8010E740_filesel(s32);
void func_8010E864_filesel(void);
void func_8010F65C_filesel(void);
void func_80105C1C_filesel(void);
void func_801061D4_filesel(void);
void func_8010744C_filesel(void);
void func_80107490_filesel(s32);
void func_80105FBC_filesel(s32, s32, s32);
void func_801069D8_filesel(s32, s32, s16);
void func_801076D0_filesel(s32, u32);
s32 func_80108834_filesel(void);
void func_8010AB1C_filesel(s32, u32);
void func_8010A9B4_filesel(s32, u32, s32 *, s32 *);
void func_8010AB58_filesel(s32, u32);
void func_8010AB60_filesel(s32, u32);
void func_8010F8A4_filesel(omObjData *object);
void func_8010FC58_filesel(omObjData *object);
void func_8010FFA0_filesel(omObjData *object);
void func_801103A0_filesel(omObjData *object);
void func_801107AC_filesel(omObjData *object);
void func_80110FB0_filesel(u32);
void func_801110F0_filesel(u32);
void func_80111004_filesel(omObjData *);
void func_80111144_filesel(omObjData *);
void func_80110D0C_filesel(omObjData *);
void func_8011139C_filesel(s32);
void func_801113E8_filesel(omObjData *);
void func_80112630_filesel(omObjData *object);
s32 func_80111B14_filesel(s32);
u32 func_80106AD8_filesel(u32);
s32 func_8010AC58_filesel(s32);
s32 func_80112494_filesel(s32, u8 *);
void func_80050064_main(s32);
void func_8000BBFC_main(u16, s16);
void func_8000BC48_main(u16, u16);
void func_8000BC88_main(u16, u16);
void func_8000BCC8_main(u16, s32);
void func_8000BD94_main(u16, s32, s32);
void func_8000BE5C_main(u16, f32, f32);

extern s32 D_80112E90_filesel;
extern u16 D_800D1244_main;
extern UnkFileSelect D_801142DC_filesel[3];
extern u8 D_80114490_filesel[0x20];
extern UnkFileSelect2 D_80114158_filesel[0x20]; // sizeof 0xC
extern UnkFileSelect3 D_80113650_filesel[0x40];
extern UnkFileSelect4 D_80112ED0_filesel[0x40];
// the one-column second dimension keeps these indexed stores addressing the array base symbolically
extern s16 D_801135D0_filesel[0x40][1];
extern Process *D_80114504_filesel;
extern UnkFileSelect6 D_80114508_filesel[9];
extern UnkFileSelect5 D_80114598_filesel[3];
extern u8 *D_801127FC_filesel[];
extern s32 D_801127B0_filesel[];
extern s32 D_801127BC_filesel[][2];
extern s32 D_801127C0_filesel[][2];
extern u8 *D_80112844_filesel[];
extern u8 *D_8011288C_filesel[];
extern s16 D_80114150_filesel;
extern u16 D_80114152_filesel;
extern s32 D_8011448C_filesel;
extern s32 D_801146D8_filesel;
extern s32 D_801129A0_filesel;
extern u8 D_801129A4_filesel[];
extern s32 D_801146D4_filesel;
extern Process *D_80114468_filesel;
extern omObjData *D_8011446C_filesel;
extern s32 D_8011447C_filesel[4];
extern Vec D_801128A4_filesel[];
extern FileSelectCameraState D_801146B0_filesel;
extern u8 D_800D09A9_main;
extern s32 D_80114500_filesel;
extern f32 D_801144F8_filesel;
extern f32 D_801144FC_filesel;
extern f32 D_801128A0_filesel;
extern Vec D_801144D4_filesel;
extern Vec D_801144E0_filesel;
extern Vec D_801144EC_filesel;

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801059D0_filesel);

#ifdef NON_MATCHING
// The C body matches, but the original has eight bytes of trailing padding.
void func_80105BC0_filesel(void) {
    D_80112E90_filesel = 0;
    func_801059D0_filesel();
    func_80107C84_filesel();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80105BC0_filesel);
#endif

void func_80105BF0_filesel(void) {
    func_80105C1C_filesel();
    func_801061D4_filesel();
    func_8010744C_filesel();
}

void func_80105C1C_filesel(void) {
    UnkFileSelect4 *p;
    f32 zero;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80112ED0_filesel); i++) {
        D_801135D0_filesel[i][0] = -1;
        D_80112ED0_filesel[i].unk_00 = -1;
        // only these two of the seven field stores go through the pointer, the rest stay symbolic
        p = &D_80112ED0_filesel[i];
        p->unk_08 = 0;
        D_80112ED0_filesel[i].unk_04 = 0;
        zero = 0.0f;
        p->unk_10 = zero;
        D_80112ED0_filesel[i].unk_0C = zero;
        D_80112ED0_filesel[i].unk_14 = zero;
        D_80112ED0_filesel[i].unk_18 = 0xFF;
    }
}

s16 func_80105CB0_filesel(s32 arg0) {
    return D_801135D0_filesel[arg0][0];
}

s16 func_80105CC4_filesel(s32 arg0) {
    return D_80112ED0_filesel[arg0].unk_00;
}

void func_80105CE0_filesel(s32 arg0, s32 arg1) {
    D_801135D0_filesel[arg0][0] = func_8000B838_main(arg1);
}

void func_80105D18_filesel(s32 arg0) {
    if (D_801135D0_filesel[arg0][0] != -1) {
        HuSprKill(D_801135D0_filesel[arg0][0]);
    }
    D_801135D0_filesel[arg0][0] = -1;
}

void func_80105D70_filesel(s32 arg0, s16 arg1) {
    D_80112ED0_filesel[arg0].unk_00 = InitEspriteSlot(D_801135D0_filesel[arg1][0], 0, 0);
    func_80105FBC_filesel(arg0, 0xA0, 0x78);
}

void func_80105DD8_filesel(s32 arg0) {
    if (D_80112ED0_filesel[arg0].unk_00 != -1) {
        func_8000C184_main(D_80112ED0_filesel[arg0].unk_00);
    }
    D_80112ED0_filesel[arg0].unk_00 = -1;
}

void func_80105E48_filesel(s32 arg0, s32 arg1) {
    func_80105CE0_filesel(arg0, arg1);
    func_80105D70_filesel(arg0, arg0);
}

void func_80105E7C_filesel(s32 arg0, s32 arg1) {
    func_80105E48_filesel(arg0, arg1);
    func_8000BC48_main(D_80112ED0_filesel[arg0].unk_00, 0x4000);
}

void func_80105EC0_filesel(s32 arg0) {
    func_80105DD8_filesel(arg0);
    func_80105D18_filesel(arg0);
}

void func_80105EEC_filesel(void) {
    s32 i;

    for (i = 0; i < 0x40; i++) {
        func_80105EC0_filesel(i);
    }
}

void func_80105F24_filesel(s32 arg0) {
    func_8000BB54_main(D_80112ED0_filesel[arg0].unk_00);
}

void func_80105F54_filesel(s32 arg0) {
    func_8000BB94_main(D_80112ED0_filesel[arg0].unk_00);
}

void func_80105F84_filesel(s32 arg0) {
    func_80105F24_filesel(arg0);
}

void func_80105FA0_filesel(s32 arg0) {
    func_80105F54_filesel(arg0);
}

void func_80105FBC_filesel(s32 arg0, s32 arg1, s32 arg2) {
    D_80112ED0_filesel[arg0].unk_04 = arg1;
    D_80112ED0_filesel[arg0].unk_08 = arg2;
    func_8000BBD4_main(D_80112ED0_filesel[arg0].unk_00, arg1, arg2);
}

void func_80106014_filesel(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = D_80112ED0_filesel[arg0].unk_04;
    *arg2 = D_80112ED0_filesel[arg0].unk_08;
}

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

void func_80106168_filesel(s32 arg0, u16 arg1, u16 arg2) {
    func_8000BDDC_main(D_80112ED0_filesel[arg0].unk_00, 1);
    func_8000BD94_main(D_80112ED0_filesel[arg0].unk_00, arg1, arg2);
}

void func_801061D4_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80113650_filesel); i++) {
        D_80113650_filesel[i].unk_00 = -1;
        D_80113650_filesel[i].unk_02 = -1;
    }
}

void func_80106220_filesel(s32 arg0, s32 arg1, s32 arg2) {
    s16 modelId = func_8000B108_main(arg1, arg2);

    D_80113650_filesel[arg0].unk_00 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
}

void func_801062BC_filesel(s32 arg0, s32 arg1, s32 arg2) {
    void *data;

    if (arg2 == -1) {
        arg2 = 0x6AD;
    }
    data = DataRead(arg1);
    D_80113650_filesel[arg0].unk_02 = func_8001F1FC_main(data, (s16)arg2);
    DataClose(data);
}

void func_80106344_filesel(s32 arg0) {
    if (D_80113650_filesel[arg0].unk_00 != -1) {
        func_8001ACDC_main(D_80113650_filesel[arg0].unk_00);
        D_80113650_filesel[arg0].unk_00 = -1;
    }
    if (D_80113650_filesel[arg0].unk_02 != -1) {
        func_8002D4B8_main(D_80113650_filesel[arg0].unk_02);
        D_80113650_filesel[arg0].unk_02 = -1;
    }
}

void func_801063F4_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80113650_filesel); i++) {
        func_80106344_filesel(i);
    }
}

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

void func_801064DC_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_80113650_filesel[arg0].unk_04 = arg1;
    D_80113650_filesel[arg0].unk_08 = arg2;
    D_80113650_filesel[arg0].unk_0C = arg3;
    Hu3DModelPosSet(D_80113650_filesel[arg0].unk_00, arg1, arg2, arg3);
}

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

void func_80106760_filesel(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s16 arg4) {
    func_8001C624_main(D_80113650_filesel[arg0].unk_00, D_80113650_filesel[arg1].unk_02, arg2, arg3, arg4);
}

void func_801067D0_filesel(s32 arg0, s16 arg1) {
    func_8001C814_main(D_80113650_filesel[arg0].unk_00, arg1, 0);
}

void func_80106814_filesel(s32 arg0) {
    // The original call omits the scale argument.
    void (*setModelScale)() = (void (*)())func_8001C92C_main;

    setModelScale(D_80113650_filesel[arg0].unk_00);
}

void func_8010684C_filesel(s32 arg0, u32 arg1) {
    func_8001C6A8_main(D_80113650_filesel[arg0].unk_00, arg1);
}

void func_801068B0_filesel(s32 arg0) {
    while (HmfModelData[D_80113650_filesel[arg0].unk_00].unk40 !=
           D_800CCF58_main[HmfModelData[D_80113650_filesel[arg0].unk_00].unk02].unk02) {
        HuPrcVSleep();
    }
}

s32 func_80106950_filesel(s32 arg0) {
    s16 modelId = D_80113650_filesel[arg0].unk_00;

    return HmfModelData[modelId].unk40 == D_800CCF58_main[HmfModelData[modelId].unk02].unk02;
}

void func_801069D8_filesel(s32 arg0, s32 arg1, s16 arg2) {
    s16 modelId = func_8010642C_filesel(arg0);
    s16 parentModelId = func_80106450_filesel(arg1);

    func_8001F304_main(modelId, parentModelId);
    func_8001C814_main(modelId, -1, arg2);
}

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

s16 func_80106D8C_filesel(u32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 window = func_8005A968_main(x, y, width, height, 0, 8);

    func_8005B63C_main(window, -1, 0x11);
    func_8005BDFC_main(window, 0);
    func_8005BEE0_main(window, 255);
    func_80060144_main(window);
    func_8005BE30_main(window, 1);
    func_8005FE54_main(window, 1);
    func_8005C154_main(window, 192, 192, 192);
    func_8005FBF8_main(window, 0, 64, 64);
    func_8005C02C_main(window, 7);
    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_8005D294_main(window);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

s16 func_80106ED8_filesel(u32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 window = func_8005A968_main(x, y, width, height, 0, 4);

    func_8005B63C_main(window, -1, 0x11);
    func_8005BDFC_main(window, 0);
    func_8005BEE0_main(window, 255);
    func_80060144_main(window);
    func_8005BE30_main(window, 1);
    func_8005FE54_main(window, 1);
    func_8005C060_main(window, 5, 0, 176, 192);
    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_8005C154_main(window, 192, 192, 192);
    func_8005FBF8_main(window, 255, 255, 255);
    func_8005C02C_main(window, 1);
    func_8005D294_main(window);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

s16 func_80107040_filesel(u32 message, s16 x, s16 y, s16 width, s16 height) {
    s16 window = func_8005A968_main(x, y, width, height, 0, 8);

    func_8005B63C_main(window, -1, 0x11);
    func_8005BDFC_main(window, 0);
    func_80060144_main(window);
    func_8005BE30_main(window, 1);
    func_8005FE54_main(window, 1);
    func_8005C060_main(window, 5, 0, 176, 192);
    func_8005C060_main(window, 7, 255, 255, 255);
    func_8005C060_main(window, 0, 0, 0, 0);
    func_8005C060_main(window, 3, 0, 0, 0);
    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_8005C154_main(window, 192, 192, 0);
    func_8005FBF8_main(window, 255, 255, 255);
    func_8005C02C_main(window, 6);
    func_8005D294_main(window);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

s16 func_801071E8_filesel(u32 message, s16 x, s16 y) {
    s16 window = func_80060880_main(x, y, 19);

    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_80060C14_main(window, 1);
    func_8005FE54_main(window, 1);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

s16 func_801072B4_filesel(u32 message, s16 x, s16 y) {
    s16 window = func_80060880_main(x, y, 20);

    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_80060C14_main(window, 0);
    func_8005FE54_main(window, 1);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

s16 func_80107380_filesel(u32 message, s16 x, s16 y) {
    s16 window = func_80060880_main(x, y, 19);

    func_8005C060_main(window, 2, 255, 64, 64);
    func_8005C060_main(window, 4, 96, 255, 64);
    func_8005C060_main(window, 6, 255, 255, 64);
    func_8005FE54_main(window, 1);
    func_80060C14_main(window, 0);
    func_8005B43C_main(window, message, -1, -1);
    return window;
}

void func_8010744C_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114158_filesel); i++) {
        D_80114158_filesel[i].unk_00 = -1;
        D_80114158_filesel[i].unk_04 = 0;
    }
}

void func_80107490_filesel(s32 arg0) {
    if (D_80114158_filesel[arg0].unk_08 == 3) {
        func_80060EA8_main(D_80114158_filesel[arg0].unk_00, 1);
        func_800610E0_main(D_80114158_filesel[arg0].unk_00);
    } else {
        func_8005FE90_main(D_80114158_filesel[arg0].unk_00);
        func_8005F364_main(D_80114158_filesel[arg0].unk_00);
        D_80114158_filesel[arg0].unk_00 = -1;
    }
    if (D_80114158_filesel[arg0].unk_04 != 0) {
        func_80019C00_main((void *)D_80114158_filesel[arg0].unk_04);
        D_80114158_filesel[arg0].unk_04 = 0;
    }
}

void func_80107574_filesel(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80114158_filesel); i++) {
        if (D_80114158_filesel[i].unk_00 != -1) {
            func_80107490_filesel(i);
        }
    }
}

void func_801075D8_filesel(s32 arg0) {
    // The original call omits the position arguments.
    void (*setWindowPosition)() = (void (*)())func_8005BB18_main;

    setWindowPosition(D_80114158_filesel[arg0].unk_00);
}

void func_80107608_filesel(s32 arg0, f32 arg1, f32 arg2) {
    func_8005BA90_main(D_80114158_filesel[arg0].unk_00, arg1, arg2);
}

void func_80107670_filesel(s32 arg0) {
    func_8005FFA8_main(D_80114158_filesel[arg0].unk_00);
}

void func_801076A0_filesel(s32 arg0) {
    func_8005FE90_main(D_80114158_filesel[arg0].unk_00);
}

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

void func_8010779C_filesel(s32 arg0, s8 arg1, u32 arg2) {
    func_800601BC_main(D_80114158_filesel[arg0].unk_00, arg2, arg1);
}

void func_801077D8_filesel(s32 arg0, s16 arg1) {
    // The original call omits the final argument.
    s32 (*setWindowStyle)() = (s32 (*)())func_8005E1D8_main;

    setWindowStyle(D_80114158_filesel[arg0].unk_00, arg1);
}

s16 func_80107810_filesel(s32 arg0) {
    return D_80114158_filesel[arg0].unk_00;
}

void func_8010782C_filesel(s32 arg0) {
    while (func_8005E0C0_main(D_80114158_filesel[arg0].unk_00) != 0) {
        HuPrcVSleep();
    }
}

void func_80107880_filesel(s32 arg0) {
    do {
        HuPrcVSleep();
    } while (!(arg0 & D_800D5558_main[0]));
}

void func_801078BC_filesel(s32 arg0, s16 arg1) {
    func_8005BE30_main(D_80114158_filesel[arg0].unk_00, arg1);
}

u16 func_801078F4_filesel(s32 value) {
    char text[0x100];
    HmfData_UnkBC *camera;

    HuPrcSleep(3);
    while (1) {
        if (D_800D5558_main[0] & 0xD010) {
            sprintf(text, "\n%d\n", value);
            break;
        }
        if (D_800D5558_main[0] & 0x2000) {
            camera = HmfModelData[gCameraList[0].unk4].hmf->unkBC;
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

void func_80107AA8_filesel(void) {
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

void func_80107C50_filesel(omObjData *object) {
    if (D_800D5558_main[0] & B_BUTTON) {
        func_8001F38C_main(0xFF, 0, 0);
    }
}

void func_80107C84_filesel(void) {
    func_80105BF0_filesel();
    func_801119F4_filesel();
    func_80111C30_filesel();
    D_80114468_filesel = omAddPrcObj(func_80107CF8_filesel, 0x5000, 0x2000, 0);
    D_8011446C_filesel = omAddObj(6, 0, 0, -1, func_80107C50_filesel);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80107CF8_filesel);

void func_801083AC_filesel(void) {
    func_80105E48_filesel(1, 0x1F000D);
    func_80105F54_filesel(1);
    func_80105E48_filesel(2, 0x1F000E);
    func_80106168_filesel(2, 0, 0);
    func_801060CC_filesel(2, 0x800);
    func_80105F54_filesel(2);
    func_80105E48_filesel(3, 0x1F000F);
    func_80106168_filesel(3, 0, 0);
    func_801060CC_filesel(3, 0x800);
    func_80105F54_filesel(3);
}

void func_80108440_filesel(void) {
    func_80105EC0_filesel(1);
    func_80105EC0_filesel(2);
    func_80105EC0_filesel(3);
}

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

void func_80108878_filesel(void) {
    s32 state = func_80108834_filesel();

    if (state == 1 || state == 2) {
        func_80106168_filesel(2, 1, 0);
    } else {
        func_80106168_filesel(2, 0, 0);
    }
    if (state != 0) {
        func_80106168_filesel(3, 1, 0);
    } else {
        func_80106168_filesel(3, 0, 0);
    }
}

void func_801088DC_filesel(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i < 3; i++) {
    }
    func_80105F24_filesel(1);
    func_80105F24_filesel(2);
    func_80105F24_filesel(3);
    func_80108878_filesel();
    for (i = 0; i <= 10; i++) {
        progress = i * 0.1f;
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        HuVecCopyXYZ(&start, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&end, 224.0f, 40.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        func_80105FBC_filesel(1, position.x, position.y);
        func_80105FBC_filesel(2, position.x - 22.0f, position.y);
        func_80105FBC_filesel(3, position.x + 26.0f, position.y);
        HuPrcVSleep();
    }
}

void func_80108A94_filesel(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i <= 10; i++) {
        progress = 1.0f - i * 0.1f;
        if (progress < 0.0f) {
            progress = 0.0f;
        }
        HuVecCopyXYZ(&start, 352.0f, 40.0f, 0.0f);
        HuVecCopyXYZ(&end, 224.0f, 40.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        func_80105FBC_filesel(1, position.x, position.y);
        func_80105FBC_filesel(2, position.x - 22.0f, position.y);
        func_80105FBC_filesel(3, position.x + 26.0f, position.y);
        HuPrcVSleep();
    }
    func_80105F54_filesel(1);
    func_80105F54_filesel(2);
    func_80105F54_filesel(3);
}

void func_80108C34_filesel(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    func_80107670_filesel(4);
    for (i = 0; i <= 10; i++) {
        progress = i * 0.1f;
        if (progress > 1.0f) {
            progress = 1.0f;
        }
        HuVecCopyXYZ(&start, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&end, 160.0f, 192.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        func_80107608_filesel(4, 160.0f, (96.0f - progress * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
}

void func_80108D74_filesel(void) {
    Vec start;
    Vec end;
    Vec position;
    s32 i;
    f32 progress;

    for (i = 0; i <= 10; i++) {
        progress = 1.0f - i * 0.1f;
        if (progress < 0.0f) {
            progress = 0.0f;
        }
        HuVecCopyXYZ(&start, 160.0f, 288.0f, 0.0f);
        HuVecCopyXYZ(&end, 160.0f, 192.0f, 0.0f);
        position.x = (end.x - start.x) * progress + start.x;
        position.y = (end.y - start.y) * progress + start.y;
        func_80107608_filesel(4, 160.0f, (96.0f - progress * 96.0f) + 208.0f);
        HuPrcVSleep();
    }
    func_801076A0_filesel(4);
}

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

s32 func_801099A8_filesel(s32 selection, s32 option0, s32 option1, s32 option2) {
    s32 options[3];
    s32 timer = 0;
    s32 input;
    s32 extraInput;

    options[0] = option0;
    options[1] = option1;
    options[2] = option2;
    func_8010AB60_filesel(18, selection);
    while (1) {
        HuPrcVSleep();
        func_8010AB1C_filesel(18, selection);
        func_8010AB58_filesel(18, -(timer / 8));
        timer = timer < 20 ? timer + 1 : 0;
        input = D_800D1244_main;
        extraInput = func_80111B14_filesel(0);
        if (extraInput != -1) {
            input |= extraInput;
        }
        if (D_800D5558_main[0] & B_BUTTON) {
            return -1;
        }
        if (D_800D5558_main[0] & A_BUTTON) {
            HuAudFXPlay(3);
            if (options[selection] == 1) {
                break;
            }
        } else if (input & L_JPAD) {
            do {
                selection--;
                if (selection < 0) {
                    selection = 2;
                }
            } while (options[selection] != 1);
            func_8010AB60_filesel(18, selection);
        } else if (input & R_JPAD) {
            do {
                selection++;
                selection = selection < 3 ? selection : 0;
            } while (options[selection] != 1);
            func_8010AB60_filesel(18, selection);
        }
    }
    return selection;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80109B2C_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE0_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE4_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AE8_filesel);

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A028_filesel);

void func_8010A680_filesel(s32 fileIndex, f32 x, f32 y, f32 z) {
    s32 modelIndex = fileIndex;
    s32 nameIndex = fileIndex + 3;

    if (D_801142DC_filesel[fileIndex].unk_00 != UNK_VALUE) {
        func_80106220_filesel(modelIndex, 0x1F0029, 0x6A9);
    } else {
        func_80106220_filesel(modelIndex, 0x1F002A, 0x6A9);
    }
    func_801064DC_filesel(modelIndex, x, y, z);
    func_80106550_filesel(modelIndex, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(modelIndex, 0);
    func_8010671C_filesel(modelIndex, 1);
    func_8010669C_filesel(modelIndex);
    func_80106220_filesel(nameIndex, D_801127B0_filesel[fileIndex], 0x6A9);
    func_801064DC_filesel(nameIndex, x, y, z);
    func_80106550_filesel(nameIndex, 0.8f, 0.8f, 0.8f);
    func_8010684C_filesel(nameIndex, 0);
    func_8010671C_filesel(nameIndex, 1);
    func_8010669C_filesel(nameIndex);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010A7D8_filesel);

void func_8010A978_filesel(s32 arg0) {
    if (arg0 >= 6) {
        arg0 = 5;
    }
    func_80105FBC_filesel(19, arg0 * 10 + 104, 61);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112AF0_filesel);

void func_8010A9B4_filesel(s32 arg0, u32 arg1, s32 *arg2, s32 *arg3) {
    Vec pos;
    Vec2f screen;
    s32 x;
    s32 y;

    x = D_801127BC_filesel[arg1][0];
    y = D_801127C0_filesel[arg1][0];
    switch (arg1) {
        case 0:
        case 1:
        case 2:
            func_801065B8_filesel(arg1, &pos.x, &pos.y, &pos.z);
            pos.x += 30.0f;
            pos.y += 300.0f;
            Hu3DCam3DToScreen(0, &pos, &screen);
            x = screen.x;
            y = screen.y;
            break;
        case 3:
        case 4:
            x = D_801127BC_filesel[arg1][0];
            y = D_801127C0_filesel[arg1][0];
            break;
        case 5:
            HuVecCopyXYZ(&pos, -400.0f, 0.0f, 0.0f);
            goto project;
        case 6:
            HuVecCopyXYZ(&pos, 0.0f, 0.0f, 0.0f);
            goto project;
        case 7:
            HuVecCopyXYZ(&pos, 400.0f, 0.0f, 0.0f);
        project:
            Hu3DCam3DToScreen(0, &pos, &screen);
            x = screen.x + 31.0f;
            y = 168;
            break;
    }
    *arg2 = x;
    *arg3 = y;
}

void func_8010AB1C_filesel(s32 arg0, u32 arg1) {
    s32 x;
    s32 y;

    func_8010A9B4_filesel(arg0, arg1, &x, &y);
    func_80105FBC_filesel(arg0, x, y);
}

void func_8010AB58_filesel(s32 arg0, u32 arg1) {
}

void func_8010AB60_filesel(s32 arg0, u32 arg1) {
    s32 targetX;
    s32 targetY;
    s32 startX;
    s32 startY;
    s32 i;
    f32 progress;

    func_8010A9B4_filesel(arg0, arg1, &targetX, &targetY);
    func_80106014_filesel(arg0, &startX, &startY);
    for (i = 0; i < 5; i++) {
        progress = i * 0.25f;
        func_80105FBC_filesel(arg0, startX + progress * (targetX - startX),
                              startY + progress * (targetY - startY));
        HuPrcVSleep();
    }
    func_80105FBC_filesel(arg0, targetX, targetY);
}

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

void func_8010B598_filesel(u8 *arg0) {
    bzero(arg0, 0x20);
    bcopy(D_80114490_filesel, arg0, 0x20);
}

s32 func_8010B5D4_filesel(s32 arg0, s32 arg1, s32 arg2, s16 *arg3, s16 *arg4) {
    s32 x = 47;
    s32 y = 103;

    switch (arg0) {
        case 4:
        case 5:
            x += 5;
            y += 12;
            if (arg1 >= 10) {
                x += 5;
            }
            if (arg1 >= 11) {
                if (arg1 < 15) {
                    x += (arg1 - 10) * 2;
                } else {
                    x += 10;
                }
            }
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        case 6:
            x += 42;
            y += 12;
            x += arg1 * 12;
            y += arg2 * 13;
            break;
        default:
            x = 0;
            y = 0;
            break;
    }
    *arg3 = x;
    *arg4 = y;
    return 0;
}

void func_8010B684_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 4) {
        func_80105F54_filesel(4);
    }
    if (arg0 != 5) {
        func_80105F54_filesel(5);
    }
    if (arg0 != 6) {
        func_80105F54_filesel(6);
    }
}

void func_8010B6F4_filesel(s32 arg0) {
    if (arg0 != -1) {
        func_80105F24_filesel(arg0);
    }
    if (arg0 != 7) {
        func_80105F54_filesel(7);
        func_80105F54_filesel(0x30);
    } else {
        func_80105F24_filesel(0x30);
    }
    if (arg0 != 8) {
        func_80105F54_filesel(8);
        func_80105F54_filesel(0x31);
    } else {
        func_80105F24_filesel(0x31);
    }
    if (arg0 != 9) {
        func_80105F54_filesel(9);
        func_80105F54_filesel(0x32);
    } else {
        func_80105F24_filesel(0x32);
    }
    if (arg0 != 10) {
        func_80105F54_filesel(10);
        func_80105F54_filesel(0x33);
    } else {
        func_80105F24_filesel(0x33);
    }
    if (arg0 != 11) {
        func_80105F54_filesel(11);
        func_80105F54_filesel(0x34);
    } else {
        func_80105F24_filesel(0x34);
    }
    D_8011448C_filesel = 0;
}

#ifdef NON_MATCHING
// GCC folds the first alpha conversion; the original keeps the floating-point operations.
void func_8010B80C_filesel(s32 arg0) {
    s32 frame;
    s32 direction;
    f32 alpha;
    u32 opacity;

    frame = D_8011448C_filesel;
    if (frame < 0) {
        frame = -frame;
    }
    direction = D_8011448C_filesel >= 0;
    alpha = 1.0f;
    frame++;
    if (direction != 0) {
        opacity = alpha * 255.0f;
    } else {
        opacity = (1.0f - alpha) * 255.0f;
    }
    D_8011448C_filesel = frame;
    if (direction < 0) {
        D_8011448C_filesel = -D_8011448C_filesel;
    }
    if (arg0 != -1) {
        func_80106094_filesel(arg0, (u8)opacity);
    }
    if (arg0 != 7) {
        func_80106094_filesel(7, (u8)opacity);
    }
    if (arg0 != 8) {
        func_80106094_filesel(8, (u8)opacity);
    }
    if (arg0 != 9) {
        func_80106094_filesel(9, (u8)opacity);
    }
    if (arg0 != 10) {
        func_80106094_filesel(10, (u8)opacity);
    }
    if (arg0 != 11) {
        func_80106094_filesel(11, (u8)opacity);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010B80C_filesel);
#endif

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

void func_8010BDC4_filesel(void) {
    s16 x;
    s16 y;

    func_8010B5D4_filesel(D_8011447C_filesel[0], D_8011447C_filesel[2], D_8011447C_filesel[3], &x, &y);
    func_80105FBC_filesel(0x11, x, y);
    func_80105F24_filesel(0x11);
}

void func_8010BE14_filesel(void) {
    func_80105F54_filesel(0x11);
}

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

void func_8010DD54_filesel(void) {
    func_80105EC0_filesel(0x14);
    func_80105EC0_filesel(0x15);
    func_80105EC0_filesel(0x16);
    func_80105EC0_filesel(0x17);
    func_80105EC0_filesel(0x18);
    func_80105EC0_filesel(0x19);
    func_80105EC0_filesel(0x1E);
    func_80105EC0_filesel(0x1D);
    func_80105EC0_filesel(0x1C);
    func_80105EC0_filesel(0x1B);
    func_80105EC0_filesel(0x1A);
}

void func_8010DDC0_filesel(s32 fileIndex) {
    func_80105F84_filesel(0x14);
    if (!_CheckFlag(0x18)) {
        func_80105FA0_filesel(0x15);
        func_80105FA0_filesel(0x16);
        func_80105FA0_filesel(0x17);
        func_80105FA0_filesel(0x18);
        func_80105F84_filesel(0x19);
        func_80105FA0_filesel(0x1A);
        func_80105FA0_filesel(0x1B);
        func_80105FA0_filesel(0x1C);
        func_80105FA0_filesel(0x1D);
        func_80105FA0_filesel(0x1E);
    } else {
        func_80105F84_filesel(0x15);
        func_80105F84_filesel(0x16);
        func_80105F84_filesel(0x17);
        func_80105F84_filesel(0x18);
        func_80105F84_filesel(0x19);
        if (_CheckFlag(0x28)) {
            func_80105F84_filesel(0x1E);
            func_80105F84_filesel(0x1C);
            func_80105F84_filesel(0x1D);
            func_80105F84_filesel(0x1A);
            if (D_801142DC_filesel[fileIndex].unk_38 / 10) {
                func_80105F84_filesel(0x1B);
            }
        }
    }
}

void func_8010DEEC_filesel(void) {
    func_80105FA0_filesel(0x14);
    func_80105FA0_filesel(0x15);
    func_80105FA0_filesel(0x16);
    func_80105FA0_filesel(0x17);
    func_80105FA0_filesel(0x18);
    func_80105FA0_filesel(0x19);
    func_80105FA0_filesel(0x1A);
    func_80105FA0_filesel(0x1B);
    func_80105FA0_filesel(0x1C);
    func_80105FA0_filesel(0x1D);
    func_80105FA0_filesel(0x1E);
}

void func_8010DF58_filesel(void) {
    func_80105EC0_filesel(0x1F);
    func_80105EC0_filesel(0x28);
    func_80105EC0_filesel(0x20);
    func_80105EC0_filesel(0x21);
    func_80105EC0_filesel(0x22);
    func_80105EC0_filesel(0x27);
    func_80105EC0_filesel(0x26);
    func_80105EC0_filesel(0x25);
    func_80105EC0_filesel(0x24);
    func_80105EC0_filesel(0x23);
    func_80105EC0_filesel(0x29);
    func_80105EC0_filesel(0x2A);
    func_80105EC0_filesel(0x2F);
    func_80105EC0_filesel(0x2E);
    func_80105EC0_filesel(0x2D);
    func_80105EC0_filesel(0x2C);
    func_80105EC0_filesel(0x2B);
}

void func_8010DFF4_filesel(s32 fileIndex) {
    func_80105F84_filesel(0x1F);
    func_80105F84_filesel(0x28);
    func_80105F84_filesel(0x20);
    if (!_CheckFlag(0x16)) {
        func_80105FA0_filesel(0x21);
        func_80105F84_filesel(0x22);
        func_80105FA0_filesel(0x27);
        func_80105FA0_filesel(0x26);
        func_80105FA0_filesel(0x25);
        func_80105FA0_filesel(0x24);
        func_80105FA0_filesel(0x23);
    } else {
        func_80105F84_filesel(0x21);
        func_80105F84_filesel(0x22);
        func_80105F84_filesel(0x27);
        func_80105F84_filesel(0x25);
        func_80105F84_filesel(0x26);
        func_80105F84_filesel(0x23);
        if (D_801142DC_filesel[fileIndex].unk_78 / 10) {
            func_80105F84_filesel(0x24);
        }
    }
    if (!_CheckFlag(0x17)) {
        func_80105FA0_filesel(0x29);
        func_80105F84_filesel(0x2A);
        func_80105FA0_filesel(0x2C);
        func_80105FA0_filesel(0x2B);
    } else {
        func_80105F84_filesel(0x29);
        func_80105F84_filesel(0x2F);
        if (D_801142DC_filesel[fileIndex].unk_60 == 20) {
            func_80105F84_filesel(0x2D);
            func_80105F84_filesel(0x2E);
            func_80105F84_filesel(0x2B);
            func_80105F84_filesel(0x2A);
            if (D_801142DC_filesel[fileIndex].unk_5C / 10) {
                func_80105F84_filesel(0x2C);
            }
        }
    }
}

void func_8010E1B4_filesel(void) {
    func_80105FA0_filesel(0x1F);
    func_80105FA0_filesel(0x28);
    func_80105FA0_filesel(0x20);
    func_80105FA0_filesel(0x21);
    func_80105FA0_filesel(0x22);
    func_80105FA0_filesel(0x27);
    func_80105FA0_filesel(0x26);
    func_80105FA0_filesel(0x25);
    func_80105FA0_filesel(0x24);
    func_80105FA0_filesel(0x23);
    func_80105FA0_filesel(0x29);
    func_80105FA0_filesel(0x2A);
    func_80105FA0_filesel(0x2F);
    func_80105FA0_filesel(0x2E);
    func_80105FA0_filesel(0x2D);
    func_80105FA0_filesel(0x2C);
    func_80105FA0_filesel(0x2B);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E250_filesel);

void func_8010E740_filesel(s32 arg0) {
    D_80114500_filesel = arg0;
    CRot.x = 0;
    CRot.y = 0;
    CRot.z = 0;
    Center.x = 0;
    Center.y = 200.0f;
    Center.z = 0;
    CZoom = 3000.0f;
    D_801144F8_filesel = 80.0f;
    D_801144FC_filesel = 8000.0f;
    D_801128A0_filesel = 20.0f;
    HuVecCopyXYZ(&D_801144D4_filesel, 10.0f, CRot.x, CRot.x);
    HuVecCopyXYZ(&D_801144E0_filesel, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&D_801144EC_filesel, 0.0f, 1.0f, 0.0f);
    Hu3DCamSetPerspective(0, D_801128A0_filesel, D_801144F8_filesel, D_801144FC_filesel);
    Hu3DCamSetPositionOrientation(0, &D_801144D4_filesel, &D_801144E0_filesel, &D_801144EC_filesel);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010E864_filesel);

void func_8010F10C_filesel(void) {
    omDelPrcObj(D_80114504_filesel);
}

void func_8010F12C_filesel(void) {
    func_8010E740_filesel(-1);
    D_80114504_filesel = omAddPrcObj(func_8010E864_filesel, 1, 0x2000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F168_filesel);

void func_8010F5C8_filesel(void) {
    func_80106344_filesel(0);
    func_80106344_filesel(1);
    func_80106344_filesel(2);
    func_80106344_filesel(3);
    func_80106344_filesel(4);
    func_80106344_filesel(5);
    func_80107490_filesel(1);
    func_80107490_filesel(2);
    func_80107490_filesel(3);
    func_80105EC0_filesel(13);
    func_80105EC0_filesel(14);
    func_80105EC0_filesel(15);
    func_80105EC0_filesel(18);
    func_80107490_filesel(0);
    func_8010F65C_filesel();
    func_80107490_filesel(4);
}

void func_8010F65C_filesel(void) {
    func_80105EC0_filesel(0xC);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112DF8_filesel);

INCLUDE_RODATA("asm/nonmatchings/overlays/filesel/516B10", D_80112E08_filesel);

void func_8010F678_filesel(s32 arg0) {
    s32 image;
    s32 x;
    s32 y;

    switch (arg0) {
        case 0:
            image = 0x1F001C;
            x = 0x5B;
            y = 0x21;
            break;
        case 1:
            image = 0x1F001D;
            x = 0x5E;
            y = 0x21;
            break;
        case 2:
            image = 0x1F001E;
            x = 0x36;
            y = 0x21;
            break;
        case 3:
            image = 0x1F001F;
            x = 0x3F;
            y = 0x21;
            break;
        case 4:
            image = 0x1F0022;
            x = 0x79;
            y = 0x1E;
            break;
        default:
            image = 0;
            y = 0;
            x = 0;
            break;
    }
    func_80105E7C_filesel(0xC, image);
    func_80106044_filesel(0xC, 1.0f, 1.0f);
    func_80106094_filesel(0xC, 0x100);
    func_80105FBC_filesel(0xC, x, y);
}

void func_8010F760_filesel(s32 arg0, s32 arg1) {
    Vec position;
    Vec2f screen;
    s32 x;
    s32 image;

    image = arg1 ? 0x1F0020 : 0x1F0021;
    position.x = D_801128A4_filesel[arg0].x;
    position.y = D_801128A4_filesel[arg0].y;
    position.z = D_801128A4_filesel[arg0].z;
    Hu3DCam3DToScreen(0, &position, &screen);
    x = screen.x;
    arg0 += 0xD;
    func_80105E48_filesel(arg0, image);
    func_80106044_filesel(arg0, 1.0f, 1.0f);
    func_80106094_filesel(arg0, 0x100);
    func_80105FBC_filesel(arg0, x, 0xB1);
}

void func_8010F844_filesel(s32 arg0) {
    func_80105F84_filesel(arg0 + 0xD);
    func_80107670_filesel(arg0 + 1);
}

void func_8010F874_filesel(s32 arg0) {
    func_80105FA0_filesel(arg0 + 0xD);
    func_801076A0_filesel(arg0 + 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010F8A4_filesel);

omObjData *func_8010FBE0_filesel(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010F8A4_filesel);

    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;

    func_801066DC_filesel(arg0);
    func_801066DC_filesel(arg0 + 3);
    return obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010FC58_filesel);

void func_8010FF48_filesel(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010FC58_filesel);

    obj->work[0] = arg0;
    obj->work[1] = arg1;
    obj->work[2] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_8010FFA0_filesel);

void func_801102F0_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].unk_00);
}

omObjData *func_80110320_filesel(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_8010FFA0_filesel);

    obj->work[0] = arg0;
    D_80114508_filesel[arg0].unk_00 = obj;
    D_80114508_filesel[arg0].unk_08 = arg1;
    D_80114508_filesel[arg0].unk_04 = 0;
    return obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801103A0_filesel);

void func_801106FC_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].unk_00);
}

void func_8011072C_filesel(s32 arg0, s32 arg1) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_801103A0_filesel);

    obj->work[0] = arg0;
    D_80114508_filesel[arg0].unk_00 = obj;
    D_80114508_filesel[arg0].unk_04 = 0;
    D_80114508_filesel[arg0].unk_08 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801107AC_filesel);

void func_80110B4C_filesel(s32 arg0) {
    omDelObj(D_80114508_filesel[arg0].unk_00);
}

omObjData *func_80110B7C_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_801107AC_filesel);
    f32 x;
    f32 y;
    f32 z;

    obj->work[0] = arg0;
    D_80114508_filesel[arg0].unk_00 = obj;
    D_80114508_filesel[arg0].unk_08 = arg4;
    D_80114508_filesel[arg0].unk_04 = 0;

    func_801065B8_filesel(arg0, &x, &y, &z);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].unk_0C, x, y, z);
    HuVecCopyXYZ(&D_80114508_filesel[arg0].unk_18, arg1, arg2, arg3);
    return obj;
}

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

void func_80110D0C_filesel(omObjData *object) {
    Vec start;
    Vec end;
    Vec position;
    s32 index;
    u32 slot;
    f32 fraction;
    f32 progress;

    index = object->work[0];
    slot = index;
    fraction = (f32)D_80114598_filesel[index].unk_50 / (f32)D_80114598_filesel[index].unk_58;
    progress = fraction > 1.0f ? 1.0f : fraction;
    HuVecCopy3F(&start, &D_80114598_filesel[index].unk_04);
    HuVecCopy3F(&end, &D_80114598_filesel[index].unk_10);
    HuVecCopyXYZ(&position, (end.x - start.x) * progress + start.x,
                 (end.y - start.y) * progress + start.y, (end.z - start.z) * progress + start.z);
    func_801064DC_filesel(slot, position.x, position.y, position.z);
    if (progress > 1.0f) {
        func_80110CC0_filesel(index);
    }
}

void func_80110E70_filesel(s32 arg0, omObjFunc arg1) {
    omObjData *obj;

    if (D_80114598_filesel[arg0].unk_00 != NULL) {
        omDelObj(D_80114598_filesel[arg0].unk_00);
    }
    obj = omAddObj(6, 0, 0, -1, arg1);
    obj->work[0] = arg0;
    D_80114598_filesel[arg0].unk_00 = obj;
}

void func_80110F04_filesel(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    Vec pos;
    Vec target;

    func_80110E70_filesel(arg0, func_80110D0C_filesel);
    func_8010642C_filesel(arg0);
    func_801065B8_filesel(arg0, &pos.x, &pos.y, &pos.z);
    HuVecCopy3F(&pos, &D_80114598_filesel[arg0].unk_04);
    HuVecCopyXYZ(&target, arg1, arg2, arg3);
}

void func_80110FB0_filesel(u32 arg0) {
    func_80110CC0_filesel(arg0);
    func_80106550_filesel(arg0, 0.8f, 0.8f, 0.8f);
    func_80106550_filesel(arg0 + 3, 0.8f, 0.8f, 0.8f);
}

void func_80111004_filesel(omObjData *object) {
    s32 index;
    s32 angle;
    f32 wave;
    f32 x;
    f32 y;

    index = object->work[0];
    angle = D_80114598_filesel[index].unk_50;
    angle += 27;
    if (angle > 360) {
        angle -= 360;
    }
    D_80114598_filesel[index].unk_50 = angle;
    wave = sindf(angle) * 0.1f;
    x = wave + 0.8f;
    y = 0.8f - wave;
    func_80106550_filesel(index, x, y, x);
    func_80106550_filesel(index + 3, x, y, x);
}

void func_801110F0_filesel(u32 arg0) {
    func_80110E70_filesel(arg0, func_80111004_filesel);
    D_80114598_filesel[arg0].unk_50 = 0;
    func_8010642C_filesel(arg0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111144_filesel);

void func_8011132C_filesel(s32 arg0) {
    func_80110E70_filesel(arg0, func_80111144_filesel);
    D_80114598_filesel[arg0].unk_58 = 45;
    D_80114598_filesel[arg0].unk_50 = 0;
    D_80114598_filesel[arg0].unk_54 = 0;
    func_8010642C_filesel(arg0);
}

void func_8011139C_filesel(s32 arg0) {
    omDelObj(D_80114598_filesel[arg0].unk_00);
    D_80114598_filesel[arg0].unk_00 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801113E8_filesel);

void func_80111660_filesel(s32 arg0, s32 arg1, s32 arg2) {
    Vec positions[3] = {
        { -400.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 400.0f, 0.0f, 0.0f }
    };

    func_80110E70_filesel(arg1, func_801113E8_filesel);
    func_8010642C_filesel(arg1);
    HuVecCopy3F(&D_80114598_filesel[arg1].unk_04, &positions[arg0]);
    D_80114598_filesel[arg1].unk_04.y += 100.0f;
    HuVecCopy3F(&D_80114598_filesel[arg1].unk_10, &positions[arg1]);
    D_80114598_filesel[arg1].unk_50 = 0;
    D_80114598_filesel[arg1].unk_58 = arg2;
}

void func_80111790_filesel(omObjData *object) {
    Vec center;
    Vec rotation;
    Vec position;
    Vec target;
    Vec up;
    f32 duration;
    f32 frame;
    f32 progress;
    f32 distance;

    duration = D_801146B0_filesel.transition.duration;
    frame = D_801146B0_filesel.transition.frame;
    HuVecCopy3F(&center, &D_801146B0_filesel.center);
    HuVecCopy3F(&rotation, &D_801146B0_filesel.rotation);
    progress = frame / duration;
    if (progress > 1.0f) {
        progress = 1.0f;
    }
    rotation.x = progress * -88.0f;
    distance = ((1.0f - progress) * 0.75f + 0.25f) * 3000.0f;
    HuVecCopy3F(&D_801146B0_filesel.center, &center);
    HuVecCopy3F(&D_801146B0_filesel.rotation, &rotation);
    D_801146B0_filesel.transition.distance = distance;
    func_8010E250_filesel(&center, &rotation, distance, &position, &target, &up);
    Hu3DCamSetPositionOrientation(0, &position, &target, &up);
    Hu3DCamUpdateMtx(0);
    if (frame == duration) {
        omDelObj(object);
    } else {
        frame += 1.0f;
        D_801146B0_filesel.transition.frame = frame;
    }
}

#ifdef NON_MATCHING
// The final state stores still use separate symbolic addresses instead of one base register.
omObjData *func_80111944_filesel(s32 duration) {
    omObjData *obj = omAddObj(6, 0, 0, -1, func_80111790_filesel);
    FileSelectCameraTransition *transition;

    obj->work[0] = 0;
    obj->work[1] = duration;
    obj->work[2] = 0;
    HuVecCopyXYZ(&D_801146B0_filesel.center, 0.0f, 200.0f, 0.0f);
    HuVecCopyXYZ(&D_801146B0_filesel.rotation, 0.0f, 0.0f, 0.0f);
    transition = &D_801146B0_filesel.transition;
    transition->distance = 3000.0f;
    transition->duration = duration;
    transition->frame = 0;
    return obj;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_80111944_filesel);
#endif

void func_801119F4_filesel(void) {
    D_801129A0_filesel = 0;
    D_801146D4_filesel = 0;
}

// converts one pad's analog stick position into a 8-way direction button mask,
// latching on the same direction repeating for a while
s32 func_80111A08_filesel(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;
    s32 direction;

    stickX = D_800CBB6E_main[arg0];
    stickY = D_800D20A1_main[arg0];

    if (((stickX != 0) | (stickY != 0)) == 0) {
        return 0;
    }

    absX = __builtin_abs(stickX);
    absY = __builtin_abs(stickY);
    if (absY < absX) {
        if (absX > absY * 2) {
            direction = (stickX < 0) ? 0x200 : 0x100;
        } else if (stickY > 0) {
            direction = (stickX < 0) ? 0xA00 : 0x900;
        } else {
            direction = (stickX < 0) ? 0x600 : 0x500;
        }
    } else if (absY > absX * 2) {
        direction = (stickY < 0) ? 0x400 : 0x800;
    } else if (stickY > 0) {
        direction = (stickX < 0) ? 0xA00 : 0x900;
    } else {
        direction = (stickX < 0) ? 0x600 : 0x500;
    }

    if (D_801129A0_filesel == direction && ++D_801146D4_filesel < 9) {
        return 0;
    }
    D_801129A0_filesel = direction;
    D_801146D4_filesel = 0;
    return direction;
}

s32 func_80111B14_filesel(s32 arg0) {
    s32 stickX;
    s32 stickY;
    s32 absX;
    s32 absY;

    stickX = D_800CBB6E_main[arg0];
    stickY = D_800D20A1_main[arg0];
    if (D_801129A0_filesel != 0) {
        if ((stickX == 0) & (stickY == 0)) {
            D_801129A0_filesel = 0;
        }
        return 0;
    }
    if ((stickX != 0) | (stickY != 0)) {
        absX = __builtin_abs(stickX);
        absY = __builtin_abs(stickY);
        if (absY < absX) {
            if (absX > absY * 2) {
                if (stickX < 0) {
                    D_801129A0_filesel = 0x200;
                } else {
                    D_801129A0_filesel = 0x100;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    D_801129A0_filesel = 0xA00;
                } else {
                    D_801129A0_filesel = 0x900;
                }
            } else {
                if (stickX < 0) {
                    D_801129A0_filesel = 0x600;
                } else {
                    D_801129A0_filesel = 0x500;
                }
            }
        } else {
            if (absY > absX * 2) {
                if (stickY < 0) {
                    D_801129A0_filesel = 0x400;
                } else {
                    D_801129A0_filesel = 0x800;
                }
            } else if (stickY > 0) {
                if (stickX < 0) {
                    D_801129A0_filesel = 0xA00;
                } else {
                    D_801129A0_filesel = 0x900;
                }
            } else {
                if (stickX < 0) {
                    D_801129A0_filesel = 0x600;
                } else {
                    D_801129A0_filesel = 0x500;
                }
            }
        }
    }
    return D_801129A0_filesel;
}

void func_80111C30_filesel(void) {
    s32 i;

    D_801142DC_filesel[2].unk_80 = 0;
    for (i = 0; i < 3; i++) {
        SLCurBoxNoSet(i);
        func_80050800_main();
        if (GwCommon.unk_00 == UNK_VALUE && D_800D09A9_main == i) {
            D_801142DC_filesel[2].unk_80 = i;
        }
        func_801122B0_filesel(i);
        func_80112184_filesel(i);
    }
}

void func_80111CBC_filesel(s32 fileIndex) {
    u8 first;
    u8 second;

    D_801142DC_filesel[fileIndex].unk_28 = 0;
    D_801142DC_filesel[fileIndex].unk_2C = 0;
    D_801142DC_filesel[fileIndex].unk_30 = 0;
    D_801142DC_filesel[fileIndex].unk_34 = 0;
    D_801142DC_filesel[fileIndex].unk_38 = 99;
    D_801142DC_filesel[fileIndex].unk_3C = 99;
    D_801142DC_filesel[fileIndex].unk_40 = 0;
    D_801142DC_filesel[fileIndex].unk_44 = 0;
    if (_CheckFlag(0x18)) {
        func_80112758_filesel();
        D_801142DC_filesel[fileIndex].unk_28 = GwStory.unk1;
        D_801142DC_filesel[fileIndex].unk_44 = GwStory.unk0;
        func_801126C0_filesel(GwStory.unk0, &first, &second);
        D_801142DC_filesel[fileIndex].unk_2C = second;
        D_801142DC_filesel[fileIndex].unk_30 = first;
        D_801142DC_filesel[fileIndex].unk_34 = GwSystem.current_turn < 4 ? GwSystem.current_game_length : 3;
        D_801142DC_filesel[fileIndex].unk_38 = GwSystem.current_turn >= 100 ? 99 : (s32)GwSystem.current_turn;
        D_801142DC_filesel[fileIndex].unk_3C = GwSystem.total_turns >= 100 ? 99 : (s32)GwSystem.total_turns;
        D_801142DC_filesel[fileIndex].unk_40 = GwStory.unk2;
    }
}

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

s32 func_80112508_filesel(s32 arg0, u8 *arg1) {
    s32 i;

    for (i = 0; i < 10; i += 2) {
        if ((u16)((D_801142DC_filesel[arg0].unk_01[i] << 8) | D_801142DC_filesel[arg0].unk_01[i + 1]) == 0) {
            break;
        }
        arg1[i] = D_801142DC_filesel[arg0].unk_01[i];
        arg1[i + 1] = D_801142DC_filesel[arg0].unk_01[i + 1];
    }

    arg1[i] = '\0';
    arg1[i + 1] = '\0';
    return i;
}

void func_80112584_filesel(s32 arg0) {
    SLCurBoxNoSet(arg0);
    func_80050800_main();
    bcopy(D_801142DC_filesel[arg0].unk_01, &GwCommon.flag[9], 10);
    D_800D09A9_main = arg0;
    func_80050064_main(1);
}

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

void func_80112684_filesel(void) {
    D_801146D8_filesel = 0;
    omAddObj(6, 0, 0, -1, func_80112630_filesel);
}

#ifdef NON_MATCHING
void func_801126C0_filesel(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 index;

    *arg1 = D_801129A4_filesel[0];
    *arg2 = D_801129A4_filesel[1];
    if (_CheckFlag(0x18)) {
        if (_CheckFlag(0x28)) {
            index = arg0 * 2;
        } else {
            index = (arg0 - 1) * 2;
        }
        *arg1 = D_801129A4_filesel[index];
        *arg2 = D_801129A4_filesel[index + 1];
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/filesel/516B10", func_801126C0_filesel);
#endif

void func_80112758_filesel(void) {
    func_80050ABC_main();
    if (GwStory.unk0 == 0 && _CheckFlag(0x18)) {
        _SetFlag(0x28);
    }
}
