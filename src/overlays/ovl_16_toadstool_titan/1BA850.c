#include "common.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"
#include "overlays/minigame.h"

typedef struct ToadstoolTitanPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 playerNo;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ToadstoolTitanPlayer; // sizeof 0x10

typedef struct ToadstoolTitanBssF614 {
    /* 0x00 */ u8 unk00[2];
    /* 0x02 */ u8 unk02[4];
} ToadstoolTitanBssF614; // sizeof 0x6

typedef struct ToadstoolTitanBssF650 {
    /* 0x00 */ u8 unk00[9];
    /* 0x09 */ u8 unk09[4];
    /* 0x0D */ u8 unk0D[4]; // group of each player
} ToadstoolTitanBssF650;    // sizeof 0x11

extern s32 D_800A178C_main[][6];
extern s16 D_800CDBC8_main;
extern s16 D_800D037E_main;
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern omObjData *D_800D6A40_main;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB75C_minigame;
extern u8 D_800CD6A6_main;
extern s16 D_800D418E_main;
extern u8 D_800D6A90_main;
extern Gfx *gMainGfxPos;

u8 D_8010EDA0_toadstool_titan = 0;       // number of mushrooms created so far
f32 D_8010EDA4_toadstool_titan = 0.0f;   // screen rect left
f32 D_8010EDA8_toadstool_titan = 0.0f;   // screen rect top
f32 D_8010EDAC_toadstool_titan = 320.0f; // screen rect right
f32 D_8010EDB0_toadstool_titan = 240.0f; // screen rect bottom
u8 D_8010EDB4_toadstool_titan[14] = { 0 };
u8 D_8010EDC4_toadstool_titan[9] = { 0 };
u8 D_8010EDCD_toadstool_titan = 0;
s16 D_8010EDCE_toadstool_titan = 0;
s16 D_8010EDD0_toadstool_titan = 0;
f32 D_8010EDD4_toadstool_titan = 0.0f;
f32 D_8010EDD8_toadstool_titan = 0.0f;
f32 D_8010EDDC_toadstool_titan = 0.0f;
f32 D_8010EDE0_toadstool_titan = 0.0f;
s16 D_8010EDE4_toadstool_titan = 0;
s16 D_8010EDE8_toadstool_titan[3] = { 0 };

Gfx D_8010EDF0_toadstool_titan[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetCombineMode(G_CC_DECALRGBA, G_CC_DECALRGBA),
    gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTexturePersp(G_TP_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, 320, 240),
    gsSPEndDisplayList(),
};

s32 D_8010EE38_toadstool_titan = 0; // set once the camera has been initialized
u8 D_8010EE3C_toadstool_titan = 0;
u8 D_8010EE40_toadstool_titan[4] = { 0 };
s16 D_8010EE44_toadstool_titan[4] = { 0 };
s16 D_8010EE4C_toadstool_titan[4] = { 0 };
f32 D_8010EE54_toadstool_titan[4] = { 0.0f };
f32 D_8010EE64_toadstool_titan[4] = { 0.0f };

f32 D_8010F3D0_toadstool_titan[14] BSS;
f32 D_8010F408_toadstool_titan[14] BSS;
f32 D_8010F440_toadstool_titan[14] BSS;
f32 D_8010F478_toadstool_titan[14] BSS;
f32 D_8010F4B0_toadstool_titan[14] BSS;
f32 D_8010F4E8_toadstool_titan[14] BSS;
f32 D_8010F520_toadstool_titan BSS;
u8 D_8010F524_toadstool_titan[4] BSS; /* Unreferenced. */
ToadstoolTitanPlayer D_8010F528_toadstool_titan[4] BSS;
ToadstoolTitanPlayer *D_8010F568_toadstool_titan[4] BSS; // players indexed by group
u8 D_8010F578_toadstool_titan[8] BSS;                    /* Unreferenced. */
u32 D_8010F580_toadstool_titan BSS;
u8 D_8010F584_toadstool_titan BSS;
s16 D_8010F586_toadstool_titan BSS;
s16 D_8010F588_toadstool_titan[1] BSS;
s8 D_8010F58A_toadstool_titan BSS;
f32 D_8010F58C_toadstool_titan BSS;
D_80111B50_vine_with_me_Struct D_8010F590_toadstool_titan BSS;
f32 D_8010F5B8_toadstool_titan BSS;
u16 D_8010F5BC_toadstool_titan BSS;
Vec D_8010F5C0_toadstool_titan BSS;           // camera target
u8 D_8010F5CC_toadstool_titan[4] BSS;         /* Unreferenced. */
omObjData *D_8010F5D0_toadstool_titan[9] BSS; // mushroom objects
u8 D_8010F5F4_toadstool_titan BSS;
omObjData *D_8010F5F8_toadstool_titan BSS;
s16 D_8010F5FC_toadstool_titan BSS;
f32 D_8010F600_toadstool_titan BSS; // music volume
f32 D_8010F604_toadstool_titan BSS;
f32 D_8010F608_toadstool_titan BSS;
s16 D_8010F60C_toadstool_titan[1] BSS;
s8 D_8010F60E_toadstool_titan BSS;
f32 D_8010F610_toadstool_titan BSS;
ToadstoolTitanBssF614 toadstoolTitanBssF614 BSS;
u32 D_8010F61C_toadstool_titan BSS;
u8 D_8010F620_toadstool_titan BSS;
f32 D_8010F624_toadstool_titan BSS; // camera fov
Vec D_8010F628_toadstool_titan BSS; // camera position
s16 D_8010F634_toadstool_titan[4] BSS;
u8 D_8010F63C_toadstool_titan[4] BSS; /* Unreferenced. */
omObjData *D_8010F640_toadstool_titan[4] BSS;
ToadstoolTitanBssF650 toadstoolTitanBssF650 BSS;
f32 D_8010F664_toadstool_titan BSS;
u8 D_8010F668_toadstool_titan[4] BSS; // start corner of each group
u8 D_8010F66C_toadstool_titan BSS;    // number of human players
f32 D_8010F670_toadstool_titan BSS;

/* Fields of toadstoolTitanBssF614/toadstoolTitanBssF650, aliased in undefined_syms.txt. */
extern u8 D_8010F614_toadstool_titan[2];
extern u8 D_8010F616_toadstool_titan[4];
extern u8 D_8010F650_toadstool_titan[9];
extern u8 D_8010F659_toadstool_titan[4];
extern u8 D_8010F65D_toadstool_titan[4]; // group of each player

const s16 D_8010EE80_toadstool_titan[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C,
    0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279,
    0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x0000, 0x0000
};

