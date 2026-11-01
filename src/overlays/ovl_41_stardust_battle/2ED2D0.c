#include "common.h"
#include "overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"

typedef struct UnkStardustBattleStard {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 modelId;
    /* 0x04 */ s16 angleX;
    /* 0x06 */ s16 angleY;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 radius;
    /* 0x18 */ f32 radius2;
    /* 0x1C */ f32 worldX;
    /* 0x20 */ f32 worldY;
    /* 0x24 */ f32 worldZ;
} UnkStardustBattleStard; // sizeof 0x28

typedef union StardustBattleWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} StardustBattleWorkBytes;

typedef struct UnkStardustBattleObj {
    /* 0x00 */ char unk_00[0x3A];
    /* 0x3A */ s16 unk_3A;
    /* 0x3E */ char unk_3E[0x2E];
    /* 0x6C */ void (*func_6C)(omObjData *);
} UnkStardustBattleObj; // sizeof 0x70

/* One entry of the stardust pool allocated by func_8010CB34_stardust_battle.
   The pool is indexed by UnkStardustBattleStars.count. */
typedef struct UnkStardustBattleStar { // sizeof 0x7C
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk_02[0x02];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk_06[0x10];
    /* 0x16 */ s16 state;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x28 */ f32 x;
    /* 0x2C */ f32 y;
    /* 0x30 */ f32 z;
    /* 0x34 */ f32 targetX;
    /* 0x38 */ f32 targetY;
    /* 0x3C */ f32 targetZ;
    /* 0x40 */ char unk_40[0x0C];
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 oldX;
    /* 0x5C */ f32 oldY;
    /* 0x60 */ f32 oldZ;
    /* 0x64 */ char unk_64[0x18];
} UnkStardustBattleStar;

typedef struct UnkStardustBattleStars { // sizeof 0x10
    /* 0x00 */ s16 modelId1;
    /* 0x02 */ s16 modelId2;
    /* 0x04 */ s16 effectId1;
    /* 0x06 */ s16 effectId2;
    /* 0x08 */ s16 count;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ UnkStardustBattleStar *star;
} UnkStardustBattleStars;

typedef struct UnkStardustBattleStreak {
    /* 0x00 */ char unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ char unk_02[0x3A];
} UnkStardustBattleStreak; // sizeof 0x3C

typedef struct UnkStardustBattleStreaks {
    /* 0x00 */ char unk_00[0x28];
    /* 0x28 */ UnkStardustBattleStreak *unk_28;
} UnkStardustBattleStreaks; // sizeof 0x2C

extern omObjData *D_80114B58_stardust_battle;
extern omObjData *D_80114B18_stardust_battle;
extern UnkStardustBattleStard *D_80114B5C_stardust_battle;
extern UnkStardustBattleStars *D_80114B2C_stardust_battle;

extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB774_minigame;

/* Call sites pass only the object and use the result as a pointer, so this
   can't use the definition's full prototype. */
u32 func_80111FEC_stardust_battle(); // Unprototyped: called with varying argument counts.
void func_80108120_stardust_battle(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801059A0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80105D18_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114100_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011410C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80105DA0_stardust_battle);

void func_801065B4_stardust_battle(void) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801065D8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106A3C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106B60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106C30_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106D0C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106EB0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801073F4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107760_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107DCC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107E84_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107F34_stardust_battle);

s16 func_80107FA4_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    obj->func_6C = func_80108120_stardust_battle;
    obj->unk_3A = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107FE8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108074_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801080B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801080EC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108120_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801081FC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801082C4_stardust_battle);

void func_80108404_stardust_battle(void) {
    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
}

void func_80108444_stardust_battle(void) {
}

void func_8010844C_stardust_battle(void) {
}

/* Like func_80107FA4, the return value of func_80111FEC_stardust_battle is
   treated as a pointer. */
void func_80108454_stardust_battle(void) {
    UnkStardustBattleStars *stars = (UnkStardustBattleStars *)func_80111FEC_stardust_battle();

    D_800EB744_minigame = 1.029f;
    D_800EB748_minigame = 0.105000004f;
    D_800EB774_minigame = 1.19f;
    stars->unk_0A = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801084B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801086E8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010882C_stardust_battle);

void func_801089B4_stardust_battle(void) {
}

void func_801089BC_stardust_battle(omObjData *object) {
    HmfModel *model;
    HmfModel *shadow;
    func_800E1BA8_minigame_ObjData *data;

    if (object->model[10] == -1) {
        return;
    }

    func_80111FEC_stardust_battle(object);
    data = object->data;
    model = &HmfModelData[object->model[0]];
    shadow = &HmfModelData[object->model[10]];
    Hu3DModelPosSet(object->model[10], object->trans.x, -object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[10], object->rot.x, data->unk3C, object->rot.z);
    shadow->motId = model->motId;
    shadow->motTime = model->motTime;
    shadow->motSpeed = 0;
    shadow->motIdShift = model->motIdShift;
    shadow->motShiftTime = model->motShiftTime;
    shadow->motShiftSpeed = 0;
    shadow->motIdShape = model->motIdShape;
    shadow->motShapeTime = model->motShapeTime;
    shadow->motShapeSpeed = 0;
    shadow->unk0C = model->unk0C;
    shadow->unk0E = model->unk0E;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108AC4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108B34_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108C14_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108D84_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108EC4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109128_stardust_battle);

/* Like func_80107FA4, the return value of func_80111FEC_stardust_battle is
   treated as a pointer. */
