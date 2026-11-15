#include "common.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/effect.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hmfanim.h"
#include "game/hmfparticle.h"
#include "game/hmfspr.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/wipe.h"
#include "math.h"

typedef struct HeyBatterBatterBase {
    /* 0x00 */ s16 base;
    /* 0x02 */ s16 shadow;
} HeyBatterBatterBase; // Size 0x4

typedef struct HeyBatterBatterCamera {
    /* 0x00 */ f32 zoom;
    /* 0x04 */ Vec rot;
    /* 0x10 */ Vec center;
} HeyBatterBatterCamera; // Size 0x1C

typedef struct HeyBatterBatterBssEE4 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s16 unk06[2];
    /* 0x0A */ s16 unk0A;
} HeyBatterBatterBssEE4; // Size 0xC

extern s32 D_800A178C_main[][6];
extern u16 D_800A11D0_main[5];
extern u16 D_800A11DC_main[5];

s16 D_80109B60_hey_batter_batter = 0;
Vec D_80109B64_hey_batter_batter[4] = { { -15.0f, 0.0f, 0.0f }, { 5.0f, 90.0f, 0.0f }, { 5.0f, -90.0f, 0.0f }, { 10.0f, 0.0f, 0.0f } };
Vec D_80109B94_hey_batter_batter[4] = { { 0.0f, 175.0f, -200.0f }, { -800.0f, 170.0f, 0.0f }, { 890.0f, 170.0f, -10.0f }, { 0.0f, 225.0f, -1700.0f } };
Vec D_80109BC4_hey_batter_batter[2] = { { 5.0f, 0.0f, 0.0f }, { 5.0f, 0.0f, 0.0f } };
Vec D_80109BDC_hey_batter_batter[2] = { { -110.0f, 200.0f, -575.0f }, { 110.0f, 200.0f, -575.0f } };
Vec D_80109BF4_hey_batter_batter[5] = {
    { 600.0f, 250.0f, -1000.0f },
    { 400.0f, 250.0f, -1400.0f },
    { 0.0f, 250.0f, -1600.0f },
    { -400.0f, 250.0f, -1400.0f },
    { -600.0f, 250.0f, -1000.0f },
};
s16 D_80109C30_hey_batter_batter = 0;
s16 D_80109C32_hey_batter_batter = 0;
s16 D_80109C34_hey_batter_batter = 0;
s16 D_80109C36_hey_batter_batter = 0;
s16 D_80109C38_hey_batter_batter = 0;
f32 D_80109C3C_hey_batter_batter = 0.0f;
s16 D_80109C40_hey_batter_batter = 0;
s16 D_80109C42_hey_batter_batter = 0;
s16 D_80109C44_hey_batter_batter = 0;
s16 D_80109C46_hey_batter_batter = 4;
s16 D_80109C48_hey_batter_batter = 0;
s16 D_80109C4A_hey_batter_batter = 0;
Vec D_80109C4C_hey_batter_batter[5] = {
    { 600.0f, 500.0f, -2200.0f },
    { -600.0f, 700.0f, -2200.0f },
    { -2000.0f, 500.0f, -700.0f },
    { -2000.0f, 1000.0f, 0.0f },
    { -2000.0f, 800.0f, 800.0f },
};
s16 D_80109C88_hey_batter_batter = 999;
s16 D_80109C8A_hey_batter_batter = 0;
s16 D_80109C8C_hey_batter_batter = 0;
s16 D_80109C8E_hey_batter_batter = 999;
f32 D_80109C90_hey_batter_batter = 0.0f;
s16 D_80109C94_hey_batter_batter = 0;
s16 D_80109C96_hey_batter_batter = 0;
f32 D_80109C98_hey_batter_batter = 30.0f;
f32 D_80109C9C_hey_batter_batter = 1000.0f;
f32 D_80109CA0_hey_batter_batter = 100.0f;
s16 D_80109CA4_hey_batter_batter = 0;
Vec D_80109CA8_hey_batter_batter[7] = {
    { 4.0f, 0.0f, 0.05f },
    { 575.0f, 225.0f, -999.0f },
    { 375.0f, 225.0f, -1399.0f },
    { 0.0f, 225.0f, -1599.0f },
    { -375.0f, 225.0f, -1399.0f },
    { -575.0f, 225.0f, -999.0f },
    { -3.0f, 0.0f, 2.0f },
};
s16 D_80109CFC_hey_batter_batter = 0;
f32 D_80109D00_hey_batter_batter = 1.47f;
Vec D_80109D04_hey_batter_batter[5] = {
    { 600.0f, 5.0f, -1000.0f },
    { 400.0f, 5.0f, -1400.0f },
    { 0.0f, 5.0f, -1600.0f },
    { -400.0f, 5.0f, -1400.0f },
    { -600.0f, 5.0f, -1000.0f },
};
s32 D_80109D40_hey_batter_batter[20] = {
    0x0021002D, 0x0021002E, 0x0021002F, 0x00210030, 0x00210031,
    0x00210032, 0x00210033, 0x00210034, 0x00210035, 0x00210036,
    0x00210037, 0x00210038, 0x00210039, 0x0021003A, 0x0021003B,
    0x0021003C, 0x0021003D, 0x0021003E, 0x0021003F, 0x00210040
};
s16 D_80109D90_hey_batter_batter = 0;
s16 D_80109D92_hey_batter_batter = 0;
s16 D_80109D94_hey_batter_batter = 0;
s16 D_80109D96_hey_batter_batter = 0;
s16 D_80109D98_hey_batter_batter = 0;

s16 D_80109EA0_hey_batter_batter BSS;
s16 D_80109EA2_hey_batter_batter BSS;
s16 D_80109EA4_hey_batter_batter BSS;
s16 D_80109EA6_hey_batter_batter BSS;
s16 D_80109EA8_hey_batter_batter BSS;
s16 D_80109EAA_hey_batter_batter BSS;
s16 D_80109EAC_hey_batter_batter BSS;
s16 D_80109EAE_hey_batter_batter BSS;
u8 D_80109EB0_hey_batter_batter[4] BSS; /* Unreferenced. */
HeyBatterBatterCamera D_80109EB4_hey_batter_batter BSS;
s16 D_80109ED0_hey_batter_batter BSS;
s16 D_80109ED2_hey_batter_batter BSS;
s16 D_80109ED4_hey_batter_batter BSS;
s16 D_80109ED6_hey_batter_batter BSS;
s16 D_80109ED8_hey_batter_batter BSS;
s16 D_80109EDA_hey_batter_batter BSS;
s16 D_80109EDC_hey_batter_batter BSS;
s16 D_80109EDE_hey_batter_batter BSS;
s16 D_80109EE0_hey_batter_batter BSS;
s16 D_80109EE2_hey_batter_batter BSS;
HeyBatterBatterBssEE4 heyBatterBatterBssEE4 BSS;
s16 D_80109EF0_hey_batter_batter BSS;
omObjData *D_80109EF4_hey_batter_batter BSS;
s16 D_80109EF8_hey_batter_batter[4] BSS;
s16 D_80109F00_hey_batter_batter[5] BSS;
s16 D_80109F0C_hey_batter_batter[5] BSS;
HeyBatterBatterBase D_80109F18_hey_batter_batter[5] BSS;
s16 D_80109F2C_hey_batter_batter[5] BSS;

