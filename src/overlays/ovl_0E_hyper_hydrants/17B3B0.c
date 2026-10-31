#include "common.h"
#include "input.h"
#include "game/pause.h"
#include "gcc/memory.h"
#include "mallocblock.h"
#include "opening.h"
#include "overlays/minigame.h"
#include "hyper_hydrants.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct {
    s8 unk00;
    s8 unk01;
    s8 unk02;
    s8 unk03;
    s8 unk04;
    s8 unk05;
    s8 unk06;
    s8 unk07;
    s16 unk08;
    s16 unk0A;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    s8 unk18;
    s8 unk19;
    s8 unk1A;
    s8 unk1B;
    s16 unk1C;
    s16 unk1E;
} HyperHydrantsPlayerData;

typedef struct {
    s8 unk00[3];
    s8 unk03;
    s8 unk04;
    f32 unk08;
    u8 unk0C[0xA8];
} HyperHydrantsMaskData;

typedef struct {
    s16 spread;
    f32 angle;
    f32 speed;
} HyperHydrantsSprayData;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    s8 unk10;
    u16 unk12;
    s32 unk14;
    union {
        s16 value;
        u8 bytes[2];
    } charge;
    s16 unk1A;
    s8 unk1C;
    s16 unk1E;
} HyperHydrantsCharacterData;

Vec D_8010BDE0_hyper_hydrants = { -900.0f, 0.0f, -30.0f };
Vec D_8010BDEC_hyper_hydrants = { -720.0f, 0.0f, -30.0f };
Vec D_8010BDF8_hyper_hydrants = { 750.0f, 0.0f, -30.0f };
Vec D_8010BE04_hyper_hydrants = { 930.0f, 0.0f, -30.0f };
s8 D_8010BE10_hyper_hydrants[] = { 5, 5 };
s16 D_8010BE14_hyper_hydrants[2][2][2] = {
    { { 59, 32 }, { 71, 32 } },
    { { 276, 32 }, { 288, 32 } },
};
s8 D_8010BE24_hyper_hydrants = 0;
s8 D_8010BE25_hyper_hydrants = 0;
f32 D_8010BE28_hyper_hydrants = 570.285f;
f32 D_8010BE2C_hyper_hydrants = -375.0f;
s32 D_8010BE30_hyper_hydrants = 0;
s8 D_8010BE34_hyper_hydrants = 0;
s8 D_8010BE35_hyper_hydrants = 0;
s8 D_8010BE38_hyper_hydrants[][16] = {
    { 0, 1, 2, 1, 0, 2, 1, 0, 1, 2, 1, 0, 0, 2, 1, 2 },
    { 2, 0, 1, 2, 1, 1, 0, 1, 2, 0, 2, 1, 2, 0, 0, 1 },
    { 1, 2, 1, 0, 2, 0, 2, 2, 0, 1, 0, 2, 1, 1, 2, 0 },
};
s8 D_8010BE68_hyper_hydrants[2] = { 0, 0 };
s8 D_8010BE6A_hyper_hydrants = 0;

extern void *D_800EBEB0_minigame;
extern D_80111B50_vine_with_me_Struct D_8010BF60_hyper_hydrants;
extern omObjData *D_8010BFE8_hyper_hydrants[2][5];

extern s8 D_8010BFAC_hyper_hydrants[2];
extern s8 D_8010BFAE_hyper_hydrants[2];
extern s16 D_8010BF42_hyper_hydrants[2];
extern s16 D_8010BF52_hyper_hydrants;
extern s16 D_8010BF54_hyper_hydrants;
extern s16 D_8010BF56_hyper_hydrants;
extern s16 D_8010BF58_hyper_hydrants;
extern s16 D_8010BF88_hyper_hydrants;
extern s16 D_8010BF8A_hyper_hydrants[2];
extern s8 D_8010BF50_hyper_hydrants;
extern u32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern s8 D_8010BF40_hyper_hydrants;
extern s16 D_8010C022_hyper_hydrants[2];
extern s16 D_800EB934_minigame;
extern Vec D_8010C028_hyper_hydrants[2];
extern HyperHydrantsChainPoint *D_8010BFB0_hyper_hydrants[2][6];

extern u8 D_800D6A90_main;
extern u16 D_800A1906_main;
extern s16 D_800EB930_minigame;
extern s32 D_8010BF48_hyper_hydrants;
extern s32 D_8010BF4C_hyper_hydrants;
extern s8 D_8010BFA8_hyper_hydrants;
extern s8 D_8010BFA9_hyper_hydrants;
extern s8 D_8010BFAA_hyper_hydrants;
extern s8 D_8010BFAB_hyper_hydrants;
extern s16 D_800EB932_minigame;
extern omObjData *D_8010BFE0_hyper_hydrants[];
extern s8 D_8010BF46_hyper_hydrants;
extern s16 D_8010BF8E_hyper_hydrants;
extern s16 D_8010BF90_hyper_hydrants;
extern u8 *D_8010BF94_hyper_hydrants[2];
extern s32 D_8010BF9C_hyper_hydrants;
extern s32 D_8010BFA0_hyper_hydrants;
extern s32 D_8010BFA4_hyper_hydrants;
extern s8 D_8010C010_hyper_hydrants;
extern s16 D_8010C012_hyper_hydrants[2];
extern s16 D_8010C016_hyper_hydrants[2];
extern s16 D_8010C01A_hyper_hydrants[2][2];

void func_80021BE0_main(void *arg0, u16 arg1);
void func_800E1804_minigame(void);
void func_80105CB4_hyper_hydrants(D_80111B50_vine_with_me_Struct *arg0);
void func_80105FC8_hyper_hydrants(void);
void func_80105D44_hyper_hydrants(omObjData *object);
void func_801060F8_hyper_hydrants(omObjData *object);
void func_80108F34_hyper_hydrants(omObjData *object);
void func_80109588_hyper_hydrants(omObjData *object);
void func_801099A0_hyper_hydrants(omObjData *object);
void func_801078B8_hyper_hydrants(omObjData *object);
void func_8010AE08_hyper_hydrants(omObjData *object);
void func_80106238_hyper_hydrants(omObjData *object);
void func_8010A68C_hyper_hydrants(omObjData *object);
void func_8010B658_hyper_hydrants(omObjData *object);
s16 func_8010BC80_hyper_hydrants(s16 soundId, s16 side, s8 playerSound, s16 player);
void func_800E6F0C_minigame(s32 state);
void func_800E1840_minigame(void);
void func_800E1370_minigame(omObjData *object, s32 arg1, f32 arg2);
void HuAudFXAllStop(void);
void HuAudFXPanning(s16 arg0, s16 arg1);
void func_8000B710_main(s32 arg0);
void func_80105EB0_hyper_hydrants(s8 camera);
void func_8010B8B0_hyper_hydrants(omObjData *object);
void func_8010B38C_hyper_hydrants(void);
void func_8010B2FC_hyper_hydrants(omObjData *object);
void func_8010AB34_hyper_hydrants(omObjData *object);
void func_8010A2D4_hyper_hydrants(omObjData *object);
void func_80107A90_hyper_hydrants(omObjData *object);
void func_80107238_hyper_hydrants(omObjData *object);
void func_80106A50_hyper_hydrants(omObjData *object);
void func_80108788_hyper_hydrants(s16 model);
void func_801083A8_hyper_hydrants(s16 model, Vec *position, HyperHydrantsSprayData *data, s8 count);
void func_801091B0_hyper_hydrants(omObjData *object);
void func_80109B30_hyper_hydrants(omObjData *object);
void func_80109E44_hyper_hydrants(omObjData *object);
void func_8010A458_hyper_hydrants(omObjData *object);
void func_80109484_hyper_hydrants(omObjData *object);
void func_80012B14_main(s16 camera, Vec *position, Vec2f *screen);
void func_8001F6BC_main(s16 model, u8 r, u8 g, u8 b, u8 a);
void func_8001F6F8_main(s16 model, u8 r, u8 g, u8 b, u8 a);
s16 HmfAnimRead(HmfData *hmf, s32 file, char *name);
void func_800E4C88_minigame(omObjData *object, u8 type, f32 x, f32 y, f32 z, f32 arg5, f32 arg6);

