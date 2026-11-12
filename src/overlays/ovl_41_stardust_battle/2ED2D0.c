#include "common.h"
#include "overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/printfunc.h"

#define CAMERA_KEEP 65535.0f
#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct UnkStardustBattleStard {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 modelId;
    /* 0x04 */ s16 angleX;
    /* 0x06 */ s16 angleY;
    /* 0x08 */ f32 x;
    /* 0x0C */ f32 y;
    /* 0x10 */ f32 z;
    /* 0x14 */ f32 radius;
    /* 0x18 */ f32 radius2;
    /* 0x1C */ f32 worldX;
    /* 0x20 */ f32 worldY;
    /* 0x24 */ f32 worldZ;
} UnkStardustBattleStard; // sizeof 0x28

typedef union StardustBattleWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} StardustBattleWorkBytes;

/* Work data of the D_80114B18_stardust_battle object, retrieved with
   func_80111FEC_stardust_battle. */
typedef struct UnkStardustBattleActor {
    /* 0x00 */ s16 active;
    /* 0x02 */ char unk_02[0x02];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk_06[0x12];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ s16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ f32 velX;
    /* 0x2C */ f32 velY;
    /* 0x30 */ f32 velZ;
    /* 0x34 */ Vec target;
    /* 0x40 */ Vec start;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
} UnkStardustBattleActor;

/* One entry of the stardust pool allocated by func_8010CB34_stardust_battle.
   The pool is indexed by UnkStardustBattleStars.count. */
typedef struct UnkStardustBattleStar {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 model[6];
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 state;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 x;
    /* 0x2C */ f32 y;
    /* 0x30 */ f32 z;
    /* 0x34 */ f32 targetX;
    /* 0x38 */ f32 targetY;
    /* 0x3C */ f32 targetZ;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ f32 unk_4C;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ f32 unk_78;
} UnkStardustBattleStar; // sizeof 0x7C

typedef struct UnkStardustBattleStars { // sizeof 0x10
    /* 0x00 */ s16 modelId1;
    /* 0x02 */ s16 modelId2;
    /* 0x04 */ s16 effectId1;
    /* 0x06 */ s16 effectId2;
    /* 0x08 */ s16 count;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ UnkStardustBattleStar *star;
} UnkStardustBattleStars;

typedef struct UnkStardustBattleScoreDisp {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 sprGrp;
    /* 0x04 */ s16 state;
    /* 0x06 */ s16 timer;
    /* 0x08 */ s16 x;
    /* 0x0A */ s16 y;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 scale;
} UnkStardustBattleScoreDisp; // sizeof 0x14

typedef struct UnkStardustBattleSpot {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 followPlayer;
    /* 0x04 */ Vec pos;
} UnkStardustBattleSpot; // sizeof 0x10

typedef struct UnkStardustBattleSpots {
    /* 0x00 */ s16 count;
    /* 0x02 */ s16 max;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ UnkStardustBattleSpot *spot;
} UnkStardustBattleSpots; // sizeof 0xC

typedef struct UnkStardustBattleStreak {
    /* 0x00 */ u8 active;
    /* 0x01 */ u8 index;
    /* 0x04 */ f32 x;
    /* 0x08 */ f32 y;
    /* 0x0C */ f32 z;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
} UnkStardustBattleStreak; // sizeof 0x3C

typedef union UnkStardustBattleColor {
    u32 word;
    u8 rgba[4];
} UnkStardustBattleColor;

typedef struct UnkStardustBattleEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ UnkStardustBattleColor color;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec vel;
    /* 0x28 */ Vec scale;
} UnkStardustBattleEffect; // sizeof 0x34

typedef struct UnkStardustBattleCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
} UnkStardustBattleCamera; // sizeof 0x24

typedef struct UnkStardustBattlePoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ char unk_06[0x26];
} UnkStardustBattlePoint; // sizeof 0x2C

typedef struct UnkStardustBattleNearPoint {
    /* 0x00 */ f32 distSq;
    /* 0x04 */ s32 index;
} UnkStardustBattleNearPoint; // sizeof 0x8

typedef struct UnkStardustBattleStarDist {
    /* 0x00 */ s32 index;
    /* 0x04 */ f32 distSq;
} UnkStardustBattleStarDist; // sizeof 0x8

/* Extended form of HmfModelData_Unk64_Unk3C_Struct allocated by
   func_801122D0_stardust_battle, with a third display list. */
typedef struct UnkStardustBattleGfxData {
    /* 0x00 */ Gfx *unk00[4];
    /* 0x10 */ void *unk10;
    /* 0x14 */ void *unk14;
    /* 0x18 */ void *unk18;
} UnkStardustBattleGfxData; // sizeof 0x1C

/* Work data of the object created by func_80108B34_stardust_battle. */
typedef struct UnkStardustBattleStage {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x24 */ UnkStardustBattlePoint *unk_24;
    /* 0x28 */ UnkStardustBattleStreak *streaks;
    /* 0x2C */ s16 unk_2C;
    /* 0x30 */ void (*func_30)(omObjData *);
    /* 0x34 */ void (*func_34)(omObjData *);
} UnkStardustBattleStage; // sizeof 0x38

/* Work data of the player object, packed into omObjData.work and retrieved
   with func_80111FEC_stardust_battle. */
typedef struct UnkStardustBattleObj {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ char unk_02[0x02];
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ char unk_06[0x04];
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ char unk_10[0x02];
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ char unk_14[0x04];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 pad;
    /* 0x24 */ s16 character;
    /* 0x26 */ char unk_26[0x06];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ char unk_3E[0x2E];
    /* 0x6C */ void (*func_6C)(omObjData *);
    /* 0x70 */ void (*func_70)(omObjData *);
    /* 0x74 */ void (*func_74)(omObjData *);
    /* 0x78 */ void (*func_78)(omObjData *);
} UnkStardustBattleObj; // sizeof 0x7C

extern omObjData *D_80114B58_stardust_battle;
extern omObjData *D_80114B18_stardust_battle;
extern UnkStardustBattleStard *D_80114B5C_stardust_battle;
extern UnkStardustBattleStars *D_80114B2C_stardust_battle;
extern UnkStardustBattleScoreDisp *D_80114B44_stardust_battle;
extern u8 D_800D2008_main;
extern s16 D_80114B54_stardust_battle;
extern UnkStardustBattleStage *D_80114B10_stardust_battle;
extern UnkStardustBattleSpots *D_80114B20_stardust_battle;
extern Vec D_80113EB8_stardust_battle;
extern omObjData *D_80114B50_stardust_battle;
extern u8 D_80114B38_stardust_battle[2][6];
extern s32 D_800A178C_main[][6];
extern s32 D_80113DE4_stardust_battle;
extern s16 D_80113DE6_stardust_battle[];
extern void (*D_80113E24_stardust_battle[])(omObjData *);
extern void (*D_80113E30_stardust_battle[])(omObjData *);
extern void (*D_80113E3C_stardust_battle[])(omObjData *);
extern void (*D_80113E48_stardust_battle[])(omObjData *);
extern s32 D_80113E54_stardust_battle[];
extern s32 D_80113E60_stardust_battle[];
extern s32 D_80113E6C_stardust_battle[];
extern void (*D_80113E78_stardust_battle[])(omObjData *);
extern void (*D_80113E84_stardust_battle[])(omObjData *);
extern s32 D_80113EF0_stardust_battle[];
extern s32 D_80113EFC_stardust_battle[];
extern s32 D_80114AA0_stardust_battle;
extern s32 D_80114AA4_stardust_battle;
extern s32 D_80114AA8_stardust_battle;
extern s32 D_80114AC0_stardust_battle;
extern s32 D_80114AC4_stardust_battle;
extern s16 D_80114ACC_stardust_battle;
extern s16 D_80114ACE_stardust_battle;
extern HuMtx4F D_80114AD0_stardust_battle;
extern UnkStardustBattleActor *D_80114B1C_stardust_battle;
extern s32 D_80114B24_stardust_battle;
extern s16 *D_80114B28_stardust_battle;
extern s16 D_80113DBC_stardust_battle[];
extern s16 D_80113DC4_stardust_battle[];
extern s16 D_80113DCC_stardust_battle[];
extern omObjData *D_80114A98_stardust_battle;
extern s32 D_80114A9C_stardust_battle;
extern UnkStardustBattleStarDist D_80114A40_stardust_battle[10];
extern UnkStardustBattleStarDist D_80114A90_stardust_battle;
extern omObjData *D_80114B34_stardust_battle;
extern s16 D_80113CE0_stardust_battle[];
extern s16 D_80113CF0_stardust_battle[];
extern s32 D_80113ED0_stardust_battle[];
extern s32 D_80113ED8_stardust_battle[];
extern UnkStardustBattleNearPoint D_80114940_stardust_battle[32];
extern s16 D_800CD1B0_main;
extern s16 *D_800D04B4_main;
extern HuMtx4F *D_800D1358_main;
extern s16 D_800D138A_main;
extern HuMtx4F D_800D5A00_main[];
extern s32 D_80113DEC_stardust_battle[];
extern Vec D_80113CB0_stardust_battle[];
extern u8 D_800D6A90_main;
extern D_80111B50_vine_with_me_Struct D_80114BB8_stardust_battle;
extern s32 D_80114AAC_stardust_battle;
extern s32 D_80114AB0_stardust_battle;
extern s32 D_80114AB4_stardust_battle;
extern u8 D_80113DE8_stardust_battle;
extern s16 D_80114B14_stardust_battle;
extern s16 *D_80114B30_stardust_battle;
extern omObjData *D_80114B48_stardust_battle;
extern UnkStardustBattleEffect *D_80114B4C_stardust_battle;
extern UnkStardustBattleColor D_80113CF4_stardust_battle;
extern UnkStardustBattleCamera D_80114B60_stardust_battle[2]; // target, origin
extern s32 D_80114BA8_stardust_battle;
extern s32 D_80114BAC_stardust_battle;
extern Gfx D_80114020_stardust_battle[];
extern s16 D_800CDD6A_main;
extern s32 D_80113F08_stardust_battle;
extern s32 D_80113F0C_stardust_battle;
extern s32 D_80113F10_stardust_battle;
extern f32 D_80113F14_stardust_battle[];
extern s32 D_80114BB0_stardust_battle;
extern s32 D_80114BB4_stardust_battle;
extern s32 D_80114AB8_stardust_battle;
extern s32 D_80114ABC_stardust_battle;
extern UnkStardustBattleObj *D_80114AC8_stardust_battle;

const s16 D_80114100_stardust_battle[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000
};

const s16 D_8011410C_stardust_battle[] = {
    0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000
};

/* Call sites pass only the object and use the result as a pointer, so this
   can't use the definition's full prototype. */
