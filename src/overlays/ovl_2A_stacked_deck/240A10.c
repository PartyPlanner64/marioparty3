#include "common.h"
#include "gcc/memory.h"
#include "math.h"
#include "overlays/minigame.h"

// The 4 player entries start at entry 2 of D_8010F730_stacked_deck, and the 12
// cards laid out on the table start at entry 6.
#define STACKED_DECK_PLAYERS (&D_8010F730_stacked_deck[2])
#define STACKED_DECK_CARDS (&D_8010F730_stacked_deck[6])

// One entry of the 50 card stack. Layout derived from the table clear in
// func_80105A74_stacked_deck, which walks 50 entries of 0x84 bytes.
typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ s16 unk_04[10];
    /* 0x18 */ f32 unk_18[10];
    /* 0x40 */ s16 unk_40[2];
    /* 0x44 */ Vec unk_44;
    /* 0x50 */ Vec unk_50;
    /* 0x5C */ Vec unk_5C;
    /* 0x68 */ f32 unk_68[4];
    /* 0x78 */ Vec unk_78;
} StackedDeckCard; // sizeof 0x84

extern StackedDeckCard D_8010F730_stacked_deck[50];
extern u8 D_8010F6F4_stacked_deck;
extern void *D_8010F708_stacked_deck[];
extern Vec2f D_8010F2B0_stacked_deck[12];
extern s16 D_8010F6F0_stacked_deck;
extern s16 D_80111120_stacked_deck;
extern s16 D_80111150_stacked_deck[];
extern u8 D_80111168_stacked_deck;
extern u8 D_80111169_stacked_deck;
extern s16 D_80111170_stacked_deck;
extern char D_8010F42C_stacked_deck[]; // "card_k_DEF"

void func_801063F4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed);
void func_80106554_stacked_deck(omObjData *object);
void func_8010655C_stacked_deck(omObjData *object);
void func_80106694_stacked_deck(omObjData *object);
void func_8010669C_stacked_deck(omObjData *object);
void func_80108E48_stacked_deck(omObjData *object);
void func_801097D4_stacked_deck(omObjData *object);
void func_8010C188_stacked_deck(omObjData *object);
void func_8010C5C8_stacked_deck(omObjData *object);
void func_8010D98C_stacked_deck(omObjData *object);
void func_8010DAE4_stacked_deck(omObjData *object);
void func_8010DC2C_stacked_deck(omObjData *object);
void func_8010DDAC_stacked_deck(omObjData *object);
void func_8010E650_stacked_deck(omObjData *object);
void func_8010F134_stacked_deck(void);

void func_801059A0_stacked_deck(void) {
    func_8010F134_stacked_deck();
}

f32 func_801059BC_stacked_deck(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

u8 func_80105A3C_stacked_deck(s32 arg0) {
    u32 ret = (rand8() & 0xFF) * arg0;
    return ret >> 8;
}

void func_80105A74_stacked_deck(void) {
    StackedDeckCard *card;
    u32 i;

    for (i = 0, card = D_8010F730_stacked_deck; i < 50; i++, card++) {
        card->obj = NULL;
        card->unk_04[0] = 0;
        card->unk_04[1] = 0;
        card->unk_04[2] = 0;
        card->unk_04[3] = 0;
        card->unk_04[4] = 0;
        card->unk_04[5] = 0;
        card->unk_04[6] = 0;
        card->unk_04[7] = 0;
        card->unk_04[8] = 0;
        card->unk_04[9] = 0;
        card->unk_18[0] = 0;
        card->unk_18[1] = 0;
        card->unk_18[2] = 0;
        card->unk_18[3] = 0;
        card->unk_18[4] = 0;
        card->unk_18[5] = 0;
        card->unk_18[6] = 0;
        card->unk_18[7] = 0;
        card->unk_18[8] = 0;
        card->unk_18[9] = 0;
        card->unk_40[0] = -1;
        card->unk_40[1] = -1;
        card->unk_44.x = card->unk_44.y = card->unk_44.z = 0.0f;
        card->unk_50.x = card->unk_50.y = card->unk_50.z = 0.0f;
        card->unk_5C.x = card->unk_5C.y = card->unk_5C.z = 0.0f;
        card->unk_68[0] = 0.0f;
        card->unk_68[1] = 0.0f;
        card->unk_68[2] = 0.0f;
        card->unk_68[3] = 0.0f;
        card->unk_78.x = card->unk_78.y = card->unk_78.z = 0.0f;
    }
}

void func_80105B3C_stacked_deck(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105BB4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80105CBC_stacked_deck);

void func_80106290_stacked_deck(u8 value) {
    D_8010F6F4_stacked_deck = value;
}

void func_8010629C_stacked_deck(omObjData *object, s16 motion, s16 start, s16 end, s16 shift, s16 *current) {
    if (*current != motion) {
        Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[motion]].motId, start, end, shift);
        *current = motion;
    }
}

