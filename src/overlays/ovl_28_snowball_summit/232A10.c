#include "common.h"

extern s32 D_8010F880_snowball_summit;
extern s32 D_8010F884_snowball_summit;
extern u16 D_8010F888_snowball_summit;
extern s32 D_8010F88C_snowball_summit;
extern s32 D_80110044_snowball_summit;
extern s32 D_801101E8_snowball_summit;
extern u16 D_801101F2_snowball_summit;
extern f32 D_801101F4_snowball_summit;
extern f32 D_801101F8_snowball_summit;
extern s32 D_80110248_snowball_summit;
extern s32 D_8011024C_snowball_summit;
extern s32 fontcolor;
extern s16 D_80110030_snowball_summit;

typedef struct UnkSnowballSummitSnowball {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the snowball is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ omObjData *unk_18; // minigame object that owns the slot
} UnkSnowballSummitSnowball;      // sizeof 0x1C

extern UnkSnowballSummitSnowball D_8010F8D8_snowball_summit[8];

typedef struct UnkSnowballSummitSlot {
    /* 0x00 */ s32 id; // -1 when the slot is unused
    /* 0x04 */ char unk_04[0x8];
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ s32 unk_10; // index into D_8010F9B8_snowball_summit of the object that owns the slot
    /* 0x14 */ char unk_14[0x2C];
} UnkSnowballSummitSlot; // sizeof 0x40

extern UnkSnowballSummitSlot D_8010FC30_snowball_summit[16];

typedef struct UnkSnowballSummitRoll {
    /* 0x00 */ s32 state; // -1 when the slot is unused, 0 when the roll is dead, 1 or 2 while in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ omObjData *unk_14; // minigame object that owns the slot
} UnkSnowballSummitRoll;          // sizeof 0x18

extern UnkSnowballSummitRoll D_80110048_snowball_summit[16];

typedef struct UnkSnowballSummitObjSlot {
    /* 0x00 */ s32 id;       // -1 when the slot is unused
    /* 0x04 */ void *unk_04; // minigame object that owns the slot
} UnkSnowballSummitObjSlot;  // sizeof 0x8

extern UnkSnowballSummitObjSlot D_801101C8_snowball_summit[4];

typedef struct UnkSnowballSummitThrow {
    /* 0x00 */ s32 state; // -1 when the slot is unused
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
} UnkSnowballSummitThrow; // sizeof 0x18

extern UnkSnowballSummitThrow D_80110200_snowball_summit[3];

typedef struct UnkSnowballSummitMover {
    /* 0x00 */ s32 id;     // -1 when the slot is unused
    /* 0x04 */ s32 unk_04; // 0 while unused, otherwise the selected model variant
    /* 0x08 */ s32 unk_08; // one of the owner's player flags
    /* 0x0C */ s32 unk_0C; // player id this mover belongs to
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 posX;
    /* 0x1C */ f32 posY;
    /* 0x20 */ f32 posZ;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 spawnPosX;
    /* 0x34 */ f32 spawnPosY;
    /* 0x38 */ f32 spawnPosZ;
    /* 0x3C */ s32 unk_3C; // 0, or 1..3 while the mover is animating
    /* 0x40 */ s32 unk_40; // 3d model handle
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ s32 unk_48; // 3d model handle
    /* 0x4C */ s32 unk_4C; // index of the owning object
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ s32 unk_60;
    /* 0x64 */ s32 unk_64;
    /* 0x68 */ s32 unk_68;
    /* 0x6C */ s32 unk_6C;
    /* 0x70 */ s32 unk_70;        // -1 when unset, else an index into D_8010FC30_snowball_summit
    /* 0x74 */ void *unk_74;      // HmfModelData
    /* 0x78 */ omObjData *unk_78; // minigame object that owns the slot
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ s32 unk_80;
    /* 0x84 */ s32 unk_84;
    /* 0x88 */ s32 unk_88;
    /* 0x8C */ s32 unk_8C;
    /* 0x90 */ s32 unk_90;
    /* 0x94 */ s16 unk_94;
    /* 0x96 */ s16 unk_96;
    /* 0x98 */ f32 unk_98;
} UnkSnowballSummitMover; // sizeof 0x9C

