#include "common.h"
#include "overlays/minigame.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/wipe.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/gamework.h"
#include "math.h"
#include "game/hmfdraw.h"
#include "game/hmfspr.h"
#include "game/input.h"
#include "game/printfunc.h"
#include "game/gamemes.h"

#define CAMERA_KEEP 65535.0f

typedef struct UnkLogJamSprites { // 0xC bytes, two entries
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} UnkLogJamSprites;

typedef struct LogJamPlayerWork LogJamPlayerWork;

struct LogJamPlayerWork { // 0x78 bytes, 0x20 entries allocated by func_80108D50_log_jam
    s16 unk_00;
    s16 unk_02[3]; // model ids
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10; // position
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C; // rotation
    f32 unk_20;
    f32 unk_24;
    f32 unk_28; // velocity
    f32 unk_2C;
    f32 unk_30;
    s16 unk_34[0x0F];
    s16 unk_52;
    f32 unk_54[8]; // callback work
    void (*unk_74)(LogJamPlayerWork *work);
};

typedef struct LogJamLogWork { // 0x38 bytes, 4 entries allocated by func_80106190_log_jam
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08; // state
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10;
    s32 unk_14; // motion id
    s16 unk_18; // player index
    s16 unk_1A; // pad index
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20; // CPU difficulty
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    u16 unk_2C; // CPU buttons
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
} LogJamLogWork;

typedef struct LogJamTeam { // 0x48 bytes, 2 entries allocated by func_80106190_log_jam
    omObjData *unk_00;
    omObjData *unk_04;
    LogJamLogWork *unk_08;
    LogJamLogWork *unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    f32 unk_24; // position
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30; // rotation
    f32 unk_34;
    f32 unk_38;
    f32 unk_3C; // velocity
    f32 unk_40;
    f32 unk_44;
} LogJamTeam;

typedef struct LogJamCamera {
    Vec center;
    Vec rot;
    f32 zoom;
    f32 unk_1C;
    f32 unk_20;
} LogJamCamera;

typedef union LogJamColor {
    u32 word;
    u8 rgba[4];
} LogJamColor;

typedef struct LogJamEffect { // 0x34 bytes, 8 entries per effect set
    u16 active;
    s16 model;
    LogJamColor color;
    f32 frame;
    f32 speed;
    Vec pos;
    Vec vel;
    Vec scale;
} LogJamEffect;

typedef struct LogJamCloud { // 0x24 bytes, 5 entries
    s16 index;
    s16 group;
    s16 angle;
    f32 base;
    Vec2f pos;
    Vec2f scale;
    f32 speed;
    s32 unk_20;
} LogJamCloud;

typedef union LogJamWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} LogJamWorkBytes;

Vec D_8010DE90_log_jam[4] = { { -233.0f, 0.0f, 70.0f }, { -131.0f, 0.0f, -5.0f }, { 131.0f, 0.0f, -5.0f }, { 233.0f, 0.0f, 70.0f } };
Vec D_8010DEC0_log_jam[4] = { { -170.0f, 0.0f, 40.0f }, { -128.0f, 0.0f, 20.0f }, { 128.0f, 0.0f, 20.0f }, { 170.0f, 0.0f, 40.0f } };
Vec D_8010DEF0_log_jam[4] = { { -70.0f, 0.0f, 200.0f }, { -190.0f, 0.0f, 250.0f }, { 190.0f, 0.0f, 250.0f }, { 70.0f, 0.0f, 200.0f } };
f32 D_8010DF20_log_jam[4] = { 45.0f, 15.0f, -15.0f, -45.0f };
Vec D_8010DF30_log_jam[2] = { { -100.0f, 50.0f, 115.0f }, { 100.0f, 50.0f, 115.0f } };
LogJamColor D_8010DF48_log_jam = { 0xE9DDA180 };
LogJamColor D_8010DF4C_log_jam = { 0xFFFFFFFF };
s32 D_8010DF50_log_jam[8] = { 0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C };
s32 D_8010DF70_log_jam[8] = { 0x000200A6, 0x000300A6, 0x000700A6, 0x000400A6, 0x000500A6, 0x000600A6, 0x000800A6, 0x0009001D };
s32 D_8010DF90_log_jam = 0;
s32 D_8010DF94_log_jam[4] = { 0, 1, 2, 3 };
s16 D_8010DFA4_log_jam[4][2][2] = { { { 0, 1 }, { 2, 3 } }, { { 3, 0 }, { 1, 2 } }, { { 2, 3 }, { 0, 1 } }, { { 1, 2 }, { 3, 0 } } };
s16 D_8010DFC4_log_jam[4] = { 0, 1, 1, 0 };
s16 D_8010DFCC_log_jam[4] = { 18, 19, 21, 20 };
s32 D_8010DFD4_log_jam[8] = { 0x00020000, 0x00030000, 0x00070000, 0x00040000, 0x00050000, 0x00060000, 0x00080000, 0x00090000 };
s32 D_8010DFF4_log_jam[4] = { 0x2F, 0x30, 0x36, 0x37 };
s32 D_8010E004_log_jam[3] = { 3, 4, 5 };
f32 D_8010E010_log_jam[8] = { 200.0f, 200.0f, 200.0f, 200.0f, 200.0f, 250.0f, 200.0f, 200.0f };
s32 D_8010E030_log_jam[9] = { 0x00340003, 0x00340004, 0x00340005, 0x00340006, 0x00340007, 0x00340008, 0x00340009, 0x0034000A, 0x0034000B };
Vec2f D_8010E054_log_jam[5] = { { 120.0f, 30.0f }, { 360.0f, 45.0f }, { 0.0f, 52.0f }, { 240.0f, 60.0f }, { 480.0f, 75.0f } };
f32 D_8010E07C_log_jam[5] = { 0.7f, 0.6f, 0.55f, 0.47f, 0.4f };
s16 D_8010E090_log_jam[2] = { 38, 282 };
s32 D_8010E094_log_jam = 0;
s32 D_8010E098_log_jam = 0;
s32 D_8010E09C_log_jam = 0;