void func_80105E50_toadstool_titan(omObjData *object);
void func_801060AC_toadstool_titan(omObjData *object);
void func_80106984_toadstool_titan(void);
void func_801069DC_toadstool_titan(omObjData *object);
void func_80106C98_toadstool_titan(omObjData *object);
void func_80107360_toadstool_titan(omObjData *object);
void func_8010AD8C_toadstool_titan(s16 left, s16 top, s16 right, s16 bottom);
void func_8010B4D4_toadstool_titan(s16 model, s16 time);
void func_8010B658_toadstool_titan(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void func_8010B99C_toadstool_titan(omObjData *object);
void func_8010BA80_toadstool_titan(omObjData *object);
void func_8010BB64_toadstool_titan(omObjData *object);
void func_8010BC48_toadstool_titan(omObjData *object);
void func_8010B510_toadstool_titan(omObjData *object);
void func_8010BD2C_toadstool_titan(omObjData *object);

void func_801059A0_toadstool_titan(void) {
    omObjData *object;
    s32 i;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(1);
    D_800CD6A6_main = func_8000B638_main();
    ScissorSet(D_800CD6A6_main, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_800CD6A6_main, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    D_800EB73C_minigame = 15.0f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    func_800E19F0_minigame(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 73.0f, 95.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x80);
    Hu3DGLightDirSet(1, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(2, 0.0f, 95.0f, 55.0f);
    Hu3DGLightColorSet(2, 0xFF, 0xFF, 0xFF);
    omAddObj(0, 0, 0, -1, func_80105E50_toadstool_titan);
    func_800E1490_minigame(D_800EBE28_minigame);
    object = omAddObj(4, 58, 58, -1, func_80106C98_toadstool_titan);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010F5F8_toadstool_titan = object;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    for (i = 0; i < 9; i++) {
        D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010F5D0_toadstool_titan[i] = omAddObj(2, 2, 2, -1, func_801069DC_toadstool_titan);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[0] = omAddObj(3, 12, 60, -1, func_8010B99C_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[1] = omAddObj(3, 12, 60, -1, func_8010BA80_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[2] = omAddObj(3, 12, 60, -1, func_8010BB64_toadstool_titan);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010F640_toadstool_titan[3] = omAddObj(3, 12, 60, -1, func_8010BC48_toadstool_titan);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010B510_toadstool_titan), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(0xFF, 30);
    func_80045010_main(D_8010EE80_toadstool_titan, 1);
    D_8010F590_toadstool_titan.unk01 = 0;
    D_8010F590_toadstool_titan.unk1C = 45;
    D_8010F590_toadstool_titan.unk1E = 1800;
    D_8010F590_toadstool_titan.unk03 = 2;
    D_8010F590_toadstool_titan.unk02 = 1;
    D_8010F590_toadstool_titan.unk22 = 60;
    D_8010F590_toadstool_titan.unk24 = 165;
    D_8010F590_toadstool_titan.unk04 = 0;
    D_8010F590_toadstool_titan.unk05 = 0;
    D_8010F590_toadstool_titan.unk20 = -1;
    func_800E5EA0_minigame(&D_8010F590_toadstool_titan);
}

void func_80105E48_toadstool_titan(void) {
}

void func_80105E50_toadstool_titan(omObjData *object) {
    s32 i;
    s32 j;

    D_8010F5BC_toadstool_titan = 0;
    D_8010F5FC_toadstool_titan = 0;
    D_8010F580_toadstool_titan = 0;
    D_8010F58A_toadstool_titan = 5;
    D_8010F584_toadstool_titan = 0;
    D_8010F586_toadstool_titan = 0;
    D_8010F61C_toadstool_titan = 0;
    D_8010F60E_toadstool_titan = -1;
    D_8010F616_toadstool_titan[0] = D_8010F616_toadstool_titan[1] = D_8010F616_toadstool_titan[2] = D_8010F616_toadstool_titan[3] = 0;
    D_8010F5F4_toadstool_titan = 0;
    D_8010F66C_toadstool_titan = 0;
    D_8010F614_toadstool_titan[0] = D_8010F614_toadstool_titan[1] = 0;
    D_8010F600_toadstool_titan = -1.0f;
    for (i = 0; i < 4; i++) {
        D_8010F568_toadstool_titan[i] = &D_8010F528_toadstool_titan[i];
        bzero(D_8010F568_toadstool_titan[i], sizeof(ToadstoolTitanPlayer));
    }
    for (i = 0; i < 4; i++) {
        // j holds the player's group here; a separate variable changes the register allocation.
        j = D_8010F65D_toadstool_titan[i] = GwPlayer[i].group;
        D_8010F568_toadstool_titan[j]->playerNo = i;
        D_8010F568_toadstool_titan[j]->pad = GwPlayer[i].pad;
        D_8010F568_toadstool_titan[j]->chr = GwPlayer[i].chr;
        D_8010F568_toadstool_titan[j]->group = j;
        D_8010F568_toadstool_titan[j]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
        D_8010F66C_toadstool_titan += (D_8010F568_toadstool_titan[j]->cpuDifficulty == -1) ? 1 : 0;
    }
    for (i = 0; i < 4; i++) {
        D_8010F668_toadstool_titan[i] = rand8() & 3;
        for (j = 0; j < i; j++) {
            if (D_8010F668_toadstool_titan[i] == D_8010F668_toadstool_titan[j]) {
                i--;
                break;
            }
        }
    }
    object->func = func_801060AC_toadstool_titan;
}

void func_801060AC_toadstool_titan(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s16 i;

    D_8010F580_toadstool_titan++;
    func_800E6F40_minigame();
    switch (D_8010F5FC_toadstool_titan) {
        case 0:
            if (func_800E6E8C_minigame() == 1) {
                D_8010F5FC_toadstool_titan = 1;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 1:
            if (D_8010F580_toadstool_titan == 61 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x38);
                D_8010F614_toadstool_titan[0] = 1;
            }
            if (func_800E6E8C_minigame() == 2) {
                D_8010F5FC_toadstool_titan = 2;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 2:
            if (D_8010F580_toadstool_titan == 1) {
                func_80106984_toadstool_titan();
            }
            if (D_8010F58A_toadstool_titan != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010F58A_toadstool_titan == 5) {
                    D_8010F5FC_toadstool_titan = 6;
                    D_8010F58A_toadstool_titan = 4;
                    if (D_8010F586_toadstool_titan == 5) {
                        D_8010F61C_toadstool_titan = 150;
                    }
                } else {
                    D_8010F5FC_toadstool_titan = 3;
                }
                D_8010F580_toadstool_titan = 0;
            }
            if (D_8010F5FC_toadstool_titan != 3) {
                break;
            }
        case 3:
            if (D_8010F580_toadstool_titan == 0) {
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010F590_toadstool_titan.unk06 = 0;
                D_8010F590_toadstool_titan.unk18[0] = D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->playerNo;
                GwPlayer[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->playerNo].bonusCoin = 10;
                D_8010F614_toadstool_titan[0] = 0;
                if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A7C4_main(60);
                    D_8010F614_toadstool_titan[1] = 0;
                }
            }
            if (D_8010F580_toadstool_titan == 2) {
                func_800E6F34_minigame(30);
                D_8010F590_toadstool_titan.unk22 = 60;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F5FC_toadstool_titan = 4;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 6:
            if (D_8010F580_toadstool_titan == 1) {
                D_8010F590_toadstool_titan.unk06 = 4;
                D_8010F590_toadstool_titan.unk22 = 90;
                D_8010F590_toadstool_titan.unk24 = 0x90;
                D_8010F614_toadstool_titan[0] = 0;
                if (D_8010F614_toadstool_titan[1] != 0 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A7C4_main(60);
                    D_8010F614_toadstool_titan[1] = 0;
                }
            }
            if (D_8010F580_toadstool_titan == 64 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqStop();
            }
            if (D_8010F580_toadstool_titan == 67 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A72C_main(3);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010F5FC_toadstool_titan = 5;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 4:
            if (D_8010F580_toadstool_titan == 24 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                HuAudSeqStop();
            }
            if (D_8010F580_toadstool_titan == 27 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                func_8004A72C_main(3);
            }
            if (D_8010F580_toadstool_titan == 29) {
                if (D_8010F586_toadstool_titan == 9) {
                    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                    func_80017954_main(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->model[0], 1,
                                       slots[D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr],
                                       D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unk_08);
                    func_800E5A00_minigame(
                        D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 13,
                        func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->chr, (rand8() & 1) ? 0x2F : 0x30), 1, 120);
                    func_80045ED0_main(D_8010F568_toadstool_titan[D_8010F58A_toadstool_titan]->unk_0C);
                    msmMusStop(D_800D037E_main);
                }
            }
            if (D_8010F580_toadstool_titan == 30 && D_8010F586_toadstool_titan == 9) {
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan], 13);
            }
        case 5:
            if (D_8010F5FC_toadstool_titan == 5) {
                if (D_8010F580_toadstool_titan == 1) {
                    for (i = 0; i < 4; i++) {
                        func_800E5A00_minigame(D_8010F640_toadstool_titan[i], 14, func_80017BB8_main(D_8010F568_toadstool_titan[i]->chr, 0x3A), 1,
                                               120);
                    }
                    msmMusStop(D_800D037E_main);
                }
                if (D_8010F5FC_toadstool_titan == 5 && D_8010F580_toadstool_titan >= 2) {
                    for (i = 0; i < 4; i++) {
                        data = D_8010F640_toadstool_titan[i]->data;
                        if (data->unk5C != 0x1000 && data->unk38 == 1000.0f) {
                            data->unk3C = 0.0f;
                            func_800E5690_minigame(D_8010F640_toadstool_titan[i], 14);
                        }
                    }
                }
            }
            if (func_800E6E8C_minigame() == 5) {
                D_8010F5FC_toadstool_titan = 7;
                D_8010F580_toadstool_titan = 0;
            }
            break;
        case 7:
            if (D_8010F580_toadstool_titan == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010F580_toadstool_titan >= 32) {
                D_8010F5BC_toadstool_titan = 1;
            }
            break;
    }
    if (D_8010F5BC_toadstool_titan != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010F584_toadstool_titan == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004A7C4_main(20);
                func_8004AB0C_main(20);
            }
            D_8010F584_toadstool_titan++;
            if (D_8010F584_toadstool_titan == 21 && D_800D6A40_main != NULL) {
                msmMusStop(D_800CDBC8_main);
                msmMusStop(D_800D037E_main);
            }
            if (D_8010F584_toadstool_titan == 23 && D_800D6A40_main != NULL && D_8010F600_toadstool_titan != -1.0f) {
                msmMusSetVolume(D_800CDBC8_main, D_8010F600_toadstool_titan);
            }
            if (D_8010F584_toadstool_titan < 25) {
                return;
            }
        }
        msmMusStop(D_800CDBC8_main);
        msmMusStop(D_800D037E_main);
        omOvlReturnEx(1);
    }
}

void func_80106984_toadstool_titan(void) {
    UnkAudioObjData *data;

    if (D_800D6A40_main != NULL) {
        data = D_800D6A40_main->data;
        D_8010F600_toadstool_titan = data->unk24 = data->unk2C = func_800037C4_main(D_800CDBC8_main);
    }
}

void func_801069DC_toadstool_titan(omObjData *object) {
    f32 xs[9] = { 0.0f, 110.0f, 250.0f, 250.0f, 110.0f, -110.0f, -250.0f, -250.0f, -110.0f };
    f32 zs[9] = { 0.0f, -230.0f, -110.0f, 110.0f, 240.0f, 240.0f, 110.0f, -110.0f, -230.0f };
    D_800EC1C0_minigame_ObjData *work;

    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[0] = func_8000B108_main(0x370000, 0xBD);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[0]);
    }
    omSetTra(object, xs[D_8010EDA0_toadstool_titan] * 1.11, 375.0f, zs[D_8010EDA0_toadstool_titan] * 1.11 + 20.0);
    omSetSca(object, 0.6666667f, 0.6666667f, 0.6666667f);
    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[1] = func_8000B108_main(0x370001, 0xBD);
    } else {
        object->model[1] = Hu3DModelLink(D_8010F5D0_toadstool_titan[0]->model[1]);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E13CC_minigame(object, 50.0f, 100.0f, -60.0f, -60.0f, 60.0f,
                           (D_8010EDA0_toadstool_titan >= 4 && D_8010EDA0_toadstool_titan < 6) ? 120.0f : 60.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    work->unk04 = D_8010EDA0_toadstool_titan + 1;
    D_8010F650_toadstool_titan[D_8010EDA0_toadstool_titan] = 0;
    D_8010EDA0_toadstool_titan++;
    object->func = NULL;
}

void func_80106C98_toadstool_titan(omObjData *object) {
    s32 spriteFiles[1] = { 0x37000C };
    D_800EC1C0_minigame_ObjData *work;
    s16 i;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 0.0f;
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E139C_minigame(object, 0.0f, -475.0f, -425.0f, 475.0f, 425.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    func_800E1468_minigame(object);
    work->unk04 = 0;
    for (i = 0; i < 1; i++) {
        D_8010F588_toadstool_titan[i] = espEntry(D_8010F60C_toadstool_titan[i] = func_8000B838_main(spriteFiles[i]), 0, 0);
        espDispOff(D_8010F588_toadstool_titan[i]);
    }
    object->model[1] = func_8000B108_main(0x370002, 0x4BD);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    Hu3DModelRotSet(object->model[1], -23.0f, 0.0f, 0.0f);
    object->model[3] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(object->model[3]);
    for (i = 1; i < 5; i++) {
        object->model[3 + i] = Hu3DModelLink(object->model[3]);
    }
    object->model[2] = func_8000B108_main(0x370003, 0x404AD);
    func_8001FA68_main(object->model[2]);
    for (i = 0; i < 3; i++) {
        HmfModel *modelP;

        object->model[26 + i] = func_8000B108_main(0x1001F, 0x8BD);
        Hu3DModelScaleSet(object->model[26 + i], 2.5f, 2.5f, 2.5f);
        func_8001C2FC_main(object->model[26 + i], 0x70000000, 0x70000000);
        modelP = &Hu3DData[object->model[26 + i]];
        modelP->motSpeed = 1.55f;
    }
    for (i = 0; i < 14; i++) {
        s32 files[6] = { 4, 5, 6, 7, 8, 9 };
        f32 scale = 0.5f;

        if (i < 6) {
            object->model[29 + i] = func_8000B108_main(files[(s16)(i % 6)] | 0x370000, 0x4BD);
        } else {
            object->model[29 + i] = Hu3DModelLink(object->model[29 + (s16)(i % 6)]);
        }
        func_8001C2FC_main(object->model[29 + i], 0x70000000, 0x70000000);
        if (i == 0) {
            object->model[43] = func_8000B108_main(9, 0xBD);
        } else {
            object->model[43 + i] = Hu3DModelLink(object->model[43]);
        }
        Hu3DModelScaleSet(object->model[29 + i], scale, scale, scale);
        scale = 0.875f;
        Hu3DModelScaleSet(object->model[43 + i], scale, scale, scale);
    }
    for (i = 0; i < 9; i++) {
        if (i == 0) {
            object->model[8] = func_8000B108_main(0x37000A, 0x8BD);
        } else {
            object->model[8 + i] = Hu3DModelLink(object->model[8]);
        }
        Hu3DModelPosSet(object->model[8 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y + 25.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z + 125.0f);
        Hu3DModelRotSet(object->model[8 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[8 + i], 2.5f, 2.5f, 2.5f);
        object->model[17 + i] = func_8000B108_main(0x37000B, 0x8BD);
        Hu3DModelPosSet(object->model[17 + i], D_8010F5D0_toadstool_titan[i]->trans.x, D_8010F5D0_toadstool_titan[i]->trans.y - 100.0f,
                        D_8010F5D0_toadstool_titan[i]->trans.z);
        Hu3DModelRotSet(object->model[17 + i], -23.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(object->model[17 + i], 0.75f, 0.75f, 0.75f);
    }
    object->model[57] = func_8000B108_main(0x37000A, 0x8BD);
    Hu3DModelScaleSet(object->model[57], 2.0f, 2.0f, 2.0f);
    object->func = func_80107360_toadstool_titan;
}

void func_80107360_toadstool_titan(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    HuCamMtxs *camMtxs;
    f32 t;
    f32 x;
    f32 y;
    f32 z;
    f32 angle;
    s32 count;
    s32 tries;
    s32 i;
    s32 j;
    s32 k;

    i = 0;
    if (D_8010F5FC_toadstool_titan == 4 && D_8010F580_toadstool_titan >= 30 && D_8010F580_toadstool_titan < 50) {
        Vec2f screenMin;
        Vec2f screenMax;
        Vec2f center;
        Vec pos;
        Vec pos2;
        Vec pos3;
        f32 width;
        f32 scale;
        f32 left;
        f32 top;
        f32 right;
        f32 bottom;
        f32 blend;
        f32 inv;
        omObjData *player = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan];

        pos2.x = player->trans.x;
        pos2.y = player->trans.y + 75.0f;
        pos2.z = player->trans.z;
        pos = pos2;
        pos3.x = player->trans.x + 25.0f;
        pos3.y = player->trans.y + 75.0f;
        pos3.z = player->trans.z;
        pos2 = pos3;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        func_80012B14_main(0, &pos, &screenMin);
        func_80012B14_main(0, &pos2, &screenMax);
        width = (screenMax.x - screenMin.x) * 12.0f;
        screenMax.x = width + screenMin.x;
        screenMin.x = screenMin.x - width;
        screenMin.y = screenMin.y - (screenMax.x - screenMin.x) * 0.75 * 0.5;
        screenMax.y = screenMax.y + (screenMax.x - screenMin.x) * 0.75 * 0.5;
        blend = 1.0f - (f32)(D_8010F580_toadstool_titan - 30) / 20.0f;
        blend = 1.0f - blend * blend * blend * blend;
        inv = 1.0f - blend;
        screenMin.x = blend * screenMin.x + inv * 0.0f;
        screenMin.y = blend * screenMin.y + inv * 0.0f;
        screenMax.x = blend * screenMax.x + inv * 320.0f;
        screenMax.y = blend * screenMax.y + inv * 240.0f;
        scale = 320.0f / (screenMax.x - screenMin.x);
        if (screenMin.x < 0.0f) {
            screenMax.x -= screenMin.x;
            screenMin.x -= screenMin.x;
        }
        if (screenMin.y < 0.0f) {
            screenMax.y -= screenMin.y;
            screenMin.y -= screenMin.y;
        }
        if (screenMax.x > 320.0f) {
            f32 over = screenMax.x - 320.0f;

            screenMin.x -= over;
            screenMax.x -= over;
        }
        if (screenMax.y > 240.0f) {
            f32 over = screenMax.y - 240.0f;

            screenMin.y -= over;
            screenMax.y -= over;
        }
        center.x = (screenMin.x + screenMax.x) * 0.5;
        center.y = (screenMin.y + screenMax.y) * 0.5;
        D_8010EDA4_toadstool_titan = (s32)((0.0f - center.x) / (screenMin.x - center.x) * (0.0f - center.x) + center.x);
        D_8010EDA8_toadstool_titan = (s32)((0.0f - center.y) / (screenMin.y - center.y) * (0.0f - center.y) + center.y);
        D_8010EDAC_toadstool_titan = (s32)((320.0f - center.x) / (screenMax.x - center.x) * (320.0f - center.x) + center.x);
        D_8010EDB0_toadstool_titan = (s32)((240.0f - center.y) / (screenMax.y - center.y) * (240.0f - center.y) + center.y);
        left = 0.0f;
        if (screenMin.x != left) {
            left = left - (screenMin.x - left) * scale;
        }
        D_8010EDA4_toadstool_titan = left;
        top = 0.0f;
        if (screenMin.y != top) {
            top = top - (screenMin.y - top) * scale;
        }
        D_8010EDA8_toadstool_titan = top;
        right = 320.0f;
        if (screenMax.x != right) {
            right = right - (screenMax.x - right) * scale;
        }
        D_8010EDAC_toadstool_titan = right;
        bottom = 240.0f;
        if (screenMax.y != bottom) {
            bottom = bottom - (screenMax.y - bottom) * scale;
        }
        D_8010EDB0_toadstool_titan = bottom;
        ViewportSet(0, (s32)(scale * 640.0f), (s32)(scale * 480.0f), 511.0f,
                    (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan != 0 && D_8010F5F4_toadstool_titan < 13) {
        f32 shakeAngle;

        if (omPauseChk() + D_800D6A90_main == 0) {
            shakeAngle = D_8010F670_toadstool_titan + rand8() / 255.0 * 30.0 - 15.0;
        } else {
            shakeAngle = D_8010F670_toadstool_titan;
        }
        D_8010EDA4_toadstool_titan = (s16)(sindf(shakeAngle) * 0.5 *
                                           ((D_8010F5F4_toadstool_titan % 2 == 0) ? D_8010F5F4_toadstool_titan : -D_8010F5F4_toadstool_titan));
        D_8010EDAC_toadstool_titan = D_8010EDA4_toadstool_titan + 320.0f;
        D_8010EDA8_toadstool_titan = (s16)(cosdf(shakeAngle) * 0.5 *
                                           ((D_8010F5F4_toadstool_titan % 2 == 0) ? D_8010F5F4_toadstool_titan : -D_8010F5F4_toadstool_titan));
        D_8010EDB0_toadstool_titan = D_8010EDA8_toadstool_titan + 240.0f;
        D_8010F5F4_toadstool_titan -= (omPauseChk() + D_800D6A90_main == 0) ? 1 : 0;
        ViewportSet(0, 640.0f, 480.0f, 511.0f, (s32)((D_8010EDA4_toadstool_titan + D_8010EDAC_toadstool_titan) / 2.0 * 4.0),
                    (s32)((D_8010EDA8_toadstool_titan + D_8010EDB0_toadstool_titan) / 2.0 * 4.0), 511.0f);
    } else if (D_8010F5F4_toadstool_titan == 13) {
        D_8010F5F4_toadstool_titan -= (omPauseChk() + D_800D6A90_main == 0) ? 1 : 0;
    }
    func_8010AD8C_toadstool_titan(D_8010EDA4_toadstool_titan, D_8010EDA8_toadstool_titan, D_8010EDAC_toadstool_titan,
                                  D_8010EDB0_toadstool_titan);
    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    D_8010F61C_toadstool_titan++;
    switch (D_8010F586_toadstool_titan) {
        case 0:
            if (D_8010F61C_toadstool_titan >= 47) {
                D_8010F586_toadstool_titan = 7;
                D_8010F61C_toadstool_titan = 0;
                for (j = 0; j < 4; j++) {
                    s16 chr = D_8010F568_toadstool_titan[j]->chr;

                    D_8010F640_toadstool_titan[j]->model[6] = func_8000B108_main(5, 0x88D);
                    D_8010F640_toadstool_titan[j]->model[7] = func_8000B108_main(8, 0x88D);
                    D_8010F640_toadstool_titan[j]->model[8] = func_8000B108_main(7, 0x88D);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 1, func_80017BB8_main(chr, 1), 1, 0);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 18, func_80017BB8_main(chr, 15), 2, 0);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 2, func_80017BB8_main(chr, 2), 1, 0);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 17, func_80017BB8_main(chr, 14), 1, 15);
                    func_800E5978_minigame(D_8010F640_toadstool_titan[j], 30, func_80017BB8_main(chr, 32), 2, 0);
                    func_800E5978_minigame(D_8010F640_toadstool_titan[j], 31, func_80017BB8_main(chr, 33), 2, 0);
                    func_800E5978_minigame(D_8010F640_toadstool_titan[j], 32, func_80017BB8_main(chr, 34), 0, 0);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 5, func_80017BB8_main(chr, 3), 0, 0);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 8, func_80017BB8_main(chr, 6), 1, 27);
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[j], 12, func_80017BB8_main(chr, 37), 1, 120);
                }
            }
            break;
        case 1:
        case 2:
            for (tries = 0, i = rand8() & 3; tries < 4; tries++) {
                i++;
                i %= 4;
                data = D_8010F640_toadstool_titan[i]->data;
                if (D_8010F586_toadstool_titan == 1 && D_8010F61C_toadstool_titan < 4 && data->unk53[3] >= 1 && data->unk53[3] <= 9 &&
                    D_8010F650_toadstool_titan[data->unk53[3] - 1] == 2) {
                    s32 start;
                    s32 n;
                    s32 slot;

                    for (n = 0, start = (u8)(rand8() % 9); n < 9; n++) {
                        slot = (n + start) % 9;
                        if (D_8010F650_toadstool_titan[slot] == 1) {
                            D_8010F650_toadstool_titan[data->unk53[3] - 1] = 1;
                            D_8010F650_toadstool_titan[slot] = 2;
                            break;
                        }
                    }
                }
                if (data->unk53[3] >= 1 && data->unk53[3] <= 9 && D_8010F650_toadstool_titan[data->unk53[3] - 1] != 3) {
                    j = data->unk53[3] - 1;
                    if (D_8010F650_toadstool_titan[j] == 2) {
                        data->unk38 += 0.5;
                        Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].unk0E = Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].unk0C;
                        D_8010F620_toadstool_titan = j;
                        for (k = 0; k < 9; k++) {
                            D_8010F650_toadstool_titan[k] = D_8010F650_toadstool_titan[k] != 0;
                        }
                        D_8010F650_toadstool_titan[j] = 3;
                        D_8010F586_toadstool_titan = 2;
                        D_8010F61C_toadstool_titan = 0;
                        D_8010F60E_toadstool_titan = i;
                    } else if (D_8010F650_toadstool_titan[j] != 3) {
                        D_8010F650_toadstool_titan[j] = 0;
                        data->unkC5 = func_8004AC98_main(0x3A5, data->unk59);
                        data->unkC4 = -1;
                        for (k = 0; k < 4; k++) {
                            func_800E149C_minigame(D_8010F640_toadstool_titan[k], j + 1, 1);
                        }
                        func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 4);
                        func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 4);
                        func_8001C258_main(D_8010F5F8_toadstool_titan->model[17 + j], 4, 0);
                        func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[17 + j], 0);
                        D_8010EDC4_toadstool_titan[j] = 1;
                        count = 0;
                        for (k = 0; count < 4 && k < 14; k++) {
                            if (D_8010EDB4_toadstool_titan[k] != 0) {
                                continue;
                            }
                            D_8010EDB4_toadstool_titan[k] = 1;
                            D_8010F3D0_toadstool_titan[k] = (count & 1) ? 25.0f : -25.0f;
                            D_8010F408_toadstool_titan[k] = (count / 2) ? 25.0f : -25.0f;
                            D_8010F440_toadstool_titan[k] = rand8() / 255.0 * 50.0 - 25.0;
                            D_8010F478_toadstool_titan[k] = rand8() / 255.0 * 15.0;
                            D_8010F4B0_toadstool_titan[k] = 30.0 - rand8() / 255.0 * 10.0;
                            D_8010F4B0_toadstool_titan[k] = HuSqrtf(D_8010F478_toadstool_titan[k] * D_8010F478_toadstool_titan[k] +
                                                                    D_8010F4B0_toadstool_titan[k] * D_8010F4B0_toadstool_titan[k]);
                            D_8010F4E8_toadstool_titan[k] = rand8() / 255.0 * 20.0;
                            D_8010F478_toadstool_titan[k] =
                                (D_8010F3D0_toadstool_titan[k] < 0.0f) ? -D_8010F478_toadstool_titan[k] : D_8010F478_toadstool_titan[k];
                            D_8010F4E8_toadstool_titan[k] =
                                (D_8010F440_toadstool_titan[k] < 0.0f) ? -D_8010F4E8_toadstool_titan[k] : D_8010F4E8_toadstool_titan[k];
                            D_8010F3D0_toadstool_titan[k] += D_8010F5D0_toadstool_titan[j]->trans.x;
                            D_8010F408_toadstool_titan[k] += D_8010F5D0_toadstool_titan[j]->trans.y;
                            D_8010F440_toadstool_titan[k] += D_8010F5D0_toadstool_titan[j]->trans.z;
                            func_8001C258_main(object->model[29 + k], 4, 0);
                            func_8001C258_main(object->model[43 + k], 4, 0);
                            count++;
                        }
                    }
                }
            }
            if (D_8010F586_toadstool_titan == 1) {
                break;
            }
            if (D_8010F61C_toadstool_titan >= 55) {
                D_8010F586_toadstool_titan = 3;
                D_8010F61C_toadstool_titan = 0;
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[1], 4, 4);
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[56], 4, 4);
                msmMusSetVolume(D_800CDBC8_main, D_8010F600_toadstool_titan);
                break;
            }
            if (D_8010F61C_toadstool_titan == 35) {
                f32 visible = 0.0f;

                for (j = 0; j < 9; j++) {
                    if (D_8010F650_toadstool_titan[j] != 0) {
                        visible += 1.0f;
                        func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                        func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
                    }
                }
                D_8010EDCD_toadstool_titan = 1;
                if (visible > 0.0f) {
                    HuAudFXPlay(0x3A9);
                }
            } else if (D_8010F61C_toadstool_titan == 42) {
                for (j = 0; j < 9; j++) {
                    D_8010F650_toadstool_titan[j] = 0;
                    for (k = 0; k < 4; k++) {
                        func_800E149C_minigame(D_8010F640_toadstool_titan[k], j + 1, 1);
                    }
                }
            } else if (D_8010F61C_toadstool_titan == 45) {
                for (j = 0; j < 9; j++) {
                    func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 4);
                    func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 4);
                }
            }
            if (D_8010F61C_toadstool_titan < 7) {
                f32 bounce = (D_8010F61C_toadstool_titan + 1) / 7.0;

                bounce = 2.0f * bounce - 1.0f;
                bounce = -(bounce * bounce - 1.0f);
                D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.y = bounce * 25.0f + 375.0f;
                Hu3DData[D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->model[0]].pos.y = bounce * 25.0f + 375.0f;
            } else if (D_8010F61C_toadstool_titan >= 12 && D_8010F61C_toadstool_titan < 45) {
                if (D_8010F61C_toadstool_titan < 35) {
                    t = (D_8010F61C_toadstool_titan - 12) / 23.0;
                } else {
                    t = 1.0f;
                }
                func_8001C258_main(object->model[1], 4, 0);
                Hu3DModelPosSet(object->model[1], D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.x,
                                t * 75.0f + D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.y + 12.5,
                                D_8010F5D0_toadstool_titan[D_8010F620_toadstool_titan]->trans.z - 25.0f);
                if (D_8010F61C_toadstool_titan == 12) {
                    func_800E1BA8_minigame_ObjData *playerData;
                    s32 n;

                    HuAudFXPlay(0x3A8);
                    for (n = 0; n < 4; n++) {
                        playerData = D_8010F640_toadstool_titan[i]->data;
                        playerData->unkC4 = -1;
                        playerData->unkC5 = -1;
                    }
                }
            } else if (D_8010F61C_toadstool_titan >= 45) {
                f32 dx;
                f32 dy;
                f32 dz;
                f32 dist;
                f32 bestDist;

                bestDist = 32767.0f;
                k = -1;
                if (D_8010F61C_toadstool_titan == 45) {
                    s32 dir = rand8() / 256.0 * 360.0;

                    D_8010F610_toadstool_titan = Hu3DData[object->model[1]].pos.x;
                    D_8010F664_toadstool_titan = Hu3DData[object->model[1]].pos.y;
                    D_8010F604_toadstool_titan = Hu3DData[object->model[1]].pos.z;
                    D_8010F5B8_toadstool_titan = cosdf(dir) * 7.0f;
                    D_8010F608_toadstool_titan = -sindf(dir) * 7.0f;
                    D_8010F58C_toadstool_titan = 0.0f;
                }
                D_8010F610_toadstool_titan += D_8010F5B8_toadstool_titan;
                D_8010F664_toadstool_titan += D_8010F58C_toadstool_titan;
                D_8010F604_toadstool_titan += D_8010F608_toadstool_titan;
                D_8010F58C_toadstool_titan -= 3.0f;
                if (D_8010F664_toadstool_titan < 50.0f) {
                    D_8010F664_toadstool_titan = 50.0f;
                    D_8010F58C_toadstool_titan = 0.0f;
                }
                if (D_8010F610_toadstool_titan < -450.0f) {
                    D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan - 900.0f;
                    D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
                }
                if (D_8010F610_toadstool_titan > 450.0f) {
                    D_8010F610_toadstool_titan = -D_8010F610_toadstool_titan + 900.0f;
                    D_8010F5B8_toadstool_titan = -D_8010F5B8_toadstool_titan;
                }
                if (D_8010F604_toadstool_titan < -400.0f) {
                    D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan - 800.0f;
                    D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
                }
                if (D_8010F604_toadstool_titan > 400.0f) {
                    D_8010F604_toadstool_titan = -D_8010F604_toadstool_titan + 800.0f;
                    D_8010F608_toadstool_titan = -D_8010F608_toadstool_titan;
                }
                Hu3DModelPosSet(object->model[1], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
                Hu3DModelPosSet(object->model[56], D_8010F610_toadstool_titan, 0.0f, D_8010F604_toadstool_titan);
                func_8001C258_main(object->model[56], 4, 0);
                for (j = 0; j < 4; j++) {
                    dx = D_8010F640_toadstool_titan[j]->trans.x - D_8010F610_toadstool_titan;
                    dy = (D_8010F640_toadstool_titan[j]->trans.y + 75.0f - D_8010F664_toadstool_titan) / 1.75;
                    dz = D_8010F640_toadstool_titan[j]->trans.z - D_8010F604_toadstool_titan;
                    dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
                    if (dist <= 100.0f && dist < bestDist) {
                        k = j;
                        bestDist = dist;
                    }
                }
                if (k != -1) {
                    D_8010F60E_toadstool_titan = k;
                    D_8010F61C_toadstool_titan = 54;
                } else {
                    D_8010F61C_toadstool_titan = 46;
                }
                if (D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) {
                    D_8010F586_toadstool_titan = 9;
                    D_8010F61C_toadstool_titan = 0;
                    func_8001C258_main(object->model[1], 4, 4);
                    func_8001C258_main(object->model[56], 4, 4);
                    func_8001C258_main(object->model[57], 4, 0);
                    Hu3DModelPosSet(object->model[57], D_8010F610_toadstool_titan, D_8010F664_toadstool_titan, D_8010F604_toadstool_titan);
                    func_8010B4D4_toadstool_titan(object->model[57], 6);
                }
            }
            break;
        case 3:
            if ((D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6) && D_8010F61C_toadstool_titan >= 2 &&
                D_8010EDD0_toadstool_titan == 0) {
                D_8010F586_toadstool_titan = 9;
                D_8010F61C_toadstool_titan = 0;
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
                D_8010EDD0_toadstool_titan = 1;
            }
            if (D_8010F61C_toadstool_titan == 1) {
                D_8010EDCE_toadstool_titan = 1;
                if (D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A670_main(90);
                    D_8010F614_toadstool_titan[0] = 0;
                }
                HuAudFXPlay(0x3AB);
                omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
                if (!(D_8010F5FC_toadstool_titan == 5 || D_8010F5FC_toadstool_titan == 6)) {
                    func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 12);
                }
                Hu3DModelLayerSet(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x800);
                for (j = 0; j < 5; j++) {
                    Hu3DModelLayerSet(D_8010F5F8_toadstool_titan->model[3 + j], 0x800);
                }
            } else if (D_8010F61C_toadstool_titan == 46) {
                func_800E5690_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 0);
            } else if (D_8010F61C_toadstool_titan >= 55) {
                D_8010F586_toadstool_titan = 4;
                D_8010F61C_toadstool_titan = 0;
                for (j = 0; j < 5; j++) {
                    Hu3DModelLayerSet(D_8010F5F8_toadstool_titan->model[3 + j], 0x400);
                }
            }
            break;
        case 4:
            if (D_8010F61C_toadstool_titan == 3) {
                func_800E1BA8_minigame_ObjData *work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;

                work->unkC5 = func_8004AC98_main(0x3A7, work->unk59);
                work->unkC4 = -1;
                omVibrate(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->playerNo, 10, 0, 10);
            }
            Hu3DModelScaleSet(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[1],
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.x,
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.y,
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.z);
            if (D_8010F61C_toadstool_titan < 24) {
                u8 pulse[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };
                f32 scale;

                scale = pulse[D_8010F61C_toadstool_titan & 7];
                scale = (D_8010F61C_toadstool_titan < 12) ? scale * 0.5 + 1.0 : 2.0 - scale * 0.5;
                omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], scale, scale, scale);
            } else {
                omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
            }
            if (D_8010F61C_toadstool_titan >= 35) {
                func_800E1BA8_minigame_ObjData *work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;

                if (D_8010F5FC_toadstool_titan == 2) {
                    work->unk50 |= 0x400;
                }
                D_8010F586_toadstool_titan = 5;
                D_8010F61C_toadstool_titan = (D_8010F5FC_toadstool_titan != 2) ? 150 : 0;
                Hu3DModelLayerSet(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[0], 0x400);
                if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_80003A70_main(D_800CDBC8_main);
                    func_8004A5C4_main(0x45);
                    D_8010F614_toadstool_titan[1] = 1;
                }
            }
            break;
        case 5:
            omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 2.0f, 2.0f, 2.0f);
            if (D_8010F61C_toadstool_titan >= 150) {
                func_800E1BA8_minigame_ObjData *work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;

                work->unk50 &= ~0x400;
                D_8010F586_toadstool_titan = 6;
                D_8010F61C_toadstool_titan = 0;
                if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0) {
                    func_8004A7C4_main(40);
                    D_8010F614_toadstool_titan[1] = 0;
                }
            } else {
                for (i = 0; i < 4; i++) {
                    if (D_8010F616_toadstool_titan[i] == 0 && D_8010F60E_toadstool_titan != i && D_8010F5FC_toadstool_titan == 2) {
                        f32 dx;
                        f32 dy;
                        f32 dz;

                        dx = D_8010F640_toadstool_titan[i]->trans.x - D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x;
                        dx *= dx;
                        dy = D_8010F640_toadstool_titan[i]->trans.y - D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.y;
                        dy *= 0.5;
                        dy *= dy;
                        dz = D_8010F640_toadstool_titan[i]->trans.z - D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z;
                        dz *= dz;
                        if (dx + dy + dz < 22500.0f && D_8010F640_toadstool_titan[i]->trans.y < 270.0f) {
                            func_800E1BA8_minigame_ObjData *work = D_8010F640_toadstool_titan[i]->data;

                            work->unk50 |= 0x400;
                            work->unkC5 = func_8004AC98_main(0x3A6, work->unk59);
                            work->unkC4 = -1;
                            omVibrate(D_8010F568_toadstool_titan[i]->playerNo, 20, 0, 20);
                            D_8010F616_toadstool_titan[i] = 1;
                            D_8010F659_toadstool_titan[i] =
                                (D_8010F640_toadstool_titan[i]->trans.x < D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x) ? 0 : 1;
                            D_8010F66C_toadstool_titan -= (D_8010F568_toadstool_titan[i]->cpuDifficulty == -1) ? 1 : 0;
                            for (j = 0, k = 0; j < 4; j++) {
                                k += D_8010F616_toadstool_titan[j] != 0;
                            }
                            if (k == 3) {
                                D_8010F58A_toadstool_titan = D_8010F60E_toadstool_titan;
                                D_8010F61C_toadstool_titan = 120;
                            }
                        }
                    }
                }
            }
            break;
        case 6:
            if (D_8010F61C_toadstool_titan < 24) {
                u8 pulse[8] = { 0, 1, 0, 1, 0, 1, 0, 1 };
                f32 scale;

                scale = pulse[D_8010F61C_toadstool_titan & 7];
                scale = (D_8010F61C_toadstool_titan < 6) ? scale * 0.5 + 1.5 : 1.5 - scale * 0.5;
                omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], scale, scale, scale);
                if (D_8010F61C_toadstool_titan == 1) {
                    func_800E1BA8_minigame_ObjData *work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;

                    work->unkC5 = func_8004AC98_main(0x3A4, work->unk59);
                    work->unkC4 = -1;
                }
            } else {
                omSetSca(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 1.0f, 1.0f, 1.0f);
            }
            Hu3DModelScaleSet(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->model[1],
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.x,
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.y,
                              D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->scale.z);
            if (D_8010F61C_toadstool_titan == 13) {
                if (D_8010F5FC_toadstool_titan == 2) {
                    D_8010F586_toadstool_titan = 7;
                    D_8010F61C_toadstool_titan = 0;
                } else {
                    D_8010F586_toadstool_titan = 9;
                    D_8010F61C_toadstool_titan = 0;
                    func_800E5A00_minigame(D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan], 13,
                                           func_80017BB8_main(D_8010F568_toadstool_titan[D_8010F60E_toadstool_titan]->chr,
                                                              D_8010F568_toadstool_titan[i]->unk_0C),
                                           1, 120);
                }
            }
            break;
        case 7:
            if (D_8010F61C_toadstool_titan == 1) {
                for (j = 0; j < 9; j++) {
                    func_8001C258_main(D_8010F5F8_toadstool_titan->model[8 + j], 4, 0);
                    func_8010B4D4_toadstool_titan(D_8010F5F8_toadstool_titan->model[8 + j], 0);
                }
                D_8010EDCD_toadstool_titan = 1;
                HuAudFXPlay(0x3A9);
                if (D_8010F5FC_toadstool_titan == 2 && D_8010F5BC_toadstool_titan == 0 && D_800D530C_main == 0 &&
                    D_8010F614_toadstool_titan[0] == 0) {
                    msmMusStop(D_800D037E_main);
                    func_80003B70_main(D_800CDBC8_main, 0);
                    func_8004A72C_main(35);
                    D_8010F614_toadstool_titan[0] = 1;
                }
            }
            if (D_8010F61C_toadstool_titan == 10) {
                D_8010F586_toadstool_titan = 1;
                D_8010F61C_toadstool_titan = 0;
                for (j = 0; j < 9; j++) {
                    D_8010F650_toadstool_titan[j] = 1;
                    func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[0], 4, 0);
                    func_8001C258_main(D_8010F5D0_toadstool_titan[j]->model[1], 4, 0);
                    for (k = 0; k < 4; k++) {
                        func_800E149C_minigame(D_8010F640_toadstool_titan[k], j + 1, 2);
                    }
                }
                j = (u8)(rand8() % 9);
                k = (u8)(rand8() % 9);
                while (j == k) {
                    k = (u8)(rand8() % 9);
                }
                D_8010F650_toadstool_titan[k] = 2;
                D_8010F650_toadstool_titan[j] = 2;
            }
            break;
        case 9:
            if (D_8010F5FC_toadstool_titan >= 3 && D_8010F58A_toadstool_titan < 4 && D_8010F61C_toadstool_titan >= 7) {
                func_800E1BA8_minigame_ObjData *winnerData = D_8010F640_toadstool_titan[D_8010F58A_toadstool_titan]->data;

                winnerData->unk3C = (winnerData->unk3C < -10.0f)  ? (winnerData->unk3C + 9.0f) - winnerData->unk3C * 0.1
                                    : (winnerData->unk3C > 10.0f) ? (winnerData->unk3C - 9.0f) - winnerData->unk3C * 0.1
                                                                  : 0.0f;
            }
            break;
    }
    for (i = 0; i < 4; i++) {
        data = D_8010F640_toadstool_titan[i]->data;
        data->unk53[3] = 0;
        if (D_8010F616_toadstool_titan[i] != 0 && D_8010F616_toadstool_titan[i] < 60) {
            func_800E5690_minigame(D_8010F640_toadstool_titan[i], 18);
            Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].motTime = 0.0f;
            Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].motSpeed = 0.0f;
            func_800E4E30_minigame(D_8010F640_toadstool_titan[i]);
            Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].unk0E = Hu3DData[D_8010F640_toadstool_titan[i]->model[0]].unk0C;
            func_800E5138_minigame(D_8010F640_toadstool_titan[i]);
            D_8010F640_toadstool_titan[i]->trans.x += sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y += cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F640_toadstool_titan[i]->rot.y += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.z += 33.0f;
            D_8010F640_toadstool_titan[i]->rot.x = 0.0f;
            D_8010F640_toadstool_titan[i]->trans.x += (D_8010F659_toadstool_titan[i] != 0) ? 30.0f : -30.0f;
            D_8010F640_toadstool_titan[i]->trans.y +=
                (D_8010F616_toadstool_titan[i] < 14) ? (1.0 - D_8010F616_toadstool_titan[i] / 13.0) * 65.0 + 15.0 : 15.0;
            D_8010F640_toadstool_titan[i]->trans.x -= sindf(D_8010F640_toadstool_titan[i]->rot.z) * -50.0f;
            D_8010F640_toadstool_titan[i]->trans.y -= cosdf(D_8010F640_toadstool_titan[i]->rot.z) * 50.0f;
            D_8010F616_toadstool_titan[i]++;
            if (D_8010F616_toadstool_titan[i] == 15) {
                data->unkC5 = PlayerFXPlay(0x286, data->unk59);
                data->unkC4 = -1;
            }
        }
    }
    for (j = 0; j < 9; j++) {
        if (D_8010EDC4_toadstool_titan[j] != 0) {
            if (D_8010EDC4_toadstool_titan[j] > 60) {
                D_8010EDC4_toadstool_titan[j] = 0;
                func_8001C258_main(object->model[17 + j], 4, 4);
            } else {
                D_8010EDC4_toadstool_titan[j]++;
            }
        }
    }
    if (D_8010EDCD_toadstool_titan != 0) {
        if (D_8010EDCD_toadstool_titan > 18) {
            D_8010EDCD_toadstool_titan = 0;
            for (j = 0; j < 9; j++) {
                func_8001C258_main(object->model[8 + j], 4, 4);
            }
        } else {
            D_8010EDCD_toadstool_titan++;
        }
    }
    for (j = 0; j < 14; j++) {
        if (D_8010EDB4_toadstool_titan[j] != 0) {
            if (D_8010EDB4_toadstool_titan[j] > 12) {
                D_8010EDB4_toadstool_titan[j] = 0;
                func_8001C258_main(object->model[29 + j], 4, 4);
                func_8001C258_main(object->model[43 + j], 4, 4);
            } else {
                D_8010EDB4_toadstool_titan[j]++;
                D_8010F4B0_toadstool_titan[j] -= 5.0f;
                D_8010F3D0_toadstool_titan[j] += D_8010F478_toadstool_titan[j];
                D_8010F408_toadstool_titan[j] += D_8010F4B0_toadstool_titan[j];
                D_8010F440_toadstool_titan[j] += D_8010F4E8_toadstool_titan[j];
                if (D_8010F408_toadstool_titan[j] < 0.0f) {
                    D_8010F408_toadstool_titan[j] = 0.0f;
                    D_8010F4B0_toadstool_titan[j] = -D_8010F4B0_toadstool_titan[j] * 0.3;
                }
                Hu3DModelPosSet(object->model[29 + j], D_8010F3D0_toadstool_titan[j], D_8010F408_toadstool_titan[j], D_8010F440_toadstool_titan[j]);
                Hu3DModelPosSet(object->model[43 + j], D_8010F3D0_toadstool_titan[j], 0.0f, D_8010F440_toadstool_titan[j]);
            }
        }
    }
    if (D_8010EDCE_toadstool_titan != 0 && D_8010EDD0_toadstool_titan == 0) {
        HuMtx4F mtx;
        HuCamera *camera;
        f32 ease;

        camera = gCameraList;
        camMtxs = &camera->mtxs[D_800D418E_main];
        D_8010EDD4_toadstool_titan = D_8010EDDC_toadstool_titan = 0.0f;
        if (D_8010EDCE_toadstool_titan == 1) {
            func_8001F9E4_main(object->model[3], 0xFF);
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 1 && D_8010EDCE_toadstool_titan < 55) {
            if (D_8010EDCE_toadstool_titan < 15) {
                ease = 1.0 - D_8010EDCE_toadstool_titan / 15.0;
                ease = 1.0f - ease * ease * ease;
                D_8010EDD4_toadstool_titan = ease * 100.0f;
            } else {
                D_8010EDD4_toadstool_titan = 90.0f;
            }
            if (D_8010EDCE_toadstool_titan < 45) {
                D_8010EDD4_toadstool_titan += D_8010EDCE_toadstool_titan / 45.0 * 125.0;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan <= 55) {
                ease = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                ease = 1.0 - (ease * ease * 0.75 + ease * 0.25);
                D_8010EDD4_toadstool_titan = 215.0f - ease * 180.0f;
            }
            if (D_8010EDCE_toadstool_titan < 55) {
                ease = D_8010EDCE_toadstool_titan / 45.0;
                D_8010EDD8_toadstool_titan += ease * 7.0f + 8.0f;
            }
            if (D_8010EDCE_toadstool_titan >= 45 && D_8010EDCE_toadstool_titan < 55) {
                ease = 1.0 - (D_8010EDCE_toadstool_titan - 45) / 10.0;
                ease = 1.0 - (ease * ease * 0.75 + ease * 0.25);
                D_8010EDD8_toadstool_titan += ease * 12.0f;
            }
        }
        if (D_8010EDCE_toadstool_titan == 55) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 0);
            }
        } else if (D_8010EDCE_toadstool_titan == 85) {
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[2], 4, 4);
            }
        }
        if (D_8010EDCE_toadstool_titan >= 55 && D_8010EDCE_toadstool_titan < 85) {
            ease = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
            ease = ease * ease * 0.75 + ease * 0.25;
            D_8010EDDC_toadstool_titan = 2.0 * (1.0f - ease) + 1.0;
            if (D_8010EDCE_toadstool_titan >= 75) {
                D_8010EDD8_toadstool_titan += 5.0f;
            } else {
                D_8010EDD8_toadstool_titan += (1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0) * 15.0;
            }
            D_8010EDE0_toadstool_titan = 1.0 - (D_8010EDCE_toadstool_titan - 55) / 30.0;
        }
        if (D_8010EDD4_toadstool_titan > 0.0f) {
            for (j = 0; j < 5; j++) {
                f32 weight;
                f32 speed;
                f32 halfSpeed;
                f32 invWeight;

                if (D_8010EDCE_toadstool_titan >= 45) {
                    weight = (D_8010EDCE_toadstool_titan - 45) / 10.0;
                } else {
                    weight = 0.0f;
                }
                invWeight = 1.0f - weight;
                x = weight * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x + invWeight * Hu3DData[object->model[1]].pos.x;
                y = (D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.y + 175.0f) * weight +
                    invWeight * Hu3DData[object->model[1]].pos.y;
                z = (D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z + 85.0f) * weight +
                    invWeight * Hu3DData[object->model[1]].pos.z;
                guMtxL2F(mtx, &camMtxs->lookAtMtx);
                angle = j * 72;
                mtxTransCat(mtx, cosdf(angle + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + x,
                            sindf(angle + D_8010EDD8_toadstool_titan) * D_8010EDD4_toadstool_titan + y, z);
                mtx[0][0] = 0.45f;
                mtx[0][1] = 0.0f;
                mtx[0][2] = 0.0f;
                mtx[1][0] = 0.0f;
                mtx[1][1] = 0.45f;
                mtx[1][2] = 0.0f;
                mtx[2][0] = 0.0f;
                mtx[2][1] = 0.0f;
                mtx[2][2] = 0.45f;
                func_8002367C_main(Hu3DData[D_8010F5F8_toadstool_titan->model[3 + j]].mtx, mtx);
            }
        }
        if (D_8010EDDC_toadstool_titan > 0.0f) {
            x = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x;
            y = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.y + 175.0f;
            z = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z + 85.0f;
            guMtxL2F(mtx, &camMtxs->lookAtMtx);
            mtxTransCat(mtx, x, y, z);
            mtx[0][0] = -sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mtx[0][1] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mtx[0][2] = 0.0f;
            mtx[1][0] = cosdf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mtx[1][1] = sindf(D_8010EDD8_toadstool_titan) * D_8010EDDC_toadstool_titan;
            mtx[1][2] = 0.0f;
            mtx[2][0] = 0.0f;
            mtx[2][1] = 0.0f;
            mtx[2][2] = D_8010EDDC_toadstool_titan;
            func_8002367C_main(Hu3DData[D_8010F5F8_toadstool_titan->model[2]].mtx, mtx);
            func_8001F9E4_main(object->model[2], D_8010EDE0_toadstool_titan * 255.0f);
        }
        if (++D_8010EDCE_toadstool_titan == 90) {
            D_8010EDCE_toadstool_titan = 0;
        }
    } else if (D_8010EDD0_toadstool_titan != 0) {
        f32 fade;

        fade = 1.0 - D_8010EDD0_toadstool_titan / 20.0;
        func_8001F9E4_main(object->model[3], (s32)(fade * fade * 255.0f));
        if (++D_8010EDD0_toadstool_titan == 20) {
            D_8010EDD0_toadstool_titan = 0;
            D_8010EDCE_toadstool_titan = 0;
            for (j = 0; j < 5; j++) {
                func_8001C258_main(D_8010F5F8_toadstool_titan->model[3 + j], 4, 4);
            }
        }
    }
    if (D_8010F586_toadstool_titan == 5) {
        D_8010EDE4_toadstool_titan = (s16)(D_8010EDE4_toadstool_titan + 1) % 51;
        if (D_8010EDE4_toadstool_titan % 17 == 0) {
            s32 cloud = D_8010EDE4_toadstool_titan / 17;

            D_8010EDE8_toadstool_titan[cloud] = 0;
            func_8010B4D4_toadstool_titan(object->model[26 + cloud], 0);
            func_8001C258_main(object->model[26 + cloud], 4, 0);
            Hu3DModelPosSet(object->model[26 + cloud], D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x * 0.9, 300.0f,
                            D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z - 15.0f);
        }
    } else {
        D_8010EDE4_toadstool_titan = 0;
    }
    for (j = 0; j < 3; j++) {
        D_8010EDE8_toadstool_titan[j] += (D_8010EDE8_toadstool_titan[j] >= 55) ? 0 : 1;
        if (D_8010EDE8_toadstool_titan[j] >= 55) {
            D_8010EDE8_toadstool_titan[j] = 55;
            func_8001C258_main(object->model[26 + j], 4, 4);
        }
    }
}