extern s16 D_80109EE4_hey_batter_batter;
extern s16 D_80109EE6_hey_batter_batter[2];
extern s16 D_80109EEA_hey_batter_batter[2];
extern s16 D_80109EEE_hey_batter_batter;

void func_801059BC_hey_batter_batter(void);
void func_80105A4C_hey_batter_batter(void);
void func_80105AB8_hey_batter_batter(void);
void func_80105C44_hey_batter_batter(void);
void func_80105CE8_hey_batter_batter(omObjData *object);
void func_80105DE0_hey_batter_batter(void);
void func_80106048_hey_batter_batter(omObjData *object);
void func_801062E0_hey_batter_batter(omObjData *object);
void func_80106744_hey_batter_batter(omObjData *object);
void func_80106928_hey_batter_batter(omObjData *object);
void func_80106C24_hey_batter_batter(omObjData *object);
void func_80106C6C_hey_batter_batter(omObjData *object);
void func_80106CBC_hey_batter_batter(omObjData *object);
void func_80106CE4_hey_batter_batter(omObjData *object);
void func_80106FA8_hey_batter_batter(omObjData *object);
void func_801070D8_hey_batter_batter(omObjData *object);
void func_80107144_hey_batter_batter(omObjData *object);
void func_80107464_hey_batter_batter(omObjData *object);
void func_801079D0_hey_batter_batter(omObjData *object);
void func_80107C48_hey_batter_batter(omObjData *object);
void func_80108B48_hey_batter_batter(omObjData *object);
void func_80108D90_hey_batter_batter(omObjData *object);
void func_8010951C_hey_batter_batter(omObjData *object);
void func_80109630_hey_batter_batter(omObjData *object);
void func_801098DC_hey_batter_batter(f32 startZoom, Vec startRot, Vec startCenter, f32 endZoom, Vec endRot,
                                     Vec endCenter, f32 duration, f32 time);
s16 func_80109A78_hey_batter_batter(s32 spriteId, u16 attr, u16 priority, s16 x, s16 y);
s16 func_80109B24_hey_batter_batter(s32 arg0);

void func_801059A0_hey_batter_batter(void) {
    func_801059BC_hey_batter_batter();
}

void func_801059BC_hey_batter_batter(void) {
    MapCollInit(32);
    Hu3DSprModelInit(32);
    omInitObjMan(32, 32);
    omGameSysInit();
    func_80105A4C_hey_batter_batter();
    func_80105AB8_hey_batter_batter();
    func_80105C44_hey_batter_batter();
    omAddObj(1000, 0, 0, -1, func_80105CE8_hey_batter_batter);
    omAddObj(2000, 0, 0, -1, func_80106CBC_hey_batter_batter);
}

void func_80105A4C_hey_batter_batter(void) {
    Hu3DGLightMaxSet(3);
    Hu3DGLightDirSet(1, -10.0f, -10.0f, 150.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, -82.0f, 255.0f, -60.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
}

void func_80105AB8_hey_batter_batter(void) {
    s16 camIndex;

    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 45.0f, 80.0f, 8000.0f);
    D_80109EB4_hey_batter_batter.zoom = CZoom = 1065.0f;
    CRot.x = -15.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    D_80109EB4_hey_batter_batter.rot = CRot;
    Center.x = 0.0f;
    Center.y = 175.0f;
    Center.z = -200.0f;
    D_80109EB4_hey_batter_batter.center = Center;
}

void func_80105C44_hey_batter_batter(void) {
    s16 i = 0;
    s16 players[4] = { 0, 1, 2, 3 };

    for (; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            break;
        }
    }
    if (i < 4) {
        D_80109ED0_hey_batter_batter = players[i];
    } else {
        D_80109ED0_hey_batter_batter = players[0];
    }
}

void func_80105CE8_hey_batter_batter(omObjData *object) {
    func_80105DE0_hey_batter_batter();
    omAddObj(10, 10, 0, -1, func_80106CE4_hey_batter_batter);
    omAddObj(20, 10, 0, -1, func_801070D8_hey_batter_batter);
    D_80109EF4_hey_batter_batter = omAddObj(30, 10, 10, -1, func_80107144_hey_batter_batter);
    omAddObj(40, 10, 10, -1, func_801079D0_hey_batter_batter);
    omAddObj(50, 20, 5, -1, func_80108B48_hey_batter_batter);
    omAddObj(60, 10, 10, -1, func_8010951C_hey_batter_batter);
    object->func = func_80106048_hey_batter_batter;
}

void func_80105DE0_hey_batter_batter(void) {
    s16 thresholds[5];
    s16 i;
    s16 roll;

    D_80109EE0_hey_batter_batter = 1;
    D_80109EE2_hey_batter_batter = 0;
    D_80109EE4_hey_batter_batter = 0;
    if (GwPlayer[D_80109ED0_hey_batter_batter].stat & 1) {
        thresholds[0] = D_800A11DC_main[0];
        for (i = 1; i < 5; i++) {
            thresholds[i] = thresholds[i - 1] + D_800A11DC_main[i];
        }
        roll = rand8() % 100;
        for (i = 0; i < 5; i++) {
            if (roll < thresholds[i]) {
                break;
            }
        }
        D_80109ED6_hey_batter_batter = i + 20;
        if (GwPlayer[D_80109ED0_hey_batter_batter].cpu_difficulty == 0) {
            if ((rand8() & 3) == 0) {
                if ((rand8() & 1) == 0) {
                    D_80109ED6_hey_batter_batter = 19 - rand8() % 3;
                } else {
                    D_80109ED6_hey_batter_batter = rand8() % 3 + 25;
                }
            }
        } else if (GwPlayer[D_80109ED0_hey_batter_batter].cpu_difficulty == 1) {
            if ((rand8() & 15) == 0) {
                if ((rand8() & 1) == 0) {
                    D_80109ED6_hey_batter_batter = 19 - (rand8() & 1);
                } else {
                    D_80109ED6_hey_batter_batter = (rand8() & 1) + 25;
                }
            }
        }
    }
}

