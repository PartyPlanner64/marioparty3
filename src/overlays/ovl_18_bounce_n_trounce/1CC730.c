#include "common.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Per-player work, allocated in func_801069F0_bounce_n_trounce
typedef struct BounceNTrounceWork {
    /* 0x00 */ u16 playerId;
    /* 0x02 */ u16 state;
    /* 0x04 */ u16 motState;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ u16 unk_08;
    /* 0x0A */ u16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E[4];
    /* 0x16 */ u16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ omObjData *floorTile;
    /* 0x20 */ f32 motSpeed;
    /* 0x24 */ f32 motDir;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 jumpVel;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 jumpTime;
    /* 0x40 */ f32 jumpBaseY;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ Vec prevPos;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 floorRadius;
    /* 0x74 */ f32 radius;
    /* 0x78 */ omObjData *emitter;
    /* 0x7C */ s16 unk_7C;
    /* 0x7E */ u16 unk_7E;
    /* 0x80 */ Vec aiTargetPos;
    /* 0x8C */ Vec aiTilePos;
    /* 0x98 */ u16 aiTile;
    /* 0x9A */ char pad_9A[2];
    /* 0x9C */ omObjData *aiTarget;
    /* 0xA0 */ u16 aiState;
    /* 0xA2 */ u16 unk_A2;
    /* 0xA4 */ s16 unk_A4;
    /* 0xA6 */ u16 aiWait;
    /* 0xA8 */ s16 unk_A8;
    /* 0xAA */ char pad_AA[2];
} BounceNTrounceWork; // Size 0xAC

// Particle emitter work, allocated in func_801069F0_bounce_n_trounce
typedef struct BounceNTrounceEmitterWork {
    /* 0x00 */ u16 interval;
    /* 0x04 */ f32 angle;
    /* 0x08 */ f32 angleStep;
} BounceNTrounceEmitterWork; // Size 0xC

// Floor tile work, allocated in func_80105E4C_bounce_n_trounce
typedef struct BounceNTrounceTileWork {
    /* 0x00 */ s16 index;
    /* 0x02 */ u16 state;
    /* 0x04 */ f32 velY;
    /* 0x08 */ u16 timer;
} BounceNTrounceTileWork; // Size 0xC

extern s32 D_800A178C_main[][6];
extern f32 D_800D2120_main;

extern D_80111B50_vine_with_me_Struct D_8010ABB0_bounce_n_trounce;
extern s8 D_8010ABD8_bounce_n_trounce[4];
extern s8 D_8010ABDC_bounce_n_trounce[4];
extern u16 D_8010ABE0_bounce_n_trounce[4];
extern Vec D_8010ABEC_bounce_n_trounce[9];
extern Vec D_8010AC58_bounce_n_trounce[7];
extern s32 D_8010ACAC_bounce_n_trounce[7];
extern s32 D_8010ACC8_bounce_n_trounce[7];
extern s16 D_8010ACE4_bounce_n_trounce[9];
extern u16 D_8010ACF6_bounce_n_trounce;
extern u16 D_8010ACF8_bounce_n_trounce;
extern Vec D_8010ACFC_bounce_n_trounce[4];
extern s32 D_8010AD2C_bounce_n_trounce[8];
extern u16 D_8010ABE8_bounce_n_trounce;
extern Vec D_8010AD4C_bounce_n_trounce[4];
extern u16 D_8010AD7C_bounce_n_trounce[4];
extern u16 D_8010AD84_bounce_n_trounce;
extern u16 D_8010AD86_bounce_n_trounce;
extern u16 D_8010AD88_bounce_n_trounce;
extern u16 D_8010AD8A_bounce_n_trounce;
extern u16 D_8010AEB0_bounce_n_trounce;
extern u16 D_8010AEB2_bounce_n_trounce;
extern f32 D_8010AEB4_bounce_n_trounce;
extern f32 D_8010AEB8_bounce_n_trounce;
extern u16 D_8010AEBC_bounce_n_trounce;
extern u16 D_8010AEBE_bounce_n_trounce;
extern omObjData *D_8010AEC0_bounce_n_trounce;
extern omObjData *D_8010AEC4_bounce_n_trounce;
extern u16 D_8010AEC8_bounce_n_trounce;
extern u16 D_8010AECA_bounce_n_trounce;
extern s16 D_8010AECC_bounce_n_trounce;
extern omObjData *D_8010AED0_bounce_n_trounce;
extern omObjData *D_8010AED4_bounce_n_trounce;
extern omObjData **D_8010AED8_bounce_n_trounce;
extern omObjData **D_8010AEDC_bounce_n_trounce;
extern omObjData **D_8010AEE0_bounce_n_trounce;
extern s16 D_8010AEE4_bounce_n_trounce[4];

void func_8004BCE4_main(struct CameraViewData *data);

void func_80105C84_bounce_n_trounce(omObjData *arg0);
void func_80105CBC_bounce_n_trounce(omObjData *);
void func_80105E4C_bounce_n_trounce(omObjData *object);
void func_801069F0_bounce_n_trounce(omObjData *object);
void func_8010A664_bounce_n_trounce(omObjData *object);
void func_80106268_bounce_n_trounce(omObjData *object);
void func_8010675C_bounce_n_trounce(omObjData *object);
void func_801068F4_bounce_n_trounce(omObjData *object);
void func_80106F78_bounce_n_trounce(omObjData *object);
void func_801070CC_bounce_n_trounce(omObjData *object);
void func_8010A740_bounce_n_trounce(s16 model);
void func_8010A8F0_bounce_n_trounce(omObjData *object);
void func_80108940_bounce_n_trounce(void);
void func_80108C18_bounce_n_trounce(omObjData *object);
void func_80109AF0_bounce_n_trounce(omObjData *object);
void func_80109F68_bounce_n_trounce(omObjData *object);
f32 func_8010AAE0_bounce_n_trounce(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8010AB90_bounce_n_trounce(void);
void func_80106764_bounce_n_trounce(omObjData *object);
void func_80106854_bounce_n_trounce(omObjData *object);
void func_80107114_bounce_n_trounce(omObjData *object, s8 stickX, s8 stickY, u16 btn);
void func_80107EDC_bounce_n_trounce(omObjData *object);
void func_80109018_bounce_n_trounce(omObjData *object, s8 *stickX, s8 *stickY, u16 *btn);
void func_80109478_bounce_n_trounce(omObjData *object);
f32 func_80106434_bounce_n_trounce(omObjData *object);
void func_8010846C_bounce_n_trounce(omObjData *object);
s32 func_80109804_bounce_n_trounce(omObjData *object, s16 arg1);
s16 func_80109A00_bounce_n_trounce(omObjData *object);
s32 func_8010AB1C_bounce_n_trounce(f32 x, f32 z);
void func_80108CA8_bounce_n_trounce(omObjData *);
void func_80108D28_bounce_n_trounce(omObjData *);

#ifdef NON_MATCHING
void func_801059A0_bounce_n_trounce(void) {
    s32 i;
    u8 slot;

    omInitObjMan(40, 0);
    func_8004A208_main();
    func_80045C2C_main();
    func_8000B5F0_main(1);
    // The original passes 1 to this function, which takes no arguments.
    func_8000B638_main();
    Center.x = 0.0f;
    Center.y = 30.0f;
    Center.z = 0.0f;
    CRot.x = -30.0f;
    CRot.y = 45.0f;
    CRot.z = 0.0f;
    CZoom = 2100.0f;
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105C84_bounce_n_trounce);
    D_8010AED0_bounce_n_trounce = omAddObj(10, 0, 0, -1, func_80105E4C_bounce_n_trounce);
    D_8010AED4_bounce_n_trounce = omAddObj(50, 0, 0, -1, func_8010A664_bounce_n_trounce);
    D_8010AED4_bounce_n_trounce->work[0] = 0;
    omMakeGroup(0, 4);
    D_8010AEDC_bounce_n_trounce = omGetGroupMemberList(0);
    for (i = 0; i < 4; i++) {
        omAddObj(30, 7, 6, 0, func_801069F0_bounce_n_trounce)->work[0] = i;
    }
    for (i = 0; i < 4; i++) {
        D_8010AEE4_bounce_n_trounce[i] = -1;
    }
    for (i = 0; i < 4;) {
        slot = rand8() & 3;
        if (D_8010AEE4_bounce_n_trounce[slot] == -1) {
            D_8010AEE4_bounce_n_trounce[slot] = i;
            i++;
        }
    }
    func_800E5EA0_minigame(&D_8010ABB0_bounce_n_trounce);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801059A0_bounce_n_trounce);