u32 func_80111FEC_stardust_battle(); // Unprototyped: called with varying argument counts.
void func_80108120_stardust_battle(omObjData *object);
void func_80108C14_stardust_battle(omObjData *object);
void func_80108D84_stardust_battle(omObjData *object);
void func_80108EC4_stardust_battle(s16 model, f32 u, f32 v, s32 width, s32 height, s16 index);
void func_80109128_stardust_battle(s16 mode);
void func_80107DCC_stardust_battle(omObjData *object, s16 mode);
void func_8010FBCC_stardust_battle(omObjData *object);
void func_8010C5A8_stardust_battle(s16 count, s16 arg1);
void func_80111FC0_stardust_battle(omObjData *arg0, u32 arg1);
void func_801081FC_stardust_battle(omObjData *object);
void func_801082C4_stardust_battle(omObjData *object);
void func_8010A690_stardust_battle(omObjData *object);
void func_8010A5A4_stardust_battle(omObjData *object);
void func_8010C1F8_stardust_battle(s16 motion, s16 startTime, s16 endTime, u8 attr);
void func_8010DF70_stardust_battle(s16 index);
f32 func_80111EB8_stardust_battle(f32 x, f32 y);
f32 func_80111B28_stardust_battle(f32 arg0, f32 arg1);
void func_801119D4_stardust_battle(s32 camIndex);
f32 func_80111DF8_stardust_battle(f32 t, f32 start, f32 end);
f32 func_80111E10_stardust_battle(f32 arg0, f32 arg1, f32 arg2);
void func_801117E4_stardust_battle(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
f32 func_80111C2C_stardust_battle(f32 target, f32 current, f32 step);
s32 func_8010A04C_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_8010C0C8_stardust_battle(void);
void func_8010C44C_stardust_battle(void);
void func_8010C498_stardust_battle(void);
s16 func_8010C508_stardust_battle(void);
void func_80105D18_stardust_battle(omObjData *object);
void func_80105DA0_stardust_battle(omObjData *object);
void func_80108B34_stardust_battle(void);
void func_8010F5E0_stardust_battle(void);
void func_8010FA60_stardust_battle(void);
void func_80106D0C_stardust_battle(void);
void func_80106EB0_stardust_battle(omObjData *object);
void func_8010A74C_stardust_battle(void);
void func_8010CB34_stardust_battle(void);
void func_8010CE5C_stardust_battle(omObjData *object);
void func_801107E4_stardust_battle(void);
void func_8010EE7C_stardust_battle(void);
void func_8010F0E8_stardust_battle(omObjData *object);
void func_801115F8_stardust_battle(s32 arg0);
void func_80111004_stardust_battle(omObjData *object);
void func_80107F34_stardust_battle(f32 step);
void func_8010F400_stardust_battle(s16 index, s32 frames);
void func_8010F580_stardust_battle(s16 index);
void func_8010F5B0_stardust_battle(s16 index);
void func_8010F73C_stardust_battle(omObjData *object);
u16 func_8010EE38_stardust_battle(s32 dirAndFile);
s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *sprite, u8 *color);
s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color);
s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);
void func_8011376C_stardust_battle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);

void func_801059A0_stardust_battle(void) {
    u8 camIndex;
    s32 level;

    func_8001FE20_main(50);
    omInitObjMan(50, 10);
    func_8004A208_main();
    func_800142A0_main(64);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_80114AB0_stardust_battle = 0;
    D_80114AA4_stardust_battle = 0;
    D_80114AA0_stardust_battle = 0;
    D_80114AA8_stardust_battle = 0;
    D_80114AAC_stardust_battle = 0;
    D_80114AB8_stardust_battle = -1;
    D_80114ABC_stardust_battle = 0;
    D_80114AC0_stardust_battle = 0;
    D_80114B14_stardust_battle = 1;
    D_80114B24_stardust_battle = 9;
    D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
    D_80114AC4_stardust_battle = 1;
    D_80114AC0_stardust_battle = _CheckFlag(0x1C);
    if (D_80114AC0_stardust_battle != 0) {
        D_80114AC0_stardust_battle = 1;
        D_80114AB4_stardust_battle = GWMgRecordGet(9);
        if (D_80114AB4_stardust_battle == 0) {
            D_80114AB4_stardust_battle = 4500;
        }
    }
    if ((GwSystem.playMode & 4) && !_CheckFlag(0x1C)) {
        level = GwStory.unk2;
    } else {
        level = 2;
    }
    switch (level) {
        case 0:
            D_80114B24_stardust_battle = 3;
            D_80114B28_stardust_battle = D_80113DCC_stardust_battle;
            break;
        case 1:
            D_80114B24_stardust_battle = 6;
            D_80114B28_stardust_battle = D_80113DC4_stardust_battle;
            break;
        default:
            D_80114B24_stardust_battle = 9;
            D_80114B28_stardust_battle = D_80113DBC_stardust_battle;
            break;
    }
    D_80114ACC_stardust_battle = -1;
    D_80114ACE_stardust_battle = 0;
    D_80114B30_stardust_battle = HuMemAllocTag(0x40, TAG_OVERLAY);
    D_80114AC8_stardust_battle = NULL;
    D_80114B10_stardust_battle = NULL;
    D_80114B18_stardust_battle = NULL;
    D_80114B1C_stardust_battle = NULL;
    D_80114B2C_stardust_battle = NULL;
    D_80114B58_stardust_battle = NULL;
    D_80114B5C_stardust_battle = NULL;
    guMtxIdentF(D_80114AD0_stardust_battle);
    D_80114A98_stardust_battle = omAddObj(0x20, 0, 0, -1, func_80105D18_stardust_battle);
    memset(&D_80114BB8_stardust_battle, 0, 0x28);
    D_80114BB8_stardust_battle.unk01 = 4;
    func_800E5EA0_minigame(&D_80114BB8_stardust_battle);
    func_80045010_main(D_80114100_stardust_battle, 1);
    func_80045010_main(D_8011410C_stardust_battle, 1);
}

