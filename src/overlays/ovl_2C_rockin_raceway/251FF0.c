#include "common.h"
#include "game/camera.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/mallocblock.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/data.h"
#include "game/util.h"
#include "game/gamework.h"
#include "game/sprite.h"
#include "math.h"
#include "game/hmfmath.h"
#include "humath.h"
#include "game/input.h"
#include "game/printfunc.h"

#define CAMERA_KEEP 65535.0f

// Several distances are written as a float fraction of 200 units (e.g. 0.1f * 200.0), which folds into
// a double constant slightly off from the round value.

typedef struct RockinRacewayCamera {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
} RockinRacewayCamera; // Size 0x24

typedef struct RockinRacewayCameraPreset {
    /* 0x00 */ Vec center;
    /* 0x0C */ Vec rot;
    /* 0x18 */ f32 zoom;
} RockinRacewayCameraPreset; // Size 0x1C

// Table of 2 rows (RockinRacewaySnapshotRow) of 4 of these allocated in func_80106B28_rockin_raceway, stored in
// D_80111B3C_rockin_raceway. func_80107E78_rockin_raceway records each racer object's transform.
typedef struct RockinRacewaySnapshot {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 active;
    /* 0x04 */ Vec trans;
    /* 0x10 */ Vec rot;
    /* 0x1C */ Vec scale;
} RockinRacewaySnapshot; // Size 0x28

typedef struct RockinRacewaySnapshotRow {
    /* 0x00 */ RockinRacewaySnapshot racers[4];
} RockinRacewaySnapshotRow; // Size 0xA0

// Vertex quad copied into each of a model's vertex buffers by func_8010FFB8_rockin_raceway.
typedef struct RockinRacewayQuad {
    /* 0x00 */ Vtx_t vtx[4];
} RockinRacewayQuad; // Size 0x40

// Saved model state, see func_80109044_rockin_raceway and func_80109134_rockin_raceway.
typedef struct RockinRacewayModelState {
    /* 0x00 */ s32 attr;
    /* 0x04 */ f32 motTime;
    /* 0x08 */ f32 motSpeed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
} RockinRacewayModelState; // Size 0x30

// Pool of 16 of these allocated in func_80109208_rockin_raceway, stored in D_80111B5C_rockin_raceway.
// func_801094EC_rockin_raceway claims a free entry, and func_80109384_rockin_raceway animates the
// sprite effect each frame until its animation finishes.
typedef struct RockinRacewayEffect {
    /* 0x00 */ u16 active;
    /* 0x02 */ s16 model;
    /* 0x04 */ f32 frame;
    /* 0x08 */ f32 speed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec vel;
    /* 0x24 */ Vec scale;
} RockinRacewayEffect; // Size 0x30

// Per-racer state; a pointer to it is packed into the work bytes of each racer object
// (see func_8010EC0C_rockin_raceway / func_8010EC38_rockin_raceway).
typedef struct RockinRacewayRacer {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ s16 unk04; // sound handle
    /* 0x06 */ s16 unk06; // sound handle
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A; // racer slot
    /* 0x0C */ u16 unk0C; // player index
    /* 0x0E */ u16 unk0E; // character
    /* 0x10 */ u16 unk10; // is CPU
    /* 0x12 */ u16 unk12; // CPU difficulty
    /* 0x14 */ u16 unk14; // CPU mash interval
    /* 0x16 */ s16 unk16; // CPU mash timer, negative while resting
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ u16 unk1C;
    /* 0x1E */ u16 unk1E; // button mask to press next
    /* 0x20 */ u16 unk20;
    /* 0x22 */ u8 unk22[2];
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ u16 unk2C;
    /* 0x2E */ u16 unk2E; // track index
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44; // distance along the track
    /* 0x48 */ f32 unk48;
    /* 0x4C */ u16 unk4C; // track node index
    /* 0x4E */ u8 unk4E[2];
    /* 0x50 */ f32 unk50; // fraction between track nodes
    /* 0x54 */ f32 unk54;
    /* 0x58 */ Vec pos;
    /* 0x64 */ Vec rot;
} RockinRacewayRacer; // Size 0x70

// Saved sprite effect state, see func_801097A0_rockin_raceway and func_801098D8_rockin_raceway.
typedef struct RockinRacewayEffectState {
    /* 0x00 */ u16 active;
    /* 0x02 */ u16 motTime;
    /* 0x04 */ s32 attr;
    /* 0x08 */ f32 frame;
    /* 0x0C */ f32 speed;
    /* 0x10 */ Vec pos;
    /* 0x1C */ Vec rot;
    /* 0x28 */ Vec scale;
} RockinRacewayEffectState; // Size 0x34

typedef struct RockinRacewayReplayRacer {
    /* 0x00 */ Vec trans;
    /* 0x0C */ Vec rot;
    /* 0x18 */ Vec scale;
    /* 0x24 */ f32 unk24;   // RockinRacewayRacer unk38
    /* 0x28 */ f32 unk28;   // RockinRacewayRacer unk24
} RockinRacewayReplayRacer; // Size 0x2C

// A recorded frame of the race state, see func_8010D600_rockin_raceway.
typedef struct RockinRacewayReplayFrame {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04[4];
    /* 0x014 */ RockinRacewayReplayRacer racers[4];
    /* 0x0C4 */ RockinRacewayModelState models[12];
    /* 0x304 */ RockinRacewayEffectState effects[16];
} RockinRacewayReplayFrame; // Size 0x644

// Array of 4 of these allocated in func_80109DA8_rockin_raceway, stored in D_80111B40_rockin_raceway
typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u16 numNodes;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 (*unk0C)[3];
    /* 0x10 */ f32 (*unk10)[3];
    /* 0x14 */ f32 *unk14;
    /* 0x18 */ f32 *unk18;
    /* 0x1C */ f32 (*unk1C)[3];
    /* 0x20 */ u16 *unk20;
} Track; // Size 0x24

// Pool of 16 of these allocated in func_8010E2E4_rockin_raceway, stored in D_80111BD0_rockin_raceway.
// func_8010E344_rockin_raceway claims a free entry for a request, and func_8010E39C_rockin_raceway
// consumes requests until they expire, setting soundId back to -1 when done.
typedef struct {
    /* 0x00 */ s16 soundId; // -1 marks a free entry
    /* 0x02 */ s16 frames;  // counted down once per frame
    /* 0x04 */ s16 unk04;   // switched on as a type by func_8010E39C_rockin_raceway
    /* 0x06 */ s16 playerIndex;
} RockinRacewaySfx; // Size 0x8

// Pool of 16 of these allocated in func_8010CA1C_rockin_raceway, stored in D_80111C4C_rockin_raceway.
// func_8010CADC_rockin_raceway appends entries, and func_8010CC10_rockin_raceway centers the camera
// focus D_80111C38_rockin_raceway on the bounding box of the entries, accumulating their weights.
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 weight;
} RockinRacewayVec; // Size 0x10

// Camera target computed from the RockinRacewayVec entries by func_8010CC10_rockin_raceway.
typedef struct {
    /* 0x00 */ f32 pos[4]; // x, y, z, and the accumulated weight of the entries
    /* 0x10 */ f32 zoom;
} RockinRacewayFocus; // Size 0x14

// Per-track lap meter sprite layout, built in func_8010A5E4_rockin_raceway.
typedef struct {
    /* 0x00 */ s16 track;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u16 x;
    /* 0x08 */ s16 y;
    /* 0x0A */ s16 offsets[5]; // x of each segment relative to x
} RockinRacewayMeter;          // Size 0x14

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} RockinRacewayPos16; // Size 0x4

// Values shown by the HUD built in func_80109A04_rockin_raceway.
typedef struct {
    /* 0x00 */ s32 players[4];
    /* 0x10 */ s32 times[2]; // current and record time, in frames
} RockinRacewayHudValues;    // Size 0x18

// Racer standing used to sort the racers in func_8010803C_rockin_raceway.
typedef struct {
    /* 0x00 */ s32 index;
    /* 0x04 */ s32 node;
    /* 0x08 */ s32 track;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 fraction;
    /* 0x14 */ f32 distance;
} RockinRacewayStanding; // Size 0x18

typedef union RockinRacewayWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} RockinRacewayWorkBytes;

// Pool of 8 of these allocated in func_80108578_rockin_raceway, stored in D_80111B48_rockin_raceway.
// func_80108760_rockin_raceway claims a free entry for a pair of blinking marker models, and
// func_80108864_rockin_raceway animates the entries each frame, alternating the visible model every
// duration frames and drifting position by the velocity vector.
typedef struct {
    /* 0x00 */ u16 active; // 0 marks a free entry
    /* 0x02 */ s16 modelA;
    /* 0x04 */ s16 modelB;
    /* 0x06 */ u16 timer;
    /* 0x08 */ u16 duration;
    /* 0x0A */ u16 flag;
    /* 0x0C */ f32 posX;
    /* 0x10 */ f32 posY;
    /* 0x14 */ f32 posZ;
    /* 0x18 */ f32 velX;
    /* 0x1C */ f32 velY;
    /* 0x20 */ f32 velZ;
} RockinRacewayFx; // Size 0x24

extern s16 D_800CDD6A_main;
extern s16 D_800D418E_main;
extern u8 D_800D6A90_main;
extern u8 D_800D2008_main;
extern f32 (*D_801112A0_rockin_raceway[4])[3]; // node positions of each track
// Node count per track; the first element of each pair sits at D_801112B0_rockin_raceway.
extern u16 D_801112B2_rockin_raceway[][2];
extern s32 D_801112C0_rockin_raceway[];
// Pairs of track node indices per racer; the first element of each pair sits at D_801112D0_rockin_raceway.
extern u16 D_801112D2_rockin_raceway[][2];
extern f32 D_801112E0_rockin_raceway[];
extern f32 D_801112F0_rockin_raceway[];
extern f32 D_80111300_rockin_raceway[4][2]; // per CPU difficulty
extern s32 D_80111320_rockin_raceway[4];    // per CPU difficulty
extern RockinRacewayCameraPreset D_80111350_rockin_raceway;
extern s16 D_80111340_rockin_raceway[8];
extern RockinRacewayPos16 D_80111330_rockin_raceway[4];
extern Vec D_80111414_rockin_raceway[4];
extern Vec D_80111444_rockin_raceway[12];
extern u8 D_801114D4_rockin_raceway[4];
extern s32 D_8011155C_rockin_raceway;
// Racer slot per racer; the first element of each pair sits at D_80111560_rockin_raceway.
extern u16 D_80111562_rockin_raceway[][2];
extern s32 D_80111570_rockin_raceway[4]; // racer slot occupying each track, or -1
extern u16 D_80111580_rockin_raceway[];  // model file per character
extern s32 D_80111590_rockin_raceway[3];
extern RockinRacewayQuad D_801114D8_rockin_raceway;
extern RockinRacewayQuad D_80111518_rockin_raceway;
extern RockinRacewayHudValues D_8011159C_rockin_raceway;
extern u8 D_801115B4_rockin_raceway[];
extern s32 D_801115F0_rockin_raceway;    // camera debug mode
extern s32 D_801115F4_rockin_raceway;    // camera debug text x
extern s32 D_801115F8_rockin_raceway;    // camera debug text y
extern s32 D_801115B8_rockin_raceway[];  // sprite file per character
extern s32 D_801115D8_rockin_raceway[6]; // sprite member of each time digit
extern Gfx D_801116F0_rockin_raceway[];
extern u8 D_80111730_rockin_raceway[4];
extern u8 D_80111734_rockin_raceway[4];
extern s32 D_80111AC8_rockin_raceway;
extern s32 D_80111B00_rockin_raceway[2][6];
extern omObjData *D_80111AC4_rockin_raceway;
extern s32 D_80111ACC_rockin_raceway;
extern s32 D_80111AD0_rockin_raceway;
extern s32 D_80111AD4_rockin_raceway;
extern s32 D_80111AD8_rockin_raceway;
extern s32 D_80111ADC_rockin_raceway;
extern s16 D_80111AE0_rockin_raceway;
extern s32 D_80111AE4_rockin_raceway;
extern s32 D_80111AE8_rockin_raceway;
extern s32 D_80111AEC_rockin_raceway;
extern s32 D_80111AF0_rockin_raceway[4];
extern RockinRacewayRacer *D_80111B30_rockin_raceway;
extern s16 D_80111B34_rockin_raceway;
extern s16 D_80111B36_rockin_raceway;
extern s16 D_80111B38_rockin_raceway;
extern s16 D_80111B3A_rockin_raceway;
extern RockinRacewaySnapshotRow *D_80111B3C_rockin_raceway;
extern Track *D_80111B40_rockin_raceway;
extern f32 D_80111B44_rockin_raceway;
extern RockinRacewayFx *D_80111B48_rockin_raceway;
extern omObjData *D_80111B4C_rockin_raceway;
extern RockinRacewayModelState *D_80111B50_rockin_raceway;
extern s16 D_80111B54_rockin_raceway;
extern omObjData *D_80111B58_rockin_raceway;
extern RockinRacewayEffect *D_80111B5C_rockin_raceway;
extern RockinRacewayEffectState *D_80111B60_rockin_raceway;
extern s16 D_80111B64_rockin_raceway;
extern s16 *D_80111B68_rockin_raceway;
extern s16 D_80111B6C_rockin_raceway[4];
extern s16 D_80111B74_rockin_raceway;
extern s16 D_80111B76_rockin_raceway[2];
extern s16 D_80111B7A_rockin_raceway;
extern RockinRacewayMeter D_80111B80_rockin_raceway[4];
extern RockinRacewaySfx *D_80111BD0_rockin_raceway;
extern s16 D_80111BD4_rockin_raceway;
extern s16 D_80111BD6_rockin_raceway;
extern omObjData *D_80111BD8_rockin_raceway;
extern RockinRacewayCamera D_80111BE0_rockin_raceway[2]; // target, origin
extern s16 D_80111C28_rockin_raceway;
extern s16 D_80111C2A_rockin_raceway;
extern s16 D_80111C2C_rockin_raceway;
extern s16 D_80111C2E_rockin_raceway;
extern omObjData *D_80111C30_rockin_raceway;
extern s16 D_80111C34_rockin_raceway;
extern RockinRacewayFocus D_80111C38_rockin_raceway;
extern RockinRacewayVec *D_80111C4C_rockin_raceway;
// Ring buffer of 30 replay frames, see func_8010D600_rockin_raceway and func_8010D944_rockin_raceway.
// D_80111C54_rockin_raceway counts recorded frames and D_80111C58_rockin_raceway is the next slot.
extern RockinRacewayReplayFrame *D_80111C50_rockin_raceway;
extern s32 D_80111C54_rockin_raceway;
extern s32 D_80111C58_rockin_raceway;