void func_80106048_hey_batter_batter(omObjData *object) {
    switch (D_80109C30_hey_batter_batter) {
        case 0:
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            D_80109C30_hey_batter_batter++;
            break;
        case 1:
            object->func = func_801062E0_hey_batter_batter;
            D_80109C30_hey_batter_batter++;
            break;
        case 2:
            if (++D_80109C34_hey_batter_batter == 1) {
                GMesCreate(8);
            } else if (GMesStatGet() == 0) {
                D_80109C34_hey_batter_batter = 0;
                D_80109C30_hey_batter_batter++;
            }
            break;
        case 3:
            object->func = func_80106744_hey_batter_batter;
            D_80109C30_hey_batter_batter++;
            break;
        case 4:
            if (++D_80109C34_hey_batter_batter == 1) {
                CharAnimSet(D_80109EF4_hey_batter_batter->model[0], 1,
                                   GwPlayer[D_80109ED0_hey_batter_batter].chr, D_80109EF8_hey_batter_batter[1]);
                D_80109B60_hey_batter_batter = 1;
                GMesCreate(0x13);
                HuAudSeqFadeOut(120);
            } else if (GMesStatGet() == 0) {
                D_80109C34_hey_batter_batter = 0;
                D_80109C30_hey_batter_batter++;
            }
            break;
        case 5:
            object->func = func_80106928_hey_batter_batter;
            D_80109C30_hey_batter_batter++;
            break;
        case 6:
            if (++D_80109C34_hey_batter_batter == 1) {
                switch (D_80109EE0_hey_batter_batter) {
                    case 0:
                        HuAudSeqPlay(0x68);
                        D_80109C32_hey_batter_batter = GMesCreate(0x24);
                        GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin =
                            D_800A11D0_main[D_80109EF0_hey_batter_batter];
                        break;
                    case 1:
                        HuAudSeqPlay(0x6B);
                        D_80109C32_hey_batter_batter = GMesCreate(0x1D);
                        GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin = -1;
                        break;
                }
                GMesTimeMaxSet(D_80109C32_hey_batter_batter, 120);
            } else if (D_80109C34_hey_batter_batter >= 135) {
                D_80109C34_hey_batter_batter = 0;
                D_80109C30_hey_batter_batter++;
            }
            break;
        case 7:
            object->func = func_80106C24_hey_batter_batter;
            break;
        case 8:
            break;
    }
}

void func_801062E0_hey_batter_batter(omObjData *object) {
    switch (D_80109C36_hey_batter_batter) {
        case 0:
            if (WipeStatGet() != 1) {
                HuAudSeqPlay(0x44);
                HuAudFXPlay(0x4D5);
                D_80109C3C_hey_batter_batter = 0.0f;
                D_80109C38_hey_batter_batter = 0;
                D_80109C36_hey_batter_batter = 1;
            }
            break;
        case 1:
            if (D_80109C38_hey_batter_batter++ >= 5) {
                D_80109C36_hey_batter_batter++;
                D_80109C38_hey_batter_batter = 0;
            }
            break;
        case 2:
            func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[0],
                                            D_80109B94_hey_batter_batter[0], D_80109EB4_hey_batter_batter.zoom,
                                            D_80109B64_hey_batter_batter[1], D_80109B94_hey_batter_batter[1], 20.0f,
                                            D_80109C3C_hey_batter_batter);
            if (sindf(D_80109C3C_hey_batter_batter * 4.5f) >= 1.0f) {
                D_80109C36_hey_batter_batter++;
                D_80109C3C_hey_batter_batter = 0.0f;
                D_80109B60_hey_batter_batter = 2;
            } else {
                D_80109C3C_hey_batter_batter += 1.0f;
            }
            break;
        case 3:
            if (D_80109C38_hey_batter_batter++ >= 30) {
                D_80109C36_hey_batter_batter++;
                D_80109C38_hey_batter_batter = 0;
            }
            break;
        case 4:
            func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[1],
                                            D_80109B94_hey_batter_batter[1], D_80109EB4_hey_batter_batter.zoom,
                                            D_80109B64_hey_batter_batter[3], D_80109B94_hey_batter_batter[3], 20.0f,
                                            D_80109C3C_hey_batter_batter);
            if (sindf(D_80109C3C_hey_batter_batter * 4.5f) >= 1.0f) {
                D_80109C36_hey_batter_batter++;
                D_80109C3C_hey_batter_batter = 0.0f;
            } else {
                D_80109C3C_hey_batter_batter += 1.0f;
            }
            break;
        case 5:
            if (D_80109C38_hey_batter_batter++ >= 20) {
                D_80109C36_hey_batter_batter++;
                D_80109C38_hey_batter_batter = 0;
                D_80109ED2_hey_batter_batter = 6;
            }
            break;
        case 6:
            func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[3],
                                            D_80109B94_hey_batter_batter[3], D_80109EB4_hey_batter_batter.zoom,
                                            D_80109B64_hey_batter_batter[0], D_80109B94_hey_batter_batter[0], 30.0f,
                                            D_80109C3C_hey_batter_batter);
            if (sindf(D_80109C3C_hey_batter_batter * 3.0f) == 1.0f) {
                D_80109C36_hey_batter_batter++;
                D_80109C3C_hey_batter_batter = 0.0f;
            } else {
                D_80109C3C_hey_batter_batter += 1.0f;
            }
            break;
        case 7:
            D_80109C3C_hey_batter_batter = 0.0f;
            D_80109C38_hey_batter_batter = 0;
            D_80109C36_hey_batter_batter = 0;
            object->func = func_80106048_hey_batter_batter;
            break;
        case 8:
            break;
    }
}

void func_80106744_hey_batter_batter(omObjData *object) {
    switch (D_80109C40_hey_batter_batter) {
        case 0:
            D_80109C42_hey_batter_batter = 0;
            D_80109C40_hey_batter_batter = 0;
            D_80109C44_hey_batter_batter = 0;
            D_80109C46_hey_batter_batter = 91;
            D_80109C40_hey_batter_batter = 1;
            break;
        case 1:
            if (D_80109C42_hey_batter_batter++ >= 30) {
                D_80109EDA_hey_batter_batter = 3;
                D_80109C40_hey_batter_batter++;
            }
            break;
        case 2:
            HuAudFXPlay(8);
            D_80109C44_hey_batter_batter = GMesCreate(0x1A, 3, 150, 160);
            GMesPosSet(D_80109C44_hey_batter_batter, 150.0f, 160.0f);
            D_80109C40_hey_batter_batter++;
            break;
        case 3:
            if (D_80109C46_hey_batter_batter-- >= 0) {
                GMesTimerValueSet((D_80109C46_hey_batter_batter + 29) / 30);
            } else {
                GMesTimerEnd();
                D_80109EDA_hey_batter_batter = 4;
                D_80109C40_hey_batter_batter++;
            }
            break;
        case 4:
            D_80109ED8_hey_batter_batter = 1;
            D_80109C40_hey_batter_batter++;
            break;
        case 5:
            if (D_80109EDE_hey_batter_batter == 2) {
                if ((D_80109ED4_hey_batter_batter == 1 && D_80109C42_hey_batter_batter++ >= 30) ||
                    D_80109ED4_hey_batter_batter == 2) {
                    object->func = func_80106048_hey_batter_batter;
                }
            }
            break;
        case 6:
            break;
    }
}

