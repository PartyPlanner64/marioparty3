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

typedef struct GameGuysMagicBoxesCharSprites { // 0x20 bytes
    s32 ids[8];                                // per-character sprite index (low half)
} GameGuysMagicBoxesCharSprites;

extern u8 D_8010C1FA_game_guys_magic_boxes;
extern u8 D_8010C1FB_game_guys_magic_boxes;
extern u8 D_8010C21C_game_guys_magic_boxes;  // state
extern u16 D_8010C21E_game_guys_magic_boxes; // sprite alpha timer
extern f32 D_8010C1E0_game_guys_magic_boxes;
extern f32 D_8010C1E4_game_guys_magic_boxes;
extern u8 D_8010C5D0_game_guys_magic_boxes[];
extern u8 D_8010C1EE_game_guys_magic_boxes;
extern u8 D_8010C1EF_game_guys_magic_boxes; // drop state
extern u16 D_8010C1F0_game_guys_magic_boxes;
extern f32 D_8010C1F4_game_guys_magic_boxes;
extern u16 D_8010C1F8_game_guys_magic_boxes;
extern u8 D_8010C1FC_game_guys_magic_boxes;  // choice state
extern s16 D_8010C1FE_game_guys_magic_boxes; // countdown tick timer
extern s16 D_8010C200_game_guys_magic_boxes; // countdown seconds
extern s16 D_8010C202_game_guys_magic_boxes; // CPU decision timer
extern f32 D_8010C204_game_guys_magic_boxes;
extern u16 D_8010C208_game_guys_magic_boxes;
extern u8 D_8010C20A_game_guys_magic_boxes;
extern f32 D_8010C20C_game_guys_magic_boxes;
extern u8 D_8010C210_game_guys_magic_boxes;
extern u16 D_8010C212_game_guys_magic_boxes;
extern s16 D_8010C214_game_guys_magic_boxes;
extern s16 D_8010C216_game_guys_magic_boxes;
extern u8 D_8010C218_game_guys_magic_boxes;
extern u16 D_8010C21A_game_guys_magic_boxes;
extern s16 D_8010C5D4_game_guys_magic_boxes;
extern s16 D_8010C7FE_game_guys_magic_boxes; // sprite x
extern s16 D_8010C81E_game_guys_magic_boxes; // sprite x
extern u16 D_8010C5D6_game_guys_magic_boxes;
extern Vec D_8010C5D8_game_guys_magic_boxes[2];
extern Vec2f D_8010C5F0_game_guys_magic_boxes[2];
extern Vec2f D_8010C600_game_guys_magic_boxes[3][2];
extern u8 D_8010CA00_game_guys_magic_boxes;
extern u8 D_8010C750_game_guys_magic_boxes;
extern u8 D_8010C751_game_guys_magic_boxes[3]; // [0] player, [2] mode for the window helpers
extern Process *D_8010C774_game_guys_magic_boxes;
extern Process *D_8010C778_game_guys_magic_boxes;
extern Process *D_8010C77C_game_guys_magic_boxes;
extern s16 D_8010CA0E_game_guys_magic_boxes;
extern u8 D_8010C753_game_guys_magic_boxes[2];
extern s16 D_8010C756_game_guys_magic_boxes;
extern f32 D_8010C9D0_game_guys_magic_boxes;
extern f32 D_8010C9D4_game_guys_magic_boxes;
extern u8 D_8010C9C8_game_guys_magic_boxes;
extern u8 D_8010C9C9_game_guys_magic_boxes;
extern u8 D_8010C9CA_game_guys_magic_boxes;
extern s16 D_8010CA10_game_guys_magic_boxes;
extern s16 D_8010CA12_game_guys_magic_boxes;
extern u8 D_8010C9D8_game_guys_magic_boxes;
extern u8 D_8010C9D9_game_guys_magic_boxes;
extern u8 D_8010C9DA_game_guys_magic_boxes;
extern u8 D_8010C9DB_game_guys_magic_boxes[3][2];
extern u8 D_8010C9E3_game_guys_magic_boxes[];
extern u8 D_8010C9E6_game_guys_magic_boxes;
extern s16 D_8010CA02_game_guys_magic_boxes;
extern s16 D_8010CA04_game_guys_magic_boxes;
extern u8 D_8010CA06_game_guys_magic_boxes;
extern u8 D_8010C9E1_game_guys_magic_boxes;
extern u8 D_8010C9E2_game_guys_magic_boxes;
extern u8 D_8010C9E7_game_guys_magic_boxes;
extern u16 D_8010CA0A_game_guys_magic_boxes;
extern GameGuysMagicBoxesBonus D_8010C5A0_game_guys_magic_boxes;
extern Vec D_8010C9B0_game_guys_magic_boxes[2];
extern u8 D_8010C9E8_game_guys_magic_boxes;
extern HuSprite *D_8010C9EC_game_guys_magic_boxes;
extern s16 D_8010C9F0_game_guys_magic_boxes;
extern void *D_8010C9F4_game_guys_magic_boxes[3];
extern s16 D_8010CA0C_game_guys_magic_boxes;
extern GameGuysMagicBoxesCamera D_8010C730_game_guys_magic_boxes;
extern omObjData *D_8010C758_game_guys_magic_boxes;
extern omObjData *D_8010C75C_game_guys_magic_boxes;
extern omObjData *D_8010C760_game_guys_magic_boxes;
extern omObjData *D_8010C764_game_guys_magic_boxes;
extern omObjData *D_8010C768_game_guys_magic_boxes;
extern omObjData *D_8010C76C_game_guys_magic_boxes;
extern omObjData *D_8010C770_game_guys_magic_boxes;
extern GameGuysMagicBoxesCharSprites D_8010C270_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C780_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C7A0_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C7BC_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C7D8_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C838_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C858_game_guys_magic_boxes[3][2];
extern GameGuysMagicBoxesSprite D_8010C900_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C91C_game_guys_magic_boxes;
extern GameGuysMagicBoxesSprite D_8010C938_game_guys_magic_boxes[3];
extern GameGuysMagicBoxesSprite D_8010C990_game_guys_magic_boxes;