const s16 D_80111740_rockin_raceway[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };
const s16 D_8011174C_rockin_raceway[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000 };

void func_80105C24_rockin_raceway(omObjData *object);
void func_80105CB0_rockin_raceway(omObjData *object);
void func_80106B28_rockin_raceway(void);
void func_80106DC8_rockin_raceway(omObjData *object);
void func_801071D8_rockin_raceway(omObjData *object);
void func_8010769C_rockin_raceway(omObjData *object);
void func_80107958_rockin_raceway(RockinRacewayRacer *racer);
void func_80107A38_rockin_raceway(RockinRacewayRacer *racer);
void func_80107BFC_rockin_raceway(RockinRacewayRacer *racer);
void func_80107D04_rockin_raceway(omObjData *object);
void func_8010CB5C_rockin_raceway(RockinRacewayRacer *racer, f32 arg1);
void func_8010A5E4_rockin_raceway(s16 track, s16 character);
void func_8010EC0C_rockin_raceway(omObjData *arg0, u32 arg1);
void func_80108578_rockin_raceway(void);
void func_80108864_rockin_raceway(omObjData *object);
s32 func_80108760_rockin_raceway(Vec *arg0, s32 arg1, u16 arg2);
void func_80108BAC_rockin_raceway(void);
void func_80108D84_rockin_raceway(void);
void func_80108ED4_rockin_raceway(omObjData *object);
void func_80109208_rockin_raceway(void);
void func_80109384_rockin_raceway(omObjData *object);
void func_801099AC_rockin_raceway(void);
void func_80109A04_rockin_raceway(omObjData *object);
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z);
s32 func_8010E344_rockin_raceway(s16 soundId, s16 frames, s16 unk04, s16 playerIndex);
void func_801096A0_rockin_raceway(RockinRacewayRacer *racer);
f32 func_8010E504_rockin_raceway(f32 arg0, f32 arg1);
f32 func_8010E608_rockin_raceway(f32 target, f32 current, f32 step);
u32 func_8010EC38_rockin_raceway(omObjData *object);
u16 func_8010A4C0_rockin_raceway(s32 dirAndFile);
s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct *sprite, u8 *color);
s32 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct *sprite, RockinRacewayQuad *quad);
void func_8010B5DC_rockin_raceway(s32 *frames);
void func_80109CF8_rockin_raceway(omObjData *object);
s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color);
void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);
void func_80109DA8_rockin_raceway(void);
void func_8010A504_rockin_raceway(void);
s32 func_8010A48C_rockin_raceway(u16 arg0, u16 arg1);
f32 func_8010E7E0_rockin_raceway(f32 arg0, f32 arg1, f32 arg2);
void func_8010E8A0_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out);
void func_8010E994_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out);
void func_8010EB84_rockin_raceway(Vec *dir, f32 *rot);
f32 func_8010A258_rockin_raceway(u16 track, f32 arg1, f32 distance, f32 speed, u16 *node, f32 *fraction, Vec *pos, Vec *rot);
void func_8010B124_rockin_raceway(void);
void func_8010B774_rockin_raceway(void);
void func_8010A990_rockin_raceway(omObjData *object);
void func_8010AAAC_rockin_raceway(s16 arg0, s16 arg1, u16 arg2);
void func_8010C0D8_rockin_raceway(omObjData *object);
void func_8010C5E0_rockin_raceway(s32 arg0);
void func_8010C7CC_rockin_raceway(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void func_8010CE90_rockin_raceway(omObjData *object);
void func_8010D134_rockin_raceway(s32 camIndex);
void func_8010D288_rockin_raceway(s32 camIndex, f32 *pos, f32 *screen, f32 *normalized);
void func_8007E040_main(Mtx *m, Mtx *n, Mtx *res);
f32 func_8010E7C8_rockin_raceway(f32 arg0, f32 arg1, f32 arg2);
void func_8010D5B8_rockin_raceway(void);
void func_8010E2E4_rockin_raceway(void);
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *players);
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *values);
s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void func_801059A0_rockin_raceway(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(64);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 67.0f, 16.0f, 98.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 1.0f, 50.0f, -108.0f);
    Hu3DGLightMaxSet(2);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 6000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_80111ACC_rockin_raceway = 0;
    D_80111AD0_rockin_raceway = 0;
    D_80111AD4_rockin_raceway = 0;
    D_80111AD8_rockin_raceway = 0;
    D_80111ADC_rockin_raceway = 0;
    D_80111AE0_rockin_raceway = 0;
    D_80111BD4_rockin_raceway = -1;
    D_80111BD6_rockin_raceway = -1;
    D_80111B36_rockin_raceway = 0;
    D_80111B38_rockin_raceway = 0;
    D_80111AE4_rockin_raceway = 0;
    D_80111AEC_rockin_raceway = 5400;
    D_80111AE8_rockin_raceway = GWMgRecordGet(3);
    if (D_80111AE8_rockin_raceway == 0) {
        D_80111AE8_rockin_raceway = 9000;
    }
    D_80111BD8_rockin_raceway = NULL;
    D_80111C30_rockin_raceway = NULL;
    D_80111B68_rockin_raceway = HuMemAllocTag(0x40, TAG_OVERLAY);
    D_80111AC4_rockin_raceway = omAddObj(0x20, 0, 0, -1, func_80105C24_rockin_raceway);
    func_80045010_main(D_80111740_rockin_raceway, 1);
    func_80045010_main(D_8011174C_rockin_raceway, 1);
}

void func_80105C24_rockin_raceway(omObjData *object) {
    object->func = func_80105CB0_rockin_raceway;
    func_80109DA8_rockin_raceway();
    func_801099AC_rockin_raceway();
    func_80108D84_rockin_raceway();
    func_80109208_rockin_raceway();
    func_8010A504_rockin_raceway();
    func_8010B124_rockin_raceway();
    func_80106B28_rockin_raceway();
    func_80108578_rockin_raceway();
    func_8010E2E4_rockin_raceway();
    func_8010B774_rockin_raceway();
    func_8010D5B8_rockin_raceway();
    if (_CheckFlag(10)) {
        D_80111AC8_rockin_raceway = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_80105CB0_rockin_raceway);

void func_80106A5C_rockin_raceway(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_80106A80_rockin_raceway(omObjData *object) {
    if (D_8011155C_rockin_raceway != 0) {
        if (D_8011155C_rockin_raceway == 1) {
            object->func = func_80106A5C_rockin_raceway;
        }
        D_8011155C_rockin_raceway--;
        return;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8011155C_rockin_raceway = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)D_8011155C_rockin_raceway);
        HuAudSeqFadeOut((s16)D_8011155C_rockin_raceway);
        func_8004AB0C_main((s16)D_8011155C_rockin_raceway);
    }
}

void func_80106B28_rockin_raceway(void) {
    RockinRacewayRacer *racer;
    omObjData *object;
    Track *track;
    u16 prev;
    s32 i;
    s32 j;

    D_80111B30_rockin_raceway = HuMemAllocTag(4 * sizeof(RockinRacewayRacer), TAG_OVERLAY);
    D_80111B34_rockin_raceway = -1;
    D_80111B3A_rockin_raceway = 0;
    D_80111B3C_rockin_raceway = HuMemAllocTag(2 * sizeof(RockinRacewaySnapshotRow), TAG_OVERLAY);
    memset(D_80111B3C_rockin_raceway, 0, 2 * sizeof(RockinRacewaySnapshotRow));
    for (i = 0, racer = D_80111B30_rockin_raceway; i < 4; i++, racer++) {
        memset(racer, 0, sizeof(RockinRacewayRacer));
        racer->unk00 = i;
        racer->unk0A = D_80111562_rockin_raceway[i][0];
        racer->unk0C = GwPlayer[racer->unk0A].pad;
        racer->unk0E = GwPlayer[racer->unk0A].chr;
        if (GwPlayer[racer->unk0A].stat & 1) {
            racer->unk10 = 1;
        } else {
            racer->unk10 = 0;
        }
        racer->unk12 = GwPlayer[racer->unk0A].cpu_difficulty;
        racer->unk2E = GwPlayer[racer->unk0A].group;
        for (j = 0; j < 4; j++) {
            if (D_80111570_rockin_raceway[racer->unk2E] == -1) {
                D_80111570_rockin_raceway[racer->unk2E] = racer->unk2E;
                break;
            }
            prev = racer->unk2E;
            racer->unk2E = prev + 1;
            if (racer->unk2E >= 4) {
                racer->unk2E = prev - 3;
            }
        }
        track = &D_80111B40_rockin_raceway[racer->unk2E];
        racer->unk30 = track->unk08 - D_80111B44_rockin_raceway;
        if (racer->unk30 < 0.0f) {
            racer->unk30 = 0.0f;
        }
        func_8010A5E4_rockin_raceway(racer->unk2E, racer->unk0E);
        object = omAddObj(i + 16, 10, 60, -1, func_80106DC8_rockin_raceway);
        D_800EC598_minigame[D_800EC280_minigame] = object;
        func_8010EC0C_rockin_raceway(object, (u32)&D_80111B30_rockin_raceway[i]);
        D_800EC280_minigame++;
    }
}

