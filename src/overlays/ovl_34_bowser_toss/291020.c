#include "common.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "game/mallocblock.h"
#include "math.h"
#include "overlays/minigame.h"

#define CAMERA_KEEP 65535.0f

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
    struct BowserTossItem *unk_5C;
    f32 (*unk_60)[16]; // per-frame matrices
} UnkBowser;

// Per-player slot of the array allocated in func_80106568_bowser_toss
typedef struct BowserTossPlayer { // 0x5C bytes, two entries
    s16 index;                    // player index
    s16 unk_02;
    f32 unk_04; // score
    s32 unk_08;
    s16 unk_0C; // state, 5 when finished
    s16 unk_0E;
    s16 unk_10;
    char unk_12[2];
    s32 unk_14;
    s16 unk_18; // GwPlayer index
    s16 unk_1A; // pad
    s16 unk_1C; // chr
    s16 unk_1E; // cpu flag
    s16 unk_20; // cpu difficulty
    char unk_22[2];
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    s16 unk_30;
    s16 unk_32;
    f32 unk_34;
    f32 unk_38;
    s16 unk_3C;
    char unk_3E[2];
    s32 unk_40;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
    char unk_4E[2];
    s32 unk_50;
    f32 unk_54;
    f32 unk_58;
} BowserTossPlayer;

// Per-player slot of the array allocated in func_8010B41C_bowser_toss
typedef struct BowserTossBowser { // 0x10 bytes, three entries
    s16 spriteId;                 // HuSprGrpCreate handle
    s16 timer;
    s16 state; // toss state, 0x20 once the toss has finished
    char unk_06[2];
    s32 unk_08;
    s32 unk_0C;
} BowserTossBowser;

// Item data block returned by func_8010D9E0_bowser_toss
typedef struct BowserTossItem { // 0xC bytes
    s16 frames;                 // motion length
    s16 step;                   // frames between baked matrices
    s16 *nodes;
    HuMtx4F *mtx; // baked hook matrix per sampled frame
} BowserTossItem;

// Entry of the array allocated in func_8010A028_bowser_toss
typedef struct BowserTossEffect { // 0x30 bytes, 32 entries
    u16 unk_00;                   // active
    s16 unk_02;                   // model
    f32 unk_04;
    f32 unk_08;
    Vec unk_0C;
    Vec unk_18;
    Vec unk_24;
} BowserTossEffect;

typedef struct BowserTossCameraKey { // 0x24 bytes
    Vec center;
    Vec rot;
    f32 zoom;
    f32 unk_1C;
    f32 unk_20;
} BowserTossCameraKey;

// Per-camera interpolation state allocated in func_8010C2DC_bowser_toss
typedef struct BowserTossCamera { // 0x54 bytes, two entries
    BowserTossCameraKey keys[2];  // target, origin
    s32 frame;                    // frames remaining
    s32 frames;                   // total frames
    s32 active;
} BowserTossCamera;

typedef struct BowserTossScissor {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
} BowserTossScissor;

typedef struct BowserTossSprPos {
    s16 x;
    s16 y;
} BowserTossSprPos;

// Background sprite frame table entry
typedef struct BowserTossScrollFrame {
    s16 sprite; // index into D_8010FB98_bowser_toss
    s16 frame;
} BowserTossScrollFrame;