extern UnkSnowballSummitMover D_8010F9B8_snowball_summit[4];

typedef struct UnkSnowballSummitNode {
    /* 0x00 */ s32 id; // -1 when the slot is unused, 0 when the node is dead, 1 when it is in use
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A; // sound effect id
    /* 0x0C */ void *unk_0C;
} UnkSnowballSummitNode; // sizeof 0x10

extern UnkSnowballSummitNode D_80110250_snowball_summit[4];

void func_801061DC_snowball_summit(omObjData *);
void func_80107230_snowball_summit(omObjData *);
void func_80106760_snowball_summit(omObjData *);
void func_8010683C_snowball_summit(omObjData *);
void func_801068EC_snowball_summit(omObjData *);
void func_80106D58_snowball_summit(omObjData *);
void func_801075E0_snowball_summit(omObjData *);
void func_80107860_snowball_summit(omObjData *);
void func_8010775C_snowball_summit(omObjData *);
void func_8010C4F4_snowball_summit(omObjData *);
void func_8010BC7C_snowball_summit(omObjData *);
void func_8010C6A8_snowball_summit(omObjData *);
void func_8010C7F0_snowball_summit(omObjData *);
void func_8010C000_snowball_summit(omObjData *);
void func_8010C170_snowball_summit(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801059A0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801059BC_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80105AA0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80105B6C_snowball_summit);

void func_80105B9C_snowball_summit(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80105C14_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80105D64_snowball_summit);

void func_801060E0_snowball_summit(u16 arg0, u16 arg1, char *arg2, u16 arg3) {
    fontcolor = arg3;
    print8(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010610C_snowball_summit);

void func_80106184_snowball_summit(void) {
    func_8000BBD4_main(D_801101F2_snowball_summit, D_801101F4_snowball_summit, D_801101F8_snowball_summit);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801061DC_snowball_summit);

void func_801062AC_snowball_summit(void) {
    omAddObj(0x96, 1, 0, -1, func_801061DC_snowball_summit);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801062E0_snowball_summit);

void func_80106758_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80106760_snowball_summit);

void func_801067FC_snowball_summit(void) {
    omObjData *object = omAddObj(0xA0, 1, 0, -1, func_80106760_snowball_summit);
    object->work[0] = 0;
}

void func_80106834_snowball_summit(omObjData *object) {
}

void func_8010683C_snowball_summit(omObjData *this) {
    *this->model = func_8000B108_main(0x490003, 0x2B9);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 20.0f;
    func_8001C8A8_main(*this->model, 2);
    this->func = func_80106834_snowball_summit;
}

void func_801068B0_snowball_summit(void) {
    omAddObj(0xC8, 1, 0, -1, func_8010683C_snowball_summit);
}

void func_801068E4_snowball_summit(omObjData *object) {
}

void func_801068EC_snowball_summit(omObjData *this) {
    *this->model = func_8000B108_main(0x490006, 0x2B9);
    func_8001C814_main(*this->model, 2, 2);
    this->trans.x = this->trans.z = 0.0f;
    this->trans.y = 0.0f;
    func_8001C8A8_main(*this->model, 1);
    this->func = func_801068E4_snowball_summit;
}

void func_80106968_snowball_summit(void) {
    omAddObj(0xAA, 1, 1, -1, func_801068EC_snowball_summit);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010699C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80106D58_snowball_summit);

void func_80107000_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        omAddObj(0xB4, 2, 0, -1, func_80106D58_snowball_summit)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010705C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801070F4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107230_snowball_summit);

void func_80107330_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x1F4, 1, 0, -1, func_80107230_snowball_summit)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010738C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010742C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_801075E0_snowball_summit);

void func_80107700_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        omAddObj(0x258, 1, 1, -1, func_801075E0_snowball_summit)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010775C_snowball_summit);

