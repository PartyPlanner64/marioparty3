#include "common.h"
#include "game/overlays/minigame.h"
#include "game/overlays/mgcamera.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "game/input.h"
#include "math.h"
#include "game/data.h"
#include "game/sprite.h"

typedef struct UnkBabyBowserBonkers { // 0x12 bytes
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08[2]; // digit x offsets
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} UnkBabyBowserBonkers;

typedef struct BabyBowserBonkersPlayer { // 0x50 bytes, 2 entries
    s16 unk_00;                          // player index
    s16 unk_02;                          // steps taken
    s16 unk_04;                          // whose turn
    s16 unk_06;
    f32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    Vec unk_1C;
    s16 unk_28; // GwPlayer index
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    f32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
} BabyBowserBonkersPlayer;

typedef struct BabyBowserBonkersActor { // 0x30 bytes, 0xE entries
    s16 unk_00;
    s16 unk_02; // model index
    s16 unk_04;
    s16 unk_06; // state
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    f32 unk_14; // wobble amplitude
    f32 unk_18; // timer
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    void (*unk_28)(struct BabyBowserBonkersActor *); // previous callback
    void (*unk_2C)(struct BabyBowserBonkersActor *); // callback
} BabyBowserBonkersActor;

typedef struct BabyBowserBonkersStageWork {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} BabyBowserBonkersStageWork; // sizeof 0xB4

typedef struct BabyBowserBonkersSpawn {
    s16 unk_00; // time
    s16 unk_02; // actor index
} BabyBowserBonkersSpawn;

typedef struct BabyBowserBonkersPattern {
    s16 unk_00; // duration
    s16 unk_02;
    s16 unk_04;
    s16 unk_06; // spawn count
    BabyBowserBonkersSpawn *unk_08;
} BabyBowserBonkersPattern;

typedef union BabyBowserBonkersBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BabyBowserBonkersBytes;

extern const s16 D_8010B950_baby_bowser_bonkers[];
extern const s16 D_8010B95C_baby_bowser_bonkers[];
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern f32 D_800EB760_minigame;

Vec D_8010B400_baby_bowser_bonkers[14] = {
    { -312.25f, 39.1f, -276.95f },
    { -105.35f, 39.1f, -276.95f },
    { 105.35f, 39.1f, -276.95f },
    { 312.25f, 39.1f, -276.95f },
    { -202.8f, 39.1f, -75.6f },
    { 3.05f, 39.1f, -75.6f },
    { 208.8f, 39.1f, -75.6f },
    { -302.8f, 39.1f, 127.8f },
    { -104.7f, 39.1f, 127.8f },
    { 104.7f, 39.1f, 127.8f },
    { 302.8f, 39.1f, 127.8f },
    { -202.8f, 39.1f, 321.5f },
    { 3.05f, 39.1f, 321.5f },
    { 208.8f, 39.1f, 321.5f }
};