void func_80105D18_stardust_battle(omObjData *object) {
    object->func = func_80105DA0_stardust_battle;
    func_80108B34_stardust_battle();
    func_8010F5E0_stardust_battle();
    func_8010FA60_stardust_battle();
    func_80106D0C_stardust_battle();
    func_8010A74C_stardust_battle();
    func_8010CB34_stardust_battle();
    func_801107E4_stardust_battle();
    func_8010EE7C_stardust_battle();
    D_80114B54_stardust_battle = func_8000D658_main(0x1CA9, 10);
    if (_CheckFlag(10)) {
        D_80114A9C_stardust_battle = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80105DA0_stardust_battle);

void func_801065B4_stardust_battle(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_801065D8_stardust_battle(omObjData *object) {
    if (D_80113DE4_stardust_battle != 0) {
        if (D_80113DE4_stardust_battle == 1) {
            object->func = func_801065B4_stardust_battle;
        }
        D_80113DE4_stardust_battle--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_80113DE4_stardust_battle = 16;
        WipeColorSet(0, 0, 0);
        WipeCreateOut(0, D_80113DE6_stardust_battle[0]);
        HuAudSeqFadeOut(D_80113DE6_stardust_battle[0]);
        func_8004AB0C_main(D_80113DE6_stardust_battle[0]);
    }
}

void func_80106690_stardust_battle(void) {
    switch (D_80114ABC_stardust_battle) {
        case 0:
            if (D_80114AB0_stardust_battle < D_80114AB4_stardust_battle) {
                D_80114ABC_stardust_battle = 2;
            } else if (func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80114ABC_stardust_battle = 16;
                D_80114AA4_stardust_battle = 0;
            }
            break;
        case 2:
            if (D_80113DE8_stardust_battle == 2) {
                if (func_8010C508_stardust_battle() == 12) {
                    func_8010C0C8_stardust_battle();
                    D_80113DE8_stardust_battle = 1;
                }
            } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80113DE8_stardust_battle = 0;
            }
            if (D_80114AA4_stardust_battle > 15.0f) {
                D_80114AB4_stardust_battle = D_80114AB0_stardust_battle;
                GWMgRecordSet(9, (u16)D_80114AB4_stardust_battle);
                func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
                func_8010F400_stardust_battle(1, D_80114AB4_stardust_battle);
                func_8010F580_stardust_battle(1);
                GMesCreate(0x1B);
                D_80114AAC_stardust_battle = 99;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 3:
            if (D_80113DE8_stardust_battle == 2) {
                if (func_8010C508_stardust_battle() == 12) {
                    func_8010C0C8_stardust_battle();
                    D_80113DE8_stardust_battle = 1;
                }
            } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80113DE8_stardust_battle = 0;
            }
            if (GMesStatGet() == 0) {
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 4:
            if (D_80113DE8_stardust_battle == 2) {
                if (func_8010C508_stardust_battle() == 12) {
                    func_8010C0C8_stardust_battle();
                    D_80113DE8_stardust_battle = 1;
                }
            } else if (D_80113DE8_stardust_battle == 1 && func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80113DE8_stardust_battle = 0;
            }
            if (D_80114AA4_stardust_battle >= 15) {
                HuAudSeqPlay(0x6A);
                D_80114AC8_stardust_battle->unk_04 = 13;
                GMesCreate(0x16, D_80114AC8_stardust_battle->character);
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 16:
            if (D_80114AA4_stardust_battle > 60.0f) {
                D_80114AC8_stardust_battle->unk_04 = 13;
                GMesCreate(0x16, D_80114AC8_stardust_battle->character);
                HuAudSeqPlay(0x65);
                D_80114AAC_stardust_battle = 98;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 17:
            if (GMesStatGet() == 0) {
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 6:
        case 18:
            if (D_80114AA4_stardust_battle >= 15) {
                D_80114AB8_stardust_battle = 32;
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
    }
}

void func_80106A3C_stardust_battle(void) {
    switch (D_80114ABC_stardust_battle) {
        case 0:
            if (func_8010C508_stardust_battle() == 14) {
                D_80114AC8_stardust_battle->unk_04 = 14;
                func_8010C44C_stardust_battle();
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 1:
            if (D_80114AA4_stardust_battle >= 15.0f) {
                GMesCreate(0x1D);
                HuAudSeqPlay(0x6B);
                D_80114AAC_stardust_battle = 132;
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 2:
            if (GMesStatGet() == 0) {
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 3:
            if (D_80114AA4_stardust_battle >= 15) {
                D_80114AB8_stardust_battle = 32;
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
    }
}

void func_80106B60_stardust_battle(void) {
    switch (D_80114ABC_stardust_battle) {
        case 0:
            func_80107F34_stardust_battle(5.0f);
            if (func_8010C508_stardust_battle() == 14) {
                func_8010C498_stardust_battle();
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 1:
            func_80107F34_stardust_battle(5.0f);
            if (D_80114AA4_stardust_battle >= 150.0f) {
                D_80114AB8_stardust_battle = 64;
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
    }
}

void func_80106C30_stardust_battle(void) {
    switch (D_80114ABC_stardust_battle) {
        case 0:
            D_80114AC8_stardust_battle->unk_04 = 14;
            D_80114AA4_stardust_battle = 0;
            D_80114ABC_stardust_battle++;
            break;
        case 1:
            if (func_8010C508_stardust_battle() == 14) {
                func_8010C44C_stardust_battle();
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
        case 2:
            if (D_80114AA4_stardust_battle >= 30.0f) {
                D_80114AB8_stardust_battle = 64;
                D_80114AA4_stardust_battle = 0;
                D_80114ABC_stardust_battle++;
            }
            break;
    }
}

void func_80106D0C_stardust_battle(void) {
    UnkStardustBattleObj *obj;
    omObjData *object;
    s16 i;

    obj = D_80114AC8_stardust_battle = HuMemAllocTag(sizeof(UnkStardustBattleObj), TAG_OVERLAY);
    func_800E19F0_minigame(0);
    func_800E18D8_minigame();
    for (i = 0; i < 4; i++) {
        if (GwPlayer[D_80113DEC_stardust_battle[i]].group == 0) {
            break;
        }
    }
    if (i >= 4) {
        i = 0;
    }
    obj->unk_00 = i;
    obj->unk_20 = D_80113DEC_stardust_battle[i];
    object = omAddObj(16, 11, 60, -1, func_80106EB0_stardust_battle);
    D_800EC598_minigame[D_800EC280_minigame] = object;
    D_800EC280_minigame++;
    object->trans.x = D_80113CB0_stardust_battle[obj->unk_00].x;
    object->trans.z = D_80113CB0_stardust_battle[obj->unk_00].z;
    obj->unk_2C = object->trans.x;
    obj->unk_30 = object->trans.y;
    obj->unk_34 = object->trans.z;
    obj->func_6C = NULL;
    obj->func_70 = NULL;
    obj->func_74 = NULL;
    obj->func_78 = NULL;
    memset(&obj->unk_3A, 0, 0x20);
    func_80111FC0_stardust_battle(object, (u32)obj);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80106EB0_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801073F4_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80107760_stardust_battle);

void func_80107DCC_stardust_battle(omObjData *object, s16 mode) {
    UnkStardustBattleObj *obj;

    if (object != NULL) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
        if (obj->func_78 != NULL) {
            obj->func_78(object);
            obj->func_78 = NULL;
        }
        if (D_80113E24_stardust_battle[mode] != NULL) {
            D_80113E24_stardust_battle[mode](object);
        }
        obj->func_70 = D_80113E30_stardust_battle[mode];
        obj->func_74 = D_80113E3C_stardust_battle[mode];
        obj->func_78 = D_80113E48_stardust_battle[mode];
    }
}

s16 func_80107E84_stardust_battle(s16 arg0) {
    omObjData *object = D_800EC598_minigame[0];
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    HmfModel *other = &Hu3DData[object->model[9]];
    HmfData *hmf;

    if (obj->unk_12 == arg0) {
        return arg0;
    }
    hmf = other->hmf;
    other->hmf = model->hmf;
    model->hmf = hmf;
    obj->unk_12 = arg0;
    return arg0;
}

void func_80107F34_stardust_battle(f32 step) {
    func_800E1BA8_minigame_ObjData *data = D_800EC598_minigame[0]->data;

    data->unk3C = func_80111C2C_stardust_battle(atan2df(D_80114B18_stardust_battle->trans.x - D_800EC598_minigame[0]->trans.x,
                                                        D_80114B18_stardust_battle->trans.z - D_800EC598_minigame[0]->trans.z),
                                                data->unk3C, step);
}

s16 func_80107FA4_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    obj->func_6C = func_80108120_stardust_battle;
    obj->unk_3A = 0;
    return 1;
}

s16 func_80107FE8_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    if (obj->func_6C != func_80108120_stardust_battle || obj->unk_3A < 2 || obj->unk_3C < 22.5f) {
        return 0;
    }
    return 1;
}

void func_80108074_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = func_801081FC_stardust_battle;
    }
}

void func_801080B0_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = func_801082C4_stardust_battle;
    }
}

void func_801080EC_stardust_battle(void) {
    UnkStardustBattleObj *obj;

    if (D_800EC280_minigame != 0) {
        obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
        obj->func_6C = NULL;
    }
}

void func_80108120_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);

    switch (obj->unk_3A) {
        case 0:
            func_800E5690_minigame(object, 40);
            obj->unk_3A++;
            break;
        case 1:
            if (func_800E4A90_minigame(object) == 1) {
                func_800E5690_minigame(object, 41);
                obj->unk_3A++;
                obj->unk_3C = 0;
            }
            break;
        case 2:
            obj->unk_3C++;
            if (func_800E4A90_minigame(object) == 1) {
                obj->func_6C = NULL;
                obj->unk_3C = 0;
                obj->unk_3A = 0;
            }
            break;
    }
}

void func_801081FC_stardust_battle(omObjData *object) {
    f32 x = object->trans.x;
    f32 z = object->trans.z;

    if (x > 200.0) {
        x = 200.0f;
    } else if (x < -200.0) {
        x = -200.0f;
    }
    if (z > 300.0) {
        z = 300.0f;
    }
    func_801117E4_stardust_battle(x, CAMERA_KEEP, z, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP, 1);
}

void func_801082C4_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(D_800EC598_minigame[0]);
    func_800E1BA8_minigame_ObjData *data = object->data;

    if (obj->unk_04 != -1 && data->unk38 == 1000.0f && !(func_800E4A90_minigame(object) & 0x8C00)) {
        if (obj->unk_04 == 13) {
            if (func_80111B28_stardust_battle(0.0f, data->unk3C) < 5.0f) {
                data->unk3C = 0.0f;
            } else {
                data->unk3C = func_80111C2C_stardust_battle(0.0f, data->unk3C, 5.0f);
                return;
            }
        }
        Hu3DData[object->model[0]].motIdShape = 0xFF;
        func_800E5798_minigame(object, (u16)obj->unk_04);
        func_80045F1C_main(obj->unk_04 == 13 ? obj->unk_18 : obj->unk_1C, -1, obj->unk_20);
        obj->unk_04 = -1;
    }
}

void func_80108404_stardust_battle(void) {
    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
}

void func_80108444_stardust_battle(void) {
}

void func_8010844C_stardust_battle(void) {
}

/* Like func_80107FA4, the return value of func_80111FEC_stardust_battle is
   treated as a pointer. */
void func_80108454_stardust_battle(void) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle();

    D_800EB744_minigame = 1.029f;
    D_800EB748_minigame = 0.105000004f;
    D_800EB774_minigame = 1.19f;
    obj->unk_0A = 0;
}

void func_801084B0_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    f32 stickX = D_800CBB6E_main[obj->pad];
    f32 stickY = D_800D20A1_main[obj->pad];
    f32 scale;

    if (stickX > 60.0f) {
        stickX = 60.0f;
    } else if (stickX < -60.0f) {
        stickX = -60.0f;
    } else {
        stickX = D_800CBB6E_main[obj->pad];
    }
    if (stickY > 60.0f) {
        stickY = 60.0f;
    } else if (stickY < -60.0f) {
        stickY = -60.0f;
    } else {
        stickY = D_800D20A1_main[obj->pad];
    }
    if (fabs(stickX) < 8.0) {
        stickX = 0.0f;
    }
    if (fabs(stickY) < 8.0) {
        stickY = 0.0f;
    }
    scale = sqrtf(stickX * stickX + stickY * stickY);
    if (scale != 0.0f) {
        scale = 1.0f / scale;
    } else {
        scale = 0.0f;
    }
    D_800CBB6E_main[obj->pad] = stickX * scale * 60.0f * 0.8f;
    D_800D20A1_main[obj->pad] = stickY * scale * 60.0f * 0.8f;
}

void func_801086E8_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    s32 stickX;
    s32 stickY;

    if (object->trans.y == 0.0f && ((stickX = D_800CBB6E_main[obj->pad], ABS(stickX) > 16) ||
                                    (stickY = D_800D20A1_main[obj->pad], ABS(stickY) > 16))) {
        obj->unk_0C = 1;
    } else {
        obj->unk_0C = 0;
    }
    if (obj->unk_0C != 0) {
        obj->unk_0E++;
    } else {
        obj->unk_0E = 0;
    }
    if (D_80114B14_stardust_battle != 1) {
        if ((object->trans.y != 0.0f || !(obj->unk_30 > 0.0f)) && obj->unk_0C != 0 && obj->unk_0E == 20) {
            obj->unk_0E = 0;
        }
        if (!(obj->unk_0A & 0xF)) {
            func_8010A04C_stardust_battle(D_80114B18_stardust_battle->trans.x, D_80114B18_stardust_battle->trans.z,
                                          37.5f, 7.5000005f, 0.0f, 0.0f);
        }
    }
}

void func_8010882C_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    HmfModel *shadow;

    D_800EB744_minigame = 1.47f;
    D_800EB748_minigame = 0.15f;
    D_800EB774_minigame = 1.7f;
    object->model[10] =
        func_8000B108_main(D_800A178C_main[obj->character][0] | D_800A178C_main[obj->character][1], 0x689);
    func_8001ED54_main(object->model[10]);
    Hu3DModelRemakeStatic(object->model[10]);
    func_8001C514_main(object->model[10]);
    shadow = &Hu3DData[object->model[10]];
    obj->unk_38 = shadow->motId;
    shadow->motId = model->motId;
    shadow->motTime = model->motTime;
    shadow->motSpeed = 0;
    shadow->motIdShift = model->motIdShift;
    shadow->motShiftTime = model->motShiftTime;
    shadow->motShiftSpeed = 0;
    shadow->motIdShape = model->motIdShape;
    shadow->motShapeTime = model->motShapeTime;
    shadow->motShapeSpeed = 0;
    shadow->unk0C = model->unk0C;
    shadow->unk0E = model->unk0E;
    guMtxIdentF(shadow->mtx);
    mtxScaleCat(shadow->mtx, 1.0f, -1.0f, 1.0f);
}

void func_801089B4_stardust_battle(void) {
}

void func_801089BC_stardust_battle(omObjData *object) {
    HmfModel *model;
    HmfModel *shadow;
    func_800E1BA8_minigame_ObjData *data;

    if (object->model[10] == -1) {
        return;
    }

    func_80111FEC_stardust_battle(object);
    data = object->data;
    model = &Hu3DData[object->model[0]];
    shadow = &Hu3DData[object->model[10]];
    Hu3DModelPosSet(object->model[10], object->trans.x, -object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[10], object->rot.x, data->unk3C, object->rot.z);
    shadow->motId = model->motId;
    shadow->motTime = model->motTime;
    shadow->motSpeed = 0;
    shadow->motIdShift = model->motIdShift;
    shadow->motShiftTime = model->motShiftTime;
    shadow->motShiftSpeed = 0;
    shadow->motIdShape = model->motIdShape;
    shadow->motShapeTime = model->motShapeTime;
    shadow->motShapeSpeed = 0;
    shadow->unk0C = model->unk0C;
    shadow->unk0E = model->unk0E;
}

void func_80108AC4_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *shadow = &Hu3DData[object->model[10]];

    shadow->motId = obj->unk_38;
    shadow->motIdShift = 0xFF;
    shadow->motIdShape = 0xFF;
    Hu3DModelKill(object->model[10]);
    object->model[10] = -1;
}