void func_80105A28_game_guys_magic_boxes(void);
void func_80105AC0_game_guys_magic_boxes(void);
void func_80105AC8_game_guys_magic_boxes(void);
void func_80105B44_game_guys_magic_boxes(void);
void func_80105B60_game_guys_magic_boxes(omObjData *object);
void func_80105CCC_game_guys_magic_boxes(void);
void func_80105FB4_game_guys_magic_boxes(omObjData *object);
void func_80108D88_game_guys_magic_boxes(omObjData *object);
void func_80106558_game_guys_magic_boxes(omObjData *object);
void func_801066F8_game_guys_magic_boxes(omObjData *object);
void func_80106828_game_guys_magic_boxes(omObjData *object);
void func_80106A2C_game_guys_magic_boxes(omObjData *object);
void func_80106B50_game_guys_magic_boxes(omObjData *object);
void func_80106CB8_game_guys_magic_boxes(omObjData *object);
void func_80106DC4_game_guys_magic_boxes(omObjData *object);
void func_80107020_game_guys_magic_boxes(void);
void func_801071B8_game_guys_magic_boxes(void);
void func_80107834_game_guys_magic_boxes(void);
void func_80107A3C_game_guys_magic_boxes(void);
void func_80107AE0_game_guys_magic_boxes(void);
void func_80107B64_game_guys_magic_boxes(void);
void func_80108294_game_guys_magic_boxes(void);
void func_80108498_game_guys_magic_boxes(void);
void func_8010861C_game_guys_magic_boxes(void);
void func_80108914_game_guys_magic_boxes(void);
void func_80108AF8_game_guys_magic_boxes(void);
void func_80108C04_game_guys_magic_boxes(void);
void func_8010942C_game_guys_magic_boxes(omObjData *object);
void func_80109600_game_guys_magic_boxes(omObjData *object);
void func_80109658_game_guys_magic_boxes(omObjData *object);
void func_8010982C_game_guys_magic_boxes(omObjData *object);
void func_801090F0_game_guys_magic_boxes(omObjData *object);
void func_8010935C_game_guys_magic_boxes(omObjData *object);
void func_80109884_game_guys_magic_boxes(omObjData *object);
void func_80109984_game_guys_magic_boxes(omObjData *object);
void func_801099E4_game_guys_magic_boxes(omObjData *object);
void func_80109A0C_game_guys_magic_boxes(void);
void func_80109AD8_game_guys_magic_boxes(GameGuysMagicBoxesCamera *cam, f32 camId, f32 zoom, f32 rotX, f32 rotY,
                                         f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void func_80109B10_game_guys_magic_boxes(GameGuysMagicBoxesCamera *cam);
void func_80109E1C_game_guys_magic_boxes(void);
void func_8010A000_game_guys_magic_boxes(void);
void func_80109C98_game_guys_magic_boxes(GameGuysMagicBoxesSprite *sprite, s32 spriteIndex, u16 numSlots,
                                         u16 visibility);
void func_80109CFC_game_guys_magic_boxes(GameGuysMagicBoxesSprite *sprite, s16 priority, s16 unk04, s16 x,
                                         s16 y, s16 xSub, s16 ySub, f32 unk10, f32 scaleX, f32 scaleY);
void func_80109D3C_game_guys_magic_boxes(GameGuysMagicBoxesSprite *sprite, u8 visible);
void func_8010A1B0_game_guys_magic_boxes(s16 x, s16 y, s16 arg2);
void func_8010A388_game_guys_magic_boxes(s16 x, s16 y, s16 arg2);
s16 func_8010A4EC_game_guys_magic_boxes(s16 x, s16 y, s16 lines);
void func_8010A560_game_guys_magic_boxes(s16 win, s16 player, s16 mode);
s16 func_8010A6AC_game_guys_magic_boxes(s16 win, s16 player, s16 mode, s16 count, u16 cancel);
void func_8010A878_game_guys_magic_boxes(s16 win);
void func_8010A8C0_game_guys_magic_boxes(s16 x, s16 y);
u8 func_8010AC18_game_guys_magic_boxes(void);

void func_801059A0_game_guys_magic_boxes(void) {
    func_80105A28_game_guys_magic_boxes();
}

s32 func_801059BC_game_guys_magic_boxes(f32 arg0) {
    u8 randomByte1 = rand8();
    u8 randomByte2 = rand8();
    s32 shiftedByte1 = (randomByte1 << 8);
    s32 scaledRandom = ((randomByte2 | shiftedByte1) / 65536.0f) * arg0;

    return scaledRandom;
}

void func_80105A28_game_guys_magic_boxes(void) {
    func_8001FE20_main(32);
    func_800142A0_main(32);
    omInitObjMan(32, 32);
    func_8004A208_main();
    func_80105AC0_game_guys_magic_boxes();
    func_80105AC8_game_guys_magic_boxes();
    func_80109E1C_game_guys_magic_boxes();
    func_80105B44_game_guys_magic_boxes();
    omAddObj(1000, 0, 0, -1, func_80105B60_game_guys_magic_boxes);
    omAddObj(10000, 0, 0, -1, func_801099E4_game_guys_magic_boxes);
}

void func_80105AC0_game_guys_magic_boxes(void) {
}

void func_80105AC8_game_guys_magic_boxes(void) {
    func_80109A0C_game_guys_magic_boxes();
    func_80109AD8_game_guys_magic_boxes(&D_8010C730_game_guys_magic_boxes, 19.03f, 1498.69f, 334.75f, 0.0f, 0.0f,
                                        0.0f, 10.82f, -505.55f);
    func_80109B10_game_guys_magic_boxes(&D_8010C730_game_guys_magic_boxes);
}

void func_80105B44_game_guys_magic_boxes(void) {
    HuWinInit();
}

void func_80105B60_game_guys_magic_boxes(omObjData *object) {
    func_8010A8C0_game_guys_magic_boxes(160, 190);
    func_80105CCC_game_guys_magic_boxes();
    func_8010A000_game_guys_magic_boxes();
    D_8010C758_game_guys_magic_boxes = omAddObj(1, 10, 10, -1, func_80105FB4_game_guys_magic_boxes);
    D_8010C75C_game_guys_magic_boxes = omAddObj(2, 10, 10, -1, func_80106558_game_guys_magic_boxes);
    D_8010C760_game_guys_magic_boxes = omAddObj(3, 10, 10, -1, func_801066F8_game_guys_magic_boxes);
    D_8010C764_game_guys_magic_boxes = omAddObj(4, 10, 10, -1, func_80106828_game_guys_magic_boxes);
    D_8010C768_game_guys_magic_boxes = omAddObj(5, 10, 10, -1, func_80106A2C_game_guys_magic_boxes);
    D_8010C76C_game_guys_magic_boxes = omAddObj(6, 10, 10, -1, func_80106B50_game_guys_magic_boxes);
    D_8010C770_game_guys_magic_boxes = omAddObj(7, 10, 10, -1, func_80106CB8_game_guys_magic_boxes);
    WipeCreateIn(0xFF, 0x10);
    object->func = func_80106DC4_game_guys_magic_boxes;
}

void func_80105CCC_game_guys_magic_boxes(void) {
    u8 i;

    D_8010C9B0_game_guys_magic_boxes[0].x = -150.0f;
    D_8010C9B0_game_guys_magic_boxes[0].y = 0.0f;
    D_8010C9B0_game_guys_magic_boxes[0].z = -1500.0f;
    D_8010C9B0_game_guys_magic_boxes[1].x = 150.0f;
    D_8010C9B0_game_guys_magic_boxes[1].y = 0.0f;
    D_8010C9B0_game_guys_magic_boxes[1].z = -1500.0f;
    D_8010CA06_game_guys_magic_boxes = 0;
    D_8010C9D0_game_guys_magic_boxes = -260.0f;
    D_8010C9D4_game_guys_magic_boxes = 260.0f;
    D_8010C9D8_game_guys_magic_boxes = 0;
    D_8010C9D9_game_guys_magic_boxes = 0;
    D_8010C1E0_game_guys_magic_boxes = 1.0f;
    D_8010C1E4_game_guys_magic_boxes = 1.0f;
    for (i = 0; i < 3; i++) {
        D_8010C9DB_game_guys_magic_boxes[i][0] = func_801059BC_game_guys_magic_boxes(2.0f);
        if (D_8010C9DB_game_guys_magic_boxes[i][0] == 0) {
            D_8010C9DB_game_guys_magic_boxes[i][1] = 1;
        } else {
            D_8010C9DB_game_guys_magic_boxes[i][1] = 0;
        }
    }
    if (D_8010C753_game_guys_magic_boxes[0] == 0) {
        D_8010C9E1_game_guys_magic_boxes = 0;
    } else if (D_8010C753_game_guys_magic_boxes[0] == 1) {
        D_8010CA04_game_guys_magic_boxes = func_801059BC_game_guys_magic_boxes(3.0f);
        if (D_8010C753_game_guys_magic_boxes[1] != 0) {
            D_8010CA04_game_guys_magic_boxes = func_801059BC_game_guys_magic_boxes(D_8010C753_game_guys_magic_boxes[1]);
            if (D_8010CA04_game_guys_magic_boxes <= 0) {
                D_8010CA04_game_guys_magic_boxes = 0;
            }
        }
        for (i = 0; i <= D_8010CA04_game_guys_magic_boxes; i++) {
            D_8010C9E3_game_guys_magic_boxes[i] = func_801059BC_game_guys_magic_boxes(2.0f);
        }
        D_8010C9E6_game_guys_magic_boxes = 1;
        for (i = 0; i <= D_8010CA04_game_guys_magic_boxes; i++) {
            if (D_8010C9DB_game_guys_magic_boxes[i][D_8010C9E3_game_guys_magic_boxes[i]] == 0) {
                D_8010C5D0_game_guys_magic_boxes[i] = 0;
                D_8010C9E6_game_guys_magic_boxes = 0;
            } else {
                D_8010C5D0_game_guys_magic_boxes[i] = 1;
            }
        }
        if (D_8010C9E6_game_guys_magic_boxes == 0) {
            D_8010CA02_game_guys_magic_boxes = 0;
        } else {
            D_8010CA02_game_guys_magic_boxes = D_8010C756_game_guys_magic_boxes * ((D_8010CA04_game_guys_magic_boxes + 1) << 1);
        }
    }
    D_8010C9E7_game_guys_magic_boxes = 0;
    D_8010C9E8_game_guys_magic_boxes = 0;
}

void func_80105FB4_game_guys_magic_boxes(omObjData *object) {
    GameGuysMagicBoxesCharSprites charSprites;
    u8 chr;
    u8 i;

    chr = GwPlayer[D_8010C750_game_guys_magic_boxes].chr;
    charSprites = D_8010C270_game_guys_magic_boxes;
    func_80109C98_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 0x650000, 0, 0x4000);
    func_80109CFC_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 1000, 0x100, 0, 0, 320, 240, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C780_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 0x650001, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7A0_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0x650002, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7BC_game_guys_magic_boxes, 0);
    func_80109C98_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0x650003, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 800, 0x100, 0, 0, 320, 186, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C7D8_game_guys_magic_boxes, 0);
    func_80109C98_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 0x650004, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 800, 0x100, 242, 16, 54, 54, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C838_game_guys_magic_boxes, 1);
    for (i = 0; i < 3; i++) {
        func_80109C98_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][0], 0x21002A, 0, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][0], 99, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][0], 0);
        func_80109C98_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][1], 0x21002B, 0, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][1], 100, 0x100, i * 16 + 24, 32, 16,
                                            16, 0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[i][1], 1);
    }
    func_80109D3C_game_guys_magic_boxes(&D_8010C858_game_guys_magic_boxes[0][0], 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 0x21001A, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 100, 0x100, 24, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C900_game_guys_magic_boxes, 1);
    func_80109C98_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 0x21001B, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 100, 0x100, 36, 16, 12, 12, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C91C_game_guys_magic_boxes, 1);
    for (i = 0; i < 3; i++) {
        func_80109C98_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 0x31, 1, 0);
        func_80109CFC_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 100, 0x100, i * 12 + 48, 16, 12, 12,
                                            0.0f, 1.0f, 1.0f);
        func_80109D3C_game_guys_magic_boxes(&D_8010C938_game_guys_magic_boxes[i], 1);
    }
    func_80109C98_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, charSprites.ids[chr] | 0x210000, 0, 0);
    func_80109CFC_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 100, 0x100, 55, 70, 46, 46, 0.0f, 1.0f,
                                        1.0f);
    func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 0);
    object->func = func_80108D88_game_guys_magic_boxes;
}