f32 func_80106338_stacked_deck(f32 base, f32 *value, f32 step) {
    f32 prev = *value;

    *value = prev - step;
    return base + prev;
}

void func_80106354_stacked_deck(omObjData *object, u8 anim) {
    Hu3DAnimKill(D_80111150_stacked_deck[object->work[0]]);
    D_80111150_stacked_deck[object->work[0]] =
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, D_8010F708_stacked_deck[anim], 0, D_8010F42C_stacked_deck);
}

#ifdef NON_MATCHING
// Only differs in f8/f10 register allocation of speed and the absolute z delta.
void func_801063F4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed) {
    f32 dx = x1 - x0;
    f32 dz = z1 - z0;
    f32 absDx = fabsf(dx);
    f32 absDz = fabsf(dz);
    f32 delta;
    f32 dist;
    f32 step;

    if (absDz <= absDx) {
        if (dx >= 0.0f) {
            *velX = -speed;
        } else {
            *velX = speed;
        }
        delta = dz;
        step = speed;
        dist = absDx;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velZ = -(delta / step);
    } else {
        if (dz >= 0.0f) {
            *velZ = -speed;
        } else {
            *velZ = speed;
        }
        delta = dx;
        step = speed;
        dist = absDz;
        if (step == 0.0f) {
            step = 1.0f;
        }
        step = dist / step;
        if (step == 0.0f) {
            step = 1.0f;
        }
        *velX = -(delta / step);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801063F4_stacked_deck);
#endif

void func_80106554_stacked_deck(omObjData *object) {
}

void func_8010655C_stacked_deck(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    D_800EC1C0_minigame[D_800EBE28_minigame++] = object;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.5f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E139C_minigame(D_800EC1C0_minigame[0], 1.0f, -5060.0f, -5000.0f, 5060.0f, 5000.0f);
    object->func = func_80106554_stacked_deck;
}

void func_80106654_stacked_deck(void) {
    omObjData *obj = omAddObj(0x3E6, 1, 1, -1, func_8010655C_stacked_deck);
    obj->work[0] = 0;
    D_8010F730_stacked_deck[0].obj = obj;
}

void func_80106694_stacked_deck(omObjData *object) {
}

void func_8010669C_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[1];

    card->unk_40[0] = func_8000B838_main(0x4B0000);
    card->unk_40[1] = espEntry(card->unk_40[0], 0, 0);
    espAttrSet(card->unk_40[1], 0x4000);
    card->unk_44.x = 160.0f;
    card->unk_44.y = 120.0f;
    espPosSet(card->unk_40[1], 160, 120);
    object->func = func_80106694_stacked_deck;
}

void func_80106738_stacked_deck(void) {
    omObjData *obj = omAddObj(0x3E7, 1, 1, -1, func_8010669C_stacked_deck);
    obj->work[0] = 0;
    D_8010F730_stacked_deck[1].obj = obj;
}

void func_80106778_stacked_deck(void) {
}

void func_80106780_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[object->work[0] + 2];
    omObjData *target;
    f32 velX;
    f32 velZ;

    if (card->unk_04[9] == 0) {
        card->unk_04[8] = (u8)(rand8() % 12);
        while (TRUE) {
            if (STACKED_DECK_CARDS[card->unk_04[8]].unk_04[1] == 1) {
                card->unk_04[9] = 1;
                return;
            }
            if (++card->unk_04[8] >= 12) {
                card->unk_04[8] = 0;
            }
        }
    }

    target = STACKED_DECK_CARDS[card->unk_04[8]].obj;
    func_801063F4_stacked_deck(target->trans.x, target->trans.z, object->trans.x, object->trans.z, &velX, &velZ, 60.0f);
    D_800CBB6E_main[object->work[3]] = velX;
    D_800D20A1_main[object->work[3]] = -velZ;
    if (target->trans.x - 45.0f <= object->trans.x && object->trans.x <= target->trans.x + 45.0f &&
        target->trans.z - 67.5f <= object->trans.z && object->trans.z <= target->trans.z + 67.5f) {
        D_800D5558_main[object->work[3]] |= 0x8000;
        D_800D5558_main[object->work[3]] |= 0x2000;
    }
}