#endif

void func_80105C84_bounce_n_trounce(omObjData *arg0) {
    D_8010AEBC_bounce_n_trounce = 4;
    D_8010AEC4_bounce_n_trounce = 0;
    D_8010AEC0_bounce_n_trounce = 0;
    D_8010AECC_bounce_n_trounce = 1;
    arg0->func = func_80105CBC_bounce_n_trounce;
}

void func_80105CBC_bounce_n_trounce(omObjData *object) {
    if (D_8010ABE8_bounce_n_trounce == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010AEC0_bounce_n_trounce == NULL) {
                    D_8010AEC8_bounce_n_trounce = 0;
                    D_8010AEC0_bounce_n_trounce = omAddObj(4, 0, 0, -1, func_80109AF0_bounce_n_trounce);
                    D_8010AED4_bounce_n_trounce->work[0] = 1;
                }
                break;
            case 1:
                break;
            case 2:
                func_80108940_bounce_n_trounce();
                if (D_8010AEBC_bounce_n_trounce == 0) {
                    D_8010AECC_bounce_n_trounce = 0;
                    D_8010AED0_bounce_n_trounce->work[0] = 0;
                    func_800E6F0C_minigame(3);
                } else if (D_8010AEBC_bounce_n_trounce == 1) {
                    D_8010AECC_bounce_n_trounce = 0;
                    D_8010AED0_bounce_n_trounce->work[0] = 0;
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                D_8010AED0_bounce_n_trounce->work[0] = 0;
                func_80108940_bounce_n_trounce();
                if (D_8010AEC4_bounce_n_trounce == NULL) {
                    D_8010AECA_bounce_n_trounce = 0;
                    D_8010AEC4_bounce_n_trounce = omAddObj(4, 0, 0, -1, func_80109F68_bounce_n_trounce);
                }
                break;
            case 4:
                func_80108940_bounce_n_trounce();
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(30);
                func_8004AB0C_main(30);
                D_8010ABE8_bounce_n_trounce = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010AB90_bounce_n_trounce();
    }
}

void func_80105E4C_bounce_n_trounce(omObjData *object) {
    omObjData *obj;
    omObjData *deco;
    BounceNTrounceTileWork *tileWork;
    s32 i;
    s16 sprite;
    f32 x;
    f32 z;
    Vec pos;
    Vec target;

    omMakeGroup(2, 9);
    D_8010AED8_bounce_n_trounce = omGetGroupMemberList(2);
    omMakeGroup(3, 7);
    D_8010AEE0_bounce_n_trounce = omGetGroupMemberList(3);
    for (i = 0; i < 9; i++) {
        obj = omAddObj(20, 1, 0, 2, func_8010675C_bounce_n_trounce);
        obj->data = HuMemAllocTag(sizeof(BounceNTrounceTileWork), TAG_OVERLAY);
        tileWork = OM_GET_DATA_PTR(obj, BounceNTrounceTileWork);
        tileWork->index = i;
        if (i & 1) {
            if (i == 1) {
                obj->model[0] = func_8000B108_main(0x390001, 0x6B9);
            } else {
                obj->model[0] = Hu3DModelLink(D_8010AED8_bounce_n_trounce[1]->model[0]);
            }
        } else {
            if (i == 0) {
                obj->model[0] = func_8000B108_main(0x390000, 0x6B9);
            } else {
                obj->model[0] = Hu3DModelLink(D_8010AED8_bounce_n_trounce[0]->model[0]);
            }
        }
        omSetTra(obj, D_8010ABEC_bounce_n_trounce[i].x, D_8010ABEC_bounce_n_trounce[i].y,
                 D_8010ABEC_bounce_n_trounce[i].z);
        tileWork->state = 0;
    }
    for (i = 0; i < 7; i++) {
        deco = omAddObj(20, 1, 0, 3, func_801068F4_bounce_n_trounce);
        deco->model[0] = func_8000B108_main(D_8010ACAC_bounce_n_trounce[i], 0x6B9);
        HuSqrtf(D_8010AC58_bounce_n_trounce[i].x * D_8010AC58_bounce_n_trounce[i].x +
                D_8010AC58_bounce_n_trounce[i].z * D_8010AC58_bounce_n_trounce[i].z);
        x = cosdf(-45.0f) * D_8010AC58_bounce_n_trounce[i].x - sindf(-45.0f) * D_8010AC58_bounce_n_trounce[i].z;
        z = sindf(-45.0f) * D_8010AC58_bounce_n_trounce[i].x + cosdf(-45.0f) * D_8010AC58_bounce_n_trounce[i].z;
        omSetTra(deco, x, D_8010AC58_bounce_n_trounce[i].y, z);
        omSetRot(deco, 0.0f, 45.0f, 0.0f);
        omSetSca(deco, 1.5f, 1.5f, 1.5f);
        deco->work[0] = 0;
        deco->work[1] = D_8010ACC8_bounce_n_trounce[i];
    }
    sprite = espEntry(func_8000B838_main(0x390002), 0, 1);
    espDispOff(sprite);
    target.x = 0.0f;
    target.y = 120.0f;
    target.z = 0.0f;
    pos.x = sindf(45.0f) * 2800.0f;
    pos.y = 1400.0f;
    pos.z = cosdf(45.0f) * 2800.0f;
    func_8004B760_main(0x7FDA, D_800CD1DC_main[sprite].unk04, func_8004BCE4_main, 45.0f, &pos, &target);
    Hu3DCameraPerspectiveSet(0, 45.0f, 500.0f, 4500.0f);
    CZoom = 2100.0f;
    object->work[0] = 1;
    D_8010ACE4_bounce_n_trounce[4] = 1;
    object->func = func_80106268_bounce_n_trounce;
}