BabyBowserBonkersSpawn D_8010B4A8_baby_bowser_bonkers[6] = { { 6, 4 }, { 12, 5 }, { 18, 6 }, { 6, 13 }, { 12, 12 }, { 18, 11 } };
BabyBowserBonkersPattern D_8010B4C0_baby_bowser_bonkers = { 30, 60, 1, 6, D_8010B4A8_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B4CC_baby_bowser_bonkers[6] = { { 6, 0 }, { 12, 4 }, { 18, 1 }, { 6, 10 }, { 12, 13 }, { 18, 9 } };
BabyBowserBonkersPattern D_8010B4E4_baby_bowser_bonkers = { 30, 60, 1, 6, D_8010B4CC_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B4F0_baby_bowser_bonkers[6] = { { 6, 3 }, { 12, 6 }, { 18, 2 }, { 6, 7 }, { 12, 11 }, { 18, 8 } };
BabyBowserBonkersPattern D_8010B508_baby_bowser_bonkers = { 30, 60, 1, 6, D_8010B4F0_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B514_baby_bowser_bonkers[6] = { { 6, 1 }, { 12, 5 }, { 18, 2 }, { 6, 9 }, { 12, 12 }, { 18, 8 } };
BabyBowserBonkersPattern D_8010B52C_baby_bowser_bonkers = { 30, 60, 1, 6, D_8010B514_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B538_baby_bowser_bonkers[8] = { { 6, 0 }, { 12, 2 }, { 18, 1 }, { 24, 3 }, { 6, 10 }, { 12, 8 }, { 18, 9 }, { 24, 7 } };
BabyBowserBonkersPattern D_8010B558_baby_bowser_bonkers = { 60, 54, 1, 14, D_8010B538_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B564_baby_bowser_bonkers[8] = { { 6, 3 }, { 12, 1 }, { 18, 2 }, { 24, 0 }, { 6, 7 }, { 12, 9 }, { 18, 8 }, { 24, 10 } };
BabyBowserBonkersPattern D_8010B584_baby_bowser_bonkers = { 60, 54, 1, 14, D_8010B564_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B590_baby_bowser_bonkers[8] = { { 6, 0 }, { 12, 4 }, { 18, 8 }, { 24, 12 }, { 6, 13 }, { 12, 9 }, { 18, 5 }, { 24, 1 } };
BabyBowserBonkersPattern D_8010B5B0_baby_bowser_bonkers = { 60, 54, 1, 14, D_8010B590_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B5BC_baby_bowser_bonkers[8] = { { 6, 3 }, { 12, 6 }, { 18, 10 }, { 24, 13 }, { 6, 11 }, { 12, 7 }, { 18, 4 }, { 24, 0 } };
BabyBowserBonkersPattern D_8010B5DC_baby_bowser_bonkers = { 60, 54, 1, 14, D_8010B5BC_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B5E8_baby_bowser_bonkers[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 24, 3 }, { 30, 6 }, { 36, 5 }, { 42, 4 }, { 6, 13 }, { 12, 12 }, { 18, 11 }, { 24, 7 }, { 30, 8 }, { 36, 9 }, { 42, 10 } };
BabyBowserBonkersPattern D_8010B620_baby_bowser_bonkers = { 60, 45, 1, 14, D_8010B5E8_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B62C_baby_bowser_bonkers[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 24, 3 }, { 30, 6 }, { 36, 10 }, { 42, 13 }, { 42, 12 }, { 36, 11 }, { 30, 7 }, { 24, 4 }, { 18, 5 }, { 12, 9 }, { 6, 8 } };
BabyBowserBonkersPattern D_8010B664_baby_bowser_bonkers = { 60, 45, 1, 14, D_8010B62C_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B670_baby_bowser_bonkers[14] = { { 6, 0 }, { 12, 4 }, { 18, 1 }, { 24, 5 }, { 30, 2 }, { 36, 6 }, { 42, 3 }, { 6, 10 }, { 12, 13 }, { 18, 9 }, { 24, 12 }, { 30, 8 }, { 36, 11 }, { 42, 7 } };
BabyBowserBonkersPattern D_8010B6A8_baby_bowser_bonkers = { 60, 45, 1, 14, D_8010B670_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B6B4_baby_bowser_bonkers[14] = { { 6, 13 }, { 12, 12 }, { 18, 11 }, { 24, 7 }, { 30, 4 }, { 36, 2 }, { 42, 1 }, { 42, 12 }, { 36, 3 }, { 30, 6 }, { 24, 10 }, { 18, 9 }, { 12, 8 }, { 6, 5 } };
BabyBowserBonkersPattern D_8010B6EC_baby_bowser_bonkers = { 60, 45, 1, 14, D_8010B6B4_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B6F8_baby_bowser_bonkers[14] = { { 6, 13 }, { 12, 12 }, { 18, 11 }, { 6, 7 }, { 12, 4 }, { 18, 2 }, { 6, 1 }, { 12, 12 }, { 18, 3 }, { 6, 6 }, { 12, 10 }, { 18, 9 }, { 6, 8 }, { 12, 5 } };
BabyBowserBonkersPattern D_8010B730_baby_bowser_bonkers = { 21, 45, 0, 14, D_8010B6F8_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B73C_baby_bowser_bonkers[14] = { { 6, 0 }, { 12, 1 }, { 18, 2 }, { 6, 3 }, { 12, 4 }, { 18, 5 }, { 6, 6 }, { 12, 7 }, { 18, 8 }, { 6, 9 }, { 12, 10 }, { 18, 11 }, { 6, 12 }, { 12, 13 } };
BabyBowserBonkersPattern D_8010B774_baby_bowser_bonkers = { 21, 45, 0, 14, D_8010B73C_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B780_baby_bowser_bonkers[14] = { { 18, 0 }, { 12, 1 }, { 6, 2 }, { 18, 3 }, { 12, 4 }, { 6, 5 }, { 18, 6 }, { 12, 7 }, { 6, 8 }, { 18, 9 }, { 12, 10 }, { 6, 11 }, { 18, 12 }, { 12, 13 } };
BabyBowserBonkersPattern D_8010B7B8_baby_bowser_bonkers = { 27, 45, 0, 14, D_8010B780_baby_bowser_bonkers };
BabyBowserBonkersSpawn D_8010B7C4_baby_bowser_bonkers[14] = { { 18, 13 }, { 12, 12 }, { 6, 11 }, { 18, 7 }, { 12, 4 }, { 6, 2 }, { 18, 1 }, { 12, 12 }, { 6, 3 }, { 6, 6 }, { 12, 10 }, { 6, 9 }, { 18, 8 }, { 12, 5 } };
BabyBowserBonkersPattern D_8010B7FC_baby_bowser_bonkers = { 27, 45, 0, 14, D_8010B7C4_baby_bowser_bonkers };
BabyBowserBonkersPattern *D_8010B808_baby_bowser_bonkers[4] = { &D_8010B4C0_baby_bowser_bonkers, &D_8010B4E4_baby_bowser_bonkers, &D_8010B508_baby_bowser_bonkers, &D_8010B52C_baby_bowser_bonkers };
BabyBowserBonkersPattern *D_8010B818_baby_bowser_bonkers[4] = { &D_8010B558_baby_bowser_bonkers, &D_8010B584_baby_bowser_bonkers, &D_8010B5B0_baby_bowser_bonkers, &D_8010B5DC_baby_bowser_bonkers };
BabyBowserBonkersPattern *D_8010B828_baby_bowser_bonkers[4] = { &D_8010B620_baby_bowser_bonkers, &D_8010B664_baby_bowser_bonkers, &D_8010B6A8_baby_bowser_bonkers, &D_8010B6EC_baby_bowser_bonkers };
BabyBowserBonkersPattern *D_8010B838_baby_bowser_bonkers[4] = { &D_8010B730_baby_bowser_bonkers, &D_8010B774_baby_bowser_bonkers, &D_8010B7B8_baby_bowser_bonkers, &D_8010B7FC_baby_bowser_bonkers };
s32 D_8010B848_baby_bowser_bonkers[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s32 D_8010B868_baby_bowser_bonkers[8] = { 0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6, 0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D };
BabyBowserBonkersPattern *D_8010B888_baby_bowser_bonkers = NULL;
s16 D_8010B88C_baby_bowser_bonkers = 0;
s32 D_8010B890_baby_bowser_bonkers = 0;
s32 D_8010B894_baby_bowser_bonkers[4] = { 0, 1, 2, 3 };
Vec D_8010B8A4_baby_bowser_bonkers[2] = {
    { -352.8f, 39.1f, -75.6f },
    { 352.8f, 39.1f, -75.6f }
};
s32 D_8010B8BC_baby_bowser_bonkers[8] = { 0x00020000, 0x00030000, 0x00070000, 0x00040000, 0x00050000, 0x00060000, 0x00080000, 0x00090000 };
s32 D_8010B8DC_baby_bowser_bonkers[2] = { 0x2F, 0x30 };
s32 D_8010B8E4_baby_bowser_bonkers[2] = { 0x36, 0x37 };
f32 D_8010B8EC_baby_bowser_bonkers = 0.0f;
f32 D_8010B8F0_baby_bowser_bonkers = 0.0f;
f32 D_8010B8F4_baby_bowser_bonkers = 180.0f;
BabyBowserBonkersPattern **D_8010B8F8_baby_bowser_bonkers[4] = { D_8010B808_baby_bowser_bonkers, D_8010B818_baby_bowser_bonkers, D_8010B828_baby_bowser_bonkers, D_8010B838_baby_bowser_bonkers };
s32 D_8010B908_baby_bowser_bonkers[4] = { 4, 4, 4, 4 };
s32 D_8010B918_baby_bowser_bonkers[8] = { 0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F };
s32 D_8010B938_baby_bowser_bonkers = 0;
s32 D_8010B93C_baby_bowser_bonkers = 0;
s32 D_8010B940_baby_bowser_bonkers = 0;

BabyBowserBonkersActor *D_8010BC00_baby_bowser_bonkers[14] BSS;
omObjData *D_8010BC38_baby_bowser_bonkers BSS;
s32 D_8010BC3C_baby_bowser_bonkers BSS;
s32 D_8010BC40_baby_bowser_bonkers BSS;
s32 D_8010BC44_baby_bowser_bonkers BSS;
s32 D_8010BC48_baby_bowser_bonkers BSS;
s32 D_8010BC4C_baby_bowser_bonkers BSS;
s32 D_8010BC50_baby_bowser_bonkers BSS;
s32 D_8010BC54_baby_bowser_bonkers BSS;
BabyBowserBonkersPlayer *D_8010BC58_baby_bowser_bonkers BSS;
s16 D_8010BC5C_baby_bowser_bonkers BSS;
BabyBowserBonkersActor *D_8010BC60_baby_bowser_bonkers BSS;
u8 D_8010BC64_baby_bowser_bonkers[4] BSS; /* Unreferenced. */
BabyBowserBonkersPattern *D_8010BC68_baby_bowser_bonkers[4][4] BSS;
s16 *D_8010BCA8_baby_bowser_bonkers BSS;
UnkBabyBowserBonkers *D_8010BCAC_baby_bowser_bonkers BSS;
MgCameraKey D_8010BCB0_baby_bowser_bonkers[2] BSS; // target, origin
s32 D_8010BCF8_baby_bowser_bonkers BSS;
s32 D_8010BCFC_baby_bowser_bonkers BSS;
s32 D_8010BD00_baby_bowser_bonkers BSS;
u8 D_8010BD04_baby_bowser_bonkers[4] BSS; /* Unreferenced. */
MinigameFlow D_8010BD08_baby_bowser_bonkers BSS;

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *object);
void func_80109E98_baby_bowser_bonkers(s32, s16);
void func_80108F9C_baby_bowser_bonkers(BabyBowserBonkersActor *);
void func_80105BB0_baby_bowser_bonkers(omObjData *object);
void func_80105C0C_baby_bowser_bonkers(omObjData *object);
void func_801062E8_baby_bowser_bonkers(omObjData *object);
void func_8010630C_baby_bowser_bonkers(omObjData *object);
void func_8010660C_baby_bowser_bonkers(omObjData *object);
void func_80106AA4_baby_bowser_bonkers(omObjData *object);
void func_80106CEC_baby_bowser_bonkers(omObjData *object);
f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 current, f32 step);
s32 func_80107648_baby_bowser_bonkers(omObjData *object);
BabyBowserBonkersActor *func_8010919C_baby_bowser_bonkers(s32 arg0);
void func_801091D4_baby_bowser_bonkers(f32 x, f32 z, BabyBowserBonkersActor **list);
s32 func_801093D4_baby_bowser_bonkers(s32 arg0);
s32 func_80109388_baby_bowser_bonkers(BabyBowserBonkersActor *arg0, s32 arg1);
s32 func_801080D0_baby_bowser_bonkers(f32 arg0, f32 arg1);
s32 func_8010943C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s32 playerIndex);
s32 func_8010958C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s32 playerIndex);
void func_8010B380_baby_bowser_bonkers(omObjData *arg0, u32 arg1);
void func_801076D8_baby_bowser_bonkers(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed);
void func_80107678_baby_bowser_bonkers(omObjData *arg0, s32 arg1, s32 arg2);
s32 func_80109080_baby_bowser_bonkers(s32 arg0, s16 arg1, s16 arg2);
s32 func_801096D0_baby_bowser_bonkers(void);
void func_8010AD00_baby_bowser_bonkers(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void func_801063B4_baby_bowser_bonkers(void);
void func_80107CD8_baby_bowser_bonkers(void);
void func_80107D38_baby_bowser_bonkers(omObjData *object);
void func_80107E54_baby_bowser_bonkers(omObjData *object);
void func_80108160_baby_bowser_bonkers(void);
void func_801081C0_baby_bowser_bonkers(omObjData *object);
void func_8010831C_baby_bowser_bonkers(omObjData *object);
void func_801089CC_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
s16 func_80108454_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
void func_80108E90_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
void func_80108B84_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
void func_80108D6C_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
void func_80108A0C_baby_bowser_bonkers(BabyBowserBonkersActor *actor);
void func_80109704_baby_bowser_bonkers(void);
void func_80109890_baby_bowser_bonkers(void);
void func_80109990_baby_bowser_bonkers(omObjData *object);
void func_80109BFC_baby_bowser_bonkers(s32 index, s32 chr);
void func_80109EB8_baby_bowser_bonkers(void);
void func_8010A6D8_baby_bowser_bonkers(omObjData *object);
void func_8010AB14_baby_bowser_bonkers(s32 arg0);
void func_8010AEF0_baby_bowser_bonkers(s32 camIndex);
f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 start, f32 end);
f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 start, f32 end);

void func_801059A0_baby_bowser_bonkers(void) {
    omObjData *obj;
    u8 camIndex;

    MapCollInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DSprModelInit(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010BC48_baby_bowser_bonkers = 900;
    D_8010BC44_baby_bowser_bonkers = 0;
    D_8010BC40_baby_bowser_bonkers = 0;
    D_8010BC4C_baby_bowser_bonkers = -1;
    D_8010BC50_baby_bowser_bonkers = 0;
    D_8010BC54_baby_bowser_bonkers = -1;
    D_8010BC5C_baby_bowser_bonkers = -1;
    D_8010BC38_baby_bowser_bonkers = omAddObj(0x20, 0, 0, -1, func_80105BB0_baby_bowser_bonkers);
    memset(&D_8010BD08_baby_bowser_bonkers, 0, 0x28);
    D_8010BD08_baby_bowser_bonkers.type = MINIGAME_BATTLE;
    func_800E5EA0_minigame(&D_8010BD08_baby_bowser_bonkers);
    GMesFontMesCreate(D_8010B950_baby_bowser_bonkers, 1);
    GMesFontMesCreate(D_8010B95C_baby_bowser_bonkers, 1);
}

void func_80105BB0_baby_bowser_bonkers(omObjData *object) {
    object->func = func_80105C0C_baby_bowser_bonkers;
    func_80107CD8_baby_bowser_bonkers();
    func_80108160_baby_bowser_bonkers();
    func_801063B4_baby_bowser_bonkers();
    func_80109890_baby_bowser_bonkers();
    func_80109EB8_baby_bowser_bonkers();
    if (_CheckFlag(10)) {
        D_8010BC3C_baby_bowser_bonkers = 1;
    }
}

const s16 D_8010B950_baby_bowser_bonkers[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0 };

const s16 D_8010B95C_baby_bowser_bonkers[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0 };

void func_80105C0C_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player1;
    BabyBowserBonkersPlayer *player2;
    s32 i;
    s32 done;
    s32 group;

    done = 0;
    switch (D_8010BC4C_baby_bowser_bonkers) {
        case -1:
            if (D_8010BC44_baby_bowser_bonkers > 0) {
                D_8010BC54_baby_bowser_bonkers = HuAudFXPlay(0x4AE);
                WipeCreateIn(WIPE_TYPE_PREV, 16);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(6);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x36);
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 1:
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (D_8010BC48_baby_bowser_bonkers + 29) / 30, 156, 32);
                MgFlowStatSet(MG_STATE_PLAY);
                if (D_8010B888_baby_bowser_bonkers == NULL) {
                    D_8010BC44_baby_bowser_bonkers = 3;
                    D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[0][0];
                }
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 2:
            D_8010BC48_baby_bowser_bonkers--;
            GMesTimerValueSet((D_8010BC48_baby_bowser_bonkers + 29) / 30);
            if (D_8010BC48_baby_bowser_bonkers <= 0) {
                D_8010BC48_baby_bowser_bonkers = 0;
            }
            if (D_8010BC48_baby_bowser_bonkers >= 60) {
                for (i = 0; i < D_8010B888_baby_bowser_bonkers->unk_06; i++) {
                    if (D_8010BC44_baby_bowser_bonkers == D_8010B888_baby_bowser_bonkers->unk_08[i].unk_00) {
                        func_80109080_baby_bowser_bonkers(D_8010B888_baby_bowser_bonkers->unk_08[i].unk_02, 12,
                                                          D_8010B888_baby_bowser_bonkers->unk_02);
                    }
                }
            }
            if (D_8010B888_baby_bowser_bonkers->unk_04 == 0 || func_801096D0_baby_bowser_bonkers() != 0) {
                done = 1;
            }
            if (D_8010BC44_baby_bowser_bonkers >= D_8010B888_baby_bowser_bonkers->unk_00 && done) {
                if (D_8010BC48_baby_bowser_bonkers >= 600) {
                    group = 0;
                } else if (D_8010BC48_baby_bowser_bonkers >= 450) {
                    group = 1;
                } else {
                    group = (D_8010BC48_baby_bowser_bonkers < 300) ? 3 : 2;
                }
                if (++D_8010BC50_baby_bowser_bonkers >= 4) {
                    D_8010BC50_baby_bowser_bonkers = 0;
                }
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[group][D_8010BC50_baby_bowser_bonkers];
            }
            if (D_8010BC48_baby_bowser_bonkers <= 0) {
                GMesTimerEnd();
                GMesCreate(0x11);
                MgFlowStatSet(MG_STATE_FINISH);
                func_80107678_baby_bowser_bonkers(D_800EC598_minigame[0], 0, 13);
                func_80107678_baby_bowser_bonkers(D_800EC598_minigame[1], 0, 13);
                HuAudSeqFadeOut(120);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 3:
            if (D_8010BC44_baby_bowser_bonkers == 15) {
                if (D_8010BC54_baby_bowser_bonkers != -1) {
                    HuAudFXFadeOut((s16)D_8010BC54_baby_bowser_bonkers, 15);
                }
                D_8010BC54_baby_bowser_bonkers = -1;
            }
            if (GMesStatGet() == 0) {
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 4:
            if (D_8010BC44_baby_bowser_bonkers >= 15) {
                player1 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[0]);
                player2 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[1]);
                if (player1->unk_02 > player2->unk_02) {
                    GMesCreate(0x16, player1->unk_2C);
                    GwPlayer[player1->unk_28].bonusCoin += 10;
                    D_8010BC5C_baby_bowser_bonkers = player1->unk_2C;
                    D_8010BC50_baby_bowser_bonkers = 140;
                    player1->unk_04 = 0;
                    player2->unk_04 = 1;
                    HuAudSeqPlay(0x67);
                    func_8010AD00_baby_bowser_bonkers(D_800EC598_minigame[0]->trans.x, D_800EC598_minigame[0]->trans.y + 50.0,
                                                      D_800EC598_minigame[0]->trans.z, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                                      600.0f, 30);
                } else if (player1->unk_02 < player2->unk_02) {
                    GMesCreate(0x16, player2->unk_2C);
                    GwPlayer[player2->unk_28].bonusCoin += 10;
                    D_8010BC5C_baby_bowser_bonkers = player2->unk_2C;
                    D_8010BC50_baby_bowser_bonkers = 140;
                    player1->unk_04 = 1;
                    player2->unk_04 = 0;
                    HuAudSeqPlay(0x67);
                    func_8010AD00_baby_bowser_bonkers(D_800EC598_minigame[1]->trans.x, D_800EC598_minigame[1]->trans.y + 50.0,
                                                      D_800EC598_minigame[1]->trans.z, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                                      600.0f, 30);
                } else {
                    GMesCreate(0x20);
                    D_8010BC50_baby_bowser_bonkers = 144;
                    HuAudSeqPlay(0x6C);
                    player2->unk_04 = 1;
                    player1->unk_04 = 1;
                }
                MgFlowStatSet(MG_STATE_RESULT);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 6:
            if (D_8010BC44_baby_bowser_bonkers >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                HuAudFXAllFadeOut(16);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = func_801062E8_baby_bowser_bonkers;
            }
            break;
    }
    player1 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers]);
    player2 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers ^ 1]);
    func_801076D8_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers],
                                      D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers ^ 1], &player1->unk_1C,
                                      &player2->unk_1C, 0);
    D_8010B88C_baby_bowser_bonkers ^= 1;
    func_8010630C_baby_bowser_bonkers(object);
    D_8010BC40_baby_bowser_bonkers++;
    D_8010BC44_baby_bowser_bonkers++;
}

void func_801062E8_baby_bowser_bonkers(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_8010630C_baby_bowser_bonkers(omObjData *object) {
    if (D_8010B890_baby_bowser_bonkers != 0) {
        if (D_8010B890_baby_bowser_bonkers == 1) {
            object->func = func_801062E8_baby_bowser_bonkers;
        }
        D_8010B890_baby_bowser_bonkers--;
        return;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010B890_baby_bowser_bonkers = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)D_8010B890_baby_bowser_bonkers);
        HuAudSeqFadeOut((s16)D_8010B890_baby_bowser_bonkers);
        HuAudFXAllFadeOut((s16)D_8010B890_baby_bowser_bonkers);
    }
}

