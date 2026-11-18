#include "common.h"
#include "game/camera.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"
#include "game/overlays/mgcamera.h"
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

// Several distances are written as a float fraction of 200 units (e.g. 0.1f * 200.0), which folds into
// a double constant slightly off from the round value.

// Table of 2 rows (RockinRacewaySnapshotRow) of 4 of these allocated in m244_PlayerObjCreateAll, stored in
// m244_ghostTbl. m244_GhostStore records each racer object's transform.
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

// Vertex quad copied into each of a model's vertex buffers by m244_QuadMdlCreate.
typedef struct RockinRacewayQuad {
    /* 0x00 */ Vtx_t vtx[4];
} RockinRacewayQuad; // Size 0x40

// Saved model state, see m244_SparkStateSave and m244_SparkStateRestore.
typedef struct RockinRacewayModelState {
    /* 0x00 */ s32 attr;
    /* 0x04 */ f32 motTime;
    /* 0x08 */ f32 motSpeed;
    /* 0x0C */ Vec pos;
    /* 0x18 */ Vec rot;
    /* 0x24 */ Vec scale;
} RockinRacewayModelState; // Size 0x30

// Pool of 16 of these allocated in m244_SmokeInit, stored in m244_smokeTbl.
// m244_SmokeCreate claims a free entry, and m244_SmokeObjMain animates the
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
// (see m244_WorkPtrSet / m244_WorkPtrGet).
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

// Saved sprite effect state, see m244_SmokeStateSave and m244_SmokeStateRestore.
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

// A recorded frame of the race state, see m244_ReplayRecord.
typedef struct RockinRacewayReplayFrame {
    /* 0x000 */ s32 unk00;
    /* 0x004 */ s32 unk04[4];
    /* 0x014 */ RockinRacewayReplayRacer racers[4];
    /* 0x0C4 */ RockinRacewayModelState models[12];
    /* 0x304 */ RockinRacewayEffectState effects[16];
} RockinRacewayReplayFrame; // Size 0x644

// Walks the model states and then the effect states of the previous replay frame in
// m244_ReplayPlay.
typedef union RockinRacewayReplayStatePtr {
    RockinRacewayModelState *model;
    RockinRacewayEffectState *effect;
} RockinRacewayReplayStatePtr;

// Array of 4 of these allocated in m244_TrackInit, stored in m244_trackTbl
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
} RockinRacewayTrack; // Size 0x24

// Pool of 16 of these allocated in m244_SeQueueInit, stored in m244_seQueue.
// m244_SeQueueAdd claims a free entry for a request, and m244_SeQueueUpdate
// consumes requests until they expire, setting soundId back to -1 when done.
typedef struct {
    /* 0x00 */ s16 soundId; // -1 marks a free entry
    /* 0x02 */ s16 frames;  // counted down once per frame
    /* 0x04 */ s16 unk04;   // switched on as a type by m244_SeQueueUpdate
    /* 0x06 */ s16 playerIndex;
} RockinRacewaySfx; // Size 0x8

// Pool of 16 of these allocated in m244_CameraFocusInit, stored in m244_cameraFocusTbl.
// m244_CameraFocusAdd appends entries, and m244_CameraFocusCalc centers the camera
// focus m244_cameraFocus on the bounding box of the entries, accumulating their weights.
typedef struct {
    /* 0x00 */ f32 pos[3];
    /* 0x0C */ f32 weight;
} RockinRacewayVec; // Size 0x10

// Camera target computed from the RockinRacewayVec entries by m244_CameraFocusCalc.
typedef struct {
    /* 0x00 */ f32 pos[4]; // x, y, z, and the accumulated weight of the entries
    /* 0x10 */ f32 zoom;
} RockinRacewayFocus; // Size 0x14

// Per-track lap meter sprite layout, built in m244_GaugeCreate.
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

// Values shown by the HUD built in m244_StageObjInit.
typedef struct {
    /* 0x00 */ s32 players[4];
    /* 0x10 */ s32 times[2]; // current and record time, in frames
} RockinRacewayHudValues;    // Size 0x18

// Racer standing used to sort the racers in m244_RankCalc.
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

// Pool of 8 of these allocated in m244_PanelCreateAll, stored in m244_panelTbl.
// m244_PanelCreate claims a free entry for a pair of blinking marker models, and
// m244_PanelObjMain animates the entries each frame, alternating the visible model every
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

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[2];
    /* 0x06 */ s16 unk06;
} RockinRacewayHudGrp; // Size 0x8

extern GAMEMES gMesData[];
extern s16 Hu3DModelTag;
extern s16 Hu3DCamMtxNo;
extern u8 omAllPauseF;
extern u8 Hu3DBufNo;
f32 m244_track0NodeTbl[20][3] = {
    { 704.785f, 0.0f, -699.55f },
    { 201.485f, 0.0f, -705.05f },
    { -294.435f, 0.0f, -705.05f },
    { -801.855f, 0.0f, -710.0f },
    { -986.52f, 0.0f, -629.3f },
    { -1153.55f, 0.0f, -519.15f },
    { -1278.255f, 0.0f, -365.4f },
    { -1350.875f, 0.0f, -188.65f },
    { -1376.325f, 0.0f, 1.4f },
    { -1353.34f, 0.0f, 186.6f },
    { -1275.89f, 0.0f, 363.35f },
    { -1152.43f, 0.0f, 513.45f },
    { -989.035f, 0.0f, 632.1f },
    { -800.13f, 0.0f, 698.7f },
    { -308.055f, 0.0f, 699.75f },
    { 299.445f, 0.0f, 699.75f },
    { 787.435f, 0.0f, 704.75f },
    { 980.315f, 0.0f, 633.85f },
    { 1143.355f, 0.0f, 515.55f },
    { 1268.58f, 0.0f, 364.75f }
};
f32 m244_track1NodeTbl[20][3] = {
    { 698.385f, 0.0f, -607.55f },
    { 202.65f, 0.0f, -613.3f },
    { -292.17f, 0.0f, -624.85f },
    { -777.295f, 0.0f, -619.1f },
    { -937.375f, 0.0f, -547.5f },
    { -1076.53f, 0.0f, -442.5f },
    { -1183.765f, 0.0f, -312.4f },
    { -1254.48f, 0.0f, -161.75f },
    { -1275.04f, 0.0f, -6.5f },
    { -1249.91f, 0.0f, 162.4f },
    { -1183.76f, 0.0f, 315.35f },
    { -1081.105f, 0.0f, 445.45f },
    { -937.39f, 0.0f, 548.2f },
    { -773.115f, 0.0f, 609.8f },
    { -305.52f, 0.0f, 611.15f },
    { 301.515f, 0.0f, 616.5f },
    { 765.37f, 0.0f, 610.85f },
    { 932.645f, 0.0f, 550.75f },
    { 1069.645f, 0.0f, 447.45f },
    { 1180.59f, 0.0f, 316.0f }
};
f32 m244_track2NodeTbl[20][3] = {
    { 699.23f, 0.0f, -517.35f },
    { 203.075f, 0.0f, -525.15f },
    { -299.32f, 0.0f, -530.1f },
    { -748.01f, 0.0f, -515.15f },
    { -882.0f, 0.0f, -463.1f },
    { -1005.37f, 0.0f, -380.85f },
    { -1095.59f, 0.0f, -266.7f },
    { -1148.435f, 0.0f, -138.95f },
    { -1172.27f, 0.0f, 0.65f },
    { -1155.245f, 0.0f, 135.25f },
    { -1095.645f, 0.0f, 268.1f },
    { -1003.655f, 0.0f, 377.15f },
    { -886.2f, 0.0f, 465.7f },
    { -748.21f, 0.0f, 520.25f },
    { -297.04f, 0.0f, 523.75f },
    { 295.995f, 0.0f, 519.85f },
    { 740.775f, 0.0f, 523.75f },
    { 877.835f, 0.0f, 464.55f },
    { 992.225f, 0.0f, 376.9f },
    { 1088.745f, 0.0f, 269.6f }
};
f32 m244_track3NodeTbl[20][3] = {
    { 701.125f, 0.0f, -421.1f },
    { 202.54f, 0.0f, -419.7f },
    { -303.185f, 0.0f, -424.85f },
    { -716.595f, 0.0f, -419.3f },
    { -833.05f, 0.0f, -380.45f },
    { -931.415f, 0.0f, -309.8f },
    { -1004.03f, 0.0f, -220.2f },
    { -1050.36f, 0.0f, -113.6f },
    { -1067.345f, 0.0f, -0.8f },
    { -1051.89f, 0.0f, 113.5f },
    { -1007.115f, 0.0f, 218.55f },
    { -931.46f, 0.0f, 309.75f },
    { -835.715f, 0.0f, 377.7f },
    { -719.915f, 0.0f, 428.7f },
    { -303.6f, 0.0f, 429.95f },
    { 302.365f, 0.0f, 429.95f },
    { 711.44f, 0.0f, 429.95f },
    { 826.63f, 0.0f, 385.3f },
    { 925.47f, 0.0f, 314.3f },
    { 1000.045f, 0.0f, 220.2f }
};
// Node positions of each track.
f32 (*m244_trackNodeTbl[4])[3] = {
    m244_track0NodeTbl,
    m244_track1NodeTbl,
    m244_track2NodeTbl,
    m244_track3NodeTbl
};
// Node count per track is [i][1].
u16 m244_trackNodeNumTbl[4][2] = { { 0, 20 }, { 0, 20 }, { 0, 20 }, { 0, 20 } };
s32 m244_goalNodeTbl[4] = { 15, 15, 15, 15 };
// Pairs of track node indices per racer; [i][1] is used.
u16 m244_panelNodeTbl[4][2] = { { 8, 14 }, { 8, 14 }, { 8, 14 }, { 8, 14 } };
f32 m244_rankAccelTbl[4] = { 1.0f, 1.1f, 1.2f, 1.4f };
f32 m244_rankSpeedTbl[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
// Per CPU difficulty.
f32 m244_comSpeedTbl[4][2] = {
    { 0.6f, 0.7f },
    { 0.7f, 0.8f },
    { 0.8f, 0.9f },
    { 0.9f, 0.99f }
};
s32 m244_comMashWaitTbl[4] = { 5, 4, 3, 2 }; // per CPU difficulty
RockinRacewayPos16 m244_gaugePosTbl[4] = { { 30, 30 }, { 270, 30 }, { 30, 211 }, { 270, 211 } };
s16 m244_timeDigitXTbl[8] = { 118, 130, 138, 150, 162, 172, 184, 196 };
MgCameraPreset m244_cameraPresetTbl[7] = {
    { { 0.0f, -288.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 4278.0f },
    { { 0.0f, 200.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 4278.0f },
    { { 136.0f, -94.8f, -1001.8f }, { 341.0f, 305.5f, 0.0f }, 952.0f },
    { { 1126.0f, -94.8f, -721.8f }, { 341.0f, 305.5f, 0.0f }, 952.0f },
    { { 246.0f, 33.2f, -693.8f }, { 350.3f, 285.4f, 0.0f }, 1140.0f },
    { { 0.0f, 200.8f, -65.0f }, { 326.0f, 0.0f, 0.0f }, 3278.0f },
    { { 340.0f, -200.0f, 165.0f }, { 326.0f, 0.0f, 0.0f }, 1678.0f }
};
Vec m244_boardFacePosTbl[4] = {
    { -384.5f, 56.6f, -88.4f },
    { -387.95f, 39.8f, 85.75f },
    { -129.3f, 56.6f, -88.4f },
    { -129.3f, 39.8f, 85.75f }
};
Vec m244_boardDigitPosTbl[12] = {
    { 58.4f, 58.75f, -92.85f },
    { 126.8f, 58.75f, -92.85f },
    { 222.3f, 58.75f, -92.85f },
    { 290.7f, 58.75f, -92.85f },
    { 397.8f, 58.75f, -92.85f },
    { 466.15f, 58.75f, -92.85f },
    { 58.4f, 43.75f, 82.0f },
    { 126.8f, 43.75f, 82.0f },
    { 222.3f, 43.75f, 82.0f },
    { 290.7f, 43.75f, 82.0f },
    { 397.8f, 43.75f, 82.0f },
    { 466.15f, 43.75f, 82.0f }
};
u8 m244_smokeColor[4] = { 0xE9, 0xDD, 0xA1, 0xFF };
RockinRacewayQuad m244_boardFaceQuad = { { { { 67, -67, 0 }, 0, { 0x7C0, 0 }, { 0, 0, 0, 255 } },
                                                  { { 67, 67, 0 }, 0, { 0x7C0, 0x7C0 }, { 0, 0, 0, 255 } },
                                                  { { -65, -67, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } },
                                                  { { -67, 67, 0 }, 0, { 0, 0x7C0 }, { 0, 0, 0, 255 } } } };
RockinRacewayQuad m244_boardDigitQuad = { { { { 29, -62, 0 }, 0, { 0x3C0, 0 }, { 0, 0, 0, 255 } },
                                                  { { 29, 62, 0 }, 0, { 0x3C0, 0x7C0 }, { 0, 0, 0, 255 } },
                                                  { { -29, -62, 0 }, 0, { 0, 0 }, { 0, 0, 0, 255 } },
                                                  { { -29, 62, 0 }, 0, { 0, 0x7C0 }, { 0, 0, 0, 255 } } } };
s32 m244_prevPhase = -1; // state on the previous frame
s32 m244_exitTimer = 0;
// Racer slot per racer is [i][1].
u16 m244_racerPlayerTbl[4][2] = { { 0, 0 }, { 0, 1 }, { 0, 2 }, { 0, 3 } };
s32 m244_trackRacerTbl[4] = { -1, -1, -1, -1 };           // racer slot occupying each track, or -1
u16 m244_carMdlTbl[8] = { 1, 2, 3, 4, 5, 6, 12, 13 }; // model file per character
s32 m244_ghostLayerTbl[3] = { 0, 0x400, 0x800 };
RockinRacewayHudValues m244_boardDisp = { { -1, -1, -1, -1 }, { 0, 0 } };
u8 m244_boardColor[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
// Sprite file per character.
s32 m244_gaugeFaceSprTbl[8] = {
    0x00210008, 0x00210009, 0x0021000A, 0x0021000B, 0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F
};
s32 m244_timeDigitMemberTbl[6] = { 0, 1, 3, 4, 6, 7 }; // sprite member of each time digit
s32 m244_cameraDebugMode = 0;                       // camera debug mode
s32 m244_cameraDebugX = 0;                       // camera debug text x
s32 m244_cameraDebugY = 0;                       // camera debug text y
s32 m244_replayPrevNo = -1;                      // replay frame last played back
Gfx m244_gfxRdpInit[] = {
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
Gfx m244_gfxRspInit[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};
Gfx m244_gfxInit[] = {
    gsSPDisplayList(m244_gfxRspInit),
    gsSPDisplayList(m244_gfxRdpInit),
    gsSPEndDisplayList(),
};
Gfx m244_gfxBillboardInit[] = {
    gsDPPipeSync(),
    gsSPDisplayList(m244_gfxInit),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};
u8 m244_faceColor[4] = { 0xFF, 0xFF, 0xFF, 0xFF };
u8 m244_digitColor[4] = { 0xFF, 0xFF, 0xFF, 0xFF };

s32 m244_replayFrameTime BSS; // frames spent on the current replay frame
omObjData *m244_mainObj BSS;
s32 m244_flag10F BSS;
s32 m244_frameCnt BSS;
s32 m244_phaseTimer BSS;
s32 m244_resultWait BSS;
s32 m244_phase BSS;
s32 m244_phaseStep BSS;
s16 m244_raceStartF BSS;
s32 m244_raceTime BSS;
s32 m244_recordTime BSS;
s32 m244_timer BSS;
s32 m244_rankOrderTbl[4] BSS;
s32 m244_timeDigitTbl[2][6] BSS;
RockinRacewayRacer *m244_racerTbl BSS;
s16 m244_winnerNo BSS;
s16 m244_newRecordF BSS;
s16 m244_photoMode BSS;
s16 m244_ghostDispF BSS;
RockinRacewaySnapshotRow *m244_ghostTbl BSS;
RockinRacewayTrack *m244_trackTbl BSS;
f32 m244_trackLenMin BSS;
RockinRacewayFx *m244_panelTbl BSS;
omObjData *m244_sparkObj BSS;
RockinRacewayModelState *m244_sparkStateTbl BSS;
s16 m244_sparkPauseF BSS;
omObjData *m244_smokeObj BSS;
RockinRacewayEffect *m244_smokeTbl BSS;
RockinRacewayEffectState *m244_smokeStateTbl BSS;
s16 m244_smokePauseF BSS;
s16 *m244_sprTbl BSS;
s16 m244_gaugeGrpTbl[4] BSS;
RockinRacewayHudGrp m244_hudGrp BSS;
u8 m244_hudGrpPad[4] BSS; /* Unreferenced. */
RockinRacewayMeter m244_gaugeTbl[4] BSS;
RockinRacewaySfx *m244_seQueue BSS;
s16 m244_cheerSeNo BSS;
s16 m244_cheerSeDelay BSS;
omObjData *m244_cameraMoveObj BSS;
u8 m244_cameraMoveObjPad[4] BSS;                  /* Unreferenced. */
MgCameraKey m244_cameraKeyTbl[2] BSS;         // target, origin
s16 m244_cameraMoveTimer BSS;
s16 m244_cameraMoveTime BSS;
s16 m244_cameraMoveF BSS;
s16 m244_cameraMoveMode BSS;
omObjData *m244_cameraFocusObj BSS;
s16 m244_cameraFocusNum BSS;
RockinRacewayFocus m244_cameraFocus BSS;
RockinRacewayVec *m244_cameraFocusTbl BSS;
// Ring buffer of 30 replay frames, see m244_ReplayRecord and m244_ReplayFrameGet.
// m244_replayCnt counts recorded frames and m244_replayNo is the next slot.
RockinRacewayReplayFrame *m244_replayTbl BSS;
s32 m244_replayCnt BSS;
s32 m244_replayNo BSS;

/* Fields of m244_hudGrp, aliased in undefined_syms.txt. */
extern s16 m244_replayGrp;
extern s16 m244_timeGrpTbl[2];
extern s16 m244_recordPulse;

const s16 m244_startMesTbl[] = { 0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000 };
const s16 m244_finishMesTbl[] = { 0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000 };

void m244_MainObjInit(omObjData *object);
void m244_MainObjMain(omObjData *object);
void m244_ExitObjMain(omObjData *object);
void m244_ExitCheck(omObjData *object);
void m244_GhostStore(s32 row, s16 arg1);
void m244_RankCalc(s32 *order);
s32 m244_WinnerGet(void);
void m244_SparkStateSave(void);
void m244_SparkStateRestore(void);
void m244_SmokeStateSave(void);
void m244_SmokeStateRestore(void);
void m244_BoardFaceSet(s32 *players);
void m244_BoardTimeSet(s32 *values);
void m244_TimeUpdate(void);
void m244_CameraMoveStop(void);
void m244_CameraMoveResume(void);
void m244_CameraFocusInit(void);
void m244_CameraFocusStop(void);
void m244_CameraFocusStart(void);
void m244_ReplayRecord(void);
void m244_ReplayPlay(s32 index);
void m244_ReplayWinnerAdjust(s32 winner);
void m244_SeQueueUpdate(void);
void m244_PlayerObjCreateAll(void);
void m244_PlayerObjInit(omObjData *object);
void m244_PlayerObjMain(omObjData *object);
void m244_PlayerComInput(omObjData *object);
void m244_RacerAccelUpdate(RockinRacewayRacer *racer);
void m244_RacerGaugeUpdate(RockinRacewayRacer *racer);
void m244_RacerSpinUpdate(RockinRacewayRacer *racer);
void m244_RacerMove(omObjData *object);
void m244_RacerFocusAdd(RockinRacewayRacer *racer, f32 arg1);
void m244_GaugeCreate(s16 track, s16 character);
void m244_WorkPtrSet(omObjData *arg0, u32 arg1);
void m244_PanelCreateAll(void);
void m244_PanelObjMain(omObjData *object);
s32 m244_PanelCreate(Vec *arg0, s32 arg1, u16 arg2);
void m244_PanelHitUpdate(void);
void m244_SparkInit(void);
void m244_SparkObjMain(omObjData *object);
void m244_SmokeInit(void);
void m244_SmokeObjMain(omObjData *object);
void m244_StageObjCreate(void);
void m244_StageObjInit(omObjData *object);
void m244_SparkCreate(f32 x, f32 y, f32 z);
s32 m244_SeQueueAdd(s16 soundId, s16 frames, s16 unk04, s16 playerIndex);
void m244_RacerSmokeCreate(RockinRacewayRacer *racer);
f32 m244_AngleDiffCalc(f32 arg0, f32 arg1);
f32 m244_AngleStepCalc(f32 target, f32 current, f32 step);
u32 m244_WorkPtrGet(omObjData *object);
u16 m244_SprAnimRead(s32 dirAndFile);
s32 m244_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color);
s32 m244_QuadMdlCreate(HuSprAnimData *sprite, RockinRacewayQuad *quad);
void m244_TimeDigitCalc(s32 *frames);
void m244_StageObjMain(omObjData *object);
s32 m244_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color);
void m244_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color);
void m244_TrackInit(void);
void m244_ReplaySprInit(void);
s32 m244_TrackNodeTypeGet(u16 arg0, u16 arg1);
f32 m244_AngleInterpCalc(f32 arg0, f32 arg1, f32 arg2);
f32 m244_BezierCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
void m244_BezierVecCalc(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out);
void m244_BezierTangentVecCalc(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out);
void m244_DirRotCalc(Vec *dir, f32 *rot);
f32 m244_TrackPosCalc(u16 track, f32 arg1, f32 distance, f32 speed, u16 *node, f32 *fraction, Vec *pos, Vec *rot);
void m244_TimeInit(void);
void m244_CameraInit(void);
void m244_GaugeObjMain(omObjData *object);
void m244_GaugeUpdate(s16 track, s16 progress, u16 state);
void m244_CameraMoveObjMain(omObjData *object);
void m244_CameraKeyStore(s32 arg0);
void m244_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void m244_CameraFocusObjMain(omObjData *object);
void m244_CameraPosUpdate(s32 camIndex);
void m244_ScreenPosCalc(s32 camIndex, f32 *pos, f32 *screen, f32 *normalized);
f32 m244_InterpCalc(f32 arg0, f32 arg1, f32 arg2);
void m244_ReplayInit(void);
void m244_SeQueueInit(void);
void m244_BoardFaceUpdate(s16 *models, HuSprAnimData *sprite, s32 *players);
void m244_BoardDigitUpdate(s16 *models, HuSprAnimData *sprite, s32 *values);
s32 m244_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void m244_ObjectSetup(void) {
    u8 camIndex;

    MapCollInit(50);
    omInitObjMan(50, 0);
    omGameSysInit();
    Hu3DSprModelInit(64);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 67.0f, 16.0f, 98.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 1.0f, 50.0f, -108.0f);
    Hu3DGLightMaxSet(2);
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 6000.0f);
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    mgItemObjNum = 0;
    m244_frameCnt = 0;
    m244_phaseTimer = 0;
    m244_resultWait = 0;
    m244_phase = 0;
    m244_phaseStep = 0;
    m244_raceStartF = 0;
    m244_cheerSeNo = -1;
    m244_cheerSeDelay = -1;
    m244_newRecordF = 0;
    m244_photoMode = 0;
    m244_raceTime = 0;
    m244_timer = 5400;
    m244_recordTime = GWMgRecordGet(3);
    if (m244_recordTime == 0) {
        m244_recordTime = 9000;
    }
    m244_cameraMoveObj = NULL;
    m244_cameraFocusObj = NULL;
    m244_sprTbl = HuMemAllocTag(0x40, TAG_OVERLAY);
    m244_mainObj = omAddObj(0x20, 0, 0, -1, m244_MainObjInit);
    GMesFontMesCreate(m244_startMesTbl, 1);
    GMesFontMesCreate(m244_finishMesTbl, 1);
}

