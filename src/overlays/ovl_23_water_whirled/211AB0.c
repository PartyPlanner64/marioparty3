#include "common.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/hmfcoll.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "overlays/minigame.h"

extern f32 D_800D5210_main;

extern Vec D_8010A160_water_whirled[];
extern f32 D_8010A190_water_whirled[4];
extern Vec D_8010A1A0_water_whirled[];
extern Vec D_8010A1D0_water_whirled[];
extern f32 D_8010A250_water_whirled;
extern f32 D_8010A254_water_whirled;
extern f32 D_8010A258_water_whirled;
extern f32 D_8010A25C_water_whirled;
extern f32 D_8010A260_water_whirled;
extern f32 D_8010A264_water_whirled;
extern f32 D_8010A268_water_whirled;
extern f32 D_8010A26C_water_whirled;
extern s32 D_8010A280_water_whirled;
extern s16 D_8010A286_water_whirled;
extern s32 D_8010A288_water_whirled;
extern D_80111B50_vine_with_me_Struct D_8010A2AC_water_whirled;
extern Vec D_8010A2D4_water_whirled;
extern s8 D_8010A2F0_water_whirled[4];
extern s16 D_8010A2F4_water_whirled;
extern s16 D_8010A2F6_water_whirled;
extern s16 D_8010A2F8_water_whirled;
extern s16 D_8010A30C_water_whirled[][20];
extern s32 D_8010A3AC_water_whirled[];
extern s32 D_8010A3BC_water_whirled[];
extern s32 D_8010A3EC_water_whirled[];
extern Vec D_8010A880_water_whirled[][20];
extern s32 D_8010AC48_water_whirled[4];
extern s32 D_8010AC58_water_whirled[4];
extern s32 D_8010AC68_water_whirled[4];
extern s32 D_8010AC78_water_whirled[4];

void func_80105EA0_water_whirled(omObjData *object);
void func_80105D64_water_whirled(void);
void func_801071BC_water_whirled(omObjData *object);
void func_8010750C_water_whirled(omObjData *object, u16 player);
void func_80107880_water_whirled(omObjData *object);
void func_8010789C_water_whirled(omObjData *object);
void func_801078B8_water_whirled(omObjData *object);
void func_801078D4_water_whirled(omObjData *object);
void func_80107F08_water_whirled(omObjData *object);
void func_80108DF8_water_whirled(omObjData *object);

void func_801059A0_water_whirled(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800D5210_main = 30000.0f;
    Hu3DCameraPerspectiveSet(0, 20.0f, 80.0f, 16000.0f);
    Hu3DGLightDirSet(1, -35.0f, -114.0f, -3.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_801071BC_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_80107880_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_8010789C_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078B8_water_whirled);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 7, 0, -1, func_801078D4_water_whirled);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(4, 0, 0, -1, func_80105EA0_water_whirled), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(omAddObj(100, 0, 0, -1, func_80108DF8_water_whirled), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_800EB73C_minigame = 10.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_8010A2AC_water_whirled);
    D_800EB930_minigame = 50;
    D_800EB932_minigame = 60;
    func_800EA0FC_minigame(0, 0.0f, D_8010A190_water_whirled[0]);
    func_800EA0FC_minigame(1, 0.0f, D_8010A190_water_whirled[1]);
    func_800EA0FC_minigame(2, 0.0f, D_8010A190_water_whirled[2]);
    func_800EA0FC_minigame(3, 0.0f, D_8010A190_water_whirled[3]);
    Hu3DGLightDirSet(1, D_8010A2D4_water_whirled.x, D_8010A2D4_water_whirled.y, D_8010A2D4_water_whirled.z);
}

void func_80105D64_water_whirled(void) {
    Vec pos;
    Vec at;
    Vec up;
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    pos.y = -sindf(rotX) * CZoom + Center.y;
    pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    at.x = Center.x;
    at.y = Center.y;
    at.z = Center.z;
    up.x = sindf(rotY) * sindf(rotX);
    up.y = cosdf(rotX);
    up.z = cosdf(rotY) * sindf(rotX);
    Hu3DCameraPosSetV(0, &pos, &at, &up);
}