void func_801059A0_hyper_hydrants(void) {
    omObjData *object;
    s32 i;
    s32 j;

    Hu3DAnimInit(0x20);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105FC8_hyper_hydrants();
    func_80105CB4_hyper_hydrants(&D_8010BF60_hyper_hydrants);
    func_800E5EA0_minigame(&D_8010BF60_hyper_hydrants);
    HmfLightColorSet(1, 0x40, 0x40, 0x40);
    HmfLightDirSet(1, 0.0f, 0.0f, 100.0f);
    object = omAddObj(0x7FDA, 0, 0, -1, func_80105D44_hyper_hydrants);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80105D44_hyper_hydrants(object);
    object = omAddObj(0, 0, 0, -1, func_801060F8_hyper_hydrants);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 2; i++) {
        D_8010BFE0_hyper_hydrants[i] = omAddObj(0, 2, 0, -1, func_80108F34_hyper_hydrants);
    }
    D_8010C010_hyper_hydrants = (rand8() * 3) >> 8;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 5; i++) {
            D_8010BFE8_hyper_hydrants[j][i] = omAddObj(0, 3, 0, -1, func_80109588_hyper_hydrants);
        }
    }
    for (i = 0; i < 2; i++) {
        omAddObj(1, 10, 0, -1, func_801078B8_hyper_hydrants);
    }
    omAddObj(1, 0, 0, -1, func_8010AE08_hyper_hydrants);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 3, 5, -1, func_80106238_hyper_hydrants);
    }
    for (i = 0; i < 2; i++) {
        omAddObj(3, 6, 0, -1, func_8010A68C_hyper_hydrants);
    }
    omAddObj(3, 0, 0, -1, func_8010B658_hyper_hydrants);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105CB4_hyper_hydrants(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 10;
    arg0->unk00 = 0;
    arg0->unk01 = 1;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 9;
    arg0->unk1C = 80;
    arg0->unk1E = 900;
    arg0->unk20 = -1;
    arg0->unk22 = 75;
    arg0->unk24 = 150;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105D44_hyper_hydrants(omObjData *object) {
    func_80105EB0_hyper_hydrants(0);
    func_80105EB0_hyper_hydrants(1);
}

void func_80105D68_hyper_hydrants(s8 camera) {
    Vec pos;
    Vec at;
    Vec up;

    if (camera == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = D_8010BE28_hyper_hydrants;
    if (camera == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0;
    D_8010BE2C_hyper_hydrants += 2.0f;
    if (D_8010BE2C_hyper_hydrants > at.y) {
        D_8010BE2C_hyper_hydrants = at.y;
    }
    at.z = D_8010BE2C_hyper_hydrants;
    up.x = 0;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(camera, &pos, &at, &up);
    Hu3DCamUpdateMtx(camera);
}

void func_80105EB0_hyper_hydrants(s8 camera) {
    Vec pos;
    Vec at;
    Vec up;

    if (camera == 0) {
        pos.x = -850.0f;
    } else {
        pos.x = 850.0f;
    }
    pos.y = 1046.895f;
    pos.z = 570.285f;
    if (camera == 0) {
        at.x = -850.0f;
    } else {
        at.x = 850.0f;
    }
    at.y = 0;
    at.z = -375.0f;
    up.x = 0;
    up.y = 1050.25f;
    up.z = 566.575f;
    Hu3DCamSetPositionOrientation(camera, &pos, &at, &up);
    Hu3DCamUpdateMtx(camera);
}

void func_80105FC8_hyper_hydrants(void) {
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 35.883f, 80.0f, 8000.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(1, 35.883f, 80.0f, 8000.0f);
}

void func_801060F8_hyper_hydrants(omObjData *object) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_8010BE34_hyper_hydrants == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            func_800E6F0C_minigame(5);
            D_8010BE34_hyper_hydrants = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 52;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010BE30_hyper_hydrants == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010BE30_hyper_hydrants++;
                break;
        }
    }
}

void func_80106238_hyper_hydrants(omObjData *object) {
    s32 character;
    u32 model;
    s32 motion;
    func_800E1BA8_minigame_ObjData *playerData;
    HyperHydrantsCharacterData *data;

    character = (s8)GwPlayer[D_8010BE35_hyper_hydrants].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A1790_main[character][0];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(object, model, motion, D_8010BE35_hyper_hydrants, 0xAC9, 0xAD9);
    playerData = object->data;
    object->rot.x = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    playerData->unk158 = HuMemAllocTag(sizeof(HyperHydrantsCharacterData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(HyperHydrantsCharacterData));
    data = playerData->unk158;
    data->charge.value = 0;
    data->unk1A = 0;
    data->unk10 = 0;
    data->unk12 = 0x4000;
    data->unk1E = 0;
    data->unk1C = 0;
    func_8000B460_main(object, 0, func_80017BB8_main(character, 0));
    func_8000B460_main(object, 1, func_80017BB8_main(character, 0x14));
    func_8000B460_main(object, 2, func_80017BB8_main(character, 0x7B));
    func_8000B460_main(object, 3, func_80017BB8_main(character, 0x2F));
    func_8000B460_main(object, 4, func_80017BB8_main(character, 0x36));
    if (D_8010BE35_hyper_hydrants == 0) {
        D_8010BF40_hyper_hydrants = (rand8() * 5U) >> 7;
    }
    switch (GwPlayer[playerData->unk59].group) {
        case 0:
            object->trans.x = D_8010BDE0_hyper_hydrants.x;
            object->trans.y = D_8010BDE0_hyper_hydrants.y;
            object->trans.z = D_8010BDE0_hyper_hydrants.z;
            D_8010BFAA_hyper_hydrants = playerData->unk59;
            object->rot.y = 180.0f;
            object->model[2] = func_8000B108_main(0x2F0004, 0xA99);
            Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
            Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[2]].motId, 0, 1, 2);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
            D_8010C022_hyper_hydrants[0] = func_8010BC80_hyper_hydrants(0x369, 0, 1, playerData->unk59);
            HuAudFXVolSet(D_8010C022_hyper_hydrants[0], 0);
            break;
        case 1:
            object->trans.x = D_8010BDEC_hyper_hydrants.x;
            object->trans.y = D_8010BDEC_hyper_hydrants.y;
            object->trans.z = D_8010BDEC_hyper_hydrants.z;
            D_8010BFA8_hyper_hydrants = playerData->unk59;
            object->rot.y = 0;
            object->model[2] = func_8000B108_main(0x2F0005, 0xA89);
            func_8001C258_main(object->model[2], 0x10000, 0x10000);
            func_8001F6BC_main(object->model[2], 0, 0, 0, 0);
            func_8001F6F8_main(object->model[2], 16, 16, 16, 0);
            Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[1]].motId, 0, 1, 2);
            if ((model >> 16) == 6) {
                object->trans.z -= 48.7f;
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            }
            Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
            break;
        case 2:
            object->trans.x = D_8010BDF8_hyper_hydrants.x;
            object->trans.y = D_8010BDF8_hyper_hydrants.y;
            object->trans.z = D_8010BDF8_hyper_hydrants.z;
            D_8010BFAB_hyper_hydrants = playerData->unk59;
            object->rot.y = 180.0f;
            object->model[2] = func_8000B108_main(0x2F0006, 0xA99);
            Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
            Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[2]].motId, 0, 1, 2);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
            D_8010C022_hyper_hydrants[1] = func_8010BC80_hyper_hydrants(0x369, 1, 1, playerData->unk59);
            HuAudFXVolSet(D_8010C022_hyper_hydrants[1], 0);
            break;
        case 3:
            object->trans.x = D_8010BE04_hyper_hydrants.x;
            object->trans.y = D_8010BE04_hyper_hydrants.y;
            object->trans.z = D_8010BE04_hyper_hydrants.z;
            D_8010BFA9_hyper_hydrants = playerData->unk59;
            object->rot.y = 0;
            object->model[2] = func_8000B108_main(0x2F0007, 0xA89);
            func_8001C258_main(object->model[2], 0x10000, 0x10000);
            func_8001F6BC_main(object->model[2], 0, 0, 0, 0);
            func_8001F6F8_main(object->model[2], 16, 16, 16, 0);
            Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[1]].motId, 0, 1, 2);
            if ((model >> 16) == 6) {
                object->trans.z -= 48.7f;
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z + 48.7f);
            } else {
                Hu3DModelPosSet(object->model[2], object->trans.x, 0, object->trans.z);
            }
            Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
            Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
            break;
    }
    data->unk00 = sindf(object->rot.y - 40.0f);
    data->unk04 = cosdf(object->rot.y - 40.0f);
    data->unk08 = sindf(object->rot.y - 140.0f);
    data->unk0C = cosdf(object->rot.y - 140.0f);
    func_8001C814_main(object->model[0], 1, 1);
    Hu3DMotionTimeSet(object->model[2], 0);
    object->func = func_80106A50_hyper_hydrants;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    D_8010BE35_hyper_hydrants++;
}