void func_80106558_game_guys_magic_boxes(omObjData *object) {
    object->model[0] = func_8000B108_main(0x650006, 0x2B9);
    omSetTra(object, 330.0f, -400.0f, -1000.0f);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    object->model[1] = Hu3DModelLink(object->model[0]);
    Hu3DModelPosSet(object->model[1], 460.0f, -400.0f, -1000.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->model[2] = func_8000B108_main(0x650007, 0x2B9);
    object->model[3] = Hu3DModelLink(object->model[2]);
    Hu3DModelPosSet(object->model[2], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[2], 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(object->model[3], 460.0f, -400.0f, -999.0f);
    Hu3DModelRotSet(object->model[3], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[3], 1.0f, 1.0f, 1.0f);
    object->func = func_801090F0_game_guys_magic_boxes;
}

void func_801066F8_game_guys_magic_boxes(omObjData *object) {
    object->model[0] = func_8000B108_main(0xA0063, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, 0.0f, 0.0f, -150.0f);
    omSetRot(object, -10.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0xA0063);
    func_8000B460_main(object, 1, 0xA0068);
    func_8000B460_main(object, 2, 0xA006C);
    D_8010C9CA_game_guys_magic_boxes = 0;
    object->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], 0.0f, 0.0f, -150.0f);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = func_8010935C_game_guys_magic_boxes;
}

