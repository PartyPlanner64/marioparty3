#include "common.h"
#include "overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"

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

/* Work data of the D_80114B18_stardust_battle object, retrieved with
   func_80111FEC_stardust_battle. */
typedef struct UnkStardustBattleActor {
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk_02[0x02];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk_06[0x12];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ f32 velX;
    /* 0x2C */ f32 velY;
    /* 0x30 */ f32 velZ;
    /* 0x34 */ Vec target;
    /* 0x40 */ Vec start;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
} UnkStardustBattleActor;

/* One entry of the stardust pool allocated by func_8010CB34_stardust_battle.
   The pool is indexed by UnkStardustBattleStars.count. */
typedef struct UnkStardustBattleStar {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 model[6];
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 state;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ char unk_1C[0x0C];
    /* 0x28 */ f32 x;
    /* 0x2C */ f32 y;
    /* 0x30 */ f32 z;
    /* 0x34 */ f32 targetX;
    /* 0x38 */ f32 targetY;
    /* 0x3C */ f32 targetZ;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ char unk_4C[0x1C];
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ f32 unk_78;
} UnkStardustBattleStar; // sizeof 0x7C

typedef struct UnkStardustBattleStars { // sizeof 0x10
    /* 0x00 */ s16 modelId1;
    /* 0x02 */ s16 modelId2;
    /* 0x04 */ s16 effectId1;
    /* 0x06 */ s16 effectId2;
    /* 0x08 */ s16 count;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ UnkStardustBattleStar *star;
} UnkStardustBattleStars;

typedef struct UnkStardustBattleScoreDisp {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 sprGrp;
    /* 0x04 */ s16 state;
    /* 0x06 */ s16 timer;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 scale;
} UnkStardustBattleScoreDisp; // sizeof 0x14

typedef struct UnkStardustBattleSpot {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 followPlayer;
    /* 0x04 */ Vec pos;
} UnkStardustBattleSpot; // sizeof 0x10

typedef struct UnkStardustBattleSpots {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 max;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ UnkStardustBattleSpot *spot;
} UnkStardustBattleSpots; // sizeof 0xC

typedef struct UnkStardustBattleStreak {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 index;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} UnkStardustBattleStreak; // sizeof 0x3C

/* Work data of the object created by func_80108B34_stardust_battle. */
typedef struct UnkStardustBattleStage {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x24 */ void *unk_24;
    /* 0x28 */ UnkStardustBattleStreak *streaks;
    /* 0x2C */ s16 unk_2C;
    /* 0x30 */ void (*func_30)(omObjData *);
    /* 0x34 */ void (*func_34)(omObjData *);
} UnkStardustBattleStage; // sizeof 0x38

/* Work data of the player object, packed into omObjData.work and retrieved
   with func_80111FEC_stardust_battle. */
typedef struct UnkStardustBattleObj {
    /* 0x00 */ char unk_00[0x0A];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ char unk_0C[0x06];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ char unk_14[0x10];
    /* 0x24 */ s16 character;
    /* 0x26 */ char unk_26[0x12];
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ char unk_3E[0x2E];
    /* 0x6C */ void (*func_6C)(omObjData *);
    /* 0x70 */ void (*func_70)(omObjData *);
    /* 0x74 */ void (*func_74)(omObjData *);
    /* 0x78 */ void (*func_78)(omObjData *);
} UnkStardustBattleObj; // sizeof 0x7C