void func_80105EA0_water_whirled(omObjData *object) {
    Vec worldPos;
    Vec2f screenPos;
    f32 min;
    f32 max;
    s32 i;

    if (func_800E6E8C_minigame() == 2) {
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].x < min) {
                min = D_8010A1D0_water_whirled[i].x;
            }
            if (max < D_8010A1D0_water_whirled[i].x) {
                max = D_8010A1D0_water_whirled[i].x;
            }
        }
        Center.x = (min + max) * 0.5f;
        min = 50000.0f;
        max = -50000.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010A1D0_water_whirled[i].z < min) {
                min = D_8010A1D0_water_whirled[i].z;
            }
            if (max < D_8010A1D0_water_whirled[i].z) {
                max = D_8010A1D0_water_whirled[i].z;
            }
        }
        Center.z = (min + max) * 0.5f;
        CZoom = 12000.0f;
        func_80105D64_water_whirled();
        max = 0.0f;
        for (i = 0; i < 4; i++) {
            worldPos.x = D_8010A1D0_water_whirled[i].x;
            worldPos.y = 0.0f;
            worldPos.z = D_8010A1D0_water_whirled[i].z;
            func_80012B14_main(0, &worldPos, &screenPos);
            screenPos.x = fabsf(screenPos.x - 160.0f);
            screenPos.y = fabsf(screenPos.y - 120.0f);
            screenPos.x = (screenPos.x + 40.0f) / 160.0f;
            screenPos.y = (screenPos.y + 20.0f) / 120.0f;
            if (max < screenPos.x) {
                max = screenPos.x;
            }
            if (max < screenPos.y) {
                max = screenPos.y;
            }
        }
        CZoom = max * 12000.0f;
        if (CZoom < 7000.0f) {
            CZoom = 7000.0f;
        }
    }
}

void func_8010616C_water_whirled(omObjData *object) {
    if (D_8010A288_water_whirled != 0) {
        D_8010A288_water_whirled = D_8010A288_water_whirled * 0.75f;
        HuAudFXVolSet(D_8010A286_water_whirled, D_8010A288_water_whirled);
    }
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

f32 func_801061E4_water_whirled(f32 x, f32 z) {
    f32 wave;

    wave = sindf((D_8010A250_water_whirled / D_8010A254_water_whirled -
                  HuSqrtf(x * x + z * z) / D_8010A258_water_whirled) *
                 (M_PI * 2)) *
           D_8010A25C_water_whirled;
    x += 8000.0f;
    z += 5000.0f;
    wave += sindf((D_8010A260_water_whirled / D_8010A264_water_whirled -
                   HuSqrtf(x * x + z * z) / D_8010A268_water_whirled) *
                  (M_PI * 2)) *
            D_8010A26C_water_whirled;
    return wave / 2.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106308_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106680_water_whirled);

void func_8010698C_water_whirled(void) {
    omObjData *target;

    if (D_8010A280_water_whirled != -1) {
        target = D_800EC598_minigame[D_8010A280_water_whirled];
        Center.x -= (Center.x - target->trans.x) * 0.25f;
        Center.z -= (Center.z - target->trans.z) * 0.25f;
        Center.y -= (Center.y - target->trans.y) * 0.25f;
        CZoom *= 0.95f;
        if (CZoom < 2000.0f) {
            CZoom = 2000.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106A58_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80106DB8_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801071BC_water_whirled);

void func_8010750C_water_whirled(omObjData *object, u16 player) {
    func_800E1BA8_minigame_ObjData *work;
    s32 i;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    memset(object->data, 0, 0x15C);
    work = object->data;
    object->model[0] = func_8000B108_main((GwPlayer[player].chr + 9) | 0x440000, 0x6D9);
    work->unk57 = GwPlayer[player].pad;
    object->func = func_80107F08_water_whirled;
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
    object->scale.x = object->scale.y = object->scale.z = 1.1f;
    for (i = 0; i < 6; i++) {
        if (i == 3 || i == 0) {
            if (D_8010A2F4_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F4_water_whirled = func_8000B108_main(0x440006, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F4_water_whirled);
            }
        } else if (i == 4 || i == 1) {
            if (D_8010A2F6_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F6_water_whirled = func_8000B108_main(0x440007, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F6_water_whirled);
            }
        } else {
            if (D_8010A2F8_water_whirled < 0) {
                object->model[i + 1] = D_8010A2F8_water_whirled = func_8000B108_main(0x440008, 0x889);
            } else {
                object->model[i + 1] = Hu3DModelLink(D_8010A2F8_water_whirled);
            }
        }
        func_8001C2FC_main(object->model[i + 1], 0x70000000, 0x70000000);
    }
    work = object->data;
    work->unk3C = 90.0f;
    func_800E149C_minigame(object, 0, 2);
    do {
        i = rand8() & 3;
    } while (D_8010A2F0_water_whirled[i] != -1);
    D_8010A2F0_water_whirled[i] = player;
    object->trans.x = D_8010A160_water_whirled[i].x;
    object->trans.y = D_8010A160_water_whirled[i].y;
    object->trans.z = D_8010A160_water_whirled[i].z;
}

void func_80107880_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 0);
}

void func_8010789C_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 1);
}

