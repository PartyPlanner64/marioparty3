#include "motor_rooter.h"
#include "macros.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hu3d.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mallocblock.h"
#include "humath.h"
#include "include_asm.h"
#include "game/input.h"
#include "variables.h"
#include "game/printfunc.h"
#include "game/hmfcoll.h"
#include "game/esprite.h"
#include "game/hmfspr.h"
#include "game/hmfmath.h"
#include "game/camsetup.h"

#define PLAYERS_TOTAL 2

// camsetup

// hmfspr

// hmfcoll

// unknown
extern s32 D_800A178C_main[][6];

enum {
    FGRP_CAMERA
};

typedef struct {
    s32 fileIds[2][2];
} CourseModels;

typedef struct {
    s32 fileIds[8];
} CharacterSprites;

typedef struct {
    s32 fileIds[7];
} ObstacleSprites;

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 obstacleSprites[21];
    /* 0x2E */ s16 obstacleSlots[3];
    /* 0x34 */ s16 obstacleSafeDirections[3][3];
    /* 0x46 */ s16 obstacleFrames[3];
    /* 0x4C */ s16 obstaclePoints[10];
    /* 0x60 */ s16 obstacleDirections[10];
    /* 0x74 */ s16 obstacleTypes[10];
    /* 0x88 */ s16 nextObstacleSlot;
    /* 0x8A */ s16 unk8A;
    /* 0x8C */ omObjData *unk8C;
    /* 0x90 */ s16 itemSlots[15];
    /* 0xAE */ s16 nextItemSlot;
    /* 0xB0 */ s16 itemSprites[5];
    /* 0xBA */ s16 itemFrames[5];
    /* 0xC4 */ s8 itemDelays[4];
    /* 0xC8 */ s8 itemStates[4];
    /* 0xCC */ char unkCC[8];
    /* 0xD4 */ s16 itemTimer;
    /* 0xD6 */ char unkD6[0x1E];
} PlayerView; // Size 0xF4

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
    /* 0x0C */ f32 pitch;
    /* 0x10 */ f32 yaw;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 segLen;
    /* 0x1C */ f32 invSegLen;
    /* 0x20 */ f32 cumDist;
} PathPoint; // Size 0x24

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 pitch;
    /* 0x14 */ f32 yaw;
    /* 0x18 */ f32 roll;
} PathPosition; // Size 0x1C

typedef union {
    struct {
        /* 0x00 */ s8 viewCounters[6];
        /* 0x06 */ s8 itemViewCount;
        /* 0x07 */ char unk07[0x19];
    } initialization;
    struct {
        /* 0x00 */ s8 playerCounters[PLAYERS_TOTAL * 4];
        /* 0x08 */ char unk08[8];
        /* 0x10 */ s16 impactFrameCounters[PLAYERS_TOTAL];
        /* 0x14 */ char unk14[0xC];
    } gameplay;
} MinigameCounters; // Size 0x20

typedef struct {
    /* 0x00 */ MinigameCounters counters;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ char unk24[0xC];
} MinigameRuntime; // Size 0x30

typedef struct {
    /* 0x000 */ PlayerView *views;
    /* 0x004 */ f32 totalDistance;
    /* 0x008 */ f32 finishDistance;
    /* 0x00C */ s16 pathPointCount;
    /* 0x00E */ s16 unk0E;
    /* 0x010 */ f32 timer;
    /* 0x014 */ s16 itemPoints[100];
    /* 0x0DC */ s16 itemDirections[100];
    /* 0x1A4 */ MinigameRuntime runtime;
} MinigameData; // Size 0x1D4

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 controllerPort;
    /* 0x06 */ s16 isCpu;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s8 unk14;
    /* 0x15 */ char unk15;
    /* 0x16 */ s16 direction;
    /* 0x18 */ f32 turnAngle;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 meterSprites[5];
    /* 0x28 */ s16 unk28[5];
    /* 0x32 */ s8 animChange;
    /* 0x34 */ s16 nextAnim;
    /* 0x36 */ char unk36[0x12];
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 progressSprite;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ char unk4E[0xA];
    /* 0x58 */ Vec cameraStart;
    /* 0x64 */ f32 rotationStart;
    /* 0x68 */ Vec motion;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ u16 unk78;
    /* 0x7A */ char unk7A[2];
    /* 0x7C */ Vec motionCopy;
    /* 0x88 */ s16 obstacleSoundStarted;
    /* 0x8A */ s16 obstacleSound;
} D_801137C8_motor_rooter_Struct; // Size 0x8C

void m254_InitEnvironment(void);
void m254_CreateMinigame(void);
void m254_CheckExitRequest(omObjData *object);
void m254_WaitExitWipeOut(omObjData *object);
void m254_ExitOverlay(omObjData *object);
void func_80106044_motor_rooter(omObjData *object);
void func_80106298_motor_rooter(omObjData *object);
void func_801062BC_motor_rooter(omObjData *object);
void func_801064EC_motor_rooter(omObjData *object);
void func_80106508_motor_rooter(omObjData *object);
void func_80106998_motor_rooter(omObjData *object);
void func_80106B7C_motor_rooter(omObjData *object);
void func_8010A174_motor_rooter(FuncContext *ctx);
void func_80106BAC_motor_rooter(omObjData *object);
void func_80107210_motor_rooter(omObjData *object);
void func_801076AC_motor_rooter(omObjData *object);
void func_801079E8_motor_rooter(omObjData *object);
void func_80107D50_motor_rooter(omObjData *object);
void m254_InitCamera(FuncContext *ctx);
void func_801082E0_motor_rooter(FuncContext *ctx);
void func_80108514_motor_rooter(FuncContext *ctx);
void func_80108E6C_motor_rooter(FuncContext *ctx);
void func_80108BF0_motor_rooter(FuncContext *ctx);
void func_801087C0_motor_rooter(FuncContext *ctx);
void func_801089B8_motor_rooter(FuncContext *ctx);
void func_8010A440_motor_rooter(FuncContext *ctx);
void func_8010BDF0_motor_rooter(FuncContext *ctx);
void func_8010AF0C_motor_rooter(FuncContext *ctx);
void func_8010B394_motor_rooter(FuncContext *ctx);
void func_8010B970_motor_rooter(FuncContext *ctx);
void func_80109134_motor_rooter(FuncContext *ctx);
void func_80108FDC_motor_rooter(FuncContext *ctx);
void func_801107FC_motor_rooter(u16 modelId, HuSprAnimData *sprite, u16 frame);
void func_801108CC_motor_rooter(u16 modelId, HuSprAnimData *sprite, u16 frame, RGBA *color);
void func_8010CB2C_motor_rooter(omObjData *object, s16 item, s16 modelIndex);
void func_8010CD84_motor_rooter(Vec *, s16);
s16 func_8010D03C_motor_rooter(f32);
PathPosition func_8010D0AC_motor_rooter(s16, f32);
void func_8010D2E4_motor_rooter(s32);
void func_8010DC3C_motor_rooter(s16 point, s16 direction);
void func_801070CC_motor_rooter(omObjData *object);
void func_8010ABC4_motor_rooter(FuncContext *ctx);
void func_8010BCD0_motor_rooter(FuncContext *ctx);
void func_8010BB78_motor_rooter(FuncContext *ctx);
void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *player, s16 anim, s8 change);
void func_8010C084_motor_rooter(FuncContext *ctx);
void func_8010C44C_motor_rooter(FuncContext *ctx);
void func_8010C824_motor_rooter(FuncContext *ctx);
void func_80109C94_motor_rooter(PlayerView *view, s16 slot);
void func_80109EFC_motor_rooter(FuncContext *ctx);
void func_8010961C_motor_rooter(FuncContext *ctx);
void func_8010972C_motor_rooter(FuncContext *ctx);
void func_801091A0_motor_rooter(FuncContext *ctx);
void func_80106968_motor_rooter(omObjData *object);