void func_80107860_snowball_summit(omObjData *this) {
    s16 *model = &D_80110030_snowball_summit;

    *model = func_8000CBA0_main(0x49000D, 0x2A9);
    func_8000CD00_main(*model, 15.0f, 110.0f, 8.0f);
    func_8001C8A8_main(*model, 2);
    this->func = func_8010775C_snowball_summit;
}

void func_801078D4_snowball_summit(void) {
    omAddObj(0x3DE, 1, 0, -1, func_80107860_snowball_summit);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107908_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107944_snowball_summit);

s32 func_80107988_snowball_summit(f32 arg0, f32 arg1, f32 arg2) {
    f32 angle = arg1 - arg0;

    if (angle < 0.0f) {
        angle += 360.0f;
    }

    if (angle < arg2) {
        return 0;
    }

    if (360.0f - arg2 < angle) {
        return 0;
    }

    if (180.0f <= angle) {
        return -1;
    }

    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107A18_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107B58_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107CA4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107D30_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107DD4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_80107F80_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010811C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A0B0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A384_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A71C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010A940_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AA78_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AC94_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010AE74_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B01C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B158_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B250_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B34C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B8E4_snowball_summit);

s32 func_8010B994_snowball_summit(UnkSnowballSummitMover *arg0) {
    s32 i;
    UnkSnowballSummitSlot *slot;

    for (i = 0; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot = &D_8010FC30_snowball_summit[i];
        if (slot->id == 0) {
            slot->id = 1;
            slot->unk_10 = arg0->unk_4C;
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010B9E4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BC7C_snowball_summit);

void func_8010BE8C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 16; i++) {
        omAddObj(0x190, 2, 0, -1, func_8010BC7C_snowball_summit)->work[0] = i;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010BEE8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C000_snowball_summit);

void func_8010C10C_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x1FE, 1, 1, -1, func_8010C000_snowball_summit)->work[0] = i;
    }
}

void func_8010C168_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C170_snowball_summit);

void func_8010C288_snowball_summit(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omAddObj(0x208, 1, 1, -1, func_8010C170_snowball_summit)->work[0] = i;
    }
}

void func_8010C2E4_snowball_summit(omObjData *arg0) {
}

void func_8010C2EC_snowball_summit(omObjData *arg0) {
    if (D_8010F88C_snowball_summit > 0) {
        D_8010F88C_snowball_summit--;
    } else {
        D_8010F884_snowball_summit = 1;
        arg0->func = func_8010C2E4_snowball_summit;
    }
}

void func_8010C328_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() & 2) {
        D_8010F88C_snowball_summit = 0x14;
        arg0->func = func_8010C2EC_snowball_summit;
    }
}

s32 func_8010C36C_snowball_summit(void) {
    s32 i = 0;
    s32 count = 0;
    s32 index = -1;
    UnkSnowballSummitMover *mover = D_8010F9B8_snowball_summit;

    for (; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        if ((u32)mover[i].id < 0x5A) {
            count++;
            index = i;
        }
    }

    if (count == 1) {
        D_80110044_snowball_summit = 1;
        return index;
    }
    return -1;
}

void func_8010C3E4_snowball_summit(s32 arg0) {
    UnkSnowballSummitMover *mover = &D_8010F9B8_snowball_summit[arg0];

    GwPlayer[mover->unk_78->work[0]].bonusCoin = 10;
    GMesCreate(0x16, GwPlayer[mover->unk_78->work[0]].chr);
    HuAudSeqPlay(0x65);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C46C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C4F4_snowball_summit);

void func_8010C5C0_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() == 0) {
        D_8010F88C_snowball_summit = 0xF;
        arg0->func = func_8010C4F4_snowball_summit;
    }
}

void func_8010C600_snowball_summit(omObjData *arg0) {
    GMesCreate(0xE);
    HuAudSeqFadeOut(0x78);
    D_8010F88C_snowball_summit = 0x4B;
    arg0->func = func_8010C5C0_snowball_summit;
}

s32 func_8010C648_snowball_summit(void) {
    s32 i = 0;
    u32 count = 0;
    UnkSnowballSummitMover *mover = D_8010F9B8_snowball_summit;

    for (; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        // unused movers have an id of -1, so compare as unsigned
        if ((u32)mover[i].id < 0x5A) {
            count++;
        }
    }

    if (count == 1) {
        return 1;
    } else if (count == 0) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C6A8_snowball_summit);

