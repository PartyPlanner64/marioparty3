#include "common.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "game/hmfdraw.h"
#include "game/hmfmath.h"
#include "game/pause.h"
#include "game/wipe.h"

typedef struct {
    /* 0x00 */ s32 dataNum;
    /* 0x04 */ s32 attr;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 motAttr;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
} SharkEntry; // Size 0x24

typedef struct {
    /* 0x00 */ s16 model;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ char unk06[2];
    /* 0x08 */ Vec cur;
    /* 0x14 */ Vec pos;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char unk26[0xA];
} SharkState; // Size 0x30

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec unk0C;
    /* 0x18 */ f32 dist;
} SharkPathPoint; // Size 0x1C

extern u16 D_800A11D0_main[];
extern u8 D_800D6A90_main;

u8 D_8010ACE0_swinging_with_sharks = 0;
u8 D_8010ACE1_swinging_with_sharks = 0;
f32 D_8010ACE4_swinging_with_sharks = 0.0f;
f32 D_8010ACE8_swinging_with_sharks = 0.0f;

SharkEntry D_8010ACEC_swinging_with_sharks[] = {
    { 0x00600001, 0x00000211, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600000, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600005, 0x00000231, 0, 0, { -700.0f, 600.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { -230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 230.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 460.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600002, 0x00000231, 0, 0, { 690.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600003, 0x00000229, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { -300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 0.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 300.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 600.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600004, 0x00000A51, 0, 0, { 900.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A01, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600006, 0x00000A51, 0, 0, { -700.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0049, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00220004, 0x00000A35, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A25, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF00A1, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x00600008, 0x00000A20, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0004, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF000D, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0010, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF000E, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0001, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0035, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0038, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0xFFFF0071, 0x00000231, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x0000007F, 0x00000A15, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0002, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A0154, 0x00000231, 0, 2, { 110.0f, 0.0f, -1170.0f }, { -25.0f, -28.0f, 0.0f } },
    { 0x000A0155, 0x00000231, 0, 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000B0030, 0x00000A20, 0, 0, { 110.0f, 0.0f, -1170.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A00EE, 0x00000231, 0, 2, { 110.0f, 60.0f, -1170.0f }, { 0.0f, -28.0f, 0.0f } },
    { 0x000A00F6, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { 0x000A00FC, 0x00000A35, 0, 0, { 0.0f, 500.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { -1, 0, 0, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};

u16 D_8010B418_swinging_with_sharks[] = { 76, 51, 25, 12 };
u8 D_8010B420_swinging_with_sharks[] = { 2, 3, 7, 4, 5, 6, 8, 9 };
s16 D_8010B428_swinging_with_sharks = 0;
s16 D_8010B42A_swinging_with_sharks = 0;
s16 D_8010B42C_swinging_with_sharks = -1;

s32 D_8010B430_swinging_with_sharks[] = {
    0x0021002D,
    0x0021002E,
    0x0021002F,
    0x00210030,
    0x00210031,
    0x00210032,
    0x00210033,
    0x00210034,
    0x00210035,
    0x00210036,
    0x00210037,
    0x00210038,
    0x00210039,
    0x0021003A,
    0x0021003B,
    0x0021003C,
    0x0021003D,
    0x0021003E,
    0x0021003F,
    0x00210040,
};

s16 D_8010B480_swinging_with_sharks = 0;
f32 D_8010B484_swinging_with_sharks = 0.017453292f;

SharkPathPoint D_8010B488_swinging_with_sharks[] = {
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -720.0f, -75.0f, -1230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -1330.0f, -75.0f, -750.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 40.0f, -50.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 910.0f, -75.0f, 20.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 1240.0f, -75.0f, -420.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 670.0f, -75.0f, -880.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

SharkPathPoint D_8010B5D8_swinging_with_sharks[] = {
    { { -750.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -750.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -740.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 40.0f, -50.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 910.0f, -75.0f, 20.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 1240.0f, -75.0f, -420.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 670.0f, -75.0f, -880.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 110.0f, -75.0f, -790.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -720.0f, -75.0f, -1230.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -1330.0f, -75.0f, -750.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -790.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { -780.0f, -75.0f, 50.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f },
};

SharkPathPoint *D_8010B760_swinging_with_sharks[2] = { D_8010B488_swinging_with_sharks, D_8010B5D8_swinging_with_sharks };
s16 D_8010B768_swinging_with_sharks = 0;
s16 D_8010B76A_swinging_with_sharks = 0;
s16 D_8010B76C_swinging_with_sharks = 0;

HuMtx4F D_8010B860_swinging_with_sharks BSS;
HuMtx4F D_8010B8A0_swinging_with_sharks BSS;
s16 D_8010B8E0_swinging_with_sharks[50] BSS; // model ids, indexed like D_8010ACEC
u8 D_8010B944_swinging_with_sharks[4] BSS; /* Unreferenced. */
s16 D_8010B948_swinging_with_sharks[50] BSS; // motion ids, indexed like D_8010ACEC
Vec D_8010B9AC_swinging_with_sharks BSS;
Vec D_8010B9B8_swinging_with_sharks BSS;
Vec D_8010B9C4_swinging_with_sharks BSS;
f32 D_8010B9D0_swinging_with_sharks BSS;
f32 D_8010B9D4_swinging_with_sharks BSS;
s16 D_8010B9D8_swinging_with_sharks BSS;
s16 D_8010B9DA_swinging_with_sharks BSS;
s16 D_8010B9DC_swinging_with_sharks BSS;
s16 D_8010B9DE_swinging_with_sharks BSS;
s16 D_8010B9E0_swinging_with_sharks BSS;
s16 D_8010B9E2_swinging_with_sharks BSS;
s16 D_8010B9E4_swinging_with_sharks BSS;
s16 D_8010B9E6_swinging_with_sharks BSS;
s16 D_8010B9E8_swinging_with_sharks BSS;
s16 D_8010B9EA_swinging_with_sharks BSS;
s16 D_8010B9EC_swinging_with_sharks BSS;
s16 D_8010B9EE_swinging_with_sharks BSS;
SharkState D_8010B9F0_swinging_with_sharks[5] BSS;
s16 D_8010BAE0_swinging_with_sharks BSS;
s16 D_8010BAE2_swinging_with_sharks BSS;
s16 D_8010BAE4_swinging_with_sharks BSS;
s16 D_8010BAE6_swinging_with_sharks BSS;
f32 D_8010BAE8_swinging_with_sharks BSS;
s16 D_8010BAEC_swinging_with_sharks BSS;
s16 D_8010BAEE_swinging_with_sharks BSS;
s16 D_8010BAF0_swinging_with_sharks[4] BSS;
s16 D_8010BAF8_swinging_with_sharks[20] BSS;
s16 D_8010BB20_swinging_with_sharks[20] BSS;
s16 D_8010BB48_swinging_with_sharks BSS;
s16 D_8010BB4A_swinging_with_sharks BSS; /* Unreferenced. */
u8 D_8010BB4C_swinging_with_sharks[4] BSS; /* Unreferenced. */
s16 D_8010BB50_swinging_with_sharks BSS;
Vec D_8010BB54_swinging_with_sharks BSS;
Vec D_8010BB60_swinging_with_sharks BSS;
Vec D_8010BB6C_swinging_with_sharks BSS;
Vec D_8010BB78_swinging_with_sharks BSS;
Vec D_8010BB84_swinging_with_sharks BSS;
Vec D_8010BB90_swinging_with_sharks BSS;
f32 D_8010BB9C_swinging_with_sharks BSS;
f32 D_8010BBA0_swinging_with_sharks BSS;
f32 D_8010BBA4_swinging_with_sharks BSS;
Vec D_8010BBA8_swinging_with_sharks BSS;
f32 D_8010BBB4_swinging_with_sharks BSS;

const s16 D_8010B770_swinging_with_sharks[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000
};

void func_80105FE4_swinging_with_sharks(omObjData *object);
void func_80106334_swinging_with_sharks(void);
void func_80106398_swinging_with_sharks(omObjData *object);
void func_80106870_swinging_with_sharks(omObjData *object);
void func_80106D44_swinging_with_sharks(omObjData *object);
void func_80107044_swinging_with_sharks(omObjData *object);
void func_801071A8_swinging_with_sharks(omObjData *object);
void func_801073F0_swinging_with_sharks(omObjData *object);
void func_80107384_swinging_with_sharks(void);
void func_80107628_swinging_with_sharks(omObjData *object);
void func_801076DC_swinging_with_sharks(omObjData *object);
void func_801077C4_swinging_with_sharks(void);
void func_80107954_swinging_with_sharks(omObjData *object);
void func_80108474_swinging_with_sharks(omObjData *object);
void func_801085F4_swinging_with_sharks(omObjData *object);
void func_801089A4_swinging_with_sharks(omObjData *object);
void func_801096AC_swinging_with_sharks(void);
void func_80108B24_swinging_with_sharks(void);
void func_801088F0_swinging_with_sharks(f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ, f32 zoom,
                                        s16 time);
void func_80108B4C_swinging_with_sharks(omObjData *object);
void func_80108C08_swinging_with_sharks(f32 arg0);
void func_80108DB0_swinging_with_sharks(Vec *pos);
void func_80108E50_swinging_with_sharks(HuMtx4F mtx, f32 angle);
void func_80108F20_swinging_with_sharks(s16 model, Vec *pos, HuMtx4F mtx);
void func_8010979C_swinging_with_sharks(SharkEntry *entries);
void func_801098C0_swinging_with_sharks(omObjData *object);
void func_80109924_swinging_with_sharks(omObjData *object);
void func_80109950_swinging_with_sharks(void);
f32 func_80109B04_swinging_with_sharks(SharkPathPoint *points, f32 speed);
void func_80109C90_swinging_with_sharks(SharkPathPoint *points, s16 model, f32 total);
void func_8010A0C0_swinging_with_sharks(void);
void func_8010A260_swinging_with_sharks(void);
void func_8010A41C_swinging_with_sharks(void);
void func_8010A4DC_swinging_with_sharks(void);
void func_8010AA68_swinging_with_sharks(void);
void func_8010AAA0_swinging_with_sharks(void);

void func_801059A0_swinging_with_sharks(void) {
    s32 index;
    s32 i;

    omInitObjMan(20, 10);
    func_8004A208_main();
    func_800142A0_main(20);
    Hu3DBGColorSet(0, 0xFF, 0);
    D_800CD280_main = 1;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CRot.x = 334.0f;
    CRot.y = D_8010BBA8_swinging_with_sharks.z = 0.0f;
    CZoom = 2750.0f;
    Center.x = -698.0f;
    Center.y = 363.0f;
    Center.z = -112.9f;
    D_8010BBB4_swinging_with_sharks = 20.0f;
    D_8010BBA8_swinging_with_sharks = CRot;
    D_8010BB90_swinging_with_sharks = D_8010BBA8_swinging_with_sharks;
    D_8010BB9C_swinging_with_sharks = CZoom;
    D_8010BB78_swinging_with_sharks = Center;
    Hu3DCameraPerspectiveSet(0, D_8010BBB4_swinging_with_sharks, 500.0f, 8000.0f);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(0, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(0, 92.0f, 79.0f, 22.0f);
    Hu3DGLightStatSet(0, 1, 1);
    Hu3DGLightColorSet(2, 100, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(10000, 0, 0, -1, func_801098C0_swinging_with_sharks);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010B9E0_swinging_with_sharks = 0;
    D_8010B9E2_swinging_with_sharks = 0;
    omAddObj(1000, 0, 0, -1, func_80105FE4_swinging_with_sharks);
    omAddObj(1000, 0, 0, -1, func_80106398_swinging_with_sharks);
    omAddObj(900, 0, 0, -1, func_801073F0_swinging_with_sharks);
    omAddObj(900, 0, 0, -1, func_80107954_swinging_with_sharks);
    omSetStatBit(omAddObj(900, 0, 0, -1, func_80108B4C_swinging_with_sharks), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddObj(900, 0, 0, -1, func_801089A4_swinging_with_sharks);
    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    D_8010B9D8_swinging_with_sharks = i;
    D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].stat & 1;
    GwPlayer[D_8010B9D8_swinging_with_sharks].bonusCoin = -1;
    D_8010B9DC_swinging_with_sharks = GwPlayer[i].chr;
    D_8010B9DA_swinging_with_sharks = GwPlayer[i].pad;
    func_8010979C_swinging_with_sharks(D_8010ACEC_swinging_with_sharks);
    if (D_8010B9E8_swinging_with_sharks != 0) {
        D_8010B9E8_swinging_with_sharks = GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty + 1;
        D_8010B9EA_swinging_with_sharks =
            rand8() > D_8010B418_swinging_with_sharks[GwPlayer[D_8010B9D8_swinging_with_sharks].cpu_difficulty];
        D_8010B9EC_swinging_with_sharks = (u8)(rand8() & 0x1F) + 15;
        if (D_8010B9EA_swinging_with_sharks != 0) {
            index = (rand8() * 5) >> 8;
            D_8010B9EE_swinging_with_sharks =
                (Hu3DData[D_8010B8E0_swinging_with_sharks[index + 3]].pos.x + 70.0f) / 1000.0f * 70.0f + 10.0f;
        }
    }
    func_80107384_swinging_with_sharks();
    func_801077C4_swinging_with_sharks();
    func_80108B24_swinging_with_sharks();
    func_8010AA68_swinging_with_sharks();
    func_80106334_swinging_with_sharks();
    D_8010ACE4_swinging_with_sharks = 0;
    D_8010B9D0_swinging_with_sharks = 80.0f;
    D_8010B9DE_swinging_with_sharks = -1;
    func_80108C08_swinging_with_sharks(0.0f);
    func_80108DB0_swinging_with_sharks(&D_8010B9B8_swinging_with_sharks);
    D_8010B9E4_swinging_with_sharks = 0;
    func_8001FA68_main(D_8010B8E0_swinging_with_sharks[31]);
    func_8001C514_main(D_8010B8E0_swinging_with_sharks[31]);
    func_80045010_main(D_8010B770_swinging_with_sharks, 1);
    func_8010A41C_swinging_with_sharks();
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    omAddPrcObj(func_80109950_swinging_with_sharks, 0x3F00, 0x2000, 0);
    HuAudSeqPlay(0x44);
    WipeCreateIn(0xFF, 0x10);
}

void func_80105FE4_swinging_with_sharks(omObjData *object) {
    switch (D_8010B9E0_swinging_with_sharks) {
        case 0:
            if (WipeStatGet() != 0) {
                break;
            }
            if (D_8010B9E4_swinging_with_sharks == 0) {
                D_8010B9E6_swinging_with_sharks = HuAudFXPlay(0x4ED);
            }
            if (++D_8010B9E4_swinging_with_sharks == 120) {
                D_8010BAE0_swinging_with_sharks = GMesCreate(8);
                func_801088F0_swinging_with_sharks(334.0f, 0.0f, 0.0f, 54.0f, 435.0f, -148.0f, 4340.0f, 30);
            }
            if (D_8010B9E4_swinging_with_sharks > 120 && GMesStatGet() == 0) {
                GMesCreate(0x1A, 10, 160, 120);
                D_8010B9E2_swinging_with_sharks = 329;
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010B9E0_swinging_with_sharks = 1;
            }
            break;
        case 1:
            if (D_8010B9E2_swinging_with_sharks > 0) {
                D_8010B9E2_swinging_with_sharks--;
                func_8003F578_main(D_8010B9E2_swinging_with_sharks / 30);
                if (D_8010B9E2_swinging_with_sharks == 0) {
                    func_8003F5C0_main();
                    D_8010B9E4_swinging_with_sharks = 0;
                }
            }
            break;
        case 3:
            if (D_8010B9E4_swinging_with_sharks == 0) {
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
                D_8010B9E4_swinging_with_sharks++;
                D_8010BAE2_swinging_with_sharks = 0;
            }
            if (++D_8010BAE2_swinging_with_sharks == 30) {
                func_8004AEF0_main(D_8010B9E6_swinging_with_sharks, 30);
            }
            if (GMesStatGet() == 0) {
                D_8010B9E4_swinging_with_sharks++;
                if (D_8010B9DE_swinging_with_sharks == -1) {
                    if (D_8010B9E4_swinging_with_sharks >= 16) {
                        GMesCreate(0x1D);
                        D_8010B9E4_swinging_with_sharks = 0;
                        D_8010B9E0_swinging_with_sharks = 4;
                        HuAudSeqPlay(0x6B);
                    }
                } else if (D_8010B9E4_swinging_with_sharks >= 16) {
                    GMesCreate(0x24);
                    D_8010B9E4_swinging_with_sharks = 0;
                    D_8010B9E0_swinging_with_sharks = 4;
                    HuAudSeqPlay(0x68);
                }
            }
            break;
        case 4:
            if (++D_8010B9E4_swinging_with_sharks >= 136) {
                D_8010B9E4_swinging_with_sharks = 0;
                D_8010ACE1_swinging_with_sharks = 1;
                D_8010B9E0_swinging_with_sharks = 5;
            }
            break;
        case 5:
            break;
    }
    func_8010A0C0_swinging_with_sharks();
    func_8010A260_swinging_with_sharks();
    func_8010A4DC_swinging_with_sharks();
    func_8010AAA0_swinging_with_sharks();
}

void func_80106334_swinging_with_sharks(void) {
    Hu3DMotionSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[41]);
    func_8001C814_main(D_8010B8E0_swinging_with_sharks[32], 1, 1);
    Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], 0.0f);
    func_8001FA68_main(D_8010B8E0_swinging_with_sharks[33]);
    func_8001C514_main(D_8010B8E0_swinging_with_sharks[33]);
}

void func_80106398_swinging_with_sharks(omObjData *object) {
    Vec pos;
    s32 jump = FALSE;
    f32 y;
    f32 velY;
    s16 frames;

    func_80108DB0_swinging_with_sharks(&pos);
    Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], pos.x, pos.y, pos.z);
    Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f, D_8010ACE4_swinging_with_sharks);
    if (D_8010ACE8_swinging_with_sharks < 180.0f) {
        Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], D_8010ACE8_swinging_with_sharks / 12.0f);
    } else {
        Hu3DMotionTimeSet(D_8010B8E0_swinging_with_sharks[32], (360.0f - D_8010ACE8_swinging_with_sharks) / 12.0f);
    }
    if (D_8010B9E0_swinging_with_sharks > 0) {
        if (D_8010B9E8_swinging_with_sharks != 0) {
            if (D_8010B9EC_swinging_with_sharks <= 0) {
                if (D_8010B9EA_swinging_with_sharks != 0) {
                    if (D_8010B9EE_swinging_with_sharks <= D_8010ACE4_swinging_with_sharks &&
                        D_8010ACE8_swinging_with_sharks < 90.0f) {
                        jump = TRUE;
                    }
                } else if ((150.0f < D_8010ACE8_swinging_with_sharks && D_8010ACE8_swinging_with_sharks < 180.0f) ||
                           345.0f < D_8010ACE8_swinging_with_sharks) {
                    jump = TRUE;
                }
            } else {
                D_8010B9EC_swinging_with_sharks--;
            }
        } else {
            jump = D_800D5558_main[D_8010B9DA_swinging_with_sharks] & 0x8000;
        }
        if ((D_8010B9E2_swinging_with_sharks != 0 && jump) ||
            (D_8010B9E2_swinging_with_sharks == 0 &&
             ((150.0f < D_8010ACE8_swinging_with_sharks && D_8010ACE8_swinging_with_sharks < 180.0f) ||
              345.0f < D_8010ACE8_swinging_with_sharks))) {
            HuAudFXPlay(0x4E9);
            if (D_8010B9E2_swinging_with_sharks != 0) {
                func_8003F5C0_main();
            }
            velY = pos.y - D_8010B9B8_swinging_with_sharks.y + 10.0f;
            y = pos.y;
            for (frames = 0;; frames++) {
                y += velY;
                velY -= 4.0f;
                if (y <= 0.0f) {
                    break;
                }
            }
            D_8010B9E0_swinging_with_sharks = 2;
            D_8010B9C4_swinging_with_sharks = pos;
            if (10.0f < D_8010ACE4_swinging_with_sharks && D_8010ACE4_swinging_with_sharks <= 80.0f &&
                D_8010ACE8_swinging_with_sharks <= 90.0f) {
                D_8010B9AC_swinging_with_sharks.x =
                    ((D_8010ACE4_swinging_with_sharks - 10.0f) * 14.285714f - 170.0f - pos.x) / frames;
            } else {
                D_8010B9AC_swinging_with_sharks.x = pos.x - D_8010B9B8_swinging_with_sharks.x;
            }
            D_8010B9AC_swinging_with_sharks.y = pos.y - D_8010B9B8_swinging_with_sharks.y;
            D_8010B9AC_swinging_with_sharks.z = 0.0f;
            D_8010B9AC_swinging_with_sharks.y += 10.0f;
            D_8010B9D0_swinging_with_sharks *= 1.1f;
            D_8010B9D4_swinging_with_sharks = D_8010ACE4_swinging_with_sharks;
            object->work[0] = 0;
            Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[34], 0, 4, 0);
            object->func = func_80106870_swinging_with_sharks;
        }
    }
    D_8010B9B8_swinging_with_sharks = pos;
}

void func_80106870_swinging_with_sharks(omObjData *object) {
    f32 x;
    s16 i;

    D_8010B9C4_swinging_with_sharks.x += D_8010B9AC_swinging_with_sharks.x;
    D_8010B9C4_swinging_with_sharks.y += D_8010B9AC_swinging_with_sharks.y;
    D_8010B9C4_swinging_with_sharks.z += D_8010B9AC_swinging_with_sharks.z;
    D_8010B9AC_swinging_with_sharks.y -= 4.0f;
    if (object->work[0] < 6) {
        Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f,
                        cosdf(object->work[0] * 18.0f) * D_8010B9D4_swinging_with_sharks);
        object->work[0]++;
    }
    if (D_8010B9C4_swinging_with_sharks.y <= 0.0f) {
        CharFXPlay(0x70, D_8010B9DC_swinging_with_sharks);
        omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
        D_8010B9E0_swinging_with_sharks = 3;
        D_8010B9D4_swinging_with_sharks = 0.0f;
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[35], 0, 8, 2);
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[47], D_8010B948_swinging_with_sharks[48], 0, 4, 2);
        Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 90.0f, 0.0f);
        object->work[0] = 0;
        func_8001C258_main(D_8010B8E0_swinging_with_sharks[29], 4, 0);
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[29], D_8010B9C4_swinging_with_sharks.x, 0.0f,
                        D_8010B9C4_swinging_with_sharks.z);
        Hu3DMotionSpeedSet(D_8010B8E0_swinging_with_sharks[29], 0.5f);
        Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[29], 3.0f, 3.0f, 3.0f);
        func_8001C258_main(D_8010B8E0_swinging_with_sharks[30], 4, 0);
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[30], D_8010B9C4_swinging_with_sharks.x, -30.0f,
                        D_8010B9C4_swinging_with_sharks.z + 50.0f);
        Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[30], 2.0f, 2.0f, 2.0f);
        HuAudFXPlay(0x4EF);
        object->func = func_80106D44_swinging_with_sharks;
    } else if (D_8010B9C4_swinging_with_sharks.y < 90.0f) {
        for (i = 0; i < 5; i++) {
            x = Hu3DData[D_8010B8E0_swinging_with_sharks[i + 3]].pos.x;
            if (x - 80.0f < D_8010B9C4_swinging_with_sharks.x && D_8010B9C4_swinging_with_sharks.x < x + 80.0f) {
                HuAudFXPlay(0x4EC);
                omVibrate(D_8010B9D8_swinging_with_sharks, 10, 0, 10);
                D_8010B9E0_swinging_with_sharks = 3;
                D_8010B9D4_swinging_with_sharks = 0.0f;
                if (D_8010B9C4_swinging_with_sharks.x < x - 40.0f) {
                    Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[36], 0, 8, 0);
                } else if (x + 40.0f < D_8010B9C4_swinging_with_sharks.x || 35.0f < D_8010B9AC_swinging_with_sharks.x) {
                    Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[32], D_8010B948_swinging_with_sharks[37], 0, 4, 0);
                } else {
                    func_8001C814_main(D_8010B8E0_swinging_with_sharks[32], 4, 4);
                }
                Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[32], 0.0f, 100.0f, 0.0f);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x, 50.0f,
                                D_8010B9C4_swinging_with_sharks.z);
                D_8010B9DE_swinging_with_sharks = i;
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[42], 4, 0);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[42], D_8010B9C4_swinging_with_sharks.x, 50.0f,
                                D_8010B9C4_swinging_with_sharks.z + 30.0f);
                HuAudFXPlay(0x4EF);
                object->func = func_80107044_swinging_with_sharks;
                break;
            }
        }
    }
    Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x,
                    D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
}

