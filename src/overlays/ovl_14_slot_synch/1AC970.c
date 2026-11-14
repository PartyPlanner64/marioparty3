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
#include "game/gamemes.h"
#include "game/input.h"
#include "game/printfunc.h"

#define CAMERA_KEEP 65535.0f

typedef struct UnkSlotPlayer { // 0x30 bytes, four entries
    s16 unk_00;
    s16 unk_02; // team
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s32 unk_18;
    s16 unk_1C; // player index
    s16 unk_1E; // pad
    s16 unk_20; // character
    s16 unk_22; // CPU flag
    s16 unk_24; // CPU difficulty
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
} UnkSlotPlayer;

typedef struct UnkSlotCamera {
    Vec center;
    Vec rot;
    f32 zoom;
    f32 unk_1C;
    f32 unk_20;
} UnkSlotCamera;

typedef struct UnkSlotSynch { // 0x20 bytes, two entries (one per team)
    omObjData *unk_00;
    omObjData *unk_04;
    UnkSlotPlayer *unk_08;
    UnkSlotPlayer *unk_0C;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} UnkSlotSynch;

typedef struct UnkSlotMachine { // 0x3C bytes, four entries (one per player)
    s16 unk_00;                 // model
    u8 unk_02;
    u8 unk_03;
    s8 unk_04;
    u8 unk_05;
    u8 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C; // state
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
} UnkSlotMachine;

typedef struct UnkSlotReelRow { // 0x94 bytes
    u16 unk_00[0x48];           // vertex indices
    s16 unk_90;
    s16 unk_92; // vertex count
} UnkSlotReelRow;

typedef struct UnkSlotReel { // 0x20 bytes, two entries
    s16 unk_00;              // model
    s16 unk_02;
    s16 unk_04;
    char unk_06[0x2];
    f32 unk_08;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    s16 unk_18; // row count
    char unk_1A[0x2];
    UnkSlotReelRow *unk_1C;
} UnkSlotReel;

typedef union UnkSlotSynchBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} UnkSlotSynchBytes;

typedef struct UnkSlotSpritePos { // 6 bytes
    s16 x;
    s16 y;
    u8 unk_04;
    u8 unk_05;
} UnkSlotSpritePos;

typedef struct UnkSlotSprite { // 0x2C bytes, 24 entries
    s16 unk_00;
    u16 unk_02;
    u16 unk_04;
    u8 unk_06;
    u8 unk_07;
    u8 unk_08;
    u8 unk_09;
    u8 unk_0A;
    u8 unk_0B;
    u16 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    f32 unk_28;
} UnkSlotSprite;

typedef struct UnkSlotOvlData { // 0xC bytes
    omObjData *unk_00;
    s16 unk_04;
    u16 unk_06;
    UnkSlotSprite *unk_08;
} UnkSlotOvlData;

typedef struct UnkSlotLight { // 0x10 bytes, two entries
    s16 unk_00;               // sprite group
    s16 unk_02;               // x
    s16 unk_04;               // y
    s16 unk_06[2];
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
} UnkSlotLight;

typedef union UnkSlotColor {
    u32 word;
    u8 rgba[4];
} UnkSlotColor;

typedef struct UnkSlotEffect { // 0x34 bytes, 8 entries
    u16 active;
    s16 model;
    UnkSlotColor color;
    f32 frame;
    f32 speed;
    Vec pos;
    Vec vel;
    Vec scale;
} UnkSlotEffect;

typedef struct UnkSlotPos {
    s16 x;
    s16 y;
} UnkSlotPos;

typedef struct UnkSlotSpin { // 0x58 bytes, five entries
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 unk_04[4];
    s16 unk_0C[4][3];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34[9];
} UnkSlotSpin;

extern omObjData *D_8010DF40_slot_synch;
extern s32 D_8010DF44_slot_synch;
extern s32 D_8010DF48_slot_synch;
extern s32 D_8010DF4C_slot_synch;
extern s32 D_8010DF50_slot_synch;
extern s32 D_8010DF54_slot_synch;
extern s32 D_8010DF58_slot_synch;
extern UnkSlotSynch *D_8010DF5C_slot_synch;
extern s16 D_8010DF64_slot_synch;
extern s16 *D_8010DF8C_slot_synch;
extern UnkSlotLight *D_8010DF90_slot_synch;
extern D_80111B50_vine_with_me_Struct D_8010DFF8_slot_synch;
extern s32 D_8010D8B0_slot_synch;
extern Vec D_8010D7F0_slot_synch[4];
extern s32 D_8010D8B4_slot_synch[4];
extern s16 D_8010D8C4_slot_synch[4][2][2];
extern s16 D_8010D8E4_slot_synch[4];
extern UnkSlotPlayer *D_8010DF60_slot_synch;
extern s32 D_8010D8EC_slot_synch[8];
extern s32 D_8010D90C_slot_synch[4];
extern s32 D_8010D870_slot_synch[8];
extern u16 D_8010D91C_slot_synch[6];
extern u16 D_8010D928_slot_synch[8];
extern s32 D_8010DA40_slot_synch[8];
extern f32 D_8010DA20_slot_synch[4];
extern s32 D_8010DA30_slot_synch[4];
extern s16 D_8010D85C_slot_synch[4];
extern Vec D_8010D820_slot_synch[2];
extern s32 D_8010D9F0_slot_synch[4];
extern s32 D_8010DA00_slot_synch[4];
extern s32 D_8010DA10_slot_synch[4];
extern f32 D_8010D9D0_slot_synch[8];
extern s16 D_8010D9C8_slot_synch[4];
extern UnkSlotSpritePos D_8010D938_slot_synch[12];
extern UnkSlotSpritePos D_8010D980_slot_synch[12];
extern u16 D_8010DF66_slot_synch[4];
extern s32 D_8010D890_slot_synch[8];
extern s32 D_800A178C_main[][6];
extern UnkSlotOvlData D_8010DF70_slot_synch;
extern UnkSlotMachine *D_8010DF7C_slot_synch;
extern UnkSlotReel *D_8010DF80_slot_synch;
extern omObjData *D_8010DF84_slot_synch;
extern omObjData *D_8010DF94_slot_synch;
extern UnkSlotEffect *D_8010DF98_slot_synch;
extern UnkSlotColor D_8010D868_slot_synch;
extern UnkSlotColor D_8010D86C_slot_synch;
extern UnkSlotColor D_8010D864_slot_synch;
extern f32 D_8010D840_slot_synch[5];
extern UnkSlotCamera D_8010DFA0_slot_synch[2]; // target, origin
extern s32 D_8010DFE8_slot_synch;
extern s32 D_8010DA60_slot_synch;
extern s32 D_8010DA64_slot_synch;
extern s32 D_8010DA68_slot_synch;
extern s32 D_8010DFEC_slot_synch;
extern s32 D_8010DFF0_slot_synch;
extern u8 D_800D6A90_main;
extern UnkSlotSpin *D_8010DF88_slot_synch;
extern UnkSlotPos D_8010D838_slot_synch[2];
extern u8 D_8010D854_slot_synch[2][4];
extern Gfx D_8010DB60_slot_synch[];
extern s16 D_800CDD6A_main;
extern u8 D_800D2008_main;

void func_80105B98_slot_synch(omObjData *object);
void func_80105C08_slot_synch(omObjData *object);
void func_80106080_slot_synch(omObjData *object);
void func_801060A4_slot_synch(omObjData *object);
void func_8010614C_slot_synch(void);
void func_80106560_slot_synch(omObjData *object);
void func_80106878_slot_synch(omObjData *object);
void func_80106E8C_slot_synch(omObjData *object);
void func_80107108_slot_synch(omObjData *object);
void func_80107794_slot_synch(omObjData *object);
void func_80107A80_slot_synch(omObjData *object);
void func_80107A88_slot_synch(void);
s16 func_80107B00_slot_synch(f32 x, f32 y, u8 arg2, u8 arg3, u16 arg4);
void func_80107BAC_slot_synch(void);
void func_80108238_slot_synch(void);
void func_80108428_slot_synch(omObjData *object);
void func_80108D3C_slot_synch(void);
void func_8010800C_slot_synch(u8 arg0, u8 arg1);
void func_801089F8_slot_synch(s16 arg0);
s16 func_80108AA8_slot_synch(s16 arg0);
s16 func_80108848_slot_synch(s16 arg0);
s16 func_80108B74_slot_synch(s16 arg0, s16 arg1);
void func_80108D14_slot_synch(s16 arg0, s16 arg1);
s32 func_8010AD68_slot_synch(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color);
s16 func_80108C88_slot_synch(s16 arg0, s16 arg1);
void func_801092B8_slot_synch(UnkSlotReel *reel);
void func_801091D8_slot_synch(omObjData *object);
void func_801094E0_slot_synch(s16 arg0, f32 arg1, f32 arg2);
void func_80109754_slot_synch(omObjData *object);
s16 func_8010C47C_slot_synch(s32 file);
void func_8010B754_slot_synch(omObjData *object);
void func_8010BB90_slot_synch(s32 arg0);
void func_8010BF6C_slot_synch(s32 camIndex);
void func_8010BD7C_slot_synch(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames);
f32 func_8010C39C_slot_synch(f32 t, f32 start, f32 end);
void func_8010AC14_slot_synch(omObjData *object);
void func_80107D54_slot_synch(omObjData *object);
void func_8010A308_slot_synch(s16 arg0, s16 arg1, f32 arg2, f32 arg3);
s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *sprite, u8 *color);
s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color);
void func_8010D2AC_slot_synch(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color);
void func_8010A7D0_slot_synch(omObjData *object);
void func_80106CCC_slot_synch(s16 arg0, s32 arg1);
void func_80106D0C_slot_synch(s16 arg0, s16 arg1);
f32 func_8010C1C4_slot_synch(f32 target, f32 current, f32 step);
u16 func_8010A2C4_slot_synch(s32 file);
void func_80108CD0_slot_synch(s16 arg0);
s16 func_80109FA4_slot_synch(s16 arg0, s16 arg1);
s16 func_8010A178_slot_synch(s16 arg0);
void func_8010AA9C_slot_synch(s16 arg0, s16 arg1);
u32 func_8010C428_slot_synch(omObjData *arg0);
void func_8010A480_slot_synch(s16 team, s16 chr0, s16 chr1, s16 arg3);
void func_8010C3FC_slot_synch(omObjData *arg0, u32 arg1);
s16 func_80106CF0_slot_synch(s16 arg0);
void func_8010A1D0_slot_synch(void);
void func_801075D4_slot_synch(void);
void func_80109508_slot_synch(void);
void func_8010A39C_slot_synch(void);
void func_8010AAB8_slot_synch(void);
void func_8010AF38_slot_synch(void);
s16 func_80108A7C_slot_synch(s16 arg0);
f32 func_8010C0C0_slot_synch(f32 arg0, f32 arg1);
f32 func_8010C384_slot_synch(f32 t, f32 start, f32 end);
f32 func_8010C1C4_slot_synch(f32 target, f32 current, f32 step);
s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset);