void func_80106A50_hyper_hydrants(omObjData *object) {
    func_800E1BA8_minigame_ObjData *playerData;
    HyperHydrantsCharacterData *data;
    s8 side;
    s32 character;

    switch (func_800E6E8C_minigame()) {
        case 0:
        case 1:
            Hu3DMotionTimeSet(object->model[2], HmfModelData[object->model[0]].motTime);
            break;
        case 2:
            playerData = object->data;
            data = playerData->unk158;
            if (playerData->unk59 == D_8010BFA8_hyper_hydrants || playerData->unk59 == D_8010BFA9_hyper_hydrants) {
                func_80107238_hyper_hydrants(object);
                break;
            }
            if (!(GwPlayer[playerData->unk59].stat & 1)) {
                if ((D_800CBB6E_main[playerData->unk57] < 0 ? -D_800CBB6E_main[playerData->unk57] : D_800CBB6E_main[playerData->unk57]) > 0 && object->rot.y > 120.0f && object->rot.y < 240.0f) {
                    func_8001C814_main(object->model[0], 1, 2);
                } else {
                    func_8001C814_main(object->model[0], 1, 1);
                }
            }
            data->unk00 = sindf(object->rot.y - 40.0f);
            data->unk04 = cosdf(object->rot.y - 40.0f);
            data->unk08 = sindf(object->rot.y - 140.0f);
            data->unk0C = cosdf(object->rot.y - 140.0f);
            side = playerData->unk59 != D_8010BFAA_hyper_hydrants;
            switch (D_8010BFAC_hyper_hydrants[side]) {
                case 0:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 0);
                    break;
                case 1:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 84);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], -300);
                    break;
                case 2:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 91);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], -200);
                    break;
                case 3:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 98);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], -100);
                    break;
                case 4:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 112);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], 100);
                    break;
                case 5:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 119);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], 200);
                    break;
                default:
                    HuAudFXVolSet(D_8010C022_hyper_hydrants[side], 127);
                    HuAudFXPitchSet(D_8010C022_hyper_hydrants[side], 300);
                    break;
            }
            break;
        case 3:
            playerData = object->data;
            if (func_800E6E9C_minigame() == 0) {
                HuAudFXStop(D_8010C022_hyper_hydrants[0]);
                HuAudFXStop(D_8010C022_hyper_hydrants[1]);
                HuAudFXPlay(0x36B);
                Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[0]].motId, 0, 30, 2);
                func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                switch (GwPlayer[playerData->unk59].group) {
                    case 0:
                    case 1:
                        if (D_8010BE24_hyper_hydrants > D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 1;
                            if (D_8010BF60_hyper_hydrants.unk18[0] == 0xFF) {
                                D_8010BF60_hyper_hydrants.unk18[0] = playerData->unk59;
                            } else {
                                D_8010BF60_hyper_hydrants.unk18[1] = playerData->unk59;
                            }
                        } else if (D_8010BE24_hyper_hydrants == D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 4;
                        }
                        break;
                    case 2:
                    case 3:
                        if (D_8010BE24_hyper_hydrants < D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 1;
                            if (D_8010BF60_hyper_hydrants.unk18[0] == 0xFF) {
                                D_8010BF60_hyper_hydrants.unk18[0] = playerData->unk59;
                            } else {
                                D_8010BF60_hyper_hydrants.unk18[1] = playerData->unk59;
                            }
                        } else if (D_8010BE24_hyper_hydrants == D_8010BE25_hyper_hydrants) {
                            D_8010BF60_hyper_hydrants.unk06 = 4;
                        }
                        break;
                }
            }
            if ((object->rot.y > 0.0f ? object->rot.y : 0.0f - object->rot.y) > 20.0f) {
                object->rot.y -= 20.0f;
            } else {
                object->rot.y = 0.0f;
            }
            if ((D_800A178C_main[GwPlayer[playerData->unk59].chr][0] >> 16) == 6 &&
                (D_8010BFA8_hyper_hydrants == playerData->unk59 || D_8010BFA9_hyper_hydrants == playerData->unk59)) {
                object->trans.z += 5.0f;
                if (object->trans.z > 18.7f) {
                    object->trans.z = 18.7f;
                }
                Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
            }
            break;
        case 4:
            if (D_800EB934_minigame != 0) {
                playerData = object->data;
                if (playerData->unk59 == D_8010BF60_hyper_hydrants.unk18[0] ||
                    playerData->unk59 == D_8010BF60_hyper_hydrants.unk18[1]) {
                    Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[3]].motId, 0, 30, 2);
                    switch (GwPlayer[playerData->unk59].chr) {
                        case 0:
                        default:
                            character = 2;
                            break;
                        case 1:
                            character = 3;
                            break;
                        case 2:
                            character = 7;
                            break;
                        case 3:
                            character = 4;
                            break;
                        case 4:
                            character = 5;
                            break;
                        case 5:
                            character = 6;
                            break;
                        case 6:
                            character = 8;
                            break;
                        case 7:
                            character = 9;
                            break;
                    }
                    func_80045ED0_main((character << 16) | 0x2F);
                    GwPlayer[playerData->unk59].bonusCoin += 10;
                } else {
                    Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[4]].motId, 0, 30, 2);
                }
            } else if (HmfModelData[object->model[0]].motTime >= 118.0f) {
                func_8001C814_main(object->model[0], 1, 1);
            }
            break;
        case 5:
            break;
    }
}

void func_80107238_hyper_hydrants(omObjData *object) {
    func_800E1BA8_minigame_ObjData *playerData;
    HyperHydrantsCharacterData *data;
    u16 pressA = 0;
    u16 pressB = 0;
    s8 side;
    s16 press;
    s8 random;
    f32 time;
    f32 end;

    playerData = object->data;
    data = playerData->unk158;
    time = HmfModelData[object->model[0]].motTime;
    end = D_800CCF58_main[HmfModelData[object->model[0]].motId].unk02;
    side = GwPlayer[playerData->unk59].group >= 2;
    if (GwPlayer[playerData->unk59].stat & 1) {
        if ((time == end) | (time == 0.0f)) {
            random = (rand8() * 100) >> 8;
            switch (GwPlayer[playerData->unk59].cpu_difficulty) {
                case 3:
                    press = 1;
                    break;
                case 2:
                    press = random < 90;
                    break;
                case 1:
                default:
                    press = random < 40;
                    break;
                case 0:
                    press = random < 30;
                    break;
            }
            if (D_8010BFAC_hyper_hydrants[side] == 0) {
                D_8010BFAC_hyper_hydrants[side] = 1;
                press = 1;
            }
        } else {
            press = 0;
        }
        if (press) {
            if (time == end) {
                pressB = 1;
            } else if (time == 0.0f) {
                pressA = 1;
            }
        }
    } else {
        pressA = (D_800D5558_main[playerData->unk57] & A_BUTTON) != 0;
        pressB = (D_800D5558_main[playerData->unk57] & (B_BUTTON | Z_TRIG)) != 0;
    }
    if ((pressA != 0) & (pressB != 0)) {
        if (data->unk12 == 0x8000) {
            pressA = 0;
        } else {
            pressB &= data->unk12 != 0x4000 ? 0xFFFF : 0;
        }
    } else if (pressA) {
        pressA &= data->unk12 != 0x8000 ? 0xFFFF : 0;
    } else if (pressB) {
        pressB &= data->unk12 != 0x4000 ? 0xFFFF : 0;
    }
    if (pressA) {
        Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[1]].motId, (s16)time, 1, 2);
        data->unk10 = 1;
        func_8010BC80_hyper_hydrants(0x368, side, 1, playerData->unk59);
        data->unk12 = 0x8000;
    } else if (pressB) {
        Hu3DMotionShiftSet(object->model[0], HmfModelData[object->motion[1]].motId, (s16)time, 1, 4);
        data->unk10 = 2;
        func_8010BC80_hyper_hydrants(0x367, side, 1, playerData->unk59);
        data->unk12 = 0x4000;
    }
    if (data->unk10 == 1) {
        if (data->charge.value < 9) {
            data->charge.value++;
        }
        if (time >= end - 2.0f) {
            func_8001C814_main(object->model[0], 1, 1);
            func_8001C814_main(object->model[2], 1, 1);
            time = end;
            data->unk10 = 0;
        }
        D_8010BF42_hyper_hydrants[side] = 0;
    } else if (data->unk10 == 2) {
        end = 0.0f;
        if (time == end) {
            func_8001C814_main(object->model[0], 1, 1);
            func_8001C814_main(object->model[2], 1, 1);
            time = end;
            data->unk10 = 0;
        } else {
            data->unk1C = 0;
        }
        D_8010BF42_hyper_hydrants[side] = 0;
    } else {
        if (data->charge.value == 0) {
            D_8010BFAC_hyper_hydrants[side] = 0;
        } else if (data->charge.value < 2) {
            D_8010BFAC_hyper_hydrants[side] = 1;
        } else if (data->charge.value < 3) {
            D_8010BFAC_hyper_hydrants[side] = 2;
        } else if (data->charge.value < 4) {
            D_8010BFAC_hyper_hydrants[side] = 3;
        } else if (data->charge.value < 6) {
            D_8010BFAC_hyper_hydrants[side] = 4;
        } else if (data->charge.value < 8) {
            D_8010BFAC_hyper_hydrants[side] = 5;
        } else {
            D_8010BFAC_hyper_hydrants[side] = 6;
        }
        if (D_8010BF42_hyper_hydrants[side] >= 2) {
            if (data->charge.value > 0) {
                data->charge.value--;
            }
        }
        D_8010BF42_hyper_hydrants[side]++;
    }
    Hu3DMotionTimeSet(object->model[0], time);
    Hu3DMotionTimeSet(object->model[2], time);
    if (time == 0.0f) {
        data->unk1C ^= 1;
    } else {
        data->unk1C = 0;
    }
    if (data->unk1C) {
        func_8001F6BC_main(object->model[2], 64, 64, 64, 0);
        func_8001F6F8_main(object->model[2], 0, 0, 0, 0);
    } else {
        func_8001F6BC_main(object->model[2], 0, 0, 0, 0);
        func_8001F6F8_main(object->model[2], 16, 16, 16, 0);
    }
    if (data->unk1A >= 31) {
        D_8010BFAC_hyper_hydrants[side] = data->charge.bytes[1];
        data->unk1A = 0;
        data->charge.value = 0;
    } else {
        data->unk1A++;
    }
}

void func_801078B8_hyper_hydrants(omObjData *object) {
    HyperHydrantsSprayData *data;
    omObjData *player;

    object->work[0] = D_8010BF46_hyper_hydrants;
    object->func = func_80107A90_hyper_hydrants;
    object->model[0] = func_8000B108_main(0x2F000B, 0x689);
    if (D_8010BF46_hyper_hydrants == 0) {
        player = D_800EC598_minigame[D_8010BFAA_hyper_hydrants];
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    } else {
        player = D_800EC598_minigame[D_8010BFAB_hyper_hydrants];
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    }
    object->trans.x = player->trans.x;
    object->trans.z = player->trans.z;
    object->trans.y = 40.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    func_8001C2FC_main(object->model[0], 0x20000, 0x20000);
    func_8001C448_main(object->model[0]);
    func_8001C954_main(object->model[0]);
    func_8001C514_main(object->model[0]);
    func_80013390_main(object->model[0], -1, 0, func_80108788_hyper_hydrants);
    data = HuMemAllocTag(sizeof(HyperHydrantsSprayData), TAG_OVERLAY);
    object->data = data;
    memset(data, 0, sizeof(HyperHydrantsSprayData));
    data->spread = 5;
    data->angle = 180.0f;
    data->speed = 50.0f;
    HmfModelData[object->model[0]].unkBC->unk08.f = D_8010BF46_hyper_hydrants;
    D_8010BF46_hyper_hydrants++;
}