s16 func_8010929C_stardust_battle(void) {
    if (D_800EBE28_minigame == 0) {
        return 0;
    }

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    return *(s16 *)func_80111FEC_stardust_battle(D_800EC1BC_minigame[D_800EBE28_minigame]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801092F0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801093CC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109424_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109B18_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109F94_stardust_battle);

void func_80109FE4_stardust_battle(void) {
    UnkStardustBattleStreaks *streaks = (UnkStardustBattleStreaks *)func_80111FEC_stardust_battle();
    UnkStardustBattleStreak *streak;
    s32 i;

    if (streaks->unk_28 == NULL) {
        streak = streaks->unk_28 = (UnkStardustBattleStreak *)HuMemAllocTag(0xF00, TAG_OVERLAY);
        memset(streak, 0, 0xF00);

        for (i = 0; i < 64; i++, streak++) {
            streak->unk_01 = i;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A04C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A204_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A418_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A5A4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A5E0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A74C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010AAC4_stardust_battle);

void func_8010BFE4_stardust_battle(f32 arg0, s16 arg1) {
    UnkStardustBattleStar *star;

    if (D_80114B18_stardust_battle == NULL) {
        return;
    }

    star = (UnkStardustBattleStar *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);

    if (arg1 > 0) {
        star->unk_24 = arg1;
        star->y = (arg0 - D_80114B18_stardust_battle->trans.y) / arg1;
    }
}

void func_8010C06C_stardust_battle(void) {
    UnkStardustBattleStar *star;

    if (D_80114B18_stardust_battle != NULL) {
        star = (UnkStardustBattleStar *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        star->y = 0.0f;
        star->unk_24 = 0;

        if (star->unk_04 != 7) {
            star->x = star->z = 0.0f;
            star->unk_04 = 11;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C0C8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C1F8_stardust_battle);

/* Unlike the other func_80111FEC_stardust_battle call sites, the return value
   is unused here; the stardust object is read straight from the global. */
void func_8010C2CC_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &HmfModelData[obj->model[0]];
        model->motSpeed = arg0;
    }
}

f32 func_8010C32C_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }

    func_80111FEC_stardust_battle(obj);
    model = &HmfModelData[obj->model[0]];
    return model->motSpeed;
}

void func_8010C38C_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &HmfModelData[obj->model[0]];
        model->motTime = arg0;
    }
}

f32 func_8010C3EC_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }

    func_80111FEC_stardust_battle(obj);
    model = &HmfModelData[obj->model[0]];
    return model->motTime;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C44C_stardust_battle);

void func_8010C498_stardust_battle(void) {
    UnkStardustBattleStar *star;

    if (D_80114B18_stardust_battle != NULL) {
        star = (UnkStardustBattleStar *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        star->unk_18 = 0;
        star->active = 0;
        star->unk_04 = 17;
        HuAudFXPlay(0x50B);
        star->unk_4C = D_80114B18_stardust_battle->trans.x;
        star->unk_50 = D_80114B18_stardust_battle->trans.y;
        star->unk_54 = D_80114B18_stardust_battle->trans.z;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C508_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C538_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C5A8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CA48_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CB34_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CE5C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114528_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011452C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114530_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", jtbl_80114538_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114550_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114558_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114560_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114568_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114570_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114578_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114580_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114588_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114590_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114598_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_801145A0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DADC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DE64_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010DF70_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E03C_stardust_battle);

/* Returns the indexed star, or NULL if the index is out of range or the star
   isn't in use. */
UnkStardustBattleStar *func_8010E300_stardust_battle(s16 arg0) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 >= stars->count) {
        return NULL;
    }
    star = &stars->star[arg0];
    return star->active ? star : NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E35C_stardust_battle);

void func_8010E46C_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 < stars->count) {
        star = &stars->star[arg0];
        if (star->active != 0) {
            star->x = arg1;
            star->y = arg2;
            star->z = arg3;
        }
    }
}

void func_8010E4C8_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 < stars->count) {
        star = &stars->star[arg0];
        if (star->active != 0) {
            star->targetX = arg1;
            star->targetY = arg2;
            star->targetZ = arg3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E524_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EA04_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010ED7C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EE38_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EE7C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F0E8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F400_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F580_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F5B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F5E0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F73C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F890_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FA60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FBCC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FCBC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FE74_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110364_stardust_battle);

void func_80110758_stardust_battle(f32 x, f32 y, f32 z) {
    omObjData *obj = D_80114B58_stardust_battle;

    if (obj != NULL) {
        obj->trans.x = x;
        obj->trans.y = y;
        obj->trans.z = z;
    }
}

void func_80110780_stardust_battle(s16 arg0) {
    UnkStardustBattleStard *stard = D_80114B5C_stardust_battle;
    s32 i;

    if (stard != NULL) {
        for (i = 0; i < 16; i++, stard++) {
            if (arg0 > i) {
                stard->active = 1;
            } else {
                stard->active = 0;
            }
        }
    }
}

void func_801107C4_stardust_battle(void) {
    omObjData *obj = D_80114B58_stardust_battle;

    if (obj != NULL) {
        obj->work[0] = 1;
        obj->work[1] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801107E4_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_801146FC_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110914_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111004_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801115F8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801117E4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801119D4_stardust_battle);

f32 func_80111B28_stardust_battle(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111C2C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111DF8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111E10_stardust_battle);

void func_80111E70_stardust_battle(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 16; i++) {
        arg2[i] = arg0[i] + arg3 * (arg1[i] - arg0[i]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111EB8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111F38_stardust_battle);

void func_80111FC0_stardust_battle(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_80111FEC_stardust_battle(omObjData *object, s32 arg1, u32 arg2) {
    StardustBattleWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80112040_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80112220_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801122D0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801127B8_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80112980_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80113568_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8011376C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801138A0_stardust_battle);