#ifdef NON_MATCHING
// The card state check reads offset 0x04 of the table card as a word (lw) rather
// than a halfword, despite the halfword stores to the same field.
void func_801069A0_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[object->work[0] + 2];
    func_800E1BA8_minigame_ObjData *data = object->data;
    omObjData *cardObj;
    s16 i;

    if (card->unk_04[0] == 0 && data->unk5C == 0x200 && data->unk50 == 0x80) {
        card->unk_04[0] = 1;
        for (i = 0; i < 12; i++) {
            cardObj = STACKED_DECK_CARDS[i].obj;
            if (cardObj->trans.x - 90.0f < object->trans.x && object->trans.x < cardObj->trans.x + 90.0f &&
                cardObj->trans.z - 135.0f < object->trans.z && object->trans.z < cardObj->trans.z + 135.0f &&
                STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                card->unk_04[8] = 0;
                card->unk_04[9] = 0;
                STACKED_DECK_CARDS[i].unk_04[0] = 1;
                D_8010F6F0_stacked_deck = cardObj->work[1];
                D_80111169_stacked_deck = 6;
            }
        }
    }
    if (data->unk5C != 0x200 && data->unk50 != 0x80 && object->trans.y <= 1.0f) {
        card->unk_04[0] = 0;
        D_80111168_stacked_deck = 0;
    }
    if (object->trans.y > 1.0f) {
        D_80111168_stacked_deck = 1;
    }
    if (object->trans.z > 800.0f) {
        object->trans.z = 800.0f;
    }
    if (object->trans.x < -500.0f) {
        object->trans.x = -500.0f;
    }
    if (object->trans.x > 500.0f) {
        object->trans.x = 500.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801069A0_stacked_deck);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F42C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106BC8_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80108E48_stacked_deck);

void func_8010969C_stacked_deck(void) {
    StackedDeckCard *card;
    omObjData *obj;
    u16 player;
    s16 i;

    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                player = 0;
                break;
            case 1:
                player = 1;
                break;
            case 2:
                player = 2;
                break;
            case 3:
                player = 3;
                break;
            default:
                player = 0;
                break;
        }
        card = &D_8010F730_stacked_deck[i + 2];
        obj = omAddObj(0x1F4, 9, 0x3C, -1, func_80108E48_stacked_deck);
        obj->work[0] = player;
        obj->work[3] = GwPlayer[player].pad;
        card->obj = obj;
        D_800EC598_minigame[D_800EC280_minigame] = obj;
        D_800EC280_minigame++;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_801097D4_stacked_deck);

void func_8010C188_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &STACKED_DECK_CARDS[object->work[0]];

    object->model[0] = func_8000B108_main(0x4B0008, 0x2A9);
    object->model[1] = func_8000B108_main(0x4B0009, 0x2A9);
    object->model[2] = func_8000B108_main(0x4B000B, 0x2A9);
    if (object->work[0] == 0) {
        D_8010F708_stacked_deck[0] = DataRead(0x4B0002);
        D_8010F708_stacked_deck[1] = DataRead(0x4B0003);
        D_8010F708_stacked_deck[2] = DataRead(0x4B0004);
        D_8010F708_stacked_deck[3] = DataRead(0x4B0005);
        D_8010F708_stacked_deck[4] = DataRead(0x4B0006);
        D_8010F708_stacked_deck[5] = DataRead(0x4B0007);
    }
    D_80111150_stacked_deck[object->work[0]] =
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, D_8010F708_stacked_deck[0], 0, D_8010F42C_stacked_deck);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C514_main(object->model[0]);
    card->unk_04[5] = 150;
    func_8001FA68_main(object->model[1]);
    func_8001F9E4_main(object->model[1], card->unk_04[5]);
    card->unk_04[6] = 0;
    func_8001FA68_main(object->model[2]);
    func_8001F9E4_main(object->model[2], card->unk_04[6]);
    card->unk_18[0] = 15.0f;
    card->unk_18[1] = 0.0f;
    object->rot.x = 0.0f;
    object->rot.y = 180.0f;
    object->rot.z = func_801059BC_stacked_deck(card->unk_18[1], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
    card->unk_18[2] = 1.0f;
    card->unk_18[3] = 1.0f;
    card->unk_18[4] = 1.0f;
    object->scale.x = card->unk_18[2];
    object->scale.y = card->unk_18[2];
    object->scale.z = card->unk_18[2];
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], card->unk_18[3], object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[2], object->scale.x, object->scale.y, object->scale.z);
    object->trans.x = D_8010F2B0_stacked_deck[object->work[0]].x;
    object->trans.y = 0.0f;
    object->trans.z = D_8010F2B0_stacked_deck[object->work[0]].y;
    card->unk_18[5] = 0.0f;
    card->unk_18[6] = 0.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x + card->unk_18[5], -4.0f, object->trans.z + card->unk_18[6]);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    func_8001C258_main(object->model[0], 4, 4);
    func_8001C258_main(object->model[1], 4, 4);
    func_8001C258_main(object->model[2], 4, 4);
    object->func = func_801097D4_stacked_deck;
}