void func_80108B34_stardust_battle(void) {
    UnkStardustBattleStage *stage = HuMemAllocTag(sizeof(UnkStardustBattleStage), TAG_OVERLAY);

    D_80114B10_stardust_battle = stage;
    memset(stage, 0, sizeof(UnkStardustBattleStage));
    stage->unk_00 = -1;
    stage->unk_20 = 0;
    stage->unk_24 = NULL;
    stage->streaks = NULL;
    stage->func_30 = NULL;
    stage->func_34 = NULL;
    D_800EC1C0_minigame[D_800EBE28_minigame] = omAddObj(3, 8, 0, -1, func_80108C14_stardust_battle);
    omSetStatBit(D_800EC1C0_minigame[D_800EBE28_minigame], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80111FC0_stardust_battle(D_800EC1C0_minigame[D_800EBE28_minigame], (u32)stage);
    D_800EBE28_minigame++;
    func_800E1490_minigame(0);
}

void func_80108C14_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    D_800EC1C0_minigame_ObjData *work;
    HmfData *hmf;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    func_800E1370_minigame(object, 2, 0.0f);
    func_80109128_stardust_battle(0);
    object->model[2] = func_8000B108_main(0x62000A, 0x19);
    Hu3DModelScaleSet(object->model[2], 1.75f, 1.5f, 1.5f);
    Hu3DModelPosSet(object->model[2], 0.0f, -200.0f, 0.0f);
    func_8001C954_main(object->model[2]);
    hmf = Hu3DData[object->model[2]].hmf;
    stage->unk_02 = func_8002C834_main(hmf, "stardast-cyl10");
    stage->unk_04 = func_8002C834_main(hmf, "stardast-cyl5_1");
    stage->unk_08 = stage->unk_0C = 0.0f;
    stage->unk_10 = stage->unk_14 = 0.0f;
    stage->unk_18 = stage->unk_1C = 0.0f;
    object->func = func_80108D84_stardust_battle;
}

void func_80108D84_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (omPauseChk() + D_800D6A90_main == 0) {
        stage->unk_0C += 2.0f;
        if (stage->unk_0C >= 64.0f) {
            stage->unk_0C -= 128.0f;
        }
        stage->unk_10 -= 0.25f;
        if (stage->unk_10 <= -32.0f) {
            stage->unk_10 += 64.0f;
        }
    }
    func_80108EC4_stardust_battle(object->model[2], stage->unk_08, stage->unk_0C, 64, 64, stage->unk_02);
    func_80108EC4_stardust_battle(object->model[2], stage->unk_10, stage->unk_14, 32, 32, stage->unk_04);
    if (stage->func_30 != NULL) {
        stage->func_30(object);
    }
}

#ifdef NON_MATCHING
// Register allocation differs (hmf is assigned a0 instead of a1) and some instructions are scheduled differently.
/* Scrolls the texture coordinates of one of the model's objects. */
void func_80108EC4_stardust_battle(s16 model, f32 u, f32 v, s32 width, s32 height, s16 index) {
    HmfData *hmf = Hu3DData[model].hmf;
    u16 wrapU;
    u16 wrapV;
    HmfModelData_Unk64_Unk60_Struct *obj;
    Vtx *src;
    Vtx *dst;
    u16 count;
    u16 du;
    u16 dv;
    s16 i;

    if (hmf != NULL) {
        wrapU = width << 5;
        wrapV = height << 5;
        obj = &hmf->unk60[index];
        count = obj->unk2A;
        src = &hmf->unk40[obj->unk28];
        dst = &hmf->unk44[D_800D2008_main][obj->unk28];
        du = u * 32.0f;
        dv = v * 32.0f;
        if (u < 0.0f) {
            u = -u;
        }
        if (v < 0.0f) {
            v = -v;
        }
        if (wrapU < u * 32.0f) {
            du %= wrapU;
        }
        if (wrapV < v * 32.0f) {
            dv %= wrapV;
        }
        for (i = 0; i < (s16)count; i++, src++, dst++) {
            dst->v.tc[0] = du + src->v.tc[0];
            dst->v.tc[1] = dv + src->v.tc[1];
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80108EC4_stardust_battle);
#endif

void func_80109128_stardust_battle(s16 mode) {
    omObjData *object;
    UnkStardustBattleStage *stage;

    if (D_800EBE28_minigame == 0 || D_800EC280_minigame == 0) {
        return;
    }

    object = D_800EC1BC_minigame[D_800EBE28_minigame];
    stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    if (stage->unk_00 == mode) {
        return;
    }

    func_80107DCC_stardust_battle(D_800EC598_minigame[0], mode);
    if (stage->func_34 != NULL) {
        stage->func_34(object);
        stage->func_34 = NULL;
    }
    stage->unk_00 = mode;
    stage->func_30 = D_80113E78_stardust_battle[mode];
    stage->func_34 = D_80113E84_stardust_battle[mode];
    if (object->model[0] != -1) {
        Hu3DModelKill(object->model[0]);
    }
    if (object->model[1] != -1) {
        Hu3DModelKill(object->model[1]);
    }
    object->model[0] = func_8000B108_main(D_80113E60_stardust_battle[mode] | 0x620000, 0x699);
    object->model[1] =
        func_8000B108_main(D_80113E54_stardust_battle[mode] | 0x620000, D_80113E6C_stardust_battle[mode] | 0x299);
    if (stage->func_30 != NULL) {
        stage->func_30(object);
    }
}

/* Like func_80107FA4, the return value of func_80111FEC_stardust_battle is
   treated as a pointer. */
s16 func_8010929C_stardust_battle(void) {
    if (D_800EBE28_minigame == 0) {
        return 0;
    }

    if (D_800EC280_minigame == 0) {
        return 0;
    }

    return ((UnkStardustBattleStage *)func_80111FEC_stardust_battle(D_800EC1BC_minigame[D_800EBE28_minigame]))
        ->unk_00;
}

void func_801092F0_stardust_battle(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    f32 dist = object->trans.x * object->trans.x + object->trans.z * object->trans.z;
    f32 radius = fabs(525.0 - data->unk48);

    if (radius * radius < dist) {
        dist = sqrtf(dist);
        if (dist != 0.0f) {
            dist = radius / dist;
        } else {
            object->trans.x = 0.0f;
            object->trans.z = radius;
            dist = 1.0f;
        }
        object->trans.x *= dist;
        object->trans.z *= dist;
    }
}

void func_801093CC_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    stage->func_30 = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109424_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80109B18_stardust_battle);

void func_80109F94_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (stage->unk_24 != NULL) {
        HuMemFree(stage->unk_24);
    }
    stage->unk_24 = NULL;
    func_8010A5A4_stardust_battle(object);
}

void func_80109FE4_stardust_battle(void) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle();
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        streak = stage->streaks = (UnkStardustBattleStreak *)HuMemAllocTag(0xF00, TAG_OVERLAY);
        memset(streak, 0, 0xF00);

        for (i = 0; i < 64; i++, streak++) {
            streak->index = i;
        }
    }
}

s32 func_8010A04C_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(D_800EC1C0_minigame[0]);
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        return -1;
    }

    streak = stage->streaks;
    for (i = 0; i < 64; i++, streak++) {
        if (streak->active == 0) {
            streak->active = 1;
            streak->x = x;
            streak->y = 0.0f;
            streak->z = z;
            streak->unk_14 = arg2;
            streak->unk_18 = arg3;
            streak->unk_1C = 150.0f;
            streak->unk_10 = arg5;
            streak->unk_20 = arg4;
            streak->unk_24 = streak->unk_14 * streak->unk_20;
            streak->unk_34 = streak->unk_1C * streak->unk_20;
            if (streak->unk_34 != 0.0f) {
                streak->unk_38 = 1.0f / streak->unk_34;
            } else {
                streak->unk_38 = 1.0f;
            }
            streak->unk_28 = (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20) *
                             (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20);
            streak->unk_2C = (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20) *
                             (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20);
            streak->unk_30 = sqrtf(x * x + z * z);
            return streak->index;
        }
    }
    return -1;
}

/* Spawns a streak at the closest point of the stage's point list, if any is
   within range of the given position. */
s16 func_8010A204_stardust_battle(f32 x, f32 z, f32 arg2, f32 arg3, f32 arg4, f32 arg5) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(D_800EC1C0_minigame[0]);
    UnkStardustBattlePoint *point;
    f32 dx;
    f32 dz;
    f32 best;
    s32 bestIndex;
    s32 count;
    s32 i;

    if (stage->streaks == NULL) {
        return -1;
    }
    if (stage->unk_24 == NULL) {
        return -1;
    }
    point = stage->unk_24;
    count = 0;
    for (i = 0; i < stage->unk_20; i++, point++) {
        dx = point->x - x;
        dz = point->z - z;
        if (fabs(dx) < 100.0 && fabs(dz) < 100.0) {
            D_80114940_stardust_battle[count].distSq = dx * dx + dz * dz;
            D_80114940_stardust_battle[count].index = i;
            count++;
            if (count >= 32) {
                break;
            }
        }
    }
    if (count != 0) {
        bestIndex = D_80114940_stardust_battle[0].index;
        best = D_80114940_stardust_battle[0].distSq;
        for (i = 1; i < count; i++) {
            if (D_80114940_stardust_battle[i].distSq < best) {
                bestIndex = D_80114940_stardust_battle[i].index;
                best = D_80114940_stardust_battle[i].distSq;
            }
        }
        x = stage->unk_24[bestIndex].x;
        z = stage->unk_24[bestIndex].z;
    }
    return func_8010A04C_stardust_battle(x, z, arg2, arg3, arg4, arg5);
}

void func_8010A418_stardust_battle(void) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle();
    UnkStardustBattleStreak *streak;
    s32 i;

    if (stage->streaks == NULL) {
        return;
    }

    streak = stage->streaks;
    for (i = 0; i < 64; i++, streak++) {
        if (streak->active == 0) {
            continue;
        }
        if (streak->unk_20 >= 0.5f) {
            streak->unk_10 += streak->unk_18;
        }
        streak->unk_28 = (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20) *
                         (fabs(streak->unk_10) + streak->unk_1C * streak->unk_20);
        streak->unk_2C = (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20) *
                         (fabs(streak->unk_10) - streak->unk_1C * streak->unk_20);
        if (streak->unk_20 < 1.0f) {
            streak->unk_20 += 0.0625f;
            if (streak->unk_20 >= 1.0f) {
                streak->unk_20 = 1.0f;
            }
        }
        streak->unk_24 = streak->unk_14 * streak->unk_20;
        streak->unk_34 = streak->unk_1C;
        if (streak->unk_34 != 0.0f) {
            streak->unk_38 = 1.0f / streak->unk_34;
        } else {
            streak->unk_38 = 1.0f;
        }
        if (streak->unk_10 - streak->unk_1C * streak->unk_20 - streak->unk_30 >= 600.0) {
            streak->unk_20 = 0.0f;
            streak->unk_14 = 0.0f;
            streak->active = 0;
        }
    }
}

void func_8010A5A4_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (stage->streaks != NULL) {
        HuMemFree(stage->streaks);
    }
    stage->streaks = NULL;
}

void func_8010A5E0_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    HmfData *hmf = Hu3DData[object->model[0]].hmf;

    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 0.1f);
    func_800E1310_minigame(object, 5.0f);
    func_8001C954_main(object->model[0]);
    stage->unk_2C = func_8002C834_main(hmf, "comet-nagare");
    stage->func_30 = func_8010A690_stardust_battle;
}

void func_8010A690_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (omPauseChk() + D_800D6A90_main == 0) {
        stage->unk_1C += 2.0f;
        if (stage->unk_1C >= 64.0f) {
            stage->unk_1C -= 128.0f;
        }
    }
    func_80108EC4_stardust_battle(object->model[0], stage->unk_18, stage->unk_1C, 64, 64, stage->unk_2C);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010A74C_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010AAC4_stardust_battle);

void func_8010BFE4_stardust_battle(f32 arg0, s16 arg1) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle == NULL) {
        return;
    }

    actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);

    if (arg1 > 0) {
        actor->unk_24 = arg1;
        actor->velY = (arg0 - D_80114B18_stardust_battle->trans.y) / arg1;
    }
}