Gfx D_8010E0A0_log_jam[] = {
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

Gfx D_8010E158_log_jam[] = {
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_OFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

Gfx D_8010E178_log_jam[] = {
    gsSPDisplayList(D_8010E158_log_jam),
    gsSPDisplayList(D_8010E0A0_log_jam),
    gsSPEndDisplayList(),
};

Gfx D_8010E190_log_jam[] = {
    gsDPPipeSync(),
    gsSPDisplayList(D_8010E178_log_jam),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING | G_SHADING_SMOOTH),
    gsDPSetBlendColor(0x00, 0x00, 0x00, 0x00),
    gsDPSetPrimColor(0, 0, 0x00, 0x00, 0x00, 0xFF),
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsSPEndDisplayList(),
};

omObjData *D_8010E590_log_jam BSS;
s32 D_8010E594_log_jam BSS;
s32 D_8010E598_log_jam BSS;
s32 D_8010E59C_log_jam BSS;
s32 D_8010E5A0_log_jam BSS;
s32 D_8010E5A4_log_jam BSS;
s32 D_8010E5A8_log_jam BSS;
LogJamTeam *D_8010E5AC_log_jam BSS;
omObjData *D_8010E5B0_log_jam[2] BSS;
LogJamLogWork *D_8010E5B8_log_jam BSS;
s16 D_8010E5BC_log_jam BSS;
omObjData *D_8010E5C0_log_jam BSS;
LogJamPlayerWork *D_8010E5C4_log_jam BSS;
s16 *D_8010E5C8_log_jam BSS;
s16 *D_8010E5CC_log_jam BSS;
UnkLogJamSprites *D_8010E5D0_log_jam BSS;
LogJamCloud *D_8010E5D4_log_jam BSS;
omObjData *D_8010E5D8_log_jam BSS;
LogJamEffect *D_8010E5DC_log_jam BSS;
omObjData *D_8010E5E0_log_jam BSS;
LogJamEffect *D_8010E5E4_log_jam BSS;
LogJamCamera D_8010E5E8_log_jam[2] BSS; // target, origin
s32 D_8010E630_log_jam BSS;
s32 D_8010E634_log_jam BSS;
s32 D_8010E638_log_jam BSS;
u8 D_8010E63C_log_jam[4] BSS; /* Unreferenced. */
D_80111B50_vine_with_me_Struct D_8010E640_log_jam BSS;
extern s32 D_800A178C_main[][6];
extern s16 D_800CD1B0_main;
extern u8 D_800D6A90_main;
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;
extern s16 *D_800D04B4_main;
extern HuMtx4F *D_800D1358_main;
extern s16 D_800D138A_main;
extern HuMtx4F D_800D5A00_main[];

void func_80105B9C_log_jam(omObjData *object);
void func_80105C10_log_jam(omObjData *object);
void func_801060C4_log_jam(omObjData *object);
void func_801060E8_log_jam(omObjData *object);
void func_80106190_log_jam(void);
void func_80106F48_log_jam(omObjData *object);
void func_80106FAC_log_jam(void);
void func_801065E8_log_jam(omObjData *object);
void func_80106968_log_jam(omObjData *object);
void func_80107080_log_jam(omObjData *object, LogJamTeam *team);
void func_80107C84_log_jam(omObjData *object, LogJamTeam *team);
void func_80108840_log_jam(omObjData *object, LogJamTeam *team);
void func_80108A80_log_jam(omObjData *object, LogJamTeam *team);
s16 func_80108D1C_log_jam(f32 arg0, f32 arg1);
void func_80108D50_log_jam(void);
s16 func_80109044_log_jam(s16 arg0, s16 arg1);
void func_80109140_log_jam(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80109190_log_jam(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80109350_log_jam(s16 arg0);
void func_80108E54_log_jam(omObjData *object);
s16 func_80108CE0_log_jam(s16 arg0);
void func_801091DC_log_jam(void);
LogJamPlayerWork *func_8010910C_log_jam(s16 arg0);
void func_8010925C_log_jam(s16 arg0);
void func_801094E4_log_jam(LogJamPlayerWork *work);
void func_80109A00_log_jam(void);
s16 func_80109A7C_log_jam(s16 arg0, s16 arg1);
void func_80109AD8_log_jam(void);
void func_80109B34_log_jam(void);
void func_80109B8C_log_jam(omObjData *object);
void func_8010A0B0_log_jam(omObjData *object);
u16 func_8010A300_log_jam(s32 file);
void func_8010A344_log_jam(void);
s32 func_8010A9D4_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
void func_8010A4C0_log_jam(omObjData *object);
void func_8010A6FC_log_jam(s16 arg0, s16 arg1);
void func_8010A724_log_jam(void);
void func_8010A880_log_jam(omObjData *object);
void func_8010ABA4_log_jam(void);
void func_8010AD04_log_jam(omObjData *object);
s32 func_8010AE58_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
void func_8010B04C_log_jam(void);
void func_8010B86C_log_jam(omObjData *object);
void func_8010BCA8_log_jam(s32 arg0);
void func_8010BE94_log_jam(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
void func_8010C084_log_jam(s32 camIndex);
f32 func_8010C1D8_log_jam(f32 arg0, f32 arg1);
f32 func_8010C2DC_log_jam(f32 target, f32 current, f32 step);
f32 func_8010C49C_log_jam(f32 t, f32 start, f32 end);
f32 func_8010C4B4_log_jam(f32 t, f32 start, f32 end);
void func_8010C55C_log_jam(omObjData *object, u32 arg1);
u32 func_8010C588_log_jam(omObjData *object);
f32 func_8010C514_log_jam(f32 arg0, f32 arg1, f32 arg2);
void func_8010C5DC_log_jam(omObjData *object, s16 motion, s16 shift);
void func_8010C6A4_log_jam(omObjData *object, s16 motion, s16 time);
void func_8010C714_log_jam(omObjData *object, s16 motion, s16 time);
void func_8010C7D0_log_jam(omObjData *object);
void func_8010C7F8_log_jam(omObjData *object);
void func_8010C8B0_log_jam(omObjData *object);
void func_8010C8E0_log_jam(s16 model, const char *name, HuMtx4F *out);
void func_8010CAC0_log_jam(omObjData *object, const char *name, HuMtx4F out);
s32 func_8010CB64_log_jam(HuSprAnimData *sprite, u8 *color);
s32 func_8010D74C_log_jam(HuSprAnimData *sprite, u16 model, u8 *color);
void func_8010D950_log_jam(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color);
s32 func_8010DA84_log_jam(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void func_801059A0_log_jam(void) {
    omObjData *obj;
    u8 camIndex;

    func_8001FE20_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
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
    D_8010E5A0_log_jam = 900;
    D_8010E59C_log_jam = 0;
    D_8010E598_log_jam = 0;
    D_8010E5A4_log_jam = -1;
    D_8010E5A8_log_jam = 0;
    D_8010E5BC_log_jam = -1;
    D_8010E5CC_log_jam = HuMemAllocTag(0x40, TAG_OVERLAY);
    D_8010E590_log_jam = omAddObj(0x20, 0, 0, -1, func_80105B9C_log_jam);
    memset(&D_8010E640_log_jam, 0, 0x28);
    D_8010E640_log_jam.unk01 = 4;
    func_800E5EA0_minigame(&D_8010E640_log_jam);
}

void func_80105B9C_log_jam(omObjData *object) {
    object->func = func_80105C10_log_jam;
    func_80109B34_log_jam();
    func_8010A344_log_jam();
    func_8010A724_log_jam();
    func_8010ABA4_log_jam();
    func_80109A00_log_jam();
    func_80106190_log_jam();
    func_80108D50_log_jam();
    func_8010B04C_log_jam();
    if (_CheckFlag(10)) {
        D_8010E594_log_jam = 1;
    }
}

void func_80105C10_log_jam(omObjData *object) {
    LogJamTeam *team0;
    LogJamTeam *team1;

    switch (D_8010E5A4_log_jam) {
        case -1:
            if (D_8010E59C_log_jam >= 2) {
                WipeCreateIn(0xFF, 16);
                D_8010E5A4_log_jam = 0;
                D_8010E59C_log_jam = 0;
            }
            break;
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(5);
                HuAudFXPlay(0xE);
                D_8010E5A4_log_jam++;
                D_8010E59C_log_jam = 0;
            }
            break;
        case 1:
            if (D_8010E59C_log_jam == 30) {
                HuAudSeqPlay(0x2E);
            }
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (D_8010E5A0_log_jam + 29) / 30, 156, 32);
                func_800E6F0C_minigame(2);
                D_8010E5A4_log_jam++;
            }
            break;
        case 2:
            D_8010E5A0_log_jam--;
            func_8003F578_main((D_8010E5A0_log_jam + 29) / 30);
            if (D_8010E5A0_log_jam <= 0) {
                func_8003F5C0_main();
                GMesCreate(0x10);
                func_800E6F0C_minigame(3);
                HuAudSeqFadeOut(120);
                D_8010E5A0_log_jam = 0;
                D_8010E59C_log_jam = 0;
                D_8010E5A4_log_jam++;
            }
            break;
        case 3:
            if (func_80108CE0_log_jam(14) && GMesStatGet() == 0) {
                func_800E6F0C_minigame(4);
                func_801091DC_log_jam();
                func_80106FAC_log_jam();
                func_80109AD8_log_jam();
                D_8010E59C_log_jam = 0;
                D_8010E5A4_log_jam++;
            }
            break;
        case 4:
            if (func_80108CE0_log_jam(17)) {
                team0 = (LogJamTeam *)func_8010C588_log_jam(D_8010E5B0_log_jam[0]);
                team1 = (LogJamTeam *)func_8010C588_log_jam(D_8010E5B0_log_jam[1]);
                if (team0->unk_12 > team1->unk_12) {
                    GMesCreate(0x1E, team0->unk_08->unk_1C, team0->unk_0C->unk_1C);
                    GwPlayer[team0->unk_08->unk_18].bonusCoin += 10;
                    GwPlayer[team0->unk_0C->unk_18].bonusCoin += 10;
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 0;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 1;
                    HuAudSeqPlay(0x66);
                    D_8010E5A8_log_jam = 140;
                } else if (team0->unk_12 < team1->unk_12) {
                    GMesCreate(0x1E, team1->unk_08->unk_1C, team1->unk_0C->unk_1C);
                    GwPlayer[team1->unk_08->unk_18].bonusCoin += 10;
                    GwPlayer[team1->unk_0C->unk_18].bonusCoin += 10;
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 1;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 0;
                    HuAudSeqPlay(0x66);
                    D_8010E5A8_log_jam = 140;
                } else {
                    GMesCreate(0x20);
                    team0->unk_08->unk_06 = team0->unk_0C->unk_06 = 1;
                    team1->unk_08->unk_06 = team1->unk_0C->unk_06 = 1;
                    HuAudSeqPlay(0x6C);
                    D_8010E5A8_log_jam = 144;
                }
                D_8010E59C_log_jam = 0;
                D_8010E5A4_log_jam++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_8010E59C_log_jam = 0;
                D_8010E5A4_log_jam++;
            }
            break;
        case 6:
            if (D_8010E59C_log_jam >= 16) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                func_8004AB0C_main(16);
                D_8010E59C_log_jam = 0;
                D_8010E5A4_log_jam++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = func_801060C4_log_jam;
            }
            break;
    }
    func_801060E8_log_jam(object);
    D_8010E598_log_jam++;
    D_8010E59C_log_jam++;
}

void func_801060C4_log_jam(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_801060E8_log_jam(omObjData *object) {
    if (D_8010DF90_log_jam != 0) {
        if (D_8010DF90_log_jam == 1) {
            object->func = func_801060C4_log_jam;
        }
        D_8010DF90_log_jam--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010DF90_log_jam = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, D_8010DF90_log_jam);
        HuAudSeqFadeOut(D_8010DF90_log_jam);
        func_8004AB0C_main((s16)D_8010DF90_log_jam);
    }
}

void func_80106190_log_jam(void) {
    s32 playerIds[2][2];
    LogJamTeam *team;
    LogJamLogWork *work;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 invalid;
    s32 group0Count;
    s32 group1Count;
    s32 group2Count;
    s32 group3Count;
    s32 group;

    D_8010E5AC_log_jam = HuMemAllocTag(sizeof(LogJamTeam) * 2, TAG_OVERLAY);
    team = D_8010E5AC_log_jam;
    memset(team, 0, sizeof(LogJamTeam) * 2);
    D_8010E5B8_log_jam = HuMemAllocTag(sizeof(LogJamLogWork) * 4, TAG_OVERLAY);
    memset(D_8010E5B8_log_jam, 0, sizeof(LogJamLogWork) * 4);
    invalid = FALSE;
    group3Count = 0;
    group2Count = 0;
    group1Count = 0;
    group0Count = 0;
    for (i = 0; i < 4; i++) {
        switch (group = GwPlayer[D_8010DF94_log_jam[i]].group) {
            case 0:
                if (group0Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[0][1] = D_8010DF94_log_jam[i];
                    group0Count++;
                }
                break;
            case 1:
                if (group1Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[0][0] = D_8010DF94_log_jam[i];
                    group1Count++;
                }
                break;
            case 2:
                if (group2Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[1][0] = D_8010DF94_log_jam[i];
                    group2Count++;
                }
                break;
            case 3:
                if (group3Count > 0) {
                    invalid = TRUE;
                } else {
                    playerIds[1][1] = D_8010DF94_log_jam[i];
                    group3Count++;
                }
                break;
            default:
                invalid = TRUE;
                break;
        }
        if (invalid) {
            break;
        }
    }
    if (invalid) {
        group = rand8() & 3;
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++) {
                playerIds[i][j] = D_8010DFA4_log_jam[group][i][j];
            }
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        team->unk_10 = i;
        team->unk_12 = 0;
        team->unk_14 = 0;
        team->unk_16 = -1;
        team->unk_18 = -1;
        team->unk_1A = 0;
        team->unk_1C = -1;
        team->unk_1E = 0;
        team->unk_20 = 0;
        team->unk_24 = team->unk_28 = team->unk_2C = 0.0f;
        team->unk_30 = team->unk_34 = team->unk_38 = 0.0f;
        team->unk_3C = 0.0f;
        team->unk_40 = team->unk_44 = 0.0f;
        D_8010E5B0_log_jam[i] = omAddObj(i + 16, 0, 0, -1, func_801065E8_log_jam);
        func_8010C55C_log_jam(D_8010E5B0_log_jam[i], (u32)team);
        for (j = 0; j < 2; j++) {
            work = &D_8010E5B8_log_jam[i * 2 + j];
            work->unk_00 = i * 2 + j;
            work->unk_04 = i;
            work->unk_02 = D_8010DFC4_log_jam[work->unk_00];
            work->unk_18 = playerIds[i][j];
            obj = D_800EC598_minigame[D_800EC280_minigame] =
                omAddObj(D_8010DFCC_log_jam[work->unk_00], 8, 11, -1, func_80106968_log_jam);
            D_800EC280_minigame++;
            obj->trans.x = D_8010DE90_log_jam[work->unk_00].x;
            obj->trans.z = D_8010DE90_log_jam[work->unk_00].z;
            obj->rot.y = D_8010DF20_log_jam[work->unk_00];
            func_8010C55C_log_jam(obj, (u32)work);
            if (work->unk_02 == 0) {
                team->unk_00 = obj;
                team->unk_08 = work;
            } else {
                team->unk_04 = obj;
                team->unk_0C = work;
            }
        }
    }
}

