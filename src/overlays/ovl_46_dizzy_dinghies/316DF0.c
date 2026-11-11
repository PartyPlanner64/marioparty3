#include "common.h"
#include "game/hmfcoll.h"
#include "game/object.h"
#include "game/wipe.h"
#include "humath.h"
#include "math.h"
#include "overlays/minigame.h"

typedef struct DizzyDinghiesWork {
    /* 0x000 */ char unk00[0x3C];
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ f32 unk40;
    /* 0x044 */ char unk44[0x118];
} DizzyDinghiesWork; // size 0x15C

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
extern s32 D_801097EC_dizzy_dinghies;
extern f32 D_80109D80_dizzy_dinghies;
extern s16 D_80109E08_dizzy_dinghies[20];
extern s32 D_80109E30_dizzy_dinghies;
extern s32 D_80109E34_dizzy_dinghies;
extern Vec D_8010A028_dizzy_dinghies[20];

void func_80107738_dizzy_dinghies(omObjData *object, u16 player);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801059A0_dizzy_dinghies);

void func_80105CAC_dizzy_dinghies(omObjData *object) {
    DizzyDinghiesWork *work = D_800EC598_minigame[0]->data;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_8010655C_dizzy_dinghies);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80106970_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80106DF4_dizzy_dinghies);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80108EC4_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801090BC_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80109238_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_80109420_dizzy_dinghies);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", func_801095D4_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109EF0_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F04_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F14_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F24_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F3C_dizzy_dinghies);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_46_dizzy_dinghies/316DF0", D_80109F50_dizzy_dinghies);
