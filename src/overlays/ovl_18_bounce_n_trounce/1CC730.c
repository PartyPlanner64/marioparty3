#include "common.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

// Per-player work, allocated in func_801069F0_bounce_n_trounce
typedef struct BounceNTrounceWork {
    /* 0x00 */ u16 playerId;
    /* 0x02 */ u16 state;
    /* 0x04 */ u16 motState;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ u16 unk_0E[4];
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ s16 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ f32 motSpeed;
    /* 0x24 */ f32 motDir;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ s32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ Vec startPos;
    /* 0x58 */ Vec unk_58;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ omObjData *shadowObj;
    /* 0x7C */ s16 unk_7C;
    /* 0x7E */ s16 unk_7E;
    /* 0x80 */ Vec aiTargetPos;
    /* 0x8C */ char pad_8C[0x10];
    /* 0x9C */ omObjData *aiTarget;
    /* 0xA0 */ s16 aiState;
    /* 0xA2 */ s16 unk_A2;
    /* 0xA4 */ s16 unk_A4;
    /* 0xA6 */ char pad_A6[2];
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

extern f32 D_800D2120_main;

extern s8 D_8010ABD8_bounce_n_trounce[4];
extern s8 D_8010ABDC_bounce_n_trounce[4];
extern u16 D_8010ABE0_bounce_n_trounce[4];
extern Vec D_8010ABEC_bounce_n_trounce[9];
extern s16 D_8010ACE4_bounce_n_trounce[9];
extern u16 D_8010ACF6_bounce_n_trounce;
extern u16 D_8010ACF8_bounce_n_trounce;
extern u16 D_8010ABE8_bounce_n_trounce;
extern Vec D_8010AD4C_bounce_n_trounce[4];
extern u16 D_8010AD7C_bounce_n_trounce[4];
extern u16 D_8010AEBC_bounce_n_trounce;
extern omObjData *D_8010AEC0_bounce_n_trounce;
extern omObjData *D_8010AEC4_bounce_n_trounce;
extern s16 D_8010AEC8_bounce_n_trounce;
extern s16 D_8010AECA_bounce_n_trounce;
extern s16 D_8010AECC_bounce_n_trounce;
extern omObjData *D_8010AED0_bounce_n_trounce;
extern omObjData *D_8010AED4_bounce_n_trounce;
extern omObjData **D_8010AED8_bounce_n_trounce;
extern omObjData **D_8010AEDC_bounce_n_trounce;

void func_80105CBC_bounce_n_trounce(omObjData *);
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
s32 func_8010AB1C_bounce_n_trounce(f32 x, f32 z);
void func_80108CA8_bounce_n_trounce(omObjData *);
void func_80108D28_bounce_n_trounce(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801059A0_bounce_n_trounce);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80105E4C_bounce_n_trounce);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80106434_bounce_n_trounce);

void func_8010675C_bounce_n_trounce(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801069F0_bounce_n_trounce);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80107EDC_bounce_n_trounce);

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

void func_80108454_bounce_n_trounce(omObjData *object, s32 arg1) {
    BounceNTrounceWork *work = OM_GET_DATA_PTR(object, BounceNTrounceWork);

    work->unk_2C = arg1;
    work->unk_3C = 0;
    work->unk_40 = object->trans.y;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_801085EC_bounce_n_trounce);

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

s32 func_80108994_bounce_n_trounce(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80108D28_bounce_n_trounce);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109018_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109478_bounce_n_trounce);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", D_8010AE14_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109AF0_bounce_n_trounce);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_18_bounce_n_trounce/1CC730", func_80109F68_bounce_n_trounce);

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