extern omObjData *D_80114B58_stardust_battle;
extern omObjData *D_80114B18_stardust_battle;
extern UnkStardustBattleStard *D_80114B5C_stardust_battle;
extern UnkStardustBattleStars *D_80114B2C_stardust_battle;
extern UnkStardustBattleScoreDisp *D_80114B44_stardust_battle;
extern u8 D_800D2008_main;
extern s16 D_80114B54_stardust_battle;
extern UnkStardustBattleStage *D_80114B10_stardust_battle;
extern UnkStardustBattleSpots *D_80114B20_stardust_battle;
extern Vec D_80113EB8_stardust_battle;
extern omObjData *D_80114B50_stardust_battle;
extern u8 D_80114B38_stardust_battle[2][6];
extern s32 D_800A178C_main[][6];
extern s32 D_80113DE4_stardust_battle;
extern s16 D_80113DE6_stardust_battle[];
extern void (*D_80113E24_stardust_battle[])(omObjData *);
extern void (*D_80113E30_stardust_battle[])(omObjData *);
extern void (*D_80113E3C_stardust_battle[])(omObjData *);
extern void (*D_80113E48_stardust_battle[])(omObjData *);
extern s32 D_80113E54_stardust_battle[];
extern s32 D_80113E60_stardust_battle[];
extern s32 D_80113E6C_stardust_battle[];
extern void (*D_80113E78_stardust_battle[])(omObjData *);
extern void (*D_80113E84_stardust_battle[])(omObjData *);
extern s32 D_80113EF0_stardust_battle[];
extern s32 D_80113EFC_stardust_battle[];

/* Call sites pass only the object and use the result as a pointer, so this
   can't use the definition's full prototype. */
u32 func_80111FEC_stardust_battle(); // Unprototyped: called with varying argument counts.
void func_80108120_stardust_battle(omObjData *object);
void func_80108C14_stardust_battle(omObjData *object);
void func_80107DCC_stardust_battle(omObjData *object, s16 mode);
void func_8010FBCC_stardust_battle(omObjData *object);
void func_8010C5A8_stardust_battle(s16 count, s16 arg1);
void func_80111FC0_stardust_battle(omObjData *arg0, u32 arg1);
void func_801081FC_stardust_battle(omObjData *object);
void func_801082C4_stardust_battle(omObjData *object);
void func_8010A690_stardust_battle(omObjData *object);
void func_8010A5A4_stardust_battle(omObjData *object);
void func_8010C1F8_stardust_battle(s16 motion, s16 startTime, s16 endTime, u8 attr);
void func_8010DF70_stardust_battle(s16 index);
f32 func_80111EB8_stardust_battle(f32 x, f32 y);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801059A0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80105D18_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114100_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011410C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80105DA0_stardust_battle);

void func_801065B4_stardust_battle(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_801065D8_stardust_battle(omObjData *object) {
    if (D_80113DE4_stardust_battle != 0) {
        if (D_80113DE4_stardust_battle == 1) {
            object->func = func_801065B4_stardust_battle;
        }
        D_80113DE4_stardust_battle--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_80113DE4_stardust_battle = 16;
        WipeColorSet(0, 0, 0);
        WipeCreateOut(0, D_80113DE6_stardust_battle[0]);
        HuAudSeqFadeOut(D_80113DE6_stardust_battle[0]);
        func_8004AB0C_main(D_80113DE6_stardust_battle[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106A3C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106B60_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106C30_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106D0C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106EB0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801073F4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107760_stardust_battle);

void func_80107DCC_stardust_battle(omObjData *object, s16 mode) {
    UnkStardustBattleObj *obj;

    if (object != NULL) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
        if (obj->func_78 != NULL) {
            obj->func_78(object);
            obj->func_78 = NULL;
        }
        if (D_80113E24_stardust_battle[mode] != NULL) {
            D_80113E24_stardust_battle[mode](object);
        }
        obj->func_70 = D_80113E30_stardust_battle[mode];
        obj->func_74 = D_80113E3C_stardust_battle[mode];
        obj->func_78 = D_80113E48_stardust_battle[mode];
    }
}

s16 func_80107E84_stardust_battle(s16 arg0) {
    omObjData *object = D_800EC598_minigame[0];
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    HmfModel *other = &Hu3DData[object->model[9]];
    HmfData *hmf;

    if (obj->unk_12 == arg0) {
        return arg0;
    }
    hmf = other->hmf;
    other->hmf = model->hmf;
    model->hmf = hmf;
    obj->unk_12 = arg0;
    return arg0;
}

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

s16 func_80107FE8_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    if (obj->func_6C != func_80108120_stardust_battle || obj->unk_3A < 2 || obj->unk_3C < 22.5f) {
        return 0;
    }
    return 1;
}

void func_80108074_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = func_801081FC_stardust_battle;
    }
}