void func_80106828_game_guys_magic_boxes(omObjData *object) {
    void *data;
    s16 anim;

    object->model[0] = func_8000B108_main(0xA0000, 0x2A9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0xA0001);
    func_8000B460_main(object, 1, 0xA000A);
    func_8000B460_main(object, 2, 0xA000B);
    func_8000B460_main(object, 3, 0xA001F);
    func_8000B460_main(object, 4, 0xA0020);
    data = DataRead(0xA002B);
    anim = Hu3DAnimCreate(Hu3DData[object->model[0]].hmf, data, 0, "c160n_0_DEF");
    DataClose(data);
    Hu3DModelRemakeStatic(object->model[0]);
    func_8001C514_main(object->model[0]);
    func_80032FC0_main(anim, 1, 0);
    Hu3DAnimBankSet(anim, 0);
    D_8010C9C8_game_guys_magic_boxes = 1;
    object->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], -150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(object->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = func_8010942C_game_guys_magic_boxes;
}

void func_80106A2C_game_guys_magic_boxes(omObjData *object) {
    D_8010CA10_game_guys_magic_boxes = object->model[0] = func_8000B108_main(0x650009, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0x65000A);
    D_8010CA12_game_guys_magic_boxes = object->model[1] = func_8000B108_main(0x650008, 0x2B9);
    Hu3DModelPosSet(object->model[1], D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
                    D_8010C9B0_game_guys_magic_boxes[0].z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = func_80109600_game_guys_magic_boxes;
}

void func_80106B50_game_guys_magic_boxes(omObjData *object) {
    object->model[0] = func_8000B108_main(0xA00EE, 0x2B9);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0xA00EE);
    func_8000B460_main(object, 1, 0xA00F4);
    func_8000B460_main(object, 2, 0xA00F5);
    func_8000B460_main(object, 3, 0xA00FD);
    func_8000B460_main(object, 4, 0xA00FE);
    D_8010C9C9_game_guys_magic_boxes = 1;
    object->model[1] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(object->model[1], 150.0f, -700.0f, -1500.0f);
    Hu3DModelRotSet(object->model[1], -15.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = func_80109658_game_guys_magic_boxes;
}

void func_80106CB8_game_guys_magic_boxes(omObjData *object) {
    object->model[0] = Hu3DModelLink(D_8010CA10_game_guys_magic_boxes);
    Hu3DMotionSpeedSet(object->model[0], 1.0f);
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    omSetRot(object, 0.0f, 0.0f, 0.0f);
    omSetSca(object, 1.0f, 1.0f, 1.0f);
    func_8000B460_main(object, 0, 0x65000A);
    object->model[1] = Hu3DModelLink(D_8010CA12_game_guys_magic_boxes);
    Hu3DModelPosSet(object->model[1], D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
                    D_8010C9B0_game_guys_magic_boxes[1].z);
    Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(object->model[1], 1.0f, 1.0f, 1.0f);
    object->func = func_8010982C_game_guys_magic_boxes;
}

void func_80106DC4_game_guys_magic_boxes(omObjData *object) {
    switch (D_8010C9E8_game_guys_magic_boxes) {
        case 0:
            D_8010C1EE_game_guys_magic_boxes = func_8010AC18_game_guys_magic_boxes();
            if (D_8010C1EE_game_guys_magic_boxes == 1) {
                D_8010C9E8_game_guys_magic_boxes = 1;
            }
            break;
        case 1:
            D_8010C774_game_guys_magic_boxes = omAddPrcObj(func_80107020_game_guys_magic_boxes, 0x3F00, 0x800, 0);
            D_8010C9E8_game_guys_magic_boxes = 2;
            break;
        case 2:
            if (D_8010CA0E_game_guys_magic_boxes == 1) {
                D_8010C9E8_game_guys_magic_boxes = 3;
                D_8010CA0E_game_guys_magic_boxes = 0;
                omDelPrcObj(D_8010C774_game_guys_magic_boxes);
            }
            break;
        case 3:
            func_801071B8_game_guys_magic_boxes();
            break;
        case 4:
            func_80107834_game_guys_magic_boxes();
            break;
        case 5:
            D_8010C778_game_guys_magic_boxes = omAddPrcObj(func_80107A3C_game_guys_magic_boxes, 0x3F00, 0x800, 0);
            D_8010C9E8_game_guys_magic_boxes = 6;
            break;
        case 6:
            if (D_8010CA0E_game_guys_magic_boxes == 1) {
                D_8010C9E8_game_guys_magic_boxes = 7;
                D_8010CA0E_game_guys_magic_boxes = 0;
                omDelPrcObj(D_8010C778_game_guys_magic_boxes);
            }
            break;
        case 7:
            func_80107AE0_game_guys_magic_boxes();
            break;
        case 8:
            func_80107B64_game_guys_magic_boxes();
            break;
        case 9:
            func_80108294_game_guys_magic_boxes();
            break;
        case 10:
            func_80108498_game_guys_magic_boxes();
            break;
        case 11:
            func_8010861C_game_guys_magic_boxes();
            break;
        case 12:
            D_8010C77C_game_guys_magic_boxes = omAddPrcObj(func_80108914_game_guys_magic_boxes, 0x3F00, 0x800, 0);
            D_8010C9E8_game_guys_magic_boxes = 13;
            break;
        case 13:
            if (D_8010CA0E_game_guys_magic_boxes == 1) {
                D_8010C9E8_game_guys_magic_boxes = 14;
                D_8010CA0E_game_guys_magic_boxes = 0;
                omDelPrcObj(D_8010C77C_game_guys_magic_boxes);
            } else if (D_8010CA0E_game_guys_magic_boxes == 2) {
                HuAudSeqFadeOut(14);
                D_8010C9E8_game_guys_magic_boxes = 15;
                D_8010CA0E_game_guys_magic_boxes = 0;
                omDelPrcObj(D_8010C77C_game_guys_magic_boxes);
            }
            break;
        case 14:
            func_80108AF8_game_guys_magic_boxes();
            break;
        case 15:
            func_80108C04_game_guys_magic_boxes();
            break;
        case 16:
            object->func = func_80109884_game_guys_magic_boxes;
            break;
    }
}

#ifdef NON_MATCHING
// Register allocation differs: done/win<<16 swap s2/s3 and the loop test lacks a `move v0, s3`.
void func_80107020_game_guys_magic_boxes(void) {
    u8 done = FALSE;
    s16 win;

    D_8010CA0E_game_guys_magic_boxes = 0;
    win = func_8010A4EC_game_guys_magic_boxes(130, 160, 12);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2C00, -1, -1);
    func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0], D_8010C751_game_guys_magic_boxes[2]);
    HuWinMesSet(win, 0x2C01, -1, -1);
    while (done == FALSE) {
        switch (func_8010A6AC_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0],
                                                    D_8010C751_game_guys_magic_boxes[2], 1, 0)) {
            case 0:
                HuWinMesSet(win, 0x2C02, -1, -1);
                func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0],
                                                    D_8010C751_game_guys_magic_boxes[2]);
                done = TRUE;
                break;
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    HuWinMesSet(win, 0x2C03, -1, -1);
    func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0], D_8010C751_game_guys_magic_boxes[2]);
    func_8010A878_game_guys_magic_boxes(win);
    D_8010CA0E_game_guys_magic_boxes = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80107020_game_guys_magic_boxes);