void func_80106D44_swinging_with_sharks(omObjData *object) {
    f32 scale;
    s16 model;

    if (object->work[0] == 8) {
        HuAudFXPlay(D_8010B9DC_swinging_with_sharks + 0x287);
    }
    if (object->work[0] >= 9) {
        model = D_8010B8E0_swinging_with_sharks[31];
        func_8001C258_main(model, 4, 0);
        Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, 0.0f, D_8010B9C4_swinging_with_sharks.z);
        if (D_8010B428_swinging_with_sharks > 90) {
            if (Hu3DData[D_8010B8E0_swinging_with_sharks[32]].motTime != 0.0f) {
                return;
            }
            D_8010B428_swinging_with_sharks = 0;
        }
        scale = sindf((s16)(D_8010B428_swinging_with_sharks % 90)) + 0.5f;
        Hu3DModelScaleSet(model, scale, scale, scale);
        func_8001F9E4_main(model, 255.0f - D_8010B428_swinging_with_sharks * 2.8333333f);
        D_8010B428_swinging_with_sharks += 3;
    } else {
        D_8010B9C4_swinging_with_sharks.y = sindf(object->work[0] * 18.0f) * D_8010B9AC_swinging_with_sharks.y;
        object->work[0]++;
        Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[32], D_8010B9C4_swinging_with_sharks.x,
                        D_8010B9C4_swinging_with_sharks.y, D_8010B9C4_swinging_with_sharks.z);
        Hu3DData[D_8010B8E0_swinging_with_sharks[32]].rot.y = 90.0f - object->work[0] * 11.25f;
    }
}