void func_80106DC8_rockin_raceway(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
    u16 character;
    s32 model;
    s32 level;
    s32 i;

    object->func = func_801071D8_rockin_raceway;
    character = racer->unk0E;
    object->model[0] = func_8000B108_main(0x4D0000 | D_80111580_rockin_raceway[character], 0x299);
    object->model[1] = func_8000B108_main(9, 0x299);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            object->model[3] = func_8000B108_main(0x4D0000 | D_80111580_rockin_raceway[character], 0x28D);
            func_8001FA68_main(object->model[3]);
            func_8001F9E4_main(object->model[3], 64);
            func_8001C514_main(object->model[3]);
        } else {
            object->model[3 + i] = Hu3DModelLink(object->model[3]);
        }
        Hu3DModelLayerSet(object->model[3 + i], D_80111590_rockin_raceway[i % 3]);
    }
    switch (racer->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    racer->unk02 = 0;
    racer->unk04 = -1;
    racer->unk06 = -1;
    racer->unk08 = 0;
    racer->unk34 = 0;
    racer->unk38 = 0.0f;
    racer->unk24 = 0.0f;
    racer->unk28 = 1.0f;
    racer->unk1C = 0;
    racer->unk1E = 0;
    racer->unk20 = 0;
    racer->unk14 = level * 200 + rand16() % 300 + 300;
    racer->unk16 = rand16() % 1000;
    if (racer->unk14 != 0) {
        racer->unk16 = racer->unk16 % racer->unk14;
    }
    racer->unk18 = 0;
    racer->unk1A = 0;
    racer->unk3C = racer->unk40 = racer->unk44 = racer->unk48 = racer->unk54 = 0.0f;
    racer->pos.x = racer->pos.y = racer->pos.z = 0.0f;
    racer->rot.x = racer->rot.y = racer->rot.z = 0.0f;
    racer->unk44 = func_8010A258_rockin_raceway(racer->unk2E, racer->unk30, racer->unk44, 0.0f, &racer->unk4C,
                                                &racer->unk50, &racer->pos, &racer->rot);
    object->model[2] = model = func_8000B108_main(0x4D0009, 0x99);
    Hu3DModelPosSet(model, racer->pos.x - 0.35f * 200.0, racer->pos.y, racer->pos.z);
    Hu3DMotionSpeedSet(model, 0.0f);
    object->trans.x = racer->pos.x;
    object->trans.y = racer->pos.y;
    object->trans.z = racer->pos.z;
    object->rot.x = racer->rot.x;
    object->rot.y = racer->rot.y;
    object->rot.z = racer->rot.z;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
}

void func_801071D8_rockin_raceway(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
    HmfModel *src;
    HmfModel *dst;
    s32 i;

    if (D_80111B3A_rockin_raceway != 0) {
        for (i = 0; i < 2; i++) {
            if (D_80111B3C_rockin_raceway[i].racers[racer->unk0A].active != 0) {
                func_8001C258_main(object->model[3 + i], 4, 0);
            } else {
                func_8001C258_main(object->model[3 + i], 4, 4);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            func_8001C258_main(object->model[3 + i], 4, 4);
        }
    }
    for (i = 1; i >= 0; i--) {
        src = &Hu3DData[(i != 0) ? object->model[i + 2] : object->model[0]];
        dst = &Hu3DData[object->model[3 + i]];
        dst->pos.x = src->pos.x;
        dst->pos.y = src->pos.y;
        dst->pos.z = src->pos.z;
        dst->rot.x = src->rot.x;
        dst->rot.y = src->rot.y;
        dst->rot.z = src->rot.z;
        dst->scale.x = src->scale.x;
        dst->scale.y = src->scale.y;
        dst->scale.z = src->scale.z;
    }
    switch (D_80111AD8_rockin_raceway) {
        case 2:
            Hu3DMotionSpeedSet(object->model[2], 1.0f);
            if (racer->unk10) {
                func_8010769C_rockin_raceway(object);
            }
            if (D_80111AE0_rockin_raceway == 0) {
                racer->unk38 = 0.0f;
                racer->unk24 = 0.0f;
                racer->unk28 = 1.0f;
            }
            racer->unk38 -= 0.009f;
            if (racer->unk38 < 0.01f) {
                racer->unk38 = 0.0f;
            }
            if (racer->unk38 == 0.0f) {
                racer->unk1E = 0xE000;
            } else {
                racer->unk24 += 20.0f;
                if (racer->unk24 >= 360.0f) {
                    racer->unk24 -= 360.0f;
                    PlayerFXPlay(!(racer->unk08 & 1) ? 0x45A : 0x463, racer->unk0A);
                    racer->unk08++;
                }
            }
            switch (racer->unk02) {
                case 0:
                case 2:
                    func_80107958_rockin_raceway(racer);
                    if (D_80111AE0_rockin_raceway == 0) {
                        racer->unk38 = 0.0f;
                        racer->unk24 = 0.0f;
                        racer->unk28 = 1.0f;
                    }
                    func_80107A38_rockin_raceway(racer);
                    break;
                case 1:
                    func_80107BFC_rockin_raceway(racer);
                    break;
            }
            func_8010CB5C_rockin_raceway(racer, 0.03f);
            func_80107D04_rockin_raceway(object);
            break;
        case 3:
        case 4:
        case 6:
            switch (racer->unk02) {
                case 0:
                case 2:
                    racer->unk38 = func_8010E7C8_rockin_raceway(0.1f, racer->unk38, 0.65f);
                    func_80107A38_rockin_raceway(racer);
                    racer->unk24 += 20.0f;
                    if (racer->unk24 >= 360.0f) {
                        racer->unk24 -= 360.0f;
                    }
                    break;
                case 1:
                    if (racer->unk00 == D_80111B34_rockin_raceway) {
                        racer->unk02 = 0;
                        racer->unk28 = 1.0f;
                        racer->unk24 = 0.0f;
                        racer->unk40 = 0.0f;
                    } else {
                        func_80107BFC_rockin_raceway(racer);
                    }
                    break;
            }
            if (D_80111AD8_rockin_raceway == 6 && racer->unk00 == D_80111B34_rockin_raceway) {
                func_8010CB5C_rockin_raceway(racer, 0.1f);
            }
            func_80107D04_rockin_raceway(object);
            break;
        case 5:
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6f, 0.6f, 0.6f);
    racer->unk34++;
}

// CPU input: mashes the buttons the racer needs next.
void func_8010769C_rockin_raceway(omObjData *object) {
    RockinRacewayRacer *racer;
    s32 press;
    s32 level;

    press = FALSE;
    racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
    switch (racer->unk12) {
        case 0:
            level = 0;
            break;
        case 1:
            level = 1;
            break;
        case 2:
            level = 2;
            break;
        default:
            level = 3;
            break;
    }
    switch (func_8010A48C_rockin_raceway(racer->unk2E, racer->unk4C)) {
        case 1:
            if (racer->unk28 >= 0.5f) {
                racer->unk1A = 1;
            }
            break;
        case 2:
            racer->unk1A = 1;
            break;
    }
    if (racer->unk1A == 0) {
        if (racer->unk16 < 0 && racer->unk02 != 2) {
            if (++racer->unk16 == 0) {
                racer->unk16 = 0;
            } else {
                D_800D5558_main[racer->unk0C] = 0;
                return;
            }
        } else {
            if (D_80111AD0_rockin_raceway > 60) {
                racer->unk16 += (rand8() & 3) + 2;
            }
            if (racer->unk16 >= racer->unk14) {
                racer->unk16 = -(rand16() % 30 + 30);
            }
        }
        if (racer->unk38 < D_80111300_rockin_raceway[level][0]) {
            racer->unk1A = 1;
        } else if (racer->unk02 == 2) {
            racer->unk1A = 1;
        } else if (racer->unk38 < D_80111300_rockin_raceway[level][1] && (rand8() & 0x3F) == 0) {
            racer->unk1A = 1;
        }
    }
    if (racer->unk1A != 0) {
        racer->unk18++;
        if (racer->unk18 > D_80111320_rockin_raceway[level]) {
            racer->unk18 = 0;
            racer->unk1A = 0;
            press = TRUE;
        }
    }
    if (press) {
        if (racer->unk1E == 0x8000) {
            D_800D5558_main[racer->unk0C] = 0x8000;
        } else {
            D_800D5558_main[racer->unk0C] = 0x6000;
        }
    }
}

void func_80107958_rockin_raceway(RockinRacewayRacer *racer) {
    if (D_800D5558_main[racer->unk0C] & racer->unk1E) {
        racer->unk38 += D_801112E0_rockin_raceway[racer->unk1C] * 0.1f;
        if (racer->unk38 >= 1.0f) {
            racer->unk38 = 1.0f;
        }
        if (D_800D5558_main[racer->unk0C] == 0x8000) {
            racer->unk1E = 0x6000;
        } else {
            racer->unk1E = 0x8000;
        }
        racer->unk28 -= 0.05f;
        if (racer->unk28 < 0.0f) {
            racer->unk28 = 0.0f;
        }
    }
}

void func_80107A38_rockin_raceway(RockinRacewayRacer *racer) {
    if (racer->unk28 <= 0.0f && D_80111AD8_rockin_raceway == 2) {
        racer->unk02 = 1;
        func_8004AC98_main(0x458, racer->unk0A);
        func_8004AC98_main(0x459, racer->unk0A);
        func_8010E344_rockin_raceway(0x286, 3, 3, racer->unk0A);
        if (D_80111AD8_rockin_raceway == 2) {
            omVibrate(racer->unk0A, 2, 2, 20);
        }
    } else {
        racer->unk28 += 0.008f;
        if (racer->unk28 > 1.0f) {
            racer->unk28 = 1.0f;
        }
    }
    if (racer->unk02 == 2) {
        if (!(racer->unk34 & 0x1F)) {
            func_80108F8C_rockin_raceway(racer->pos.x + 0.1f * 200.0, racer->pos.y + 0.7f * 200.0, racer->pos.z);
        }
        racer->unk28 = 1.0f;
        if (--racer->unk20 == 0) {
            if (D_80111AD8_rockin_raceway == 2) {
                if (racer->unk04 != -1) {
                    HuAudFXStop(racer->unk04);
                    racer->unk04 = -1;
                }
                if (racer->unk06 != -1) {
                    HuAudFXStop(racer->unk06);
                    racer->unk06 = -1;
                }
            }
            racer->unk20 = 0;
            racer->unk02 = 0;
        }
    }
}

void func_80107BFC_rockin_raceway(RockinRacewayRacer *racer) {
    racer->unk38 = 0.0f;
    if (racer->unk28 >= 0.975f) {
        racer->unk40 = func_8010E608_rockin_raceway(racer->unk38, racer->unk40, 30.0f);
        if (func_8010E504_rockin_raceway(0.0f, racer->unk40) < 0.5f) {
            racer->unk24 = 0;
            racer->unk40 = 0.0f;
            racer->unk02 = 0;
        }
    } else {
        racer->unk40 += 30.0f;
        if (racer->unk40 >= 360.0f) {
            racer->unk40 -= 360.0f;
        }
        if (racer->unk34 & 3) {
            func_801096A0_rockin_raceway(racer);
        }
        racer->unk28 += 0.025f;
    }
}

void func_80107D04_rockin_raceway(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
    HuMtx4F mtx;
    f32 speed;

    speed = racer->unk38 * D_801112F0_rockin_raceway[racer->unk1C] * 3.0f;
    racer->unk3C = sindf(racer->unk24) * racer->unk38 * 30.0f;
    racer->unk44 = func_8010A258_rockin_raceway(racer->unk2E, racer->unk30, racer->unk44, speed, &racer->unk4C,
                                                &racer->unk50, &racer->pos, &racer->rot);
    if (racer->unk3C > 0.0f) {
        func_8008A070_main(mtx);
        mtxRotCat(mtx, racer->unk3C, 0.0f, 0.0f);
        mtxTransCat(mtx, 0.0f, 0.0f, 47.0f);
        racer->unk54 = mtx[3][2];
    } else {
        racer->unk54 = 47.0f;
    }
    racer->unk48 = racer->unk44 + racer->unk54;
    object->trans.x = racer->pos.x;
    object->trans.y = racer->pos.y;
    object->trans.z = racer->pos.z;
    object->rot.x = racer->rot.x + racer->unk3C;
    object->rot.y = racer->rot.y + racer->unk40;
}

// Records the transform of each racer object into the given row of the snapshot table, once per racer.
void func_80107E78_rockin_raceway(s32 row, s16 arg1) {
    RockinRacewayRacer *racer;
    omObjData *object;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = D_800EC598_minigame[i];
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(object);
        if (D_80111B3C_rockin_raceway[row].racers[racer->unk0A].active != 0) {
            continue;
        }
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].active = 1;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].unk00 = arg1;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].trans.x = object->trans.x;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].trans.y = object->trans.y;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].trans.z = object->trans.z;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].rot.x = object->rot.x;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].rot.y = object->rot.y;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].rot.z = object->rot.z;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].scale.x = object->scale.x;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].scale.y = object->scale.y;
        D_80111B3C_rockin_raceway[row].racers[racer->unk0A].scale.z = object->scale.z;
    }
}