void func_801065E8_log_jam(omObjData *object) {
    Vec pos;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    LogJamTeam *team;
    LogJamPlayerWork *player;
    s16 done = FALSE;

    team = (LogJamTeam *)func_8010C588_log_jam(object);
    func_80107080_log_jam(team->unk_00, team);
    func_80107C84_log_jam(team->unk_04, team);
    if (team->unk_12 >= 30) {
        team->unk_12 = 29;
    }
    func_8010A6FC_log_jam(team->unk_10, team->unk_12);
    if (func_800E6E8C_minigame() == 3 && team->unk_16 != -1) {
        player = func_8010910C_log_jam(team->unk_16);
        pos.x = player->unk_10;
        pos.z = player->unk_18;
        pos.y = player->unk_14 + 40.0000005960464478;
        func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, D_8010DF4C_log_jam.rgba);
        func_8010925C_log_jam(team->unk_16);
        team->unk_16 = team->unk_18 = -1;
    }
    if (team->unk_1C != -1) {
        team->unk_30 += team->unk_40;
        team->unk_34 += team->unk_44;
        team->unk_28 += team->unk_3C;
        team->unk_3C -= 1.6333001f;
        team->unk_24 = func_8010C514_log_jam(D_8010DF30_log_jam[team->unk_10 ^ 1].x, team->unk_24, 7.0f);
        team->unk_2C = func_8010C514_log_jam(D_8010DF30_log_jam[team->unk_10 ^ 1].z, team->unk_2C, 7.0f);
        if (team->unk_28 < 184.0000033378601 && team->unk_3C <= 0.0f) {
            done = TRUE;
            team->unk_30 = -225.0f;
            team->unk_28 = 184.0f;
        }
        Hu3DModelPosSet(team->unk_1C, team->unk_24, team->unk_28, team->unk_2C);
        Hu3DModelRotSet(team->unk_1C, 0.0f, team->unk_34, 0.0f);
        if (team->unk_20 >= 0) {
            pos.x = team->unk_24;
            pos.z = team->unk_2C;
            pos.y = team->unk_28 - 50.0;
            func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, D_8010DF4C_log_jam.rgba);
            func_8001C258_main(team->unk_1C, 4, 4);
            done = TRUE;
        }
        func_8008A070_main(Hu3DData[team->unk_1C].mtx);
        mtxTransCat(Hu3DData[team->unk_1C].mtx, 0.0f, -50.0f, 0.0f);
        mtxRotCat(Hu3DData[team->unk_1C].mtx, team->unk_30, 0.0f, 0.0f);
        team->unk_20++;
        if (done) {
            team->unk_1C = -1;
        }
    }
    team->unk_1A++;
}

void func_80106968_log_jam(omObjData *object) {
    LogJamLogWork *work;
    func_800E1BA8_minigame_ObjData *data;
    s16 player;
    s16 chr;
    s32 model;
    s32 motion;
    s16 i;
    s32 index;

    work = (LogJamLogWork *)func_8010C588_log_jam(object);
    player = work->unk_18;
    chr = GwPlayer[player].chr;
    work->unk_1C = chr;
    work->unk_1A = GwPlayer[player].pad;
    work->unk_1E = GwPlayer[player].stat & 1;
    work->unk_20 = GwPlayer[player].cpu_difficulty;
    model = D_800A178C_main[chr][0];
    motion = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motion, player, 0x6A9, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = NULL;
    if (work->unk_02 == 1) {
        object->model[2] = func_8000B108_main(0x340000, 0xB9);
        func_8001C258_main(object->model[2], 0x4000, 0x4000);
        Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
        for (i = 0; i < 3; i++) {
            object->model[i + 3] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(object->model[i + 3], 4, 4);
            func_8001C258_main(object->model[i + 3], 0x4000, 0x4000);
            Hu3DModelHookSet(object->model[i + 3], object->model[2], "m219-item-f");
        }
    } else {
        for (i = 0; i < 3; i++) {
            object->model[i + 3] = func_80109A7C_log_jam(i, 0);
            func_8001C258_main(object->model[i + 3], 4, 4);
            func_8001C258_main(object->model[i + 3], 0x4000, 0x4000);
            Hu3DModelHookSet(object->model[i + 3], object->model[0], "item_hook");
        }
    }
    object->model[6] = func_8000B108_main(8, 0x68D);
    Hu3DModelScaleSet(object->model[6], 0.5f, 0.5f, 0.5f);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 6), 1, 27);
    if (work->unk_02 == 1) {
        func_800E5A00_minigame(object, 3, func_80017BB8_main(chr, 0x74), 0, 20);
        func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x75), 0, 10);
        func_800E5A00_minigame(object, 5, func_80017BB8_main(chr, 0x81), 0, 8);
        func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 0x76), 1, 0);
    } else {
        func_800E5A00_minigame(object, 7, func_80017BB8_main(chr, 0x77), 0, 30);
        func_800E5A00_minigame(object, 8, func_80017BB8_main(chr, 0x78), 0, 40);
    }
    if (chr == 5) {
        func_800E5A00_minigame(object, 9, func_80017BB8_main(5, 0x31), 1, 120);
        work->unk_14 = D_8010DFD4_log_jam[5] | 0x31;
    } else if (chr == 1 || chr == 6) {
        func_800E5A00_minigame(object, 9, func_80017BB8_main(chr, D_8010DFF4_log_jam[0]), 1, 120);
        work->unk_14 = D_8010DFD4_log_jam[chr] | D_8010DFF4_log_jam[0];
    } else {
        index = rand8() & 1;
        func_800E5A00_minigame(object, 9, func_80017BB8_main(chr, D_8010DFF4_log_jam[index]), 1, 120);
        work->unk_14 = D_8010DFD4_log_jam[chr] | D_8010DFF4_log_jam[index];
    }
    func_800E5A00_minigame(object, 10, func_80017BB8_main(chr, D_8010DFF4_log_jam[2]), 1, 120);
    work->unk_06 = -1;
    work->unk_0C = 0;
    work->unk_0A = 0;
    work->unk_22 = -1;
    work->unk_24 = -1;
    work->unk_26 = -1;
    work->unk_10 = 0.0f;
    work->unk_0E = 0;
    work->unk_28 = 0;
    work->unk_2A = 10;
    work->unk_2C = 0;
    work->unk_2E = 0;
    work->unk_30 = 4 - work->unk_20;
    if (work->unk_02 == 0) {
        work->unk_08 = 0;
        func_8010C5DC_log_jam(object, 0, 5);
        work->unk_32 = 0;
    } else {
        work->unk_08 = 5;
        func_8010C714_log_jam(object, 4, 7);
        work->unk_32 = 4;
    }
    work->unk_34 = 0;
    object->func = func_80106F48_log_jam;
}

void func_80106F48_log_jam(omObjData *object) {
    LogJamLogWork *work = (LogJamLogWork *)func_8010C588_log_jam(object);

    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    work->unk_0C++;
    func_8010C7F8_log_jam(object);
    func_8010C8B0_log_jam(object);
}

void func_80106FAC_log_jam(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            if (D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] != -1) {
                Hu3DModelKill(D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]]);
                D_800EC598_minigame[i]->model[D_8010E004_log_jam[j]] = -1;
            }
        }
    }
}