// DATA
Vec D_80111550_motor_rooter[321] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, -100.0f },
    { 0.0f, 0.0f, -200.0f },
    { 0.0f, 0.0f, -300.0f },
    { 0.0f, 0.0f, -400.0f },
    { 0.0f, 0.0f, -500.0f },
    { 0.0f, 0.0f, -600.0f },
    { 0.0f, 0.0f, -700.0f },
    { 0.0f, 0.0f, -800.0f },
    { 0.0f, 0.0f, -900.0f },
    { 0.0f, 0.0f, -1000.0f },
    { 0.0f, 0.0f, -1100.0f },
    { 0.0f, 0.0f, -1200.0f },
    { 0.0f, 0.0f, -1300.0f },
    { 0.0f, 0.0f, -1400.0f },
    { 0.0f, 0.0f, -1500.0f },
    { 0.0f, 0.0f, -1600.0f },
    { 0.0f, 0.0f, -1700.0f },
    { 0.0f, 0.0f, -1800.0f },
    { 0.0f, 0.0f, -1900.0f },
    { 0.0f, 0.0f, -2000.0f },
    { 4.625f, 0.0f, -2117.65f },
    { 18.47f, 0.0f, -2234.65f },
    { 41.445f, 0.0f, -2350.15f },
    { 73.415f, 0.0f, -2463.5f },
    { 114.18f, 0.0f, -2574.0f },
    { 163.49f, 0.0f, -2680.95f },
    { 221.04f, 0.0f, -2783.75f },
    { 286.475f, 0.0f, -2881.65f },
    { 359.39f, 0.0f, -2974.15f },
    { 439.34f, 0.0f, -3060.65f },
    { 525.83f, 0.0f, -3140.6f },
    { 618.32f, 0.0f, -3213.5f },
    { 716.25f, 0.0f, -3278.95f },
    { 819.015f, 0.0f, -3336.5f },
    { 925.975f, 0.0f, -3385.8f },
    { 1036.475f, 0.0f, -3426.55f },
    { 1149.83f, 0.0f, -3458.55f },
    { 1265.35f, 0.0f, -3481.5f },
    { 1382.31f, 0.0f, -3495.35f },
    { 1500.0f, 0.0f, -3500.0f },
    { 1617.69f, 0.0f, -3504.6f },
    { 1734.65f, 0.0f, -3518.45f },
    { 1850.17f, 0.0f, -3541.4f },
    { 1963.525f, 0.0f, -3573.4f },
    { 2074.025f, 0.0f, -3614.15f },
    { 2180.985f, 0.0f, -3663.45f },
    { 2283.75f, 0.0f, -3721.0f },
    { 2381.68f, 0.0f, -3786.45f },
    { 2474.17f, 0.0f, -3859.35f },
    { 2560.66f, 0.0f, -3939.3f },
    { 2640.61f, 0.0f, -4025.8f },
    { 2713.525f, 0.0f, -4118.3f },
    { 2778.96f, 0.0f, -4216.25f },
    { 2836.51f, 0.0f, -4319.0f },
    { 2885.82f, 0.0f, -4425.95f },
    { 2926.585f, 0.0f, -4536.45f },
    { 2958.555f, 0.0f, -4649.8f },
    { 2981.535f, 0.0f, -4765.35f },
    { 2995.375f, 0.0f, -4882.3f },
    { 3000.0f, 0.0f, -5000.0f },
    { 3000.0f, 0.0f, -5100.0f },
    { 3000.0f, 0.0f, -5200.0f },
    { 3000.0f, 0.0f, -5300.0f },
    { 3000.0f, 0.0f, -5400.0f },
    { 3000.0f, 0.0f, -5500.0f },
    { 3000.0f, 0.0f, -5600.0f },
    { 3000.0f, 0.0f, -5700.0f },
    { 3000.0f, 0.0f, -5800.0f },
    { 3000.0f, 0.0f, -5900.0f },
    { 3000.0f, 0.0f, -6000.0f },
    { 3000.0f, 0.0f, -6100.0f },
    { 3000.0f, 0.0f, -6200.0f },
    { 3000.0f, 0.0f, -6300.0f },
    { 3000.0f, 0.0f, -6400.0f },
    { 3000.0f, 0.0f, -6500.0f },
    { 3000.0f, 0.0f, -6600.0f },
    { 3000.0f, 0.0f, -6700.0f },
    { 3000.0f, 0.0f, -6800.0f },
    { 3000.0f, 0.0f, -6900.0f },
    { 3000.0f, 0.0f, -7000.0f },
    { 2995.375f, 0.0f, -7117.65f },
    { 2981.535f, 0.0f, -7234.65f },
    { 2958.555f, 0.0f, -7350.15f },
    { 2926.585f, 0.0f, -7463.5f },
    { 2885.82f, 0.0f, -7574.0f },
    { 2836.645f, 0.0f, -7680.9f },
    { 2778.96f, 0.0f, -7783.75f },
    { 2713.525f, 0.0f, -7881.65f },
    { 2640.61f, 0.0f, -7974.15f },
    { 2560.66f, 0.0f, -8060.65f },
    { 2474.17f, 0.0f, -8140.6f },
    { 2381.68f, 0.0f, -8213.5f },
    { 2283.75f, 0.0f, -8278.95f },
    { 2180.985f, 0.0f, -8336.5f },
    { 2074.025f, 0.0f, -8385.8f },
    { 1963.525f, 0.0f, -8426.55f },
    { 1850.17f, 0.0f, -8458.55f },
    { 1734.65f, 0.0f, -8481.5f },
    { 1617.69f, 0.0f, -8495.35f },
    { 1500.0f, 0.0f, -8500.0f },
    { 1382.31f, 0.0f, -8504.6f },
    { 1265.35f, 0.0f, -8518.45f },
    { 1149.83f, 0.0f, -8541.4f },
    { 1036.475f, 0.0f, -8573.4f },
    { 925.975f, 0.0f, -8614.15f },
    { 819.015f, 0.0f, -8663.45f },
    { 716.25f, 0.0f, -8721.0f },
    { 618.32f, 0.0f, -8786.45f },
    { 525.83f, 0.0f, -8859.35f },
    { 439.34f, 0.0f, -8939.3f },
    { 359.39f, 0.0f, -9025.8f },
    { 286.475f, 0.0f, -9118.3f },
    { 221.04f, 0.0f, -9216.25f },
    { 163.49f, 0.0f, -9319.0f },
    { 114.18f, 0.0f, -9425.95f },
    { 73.415f, 0.0f, -9536.45f },
    { 41.445f, 0.0f, -9649.8f },
    { 18.465f, 0.0f, -9765.35f },
    { 4.625f, 0.0f, -9882.3f },
    { 0.0f, 0.0f, -10000.0f },
    { 0.0f, 0.0f, -10100.0f },
    { 0.0f, 0.0f, -10200.0f },
    { 0.0f, 0.0f, -10300.0f },
    { 0.0f, 0.0f, -10400.0f },
    { 0.0f, 0.0f, -10500.0f },
    { 0.0f, 0.0f, -10600.0f },
    { 0.0f, 0.0f, -10700.0f },
    { 0.0f, 0.0f, -10800.0f },
    { 0.0f, 0.0f, -10900.0f },
    { 0.0f, 0.0f, -11000.0f },
    { 0.0f, 0.0f, -11100.0f },
    { 0.0f, 0.0f, -11200.0f },
    { 0.0f, 0.0f, -11300.0f },
    { 0.0f, 0.0f, -11400.0f },
    { 0.0f, 0.0f, -11500.0f },
    { 0.0f, 0.0f, -11600.0f },
    { 0.0f, 0.0f, -11700.0f },
    { 0.0f, 0.0f, -11800.0f },
    { 0.0f, 0.0f, -11900.0f },
    { 0.0f, 0.0f, -12000.0f },
    { -4.625f, 0.0f, -12117.65f },
    { -18.47f, 0.0f, -12234.65f },
    { -41.445f, 0.0f, -12350.15f },
    { -73.415f, 0.0f, -12463.5f },
    { -114.18f, 0.0f, -12574.0f },
    { -163.49f, 0.0f, -12680.95f },
    { -221.04f, 0.0f, -12783.75f },
    { -286.475f, 0.0f, -12881.65f },
    { -359.39f, 0.0f, -12974.15f },
    { -439.34f, 0.0f, -13060.65f },
    { -525.83f, 0.0f, -13140.6f },
    { -618.32f, 0.0f, -13213.5f },
    { -716.25f, 0.0f, -13278.95f },
    { -819.015f, 0.0f, -13336.5f },
    { -925.975f, 0.0f, -13385.8f },
    { -1036.475f, 0.0f, -13426.55f },
    { -1149.83f, 0.0f, -13458.55f },
    { -1265.35f, 0.0f, -13481.5f },
    { -1382.31f, 0.0f, -13495.35f },
    { -1500.0f, 0.0f, -13500.0f },
    { -1617.69f, 0.0f, -13504.6f },
    { -1734.65f, 0.0f, -13518.45f },
    { -1850.17f, 0.0f, -13541.4f },
    { -1963.525f, 0.0f, -13573.4f },
    { -2074.025f, 0.0f, -13614.15f },
    { -2180.985f, 0.0f, -13663.45f },
    { -2283.75f, 0.0f, -13721.0f },
    { -2381.68f, 0.0f, -13786.45f },
    { -2474.17f, 0.0f, -13859.35f },
    { -2560.66f, 0.0f, -13939.3f },
    { -2640.61f, 0.0f, -14025.8f },
    { -2713.525f, 0.0f, -14118.3f },
    { -2778.96f, 0.0f, -14216.25f },
    { -2836.51f, 0.0f, -14319.0f },
    { -2885.82f, 0.0f, -14425.95f },
    { -2926.585f, 0.0f, -14536.45f },
    { -2958.555f, 0.0f, -14649.8f },
    { -2981.535f, 0.0f, -14765.35f },
    { -2995.375f, 0.0f, -14882.3f },
    { -3000.0f, 0.0f, -15000.0f },
    { -2995.375f, 0.0f, -15117.65f },
    { -2981.535f, 0.0f, -15234.65f },
    { -2958.555f, 0.0f, -15350.15f },
    { -2926.585f, 0.0f, -15463.5f },
    { -2885.82f, 0.0f, -15574.0f },
    { -2836.51f, 0.0f, -15680.95f },
    { -2778.96f, 0.0f, -15783.75f },
    { -2713.525f, 0.0f, -15881.65f },
    { -2640.61f, 0.0f, -15974.15f },
    { -2560.66f, 0.0f, -16060.65f },
    { -2474.17f, 0.0f, -16140.6f },
    { -2381.68f, 0.0f, -16213.5f },
    { -2283.75f, 0.0f, -16278.95f },
    { -2180.985f, 0.0f, -16336.5f },
    { -2074.025f, 0.0f, -16385.8f },
    { -1963.525f, 0.0f, -16426.55f },
    { -1850.17f, 0.0f, -16458.55f },
    { -1734.65f, 0.0f, -16481.5f },
    { -1617.69f, 0.0f, -16495.35f },
    { -1500.0f, 0.0f, -16500.0f },
    { -1382.31f, 0.0f, -16504.6f },
    { -1265.35f, 0.0f, -16518.45f },
    { -1149.83f, 0.0f, -16541.4f },
    { -1036.475f, 0.0f, -16573.4f },
    { -925.975f, 0.0f, -16614.15f },
    { -819.015f, 0.0f, -16663.45f },
    { -716.25f, 0.0f, -16721.0f },
    { -618.32f, 0.0f, -16786.45f },
    { -525.83f, 0.0f, -16859.35f },
    { -439.34f, 0.0f, -16939.3f },
    { -359.39f, 0.0f, -17025.8f },
    { -286.475f, 0.0f, -17118.3f },
    { -221.04f, 0.0f, -17216.25f },
    { -163.49f, 0.0f, -17319.0f },
    { -114.18f, 0.0f, -17425.95f },
    { -73.415f, 0.0f, -17536.45f },
    { -41.445f, 0.0f, -17649.8f },
    { -18.47f, 0.0f, -17765.35f },
    { -4.625f, 0.0f, -17882.3f },
    { 0.0f, 0.0f, -18000.0f },
    { 4.625f, 0.0f, -18117.65f },
    { 18.47f, 0.0f, -18234.65f },
    { 41.445f, 0.0f, -18350.15f },
    { 73.415f, 0.0f, -18463.5f },
    { 114.18f, 0.0f, -18574.0f },
    { 163.49f, 0.0f, -18680.95f },
    { 221.04f, 0.0f, -18783.75f },
    { 286.475f, 0.0f, -18881.65f },
    { 359.39f, 0.0f, -18974.15f },
    { 439.34f, 0.0f, -19060.65f },
    { 525.83f, 0.0f, -19140.6f },
    { 618.32f, 0.0f, -19213.5f },
    { 716.25f, 0.0f, -19278.95f },
    { 819.015f, 0.0f, -19336.5f },
    { 925.975f, 0.0f, -19385.8f },
    { 1036.475f, 0.0f, -19426.55f },
    { 1149.83f, 0.0f, -19458.55f },
    { 1265.35f, 0.0f, -19481.5f },
    { 1382.31f, 0.0f, -19495.35f },
    { 1500.0f, 0.0f, -19500.0f },
    { 1617.69f, 0.0f, -19495.35f },
    { 1734.65f, 0.0f, -19481.5f },
    { 1850.17f, 0.0f, -19458.55f },
    { 1963.525f, 0.0f, -19426.55f },
    { 2074.025f, 0.0f, -19385.8f },
    { 2180.985f, 0.0f, -19336.5f },
    { 2283.75f, 0.0f, -19278.95f },
    { 2381.68f, 0.0f, -19213.5f },
    { 2474.17f, 0.0f, -19140.6f },
    { 2560.66f, 0.0f, -19060.65f },
    { 2640.61f, 0.0f, -18974.15f },
    { 2713.525f, 0.0f, -18881.65f },
    { 2778.96f, 0.0f, -18783.75f },
    { 2836.51f, 0.0f, -18680.95f },
    { 2885.82f, 0.0f, -18574.0f },
    { 2926.585f, 0.0f, -18463.5f },
    { 2958.555f, 0.0f, -18350.15f },
    { 2981.535f, 0.0f, -18234.65f },
    { 2995.375f, 0.0f, -18117.65f },
    { 3000.0f, 0.0f, -18000.0f },
    { 3000.0f, 0.0f, -17900.0f },
    { 3000.0f, 0.0f, -17800.0f },
    { 3000.0f, 0.0f, -17700.0f },
    { 3000.0f, 0.0f, -17600.0f },
    { 3000.0f, 0.0f, -17500.0f },
    { 3000.0f, 0.0f, -17400.0f },
    { 3000.0f, 0.0f, -17300.0f },
    { 3000.0f, 0.0f, -17200.0f },
    { 3000.0f, 0.0f, -17100.0f },
    { 3000.0f, 0.0f, -17000.0f },
    { 3000.0f, 0.0f, -16900.0f },
    { 3000.0f, 0.0f, -16800.0f },
    { 3000.0f, 0.0f, -16700.0f },
    { 3000.0f, 0.0f, -16600.0f },
    { 3000.0f, 0.0f, -16500.0f },
    { 3000.0f, 0.0f, -16400.0f },
    { 3000.0f, 0.0f, -16300.0f },
    { 3000.0f, 0.0f, -16200.0f },
    { 3000.0f, 0.0f, -16100.0f },
    { 3000.0f, 0.0f, -16000.0f },
    { 3000.0f, 0.0f, -15900.0f },
    { 3000.0f, 0.0f, -15800.0f },
    { 3000.0f, 0.0f, -15700.0f },
    { 3000.0f, 0.0f, -15600.0f },
    { 3000.0f, 0.0f, -15500.0f },
    { 3000.0f, 0.0f, -15400.0f },
    { 3000.0f, 0.0f, -15300.0f },
    { 3000.0f, 0.0f, -15200.0f },
    { 3000.0f, 0.0f, -15100.0f },
    { 3000.0f, 0.0f, -15000.0f },
    { 3000.0f, 0.0f, -14900.0f },
    { 3000.0f, 0.0f, -14800.0f },
    { 3000.0f, 0.0f, -14700.0f },
    { 3000.0f, 0.0f, -14600.0f },
    { 3000.0f, 0.0f, -14500.0f },
    { 3000.0f, 0.0f, -14400.0f },
    { 3000.0f, 0.0f, -14300.0f },
    { 3000.0f, 0.0f, -14200.0f },
    { 3000.0f, 0.0f, -14100.0f },
    { 3000.0f, 0.0f, -14000.0f },
    { 3000.0f, 0.0f, -13900.0f },
    { 3000.0f, 0.0f, -13800.0f },
    { 3000.0f, 0.0f, -13700.0f },
    { 3000.0f, 0.0f, -13600.0f },
    { 3000.0f, 0.0f, -13500.0f },
    { 3000.0f, 0.0f, -13400.0f },
    { 3000.0f, 0.0f, -13300.0f },
    { 3000.0f, 0.0f, -13200.0f },
    { 3000.0f, 0.0f, -13100.0f },
    { 3000.0f, 0.0f, -13000.0f },
    { 3000.0f, 0.0f, -12900.0f },
    { 3000.0f, 0.0f, -12800.0f },
    { 3000.0f, 0.0f, -12700.0f },
    { 3000.0f, 0.0f, -12600.0f },
    { 3000.0f, 0.0f, -12500.0f },
    { 3000.0f, 0.0f, -12400.0f },
    { 3000.0f, 0.0f, -12300.0f },
    { 3000.0f, 0.0f, -12200.0f },
    { 3000.0f, 0.0f, -12100.0f },
    { 3000.0f, 0.0f, -12000.0f }
};
Vec D_8011245C_motor_rooter[341] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, -100.0f },
    { 0.0f, 0.0f, -200.0f },
    { 0.0f, 0.0f, -300.0f },
    { 0.0f, 0.0f, -400.0f },
    { 0.0f, 0.0f, -500.0f },
    { 0.0f, 0.0f, -600.0f },
    { 0.0f, 0.0f, -700.0f },
    { 0.0f, 0.0f, -800.0f },
    { 0.0f, 0.0f, -900.0f },
    { 0.0f, 0.0f, -1000.0f },
    { 0.0f, 0.0f, -1100.0f },
    { 0.0f, 0.0f, -1200.0f },
    { 0.0f, 0.0f, -1300.0f },
    { 0.0f, 0.0f, -1400.0f },
    { 0.0f, 0.0f, -1500.0f },
    { 0.0f, 0.0f, -1600.0f },
    { 0.0f, 0.0f, -1700.0f },
    { 0.0f, 0.0f, -1800.0f },
    { 0.0f, 0.0f, -1900.0f },
    { 0.0f, 0.0f, -2000.0f },
    { 0.0f, 4.625f, -2117.65f },
    { 0.0f, 18.465f, -2234.65f },
    { 0.0f, 41.445f, -2350.15f },
    { 0.0f, 73.415f, -2463.5f },
    { 0.0f, 114.18f, -2574.0f },
    { 0.0f, 163.49f, -2680.95f },
    { 0.0f, 221.04f, -2783.75f },
    { 0.0f, 286.475f, -2881.65f },
    { 0.0f, 359.39f, -2974.15f },
    { 0.0f, 439.34f, -3060.65f },
    { 0.0f, 525.825f, -3140.6f },
    { 0.0f, 618.32f, -3213.5f },
    { 0.0f, 716.25f, -3278.95f },
    { 0.0f, 819.015f, -3336.5f },
    { 0.0f, 925.975f, -3385.8f },
    { 0.0f, 1036.475f, -3426.55f },
    { 0.0f, 1149.83f, -3458.55f },
    { 0.0f, 1265.345f, -3481.5f },
    { 0.0f, 1382.31f, -3495.35f },
    { 0.0f, 1500.0f, -3500.0f },
    { 0.0f, 1617.69f, -3504.6f },
    { 0.0f, 1734.65f, -3518.45f },
    { 0.0f, 1850.165f, -3541.4f },
    { 0.0f, 1963.525f, -3573.4f },
    { 0.0f, 2074.025f, -3614.15f },
    { 0.0f, 2180.985f, -3663.45f },
    { 0.0f, 2283.745f, -3721.0f },
    { 0.0f, 2381.675f, -3786.45f },
    { 0.0f, 2474.17f, -3859.35f },
    { 0.0f, 2560.66f, -3939.3f },
    { 0.0f, 2640.61f, -4025.8f },
    { 0.0f, 2713.525f, -4118.3f },
    { 0.0f, 2778.96f, -4216.25f },
    { 0.0f, 2836.51f, -4319.0f },
    { 0.0f, 2885.82f, -4425.95f },
    { 0.0f, 2926.585f, -4536.45f },
    { 0.0f, 2958.555f, -4649.8f },
    { 0.0f, 2981.53f, -4765.35f },
    { 0.0f, 2995.375f, -4882.3f },
    { 0.0f, 3000.0f, -5000.0f },
    { 0.0f, 2995.375f, -5117.65f },
    { 0.0f, 2981.53f, -5234.65f },
    { 0.0f, 2958.555f, -5350.15f },
    { 0.0f, 2926.585f, -5463.5f },
    { 0.0f, 2885.82f, -5574.0f },
    { 0.0f, 2836.51f, -5680.95f },
    { 0.0f, 2778.96f, -5783.75f },
    { 0.0f, 2713.525f, -5881.65f },
    { 0.0f, 2640.61f, -5974.15f },
    { 0.0f, 2560.66f, -6060.65f },
    { 0.0f, 2474.17f, -6140.6f },
    { 0.0f, 2381.675f, -6213.5f },
    { 0.0f, 2283.745f, -6278.95f },
    { 0.0f, 2180.985f, -6336.5f },
    { 0.0f, 2074.025f, -6385.8f },
    { 0.0f, 1963.525f, -6426.55f },
    { 0.0f, 1850.165f, -6458.55f },
    { 0.0f, 1734.65f, -6481.5f },
    { 0.0f, 1617.685f, -6495.35f },
    { 0.0f, 1500.0f, -6500.0f },
    { 0.0f, 1382.31f, -6504.6f },
    { 0.0f, 1265.345f, -6518.45f },
    { 0.0f, 1149.83f, -6541.4f },
    { 0.0f, 1036.475f, -6573.4f },
    { 0.0f, 925.975f, -6614.15f },
    { 0.0f, 819.015f, -6663.45f },
    { 0.0f, 716.25f, -6721.0f },
    { 0.0f, 618.32f, -6786.45f },
    { 0.0f, 525.825f, -6859.35f },
    { 0.0f, 439.34f, -6939.3f },
    { 0.0f, 359.39f, -7025.8f },
    { 0.0f, 286.475f, -7118.3f },
    { 0.0f, 221.04f, -7216.25f },
    { 0.0f, 163.49f, -7319.0f },
    { 0.0f, 114.18f, -7425.95f },
    { 0.0f, 73.415f, -7536.45f },
    { 0.0f, 41.445f, -7649.8f },
    { 0.0f, 18.465f, -7765.35f },
    { 0.0f, 4.62f, -7882.3f },
    { 0.0f, 0.0f, -8000.0f },
    { 0.0f, 0.0f, -8100.0f },
    { 0.0f, 0.0f, -8200.0f },
    { 0.0f, 0.0f, -8300.0f },
    { 0.0f, 0.0f, -8400.0f },
    { 0.0f, 0.0f, -8500.0f },
    { 0.0f, 0.0f, -8600.0f },
    { 0.0f, 0.0f, -8700.0f },
    { 0.0f, 0.0f, -8800.0f },
    { 0.0f, 0.0f, -8900.0f },
    { 0.0f, 0.0f, -9000.0f },
    { 0.0f, 0.0f, -9100.0f },
    { 0.0f, 0.0f, -9200.0f },
    { 0.0f, 0.0f, -9300.0f },
    { 0.0f, 0.0f, -9400.0f },
    { 0.0f, 0.0f, -9500.0f },
    { 0.0f, 0.0f, -9600.0f },
    { 0.0f, 0.0f, -9700.0f },
    { 0.0f, 0.0f, -9800.0f },
    { 0.0f, 0.0f, -9900.0f },
    { 0.0f, 0.0f, -10000.0f },
    { 4.625f, 0.0f, -10117.65f },
    { 18.47f, 0.0f, -10234.65f },
    { 41.445f, 0.0f, -10350.15f },
    { 73.415f, 0.0f, -10463.5f },
    { 114.18f, 0.0f, -10574.0f },
    { 163.49f, 0.0f, -10680.95f },
    { 221.04f, 0.0f, -10783.75f },
    { 286.475f, 0.0f, -10881.65f },
    { 359.39f, 0.0f, -10974.15f },
    { 439.34f, 0.0f, -11060.65f },
    { 525.83f, 0.0f, -11140.6f },
    { 618.325f, 0.0f, -11213.5f },
    { 716.255f, 0.0f, -11278.95f },
    { 819.015f, 0.0f, -11336.5f },
    { 925.975f, 0.0f, -11385.8f },
    { 1036.475f, 0.0f, -11426.55f },
    { 1149.835f, 0.0f, -11458.55f },
    { 1265.35f, 0.0f, -11481.5f },
    { 1382.31f, 0.0f, -11495.35f },
    { 1500.0f, 0.0f, -11500.0f },
    { 1617.69f, 0.0f, -11495.35f },
    { 1734.65f, 0.0f, -11481.5f },
    { 1850.17f, 0.0f, -11458.55f },
    { 1963.525f, 0.0f, -11426.55f },
    { 2074.025f, 0.0f, -11385.8f },
    { 2180.985f, 0.0f, -11336.5f },
    { 2283.75f, 0.0f, -11278.95f },
    { 2381.68f, 0.0f, -11213.5f },
    { 2474.175f, 0.0f, -11140.6f },
    { 2560.66f, 0.0f, -11060.65f },
    { 2640.61f, 0.0f, -10974.15f },
    { 2713.525f, 0.0f, -10881.65f },
    { 2778.96f, 0.0f, -10783.75f },
    { 2836.51f, 0.0f, -10680.95f },
    { 2885.82f, 0.0f, -10574.0f },
    { 2926.585f, 0.0f, -10463.5f },
    { 2958.555f, 0.0f, -10350.15f },
    { 2981.535f, 0.0f, -10234.65f },
    { 2995.375f, 0.0f, -10117.65f },
    { 3000.0f, 0.0f, -10000.0f },
    { 3004.625f, 0.0f, -9882.3f },
    { 3018.47f, 0.0f, -9765.35f },
    { 3041.445f, 0.0f, -9649.8f },
    { 3073.415f, 0.0f, -9536.45f },
    { 3114.18f, 0.0f, -9425.95f },
    { 3163.49f, 0.0f, -9319.0f },
    { 3221.04f, 0.0f, -9216.25f },
    { 3286.475f, 0.0f, -9118.3f },
    { 3359.39f, 0.0f, -9025.8f },
    { 3439.34f, 0.0f, -8939.3f },
    { 3525.83f, 0.0f, -8859.35f },
    { 3618.325f, 0.0f, -8786.45f },
    { 3716.255f, 0.0f, -8721.0f },
    { 3819.015f, 0.0f, -8663.45f },
    { 3925.975f, 0.0f, -8614.15f },
    { 4036.475f, 0.0f, -8573.4f },
    { 4149.83f, 0.0f, -8541.4f },
    { 4265.35f, 0.0f, -8518.45f },
    { 4382.31f, 0.0f, -8504.6f },
    { 4500.0f, 0.0f, -8500.0f },
    { 4617.69f, 0.0f, -8504.6f },
    { 4734.65f, 0.0f, -8518.45f },
    { 4850.17f, 0.0f, -8541.4f },
    { 4963.525f, 0.0f, -8573.4f },
    { 5074.025f, 0.0f, -8614.15f },
    { 5180.985f, 0.0f, -8663.45f },
    { 5283.75f, 0.0f, -8721.0f },
    { 5381.68f, 0.0f, -8786.45f },
    { 5474.17f, 0.0f, -8859.35f },
    { 5560.66f, 0.0f, -8939.3f },
    { 5640.61f, 0.0f, -9025.8f },
    { 5713.525f, 0.0f, -9118.3f },
    { 5778.96f, 0.0f, -9216.25f },
    { 5836.51f, 0.0f, -9319.0f },
    { 5885.82f, 0.0f, -9425.95f },
    { 5926.585f, 0.0f, -9536.45f },
    { 5958.555f, 0.0f, -9649.8f },
    { 5981.535f, 0.0f, -9765.35f },
    { 5995.375f, 0.0f, -9882.3f },
    { 6000.0f, 0.0f, -10000.0f },
    { 6000.0f, 0.0f, -10100.0f },
    { 6000.0f, 0.0f, -10200.0f },
    { 6000.0f, 0.0f, -10300.0f },
    { 6000.0f, 0.0f, -10400.0f },
    { 6000.0f, 0.0f, -10500.0f },
    { 6000.0f, 0.0f, -10600.0f },
    { 6000.0f, 0.0f, -10700.0f },
    { 6000.0f, 0.0f, -10800.0f },
    { 6000.0f, 0.0f, -10900.0f },
    { 6000.0f, 0.0f, -11000.0f },
    { 6000.0f, 0.0f, -11100.0f },
    { 6000.0f, 0.0f, -11200.0f },
    { 6000.0f, 0.0f, -11300.0f },
    { 6000.0f, 0.0f, -11400.0f },
    { 6000.0f, 0.0f, -11500.0f },
    { 6000.0f, 0.0f, -11600.0f },
    { 6000.0f, 0.0f, -11700.0f },
    { 6000.0f, 0.0f, -11800.0f },
    { 6000.0f, 0.0f, -11900.0f },
    { 6000.0f, 0.0f, -12000.0f },
    { 6000.0f, 4.62f, -12117.65f },
    { 6000.0f, 18.465f, -12234.65f },
    { 6000.0f, 41.445f, -12350.15f },
    { 6000.0f, 73.415f, -12463.5f },
    { 6000.0f, 114.18f, -12574.0f },
    { 6000.0f, 163.49f, -12680.95f },
    { 6000.0f, 221.04f, -12783.75f },
    { 6000.0f, 286.47f, -12881.65f },
    { 6000.0f, 359.39f, -12974.15f },
    { 6000.0f, 439.34f, -13060.65f },
    { 6000.0f, 525.825f, -13140.6f },
    { 6000.0f, 618.32f, -13213.5f },
    { 6000.0f, 716.25f, -13278.95f },
    { 6000.0f, 819.01f, -13336.5f },
    { 6000.0f, 925.975f, -13385.8f },
    { 6000.0f, 1036.47f, -13426.55f },
    { 6000.0f, 1149.83f, -13458.55f },
    { 6000.0f, 1265.345f, -13481.5f },
    { 6000.0f, 1382.31f, -13495.35f },
    { 6000.0f, 1500.0f, -13500.0f },
    { 6000.0f, 1617.685f, -13504.6f },
    { 6000.0f, 1734.65f, -13518.45f },
    { 6000.0f, 1850.165f, -13541.4f },
    { 6000.0f, 1963.525f, -13573.4f },
    { 6000.0f, 2074.025f, -13614.15f },
    { 6000.0f, 2180.985f, -13663.45f },
    { 6000.0f, 2283.745f, -13721.0f },
    { 6000.0f, 2381.675f, -13786.45f },
    { 6000.0f, 2474.17f, -13859.35f },
    { 6000.0f, 2560.66f, -13939.3f },
    { 6000.0f, 2640.605f, -14025.8f },
    { 6000.0f, 2713.525f, -14118.3f },
    { 6000.0f, 2778.96f, -14216.25f },
    { 6000.0f, 2836.51f, -14319.0f },
    { 6000.0f, 2885.82f, -14425.95f },
    { 6000.0f, 2926.585f, -14536.45f },
    { 6000.0f, 2958.555f, -14649.8f },
    { 6000.0f, 2981.53f, -14765.35f },
    { 6000.0f, 2995.375f, -14882.3f },
    { 6000.0f, 3000.0f, -15000.0f },
    { 5995.375f, 3000.0f, -15117.65f },
    { 5981.535f, 3000.0f, -15234.65f },
    { 5958.555f, 3000.0f, -15350.15f },
    { 5926.585f, 3000.0f, -15463.5f },
    { 5885.82f, 3000.0f, -15574.0f },
    { 5836.51f, 3000.0f, -15680.95f },
    { 5778.96f, 3000.0f, -15783.75f },
    { 5713.525f, 3000.0f, -15881.65f },
    { 5640.61f, 3000.0f, -15974.15f },
    { 5560.66f, 3000.0f, -16060.65f },
    { 5474.175f, 3000.0f, -16140.6f },
    { 5381.68f, 3000.0f, -16213.5f },
    { 5283.75f, 3000.0f, -16278.95f },
    { 5180.985f, 3000.0f, -16336.5f },
    { 5074.025f, 3000.0f, -16385.8f },
    { 4963.525f, 3000.0f, -16426.55f },
    { 4850.17f, 3000.0f, -16458.55f },
    { 4734.655f, 3000.0f, -16481.5f },
    { 4617.69f, 3000.0f, -16495.35f },
    { 4500.0f, 3000.0f, -16500.0f },
    { 4400.0f, 3000.0f, -16500.0f },
    { 4300.0f, 3000.0f, -16500.0f },
    { 4200.0f, 3000.0f, -16500.0f },
    { 4100.0f, 3000.0f, -16500.0f },
    { 4000.0f, 3000.0f, -16500.0f },
    { 3900.0f, 3000.0f, -16500.0f },
    { 3800.0f, 3000.0f, -16500.0f },
    { 3700.0f, 3000.0f, -16500.0f },
    { 3600.0f, 3000.0f, -16500.0f },
    { 3500.0f, 3000.0f, -16500.0f },
    { 3400.0f, 3000.0f, -16500.0f },
    { 3300.0f, 3000.0f, -16500.0f },
    { 3200.0f, 3000.0f, -16500.0f },
    { 3100.0f, 3000.0f, -16500.0f },
    { 3000.0f, 3000.0f, -16500.0f },
    { 2900.0f, 3000.0f, -16500.0f },
    { 2800.0f, 3000.0f, -16500.0f },
    { 2700.0f, 3000.0f, -16500.0f },
    { 2600.0f, 3000.0f, -16500.0f },
    { 2500.0f, 3000.0f, -16500.0f },
    { 2400.0f, 3000.0f, -16500.0f },
    { 2300.0f, 3000.0f, -16500.0f },
    { 2200.0f, 3000.0f, -16500.0f },
    { 2100.0f, 3000.0f, -16500.0f },
    { 2000.0f, 3000.0f, -16500.0f },
    { 1900.0f, 3000.0f, -16500.0f },
    { 1800.0f, 3000.0f, -16500.0f },
    { 1700.0f, 3000.0f, -16500.0f },
    { 1600.0f, 3000.0f, -16500.0f },
    { 1500.0f, 3000.0f, -16500.0f },
    { 1400.0f, 3000.0f, -16500.0f },
    { 1300.0f, 3000.0f, -16500.0f },
    { 1200.0f, 3000.0f, -16500.0f },
    { 1100.0f, 3000.0f, -16500.0f },
    { 1000.0f, 3000.0f, -16500.0f },
    { 900.0f, 3000.0f, -16500.0f },
    { 800.0f, 3000.0f, -16500.0f },
    { 700.0f, 3000.0f, -16500.0f },
    { 600.0f, 3000.0f, -16500.0f },
    { 500.0f, 3000.0f, -16500.0f },
    { 400.0f, 3000.0f, -16500.0f },
    { 300.0f, 3000.0f, -16500.0f },
    { 200.0f, 3000.0f, -16500.0f },
    { 100.0f, 3000.0f, -16500.0f },
    { 0.0f, 3000.0f, -16500.0f },
    { -100.0f, 3000.0f, -16500.0f },
    { -200.0f, 3000.0f, -16500.0f },
    { -300.0f, 3000.0f, -16500.0f },
    { -400.0f, 3000.0f, -16500.0f },
    { -500.0f, 3000.0f, -16500.0f },
    { -600.0f, 3000.0f, -16500.0f },
    { -700.0f, 3000.0f, -16500.0f },
    { -800.0f, 3000.0f, -16500.0f },
    { -900.0f, 3000.0f, -16500.0f },
    { -1000.0f, 3000.0f, -16500.0f },
    { -1100.0f, 3000.0f, -16500.0f },
    { -1200.0f, 3000.0f, -16500.0f },
    { -1300.0f, 3000.0f, -16500.0f },
    { -1400.0f, 3000.0f, -16500.0f },
    { -1500.0f, 3000.0f, -16500.0f }
};
s16 D_80113458_motor_rooter = 1;
// Indexed by player->unk14 - 1.
s16 D_8011345C_motor_rooter[6] = { 0, 100, 250, 400, 600, 0 };
s8 D_80113468_motor_rooter[4] = { 0 };
s8 D_8011346C_motor_rooter[4] = { 0 };
RGBA D_80113470_motor_rooter = { 255, 255, 255, 255 };
s32 D_80113474_motor_rooter[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5,
                                   0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s16 D_80113494_motor_rooter = 0;
s16 D_80113496_motor_rooter = 1;
s16 D_80113498_motor_rooter = 0;
s8 D_8011349C_motor_rooter[4] = { -8, 8, -2, 2 };
// Indexed by player->unk14 - 1.
s16 D_801134A0_motor_rooter[6] = { 999, 110, 90, 70, 60, 40 };

Gfx D_801134B0_motor_rooter[] = {
    gsSPSegment(0x00, 0x00000000),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPPipelineMode(G_PM_1PRIMITIVE),
    gsDPSetTextureLOD(G_TL_TILE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureDetail(G_TD_CLAMP),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0, 0),
    gsDPSetTileSize(1, 0, 0, 0, 0),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_4b, 0, 0x0000, 1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD,
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetTextureConvert(G_TC_FILT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsDPSetCombineKey(G_CK_NONE),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetDepthSource(G_ZS_PIXEL),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPNoOp(),
    gsDPSetColorDither(G_CD_DISABLE),
    gsDPPipeSync(),
    gsSPEndDisplayList(),
};

Gfx D_80113568_motor_rooter[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_80113588_motor_rooter[] = {
    gsSPDisplayList(D_80113568_motor_rooter),
    gsSPDisplayList(D_801134B0_motor_rooter),
    gsSPEndDisplayList(),
};

Gfx D_801135A0_motor_rooter[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_80113588_motor_rooter),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

const s16 D_801135E0_motor_rooter[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };
const s16 D_801135EC_motor_rooter[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000 };
const s16 D_801135FC_motor_rooter[] = { 0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000 };
const CourseModels D_80113608_motor_rooter = { { { 3, 4 }, { 5, 6 } } };
const ObstacleSprites D_80113618_motor_rooter = { { 14, 13, 11, 9, 12, 10, 8 } };
const CharacterSprites D_80113634_motor_rooter = { { 8, 9, 10, 11, 12, 13, 14, 15 } };

// BSS
PathPoint *D_801137C0_motor_rooter BSS;
MinigameData *m254_minigame BSS; // D_801137C4_motor_rooter
D_801137C8_motor_rooter_Struct *D_801137C8_motor_rooter BSS;
s16 D_801137CC_motor_rooter BSS;
s16 D_801137CE_motor_rooter BSS;
s16 D_801137D0_motor_rooter BSS;
s16 D_801137D2_motor_rooter BSS;
s16 m254_playerId[PLAYERS_TOTAL] BSS; // D_801137D4_motor_rooter
s16 D_801137D8_motor_rooter BSS;

void m254_OverlayMain(void) {
    m254_InitEnvironment();
}

void m254_InitEnvironment(void) {
    omObjData *temp_v0;

    MapCollInit(50);
    Hu3DSprModelInit(0x30);
    omInitObjMan(50, 0);
    omGameSysInit();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0->work[0] = 2;
    omSetStatBit(temp_v0, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 152.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 60.0f, 40.0f, 4000.0f);
    ScissorSet(1, 168.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(1, 60.0f, 40.0f, 4000.0f);
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    m254_CreateSystem();
    m254_CreateMinigame();
    omAddObj(100, 0, 0, -1, func_80106044_motor_rooter);
    omAddObj(1000, 0, 0, -1, m254_CheckExitRequest);
    GMesFontMesCreate(D_801135E0_motor_rooter, 1);
    GMesFontMesCreate(D_801135EC_motor_rooter, 1);
    GMesFontMesCreate(D_801135FC_motor_rooter, 1);
}

void m254_CreateMinigame(void) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m254_playerId[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m254_playerId[1] = i;
                player2Set = TRUE;
            }
        }
    }
    m254_minigame = HuMemAllocTag(sizeof(MinigameData), TAG_OVERLAY);
    memset(m254_minigame, 0, sizeof(MinigameData));
    m254_minigame->views = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerView), TAG_OVERLAY);
    memset(m254_minigame->views, 0, PLAYERS_TOTAL * sizeof(PlayerView));
    D_801137CE_motor_rooter = (rand16() % 201) / 100;
    switch (D_801137CE_motor_rooter) {
        case 0:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(D_80111550_motor_rooter, 321);
            break;
        case 1:
            D_801137CC_motor_rooter = 300;
            func_8010CD84_motor_rooter(D_8011245C_motor_rooter, 341);
            break;
        default:
            D_801137CC_motor_rooter = 280;
            func_8010CD84_motor_rooter(D_80111550_motor_rooter, 321);
            D_801137CE_motor_rooter = 0;
            break;
    }
    func_8010D2E4_motor_rooter(0);
    D_801137C8_motor_rooter = HuMemAllocTag(2 * sizeof(D_801137C8_motor_rooter_Struct), TAG_OVERLAY); // PLAYERS_TOTAL?
    memset(D_801137C8_motor_rooter, 0, 2 * sizeof(D_801137C8_motor_rooter_Struct));
}

