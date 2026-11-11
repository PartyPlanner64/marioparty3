#include "common.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/esprite.h"
#include "game/object.h"
#include "game/wipe.h"
#include "math.h"

typedef struct HeyBatterBatterCamera {
    /* 0x00 */ f32 zoom;
    /* 0x04 */ Vec rot;
    /* 0x10 */ Vec center;
} HeyBatterBatterCamera; // Size 0x1C

extern HeyBatterBatterCamera D_80109EB4_hey_batter_batter;
extern u16 D_800A11DC_main[5];

extern s16 D_80109ED0_hey_batter_batter;
extern s16 D_80109ED6_hey_batter_batter;
extern s16 D_80109EE0_hey_batter_batter;
extern s16 D_80109EE2_hey_batter_batter;
extern s16 D_80109EE4_hey_batter_batter;
extern s16 D_80109EE6_hey_batter_batter[2];
extern s16 D_80109EEA_hey_batter_batter[2];
extern omObjData *D_80109EF4_hey_batter_batter;
extern s16 D_80109F00_hey_batter_batter[5];
extern s16 D_80109F0C_hey_batter_batter[5];

void func_801059BC_hey_batter_batter(void);
void func_80105A4C_hey_batter_batter(void);
void func_80105AB8_hey_batter_batter(void);
void func_80105C44_hey_batter_batter(void);
void func_80105CE8_hey_batter_batter(omObjData *object);
void func_80105DE0_hey_batter_batter(void);
void func_80106048_hey_batter_batter(omObjData *object);
void func_80106C24_hey_batter_batter(omObjData *object);
void func_80106C6C_hey_batter_batter(omObjData *object);
void func_80106CBC_hey_batter_batter(omObjData *object);
void func_80106CE4_hey_batter_batter(omObjData *object);
void func_801070D8_hey_batter_batter(omObjData *object);
void func_80107144_hey_batter_batter(omObjData *object);
void func_801079D0_hey_batter_batter(omObjData *object);
void func_80108B48_hey_batter_batter(omObjData *object);
void func_8010951C_hey_batter_batter(omObjData *object);
void func_80109630_hey_batter_batter(omObjData *object);
s16 func_80109B24_hey_batter_batter(s32 arg0);

void func_801059A0_hey_batter_batter(void) {
    func_801059BC_hey_batter_batter();
}

void func_801059BC_hey_batter_batter(void) {
    func_8001FE20_main(32);
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_8004A208_main();
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
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106048_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801062E0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106744_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106928_hey_batter_batter);

void func_80106C24_hey_batter_batter(omObjData *object) {
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80106CE4_hey_batter_batter);

void func_80106FA8_hey_batter_batter(void) {
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
    object->model[0] = func_8000B108_main(0x5D0001, 0x2A9);
    object->model[1] = func_8000B108_main(0x5D0002, 0x2A9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -1000.0f);
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107144_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107464_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_801079D0_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80107C48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108B48_hey_batter_batter);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80108D90_hey_batter_batter);

void func_8010951C_hey_batter_batter(omObjData *object) {
    s16 i;

    object->model[0] = func_8000B108_main(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[0], 0);
    for (i = 1; i < 6; i++) {
        object->model[i] = func_8000B108_main(0x5D0008, 0x6A9);
        Hu3DModelCameraSet(object->model[i], 0);
    }
    object->model[6] = func_8000B108_main(0xB0006, 0x6A9);
    Hu3DModelCameraSet(object->model[6], 0);
    D_80109EE6_hey_batter_batter[0] = func_80109B24_hey_batter_batter(0xB0006);
    D_80109EE6_hey_batter_batter[1] = func_80109B24_hey_batter_batter(0x5D0008);
    D_80109EEA_hey_batter_batter[0] = 0;
    D_80109EEA_hey_batter_batter[1] = 0;
    object->func = func_80109630_hey_batter_batter;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3C_hey_batter_batter/2D3E70", func_80109630_hey_batter_batter);

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

    espriteSlot = espEntry(func_8000B838_main(spriteId), 0, 0);
    espAttrSet(espriteSlot, attr);
    espPriSet(espriteSlot, priority);
    espPosSet(espriteSlot, x, y);
    return espriteSlot;
}

s16 func_80109B24_hey_batter_batter(s32 arg0) {
    s16 temp = func_8000B13C_main(arg0);

    if (temp < 0) {
        temp = -1;
    }
    return temp;
}
