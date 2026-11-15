#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "game/overlays/minigame.h"

extern s32 D_800A178C_main[][6];
extern f32 CFanOfs;
extern u8 storySceneNo;
extern u8 Hu3DBufNo;
extern f32 CFanLen;
extern u8 omAllPauseF;

Vec D_80109740_dizzy_dinghies[3] = {
    { 4500.0f, 0.0f, 7300.0f },
    { 6500.0f, 0.0f, 2300.0f },
    { 5500.0f, 0.0f, 6300.0f },
};
f32 D_80109764_dizzy_dinghies = 180.0f; /* Unreferenced. */
f32 D_80109768_dizzy_dinghies = 180.0f;
f32 D_8010976C_dizzy_dinghies = 0.0f; /* Unreferenced. */
f32 D_80109770_dizzy_dinghies = 80.0f;
f32 D_80109774_dizzy_dinghies = 1.1f;
f32 D_80109778_dizzy_dinghies = 0.975f;
f32 D_8010977C_dizzy_dinghies = 0.925f; /* Unreferenced. */
f32 D_80109780_dizzy_dinghies = 0.925f;
f32 D_80109784_dizzy_dinghies = 0.775f;
Vec D_80109788_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
Vec D_80109794_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
Vec D_801097A0_dizzy_dinghies = { 0.0f, 0.0f, 0.0f };
f32 D_801097AC_dizzy_dinghies = 0.0f;
f32 D_801097B0_dizzy_dinghies = 0.1f;
f32 D_801097B4_dizzy_dinghies = 0.0f;
f32 D_801097B8_dizzy_dinghies = 0.2f;
f32 D_801097BC_dizzy_dinghies = 50.0f;
f32 D_801097C0_dizzy_dinghies = 55.0f;
f32 D_801097C4_dizzy_dinghies = 0.0f;
f32 D_801097C8_dizzy_dinghies = 0.13f;
f32 D_801097CC_dizzy_dinghies = 40.0f;
f32 D_801097D0_dizzy_dinghies = 40.0f;
s32 D_801097D4_dizzy_dinghies = 0;
f32 D_801097D8_dizzy_dinghies = 0.0f;
f32 D_801097DC_dizzy_dinghies = 0.0f;
f32 D_801097E0_dizzy_dinghies = 300.0f;
f32 D_801097E4_dizzy_dinghies = 2.0f;
s32 D_801097E8_dizzy_dinghies = -1;
s32 D_801097EC_dizzy_dinghies = 0;
Vec D_801097F0_dizzy_dinghies[17] = {
    { 3800.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 7200.0f },
    { 5200.0f, 112.5f, 4600.0f },
    { 3700.0f, 112.5f, 2700.0f },
    { 4600.0f, 112.5f, -900.0f },
    { 3500.0f, 112.5f, -2800.0f },
    { 5900.0f, 112.5f, -7100.0f },
    { 1600.0f, 112.5f, -8400.0f },
    { -1100.0f, 112.5f, -9100.0f },
    { -3400.0f, 112.5f, -8400.0f },
    { -5200.0f, 112.5f, -9400.0f },
    { -4500.0f, 112.5f, -3600.0f },
    { -3600.0f, 112.5f, -1300.0f },
    { -4700.0f, 112.5f, 600.0f },
    { -3700.0f, 112.5f, 3100.0f },
    { -5200.0f, 112.5f, 7300.0f },
    { -3800.0f, 112.5f, 7200.0f },
};
Vec D_801098BC_dizzy_dinghies[17] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 225.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
};
s8 D_80109988_dizzy_dinghies[18] = { 0, 0, 1, 2, 1, 1, 0, 1, 2, 1, 0, 1, 2, 1, 2, 0, 0, -1 };
Vec D_8010999C_dizzy_dinghies[19] = {
    { 5800.0f, 112.5f, 2100.0f },
    { 7200.0f, 112.5f, 2100.0f },
    { 5700.0f, 112.5f, -1000.0f },
    { 7200.0f, 112.5f, -3500.0f },
    { 6600.0f, 112.5f, -7000.0f },
    { 1900.0f, 112.5f, -6200.0f },
    { 4500.0f, 112.5f, -5700.0f },
    { 3200.0f, 112.5f, -900.0f },
    { 1500.0f, 112.5f, 3700.0f },
    { 200.0f, 112.5f, 0.0f },
    { 900.0f, 112.5f, -2100.0f },
    { 1300.0f, 112.5f, -7400.0f },
    { -2700.0f, 112.5f, -9200.0f },
    { -5400.0f, 112.5f, -7900.0f },
    { -3300.0f, 112.5f, -4200.0f },
    { -3500.0f, 112.5f, -2000.0f },
    { -1900.0f, 112.5f, 300.0f },
    { -3200.0f, 112.5f, 5300.0f },
    { -1800.0f, 112.5f, 5200.0f },
};
Vec D_80109A80_dizzy_dinghies[19] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 180.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};
s8 D_80109B64_dizzy_dinghies[20] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 2, 1, 0, 2, 0, 1, 0, 0, -1 };
Vec D_80109B78_dizzy_dinghies[18] = {
    { 4600.0f, -150.0f, 6200.0f },
    { 6400.0f, -150.0f, 6200.0f },
    { 5300.0f, -150.0f, 1000.0f },
    { 7200.0f, 0.0f, -4000.0f },
    { 3000.0f, -150.0f, -6800.0f },
    { 2100.0f, -150.0f, -1700.0f },
    { 2600.0f, -150.0f, 2300.0f },
    { 2100.0f, 0.0f, 7200.0f },
    { -300.0f, -150.0f, 8200.0f },
    { -2800.0f, -150.0f, 8000.0f },
    { -3600.0f, -150.0f, 4600.0f },
    { -4600.0f, 0.0f, 200.0f },
    { -800.0f, 0.0f, -3800.0f },
    { -1500.0f, -150.0f, -7000.0f },
    { -6200.0f, -150.0f, -3600.0f },
    { -5400.0f, -150.0f, -200.0f },
    { -7500.0f, -150.0f, 3900.0f },
    { -5500.0f, -150.0f, 3900.0f },
};
Vec D_80109C50_dizzy_dinghies[18] = {
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { -40.0f, 320.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { -40.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f },
    { 0.0f, 320.0f, 0.0f },
};
s8 D_80109D28_dizzy_dinghies[19] = { 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, -1 };
MinigameFlow D_80109D3C_dizzy_dinghies = {
    MG_STATE_OPENING, 7, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_RECORD, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    75, -1, 5400, 90, 135
};
Vec D_80109D64_dizzy_dinghies = { 101.0f, -51.0f, 38.0f }; /* Unreferenced. */
f32 D_80109D70_dizzy_dinghies = -2000.0f;
f32 D_80109D74_dizzy_dinghies = -20.0f;
f32 D_80109D78_dizzy_dinghies = -90.0f;
f32 D_80109D7C_dizzy_dinghies = 20.0f;
f32 D_80109D80_dizzy_dinghies = 5.0f;
s32 D_80109D84_dizzy_dinghies[3][3] = {
    { 0x000A0000, 0x000A008E, 0x000A00A5 },
    { 0x000A00C3, 0x000A00E7, 0x000A00CE },
    { 0x000A0086, 0x000A0059, 0x000A0154 },
};
s32 D_80109DA8_dizzy_dinghies[3][3] = {
    { 0x000A0017, 0x000A0095, 0x000A00B2 },
    { 0x000A00BC, 0x000A00ED, 0x000A00D0 },
    { 0x000A0088, 0x000A005A, 0x000A0154 },
};

Vec D_80109F60_dizzy_dinghies[6] BSS;
f32 D_80109FA8_dizzy_dinghies[6] BSS;
Vec D_80109FC0_dizzy_dinghies[6] BSS;
f32 D_8010A008_dizzy_dinghies[6] BSS;
s32 D_8010A020_dizzy_dinghies BSS;
u8 D_8010A024_dizzy_dinghies[4] BSS; /* Unreferenced. */
Vec D_8010A028_dizzy_dinghies[20] BSS;
s32 D_8010A118_dizzy_dinghies BSS;
s32 D_8010A11C_dizzy_dinghies BSS;
u8 D_8010A120_dizzy_dinghies[0x30] BSS; /* Unreferenced. */

void func_80105CAC_dizzy_dinghies(omObjData *object);
void func_80105EB4_dizzy_dinghies(omObjData *object);
void func_80106970_dizzy_dinghies(omObjData *object);
void func_80106DF4_dizzy_dinghies(omObjData *object);
void func_80107098_dizzy_dinghies(omObjData *object);
void func_80107738_dizzy_dinghies(omObjData *object, u16 player);
void func_80107DE8_dizzy_dinghies(omObjData *object);
void func_801085F4_dizzy_dinghies(omObjData *object);
void func_80108EC4_dizzy_dinghies(omObjData *object, f32 x, f32 z);
f32 func_80109238_dizzy_dinghies(omObjData *object, f32 x, f32 y, f32 z);
void func_801095D4_dizzy_dinghies(omObjData *object);
void func_80109420_dizzy_dinghies(omObjData *object);
void func_80108E30_dizzy_dinghies(Vec *origin, Vec *p, Vec *q, Vec *out);

void func_801059A0_dizzy_dinghies(void) {
    u8 camIndex;

    MapCollInit(50);
    Hu3DQuadPoolInit(&D_800EBEB0_minigame, 0x40);
    Hu3DSprModelInit(32);
    omInitObjMan(50, 0);
    omGameSysInit();
    func_800E1804_minigame();
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 8000.0f);
    CFanLen = 20000.0f;
    CFanOfs = 12000.0f;
    Hu3DBGColorSet(0, 0, 64);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(1, -98.0f, 14.0f, 66.0f);
    Hu3DGLightDirSet(2, -84.0f, 83.0f, 12.0f);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightColorSet(2, 230, 230, 230);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 40, 0, -1, func_80107098_dizzy_dinghies);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 13, 0, -1, func_80107DE8_dizzy_dinghies);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(4, 0, 0, -1, func_80105CAC_dizzy_dinghies), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(100, 0, 0, -1, func_80109420_dizzy_dinghies), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_80109D3C_dizzy_dinghies);
    D_800EB930_minigame = 50;
    D_800EB932_minigame = 72;
    D_801097EC_dizzy_dinghies = storySceneNo;
}