void func_801080B0_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = func_801082C4_stardust_battle;
    }
}

void func_801080EC_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = NULL;
    }
}

void func_80108120_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);

    switch (obj->unk_3A) {
        case 0:
            func_800E5690_minigame(object, 40);
            obj->unk_3A++;
            break;
        case 1:
            if (func_800E4A90_minigame(object) == 1) {
                func_800E5690_minigame(object, 41);
                obj->unk_3A++;
                obj->unk_3C = 0;
            }
            break;
        case 2:
            obj->unk_3C++;
            if (func_800E4A90_minigame(object) == 1) {
                obj->func_6C = NULL;
                obj->unk_3C = 0;
                obj->unk_3A = 0;
            }
            break;
    }
}

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
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle();

    D_800EB744_minigame = 1.029f;
    D_800EB748_minigame = 0.105000004f;
    D_800EB774_minigame = 1.19f;
    obj->unk_0A = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801084B0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801086E8_stardust_battle);

void func_8010882C_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    HmfModel *shadow;

    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
    object->model[10] =
        func_8000B108_main(D_800A178C_main[obj->character][0] | D_800A178C_main[obj->character][1], 0x689);
    func_8001ED54_main(object->model[10]);
    Hu3DModelRemakeStatic(object->model[10]);
    func_8001C514_main(object->model[10]);
    shadow = &Hu3DData[object->model[10]];
    obj->unk_38 = shadow->motId;
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
    guMtxIdentF(shadow->mtx);
    mtxScaleCat(shadow->mtx, 1.0f, -1.0f, 1.0f);
}

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
    model = &Hu3DData[object->model[0]];
    shadow = &Hu3DData[object->model[10]];
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

void func_80108AC4_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *shadow = &Hu3DData[object->model[10]];

    shadow->motId = obj->unk_38;
    shadow->motIdShift = 0xFF;
    shadow->motIdShape = 0xFF;
    Hu3DModelKill(object->model[10]);
    object->model[10] = -1;
}

void func_80108B34_stardust_battle(void) {
    UnkStardustBattleStage *stage = HuMemAllocTag(sizeof(UnkStardustBattleStage), TAG_OVERLAY);

    D_80114B10_stardust_battle = stage;
    memset(stage, 0, sizeof(UnkStardustBattleStage));
    stage->unk_00 = -1;
    stage->unk_20 = 0;
    stage->unk_24 = NULL;
    stage->streaks = NULL;
    stage->func_30 = NULL;
    stage->func_34 = NULL;
    D_800EC1C0_minigame[D_800EBE28_minigame] = omAddObj(3, 8, 0, -1, func_80108C14_stardust_battle);
    omSetStatBit(D_800EC1C0_minigame[D_800EBE28_minigame], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80111FC0_stardust_battle(D_800EC1C0_minigame[D_800EBE28_minigame], (u32)stage);
    D_800EBE28_minigame++;
    func_800E1490_minigame(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108C14_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108D84_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108EC4_stardust_battle);

void func_80109128_stardust_battle(s16 mode) {
    omObjData *object;
    UnkStardustBattleStage *stage;

    if (D_800EBE28_minigame == 0 || D_800EC280_minigame == 0) {
        return;
    }

    object = D_800EC1BC_minigame[D_800EBE28_minigame];
    stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    if (stage->unk_00 == mode) {
        return;
    }

    func_80107DCC_stardust_battle(D_800EC598_minigame[0], mode);
    if (stage->func_34 != NULL) {
        stage->func_34(object);
        stage->func_34 = NULL;
    }
    stage->unk_00 = mode;
    stage->func_30 = D_80113E78_stardust_battle[mode];
    stage->func_34 = D_80113E84_stardust_battle[mode];
    if (object->model[0] != -1) {
        Hu3DModelKill(object->model[0]);
    }
    if (object->model[1] != -1) {
        Hu3DModelKill(object->model[1]);
    }
    object->model[0] = func_8000B108_main(D_80113E60_stardust_battle[mode] | 0x620000, 0x699);
    object->model[1] =
        func_8000B108_main(D_80113E54_stardust_battle[mode] | 0x620000, D_80113E6C_stardust_battle[mode] | 0x299);
    if (stage->func_30 != NULL) {
        stage->func_30(object);
    }
}

/* Like func_80107FA4, the return value of func_80111FEC_stardust_battle is
   treated as a pointer. */
s16 func_8010929C_stardust_battle(void) {
    if (D_800EBE28_minigame == 0) {
        return 0;
    }

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    return ((UnkStardustBattleStage *)func_80111FEC_stardust_battle(D_800EC1BC_minigame[D_800EBE28_minigame]))
        ->unk_00;
}

void func_801092F0_stardust_battle(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    f32 dist = object->trans.x * object->trans.x + object->trans.z * object->trans.z;
    f32 radius = fabs(525.0 - data->unk48);

    if (radius * radius < dist) {
        dist = sqrtf(dist);
        if (dist != 0.0f) {
            dist = radius / dist;
        } else {
            object->trans.x = 0.0f;
            object->trans.z = radius;
            dist = 1.0f;
        }
        object->trans.x *= dist;
        object->trans.z *= dist;
    }
}

void func_801093CC_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    stage->func_30 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109424_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109B18_stardust_battle);

void func_80109F94_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (stage->unk_24 != NULL) {
        HuMemFree(stage->unk_24);
    }
    stage->unk_24 = NULL;
    func_8010A5A4_stardust_battle(object);
}