void func_80106928_hey_batter_batter(omObjData *object) {
    switch (D_80109C48_hey_batter_batter) {
        case 0:
            switch (D_80109ED4_hey_batter_batter) {
                case 1:
                    D_80109EE0_hey_batter_batter = 0;
                    break;
                case 2:
                    D_80109EE0_hey_batter_batter = 1;
                    break;
            }
            D_80109C48_hey_batter_batter++;
            break;
        case 1:
            if (D_80109EE0_hey_batter_batter == 0) {
                D_80109EEE_hey_batter_batter = 3;
                func_801098DC_hey_batter_batter(D_80109EB4_hey_batter_batter.zoom, D_80109B64_hey_batter_batter[0],
                                                D_80109B94_hey_batter_batter[0], D_80109EB4_hey_batter_batter.zoom,
                                                D_80109BC4_hey_batter_batter[0], D_80109BDC_hey_batter_batter[0], 30.0f,
                                                D_80109C4A_hey_batter_batter);
                if (sindf(D_80109C4A_hey_batter_batter * 3.0f) >= 1.0f) {
                    D_80109C48_hey_batter_batter++;
                    D_80109C4A_hey_batter_batter = 0;
                } else {
                    D_80109C4A_hey_batter_batter++;
                }
            } else if (D_80109EE0_hey_batter_batter == 1) {
                D_80109C48_hey_batter_batter++;
            }
            break;
        case 2:
            if (D_80109EE0_hey_batter_batter == 1) {
                CharAnimSet(D_80109EF4_hey_batter_batter->model[0], 1,
                                   GwPlayer[D_80109ED0_hey_batter_batter].chr, D_80109EF8_hey_batter_batter[3]);
                D_80109ED2_hey_batter_batter = 3;
                D_80109EDA_hey_batter_batter = 1;
                HuAudFXPlay(0x4D8);
            } else if (D_80109EE0_hey_batter_batter == 0) {
                CharAnimSet(D_80109EF4_hey_batter_batter->model[0], 1,
                                   GwPlayer[D_80109ED0_hey_batter_batter].chr, D_80109EF8_hey_batter_batter[2]);
                D_80109ED2_hey_batter_batter = 2;
                D_80109EDA_hey_batter_batter = 2;
            }
            D_80109C48_hey_batter_batter++;
            break;
        case 3:
            object->func = func_80106048_hey_batter_batter;
            break;
    }
}

void func_80106C24_hey_batter_batter(omObjData *object) {
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    HuAudFXAllFadeOut(30);
    object->func = func_80106C6C_hey_batter_batter;
}

void func_80106C6C_hey_batter_batter(omObjData *object) {
    if (WipeStatGet() != 1) {
        osViBlack(0);
        GMesClose();
        HuWinAllKill();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void func_80106CBC_hey_batter_batter(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_80106C24_hey_batter_batter;
    }
}

void func_80106CE4_hey_batter_batter(omObjData *object) {
    s16 i;
    s16 model;

    func_80109A78_hey_batter_batter(0x5D0000, 0x4000, 1000, 160, 120);
    for (i = 0; i < 2; i++) {
        model = D_80109F00_hey_batter_batter[i] = Hu3DModelRead(0x5D0003, 0x2A9);
        Hu3DModelPosSet(model, D_80109C4C_hey_batter_batter[i].x, D_80109C4C_hey_batter_batter[i].y,
                        D_80109C4C_hey_batter_batter[i].z);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DData[model].rot.x = 20.0f;
        D_80109F0C_hey_batter_batter[i] = rand8() % 90;
    }
    for (; i < 5; i++) {
        model = D_80109F00_hey_batter_batter[i] = Hu3DModelRead(0x5D0003, 0x2A9);
        Hu3DModelPosSet(model, D_80109C4C_hey_batter_batter[i].x, D_80109C4C_hey_batter_batter[i].y,
                        D_80109C4C_hey_batter_batter[i].z);
        Hu3DModelScaleSet(model, 2.0f, 2.0f, 2.0f);
        Hu3DData[model].rot.x = 20.0f;
        Hu3DData[model].rot.y = 90.0f;
        D_80109F0C_hey_batter_batter[i] = rand8() % 90;
    }
    object->func = func_80106FA8_hey_batter_batter;
}

void func_80106FA8_hey_batter_batter(omObjData *object) {
    s16 i;
    s16 model;

    for (i = 0; i < 5; i++) {
        model = D_80109F00_hey_batter_batter[i];
        Hu3DData[model].scale.x = Hu3DData[model].scale.y = Hu3DData[model].scale.z =
            sindf(D_80109F0C_hey_batter_batter[i] * 2.0f) * 0.5f + 2.0f;
        if (D_80109F0C_hey_batter_batter[i]++ >= 180.0f) {
            D_80109F0C_hey_batter_batter[i] = 0;
        }
    }
}

void func_801070D8_hey_batter_batter(omObjData *object) {
    object->model[0] = Hu3DModelRead(0x5D0001, 0x2A9);
    object->model[1] = Hu3DModelRead(0x5D0002, 0x2A9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -1000.0f);
    object->func = NULL;
}

void func_80107144_hey_batter_batter(omObjData *object) {
    s32 chr = GwPlayer[D_80109ED0_hey_batter_batter].chr;

    object->model[0] = Hu3DModelRead(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x6A8);
    object->model[1] = Hu3DModelRead(0x5D0005, 0x6A9);
    object->model[2] = Hu3DModelRead(9, 0x2A9);
    omObjMotionRead(object, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0x82));
    omObjMotionRead(object, 2, CharMotionDataNumGet(chr, 0x35));
    omObjMotionRead(object, 3, CharMotionDataNumGet(chr, 0x38));
    omObjMotionRead(object, 4, CharMotionDataNumGet(chr, 0x83));
    omObjMotionRead(object, 5, CharMotionDataNumGet(chr, 1));
    if (chr == 5) {
        omObjMotionRead(object, 6, 0x5D000A);
    }
    Hu3DModelAttrSet(object->model[1], 0x4000, 0x4000);
    Hu3DModelHookSet(object->model[1], object->model[0], "item_hook");
    omSetTra(object, -150.0f, 15.0f, 0.0f);
    omSetRot(object, 0.0f, 180.0f, 0.0f);
    Hu3DModelPosSet(object->model[2], -150.0f, 15.0f, 0.0f);
    GwPlayer[D_80109ED0_hey_batter_batter].bonusCoin = -1;
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[1]].motId, 0, 2, 2);
    D_80109ED2_hey_batter_batter = 1;
    D_80109EF8_hey_batter_batter[0] = CharAnimCreate(object->model[0], 1, chr, CharMotionDataNumGet(chr, 0xAA));
    D_80109EF8_hey_batter_batter[1] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA4));
    D_80109EF8_hey_batter_batter[2] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA5));
    D_80109EF8_hey_batter_batter[3] = Hu3DAnimDataRead(CharMotionDataNumGet(chr, 0xA6));
    Hu3DModelDynamicFree(object->model[0]);
    CharAnimSet(object->model[0], 1, GwPlayer[D_80109ED0_hey_batter_batter].chr,
                       D_80109EF8_hey_batter_batter[0]);
    object->func = func_80107464_hey_batter_batter;
}