void func_80105CAC_dizzy_dinghies(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work = D_800EC598_minigame[0]->data;
    f32 angle = work->unk3C;
    f32 dist = D_801097B0_dizzy_dinghies * 100.0f + D_801097E0_dizzy_dinghies + work->unk40 * 2.0f;

    Center.x = D_800EC598_minigame[0]->trans.x + sindf(angle) * dist;
    Center.y = 0.0f;
    Center.z = D_800EC598_minigame[0]->trans.z + cosdf(angle) * dist;
}

void func_80105D64_dizzy_dinghies(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

f32 func_80105D90_dizzy_dinghies(f32 x, f32 z) {
    f32 height;

    height = sindf((D_801097B4_dizzy_dinghies / D_801097B8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097BC_dizzy_dinghies) *
                   (2 * M_PI)) *
             D_801097C0_dizzy_dinghies;
    x += 8000.0f;
    z += 5000.0f;
    height += sindf((D_801097C4_dizzy_dinghies / D_801097C8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097CC_dizzy_dinghies) *
                    (2 * M_PI)) *
              D_801097D0_dizzy_dinghies;
    return height / 2.0f;
}

void func_80105EB4_dizzy_dinghies(omObjData *object) {
    HmfData *hmf;
    Vtx *vtx;
    Vtx *src;
    f32 boatX;
    f32 boatZ;
    f32 x, z;
    f32 height;
    s32 i;

    boatX = D_800EC598_minigame[0]->trans.x;
    boatZ = D_800EC598_minigame[0]->trans.z;
    hmf = Hu3DData[object->model[1]].hmf;
    vtx = hmf->unk44[Hu3DBufNo];
    src = hmf->unk40;
    for (i = 0; i < hmf->unk18; i++, vtx++, src++) {
        x = src->v.ob[0] + boatX;
        z = src->v.ob[2] + boatZ;
        height = sindf((D_801097B4_dizzy_dinghies / D_801097B8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097BC_dizzy_dinghies) *
                       (2 * M_PI)) *
                 D_801097C0_dizzy_dinghies;
        x += 8000.0f;
        z += 5000.0f;
        height = (height + sindf((D_801097C4_dizzy_dinghies / D_801097C8_dizzy_dinghies - HuSqrtf(x * x + z * z) / D_801097CC_dizzy_dinghies) *
                                 (2 * M_PI)) *
                               D_801097D0_dizzy_dinghies) /
                 2.0f;
        vtx->v.ob[1] = height;
        if (height > 0.0) {
            height = 256.0f - height;
            vtx->v.cn[1] = vtx->v.cn[0] = 170;
            vtx->v.cn[2] = height;
        } else {
            height = 175.0f - height;
            if (height > 255.0f) {
                height = 255.0f;
            }
            vtx->v.cn[0] = height;
            vtx->v.cn[1] = height;
            vtx->v.cn[2] = 255;
        }
    }
    if (omPauseChk() + omAllPauseF == 0) {
        D_801097B4_dizzy_dinghies += 0.11f;
        D_801097C4_dizzy_dinghies += 0.09f;
        Hu3DModelPosSet(object->model[1], boatX, 0.0f, boatZ);
    }
    Hu3DModelTexScroll(object->model[1], D_801097D8_dizzy_dinghies, D_801097DC_dizzy_dinghies, 32, 32);
    if (HuPadBtn[1] & 8) {
        D_801097B8_dizzy_dinghies += 0.001f;
    }
    if (HuPadBtn[1] & 4) {
        D_801097B8_dizzy_dinghies -= 0.001f;
    }
    if (D_801097B8_dizzy_dinghies < 0.01f) {
        D_801097B8_dizzy_dinghies = 0.01f;
    }
    if (HuPadBtn[1] & 1) {
        D_801097BC_dizzy_dinghies += 0.1f;
    }
    if (HuPadBtn[1] & 2) {
        D_801097BC_dizzy_dinghies -= 0.1f;
    }
    if (HuPadBtn[1] & 0x10) {
        D_801097C0_dizzy_dinghies -= 0.1f;
    }
    if (HuPadBtn[1] & 0x20) {
        D_801097C0_dizzy_dinghies += 0.1f;
    }
    D_801097C8_dizzy_dinghies = D_801097B8_dizzy_dinghies - 0.3f;
    D_801097CC_dizzy_dinghies = D_801097BC_dizzy_dinghies - 5.0f;
    D_801097D0_dizzy_dinghies = D_801097C0_dizzy_dinghies - 20.0f;
}

void func_80106494_dizzy_dinghies(void) {
    omObjData *obj;

    if (D_801097D4_dizzy_dinghies == 1) {
        obj = D_800EC598_minigame[0];
        Center.x -= (Center.x - obj->trans.x) * 0.25f;
        Center.z -= (Center.z - obj->trans.z) * 0.25f;
        Center.y -= (Center.y - obj->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

void func_8010655C_dizzy_dinghies(omObjData *object) {
    f32 x, y, z;
    s32 time;

    x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 400.0f + D_80109D70_dizzy_dinghies;
    y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f;
    z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    Hu3DModelPosSet(object->model[3], x, y, z);
    x += cosdf(D_80109D74_dizzy_dinghies + 90.0f) * 77.65f;
    Hu3DModelPosSet(object->model[2], x, y + sindf(D_80109D74_dizzy_dinghies + 90.0f) * 77.65f, z + 140.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, 0.0f, D_80109D74_dizzy_dinghies);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, sindf(D_80109D78_dizzy_dinghies) * D_80109D7C_dizzy_dinghies);
    D_80109D70_dizzy_dinghies *= 0.9f;
    if (D_80109D70_dizzy_dinghies > -300.0f) {
        D_80109D78_dizzy_dinghies += 10.0f;
        D_80109D7C_dizzy_dinghies *= 0.98f;
        D_80109D74_dizzy_dinghies *= 0.8f;
    }
    time = func_800E6E9C_minigame();
    if (MgFlowStatGet() == MG_STATE_OPENING) {
        if (time == 60) {
            Hu3DMotionAttrSet(object->model[2], 1, 0);
        }
    } else if (time == 15.0 || time == 45.0) {
        HuAudFXPlay(0x426);
    }
}

void func_80106818_dizzy_dinghies(omObjData *object) {
    f32 x, y, z;

    if (D_80109D80_dizzy_dinghies < 2000.0f) {
        x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 400.0f;
        y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f + D_80109D80_dizzy_dinghies;
        z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
        D_80109D80_dizzy_dinghies *= 1.15f;
        Hu3DModelPosSet(object->model[3], x, y, z);
        Hu3DModelPosSet(object->model[2], x, y + 77.65f, z + 140.0f);
    } else {
        Hu3DModelAttrSet(object->model[3], 4, 4);
        Hu3DModelAttrSet(object->model[2], 4, 4);
    }
}

void func_80106970_dizzy_dinghies(omObjData *object) {
    f32 x, y, z;
    f32 rotX, rotY, rotZ;
    f32 dx, dz;
    f32 scale;
    s32 type;
    s32 count0;
    s32 count1;
    s32 count2;
    s32 i;

    count2 = 0;
    count1 = 0;
    count0 = 0;
    for (i = 0; i < 30; i++) {
        Hu3DModelAttrSet(object->model[i + 9], 4, 4);
    }
    for (i = 0;; i++) {
        switch (D_801097EC_dizzy_dinghies) {
            case 0:
                type = D_80109988_dizzy_dinghies[i];
                x = D_801097F0_dizzy_dinghies[i].x;
                y = D_801097F0_dizzy_dinghies[i].y;
                z = D_801097F0_dizzy_dinghies[i].z;
                rotX = D_801098BC_dizzy_dinghies[i].x;
                rotY = D_801098BC_dizzy_dinghies[i].y;
                rotZ = D_801098BC_dizzy_dinghies[i].z;
                break;
            case 1:
                type = D_80109B64_dizzy_dinghies[i];
                x = D_8010999C_dizzy_dinghies[i].x;
                y = D_8010999C_dizzy_dinghies[i].y;
                z = D_8010999C_dizzy_dinghies[i].z;
                rotX = D_80109A80_dizzy_dinghies[i].x;
                rotY = D_80109A80_dizzy_dinghies[i].y;
                rotZ = D_80109A80_dizzy_dinghies[i].z;
                break;
            case 2:
                type = D_80109D28_dizzy_dinghies[i];
                x = D_80109B78_dizzy_dinghies[i].x;
                y = D_80109B78_dizzy_dinghies[i].y;
                z = D_80109B78_dizzy_dinghies[i].z;
                rotX = D_80109C50_dizzy_dinghies[i].x;
                rotY = D_80109C50_dizzy_dinghies[i].y;
                rotZ = D_80109C50_dizzy_dinghies[i].z;
                break;
        }
        if (type == -1) {
            break;
        }
        dx = Center.x - x;
        dz = Center.z - z;
        if (HuSqrtf(dx * dx + dz * dz) < 2500.0f) {
            switch (type) {
                case 0:
                    if (count0 < 5) {
                        Hu3DModelPosSet(object->model[count0 + 9], x, y, z);
                        Hu3DModelRotSet(object->model[count0 + 9], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count0 + 9], 1.5f, 1.5f, 1.5f);
                        Hu3DModelAttrSet(object->model[count0 + 9], 4, 0);
                        count0++;
                    }
                    break;
                case 1:
                    if (count1 < 5) {
                        Hu3DModelPosSet(object->model[count1 + 19], x, y, z);
                        Hu3DModelRotSet(object->model[count1 + 19], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count1 + 19], 1.5f, 1.5f, 1.5f);
                        Hu3DModelAttrSet(object->model[count1 + 19], 4, 0);
                        count1++;
                    }
                    break;
                case 2:
                    if (count2 < 5) {
                        if (D_801097EC_dizzy_dinghies == 1) {
                            scale = 0.8f;
                        } else {
                            scale = 1.5f;
                        }
                        Hu3DModelPosSet(object->model[count2 + 29], x, y, z);
                        Hu3DModelRotSet(object->model[count2 + 29], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count2 + 29], scale, scale, scale);
                        Hu3DModelAttrSet(object->model[count2 + 29], 4, 0);
                        count2++;
                    }
                    break;
            }
        }
    }
}