void func_80109FE4_stardust_battle(void) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle();
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        streak = stage->streaks = (UnkStardustBattleStreak *)HuMemAllocTag(0xF00, TAG_OVERLAY);
        memset(streak, 0, 0xF00);

        for (i = 0; i < 64; i++, streak++) {
            streak->index = i;
        }
    }
}

s32 func_8010A04C_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(D_800EC1C0_minigame[0]);
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        return -1;
    }

    streak = stage->streaks;
    for (i = 0; i < 64; i++, streak++) {
        if (streak->active == 0) {
            streak->active = 1;
            streak->x = x;
            streak->y = 0.0f;
            streak->z = z;
            streak->unk_14 = arg2;
            streak->unk_18 = arg3;
            streak->unk_1C = 150.0f;
            streak->unk_10 = arg5;
            streak->unk_20 = arg4;
            streak->unk_24 = streak->unk_14 * streak->unk_20;
            streak->unk_34 = streak->unk_1C * streak->unk_20;
            if (streak->unk_34 != 0.0f) {
                streak->unk_38 = 1.0f / streak->unk_34;
            } else {
                streak->unk_38 = 1.0f;
            }
            streak->unk_28 = (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20) *
                             (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20);
            streak->unk_2C = (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20) *
                             (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20);
            streak->unk_30 = sqrtf(x * x + z * z);
            return streak->index;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A204_stardust_battle);

void func_8010A418_stardust_battle(void) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle();
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        return;
    }

    streak = stage->streaks;
    for (i = 0; i < 64; i++, streak++) {
        if (streak->active == 0) {
            continue;
        }
        if (streak->unk_20 >= 0.5f) {
            streak->unk_10 += streak->unk_18;
        }
        streak->unk_28 = (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20) *
                         (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20);
        streak->unk_2C = (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20) *
                         (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20);
        if (streak->unk_20 < 1.0f) {
            streak->unk_20 += 0.0625f;
            if (streak->unk_20 >= 1.0f) {
                streak->unk_20 = 1.0f;
            }
        }
        streak->unk_24 = streak->unk_14 * streak->unk_20;
        streak->unk_34 = streak->unk_1C;
        if (streak->unk_34 != 0.0f) {
            streak->unk_38 = 1.0f / streak->unk_34;
        } else {
            streak->unk_38 = 1.0f;
        }
        if (streak->unk_10 - streak->unk_1C * streak->unk_20 - streak->unk_30 >= 600.0) {
            streak->unk_20 = 0.0f;
            streak->unk_14 = 0.0f;
            streak->active = 0;
        }
    }
}

