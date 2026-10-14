#include "common.h"

typedef struct GameGuysMagicBoxesCamera { // 0x20 bytes
    f32 unk_00;                           // perspective camera id
    f32 unk_04;                           // zoom
    f32 unk_08;                           // CRot x
    f32 unk_0C;                           // CRot y
    f32 unk_10;                           // CRot z
    f32 unk_14;                           // Center x
    f32 unk_18;                           // Center y
    f32 unk_1C;                           // Center z
} GameGuysMagicBoxesCamera;

typedef struct GameGuysMagicBoxesBonus { // 0x6 bytes
    s16 amount[3];
} GameGuysMagicBoxesBonus;

typedef struct GameGuysMagicBoxesSprite { // 0x1C bytes
    /* 0x00 */ s16 unk_00;                // esprite slot, written by func_80109C98
    /* 0x02 */ s16 priority;              // lower 8 bits given to HuSprPriSet
    /* 0x04 */ s16 unk_04;                // given to func_8000BBFC
    /* 0x06 */ s16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 xSub;   // added to x, halved
    /* 0x0C */ s16 ySub;   // added to y, halved
    /* 0x10 */ f32 unk_10; // given to func_8000BF00
    /* 0x14 */ f32 scaleX;
    /* 0x18 */ f32 scaleY;
} GameGuysMagicBoxesSprite;

extern u8 D_8010C1FA_game_guys_magic_boxes;
extern u8 D_8010C1FB_game_guys_magic_boxes;
extern u8 D_8010C21C_game_guys_magic_boxes;  // state
extern u16 D_8010C21E_game_guys_magic_boxes; // sprite alpha timer
extern u8 D_8010C750_game_guys_magic_boxes;
extern s16 D_8010C756_game_guys_magic_boxes;
extern u8 D_8010C9D9_game_guys_magic_boxes;
extern u8 D_8010C9E1_game_guys_magic_boxes;
extern u8 D_8010C9E2_game_guys_magic_boxes;
extern u8 D_8010C9E7_game_guys_magic_boxes;
extern u16 D_8010CA0A_game_guys_magic_boxes;
extern GameGuysMagicBoxesBonus D_8010C5A0_game_guys_magic_boxes;
extern Vec D_8010C9B0_game_guys_magic_boxes;
extern Vec D_8010C9BC_game_guys_magic_boxes;
extern u8 D_8010C9E8_game_guys_magic_boxes;
extern HuSprite *D_8010C9EC_game_guys_magic_boxes;
extern s16 D_8010C9F0_game_guys_magic_boxes;
extern void *D_8010C9F4_game_guys_magic_boxes[3];
extern s16 D_8010CA0C_game_guys_magic_boxes;

void func_8000BC48_main(u16, u16);
void func_80109884_game_guys_magic_boxes(omObjData *object);
void func_80109984_game_guys_magic_boxes(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_801059A0_game_guys_magic_boxes);

s32 func_801059BC_game_guys_magic_boxes(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105A28_game_guys_magic_boxes);

void func_80105AC0_game_guys_magic_boxes(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105AC8_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105B44_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105B60_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105CCC_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105FB4_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106558_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_801066F8_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106828_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106A2C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106B50_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106CB8_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80106DC4_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107020_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_801071B8_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107834_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107A3C_game_guys_magic_boxes);

void func_80107AE0_game_guys_magic_boxes(void) {
    if (D_8010C1FA_game_guys_magic_boxes == 0) {
        GMesClose();
        D_8010CA0C_game_guys_magic_boxes = GMesCreate(GMES_MES_9);
        D_8010C1FA_game_guys_magic_boxes = 1;
    } else if (D_8010C1FA_game_guys_magic_boxes == 1) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            D_8010C9E8_game_guys_magic_boxes = 8;
            D_8010C1FA_game_guys_magic_boxes = 0;
            D_8010C1FB_game_guys_magic_boxes = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107B64_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108294_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108498_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010861C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108914_game_guys_magic_boxes);