void func_80106268_bounce_n_trounce(omObjData *object) {
    s16 candidates[9];
    s16 count;
    s32 i;
    s16 choice;
    BounceNTrounceTileWork *work;

    if (func_800E6E8C_minigame() == 2 && object->work[0] != 0) {
        if (D_8010ACF6_bounce_n_trounce != 0) {
            D_8010ACF6_bounce_n_trounce--;
            return;
        }
        if (D_8010ACF8_bounce_n_trounce != 0) {
            D_8010ACF8_bounce_n_trounce--;
            return;
        }
        D_8010ACF8_bounce_n_trounce = 60;
        count = 0;
        for (i = 0; i < 9; i++) {
            if (D_8010ACE4_bounce_n_trounce[i] == 0) {
                candidates[count++] = i;
            }
        }
        if (count == 0) {
            return;
        }
        if (count == 1) {
            choice = candidates[0];
        } else {
            choice = candidates[rand8() % count];
        }
        D_8010ACE4_bounce_n_trounce[choice] = 1;
        work = OM_GET_DATA_PTR(D_8010AED8_bounce_n_trounce[choice], BounceNTrounceTileWork);
        work->state = 1;
        work->velY = -15.0f;
        work->timer = 40;
        HuAudFXPlay(0x3D1);
        D_8010AED8_bounce_n_trounce[choice]->func = func_80106764_bounce_n_trounce;
    }
}

f32 func_80106434_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work;
    f32 radius;
    f32 maxY = -100000.0f;
    omObjData *tile;
    f32 x0;
    f32 x1;
    f32 z0;
    f32 z1;
    f32 dist;
    s32 i;
    s32 j;

    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    radius = work->floorRadius;
    work->floorTile = NULL;
    for (i = 0; i < 9; i++) {
        tile = D_8010AED8_bounce_n_trounce[i];
        if (OM_GET_DATA_PTR(tile, BounceNTrounceTileWork)->state == 3) {
            continue;
        }
        x0 = tile->trans.x - 150.0f;
        z0 = tile->trans.z - 150.0f;
        x1 = tile->trans.x + 150.0f;
        z1 = tile->trans.z + 150.0f;
        if (x0 <= object->trans.x && z0 <= object->trans.z && object->trans.x <= x1 && object->trans.z <= z1 &&
            maxY < tile->trans.y) {
            maxY = tile->trans.y;
            work->floorTile = tile;
            continue;
        }
        for (j = 0; j < 2; j++) {
            x0 = tile->trans.x - 150.0f;
            z0 = tile->trans.z - 150.0f + j * 150.0f * 2;
            x1 = tile->trans.x + 150.0f;
            if (x0 <= object->trans.x && object->trans.x <= x1) {
                dist = HuSqrtf((object->trans.z - z0) * (object->trans.z - z0));
            } else if (object->trans.x < x0) {
                dist = func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, x0, z0);
            } else if (x1 < object->trans.x) {
                dist = func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, x1, z0);
            }
            if (dist <= radius && maxY < tile->trans.y) {
                maxY = tile->trans.y;
                work->floorTile = tile;
            }
        }
        for (j = 0; j < 2; j++) {
            x0 = tile->trans.x - 150.0f + j * 150.0f * 2;
            z0 = tile->trans.z - 150.0f;
            z1 = tile->trans.z + 150.0f;
            if (z0 <= object->trans.z && object->trans.z <= z1) {
                dist = HuSqrtf((object->trans.x - x0) * (object->trans.x - x0));
            } else if (object->trans.z < z0) {
                dist = func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, x0, z0);
            } else if (z1 < object->trans.z) {
                // Uses x1 from the previous loop rather than x0.
                dist = func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, x1, z0);
            }
            if (dist <= radius && maxY < tile->trans.y) {
                maxY = tile->trans.y;
                work->floorTile = tile;
            }
        }
    }
    return maxY;
}

void func_8010675C_bounce_n_trounce(omObjData *object) {
}

void func_80106764_bounce_n_trounce(omObjData *object) {
    BounceNTrounceTileWork *work = OM_GET_DATA_PTR(object, BounceNTrounceTileWork);

    if (D_8010AED0_bounce_n_trounce->work[0] == 0) {
        omSetTra(object, object->trans.x, 0.0f, object->trans.z);
        object->func = NULL;
        return;
    }
    if (work->velY == 0.0f) {
        omSetTra(object, object->trans.x, 0.0f, object->trans.z);
        work->velY = -15.0f;
    } else {
        omSetTra(object, object->trans.x, work->velY, object->trans.z);
        work->velY = 0.0f;
    }
    if (--work->timer == 0) {
        work->velY = -4.4f;
        work->state = 2;
        object->func = func_80106854_bounce_n_trounce;
    }
}

void func_80106854_bounce_n_trounce(omObjData *object) {
    BounceNTrounceTileWork *work = OM_GET_DATA_PTR(object, BounceNTrounceTileWork);

    object->trans.y += work->velY;
    work->velY *= 1.22f;
    if (object->trans.y < -1500.0f) {
        object->trans.y = -1500.0f;
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->state = 3;
        object->func = NULL;
    }
}

void func_801068F4_bounce_n_trounce(omObjData *object) {
    f32 angle = object->work[0];

    angle /= 10.0f;
    object->work[0] += object->work[1];
    if (object->work[0] >= 3600) {
        object->work[0] -= 3600;
    }
    omSetSca(object, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f, 1.5f - sindf(angle) * 0.5f);
}

