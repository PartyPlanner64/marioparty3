#include "common.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
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
    s16 unk_02;
    f32 unk_04; // score
    f32 unk_08;
    s16 unk_0C; // state, 5 when finished
    char unk_0E[10];
    s16 unk_18; // GwPlayer index
    char unk_1A[2];
    s16 unk_1C;
    char unk_1E[62];
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

extern s32 D_8010F194_bowser_toss;
extern Vec D_8010F198_bowser_toss[2];
extern s32 D_8010F1B0_bowser_toss[4];
extern omObjData *D_8010FB50_bowser_toss;
extern s32 D_8010FB54_bowser_toss;
extern s32 D_8010FB58_bowser_toss;
extern s32 D_8010FB5C_bowser_toss;
extern s32 D_8010FB60_bowser_toss;
extern s32 D_8010FB64_bowser_toss;
extern s32 D_8010FB68_bowser_toss;
extern s32 D_8010FB6C_bowser_toss;
extern s16 D_8010FB70_bowser_toss;
extern s16 D_8010FB72_bowser_toss;
extern BowserTossPlayer *D_8010FB74_bowser_toss;
extern s16 D_8010FB78_bowser_toss;
extern s32 D_8010FB7C_bowser_toss;
extern s32 D_8010FB80_bowser_toss;
extern s32 D_8010FB84_bowser_toss;
extern s16 *D_8010FB98_bowser_toss;
extern D_80111B50_vine_with_me_Struct D_8010FBB8_bowser_toss;
extern const s16 D_8010F530_bowser_toss[];
extern const s16 D_8010F53C_bowser_toss[];
extern UnkBowser *D_8010FB8C_bowser_toss;
extern BowserTossBowser *D_8010FBA0_bowser_toss;