void func_80107080_log_jam(omObjData *object, LogJamTeam *team) {
    HuMtx4F mtx;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    Vec pos;
    LogJamLogWork *work;
    LogJamLogWork *partner;
    HmfModel *model;
    s32 dir;
    f32 t = 0.0f;

    work = (LogJamLogWork *)func_8010C588_log_jam(object);
    model = &Hu3DData[object->model[0]];
    partner = team->unk_0C;
    if (work->unk_1E != 0) {
        func_80108840_log_jam(object, team);
    }
    if (func_800E6E8C_minigame() == 3 && work->unk_08 < 13) {
        work->unk_08 = 13;
        work->unk_0C = 0;
    }
    if (!(work->unk_08 == 1 && work->unk_0A == 0) && work->unk_08 < 13) {
        object->rot.y = func_8010C2DC_log_jam(D_8010DF20_log_jam[work->unk_00], object->rot.y, 10.0f);
    }
    switch (work->unk_08) {
        case 0:
            if (work->unk_0C >= 3.0f && func_800E6E8C_minigame() == 2) {
                func_8010C5DC_log_jam(object, 7, 5);
                func_8004AC98_main(0x38A, work->unk_18);
                work->unk_08 = 1;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 1:
            if (work->unk_0A == 0) {
                t = work->unk_0C / 14.0f;
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->rot.y = func_8010C4B4_log_jam(D_8010DF20_log_jam[work->unk_00], 0.0f, t);
                if (model->motIdShift == 0xFF && model->motTime >= 14.0f && model->motId == object->motion[7]) {
                    work->unk_24 = (u8)(rand8() % 3);
                    func_8001C258_main(object->model[work->unk_24 + 3], 4, 0);
                    work->unk_0A++;
                    work->unk_0C = 0;
                }
            } else {
                if (model->motIdShift == 0xFF && model->motTime >= 29.0f && model->motId == object->motion[7]) {
                    work->unk_08 = 2;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 2:
            if ((D_800D5558_main[work->unk_1A] & 0xE000) && team->unk_16 == -1 && partner->unk_22 == -1 &&
                (partner->unk_08 == 6 || partner->unk_08 == 7)) {
                switch (D_800D5558_main[work->unk_1A]) {
                    case 0x8000:
                        dir = 0;
                        break;
                    case 0x4000:
                        dir = 1;
                        break;
                    case 0x2000:
                        dir = 2;
                        break;
                    default:
                        dir = 3;
                        break;
                }
                if (dir == work->unk_24) {
                    func_8010C5DC_log_jam(object, 8, 5);
                    work->unk_08 = 3;
                } else {
                    func_8010C714_log_jam(object, 8, 0);
                    model->motTime = 0.0f;
                    model->motSpeed = 0.0f;
                    omVibrate(work->unk_18, 2, 3, 10);
                    work->unk_08 = 4;
                }
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 4:
            if (work->unk_0A == 0) {
                model->motTime += 2.0f;
                if (model->motTime >= 10.0f) {
                    pos.x = object->trans.x;
                    pos.y = object->trans.y + D_8010E010_log_jam[work->unk_1C];
                    pos.z = object->trans.z;
                    func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
                    work->unk_0A++;
                }
            } else if (!(work->unk_0A & 1)) {
                model->motTime += 2.0f;
                if (model->motTime >= 6.0f) {
                    work->unk_0A++;
                }
            } else {
                model->motTime -= 2.0f;
                if (model->motTime <= 0.0f) {
                    if (work->unk_0A == 1 || work->unk_0A == 5 || work->unk_0A == 9) {
                        pos.x = object->trans.x;
                        pos.y = object->trans.y + D_8010E010_log_jam[work->unk_1C];
                        pos.z = object->trans.z;
                        func_8010AE58_log_jam(&pos, NULL, NULL, 1.0f, NULL);
                    }
                    work->unk_0A++;
                }
            }
            if (work->unk_0A >= 9) {
                func_8010C7D0_log_jam(object);
                model->motTime = 0.0f;
                work->unk_08 = 2;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 3:
            if (work->unk_0A == 0) {
                if (model->motIdShift == 0xFF && model->motId == object->motion[8]) {
                    t = model->motTime / 20.0f;
                }
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->trans.x =
                    func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].x, D_8010DEC0_log_jam[work->unk_00].x);
                object->trans.z =
                    func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].z, D_8010DEC0_log_jam[work->unk_00].z);
                if (model->motIdShift == 0xFF && model->motTime >= 19.0f && model->motId == object->motion[8]) {
                    func_8001C258_main(object->model[work->unk_24 + 3], 4, 4);
                    work->unk_22 = func_80109044_log_jam(work->unk_24, 0);
                    func_80109140_log_jam(work->unk_22, D_8010DF30_log_jam[team->unk_10].x,
                                          D_8010DF30_log_jam[team->unk_10].y, D_8010DF30_log_jam[team->unk_10].z);
                    func_80109190_log_jam(work->unk_22, 0.0f, 0.0f, 0.0f);
                    team->unk_16 = work->unk_22;
                    team->unk_18 = work->unk_24;
                    team->unk_1A = 0;
                    work->unk_22 = work->unk_24 = -1;
                    omVibrate(work->unk_18, 10, 0, 10);
                    work->unk_0A++;
                    work->unk_0C = 0;
                }
            } else {
                if (model->motIdShift == 0xFF && model->motId == object->motion[8]) {
                    t = (model->motTime - 19.0f) / 20.0f;
                }
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                object->trans.x =
                    func_8010C49C_log_jam(t, D_8010DEC0_log_jam[work->unk_00].x, D_8010DE90_log_jam[work->unk_00].x);
                object->trans.z =
                    func_8010C49C_log_jam(t, D_8010DEC0_log_jam[work->unk_00].z, D_8010DE90_log_jam[work->unk_00].z);
                if (model->motIdShift == 0xFF && model->motTime >= 39.0f && model->motId == object->motion[8]) {
                    func_8010C5DC_log_jam(object, 0, 5);
                    work->unk_08 = 0;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 13:
            if (work->unk_24 != -1) {
                func_8001C258_main(object->model[work->unk_24 + 3], 4, 4);
                func_8010CAC0_log_jam(object, "item_hook", mtx);
                func_8010A9D4_log_jam((Vec *)mtx[3], NULL, &scale, 1.0f, D_8010DF4C_log_jam.rgba);
                work->unk_22 = work->unk_24 = -1;
            }
            func_8010C5DC_log_jam(object, 0, 5);
            work->unk_08 = 14;
            // fallthrough
        case 14:
            object->rot.y = func_8010C2DC_log_jam(0.0f, object->rot.y, 10.0f);
            object->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[work->unk_00].x, object->trans.x, 10.0f);
            object->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[work->unk_00].z, object->trans.z, 10.0f);
            if (func_800E6E8C_minigame() == 4) {
                func_8010C5DC_log_jam(object, 1, 5);
                work->unk_10 = 32.0f;
                work->unk_0E = func_80108D1C_log_jam(32.0f, 1.6333001f);
                work->unk_08 = 15;
                work->unk_0C = 0;
            }
            break;
        case 15:
            t = (f32)work->unk_0C / work->unk_0E;
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            if (work->unk_0C == 6) {
                func_8010C5DC_log_jam(object, 2, 6);
            } else if (work->unk_0C == work->unk_0E - 10) {
                func_8010C5DC_log_jam(object, 1, 7);
            }
            object->trans.x =
                func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].x, D_8010DEF0_log_jam[work->unk_00].x);
            object->trans.z =
                func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].z, D_8010DEF0_log_jam[work->unk_00].z);
            object->trans.y += work->unk_10;
            work->unk_10 -= 1.6333001f;
            if (object->trans.y <= 0.0f) {
                func_8010C5DC_log_jam(object, 0, 5);
                object->trans.y = 0.0f;
                work->unk_08 = 16;
                work->unk_0C = 0;
            }
            break;
        case 16:
            work->unk_08 = 17;
            work->unk_0C = 0;
            break;
        case 17:
            if (work->unk_06 != -1) {
                switch (work->unk_06) {
                    case 0:
                        func_8010C5DC_log_jam(object, 9, 5);
                        func_80017790_main(object->model[0], 2, work->unk_1C, D_8010DF50_log_jam[work->unk_1C]);
                        func_80045F1C_main(work->unk_14, -1, work->unk_18);
                        break;
                    case 1:
                        func_8010C5DC_log_jam(object, 10, 5);
                        func_80017790_main(object->model[0], 2, work->unk_1C, D_8010DF70_log_jam[work->unk_1C]);
                        break;
                }
                work->unk_06 = -1;
            }
            break;
    }
}