// Ranks the racers by track progress, writing each racer's rank to unk1C and the racer slots in rank
// order to order. Ties are broken randomly.
void func_8010803C_rockin_raceway(s32 *order) {
    RockinRacewayStanding standings[4];
    RockinRacewayStanding temp;
    RockinRacewayRacer *racer;
    s32 swap;
    s32 k;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        standings[i].index = i;
        standings[i].node = racer->unk4C;
        standings[i].track = racer->unk2E;
        standings[i].x = D_800EC598_minigame[i]->trans.x + racer->unk54;
        standings[i].fraction = racer->unk50;
        standings[i].distance = racer->unk48;
    }
    for (i = 0; i < 64; i++) {
        j = rand8() & 3;
        k = rand8() & 3;
        temp = standings[j];
        standings[j] = standings[k];
        standings[k] = temp;
    }
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            swap = FALSE;
            if (standings[i].node >= D_801112C0_rockin_raceway[standings[i].track] - 1 &&
                standings[j].node >= D_801112C0_rockin_raceway[standings[j].track] - 1 &&
                standings[i].x < standings[j].x) {
                swap = TRUE;
            } else if (standings[i].node < standings[j].node) {
                swap = TRUE;
            } else if (standings[i].node == standings[j].node && standings[i].fraction < standings[j].fraction) {
                swap = TRUE;
            }
            if (swap) {
                temp = standings[i];
                standings[i] = standings[j];
                standings[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        for (j = 0; j < 4; j++) {
            if (standings[j].index == i) {
                break;
            }
        }
        if (j >= 4) {
            j = 3;
        }
        racer->unk1C = j;
    }
    for (i = 0; i < 4; i++) {
        order[i] = ((RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[standings[i].index]))->unk0A;
    }
}

s32 func_80108464_rockin_raceway(void) {
    RockinRacewayRacer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        if (racer->unk4C >= D_801112C0_rockin_raceway[racer->unk2E] - 1 &&
            D_800EC598_minigame[i]->trans.x + racer->unk54 >= 1.7f * 200.0) {
            break;
        }
    }
    if (i < 4) {
        for (i = 0; i < 4; i++) {
            racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
            if (racer->unk1C == 0) {
                return i;
            }
        }
    }
    return -1;
}

void func_80108578_rockin_raceway(void) {
    RockinRacewayFx *entry;
    RockinRacewayRacer *racer;
    Vec rot;
    Vec pos;
    s32 i;

    D_80111B48_rockin_raceway = entry = HuMemAllocTag(8 * sizeof(RockinRacewayFx), TAG_OVERLAY);
    for (i = 0; i < 8; i++, entry++) {
        memset(entry, 0, sizeof(RockinRacewayFx));
        if (i == 0) {
            entry->modelA = func_8000B108_main(0x4D0007, 0x99);
            entry->modelB = func_8000B108_main(0x4D0008, 0x99);
        } else {
            entry->modelA = Hu3DModelLink(D_80111B48_rockin_raceway->modelA);
            entry->modelB = Hu3DModelLink(D_80111B48_rockin_raceway->modelB);
        }
        func_8001C258_main(entry->modelA, 4, 4);
        func_8001C258_main(entry->modelB, 4, 4);
        entry->flag = 0;
        entry->timer = 0;
        entry->active = 0;
        entry->posX = entry->posY = entry->posZ = 0.0f;
        entry->velX = entry->velY = entry->velZ = 0.0f;
    }
    for (i = 0, racer = D_80111B30_rockin_raceway; i < 4; i++, racer++) {
        func_8010A258_rockin_raceway(racer->unk2E, racer->unk30, 1500.0f, 0.0f, NULL, NULL, &pos, &rot);
        func_80108760_rockin_raceway(&pos, 0, 90);
        func_80108760_rockin_raceway((Vec *)D_80111B40_rockin_raceway[i].unk0C[D_801112D2_rockin_raceway[i][0]], 0,
                                     30);
    }
    omSetStatBit(omAddObj(30, 0, 0, -1, func_80108864_rockin_raceway), 0xA0);
}

// Claims a free blink-marker entry, initializes it with the duration and base position, positions
// both models there, and returns the entry index, or -1 if the pool is full.
s32 func_80108760_rockin_raceway(Vec *arg0, s32 arg1, u16 arg2) {
    RockinRacewayFx *entry;
    s32 i;

    for (i = 0, entry = D_80111B48_rockin_raceway; i < 8 && entry->active != 0; i++, entry++) {
    }
    if (i >= 8) {
        return -1;
    }
    entry->active = 1;
    entry->duration = arg2;
    entry->flag = 0;
    if (arg0 != NULL) {
        entry->posX = arg0->x;
        entry->posY = arg0->y;
        entry->posZ = arg0->z;
    } else {
        entry->posX = entry->posY = entry->posZ = 0.0f;
    }
    if (arg1 != 0) {
        entry->velX = arg0->x;
        entry->velY = arg0->y;
        entry->velZ = arg0->z;
    } else {
        entry->velX = entry->velY = entry->velZ = 0.0f;
    }
    Hu3DModelPosSet(entry->modelA, entry->posX, entry->posY, entry->posZ);
    Hu3DModelPosSet(entry->modelB, entry->posX, entry->posY, entry->posZ);
    return i;
}

void func_80108864_rockin_raceway(omObjData *object) {
    RockinRacewayFx *entry;
    u16 shown;
    u16 hidden;
    s32 i;

    if (omPauseChk() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
        func_80108BAC_rockin_raceway();
    }
    for (i = 0, entry = D_80111B48_rockin_raceway; i < 8; i++, entry++) {
        if (entry->active == 0) {
            continue;
        }
        if (omPauseChk() + D_800D6A90_main == 0 && D_80111AD8_rockin_raceway == 2) {
            if (++entry->timer >= entry->duration) {
                entry->timer = 0;
                entry->flag ^= 1;
            }
        }
        if (entry->flag & 1) {
            shown = entry->modelB;
            hidden = entry->modelA;
        } else {
            shown = entry->modelA;
            hidden = entry->modelB;
        }
        func_8001C258_main(shown, 4, 0);
        func_8001C258_main(hidden, 4, 4);
        entry->posX += entry->velX;
        entry->posY += entry->velY;
        entry->posZ += entry->velZ;
        Hu3DModelPosSet(shown, entry->posX, entry->posY, entry->posZ);
        Hu3DModelPosSet(hidden, entry->posX, entry->posY, entry->posZ);
        Hu3DModelScaleSet(shown, 1.0f, 1.0f, 1.0f);
        Hu3DModelScaleSet(hidden, 1.0f, 1.0f, 1.0f);
        if (D_80111AD8_rockin_raceway >= 3) {
            entry->active = 0;
            func_8001C258_main(shown, 4, 4);
            func_8001C258_main(hidden, 4, 4);
        }
    }
}

// Collects the first active blink marker within range of pos, returning its flag, or -1 if none.
s32 func_80108A80_rockin_raceway(Vec *pos) {
    RockinRacewayFx *entry;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    for (i = 0, entry = D_80111B48_rockin_raceway; i < 8; i++, entry++) {
        if (entry->active == 0) {
            continue;
        }
        dx = entry->posX - pos->x;
        dy = entry->posY - pos->y;
        dz = entry->posZ - pos->z;
        if (dx * dx + dy * dy + dz * dz < (0.3f * 200.0) * (0.3f * 200.0)) {
            func_8001C258_main(entry->modelA, 4, 4);
            func_8001C258_main(entry->modelB, 4, 4);
            entry->active = 0;
            if (D_80111BD4_rockin_raceway == -1 && D_80111BD6_rockin_raceway == -1 && entry->duration == 30) {
                D_80111BD6_rockin_raceway = 4;
            }
            break;
        }
    }
    if (i < 8) {
        return entry->flag;
    }
    return -1;
}

void func_80108BAC_rockin_raceway(void) {
    RockinRacewayRacer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        switch (func_80108A80_rockin_raceway(&racer->pos)) {
            case 0:
                racer->unk02 = 2;
                racer->unk28 = 1.0f;
                racer->unk20 = 300;
                racer->unk34 |= 0xE;
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(racer->unk0A, 10, 0, 10);
                }
                if (D_80111AD8_rockin_raceway == 2) {
                    if (racer->unk04 != -1) {
                        HuAudFXStop(racer->unk04);
                        racer->unk04 = -1;
                    }
                    if (racer->unk06 != -1) {
                        HuAudFXStop(racer->unk06);
                        racer->unk06 = -1;
                    }
                }
                racer->unk04 = func_8004AC98_main(0x46D, racer->unk0A);
                racer->unk06 = func_8004AC98_main(0x46E, racer->unk0A);
                break;
            case 1:
                racer->unk02 = 1;
                racer->unk28 = 0.0f;
                if (D_80111AD8_rockin_raceway == 2) {
                    if (racer->unk04 != -1) {
                        HuAudFXStop(racer->unk04);
                        racer->unk04 = -1;
                    }
                    if (racer->unk06 != -1) {
                        HuAudFXStop(racer->unk06);
                        racer->unk06 = -1;
                    }
                }
                func_8004AC98_main(0x458, racer->unk0A);
                func_8004AC98_main(0x459, racer->unk0A);
                func_8010E344_rockin_raceway(0x286, 3, 3, racer->unk0A);
                if (D_80111AD8_rockin_raceway == 2) {
                    omVibrate(racer->unk0A, 2, 2, 20);
                }
                break;
        }
    }
}

void func_80108D84_rockin_raceway(void) {
    omObjData *object;
    HmfModel *model;
    s32 i;

    D_80111B4C_rockin_raceway = object = omAddObj(29, 13, 0, -1, func_80108ED4_rockin_raceway);
    object->model[0] = -1;
    for (i = 1; i < 13; i++) {
        object->model[i] = func_8000B108_main(0x1001F, 0x899);
        func_8001C2FC_main(object->model[i], 0x600, 0x400);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
        model = &Hu3DData[object->model[i]];
        model->motTime = 0.0f;
        model->motSpeed = 1.0f;
        func_8001C258_main(object->model[i], 4, 4);
    }
    D_80111B50_rockin_raceway = HuMemAllocTag(12 * sizeof(RockinRacewayModelState), TAG_OVERLAY);
    memset(D_80111B50_rockin_raceway, 0, 12 * sizeof(RockinRacewayModelState));
    D_80111B54_rockin_raceway = 0;
}

// Hides each spark model once its motion has finished playing.
void func_80108ED4_rockin_raceway(omObjData *object) {
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway != 0) {
        return;
    }
    for (i = 1; i < 13; i++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        if (model->attr & 4) {
            continue;
        }
        if (D_800CCF58_main[model->motId].unk02 <= model->motTime) {
            model->attr |= 4;
            model->motTime = 0.0f;
        }
    }
}

// Shows the first hidden spark model at the given position, facing the camera.
void func_80108F8C_rockin_raceway(f32 x, f32 y, f32 z) {
    omObjData *object = D_80111B4C_rockin_raceway;
    HmfModel *model;
    s32 i;

    for (i = 1; i < 13; i++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        if (!(model->attr & 4)) {
            continue;
        }
        model->pos.x = x;
        model->pos.y = y;
        model->pos.z = z;
        model->rot.x = CRot.x;
        model->rot.y = CRot.y;
        model->rot.z = CRot.z;
        model->attr &= ~4;
        model->motTime = 0.0f;
        model->motSpeed = 1.5f;
        break;
    }
}

// Saves the state of each spark model and pauses it.
void func_80109044_rockin_raceway(void) {
    omObjData *object = D_80111B4C_rockin_raceway;
    RockinRacewayModelState *state = D_80111B50_rockin_raceway;
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway != 0) {
        return;
    }
    for (i = 1; i < 13; i++, state++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        state->attr = model->attr;
        state->motTime = model->motTime;
        state->motSpeed = model->motSpeed;
        state->pos.x = model->pos.x;
        state->pos.y = model->pos.y;
        state->pos.z = model->pos.z;
        state->rot.x = model->rot.x;
        state->rot.y = model->rot.y;
        state->rot.z = model->rot.z;
        state->scale.x = model->scale.x;
        state->scale.y = model->scale.y;
        state->scale.z = model->scale.z;
        model->attr |= 4;
        model->motTime = model->motSpeed = 0.0f;
    }
    D_80111B54_rockin_raceway = 1;
}