void m254_CheckExitRequest(omObjData *object) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m254_WaitExitWipeOut;
    }
}

void m254_WaitExitWipeOut(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m254_ExitOverlay;
    }
}

void m254_ExitOverlay(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void func_80105F04_motor_rooter(void) {
    s16 i;

    for (i = 0; i < 2; i++) {
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
    }
    m254_UpdateFuncGroup(FGRP_CAMERA);
}

void func_80106044_motor_rooter(omObjData *object) {
    s16 i;

    Hu3DFogSet(0x3CA, 1000, 0xFF, 0xFF, 0xFF);
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    for (i = 0; i < 2; i++) {
        D_800EC1C0_minigame[i] = omAddObj(10, 2, 0, -1, func_801062BC_motor_rooter);
        m254_minigame->views[i].unk00 = omAddObj(100, 21, 0, -1, func_80106508_motor_rooter);
        m254_minigame->views[i].unk8C = omAddObj(200, 15, 0, -1, func_80106998_motor_rooter);
        omAddObj(500, 1, 0, -1, func_80107210_motor_rooter);
        omAddObj(800, 5, 0, -1, func_801079E8_motor_rooter);
        D_800EC598_minigame[i] = D_801137C8_motor_rooter[i].unk00 = omAddObj(300, 11, 40, -1, func_80106BAC_motor_rooter);
    }
    memset(&m254_minigame->runtime, 0, sizeof(m254_minigame->runtime));
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, m254_InitCamera, 0, FALSE);
    m254_SetFunc(1, 0, -1, NULL, func_80108BF0_motor_rooter, 0, FALSE);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    object->func = func_80106298_motor_rooter;
}