void func_80107044_swinging_with_sharks(omObjData *object) {
    HmfModel *shark;
    s16 model = D_8010B8E0_swinging_with_sharks[32];

    if (Hu3DData[model].motId == D_8010B948_swinging_with_sharks[37] &&
        Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[32], 0, 16, 2);
    }
    shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, shark->pos.y + 80.0f, D_8010B9C4_swinging_with_sharks.z);
    if (++object->work[0] > 20) {
        object->work[0] = 0;
        Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[47], D_8010B948_swinging_with_sharks[49], 0, 4, 0);
        object->func = func_801071A8_swinging_with_sharks;
    }
}

void func_801071A8_swinging_with_sharks(omObjData *object) {
    HmfModel *shark;
    s16 model = D_8010B8E0_swinging_with_sharks[32];

    shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    D_8010B9C4_swinging_with_sharks.x += (shark->pos.x - D_8010B9C4_swinging_with_sharks.x) / 2.0f;
    Hu3DModelPosSet(model, D_8010B9C4_swinging_with_sharks.x, shark->pos.y + 80.0f, D_8010B9C4_swinging_with_sharks.z);
    if (object->work[0] == 0) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[38], 0, 4, 2);
    }
    if (++object->work[0] == 75) {
        Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[39], 0, 4, 0);
        func_80045ED0_main((D_8010B420_swinging_with_sharks[D_8010B9DC_swinging_with_sharks] << 16) | 0x35);
    }
    if (object->work[0] < 9) {
        Hu3DData[model].rot.y = 90.0f - object->work[0] * 11.25f;
        if (object->work[0] == 8) {
            Hu3DMotionShiftSet(model, D_8010B948_swinging_with_sharks[32], 0, 8, 2);
        }
    }
}