// Restores the state of each spark model saved by func_80109044_rockin_raceway.
void func_80109134_rockin_raceway(void) {
    omObjData *object = D_80111B4C_rockin_raceway;
    RockinRacewayModelState *state = D_80111B50_rockin_raceway;
    HmfModel *model;
    s32 i;

    if (D_80111B54_rockin_raceway == 0) {
        return;
    }
    for (i = 1; i < 13; i++, state++) {
        if (object->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[object->model[i]];
        model->attr = state->attr;
        model->motTime = state->motTime;
        model->motSpeed = state->motSpeed;
        model->pos.x = state->pos.x;
        model->pos.y = state->pos.y;
        model->pos.z = state->pos.z;
        model->rot.x = state->rot.x;
        model->rot.y = state->rot.y;
        model->rot.z = state->rot.z;
        model->scale.x = state->scale.x;
        model->scale.y = state->scale.y;
        model->scale.z = state->scale.z;
    }
    D_80111B54_rockin_raceway = 0;
}

void func_80109208_rockin_raceway(void) {
    HuSprite_Unk84_Struct *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    D_80111B68_rockin_raceway[2] = func_8010A4C0_rockin_raceway(11);
    sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    D_80111B58_rockin_raceway = omAddObj(28, 0, 0, -1, func_80109384_rockin_raceway);
    D_80111B5C_rockin_raceway = effect = HuMemAllocTag(sizeof(RockinRacewayEffect) * 16, TAG_OVERLAY);
    for (i = 0; i < 16; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010EC8C_rockin_raceway(sprite, D_801114D4_rockin_raceway);
        } else {
            effect->model =
                func_8010F874_rockin_raceway(sprite, D_80111B5C_rockin_raceway[0].model, D_801114D4_rockin_raceway);
        }
        effect->active = 0;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
    D_80111B60_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewayEffectState), TAG_OVERLAY);
    memset(D_80111B60_rockin_raceway, 0, 16 * sizeof(RockinRacewayEffectState));
    D_80111B64_rockin_raceway = 0;
}

void func_80109384_rockin_raceway(omObjData *object) {
    HuSprite_Unk84_Struct *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        return;
    }
    sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    for (i = 0, effect = D_80111B5C_rockin_raceway; i < 16; i++, effect++) {
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
        func_8010FA78_rockin_raceway(effect->model, sprite, (s32)effect->frame, D_801114D4_rockin_raceway);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->unk10) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_801094EC_rockin_raceway(Vec *pos, Vec *vel, Vec *scale, f32 speed) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_80111B68_rockin_raceway[2]);
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_80111B5C_rockin_raceway; i < 16; i++, effect++) {
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
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8010FA78_rockin_raceway(effect->model, sprite, 0, D_801114D4_rockin_raceway);
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

// Spawns a small effect above the racer, drifting backward from its heading.
void func_801096A0_rockin_raceway(RockinRacewayRacer *racer) {
    Vec pos;
    Vec vel;
    Vec scale;

    pos.x = racer->pos.x;
    pos.z = racer->pos.z;
    pos.y = racer->pos.y + 0.1f * 200.0;
    vel.x = -(sindf(racer->rot.y + racer->unk40) * 100.0 * 0.1f);
    vel.z = -(cosdf(racer->rot.y + racer->unk40) * 100.0 * 0.1f);
    vel.y = 1.0f;
    scale.x = scale.y = scale.z = 0.25f;
    func_801094EC_rockin_raceway(&pos, &vel, &scale, 1.0f);
}

// Saves the state of each sprite effect and hides it.
void func_801097A0_rockin_raceway(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway != 0) {
        return;
    }
    for (state = D_80111B60_rockin_raceway, effect = D_80111B5C_rockin_raceway, i = 0; i < 16;
         i++, effect++, state++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        state->active = effect->active;
        state->motTime = model->motTime;
        state->attr = model->attr;
        state->frame = effect->frame;
        state->speed = effect->speed;
        state->pos.x = model->pos.x;
        state->pos.y = model->pos.y;
        state->pos.z = model->pos.z;
        state->rot.x = model->rot.x;
        state->rot.y = model->rot.y;
        state->rot.z = model->rot.z;
        state->scale.x = model->scale.x;
        state->scale.y = model->scale.y;
        state->scale.z = model->scale.z;
        effect->active = 0;
        model->attr |= 4;
        model->motTime = 0.0f;
    }
    D_80111B64_rockin_raceway = 1;
}

// Restores the state of each sprite effect saved by func_801097A0_rockin_raceway.
void func_801098D8_rockin_raceway(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (D_80111B64_rockin_raceway == 0) {
        return;
    }
    for (state = D_80111B60_rockin_raceway, effect = D_80111B5C_rockin_raceway, i = 0; i < 16;
         i++, effect++, state++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        effect->active = state->active;
        model->attr = state->attr;
        effect->frame = state->frame;
        effect->speed = state->speed;
        model->pos.x = state->pos.x;
        model->pos.y = state->pos.y;
        model->pos.z = state->pos.z;
        model->rot.x = state->rot.x;
        model->rot.y = state->rot.y;
        model->rot.z = state->rot.z;
        model->scale.x = state->scale.x;
        model->scale.y = state->scale.y;
        model->scale.z = state->scale.z;
    }
    D_80111B64_rockin_raceway = 0;
}

// Appends a new object to the shared minigame object list.
void func_801099AC_rockin_raceway(void) {
    omObjData *obj = omAddObj(1, 0x18, 0, -1, func_80109A04_rockin_raceway);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

void func_80109A04_rockin_raceway(omObjData *object) {
    s16 group;
    s32 i;

    object->func = func_80109CF8_rockin_raceway;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->model[0] = func_8000B0A0_main(0x4D0000, 0x99);
    object->model[1] = func_8000B0A0_main(0x4D000A, 0xB9);
    object->model[2] = func_8000B0A0_main(0x4D000B, 0xB9);
    D_80111B68_rockin_raceway[3] = func_8010A4C0_rockin_raceway(0x4D0010);
    D_80111B68_rockin_raceway[4] = func_8010A4C0_rockin_raceway(0x4D0011);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            object->model[3] =
                func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway[3]), &D_801114D8_rockin_raceway);
        } else {
            object->model[3 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway[3]),
                                                                object->model[3], D_801115B4_rockin_raceway);
        }
    }
    for (i = 0; i < 12; i++) {
        if (i == 0) {
            object->model[7] =
                func_8010FFB8_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway[4]), &D_80111518_rockin_raceway);
        } else {
            object->model[7 + i] = func_8010F874_rockin_raceway(func_80055194_main(D_80111B68_rockin_raceway[4]),
                                                                object->model[7], D_801115B4_rockin_raceway);
        }
    }
    func_80110C38_rockin_raceway(&object->model[3], func_80055194_main(D_80111B68_rockin_raceway[3]),
                                 D_8011159C_rockin_raceway.players);
    D_8011159C_rockin_raceway.times[1] = D_80111AE8_rockin_raceway;
    func_8010B5DC_rockin_raceway(D_8011159C_rockin_raceway.times);
    func_80110D90_rockin_raceway(&object->model[7], func_80055194_main(D_80111B68_rockin_raceway[4]),
                                 D_8011159C_rockin_raceway.times);
    D_80111B68_rockin_raceway[0] = func_8010A4C0_rockin_raceway(0x4D000E);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, D_80111B68_rockin_raceway[0], 0);
    HuSprAttrSet(group, 0, 0x4000);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    HuSprPosSet(group, 0, 160, 120);
    HuSprPriSet(group, 0, 0xFFFF);
    func_800550F4_main(group, 0, 0);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80109CF8_rockin_raceway(omObjData *object) {
}

void func_80109D00_rockin_raceway(s32 *players) {
    omObjData *object = D_800EC1C0_minigame[0];

    func_80110C38_rockin_raceway(&object->model[3], func_80055194_main(D_80111B68_rockin_raceway[3]), players);
}

void func_80109D54_rockin_raceway(s32 *values) {
    omObjData *object = D_800EC1C0_minigame[0];

    func_80110D90_rockin_raceway(&object->model[7], func_80055194_main(D_80111B68_rockin_raceway[4]), values);
}

void func_80109DA8_rockin_raceway(void) {
    Track *track;
    Vec dir;
    f32 dx, dy, dz;
    f32 distance;
    s32 next;
    s32 i;
    s32 j;

    D_80111B40_rockin_raceway = HuMemAllocTag(4 * sizeof(Track), TAG_OVERLAY);
    for (i = 0, track = D_80111B40_rockin_raceway; i < 4; i++, track++) {
        track->unk00 = i;
        track->unk04 = track->unk08 = 0.0f;
        track->unk0C = D_801112A0_rockin_raceway[i];
        track->numNodes = D_801112B2_rockin_raceway[i][0];
        track->unk0C[D_801112C0_rockin_raceway[i]][0] = 340.0f;
        track->unk10 = HuMemAllocTag(track->numNodes * sizeof(*track->unk10), TAG_OVERLAY);
        track->unk14 = HuMemAllocTag(track->numNodes * sizeof(f32), TAG_OVERLAY);
        track->unk18 = HuMemAllocTag((track->numNodes + 1) * sizeof(f32), TAG_OVERLAY);
        track->unk1C = HuMemAllocTag(track->numNodes * sizeof(*track->unk1C), TAG_OVERLAY);
        track->unk20 = HuMemAllocTag(track->numNodes * sizeof(u16), TAG_OVERLAY);
        memset(track->unk20, 0, 4);
        for (j = 0; j < 5; j++) {
            next = rand8() % D_801112C0_rockin_raceway[i];
            track->unk20[next] = 1;
        }
        for (j = 0; j < 3; j++) {
            next = rand8() % D_801112C0_rockin_raceway[i];
            track->unk20[next] = 2;
        }
        distance = 0.0f;
        for (j = 0; j < track->numNodes; j++) {
            next = (j + 1) % track->numNodes;
            dx = track->unk0C[next][0] - track->unk0C[j][0];
            dy = track->unk0C[next][1] - track->unk0C[j][1];
            dz = track->unk0C[next][2] - track->unk0C[j][2];
            track->unk14[j] = sqrtf(dx * dx + dy * dy + dz * dz);
            track->unk18[j] = distance;
            distance += track->unk14[j];
            if (j < D_801112C0_rockin_raceway[i]) {
                track->unk08 = distance;
            }
            track->unk10[j][0] = track->unk0C[j][0] + dx * 0.5f;
            track->unk10[j][1] = track->unk0C[j][1] + dy * 0.5f;
            track->unk10[j][2] = track->unk0C[j][2] + dz * 0.5f;
            func_8010E994_rockin_raceway(0.0f, track->unk0C[j], track->unk10[j], track->unk0C[next], &dir.x);
            func_8010EB84_rockin_raceway(&dir, track->unk1C[j]);
        }
        track->unk18[j] = distance;
        track->unk04 = distance - track->unk14[j - 1];
    }
    D_80111B44_rockin_raceway = D_80111B40_rockin_raceway[0].unk08;
    for (i = 1, track = &D_80111B40_rockin_raceway[1]; i < 4; i++, track++) {
        if (D_80111B44_rockin_raceway > track->unk08) {
            D_80111B44_rockin_raceway = track->unk08;
        }
    }
}

#ifdef NON_MATCHING
// Only differs in register allocation: the target keeps i in s1 and numNodes in a0.
// Advances distance along the track by speed, and evaluates the position and rotation at the
// resulting point (offset by arg1).
f32 func_8010A258_rockin_raceway(u16 trackIndex, f32 arg1, f32 distance, f32 speed, u16 *node, f32 *fraction, Vec *pos,
                                 Vec *rot) {
    s32 i;
    s32 next;
    Track *track = &D_80111B40_rockin_raceway[trackIndex];
    f32 newDistance;
    f32 offset;
    f32 remainder;
    f32 t;

    newDistance = distance + speed;
    if (newDistance >= track->unk04) {
        newDistance = track->unk04;
    } else if (newDistance <= 0.0f) {
        newDistance = 0.0f;
    }
    offset = newDistance + arg1;
    if (offset >= track->unk04) {
        offset = track->unk04;
    } else if (offset <= 0.0f) {
        offset = 0.0f;
    }
    remainder = offset;
    for (i = 0; i < track->numNodes; i++) {
        if (offset <= track->unk18[i + 1]) {
            break;
        }
        remainder = offset - track->unk18[i + 1];
    }
    if (i > track->numNodes - 1) {
        i = track->numNodes - 1;
    }
    if (node != NULL) {
        *node = i;
    }
    t = (remainder == 0.0f || track->unk14[i] == 0.0f) ? 0.0f : remainder / track->unk14[i];
    if (fraction != NULL) {
        *fraction = t;
    }
    next = (i < track->numNodes - 1) ? i + 1 : 0;
    func_8010E8A0_rockin_raceway(t, track->unk0C[i], track->unk10[i], track->unk0C[next], &pos->x);
    rot->x = func_8010E7E0_rockin_raceway(t, track->unk1C[i][0], track->unk1C[next][0]);
    rot->y = func_8010E7E0_rockin_raceway(t, track->unk1C[i][1], track->unk1C[next][1]);
    return newDistance;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010A258_rockin_raceway);