void func_801063B4_baby_bowser_bonkers(void) {
    s32 used[2];
    BabyBowserBonkersPlayer *player;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 minGroup;

    used[0] = -1;
    used[1] = -1;
    D_8010BC58_baby_bowser_bonkers = HuMemAllocTag(sizeof(BabyBowserBonkersPlayer) * 2, TAG_OVERLAY);
    player = D_8010BC58_baby_bowser_bonkers;
    memset(player, 0, sizeof(BabyBowserBonkersPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, minGroup = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (used[k] == D_8010B894_baby_bowser_bonkers[j]) {
                    found = 1;
                }
            }
            if (!found && GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group < minGroup) {
                minGroup = GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group;
                D_8010BC58_baby_bowser_bonkers[i].unk_28 = D_8010B894_baby_bowser_bonkers[j];
            }
        }
        used[i] = D_8010BC58_baby_bowser_bonkers[i].unk_28;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    D_800EB744_minigame = 1.4f;
    D_800EB748_minigame = 0.14f;
    D_800EB774_minigame = 1.46f;
    for (i = 0; i < 2; i++, player++) {
        player->unk_00 = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(0x10, 14, 60, -1, func_8010660C_baby_bowser_bonkers);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010B8A4_baby_bowser_bonkers[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010B8A4_baby_bowser_bonkers[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = 39.100002f;
        func_8010B380_baby_bowser_bonkers(D_800EC598_minigame[D_800EC280_minigame], (u32)player);
        D_800EC280_minigame++;
    }
}

void func_8010660C_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    s32 variant;
    s16 gwIndex;
    s16 chr;
    s16 i;
    u32 model;
    s32 motionFile;
    s32 linkModel;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    gwIndex = player->unk_28;
    chr = GwPlayer[gwIndex].chr;
    player->unk_2C = chr;
    player->unk_2A = GwPlayer[gwIndex].pad;
    player->unk_2E = GwPlayer[gwIndex].stat & 1;
    player->unk_30 = GwPlayer[gwIndex].cpu_difficulty;
    model = D_800A178C_main[chr][0];
    motionFile = D_800A178C_main[chr][1];
    linkModel = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motionFile, gwIndex, 0x289, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->model[3] = Hu3DModelRead(3, 0x68D);
    object->model[4] = Hu3DModelRead(4, 0x68D);
    for (i = 0; i < 3; i++) {
        object->model[7 + i] = Hu3DModelRead(8, 0x68D);
    }
    object->model[13] = Hu3DModelRead(model | linkModel, 0x28D);
    func_800E5A00_minigame(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, CharMotionDataNumGet(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, CharMotionDataNumGet(chr, 4), 1, 0x13);
    func_800E5A00_minigame(object, 0x11, CharMotionDataNumGet(chr, 0xE), 0, 0);
    func_800E5A00_minigame(object, 0x12, CharMotionDataNumGet(chr, 0xF), 2, 0);
    func_800E5A00_minigame(object, 0x15, CharMotionDataNumGet(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 0x14, CharMotionDataNumGet(chr, 0x1D), 0, 0);
    func_800E5A00_minigame(object, 4, CharMotionDataNumGet(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(object, 0x20, CharMotionDataNumGet(chr, 0x22), 0, 0);
    func_800E5978_minigame(object, 0x21, CharMotionDataNumGet(chr, 0x23), 2, 0);
    func_800E5A00_minigame(object, 0x22, CharMotionDataNumGet(chr, 0x24), 2, 0);
    variant = rand8() & 1;
    func_800E5A00_minigame(object, 0xD, CharMotionDataNumGet(chr, D_8010B8DC_baby_bowser_bonkers[variant]), 1, 120);
    player->unk_0C = D_8010B8BC_baby_bowser_bonkers[chr] | D_8010B8DC_baby_bowser_bonkers[variant];
    func_800E5A00_minigame(object, 0xE, CharMotionDataNumGet(chr, D_8010B8E4_baby_bowser_bonkers[rand8() & 1]), 1, 120);
    func_800E5690_minigame(object, 0);
    func_800E149C_minigame(object, 0, 2);
    player->unk_10 = player->unk_1C.x = 0.0f;
    player->unk_02 = 0;
    player->unk_04 = -1;
    player->unk_32 = -1;
    player->unk_34 = 0;
    player->unk_36 = 0;
    player->unk_38 = 1000.0 - player->unk_30 * 225.0;
    player->unk_08 = 0.0f;
    player->unk_3C = player->unk_30 * 6 + ((rand8() & 3) + 4);
    player->unk_3E = 0;
    player->unk_40 = 0;
    player->unk_42 = 0;
    player->unk_44 = player->unk_48 = 0.0f;
    object->func = func_80106AA4_baby_bowser_bonkers;
}

void func_80106AA4_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    f32 prevRot;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    data = object->data;
    player->unk_10 = object->trans.x;
    player->unk_14 = object->trans.y;
    player->unk_18 = object->trans.z;
    data->unk50 |= 0x8000;
    switch (MgFlowStatGet()) {
        case MG_STATE_PLAY:
            if (data->unk38 != 1000.0f) {
                object->trans.y -= 1.5000000596046448;
            }
            if (player->unk_2E != 0) {
                func_80106CEC_baby_bowser_bonkers(object);
            }
            break;
        case MG_STATE_FINISH:
            data->unk3C = func_8010B148_baby_bowser_bonkers(0.0f, data->unk3C, 15.0f);
            break;
        case MG_STATE_RESULT:
            switch (player->unk_04) {
                case 0:
                    if (func_800E5690_minigame(object, 0xD) != 0) {
                        CharAnimCreate(object->model[0], 2, player->unk_2C,
                                           D_8010B848_baby_bowser_bonkers[player->unk_2C]);
                        HuAudCharVoicePlayPlayer(player->unk_0C, -1, player->unk_00);
                        player->unk_04 = -1;
                    }
                    break;
                case 1:
                    if (func_800E5690_minigame(object, 0xE) != 0) {
                        CharAnimCreate(object->model[0], 2, player->unk_2C,
                                           D_8010B868_baby_bowser_bonkers[player->unk_2C]);
                        player->unk_04 = -1;
                    }
                    break;
            }
            break;
    }
    prevRot = data->unk3C;
    func_800DDD94_minigame(object);
    player->unk_1C.x = object->trans.x - player->unk_10;
    player->unk_1C.y = object->trans.y - player->unk_14;
    player->unk_1C.z = object->trans.z - player->unk_18;
    data->unk3C = func_8010B148_baby_bowser_bonkers(data->unk3C, prevRot, 30.0f);
    func_80088910_main(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
}

void func_80106CEC_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    BabyBowserBonkersActor *actor;
    HmfModel *model;
    f32 dist;
    f32 dz;
    f32 dx;
    f32 scale;
    f32 dx2;
    f32 dz2;
    s32 ready;
    s32 count;
    s32 i;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    data = object->data;
    D_800CDA7C_main[player->unk_2A] = D_800D5558_main[player->unk_2A] = 0;
    D_800CBB6E_main[player->unk_2A] = 0;
    D_800D20A1_main[player->unk_2A] = 0;
    if (D_8010BC48_baby_bowser_bonkers >= 450) {
        ready = player->unk_3C / 2 <= player->unk_02;
    } else {
        ready = player->unk_3C <= player->unk_02;
    }
    if (data->unk38 != 1000.0f) {
        player->unk_42 = player->unk_02;
    }
    if (player->unk_42 < player->unk_02 && (ready || player->unk_30 == 0)) {
        dx = player->unk_44 - object->trans.x;
        dz = player->unk_44 - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist != 0.0f) {
            dx /= dist;
            dz /= dist;
        } else {
            dx = dz = 0.0f;
        }
        scale = dist / 100.0;
        if (scale >= 1.0f) {
            scale = 1.0f;
        }
        D_800CBB6E_main[player->unk_2A] = dx * 64.0f * scale;
        D_800D20A1_main[player->unk_2A] = -(dz * 64.0f * scale);
        D_800CDA7C_main[player->unk_2A] |= 0x8000;
        D_800D5558_main[player->unk_2A] = 0;
        return;
    }
    if (ready) {
        if (player->unk_3E != 0) {
            D_800CBB6E_main[player->unk_2A] = 0;
            D_800D20A1_main[player->unk_2A] = 0;
            if (!(player->unk_3E & 7) && player->unk_32 != -1) {
                D_800D5558_main[player->unk_2A] |= 0x8000;
                D_800CDA7C_main[player->unk_2A] |= 0x8000;
            }
            if (--player->unk_3E <= 0) {
                player->unk_40 = (u8)(rand8() % 15) + 15.0f + player->unk_30 * 5;
                player->unk_3E = 0;
            }
            return;
        }
        if (--player->unk_40 <= 0) {
            player->unk_3E = (u8)(rand8() % 15) + 15.0f - player->unk_30 * 5;
            player->unk_40 = 0;
        }
    }
    if (player->unk_32 != -1) {
        actor = func_8010919C_baby_bowser_bonkers(player->unk_32);
        if (actor == NULL) {
            player->unk_32 = -1;
            return;
        }
        model = &Hu3DData[actor->unk_02];
        dx = model->pos.x - object->trans.x;
        dz = model->pos.z - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 150.0 && dist > 50.0 && player->unk_34 >= 12 - player->unk_30 * 2 &&
            func_80107648_baby_bowser_bonkers(object) == 0 && actor->unk_04 != 0) {
            D_800D5558_main[player->unk_2A] |= 0x8000;
        }
        if (data->unk38 != 1000.0f) {
            D_800CDA7C_main[player->unk_2A] |= 0x8000;
        } else if ((func_801093D4_baby_bowser_bonkers(actor->unk_00) < 15.0f && player->unk_34 >= player->unk_36 &&
                    player->unk_38 <= dist) ||
                   (ready && !(rand8() & 0xF))) {
            func_801091D4_baby_bowser_bonkers(object->trans.x, object->trans.z, D_8010BC00_baby_bowser_bonkers);
            for (i = 0; i < 14; i++) {
                if (func_801093D4_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers[i]->unk_00) >= 225) {
                    model = &Hu3DData[D_8010BC00_baby_bowser_bonkers[i]->unk_02];
                    dx2 = model->pos.x - object->trans.x;
                    dz2 = model->pos.z - object->trans.z;
                    if (sqrtf(dx2 * dx2 + dz2 * dz2) <= player->unk_38) {
                        player->unk_32 = i;
                        return;
                    }
                }
            }
        }
        if (actor->unk_06 != 4 && actor->unk_06 != 5 &&
            (actor->unk_04 != 0 || func_80107648_baby_bowser_bonkers(object) != 0)) {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            scale = dist / 100.0;
            if (scale >= 1.0f) {
                scale = 1.0f;
            }
            D_800CBB6E_main[player->unk_2A] = dx * 64.0f * scale;
            D_800D20A1_main[player->unk_2A] = -(dz * 64.0f * scale);
        } else if (player->unk_34 >= player->unk_36) {
            player->unk_32 = -1;
        } else {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            scale = dist / 100.0;
            if (scale >= 1.0f) {
                scale = 1.0f;
            }
            D_800CBB6E_main[player->unk_2A] = dx * 64.0f * scale;
            D_800D20A1_main[player->unk_2A] = -(dz * 64.0f * scale);
        }
    } else {
        func_801091D4_baby_bowser_bonkers(object->trans.x, object->trans.z, D_8010BC00_baby_bowser_bonkers);
        count = 7 - (s32)(player->unk_30 * 1.5f);
        if (count <= 0) {
            count = 1;
        }
        player->unk_32 = func_8010943C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, count, player->unk_00 ^ 1);
        if (player->unk_32 == -1) {
            player->unk_32 =
                func_8010958C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, count, player->unk_00 ^ 1);
        }
        player->unk_36 = 39.0f - player->unk_30 * 7.5f;
        player->unk_34 = 0;
    }
    player->unk_34++;
}

