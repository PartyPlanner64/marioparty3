#include "common.h"
#include "gcc/memory.h"
#include "math.h"
#include "overlays/minigame.h"

// The 4 player entries start at entry 2 of D_8010F730_stacked_deck, and the 12
// cards laid out on the table start at entry 6.
#define STACKED_DECK_PLAYERS (&D_8010F730_stacked_deck[2])
#define STACKED_DECK_CARDS (&D_8010F730_stacked_deck[6])
// Entries 23-25 are the three spinning objects created by func_8010E4EC_stacked_deck.
#define STACKED_DECK_SPINNERS (&D_8010F730_stacked_deck[23])

typedef struct {
    f32 scissorX;
    f32 scissorY;
    f32 scissorWidth;
    f32 scissorHeight;
    Vec viewportScale;
    Vec viewportTranslate;
    f32 fov;
} StackedDeckCamera;

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
// Alias of the player entries (STACKED_DECK_PLAYERS), used where the target
// indexes the player table directly.
extern StackedDeckCard D_8010F838_stacked_deck[4];
extern s32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern u8 D_8010F6F4_stacked_deck;
extern void *D_8010F708_stacked_deck[];
extern Vec2f D_8010F2B0_stacked_deck[12];
extern s16 D_8010F6F0_stacked_deck;
extern s16 D_80111120_stacked_deck;
extern s16 D_80111150_stacked_deck[];
extern u8 D_80111168_stacked_deck;
extern u8 D_80111169_stacked_deck;
extern s16 D_80111170_stacked_deck;
extern s32 D_8010F35C_stacked_deck;
extern Vec2f D_8010F310_stacked_deck[];
extern f32 D_8010F328_stacked_deck[];
extern s32 D_801110FC_stacked_deck;
extern D_80111B50_vine_with_me_Struct D_8010F334_stacked_deck;
extern StackedDeckCamera D_8010F360_stacked_deck[1];
extern const s16 D_8010F6E8_stacked_deck[];
extern s16 D_8010F6F2_stacked_deck;
extern s8 D_8010F6F5_stacked_deck[];
extern s16 D_8010F6FA_stacked_deck[];
extern s16 D_8010F720_stacked_deck;
extern s16 D_801110F8_stacked_deck;
extern s16 D_801110FA_stacked_deck;
extern s16 D_80111100_stacked_deck;
extern s16 D_80111102_stacked_deck[];
extern s16 D_8011110A_stacked_deck;
extern s16 D_8011110C_stacked_deck;
extern s8 D_80111110_stacked_deck[4][4];
extern s16 D_80111128_stacked_deck[];
extern s16 D_80111140_stacked_deck;
extern s16 D_80111142_stacked_deck[];
extern s16 D_8011114A_stacked_deck;
extern s16 D_8011114C_stacked_deck;
extern s16 D_8011114E_stacked_deck;
extern s16 D_8011116A_stacked_deck;
extern s16 D_8011116C_stacked_deck;
extern s16 D_8011116E_stacked_deck;

void func_801063F4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1, f32 *velX, f32 *velZ, f32 speed);
void func_80106554_stacked_deck(omObjData *object);
void func_8010655C_stacked_deck(omObjData *object);
void func_80106694_stacked_deck(omObjData *object);
void func_8010669C_stacked_deck(omObjData *object);
void func_80106BC8_stacked_deck(omObjData *object);
void func_80108E48_stacked_deck(omObjData *object);
void func_801097D4_stacked_deck(omObjData *object);
void func_8010C188_stacked_deck(omObjData *object);
void func_8010C5C8_stacked_deck(omObjData *object);
void func_8010D98C_stacked_deck(omObjData *object);
void func_8010DAE4_stacked_deck(omObjData *object);
void func_8010DC2C_stacked_deck(omObjData *object);
void func_8010DDAC_stacked_deck(omObjData *object);
void func_8010DEF4_stacked_deck(omObjData *object);
void func_8010E368_stacked_deck(omObjData *object);
void func_8010E650_stacked_deck(omObjData *object);
void func_8010E6FC_stacked_deck(omObjData *object);
void func_8010E734_stacked_deck(omObjData *object);
void func_8010E78C_stacked_deck(omObjData *object);
void func_8010ED44_stacked_deck(omObjData *object);
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