void func_80107A90_hyper_hydrants(omObjData *object) {
    HyperHydrantsSprayData *data;
    HyperHydrantsCharacterData *characterData;
    omObjData *player;
    func_800E1BA8_minigame_ObjData *playerData;
    Vec position;
    f32 angle;
    f32 farthest;
    s16 side;
    s16 target;
    s16 count;
    s16 i;
    s8 playerIndex;
    s8 port;
    s8 particles;
    s16 maxSpread;

    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    if (object->work[0] == 0) {
        if (D_8010BFAC_hyper_hydrants[0] == 0) {
            return;
        }
        side = 0;
        playerIndex = D_8010BFAA_hyper_hydrants;
    } else {
        if (D_8010BFAC_hyper_hydrants[1] == 0) {
            return;
        }
        side = 1;
        playerIndex = D_8010BFAB_hyper_hydrants;
    }
    player = D_800EC598_minigame[playerIndex];
    playerData = player->data;
    characterData = playerData->unk158;
    port = playerData->unk57;
    data = object->data;
    count = 0;
    if (GwPlayer[playerIndex].stat & 1) {
        farthest = -1000.0f;
        target = 4;
        for (i = 0; i < 5; i++) {
            if (D_8010BFE8_hyper_hydrants[side][i]->trans.z > farthest) {
                farthest = D_8010BFE8_hyper_hydrants[side][i]->trans.z;
                target = i;
            }
            if (D_8010BFE8_hyper_hydrants[side][i]->trans.z >= -250.0f) {
                count++;
            }
        }
        angle = atan2df(D_8010BFE8_hyper_hydrants[side][target]->trans.x - D_800EC598_minigame[playerIndex]->trans.x,
                        D_8010BFE8_hyper_hydrants[side][target]->trans.z - D_800EC598_minigame[playerIndex]->trans.z);
        while (angle >= 360.0f) {
            angle -= 360.0f;
        }
        while (angle < 0.0f) {
            angle += 360.0f;
        }
        if (ABS((s32)angle - data->angle) > 5.0f) {
            func_8001C814_main(D_800EC598_minigame[playerIndex]->model[0], 1, 2);
            switch (GwPlayer[playerIndex].cpu_difficulty) {
                case 3:
                    if ((s32)angle < data->angle) {
                        data->angle -= 4.0f;
                    } else {
                        data->angle += 4.0f;
                    }
                    break;
                case 2:
                    if (((rand8() * 2) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 4.0f;
                        } else {
                            data->angle += 4.0f;
                        }
                    }
                    break;
                case 1:
                default:
                    if (((rand8() * 3) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 2.0f;
                        } else {
                            data->angle += 2.0f;
                        }
                    }
                    break;
                case 0:
                    if (((rand8() * 5) >> 8) == 0) {
                        if ((s32)angle < data->angle) {
                            data->angle -= 1.0f;
                        } else {
                            data->angle += 1.0f;
                        }
                    }
                    break;
            }
        } else {
            func_8001C814_main(D_800EC598_minigame[playerIndex]->model[0], 1, 1);
        }
        if (data->angle > 240.0f) {
            data->angle = 240.0f;
        }
        if (data->angle < 120.0f) {
            data->angle = 120.0f;
        }
        if (count >= 2) {
            D_800CDA7C_main[port] |= 0x8000;
        } else {
            D_800CDA7C_main[port] &= 0x7FFF;
        }
    } else if (ABS(D_800CBB6E_main[port]) > 40) {
        if (D_800CBB6E_main[port] < 0) {
            data->angle += 5.0f;
            if (data->angle > 240.0f) {
                data->angle = 240.0f;
            }
        } else if (D_800CBB6E_main[port] > 0) {
            data->angle -= 5.0f;
            if (data->angle < 120.0f) {
                data->angle = 120.0f;
            }
        }
    } else if (ABS(D_800CBB6E_main[port]) > 20) {
        if (D_800CBB6E_main[port] < 0) {
            data->angle += 2.0f;
            if (data->angle > 240.0f) {
                data->angle = 240.0f;
            }
        } else if (D_800CBB6E_main[port] > 0) {
            data->angle -= 2.0f;
            if (data->angle < 120.0f) {
                data->angle = 120.0f;
            }
        }
    }
    player->rot.y = data->angle;
    Hu3DModelRotSet(player->model[2], player->rot.x, player->rot.y, player->rot.z);
    if ((u16)D_800CDA7C_main[port] & A_BUTTON) {
        data->spread += 3;
        maxSpread = D_8010BFAC_hyper_hydrants[side] * 15;
        if (data->spread > maxSpread) {
            data->spread = maxSpread;
        }
    } else {
        data->spread -= 3;
        if (data->spread < 5) {
            data->spread = 5;
        }
    }
    D_8010BFAE_hyper_hydrants[side] = data->spread;
    if (data->spread > 50) {
        position.x = characterData->unk00 * 110.0f + player->trans.x;
        position.z = characterData->unk04 * 110.0f + player->trans.z;
    } else {
        position.x = characterData->unk00 * 55.0f + player->trans.x;
        position.z = characterData->unk04 * 55.0f + player->trans.z;
    }
    position.y = 40.0f;
    if (data->spread > 20) {
        particles = 28;
    } else {
        particles = 10;
    }
    func_801083A8_hyper_hydrants(object->model[0], &position, data, particles);
}

void func_801083A8_hyper_hydrants(s16 model, Vec *position, HyperHydrantsSprayData *data, s8 count) {
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 particleCount;
    s16 halfSpread;
    s16 i;
    f32 angle;
    f32 speed;
    f32 offset;
    f32 random;
    Vec velocity;

    hmf = HmfModelData[model].hmf;
    modelData = HmfModelData[model].unkBC;
    particleCount = hmf->unk1A;
    halfSpread = data->spread / 2;
    angle = data->angle - halfSpread;
    speed = data->speed + ((rand8() * 10) >> 8) * 0.1f;
    random = (rand8() * data->spread) >> 8;
    velocity.x = sindf(angle + random) * speed;
    random = (rand8() * data->spread) >> 8;
    velocity.y = sindf(-halfSpread + random) * speed;
    random = (rand8() * data->spread) >> 8;
    velocity.z = cosdf(angle + random) * speed;
    particle = modelData->unk58;
    for (i = 0; i < particleCount; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            memcpy(&particle->unk24, &velocity, sizeof(velocity));
            offset = ((rand8() * 10) >> 8) * 0.1f;
            particle->unk0C = offset * velocity.x + position->x;
            particle->unk10 = offset * velocity.y + position->y;
            particle->unk14 = offset * velocity.z + position->z;
            if (data->spread >= 21) {
                particle->unk08 = (rand8() % 8) + 2;
            } else {
                particle->unk08 = (rand8() % 3) + 2;
            }
            if (--count == 0) {
                break;
            }
            speed = data->speed + ((rand8() * 10) >> 8) * 0.1f;
            random = (rand8() * data->spread) >> 8;
            velocity.x = sindf(angle + random) * speed;
            random = (rand8() * data->spread) >> 8;
            velocity.y = sindf(-halfSpread + random) * speed;
            random = (rand8() * data->spread) >> 8;
            velocity.z = cosdf(angle + random) * speed;
        }
    }
}

