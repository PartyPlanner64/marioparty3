#include "common.h"
#include "game/camera.h"
#include "game/camsetup.h"
#include "game/util.h"
#include "game/pause.h"
#include "game/wipe.h"
#include "variables.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/input.h"
#include "game/mallocblock.h"
#include "game/sprite.h"
#include "gcc/memory.h"
#include "humath.h"
#include "math.h"
#include "overlays/minigame.h"

// Grid cell value marking a cell that was just filled.
#define ETCH_N_CATCH_CELL_FILLED 0x21
// Grid cell value marking a cell that ends a fill.
#define ETCH_N_CATCH_CELL_EDGE 0x22

#define ABS(x) ((x) > 0.0f ? (x) : 0.0f - (x))
#define FABS(x) ((x) < 0.0f ? -(x) : (x))
#define IABS(x) ((x) < 0 ? -(x) : (x))

// Per-player record. D_801113D8_etch_n_catch points at one 0x100-entry array of
// these per player, and a record is free for reuse while unk_00 is zero.
// Records are chained through unk_04/unk_08/unk_0C.
typedef struct EtchNCatchNode {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ struct EtchNCatchNode *unk_04;
    /* 0x08 */ struct EtchNCatchNode *unk_08;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ struct EtchNCatchNode *unk_10;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
    /* 0x16 */ s16 unk_16; // Countdown
    /* 0x18 */ s16 unk_18; // Grid x
    /* 0x1A */ s16 unk_1A; // Grid y
    /* 0x1C */ u8 unk_1C;  // Player index
    /* 0x1E */ s16 unk_1E; // Model, or -1
    /* 0x20 */ Vec unk_20;
    /* 0x2C */ s8 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u8 unk_34; // Index into D_8010C6E8_etch_n_catch[unk_1C]
} EtchNCatchNode;         // sizeof 0x38

// Heap-allocated (0x20 bytes) work block; unk_0C is the head of a linked list
// of nodes (func_80108B64 inserts, func_80108BCC removes, func_80108C08 walks).
typedef struct EtchNCatchWork {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01; // Team (3 or 12)
    /* 0x02 */ u8 unk_02;
    /* 0x04 */ s16 unk_04; // Grid x
    /* 0x06 */ s16 unk_06; // Grid y
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ struct EtchNCatchNode *unk_0C;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ u8 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x17 */ u8 unk_17;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s16 unk_1C;
} EtchNCatchWork; // sizeof 0x20

// Positions of the four players and the offsets applied to them while
// func_80106A64_etch_n_catch runs the shared player update.
typedef struct EtchNCatchPlayerOffsets {
    /* 0x00 */ f32 offsetX[4];
    /* 0x10 */ f32 offsetZ[4];
    /* 0x20 */ f32 x[4];
    /* 0x30 */ f32 z[4];
} EtchNCatchPlayerOffsets; // sizeof 0x40

// Byte grid of player slots: D_8010C84C_etch_n_catch is the base address and
// D_8010C846_etch_n_catch the row stride in bytes.
extern u8 *D_8010C84C_etch_n_catch;
extern s16 D_8010C846_etch_n_catch;
extern s16 D_8010C848_etch_n_catch; // Grid height
extern EtchNCatchNode *D_801113D8_etch_n_catch[4];

// Heap-allocated list of grid cells touched this frame, one pointer per entry.
extern u8 **D_8010C878_etch_n_catch;

// Two heap-allocated queues of grid cells, swapped between fill passes.
extern u8 **D_8010C87C_etch_n_catch[2];

// Per-player region bits of each grid cell pair, 160 cells per row.
extern u8 D_8010C890_etch_n_catch[][160];

// Per-object data of the player objects created by func_80109A54_etch_n_catch.
typedef struct EtchNCatchPlayerData {
    /* 0x000 */ func_800E1BA8_minigame_ObjData base;
    /* 0x15C */ s32 unk15C;
    /* 0x160 */ u8 unk160; // Index into D_801113E8_etch_n_catch
    /* 0x161 */ u8 unk161;
    /* 0x164 */ f32 unk164;
    /* 0x168 */ f32 unk168;
    /* 0x16C */ f32 unk16C;
    /* 0x170 */ f32 unk170;
    /* 0x174 */ f32 unk174;
    /* 0x178 */ Vec unk178[5];
    /* 0x1B4 */ f32 unk1B4;
} EtchNCatchPlayerData; // sizeof 0x1B8

// Per-object data of the objects created by func_8010B24C_etch_n_catch.
typedef struct EtchNCatchBoardWork {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
} EtchNCatchBoardWork; // sizeof 0xC

extern s8 D_8010C6A0_etch_n_catch;
extern f32 D_8010C6DC_etch_n_catch;
extern u8 D_8010C6E0_etch_n_catch;
extern u8 D_8010C6E1_etch_n_catch;
extern u8 D_8010C6E2_etch_n_catch;
extern f32 D_8010C834_etch_n_catch;
extern f32 D_800EB770_minigame;
extern EtchNCatchWork *D_8010C838_etch_n_catch;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern s16 D_8010C6A4_etch_n_catch[2][2];
extern s32 D_8010C6D4_etch_n_catch;
extern s8 D_8010C6D9_etch_n_catch;
extern s8 D_8010C6DA_etch_n_catch[2];
extern s8 D_8010C6D8_etch_n_catch;
extern Vec D_8010C6B0_etch_n_catch[3];
extern u8 D_8010C6E4_etch_n_catch[4];
extern u8 D_8010C6E8_etch_n_catch[4][3];
extern u8 D_8010C6F4_etch_n_catch[4];
extern u8 D_8010C6F8_etch_n_catch[2];
extern s16 D_8010C83C_etch_n_catch;
extern s16 D_8010C83E_etch_n_catch;
extern u8 D_8010C830_etch_n_catch;
extern u8 D_8010C840_etch_n_catch;
extern s16 D_8010C842_etch_n_catch;
extern s16 D_8010C844_etch_n_catch;
extern u16 D_801113E8_etch_n_catch[4];
extern s8 D_8010C6AC_etch_n_catch;
extern s8 D_8010C6AD_etch_n_catch;
extern s16 D_8010C850_etch_n_catch[2][2];
extern omObjData *D_8010C858_etch_n_catch[2];
extern omObjData *D_8010C860_etch_n_catch[2];
extern EtchNCatchWork *D_8010C868_etch_n_catch[4];
extern s16 D_80111390_etch_n_catch[4][3];
extern u16 D_801113A8_etch_n_catch[2];
extern D_80111B50_vine_with_me_Struct D_801113B0_etch_n_catch;

void func_80105CD0_etch_n_catch(D_80111B50_vine_with_me_Struct *arg0);
void func_80105D5C_etch_n_catch(void);
void func_8010C2F4_etch_n_catch(void);
void func_80105ED4_etch_n_catch(omObjData *object);
void func_80106334_etch_n_catch(omObjData *object);
void func_80106A64_etch_n_catch(omObjData *object);
void func_80108B20_etch_n_catch(EtchNCatchWork *arg0);
void func_80107EA4_etch_n_catch(omObjData *object);
void func_8010880C_etch_n_catch(func_800E1BA8_minigame_ObjData *data);
EtchNCatchNode *func_80108B28_etch_n_catch(s8 playerId);
void func_80108B64_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node);
void func_80108BCC_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node);
s32 func_80108C08_etch_n_catch(EtchNCatchWork *work);
s32 func_80108DD0_etch_n_catch(s16 x, s16 y);
u8 func_80109114_etch_n_catch(s16 x, s16 y);
void func_8010914C_etch_n_catch(s16 x, s16 y, s32 value);
void func_80109370_etch_n_catch(EtchNCatchNode *node, u8 value);
void func_801097B4_etch_n_catch(EtchNCatchNode *node);
s32 func_8010B154_etch_n_catch(s16 x, s16 y);
void func_8010C628_etch_n_catch(omObjData *object, f32 scale);
void func_80109A54_etch_n_catch(omObjData *object);
void func_80109EB8_etch_n_catch(omObjData *object);
void func_8010AB7C_etch_n_catch(omObjData *object);
void func_8010AD6C_etch_n_catch(EtchNCatchPlayerData *data);
void func_8010AEE4_etch_n_catch(EtchNCatchPlayerData *data);
void func_8010AFB8_etch_n_catch(EtchNCatchPlayerData *data);
void func_8010B24C_etch_n_catch(omObjData *object);
void func_8010B3B4_etch_n_catch(omObjData *object);
void func_8010BBE4_etch_n_catch(omObjData *object);
void func_8010BD98_etch_n_catch(omObjData *object);
void func_8010BE84_etch_n_catch(omObjData *object);
void func_8010C390_etch_n_catch(omObjData *object);
void func_8010C444_etch_n_catch(omObjData *object);
f32 func_8010C4F8_etch_n_catch(f32 arg0);
Vec2f func_8010C574_etch_n_catch(s32 x0, s32 y0, s32 x1, s32 y1);