void func_80107384_swinging_with_sharks(void) {
    HmfSkeletonNode *node;

    node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "rope");
    func_8002367C_main(D_8010B860_swinging_with_sharks, node->unk4C);
    node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "step");
    func_8002367C_main(D_8010B8A0_swinging_with_sharks, node->unk4C);
    D_8010ACE8_swinging_with_sharks = 0.0f;
}

void func_801073F0_swinging_with_sharks(omObjData *object) {
    switch (D_8010B42A_swinging_with_sharks) {
        case 0:
            if (D_8010ACE8_swinging_with_sharks == 0.0f) {
                D_8010B42C_swinging_with_sharks = HuAudFXPlay(0x4EA);
            }
            D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            if (D_8010ACE8_swinging_with_sharks > 360.0f) {
                D_8010ACE8_swinging_with_sharks -= 360.0f;
                D_8010B42A_swinging_with_sharks++;
            }
            break;
        case 1:
            D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * 180.0f;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            if (D_8010ACE8_swinging_with_sharks > 90.0f) {
                D_8010B42A_swinging_with_sharks++;
                D_8010B9D0_swinging_with_sharks = 180.0f;
            }
            break;
        case 2:
            D_8010ACE4_swinging_with_sharks = -sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
            D_8010ACE8_swinging_with_sharks += 5.0f;
            D_8010B9D0_swinging_with_sharks -= 6.0f;
            if (D_8010ACE8_swinging_with_sharks > 180.0f) {
                D_8010B9D0_swinging_with_sharks = 80.0f;
                D_8010ACE8_swinging_with_sharks += 180.0f;
                object->func = func_80107628_swinging_with_sharks;
            }
            break;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
}

void func_80107628_swinging_with_sharks(omObjData *object) {
    D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
    D_8010ACE8_swinging_with_sharks += 5.0f;
    if (D_8010ACE8_swinging_with_sharks > 360.0f) {
        D_8010ACE8_swinging_with_sharks -= 360.0f;
    }
    func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    if (D_8010B9E0_swinging_with_sharks == 2) {
        object->func = func_801076DC_swinging_with_sharks;
    }
}

void func_801076DC_swinging_with_sharks(omObjData *object) {
    if (D_8010B9D0_swinging_with_sharks > 0.0f) {
        D_8010ACE4_swinging_with_sharks = sindf(D_8010ACE8_swinging_with_sharks) * D_8010B9D0_swinging_with_sharks;
        D_8010ACE8_swinging_with_sharks += 5.0f;
        if (D_8010ACE8_swinging_with_sharks > 360.0f) {
            D_8010ACE8_swinging_with_sharks -= 360.0f;
        }
        D_8010B9D0_swinging_with_sharks -= 0.5f;
        if (D_8010B9D0_swinging_with_sharks <= 0.0f) {
            D_8010B9D0_swinging_with_sharks = 0.0f;
        }
        func_80108C08_swinging_with_sharks(D_8010ACE4_swinging_with_sharks);
    }
}

void func_801077C4_swinging_with_sharks(void) {
    SharkState *shark;
    s16 i;

    for (i = 0; i < 5; i++) {
        shark = &D_8010B9F0_swinging_with_sharks[i];
        shark->model = D_8010B8E0_swinging_with_sharks[i + 3];
        Hu3DModelPosGet(shark->model, &shark->pos);
        shark->unk20 = rand8() & 0xF8;
        shark->unk02 = 0;
        shark->unk04 = 30;
        Hu3DAnimBankSet(Hu3DAnimRead(Hu3DData[D_8010B8E0_swinging_with_sharks[i + 8]].hmf, 0x21002C, "m259_30_000_DEF"),
                        D_800A11D0_main[i]);
        Hu3DModelRemakeStatic(D_8010B8E0_swinging_with_sharks[i + 8]);
        func_8001C514_main(D_8010B8E0_swinging_with_sharks[i + 8]);
        shark->unk24 = rand8() & 0x3F;
        func_8001FA68_main(D_8010B8E0_swinging_with_sharks[i + 18]);
        func_8001C514_main(D_8010B8E0_swinging_with_sharks[i + 18]);
    }
    D_8010BAE6_swinging_with_sharks = func_8000CED8_main(0xB0004, 0x2A9);
    func_800138EC_main(D_8010BAE6_swinging_with_sharks, 1, 0);
}

void func_80107954_swinging_with_sharks(omObjData *object) {
    SharkState *shark;
    HmfModel *model;
    s16 i;
    s16 splash;
    f32 scale;

    if (D_8010B9DE_swinging_with_sharks != -1) {
        i = D_8010B9DE_swinging_with_sharks;
        shark = &D_8010B9F0_swinging_with_sharks[i];
        model = &Hu3DData[shark->model];
        if (shark->unk02 < 50) {
            shark->cur.y = sindf(shark->unk02 * 30) * shark->unk04 + shark->pos.y - 50.0f;
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            Hu3DData[shark->model].rot.z = 0.0f;
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 8], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DData[D_8010B8E0_swinging_with_sharks[i + 8]].rot.z = 0.0f;
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 13], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DData[D_8010B8E0_swinging_with_sharks[i + 13]].rot.z = 0.0f;
            shark->unk04--;
            if (++shark->unk02 == 50) {
                shark->unk20 = 500.0f;
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[43], 4, 0);
                Hu3DModelRotSet(D_8010B8E0_swinging_with_sharks[43], CRot.x, CRot.y, CRot.z);
                Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[43], 4.0f, 4.0f, 4.0f);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[43], model->pos.x, model->pos.y + 300.0f,
                                model->pos.z);
            }
        } else {
            shark->cur.y = sindf(shark->unk20) * 5.0f + shark->pos.y - 50.0f;
            shark->unk20 += 10.0f;
            if (shark->unk20 > 1440.0f) {
                shark->unk20 -= 1440.0f;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            if (shark->unk02 > 60) {
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[i + 8], 4, 4);
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[i + 13], 4, 4);
            } else {
                shark->unk02++;
            }
            if (shark->unk02 == 60) {
                omAddObj(900, 0, 0, -1, func_80108474_swinging_with_sharks);
            }
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 8], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 13], model->pos.x, model->pos.y,
                            model->pos.z - ((i & 1) * 10 + 80));
        }
    }
    if (D_8010B9E0_swinging_with_sharks < 3) {
        for (i = 0; i < 5; i++) {
            if (i == D_8010B9DE_swinging_with_sharks) {
                continue;
            }
            shark = &D_8010B9F0_swinging_with_sharks[i];
            shark->cur.x = sindf(shark->unk20 / 4.0f) * 50.0f + shark->pos.x;
            shark->cur.y = sindf(shark->unk20) * 10.0f + shark->pos.y;
            shark->cur.z = shark->pos.z;
            shark->unk20 += 10.0f;
            if (shark->unk20 > 1440.0f) {
                shark->unk20 -= 1440.0f;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
            Hu3DData[shark->model].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 8], shark->cur.x, shark->cur.y,
                            shark->cur.z - ((i & 1) * 10 + 80));
            Hu3DData[D_8010B8E0_swinging_with_sharks[i + 8]].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
            Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 13], shark->cur.x, shark->cur.y,
                            shark->cur.z - ((i & 1) * 10 + 80));
            Hu3DData[D_8010B8E0_swinging_with_sharks[i + 13]].rot.z = sindf(shark->unk20 / 2.0f) * 5.0f;
        }
    } else {
        for (i = 0; i < 5; i++) {
            shark = &D_8010B9F0_swinging_with_sharks[i];
            if (i == D_8010B9DE_swinging_with_sharks || shark->cur.y < -1500.0f) {
                continue;
            }
            if (shark->cur.y > -80.0f) {
                shark->cur.y -= 4.0f;
                shark->unk20 = 0.0f;
                shark->unk04 = (u8)(rand8() & 0xF) - 8;
                Hu3DData[shark->model].rot.z = 0.0f;
                scale = shark->cur.y * 0.0125f + 1.0f;
                Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[i + 13], scale, scale, scale);
                Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[i + 8], scale, scale, scale);
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 13], shark->cur.x, 0.0f,
                                shark->cur.z - ((i & 1) * 10 + 80));
                Hu3DData[D_8010B8E0_swinging_with_sharks[i + 13]].rot.z = 0.0f;
                Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 8], shark->cur.x, shark->cur.y,
                                shark->cur.z - ((i & 1) * 10 + 80));
                Hu3DData[D_8010B8E0_swinging_with_sharks[i + 8]].rot.z = 0.0f;
                if (shark->cur.y <= -80.0f) {
                    func_8001C258_main(D_8010B8E0_swinging_with_sharks[i + 23], 4, 0);
                    Hu3DModelPosSet(D_8010B8E0_swinging_with_sharks[i + 23], shark->cur.x, 0.0f, shark->cur.z);
                    Hu3DMotionSpeedSet(D_8010B8E0_swinging_with_sharks[i + 23], 1.0f);
                    Hu3DModelScaleSet(D_8010B8E0_swinging_with_sharks[i + 23], 1.0f, 1.0f, 1.0f);
                }
            } else {
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[i + 8], 4, 4);
                func_8001C258_main(D_8010B8E0_swinging_with_sharks[i + 13], 4, 4);
                shark->cur.y -= 8.0f;
                shark->unk20 += shark->unk04 / 10.0f;
                Hu3DData[shark->model].rot.z = shark->unk20;
            }
            Hu3DModelPosSet(shark->model, shark->cur.x, shark->cur.y, shark->cur.z);
        }
    }
    for (i = 0; i < 5; i++) {
        shark = &D_8010B9F0_swinging_with_sharks[i];
        splash = D_8010B8E0_swinging_with_sharks[i + 18];
        if (shark->unk24 <= 90) {
            Hu3DModelPosSet(splash, shark->cur.x, 0.0f, shark->cur.z);
            scale = sindf((s16)(shark->unk24 % 90)) + 0.8f;
            Hu3DModelScaleSet(splash, scale, scale, scale);
            func_8001F9E4_main(splash, 255.0f - shark->unk24 * 2.8333333f);
            shark->unk24 += 2;
            if (shark->unk24 > 90) {
                if (shark->cur.y < -50.0f && D_8010B9DE_swinging_with_sharks != i) {
                    shark->unk24 = 90;
                } else {
                    shark->unk24 = 0;
                }
            }
        }
    }
}