#endif

void func_801071B8_game_guys_magic_boxes(void) {
    D_8010C9B0_game_guys_magic_boxes[0].y -= D_8010C1F4_game_guys_magic_boxes;
    D_8010C9B0_game_guys_magic_boxes[1].y -= D_8010C1F4_game_guys_magic_boxes;
    D_8010C5D8_game_guys_magic_boxes[0].x = D_8010C9B0_game_guys_magic_boxes[0].x;
    D_8010C5D8_game_guys_magic_boxes[0].y = D_8010C9B0_game_guys_magic_boxes[0].y + 100.0f;
    D_8010C5D8_game_guys_magic_boxes[0].z = D_8010C9B0_game_guys_magic_boxes[0].z;
    D_8010C5D8_game_guys_magic_boxes[1].x = D_8010C9B0_game_guys_magic_boxes[1].x;
    D_8010C5D8_game_guys_magic_boxes[1].y = D_8010C9B0_game_guys_magic_boxes[1].y + 100.0f;
    D_8010C5D8_game_guys_magic_boxes[1].z = D_8010C9B0_game_guys_magic_boxes[1].z;
    Hu3D3Dto2D(0, &D_8010C5D8_game_guys_magic_boxes[0], &D_8010C5F0_game_guys_magic_boxes[0]);
    Hu3D3Dto2D(0, &D_8010C5D8_game_guys_magic_boxes[1], &D_8010C5F0_game_guys_magic_boxes[1]);

    switch (D_8010C1EF_game_guys_magic_boxes) {
        case 0:
            D_8010C5D4_game_guys_magic_boxes = 0;
            D_8010C5D6_game_guys_magic_boxes = 0;
            D_8010C9D9_game_guys_magic_boxes = 1;
            D_8010C1EF_game_guys_magic_boxes++;
            break;
        case 1:
            if (D_8010C5D6_game_guys_magic_boxes >= 0x80) {
                D_8010C1F4_game_guys_magic_boxes = 8.0f;
                D_8010CA06_game_guys_magic_boxes = 0;
            } else {
                D_8010C5D6_game_guys_magic_boxes += 8;
            }
            HuSprTPLvlSet(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C5D6_game_guys_magic_boxes);
            if (D_8010C9B0_game_guys_magic_boxes[0].y == -128.0f) {
                HuAudFXPlay(0x535);
            }
            if (D_8010C9B0_game_guys_magic_boxes[0].y <= -450.0f) {
                HuAudFXPlay(0x531);
                HuAudFXPlay(0x530);
                D_8010C1EF_game_guys_magic_boxes++;
            }
            break;
        case 2:
            D_8010C1F4_game_guys_magic_boxes -= 0.4f;
            if (D_8010C1F4_game_guys_magic_boxes < 0.0f) {
                omVibrate(D_8010C750_game_guys_magic_boxes, 2, 3, 10);
                D_8010C1F4_game_guys_magic_boxes = 0.0f;
                D_8010C1EF_game_guys_magic_boxes++;
            }
            break;
        case 3:
            if (D_8010C5D6_game_guys_magic_boxes == 0) {
                D_8010C1EF_game_guys_magic_boxes = 4;
            } else {
                D_8010C5D6_game_guys_magic_boxes -= 8;
            }
            HuSprTPLvlSet(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C5D6_game_guys_magic_boxes);
            break;
        case 4:
            if (D_8010C9E2_game_guys_magic_boxes != 0) {
                HuAudFXPlay(0x531);
                HuAudFXPlay(0x530);
            }
            HuAudFXPlay(0x52E);
            Hu3DMotionSpeedSet(D_8010C768_game_guys_magic_boxes->model[0], -1.2f);
            Hu3DMotionSpeedSet(D_8010C770_game_guys_magic_boxes->model[0], -1.2f);
            D_8010C1EF_game_guys_magic_boxes = 5;
            D_8010C9D9_game_guys_magic_boxes = 0;
            break;
        case 5:
            if (D_8010C1F0_game_guys_magic_boxes >= 13) {
                D_8010C9C8_game_guys_magic_boxes = 0;
                if (D_8010C9E7_game_guys_magic_boxes == 0) {
                    D_8010C9C9_game_guys_magic_boxes = 0;
                }
            } else {
                D_8010C1F0_game_guys_magic_boxes++;
            }
            if (Hu3DData[D_8010C768_game_guys_magic_boxes->model[0]].motTime < 0.0f) {
                Hu3DMotionSpeedSet(D_8010C768_game_guys_magic_boxes->model[0], 0.0f);
                D_8010C1EF_game_guys_magic_boxes = 6;
            }
            if (Hu3DData[D_8010C770_game_guys_magic_boxes->model[0]].motTime < 0.0f) {
                Hu3DMotionSpeedSet(D_8010C770_game_guys_magic_boxes->model[0], 0.0f);
                D_8010C1EF_game_guys_magic_boxes = 6;
            }
            break;
        case 6:
            Hu3DModelCameraSet(D_8010C76C_game_guys_magic_boxes->model[0], 0);
            Hu3DModelCameraSet(D_8010C764_game_guys_magic_boxes->model[0], 0);
            D_8010C1F0_game_guys_magic_boxes = 0;
            D_8010C1EF_game_guys_magic_boxes = 4;
            D_8010C1F4_game_guys_magic_boxes = 0.0f;
            Hu3DMotionSpeedSet(D_8010C768_game_guys_magic_boxes->model[0], 0.0f);
            Hu3DMotionSpeedSet(D_8010C770_game_guys_magic_boxes->model[0], 0.0f);
            D_8010C9CA_game_guys_magic_boxes = 1;
            D_8010C9E8_game_guys_magic_boxes = 4;
            break;
    }

    if (D_8010C1EF_game_guys_magic_boxes < 4) {
        func_8010A388_game_guys_magic_boxes(D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][0].x,
                                            D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][0].y, 50);
        func_8010A388_game_guys_magic_boxes(D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][1].x,
                                            D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][1].y, 50);
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][0].x = D_8010C5F0_game_guys_magic_boxes[0].x;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][1].x = D_8010C5F0_game_guys_magic_boxes[1].x;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][0].y = D_8010C5F0_game_guys_magic_boxes[0].y;
        D_8010C600_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes][1].y = D_8010C5F0_game_guys_magic_boxes[1].y;
        func_8010A1B0_game_guys_magic_boxes(D_8010C5F0_game_guys_magic_boxes[0].x, D_8010C5F0_game_guys_magic_boxes[0].y,
                                            50);
        func_8010A1B0_game_guys_magic_boxes(D_8010C5F0_game_guys_magic_boxes[1].x, D_8010C5F0_game_guys_magic_boxes[1].y,
                                            50);
        D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 =
            D_8010C9F4_game_guys_magic_boxes[D_8010CA00_game_guys_magic_boxes];
        D_8010CA00_game_guys_magic_boxes = (u8)(D_8010CA00_game_guys_magic_boxes + 1) % 3;
    }
}