void func_8010AD8C_toadstool_titan(s16 left, s16 top, s16 right, s16 bottom) {
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 scaleX;
    f32 scaleY;
    f32 offsetX;
    f32 offsetY;
    f32 s0;
    f32 t0;
    f32 s1;
    f32 t1;
    s32 dsdx;
    s32 dtdy;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;
    s32 i;
    s32 j;

    scaleX = (right - left) / 320.0;
    offsetX = left;
    dsdx = (1.0 / scaleX) * 1024.0;
    scaleY = (bottom - top) / 240.0;
    offsetY = top;
    dtdy = (1.0 / scaleY) * 1024.0;

    gSPDisplayList(gMainGfxPos++, D_8010EDF0_toadstool_titan);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    sprite = HuSprGet(D_800CD1DC_main[D_8010F588_toadstool_titan[0]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
    for (i = 0; i < 6; i++) {
        t0 = i * 40;
        t1 = t0 + 40.0f + ((i == 5) ? -0.75 : 1.0);
        for (j = 0; j < 8; j++) {
            s0 = j * 40;
            s1 = s0 + 40.0f + ((j < 7) ? 1.0f : 0.0f);
            xl = (scaleX * s0 + offsetX) * 4.0f;
            yl = (scaleY * t0 + offsetY) * 4.0f;
            xh = (scaleX * s1 + offsetX) * 4.0f;
            yh = (scaleY * t1 + offsetY) * 4.0f;
            if (xl > 1280 || yl > 960) {
                continue;
            }
            if (xh < 0 || yh < 0) {
                continue;
            }
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 320, 240, (s32)s0, (s32)t0, (s32)s1,
                               (s32)t1, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s0 * 32.0f, t0 * 32.0f, dsdx, dtdy);
        }
    }
}

void func_8010B4D4_toadstool_titan(s16 model, s16 time) {
    Hu3DMotionTimeSet(model, time);
}

void func_8010B510_toadstool_titan(omObjData *object) {
    Vec up;

    if (D_8010EE38_toadstool_titan == 0) {
        D_8010EE38_toadstool_titan = 1;
        D_8010F628_toadstool_titan.x = 0.0f;
        D_8010F628_toadstool_titan.y = 868.0f;
        D_8010F628_toadstool_titan.z = 1561.0f;
        D_8010F5C0_toadstool_titan.x = 0.0f;
        D_8010F5C0_toadstool_titan.y = -100.0f;
        D_8010F5C0_toadstool_titan.z = -485.0f;
        D_8010F624_toadstool_titan = 32.5f;
    }
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    D_800CE17C_main[0] = D_8010F628_toadstool_titan.x;
    D_800CE17C_main[1] = D_8010F628_toadstool_titan.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPerspectiveSet(0, D_8010F624_toadstool_titan, 800.0f, 2750.0f);
    Hu3DCameraPosSetV(0, &D_8010F628_toadstool_titan, &D_8010F5C0_toadstool_titan, &up);
    Hu3DCamUpdateMtx(0);
}

void func_8010B658_toadstool_titan(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 dirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 slots[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 files[2][8] = { { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B }, { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C } };
    func_800E1BA8_minigame_ObjData *data;
    s32 modelFlags;
    s32 motionFlags;
    u16 chr;

    modelFlags = 0x4A9;
    motionFlags = 0x99;
    chr = D_8010F568_toadstool_titan[group]->chr;
    func_800E18D8_minigame();
    func_800E1BA8_minigame(object, model, motion, D_8010F568_toadstool_titan[group]->playerNo, modelFlags, motionFlags);
    omSetTra(object, x, y, z);
    Hu3DModelPosSet(object->model[1], x, 0.0f, z);
    data = object->data;
    data->unk59 = D_8010F568_toadstool_titan[group]->playerNo;
    D_8010F568_toadstool_titan[group]->unk_0C = (rand8() & 1) ? 0x2F : 0x30;
    D_8010F568_toadstool_titan[group]->unk_0C |= dirs[chr] << 16;
    D_8010F568_toadstool_titan[group]->unk_06 = func_80017790_main(object->model[0], 1, slots[chr], (dirs[chr] << 16) | files[0][chr]);
    D_8010F568_toadstool_titan[group]->unk_08 = func_80017AD8_main((dirs[chr] << 16) | files[1][chr]);
    func_80033910_main(Hu3DData[object->model[0]].hmf);
    func_8001C514_main(object->model[0]);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5978_minigame(object, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E149C_minigame(object, 0, 2);
}

void func_8010B99C_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[0]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[0]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 0, (D_8010F668_toadstool_titan[0] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[0] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BA80_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[1]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[1]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 1, (D_8010F668_toadstool_titan[1] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[1] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BB64_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[2]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[2]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 2, (D_8010F668_toadstool_titan[2] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[2] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

void func_8010BC48_toadstool_titan(omObjData *object) {
    s32 motion;
    s32 model;

    motion = D_800A178C_main[D_8010F568_toadstool_titan[3]->chr][3];
    model = D_800A178C_main[D_8010F568_toadstool_titan[3]->chr][0];
    func_8010B658_toadstool_titan(object, model, motion, 3, (D_8010F668_toadstool_titan[3] >> 1) ? -400.0f : 400.0f, 800.0f,
                                  (D_8010F668_toadstool_titan[3] & 1) ? -350.0f : 350.0f);
    object->func = func_8010BD2C_toadstool_titan;
}

// Only differs in the two D_800D20A1_main stick computations (cases 2/3 and
// 11/12): the target converts the int result of (dist > 33.0f) to double rather
// than loading 1.0. Writing them with the GNU omitted-middle-operand form
// `((dist > 33.0f) ?: dist / 33.0)` gives a full match; standard C forms tried
// (`c ? c : ...`, `(double)` cast, inverted condition, MIN) do not.
#ifdef NON_MATCHING
void func_8010BD2C_toadstool_titan(omObjData *object) {
    u8 flags[4];
    func_800E1BA8_minigame_ObjData *data;
    u16 savedBtn;
    u16 savedBtn2;
    u16 savedBtn3;
    s8 savedStickX;
    s8 savedStickY;
    s16 savedStick2;
    s16 savedStick3;
    func_800E1BA8_minigame_ObjData *otherData;
    func_800E1BA8_minigame_ObjData *work;
    ToadstoolTitanPlayer *player;
    s16 group;
    s32 i;
    s32 best;
    f32 bestDist;
    f32 dz;
    f32 dx;
    f32 dist;
    f32 dirX;
    f32 dirZ;
    f32 cornerX;
    f32 cornerZ;
    f32 bestScore;
    f32 weight;
    f32 speed;
    f32 halfSpeed;
    f32 sinVal;
    f32 cosVal;
    f32 normX;
    f32 normZ;
    f32 signSin;
    f32 signCos;
    f32 hitX;
    f32 hitZ;
    f32 posX;
    f32 posZ;
    f32 otherX;
    f32 otherZ;
    f32 velX;
    f32 velZ;
    f32 otherVelX;
    f32 otherVelZ;
    s32 range;
    s32 rnd;
    s32 minTime;
    s32 newTime;
    s16 *timer;

    data = object->data;
    group = D_8010F65D_toadstool_titan[data->unk59];
    player = D_8010F568_toadstool_titan[group];
    // Computed but never read in the original.
    if (group == 0) {
        for (i = 0; i < 4; i++) {
            flags[i] = (D_8010F640_toadstool_titan[i]->trans.y <= 0.0f) ? 1 : ((D_8010F616_toadstool_titan[i] != 0) ? 2 : 0);
        }
    }
    (void)flags;
    savedBtn = D_800CDA7C_main[player->pad];
    savedBtn2 = D_800D5558_main[player->pad];
    savedBtn3 = D_800D1244_main[player->pad];
    savedStickX = D_800CBB6E_main[player->pad];
    savedStickY = D_800D20A1_main[player->pad];
    savedStick2 = D_800D056A_main[player->pad];
    savedStick3 = D_800D1382_main[player->pad];
    if (player->cpuDifficulty != -1) {
        s16 params[22][4] = {
            { 0, 0, 0, 0 },
            { 300, 300, 200, 150 },
            { 11, 9, 6, 3 },
            { 6, 6, 6, 6 },
            { 11, 9, 5, 2 },
            { 4, 4, 3, 1 },
            { -30, -40, -40, -200 },
            { 15, 20, 20, 100 },
            { 45, 35, 25, 25 },
            { 1, 1, 1, 15 },
            { 36, 46, 56, 66 },
            { 1, 1, 1, 1 },
            { 20, 20, 15, 15 },
            { 35, 25, 12, 8 },
            { 0, 0, 6, 6 },
            { 1, 8, 4, 5 },
            { 0, 24, 16, 32 },
            { 1, 8, 24, 1 },
            { 14, 9, 6, 0 },
            { 6, 8, 5, 7 },
            { 0, 0, 0, 0 },
            { 1, 1, 1, 1 },
        };

        D_800CDA7C_main[player->pad] = 0;
        D_800D5558_main[player->pad] = 0;
        D_800D1244_main[player->pad] = 0;
        D_800CBB6E_main[player->pad] = 0;
        D_800D20A1_main[player->pad] = 0;
        D_800D056A_main[player->pad] = 0;
        D_800D1382_main[player->pad] = 0;
        if (D_8010F616_toadstool_titan[group] != 0) {
            D_8010EE40_toadstool_titan[group] = 13;
        }
        if (D_8010F586_toadstool_titan == 2) {
            if (D_8010F61C_toadstool_titan >= ((D_8010F60E_toadstool_titan == group) ? 10 : 30)) {
                if (D_8010EE40_toadstool_titan[group] > 0 && D_8010EE40_toadstool_titan[group] < 4) {
                    D_8010EE40_toadstool_titan[group] = 10;
                    D_8010EE44_toadstool_titan[group] = 0;
                }
            }
        }
        if (D_8010F586_toadstool_titan == 3) {
            if ((D_8010EE40_toadstool_titan[group] > 0 && D_8010EE40_toadstool_titan[group] < 4) ||
                (D_8010EE40_toadstool_titan[group] >= 10 && D_8010EE40_toadstool_titan[group] < 13)) {
                D_8010EE40_toadstool_titan[group] = (D_8010F60E_toadstool_titan == group) ? 4 : 7;
                D_8010EE44_toadstool_titan[group] = 0;
            }
        }
        if (D_8010F586_toadstool_titan == 7) {
            if ((D_8010EE40_toadstool_titan[group] >= 4 && D_8010EE40_toadstool_titan[group] < 7) ||
                (D_8010EE40_toadstool_titan[group] >= 7 && D_8010EE40_toadstool_titan[group] < 10)) {
                D_8010EE40_toadstool_titan[group] = 1;
                D_8010EE44_toadstool_titan[group] = params[12][player->cpuDifficulty] + rand8() % params[13][player->cpuDifficulty];
                D_8010EE4C_toadstool_titan[group] = 0;
            }
        }
        switch (D_8010EE40_toadstool_titan[group]) {
            case 0:
                D_8010EE40_toadstool_titan[group] = 1;
                D_8010EE44_toadstool_titan[group] = 5;
            case 1:
                D_8010EE44_toadstool_titan[group] -= (D_8010EE44_toadstool_titan[group] > 0) ? 1 : 0;
                if (D_8010EE44_toadstool_titan[group] > 0) {
                    break;
                }
                for (i = 0, bestDist = 16777216.0f, best = -1; i < 9; i++) {
                    if (D_8010F650_toadstool_titan[i] != 0) {
                        dx = object->trans.x - D_8010F5D0_toadstool_titan[i]->trans.x;
                        dz = object->trans.z - D_8010F5D0_toadstool_titan[i]->trans.z;
                        dist = dx * dx + dz * dz + rand8() / 255.0 * params[1][player->cpuDifficulty] * params[1][player->cpuDifficulty];
                        if (dist < bestDist) {
                            bestDist = dist;
                            best = i;
                        }
                    }
                }
                if (best == -1) {
                    D_8010EE44_toadstool_titan[group] = 1;
                    break;
                }
                D_8010EE40_toadstool_titan[group] = 2;
                D_8010EE44_toadstool_titan[group] = best;
                D_8010EE4C_toadstool_titan[group] = 0;
                break;
            case 2:
            case 3:
                dx = D_8010F5D0_toadstool_titan[D_8010EE44_toadstool_titan[group]]->trans.x - object->trans.x;
                dz = D_8010F5D0_toadstool_titan[D_8010EE44_toadstool_titan[group]]->trans.z - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                D_800CBB6E_main[player->pad] = dx / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty];
                D_800D20A1_main[player->pad] = -(dz / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty]);
                if (object->trans.y > 375.0f && data->unk38 == 1000.0f) {
                    D_800CBB6E_main[player->pad] = 0;
                    D_800D20A1_main[player->pad] = 66;
                }
                if (D_8010EE40_toadstool_titan[group] == 3 && D_8010EE4C_toadstool_titan[group] == 0 && object->trans.y <= 0.0f) {
                    D_8010EE40_toadstool_titan[group] = 2;
                    D_8010EE4C_toadstool_titan[group] = 0;
                } else if (D_8010EE40_toadstool_titan[group] == 2 && D_8010EE4C_toadstool_titan[group] == 0 && object->trans.y <= 0.0f &&
                           (dist < 50.0f || data->unk53[1] != -1)) {
                    switch ((dist < 50.0f) ? 1 : rand8() % 5 / 2) {
                        case 0:
                            break;
                        case 1:
                            D_8010EE40_toadstool_titan[group] = 3;
                            D_800D5558_main[player->pad] |= 0x8000;
                            D_8010EE4C_toadstool_titan[group] = params[4][player->cpuDifficulty] + rand8() % params[5][player->cpuDifficulty];
                            break;
                        case 2:
                            D_8010EE40_toadstool_titan[group] = 1;
                            D_8010EE44_toadstool_titan[group] = params[2][player->cpuDifficulty] + rand8() % params[3][player->cpuDifficulty];
                            break;
                    }
                }
                if (D_8010EE40_toadstool_titan[group] == 3) {
                    D_800CDA7C_main[player->pad] |= 0x8000;
                }
                D_8010EE4C_toadstool_titan[group] -= (D_8010EE4C_toadstool_titan[group] > 0) ? 1 : 0;
                if (D_8010F650_toadstool_titan[D_8010EE44_toadstool_titan[group]] == 0) {
                    D_8010EE40_toadstool_titan[group] = 1;
                    D_8010EE44_toadstool_titan[group] = params[2][player->cpuDifficulty] + rand8() % params[3][player->cpuDifficulty];
                }
                break;
            case 4:
                D_8010EE44_toadstool_titan[group] -= (D_8010EE44_toadstool_titan[group] > 0) ? 1 : 0;
                work = D_8010F640_toadstool_titan[group]->data;
                if (D_8010EE44_toadstool_titan[group] > 0 || work->unk5C == 0x8000) {
                    break;
                }
                for (i = 0, bestDist = 16777216.0f, best = -1; i < 4; i++) {
                    if (i == group || D_8010F616_toadstool_titan[i] != 0) {
                        continue;
                    }
                    dx = object->trans.x - D_8010F640_toadstool_titan[i]->trans.x;
                    dz = object->trans.z - D_8010F640_toadstool_titan[i]->trans.z;
                    dist = dx * dx + dz * dz + params[6][player->cpuDifficulty] + rand8() % params[7][player->cpuDifficulty];
                    if (dist < bestDist) {
                        bestDist = dist;
                        best = i;
                    }
                }
                if (best == -1) {
                    D_8010EE44_toadstool_titan[group] = 1;
                    break;
                }
                D_8010EE40_toadstool_titan[group] = 5;
                D_8010EE44_toadstool_titan[group] = best;
                if (params[14][player->cpuDifficulty] + rand8() % params[15][player->cpuDifficulty] < 8) {
                    break;
                }
                dx = (D_8010F640_toadstool_titan[best]->trans.x > 0.0f) ? D_8010F640_toadstool_titan[best]->trans.x - 350.0f
                                                                        : -D_8010F640_toadstool_titan[best]->trans.x - 350.0f;
                dz = (D_8010F640_toadstool_titan[best]->trans.z > 0.0f) ? D_8010F640_toadstool_titan[best]->trans.z - 350.0f
                                                                        : -D_8010F640_toadstool_titan[best]->trans.z - 350.0f;
                if (dx * dx + dz * dz < 62500.0f) {
                    D_8010EE44_toadstool_titan[group] += 4;
                    D_8010EE54_toadstool_titan[group] = D_8010EE64_toadstool_titan[group] = 0.0f;
                    if (((D_8010F640_toadstool_titan[best]->trans.x - object->trans.x > 0.0f)
                             ? D_8010F640_toadstool_titan[best]->trans.x - object->trans.x
                             : -(D_8010F640_toadstool_titan[best]->trans.x - object->trans.x)) <
                        ((D_8010F640_toadstool_titan[best]->trans.z - object->trans.z > 0.0f)
                             ? D_8010F640_toadstool_titan[best]->trans.z - object->trans.z
                             : -(D_8010F640_toadstool_titan[best]->trans.z - object->trans.z))) {
                        D_8010EE54_toadstool_titan[group] = rand8() / 255.0 * 200.0 * ((D_8010F640_toadstool_titan[best]->trans.x < 0.0f) ? 1 : -1);
                    } else {
                        D_8010EE64_toadstool_titan[group] = rand8() / 255.0 * 200.0 * ((D_8010F640_toadstool_titan[best]->trans.z < 0.0f) ? 1 : -1);
                    }
                }
                break;
            case 5:
            case 6:
                dx = D_8010F640_toadstool_titan[D_8010EE44_toadstool_titan[group] % 4]->trans.x - object->trans.x +
                     ((D_8010EE44_toadstool_titan[group] >= 4) ? D_8010EE54_toadstool_titan[group] : 0.0f);
                dz = D_8010F640_toadstool_titan[D_8010EE44_toadstool_titan[group] % 4]->trans.z - object->trans.z +
                     ((D_8010EE44_toadstool_titan[group] >= 4) ? D_8010EE64_toadstool_titan[group] : 0.0f);
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                D_800CBB6E_main[player->pad] = dx / dist * ((dist > 33.0f) ? 66.0f : dist * 2);
                D_800D20A1_main[player->pad] = -(dz / dist * ((dist > 33.0f) ? 66.0f : dist * 2));
                if (D_8010EE40_toadstool_titan[group] == 5 && D_8010EE4C_toadstool_titan[group] <= 0 && D_8010EE3C_toadstool_titan != 0) {
                    D_8010EE40_toadstool_titan[group] = 6;
                    D_8010EE4C_toadstool_titan[group] = 0;
                }
                D_8010EE4C_toadstool_titan[group] -= (D_8010EE4C_toadstool_titan[group] > 0) ? 1 : 0;
                if (D_8010EE40_toadstool_titan[group] == 6 && D_8010EE3C_toadstool_titan == 0) {
                    D_8010EE40_toadstool_titan[group] = 4;
                    D_8010EE44_toadstool_titan[group] = params[8][player->cpuDifficulty] + rand8() % params[9][player->cpuDifficulty];
                }
                break;
            case 7:
                D_8010EE44_toadstool_titan[group] -= (D_8010EE44_toadstool_titan[group] > 0) ? 1 : 0;
                if (D_8010EE44_toadstool_titan[group] <= 0) {
                    D_8010EE40_toadstool_titan[group] = 8;
                    D_8010EE44_toadstool_titan[group] = -1;
                    D_8010EE4C_toadstool_titan[group] = 0;
                }
                break;
            case 8:
            case 9:
                if (D_8010EE44_toadstool_titan[group] == -1) {
                    bestScore = 100.0f;
                    dx = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x - object->trans.x;
                    dz = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z - object->trans.z;
                    dist = (dx != 0.0f || dz != 0.0f) ? 1.0f / HuSqrtf(dx * dx + dz * dz) : 0.000001f;
                    dirX = dx * dist;
                    dirZ = dz * dist;
                    for (i = 0, best = 0; i < 4; i++) {
                        cornerX = (i < 2) ? -400.0f : 400.0f;
                        dx = cornerX - object->trans.x;
                        cornerZ = ((i + 1) % 4 < 2) ? -350.0f : 350.0f;
                        dz = cornerZ - object->trans.z;
                        dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                        normX = dx / dist;
                        normZ = dz / dist;
                        bestDist = dirX * normX + dirZ * normZ + 1.0f;
                        weight = (dist == 16777216.0f) ? 10.0f : ((dist > 500.0f) ? 0.0f : 1.0 - dist / 500.0);
                        bestDist = bestDist * bestDist + weight * weight * 4.0f;
                        if (D_8010EE40_toadstool_titan[group] == 9) {
                            otherData = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
                            sinVal = sindf(otherData->unk3C);
                            cosVal = cosdf(otherData->unk3C);
                            dx = (sinVal > 0.0f) ? sinVal : -sinVal;
                            signSin = (sinVal < 0.0f) ? -1.0f : 1.0f;
                            dz = (cosVal > 0.0f) ? cosVal : -cosVal;
                            signCos = (cosVal < 0.0f) ? -1.0f : 1.0f;
                            hitZ = 1000.0f;
                            if (dz < dx) {
                                hitZ = (401.0f - signSin * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x) / dx * dz +
                                       signCos * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z;
                            }
                            if (hitZ > 351.0f) {
                                hitX = (351.0f - signCos * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z) / dz * dx +
                                       signSin * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x;
                                if (hitX > 401.0f) {
                                    hitZ = (401.0f - signSin * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x) / dx * dz +
                                           signCos * D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z;
                                    hitX = 401.0f;
                                } else {
                                    hitZ = 351.0f;
                                }
                            } else {
                                hitX = 401.0f;
                            }
                            hitX = hitX * signSin - cornerX;
                            hitZ = hitZ * signCos - cornerZ;
                            dist = (hitX != 0.0f || hitZ != 0.0f) ? HuSqrtf(hitX * hitX + hitZ * hitZ) : 0.0f;
                            bestDist += (dist > 600.0f) ? 0.0 : (1.0 - dist / 600.0) * 8.0;
                        }
                        if ((D_8010EE40_toadstool_titan[group] == 8 || D_8010EE40_toadstool_titan[group] == 9) && bestDist < bestScore) {
                            best = i;
                            bestScore = bestDist;
                        }
                        if (bestScore != 100.0f) {
                            D_8010EE44_toadstool_titan[group] = best;
                        }
                    }
                }
                dx = ((D_8010EE44_toadstool_titan[group] < 2) ? -400.0f : 400.0f) - object->trans.x;
                dz = (((D_8010EE44_toadstool_titan[group] + 1) % 4 < 2) ? -350.0f : 350.0f) - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                D_800CBB6E_main[player->pad] = dx / dist * ((dist > 70.0f) ? 70.0f : ((dist > 35.0f) ? dist : 0.0f));
                D_800D20A1_main[player->pad] = -(dz / dist * ((dist > 70.0f) ? 70.0f : ((dist > 35.0f) ? dist : 0.0f)));
                if (D_8010EE3C_toadstool_titan != 0) {
                    D_8010EE4C_toadstool_titan[group] -= (D_8010EE4C_toadstool_titan[group] > 0) ? 1 : 0;
                    if (D_8010EE4C_toadstool_titan[group] <= 0) {
                        D_8010EE40_toadstool_titan[group] = 9;
                        D_8010EE44_toadstool_titan[group] = -1;
                        range = params[19][player->cpuDifficulty];
                        timer = &D_8010EE4C_toadstool_titan[group];
                        rnd = rand8();
                        minTime = params[18][player->cpuDifficulty];
                        if (D_8010F66C_toadstool_titan == 0) {
                            minTime += 5;
                            newTime = minTime + rnd % (range + 12);
                        } else {
                            newTime = minTime + rnd % range;
                        }
                        *timer = newTime;
                    }
                } else {
                    D_8010EE4C_toadstool_titan[group] -= (D_8010EE4C_toadstool_titan[group] > 0) ? 1 : 0;
                    if (D_8010EE4C_toadstool_titan[group] <= 0) {
                        D_8010EE40_toadstool_titan[group] = 8;
                        D_8010EE44_toadstool_titan[group] = -1;
                        D_8010EE4C_toadstool_titan[group] = params[18][player->cpuDifficulty] + rand8() % params[19][player->cpuDifficulty];
                    }
                }
                if (data->unk38 != 1000.0f) {
                    D_800CDA7C_main[player->pad] |= 0x8000;
                } else if (D_8010F66C_toadstool_titan != 0) {
                    if (params[16][player->cpuDifficulty] + rand8() % params[17][player->cpuDifficulty] < 32) {
                        break;
                    }
                    posX = object->trans.x;
                    posZ = object->trans.z;
                    otherX = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.x;
                    otherZ = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->trans.z;
                    otherData = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
                    velX = sindf(data->unk3C) * data->unk40;
                    velZ = cosdf(data->unk3C) * data->unk40;
                    otherVelX = sindf(otherData->unk3C) * otherData->unk40;
                    otherVelZ = cosdf(otherData->unk3C) * otherData->unk40;
                    for (i = 0; i < 6; i++) {
                        if ((posX - otherX) * (posX - otherX) + (posZ - otherZ) * (posZ - otherZ) < 22500.0f) {
                            D_800CDA7C_main[player->pad] |= 0x8000;
                            D_800D5558_main[player->pad] |= 0x8000;
                            D_800D1244_main[player->pad] |= 0x8000;
                            break;
                        }
                        posX += velX;
                        posZ += velZ;
                        otherX += otherVelX;
                        otherZ += otherVelZ;
                    }
                }
                break;
            case 10:
                D_8010EE44_toadstool_titan[group] -= (D_8010EE44_toadstool_titan[group] > 0) ? 1 : 0;
                if (D_8010EE44_toadstool_titan[group] <= 0) {
                    D_8010EE40_toadstool_titan[group] = 11;
                    D_8010EE44_toadstool_titan[group] = 0;
                    D_8010EE4C_toadstool_titan[group] = 0;
                }
                break;
            case 11:
            case 12:
                dx = Hu3DData[D_8010F5F8_toadstool_titan->model[1]].pos.x - object->trans.x;
                dz = Hu3DData[D_8010F5F8_toadstool_titan->model[1]].pos.z - object->trans.z;
                dist = (dx != 0.0f || dz != 0.0f) ? HuSqrtf(dx * dx + dz * dz) : 16777216.0f;
                D_800CBB6E_main[player->pad] = dx / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty];
                D_800D20A1_main[player->pad] = -(dz / dist * ((dist > 33.0f) ? 1.0 : dist / 33.0) * params[10][player->cpuDifficulty]);
                if (D_8010EE40_toadstool_titan[group] == 12 && D_8010EE4C_toadstool_titan[group] == 0 && object->trans.y <= 0.0f) {
                    D_8010EE40_toadstool_titan[group] = 11;
                    D_8010EE4C_toadstool_titan[group] = 0;
                } else if (D_8010EE40_toadstool_titan[group] == 11 && D_8010EE4C_toadstool_titan[group] == 0 && object->trans.y <= 0.0f &&
                           player->cpuDifficulty > 0 && dist < 50.0f && D_8010F61C_toadstool_titan >= 42) {
                    switch ((dist < 50.0f) ? 1 : (rand8() & 3) < 3) {
                        case 1:
                            D_8010EE40_toadstool_titan[group] = 12;
                            D_800D5558_main[player->pad] |= 0x8000;
                            D_8010EE4C_toadstool_titan[group] = params[4][player->cpuDifficulty] + rand8() % params[5][player->cpuDifficulty];
                            break;
                    }
                }
                if (D_8010EE40_toadstool_titan[group] == 12) {
                    D_800CDA7C_main[player->pad] |= 0x8000;
                }
                D_8010EE4C_toadstool_titan[group] -= (D_8010EE4C_toadstool_titan[group] > 0) ? 1 : 0;
                break;
        }
        D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
        D_800D1382_main[player->pad] = D_800D20A1_main[player->pad] * 2;
    }
    if (D_8010F586_toadstool_titan == 3 && D_8010F60E_toadstool_titan == group) {
        D_800CDA7C_main[player->pad] = 0;
        D_800D5558_main[player->pad] = 0;
        D_800D1244_main[player->pad] = 0;
        D_800CBB6E_main[player->pad] = 0;
        D_800D20A1_main[player->pad] = 0;
        D_800D056A_main[player->pad] = 0;
        D_800D1382_main[player->pad] = 0;
    } else if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == group) {
        D_800CDA7C_main[player->pad] = 0;
        D_800D5558_main[player->pad] = 0;
        D_800D1244_main[player->pad] = 0;
    }
    if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == group) {
        D_800EB73C_minigame = 30.0f;
        D_800EB75C_minigame = 1.6666666f;
        speed = 18.0f;
        D_800EB760_minigame = speed * 2;
        D_800EB764_minigame = speed * 1.5f;
        halfSpeed = speed / 2;
        D_800EB768_minigame = speed;
        D_800EB76C_minigame = halfSpeed;
    }
    if (D_8010F586_toadstool_titan == 5 && D_8010F60E_toadstool_titan == group) {
        if (D_8010EE3C_toadstool_titan == 0 && data->unk40 > 9.0f) {
            D_8010EE3C_toadstool_titan = 1;
            if (D_800CBB6E_main[player->pad] * D_800CBB6E_main[player->pad] + D_800D20A1_main[player->pad] * D_800D20A1_main[player->pad] > 1600) {
                data->unk3C = (D_800CBB6E_main[player->pad] == 0) ? ((D_800D20A1_main[player->pad] >= 0) ? 180.0f : 0.0f)
                                                                  : atan2df(D_800CBB6E_main[player->pad], -D_800D20A1_main[player->pad]);
            }
            D_8010F520_toadstool_titan = data->unk3C;
        }
        if (D_8010EE3C_toadstool_titan != 0) {
            D_800CBB6E_main[player->pad] = sindf(D_8010F520_toadstool_titan) * 63.0f + D_800CBB6E_main[player->pad] / 6;
            D_800D20A1_main[player->pad] = cosdf(D_8010F520_toadstool_titan) * -63.0f + D_800D20A1_main[player->pad] / 6;
            D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
            D_800D1382_main[player->pad] = D_800D20A1_main[player->pad] * 2;
        }
    } else if (D_8010F586_toadstool_titan != 5) {
        D_8010EE3C_toadstool_titan = 0;
    }
    if ((D_8010F586_toadstool_titan == 3 || D_8010F586_toadstool_titan == 4 || D_8010F586_toadstool_titan == 6) && group != D_8010F60E_toadstool_titan) {
        work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
        work->unkBE = 1;
        work->unk50 |= 0x200;
    }
    if (D_8010F5FC_toadstool_titan >= 3 && data->unk53[0] == -1) {
        D_800CBB6E_main[player->pad] = rand8() % 40;
        D_800D20A1_main[player->pad] = rand8() % 40;
        D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
        D_800D1382_main[player->pad] = D_800D20A1_main[player->pad] * 2;
    }
    if (data->unk53[0] == 5 || data->unk53[0] == 6) {
        if (object->trans.z > 330.0f) {
            object->trans.z = 330.0f;
        }
    }
    if (object->trans.y >= 425.0f) {
        if (object->trans.z > 345.0f) {
            object->trans.z = 345.0f;
        }
    }
    if ((D_8010F5FC_toadstool_titan != 0 || D_8010F580_toadstool_titan < 46 || D_8010F580_toadstool_titan > 54) &&
        ((D_8010F586_toadstool_titan != 4 && D_8010F586_toadstool_titan != 6) || D_8010F60E_toadstool_titan != group) &&
        D_8010F616_toadstool_titan[group] == 0) {
        func_800DDD94_minigame(object);
        D_8010F634_toadstool_titan[group] = -1;
    } else if (D_8010F634_toadstool_titan[group] == -1 || D_8010F634_toadstool_titan[group] > Hu3DData[object->model[0]].motTime) {
        D_8010F634_toadstool_titan[group] = Hu3DData[object->model[0]].motTime;
    } else {
        Hu3DMotionTimeSet(object->model[0], D_8010F634_toadstool_titan[group]);
    }
    if (D_8010F5FC_toadstool_titan == 0 && (D_8010F580_toadstool_titan < 10 || group != 0)) {
        HuAudFXStop(data->unkC5);
    }
    if ((D_8010F586_toadstool_titan == 3 || D_8010F586_toadstool_titan == 4 || D_8010F586_toadstool_titan == 6) && group != D_8010F60E_toadstool_titan) {
        work = D_8010F640_toadstool_titan[D_8010F60E_toadstool_titan]->data;
        work->unkBE = 0;
        work->unk50 &= ~0x200;
    }
    if (D_8010F5FC_toadstool_titan == 0 && D_8010F580_toadstool_titan < 10) {
        data->unk38 = 0.0f;
    }
    if (D_8010F60E_toadstool_titan == group && D_8010F586_toadstool_titan == 5) {
        omSetSca(object, 2.0f, 2.0f, 2.0f);
        if (D_8010EE3C_toadstool_titan != 0) {
            if ((data->unk3C > -145.0f && data->unk3C < -35.0f && object->trans.x <= -400.0f) ||
                (data->unk3C > 35.0f && data->unk3C < 145.0f && object->trans.x >= 400.0f) ||
                ((data->unk3C > 125.0f || data->unk3C < -125.0f) && object->trans.z <= -350.0f) ||
                (data->unk3C > -55.0f && data->unk3C < 55.0f && object->trans.z >= 350.0f)) {
                object->trans.x = (object->trans.x <= -400.0f) ? -400.0f : ((object->trans.x >= 400.0f) ? 400.0f : object->trans.x);
                object->trans.z = (object->trans.z <= -350.0f) ? -350.0f : ((object->trans.z >= 350.0f) ? 350.0f : object->trans.z);
                data->unk40 = -D_800EB768_minigame;
                func_800E5690_minigame(object, 30);
                omVibrate(data->unk59, 20, 0, 20);
                for (i = 0; i < 4; i++) {
                    if (D_8010F616_toadstool_titan[i] == 0 && D_8010F568_toadstool_titan[i]->playerNo != data->unk59) {
                        omVibrate(D_8010F568_toadstool_titan[i]->playerNo, 10, 0, 10);
                    }
                }
                D_8010EE3C_toadstool_titan = 0;
                D_8010F5F4_toadstool_titan = 13;
                D_8010F670_toadstool_titan = data->unk3C;
                HuAudFXPlay(0x3AA);
            }
        }
    }
    D_800EB73C_minigame = 15.0f;
    D_800EB75C_minigame = 3.3333333f;
    D_800EB760_minigame = 18.0f;
    D_800EB764_minigame = 13.5f;
    D_800EB768_minigame = 9.0f;
    D_800EB76C_minigame = 4.5f;
    D_800CDA7C_main[player->pad] = savedBtn;
    D_800D5558_main[player->pad] = savedBtn2;
    D_800D1244_main[player->pad] = savedBtn3;
    D_800CBB6E_main[player->pad] = savedStickX;
    D_800D20A1_main[player->pad] = savedStickY;
    D_800D056A_main[player->pad] = savedStick2;
    D_800D1382_main[player->pad] = savedStick3;
    if (D_8010F616_toadstool_titan[group] >= 60) {
        func_8001C258_main(object->model[0], 4, 4);
    }
    if (D_8010F616_toadstool_titan[group] != 0) {
        func_8001C258_main(object->model[1], 4, 4);
    } else {
        Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    }
}
#else
// Initializer of the CPU params table copied onto the stack in func_8010BD2C_toadstool_titan.
const s16 D_8010F278_toadstool_titan[22][4] = {
    { 0, 0, 0, 0 },
    { 300, 300, 200, 150 },
    { 11, 9, 6, 3 },
    { 6, 6, 6, 6 },
    { 11, 9, 5, 2 },
    { 4, 4, 3, 1 },
    { -30, -40, -40, -200 },
    { 15, 20, 20, 100 },
    { 45, 35, 25, 25 },
    { 1, 1, 1, 15 },
    { 36, 46, 56, 66 },
    { 1, 1, 1, 1 },
    { 20, 20, 15, 15 },
    { 35, 25, 12, 8 },
    { 0, 0, 6, 6 },
    { 1, 8, 4, 5 },
    { 0, 24, 16, 32 },
    { 1, 8, 24, 1 },
    { 14, 9, 6, 0 },
    { 6, 8, 5, 7 },
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 }
};

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BD2C_toadstool_titan);
#endif
