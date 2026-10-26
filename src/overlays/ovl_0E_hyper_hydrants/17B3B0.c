#include "common.h"
#include "overlays/minigame.h"

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

extern s8 D_8010BE24_hyper_hydrants;
extern s8 D_8010BE25_hyper_hydrants;
extern s8 D_8010BFA8_hyper_hydrants;
extern s8 D_8010BFA9_hyper_hydrants;
extern s8 D_8010BFAA_hyper_hydrants;
extern s8 D_8010BFAB_hyper_hydrants;
extern s16 D_800EB932_minigame;
extern f32 D_8010BE28_hyper_hydrants;
extern f32 D_8010BE2C_hyper_hydrants;
extern s8 D_8010BE10_hyper_hydrants[];
extern s8 D_8010BE38_hyper_hydrants[][16];
extern omObjData *D_8010BFE0_hyper_hydrants[];
extern s8 D_8010C010_hyper_hydrants;

s16 func_8010BC80_hyper_hydrants(s16 soundId, s16 side, s8 playerSound, s16 player);
void func_8004AE00_main(s16 arg0, s16 arg1);
void func_8000B710_main(s32 arg0);
void func_80105EB0_hyper_hydrants(s8 camera);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801059A0_hyper_hydrants);

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

void func_80105D44_hyper_hydrants(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801060F8_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80106238_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80106A50_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80107238_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801078B8_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80107A90_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801083A8_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108788_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80108F34_hyper_hydrants);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", D_8010BEF0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801091B0_hyper_hydrants);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109588_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_801099A0_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109B30_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_80109E44_hyper_hydrants);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010A68C_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010AB34_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010AE08_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B2FC_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B38C_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B658_hyper_hydrants);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", func_8010B8B0_hyper_hydrants);

s16 func_8010BC80_hyper_hydrants(s16 soundId, s16 side, s8 playerSound, s16 player) {
    s16 sound;

    if (playerSound) {
        sound = func_8004AC98_main(soundId, player);
    } else {
        sound = HuAudFXPlay(soundId);
    }
    if (side == 0) {
        func_8004AE00_main(sound, 0x20);
    } else {
        func_8004AE00_main(sound, 0x60);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_0E_hyper_hydrants/17B3B0", D_8010BF30_hyper_hydrants);
