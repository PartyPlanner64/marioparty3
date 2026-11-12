#include "overlays/ovl_11_puddle_paddle/puddle_paddle.h"
#include "gcc/memory.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

typedef struct PuddlePaddlePlayer {
    /* 0x00 */ s16 unk_00; // player index
    /* 0x02 */ char unk_02[2];
    /* 0x04 */ s32 unk_04; // flags
    /* 0x08 */ s8 unk_08;
    /* 0x09 */ char unk_09;
    /* 0x0A */ s16 unk_0A; // current motion
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E; // queued motion
    /* 0x10 */ s8 unk_10;
    /* 0x11 */ s8 unk_11;
    /* 0x12 */ char unk_12[0x36];
    /* 0x48 */ f32 unk_48; // paddle angle offset
    /* 0x4C */ f32 unk_4C; // paddle power
    /* 0x50 */ s16 team;
    /* 0x52 */ s16 unk_52;
    /* 0x54 */ s16 unk_54;
    /* 0x56 */ s16 unk_56; // won
    /* 0x58 */ s16 unk_58;
    /* 0x5A */ char unk_5A[2];
} PuddlePaddlePlayer; // Size 0x5C

typedef struct PuddlePaddleTeam {
    /* 0x00 */ Vec velocity;
    /* 0x0C */ Vec drag;
    /* 0x18 */ f32 unk_18; // boat angle
    /* 0x1C */ f32 power;
    /* 0x20 */ s8 count;
    /* 0x21 */ char unk_21;
    /* 0x22 */ s16 players[2];
    /* 0x26 */ s16 tensSprite;
    /* 0x28 */ s16 onesSprite;
    /* 0x2A */ s16 score;
    /* 0x2C */ s16 unk_2C; // human player
    /* 0x2E */ char unk_2E[0x22];
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ char unk_58[8];
    /* 0x60 */ s16 unk_60;
    /* 0x62 */ s16 unk_62;
} PuddlePaddleTeam; // Size 0x64

typedef struct PuddlePaddlePositions {
    /* 0x00 */ Vec points[2];
} PuddlePaddlePositions; // Size 0x18

typedef struct PuddlePaddleItem {
    /* 0x00 */ s16 type;
    /* 0x02 */ s16 model;
    /* 0x04 */ u8 state;
    /* 0x05 */ char unk_05[3];
    /* 0x08 */ Vec velocity;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ s16 timer;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ s16 unk_1C;
    /* 0x1E */ char unk_1E[2];
    /* 0x20 */ f32 radius;
    /* 0x24 */ f32 spin;
    /* 0x28 */ f32 spinSpeed;
    /* 0x2C */ char unk_2C[8];
} PuddlePaddleItem; // Size 0x34

typedef struct PuddlePaddleGame {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 timer;
    /* 0x08 */ char unk_08[0x30];
    /* 0x38 */ PuddlePaddleItem *items;
    /* 0x3C */ s16 unk_3C; // effect index
    /* 0x3E */ char unk_3E[2];
    /* 0x40 */ s16 unk_40;
    /* 0x42 */ char unk_42[2];
} PuddlePaddleGame; // Size 0x44

extern u8 D_800D6A90_main;

extern PuddlePaddleTeam *D_80111650_puddle_paddle;
extern PuddlePaddlePlayer *D_80111654_puddle_paddle;
extern PuddlePaddleGame *D_80111658_puddle_paddle;

f32 D_80111220_puddle_paddle = 0.0f;
f32 D_80111224_puddle_paddle = 0.0f;
f32 D_80111228_puddle_paddle = 180.0f;
s16 D_8011122C_puddle_paddle = -1;
s16 D_8011122E_puddle_paddle = 0;
s16 D_80111230_puddle_paddle = 0;
s16 D_80111232_puddle_paddle = 0;
s16 D_80111234_puddle_paddle = 0;

const s16 D_80111370_puddle_paddle[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000
};

const s16 D_8011137C_puddle_paddle[] = {
    0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000
};

const s16 D_8011138C_puddle_paddle[] = {
    0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000
};

void func_801059BC_puddle_paddle(void);
void func_80105B94_puddle_paddle(void);
void func_80105C3C_puddle_paddle(omObjData *object);
void func_80105CE0_puddle_paddle(void);
void func_80105DBC_puddle_paddle(omObjData *object);
void func_80106028_puddle_paddle(omObjData *object);
void func_80106064_puddle_paddle(omObjData *object);
void func_80106988_puddle_paddle(omObjData *object);
void func_80106CE4_puddle_paddle(omObjData *object);
void func_801073E4_puddle_paddle(omObjData *object);
void func_801075B8_puddle_paddle(void);
void func_80107638_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_801079D4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80107B2C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010788C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80107588_puddle_paddle(omObjData *object);
void func_80107DB0_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80109804_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1, u8 arg2);
void func_80109BD4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_801091F8_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010981C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_80108E2C_puddle_paddle(s16 index, s16 type, f32 angle, f32 pitch, s16 model);
s16 func_8010910C_puddle_paddle(s16 type);
void func_8010A224_puddle_paddle(void);
void func_80108D10_puddle_paddle(void);
void func_8010A398_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010ABCC_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler);
void func_8010B574_puddle_paddle(void);
void func_80105C84_puddle_paddle(omObjData *object);
void func_80105CBC_puddle_paddle(omObjData *object);
void func_801069FC_puddle_paddle(omObjData *object);

void func_801059A0_puddle_paddle(void) {
    func_801059BC_puddle_paddle();
}