void func_80107C84_log_jam(omObjData *object, LogJamTeam *team) {
    HuMtx4F mtx;
    Vec scale = { 0.7f, 0.7f, 0.7f };
    LogJamLogWork *work;
    LogJamLogWork *partner;
    HmfModel *model;
    s32 dir;
    f32 time;
    f32 t;

    work = (LogJamLogWork *)func_8010C588_log_jam(object);
    model = &Hu3DData[object->model[0]];
    partner = team->unk_08;
    if (work->unk_1E != 0) {
        func_80108A80_log_jam(object, team);
    }
    if (func_800E6E8C_minigame() == 3 && work->unk_08 < 13) {
        work->unk_08 = 13;
        work->unk_0C = 0;
    }
    switch (work->unk_08) {
        case 5:
            if (func_800E6E8C_minigame() == 2) {
                func_8010C5DC_log_jam(object, 3, 7);
                work->unk_08 = 6;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 6:
            if (model->motIdShift == 0xFF && model->motTime >= 19.0f && model->motId == object->motion[3]) {
                work->unk_08 = 7;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 7:
            if ((D_800D5558_main[work->unk_1A] & 0xE000) && !(partner->unk_08 == 3 && partner->unk_0A == 0)) {
                if (D_800D5558_main[work->unk_1A] == 0x8000) {
                    work->unk_26 = 0;
                } else if (D_800D5558_main[work->unk_1A] == 0x4000) {
                    work->unk_26 = 1;
                } else if (D_800D5558_main[work->unk_1A] == 0x2000) {
                    work->unk_26 = 2;
                } else {
                    work->unk_26 = 3;
                }
                if (work->unk_22 == 0x20) {
                    dir = work->unk_24;
                } else {
                    dir = team->unk_18;
                }
                func_8004AC98_main(0x38D, work->unk_18);
                if (dir == -1 || dir == work->unk_26) {
                    func_8010C5DC_log_jam(object, 4, 2);
                    work->unk_08 = 8;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                } else {
                    func_8010C5DC_log_jam(object, 5, 2);
                    work->unk_08 = 9;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                }
            }
            break;
        case 8:
            if (work->unk_22 == 0x20) {
                dir = work->unk_24;
            } else {
                dir = team->unk_18;
            }
            time = 9.0f;
            if (model->motIdShift == 0xFF && model->motTime >= time && model->motId == object->motion[4]) {
                if (dir == -1) {
                    func_8004AC98_main(0x38C, work->unk_18);
                    work->unk_08 = 12;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                    func_8010C5DC_log_jam(object, 6, 5);
                    func_800E4C88_minigame(object, 6, D_8010DF30_log_jam[team->unk_10].x,
                                           D_8010DF30_log_jam[team->unk_10].y, D_8010DF30_log_jam[team->unk_10].z, 0.0f,
                                           0.0f);
                } else {
                    func_8004AC98_main(0x38B, work->unk_18);
                    omVibrate(work->unk_18, 10, 0, 10);
                    work->unk_08 = 10;
                    work->unk_0A = 0;
                    work->unk_0C = 0;
                    if (team->unk_16 != -1) {
                        work->unk_22 = team->unk_16;
                        team->unk_16 = team->unk_18 = -1;
                        team->unk_1A = 0;
                    } else {
                        func_8001C258_main(object->model[work->unk_24 + 3], 4, 4);
                        work->unk_24 = work->unk_22 = -1;
                        work->unk_22 = func_80109044_log_jam(dir, 0);
                        func_80109140_log_jam(work->unk_22, D_8010DF30_log_jam[team->unk_10].x,
                                              D_8010DF30_log_jam[team->unk_10].y, D_8010DF30_log_jam[team->unk_10].z);
                        func_80109190_log_jam(work->unk_22, 0.0f, 0.0f, 0.0f);
                    }
                    if (work->unk_22 != -1) {
                        func_80109350_log_jam(work->unk_22);
                        work->unk_22 = work->unk_24 = -1;
                    }
                    if (func_800E6E8C_minigame() == 2) {
                        team->unk_12++;
                    }
                }
            }
            break;
        case 9:
            if (model->motIdShift == 0xFF && model->motTime >= 8.0f && model->motId == object->motion[5]) {
                func_8004AC98_main(0x38C, work->unk_18);
                work->unk_08 = 11;
                work->unk_0A = 0;
                work->unk_0C = 0;
                if (team->unk_16 != -1) {
                    work->unk_22 = 0x20;
                    work->unk_24 = team->unk_18;
                    func_8001C258_main(object->model[work->unk_24 + 3], 4, 0);
                    func_8010925C_log_jam(team->unk_16);
                    team->unk_16 = team->unk_18 = -1;
                    team->unk_1A = 0;
                    func_800E4C88_minigame(object, 6, D_8010DF30_log_jam[team->unk_10].x,
                                           D_8010DF30_log_jam[team->unk_10].y + 50.0,
                                           D_8010DF30_log_jam[team->unk_10].z, 0.0f, 0.0f);
                } else {
                    func_800E4C88_minigame(object, 6, D_8010DF30_log_jam[team->unk_10].x,
                                           D_8010DF30_log_jam[team->unk_10].y, D_8010DF30_log_jam[team->unk_10].z, 0.0f,
                                           0.0f);
                }
                omVibrate(work->unk_18, 2, 2, 20);
                func_8010C7D0_log_jam(object);
            }
            break;
        case 10:
            if (work->unk_0C >= 9.0f) {
                work->unk_08 = 5;
                work->unk_0A = 0;
                work->unk_0C = 0;
                func_8010C5DC_log_jam(object, 3, 5);
            }
            break;
        case 11:
            if (work->unk_0C >= 15.0f) {
                work->unk_08 = 6;
                work->unk_0A = 0;
                work->unk_0C = 0;
                func_8010C6A4_log_jam(object, 3, 12);
            }
            break;
        case 12:
            if (work->unk_0C >= 90.0f) {
                func_8010C5DC_log_jam(object, 3, 7);
                work->unk_08 = 5;
                work->unk_0A = 0;
                work->unk_0C = 0;
            }
            break;
        case 13:
            func_8010CAC0_log_jam(object, "item_hook", mtx);
            team->unk_1C = object->model[2];
            if (team->unk_1C != -1) {
                func_8008A070_main(Hu3DData[team->unk_1C].mtx);
                mtxTransCat(Hu3DData[team->unk_1C].mtx, 0.0f, -50.0f, 0.0f);
                func_8001C258_main(team->unk_1C, 0x4000, 0);
                team->unk_20 = 0;
                team->unk_24 = mtx[3][0];
                team->unk_2C = mtx[3][2];
                team->unk_28 = mtx[3][1] + 50.0;
                team->unk_3C = 30.000002f;
                team->unk_40 = (u8)(rand8() % 10) + 40;
                team->unk_44 = 3 - (u8)(rand8() % 6);
            }
            if (work->unk_24 != -1) {
                func_8001C258_main(object->model[work->unk_24 + 3], 4, 4);
                func_8010A9D4_log_jam((Vec *)mtx[3], NULL, &scale, 1.0f, D_8010DF4C_log_jam.rgba);
                work->unk_22 = work->unk_24 = -1;
            }
            func_8010C5DC_log_jam(object, 0, 5);
            work->unk_08 = 14;
            // fallthrough
        case 14:
            object->rot.y = func_8010C2DC_log_jam(0.0f, object->rot.y, 10.0f);
            object->trans.x = func_8010C514_log_jam(D_8010DE90_log_jam[work->unk_00].x, object->trans.x, 10.0f);
            object->trans.z = func_8010C514_log_jam(D_8010DE90_log_jam[work->unk_00].z, object->trans.z, 10.0f);
            if (func_800E6E8C_minigame() == 4) {
                func_8010C5DC_log_jam(object, 1, 5);
                work->unk_10 = 25.0f;
                work->unk_0E = func_80108D1C_log_jam(25.0f, 1.6333001f);
                work->unk_08 = 15;
                work->unk_0C = 0;
            }
            break;
        case 15:
            t = (f32)work->unk_0C / work->unk_0E;
            if (t > 1.0f) {
                t = 1.0f;
            } else if (t < 0.0f) {
                t = 0.0f;
            }
            if (work->unk_0C == 6) {
                func_8010C5DC_log_jam(object, 2, 6);
            } else if (work->unk_0C == work->unk_0E - 6) {
                func_8010C5DC_log_jam(object, 1, 6);
            }
            object->trans.x =
                func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].x, D_8010DEF0_log_jam[work->unk_00].x);
            object->trans.z =
                func_8010C49C_log_jam(t, D_8010DE90_log_jam[work->unk_00].z, D_8010DEF0_log_jam[work->unk_00].z);
            object->trans.y += work->unk_10;
            work->unk_10 -= 1.6333001f;
            if (object->trans.y <= 0.0f) {
                func_8010C5DC_log_jam(object, 0, 5);
                object->trans.y = 0.0f;
                work->unk_08 = 16;
                work->unk_0C = 0;
            }
            break;
        case 16:
            work->unk_08 = 17;
            work->unk_0C = 0;
            break;
        case 17:
            if (work->unk_06 != -1) {
                switch (work->unk_06) {
                    case 0:
                        func_8010C5DC_log_jam(object, 9, 5);
                        func_80017790_main(object->model[0], 2, work->unk_1C, D_8010DF50_log_jam[work->unk_1C]);
                        func_80045F1C_main(work->unk_14, -1, work->unk_18);
                        break;
                    case 1:
                        func_8010C5DC_log_jam(object, 10, 5);
                        func_80017790_main(object->model[0], 2, work->unk_1C, D_8010DF70_log_jam[work->unk_1C]);
                        break;
                }
                work->unk_06 = -1;
            }
            break;
    }
}

void func_80108840_log_jam(omObjData *object, LogJamTeam *team) {
    LogJamLogWork *work = (LogJamLogWork *)func_8010C588_log_jam(object);
    LogJamLogWork *partner = team->unk_0C;

    D_800D5558_main[work->unk_1A] = 0;
    switch (work->unk_08) {
        case 1:
        case 3:
        case 4:
            work->unk_2C = 0;
            break;
        case 2:
            if (work->unk_2C != 0) {
                D_800D5558_main[work->unk_1A] |= work->unk_2C;
            } else if (work->unk_28 > work->unk_2A) {
                if ((u8)(rand8() % 100) < work->unk_20 * 13 + 50 || work->unk_2E >= work->unk_30 ||
                    partner->unk_1E == 0) {
                    switch (work->unk_24) {
                        case 0:
                            work->unk_2C |= 0x8000;
                            break;
                        case 1:
                            work->unk_2C |= 0x4000;
                            break;
                        default:
                            work->unk_2C |= 0x2000;
                            break;
                    }
                    work->unk_2E = 0;
                } else {
                    switch (work->unk_24) {
                        case 0:
                            work->unk_2C |= 0x2000;
                            break;
                        case 1:
                            work->unk_2C |= 0x8000;
                            break;
                        default:
                            work->unk_2C |= 0x4000;
                            break;
                    }
                    work->unk_2E++;
                }
                work->unk_28 = 0;
                work->unk_2A = (u8)(rand8() % 3) + (6 - work->unk_20 * 2) * 2;
            }
            break;
    }
    work->unk_28++;
}

void func_80108A80_log_jam(omObjData *object, LogJamTeam *team) {
    LogJamLogWork *work = (LogJamLogWork *)func_8010C588_log_jam(object);
    LogJamLogWork *partner = team->unk_08;
    s16 dir;

    D_800D5558_main[work->unk_1A] = 0;
    if (team->unk_16 != -1) {
        dir = team->unk_18;
    } else {
        dir = work->unk_24;
    }
    switch (work->unk_08) {
        case 7:
            if (work->unk_2C & 0xE000) {
                D_800D5558_main[work->unk_1A] |= work->unk_2C;
            } else if (work->unk_28 > work->unk_2A && dir != -1) {
                if ((u8)(rand8() % 100) < work->unk_20 * 13 + 50 || work->unk_2E >= work->unk_30 ||
                    partner->unk_1E == 0) {
                    switch (dir) {
                        case 0:
                            work->unk_2C |= 0x8000;
                            break;
                        case 1:
                            work->unk_2C |= 0x4000;
                            break;
                        default:
                            work->unk_2C |= 0x2000;
                            break;
                    }
                    work->unk_2E = 0;
                } else {
                    switch (dir) {
                        case 0:
                            work->unk_2C |= 0x2000;
                            break;
                        case 1:
                            work->unk_2C |= 0x8000;
                            break;
                        default:
                            work->unk_2C |= 0x4000;
                            break;
                    }
                    work->unk_2E++;
                }
                work->unk_28 = 0;
                work->unk_2A = (u8)(rand8() % 10) + 16 - work->unk_20 * 2;
            }
            break;
        case 8:
        case 9:
            work->unk_2C = 0;
            break;
    }
    work->unk_28++;
}

s16 func_80108CE0_log_jam(s16 arg0) {
    s32 i = 0;
    LogJamLogWork *work = D_8010E5B8_log_jam;

    do {
        if (work->unk_08 != arg0) {
            return 0;
        }
        work++;
    } while (++i < 4);

    return 1;
}

s16 func_80108D1C_log_jam(f32 arg0, f32 arg1) {
    f32 total = 0.0f;
    s16 frames = 0;
    f32 speed = arg0;

    do {
        total += speed;
        speed -= arg1;
        frames++;
    } while (0.0f < total);

    return frames;
}