#endif

s32 func_8010A48C_rockin_raceway(u16 arg0, u16 arg1) {
    Track *track = &D_80111B40_rockin_raceway[arg0];
    return track->unk20[arg1];
}

u16 func_8010A4C0_rockin_raceway(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 anim = HuSprAnimRead(data);

    DataClose(data);
    return anim;
}

void func_8010A504_rockin_raceway(void) {
    s32 group;

    D_80111B68_rockin_raceway[1] = func_8010A4C0_rockin_raceway(0x4D000F);
    D_80111B68_rockin_raceway[5] = func_8010A4C0_rockin_raceway(0x4D0012);
    D_80111B68_rockin_raceway[8] = func_8010A4C0_rockin_raceway(0x4D0013);
    group = HuSprGrpCreate(1, 0);
    D_80111B74_rockin_raceway = group;
    HuSprPosSet(group, 0, 160, 60);
    HuSprGrpMemberSet(group, 0, D_80111B68_rockin_raceway[5], 0);
    func_800550F4_main(group, 0, 0);
    func_80054FF8_main(group, 0, 0);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF | 0x1000);
}

// Creates the lap meter sprites for a track, mirrored for odd tracks.
void func_8010A5E4_rockin_raceway(s16 track, s16 character) {
    s32 anim;
    s32 x;
    s32 y;
    s32 group;
    s32 i;

    anim = func_8010A4C0_rockin_raceway(D_801115B8_rockin_raceway[character]);
    x = D_80111330_rockin_raceway[track].x;
    y = D_80111330_rockin_raceway[track].y;
    D_80111B6C_rockin_raceway[track] = group = HuSprGrpCreate(7, 0);
    D_80111B80_rockin_raceway[track].track = track;
    D_80111B80_rockin_raceway[track].y = y;
    D_80111B80_rockin_raceway[track].unk04 = 0;
    D_80111B80_rockin_raceway[track].unk02 = 0;
    if (track & 1) {
        D_80111B80_rockin_raceway[track].x = x - 4;
    } else {
        D_80111B80_rockin_raceway[track].x = x + 46;
    }
    for (i = 0; i < 5; i++) {
        if (track & 1) {
            D_80111B80_rockin_raceway[track].offsets[i] = x + (i * 8 - 20) - D_80111B80_rockin_raceway[track].x;
        } else {
            D_80111B80_rockin_raceway[track].offsets[i] = x + (i * 8 + 30) - D_80111B80_rockin_raceway[track].x;
        }
    }
    for (i = 0; i < 7; i++) {
        if (i == 0) {
            if (track & 1) {
                HuSprPosSet(group, i, x - 42, y);
            } else {
                HuSprPosSet(group, i, x + 8, y);
            }
            HuSprGrpMemberSet(group, i, anim, 0);
        } else if (i == 6) {
            if (track & 1) {
                HuSprPosSet(group, i, x - 55, y);
            } else {
                HuSprPosSet(group, i, x - 5, y);
            }
            HuSprGrpMemberSet(group, i, D_80111B68_rockin_raceway[8], 0);
            func_80055484_main(group, i, 0, 0, 0, 160);
        } else {
            if (track & 1) {
                HuSprPosSet(group, i, x - 20, y);
            } else {
                HuSprPosSet(group, i, x + 30, y);
            }
            HuSprGrpMemberSet(group, i, D_80111B68_rockin_raceway[1], 0);
            x += 8;
        }
        func_800550F4_main(group, i, 0);
        func_80054FF8_main(group, i, 0);
        HuSprAttrSet(group, i, 0x1000);
        if (i != 6) {
            HuSprPriSet(group, i, -16 - i);
        } else {
            HuSprPriSet(group, i, 0xFFFF);
        }
    }
    omSetStatBit(omAddObj(20, 0, 0, -1, func_8010A990_rockin_raceway), 0xA0);
}

void func_8010A990_rockin_raceway(omObjData *object) {
    RockinRacewayRacer *racer;
    s32 i;

    if (D_80111AD8_rockin_raceway == 5 && (D_80111ADC_rockin_raceway > 0 || D_80111AD0_rockin_raceway >= 2)) {
        HuSprAttrReset(D_80111B74_rockin_raceway, 0, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(D_80111B74_rockin_raceway, 0, HUSPR_ATTR_DISPOFF);
    }
    if (D_80111AD8_rockin_raceway < 3) {
        racer = D_80111B30_rockin_raceway;
        for (i = 0; i < 4; i++, racer++) {
            func_8010AAAC_rockin_raceway(racer->unk2E, racer->unk28 * 100.0f, racer->unk02);
        }
    } else {
        for (i = 0; i < 4; i++) {
            func_8010AAAC_rockin_raceway(i, 0, 0xFFFF);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010AAAC_rockin_raceway);

void func_8010B124_rockin_raceway(void) {
    s32 group;
    s32 i;
    s32 j;

    D_80111B68_rockin_raceway[6] = func_8010A4C0_rockin_raceway(0x31);
    D_80111B68_rockin_raceway[7] = func_8010A4C0_rockin_raceway(0x32);
    D_80111B7A_rockin_raceway = 0;
    for (i = 0; i < 2; i++) {
        D_80111B76_rockin_raceway[i] = group = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            HuSprPosSet(group, j, D_80111340_rockin_raceway[j], i * 12 + 28);
            HuSprGrpMemberSet(group, j, D_80111B68_rockin_raceway[6 + i], 0);
            func_80054FF8_main(group, j, 0);
            HuSprAttrSet(group, j, 0x1000);
            func_800550F4_main(group, j, 0);
        }
        func_80054FF8_main(group, 2, 10);
        func_80054FF8_main(group, 5, 11);
    }
}

#ifdef NON_MATCHING
// Logic matches; register allocation differs (the target rematerializes &D_80111B76_rockin_raceway in the
// last loop and keeps the digit table base in s5).
// Updates the current and record time digits, pulsing the record time when it is beaten.
void func_8010B2B8_rockin_raceway(void) {
    s32(*digits)[6];
    f32 scale = 1.0f;
    u16 group;
    s32 i;
    s32 j;

    if (D_80111AD8_rockin_raceway == 5) {
        for (i = 0; i < 2; i++) {
            group = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrSet(group, j, HUSPR_ATTR_DISPOFF);
            }
        }
    } else {
        digits = D_80111B00_rockin_raceway;
        for (i = 0; i < 2; i++) {
            group = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrReset(group, j, HUSPR_ATTR_DISPOFF);
            }
        }
        if (D_80111B7A_rockin_raceway != 0) {
            scale = sindf(D_80111B7A_rockin_raceway / 15.0f * 180.0f) + 1.0f;
            if (--D_80111B7A_rockin_raceway == 1) {
                scale = 1.0f;
            }
        }
        for (i = 0; i < 2; i++) {
            group = D_80111B76_rockin_raceway[i];
            for (j = 0; j < 6; j++) {
                if (digits[i][j] >= 10) {
                    digits[i][j] = 9;
                } else if (digits[i][j] < 0) {
                    digits[i][j] = 0;
                }
                func_80054FF8_main(group, D_801115D8_rockin_raceway[j], (s16)digits[i][j]);
            }
            if (D_80111B7A_rockin_raceway != 0 && i == 1) {
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(group, j, (D_80111340_rockin_raceway[j] - 156) * scale + 156.0f, i * 12 + 28);
                    HuSprScaleSet(group, j, scale, scale);
                }
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010B2B8_rockin_raceway);
#endif

// Converts the two frame counts into minute, second and hundredth digits in D_80111B00_rockin_raceway.
void func_8010B5DC_rockin_raceway(s32 *frames) {
    s32 time[3];
    s32(*digits)[6] = D_80111B00_rockin_raceway;
    s32 i;

    for (i = 0; i < 2; i++) {
        time[0] = frames[i] / 1800;
        frames[i] -= time[0] * 1800;
        time[1] = frames[i] / 30;
        frames[i] -= time[1] * 30;
        time[2] = frames[i] / 30.0f * 99.0f;
        digits[i][0] = time[0] / 10;
        digits[i][1] = time[0] - digits[i][0] * 10;
        digits[i][2] = time[1] / 10;
        digits[i][3] = time[1] - digits[i][2] * 10;
        digits[i][4] = time[2] / 10;
        digits[i][5] = time[2] - digits[i][4] * 10;
    }
}

void func_8010B774_rockin_raceway(void) {
    HuCamera *camera;
    s32 i;

    Center.x = D_80111350_rockin_raceway.center.x;
    Center.y = D_80111350_rockin_raceway.center.y;
    Center.z = D_80111350_rockin_raceway.center.z;
    CRot.x = D_80111350_rockin_raceway.rot.x;
    CRot.y = D_80111350_rockin_raceway.rot.y;
    CRot.z = D_80111350_rockin_raceway.rot.z;
    CZoom = D_80111350_rockin_raceway.zoom;
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2E_rockin_raceway = 0;
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010C0D8_rockin_raceway);
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

// Camera debug mode: R cycles between free camera control and moving the camera info text.
void func_8010B89C_rockin_raceway(void) {
    RockinRacewayCamera delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (D_801115F0_rockin_raceway) {
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
                func_8010C7CC_rockin_raceway(delta.center.x, delta.center.y, delta.center.z, delta.rot.x, delta.rot.y,
                                             delta.rot.z, delta.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 104, D_800D5218_main);
            D_800EBE24_minigame = 0;
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_801115F4_rockin_raceway++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_801115F4_rockin_raceway--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_801115F8_rockin_raceway++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_801115F8_rockin_raceway--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 80, D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 88, D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 96, D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8(D_801115F4_rockin_raceway + 20, D_801115F8_rockin_raceway + 104, D_800D5218_main);
            break;
        default:
            D_800EBE24_minigame = 1;
            break;
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_801115F0_rockin_raceway & 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (++D_801115F0_rockin_raceway >= 3) {
            D_801115F0_rockin_raceway = 0;
        }
    }
}

// Interpolates the camera from the origin preset to the target preset over D_80111C2A_rockin_raceway frames.
void func_8010C0D8_rockin_raceway(omObjData *object) {
    f32 t;

    if (D_80111C2A_rockin_raceway <= 0) {
        func_8010D134_rockin_raceway(0);
        D_80111C2C_rockin_raceway = 0;
        return;
    }
    if (D_80111C28_rockin_raceway == 0) {
        Center.x = D_80111BE0_rockin_raceway[0].center.x;
        Center.y = D_80111BE0_rockin_raceway[0].center.y;
        Center.z = D_80111BE0_rockin_raceway[0].center.z;
        CRot.x = D_80111BE0_rockin_raceway[0].rot.x;
        CRot.y = D_80111BE0_rockin_raceway[0].rot.y;
        CRot.z = D_80111BE0_rockin_raceway[0].rot.z;
        CZoom = D_80111BE0_rockin_raceway[0].zoom;
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
        D_80111C2A_rockin_raceway = 0;
    } else {
        switch (D_80111C2E_rockin_raceway) {
            case 0:
                t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
                break;
            case 1:
                t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
                t = sindf(t * 90.0f);
                break;
            default:
                t = (f32)D_80111C28_rockin_raceway / (f32)D_80111C2A_rockin_raceway;
                t = sindf(t * 90.0f);
                t = t * t;
                break;
        }
        Center.x = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.x,
                                                D_80111BE0_rockin_raceway[1].center.x);
        Center.y = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.y,
                                                D_80111BE0_rockin_raceway[1].center.y);
        Center.z = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].center.z,
                                                D_80111BE0_rockin_raceway[1].center.z);
        CRot.x = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.x, D_80111BE0_rockin_raceway[1].rot.x);
        CRot.y = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.y, D_80111BE0_rockin_raceway[1].rot.y);
        CRot.z = func_8010E7E0_rockin_raceway(t, D_80111BE0_rockin_raceway[0].rot.z, D_80111BE0_rockin_raceway[1].rot.z);
        CZoom = func_8010E7C8_rockin_raceway(t, D_80111BE0_rockin_raceway[0].zoom, D_80111BE0_rockin_raceway[1].zoom);
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
        if (D_80111C28_rockin_raceway > 0) {
            D_80111C28_rockin_raceway--;
        } else {
            D_80111C28_rockin_raceway++;
        }
    }
    D_80111C2C_rockin_raceway = 1;
    func_8010D134_rockin_raceway(0);
}