void func_801069F0_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work;
    omObjData *emitter;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    u16 playerId;
    s8 chr;
    s32 mdlId;
    s32 mdlAttr;
    f32 angle;
    s32 i;

    object->data = HuMemAllocTag(sizeof(BounceNTrounceWork), TAG_OVERLAY);
    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    work->playerId = object->work[0];
    playerId = work->playerId;
    work->state = 0;
    work->motState = 2;
    work->motSpeed = 4.0f;
    work->motDir = 1.0f;
    work->unk_28 = 1.5f;
    work->unk_30 = work->unk_34 = work->unk_38 = 0.0f;
    work->unk_08 = 0;
    work->unk_0A = 0;
    work->unk_0C = 0;
    work->unk_18 = 0;
    work->unk_44 = 0.0f;
    work->unk_48 = 0.0f;
    work->unk_06 = 0;
    work->unk_16 = 0;
    work->floorRadius = 40.0f;
    work->radius = 55.0f;
    work->floorTile = NULL;
    work->unk_7C = 0;
    work->unk_7E = 0;
    work->aiState = 0;
    work->aiTarget = NULL;
    work->unk_A2 = 0;
    work->unk_64 = work->unk_68 = work->unk_6C = 0.0f;
    for (i = 0; i < 4; i++) {
        work->unk_0E[i] = 0;
    }
    chr = GwPlayer[playerId].chr;
    mdlId = D_800A178C_main[chr][0];
    mdlAttr = D_800A178C_main[chr][1];
    object->model[0] = func_8000B108_main(D_8010AD2C_bounce_n_trounce[chr], 0x6D9);
    omSetTra(object, D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[playerId]].x,
             D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[playerId]].y,
             D_8010ACFC_bounce_n_trounce[D_8010AEE4_bounce_n_trounce[playerId]].z);
    object->model[1] = func_8000B108_main(mdlId | mdlAttr, 0x206B9);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->model[2] = func_8000B0D4_main(0, 0xA89);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y + 1.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], work->unk_28, 1.0f, work->unk_28);
    object->model[3] = func_8000B108_main(0x39000B, 0x68D);
    object->model[4] = func_8000B108_main(0x39000C, 0x68D);
    object->model[6] = func_8000B108_main(0x82, 0xA8D);
    Hu3DModelScaleSet(object->model[3], 1.2f, 1.0f, 1.2f);
    func_8000B460_main(object, 0, func_80017BB8_main(chr, 0x73));
    func_8000B460_main(object, 1, func_80017BB8_main(chr, 0));
    func_8000B460_main(object, 2, func_80017BB8_main(chr, 1));
    func_8000B460_main(object, 3, func_80017BB8_main(chr, 0x1F));
    func_8000B460_main(object, 4, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(object, 5, func_80017BB8_main(chr, 0x36));
    func_8001C5B4_main(object->model[1], object->motion[0]);
    func_8001C814_main(object->model[1], 3, 1);
    func_8001C814_main(object->model[0], 3, 1);
    angle = atan2df(-object->trans.x, -object->trans.z);
    omSetRot(object, 0.0f, angle, 0.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, angle, 0.0f);
    object->model[5] = func_8000B108_main(0x39000F, 0x6A9);
    Hu3DModelPosSet(object->model[5], object->trans.x, object->trans.y, object->trans.z);
    func_8001C2FC_main(object->model[5], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(object->model[5]);
    func_8001C954_main(object->model[5]);
    func_8001C514_main(object->model[5]);
    func_80013390_main(object->model[5], -1, NULL, func_8010A740_bounce_n_trounce);
    hmf = Hu3DData[object->model[5]].hmf;
    modelData = Hu3DData[object->model[5]].unkBC;
    particle = modelData->unk58;
    modelData->unk1C.i = 0;
    modelData->unk20.i = 0;
    modelData->unk24.i = 0;
    func_800138EC_main(object->model[5], 1, 1);
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = particle->unk1C = particle->unk20 = 0.0f;
        particle->unk04 = particle->unk08 = 0.0f;
    }
    emitter = omAddObj(60, 0, 0, -1, func_8010A8F0_bounce_n_trounce);
    work->emitter = emitter;
    emitter->data = HuMemAllocTag(sizeof(BounceNTrounceEmitterWork), TAG_OVERLAY);
    emitter->work[0] = 0;
    emitter->work[1] = (u32)object;
    work->unk_A8 = 0;
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
    object->func = func_801070CC_bounce_n_trounce;
}

void func_80106F78_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    u16 port = GwPlayer[work->playerId].pad;
    s8 stickX;
    s8 stickY;
    u16 btn;

    if (work->state == 3) {
        return;
    }
    if (GwPlayer[work->playerId].stat & 1) {
        func_80109018_bounce_n_trounce(object, &stickX, &stickY, &btn);
    } else {
        stickX = D_800CBB6E_main[port];
        stickY = D_800D20A1_main[port];
        btn = D_800D5558_main[port];
    }
    if (func_800E6E8C_minigame() == 0 || func_800E6E8C_minigame() == 1 || func_800E6E8C_minigame() == 3) {
        stickY = 0;
        stickX = 0;
        btn = 0;
    }
    if (work->state == 2 || work->state == 3) {
        stickY = 0;
        stickX = 0;
        btn = 0;
        func_80107EDC_bounce_n_trounce(object);
    } else {
        func_80107114_bounce_n_trounce(object, stickX, stickY, btn);
    }
}

void func_801070CC_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    func_80107114_bounce_n_trounce(object, D_8010ABD8_bounce_n_trounce[work->playerId],
                                   D_8010ABDC_bounce_n_trounce[work->playerId],
                                   D_8010ABE0_bounce_n_trounce[work->playerId]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107114_bounce_n_trounce);

void func_80107EDC_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    f32 rotY = object->rot.y;
    f32 floorY = func_80106434_bounce_n_trounce(object);
    Vec pos;
    Vec2f screenPos;

    if (work->unk_08 == 1) {
        if (work->unk_44 != 0.0f) {
            rotY += work->unk_44;
        }
        work->jumpTime += 1.0f;
        object->trans.y =
            work->jumpVel * work->jumpTime + work->jumpBaseY - work->jumpTime * 2.4f * work->jumpTime;
        if (work->unk_16 == 1) {
            object->trans.x += work->unk_64;
            object->trans.z += work->unk_68;
        }
        object->trans.x += work->unk_34;
        object->trans.z += work->unk_38;
    }
    work->unk_64 *= work->unk_6C;
    work->unk_68 *= work->unk_6C;
    if (fabs(work->unk_64) < 0.01f) {
        work->unk_64 = 0.0f;
    }
    if (fabs(work->unk_68) < 0.01f) {
        work->unk_68 = 0.0f;
    }
    if (work->unk_64 == 0.0f && work->unk_68 == 0.0f) {
        work->unk_16 = 0;
    } else {
        object->trans.x += work->unk_64;
        object->trans.z += work->unk_68;
    }
    omSetRot(object, object->rot.x, rotY, object->rot.z);
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    if (floorY == -100000.0f) {
        func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    } else {
        work->unk_28 = 1.5 - fabs(object->trans.y - floorY) / 900.0 * 1.2f;
        if (work->unk_28 < 0.3f) {
            work->unk_28 = 0.3f;
        }
        func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[2], object->trans.x, floorY + 1.0f, object->trans.z);
        Hu3DModelScaleSet(object->model[2], work->unk_28, 1.0f, work->unk_28);
    }
    if (work->unk_06 == 1) {
        Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y + 60.0f, object->trans.z);
    }
    func_8010846C_bounce_n_trounce(object);
    if (object->trans.y < -5000.0f) {
        work->state = 3;
        func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->unk_06 = 0;
        func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        object->func = NULL;
    }
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->trans.z;
    func_80012B14_main(0, &pos, &screenPos);
    if (screenPos.y > 240.0f && work->unk_18 == 0) {
        work->unk_18 = 1;
        PlayerFXPlay(0x286, work->playerId);
    }
    work->prevPos.x = object->trans.x;
    work->prevPos.y = object->trans.y;
    work->prevPos.z = object->trans.z;
}

void func_80108350_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    if (work->state != 2 && work->state != 3) {
        work->state = 0;
    }
    work->unk_44 = 0.0f;
    work->unk_48 = 0.0f;
    func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_80108398_bounce_n_trounce(omObjData *object, omObjData *other) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork = OM_GET_DATA_PTR(other, BounceNTrounceWork);
    f32 speed;
    f32 angle;

    speed = work->unk_44 / 160.0f * 22.0f + 20.0f;
    angle = atan2df(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
    otherWork->unk_64 = sindf(angle) * speed;
    otherWork->unk_68 = cosdf(angle) * speed;
    otherWork->unk_6C = 0.8f;
}