typedef union BowserTossWorkBytes { // packs the low byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BowserTossWorkBytes;

extern u8 D_8010F150_bowser_toss[]; // RGBA
extern s32 D_8010F194_bowser_toss;
extern Vec D_8010F198_bowser_toss[2];
extern s32 D_800A178C_main[][6];
extern s32 D_8010F1B0_bowser_toss[4];
extern s32 D_8010F1C0_bowser_toss[];
extern f32 D_8010F1E0_bowser_toss[];
extern f32 D_8010F200_bowser_toss[];
extern s32 D_8010F220_bowser_toss[];
extern s32 D_8010F228_bowser_toss[];
extern f32 D_8010F230_bowser_toss[];
extern f32 D_8010F240_bowser_toss[];
extern f32 D_8010F250_bowser_toss[];
extern f32 D_8010F260_bowser_toss[];
extern f32 D_8010F270_bowser_toss[2];
extern Vec D_8010F278_bowser_toss[14];
extern u8 D_8010F320_bowser_toss[4]; // RGBA
extern s16 D_8010F324_bowser_toss[2][5];
extern u8 D_8010F338_bowser_toss[4]; // RGBA
extern BowserTossScissor D_8010F33C_bowser_toss[2];
extern f32 D_8010F34C_bowser_toss;
extern s32 D_8010F3EC_bowser_toss; // camera test mode
extern s32 D_8010F3F0_bowser_toss; // camera test mode camera index
extern s32 D_8010F3F4_bowser_toss; // camera test mode text x offset
extern s32 D_8010F3F8_bowser_toss; // camera test mode text y offset
extern BowserTossScrollFrame D_8010F350_bowser_toss[];
extern BowserTossSprPos D_8010F378_bowser_toss[3][8]; // score sprite positions per counter
extern s32 D_8010F3D8_bowser_toss[5];                 // decimal place divisors
extern s8 D_800D20A1_main[];
extern u16 D_800D5558_main[];
extern s16 D_800CDA7C_main[];
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
extern omObjData *D_8010FB90_bowser_toss;
extern BowserTossEffect *D_8010FB94_bowser_toss;
extern s16 *D_8010FB98_bowser_toss;
extern s16 D_8010FB9C_bowser_toss[2];
extern D_80111B50_vine_with_me_Struct D_8010FBB8_bowser_toss;
extern const s16 D_8010F530_bowser_toss[];
extern const s16 D_8010F53C_bowser_toss[];
extern omObjData *D_8010FB88_bowser_toss;
extern UnkBowser *D_8010FB8C_bowser_toss;
extern BowserTossBowser *D_8010FBA0_bowser_toss;
extern s16 D_800CD1B0_main;
extern u8 D_800D2008_main;
extern s16 *D_800D04B4_main;
extern HuMtx4F *D_800D1358_main;
extern s16 D_800D138A_main;
extern HuMtx4F D_800D5A00_main[];
extern BowserTossCamera *D_8010FBA4_bowser_toss;
extern Vec D_8010FBA8_bowser_toss;

void func_80105C80_bowser_toss(omObjData *object);
void func_80105CEC_bowser_toss(omObjData *object);
void func_80106568_bowser_toss(void);
void func_801084DC_bowser_toss(void);
void func_8010A028_bowser_toss(void);
void func_8010A4A8_bowser_toss(void);
void func_8010AD98_bowser_toss(void);
void func_8010B41C_bowser_toss(void);
void func_8010C2DC_bowser_toss(void);
void func_8010B7AC_bowser_toss(omObjData *object);
void func_8010CDB8_bowser_toss(omObjData *object);
void func_8010D080_bowser_toss(s32 camIndex, s32 key);
f32 func_8010D8A0_bowser_toss(f32 t, f32 start, f32 end);
f32 func_8010D8B8_bowser_toss(f32 t, f32 start, f32 end);
f32 func_8010D5DC_bowser_toss(f32 arg0, f32 arg1);
f32 func_8010D6E0_bowser_toss(f32 target, f32 current, f32 step);
void func_8010D43C_bowser_toss(s32 camIndex);
void func_8010A500_bowser_toss(omObjData *object);
void func_8010649C_bowser_toss(omObjData *object);
void func_801064C0_bowser_toss(omObjData *object);
void func_801067B0_bowser_toss(omObjData *object);
s16 func_8010840C_bowser_toss(void);
s16 func_80108444_bowser_toss(void);
void func_8010847C_bowser_toss(omObjData *object, s16 arg1, s16 arg2);
s16 func_80109F20_bowser_toss(void);
void func_8010C1A0_bowser_toss(s16 index, s32 score);
s16 func_8010C23C_bowser_toss(void);
void func_8010C274_bowser_toss(void);
s16 func_8010C2A4_bowser_toss(void);
void func_8010D250_bowser_toss(s32 camIndex, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom,
                               s32 frames);
void func_8010D960_bowser_toss(omObjData *obj, u32 arg1);
void func_80106BC4_bowser_toss(omObjData *object);
void func_8010858C_bowser_toss(s16 arg0);
UnkBowser *func_80108800_bowser_toss(s16 arg0);
f32 func_801080D0_bowser_toss(f32 arg0, f32 arg1, f32 arg2);
void func_8010882C_bowser_toss(omObjData *object);
struct BowserTossItem *func_8010D9E0_bowser_toss(s16 model, s16 step, const char *hookName, s16 shape, s16 frame);
void func_8010DB9C_bowser_toss(s16 model, s16 step, struct BowserTossItem *item, s16 node, s16 shape, s16 frame);
void func_8010DDC4_bowser_toss(struct BowserTossItem *item);
void func_8010D918_bowser_toss(f32 *arg0, f32 *arg1, f32 *arg2, f32 arg3);
void func_8010A17C_bowser_toss(omObjData *object);
void func_8010A908_bowser_toss(omObjData *object);
void func_8010AF38_bowser_toss(s16 camera, Vec *pos, Vec *rot);
u16 func_8010AD54_bowser_toss(s32 dirAndFile);
s16 func_8010DDFC_bowser_toss(HuSprite_Unk84_Struct *sprite, u8 *color, s32 arg2);
s16 func_8010EA0C_bowser_toss(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color);
void func_8010EC10_bowser_toss(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);
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
                    func_8010D250_bowser_toss(D_8010FB78_bowser_toss, x, y, CAMERA_KEEP, CAMERA_KEEP, CAMERA_KEEP,
                                              CAMERA_KEEP, zoom, 30);
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

void func_801067B0_bowser_toss(omObjData *object) {
    BowserTossPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    s32 variant;
    s16 gwIndex;
    s16 chr;
    u32 model;
    s32 motionFile;
    s32 linkModel;
    f32 zero;

    player = func_8010D98C_bowser_toss(object);
    gwIndex = player->unk_18;
    chr = GwPlayer[gwIndex].chr;
    player->unk_1C = chr;
    player->unk_1A = GwPlayer[gwIndex].pad;
    player->unk_1E = GwPlayer[gwIndex].stat & 1;
    player->unk_20 = GwPlayer[gwIndex].cpu_difficulty;
    model = D_800A178C_main[chr][0];
    motionFile = D_800A178C_main[chr][1];
    linkModel = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motionFile, gwIndex, 0x289, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->model[3] = func_8000B108_main(3, 0x68D);
    object->model[4] = func_8000B108_main(4, 0x68D);
    object->model[10] = func_8000B108_main(model | linkModel, 0x2AD);
    Hu3DModelCameraSet(object->model[0], 1 << player->index);
    Hu3DModelCameraSet(object->model[1], 1 << player->index);
    Hu3DModelCameraSet(object->model[10], 1 << player->index);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 3, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x6D), 1, 0);
    func_800E5A00_minigame(object, 5, func_80017BB8_main(chr, 0x64), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 0x65), 1, 30);
    variant = rand8() & 1;
    func_800E5A00_minigame(object, 7, func_80017BB8_main(chr, D_8010F220_bowser_toss[variant]), 1, 120);
    player->unk_14 = D_8010F1C0_bowser_toss[chr] | D_8010F220_bowser_toss[variant];
    func_800E5A00_minigame(object, 8, func_80017BB8_main(chr, D_8010F228_bowser_toss[rand8() & 1]), 1, 120);
    func_800E5690_minigame(object, 5);
    Hu3DData[object->model[0]].motId = object->motion[5];
    Hu3DMotionShapeSet(object->model[0], object->motion[6], 1);
    Hu3DData[object->model[0]].motShapeSpeed = 0.0f;
    Hu3DData[object->model[0]].motShapeTime = 0.0f;
    player->unk_24 = D_8010F1E0_bowser_toss[chr];
    player->unk_28 = D_8010F200_bowser_toss[chr];
    player->unk_2C = player->unk_28 - player->unk_24;
    player->unk_30 = player->unk_32 = 0;
    player->unk_3C = 1;
    player->unk_40 = 0;
    player->unk_44 = 0;
    player->unk_04 = 0.0f;
    zero = player->unk_04;
    player->unk_34 = player->unk_38 = zero;
    player->unk_0E = 0;
    player->unk_02 = -1;
    player->unk_08 = 0;
    player->unk_50 = 0;
    player->unk_48 = zero;
    player->unk_0C = 0;
    player->unk_10 = -1;
    player->unk_4C = 0;
    func_8010858C_bowser_toss(player->index);
    func_80108800_bowser_toss(player->index);
    object->func = func_80106BC4_bowser_toss;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F5A0_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_80106BC4_bowser_toss);

void func_80107E84_bowser_toss(omObjData *object) {
    BowserTossPlayer *player;
    f32 ratio;

    player = func_8010D98C_bowser_toss(object);
    func_80108800_bowser_toss(player->index);
    D_800CDA7C_main[player->unk_1A] = D_800D5558_main[player->unk_1A] = D_800D20A1_main[player->unk_1A] = 0;
    switch (player->unk_0C) {
        case 1:
            player->unk_54 = D_8010F230_bowser_toss[player->unk_20] +
                             D_8010F240_bowser_toss[player->unk_20] *
                                 ((0.5 - (f32)(u8)(rand8() % 100) * 0.01) * 2);
            player->unk_58 = func_801080D0_bowser_toss(
                player->unk_54,
                D_8010F260_bowser_toss[player->unk_20] + (f32)(u8)(rand8() % 100) * 0.01 * 1500.0,
                D_8010F250_bowser_toss[player->unk_20]);
            D_800D5558_main[player->unk_1A] |= A_BUTTON;
            break;
        case 2:
            D_800D20A1_main[player->unk_1A] = player->unk_54 * 60.0f;
            ratio = player->unk_44 / 45.0f;
            if ((player->unk_08 & 1) && ratio < player->unk_58) {
                D_800D5558_main[player->unk_1A] |= A_BUTTON;
            }
            break;
    }
}

f32 func_801080D0_bowser_toss(f32 power, f32 distance, f32 fallback) {
    f32 pos[2];
    f32 vel[2];
    f32 angle;
    f32 scale;

    angle = 360.0f - power * 85.0f;
    for (scale = 0.5f; scale < 1.0f; scale += 0.01f) {
        pos[0] = D_8010F270_bowser_toss[0];
        pos[1] = D_8010F270_bowser_toss[1];
        vel[0] = fabs(cosdf(angle)) * scale * 75.99999904632568;
        vel[1] = fabs(sindf(angle)) * scale * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (distance <= pos[0]) {
            return scale;
        }
    }
    for (scale = 0.5f; scale > 0.1f; scale -= 0.01f) {
        pos[0] = D_8010F270_bowser_toss[0];
        pos[1] = D_8010F270_bowser_toss[1];
        vel[0] = fabs(cosdf(angle)) * scale * 75.99999904632568;
        vel[1] = fabs(sindf(angle)) * scale * 75.99999904632568;
        while (pos[1] > 0.0f) {
            pos[0] += vel[0];
            pos[1] += vel[1];
            vel[1] -= 0.65332f;
            if (vel[1] < -250.0) {
                vel[1] = -250.0f;
            }
        }
        if (distance <= pos[0]) {
            return scale;
        }
    }
    return fallback;
}

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