void func_8010A5A4_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (stage->streaks != NULL) {
        HuMemFree(stage->streaks);
    }
    stage->streaks = NULL;
}

void func_8010A5E0_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    HmfData *hmf = Hu3DData[object->model[0]].hmf;

    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.1f);
    func_800E1310_minigame(object, 5.0f);
    func_8001C954_main(object->model[0]);
    stage->unk_2C = func_8002C834_main(hmf, "comet-nagare");
    stage->func_30 = func_8010A690_stardust_battle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A690_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A74C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010AAC4_stardust_battle);

void func_8010BFE4_stardust_battle(f32 arg0, s16 arg1) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle == NULL) {
        return;
    }

    actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);

    if (arg1 > 0) {
        actor->unk_24 = arg1;
        actor->velY = (arg0 - D_80114B18_stardust_battle->trans.y) / arg1;
    }
}

void func_8010C06C_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->velY = 0.0f;
        actor->unk_24 = 0;

        if (actor->unk_04 != 7) {
            actor->velX = actor->velZ = 0.0f;
            actor->unk_04 = 11;
        }
    }
}

void func_8010C0C8_stardust_battle(void) {
    UnkStardustBattleActor *actor;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->start.x = D_80114B18_stardust_battle->trans.x;
        actor->start.y = D_80114B18_stardust_battle->trans.y;
        actor->start.z = D_80114B18_stardust_battle->trans.z;
        actor->target.x = Center.x;
        actor->target.y = 450.0f;
        actor->target.z = Center.z + 200.0;
        dx = actor->target.x - actor->start.x;
        dy = actor->target.y - actor->start.y;
        dz = actor->target.z - actor->start.z;
        actor->unk_26 = sqrtf(dx * dx + dy * dy + dz * dz) / 15.0000005960464478;
        if (actor->unk_26 == 0) {
            actor->unk_26 = 1;
        }
        actor->unk_24 = 0;
        actor->active = 0;
        actor->unk_04 = 13;
    }
}

void func_8010C1F8_stardust_battle(s16 motion, s16 startTime, s16 endTime, u8 attr) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        model->motTime = startTime;
        model->unk48 = endTime;
        model->motAttr = attr;
    }
}

/* Unlike the other func_80111FEC_stardust_battle call sites, the return value
   is unused here; the stardust object is read straight from the global. */
void func_8010C2CC_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
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
    model = &Hu3DData[obj->model[0]];
    return model->motSpeed;
}

void func_8010C38C_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
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
    model = &Hu3DData[obj->model[0]];
    return model->motTime;
}

void func_8010C44C_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->active = 0;
        actor->unk_04 = 15;
        func_8010C1F8_stardust_battle(1, 0, 0, 2);
    }
}

void func_8010C498_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->unk_18 = 0;
        actor->active = 0;
        actor->unk_04 = 17;
        HuAudFXPlay(0x50B);
        actor->unk_4C = D_80114B18_stardust_battle->trans.x;
        actor->unk_50 = D_80114B18_stardust_battle->trans.y;
        actor->unk_54 = D_80114B18_stardust_battle->trans.z;
    }
}

s16 func_8010C508_stardust_battle(void) {
    if (D_80114B18_stardust_battle == NULL) {
        return 0;
    }
    return ((UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle))->unk_04;
}