void func_80108788_hyper_hydrants(s16 model) {
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    func_800E1BA8_minigame_ObjData *characterData;
    omObjData *target;
    HyperHydrantsPlayerData *data;
    s16 particleCount;
    s16 j;
    s16 i;
    s32 side;
    s32 port;
    s32 hit;
    s32 hitEnd;
    f32 limit;
    f32 oldZ;
    f32 nextZ;
    f32 targetZ;
    f32 distance;
    s32 threshold;

    hmf = HmfModelData[model].hmf;
    modelData = HmfModelData[model].unkBC;
    particleCount = hmf->unk1A;
    side = modelData->unk08.f;
    if (modelData->unk02 == 0) {
        modelData->unk04 &= ~4;
        for (i = 0, particle = modelData->unk58; i < particleCount; particle++, i++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        modelData->unk02++;
    }
    particle = modelData->unk58;
    if (side == 0) {
        characterData = D_800EC598_minigame[D_8010BFAA_hyper_hydrants]->data;
    } else {
        characterData = D_800EC598_minigame[D_8010BFAB_hyper_hydrants]->data;
    }
    port = characterData->unk57;
    limit = ((u16)D_800CDA7C_main[port] & A_BUTTON) ? -250.0f : -500.0f;
    for (i = 0; i < particleCount; particle++, i++) {
        if (particle->unk10 > 0.0f) {
            if (particle->unk14 < limit) {
                particle->unk08 = 0.0f;
                particle->unk10 = 0.0f;
            } else {
                oldZ = particle->unk14;
                nextZ = oldZ + particle->unk2C;
                for (j = 0; j < 5; j++) {
                    target = D_8010BFE8_hyper_hydrants[side][j];
                    data = target->data;
                    if (data->unk10 == 0.0f) {
                        continue;
                    }
                    targetZ = target->trans.z;
                    distance = target->trans.x - particle->unk0C > 0.0f ? target->trans.x - particle->unk0C : 0.0f - (target->trans.x - particle->unk0C);
                    if (nextZ < oldZ) {
                        hit = nextZ < targetZ;
                        hitEnd = targetZ < oldZ;
                    } else {
                        hit = oldZ < targetZ;
                        hitEnd = targetZ < nextZ;
                    }
                    if ((hit & hitEnd) && distance < data->unk10 * target->scale.x) {
                        if ((u16)D_800CDA7C_main[port] & A_BUTTON) {
                            particle->unk10 = particle->unk08 = 0.0f;
                        }
                        // TODO: do-while(0) required to match (raises the hoisted 1's
                        // register-allocation priority above the loop counter i)
                        do {
                            data->unk19 = 1;
                        } while (0);
                        break;
                    }
                }
            }
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28 - 1.0f;
            particle->unk14 += particle->unk2C;
            switch (D_8010BFAC_hyper_hydrants[side]) {
                case 0:
                    particle->unk10 = particle->unk08 = 0.0f;
                    particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
                    break;
                case 1:
                    particle->unk24 *= 0.6f;
                    particle->unk28 *= 0.6f;
                    particle->unk2C *= 0.6f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 75.0f;
                    } else {
                        particle->unk28 -= 2.5f;
                    }
                    break;
                case 2:
                    particle->unk24 *= 0.7f;
                    particle->unk28 *= 0.7f;
                    particle->unk2C *= 0.7f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 52.5f;
                    } else {
                        particle->unk28 -= 1.75f;
                    }
                    break;
                case 3:
                    particle->unk24 *= 0.8f;
                    particle->unk28 *= 0.8f;
                    particle->unk2C *= 0.8f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 45.0f;
                    } else {
                        particle->unk28 -= 1.5f;
                    }
                    break;
                case 4:
                    particle->unk24 *= 0.8f;
                    particle->unk28 *= 0.8f;
                    particle->unk2C *= 0.8f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 30.0f;
                    } else {
                        particle->unk28 -= 1.0f;
                    }
                    break;
                case 5:
                    particle->unk24 *= 0.9f;
                    particle->unk28 *= 0.9f;
                    particle->unk2C *= 0.9f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 15.0f;
                    } else {
                        particle->unk28 -= 0.5f;
                    }
                    break;
                default:
                    particle->unk24 *= 0.99f;
                    particle->unk28 *= 0.99f;
                    particle->unk2C *= 0.99f;
                    if (D_8010BFAE_hyper_hydrants[side] >= 6) {
                        particle->unk28 -= 15.0f;
                    } else {
                        particle->unk28 -= 0.5f;
                    }
                    break;
            }
        } else {
            particle->unk08 = 0.0f;
        }
    }
    for (j = 0; j < 5; j++) {
        target = D_8010BFE8_hyper_hydrants[side][j];
        data = target->data;
        if (data->unk19 == 1) {
            if (D_8010BFAC_hyper_hydrants[side] > 0) {
                func_800E4C88_minigame(target, 2, target->trans.x, 100.0f, target->trans.z + 50.0f, 0.0f, 0.0f);
                if (data->unk18 == 1) {
                    data->unk1A = 1;
                }
                data->unk18++;
            }
            threshold = 15;
            if ((u16)D_800CDA7C_main[port] & A_BUTTON) {
                threshold = 30;
            }
            if (data->unk04 == 0 && data->unk18 >= threshold) {
                data->unk04 = 1;
                data->unk18 = 0;
            }
            data->unk19 = 0;
        } else {
            data->unk18 = 0;
        }
    }
}

void func_80108F34_hyper_hydrants(omObjData *object) {
    Vec position;
    Vec2f screen;
    s16 model;
    HyperHydrantsPlayerData *data;

    object->func = func_801091B0_hyper_hydrants;
    object->data = HuMemAllocTag(sizeof(HyperHydrantsPlayerData), TAG_OVERLAY);
    data = object->data;
    memset(data, 0, sizeof(HyperHydrantsPlayerData));
    data->unk00 = D_8010BF48_hyper_hydrants;
    data->unk03 = 0;
    data->unk14 = 0;
    if (data->unk00 == 0) {
        object->trans.x = -800.0f;
    } else {
        object->trans.x = 800.0f;
    }
    object->trans.y = 800.0f;
    object->trans.z = -700.0f;
    object->scale.x = object->scale.y = object->scale.z = 3.0f;
    position.x = object->trans.x;
    position.y = object->trans.y + 200.0f;
    position.z = object->trans.z;
    if (data->unk00 == 0) {
        func_80012B14_main(0, &position, &screen);
    } else {
        func_80012B14_main(1, &position, &screen);
    }
    D_8010BFA0_hyper_hydrants = screen.x;
    D_8010BFA4_hyper_hydrants = screen.y;
    model = object->model[0] = func_8000B108_main(0xA008A, 0x289);
    if (data->unk00 == 0) {
        HmfAnimRead(HmfModelData[model].hmf, 0xA008C, "c201n_00_DEF");
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    } else {
        HmfAnimLink(HmfModelData[model].hmf, 0, 0, "c201n_00_DEF");
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
    }
    func_8001C448_main(model);
    func_8001C514_main(model);
    object->model[1] = func_8000B108_main(0x2F0003, 0x99);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    data->unk0C = 0.1f;
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
    D_8010BF48_hyper_hydrants++;
}

void func_801091B0_hyper_hydrants(omObjData *object) {
    Vec position;
    Vec2f screen;
    HyperHydrantsPlayerData *data = object->data;
    HyperHydrantsPlayerData *otherData;

    switch (func_800E6E8C_minigame()) {
        case 0:
            if (data->unk00 == 0) {
                position.x = object->trans.x + 50.0f;
                position.y = object->trans.y + 120.0f;
                position.z = object->trans.z;
                func_80012B14_main(0, &position, &screen);
                D_8010BFA0_hyper_hydrants = screen.x;
                D_8010BFA4_hyper_hydrants = screen.y;
                if (data->unk03 == 0) {
                    object->trans.y -= 40.0f;
                    if (object->trans.y < 0.0f) {
                        func_8010BC80_hyper_hydrants(0x366, 0, 1, 0);
                        data->unk03 = 1;
                        omVibrate(0, 10, 0, 10);
                        omVibrate(1, 10, 0, 10);
                        omVibrate(2, 10, 0, 10);
                        omVibrate(3, 10, 0, 10);
                    }
                } else if (data->unk03 == 1) {
                    func_80109484_hyper_hydrants(object);
                }
                data->unk0C += 0.5f;
                if (data->unk0C > object->scale.x / 2.0f) {
                    data->unk0C = object->scale.x / 2.0f;
                }
            } else {
                otherData = D_8010BFE0_hyper_hydrants[0]->data;
                object->trans.y = D_8010BFE0_hyper_hydrants[0]->trans.y;
                data->unk0C = otherData->unk0C;
                data->unk03 = otherData->unk03;
                if (data->unk03 == 0 && object->trans.y < 0.0f) {
                    func_8010BC80_hyper_hydrants(0x366, 1, 1, 1);
                }
            }
            Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
            break;
        case 1:
            object->trans.y = 0;
            data->unk03 = 0;
            break;
        case 2:
            func_80109484_hyper_hydrants(object);
            break;
        case 3:
        case 4:
        case 5:
            object->scale.x -= 0.4f;
            if (object->scale.x < 0.0f) {
                object->scale.x = 0.0f;
            }
            object->scale.y = object->scale.z = object->scale.x;
            data->unk0C = object->scale.x / 2.0f;
            Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
            break;
    }
}

void func_80109484_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;

    if (data->unk03 == 1) {
        if (data->unk14 < 1080.0f) {
            object->trans.y = sindf(data->unk14) * 50.0f + 0.0f;
            data->unk14 += 45.0f;
            if ((s32)data->unk14 % 180 == 0) {
                data->unk14 += 180.0f;
            }
        } else {
            object->trans.y = 0.0f;
            data->unk14 = 0.0f;
            data->unk03 = 2;
        }
    }
}

void func_80109588_hyper_hydrants(omObjData *object) {
    s16 model;
    HyperHydrantsPlayerData *data;

    object->func = func_801099A0_hyper_hydrants;
    object->data = HuMemAllocTag(sizeof(HyperHydrantsPlayerData), TAG_OVERLAY);
    data = object->data;
    memset(data, 0, sizeof(HyperHydrantsPlayerData));
    if (D_8010BF4C_hyper_hydrants < 5) {
        data->unk02 = 0;
    } else {
        data->unk02 = 1;
    }
    data->unk00 = D_8010BF4C_hyper_hydrants % 5;
    data->unk10 = 50.0f;
    data->unk03 = rand8() >> 7;
    data->unk04 = 0;
    data->unk08 = (rand8() >> 5) * 15;
    data->unk18 = 0;
    data->unk19 = 0;
    data->unk14 = 0;
    data->unk05 = 0;
    data->unk06 = 2;
    data->unk0A = (rand8() >> 5) * 15;
    data->unk1A = 0;
    data->unk1E = 0;
    object->trans.x = D_8010BFE0_hyper_hydrants[data->unk02]->trans.x;
    object->trans.z = D_8010BFE0_hyper_hydrants[data->unk02]->trans.z;
    object->trans.y = 0;
    object->rot.x = object->rot.y = object->rot.z = object->trans.y;
    switch (D_8010BE38_hyper_hydrants[D_8010C010_hyper_hydrants][data->unk00]) {
        case 0:
            object->scale.x = object->scale.y = object->scale.z = 1.0f;
            data->unk0C = 0.5f;
            data->unk01 = 1;
            break;
        case 1:
            object->scale.x = object->scale.y = object->scale.z = 1.25f;
            data->unk0C = 0.625f;
            data->unk01 = 2;
            break;
        case 2:
        default:
            object->scale.x = object->scale.y = object->scale.z = 1.5f;
            data->unk0C = 0.75f;
            data->unk01 = 3;
            break;
    }
    model = object->model[0] = func_8000B108_main(0x2F0002, 9);
    if (D_8010BF4C_hyper_hydrants == 0) {
        HmfAnimRead(HmfModelData[model].hmf, 0xA008C, "c201n_00_DEF");
    } else {
        HmfAnimLink(HmfModelData[model].hmf, 0, 0, "c201n_00_DEF");
    }
    func_8001C448_main(model);
    func_8001C514_main(model);
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->model[1] = func_8000B108_main(0x2F0003, 0x99);
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
    func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    object->model[2] = func_8000B108_main(0x2F000C, 0xA59);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    if (data->unk02 == 0) {
        Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
        Hu3DModelCameraSet(object->model[1], HU3D_CAM0);
        Hu3DModelCameraSet(object->model[2], HU3D_CAM0);
    } else {
        Hu3DModelCameraSet(object->model[0], HU3D_CAM1);
        Hu3DModelCameraSet(object->model[1], HU3D_CAM1);
        Hu3DModelCameraSet(object->model[2], HU3D_CAM1);
    }
    D_8010BF4C_hyper_hydrants++;
}