void func_80108474_swinging_with_sharks(omObjData *object) {
    HmfModel *shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    s16 model;

    D_8010BAE4_swinging_with_sharks =
        SprModelRead(D_8010B430_swinging_with_sharks[D_800A11D0_main[D_8010B9DE_swinging_with_sharks]], 0xA4, 0x10);
    model = D_800CBB60_main[D_8010BAE4_swinging_with_sharks].modelId;
    Hu3DModelScaleSet(model, 5.0f, 5.0f, 5.0f);
    Hu3DModelPosSet(model, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    func_80014850_main(D_8010BAE4_swinging_with_sharks);
    object->work[0] = 0;
    object->work[1] = 0;
    func_800138EC_main(D_8010BAE6_swinging_with_sharks, 1, 1);
    func_8000CD00_main(D_8010BAE6_swinging_with_sharks, 8.0f, 20.0f, 10.0f);
    func_8000D018_main(D_8010BAE6_swinging_with_sharks, 150.0f);
    func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, shark->pos.x, 200.0f, shark->pos.z - 80.0f);
    HuAudFXPlay(0x4EE);
    object->func = func_801085F4_swinging_with_sharks;
}

void func_801085F4_swinging_with_sharks(omObjData *object) {
    HmfModel *shark = &Hu3DData[D_8010B8E0_swinging_with_sharks[D_8010B9DE_swinging_with_sharks + 3]];
    s16 model = D_800CBB60_main[D_8010BAE4_swinging_with_sharks].modelId;
    HmfModel *spr = &Hu3DData[model];

    switch (object->work[0]) {
        case 0:
            Hu3DModelPosSet(model, shark->pos.x, sindf(object->work[1] * 9.0f) * 200.0f + 200.0f, shark->pos.z - (80.0f - sindf(object->work[1] * 9.0f) * 80.0f));
            func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, spr->pos.x, spr->pos.y - 50.0f, spr->pos.z);
            if (++object->work[1] > 10) {
                GwPlayer[D_8010B9D8_swinging_with_sharks].bonusCoin = D_800A11D0_main[D_8010B9DE_swinging_with_sharks];
                object->work[0] = 1;
                object->work[1] = 0;
                func_801088F0_swinging_with_sharks(334.0f, 0.0f, 0.0f, shark->pos.x, 300.0f, shark->pos.z, 2500.0f, 20);
            }
            break;
        case 1:
            Hu3DData[model].pos.y = sindf(object->work[1]) * 20.0f + 400.0f;
            func_8000CFA4_main(D_8010BAE6_swinging_with_sharks, spr->pos.x, spr->pos.y - 50.0f, spr->pos.z);
            object->work[1] += 10;
            break;
    }
}

