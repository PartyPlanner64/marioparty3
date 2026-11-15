#include "common.h"
#include "macros.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/effect.h"
#include "game/esprite.h"
#include "game/hmfanim.h"
#include "game/hmfspr.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

// Per-player info, indexed by group through D_8010D308_awful_tower
typedef struct {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk05[3];
    /* 0x08 */ s32 unk08;
} AwfulTowerPlayer; // Size 0xC

extern s32 D_800A178C_main[][6];
extern EffectGroup *D_800D6A00_main[];
extern f32 D_800EB760_minigame;
extern Gfx *gMainGfxPos;
extern omObjData *D_800EBE70_minigame[];

s32 D_8010CB60_awful_tower[] = { 1, 2, 4, 8 };
MinigameFlow D_8010CB70_awful_tower = { 0 };
s32 D_8010CB98_awful_tower[] = { -1, -1 };

Gfx D_8010CBA0_awful_tower[] = {
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

u32 D_8010CBE8_awful_tower = 40;
f32 D_8010CBEC_awful_tower[4] = { 32000.0f, 32000.0f, 32000.0f, 32000.0f };
s8 D_8010CBFC_awful_tower[4] = { -1, -1, -1, -1 };
s8 D_8010CC00_awful_tower[4] = { -1, -1, -1, -1 };
s8 D_8010CC04_awful_tower[4] = { 0 };
s8 D_8010CC08_awful_tower[4] = { 0 };
u8 D_8010CC0C_awful_tower[4] = { 0 };
u8 D_8010CC10_awful_tower[4] = { 0 };
u8 D_8010CC14_awful_tower[4] = { 0 };
f32 D_8010CC18_awful_tower[4] = { -1000.0f, -1000.0f, -1000.0f, -1000.0f };
u8 D_8010CC28_awful_tower[4] = { 1, 1, 1, 1 };
f32 D_8010CC2C_awful_tower[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
s8 D_8010CC3C_awful_tower[4] = { -1, -1, -1, -1 };
u8 D_8010CC40_awful_tower[4] = { 0 };
u8 D_8010CC44_awful_tower = 0;
f32 D_8010CC48_awful_tower = 1000.0f;
u8 D_8010CC4C_awful_tower[4] = { 0 };
f32 D_8010CC50_awful_tower[4] = { 0 };
f32 D_8010CC60_awful_tower[4] = { 0 };
u8 D_8010CC70_awful_tower[4] = { 0 };
s8 D_8010CC74_awful_tower[4] = { 0 };
s8 D_8010CC78_awful_tower[4] = { 0 };
s8 D_8010CC7C_awful_tower[20] = { 0, 0, 0, 0, 3, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2, 6, 60, 0, 0, 0 };
s8 D_8010CC90_awful_tower[20] = { 0, 0, 0, 0, 3, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 };
u8 D_8010CCA4_awful_tower[4] = { 0 };
f32 D_8010CCA8_awful_tower[] = { -10.0f, -16.0f, -18.0f };
f32 D_8010CCB4_awful_tower[] = { 22.0f, 24.0f, 60.0f };

f32 D_8010D0D0_awful_tower[16] BSS;
f32 D_8010D110_awful_tower[16] BSS;
f32 D_8010D150_awful_tower[4] BSS;
f32 D_8010D160_awful_tower[4] BSS;
f32 D_8010D170_awful_tower[4] BSS;
f32 D_8010D180_awful_tower[4] BSS;
f32 D_8010D190_awful_tower[4] BSS;
f32 D_8010D1A0_awful_tower[4] BSS;
f32 D_8010D1B0_awful_tower[4] BSS;
f32 D_8010D1C0_awful_tower[4] BSS;
f32 D_8010D1D0_awful_tower[4] BSS;
f32 D_8010D1E0_awful_tower[4] BSS;
f32 D_8010D1F0_awful_tower[55] BSS;
s16 D_8010D2CC_awful_tower[4] BSS;
u8 D_8010D2D4_awful_tower[4] BSS; /* Unreferenced. */
AwfulTowerPlayer D_8010D2D8_awful_tower[4] BSS;
AwfulTowerPlayer *D_8010D308_awful_tower[4] BSS;
u8 D_8010D318_awful_tower[8] BSS; /* Unreferenced. */
f32 D_8010D320_awful_tower[4] BSS;
u8 D_8010D330_awful_tower[4][5] BSS;
omObjData *D_8010D344_awful_tower BSS;
u16 D_8010D348_awful_tower[4][3] BSS;
omObjData *D_8010D360_awful_tower[4][3] BSS;
omObjData *D_8010D390_awful_tower[5] BSS;
u8 D_8010D3A4_awful_tower[4] BSS; /* Unreferenced. */
omObjData *D_8010D3A8_awful_tower[4] BSS;
s16 D_8010D3B8_awful_tower[4] BSS;
u8 D_8010D3C0_awful_tower[0xC] BSS; /* Unreferenced. */
u8 D_8010D3CC_awful_tower[4] BSS;
s16 D_8010D3D0_awful_tower[4] BSS;
u16 D_8010D3D8_awful_tower BSS;
u32 D_8010D3DC_awful_tower BSS;
u8 D_8010D3E0_awful_tower[4] BSS; /* Unreferenced. */
s16 D_8010D3E4_awful_tower BSS;
omObjData *D_8010D3E8_awful_tower BSS;
s16 D_8010D3EC_awful_tower[2] BSS;
u8 D_8010D3F0_awful_tower[0xC] BSS; /* Unreferenced. */
s8 D_8010D3FC_awful_tower BSS;
u8 D_8010D3FD_awful_tower BSS;
u8 D_8010D3FE_awful_tower BSS;

extern const s16 D_8010CCE0_awful_tower[];

void func_80106028_awful_tower(omObjData *object);
void func_801061FC_awful_tower(omObjData *object);
void func_80106A9C_awful_tower(omObjData *object);
void func_80106CDC_awful_tower(omObjData *object);
void func_80106E84_awful_tower(omObjData *object);
void func_80106FDC_awful_tower(omObjData *object);
void func_80107734_awful_tower(omObjData *object);
void func_80107858_awful_tower(void);
void func_80108880_awful_tower(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void func_80108CCC_awful_tower(omObjData *object);
void func_80108D3C_awful_tower(omObjData *object);
void func_80108DAC_awful_tower(omObjData *object);
void func_80108E1C_awful_tower(omObjData *object);
void func_80108E8C_awful_tower(omObjData *object);

void func_801059A0_awful_tower(void) {
    omObjData *object;
    s32 i;
    s32 j;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        s32 lefts[4] = { 0, 93, 161, 229 };
        s32 rights[4] = { 92, 160, 228, 320 };

        ScissorSet(i, lefts[i], 0.0f, rights[i], 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, i * 272 + 236, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 7.152669f, 8000.0f, 16000.0f);
        CenterM[i].x = 0.0f;
        CenterM[i].y = 650.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CZoomM[i] = 12000.0f;
    }
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 80.0f, 130.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x90);
    Hu3DGLightDirSet(1, 20.0f, 80.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xF0);
    omAddObj(0, 0, 0, -1, func_80106028_awful_tower);
    D_8010D3E8_awful_tower = omAddObj(4, 21, 21, -1, func_80106FDC_awful_tower);
    omSetStatBit(D_8010D3E8_awful_tower, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010D344_awful_tower = omAddObj(2, 21, 21, -1, func_80106A9C_awful_tower);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010D360_awful_tower[i][j] = omAddObj(2, 4, 4, -1, func_80106E84_awful_tower);
        }
    }
    for (i = 0; i < 5; i++) {
        D_800EBE70_minigame[D_800EC1B8_minigame++] = D_8010D390_awful_tower[i] = omAddObj(2, 4, 2, -1, func_80106CDC_awful_tower);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[0] = omAddObj(3, 12, 60, -1, func_80108CCC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[1] = omAddObj(3, 12, 60, -1, func_80108D3C_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[2] = omAddObj(3, 12, 60, -1, func_80108DAC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[3] = omAddObj(3, 12, 60, -1, func_80108E1C_awful_tower);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 4;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(0xFF, 30);
    func_80045010_main(D_8010CCE0_awful_tower, 1);
    D_8010CB70_awful_tower.type = MINIGAME_4P;
    D_8010CB70_awful_tower.startDelay = 60;
    D_8010CB70_awful_tower.timer = 1800;
    D_8010CB70_awful_tower.timeDisp = MG_TIME_DISP_COUNTDOWN;
    D_8010CB70_awful_tower.timerMode = MG_TIMER_COUNT_DOWN;
    D_8010CB70_awful_tower.finishDelay = 75;
    D_8010CB70_awful_tower.resultDelay = 165;
    D_8010CB70_awful_tower.newRecord = FALSE;
    D_8010CB70_awful_tower.gauge = MG_GAUGE_NONE;
    D_8010CB70_awful_tower.timeLimit = -1;
    func_800E5EA0_minigame(&D_8010CB70_awful_tower);
    for (i = 0; i < 4; i++) {
        D_8010D2CC_awful_tower[i] = func_8000D658_main(0x6A9, 4);
    }
}

void func_8010600C_awful_tower(void) {
    func_80107858_awful_tower();
}

void func_80106028_awful_tower(omObjData *object) {
    s32 i;
    s32 group;

    D_8010D3D8_awful_tower = 0;
    D_8010D3E4_awful_tower = 0;
    D_8010D3DC_awful_tower = 0;
    D_8010D3FC_awful_tower = 5;
    D_8010D3FD_awful_tower = 0;
    D_8010D3FE_awful_tower = 0;
    D_8010D320_awful_tower[0] = 650.0f;
    D_8010D320_awful_tower[1] = 650.0f;
    D_8010D320_awful_tower[2] = 650.0f;
    D_8010D320_awful_tower[3] = 650.0f;
    for (i = 0; i < 4; i++) {
        D_8010D330_awful_tower[i][0] = D_8010D330_awful_tower[i][1] = D_8010D330_awful_tower[i][2] =
            D_8010D330_awful_tower[i][3] = D_8010D330_awful_tower[i][4] = 1;
        D_8010D308_awful_tower[i] = &D_8010D2D8_awful_tower[i];
        bzero(&D_8010D2D8_awful_tower[i], sizeof(AwfulTowerPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = D_8010D3CC_awful_tower[i] = GwPlayer[i].group;
        D_8010D308_awful_tower[group]->player = i;
        D_8010D308_awful_tower[group]->pad = GwPlayer[i].pad;
        D_8010D308_awful_tower[group]->chr = GwPlayer[i].chr;
        D_8010D308_awful_tower[group]->group = group;
        D_8010D308_awful_tower[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    object->func = func_801061FC_awful_tower;
}

const s16 D_8010CCE0_awful_tower[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C,
    0x826D, 0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279,
    0x824F, 0x8250, 0x8251, 0x8252, 0x8253, 0x8254, 0x8255, 0x8256, 0x8257, 0x8258, 0x0000
};

void func_801061FC_awful_tower(omObjData *object) {
    u8 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 winFiles[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    s8 chr;
    s16 i;

    D_8010D3DC_awful_tower++;
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (D_8010D3DC_awful_tower == 51 && D_8010D3D8_awful_tower == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x33);
            }
            break;
        case 3:
            if (D_8010D3FE_awful_tower >= 20) {
                MgFlowStatNext();
            }
            break;
    }
    MgFlowMain();
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (MgFlowStatGet() == MG_STATE_START) {
                D_8010D3E4_awful_tower = 1;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 1:
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                D_8010D3E4_awful_tower = 2;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 2:
            if (D_8010D3FC_awful_tower != 5 || MgFlowStatGet() == MG_STATE_FINISH) {
                if (D_8010D3FC_awful_tower == 5) {
                    D_8010D3E4_awful_tower = 6;
                    D_8010D3FC_awful_tower = 4;
                } else {
                    D_8010D3E4_awful_tower = 3;
                }
                D_8010D3DC_awful_tower = 0;
            }
            if (D_8010D3E4_awful_tower != 3) {
                break;
            }
        case 3:
            if (D_8010D3DC_awful_tower == 0) {
                D_8010CB70_awful_tower.finishDelay = 210;
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                D_8010CB70_awful_tower.resultType = MG_RESULT_WIN_1;
                D_8010CB70_awful_tower.winners[0] = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->player;
                GwPlayer[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->player].bonusCoin = 10;
            }
            if (D_8010D3DC_awful_tower == 2) {
                func_800E6F34_minigame(30);
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                D_8010D3E4_awful_tower = 4;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 6:
            if (D_8010D3DC_awful_tower == 1) {
                D_8010CB70_awful_tower.resultType = MG_RESULT_DRAW;
                D_8010CB70_awful_tower.resultDelay = 0x90;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                D_8010D3E4_awful_tower = 5;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 4:
            if (D_8010D3DC_awful_tower == 1) {
                chr = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->chr;
                D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9] =
                    func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x4AD);
                D_8010D3EC_awful_tower[0] =
                    func_80017790_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1, motions[chr],
                                       (chrDirs[chr] << 16) | winFiles[0][chr]);
                D_8010D3EC_awful_tower[1] = func_80017AD8_main((chrDirs[chr] << 16) | winFiles[1][chr]);
                func_8001C514_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]);
                Hu3DModelCameraSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0], 4, 4);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 4, 0);
                Hu3DMotionTimeSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                  Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0]].motTime);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 2);
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.x =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x;
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.y =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.y;
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.z =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.z;
            }
            if (D_8010D3DC_awful_tower < 16) {
                Hu3DModelRotSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 0.0f,
                                D_8010D3DC_awful_tower / 15.0f * 90.0f + -90.0f, 0.0f);
            }
            if (D_8010D3DC_awful_tower == 30) {
                func_8001C5B4_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[10]);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 0);
                func_80017954_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1,
                                   motions[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->chr],
                                   D_8010D3EC_awful_tower[1]);
                func_80045ED0_main(D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk08);
            }
        case 5:
            if (D_8010D3E4_awful_tower == 5 && D_8010D3DC_awful_tower == 1) {
                for (i = 0; i < 4; i++) {
                    func_800E5690_minigame(D_8010D3A8_awful_tower[i], 14);
                }
            }
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                D_8010D3E4_awful_tower = 7;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 7:
            if (D_8010D3DC_awful_tower == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010D3DC_awful_tower >= 32) {
                D_8010D3D8_awful_tower = 1;
            }
            break;
    }
    if (D_8010D3D8_awful_tower != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010D3FD_awful_tower == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_8010D3FD_awful_tower++;
            if (D_8010D3FD_awful_tower < 25) {
                return;
            }
        } else {
            HuAudSeqFadeOut(30);
        }
        omOvlReturnEx(1);
    }
}