void func_8010C5E0_rockin_raceway(s32 arg0) {
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
    D_80111BE0_rockin_raceway[arg0].center.x = Center.x;
    D_80111BE0_rockin_raceway[arg0].center.y = Center.y;
    D_80111BE0_rockin_raceway[arg0].center.z = Center.z;
    D_80111BE0_rockin_raceway[arg0].rot.x = CRot.x;
    D_80111BE0_rockin_raceway[arg0].rot.y = CRot.y;
    D_80111BE0_rockin_raceway[arg0].rot.z = CRot.z;
    D_80111BE0_rockin_raceway[arg0].zoom = CZoom;
    D_80111BE0_rockin_raceway[arg0].unk_1C = D_80111BE0_rockin_raceway[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010C7CC_rockin_raceway(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_80111C28_rockin_raceway = frames - 1;
        D_80111C2A_rockin_raceway = frames;
        if (x != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.x = x;
        } else {
            D_80111BE0_rockin_raceway[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.y = y;
        } else {
            D_80111BE0_rockin_raceway[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].center.z = z;
        } else {
            D_80111BE0_rockin_raceway[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.x = rotX;
        } else {
            D_80111BE0_rockin_raceway[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.y = rotY;
        } else {
            D_80111BE0_rockin_raceway[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].rot.z = rotZ;
        } else {
            D_80111BE0_rockin_raceway[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_80111BE0_rockin_raceway[0].zoom = zoom;
        } else {
            D_80111BE0_rockin_raceway[0].zoom = CZoom;
        }
        func_8010C5E0_rockin_raceway(1);
    }
}

void func_8010C9BC_rockin_raceway(void) {
    D_80111BD8_rockin_raceway->func = NULL;
}

void func_8010C9CC_rockin_raceway(void) {
    func_8010C5E0_rockin_raceway(0);
    func_8010C5E0_rockin_raceway(1);
    D_80111C2C_rockin_raceway = 0;
    D_80111C2A_rockin_raceway = 0;
    D_80111C28_rockin_raceway = 0;
    D_80111BD8_rockin_raceway->func = func_8010C0D8_rockin_raceway;
}

void func_8010CA1C_rockin_raceway(void) {
    HuCamera *camera;
    s32 i;

    D_80111C34_rockin_raceway = 0;
    D_80111C4C_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewayVec), TAG_OVERLAY);
    D_80111C30_rockin_raceway = omAddObj(31, 0, 0, -1, func_8010CE90_rockin_raceway);
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

void func_8010CADC_rockin_raceway(Vec *arg0, f32 arg1) {
    if (D_80111C30_rockin_raceway != NULL && D_80111C34_rockin_raceway < 16) {
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos[0] = arg0->x;
        do {
        } while (0); // splits the basic block so the entry address is recomputed
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos[1] = arg0->y;
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].pos[2] = arg0->z;
        D_80111C4C_rockin_raceway[D_80111C34_rockin_raceway].weight = arg1;
        D_80111C34_rockin_raceway++;
    }
}

void func_8010CB5C_rockin_raceway(RockinRacewayRacer *racer, f32 arg1) {
    Vec pos;

    pos.x = racer->pos.x + 100.0;
    pos.y = racer->pos.y + 100.0;
    pos.z = racer->pos.z;
    func_8010CADC_rockin_raceway(&pos, arg1);
    pos.x = racer->pos.x - 100.0;
    pos.y = racer->pos.y - 100.0;
    pos.z = racer->pos.z;
    func_8010CADC_rockin_raceway(&pos, arg1);
}

void func_8010CC10_rockin_raceway(void) {
    RockinRacewayVec *entry;
    f32 max[3];
    f32 min[3];
    s32 j;
    s32 i;

    if (D_80111C34_rockin_raceway > 0) {
        for (i = 0; i < 4; i++) {
            D_80111C38_rockin_raceway.pos[i] = 0.0f;
        }
        for (i = 0; i < D_80111C34_rockin_raceway; i++) {
            D_80111C38_rockin_raceway.pos[3] += D_80111C4C_rockin_raceway[i].weight;
        }
        for (i = 0; i < 3; i++) {
            max[i] = D_80111C4C_rockin_raceway[0].pos[i];
        }
        for (i = 0; i < 3; i++) {
            min[i] = D_80111C4C_rockin_raceway[0].pos[i];
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            entry = &D_80111C4C_rockin_raceway[i];
            for (j = 0; j < 3; j++) {
                if (max[j] < entry->pos[j]) {
                    max[j] = entry->pos[j];
                }
            }
        }
        for (i = 1; i < D_80111C34_rockin_raceway; i++) {
            entry = &D_80111C4C_rockin_raceway[i];
            for (j = 0; j < 3; j++) {
                if (min[j] > entry->pos[j]) {
                    min[j] = entry->pos[j];
                }
            }
        }
        for (i = 0; i < 3; i++) {
            D_80111C38_rockin_raceway.pos[i] = (max[i] + min[i]) * 0.5f;
        }
        if (D_80111C38_rockin_raceway.pos[3] >= 1.0f) {
            D_80111C38_rockin_raceway.pos[3] = 1.0f;
        }
    } else {
        D_80111C38_rockin_raceway.pos[0] = Center.x;
        D_80111C38_rockin_raceway.pos[1] = Center.y;
        D_80111C38_rockin_raceway.pos[2] = Center.z;
        D_80111C38_rockin_raceway.pos[3] = 0.0f;
    }
}

// Moves the camera to keep all of the registered focus points in view.
void func_8010CE90_rockin_raceway(omObjData *object) {
    f32 screen[2];
    f32 extent;
    f32 scale;
    s32 i;

    extent = 0.0f;
    func_8010CC10_rockin_raceway();
    Center.x = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway.pos[3], Center.x, D_80111C38_rockin_raceway.pos[0]);
    Center.y = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway.pos[3], Center.y, D_80111C38_rockin_raceway.pos[1]);
    Center.z = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway.pos[3], Center.z, D_80111C38_rockin_raceway.pos[2]);
    func_8010D134_rockin_raceway(0);
    for (i = 0; i < D_80111C34_rockin_raceway; i++) {
        func_8010D288_rockin_raceway(0, D_80111C4C_rockin_raceway[i].pos, NULL, screen);
        if (fabs(screen[0]) > extent) {
            extent = fabs(screen[0]);
        }
        if (fabs(screen[1]) > extent) {
            extent = fabs(screen[1]);
        }
    }
    if (extent != 0.0f) {
        scale = extent / 0.8f;
    } else {
        scale = 1.0f;
    }
    D_80111C38_rockin_raceway.zoom = scale * CZoom;
    if (D_80111AD8_rockin_raceway == 2) {
        if (D_80111C38_rockin_raceway.zoom < 1500.0f) {
            D_80111C38_rockin_raceway.zoom = 1500.0f;
        } else if (D_80111C38_rockin_raceway.zoom >= 5000.0f) {
            D_80111C38_rockin_raceway.zoom = 5000.0f;
        }
    } else if (D_80111C38_rockin_raceway.zoom < 1000.0f) {
        D_80111C38_rockin_raceway.zoom = 1000.0f;
    } else if (D_80111C38_rockin_raceway.zoom >= 5000.0f) {
        D_80111C38_rockin_raceway.zoom = 5000.0f;
    }
    CZoom = func_8010E7C8_rockin_raceway(D_80111C38_rockin_raceway.pos[3] * 0.5f, CZoom, D_80111C38_rockin_raceway.zoom);
    CRot.x = func_8010E608_rockin_raceway(318.38f, CRot.x, 10.0f);
    CRot.y = func_8010E608_rockin_raceway(0.0f, CRot.y, 10.0f);
    D_80111C34_rockin_raceway = 0;
}

void func_8010D104_rockin_raceway(void) {
    D_80111C30_rockin_raceway->func = NULL;
}

void func_8010D114_rockin_raceway(void) {
    D_80111C34_rockin_raceway = 0;
    D_80111C30_rockin_raceway->func = func_8010CE90_rockin_raceway;
}