void func_80106298_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(1);
    func_80105F04_motor_rooter();
}

void func_801062BC_motor_rooter(omObjData *object) {
    s32 modelFlags = 0x99;
    CourseModels courseModels = D_80113608_motor_rooter;
    s16 modelCounts[2] = { 2, 2 };
    s16 i;
    s16 cameraMask;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[0];
    for (i = 0; i < modelCounts[D_801137CE_motor_rooter]; i++) {
        if (object->work[0] == 0) {
            object->model[i] = Hu3DModelRead(courseModels.fileIds[D_801137CE_motor_rooter][i] | 0x570000, modelFlags);
        } else {
            object->model[i] = Hu3DModelLink(D_800EC1C0_minigame[0]->model[i]);
        }
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, 0.0f);
    }
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < modelCounts[D_801137CE_motor_rooter]; i++) {
        Hu3DModelCameraSet(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[0]++;
    object->func = func_801064EC_motor_rooter;
}

void func_801064EC_motor_rooter(omObjData *object) {
    m254_SyncWithModel(object);
}

void func_80106508_motor_rooter(omObjData *object) {
    ObstacleSprites sprites = D_80113618_motor_rooter;
    s32 *fileIds;
    PlayerView *view;
    FuncContext *ctx;
    s16 i;
    s16 j;
    s16 cameraMask;
    s16 spriteId;
    s16 k;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[1];
    view = &m254_minigame->views[object->work[0]];
    for (i = 0, fileIds = sprites.fileIds; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            spriteId = HuSprAnimDataRead(fileIds[j] | 0x570000);
            m254_minigame->views[object->work[0]].obstacleSprites[i * 7 + j] = spriteId;
            object->model[i * 7 + j] = func_8010EFF8_motor_rooter(HuSprAnimDataGet(spriteId), 1.0f);
            Hu3DModelScaleSet(object->model[i * 7 + j], 2.0f, 2.0f, 2.0f);
        }
        view->obstacleSlots[i] = view->nextObstacleSlot++;
        if (view->nextObstacleSlot > D_801137D2_motor_rooter) {
            for (j = i * 7; j < i * 7 + 7; j++) {
                Hu3DModelAttrSet(object->model[j], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            view->obstacleSlots[i] = -1;
        } else {
            func_80109C94_motor_rooter(view, i);
        }
        view->obstacleFrames[i] = rand16() % 3;
    }
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            Hu3DModelCameraSet(object->model[i * 7 + j], cameraMask);
        }
    }
    m254_minigame->runtime.counters.initialization.viewCounters[1]++;
    m254_SetFunc(2, 6, -1, &m254_minigame->views[object->work[0]], func_8010961C_motor_rooter, object->work[0], FALSE);
    ctx = m254_SetFunc(2, 7, -1, &m254_minigame->views[object->work[0]], func_8010972C_motor_rooter, object->work[0], FALSE);
    for (k = 0; k < 3; k++) {
        ctx->work.s16[0] = k;
        func_801091A0_motor_rooter(ctx);
    }
    m254_SyncWithModel(object);
    object->func = func_80106968_motor_rooter;
}

void func_80106968_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(2);
    m254_SyncWithModel(object);
}

void func_80106998_motor_rooter(omObjData *object) {
    PlayerView *view;
    s16 i;
    s16 cameraMask;
    s32 modelFlags = 0x99;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[3];
    view = &m254_minigame->views[object->work[0]];
    for (i = 0; i < 15; i++) {
        if (object->work[0] == 0) {
            object->model[i] = Hu3DModelRead(0x570002, modelFlags);
        } else {
            object->model[i] = Hu3DModelLink(m254_minigame->views[0].unk8C->model[i]);
        }
        view->itemSlots[i] = view->nextItemSlot++;
        Hu3DModelScaleSet(object->model[i], 0.7f, 0.7f, 0.7f);
    }
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 15; i++) {
        Hu3DModelCameraSet(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[3]++;
    m254_SetFunc(3, 5, -1, object, func_8010A174_motor_rooter, 0, FALSE);
    object->func = func_80106B7C_motor_rooter;
}

void func_80106B7C_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup(3);
    m254_SyncWithModel(object);
}