void func_8010C06C_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->velY = 0.0f;
        actor->unk_24 = 0;

        if (actor->unk_04 != 7) {
            actor->velX = actor->velZ = 0.0f;
            actor->unk_04 = 11;
        }
    }
}

void func_8010C0C8_stardust_battle(void) {
    UnkStardustBattleActor *actor;
    f32 dx;
    f32 dy;
    f32 dz;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->start.x = D_80114B18_stardust_battle->trans.x;
        actor->start.y = D_80114B18_stardust_battle->trans.y;
        actor->start.z = D_80114B18_stardust_battle->trans.z;
        actor->target.x = Center.x;
        actor->target.y = 450.0f;
        actor->target.z = Center.z + 200.0;
        dx = actor->target.x - actor->start.x;
        dy = actor->target.y - actor->start.y;
        dz = actor->target.z - actor->start.z;
        actor->unk_26 = sqrtf(dx * dx + dy * dy + dz * dz) / 15.0000005960464478;
        if (actor->unk_26 == 0) {
            actor->unk_26 = 1;
        }
        actor->unk_24 = 0;
        actor->active = 0;
        actor->unk_04 = 13;
    }
}

void func_8010C1F8_stardust_battle(s16 motion, s16 startTime, s16 endTime, u8 attr) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
        func_8001C5B4_main(obj->model[0], obj->motion[motion]);
        model->motTime = startTime;
        model->unk48 = endTime;
        model->motAttr = attr;
    }
}

/* Unlike the other func_80111FEC_stardust_battle call sites, the return value
   is unused here; the stardust object is read straight from the global. */
void func_8010C2CC_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
        model->motSpeed = arg0;
    }
}

f32 func_8010C32C_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }

    func_80111FEC_stardust_battle(obj);
    model = &Hu3DData[obj->model[0]];
    return model->motSpeed;
}

void func_8010C38C_stardust_battle(f32 arg0) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj != NULL) {
        func_80111FEC_stardust_battle(obj);
        model = &Hu3DData[obj->model[0]];
        model->motTime = arg0;
    }
}

f32 func_8010C3EC_stardust_battle(void) {
    omObjData *obj = D_80114B18_stardust_battle;
    HmfModel *model;

    if (obj == NULL) {
        return 0.0f;
    }

    func_80111FEC_stardust_battle(obj);
    model = &Hu3DData[obj->model[0]];
    return model->motTime;
}

void func_8010C44C_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->active = 0;
        actor->unk_04 = 15;
        func_8010C1F8_stardust_battle(1, 0, 0, 2);
    }
}

void func_8010C498_stardust_battle(void) {
    UnkStardustBattleActor *actor;

    if (D_80114B18_stardust_battle != NULL) {
        actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle);
        actor->unk_18 = 0;
        actor->active = 0;
        actor->unk_04 = 17;
        HuAudFXPlay(0x50B);
        actor->unk_4C = D_80114B18_stardust_battle->trans.x;
        actor->unk_50 = D_80114B18_stardust_battle->trans.y;
        actor->unk_54 = D_80114B18_stardust_battle->trans.z;
    }
}

s16 func_8010C508_stardust_battle(void) {
    if (D_80114B18_stardust_battle == NULL) {
        return 0;
    }
    return ((UnkStardustBattleActor *)func_80111FEC_stardust_battle(D_80114B18_stardust_battle))->unk_04;
}

void func_8010C538_stardust_battle(void) {
    UnkStardustBattleSpots *spots = HuMemAllocTag(sizeof(UnkStardustBattleSpots), TAG_OVERLAY);

    D_80114B20_stardust_battle = spots;
    spots->spot = HuMemAllocTag(32 * sizeof(UnkStardustBattleSpot), TAG_OVERLAY);
    memset(spots->spot, 0, 32 * sizeof(UnkStardustBattleSpot));
    spots->count = 0;
    spots->max = 32;
    spots->unk_04 = 0;
    func_8010C5A8_stardust_battle(32, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010C5A8_stardust_battle);

Vec *func_8010CA48_stardust_battle(s16 index) {
    UnkStardustBattleSpots *spots = D_80114B20_stardust_battle;
    UnkStardustBattleSpot *spot;

    if (index >= 32) {
        index %= 32;
    }
    spot = &spots->spot[index];
    if (spots->count == 0) {
        return &D_80113EB8_stardust_battle;
    }
    if (spot->active == 0) {
        spot = &spots->spot[(s16)(index % spots->count)];
    }
    if (spot->followPlayer != 0) {
        spot->pos.x = D_800EC598_minigame[0]->trans.x;
        spot->pos.z = D_800EC598_minigame[0]->trans.z;
        spot->pos.y = 0.0f;
    }
    return &spot->pos;
}

void func_8010CB34_stardust_battle(void) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    s32 i;

    stars = HuMemAllocTag(sizeof(UnkStardustBattleStars), TAG_OVERLAY);
    D_80114B2C_stardust_battle = stars;
    memset(stars, 0, sizeof(UnkStardustBattleStars));
    stars->modelId1 = func_8000B108_main(0x620005, 0x49D);
    stars->modelId2 = func_8000B108_main(0x620006, 0x49D);
    stars->effectId1 = func_8000B108_main(0, 0x149D);
    stars->effectId2 = func_8000B108_main(0x620008, 0x189D);
    stars->count = 10;
    star = HuMemAllocTag(sizeof(UnkStardustBattleStar) * 10, TAG_OVERLAY);
    stars->star = star;
    memset(star, 0, stars->count * sizeof(UnkStardustBattleStar));
    for (i = 0; i < stars->count; i++, star++) {
        star->active = 0;
        if (i == 0) {
            star->model[0] = stars->modelId1;
            star->model[2] = Hu3DModelLink(stars->modelId1);
            star->model[1] = stars->modelId2;
            star->model[3] = Hu3DModelLink(stars->modelId2);
            star->model[4] = stars->effectId1;
        } else {
            star->model[0] = Hu3DModelLink(stars->modelId1);
            star->model[2] = Hu3DModelLink(stars->modelId1);
            star->model[1] = Hu3DModelLink(stars->modelId2);
            star->model[3] = Hu3DModelLink(stars->modelId2);
            star->model[4] = Hu3DModelLink(stars->effectId1);
        }
        func_8001C258_main(star->model[0], 4, 4);
        func_8001C258_main(star->model[2], 4, 4);
        func_8001C258_main(star->model[1], 4, 4);
        func_8001C258_main(star->model[3], 4, 4);
        func_8001C258_main(star->model[4], 4, 4);
        mtxRotCat(Hu3DData[star->model[2]].mtx, 180.0f, 0.0f, 0.0f);
        mtxRotCat(Hu3DData[star->model[2]].mtx, 0.0f, 180.0f, 0.0f);
        mtxRotCat(Hu3DData[star->model[3]].mtx, 180.0f, 0.0f, 0.0f);
        mtxRotCat(Hu3DData[star->model[3]].mtx, 0.0f, 180.0f, 0.0f);
        star->model[5] = func_8000B108_main(0x620007, 0x189D);
        Hu3DModelScaleSet(star->model[5], 0.75f, 0.75f, 0.75f);
        func_8001C954_main(star->model[5]);
        star->unk_0E = 0;
        star->unk_10 = 0;
        star->unk_12 = 0;
        star->unk_68 = star->unk_6C = 0.0f;
        star->unk_70 = star->unk_74 = star->unk_78 = 0.0f;
        star->unk_14 = 0;
        star->state = 3;
        star->unk_1A = -1;
    }
    omSetStatBit(omAddObj(18, 0, 0, -1, func_8010CE5C_stardust_battle), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010CE5C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114528_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_8011452C_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114530_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", jtbl_80114538_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114550_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114558_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114560_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114568_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114570_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114578_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114580_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114588_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114590_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_80114598_stardust_battle);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", D_801145A0_stardust_battle);

/* Activates a free star falling from pos towards target, returning its index
   or -1 if none are free. */
s16 func_8010DADC_stardust_battle(Vec *pos, Vec *target, f32 speed) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    f32 y;
    f32 step;
    s32 frames;
    s32 i;

    if (D_80114B2C_stardust_battle == NULL) {
        return -1;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active == 0) {
            star->active = 1;
            func_8001C258_main(star->model[0], 4, 0);
            func_8001C258_main(star->model[5], 4, 0);
            star->state = 0;
            star->unk_14 = 0;
            star->unk_18 = 1;
            star->unk_0E = 0;
            star->unk_10 = 0;
            star->unk_12 = 4;
            star->unk_68 = star->unk_6C = 0.0f;
            star->x = pos->x;
            star->y = pos->y;
            star->z = pos->z;
            star->unk_4C = target->x;
            star->unk_50 = target->y;
            star->unk_54 = target->z;
            star->unk_44 = speed;
            y = star->y;
            step = star->unk_44;
            for (frames = 0; frames < 256; frames++) {
                y += step;
                if (y < 0.0f) {
                    break;
                }
            }
            if (frames != 0) {
                step = 1.0f / frames;
            } else {
                step = 1.0f;
            }
            star->unk_40 = (star->unk_4C - star->x) * step;
            star->unk_48 = (star->unk_54 - star->z) * step;
            star->unk_70 = atan2df(star->unk_40 * star->unk_40 + star->unk_48 * star->unk_48, -(star->unk_44 * star->unk_44));
            star->unk_74 = atan2df(star->unk_40, star->unk_48);
            star->unk_78 = 0.0f;
            star->targetX = star->targetY = star->targetZ = 0.0f;
            star->unk_1C = star->x;
            star->unk_20 = star->y;
            star->unk_24 = star->z;
            star->unk_64 = atan2df(star->unk_40, star->unk_48);
            Hu3DModelPosSet(star->model[0], star->x, star->y, star->z);
            Hu3DModelPosSet(star->model[2], star->x, -star->y, star->z);
            Hu3DModelPosSet(star->model[4], star->x, 0.0f, star->z);
            func_8008A070_main(Hu3DData[star->model[0]].mtx);
            func_8008A070_main(Hu3DData[star->model[1]].mtx);
            Hu3DModelPosSet(star->model[5], star->x, star->y + 34.99999940395355, star->z);
            Hu3DModelScaleSet(star->model[5], 0.75f, 0.75f, 0.75f);
            func_8001CAA4_main(star->model[5], stars->effectId2, star->unk_68);
            Hu3DModelRotSet(star->model[5], star->unk_70 + 180.0f, star->unk_74, 0.0f);
            func_8008A070_main(Hu3DData[star->model[5]].mtx);
            mtxRotCat(Hu3DData[star->model[5]].mtx, 0.0f, star->unk_78, 0.0f);
            return i;
        }
    }
    return -1;
}

/* Spawns a star falling towards target from a randomized position above it. */
s16 func_8010DE64_stardust_battle(Vec *target, f32 speed) {
    Vec pos;

    pos.x = target->x + 400.0;
    pos.z = target->z + (0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 100.0 * 5.0;
    pos.y = target->y + 600.0;
    return func_8010DADC_stardust_battle(&pos, target, speed);
}

void func_8010DF70_stardust_battle(s16 index) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (index < stars->count) {
        star = &stars->star[index];
        if (star->active != 0) {
            star->active = 0;
            star->x = star->targetX = star->unk_40 = 0.0f;
            func_8001C258_main(star->model[0], 4, 4);
            func_8001C258_main(star->model[1], 4, 4);
            func_8001C258_main(star->model[2], 4, 4);
            func_8001C258_main(star->model[3], 4, 4);
            func_8001C258_main(star->model[4], 4, 4);
            func_8001C258_main(star->model[5], 4, 4);
        }
    }
}