void func_80107464_hey_batter_batter(omObjData *object) {
    if (D_80109C88_hey_batter_batter != D_80109ED2_hey_batter_batter) {
        switch (D_80109ED2_hey_batter_batter) {
            case 0:
            case 1:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_80109ED2_hey_batter_batter]].motId, 0,
                                   30, 2);
                break;
            case 2:
                Hu3DMotionModelSet(object->model[0], object->motion[2]);
                HuAudCharVoicePlay(D_800A178C_main[GwPlayer[D_80109ED0_hey_batter_batter].chr][0] | 0x35);
                break;
            case 3:
                Hu3DMotionModelSet(object->model[0], object->motion[3]);
                HuAudCharVoicePlay(D_800A178C_main[GwPlayer[D_80109ED0_hey_batter_batter].chr][0] | 0x38);
                break;
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_80109ED2_hey_batter_batter]].motId, 0,
                                   15, 0);
                break;
            case 5:
                Hu3DMotionModelSet(object->model[0], object->motion[4]);
                Hu3DMotionTimeSet(object->model[0], D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02);
                Hu3DMotionSpeedSet(object->model[0], -0.9f);
                break;
            case 6:
                Hu3DMotionSpeedSet(object->model[0], 1.0f);
                break;
            case 7:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[5]].motId, 0, 10, 2);
                break;
            case 8:
                Hu3DMotionModelSet(object->model[0], object->motion[6]);
                break;
        }
        D_80109C88_hey_batter_batter = D_80109ED2_hey_batter_batter;
    }
    if (D_80109B60_hey_batter_batter == 1) {
        switch (D_80109C8A_hey_batter_batter) {
            case 0:
                D_80109EEA_hey_batter_batter[1] = 1;
                if (GwPlayer[D_80109ED0_hey_batter_batter].chr == 5 && D_80109ED2_hey_batter_batter == 4) {
                    D_80109ED2_hey_batter_batter = 8;
                } else {
                    D_80109ED2_hey_batter_batter = 0;
                }
                Hu3DModelCameraSet(object->model[1], 0);
                D_80109C8A_hey_batter_batter++;
                break;
            case 1:
                if (D_80109C8C_hey_batter_batter++ >= 45) {
                    D_80109C8A_hey_batter_batter++;
                }
                break;
            case 2:
                if (object->rot.y > 0.0f) {
                    D_80109ED2_hey_batter_batter = 7;
                    object->rot.y -= 10.0f;
                } else {
                    D_80109ED2_hey_batter_batter = 0;
                    D_80109C8A_hey_batter_batter++;
                }
                break;
        }
    }
    if (D_80109B60_hey_batter_batter == 2) {
        switch (D_80109C8A_hey_batter_batter) {
            case 0:
                HuAudFXPlay(0x4D0);
                D_80109ED2_hey_batter_batter = 4;
                D_80109C8A_hey_batter_batter++;
                break;
            case 1:
                if (D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 == Hu3DData[object->model[0]].motTime) {
                    D_80109ED2_hey_batter_batter = 5;
                    D_80109C8A_hey_batter_batter++;
                }
                break;
            case 2:
                if (Hu3DData[object->model[0]].motTime <= 3.0f) {
                    D_80109ED2_hey_batter_batter = 1;
                    Hu3DMotionSpeedSet(object->model[0], 0.0f);
                    Hu3DMotionTimeSet(object->model[0], 0.0f);
                    D_80109C8A_hey_batter_batter = 0;
                    D_80109B60_hey_batter_batter = 0;
                }
                break;
        }
    }
}

void func_801079D0_hey_batter_batter(omObjData *object) {
    void *data;
    s16 anim;

    object->model[0] = Hu3DModelRead(0xA00EE, 0x2A9);
    object->model[1] = Hu3DModelRead(0x5D0009, 0x2A9);
    object->model[2] = Hu3DModelRead(9, 0x6A9);
    object->model[3] = Hu3DModelRead(0x5D0004, 0x2A9);
    object->model[4] = Hu3DModelRead(9, 0x6A9);
    data = DataRead(0xA0100);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c162n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    Hu3DAnimBankSet(anim, 0);
    Hu3DAnimAttrSet(anim, 1, 0);
    omObjMotionRead(object, 0, 0xA00F7);
    omObjMotionRead(object, 1, 0xA00F6);
    omObjMotionRead(object, 2, 0xA00F2);
    omObjMotionRead(object, 3, 0xA00F8);
    omObjMotionRead(object, 4, 0xA00F9);
    omObjMotionRead(object, 5, 0xA00FA);
    Hu3DModelAttrSet(object->model[1], 0x4000, 0x4000);
    Hu3DModelHookSet(object->model[1], object->model[0], "c162_000-te2");
    Hu3DModelCameraSet(object->model[1], 1);
    omSetTra(object, 0.0f, 5.5f, -1000.0f);
    Hu3DModelPosSet(object->model[2], 0.0f, 4.0f, -1000.0f);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[0]].motId, 0, 2, 2);
    D_80109EDA_hey_batter_batter = 0;
    Hu3DModelCameraSet(object->model[3], 0);
    Hu3DModelCameraSet(object->model[4], 0);
    object->func = func_80107C48_hey_batter_batter;
}