void func_80106BAC_motor_rooter(omObjData *object) {
    s32 modelFiles[2] = { 0, 1 };
    func_800E1BA8_minigame_ObjData *data;
    s16 character;
    s32 modelFlags = 0x289;
    s32 characterIndex;
    s32 characterModel;
    s32 characterMotion;
    s32 motion;
    s16 cameraMask;
    s16 i;

    object->work[0] = D_800EC280_minigame;
    object->work[1] = m254_playerId[object->work[0]];
    character = GwPlayer[object->work[1]].chr;
    characterIndex = GwPlayer[object->work[1]].chr;
    characterModel = D_800A178C_main[characterIndex][0];
    characterMotion = D_800A178C_main[characterIndex][2];
    func_800E1BA8_minigame(object, characterModel, characterMotion, object->work[1], modelFlags, 0x299);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(object->model[1], 0.2f, 0.2f, 0.2f);
    object->model[9] = Hu3DModelRead(modelFiles[object->work[0]] | 0x570000, 0x299);
    Hu3DModelAttrSet(object->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    object->model[10] = Hu3DModelRead(9, 0x99);
    Hu3DModelScaleSet(object->model[10], 0.4f, 0.4f, 0.4f);
    motion = CharMotionDataNumGet(character, 0);
    func_800E5A00_minigame(object, 0, motion, 1, 0);
    motion = CharMotionDataNumGet(character, 4);
    func_800E5A00_minigame(object, 6, motion, 1, 19);
    motion = CharMotionDataNumGet(character, 47);
    func_800E5A00_minigame(object, 13, motion, 1, 999);
    motion = CharMotionDataNumGet(character, 31);
    func_800E5A00_minigame(object, 21, motion, 1, 999);
    motion = CharMotionDataNumGet(character, 39);
    func_800E5A00_minigame(object, 38, motion, 1, 0);
    motion = CharMotionDataNumGet(character, 40);
    func_800E5A00_minigame(object, 39, motion, 1, 99);
    object->trans.x = 0.0f;
    object->trans.y = -56.0f;
    object->trans.z = 100.0f;
    object->rot.y = 180.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.2f;
    Hu3DModelPosSet(object->model[9], 0.0f, 0.0f, 200.0f);
    Hu3DModelRotSet(object->model[9], 0.0f, 180.0f, 0.0f);
    Hu3DModelAttrSet(object->model[10], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8010BDE4_motor_rooter(&D_801137C8_motor_rooter[object->work[0]], 38, 1);
    D_800EC280_minigame++;
    data = object->data;
    D_801137C8_motor_rooter[object->work[0]].unk08 = 1;
    D_801137C8_motor_rooter[object->work[0]].controllerPort = data->unk57;
    D_801137C8_motor_rooter[object->work[0]].direction = 0;
    D_801137C8_motor_rooter[object->work[0]].unk14 = 1;
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 11; i++) {
        Hu3DModelCameraSet(object->model[i], cameraMask);
    }
    m254_SetFunc((u8)object->work[0] + 4, 5, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010ABC4_motor_rooter, 0, 0);
    m254_SetFunc((u8)object->work[0] + 4, 9, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BCD0_motor_rooter, 0, 0);
    m254_SetFunc((u8)object->work[0] + 4, 4, -1, &D_801137C8_motor_rooter[object->work[0]], func_8010BB78_motor_rooter, 0, 0);
    object->func = func_801070CC_motor_rooter;
}

void func_801070CC_motor_rooter(omObjData *object) {
    m254_UpdateFuncGroup((u8)object->work[0] + 4);
    func_800E4E30_minigame(object);
    if (object->rot.x >= 360.0f) {
        object->rot.x -= 360.0f;
    }
    if (object->rot.x < 0.0f) {
        object->rot.x += 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    if (object->rot.z >= 360.0f) {
        object->rot.z -= 360.0f;
    }
    if (object->rot.z < 0.0f) {
        object->rot.z += 360.0f;
    }
}

void func_80107210_motor_rooter(omObjData *object) {
    CharacterSprites characters = D_80113634_motor_rooter;
    s16 sprite;
    s16 i;
    f32 y;

    object->work[0] = m254_minigame->runtime.counters.initialization.viewCounters[2];
    object->work[1] = m254_playerId[object->work[0]];
    m254_SetSpriteDispOn(m254_SetSprite(0xFFFF, 0x57, 7, 0, 0), 160, 120);
    for (i = 0; i < 5; i++) {
        sprite = m254_SetSprite(0xFFFF, 0x21, 0x18, 0, 0);
        if (object->work[0] == 0) {
            m254_SetSpriteDispOn(sprite, (s16)(35 + i * 10), 25);
        } else {
            m254_SetSpriteDispOn(sprite, (s16)(285 - i * 10), 25);
        }
    }
    for (i = 0; i < 5; i++) {
        sprite = D_801137C8_motor_rooter[object->work[0]].meterSprites[i] = m254_SetSprite(0xFFF, 0x21, 0x19, 0, 0x1000);
        if (object->work[0] == 0) {
            m254_SetSpriteDispOn(sprite, (s16)(35 + i * 10), 25);
        } else {
            m254_SetSpriteDispOn(sprite, (s16)(285 - (4 - i) * 10), 25);
        }
        if (i == 0) {
            m254_sprites[sprite].unk06 = 255;
        } else {
            m254_sprites[sprite].unk06 = 0;
        }
        HuSprTPLvlSet(m254_sprites[sprite].groupId, 0, (u8)m254_sprites[sprite].unk06);
        D_801137C8_motor_rooter[object->work[0]].unk28[i] = 0;
    }
    D_801137C8_motor_rooter[object->work[0]].progressSprite = sprite = m254_SetSprite(0xFFF, 0x21, characters.fileIds[GwPlayer[m254_playerId[object->work[0]]].chr], 0, 0);
    m254_SetSpriteDispOn(sprite, (s16)(152 + object->work[0] * 16), 220);
    for (i = 0; i < D_801137D2_motor_rooter; i++) {
        y = 220 - (s16)(D_801137C0_motor_rooter[m254_minigame->views[object->work[0]].obstaclePoints[i]].cumDist / m254_minigame->finishDistance * 180.0f);
        sprite = m254_SetSprite(0xEFFF, 0x57, 0x11, 0, 0);
        m254_SetSpriteDispOn(sprite, (s16)(152 + object->work[0] * 16), (s16)y);
    }
    m254_minigame->runtime.counters.initialization.viewCounters[2]++;
    object->func = func_801076AC_motor_rooter;
}

void func_801076AC_motor_rooter(omObjData *object) {
    D_801137C8_motor_rooter_Struct *player = D_801137C8_motor_rooter;
    SpriteData *sprite;
    s16 fading;
    s16 i;
    s16 j;
    s16 y;
    s16 alpha;

    for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
        fading = 0;
        for (j = 0; j < 5; j++) {
            if (player->unk28[j] != 0) {
                fading = 1;
            }
        }
        if (!fading && player->unk14 == 5) {
            if (D_80113468_motor_rooter[i] == 0) {
                for (j = 0; j < 5; j++) {
                    sprite = &m254_sprites[player->meterSprites[j]];
                    HuSprTPLvlSet(sprite->groupId, 0, 0);
                }
                if (++D_8011346C_motor_rooter[i] >= 3) {
                    D_8011346C_motor_rooter[i] = 0;
                    D_80113468_motor_rooter[i] = 1;
                }
            } else {
                for (j = 0; j < 5; j++) {
                    sprite = &m254_sprites[player->meterSprites[j]];
                    HuSprTPLvlSet(sprite->groupId, 0, 255);
                }
                if (++D_8011346C_motor_rooter[i] >= 3) {
                    D_8011346C_motor_rooter[i] = 0;
                    D_80113468_motor_rooter[i] = 0;
                }
            }
        } else {
            for (j = 0; j < 5; j++) {
                sprite = &m254_sprites[player->meterSprites[j]];
                if (player->unk28[j] == 0) {
                    HuSprTPLvlSet(sprite->groupId, 0, (u8)sprite->unk06);
                } else {
                    if (player->unk28[j] == 1) {
                        alpha = sprite->unk06 + 10;
                        sprite->unk06 = alpha;
                        if (alpha >= 255) {
                            alpha = 255;
                            sprite->unk06 = alpha;
                            player->unk28[j] = 0;
                        }
                    } else {
                        alpha = sprite->unk06 - 10;
                        sprite->unk06 = alpha;
                        if (alpha <= 0) {
                            sprite->unk06 = 0;
                            player->unk28[j] = 0;
                        }
                    }
                    HuSprTPLvlSet(sprite->groupId, 0, (u8)sprite->unk06);
                }
            }
        }
        if (!(player->unk08 & 0x40)) {
            y = 220 - (s32)(player->unk0C / m254_minigame->finishDistance * 180.0f);
            m254_SetSpriteDispOn(player->progressSprite, (s16)(152 + i * 16), y);
        }
    }
}

void func_801079E8_motor_rooter(omObjData *object) {
    s16 i;
    s16 cameraMask;
    s16 spriteId;
    HuSprAnimData *sprite;

    object->work[0] = m254_minigame->runtime.counters.initialization.itemViewCount;
    for (i = 0; i < 4; i++) {
        m254_minigame->views[object->work[0]].itemSprites[i] = spriteId = HuSprAnimDataRead(0x570010);
        sprite = HuSprAnimDataGet(spriteId);
        object->model[i] = func_8010FC10_motor_rooter(sprite, &D_80113470_motor_rooter);
        Hu3DModelScaleSet(object->model[i], 2.0f, 2.0f, 1.0f);
        Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        m254_minigame->views[object->work[0]].itemFrames[i] = 0;
        m254_minigame->views[object->work[0]].itemDelays[i] = rand16() % 11;
        m254_minigame->views[object->work[0]].itemStates[i] = 0;
    }
    m254_minigame->views[object->work[0]].itemTimer = 0;
    m254_minigame->views[object->work[0]].itemSprites[i] = spriteId = HuSprAnimDataRead(0x57000F);
    sprite = HuSprAnimDataGet(spriteId);
    object->model[i] = func_8010EFF8_motor_rooter(sprite, 1.0f);
    Hu3DModelScaleSet(object->model[i], 1.5f, 1.5f, 1.0f);
    Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    m254_minigame->views[object->work[0]].itemFrames[i] = 0;
    m254_SyncWithModel(object);
    cameraMask = object->work[0] == 0 ? 1 : 2;
    for (i = 0; i < 5; i++) {
        Hu3DModelCameraSet(object->model[i], cameraMask);
    }
    m254_minigame->runtime.counters.initialization.itemViewCount++;
    object->func = func_80107D50_motor_rooter;
}

void func_80107D50_motor_rooter(omObjData *object) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *player;
    s16 camera;
    s16 i;
    s16 j;

    camera = object->work[0];
    view = &m254_minigame->views[camera];
    player = &D_801137C8_motor_rooter[camera];
    i = 0;
    if (player->unk10 == 0.0f) {
        for (i = 0; i < 5; i++) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
        return;
    }
    if (player->unk78 & 4) {
        for (i = 0; i < 4; i++) {
            if (view->itemDelays[i] != 99) {
                if (++m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] > view->itemDelays[i]) {
                    Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    func_8010CB2C_motor_rooter(object, 4, i);
                    func_801108CC_motor_rooter(object->model[i], HuSprAnimDataGet(view->itemSprites[i]),
                                               view->itemFrames[i], &D_80113470_motor_rooter);
                    if (++view->itemFrames[i] >= 15) {
                        if (view->itemStates[i] == 0) {
                            view->itemStates[i] = 1;
                            view->itemFrames[i] = 0;
                        } else {
                            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] = 0;
                            view->itemDelays[i] = 99;
                            view->itemFrames[i] = 0;
                            if (++view->itemTimer >= 4) {
                                for (j = 0; j < 4; j++) {
                                    view->itemStates[j] = 0;
                                    view->itemDelays[j] = rand16() % 11;
                                }
                                player->unk78 &= ~4;
                            }
                        }
                    }
                }
            }
        }
    } else if (player->unk78 & 1) {
        Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8010CB2C_motor_rooter(object, 1, 0);
        func_801108CC_motor_rooter(object->model[0], HuSprAnimDataGet(view->itemSprites[0]),
                                   view->itemFrames[0], &D_80113470_motor_rooter);
        if (++view->itemFrames[0] >= 15) {
            Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            player->unk78 &= ~1;
            view->itemFrames[0] = 0;
        }
    }
    if (player->unk78 & 2) {
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        func_8010CB2C_motor_rooter(object, 2, 4);
        func_801107FC_motor_rooter(object->model[4], HuSprAnimDataGet(view->itemSprites[4]), view->itemFrames[4]);
        if (++m254_minigame->runtime.counters.gameplay.impactFrameCounters[object->work[0]] >= 2) {
            m254_minigame->runtime.counters.gameplay.impactFrameCounters[object->work[0]] = 0;
            if (++view->itemFrames[4] >= 5) {
                Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                player->unk78 &= ~2;
                view->itemFrames[4] = 0;
            }
        }
    }
    m254_SyncWithModel(object);
}

void m254_InitCamera(FuncContext *ctx) {
    s16 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 100.0f;
        CenterM[i].x = D_801137C0_motor_rooter[0].x;
        CenterM[i].y = D_801137C0_motor_rooter[0].y;
        CenterM[i].z = D_801137C0_motor_rooter[0].z;
        CRotM[i].x = D_801137C0_motor_rooter[0].pitch - 180.0f;
        CRotM[i].y = D_801137C0_motor_rooter[0].yaw;
        CRotM[i].z = D_801137C0_motor_rooter[0].unk14;
    }
    m254_ResetFunc(FGRP_CAMERA, ctx);
    m254_SetFunc(FGRP_CAMERA, 0, -1, NULL, func_801082E0_motor_rooter, 0, FALSE);
}

void func_801082E0_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *var_s1;
    PathPosition position;
    s16 temp_v0;
    s16 i;

    view = m254_minigame->views;
    var_s1 = D_801137C8_motor_rooter;
    for (i = 0; i < 2; i++, var_s1++, view++) {
        if (var_s1->unk08 & 0x80) {
            continue;
        }
        temp_v0 = func_8010D03C_motor_rooter(var_s1->unk0C);
        position = func_8010D0AC_motor_rooter(temp_v0, var_s1->unk0C);
        CenterM[i].x = position.x;
        CenterM[i].y = position.y;
        CenterM[i].z = position.z;
        CRotM[i].x = position.pitch - 180.0f;
        CRotM[i].y = position.yaw;
        CRotM[i].z = position.roll;
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
        var_s1->unk1C = temp_v0 + 1;
        view->unk8A = temp_v0;
    }
}

void func_80108514_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 camera = object->work[0];
    PathPosition position;
    f32 t;
    s32 fileId;

    if (ctx->state == 0) {
        position = func_8010D0AC_motor_rooter(func_8010D03C_motor_rooter(player->unk0C + 90.0),
                                              player->unk0C + 90.0);
        ctx->work.f32[0] = position.x;
        ctx->work.f32[1] = position.y - 30.0;
        ctx->work.f32[2] = position.z;
        player->cameraStart.x = CenterM[camera].x;
        player->cameraStart.y = CenterM[camera].y;
        player->cameraStart.z = CenterM[camera].z;
        ctx->work.s8[0] = ctx->work.s8[1] = ctx->work.s8[2] = 0;
        ctx->state = 1;
    }
    t = ctx->work.s8[0] / 30.0f;
    t = sindf(t * 90.0f);
    t = t > 1.0f ? 1.0f : t;
    CenterM[camera].x = (ctx->work.f32[0] - player->cameraStart.x) * t + player->cameraStart.x;
    CenterM[camera].y = (ctx->work.f32[1] - player->cameraStart.y) * t + player->cameraStart.y;
    CenterM[camera].z = (ctx->work.f32[2] - player->cameraStart.z) * t + player->cameraStart.z;
    if (++ctx->work.s8[0] >= 31) {
        fileId = D_80113474_motor_rooter[GwPlayer[m254_playerId[object->work[0]]].chr];
        CharAnimCreate(object->model[0], 2, GwPlayer[m254_playerId[object->work[0]]].chr, fileId);
        func_8010BDE4_motor_rooter(player, 0xD, 1);
        m254_ResetFunc(FGRP_CAMERA, ctx);
        m254_SetFunc(1, 0, -1, player, func_80108E6C_motor_rooter, 0, FALSE);
    }
}

void func_801087C0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = D_801137C8_motor_rooter;
    s16 count = 0;
    s16 finishers[2];
    s16 i;
    s32 loser;
    D_801137C8_motor_rooter_Struct *winnerPlayer;
    D_801137C8_motor_rooter_Struct *loserPlayer;

    finishers[0] = -1;
    finishers[1] = -1;
    for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
        if (!(player->unk08 & 0x40) && player->unk1C == D_801137CC_motor_rooter) {
            finishers[count] = i;
            count++;
        }
    }
    if (count != 0) {
        if (count == 2) {
            i = rand16() % 2;
        } else {
            i = finishers[0];
        }
        D_801137C8_motor_rooter[i].unk08 |= 0x50;
        loser = !i;
        D_801137C8_motor_rooter[loser].unk08 |= 0x41;
        HuAudSeqFadeOut(120);
        GMesCreate(0x11);
        GMesTimerEnd();
        m254_minigame->runtime.unk20 = 99.0f;
        winnerPlayer = &D_801137C8_motor_rooter[i];
        m254_SetFunc((u8)winnerPlayer->unk00->work[0] + 4, 5, -1, winnerPlayer, func_8010C084_motor_rooter, 0, 0);
        loserPlayer = &D_801137C8_motor_rooter[loser];
        m254_SetFunc((u8)loserPlayer->unk00->work[0] + 4, 5, -1, loserPlayer, func_8010C824_motor_rooter, 0, 0);
        m254_ResetFunc(1, ctx);
    }
}

void func_801089B8_motor_rooter(FuncContext *ctx) {
    s16 i;
    f32 fps;

    switch (ctx->state) {
        case 0:
            m254_minigame->timer = 1800.0f;
            fps = 30.0f;
            GMesCreate(0x1A, 60.0, 160, 28);
            GMesTimerValueSet((m254_minigame->timer + 29.0f) / fps);
            ctx->state = 1;
            break;
        case 1:
            if (m254_minigame->runtime.unk20 == 99.0f) {
                break;
            }
            m254_minigame->timer -= 1.0f;
            GMesTimerValueSet((m254_minigame->timer + 29.0f) * (1.0f / 30.0f));
            if (m254_minigame->timer < 0.0f) {
                GMesTimerEnd();
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80108FDC_motor_rooter, 0, FALSE);
                for (i = 0; i < 2; i++) {
                    D_801137C8_motor_rooter[i].unk08 |= 0x41;
                    m254_SetFunc((u8)D_801137C8_motor_rooter[i].unk00->work[0] + 4, 5, -1,
                                 &D_801137C8_motor_rooter[i], func_8010C824_motor_rooter, 0, FALSE);
                }
            }
            break;
    }
}

void func_80108BF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    s16 i;

    player = D_801137C8_motor_rooter;
    if (ctx->state == 0) {
        ctx->work.s16[0] = 0;
        ctx->state = 1;
    }
    switch (++ctx->work.s16[0]) {
        case 10:
            for (i = 0; i < 2; i++, player++) {
                m254_SetFunc(i + 4, 0, -1, player, func_8010BDF0_motor_rooter, 0, FALSE);
            }
            break;
        case 110:
            GMesCreate(6);
            HuAudFXPlay(14);
            HuAudSeqPlay(0x37);
            break;
        case 130:
            D_80113494_motor_rooter = 1;
            break;
        default:
            if (D_80113494_motor_rooter && GMesStatGet() == GMES_STAT_TIMEEND) {
                m254_SetFunc(1, 0, -1, NULL, func_801089B8_motor_rooter, 0, FALSE);
                for (i = 0; i < 2; i++, player++) {
                    player->unk08 = (player->unk08 & ~1) | 0x120;
                    player->unk10 = 1.0f;
                    player->unk4C = 0;
                    if (GwPlayer[m254_playerId[i]].stat & PLAYER_IS_CPU) {
                        player->isCpu = TRUE;
                        m254_SetFunc(i + 4, 0, -1, player, func_8010A440_motor_rooter, 0, FALSE);
                    } else {
                        player->isCpu = FALSE;
                    }
                }
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 1, -1, NULL, func_801087C0_motor_rooter, 0, FALSE);
            }
            break;
    }
}

void func_80108E6C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 timer;

    if (D_80113496_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113496_motor_rooter = 3;
        }
        if (D_80113496_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else {
        timer = ctx->work.s16[0]++;
        if (timer == 0) {
            HuAudSeqPlay(0x67);
            GMesCreate(0x16, GwPlayer[m254_playerId[object->work[0]]].chr);
            GwPlayer[m254_playerId[object->work[0]]].bonusCoin += 10;
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113496_motor_rooter = 2;
        }
    }
}

void func_80108FDC_motor_rooter(FuncContext *ctx) {
    s16 timer;

    if (D_80113498_motor_rooter >= 2) {
        if (GMesStatGet() == 0) {
            D_80113498_motor_rooter = 3;
        }
        if (D_80113498_motor_rooter == 3) {
            if (++ctx->work.s16[0] >= 15) {
                m254_ResetFunc(1, ctx);
                m254_SetFunc(1, 0, -1, NULL, func_80109134_motor_rooter, 0, TRUE);
            }
        }
    } else if (D_80113498_motor_rooter == 1) {
        timer = ctx->work.s16[0]++;
        if (timer == 15) {
            GMesCreate(0x20);
            HuAudSeqPlay(0x6C);
        }
        if (GMesStatGet() != 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 2;
        }
    } else {
        timer = ctx->work.s16[0]++;
        if (timer == 0) {
            HuAudSeqFadeOut(120);
            GMesCreate(0x11);
        } else if (GMesStatGet() == 0) {
            ctx->work.s16[0] = 0;
            D_80113498_motor_rooter = 1;
        }
    }
}