void func_80106DF4_dizzy_dinghies(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work;
    s32 time;
    s32 i;

    func_80105EB4_dizzy_dinghies(object);
    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    time = func_800E6E9C_minigame();
    switch (MgFlowMain()) {
        case 0:
            if (time == 5) {
                HuAudFXPlay(0x424);
                D_801097E8_dizzy_dinghies = HuAudPlayerFXPlay(D_8010A020_dizzy_dinghies + 0x428, 0);
            }
        case 1:
            func_8010655C_dizzy_dinghies(object);
            break;
        case 2:
            if (time == 0) {
                HuAudFXPlay(0x427);
            }
            func_80106818_dizzy_dinghies(object);
            break;
        case 3:
            if (time == 15.0) {
                HuAudFXFadeOut(D_801097E8_dizzy_dinghies, 30);
                D_801097E8_dizzy_dinghies = -1;
            }
            if (time == 1) {
                D_80109778_dizzy_dinghies -= 0.025f;
            }
            D_801097E0_dizzy_dinghies *= 0.95f;
            D_80109D3C_dizzy_dinghies.resultType = MG_RESULT_NONE;
        case 4:
            if (D_800EB934_minigame == 1) {
                if (D_801097D4_dizzy_dinghies == 0) {
                    HuAudSeqPlay(0x6B);
                } else if (D_80109D3C_dizzy_dinghies.newRecord == TRUE) {
                    HuAudSeqPlay(0x6A);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_80105D64_dizzy_dinghies;
            HuAudFXAllFadeOut(30);
            break;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        work = D_800EC598_minigame[i]->data;
        work->unk60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = func_80105D64_dizzy_dinghies;
    }
    func_80106970_dizzy_dinghies(object);
}

void func_80107098_dizzy_dinghies(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;
    s16 motion;

    object->model[0] = Hu3DModelRead2((D_801097EC_dizzy_dinghies + 3) | 0x670000, 0x4B9);
    object->model[1] = Hu3DModelRead2(0x670006, 0x4A9);
    object->model[2] = Hu3DModelRead2(0x670007, 0x8C9);
    object->model[3] = Hu3DModelRead2(0xA0089, 0x8C9);
    object->model[9] = Hu3DModelRead2(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][0], 0x4DD);
    object->model[10] = Hu3DModelLink(object->model[9]);
    object->model[11] = Hu3DModelLink(object->model[9]);
    object->model[12] = Hu3DModelLink(object->model[9]);
    motion = Hu3DMotionModelRead(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][0]);
    Hu3DMotionModelSet(object->model[9], motion);
    Hu3DMotionModelSet(object->model[10], motion);
    Hu3DMotionModelSet(object->model[11], motion);
    Hu3DMotionModelSet(object->model[12], motion);
    Hu3DMotionAttrSet(object->model[9], 2, 2);
    Hu3DMotionAttrSet(object->model[10], 2, 2);
    Hu3DMotionAttrSet(object->model[11], 2, 2);
    Hu3DMotionAttrSet(object->model[12], 2, 2);
    object->model[19] = Hu3DModelRead2(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][1], 0x4DD);
    object->model[20] = Hu3DModelLink(object->model[19]);
    object->model[21] = Hu3DModelLink(object->model[19]);
    object->model[22] = Hu3DModelLink(object->model[19]);
    motion = Hu3DMotionModelRead(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][1]);
    Hu3DMotionModelSet(object->model[19], motion);
    Hu3DMotionModelSet(object->model[20], motion);
    Hu3DMotionModelSet(object->model[21], motion);
    Hu3DMotionModelSet(object->model[22], motion);
    Hu3DMotionAttrSet(object->model[19], 2, 2);
    Hu3DMotionAttrSet(object->model[20], 2, 2);
    Hu3DMotionAttrSet(object->model[21], 2, 2);
    Hu3DMotionAttrSet(object->model[22], 2, 2);
    object->model[29] = Hu3DModelRead2(D_80109D84_dizzy_dinghies[D_801097EC_dizzy_dinghies][2], 0x4DD);
    object->model[30] = Hu3DModelLink(object->model[29]);
    object->model[31] = Hu3DModelLink(object->model[29]);
    object->model[32] = Hu3DModelLink(object->model[29]);
    motion = Hu3DMotionModelRead(D_80109DA8_dizzy_dinghies[D_801097EC_dizzy_dinghies][2]);
    Hu3DMotionModelSet(object->model[29], motion);
    Hu3DMotionModelSet(object->model[30], motion);
    Hu3DMotionModelSet(object->model[31], motion);
    Hu3DMotionModelSet(object->model[32], motion);
    Hu3DMotionAttrSet(object->model[29], 2, 2);
    Hu3DMotionAttrSet(object->model[30], 2, 2);
    Hu3DMotionAttrSet(object->model[31], 2, 2);
    Hu3DMotionAttrSet(object->model[32], 2, 2);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    object->func = func_80106DF4_dizzy_dinghies;
    work->unk03 = 1;
    Center.x = -224.0f;
    Center.y = 300.0f;
    Center.z = 300.0f;
    CRot.x = 330.0f;
    CRot.y = 5.0f;
    CZoom = 4500.0f;
    func_800E147C_minigame(object);
    func_800E1370_minigame(object, 1, 0.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 25.0f);
    work->unk04 = 0;
    Hu3DLLightCreate(object->model[1], 1);
    Hu3DLLightDirSet(object->model[1], -66.0f, -99.0f, -9.0f);
    Hu3DModelObjAttrSet(object->model[1], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[1]);
    Hu3DModelVtxBufMake(object->model[1]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DModelPosSet(object->model[2], D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 500.0f,
                    D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f,
                    D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z);
    Hu3DModelPosSet(object->model[3], D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x + 500.0f,
                    D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y + 500.0f,
                    D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DMotionAttrSet(object->model[2], 1, 1);
    Hu3DMotionAttrSet(object->model[3], 2, 2);
}

// Defined here (not at the top) so that the initialiser strings are emitted into
// .rodata after the preceding functions' constants, matching the original layout.
char *D_80109DCC_dizzy_dinghies[11] = {
    "atama_2",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "c003_000-head_1",
    "Luigi1-atama_1",
    "c005_000-bmerge1",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "atama_2",
    "atama_2",
    "atama_2",
};
s8 D_80109DF8_dizzy_dinghies[4] = { -1, -1, -1, -1 };
s16 D_80109DFC_dizzy_dinghies = -1;
s16 D_80109DFE_dizzy_dinghies = -1;
s16 D_80109E00_dizzy_dinghies = -1;
s32 D_80109E04_dizzy_dinghies = 0;
s16 D_80109E08_dizzy_dinghies[20] = { 0 };
s32 D_80109E30_dizzy_dinghies = 0;
s32 D_80109E34_dizzy_dinghies = 0;
f32 D_80109E38_dizzy_dinghies = 1.0f; /* Unreferenced. */
s32 D_80109E3C_dizzy_dinghies = 0;
s32 D_80109E40_dizzy_dinghies = -1;
Vec D_80109E44_dizzy_dinghies[3][3] = {
    { { -4000.0f, 100.0f, 7000.0f }, { -5000.0f, 100.0f, 7000.0f }, { 0.0f, -500.0f, 7000.0f } },
    { { -2000.0f, 100.0f, 5000.0f }, { -3000.0f, 100.0f, 5000.0f }, { 0.0f, -500.0f, 5000.0f } },
    { { -5800.0f, 100.0f, 4000.0f }, { -7200.0f, 100.0f, 4000.0f }, { 0.0f, -500.0f, 4000.0f } },
};

void func_80107738_dizzy_dinghies(omObjData *object, u16 player) {
    func_800E1BA8_minigame_ObjData *work;
    s32 tag;
    s32 charModel;
    s32 model;
    s32 motion;
    s32 boatType;
    s32 i;

    tag = 0x6D9;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    work = object->data;
    motion = D_800A178C_main[GwPlayer[player].chr][2];
    model = D_800A178C_main[GwPlayer[player].chr][0];
    charModel = Hu3DModelRead(model | motion, tag | 4);
    D_8010A020_dizzy_dinghies = boatType = mgModeCoinRate;
    object->model[0] = Hu3DModelRead(boatType | 0x670000, tag);
    Hu3DModelObjCopy(charModel, D_80109DCC_dizzy_dinghies[GwPlayer[player].chr], object->model[0],
                       "atama_2");
    switch (boatType) {
        case 0:
            D_80109770_dizzy_dinghies = 80.0f;
            D_80109774_dizzy_dinghies = 1.1f;
            D_80109778_dizzy_dinghies = 0.975f;
            D_80109780_dizzy_dinghies = 0.925f;
            D_80109784_dizzy_dinghies = 0.775f;
            break;
        case 1:
            D_80109770_dizzy_dinghies = 85.0f;
            D_80109774_dizzy_dinghies = 1.025f;
            D_80109778_dizzy_dinghies = 0.97f;
            D_80109780_dizzy_dinghies = 0.92f;
            D_80109784_dizzy_dinghies = 0.76f;
            break;
        case 2:
        default:
            D_80109770_dizzy_dinghies = 90.0f;
            D_80109774_dizzy_dinghies = 1.0125f;
            D_80109778_dizzy_dinghies = 0.96f;
            D_80109780_dizzy_dinghies = 0.9125f;
            D_80109784_dizzy_dinghies = 0.75f;
            break;
    }
    work->unk57 = GwPlayer[player].pad;
    object->func = func_801085F4_dizzy_dinghies;
    work->unk52 = 0;
    work->unkB4 = 1.0f;
    work->unk8C = 65536.0f;
    work->unkD0 = 0xFFFF;
    work->unk4C = 0.5f;
    work->unkCC = 1.0f;
    work->unk60 = 0.0f;
    func_800E1328_minigame(object, 100.0f);
    func_800E1334_minigame(object, 150.0f);
    func_800E1340_minigame(object, 20.0f);
    func_800E134C_minigame(object, 30.0f);
    func_800E12EC_minigame(object, 1000.0f);
    work->unk9C = work->unkA0 = work->unkA4 = 0.0f;
    work->unk59 = player;
    work->unkC3 = -1;
    work->unkC4 = -1;
    work->unkAC = work->unkB0 = 1.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (D_80109DFC_dizzy_dinghies < 0) {
                object->model[i + 1] = D_80109DFC_dizzy_dinghies = Hu3DModelRead(0x440006, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_80109DFC_dizzy_dinghies);
            }
        } else if (i == 4 || i == 1) {
            if (D_80109DFE_dizzy_dinghies < 0) {
                object->model[i + 1] = D_80109DFE_dizzy_dinghies = Hu3DModelRead(0x440007, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_80109DFE_dizzy_dinghies);
            }
        } else {
            if (D_80109E00_dizzy_dinghies < 0) {
                object->model[i + 1] = D_80109E00_dizzy_dinghies = Hu3DModelRead(0x440008, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_80109E00_dizzy_dinghies);
            }
        }
        Hu3DModelObjAttrSet(object->model[i + 1], 0x70000000, 0x70000000);
    }
    if (boatType == 2) {
        for (i = 0; i < 6; i++) {
            if (i == 3 || i == 0) {
                object->model[i + 7] = Hu3DModelLink(D_80109DFC_dizzy_dinghies);
            } else if (i == 4 || i == 1) {
                object->model[i + 7] = Hu3DModelLink(D_80109DFE_dizzy_dinghies);
            } else {
                object->model[i + 7] = Hu3DModelLink(D_80109E00_dizzy_dinghies);
            }
            Hu3DModelObjAttrSet(object->model[i + 7], 0x70000000, 0x70000000);
        }
    }
    work = object->data;
    work->unk3C = D_80109768_dizzy_dinghies;
    func_800E149C_minigame(object, 0, 2);
    do {
        i = rand8() & 3;
    } while (D_80109DF8_dizzy_dinghies[i] != -1);
    object->trans.x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x;
    object->trans.y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y;
    object->trans.z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    Center.x = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].x;
    Center.y = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].y;
    Center.z = D_80109740_dizzy_dinghies[D_801097EC_dizzy_dinghies].z;
    Hu3DMotionTimeSet(object->model[0], 5.0f);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    switch (GwPlayer[player].chr) {
        case 2:
        case 6:
        case 7:
            D_801097E4_dizzy_dinghies = 3.0f;
            break;
        case 4:
            D_801097E4_dizzy_dinghies = 1.8f;
            break;
    }
}