void func_801059A0_etch_n_catch(void) {
    s32 i;

    func_8001FE20_main(32);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    omInitObjMan(32, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105CD0_etch_n_catch(&D_801113B0_etch_n_catch);
    func_800E5EA0_minigame(&D_801113B0_etch_n_catch);
    Hu3DGLightColorSet(1, 64, 64, 64);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    omSetStatBit(omAddObj(0, 0, 0, -1, func_80105ED4_etch_n_catch), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80105D5C_etch_n_catch();
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C390_etch_n_catch);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(2, 1, 0, -1, func_8010C444_etch_n_catch);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 0, 0, -1, func_8010BE84_etch_n_catch);
    func_800E18D8_minigame();
    D_800EB740_minigame = 0.5f;
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 5, 60, -1, func_80106334_etch_n_catch);
        omSetStatBit(D_800EC598_minigame[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        D_801113D8_etch_n_catch[i] = HuMemAllocTag(0x100 * sizeof(EtchNCatchNode), TAG_OVERLAY);
        memset(D_801113D8_etch_n_catch[i], 0, 0x100 * sizeof(EtchNCatchNode));
    }
    for (i = 0; i < 2; i++) {
        D_8010C860_etch_n_catch[i] = omAddObj(2, 3, 0, -1, func_8010B24C_etch_n_catch);
        D_8010C858_etch_n_catch[i] = omAddObj(2, 7, 2, -1, func_80109A54_etch_n_catch);
    }
    omAddObj(3, 0, 0, -1, func_8010BBE4_etch_n_catch);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80105CD0_etch_n_catch(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 60;
    arg0->unk00 = 0;
    arg0->unk01 = 1;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 0;
    arg0->unk1C = 90;
    arg0->unk1E = 900;
    arg0->unk20 = -1;
    arg0->unk22 = 75;
    arg0->unk24 = 150;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

void func_80105D5C_etch_n_catch(void) {
    s32 camIndex;
    HuCamera *camera;

    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(camIndex, 27.211f, 80.0f, 8000.0f);
    camera = &gCameraList[camIndex];
    camera->pos.x = -1.965f;
    camera->pos.y = 1392.72f;
    camera->pos.z = 1374.455f;
    camera->at.x = -1.965f;
    camera->at.y = 60.495f;
    camera->at.z = 20.66f;
    camera->up.x = 0.0f;
    camera->up.y = 0.5f;
    camera->up.z = -0.8660254f;
}

void func_80105ED4_etch_n_catch(omObjData *object) {
    s32 voice;
    s8 i;

    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_8010C6D8_etch_n_catch == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            func_800E6F0C_minigame(5);
            D_8010C6D8_etch_n_catch = 1;
        }
        func_800E1840_minigame();
        switch (func_800E6F40_minigame()) {
            case 0:
                D_800EB930_minigame = 56;
                break;
            case 1:
                break;
            case 2:
                if (D_8010C6AC_etch_n_catch >= 5 || D_8010C6AD_etch_n_catch >= 5) {
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (func_800E6E9C_minigame() == 74.0) {
                    if (D_8010C6AC_etch_n_catch == D_8010C6AD_etch_n_catch) {
                        D_801113B0_etch_n_catch.unk06 = 4;
                    } else {
                        D_801113B0_etch_n_catch.unk06 = 1;
                        for (i = 0; i < 4; i++) {
                            if (D_8010C6AC_etch_n_catch > D_8010C6AD_etch_n_catch && GwPlayer[i].group == 0) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            } else if (D_8010C6AC_etch_n_catch < D_8010C6AD_etch_n_catch && GwPlayer[i].group == 1) {
                                if (D_801113B0_etch_n_catch.unk18[0] == 0xFF) {
                                    D_801113B0_etch_n_catch.unk18[0] = i;
                                } else {
                                    D_801113B0_etch_n_catch.unk18[1] = i;
                                }
                                GwPlayer[i].gameCoin += 10;
                            }
                        }
                    }
                }
                break;
            case 4:
                if (D_800EB934_minigame != 0) {
                    for (i = 0; i < 4; i++) {
                        if (D_801113B0_etch_n_catch.unk06 == 1) {
                            if (i == D_801113B0_etch_n_catch.unk18[0] || i == D_801113B0_etch_n_catch.unk18[1]) {
                                func_800E5690_minigame(D_800EC598_minigame[i], 13);
                                switch (GwPlayer[i].chr) {
                                    case 0:
                                    default:
                                        voice = 2;
                                        break;
                                    case 1:
                                        voice = 3;
                                        break;
                                    case 2:
                                        voice = 7;
                                        break;
                                    case 3:
                                        voice = 4;
                                        break;
                                    case 4:
                                        voice = 5;
                                        break;
                                    case 5:
                                        voice = 6;
                                        break;
                                    case 6:
                                        voice = 8;
                                        break;
                                    case 7:
                                        voice = 9;
                                        break;
                                }
                                HuAudFXAllStop();
                                func_80045ED0_main((voice << 16) | 0x2F);
                            } else {
                                func_800E5690_minigame(D_800EC598_minigame[i], 14);
                            }
                        } else {
                            func_800E5690_minigame(D_800EC598_minigame[i], 14);
                        }
                    }
                }
                break;
            case 5:
                if (D_8010C6D4_etch_n_catch == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    func_8010C2F4_etch_n_catch();
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    omOvlReturnEx(1);
                }
                D_8010C6D4_etch_n_catch++;
                break;
        }
        Hu3DCameraPosSetV(0, &gCameraList[0].pos, &gCameraList[0].at, &gCameraList[0].up);
        Hu3DCamUpdateMtx(0);
    }
}

#ifdef NON_MATCHING
void func_80106334_etch_n_catch(omObjData *object) {
    Vec team0PosA[2] = { { -350.0f, 1000.0f, -200.0f }, { -150.0f, 1000.0f, 250.0f } };
    Vec team0PosB[2] = { { -150.0f, 1000.0f, 250.0f }, { -350.0f, 1000.0f, -200.0f } };
    Vec team1PosA[2] = { { 150.0f, 1000.0f, -200.0f }, { 350.0f, 1000.0f, 250.0f } };
    Vec team1PosB[2] = { { 350.0f, 1000.0f, 250.0f }, { 150.0f, 1000.0f, -200.0f } };
    func_800E1BA8_minigame_ObjData *data;
    EtchNCatchWork *work;
    Vec *pos;
    f32 offsetX;
    f32 offsetZ;
    s8 chr;
    s32 model;
    s32 motion;
    s32 i;

    chr = GwPlayer[D_8010C6D9_etch_n_catch].chr;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][1];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(object, model, motion, D_8010C6D9_etch_n_catch, 0xAA9, 0xAB9);
    data = object->data;
    D_800EB784_minigame[data->unk59][0] = -1;
    D_800EB784_minigame[data->unk59][1] = -1;
    data->unk3C = 0.0f;
    D_8010C868_etch_n_catch[D_8010C6D9_etch_n_catch] = work = HuMemAllocTag(sizeof(EtchNCatchWork), TAG_OVERLAY);
    memset(work, 0, sizeof(EtchNCatchWork));
    func_80108B20_etch_n_catch(work);
    object->rot.y = 0.0f;
    object->rot.x = object->rot.z = object->rot.y;
    object->scale.x = object->scale.y = object->scale.z = 0.75f;
    if (D_8010C6D9_etch_n_catch == 0) {
        D_8010C830_etch_n_catch = (rand8() * 10) >> 8;
    }
    switch (GwPlayer[data->unk59].group) {
        case 0:
            if (!(D_8010C830_etch_n_catch & 1)) {
                pos = &team0PosA[D_8010C6DA_etch_n_catch[0]];
            } else {
                pos = &team0PosB[D_8010C6DA_etch_n_catch[0]];
            }
            object->trans.x = pos->x;
            object->trans.y = pos->y;
            object->trans.z = pos->z;
            work->unk_02 = 8;
            work->unk_01 = 3;
            if (D_8010C6DA_etch_n_catch[0] == 0) {
                work->unk_00 = 1;
            } else {
                work->unk_00 = 2;
            }
            func_800E149C_minigame(object, 0, 2);
            func_800E149C_minigame(object, 1, 1);
            D_8010C6DA_etch_n_catch[0]++;
            break;
        case 1:
            if (!(D_8010C830_etch_n_catch & 1)) {
                pos = &team1PosA[D_8010C6DA_etch_n_catch[1]];
            } else {
                pos = &team1PosB[D_8010C6DA_etch_n_catch[1]];
            }
            object->trans.x = pos->x;
            object->trans.y = pos->y;
            object->trans.z = pos->z;
            work->unk_02 = 1;
            work->unk_01 = 12;
            if (D_8010C6DA_etch_n_catch[1] == 0) {
                work->unk_00 = 4;
            } else {
                work->unk_00 = 8;
            }
            func_800E149C_minigame(object, 0, 1);
            func_800E149C_minigame(object, 1, 2);
            D_8010C6DA_etch_n_catch[1]++;
            break;
    }
    work->unk_0A = 0;
    work->unk_08 = 0;
    work->unk_14 = 0;
    work->unk_18 = 0;
    work->unk_17 = 0;
    work->unk_1C = 0;
    work->unk_12 = 0;
    work->unk_10 = 0;
    object->func = func_80106A64_etch_n_catch;
    offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
    offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
    Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    if (work->unk_02 == 8) {
        object->model[2] = func_8000B108_main(0x330000, 0xAB9);
    } else {
        object->model[2] = func_8000B108_main(0x330001, 0xAB9);
    }
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    func_8001C814_main(object->model[2], 2, 1);
    object->model[3] = func_8000B108_main(3, 0x89D);
    object->model[4] = func_8000B108_main(4, 0x89D);
    for (i = 0; i < 3; i++) {
        if (i == 0 && data->unk59 == 0) {
            D_80111390_etch_n_catch[0][0] = func_8000B0D4_main(0x330006, 0x28D);
        } else {
            D_80111390_etch_n_catch[data->unk59][i] = Hu3DModelLink(D_80111390_etch_n_catch[0][0]);
        }
        func_8001C814_main(D_80111390_etch_n_catch[data->unk59][i], 2, 2);
        func_8001FA68_main(D_80111390_etch_n_catch[data->unk59][i]);
    }
    func_800E1328_minigame(object, 46.875f);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0x47), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 0x48), 1, 0);
    func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, 0x2F), 1, 120);
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, 0x36), 1, 120);
    func_800E5A00_minigame(object, 38, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5690_minigame(object, 0);
    D_8010C6D9_etch_n_catch++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80106334_etch_n_catch);
#endif