void func_80109134_motor_rooter(FuncContext *ctx) {
    switch (ctx->state) {
        case 0:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            ctx->state = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
    }
}

void func_801091A0_motor_rooter(FuncContext *ctx) {
    PlayerView *view = ctx->data;
    omObjData *object = view->unk00;
    s16 direction = 0;
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    s16 directions0[] = { 0, 1, 2, 3, -1, -2, -3 };
    s16 directions2[] = { 0, 1, 99, 2, -1, -2, -3 };
    s16 directions3[] = { 0, 1, 2, 3, -1, 99, -2 };
    s16 directions1[] = { 0, 1, 99, 2, -1, 99, -2 };
    s16 i;
    s16 obstacle;
    HmfModel *model;
    PathPoint *point;
    f32 angle;
    f32 pitch;

    obstacle = view->obstacleSlots[ctx->work.s16[0]];
    for (i = 0; i < 7; i++) {
        model = &Hu3DData[object->model[ctx->work.s16[0] * 7 + i]];
        switch (view->obstacleTypes[obstacle]) {
            case 0:
                direction = view->obstacleDirections[obstacle] + directions0[i];
                break;
            case 1:
                direction = view->obstacleDirections[obstacle] + directions1[i];
                break;
            case 2:
                direction = view->obstacleDirections[obstacle] + directions2[i];
                break;
            case 3:
                direction = view->obstacleDirections[obstacle] + directions3[i];
                break;
        }
        if (direction >= 51) {
            Hu3DModelPosSet(object->model[ctx->work.s16[0] * 7 + i], 0.0f, 200.0f, 0.0f);
            Hu3DModelAttrSet(object->model[ctx->work.s16[0] * 7 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            continue;
        }
        if (direction >= 8) {
            direction -= 8;
        }
        if (direction < 0) {
            direction += 8;
        }
        angle = direction * 45.0f;
        offset.x = sindf(angle) * 55.9999990463256836;
        offset.y = -cosdf(angle) * 55.9999990463256836;
        offset.z = 0.0f;
        point = &D_801137C0_motor_rooter[view->obstaclePoints[obstacle]];
        pitch = point->pitch - 180.0f;
        m254_MakeRotXMtx(rotX, pitch);
        m254_MakeRotYMtx(rotY, point->yaw);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        model->pos.x = point->x + position[0];
        model->pos.y = point->y + position[1];
        model->pos.z = point->z + position[2];
        model->rot.x = pitch;
        model->rot.y = point->yaw;
        m254_MakeIdentityMtx(model->mtx[0]);
        mtxRotCat(model->mtx, 0.0f, 0.0f, angle);
    }
}

void func_8010961C_motor_rooter(FuncContext *ctx) {
    PlayerView *view;
    omObjData *object;
    s16 i;
    s16 j;

    view = ctx->data;
    object = view->unk00;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 7; j++) {
            func_801107FC_motor_rooter(object->model[i * 7 + j],
                                       HuSprAnimDataGet(view->obstacleSprites[i * 7 + j]),
                                       view->obstacleFrames[i]);
        }
        view->obstacleFrames[i] = view->obstacleFrames[i] + 1 < 5 ? view->obstacleFrames[i] + 1 : 0;
    }
}

void func_8010972C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    PlayerView *view;
    omObjData *object;
    s16 distance;
    s16 slot;
    s16 obstacle;
    s16 i;

    player = &D_801137C8_motor_rooter[ctx->tag];
    view = ctx->data;
    object = view->unk00;
    distance = 9999;
    for (slot = 0; slot < 3; slot++) {
        obstacle = view->obstacleSlots[slot];
        if (obstacle == -1) {
            continue;
        }
        if (view->obstaclePoints[obstacle] - player->unk1C < m254_minigame->unk0E) {
            for (i = slot * 7; i < slot * 7 + 7; i++) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
        } else {
            for (i = slot * 7; i < slot * 7 + 7; i++) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
        if (distance > view->obstaclePoints[obstacle] - player->unk1C) {
            distance = view->obstaclePoints[obstacle] - player->unk1C;
        }
        ctx->work.s16[0] = slot;
        if (!(player->unk08 & 0x42) && player->unk1C == view->obstaclePoints[obstacle] &&
            player->direction != view->obstacleSafeDirections[slot][0] &&
            player->direction != view->obstacleSafeDirections[slot][1] &&
            player->direction != view->obstacleSafeDirections[slot][2]) {
            for (i = 0; i < 3; i++) {
                if (player->unk14 - 1 > 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                    player->unk10 -= 4.0f;
                }
            }
            HuAudPlayerFXPlay(0x4B0, player->unk00->work[0]);
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345C_motor_rooter[player->unk14 - 1]);
            player->unk08 |= 2;
            player->unk78 |= 2;
            func_8010BDE4_motor_rooter(player, 0x27, 1);
            if (!player->isCpu) {
                omVibrate(m254_playerId[ctx->tag], 2, 2, 20);
            }
        }
        if (view->unk8A > view->obstaclePoints[obstacle] + 2) {
            view->obstacleSlots[slot] = view->nextObstacleSlot++;
            if (view->nextObstacleSlot > D_801137D2_motor_rooter) {
                for (i = slot * 7; i < slot * 7 + 7; i++) {
                    Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                view->obstacleSlots[slot] = -1;
            } else {
                for (i = slot * 7; i < slot * 7 + 7; i++) {
                    Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                func_80109C94_motor_rooter(view, slot);
                func_801091A0_motor_rooter(ctx);
            }
        }
    }
    if (!player->obstacleSoundStarted) {
        player->obstacleSoundStarted = 1;
        player->obstacleSound = _HuAudPlayerFXPlay(0x4B2, ctx->tag);
        HuAudFXVolSet(player->obstacleSound, 0);
    }
    distance += 3;
    if (distance < 26) {
        distance = distance < 0 ? 0 : distance;
        HuAudFXVolSet(player->obstacleSound, 127 - distance * 3);
    } else {
        HuAudFXVolSet(player->obstacleSound, 0);
    }
}

void func_80109C94_motor_rooter(PlayerView *view, s16 slot) {
    s16 i;

    switch (view->obstacleTypes[view->obstacleSlots[slot]]) {
        case 0:
            view->obstacleSafeDirections[slot][0] = view->obstacleSafeDirections[slot][1] =
                view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            break;
        case 1:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 5;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 3;
            break;
        case 2:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 3;
            break;
        case 3:
            view->obstacleSafeDirections[slot][0] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][1] = view->obstacleDirections[view->obstacleSlots[slot]] + 4;
            view->obstacleSafeDirections[slot][2] = view->obstacleDirections[view->obstacleSlots[slot]] + 5;
            break;
    }
    for (i = 0; i < 3; i++) {
        if (view->obstacleSafeDirections[slot][i] >= 8) {
            view->obstacleSafeDirections[slot][i] -= 8;
        }
        if (view->obstacleSafeDirections[slot][i] < 0) {
            view->obstacleSafeDirections[slot][i] += 8;
        }
    }
}

void func_80109EFC_motor_rooter(FuncContext *ctx) {
    omObjData *object = ctx->data;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    HmfModel *model;
    PathPoint *point;
    f32 angle;
    s16 slot = ctx->work.s16[0];
    f32 pitch;

    model = &Hu3DData[object->model[slot]];
    angle = m254_minigame->itemDirections[view->itemSlots[slot]] * 45.0f;
    offset.x = sindf(angle) * 64.0000009536743164;
    offset.y = -cosdf(angle) * 64.0000009536743164;
    offset.z = -30.0f;
    point = &D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]];
    pitch = point->pitch - 180.0f;
    m254_MakeRotXMtx(rotX, pitch);
    m254_MakeRotYMtx(rotY, point->yaw);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    model->pos.x = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].x + position[0];
    model->pos.y = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].y + position[1];
    model->pos.z = D_801137C0_motor_rooter[m254_minigame->itemPoints[view->itemSlots[slot]]].z + position[2];
    model->rot.x = pitch;
    model->rot.y = point->yaw;
    m254_MakeIdentityMtx(model->mtx[0]);
    mtxRotCat(model->mtx, 0.0f, 0.0f, angle);
}

void func_8010A174_motor_rooter(FuncContext *ctx) {
    omObjData *object;
    PlayerView *view;
    D_801137C8_motor_rooter_Struct *player;
    s16 slot;

    object = ctx->data;
    view = &m254_minigame->views[object->work[0]];
    player = &D_801137C8_motor_rooter[object->work[0]];
    if (ctx->work.s16[1] != player->unk1C) {
        for (slot = 0; slot < 15; slot++) {

            if (view->itemSlots[slot] >= D_801137D0_motor_rooter) {
                Hu3DModelAttrSet(object->model[slot], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                continue;
            }
            ctx->work.s16[0] = slot;
            func_80109EFC_motor_rooter(ctx);
            if (player->unk1C == m254_minigame->itemPoints[view->itemSlots[slot]] &&
                player->direction == m254_minigame->itemDirections[view->itemSlots[slot]]) {
                if (player->unk14 + 1 < 6) {
                    if (player->unk48 > 90) {
                        player->unk48 = 180 - player->unk48;
                    }
                    player->unk4C = 0;
                    player->unk28[player->unk14++] = 1;
                    player->unk10 += 4.0f;
                    player->unk08 |= 0x20;
                    player->unk78 |= 1;
                    ctx->work.s16[1] = player->unk1C;
                    HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345C_motor_rooter[player->unk14 - 1]);
                    _HuAudPlayerFXPlay(0x4B1, player->unk00->work[0]);
                    if (!player->isCpu) {
                        omVibrate(m254_playerId[object->work[0]], 10, 0, 10);
                    }
                } else {
                    if (player->unk48 > 90) {
                        player->unk48 = 180 - player->unk48;
                    }
                    player->unk08 |= 0x20;
                    player->unk78 |= 1;
                    ctx->work.s16[1] = player->unk1C;
                    player->unk4C = 0;
                    _HuAudPlayerFXPlay(0x4B1, player->unk00->work[0]);
                    if (!player->isCpu) {
                        omVibrate(m254_playerId[object->work[0]], 10, 0, 10);
                    }
                }
            }
            if (view->unk8A > m254_minigame->itemPoints[view->itemSlots[slot]]) {
                view->itemSlots[slot] = view->nextItemSlot++;
            }
        }
    }
}

void func_8010A440_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    PlayerView *view = &m254_minigame->views[object->work[0]];
    s16 selected = 0;
    s16 obstacleClosest;
    s16 itemClosest;
    s16 obstacleI;
    s16 itemI;
    s16 obstaclePoint;
    s16 itemPoint;
    s16 slot;
    s16 obstacleDirection;
    s16 itemDirection;
    s16 obstacleTargetDirection;
    s16 itemTargetDirection;
    s16 obstacleDifference;
    s16 itemDifference;
    s32 unused[24]; // Unreferenced, but present in the stack frame.

    if (!ctx->state) {
        switch (GwPlayer[m254_playerId[object->work[0]]].cpu_difficulty) {
            case 0:
                ctx->work.s8[2] = 8;
                ctx->work.s8[3] = 7;
                ctx->work.s8[4] = 5;
                ctx->work.s8[5] = 3;
                ctx->work.s8[6] = 1;
                ctx->work.s8[7] = 1;
                break;
            case 1:
                ctx->work.s8[2] = 6;
                ctx->work.s8[3] = 5;
                ctx->work.s8[4] = 4;
                ctx->work.s8[5] = 4;
                ctx->work.s8[6] = 3;
                ctx->work.s8[7] = 3;
                break;
            case 2:
                ctx->work.s8[2] = 4;
                ctx->work.s8[3] = 3;
                ctx->work.s8[4] = 3;
                ctx->work.s8[5] = 5;
                ctx->work.s8[6] = 6;
                ctx->work.s8[7] = 6;
                break;
            case 3:
                ctx->work.s8[2] = 2;
                ctx->work.s8[3] = 1;
                ctx->work.s8[4] = 2;
                ctx->work.s8[5] = 6;
                ctx->work.s8[6] = 8;
                ctx->work.s8[7] = 10;
                break;
        }
        ctx->work.s16[1] = 8;
        ctx->state = 1;
    }
    D_800CBB6E_main[player->controllerPort] = 0;
    D_800D20A1_main[player->controllerPort] = 0;
    D_800CDA7C_main[player->controllerPort] = 0;
    obstacleClosest = 999;
    for (obstacleI = 0; obstacleI < 3; obstacleI++) {
        if (view->obstacleSlots[obstacleI] != -1) {
            obstaclePoint = view->obstaclePoints[view->obstacleSlots[obstacleI]];
            if (player->unk1C <= obstaclePoint) {
                if (obstaclePoint < obstacleClosest) {
                    obstacleClosest = obstaclePoint;
                    selected = obstacleI;
                }
            }
        }
    }
    if (obstacleClosest != 999 && player->unk1C + ctx->work.s16[1] > view->obstaclePoints[view->obstacleSlots[selected]]) {
        obstacleDirection = player->direction;
        obstacleTargetDirection = view->obstacleSafeDirections[selected][0];
        if (obstacleDirection != obstacleTargetDirection) {
            obstacleDifference = obstacleTargetDirection - obstacleDirection;
            if (obstacleDifference < 0) {
                obstacleDifference += 7;
            }
            if (ctx->work.s8[0] > ctx->work.s8[2]) {
                ctx->work.s8[0] = 0;
                switch (D_80113458_motor_rooter) {
                    case 0:
                    case 1:
                        if (obstacleDifference < 3) {
                            D_800CBB6E_main[player->controllerPort] = 50;
                        } else {
                            if (obstacleDifference < 4) {
                                (void)rand16();
                            }
                            D_800CBB6E_main[player->controllerPort] = -50;
                        }
                        break;
                    case 2:
                        if (obstacleDifference < 3) {
                            ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x8000;
                        } else {
                            if (obstacleDifference < 4) {
                                (void)rand16();
                            }
                            ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x4000;
                        }
                        break;
                }
            } else {
                ctx->work.s8[0]++;
            }
        } else {
            ctx->work.s16[1] = 8 - rand16() % (ctx->work.s8[3] + 1);
        }
    } else {
        ctx->work.s8[0] = 0;
        if (rand16() % (ctx->work.s8[7] + 1)) {
            itemClosest = 999;
            for (itemI = 0; itemI < 15; itemI++) {
                slot = view->itemSlots[itemI];
                itemPoint = m254_minigame->itemPoints[slot];
                if (player->unk1C < itemPoint) {
                    if (itemPoint < itemClosest) {
                        itemClosest = itemPoint;
                        selected = slot;
                    }
                }
            }
            if (itemClosest != 999 && player->unk1C + ctx->work.s8[5] > m254_minigame->itemPoints[selected]) {
                itemDirection = player->direction;
                itemTargetDirection = m254_minigame->itemDirections[selected];
                if (itemDirection != itemTargetDirection) {
                    itemDifference = itemTargetDirection - itemDirection;
                    if (itemDifference < 0) {
                        itemDifference += 7;
                    }
                    if (ctx->work.s8[1] > ctx->work.s8[4]) {
                        ctx->work.s8[1] = 0;
                        switch (D_80113458_motor_rooter) {
                            case 0:
                            case 1:
                                if (itemDifference < 3) {
                                    D_800CBB6E_main[player->controllerPort] = 50;
                                } else {
                                    if (itemDifference < 4) {
                                        (void)rand16();
                                    }
                                    D_800CBB6E_main[player->controllerPort] = -50;
                                }
                                if (!(rand16() % (ctx->work.s8[6] + 1))) {
                                    D_800CBB6E_main[player->controllerPort] *= -1;
                                }
                                break;
                            case 2:
                                if (itemDifference < 3) {
                                    ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x8000;
                                } else {
                                    if (itemDifference < 4) {
                                        (void)rand16();
                                    }
                                    ((u16 *)D_800CDA7C_main)[player->controllerPort] = 0x4000;
                                }
                                if (!(rand16() % (ctx->work.s8[6] + 1))) {
                                    D_800CDA7C_main[player->controllerPort] = ~D_800CDA7C_main[player->controllerPort];
                                    D_800CDA7C_main[player->controllerPort] &= 0xC000;
                                }
                                break;
                        }
                    } else {
                        ctx->work.s8[1]++;
                    }
                }
            }
        }
    }
}