void func_801088F0_swinging_with_sharks(f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ, f32 zoom,
                                        s16 time) {
    D_8010BB84_swinging_with_sharks = CRot;
    D_8010BB6C_swinging_with_sharks = Center;
    D_8010BBA0_swinging_with_sharks = CZoom;
    D_8010BB54_swinging_with_sharks.x = rotX;
    D_8010BB54_swinging_with_sharks.y = rotY;
    D_8010BB54_swinging_with_sharks.z = rotZ;
    D_8010BB60_swinging_with_sharks.x = centerX;
    D_8010BB60_swinging_with_sharks.y = centerY;
    D_8010BB60_swinging_with_sharks.z = centerZ;
    D_8010BBA4_swinging_with_sharks = zoom;
    D_8010B480_swinging_with_sharks = D_8010BB50_swinging_with_sharks = time;
}

void func_801089A4_swinging_with_sharks(omObjData *object) {
    f32 t;

    if (D_8010B480_swinging_with_sharks != 0) {
        D_8010B480_swinging_with_sharks--;
        t = sindf((1.0f - (f32)D_8010B480_swinging_with_sharks / D_8010BB50_swinging_with_sharks) * 90.0f);
        CRot.x = (-D_8010BB84_swinging_with_sharks.x + D_8010BB54_swinging_with_sharks.x) * t +
                 D_8010BB84_swinging_with_sharks.x;
        CRot.y = (-D_8010BB84_swinging_with_sharks.y + D_8010BB54_swinging_with_sharks.y) * t +
                 D_8010BB84_swinging_with_sharks.y;
        CRot.z = (-D_8010BB84_swinging_with_sharks.z + D_8010BB54_swinging_with_sharks.z) * t +
                 D_8010BB84_swinging_with_sharks.z;
        Center.x = (-D_8010BB6C_swinging_with_sharks.x + D_8010BB60_swinging_with_sharks.x) * t +
                   D_8010BB6C_swinging_with_sharks.x;
        Center.y = (-D_8010BB6C_swinging_with_sharks.y + D_8010BB60_swinging_with_sharks.y) * t +
                   D_8010BB6C_swinging_with_sharks.y;
        Center.z = (-D_8010BB6C_swinging_with_sharks.z + D_8010BB60_swinging_with_sharks.z) * t +
                   D_8010BB6C_swinging_with_sharks.z;
        CZoom = (-D_8010BBA0_swinging_with_sharks + D_8010BBA4_swinging_with_sharks) * t + D_8010BBA0_swinging_with_sharks;
    }
}

void func_80108B24_swinging_with_sharks(void) {
    func_8001C954_main(D_8010B8E0_swinging_with_sharks[0]);
    D_8010BAE8_swinging_with_sharks = 0;
}

void func_80108B4C_swinging_with_sharks(omObjData *object) {
    func_8001E888_main(D_8010B8E0_swinging_with_sharks[0], 0, -D_8010BAE8_swinging_with_sharks, 32, 32, "sea", 0);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010BAE8_swinging_with_sharks += 0.3f;
        if (D_8010BAE8_swinging_with_sharks > 32.0f) {
            D_8010BAE8_swinging_with_sharks = 0.0f;
        }
    }
}

void func_80108C08_swinging_with_sharks(f32 angle) {
    HmfSkeletonNode *rope;
    HmfSkeletonNode *step;
    s32 deg;
    f32 swing;

    if (D_8010B42C_swinging_with_sharks != -1) {
        deg = (s32)(angle + 360.0f) % 360;
        if (deg > 180) {
            deg = 360 - deg;
        }
        swing = deg;
        HuAudFXPitchSet(D_8010B42C_swinging_with_sharks, (s16)(swing * 6.6666665f));
        HuAudFXVolSet(D_8010B42C_swinging_with_sharks, 127.0f - swing * 0.35f);
    }
    rope = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "rope");
    func_8002367C_main(rope->unk4C, D_8010B860_swinging_with_sharks);
    func_80108E50_swinging_with_sharks(rope->unk4C, angle);
    step = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "step");
    func_8002367C_main(step->unk4C, rope->unk4C);
    mtxTransCat(step->unk4C, step->unk08.x, step->unk08.y, step->unk08.z);
}

void func_80108DB0_swinging_with_sharks(Vec *pos) {
    HmfSkeletonNode *node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "step");

    func_80108F20_swinging_with_sharks(D_8010B8E0_swinging_with_sharks[2], pos, node->unk4C);
}

void func_80108E00_swinging_with_sharks(Vec *pos) {
    HmfSkeletonNode *node = func_8001D33C_main(D_8010B8E0_swinging_with_sharks[2], "rope");

    func_80108F20_swinging_with_sharks(D_8010B8E0_swinging_with_sharks[2], pos, node->unk4C);
}

void func_80108E50_swinging_with_sharks(HuMtx4F mtx, f32 angle) {
    f32 row[3];
    f32 s;
    f32 c;
    s32 i;

    row[0] = angle * D_8010B484_swinging_with_sharks;
    s = sinf(row[0]);
    c = cosf(row[0]);
    for (i = 0; i < 3; i++) {
        row[i] = mtx[0][i];
    }
    for (i = 0; i < 3; i++) {
        mtx[0][i] = c * row[i] + s * mtx[1][i];
        mtx[1][i] = -row[i] * s + c * mtx[1][i];
    }
}

void func_80108F20_swinging_with_sharks(s16 model, Vec *pos, HuMtx4F mtx) {
    HmfModel *hmf = &Hu3DData[model];
    HuMtx4F local;
    HuMtx4F result;

    func_80088800_main(local, hmf->pos.x, hmf->pos.y, hmf->pos.z);
    mtxRotCat(local, hmf->rot.x, hmf->rot.y, hmf->rot.z);
    mtxScaleCat(local, hmf->scale.x, hmf->scale.y, hmf->scale.z);
    func_80018044_main(mtx, local, result);
    pos->x = result[0][0] + result[1][0] + result[2][0] + result[3][0];
    pos->y = result[0][1] + result[1][1] + result[2][1] + result[3][1];
    pos->z = result[0][2] + result[1][2] + result[2][2] + result[3][2];
}