void func_80108454_bounce_n_trounce(omObjData *object, f32 vel) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->jumpVel = vel;
    work->jumpTime = 0.0f;
    work->jumpBaseY = object->trans.y;
}

void func_8010846C_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    f32 dir = work->motDir;
    f32 rate = D_800D2120_main;
    f32 time = Hu3DData[object->model[0]].motTime;

    if (work->motState == 2) {
        time += dir * work->motSpeed * rate;
        if (time > D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02) {
            work->motDir = -1.0f;
            time = D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02;
            work->motState = 4;
        }
    } else if (work->motState == 3) {
        time += work->motDir * work->motSpeed * D_800D2120_main;
        if (time < 0.0f) {
            time = 0.0f;
            work->motState = 1;
        }
    }
    Hu3DMotionTimeSet(object->model[0], time);
    Hu3DMotionTimeSet(object->model[1], time);
}

void func_801085EC_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork;
    omObjData *other;
    f32 dist;
    f32 minDist;
    f32 angle;
    s32 i;

    for (i = 0; i < 4; i++) {
        other = D_8010AEDC_bounce_n_trounce[i];
        if (object == other) {
            continue;
        }
        otherWork = OM_GET_DATA_PTR(other, BounceNTrounceWork);
        dist = func_8010AAE0_bounce_n_trounce(other->trans.x, other->trans.z, object->trans.x, object->trans.z);
        minDist = HuSqrtf((work->radius + otherWork->radius) * (work->radius + otherWork->radius));
        if (!(dist < minDist)) {
            continue;
        }
        if (other->trans.y + 180.0f < object->trans.y) {
            continue;
        }
        if (object->trans.y + 180.0f < other->trans.y) {
            continue;
        }
        if (other->trans.x == object->trans.x && other->trans.z == object->trans.z) {
            rand8();
            rand8();
        }
        angle = -atan2df(other->trans.x - object->trans.x, -(other->trans.z - object->trans.z));
        if (object->trans.y < other->trans.y + 180.0f && other->trans.y + 180.0f - 40.0f < object->trans.y) {
            work->unk_0E[otherWork->playerId] |= 4;
            otherWork->unk_0E[work->playerId] |= 1;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
            object->trans.y = other->trans.y + 180.0f + 1.0f;
        } else if (other->trans.y < object->trans.y + 180.0f && object->trans.y + 180.0f < other->trans.y + 40.0f) {
            work->unk_0E[otherWork->playerId] |= 1;
            otherWork->unk_0E[work->playerId] |= 4;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
            object->trans.y = other->trans.y - 180.0f - 1.0f;
        } else {
            work->unk_0E[otherWork->playerId] |= 2;
            otherWork->unk_0E[work->playerId] |= 2;
            minDist -= dist;
            object->trans.x += sindf(angle) * minDist;
            object->trans.z += cosdf(angle) * minDist;
        }
    }
}

void func_80108940_bounce_n_trounce(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        BounceNTrounceWork *work = OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork);
        s32 j;

        for (j = 0; j < 4; j++) {
            work->unk_0E[j] = 0;
        }
    }
}

u16 func_80108994_bounce_n_trounce(void) {
    f32 dists[4];
    u16 order[4];
    s32 count = 0;
    s32 i;
    s32 j;
    s32 k;
    BounceNTrounceWork *work;
    f32 dist;
    u16 temp;

    for (i = 0; i < 4; i++) {
        work = OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork);
        count += (work->state == 3);
        if (work->motState == 2 || work->motState == 4) {
            if (work->state != 4) {
                D_8010AEDC_bounce_n_trounce[i]->func = func_80108C18_bounce_n_trounce;
                for (j = 0; j < 4; j++) {
                    dists[j] = func_8010AAE0_bounce_n_trounce(
                        D_8010AD4C_bounce_n_trounce[j].x, D_8010AD4C_bounce_n_trounce[j].z,
                        D_8010AEDC_bounce_n_trounce[i]->trans.x, D_8010AEDC_bounce_n_trounce[i]->trans.z);
                    order[j] = j;
                }
                for (j = 0; j < 3; j++) {
                    for (k = j + 1; k < 4; k++) {
                        if (dists[order[j]] > dists[order[k]]) {
                            dist = dists[order[j]];
                            temp = order[j];
                            dists[order[j]] = dists[order[k]];
                            order[j] = order[k];
                            dists[order[k]] = dist;
                            order[k] = temp;
                        }
                    }
                }
                for (j = 0; j < 4; j++) {
                    if (D_8010AD7C_bounce_n_trounce[order[j]] != 1) {
                        work->unk_58 = D_8010AD4C_bounce_n_trounce[order[j]];
                        D_8010AD7C_bounce_n_trounce[order[j]] = 1;
                        break;
                    }
                }
            } else {
                count += (D_8010AEDC_bounce_n_trounce[i]->work[0] == 0);
            }
        }
    }
    return count == 4;
}

void func_80108C18_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->state = 4;
    func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[3]].motId, 0, 6, 0);
    object->work[0] = 8;
    object->func = func_80108CA8_bounce_n_trounce;
}

void func_80108CA8_bounce_n_trounce(omObjData *object) {
    if (object->work[0] != 0) {
        object->work[0]--;
    } else {
        Hu3DMotionShiftSet(object->model[1], Hu3DData[object->motion[1]].motId, 0, 6, 2);
        object->func = func_80108D28_bounce_n_trounce;
    }
}

void func_80108D28_bounce_n_trounce(omObjData *object) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *otherWork;
    f32 angle;
    f32 dist;
    f32 step;
    s32 i;

    for (i = 0; i < 4; i++) {
        otherWork = OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork);
        if (otherWork->state == 4) {
            continue;
        }
        if (work->unk_0E[i] & 1 || work->unk_0E[i] & 2) {
            angle = atan2df(-D_8010AEDC_bounce_n_trounce[i]->trans.x, -D_8010AEDC_bounce_n_trounce[i]->trans.z);
            otherWork->unk_64 = sindf(angle) * 6.0f;
            otherWork->unk_68 = cosdf(angle) * 6.0f;
            otherWork->unk_6C = 0.9f;
            dist = func_8010AAE0_bounce_n_trounce(work->unk_58.x, work->unk_58.z, object->trans.x, object->trans.z);
            step = (dist < 50.0f) ? dist : 50.0f;
            angle = atan2df(work->unk_58.x - object->trans.x, work->unk_58.z - object->trans.z);
            object->trans.x += sindf(angle) * step;
            object->trans.z += cosdf(angle) * step;
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelPosSet(object->model[2], object->trans.x, 1.0f, object->trans.z);
        }
    }
}

void func_80108EFC_bounce_n_trounce(omObjData *object) {
    func_8001C258_main(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y + 200.0f, object->trans.z);
    Hu3DModelRotSet(object->model[4], 0.0f, CRot.y, 0.0f);
    func_8001C814_main(object->model[4], 3, 0);
    Hu3DMotionTimeSet(object->model[4], 0.0f);
}