void func_8010ABC4_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;

    if (player->unk08 & 0x13) {
        return;
    }
    switch (D_80113458_motor_rooter) {
        case 0:
        case 1:
            if (D_800CBB6E_main[player->controllerPort] > 10) {
                if (!ctx->work.s8[0]) {
                    if (D_80113458_motor_rooter == 0) {
                        ctx->work.s8[0] = 1;
                    }
                    ctx->work.s8[1] = 0;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 4;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                    } else {
                        ctx->work.s8[2] = 4;
                    }
                }
            } else if (D_800CBB6E_main[player->controllerPort] < -10) {
                if (!ctx->work.s8[1]) {
                    ctx->work.s8[0] = 0;
                    if (D_80113458_motor_rooter == 0) {
                        ctx->work.s8[1] = 1;
                    }
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 8;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                    } else {
                        ctx->work.s8[2] = 8;
                    }
                }
            } else {
                ctx->work.s8[0] = ctx->work.s8[1] = 0;
            }
            break;
        case 2:
            if ((u16)D_800CDA7C_main[player->controllerPort] & A_BUTTON) {
                if (!ctx->work.s8[0]) {
                    ctx->work.s8[0] = 1;
                    ctx->work.s8[1] = 0;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 4;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                    } else {
                        ctx->work.s8[2] = 4;
                    }
                }
            } else if (D_800CDA7C_main[player->controllerPort] & B_BUTTON) {
                if (!ctx->work.s8[1]) {
                    ctx->work.s8[0] = 0;
                    ctx->work.s8[1] = 1;
                    if (!(player->unk08 & 0xC)) {
                        player->unk08 |= 8;
                        m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                    } else {
                        ctx->work.s8[2] = 8;
                    }
                }
            } else {
                ctx->work.s8[0] = ctx->work.s8[1] = 0;
            }
            break;
    }
    if (D_80113458_motor_rooter != 1 && !(GwPlayer[m254_playerId[object->work[0]]].stat & PLAYER_IS_CPU) &&
        !(player->unk08 & 0xC)) {
        switch (ctx->work.s8[2]) {
            case 4:
                player->unk08 |= 4;
                m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 0);
                break;
            case 8:
                player->unk08 |= 8;
                m254_SetFunc((u8)object->work[0] + 4, 4, -1, player, func_8010B970_motor_rooter, 0, 1);
                break;
        }
        ctx->work.s8[2] = 0;
    }
}

void func_8010AF0C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    f32 bounce = 0.0f;
    s16 camera = object->work[0];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    f32 angle;

    if (player->unk08 & 0x80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        return;
    }
    if (player->unk08 == 0) {
        ctx->work.s16[1] = 1;
        ctx->state = 1;
    }
    player->unk0C += player->unk10;
    ctx->work.s16[0] = ctx->work.s16[0] + 2 < 361 ? ctx->work.s16[0] + 2 : 0;
    ctx->work.f32[0] = sindf(ctx->work.s16[0]) * 20.0 * 0.05;
    if (player->unk08 & 2) {
        f32 jitter = D_8011349C_motor_rooter[ctx->work.s8[0]];
        angle = jitter + player->turnAngle;
        ctx->work.s8[0]++;
        if (ctx->work.s8[0] >= 4) {
            func_8010BDE4_motor_rooter(player, 38, 0);
            ctx->work.s8[0] = 0;
            player->unk08 &= ~2;
        }
    } else {
        angle = player->turnAngle;
    }
    if (player->unk08 & 0x20) {
        bounce = sindf(player->unk48) * 30.0;
        player->unk48 += 10;
        if (player->unk48 >= 181) {
            player->unk48 = 0;
            player->unk08 &= ~0x20;
        }
    }
    player->motion.x = ctx->work.f32[0];
    player->motion.y = angle;
    player->motion.z = bounce;
    player->motionCopy.x = ctx->work.f32[0];
    player->motionCopy.y = angle;
    player->motionCopy.z = bounce;
    offset.x = sindf(angle) * (ctx->work.f32[0] + 55.9999990463256836);
    offset.y = -cosdf(angle) * (ctx->work.f32[0] + 55.9999990463256836);
    offset.z = -120.0 - bounce;
    m254_MakeRotXMtx(rotX, CRotM[camera].x);
    m254_MakeRotYMtx(rotY, CRotM[camera].y);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    object->trans.x = CenterM[camera].x + position[0];
    object->trans.y = CenterM[camera].y + position[1];
    object->trans.z = CenterM[camera].z + position[2];
    if (player->unk08 & 0x400) {
        object->rot.x = CRotM[camera].x;
        m254_MakeIdentityMtx(Hu3DData[object->model[0]].mtx[0]);
        mtxRotCat(Hu3DData[object->model[0]].mtx, 0.0f, player->unk74, 0.0f);
        object->rot.y = 0.0f;
    } else {
        object->rot.x = 360.0f - CRotM[camera].x;
        if (!(player->unk08 & 1)) {
            object->rot.y = CRotM[camera].y + 180.0f;
        }
        m254_MakeIdentityMtx(Hu3DData[object->model[0]].mtx[0]);
        mtxRotCat(Hu3DData[object->model[0]].mtx, 0.0f, 0.0f, 360.0f - angle);
    }
}

void func_8010B394_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    HmfModel *model = &Hu3DData[object->model[9]];
    s16 camera = object->work[0];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    f32 angle;
    f32 bounce;

    if (player->unk08 & 0x80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        return;
    }
    if (!(player->unk08 & 0x200)) {
        offset.x = sindf(player->motionCopy.y) * (player->motionCopy.x + 55.9999990463256836);
        offset.y = -cosdf(player->motionCopy.y) * (player->motionCopy.x + 55.9999990463256836);
        offset.z = -120.0 - player->motionCopy.z;
        m254_MakeRotXMtx(rotX, CRotM[camera].x);
        m254_MakeRotYMtx(rotY, CRotM[camera].y);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        Hu3DData[object->model[9]].pos.x = CenterM[camera].x + position[0];
        Hu3DData[object->model[9]].pos.y = CenterM[camera].y + position[1];
        Hu3DData[object->model[9]].pos.z = CenterM[camera].z + position[2];
    } else {
        Hu3DModelPosSet(object->model[9], object->trans.x, object->trans.y + 0.0, object->trans.z);
    }
    Hu3DModelRotSet(object->model[9], object->rot.x, object->rot.y, object->rot.z);
    if (player->unk08 & 0x400) {
        m254_MakeIdentityMtx(model->mtx[0]);
        mtxRotCat(model->mtx, 0.0f, player->unk74, 0.0f);
        model->rot.y = model->rot.z = 0.0f;
    } else {
        m254_MakeIdentityMtx(model->mtx[0]);
        mtxRotCat(model->mtx, 0.0f, 0.0f, 360.0f - player->turnAngle);
    }
    if (!(player->unk08 & 0x200)) {
        angle = player->motion.y;
        bounce = player->motion.z;
        offset.x = sindf(angle) * (player->motion.x + 65.9999990463256836);
        offset.y = -cosdf(angle) * (player->motion.x + 65.9999990463256836);
        offset.z = -120.0 - bounce;
        m254_MakeRotXMtx(rotX, CRotM[camera].x);
        m254_MakeRotYMtx(rotY, CRotM[camera].y);
        m254_MultiplyMtx(rotX, rotY, transform);
        func_801114B0_motor_rooter(transform, &offset, position);
        Hu3DData[object->model[10]].pos.x = CenterM[camera].x + position[0];
        Hu3DData[object->model[10]].pos.y = CenterM[camera].y + position[1];
        Hu3DData[object->model[10]].pos.z = CenterM[camera].z + position[2];
    } else {
        Hu3DModelAttrSet(object->model[10], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[10], object->trans.x, object->trans.y - 10.0 + 0.0, object->trans.z);
    }
    if (player->unk08 & 0x400) {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, 0.0f);
        m254_MakeIdentityMtx(Hu3DData[object->model[10]].mtx[0]);
        mtxRotCat(Hu3DData[object->model[10]].mtx, 0.0f, player->unk74, 0.0f);
    } else {
        Hu3DModelRotSet(object->model[10], object->rot.x, object->rot.y, object->rot.z);
        m254_MakeIdentityMtx(Hu3DData[object->model[10]].mtx[0]);
        mtxRotCat(Hu3DData[object->model[10]].mtx, 0.0f, 0.0f, 360.0f - player->turnAngle);
    }
}

void func_8010B970_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;

    if (player->unk08 & 2) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            if (player->unk08 & 4) {
                ctx->work.f32[0] = player->turnAngle;
                ctx->work.f32[1] = player->turnAngle + 45.0f;
                player->direction = player->direction + 1 < 8 ? player->direction + 1 : 0;
            } else {
                player->direction = player->direction - 1 >= 0 ? player->direction - 1 : 7;
                ctx->work.f32[0] = player->turnAngle;
                ctx->work.f32[1] = player->turnAngle - 45.0f;
            }
            ctx->state = 1;
            break;
        case 1:
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[0]) * sindf(ctx->work.s8[0] / 4.0f * 90.0f) + ctx->work.f32[0];
            if (player->turnAngle > 360.0f) {
                player->turnAngle -= 360.0f;
            }
            if (player->turnAngle < 0.0f) {
                player->turnAngle += 360.0f;
            }
            if (++ctx->work.s8[0] > 4.0f) {
                player->unk08 &= ~0xC;
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010BB78_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;

    if (player->unk08 & 0x11) {
        return;
    }
    if (player->unk08 & 0x100) {
        if (player->unk10 < 20.0f) {
            player->unk10 *= 2.0f;
            if (player->unk10 > 20.0f) {
                player->unk10 = 20.0f;
            }
        } else {
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345C_motor_rooter[player->unk14 - 1]);
            player->unk08 &= ~0x100;
        }
    } else {
        player->unk4C++;
        if (player->unk4C > D_801134A0_motor_rooter[player->unk14 - 1]) {
            player->unk4C = 0;
            if (player->unk14 - 1 > 0) {
                player->unk14--;
                player->unk28[player->unk14] = 2;
                player->unk10 -= 4.0f;
            }
            HuAudFXVolSet(D_801137D8_motor_rooter, 64);
            HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345C_motor_rooter[player->unk14 - 1]);
        }
    }
}

void func_8010BCD0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player;
    omObjData *object;
    HmfModel *model;

    player = ctx->data;
    object = player->unk00;
    model = &Hu3DData[object->model[0]];
    if (model->motTime >= D_800CCF58_main[model->motId].unk02 - 1) {
        player->animChange = 1;
    }
    if (player->animChange) {
        func_800E5690_minigame(object, player->nextAnim);
        player->animChange = 0;
        if (player->nextAnim == 13) {
            HuAudCharVoicePlayPlayer(D_800A178C_main[GwPlayer[m254_playerId[object->work[0]]].chr][0] | 0x2F, -1, 0);
        }
    }
}

void func_8010BDE4_motor_rooter(D_801137C8_motor_rooter_Struct *player, s16 anim, s8 change) {
    player->animChange = change;
    player->nextAnim = anim;
}

void func_8010BDF0_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    f32 t;

    if (ctx->state == 0) {
        ctx->work.s8[0] = 0;
        ctx->work.s16[0] = 0;
        ctx->work.f32[0] = -120.0f;
        ctx->work.f32[1] = 40.0f;
        ctx->state = 1;
        player->unk08 |= 0x200;
        D_801137D8_motor_rooter = _HuAudPlayerFXPlay(0x4AF, player->unk00->work[0]);
        HuAudFXVolSet(D_801137D8_motor_rooter, 64);
        HuAudFXPitchSet(D_801137D8_motor_rooter, D_8011345C_motor_rooter[player->unk14 - 1]);
        m254_SetFunc((u8)object->work[0] + 4, 8, -1, &D_801137C8_motor_rooter[object->work[0]],
                     func_8010B394_motor_rooter, 0, 0);
    }
    t = ctx->work.s8[0];
    t = sindf(t / 80.0f) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    ctx->work.s16[0] = ctx->work.s16[0] + 2 < 361 ? ctx->work.s16[0] + 2 : 0;
    ctx->work.f32[2] = sindf(ctx->work.s16[0]) * 20.0 * 0.05;
    object->trans.z = (ctx->work.f32[0] - ctx->work.f32[1]) * t + ctx->work.f32[1];
    object->trans.y = ctx->work.f32[2] + -55.9999990463256836;
    if (++ctx->work.s8[0] > 80) {
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
        m254_SetFunc((u8)object->work[0] + 4, 7, -1, player, func_8010AF0C_motor_rooter, 0, 0)->work.s16[0] = ctx->work.s16[0];
        player->unk08 &= ~0x200;
    }
}