void func_801059A0_slot_synch(void) {
    omObjData *obj;
    u8 camIndex;

    func_8001FE20_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(64);
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
    D_8010DF50_slot_synch = 900;
    D_8010DF4C_slot_synch = 0;
    D_8010DF48_slot_synch = 0;
    D_8010DF54_slot_synch = 0;
    D_8010DF58_slot_synch = 0;
    D_8010DF64_slot_synch = -1;
    D_8010DF8C_slot_synch = HuMemAllocTag(0x40, TAG_OVERLAY);
    D_8010DF40_slot_synch = omAddObj(0x20, 0, 0, -1, func_80105B98_slot_synch);
    memset(&D_8010DFF8_slot_synch, 0, 0x28);
    D_8010DFF8_slot_synch.unk01 = 4;
    func_800E5EA0_minigame(&D_8010DFF8_slot_synch);
}

void func_80105B98_slot_synch(omObjData *object) {
    object->func = func_80105C08_slot_synch;
    func_8010A39C_slot_synch();
    func_80109508_slot_synch();
    func_801075D4_slot_synch();
    func_8010AAB8_slot_synch();
    func_8010614C_slot_synch();
    func_8010AF38_slot_synch();
    if (_CheckFlag(10)) {
        D_8010DF44_slot_synch = 1;
    }
    WipeCreateIn(0xFF, 16);
}

void func_80105C08_slot_synch(omObjData *object) {
    UnkSlotSynch *team0 = &D_8010DF5C_slot_synch[0];
    UnkSlotSynch *team1 = &D_8010DF5C_slot_synch[1];

    switch (D_8010DF54_slot_synch) {
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(5);
                HuAudFXPlay(0xE);
                D_8010DF54_slot_synch++;
                D_8010DF4C_slot_synch = 0;
            }
            break;
        case 1:
            if (D_8010DF4C_slot_synch == 30) {
                HuAudSeqPlay(0x2E);
            }
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (D_8010DF50_slot_synch + 29) / 30, 156, 32);
                func_800E6F0C_minigame(2);
                D_8010DF54_slot_synch++;
            }
            break;
        case 2:
            D_8010DF50_slot_synch--;
            func_8003F578_main((D_8010DF50_slot_synch + 29) / 30);
            if (D_8010DF50_slot_synch <= 0) {
                HuAudFXAllStop();
                func_8003F5C0_main();
                GMesCreate(0x10);
                func_800E6F0C_minigame(3);
                HuAudSeqFadeOut(120);
                D_8010DF50_slot_synch = 0;
                D_8010DF4C_slot_synch = 0;
                D_8010DF54_slot_synch++;
            }
            break;
        case 3:
            if (GMesStatGet() == 0 && func_80106CF0_slot_synch(0) == 0 && func_80106CF0_slot_synch(1) == 0) {
                func_800E6F0C_minigame(4);
                func_8010A1D0_slot_synch();
                D_8010DF4C_slot_synch = 0;
                D_8010DF54_slot_synch++;
            }
            break;
        case 4:
            if (D_8010DF4C_slot_synch >= 15) {
                if (team0->unk_16 > team1->unk_16) {
                    GMesCreate(0x1E, team0->unk_08->unk_20, team0->unk_0C->unk_20);
                    GwPlayer[team0->unk_08->unk_1C].bonusCoin += 10;
                    GwPlayer[team0->unk_0C->unk_1C].bonusCoin += 10;
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 0;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 1;
                    HuAudSeqPlay(0x66);
                    D_8010DF58_slot_synch = 140;
                } else if (team0->unk_16 < team1->unk_16) {
                    GMesCreate(0x1E, team1->unk_08->unk_20, team1->unk_0C->unk_20);
                    GwPlayer[team1->unk_08->unk_1C].bonusCoin += 10;
                    GwPlayer[team1->unk_0C->unk_1C].bonusCoin += 10;
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 1;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 0;
                    HuAudSeqPlay(0x66);
                    D_8010DF58_slot_synch = 140;
                } else {
                    GMesCreate(0x20);
                    team0->unk_08->unk_04 = team0->unk_0C->unk_04 = 1;
                    team1->unk_08->unk_04 = team1->unk_0C->unk_04 = 1;
                    HuAudSeqPlay(0x6C);
                    D_8010DF58_slot_synch = 144;
                }
                D_8010DF4C_slot_synch = 0;
                D_8010DF54_slot_synch++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_8010DF4C_slot_synch = 0;
                D_8010DF54_slot_synch++;
            }
            break;
        case 6:
            if (D_8010DF4C_slot_synch >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                func_8004AB0C_main(16);
                D_8010DF4C_slot_synch = 0;
                D_8010DF54_slot_synch++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = func_80106080_slot_synch;
            }
            break;
    }
    func_801060A4_slot_synch(object);
    D_8010DF48_slot_synch++;
    D_8010DF4C_slot_synch++;
}

void func_80106080_slot_synch(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_801060A4_slot_synch(omObjData *object) {
    if (D_8010D8B0_slot_synch != 0) {
        if (D_8010D8B0_slot_synch == 1) {
            object->func = func_80106080_slot_synch;
        }
        D_8010D8B0_slot_synch--;
    } else if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010D8B0_slot_synch = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, D_8010D8B0_slot_synch);
        HuAudSeqFadeOut(D_8010D8B0_slot_synch);
        func_8004AB0C_main((s16)D_8010D8B0_slot_synch);
    }
}

void func_8010614C_slot_synch(void) {
    s32 playerIds[2][2];
    UnkSlotSynch *team;
    UnkSlotPlayer *player;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 invalid;
    s32 group0Count;
    s32 group1Count;
    s32 temp;
    s32 group;

    team = D_8010DF5C_slot_synch = HuMemAllocTag(sizeof(UnkSlotSynch) * 2, TAG_OVERLAY);
    D_8010DF60_slot_synch = HuMemAllocTag(sizeof(UnkSlotPlayer) * 4, TAG_OVERLAY);
    memset(D_8010DF60_slot_synch, 0, sizeof(UnkSlotPlayer) * 4);
    invalid = FALSE;
    group1Count = 0;
    group0Count = 0;
    for (i = 0; i < 4; i++) {
        group = GwPlayer[D_8010D8B4_slot_synch[i]].group;
        switch (group) {
            case 0:
                if (group0Count < 2) {
                    playerIds[group][group0Count] = D_8010D8B4_slot_synch[i];
                    group0Count++;
                } else {
                    invalid = TRUE;
                }
                break;
            case 1:
                if (group1Count < 2) {
                    playerIds[group][group1Count] = D_8010D8B4_slot_synch[i];
                    group1Count++;
                } else {
                    invalid = TRUE;
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
                playerIds[i][j] = D_8010D8C4_slot_synch[group][i][j];
            }
        }
    } else {
        if (rand8() & 1) {
            temp = playerIds[0][0];
            playerIds[0][0] = playerIds[0][1];
            playerIds[0][1] = temp;
        }
        if (rand8() & 1) {
            temp = playerIds[1][0];
            playerIds[1][0] = playerIds[1][1];
            playerIds[1][1] = temp;
        }
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    for (i = 0; i < 2; i++, team++) {
        obj = omAddObj(i + 16, 0, 0, -1, func_80106878_slot_synch);
        func_8010C3FC_slot_synch(obj, (u32)team);
        team->unk_10 = i;
        team->unk_12 = 0;
        team->unk_14 = 0;
        team->unk_16 = 0;
        team->unk_18 = -1;
        team->unk_1A = -1;
        team->unk_1C = 0;
        team->unk_1E = -1;
        for (j = 0; j < 2; j++) {
            player = &D_8010DF60_slot_synch[i * 2 + j];
            player->unk_00 = i * 2 + j;
            player->unk_02 = i;
            player->unk_1C = playerIds[i][j];
            obj = D_800EC598_minigame[D_800EC280_minigame] =
                omAddObj(D_8010D8E4_slot_synch[player->unk_00], 9, 60, -1, func_80106560_slot_synch);
            D_800EC280_minigame++;
            obj->trans.x = D_8010D7F0_slot_synch[player->unk_00].x;
            obj->trans.z = D_8010D7F0_slot_synch[player->unk_00].z;
            if (j == 0) {
                team->unk_00 = obj;
                team->unk_08 = player;
            } else {
                team->unk_04 = obj;
                team->unk_0C = player;
            }
            func_8010C3FC_slot_synch(obj, (u32)player);
        }
        func_8010A480_slot_synch(i, GwPlayer[team->unk_08->unk_1C].chr, GwPlayer[team->unk_0C->unk_1C].chr, 0);
    }
}

void func_80106560_slot_synch(omObjData *object) {
    UnkSlotPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    s16 playerIndex;
    s16 chr;
    s32 index;
    s32 model;
    s32 anim;

    player = (UnkSlotPlayer *)func_8010C428_slot_synch(object);
    playerIndex = player->unk_1C;
    chr = GwPlayer[playerIndex].chr;
    player->unk_20 = chr;
    player->unk_1E = GwPlayer[playerIndex].pad;
    player->unk_22 = GwPlayer[playerIndex].stat & 1;
    player->unk_24 = GwPlayer[playerIndex].cpu_difficulty;
    player->unk_26 = 0;
    player->unk_28 = 0;
    player->unk_2A = 0;
    player->unk_2C = -1;
    model = D_800A178C_main[chr][0];
    anim = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, anim, playerIndex, 0x2A9, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = NULL;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 21, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 38, func_80017BB8_main(chr, 0x33), 1, 60);
    func_800E5A00_minigame(object, 39, func_80017BB8_main(chr, 0x3A), 1, 60);
    if (chr != 5) {
        index = rand8() & 1;
        func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, D_8010D90C_slot_synch[index]), 1, 120);
        player->unk_18 = D_8010D8EC_slot_synch[chr] | D_8010D90C_slot_synch[index];
    } else {
        func_800E5A00_minigame(object, 13, func_80017BB8_main(chr, D_8010D90C_slot_synch[1]), 1, 120);
        player->unk_18 = D_8010D8EC_slot_synch[chr] | D_8010D90C_slot_synch[1];
    }
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, D_8010D90C_slot_synch[2]), 1, 120);
    func_800E5690_minigame(object, 0);
    func_800E149C_minigame(object, 0, 2);
    player->unk_04 = -1;
    player->unk_0A = 0;
    player->unk_08 = 0;
    player->unk_0C = player->unk_10 = player->unk_14 = 0.0f;
    object->func = func_80106E8C_slot_synch;
}