void func_801099A0_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;

    switch (func_800E6E8C_minigame()) {
        case 0:
            func_80109B30_hyper_hydrants(object);
            break;
        case 1:
            object->trans.y = 0;
            break;
        case 2:
            func_80109E44_hyper_hydrants(object);
            if (data->unk04 == 1) {
                func_8010A458_hyper_hydrants(object);
            }
            if (data->unk1A == 1) {
                if (data->unk1E >= 2) {
                    data->unk1E = 0;
                    data->unk1A = 0;
                } else {
                    if (data->unk1E == 0) {
                        data->unk1C = func_8010BC80_hyper_hydrants(0x365, data->unk02, 0, 0);
                    }
                    data->unk1E++;
                }
            }
            break;
        case 3:
            object->scale.x -= 0.1f;
            if (object->scale.x < 0.0f) {
                object->scale.x = 0.0f;
            }
            object->scale.y = object->scale.z = object->scale.x;
            data->unk0C = object->scale.x / 2.0f;
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0, object->trans.z);
    Hu3DModelScaleSet(object->model[1], data->unk0C, data->unk0C, data->unk0C);
}

void func_80109B30_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;
    s32 angle = 0;

    if (D_8010BFE0_hyper_hydrants[data->unk02]->trans.y > 0.0f) {
        return;
    }
    if (data->unk14 == 0.0f) {
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    } else if (data->unk14 < 720.0f) {
        angle = (s32)data->unk14 % 360;
        object->trans.y = sindf(data->unk14) * 200.0f;
    } else {
        object->trans.y = 0.0f;
    }
    switch (data->unk00) {
        case 0:
            object->trans.z += 6.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 8.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 1:
            object->trans.x -= 1.5f;
            object->trans.z += 8.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 10.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 2:
            object->trans.x += 1.5f;
            object->trans.z += 8.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 10.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        case 3:
            object->trans.x -= 1.5f;
            object->trans.z += 5.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 6.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
        default:
            object->trans.x += 1.5f;
            object->trans.z += 5.0f;
            if (data->unk14 < 720.0f) {
                data->unk14 += 6.0f;
                if (angle >= 180) {
                    data->unk14 += 180.0f;
                }
            }
            break;
    }
}

void func_80109E44_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;
    Vec position;
    Vec2f screen;

    if (data->unk01 == 0) {
        if ((u16)(func_800E6E9C_minigame() % 60) == 0) {
            if (D_8010BE68_hyper_hydrants[data->unk02] != 0) {
                return;
            }
            func_8010A2D4_hyper_hydrants(object);
            func_8010BC80_hyper_hydrants(0x365, data->unk02, 0, 0);
            D_8010BE68_hyper_hydrants[data->unk02] = 1;
            ((HyperHydrantsPlayerData *)D_8010BFE0_hyper_hydrants[data->unk02]->data)->unk03 = 1;
        } else {
            D_8010BE68_hyper_hydrants[data->unk02] = 0;
            return;
        }
    } else if (data->unk05 == 1) {
        object->scale.x += 0.05f;
        switch (data->unk01) {
            case 1:
                if (object->scale.x > 1.0f) {
                    object->scale.x = 1.0f;
                    data->unk05 = 0;
                }
                break;
            case 2:
                if (object->scale.x > 1.25f) {
                    object->scale.x = 1.25f;
                    data->unk05 = 0;
                }
                break;
            case 3:
                if (object->scale.x > 1.5f) {
                    object->scale.x = 1.5f;
                    data->unk05 = 0;
                }
                break;
        }
        object->scale.y = object->scale.z = object->scale.x;
        data->unk0C = object->scale.x / 2.0f;
    }
    if (data->unk06 == 2) {
        object->trans.z += 2.0f;
        if (object->trans.z > -500.0f) {
            data->unk06 = 0;
        }
    } else if (data->unk0A == 0) {
        data->unk0A = (rand8() >> 5) * 15;
        if ((rand8() >> 7) == 0) {
            data->unk06 ^= 1;
        }
    } else {
        data->unk0A--;
        if (data->unk06 == 0) {
            if (object->trans.z > -200.0f) {
                data->unk06 ^= 1;
            }
        } else if (data->unk06 == 1) {
            if (object->trans.z < -500.0f) {
                data->unk06 ^= 1;
            }
        }
    }
    if (data->unk06 == 0) {
        object->trans.z += 3.0f;
    } else if (data->unk06 == 1) {
        object->trans.z -= 3.0f;
    }
    if (data->unk08 == 0) {
        data->unk03 ^= 1;
        data->unk08 = (rand8() >> 5) * 15;
    } else {
        data->unk08--;
        position.x = object->trans.x;
        position.y = object->trans.y;
        position.z = object->trans.z;
        if (data->unk02 == 0) {
            Hu3DCam3DToScreen(0, &position, &screen);
            if (data->unk03 == 0 && screen.x < 119.0f) {
                data->unk03 ^= 1;
            } else if (data->unk03 == 1 && screen.x > 225.0f) {
                data->unk03 ^= 1;
            }
        } else {
            Hu3DCam3DToScreen(1, &position, &screen);
            if (data->unk03 == 0 && screen.x < 95.0f) {
                data->unk03 ^= 1;
            } else if (data->unk03 == 1 && screen.x > 201.0f) {
                data->unk03 ^= 1;
            }
        }
    }
    if (data->unk03 != 0) {
        object->trans.x += 4.0f;
    } else {
        object->trans.x -= 4.0f;
    }
}

void func_8010A2D4_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;
    s8 index;
    s8 type;

    index = D_8010BE10_hyper_hydrants[data->unk02]++;
    if (index >= 16) {
        index %= 16;
    }
    type = D_8010BE38_hyper_hydrants[D_8010C010_hyper_hydrants][index];
    data->unk10 = 50.0f;
    data->unk18 = 0;
    data->unk1A = 0;
    data->unk05 = 1;
    data->unk06 = 2;
    object->trans.x = D_8010BFE0_hyper_hydrants[data->unk02]->trans.x;
    object->trans.z = D_8010BFE0_hyper_hydrants[data->unk02]->trans.z;
    object->trans.y = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.1f;
    switch (type) {
        case 0:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 1;
            break;
        case 1:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 2;
            break;
        case 2:
        default:
            data->unk0C = object->scale.x / 2.0f;
            data->unk01 = 3;
            break;
    }
}

