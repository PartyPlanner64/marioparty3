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
extern f32 D_8010C1E0_game_guys_magic_boxes;
extern f32 D_8010C1E4_game_guys_magic_boxes;
extern u8 D_8010C5D0_game_guys_magic_boxes[];
extern u8 D_8010C750_game_guys_magic_boxes;
extern u8 D_8010C753_game_guys_magic_boxes[2];
extern s16 D_8010C756_game_guys_magic_boxes;
extern f32 D_8010C9D0_game_guys_magic_boxes;
extern f32 D_8010C9D4_game_guys_magic_boxes;
extern u8 D_8010C9CA_game_guys_magic_boxes;
extern u8 D_8010C9D8_game_guys_magic_boxes;
extern u8 D_8010C9D9_game_guys_magic_boxes;
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

void func_80105A28_game_guys_magic_boxes(void);
void func_80105AC0_game_guys_magic_boxes(void);
void func_80105AC8_game_guys_magic_boxes(void);
void func_80105B44_game_guys_magic_boxes(void);
void func_80105B60_game_guys_magic_boxes(omObjData *object);
void func_80105CCC_game_guys_magic_boxes(void);
void func_80105FB4_game_guys_magic_boxes(omObjData *object);
void func_80106558_game_guys_magic_boxes(omObjData *object);
void func_801066F8_game_guys_magic_boxes(omObjData *object);
void func_80106828_game_guys_magic_boxes(omObjData *object);
void func_80106A2C_game_guys_magic_boxes(omObjData *object);
void func_80106B50_game_guys_magic_boxes(omObjData *object);
void func_80106CB8_game_guys_magic_boxes(omObjData *object);
void func_80106DC4_game_guys_magic_boxes(omObjData *object);
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
void func_8010A8C0_game_guys_magic_boxes(s16 x, s16 y);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_44_game_guys_magic_boxes/308D10", func_80105FB4_game_guys_magic_boxes);

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