void func_801084DC_bowser_toss(void) {
    UnkBowser *bowser;
    s32 i;

    bowser = D_8010FB8C_bowser_toss = HuMemAllocTag(sizeof(UnkBowser) * 2, TAG_OVERLAY);
    memset(bowser, 0, sizeof(UnkBowser) * 2);
    for (i = 0; i < 2; i++, bowser++) {
        bowser->unk_00 = NULL;
        bowser->unk_5C = NULL;
        bowser->unk_10 = 0.0f;
        bowser->unk_14 = 120.0f;
        bowser->unk_18 = 0.0f;
        bowser->unk_1C = 0.0f;
        bowser->unk_20 = -1;
        bowser->unk_22 = 0;
        bowser->unk_24 = 0;
    }
    D_8010FB88_bowser_toss = omAddObj(0x14, 0, 0, -1, func_8010882C_bowser_toss);
}

void func_8010858C_bowser_toss(s16 index) {
    UnkBowser *bowser;
    HmfModel *model;
    u8 motId;
    u8 motIdShape;
    s16 frames;
    s32 size;
    s32 modelId;
    HmfModelData_Unk64_Unk8C_Struct *motData;

    bowser = &D_8010FB8C_bowser_toss[index];
    bowser->unk_00 = D_800EC598_minigame[index];
    bowser->unk_0A = 0;
    func_8010D98C_bowser_toss(bowser->unk_00);
    model = &Hu3DData[bowser->unk_00->model[0]];
    motId = model->motId;
    motIdShape = model->motIdShape;
    model->motId = bowser->unk_00->motion[4];
    model->motIdShape = bowser->unk_00->motion[6];
    bowser->unk_5C = func_8010D9E0_bowser_toss(bowser->unk_00->model[0], 1, "item_hook", 1, 0);
    model->motId = motId;
    model->motIdShape = motIdShape;
    motData = &D_800CCF58_main[bowser->unk_00->motion[6]];
    frames = motData->unk02 + 1;
    size = frames * sizeof(Mtx);
    bowser->unk_60 = HuMemAllocTag(size, TAG_OVERLAY);
    memset(bowser->unk_60, 0, size);
    memcpy(bowser->unk_60, bowser->unk_5C->mtx, size);
    func_8010DDC4_bowser_toss(bowser->unk_5C);
    bowser->unk_5C = NULL;
    if (index == 0) {
        bowser->unk_04 = func_8000B108_main(0x550000, 0x299);
        bowser->unk_06 = func_8000B108_main(0x550005, 0x29D);
        modelId = bowser->unk_08 = func_8000B108_main(0, 0x299);
    } else {
        bowser->unk_04 = Hu3DModelLink(D_8010FB8C_bowser_toss->unk_04);
        bowser->unk_06 = Hu3DModelLink(D_8010FB8C_bowser_toss->unk_06);
        modelId = bowser->unk_08 = Hu3DModelLink(D_8010FB8C_bowser_toss->unk_08);
    }
    Hu3DModelScaleSet(modelId, 1.3f, 1.3f, 1.3f);
    func_8001C258_main(bowser->unk_04, 0x4000, 0x4000);
    Hu3DModelHookSet(bowser->unk_04, bowser->unk_00->model[0], "item_hook");
    Hu3DModelCameraSet(bowser->unk_04, 1 << index);
    Hu3DModelCameraSet(bowser->unk_06, 1 << index);
    Hu3DModelCameraSet(bowser->unk_08, 1 << index);
}

UnkBowser *func_80108800_bowser_toss(s16 arg0) {
    return &D_8010FB8C_bowser_toss[arg0];
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010882C_bowser_toss);

void func_80109DB8_bowser_toss(omObjData *object, f32 angle, HuMtx4F mtx) {
    fmod(object->rot.y + angle, 360.0);
    func_8008A070_main(mtx);
    mtxTransCat(mtx, object->trans.x, object->trans.y, object->trans.z);
    mtxRotCat(mtx, object->rot.x, angle, object->rot.z);
    mtxScaleCat(mtx, object->scale.x, object->scale.y, object->scale.z);
}

void func_80109E4C_bowser_toss(UnkBowser *bowser, f32 *out, f32 time) {
    s16 frame;
    s16 next;
    f32 frac;

    if ((s16)time >= 29) {
        frame = next = 29;
        frac = 0.0f;
    } else if ((s16)time <= 0) {
        frame = next = 0;
        frac = 0.0f;
    } else {
        frac = time - (s16)time;
        frame = time;
        next = frame + 1;
    }
    func_8010D918_bowser_toss(bowser->unk_60[frame], bowser->unk_60[next], out, frac);
}

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

// Counts the frames until a projectile falls back to the ground.
s16 func_80109F68_bowser_toss(f32 x, f32 y, f32 velX, f32 velY) {
    s16 frames;
    f32 groundOffset;

    frames = 0;
    groundOffset = 0.0f;
    while (y > groundOffset + 10.0) {
        y += velY;
        velY -= 1.95996f;
        if (velY < -250.0) {
            velY = -250.0f;
        }
        groundOffset = -(fabs(velY) / 250.0 * 100.0);
        frames++;
    }
    return frames;
}

void func_8010A028_bowser_toss(void) {
    HuSprite_Unk84_Struct *sprite;
    BowserTossEffect *effect;
    HmfModel *model;
    s32 i;

    D_8010FB98_bowser_toss[5] = func_8010AD54_bowser_toss(11);
    sprite = func_80055194_main(D_8010FB98_bowser_toss[5]);
    D_8010FB90_bowser_toss = omAddObj(0x1E, 0, 0, -1, func_8010A17C_bowser_toss);
    D_8010FB94_bowser_toss = effect = HuMemAllocTag(sizeof(BowserTossEffect) * 32, TAG_OVERLAY);
    for (i = 0; i < 32; i++, effect++) {
        if (i == 0) {
            effect->unk_02 = func_8010DDFC_bowser_toss(sprite, D_8010F150_bowser_toss, 0);
        } else {
            effect->unk_02 = func_8010EA0C_bowser_toss(sprite, D_8010FB94_bowser_toss->unk_02, D_8010F150_bowser_toss);
        }
        effect->unk_00 = 0;
        effect->unk_04 = effect->unk_08 = 0.0f;
        effect->unk_0C.x = effect->unk_0C.y = effect->unk_0C.z = 0.0f;
        effect->unk_18.x = effect->unk_18.y = effect->unk_18.z = 0.0f;
        effect->unk_24.x = effect->unk_24.y = effect->unk_24.z = 0.0f;
        func_8001C258_main(effect->unk_02, 4, 4);
        model = &Hu3DData[effect->unk_02];
        model->motTime = 0.0f;
    }
}