void func_80109020_swinging_with_sharks(void) {
    char buf[256];
    f32 rotX;
    f32 rotY;
    f32 speed;
    f32 dirZ;
    f32 inv;

    if (D_800D5558_main[0] & 0x10) {
        D_8010ACE0_swinging_with_sharks ^= 1;
    }
    if (D_800CDA7C_main[0] & 0x1000) {
        func_801096AC_swinging_with_sharks();
    }
    if (D_800CDA7C_main[0] & 8) {
        CZoom = (D_800CDA7C_main[0] & 0x2000) ? CZoom + 30.0f : CZoom + 10.0f;
    }
    if ((D_800CDA7C_main[0] & 4) && CZoom - 10.0f != 0.0f) {
        CZoom = (D_800CDA7C_main[0] & 0x2000) ? CZoom - 30.0f : CZoom - 10.0f;
    }
    if (D_800CDA7C_main[0] & 2) {
        D_8010BBB4_swinging_with_sharks += 1.0f;
    }
    if (D_800CDA7C_main[0] & 1) {
        D_8010BBB4_swinging_with_sharks -= 1.0f;
    }
    Hu3DCameraPerspectiveSet(0, D_8010BBB4_swinging_with_sharks, 500.0f, 8000.0f);
    rotX = D_8010BB90_swinging_with_sharks.x;
    rotY = D_8010BB90_swinging_with_sharks.y;
    speed = (D_800CDA7C_main[0] & 0x2000) ? 5.0f : 2.0f;
    rotY += (-D_800CBB6E_main[0] / 30) * speed;
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    } else if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    D_8010BB90_swinging_with_sharks.y = rotY;
    rotX += (s8)(D_800D20A1_main[0] / 30) * speed;
    if (rotX >= 360.0f) {
        rotX -= 360.0f;
    } else if (rotX < 0.0f) {
        rotX += 360.0f;
    }
    D_8010BB90_swinging_with_sharks.x = rotX;
    CRot.x = (s16)rotX;
    CRot.y = (s16)D_8010BB90_swinging_with_sharks.y;
    speed = (D_800CDA7C_main[0] & 0x2000) ? 10.0f : 2.0f;
    if (D_800CDA7C_main[0] & 0x800) {
        Center.x += sindf(rotY) * sindf(rotX) * -speed;
        Center.y += cosdf(rotX) * -speed;
        Center.z += cosdf(rotY) * sindf(rotX) * -speed;
    } else if (D_800CDA7C_main[0] & 0x400) {
        Center.x += sindf(rotY) * sindf(rotX) * speed;
        Center.y += cosdf(rotX) * speed;
        Center.z += cosdf(rotY) * sindf(rotX) * speed;
    } else if (D_800CDA7C_main[0] & 0x200) {
        // rotX is reused here as the X component of the camera direction.
        rotX = gCameraList->pos.z - Center.z;
        dirZ = -(gCameraList->pos.x - Center.x);
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    } else if (D_800CDA7C_main[0] & 0x100) {
        rotX = -(gCameraList->pos.z - Center.z);
        dirZ = gCameraList->pos.x - Center.x;
        inv = 1.0f / HuSqrtf(rotX * rotX + dirZ * dirZ);
        Center.x += rotX * inv * speed;
        Center.y += 0.0f;
        Center.z += dirZ * inv * speed;
    }
    if (D_8010ACE0_swinging_with_sharks) {
        sprintf(buf, "CROT %4.1f,%4.1f,%4.1f", CRot.x, CRot.y, CRot.z);
        print8(32, 180, buf);
        sprintf(buf, "INT %4.1f,%4.1f,%4.1f", Center.x, Center.y, Center.z);
        print8(32, 190, buf);
        sprintf(buf, "CZOOM %4.1f  FOVY %4.1f", CZoom, D_8010BBB4_swinging_with_sharks);
        print8(32, 200, buf);
    }
}

void func_801096AC_swinging_with_sharks(void) {
    CRot = D_8010BBA8_swinging_with_sharks;
    D_8010BB90_swinging_with_sharks = CRot;
    CZoom = D_8010BB9C_swinging_with_sharks;
    Center = D_8010BB78_swinging_with_sharks;
}

void func_80109730_swinging_with_sharks(SharkEntry *arg0, s16 arg1, s16 modelId) {
    SharkEntry *entry = &arg0[arg1];
    Hu3DModelPosSet(modelId, entry->pos.x, entry->pos.y, entry->pos.z);
    Hu3DModelRotSet(modelId, entry->rot.x, entry->rot.y, entry->rot.z);
}

void func_8010979C_swinging_with_sharks(SharkEntry *entries) {
    SharkEntry *entry = entries;
    s16 i;
    s16 model;

    for (i = 0; entry->dataNum != -1; i++, entry++) {
        if ((entry->dataNum & 0xFFFF0000) == 0xFFFF0000) {
            entry->dataNum = func_80017BB8_main(D_8010B9DC_swinging_with_sharks, (s16)entry->dataNum);
        }
        D_8010B8E0_swinging_with_sharks[i] = func_8000B108_main(entry->dataNum, entry->attr | 0x288);
        model = D_8010B8E0_swinging_with_sharks[i];
        func_80109730_swinging_with_sharks(entries, i, model);
        D_8010B948_swinging_with_sharks[i] = Hu3DData[model].motId;
        if (D_8010B948_swinging_with_sharks[i] != -1) {
            func_8001C814_main(model, -1, entry->motAttr);
        }
    }
}

void func_801098C0_swinging_with_sharks(omObjData *object) {
    if (D_8010ACE1_swinging_with_sharks != 0 || D_800D530C_main != 0) {
        WipeCreateOut(0, 20);
        object->func = func_80109924_swinging_with_sharks;
        HuAudSeqFadeOut(60);
        func_8004AB0C_main(30);
    }
}