void func_80106A64_etch_n_catch(omObjData *object) {
    EtchNCatchNode *nodes[32];
    Vec pos;
    Vec2f screenPos;
    Vec2f dir;
    EtchNCatchPlayerOffsets saved;
    func_800E1BA8_minigame_ObjData *data;
    func_800E1BA8_minigame_ObjData *otherData;
    EtchNCatchNode *newNode;
    EtchNCatchNode *node;
    f32 offsetX;
    f32 offsetZ;
    s32 buttons;
    s32 side;
    s32 found;
    s32 count;
    s32 i;
    s32 j;
    s16 gridX;
    s16 gridY;

    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    if (func_800E6E8C_minigame() == 5) {
        return;
    }
    data = object->data;
    D_8010C838_etch_n_catch = D_8010C868_etch_n_catch[data->unk59];
    if (func_800E6E8C_minigame() == 0) {
        if (D_8010C860_etch_n_catch[0]->work[0] != 3) {
            Hu3DModelScaleSet(object->model[1], 0.0f, 0.0f, 0.0f);
        } else {
            object->trans.y -= D_8010C834_etch_n_catch + 5.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
            } else if (data->unk59 == 0) {
                D_8010C834_etch_n_catch += 5.0f;
                D_8010C6DC_etch_n_catch += 0.05f;
                if (D_8010C6DC_etch_n_catch > 0.75f) {
                    D_8010C6DC_etch_n_catch = 0.75f;
                }
            }
            func_800DDD94_minigame(object);
            Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
            func_8010C628_etch_n_catch(object, 0.75f);
            offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
            offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
            Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            Hu3DModelScaleSet(object->model[1], D_8010C6DC_etch_n_catch, object->scale.y, D_8010C6DC_etch_n_catch);
        }
        return;
    }
    buttons = D_800D5558_main[data->unk57];
    D_800D5558_main[data->unk57] = 0;
    if (object->trans.x < 0.0f) {
        side = 0;
    } else {
        side = 1;
    }
    if (D_8010C858_etch_n_catch[side]->work[0] >= 6 || D_8010C860_etch_n_catch[side]->work[0] != 3) {
        D_800CBB6E_main[data->unk57] = 0;
        D_800D20A1_main[data->unk57] = 0;
    }
    if (GwPlayer[data->unk59].stat & 1) {
        func_80107EA4_etch_n_catch(object);
    }
    data->unk40 *= 0.9f;
    func_8010880C_etch_n_catch(data);
    for (i = 0; i < 4; i++) {
        saved.x[i] = D_800EC598_minigame[i]->trans.x;
        saved.z[i] = D_800EC598_minigame[i]->trans.z;
        otherData = D_800EC598_minigame[i]->data;
        saved.offsetX[i] = sindf(otherData->unk3C) * 46.875f;
        saved.offsetZ[i] = cosdf(otherData->unk3C) * 46.875f;
        D_800EC598_minigame[i]->trans.x -= saved.offsetX[i];
        D_800EC598_minigame[i]->trans.z -= saved.offsetZ[i];
    }
    func_800DDD94_minigame(object);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i]->trans.x += saved.offsetX[i];
        D_800EC598_minigame[i]->trans.z += saved.offsetZ[i];
    }
    offsetX = sindf(data->unk3C) * 65.0f * 0.75f;
    offsetZ = cosdf(data->unk3C) * 65.0f * 0.75f;
    switch (func_800E6E8C_minigame()) {
        case 3:
            if (func_800E6E9C_minigame() == 0) {
                func_800E1328_minigame(object, 60.0f);
                object->trans.x -= offsetX;
                object->trans.z -= offsetZ;
            }
            if (data->unk3C == 0.0f) {
                Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
            } else {
                Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            }
            break;
        case 4:
        case 5:
            Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
            break;
        default:
            Hu3DModelPosSet(object->model[1], object->trans.x - offsetX, 0.0f, object->trans.z - offsetZ);
            break;
    }
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[2], object->rot.x, data->unk3C, object->rot.z);
    if (func_800E4A90_minigame(object) == 2) {
        func_8001C814_main(object->model[2], 2, 1);
    } else {
        func_8001C814_main(object->model[2], 2, 2);
    }
    switch (func_800E6E8C_minigame()) {
        case 0:
        case 1:
        case 5:
            func_8010C628_etch_n_catch(object, 0.75f);
            return;
        case 3:
            if (func_800E6E9C_minigame() == 0) {
                func_8001C258_main(object->model[2], 4, 4);
                func_800E5690_minigame(object, 38);
            }
            data->unk3C = func_8010C4F8_etch_n_catch(data->unk3C);
            if (data->unk3C < 0.0f) {
                data->unk3C += 360.0f;
            } else if (data->unk3C > 360.0f) {
                data->unk3C -= 360.0f;
            }
            if (data->unk3C > 10.0f && data->unk3C < 180.0f) {
                data->unk3C -= 10.0f;
            } else if (data->unk3C >= 180.0f && data->unk3C < 350.0f) {
                data->unk3C += 10.0f;
            } else {
                data->unk3C = 0.0f;
            }
            func_8010C628_etch_n_catch(object, 0.75f);
            break;
    }
    pos.x = object->trans.x;
    pos.y = object->trans.y;
    pos.z = object->trans.z;
    func_80012B14_main(0, &pos, &screenPos);
    if (D_8010C838_etch_n_catch->unk_08 != D_8010C838_etch_n_catch->unk_04 ||
        D_8010C838_etch_n_catch->unk_0A != D_8010C838_etch_n_catch->unk_06) {
        D_8010C838_etch_n_catch->unk_08 = D_8010C838_etch_n_catch->unk_04;
        D_8010C838_etch_n_catch->unk_0A = D_8010C838_etch_n_catch->unk_06;
    }
    D_8010C838_etch_n_catch->unk_04 = screenPos.x;
    D_8010C838_etch_n_catch->unk_06 = screenPos.y;
    if (func_800E6E8C_minigame() == 2) {
        if (D_8010C838_etch_n_catch->unk_12 == 0 && (data->unk5C & 4) && Hu3DData[object->model[0]].motTime == 0.0f) {
            D_8010C838_etch_n_catch->unk_10 = PlayerFXPlay(0x37F, data->unk59);
            if (D_8010C838_etch_n_catch->unk_02 == 8) {
                HuAudFXPanning(D_8010C838_etch_n_catch->unk_10, 32);
            } else {
                HuAudFXPanning(D_8010C838_etch_n_catch->unk_10, 95);
            }
            D_8010C838_etch_n_catch->unk_12 = 1;
        } else if (D_8010C838_etch_n_catch->unk_12 == 1 && data->unk40 == D_800EB770_minigame) {
            HuAudFXStop(D_8010C838_etch_n_catch->unk_10);
            D_8010C838_etch_n_catch->unk_12 = 0;
        }
    } else if (func_800E6E8C_minigame() == 3) {
        HuAudFXStop(D_8010C838_etch_n_catch->unk_10);
        D_8010C838_etch_n_catch->unk_12 = 0;
    }
    if (func_800E6E8C_minigame() == 2 && D_8010C838_etch_n_catch->unk_08 != 0 && D_8010C838_etch_n_catch->unk_0A != 0) {
        while (D_8010C838_etch_n_catch->unk_08 != D_8010C838_etch_n_catch->unk_04 ||
               D_8010C838_etch_n_catch->unk_0A != D_8010C838_etch_n_catch->unk_06) {
            newNode = func_80108B28_etch_n_catch(data->unk59);
            memset(newNode, 0, sizeof(EtchNCatchNode));
            newNode->unk_00 = 1;
            newNode->unk_16 = 106;
            newNode->unk_18 = D_8010C838_etch_n_catch->unk_08;
            newNode->unk_1A = D_8010C838_etch_n_catch->unk_0A;
            newNode->unk_1C = data->unk59;
            newNode->unk_10 = NULL;
            newNode->unk_0C = NULL;
            newNode->unk_08 = NULL;
            newNode->unk_04 = NULL;
            func_80108B64_etch_n_catch(&D_8010C838_etch_n_catch->unk_0C, newNode);
            newNode->unk_2C = 0;
            newNode->unk_30 = 1.0f;
            switch (rand8() >> 6) {
                case 0:
                    newNode->unk_20.x = object->trans.x + 10.0f;
                    newNode->unk_20.z = object->trans.z + 10.0f;
                    break;
                case 1:
                    newNode->unk_20.x = object->trans.x - 10.0f;
                    newNode->unk_20.z = object->trans.z - 10.0f;
                    break;
                case 2:
                    newNode->unk_20.x = object->trans.x + 10.0f;
                    newNode->unk_20.z = object->trans.z - 10.0f;
                    break;
                default:
                    newNode->unk_20.x = object->trans.x - 10.0f;
                    newNode->unk_20.z = object->trans.z + 10.0f;
                    break;
            }
            newNode->unk_20.y = object->trans.y;
            if (func_80109114_etch_n_catch(D_8010C838_etch_n_catch->unk_08, D_8010C838_etch_n_catch->unk_0A) ==
                D_8010C838_etch_n_catch->unk_02) {
                found = 0;
                for (i = 0; i < 4; i++) {
                    if (found == 1) {
                        break;
                    }
                    for (node = D_8010C868_etch_n_catch[i]->unk_0C; node != NULL; node = node->unk_08) {
                        if (newNode != node && node->unk_18 == newNode->unk_18 && node->unk_1A == newNode->unk_1A) {
                            while (node->unk_0C != NULL) {
                                node = node->unk_0C;
                            }
                            found = 1;
                            node->unk_0C = newNode;
                            newNode->unk_10 = node;
                            break;
                        }
                    }
                }
            }
            newNode->unk_14 |= D_8010C838_etch_n_catch->unk_00;
            func_8010914C_etch_n_catch(D_8010C838_etch_n_catch->unk_08, D_8010C838_etch_n_catch->unk_0A,
                                       D_8010C838_etch_n_catch->unk_02);
            newNode->unk_15 = D_8010C838_etch_n_catch->unk_02;
            D_8010C890_etch_n_catch[D_8010C838_etch_n_catch->unk_06 / 2][D_8010C838_etch_n_catch->unk_04 / 2] |=
                D_8010C838_etch_n_catch->unk_00;
            if ((D_800CBB6E_main[data->unk57] != 0 || D_800D20A1_main[data->unk57] != 0) &&
                func_80108C08_etch_n_catch(D_8010C838_etch_n_catch)) {
                if (object->trans.x < 0.0f) {
                    D_8010C6E0_etch_n_catch = 1;
                } else {
                    D_8010C6E1_etch_n_catch = 1;
                }
            }
            dir = func_8010C574_etch_n_catch(D_8010C838_etch_n_catch->unk_08, D_8010C838_etch_n_catch->unk_0A,
                                             D_8010C838_etch_n_catch->unk_04, D_8010C838_etch_n_catch->unk_06);
            if (dir.x <= -0.5f) {
                D_8010C838_etch_n_catch->unk_08--;
            } else if (dir.x >= 0.5f) {
                D_8010C838_etch_n_catch->unk_08++;
            }
            if (dir.y <= -0.5f) {
                D_8010C838_etch_n_catch->unk_0A--;
            } else if (dir.y >= 0.5f) {
                D_8010C838_etch_n_catch->unk_0A++;
            }
        }
    }
    if (data->unk59 == 3) {
        if (D_8010C6E2_etch_n_catch == 0 && D_8010C6E0_etch_n_catch != 0 && D_8010C860_etch_n_catch[0]->work[0] == 3 &&
            D_8010C858_etch_n_catch[0]->work[0] < 5) {
            D_8010C858_etch_n_catch[0]->work[1] =
                func_80108DD0_etch_n_catch(D_8010C850_etch_n_catch[0][0], D_8010C850_etch_n_catch[0][1]);
            if (D_8010C858_etch_n_catch[0]->work[1] != 0) {
                D_8010C858_etch_n_catch[0]->work[0] = 5;
                for (i = 0; i < 4; i++) {
                    if (D_8010C868_etch_n_catch[i]->unk_01 == 3) {
                        otherData = D_800EC598_minigame[i]->data;
                        omVibrate(otherData->unk59, 2, 3, 10);
                    }
                }
            }
            D_8010C6E0_etch_n_catch = 0;
        } else if (D_8010C6E2_etch_n_catch != 0 && D_8010C6E1_etch_n_catch != 0 &&
                   D_8010C860_etch_n_catch[1]->work[0] == 3 && D_8010C858_etch_n_catch[1]->work[0] < 5) {
            D_8010C858_etch_n_catch[1]->work[1] =
                func_80108DD0_etch_n_catch(D_8010C850_etch_n_catch[1][0], D_8010C850_etch_n_catch[1][1]);
            if (D_8010C858_etch_n_catch[1]->work[1] != 0) {
                D_8010C858_etch_n_catch[1]->work[0] = 5;
                for (i = 0; i < 4; i++) {
                    if (D_8010C868_etch_n_catch[i]->unk_01 == 12) {
                        otherData = D_800EC598_minigame[i]->data;
                        omVibrate(otherData->unk59, 2, 3, 10);
                    }
                }
            }
            D_8010C6E1_etch_n_catch = 0;
        }
        D_8010C6E2_etch_n_catch ^= 1;
    }
    func_8010C628_etch_n_catch(object, 0.75f);
    gridX = D_8010C850_etch_n_catch[side][0] * 2;
    gridY = D_8010C850_etch_n_catch[side][1] * 2;
    if (func_8010B154_etch_n_catch(gridX, gridY)) {
        for (i = 0; i < 32; i++) {
            nodes[i] = NULL;
        }
        count = 0;
        for (node = D_8010C838_etch_n_catch->unk_0C; node != NULL; node = node->unk_08) {
            if (IABS(gridX - node->unk_18) < 2 && IABS(gridY - node->unk_1A) < 2) {
                nodes[count++] = node;
            }
        }
        for (i = 0; i < count; i++) {
            for (node = nodes[i]; node != NULL; node = node->unk_04) {
                node->unk_16 = 17;
            }
        }
    }
    if (data->unk59 == 3) {
        for (j = 0; j < 4; j++) {
            D_8010C838_etch_n_catch = D_8010C868_etch_n_catch[j];
            if (D_8010C838_etch_n_catch != NULL) {
                for (node = D_8010C838_etch_n_catch->unk_0C; node != NULL; node = node->unk_08) {
                    node->unk_16--;
                    if (node->unk_16 <= 16) {
                        if (node->unk_16 == 16) {
                            for (i = 0; i < 4; i++) {
                                if (node->unk_0C != NULL) {
                                    if (node->unk_0C->unk_15 != D_8010C868_etch_n_catch[i]->unk_02) {
                                        D_8010C890_etch_n_catch[node->unk_1A / 2][node->unk_18 / 2] &=
                                            ~D_8010C868_etch_n_catch[i]->unk_00;
                                    }
                                } else {
                                    D_8010C890_etch_n_catch[node->unk_1A / 2][node->unk_18 / 2] &=
                                        ~D_8010C868_etch_n_catch[i]->unk_00;
                                }
                            }
                            func_80109370_etch_n_catch(node, D_8010C838_etch_n_catch->unk_02);
                        } else if (node->unk_16 > 0) {
                            if (node->unk_1E != -1) {
                                func_801097B4_etch_n_catch(node);
                            }
                        } else {
                            func_8001C258_main(node->unk_1E, 4, 4);
                            func_80108BCC_etch_n_catch(&D_8010C838_etch_n_catch->unk_0C, node);
                        }
                    }
                }
            }
        }
        D_800D5558_main[data->unk57] = buttons;
    }
}