void func_801059BC_puddle_paddle(void) {
    u8 camera;

    func_8001FE20_main(0x32);
    func_800142A0_main(0x30);
    omInitObjMan(0x32, 0);
    func_8004A208_main();
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camera = func_8000B638_main();
    ScissorSet(camera, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camera, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 5000.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_8010B820_puddle_paddle();
    func_80105B94_puddle_paddle();
    omAddObj(0x3E8, 0, 0, -1, func_80105DBC_puddle_paddle);
    omAddObj(0x7D0, 0, 0, -1, func_80105C3C_puddle_paddle);
    func_80045010_main(D_80111370_puddle_paddle, 1);
    func_80045010_main(D_8011137C_puddle_paddle, 1);
    func_80045010_main(D_8011138C_puddle_paddle, 1);
}

void func_80105B94_puddle_paddle(void) {
    D_80111658_puddle_paddle = HuMemAllocTag(sizeof(PuddlePaddleGame), TAG_OVERLAY);
    memset(D_80111658_puddle_paddle, 0, sizeof(PuddlePaddleGame));
    D_80111658_puddle_paddle->items = HuMemAllocTag(16 * sizeof(PuddlePaddleItem), TAG_OVERLAY);
    memset(D_80111658_puddle_paddle->items, 0, 16 * sizeof(PuddlePaddleItem));
    D_80111654_puddle_paddle = HuMemAllocTag(4 * sizeof(PuddlePaddlePlayer), TAG_OVERLAY);
    memset(D_80111654_puddle_paddle, 0, 4 * sizeof(PuddlePaddlePlayer));
    D_80111650_puddle_paddle = HuMemAllocTag(2 * sizeof(PuddlePaddleTeam), TAG_OVERLAY);
    memset(D_80111650_puddle_paddle, 0, 2 * sizeof(PuddlePaddleTeam));
}

void func_80105C3C_puddle_paddle(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = func_80105C84_puddle_paddle;
    }
}

void func_80105C84_puddle_paddle(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = func_80105CBC_puddle_paddle;
    }
}

void func_80105CBC_puddle_paddle(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105CE0_puddle_paddle(void) {
    if (CRot.x > 360.0f) {
        CRot.x -= 360.0f;
    } else if (CRot.x < 0.0f) {
        CRot.x += 360.0f;
    }
    if (CRot.y > 360.0f) {
        CRot.y -= 360.0f;
    } else if (CRot.y < 0.0f) {
        CRot.y += 360.0f;
    }
    func_8010BC14_puddle_paddle(0);
}

void func_80105DBC_puddle_paddle(omObjData *object) {
    s16 i;
    PuddlePaddleTeam *team;

    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    func_8010B8B4_puddle_paddle(NULL, 0, 0, 4);
    func_8010BA04_puddle_paddle(0, 0, 0, func_801075B8_puddle_paddle, 0);
    object->work[1] = 1;
    func_8010B8B4_puddle_paddle(object, (s8)object->work[1], 0, 4);
    D_800EC1C0_minigame[0] = omAddObj(10, 1, 2, -1, func_80106064_puddle_paddle);
    D_800EC1C0_minigame[1] = omAddObj(10, 1, 0, -1, func_80106988_puddle_paddle);
    omSetStatBit(D_800EC1C0_minigame[1], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 4; i++) {
        team = &D_80111650_puddle_paddle[D_80111654_puddle_paddle[i].team = GwPlayer[i].group];
        D_80111654_puddle_paddle[i].unk_10 = team->count;
        team->players[team->count++] = i;
    }
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(300, 11, 42, -1, func_80106CE4_puddle_paddle);
    }
    omAddObj(500, 2, 0, -1, func_801073E4_puddle_paddle);
    D_80111658_puddle_paddle->unk_00 = 1;
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xF, 0, func_801079D4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0x1F, 0, func_80107638_puddle_paddle, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 20);
    object->func = func_80106028_puddle_paddle;
}

void func_80106028_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle((s8)object->work[1]);
    func_80105CE0_puddle_paddle();
    func_8010C16C_puddle_paddle();
    func_8010C664_puddle_paddle();
    func_8010CCF0_puddle_paddle();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_80111398_puddle_paddle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_801113B8_puddle_paddle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_801113C4_puddle_paddle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_801113CC_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", func_80106064_puddle_paddle);

void func_80106958_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(2);
    func_80110714_puddle_paddle(object);
}

void func_80106988_puddle_paddle(omObjData *object) {
    object->model[0] = func_8000B108_main(0x320001, 0x20099);
    Hu3DModelPosSet(object->model[0], 0.0f, 200.0f, 0.0f);
    func_8001C954_main(object->model[0]);
    func_80110714_puddle_paddle(object);
    object->func = func_801069FC_puddle_paddle;
}

void func_801069FC_puddle_paddle(omObjData *object) {
    func_8001E65C_main(object->model[0], sindf(D_80111220_puddle_paddle) * 15.0f, -D_80111224_puddle_paddle, 64, 64);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_80111220_puddle_paddle += 0.5f;
        if (D_80111220_puddle_paddle >= 360.0f) {
            D_80111220_puddle_paddle -= 360.0f;
        }
        D_80111224_puddle_paddle += 0.2f;
        if (D_80111224_puddle_paddle >= 64.0f) {
            D_80111224_puddle_paddle -= 64.0f;
        }
        D_80111228_puddle_paddle += 2.4f;
        if (D_80111228_puddle_paddle >= 360.0f) {
            D_80111228_puddle_paddle -= 360.0f;
        }
    }
    func_80110714_puddle_paddle(object);
}

void func_80106B6C_puddle_paddle(s16 srcModel, s16 dstModel, u16 dstObj) {
    HmfData *dst = Hu3DData[dstModel].hmf;
    HmfData *src = Hu3DData[srcModel].hmf;
    s16 srcObj = 0;
    s16 i, j;

    if (dst->unk80 == (HmfMotionNode *)-1) {
        for (i = 0; i < dst->unk64; i++) {
            HmfSkeletonNode *skel = &dst->unk68[i];

            if (skel->unk00 == dstObj) {
                skel->unk48 = src;
                skel->unk00 = srcObj;
            }
        }
    } else {
        for (i = 0; i < dst->unk16; i++) {
            HmfMotionNode *node = &dst->unk80[i];

            for (j = 0; j < node->unk00; j++) {
                if (node->unk50[j] == dstObj) {
                    node->unk54 = src;
                    node->unk50[j] = srcObj;
                    break;
                }
            }
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_801113D4_puddle_paddle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", D_801113F4_puddle_paddle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", func_80106CE4_puddle_paddle);

const PuddlePaddlePositions D_80111614_puddle_paddle = {
    { { -300.0f, 200.0f, 0.0f }, { 300.0f, 200.0f, 0.0f } }
};

void func_801073AC_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(object->work[1]);
    func_800E4E30_minigame(object);
    func_80110714_puddle_paddle(object);
}

void func_801073E4_puddle_paddle(omObjData *object) {
    s32 flags = 0x99;
    PuddlePaddlePositions positions = D_80111614_puddle_paddle;
    PuddlePaddleSlot *slot;
    s16 i;

    object->work[1] = 7;
    slot = func_8010B8B4_puddle_paddle(object, (s8)object->work[1], 2, 6)->unk_00;
    for (i = 0; i < 2; i++) {
        slot->unk_04[i] = func_8000B108_main(0x320002, flags);
        Hu3DModelPosSet(slot->unk_04[i], positions.points[i].x, positions.points[i].y, positions.points[i].z);
    }
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFF, 0, func_8010A398_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFFF, 0, func_80109BD4_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0x1FFF, 0, func_8010A224_puddle_paddle, 0);
    func_8010BA04_puddle_paddle((s8)object->work[1], 0xFFFF, 0, func_8010ABCC_puddle_paddle, 0);
    object->model[0] = slot->unk_04[0];
    func_80110714_puddle_paddle(object);
    object->func = func_80107588_puddle_paddle;
}