void func_8010C7A4_snowball_summit(omObjData *arg0) {
    GMesCreate(0x1A, 0x3C, 0xA0, 0x1C);
    D_8010F88C_snowball_summit = 0x709;
    arg0->func = func_8010C6A8_snowball_summit;
}

void func_8010C7F0_snowball_summit(omObjData *arg0) {
    if (GMesStatGet() == 0 || GMesStatGet() & 2) {
        arg0->func = func_8010C7A4_snowball_summit;
        D_8010F884_snowball_summit = 1;
        HuAudSeqPlay(0x30);
    }
}

void func_8010C850_snowball_summit(omObjData *arg0) {
    GMesCreate(3);
    arg0->func = func_8010C7F0_snowball_summit;
    D_8010F884_snowball_summit = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C890_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C9B4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010C9E0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA18_snowball_summit);

void func_8010CA70_snowball_summit(void) {
    D_8010F880_snowball_summit += D_8010F884_snowball_summit;
    D_8010F884_snowball_summit = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CA98_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CC00_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010CD58_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D108_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D304_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D55C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010D86C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DB10_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DD00_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010DFD0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E2F4_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E52C_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010E824_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EA68_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EBC0_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010EEEC_snowball_summit);

void func_8010EFA0_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitMover *mover;

    for (i = 0, mover = D_8010F9B8_snowball_summit; i < ARRAY_COUNT(D_8010F9B8_snowball_summit); i++) {
        mover[i].id = -1;
    }
}

void func_8010EFE4_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitThrow *throwSlot;

    for (i = 0, throwSlot = D_80110200_snowball_summit; i < ARRAY_COUNT(D_80110200_snowball_summit); i++) {
        throwSlot[i].state = -1;
    }
}

void func_8010F020_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitRoll *roll;

    for (i = 0, roll = D_80110048_snowball_summit; i < ARRAY_COUNT(D_80110048_snowball_summit); i++) {
        roll[i].state = -1;
    }
}

void func_8010F05C_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitSlot *slot;

    for (i = 0, slot = D_8010FC30_snowball_summit; i < ARRAY_COUNT(D_8010FC30_snowball_summit); i++) {
        slot[i].id = -1;
    }
}

void func_8010F090_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitSnowball *snowball;

    for (i = 0, snowball = D_8010F8D8_snowball_summit; i < ARRAY_COUNT(D_8010F8D8_snowball_summit); i++) {
        snowball[i].state = -1;
    }
}

void func_8010F0CC_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitObjSlot *slot;

    for (i = 0, slot = D_801101C8_snowball_summit; i < ARRAY_COUNT(D_801101C8_snowball_summit); i++) {
        slot[i].id = -1;
    }
}

void func_8010F100_snowball_summit(void) {
    s32 i;
    UnkSnowballSummitNode *node;

    for (i = 0, node = D_80110250_snowball_summit; i < ARRAY_COUNT(D_80110250_snowball_summit); i++) {
        node[i].id = -1;
    }
}

void func_8010F134_snowball_summit(void) {
    D_8010F880_snowball_summit = 0;
    D_8010F884_snowball_summit = 0;
    D_8010F888_snowball_summit = 0;
    D_80110044_snowball_summit = 0;
    D_80110248_snowball_summit = -1;
    D_801101E8_snowball_summit = 0;
    D_8011024C_snowball_summit = 0;
    func_8010EFA0_snowball_summit();
    func_8010EFE4_snowball_summit();
    func_8010F05C_snowball_summit();
    func_8010F020_snowball_summit();
    func_8010F0CC_snowball_summit();
    func_8010F100_snowball_summit();
    func_8010F090_snowball_summit();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F1B8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F234_snowball_summit);

void func_8010F2B0_snowball_summit(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F2B8_snowball_summit);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", func_8010F42C_snowball_summit);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_28_snowball_summit/232A10", D_8010F870_snowball_summit);