void func_80109924_swinging_with_sharks(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80109950_swinging_with_sharks(void) {
    s16 model;
    s16 n;
    s16 path;
    f32 total;

    if (D_8010B768_swinging_with_sharks == 0) {
        model = D_8010BAEC_swinging_with_sharks = func_8000B108_main(0xA0154, 0x299);
        D_8010BAEE_swinging_with_sharks = func_8000B13C_main(0xA0155);
    } else {
        model = Hu3DModelLink(D_8010BAEC_swinging_with_sharks);
    }
    func_8001C5B4_main(model, D_8010BAEE_swinging_with_sharks);
    n = D_8010B768_swinging_with_sharks++;
    D_8010BAF0_swinging_with_sharks[n] = model;
    path = n % 2;
    func_8001C814_main(model, 2, 2);
    Hu3DMotionTimeSet(model, n * 10);
    Hu3DModelPosSet(model, 0.0f, -100.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 90.0f, 0.0f);
    total = func_80109B04_swinging_with_sharks(D_8010B760_swinging_with_sharks[path], 20.0f);
    while (TRUE) {
        func_80109C90_swinging_with_sharks(D_8010B760_swinging_with_sharks[path], model, total);
        HuPrcVSleep();
    }
}

f32 func_80109B04_swinging_with_sharks(SharkPathPoint *points, f32 speed) {
    SharkPathPoint *prev;
    SharkPathPoint *point;
    f32 total;
    f32 dist;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 i;

    prev = NULL;
    total = 0.0f;
    for (i = 0, point = points; point->pos.x != 0.0f || point->pos.y != 0.0f || point->pos.z != 0.0f;
         i++, point = &points[i]) {
        if (i > 0) {
            dx = prev->pos.x - point->pos.x;
            dy = prev->pos.y - point->pos.y;
            dz = prev->pos.z - point->pos.z;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
            if (dist == 0.0f) {
                dist = speed * 10.0f;
            }
            total += dist / speed;
            point->dist = total;
        }
        prev = point;
    }
    return total;
}

void func_80109C90_swinging_with_sharks(SharkPathPoint *points, s16 model, f32 total) {
    f32 values[4];
    f32 times[4];
    Vec prevPos;
    f32 end;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;
    f32 delta;
    s16 sink;
    s16 i;
    s16 t;

    sink = 0;
    while (TRUE) {
        end = total - 10.0f;
        i = 1;
        for (t = 10; t < end; t++) {
            if (t > points[i + 1].dist) {
                i++;
            }
            Hu3DModelPosGet(model, &prevPos);
            times[0] = points[i - 1].dist;
            times[1] = points[i].dist;
            times[2] = points[i + 1].dist;
            times[3] = points[i + 2].dist;
            values[0] = points[i - 1].pos.x;
            values[1] = points[i].pos.x;
            values[2] = points[i + 1].pos.x;
            values[3] = points[i + 2].pos.x;
            x = InterpolateBMLine(values, times, t);
            values[0] = points[i - 1].pos.y;
            values[1] = points[i].pos.y;
            values[2] = points[i + 1].pos.y;
            values[3] = points[i + 2].pos.y;
            y = InterpolateBMLine(values, times, t);
            values[0] = points[i - 1].pos.z;
            values[1] = points[i].pos.z;
            values[2] = points[i + 1].pos.z;
            values[3] = points[i + 2].pos.z;
            z = InterpolateBMLine(values, times, t);
            Hu3DModelPosSet(model, x, y, z);
            x -= prevPos.x;
            z -= prevPos.z;
            if (z != 0.0f || x != 0.0f) {
                Hu3DData[model].rot.y = atan2df(x, z);
            }
            if (D_8010B9E0_swinging_with_sharks >= 3) {
                if (D_8010B9DE_swinging_with_sharks == -1) {
                    if (sink < 20) {
                        sink++;
                        y = Hu3DData[model].pos.y;
                        angle = sink * 4.5f;
                        delta = sindf(angle) * (-30.0f - y);
                        Hu3DData[model].pos.y = y + delta;
                        delta = sindf(angle) * -30.0f;
                        Hu3DData[model].rot.x = delta;
                    } else {
                        Hu3DData[model].pos.y = -30.0f;
                        Hu3DData[model].rot.x = -30.0f;
                    }
                } else {
                    Hu3DData[model].pos.y -= sink * 10;
                    sink++;
                }
            }
            HuPrcVSleep();
        }
    }
}

void func_8010A0C0_swinging_with_sharks(void) {
    s16 model = D_8010B8E0_swinging_with_sharks[47];
    HmfModel *target;
    HmfModel *self;
    HmfMotionNode *node;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 angle;

    if (Hu3DData[model].motId != D_8010B948_swinging_with_sharks[47]) {
        func_8002FDCC_main(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x46);
        return;
    }
    target = &Hu3DData[D_8010B8E0_swinging_with_sharks[32]];
    self = &Hu3DData[model];
    dx = target->pos.x - self->pos.x;
    dy = target->pos.y - self->pos.y;
    dz = target->pos.z - self->pos.z;
    angle = atan2df(dx, dz);
    func_8002FD8C_main(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x46);
    node = func_8001D33C_main(model, "c162_000-atama");
    node->baseRot.y = node->rot.y = angle - self->rot.y;
    func_8002FD8C_main(model, Hu3DData[model].motId, "c162_000-atama", 0x4C, 0x45);
    node->baseRot.x = node->rot.x = -atan2df(dy, dz);
}

void func_8010A260_swinging_with_sharks(void) {
    s16 model = D_8010B8E0_swinging_with_sharks[33];
    HmfModel *base = &Hu3DData[D_8010B8E0_swinging_with_sharks[32]];
    s16 alpha;
    f32 len;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 t;
    f32 x;
    f32 z;

    if (base->pos.y < 90.0f) {
        alpha = (base->pos.y - 40.0f) / 50.0f * 102.0f;
        if (alpha <= 0) {
            alpha = 0;
            func_8001C258_main(model, 4, 4);
        }
        func_8001F9E4_main(model, alpha);
    } else {
        func_8001C258_main(model, 4, 0);
        func_8001F9E4_main(model, 102);
    }
    len = HuSqrtf(-1.3f * -1.3f + -1.0f * -1.0f + -1.3f * -1.3f);
    dx = -1.3f / len;
    dy = -1.0f / len;
    dz = -1.3f / len;
    t = 1.0f / dy;
    if (t < 0.0f) {
        t = -t;
    }
    dx *= t;
    dz *= t;
    x = dx * base->pos.y + base->pos.x;
    z = dz * base->pos.y + base->pos.z;
    Hu3DModelPosSet(model, x, 0.0f, z);
}

void func_8010A41C_swinging_with_sharks(void) {
    s16 i;

    func_8001FA68_main(D_8010B8E0_swinging_with_sharks[46]);
    func_8001C514_main(D_8010B8E0_swinging_with_sharks[46]);
    for (i = 0; i < 20; i++) {
        D_8010BB20_swinging_with_sharks[i] = func_8000B108_main(0xB0031, 0xA8C);
        D_8010BAF8_swinging_with_sharks[i] = 90;
        func_8001FA68_main(D_8010BB20_swinging_with_sharks[i]);
        func_8001C514_main(D_8010BB20_swinging_with_sharks[i]);
    }
}

void func_8010A4DC_swinging_with_sharks(void) {
    HmfModel *source;
    f32 scale;
    s16 model;
    s16 i;
    s16 j;

    for (i = 0; i < 2; i++) {
        if (((D_8010B76A_swinging_with_sharks + i * 2) & 7) == 0) {
            source = &Hu3DData[D_8010BAF0_swinging_with_sharks[i]];
            if (!(source->pos.y < -100.0f)) {
                for (j = 0; j < 20; j++) {
                    if (D_8010BAF8_swinging_with_sharks[j] >= 90) {
                        D_8010BAF8_swinging_with_sharks[j] = 0;
                        Hu3DModelPosSet(D_8010BB20_swinging_with_sharks[j], source->pos.x, 0.0f, source->pos.z);
                        Hu3DModelRotSet(D_8010BB20_swinging_with_sharks[j], 0.0f, source->rot.y, 0.0f);
                        func_8001C258_main(D_8010BB20_swinging_with_sharks[j], 4, 0);
                        break;
                    }
                }
            }
        }
    }
    model = D_8010B8E0_swinging_with_sharks[46];
    scale = sindf(D_8010B76A_swinging_with_sharks % 90) * 1.5f + 0.5f;
    Hu3DModelScaleSet(model, scale, scale, scale);
    func_8001F9E4_main(model, 255.0f - D_8010B76A_swinging_with_sharks * (255.0f / 90.0f));
    D_8010B76A_swinging_with_sharks += 2;
    if (D_8010B9E0_swinging_with_sharks >= 3 &&
        Hu3DData[D_8010B8E0_swinging_with_sharks[47]].motId == D_8010B948_swinging_with_sharks[49]) {
        if (D_8010B76A_swinging_with_sharks > 90) {
            func_8001C258_main(model, 4, 4);
        }
        if ((D_8010B76A_swinging_with_sharks & 0xF) == 0) {
            source = &Hu3DData[D_8010B8E0_swinging_with_sharks[44]];
            for (j = 0; j < 20; j++) {
                if (D_8010BAF8_swinging_with_sharks[j] >= 90) {
                    D_8010BAF8_swinging_with_sharks[j] = 0;
                    Hu3DModelPosSet(D_8010BB20_swinging_with_sharks[j], source->pos.x, 0.0f, source->pos.z);
                    Hu3DModelRotSet(D_8010BB20_swinging_with_sharks[j], 0.0f, source->rot.y, 0.0f);
                    func_8001C258_main(D_8010BB20_swinging_with_sharks[j], 4, 0);
                    break;
                }
            }
        }
    }
    if (D_8010B76A_swinging_with_sharks > 90) {
        D_8010B76A_swinging_with_sharks = 0;
    }
    for (i = 0; i < 20; i++) {
        if (D_8010BAF8_swinging_with_sharks[i] >= 90) {
            func_8001C258_main(D_8010BB20_swinging_with_sharks[i], 4, 4);
        } else {
            scale = sindf(D_8010BAF8_swinging_with_sharks[i] % 90) * 1.5f;
            Hu3DModelScaleSet(D_8010BB20_swinging_with_sharks[i], scale, scale, scale);
            func_8001F9E4_main(D_8010BB20_swinging_with_sharks[i],
                               128.0f - D_8010BAF8_swinging_with_sharks[i] * (128.0f / 90.0f));
            D_8010BAF8_swinging_with_sharks[i] += 2;
        }
    }
}

void func_8010AA68_swinging_with_sharks(void) {
    D_8010BB48_swinging_with_sharks = Hu3DData[D_8010B8E0_swinging_with_sharks[44]].rot.y;
}

void func_8010AAA0_swinging_with_sharks(void) {
    s16 model = D_8010B8E0_swinging_with_sharks[44];
    f32 x;
    f32 y;
    f32 z;

    if (D_8010B9E0_swinging_with_sharks >= 3 &&
        Hu3DData[D_8010B8E0_swinging_with_sharks[47]].motId == D_8010B948_swinging_with_sharks[49]) {
        if (D_8010B76C_swinging_with_sharks == 0) {
            Hu3DMotionShiftSet(D_8010B8E0_swinging_with_sharks[model], D_8010B948_swinging_with_sharks[45], 0, 4, 2);
        }
        if (++D_8010B76C_swinging_with_sharks >= 30) {
            if (D_8010BB48_swinging_with_sharks < 90) {
                D_8010BB48_swinging_with_sharks += 1.5f;
            }
            x = Hu3DData[model].pos.x + sindf(D_8010BB48_swinging_with_sharks) * 10.0f;
            y = Hu3DData[model].pos.y;
            z = Hu3DData[model].pos.z + cosdf(D_8010BB48_swinging_with_sharks) * 10.0f;
            Hu3DModelPosSet(model, x, y, z);
            Hu3DData[model].rot.y = D_8010BB48_swinging_with_sharks;
            Hu3DData[D_8010B8E0_swinging_with_sharks[47]].pos.x = x;
            Hu3DData[D_8010B8E0_swinging_with_sharks[47]].pos.z = z;
            Hu3DData[D_8010B8E0_swinging_with_sharks[47]].rot.y = D_8010BB48_swinging_with_sharks;
        }
    }
}