void func_80107588_puddle_paddle(omObjData *object) {
    func_8010BC14_puddle_paddle(object->work[1]);
    func_80110714_puddle_paddle(object);
}

void func_801075B8_puddle_paddle(void) {
    // The original call omits the buffer argument.
    void (*initBuffer)() = (void (*)())func_8010BAA8_puddle_paddle;

    Center.x = 0.0f;
    Center.y = 280.0f;
    Center.z = 102.0f;
    CRot.x = 321.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2970.0f;
    initBuffer(0);
}

void func_80107638_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s16 i;
    s16 score;
    s16 tens, ones;

    for (i = 0; i < 2; i++) {
        score = D_80111650_puddle_paddle[i].score;
        if (score < 100) {
            ones = score % 10;
            tens = score * 0.1f;
            if (tens != 0) {
                func_8010C088_puddle_paddle(D_80111650_puddle_paddle[i].tensSprite, i * 160 + 104, 32);
            } else {
                func_8010C11C_puddle_paddle(D_80111650_puddle_paddle[i].tensSprite);
            }
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].tensSprite].unk_01, 0, tens);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].onesSprite].unk_01, 0, ones);
        } else {
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].tensSprite].unk_01, 0, 9);
            func_80054FF8_main(D_80111664_puddle_paddle[D_80111650_puddle_paddle[i].onesSprite].unk_01, 0, 9);
        }
    }
}

void func_8010788C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    if (handler->unk_04 == 0) {
        D_80111658_puddle_paddle->timer = 900.0f;
        GMesCreate(26, D_80111658_puddle_paddle->timer / 30.0f, 160, 28);
        handler->unk_04 = 1;
    }
    D_80111658_puddle_paddle->timer -= 1.0f;
    func_8003F578_main((s16)((D_80111658_puddle_paddle->timer + 29.0f) * (1.0f / 30.0f)));
    if (D_80111658_puddle_paddle->timer < 0.0f) {
        D_80111658_puddle_paddle->unk_00 = 4;
        HuAudSeqFadeOut(120);
        GMesCreate(16);
        func_8003F5C0_main();
        func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0, 0, func_80107B2C_puddle_paddle, 0);
        func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
    }
}

void func_801079D4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s32 status;

    switch (++handler->unk_1C[0]) {
        case 5:
            HuAudFXPlay(0x374);
            break;
        case 30:
            GMesCreate(5);
            HuAudFXPlay(14);
            break;
        case 50:
            D_8011122E_puddle_paddle = 1;
            break;
        default:
            if (D_8011122E_puddle_paddle == 1 && (status = GMesStatGet()) == 2) {
                func_8010B574_puddle_paddle();
                func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0xF, 0, func_8010788C_puddle_paddle, 0);
                D_80111658_puddle_paddle->unk_00 = status;
                func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            }
            break;
    }
    if (D_80111230_puddle_paddle == 0 && GMesStatGet() != 0) {
        HuAudSeqPlay(0x30);
        D_80111230_puddle_paddle = 1;
    }
}

void func_80107B2C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    s16 won[2];
    s16 i, j;

    if (GMesStatGet() == 0) {
        D_80111232_puddle_paddle = 1;
    }
    if (D_80111232_puddle_paddle == 0) {
        return;
    }
    switch (++handler->unk_1C[0]) {
        case 15:
            won[0] = won[1] = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 2; j++) {
                    if (D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_56 != 0) {
                        func_80109804_puddle_paddle(&D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]], 13, 1);
                        func_8004AC98_main(GwPlayer[D_80111650_puddle_paddle[i].players[j]].chr + 0x290,
                                           D_80111650_puddle_paddle[i].players[j]);
                        D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_58 = -1;
                        D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[j]].unk_0E = -1;
                        won[i] = 1;
                    }
                }
            }
            if (won[0] != 0 && won[1] != 0) {
                HuAudSeqPlay(0x66);
            } else if (won[0] != 0 || won[1] != 0) {
                HuAudSeqPlay(0x65);
            } else {
                HuAudSeqPlay(0x6C);
            }
            break;
        case 140:
            func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0, 0, func_80107DB0_puddle_paddle, 0);
            func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            break;
    }
}

void func_80107DB0_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    switch (handler->unk_04) {
        case 0:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            handler->unk_04 = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_80107E1C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    HmfModel *model = &Hu3DData[slot->unk_04[0]];
    f32 angle, target;

    if (D_80111658_puddle_paddle->unk_00 & 1) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_40 != 0) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_00 & 4) {
        if (handler->unk_1C[0] != 0) {
            return;
        }
        angle = model->rot.y;
        target = 0.0f;
        func_80110BBC_puddle_paddle(&angle, &target);
        if (model->rot.y >= 360.0f) {
            model->rot.y -= 360.0f;
        } else if (model->rot.y < 0.0f) {
            model->rot.y += 360.0f;
        }
        if (ABS(model->rot.y) <= 2.0f) {
            handler->unk_1C[0] = 1;
        }
        if (angle - target > 0.0f) {
            model->rot.y -= 2.0f;
        } else if (angle - target < 0.0f) {
            model->rot.y += 2.0f;
        }
    } else {
        if (handler->unk_0C[0] == 0) {
            handler->unk_0C[0] = 1;
            handler->unk_2C[0] = rand16() % 361;
        }
        angle = model->rot.y;
        target = handler->unk_2C[0];
        func_80110BBC_puddle_paddle(&angle, &target);
        if (ABS(model->rot.y - handler->unk_2C[0]) < 5.0f) {
            handler->unk_0C[0] = 0;
        }
        if (angle - target > 0.0f) {
            model->rot.y -= 1.0f;
        } else if (angle - target < 0.0f) {
            model->rot.y += 1.0f;
        }
    }
}

