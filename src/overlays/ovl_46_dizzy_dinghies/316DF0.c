#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/object.h"
#include "game/wipe.h"
#include "humath.h"
#include "math.h"
#include "overlays/minigame.h"

extern u8 D_800D6A90_main;

extern Vec D_80109740_dizzy_dinghies[];
extern Vec D_80109788_dizzy_dinghies;
extern f32 D_801097B0_dizzy_dinghies;
extern f32 D_801097B4_dizzy_dinghies;
extern f32 D_801097B8_dizzy_dinghies;
extern f32 D_801097BC_dizzy_dinghies;
extern f32 D_801097C0_dizzy_dinghies;
extern f32 D_801097C4_dizzy_dinghies;
extern f32 D_801097C8_dizzy_dinghies;
extern f32 D_801097CC_dizzy_dinghies;
extern f32 D_801097D0_dizzy_dinghies;
extern s32 D_801097D4_dizzy_dinghies;
extern f32 D_801097E0_dizzy_dinghies;
extern s32 D_801097E8_dizzy_dinghies;
extern f32 D_80109770_dizzy_dinghies;
extern f32 D_80109778_dizzy_dinghies;
extern f32 D_80109780_dizzy_dinghies;
extern f32 D_80109784_dizzy_dinghies;
extern Vec D_801097A0_dizzy_dinghies;
extern f32 D_801097AC_dizzy_dinghies;
extern Vec D_80109794_dizzy_dinghies;
extern s32 D_80109E3C_dizzy_dinghies;
extern s32 D_80109E40_dizzy_dinghies;
extern Vec D_80109E44_dizzy_dinghies[][3];
extern s32 D_801097EC_dizzy_dinghies;
extern Vec D_801097F0_dizzy_dinghies[];
extern Vec D_801098BC_dizzy_dinghies[];
extern s8 D_80109988_dizzy_dinghies[];
extern Vec D_8010999C_dizzy_dinghies[];
extern Vec D_80109A80_dizzy_dinghies[];
extern s8 D_80109B64_dizzy_dinghies[];
extern Vec D_80109B78_dizzy_dinghies[];
extern Vec D_80109C50_dizzy_dinghies[];
extern s8 D_80109D28_dizzy_dinghies[];
extern D_80111B50_vine_with_me_Struct D_80109D3C_dizzy_dinghies;
extern f32 D_80109D70_dizzy_dinghies;
extern f32 D_80109D74_dizzy_dinghies;
extern f32 D_80109D78_dizzy_dinghies;
extern f32 D_80109D7C_dizzy_dinghies;
extern f32 D_80109D80_dizzy_dinghies;
extern s16 D_80109E08_dizzy_dinghies[20];
extern s32 D_80109E30_dizzy_dinghies;
extern s32 D_80109E34_dizzy_dinghies;
extern s32 D_8010A020_dizzy_dinghies;
extern Vec D_8010A028_dizzy_dinghies[20];

void func_80105EB4_dizzy_dinghies(omObjData *object);
void func_80106970_dizzy_dinghies(omObjData *object);
void func_80107738_dizzy_dinghies(omObjData *object, u16 player);
void func_80108E30_dizzy_dinghies(Vec *origin, Vec *p, Vec *q, Vec *out);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801059A0_dizzy_dinghies);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80105EB4_dizzy_dinghies);

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
    if (func_800E6E8C_minigame() == 0) {
        if (time == 60) {
            func_8001C814_main(object->model[2], 1, 0);
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
        func_8001C258_main(object->model[3], 4, 4);
        func_8001C258_main(object->model[2], 4, 4);
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
        func_8001C258_main(object->model[i + 9], 4, 4);
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
                        func_8001C258_main(object->model[count0 + 9], 4, 0);
                        count0++;
                    }
                    break;
                case 1:
                    if (count1 < 5) {
                        Hu3DModelPosSet(object->model[count1 + 19], x, y, z);
                        Hu3DModelRotSet(object->model[count1 + 19], rotX, rotY, rotZ);
                        Hu3DModelScaleSet(object->model[count1 + 19], 1.5f, 1.5f, 1.5f);
                        func_8001C258_main(object->model[count1 + 19], 4, 0);
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
                        func_8001C258_main(object->model[count2 + 29], 4, 0);
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
    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    time = func_800E6E9C_minigame();
    switch (func_800E6F40_minigame()) {
        case 0:
            if (time == 5) {
                HuAudFXPlay(0x424);
                D_801097E8_dizzy_dinghies = func_8004AC98_main(D_8010A020_dizzy_dinghies + 0x428, 0);
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
                func_8004AEF0_main(D_801097E8_dizzy_dinghies, 30);
                D_801097E8_dizzy_dinghies = -1;
            }
            if (time == 1) {
                D_80109778_dizzy_dinghies -= 0.025f;
            }
            D_801097E0_dizzy_dinghies *= 0.95f;
            D_80109D3C_dizzy_dinghies.unk06 = 9;
        case 4:
            if (D_800EB934_minigame == 1) {
                if (D_801097D4_dizzy_dinghies == 0) {
                    HuAudSeqPlay(0x6B);
                } else if (D_80109D3C_dizzy_dinghies.unk04 == 1) {
                    HuAudSeqPlay(0x6A);
                } else {
                    HuAudSeqPlay(0x65);
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_80105D64_dizzy_dinghies;
            func_8004AB0C_main(30);
            break;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        work = D_800EC598_minigame[i]->data;
        work->unk60 = CRot.y;
    }
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        object->func = func_80105D64_dizzy_dinghies;
    }
    func_80106970_dizzy_dinghies(object);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107098_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107738_dizzy_dinghies);

void func_80107DE8_dizzy_dinghies(omObjData *object) {
    func_80107738_dizzy_dinghies(object, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80107E04_dizzy_dinghies);

s32 func_80108488_dizzy_dinghies(omObjData *object, s16 value) {
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

void func_80108514_dizzy_dinghies(omObjData *object, f32 arg1, Vec *out) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801085F4_dizzy_dinghies);

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
    func_800202FC_main(out);
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
    func_800202FC_main(&normal);
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
    if (func_800E6E8C_minigame() == 2) {
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
            func_800202FC_main(&D_801097A0_dizzy_dinghies);
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
    frameSprite = func_8000B838_main(0x670008);
    func_8000B838_main(0x440014);
    func_8000B838_main(0x440015);
    data = DataRead(0x440013);
    HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 1; i++) {
        sprite = espEntry(frameSprite, 0, 1);
        espDispOn(sprite);
        espPosSet(sprite, pos[0], pos[1]);
        espPriSet(sprite, 0xFFFF);
        espTPLvlSet(sprite, 200);
        sprite = espEntry(func_8000B838_main((GwPlayer[i].chr + 8) | 0x210000), 0, 1);
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
    if (inside == 1 && func_800E6E8C_minigame() == 2) {
        func_800E6F0C_minigame(3);
        D_801097D4_dizzy_dinghies = inside;
        D_80109E40_dizzy_dinghies = HuAudFXPlay(0x425);
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109EF0_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F04_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F14_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F24_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F3C_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F50_dizzy_dinghies);