void func_80108F98_bounce_n_trounce(omObjData *object) {
    func_8001C258_main(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(object->model[6], object->trans.x, object->trans.y + 5.0f, object->trans.z);
    func_8001C814_main(object->model[6], 3, 0);
    Hu3DMotionTimeSet(object->model[6], 0.0f);
}

void func_80109018_bounce_n_trounce(omObjData *object, s8 *stickX, s8 *stickY, u16 *btn) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    BounceNTrounceWork *targetWork;
    u16 tile;
    u16 chance;
    f32 dist;
    f32 angle;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    if (work->floorTile != NULL) {
        u16 state = OM_GET_DATA_PTR(work->floorTile, BounceNTrounceTileWork)->state;

        if ((state == 1 || state == 2) && work->unk_7E == 0) {
            tile = func_80109A00_bounce_n_trounce(object);
            work->unk_7E = 1;
            work->aiState = 1;
            work->aiTargetPos.x = D_8010ABEC_bounce_n_trounce[tile].x;
            work->aiTargetPos.y = D_8010ABEC_bounce_n_trounce[tile].y;
            work->aiTargetPos.z = D_8010ABEC_bounce_n_trounce[tile].z;
        }
    }
    if (work->aiState == 0) {
        func_80109478_bounce_n_trounce(object);
    }
    switch (work->aiState) {
        case 1:
            if (func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, work->aiTargetPos.x,
                                               work->aiTargetPos.z) < 60.0f) {
                work->aiState = 0;
                work->unk_7E = 0;
                return;
            }
            if (work->motState == 2) {
                *btn |= 0x8000;
            }
            angle = atan2df(work->aiTargetPos.z - object->trans.z, work->aiTargetPos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 2:
            if (work->aiWait != 0) {
                work->aiState = 0;
            } else {
                work->aiWait--;
            }
            return;
        case 3:
            targetWork = OM_GET_DATA_PTR(work->aiTarget, BounceNTrounceWork);
            if (work->unk_A2 == 1) {
                switch (GwPlayer[work->playerId].cpu_difficulty) {
                    case 0:
                        chance = 100;
                        break;
                    case 1:
                        chance = 50;
                        break;
                    case 2:
                        chance = 30;
                        break;
                    case 3:
                        chance = 10;
                        break;
                }
                if (rand8() < chance) {
                    work->aiState = 0;
                    work->unk_A2 = 0;
                }
            }
            if (targetWork->floorTile == NULL || targetWork->state == 2 || targetWork->state == 3) {
                work->aiState = 0;
                return;
            }
            dist = func_8010AAE0_bounce_n_trounce(work->aiTarget->trans.x, work->aiTarget->trans.z,
                                                  object->trans.x, object->trans.z);
            if (dist < 80.0f && work->state != 1) {
                work->aiState = 0;
            }
            if (dist < 150.0f && work->unk_0A != 0) {
                *btn |= 0x2000;
            }
            if (dist < 400.0f && work->motState == 2) {
                *btn |= 0x8000;
            }
            angle = atan2df(work->aiTarget->trans.z - object->trans.z, work->aiTarget->trans.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 5:
            if (func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, work->aiTargetPos.x,
                                               work->aiTargetPos.z) < 100.0f) {
                work->aiState = work->unk_A4;
                return;
            }
            angle = atan2df(work->aiTargetPos.z - object->trans.z, work->aiTargetPos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
        case 4:
            if (OM_GET_DATA_PTR(D_8010AED8_bounce_n_trounce[work->aiTile], BounceNTrounceTileWork)->state != 0) {
                work->aiState = 0;
                return;
            }
            if (func_8010AAE0_bounce_n_trounce(object->trans.x, object->trans.z, work->aiTilePos.x,
                                               work->aiTilePos.z) < 100.0f) {
                work->aiState = 0;
                return;
            }
            angle = atan2df(work->aiTilePos.z - object->trans.z, work->aiTilePos.x - object->trans.x) + CRot.y;
            *stickX = cosdf(angle) * 80.0f;
            *stickY = -sindf(angle) * 80.0f;
            break;
    }
}

void func_80109478_bounce_n_trounce(omObjData *object) {
    omObjData *targets[4];
    s16 tiles[9];
    u16 aiStates[4][8] = {
        { 2, 2, 2, 3, 2, 4, 4, 3 },
        { 2, 3, 2, 3, 2, 3, 4, 3 },
        { 2, 3, 2, 3, 2, 3, 4, 3 },
        { 2, 3, 3, 3, 2, 3, 3, 3 },
    };
    BounceNTrounceWork *work;
    s32 count;
    s16 tileCount;
    s16 tile;
    s32 i;

    work = OM_GET_DATA_PTR(object, BounceNTrounceWork);
    work->aiState = aiStates[GwPlayer[work->playerId].cpu_difficulty][rand8() & 7];
    while (TRUE) {
        switch (work->aiState) {
            case 2:
                work->aiWait = rand8() % 30 + 20;
                return;
            case 3:
                count = 0;
                for (i = 0; i < 4; i++) {
                    if (i != work->playerId &&
                        OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork)->state < 2) {
                        targets[count++] = D_8010AEDC_bounce_n_trounce[i];
                    }
                }
                if (count == 0) {
                    work->aiState = 2;
                    break;
                }
                if (count == 1) {
                    work->aiTarget = targets[0];
                } else {
                    work->aiTarget = targets[rand8() % count];
                }
                func_80109804_bounce_n_trounce(object, 3);
                return;
            case 4:
                tileCount = 0;
                for (i = 0; i < 9; i++) {
                    if (OM_GET_DATA_PTR(D_8010AED8_bounce_n_trounce[i], BounceNTrounceTileWork)->state == 0) {
                        tiles[tileCount++] = i;
                    }
                }
                if (tileCount == 1) {
                    tile = tiles[0];
                } else {
                    tile = tiles[rand8() % tileCount];
                }
                work->aiTarget = D_8010AED8_bounce_n_trounce[tile];
                work->aiTilePos.x = D_8010ABEC_bounce_n_trounce[tile].x;
                work->aiTilePos.y = D_8010ABEC_bounce_n_trounce[tile].y;
                work->aiTilePos.z = D_8010ABEC_bounce_n_trounce[tile].z;
                work->aiTile = tile;
                return;
        }
    }
}

#ifdef NON_MATCHING
s32 func_80109804_bounce_n_trounce(omObjData *object, s16 arg1) {
    s16 tile;
    s16 targetTile;
    s16 nextTile;
    s32 diff;
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    tile = func_8010AB1C_bounce_n_trounce(object->trans.x, object->trans.z);
    targetTile = func_8010AB1C_bounce_n_trounce(work->aiTarget->trans.x, work->aiTarget->trans.z);
    diff = tile - targetTile;
    if (diff < 0) {
        diff = -diff;
    }
    if (diff == 1 || diff == 3) {
        return 0;
    }
    if (tile == 0 || tile == 2 || tile == 6 || tile == 8) {
        diff = tile - targetTile;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff != 2 && diff != 6) {
            return 0;
        }
        if (tile + 2 == targetTile) {
            nextTile = tile + 1;
        } else if (tile + 6 == targetTile) {
            nextTile = tile + 3;
        } else if (tile - 2 == targetTile) {
            nextTile = tile - 1;
        } else if (tile - 6 == targetTile) {
            nextTile = tile - 3;
        } else {
            goto end;
        }
        if (OM_GET_DATA_PTR(D_8010AED8_bounce_n_trounce[nextTile], BounceNTrounceTileWork)->state != 1) {
            work->aiState = 5;
            work->unk_A4 = arg1;
            work->aiTargetPos.x = D_8010ABEC_bounce_n_trounce[nextTile].x;
            work->aiTargetPos.y = D_8010ABEC_bounce_n_trounce[nextTile].y;
            work->aiTargetPos.z = D_8010ABEC_bounce_n_trounce[nextTile].z;
        }
    }