void func_80105BB4_stacked_deck(f32 x0, f32 z0, f32 x1, f32 z1) {
    f32 dx = fabs(x0 - x1) * 5.0;
    f32 dz = fabs(z0 - z1) * 5.0;
    f32 zoom = sqrtf(dx * dx + dz * dz);
    f32 rot = func_801059BC_stacked_deck(atan2df(dx, dz), 0.0f);

    osSyncPrintf("Zoom = %f\n", zoom);
    osSyncPrintf("Rot  = %f\n", 360.0f - rot);
}

void func_80105CBC_stacked_deck(s16 conNo) {
    s16 i;

    if (conNo < 0 || conNo >= 4) {
        osSyncPrintf("\n ConNo False! \n");
        return;
    }
    if ((u16)D_800CDA7C_main[conNo] & D_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_stacked_deck(CRotM[i].x, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].x = func_801059BC_stacked_deck(CRotM[i].x, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_stacked_deck(CRotM[i].y, 1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_JPAD) {
        for (i = 0; i < 1; i++) {
            CRotM[i].y = func_801059BC_stacked_deck(CRotM[i].y, -1.0f);
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & A_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & B_BUTTON) {
        for (i = 0; i < 1; i++) {
            CZoomM[i] -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & L_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & R_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].x += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & U_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y += 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & D_CBUTTONS) {
        for (i = 0; i < 1; i++) {
            CenterM[i].y -= 10.0f;
        }
    }
    if ((u16)D_800CDA7C_main[conNo] & Z_TRIG) {
        osSyncPrintf("\n");
        for (i = 0; i < 1; i++) {
            osSyncPrintf("CameraNo / %d   Zoom / %f\n", i, CZoomM[i]);
            osSyncPrintf("Rot:   X / %f   Y / %f   Z / %f\n", CRotM[i].x, CRotM[i].y, CRotM[i].z);
            osSyncPrintf("Center:   X / %f   Y / %f   Z / %f\n", CenterM[i].x, CenterM[i].y, CenterM[i].z);
        }
    }
}

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
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, D_8010F708_stacked_deck[anim], 0, "card_k_DEF");
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80106BC8_stacked_deck);

#ifdef NON_MATCHING
// Only differs in v0/v1 register allocation of the player address in the final
// positioning loop.
void func_80108E48_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &STACKED_DECK_PLAYERS[object->work[0]];
    u16 character = GwPlayer[object->work[0]].chr;
    s32 modelFile = D_800A178C_main[character][0];
    s32 motionFile = D_800A1790_main[character][0];
    func_800E1BA8_minigame_ObjData *work;
    omObjData *obj;
    s32 values[4];
    s16 i;
    s16 j;
    s16 rank;
    s16 slot;

    func_800E18D8_minigame();
    func_800E1BA8_minigame(object, modelFile, motionFile, ((u16 *)object->work)[1], 0x2B9, 0x2A9);
    work = object->data;
    work->unkEC = NULL;
    func_8001C2FC_main(object->model[1], 0x80000000, 0);
    func_8001C258_main(object->model[1], 0x60, 0x20);
    func_8001C258_main(object->model[1], 0x180, 0x80);
    Hu3DModelRemakeStatic(object->model[1]);
    func_8001C514_main(object->model[1]);
    object->model[7] = func_8000B108_main(8, 0x2BD);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(character, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(character, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(character, 4), 1, 0x13);
    func_800E5A00_minigame(object, 8, func_80017BB8_main(character, 6), 1, 0x1B);
    func_800E5A00_minigame(object, 0x12, func_80017BB8_main(character, 0xF), 2, 0);
    func_800E5978_minigame(object, 0x15, func_80017BB8_main(character, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(character, 0x30), 1, 0x78);
    func_800E5A00_minigame(object, 0x27, func_80017BB8_main(character, 0x33), 2, 0);
    func_800E5A00_minigame(object, 0x28, func_80017BB8_main(character, 0x7A), 2, 0);
    func_800E5A00_minigame(object, 0x29, func_80017BB8_main(character, 0x37), 1, 0x78);
    func_800E5A00_minigame(object, 0x2A, func_80017BB8_main(character, 0x70), 1, 0);
    card->unk_04[1] = 0;
    func_800E5690_minigame(object, 0);
    D_800EBE24_minigame = 1;

    // The last player sets up the turn order for everyone, ranked by coins and
    // then by stars.
    if (object->work[0] == 3) {
        for (i = 0; i < 4; i++) {
            obj = STACKED_DECK_PLAYERS[i].obj;
            for (j = 0; j < 4; j++) {
                values[j] = GwPlayer[j].coin;
            }
            for (j = 0, rank = 0; j < 4; j++) {
                if (j != obj->work[0] && values[obj->work[0]] < values[j]) {
                    rank++;
                }
            }
            D_8010F6FA_stacked_deck[i] = rank;
        }
        for (i = 0; i < 4; i++) {
            obj = STACKED_DECK_PLAYERS[i].obj;
            for (j = 0; j < 4; j++) {
                values[j] = GwPlayer[j].star;
            }
            for (j = 0, rank = 0; j < 4; j++) {
                if (j != obj->work[0]) {
                    if (values[obj->work[0]] < values[j]) {
                        rank++;
                    } else if (values[obj->work[0]] == values[j] &&
                               D_8010F6FA_stacked_deck[i] > D_8010F6FA_stacked_deck[j]) {
                        rank++;
                    }
                }
            }
            D_80111102_stacked_deck[i] = rank;
        }
        for (i = 0; i < 4; i++) {
            obj = STACKED_DECK_PLAYERS[i].obj;
            rank = D_80111102_stacked_deck[i];
            obj->work[1] = rank;
            D_80111110_stacked_deck[rank][D_8010F6F5_stacked_deck[rank]] = obj->work[0];
            D_8010F6F5_stacked_deck[rank]++;
        }
        for (i = 0; i < 4;) {
            if (D_8010F6F5_stacked_deck[i] >= 2) {
                slot = func_80105A3C_stacked_deck(D_8010F6F5_stacked_deck[i]);
                obj = D_8010F838_stacked_deck[D_80111110_stacked_deck[i][slot]].obj;
                obj->work[1] += D_8010F6F5_stacked_deck[i] - 1;
                D_8010F6F5_stacked_deck[i]--;
                for (j = slot; j < 3; j++) {
                    D_80111110_stacked_deck[i][j] = D_80111110_stacked_deck[i][j + 1];
                }
                if (D_8010F6F5_stacked_deck[i] == 1) {
                    i++;
                }
            } else {
                i++;
            }
        }
        for (i = 0; i < 4; i++) {
            obj = STACKED_DECK_PLAYERS[i].obj;
            obj->trans.x = obj->work[1] * 140.0f;
            obj->trans.y = 0.0f;
            obj->trans.z = 1100.0f;
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelPosSet(obj->model[1], obj->trans.x, obj->trans.y, obj->trans.z);
        }
    }
    func_800E149C_minigame(object, 0, 2);
    func_80105B3C_stacked_deck(object->work[0]);
    object->rot.y = 180.0f;
    work->unk3C = 180.0f;
    object->func = func_80106BC8_stacked_deck;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_80108E48_stacked_deck);
#endif

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
        Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, D_8010F708_stacked_deck[0], 0, "card_k_DEF");
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

#ifdef NON_MATCHING
// Only differs in v0/v1 register allocation of the spinner address in the
// four small loops over STACKED_DECK_SPINNERS.
void func_8010DEF4_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[object->work[0] + 23];
    f32 speed;
    s16 i;
    s16 moving;

    switch (D_8010F6F4_stacked_deck) {
        case 8:
            speed = 2.0f;
            break;
        case 9:
            speed = 4.0f;
            break;
        default:
            speed = 1.0f;
            break;
    }

    switch (D_8010F6F4_stacked_deck) {
        case 2:
            card->unk_18[0] -= D_8010F328_stacked_deck[object->work[0]] * 5.0f;
            if (card->unk_18[0] < 0.0f) {
                card->unk_18[0] = func_801059BC_stacked_deck(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        case 3:
            card->unk_18[0] += D_8010F328_stacked_deck[object->work[0]] * 5.0f;
            if (card->unk_18[0] > 360.0f) {
                card->unk_18[0] = func_801059BC_stacked_deck(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        case 11:
            if (object->work[0] == 0 || object->work[0] == 2) {
                card->unk_18[0] += D_8010F328_stacked_deck[object->work[0]] * 5.0f;
            } else {
                card->unk_18[0] -= D_8010F328_stacked_deck[object->work[0]] * 5.0f;
            }
            if (card->unk_18[0] > 360.0f) {
                card->unk_18[0] = func_801059BC_stacked_deck(card->unk_18[0], 0.0f);
            }
            if (card->unk_18[0] < 0.0f) {
                card->unk_18[0] = func_801059BC_stacked_deck(card->unk_18[0], 0.0f);
            }
            card->unk_04[0] = 0;
            break;
        default:
            switch (card->unk_04[0]) {
                case 0:
                    if (card->unk_18[0] > -40.0f) {
                        card->unk_18[0] -= speed * D_8010F328_stacked_deck[object->work[0]];
                    } else {
                        card->unk_18[0] = -40.0f;
                    }
                    moving = FALSE;
                    for (i = 0; i < 3; i++) {
                        if (STACKED_DECK_SPINNERS[i].unk_18[0] != -40.0f) {
                            moving = TRUE;
                        }
                    }
                    if (!moving) {
                        for (i = 0; i < 3; i++) {
                            STACKED_DECK_SPINNERS[i].unk_04[0] = 1;
                        }
                    }
                    break;
                case 1:
                    if (card->unk_18[0] < 40.0f) {
                        card->unk_18[0] += speed * D_8010F328_stacked_deck[object->work[0]];
                    } else {
                        card->unk_18[0] = 40.0f;
                    }
                    moving = FALSE;
                    for (i = 0; i < 3; i++) {
                        if (STACKED_DECK_SPINNERS[i].unk_18[0] != 40.0f) {
                            moving = TRUE;
                        }
                    }
                    if (!moving) {
                        for (i = 0; i < 3; i++) {
                            STACKED_DECK_SPINNERS[i].unk_04[0] = 0;
                        }
                    }
                    break;
            }
            break;
    }

    object->rot.z = func_801059BC_stacked_deck(card->unk_18[0], 0.0f);
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", func_8010DEF4_stacked_deck);
#endif

void func_8010E368_stacked_deck(omObjData *object) {
    StackedDeckCard *card = &D_8010F730_stacked_deck[object->work[0] + 23];

    if (object->work[0] == 0) {
        object->model[0] = func_8000B108_main(0x4B000A, 0x2B9);
        D_801110FC_stacked_deck = object->model[0];
    } else {
        object->model[0] = Hu3DModelLink((s16)D_801110FC_stacked_deck);
    }
    object->trans.x = D_8010F310_stacked_deck[object->work[0]].x * 5.0f;
    object->trans.y = D_8010F310_stacked_deck[object->work[0]].y * 5.0f;
    object->trans.z = -875.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->rot.x = 0.0f;
    object->rot.y = 180.0f;
    object->rot.z = 0.0f;
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->rot.z);
    object->scale.x = 1.0f;
    object->scale.y = 1.0f;
    object->scale.z = 1.0f;
    Hu3DModelScaleSet(object->model[0], object->scale.x, object->scale.y, object->scale.z);
    card->unk_18[0] = 0.0f;
    func_8001C258_main(object->model[0], 4, 0);
    object->func = func_8010DEF4_stacked_deck;
}

void func_8010E4EC_stacked_deck(void) {
    s16 i;

    for (i = 0; i < 3; i++) {
        StackedDeckCard *card = &D_8010F730_stacked_deck[i + 23];
        omObjData *obj = omAddObj(0x258, 1, 1, -1, func_8010E368_stacked_deck);

        obj->work[0] = i;
        card->obj = obj;
    }
}

void func_8010E590_stacked_deck(void) {
    u32 i;

    if (D_8010F35C_stacked_deck == 0) {
        D_8010F35C_stacked_deck = 1;
        for (i = 0; i < 1; i++) {
            CZoomM[i] = 2522.7217f;
            CRotM[i].x = 332.3684f;
            CRotM[i].y = 0.0f;
            CRotM[i].z = 0.0f;
            CenterM[i].x = 0.0f;
            CenterM[i].y = -200.0f;
            CenterM[i].z = 75.0f;
        }
    }
}

void func_8010E650_stacked_deck(omObjData *object) {
    s16 i;

    for (i = 0; i < 6; i++) {
        DataClose(D_8010F708_stacked_deck[i]);
    }
    for (i = 0; i < 12; i++) {
        Hu3DAnimKill(D_80111150_stacked_deck[i]);
    }
    osViBlack(FALSE);
    omOvlReturnEx(1);
}

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

void func_8010E78C_stacked_deck(omObjData *object) {
    StackedDeckCard *players[4];
    omObjData *playerObjs[4];
    s16 i;

    for (i = 0; i < 4; i++) {
        players[i] = &STACKED_DECK_PLAYERS[i];
        playerObjs[i] = players[i]->obj;
    }

    switch (D_8010F6F4_stacked_deck) {
        case 0:
            func_80106290_stacked_deck(1);
            D_8010F720_stacked_deck = 0;
            break;
        case 1:
            if (D_80111169_stacked_deck == 1) {
                if (!(rand8() & 1)) {
                    func_80106290_stacked_deck(2);
                } else {
                    func_80106290_stacked_deck(3);
                }
            }
            break;
        case 2:
            if (D_80111169_stacked_deck == 2) {
                if (D_8011116C_stacked_deck == 0) {
                    func_80106290_stacked_deck(4);
                } else {
                    func_80106290_stacked_deck(13);
                }
                if (++D_8011116C_stacked_deck >= 5) {
                    D_8011116C_stacked_deck = 4;
                }
            }
            break;
        case 3:
            if (D_80111169_stacked_deck == 3) {
                if (D_8011116C_stacked_deck == 0) {
                    func_80106290_stacked_deck(4);
                } else {
                    func_80106290_stacked_deck(13);
                }
                if (++D_8011116C_stacked_deck >= 5) {
                    D_8011116C_stacked_deck = 4;
                }
            }
            break;
        case 4:
            if (D_80111169_stacked_deck == 4) {
                func_80106290_stacked_deck(5);
                D_8010F720_stacked_deck = 0;
            }
            break;
        case 5:
            if (D_8010F720_stacked_deck == 0) {
                GMesCreate(7);
                D_8010F720_stacked_deck++;
            } else if (D_8010F720_stacked_deck >= 43) {
                HuAudSeqPlay(0x35);
            } else {
                D_8010F720_stacked_deck++;
            }
            if (GMesStatGet() == 0) {
                func_80106290_stacked_deck(6);
                GMesCreate(0x1A, 10, 0xA0, 0x1C);
                D_8010F720_stacked_deck = 301;
            }
            break;
        case 13:
            if (D_80111169_stacked_deck == 13) {
                func_80106290_stacked_deck(6);
                GMesCreate(0x1A, 10, 0xA0, 0x1C);
                D_8010F720_stacked_deck = 301;
            }
            break;
        case 6:
            if (D_8010F720_stacked_deck > 0) {
                D_8010F720_stacked_deck--;
                func_8003F578_main((D_8010F720_stacked_deck + 29) / 30);
            } else if (D_80111169_stacked_deck != 6 && D_80111168_stacked_deck == 0) {
                D_8010F6F0_stacked_deck = 4;
                func_8003F5C0_main();
                D_8010F720_stacked_deck = 0;
                func_80106290_stacked_deck(7);
            }
            if (D_80111169_stacked_deck == 6) {
                func_8003F5C0_main();
                D_8010F720_stacked_deck = 0;
                func_80106290_stacked_deck(7);
            }
            break;
        case 7:
            if (D_80111169_stacked_deck == 7) {
                D_8010F720_stacked_deck = 0;
                switch (D_8010F6F0_stacked_deck) {
                    case 1:
                        func_80106290_stacked_deck(8);
                        break;
                    case 2:
                        func_80106290_stacked_deck(9);
                        break;
                    case 3:
                        if (D_8011116E_stacked_deck == 1) {
                            func_80106290_stacked_deck(14);
                        } else {
                            func_80106290_stacked_deck(11);
                        }
                        break;
                }
            }
            break;
        case 8:
            if (D_80111169_stacked_deck == 8) {
                D_8011116A_stacked_deck--;
                func_80106290_stacked_deck(13);
            }
            break;
        case 9:
            if (D_80111169_stacked_deck == 9) {
                D_80111100_stacked_deck--;
                func_80106290_stacked_deck(10);
            }
            break;
        case 10:
            if (D_80111169_stacked_deck == 10) {
                func_80106290_stacked_deck(13);
            }
            break;
        case 11:
            if (D_80111169_stacked_deck == 11) {
                D_801110FA_stacked_deck--;
                func_80106290_stacked_deck(13);
            }
            break;
        case 12:
            break;
        case 14:
            if (D_8011110A_stacked_deck == 1) {
                GMesCreate(0x12);
                HuAudSeqFadeOut(120);
                func_80106290_stacked_deck(15);
                D_8010F720_stacked_deck = -15;
            }
            break;
        case 15:
            if (GMesStatGet() == 0) {
                if (D_8010F720_stacked_deck >= 0) {
                    func_80106290_stacked_deck(16);
                    D_8010F720_stacked_deck = 98;
                } else {
                    D_8010F720_stacked_deck++;
                }
            }
            break;
        case 16:
            if (D_8010F720_stacked_deck == 98) {
                HuAudSeqPlay(0x65);
            }
            if (D_8010F720_stacked_deck > 0) {
                D_8010F720_stacked_deck--;
            } else {
                func_80106290_stacked_deck(17);
                D_8010F720_stacked_deck = 0;
                for (i = 0; i < 4; i++) {
                    GwPlayer[playerObjs[i]->work[0]].bonusCoin = players[i]->unk_04[7];
                }
            }
            break;
        case 17:
            if (D_8010F720_stacked_deck == 0) {
                WipeCreateOut(0, 20);
                object->func = func_8010E6FC_stacked_deck;
                D_8010F720_stacked_deck++;
            }
            break;
    }
}

void func_8010ED44_stacked_deck(omObjData *object) {
    s16 i;
    s16 j;

    func_800E6F0C_minigame(2);
    D_8010F720_stacked_deck = 0;
    D_8010F6F4_stacked_deck = 0;
    D_80111169_stacked_deck = 0;
    D_8011116C_stacked_deck = 0;
    D_8011116A_stacked_deck = 0;
    D_80111100_stacked_deck = 0;
    D_801110FA_stacked_deck = 0;
    D_80111170_stacked_deck = 0;
    D_80111120_stacked_deck = 0;
    D_8010F6F0_stacked_deck = 0;
    D_8011116E_stacked_deck = 3;
    for (i = 0; i < 4; i++) {
        D_80111142_stacked_deck[i] = 0;
    }
    D_80111168_stacked_deck = 0;
    for (i = 0; i < 12; i++) {
        D_80111128_stacked_deck[i] = 0;
    }
    D_8011114E_stacked_deck = 0;
    D_801110F8_stacked_deck = 0;
    D_8011114C_stacked_deck = 0;
    for (i = 0; i < 4; i++) {
        D_8010F6F5_stacked_deck[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_80111110_stacked_deck[i][j] = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        D_8010F6FA_stacked_deck[i] = 0;
        D_80111102_stacked_deck[i] = 0;
    }
    D_8011114A_stacked_deck = 0;
    D_8011110C_stacked_deck = 0;
    D_8010F6F2_stacked_deck = 0;
    D_80111140_stacked_deck = 0;
    D_8011110A_stacked_deck = 0;
    func_80106654_stacked_deck();
    func_80106738_stacked_deck();
    func_8010969C_stacked_deck();
    func_8010C524_stacked_deck();
    func_8010D8E8_stacked_deck();
    func_8010DBF4_stacked_deck();
    func_8010DEBC_stacked_deck();
    func_8010E4EC_stacked_deck();
    func_8010E590_stacked_deck();
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    object->func = func_8010E78C_stacked_deck;
}

void func_8010EFBC_stacked_deck(void) {
}

void func_8010EFC4_stacked_deck(void) {
    omObjData *obj;
    s32 i;

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 1;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_8000B5F0_main(1);
    func_8000B710_main(1);
    for (i = 0; i < 1; i++) {
        ScissorSet(i, D_8010F360_stacked_deck[i].scissorX, D_8010F360_stacked_deck[i].scissorY,
                   D_8010F360_stacked_deck[i].scissorWidth, D_8010F360_stacked_deck[i].scissorHeight);
        ViewportSet(i, D_8010F360_stacked_deck[i].viewportScale.x, D_8010F360_stacked_deck[i].viewportScale.y,
                    D_8010F360_stacked_deck[i].viewportScale.z, D_8010F360_stacked_deck[i].viewportTranslate.x,
                    D_8010F360_stacked_deck[i].viewportTranslate.y, D_8010F360_stacked_deck[i].viewportTranslate.z);
        Hu3DCameraPerspectiveSet(i, D_8010F360_stacked_deck[i].fov, 80.0f, 8000.0f);
    }
}

void func_8010F134_stacked_deck(void) {
    func_8001FE20_main(50);
    func_800142A0_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_8010EFC4_stacked_deck();
    Hu3DGLightMaxSet(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(0, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 90.0f, 560.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 90.0f, 560.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_80045010_main(D_8010F6E8_stacked_deck, 0);
    func_80045010_main(D_8010F6E8_stacked_deck, 1);
    omAddObj(1000, 0, 0, -1, func_8010ED44_stacked_deck);
    omAddObj(1000, 0, 0, -1, func_8010E734_stacked_deck);
    func_80105A74_stacked_deck();
    func_800E5EA0_minigame(&D_8010F334_stacked_deck);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_2A_stacked_deck/240A10", D_8010F6E8_stacked_deck);