void func_80106A9C_awful_tower(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->model[0] = func_8000B0A0_main(0x460006, 0x499);
    func_8001C2FC_main(object->model[0], 0x600, 0);
    Hu3DLLightCreate(object->model[0], 1);
    Hu3DLLightColorSet(object->model[0], 0xFF, 0xFF, 0xFF);
    Hu3DLLightDirSet(object->model[0], 0.0f, 0.0f, 127.0f);
    object->trans.y = object->trans.z = 0.0f;
    object->trans.x = 1500.0f;
    object->trans.y = -60.0f;
    object->trans.z = 300.0f;
    omSetRot(object, 90.0f, 0.0f, 0.0f);
    omSetSca(object, 1000.0f, 1.0f, 1.0f);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E139C_minigame(object, 0.0f, -670.0f, -380.0f, 670.0f, 250.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    func_800E1468_minigame(object);
    work->unk04 = 0;
    object->func = NULL;
}

s32 func_80106C44_awful_tower(omObjData *player, omObjData *object) {
    A96F0_ObjData *data = object->data;

    GwPlayer[((func_800E1BA8_minigame_ObjData *)player->data)->unk59].gameCoin++;
    HuAudFXPlay(9);
    data->unk54 = 0;
    data->unk78 = 0;
    func_8001C258_main(object->model[0], 4, 4);
    func_8001C258_main(object->model[1], 4, 4);
    return 1;
}

void func_80106CDC_awful_tower(omObjData *object) {
    A96F0_ObjData *data;
    s16 i;
    s32 unused[2]; // Retain the original stack frame.

    object->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(A96F0_ObjData));
    data = object->data;
    if (D_8010CB98_awful_tower[0] == -1) {
        func_800E1594_minigame(object, 0x210026, 0x41D, 8);
        D_8010CB98_awful_tower[0] = data->unk55;
    } else {
        data->unk55 = func_80014618_main(D_8010CB98_awful_tower[0], 8);
        object->model[0] = D_800CBB60_main[data->unk55].modelId;
        func_8001C2FC_main(object->model[0], 0x70000000, 0x70000000);
    }
    data->unk44 = 0.0f;
    data->unk48 = 40.0f;
    data->unk34 = 50.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 2000;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    data->unk58 = 1.2f;
    data->unk56 = 0;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk84[8] = (void *)func_80106C44_awful_tower;
    func_800E17F4_minigame(object, 3.0f, 3.0f, 3.0f);
    func_8001C258_main(object->model[0], 4, 4);
    object->func = NULL;
}