void func_80108178_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    f32 time;

    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        handler->unk_1C[0] = 0;
    }
    if (handler->unk_04 == 0) {
        handler->unk_1C[0] = 0;
        handler->unk_1C[1] = 10;
        D_80111658_puddle_paddle->unk_40 = 0;
        handler->unk_04 = 1;
    }
    if (D_80111658_puddle_paddle->unk_40 == 0) {
        if (++handler->unk_1C[0] > handler->unk_1C[1]) {
            func_8001C5B4_main(slot->unk_04[0], object->motion[1]);
            Hu3DMotionSpeedSet(slot->unk_04[0], 2.0f);
            Hu3DMotionTimeSet(object->model[0], 0.0f);
            D_80111658_puddle_paddle->unk_40 = 1;
            handler->unk_1C[0] = 0;
            handler->unk_1C[1] = (f32)(rand16() % 61 + 40);
        }
        time = Hu3DData[object->model[0]].motTime;
        if (time >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02) {
            func_8001C5B4_main(slot->unk_04[0], object->motion[0]);
            Hu3DMotionSpeedSet(slot->unk_04[0], 1.0f);
        }
    }
}

// NON_MATCHING: register allocation differs (the target spills `count` to the stack and
// hoists the inner loop's entry test).
#ifdef NON_MATCHING
void func_80108368_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    f32 angles[5];
    f32 time;
    f32 angle;
    f32 pitch;
    s16 count;
    s16 chance;
    s16 type;
    s16 i, j;
    s32 overlap;

    if (D_80111658_puddle_paddle->unk_40 == 0) {
        return;
    }
    time = Hu3DData[object->model[0]].motTime;
    if ((time >= 30.0f) & (time <= 35.0f)) {
        D_80111658_puddle_paddle->unk_40 = 0;
        count = rand16() % 3 + 2;
        for (i = 0; i < count; i++) {
            chance = 65;
            if (D_80111234_puddle_paddle < 11) {
                chance = rand16() % 101;
            }
            pitch = rand16() % 41 + 30;
            do {
                if (i == 0) {
                    angle = angles[0] = Hu3DData[slot->unk_04[0]].rot.y;
                } else {
                    angle = angles[i] = rand16() % 360;
                }
                overlap = 0;
                for (j = 0; j < i; j++) {
                    if (i != j && ABS(angles[i] - angles[j]) < 45.0f) {
                        overlap = 1;
                    }
                }
            } while (overlap);
            type = 0;
            if (chance < 61) {
                D_80111234_puddle_paddle++;
            } else if (chance < 71) {
                D_80111234_puddle_paddle = 0;
                type = 1;
            } else if (chance < 101) {
                type = 2;
            }
            func_80108E2C_puddle_paddle(func_8010910C_puddle_paddle(type), type, angle, pitch, slot->unk_04[0]);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", func_80108368_puddle_paddle);
#endif

void func_801087DC_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    HmfModel *model;
    f32 t;
    s16 i;
    s16 index;

    for (i = 0; i < 16; i++, item++) {
        if (item->state == 0) {
            continue;
        }
        model = &Hu3DData[item->model];
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        if (item->type == 2) {
            item->spin += item->spinSpeed;
            if (item->spin > 360.0f) {
                item->spin -= 360.0f;
            }
            if (item->spin < 0.0f) {
                item->spin += 360.0f;
            }
            func_80088910_main(Hu3DData[item->model].mtx, 0.0f, 0.0f, item->spin);
        }
        if (D_80111658_puddle_paddle->unk_00 & 4) {
            func_8010BA04_puddle_paddle((s8)slot->unk_00->work[1], 0xFFF, 0, func_80108D10_puddle_paddle, 0);
            func_8010BAA8_puddle_paddle((s8)slot->unk_00->work[1], handler);
            return;
        }
        switch (item->state) {
            case 1:
                model->pos.x += item->velocity.x;
                model->pos.y += item->velocity.y;
                model->pos.z += item->velocity.z;
                item->velocity.y = item->unk_14 - ++item->timer * 2.45f;
                if (model->pos.y < 170.0f) {
                    index = func_8010C42C_puddle_paddle(0);
                    if (index != -1) {
                        func_8010C4D0_puddle_paddle(index, model->pos.x, 170.0f, model->pos.z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                    if (item->type != 2) {
                        item->state = 2;
                        item->timer = 0;
                        item->velocity.y *= 0.25f;
                    } else {
                        item->timer = 0;
                        item->unk_1C = 3;
                        item->state = 4;
                        item->velocity.y = 2.45f;
                    }
                    switch (item->type) {
                        case 0:
                            HuAudFXPlay(0x376);
                            break;
                        case 1:
                            HuAudFXPlay(0x377);
                            break;
                        case 2:
                            HuAudFXPlay(0x37A);
                            break;
                    }
                }
                break;
            case 2:
                model->pos.y += item->velocity.y;
                item->velocity.y += 2.45f;
                if (model->pos.y >= 170.0f) {
                    item->state = 3;
                    item->velocity.y = model->pos.y;
                }
                break;
            case 3:
                t = item->timer / 50.0f;
                if (t > 1.0f) {
                    t = 1.0f;
                }
                model->pos.y = sindf(t * 180.0f) * 20.0f * 5.0f * 0.4f + item->velocity.y;
                if (++item->timer >= 51) {
                    item->timer = 0;
                }
                if (++item->unk_1C > item->unk_1A) {
                    item->timer = 0;
                    item->unk_1C = 3;
                    item->state = 4;
                    item->velocity.y = 2.45f * 1.5f;
                }
                break;
            case 4:
                if (++item->timer < item->unk_1C) {
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else {
                    item->timer = 0;
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                model->pos.y -= item->velocity.y;
                if (model->pos.y < 0.0f) {
                    item->state = 0;
                    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                break;
        }
    }
}

void func_80108D10_puddle_paddle(void) {
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    HmfModel *model;
    s16 i;
    s16 index;

    for (i = 0; i < 16; i++, item++) {
        if (item->state == 0) {
            continue;
        }
        model = &Hu3DData[item->model];
        if (item->state == 5) {
            if (++item->timer >= 6) {
                func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                item->state = 0;
            }
        } else {
            item->state = 5;
            item->timer = 0;
            index = func_8010C98C_puddle_paddle(0);
            if (index != -1) {
                func_8010CA30_puddle_paddle(index, model->pos.x, model->pos.y - 20.0f, model->pos.z);
            }
        }
    }
}

void func_80108E2C_puddle_paddle(s16 index, s16 type, f32 angle, f32 pitch, s16 model) {
    PuddlePaddleItem *item;
    f32 speed;
    f32 dx, dz;

    if (index == -1) {
        return;
    }
    item = &D_80111658_puddle_paddle->items[index];
    speed = (rand16() % 6 + 20) * 0.01f;
    item->velocity.x = sindf(angle) * 20.0f * 5.0f * speed;
    item->velocity.z = cosdf(angle) * 20.0f * 5.0f * speed;
    item->unk_14 = item->velocity.y = sindf(pitch) * 20.0f * 5.0f * 0.3f;
    item->type = type;
    item->state = 1;
    item->timer = 0;
    item->unk_1C = 0;
    switch (type) {
        case 0:
            item->unk_1A = 250;
            break;
        case 1:
            item->unk_1A = 150;
            break;
        case 2:
            if (angle < 180.0f) {
                item->spinSpeed = -20.0f;
            } else {
                item->spinSpeed = 20.0f;
            }
            break;
    }
    dx = sindf(Hu3DData[model].rot.y) * 75.0f;
    dz = cosdf(Hu3DData[model].rot.y) * 75.0f;
    func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(item->model, Hu3DData[model].pos.x + dx, Hu3DData[model].pos.y + 50.0f, Hu3DData[model].pos.z + dz);
}

s16 func_8010910C_puddle_paddle(s16 type) {
    s16 end = 0;
    s16 start = 0;
    s16 i;

    switch (type) {
        case 2:
            start += 4;
            end += 4;
        case 1:
            start += 8;
            end += 4;
        case 0:
            end += 8;
    }
    for (i = start; i < end; i++) {
        if (D_80111658_puddle_paddle->items[i].state == 0) {
            break;
        }
    }
    if (i == end) {
        return -1;
    }
    return i;
}

void func_801091F8_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    omObjData *object = slot->unk_00;
    PuddlePaddlePlayer *players[2]; // [0] = this CPU, [1] = the team's human player

    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        return;
    }
    players[0] = (PuddlePaddlePlayer *)handler->unk_3C;
    players[1] = &D_80111654_puddle_paddle[D_80111650_puddle_paddle[players[0]->team].unk_2C];
    if (handler->unk_04 == 0) {
        switch (GwPlayer[object->work[0]].cpu_difficulty) {
            case 0:
                handler->unk_0C[0] = 4;
                handler->unk_0C[1] = 8;
                players[0]->unk_52 = 20;
                players[0]->unk_54 = 15;
                break;
            case 1:
                handler->unk_0C[0] = 4;
                handler->unk_0C[1] = 7;
                players[0]->unk_52 = 30;
                players[0]->unk_54 = 13;
                break;
            case 2:
                handler->unk_0C[0] = 3;
                handler->unk_0C[1] = 6;
                players[0]->unk_52 = 40;
                players[0]->unk_54 = 11;
                break;
            case 3:
                handler->unk_0C[0] = 3;
                handler->unk_0C[1] = 5;
                players[0]->unk_52 = 99;
                players[0]->unk_54 = 9;
                break;
        }
        handler->unk_04 = 1;
    }
    D_800CBB6E_main[players[0]->unk_00] = 0;
    D_800D20A1_main[players[0]->unk_00] = 0;
    D_800CDA7C_main[players[0]->unk_00] = 0;
    if (object->work[0] == D_80111650_puddle_paddle[players[0]->team].unk_2C || (players[1]->unk_04 & 8)) {
        if (++handler->unk_1C[0] > handler->unk_1C[1]) {
            handler->unk_1C[0] = 0;
            handler->unk_1C[1] = rand16() % (handler->unk_0C[1] - handler->unk_0C[0] + 1) + handler->unk_0C[0];
            ((u16 *)D_800CDA7C_main)[players[0]->unk_00] = A_BUTTON;
        }
    }
}

void func_801094C4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddlePlayer *player = (PuddlePaddlePlayer *)handler->unk_3C;
    s16 stickX;

    player->unk_04 &= ~6;
    if (player->unk_04 & 0x10) {
        return;
    }
    if (D_80111658_puddle_paddle->unk_00 & 2) {
        if (++handler->unk_0C[2] >= 7) {
            handler->unk_0C[2] = 6;
            player->unk_04 &= ~8;
        }
        if ((u16)D_800CDA7C_main[player->unk_00] & A_BUTTON) {
            if (handler->unk_0C[0] == 0) {
                handler->unk_0C[0] = 1;
                handler->unk_0C[2] = 0;
                player->unk_4C += 0.05f;
                player->unk_04 |= 8;
                if (player->unk_4C > 1.0f) {
                    player->unk_4C = 1.0f;
                }
            }
        } else {
            handler->unk_0C[0] = 0;
        }
        if (handler->unk_0C[1] == 0) {
            handler->unk_0C[1] = 1;
            player->unk_4C -= sindf(player->unk_4C * 90.0f) * 0.025f;
            if (player->unk_4C < 0.0f) {
                player->unk_4C = 0.0f;
            }
        } else {
            handler->unk_0C[1] = 0;
        }
        stickX = D_800CBB6E_main[player->unk_00];
        if ((stickX == 0) & (D_800D20A1_main[player->unk_00] == 0)) {
            return;
        }
        if (stickX < -7) {
            player->unk_04 |= 4;
        } else if (stickX >= 8) {
            player->unk_04 |= 2;
        }
    } else {
        player->unk_04 &= ~8;
        if (handler->unk_0C[1] == 0) {
            handler->unk_0C[1] = 1;
            player->unk_4C -= sindf(player->unk_4C * 90.0f) * 0.1f;
            if (player->unk_4C < 0.0f) {
                player->unk_4C = 0.0f;
            }
        } else {
            handler->unk_0C[1] = 0;
        }
    }
}

void func_80109718_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddlePlayer *player = (PuddlePaddlePlayer *)handler->unk_3C;
    omObjData *object = slot->unk_00;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (player->unk_58 == 1) {
        return;
    }
    if (model->motTime >= D_800CCF58_main[model->motId].unk02 - 1) {
        player->unk_08 = 1;
    }
    if (player->unk_08 != 0) {
        func_800E5690_minigame(object, player->unk_0A);
        player->unk_08 = 0;
        if (player->unk_58 == -1) {
            player->unk_58 = 1;
        }
        if (player->unk_0E != -1) {
            player->unk_0A = player->unk_0E;
            player->unk_0E = -1;
        }
    }
}

void func_80109804_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1, u8 arg2) {
    arg0->unk_08 = arg2;
    arg0->unk_0A = arg0->unk_0C = arg1;
}

void func_80109814_puddle_paddle(PuddlePaddlePlayer *arg0, s16 arg1) {
    arg0->unk_0E = arg1;
}

// NON_MATCHING: the target keeps `closest` in a stack slot and computes dist/angle in $f12.
#ifdef NON_MATCHING
void func_8010981C_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleTeam *team = (PuddlePaddleTeam *)handler->unk_3C;
    PuddlePaddleItem *item = D_80111658_puddle_paddle->items;
    PuddlePaddlePlayer *player = &D_80111654_puddle_paddle[team->unk_2C];
    HmfModel *models[2]; // [0] = boat, [1] = item
    Vec boatPos;
    Vec itemPos;
    Vec diff;
    f32 minDist;
    f32 distSq;
    f32 dist;
    f32 angle;
    s16 closest;
    s16 i;

    player->unk_04 &= ~6;
    if (player->unk_04 & 0x10) {
        return;
    }
    if (!(D_80111658_puddle_paddle->unk_00 & 2)) {
        return;
    }
    models[0] = &Hu3DData[slot->unk_04[handler->unk_05]];
    boatPos.x = models[0]->pos.x;
    boatPos.y = models[0]->pos.y;
    boatPos.z = models[0]->pos.z;
    minDist = 9999.0f;
    closest = -1;
    for (i = 0; i < 16; i++, item++) {
        if (item->state == 3 && item->type != 2) {
            models[1] = &Hu3DData[item->model];
            itemPos.x = models[1]->pos.x;
            itemPos.y = models[1]->pos.y;
            itemPos.z = models[1]->pos.z;
            diff.x = itemPos.x - boatPos.x;
            diff.y = itemPos.y - boatPos.y;
            diff.z = itemPos.z - boatPos.z;
            distSq = diff.x * diff.x + diff.z * diff.z;
            if (distSq == 0.0f) {
                dist = 0.0f;
            } else {
                dist = HuSqrtf(distSq);
            }
            if (dist < minDist) {
                minDist = dist;
                closest = i;
            }
        }
    }
    if (closest == -1) {
        return;
    }
    models[1] = &Hu3DData[D_80111658_puddle_paddle->items[closest].model];
    itemPos.x = models[1]->pos.x;
    itemPos.y = models[1]->pos.y;
    itemPos.z = models[1]->pos.z;
    diff.x = itemPos.x - boatPos.x;
    diff.z = itemPos.z - boatPos.z;
    angle = atan2df(-diff.z, diff.x) + 90.0f;
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    if (angle > 360.0f) {
        angle -= 360.0f;
    }
    diff.x = models[0]->rot.y;
    diff.y = angle;
    func_80110BBC_puddle_paddle(&diff.x, &diff.y);
    if (ABS(diff.x - diff.y) < 6.0f) {
        return;
    }
    if (diff.x - diff.y > 0.0f) {
        player->unk_04 |= 2;
    } else if (diff.x - diff.y < 0.0f) {
        player->unk_04 |= 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_11_puddle_paddle/main", func_8010981C_puddle_paddle);
#endif

void func_80109BD4_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    PuddlePaddlePlayer *player;
    HmfModel *boat;
    HmfModel *model;
    HmfModel *other;
    func_800E1BA8_minigame_ObjData *data;
    Vec diff;
    f32 x, z;
    s16 angle;
    s16 index;
    s16 left, right;
    s16 i, j;

    for (i = 0; i < 2; i++, team++) {
        boat = &Hu3DData[slot->unk_04[i]];
        for (j = 0; j < 2; j++) {
            player = &D_80111654_puddle_paddle[team->players[j]];
            model = &Hu3DData[D_800EC598_minigame[team->players[j]]->model[0]];
            angle = player->unk_48 + team->unk_18;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            x = sindf(angle) * 20.0f * 5.0f * 0.7f + boat->pos.x;
            z = cosdf(angle) * 20.0f * 5.0f * 0.7f + boat->pos.z;
            Hu3DModelPosSet(D_800EC598_minigame[team->players[j]]->model[0], x, boat->pos.y + 37.0f, z);
            Hu3DModelRotSet(D_800EC598_minigame[team->players[j]]->model[0], 0.0f, boat->rot.y, 0.0f);
            Hu3DModelPosSet(D_800EC598_minigame[team->players[j]]->model[1], x, boat->pos.y + 34.0f, z);
            if (player->unk_04 & 8) {
                if (player->unk_04 & 2) {
                    func_80109804_puddle_paddle(player, 0x27, 0);
                } else if (player->unk_04 & 4) {
                    func_80109804_puddle_paddle(player, 0x28, 0);
                } else {
                    func_80109804_puddle_paddle(player, 0x26, 0);
                }
            } else {
                if (player->unk_04 & 2) {
                    func_80109804_puddle_paddle(player, 0x27, 0);
                } else if (player->unk_04 & 4) {
                    func_80109804_puddle_paddle(player, 0x28, 0);
                } else {
                    func_80109804_puddle_paddle(player, 0, 0);
                }
            }
            data = D_800EC598_minigame[team->players[j]]->data;
            left = FALSE;
            right = FALSE;
            if (model->motTime == 20.0f) {
                if (data->unkD8.unk02 == 0x26) {
                    left = TRUE;
                    right = TRUE;
                } else if (data->unkD8.unk02 == 0x27) {
                    left = TRUE;
                } else if (data->unkD8.unk02 == 0x28) {
                    right = TRUE;
                }
            }
            other = &Hu3DData[i == 0 ? slot->unk_04[1] : slot->unk_04[0]];
            if (left) {
                index = func_8010C42C_puddle_paddle(0);
                if (index != -1) {
                    x = model->pos.x + sindf(team->unk_18 + 70.0f) * 20.0f * 5.0f * 2.0f;
                    z = model->pos.z + cosdf(team->unk_18 + 70.0f) * 20.0f * 5.0f * 2.0f;
                    diff.x = x - other->pos.x;
                    diff.z = z - other->pos.z;
                    diff.y = HuSqrtf(diff.x * diff.x + diff.z * diff.z);
                    if (diff.y > 200.0f) {
                        func_8010C4D0_puddle_paddle(index, x, model->pos.y, z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                }
            }
            if (right) {
                index = func_8010C42C_puddle_paddle(0);
                if (index != -1) {
                    x = model->pos.x + sindf(team->unk_18 + 290.0f) * 20.0f * 5.0f * 2.0f;
                    z = model->pos.z + cosdf(team->unk_18 + 290.0f) * 20.0f * 5.0f * 2.0f;
                    diff.x = x - other->pos.x;
                    diff.z = z - other->pos.z;
                    diff.y = HuSqrtf(diff.x * diff.x + diff.z * diff.z);
                    if (diff.y > 200.0f) {
                        func_8010C4D0_puddle_paddle(index, x, model->pos.y, z, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
                    }
                }
            }
            if (left | right) {
                func_8004AC5C_main(0x379, team->players[j]);
            }
        }
    }
}

void func_8010A224_puddle_paddle(void) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    PuddlePaddlePlayer *player;
    omObjData *object;
    s16 i, j;
    s16 index;

    for (i = 0; i < 2; i++, team++) {
        for (j = 0; j < 2; j++) {
            index = team->players[j];
            player = &D_80111654_puddle_paddle[index];
            object = D_800EC598_minigame[index];
            if (!(player->unk_04 & 0x10)) {
                continue;
            }
            if (++player->unk_10 < 3) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                player->unk_10 = 0;
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            if (++player->unk_11 >= 21) {
                func_8001C258_main(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                player->unk_04 &= ~0x10;
                player->unk_11 = 0;
                player->unk_10 = 0;
            }
        }
    }
}

void func_8010A398_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    PuddlePaddlePlayer *player;
    HmfModel *boat;
    f32 x, z;
    f32 t;
    f32 shake;
    s16 i, j;

    for (i = 0; i < 2; i++, team++) {
        boat = &Hu3DData[slot->unk_04[i]];
        team->power = 0.0f;
        for (j = 0; j < 2; j++) {
            player = &D_80111654_puddle_paddle[team->players[j]];
            if ((GwPlayer[team->players[j]].stat & 1) && team->players[j] != team->unk_2C) {
                if (rand16() % (player->unk_52 + 1) == 0 && (GwPlayer[team->unk_2C].stat & 1)) {
                    team->unk_60 = 0;
                    team->unk_62 = rand16() % (player->unk_54 - 4) + 5;
                }
                player->unk_04 &= ~6;
                if (++team->unk_60 > team->unk_62) {
                    team->unk_60 = team->unk_62;
                    if (D_80111654_puddle_paddle[team->unk_2C].unk_04 & 4) {
                        player->unk_04 |= 4;
                    }
                    if (D_80111654_puddle_paddle[team->unk_2C].unk_04 & 2) {
                        player->unk_04 |= 2;
                    }
                } else {
                    if (D_80111654_puddle_paddle[team->unk_2C].unk_04 & 4) {
                        player->unk_04 |= 2;
                    }
                    if (D_80111654_puddle_paddle[team->unk_2C].unk_04 & 2) {
                        player->unk_04 |= 4;
                    }
                }
            }
            if (player->unk_04 & 2) {
                team->unk_18 -= 2.0f;
            } else if (player->unk_04 & 4) {
                team->unk_18 += 2.0f;
            }
            if (!(player->unk_4C < 0.1f)) {
                team->power += player->unk_4C;
            }
        }
        if (team->unk_18 < 0.0f) {
            team->unk_18 += 360.0f;
        }
        if (team->unk_18 >= 360.0f) {
            team->unk_18 -= 360.0f;
        }
        boat->rot.y = team->unk_18;
        x = team->drag.x;
        if (ABS(team->velocity.x) > team->drag.x) {
            team->velocity.x = (team->velocity.x > 0.0f) ? team->velocity.x - x : x + team->velocity.x;
        } else {
            team->velocity.x = 0.0f;
        }
        z = team->drag.z;
        if (ABS(team->velocity.z) > team->drag.z) {
            z = team->drag.z;
            team->velocity.z = (team->velocity.z > 0.0f) ? team->velocity.z - z : z + team->velocity.z;
        } else {
            team->velocity.z = 0.0f;
        }
        t = handler->unk_1C[0] / 120.0f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        if (++handler->unk_1C[0] > 120) {
            handler->unk_1C[0] = 0;
        }
        if (player->unk_04 & 0x10) {
            shake = (rand16() % 7 - 3) * 0.2f;
            x = shake * 100.0f * 0.2f;
            shake = (rand16() % 7 - 3) * 0.2f;
            z = shake * 100.0f * 0.2f;
            boat->pos.x = x + team->unk_50;
            boat->pos.z = z + team->unk_54;
        } else {
            x = sindf(team->unk_18) * 20.0f * 5.0f * team->power * 0.08f;
            z = cosdf(team->unk_18) * 20.0f * 5.0f * team->power * 0.08f;
            boat->pos.x += x;
            boat->pos.z += z;
        }
        boat->pos.y = sindf(t * 180.0f) * 20.0f * 5.0f * 0.1f + 170.0f;
        if ((x != 0.0f) & (z != 0.0f)) {
            team->velocity.x += x * 0.005f;
            team->velocity.z += z * 0.005f;
            team->drag.x = x * 0.001f;
            team->drag.z = z * 0.001f;
        }
    }
}

void func_8010ABCC_puddle_paddle(PuddlePaddleSlot *slot, PuddlePaddleHandler *handler) {
    HmfModel *models[3]; // [0], [1] = boats, [2] = item
    Vec a;
    Vec b;
    Vec d;
    f32 dist;
    f32 range;
    f32 maxDist;
    f32 minDist; // also reused for the squared item distance
    PuddlePaddleItem *item;
    s16 i, j, k;
    s16 index;

    models[0] = &Hu3DData[slot->unk_04[0]];
    models[1] = &Hu3DData[slot->unk_04[1]];
    if (D_80111650_puddle_paddle[0].power > D_80111650_puddle_paddle[1].power) {
        a.x = models[1]->pos.x;
        b.x = models[0]->pos.x;
        a.z = models[1]->pos.z;
        b.z = models[0]->pos.z;
    } else {
        a.x = models[0]->pos.x;
        b.x = models[1]->pos.x;
        a.z = models[0]->pos.z;
        b.z = models[1]->pos.z;
    }
    d.x = b.x - a.x;
    d.z = b.z - a.z;
    dist = HuSqrtf(d.x * d.x + d.z * d.z);
    if (dist <= 300.0f) {
        d.x = d.x / dist * 300.0f;
        a.x = b.x - d.x;
        d.z = d.z / dist * 300.0f;
        a.z = b.z - d.z;
    }
    if (D_80111650_puddle_paddle[0].power > D_80111650_puddle_paddle[1].power) {
        models[1]->pos.x = a.x;
        models[0]->pos.x = b.x;
        models[1]->pos.z = a.z;
        models[0]->pos.z = b.z;
    } else {
        models[0]->pos.x = a.x;
        models[1]->pos.x = b.x;
        models[0]->pos.z = a.z;
        models[1]->pos.z = b.z;
    }

    for (i = 0; i < 2; i++) {
        d.x = models[i]->pos.x;
        d.z = models[i]->pos.z;
        maxDist = 700.0f;
        minDist = 400.0f;
        dist = HuSqrtf(d.x * d.x + d.z * d.z);
        if (dist >= maxDist) {
            d.x = d.x / dist * maxDist;
            d.z = d.z / dist * maxDist;
        } else if (dist < minDist) {
            d.x = minDist * (d.x / dist);
            d.z = minDist * (d.z / dist);
        }
        models[i]->pos.x = d.x;
        models[i]->pos.z = d.z;
    }

    for (i = 0; i < 2; i++) {
        a.x = models[i]->pos.x;
        a.y = models[i]->pos.y + 50.0f;
        a.z = models[i]->pos.z;
        range = 120.00001f;
        item = D_80111658_puddle_paddle->items;
        for (j = 0; j < 16; j++, item++) {
            if (item->state == 0) {
                continue;
            }
            if (item->state == 4 && Hu3DData[item->model].pos.y < 100.0f) {
                continue;
            }
            models[2] = &Hu3DData[item->model];
            b.x = models[2]->pos.x;
            b.y = models[2]->pos.y;
            b.z = models[2]->pos.z;
            d.x = b.x - a.x;
            d.y = b.y - a.y;
            d.z = b.z - a.z;
            if (item->state < 3 && item->radius < ABS(d.y)) {
                continue;
            }
            minDist = d.x * d.x + d.z * d.z;
            dist = (minDist == 0.0f) ? 0.0f : HuSqrtf(minDist);
            if (!(dist < range + item->radius)) {
                continue;
            }
            item->state = 0;
            func_8001C258_main(item->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            switch (item->type) {
                case 0:
                    Hu3DModelScaleSet(func_8000D550_main(D_80111658_puddle_paddle->unk_3C, b.x, b.y, b.z), 2.0f, 2.0f, 2.0f);
                    D_80111650_puddle_paddle[i].score += 1;
                    GwPlayer[D_80111650_puddle_paddle[i].players[0]].gameCoin += 1;
                    GwPlayer[D_80111650_puddle_paddle[i].players[1]].gameCoin += 1;
                    D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[0]].unk_56 += 1;
                    D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[1]].unk_56 += 1;
                    HuAudFXPlay(9);
                    break;
                case 1:
                    Hu3DModelScaleSet(func_8000D550_main(D_80111658_puddle_paddle->unk_3C, b.x, b.y, b.z), 2.0f, 2.0f, 2.0f);
                    D_80111650_puddle_paddle[i].score += 5;
                    GwPlayer[D_80111650_puddle_paddle[i].players[0]].gameCoin += 5;
                    GwPlayer[D_80111650_puddle_paddle[i].players[1]].gameCoin += 5;
                    D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[0]].unk_56 += 5;
                    D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[1]].unk_56 += 5;
                    HuAudFXPlay(0x15);
                    break;
                case 2:
                    if (D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[0]].unk_04 & 0x10) {
                        break;
                    }
                    for (k = 0; k < 2; k++) {
                        omVibrate(D_80111650_puddle_paddle[i].players[k], 20, 0, 20);
                        D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[k]].unk_04 |= 0x10;
                        func_80109804_puddle_paddle(&D_80111654_puddle_paddle[D_80111650_puddle_paddle[i].players[k]], 0x29, 1);
                        func_8004AC5C_main(GwPlayer[D_80111650_puddle_paddle[i].players[k]].chr + 0x95, D_80111650_puddle_paddle[i].players[k]);
                        D_80111650_puddle_paddle[i].unk_50 = models[i]->pos.x;
                        D_80111650_puddle_paddle[i].unk_54 = models[i]->pos.z;
                    }
                    index = func_8010C42C_puddle_paddle(1);
                    if (index != -1) {
                        func_8010C4D0_puddle_paddle(index, models[i]->pos.x, models[i]->pos.y + 20.0f, models[i]->pos.z, 0.0f, 0.0f, 0.0f, 1.2f, 0.0f);
                    }
                    break;
            }
        }
    }
}