#ifdef NON_MATCHING
// Register allocation: stars and data have swapped s4/s5, and v0/v1 are swapped when indexing the chosen star.
/* Picks up the closest landed star in front of the object, returning its index
   or -1 if there is none. */
s16 func_8010E03C_stardust_battle(omObjData *object) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    func_800E1BA8_minigame_ObjData *data;
    f32 dx;
    f32 dz;
    f32 distSq;
    f32 angle;
    f32 range;
    s32 count;
    s32 i;
    s32 j;

    if (D_80114B2C_stardust_battle == NULL) {
        return -1;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    data = object->data;
    memset(D_80114A40_stardust_battle, 0, sizeof(D_80114A40_stardust_battle));
    count = 0;
    range = data->unk48 + 50.0 + 50.0;
    range = range * range;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active != 0 && star->state == 3) {
            dx = star->x - object->trans.x;
            dz = star->z - object->trans.z;
            distSq = dx * dx + dz * dz;
            angle = atan2df(dx, dz);
            if (distSq < range && fabs(func_80111B28_stardust_battle(angle, data->unk3C)) < 40.0) {
                D_80114A40_stardust_battle[count].index = i;
                D_80114A40_stardust_battle[count].distSq = distSq;
                count++;
            }
        }
    }
    if (count <= 0) {
        return -1;
    }
    if (count != 1) {
        for (i = 0; i < count - 1; i++) {
            for (j = i + 1; j < count; j++) {
                if (D_80114A40_stardust_battle[i].distSq > D_80114A40_stardust_battle[j].distSq) {
                    D_80114A90_stardust_battle = D_80114A40_stardust_battle[i];
                    D_80114A40_stardust_battle[i] = D_80114A40_stardust_battle[j];
                    D_80114A40_stardust_battle[j] = D_80114A90_stardust_battle;
                }
            }
        }
    }
    star = &stars->star[D_80114A40_stardust_battle[0].index];
    if (star->active != 0) {
        func_8001C258_main(star->model[star->unk_10], 4, 0);
        star->unk_58 = star->x;
        star->unk_5C = star->y;
        star->unk_60 = star->z;
        HuAudFXPlay(0x507);
        star->state = 4;
        star->unk_14 = 0;
    }
    return D_80114A40_stardust_battle[0].index;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E03C_stardust_battle);
#endif

/* Returns the indexed star, or NULL if the index is out of range or the star
   isn't in use. */
UnkStardustBattleStar *func_8010E300_stardust_battle(s16 arg0) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 >= stars->count) {
        return NULL;
    }
    star = &stars->star[arg0];
    return star->active ? star : NULL;
}

void func_8010E35C_stardust_battle(s16 index) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (index < stars->count) {
        star = &stars->star[index];
        if (star->active != 0) {
            if (star->state == 4) {
                star->state = 5;
                star->unk_14 = 0;
                guMtxIdentF(Hu3DData[star->model[star->unk_10]].mtx);
                PlayerFXPlay(0xAF, 0);
                star->unk_40 = sindf(star->targetY) * 31.9999992847442627;
                star->unk_48 = cosdf(star->targetY) * 31.9999992847442627;
                star->unk_44 = 10.0f;
            } else {
                func_8010DF70_stardust_battle(index);
            }
        }
    }
}

void func_8010E46C_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 < stars->count) {
        star = &stars->star[arg0];
        if (star->active != 0) {
            star->x = arg1;
            star->y = arg2;
            star->z = arg3;
        }
    }
}

void func_8010E4C8_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star;

    if (arg0 < stars->count) {
        star = &stars->star[arg0];
        if (star->active != 0) {
            star->targetX = arg1;
            star->targetY = arg2;
            star->targetZ = arg3;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010E524_stardust_battle);

/* Pushes the object out of any nearby stars and the stardust actor. Note that
   scale holds the squared push radius until it is first reused. */
void func_8010EA04_stardust_battle(omObjData *object) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    func_800E1BA8_minigame_ObjData *data;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 radius;
    f32 height;
    f32 scale;
    s32 retries;
    s32 i;

    if (D_80114B2C_stardust_battle == NULL || D_80114B18_stardust_battle == NULL) {
        return;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    data = object->data;
    radius = (data->unk48 + 50.0) * 0.699999988079071;
    height = data->unk34 * 0.7f;
    scale = radius * radius;
    retries = 16;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active == 0 || star->state == 4 || star->state == 5) {
            continue;
        }
        dx = star->x - object->trans.x;
        dy = star->y - object->trans.y;
        dz = star->z - object->trans.z;
        dist = dx * dx + dz * dz;
        if (dist < scale && (dy > -50.0 && dy < height)) {
            dist = sqrtf(dist);
            if (dist != 0.0f) {
                scale = radius / dist;
            } else {
                dz = radius;
                scale = 1.0f;
            }
            object->trans.x = star->x - dx * scale;
            object->trans.z = star->z - dz * scale;
            if (retries != 0) {
                retries--;
                star = stars->star;
                i = 0;
            }
        }
    }
    dx = D_80114B18_stardust_battle->trans.x - object->trans.x;
    dz = D_80114B18_stardust_battle->trans.z - object->trans.z;
    dy = D_80114B18_stardust_battle->trans.y + 34.99999940395355 - object->trans.y;
    dist = dx * dx + dz * dz;
    radius = (data->unk48 + 85.00000238418579) * 0.699999988079071;
    scale = radius * radius;
    if (dist < scale && (dy > -150.0 && dy < height)) {
        dist = sqrtf(dist);
        if (dist != 0.0f) {
            scale = radius / dist;
        } else {
            dz = radius;
            dx = 0.0f;
            scale = 1.0f;
        }
        object->trans.x = D_80114B18_stardust_battle->trans.x - dx * scale;
        object->trans.z = D_80114B18_stardust_battle->trans.z - dz * scale;
    }
}

void func_8010ED7C_stardust_battle(void) {
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    s32 i;

    if (D_80114B2C_stardust_battle == NULL) {
        return;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active != 0) {
            Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, star->x, star->y, star->z), 2.0f, 2.0f,
                              2.0f);
            func_8010DF70_stardust_battle(i);
        }
    }
}

u16 func_8010EE38_stardust_battle(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    u16 anim = HuSprAnimRead(data);

    DataClose(data);
    return anim;
}

void func_8010EE7C_stardust_battle(void) {
    UnkStardustBattleScoreDisp *disp;
    s32 sprGrp;
    s32 i;
    s32 j;

    disp = D_80114B44_stardust_battle = HuMemAllocTag(sizeof(UnkStardustBattleScoreDisp) * 2, TAG_OVERLAY);
    memset(disp, 0, sizeof(UnkStardustBattleScoreDisp) * 2);
    D_80114B34_stardust_battle = omAddObj(29, 0, 0, -1, func_8010F0E8_stardust_battle);
    D_80114B34_stardust_battle->work[2] = 0;
    for (i = 0; i < 2; i++, disp++) {
        disp->active = 1;
        disp->sprGrp = -1;
        disp->state = 0;
        disp->timer = 0;
        disp->unk_0C = 1.0f;
        disp->scale = 1.0f;
        disp->x = disp->y = 0;
        if (!D_80114AC0_stardust_battle && i == 1) {
            disp->active = 0;
            continue;
        }
        D_80114B30_stardust_battle[i + 3] = func_8010EE38_stardust_battle(D_80113ED0_stardust_battle[i]);
        disp->sprGrp = sprGrp = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            HuSprPosSet(sprGrp, j, D_80113CE0_stardust_battle[j], D_80113CF0_stardust_battle[i]);
            HuSprGrpMemberSet(sprGrp, j, D_80114B30_stardust_battle[i + 3], 0);
            func_80054FF8_main(sprGrp, j, 0);
            HuSprAttrSet(sprGrp, j, 0x1000);
            func_800550F4_main(sprGrp, j, 0);
        }
        HuSprAttrSet(sprGrp, 0, 0x8000);
        func_80054FF8_main(sprGrp, 2, 10);
        func_80054FF8_main(sprGrp, 5, 11);
    }
    func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
    if (D_80114AC0_stardust_battle != 0) {
        func_8010F400_stardust_battle(1, D_80114AB4_stardust_battle);
    }
}

void func_8010F0E8_stardust_battle(omObjData *object) {
    UnkStardustBattleScoreDisp *disp = D_80114B44_stardust_battle;
    u8 *digits;
    f32 scale;
    s32 center;
    s32 i;
    s32 j;
    s32 sprGrp;

    if (object->work[2] != 0) {
        object->work[2]--;
    }
    for (i = 0; i < 2; i++, disp++) {
        if (disp->active == 0) {
            continue;
        }
        sprGrp = disp->sprGrp;
        digits = D_80114B38_stardust_battle[i];
        switch (disp->state) {
            case 0:
                break;
            case 1:
                disp->scale = sindf(disp->timer / 15.0f * 180.0f) + 1.0f;
                if (disp->timer >= 15) {
                    disp->scale = 1.0f;
                    disp->state = 0;
                }
                scale = disp->scale;
                center = disp->x + D_80113CE0_stardust_battle[3] + 6;
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(sprGrp, j, disp->x + (center + (D_80113CE0_stardust_battle[j] - center) * scale),
                                disp->y + D_80113CF0_stardust_battle[i]);
                    HuSprScaleSet(sprGrp, j, scale, scale);
                }
                break;
            case 2:
                disp->x -= 3;
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(sprGrp, j, disp->x + D_80113CE0_stardust_battle[j], disp->y + D_80113CF0_stardust_battle[i]);
                }
                if (disp->x < -74) {
                    disp->state = 0;
                }
                break;
        }
        for (j = 0; j < 6; j++) {
            if (digits[j] >= 10) {
                digits[j] = 9;
            }
            func_80054FF8_main(sprGrp, D_80113ED8_stardust_battle[j], digits[j]);
        }
        disp->timer++;
    }
}

/* Splits a frame count into minutes, seconds and hundredths, stored as the
   decimal digits of a time display. */
void func_8010F400_stardust_battle(s16 index, s32 frames) {
    u8 *digits = D_80114B38_stardust_battle[index];
    s32 parts[3];

    parts[0] = parts[1] = parts[2] = 0;
    digits[0] = digits[1] = digits[2] = digits[3] = digits[4] = digits[5] = 0;
    while (frames >= 1800) {
        frames -= 1800;
        parts[0]++;
    }
    while (frames >= 30) {
        parts[1]++;
        frames -= 30;
    }
    parts[2] = frames * (1.0f / 30.0f) * 99.0f;
    while (parts[0] >= 10) {
        parts[0] -= 10;
        digits[0]++;
    }
    digits[1] = parts[0];
    while (parts[1] >= 10) {
        parts[1] -= 10;
        digits[2]++;
    }
    digits[3] = parts[1];
    while (parts[2] >= 10) {
        parts[2] -= 10;
        digits[4]++;
    }
    digits[5] = parts[2];
}

