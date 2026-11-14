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
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ s16 unk_16;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
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
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
    /* 0x70 */ f32 unk_70;
} UnkStardustBattleActor; // sizeof 0x74

/* One entry of the stardust pool allocated by func_8010CB34_stardust_battle.
   The pool is indexed by UnkStardustBattleStars.count. */
typedef struct UnkStardustBattleStar {
    /* 0x00 */ s16 active;
    /* 0x02 */ s16 model[2];
    /* 0x06 */ s16 reflection[2];
    /* 0x0A */ s16 shadow;
    /* 0x0C */ s16 effect;
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

typedef struct UnkStardustBattleCamPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} UnkStardustBattleCamPreset; // sizeof 0x1C

typedef struct UnkStardustBattlePoint {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ s16 vtxCount;
    /* 0x08 */ s16 vtx[8];
    /* 0x18 */ u8 unk_18;
    /* 0x1C */ Vec normal;
    /* 0x28 */ f32 height;
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
    /* 0x06 */ char unk_06[0x02];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ s16 unk_14;
    /* 0x16 */ char unk_16[0x02];
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s16 unk_20;
    /* 0x22 */ s16 pad;
    /* 0x24 */ s16 character;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ s16 cpuDifficulty;
    /* 0x2A */ char unk_2A[0x02];
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ s16 unk_38;
    /* 0x3A */ s16 unk_3A;
    /* 0x3C */ s16 unk_3C;
    /* 0x3E */ char unk_3E[0x28];
    /* 0x66 */ s16 unk_66;
    /* 0x68 */ s16 unk_68;
    /* 0x6A */ s16 unk_6A;
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
extern s32 D_80113DFC_stardust_battle[];
extern s32 D_80113E1C_stardust_battle[];
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
extern f32 D_800EB770_minigame;
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
extern UnkStardustBattleColor D_80113EC4_stardust_battle[];
extern UnkStardustBattleCamera D_80114B60_stardust_battle[2]; // target, origin
extern s32 D_80114BA8_stardust_battle;
extern s32 D_80114BAC_stardust_battle;
extern Gfx D_80114020_stardust_battle[];
extern Vtx_t D_80114060_stardust_battle[10];
extern s16 D_800CDD6A_main;
extern s32 D_80113F08_stardust_battle;
extern s32 D_80113F0C_stardust_battle;
extern s32 D_80113F10_stardust_battle;
extern f32 D_80113F14_stardust_battle[];
extern s32 D_80114BB0_stardust_battle;
extern UnkStardustBattleCamPreset D_80113CF8_stardust_battle;
extern UnkStardustBattleCamPreset D_80113D14_stardust_battle;
extern UnkStardustBattleCamPreset D_80113D30_stardust_battle;
extern UnkStardustBattleCamPreset D_80113D68_stardust_battle;
extern s16 D_80113DE0_stardust_battle;
extern void (*D_80113DDC_stardust_battle)(); // Unprototyped: called with the object.
extern s32 D_80114BB4_stardust_battle;
extern s32 D_80114AB8_stardust_battle;
extern s32 D_80114ABC_stardust_battle;
extern UnkStardustBattleObj *D_80114AC8_stardust_battle;
extern s16 D_80113E90_stardust_battle[];
extern f32 D_80113E98_stardust_battle[];
extern s16 D_80113EA8_stardust_battle[];
extern s16 D_80113EB0_stardust_battle[];

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
void func_801065B4_stardust_battle(omObjData *object);
void func_801065D8_stardust_battle(omObjData *object);
void func_80106690_stardust_battle(void);
void func_80106A3C_stardust_battle(void);
void func_80106B60_stardust_battle(void);
void func_80106C30_stardust_battle(void);
s16 func_80107FA4_stardust_battle(void);
s16 func_80107FE8_stardust_battle(void);
void func_80108074_stardust_battle(void);
void func_801080B0_stardust_battle(void);
void func_801080EC_stardust_battle(void);
void func_8010BFE4_stardust_battle(f32 arg0, s16 arg1);
void func_8010C06C_stardust_battle(void);
void func_8010C2CC_stardust_battle(f32 arg0);
f32 func_8010C32C_stardust_battle(void);
void func_8010C38C_stardust_battle(f32 arg0);
f32 func_8010C3EC_stardust_battle(void);
void func_8010ED7C_stardust_battle(void);
void func_80108B34_stardust_battle(void);
void func_8010F5E0_stardust_battle(void);
void func_8010FA60_stardust_battle(void);
void func_80106D0C_stardust_battle(void);
void func_80106EB0_stardust_battle(omObjData *object);
void func_801073F4_stardust_battle(omObjData *object);
s16 func_80107E84_stardust_battle(s16 arg0);
void func_80107760_stardust_battle(omObjData *object, s16 noControl);
void func_80109B18_stardust_battle(omObjData *object);
void func_80109FE4_stardust_battle(omObjData *object);
void func_8010A418_stardust_battle(omObjData *object);
s16 func_8010E03C_stardust_battle(omObjData *object);
UnkStardustBattleStar *func_8010E300_stardust_battle(s16 arg0);
void func_8010E35C_stardust_battle(s16 index);
void func_8010E46C_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_8010E4C8_stardust_battle(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80111E70_stardust_battle(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3);
void func_80112220_stardust_battle(omObjData *object, const char *name, HuMtx4F out);
s16 func_8010E524_stardust_battle(omObjData *object, s16 mode, Vec *out);
s32 func_8010FCBC_stardust_battle(Vec *pos, Vec *rot, f32 scale, s16 group);
void func_80111F38_stardust_battle(Vec *dir, f32 *rot);
void func_8010EA04_stardust_battle(omObjData *object);
void func_801092F0_stardust_battle(omObjData *object);
s16 func_8010929C_stardust_battle(void);
void func_8010A74C_stardust_battle(void);
void func_8010AAC4_stardust_battle(omObjData *object);
void func_8010C538_stardust_battle(void);
void func_8010FE74_stardust_battle(s16 arg0);
void func_80110364_stardust_battle(omObjData *object);
s32 func_801122D0_stardust_battle(void);
void func_801127B8_stardust_battle(s16 model, s16 count, s16 buffer);
void func_8010CB34_stardust_battle(void);
void func_8010CE5C_stardust_battle(omObjData *object);
s32 func_8010F890_stardust_battle(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
void func_801107E4_stardust_battle(void);
void func_8010EE7C_stardust_battle(void);
Vec *func_8010CA48_stardust_battle(s16 index);
s16 func_8010DE64_stardust_battle(Vec *target, f32 speed);
void func_80110758_stardust_battle(f32 x, f32 y, f32 z);
void func_80110780_stardust_battle(s16 arg0);
void func_801107C4_stardust_battle(void);
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

void func_80105DA0_stardust_battle(omObjData *object) {
    UnkStardustBattleActor *actor = D_80114B1C_stardust_battle;
    s32 secs;

    switch (D_80114AB8_stardust_battle) {
        case -1:
            if (D_80114AA4_stardust_battle > 0) {
                D_80114BB4_stardust_battle = 0;
                func_801117E4_stardust_battle(D_80113CF8_stardust_battle.center.x, D_80113CF8_stardust_battle.center.y,
                                              D_80113CF8_stardust_battle.center.z, D_80113CF8_stardust_battle.rot.x,
                                              D_80113CF8_stardust_battle.rot.y, D_80113CF8_stardust_battle.rot.z,
                                              D_80113CF8_stardust_battle.zoom, 1);
                D_80113DE0_stardust_battle = HuAudFXPlay(0x50C);
                WipeCreateIn(WIPE_TYPE_PREV, 16);
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 0:
            if (WipeStatGet() == 0 && func_80107FA4_stardust_battle() != 0) {
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 1:
            if (func_80107FE8_stardust_battle() != 0) {
                D_80114BB4_stardust_battle = 0;
                func_801117E4_stardust_battle(D_80113D14_stardust_battle.center.x, D_80113D14_stardust_battle.center.y,
                                              D_80113D14_stardust_battle.center.z, D_80113D14_stardust_battle.rot.x,
                                              D_80113D14_stardust_battle.rot.y, D_80113D14_stardust_battle.rot.z,
                                              D_80113D14_stardust_battle.zoom, 37);
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 2:
            if (D_80114BB0_stardust_battle == 0) {
                HuAudSeqPlay(0x41);
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 3:
            if (D_80114AA4_stardust_battle >= 22.5) {
                D_80114BB4_stardust_battle = 3;
                func_801117E4_stardust_battle(D_80113D30_stardust_battle.center.x, D_80113D30_stardust_battle.center.y,
                                              D_80113D30_stardust_battle.center.z, D_80113D30_stardust_battle.rot.x,
                                              D_80113D30_stardust_battle.rot.y, D_80113D30_stardust_battle.rot.z,
                                              D_80113D30_stardust_battle.zoom, 15);
                func_80107E84_stardust_battle(0);
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 4:
            if (D_80114BB0_stardust_battle == 0) {
                func_8010C1F8_stardust_battle(0, 0, 300, 0);
                HuAudFXPlay(0x511);
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 5:
            if (func_8010C3EC_stardust_battle() >= 60.0f && func_8010C32C_stardust_battle() == 1.0f) {
                func_8010C38C_stardust_battle(60.0f);
                func_8010C2CC_stardust_battle(0.0f);
            }
            if (D_80114AA4_stardust_battle == 43.0f) {
                func_8010BFE4_stardust_battle(450.0f, 30);
            }
            if (D_80114AA4_stardust_battle > 45.0f) {
                func_8010C1F8_stardust_battle(0, 60, 0, 4);
                func_8010C2CC_stardust_battle(2.0f);
                D_80114BB4_stardust_battle = 2;
                func_801117E4_stardust_battle(D_80113D68_stardust_battle.center.x, D_80113D68_stardust_battle.center.y,
                                              D_80113D68_stardust_battle.center.z, D_80113D68_stardust_battle.rot.x,
                                              D_80113D68_stardust_battle.rot.y, D_80113D68_stardust_battle.rot.z,
                                              D_80113D68_stardust_battle.zoom, 22);
                if (D_80113DE0_stardust_battle != -1) {
                    func_8004AEF0_main(D_80113DE0_stardust_battle, 22);
                    D_80113DE0_stardust_battle = -1;
                }
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 6:
            if (D_80114BB0_stardust_battle == 0) {
                GMesCreate(9);
                HuAudFXPlay(0xE);
                func_80108074_stardust_battle();
                D_80114AB8_stardust_battle++;
            }
            break;
        case 7:
            if (GMesStatGet() == 0) {
                func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
                func_800E6F0C_minigame(2);
                D_80114AB8_stardust_battle++;
            }
            break;
        case 8:
            D_80114AB0_stardust_battle++;
            func_8010F400_stardust_battle(0, D_80114AB0_stardust_battle);
            if (D_80114AB0_stardust_battle == 4470) {
                func_8010F5B0_stardust_battle(0);
                func_8010F5B0_stardust_battle(1);
            } else if (D_80114AB0_stardust_battle == 4499) {
                GMesCreate(0x1A, 31, 156, 32);
            } else if (D_80114AB0_stardust_battle >= 4500) {
                secs = 5400 - D_80114AB0_stardust_battle + 29;
                func_8003F578_main(secs / 30);
            }
            if (D_80114AB0_stardust_battle >= 5400 || D_80114ACE_stardust_battle != 0 || actor->unk_06 <= 0) {
                func_8003F5C0_main();
                GMesCreate(0x14);
                func_800E6F0C_minigame(3);
                func_8010C06C_stardust_battle();
                func_8010ED7C_stardust_battle();
                HuAudSeqFadeOut(120);
                func_801080EC_stardust_battle();
                if (actor->unk_06 <= 0) {
                    D_80114ACC_stardust_battle = 0;
                    secs = (5400 - D_80114AB0_stardust_battle + 29) / 30;
                    if (secs >= 60) {
                        GwPlayer[D_80114AC8_stardust_battle->unk_20].bonusCoin = 3;
                    } else if (secs >= 40) {
                        GwPlayer[D_80114AC8_stardust_battle->unk_20].bonusCoin = 2;
                    } else if (secs >= 20) {
                        GwPlayer[D_80114AC8_stardust_battle->unk_20].bonusCoin = 1;
                    } else {
                        GwPlayer[D_80114AC8_stardust_battle->unk_20].bonusCoin = 0;
                    }
                } else {
                    GwPlayer[D_80114AC8_stardust_battle->unk_20].bonusCoin = -1;
                }
                D_80114AA4_stardust_battle = 0;
                D_80114AB8_stardust_battle++;
            }
            break;
        case 9:
            if (GMesStatGet() == 0 &&
                (func_8010C508_stardust_battle() == 12 ||
                 (D_80114AC0_stardust_battle != 0 && D_80114ACC_stardust_battle >= 0 &&
                  D_80114AB0_stardust_battle < D_80114AB4_stardust_battle))) {
                func_800E6F0C_minigame(4);
                func_801080B0_stardust_battle();
                D_80114ABC_stardust_battle = 0;
                if (D_80114AC0_stardust_battle == 0 || D_80114ACC_stardust_battle < 0 ||
                    D_80114AB0_stardust_battle >= D_80114AB4_stardust_battle) {
                    func_8010C0C8_stardust_battle();
                }
                if (D_80114AC0_stardust_battle != 0) {
                    if (D_80114ACC_stardust_battle >= 0) {
                        D_80113DDC_stardust_battle = func_80106690_stardust_battle;
                    } else {
                        D_80113DDC_stardust_battle = func_80106A3C_stardust_battle;
                    }
                } else if (D_80114ACC_stardust_battle >= 0) {
                    D_80113DDC_stardust_battle = func_80106B60_stardust_battle;
                } else {
                    D_80113DDC_stardust_battle = func_80106C30_stardust_battle;
                }
                D_80114AB8_stardust_battle++;
                D_80114AA4_stardust_battle = 0;
            }
            break;
        case 10:
            if (D_80113DDC_stardust_battle != NULL) {
                D_80113DDC_stardust_battle(object);
            }
            break;
        case 32:
        case 64:
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 16);
            HuAudSeqFadeOut(16);
            func_8004AB0C_main(16);
            HuAudFXPlay(0x509);
            D_80114AB8_stardust_battle = 99;
            D_80114AA4_stardust_battle = 0;
            break;
        case 99:
            if (WipeStatGet() == 0) {
                object->func = func_801065B4_stardust_battle;
            }
            break;
    }
    func_801065D8_stardust_battle(object);
    D_80114AA0_stardust_battle++;
    D_80114AA4_stardust_battle++;
}

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

void func_80106EB0_stardust_battle(omObjData *object) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    func_800E1BA8_minigame_ObjData *data;
    s16 player = obj->unk_20;
    s16 character;
    s16 chr;
    s32 model;
    s32 motion;
    s32 extra;
    s32 r;

    character = GwPlayer[player].chr;
    obj->character = character;
    obj->pad = GwPlayer[player].pad;
    obj->unk_26 = GwPlayer[player].stat & 1;
    obj->cpuDifficulty = GwPlayer[player].cpu_difficulty;
    chr = character;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][1];
    extra = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motion, player, 0x699, 0x1699);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = NULL;
    object->model[3] = func_8000B108_main(3, 0x1E8D);
    object->model[4] = func_8000B108_main(4, 0x1E8D);
    object->model[10] = -1;
    object->model[9] = func_8000B108_main(model | extra, 0x6BD);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 17, func_80017BB8_main(chr, 14), 1, 15);
    func_800E5A00_minigame(object, 18, func_80017BB8_main(chr, 15), 2, 0);
    func_800E5A00_minigame(object, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E5A00_minigame(object, 20, func_80017BB8_main(chr, 29), 0, 0);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 30), 1, 0);
    func_800E5A00_minigame(object, 32, func_80017BB8_main(chr, 34), 0, 0);
    func_800E5A00_minigame(object, 9, func_80017BB8_main(chr, 7), 1, 39);
    func_800E5978_minigame(object, 33, func_80017BB8_main(chr, 35), 2, 0);
    func_800E5A00_minigame(object, 34, func_80017BB8_main(chr, 36), 2, 0);
    if (chr != 5) {
        func_800E5A00_minigame(object, 5, func_80017BB8_main(chr, 142), 0, 0);
        func_800E5A00_minigame(object, 38, func_80017BB8_main(chr, 18), 0, 0);
        func_800E5A00_minigame(object, 39, func_80017BB8_main(chr, 28), 0, 0);
    } else {
        func_800E5A00_minigame(object, 5, 0xA015C, 0, 0);
        func_800E5A00_minigame(object, 38, 0xA015B, 0, 0);
        func_800E5A00_minigame(object, 39, 0xA015A, 0, 0);
    }
    chr = character;
    func_800E5A00_minigame(object, 40, func_80017BB8_main(chr, 108), 0, 0);
    func_800E5A00_minigame(object, 41, func_80017BB8_main(chr, 155), 0, 0);
    r = rand8() & 1;
    func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, D_80113E1C_stardust_battle[r]), 1, 120);
    obj->unk_18 = D_80113DFC_stardust_battle[chr] | D_80113E1C_stardust_battle[r];
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, 57), 1, 60);
    obj->unk_1C = D_80113DFC_stardust_battle[chr] | 57;
    func_800E5690_minigame(object, 0);
    func_800E149C_minigame(object, 0, 2);
    obj->unk_0C = 0;
    obj->unk_0E = 0;
    obj->unk_04 = -1;
    obj->unk_0A = 0;
    obj->unk_08 = 0;
    obj->unk_66 = -1;
    obj->unk_68 = 0;
    obj->unk_6A = 0;
    obj->unk_10 = -1;
    obj->unk_12 = 0;
    obj->unk_14 = 0;
    func_80107E84_stardust_battle(1);
    object->func = func_801073F4_stardust_battle;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_801073F4_stardust_battle(omObjData *object) {
    s16 noControl = FALSE;
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    func_800E1BA8_minigame_ObjData *data = object->data;
    u16 btnDown;
    s16 stickX;
    s16 stickY;

    if (omPauseChk() + D_800D6A90_main != 0) {
        func_8001C258_main(object->model[0], 4, 0);
        return;
    }
    if (obj->func_6C != NULL) {
        obj->func_6C(object);
    }
    btnDown = D_800D5558_main[obj->pad];
    stickX = D_800CBB6E_main[obj->pad];
    stickY = D_800D20A1_main[obj->pad];
    if (model->motIdShape == object->motion[39]) {
        D_800D5558_main[obj->pad] = 0;
        D_800CBB6E_main[obj->pad] = D_800D20A1_main[obj->pad] = 0;
    } else if (obj->unk_66 != -1) {
        D_800D5558_main[obj->pad] &= ~0x4000;
    }
    if (obj->func_70 != NULL) {
        obj->func_70(object);
    }
    func_800DDD94_minigame(object);
    if (func_800E4A90_minigame(object) & 0x8C00) {
        noControl = TRUE;
    }
    if (obj->func_74 != NULL) {
        obj->func_74(object);
    }
    D_800D5558_main[obj->pad] = btnDown;
    D_800CBB6E_main[obj->pad] = stickX;
    D_800D20A1_main[obj->pad] = stickY;
    func_80107760_stardust_battle(object, noControl);
    if (!noControl && obj->unk_14 == 0 && func_800E6E8C_minigame() == 2) {
        obj->unk_10 = func_8010E524_stardust_battle(object, 0, NULL);
        if (obj->unk_10 != -1) {
            if (obj->unk_10 == 0xFF) {
                obj->unk_14 = 90;
            } else {
                D_80114ACE_stardust_battle = 1;
            }
            data->unk40 = D_800EB770_minigame;
            data->unk38 = -(D_800EB744_minigame * 0.65f);
            func_800E5690_minigame(object, 9);
        }
        func_8010EA04_stardust_battle(object);
    }
    func_801092F0_stardust_battle(object);
    if (func_8010929C_stardust_battle() == 1) {
        func_8001C258_main(object->model[1], 4, 4);
    }
    obj->unk_2C = object->trans.x;
    obj->unk_30 = object->trans.y;
    obj->unk_34 = object->trans.z;
    if (obj->unk_14 != 0) {
        if (obj->unk_0A & 1) {
            func_8001C258_main(object->model[0], 4, 4);
        } else {
            func_8001C258_main(object->model[0], 4, 0);
        }
        if (--obj->unk_14 == 0) {
            func_8001C258_main(object->model[0], 4, 0);
        }
    }
    obj->unk_0A++;
}

void func_80107760_stardust_battle(omObjData *object, s16 noControl) {
    UnkStardustBattleObj *obj = (UnkStardustBattleObj *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[0]];
    func_800E1BA8_minigame_ObjData *data = object->data;
    UnkStardustBattleStar *star;
    HuMtx4F mtx;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    s16 time;
    s16 item;

    if (func_800E6E8C_minigame() == 2 && noControl == 0) {
        item = obj->unk_66;
        switch (item) {
            case -1:
                if (data->unk5C != 64) {
                    break;
                }
                time = Hu3DData[object->model[0]].motTime;
                if (Hu3DData[object->model[0]].motIdShift != 0xFF || time < 10.0f || time > 20.0f) {
                    break;
                }
                obj->unk_66 = func_8010E03C_stardust_battle(object);
                if (obj->unk_66 != item) {
                    func_80112220_stardust_battle(object, "item_hook", mtx);
                    obj->unk_6A = 1;
                    obj->unk_68 = 0;
                }
                break;
            case -2:
                if (model->motShapeTime >= D_800CCF58_main[model->motIdShape].unk02) {
                    Hu3DData[object->model[0]].motIdShape = 0xFF;
                    obj->unk_66 = -1;
                }
                break;
            default:
                func_80112220_stardust_battle(object, "item_hook", mtx);
                if (obj->unk_6A < 5) {
                    t = obj->unk_6A / 5.0f;
                    if (t < 0.0f) {
                        t = 0.0f;
                    } else if (t > 1.0f) {
                        t = 1.0f;
                    }
                    star = func_8010E300_stardust_battle(obj->unk_66);
                    if (star != NULL) {
                        x = func_80111DF8_stardust_battle(t, star->unk_58, mtx[3][0]);
                        y = func_80111DF8_stardust_battle(t, star->unk_5C, mtx[3][1]);
                        z = func_80111DF8_stardust_battle(t, star->unk_60, mtx[3][2]);
                        func_80111DF8_stardust_battle(t, 0.0f, data->unk3C);
                        func_8010E46C_stardust_battle(obj->unk_66, x, y, z);
                        mtx[3][0] = mtx[3][1] = mtx[3][2] = 0.0f;
                        func_80111E70_stardust_battle((f32 *)D_80114AD0_stardust_battle, (f32 *)mtx,
                                                      (f32 *)Hu3DData[star->model[star->unk_10]].mtx, t);
                        func_8010E4C8_stardust_battle(obj->unk_66, 0.0f, 0.0f, 0.0f);
                    } else {
                        func_8010E46C_stardust_battle(obj->unk_66, mtx[3][0], mtx[3][1], mtx[3][2]);
                        func_8010E4C8_stardust_battle(obj->unk_66, 0.0f, data->unk3C, 0.0f);
                        obj->unk_6A = 5;
                    }
                    obj->unk_6A++;
                } else {
                    func_8010E46C_stardust_battle(obj->unk_66, mtx[3][0], mtx[3][1], mtx[3][2]);
                    star = func_8010E300_stardust_battle(obj->unk_66);
                    if (star != NULL) {
                        mtx[3][0] = mtx[3][1] = mtx[3][2] = 0.0f;
                        func_8002367C_main(Hu3DData[star->model[star->unk_10]].mtx, mtx);
                        func_8010E4C8_stardust_battle(obj->unk_66, 0.0f, 0.0f, 0.0f);
                    } else {
                        func_8010E4C8_stardust_battle(obj->unk_66, 0.0f, data->unk3C, 0.0f);
                    }
                }
                if (obj->unk_68 == 0 && model->motIdShape != object->motion[38]) {
                    if (data->unk5C == 64) {
                        if ((s16)Hu3DData[object->model[0]].motTime >= 28) {
                            Hu3DMotionShapeSet(object->model[0], object->motion[38], 0);
                            obj->unk_68 = 1;
                        }
                    } else {
                        Hu3DMotionShapeSet(object->model[0], object->motion[38], 0);
                        obj->unk_68 = 1;
                    }
                }
                if (model->motIdShape == object->motion[38] && (D_800D5558_main[obj->pad] & 0x4000)) {
                    if (data->unk5C != 64) {
                        Hu3DMotionShapeSet(object->model[0], object->motion[39], 0);
                        model->motShapeSpeed = 2.0f;
                    }
                } else if (model->motIdShape == object->motion[39] &&
                           model->motShapeTime >= D_800CCF58_main[model->motIdShape].unk02 * 0.5f) {
                    func_8010E4C8_stardust_battle(obj->unk_66, 0.0f, data->unk3C, 0.0f);
                    func_8010E35C_stardust_battle(obj->unk_66);
                    obj->unk_66 = -2;
                }
                break;
        }
    } else {
        if (obj->unk_66 >= 0) {
            star = func_8010E300_stardust_battle(obj->unk_66);
            if (star != NULL) {
                Hu3DModelScaleSet(func_8000D550_main(D_80114B54_stardust_battle, star->x, star->y, star->z), 2.0f, 2.0f,
                                  2.0f);
                func_8010DF70_stardust_battle(obj->unk_66);
            }
            obj->unk_66 = -1;
        }
        if (model->motIdShape != 0xFF) {
            Hu3DData[object->model[0]].motIdShape = 0xFF;
        }
    }
}

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

/* Scrolls the texture coordinates of one of the model's objects. */
void func_80108EC4_stardust_battle(s16 model, f32 u, f32 v, s32 width, s32 height, s16 index) {
    HmfData *hmf = Hu3DData[model].hmf;
    u16 wrapU;
    u16 wrapV;
    Vtx *src;
    Vtx *dst;
    u16 count;
    u16 du;
    u16 dv;
    s16 i;

    if (hmf != NULL) {
        count = hmf->unk60[index].unk2A;
        src = &hmf->unk40[hmf->unk60[index].unk28];
        dst = &hmf->unk44[D_800D2008_main][hmf->unk60[index].unk28];
        wrapU = width << 5;
        wrapV = height << 5;
        du = u * 32.0f;
        dv = v * 32.0f;
        if (u < 0.0f) {
            u = -u;
        }
        if (v < 0.0f) {
            v = -v;
        }
        if (u * 32.0f > wrapU) {
            du %= wrapU;
        }
        if (v * 32.0f > wrapV) {
            dv %= wrapV;
        }
        for (i = 0; i < (s16)count; src++, i++, dst++) {
            dst->v.tc[0] = du + src->v.tc[0];
            dst->v.tc[1] = dv + src->v.tc[1];
        }
    }
}

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

void func_80109424_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    HmfModel *model = &Hu3DData[object->model[1]];
    HmfData *hmf = model->hmf;
    UnkStardustBattlePoint *points;
    Vtx *vtx;
    f32 inv;
    f32 t;
    f32 s;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 x;
    f32 z;
    f32 angle;
    s32 i;
    s32 j;

    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.5f);
    func_800E1310_minigame(object, 8.0f);
    func_8001C954_main(object->model[1]);
    func_8001EFEC_main(object->model[1], "co_y02_DEF");
    hmf->unk60->unk50 |= 0x8000000;
    points = HuMemAlloc(hmf->unk18 * sizeof(UnkStardustBattlePoint));
    memset(points, 0, hmf->unk18 * sizeof(UnkStardustBattlePoint));
    vtx = hmf->unk40;
    stage->unk_20 = 0;
    for (i = 0; i < hmf->unk18; i++, vtx++) {
        for (j = 0; j < stage->unk_20; j++) {
            if (points[j].x != vtx->v.ob[0]) {
                continue;
            }
            if (points[j].y != vtx->v.ob[1]) {
                continue;
            }
            if (points[j].z != vtx->v.ob[2]) {
                continue;
            }
            if (points[j].vtxCount < 8) {
                points[j].vtx[points[j].vtxCount] = i;
                points[j].vtxCount++;
            } else {
                osSyncPrintf("VTX OVER %d \n", i);
            }
            break;
        }
        if (j < stage->unk_20) {
            continue;
        }
        points[stage->unk_20].x = vtx->v.ob[0];
        points[stage->unk_20].y = vtx->v.ob[1];
        points[stage->unk_20].z = vtx->v.ob[2];
        points[stage->unk_20].vtxCount = 1;
        points[stage->unk_20].vtx[0] = i;
        t = sqrtf(vtx->v.ob[0] * vtx->v.ob[0] + vtx->v.ob[2] * vtx->v.ob[2]);
        if (t != 0.0f) {
            inv = 1.0f / t;
        } else {
            inv = 0.0f;
        }
        t = t / 600.0;
        if (t >= 1.0f) {
            t = 1.0f;
        }
        s = sindf(t * 90.0f);
        nx = points[stage->unk_20].x * inv * s * 128.0f;
        nz = points[stage->unk_20].z * inv * s * 128.0f;
        ny = (1.0f - s) * 128.0f;
        t = sqrtf(nx * nx + ny * ny + nz * nz);
        if (t != 0.0f) {
            nx /= t;
            ny /= t;
            nz /= t;
        }
        points[stage->unk_20].normal.x = 0.0f;
        points[stage->unk_20].normal.y = 1.0f;
        points[stage->unk_20].normal.z = 0.0f;
        points[stage->unk_20].height = 0.0f;
        if (sqrtf(points[stage->unk_20].x * points[stage->unk_20].x +
                  points[stage->unk_20].z * points[stage->unk_20].z) > 525.0) {
            points[stage->unk_20].unk_18 = 1;
        } else {
            points[stage->unk_20].unk_18 = 0;
        }
        stage->unk_20++;
    }
    stage->unk_24 = HuMemAllocTag(stage->unk_20 * sizeof(UnkStardustBattlePoint), TAG_OVERLAY);
    memcpy(stage->unk_24, points, stage->unk_20 * sizeof(UnkStardustBattlePoint));
    HuMemFree(points);
    func_80109FE4_stardust_battle(object);
    angle = 0.0f;
    for (i = 0; i < 8; i++) {
        x = (f32)(rand8() % 100) * 0.01 * 100.0;
        z = (f32)(rand8() % 100) * 0.01 * 100.0;
        func_8010A04C_stardust_battle(x, z, 31.25f, 7.5000005f, 1.0f, angle);
        angle += 120.000004768371582;
    }
    stage->func_30 = func_80109B18_stardust_battle;
}