void func_80106878_slot_synch(omObjData *object) {
    UnkSlotSynch *team = (UnkSlotSynch *)func_8010C428_slot_synch(object);
    UnkSlotMachine *machine;
    func_800E1BA8_minigame_ObjData *data0;
    func_800E1BA8_minigame_ObjData *data1;
    s16 result0;
    s16 result1;

    switch (team->unk_12) {
        case 0:
            if (func_800E6E8C_minigame() == 2) {
                func_801089F8_slot_synch(team->unk_08->unk_00);
                func_801089F8_slot_synch(team->unk_0C->unk_00);
                machine = &D_8010DF7C_slot_synch[team->unk_08->unk_00];
                if (machine->unk_20 != -1) {
                    HuAudFXStop((s16)machine->unk_20);
                    machine->unk_20 = -1;
                }
                machine->unk_20 = HuAudFXPlay(team->unk_10 == 0 ? 0x38F : 0x395);
                team->unk_14 = 0;
                team->unk_12 = 1;
            } else if (func_800E6E8C_minigame() == 3 || func_800E6E8C_minigame() == 4) {
                func_80108CD0_slot_synch(team->unk_08->unk_00);
                func_80108CD0_slot_synch(team->unk_0C->unk_00);
            }
            break;
        case 1:
            if (func_800E6E8C_minigame() != 2) {
                team->unk_1C = 0;
                team->unk_14 = 0;
                team->unk_12 = 0;
            }
            if (team->unk_14 >= 30) {
                team->unk_1C = 1;
                team->unk_14 = 0;
                team->unk_12 = 2;
            }
            break;
        case 2:
            if (func_80108A7C_slot_synch(team->unk_08->unk_00) && func_80108A7C_slot_synch(team->unk_0C->unk_00)) {
                if (func_800E6E8C_minigame() == 2) {
                    machine = &D_8010DF7C_slot_synch[team->unk_08->unk_00];
                    if (machine->unk_20 != -1) {
                        HuAudFXStop((s16)machine->unk_20);
                        machine->unk_20 = -1;
                    }
                }
                team->unk_1C = 0;
                result0 = func_80108AA8_slot_synch(team->unk_08->unk_00);
                result1 = func_80108AA8_slot_synch(team->unk_0C->unk_00);
                if (func_800E6E8C_minigame() == 3) {
                    func_80108CD0_slot_synch(team->unk_08->unk_00);
                    func_80108CD0_slot_synch(team->unk_0C->unk_00);
                }
                if (result0 == result1) {
                    team->unk_1A = result0;
                } else {
                    team->unk_1A = 4;
                }
                team->unk_18 = func_80109FA4_slot_synch(team->unk_10, team->unk_1A);
                team->unk_14 = 0;
                team->unk_12 = 3;
            } else if (func_800E6E8C_minigame() != 2) {
                team->unk_1C = 0;
                data0 = team->unk_00->data;
                data1 = team->unk_04->data;
                if (data0->unk38 == 1000.0f && data1->unk38 == 1000.0f) {
                    if (func_800E6E8C_minigame() == 3) {
                        func_80108CD0_slot_synch(team->unk_08->unk_00);
                        func_80108CD0_slot_synch(team->unk_0C->unk_00);
                    }
                    team->unk_14 = 0;
                    team->unk_12 = 0;
                }
            }
            break;
        case 3:
            if (func_8010A178_slot_synch(team->unk_18)) {
                if (team->unk_1A != 4) {
                    func_8010800C_slot_synch(team->unk_1A, team->unk_10);
                }
                if (team->unk_1A != 3 && team->unk_1A != 4) {
                    func_800E5690_minigame(team->unk_00, 38);
                    func_800E5690_minigame(team->unk_04, 38);
                } else {
                    func_800E5690_minigame(team->unk_00, 39);
                    func_800E5690_minigame(team->unk_04, 39);
                }
                team->unk_14 = 0;
                team->unk_12 = 4;
            }
            break;
        case 4:
            if (team->unk_14 >= 30.0f) {
                func_800E5690_minigame(team->unk_00, 0);
                func_800E5690_minigame(team->unk_04, 0);
                team->unk_14 = 0;
                team->unk_12 = 0;
            }
            break;
    }
    team->unk_14++;
    if (team->unk_16 >= 100) {
        team->unk_16 = 99;
    } else if (team->unk_16 < 0) {
        team->unk_16 = 0;
    }
    func_8010AA9C_slot_synch(team->unk_10, team->unk_16);
}

void func_80106CCC_slot_synch(s16 arg0, s32 arg1) {
    UnkSlotSynch *slot = &D_8010DF5C_slot_synch[arg0];
    slot->unk_16 += arg1;
}

s16 func_80106CF0_slot_synch(s16 arg0) {
    UnkSlotSynch *slot = &D_8010DF5C_slot_synch[arg0];

    return slot->unk_12;
}

void func_80106D0C_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotSynch *team = &D_8010DF5C_slot_synch[arg0];

    switch (arg1) {
        case 1:
            omVibrate(team->unk_08->unk_1C, 5, 0, 5);
            omVibrate(team->unk_0C->unk_1C, 5, 0, 5);
            break;
        case 2:
            omVibrate(team->unk_08->unk_1C, 2, 3, 10);
            omVibrate(team->unk_0C->unk_1C, 2, 3, 10);
            break;
        case 3:
            omVibrate(team->unk_08->unk_1C, 10, 0, 10);
            omVibrate(team->unk_0C->unk_1C, 10, 0, 10);
            break;
        case 4:
            omVibrate(team->unk_08->unk_1C, 2, 2, 20);
            omVibrate(team->unk_0C->unk_1C, 2, 2, 20);
            break;
        case 5:
            omVibrate(team->unk_08->unk_1C, 20, 0, 20);
            omVibrate(team->unk_0C->unk_1C, 20, 0, 20);
            break;
        default:
            omVibrate(team->unk_08->unk_1C, 30, 0, 30);
            omVibrate(team->unk_0C->unk_1C, 30, 0, 30);
            break;
    }
}