void func_80107DE8_dizzy_dinghies(omObjData *object) {
    func_80107738_dizzy_dinghies(object, 0);
}

void func_80107E04_dizzy_dinghies(omObjData *object, f32 speed) {
    f32 angle;
    f32 offset;
    f32 backAngle;
    f32 scale;
    f32 leftX, leftZ;
    f32 rightX, rightZ;
    s32 idx;
    s32 i;

    angle = ((func_800E1BA8_minigame_ObjData *)object->data)->unk3C;
    idx = D_80109E04_dizzy_dinghies + 1;
    idx = (idx != 6) ? idx : 0;
    D_80109E04_dizzy_dinghies = idx;
    D_8010A008_dizzy_dinghies[idx] = 1.0f;
    D_80109FA8_dizzy_dinghies[idx] = speed * 10.0f;
    offset = (rand8() - 128) / 4;
    D_80109F60_dizzy_dinghies[idx].x = sindf(angle + 180.0f) * 150.0f + object->trans.x + sindf(angle + 90.0f) + offset;
    D_80109F60_dizzy_dinghies[idx].y = object->trans.y;
    D_80109F60_dizzy_dinghies[idx].z = cosdf(angle + 180.0f) * 150.0f + object->trans.z + sindf(angle + 90.0f) + offset;
    offset = (rand8() - 128) / 4;
    backAngle = angle + 180.0f + offset;
    D_80109FC0_dizzy_dinghies[idx].x = sindf(backAngle);
    D_80109FC0_dizzy_dinghies[idx].z = cosdf(backAngle);
    if (D_8010A020_dizzy_dinghies == 2) {
        for (i = 0; i < 6; i++) {
            if (D_80109FA8_dizzy_dinghies[i] > 0.0f) {
                leftX = sindf(angle + 90.0f) * 60.0f;
                leftZ = cosdf(angle + 90.0f) * 60.0f;
                rightX = sindf(angle + 90.0f) * -60.0f;
                rightZ = cosdf(angle + 90.0f) * -60.0f;
                D_80109F60_dizzy_dinghies[i].x += D_80109FC0_dizzy_dinghies[i].x * D_80109FA8_dizzy_dinghies[i] * speed;
                D_80109F60_dizzy_dinghies[i].y -= 20.0f;
                D_80109F60_dizzy_dinghies[i].z += D_80109FC0_dizzy_dinghies[i].z * D_80109FA8_dizzy_dinghies[i] * speed;
                D_8010A008_dizzy_dinghies[i] *= 1.3f;
                scale = speed * D_8010A008_dizzy_dinghies[i];
                Hu3DModelPosSet(object->model[i + 1], leftX + D_80109F60_dizzy_dinghies[i].x,
                                D_80109F60_dizzy_dinghies[i].y, leftZ + D_80109F60_dizzy_dinghies[i].z);
                Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 1], 4, 0);
                Hu3DModelPosSet(object->model[i + 7], rightX + D_80109F60_dizzy_dinghies[i].x,
                                D_80109F60_dizzy_dinghies[i].y, rightZ + D_80109F60_dizzy_dinghies[i].z);
                Hu3DModelScaleSet(object->model[i + 7], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 7], 4, 0);
            } else {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
                Hu3DModelAttrSet(object->model[i + 7], 4, 4);
            }
        }
    } else {
        for (i = 0; i < 6; i++) {
            if (D_80109FA8_dizzy_dinghies[i] > 0.0f) {
                D_80109F60_dizzy_dinghies[i].x += D_80109FC0_dizzy_dinghies[i].x * D_80109FA8_dizzy_dinghies[i] * speed;
                D_80109F60_dizzy_dinghies[i].y -= 20.0f;
                D_80109F60_dizzy_dinghies[i].z += D_80109FC0_dizzy_dinghies[i].z * D_80109FA8_dizzy_dinghies[i] * speed;
                Hu3DModelPosSet(object->model[i + 1], D_80109F60_dizzy_dinghies[i].x, D_80109F60_dizzy_dinghies[i].y,
                                D_80109F60_dizzy_dinghies[i].z);
                D_8010A008_dizzy_dinghies[i] *= 1.3f;
                scale = speed * D_8010A008_dizzy_dinghies[i];
                Hu3DModelScaleSet(object->model[i + 1], scale, scale, scale);
                Hu3DModelAttrSet(object->model[i + 1], 4, 0);
            } else {
                Hu3DModelAttrSet(object->model[i + 1], 4, 4);
            }
        }
    }
}