s32 func_80107D38_etch_n_catch(f32 x, f32 z, EtchNCatchWork *work) {
    s32 result;

    if (work->unk_01 == 3) {
        if (x < -80.0f && x > -450.0f && z < 300.0f && z > -400.0f) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    } else {
        if (x > 80.0f && x < 450.0f && z < 300.0f && z > -400.0f) {
            result = FALSE;
        } else {
            result = TRUE;
        }
    }
    return result;
}

void func_80107EA4_etch_n_catch(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    EtchNCatchWork *work = D_8010C868_etch_n_catch[data->unk59];
    omObjData *target;
    Vec2f dir;
    f32 radius;
    f32 dx;
    f32 dz;
    f32 x;
    f32 z;
    s8 speed;
    s32 side;

    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    switch (GwPlayer[data->unk59].cpu_difficulty) {
        case 3:
            speed = 60;
            radius = 200.0f;
            break;
        case 2:
            speed = 60;
            radius = 250.0f;
            break;
        case 1:
        default:
            speed = 57;
            radius = 300.0f;
            break;
        case 0:
            speed = 54;
            radius = 350.0f;
            break;
    }
    side = (object->trans.x < 0.0f) ? 0 : 1;
    if (D_8010C858_etch_n_catch[side]->work[0] >= 6 || D_8010C860_etch_n_catch[side]->work[0] != 3) {
        D_800CBB6E_main[data->unk57] = 0;
        D_800D20A1_main[data->unk57] = 0;
        return;
    }
    if (object->trans.x < 0.0f) {
        target = D_8010C858_etch_n_catch[0];
    } else {
        target = D_8010C858_etch_n_catch[1];
    }
    dx = ABS(target->trans.x - object->trans.x);
    dz = ABS(target->trans.z - object->trans.z);
    if (HuSqrtf(dx * dx + dz * dz) > 375.0f) {
        D_8010C6E4_etch_n_catch[data->unk59] = 0;
    }
    switch (D_8010C6E4_etch_n_catch[data->unk59]) {
        case 0:
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                dir = func_8010C574_etch_n_catch(object->trans.x, object->trans.z, target->trans.x, target->trans.z - 75.0f);
            } else {
                dir = func_8010C574_etch_n_catch(object->trans.x, object->trans.z, target->trans.x, target->trans.z + 75.0f);
            }
            D_800CBB6E_main[data->unk57] = speed * dir.x;
            D_800D20A1_main[data->unk57] = -(speed * dir.y);
            dx = ABS(target->trans.x - object->trans.x);
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                dz = ABS(target->trans.z - 75.0f - object->trans.z);
            } else {
                dz = ABS(target->trans.z + 75.0f - object->trans.z);
            }
            if (HuSqrtf(dx * dx + dz * dz) < 50.0f) {
                D_8010C6E4_etch_n_catch[data->unk59] = 1;
            }
            break;
        case 1:
            if (work->unk_00 == 1 || work->unk_00 == 4) {
                data->unk3C = func_8010C4F8_etch_n_catch(data->unk3C);
                if (ABS(data->unk3C - 90.0f) < 5.0f) {
                    data->unk3C = 90.0f;
                    D_8010C6E4_etch_n_catch[data->unk59] = 2;
                } else {
                    D_800CBB6E_main[data->unk57] = speed / 2;
                    D_800D20A1_main[data->unk57] = 0;
                }
            }
            if (work->unk_00 == 2 || work->unk_00 == 8) {
                data->unk3C = func_8010C4F8_etch_n_catch(data->unk3C);
                if (ABS(data->unk3C - 270.0f) < 5.0f) {
                    data->unk3C = 270.0f;
                    D_8010C6E4_etch_n_catch[data->unk59] = 2;
                } else {
                    D_800CBB6E_main[data->unk57] = -speed / 2;
                    D_800D20A1_main[data->unk57] = 0;
                }
            }
            break;
        case 2:
            data->unk3C += 5.0f;
            if (data->unk3C > 360.0f) {
                data->unk3C -= 360.0f;
            }
            x = sindf(data->unk3C) * (radius + 75.0f) + target->trans.x;
            z = cosdf(data->unk3C) * (radius + 75.0f) + target->trans.z;
            dir = func_8010C574_etch_n_catch(object->trans.x, object->trans.z, x, z);
            D_800CBB6E_main[data->unk57] = speed * dir.x;
            D_800D20A1_main[data->unk57] = -(speed * dir.y);
            break;
    }
    x = sindf(data->unk3C) * 65.0f * 0.75f + object->trans.x;
    z = cosdf(data->unk3C) * 65.0f * 0.75f + object->trans.z;
    if (func_80107D38_etch_n_catch(x, z, work)) {
        data->unk3C += 20.0f;
        if (data->unk3C > 360.0f) {
            data->unk3C -= 360.0f;
        }
        x = sindf(data->unk3C) * 10.0f + object->trans.x;
        z = cosdf(data->unk3C) * 10.0f + object->trans.z;
        dir = func_8010C574_etch_n_catch(object->trans.x, object->trans.z, x, z);
        D_800CBB6E_main[data->unk57] = speed * dir.x;
        D_800D20A1_main[data->unk57] = -(speed * dir.y);
    }
}

void func_8010880C_etch_n_catch(func_800E1BA8_minigame_ObjData *data) {
    f32 stickX = D_800CBB6E_main[data->unk57];
    f32 stickY = -D_800D20A1_main[data->unk57];
    f32 angle;
    f32 diff;
    f32 magnitude;

    if (FABS(stickX) < 8.0f && FABS(stickY) < 8.0f) {
        angle = data->unk3C;
    } else {
        angle = atan2df(stickX, stickY);
    }
    angle = func_8010C4F8_etch_n_catch(angle);
    data->unk3C = func_8010C4F8_etch_n_catch(data->unk3C);
    diff = angle - data->unk3C;
    if (ABS(diff) > 30.0f) {
        if ((diff > 0.0f && diff < 180.0f) || (diff < -180.0f && diff > -360.0f)) {
            angle = data->unk3C + 30.0f;
        } else {
            angle = data->unk3C - 30.0f;
        }
    } else {
        angle = diff + data->unk3C;
    }
    angle = func_8010C4F8_etch_n_catch(angle);
    magnitude = HuSqrtf(stickX * stickX + stickY * stickY);
    D_800CBB6E_main[data->unk57] = sindf(angle) * magnitude;
    D_800D20A1_main[data->unk57] = -cosdf(angle) * magnitude;
}