void m244_MainObjInit(omObjData *object) {
    object->func = m244_MainObjMain;
    m244_TrackInit();
    m244_StageObjCreate();
    m244_SparkInit();
    m244_SmokeInit();
    m244_ReplaySprInit();
    m244_TimeInit();
    m244_PlayerObjCreateAll();
    m244_PanelCreateAll();
    m244_SeQueueInit();
    m244_CameraInit();
    m244_ReplayInit();
    if (_CheckFlag(10)) {
        m244_flag10F = 1;
    }
}

void m244_MainObjMain(omObjData *object) {
    s32 times[2];
    RockinRacewayRacer *racer;
    RockinRacewayRacer *other;
    omObjData *leaderObj;
    omObjData *otherObj;
    f32 t;
    s16 mes;
    s32 i;

    times[0] = 0;
    times[1] = 0;
    m244_ExitCheck(object);
    m244_SeQueueUpdate();
    if (m244_cheerSeDelay >= 0) {
        if (--m244_cheerSeDelay == 0) {
            m244_cheerSeNo = HuAudFXPlay(0x470);
            HuAudFXVolSet(m244_cheerSeNo, 64);
            HuAudFXPitchSet(m244_cheerSeNo, 0);
            m244_cheerSeDelay = -1;
        }
    }
    switch (m244_phase) {
        case 0:
            m244_phase = 1;
            m244_phaseStep = 0;
            break;
        case 1:
            switch (m244_phaseStep) {
                case 0:
                    HuAudFXPlay(0x46F);
                    m244_CameraMoveStart(m244_cameraPresetTbl[1].center.x, m244_cameraPresetTbl[1].center.y,
                                                 m244_cameraPresetTbl[1].center.z, m244_cameraPresetTbl[1].rot.x,
                                                 m244_cameraPresetTbl[1].rot.y, m244_cameraPresetTbl[1].rot.z,
                                                 m244_cameraPresetTbl[1].zoom, 19);
                    m244_cameraMoveMode = 0;
                    m244_phaseStep++;
                    break;
                case 2:
                    m244_CameraMoveStart(m244_cameraPresetTbl[2].center.x, m244_cameraPresetTbl[2].center.y,
                                                 m244_cameraPresetTbl[2].center.z, m244_cameraPresetTbl[2].rot.x,
                                                 m244_cameraPresetTbl[2].rot.y, m244_cameraPresetTbl[2].rot.z,
                                                 m244_cameraPresetTbl[2].zoom, 75);
                    m244_cameraMoveMode = 0;
                    m244_phaseStep++;
                    break;
                case 4:
                    if (m244_phaseTimer >= 5) {
                        m244_phaseStep++;
                    }
                    break;
                case 6:
                    m244_CameraMoveStart(m244_cameraPresetTbl[3].center.x, m244_cameraPresetTbl[3].center.y,
                                                 m244_cameraPresetTbl[3].center.z, m244_cameraPresetTbl[3].rot.x,
                                                 m244_cameraPresetTbl[3].rot.y, m244_cameraPresetTbl[3].rot.z,
                                                 m244_cameraPresetTbl[3].zoom, 75);
                    m244_cameraMoveMode = 0;
                    m244_phaseTimer = 0;
                    m244_phaseStep++;
                    break;
                case 8:
                    m244_CameraMoveStart(m244_cameraPresetTbl[4].center.x, m244_cameraPresetTbl[4].center.y,
                                                 m244_cameraPresetTbl[4].center.z, m244_cameraPresetTbl[4].rot.x,
                                                 m244_cameraPresetTbl[4].rot.y, m244_cameraPresetTbl[4].rot.z,
                                                 m244_cameraPresetTbl[4].zoom, 45);
                    m244_cameraMoveMode = 2;
                    m244_phaseStep++;
                    break;
                case 10:
                    if (m244_phaseTimer != 3) {
                        if (m244_phaseTimer > 3) {
                            m244_phase = 2;
                            m244_phaseStep = 0;
                        }
                    }
                    break;
                default:
                    if (m244_phaseStep == 9 && m244_phaseTimer == 20) {
                        GMesCreate(GMES_MES_3);
                        HuAudSeqPlay(0x2E);
                    }
                    if (m244_cameraMoveF == 0) {
                        if (m244_phaseStep == 3) {
                            HuAudSeqPlay(0x6D);
                        }
                        m244_phaseTimer = 0;
                        m244_phaseStep++;
                    }
                    break;
            }
            break;
        case 2:
            if (m244_phaseTimer == 8) {
                HuAudFXPlay(0x46C);
            }
            if (m244_phaseTimer == 30) {
                m244_raceStartF = 1;
            }
            if (m244_phaseTimer == 20) {
                m244_CameraMoveStop();
                m244_CameraFocusInit();
            }
            m244_RankCalc(m244_rankOrderTbl);
            if (m244_raceStartF != 0) {
                times[0] = ++m244_raceTime;
                times[1] = m244_recordTime;
                m244_TimeDigitCalc(times);
                m244_BoardFaceSet(m244_rankOrderTbl);
                m244_BoardTimeSet(times);
                m244_ReplayRecord();
                m244_timer--;
            }
            if (m244_timer == 900) {
                mes = GMesCreate(GMES_MES_TIMER, 30, 156, 56);
                gMesData[mes].pos.x = 156.0f;
                gMesData[mes].pos.y = 56.0f;
            } else if (m244_timer < 900) {
                GMesTimerValueSet((m244_timer + 29) / 30);
                if (m244_timer == 0) {
                    GMesTimerEnd();
                }
            }
            m244_winnerNo = m244_WinnerGet();
            if (m244_winnerNo == -1 && m244_timer > 0) {
                break;
            }
            m244_CameraFocusStop();
            m244_CameraMoveResume();
            m244_CameraMoveStart(m244_cameraPresetTbl[5].center.x, m244_cameraPresetTbl[5].center.y,
                                         m244_cameraPresetTbl[5].center.z, m244_cameraPresetTbl[5].rot.x,
                                         m244_cameraPresetTbl[5].rot.y, m244_cameraPresetTbl[5].rot.z,
                                         m244_cameraPresetTbl[5].zoom, 10);
            m244_cameraMoveMode = 2;
            if (m244_winnerNo != -1) {
                leaderObj = mgPlayerObjTbl[m244_rankOrderTbl[0]];
                racer = (RockinRacewayRacer *)m244_WorkPtrGet(leaderObj);
                for (i = 1; i < 4; i++) {
                    otherObj = mgPlayerObjTbl[m244_rankOrderTbl[i]];
                    other = (RockinRacewayRacer *)m244_WorkPtrGet(otherObj);
                    if (other->unk02 == 1) {
                        continue;
                    }
                    if (fabs(racer->unk48 - other->unk48) < 30.0) {
                        m244_photoMode = 3;
                        break;
                    }
                    if (racer->unk48 - other->unk48 < 100.0) {
                        if (fabs(leaderObj->trans.x - otherObj->trans.x) < 30.0) {
                            m244_photoMode = 3;
                        } else {
                            m244_photoMode = 1;
                        }
                        break;
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
                if (racer->unk04 != -1) {
                    HuAudFXStop(racer->unk04);
                    racer->unk04 = -1;
                }
                if (racer->unk06 != -1) {
                    HuAudFXStop(racer->unk06);
                    racer->unk06 = -1;
                }
            }
            GMesCreate(GMES_MES_14);
            HuAudSeqFadeOut(120);
            m244_phase = 3;
            m244_phaseStep = 0;
            break;
        case 3:
            if (m244_phaseTimer == 3 && m244_cheerSeNo != -1) {
                HuAudFXVolSet(m244_cheerSeNo, 110);
                HuAudFXPitchSet(m244_cheerSeNo, 200);
            }
            if (GMesStatGet() == 0) {
                m244_phase = 4;
                m244_phaseStep = 0;
            }
            break;
        case 4:
            if (m244_phaseTimer < 15) {
                break;
            }
            if (m244_winnerNo != -1) {
                racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[m244_winnerNo]);
                GwPlayer[racer->unk0A].bonusCoin += 10;
                if (m244_photoMode != 0) {
                    m244_SparkStateSave();
                    m244_SmokeStateSave();
                    m244_ReplayWinnerAdjust(m244_winnerNo);
                    m244_phase = 5;
                    m244_phaseStep = 0;
                    break;
                }
            }
            m244_phase = 6;
            m244_phaseStep = 0;
            break;
        case 5:
            m244_ghostDispF = 1;
            if (m244_phaseStep > 0 && m244_phaseStep < 29) {
                if (m244_phaseTimer >= 4.5f) {
                    if (m244_phaseStep == 10) {
                        m244_GhostStore(0, 9);
                    }
                    m244_phaseStep++;
                    m244_phaseTimer = 0;
                }
            } else if (m244_phaseStep < 33) {
                if (m244_phaseTimer >= 7.5f) {
                    m244_phaseStep++;
                    m244_phaseTimer = 0;
                }
            } else if (m244_phaseTimer >= 30.0f) {
                m244_phaseStep++;
                m244_phaseTimer = 0;
            }
            if (m244_phaseStep < 30) {
                m244_ReplayPlay(m244_phaseStep);
                if (m244_cheerSeNo != -1) {
                    t = m244_phaseStep / 30.0f;
                    HuAudFXVolSet(m244_cheerSeNo, m244_InterpCalc(t, 64.0f, 110.0f));
                    HuAudFXPitchSet(m244_cheerSeNo, (s16)m244_InterpCalc(t, 0.0f, 200.0f));
                }
                m244_CameraMoveStart(m244_cameraPresetTbl[6].center.x, m244_cameraPresetTbl[6].center.y,
                                             m244_cameraPresetTbl[6].center.z, m244_cameraPresetTbl[6].rot.x,
                                             m244_cameraPresetTbl[6].rot.y, m244_cameraPresetTbl[6].rot.z,
                                             m244_cameraPresetTbl[6].zoom, 1);
            } else if (m244_phaseStep < 34) {
                if (m244_cheerSeNo != -1) {
                    HuAudFXVolSet(m244_cheerSeNo, 110);
                    HuAudFXPitchSet(m244_cheerSeNo, 200);
                }
                m244_ReplayPlay(29);
                m244_CameraMoveStart(CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                             m244_cameraPresetTbl[6].zoom - (m244_phaseStep - 29) * 100, 1);
            } else {
                m244_CameraMoveStart(m244_cameraPresetTbl[5].center.x, m244_cameraPresetTbl[5].center.y,
                                             m244_cameraPresetTbl[5].center.z, m244_cameraPresetTbl[5].rot.x,
                                             m244_cameraPresetTbl[5].rot.y, m244_cameraPresetTbl[5].rot.z,
                                             m244_cameraPresetTbl[5].zoom, 1);
                m244_SparkStateRestore();
                m244_SmokeStateRestore();
                m244_ghostDispF = 0;
                m244_phase = 6;
                m244_phaseStep = 0;
            }
            break;
        case 6:
            switch (m244_phaseStep) {
                case 0:
                    if (!(m244_phaseTimer >= 15.0f) && m244_photoMode != 0) {
                        break;
                    }
                    if (m244_winnerNo != -1 && m244_raceTime < m244_recordTime) {
                        m244_recordTime = m244_raceTime;
                        GWMgRecordSet(3, (u16)m244_recordTime);
                        GMesCreate(GMES_MES_MG_RECORD);
                        m244_recordPulse = 15;
                        m244_resultWait = 99;
                        m244_newRecordF = 1;
                        m244_phaseStep++;
                    } else {
                        m244_phaseStep = 2;
                    }
                    times[0] = m244_raceTime;
                    times[1] = m244_recordTime;
                    m244_TimeDigitCalc(times);
                    m244_phaseTimer = 0;
                    break;
                case 1:
                    if (m244_phaseTimer >= 75.0f) {
                        m244_phaseStep++;
                        m244_phaseTimer = 0;
                    }
                    break;
                case 2:
                    if (m244_winnerNo != -1) {
                        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[m244_winnerNo]);
                        GMesCreate(GMES_MES_MG_WINNER, racer->unk0E);
                        if (m244_newRecordF == 0) {
                            HuAudSeqPlay(0x65);
                            m244_resultWait = 138;
                        } else {
                            HuAudSeqPlay(0x6A);
                        }
                        PlayerFXPlay(0x28F, racer->unk0A);
                        m244_CameraMoveStop();
                        m244_CameraFocusStart();
                    } else {
                        if (m244_newRecordF == 0) {
                            HuAudSeqPlay(0x6C);
                            m244_resultWait = 144;
                        }
                        GMesCreate(GMES_MES_MG_DRAW);
                    }
                    m244_phaseStep++;
                    m244_phaseTimer = 0;
                    break;
                case 3:
                    if (GMesStatGet() == 0) {
                        m244_phaseStep++;
                        m244_phaseTimer = 0;
                    }
                    break;
                case 4:
                    if (m244_phaseTimer >= 15) {
                        WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                        HuAudSeqFadeOut(16);
                        HuAudFXAllFadeOut(16);
                        m244_phaseTimer = 0;
                        m244_phaseStep++;
                    }
                    break;
                default:
                    if (WipeStatGet() == 0) {
                        object->func = m244_ExitObjMain;
                    }
                    break;
            }
            break;
    }
    m244_TimeUpdate();
    m244_frameCnt++;
    if (m244_prevPhase == m244_phase) {
        m244_phaseTimer++;
    } else {
        m244_phaseTimer = 0;
        m244_prevPhase = m244_phase;
    }
}