void func_80106E8C_slot_synch(omObjData *object) {
    s16 done = TRUE;
    UnkSlotPlayer *player = (UnkSlotPlayer *)func_8010C428_slot_synch(object);
    UnkSlotSynch *team = &D_8010DF5C_slot_synch[player->unk_02];
    u16 btn;
    u16 btnDown;
    s16 stickX;
    s16 stickY;

    if (player->unk_22 != 0) {
        func_80107108_slot_synch(object);
    }
    if (player->unk_04 != -1) {
        switch (player->unk_04) {
            case 0:
                func_800E5690_minigame(object, 13);
                func_80017790_main(object->model[0], 2, player->unk_20, D_8010D870_slot_synch[player->unk_20]);
                func_80045F1C_main(player->unk_18, -1, player->unk_1C);
                break;
            case 1:
                func_800E5690_minigame(object, 14);
                func_80017790_main(object->model[0], 2, player->unk_20, D_8010D890_slot_synch[player->unk_20]);
                break;
        }
        player->unk_04 = -1;
    }
    player->unk_0C = object->trans.x;
    player->unk_10 = object->trans.y;
    player->unk_14 = object->trans.z;
    if (func_80108A7C_slot_synch(player->unk_00) != 0) {
        done = FALSE;
    }
    if (team->unk_1C == 0 || !done) {
        btn = D_800CDA7C_main[player->unk_1E];
        btnDown = D_800D5558_main[player->unk_1E];
        D_800CDA7C_main[player->unk_1E] = 0;
        D_800D5558_main[player->unk_1E] = 0;
    } else {
        btnDown = 0;
        btn = 0;
    }
    stickX = D_800CBB6E_main[player->unk_1E];
    stickY = D_800D20A1_main[player->unk_1E];
    D_800CBB6E_main[player->unk_1E] = 0;
    D_800D20A1_main[player->unk_1E] = 0;
    func_800DDD94_minigame(object);
    D_800CBB6E_main[player->unk_1E] = stickX;
    D_800D20A1_main[player->unk_1E] = stickY;
    if (team->unk_1C == 0) {
        D_800CDA7C_main[player->unk_1E] = btn;
        D_800D5558_main[player->unk_1E] = btnDown;
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    player->unk_0A++;
}

void func_80107108_slot_synch(omObjData *object) {
    UnkSlotPlayer *player = (UnkSlotPlayer *)func_8010C428_slot_synch(object);
    UnkSlotSynch *team = &D_8010DF5C_slot_synch[player->unk_02];
    UnkSlotPlayer *partner;
    u16 spin;
    s16 result;
    s16 index;

    if (team->unk_08 == player) {
        partner = team->unk_0C;
    } else {
        partner = team->unk_08;
    }
    D_800CDA7C_main[player->unk_1E] = 0;
    D_800D5558_main[player->unk_1E] = 0;
    spin = D_8010D928_slot_synch[player->unk_20];
    switch (team->unk_12) {
        case 0:
            if (player->unk_2C != -1) {
                break;
            }
            if (partner->unk_22 == 0) {
                player->unk_2A = 150;
                player->unk_2C = D_8010D91C_slot_synch[(u8)(rand8() % 3)];
                break;
            }
            if ((u8)(rand8() % 100) < player->unk_24 * 15 + 60) {
                player->unk_28 = 0;
            } else {
                player->unk_28 = 1;
            }
            player->unk_2A = (u8)(rand8() % 30) + 75 - player->unk_24 * 12;
            if (team->unk_1E == -1) {
                index = (u8)(rand8() % 100) * (1.0f - player->unk_24 * 0.075f);
                index /= 25;
                team->unk_1E = player->unk_2C = D_8010D91C_slot_synch[index];
            } else {
                player->unk_2C = team->unk_1E;
                if (abs(player->unk_2A - partner->unk_2A) < 9.0f) {
                    if (partner->unk_2A < player->unk_2A) {
                        player->unk_2A = player->unk_2A + 9.0f;
                    } else {
                        player->unk_2A = player->unk_2A - 9.0f;
                    }
                }
            }
            break;
        case 1:
            player->unk_0A = 0;
            break;
        case 2:
            if (func_80108A7C_slot_synch(player->unk_00) == 0) {
                func_80108AA8_slot_synch(player->unk_00);
                if (player->unk_0A > player->unk_2A) {
                    if (player->unk_28 == 0) {
                        result = func_80108B74_slot_synch(player->unk_00, spin);
                        if (result == player->unk_2C) {
                            func_80108D14_slot_synch(player->unk_00, result);
                            D_800D5558_main[player->unk_1E] |= A_BUTTON;
                        }
                    } else if (func_80108B74_slot_synch(player->unk_00, spin) != player->unk_2C) {
                        D_800D5558_main[player->unk_1E] |= A_BUTTON;
                    }
                } else if (partner->unk_22 == 0 && func_80108A7C_slot_synch(partner->unk_00)) {
                    player->unk_0A = 0;
                    if (func_80108B74_slot_synch(player->unk_00, spin) == func_80108AA8_slot_synch(partner->unk_00)) {
                        func_80108D14_slot_synch(player->unk_00, func_80108AA8_slot_synch(partner->unk_00));
                        D_800D5558_main[player->unk_1E] |= A_BUTTON;
                    }
                }
            }
            player->unk_26 = func_80108AA8_slot_synch(player->unk_00);
            break;
        case 3:
            if (player->unk_2C != -1) {
                player->unk_28 = 0;
                player->unk_2A = 0;
                team->unk_1E = player->unk_2C = -1;
            }
            break;
    }
}

void func_801075D4_slot_synch(void) {
    s16 i;
    s16 count;
    s32 priority = 0xFFFF;

    func_80107A88_slot_synch();
    func_80108238_slot_synch();
    func_80108D3C_slot_synch();
    D_8010DF66_slot_synch[0] = priority;
    priority--;
    D_8010DF66_slot_synch[1] = priority;
    priority--;
    count = 12;
    for (i = 0; i < count; i++) {
        func_80107B00_slot_synch(D_8010D938_slot_synch[i].x, D_8010D938_slot_synch[i].y, D_8010D938_slot_synch[i].unk_05, 0,
                                 priority);
        priority--;
    }
    count = 12;
    for (i = 0; i < count; i++) {
        func_80107B00_slot_synch(D_8010D980_slot_synch[i].x, D_8010D980_slot_synch[i].y, D_8010D980_slot_synch[i].unk_05, 1,
                                 priority);
        priority--;
    }
    D_8010DF66_slot_synch[2] = priority;
    priority--;
    D_8010DF66_slot_synch[3] = priority;
    priority--;
    func_80107BAC_slot_synch();
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(0x1D, 16, 0, -1, func_80107794_slot_synch);
    func_800E1490_minigame(0);
}

void func_80107794_slot_synch(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;
    s16 group;

    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    func_800E139C_minigame(object, 0.0f, -2000.0f, -2000.0f, 2000.0f, 2000.0f);
    group = HuSprGrpCreate(4, 0);
    D_8010DF8C_slot_synch[3] = func_8010A2C4_slot_synch(0x350007);
    HuSprGrpMemberSet(group, 0, D_8010DF8C_slot_synch[3], 0);
    HuSprPosSet(group, 0, 0, 0);
    func_800550F4_main(group, 0, 0);
    func_80054FF8_main(group, 0, 0);
    HuSprAttrSet(group, 0, 0x580C);
    HuSprPriSet(group, 0, D_8010DF66_slot_synch[0]);
    D_8010DF8C_slot_synch[8] = func_8010A2C4_slot_synch(0x350008);
    HuSprGrpMemberSet(group, 1, D_8010DF8C_slot_synch[8], 0);
    HuSprPosSet(group, 1, 0, 84);
    func_800550F4_main(group, 1, 0);
    func_80054FF8_main(group, 1, 0);
    HuSprAttrSet(group, 1, 0x580C);
    HuSprPriSet(group, 1, D_8010DF66_slot_synch[1]);
    D_8010DF8C_slot_synch[9] = func_8010A2C4_slot_synch(0x350009);
    HuSprGrpMemberSet(group, 2, D_8010DF8C_slot_synch[9], 0);
    HuSprPosSet(group, 2, 160, 0);
    func_800550F4_main(group, 2, 0);
    func_80054FF8_main(group, 2, 0);
    HuSprAttrSet(group, 2, 0x580C);
    HuSprPriSet(group, 2, D_8010DF66_slot_synch[2]);
    D_8010DF8C_slot_synch[0] = func_8010A2C4_slot_synch(0x35000A);
    HuSprGrpMemberSet(group, 3, D_8010DF8C_slot_synch[0], 0);
    HuSprPosSet(group, 3, 0, 138);
    func_800550F4_main(group, 3, 0);
    func_80054FF8_main(group, 3, 0);
    HuSprAttrSet(group, 3, 0x580C);
    HuSprPriSet(group, 3, D_8010DF66_slot_synch[3]);
    object->func = func_80107A80_slot_synch;
}

void func_80107A80_slot_synch(omObjData *object) {
}

void func_80107A88_slot_synch(void) {
    memset(&D_8010DF70_slot_synch, 0, sizeof(D_8010DF70_slot_synch));
    D_8010DF70_slot_synch.unk_06 = 0;
    D_8010DF70_slot_synch.unk_08 = HuMemAllocTag(0x420, TAG_OVERLAY);
    memset(D_8010DF70_slot_synch.unk_08, 0, 0x420);
    D_8010DF70_slot_synch.unk_00 = omAddObj(0x1C, 0, 0, -1, NULL);
}

s16 func_80107B00_slot_synch(f32 x, f32 y, u8 arg2, u8 arg3, u16 arg4) {
    UnkSlotSprite *sprite;
    s16 index;

    if (D_8010DF70_slot_synch.unk_00->func != NULL || D_8010DF70_slot_synch.unk_06 >= 24) {
        return -1;
    }
    index = D_8010DF70_slot_synch.unk_06;
    sprite = &D_8010DF70_slot_synch.unk_08[index];
    sprite->unk_00 = index;
    sprite->unk_06 = arg2;
    sprite->unk_07 = arg3;
    sprite->unk_02 = arg4;
    sprite->unk_1C = sprite->unk_14 = sprite->unk_24 = x;
    sprite->unk_20 = sprite->unk_18 = sprite->unk_28 = y;
    sprite->unk_08 = 0;
    sprite->unk_0A = 0;
    sprite->unk_09 = 0;
    sprite->unk_0B = 0;
    sprite->unk_0C = 0;
    sprite->unk_10 = 0;
    D_8010DF70_slot_synch.unk_06++;
    return index;
}

void func_80107BAC_slot_synch(void) {
    s16 anims[4];
    UnkSlotSprite *sprite;
    s16 i;
    s16 group;

    anims[0] = D_8010DF8C_slot_synch[4] = func_8010A2C4_slot_synch(0x350003);
    anims[1] = D_8010DF8C_slot_synch[5] = func_8010A2C4_slot_synch(0x350005);
    anims[2] = D_8010DF8C_slot_synch[6] = func_8010A2C4_slot_synch(0x350004);
    anims[3] = D_8010DF8C_slot_synch[7] = func_8010A2C4_slot_synch(0x350006);
    group = D_8010DF70_slot_synch.unk_04 = HuSprGrpCreate(D_8010DF70_slot_synch.unk_06, 0);
    sprite = D_8010DF70_slot_synch.unk_08;
    for (i = 0; i < D_8010DF70_slot_synch.unk_06; i++, sprite++) {
        HuSprScaleSet(group, sprite->unk_00, 0.75f, 0.75f);
        HuSprGrpMemberSet(group, sprite->unk_00, anims[sprite->unk_06], 0);
        func_8010A308_slot_synch(group, sprite->unk_00, sprite->unk_24, sprite->unk_28);
        func_800550F4_main(group, sprite->unk_00, 0);
        func_80054FF8_main(group, sprite->unk_00, 0);
        HuSprAttrSet(group, sprite->unk_00, 0x4000580C);
        HuSprPriSet(group, sprite->unk_00, sprite->unk_02);
    }
    D_8010DF70_slot_synch.unk_00->func = func_80107D54_slot_synch;
}

void func_80107D54_slot_synch(omObjData *object) {
    UnkSlotSprite *sprite = D_8010DF70_slot_synch.unk_08;
    s16 i;
    f32 bounce;

    for (i = 0; i < D_8010DF70_slot_synch.unk_06; i++, sprite++) {
        sprite->unk_1C = sprite->unk_24;
        sprite->unk_20 = sprite->unk_28;
        switch (sprite->unk_08) {
            case 1:
                if (sprite->unk_0B != 0) {
                    sprite->unk_0B--;
                    sprite->unk_04 = 0;
                    break;
                }
                if (sprite->unk_0A & 0x80) {
                    if ((++sprite->unk_0A & 0x7F) >= 2) {
                        sprite->unk_0A = 2;
                    }
                } else if ((--sprite->unk_0A & 0x7F) == 0) {
                    sprite->unk_0A = 0x80;
                }
                func_80054FF8_main(D_8010DF70_slot_synch.unk_04, sprite->unk_00, (s16)(u8)(sprite->unk_0A & 2));
                bounce = sindf(sprite->unk_04 * 25);
                sprite->unk_24 = sprite->unk_14;
                sprite->unk_28 = sprite->unk_18 - fabs(bounce) * sprite->unk_10;
                sprite->unk_09 = 1;
                if (sprite->unk_04 >= sprite->unk_0C) {
                    sprite->unk_04 = 0;
                    sprite->unk_08++;
                }
                break;
            case 2:
                if (sprite->unk_28 < sprite->unk_18 - 1.0f) {
                    if (sprite->unk_0A & 0x80) {
                        if ((++sprite->unk_0A & 0x7F) >= 2) {
                            sprite->unk_0A = 2;
                        }
                    } else if ((--sprite->unk_0A & 0x7F) == 0) {
                        sprite->unk_0A = 0x80;
                    }
                    func_80054FF8_main(D_8010DF70_slot_synch.unk_04, sprite->unk_00, (s16)(u8)(sprite->unk_0A & 2));
                    sprite->unk_28 += 1.0f;
                } else {
                    func_80054FF8_main(D_8010DF70_slot_synch.unk_04, sprite->unk_00, 0);
                    sprite->unk_28 = sprite->unk_18;
                    sprite->unk_04 = 0;
                    sprite->unk_08 = 0;
                }
                sprite->unk_09 = 1;
                break;
        }
        if (sprite->unk_09 != 0) {
            func_8010A308_slot_synch(D_8010DF70_slot_synch.unk_04, sprite->unk_00, sprite->unk_24, sprite->unk_28);
            sprite->unk_09 = 0;
        }
        sprite->unk_04++;
    }
}

void func_8010800C_slot_synch(u8 arg0, u8 arg1) {
    UnkSlotSprite *sprite = D_8010DF70_slot_synch.unk_08;
    s16 i;

    for (i = 0; i < D_8010DF70_slot_synch.unk_06; i++, sprite++) {
        if (sprite->unk_06 == arg0 && sprite->unk_07 == arg1 && sprite->unk_08 == 0) {
            sprite->unk_08 = 1;
            sprite->unk_04 = 0;
            sprite->unk_0A = 0x80;
            sprite->unk_0C = (f32)(u8)(rand8() % 100) * 0.01 * 30.0 + 30.0;
            sprite->unk_0B = rand8() % 22;
            sprite->unk_10 = (f32)(u8)(rand8() % 100) * 0.01 * 5.0 + 5.0;
        }
    }
}

void func_80108238_slot_synch(void) {
    UnkSlotMachine *machine;
    s16 i;
    s16 model1 = -1;
    s16 model0 = -1;

    machine = D_8010DF7C_slot_synch = HuMemAllocTag(sizeof(UnkSlotMachine) * 4, TAG_OVERLAY);
    memset(machine, 0, sizeof(UnkSlotMachine) * 4);
    for (i = 0; i < 4; i++, machine++) {
        machine->unk_03 = D_8010D9C8_slot_synch[i];
        if (machine->unk_03 == 0) {
            if (model0 != -1) {
                machine->unk_00 = Hu3DModelLink(model0);
            } else {
                model0 = machine->unk_00 = func_8000B108_main(0x350000, 0xB9);
            }
        } else {
            if (model1 != -1) {
                machine->unk_00 = Hu3DModelLink(model1);
            } else {
                model1 = machine->unk_00 = func_8000B108_main(0x350001, 0xB9);
            }
        }
        machine->unk_02 = i;
        machine->unk_04 = i % 2;
        machine->unk_0A = 0;
        machine->unk_05 = 0;
        machine->unk_06 = 0;
        machine->unk_0C = 0;
        machine->unk_10 = 0.0f;
        machine->unk_08 = -1;
        machine->unk_14 = 0.0f;
        machine->unk_18 = 0.5f;
        machine->unk_1C = 14.0f;
        machine->unk_20 = -1;
        machine->unk_24 = D_8010D7F0_slot_synch[i].x;
        machine->unk_2C = D_8010D7F0_slot_synch[i].z;
        machine->unk_28 = 280.0f;
        machine->unk_30 = 0.0f;
        machine->unk_34 = machine->unk_38 = 0.0f;
    }
    omAddObj(0x1A, 0, 0, -1, func_80108428_slot_synch);
}

void func_80108428_slot_synch(omObjData *object) {
    UnkSlotMachine *machine = D_8010DF7C_slot_synch;
    Vec pos;
    f32 angle;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++, machine++) {
        switch (machine->unk_0C) {
            case 0:
                break;
            case 1:
                machine->unk_14 += machine->unk_18;
                if (machine->unk_14 >= machine->unk_1C) {
                    machine->unk_14 = machine->unk_1C;
                    machine->unk_0C = 2;
                    machine->unk_0A = 0;
                }
                break;
            case 2:
                break;
            case 3:
                machine->unk_28 += machine->unk_10;
                machine->unk_10 -= 6.0;
                if (machine->unk_28 <= 280.0) {
                    machine->unk_28 = 280.0f;
                    machine->unk_0A = 0;
                    machine->unk_0C = 0;
                }
                break;
            case 4:
                func_8001C258_main(machine->unk_00, 4, 4);
                pos.x = machine->unk_24;
                pos.y = machine->unk_28;
                pos.z = machine->unk_2C;
                func_8010AD68_slot_synch(&pos, NULL, NULL, 1.0f, D_8010D86C_slot_synch.rgba);
                machine->unk_0C = 5;
                break;
            case 5:
                break;
        }
        angle = machine->unk_30 + 45.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        } else if (angle < 0.0f) {
            angle += 360.0f;
        }
        machine->unk_05 = angle / 90.0f;
        if (machine->unk_05 >= 4) {
            machine->unk_05 -= 4;
        }
        machine->unk_06 = func_80108C88_slot_synch(machine->unk_02, machine->unk_05);
        machine->unk_30 += machine->unk_14;
        if (machine->unk_30 >= 360.0f) {
            machine->unk_30 -= 360.0f;
        }
        if (func_80108848_slot_synch(machine->unk_02) != -1 && (machine->unk_0C == 1 || machine->unk_0C == 2)) {
            func_8004AC98_main(0x38E, i);
            if (machine->unk_08 == -1) {
                machine->unk_14 = 0.0f;
                machine->unk_30 = D_8010D840_slot_synch[machine->unk_05];
            } else {
                machine->unk_14 = 0.0f;
                for (j = 0; j < 4; j++) {
                    machine->unk_30 = j * 90;
                    angle = machine->unk_30 + 45.0f;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    } else if (angle < 0.0f) {
                        angle += 360.0f;
                    }
                    machine->unk_05 = angle / 90.0f;
                    if (machine->unk_05 >= 4) {
                        machine->unk_05 -= 4;
                    }
                    machine->unk_06 = func_80108C88_slot_synch(machine->unk_02, machine->unk_05);
                    if (machine->unk_06 == machine->unk_08) {
                        break;
                    }
                }
            }
            machine->unk_28 = 340.0f;
            machine->unk_10 = 0.0f;
            machine->unk_08 = -1;
            machine->unk_0A = 0;
            machine->unk_0C = 3;
        }
        Hu3DModelPosSet(machine->unk_00, machine->unk_24, machine->unk_28, machine->unk_2C);
        Hu3DModelRotSet(machine->unk_00, machine->unk_30, machine->unk_34, machine->unk_38);
        machine->unk_0A++;
    }
}