void func_80107C48_hey_batter_batter(omObjData *object) {
    f32 scale;

    if (D_80109C8E_hey_batter_batter != D_80109EDA_hey_batter_batter) {
        switch (D_80109EDA_hey_batter_batter) {
            case 2:
            case 4:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_80109EDA_hey_batter_batter]].motId, 0,
                                   30, 0);
                break;
            case 0:
            case 1:
            case 3:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_80109EDA_hey_batter_batter]].motId, 0,
                                   30, 2);
                break;
            case 5:
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[D_80109EDA_hey_batter_batter]].motId, 0,
                                   10, 0);
                Hu3DMotionSpeedSet(object->model[0], 0.0f);
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                break;
        }
        D_80109C8E_hey_batter_batter = D_80109EDA_hey_batter_batter;
    }
    if (D_80109ED8_hey_batter_batter == 1 && Hu3DData[object->model[0]].motTime >= 26.0f) {
        HuAudFXPlay(0x4D1);
        Hu3DModelCameraSet(object->model[1], 0);
        D_80109EDE_hey_batter_batter = 1;
        D_80109ED8_hey_batter_batter = 0;
        D_80109C98_hey_batter_batter = 30.0f;
        D_80109CA0_hey_batter_batter = rand8() % 50 + 100.0f;
    }
    if (D_80109EDE_hey_batter_batter == 1) {
        switch (D_80109C94_hey_batter_batter) {
            case 0:
                Hu3DModelPosSet(object->model[3], -30.0f, 70.0f, -1015.0f);
                Hu3DModelCameraSet(object->model[3], 1);
                Hu3DModelCameraSet(object->model[4], 1);
                D_80109C90_hey_batter_batter = 1.0f;
                D_80109C96_hey_batter_batter = 0;
                D_80109EAE_hey_batter_batter = 0;
                D_80109C94_hey_batter_batter++;
                break;
            case 1:
                Hu3DData[object->model[3]].pos.z += D_80109C9C_hey_batter_batter / D_80109C98_hey_batter_batter;
                if (Hu3DData[object->model[3]].pos.y > 50.0f) {
                    Hu3DData[object->model[3]].pos.y =
                        sindf(90.0f / (D_80109C98_hey_batter_batter / 2.0f) * D_80109C90_hey_batter_batter) *
                            D_80109CA0_hey_batter_batter +
                        70.0f;
                } else {
                    Hu3DData[object->model[3]].pos.y = 50.0f;
                }
                Hu3DData[object->model[3]].rot.x += 30.0f;
                if (D_80109EAE_hey_batter_batter == 0) {
                    if (GwPlayer[D_80109ED0_hey_batter_batter].stat & 1) {
                        if (D_80109C90_hey_batter_batter == D_80109ED6_hey_batter_batter) {
                            D_80109EAE_hey_batter_batter = 1;
                            HuAudFXPlay(0x4D0);
                            D_80109ED2_hey_batter_batter = 4;
                            if (D_80109C98_hey_batter_batter - 11.0f <= D_80109C90_hey_batter_batter &&
                                D_80109C90_hey_batter_batter < D_80109C98_hey_batter_batter - 4.0f) {
                                D_80109CFC_hey_batter_batter =
                                    D_80109C98_hey_batter_batter - D_80109C90_hey_batter_batter - 5.0f;
                                D_80109CA4_hey_batter_batter = 1;
                            } else {
                                D_80109CA4_hey_batter_batter = 0;
                            }
                        }
                    } else if (D_800D5558_main[GwPlayer[D_80109ED0_hey_batter_batter].pad] & A_BUTTON) {
                        D_80109EAE_hey_batter_batter = 1;
                        HuAudFXPlay(0x4D0);
                        D_80109ED2_hey_batter_batter = 4;
                        if (D_80109C98_hey_batter_batter - 11.0f <= D_80109C90_hey_batter_batter &&
                            D_80109C90_hey_batter_batter < D_80109C98_hey_batter_batter - 4.0f) {
                            omVibrate(D_80109ED0_hey_batter_batter, 2, 2, 20);
                            D_80109CFC_hey_batter_batter =
                                D_80109C98_hey_batter_batter - D_80109C90_hey_batter_batter - 5.0f;
                            D_80109CA4_hey_batter_batter = 1;
                        } else {
                            D_80109CA4_hey_batter_batter = 0;
                        }
                    }
                }
                if (D_80109CA4_hey_batter_batter == 1 && ++D_80109C96_hey_batter_batter == 8) {
                    D_80109C94_hey_batter_batter++;
                    break;
                }
                if (Hu3DData[object->model[3]].pos.z >= 500.0f) {
                    Hu3DModelCameraSet(object->model[3], 0);
                    D_80109C94_hey_batter_batter++;
                }
                D_80109C90_hey_batter_batter += 1.0f;
                break;
            case 2:
                if (D_80109CA4_hey_batter_batter == 1) {
                    if (D_80109CFC_hey_batter_batter == 0 || D_80109CFC_hey_batter_batter == 6) {
                        HuAudFXPlay(0x4D9);
                    } else {
                        HuAudFXPlay(0x4D2);
                    }
                    HuAudFXPlay(0x4D6);
                    D_80109C94_hey_batter_batter++;
                } else if (D_80109CA4_hey_batter_batter == 0) {
                    D_80109EDE_hey_batter_batter = 2;
                    D_80109ED4_hey_batter_batter = 2;
                    break;
                }
            case 3:
                D_80109EA0_hey_batter_batter = Hu3DData[object->model[3]].pos.x;
                D_80109EA2_hey_batter_batter = Hu3DData[object->model[3]].pos.y;
                D_80109EA4_hey_batter_batter = Hu3DData[object->model[3]].pos.z;
                Hu3DModelPosSet(object->model[3], D_80109EA0_hey_batter_batter, D_80109EA2_hey_batter_batter,
                                D_80109EA4_hey_batter_batter);
                D_80109EA6_hey_batter_batter = (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].x + rand8() % 50 -
                                                D_80109EA0_hey_batter_batter) /
                                               10.0f;
                D_80109EA8_hey_batter_batter = (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].y + rand8() % 50 -
                                                D_80109EA2_hey_batter_batter) /
                                               10.0f;
                D_80109EAA_hey_batter_batter =
                    (D_80109CA8_hey_batter_batter[D_80109CFC_hey_batter_batter].z - D_80109EA4_hey_batter_batter) / 10.0f;
                D_80109C98_hey_batter_batter = 10.0f;
                D_80109C90_hey_batter_batter = 0.0f;
                D_80109CA0_hey_batter_batter = rand8() % 200;
                D_80109C94_hey_batter_batter++;
                D_80109D00_hey_batter_batter = -2.0f;
                D_80109EAC_hey_batter_batter = 0;
            case 4:
            case 6:
                if (D_80109CFC_hey_batter_batter >= 1 && D_80109CFC_hey_batter_batter <= 5) {
                    Hu3DData[object->model[3]].pos.x += D_80109EA6_hey_batter_batter;
                    Hu3DData[object->model[3]].pos.y += D_80109EA8_hey_batter_batter;
                    Hu3DData[object->model[3]].pos.z += D_80109EAA_hey_batter_batter;
                    Hu3DData[object->model[3]].rot.x -= 50.0f;
                    if (D_80109C98_hey_batter_batter == D_80109C90_hey_batter_batter) {
                        HuAudFXPlay(0x4D3);
                        D_80109C94_hey_batter_batter++;
                        break;
                    }
                    D_80109C90_hey_batter_batter += 1.0f;
                    break;
                }
                if (D_80109EAC_hey_batter_batter == 10) {
                    D_80109EDA_hey_batter_batter = 5;
                }
                if (D_80109CFC_hey_batter_batter == 0) {
                    Hu3DData[object->model[3]].pos.z =
                        D_80109EA4_hey_batter_batter +
                        sindf(D_80109EAC_hey_batter_batter * 0.75f) * (D_80109EA4_hey_batter_batter + -1300.0f);
                } else {
                    Hu3DData[object->model[3]].pos.z =
                        D_80109EA4_hey_batter_batter +
                        sindf(D_80109EAC_hey_batter_batter * 0.75f) * (D_80109EA4_hey_batter_batter + -860.0f);
                }
                if (Hu3DData[object->model[3]].pos.y >= 0.0f) {
                    Hu3DData[object->model[3]].pos.y +=
                        D_80109D00_hey_batter_batter * D_80109D00_hey_batter_batter *
                        (D_80109D00_hey_batter_batter >= 0.0f ? -35.0f : 35.0f);
                    if (D_80109D00_hey_batter_batter >= 1.4f) {
                        D_80109D00_hey_batter_batter = 1.4f;
                    } else {
                        D_80109D00_hey_batter_batter += 0.055f;
                    }
                }
                if (D_80109EAC_hey_batter_batter == 75) {
                    Hu3DMotionSpeedSet(object->model[0], 1.0f);
                }
                if (D_80109EAC_hey_batter_batter == 80) {
                    HuAudFXPlay(0x4D4);
                    Hu3DModelCameraSet(object->model[1], 1);
                    Hu3DModelCameraSet(object->model[4], 0);
                    Hu3DModelCameraSet(object->model[3], 0);
                }
                if (D_80109EAC_hey_batter_batter++ >= 85) {
                    D_80109C94_hey_batter_batter = 5;
                    Hu3DModelCameraSet(object->model[1], 1);
                }
                break;
            case 5:
                if (D_80109CFC_hey_batter_batter >= 1 && D_80109CFC_hey_batter_batter <= 5) {
                    Hu3DModelCameraSet(object->model[3], 0);
                    Hu3DModelCameraSet(object->model[4], 0);
                    D_80109ED4_hey_batter_batter = 1;
                    D_80109EF0_hey_batter_batter = D_80109CFC_hey_batter_batter - 1;
                    D_80109EEE_hey_batter_batter = 1;
                } else {
                    D_80109ED4_hey_batter_batter = 2;
                }
                D_80109EDE_hey_batter_batter = 2;
                D_80109C94_hey_batter_batter = 0;
                D_80109C90_hey_batter_batter = 0.0f;
                break;
        }
    }
    scale = 1.0f - Hu3DData[object->model[3]].pos.y * 0.0005f;
    Hu3DModelPosSet(object->model[4], Hu3DData[object->model[3]].pos.x, 10.0f, Hu3DData[object->model[3]].pos.z);
    Hu3DModelScaleSet(object->model[4], scale, scale, scale);
}