void func_80107834_game_guys_magic_boxes(void) {
    switch (D_8010C1F8_game_guys_magic_boxes) {
        case 10:
            HuAudFXPlay(0x532);
            break;
        case 18:
            D_8010C9D8_game_guys_magic_boxes = 1;
            break;
        case 30:
            if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][0] == 1) {
                D_8010C9B0_game_guys_magic_boxes[0].x = -150.0f;
                D_8010C9B0_game_guys_magic_boxes[1].x = 150.0f;
            } else {
                D_8010C9B0_game_guys_magic_boxes[0].x = 150.0f;
                D_8010C9B0_game_guys_magic_boxes[1].x = -150.0f;
            }
            break;
        case 27:
            HuAudFXPlay(0x52D);
            break;
        case 43:
            D_8010C9CA_game_guys_magic_boxes = 2;
            break;
        case 45:
            Hu3DMotionSpeedSet(D_8010C760_game_guys_magic_boxes->model[0], 0.0f);
            break;
        case 48:
            Hu3DMotionSpeedSet(D_8010C760_game_guys_magic_boxes->model[0], 1.0f);
            break;
        case 91:
            D_8010C9CA_game_guys_magic_boxes = 1;
            break;
        case 94:
            HuAudFXPlay(0x52D);
            Hu3DMotionTimeSet(D_8010C760_game_guys_magic_boxes->model[0], 90.0f);
            Hu3DMotionSpeedSet(D_8010C760_game_guys_magic_boxes->model[0], -1.0f);
            break;
        case 122:
            HuAudFXPlay(0x533);
            D_8010C9D8_game_guys_magic_boxes = 2;
            break;
        case 138:
            D_8010C9CA_game_guys_magic_boxes = 0;
            break;
        case 140:
            Hu3DMotionSpeedSet(D_8010C760_game_guys_magic_boxes->model[0], 1.0f);
            D_8010C7FE_game_guys_magic_boxes = -58;
            D_8010C81E_game_guys_magic_boxes = 250;
            D_8010C1F8_game_guys_magic_boxes = 0;
            D_8010C9E8_game_guys_magic_boxes = 5;
            break;
        // Empty cases; needed for the jump table.
        case 11:
        case 12:
            break;
    }
    D_8010C1F8_game_guys_magic_boxes++;
}

void func_80107A3C_game_guys_magic_boxes(void) {
    s16 win;

    D_8010CA0E_game_guys_magic_boxes = 0;
    win = func_8010A4EC_game_guys_magic_boxes(130, 160, 12);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2C04, -1, -1);
    func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0], D_8010C751_game_guys_magic_boxes[2]);
    func_8010A878_game_guys_magic_boxes(win);
    D_8010CA0E_game_guys_magic_boxes = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

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

void func_80107B64_game_guys_magic_boxes(void) {
    u8 dir = 0;
    s32 confirm = FALSE;
    u16 buttons;

    switch (D_8010C1FC_game_guys_magic_boxes) {
        case 0:
            GMesCreate(26, 10, 156, 56);
            D_8010C9E1_game_guys_magic_boxes = 0;
            D_8010C208_game_guys_magic_boxes = 0;
            D_8010C1FC_game_guys_magic_boxes = 10;
            break;
        case 10:
            D_8010C990_game_guys_magic_boxes.x = 55;
            D_8010C990_game_guys_magic_boxes.scaleY = D_8010C204_game_guys_magic_boxes;
            D_8010C990_game_guys_magic_boxes.scaleX = D_8010C204_game_guys_magic_boxes;
            if (D_8010C204_game_guys_magic_boxes < 1.0f) {
                D_8010C204_game_guys_magic_boxes += 0.25f;
            } else {
                D_8010C1FC_game_guys_magic_boxes = 1;
            }
            func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
            if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 0) {
                if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
                    D_8010C1E0_game_guys_magic_boxes -= 0.05f;
                }
                if (D_8010C1E4_game_guys_magic_boxes < 1.1f) {
                    D_8010C1E4_game_guys_magic_boxes += 0.05f;
                }
            } else {
                if (D_8010C1E0_game_guys_magic_boxes < 1.1f) {
                    D_8010C1E0_game_guys_magic_boxes += 0.05f;
                }
                if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
                    D_8010C1E4_game_guys_magic_boxes -= 0.05f;
                }
            }
            omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
                     D_8010C1E0_game_guys_magic_boxes);
            Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                              D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
            omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
                     D_8010C1E4_game_guys_magic_boxes);
            Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                              D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
            break;
        case 1:
            if (D_8010C751_game_guys_magic_boxes[2] == 0) {
                if (D_800CBB6E_main[D_8010C751_game_guys_magic_boxes[0]] > 64) {
                    dir = 1;
                }
                if (D_800CBB6E_main[D_8010C751_game_guys_magic_boxes[0]] < -64) {
                    dir = 2;
                }
                buttons = D_800CDA7C_main[D_8010C751_game_guys_magic_boxes[0]];
                if (buttons & A_BUTTON) {
                    confirm = TRUE;
                }
                if (dir == 1) {
                    D_8010C9E1_game_guys_magic_boxes = 1;
                } else if (dir == 2) {
                    D_8010C9E1_game_guys_magic_boxes = 0;
                }
            } else if (D_8010C751_game_guys_magic_boxes[2] == 1) {
                if (D_8010C202_game_guys_magic_boxes >= 35) {
                    if (D_8010C9E3_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes] !=
                        D_8010C9E1_game_guys_magic_boxes) {
                        D_8010C9E1_game_guys_magic_boxes = 1;
                        D_8010C202_game_guys_magic_boxes = 0;
                    } else {
                        D_8010C202_game_guys_magic_boxes = 0;
                        confirm = TRUE;
                    }
                } else {
                    D_8010C202_game_guys_magic_boxes++;
                }
            }
            if (D_8010C208_game_guys_magic_boxes != D_8010C9E1_game_guys_magic_boxes) {
                if (D_8010C9E1_game_guys_magic_boxes == 1) {
                    HuAudFXPlay(1);
                    D_8010C990_game_guys_magic_boxes.x = 140;
                } else if (D_8010C9E1_game_guys_magic_boxes == 0) {
                    HuAudFXPlay(1);
                    D_8010C990_game_guys_magic_boxes.x = 55;
                }
                D_8010C208_game_guys_magic_boxes = D_8010C9E1_game_guys_magic_boxes;
            }
            if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 0) {
                if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
                    D_8010C1E0_game_guys_magic_boxes -= 0.05f;
                }
                if (D_8010C1E4_game_guys_magic_boxes < 1.1f) {
                    D_8010C1E4_game_guys_magic_boxes += 0.05f;
                }
            } else {
                if (D_8010C1E0_game_guys_magic_boxes < 1.1f) {
                    D_8010C1E0_game_guys_magic_boxes += 0.05f;
                }
                if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
                    D_8010C1E4_game_guys_magic_boxes -= 0.05f;
                }
            }
            omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
                     D_8010C1E0_game_guys_magic_boxes);
            Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                              D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
            omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
                     D_8010C1E4_game_guys_magic_boxes);
            Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                              D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
            func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
            if (D_8010C1FE_game_guys_magic_boxes >= 30) {
                D_8010C200_game_guys_magic_boxes--;
                D_8010C1FE_game_guys_magic_boxes = 0;
                func_8003F578_main(D_8010C200_game_guys_magic_boxes);
            } else {
                D_8010C1FE_game_guys_magic_boxes++;
            }
            if ((confirm == TRUE) | (D_8010C200_game_guys_magic_boxes < 1)) {
                D_8010C204_game_guys_magic_boxes = 0.0f;
                D_8010C1FC_game_guys_magic_boxes = 2;
            }
            break;
        case 2:
            if (D_8010C9DB_game_guys_magic_boxes[D_8010C9E7_game_guys_magic_boxes][D_8010C9E1_game_guys_magic_boxes] == 1) {
                D_8010C9E2_game_guys_magic_boxes = 1;
            } else {
                D_8010C9E2_game_guys_magic_boxes = 0;
            }
            HuAudFXPlay(3);
            D_800D6A58_main = 1;
            func_8003F5C0_main();
            D_8010C9E8_game_guys_magic_boxes = 9;
            D_8010C1FC_game_guys_magic_boxes = 0;
            D_8010C1FE_game_guys_magic_boxes = 0;
            D_8010C200_game_guys_magic_boxes = 10;
            D_8010C204_game_guys_magic_boxes = 0.0f;
            break;
    }
}