s32 func_80108488_dizzy_dinghies(s32 player, s16 value) {
    s32 sum;
    u8 i;

    D_80109E08_dizzy_dinghies[D_80109E34_dizzy_dinghies] = value;
    if (++D_80109E34_dizzy_dinghies >= 20) {
        D_80109E34_dizzy_dinghies = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += D_80109E08_dizzy_dinghies[i];
    }
    return sum / 20;
}

void func_80108514_dizzy_dinghies(s32 player, f32 speed, Vec *out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    D_8010A028_dizzy_dinghies[D_80109E30_dizzy_dinghies].x = D_80109788_dizzy_dinghies.x;
    D_8010A028_dizzy_dinghies[D_80109E30_dizzy_dinghies].z = D_80109788_dizzy_dinghies.z;
    if (++D_80109E30_dizzy_dinghies >= 20) {
        D_80109E30_dizzy_dinghies = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += D_8010A028_dizzy_dinghies[i].x;
        out->z += D_8010A028_dizzy_dinghies[i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

void func_801085F4_dizzy_dinghies(omObjData *object) {
    func_800E1BA8_minigame_ObjData *work;
    HmfMotionNode *node;
    Vec vel;
    Vec drift;
    s16 stickX;
    s16 stickY;
    s32 player;
    s32 pad;
    s32 mode;
    f32 speed;
    f32 turn;
    f32 avg;
    f32 x, y, z;
    f32 dist;
    f32 motTime;

    work = object->data;
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
    player = work->unk59;
    pad = work->unk57;
    speed = work->unk40;
    D_80109794_dizzy_dinghies.x = x = object->trans.x;
    D_80109794_dizzy_dinghies.y = y = object->trans.y;
    D_80109794_dizzy_dinghies.z = z = object->trans.z;
    D_8010A118_dizzy_dinghies = (u16)HuPadBtn[pad];
    D_8010A11C_dizzy_dinghies = HuPadStkX[pad];
    HuPadStkX[pad] = 0;
    HuPadBtn[pad] = 0;
    mode = MgFlowStatGet();
    if (mode == MG_STATE_PLAY) {
        stickX = D_8010A11C_dizzy_dinghies;
        stickY = 0;
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        func_800E2308_minigame(&stickX, &stickY);
    } else {
        stickY = 0;
        stickX = 0;
        D_8010A118_dizzy_dinghies = 0;
        if (mode == 3) {
            if (work->unk3C > 180.0f) {
                work->unk3C += 2.0f;
                if (work->unk3C > 360.0f) {
                    work->unk3C = 0.0f;
                }
            } else {
                work->unk3C -= 2.0f;
                if (work->unk3C < 0.0f) {
                    work->unk3C = 0.0f;
                }
            }
        }
    }
    if (D_8010A118_dizzy_dinghies & 0x8000) {
        if (speed == 0.0f) {
            speed = 1.0f;
        }
        speed *= 1.08f;
        D_801097B0_dizzy_dinghies *= D_80109774_dizzy_dinghies;
    } else {
        speed *= D_80109778_dizzy_dinghies;
        D_801097B0_dizzy_dinghies *= 0.9f;
    }
    avg = func_80108488_dizzy_dinghies(player, stickX);
    turn = avg / 15.0f;
    if (speed < 1.0f) {
        speed = 0.0f;
    }
    if (speed > D_80109770_dizzy_dinghies) {
        speed = D_80109770_dizzy_dinghies;
    }
    if (D_801097B0_dizzy_dinghies < 0.05f) {
        D_801097B0_dizzy_dinghies = 0.05f;
    }
    if (D_801097B0_dizzy_dinghies > 1.0f) {
        D_801097B0_dizzy_dinghies = 1.0f;
    }
    if (D_801097E8_dizzy_dinghies != -1) {
        HuAudFXPitchSet((s16)D_801097E8_dizzy_dinghies, (s16)(D_801097B0_dizzy_dinghies * 400.0f + -400.0f));
    }
    work->unk40 = speed;
    vel.x = sindf(work->unk3C) * (speed * D_801097B0_dizzy_dinghies);
    vel.y = 0.0f;
    vel.z = cosdf(work->unk3C) * (speed * D_801097B0_dizzy_dinghies);
    work->unk3C = HuAngleWrap(work->unk3C - turn);
    func_80108514_dizzy_dinghies(player, speed, &drift);
    drift.x += vel.x;
    drift.z += vel.z;
    dist = HuSqrtf(drift.x * drift.x + drift.z * drift.z);
    if (speed < dist) {
        drift.x *= speed / dist;
        drift.z *= speed / dist;
    }
    x += D_801097A0_dizzy_dinghies.x * D_801097AC_dizzy_dinghies + drift.x;
    z += D_801097A0_dizzy_dinghies.z * D_801097AC_dizzy_dinghies + drift.z;
    y = func_80109238_dizzy_dinghies(object, x, 0.0f, z);
    D_80109788_dizzy_dinghies.x = x - D_80109794_dizzy_dinghies.x;
    D_80109788_dizzy_dinghies.y = 0.0f;
    D_80109788_dizzy_dinghies.z = z - D_80109794_dizzy_dinghies.z;
    x += D_800EBE2C_minigame;
    z += D_800EC5D8_minigame;
    D_801097D8_dizzy_dinghies -= (object->trans.x - x) * 32.0f / 1000.0f;
    D_801097DC_dizzy_dinghies += (object->trans.z - z) * 32.0f / 1000.0f;
    func_80108EC4_dizzy_dinghies(object, x, z);
    speed = work->unk40;
    func_80088910_main(Hu3DData[object->model[0]].mtx, 0.0f, work->unk3C, 0.0f);
    func_800E17D4_minigame(object, x, y - 40.0f, z);
    func_80107E04_dizzy_dinghies(object, D_801097B0_dizzy_dinghies);
    if (D_801097AC_dizzy_dinghies != 0.0f) {
        D_801097AC_dizzy_dinghies *= 0.9f;
        if (D_801097AC_dizzy_dinghies < 1.0f) {
            D_801097AC_dizzy_dinghies = 0.0f;
        }
    }
    motTime = Hu3DData[object->model[0]].motTime;
    if (abs(stickX) < 10) {
        if (motTime > 5.0f) {
            motTime *= 0.9f;
            if (motTime < 5.0f) {
                motTime = 5.0f;
            }
        } else {
            motTime *= 1.1f;
            if (motTime > 5.0f) {
                motTime = 5.0f;
            }
            if (motTime < 1.0f) {
                motTime = 1.0f;
            }
        }
    } else {
        motTime -= stickX / 100.0f;
    }
    if (motTime < 0.0f) {
        motTime = 0.0f;
    }
    if (motTime > 10.0f) {
        motTime = 10.0f;
    }
    Hu3DMotionTimeSet(object->model[0], motTime);
    func_801095D4_dizzy_dinghies(object);
    HuPadBtn[pad] = D_8010A118_dizzy_dinghies;
    HuPadStkX[pad] = D_8010A11C_dizzy_dinghies;
    node = Hu3DModelObjPtrGet(object->model[0], "atama_2");
    if (node != (HmfMotionNode *)-1) {
        node->scale.x = node->scale.y = node->scale.z = node->baseScale.x = node->baseScale.y = node->baseScale.z =
            D_801097E4_dizzy_dinghies;
    }
    func_800EA178_minigame(0, speed);
}

void func_80108E30_dizzy_dinghies(Vec *origin, Vec *p, Vec *q, Vec *out) {
    f32 ax = p->x - origin->x;
    f32 ay = p->y - origin->y;
    f32 az = p->z - origin->z;
    f32 bx = q->x - origin->x;
    f32 by = q->y - origin->y;
    f32 bz = q->z - origin->z;

    out->x = ay * bz - az * by;
    out->y = az * bx - ax * bz;
    out->z = ax * by - ay * bx;
    MapVecNormalize(out);
}

void func_80108EC4_dizzy_dinghies(omObjData *object, f32 x, f32 z) {
    func_800E1BA8_minigame_ObjData *work;
    Vec a;
    Vec b;
    Vec c;
    Vec normal;

    a.x = x;
    a.y = func_80105D90_dizzy_dinghies(x, z);
    a.z = z;
    b.x = x + sindf(0.0f) * 10.0f;
    b.z = z + cosdf(0.0f) * 10.0f;
    b.y = func_80105D90_dizzy_dinghies(b.x, b.z);
    c.x = x + sindf(90.0f) * 10.0f;
    c.z = z + cosdf(90.0f) * 10.0f;
    c.y = func_80105D90_dizzy_dinghies(c.x, c.z);
    func_80108E30_dizzy_dinghies(&a, &b, &c, &normal);
    normal.y = 0.0f;
    MapVecNormalize(&normal);
    work = object->data;
    normal.x *= 5.0f;
    normal.z *= 20.0f;
    if (work->unk90 < normal.x) {
        work->unk90 += 1.0f;
    } else if (normal.x < work->unk90) {
        work->unk90 -= 1.0f;
    }
    if (work->unk98 < normal.z) {
        work->unk98 += 1.0f;
    } else if (normal.z < work->unk98) {
        work->unk98 -= 1.0f;
    }
    object->rot.x = work->unk90;
    object->rot.z = work->unk98;
}

void func_801090BC_dizzy_dinghies(omObjData *object, f32 x, f32 z) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    f32 limit = work->unk48;
    f32 mag = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);

    if (mag > limit || fabs(D_800EBE2C_minigame) > limit || fabs(D_800EC5D8_minigame) > limit) {
        D_800EBE2C_minigame = D_80109794_dizzy_dinghies.x - x;
        D_800EC5D8_minigame = D_80109794_dizzy_dinghies.z - z;
    }
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        if (D_80109E3C_dizzy_dinghies == 0) {
            if (0.0f < mag) {
                if (mag < limit / 3.0f) {
                    omVibrate(work->unk59, 2, 3, 10);
                } else {
                    omVibrate(work->unk59, 10, 0, 10);
                }
                D_80109E3C_dizzy_dinghies = 10;
            }
        } else {
            D_80109E3C_dizzy_dinghies--;
        }
    }
}