void func_8010F580_stardust_battle(s16 index) {
    D_80114B44_stardust_battle[index].state = 1;
    D_80114B44_stardust_battle[index].timer = 0;
}

void func_8010F5B0_stardust_battle(s16 index) {
    D_80114B44_stardust_battle[index].state = 2;
    D_80114B44_stardust_battle[index].timer = 0;
}

void func_8010F5E0_stardust_battle(void) {
    HuSprite_Unk84_Struct *sprite;
    UnkStardustBattleEffect *effect;
    HmfModel *model;
    s32 i;

    D_80114B30_stardust_battle[1] = func_8010EE38_stardust_battle(11);
    sprite = func_80055194_main(D_80114B30_stardust_battle[1]);
    D_80114B48_stardust_battle = omAddObj(30, 0, 0, -1, func_8010F73C_stardust_battle);
    D_80114B4C_stardust_battle = effect = HuMemAllocTag(sizeof(UnkStardustBattleEffect) * 4, TAG_OVERLAY);
    for (i = 0; i < 4; i++, effect++) {
        if (i == 0) {
            effect->model = func_80112980_stardust_battle(sprite, D_80113CF4_stardust_battle.rgba);
        } else {
            effect->model =
                func_80113568_stardust_battle(sprite, D_80114B4C_stardust_battle[0].model, D_80113CF4_stardust_battle.rgba);
        }
        effect->active = 0;
        effect->color = D_80113CF4_stardust_battle;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void func_8010F73C_stardust_battle(omObjData *object) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_80114B30_stardust_battle[1]);
    UnkStardustBattleEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_80114B4C_stardust_battle; i < 4; i++, effect++) {
        if (effect->active == 0) {
            continue;
        }
        model = &Hu3DData[effect->model];
        if (model->attr & 4) {
            continue;
        }
        effect->pos.x += effect->vel.x;
        effect->pos.y += effect->vel.y;
        effect->pos.z += effect->vel.z;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        func_8011376C_stardust_battle(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->unk10) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_80114B30_stardust_battle[1]);
    UnkStardustBattleEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_80114B4C_stardust_battle; i < 4; i++, effect++) {
        if (effect->active != 0) {
            continue;
        }
        effect->active = 1;
        model = &Hu3DData[effect->model];
        if (pos != NULL) {
            effect->pos.x = pos->x;
            effect->pos.y = pos->y;
            effect->pos.z = pos->z;
        } else {
            effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        }
        if (vel != NULL) {
            effect->vel.x = vel->x;
            effect->vel.y = vel->y;
            effect->vel.z = vel->z;
        } else {
            effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        }
        if (scale != NULL) {
            effect->scale.x = scale->x;
            effect->scale.y = scale->y;
            effect->scale.z = scale->z;
        } else {
            effect->scale.x = effect->scale.y = effect->scale.z = 1.0f;
        }
        memcpy(effect->color.rgba, color, sizeof(UnkStardustBattleColor));
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8011376C_stardust_battle(effect->model, sprite, 0, effect->color.rgba);
        func_8001C258_main(effect->model, 4, 0);
        model->motTime = 0.0f;
        model->pos.x = effect->pos.x;
        model->pos.y = effect->pos.y;
        model->pos.z = effect->pos.z;
        model->scale.x = effect->scale.x;
        model->scale.y = effect->scale.y;
        model->scale.z = effect->scale.z;
        return i;
    }
    return -1;
}

void func_8010FA60_stardust_battle(void) {
    omObjData *object;
    HmfModel *model;
    s32 count = 8;
    s32 i;
    s32 j;

    object = D_80114B50_stardust_battle = omAddObj(0x1E, 8, 0, -1, func_8010FBCC_stardust_battle);
    object->work[0] = 0;
    object->work[1] = 2;
    object->work[2] = 4;
    object->work[3] = 255;
    for (i = 0, j = 0; i < count; i++) {
        if (i >= object->work[j + 1]) {
            j++;
        }
        object->model[i] = func_8000B0A0_main(D_80113EF0_stardust_battle[j], D_80113EFC_stardust_battle[i / 16] | 0x99);
        func_8001C258_main(object->model[i], 4, 4);
        model = &Hu3DData[object->model[i]];
        model->motTime = 0.0f;
        model->motSpeed = 0.0f;
        if (model->hmf->unk98 != NULL) {
            model->hmf->unk98->unk08 = 0.0f;
        }
    }
}

void func_8010FBCC_stardust_battle(omObjData *object) {
    HmfModel *model;
    s32 count = 8;
    s32 i;

    for (i = 0; i < count; i++) {
        model = &Hu3DData[object->model[i]];
        if (model->attr & 4) {
            continue;
        }
        if (D_800CCF58_main[model->motId].unk02 <= model->motTime) {
            func_8001C258_main(object->model[i], 4, 4);
            model->motTime = 0.0f;
            model->motSpeed = 0.0f;
            if (model->hmf->unk98 != NULL) {
                model->hmf->unk98->unk08 = 0.0f;
            }
        }
    }
}

/* Activates the first free model of the given group in the D_80114B50 object
   and returns its index, or -1 if none are free. */
s32 func_8010FCBC_stardust_battle(Vec *pos, Vec *rot, f32 scale, s16 group) {
    omObjData *object = D_80114B50_stardust_battle;
    HmfModel *model;
    s32 count = 8;
    s32 i;

    for (i = object->work[group]; i < count; i++) {
        if (i >= object->work[group + 1]) {
            break;
        }
        model = &Hu3DData[object->model[i]];
        if (!(model->attr & 4)) {
            continue;
        }
        func_8001C258_main(object->model[i], 4, 0);
        if (pos != NULL) {
            model->pos.x = pos->x;
            model->pos.y = pos->y;
            model->pos.z = pos->z;
        } else {
            model->pos.x = model->pos.y = model->pos.z = 0.0f;
        }
        if (rot != NULL) {
            model->rot.x = rot->x;
            model->rot.y = rot->y;
            model->rot.z = rot->z;
        } else {
            model->rot.x = model->rot.y = model->rot.z = 0.0f;
        }
        model->scale.x = model->scale.y = model->scale.z = scale;
        if (i == 0) {
            object->trans.x = model->pos.x;
            object->trans.y = model->pos.y;
            object->trans.z = model->pos.z;
            object->rot.x = model->rot.x;
            object->rot.y = model->rot.y;
            object->rot.z = model->rot.z;
            object->scale.x = model->scale.x;
            object->scale.y = model->scale.y;
            object->scale.z = model->scale.z;
        }
        model->motSpeed = 1.0f;
        return i;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_8010FE74_stardust_battle);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80110364_stardust_battle);

void func_80110758_stardust_battle(f32 x, f32 y, f32 z) {
    omObjData *obj = D_80114B58_stardust_battle;

    if (obj != NULL) {
        obj->trans.x = x;
        obj->trans.y = y;
        obj->trans.z = z;
    }
}

void func_80110780_stardust_battle(s16 arg0) {
    UnkStardustBattleStard *stard = D_80114B5C_stardust_battle;
    s32 i;

    if (stard != NULL) {
        for (i = 0; i < 16; i++, stard++) {
            if (arg0 > i) {
                stard->active = 1;
            } else {
                stard->active = 0;
            }
        }
    }
}

void func_801107C4_stardust_battle(void) {
    omObjData *obj = D_80114B58_stardust_battle;

    if (obj != NULL) {
        obj->work[0] = 1;
        obj->work[1] = 0;
    }
}

void func_801107E4_stardust_battle(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = 126.8f;
    Center.z = -0.0f;
    CRot.x = 330.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2062.0f;
    func_801115F8_stardust_battle(0);
    func_801115F8_stardust_battle(1);
    D_80114BB0_stardust_battle = 0;
    D_80114BAC_stardust_battle = 0;
    D_80114BA8_stardust_battle = 0;
    D_80114BB4_stardust_battle = 0;
    omAddObj(31, 0, 0, -1, func_80111004_stardust_battle);
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

void func_80110914_stardust_battle(void) {
    UnkStardustBattleCamera delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (D_80113F08_stardust_battle) {
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
                func_801117E4_stardust_battle(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                              delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 104,
                   D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_80113F0C_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_80113F0C_stardust_battle--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_80113F10_stardust_battle++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_80113F10_stardust_battle--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_80113F0C_stardust_battle + 20, (s16)D_80113F10_stardust_battle + 104,
                   D_800D5218_main);
            break;
        case 3:
            D_80113F08_stardust_battle = 0;
            break;
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_80113F08_stardust_battle == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_80113F08_stardust_battle++ >= 4) {
            D_80113F08_stardust_battle = 0;
        }
    }
}

#ifdef NON_MATCHING
// Register allocation: t and the case 5 sine temporary have swapped f20/f22.
void func_80111004_stardust_battle(omObjData *object) {
    f32 t = 0.0f;

    if (D_80114BAC_stardust_battle <= 0) {
        func_801119D4_stardust_battle(0);
        D_80114BB0_stardust_battle = 0;
        return;
    }
    if (D_80114BA8_stardust_battle == 0) {
        Center.x = D_80114B60_stardust_battle[0].center.x;
        Center.y = D_80114B60_stardust_battle[0].center.y;
        Center.z = D_80114B60_stardust_battle[0].center.z;
        CRot.x = D_80114B60_stardust_battle[0].rot.x;
        CRot.y = D_80114B60_stardust_battle[0].rot.y;
        CRot.z = D_80114B60_stardust_battle[0].rot.z;
        CZoom = D_80114B60_stardust_battle[0].zoom;
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
        D_80114BAC_stardust_battle = 0;
    } else {
        switch (D_80114BB4_stardust_battle) {
            case 0:
                t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
                break;
            case 1:
                t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
                t = sindf(t * 90.0f);
                break;
            case 2:
                t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
                t = sindf(t * 90.0f);
                t = t * t;
                break;
            case 3:
                if (D_80114BA8_stardust_battle >= 6) {
                    t = (f32)(D_80114BA8_stardust_battle - 5) / (f32)(D_80114BAC_stardust_battle - 5);
                    t = sindf(t * 90.0f);
                    t = t * t;
                } else {
                    t = D_80113F14_stardust_battle[5 - D_80114BA8_stardust_battle];
                }
                break;
            case 4:
                t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
                t = fabsf(sindf(sindf(t * 90.0f) * 450.0f) * t);
                break;
            case 5:
                t = (f32)D_80114BA8_stardust_battle / (f32)D_80114BAC_stardust_battle;
                t = sindf(t * 90.0f) + sindf(t * 720.0f) * 0.2f;
                break;
        }
        Center.x = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.x,
                                                 D_80114B60_stardust_battle[1].center.x);
        Center.y = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.y,
                                                 D_80114B60_stardust_battle[1].center.y);
        Center.z = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].center.z,
                                                 D_80114B60_stardust_battle[1].center.z);
        CRot.x = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.x,
                                               D_80114B60_stardust_battle[1].rot.x);
        CRot.y = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.y,
                                               D_80114B60_stardust_battle[1].rot.y);
        CRot.z = func_80111E10_stardust_battle(t, D_80114B60_stardust_battle[0].rot.z,
                                               D_80114B60_stardust_battle[1].rot.z);
        CZoom = func_80111DF8_stardust_battle(t, D_80114B60_stardust_battle[0].zoom, D_80114B60_stardust_battle[1].zoom);
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
        if (D_80114BA8_stardust_battle > 0) {
            D_80114BA8_stardust_battle--;
        } else {
            D_80114BA8_stardust_battle++;
        }
    }
    D_80114BB0_stardust_battle = 1;
    func_801119D4_stardust_battle(0);
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_80111004_stardust_battle);
#endif