void func_801075F4_baby_bowser_bonkers(omObjData *arg0, f32 arg1, f32 arg2) {
    BabyBowserBonkersPlayer *player = func_8010B3AC_baby_bowser_bonkers(arg0);

    player->unk_02++;
    player->unk_44 = arg1;
    player->unk_48 = arg2;
    func_80109E98_baby_bowser_bonkers(player->unk_00, player->unk_02);
}

s32 func_80107648_baby_bowser_bonkers(omObjData *object) {
    return object->trans.y >= 44.1000009328126907;
}

void func_80107678_baby_bowser_bonkers(omObjData *arg0, s32 arg1, s32 arg2) {
    HmfModel *model;
    HmfModel *otherModel;
    HmfData *temp;

    model = &Hu3DData[arg0->model[(s16)arg1]];
    otherModel = &Hu3DData[arg0->model[(s16)arg2]];

    temp = model->hmf;
    model->hmf = otherModel->hmf;
    otherModel->hmf = temp;
}

void func_801076D8_baby_bowser_bonkers(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed) {
    omObjData *mover;
    omObjData *other;
    func_800E1BA8_minigame_ObjData *moverData;
    func_800E1BA8_minigame_ObjData *otherData;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 minDist;
    f32 scale;
    f32 limit;
    f32 pushX;
    f32 pushZ;
    u16 pushed;

    pushed = 0;
    if (recursed == 0) {
        if ((vel1->x != 0.0f || vel1->z != 0.0f) && vel2->x == 0.0f && vel2->z == 0.0f) {
            mover = obj1;
            other = obj2;
        } else if ((vel2->x != 0.0f || vel2->z != 0.0f) && vel1->x == 0.0f && vel1->z == 0.0f) {
            mover = obj2;
            other = obj1;
        } else if (obj1->trans.y > obj2->trans.y) {
            mover = obj1;
            other = obj2;
        } else if (obj2->trans.y > obj1->trans.y) {
            mover = obj2;
            other = obj1;
        } else {
            mover = obj1;
            other = obj2;
        }
    } else {
        mover = obj1;
        other = obj2;
    }
    moverData = mover->data;
    otherData = other->data;
    dx = mover->trans.x - other->trans.x;
    dz = mover->trans.z - other->trans.z;
    dist = sqrtf(dx * dx + dz * dz);
    minDist = (moverData->unk48 + otherData->unk48) * 0.75f;
    if (dist < minDist && mover->trans.y >= other->trans.y &&
        mover->trans.y <= other->trans.y + otherData->unk34) {
        if (dist != 0.0f) {
            scale = minDist / dist;
        } else {
            if (minDist == 0.0f) {
                dx = dz = 0.0f;
            } else {
                if (other->trans.x >= 0.0f) {
                    dx = minDist / 1.4142f;
                } else {
                    dx = -minDist / 1.4142f;
                }
                if (other->trans.z >= 0.0f) {
                    dz = minDist / 1.4142f;
                } else {
                    dz = -minDist / 1.4142f;
                }
            }
            scale = 1.0f;
        }
        mover->trans.x = dx * scale + other->trans.x;
        mover->trans.z = dz * scale + other->trans.z;
        pushed = 1;
    }
    pushZ = 0.0f;
    pushX = 0.0f;
    limit = 469.999980926513672 - moverData->unk48;
    if (mover->trans.x > limit) {
        pushX = limit - mover->trans.x;
        mover->trans.x = limit;
    } else if (mover->trans.x < -limit) {
        pushX = -limit - mover->trans.x;
        mover->trans.x = -limit;
    }
    if (mover->trans.z > limit) {
        pushZ = limit - mover->trans.x;
        mover->trans.z = limit;
    } else if (mover->trans.z < -limit) {
        pushZ = -limit - mover->trans.x;
        mover->trans.z = -limit;
    }
    limit = 469.999980926513672 - otherData->unk48;
    if (other->trans.x > limit) {
        other->trans.x = limit;
    } else if (other->trans.x < -limit) {
        other->trans.x = -limit;
    }
    if (other->trans.z > limit) {
        other->trans.z = limit;
    } else if (other->trans.z < -limit) {
        other->trans.z = -limit;
    }
    if (pushX == 0.0f && pushZ == 0.0f) {
        return;
    }
    if (pushed) {

        dx = mover->trans.x - other->trans.x;
        dz = mover->trans.z - other->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < minDist && mover->trans.y >= other->trans.y &&

            mover->trans.y <= otherData->unk34 * 0.5f + other->trans.y) {
            other->trans.x += pushX;
            other->trans.z += pushZ;
            if (other->trans.x > limit) {
                other->trans.x = limit;
            } else if (other->trans.x < -limit) {
                other->trans.x = -limit;
            }
            if (other->trans.z > limit) {
                other->trans.z = limit;
            } else if (other->trans.z < -limit) {
                other->trans.z = -limit;
            }
        }
        if (recursed == 0) {
            func_801076D8_baby_bowser_bonkers(other, mover, NULL, NULL, 1);
        }
    }
}