void m244_ExitObjMain(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void m244_ExitCheck(omObjData *object) {
    if (m244_exitTimer != 0) {
        if (m244_exitTimer == 1) {
            object->func = m244_ExitObjMain;
        }
        m244_exitTimer--;
        return;
    }
    if (omSysExitReq == 1 && WipeStatGet() == 0) {
        m244_exitTimer = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)m244_exitTimer);
        HuAudSeqFadeOut((s16)m244_exitTimer);
        HuAudFXAllFadeOut((s16)m244_exitTimer);
    }
}

void m244_PlayerObjCreateAll(void) {
    RockinRacewayRacer *racer;
    omObjData *object;
    RockinRacewayTrack *track;
    u16 prev;
    s32 i;
    s32 j;

    m244_racerTbl = HuMemAllocTag(4 * sizeof(RockinRacewayRacer), TAG_OVERLAY);
    m244_winnerNo = -1;
    m244_ghostDispF = 0;
    m244_ghostTbl = HuMemAllocTag(2 * sizeof(RockinRacewaySnapshotRow), TAG_OVERLAY);
    memset(m244_ghostTbl, 0, 2 * sizeof(RockinRacewaySnapshotRow));
    for (i = 0, racer = m244_racerTbl; i < 4; i++, racer++) {
        memset(racer, 0, sizeof(RockinRacewayRacer));
        racer->unk00 = i;
        racer->unk0A = m244_racerPlayerTbl[i][1];
        racer->unk0C = GwPlayer[racer->unk0A].pad;
        racer->unk0E = GwPlayer[racer->unk0A].chr;
        if (GwPlayer[racer->unk0A].stat & PLAYER_IS_CPU) {
            racer->unk10 = 1;
        } else {
            racer->unk10 = 0;
        }
        racer->unk12 = GwPlayer[racer->unk0A].cpu_difficulty;
        racer->unk2E = GwPlayer[racer->unk0A].group;
        for (j = 0; j < 4; j++) {
            if (m244_trackRacerTbl[racer->unk2E] == -1) {
                m244_trackRacerTbl[racer->unk2E] = racer->unk2E;
                break;
            }
            prev = racer->unk2E;
            racer->unk2E = prev + 1;
            if (racer->unk2E >= 4) {
                racer->unk2E = prev - 3;
            }
        }
        track = &m244_trackTbl[racer->unk2E];
        racer->unk30 = track->unk08 - m244_trackLenMin;
        if (racer->unk30 < 0.0f) {
            racer->unk30 = 0.0f;
        }
        m244_GaugeCreate(racer->unk2E, racer->unk0E);
        object = omAddObj(i + 16, 10, 60, -1, m244_PlayerObjInit);
        mgPlayerObjTbl[mgPlayerObjNum] = object;
        m244_WorkPtrSet(object, (u32)&m244_racerTbl[i]);
        mgPlayerObjNum++;
    }
}

void m244_PlayerObjInit(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)m244_WorkPtrGet(object);
    u16 character;
    s32 model;
    s32 level;
    s32 i;

    object->func = m244_PlayerObjMain;
    character = racer->unk0E;
    object->model[0] = Hu3DModelRead(0x4D0000 | m244_carMdlTbl[character], 0x299);
    object->model[1] = Hu3DModelRead(9, 0x299);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            object->model[3] = Hu3DModelRead(0x4D0000 | m244_carMdlTbl[character], 0x28D);
            Hu3DModelTPLvlInit(object->model[3]);
            Hu3DModelTPLvlSet(object->model[3], 64);
            Hu3DModelDynamicFree(object->model[3]);
        } else {
            object->model[3 + i] = Hu3DModelLink(object->model[3]);
        }
        Hu3DModelLayerSet(object->model[3 + i], m244_ghostLayerTbl[i % 3]);
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
    racer->unk44 = m244_TrackPosCalc(racer->unk2E, racer->unk30, racer->unk44, 0.0f, &racer->unk4C,
                                                &racer->unk50, &racer->pos, &racer->rot);
    object->model[2] = model = Hu3DModelRead(0x4D0009, 0x99);
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