void func_80106E84_awful_tower(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 250.0f;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E13CC_minigame(object, 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    work->unk04 = 0;
    object->func = NULL;
}

s16 func_80106F58_awful_tower(s32 file, u16 *sprite) {
    void *data = DataRead(file);
    s16 anim = func_800329B4_main(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, 0x6B9, 0);
    D_800CBB60_main[idx].unk_02 = anim;
    return D_800CBB60_main[idx].modelId;
}

void func_80106FDC_awful_tower(omObjData *object) {
    s32 sprFiles[4] = { 0x46000A, 0x46000B, 0x46000C, 0x46000D };
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        D_8010D3B8_awful_tower[i] = HuSprAnimDataRead(sprFiles[i]);
        D_8010D3B8_awful_tower[i] = HuSprAnimDataRead(sprFiles[i]);
        D_8010D3D0_awful_tower[i] = espEntry(D_8010D3B8_awful_tower[i], 0, 0);
        espDispOff(D_8010D3D0_awful_tower[i]);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            s32 modelIdx[3] = { 8, 12, 16 };
            s32 animFiles[3] = { 7, 8, 9 };

            object->model[modelIdx[j] + i] =
                func_80106F58_awful_tower(animFiles[j] | 0x460000, &D_8010D348_awful_tower[i][j]);
            func_8001C258_main(object->model[modelIdx[j] + i], 4, 4);
            Hu3DModelCameraSet(object->model[modelIdx[j] + i], D_8010CB60_awful_tower[i]);
            if (j < 2) {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 6.0525f, 6.0525f, 6.0525f);
            } else {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 3.02625f, 3.02625f, 3.02625f);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        f32 posX[5] = { 1.0f, -1.0f, 1.0f, -1.0f, 0.25f };
        f32 posY[5] = { 13.5f, 8.5f, 24.0f, 34.0f, 40.5f };
        A96F0_ObjData *data = D_8010D390_awful_tower[i]->data;

        D_8010D390_awful_tower[i]->trans.x = posX[i] * 150.0f;
        D_8010D390_awful_tower[i]->trans.y = posY[i] * 100.0f + 50.0f;
        D_8010D390_awful_tower[i]->trans.z = 0.0f;
        data->unk56 = i;
        func_8001C258_main(D_8010D390_awful_tower[i]->model[0], 4, 0);
    }
    for (i = 0; i < 3; i++) {
        s32 files[3] = { 2, 3, 4 };

        object->model[i] = func_8000B108_main(files[i] | 0x460000, 0x4BD);
    }
    object->model[20] = func_8000B108_main(0x460005, 0x4BD);
    Hu3DModelCameraSet(object->model[20], 0);
    Hu3DModelScaleSet(object->model[20], 0.666666f, 0.666666f, 0.666666f);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            ((D_800EC1C0_minigame_ObjData *)D_8010D360_awful_tower[i][j]->data)->unk04 = i * 3 + j + 1;
            for (k = 0; k < 3; k++) {
                D_8010D360_awful_tower[i][j]->model[k + 1] = Hu3DModelLink(D_8010D3E8_awful_tower->model[j]);
                func_8001C258_main(D_8010D360_awful_tower[i][j]->model[k + 1], 4, 4);
                Hu3DModelScaleSet(D_8010D360_awful_tower[i][j]->model[k + 1], 0.666666f, 0.666666f, 0.666666f);
                Hu3DModelCameraSet(D_8010D360_awful_tower[i][j]->model[k + 1], D_8010CB60_awful_tower[i]);
            }
        }
    }
    object->model[3] = func_8000B108_main(0xA011A, 0x4BD);
    func_8001C814_main(object->model[3], 2, 2);
    Hu3DModelPosSet(object->model[3], 0.0f, 4500.0f, 300.0f);
    Hu3DModelScaleSet(object->model[3], 0.5f, 0.5f, 0.5f);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 3) {
            object->model[i + 4] = func_8000B108_main(i == 3 ? 0x460001 : 0x460000, 0x4B9);
        } else {
            object->model[i + 4] = Hu3DModelLink(object->model[4]);
        }
        Hu3DModelCameraSet(object->model[i + 4], 15);
        func_8001C814_main(object->model[i + 4], 1, 1);
        Hu3DModelPosSet(object->model[i + 4], 0.0f, i * 1120.0 - 9.0, -300.0f);
        Hu3DModelScaleSet(object->model[i + 4], 0.75f, 0.75f, 0.75f);
    }
    object->func = func_80107734_awful_tower;
}

void func_80107734_awful_tower(omObjData *object) {
    func_80107858_awful_tower();
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010D3DC_awful_tower == 1) {
            func_8001C258_main(object->model[3], 4, 0);
            Hu3DModelCameraSet(object->model[3], D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
        }
        if (D_8010D3DC_awful_tower != 0 && D_8010D3DC_awful_tower < 46) {
            f32 t = D_8010D3DC_awful_tower / 45.0f;

            t = (1.0f - t) * (1.0f - t);
            Hu3DModelPosSet(object->model[3], 0.0f, t * 700.0f + 4430.0, 300.0f);
        }
    }
    omPauseChk();
}