void func_80107CD8_baby_bowser_bonkers(void) {
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_80107D38_baby_bowser_bonkers);
    func_800E1490_minigame(0);
}

void func_80107D38_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersStageWork *work;

    work = HuMemAllocTag(sizeof(BabyBowserBonkersStageWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(BabyBowserBonkersStageWork));
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    func_800E139C_minigame(object, 39.100002f, -939.99994f, -939.99994f, 939.99994f, 939.99994f);
    object->model[0] = Hu3DModelRead2(0x560000, 0x10099);
    Hu3DModelVtxBufMake(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->model[1] = Hu3DModelRead2(0x560001, 0x99);
    object->model[2] = Hu3DModelRead2(0x560002, 0x99);
    object->func = func_80107E54_baby_bowser_bonkers;
}

void func_80107E54_baby_bowser_bonkers(omObjData *object) {
    Hu3DModelTexScroll(object->model[0], sindf(D_8010B8EC_baby_bowser_bonkers) * 15.0f,
                       -D_8010B8F0_baby_bowser_bonkers, 64, 64);
    Hu3DModelPrimColorSet(object->model[0], (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f), 0, 0,
                       (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f));
    Hu3DModelEnvColorSet(object->model[0], 64, 32, 32, 0);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010B8EC_baby_bowser_bonkers += 0.5f;
        if (D_8010B8EC_baby_bowser_bonkers >= 360.0f) {
            D_8010B8EC_baby_bowser_bonkers -= 360.0f;
        }
        D_8010B8F0_baby_bowser_bonkers += 0.2f;
        if (D_8010B8F0_baby_bowser_bonkers >= 64.0f) {
            D_8010B8F0_baby_bowser_bonkers -= 64.0f;
        }
        D_8010B8F4_baby_bowser_bonkers += 2.4f;
        if (D_8010B8F4_baby_bowser_bonkers >= 360.0f) {
            D_8010B8F4_baby_bowser_bonkers -= 360.0f;
        }
    }
}

s32 func_801080D0_baby_bowser_bonkers(f32 arg0, f32 arg1) {
    if (__builtin_fabs((f64)arg0) < 200.0 && __builtin_fabs((f64)arg1) < 200.0) {
        return 0;
    }
    if (arg0 > 0.0f) {
        if (arg1 > 0.0f) {
            return 1;
        }
        return 2;
    }
    if (arg1 > 0.0f) {
        return 3;
    }
    return 4;
}

void func_80108160_baby_bowser_bonkers(void) {
    D_8010BC60_baby_bowser_bonkers = HuMemAllocTag(sizeof(BabyBowserBonkersActor) * 14, TAG_OVERLAY);
    memset(D_8010BC60_baby_bowser_bonkers, 0, sizeof(BabyBowserBonkersActor) * 14);
    omAddObj(2, 8, 0, -1, func_801081C0_baby_bowser_bonkers);
    func_80109704_baby_bowser_bonkers();
}

void func_801081C0_baby_bowser_bonkers(omObjData *object) {
    s32 i;
    BabyBowserBonkersActor *actor;

    object->func = func_8010831C_baby_bowser_bonkers;
    for (actor = D_8010BC60_baby_bowser_bonkers, i = 0; i < 14; i++, actor++) {
        if (i == 0) {
            actor->unk_02 = Hu3DModelRead2(0x560003, 0x299);
        } else {
            actor->unk_02 = Hu3DModelLink(D_8010BC60_baby_bowser_bonkers->unk_02);
        }
        actor->unk_00 = i;
        actor->unk_04 = -1;
        actor->unk_08 = 0;
        actor->unk_06 = actor->unk_0A = actor->unk_0C = actor->unk_0E = 0;
        actor->unk_10 = 0;
        actor->unk_12 = 0;
        actor->unk_14 = 0.0f;
        actor->unk_18 = 0.0f;
        actor->unk_1C = D_8010B400_baby_bowser_bonkers[i].y - 110.000002384185791;
        actor->unk_20 = 65.0f;
        actor->unk_24 = 70.0f;
        actor->unk_28 = func_801089CC_baby_bowser_bonkers;
        actor->unk_2C = func_801089CC_baby_bowser_bonkers;
        Hu3DModelPosSet(actor->unk_02, D_8010B400_baby_bowser_bonkers[i].x, D_8010B400_baby_bowser_bonkers[i].y,
                        D_8010B400_baby_bowser_bonkers[i].z - 20.0000002980232239);
    }
}

void func_8010831C_baby_bowser_bonkers(omObjData *object) {
    s32 i;
    BabyBowserBonkersActor *actor;
    HmfModel *model;

    for (actor = D_8010BC60_baby_bowser_bonkers, i = 0; i < 14; i++, actor++) {
        model = Hu3DData + actor->unk_02;
        if (actor->unk_2C != NULL) {
            actor->unk_2C(actor);
        }
        model->pos.y = actor->unk_1C + actor->unk_18;
        if (actor->unk_04 != 0) {
            actor->unk_08 = func_80108454_baby_bowser_bonkers(actor);
            if (actor->unk_08 != -1) {
                HuAudFXPlay(0x4AD);
                actor->unk_2C = func_80108E90_baby_bowser_bonkers;
            }
        }
        if (model->motSpeed < 0.0f && model->motTime + model->motSpeed <= 0.0f) {
            model->motSpeed = 0.0f;
        }
        if (actor->unk_28 == actor->unk_2C) {
            actor->unk_0A++;
        } else {
            actor->unk_28 = actor->unk_2C;
            actor->unk_0A = 0;
        }
    }
}

