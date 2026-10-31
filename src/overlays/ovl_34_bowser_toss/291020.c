#include "common.h"
#include "mallocblock.h"
#include "overlays/minigame.h"

typedef struct UnkBowser { // 0x64 bytes, two entries
    omObjData *unk_00;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    char unk_26[2];
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C;
    f32 unk_40;
    s32 unk_44;
    f32 unk_48;
    f32 unk_4C;
    s32 unk_50;
    char unk_54[8];
    s32 unk_5C;
    s32 unk_60;
} UnkBowser;

// Per-player slot of the array allocated in func_80106568_bowser_toss
typedef struct BowserTossPlayer { // 0x5C bytes, two entries
    s16 index;                    // player index
    char unk_02[6];
    f32 unk_08;
    s16 unk_0C; // state, 5 when finished
    char unk_0E[10];
    s16 unk_18;
    char unk_1A[66];
} BowserTossPlayer;

// Per-player slot of the array allocated in func_8010B41C_bowser_toss
typedef struct BowserTossBowser { // 0x10 bytes, two entries
    s16 spriteId;                 // HuSprGrpCreate handle
    s16 angle;
    s16 state; // toss state, 0x20 once the toss has finished
    char unk_06[2];
    s32 unk_08;
    s32 unk_0C;
} BowserTossBowser;

// Item data block returned by func_8010D9E0_bowser_toss
typedef struct BowserTossItem { // 0xC bytes
    s16 unk_00;
    s16 unk_02;
    void *unk_04;
    void *unk_08;
} BowserTossItem;

typedef union BowserTossWorkBytes { // packs the low byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BowserTossWorkBytes;

extern BowserTossPlayer *D_8010FB74_bowser_toss;
extern UnkBowser *D_8010FB8C_bowser_toss;
extern BowserTossBowser *D_8010FBA0_bowser_toss;

void func_8010A500_bowser_toss(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801059A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80105C80_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F530_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F53C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80105CEC_bowser_toss);

void func_8010649C_bowser_toss(void) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801064C0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106568_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801067B0_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F5A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106BC4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80107E84_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801080D0_bowser_toss);

s32 func_8010840C_bowser_toss(void) {
    s32 i;
    BowserTossPlayer *p;

    for (i = 0, p = D_8010FB74_bowser_toss; i < 2; i++, p++) {
        if (p->unk_0C != 5) {
            return 0;
        }
    }
    return 1;
}

s32 func_80108444_bowser_toss(void) {
    s32 i;
    BowserTossPlayer *p;

    for (i = 0, p = D_8010FB74_bowser_toss; i < 2; i++, p++) {
        if (p->unk_0C != 10) {
            return 0;
        }
    }
    return 1;
}

// Swaps the shared HmfData pointer of two of the object's models.
void func_8010847C_bowser_toss(omObjData *object, s16 arg1, s16 arg2) {
    HmfModel *model1 = &HmfModelData[object->model[arg1]];
    HmfModel *model2 = &HmfModelData[object->model[arg2]];
    HmfData *hmf = model1->hmf;

    model1->hmf = model2->hmf;
    model2->hmf = hmf;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801084DC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010858C_bowser_toss);

UnkBowser *func_80108800_bowser_toss(s16 arg0) {
    return &D_8010FB8C_bowser_toss[arg0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010882C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109DB8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109E4C_bowser_toss);

s32 func_80109F20_bowser_toss(void) {
    s32 i;
    UnkBowser *pBowser;

    for (i = 0, pBowser = D_8010FB8C_bowser_toss; i < 2; i++, pBowser++) {
        if (pBowser->unk_0A == 0 || pBowser->unk_0A == 9) {
            continue;
        }
        return 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80109F68_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A028_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A17C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A2D4_bowser_toss);

// Appends a new object to the shared minigame object list.
void func_8010A4A8_bowser_toss(void) {
    omObjData *obj = omAddObj(0x20, 0x1C, 0, -1, func_8010A500_bowser_toss);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A500_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A908_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AD54_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AD98_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010AF38_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B41C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B7AC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C1A0_bowser_toss);

s32 func_8010C23C_bowser_toss(void) {
    s32 i;
    BowserTossBowser *p;

    for (i = 0, p = D_8010FBA0_bowser_toss; i < 2; i++, p++) {
        if (p->state < 0x1F) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C274_bowser_toss);

s32 func_8010C2A4_bowser_toss(void) {
    s32 i;
    BowserTossBowser *p;

    for (i = 0, p = D_8010FBA0_bowser_toss; i < 2; i++, p++) {
        if (p->state < 0x40) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C2DC_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F998_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C570_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010CDB8_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D080_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D250_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D43C_bowser_toss);

f32 func_8010D5DC_bowser_toss(f32 arg0, f32 arg1) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D6E0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D8A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D8B8_bowser_toss);

void func_8010D918_bowser_toss(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 16; i++) {
        arg2[i] = arg0[i] + arg3 * (arg1[i] - arg0[i]);
    }
}

void func_8010D960_bowser_toss(omObjData *obj, u32 arg1) {
    obj->work[0] = arg1 >> 24;
    obj->work[1] = (arg1 >> 16) & 0xFF;
    obj->work[2] = (arg1 >> 8) & 0xFF;
    obj->work[3] = arg1 & 0xFF;
}

u32 func_8010D98C_bowser_toss(omObjData *object, s32 arg1, u32 arg2) {
    BowserTossWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010D9E0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DB9C_bowser_toss);

void func_8010DDC4_bowser_toss(BowserTossItem *item) {
    HuMemFree(item->unk_08);
    HuMemFree(item->unk_04);
    HuMemFree(item);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DDFC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010EA0C_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010EC10_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010ED44_bowser_toss);