void func_80105C80_bowser_toss(omObjData *object);
void func_80105CEC_bowser_toss(omObjData *object);
void func_80106568_bowser_toss(void);
void func_801084DC_bowser_toss(void);
void func_8010A028_bowser_toss(void);
void func_8010A4A8_bowser_toss(void);
void func_8010AD98_bowser_toss(void);
void func_8010B41C_bowser_toss(void);
void func_8010C2DC_bowser_toss(void);
void func_8010A500_bowser_toss(omObjData *object);
void func_8010649C_bowser_toss(omObjData *object);
void func_801064C0_bowser_toss(omObjData *object);
void func_801067B0_bowser_toss(omObjData *object);
s16 func_8010840C_bowser_toss(void);
s16 func_80108444_bowser_toss(void);
void func_8010847C_bowser_toss(omObjData *object, s16 arg1, s16 arg2);
s16 func_80109F20_bowser_toss(void);
void func_8010C1A0_bowser_toss(s16 arg0, s32 arg1);
s16 func_8010C23C_bowser_toss(void);
void func_8010C274_bowser_toss(void);
s16 func_8010C2A4_bowser_toss(void);
void func_8010D250_bowser_toss(s32 camIndex, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void func_8010D960_bowser_toss(omObjData *obj, u32 arg1);
BowserTossPlayer *func_8010D98C_bowser_toss(omObjData *object);

void func_801059A0_bowser_toss(void) {
    omObjData *obj;
    s32 i;

    func_8001FE20_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 121.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    for (i = 0; i < 2; i++) {
        Hu3DCameraPerspectiveSet(i, 45.0f, 80.0f, 4000.0f);
    }
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010FB60_bowser_toss = 300;
    D_8010FB5C_bowser_toss = 0;
    D_8010FB58_bowser_toss = 0;
    D_8010FB64_bowser_toss = 0;
    D_8010FB68_bowser_toss = 0;
    D_8010FB6C_bowser_toss = 0;
    D_8010FB78_bowser_toss = -1;
    D_8010FB7C_bowser_toss = 0;
    D_8010FB70_bowser_toss = -1;
    D_8010FB84_bowser_toss = -1;
    D_8010FB80_bowser_toss = GWMgRecordGet(4);
    D_8010FB72_bowser_toss = 0;
    D_8010FB50_bowser_toss = omAddObj(0x40, 0, 0, -1, func_80105C80_bowser_toss);
    memset(&D_8010FBB8_bowser_toss, 0, 0x28);
    D_8010FBB8_bowser_toss.unk01 = 4;
    func_800E5EA0_minigame(&D_8010FBB8_bowser_toss);
    D_8010FB98_bowser_toss = HuMemAllocTag(0x20, TAG_OVERLAY);
    memset(D_8010FB98_bowser_toss, 0, 0x20);
    func_80045010_main(D_8010F530_bowser_toss, 1);
    func_80045010_main(D_8010F53C_bowser_toss, 1);
}

void func_80105C80_bowser_toss(omObjData *object) {
    object->func = func_80105CEC_bowser_toss;
    func_8010AD98_bowser_toss();
    func_8010B41C_bowser_toss();
    func_8010A028_bowser_toss();
    func_8010A4A8_bowser_toss();
    func_801084DC_bowser_toss();
    func_80106568_bowser_toss();
    func_8010C2DC_bowser_toss();
    if (_CheckFlag(10)) {
        D_8010FB54_bowser_toss = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F530_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F53C_bowser_toss);

void func_80105CEC_bowser_toss(omObjData *object) {
    BowserTossPlayer *player1;
    BowserTossPlayer *player2;
    UnkBowser *bowser;
    omObjData *obj;
    s32 score1;
    s32 score2;
    f32 x;
    f32 y;
    f32 zoom;

    switch (D_8010FB64_bowser_toss) {
        case 0:
            if (D_8010FB5C_bowser_toss == 2) {
                WipeCreateIn(WIPE_TYPE_PREV, 16);
            }
            if (D_8010FB68_bowser_toss > 0) {
                D_8010FB68_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 1:
            GMesCreate(6);
            HuAudFXPlay(0xE);
            HuAudSeqPlay(0x30);
            D_8010FB68_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
            break;
        case 2:
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (D_8010FB60_bowser_toss + 29) / 30, 156, 32);
                func_800E6F0C_minigame(2);
                D_8010FB64_bowser_toss++;
            }
            break;
        case 3:
            D_8010FB60_bowser_toss--;
            func_8003F578_main((D_8010FB60_bowser_toss + 29) / 30);
            if (D_8010FB60_bowser_toss <= 0) {
                player1 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
                player2 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
                player2->unk_0C = player1->unk_0C = 3;
                func_8003F5C0_main();
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 4:
            if (func_80109F20_bowser_toss() && func_8010840C_bowser_toss()) {
                GMesCreate(0x11);
                func_800E6F0C_minigame(3);
                HuAudSeqFadeOut(120);
                func_8010847C_bowser_toss(D_800EC598_minigame[0], 0, 10);
                func_8010847C_bowser_toss(D_800EC598_minigame[1], 0, 10);
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 6:
            if (D_8010FB5C_bowser_toss >= 15) {
                player1 = func_8010D98C_bowser_toss(D_800EC598_minigame[0]);
                player2 = func_8010D98C_bowser_toss(D_800EC598_minigame[1]);
                score1 = player1->unk_04;
                score2 = player2->unk_04;
                if (player1->unk_04 == 0.0f && player2->unk_04 == 0.0f) {
                    D_8010FB78_bowser_toss = -1;
                    D_8010FB7C_bowser_toss = -1;
                    player2->unk_02 = 1;
                    player1->unk_02 = 1;
                } else if (score1 == score2) {
                    if (rand8() & 1) {
                        score1++;
                        player1->unk_04 += 1.0f;
                    } else {
                        score2++;
                        player2->unk_04 += 1.0f;
                    }
                }
                if (score1 > score2) {
                    D_8010FB78_bowser_toss = player1->index;
                    GwPlayer[player1->unk_18].bonusCoin += 10;
                    player1->unk_02 = 0;
                    player2->unk_02 = 1;
                    D_8010FB7C_bowser_toss = score1;
                } else if (score2 > score1) {
                    D_8010FB78_bowser_toss = player2->index;
                    GwPlayer[player2->unk_18].bonusCoin += 10;
                    player1->unk_02 = 1;
                    player2->unk_02 = 0;
                    D_8010FB7C_bowser_toss = score2;
                }
                func_8010C1A0_bowser_toss(player1->index, score1);
                func_8010C1A0_bowser_toss(player2->index, score2);
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 7:
            if (func_8010C23C_bowser_toss()) {
                if (D_8010FB70_bowser_toss != -1) {
                    HuAudFXPlay(0x4AC);
                    D_8010FB70_bowser_toss = -1;
                }
                func_8010C274_bowser_toss();
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 8:
            if (func_80108444_bowser_toss() && func_8010C2A4_bowser_toss()) {
                if (D_8010FB78_bowser_toss == -1) {
                    GMesCreate(0x20);
                    HuAudSeqPlay(0x6C);
                    D_8010FB68_bowser_toss = 144;
                    func_800E6F0C_minigame(4);
                    D_8010FB64_bowser_toss = 11;
                } else {
                    if (D_8010FB78_bowser_toss != 0) {
                        D_8010FB78_bowser_toss = 1;
                    }
                    if (D_8010FB80_bowser_toss < D_8010FB7C_bowser_toss) {
                        D_8010FB80_bowser_toss = D_8010FB7C_bowser_toss;
                        func_8010C1A0_bowser_toss(2, D_8010FB7C_bowser_toss);
                        GWMgRecordSet(4, (u16)D_8010FB80_bowser_toss);
                        GMesCreate(0x1B);
                        D_8010FB72_bowser_toss = 1;
                        D_8010FB68_bowser_toss = 99;
                        D_8010FB64_bowser_toss = 9;
                    } else {
                        HuAudSeqPlay(0x67);
                        D_8010FB68_bowser_toss = 140;
                        D_8010FB64_bowser_toss = 10;
                    }
                    obj = D_800EC598_minigame[D_8010FB78_bowser_toss];
                    bowser = &D_8010FB8C_bowser_toss[D_8010FB78_bowser_toss];
                    func_8010D98C_bowser_toss(obj);
                    x = obj->trans.x * 0.5f + bowser->unk_30 * 0.5f;
                    if (obj->trans.x != 0.0f) {
                        y = obj->trans.y * 0.5f + 100.0;
                    } else {
                        y = obj->trans.y * 0.5f + 150.0;
                    }
                    zoom = CZoom * 0.5f;
                    if (D_8010FB78_bowser_toss == 1) {
                        y -= 15.000000596046448;
                    }
                    func_8010D250_bowser_toss(D_8010FB78_bowser_toss, x, y, 65535.0f, 65535.0f, 65535.0f, 65535.0f,
                                              zoom, 30);
                    func_800E6F0C_minigame(4);
                }
                D_8010FB5C_bowser_toss = 0;
            }
            break;
        case 9:
            if (D_8010FB5C_bowser_toss >= 75.0f) {
                D_8010FB64_bowser_toss = 10;
                D_8010FB5C_bowser_toss = 0;
            }
            break;
        case 10:
            GMesCreate(0x16, func_8010D98C_bowser_toss(D_800EC598_minigame[D_8010FB78_bowser_toss])->unk_1C);
            if (D_8010FB72_bowser_toss != 0) {
                HuAudSeqPlay(0x6A);
            }
            D_8010FB5C_bowser_toss = 0;
            D_8010FB64_bowser_toss++;
            break;
        case 11:
            if (GMesStatGet() == 0) {
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        case 12:
            if (D_8010FB5C_bowser_toss >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                func_8004AB0C_main(16);
                D_8010FB5C_bowser_toss = 0;
                D_8010FB64_bowser_toss++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = func_8010649C_bowser_toss;
            }
            break;
    }
    func_801064C0_bowser_toss(object);
    D_8010FB58_bowser_toss++;
    D_8010FB5C_bowser_toss++;
}

void func_8010649C_bowser_toss(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_801064C0_bowser_toss(omObjData *object) {
    if (D_8010F194_bowser_toss != 0) {
        if (D_8010F194_bowser_toss == 1) {
            object->func = func_8010649C_bowser_toss;
        }
        D_8010F194_bowser_toss--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010F194_bowser_toss = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)D_8010F194_bowser_toss);
        HuAudSeqFadeOut((s16)D_8010F194_bowser_toss);
        func_8004AB0C_main((s16)D_8010F194_bowser_toss);
    }
}

void func_80106568_bowser_toss(void) {
    s32 used[2];
    BowserTossPlayer *player;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 minGroup;

    used[0] = -1;
    used[1] = -1;
    player = D_8010FB74_bowser_toss = HuMemAllocTag(sizeof(BowserTossPlayer) * 2, TAG_OVERLAY);
    memset(player, 0, sizeof(BowserTossPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, minGroup = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (used[k] == D_8010F1B0_bowser_toss[j]) {
                    found = 1;
                }
            }
            if (!found && GwPlayer[D_8010F1B0_bowser_toss[j]].group < minGroup) {
                minGroup = GwPlayer[D_8010F1B0_bowser_toss[j]].group;
                D_8010FB74_bowser_toss[i].unk_18 = D_8010F1B0_bowser_toss[j];
            }
        }
        used[i] = D_8010FB74_bowser_toss[i].unk_18;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, player++) {
        player->index = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(i + 16, 11, 60, -1, func_801067B0_bowser_toss);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010F198_bowser_toss[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = D_8010F198_bowser_toss[i].y;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010F198_bowser_toss[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->rot.y = 90.0f;
        func_8010D960_bowser_toss(D_800EC598_minigame[D_800EC280_minigame], (u32)player);
        D_800EC280_minigame++;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801067B0_bowser_toss);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F5A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106BC4_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80107E84_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_801080D0_bowser_toss);

s16 func_8010840C_bowser_toss(void) {
    s32 i;
    BowserTossPlayer *p;

    for (i = 0, p = D_8010FB74_bowser_toss; i < 2; i++, p++) {
        if (p->unk_0C != 5) {
            return 0;
        }
    }
    return 1;
}

s16 func_80108444_bowser_toss(void) {
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
    HmfModel *model1 = &Hu3DData[object->model[arg1]];
    HmfModel *model2 = &Hu3DData[object->model[arg2]];
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

s16 func_80109F20_bowser_toss(void) {
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

s16 func_8010C23C_bowser_toss(void) {
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

s16 func_8010C2A4_bowser_toss(void) {
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

BowserTossPlayer *func_8010D98C_bowser_toss(omObjData *object) {
    BowserTossWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return (BowserTossPlayer *)packed.word;
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