void func_80109B18_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
    UnkStardustBattlePoint *point = stage->unk_24;
    HmfModel *model = &Hu3DData[object->model[1]];
    Vtx *vtx = model->hmf->unk44[D_800D2008_main];
    UnkStardustBattleStreak *streak;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 wave;
    f32 best;
    f32 bestDx;
    f32 bestDz;
    f32 scale;
    f32 nx;
    f32 nz;
    s16 y;
    s32 i;
    s32 j;

    if (omPauseChk() + D_800D6A90_main == 0) {
        func_8010A418_stardust_battle(object);
    }
    if (stage->unk_24 == NULL) {
        return;
    }
    for (i = 0; i < stage->unk_20; i++, point++) {
        point->height = 50.0f;
        bestDx = bestDz = best = wave = 0.0f;
        streak = stage->streaks;
        if (streak != NULL) {
            for (j = 0; j < 64; j++, streak++) {
                if (streak->active == 0) {
                    continue;
                }
                dx = point->x - streak->x;
                dz = point->z - streak->z;
                dist = dx * dx + dz * dz;
                if (streak->unk_28 < dist) {
                    continue;
                }
                if (dist < streak->unk_2C) {
                    continue;
                }
                dist = sqrtf(dist) - streak->unk_10;
                if (fabs(dist) > streak->unk_34) {
                    continue;
                }
                scale = dist * streak->unk_38;
                wave = cosdf(scale * 180.0f);
                scale = (wave + 1.0f) * 0.5f;
                if (fabs(scale) > fabs(best)) {
                    best = scale;
                    bestDx = dx;
                    bestDz = dz;
                }
                scale *= streak->unk_24;
                if (point->height < scale) {
                    point->height = scale;
                }
            }
        }
        if (best != 0.0f) {
            wave = fabs(wave) * (point->height * 0.008);
            scale = 1.0f - wave;
            dist = sqrtf(bestDx * bestDx + bestDz * bestDz);
            if (dist != 0.0f) {
                dist = 1.0f / dist;
            } else {
                dist = 1.0f;
                bestDx = 0.0f;
                bestDz = -1.0f;
            }
            dist *= scale;
            if (best < 0.0f) {
                dist = -dist;
            }
            nx = bestDx * dist;
            nz = bestDz * dist;
        } else {
            nx = point->normal.x;
            wave = point->normal.y;
            nz = point->normal.z;
        }
        if (point->unk_18 != 0) {
            y = 15;
        } else {
            y = point->y + point->height;
        }
        for (j = 0; j < point->vtxCount; j++) {
            vtx[point->vtx[j]].n.ob[1] = y;
            vtx[point->vtx[j]].n.n[0] = nx * 127.0f;
            vtx[point->vtx[j]].n.n[1] = wave * 127.0f;
            vtx[point->vtx[j]].n.n[2] = nz * 127.0f;
        }
    }
}