void func_8010C524_stacked_deck(void) {
    s16 i;

    for (i = 0; i < 12; i++) {
        StackedDeckCard *card = &STACKED_DECK_CARDS[i];
        omObjData *obj = omAddObj(0x226, 3, 3, -1, func_8010C188_stacked_deck);

        obj->work[0] = i;
        card->obj = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010C5C8_stacked_deck);

void func_8010D58C_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[object->work[0] + 18];

    switch (object->work[0]) {
        case 0:
            object->model[0] = func_8000B108_main(0xA0000, 0x2B9);
            func_8000B460_main(object, 0, 0xA0001);
            func_8000B460_main(object, 1, 0xA0006);
            func_8001C5B4_main(object->model[0], object->motion[0]);
            func_8001C814_main(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 0.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.0f;
            object->scale.y = 1.0f;
            object->scale.z = 1.0f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            break;
        case 1:
            object->model[0] = func_8000B108_main(0xA00C4, 0x2A9);
            func_8000B460_main(object, 0, 0xA00C7);
            func_8001C5B4_main(object->model[0], object->motion[0]);
            func_8001C814_main(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 50.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.7f;
            object->scale.y = 1.7f;
            object->scale.z = 1.7f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            card->unk_04[4] = 0;
            func_8001FA68_main(object->model[0]);
            func_8001F9E4_main(object->model[0], card->unk_04[4]);
            break;
        case 2:
            object->model[0] = func_8000B108_main(0xA00EE, 0x2B9);
            func_8000B460_main(object, 0, 0xA00EF);
            func_8000B460_main(object, 1, 0xA0103);
            func_8001C5B4_main(object->model[0], object->motion[0]);
            func_8001C814_main(object->model[0], 2, 2);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            object->trans.x = 0.0f;
            object->trans.y = 0.0f;
            object->trans.z = 0.0f;
            object->scale.x = 1.0f;
            object->scale.y = 1.0f;
            object->scale.z = 1.0f;
            object->rot.x = 0.0f;
            object->rot.y = 0.0f;
            object->rot.z = 0.0f;
            break;
    }
    object->model[1] = func_8000B0A0_main(0, 0xC9);
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    if (object->work[0] == 1) {
        func_8001FA68_main(object->model[1]);
        func_8001F9E4_main(object->model[1], card->unk_04[4]);
    } else {
        Hu3DModelRemakeStatic(object->model[1]);
        func_8001C514_main(object->model[1]);
    }
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelPosSet(object->model[1], object->trans.x, 1.5f, object->trans.z);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    card->unk_18[4] = 1.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], card->unk_18[4], object->scale.y, card->unk_18[4]);
    func_8001C258_main(object->model[0], 4, 4);
    func_8001C258_main(object->model[1], 4, 4);
    object->func = func_8010C5C8_stacked_deck;
}

void func_8010D8E8_stacked_deck(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        StackedDeckCard *card = &D_8010F730_stacked_deck[i + 18];
        omObjData *obj = omAddObj(0x23A, 5, 5, -1, func_8010D58C_stacked_deck);

        obj->work[0] = i;
        card->obj = obj;
    }
}