void func_8010C538_stardust_battle(void) {
    UnkStardustBattleSpots *spots = HuMemAllocTag(sizeof(UnkStardustBattleSpots), TAG_OVERLAY);

    D_80114B20_stardust_battle = spots;
    spots->spot = HuMemAllocTag(32 * sizeof(UnkStardustBattleSpot), TAG_OVERLAY);
    memset(spots->spot, 0, 32 * sizeof(UnkStardustBattleSpot));
    spots->count = 0;
    spots->max = 32;
    spots->unk_04 = 0;
    func_8010C5A8_stardust_battle(32, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C5A8_stardust_battle);

Vec *func_8010CA48_stardust_battle(s16 index) {
    UnkStardustBattleSpots *spots = D_80114B20_stardust_battle;
    UnkStardustBattleSpot *spot;

    if (index >= 32) {
        index %= 32;
    }
    spot = &spots->spot[index];
    if (spots->count == 0) {
        return &D_80113EB8_stardust_battle;
    }
    if (spot->active == 0) {
        spot = &spots->spot[(s16)(index % spots->count)];
    }
    if (spot->followPlayer != 0) {
        spot->pos.x = D_800EC598_minigame[0]->trans.x;
        spot->pos.z = D_800EC598_minigame[0]->trans.z;
        spot->pos.y = 0.0f;
    }
    return &spot->pos;
}

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

void func_8010DF70_stardust_battle(s16 index) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (index < stars->count) {
        star = &stars->star[index];
        if (star->active != 0) {
            star->active = 0;
            star->x = star->targetX = star->unk_40 = 0.0f;
            func_8001C258_main(star->model[0], 4, 4);
            func_8001C258_main(star->model[1], 4, 4);
            func_8001C258_main(star->model[2], 4, 4);
            func_8001C258_main(star->model[3], 4, 4);
            func_8001C258_main(star->model[4], 4, 4);
            func_8001C258_main(star->model[5], 4, 4);
        }
    }
}

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

void func_8010E35C_stardust_battle(s16 index) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (index < stars->count) {
        star = &stars->star[index];
        if (star->active != 0) {
            if (star->state == 4) {
                star->state = 5;
                star->unk_14 = 0;
                guMtxIdentF(Hu3DData[star->model[star->unk_10]].mtx);
                PlayerFXPlay(0xAF, 0);
                star->unk_40 = sindf(star->targetY) * 31.9999992847442627;
                star->unk_48 = cosdf(star->targetY) * 31.9999992847442627;
                star->unk_44 = 10.0f;
            } else {
                func_8010DF70_stardust_battle(index);
            }
        }
    }
}

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

void func_8010ED7C_stardust_battle(void) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    s32 i;

    if (D_80114B2C_stardust_battle == NULL) {
        return;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active != 0) {
            Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, star->x, star->y, star->z), 2.0f, 2.0f,
                              2.0f);
            func_8010DF70_stardust_battle(i);
        }
    }
}

u16 func_8010EE38_stardust_battle(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    u16 anim = HuSprAnimRead(data);

    DataClose(data);
    return anim;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010EE7C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F0E8_stardust_battle);

/* Splits a frame count into minutes, seconds and hundredths, stored as the
   decimal digits of a time display. */
void func_8010F400_stardust_battle(s16 index, s32 frames) {
    u8 *digits = D_80114B38_stardust_battle[index];
    s32 parts[3];

    parts[0] = parts[1] = parts[2] = 0;
    digits[0] = digits[1] = digits[2] = digits[3] = digits[4] = digits[5] = 0;
    while (frames >= 1800) {
        frames -= 1800;
        parts[0]++;
    }
    while (frames >= 30) {
        parts[1]++;
        frames -= 30;
    }
    parts[2] = frames * (1.0f / 30.0f) * 99.0f;
    while (parts[0] >= 10) {
        parts[0] -= 10;
        digits[0]++;
    }
    digits[1] = parts[0];
    while (parts[1] >= 10) {
        parts[1] -= 10;
        digits[2]++;
    }
    digits[3] = parts[1];
    while (parts[2] >= 10) {
        parts[2] -= 10;
        digits[4]++;
    }
    digits[5] = parts[2];
}

void func_8010F580_stardust_battle(s16 index) {
    D_80114B44_stardust_battle[index].state = 1;
    D_80114B44_stardust_battle[index].timer = 0;
}

void func_8010F5B0_stardust_battle(s16 index) {
    D_80114B44_stardust_battle[index].state = 2;
    D_80114B44_stardust_battle[index].timer = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F5E0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F73C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010F890_stardust_battle);