void func_80109F94_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);

    if (stage->unk_24 != NULL) {
        HuMemFree(stage->unk_24);
    }
    stage->unk_24 = NULL;
    func_8010A5A4_stardust_battle(object);
}

void func_80109FE4_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
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

void func_8010A418_stardust_battle(omObjData *object) {
    UnkStardustBattleStage *stage = (UnkStardustBattleStage *)func_80111FEC_stardust_battle(object);
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

void func_8010A74C_stardust_battle(void) {
    omObjData *object;
    UnkStardustBattleActor *actor;

    object = D_80114B18_stardust_battle = omAddObj(1, 4, 2, -1, func_8010AAC4_stardust_battle);
    actor = D_80114B1C_stardust_battle = HuMemAllocTag(sizeof(UnkStardustBattleActor), TAG_OVERLAY);
    memset(actor, 0, sizeof(UnkStardustBattleActor));
    func_80111FC0_stardust_battle(object, (u32)actor);
    object->model[0] = func_8000B108_main(0xA0122, 0x1AA8);
    func_8008A070_main(Hu3DData[object->model[0]].mtx);
    mtxTransCat(Hu3DData[object->model[0]].mtx, 0.0f, 90.0f, 0.0f);
    func_800461B4_main(object->model[0]);
    func_800465A8_main(object->model[0], 0.0f, 0.0f, 1.0f);
    object->model[1] = func_8000B108_main(0, 0x149D);
    object->model[2] = func_8000B108_main(0xA0122, 0x688);
    func_8001C258_main(object->model[2], 4, 4);
    func_800461B4_main(object->model[2]);
    mtxRotCat(Hu3DData[object->model[2]].mtx, 180.0f, 0.0f, 0.0f);
    mtxRotCat(Hu3DData[object->model[2]].mtx, 0.0f, 180.0f, 0.0f);
    mtxTransCat(Hu3DData[object->model[2]].mtx, 0.0f, 90.0f, 0.0f);
    object->motion[0] = func_8000B108_main(0xA012C, 0x18);
    object->motion[1] = func_8000B108_main(0xA0128, 0x18);
    func_8010FE74_stardust_battle(16);
    func_8010C538_stardust_battle();
    actor->active = 0;
    actor->unk_02 = 0;
    actor->unk_04 = 0;
    actor->unk_06 = D_80114B24_stardust_battle;
    actor->unk_0C = 0;
    actor->unk_0E = 0;
    actor->unk_24 = 0;
    actor->unk_18 = 0;
    actor->unk_1C = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
    actor->unk_20 = 0;
    actor->unk_10 = 45;
    actor->unk_12 = 32;
    actor->unk_14 = 0;
    actor->unk_16 = 0;
    actor->unk_08 = 0;
    actor->unk_0A = 0;
    actor->unk_24 = 0;
    actor->unk_26 = 0;
    actor->velX = actor->velY = actor->velZ = 0.0f;
    actor->target.x = actor->target.y = actor->target.z = 0.0f;
    actor->start.x = actor->start.y = actor->start.z = 0.0f;
    actor->unk_4C = actor->unk_50 = actor->unk_54 = 0.0f;
    actor->unk_58 = 0.0f;
    actor->unk_5C = actor->unk_60 = actor->unk_64 = 0.0f;
    actor->unk_68 = 0.0f;
    actor->unk_6C = 0.0f;
    actor->unk_70 = 1.0f;
    object->trans.x = 0.0f;
    object->trans.z = 0.0f;
    object->trans.y = 600.0f;
}

void func_8010AAC4_stardust_battle(omObjData *object) {
    UnkStardustBattleActor *actor = (UnkStardustBattleActor *)func_80111FEC_stardust_battle(object);
    Vec effectPos;
    Vec hitDir;
    Vec prevPos;
    f32 x;
    f32 z;
    f32 amp;
    f32 t;
    s16 interval;

    if (actor->unk_24 != 0) {
        object->trans.y += actor->velY;
        actor->unk_24--;
    }

    prevPos.x = object->trans.x;
    prevPos.y = object->trans.y;
    prevPos.z = object->trans.z;
    (void)prevPos; // Copied but never read in the original.

    switch (actor->unk_04) {
        case 0:
            if (func_800E6E8C_minigame() == 2) {
                actor->active = 0;
                actor->unk_04 = 1;
            }
            break;
        case 1:
            if (actor->active > 30) {
                actor->active = 0;
                if (D_80114AB0_stardust_battle < 5340) {
                    actor->unk_04 = 2;
                }
            }
            break;
        case 2:
            if (actor->active > 30) {
                amp = 1.0f - (actor->active - 30) / 15.0f;
            } else {
                if (actor->active == 1) {
                    HuAudFXPlay(0x508);
                }
                amp = 1.0f;
            }
            object->rot.z = sindf(fmod(actor->active * 25.0f, 360.0)) * amp * 30.0f;
            if (actor->active > 45.0f) {
                object->rot.z = 0.0f;
                actor->active = 0;
                actor->unk_04 = 3;
            }
            break;
        case 3:
            if (actor->unk_14 >= D_80113EA8_stardust_battle[actor->unk_0C]) {
                if (actor->unk_12 >= 10) {
                    func_8010C5A8_stardust_battle(10, 10);
                    actor->unk_12 = 0;
                }
                func_8010DE64_stardust_battle(func_8010CA48_stardust_battle(actor->unk_12),
                                              D_80113E98_stardust_battle[actor->unk_0C]);
                HuAudFXPlay(0x50D);
                actor->unk_14 = 0;
                actor->unk_12++;
            }
            actor->unk_14++;
            x = actor->target.x - object->trans.x;
            z = actor->target.z - object->trans.z;
            actor->unk_1C = func_80111C2C_stardust_battle(atan2df(x, z), actor->unk_1C, 15.0f);
            object->trans.x += sindf(actor->unk_1C) * actor->unk_58;
            object->trans.z += cosdf(actor->unk_1C) * actor->unk_58;
            if (x * x + z * z < 22500.0) {
                // Pick a new target; z is reused as the angle and x as the distance.
                z = ((rand8() << 8) | rand8()) % 360;
                x = fmod((f32)((rand8() << 8) | rand8()), 400.0) + 100.0;
                actor->target.x = sindf(z) * x;
                actor->target.z = cosdf(z) * x;
            }
            if (actor->active > 150.0f) {
                if (actor->unk_58 > 0.0f) {
                    actor->unk_58 -= 0.999999977648258209;
                    if (actor->unk_58 <= 0.0f) {
                        actor->unk_58 = 0.0f;
                        func_8010BFE4_stardust_battle(100.0f, 60);
                        actor->unk_0A = 1;
                        actor->active = 0;
                        actor->unk_04 = 4;
                    }
                }
            } else if (actor->unk_58 < 15.0000005960464478) {
                actor->unk_58 += 0.999999977648258209;
            }
            break;
        case 4:
            if (actor->active >= 30) {
                actor->active = 0;
                actor->unk_04 = 5;
            }
            break;
        case 5:
            if (actor->unk_24 == 0) {
                if (actor->active >= actor->unk_10) {
                    func_8010BFE4_stardust_battle(450.0f, 60);
                    actor->active = 0;
                    actor->unk_04 = 6;
                }
            } else {
                actor->active = 0;
            }
            break;
        case 6:
            if (actor->unk_24 == 0) {
                z = ((rand8() << 8) | rand8()) % 360;
                x = fmod((f32)((rand8() << 8) | rand8()), 500.0);
                actor->target.x = sindf(z) * x;
                actor->target.z = cosdf(z) * x;
                actor->unk_0A = 0;
                if (actor->unk_06 <= D_80114B28_stardust_battle[actor->unk_0C]) {
                    actor->unk_0E = actor->unk_0C + 1;
                }
                actor->active = 0;
                if (actor->unk_0C != actor->unk_0E && D_80114AC4_stardust_battle != 0 &&
                    D_80114AB0_stardust_battle < 5250) {
                    HuAudFXPlay(0x50E);
                    actor->unk_04 = 8;
                } else if (D_80114AB0_stardust_battle < 5340) {
                    actor->unk_04 = 2;
                } else {
                    actor->unk_04 = 1;
                }
            }
            break;
        case 7:
            actor->unk_0A = 0;
            t = 1.0f - actor->active / 9.99f;
            object->trans.x += actor->velX;
            object->trans.z += actor->velZ;
            object->rot.z = -(sindf(actor->unk_20) * t * 45.0f);
            object->rot.x = cosdf(actor->unk_20) * t * 45.0f;
            if (actor->active & 1) {
                object->trans.x += 50.0;
            } else {
                object->trans.x -= 50.0;
            }
            if (actor->active >= 9.99f) {
                actor->unk_0A = 0;
                t = actor->unk_06 / 9.0f;
                actor->unk_68 = func_80111DF8_stardust_battle(t, 1.0f, 0.0f);
                actor->unk_70 = func_80111DF8_stardust_battle(t, 0.0f, 1.0f);
                object->rot.z = object->rot.x = 0.0f;
                actor->active = 0;
                if (actor->unk_06 != 0 && func_800E6E8C_minigame() == 2) {
                    func_8010BFE4_stardust_battle(450.0f, 30);
                    actor->unk_04 = 6;
                } else {
                    actor->unk_04 = 12;
                }
            }
            break;
        case 8:
            if (actor->active >= 15.0f) {
                if (actor->unk_18 < 45.0f) {
                    actor->unk_18 += 5.0f;
                }
                object->rot.y += actor->unk_18;
                if (object->rot.y > 360.0f) {
                    object->rot.y -= 360.0f;
                }
                if (actor->active >= 45.0f) {
                    WipeColorSet(255, 255, 255);
                    WipeCreateOut(11, 30);
                    actor->active = 0;
                    actor->unk_04 = 9;
                    HuAudFXPlay(0x509);
                }
            }
            break;
        case 9:
            object->rot.y += actor->unk_18;
            if (object->rot.y > 360.0f) {
                object->rot.y -= 360.0f;
            }
            if (WipeStatGet() == 0) {
                func_80109128_stardust_battle(D_80113E90_stardust_battle[actor->unk_0E]);
                actor->unk_0C = actor->unk_0E;
                object->rot.y = 0.0f;
                actor->unk_18 = 0.0f;
                WipeColorSet(255, 255, 255);
                WipeCreateIn(11, 15);
                switch (actor->unk_0C) {
                    case 1:
                        HuAudFXPlay(0x50F);
                        break;
                    case 2:
                        HuAudFXPlay(0x510);
                        break;
                }
                actor->active = 0;
                actor->unk_04 = 10;
            }
            break;
        case 10:
            if (WipeStatGet() == 0) {
                actor->active = 0;
                actor->unk_04 = 1;
            }
            break;
        case 11:
            actor->unk_0A = 0;
            object->rot.x = func_80111C2C_stardust_battle(0.0f, object->rot.x, 10.0f);
            object->rot.y = func_80111C2C_stardust_battle(0.0f, object->rot.y, 10.0f);
            object->rot.z = func_80111C2C_stardust_battle(0.0f, object->rot.z, 10.0f);
            if (func_80111B28_stardust_battle(0.0f, object->rot.x) < 10.0f &&
                func_80111B28_stardust_battle(0.0f, object->rot.y) < 10.0f &&
                func_80111B28_stardust_battle(0.0f, object->rot.z) < 10.0f) {
                object->rot.x = object->rot.y = object->rot.z = 0.0f;
                actor->unk_04 = 12;
            }
            break;
        case 13:
            actor->unk_0A = 0;
            t = (f32)actor->active / actor->unk_26;
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            t = sindf(t * 90.0f);
            object->trans.x = func_80111DF8_stardust_battle(t, actor->start.x, actor->target.x);
            object->trans.y = func_80111DF8_stardust_battle(t, actor->start.y, actor->target.y);
            object->trans.z = func_80111DF8_stardust_battle(t, actor->start.z, actor->target.z);
            if (actor->active >= actor->unk_26) {
                object->trans.x = actor->target.x;
                object->trans.y = actor->target.y;
                object->trans.z = actor->target.z;
                actor->unk_26 = 0;
                actor->active = 0;
                actor->unk_04 = 14;
            }
            break;
        case 12:
        case 14:
            actor->unk_0A = 0;
            break;
        case 16:
            if (actor->active < 30) {
                object->rot.x = sindf(actor->active / 30.0f * 90.0f) * 30.0f;
            } else if (actor->active > 90.0f) {
                object->rot.x = 30.0f - sindf((actor->active - 90.0f) / 30.0f * 90.0f) * 30.0f;
                if (actor->active > 120.0f) {
                    object->rot.x = 0.0f;
                    actor->active = 0;
                    actor->unk_04 = 0;
                }
            }
            break;
        case 17:
            if (actor->unk_18 < 22.5f) {
                actor->unk_18 += 5.0f;
            } else {
                actor->unk_18 = 22.5f;
            }
            object->rot.y += actor->unk_18;
            if (object->rot.y > 360.0f) {
                object->rot.y -= 360.0f;
            }
            if (actor->active & 1) {
                object->trans.y =
                    actor->unk_50 + 5.00000007450580597 + (f32)(u8)(rand8() % 100) * 0.01 * 5.00000007450580597;
            } else {
                object->trans.y =
                    actor->unk_50 - 5.00000007450580597 - (f32)(u8)(rand8() % 100) * 0.01 * 5.00000007450580597;
            }
            func_80110758_stardust_battle(actor->unk_4C, actor->unk_50 + 80.0000011920928955, actor->unk_54);
            if (actor->unk_16 <= 16) {
                if ((u16)actor->unk_16 < 4) {
                    if (actor->active >= D_80113EB0_stardust_battle[actor->unk_16]) {
                        HuAudFXPlay(0x50A);
                        actor->unk_16++;
                        actor->active = 0;
                    }
                } else if (actor->active & 1) {
                    HuAudFXPlay(0x50A);
                    actor->unk_16++;
                }
                if (actor->unk_16 < 16) {
                    func_80110780_stardust_battle(actor->unk_16);
                } else {
                    func_801107C4_stardust_battle();
                }
            }
            if ((actor->active & 7) == 0) {
                effectPos.x = actor->unk_4C + (0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 100.0 * 2.0;
                effectPos.z = actor->unk_54 + (0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 100.0 * 2.0;
                effectPos.y = actor->unk_50 + (f32)(u8)(rand8() % 100) * 0.01 * 150.0;
                Hu3DModelScaleSet(
                    func_8000D550_main(D_80114B54_stardust_battle, effectPos.x, effectPos.y, effectPos.z), 2.0f,
                    2.0f, 2.0f);
            }
            break;
    }

    if (actor->unk_0A != 0 && (actor->unk_08 = func_8010E524_stardust_battle(object, 1, &hitDir)) != -1) {
        if (actor->unk_06 != 0) {
            actor->unk_06--;
        }
        actor->unk_10 -= 4;
        if (actor->unk_10 < 15.0f) {
            actor->unk_10 = 15;
        }
        actor->unk_20 = atan2df(hitDir.x, hitDir.z);
        actor->velX = sindf(actor->unk_20) * 100.0 * 0.100100100040435791;
        actor->velZ = cosdf(actor->unk_20) * 100.0 * 0.100100100040435791;
        actor->unk_04 = 7;
        actor->active = 0;
    }

    func_800465A8_main(object->model[0], actor->unk_68, actor->unk_6C, actor->unk_70);

    x = object->trans.x;
    z = object->trans.z;
    if ((x - actor->unk_5C) * (x - actor->unk_5C) + (z - actor->unk_60) * (z - actor->unk_60) >
        100.000002980232267) {
        interval = 8;
        actor->unk_64 = func_80111C2C_stardust_battle(atan2df(x - actor->unk_5C, z - actor->unk_60), actor->unk_64, 10.0f);
        actor->unk_5C += sindf(actor->unk_64) * 100.0 * 0.0666666701436042786;
        actor->unk_60 += cosdf(actor->unk_64) * 100.0 * 0.0666666701436042786;
    } else {
        interval = 16;
    }

    if (D_80114B14_stardust_battle == 1 && func_8010929C_stardust_battle() == 1 && actor->unk_02 >= interval) {
        if (interval != 16) {
            func_8010A04C_stardust_battle(actor->unk_5C, actor->unk_60, 43.75f, 7.5000005f, 0.125f, 50.0f);
        } else {
            func_8010A204_stardust_battle(actor->unk_5C, actor->unk_60, 43.75f, 7.5000005f, 0.125f, 50.0f);
        }
        actor->unk_02 = 0;
    }

    if (func_8010929C_stardust_battle() != 1 &&
        object->trans.x * object->trans.x + object->trans.z * object->trans.z < 275625.0) {
        t = 1.0 - object->trans.y * 0.001;
        if (t < 0.2f) {
            t = 0.2f;
        }
        func_8001C258_main(object->model[1], 4, 0);
        Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
        Hu3DModelScaleSet(object->model[1], t * 1.5f, 1.0f, t * 1.5f);
    } else {
        func_8001C258_main(object->model[1], 4, 4);
    }

    if (func_8010929C_stardust_battle() == 2) {
        func_8001C258_main(object->model[2], 4, 0);
        Hu3DModelPosSet(object->model[2], object->trans.x, -object->trans.y, object->trans.z);
        Hu3DModelRotSet(object->model[2], object->rot.x, object->rot.y, object->rot.z);
        Hu3DData[object->model[2]].motId = Hu3DData[object->model[0]].motId;
        Hu3DData[object->model[2]].motTime = Hu3DData[object->model[0]].motTime;
    } else {
        func_8001C258_main(object->model[2], 4, 4);
    }

    actor->active++;
    actor->unk_02++;
}

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

void func_8010C5A8_stardust_battle(s16 count, s16 arg1) {
    UnkStardustBattleSpots *spots = D_80114B20_stardust_battle;
    UnkStardustBattleSpot *spot = spots->spot;
    f32 angle[32];
    f32 dist[32];
    s32 order[32];
    f32 tempF;
    s32 tempI;
    s32 a;
    s32 b;
    s32 i;
    s32 j;

    memset(spot, 0, sizeof(UnkStardustBattleSpot) * 32);
    spots->count = count;
    spots->unk_04 = arg1;
    if (spots->count == 0) {
        return;
    }
    for (i = 0; i < spots->count; i++) {
        angle[i] = 360.0f / spots->count * i;
    }
    for (i = 0; i < spots->count * 8; i++) {
        a = rand8() % spots->count;
        b = rand8() % spots->count;
        if (a != b) {
            tempF = angle[b];
            angle[b] = angle[a];
            angle[a] = tempF;
        }
    }
    for (i = 0; i < spots->count; i++) {
        dist[i] = 525.0 / spots->count * i;
    }
    for (i = 0; i < spots->count * 8; i++) {
        a = rand8() % spots->count;
        b = rand8() % spots->count;
        if (a != b) {
            tempF = dist[b];
            dist[b] = dist[a];
            dist[a] = tempF;
        }
    }
    for (i = 0; i < spots->count; i++) {
        order[i] = i;
    }
    for (i = 0; i < spots->count * 8; i++) {
        a = rand8() % spots->count;
        b = rand8() % spots->count;
        if (a != b) {
            tempI = order[b];
            order[b] = order[a];
            order[a] = tempI;
        }
    }
    for (i = 0; i < 32; i++, spot++) {
        if (i >= spots->count) {
            spot->active = 0;
        } else {
            for (j = 0; j < spots->unk_04; j++) {
                if (i == order[j]) {
                    spot->followPlayer = 1;
                    j = spots->unk_04;
                }
            }
            spot->active = 1;
            spot->pos.x = sindf(angle[i]) * dist[i];
            spot->pos.z = cosdf(angle[i]) * dist[i];
            spot->pos.y = 0.0f;
        }
    }
}

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
            star->reflection[0] = Hu3DModelLink(stars->modelId1);
            star->model[1] = stars->modelId2;
            star->reflection[1] = Hu3DModelLink(stars->modelId2);
            star->shadow = stars->effectId1;
        } else {
            star->model[0] = Hu3DModelLink(stars->modelId1);
            star->reflection[0] = Hu3DModelLink(stars->modelId1);
            star->model[1] = Hu3DModelLink(stars->modelId2);
            star->reflection[1] = Hu3DModelLink(stars->modelId2);
            star->shadow = Hu3DModelLink(stars->effectId1);
        }
        func_8001C258_main(star->model[0], 4, 4);
        func_8001C258_main(star->reflection[0], 4, 4);
        func_8001C258_main(star->model[1], 4, 4);
        func_8001C258_main(star->reflection[1], 4, 4);
        func_8001C258_main(star->shadow, 4, 4);
        mtxRotCat(Hu3DData[star->reflection[0]].mtx, 180.0f, 0.0f, 0.0f);
        mtxRotCat(Hu3DData[star->reflection[0]].mtx, 0.0f, 180.0f, 0.0f);
        mtxRotCat(Hu3DData[star->reflection[1]].mtx, 180.0f, 0.0f, 0.0f);
        mtxRotCat(Hu3DData[star->reflection[1]].mtx, 0.0f, 180.0f, 0.0f);
        star->effect = func_8000B108_main(0x620007, 0x189D);
        Hu3DModelScaleSet(star->effect, 0.75f, 0.75f, 0.75f);
        func_8001C954_main(star->effect);
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

void func_8010CE5C_stardust_battle(omObjData *object) {
    UnkStardustBattleStars *stars = D_80114B2C_stardust_battle;
    UnkStardustBattleStar *star = stars->star;
    Vec pos;
    Vec scale;
    f32 floorY;
    f32 temp;
    s32 mode;
    s32 done;
    s32 i;

    mode = func_8010929C_stardust_battle();
    if (mode == 1) {
        floorY = 25.0f;
    } else {
        floorY = 0.0f;
    }
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active == 0) {
            continue;
        }
        if (omPauseChk() + D_800D6A90_main != 0) {
            if (star->unk_18 != 0) {
                func_8001CAA4_main(star->effect, stars->effectId2, star->unk_68);
            }
            if (star->state == 3) {
                func_8001C258_main(star->model[star->unk_10], 4, 0);
            }
            continue;
        }
        star->unk_1C = star->x;
        star->unk_20 = star->y;
        star->unk_24 = star->z;
        done = 0;
        switch (star->state) {
            case 0:
                star->x += star->unk_40;
                star->y += star->unk_44;
                star->z += star->unk_48;
                temp = sindf((star->unk_14 & 7) * (360.0f / 7)) * 0.2f;
                Hu3DModelScaleSet(star->effect, temp + 0.75f, temp + 0.75f, temp + 0.75f);
                if (star->y <= floorY) {
                    temp = (f32)fabs((floorY - star->y) / star->unk_44);
                    star->x -= temp * star->unk_40;
                    star->z -= temp * star->unk_48;
                    star->y = floorY;
                    pos.x = star->x;
                    pos.y = star->y;
                    pos.z = star->z + 50.0;
                    scale.x = scale.y = scale.z = 1.2f;
                    func_8010F890_stardust_battle(&pos, NULL, &scale, 1.0f, D_80113EC4_stardust_battle[mode].rgba);
                    HuAudFXPlay(0x504);
                    star->state = 2;
                    star->unk_14 = 0;
                }
                break;
            case 1:
                temp = sindf((star->unk_14 & 7) * (360.0f / 7)) * 0.2f;
                Hu3DModelScaleSet(star->effect, temp + 1.0f, temp + 1.0f, temp + 1.0f);
                if (star->unk_68 < 1.0f) {
                    star->unk_68 += 0.2f;
                }
                if (star->unk_12 & 1) {
                    star->x -= fabs(star->y - 0.0f);
                    star->y = floorY;
                    if (star->unk_12 < 2) {
                        star->state = 2;
                        star->unk_14 = 0;
                    }
                } else {
                    star->x += ((f32)(u8)(rand8() % 100) * 0.01 * 0.025f + 0.025f) * 100.0;
                    star->y = floorY + ((f32)(u8)(rand8() % 100) * 0.01 * 0.025f + 0.025f) * 100.0;
                }
                star->unk_12--;
                break;
            case 2:
                if (star->unk_14 >= 30) {
                    func_8001C258_main(star->model[1], 4, 0);
                    star->unk_10 = 1;
                    star->unk_18 = 0;
                    star->state = 3;
                    star->unk_14 = 0;
                    break;
                }
                temp = 1.0f - star->unk_14 * (1.0f / 30);
                if (temp < 0.0f) {
                    temp = 0.5f;
                } else {
                    temp = temp * 0.5f + 0.5f;
                }
                temp += sindf((star->unk_14 & 7) * (360.0f / 7)) * 0.2f;
                Hu3DModelScaleSet(star->effect, temp, temp, temp);
                if (star->unk_68 < 1.0f) {
                    star->unk_68 += 0.2f;
                }
                if (star->unk_14 >= 15.0f) {
                    if (star->unk_14 & 1) {
                        func_8001C258_main(star->model[0], 4, 0);
                        star->unk_10 = 0;
                    } else {
                        func_8001C258_main(star->model[1], 4, 0);
                        star->unk_10 = 1;
                    }
                }
                break;
            case 3:
                if (star->unk_14 >= 60.0f) {
                    if (star->unk_14 & 1) {
                        func_8001C258_main(star->model[star->unk_10], 4, 4);
                    } else {
                        func_8001C258_main(star->model[star->unk_10], 4, 0);
                    }
                    if (star->unk_14 >= 90.0f) {
                        func_8010DF70_stardust_battle(i);
                        done = 1;
                    }
                }
                break;
            case 4:
                break;
            case 5:
                star->unk_44 -= 2.44995f;
                star->x += star->unk_40;
                star->y += star->unk_44;
                star->z += star->unk_48;
                if ((star->y < floorY && star->x * star->x + star->z * star->z < 330625.0) || (star->unk_1C * star->unk_1C + star->unk_24 * star->unk_24 < 330625.0 && star->x * star->x + star->z * star->z > 330625.0 && star->unk_20 < 50.0 && star->y < 50.0)) {
                    pos.x = star->x;
                    pos.z = star->z;
                    pos.y = 30.000002f;
                    func_8010FCBC_stardust_battle(&pos, NULL, 1.0f, 1);
                    func_8010FCBC_stardust_battle(&pos, NULL, 1.0f, 2);
                    func_8010DF70_stardust_battle(i);
                    done = 1;
                }
                break;
        }
        if (done) {
            continue;
        }
        func_8001C258_main(star->model[(s16)(star->unk_10 ^ 1)], 4, 4);
        func_8001C258_main(star->reflection[(s16)(star->unk_10 ^ 1)], 4, 4);
        Hu3DModelPosSet(star->model[star->unk_10], star->x, star->y, star->z);
        Hu3DModelRotSet(star->model[star->unk_10], star->targetX, star->targetY, star->targetZ);
        if (mode != 2 || star->y <= -50.0 || star->x * star->x + star->z * star->z > 275625.0) {
            func_8001C258_main(star->reflection[star->unk_10], 4, 4);
        } else {
            func_8001C258_main(star->reflection[star->unk_10], 4, 0);
            Hu3DModelPosSet(star->reflection[star->unk_10], star->x, -star->y, star->z);
            Hu3DModelRotSet(star->reflection[star->unk_10], star->targetX, star->targetY, star->targetZ);
        }
        if (star->unk_18 != 0) {
            func_8001C258_main(star->effect, 4, 0);
            Hu3DModelPosSet(star->effect, star->x, star->y + 34.99999940395355, star->z);
            star->unk_78 += 20.0f;
            if (star->unk_78 >= 360.0f) {
                star->unk_74 -= 360.0f;
            }
            Hu3DModelRotSet(star->effect, star->unk_70 + 180.0f, star->unk_74, 0.0f);
            func_8008A070_main(Hu3DData[star->effect].mtx);
            mtxRotCat(Hu3DData[star->effect].mtx, 0.0f, star->unk_78, 0.0f);
            if (star->unk_68 > 1.0f) {
                star->unk_68 = 1.0f;
            } else if (star->unk_68 < 0.0f) {
                star->unk_68 = 0.0f;
            }
            if (star->unk_68 != star->unk_6C) {
                func_8001CAA4_main(star->effect, stars->effectId2, star->unk_68);
            }
            star->unk_6C = star->unk_68;
        } else {
            func_8001C258_main(star->effect, 4, 4);
        }
        if (mode != 1 && star->x * star->x + star->z * star->z < 275625.0) {
            temp = 1.0 - star->y * 0.001;
            if (temp < 0.2f) {
                temp = 0.2f;
            }
            func_8001C258_main(star->shadow, 4, 0);
            Hu3DModelPosSet(star->shadow, star->x, 0.0f, star->z);
            Hu3DModelScaleSet(star->shadow, temp * 0.8f, 1.0f, temp * 0.8f);
        } else {
            func_8001C258_main(star->shadow, 4, 4);
        }
        if (star->y < -1000.0) {
            func_8010DF70_stardust_battle(i);
        }
        star->unk_14++;
    }
}

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
            func_8001C258_main(star->effect, 4, 0);
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
            Hu3DModelPosSet(star->reflection[0], star->x, -star->y, star->z);
            Hu3DModelPosSet(star->shadow, star->x, 0.0f, star->z);
            func_8008A070_main(Hu3DData[star->model[0]].mtx);
            func_8008A070_main(Hu3DData[star->model[1]].mtx);
            Hu3DModelPosSet(star->effect, star->x, star->y + 34.99999940395355, star->z);
            Hu3DModelScaleSet(star->effect, 0.75f, 0.75f, 0.75f);
            func_8001CAA4_main(star->effect, stars->effectId2, star->unk_68);
            Hu3DModelRotSet(star->effect, star->unk_70 + 180.0f, star->unk_74, 0.0f);
            func_8008A070_main(Hu3DData[star->effect].mtx);
            mtxRotCat(Hu3DData[star->effect].mtx, 0.0f, star->unk_78, 0.0f);
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
            func_8001C258_main(star->reflection[0], 4, 4);
            func_8001C258_main(star->reflection[1], 4, 4);
            func_8001C258_main(star->shadow, 4, 4);
            func_8001C258_main(star->effect, 4, 4);
        }
    }
}

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
    s32 index;

    if (D_80114B2C_stardust_battle == NULL) {
        return -1;
    }
    // The do-while gives stars the loop weighting needed for its register.
    do {
        stars = D_80114B2C_stardust_battle;
    } while (0);
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
    // The do-while gives index the loop weighting needed for its register.
    do {
        index = D_80114A40_stardust_battle[0].index;
    } while (0);
    star = &stars->star[index];
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