void func_8010B574_puddle_paddle(void) {
    PuddlePaddleTeam *team = D_80111650_puddle_paddle;
    s16 isCpu[2];
    s16 difficulty[2];
    s16 i, j;
    s16 index;

    for (i = 0; i < 2; i++, team++) {
        isCpu[0] = GwPlayer[D_80111650_puddle_paddle[i].players[0]].stat & 1;
        isCpu[1] = GwPlayer[D_80111650_puddle_paddle[i].players[1]].stat & 1;
        if (isCpu[0] && isCpu[1]) {
            difficulty[0] = GwPlayer[team->players[0]].cpu_difficulty;
            difficulty[1] = GwPlayer[team->players[1]].cpu_difficulty;
            if (difficulty[1] < difficulty[0]) {
                team->unk_2C = team->players[0];
            } else {
                team->unk_2C = team->players[1];
            }
            for (j = 0; j < 2; j++) {
                index = team->players[j];
                func_8010BA04_puddle_paddle(index + 3, 0, &D_80111654_puddle_paddle[index], func_801091F8_puddle_paddle, 0);
            }
            func_8010BA04_puddle_paddle(7, 0, &D_80111650_puddle_paddle[i], func_8010981C_puddle_paddle, i);
        } else if (isCpu[0] || isCpu[1]) {
            if (isCpu[0]) {
                team->unk_2C = team->players[1];
            } else {
                team->unk_2C = team->players[0];
            }
            for (j = 0; j < 2; j++) {
                index = team->players[j];
                if (index != team->unk_2C) {
                    func_8010BA04_puddle_paddle(index + 3, 0, &D_80111654_puddle_paddle[index], func_801091F8_puddle_paddle, 0);
                }
            }
        }
    }
}