void func_8010FA60_stardust_battle(void) {
    omObjData *object;
    HmfModel *model;
    s32 count = 8;
    s32 i;
    s32 j;

    object = D_80114B50_stardust_battle = omAddObj(0x1E, 8, 0, -1, func_8010FBCC_stardust_battle);
    object->work[0] = 0;
    object->work[1] = 2;
    object->work[2] = 4;
    object->work[3] = 255;
    for (i = 0, j = 0; i < count; i++) {
        if (i >= object->work[j + 1]) {
            j++;
        }
        object->model[i] = func_8000B0A0_main(D_80113EF0_stardust_battle[j], D_80113EFC_stardust_battle[i / 16] | 0x99);
        func_8001C258_main(object->model[i], 4, 4);
        model = &Hu3DData[object->model[i]];
        model->motTime = 0.0f;
        model->motSpeed = 0.0f;
        if (model->hmf->unk98 != NULL) {
            model->hmf->unk98->unk08 = 0.0f;
        }
    }
}

void func_8010FBCC_stardust_battle(omObjData *object) {
    HmfModel *model;
    s32 count = 8;
    s32 i;

    for (i = 0; i < count; i++) {
        model = &Hu3DData[object->model[i]];
        if (model->attr & 4) {
            continue;
        }
        if (D_800CCF58_main[model->motId].unk02 <= model->motTime) {
            func_8001C258_main(object->model[i], 4, 4);
            model->motTime = 0.0f;
            model->motSpeed = 0.0f;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0.0f;
            }
        }
    }
}

/* Activates the first free model of the given group in the D_80114B50 object
   and returns its index, or -1 if none are free. */
s32 func_8010FCBC_stardust_battle(Vec *pos, Vec *rot, f32 scale, s16 group) {
    omObjData *object = D_80114B50_stardust_battle;
    HmfModel *model;
    s32 count = 8;
    s32 i;

    for (i = object->work[group]; i < count; i++) {
        if (i >= object->work[group + 1]) {
            break;
        }
        model = &Hu3DData[object->model[i]];
        if (!(model->attr & 4)) {
            continue;
        }
        func_8001C258_main(object->model[i], 4, 0);
        if (pos != NULL) {
            model->pos.x = pos->x;
            model->pos.y = pos->y;
            model->pos.z = pos->z;
        } else {
            model->pos.x = model->pos.y = model->pos.z = 0.0f;
        }
        if (rot != NULL) {
            model->rot.x = rot->x;
            model->rot.y = rot->y;
            model->rot.z = rot->z;
        } else {
            model->rot.x = model->rot.y = model->rot.z = 0.0f;
        }
        model->scale.x = model->scale.y = model->scale.z = scale;
        if (i == 0) {
            object->trans.x = model->pos.x;
            object->trans.y = model->pos.y;
            object->trans.z = model->pos.z;
            object->rot.x = model->rot.x;
            object->rot.y = model->rot.y;
            object->rot.z = model->rot.z;
            object->scale.x = model->scale.x;
            object->scale.y = model->scale.y;
            object->scale.z = model->scale.z;
        }
        model->motSpeed = 1.0f;
        return i;
    }
    return -1;
}

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

void func_801119D4_stardust_battle(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    camera->pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    camera->pos.y = -sindf(rotX) * CZoom + Center.y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    camera->at.x = Center.x;
    camera->at.y = Center.y;
    camera->at.z = Center.z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

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

f32 func_80111DF8_stardust_battle(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111E10_stardust_battle);

void func_80111E70_stardust_battle(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 16; i++) {
        arg2[i] = arg0[i] + arg3 * (arg1[i] - arg0[i]);
    }
}

f32 func_80111EB8_stardust_battle(f32 x, f32 y) {
    f32 angle = atan2df(y, x);

    if (angle < 0.0) {
        angle += 360.0;
    } else if (angle >= 360.0) {
        angle -= 360.0;
    }
    return angle;
}

void func_80111F38_stardust_battle(Vec *dir, f32 *rot) {
    *rot++ = func_80111EB8_stardust_battle(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_80111EB8_stardust_battle(dir->z, dir->x);
    *rot = 0.0f;
}

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

void func_8011376C_stardust_battle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801138A0_stardust_battle);