s16 func_80108454_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    s16 order[4];
    s16 i;
    HmfModel *model;
    omObjData *obj;
    func_800E1BA8_minigame_ObjData *data;
    BabyBowserBonkersPlayer *player;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 radius;
    f32 speed;
    s16 stickX;
    s16 stickY;
    s16 pad;

    if (D_8010BC40_baby_bowser_bonkers & 1) {
        for (i = 0; i < D_800EC280_minigame; i++) {
            order[i] = i;
        }
    } else {
        for (i = 0; i < D_800EC280_minigame; i++) {
            order[i] = D_800EC280_minigame - i - 1;
        }
    }
    model = Hu3DData + actor->unk_02;
    for (i = 0; i < D_800EC280_minigame; i++) {
        obj = D_800EC598_minigame[order[i]];
        data = obj->data;
        player = func_8010B3AC_baby_bowser_bonkers(obj);
        dx = obj->trans.x - model->pos.x;
        dz = obj->trans.z - model->pos.z;
        dist = sqrtf(dx * dx + dz * dz);
        radius = data->unk48 + actor->unk_20;
        if (!(obj->trans.y + data->unk34 < model->pos.y) &&
            !(actor->unk_24 * model->scale.y + model->pos.y < obj->trans.y) && dist < radius) {
            if (data->unk38 == 1000.0f) {
                obj->trans.y = actor->unk_24 * 1.2f + model->pos.y;
                func_800E5798_minigame(obj, 6);
                data->unk38 = -D_800EB744_minigame;
                data->unk50 &= ~0x80;
                data->unk40 = 0.0f;
                func_800E4C88_minigame(obj, player->unk_4C + 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
                omVibrate(player->unk_28, 10, 0, 10);
                if (++player->unk_4C >= 3) {
                    player->unk_4C = 0;
                }
                func_801075F4_baby_bowser_bonkers(obj, model->pos.x, model->pos.z);
                return order[i];
            } else {
                obj->trans.y = actor->unk_24 * 1.2f + model->pos.y;
                pad = GwPlayer[order[i]].pad;
                stickX = D_800CBB6E_main[pad];
                if (abs(stickX) < 9) {
                    stickX = 0;
                }
                stickY = D_800D20A1_main[pad];
                if (abs(stickY) < 9) {
                    stickY = 0;
                }
                if ((stickX != 0) | (stickY != 0)) {
                    if (stickX > 60) {
                        stickX = 60;
                    } else if (stickX < -60) {
                        stickX = -60;
                    }
                    if (stickY > 60) {
                        stickY = 60;
                    } else if (stickY < -60) {
                        stickY = -60;
                    }
                    data->unk3C = atan2df(stickX, -stickY) + data->unk60;
                    speed = D_800EB760_minigame * 0.5f;
                    data->unk40 = speed * (sqrtf(stickX * stickX + stickY * stickY) / 60.0f);
                }
                func_800E5798_minigame(obj, 6);
                data->unk50 &= ~0x80;
                if ((u16)D_800CDA7C_main[pad] & 0x8000) {
                    data->unk38 = -D_800EB744_minigame;
                } else {
                    data->unk38 = -D_800EB744_minigame * 0.75f;
                }
                func_800E4C88_minigame(obj, player->unk_4C + 7, obj->trans.x, obj->trans.y, obj->trans.z, 0.0f, 0.0f);
                omVibrate(player->unk_28, 10, 0, 10);
                if (++player->unk_4C >= 3) {
                    player->unk_4C = 0;
                }
                func_801075F4_baby_bowser_bonkers(obj, model->pos.x, model->pos.z);
                return order[i];
            }
        }
    }
    return -1;
}

void func_801089CC_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;

    actor->unk_06 = 0;
    actor->unk_04 = 0;
    actor->unk_08 = -1;
    actor->unk_18 = 0;
    model->attr |= HU3D_ATTR_DISPOFF;
}

void func_80108A0C_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 t;
    f32 scale;

    actor->unk_06 = 1;
    if (actor->unk_0C != 0) {
        t = (f32)actor->unk_0A / (f32)actor->unk_0C;
    } else {
        t = 1.0f;
    }
    actor->unk_18 = t * 110.0f;
    scale = t * 0.8f + 0.2f;
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
    if (t > 0.3f) {
        actor->unk_04 = 0;
    } else {
        actor->unk_04 = 1;
    }
    if (actor->unk_10 != 0 && actor->unk_0A >= 7 && model->motSpeed == 0.0f) {
        if (--actor->unk_10 <= 0) {
            model->motSpeed = 1.0f;
            model->motTime = 0.0f;
        } else {
            actor->unk_0A--;
        }
    }
    if (t >= 1.0f) {
        actor->unk_0A = 0;
        actor->unk_2C = func_80108B84_baby_bowser_bonkers;
    }
}

void func_80108B84_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;

    actor->unk_06 = 2;
    actor->unk_04 = 1;
    switch (actor->unk_12) {
        case 1:
            if (actor->unk_14 < 20.0f) {
                actor->unk_14 += 2.5f;
            }
            model->rot.y = sindf((f32)actor->unk_0A / (f32)actor->unk_0E * 720.0f) * actor->unk_14;
            break;
        case 2:
        case 3:
            if (actor->unk_14 < 20.0f) {
                actor->unk_14 += 2.5f;
            }
            model->rot.y = -(sindf((f32)actor->unk_0A / (f32)actor->unk_0E * 720.0f) * actor->unk_14);
            break;
    }
    if (actor->unk_0A >= actor->unk_0E - 7 && model->motSpeed >= 0.0f) {
        model->motSpeed = -1.5f;
        model->motTime = 30.0f;
    }
    if (actor->unk_0A >= actor->unk_0E) {
        actor->unk_0A = 0;
        actor->unk_2C = func_80108D6C_baby_bowser_bonkers;
    }
}

void func_80108D6C_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 t;
    f32 scale;

    actor->unk_06 = 3;
    if (actor->unk_0C != 0) {
        t = (f32)actor->unk_0A / (f32)actor->unk_0C;
    } else {
        t = 1.0f;
    }
    actor->unk_18 = (1.0f - t) * 110.0f;
    scale = (1.0f - t) * 0.8f + 0.2f;
    model->scale.x = scale;
    model->scale.y = scale;
    model->scale.z = scale;
    if (t < 0.3f) {
        actor->unk_04 = 0;
    } else {
        actor->unk_04 = 1;
    }
    if (t >= 1.0f) {
        model->attr |= HU3D_ATTR_DISPOFF;
        actor->unk_0A = 0;
        actor->unk_2C = func_801089CC_baby_bowser_bonkers;
    }
}

void func_80108E90_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 4;
    actor->unk_04 = 0;
    actor->unk_18 = 110.0f;
    scale = 1.0f - (f32)actor->unk_0A / 5.0f;
    if (scale <= 0.0f) {
        scale = 0.0f;
    }
    model->scale.x = 1.0f;
    model->scale.z = 1.0f;
    model->scale.y = 0.4f - scale * 0.35f;
    model->motSpeed = 0.0f;
    if (15.0f <= (f32)actor->unk_0A) {
        actor->unk_0A = 0;
        actor->unk_2C = func_80108F9C_baby_bowser_bonkers;
    }
}

void func_80108F9C_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 5;
    actor->unk_04 = 0;
    actor->unk_18 -= 9.166667f;
    scale = model->scale.z - 0.2f;
    model->scale.z = scale;
    model->scale.x = scale;
    if (scale <= 0.1f) {
        model->scale.x = model->scale.z = 0.0f;
    }
    if (actor->unk_18 <= 0.0f) {
        model->attr |= HU3D_ATTR_DISPOFF;
        model->scale.y = 1.0f;
        actor->unk_0A = 0;
        actor->unk_2C = func_801089CC_baby_bowser_bonkers;
    }
}

s32 func_80109080_baby_bowser_bonkers(s32 arg0, s16 arg1, s16 arg2) {
    BabyBowserBonkersActor *actor;
    HmfModel *model;

    if (arg0 >= 14) {
        return -1;
    }
    if (arg0 < 0) {
        return -1;
    }
    actor = &D_8010BC60_baby_bowser_bonkers[arg0];
    model = Hu3DData + actor->unk_02;
    if (actor->unk_06 != 0) {
        return -1;
    }
    actor->unk_0C = arg1;
    actor->unk_0E = arg2;
    actor->unk_0A = 0;
    actor->unk_10 = 15;
    actor->unk_14 = 0.0f;
    if (!(rand8() & 3)) {
        actor->unk_12 = rand8() % 3 + 1;
    } else {
        actor->unk_12 = 0;
    }
    actor->unk_2C = func_80108A0C_baby_bowser_bonkers;
    model->attr &= ~HU3D_ATTR_DISPOFF;
    model->rot.x = model->rot.y = model->rot.z = 0.0f;
    model->motTime = model->motSpeed = 0.0f;
    return arg0;
}

BabyBowserBonkersActor *func_8010919C_baby_bowser_bonkers(s32 arg0) {
    if (arg0 < 14) {
        if (arg0 >= 0) {
            return &D_8010BC60_baby_bowser_bonkers[arg0];
        }
    }
    return NULL;
}