void func_8010A458_hyper_hydrants(omObjData *object) {
    HyperHydrantsPlayerData *data = object->data;

    switch (data->unk01) {
        case 3:
            if (object->scale.x <= 1.25f) {
                data->unk0C = 1.25f;
                object->scale.x = object->scale.y = object->scale.z = 1.25f;
                data->unk04 = 0;
                data->unk01--;
            } else {
                object->scale.x -= 0.05f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
        case 2:
            if (object->scale.x <= 1.0f) {
                data->unk0C = 1.0f;
                object->scale.x = object->scale.y = object->scale.z = 1.0f;
                data->unk04 = 0;
                data->unk01--;
            } else {
                object->scale.x -= 0.05f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
        case 1:
            if (object->scale.x <= 0.0f) {
                object->trans.z = D_8010BFE0_hyper_hydrants[data->unk02]->trans.z;
                data->unk0C = data->unk10 = 0.0f;
                object->scale.x = object->scale.y = object->scale.z = 0.0f;
                data->unk04 = 0;
                data->unk01--;
                if (data->unk02 == 0) {
                    D_8010BE24_hyper_hydrants++;
                    func_8010BC80_hyper_hydrants(0x364, data->unk02, 1, D_8010BFAA_hyper_hydrants);
                } else {
                    D_8010BE25_hyper_hydrants++;
                    func_8010BC80_hyper_hydrants(0x364, data->unk02, 1, D_8010BFAB_hyper_hydrants);
                }
                if (data->unk02 == 0) {
                    omVibrate(D_8010BFA8_hyper_hydrants, 2, 3, 10);
                    omVibrate(D_8010BFAA_hyper_hydrants, 2, 3, 10);
                } else {
                    omVibrate(D_8010BFA9_hyper_hydrants, 2, 3, 10);
                    omVibrate(D_8010BFAB_hyper_hydrants, 2, 3, 10);
                }
            } else {
                object->scale.x -= 0.1f;
                object->scale.y = object->scale.z = data->unk0C = object->scale.x;
            }
            break;
    }
}

void func_8010A68C_hyper_hydrants(omObjData *object) {
    omObjData *player;
    func_800E1BA8_minigame_ObjData *playerData;
    HyperHydrantsCharacterData *characterData;
    Vec step;
    f32 x;
    f32 z;
    s32 side;
    s32 i;
    s32 playerIndex;

    side = 1;
    object->func = func_8010AB34_hyper_hydrants;
    if (D_8010BF50_hyper_hydrants == 0) {
        object->work[0] = 0;
        playerIndex = D_8010BFA8_hyper_hydrants;
        side = 0;
    } else {
        object->work[0] = side;
        playerIndex = D_8010BFA9_hyper_hydrants;
    }
    player = D_800EC598_minigame[playerIndex];
    D_8010C028_hyper_hydrants[side].x = player->trans.x - 25.0f - 18.75f;
    D_8010C028_hyper_hydrants[side].y = 37.5f;
    playerData = player->data;
    if ((D_800A178C_main[GwPlayer[playerData->unk59].chr][0] >> 16) == 6) {
        D_8010C028_hyper_hydrants[side].z = player->trans.z + 50.0f + 18.75f + 48.7f;
    } else {
        D_8010C028_hyper_hydrants[side].z = player->trans.z + 50.0f + 18.75f;
    }
    object->scale.x = object->scale.y = object->scale.z = 1.6f;
    if (object->work[0] == 0) {
        player = D_800EC598_minigame[D_8010BFAA_hyper_hydrants];
    } else {
        player = D_800EC598_minigame[D_8010BFAB_hyper_hydrants];
    }
    playerData = player->data;
    characterData = playerData->unk158;
    x = player->trans.x + characterData->unk08 * 60.0f;
    z = player->trans.z + characterData->unk0C * 60.0f;
    step.x = ((D_8010C028_hyper_hydrants[side].x - x > 0.0f) ? D_8010C028_hyper_hydrants[side].x - x : 0.0f - (D_8010C028_hyper_hydrants[side].x - x)) / 5.0f;
    step.y = -8.5f;
    step.z = ((D_8010C028_hyper_hydrants[side].z - z > 0.0f) ? D_8010C028_hyper_hydrants[side].z - z : 0.0f - (D_8010C028_hyper_hydrants[side].z - z)) / 5.0f;
    for (i = 0; i < 6; i++) {
        object->model[i] = func_8000B108_main(0x2F0008, 0x899);
        Hu3DModelScaleSet(object->model[i], object->scale.x, object->scale.y, object->scale.z);
        D_8010BFB0_hyper_hydrants[side][i] = HuMemAllocTag(sizeof(HyperHydrantsChainPoint), TAG_OVERLAY);
        if (side == 0) {
            Hu3DModelCameraSet(object->model[i], HU3D_CAM0);
        } else {
            Hu3DModelCameraSet(object->model[i], HU3D_CAM1);
        }
        D_8010BFB0_hyper_hydrants[side][i]->position.x = x + i * step.x;
        D_8010BFB0_hyper_hydrants[side][i]->position.y = i * step.y + 80.0f;
        D_8010BFB0_hyper_hydrants[side][i]->position.z = z + i * step.z;
        if (i == 0) {
            object->trans.x = D_8010BFB0_hyper_hydrants[side][i]->position.x;
            object->trans.y = D_8010BFB0_hyper_hydrants[side][i]->position.y;
            object->trans.z = D_8010BFB0_hyper_hydrants[side][i]->position.z;
        }
        Hu3DModelPosSet(object->model[i], D_8010BFB0_hyper_hydrants[side][i]->position.x, D_8010BFB0_hyper_hydrants[side][i]->position.y, D_8010BFB0_hyper_hydrants[side][i]->position.z);
    }
    D_8010BF50_hyper_hydrants++;
}

void func_8010AB34_hyper_hydrants(omObjData *object) {
    omObjData *player;
    func_800E1BA8_minigame_ObjData *playerData;
    HyperHydrantsCharacterData *characterData;
    Vec step;
    f32 x;
    f32 z;
    s32 side;
    s32 i;
    s32 playerIndex;

    switch (func_800E6E8C_minigame()) {
        case 0:
        case 1:
            break;
        case 2:
            if (object->work[0] == 0) {
                playerIndex = D_8010BFAA_hyper_hydrants;
                side = 0;
            } else {
                playerIndex = D_8010BFAB_hyper_hydrants;
                side = 1;
            }
            player = D_800EC598_minigame[playerIndex];
            playerData = player->data;
            characterData = playerData->unk158;
            x = player->trans.x + characterData->unk08 * 60.0f;
            z = player->trans.z + characterData->unk0C * 60.0f;
            step.x = ((D_8010C028_hyper_hydrants[side].x - x > 0.0f) ? D_8010C028_hyper_hydrants[side].x - x : 0.0f - (D_8010C028_hyper_hydrants[side].x - x)) / 5.0f;
            step.y = -8.5f;
            step.z = ((D_8010C028_hyper_hydrants[side].z - z > 0.0f) ? D_8010C028_hyper_hydrants[side].z - z : 0.0f - (D_8010C028_hyper_hydrants[side].z - z)) / 5.0f;
            for (i = 0; i < 6; i++) {
                D_8010BFB0_hyper_hydrants[side][i]->position.x = x + i * step.x;
                D_8010BFB0_hyper_hydrants[side][i]->position.y = i * step.y + 80.0f;
                D_8010BFB0_hyper_hydrants[side][i]->position.z = z + i * step.z;
                if (i == 0) {
                    object->trans.x = D_8010BFB0_hyper_hydrants[side][i]->position.x;
                    object->trans.y = D_8010BFB0_hyper_hydrants[side][i]->position.y;
                    object->trans.z = D_8010BFB0_hyper_hydrants[side][i]->position.z;
                }
                Hu3DModelPosSet(object->model[i], D_8010BFB0_hyper_hydrants[side][i]->position.x, D_8010BFB0_hyper_hydrants[side][i]->position.y, D_8010BFB0_hyper_hydrants[side][i]->position.z);
            }
            break;
        case 3:
        case 4:
        case 5:
            for (i = 0; i < 6; i++) {
                func_8001C258_main(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

void func_8010AE08_hyper_hydrants(omObjData *object) {
    HuSprite *sprites[2];
    HyperHydrantsMaskData *data;
    s32 i;
    u8 *first;
    u8 *second;
    f32 x;
    f32 y;
    f32 dx;
    f32 dy;
    f32 distance;
    f32 step;

    object->func = func_8010B2FC_hyper_hydrants;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    D_8010BF56_hyper_hydrants = func_8000B838_main(0x2F0009);
    D_8010BF58_hyper_hydrants = HuSprGrpCreate(1, 0);
    func_80055024_main(D_8010BF58_hyper_hydrants, 0, D_8010BF56_hyper_hydrants, 0);
    HuSprPriSet(D_8010BF58_hyper_hydrants, 0, 0x10);
    HuSprAttrReset(D_8010BF58_hyper_hydrants, 0, 0xFFFF);
    HuSprAttrSet(D_8010BF58_hyper_hydrants, 0, 0x1000);
    HuSprPosSet(D_8010BF58_hyper_hydrants, 0, 160, 120);
    for (i = 0; i < 2; i++) {
        D_8010BF52_hyper_hydrants = func_8000B838_main(0x2F0000);
        D_8010BF88_hyper_hydrants = HuSprGrpCreate(1, 0);
        func_80055024_main(D_8010BF88_hyper_hydrants, 0, D_8010BF52_hyper_hydrants, 0);
        HuSprAttrReset(D_8010BF88_hyper_hydrants, 0, 0xFFFF);
        if (i == 0) {
            HuSprAttrSet(D_8010BF88_hyper_hydrants, 0, 0x5000);
            HuSprPosSet(D_8010BF88_hyper_hydrants, 0, 80, 120);
        } else {
            HuSprAttrSet(D_8010BF88_hyper_hydrants, 0, 0x5001);
            HuSprPosSet(D_8010BF88_hyper_hydrants, 0, 240, 120);
        }
    }
    data = object->data = HuMemAllocTag(sizeof(HyperHydrantsMaskData), TAG_OVERLAY);
    memset(data, 0, sizeof(HyperHydrantsMaskData));
    data->unk03 = 1;
    data->unk04 = 0;
    data->unk08 = 0.5f;
    func_800E1370_minigame(object, 2, 0.0f);
    for (i = 0; i < 2; i++) {
        D_8010BF54_hyper_hydrants = func_8000B838_main(0x2F0001);
        D_8010BF8A_hyper_hydrants[i] = HuSprGrpCreate(1, 0);
        func_80055024_main(D_8010BF8A_hyper_hydrants[i], 0, D_8010BF54_hyper_hydrants, 0);
        HuSprPriSet(D_8010BF58_hyper_hydrants, 0, 0x20);
        HuSprAttrReset(D_8010BF8A_hyper_hydrants[i], 0, 0xFFFF);
        if (i == 0) {
            HuSprAttrSet(D_8010BF8A_hyper_hydrants[0], 0, 0x1000);
            HuSprPosSet(D_8010BF8A_hyper_hydrants[0], 0, 80, 120);
        } else {
            HuSprAttrSet(D_8010BF8A_hyper_hydrants[i], 0, 0x1001);
            HuSprPosSet(D_8010BF8A_hyper_hydrants[i], 0, 240, 120);
        }
        sprites[i] = HuSprGet(D_8010BF8A_hyper_hydrants[i], 0);
        D_8010BF94_hyper_hydrants[i] = sprites[i]->unk_84->unk00->unk00;
    }
    D_8010BF8E_hyper_hydrants = sprites[0]->unk_84->unk14;
    D_8010BF90_hyper_hydrants = sprites[0]->unk_84->unk16;
    D_8010BF9C_hyper_hydrants = 35;
    step = 35.0f / 255.0f;
    first = D_8010BF94_hyper_hydrants[0];
    second = D_8010BF94_hyper_hydrants[1];
    for (y = 0.0f; y < D_8010BF90_hyper_hydrants; y++) {
        for (x = 0.0f; x < D_8010BF8E_hyper_hydrants; x++, first++, second++) {
            dx = x - D_8010BFA0_hyper_hydrants;
            dy = y - D_8010BFA4_hyper_hydrants;
            distance = HuSqrtf(dx * dx + dy * dy);
            if (distance > D_8010BF9C_hyper_hydrants) {
                *first = *second = 255;
            } else {
                *first = *second = (u32)(distance / step);
            }
        }
    }
    HuSprTPLvlSet(D_8010BF8A_hyper_hydrants[0], 0, 240);
    HuSprTPLvlSet(D_8010BF8A_hyper_hydrants[1], 0, 240);
}

void func_8010B2FC_hyper_hydrants(omObjData *object) {
    if (func_800E6E8C_minigame() == 0) {
        if (D_8010BFE0_hyper_hydrants[0]->trans.y > 0.0f) {
            func_8010B38C_hyper_hydrants();
        } else if (D_8010BF9C_hyper_hydrants < 240) {
            D_8010BF9C_hyper_hydrants += 3;
            func_8010B38C_hyper_hydrants();
        } else {
            D_8010BF9C_hyper_hydrants = 240;
        }
    }
}

void func_8010B38C_hyper_hydrants(void) {
    HyperHydrantsPlayerData *data;
    f32 innerRadius;
    f32 step;
    s32 endRow;
    u8 *first;
    u8 *second;
    s32 row;
    s32 column;
    f32 x;
    f32 y;
    f32 distance;
    u8 alpha;

    data = D_8010BFE0_hyper_hydrants[0]->data;
    if (data->unk03 == 2) {
        D_8010BE6A_hyper_hydrants = 1;
    }
    innerRadius = D_8010BF9C_hyper_hydrants * 0.8f;
    step = D_8010BF9C_hyper_hydrants * 0.2f / 255.0f;
    endRow = D_8010BFA4_hyper_hydrants + D_8010BF9C_hyper_hydrants;
    first = D_8010BF94_hyper_hydrants[0];
    second = D_8010BF94_hyper_hydrants[1];
    for (row = 0; row < D_8010BF90_hyper_hydrants; row++) {
        if (data->unk03 == 1) {
            if (row > D_8010BF90_hyper_hydrants / 2) {
                break;
            }
        } else if (row > endRow) {
            break;
        }
        for (column = 0; column < D_8010BF8E_hyper_hydrants; column++, first++, second++) {
            if (D_8010BE6A_hyper_hydrants && *first == 0) {
                continue;
            }
            x = column - D_8010BFA0_hyper_hydrants;
            y = row - D_8010BFA4_hyper_hydrants;
            distance = HuSqrtf(x * x + y * y);
            if (distance <= innerRadius) {
                if (*first != 0) {
                    *second = 0;
                    *first = 0;
                }
            } else if (distance > D_8010BF9C_hyper_hydrants) {
                if ((~*first & 0xFF) != 0) {
                    *second = 255;
                    *first = 255;
                }
            } else {
                alpha = (u32)((distance - innerRadius) / step);
                if (alpha != *first) {
                    *second = alpha;
                    *first = alpha;
                }
            }
        }
    }
}

void func_8010B658_hyper_hydrants(omObjData *object) {
    s16 positions[2][2] = { { 35, 32 }, { 252, 32 } };
    s16 sprite;
    s16 i;
    s16 j;

    sprite = func_8000B838_main(0x2F000A);
    for (i = 0; i < 2; i++) {
        D_8010C012_hyper_hydrants[i] = espEntry(sprite, 0, 1);
        espPosSet(D_8010C012_hyper_hydrants[i], positions[i][0], positions[i][1]);
        espDispOff(D_8010C012_hyper_hydrants[i]);
    }
    sprite = func_8000B838_main(0x21001B);
    for (i = 0; i < 2; i++) {
        D_8010C016_hyper_hydrants[i] = espEntry(sprite, 0, 1);
        espPosSet(D_8010C016_hyper_hydrants[i], positions[i][0] + 12, positions[i][1]);
        espDispOff(D_8010C016_hyper_hydrants[i]);
    }
    sprite = func_8000B838_main(0x31);
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            D_8010C01A_hyper_hydrants[i][j] = espEntry(sprite, 0, 1);
            espPosSet(D_8010C01A_hyper_hydrants[i][j], D_8010BE14_hyper_hydrants[i][j][0], D_8010BE14_hyper_hydrants[i][j][1]);
            espDispOff(D_8010C01A_hyper_hydrants[i][j]);
        }
    }
    object->func = func_8010B8B0_hyper_hydrants;
}

void func_8010B8B0_hyper_hydrants(omObjData *object) {
    s32 i;
    s32 j;

    switch (func_800E6E8C_minigame()) {
        case 2:
        case 3:
            if (D_8010BE24_hyper_hydrants < 10) {
                espDispOn(D_8010C01A_hyper_hydrants[0][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][0], (s8)(D_8010BE24_hyper_hydrants % 10));
                espPosSet(D_8010C01A_hyper_hydrants[0][0], D_8010BE14_hyper_hydrants[0][0][0], D_8010BE14_hyper_hydrants[0][0][1]);
                espDispOff(D_8010C01A_hyper_hydrants[0][1]);
            } else {
                espDispOn(D_8010C01A_hyper_hydrants[0][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][0], (s8)(D_8010BE24_hyper_hydrants / 10));
                espPosSet(D_8010C01A_hyper_hydrants[0][0], D_8010BE14_hyper_hydrants[0][0][0], D_8010BE14_hyper_hydrants[0][0][1]);
                espDispOn(D_8010C01A_hyper_hydrants[0][1]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[0][1], (s8)(D_8010BE24_hyper_hydrants % 10));
                espPosSet(D_8010C01A_hyper_hydrants[0][1], D_8010BE14_hyper_hydrants[0][1][0], D_8010BE14_hyper_hydrants[0][1][1]);
            }
            if (D_8010BE25_hyper_hydrants < 10) {
                espDispOn(D_8010C01A_hyper_hydrants[1][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][0], (s8)(D_8010BE25_hyper_hydrants % 10));
                espPosSet(D_8010C01A_hyper_hydrants[1][0], D_8010BE14_hyper_hydrants[1][0][0], D_8010BE14_hyper_hydrants[1][0][1]);
                espDispOff(D_8010C01A_hyper_hydrants[1][1]);
            } else {
                espDispOn(D_8010C01A_hyper_hydrants[1][0]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][0], (s8)(D_8010BE25_hyper_hydrants / 10));
                espPosSet(D_8010C01A_hyper_hydrants[1][0], D_8010BE14_hyper_hydrants[1][0][0], D_8010BE14_hyper_hydrants[1][0][1]);
                espDispOn(D_8010C01A_hyper_hydrants[1][1]);
                func_8000BD50_main(D_8010C01A_hyper_hydrants[1][1], (s8)(D_8010BE25_hyper_hydrants % 10));
                espPosSet(D_8010C01A_hyper_hydrants[1][1], D_8010BE14_hyper_hydrants[1][1][0], D_8010BE14_hyper_hydrants[1][1][1]);
            }
            for (i = 0; i < 2; i++) {
                espDispOn(D_8010C012_hyper_hydrants[i]);
                espDispOn(D_8010C016_hyper_hydrants[i]);
            }
            break;
        default:
            for (i = 0; i < 2; i++) {
                espDispOff(D_8010C012_hyper_hydrants[i]);
                espDispOff(D_8010C016_hyper_hydrants[i]);
                for (j = 0; j < 2; j++) {
                    espDispOff(D_8010C01A_hyper_hydrants[i][j]);
                }
            }
            break;
    }
}

s16 func_8010BC80_hyper_hydrants(s16 soundId, s16 side, s8 playerSound, s16 player) {
    s16 sound;

    if (playerSound) {
        sound = func_8004AC98_main(soundId, player);
    } else {
        sound = HuAudFXPlay(soundId);
    }
    if (side == 0) {
        HuAudFXPanning(sound, 0x20);
    } else {
        HuAudFXPanning(sound, 0x60);
    }
    return sound;
}

void func_8010BD14_hyper_hydrants(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 length;

    arg0->x = arg2->x - arg1->x;
    arg0->y = arg2->y - arg1->y;
    arg0->z = arg2->z - arg1->z;
    length = arg0->x * arg0->x;
    length += arg0->y * arg0->y;
    length += arg0->z * arg0->z;
    length = HuSqrtf(length);
    if (length != 0.0f) {
        arg0->x /= length;
        arg0->y /= length;
        arg0->z /= length;
    } else {
        arg0->x = arg0->y = arg0->z = 0.0f;
    }
}