void func_8010A17C_bowser_toss(omObjData *object) {
    HuSprite_Unk84_Struct *sprite;
    BowserTossEffect *effect;
    HmfModel *model;
    s32 i;

    sprite = func_80055194_main(D_8010FB98_bowser_toss[5]);
    for (i = 0, effect = D_8010FB94_bowser_toss; i < 32; i++, effect++) {
        if (effect->unk_00 == 0) {
            continue;
        }
        model = &Hu3DData[effect->unk_02];
        if (model->attr & 4) {
            continue;
        }
        effect->unk_0C.x += effect->unk_18.x;
        effect->unk_0C.y += effect->unk_18.y;
        effect->unk_0C.z += effect->unk_18.z;
        model->pos.x = effect->unk_0C.x;
        model->pos.y = effect->unk_0C.y;
        model->pos.z = effect->unk_0C.z;
        model->scale.x = effect->unk_24.x;
        model->scale.y = effect->unk_24.y;
        model->scale.z = effect->unk_24.z;
        func_8010EC10_bowser_toss(effect->unk_02, sprite, (s32)effect->unk_04, D_8010F150_bowser_toss);
        effect->unk_04 += effect->unk_08;
        if ((s32)effect->unk_04 >= sprite->unk10) {
            effect->unk_00 = 0;
            effect->unk_04 = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_8010A2D4_bowser_toss(Vec *pos, Vec *vel, Vec *scale, f32 speed, u16 camera) {
    HuSprite_Unk84_Struct *sprite;
    BowserTossEffect *effect;
    HmfModel *model;
    s32 i;

    sprite = func_80055194_main(D_8010FB98_bowser_toss[5]);
    for (i = 0, effect = D_8010FB94_bowser_toss; i < 32; i++, effect++) {
        if (effect->unk_00 != 0) {
            continue;
        }
        effect->unk_00 = 1;
        model = &Hu3DData[effect->unk_02];
        if (pos != NULL) {
            effect->unk_0C.x = pos->x;
            effect->unk_0C.y = pos->y;
            effect->unk_0C.z = pos->z;
        } else {
            effect->unk_0C.x = effect->unk_0C.y = effect->unk_0C.z = 0.0f;
        }
        if (vel != NULL) {
            effect->unk_18.x = vel->x;
            effect->unk_18.y = vel->y;
            effect->unk_18.z = vel->z;
        } else {
            effect->unk_18.x = effect->unk_18.y = effect->unk_18.z = 0.0f;
        }
        if (scale != NULL) {
            effect->unk_24.x = scale->x;
            effect->unk_24.y = scale->y;
            effect->unk_24.z = scale->z;
        } else {
            effect->unk_24.x = effect->unk_24.y = effect->unk_24.z = 1.0f;
        }
        effect->unk_08 = speed;
        effect->unk_04 = 0.0f;
        func_8010EC10_bowser_toss(effect->unk_02, sprite, 0, D_8010F150_bowser_toss);
        func_8001C258_main(effect->unk_02, 4, 0);
        Hu3DModelCameraSet(effect->unk_02, 1 << camera);
        model->motTime = 0.0f;
        model->pos.x = effect->unk_0C.x;
        model->pos.y = effect->unk_0C.y;
        model->pos.z = effect->unk_0C.z;
        model->scale.x = effect->unk_24.x;
        model->scale.y = effect->unk_24.y;
        model->scale.z = effect->unk_24.z;
        return i;
    }
    return -1;
}

// Appends a new object to the shared minigame object list.
void func_8010A4A8_bowser_toss(void) {
    omObjData *obj = omAddObj(0x20, 0x1C, 0, -1, func_8010A500_bowser_toss);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

void func_8010A500_bowser_toss(omObjData *object) {
    HuSprite_Unk84_Struct *sprite;
    s32 i;
    s32 j;
    s32 k;
    s32 base;
    s16 group;

    D_8010FB98_bowser_toss[0] = func_8010AD54_bowser_toss(0x550006);
    sprite = func_80055194_main(D_8010FB98_bowser_toss[0]);
    for (i = 0; i < 2; i++) {
        base = i * 14;
        j = 0;
        if (i == 0) {
            object->model[base + j] = func_8000B108_main(0x550001, 0xB9);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[0]);
        }
        j++;
        if (i == 0) {
            object->model[base + j] = func_8000B108_main(0x550003, 0xB9);
            object->model[base + j + 1] = func_8000B108_main(0x550004, 0xB9);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[j]);
            object->model[base + j + 1] = Hu3DModelLink(object->model[j + 1]);
        }
        for (k = 2; k < 5; k++) {
            object->model[base + j + k] = Hu3DModelLink(object->model[j + (k & 1)]);
        }
        j += 5;
        if (i == 0) {
            object->model[base + j] = func_8000B108_main(0x550002, 0x99);
        } else {
            object->model[base + j] = Hu3DModelLink(object->model[j]);
        }
        for (k = 1; k < 4; k++) {
            object->model[base + j + k] = Hu3DModelLink(object->model[base + j]);
        }
        j += 4;
        if (i == 0) {
            object->model[base + j] = func_8010DDFC_bowser_toss(sprite, D_8010F320_bowser_toss, 0);
        } else {
            object->model[base + j] = func_8010EA0C_bowser_toss(sprite, object->model[j], D_8010F320_bowser_toss);
        }
        for (k = 1; k < 4; k++) {
            object->model[base + j + k] = func_8010EA0C_bowser_toss(sprite, object->model[j], D_8010F320_bowser_toss);
        }
        for (k = base; k < base + 14; k++) {
            Hu3DModelPosSet(object->model[k], D_8010F278_bowser_toss[k - base].x, D_8010F278_bowser_toss[k - base].y,
                            D_8010F278_bowser_toss[k - base].z);
            Hu3DModelCameraSet(object->model[k], 1 << i);
        }
    }
    D_8010FB98_bowser_toss[4] = func_8010AD54_bowser_toss(0x55000A);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, D_8010FB98_bowser_toss[4], 0);
    HuSprPosSet(group, 0, 160, 120);
    func_800550F4_main(group, 0, 0);
    func_80054FF8_main(group, 0, 0);
    HuSprAttrSet(group, 0, 0x1000);
    object->func = func_8010A908_bowser_toss;
}

// Matches except for register allocation and floating-point constant hoisting: the
// target loads the 955.695 constant from rodata at each use (two copies) instead of
// keeping it in a callee-saved register, and spills the table row pointer.
#ifdef NON_MATCHING
void func_8010A908_bowser_toss(omObjData *object) {
    HuSprite_Unk84_Struct *sprite;
    s32 i;
    s32 j;
    s32 k;
    s32 base;
    s32 start;
    u16 parity;
    s32 index;
    s32 frame;

    sprite = func_80055194_main(D_8010FB98_bowser_toss[0]);
    for (i = 0; i < 2; i++) {
        base = i * 14;
        j = 0;
        start = (CenterM[i].x - 955.695037841796875) / 704.502487182617188 - 2.0;
        if (start < 0) {
            start = 0;
        }
        if (start >= 2) {
            func_8001C258_main(object->model[base + j], 4, 4);
        } else {
            func_8001C258_main(object->model[base + j], 4, 0);
        }
        j++;
        parity = start & 1;
        for (k = 0; k < 5; k++) {
            index = start + k;
            if (CenterM[i].x == Center.x) {
                func_8001C258_main(object->model[base + j + D_8010F324_bowser_toss[parity][k]], 4, 4);
            } else {
                func_8001C258_main(object->model[base + j + D_8010F324_bowser_toss[parity][k]], 4, 0);
                Hu3DModelPosSet(object->model[base + j + D_8010F324_bowser_toss[parity][k]],
                                (s16)index * 704.502487182617188 + 955.695037841796875, 0.0f, 0.0f);
            }
        }
        j += 5;
        start = CenterM[i].x / 500.0 - 1.0;
        if (start <= 0) {
            start = 1;
        }
        for (k = 0; k < 4; k++) {
            Hu3DModelPosSet(object->model[base + j + k], (f32)(start + k) * 500.0, 0.0f, 0.0f);
        }
        j += 4;
        for (k = 0; k < 4; k++) {
            Hu3DModelPosSet(object->model[base + j + k], (f32)(start + k) * 500.0, 75.0f, -300.0f);
            frame = start + k - 1;
            if (frame >= 20) {
                frame = 19;
                func_8001C258_main(object->model[base + j + k], 4, 4);
            } else {
                if (frame < 0) {
                    frame = 0;
                }
                func_8001C258_main(object->model[base + j + k], 4, 0);
            }
            func_8010EC10_bowser_toss(object->model[base + j + k], sprite, frame, D_8010F338_bowser_toss);
        }
        func_8010AF38_bowser_toss(i, &CenterM[i], &CRotM[i]);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010A908_bowser_toss);
#endif

u16 func_8010AD54_bowser_toss(s32 dirAndFile) {
    void *data;
    u16 sprite;

    data = DataRead(dirAndFile);
    sprite = HuSprAnimRead(data);
    DataClose(data);
    return sprite;
}

void func_8010AD98_bowser_toss(void) {
    s32 i;
    s32 j;
    s32 group;

    D_8010FB98_bowser_toss[1] = func_8010AD54_bowser_toss(0x550007);
    D_8010FB98_bowser_toss[2] = func_8010AD54_bowser_toss(0x550008);
    D_8010FB98_bowser_toss[3] = func_8010AD54_bowser_toss(0x550009);
    for (i = 0; i < 2; i++) {
        D_8010FB9C_bowser_toss[i] = group = (s32)HuSprGrpCreate(4, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(group, j, D_8010FB98_bowser_toss[1], 0);
            HuSprPosSet(group, j, D_8010F33C_bowser_toss[i].x, D_8010F33C_bowser_toss[i].y);
            func_800550F4_main(group, j, 0);
            func_80054FF8_main(group, j, 0);
            HuSprAttrSet(group, j, 0x483C);
            HuSprScissorSet(group, j, D_8010F33C_bowser_toss[i].x, D_8010F33C_bowser_toss[i].y,
                            D_8010F33C_bowser_toss[i].width, D_8010F33C_bowser_toss[i].height);
        }
    }
}

void func_8010AF38_bowser_toss(s16 camera, Vec *pos, Vec *rot) {
    s16 group;
    f32 x;
    f32 y;
    f32 scrollY;
    f32 signX;
    f32 signY;
    s16 frame;
    BowserTossScrollFrame *entry;

    group = D_8010FB9C_bowser_toss[camera];
    x = (pos->x - Center.x) / D_8010F34C_bowser_toss;
    y = (pos->y - Center.y) / D_8010F34C_bowser_toss;
    if (x == 0.0f) {
        HuSprDispOff(group, 1);
        HuSprDispOff(group, 3);
    } else {
        HuSprDispOn(group, 1);
        HuSprDispOn(group, 3);
    }
    if (y == 0.0f) {
        HuSprDispOff(group, 2);
        HuSprDispOff(group, 3);
    } else {
        HuSprDispOn(group, 2);
        HuSprDispOn(group, 3);
    }
    frame = y / 120.0f;
    if (camera == 0) {
        x = -fmod(x, 320.0);
        scrollY = fmod(y, 120.0);
    } else {
        x = -fmod(x, 320.0);
        scrollY = fmod(y, 120.0) + 120.0;
    }
    signX = (pos->x >= 0.0f) ? 1.0f : -1.0f;
    signY = (pos->y >= 0.0f) ? 1.0f : -1.0f;

    if (frame >= 8) {
        frame = 7;
    } else if (frame < 0) {
        frame = 0;
    }
    entry = &D_8010F350_bowser_toss[frame];
    HuSprPosSet(group, 0, x, scrollY);
    HuSprGrpMemberSet(group, 0, D_8010FB98_bowser_toss[entry->sprite], entry->frame);
    func_80054FF8_main(group, 0, entry->frame);
    HuSprPosSet(group, 1, x + signX * 320.0f, scrollY);
    HuSprGrpMemberSet(group, 1, D_8010FB98_bowser_toss[entry->sprite], entry->frame);
    func_80054FF8_main(group, 1, entry->frame);

    if (signY >= 0.0f) {
        frame++;
    } else {
        frame--;
    }
    if (frame >= 8) {
        frame = 7;
    } else if (frame < 0) {
        frame = 0;
    }
    entry = &D_8010F350_bowser_toss[frame];
    HuSprPosSet(group, 2, x, scrollY - signY * 120.0f);
    HuSprGrpMemberSet(group, 2, D_8010FB98_bowser_toss[entry->sprite], entry->frame);
    func_80054FF8_main(group, 2, entry->frame);
    HuSprPosSet(group, 3, x + signX * 320.0f, scrollY - signY * 120.0f);
    HuSprGrpMemberSet(group, 3, D_8010FB98_bowser_toss[entry->sprite], entry->frame);
    func_80054FF8_main(group, 3, entry->frame);
}

void func_8010B41C_bowser_toss(void) {
    HuSprite_Unk84_Struct *anim;
    BowserTossBowser *bowser;
    s32 i;
    s32 j;

    D_8010FB98_bowser_toss[6] = func_8010AD54_bowser_toss(0x31);
    D_8010FB98_bowser_toss[7] = func_8010AD54_bowser_toss(0x55000B);
    D_8010FB98_bowser_toss[8] = func_8010AD54_bowser_toss(0x55000C);
    anim = func_80055194_main(D_8010FB98_bowser_toss[8]);
    for (i = 0; i < anim->unk10; i++) {
        anim->unk00[i].unk08 = 8;
        anim->unk00[i].unk0A = 8;
    }
    D_8010FB98_bowser_toss[9] = func_8010AD54_bowser_toss(0x32);
    D_8010FB98_bowser_toss[10] = func_8010AD54_bowser_toss(0x55000D);
    anim = func_80055194_main(D_8010FB98_bowser_toss[10]);
    for (i = 0; i < anim->unk10; i++) {
        anim->unk00[i].unk08 = 8;
        anim->unk00[i].unk0A = 8;
    }

    D_8010FBA0_bowser_toss = HuMemAllocTag(sizeof(BowserTossBowser) * 3, TAG_OVERLAY);
    for (i = 0, bowser = D_8010FBA0_bowser_toss; i < 3; i++, bowser++) {
        bowser->timer = 0;
        if (i != 2) {
            bowser->state = 0;
            bowser->unk_0C = 0;
            bowser->unk_08 = 0;
        } else {
            bowser->state = 0x10;
            bowser->unk_08 = bowser->unk_0C = D_8010FB80_bowser_toss;
        }
        bowser->spriteId = HuSprGrpCreate(8, 0);
        for (j = 0; j < 8; j++) {
            switch (j) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 7:
                    if (i != 2) {
                        HuSprGrpMemberSet(bowser->spriteId, j, D_8010FB98_bowser_toss[6], 0);
                    } else {
                        HuSprGrpMemberSet(bowser->spriteId, j, D_8010FB98_bowser_toss[9], 0);
                    }
                    HuSprScaleSet(bowser->spriteId, j, 1.2f, 1.2f);
                    break;
                case 4:
                case 5:
                    if (i != 2) {
                        HuSprGrpMemberSet(bowser->spriteId, j, D_8010FB98_bowser_toss[8], 0);
                    } else {
                        HuSprGrpMemberSet(bowser->spriteId, j, D_8010FB98_bowser_toss[10], 0);
                    }
                    if ((i != 2) & (j == 5)) {
                        HuSprScaleSet(bowser->spriteId, j, 0.88f, 0.88f);
                    }
                    break;
                case 6:
                default:
                    HuSprGrpMemberSet(bowser->spriteId, j, D_8010FB98_bowser_toss[7], 0);
                    HuSprScaleSet(bowser->spriteId, j, 0.75f, 0.75f);
                    break;
            }
            func_800550F4_main(bowser->spriteId, j, 0);
            func_80054FF8_main(bowser->spriteId, j, 0);
            HuSprAttrSet(bowser->spriteId, j, 0x903C);
        }
    }
    omAddObj(0x3F, 0, 0, -1, func_8010B7AC_bowser_toss);
}

// Matches except for minor register allocation and instruction ordering: the
// TPLvl fade value lands in $f12 instead of $f2, operand registers swap in the
// score spread lerp, and the hoisted lerp offset adds have swapped operands.
#ifdef NON_MATCHING
void func_8010B7AC_bowser_toss(omObjData *object) {
    s32 digits[5];
    BowserTossBowser *bowser;
    BowserTossBowser *other;
    s32 i;
    s32 j;
    s32 done;
    s32 value;
    f32 t;
    f32 center;
    f32 dy;

    for (i = 0, bowser = D_8010FBA0_bowser_toss; i < 3; i++, bowser++) {
        done = 0;
        switch (bowser->state) {
            case 1:
                HuSprPosSet(bowser->spriteId, 6, D_8010F378_bowser_toss[i][6].x, D_8010F378_bowser_toss[i][6].y);
                HuSprTPLvlSet(bowser->spriteId, 6, 0);
                HuSprDispOn(bowser->spriteId, 6);
                bowser->state = 2;
                bowser->timer = 0;
                break;
            case 2:
                t = bowser->timer / 15.0f;
                HuSprTPLvlSet(bowser->spriteId, 6, (u16)(t * 256.0f));
                if (bowser->timer >= 15.0f) {
                    HuSprTPLvlSet(bowser->spriteId, 6, 256);
                    bowser->state = 0x1F;
                    bowser->timer = 0;
                }
                break;
            case 3:
                for (j = 0; j < 6; j++) {
                    HuSprPosSet(bowser->spriteId, j, D_8010F378_bowser_toss[i][j].x, D_8010F378_bowser_toss[i][j].y);
                    HuSprDispOn(bowser->spriteId, j);
                }
                HuSprPosSet(bowser->spriteId, 7, D_8010F378_bowser_toss[i][7].x, D_8010F378_bowser_toss[i][7].y);
                func_80054FF8_main(bowser->spriteId, 4, 1);
                func_80054FF8_main(bowser->spriteId, 5, 0);
                bowser->state = 4;
                bowser->timer = 0;
                break;
            case 4:
                bowser->unk_0C += 333;
                if (bowser->unk_08 < bowser->unk_0C) {
                    bowser->unk_0C = bowser->unk_08;
                    done = 1;
                }
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / D_8010F3D8_bowser_toss[j];
                    value -= digits[j] * D_8010F3D8_bowser_toss[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        func_80054FF8_main(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        func_80054FF8_main(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                if (done) {
                    if (D_8010FB70_bowser_toss != -1) {
                        if (i == 0) {
                            other = &D_8010FBA0_bowser_toss[1];
                        } else {
                            other = &D_8010FBA0_bowser_toss[0];
                        }
                        if (other->state != 3 && other->state != 4) {
                            HuAudFXPlay(0x4AC);
                            D_8010FB70_bowser_toss = -1;
                        }
                    }
                    bowser->state = 5;
                    bowser->timer = 0;
                }
                break;
            case 5:
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x1F;
                    bowser->timer = 0;
                }
                break;
            case 16:
                for (j = 0; j < 6; j++) {
                    HuSprPosSet(bowser->spriteId, j, D_8010F378_bowser_toss[i][j].x, D_8010F378_bowser_toss[i][j].y);
                    HuSprDispOn(bowser->spriteId, j);
                }
                HuSprPosSet(bowser->spriteId, 7, D_8010F378_bowser_toss[i][7].x, D_8010F378_bowser_toss[i][7].y);
                func_80054FF8_main(bowser->spriteId, 4, 1);
                func_80054FF8_main(bowser->spriteId, 5, 0);
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / D_8010F3D8_bowser_toss[j];
                    value -= digits[j] * D_8010F3D8_bowser_toss[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        func_80054FF8_main(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        func_80054FF8_main(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                bowser->state = 0x40;
                bowser->timer = 0;
                break;
            case 18:
                value = bowser->unk_0C;
                for (j = 0; j < 5; j++) {
                    digits[j] = value / D_8010F3D8_bowser_toss[j];
                    value -= digits[j] * D_8010F3D8_bowser_toss[j];
                    if (digits[j] >= 10) {
                        digits[j] = 9;
                    } else if (digits[j] < 0) {
                        digits[j] = 0;
                    }
                    if (j == 0) {
                        if (digits[0] > 0) {
                            HuSprDispOn(bowser->spriteId, 7);
                        }
                        func_80054FF8_main(bowser->spriteId, 7, (s16)digits[j]);
                    } else {
                        func_80054FF8_main(bowser->spriteId, j - 1, (s16)digits[j]);
                    }
                }
                bowser->state = 0x13;
                bowser->timer = 0;
            case 19:
                center = 0.0f;
                for (j = 0; j < 6; j++) {
                    center += D_8010F378_bowser_toss[i][j].x;
                }
                center += D_8010F378_bowser_toss[i][7].x;
                center /= 7.0f;
                t = bowser->timer / 15.0f;
                if (t < 0.0f) {
                    t = 0.0f;
                } else if (t > 1.0f) {
                    t = 1.0f;
                }
                t = sindf(t * 180.0f);
                HuSprPosSet(bowser->spriteId, 7,
                            center + (D_8010F378_bowser_toss[i][7].x - center) * (t + 1.0f),
                            D_8010F378_bowser_toss[i][7].y);
                HuSprScaleSet(bowser->spriteId, j, t * 1.2f + 1.2, t * 1.2f + 1.2);
                for (j = 0; j < 6; j++) {
                    HuSprPosSet(bowser->spriteId, j, center + (D_8010F378_bowser_toss[i][j].x - center) * (t + 1.0f),
                                D_8010F378_bowser_toss[i][j].y);
                    if (j < 4) {
                        HuSprScaleSet(bowser->spriteId, j, t * 1.2f + 1.2, t * 1.2f + 1.2);
                    } else {
                        HuSprScaleSet(bowser->spriteId, j, t + 1.0, t + 1.0);
                    }
                }
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x40;
                    bowser->timer = 0;
                }
                break;
            case 32:
                t = bowser->timer / 15.0f;
                center = func_8010D8A0_bowser_toss(t, 0.0f, 81.0f);
                dy = func_8010D8A0_bowser_toss(t, 0.0f, -35.0f);
                for (j = 0; j < 8; j++) {
                    HuSprPosSet(bowser->spriteId, j, D_8010F378_bowser_toss[i][j].x + (s32)center,
                                D_8010F378_bowser_toss[i][j].y + (s32)dy);
                }
                if (bowser->timer >= 15.0f) {
                    bowser->state = 0x40;
                    bowser->timer = 0;
                }
                break;
            case 0x40:
                break;
        }
        bowser->timer++;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010B7AC_bowser_toss);
#endif

void func_8010C1A0_bowser_toss(s16 index, s32 score) {
    BowserTossBowser *bowser = &D_8010FBA0_bowser_toss[index];

    if (score == 0) {
        bowser->state = 1;
    } else if (index < 2) {
        bowser->state = 3;
        bowser->timer = 0;
        bowser->unk_08 = score;
        bowser->unk_0C = 0;
        if (D_8010FB70_bowser_toss == -1) {
            D_8010FB70_bowser_toss = HuAudFXPlay(0x4AB);
        }
    } else {
        bowser->state = 0x12;
        bowser->timer = 0;
        bowser->unk_08 = bowser->unk_0C = score;
    }
}

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

void func_8010C274_bowser_toss(void) {
    s32 i;
    BowserTossBowser *bowser;

    for (i = 0, bowser = D_8010FBA0_bowser_toss; i < 2; i++, bowser++) {
        bowser->state = 0x20;
        bowser->timer = 0;
    }
}

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

void func_8010C2DC_bowser_toss(void) {
    BowserTossCamera *cam;
    HuCamera *camera;
    s32 i;
    s32 j;

    D_8010FBA4_bowser_toss = HuMemAllocTag(sizeof(BowserTossCamera) * 2, TAG_OVERLAY);
    memset(D_8010FBA4_bowser_toss, 0, sizeof(BowserTossCamera) * 2);
    Center.x = 0.0f;
    Center.y = 212.0f;
    Center.z = 0.0f;
    CRot.x = 1.01f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1222.0f;
    D_8010FBA8_bowser_toss.x = 0.0f;
    D_8010FBA8_bowser_toss.y = 162.0f;
    D_8010FBA8_bowser_toss.z = 0.0f;
    for (i = 0, cam = D_8010FBA4_bowser_toss; i < 2; i++, cam++) {
        CenterM[i].x = Center.x;
        CenterM[i].y = Center.y;
        CenterM[i].z = Center.z;
        CRotM[i].x = CRot.x;
        CRotM[i].y = CRot.y;
        CRotM[i].z = CRot.z;
        CZoomM[i] = CZoom;
        func_8010D080_bowser_toss(i, 0);
        func_8010D080_bowser_toss(i, 1);
        cam->frame = cam->frames = cam->active = 0;
        camera = &gCameraList[i];
        for (j = 0; j < D_800D1FF0_main; j++) {
            camera->viewports[j].vp.vscale[0] = camera->screenScale.x;
            camera->viewports[j].vp.vscale[1] = camera->screenScale.y;
            camera->viewports[j].vp.vscale[2] = camera->screenScale.z;
            camera->viewports[j].vp.vtrans[0] = camera->screenPos.x;
            camera->viewports[j].vp.vtrans[1] = camera->screenPos.y;
            camera->viewports[j].vp.vtrans[2] = camera->screenPos.z;
        }
    }
    omAddObj(0x1F, 0, 0, -1, func_8010CDB8_bowser_toss);
}

// Matches except that the target loads D_8010F3F0_bowser_toss into a temporary
// before setting fontcolor and copies it into cam afterwards.
#ifdef NON_MATCHING
void func_8010C570_bowser_toss(void) {
    BowserTossCameraKey delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;
    s32 cam;
    s32 i;
    Vec *center;
    Vec *rot;

    speed = 1.0f;
    cam = -1;
    switch (D_8010F3EC_bowser_toss) {
        case 1:
            if ((u16)D_800CDA7C_main[0] & A_BUTTON) {
                speed = 8.0f;
            }
            if (D_800CDA7C_main[0] & B_BUTTON) {
                speed = 0.5f;
            }
            if (D_800D5558_main[0] & START_BUTTON) {
                CenterM[D_8010F3F0_bowser_toss].x = Center.x;
                CenterM[D_8010F3F0_bowser_toss].y = Center.y;
                CenterM[D_8010F3F0_bowser_toss].z = Center.z;
                CRotM[D_8010F3F0_bowser_toss].x = CRot.x;
                CRotM[D_8010F3F0_bowser_toss].y = CRot.y;
                CRotM[D_8010F3F0_bowser_toss].z = CRot.z;
                CZoomM[D_8010F3F0_bowser_toss] = CZoom;
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
                delta.center.x += CenterM[D_8010F3F0_bowser_toss].x;
                delta.center.y += CenterM[D_8010F3F0_bowser_toss].y;
                delta.center.z += CenterM[D_8010F3F0_bowser_toss].z;
                delta.rot.x += CRotM[D_8010F3F0_bowser_toss].x;
                delta.rot.y += CRotM[D_8010F3F0_bowser_toss].y;
                delta.rot.z += CRotM[D_8010F3F0_bowser_toss].z;
                delta.zoom += CZoomM[D_8010F3F0_bowser_toss];
                func_8010D250_bowser_toss(D_8010F3F0_bowser_toss, delta.center.x, delta.center.y, delta.center.z,
                                          delta.rot.x, delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            cam = D_8010F3F0_bowser_toss;
            fontcolor = 15;
            if (D_800D5558_main[0] & R_TRIG) {
                if (++D_8010F3F0_bowser_toss >= 2) {
                    D_8010F3F0_bowser_toss = 0;
                    D_8010F3EC_bowser_toss++;
                }
                D_800D5558_main[0] &= ~R_TRIG;
            }
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_8010F3F4_bowser_toss++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_8010F3F4_bowser_toss--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_8010F3F8_bowser_toss++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_8010F3F8_bowser_toss--;
            }
            fontcolor = 8;
            cam = 1;
            break;
        case 3:
            D_8010F3EC_bowser_toss = 0;
            break;
    }
    if (cam != -1) {
        center = &CenterM[cam];
        rot = &CRotM[cam];
        sprintf(D_800D5218_main, "CAMERA TEST_MODE CAM_%d ", cam);
        print8((s16)D_8010F3F4_bowser_toss + 20, (s16)D_8010F3F8_bowser_toss + 80, D_800D5218_main);
        sprintf(D_800D5218_main, " CENTER X>%3.2f Y>%3.2f Z>%3.2f ", center->x, center->y, center->z);
        print8((s16)D_8010F3F4_bowser_toss + 20, (s16)D_8010F3F8_bowser_toss + 88, D_800D5218_main);
        sprintf(D_800D5218_main, " ROT    X>%3.2f Y>%3.2f Z>%3.2f ", rot->x, rot->y, rot->z);
        print8((s16)D_8010F3F4_bowser_toss + 20, (s16)D_8010F3F8_bowser_toss + 96, D_800D5218_main);
        sprintf(D_800D5218_main, " ZOOM   %3.2f ", CZoomM[cam]);
        print8((s16)D_8010F3F4_bowser_toss + 20, (s16)D_8010F3F8_bowser_toss + 104, D_800D5218_main);
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_8010F3EC_bowser_toss == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            for (i = 0; i < 2; i++) {
                center = &CenterM[i];
                rot = &CRotM[i];
                osSyncPrintf("CAMERA_NO %d \n", i);
                osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", center->x, center->y, center->z);
                osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", rot->x, rot->y, rot->z);
                osSyncPrintf(" ZOOM   %3.3f \n", CZoom);
            }
            osSyncPrintf(" \n");
        }
        if (D_8010F3EC_bowser_toss++ >= 4) {
            D_8010F3EC_bowser_toss = 0;
        }
    }
}
#else
INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", D_8010F998_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010C570_bowser_toss);
#endif

void func_8010CDB8_bowser_toss(omObjData *object) {
    BowserTossCamera *cam;
    Vec *center;
    Vec *rot;
    f32 t;
    s32 i;

    for (i = 0, cam = D_8010FBA4_bowser_toss; i < 2; i++, cam++) {
        center = &CenterM[i];
        rot = &CRotM[i];
        if (cam->frames <= 0) {
            func_8010D43C_bowser_toss(i);
            cam->active = 0;
            continue;
        }
        if (cam->frame == 0) {
            center->x = cam->keys[0].center.x;
            center->y = cam->keys[0].center.y;
            center->z = cam->keys[0].center.z;
            rot->x = cam->keys[0].rot.x;
            rot->y = cam->keys[0].rot.y;
            rot->z = cam->keys[0].rot.z;
            CZoomM[i] = cam->keys[0].zoom;
            cam->frames = 0;
        } else {
            t = 1.0f - (f32)cam->frame / (f32)cam->frames;
            center->x = func_8010D8A0_bowser_toss(t, cam->keys[1].center.x, cam->keys[0].center.x);
            center->y = func_8010D8A0_bowser_toss(t, cam->keys[1].center.y, cam->keys[0].center.y);
            center->z = func_8010D8A0_bowser_toss(t, cam->keys[1].center.z, cam->keys[0].center.z);
            rot->x = func_8010D8B8_bowser_toss(t, cam->keys[1].rot.x, cam->keys[0].rot.x);
            rot->y = func_8010D8B8_bowser_toss(t, cam->keys[1].rot.y, cam->keys[0].rot.y);
            rot->z = func_8010D8B8_bowser_toss(t, cam->keys[1].rot.z, cam->keys[0].rot.z);
            CZoomM[i] = func_8010D8A0_bowser_toss(t, cam->keys[1].zoom, cam->keys[0].zoom);
            if (cam->frame > 0) {
                cam->frame--;
            } else {
                cam->frame++;
            }
        }
        if (rot->x >= 360.0) {
            rot->x -= 360.0;
        } else if (rot->x < 0.0) {
            rot->x += 360.0;
        }
        if (rot->y >= 360.0) {
            rot->y -= 360.0;
        } else if (rot->y < 0.0) {
            rot->y += 360.0;
        }
        if (rot->z >= 360.0) {
            rot->z -= 360.0;
        } else if (rot->z < 0.0) {
            rot->z += 360.0;
        }
        cam->active = 1;
        func_8010D43C_bowser_toss(i);
    }
}

void func_8010D080_bowser_toss(s32 camIndex, s32 key) {
    BowserTossCamera *cam = &D_8010FBA4_bowser_toss[camIndex];
    Vec *center = &CenterM[camIndex];
    Vec *rot = &CRotM[camIndex];

    if (rot->x >= 360.0) {
        rot->x -= 360.0;
    } else if (rot->x < 0.0) {
        rot->x += 360.0;
    }
    if (rot->y >= 360.0) {
        rot->y -= 360.0;
    } else if (rot->y < 0.0) {
        rot->y += 360.0;
    }
    if (rot->z >= 360.0) {
        rot->z -= 360.0;
    } else if (rot->z < 0.0) {
        rot->z += 360.0;
    }
    cam->keys[key].center.x = center->x;
    cam->keys[key].center.y = center->y;
    cam->keys[key].center.z = center->z;
    cam->keys[key].rot.x = rot->x;
    cam->keys[key].rot.y = rot->y;
    cam->keys[key].rot.z = rot->z;
    cam->keys[key].zoom = CZoomM[camIndex];
    cam->keys[key].unk_1C = cam->keys[key].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010D250_bowser_toss(s32 camIndex, f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    BowserTossCamera *cam = &D_8010FBA4_bowser_toss[camIndex];
    Vec *center = &CenterM[camIndex];
    Vec *rot = &CRotM[camIndex];

    if (frames > 0) {
        cam->frame = frames - 1;
        cam->frames = frames;
        if (x != CAMERA_KEEP) {
            cam->keys[0].center.x = x;
        } else {
            cam->keys[0].center.x = center->x;
        }
        if (y != CAMERA_KEEP) {
            cam->keys[0].center.y = y;
        } else {
            cam->keys[0].center.y = center->y;
        }
        if (z != CAMERA_KEEP) {
            cam->keys[0].center.z = z;
        } else {
            cam->keys[0].center.z = center->z;
        }
        if (rotX != CAMERA_KEEP) {
            cam->keys[0].rot.x = rotX;
        } else {
            cam->keys[0].rot.x = rot->x;
        }
        if (rotY != CAMERA_KEEP) {
            cam->keys[0].rot.y = rotY;
        } else {
            cam->keys[0].rot.y = rot->y;
        }
        if (rotZ != CAMERA_KEEP) {
            cam->keys[0].rot.z = rotZ;
        } else {
            cam->keys[0].rot.z = rot->z;
        }
        if (zoom != CAMERA_KEEP) {
            cam->keys[0].zoom = zoom;
        } else {
            cam->keys[0].zoom = CZoomM[camIndex];
        }
        func_8010D080_bowser_toss(camIndex, 1);
    }
}

void func_8010D43C_bowser_toss(s32 camIndex) {
    HuCamera *camera = &gCameraList[camIndex];
    f32 rotX = CRotM[camIndex].x;
    f32 rotY = CRotM[camIndex].y;

    camera->pos.x = sindf(rotY) * cosdf(rotX) * CZoomM[camIndex] + CenterM[camIndex].x;
    camera->pos.y = -sindf(rotX) * CZoomM[camIndex] + CenterM[camIndex].y;
    camera->pos.z = cosdf(rotY) * cosdf(rotX) * CZoomM[camIndex] + CenterM[camIndex].z;
    camera->at.x = CenterM[camIndex].x;
    camera->at.y = CenterM[camIndex].y;
    camera->at.z = CenterM[camIndex].z;
    camera->up.x = sindf(rotY) * sindf(rotX);
    camera->up.y = cosdf(rotX);
    camera->up.z = cosdf(rotY) * sindf(rotX);
}

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

f32 func_8010D6E0_bowser_toss(f32 target, f32 current, f32 step) {
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

f32 func_8010D8A0_bowser_toss(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 func_8010D8B8_bowser_toss(f32 t, f32 start, f32 end) {
    return func_8010D6E0_bowser_toss(end, start, fabsf(func_8010D5DC_bowser_toss(end, start) * t));
}

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

BowserTossItem *func_8010D9E0_bowser_toss(s16 model, s16 step, const char *hookName, s16 shape, s16 frame) {
    HmfModelData_Unk64_Unk8C_Struct *motion;
    HmfData *hmf;
    s16 node;
    BowserTossItem *item;

    if (shape) {
        motion = &D_800CCF58_main[Hu3DData[model].motIdShape];
    } else {
        motion = &D_800CCF58_main[Hu3DData[model].motId];
    }
    hmf = Hu3DData[model].hmf;
    node = func_8002C834_main(hmf, hookName);
    item = HuMemAlloc(sizeof(BowserTossItem));
    item->mtx = HuMemAlloc((motion->unk02 + step) / step * sizeof(HuMtx4F));
    item->nodes = HuMemAlloc(hmf->unk16 * sizeof(s16));
    item->frames = motion->unk02;
    item->step = step;
    func_8010DB9C_bowser_toss(model, step, item, node, shape, frame);
    return item;
}

void func_8010DB9C_bowser_toss(s16 model, s16 step, BowserTossItem *item, s16 node, s16 shape, s16 frame) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_Unk64_Unk8C_Struct *motion = &D_800CCF58_main[Hu3DData[model].motId];
    HmfModelData_Unk64_Unk8C_Struct *shapeMotion = &D_800CCF58_main[Hu3DData[model].motIdShape];
    s16 i;

    D_800D1358_main = item->mtx;
    D_800D04B4_main = item->nodes;
    D_800CD1B0_main = 0;
    guMtxIdentF(D_800D5A00_main[0]);
    if (shape) {
        for (i = 0; i < shapeMotion->unk02; i += step) {
            func_8002DFF8_main(hmf, frame, motion, 1);
            func_8002DFF8_main(hmf, i, shapeMotion, 0);
            D_800D138A_main = 0;
            func_80016C2C_main(hmf, 0, node);
        }
    } else {
        for (i = 0; i < motion->unk02; i += step) {
            func_8002DFF8_main(hmf, i, motion, 1);
            func_8002DFF8_main(hmf, frame, shapeMotion, 0);
            D_800D138A_main = 0;
            func_80016C2C_main(hmf, 0, node);
        }
    }
}

void func_8010DDC4_bowser_toss(BowserTossItem *item) {
    HuMemFree(item->mtx);
    HuMemFree(item->nodes);
    HuMemFree(item);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010DDFC_bowser_toss);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010EA0C_bowser_toss);

void func_8010EC10_bowser_toss(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_34_bowser_toss/291020", func_8010ED44_bowser_toss);