s16 func_8010E524_stardust_battle(omObjData *object, s16 mode, Vec *out) {
    func_800E1BA8_minigame_ObjData *data;
    UnkStardustBattleStars *stars;
    UnkStardustBattleStar *star;
    Vec pos;
    Vec rot;
    Vec dir;
    f32 radius;
    f32 radiusSq;
    f32 dist;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    if (D_80114B2C_stardust_battle == NULL || D_80114B18_stardust_battle == NULL) {
        return -1;
    }
    stars = D_80114B2C_stardust_battle;
    star = stars->star;
    data = object->data;
    if (mode == 0) {
        radius = (data->unk48 + 50.0) * 0.7f;
        height = data->unk34;
    } else {
        radius = 135.0f;
        height = 150.0f;
    }
    radiusSq = radius * radius;
    for (i = 0; i < stars->count; i++, star++) {
        if (star->active == 0) {
            continue;
        }
        if (mode == 0) {
            if (star->state == 3) {
                continue;
            }
            if (star->unk_18 == 0) {
                continue;
            }
            dy = star->y - object->trans.y;
        } else {
            if (star->unk_18 != 0) {
                continue;
            }
            if (star->state != 5) {
                continue;
            }
            dy = star->y + 34.9999994039535522 - object->trans.y;
        }
        dx = star->x - object->trans.x;
        dz = star->z - object->trans.z;
        if (fabs(dx) > radius) {
            continue;
        }
        if (fabs(dz) > radius) {
            continue;
        }
        dist = dx * dx + dz * dz;
        if (dist < radiusSq && ((dy > -50.0) & (dy < height))) {
            if (mode == 0) {
                pos.x = (star->x + object->trans.x) * 0.5f;
                pos.z = (star->z + object->trans.z) * 0.5f;
                pos.y = (star->y + 50.0 + object->trans.y + 100.0) * 0.5;
                func_8010FCBC_stardust_battle(&pos, NULL, 1.2f, 2);
                HuAudFXPlay(0x505);
            } else {
                pos.x = star->x;
                pos.y = star->y;
                pos.z = star->z;
                dir.x = star->unk_40;
                dir.y = star->unk_44;
                dir.z = star->unk_48;
                func_80111F38_stardust_battle(&dir, &rot.x);
                rot.x -= 90.0f;
                func_8010FCBC_stardust_battle(&pos, &rot, 1.0f, 0);
                out->x = star->unk_40;
                out->y = star->unk_44;
                out->z = star->unk_48;
                HuAudFXPlay(0x506);
                func_8010DF70_stardust_battle(i);
            }
            return i;
        }
    }
    if (mode == 0) {
        dx = D_80114B18_stardust_battle->trans.x - object->trans.x;
        dz = D_80114B18_stardust_battle->trans.z - object->trans.z;
        dy = D_80114B18_stardust_battle->trans.y + 34.9999994039535522 - object->trans.y;
        radius = (data->unk48 + 85.000002384185791) * 0.7f;
        dist = dx * dx + dz * dz;
        radiusSq = radius * radius;
        if (dist < radiusSq && ((dy > -150.0) & (dy < height))) {
            pos.x = (D_80114B18_stardust_battle->trans.x + object->trans.x) * 0.5f;
            pos.z = (D_80114B18_stardust_battle->trans.z + object->trans.z) * 0.5f;
            pos.y = (D_80114B18_stardust_battle->trans.y + 100.0 + object->trans.y + 100.0) * 0.5;
            rot.x = 90.0f;
            rot.y = atan2df(dx, dz);
            rot.z = 0.0f;
            func_8010FCBC_stardust_battle(&pos, &rot, 1.0f, 1);
            return 0xFF;
        }
    }
    return -1;
}

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