void func_801115F8_stardust_battle(s32 arg0) {
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
    D_80114B60_stardust_battle[arg0].center.x = Center.x;
    D_80114B60_stardust_battle[arg0].center.y = Center.y;
    D_80114B60_stardust_battle[arg0].center.z = Center.z;
    D_80114B60_stardust_battle[arg0].rot.x = CRot.x;
    D_80114B60_stardust_battle[arg0].rot.y = CRot.y;
    D_80114B60_stardust_battle[arg0].rot.z = CRot.z;
    D_80114B60_stardust_battle[arg0].zoom = CZoom;
    D_80114B60_stardust_battle[arg0].unk_1C = D_80114B60_stardust_battle[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_801117E4_stardust_battle(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80114BA8_stardust_battle = frames - 1;
        D_80114BAC_stardust_battle = frames;
        if (x != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].center.x = x;
        } else {
            D_80114B60_stardust_battle[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].center.y = y;
        } else {
            D_80114B60_stardust_battle[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].center.z = z;
        } else {
            D_80114B60_stardust_battle[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].rot.x = rotX;
        } else {
            D_80114B60_stardust_battle[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].rot.y = rotY;
        } else {
            D_80114B60_stardust_battle[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].rot.z = rotZ;
        } else {
            D_80114B60_stardust_battle[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_80114B60_stardust_battle[0].zoom = zoom;
        } else {
            D_80114B60_stardust_battle[0].zoom = CZoom;
        }
        func_801115F8_stardust_battle(1);
    }
}

void func_801119D4_stardust_battle(s32 camIndex) {
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

f32 func_80111B28_stardust_battle(f32 arg0, f32 arg1) {
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

f32 func_80111C2C_stardust_battle(f32 target, f32 current, f32 step) {
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
    diff = target - current + 360.0;
    while (diff > 360.0f) {
        diff -= 360.0f;
    }
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

f32 func_80111DF8_stardust_battle(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 func_80111E10_stardust_battle(f32 arg0, f32 arg1, f32 arg2) {
    return func_80111C2C_stardust_battle(arg2, arg1, fabsf(func_80111B28_stardust_battle(arg2, arg1) * arg0));
}

void func_80111E70_stardust_battle(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3) {
    s32 i;

    for (i = 0; i < 16; i++) {
        arg2[i] = arg0[i] + arg3 * (arg1[i] - arg0[i]);
    }
}

f32 func_80111EB8_stardust_battle(f32 x, f32 y) {
    f32 angle = atan2df(y, x);

    if (angle < 0.0) {
        angle += 360.0;
    } else if (angle >= 360.0) {
        angle -= 360.0;
    }
    return angle;
}

void func_80111F38_stardust_battle(Vec *dir, f32 *rot) {
    *rot++ = func_80111EB8_stardust_battle(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_80111EB8_stardust_battle(dir->z, dir->x);
    *rot = 0.0f;
}

void func_80111FC0_stardust_battle(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_80111FEC_stardust_battle(omObjData *object, s32 arg1, u32 arg2) {
    StardustBattleWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

void func_80112040_stardust_battle(s16 model, const char *name, HuMtx4F *out) {
    s16 nodeMap[4];
    HmfModel *mdl = &Hu3DData[model];
    HmfData *hmf = mdl->hmf;
    s16 node = func_8002C834_main(hmf, name);
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[Hu3DData[model].motId];

    D_800D1358_main = out;
    D_800D04B4_main = nodeMap;
    D_800CD1B0_main = 0;
    if (mdl->motIdShape != 0xFF) {
        hmf->unk94 = &D_800CCF58_main[mdl->motIdShape];
        hmf->unkAC = mdl->motShapeTime;
    } else {
        hmf->unk94 = NULL;
    }
    if (mdl->motIdShift != 0xFF && mdl->unk0C != 0) {
        hmf->unk90 = &D_800CCF58_main[mdl->motIdShift];
        hmf->unkA4 = mdl->motShiftTime;
        hmf->unkA8 = (f32)mdl->unk0E / mdl->unk0C;
    } else {
        hmf->unk90 = NULL;
    }
    guMtxIdentF(D_800D5A00_main[0]);
    func_8002DFF8_main(hmf, mdl->motTime, motion, 1);
    if (hmf->unk90 != NULL) {
        func_8002EAC0_main(hmf, hmf->unkA4, hmf->unkA8);
    }
    if (hmf->unk94 != NULL) {
        func_8002DFF8_main(hmf, hmf->unkAC, hmf->unk94, 0);
    }
    D_800D138A_main = 0;
    func_80016C2C_main(hmf, 0, node);
    if (D_800CD1B0_main >= 2) {
        osSyncPrintf("Mtx Made Over\n");
    }
}

void func_80112220_stardust_battle(omObjData *object, const char *name, HuMtx4F out) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    HuMtx4F mtx;
    HuMtx4F local;

    func_8008A070_main(mtx);
    mtxTransCat(mtx, object->trans.x, object->trans.y, object->trans.z);
    mtxRotCat(mtx, 0.0f, data->unk3C, 0.0f);
    mtxScaleCat(mtx, object->scale.x, object->scale.y, object->scale.z);
    func_80112040_stardust_battle(object->model[0], name, &local);
    func_80018044_main(local, mtx, out);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_41_stardust_battle/2ED2D0", func_801122D0_stardust_battle);

void func_801127B8_stardust_battle(s16 model, s16 count, s16 buffer) {
    HmfData *hmf;
    Gfx *gfx;
    s16 index;
    s16 i;

    if (buffer != -1) {
        index = buffer;
    } else {
        index = D_800D2008_main;
    }
    hmf = Hu3DData[model].hmf;
    gfx = (hmf->unk3C->unk00 + 1)[index];
    gDPPipeSync(gfx++);
    gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk10));
    for (i = 0; i < count; i++) {
        gSPSegment(gfx++, 1, osVirtualToPhysical(&hmf->unk40[i * 10]));
        gSPDisplayList(gfx++, osVirtualToPhysical(hmf->unk3C->unk14));
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(((UnkStardustBattleGfxData *)hmf->unk3C)->unk18));
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[index + 1];
}

s32 func_80112980_stardust_battle(HuSprite_Unk84_Struct *sprite, u8 *color) {
    u8 *buffer;
    Gfx *gfx;
    Gfx *header;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    header = gfx;
    buffer = (u8 *)gfx;
    model = func_8001A894_main(0x1CC1, gfx, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_801138A0_stardust_battle(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_80114020_stardust_battle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_CULL_FRONT | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_CLD_SURF, G_RM_NOOP2);
    if (sprite->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk10 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk10, size);
    HuMemFree(buffer);
    gfx = HuMemAlloc(0x10000);
    {
        Gfx *textureHeader = gfx;
        buffer = (u8 *)gfx;
        gfx++;
        gSPTexture(textureHeader, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    }
    gDPSetTexturePersp(gfx++, G_TP_PERSP);
    if (sprite->unk1A >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->unk18 == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->unk0C);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->unk0C);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->unk18;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->unk18 & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->unk00->unk04, sprite->unk00->unk06, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
    }
    gDPPipeSync(gfx++);
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
    gSPVertex(gfx++, 0x01000000, 4, 0);
    gSP2Triangles(gfx++, 0, 1, 2, 0, 1, 3, 2, 0);
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    data->unk3C->unk14 = HuMemAllocTag(size, data->unk0E);
    bcopy(buffer, data->unk3C->unk14, size);
    HuMemFree(buffer);
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

s32 func_80113568_stardust_battle(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color) {
    HmfModel *srcModel = Hu3DData + model;
    HmfData *srcData = srcModel->hmf;
    HmfData *data;
    Gfx *gfx;
    s32 newModel;
    s32 i;

    newModel = func_8001A894_main(srcModel->attr, NULL, 4);
    data = Hu3DData[newModel].hmf;
    data->unk60->unk50 = srcData->unk60->unk50;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    data->unk3C->unk10 = srcData->unk3C->unk10;
    data->unk3C->unk14 = srcData->unk3C->unk14;
    for (i = 0; i < D_800D1FF0_main; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return newModel;
}

void func_8011376C_stardust_battle(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->unk00[frame].unk00));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s32 func_801138A0_stardust_battle(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
    s32 capacity = 0x1000;
    s32 width, height, scaledWidth, scaledHeight;
    s32 size, slices, textureHeight, sliceHeight, vertexCount;
    s32 i, j;
    Vtx_t *vertices, *start;

    if (sprite->unk1A >= 2) {
        capacity = 0x800;
    }
    width = sprite->unk00->unk04;
    height = sprite->unk00->unk06;
    scaledWidth = width * 100.0 * scale / 32.0;
    scaledHeight = height * 100.0 * scale / 32.0;
    if ((sprite->unk18 & 0xFFF) == 4) {
        size = ((width + 1) & 0xFFFE) * height * 4;
    } else {
        size = width * height * sprite->unk18;
    }
    size /= 8;
    slices = size / capacity;
    if (slices <= 0) {
        slices = 1;
    }
    textureHeight = height / slices;
    sliceHeight = scaledHeight / slices;
    vertexCount = slices * 4;
    size = slices * 4 * sizeof(Vtx_t);
    start = vertices = HuMemAllocTag(size, data->unk0E);
    memset(start, 0, size);
    for (i = 0; i < slices; i++, vertices += 4) {
        vertices[0].ob[0] = scaledWidth * 0.5;
        vertices[0].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[0].tc[0] = (width - 1) << 6;
        vertices[0].tc[1] = 0;
        vertices[1].ob[0] = scaledWidth * 0.5;
        vertices[1].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[1].tc[0] = (width - 1) << 6;
        vertices[1].tc[1] = (textureHeight - 1) << 6;
        vertices[2].ob[0] = -(scaledWidth * 0.5);
        vertices[2].ob[1] = scaledHeight * 0.5 - sliceHeight * i;
        vertices[2].tc[0] = 0;
        vertices[2].tc[1] = 0;
        vertices[3].ob[0] = -(scaledWidth * 0.5);
        vertices[3].ob[1] = scaledHeight * 0.5 - sliceHeight * (i + 1);
        vertices[3].tc[0] = 0;
        vertices[3].tc[1] = (textureHeight - 1) << 6;
        for (j = 0; j < 4; j++) {
            vertices[j].ob[0] += xOffset;
            vertices[j].ob[1] += yOffset;
            vertices[j].ob[2] = 0;
            vertices[j].flag = 0;
            vertices[j].cn[3] = 255;
            vertices[j].cn[0] = vertices[j].cn[1] = vertices[j].cn[2] = 0;
        }
    }
    vertices = start;
    for (i = 0; i < D_800D1FF0_main; i++) {
        Vtx_t *destination;
        Vtx_t *source;
        data->unk44[i] = HuMemAllocTag(vertexCount * sizeof(Vtx_t), data->unk0E);
        destination = (Vtx_t *)data->unk44[i];
        source = vertices;
        for (j = 0; j < vertexCount; j++) {
            *destination++ = *source++;
        }
    }
    HuMemFree(start);
    return slices;
}