void func_80108294_game_guys_magic_boxes(void) {
    if (D_8010C20C_game_guys_magic_boxes > 0.0f) {
        D_8010C20C_game_guys_magic_boxes -= 0.25f;
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 1);
    } else {
        func_80109D3C_game_guys_magic_boxes(&D_8010C990_game_guys_magic_boxes, 0);
    }
    D_8010C990_game_guys_magic_boxes.scaleX = D_8010C990_game_guys_magic_boxes.scaleY =
        D_8010C20C_game_guys_magic_boxes;
    if (D_8010C1E0_game_guys_magic_boxes > 1.0f) {
        D_8010C1E0_game_guys_magic_boxes -= 0.05f;
    }
    if (D_8010C1E4_game_guys_magic_boxes > 1.0f) {
        D_8010C1E4_game_guys_magic_boxes -= 0.05f;
    }
    omSetSca(D_8010C768_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes,
             D_8010C1E0_game_guys_magic_boxes);
    Hu3DModelScaleSet(D_8010C768_game_guys_magic_boxes->model[1], D_8010C1E0_game_guys_magic_boxes,
                      D_8010C1E0_game_guys_magic_boxes, D_8010C1E0_game_guys_magic_boxes);
    omSetSca(D_8010C770_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes,
             D_8010C1E4_game_guys_magic_boxes);
    Hu3DModelScaleSet(D_8010C770_game_guys_magic_boxes->model[1], D_8010C1E4_game_guys_magic_boxes,
                      D_8010C1E4_game_guys_magic_boxes, D_8010C1E4_game_guys_magic_boxes);
    if (D_8010C20A_game_guys_magic_boxes == 0) {
        func_8004A670_main(120);
        GMesCreate(20);
        D_8010C20A_game_guys_magic_boxes = 1;
    } else if (D_8010C20A_game_guys_magic_boxes == 1) {
        if (GMesStatGet() == GMES_STAT_NONE) {
            D_8010C9E8_game_guys_magic_boxes = 10;
            D_8010C20C_game_guys_magic_boxes = 1.0f;
            D_8010C20A_game_guys_magic_boxes = 0;
            D_8010C990_game_guys_magic_boxes.x = 55;
        }
    }
}

void func_80108498_game_guys_magic_boxes(void) {
    u8 *pixels;
    s32 i;

    switch (D_8010C210_game_guys_magic_boxes) {
        case 0:
            func_8004A5C4_main(0x49);
            GMesClose();
            D_8010C9D9_game_guys_magic_boxes = 1;
            D_8010C212_game_guys_magic_boxes = 0;
            if (D_8010C9E1_game_guys_magic_boxes == 1) {
                D_8010C214_game_guys_magic_boxes = 203;
            } else {
                D_8010C214_game_guys_magic_boxes = 117;
            }
            D_8010C216_game_guys_magic_boxes = 120;
            pixels = D_8010C9F4_game_guys_magic_boxes[0];
            for (i = 0; i < 0x9600; i++) {
                *pixels++ = 0;
            }
            D_8010CA00_game_guys_magic_boxes = 0;
            func_8010A1B0_game_guys_magic_boxes(D_8010C214_game_guys_magic_boxes, D_8010C216_game_guys_magic_boxes, 50);
            D_8010C9EC_game_guys_magic_boxes->unk_84->unk00->unk00 = D_8010C9F4_game_guys_magic_boxes[0];
            D_8010C210_game_guys_magic_boxes = 1;
            break;
        case 1:
            if (D_8010C212_game_guys_magic_boxes >= 0x80) {
                D_8010C210_game_guys_magic_boxes = 2;
            } else {
                D_8010C212_game_guys_magic_boxes += 8;
            }
            HuSprTPLvlSet(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C212_game_guys_magic_boxes);
            break;
        case 2:
            D_8010C210_game_guys_magic_boxes = 0;
            D_8010C214_game_guys_magic_boxes = 0;
            D_8010C216_game_guys_magic_boxes = 0;
            D_8010C9E8_game_guys_magic_boxes = 11;
            break;
    }
}