void func_8010D98C_stacked_deck(omObjData *object) {
    StackedDeckCard *effect = &D_8010F730_stacked_deck[21];
    omObjData *cardObj;
    s16 i;

    switch (D_80111170_stacked_deck) {
        case 0:
            break;
        case 1:
            for (i = 0; i < 12; i++) {
                cardObj = STACKED_DECK_CARDS[i].obj;
                if (STACKED_DECK_CARDS[i].unk_04[0] == 1) {
                    break;
                }
            }
            object->trans.x = cardObj->trans.x;
            object->trans.y = -50.0f;
            object->trans.z = cardObj->trans.z + 150.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            D_80111170_stacked_deck = 2;
            break;
        case 2:
            effect->unk_18[0] += 0.7f;
            func_80014714_main(effect->unk_04[0], (s32)effect->unk_18[0]);
            if (func_8001476C_main(effect->unk_04[0]) >= 14) {
                D_80111170_stacked_deck = 0;
                effect->unk_18[0] = 0.0f;
            }
            break;
    }
}

void func_8010DAE4_stacked_deck(omObjData *object) {
    StackedDeckCard *effect = &D_8010F730_stacked_deck[21];
    void *data;
    u16 sprite;

    data = DataRead(0xB);
    sprite = Hu3DSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    object->model[0] = D_800CBB60_main[sprite].modelId;
    effect->unk_04[0] = sprite;
    func_800146DC_main(sprite, 1, 1);
    func_800147FC_main(effect->unk_04[0], 200, 200, 200);
    func_80014794_main(effect->unk_04[0], 255);
    func_80014714_main(effect->unk_04[0], 14);
    object->scale.x = object->scale.y = object->scale.z = 10.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    object->func = func_8010D98C_stacked_deck;
}

void func_8010DBF4_stacked_deck(void) {
    omObjData *obj = omAddObj(0x244, 1, 0, -1, func_8010DAE4_stacked_deck);
    obj->work[0] = 0;
}

void func_8010DC2C_stacked_deck(omObjData *object) {
    StackedDeckCard *effect = &D_8010F730_stacked_deck[22];
    omObjData *player;
    s16 i;

    for (i = 0; i < 4; i++) {
        player = STACKED_DECK_PLAYERS[i].obj;
        if (player->work[1] == 0) {
            break;
        }
    }

    switch (D_80111120_stacked_deck) {
        case 0:
            break;
        case 1:
            object->trans.x = player->trans.x;
            object->trans.y = 60.0f;
            object->trans.z = player->trans.z + 60.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            D_80111120_stacked_deck = 2;
            if (!(GwPlayer[player->work[0]].stat & 1)) {
                omVibrate(player->work[0], 20, 0, 20);
            }
            break;
        case 2:
            if (effect->unk_04[1] < 5) {
                func_8001C258_main(object->model[0], 4, 0);
                effect->unk_04[1]++;
            } else {
                D_80111120_stacked_deck = 0;
                effect->unk_04[1] = 0;
                func_8001C258_main(object->model[0], 4, 4);
            }
            break;
    }
}

void func_8010DDAC_stacked_deck(omObjData *object) {
    StackedDeckCard *effect = &D_8010F730_stacked_deck[22];
    void *data;
    u16 sprite;

    data = DataRead(0x4B0001);
    sprite = Hu3DSprModelCreate(data, 0x2A0, 8);
    DataClose(data);
    object->model[0] = D_800CBB60_main[sprite].modelId;
    effect->unk_04[0] = sprite;
    func_800146DC_main(sprite, 2, 0);
    func_80014714_main(effect->unk_04[0], 0);
    Hu3DMotionSpeedSet(object->model[0], 3.0f);
    object->scale.x = object->scale.y = object->scale.z = 5.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    func_8001C258_main(object->model[0], 4, 4);
    object->func = func_8010DC2C_stacked_deck;
}

void func_8010DEBC_stacked_deck(void) {
    omObjData *obj = omAddObj(0x24E, 1, 0, -1, func_8010DDAC_stacked_deck);
    obj->work[0] = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DEF4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E368_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E4EC_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E590_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E650_stacked_deck);

void func_8010E6FC_stacked_deck(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_8010E650_stacked_deck;
    }
}

void func_8010E734_stacked_deck(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        object->func = func_8010E6FC_stacked_deck;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010E78C_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010ED44_stacked_deck);

void func_8010EFBC_stacked_deck(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010EFC4_stacked_deck);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010F134_stacked_deck);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F6E8_stacked_deck);