void func_8010C084_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 camera = object->work[0];
    s16 i;
    f32 t;

    if (player->unk08 & 0xC) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[2] = 0;
            ctx->work.s16[0] = 1;
            ctx->work.f32[3] = object->rot.y;
            player->rotationStart = CRotM[camera].y + 90.0f;
            if (ctx->work.f32[3] > 360.0f) {
                ctx->work.f32[3] -= 360.0f;
            }
            if (ctx->work.f32[3] < 0.0f) {
                ctx->work.f32[3] += 360.0f;
            }
            if (player->rotationStart - ctx->work.f32[3] > 180.0f) {
                player->rotationStart -= 360.0f;
            }
            ctx->work.f32[2] = player->turnAngle;
            if (player->turnAngle > 180.0f) {
                ctx->work.f32[1] = 360.0f;
            } else {
                ctx->work.f32[1] = 0;
            }
            ctx->work.f32[0] = player->unk10 / 40.0f;
            ctx->state = 1;
            player->unk08 |= 1;
            break;
        case 1:
            t = ctx->work.s8[2] / 15.0f;
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[2]) * t + ctx->work.f32[2];
            if (++ctx->work.s8[2] > 15) {
                HuAudFXAllFadeOut(120);
                ctx->state = 2;
                player->unk78 |= 4;
                for (i = 0; i < 4; i++) {
                    m254_minigame->runtime.counters.gameplay.playerCounters[camera * 4 + i] = 0;
                }
            }
            break;
        case 2:
            object->rot.y = (player->rotationStart - ctx->work.f32[3]) * sindf(ctx->work.s16[0]) + ctx->work.f32[3];
            if ((ctx->work.s16[0] *= 2.0f) > 90) {
                ctx->work.s16[0] = 90;
            }
            player->unk10 -= ctx->work.f32[0];
            if (++ctx->work.s16[5] > 6) {
                ctx->work.s16[5] = 0;
                if (player->unk14 - 1 >= 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                }
            }
            if (player->unk10 < 0.0f) {
                player->unk10 = 0;
                player->unk08 |= 0x80;
                m254_SetFunc((u8)object->work[0] + 4, 5, -1, player, func_8010C44C_motor_rooter, 0, 0);
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010C44C_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    PathPosition position;
    f32 t;

    if (ctx->state == 0) {
        position = func_8010D0AC_motor_rooter(func_8010D03C_motor_rooter(player->unk0C + 60.0),
                                              player->unk0C + 60.0);
        ctx->work.f32[0] = position.x;
        ctx->work.f32[1] = position.y;
        ctx->work.f32[2] = position.z;
        ctx->work.f32[3] = CRotM[object->work[0]].y;
        if (ctx->work.f32[3] <= -360.0f) {
            ctx->work.f32[3] += 360.0f;
        }
        player->cameraStart.x = object->trans.x;
        player->cameraStart.y = object->trans.y;
        player->cameraStart.z = object->trans.z;
        player->rotationStart = object->rot.y;
        ctx->work.s8[0] = ctx->work.s8[1] = ctx->work.s8[2] = 0;
        func_8010BDE4_motor_rooter(player, 6, 1);
        CharFXPlay(0x3A, GwPlayer[m254_playerId[object->work[0]]].chr);
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        ctx->state = 1;
    }
    t = ctx->work.s8[0] / 30.0f;
    t = sindf(t) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    object->trans.x = (ctx->work.f32[0] - player->cameraStart.x) * t + player->cameraStart.x;
    object->trans.z = (ctx->work.f32[2] - player->cameraStart.z) * t + player->cameraStart.z;
    object->trans.y = m254_CalcQuadraticBezier(t, player->cameraStart.y,
                                               player->cameraStart.y + 60.0, player->cameraStart.y);
    Hu3DModelPosSet(object->model[1], object->trans.x, player->cameraStart.y, object->trans.z);
    t = ctx->work.s8[1] / 10.0f;
    t = sindf(t) * 90.0f;
    t = t > 1.0f ? 1.0f : t;
    object->rot.y = (ctx->work.f32[3] - player->rotationStart) * t + player->rotationStart;
    if (++ctx->work.s8[0] > 30) {
        m254_SetFunc(FGRP_CAMERA, 0, -1, player, func_80108514_motor_rooter, 0, 0);
        m254_ResetFunc((u8)object->work[0] + 4, ctx);
    }
    if (++ctx->work.s8[1] > 10) {
        ctx->work.s8[1] = 10;
    }
    if (ctx->work.s8[0] > 20) {
        if (ctx->work.s8[2] == 0) {
            ctx->work.s8[2] = 1;
            func_8010BDE4_motor_rooter(player, 21, 1);
            CharFXPlay(0x31, GwPlayer[m254_playerId[object->work[0]]].chr);
        } else if (ctx->work.s8[2] == 1) {
            ctx->work.s8[2] = 2;
            func_8010BDE4_motor_rooter(player, 0, 0);
        }
    }
}

void func_8010C824_motor_rooter(FuncContext *ctx) {
    D_801137C8_motor_rooter_Struct *player = ctx->data;
    omObjData *object = player->unk00;
    s16 i;
    f32 t;

    if (player->unk08 & 0xC) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->work.s8[2] = 0;
            ctx->work.s16[0] = 1;
            ctx->work.f32[3] = object->rot.y;
            ctx->work.f32[2] = player->turnAngle;
            if (player->turnAngle > 180.0f) {
                ctx->work.f32[1] = 360.0f;
            } else {
                ctx->work.f32[1] = 0;
            }
            ctx->work.f32[0] = player->unk10 / 60.0f;
            ctx->state = 1;
            player->unk08 |= 1;
            break;
        case 1:
            t = ctx->work.s8[2] / 15.0f;
            player->turnAngle = (ctx->work.f32[1] - ctx->work.f32[2]) * t + ctx->work.f32[2];
            if (++ctx->work.s8[2] > 15) {
                player->unk74 = object->rot.y;
                player->unk08 |= 0x400;
                ctx->state = 2;
                player->unk78 |= 4;
                for (i = 0; i < 4; i++) {
                    m254_minigame->runtime.counters.gameplay.playerCounters[object->work[0] * 4 + i] = 0;
                }
            }
            break;
        case 2:
            player->unk74 = (ctx->work.f32[3] + 1080.0f - ctx->work.f32[3]) * sindf(ctx->work.s16[0]) + ctx->work.f32[3];
            if (player->unk74 > 360.0f) {
                player->unk74 -= 360.0f;
            }
            if ((ctx->work.s16[0] += 1.0f) > 90) {
                ctx->work.s16[0] = 90;
            }
            player->unk10 -= ctx->work.f32[0];
            if (++ctx->work.s16[5] > 10) {
                ctx->work.s16[5] = 0;
                if (player->unk14 - 1 >= 0) {
                    player->unk14--;
                    player->unk28[player->unk14] = 2;
                }
            }
            if (player->unk10 < 0.0f) {
                player->unk10 = 0;
                func_8010BDE4_motor_rooter(player, 0, 1);
                m254_ResetFunc((u8)object->work[0] + 4, ctx);
            }
            break;
    }
}

void func_8010CB2C_motor_rooter(omObjData *object, s16 item, s16 modelIndex) {
    D_801137C8_motor_rooter_Struct *player = &D_801137C8_motor_rooter[object->work[0]];
    f32 jitter = 0.0f;
    s16 camera = object->work[0];
    s16 modelId = object->model[modelIndex];
    f32 rotX[16];
    f32 rotY[16];
    f32 transform[16];
    Vec offset;
    f32 position[3];
    HmfModel *model;
    f32 angle;

    if (item == 4) {
        jitter = rand16() % 31 - 15;
    }
    model = &Hu3DData[modelId];
    angle = jitter + player->turnAngle;
    offset.x = sindf(angle) * 55.9999990463256836;
    offset.y = -cosdf(angle) * 55.9999990463256836;
    offset.z = -100.0f;
    m254_MakeRotXMtx(rotX, CRotM[camera].x);
    m254_MakeRotYMtx(rotY, CRotM[camera].y);
    m254_MultiplyMtx(rotX, rotY, transform);
    func_801114B0_motor_rooter(transform, &offset, position);
    model->pos.x = CenterM[camera].x + position[0];
    model->pos.y = CenterM[camera].y + position[1];
    model->pos.z = CenterM[camera].z + position[2];
    model->rot.x = CRotM[camera].x;
    model->rot.y = CRotM[camera].y;
    m254_MakeIdentityMtx(model->mtx[0]);
    mtxRotCat(model->mtx, 0.0f, 0.0f, angle);
}

void func_8010CD84_motor_rooter(Vec *positions, s16 count) {
    PathPoint *point;
    f32 angles[3];
    f32 distance;
    f32 finishDistance;
    f32 dx, dy, dz;
    s16 i;

    D_801137C0_motor_rooter = HuMemAllocTag(count * sizeof(PathPoint), TAG_OVERLAY);
    point = D_801137C0_motor_rooter;
    finishDistance = distance = 0.0f;
    for (i = 0; i < count - 1; i++, point++) {
        dx = positions[i + 1].x - positions[i].x;
        dy = positions[i + 1].y - positions[i].y;
        dz = positions[i + 1].z - positions[i].z;
        point->segLen = point->invSegLen = sqrtf(dx * dx + dy * dy + dz * dz);
        point->cumDist = distance;
        distance += point->segLen;
        if (i <= D_801137CC_motor_rooter) {
            finishDistance += point->segLen;
        }
        if (point->invSegLen != 0.0f) {
            point->invSegLen = 1.0f / point->invSegLen;
        } else {
            point->invSegLen = 0.0f;
        }
        point->x = positions[i].x;
        point->y = positions[i].y;
        point->z = positions[i].z;
        m254_CalcPitchAndYaw(positions[i], positions[i + 1], angles);
        point->pitch = angles[0] + 180.0f;
        point->yaw = angles[1] - 180.0f;
        point->unk14 = 0.0f;
        while (point->pitch >= 360.0f) {
            point->pitch -= 360.0f;
        }
    }
    point->segLen = -1.0f;
    point->cumDist = distance;
    point->x = positions[i].x;
    point->y = positions[i].y;
    point->z = positions[i].z;
    m254_minigame->totalDistance = distance;
    m254_minigame->finishDistance = finishDistance;
    m254_minigame->pathPointCount = count;
    m254_minigame->unk0E = 60;
}

s16 func_8010D03C_motor_rooter(f32 dist) {
    s16 i;
    PathPoint *point;

    point = &D_801137C0_motor_rooter[m254_minigame->pathPointCount - 1];
    for (i = m254_minigame->pathPointCount; i > 0; i--, point--) {
        if (point->cumDist <= dist) {
            break;
        }
    }
    return i - 1;
}

PathPosition func_8010D0AC_motor_rooter(s16 index, f32 dist) {
    PathPosition position;
    PathPoint *point;
    f32 fraction;
    f32 start;
    f32 end;

    point = &D_801137C0_motor_rooter[index];
    fraction = dist - point->cumDist;
    fraction *= point->invSegLen;
    end = point[1].x;
    start = point->x;
    position.x = (end - start) * fraction + start;
    end = point[1].y;
    start = point->y;
    position.y = (end - start) * fraction + start;
    end = point[1].z;
    start = point->z;
    position.z = (end - start) * fraction + start;
    end = point[1].pitch;
    start = point->pitch;
    position.pitch = (end - start) * fraction + start;
    end = point[1].yaw;
    start = point->yaw;
    position.yaw = (end - start) * fraction + start;
    position.roll = 0;
    return position;
}

void func_8010D1A8_motor_rooter(s16 point, s16 direction) {
    s16 index = D_801137D2_motor_rooter;

    if (point >= D_801137CC_motor_rooter) {
        return;
    }
    if (index >= 10) {
        return;
    }
    m254_minigame->views[0].obstaclePoints[index] = m254_minigame->views[1].obstaclePoints[index] = point;
    direction += 4;
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->views[0].obstacleDirections[index] = m254_minigame->views[1].obstacleDirections[index] = direction;
    m254_minigame->views[0].obstacleTypes[index] = m254_minigame->views[1].obstacleTypes[index] = (rand16() % 3) + 1;
    D_801137D2_motor_rooter++;
}

void func_8010D2E4_motor_rooter(s32 arg0) {
    s16 directions[8];
    s16 obstacleSections[10];
    s16 j, k;
    s16 point, direction, count, sectionLength, section, preferredDirection, step, chance;

    for (step = 0; step < 10; step++) {
        obstacleSections[step] = 0;
    }
    sectionLength = (D_801137CC_motor_rooter - 10) / 10;
    direction = 0;
    point = 5;
    while (1) {
        if (point >= D_801137CC_motor_rooter || D_801137D0_motor_rooter >= 100) {
            break;
        }
        preferredDirection = -1;
        switch ((s16)(rand16() % 14)) {
            case 0:
            case 1:
                direction = rand16() % 8;
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 2) {
                    func_8010DC3C_motor_rooter(point, direction);
                }
                preferredDirection = direction + 4;
                chance = 70;
                break;
            case 2:
            case 3:
            case 4:
                direction = rand16() % 8;
                count = rand16() % 2 + 3;
                for (j = 0; j < count; j++, point += 6) {
                    func_8010DC3C_motor_rooter(point, direction);
                    direction += rand16() % 2 ? -1 : 1;
                }
                chance = 25;
                break;
            case 5:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 8) {
                    direction = rand16() % 8;
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                }
                preferredDirection = direction;
                chance = 25;
                break;
            case 6:
            case 7:
                direction = rand16() % 8;
                step = rand16() % 2 ? -1 : 1;
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 7) {
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                    direction += step;
                }
                preferredDirection = direction;
                chance = 25;
                break;
            case 8:
                count = rand16() % 2 + 1;
                for (j = 0; j < count; j++, point += 9) {
                    m254_MakeRandPermutation(directions, 8);
                    for (k = 0; k < 3; k++) {
                        func_8010DC3C_motor_rooter(point, directions[k]);
                    }
                }
                chance = 50;
                break;
            case 9:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 7) {
                    direction = rand16() % 8;
                    for (k = 0; k < 3; k++, direction += 3) {
                        func_8010DC3C_motor_rooter(point, direction);
                    }
                }
                chance = 50;
                break;
            case 10:
                direction = rand16() % 8;
                count = rand16() % 2 + 1;
                func_8010DC3C_motor_rooter(point, direction);
                point += 2;
                for (j = 0; j < count; j++, point += 2) {
                    for (k = 0; k < 2; k++) {
                        func_8010DC3C_motor_rooter(point, direction + k * 4);
                    }
                }
                preferredDirection = direction + 4;
                chance = 100;
                break;
            default:
                count = rand16() % 2 + 2;
                for (j = 0; j < count; j++, point += 9) {
                    direction = rand16() % 8;
                    func_8010DC3C_motor_rooter(point, direction);
                }
                chance = 50;
                break;
        }
        obstacleSections[0] = 1;
        section = (point - 10) / sectionLength;
        if (rand16() % 101 < chance && obstacleSections[section] == 0) {
            if (preferredDirection == -1) {
                direction = rand16() % 8;
            } else {
                direction = preferredDirection;
            }
            obstacleSections[section]++;
            step = 0;
            if (D_801137D2_motor_rooter > 0 &&
                point - m254_minigame->views[0].obstaclePoints[D_801137D2_motor_rooter - 1] < 5) {
                func_8010D1A8_motor_rooter(point,
                                           m254_minigame->views[0].obstacleDirections[D_801137D2_motor_rooter - 1] + 2);
            } else {
                func_8010D1A8_motor_rooter(point - step, direction);
            }
            for (j = 0; j < section; j++) {
                if (obstacleSections[j] == 0) {
                    obstacleSections[section] = 0;
                    obstacleSections[j]++;
                }
            }
            point += 4 + rand16() % 5;
        }
    }
}

void func_8010DC3C_motor_rooter(s16 point, s16 direction) {
    if (point >= D_801137CC_motor_rooter || D_801137D0_motor_rooter >= 100) {
        return;
    }
    if (D_801137D0_motor_rooter >= 16 &&
        point - m254_minigame->itemPoints[D_801137D0_motor_rooter - 15] < m254_minigame->unk0E) {
        return;
    }
    while (direction < 0) {
        direction += 8;
    }
    while (direction >= 8) {
        direction -= 8;
    }
    m254_minigame->itemPoints[D_801137D0_motor_rooter] = point;
    m254_minigame->itemDirections[D_801137D0_motor_rooter++] = direction;
}

void func_8010DD10_motor_rooter(FuncContext *ctx) {
    ctx->work.s8[0]++;
    if (ctx->work.s8[0] >= 6) {
        ctx->work.s8[0] = 0;
        if (D_800CDA7C_main[0] & Z_TRIG) {
            D_80113458_motor_rooter = D_80113458_motor_rooter + 1 < 3 ? D_80113458_motor_rooter + 1 : 0;
        }
    }
    sprintf(D_800D5218_main, "CONT TYPE %d", D_80113458_motor_rooter);
    print8(16, 80, D_800D5218_main);
}