void func_80107858_awful_tower(void) {
    s32 groups[4] = { 3, 2, 1, 0 };
    s32 lefts[4] = { 0, 93, 161, 229 };
    s32 rights[4] = { 92, 160, 228, 320 };
    s32 texLefts[4] = { 0, 25, 25, 25 };
    s32 zoomLefts[4] = { 0, 0, 0, 0 };
    s32 zoomRights[4] = { 320, 320, 320, 320 };
    s32 zoomTexLefts[4] = { 0, 0, 0, 0 };
    u8 order[4] = { 0, 1, 2, 3 };
    s32 curLefts[4] = { 0, 93, 161, 229 };
    s32 curRights[4] = { 92, 160, 228, 320 };
    HuSprite *sprite;
    HuSprAnimPat *frame;
    f32 t = 0.0f;
    f32 a;
    f32 b;
    f32 scale;
    s32 left;
    s32 right;
    s32 y;
    s32 yEnd;
    s32 offset;
    s32 xl;
    s32 xh;
    s32 yl;
    s32 yh;
    s32 s;
    s32 dsdx;
    s16 player;
    s16 i;
    s16 j;
    s16 k;

    if (D_8010D3FC_awful_tower < 4) {
        for (i = 0, k = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower == i) {
                if (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower < 30) {
                    t = 1.0f - D_8010D3DC_awful_tower / 29.0f;
                    t = ((1.0f - t) + 1.0f - t * t * t) * 0.5;
                } else if (D_8010D3E4_awful_tower == 7 ||
                           (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower >= 30)) {
                    t = 1.0f;
                }
            } else {
                order[k++] = i;
            }
        }
        order[k] = D_8010D3FC_awful_tower;
    }
    if (t > 0.0f) {
        a = 1.0f - t;
        b = 1.0f - a;
        scale = ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) / (a * 67.0f + b * 113.0f);
        left = curLefts[D_8010D3FC_awful_tower] =
            lefts[D_8010D3FC_awful_tower] * a + zoomLefts[D_8010D3FC_awful_tower] * b;
        right = curRights[D_8010D3FC_awful_tower] =
            rights[D_8010D3FC_awful_tower] * a + zoomRights[D_8010D3FC_awful_tower] * b;
        ScissorSet(D_8010D3FC_awful_tower, left, 0.0f, right, 240.0f);
        ViewportSet(D_8010D3FC_awful_tower, scale * 320.0f * 2.0f, scale * 240.0f * 2.0f, 511.0f,
                    ((D_8010D3FC_awful_tower * 68 + 59) * a + b * 160.0f) * 4.0f, 480.0f, 511.0f);
        CenterM[D_8010D3FC_awful_tower].y = a * D_8010D320_awful_tower[D_8010D3FC_awful_tower] + b * 4605.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower != i) {
                if (i < D_8010D3FC_awful_tower) {
                    curLefts[i] = MIN(left, curLefts[i]);
                    curRights[i] = MIN(left, curRights[i]);
                } else {
                    curLefts[i] = MAX(right, curLefts[i]);
                    curRights[i] = MAX(right, curRights[i]);
                }
            }
        }
    }
    gSPDisplayList(gMainGfxPos++, D_8010CBA0_awful_tower);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 3; i >= 0; i--) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010D3D0_awful_tower[groups[i]]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        for (j = 0; j < 9; j++) {
            y = j * 16;
            yEnd = (y + 17 > 130) ? 130 : y + 17;
            if (i != 0) {
                gDPLoadTextureTile(gMainGfxPos++, (u8 *)frame->data + y * 114, G_IM_FMT_CI, G_IM_SIZ_8b, 114, 0, 0, 0,
                                   114, yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
            } else {
                gDPLoadTextureTile_4b(gMainGfxPos++, (u8 *)frame->data + y * 57, G_IM_FMT_CI, 114, 0, 0, 0, 114,
                                      yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
            }
            for (k = 0; k < 4; k++) {
                player = order[k];
                if (t > 0.0f) {
                    if (curLefts[player] == curRights[player]) {
                        continue;
                    }
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, curLefts[player], 0,
                                  curRights[player] - ((player == D_8010D3FC_awful_tower) ? 1 : 0), 240);
                }
                if (player == D_8010D3FC_awful_tower) {
                    a = 1.0f - t;
                    b = 1.0f - a;
                } else {
                    a = 1.0f;
                    b = 0.0f;
                }
                offset = (D_8010D320_awful_tower[player] - 650.0f) / 3850.0 * -284.0 + 284.0;
                xl = (lefts[player] * a + zoomLefts[player] * b) * 4.0f;
                xh = (rights[player] * a + zoomRights[player] * b) * 4.0f;
                yl = ((y + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0;
                yh = ((yEnd + 2 + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0 - 1.0;
                if ((xl > 1280) | (xh < 0)) {
                    continue;
                }
                if ((yl > 960) | (yh < 0)) {
                    continue;
                }
                s = (texLefts[player] * a + zoomTexLefts[player] * b) * 32.0;
                dsdx = (a * 67.0f + b * 113.0f) / ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) * 1024.0;
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s, 0, dsdx, dsdx);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ScissorSet(i, curLefts[i], 0.0f, curRights[i], 240.0f);
    }
}

void func_80108880_awful_tower(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 attr1 = 0x4B9;
    s32 attr2 = 0x49D;
    u16 chr = D_8010D308_awful_tower[group]->chr;
    func_800E1BA8_minigame_ObjData *data;
    s32 i;

    func_800E18D8_minigame();
    func_800E1BA8_minigame(object, model, motion, D_8010D308_awful_tower[group]->player, attr1, attr2);
    Hu3DModelCameraSet(object->model[0], D_8010CB60_awful_tower[group]);
    data = object->data;
    data->unk59 = D_8010D308_awful_tower[group]->player;
    data->unk50 |= 0x400;
    data->unk4C = 1.0f;
    data->unkB4 = 1.0f;
    object->model[6] = func_8000B108_main(5, 0x80D);
    Hu3DModelCameraSet(object->model[6], D_8010CB60_awful_tower[group]);
    Hu3DModelCameraSet(object->model[9], D_8010CB60_awful_tower[group]);
    D_8010D308_awful_tower[group]->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    object->model[10] = func_8000B108_main(func_80017BB8_main(chr, D_8010D308_awful_tower[group]->unk08), attr1 | 4);
    D_8010D308_awful_tower[group]->unk08 |= chrDirs[chr] << 16;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 17, func_80017BB8_main(chr, 14), 1, 15);
    func_800E5978_minigame(object, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E5978_minigame(object, 30, func_80017BB8_main(chr, 32), 2, 0);
    func_800E5978_minigame(object, 31, func_80017BB8_main(chr, 33), 2, 0);
    func_800E5978_minigame(object, 32, func_80017BB8_main(chr, 34), 0, 0);
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, 58), 1, 120);
    object->trans.x = x;
    object->trans.y = y;
    object->trans.z = z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    for (i = 0; i < 12; i++) {
        func_800E149C_minigame(object, i + 1, 1);
    }
    func_800E149C_minigame(object, 0, 2);
    func_800E149C_minigame(object, group * 3 + 1, 2);
    func_800E149C_minigame(object, group * 3 + 2, 2);
    func_800E149C_minigame(object, group * 3 + 3, 2);
}

void func_80108CCC_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[0]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 0, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108D3C_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[1]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 1, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108DAC_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[2]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 2, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108E1C_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[3]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 3, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108E8C_awful_tower(omObjData *object) {
    AwfulTowerPlayer *player;
    s16 savedBtn;
    u16 savedBtn2;
    u16 savedBtn3;
    s8 savedStickX;
    s8 savedStickY;
    s16 savedStick2;
    s16 savedStick3;
    func_800E1BA8_minigame_ObjData *data = object->data;
    s16 group = D_8010D3CC_awful_tower[data->unk59];
    u8 savedCB70 = 0xFF;
    u8 platTypes[16] = { 0, 2, 1, 1, 0, 0, 2, 1, 2, 2, 1, 0, 1, 2, 2, 0 };
    f32 platBaseY[16] = { 45.0f, 250.0f, 615.0f, 950.0f, 1100.0f, 1350.0f, 1600.0f, 1800.0f,
                          2150.0f, 2450.0f, 2850.0f, 3150.0f, 3400.0f, 3700.0f, 3950.0f, 4500.0f };
    u8 platCols[16] = { 0, 1, 2, 1, 0, 1, 2, 0, 1, 0, 1, 2, 1, 0, 2, 1 };
    u8 nearPlats[7] = { -1, -1, -1, -1, -1, -1, -1 };
    f32 nearDists[7] = { 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f, 32000.0f };
    u8 closePlats[3] = { -1, -1, -1 };
    f32 closeDists[3] = { 32000.0f, 32000.0f, 32000.0f };
    u8 coinNear[5];
    func_800E1BA8_minigame_ObjData *work;
    f32 dist;
    f32 vx;
    f32 vy;
    f32 wave;
    s32 i;
    s32 j;
    s32 k;

    player = D_8010D308_awful_tower[group];
    if (D_8010D3E4_awful_tower == 5 && D_8010D3DC_awful_tower == 1) {
        D_8010CC00_awful_tower[group] = D_8010CBFC_awful_tower[group];
        data->unk3C = 0.0f;
    }
    if (group == 0) {
        s16 periods[3] = { 60, 60, 60 };
        f32 offsets[3];
        f32 amplitudes[3] = { 150.0f, 200.0f, 300.0f };

        if (D_8010CBE8_awful_tower == 40) {
            for (i = 0; i < 15; i++) {
                D_8010D110_awful_tower[i] = 0.0f;
            }
            for (i = 0; i < 55; i++) {
                D_8010D1F0_awful_tower[i] = -1.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            offsets[i] = ((D_8010CBE8_awful_tower % periods[i] < periods[i] / 2)
                              ? (D_8010CBE8_awful_tower % periods[i]) * 2.0
                              : (periods[i] - D_8010CBE8_awful_tower % periods[i]) * 2.0) /
                         periods[i] * amplitudes[i];
        }
        for (i = 0; i < 15; i++) {
            D_8010D0D0_awful_tower[i] =
                platBaseY[i] + (((i & 1) == 0) ? offsets[platTypes[i]]
                                               : amplitudes[platTypes[i]] - offsets[platTypes[i]]);
            D_8010D110_awful_tower[i] += D_8010D0D0_awful_tower[i];
        }
    }
    savedBtn = D_800CDA7C_main[player->pad];
    savedBtn2 = D_800D5558_main[player->pad];
    savedBtn3 = D_800D1244_main[player->pad];
    savedStickX = D_800CBB6E_main[player->pad];
    savedStickY = D_800D20A1_main[player->pad];
    savedStick2 = D_800D056A_main[player->pad];
    savedStick3 = D_800D1382_main[player->pad];
    D_800D20A1_main[player->pad] = D_800D1382_main[player->pad] = 0;
    if (D_8010CC04_awful_tower[group] != 0 && D_8010D110_awful_tower[D_8010CC04_awful_tower[group]] < 0.0f) {
        object->trans.y += D_8010D110_awful_tower[D_8010CC04_awful_tower[group]];
        D_8010CC28_awful_tower[group] = D_8010CC04_awful_tower[group];
        if (data->unk38 < 0.0) {
            data->unk38 = 0.25f;
        }
    }
    if (D_8010CC28_awful_tower[group] != 0 && D_8010CC70_awful_tower[group] == 0) {
        if (object->trans.y + 155.0f >= D_8010D0D0_awful_tower[D_8010CC28_awful_tower[group]] - 50.0f) {
            object->trans.y = -155.0f + D_8010D0D0_awful_tower[D_8010CC28_awful_tower[group]] - 50.0f;
        }
    }
    for (i = 0; i < 15; i++) {
        dist = ABS(D_8010D0D0_awful_tower[i] - D_8010D320_awful_tower[group]);
        for (j = 0; j < 7; j++) {
            if (dist < nearDists[j]) {
                for (k = 5; k >= j; k--) {
                    nearPlats[k + 1] = nearPlats[k];
                    nearDists[k + 1] = nearDists[k];
                }
                nearPlats[j] = i;
                nearDists[j] = dist;
                break;
            }
        }
    }
    for (i = 0; i < 7; i++) {
        dist = ABS(D_8010D0D0_awful_tower[nearPlats[i]] - (object->trans.y + 75.0));
        for (j = 0; j < 3; j++) {
            if (dist < closeDists[j]) {
                for (k = 2; k >= j; k--) {
                    closePlats[k + 1] = closePlats[k];
                    closeDists[k + 1] = closeDists[k];
                }
                closePlats[j] = nearPlats[i];
                closeDists[j] = dist;
                break;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        omSetTra(D_8010D360_awful_tower[group][i], platCols[closePlats[i]] * 150 - 150,
                 D_8010D0D0_awful_tower[closePlats[i]], 0.0f);
        if (closePlats[i] == 0) {
            func_800E13CC_minigame(D_8010D360_awful_tower[group][i], 50.0f, 300.0f, -150.0f, -50.0f, 50.0f, 50.0f);
        } else {
            func_800E13CC_minigame(D_8010D360_awful_tower[group][i], 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
        }
        for (j = 0; j < 3; j++) {
            func_8001C258_main(D_8010D360_awful_tower[group][i]->model[j + 1], 4, 4);
        }
        if (group == 0) {
            func_8001C258_main(D_8010D3E8_awful_tower->model[20], 4, 4);
            Hu3DModelCameraSet(D_8010D3E8_awful_tower->model[20], 0);
        }
    }
    {
        u8 counts[3] = { 0, 0, 0 };

        for (i = 0; i < 7; i++) {
            j = nearPlats[i];
            k = platTypes[j];
            if (counts[k] < 3) {
                if (j == 14) {
                    Hu3DModelPosSet(D_8010D3E8_awful_tower->model[20], platCols[j] * 150 - 150,
                                    D_8010D0D0_awful_tower[j], 0.0f);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[20], 4, 0);
                    Hu3DData[D_8010D3E8_awful_tower->model[20]].cameraBit |= D_8010CB60_awful_tower[group];
                } else {
                    Hu3DModelPosSet(D_8010D360_awful_tower[group][k]->model[counts[k] + 1],
                                    platCols[j] * 150 - 150, D_8010D0D0_awful_tower[j], 0.0f);
                    func_8001C258_main(D_8010D360_awful_tower[group][k]->model[counts[k] + 1], 4, 0);
                }
                counts[k]++;
            }
        }
    }
    if (D_8010CC18_awful_tower[group] > -1000.0f) {
        func_800E1BA8_minigame_ObjData *hitData;
        f32 dx;
        f32 dy;

        D_8010D1B0_awful_tower[group] -= 4.0f;
        D_8010D190_awful_tower[group] += D_8010D1A0_awful_tower[group];
        D_8010CC18_awful_tower[group] += D_8010D1B0_awful_tower[group];
        D_8010D1C0_awful_tower[group] += D_8010D1D0_awful_tower[group];
        Hu3DModelPosSet(D_8010D3E8_awful_tower->model[group + 16], D_8010D190_awful_tower[group],
                        D_8010CC18_awful_tower[group], 0.0f);
        Hu3DModelRotSet(D_8010D3E8_awful_tower->model[group + 16], 0.0f, 0.0f, D_8010D1C0_awful_tower[group]);
        dx = D_8010D190_awful_tower[group] - object->trans.x;
        dy = (D_8010CC18_awful_tower[group] - object->trans.y - 75.0f) / 2.0;
        if (D_8010D1E0_awful_tower[group] != 0.0f && (D_8010D3E4_awful_tower == 2 || D_8010D3E4_awful_tower == 6) &&
            dx * dx + dy * dy < 3600.0f) {
            hitData = object->data;
            hitData->unk3C = (object->trans.y > 3500.0f) ? 90.0f : -90.0f;
            func_800E5690_minigame(object, 30);
            if (hitData->unk38 == 1000.0f) {
                hitData->unk40 = -D_800EB760_minigame;
            } else {
                hitData->unk40 = -D_800EB760_minigame;
                hitData->unk38 = -D_800EB744_minigame * 0.6f;
            }
            func_800E4C88_minigame(object, 6, (D_8010D190_awful_tower[group] + object->trans.x) / 2.0,
                                   (D_8010CC18_awful_tower[group] + object->trans.y + 75.0f) / 2.0, 0.0f, 0.0f,
                                   180.0f);
            PlayerFXPlay(0x286, hitData->unk59);
            func_800E19FC_minigame(hitData, 8);
            omVibrate(hitData->unk59, 2, 2, 20);
            D_8010D1E0_awful_tower[group] = 0.0f;
        }
    }
    if (Hu3DData[object->model[6]].motTime >= 10.0f) {
        Hu3DData[object->model[6]].motTime = 0.0f;
        func_8001C258_main(object->model[6], 4, 4);
    }
    if (player->cpuDifficulty != -1 ||
        (D_8010D3FC_awful_tower == group && D_8010D3E4_awful_tower == 3 && D_8010D3DC_awful_tower >= 50)) {
        u8 chances[4] = { 8, 9, 12, 14 };
        u8 jitters[4] = { 18, 11, 6, 4 };
        u8 chance;

        if (player->cpuDifficulty != -1) {
            chance = chances[player->cpuDifficulty];
        } else {
            chance = 16;
        }
        if (D_8010CBE8_awful_tower % 60 == 0) {
            D_8010CC78_awful_tower[group] =
                (player->cpuDifficulty != -1)
                    ? rand8() % jitters[player->cpuDifficulty] - jitters[player->cpuDifficulty] / 2
                    : 0;
        }
        D_800CDA7C_main[player->pad] = 0;
        D_800D5558_main[player->pad] = 0;
        D_800D1244_main[player->pad] = 0;
        D_800CBB6E_main[player->pad] = 0;
        D_800D20A1_main[player->pad] = 0;
        D_800D056A_main[player->pad] = 0;
        D_800D1382_main[player->pad] = 0;
        if (D_8010CC40_awful_tower[group] != 0 && D_8010CBFC_awful_tower[group] != -1 &&
            D_8010CBFC_awful_tower[group] != D_8010CC3C_awful_tower[group] - 1 &&
            D_8010CBFC_awful_tower[group] != D_8010CC3C_awful_tower[group]) {
            D_8010CC40_awful_tower[group] = 0;
        }
        if (D_8010D3E4_awful_tower == 2) {
            if (D_8010CBE8_awful_tower % 60 ==
                D_8010CC7C_awful_tower[D_8010CBFC_awful_tower[group]] +
                    ((D_8010CBFC_awful_tower[group] % 2 != 0) ? 20 : 50) + D_8010CC78_awful_tower[group]) {
                if (D_8010CC40_awful_tower[group] == 0 ||
                    D_8010CBFC_awful_tower[group] == D_8010CC3C_awful_tower[group]) {
                    if (D_8010CBFC_awful_tower[group] != -1) {
                        D_8010CCA4_awful_tower[group] += (D_8010CCA4_awful_tower[group] < 5) ? 1 : 0;
                    }
                }
            }
        }
        if (D_8010D3E4_awful_tower == 2) {
            if ((rand8() & 15) < chance || D_8010CCA4_awful_tower[group] >= 5) {
                if (D_8010CBE8_awful_tower % 60 ==
                    D_8010CC7C_awful_tower[D_8010CBFC_awful_tower[group]] +
                        ((D_8010CBFC_awful_tower[group] % 2 != 0) ? 20 : 50) + D_8010CC78_awful_tower[group]) {
                    if (D_8010CC40_awful_tower[group] == 0 ||
                        D_8010CBFC_awful_tower[group] == D_8010CC3C_awful_tower[group]) {
                        if (D_8010CBFC_awful_tower[group] != -1) {
                            D_8010CC40_awful_tower[group] = 1;
                            D_8010CC3C_awful_tower[group] = D_8010CBFC_awful_tower[group] + 1;
                            D_8010CCA4_awful_tower[group] = 0;
                        }
                    }
                }
            }
        }
        if (D_8010D3E4_awful_tower == 3 && D_8010D3FC_awful_tower == group && D_8010CBE8_awful_tower % 60 == 27 &&
            D_8010D3DC_awful_tower >= 40) {
            if (D_8010CC40_awful_tower[group] == 0 ||
                D_8010CBFC_awful_tower[group] == D_8010CC3C_awful_tower[group]) {
                if (D_8010CBFC_awful_tower[group] == 15) {
                    D_8010CC40_awful_tower[group] = 1;
                    D_8010CC3C_awful_tower[group] = D_8010CBFC_awful_tower[group] + 1;
                    D_8010CC44_awful_tower = 1;
                    D_8010CC48_awful_tower = object->trans.x;
                }
            }
        }
        if (D_8010CC40_awful_tower[group] == D_8010CC90_awful_tower[D_8010CC3C_awful_tower[group] - 1] + 3) {
            D_800CDA7C_main[player->pad] |= 0x8000;
            D_800D5558_main[player->pad] = 0x8000;
        } else if (D_8010CC40_awful_tower[group] > D_8010CC90_awful_tower[D_8010CC3C_awful_tower[group] - 1] + 3) {
            D_800CDA7C_main[player->pad] |= 0x8000;
        }
        if (D_8010CC40_awful_tower[group] != 0) {
            f32 dx = (platCols[D_8010CC3C_awful_tower[group] - 1] * 150 - 150) * 1.125 - object->trans.x;

            D_800CBB6E_main[player->pad] = (dx > 30.0f)    ? 60
                                           : (dx > 15.0f)  ? dx / 7.5 - 1.0
                                           : (dx < -30.0f) ? -60
                                           : (dx < -15.0f) ? dx / 7.5 + 1.0
                                                           : 0;
            D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
            D_8010CC40_awful_tower[group]++;
            D_8010CC40_awful_tower[group] %= 60;
            if (D_800CBB6E_main[player->pad] == 0 && D_8010CBFC_awful_tower[group] == D_8010CC3C_awful_tower[group]) {
                D_8010CC40_awful_tower[group] = 0;
            }
        }
        if (D_8010CBFC_awful_tower[group] == 0) {
            if (object->trans.x < -40.0f) {
                D_8010CC40_awful_tower[group] = 0;
                D_800CBB6E_main[player->pad] = 60;
                D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
            }
            if (D_8010CBFC_awful_tower[group] == 0 && object->trans.x > 20.0f) {
                D_8010CC40_awful_tower[group] = 0;
                D_800CBB6E_main[player->pad] = -60;
                D_800D056A_main[player->pad] = D_800CBB6E_main[player->pad] * 2;
            }
        }
        if (D_8010D3E4_awful_tower == 3 && D_8010D3FC_awful_tower == group) {
            savedCB70 = D_8010CB70_awful_tower.state;
            D_8010CB70_awful_tower.state = MG_STATE_PLAY;
            data->unk4C = 0.5f;
            data->unkB4 = 1.5f;
        }
    }
    if (D_8010D3FC_awful_tower == group &&
        ((D_8010D3E4_awful_tower >= 4 && object->trans.y >= 4550.0f) ||
         (D_8010D3E4_awful_tower == 3 && D_8010D3DC_awful_tower >= 30))) {
        omSetTra(D_8010D360_awful_tower[D_8010D3FC_awful_tower][2], 0.0f, 4500.0f, 0.0f);
        closePlats[2] = 15;
        closeDists[2] = 4500.0f;
    }
    if (D_8010CBFC_awful_tower[group] == 15 && (D_8010D3E4_awful_tower != 3 || D_8010D3DC_awful_tower < 30)) {
        D_800CBB6E_main[player->pad] = 0;
        D_800D056A_main[player->pad] = 0;
        D_800CDA7C_main[player->pad] &= 0x7FFF;
        D_800D5558_main[player->pad] &= 0x7FFF;
        D_800D1244_main[player->pad] &= 0x7FFF;
    }
    if (D_8010CC74_awful_tower[group] != 0) {
        if (D_8010CC74_awful_tower[group] == ((D_800CBB6E_main[player->pad] < 0)   ? -1
                                              : (D_800CBB6E_main[player->pad] > 0) ? 1
                                                                                   : 0)) {
            D_8010CC74_awful_tower[group] = 0;
            D_800CBB6E_main[player->pad] = 0;
            D_800D056A_main[player->pad] = 0;
        }
    }
    for (i = 0; i < 5; i++) {
        A96F0_ObjData *coin = D_8010D390_awful_tower[i]->data;

        coinNear[i] = ABS(D_8010D390_awful_tower[i]->trans.y - (object->trans.y + 160.0)) < 200.0;
        coin->unk54 = D_8010D330_awful_tower[group][i] && coinNear[i];
        coin->unk48 = (data->unk38 != 1000.0f) ? 59.0f : 40.0f;
        if (i == 0 && object->trans.x > 55.0f && object->trans.y > 1275.0f && object->trans.y < 1425.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
        if (i == 2 && object->trans.x > 55.0f && object->trans.y > 2300.0f && object->trans.y < 2450.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
        if (i == 3 && object->trans.x < -55.0f && object->trans.y > 3300.0f && object->trans.y < 3500.0f &&
            data->unk38 >= 1.0f && data->unk38 < 1000.0f) {
            coin->unk48 = 90.0f;
        }
    }
    if (D_8010CC28_awful_tower[group] != 0) {
        D_800CDA7C_main[player->pad] &= 0x7FFF;
    }
    if (!(D_8010D3FC_awful_tower < 4 &&
          (D_8010D3E4_awful_tower == 7 || (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower >= 30)))) {
        func_800DDD94_minigame(object);
    }
    if (D_8010D3E4_awful_tower == 3 && D_8010CC44_awful_tower >= 12) {
        HuAudFXStop(data->unkC5);
    }
    if (D_8010D3E4_awful_tower == 3 && group == D_8010D3FC_awful_tower && D_8010CC44_awful_tower != 0) {
        f32 scales[18] = { 1.0f, 1.0f, 1.0f, 0.909788f, 0.819576f, 0.729364f,
                           0.639153f, 0.548941f, 0.458729f, 0.368517f, 0.278305f, 0.188094f,
                           0.097882f, 0.00767f, 0.005113f, 0.002557f, 0.0f, 0.0f };

        object->trans.x = D_8010CC48_awful_tower * scales[D_8010CC44_awful_tower - 1];
        D_8010CC44_awful_tower = (D_8010CC44_awful_tower == 18) ? 0 : D_8010CC44_awful_tower + 1;
    }
    if (savedCB70 != 0xFF) {
        D_8010CB70_awful_tower.state = savedCB70;
    }
    func_8001C258_main(object->model[1], 4, 4);
    for (i = 0; i < 3; i++) {
        if (data->unk38 != 1000.0f && ABS(object->trans.x - D_8010D360_awful_tower[group][i]->trans.x) < 110.0f &&
            ABS(object->trans.y + 75.0f - D_8010D360_awful_tower[group][i]->trans.y) < 125.0f) {
            s32 facing = data->unk3C >= 0.0f && data->unk3C < 180.0f;
            s32 side = D_8010D360_awful_tower[group][i]->trans.x < object->trans.x;

            if (facing == side) {
                D_8010CC74_awful_tower[group] = facing * 2 - 1;
            }
        }
    }
    for (i = 0; i < 5; i++) {
        A96F0_ObjData *coin = D_8010D390_awful_tower[i]->data;
        s32 cameras;

        if (D_8010D330_awful_tower[group][i] != 0 && coinNear[i] != 0 && coin->unk54 == 0) {
            EffectGroupModel *effect = D_800D6A00_main[D_8010D2CC_awful_tower[group]]->models;

            func_8000D550_main(D_8010D2CC_awful_tower[group], D_8010D390_awful_tower[i]->trans.x,
                               D_8010D390_awful_tower[i]->trans.y, D_8010D390_awful_tower[i]->trans.z);
            Hu3DModelCameraSet(effect->model, D_8010CB60_awful_tower[group]);
            D_8010D330_awful_tower[group][i] = 0;
        } else if (D_8010D330_awful_tower[group][i] != 0 &&
                   ABS(D_8010D390_awful_tower[i]->trans.y - D_8010D320_awful_tower[group]) > 900.0f) {
            D_8010D330_awful_tower[group][i] = 2;
        } else if (D_8010D330_awful_tower[group][i] == 2) {
            D_8010D330_awful_tower[group][i] = 1;
        }
        if (group == 3) {
            cameras = ((D_8010D330_awful_tower[0][i] == 1) ? D_8010CB60_awful_tower[0] : 0) |
                      ((D_8010D330_awful_tower[1][i] == 1) ? D_8010CB60_awful_tower[1] : 0) |
                      ((D_8010D330_awful_tower[2][i] == 1) ? D_8010CB60_awful_tower[2] : 0) |
                      ((D_8010D330_awful_tower[3][i] == 1) ? D_8010CB60_awful_tower[3] : 0);
            func_8001C258_main(D_8010D390_awful_tower[i]->model[0], 4, 0);
            Hu3DModelCameraSet(D_8010D390_awful_tower[i]->model[0], cameras);
        }
    }
    if (D_8010CC00_awful_tower[group] > 0 && (u16)func_800E4A80_minigame(object) == 14) {
        object->trans.y = D_8010D0D0_awful_tower[D_8010CC00_awful_tower[group] - 1] + 50.0f;
    }
    work = object->data;
    if (work->unk38 != 1000.0f && work->unk53[3] != 0 && work->unk53[3] != -1 && D_8010CC08_awful_tower[group] == -1) {
        func_8004AC98_main(player->chr + 203, work->unk59);
    }
    D_8010CC08_awful_tower[group] = (work->unk53[3] != 0) ? work->unk53[3] - 1 : -1;
    D_8010CC04_awful_tower[group] =
        (work->unk53[3] != 0 && work->unk53[3] != -1) ? closePlats[(work->unk53[3] - 1) % 3] : 0;
    if (work->unk53[3] >= 0 && work->unk53[0] >= 0 &&
        D_8010CC04_awful_tower[group] == closePlats[(work->unk53[0] - 1) % 3] && D_8010CC04_awful_tower[group] < 15) {
        D_8010CC04_awful_tower[group]++;
        D_8010CC70_awful_tower[group] = 1;
    } else {
        D_8010CC70_awful_tower[group] = 0;
    }
    if (work->unk38 == 1000.0f) {
        D_8010CC28_awful_tower[group] = 0;
    }
    work->unk53[3] = -1;
    D_8010CBFC_awful_tower[group] = -1;
    if (work->unk53[0] >= 0) {
        D_8010CBFC_awful_tower[group] = (work->unk53[0] != 0) ? closePlats[(work->unk53[0] - 1) % 3] + 1 : 0;
        if (D_8010CBFC_awful_tower[group] == 16) {
            D_8010D3FE_awful_tower += (D_8010D3FE_awful_tower < 255) ? 1 : 0;
        }
        i = (work->unk53[0] != 0) ? closePlats[(work->unk53[0] - 1) % 3] : 0;
        if (D_8010D3E4_awful_tower == 2 && (D_8010CC0C_awful_tower[group] == 0 || D_8010CC0C_awful_tower[group] == 3) &&
            i % 5 == 2) {
            if (D_8010CC0C_awful_tower[group] == 0) {
                D_8010D150_awful_tower[group] = 0.0f;
                D_8010D170_awful_tower[group] = 0.0f;
                D_8010D180_awful_tower[group] = -20.0f;
                D_8010D160_awful_tower[group] = D_8010D320_awful_tower[group] + 900.0f;
                func_8001C258_main(D_8010D3E8_awful_tower->model[group + 8], 4, 0);
            }
            D_8010CC0C_awful_tower[group] = 1;
            D_8010CC10_awful_tower[group] = i / 5;
            Hu3DModelScaleSet(D_8010D3E8_awful_tower->model[group + 8],
                              (D_8010CC10_awful_tower[group] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
            Hu3DModelScaleSet(D_8010D3E8_awful_tower->model[group + 12],
                              (D_8010CC10_awful_tower[group] != 3) ? -6.0525f : 6.0525f, 6.0525f, 6.0525f);
        }
        if (D_8010CC0C_awful_tower[group] == 2 && (i % 5 == 0 || i % 5 == 4)) {
            D_8010CC0C_awful_tower[group] = 3;
        }
    }
    if (object->trans.x <= -50.0f && object->trans.y < 15.0f) {
        object->trans.x = -40.0f;
    }
    if (work->unk38 != 1000.0) {
        work->unk4C = (work->unk38 < -0.05) ? 0.5f : 1.0f;
        work->unkB4 = (work->unk38 < -0.05) ? 1.5f : 1.0f;
        D_8010CBEC_awful_tower[group] = object->trans.x;
    } else {
        work->unk4C = 1.0f;
        work->unkB4 = 1.0f;
        D_8010CBEC_awful_tower[group] = 32000.0f;
    }
    if (D_8010CC0C_awful_tower[group] != 0) {
        f32 targetY = 0.0f;
        f32 heights[3] = { 1550.0f, 2650.0f, 3850.0f };
        f32 targetX;
        s32 frame;

        targetX = 0.0f;
        switch (D_8010CC0C_awful_tower[group]) {
            case 1:
                targetX = (D_8010CC10_awful_tower[group] != 3) ? 100.0f : -100.0f;
                targetY = heights[D_8010CC10_awful_tower[group]];
                if (D_8010D3E4_awful_tower != 2) {
                    D_8010CC0C_awful_tower[group] = 3;
                } else if (D_8010D160_awful_tower[group] <= targetY + 100.0f) {
                    D_8010CC0C_awful_tower[group] = 2;
                } else {
                    break;
                }
            case 2:
                targetX = (D_8010CC10_awful_tower[group] != 3) ? 100.0f : -100.0f;
                targetY = heights[D_8010CC10_awful_tower[group]];
                i = ((D_8010CC10_awful_tower[group] == 0)   ? 33
                     : (D_8010CC10_awful_tower[group] == 1) ? 10
                                                            : 41) -
                    D_8010CC4C_awful_tower[group];
                frame = (i < 0) ? i + 60 : i;
                if (D_8010CBE8_awful_tower % 60 == frame && D_8010CC14_awful_tower[group] == 0) {
                    D_8010CC14_awful_tower[group] = 1;
                    D_8010CC4C_awful_tower[group] += (D_8010CC4C_awful_tower[group] < 30) ? 5 : 0;
                    func_80014850_main(D_8010D348_awful_tower[group][1]);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[group + 8], 4, 4);
                }
                if (D_8010D3E4_awful_tower != 2) {
                    D_8010CC0C_awful_tower[group] = 3;
                }
            case 3:
                if (D_8010D320_awful_tower[group] + 900.0f <= D_8010D160_awful_tower[group] ||
                    D_8010D150_awful_tower[group] >= 700.0f || D_8010D150_awful_tower[group] <= -700.0f) {
                    D_8010CC14_awful_tower[group] = 0;
                    D_8010CC0C_awful_tower[group] = 0;
                    D_8010CC4C_awful_tower[group] = 0;
                    func_8001C258_main(D_8010D3E8_awful_tower->model[group + 8], 4, 4);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[group + 12], 4, 4);
                } else if (D_8010CC0C_awful_tower[group] == 3) {
                    targetX = (D_8010CC10_awful_tower[group] == 2) ? -1000.0f : 1000.0f;
                    targetY = D_8010D320_awful_tower[group] + 1200.0f;
                }
                break;
        }
        // Bug: tests the array address instead of D_8010CC0C_awful_tower[group], so this is always true.
        if ((u32)D_8010CC0C_awful_tower != 0) {
            wave = D_8010D1F0_awful_tower[D_8010CBE8_awful_tower % 55];
            vx = (targetX - D_8010D150_awful_tower[group]) / 8.0f;
            vx = (vx < -22.0f) ? -22.0f : (vx > 22.0f) ? 22.0f
                                                       : vx;
            vy = (targetY - D_8010D160_awful_tower[group]) / 12.0f;
            vy = (vy < -27.0f) ? -27.0f : (vy > 27.0f) ? 27.0f
                                                       : vy;
            D_8010D170_awful_tower[group] = (vx < D_8010D170_awful_tower[group])
                                                ? ((D_8010D170_awful_tower[group] - 2.5 < vx) ? vx : D_8010D170_awful_tower[group] - 2.5)
                                                : ((D_8010D170_awful_tower[group] + 2.5 > vx) ? vx : D_8010D170_awful_tower[group] + 2.5);
            D_8010D180_awful_tower[group] = (vy < D_8010D180_awful_tower[group])
                                                ? ((D_8010D180_awful_tower[group] - 2.5 < vy) ? vy : D_8010D180_awful_tower[group] - 2.5)
                                                : ((D_8010D180_awful_tower[group] + 2.5 > vy) ? vy : D_8010D180_awful_tower[group] + 2.5);
            D_8010D150_awful_tower[group] += D_8010D170_awful_tower[group];
            D_8010D160_awful_tower[group] += D_8010D180_awful_tower[group];
            if (wave == -1.0f) {
                wave = D_8010D1F0_awful_tower[D_8010CBE8_awful_tower % 55] =
                    cosdf(D_8010CBE8_awful_tower % 55 / 55.0 * 360.0);
            }
            Hu3DModelPosSet(D_8010D3E8_awful_tower->model[group + 8], D_8010D150_awful_tower[group],
                            D_8010D160_awful_tower[group] + wave * 15.0f, 0.0f);
            Hu3DModelPosSet(D_8010D3E8_awful_tower->model[group + 12], D_8010D150_awful_tower[group],
                            D_8010D160_awful_tower[group] + wave * 15.0f, 0.0f);
            if (D_8010CC14_awful_tower[group] != 0) {
                if (D_8010CC14_awful_tower[group] == 12) {
                    D_8010CC14_awful_tower[group] = 0;
                    func_80014850_main(D_8010D348_awful_tower[group][0]);
                    func_8001C258_main(D_8010D3E8_awful_tower->model[group + 12], 4, 4);
                } else {
                    D_8010CC14_awful_tower[group]++;
                    if (D_8010CC14_awful_tower[group] == 8 && D_8010CC18_awful_tower[group] <= -1000.0f) {
                        D_8010D1E0_awful_tower[group] = 1.0f;
                        D_8010D190_awful_tower[group] = D_8010D150_awful_tower[group];
                        D_8010CC18_awful_tower[group] = D_8010D160_awful_tower[group];
                        D_8010D1A0_awful_tower[group] = D_8010CCA8_awful_tower[D_8010CC10_awful_tower[group]];
                        D_8010D1B0_awful_tower[group] = D_8010CCB4_awful_tower[D_8010CC10_awful_tower[group]];
                        D_8010D1C0_awful_tower[group] = 0.0f;
                        D_8010D1D0_awful_tower[group] = (D_8010CC10_awful_tower[group] != 3) ? 23.0f : -23.0f;
                        func_8001C258_main(D_8010D3E8_awful_tower->model[group + 16], 4, 0);
                        Hu3DModelPosSet(D_8010D3E8_awful_tower->model[group + 16], D_8010D190_awful_tower[group],
                                        D_8010CC18_awful_tower[group], 0.0f);
                        Hu3DModelRotSet(D_8010D3E8_awful_tower->model[group + 16], 0.0f, 0.0f,
                                        D_8010D1C0_awful_tower[group]);
                    }
                }
            }
        }
    }
    if (D_8010CC04_awful_tower[group] != 0) {
        if (object->trans.x < 5.0f && object->trans.x > 0.0f) {
            if (object->trans.x - D_8010CC60_awful_tower[group] < -20.0f &&
                D_8010CC60_awful_tower[group] - D_8010CC50_awful_tower[group] > 10.0f) {
                object->trans.x = D_8010CC60_awful_tower[group];
            }
        }
        if (object->trans.x > -5.0f && object->trans.x < 0.0f) {
            if (object->trans.x - D_8010CC60_awful_tower[group] > 20.0f &&
                D_8010CC60_awful_tower[group] - D_8010CC50_awful_tower[group] < -10.0f) {
                object->trans.x = D_8010CC60_awful_tower[group];
            }
        }
    }
    D_8010CC50_awful_tower[group] = D_8010CC60_awful_tower[group];
    D_8010CC60_awful_tower[group] = object->trans.x;
    object->trans.x = (object->trans.x < -175.0f)  ? -175.0f
                      : (object->trans.x > 175.0f) ? 175.0f
                                                   : object->trans.x;
    if (object->trans.y > D_8010D320_awful_tower[group]) {
        D_8010D320_awful_tower[group] = object->trans.y;
    }
    if (object->trans.y < D_8010D320_awful_tower[group] - 300.0f) {
        D_8010D320_awful_tower[group] = object->trans.y + 300.0f;
    }
    if (D_8010D320_awful_tower[group] < 650.0f) {
        D_8010D320_awful_tower[group] = 650.0f;
    }
    object->trans.z = 0.0f;
    if (D_8010D3E4_awful_tower == 0 && D_8010D3DC_awful_tower < 91) {
        if (D_8010D3DC_awful_tower < 76) {
            D_8010D320_awful_tower[group] = (1.0f - D_8010D3DC_awful_tower / 75.0f) * 3625.0f + 1025.0f;
        }
        if (D_8010D3DC_awful_tower >= 76) {
            f32 t = 1.0f - (D_8010D3DC_awful_tower - 75) / 15.0f;

            D_8010D320_awful_tower[group] = t * 375.0f * t + 650.0f;
        }
    }
    if (D_8010CC18_awful_tower[group] > -1000.0f &&
        (D_8010CC18_awful_tower[group] < D_8010D320_awful_tower[group] - 850.0f ||
         D_8010CC18_awful_tower[group] > D_8010D320_awful_tower[group] + 850.0f)) {
        D_8010CC18_awful_tower[group] = -1000.0f;
        func_8001C258_main(D_8010D3E8_awful_tower->model[group + 16], 4, 4);
    }
    CenterM[group].y = D_8010D320_awful_tower[group];
    D_800CDA7C_main[player->pad] = savedBtn;
    D_800D5558_main[player->pad] = savedBtn2;
    D_800D1244_main[player->pad] = savedBtn3;
    D_800CBB6E_main[player->pad] = savedStickX;
    D_800D20A1_main[player->pad] = savedStickY;
    D_800D056A_main[player->pad] = savedStick2;
    D_800D1382_main[player->pad] = savedStick3;
    if (group == 3) {
        D_8010CBE8_awful_tower++;
        for (i = 0; i < 15; i++) {
            D_8010D110_awful_tower[i] = -D_8010D0D0_awful_tower[i];
        }
        if (D_8010D3FC_awful_tower == 5) {
            s32 best = -1;
            s32 bestIdx = -1;

            for (i = 0; i < 4; i++) {
                if (D_8010CBFC_awful_tower[i] == 15 && D_8010CC2C_awful_tower[i] <= D_8010D3A8_awful_tower[i]->trans.x) {
                    j = rand8();
                    if (best < j) {
                        bestIdx = i;
                        best = j;
                    }
                }
            }
            if (bestIdx >= 0) {
                D_8010D3FC_awful_tower = bestIdx;
                if (D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x < 105.0) {
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x = 105.0f;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (D_8010CBFC_awful_tower[i] == 15) {
                D_8010CC2C_awful_tower[i] = D_8010D3A8_awful_tower[i]->trans.x;
            } else {
                D_8010CC2C_awful_tower[i] = 1000.0f;
            }
        }
    }
}

void func_8010CB1C_awful_tower(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &Hu3DData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}