void func_801091D4_baby_bowser_bonkers(f32 x, f32 z, BabyBowserBonkersActor **list) {
    s32 i;
    s32 j;
    HmfModel *model1;
    HmfModel *model2;
    f32 dx;
    f32 dz;
    f32 dist;
    BabyBowserBonkersActor *temp;

    for (i = 0; i < 14; i++) {
        list[i] = &D_8010BC60_baby_bowser_bonkers[i];
    }
    for (i = 0; i < 13; i++) {
        for (j = i + 1; j < 14; j++) {
            model1 = Hu3DData + list[i]->unk_02;
            model2 = Hu3DData + list[j]->unk_02;
            dx = model1->pos.x - x;
            dz = model1->pos.z - z;
            dist = sqrtf(dx * dx + dz * dz);
            dx = model2->pos.x - x;
            dz = model2->pos.z - z;
            if (sqrtf(dx * dx + dz * dz) < dist) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

s32 func_80109388_baby_bowser_bonkers(BabyBowserBonkersActor *arg0, s32 arg1) {
    if (arg0->unk_08 == 0) {
        return 0;
    }
    switch (arg0->unk_06) {
        case 1:
            return 1;
        case 2:
            if (arg0->unk_0A > arg0->unk_0E - arg1) {
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801093D4_baby_bowser_bonkers(s32 arg0) {
    BabyBowserBonkersActor *actor = &D_8010BC60_baby_bowser_bonkers[arg0];

    if (actor->unk_08 != 0) {
        switch (actor->unk_06) {
            case 1:
                return actor->unk_0E;
            case 2:
                return actor->unk_0E - actor->unk_0A;
        }
    }
    return 0;
}

s32 func_8010943C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s32 playerIndex) {
    s32 candidates[16];
    s32 i;
    s32 n;
    s32 quadrant;
    HmfModel *model;

    quadrant = func_801080D0_baby_bowser_bonkers(D_800EC598_minigame[playerIndex]->trans.x,
                                                 D_800EC598_minigame[playerIndex]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        model = Hu3DData + list[i]->unk_02;
        if (func_80109388_baby_bowser_bonkers(list[i], 9) == 0) {
            continue;
        }
        if (func_801080D0_baby_bowser_bonkers(model->pos.x, model->pos.z) != quadrant) {
            candidates[n] = list[i]->unk_00;
            n++;
            if (n >= count) {
                break;
            }
        }
    }
    if (n == 0) {
        return -1;
    }
    return candidates[rand8() % n];
}

s32 func_8010958C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s32 playerIndex) {
    s32 candidates[16];
    s32 i;
    s32 n;
    s32 quadrant;
    HmfModel *model;

    quadrant = func_801080D0_baby_bowser_bonkers(D_800EC598_minigame[playerIndex]->trans.x,
                                                 D_800EC598_minigame[playerIndex]->trans.z);
    for (i = 0, n = 0; i < 14; i++) {
        model = Hu3DData + list[i]->unk_02;
        if (list[i]->unk_04 == 0) {
            continue;
        }
        if (func_801080D0_baby_bowser_bonkers(model->pos.x, model->pos.z) != quadrant) {
            candidates[n] = list[i]->unk_00;
            n++;
            if (n >= count) {
                break;
            }
        }
    }
    if (n == 0) {
        return -1;
    }
    return candidates[rand8() % n];
}

s32 func_801096D0_baby_bowser_bonkers(void) {
    s32 i;
    BabyBowserBonkersActor *actor;

    for (i = 0, actor = D_8010BC60_baby_bowser_bonkers; i < 14; i++, actor++) {
        if (actor->unk_06 != 0) {
            return 0;
        }
    }
    return 1;
}

void func_80109704_baby_bowser_bonkers(void) {
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    BabyBowserBonkersPattern *temp;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            D_8010BC68_baby_bowser_bonkers[i][j] = D_8010B8F8_baby_bowser_bonkers[i][j % D_8010B908_baby_bowser_bonkers[i]];
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 255; j++) {
            a = rand8() & 3;
            b = rand8() & 3;
            if (a != b) {
                temp = D_8010BC68_baby_bowser_bonkers[i][a];
                D_8010BC68_baby_bowser_bonkers[i][a] = D_8010BC68_baby_bowser_bonkers[i][b];
                D_8010BC68_baby_bowser_bonkers[i][b] = temp;
            }
        }
    }
}

u16 func_8010984C_baby_bowser_bonkers(s32 dirAndFile) {
    void *data;
    u16 sprite;

    data = DataRead(dirAndFile);
    sprite = HuSprAnimRead(data);
    DataClose(data);
    return sprite;
}

void func_80109890_baby_bowser_bonkers(void) {
    s32 i;
    UnkBabyBowserBonkers *entry;

    D_8010BCA8_baby_bowser_bonkers = HuMemAllocTag(0x20, TAG_OVERLAY);
    D_8010BCAC_baby_bowser_bonkers = HuMemAllocTag(sizeof(UnkBabyBowserBonkers) * 2, TAG_OVERLAY);
    D_8010BCA8_baby_bowser_bonkers[0] = func_8010984C_baby_bowser_bonkers(0x31);
    D_8010BCA8_baby_bowser_bonkers[1] = func_8010984C_baby_bowser_bonkers(0x560004);
    for (i = 0, entry = D_8010BCAC_baby_bowser_bonkers; i < 2; i++, entry++) {
        memset(entry, 0, sizeof(UnkBabyBowserBonkers));
        func_80109BFC_baby_bowser_bonkers(i, GwPlayer[D_8010BC58_baby_bowser_bonkers[i].unk_28].chr);
    }
    omAddObj(30, 0, 0, -1, func_80109990_baby_bowser_bonkers);
}

void func_80109990_baby_bowser_bonkers(omObjData *object) {
    s16 i;
    UnkBabyBowserBonkers *entry;
    u16 digits[2];
    f32 scale;

    for (i = 0, entry = D_8010BCAC_baby_bowser_bonkers; i < 2; i++, entry++) {
        digits[0] = entry->unk_0C / 10;
        digits[1] = entry->unk_0C - digits[0] * 10;
        if (digits[0] >= 10) {
            digits[0] = 9;
        }
        if (digits[1] >= 10) {
            digits[1] = 9;
        }
        HuSprPatNoSet(entry->unk_02, 0, (s16)digits[0]);
        HuSprPatNoSet(entry->unk_02, 1, (s16)digits[1]);
        if (entry->unk_0C < entry->unk_0E && entry->unk_10 == 0) {
            entry->unk_10 = 12;
            if (++entry->unk_0C == 10) {
                HuSprAttrReset(entry->unk_02, 0, HUSPR_ATTR_DISPOFF);
            }
        }
        scale = sindf(entry->unk_10 / 12.0f * 180.0f) * 0.5f + 1.0f;
        HuSprPosSet(entry->unk_02, 0, entry->unk_04 + entry->unk_08[0] * scale, entry->unk_06);
        HuSprPosSet(entry->unk_02, 1, entry->unk_04 + entry->unk_08[1] * scale, entry->unk_06);
        HuSprScaleSet(entry->unk_02, 0, scale, scale);
        HuSprScaleSet(entry->unk_02, 1, scale, scale);
        if (entry->unk_10 != 0) {
            entry->unk_10--;
        }
    }
}

void func_80109BFC_baby_bowser_bonkers(s32 index, s32 chr) {
    UnkBabyBowserBonkers *entry;
    s32 group;
    s32 x;
    s32 y;
    s32 i;

    entry = &D_8010BCAC_baby_bowser_bonkers[index];
    entry->unk_00 = func_8010984C_baby_bowser_bonkers(D_8010B918_baby_bowser_bonkers[chr]);
    group = HuSprGrpCreate(4, 0);
    entry->unk_02 = group;
    x = 266;
    if (index == 0) {
        x = 56;
    }
    y = 30;
    entry->unk_04 = x + 8;
    entry->unk_06 = y;
    entry->unk_08[0] = -6;
    entry->unk_08[1] = 6;
    entry->unk_0C = entry->unk_0E = entry->unk_10 = 0;
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                HuSprAttrSet(group, i, 0x8000);
            case 1:
                HuSprGrpMemberSet(group, i, D_8010BCA8_baby_bowser_bonkers[0], 0);
                HuSprPosSet(group, i, entry->unk_04 + entry->unk_08[i], y);
                break;
            case 2:
                HuSprGrpMemberSet(group, i, entry->unk_00, 0);
                HuSprPosSet(group, i, x - 18, y);
                break;
            case 3:
                HuSprGrpMemberSet(group, i, D_8010BCA8_baby_bowser_bonkers[1], 0);
                HuSprPosSet(group, i, x, y);
                HuSprScaleSet(group, i, 1.0f, 1.0f);
                HuSprColorTPLvlSet(group, i, 0, 0, 255, 160);
                break;
        }
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(group, i, 0);
        HuSprAttrSet(group, i, 0x1000);
        HuSprPriSet(group, i, i - 16);
    }
}

void func_80109E98_baby_bowser_bonkers(s32 arg0, s16 arg1) {
    s16 *field = &D_8010BCAC_baby_bowser_bonkers[arg0].unk_0E;

    *field = arg1;
}