s16 func_80108848_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];
    func_800E1BA8_minigame_ObjData *data;
    UnkSlotPlayer *player;
    omObjData *obj;
    f32 height;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_800EC598_minigame[i];
        data = obj->data;
        player = (UnkSlotPlayer *)func_8010C428_slot_synch(obj);
        // The original checks the x distance twice.
        if (fabs(obj->trans.x - machine->unk_24) > 50.0 || fabs(obj->trans.x - machine->unk_24) > 50.0) {
            continue;
        }
        if (machine->unk_0C == 1 || machine->unk_0C == 2) {
            height = D_8010D9D0_slot_synch[player->unk_20];
        } else {
            height = D_8010D9D0_slot_synch[player->unk_20] + 50.0;
        }
        if (height + obj->trans.y >= machine->unk_28 && height + player->unk_10 <= machine->unk_28) {
            obj->trans.y = machine->unk_28 - D_8010D9D0_slot_synch[player->unk_20] * 1.1;
            data->unk38 = 0.0f;
            return i;
        }
    }
    return -1;
}

void func_801089F8_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];
    f32 t;

    if (func_80108A7C_slot_synch(arg0)) {
        t = D_8010DF50_slot_synch / 900.0f;
        machine->unk_1C = func_8010C384_slot_synch(t, 30.0f, 14.0f);
        machine->unk_0C = 1;
        machine->unk_0A = 0;
    }
}

s16 func_80108A7C_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    return machine->unk_0C == 0;
}

s16 func_80108AA8_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];
    f32 angle = machine->unk_30 + 45.0f;
    s16 quadrant;

    if (angle > 360.0f) {
        angle -= 360.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    }
    quadrant = angle / 90.0f;
    return func_80108C88_slot_synch(arg0, quadrant);
}

s16 func_80108B74_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];
    s16 quadrant;
    f32 angle = machine->unk_30 + arg1 * machine->unk_14 + 45.0f;

    while (angle > 360.0f) {
        angle -= 360.0f;
    }
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    quadrant = angle / 90.0f;
    return func_80108C88_slot_synch(arg0, quadrant);
}

s16 func_80108C88_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    return D_8010D854_slot_synch[machine->unk_03][arg1];
}

void func_80108CD0_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    if (machine->unk_0C != 4 && machine->unk_0C != 5) {
        machine->unk_0C = 4;
        machine->unk_0A = 0;
    }
}

void func_80108D14_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    machine->unk_08 = arg1;
}

void func_80108D3C_slot_synch(void) {
    s16 heights[256];
    UnkSlotReel *reel;
    UnkSlotReelRow *row;
    HmfData *hmf;
    Vtx *vtx;
    s16 i;
    s16 j;
    s16 k;
    s16 count;
    s16 temp;

    reel = D_8010DF80_slot_synch = HuMemAllocTag(sizeof(UnkSlotReel) * 2, TAG_OVERLAY);
    memset(reel, 0, sizeof(UnkSlotReel) * 2);
    for (i = 0; i < 2; i++, reel++) {
        reel->unk_00 = func_8000B108_main(0x350002, 0xB9);
        Hu3DModelPosSet(reel->unk_00, D_8010D820_slot_synch[i].x, D_8010D820_slot_synch[i].y,
                        D_8010D820_slot_synch[i].z);
        Hu3DModelScaleSet(reel->unk_00, 1.0f, 0.85f, 1.0f);
        func_8001C954_main(reel->unk_00);
        hmf = Hu3DData[reel->unk_00].hmf;
        reel->unk_02 = i;
        reel->unk_04 = 0;
        reel->unk_08 = -75.0f;
        reel->unk_0C = 75.0f;
        reel->unk_10 = 0.75f;
        reel->unk_14 = 0.0f;
        if (i == 0) {
            vtx = hmf->unk40;
            count = 0;
            for (j = 0; j < hmf->unk18; j++, vtx++) {
                for (k = 0; k < count; k++) {
                    if (heights[k] == vtx->v.ob[1]) {
                        break;
                    }
                }
                if (k >= count) {
                    heights[k] = vtx->v.ob[1];
                    count++;
                }
                if (count >= 256) {
                    osSyncPrintf("VTX OVER!! \n");
                }
            }
            for (j = 0; j < count - 1; j++) {
                for (k = j + 1; k < count; k++) {
                    if (heights[j] < heights[k]) {
                        temp = heights[j];
                        heights[j] = heights[k];
                        heights[k] = temp;
                    }
                }
            }
            reel->unk_18 = count;
            row = reel->unk_1C = HuMemAllocTag(count * sizeof(UnkSlotReelRow), TAG_OVERLAY);
            for (j = 0; j < reel->unk_18; j++, row++) {
                row->unk_90 = heights[j];
                row->unk_92 = 0;
            }
            vtx = hmf->unk40;
            for (j = 0; j < hmf->unk18; j++, vtx++) {
                for (k = 0; k < reel->unk_18; k++) {
                    row = &reel->unk_1C[k];
                    if (vtx->v.ob[1] == row->unk_90) {
                        row->unk_00[row->unk_92] = j;
                        row->unk_92++;
                        break;
                    }
                    if (row->unk_92 >= 72) {
                        osSyncPrintf("VTX H OVER!! \n");
                    }
                }
            }
        } else {
            reel->unk_18 = D_8010DF80_slot_synch->unk_18;
            reel->unk_1C = D_8010DF80_slot_synch->unk_1C;
        }
    }
    omSetStatBit(omAddObj(0x1B, 0, 0, -1, func_801091D8_slot_synch), 0xA0);
}