void func_8010FE74_stardust_battle(s16 arg0) {
    UnkStardustBattleStard *stard;
    omObjData *object;
    f32 angles[16];
    f32 temp;
    s32 a;
    s32 b;
    s32 i;
    s16 sprGrp;

    stard = D_80114B5C_stardust_battle = HuMemAllocTag(sizeof(UnkStardustBattleStard) * 16, TAG_OVERLAY);
    object = D_80114B58_stardust_battle = omAddObj(30, 1, 0, -1, func_80110364_stardust_battle);
    for (i = 0; i < 16; i++) {
        angles[i] = i * 22.5f;
    }
    for (i = 0; i < 512; i++) {
        a = rand8() & 0xF;
        b = rand8() & 0xF;
        if (a != b) {
            temp = angles[a];
            angles[a] = angles[b];
            angles[b] = temp;
        }
    }
    for (i = 0; i < 16; i++, stard++) {
        stard->modelId = func_801122D0_stardust_battle();
        func_8001C258_main(stard->modelId, 4, 4);
        Hu3DModelScaleSet(stard->modelId, (f32)(rand8() % 100) * 0.01 * 1.5 + 1.0 - 0.5, 1.0f, 1.0f);
        stard->angleX = rand8() % 180;
        stard->angleY = rand8() % 180;
        stard->active = 0;
        stard->radius2 = stard->radius = 20.0f;
        stard->x = (f32)(rand8() % 100) * 0.01 * 40.0 - 20.0;
        stard->y = (f32)(rand8() % 100) * 0.01 * 90.0 - 45.0;
        stard->z = angles[i] + ((f32)(rand8() % 100) * 0.01 * 10.0 - 5.0);
        stard->worldX = stard->worldY = stard->worldZ = 0.0f;
    }
    object->model[0] = func_8000B0A0_main(0x620009, 0x1839);
    func_8001C258_main(object->model[0], 4, 4);
    object->scale.x = object->scale.y = object->scale.z = 10.0f;
    D_80114B30_stardust_battle[2] = func_8010EE38_stardust_battle(0x62000B);
    object->work[3] = sprGrp = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(sprGrp, 0, D_80114B30_stardust_battle[2], 0);
    func_800550F4_main(sprGrp, 0, 0);
    func_80054FF8_main(sprGrp, 0, 0);
    HuSprPosSet(sprGrp, 0, 160, 120);
    HuSprScaleSet(sprGrp, 0, 4.0f, 4.0f);
    func_80055484_main(sprGrp, 0, 255, 255, 255, 0);
    HuSprAttrSet(sprGrp, 0, 0x20009800);
    HuSprPriSet(sprGrp, 0, 0xFFFF);
}