void func_80108AF8_game_guys_magic_boxes(void) {
    s16 *coins;

    switch (D_8010C21C_game_guys_magic_boxes) {
        case 0:
            D_8010C9E7_game_guys_magic_boxes++;
            coins = &D_8010C756_game_guys_magic_boxes;
            *coins = *coins * 2;
            D_8010C9E1_game_guys_magic_boxes = 0;
            D_8010C21C_game_guys_magic_boxes++;
            break;
        case 1:
            if (D_8010C21E_game_guys_magic_boxes == 0) {
                D_8010C21C_game_guys_magic_boxes = 2;
            } else {
                D_8010C21E_game_guys_magic_boxes -= 8;
            }
            func_80055458_main(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C21E_game_guys_magic_boxes);
            break;
        case 2:
            D_8010C9D9_game_guys_magic_boxes = 0;
            D_8010C9E8_game_guys_magic_boxes = 3;
            D_8010C21C_game_guys_magic_boxes = 0;
            D_8010C21E_game_guys_magic_boxes = 0x80;
            break;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C514_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C520_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C530_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C538_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C544_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C550_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C55C_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C568_game_guys_magic_boxes);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", D_8010C574_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108C04_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108D88_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_801090F0_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010935C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010942C_game_guys_magic_boxes);

void func_80109600_game_guys_magic_boxes(omObjData *object) {
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes.x, D_8010C9B0_game_guys_magic_boxes.y,
             D_8010C9B0_game_guys_magic_boxes.z);
    Hu3DModelPosSet(object->model[1], D_8010C9B0_game_guys_magic_boxes.x, D_8010C9B0_game_guys_magic_boxes.y,
                    D_8010C9B0_game_guys_magic_boxes.z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109658_game_guys_magic_boxes);

void func_8010982C_game_guys_magic_boxes(omObjData *object) {
    omSetTra(object, D_8010C9BC_game_guys_magic_boxes.x, D_8010C9BC_game_guys_magic_boxes.y,
             D_8010C9BC_game_guys_magic_boxes.z);
    Hu3DModelPosSet(object->model[1], D_8010C9BC_game_guys_magic_boxes.x,
                    D_8010C9BC_game_guys_magic_boxes.y, D_8010C9BC_game_guys_magic_boxes.z);
}

void func_80109884_game_guys_magic_boxes(omObjData *object) {
    GameGuysMagicBoxesBonus bonus;
    u8 *playerIdx;

    bonus = D_8010C5A0_game_guys_magic_boxes;
    playerIdx = &D_8010C750_game_guys_magic_boxes;
    GwPlayer[*playerIdx].gameCoin = D_8010CA0A_game_guys_magic_boxes;
    if (D_8010C9E2_game_guys_magic_boxes == 1) {
        GwPlayer[*playerIdx].bonusCoin = bonus.amount[D_8010C9E7_game_guys_magic_boxes];
    } else {
        GwPlayer[D_8010C750_game_guys_magic_boxes].bonusCoin = 0;
    }
    WipeCreateOut(0, 20);
    HuAudSeqFadeOut(30);
    func_8004AB0C_main(30);
    object->func = func_80109984_game_guys_magic_boxes;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109984_game_guys_magic_boxes);

void func_801099E4_game_guys_magic_boxes(omObjData *object) {
    if (D_800D530C_main == 1) {
        object->func = func_80109884_game_guys_magic_boxes;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109A0C_game_guys_magic_boxes);

void func_80109AD8_game_guys_magic_boxes(GameGuysMagicBoxesCamera *cam, f32 camId, f32 zoom, f32 rotX,
                                         f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    cam->unk_00 = camId;
    cam->unk_04 = zoom;
    cam->unk_08 = rotX;
    cam->unk_0C = rotY;
    cam->unk_10 = rotZ;
    cam->unk_14 = centerX;
    cam->unk_18 = centerY;
    cam->unk_1C = centerZ;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109B10_game_guys_magic_boxes);

void func_80109C98_game_guys_magic_boxes(GameGuysMagicBoxesSprite *sprite, s32 spriteIndex, u16 numSlots,
                                         u16 visibility) {
    sprite->unk_00 = InitEspriteSlot(func_8000B838_main(spriteIndex), 0, numSlots);
    func_8000BC48_main(sprite->unk_00, visibility);
}

void func_80109CFC_game_guys_magic_boxes(GameGuysMagicBoxesSprite *sprite, s16 priority, s16 unk04, s16 x,
                                         s16 y, s16 xSub, s16 ySub, f32 unk10, f32 scaleX, f32 scaleY) {
    sprite->priority = priority;
    sprite->unk_04 = unk04;
    sprite->x = x;
    sprite->y = y;
    sprite->xSub = xSub;
    sprite->ySub = ySub;
    sprite->unk_10 = unk10;
    sprite->scaleX = scaleX;
    sprite->scaleY = scaleY;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109D3C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109E1C_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A000_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A1B0_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A388_game_guys_magic_boxes);

void func_8010A4CC_game_guys_magic_boxes(void) {
    D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 =
        D_8010C9F4_game_guys_magic_boxes[0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A4EC_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A560_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A6AC_game_guys_magic_boxes);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_8010A878_game_guys_magic_boxes);