void func_801091D8_slot_synch(omObjData *object) {
    UnkSlotReel *reel = D_8010DF80_slot_synch;
    s32 i;

    for (i = 0; i < 2; i++, reel++) {
        if (omPauseChk() + D_800D6A90_main == 0 && reel->unk_04 == 1) {
            reel->unk_08 += reel->unk_14;
            if (reel->unk_08 >= 359.99999046325684 || reel->unk_08 <= -120.00000476837158) {
                reel->unk_14 = 0.0f;
                reel->unk_04 = 0;
            }
        }
        func_801092B8_slot_synch(reel);
    }
}

void func_801092B8_slot_synch(UnkSlotReel *reel) {
    UnkSlotReelRow *row = reel->unk_1C;
    HmfData *hmf = Hu3DData[reel->unk_00].hmf;
    Vtx *src = hmf->unk40;
    Vtx *dst = hmf->unk44[D_800D2008_main];
    f32 dist;
    f32 scale;
    s32 i;
    s32 j;

    for (i = 0; i < reel->unk_18; i++, row++) {
        dist = fabsf(reel->unk_08 - row->unk_90 * 0.85f);
        if (dist > reel->unk_0C) {
            scale = 0.0f;
        } else {
            scale = 1.0f - dist / reel->unk_0C;
        }
        if (scale >= 1.0f) {
            scale = 1.0f;
        } else if (scale <= 0.0f) {
            scale = 0.0f;
        }
        if (scale != 0.0f) {
            scale = scale * reel->unk_10 + 1.0f;
            for (j = 0; j < row->unk_92; j++) {
                dst[row->unk_00[j]].v.ob[0] = src[row->unk_00[j]].v.ob[0] * scale;
                dst[row->unk_00[j]].v.ob[2] = src[row->unk_00[j]].v.ob[2] * scale;
            }
        } else {
            for (j = 0; j < row->unk_92; j++) {
                dst[row->unk_00[j]].v = src[row->unk_00[j]].v;
            }
        }
    }
}

void func_801094E0_slot_synch(s16 arg0, f32 arg1, f32 arg2) {
    UnkSlotReel *reel = &D_8010DF80_slot_synch[arg0];

    reel->unk_04 = 1;
    reel->unk_08 = arg1;
    reel->unk_14 = arg2;
}

void func_80109508_slot_synch(void) {
    UnkSlotSpin *spin;
    s32 i;
    s32 j;

    spin = D_8010DF88_slot_synch = HuMemAllocTag(sizeof(UnkSlotSpin) * 5, TAG_OVERLAY);
    memset(spin, 0, sizeof(UnkSlotSpin) * 5);
    for (i = 0; i < 5; i++, spin++) {
        spin->unk_00 = 0;
        spin->unk_01 = 0;
        spin->unk_02 = 0;
        spin->unk_03 = 0;
        spin->unk_26 = 0;
        spin->unk_2A = 0;
        spin->unk_28 = 0;
        spin->unk_2C = 0;
        spin->unk_30 = 0;
        if (i == 0) {
            for (j = 0; j < 4; j++) {
                spin->unk_04[j] = func_8000B108_main(D_8010D9F0_slot_synch[j], 0x299);
                func_8001C258_main(spin->unk_04[j], 4, 4);
                spin->unk_0C[j][0] = Hu3DData[spin->unk_04[j]].motId;
                spin->unk_0C[j][1] = func_8010C47C_slot_synch(D_8010DA00_slot_synch[j]);
                spin->unk_0C[j][2] = func_8010C47C_slot_synch(D_8010DA10_slot_synch[j]);
            }
            spin->unk_24 = func_8000B108_main(9, 0x99);
            func_8001C258_main(spin->unk_24, 4, 4);
        } else {
            for (j = 0; j < 4; j++) {
                spin->unk_04[j] = Hu3DModelLink(D_8010DF88_slot_synch->unk_04[j]);
                func_8001C258_main(spin->unk_04[j], 4, 4);
                spin->unk_0C[j][0] = D_8010DF88_slot_synch->unk_0C[j][0];
                spin->unk_0C[j][1] = D_8010DF88_slot_synch->unk_0C[j][1];
                spin->unk_0C[j][2] = D_8010DF88_slot_synch->unk_0C[j][2];
            }
            spin->unk_24 = Hu3DModelLink(D_8010DF88_slot_synch->unk_24);
            func_8001C258_main(spin->unk_24, 4, 4);
        }
    }
    D_8010DF84_slot_synch = omAddObj(0x19, 0, 6, -1, func_80109754_slot_synch);
}