void func_801078B8_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 2);
}

void func_801078D4_water_whirled(omObjData *object) {
    func_8010750C_water_whirled(object, 3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801078F0_water_whirled);

s32 func_80107D18_water_whirled(s32 index, s16 value) {
    s32 sum;
    u8 i;

    D_8010A30C_water_whirled[index][D_8010A3BC_water_whirled[index]] = value;
    if (++D_8010A3BC_water_whirled[index] >= 20) {
        D_8010A3BC_water_whirled[index] = 0;
    }
    sum = 0;
    for (i = 0; i < 20; i++) {
        sum += D_8010A30C_water_whirled[index][i];
    }
    return sum / 20;
}

void func_80107DD4_water_whirled(s32 index, f32 unused, Vec *out) {
    s32 i;

    out->x = out->y = out->z = 0.0f;
    D_8010A880_water_whirled[index][D_8010A3AC_water_whirled[index]].x = D_8010A1A0_water_whirled[index].x;
    D_8010A880_water_whirled[index][D_8010A3AC_water_whirled[index]].z = D_8010A1A0_water_whirled[index].z;
    if (++D_8010A3AC_water_whirled[index] >= 20) {
        D_8010A3AC_water_whirled[index] = 0;
    }
    for (i = 0; i < 20; i++) {
        out->x += D_8010A880_water_whirled[index][i].x;
        out->z += D_8010A880_water_whirled[index][i].z;
    }
    out->x /= 20.0f;
    out->z /= 20.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80107F08_water_whirled);

void func_8010860C_water_whirled(Vec *origin, Vec *p, Vec *q, Vec *out) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801086A0_water_whirled);

void func_80108898_water_whirled(omObjData *object, Vec *pos) {
    func_800E1BA8_minigame_ObjData *work = object->data;
    func_800E1BA8_minigame_ObjData *otherWork;
    omObjData *other;
    f32 x = pos->x;
    f32 z = pos->z;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherWork = other->data;
        if (work == otherWork) {
            continue;
        }
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        dist = HuSqrtf(dx * dx + dz * dz) - (otherWork->unk48 + work->unk48);
        if (dist < 0.0f) {
            func_800DFCDC_minigame(dx, dz, dist);
            work->unk53[1] = i;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801089C0_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108B98_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80108DF8_water_whirled);

void func_80109340_water_whirled(s16 player, s32 bank) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOn(D_8010AC68_water_whirled[player]);
    HuSprDispOn(grp, 0);
    HuSprBankSet(grp, 0, bank, 0);
    func_800550F4_main(grp, 0, 1);
    HuSprDispOn(grp, 1);
    HuSprBankSet(grp, 1, 10, 0);
    func_800550F4_main(grp, 1, 1);
    HuSprDispOn(grp, 2);
    HuSprBankSet(grp, 2, 5, 0);
    func_800550F4_main(grp, 2, 1);
    espDispOff(D_8010AC58_water_whirled[player]);
    espDispOff(D_8010AC78_water_whirled[player]);
}

void func_80109458_water_whirled(s16 player) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOff(D_8010AC68_water_whirled[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    if (D_8010A3EC_water_whirled[player] >= 0) {
        espDispOn(D_8010AC58_water_whirled[player]);
        if (D_8010A3EC_water_whirled[player] >= 4) {
            D_8010A3EC_water_whirled[player] = -4;
        }
    } else {
        espDispOff(D_8010AC58_water_whirled[player]);
    }
    D_8010A3EC_water_whirled[player]++;
    espDispOff(D_8010AC78_water_whirled[player]);
}

void func_8010956C_water_whirled(s16 player) {
    s16 grp = D_8010AC48_water_whirled[player];

    espDispOff(D_8010AC68_water_whirled[player]);
    HuSprDispOff(grp, 0);
    HuSprDispOff(grp, 1);
    HuSprDispOff(grp, 2);
    espDispOff(D_8010AC58_water_whirled[player]);
    espDispOn(D_8010AC78_water_whirled[player]);
}

s32 func_8010960C_water_whirled(omObjData *object) {
    f32 x = object->trans.x;
    f32 z = object->trans.z;

    if ((x > -550.0f) & (x < 550.0f)) {
        if (z > 0.0f) {
            return 0;
        }
        return 2;
    }
    if (x > 0.0f) {
        return 1;
    }
    return 3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801096BC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_801098AC_water_whirled);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", func_80109E2C_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A520_water_whirled);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_23_water_whirled/211AB0", D_8010A540_water_whirled);