void func_80109EB8_baby_bowser_bonkers(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = -708.8f;
    Center.z = -781.8f;
    CRot.x = 318.38f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2938.0f;
    func_8010AB14_baby_bowser_bonkers(0);
    func_8010AB14_baby_bowser_bonkers(1);
    D_8010BD00_baby_bowser_bonkers = 0;
    D_8010BCFC_baby_bowser_bonkers = 0;
    D_8010BCF8_baby_bowser_bonkers = 0;
    omAddObj(31, 0, 0, -1, func_8010A6D8_baby_bowser_bonkers);
    camera = gCameraList;
    for (i = 1; i < D_800D1FF0_main; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

void func_80109FE8_baby_bowser_bonkers(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (D_8010B938_baby_bowser_bonkers) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & A_BUTTON) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & B_BUTTON) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & START_BUTTON) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                delta.rot.x = (f32)D_800D20A1_main[0] * 0.125 * speed;
                delta.rot.y = (f32)D_800CBB6E_main[0] * 0.125 * speed;
                if (D_800CDA7C_main[0] & L_JPAD) {
                    delta.center.x = speed * 2.0;
                }
                if (D_800CDA7C_main[0] & R_JPAD) {
                    delta.center.x = -(speed * 2.0);
                }
                if (D_800CDA7C_main[0] & U_JPAD) {
                    delta.center.z = -(speed * 2.0);
                }
                if (D_800CDA7C_main[0] & D_JPAD) {
                    delta.center.z = speed * 2.0;
                }
                if (D_800CDA7C_main[0] & U_CBUTTONS) {
                    delta.center.y = speed * 2.0;
                }
                if (D_800CDA7C_main[0] & D_CBUTTONS) {
                    delta.center.y = -(speed * 2.0);
                }
                if (D_800CDA7C_main[0] & R_CBUTTONS) {
                    delta.zoom = speed * 2.0;
                }
                if (D_800CDA7C_main[0] & L_CBUTTONS) {
                    delta.zoom = -(speed * 2.0);
                }
                delta.center.x += Center.x;
                delta.center.y += Center.y;
                delta.center.z += Center.z;
                delta.rot.x += CRot.x;
                delta.rot.y += CRot.y;
                delta.rot.z += CRot.z;
                delta.zoom += CZoom;
                func_8010AD00_baby_bowser_bonkers(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                                  delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 104,
                   D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_8010B93C_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_8010B93C_baby_bowser_bonkers--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_8010B940_baby_bowser_bonkers++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_8010B940_baby_bowser_bonkers--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010B93C_baby_bowser_bonkers + 20, (s16)D_8010B940_baby_bowser_bonkers + 104,
                   D_800D5218_main);
            break;
        case 3:
            D_8010B938_baby_bowser_bonkers = 0;
            break;
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_8010B938_baby_bowser_bonkers == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010B938_baby_bowser_bonkers++ >= 4) {
            D_8010B938_baby_bowser_bonkers = 0;
        }
    }
}

void func_8010A6D8_baby_bowser_bonkers(omObjData *object) {
    f32 t;

    if (D_8010BCFC_baby_bowser_bonkers <= 0) {
        func_8010AEF0_baby_bowser_bonkers(0);
        D_8010BD00_baby_bowser_bonkers = 0;
        return;
    }
    if (D_8010BCF8_baby_bowser_bonkers == 0) {
        Center.x = D_8010BCB0_baby_bowser_bonkers[0].center.x;
        Center.y = D_8010BCB0_baby_bowser_bonkers[0].center.y;
        Center.z = D_8010BCB0_baby_bowser_bonkers[0].center.z;
        CRot.x = D_8010BCB0_baby_bowser_bonkers[0].rot.x;
        CRot.y = D_8010BCB0_baby_bowser_bonkers[0].rot.y;
        CRot.z = D_8010BCB0_baby_bowser_bonkers[0].rot.z;
        CZoom = D_8010BCB0_baby_bowser_bonkers[0].zoom;
        if (CRot.x >= 360.0) {
            CRot.x -= 360.0;
        } else if (CRot.x < 0.0) {
            CRot.x += 360.0;
        }
        if (CRot.y >= 360.0) {
            CRot.y -= 360.0;
        } else if (CRot.y < 0.0) {
            CRot.y += 360.0;
        }
        if (CRot.z >= 360.0) {
            CRot.z -= 360.0;
        } else if (CRot.z < 0.0) {
            CRot.z += 360.0;
        }
        D_8010BCFC_baby_bowser_bonkers = 0;
    } else {
        t = (f32)D_8010BCF8_baby_bowser_bonkers / (f32)D_8010BCFC_baby_bowser_bonkers;
        Center.x = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.x,
                                                     D_8010BCB0_baby_bowser_bonkers[1].center.x);
        Center.y = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.y,
                                                     D_8010BCB0_baby_bowser_bonkers[1].center.y);
        Center.z = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].center.z,
                                                     D_8010BCB0_baby_bowser_bonkers[1].center.z);
        CRot.x = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.x,
                                                   D_8010BCB0_baby_bowser_bonkers[1].rot.x);
        CRot.y = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.y,
                                                   D_8010BCB0_baby_bowser_bonkers[1].rot.y);
        CRot.z = func_8010B320_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].rot.z,
                                                   D_8010BCB0_baby_bowser_bonkers[1].rot.z);
        CZoom = func_8010B308_baby_bowser_bonkers(t, D_8010BCB0_baby_bowser_bonkers[0].zoom,
                                                  D_8010BCB0_baby_bowser_bonkers[1].zoom);
        if (CRot.x >= 360.0) {
            CRot.x -= 360.0;
        } else if (CRot.x < 0.0) {
            CRot.x += 360.0;
        }
        if (CRot.y >= 360.0) {
            CRot.y -= 360.0;
        } else if (CRot.y < 0.0) {
            CRot.y += 360.0;
        }
        if (CRot.z >= 360.0) {
            CRot.z -= 360.0;
        } else if (CRot.z < 0.0) {
            CRot.z += 360.0;
        }
        if (D_8010BCF8_baby_bowser_bonkers > 0) {
            D_8010BCF8_baby_bowser_bonkers--;
        } else {
            D_8010BCF8_baby_bowser_bonkers++;
        }
    }
    D_8010BD00_baby_bowser_bonkers = 1;
    func_8010AEF0_baby_bowser_bonkers(0);
}

void func_8010AB14_baby_bowser_bonkers(s32 arg0) {
    if (CRot.x >= 360.0) {
        CRot.x -= 360.0;
    } else if (CRot.x < 0.0) {
        CRot.x += 360.0;
    }
    if (CRot.y >= 360.0) {
        CRot.y -= 360.0;
    } else if (CRot.y < 0.0) {
        CRot.y += 360.0;
    }
    if (CRot.z >= 360.0) {
        CRot.z -= 360.0;
    } else if (CRot.z < 0.0) {
        CRot.z += 360.0;
    }
    D_8010BCB0_baby_bowser_bonkers[arg0].center.x = Center.x;
    D_8010BCB0_baby_bowser_bonkers[arg0].center.y = Center.y;
    D_8010BCB0_baby_bowser_bonkers[arg0].center.z = Center.z;
    D_8010BCB0_baby_bowser_bonkers[arg0].rot.x = CRot.x;
    D_8010BCB0_baby_bowser_bonkers[arg0].rot.y = CRot.y;
    D_8010BCB0_baby_bowser_bonkers[arg0].rot.z = CRot.z;
    D_8010BCB0_baby_bowser_bonkers[arg0].zoom = CZoom;
    D_8010BCB0_baby_bowser_bonkers[arg0].unk_1C = D_8010BCB0_baby_bowser_bonkers[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010AD00_baby_bowser_bonkers(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010BCF8_baby_bowser_bonkers = frames - 1;
        D_8010BCFC_baby_bowser_bonkers = frames;
        if (x != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = x;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = y;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = z;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = rotX;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = rotY;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = rotZ;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = zoom;
        } else {
            D_8010BCB0_baby_bowser_bonkers[0].zoom = CZoom;
        }
        func_8010AB14_baby_bowser_bonkers(1);
    }
}

void func_8010AEF0_baby_bowser_bonkers(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRot.x;
    f32 rotY = CRot.y;

    camera->pos.x = Center.x + sindf(rotY) * cosdf(rotX) * CZoom;
    camera->pos.y = -sindf(rotX) * CZoom + Center.y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoom + Center.z;
    camera->at.x = Center.x;
    camera->at.y = Center.y;
    camera->at.z = Center.z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

f32 func_8010B044_baby_bowser_bonkers(f32 arg0, f32 arg1) {
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

f32 func_8010B148_baby_bowser_bonkers(f32 target, f32 current, f32 step) {
    f32 diff;
    f32 delta;

    if (target >= 360.0) {
        target -= 360.0;
    } else if (target < 0.0) {
        target += 360.0;
    }
    if (current >= 360.0) {
        current -= 360.0;
    } else if (current < 0.0) {
        current += 360.0;
    }
    diff = fmod(target - current + 360.0, 360.0);
    if (diff < 180.0) {
        if (diff <= step) {
            delta = diff;
        } else {
            delta = step;
        }
    } else if (360.0 - diff <= step) {
        delta = -(360.0 - diff);
    } else {
        delta = -step;
    }
    delta += current;
    if (delta >= 360.0) {
        delta -= 360.0;
    } else if (delta < 0.0) {
        delta += 360.0;
    }
    return delta;
}

f32 func_8010B308_baby_bowser_bonkers(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 func_8010B320_baby_bowser_bonkers(f32 t, f32 start, f32 end) {
    return func_8010B148_baby_bowser_bonkers(end, start, fabsf(func_8010B044_baby_bowser_bonkers(end, start) * t));
}

void func_8010B380_baby_bowser_bonkers(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *arg0) {
    BabyBowserBonkersBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return (BabyBowserBonkersPlayer *)packed.word;
}