void func_80109754_slot_synch(omObjData *object) {
    UnkSlotSpin *spin;
    HmfModel *model;
    Vec pos;
    Vec vel;
    Vec scale;
    f32 baseAngle;
    f32 angle;
    f32 shadowScale;
    s32 modelId;
    s32 i;
    s32 j;

    if (D_8010DF88_slot_synch == NULL) {
        return;
    }
    for (spin = D_8010DF88_slot_synch, i = 0; i < 5; i++, spin++) {
        if (spin->unk_00 == 0) {
            continue;
        }
        if (spin->unk_26 != 4) {
            modelId = spin->unk_04[spin->unk_26];
            model = &Hu3DData[modelId];
        } else {
            modelId = spin->unk_04[0];
            model = &Hu3DData[modelId];
        }
        switch (spin->unk_28) {
            case 0:
                spin->unk_34[1] += 20.0000002980232239;
                spin->unk_34[6] = spin->unk_34[7] = spin->unk_34[8] = spin->unk_34[1] / 255.000007152557373;
                if (spin->unk_34[1] >= 0.0f) {
                    func_8001C258_main(modelId, 4, 0);
                    func_8001C258_main(spin->unk_24, 4, 0);
                }
                if (spin->unk_03 == 0 && spin->unk_34[1] > 204.000008761882867) {
                    baseAngle = (f32)(u8)(rand8() % 100) * 0.01 * 360.0;
                    for (j = 0; j < 4; j++) {
                        pos.x = spin->unk_34[0];
                        pos.y = spin->unk_34[1];
                        pos.z = spin->unk_34[2];
                        angle = baseAngle + j * 90.0f;
                        vel.x = sindf(angle) * 100.0 * 0.100000001490116119;
                        vel.z = cosdf(angle) * 100.0 * 0.100000001490116119;
                        vel.y = 10.0f;
                        scale.x = scale.y = scale.z = 0.5f;
                        func_8010AD68_slot_synch(&pos, &vel, &scale, 1.0f, D_8010D868_slot_synch.rgba);
                    }
                    HuAudFXPlay(0x390);
                }
                if (spin->unk_34[1] >= 255.000007152557373) {
                    func_8004AC98_main(D_8010DA30_slot_synch[spin->unk_26], spin->unk_01);
                    if (spin->unk_26 == 3) {
                        func_80106D0C_slot_synch(spin->unk_01, 4);
                    } else {
                        func_80106D0C_slot_synch(spin->unk_01, 3);
                    }
                    spin->unk_34[1] = 255.0f;
                    spin->unk_2C = 20.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 1:
                if (model->motSpeed == 0.0f && spin->unk_2C < 0.0f) {
                    model->motSpeed = 1.0f;
                }
                if (spin->unk_01 == 0) {
                    spin->unk_34[0] += 1.49999996647238731;
                } else {
                    spin->unk_34[0] -= 1.49999996647238731;
                }
                spin->unk_34[2] += 10.0000001490116119;
                spin->unk_34[1] += spin->unk_2C;
                spin->unk_2C -= 1.63330006599426269531f;
                if (spin->unk_34[1] <= 0.0f) {
                    pos.x = spin->unk_34[0];
                    pos.y = spin->unk_34[1];
                    pos.z = spin->unk_34[2];
                    func_8010AD68_slot_synch(&pos, NULL, NULL, 1.0f, D_8010D864_slot_synch.rgba);
                    Hu3DMotionShiftSet(modelId, spin->unk_0C[spin->unk_26][0], 0, 5, 2);
                    func_80106CCC_slot_synch(spin->unk_01, D_8010D85C_slot_synch[spin->unk_26]);
                    spin->unk_02 = 1;
                    spin->unk_34[1] = 0.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 2:
                if (spin->unk_2A >= 7.5f) {
                    Hu3DMotionShiftSet(modelId, spin->unk_0C[spin->unk_26][2], 0, 5, 2);
                    model->motSpeed = D_8010DA20_slot_synch[spin->unk_26];
                    spin->unk_30 = 0.0f;
                    spin->unk_2A = 0;
                    spin->unk_28++;
                }
                break;
            case 3:
                spin->unk_30 += 3.50000000000000044;
                if (spin->unk_30 > 15.0000005960464478) {
                    spin->unk_30 = 15.000001f;
                }
                if (!(spin->unk_01 & 1)) {
                    spin->unk_34[0] -= spin->unk_30;
                    spin->unk_34[4] = func_8010C1C4_slot_synch(-90.0f, spin->unk_34[4], 15.0f);
                } else {
                    spin->unk_34[0] += spin->unk_30;
                    spin->unk_34[4] = func_8010C1C4_slot_synch(90.0f, spin->unk_34[4], 15.0f);
                }
                if (fabs(spin->unk_34[0]) >= 600.0) {
                    spin->unk_2A = 0;
                    spin->unk_28 = 64;
                }
                break;
            case 16:
                spin->unk_34[1] += 20.0000002980232239;
                if (spin->unk_34[1] >= 205.000007152557373) {
                    pos.x = spin->unk_34[0];
                    pos.y = spin->unk_34[1];
                    pos.z = spin->unk_34[2];
                    vel.x = vel.z = 0.0f;
                    vel.y = 10.0f;
                    func_8010AD68_slot_synch(&pos, &vel, NULL, 1.0f, D_8010D86C_slot_synch.rgba);
                    spin->unk_34[1] = 255.0f;
                    spin->unk_2C = 20.0f;
                    func_80106D0C_slot_synch(spin->unk_01, 2);
                    func_80106CCC_slot_synch(spin->unk_01, 0);
                    spin->unk_02 = 1;
                    spin->unk_2A = 0;
                    spin->unk_28 = 64;
                }
                break;
            case 64:
                spin->unk_00 = 0;
                spin->unk_28 = 0;
                spin->unk_2A = 0;
                func_8001C258_main(modelId, 4, 4);
                break;
        }
        Hu3DModelPosSet(modelId, spin->unk_34[0], spin->unk_34[1], spin->unk_34[2]);
        Hu3DModelRotSet(modelId, spin->unk_34[3], spin->unk_34[4], spin->unk_34[5]);
        Hu3DModelScaleSet(modelId, spin->unk_34[6], spin->unk_34[7], spin->unk_34[8]);
        shadowScale = 1.0 - spin->unk_34[1] / 765.000021457672119;
        if (shadowScale < 0.5f) {
            shadowScale = 0.5f;
        }
        Hu3DModelPosSet(spin->unk_24, spin->unk_34[0], 0.0f, spin->unk_34[2]);
        Hu3DModelScaleSet(spin->unk_24, shadowScale, 1.0f, shadowScale);
        spin->unk_2A++;
    }
}

s16 func_80109FA4_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotSpin *spin;
    HmfModel *model;
    s16 modelId;
    s32 i;

    if (D_8010DF88_slot_synch == NULL) {
        return -1;
    }
    for (spin = D_8010DF88_slot_synch, i = 0; i < 5; i++, spin++) {
        if (spin->unk_00 != 0) {
            continue;
        }
        spin->unk_00 = 1;
        spin->unk_01 = arg0;
        spin->unk_02 = 0;
        spin->unk_03 = 0;
        spin->unk_26 = arg1;
        spin->unk_2A = 0;
        spin->unk_2C = 0;
        spin->unk_34[0] = D_8010D820_slot_synch[spin->unk_01].x;
        spin->unk_34[2] = D_8010D820_slot_synch[spin->unk_01].z;
        spin->unk_34[1] = D_8010D820_slot_synch[spin->unk_01].y - 20.0000002980232239;
        spin->unk_34[3] = spin->unk_34[4] = spin->unk_34[5] = 0.0f;
        spin->unk_34[6] = spin->unk_34[7] = spin->unk_34[8] = 0.1f;
        if (spin->unk_26 != 4) {
            spin->unk_28 = 0;
            modelId = spin->unk_04[spin->unk_26];
            func_8001C258_main(modelId, 4, 4);
            Hu3DData[modelId].motId = spin->unk_0C[spin->unk_26][1];
            model = &Hu3DData[modelId];
            model->motTime = 0.0f;
            model->motSpeed = 0.0f;
            model->motAttr &= ~2;
        } else {
            spin->unk_28 = 16;
        }
        func_801094E0_slot_synch(spin->unk_01, spin->unk_34[1], 20.0f);
        return i;
    }
    return -1;
}

s16 func_8010A178_slot_synch(s16 arg0) {
    UnkSlotSpin *spin;

    if (D_8010DF88_slot_synch == NULL) {
        return 1;
    }
    spin = &D_8010DF88_slot_synch[arg0];
    if (spin->unk_00 == 0) {
        goto ret_one;
    }
    if (spin->unk_02 == 0) {
        goto ret_zero;
    }
ret_one:
    return 1;
ret_zero:
    return 0;
}

void func_8010A1D0_slot_synch(void) {
    UnkSlotSpin *spin = D_8010DF88_slot_synch;
    s32 i;
    s32 j;

    if (spin != NULL) {
        for (i = 0; i < 5; i++, spin++) {
            for (j = 0; j < 4; j++) {
                Hu3DData[spin->unk_04[j]].motId = 0xFF;
                Hu3DModelKill(spin->unk_04[j]);
                Hu3DMotionKill(spin->unk_0C[j][0]);
                Hu3DMotionKill(spin->unk_0C[j][1]);
                Hu3DMotionKill(spin->unk_0C[j][2]);
            }
            Hu3DModelKill(spin->unk_24);
        }
        HuMemFree(D_8010DF88_slot_synch);
        D_8010DF88_slot_synch = NULL;
        D_8010DF84_slot_synch->func = NULL;
    }
}

u16 func_8010A2C4_slot_synch(s32 file) {
    void *data = DataRead(file);
    u16 sprite = HuSprAnimRead(data);

    DataClose(data);
    return sprite;
}

void func_8010A308_slot_synch(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *spr = HuSprGet(arg0, arg1);

    if (spr->pos.x != arg2 || spr->pos.y != arg3) {
        grp->dirty = 1;
        spr->pos.x = arg2;
        spr->pos.y = arg3;
    }
}

void func_8010A39C_slot_synch(void) {
    UnkSlotLight *light;
    s32 i;

    D_8010DF8C_slot_synch[10] = func_8010A2C4_slot_synch(0x35000C);
    D_8010DF8C_slot_synch[11] = func_8010A2C4_slot_synch(0x35000B);
    D_8010DF8C_slot_synch[12] = func_8010A2C4_slot_synch(0x2D);
    light = D_8010DF90_slot_synch = HuMemAllocTag(sizeof(UnkSlotLight) * 2, TAG_OVERLAY);
    for (i = 0; i < 2; i++, light++) {
        light->unk_00 = -1;
        light->unk_02 = D_8010D838_slot_synch[i].x;
        light->unk_04 = D_8010D838_slot_synch[i].y;
        light->unk_06[0] = 0;
        light->unk_06[1] = 0;
        light->unk_0A = 0;
        light->unk_0C = 0;
        light->unk_0E = 0;
    }
    omAddObj(0x1E, 0, 0, -1, func_8010A7D0_slot_synch);
}

void func_8010A480_slot_synch(s16 team, s16 chr0, s16 chr1, s16 arg3) {
    UnkSlotLight *light = &D_8010DF90_slot_synch[team];
    s32 group;
    s32 i;

    D_8010DF8C_slot_synch[team * 2 + 13] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[chr0]);
    D_8010DF8C_slot_synch[team * 2 + 14] = func_8010A2C4_slot_synch(D_8010DA40_slot_synch[chr1]);
    group = HuSprGrpCreate(6, 0);
    light->unk_00 = group;
    light->unk_06[0] = -8;
    light->unk_06[1] = 8;
    light->unk_0A = light->unk_0C = light->unk_0E = 0;
    func_8010AA9C_slot_synch(team, arg3);
    for (i = 0; i < 6; i++) {
        switch (i) {
            case 0:
                HuSprAttrSet(group, i, HUSPR_ATTR_DISPOFF);
            case 1:
                HuSprGrpMemberSet(group, i, D_8010DF8C_slot_synch[12], 0);
                HuSprPosSet(group, i, light->unk_02 + light->unk_06[i], light->unk_04);
                break;
            case 2:
                HuSprPosSet(group, i, light->unk_02 - 26, light->unk_04 - 9);
                HuSprGrpMemberSet(group, i, D_8010DF8C_slot_synch[team * 2 + 13], 0);
                break;
            case 3:
                HuSprPosSet(group, i, light->unk_02 - 26, light->unk_04 + 8);
                HuSprGrpMemberSet(group, i, D_8010DF8C_slot_synch[team * 2 + 14], 0);
                break;
            case 4:
                HuSprPosSet(group, i, light->unk_02 + 27, light->unk_04);
                HuSprGrpMemberSet(group, i, D_8010DF8C_slot_synch[11], 0);
                break;
            case 5:
                HuSprPosSet(group, i, light->unk_02, light->unk_04);
                HuSprScaleSet(group, i, 1.0f, 1.0f);
                func_80055484_main(group, i, 0, 0, 255, 160);
                HuSprGrpMemberSet(group, i, D_8010DF8C_slot_synch[10], 0);
                break;
        }
        func_800550F4_main(group, i, 0);
        func_80054FF8_main(group, i, 0);
        HuSprAttrSet(group, i, 0x1000);
        HuSprPriSet(group, i, i - 16);
    }
}

void func_8010A7D0_slot_synch(omObjData *object) {
    UnkSlotLight *light = D_8010DF90_slot_synch;
    u16 digits[2];
    f32 scale;
    s32 i;

    for (i = 0; i < 2; i++, light++) {
        digits[0] = light->unk_0A / 10;
        digits[1] = light->unk_0A - digits[0] * 10;
        if (digits[0] >= 10) {
            digits[0] = 9;
        }
        if (digits[1] >= 10) {
            digits[1] = 9;
        }
        func_80054FF8_main(light->unk_00, 0, (s16)digits[0]);
        func_80054FF8_main(light->unk_00, 1, (s16)digits[1]);
        if (light->unk_0A != light->unk_0C && light->unk_0E == 0) {
            light->unk_0E = 15;
            if (light->unk_0A < light->unk_0C) {
                light->unk_0A++;
            } else {
                light->unk_0A--;
            }
            HuSprAttrSet(light->unk_00, 0, 0x838);
            HuSprAttrSet(light->unk_00, 1, 0x838);
            if (light->unk_0A >= 10) {
                HuSprAttrReset(light->unk_00, 0, HUSPR_ATTR_DISPOFF);
            } else {
                HuSprAttrSet(light->unk_00, 0, HUSPR_ATTR_DISPOFF);
            }
        }
        scale = sindf(light->unk_0E / 15.0f * 180.0f) * 0.5f + 1.0f;
        HuSprPosSet(light->unk_00, 0, light->unk_02 + light->unk_06[0] * scale, light->unk_04);
        HuSprPosSet(light->unk_00, 1, light->unk_02 + light->unk_06[1] * scale, light->unk_04);
        HuSprScaleSet(light->unk_00, 0, scale, scale);
        HuSprScaleSet(light->unk_00, 1, scale, scale);
        if (light->unk_0E != 0 && --light->unk_0E == 0) {
            HuSprAttrReset(light->unk_00, 0, 0x838);
            HuSprAttrReset(light->unk_00, 1, 0x838);
        }
    }
}

void func_8010AA9C_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotLight *light = &D_8010DF90_slot_synch[arg0];

    light->unk_0C = arg1;
}

void func_8010AAB8_slot_synch(void) {
    HuSprite_Unk84_Struct *sprite;
    UnkSlotEffect *effect;
    HmfModel *model;
    s32 i;

    D_8010DF8C_slot_synch[1] = func_8010A2C4_slot_synch(11);
    sprite = func_80055194_main(D_8010DF8C_slot_synch[1]);
    D_8010DF94_slot_synch = omAddObj(30, 0, 0, -1, func_8010AC14_slot_synch);
    D_8010DF98_slot_synch = effect = HuMemAllocTag(sizeof(UnkSlotEffect) * 8, TAG_OVERLAY);
    for (i = 0; i < 8; i++, effect++) {
        if (i == 0) {
            effect->model = func_8010C4C0_slot_synch(sprite, D_8010D868_slot_synch.rgba);
        } else {
            effect->model = func_8010D0A8_slot_synch(sprite, D_8010DF98_slot_synch[0].model, D_8010D868_slot_synch.rgba);
        }
        effect->active = 0;
        effect->color = D_8010D868_slot_synch;
        effect->frame = effect->speed = 0.0f;
        effect->pos.x = effect->pos.y = effect->pos.z = 0.0f;
        effect->vel.x = effect->vel.y = effect->vel.z = 0.0f;
        effect->scale.x = effect->scale.y = effect->scale.z = 0.0f;
        func_8001C258_main(effect->model, 4, 4);
        model = &Hu3DData[effect->model];
        model->motTime = 0.0f;
    }
}