f32 func_80109238_dizzy_dinghies(omObjData *object, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    f32 speed = work->unk40;
    Hu3DSphere sphere;
    f32 dist;

    sphere.pos.x = x + sindf(work->unk3C) * speed + D_800EBE2C_minigame;
    sphere.pos.y = y;
    sphere.pos.z = z + cosdf(work->unk3C) * speed + D_800EC5D8_minigame;
    sphere.radius = work->unk48;
    work->unk53[0] = work->unk53[1] = -1;
    sphere.pos.x += D_800EBE2C_minigame;
    sphere.pos.z += D_800EC5D8_minigame;
    func_800DD530_minigame(object, &sphere, 0.0f);
    dist = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
    if (dist != 0.0f) {
        if (dist > D_80109770_dizzy_dinghies * 0.5f) {
            work->unk40 *= D_80109784_dizzy_dinghies;
        } else {
            work->unk40 *= D_80109780_dizzy_dinghies;
        }
        if (dist > D_801097AC_dizzy_dinghies) {
            D_801097A0_dizzy_dinghies.x = D_800EBE2C_minigame;
            D_801097A0_dizzy_dinghies.y = 0.0f;
            D_801097A0_dizzy_dinghies.z = D_800EC5D8_minigame;
            MapVecNormalize(&D_801097A0_dizzy_dinghies);
            D_801097AC_dizzy_dinghies = 16.0f;
        }
    }
    func_801090BC_dizzy_dinghies(object, x, z);
    return func_80105D90_dizzy_dinghies(sphere.pos.x, sphere.pos.z);
}