void func_80108B20_etch_n_catch(EtchNCatchWork *arg0) {
    arg0->unk_0C = NULL;
}

EtchNCatchNode *func_80108B28_etch_n_catch(s8 playerId) {
    EtchNCatchNode *node = D_801113D8_etch_n_catch[playerId];
    s32 i;

    for (i = 0; i < 0x100; i++) {
        if (node->unk_00 == 0) {
            break;
        }
        node++;
    }
    return node;
}

void func_80108B64_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    EtchNCatchNode *prev = *head;

    if (prev != NULL) {
        while (prev->unk_08 != NULL) {
            prev = prev->unk_08;
        }
        node->unk_08 = prev->unk_08;
        node->unk_04 = prev;
        prev->unk_08 = node;
        if (node->unk_08 != NULL) {
            node->unk_08->unk_04 = node;
        }
        return;
    }

    node->unk_08 = *head;
    node->unk_04 = NULL;
    *head = node;
    if (prev != NULL) {
        prev->unk_04 = node;
    }
}

void func_80108BCC_etch_n_catch(EtchNCatchNode **head, EtchNCatchNode *node) {
    if (node->unk_08 != NULL) {
        node->unk_08->unk_04 = node->unk_04;
    }
    if (node->unk_04 != NULL) {
        node->unk_04->unk_08 = node->unk_08;
    } else {
        *head = node->unk_08;
    }
    node->unk_00 = 0;
}

s32 func_80108C08_etch_n_catch(EtchNCatchWork *work) {
    EtchNCatchNode *node;
    s32 count = 0;
    s32 i;

    if (D_8010C868_etch_n_catch[0]->unk_0C == NULL && D_8010C868_etch_n_catch[1]->unk_0C == NULL &&
        D_8010C868_etch_n_catch[2]->unk_0C == NULL && D_8010C868_etch_n_catch[3]->unk_0C == NULL) {
        return FALSE;
    }
    for (i = 0; i < 4; i++) {
        for (node = D_8010C868_etch_n_catch[i]->unk_0C; node != NULL; node = node->unk_08) {
            if (node->unk_18 == work->unk_04 - 1) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (node->unk_18 == work->unk_04) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (node->unk_18 == work->unk_04 + 1) {
                count += node->unk_1A == work->unk_06 - 1;
                count += node->unk_1A == work->unk_06;
                count += node->unk_1A == work->unk_06 + 1;
            }
            if (count >= 3) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

// Undoes the "filled" mark on every grid cell appended to the touched-cell list
// up to (but not including) arg0.
void func_80108D84_etch_n_catch(u8 **arg0, u8 *arg1) {
    u8 **cellPtr = D_8010C878_etch_n_catch;
    // arg0 points one past the last appended cell, so the difference is a byte offset.
    s32 count = ((s32)arg0 - (s32)cellPtr) >> 2;
    s32 i;

    for (i = 0; i < count; i++) {
        u8 *cell = *cellPtr++;
        if (cell[0] == ETCH_N_CATCH_CELL_FILLED) {
            cell[0] = 0;
        }
    }
}

#ifdef NON_MATCHING
s32 func_80108DD0_etch_n_catch(s16 x, s16 y) {
    u8 **list;
    u8 **readBuf;
    u8 **writeBuf;
    u8 **read;
    u8 **write;
    u8 *cell;
    s32 count;
    s32 i;
    s32 offset;
    s32 row;
    s32 col;
    s32 flags = 0;

    cell = D_8010C84C_etch_n_catch + x * 2 + y * (D_8010C846_etch_n_catch << 1);
    list = D_8010C878_etch_n_catch;
    *cell = ETCH_N_CATCH_CELL_FILLED;
    read = D_8010C87C_etch_n_catch[0];
    *read = *list++ = cell;
    count = 1;
    write = writeBuf = D_8010C87C_etch_n_catch[1];
    read = readBuf = D_8010C87C_etch_n_catch[0];
    while (count != 0) {
        for (i = 0; i < count; i++) {
            cell = *read++;
            *cell = ETCH_N_CATCH_CELL_FILLED;
            offset = cell - D_8010C84C_etch_n_catch;
            row = offset / 320;
            col = offset % 320;
            col >>= 1;
            row >>= 1;
            cell++;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                func_80108D84_etch_n_catch(list, cell);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= D_8010C890_etch_n_catch[row][col + 1];
            }
            cell -= 2;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                func_80108D84_etch_n_catch(list, cell);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= D_8010C890_etch_n_catch[row][col - 1];
            }
            cell += D_8010C846_etch_n_catch + 1;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                func_80108D84_etch_n_catch(list, cell);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= D_8010C890_etch_n_catch[row + 1][col];
            }
            cell -= D_8010C846_etch_n_catch * 2;
            if (*cell == 0) {
                *cell = ETCH_N_CATCH_CELL_FILLED;
                *write++ = *list++ = cell;
            } else if (*cell == ETCH_N_CATCH_CELL_EDGE) {
                func_80108D84_etch_n_catch(list, cell);
                return FALSE;
            } else if ((*cell & 9) == 0) {
                *list++ = cell;
            } else {
                flags |= D_8010C890_etch_n_catch[row - 1][col];
            }
        }
        count = write - writeBuf;
        write = readBuf;
        readBuf = writeBuf;
        writeBuf = write;
        read = readBuf;
    }
    func_80108D84_etch_n_catch(list, cell);
    return flags == 3 || flags == 12;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_80108DD0_etch_n_catch);
#endif

u8 *func_801090E0_etch_n_catch(s16 x, s16 y) {
    return D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
}

u8 func_80109114_etch_n_catch(s16 x, s16 y) {
    u8 *p = D_8010C84C_etch_n_catch + D_8010C846_etch_n_catch * y + x;
    return *p;
}