void func_8010AC14_slot_synch(omObjData *object) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_8010DF8C_slot_synch[1]);
    UnkSlotEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010DF98_slot_synch; i < 8; i++, effect++) {
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
        func_8010D2AC_slot_synch(effect->model, sprite, (s32)effect->frame, effect->color.rgba);
        effect->frame += effect->speed;
        if ((s32)effect->frame >= sprite->unk10) {
            effect->active = 0;
            effect->frame = 0.0f;
            model->attr |= 4;
        }
    }
}

s32 func_8010AD68_slot_synch(Vec *pos, Vec *vel, Vec *scale, f32 speed, u8 *color) {
    HuSprite_Unk84_Struct *sprite = func_80055194_main(D_8010DF8C_slot_synch[1]);
    UnkSlotEffect *effect;
    HmfModel *model;
    s32 i;

    for (i = 0, effect = D_8010DF98_slot_synch; i < 8; i++, effect++) {
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
        memcpy(effect->color.rgba, color, sizeof(UnkSlotColor));
        effect->speed = speed;
        effect->frame = 0.0f;
        func_8010D2AC_slot_synch(effect->model, sprite, 0, effect->color.rgba);
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

void func_8010AF38_slot_synch(void) {
    HuCamera *camera;
    s32 i;

    Center.x = 0.0f;
    Center.y = 184.8f;
    Center.z = -708.8f;
    CRot.x = 354.505f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 2000.0f;
    func_8010BB90_slot_synch(0);
    func_8010BB90_slot_synch(1);
    D_8010DFF0_slot_synch = 0;
    D_8010DFEC_slot_synch = 0;
    D_8010DFE8_slot_synch = 0;
    omAddObj(31, 0, 0, -1, func_8010B754_slot_synch);
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

void func_8010B064_slot_synch(void) {
    UnkSlotCamera delta = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 0.0f, 0.0f, 0.0f };
    f32 speed;

    speed = 1.0f;
    switch (D_8010DA60_slot_synch) {
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
                func_8010BD7C_slot_synch(delta.center.x, delta.center.y, delta.center.z, delta.rot.x,
                                         delta.rot.y, delta.rot.z, delta.zoom, 1);
            }
            sprintf(D_800D5218_main, "CAMERA TEST_MODE");
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 104,
                   D_800D5218_main);
            break;
        case 2:
            if ((D_800CDA7C_main[0] & R_JPAD) || (D_800CDA7C_main[0] & R_CBUTTONS)) {
                D_8010DA64_slot_synch++;
            }
            if (D_800CDA7C_main[0] & (L_JPAD | L_CBUTTONS)) {
                D_8010DA64_slot_synch--;
            }
            if (D_800CDA7C_main[0] & (D_JPAD | D_CBUTTONS)) {
                D_8010DA68_slot_synch++;
            }
            if (D_800CDA7C_main[0] & (U_JPAD | U_CBUTTONS)) {
                D_8010DA68_slot_synch--;
            }
            fontcolor = 8;
            sprintf(D_800D5218_main, "CAMERA TEST_MODE ");
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 80,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " CENTER X>%3.3f Y>%3.3f Z>%3.3f ", Center.x, Center.y, Center.z);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 88,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ROT    X>%3.3f Y>%3.3f Z>%3.3f ", CRot.x, CRot.y, CRot.z);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 96,
                   D_800D5218_main);
            sprintf(D_800D5218_main, " ZOOM   %3.3f ", CZoom);
            print8((s16)D_8010DA64_slot_synch + 20, (s16)D_8010DA68_slot_synch + 104,
                   D_800D5218_main);
            break;
        case 3:
            D_8010DA60_slot_synch = 0;
            break;
    }
    if (D_800D5558_main[0] & R_TRIG) {
        if (D_8010DA60_slot_synch == 1) {
            osSyncPrintf("CAMERA TEST_MODE \n");
            osSyncPrintf(" CENTER X>%3.3f Y>%3.3f Z>%3.3f \n", Center.x, Center.y, Center.z);
            osSyncPrintf(" ROT    X>%3.3f Y>%3.3f Z>%3.3f \n", CRot.x, CRot.y, CRot.z);
            osSyncPrintf(" ZOOM   %3.3f \n\n", CZoom);
        }
        if (D_8010DA60_slot_synch++ >= 4) {
            D_8010DA60_slot_synch = 0;
        }
    }
}

void func_8010B754_slot_synch(omObjData *object) {
    f32 t;

    if (D_8010DFEC_slot_synch <= 0) {
        func_8010BF6C_slot_synch(0);
        D_8010DFF0_slot_synch = 0;
        return;
    }
    if (D_8010DFE8_slot_synch == 0) {
        Center.x = D_8010DFA0_slot_synch[0].center.x;
        Center.y = D_8010DFA0_slot_synch[0].center.y;
        Center.z = D_8010DFA0_slot_synch[0].center.z;
        CRot.x = D_8010DFA0_slot_synch[0].rot.x;
        CRot.y = D_8010DFA0_slot_synch[0].rot.y;
        CRot.z = D_8010DFA0_slot_synch[0].rot.z;
        CZoom = D_8010DFA0_slot_synch[0].zoom;
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
        D_8010DFEC_slot_synch = 0;
    } else {
        t = (f32)D_8010DFE8_slot_synch / (f32)D_8010DFEC_slot_synch;
        Center.x = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.x,
                                            D_8010DFA0_slot_synch[1].center.x);
        Center.y = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.y,
                                            D_8010DFA0_slot_synch[1].center.y);
        Center.z = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].center.z,
                                            D_8010DFA0_slot_synch[1].center.z);
        CRot.x = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.x,
                                          D_8010DFA0_slot_synch[1].rot.x);
        CRot.y = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.y,
                                          D_8010DFA0_slot_synch[1].rot.y);
        CRot.z = func_8010C39C_slot_synch(t, D_8010DFA0_slot_synch[0].rot.z,
                                          D_8010DFA0_slot_synch[1].rot.z);
        CZoom = func_8010C384_slot_synch(t, D_8010DFA0_slot_synch[0].zoom,
                                         D_8010DFA0_slot_synch[1].zoom);
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
        if (D_8010DFE8_slot_synch > 0) {
            D_8010DFE8_slot_synch--;
        } else {
            D_8010DFE8_slot_synch++;
        }
    }
    D_8010DFF0_slot_synch = 1;
    func_8010BF6C_slot_synch(0);
}

void func_8010BB90_slot_synch(s32 arg0) {
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
    D_8010DFA0_slot_synch[arg0].center.x = Center.x;
    D_8010DFA0_slot_synch[arg0].center.y = Center.y;
    D_8010DFA0_slot_synch[arg0].center.z = Center.z;
    D_8010DFA0_slot_synch[arg0].rot.x = CRot.x;
    D_8010DFA0_slot_synch[arg0].rot.y = CRot.y;
    D_8010DFA0_slot_synch[arg0].rot.z = CRot.z;
    D_8010DFA0_slot_synch[arg0].zoom = CZoom;
    D_8010DFA0_slot_synch[arg0].unk_1C = D_8010DFA0_slot_synch[arg0].unk_20 = 0.0f;
}

// Passing CAMERA_KEEP for a component keeps its current value.
void func_8010BD7C_slot_synch(f32 x, f32 y, f32 z, f32 rotX, f32 rotY, f32 rotZ, f32 zoom, s32 frames) {
    if (frames > 0) {
        D_8010DFE8_slot_synch = frames - 1;
        D_8010DFEC_slot_synch = frames;
        if (x != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].center.x = x;
        } else {
            D_8010DFA0_slot_synch[0].center.x = Center.x;
        }
        if (y != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].center.y = y;
        } else {
            D_8010DFA0_slot_synch[0].center.y = Center.y;
        }
        if (z != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].center.z = z;
        } else {
            D_8010DFA0_slot_synch[0].center.z = Center.z;
        }
        if (rotX != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].rot.x = rotX;
        } else {
            D_8010DFA0_slot_synch[0].rot.x = CRot.x;
        }
        if (rotY != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].rot.y = rotY;
        } else {
            D_8010DFA0_slot_synch[0].rot.y = CRot.y;
        }
        if (rotZ != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].rot.z = rotZ;
        } else {
            D_8010DFA0_slot_synch[0].rot.z = CRot.z;
        }
        if (zoom != CAMERA_KEEP) {
            D_8010DFA0_slot_synch[0].zoom = zoom;
        } else {
            D_8010DFA0_slot_synch[0].zoom = CZoom;
        }
        func_8010BB90_slot_synch(1);
    }
}

void func_8010BF6C_slot_synch(s32 camIndex) {
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

f32 func_8010C0C0_slot_synch(f32 arg0, f32 arg1) {
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

f32 func_8010C1C4_slot_synch(f32 target, f32 current, f32 step) {
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

f32 func_8010C384_slot_synch(f32 t, f32 start, f32 end) {
    return start + t * (end - start);
}

f32 func_8010C39C_slot_synch(f32 arg0, f32 arg1, f32 arg2) {
    return func_8010C1C4_slot_synch(arg2, arg1, fabsf(func_8010C0C0_slot_synch(arg2, arg1) * arg0));
}

void func_8010C3FC_slot_synch(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_8010C428_slot_synch(omObjData *arg0) {
    UnkSlotSynchBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return packed.word;
}

s16 func_8010C47C_slot_synch(s32 file) {
    s16 motion = Hu3DMotionCreate(DataRead(file), 0x18);

    if (motion >= 0) {
        return motion;
    }
    return -1;
}

s32 func_8010C4C0_slot_synch(HuSprite_Unk84_Struct *sprite, u8 *color) {
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
    func_8010D3E0_slot_synch(sprite, data, 1.0f, 0, 0);
    gSPDisplayList(header, osVirtualToPhysical(D_8010DB60_slot_synch));
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

s32 func_8010D0A8_slot_synch(HuSprite_Unk84_Struct *sprite, u16 model, u8 *color) {
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

void func_8010D2AC_slot_synch(u16 model, HuSprite_Unk84_Struct *sprite, u16 frame, u8 *color) {
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

s32 func_8010D3E0_slot_synch(HuSprite_Unk84_Struct *sprite, HmfData *data, f32 scale, s16 xOffset, s16 yOffset) {
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