void m244_PlayerObjMain(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)m244_WorkPtrGet(object);
    HmfModel *src;
    HmfModel *dst;
    s32 i;

    if (m244_ghostDispF != 0) {
        for (i = 0; i < 2; i++) {
            if (m244_ghostTbl[i].racers[racer->unk0A].active != 0) {
                Hu3DModelAttrSet(object->model[3 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            } else {
                Hu3DModelAttrSet(object->model[3 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            Hu3DModelAttrSet(object->model[3 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
    switch (m244_phase) {
        case 2:
            Hu3DMotionSpeedSet(object->model[2], 1.0f);
            if (racer->unk10) {
                m244_PlayerComInput(object);
            }
            if (m244_raceStartF == 0) {
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
                    m244_RacerAccelUpdate(racer);
                    if (m244_raceStartF == 0) {
                        racer->unk38 = 0.0f;
                        racer->unk24 = 0.0f;
                        racer->unk28 = 1.0f;
                    }
                    m244_RacerGaugeUpdate(racer);
                    break;
                case 1:
                    m244_RacerSpinUpdate(racer);
                    break;
            }
            m244_RacerFocusAdd(racer, 0.03f);
            m244_RacerMove(object);
            break;
        case 3:
        case 4:
        case 6:
            switch (racer->unk02) {
                case 0:
                case 2:
                    racer->unk38 = m244_InterpCalc(0.1f, racer->unk38, 0.65f);
                    m244_RacerGaugeUpdate(racer);
                    racer->unk24 += 20.0f;
                    if (racer->unk24 >= 360.0f) {
                        racer->unk24 -= 360.0f;
                    }
                    break;
                case 1:
                    if (racer->unk00 == m244_winnerNo) {
                        racer->unk02 = 0;
                        racer->unk28 = 1.0f;
                        racer->unk24 = 0.0f;
                        racer->unk40 = 0.0f;
                    } else {
                        m244_RacerSpinUpdate(racer);
                    }
                    break;
            }
            if (m244_phase == 6 && racer->unk00 == m244_winnerNo) {
                m244_RacerFocusAdd(racer, 0.1f);
            }
            m244_RacerMove(object);
            break;
        case 5:
            break;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6f, 0.6f, 0.6f);
    racer->unk34++;
}

// CPU input: mashes the buttons the racer needs next.
void m244_PlayerComInput(omObjData *object) {
    RockinRacewayRacer *racer;
    s32 press;
    s32 level;

    press = FALSE;
    racer = (RockinRacewayRacer *)m244_WorkPtrGet(object);
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
    switch (m244_TrackNodeTypeGet(racer->unk2E, racer->unk4C)) {
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
                HuPadBtnDown[racer->unk0C] = 0;
                return;
            }
        } else {
            if (m244_phaseTimer > 60) {
                racer->unk16 += (rand8() & 3) + 2;
            }
            if (racer->unk16 >= racer->unk14) {
                racer->unk16 = -(rand16() % 30 + 30);
            }
        }
        if (racer->unk38 < m244_comSpeedTbl[level][0]) {
            racer->unk1A = 1;
        } else if (racer->unk02 == 2) {
            racer->unk1A = 1;
        } else if (racer->unk38 < m244_comSpeedTbl[level][1] && (rand8() & 0x3F) == 0) {
            racer->unk1A = 1;
        }
    }
    if (racer->unk1A != 0) {
        racer->unk18++;
        if (racer->unk18 > m244_comMashWaitTbl[level]) {
            racer->unk18 = 0;
            racer->unk1A = 0;
            press = TRUE;
        }
    }
    if (press) {
        if (racer->unk1E == 0x8000) {
            HuPadBtnDown[racer->unk0C] = A_BUTTON;
        } else {
            HuPadBtnDown[racer->unk0C] = (B_BUTTON | Z_TRIG);
        }
    }
}

void m244_RacerAccelUpdate(RockinRacewayRacer *racer) {
    if (HuPadBtnDown[racer->unk0C] & racer->unk1E) {
        racer->unk38 += m244_rankAccelTbl[racer->unk1C] * 0.1f;
        if (racer->unk38 >= 1.0f) {
            racer->unk38 = 1.0f;
        }
        if (HuPadBtnDown[racer->unk0C] == A_BUTTON) {
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

void m244_RacerGaugeUpdate(RockinRacewayRacer *racer) {
    if (racer->unk28 <= 0.0f && m244_phase == 2) {
        racer->unk02 = 1;
        HuAudPlayerFXPlay(0x458, racer->unk0A);
        HuAudPlayerFXPlay(0x459, racer->unk0A);
        m244_SeQueueAdd(0x286, 3, 3, racer->unk0A);
        if (m244_phase == 2) {
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
            m244_SparkCreate(racer->pos.x + 0.1f * 200.0, racer->pos.y + 0.7f * 200.0, racer->pos.z);
        }
        racer->unk28 = 1.0f;
        if (--racer->unk20 == 0) {
            if (m244_phase == 2) {
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

void m244_RacerSpinUpdate(RockinRacewayRacer *racer) {
    racer->unk38 = 0.0f;
    if (racer->unk28 >= 0.975f) {
        racer->unk40 = m244_AngleStepCalc(racer->unk38, racer->unk40, 30.0f);
        if (m244_AngleDiffCalc(0.0f, racer->unk40) < 0.5f) {
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
            m244_RacerSmokeCreate(racer);
        }
        racer->unk28 += 0.025f;
    }
}

void m244_RacerMove(omObjData *object) {
    RockinRacewayRacer *racer = (RockinRacewayRacer *)m244_WorkPtrGet(object);
    HuMtx4F mtx;
    f32 speed;

    speed = racer->unk38 * m244_rankSpeedTbl[racer->unk1C] * 3.0f;
    racer->unk3C = sindf(racer->unk24) * racer->unk38 * 30.0f;
    racer->unk44 = m244_TrackPosCalc(racer->unk2E, racer->unk30, racer->unk44, speed, &racer->unk4C,
                                                &racer->unk50, &racer->pos, &racer->rot);
    if (racer->unk3C > 0.0f) {
        HuMtxIdentF(mtx);
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
void m244_GhostStore(s32 row, s16 arg1) {
    RockinRacewayRacer *racer;
    omObjData *object;
    s32 i;

    for (i = 0; i < 4; i++) {
        object = mgPlayerObjTbl[i];
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(object);
        if (m244_ghostTbl[row].racers[racer->unk0A].active != 0) {
            continue;
        }
        m244_ghostTbl[row].racers[racer->unk0A].active = 1;
        m244_ghostTbl[row].racers[racer->unk0A].unk00 = arg1;
        m244_ghostTbl[row].racers[racer->unk0A].trans.x = object->trans.x;
        m244_ghostTbl[row].racers[racer->unk0A].trans.y = object->trans.y;
        m244_ghostTbl[row].racers[racer->unk0A].trans.z = object->trans.z;
        m244_ghostTbl[row].racers[racer->unk0A].rot.x = object->rot.x;
        m244_ghostTbl[row].racers[racer->unk0A].rot.y = object->rot.y;
        m244_ghostTbl[row].racers[racer->unk0A].rot.z = object->rot.z;
        m244_ghostTbl[row].racers[racer->unk0A].scale.x = object->scale.x;
        m244_ghostTbl[row].racers[racer->unk0A].scale.y = object->scale.y;
        m244_ghostTbl[row].racers[racer->unk0A].scale.z = object->scale.z;
    }
}

// Ranks the racers by track progress, writing each racer's rank to unk1C and the racer slots in rank
// order to order. Ties are broken randomly.
void m244_RankCalc(s32 *order) {
    RockinRacewayStanding standings[4];
    RockinRacewayStanding temp;
    RockinRacewayRacer *racer;
    s32 swap;
    s32 k;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
        standings[i].index = i;
        standings[i].node = racer->unk4C;
        standings[i].track = racer->unk2E;
        standings[i].x = mgPlayerObjTbl[i]->trans.x + racer->unk54;
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
            if (standings[i].node >= m244_goalNodeTbl[standings[i].track] - 1 &&
                standings[j].node >= m244_goalNodeTbl[standings[j].track] - 1 &&
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
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
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
        order[i] = ((RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[standings[i].index]))->unk0A;
    }
}

s32 m244_WinnerGet(void) {
    RockinRacewayRacer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
        if (racer->unk4C >= m244_goalNodeTbl[racer->unk2E] - 1 &&
            mgPlayerObjTbl[i]->trans.x + racer->unk54 >= 1.7f * 200.0) {
            break;
        }
    }
    if (i < 4) {
        for (i = 0; i < 4; i++) {
            racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
            if (racer->unk1C == 0) {
                return i;
            }
        }
    }
    return -1;
}

void m244_PanelCreateAll(void) {
    RockinRacewayFx *entry;
    RockinRacewayRacer *racer;
    Vec rot;
    Vec pos;
    s32 i;

    m244_panelTbl = entry = HuMemAllocTag(8 * sizeof(RockinRacewayFx), TAG_OVERLAY);
    for (i = 0; i < 8; i++, entry++) {
        memset(entry, 0, sizeof(RockinRacewayFx));
        if (i == 0) {
            entry->modelA = Hu3DModelRead(0x4D0007, 0x99);
            entry->modelB = Hu3DModelRead(0x4D0008, 0x99);
        } else {
            entry->modelA = Hu3DModelLink(m244_panelTbl->modelA);
            entry->modelB = Hu3DModelLink(m244_panelTbl->modelB);
        }
        Hu3DModelAttrSet(entry->modelA, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(entry->modelB, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        entry->flag = 0;
        entry->timer = 0;
        entry->active = 0;
        entry->posX = entry->posY = entry->posZ = 0.0f;
        entry->velX = entry->velY = entry->velZ = 0.0f;
    }
    for (i = 0, racer = m244_racerTbl; i < 4; i++, racer++) {
        m244_TrackPosCalc(racer->unk2E, racer->unk30, 1500.0f, 0.0f, NULL, NULL, &pos, &rot);
        m244_PanelCreate(&pos, 0, 90);
        m244_PanelCreate((Vec *)m244_trackTbl[i].unk0C[m244_panelNodeTbl[i][1]], 0,
                                     30);
    }
    omSetStatBit(omAddObj(30, 0, 0, -1, m244_PanelObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

// Claims a free blink-marker entry, initializes it with the duration and base position, positions
// both models there, and returns the entry index, or -1 if the pool is full.
s32 m244_PanelCreate(Vec *arg0, s32 arg1, u16 arg2) {
    RockinRacewayFx *entry;
    s32 i;

    for (i = 0, entry = m244_panelTbl; i < 8 && entry->active != 0; i++, entry++) {
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

void m244_PanelObjMain(omObjData *object) {
    RockinRacewayFx *entry;
    u16 shown;
    u16 hidden;
    s32 i;

    if (omPauseChk() + omAllPauseF == 0 && m244_phase == 2) {
        m244_PanelHitUpdate();
    }
    for (i = 0, entry = m244_panelTbl; i < 8; i++, entry++) {
        if (entry->active == 0) {
            continue;
        }
        if (omPauseChk() + omAllPauseF == 0 && m244_phase == 2) {
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
        Hu3DModelAttrSet(shown, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(hidden, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        entry->posX += entry->velX;
        entry->posY += entry->velY;
        entry->posZ += entry->velZ;
        Hu3DModelPosSet(shown, entry->posX, entry->posY, entry->posZ);
        Hu3DModelPosSet(hidden, entry->posX, entry->posY, entry->posZ);
        Hu3DModelScaleSet(shown, 1.0f, 1.0f, 1.0f);
        Hu3DModelScaleSet(hidden, 1.0f, 1.0f, 1.0f);
        if (m244_phase >= 3) {
            entry->active = 0;
            Hu3DModelAttrSet(shown, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(hidden, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

// Collects the first active blink marker within range of pos, returning its flag, or -1 if none.
s32 m244_PanelHitCheck(Vec *pos) {
    RockinRacewayFx *entry;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 i;

    for (i = 0, entry = m244_panelTbl; i < 8; i++, entry++) {
        if (entry->active == 0) {
            continue;
        }
        dx = entry->posX - pos->x;
        dy = entry->posY - pos->y;
        dz = entry->posZ - pos->z;
        if (dx * dx + dy * dy + dz * dz < (0.3f * 200.0) * (0.3f * 200.0)) {
            Hu3DModelAttrSet(entry->modelA, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(entry->modelB, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            entry->active = 0;
            if (m244_cheerSeNo == -1 && m244_cheerSeDelay == -1 && entry->duration == 30) {
                m244_cheerSeDelay = 4;
            }
            break;
        }
    }
    if (i < 8) {
        return entry->flag;
    }
    return -1;
}

void m244_PanelHitUpdate(void) {
    RockinRacewayRacer *racer;
    s32 i;

    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
        switch (m244_PanelHitCheck(&racer->pos)) {
            case 0:
                racer->unk02 = 2;
                racer->unk28 = 1.0f;
                racer->unk20 = 300;
                racer->unk34 |= 0xE;
                if (m244_phase == 2) {
                    omVibrate(racer->unk0A, 10, 0, 10);
                }
                if (m244_phase == 2) {
                    if (racer->unk04 != -1) {
                        HuAudFXStop(racer->unk04);
                        racer->unk04 = -1;
                    }
                    if (racer->unk06 != -1) {
                        HuAudFXStop(racer->unk06);
                        racer->unk06 = -1;
                    }
                }
                racer->unk04 = HuAudPlayerFXPlay(0x46D, racer->unk0A);
                racer->unk06 = HuAudPlayerFXPlay(0x46E, racer->unk0A);
                break;
            case 1:
                racer->unk02 = 1;
                racer->unk28 = 0.0f;
                if (m244_phase == 2) {
                    if (racer->unk04 != -1) {
                        HuAudFXStop(racer->unk04);
                        racer->unk04 = -1;
                    }
                    if (racer->unk06 != -1) {
                        HuAudFXStop(racer->unk06);
                        racer->unk06 = -1;
                    }
                }
                HuAudPlayerFXPlay(0x458, racer->unk0A);
                HuAudPlayerFXPlay(0x459, racer->unk0A);
                m244_SeQueueAdd(0x286, 3, 3, racer->unk0A);
                if (m244_phase == 2) {
                    omVibrate(racer->unk0A, 2, 2, 20);
                }
                break;
        }
    }
}

void m244_SparkInit(void) {
    omObjData *object;
    HmfModel *model;
    s32 i;

    m244_sparkObj = object = omAddObj(29, 13, 0, -1, m244_SparkObjMain);
    object->model[0] = -1;
    for (i = 1; i < 13; i++) {
        object->model[i] = Hu3DModelRead(0x1001F, 0x899);
        Hu3DModelObjAttrSet(object->model[i], 0x600, 0x400);
        Hu3DModelScaleSet(object->model[i], 1.0f, 1.0f, 1.0f);
        model = &Hu3DData[object->model[i]];
        model->motTime = 0.0f;
        model->motSpeed = 1.0f;
        Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    m244_sparkStateTbl = HuMemAllocTag(12 * sizeof(RockinRacewayModelState), TAG_OVERLAY);
    memset(m244_sparkStateTbl, 0, 12 * sizeof(RockinRacewayModelState));
    m244_sparkPauseF = 0;
}

// Hides each spark model once its motion has finished playing.
void m244_SparkObjMain(omObjData *object) {
    HmfModel *model;
    s32 i;

    if (m244_sparkPauseF != 0) {
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
        if (Hu3DMotion[model->motId].unk02 <= model->motTime) {
            model->attr |= 4;
            model->motTime = 0.0f;
        }
    }
}

// Shows the first hidden spark model at the given position, facing the camera.
void m244_SparkCreate(f32 x, f32 y, f32 z) {
    omObjData *object = m244_sparkObj;
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
void m244_SparkStateSave(void) {
    omObjData *object = m244_sparkObj;
    RockinRacewayModelState *state = m244_sparkStateTbl;
    HmfModel *model;
    s32 i;

    if (m244_sparkPauseF != 0) {
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
    m244_sparkPauseF = 1;
}

// Restores the state of each spark model saved by m244_SparkStateSave.
void m244_SparkStateRestore(void) {
    omObjData *object = m244_sparkObj;
    RockinRacewayModelState *state = m244_sparkStateTbl;
    HmfModel *model;
    s32 i;

    if (m244_sparkPauseF == 0) {
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
    m244_sparkPauseF = 0;
}

void m244_SmokeInit(void) {
    HuSprAnimData *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    m244_sprTbl[2] = m244_SprAnimRead(11);
    sprite = HuSprAnimDataGet(m244_sprTbl[2]);
    m244_smokeObj = omAddObj(28, 0, 0, -1, m244_SmokeObjMain);
    m244_smokeTbl = effect = HuMemAllocTag(sizeof(RockinRacewayEffect) * 16, TAG_OVERLAY);
    for (i = 0; i < 16; i++, effect++) {
        if (i == 0) {
            effect->model = m244_BillboardColorMdlCreate(sprite, m244_smokeColor);
        } else {
            effect->model =
                m244_BillboardColorMdlLink(sprite, m244_smokeTbl[0].model, m244_smokeColor);
        }
        effect->active = 0;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
    m244_smokeStateTbl = HuMemAllocTag(16 * sizeof(RockinRacewayEffectState), TAG_OVERLAY);
    memset(m244_smokeStateTbl, 0, 16 * sizeof(RockinRacewayEffectState));
    m244_smokePauseF = 0;
}

void m244_SmokeObjMain(omObjData *object) {
    HuSprAnimData *sprite;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (m244_smokePauseF != 0) {
        return;
    }
    sprite = HuSprAnimDataGet(m244_sprTbl[2]);
    for (i = 0, effect = m244_smokeTbl; i < 16; i++, effect++) {
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
        m244_BillboardColorPatSet(effect->model, sprite, (s32)effect->frame, m244_smokeColor);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 m244_SmokeCreate(Vec *pos, Vec *vel, Vec *scale, f32 speed) {
    HuSprAnimData *sprite = HuSprAnimDataGet(m244_sprTbl[2]);
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = m244_smokeTbl; i < 16; i++, effect++) {
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
        m244_BillboardColorPatSet(effect->model, sprite, 0, m244_smokeColor);
        Hu3DModelAttrSet(effect->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
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
void m244_RacerSmokeCreate(RockinRacewayRacer *racer) {
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
    m244_SmokeCreate(&pos, &vel, &scale, 1.0f);
}

// Saves the state of each sprite effect and hides it.
void m244_SmokeStateSave(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (m244_smokePauseF != 0) {
        return;
    }
    for (state = m244_smokeStateTbl, effect = m244_smokeTbl, i = 0; i < 16;
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
    m244_smokePauseF = 1;
}

// Restores the state of each sprite effect saved by m244_SmokeStateSave.
void m244_SmokeStateRestore(void) {
    RockinRacewayEffectState *state;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    if (m244_smokePauseF == 0) {
        return;
    }
    for (state = m244_smokeStateTbl, effect = m244_smokeTbl, i = 0; i < 16;
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
    m244_smokePauseF = 0;
}

// Appends a new object to the shared minigame object list.
void m244_StageObjCreate(void) {
    omObjData *obj = omAddObj(1, 0x18, 0, -1, m244_StageObjInit);
    u16 index = mgMapObjNum;

    mgMapObjNum = index + 1;
    mgMapObjTbl[index] = obj;
}

void m244_StageObjInit(omObjData *object) {
    s16 group;
    s32 i;

    object->func = m244_StageObjMain;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->model[0] = Hu3DModelRead2(0x4D0000, 0x99);
    object->model[1] = Hu3DModelRead2(0x4D000A, 0xB9);
    object->model[2] = Hu3DModelRead2(0x4D000B, 0xB9);
    m244_sprTbl[3] = m244_SprAnimRead(0x4D0010);
    m244_sprTbl[4] = m244_SprAnimRead(0x4D0011);
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            object->model[3] =
                m244_QuadMdlCreate(HuSprAnimDataGet(m244_sprTbl[3]), &m244_boardFaceQuad);
        } else {
            object->model[3 + i] = m244_BillboardColorMdlLink(HuSprAnimDataGet(m244_sprTbl[3]),
                                                                object->model[3], m244_boardColor);
        }
    }
    for (i = 0; i < 12; i++) {
        if (i == 0) {
            object->model[7] =
                m244_QuadMdlCreate(HuSprAnimDataGet(m244_sprTbl[4]), &m244_boardDigitQuad);
        } else {
            object->model[7 + i] = m244_BillboardColorMdlLink(HuSprAnimDataGet(m244_sprTbl[4]),
                                                                object->model[7], m244_boardColor);
        }
    }
    m244_BoardFaceUpdate(&object->model[3], HuSprAnimDataGet(m244_sprTbl[3]),
                                 m244_boardDisp.players);
    m244_boardDisp.times[1] = m244_recordTime;
    m244_TimeDigitCalc(m244_boardDisp.times);
    m244_BoardDigitUpdate(&object->model[7], HuSprAnimDataGet(m244_sprTbl[4]),
                                 m244_boardDisp.times);
    m244_sprTbl[0] = m244_SprAnimRead(0x4D000E);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, m244_sprTbl[0], 0);
    HuSprAttrSet(group, 0, HUSPR_ATTR_BG);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    HuSprPosSet(group, 0, 160, 120);
    HuSprPriSet(group, 0, 0xFFFF);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void m244_StageObjMain(omObjData *object) {
}

void m244_BoardFaceSet(s32 *players) {
    omObjData *object = mgMapObjTbl[0];

    m244_BoardFaceUpdate(&object->model[3], HuSprAnimDataGet(m244_sprTbl[3]), players);
}

void m244_BoardTimeSet(s32 *values) {
    omObjData *object = mgMapObjTbl[0];

    m244_BoardDigitUpdate(&object->model[7], HuSprAnimDataGet(m244_sprTbl[4]), values);
}

void m244_TrackInit(void) {
    RockinRacewayTrack *track;
    Vec dir;
    f32 dx, dy, dz;
    f32 distance;
    s32 next;
    s32 i;
    s32 j;

    m244_trackTbl = HuMemAllocTag(4 * sizeof(RockinRacewayTrack), TAG_OVERLAY);
    for (i = 0, track = m244_trackTbl; i < 4; i++, track++) {
        track->unk00 = i;
        track->unk04 = track->unk08 = 0.0f;
        track->unk0C = m244_trackNodeTbl[i];
        track->numNodes = m244_trackNodeNumTbl[i][1];
        track->unk0C[m244_goalNodeTbl[i]][0] = 340.0f;
        track->unk10 = HuMemAllocTag(track->numNodes * sizeof(*track->unk10), TAG_OVERLAY);
        track->unk14 = HuMemAllocTag(track->numNodes * sizeof(f32), TAG_OVERLAY);
        track->unk18 = HuMemAllocTag((track->numNodes + 1) * sizeof(f32), TAG_OVERLAY);
        track->unk1C = HuMemAllocTag(track->numNodes * sizeof(*track->unk1C), TAG_OVERLAY);
        track->unk20 = HuMemAllocTag(track->numNodes * sizeof(u16), TAG_OVERLAY);
        memset(track->unk20, 0, 4);
        for (j = 0; j < 5; j++) {
            next = rand8() % m244_goalNodeTbl[i];
            track->unk20[next] = 1;
        }
        for (j = 0; j < 3; j++) {
            next = rand8() % m244_goalNodeTbl[i];
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
            if (j < m244_goalNodeTbl[i]) {
                track->unk08 = distance;
            }
            track->unk10[j][0] = track->unk0C[j][0] + dx * 0.5f;
            track->unk10[j][1] = track->unk0C[j][1] + dy * 0.5f;
            track->unk10[j][2] = track->unk0C[j][2] + dz * 0.5f;
            m244_BezierTangentVecCalc(0.0f, track->unk0C[j], track->unk10[j], track->unk0C[next], &dir.x);
            m244_DirRotCalc(&dir, track->unk1C[j]);
        }
        track->unk18[j] = distance;
        track->unk04 = distance - track->unk14[j - 1];
    }
    m244_trackLenMin = m244_trackTbl[0].unk08;
    for (i = 1, track = &m244_trackTbl[1]; i < 4; i++, track++) {
        if (m244_trackLenMin > track->unk08) {
            m244_trackLenMin = track->unk08;
        }
    }
}

// Advances distance along the track by speed, and evaluates the position and rotation at the
// resulting point (offset by arg1).
f32 m244_TrackPosCalc(u16 trackIndex, f32 arg1, f32 distance, f32 speed, u16 *node, f32 *fraction, Vec *pos,
                                 Vec *rot) {
    s32 i;
    s32 cur;
    s32 next;
    RockinRacewayTrack *track = &m244_trackTbl[trackIndex];
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
    // cur is assigned in both branches (merged by cross-jumping) to match register allocation.
    if (i < track->numNodes - 1) {
        next = i + 1;
        cur = i;
    } else {
        next = 0;
        cur = i;
    }
    m244_BezierVecCalc(t, track->unk0C[cur], track->unk10[cur], track->unk0C[next], &pos->x);
    rot->x = m244_AngleInterpCalc(t, track->unk1C[cur][0], track->unk1C[next][0]);
    rot->y = m244_AngleInterpCalc(t, track->unk1C[cur][1], track->unk1C[next][1]);
    return newDistance;
}

s32 m244_TrackNodeTypeGet(u16 arg0, u16 arg1) {
    RockinRacewayTrack *track = &m244_trackTbl[arg0];
    return track->unk20[arg1];
}

u16 m244_SprAnimRead(s32 dirAndFile) {
    void *data = DataRead(dirAndFile);
    s16 anim = HuSprAnimRead(data);

    DataClose(data);
    return anim;
}

void m244_ReplaySprInit(void) {
    s32 group;

    m244_sprTbl[1] = m244_SprAnimRead(0x4D000F);
    m244_sprTbl[5] = m244_SprAnimRead(0x4D0012);
    m244_sprTbl[8] = m244_SprAnimRead(0x4D0013);
    group = HuSprGrpCreate(1, 0);
    m244_replayGrp = group;
    HuSprPosSet(group, 0, 160, 60);
    HuSprGrpMemberSet(group, 0, m244_sprTbl[5], 0);
    HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
    HuSprPatNoSet(group, 0, 0);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF | 0x1000);
}

// Creates the lap meter sprites for a track, mirrored for odd tracks.
void m244_GaugeCreate(s16 track, s16 character) {
    s32 anim;
    s32 x;
    s32 y;
    s32 group;
    s32 i;

    anim = m244_SprAnimRead(m244_gaugeFaceSprTbl[character]);
    x = m244_gaugePosTbl[track].x;
    y = m244_gaugePosTbl[track].y;
    m244_gaugeGrpTbl[track] = group = HuSprGrpCreate(7, 0);
    m244_gaugeTbl[track].track = track;
    m244_gaugeTbl[track].y = y;
    m244_gaugeTbl[track].unk04 = 0;
    m244_gaugeTbl[track].unk02 = 0;
    if (track & 1) {
        m244_gaugeTbl[track].x = x - 4;
    } else {
        m244_gaugeTbl[track].x = x + 46;
    }
    for (i = 0; i < 5; i++) {
        if (track & 1) {
            m244_gaugeTbl[track].offsets[i] = x + (i * 8 - 20) - m244_gaugeTbl[track].x;
        } else {
            m244_gaugeTbl[track].offsets[i] = x + (i * 8 + 30) - m244_gaugeTbl[track].x;
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
            HuSprGrpMemberSet(group, i, m244_sprTbl[8], 0);
            HuSprColorTPLvlSet(group, i, 0, 0, 0, 160);
        } else {
            if (track & 1) {
                HuSprPosSet(group, i, x - 20, y);
            } else {
                HuSprPosSet(group, i, x + 30, y);
            }
            HuSprGrpMemberSet(group, i, m244_sprTbl[1], 0);
            x += 8;
        }
        HuSprAnimModeSet(group, i, HUSPR_ANIM_MODE_STOP);
        HuSprPatNoSet(group, i, 0);
        HuSprAttrSet(group, i, HUSPR_ATTR_XLU);
        if (i != 6) {
            HuSprPriSet(group, i, -16 - i);
        } else {
            HuSprPriSet(group, i, 0xFFFF);
        }
    }
    omSetStatBit(omAddObj(20, 0, 0, -1, m244_GaugeObjMain), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m244_GaugeObjMain(omObjData *object) {
    RockinRacewayRacer *racer;
    s32 i;

    if (m244_phase == 5 && (m244_phaseStep > 0 || m244_phaseTimer >= 2)) {
        HuSprAttrReset(m244_replayGrp, 0, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(m244_replayGrp, 0, HUSPR_ATTR_DISPOFF);
    }
    if (m244_phase < 3) {
        racer = m244_racerTbl;
        for (i = 0; i < 4; i++, racer++) {
            m244_GaugeUpdate(racer->unk2E, racer->unk28 * 100.0f, racer->unk02);
        }
    } else {
        for (i = 0; i < 4; i++) {
            m244_GaugeUpdate(i, 0, 0xFFFF);
        }
    }
}

// Updates the lap meter sprites for a track, scaling the meter up while state is 2.
void m244_GaugeUpdate(s16 track, s16 progress, u16 state) {
    s16 group;
    f32 scale;
    f32 x;
    s16 remainder;
    s32 i;

    group = m244_gaugeGrpTbl[track];
    if (state == 2) {
        if (m244_gaugeTbl[track].unk02++ > 30.0f) {
            m244_gaugeTbl[track].unk02 = 30;
        }
        scale = m244_gaugeTbl[track].unk02;
        scale = m244_BezierCalc(scale / 30.0f, 0.0f, 1.0f, 0.4f) + 1.0;
    } else {
        if (m244_gaugeTbl[track].unk02-- < 0) {
            m244_gaugeTbl[track].unk02 = 0;
        }
        scale = m244_gaugeTbl[track].unk02;
        scale /= 30.0f;
        scale = scale * 0.4f + 1.0;
    }
    if (m244_gaugeTbl[track].unk02 != m244_gaugeTbl[track].unk04) {
        for (i = 0; i < 5; i++) {
            x = (s16)m244_gaugeTbl[track].x + m244_gaugeTbl[track].offsets[i] * scale;
            HuSprScaleSet(group, i + 1, scale, scale);
            HuSprPosSet(group, i + 1, x, m244_gaugeTbl[track].y);
            if (state == 2) {
                HuSprAttrSet(group, i + 1, HUSPR_ATTR_AA | HUSPR_ATTR_DITHER_MAGICSQ | HUSPR_ATTR_FILTER_BILERP);
            } else {
                HuSprAttrReset(group, i + 1, HUSPR_ATTR_AA | HUSPR_ATTR_DITHER_MAGICSQ | HUSPR_ATTR_FILTER_BILERP);
            }
        }
        m244_gaugeTbl[track].unk04 = m244_gaugeTbl[track].unk02;
    }
    switch (state) {
        case 1:
            if ((m244_phaseTimer & 1) && omPauseChk() + omAllPauseF == 0) {
                HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
            }
            break;
        case 2:
            HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
            if (!(m244_phaseTimer & 3)) {
                for (i = 0; i < 5; i++) {
                    HuSprAttrReset(group, i + 1, HUSPR_ATTR_DISPOFF);
                    HuSprPatNoSet(group, i + 1, 1);
                    HuSprTPLvlSet(group, i + 1, 0x100);
                }
            } else {
                for (i = 0; i < 5; i++) {
                    HuSprAttrReset(group, i + 1, HUSPR_ATTR_DISPOFF);
                    HuSprPatNoSet(group, i + 1, 0);
                    HuSprTPLvlSet(group, i + 1, 0x100);
                }
            }
            return;
        case 0xFFFF:
            for (i = 0; i < 7; i++) {
                HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
            }
            return;
        default:
            HuSprAttrReset(group, 0, HUSPR_ATTR_DISPOFF);
            break;
    }
    for (i = 0; i < 5; i++) {
        if (i * 20 < progress) {
            HuSprAttrReset(group, i + 1, HUSPR_ATTR_DISPOFF);
            if ((i + 1) * 20 <= progress) {
                HuSprTPLvlSet(group, i + 1, 0x100);
                HuSprPatNoSet(group, i + 1, 0);
            } else {
                remainder = progress % 20;
                HuSprTPLvlSet(group, i + 1, remainder * 0.05f * 256.0f);
                HuSprPatNoSet(group, i + 1, 0);
            }
        } else {
            HuSprAttrSet(group, i + 1, HUSPR_ATTR_DISPOFF);
        }
    }
}

void m244_TimeInit(void) {
    s32 group;
    s32 i;
    s32 j;

    m244_sprTbl[6] = m244_SprAnimRead(0x31);
    m244_sprTbl[7] = m244_SprAnimRead(0x32);
    m244_recordPulse = 0;
    for (i = 0; i < 2; i++) {
        m244_timeGrpTbl[i] = group = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            HuSprPosSet(group, j, m244_timeDigitXTbl[j], i * 12 + 28);
            HuSprGrpMemberSet(group, j, m244_sprTbl[6 + i], 0);
            HuSprPatNoSet(group, j, 0);
            HuSprAttrSet(group, j, HUSPR_ATTR_XLU);
            HuSprAnimModeSet(group, j, HUSPR_ANIM_MODE_STOP);
        }
        HuSprPatNoSet(group, 2, 10);
        HuSprPatNoSet(group, 5, 11);
    }
}

// Updates the current and record time digits, pulsing the record time when it is beaten.
void m244_TimeUpdate(void) {
    s32 *digits;
    f32 scale = 1.0f;
    u16 group;
    s32 i;
    s32 j;

    if (m244_phase == 5) {
        for (i = 0; i < 2; i++) {
            group = m244_timeGrpTbl[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrSet(group, j, HUSPR_ATTR_DISPOFF);
            }
        }
    } else {
        digits = m244_timeDigitTbl[0];
        for (i = 0; i < 2; i++) {
            group = m244_timeGrpTbl[i];
            for (j = 0; j < 8; j++) {
                HuSprAttrReset(group, j, HUSPR_ATTR_DISPOFF);
            }
        }
        if (m244_recordPulse != 0) {
            scale = sindf(m244_recordPulse / 15.0f * 180.0f) + 1.0f;
            if (--m244_recordPulse == 1) {
                scale = 1.0f;
            }
        }
        for (i = 0; i < 2; i++) {
            group = m244_timeGrpTbl[i];
            for (j = 0; j < 6; j++) {
                if (digits[i * 6 + j] >= 10) {
                    digits[i * 6 + j] = 9;
                } else if (digits[i * 6 + j] < 0) {
                    digits[i * 6 + j] = 0;
                }
                HuSprPatNoSet(group, m244_timeDigitMemberTbl[j], (s16)digits[i * 6 + j]);
            }
            if (m244_recordPulse != 0 && i == 1) {
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(group, j, (m244_timeDigitXTbl[j] - 156) * scale + 156.0f, i * 12 + 28);
                    HuSprScaleSet(group, j, scale, scale);
                }
            }
        }
    }
}

// Converts the two frame counts into minute, second and hundredth digits in m244_timeDigitTbl.
void m244_TimeDigitCalc(s32 *frames) {
    s32 time[3];
    s32(*digits)[6] = m244_timeDigitTbl;
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

void m244_CameraInit(void) {
    HuCamera *camera;
    s32 i;

    Center.x = m244_cameraPresetTbl[0].center.x;
    Center.y = m244_cameraPresetTbl[0].center.y;
    Center.z = m244_cameraPresetTbl[0].center.z;
    CRot.x = m244_cameraPresetTbl[0].rot.x;
    CRot.y = m244_cameraPresetTbl[0].rot.y;
    CRot.z = m244_cameraPresetTbl[0].rot.z;
    CZoom = m244_cameraPresetTbl[0].zoom;
    m244_CameraKeyStore(0);
    m244_CameraKeyStore(1);
    m244_cameraMoveMode = 0;
    m244_cameraMoveF = 0;
    m244_cameraMoveTime = 0;
    m244_cameraMoveTimer = 0;
    m244_cameraMoveObj = omAddObj(31, 0, 0, -1, m244_CameraMoveObjMain);
    camera = gCameraList;
    for (i = 1; i < Hu3DBufNum; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

// Camera debug mode: R cycles between free camera control and moving the camera info text.
void m244_CameraDebugPad(void) {
    MgCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (m244_cameraDebugMode) {
        case 1:
            if ((u16)HuPadBtn[0] & A_BUTTON) {
                speed = 8.0f;
            }
            if (HuPadBtn[0] & B_BUTTON) {
                speed = 0.5f;
            }
            if (HuPadBtnDown[0] & START_BUTTON) {
                Center.x = 0.0f;
                Center.y = 191.2f;
                Center.z = 0.2f;
                CRot.x = -14.5f;
                CRot.y = 0.0f;
                CRot.z = 0.0f;
                CZoom = 1069.0f;
            } else {
                delta.rot.x = (f32)HuPadStkY[0] * 0.125 * speed;
                delta.rot.y = (f32)HuPadStkX[0] * 0.125 * speed;
                if (HuPadBtn[0] & L_JPAD) {
                    delta.center.x = speed * 2.0;
                }
                if (HuPadBtn[0] & R_JPAD) {
                    delta.center.x = -(speed * 2.0);
                }
                if (HuPadBtn[0] & U_JPAD) {
                    delta.center.z = -(speed * 2.0);
                }
                if (HuPadBtn[0] & D_JPAD) {
                    delta.center.z = speed * 2.0;
                }
                if (HuPadBtn[0] & U_CBUTTONS) {
                    delta.center.y = speed * 2.0;
                }
                if (HuPadBtn[0] & D_CBUTTONS) {
                    delta.center.y = -(speed * 2.0);
                }
                if (HuPadBtn[0] & R_CBUTTONS) {
                    delta.zoom = speed * 2.0;
                }
                if (HuPadBtn[0] & L_CBUTTONS) {
                    delta.zoom = -(speed * 2.0);
                }
                delta.center.x += Center.x;
                delta.center.y += Center.y;
                delta.center.z += Center.z;
                delta.rot.x += CRot.x;
                delta.rot.y += CRot.y;
                delta.rot.z += CRot.z;
                delta.zoom += CZoom;
                m244_CameraMoveStart(delta.center.x, delta.center.y, delta.center.z, delta.rot.x, delta.rot.y,
                                             delta.rot.z, delta.zoom, 1);
            }
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE");
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 80, omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 88, omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 96, omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 104, omDBGStrBuf);
            mgFieldStat = 0;
            break;
        case 2:
            if ((HuPadBtn[0] & R_JPAD) || (HuPadBtn[0] & R_CBUTTONS)) {
                m244_cameraDebugX++;
            }
            if (HuPadBtn[0] & (L_JPAD | L_CBUTTONS)) {
                m244_cameraDebugX--;
            }
            if (HuPadBtn[0] & (D_JPAD | D_CBUTTONS)) {
                m244_cameraDebugY++;
            }
            if (HuPadBtn[0] & (U_JPAD | U_CBUTTONS)) {
                m244_cameraDebugY--;
            }
            fontcolor = 8;
            sprintf(omDBGStrBuf, "CAMERA TEST_MODE ");
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 80, omDBGStrBuf);
            sprintf(omDBGStrBuf, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 88, omDBGStrBuf);
            sprintf(omDBGStrBuf, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 96, omDBGStrBuf);
            sprintf(omDBGStrBuf, " ZOOM   %3.3f ", CZoom);
            print8(m244_cameraDebugX + 20, m244_cameraDebugY + 104, omDBGStrBuf);
            break;
        default:
            mgFieldStat = 1;
            break;
    }
    if (HuPadBtnDown[0] & R_TRIG) {
        if (m244_cameraDebugMode & 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (++m244_cameraDebugMode >= 3) {
            m244_cameraDebugMode = 0;
        }
    }
}

// Interpolates the camera from the origin preset to the target preset over m244_cameraMoveTime frames.
void m244_CameraMoveObjMain(omObjData *object) {
    f32 t;

    if (m244_cameraMoveTime <= 0) {
        m244_CameraPosUpdate(0);
        m244_cameraMoveF = 0;
        return;
    }
    if (m244_cameraMoveTimer == 0) {
        Center.x = m244_cameraKeyTbl[0].center.x;
        Center.y = m244_cameraKeyTbl[0].center.y;
        Center.z = m244_cameraKeyTbl[0].center.z;
        CRot.x = m244_cameraKeyTbl[0].rot.x;
        CRot.y = m244_cameraKeyTbl[0].rot.y;
        CRot.z = m244_cameraKeyTbl[0].rot.z;
        CZoom = m244_cameraKeyTbl[0].zoom;
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
        m244_cameraMoveTime = 0;
    } else {
        switch (m244_cameraMoveMode) {
            case 0:
                t = (f32)m244_cameraMoveTimer / (f32)m244_cameraMoveTime;
                break;
            case 1:
                t = (f32)m244_cameraMoveTimer / (f32)m244_cameraMoveTime;
                t = sindf(t * 90.0f);
                break;
            default:
                t = (f32)m244_cameraMoveTimer / (f32)m244_cameraMoveTime;
                t = sindf(t * 90.0f);
                t = t * t;
                break;
        }
        Center.x = m244_InterpCalc(t, m244_cameraKeyTbl[0].center.x,
                                                m244_cameraKeyTbl[1].center.x);
        Center.y = m244_InterpCalc(t, m244_cameraKeyTbl[0].center.y,
                                                m244_cameraKeyTbl[1].center.y);
        Center.z = m244_InterpCalc(t, m244_cameraKeyTbl[0].center.z,
                                                m244_cameraKeyTbl[1].center.z);
        CRot.x = m244_AngleInterpCalc(t, m244_cameraKeyTbl[0].rot.x, m244_cameraKeyTbl[1].rot.x);
        CRot.y = m244_AngleInterpCalc(t, m244_cameraKeyTbl[0].rot.y, m244_cameraKeyTbl[1].rot.y);
        CRot.z = m244_AngleInterpCalc(t, m244_cameraKeyTbl[0].rot.z, m244_cameraKeyTbl[1].rot.z);
        CZoom = m244_InterpCalc(t, m244_cameraKeyTbl[0].zoom, m244_cameraKeyTbl[1].zoom);
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
        if (m244_cameraMoveTimer > 0) {
            m244_cameraMoveTimer--;
        } else {
            m244_cameraMoveTimer++;
        }
    }
    m244_cameraMoveF = 1;
    m244_CameraPosUpdate(0);
}

void m244_CameraKeyStore(s32 arg0) {
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
    m244_cameraKeyTbl[arg0].center.x = Center.x;
    m244_cameraKeyTbl[arg0].center.y = Center.y;
    m244_cameraKeyTbl[arg0].center.z = Center.z;
    m244_cameraKeyTbl[arg0].rot.x = CRot.x;
    m244_cameraKeyTbl[arg0].rot.y = CRot.y;
    m244_cameraKeyTbl[arg0].rot.z = CRot.z;
    m244_cameraKeyTbl[arg0].zoom = CZoom;
    m244_cameraKeyTbl[arg0].unk_1C = m244_cameraKeyTbl[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void m244_CameraMoveStart(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        m244_cameraMoveTimer = frames - 1;
        m244_cameraMoveTime = frames;
        if (x != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].center.x = x;
        } else {
            m244_cameraKeyTbl[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].center.y = y;
        } else {
            m244_cameraKeyTbl[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].center.z = z;
        } else {
            m244_cameraKeyTbl[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].rot.x = rotX;
        } else {
            m244_cameraKeyTbl[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].rot.y = rotY;
        } else {
            m244_cameraKeyTbl[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].rot.z = rotZ;
        } else {
            m244_cameraKeyTbl[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            m244_cameraKeyTbl[0].zoom = zoom;
        } else {
            m244_cameraKeyTbl[0].zoom = CZoom;
        }
        m244_CameraKeyStore(1);
    }
}

void m244_CameraMoveStop(void) {
    m244_cameraMoveObj->func = NULL;
}

void m244_CameraMoveResume(void) {
    m244_CameraKeyStore(0);
    m244_CameraKeyStore(1);
    m244_cameraMoveF = 0;
    m244_cameraMoveTime = 0;
    m244_cameraMoveTimer = 0;
    m244_cameraMoveObj->func = m244_CameraMoveObjMain;
}

void m244_CameraFocusInit(void) {
    HuCamera *camera;
    s32 i;

    m244_cameraFocusNum = 0;
    m244_cameraFocusTbl = HuMemAllocTag(16 * sizeof(RockinRacewayVec), TAG_OVERLAY);
    m244_cameraFocusObj = omAddObj(31, 0, 0, -1, m244_CameraFocusObjMain);
    camera = gCameraList;
    for (i = 1; i < Hu3DBufNum; i++) {
        camera->viewports[i].vp.vscale[0] = camera->viewports[0].vp.vscale[0];
        camera->viewports[i].vp.vscale[1] = camera->viewports[0].vp.vscale[1];
        camera->viewports[i].vp.vscale[2] = camera->viewports[0].vp.vscale[2];
        camera->viewports[i].vp.vtrans[0] = camera->viewports[0].vp.vtrans[0];
        camera->viewports[i].vp.vtrans[1] = camera->viewports[0].vp.vtrans[1];
        camera->viewports[i].vp.vtrans[2] = camera->viewports[0].vp.vtrans[2];
    }
}

void m244_CameraFocusAdd(Vec *arg0, f32 arg1) {
    if (m244_cameraFocusObj != NULL && m244_cameraFocusNum < 16) {
        m244_cameraFocusTbl[m244_cameraFocusNum].pos[0] = arg0->x;
        do {
        } while (0); // splits the basic block so the entry address is recomputed
        m244_cameraFocusTbl[m244_cameraFocusNum].pos[1] = arg0->y;
        m244_cameraFocusTbl[m244_cameraFocusNum].pos[2] = arg0->z;
        m244_cameraFocusTbl[m244_cameraFocusNum].weight = arg1;
        m244_cameraFocusNum++;
    }
}

void m244_RacerFocusAdd(RockinRacewayRacer *racer, f32 arg1) {
    Vec pos;

    pos.x = racer->pos.x + 100.0;
    pos.y = racer->pos.y + 100.0;
    pos.z = racer->pos.z;
    m244_CameraFocusAdd(&pos, arg1);
    pos.x = racer->pos.x - 100.0;
    pos.y = racer->pos.y - 100.0;
    pos.z = racer->pos.z;
    m244_CameraFocusAdd(&pos, arg1);
}

void m244_CameraFocusCalc(void) {
    RockinRacewayVec *entry;
    f32 max[3];
    f32 min[3];
    s32 j;
    s32 i;

    if (m244_cameraFocusNum > 0) {
        for (i = 0; i < 4; i++) {
            m244_cameraFocus.pos[i] = 0.0f;
        }
        for (i = 0; i < m244_cameraFocusNum; i++) {
            m244_cameraFocus.pos[3] += m244_cameraFocusTbl[i].weight;
        }
        for (i = 0; i < 3; i++) {
            max[i] = m244_cameraFocusTbl[0].pos[i];
        }
        for (i = 0; i < 3; i++) {
            min[i] = m244_cameraFocusTbl[0].pos[i];
        }
        for (i = 1; i < m244_cameraFocusNum; i++) {
            entry = &m244_cameraFocusTbl[i];
            for (j = 0; j < 3; j++) {
                if (max[j] < entry->pos[j]) {
                    max[j] = entry->pos[j];
                }
            }
        }
        for (i = 1; i < m244_cameraFocusNum; i++) {
            entry = &m244_cameraFocusTbl[i];
            for (j = 0; j < 3; j++) {
                if (min[j] > entry->pos[j]) {
                    min[j] = entry->pos[j];
                }
            }
        }
        for (i = 0; i < 3; i++) {
            m244_cameraFocus.pos[i] = (max[i] + min[i]) * 0.5f;
        }
        if (m244_cameraFocus.pos[3] >= 1.0f) {
            m244_cameraFocus.pos[3] = 1.0f;
        }
    } else {
        m244_cameraFocus.pos[0] = Center.x;
        m244_cameraFocus.pos[1] = Center.y;
        m244_cameraFocus.pos[2] = Center.z;
        m244_cameraFocus.pos[3] = 0.0f;
    }
}

// Moves the camera to keep all of the registered focus points in view.
void m244_CameraFocusObjMain(omObjData *object) {
    f32 screen[2];
    f32 extent;
    f32 scale;
    s32 i;

    extent = 0.0f;
    m244_CameraFocusCalc();
    Center.x = m244_InterpCalc(m244_cameraFocus.pos[3], Center.x, m244_cameraFocus.pos[0]);
    Center.y = m244_InterpCalc(m244_cameraFocus.pos[3], Center.y, m244_cameraFocus.pos[1]);
    Center.z = m244_InterpCalc(m244_cameraFocus.pos[3], Center.z, m244_cameraFocus.pos[2]);
    m244_CameraPosUpdate(0);
    for (i = 0; i < m244_cameraFocusNum; i++) {
        m244_ScreenPosCalc(0, m244_cameraFocusTbl[i].pos, NULL, screen);
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
    m244_cameraFocus.zoom = scale * CZoom;
    if (m244_phase == 2) {
        if (m244_cameraFocus.zoom < 1500.0f) {
            m244_cameraFocus.zoom = 1500.0f;
        } else if (m244_cameraFocus.zoom >= 5000.0f) {
            m244_cameraFocus.zoom = 5000.0f;
        }
    } else if (m244_cameraFocus.zoom < 1000.0f) {
        m244_cameraFocus.zoom = 1000.0f;
    } else if (m244_cameraFocus.zoom >= 5000.0f) {
        m244_cameraFocus.zoom = 5000.0f;
    }
    CZoom = m244_InterpCalc(m244_cameraFocus.pos[3] * 0.5f, CZoom, m244_cameraFocus.zoom);
    CRot.x = m244_AngleStepCalc(318.38f, CRot.x, 10.0f);
    CRot.y = m244_AngleStepCalc(0.0f, CRot.y, 10.0f);
    m244_cameraFocusNum = 0;
}

void m244_CameraFocusStop(void) {
    m244_cameraFocusObj->func = NULL;
}

void m244_CameraFocusStart(void) {
    m244_cameraFocusNum = 0;
    m244_cameraFocusObj->func = m244_CameraFocusObjMain;
}

void m244_CameraPosUpdate(s32 camIndex) {
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

// Projects pos with the camera; screen receives the pixel position and depth, and normalized the
// position relative to the screen center.
void m244_ScreenPosCalc(s32 camIndex, f32 *pos, f32 *screen, f32 *normalized) {
    HuCamera *camera = &gCameraList[camIndex];
    Mtx lookAt;
    Mtx mtx;
    u16(*integer)[4] = (u16(*)[4])mtx.m;
    u16(*fraction)[4] = (u16(*)[4])mtx.m[2];
    f32 viewX, viewY, viewZ;
    f32 depth;
    f32 x, y;

    guLookAt(&lookAt, camera->pos.x, camera->pos.y, camera->pos.z, camera->at.x, camera->at.y, camera->at.z,
             camera->up.x, camera->up.y, camera->up.z);
    HuTranslate(&mtx, pos[0], pos[1], pos[2]);
    guMtxCatL(&mtx, &lookAt, &mtx);
    viewX = (s32)(((u32)integer[3][0] << 16) | fraction[3][0]) >> 16;
    viewY = (s32)(((u32)integer[3][1] << 16) | fraction[3][1]) >> 16;
    viewZ = (s32)(((u32)integer[3][2] << 16) | fraction[3][2]) >> 16;
    viewZ = viewZ * sindf(gCameraList[camIndex].fov / 2.0) / cosdf(gCameraList[camIndex].fov / 2.0);
    depth = fabsf(viewZ);
    if (depth != 0.0) {
        x = camera->viewports[Hu3DCamMtxNo].vp.vscale[0] / 4.0 * viewX / depth / (4.0f / 3.0f);
        y = camera->viewports[Hu3DCamMtxNo].vp.vscale[1] / 4.0 * -viewY / depth;
        if (screen != NULL) {
            screen[0] = (s16)(x + camera->viewports[Hu3DCamMtxNo].vp.vtrans[0] * 0.25f);
            screen[1] = (s16)(y + camera->viewports[Hu3DCamMtxNo].vp.vtrans[1] * 0.25f);
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

void m244_ReplayInit(void) {
    RockinRacewayReplayFrame *pool = HuMemAllocTag(30 * sizeof(RockinRacewayReplayFrame), TAG_OVERLAY);

    m244_replayTbl = pool;
    memset(pool, 0, 30 * sizeof(RockinRacewayReplayFrame));
    m244_replayCnt = 0;
    m244_replayNo = 0;
}

// Records the current race state into the next replay frame.
void m244_ReplayRecord(void) {
    RockinRacewayReplayFrame *frame = &m244_replayTbl[m244_replayNo];
    RockinRacewayReplayRacer *replay;
    RockinRacewayRacer *racer;
    RockinRacewayModelState *state;
    RockinRacewayEffectState *effectState;
    RockinRacewayEffect *effect;
    HmfModel *model;
    s32 i;

    frame->unk00 = m244_raceTime;
    for (i = 0; i < 4; i++) {
        frame->unk04[i] = m244_rankOrderTbl[i];
    }
    for (i = 0; i < 4; i++) {
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[i]);
        replay = &frame->racers[i];
        replay->trans.x = mgPlayerObjTbl[i]->trans.x;
        replay->trans.y = mgPlayerObjTbl[i]->trans.y;
        replay->trans.z = mgPlayerObjTbl[i]->trans.z;
        replay->rot.x = mgPlayerObjTbl[i]->rot.x;
        replay->rot.y = mgPlayerObjTbl[i]->rot.y;
        replay->rot.z = mgPlayerObjTbl[i]->rot.z;
        replay->scale.x = mgPlayerObjTbl[i]->scale.x;
        replay->scale.y = mgPlayerObjTbl[i]->scale.y;
        replay->scale.z = mgPlayerObjTbl[i]->scale.z;
        replay->unk24 = racer->unk38;
        replay->unk28 = racer->unk24;
    }
    for (state = frame->models, i = 1; i < 13; i++, state++) {
        if (m244_sparkObj->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[m244_sparkObj->model[i]];
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
    for (effectState = frame->effects, effect = m244_smokeTbl, i = 0; i < 16;
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
    m244_replayCnt++;
    m244_replayNo++;
    if (m244_replayNo >= 30) {
        m244_replayNo -= 30;
    }
}

RockinRacewayReplayFrame *m244_ReplayFrameGet(s32 arg0) {
    s32 index = arg0;

    if (arg0 >= m244_replayCnt || arg0 >= 30) {
        return NULL;
    }
    if (m244_replayCnt >= 30) {
        index += m244_replayNo;
    }
    if (index >= 30) {
        index -= 30;
    }
    return &m244_replayTbl[index];
}

// Plays back a recorded replay frame, interpolating from the previous frame.
void m244_ReplayPlay(s32 index) {
    RockinRacewayReplayFrame *frame;
    RockinRacewayReplayFrame *prevFrame;
    RockinRacewayReplayRacer *replay;
    RockinRacewayReplayRacer *prev;
    RockinRacewayReplayRacer *prev2;
    RockinRacewayModelState *state;
    RockinRacewayReplayStatePtr prevState;
    RockinRacewayEffectState *effectState;
    RockinRacewayEffect *effect;
    RockinRacewaySnapshot *snapshot;
    omObjData *object;
    HmfModel *model;
    s32 times[2];
    f32 t;
    s32 i;
    s32 j;

    if (m244_replayPrevNo != index) {
        m244_replayPrevNo = index;
        m244_replayFrameTime = 0;
    } else {
        m244_replayFrameTime++;
    }
    t = m244_replayFrameTime / 4.5f;
    if (1.0f <= t) {
        t = 1.0f;
    } else if (t <= 0.0f) {
        t = 0.0f;
    }
    frame = m244_ReplayFrameGet(index);
    times[0] = frame->unk00;
    times[1] = m244_recordTime;
    m244_TimeDigitCalc(times);
    m244_BoardFaceSet(frame->unk04);
    m244_BoardTimeSet(times);
    for (i = 0; i < 4; i++) {
        replay = &frame->racers[i];
        object = mgPlayerObjTbl[i];
        if (index - 1 < 0) {
            prev = replay;
        } else {
            prev = &m244_ReplayFrameGet(index - 1)->racers[i];
        }
        object->trans.x = m244_InterpCalc(t, prev->trans.x, replay->trans.x);
        object->trans.y = m244_InterpCalc(t, prev->trans.y, replay->trans.y);
        object->trans.z = m244_InterpCalc(t, prev->trans.z, replay->trans.z);
        object->rot.x = m244_AngleInterpCalc(t, prev->rot.x, replay->rot.x);
        object->rot.y = m244_AngleInterpCalc(t, prev->rot.y, replay->rot.y);
        object->rot.z = m244_AngleInterpCalc(t, prev->rot.z, replay->rot.z);
        object->scale.x = m244_InterpCalc(t, prev->scale.x, replay->scale.x);
        object->scale.y = m244_InterpCalc(t, prev->scale.y, replay->scale.y);
        object->scale.z = m244_InterpCalc(t, prev->scale.z, replay->scale.z);
    }
    if (m244_ghostDispF != 0) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 2; j++) {
                if (index - (j + 1) < 0) {
                    prev = &frame->racers[i];
                } else {
                    prev = &m244_ReplayFrameGet(index - (j + 2))->racers[i];
                }
                if (index - (j + 2) < 0) {
                    prev2 = prev;
                } else {
                    prev2 = &m244_ReplayFrameGet(index - (j + 3))->racers[i];
                }
                model = &Hu3DData[mgPlayerObjTbl[i]->model[j + 3]];
                if (m244_ghostTbl[j].racers[i].active != 0) {
                    snapshot = &m244_ghostTbl[j].racers[i];
                    if (snapshot->unk00 != 0) {
                        model->pos.x = snapshot->trans.x;
                        model->pos.y = snapshot->trans.y;
                        model->pos.z = snapshot->trans.z;
                        model->rot.x = snapshot->rot.x;
                        model->rot.y = snapshot->rot.y;
                        model->rot.z = snapshot->rot.z;
                        model->scale.x = snapshot->scale.x;
                        model->scale.y = snapshot->scale.y;
                        model->scale.z = snapshot->scale.z;
                        snapshot->unk00--;
                    } else {
                        model->pos.x = m244_InterpCalc(t, prev2->trans.x, prev->trans.x);
                        model->pos.y = m244_InterpCalc(t, prev2->trans.y, prev->trans.y);
                        model->pos.z = m244_InterpCalc(t, prev2->trans.z, prev->trans.z);
                        model->rot.x = m244_AngleInterpCalc(t, prev2->rot.x, prev->rot.x);
                        model->rot.y = m244_AngleInterpCalc(t, prev2->rot.y, prev->rot.y);
                        model->rot.z = m244_AngleInterpCalc(t, prev2->rot.z, prev->rot.z);
                        model->scale.x = m244_InterpCalc(t, prev2->scale.x, prev->scale.x);
                        model->scale.y = m244_InterpCalc(t, prev2->scale.y, prev->scale.y);
                        model->scale.z = m244_InterpCalc(t, prev2->scale.z, prev->scale.z);
                    }
                }
            }
        }
    }
    if (index - 1 < 0) {
        prevFrame = frame;
    } else {
        prevFrame = m244_ReplayFrameGet(index - 1);
    }
    for (state = frame->models, prevState.model = prevFrame->models, i = 1; i < 13; i++, state++, prevState.model++) {
        if (m244_sparkObj->model[i] == -1) {
            continue;
        }
        model = &Hu3DData[m244_sparkObj->model[i]];
        model->attr = state->attr;
        model->motTime = m244_InterpCalc(t, prevState.model->motTime, state->motTime);
        model->motSpeed = 0.0f;
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
    for (effectState = frame->effects, prevState.effect = prevFrame->effects, effect = m244_smokeTbl, i = 0;
         i < 16; i++, effect++, effectState++, prevState.effect++) {
        if (effect->model == -1) {
            continue;
        }
        model = &Hu3DData[effect->model];
        effect->active = effectState->active;
        model->attr = effectState->attr;
        effect->frame = effectState->frame;
        effect->speed = effectState->speed;
        m244_BillboardColorPatSet(effect->model, HuSprAnimDataGet(m244_sprTbl[2]), effect->frame,
                                     m244_smokeColor);
        if (prevState.effect->active != 0) {
            model->pos.x = m244_InterpCalc(t, prevState.effect->pos.x, effectState->pos.x);
            model->pos.y = m244_InterpCalc(t, prevState.effect->pos.y, effectState->pos.y);
            model->pos.z = m244_InterpCalc(t, prevState.effect->pos.z, effectState->pos.z);
        } else {
            model->pos.x = effectState->pos.x;
            model->pos.y = effectState->pos.y;
            model->pos.z = effectState->pos.z;
        }
        model->rot.x = effectState->rot.x;
        model->rot.y = effectState->rot.y;
        model->rot.z = effectState->rot.z;
        model->scale.x = effectState->scale.x;
        model->scale.y = effectState->scale.y;
        model->scale.z = effectState->scale.z;
    }
}

// Shifts the recorded replay frames so that the winner ends up ahead of the other racers.
void m244_ReplayWinnerAdjust(s32 winner) {
    RockinRacewayReplayRacer *replay;
    RockinRacewayRacer *racer;
    s32 angle;
    s32 i;
    s32 j;

    for (i = 0; i < 30; i++) {
        for (j = 0; j < 4; j++) {
            replay = &m244_ReplayFrameGet(i)->racers[j];
            if (j == winner) {
                replay->trans.x -= 0.1f * 200.0;
                replay->trans.x += i / 30.0f * (0.2f * 200.0);
            } else {
                replay->trans.x -= 0.1f * 200.0;
            }
        }
    }
    for (j = 0; j < 4; j++) {
        racer = (RockinRacewayRacer *)m244_WorkPtrGet(mgPlayerObjTbl[j]);
        if (winner == j) {
            racer->unk44 += 0.1f * 200.0;
        } else {
            racer->unk44 -= 0.1f * 200.0;
        }
    }
    replay = &m244_ReplayFrameGet(29)->racers[winner];
    angle = 90.0f - replay->unk28;
    for (i = 0; i < 30; i++) {
        replay = &m244_ReplayFrameGet(i)->racers[winner];
        replay->unk28 += angle;
        if (replay->unk28 > 360.0f) {
            replay->unk28 -= 360.0f;
        } else if (replay->unk28 < 0.0f) {
            replay->unk28 += 360.0f;
        }
        replay->rot.x = sindf(replay->unk28) * replay->unk24 * 30.0f;
    }
}

void m244_SeQueueInit(void) {
    RockinRacewaySfx *sfx;
    s32 i;

    m244_seQueue = HuMemAllocTag(16 * sizeof(RockinRacewaySfx), TAG_OVERLAY);
    sfx = m244_seQueue;
    memset(sfx, 0, 16 * sizeof(RockinRacewaySfx));
    for (i = 0; i < 16; i++, sfx++) {
        sfx->soundId = -1;
    }
}

// Finds a free entry in the sfx pool, fills it in, and returns its index, or -1 if the pool is full.
s32 m244_SeQueueAdd(s16 soundId, s16 frames, s16 unk04, s16 playerIndex) {
    RockinRacewaySfx *sfx = m244_seQueue;
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
void m244_SeQueueUpdate(void) {
    RockinRacewaySfx *sfx = m244_seQueue;
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
                    HuAudPlayerFXPlay(sfx->soundId, sfx->playerIndex);
                    break;
                case 2:
                    CharFXPlay(sfx->soundId, GwPlayer[(s16)(sfx->playerIndex % 4)].chr);
                    break;
                default:
                    HuAudPlayerFXPlay(GwPlayer[(s16)(sfx->playerIndex % 4)].chr + sfx->soundId + 1, sfx->playerIndex);
                    break;
            }
            sfx->soundId = -1;
        }
        sfx->frames--;
    }
}

f32 m244_AngleDiffCalc(f32 arg0, f32 arg1) {
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
f32 m244_AngleStepCalc(f32 target, f32 current, f32 step) {
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
f32 m244_InterpCalc(f32 arg0, f32 arg1, f32 arg2) {
    return arg1 + arg0 * (arg2 - arg1);
}

f32 m244_AngleInterpCalc(f32 arg0, f32 arg1, f32 arg2) {
    return m244_AngleStepCalc(arg2, arg1, fabsf(m244_AngleDiffCalc(arg2, arg1) * arg0));
}

// Evaluates a quadratic bezier curve, blending arg1/arg2/arg3 as a function of arg0.
f32 m244_BezierCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 inv = 1.0 - arg0;

    return inv * inv * arg1 + (inv * arg0 * arg2) * 2.0 + arg0 * arg0 * arg3;
}

// Evaluates the quadratic bezier curve per component for 3-component vectors.
void m244_BezierVecCalc(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    s32 i;

    for (i = 0; i < 3; i++) {
        *out++ = m244_BezierCalc(arg0, *arg1++, *arg2++, *arg3++);
    }
}

// Evaluates a curve, blending arg1/arg2/arg3 as a function of arg0.
f32 m244_BezierTangentCalc(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    return ((arg0 - 1.0) * arg1 + (1.0 - 2.0 * arg0) * arg2 + arg0 * arg3) * 2.0;
}

// Computes the normalized tangent of the curve per component for 3-component vectors.
void m244_BezierTangentVecCalc(f32 arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *out) {
    f32 tangent[3];
    f32 length;
    s32 i;

    for (i = 0; i < 3; i++) {
        tangent[i] = m244_BezierTangentCalc(arg0, *arg1++, *arg2++, *arg3++);
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
f32 m244_AngleCalc(f32 arg0, f32 arg1) {
    f32 angle = atan2df(arg1, arg0);

    if (angle < 0.0) {
        angle += 360.0;
    } else if (angle >= 360.0) {
        angle -= 360.0;
    }
    return angle;
}

// Converts a direction vector into pitch and yaw angles, with zero roll.
void m244_DirRotCalc(Vec *dir, f32 *rot) {
    *rot++ = m244_AngleCalc(sqrtf(dir->x * dir->x + dir->z * dir->z), -dir->y);
    *rot++ = m244_AngleCalc(dir->z, dir->x);
    *rot = 0.0f;
}

void m244_WorkPtrSet(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 m244_WorkPtrGet(omObjData *object) {
    RockinRacewayWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

s32 m244_BillboardColorMdlCreate(HuSprAnimData *sprite, u8 *color) {
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
    model = Hu3DModelDLCreate(0x18C1, buffer, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x71010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), Hu3DModelTag);
    m244_BillboardVtxCreate(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(m244_gfxBillboardInit));
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
    if (sprite->pixelBits & 0x8000) {
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
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->pixelBits;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->pixelBits & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
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
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[Hu3DBufNo + 1];
    return model;
}

s32 m244_BillboardColorMdlLink(HuSprAnimData *sprite, u16 model, u8 *color) {
    HmfModel *srcModel = Hu3DData + model;
    HmfData *srcData = srcModel->hmf;
    HmfData *data;
    Gfx *gfx;
    s32 newModel;
    s32 i;

    newModel = Hu3DModelDLCreate(srcModel->attr, NULL, 4);
    data = Hu3DData[newModel].hmf;
    data->unk60->unk50 = srcData->unk60->unk50;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), Hu3DModelTag);
    data->unk3C->unk10 = srcData->unk3C->unk10;
    data->unk3C->unk14 = srcData->unk3C->unk14;
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x100, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], color[3]);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[Hu3DBufNo + 1];
    return newModel;
}

void m244_BillboardColorPatSet(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[Hu3DBufNo + 1];

    data->unk3C->unk00[0] = gfx;
    gDPPipeSync(gfx);
    gSPSegment(gfx + 1, 2, osVirtualToPhysical(sprite->pat[frame].data));
    gSPDisplayList(gfx + 2, osVirtualToPhysical(data->unk3C->unk10));
    gDPSetPrimColor(gfx + 3, 0, 0, color[0], color[1], color[2], color[3]);
    gDPPipeSync(gfx + 4);
    gSPDisplayList(gfx + 5, osVirtualToPhysical(data->unk3C->unk14));
    gDPPipeSync(gfx + 6);
    gSPEndDisplayList(gfx + 7);
}

s32 m244_BillboardVtxCreate(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
    s32 capacity = 0x1000;
    s32 width, height, scaledWidth, scaledHeight;
    s32 size, slices, textureHeight, sliceHeight, vertexCount;
    s32 i, j;
    Vtx_t *vertices, *start;

    if (sprite->palNum >= 2) {
        capacity = 0x800;
    }
    width = sprite->pat->sizeX;
    height = sprite->pat->sizeY;
    scaledWidth = width * 100.0 * scale / 32.0;
    scaledHeight = height * 100.0 * scale / 32.0;
    if ((sprite->pixelBits & 0xFFF) == 4) {
        size = ((width + 1) & 0xFFFE) * height * 4;
    } else {
        size = width * height * sprite->pixelBits;
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
    for (i = 0; i < Hu3DBufNum; i++) {
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

s32 m244_QuadMdlCreate(HuSprAnimData *sprite, RockinRacewayQuad *quad) {
    u8 *buffer;
    Gfx *gfx;
    HmfData *data;
    u16 format;
    s32 i;
    s32 model;
    s32 size;

    gfx = HuMemAlloc(0x10000);
    buffer = (u8 *)gfx;
    model = Hu3DModelDLCreate(0x4C1, buffer, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x1000000;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), Hu3DModelTag);
    for (i = 0; i < Hu3DBufNum; i++) {
        data->unk44[i] = HuMemAllocTag(sizeof(RockinRacewayQuad), data->unk0E);
        *(RockinRacewayQuad *)data->unk44[i] = *quad;
    }
    gSPDisplayList(gfx++, osVirtualToPhysical(m244_gfxBillboardInit));
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
    if (sprite->pixelBits & 0x8000) {
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
    if (sprite->palNum >= 2) {
        gDPSetTextureLUT(gfx++, G_TT_RGBA16);
        if (sprite->pixelBits == 4) {
            gDPLoadTLUT_pal16(gfx++, 0, sprite->pal);
        } else {
            gDPLoadTLUT_pal256(gfx++, sprite->pal);
        }
        gDPPipeSync(gfx++);
        format = G_IM_FMT_CI;
    } else {
        gDPSetTextureLUT(gfx++, G_TT_NONE);
        gDPPipeSync(gfx++);
        format = sprite->pixelBits;
        format = ((u32)format / 0x8000) * 4;
    }
    switch (sprite->pixelBits & 0xFFF) {
        case 4:
            gDPLoadTextureBlock_4b(gfx++, 0x02000000, format, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                   G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 8:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_8b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
                                G_TX_CLAMP, G_TX_CLAMP, 0, 0, G_TX_NOLOD, G_TX_NOLOD);
            break;
        case 16:
            gDPLoadTextureBlock(gfx++, 0x02000000, format, G_IM_SIZ_16b, sprite->pat->sizeX, sprite->pat->sizeY, 0,
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
    for (i = 0; i < Hu3DBufNum; i++) {
        gfx = (data->unk3C->unk00 + 1)[i] = HuMemAllocTag(0x200, data->unk0E);
        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk10));
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);
        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, osVirtualToPhysical(data->unk3C->unk14));
        gDPPipeSync(gfx++);
        gSPEndDisplayList(gfx++);
    }
    data->unk3C->unk00[0] = data->unk3C->unk00[Hu3DBufNo + 1];
    return model;
}

// Shows a character face sprite above each of the 4 slots, or a blank one for a negative player.
void m244_BoardFaceUpdate(s16 *models, HuSprAnimData *sprite, s32 *players) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (players[i] < 0) {
            m244_BillboardColorPatSet(models[i], sprite, 8, m244_faceColor);
        } else {
            if (players[i] >= 4) {
                players[i] = 0;
            }
            m244_BillboardColorPatSet(models[i], sprite, GwPlayer[players[i]].chr, m244_faceColor);
        }
        Hu3DModelPosSet(models[i], m244_boardFacePosTbl[i].x, m244_boardFacePosTbl[i].y + 0.2f * 200.0,
                        m244_boardFacePosTbl[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}

// Shows a digit sprite for each of the 12 digits in m244_timeDigitTbl, clamped to 0-9.
void m244_BoardDigitUpdate(s16 *models, HuSprAnimData *sprite, s32 *values) {
    s32 *digits = m244_timeDigitTbl[0];
    s32 i;

    for (i = 0; i < 12; i++) {
        if (digits[i] >= 9) {
            digits[i] = 9;
        } else if (digits[i] < 0) {
            digits[i] = 0;
        }
        m244_BillboardColorPatSet(models[i], sprite, digits[i], m244_digitColor);
        Hu3DModelPosSet(models[i], m244_boardDigitPosTbl[i].x, m244_boardDigitPosTbl[i].y + 0.2f * 200.0,
                        m244_boardDigitPosTbl[i].z);
        Hu3DModelRotSet(models[i], 95.72f, 0.0f, 0.0f);
    }
}