void func_8010D134_rockin_raceway(s32 camIndex) {
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

#ifdef NON_MATCHING
// Only differs in float register allocation: viewZ and the sine result are swapped between f22 and f24.
// Projects pos with the camera; screen receives the pixel position and depth, and normalized the
// position relative to the screen center.
void func_8010D288_rockin_raceway(s32 camIndex, f32 *pos, f32 *screen, f32 *normalized) {
    HuCamera *camera = &gCameraList[camIndex];
    Mtx lookAt;
    Mtx mtx;
    u16(*integer)[4] = (u16(*)[4])mtx.m;
    u16(*fraction)[4] = (u16(*)[4])mtx.m[2];
    f32 viewZ;
    f32 depth;
    f32 viewX, viewY, viewZ;
    f32 depth;
    f32 x, y;

    guLookAt(&lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
             camera->up.x, camera->up.y, camera->up.z);
    func_80088850_main(&mtx, pos[0], pos[1], pos[2]);
    func_8007E040_main(&mtx, &lookAt, &mtx);
    viewX = (s32)(((u32)integer[3][0] << 16) | fraction[3][0]) >> 16;
    viewY = (s32)(((u32)integer[3][1] << 16) | fraction[3][1]) >> 16;
    viewZ = (s32)(((u32)integer[3][2] << 16) | fraction[3][2]) >> 16;
    depth = fabsf(viewZ * sindf(gCameraList[camIndex].fov / 2.0) / cosdf(gCameraList[camIndex].fov / 2.0));
    if (depth != 0.0) {
        x = camera->viewports[D_800D418E_main].vp.vscale[0] / 4.0 * viewX / depth / (4.0f / 3.0f);
        y = camera->viewports[D_800D418E_main].vp.vscale[1] / 4.0 * -viewY / depth;
        if (screen != NULL) {
            screen[0] = (s16)(x + camera->viewports[D_800D418E_main].vp.vtrans[0] * 0.25f);
            screen[1] = (s16)(y + camera->viewports[D_800D418E_main].vp.vtrans[1] * 0.25f);
            screen[2] = depth;
        }
        if (normalized != NULL) {
            normalized[0] = x / 160.0f;
            normalized[1] = y / 120.0f;
        }
    } else {
        screen[0] = screen[1] = screen[2] = 0.0f;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D288_rockin_raceway);
#endif

void func_8010D5B8_rockin_raceway(void) {
    RockinRacewayReplayFrame *pool = HuMemAllocTag(30 * sizeof(RockinRacewayReplayFrame), TAG_OVERLAY);

    D_80111C50_rockin_raceway = pool;
    memset(pool, 0, 30 * sizeof(RockinRacewayReplayFrame));
    D_80111C54_rockin_raceway = 0;
    D_80111C58_rockin_raceway = 0;
}

// Records the current race state into the next replay frame.
void func_8010D600_rockin_raceway(void) {
    RockinRacewayReplayFrame *frame = &D_80111C50_rockin_raceway[D_80111C58_rockin_raceway];
    RockinRacewayReplayRacer *replay;
    RockinRacewayRacer *racer;
    RockinRacewayModelState *state;
    RockinRacewayEffectState *effectState;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    frame->unk00 = D_80111AE4_rockin_raceway;
    for (i = 0; i < 4; i++) {
        frame->unk04[i] = D_80111AF0_rockin_raceway[i];
    }
    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[i]);
        replay = &frame->racers[i];
        replay->trans.x = D_800EC598_minigame[i]->trans.x;
        replay->trans.y = D_800EC598_minigame[i]->trans.y;
        replay->trans.z = D_800EC598_minigame[i]->trans.z;
        replay->rot.x = D_800EC598_minigame[i]->rot.x;
        replay->rot.y = D_800EC598_minigame[i]->rot.y;
        replay->rot.z = D_800EC598_minigame[i]->rot.z;
        replay->scale.x = D_800EC598_minigame[i]->scale.x;
        replay->scale.y = D_800EC598_minigame[i]->scale.y;
        replay->scale.z = D_800EC598_minigame[i]->scale.z;
        replay->unk24 = racer->unk38;
        replay->unk28 = racer->unk24;
    }
    for (state = frame->models, i = 1; i < 13; i++, state++) {
        if (D_80111B4C_rockin_raceway->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[D_80111B4C_rockin_raceway->model[i]];
        state->attr = model->attr;
        state->motTime = model->motTime;
        state->motSpeed = 0.0f;
        state->pos.x = model->pos.x;
        state->pos.y = model->pos.y;
        state->pos.z = model->pos.z;
        state->rot.x = model->rot.x;
        state->rot.y = model->rot.y;
        state->rot.z = model->rot.z;
        state->scale.x = model->scale.x;
        state->scale.y = model->scale.y;
        state->scale.z = model->scale.z;
    }
    for (effectState = frame->effects, effect = D_80111B5C_rockin_raceway, i = 0; i < 16;
         i++, effectState++, effect++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        effectState->active = effect->active;
        effectState->motTime = model->motTime;
        effectState->attr = model->attr;
        effectState->frame = effect->frame;
        effectState->speed = effect->speed;
        effectState->pos.x = model->pos.x;
        effectState->pos.y = model->pos.y;
        effectState->pos.z = model->pos.z;
        effectState->rot.x = model->rot.x;
        effectState->rot.y = model->rot.y;
        effectState->rot.z = model->rot.z;
        effectState->scale.x = model->scale.x;
        effectState->scale.y = model->scale.y;
        effectState->scale.z = model->scale.z;
    }
    D_80111C54_rockin_raceway++;
    D_80111C58_rockin_raceway++;
    if (D_80111C58_rockin_raceway >= 30) {
        D_80111C58_rockin_raceway -= 30;
    }
}

RockinRacewayReplayFrame *func_8010D944_rockin_raceway(s32 arg0) {
    s32 index = arg0;

    if (arg0 >= D_80111C54_rockin_raceway || arg0 >= 30) {
        return NULL;
    }
    if (D_80111C54_rockin_raceway >= 30) {
        index += D_80111C58_rockin_raceway;
    }
    if (index >= 30) {
        index -= 30;
    }
    return &D_80111C50_rockin_raceway[index];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_2C_rockin_raceway/251FF0", func_8010D9C4_rockin_raceway);

// Shifts the recorded replay frames so that the winner ends up ahead of the other racers.
void func_8010E08C_rockin_raceway(s32 winner) {
    RockinRacewayReplayRacer *replay;
    RockinRacewayRacer *racer;
    s32 angle;
    s32 i;
    s32 j;

    for (i = 0; i < 30; i++) {
        for (j = 0; j < 4; j++) {
            replay = &func_8010D944_rockin_raceway(i)->racers[j];
            if (j == winner) {
                replay->trans.x -= 0.1f * 200.0;
                replay->trans.x += i / 30.0f * (0.2f * 200.0);
            } else {
                replay->trans.x -= 0.1f * 200.0;
            }
        }
    }
    for (j = 0; j < 4; j++) {
        racer = (RockinRacewayRacer *)func_8010EC38_rockin_raceway(D_800EC598_minigame[j]);
        if (winner == j) {
            racer->unk44 += 0.1f * 200.0;
        } else {
            racer->unk44 -= 0.1f * 200.0;
        }
    }
    replay = &func_8010D944_rockin_raceway(29)->racers[winner];
    angle = 90.0f - replay->unk28;
    for (i = 0; i < 30; i++) {
        replay = &func_8010D944_rockin_raceway(i)->racers[winner];
        replay->unk28 += angle;
        if (replay->unk28 > 360.0f) {
            replay->unk28 -= 360.0f;
        } else if (replay->unk28 < 0.0f) {
            replay->unk28 += 360.0f;
        }
        replay->rot.x = sindf(replay->unk28) * replay->unk24 * 30.0f;
    }
}

void func_8010E2E4_rockin_raceway(void) {
    RockinRacewaySfx *sfx;
    s32 i;

    D_80111BD0_rockin_raceway = HuMemAllocTag(16 * sizeof(RockinRacewaySfx), TAG_OVERLAY);
    sfx = D_80111BD0_rockin_raceway;
    memset(sfx, 0, 16 * sizeof(RockinRacewaySfx));
    for (i = 0; i < 16; i++, sfx++) {
        sfx->soundId = -1;
    }
}

// Finds a free entry in the sfx pool, fills it in, and returns its index, or -1 if the pool is full.
s32 func_8010E344_rockin_raceway(s16 soundId, s16 frames, s16 unk04, s16 playerIndex) {
    RockinRacewaySfx *sfx = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16 && sfx->soundId != -1; i++, sfx++) {
    }
    if (i >= 16) {
        return -1;
    }
    sfx->soundId = soundId;
    sfx->frames = frames;
    sfx->unk04 = unk04;
    sfx->playerIndex = playerIndex;
    return i;
}

// Plays each queued sound once its delay has elapsed, then frees the entry.
void func_8010E39C_rockin_raceway(void) {
    RockinRacewaySfx *sfx = D_80111BD0_rockin_raceway;
    s32 i;

    for (i = 0; i < 16; i++, sfx++) {
        if (sfx->soundId == -1) {
            continue;
        }
        if (sfx->frames <= 0) {
            switch (sfx->unk04) {
                case 0:
                    HuAudFXPlay(sfx->soundId);
                    break;
                case 1:
                    func_8004AC98_main(sfx->soundId, sfx->playerIndex);
                    break;
                case 2:
                    CharFXPlay(sfx->soundId, GwPlayer[(s16)(sfx->playerIndex % 4)].chr);
                    break;
                default:
                    func_8004AC98_main(GwPlayer[(s16)(sfx->playerIndex % 4)].chr + sfx->soundId + 1, sfx->playerIndex);
                    break;
            }
            sfx->soundId = -1;
        }
        sfx->frames--;
    }
}

f32 func_8010E504_rockin_raceway(f32 arg0, f32 arg1) {
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

// Steps the angle current toward target by at most step degrees along the shorter direction.
f32 func_8010E608_rockin_raceway(f32 target, f32 current, f32 step) {
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

// Linearly interpolates from arg1 to arg2 by arg0.
f32 func_8010E7C8_rockin_raceway(f32 arg0, f32 arg1, f32 arg2) {
    return arg1 + arg0 * (arg2 - arg1);
}

f32 func_8010E7E0_rockin_raceway(f32 arg0, f32 arg1, f32 arg2) {
    return func_8010E608_rockin_raceway(arg2, arg1, fabsf(func_8010E504_rockin_raceway(arg2, arg1) * arg0));
}

// Evaluates a quadratic bezier curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E840_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 inv = 1.0 - arg0;

    return inv * inv * arg1 + (inv * arg0 * arg2) * 2.0 + arg0 * arg0 * arg3;
}

// Evaluates the quadratic bezier curve per component for 3-component vectors.
void func_8010E8A0_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *out++ = func_8010E840_rockin_raceway(arg0, *arg1++, *arg2++, *arg3++);
    }
}

// Evaluates a curve, blending arg1/arg2/arg3 as a function of arg0.
f32 func_8010E93C_rockin_raceway(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return ((arg0 - 1.0) * arg1 + (1.0 - 2.0 * arg0) * arg2 + arg0 * arg3) * 2.0;
}

// Computes the normalized tangent of the curve per component for 3-component vectors.
void func_8010E994_rockin_raceway(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    f32 tangent[3];
    f32 length;
    s32 i;

    for (i = 0; i < 3; i++) {
        tangent[i] = func_8010E93C_rockin_raceway(arg0, *arg1++, *arg2++, *arg3++);
    }
    length = sqrtf(tangent[0] * tangent[0] + tangent[1] * tangent[1] + tangent[2] * tangent[2]);
    if (length != 0.0f) {
        length = 1.0 / length;
        for (i = 0; i < 3; i++) {
            *out++ = length * tangent[i];
        }
    } else {
        *out++ = 0.0f;
        *out++ = 0.0f;
        *out = 1.0f;
    }
}

// Returns the angle of (arg0, arg1) in degrees, normalized to [0, 360).
f32 func_8010EB04_rockin_raceway(f32 arg0, f32 arg1) {
    f32 angle = atan2df(arg1, arg0);

    if (angle < 0.0) {
        angle += 360.0;
    } else if (angle >= 360.0) {
        angle -= 360.0;
    }
    return angle;
}

// Converts a direction vector into pitch and yaw angles, with zero roll.
void func_8010EB84_rockin_raceway(Vec *dir, f32 *rot) {
    *rot++ = func_8010EB04_rockin_raceway(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = func_8010EB04_rockin_raceway(dir->z, dir->x);
    *rot = 0.0f;
}

void func_8010EC0C_rockin_raceway(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_8010EC38_rockin_raceway(omObjData *object) {
    RockinRacewayWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

s32 func_8010EC8C_rockin_raceway(HuSprite_Unk84_Struct *sprite, u8 *color) {
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
    model = func_8001A894_main(0x18C1, buffer, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x71010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_8010FBAC_rockin_raceway(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_801116F0_rockin_raceway));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
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

s32 func_8010F874_rockin_raceway(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color) {
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

void func_8010FA78_rockin_raceway(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
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

s32 func_8010FBAC_rockin_raceway(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
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

s32 func_8010FFB8_rockin_raceway(HuSprite_Unk84_Struct *sprite, RockinRacewayQuad *quad) {
    u8 *buffer;
    Gfx *gfx;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    buffer = (u8 *)gfx;
    model = func_8001A894_main(0x4C1, buffer, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x1000000;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    for (i = 0; i < D_800D1FF0_main; i++) {
        data->unk44[i] = HuMemAllocTag(sizeof(RockinRacewayQuad), data->unk0E);
        *(RockinRacewayQuad *)data->unk44[i] = *quad;
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(D_801116F0_rockin_raceway));
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_1CYCLE);
    gDPPipeSync(gfx++);
    gSPClearGeometryMode(gfx++, G_CULL_BOTH | G_LIGHTING);
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_TEXTURE_GEN_LINEAR);
    gDPSetColorDither(gfx++, G_CD_NOISE);
    gDPSetTexturePersp(gfx++, G_TP_NONE);
    gDPSetTextureFilter(gfx++, G_TF_BILERP);
    gDPSetTextureConvert(gfx++, G_TC_FILT);
    gDPSetAlphaDither(gfx++, G_AD_PATTERN);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetBlendColor(gfx++, 1, 1, 1, 1);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_ZB_XLU_SURF, G_RM_NOOP2);
    if (sprite->unk18 & 0x8000) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0);
    }
    gSPSegment(gfx++, 1, osVirtualToPhysical(data->unk44[0]));
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
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x200, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->unk00->unk00));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

// Shows a character face sprite above each of the 4 slots, or a blank one for a negative player.
void func_80110C38_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *players) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (players[i] < 0) {
            func_8010FA78_rockin_raceway(models[i], sprite, 8, D_80111730_rockin_raceway);
        } else {
            if (players[i] >= 4) {
                players[i] = 0;
            }
            func_8010FA78_rockin_raceway(models[i], sprite, GwPlayer[players[i]].chr, D_80111730_rockin_raceway);
        }
        Hu3DModelPosSet(models[i], D_80111414_rockin_raceway[i].x, D_80111414_rockin_raceway[i].y + 0.2f * 200.0,
                        D_80111414_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}

// Shows a digit sprite for each of the 12 digits in D_80111B00_rockin_raceway, clamped to 0-9.
void func_80110D90_rockin_raceway(s16 *models, HuSprite_Unk84_Struct *sprite, s32 *values) {
    s32 *digits = D_80111B00_rockin_raceway[0];
    s32 i;

    for (i = 0; i < 12; i++) {
        if (digits[i] >= 9) {
            digits[i] = 9;
        } else if (digits[i] < 0) {
            digits[i] = 0;
        }
        func_8010FA78_rockin_raceway(models[i], sprite, digits[i], D_80111734_rockin_raceway);
        Hu3DModelPosSet(models[i], D_80111444_rockin_raceway[i].x, D_80111444_rockin_raceway[i].y + 0.2f * 200.0,
                        D_80111444_rockin_raceway[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}