void func_80108D50_log_jam(void) {
    s32 i;
    LogJamPlayerWork *work;

    D_8010E5C4_log_jam = HuMemAllocTag(0xF00, TAG_OVERLAY);
    work = D_8010E5C4_log_jam;
    for (i = 0; i < 0x20; i++) {
        work->unk_00 = i;
        work->unk_02[0] = -1;
        work->unk_02[1] = -1;
        work->unk_02[2] = -1;
        work->unk_08 = 0;
        work->unk_0A = 0;
        work->unk_0C = 0;
        work->unk_0E = 0;
        work->unk_10 = work->unk_14 = work->unk_18 = 0.0f;
        work->unk_1C = work->unk_20 = work->unk_24 = 0.0f;
        work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
        memset(&work->unk_34, 0, 0x20);
        memset(&work->unk_54, 0, 0x20);
        work->unk_74 = NULL;
        work++;
    }
    D_8010E5C0_log_jam = omAddObj(0x18, 0, 0, -1, func_80108E54_log_jam);
    omSetStatBit(D_8010E5C0_log_jam, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_80108E54_log_jam(omObjData *object) {
    LogJamPlayerWork *work;
    s32 i;
    s32 j;

    for (i = 0, work = D_8010E5C4_log_jam; i < 0x20; i++, work++) {
        if (work->unk_08 == 0) {
            continue;
        }
        switch (work->unk_0C) {
            case 0:
                break;
            case 1:
                if ((work->unk_0E & 1) || omPauseChk() + D_800D6A90_main != 0) {
                    for (j = 0; j < 3; j++) {
                        if (work->unk_02[j] != -1) {
                            func_8001C258_main(work->unk_02[j], 4, 0);
                        }
                    }
                } else {
                    for (j = 0; j < 3; j++) {
                        if (work->unk_02[j] != -1) {
                            func_8001C258_main(work->unk_02[j], 4, 4);
                        }
                    }
                }
                if (work->unk_0E >= 30.0f) {
                    work->unk_0E = 0;
                    work->unk_0C++;
                }
                break;
            default:
                func_8010925C_log_jam(work->unk_00);
                continue;
        }
        if (work->unk_74 != NULL && omPauseChk() + D_800D6A90_main == 0) {
            work->unk_74(work);
        }
        if (work->unk_08 == 0) {
            continue;
        }
        if (work->unk_02[0] != -1) {
            Hu3DModelPosSet(work->unk_02[0], work->unk_10, work->unk_14, work->unk_18);
            Hu3DModelRotSet(work->unk_02[0], work->unk_1C, work->unk_20, work->unk_24);
        }
        if (omPauseChk() + D_800D6A90_main == 0) {
            work->unk_0E++;
        }
    }
}

s16 func_80109044_log_jam(s16 arg0, s16 arg1) {
    s32 i;
    LogJamPlayerWork *work;

    if (D_8010E5C4_log_jam == NULL) {
        return -1;
    }
    for (i = 0, work = D_8010E5C4_log_jam; i < 0x20; i++, work++) {
        if (work->unk_08 == 0) {
            work->unk_02[0] = func_80109A7C_log_jam(arg0, arg1);
            if (work->unk_02[0] != -1) {
                func_8001C258_main(work->unk_02[0], 4, 0);
            }
            work->unk_08 = 1;
            work->unk_0A = arg0;
            work->unk_0C = 0;
            work->unk_0E = 0;
            return i;
        }
    }
    return -1;
}

LogJamPlayerWork *func_8010910C_log_jam(s16 arg0) {
    if (D_8010E5C4_log_jam == NULL) {
        return NULL;
    }

    return &D_8010E5C4_log_jam[arg0];
}

void func_80109140_log_jam(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (D_8010E5C4_log_jam != NULL) {
        LogJamPlayerWork *work = &D_8010E5C4_log_jam[arg0];

        if (work->unk_08 != 0) {
            work->unk_10 = arg1;
            work->unk_14 = arg2;
            work->unk_18 = arg3;
        }
    }
}

void func_80109190_log_jam(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (D_8010E5C4_log_jam != NULL) {
        LogJamPlayerWork *work = &D_8010E5C4_log_jam[arg0];

        if (work->unk_08 != 0) {
            work->unk_1C = arg1;
            work->unk_20 = arg2;
            work->unk_24 = arg1;
        }
    }
}

void func_801091DC_log_jam(void) {
    s32 i;
    LogJamPlayerWork *work;

    if (D_8010E5C4_log_jam != NULL) {
        for (i = 0, work = D_8010E5C4_log_jam; i < 0x20; i++, work++) {
            if (work->unk_08 != 0) {
                func_8010925C_log_jam(i);
            }
        }
        HuMemFree(D_8010E5C4_log_jam);
        D_8010E5C4_log_jam = NULL;
        D_8010E5C0_log_jam->func = NULL;
    }
}

void func_8010925C_log_jam(s16 arg0) {
    s32 i;
    LogJamPlayerWork *work;

    if (D_8010E5C4_log_jam != NULL) {
        work = &D_8010E5C4_log_jam[arg0];
        if (work->unk_08 != 0) {
            for (i = 0; i < 3; i++) {
                if (work->unk_02[i] != -1) {
                    Hu3DModelKill(work->unk_02[i]);
                    work->unk_02[i] = -1;
                }
            }
            work->unk_08 = 0;
            work->unk_0A = work->unk_0C = work->unk_0E = 0;
            work->unk_10 = work->unk_14 = work->unk_18 = 0.0f;
            work->unk_1C = work->unk_20 = work->unk_24 = 0.0f;
            work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
            memset(&work->unk_34, 0, 0x20);
            memset(&work->unk_54, 0, 0x20);
            work->unk_74 = NULL;
        }
    }
}

void func_80109350_log_jam(s16 arg0) {
    Vec pos = { 0.0f, 0.0f, 0.0f };
    Vec scale = { 0.5f, 0.5f, 0.5f };
    LogJamPlayerWork *work;
    f32 x;
    f32 y;
    f32 z;
    s32 type;
    s32 i;
    s16 id;

    if (D_8010E5C4_log_jam == NULL) {
        return;
    }
    work = &D_8010E5C4_log_jam[arg0];
    if (work->unk_08 == 0) {
        return;
    }
    type = work->unk_0A;
    x = work->unk_10;
    y = work->unk_14;
    z = work->unk_18;
    pos.x = work->unk_10;
    pos.y = work->unk_14;
    pos.z = work->unk_18;
    func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, D_8010DF48_log_jam.rgba);
    func_8010925C_log_jam(arg0);
    for (i = 0; i < 2; i++) {
        id = func_80109044_log_jam(type, i + 1);
        if (id != -1) {
            work = &D_8010E5C4_log_jam[id];
            work->unk_10 = x;
            work->unk_14 = y;
            work->unk_18 = z;
            work->unk_34[0] = i;
            work->unk_52 = 0;
            work->unk_74 = func_801094E4_log_jam;
            work->unk_74(work);
        }
    }
}

void func_801094E4_log_jam(LogJamPlayerWork *work) {
    Vec pos = { 0.0f, 0.0f, 0.0f };
    Vec scale = { 0.5f, 0.5f, 0.5f };
    f32 amplitude;

    switch (work->unk_52) {
        case 0:
            if (work->unk_34[0] == 0) {
                work->unk_28 = ((f32)(u8)(rand8() % 100) * 0.01 * 0.02 + 0.03f) * 100.0;
                work->unk_54[0] = -((f32)(u8)(rand8() % 100) * 0.01 * 0.75 + 4.0);
                work->unk_54[5] = -90.0f;
            } else {
                work->unk_28 = -(((f32)(u8)(rand8() % 100) * 0.01 * 0.02 + 0.03f) * 100.0);
                work->unk_54[0] = (f32)(u8)(rand8() % 100) * 0.01 * 0.75 + 4.0;
                work->unk_54[5] = 90.0f;
            }
            work->unk_2C = (f32)(u8)(rand8() % 100) * 0.01 * 2.0 + 10.999999940395355;
            work->unk_30 = (f32)(u8)(rand8() % 100) * 0.01 * 1.2500000186264515 + 0.6250000093132257;
            work->unk_52++;
            break;
        case 1:
            work->unk_24 += work->unk_54[0];
            work->unk_2C -= 1.6333001f;
            if (work->unk_14 <= 0.0f) {
                work->unk_14 = 0.0f;
                work->unk_28 = work->unk_2C = work->unk_30 = 0.0f;
                work->unk_54[1] = 20.0f;
                work->unk_54[2] = 1.0f;
                work->unk_54[3] = 0.0f;
                work->unk_54[4] = 55.0f;
                work->unk_52++;
                pos.x = work->unk_10;
                pos.y = work->unk_14;
                pos.z = work->unk_18;
                func_8010A9D4_log_jam(&pos, NULL, &scale, 1.0f, D_8010DF48_log_jam.rgba);
            }
            break;
        case 2:
            work->unk_54[3] += work->unk_54[4];
            if (work->unk_54[3] >= 360.0f) {
                work->unk_54[3] -= 360.0f;
            }
            amplitude = work->unk_54[1] - work->unk_54[2];
            if (amplitude > 0.0f) {
                work->unk_54[1] = amplitude;
            } else {
                work->unk_54[1] = 0.0f;
            }
            work->unk_24 = sindf(work->unk_54[3]) * work->unk_54[1] + work->unk_54[5];
            if (work->unk_0C == 0) {
                work->unk_0C = 1;
            }
            break;
    }
    work->unk_10 += work->unk_28;
    work->unk_14 += work->unk_2C;
    work->unk_18 += work->unk_30;
}

void func_80109A00_log_jam(void) {
    s32 i;

    D_8010E5C8_log_jam = HuMemAllocTag(0x12, TAG_OVERLAY);

    for (i = 0; i < 9; i++) {
        D_8010E5C8_log_jam[i] = func_8000B108_main(D_8010E030_log_jam[i], 0xBD);
    }
}

s16 func_80109A7C_log_jam(s16 arg0, s16 arg1) {
    if (D_8010E5C8_log_jam == NULL) {
        return -1;
    }

    return Hu3DModelLink(D_8010E5C8_log_jam[arg0 * 3 + arg1]);
}

void func_80109AD8_log_jam(void) {
    s32 i;

    for (i = 0; i < 9; i++) {
        Hu3DModelKill(D_8010E5C8_log_jam[i]);
    }
    HuMemFree(D_8010E5C8_log_jam);
    D_8010E5C8_log_jam = NULL;
}

// Appends a new object to the shared minigame object list.
void func_80109B34_log_jam(void) {
    omObjData *obj = omAddObj(1, 0x10, 0, -1, func_80109B8C_log_jam);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

void func_80109B8C_log_jam(omObjData *object) {
    s16 model;
    s16 group;
    LogJamCloud *cloud;
    s16 i;
    s16 j;

    model = object->model[1] = func_8000B108_main(0x340001, 0xA9);
    Hu3DModelPosSet(model, -100.0f, 0.0f, 115.0f);
    Hu3DModelPosSet(object->model[2] = Hu3DModelLink(model), 100.0f, 0.0f, 115.0f);
    model = object->model[3] = func_8000B108_main(0x340002, 0x89);
    Hu3DModelPosSet(model, -230.0f, 0.0f, 195.0f);
    Hu3DModelPosSet(object->model[4] = Hu3DModelLink(model), 230.0f, 0.0f, 195.0f);

    D_8010E5CC_log_jam[0] = func_8010A300_log_jam(0x34000C);
    group = HuSprGrpCreate(3, 0);
    HuSprGrpMemberSet(group, 0, D_8010E5CC_log_jam[0], 0);
    HuSprPosSet(group, 0, 160, 120);
    HuSprAnimModeSet(group, 0, 0);
    func_80054FF8_main(group, 0, 0);
    HuSprAttrSet(group, 0, 0x4000580C);
    HuSprPriSet(group, 0, 0xFF00);
    D_8010E5CC_log_jam[4] = func_8010A300_log_jam(0x340010);
    HuSprGrpMemberSet(group, 1, D_8010E5CC_log_jam[4], 0);
    HuSprPosSet(group, 1, 0, 40);
    HuSprAnimModeSet(group, 1, 0);
    func_80054FF8_main(group, 1, 0);
    HuSprAttrSet(group, 1, 0x4000580C);
    HuSprPriSet(group, 1, 0xFF01);
    HuSprTPLvlSet(group, 1, 200);
    D_8010E5CC_log_jam[1] = func_8010A300_log_jam(0x34000D);
    HuSprGrpMemberSet(group, 2, D_8010E5CC_log_jam[1], 0);
    HuSprPosSet(group, 2, 0, 0);
    HuSprAnimModeSet(group, 2, 0);
    func_80054FF8_main(group, 2, 0);
    HuSprAttrSet(group, 2, 0x403C);
    HuSprPriSet(group, 2, 0xFFFF);

    D_8010E5CC_log_jam[2] = func_8010A300_log_jam(0x34000E);
    D_8010E5CC_log_jam[5] = func_8010A300_log_jam(0x340011);
    D_8010E5D4_log_jam = HuMemAllocTag(sizeof(LogJamCloud) * 5, TAG_OVERLAY);
    cloud = D_8010E5D4_log_jam;
    for (i = 0; i < 5; i++, cloud++) {
        cloud->index = i;
        cloud->group = HuSprGrpCreate(2, 0);
        cloud->angle = rand8() % 360;
        cloud->base = D_8010E07C_log_jam[i];
        cloud->pos.x = D_8010E054_log_jam[i].x;
        cloud->pos.y = D_8010E054_log_jam[i].y;
        cloud->scale.x = cloud->scale.y = 1.0f;
        cloud->speed = -0.5f;
        cloud->unk_20 = 0;
        for (j = 0; j < 2; j++) {
            if (j == 0) {
                HuSprGrpMemberSet(cloud->group, 0, D_8010E5CC_log_jam[2], 0);
            } else {
                HuSprGrpMemberSet(cloud->group, j, D_8010E5CC_log_jam[5], 0);
                HuSprTPLvlSet(cloud->group, j, 190);
            }
            HuSprAnimModeSet(cloud->group, j, 0);
            func_80054FF8_main(cloud->group, j, 0);
            HuSprAttrSet(cloud->group, j, 0x2000583C);
            HuSprPosSet(cloud->group, j, cloud->pos.x, cloud->pos.y);
            HuSprScaleSet(cloud->group, j, cloud->scale.x, cloud->scale.y);
            HuSprPriSet(cloud->group, j, j + i * 2 - 241);
        }
    }
    object->func = func_8010A0B0_log_jam;
}

void func_8010A0B0_log_jam(omObjData *object) {
    LogJamCloud *cloud;
    HuSprite *sprite;
    f32 wobble;
    s16 i;

    for (i = 0, cloud = D_8010E5D4_log_jam; i < 5; i++, cloud++) {
        wobble = sindf(cloud->angle);
        cloud->pos.x += cloud->speed * ((f32)(u8)(rand8() % 100) * 0.01 * 0.4f + 0.6f);
        cloud->scale.x = cloud->base + 0.075f + wobble * 0.075f;
        cloud->scale.y = cloud->base + 0.075f - wobble * 0.075f;
        if (cloud->pos.x <= -64.0f) {
            cloud->pos.x += 416.0f;
        } else if (cloud->pos.x > 384.0f) {
            cloud->pos.x -= 320.0f;
        }
        HuSprScaleSet(cloud->group, 0, cloud->scale.x, cloud->scale.y);
        HuSprScaleSet(cloud->group, 1, cloud->scale.x, cloud->scale.y);
        sprite = HuSprGet(cloud->group, 0);
        sprite->pos.x = cloud->pos.x;
        sprite->pos.y = cloud->pos.y;
        sprite = HuSprGet(cloud->group, 1);
        sprite->pos.x = cloud->pos.x;
        sprite->pos.y = cloud->pos.y;
        cloud->angle += (u8)(rand8() % 7) + 2;
        if (cloud->angle >= 360) {
            cloud->angle -= 360;
        }
    }
}

u16 func_8010A300_log_jam(s32 file) {
    void *data = DataRead(file);
    u16 sprite = HuSprAnimRead(data);

    DataClose(data);
    return sprite;
}

void func_8010A344_log_jam(void) {
    UnkLogJamSprites *sprites;
    s32 i;
    s32 j;
    s32 x;

    D_8010E5CC_log_jam[3] = func_8010A300_log_jam(0x34000F);
    D_8010E5D0_log_jam = HuMemAllocTag(sizeof(UnkLogJamSprites) * 2, TAG_OVERLAY);
    sprites = D_8010E5D0_log_jam;
    for (i = 0; i < 2; i++, sprites++) {
        x = D_8010E090_log_jam[i];
        memset(sprites, 0, sizeof(UnkLogJamSprites));
        sprites->unk_00 = i;
        sprites->unk_02 = HuSprGrpCreate(10, 0);
        for (j = 0; j < 10; j++) {
            HuSprGrpMemberSet(sprites->unk_02, j, D_8010E5CC_log_jam[3], 0);
            HuSprAnimModeSet(sprites->unk_02, j, 0);
            func_80054FF8_main(sprites->unk_02, j, 0);
            HuSprTPLvlSet(sprites->unk_02, j, 0x100);
            HuSprAttrSet(sprites->unk_02, j, 0x9000);
            HuSprPosSet(sprites->unk_02, j, x, 28);
            if (i == 0) {
                x += 16;
            } else {
                x -= 16;
            }
        }
    }
    omAddObj(30, 0, 0, -1, func_8010A4C0_log_jam);
}

void func_8010A4C0_log_jam(omObjData *object) {
    UnkLogJamSprites *sprites;
    s32 i;
    s32 j;
    s32 fives;
    s32 count;
    f32 t;

    for (i = 0, sprites = D_8010E5D0_log_jam; i < 2; i++, sprites++) {
        fives = (s16)(sprites->unk_08 / 5);
        count = fives + (s16)(sprites->unk_08 % 5);
        if (sprites->unk_0A != sprites->unk_08) {
            for (j = 0; j < 10; j++) {
                HuSprTPLvlSet(sprites->unk_02, j, 0x100);
                HuSprScaleSet(sprites->unk_02, j, 1.0f, 1.0f);
            }
            sprites->unk_04 = 15;
            if (count != 0) {
                sprites->unk_06 = count - 1;
            }
        }
        if (sprites->unk_04 > 0) {
            if (sprites->unk_04 == 1) {
                t = 0.0f;
            } else {
                t = sprites->unk_04 / 15.0f;
            }
            HuSprTPLvlSet(sprites->unk_02, sprites->unk_06, (s32)((1.0f - t) * 256.0f));
            HuSprScaleSet(sprites->unk_02, sprites->unk_06, t + 1.0f, t + 1.0f);
            sprites->unk_04--;
        }
        for (j = 0; j < 10; j++) {
            if (j < fives) {
                func_80054FF8_main(sprites->unk_02, j, 1);
            } else {
                func_80054FF8_main(sprites->unk_02, j, 0);
            }
            if (j < count) {
                HuSprAttrReset(sprites->unk_02, j, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrSet(sprites->unk_02, j, HUSPR_ATTR_DISPOFF);
            }
        }
        sprites->unk_0A = sprites->unk_08;
    }
}

void func_8010A6FC_log_jam(s16 arg0, s16 arg1) {
    UnkLogJamSprites *sprites = &D_8010E5D0_log_jam[arg0];

    sprites->unk_08 = arg1;
}

void func_8010A724_log_jam(void) {
    HuSprAnimData *sprite;
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    D_8010E5CC_log_jam[6] = func_8010A300_log_jam(11);
    sprite = func_80055194_main(D_8010E5CC_log_jam[6]);
    D_8010E5D8_log_jam = omAddObj(30, 0, 0, -1, func_8010A880_log_jam);
    D_8010E5DC_log_jam = effect = HuMemAllocTag(sizeof(LogJamEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(sprite, D_8010DF48_log_jam.rgba);
        } else {
            effect->model = func_8010D74C_log_jam(sprite, D_8010E5DC_log_jam[0].model, D_8010DF48_log_jam.rgba);
        }
        effect->active = 0;
        effect->color = D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void func_8010A880_log_jam(omObjData *object) {
    HuSprAnimData *sprite = func_80055194_main(D_8010E5CC_log_jam[6]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010E5DC_log_jam; i < 8; i++, effect++) {
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
        func_8010D950_log_jam(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_8010A9D4_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprAnimData *sprite = func_80055194_main(D_8010E5CC_log_jam[6]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010E5DC_log_jam; i < 8; i++, effect++) {
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
        memcpy(effect->color.rgba, color, sizeof(LogJamColor));
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8010D950_log_jam(effect->model, sprite, 0, effect->color.rgba);
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

void func_8010ABA4_log_jam(void) {
    HuSprAnimData *sprite;
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    D_8010E5CC_log_jam[7] = func_8010A300_log_jam(0x340012);
    sprite = func_80055194_main(D_8010E5CC_log_jam[7]);
    D_8010E5E0_log_jam = omAddObj(30, 0, 0, -1, func_8010AD04_log_jam);
    D_8010E5E4_log_jam = effect = HuMemAllocTag(sizeof(LogJamEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010CB64_log_jam(sprite, D_8010DF48_log_jam.rgba);
        } else {
            effect->model = func_8010D74C_log_jam(sprite, D_8010E5E4_log_jam[0].model, D_8010DF48_log_jam.rgba);
        }
        effect->active = 0;
        effect->color = D_8010DF48_log_jam;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void func_8010AD04_log_jam(omObjData *object) {
    HuSprAnimData *sprite = func_80055194_main(D_8010E5CC_log_jam[7]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010E5E4_log_jam; i < 8; i++, effect++) {
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
        func_8010D950_log_jam(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->patNum) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_8010AE58_log_jam(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprAnimData *sprite = func_80055194_main(D_8010E5CC_log_jam[7]);
    LogJamEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010E5E4_log_jam; i < 8; i++, effect++) {
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
        if (color != NULL) {
            memcpy(effect->color.rgba, color, sizeof(LogJamColor));
        } else {
            memset(effect->color.rgba, 0xFF, sizeof(LogJamColor));
        }
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8010D950_log_jam(effect->model, sprite, 0, effect->color.rgba);
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

void func_8010B04C_log_jam(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = 126.8f;
    Center.z = -0.8f;
    CRot.x = 350.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1062.0f;
    func_8010BCA8_log_jam(0);
    func_8010BCA8_log_jam(1);
    D_8010E638_log_jam = 0;
    D_8010E634_log_jam = 0;
    D_8010E630_log_jam = 0;
    omAddObj(31, 0, 0, -1, func_8010B86C_log_jam);
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

void func_8010B17C_log_jam(void) {
    LogJamCamera delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (D_8010E094_log_jam) {
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
                func_8010BE94_log_jam(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                      delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 104,
                   D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_8010E098_log_jam++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_8010E098_log_jam--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_8010E09C_log_jam++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_8010E09C_log_jam--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010E098_log_jam + 20, (s16)D_8010E09C_log_jam + 104,
                   D_800D5218_main);
            break;
        case 3:
            D_8010E094_log_jam = 0;
            break;
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_8010E094_log_jam == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010E094_log_jam++ >= 4) {
            D_8010E094_log_jam = 0;
        }
    }
}

void func_8010B86C_log_jam(omObjData *object) {
    f32 t;

    if (D_8010E634_log_jam <= 0) {
        func_8010C084_log_jam(0);
        D_8010E638_log_jam = 0;
        return;
    }
    if (D_8010E630_log_jam == 0) {
        Center.x = D_8010E5E8_log_jam[0].center.x;
        Center.y = D_8010E5E8_log_jam[0].center.y;
        Center.z = D_8010E5E8_log_jam[0].center.z;
        CRot.x = D_8010E5E8_log_jam[0].rot.x;
        CRot.y = D_8010E5E8_log_jam[0].rot.y;
        CRot.z = D_8010E5E8_log_jam[0].rot.z;
        CZoom = D_8010E5E8_log_jam[0].zoom;
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
        D_8010E634_log_jam = 0;
    } else {
        t = (f32)D_8010E630_log_jam / (f32)D_8010E634_log_jam;
        Center.x = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.x,
                                         D_8010E5E8_log_jam[1].center.x);
        Center.y = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.y,
                                         D_8010E5E8_log_jam[1].center.y);
        Center.z = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].center.z,
                                         D_8010E5E8_log_jam[1].center.z);
        CRot.x = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.x,
                                       D_8010E5E8_log_jam[1].rot.x);
        CRot.y = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.y,
                                       D_8010E5E8_log_jam[1].rot.y);
        CRot.z = func_8010C4B4_log_jam(t, D_8010E5E8_log_jam[0].rot.z,
                                       D_8010E5E8_log_jam[1].rot.z);
        CZoom = func_8010C49C_log_jam(t, D_8010E5E8_log_jam[0].zoom,
                                      D_8010E5E8_log_jam[1].zoom);
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
        if (D_8010E630_log_jam > 0) {
            D_8010E630_log_jam--;
        } else {
            D_8010E630_log_jam++;
        }
    }
    D_8010E638_log_jam = 1;
    func_8010C084_log_jam(0);
}

void func_8010BCA8_log_jam(s32 arg0) {
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
    D_8010E5E8_log_jam[arg0].center.x = Center.x;
    D_8010E5E8_log_jam[arg0].center.y = Center.y;
    D_8010E5E8_log_jam[arg0].center.z = Center.z;
    D_8010E5E8_log_jam[arg0].rot.x = CRot.x;
    D_8010E5E8_log_jam[arg0].rot.y = CRot.y;
    D_8010E5E8_log_jam[arg0].rot.z = CRot.z;
    D_8010E5E8_log_jam[arg0].zoom = CZoom;
    D_8010E5E8_log_jam[arg0].unk_1C = D_8010E5E8_log_jam[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010BE94_log_jam(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010E630_log_jam = frames - 1;
        D_8010E634_log_jam = frames;
        if (x != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].center.x = x;
        } else {
            D_8010E5E8_log_jam[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].center.y = y;
        } else {
            D_8010E5E8_log_jam[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].center.z = z;
        } else {
            D_8010E5E8_log_jam[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].rot.x = rotX;
        } else {
            D_8010E5E8_log_jam[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].rot.y = rotY;
        } else {
            D_8010E5E8_log_jam[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].rot.z = rotZ;
        } else {
            D_8010E5E8_log_jam[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_8010E5E8_log_jam[0].zoom = zoom;
        } else {
            D_8010E5E8_log_jam[0].zoom = CZoom;
        }
        func_8010BCA8_log_jam(1);
    }
}

void func_8010C084_log_jam(s32 camIndex) {
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

f32 func_8010C1D8_log_jam(f32 arg0, f32 arg1) {
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

f32 func_8010C2DC_log_jam(f32 target, f32 current, f32 step) {
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

f32 func_8010C49C_log_jam(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 func_8010C4B4_log_jam(f32 arg0, f32 arg1, f32 arg2) {
    return func_8010C2DC_log_jam(arg2, arg1, fabsf(func_8010C1D8_log_jam(arg2, arg1) * arg0));
}

f32 func_8010C514_log_jam(f32 arg0, f32 arg1, f32 arg2) {
    if (__builtin_fabs((f64)(arg0 - arg1)) < arg2) {
        return arg0;
    }

    if (arg0 < arg1) {
        arg2 = -arg2;
    }

    return arg1 + arg2;
}

void func_8010C55C_log_jam(omObjData *object, u32 arg1) {
    object->work[0] = arg1 >> 24;
    object->work[1] = (arg1 >> 16) & 0xFF;
    object->work[2] = (arg1 >> 8) & 0xFF;
    object->work[3] = arg1 & 0xFF;
}

u32 func_8010C588_log_jam(omObjData *object) {
    LogJamWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

void func_8010C5DC_log_jam(omObjData *object, s16 motion, s16 shift) {
    HmfModel *model = &Hu3DData[object->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *anim;

    Hu3DMotionShiftSet(object->model[0], object->motion[motion], 0, shift, 0);
    anim = &((func_800E1BA8_minigame_ObjData *)object->data)->unkE8[motion];
    if (anim->unk00 & 1) {
        model->motShiftAttr = 2;
    } else {
        model->motShiftAttr = 0;
    }
    model->unk54 = (u16)anim->unk02;
}

void func_8010C6A4_log_jam(omObjData *object, s16 motion, s16 time) {
    HmfModel *model = &Hu3DData[object->model[0]];

    func_8010C5DC_log_jam(object, motion, 5);
    model->motShiftTime = time;
}

void func_8010C714_log_jam(omObjData *object, s16 motion, s16 time) {
    HmfModel *model = &Hu3DData[object->model[0]];
    func_800E1BA8_minigame_UnkE8_ObjData *anim;

    model->motId = object->motion[motion];
    model->unk48 = model->motTime = model->motSpeed = 1.0f;
    model->motIdShift = 0xFF;
    model->motTime = time;
    anim = &((func_800E1BA8_minigame_ObjData *)object->data)->unkE8[motion];
    if (anim->unk00 & 1) {
        model->motAttr = 2;
    } else {
        model->motAttr = 0;
    }
    model->unk48 = (u16)anim->unk02;
}

void func_8010C7D0_log_jam(omObjData *object) {
    HmfModel *model = &Hu3DData[object->model[0]];

    model->motSpeed = 0.0f;
}

void func_8010C7F8_log_jam(omObjData *object) {
    f32 frame = 0.0f;
    HmfModel *model = &Hu3DData[object->model[0]];

    if (model->motIdShift != 0xFF) {
        if (Hu3DPauseF == 0) {
            frame = model->unk0E + 2;
        }
        if (model->unk0C <= frame) {
            model->motId = model->motIdShift;
            model->motTime = model->motShiftTime;
            model->motAttr = model->motShiftAttr;
            model->unk48 = model->unk54;
            model->motIdShift = 0xFF;
            model->motSpeed = 1.0f;
        }
    }
}

void func_8010C8B0_log_jam(omObjData *object) {
    if (object->model[6] != -1) {
        func_800E4BA4_minigame((u8)object->model[6]);
    }
}

void func_8010C8E0_log_jam(s16 model, const char *name, HuMtx4F *out) {
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

void func_8010CAC0_log_jam(omObjData *object, const char *name, HuMtx4F out) {
    HuMtx4F mtx;
    HuMtx4F local;

    func_8008A070_main(mtx);
    mtxTransCat(mtx, object->trans.x, object->trans.y, object->trans.z);
    mtxRotCat(mtx, object->rot.x, object->rot.y, object->rot.z);
    mtxScaleCat(mtx, object->scale.x, object->scale.y, object->scale.z);
    func_8010C8E0_log_jam(object->model[0], name, &local);
    func_80018044_main(local, mtx, out);
}

s32 func_8010CB64_log_jam(HuSprAnimData *sprite, u8 *color) {
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
    model = func_8001A894_main(0x8C1, gfx, 4);
    data = Hu3DData[model].hmf;
    data->unk60->unk50 |= 0x1010000;
    gfx++;
    HuMemFree(data->unk3C);
    data->unk3C = HuMemAllocTag(sizeof(HmfModelData_Unk64_Unk3C_Struct), D_800CDD6A_main);
    func_8010DA84_log_jam(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_8010E190_log_jam));
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
    gDPSetRenderMode(gfx++, G_RM_AA_ZB_XLU_SURF, G_RM_NOOP2);
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
    for (i = 0; i < D_800D1FF0_main; i++) {
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
    data->unk3C->unk00[0] = data->unk3C->unk00[D_800D2008_main + 1];
    return model;
}

s32 func_8010D74C_log_jam(HuSprAnimData *sprite, u16 model, u8 *color) {
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
        gSPSegment(gfx++, 2, osVirtualToPhysical(sprite->pat->data));
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

void func_8010D950_log_jam(u16 model, HuSprAnimData *sprite, u16 frame, u8 *color) {
    HmfModel *modelData = Hu3DData + model;
    HmfData *data = modelData->hmf;
    Gfx *gfx = data->unk3C->unk00[D_800D2008_main + 1];

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

s32 func_8010DA84_log_jam(HuSprAnimData *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
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