end:
    // The original has no return value here.
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109804_bounce_n_trounce);
#endif

s16 func_80109A00_bounce_n_trounce(omObjData *object) {
    f32 dists[9]; // Unused stack space retained from the original function.
    f32 minDist = 1000000.0f;
    s32 result = 0;
    u16 i;

    for (i = 0; i < 9; i++) {
        if (OM_GET_DATA_PTR(D_8010AED8_bounce_n_trounce[i], BounceNTrounceTileWork)->state == 0) {
            if (HuSqrtf((object->trans.x - D_8010ABEC_bounce_n_trounce[i].x) *
                            (object->trans.x - D_8010ABEC_bounce_n_trounce[i].x) +
                        (object->trans.z - D_8010ABEC_bounce_n_trounce[i].z) *
                            (object->trans.z - D_8010ABEC_bounce_n_trounce[i].z)) < minDist) {
                result = i;
            }
        }
    }
    return result;
}

void func_80109AF0_bounce_n_trounce(omObjData *object) {
    omObjData *player;
    BounceNTrounceWork *work;
    f32 angle;
    s32 i;

    switch (D_8010AEC8_bounce_n_trounce) {
        case 0:
            WipeCreateIn(0xFF, 16);
            D_8010AEC8_bounce_n_trounce = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                D_8010AEC8_bounce_n_trounce = 2;
            }
            break;
        case 2:
            player = D_8010AEDC_bounce_n_trounce[0];
            work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
            if (work->motState == 2) {
                if (++D_8010AD86_bounce_n_trounce == 6) {
                    D_8010AD84_bounce_n_trounce = 1;
                }
            }
            for (i = 0; i < 4; i++) {
                player = D_8010AEDC_bounce_n_trounce[i];
                work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                if (work->motState == 2 && D_8010AD84_bounce_n_trounce == 1) {
                    D_8010ABE0_bounce_n_trounce[i] |= 0x8000;
                }
            }
            if (D_8010AD84_bounce_n_trounce == 1) {
                D_8010AEC8_bounce_n_trounce = 3;
            }
            break;
        case 3:
            if (D_8010AEDC_bounce_n_trounce[0]->trans.y > 500.0f) {
                for (i = 0; i < 4; i++) {
                    D_8010ABE0_bounce_n_trounce[i] |= 0x2000;
                }
                D_8010AEC8_bounce_n_trounce = 4;
            }
            break;
        case 4:
            player = D_8010AEDC_bounce_n_trounce[0];
            work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
            if (work->motState == 2) {
                for (i = 0; i < 4; i++) {
                    player = D_8010AEDC_bounce_n_trounce[i];
                    work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                    angle = atan2df(-player->trans.x, -player->trans.z);
                    player->rot.y = angle;
                    angle -= 180.0f;
                    work->unk_64 = sindf(angle) * 30.0f;
                    work->unk_68 = cosdf(angle) * 30.0f;
                    work->unk_6C = 0.925f;
                    work->unk_16 = 1;
                    work->unk_0A = 0;
                    player->func = NULL;
                    omVibrate(work->playerId, 2, 2, 20);
                }
                D_8010AEC8_bounce_n_trounce = 5;
            }
            break;
        case 5:
            for (i = 0; i < 4; i++) {
                player = D_8010AEDC_bounce_n_trounce[i];
                work = OM_GET_DATA_PTR(player, BounceNTrounceWork);
                player->trans.x += work->unk_64;
                player->trans.z += work->unk_68;
                Hu3DModelPosSet(player->model[1], player->trans.x, player->trans.y, player->trans.z);
                Hu3DModelPosSet(player->model[2], player->trans.x, player->trans.y + 1.0f, player->trans.z);
                Hu3DModelRotSet(player->model[1], player->rot.x, player->rot.y, player->rot.z);
                work->unk_64 *= work->unk_6C;
                work->unk_68 *= work->unk_6C;
                if (fabs(work->unk_64) < 1.0) {
                    work->unk_64 = 0.0f;
                }
                if (fabs(work->unk_68) < 1.0) {
                    work->unk_68 = 0.0f;
                }
                if (work->unk_64 == 0.0f && work->unk_68 == 0.0f) {
                    D_8010AEC8_bounce_n_trounce = 6;
                    HuAudSeqPlay(0x37);
                }
            }
            break;
        case 6:
            for (i = 0; i < 4; i++) {
                D_8010AEDC_bounce_n_trounce[i]->func = func_80106F78_bounce_n_trounce;
            }
            omDelObj(object);
            D_8010AEC0_bounce_n_trounce = NULL;
            func_800E6F0C_minigame(1);
            break;
    }
}