void func_8010861C_game_guys_magic_boxes(void) {
    switch (D_8010C218_game_guys_magic_boxes) {
        case 0:
            if (D_8010C21A_game_guys_magic_boxes >= 30) {
                func_8004A7C4_main(1);
                D_8010C21A_game_guys_magic_boxes = 0;
                D_8010C218_game_guys_magic_boxes = 1;
            } else {
                D_8010C21A_game_guys_magic_boxes++;
            }
            break;
        case 1:
            HuAudFXPlay(0x52F);
            Hu3DModelCameraSet(D_8010C76C_game_guys_magic_boxes->model[0], 1);
            Hu3DModelCameraSet(D_8010C764_game_guys_magic_boxes->model[0], 1);
            Hu3DMotionSpeedSet(D_8010C768_game_guys_magic_boxes->model[0], 1.0f);
            Hu3DMotionSpeedSet(D_8010C770_game_guys_magic_boxes->model[0], 1.0f);
            D_8010C9C8_game_guys_magic_boxes = 2;
            D_8010C9C9_game_guys_magic_boxes = 2;
            D_8010C218_game_guys_magic_boxes = 2;
            if (D_8010C9E2_game_guys_magic_boxes == 1) {
                if (D_8010C9E7_game_guys_magic_boxes == 2) {
                    omVibrate(D_8010C750_game_guys_magic_boxes, 30, 0, 30);
                } else {
                    omVibrate(D_8010C750_game_guys_magic_boxes, 10, 0, 10);
                }
            } else {
                omVibrate(D_8010C750_game_guys_magic_boxes, 2, 2, 20);
            }
            break;
        case 2:
            if (D_8010C21A_game_guys_magic_boxes >= 45) {
                if (D_8010C9E2_game_guys_magic_boxes == 0) {
                    HuAudFXPlay(0x534);
                } else {
                    HuAudFXPlay(0x535);
                }
                D_8010C21A_game_guys_magic_boxes = 0;
                D_8010C218_game_guys_magic_boxes = 3;
            } else {
                D_8010C21A_game_guys_magic_boxes++;
            }
            if (D_8010C21A_game_guys_magic_boxes == 23) {
                if (D_8010C9E2_game_guys_magic_boxes == 1) {
                    D_8010C9C8_game_guys_magic_boxes = 4;
                    D_8010C9C9_game_guys_magic_boxes = 4;
                } else {
                    D_8010C9C8_game_guys_magic_boxes = 3;
                    D_8010C9C9_game_guys_magic_boxes = 3;
                }
            }
            if (D_8010C21A_game_guys_magic_boxes == 25) {
                if (D_8010C9E2_game_guys_magic_boxes == 1) {
                    HuAudFXPlay(0x531);
                } else {
                    HuAudFXPlay(0x530);
                }
            }
            break;
        case 3:
            if (D_8010C9E2_game_guys_magic_boxes == 1 && D_8010C9E7_game_guys_magic_boxes != 2) {
                func_8004A5C4_main(0x70);
                D_8010C9E8_game_guys_magic_boxes = 12;
                D_8010C218_game_guys_magic_boxes = 0;
                D_8010C21A_game_guys_magic_boxes = 0;
            } else if (D_8010C9E2_game_guys_magic_boxes == 0 || D_8010C9E7_game_guys_magic_boxes == 2) {
                D_8010C9E8_game_guys_magic_boxes = 15;
            }
            break;
    }
}

#ifdef NON_MATCHING
// Regalloc: done/choice/win<<16 land in different s-registers, and the done tests use andi instead of move.
void func_80108914_game_guys_magic_boxes(void) {
    u8 done = FALSE;
    s16 choice = 0;
    s16 win;

    HuPrcSleep(50);
    func_8004A650_main(10);
    D_8010CA0E_game_guys_magic_boxes = 0;
    win = func_8010A4EC_game_guys_magic_boxes(130, 160, 12);
    HuAudFXPlay(0x11D);
    func_80060C14_main(win, 1);
    HuWinMesSet(win, 0x2C05, -1, -1);
    func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0], D_8010C751_game_guys_magic_boxes[2]);
    HuWinMesSet(win, 0x2C06, -1, -1);
    if (D_8010CA04_game_guys_magic_boxes != D_8010C9E7_game_guys_magic_boxes) {
        D_8010C9DA_game_guys_magic_boxes = 0;
    } else {
        D_8010C9DA_game_guys_magic_boxes = 1;
    }
    while (done == FALSE) {
        choice = func_8010A6AC_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0],
                                                     D_8010C751_game_guys_magic_boxes[2],
                                                     D_8010C9DA_game_guys_magic_boxes, 1);
        switch (choice) {
            case 0:
                HuWinMesSet(win, 0x2C07, -1, -1);
                func_8010A560_game_guys_magic_boxes(win, D_8010C751_game_guys_magic_boxes[0],
                                                    D_8010C751_game_guys_magic_boxes[2]);
                done = TRUE;
                break;
            case 1:
                done = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    func_8010A878_game_guys_magic_boxes(win);
    if (choice == 0) {
        D_8010CA0E_game_guys_magic_boxes = 1;
    } else if (choice == 1) {
        D_8010CA0E_game_guys_magic_boxes = 2;
    }
    while (TRUE) {
        HuPrcVSleep();
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80108914_game_guys_magic_boxes);
#endif

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
            HuSprTPLvlSet(D_8010C9F0_game_guys_magic_boxes, 0, D_8010C21E_game_guys_magic_boxes);
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
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
             D_8010C9B0_game_guys_magic_boxes[0].z);
    Hu3DModelPosSet(object->model[1], D_8010C9B0_game_guys_magic_boxes[0].x, D_8010C9B0_game_guys_magic_boxes[0].y,
                    D_8010C9B0_game_guys_magic_boxes[0].z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80109658_game_guys_magic_boxes);

void func_8010982C_game_guys_magic_boxes(omObjData *object) {
    omSetTra(object, D_8010C9B0_game_guys_magic_boxes[1].x, D_8010C9B0_game_guys_magic_boxes[1].y,
             D_8010C9B0_game_guys_magic_boxes[1].z);
    Hu3DModelPosSet(object->model[1], D_8010C9B0_game_guys_magic_boxes[1].x,
                    D_8010C9B0_game_guys_magic_boxes[1].y, D_8010C9B0_game_guys_magic_boxes[1].z);
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
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
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
    sprite->unk_00 = espEntry(func_8000B838_main(spriteIndex), 0, numSlots);
    espAttrSet(sprite->unk_00, visibility);
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