void func_80109420_dizzy_dinghies(omObjData *object) {
    s32 pos[4];
    s16 frameSprite;
    void *data;
    u16 sprite;
    s32 i;

    pos[0] = 62;
    pos[1] = 32;
    pos[2] = 44;
    pos[3] = 28;
    frameSprite = HuSprAnimDataRead(0x670008);
    HuSprAnimDataRead(0x440014);
    HuSprAnimDataRead(0x440015);
    data = DataRead(0x440013);
    HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 1; i++) {
        sprite = espEntry(frameSprite, 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, pos[0], pos[1]);
        espPriSet(sprite, 0xFFFF);
        espTPLvlSet(sprite, 200);
        sprite = espEntry(HuSprAnimDataRead((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, pos[2] - 10, pos[3] + 4);
        espPriSet(sprite, 100);
        func_800E9C20_minigame(1, 5);
        func_800EA0FC_minigame(0, 0.0f, D_80109770_dizzy_dinghies);
        func_800E9F40_minigame(0, 44, 27, 0);
        func_800EA2A8_minigame(0);
    }
    object->func = NULL;
}

void func_801095D4_dizzy_dinghies(omObjData *object) {
    Vec normal;
    f32 dx, dy, dz;
    s32 inside;

    func_80108E30_dizzy_dinghies(&D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0],
                                 &D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][1],
                                 &D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][2], &normal);
    dx = object->trans.x - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].x;
    dy = object->trans.y - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].y;
    dz = object->trans.z - D_80109E44_dizzy_dinghies[D_801097EC_dizzy_dinghies][0].z;
    inside = (dx * normal.x + dy * normal.y + dz * normal.z >= 0.0f) ? 1 : 0;
    if (HuSqrtf(dx * dx + dz * dz) > 1400.0f) {
        inside = 0;
    }
    if (inside == 1 && MgFlowStatGet() == MG_STATE_PLAY) {
        MgFlowStatSet(MG_STATE_FINISH);
        D_801097D4_dizzy_dinghies = inside;
        D_80109E40_dizzy_dinghies = HuAudFXPlay(0x425);
    }
}