void func_80110364_stardust_battle(omObjData *object) {
    UnkStardustBattleStard *stard = D_80114B5C_stardust_battle;
    f32 alpha;
    s32 next;
    s32 i;

    if (stard == NULL) {
        return;
    }
    for (i = 0; i < 16; i++, stard++) {
        if (stard->active == 0) {
            continue;
        }
        stard->angleX += 5.0f;
        if (stard->angleX >= 360.0f) {
            stard->angleX -= 360.0f;
        }
        stard->angleY += 5.0f;
        if (stard->angleY >= 360.0f) {
            stard->angleY -= 360.0f;
        }
        stard->worldX = sindf(stard->angleX) * stard->radius + stard->x;
        stard->worldY = sindf(stard->angleX) * stard->radius2 + stard->y;
        stard->worldZ = stard->z;
        func_8001C258_main(stard->modelId, 4, 0);
        Hu3DModelPosSet(stard->modelId, object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelRotSet(stard->modelId, stard->worldX, stard->worldY, stard->worldZ);
    }
    switch (object->work[0]) {
        case 1:
            if (++object->work[1] >= 90.0f) {
                object->work[0]++;
                object->work[1] = 0;
                object->work[2] = 0;
                func_8001C258_main(object->model[0], 4, 0);
                object->scale.x = object->scale.y = object->scale.z = 0.1f;
            }
            break;
        case 2:
            if (object->scale.x < 40.0f) {
                object->scale.x = object->scale.y = object->scale.z += 0.5f;
                if (object->scale.x >= 25.0f && object->work[2] == 0) {
                    object->work[2] = 2;
                }
            } else {
                object->work[0]++;
                object->work[1] = 0;
            }
            break;
    }
    if (object->work[2] >= 2) {
        alpha = object->work[2] / 255.0f;
        next = object->work[2];
        HuSprAttrReset(object->work[3], 0, 0x8000);
        func_80055484_main(object->work[3], 0, 255, 255, 255, alpha * 255.0f);
        next += 10;
        if (next >= 255) {
            func_80055484_main(object->work[3], 0, 255, 255, 255, 256);
            object->work[2] = 1;
        } else {
            object->work[2] = next;
        }
    }
}

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

s32 func_801122D0_stardust_battle(void) {
    Gfx *gfx;
    u8 *buffer;
    HmfData *hmf;
    Vtx *vtx;
    Vtx_t *src;
    s32 model;
    s32 size;
    s32 i;
    s32 j;

    buffer = (u8 *)(gfx = HuMemAlloc(0x10000));
    model = func_8001A894_main(0x1CC1, buffer, 4);
    hmf = Hu3DData[model].hmf;
    hmf->unk60->unk50 |= 0x1010000;
    HuMemFree(hmf->unk3C);
    hmf->unk3C = HuMemAllocTag(sizeof(UnkStardustBattleGfxData), D_800CDD6A_main);
    hmf->unk18 = 10;
    vtx = hmf->unk40 = HuMemAllocTag(sizeof(D_80114060_stardust_battle), hmf->unk0E);
    for (j = 0, src = D_80114060_stardust_battle; j < 10; j++, vtx++, src++) {
        vtx->v = *src;
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(D_80114020_stardust_battle));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_TEXTURE_GEN_LINEAR | G_SHADING_SMOOTH);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, SHADE, 0);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
    gDPSetTextureLUT(gfx++, G_TT_NONE);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    ((UnkStardustBattleGfxData *)hmf->unk3C)->unk10 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buffer, ((UnkStardustBattleGfxData *)hmf->unk3C)->unk10, size);
    HuMemFree(buffer);

    gfx = HuMemAlloc(0x10000);
    buffer = (u8 *)gfx;
    gSPVertex(gfx++, 0x01000000, 10, 0);
    gSP1Triangle(gfx++, 0, 1, 2, 0);
    gSP1Triangle(gfx++, 1, 3, 4, 0);
    gSP1Triangle(gfx++, 2, 1, 4, 0);
    gSP1Triangle(gfx++, 2, 4, 5, 0);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    ((UnkStardustBattleGfxData *)hmf->unk3C)->unk14 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buffer, ((UnkStardustBattleGfxData *)hmf->unk3C)->unk14, size);
    HuMemFree(buffer);

    gfx = HuMemAlloc(0x10000);
    buffer = (u8 *)gfx;
    gSPClearGeometryMode(gfx++, -1);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADE | G_CULL_BACK | G_TEXTURE_GEN_LINEAR);
    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
    size = (u8 *)gfx - buffer;
    ((UnkStardustBattleGfxData *)hmf->unk3C)->unk18 = HuMemAllocTag(size, hmf->unk0E);
    bcopy(buffer, ((UnkStardustBattleGfxData *)hmf->unk3C)->unk18, size);
    HuMemFree(buffer);

    for (i = 0; i < D_800D1FF0_main; i++) {
        (hmf->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, hmf->unk0E);
        func_801127B8_stardust_battle(model, 1, i);
    }
    hmf->unk3C->unk00[0] = hmf->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

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
    model = func_8001A894_main(0x1CC1, buffer, 4);
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