#ifdef NON_MATCHING
void func_80109F68_bounce_n_trounce(omObjData *object) {
    omObjData *player;
    f32 dist;
    f32 diff;
    s32 i;

    switch (D_8010AECA_bounce_n_trounce) {
        case 0:
            D_8010AED4_bounce_n_trounce->work[0] = 0;
            D_8010AEB0_bounce_n_trounce = 45;
            D_8010AECA_bounce_n_trounce = 1;
            for (i = 0; i < 4; i++) {
                OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork)->radius = 50.0f;
            }
            break;
        case 1:
            if (D_8010AEB0_bounce_n_trounce == 0) {
                if (D_8010AD88_bounce_n_trounce == 1) {
                    D_8010AECA_bounce_n_trounce = D_8010AEB2_bounce_n_trounce;
                }
            } else {
                D_8010AEB0_bounce_n_trounce--;
            }
            if (D_8010AD88_bounce_n_trounce != 0) {
                break;
            }
            if (D_8010AEBC_bounce_n_trounce != 0) {
                if (func_80108994_bounce_n_trounce() != 1) {
                    break;
                }
                if (D_8010AEBC_bounce_n_trounce == 1) {
                    for (i = 0; i < 4; i++) {
                        if (OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork)->state == 4) {
                            D_8010AEBE_bounce_n_trounce = i;
                            D_8010ABB0_bounce_n_trounce.unk18[0] = D_8010AEBE_bounce_n_trounce;
                            D_8010AEB2_bounce_n_trounce = 3;
                            D_8010AD88_bounce_n_trounce = 1;
                        }
                    }
                    break;
                }
            }
            D_8010ABB0_bounce_n_trounce.unk06 = 4;
            D_8010AEB2_bounce_n_trounce = 2;
            D_8010AD88_bounce_n_trounce = 1;
            break;
        case 2:
            func_800E6F0C_minigame(4);
            for (i = 0; i < 4; i++) {
                if (OM_GET_DATA_PTR(D_8010AEDC_bounce_n_trounce[i], BounceNTrounceWork)->state == 4) {
                    Hu3DMotionShiftSet(D_8010AEDC_bounce_n_trounce[i]->model[1],
                                       Hu3DData[D_8010AEDC_bounce_n_trounce[i]->motion[5]].motId, 0, 6, 0);
                }
            }
            D_8010AECA_bounce_n_trounce = 6;
            break;
        case 3:
            player = D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce];
            D_8010AEB8_bounce_n_trounce = 1350.0f;
            dist = HuSqrtf(player->trans.x * player->trans.x + player->trans.z * player->trans.z);
            if (dist > 560.0f && (player->trans.z > 0.0f || player->trans.x > 0.0f)) {
                D_8010AEB8_bounce_n_trounce += (dist - 560.0f) / 113.0f * 400.0f;
            }
            D_8010AEB4_bounce_n_trounce = (D_8010AEB8_bounce_n_trounce - CZoom) / 30.0f;
            Hu3DMotionShiftSet(D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce]->model[1],
                               Hu3DData[D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce]->motion[2]].motId, 0,
                               6, 0);
            D_8010AECA_bounce_n_trounce = 4;
            break;
        case 4:
            CZoom += D_8010AEB4_bounce_n_trounce;
            if (CZoom < D_8010AEB8_bounce_n_trounce) {
                CZoom = D_8010AEB8_bounce_n_trounce;
                D_8010AECA_bounce_n_trounce = 5;
            }
            if (D_8010AD8A_bounce_n_trounce != 0) {
                break;
            }
            player = D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce];
            if (player->rot.y >= 360.0f) {
                player->rot.y -= 360.0f;
            }
            if (player->rot.y < 0.0f) {
                player->rot.y += 360.0f;
            }
            diff = CRot.y + 0.0f - player->rot.y;
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                if (diff > 8.0f) {
                    player->rot.y += 8.0f;
                } else {
                    player->rot.y += diff;
                }
            } else if (360.0f - diff > 8.0f) {
                player->rot.y -= 8.0f;
            } else {
                player->rot.y -= 360.0f - diff;
            }
            Hu3DModelRotSet(player->model[1], player->rot.x, player->rot.y, player->rot.z);
            if (fabs(player->rot.y - (CRot.y + 0.0f)) < 0.1f) {
                Hu3DMotionShiftSet(player->model[1], Hu3DData[player->motion[1]].motId, 0, 6, 0);
                D_8010AD8A_bounce_n_trounce = 1;
            }
            break;
        case 5:
            Hu3DMotionShiftSet(D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce]->model[1],
                               Hu3DData[D_8010AEDC_bounce_n_trounce[D_8010AEBE_bounce_n_trounce]->motion[4]].motId, 0,
                               6, 0);
            func_800E6F0C_minigame(4);
            func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010AEBE_bounce_n_trounce].chr][0] | 0x2F);
            GwPlayer[D_8010AEBE_bounce_n_trounce].bonusCoin = 10;
            D_8010AECA_bounce_n_trounce = 6;
            break;
        case 6:
            omDelObj(object);
            D_8010AEC4_bounce_n_trounce = NULL;
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109F68_bounce_n_trounce);
#endif

void func_8010A664_bounce_n_trounce(omObjData *object) {
    f32 maxY;
    s32 i;

    if (object->work[0] != 0) {
        maxY = 0.0f;
        for (i = 0; i < 4; i++) {
            if (maxY < D_8010AEDC_bounce_n_trounce[i]->trans.y) {
                maxY = D_8010AEDC_bounce_n_trounce[i]->trans.y;
            }
        }
        if (maxY > 300.0f) {
            maxY -= 300.0f;
            CZoom = maxY * 700.0f / 700.0f + 2100.0f;
            if (CZoom > 2800.0f) {
                CZoom = 2800.0f;
            }
        } else {
            CZoom = 2100.0f;
        }
    }
}

void func_8010A740_bounce_n_trounce(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *modelData = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = modelData->unk58;
    s16 i;
    s32 tile;
    f32 floorY;

    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C;
            particle->unk14 += particle->unk20;
            particle->unk18 *= particle->unk24;
            particle->unk20 *= particle->unk2C;
            particle->unk1C *= particle->unk28;
            particle->unk08 += particle->unk04;
            if (particle->unk08 < 0.0f) {
                particle->unk08 = 0.0f;
            }
            tile = (s16)func_8010AB1C_bounce_n_trounce(particle->unk0C, particle->unk14);
            if (tile >= 0 && tile < 9) {
                floorY = D_8010AED8_bounce_n_trounce[tile]->trans.y;
                if (particle->unk10 < floorY && particle->unk10 > floorY - 300.0f) {
                    particle->unk08 = 0.0f;
                }
            }
        }
    }
    modelData->unk02++;
}

#ifdef NON_MATCHING
void func_8010A8F0_bounce_n_trounce(omObjData *object) {
    omObjData *player = (omObjData *)object->work[1];
    BounceNTrounceWork *playerWork = OM_GET_DATA_PTR(player, BounceNTrounceWork);
    BounceNTrounceEmitterWork *work;
    HmfModelData_UnkBC_Struct *modelData;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    HmfData *hmf;
    s16 count;
    s32 i;
    f32 angle;
    f32 speed;

    if (object->work[0] == 0) {
        return;
    }
    if (object->work[2] != 0) {
        object->work[2]--;
        return;
    }
    work = OM_GET_DATA_PTR(object, BounceNTrounceEmitterWork);
    modelData = Hu3DData[player->model[5]].unkBC;
    hmf = Hu3DData[player->model[5]].hmf;
    particle = modelData->unk58;
    count = hmf->unk1A;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            break;
        }
    }
    if (i == hmf->unk1A) {
        return;
    }
    object->work[2] = work->interval;
    angle = work->angle;
    work->angle += work->angleStep;
    if (work->angle >= 360.0f) {
        work->angle -= 360.0f;
    }
    particle->unk0C = player->trans.x;
    particle->unk10 = player->trans.y + 120.0f;
    particle->unk14 = player->trans.z;
    speed = playerWork->unk_44 / 7.0f;
    if (speed < 10.0f) {
        speed = 10.0f;
    }
    particle->unk18 = sindf(angle) * speed;
    particle->unk20 = cosdf(angle) * speed;
    particle->unk1C = -10.0f;
    particle->unk2C = particle->unk24 = 0.95f;
    particle->unk28 = 1.05f;
    particle->unk04 = -0.22f;
    particle->unk08 = 10.0f;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_8010A8F0_bounce_n_trounce);
#endif

f32 func_8010AAE0_bounce_n_trounce(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return HuSqrtf((arg0 - arg2) * (arg0 - arg2) + (arg1 - arg3) * (arg1 - arg3));
}

s32 func_8010AB1C_bounce_n_trounce(f32 arg0, f32 arg1) {
    s32 x;
    s32 y;
    s16 index;

    arg0 += 450.0f;
    arg1 += 450.0f;
    x = arg0 / 300.0f;
    y = arg1 / 300.0f;
    index = x + y * 3;
    return (index >= 0 && index < 9) ? index : -1;
}