void func_80108B48_hey_batter_batter(omObjData *object) {
    s16 i;
    HeyBatterBatterBase *base;
    s16 sprite;
    s16 model;

    for (i = 0; i < 5; i++) {
        model = Hu3DModelRead(0x5D0006, 0x6A9);
        base = &D_80109F18_hey_batter_batter[i];
        base->base = model;
        Hu3DModelPosSet(base->base, D_80109D04_hey_batter_batter[i].x,
                        D_80109D04_hey_batter_batter[i].y + 1.0f, D_80109D04_hey_batter_batter[i].z);
        base->shadow = Hu3DModelRead(0x5D0007, 0x2A9);
        Hu3DModelPosSet(base->shadow, D_80109D04_hey_batter_batter[i].x,
                        D_80109D04_hey_batter_batter[i].y, D_80109D04_hey_batter_batter[i].z);
        sprite = SprModelRead(0x21002C, 0xA0, 0x10);
        model = D_80109F2C_hey_batter_batter[i] = D_800CBB60_main[sprite].modelId;
        Hu3DSprModelPointSet(sprite, D_800A11D0_main[i]);
        Hu3DModelPosSet(model, D_80109D04_hey_batter_batter[i].x, D_80109D04_hey_batter_batter[i].y + 250.0f,
                        D_80109D04_hey_batter_batter[i].z + 2.0f);
        Hu3DModelScaleSet(model, 6.0f, 6.0f, 6.0f);
    }
    object->model[2] = Hu3DModelRead(9, 0x6A9);
    Hu3DModelCameraSet(object->model[2], 0);
    object->model[3] = EffectCreate(0xB0004, 0x6A9);
    Hu3DParticleAttrSet(object->model[3], 1, 0);
    D_80109EEE_hey_batter_batter = 0;
    object->func = func_80108D90_hey_batter_batter;
}

void func_80108D90_hey_batter_batter(omObjData *object) {
    s16 i = 0;
    f32 scale;

    if (D_80109EEE_hey_batter_batter == 1) {
        D_80109D90_hey_batter_batter = D_80109EF0_hey_batter_batter;
        D_80109D92_hey_batter_batter = D_80109F2C_hey_batter_batter[D_80109D90_hey_batter_batter];
        D_80109EEA_hey_batter_batter[0] = 1;
        for (; i < 5; i++) {
            if (i != D_80109D90_hey_batter_batter) {
                Hu3DModelCameraSet(D_80109F18_hey_batter_batter[i].base, 0);
            }
            Hu3DModelCameraSet(D_80109F2C_hey_batter_batter[i], 0);
        }
        D_80109D98_hey_batter_batter =
            SprModelRead(D_80109D40_hey_batter_batter[D_800A11D0_main[D_80109D90_hey_batter_batter]], 0xA0, 0x10);
        object->model[1] = D_800CBB60_main[D_80109D98_hey_batter_batter].modelId;
        Hu3DModelPosSet(object->model[1], Hu3DData[D_80109D92_hey_batter_batter].pos.x,
                        Hu3DData[D_80109D92_hey_batter_batter].pos.y,
                        Hu3DData[D_80109D92_hey_batter_batter].pos.z + 1.0f);
        Hu3DModelScaleSet(object->model[1], 6.0f, 6.0f, 6.0f);
        Hu3DModelCameraSet(object->model[2], 1);
        Hu3DModelPosSet(object->model[2], Hu3DData[object->model[1]].pos.x, 10.0f, Hu3DData[object->model[1]].pos.z);
        Hu3DParticleAttrSet(object->model[3], 1, 1);
        EffectParamSet(object->model[3], 5.0f, 20.0f, 10.0f);
        EffectRangeSet(object->model[3], 100.0f);
        EffectPosSet(object->model[3], Hu3DData[object->model[1]].pos.x, Hu3DData[object->model[1]].pos.y,
                           Hu3DData[object->model[1]].pos.z);
        omVibrate(D_80109ED0_hey_batter_batter, 2, 2, 20);
        D_80109EEE_hey_batter_batter = 2;
    }
    if (D_80109EEE_hey_batter_batter == 2) {
        Hu3DData[object->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 250.0f;
        if (D_80109D94_hey_batter_batter++ >= 30) {
            D_80109D94_hey_batter_batter = 0;
        }
    }
    if (D_80109EEE_hey_batter_batter == 3) {
        switch (D_80109D96_hey_batter_batter) {
            case 0:
                Hu3DData[object->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 250.0f;
                if (Hu3DData[object->model[1]].pos.y == 250.0f) {
                    D_80109D94_hey_batter_batter = 0;
                    D_80109D96_hey_batter_batter++;
                    HuAudFXPlay(0x4D7);
                }
                if (D_80109D94_hey_batter_batter++ >= 30) {
                    D_80109D94_hey_batter_batter = 0;
                }
                break;
            case 1:
                Hu3DData[object->model[1]].pos.x =
                    D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].x -
                    sindf(D_80109D94_hey_batter_batter * 3.0f) *
                        (D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].x + 150.0f);
                Hu3DData[object->model[1]].pos.y =
                    D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].y -
                    sindf(D_80109D94_hey_batter_batter * 3.0f) *
                        (D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].y - 275.0f);
                Hu3DData[object->model[1]].pos.z =
                    D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].z -
                    sindf(D_80109D94_hey_batter_batter * 3.0f) *
                        (D_80109BF4_hey_batter_batter[D_80109D90_hey_batter_batter].z - 0.0f);
                scale = 6.0f - sindf(D_80109D94_hey_batter_batter * 3.0f) * 4.0f;
                Hu3DModelScaleSet(object->model[1], scale, scale, scale);
                if (sindf(D_80109D94_hey_batter_batter * 3.0f) == 1.0f) {
                    D_80109D96_hey_batter_batter++;
                } else {
                    D_80109D94_hey_batter_batter++;
                }
                break;
            case 2:
                Hu3DData[object->model[1]].pos.y = sindf(D_80109D94_hey_batter_batter * 12.0f) * 10.0f + 275.0f;
                if (D_80109D94_hey_batter_batter++ >= 30) {
                    D_80109D94_hey_batter_batter = 0;
                }
                break;
        }
        Hu3DModelPosSet(object->model[2], Hu3DData[object->model[1]].pos.x, 10.0f, Hu3DData[object->model[1]].pos.z);
        EffectPosSet(object->model[3], Hu3DData[object->model[1]].pos.x, Hu3DData[object->model[1]].pos.y,
                           Hu3DData[object->model[1]].pos.z);
    }
}