#ifdef NON_MATCHING
void func_8010914C_etch_n_catch(s16 x, s16 y, s32 value) {
    u8 *cell;

    *func_801090E0_etch_n_catch(x, y) = value;
    cell = func_801090E0_etch_n_catch(x - 1, y);
    if (*cell != (u8)value) {
        *cell = value * 2;
    }
    cell = func_801090E0_etch_n_catch(x + 1, y);
    if (*cell != (u8)value) {
        *cell = value * 2;
    }
    cell = func_801090E0_etch_n_catch(x, y - 1);
    if (*cell != (u8)value) {
        *cell = value * 2;
    }
    cell = func_801090E0_etch_n_catch(x, y + 1);
    if (*cell != (u8)value) {
        *cell = value * 2;
    }
    cell = func_801090E0_etch_n_catch(x - 1, y - 1);
    if (*cell != (u8)value && *cell != (u8)value * 2) {
        *cell = value * 4;
    }
    cell = func_801090E0_etch_n_catch(x - 1, y + 1);
    if (*cell != (u8)value && *cell != (u8)value * 2) {
        *cell = value * 4;
    }
    cell = func_801090E0_etch_n_catch(x + 1, y + 1);
    if (*cell != (u8)value && *cell != (u8)value * 2) {
        *cell = value * 4;
    }
    cell = func_801090E0_etch_n_catch(x + 1, y - 1);
    if (*cell != (u8)value && *cell != (u8)value * 2) {
        *cell = value * 4;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010914C_etch_n_catch);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C740_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C758_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C770_etch_n_catch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", D_8010C788_etch_n_catch);

void func_80109370_etch_n_catch(EtchNCatchNode *node, u8 value) {
    u8 *cells[8];
    u8 *cell;
    s32 x;
    s32 y;
    s32 i;

    cell = func_801090E0_etch_n_catch(node->unk_18, node->unk_1A);
    if (node->unk_0C == NULL && node->unk_10 == NULL) {
        *cell = 0;
    }
    if (node->unk_10 != NULL && node->unk_0C != NULL) {
        node->unk_10->unk_0C = node->unk_0C;
        node->unk_0C->unk_10 = node->unk_10;
    } else if (node->unk_10 != NULL && node->unk_0C == NULL) {
        node->unk_10->unk_0C = NULL;
    } else if (node->unk_10 == NULL && node->unk_0C != NULL) {
        node->unk_0C->unk_10 = NULL;
    }
    for (i = 0; i < 8; i++) {
        switch (i) {
            case 0:
                x = node->unk_18;
                y = node->unk_1A - 1;
                break;
            case 1:
                x = node->unk_18;
                y = node->unk_1A + 1;
                break;
            case 2:
                x = node->unk_18 - 1;
                y = node->unk_1A;
                break;
            case 3:
                x = node->unk_18 + 1;
                y = node->unk_1A;
                break;
            case 4:
                x = node->unk_18 - 1;
                y = node->unk_1A - 1;
                break;
            case 5:
                x = node->unk_18 + 1;
                y = node->unk_1A + 1;
                break;
            case 6:
                x = node->unk_18 - 1;
                y = node->unk_1A + 1;
                break;
            default:
                x = node->unk_18 + 1;
                y = node->unk_1A - 1;
                break;
        }
        cell = func_801090E0_etch_n_catch(x, y);
        if (node->unk_10 != NULL || node->unk_0C != NULL) {
            if (i >= 0) {
                if (i < 4) {
                    if (*cell != value) {
                        *cell = value << 1;
                    }
                } else if (i < 8) {
                    if (*cell != value && *cell != value * 2) {
                        *cell = value << 2;
                    }
                }
            }
        }
        cells[0] = func_801090E0_etch_n_catch(x, y + 1);
        cells[1] = func_801090E0_etch_n_catch(x, y - 1);
        cells[2] = func_801090E0_etch_n_catch(x - 1, y);
        cells[3] = func_801090E0_etch_n_catch(x + 1, y);
        cells[4] = func_801090E0_etch_n_catch(x - 1, y - 1);
        cells[5] = func_801090E0_etch_n_catch(x + 1, y + 1);
        cells[6] = func_801090E0_etch_n_catch(x - 1, y + 1);
        cells[7] = func_801090E0_etch_n_catch(x + 1, y - 1);
        if (*cells[0] != value && *cells[1] != value && *cells[2] != value && *cells[3] != value &&
            *cells[4] != value && *cells[5] != value && *cells[6] != value && *cells[7] != value) {
            *cell = 0;
        } else if (*cells[0] == value || *cells[1] == value || *cells[2] == value || *cells[3] == value) {
            if (*cell != value) {
                *cell = value << 1;
            }
        } else if (*cells[4] == value || *cells[5] == value || *cells[6] == value || *cells[7] == value) {
            if (*cell != value && *cell != value * 2) {
                *cell = value << 2;
            }
        }
    }
}

void func_801097B4_etch_n_catch(EtchNCatchNode *node) {
    if (node->unk_2C == 0) {
        if (D_8010C6F4_etch_n_catch[node->unk_1C] == 0) {
            if (D_8010C6E8_etch_n_catch[node->unk_1C][0] == 0) {
                node->unk_1E = D_80111390_etch_n_catch[node->unk_1C][0];
                node->unk_34 = 0;
                D_8010C6E8_etch_n_catch[node->unk_1C][0] = 1;
            } else if (D_8010C6E8_etch_n_catch[node->unk_1C][1] == 0) {
                node->unk_1E = D_80111390_etch_n_catch[node->unk_1C][1];
                node->unk_34 = 1;
                D_8010C6E8_etch_n_catch[node->unk_1C][1] = 1;
            } else if (D_8010C6E8_etch_n_catch[node->unk_1C][2] == 0) {
                node->unk_1E = D_80111390_etch_n_catch[node->unk_1C][2];
                node->unk_34 = 2;
                D_8010C6E8_etch_n_catch[node->unk_1C][2] = 1;
            } else {
                node->unk_1E = -1;
                node->unk_34 = 0xFF;
            }
        } else {
            node->unk_1E = -1;
            node->unk_34 = 0xFF;
        }
        D_8010C6F4_etch_n_catch[node->unk_1C]++;
        if (D_8010C6F4_etch_n_catch[node->unk_1C] > 8) {
            D_8010C6F4_etch_n_catch[node->unk_1C] = 0;
        }
    }
    if (node->unk_1E != -1) {
        node->unk_2C++;
        node->unk_30 += 0.05f;
        if (node->unk_30 > 1.5f) {
            node->unk_30 = 1.5f;
        }
        Hu3DModelScaleSet(node->unk_1E, node->unk_30, node->unk_30, node->unk_30);
        Hu3DModelPosSet(node->unk_1E, node->unk_20.x, node->unk_20.y, node->unk_20.z);
        node->unk_20.y += 5.0f;
        if (node->unk_2C >= 15) {
            func_8001C258_main(node->unk_1E, 4, 4);
            D_8010C6E8_etch_n_catch[node->unk_1C][node->unk_34] = 0;
        } else {
            func_8001F9E4_main(node->unk_1E, 255 - node->unk_2C * 16);
            func_8001C258_main(node->unk_1E, 4, 0);
        }
    }
}

void func_80109A54_etch_n_catch(omObjData *object) {
    EtchNCatchPlayerData *data;
    s32 file = 0xA0000;
    s32 i;

    if (D_8010C6A0_etch_n_catch == 0) {
        D_8010C83C_etch_n_catch = object->model[0] = func_8000B108_main(0xA0000, 0x8BD);
    } else {
        object->model[0] = Hu3DModelLink(D_8010C83C_etch_n_catch);
    }
    func_8001C258_main(object->model[0], 4, 0);
    object->data = HuMemAllocTag(sizeof(EtchNCatchPlayerData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(EtchNCatchPlayerData));
    data = object->data;
    data->base.unkE8 = HuMemAllocTag(object->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), TAG_OVERLAY);
    data->base.unk5A = object->model[0];
    data->base.unk5B = 0;
    data->unk160 = D_8010C6A0_etch_n_catch % 2;
    data->unk168 = 0.0f;
    func_8000B460_main(object, 2, file | 8);
    func_8000B460_main(object, 3, file);
    Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
    switch (data->unk160) {
        case 0:
            object->trans.x = D_8010C6B0_etch_n_catch[0].x;
            break;
        case 1:
            object->trans.x = -D_8010C6B0_etch_n_catch[0].x;
            break;
    }
    object->trans.y = D_8010C6B0_etch_n_catch[0].y;
    object->trans.z = D_8010C6B0_etch_n_catch[0].z;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->work[0] = 10;
    object->work[1] = 0;
    data->unk15C = 0;
    data->unk164 = 0.5f;
    data->unk170 = data->unk174 = 0.0f;
    data->unk161 = 0;
    if (D_8010C6A0_etch_n_catch == 0) {
        D_8010C83E_etch_n_catch = object->model[6] = func_8000B108_main(9, 0x8BD);
    } else {
        object->model[6] = Hu3DModelLink(D_8010C83E_etch_n_catch);
    }
    Hu3DModelPosSet(object->model[6], object->trans.x, 0.0f, object->trans.z);
    for (i = 0; i < 5; i++) {
        if (i == 0) {
            object->model[1] = func_8000B108_main(0x330006, 0x8AD);
        } else {
            object->model[i + 1] = Hu3DModelLink(object->model[1]);
        }
        func_8001C814_main(object->model[i + 1], 2, 2);
        func_8001FA68_main(object->model[i + 1]);
        data->unk1B4 = 0.0f;
        data->unk178[i].y = 1.0f;
    }
    data->unk178[0].x = 0.8660254f;
    data->unk178[0].z = -0.5f;
    data->unk178[1].x = 0.8660254f;
    data->unk178[1].z = 0.5f;
    data->unk178[2].x = 0.0f;
    data->unk178[2].z = 1.0f;
    data->unk178[3].x = -0.8660254f;
    data->unk178[3].z = 0.5f;
    data->unk178[4].x = -0.8660254f;
    data->unk178[4].z = -0.5f;
    D_801113E8_etch_n_catch[data->unk160] = espEntry(func_8000B838_main(0x330005), 0, 1);
    espAttrSet(D_801113E8_etch_n_catch[data->unk160], 0x5000);
    espPosSet(D_801113E8_etch_n_catch[data->unk160], 0, 0);
    espScaleSet(D_801113E8_etch_n_catch[data->unk160], 0.5f, 0.5f);
    espTPLvlSet(D_801113E8_etch_n_catch[data->unk160], 0xCC);
    espDispOff(D_801113E8_etch_n_catch[data->unk160]);
    object->func = func_80109EB8_etch_n_catch;
    D_8010C6A0_etch_n_catch++;
}

void func_80109EB8_etch_n_catch(omObjData *object) {
    Vec2f screen;
    Vec pos;
    f32 angles[8] = { 1.0f, 46.0f, 91.0f, 136.0f, 181.0f, 226.0f, 271.0f, 316.0f };
    EtchNCatchPlayerData *data = object->data;
    f32 x;
    f32 z;
    s32 i;

    pos.x = object->trans.x;
    pos.y = 0.0f;
    pos.z = object->trans.z;
    func_80012B14_main(0, &pos, &screen);
    D_8010C850_etch_n_catch[data->unk160][0] = screen.x / 2.0f;
    D_8010C850_etch_n_catch[data->unk160][1] = screen.y / 2.0f;
    switch (object->work[0]) {
        case 0:
            object->trans.x = D_8010C860_etch_n_catch[data->unk160]->trans.x;
            object->trans.y = 0.0f;
            object->trans.z = D_8010C860_etch_n_catch[data->unk160]->trans.z;
            pos.x = object->trans.x;
            pos.y = 0.0f;
            pos.z = object->trans.z;
            func_80012B14_main(0, &pos, &screen);
            espPosSet(D_801113E8_etch_n_catch[data->unk160], screen.x, screen.y);
            data->unk164 = 0.5f;
            espScaleSet(D_801113E8_etch_n_catch[data->unk160], data->unk164, data->unk164);
            data->unk170 = data->unk174 = 0.0f;
            espZRotSet(D_801113E8_etch_n_catch[data->unk160], data->unk170);
            espDispOn(D_801113E8_etch_n_catch[data->unk160]);
            func_8001C258_main(object->model[0], 4, 4);
            func_8001C258_main(object->model[6], 4, 4);
            for (i = 0; i < 5; i++) {
                func_8001C258_main(object->model[i + 1], 4, 4);
            }
            data->unk15C = 0;
            object->work[0] = 1;
            break;
        case 5:
            data->unk168 += 2.0f;
            object->trans.y += data->unk168 + 5.0f;
            Hu3DModelPosSet(object->model[0], object->trans.x, 0.0f, object->trans.z);
            Hu3DModelPosSet(object->model[6], object->trans.x, 0.0f, object->trans.z);
            if (D_8010C6F8_etch_n_catch[data->unk160] == 0) {
                if (data->unk160 == 0) {
                    HuAudFXPanning(HuAudFXPlay(0x37D), 0x20);
                } else {
                    HuAudFXPanning(HuAudFXPlay(0x37E), 0x5F);
                }
                data->unk164 = 1.0f;
                Hu3DMotionShiftSet(object->model[0], Hu3DData[object->motion[2]].motId, 0, 1, 2);
                Hu3DMotionTimeSet(object->model[0], 0.0f);
                data->unk15C = 0;
                data->unk1B4 = 0.0f;
                D_8010C6F8_etch_n_catch[data->unk160] = 1;
            } else {
                espDispOff(D_801113E8_etch_n_catch[data->unk160]);
                func_8001C258_main(object->model[0], 4, 0);
                func_8001C258_main(object->model[6], 4, 0);
                for (i = 0; i < 5; i++) {
                    Hu3DMotionTimeSet(object->model[i + 1], 0.0f);
                }
                func_8010AB7C_etch_n_catch(object);
                if (data->unk160 == 0) {
                    D_8010C6AC_etch_n_catch++;
                } else {
                    D_8010C6AD_etch_n_catch++;
                }
                D_8010C6F8_etch_n_catch[data->unk160] = 0;
                data->unk15C = 0;
                object->work[0] = 6;
            }
            break;
        case 6:
            if (data->unk15C < 10) {
                func_8010AB7C_etch_n_catch(object);
            } else {
                for (i = 0; i < 5; i++) {
                    func_8001C258_main(object->model[i + 1], 4, 4);
                }
            }
            if (data->unk15C >= D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 / 2.0f - 2.0f) {
                func_8001C814_main(object->model[0], 2, 1);
                object->work[0] = 8;
                data->unk15C = 0;
            } else {
                data->unk168 += 2.0f;
                object->trans.y += data->unk168 + 5.0f;
                data->unk15C++;
            }
            break;
        case 8:
            data->unk168 += 2.0f;
            object->trans.y += data->unk168 + 5.0f;
            for (i = 0; i < 5; i++) {
                func_8001C258_main(object->model[i + 1], 4, 4);
            }
            object->work[0] = 9;
            D_8010C860_etch_n_catch[data->unk160]->work[0] = 0;
            break;
        case 9:
            for (i = 0; i < 5; i++) {
                func_8001C258_main(object->model[i + 1], 4, 4);
            }
            data->unk15C++;
            object->trans.y += data->unk168 + 5.0f;
            if (object->trans.y > 800.0f && data->unk164 == 0.0f) {
                data->unk168 = 0.0f;
                data->unk15C = 0;
                object->work[0] = 10;
            } else {
                data->unk168 += 2.0f;
                data->unk164 -= 0.05f;
                if (data->unk164 < 0.0f) {
                    data->unk164 = 0.0f;
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelScaleSet(object->model[6], data->unk164, data->unk164, data->unk164);
            break;
        case 10:
            func_8001C258_main(object->model[0], 4, 4);
            func_8001C258_main(object->model[6], 4, 4);
            data->unk164 = 1.0f;
            Hu3DModelScaleSet(object->model[6], data->unk164, data->unk164, data->unk164);
            break;
        default:
            if (func_800E6E8C_minigame() != 0) {
                switch (object->work[0]) {
                    case 1:
                        if (data->unk15C > 120) {
                            data->unk15C = 0;
                            object->work[0] = 2;
                        } else {
                            if (data->unk15C == 0) {
                                data->unk174 = data->unk170;
                            }
                            func_8010AD6C_etch_n_catch(data);
                            data->unk15C++;
                        }
                        break;
                    case 2:
                        if (data->unk15C > 16) {
                            data->unk15C = 0;
                            data->unk164 = 0.5f;
                            espScaleSet(D_801113E8_etch_n_catch[data->unk160], data->unk164, data->unk164);
                            object->work[0] = 3;
                        } else {
                            data->unk15C++;
                            func_8010AEE4_etch_n_catch(data);
                        }
                        break;
                    case 3:
                        if (data->unk15C == 0) {
                            while (TRUE) {
                                data->unk16C = angles[rand8() >> 5];
                                x = object->trans.x - sindf(data->unk16C) * 100.0f;
                                z = object->trans.z - cosdf(data->unk16C) * 100.0f;
                                if ((z > -300.0f) & (z < 200.0f)) {
                                    if (data->unk160 == 0) {
                                        if ((x < -180.0f) & (x > -350.0f)) {
                                            break;
                                        }
                                    } else {
                                        if ((x > 180.0f) & (x < 350.0f)) {
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        data->unk15C++;
                        if (data->unk16C == data->unk170) {
                            data->unk15C = 0;
                            object->work[0] = 4;
                        } else {
                            func_8010AFB8_etch_n_catch(data);
                        }
                        break;
                    case 4:
                        object->trans.x -= sindf(data->unk170) * 3.0f;
                        object->trans.z -= cosdf(data->unk170) * 3.0f;
                        pos.x = object->trans.x;
                        pos.y = 0.0f;
                        pos.z = object->trans.z;
                        func_80012B14_main(0, &pos, &screen);
                        espPosSet(D_801113E8_etch_n_catch[data->unk160], screen.x, screen.y);
                        D_8010C850_etch_n_catch[data->unk160][0] = screen.x / 2.0f;
                        D_8010C850_etch_n_catch[data->unk160][1] = screen.y / 2.0f;
                        if (data->unk15C % 10 == 0) {
                            sindf(data->unk170);
                            cosdf(data->unk170);
                        }
                        if (object->trans.z < -300.0f || object->trans.z > 200.0f) {
                            data->unk15C = 0;
                            object->work[0] = 1;
                        } else if (data->unk160 == 0) {
                            if (object->trans.x > -180.0f || object->trans.x < -350.0f) {
                                data->unk15C = 0;
                                object->work[0] = 1;
                            }
                        } else {
                            if (object->trans.x < 180.0f || object->trans.x > 350.0f) {
                                data->unk15C = 0;
                                object->work[0] = 1;
                            }
                        }
                        if (data->unk15C > 60) {
                            data->unk15C = 0;
                            object->work[0] = 1;
                        } else {
                            if (data->unk15C == 0) {
                                data->unk174 = data->unk170;
                            }
                            func_8010AD6C_etch_n_catch(data);
                            data->unk15C++;
                        }
                        break;
                }
            }
            break;
    }
}

void func_8010AB7C_etch_n_catch(omObjData *object) {
    EtchNCatchPlayerData *data = object->data;
    s32 i;

    data->unk1B4 += 7.0f;
    for (i = 0; i < 5; i++) {
        Hu3DModelPosSet(object->model[i + 1], data->unk178[i].x * data->unk1B4 * 1.5f + object->trans.x,
                        data->unk178[i].y * data->unk1B4 + object->trans.y,
                        data->unk178[i].z * data->unk1B4 * 1.5f + object->trans.z);
        func_8001F9E4_main(object->model[i + 1], 255.0f - data->unk1B4 * 8.0f);
        Hu3DModelScaleSet(object->model[i + 1], 3.0f, 3.0f, 3.0f);
        Hu3DModelRotSet(object->model[i + 1], 0.0f, 90.0f, 0.0f);
        func_8001C258_main(object->model[i + 1], 4, 0);
    }
}

void func_8010AD6C_etch_n_catch(EtchNCatchPlayerData *data) {
    if (data->unk161 == 0) {
        data->unk170 += 2.0f;
        if (ABS(data->unk170 - data->unk174) >= 30.0f) {
            data->unk161 = 1;
        }
    } else {
        data->unk170 -= 2.0f;
        if (ABS(data->unk170 - data->unk174) >= 30.0f) {
            data->unk161 = 0;
        }
    }
    espZRotSet(D_801113E8_etch_n_catch[data->unk160], data->unk170);
}

void func_8010AEE4_etch_n_catch(EtchNCatchPlayerData *data) {
    if (data->unk15C < 16) {
        data->unk164 -= 0.01f;
    } else if (data->unk15C < 8) {
        data->unk164 += 0.01f;
    } else if (data->unk15C < 10) {
        data->unk164 -= 0.01;
    } else {
        data->unk164 += 0.01;
    }
    espScaleSet(D_801113E8_etch_n_catch[data->unk160], data->unk164, data->unk164);
}

void func_8010AFB8_etch_n_catch(EtchNCatchPlayerData *data) {
    f32 diff;

    data->unk170 = func_8010C4F8_etch_n_catch(data->unk170);
    diff = data->unk16C - data->unk170;
    if (ABS(diff) > 5.0f) {
        if ((diff > 0.0f && diff < 180.0f) || (diff < -180.0f && diff > -360.0f)) {
            data->unk170 += 5.0f;
        } else {
            data->unk170 -= 5.0f;
        }
    } else {
        data->unk170 += diff;
    }
    data->unk170 = func_8010C4F8_etch_n_catch(data->unk170);
    espZRotSet(D_801113E8_etch_n_catch[data->unk160], data->unk170);
}

s32 func_8010B154_etch_n_catch(s16 x, s16 y) {
    s32 count = 0;
    s32 result;

    if (func_80109114_etch_n_catch(x, y) != 0) {
        result = TRUE;
    } else {
        count += func_80109114_etch_n_catch(x - 1, y) != 0;
        count += func_80109114_etch_n_catch(x + 1, y) != 0;
        count += func_80109114_etch_n_catch(x, y - 1) != 0;
        count += func_80109114_etch_n_catch(x, y + 1) != 0;
        result = count >= 3;
    }
    return result;
}

void func_8010B24C_etch_n_catch(omObjData *object) {
    EtchNCatchBoardWork *work;

    object->data = HuMemAllocTag(sizeof(EtchNCatchBoardWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(EtchNCatchBoardWork));
    work = object->data;
    work->unk01 = 0;
    work->unk00 = D_8010C840_etch_n_catch;
    work->unk04 = 0.0f;
    work->unk08 = 0.0f;
    work->unk02 = 0;
    object->work[0] = 0;
    switch (work->unk00) {
        case 0:
            object->trans.x = D_8010C6B0_etch_n_catch[0].x;
            break;
        case 1:
            object->trans.x = -D_8010C6B0_etch_n_catch[0].x;
            break;
    }
    object->trans.y = 800.0f;
    object->trans.z = D_8010C6B0_etch_n_catch[0].z;
    object->model[0] = func_8000B108_main(0x330002, 0x8B9);
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->model[1] = func_8000B108_main(0x330008, 0x89D);
    object->model[2] = func_8000B108_main(9, 0x8B9);
    Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[2], 0.0f, 0.0f, 0.0f);
    object->func = func_8010B3B4_etch_n_catch;
    D_8010C840_etch_n_catch++;
}

void func_8010B3B4_etch_n_catch(omObjData *object) {
    omObjData *first = NULL;
    omObjData *second = NULL;
    EtchNCatchBoardWork *work = object->data;
    s32 i;
    s16 fx;
    u8 index;

    switch (object->work[0]) {
        case 0:
            if (work->unk01 != 0 && work->unk08 == 0.0f) {
                for (i = 0; i < 4; i++) {
                    if (work->unk00 == 0 && D_8010C868_etch_n_catch[i]->unk_01 == 3) {
                        if (first == NULL) {
                            first = D_800EC598_minigame[i];
                        } else {
                            second = D_800EC598_minigame[i];
                        }
                    } else if (work->unk00 == 1 && D_8010C868_etch_n_catch[i]->unk_01 == 12) {
                        if (first == NULL) {
                            first = D_800EC598_minigame[i];
                        } else {
                            second = D_800EC598_minigame[i];
                        }
                    }
                }
                index = rand8() * 3 >> 8;
                switch (work->unk00) {
                    case 0:
                        object->trans.x = D_8010C6B0_etch_n_catch[index].x;
                        break;
                    case 1:
                        object->trans.x = -D_8010C6B0_etch_n_catch[index].x;
                        break;
                }
                object->trans.z = D_8010C6B0_etch_n_catch[index].z;
                if (ABS(first->trans.x - object->trans.x) < 75.0f && ABS(first->trans.z - object->trans.z) < 75.0f) {
                    break;
                }
                if (ABS(second->trans.x - object->trans.x) < 75.0f && ABS(second->trans.z - object->trans.z) < 75.0f) {
                    break;
                }
            } else if (work->unk01 == 0) {
                work->unk01 = 1;
            }
            object->trans.y -= work->unk08 + 5.0f;
            if (object->trans.y < 0.0f) {
                object->trans.y = 0.0f;
                work->unk08 = 0.0f;
                object->work[0] = 1;
            } else {
                work->unk08 += 5.0f;
                work->unk04 += 0.1f;
                if (work->unk04 > 1.5f) {
                    work->unk04 = 1.5f;
                }
                if (work->unk08 == 45.0f) {
                    Hu3DModelScaleSet(object->model[1], 3.6f, 3.6f, 3.6f);
                    func_800E4C88_minigame(object, 1, object->trans.x, 0.0f, object->trans.z, 0.0f, 0.0f);
                } else if (work->unk08 == 50.0f) {
                    if (work->unk00 == 0) {
                        fx = HuAudFXPlay(0x37B);
                        HuAudFXPanning(fx, 32);
                        if (D_8010C6AC_etch_n_catch == 0) {
                            HuAudFXVolSet(fx, 102);
                        } else {
                            HuAudFXVolSet(fx, 127);
                        }
                    } else {
                        fx = HuAudFXPlay(0x37C);
                        HuAudFXPanning(fx, 95);
                    }
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelPosSet(object->model[2], object->trans.x, 0.0f, object->trans.z);
            Hu3DModelScaleSet(object->model[2], work->unk04, work->unk04, work->unk04);
            func_8001C258_main(object->model[2], 4, 0);
            break;
        case 1:
            if (D_8010C858_etch_n_catch[work->unk00]->work[0] != 10) {
                break;
            }
            if (work->unk02 >= 5) {
                work->unk02 = 0;
                D_8010C858_etch_n_catch[work->unk00]->work[0] = 0;
                object->work[0] = 2;
                break;
            }
            if (work->unk02 == 0) {
                if (work->unk00 == 0) {
                    for (i = 0; i < 4; i++) {
                        if (D_8010C868_etch_n_catch[i]->unk_01 == 3) {
                            omVibrate(((func_800E1BA8_minigame_ObjData *)D_800EC598_minigame[i]->data)->unk59, 10, 0, 10);
                        }
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        if (D_8010C868_etch_n_catch[i]->unk_01 == 12) {
                            omVibrate(((func_800E1BA8_minigame_ObjData *)D_800EC598_minigame[i]->data)->unk59, 10, 0, 10);
                        }
                    }
                }
            }
            work->unk02++;
            break;
        case 2:
            object->trans.y += work->unk08 + 5.0f;
            if (object->trans.y > 800.0f && work->unk04 == 0.0f) {
                object->trans.y = 800.0f;
                work->unk08 = 0.0f;
                object->work[0] = 3;
            } else {
                work->unk08 += 5.0f;
                work->unk04 -= 0.1f;
                if (work->unk04 < 0.0f) {
                    work->unk04 = 0.0f;
                }
            }
            Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
            Hu3DModelScaleSet(object->model[2], work->unk04, work->unk04, work->unk04);
            break;
        case 3:
            work->unk04 = 1.0f;
            func_8001C258_main(object->model[2], 4, 4);
            break;
    }
}

void func_8010BBE4_etch_n_catch(omObjData *object) {
    s16 pos[2][2] = { { 35, 38 }, { 252, 38 } };
    s16 sprite;
    s16 i;

    sprite = func_8000B838_main(0x21002A);
    for (i = 0; i < 2; i++) {
        espPosSet(espEntry(sprite, 0, 1), pos[i][0], pos[i][1]);
    }
    sprite = func_8000B838_main(0x21001B);
    for (i = 0; i < 2; i++) {
        espPosSet(espEntry(sprite, 0, 1), pos[i][0] + 16, pos[i][1]);
    }
    sprite = func_8000B838_main(0x31);
    for (i = 0; i < 2; i++) {
        D_801113A8_etch_n_catch[i] = espEntry(sprite, 0, 1);
        espPosSet(D_801113A8_etch_n_catch[i], D_8010C6A4_etch_n_catch[i][0], D_8010C6A4_etch_n_catch[i][1]);
    }
    object->func = func_8010BD98_etch_n_catch;
}

void func_8010BD98_etch_n_catch(omObjData *object) {
    func_8000BD50_main(D_801113A8_etch_n_catch[0], (s8)(D_8010C6AC_etch_n_catch % 10));
    espPosSet(D_801113A8_etch_n_catch[0], D_8010C6A4_etch_n_catch[0][0], D_8010C6A4_etch_n_catch[0][1]);
    func_8000BD50_main(D_801113A8_etch_n_catch[1], (s8)(D_8010C6AD_etch_n_catch % 10));
    espPosSet(D_801113A8_etch_n_catch[1], D_8010C6A4_etch_n_catch[1][0], D_8010C6A4_etch_n_catch[1][1]);
}

#ifdef NON_MATCHING
void func_8010BE84_etch_n_catch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;
    HuSprite *sprite;
    u16 *palette;
    u8 *grid;
    s16 spriteId;
    s32 i;

    spriteId = func_8000B838_main(0x330003);
    D_8010C842_etch_n_catch = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(D_8010C842_etch_n_catch, 0, spriteId, 0);
    HuSprAttrReset(D_8010C842_etch_n_catch, 0, 0xFFFF);
    HuSprAttrSet(D_8010C842_etch_n_catch, 0, 0x5000);
    HuSprPosSet(D_8010C842_etch_n_catch, 0, 160, 120);
    spriteId = func_8000B838_main(0x330004);
    D_8010C844_etch_n_catch = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(D_8010C844_etch_n_catch, 0, spriteId, 0);
    HuSprAttrReset(D_8010C844_etch_n_catch, 0, 0xFFFF);
    HuSprAttrSet(D_8010C844_etch_n_catch, 0, 0x5000);
    HuSprPosSet(D_8010C844_etch_n_catch, 0, 160, 120);
    D_8010C878_etch_n_catch = HuMemAlloc(0xE100);
    D_8010C87C_etch_n_catch[0] = HuMemAlloc(0xFA0);
    D_8010C87C_etch_n_catch[1] = HuMemAlloc(0xFA0);
    sprite = HuSprGet(D_8010C844_etch_n_catch, 0);
    D_8010C84C_etch_n_catch = grid = sprite->unk_84->unk00->unk00;
    palette = sprite->unk_84->unk0C;
    D_8010C846_etch_n_catch = sprite->unk_84->unk14;
    D_8010C848_etch_n_catch = sprite->unk_84->unk16;
    palette[0] = 0;
    palette[1] = 0xF801;
    palette[2] = 0xFC21;
    palette[4] = 0xFE31;
    palette[8] = 0x3F;
    palette[0x10] = 0x843F;
    palette[0x20] = 0xC63F;
    palette[ETCH_N_CATCH_CELL_FILLED] = 0x400;
    palette[ETCH_N_CATCH_CELL_EDGE] = 0xFFFE;
    for (i = 0; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i++) {
        if (i > D_8010C846_etch_n_catch * 50 && i < D_8010C846_etch_n_catch * 51) {
            *grid = ETCH_N_CATCH_CELL_EDGE;
        } else if (i > D_8010C846_etch_n_catch * 200 && i < D_8010C846_etch_n_catch * 201) {
            *grid = ETCH_N_CATCH_CELL_EDGE;
        } else {
            *grid = 0;
        }
        grid++;
    }
    grid = D_8010C84C_etch_n_catch;
    for (i = 30; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    for (i = 160; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    for (i = 290; i < D_8010C846_etch_n_catch * D_8010C848_etch_n_catch; i += D_8010C846_etch_n_catch) {
        grid[i] = ETCH_N_CATCH_CELL_EDGE;
    }
    object->func = NULL;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk08 = 0.5f;
    func_800E1370_minigame(object, 2, 0.0f);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_12_etch_n_catch/19CEF0", func_8010BE84_etch_n_catch);
#endif

void func_8010C2F4_etch_n_catch(void) {
    s32 i;

    HuMemFree(D_8010C878_etch_n_catch);
    HuMemFree(D_8010C87C_etch_n_catch[0]);
    HuMemFree(D_8010C87C_etch_n_catch[1]);
    for (i = 0; i < 4; i++) {
        EtchNCatchWork *work = D_8010C868_etch_n_catch[i];

        HuMemFree(D_801113D8_etch_n_catch[i]);
        HuMemFree(work);
    }
}

void func_8010C390_etch_n_catch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    work->unk08 = 0.5f;
    func_800E139C_minigame(object, 0.0f, -450.0f, -400.0f, -80.0f, 300.0f);
    func_800E1468_minigame(object);
}

void func_8010C444_etch_n_catch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->func = NULL;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 1;
    work->unk08 = 0.5f;
    func_800E139C_minigame(object, 0.0f, 80.0f, -400.0f, 450.0f, 300.0f);
    func_800E1468_minigame(object);
}

f32 func_8010C4F8_etch_n_catch(f32 arg0) {
    while (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    }
    while (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    return arg0;
}

Vec2f func_8010C574_etch_n_catch(s32 x0, s32 y0, s32 x1, s32 y1) {
    Vec2f dir;
    f32 len;

    dir.x = x1 - x0;
    dir.y = y1 - y0;
    len = HuSqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len == 0.0f) {
        dir.y = 0.0f;
        dir.x = 0.0f;
    } else {
        dir.x /= len;
        dir.y /= len;
    }
    return dir;
}

void func_8010C628_etch_n_catch(omObjData *object, f32 scale) {
    object->scale.z = scale;
    object->scale.y = scale;
    object->scale.x = scale;
    Hu3DModelScaleSet(object->model[0], scale, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    Hu3DModelScaleSet(object->model[2], object->scale.x, object->scale.y, object->scale.z);
}