void func_8010951C_hey_batter_batter(omObjData *object) {
    s16 i;

    object->model[0] = Hu3DModelRead(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[0], 0);
    for (i = 1; i < 6; i++) {
        object->model[i] = Hu3DModelRead(0x5D0008, 0x6A9);
        Hu3DModelCameraSet(object->model[i], 0);
    }
    object->model[6] = Hu3DModelRead(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[6], 0);
    D_80109EE6_hey_batter_batter[0] = func_80109B24_hey_batter_batter(0xB0006);
    D_80109EE6_hey_batter_batter[1] = func_80109B24_hey_batter_batter(0x5D0008);
    D_80109EEA_hey_batter_batter[0] = 0;
    D_80109EEA_hey_batter_batter[1] = 0;
    object->func = func_80109630_hey_batter_batter;
}

void func_80109630_hey_batter_batter(omObjData *object) {
    s16 i;
    s16 batter = D_80109EF0_hey_batter_batter;

    if (D_80109EEA_hey_batter_batter[0] == 1) {
        for (i = 0; i < 5; i++) {
            if (i == batter) {
                omSetTra(object, D_80109BF4_hey_batter_batter[i].x, D_80109BF4_hey_batter_batter[i].y,
                         D_80109BF4_hey_batter_batter[i].z);
                omSetSca(object, 3.0f, 3.0f, 3.0f);
                Hu3DMotionModelSet(object->model[0], D_80109EE6_hey_batter_batter[0]);
                Hu3DModelCameraSet(object->model[0], 1);
            } else {
                Hu3DModelPosSet(object->model[i + 1], D_80109BF4_hey_batter_batter[i].x,
                                D_80109BF4_hey_batter_batter[i].y, D_80109BF4_hey_batter_batter[i].z);
                Hu3DModelScaleSet(object->model[i + 1], 3.0f, 3.0f, 3.0f);
                Hu3DMotionModelSet(object->model[i + 1], D_80109EE6_hey_batter_batter[1]);
                Hu3DModelCameraSet(object->model[i + 1], 1);
            }
        }
        D_80109EDC_hey_batter_batter = 1;
        D_80109EEA_hey_batter_batter[0] = 0;
    }
    for (i = 0; i < 7; i++) {
        if (D_800CCF58_main[Hu3DData[object->model[i]].motId].unk02 == Hu3DData[object->model[i]].motTime) {
            Hu3DModelCameraSet(object->model[i], 0);
        }
    }
    if (D_80109EEA_hey_batter_batter[1] == 1) {
        Hu3DModelPosSet(object->model[6], -170.0f, 100.0f, 0.0f);
        Hu3DModelScaleSet(object->model[6], 1.0f, 1.0f, 1.0f);
        Hu3DMotionModelSet(object->model[6], D_80109EE6_hey_batter_batter[0]);
        Hu3DModelCameraSet(object->model[6], 1);
        D_80109EEA_hey_batter_batter[1] = 0;
    }
}

void func_801098DC_hey_batter_batter(f32 startZoom, Vec startRot, Vec startCenter, f32 endZoom, Vec endRot,
                                     Vec endCenter, f32 duration, f32 time) {
    f32 angle = 90.0f / duration * time;

    CZoom = startZoom - sindf(angle) * (startZoom - endZoom);
    CRot.x = startRot.x - sindf(angle) * (startRot.x - endRot.x);
    CRot.y = startRot.y - sindf(angle) * (startRot.y - endRot.y);
    CRot.z = startRot.z - sindf(angle) * (startRot.z - endRot.z);
    Center.x = startCenter.x - sindf(angle) * (startCenter.x - endCenter.x);
    Center.y = startCenter.y - sindf(angle) * (startCenter.y - endCenter.y);
    Center.z = startCenter.z - sindf(angle) * (startCenter.z - endCenter.z);
    D_80109EB4_hey_batter_batter.zoom = CZoom;
    D_80109EB4_hey_batter_batter.rot = CRot;
    D_80109EB4_hey_batter_batter.center = Center;
}

s16 func_80109A78_hey_batter_batter(s32 spriteId, u16 attr, u16 priority, s16 x, s16 y) {
    s16 espriteSlot;

    espriteSlot = espEntry(HuSprAnimDataRead(spriteId), 0, 0);
    espAttrSet(espriteSlot, attr);
    espPriSet(espriteSlot, priority);
    espPosSet(espriteSlot, x, y);
    return espriteSlot;
}

s16 func_80109B24_hey_batter_batter(s32 arg0) {
    s16 temp = Hu3DMotionModelRead(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}
