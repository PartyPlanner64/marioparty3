#include "common.h"
#include "game/overlays/minigame.h"
#include "game/pause.h"

typedef struct PickingPanicPlayer {
    /* 0x00 */ s8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s8 unk2;
    /* 0x03 */ s8 unk3;
    /* 0x04 */ s8 unk4;
    /* 0x05 */ char unk5;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ char unkA[2];
    /* 0x0C */ s32 unkC;
} PickingPanicPlayer; // sizeof 0x10

typedef struct PickingPanicCpuState {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
} PickingPanicCpuState; // sizeof 0x08

// Group of misaligned byte variables (see undefined_syms.txt for aliases).
typedef struct PickingPanicBssEF14 {
    /* 0x00 */ s8 unk00; // D_8010EF14_picking_panic
    /* 0x01 */ u8 unk01[2]; // D_8010EF15_picking_panic
} PickingPanicBssEF14; // sizeof 0x03

extern Gfx *gMainGfxPos;
extern const s16 D_8010E720_picking_panic[];

MinigameFlow D_8010E5B0_picking_panic = { 0 };
s32 D_8010E5D8_picking_panic = 0;
Gfx D_8010E5E0_picking_panic[] = {
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
u8 D_8010E628_picking_panic = 0;
f32 D_8010E62C_picking_panic[3][16] = { 0 };
u32 D_8010E6EC_picking_panic = 45;
s8 D_8010E6F0_picking_panic[2][4] = { 0 };
u8 D_8010E6F8_picking_panic[4] = { 0 };
u8 D_8010E6FC_picking_panic[4] = { 0 };
s8 D_8010E700_picking_panic[4] = { -1, -1, -1, -1 };
PickingPanicCpuState D_8010E704_picking_panic[2] = { 0 };
u8 D_8010E714_picking_panic[4] = { 0 };
u8 D_8010E718_picking_panic[6] = { 0, 0, 1, 0, 1, 1 };

f32 D_8010EC20_picking_panic[3][16] BSS;
f32 D_8010ECE0_picking_panic[3][16] BSS;
u8 D_8010EDA0_picking_panic[2][4] BSS;
u8 D_8010EDA8_picking_panic[2][4] BSS;
f32 D_8010EDB0_picking_panic[2][4] BSS;
f32 D_8010EDD0_picking_panic[2][4] BSS;
f32 D_8010EDF0_picking_panic[2][4] BSS;
f32 D_8010EE10_picking_panic[2][4] BSS;
f32 D_8010EE30_picking_panic[2][4] BSS;
f32 D_8010EE50_picking_panic[2][4] BSS;
f32 D_8010EE70_picking_panic BSS;
f32 D_8010EE74_picking_panic BSS;
f32 D_8010EE78_picking_panic BSS;
f32 D_8010EE7C_picking_panic BSS;
f32 D_8010EE80_picking_panic BSS;
f32 D_8010EE84_picking_panic BSS;
f32 D_8010EE88_picking_panic BSS;
f32 D_8010EE8C_picking_panic BSS;
f32 D_8010EE90_picking_panic BSS;
f32 D_8010EE94_picking_panic BSS;
f32 D_8010EE98_picking_panic BSS;
u8 D_8010EE9C_picking_panic[4] BSS; /* Unreferenced. */
PickingPanicPlayer D_8010EEA0_picking_panic[4] BSS;
PickingPanicPlayer *D_8010EEE0_picking_panic[4] BSS;
u8 D_8010EEF0_picking_panic[2] BSS;
f32 D_8010EEF4_picking_panic[2] BSS;
omObjData *D_8010EEFC_picking_panic BSS;
omObjData *D_8010EF00_picking_panic[4] BSS;
u16 D_8010EF10_picking_panic[2] BSS;
PickingPanicBssEF14 pickingPanicBssEF14 BSS;
s16 *D_8010EF18_picking_panic[2][4][3] BSS;
f32 D_8010EF78_picking_panic BSS;
s32 D_8010EF7C_picking_panic BSS;
s16 D_8010EF80_picking_panic BSS;
f32 D_8010EF84_picking_panic[2] BSS;
f32 D_8010EF8C_picking_panic[2] BSS;
f32 D_8010EF94_picking_panic BSS;
s8 D_8010EF98_picking_panic[2] BSS;
f32 D_8010EF9C_picking_panic[2] BSS;
u8 D_8010EFA4_picking_panic BSS;
u8 D_8010EFA5_picking_panic BSS;
s32 D_8010EFA8_picking_panic BSS;
f32 D_8010EFAC_picking_panic[2] BSS;
f32 D_8010EFB4_picking_panic[2] BSS;
s8 D_8010EFBC_picking_panic[2] BSS;
u16 D_8010EFBE_picking_panic BSS;
u8 D_8010EFC0_picking_panic[4] BSS;
f32 D_8010EFC4_picking_panic[2] BSS;
u8 D_8010EFCC_picking_panic[4] BSS; /* Unreferenced. */
s16 D_8010EFD0_picking_panic[10] BSS;
f32 D_8010EFE4_picking_panic[2] BSS;
f32 D_8010EFEC_picking_panic[2] BSS;
u8 D_8010EFF4_picking_panic[4] BSS; /* Unreferenced. */
s16 D_8010EFF8_picking_panic[10] BSS;

// Aliases into pickingPanicBssEF14 (see undefined_syms.txt).
extern s8 D_8010EF14_picking_panic;
extern u8 D_8010EF15_picking_panic[2];

void func_80105D3C_picking_panic(omObjData *object);
void func_80106020_picking_panic(omObjData *object);
void func_8010664C_picking_panic(omObjData *object);
void func_8010B160_picking_panic(omObjData *object);
void func_8010B194_picking_panic(omObjData *object);
void func_8010B1C0_picking_panic(omObjData *object);
void func_8010B1F4_picking_panic(omObjData *object);
void func_80106E84_picking_panic(omObjData *object);
void func_80107A48_picking_panic(void);
void func_80109C00_picking_panic(Gfx **, s32, s32);
void func_8010B11C_picking_panic(s16 arg0, s16 arg1);
void func_8010B220_picking_panic(omObjData *object, s8 arg1);
void func_8010B8D0_picking_panic(omObjData *object);
void func_8010B8EC_picking_panic(omObjData *object);
void func_8010B908_picking_panic(omObjData *object, s8 arg1);

void func_801059A0_picking_panic(void) {
    omObjData *object;

    Hu3DSprModelInit(0x20);
    omInitObjMan(50, 0);
    omGameSysInit();
    D_800CD280_main = 1;
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 120.0f);
    ScissorSet(1, 0.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 240.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 640.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 22.619865f, 4000.0f, 10000.0f);
    Hu3DCameraPerspectiveSet(1, 22.619865f, 4000.0f, 10000.0f);
    Hu3DGLightMaxSet(1);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, 0.0f, 65.0f, 90.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = 0.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 4687.5f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = 0.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 4687.5f;
    omAddObj(0, 0, 0, -1, func_80105D3C_picking_panic);
    D_8010EEFC_picking_panic = omAddObj(8, 38, 38, -1, func_8010664C_picking_panic);
    omSetStatBit(D_8010EEFC_picking_panic, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010EF00_picking_panic[0] = omAddObj(3, 8, 5, -1, func_8010B160_picking_panic);
    D_8010EF00_picking_panic[1] = omAddObj(3, 8, 5, -1, func_8010B194_picking_panic);
    D_8010EF00_picking_panic[2] = omAddObj(3, 8, 5, -1, func_8010B1C0_picking_panic);
    D_8010EF00_picking_panic[3] = omAddObj(3, 8, 5, -1, func_8010B1F4_picking_panic);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    GMesFontMesCreate(D_8010E720_picking_panic, 1);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    D_8010E5B0_picking_panic.type = MINIGAME_1V3;
    D_8010E5B0_picking_panic.startDelay = 60;
    D_8010E5B0_picking_panic.timer = 900;
    D_8010E5B0_picking_panic.timeDisp = MG_TIME_DISP_COUNTDOWN;
    D_8010E5B0_picking_panic.timerMode = MG_TIMER_COUNT_DOWN;
    D_8010E5B0_picking_panic.finishDelay = 75;
    D_8010E5B0_picking_panic.resultDelay = 165;
    D_8010E5B0_picking_panic.newRecord = FALSE;
    D_8010E5B0_picking_panic.gauge = MG_GAUGE_NONE;
    D_8010E5B0_picking_panic.timeLimit = -1;
    func_800E5EA0_minigame(&D_8010E5B0_picking_panic);
}

void func_80105D3C_picking_panic(omObjData *object) {
    u8 groups[4];
    u8 group;
    s32 i;

    D_8010EFBE_picking_panic = 0;
    D_8010EF80_picking_panic = 0;
    D_8010EFA8_picking_panic = 0;
    D_8010EF7C_picking_panic = 0;
    D_8010EF14_picking_panic = 5;
    D_8010EF10_picking_panic[0] = D_8010EF10_picking_panic[1] = 1;
    D_8010EF98_picking_panic[0] = D_8010EF98_picking_panic[1] = -1;
    D_8010EFBC_picking_panic[0] = D_8010EFBC_picking_panic[1] = 0;
    D_8010EEF0_picking_panic[0] = D_8010EEF0_picking_panic[1] = 0;
    D_8010EF15_picking_panic[0] = D_8010EF15_picking_panic[1] = 0;
    D_8010EFA4_picking_panic = 0xFF;
    D_8010EF94_picking_panic = D_8010EF84_picking_panic[0] = D_8010EF84_picking_panic[1] = 0.0f;

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[i] = &D_8010EEA0_picking_panic[i];
        bzero(&D_8010EEA0_picking_panic[i], sizeof(PickingPanicPlayer));
    }

    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        groups[i] = group;
        D_8010EFC0_picking_panic[groups[i]] = i;
    }

    for (i = 0; i < 4; i++) {
        D_8010EEE0_picking_panic[groups[i]]->unk0 = i;
        D_8010EEE0_picking_panic[i]->unk2 = GwPlayer[D_8010EFC0_picking_panic[i]].pad;
        D_8010EEE0_picking_panic[i]->unk3 = GwPlayer[D_8010EFC0_picking_panic[i]].chr;
        D_8010EEE0_picking_panic[i]->unk1 = i;
        D_8010EEE0_picking_panic[i]->unk4 = (GwPlayer[D_8010EFC0_picking_panic[i]].stat & 1)
                                                ? GwPlayer[D_8010EFC0_picking_panic[i]].cpu_difficulty
                                                : -1;
    }

    for (i = 0; i < 4; i++) {
        if (D_8010EEE0_picking_panic[i]->unk4 != -1) {
            if (D_8010EEE0_picking_panic[(i & 1) ? i - 1 : i + 1]->unk4 == -1) {
                D_8010EEE0_picking_panic[i]->unk4 += 4;
            }
        }
    }

    Hu3DHookFuncCreate(0, func_80109C00_picking_panic, 2);
    object->func = func_80106020_picking_panic;
}

const s16 D_8010E720_picking_panic[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x8149, 0x0000
};

void func_80106020_picking_panic(omObjData *object) {
    s32 i;
    u8 j;

    CenterM[0].x = 0.0f;
    CenterM[0].y = 0.0f;
    CenterM[0].z = 0.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 0.0f;
    CenterM[1].z = 0.0f;
    D_8010EFA8_picking_panic++;
    D_8010EF7C_picking_panic++;
    MgFlowMain();
    switch (D_8010EF80_picking_panic) {
        case 0:
            if (D_8010EFA8_picking_panic == 2) {
                HuAudFXPlay(0x371);
            }
            if (MgFlowStatGet() == MG_STATE_START) {
                D_8010EF80_picking_panic = 1;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 1:
            if (D_8010EFA8_picking_panic == 33 && D_8010EFBE_picking_panic == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x38);
            }
            if (MgFlowStatGet() == MG_STATE_PLAY) {
                D_8010EF80_picking_panic = 2;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 2:
            if (D_8010EF14_picking_panic == 5 && MgFlowStatGet() == MG_STATE_FINISH) {
                if (D_8010EF15_picking_panic[0] == D_8010EF15_picking_panic[1]) {
                    D_8010EF80_picking_panic = 4;
                    D_8010EF14_picking_panic = 4;
                } else {
                    D_8010EF80_picking_panic = 3;
                    D_8010EF14_picking_panic = D_8010EF15_picking_panic[0] <= D_8010EF15_picking_panic[1];
                }
                D_8010EFA8_picking_panic = 0;
            }
            if (D_8010EF80_picking_panic != 3) {
                break;
            }
        case 3:
            if (D_8010EFA8_picking_panic == 0) {
                if (MgFlowStatGet() != MG_STATE_FINISH) {
                    MgFlowStatNext();
                }
                D_8010E5B0_picking_panic.resultType = MG_RESULT_WIN_2;
                D_8010E5B0_picking_panic.winners[0] = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk0;
                D_8010E5B0_picking_panic.winners[1] = D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk0;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2]->unk0].bonusCoin = 10;
                GwPlayer[D_8010EEE0_picking_panic[D_8010EF14_picking_panic * 2 + 1]->unk0].bonusCoin = 10;
            }
            if (D_8010EFA8_picking_panic == 2) {
                func_800E6F34_minigame(30);
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                D_8010EF80_picking_panic = 5;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 4:
            if (D_8010EFA8_picking_panic == 1) {
                D_8010E5B0_picking_panic.resultType = MG_RESULT_DRAW;
                D_8010E5B0_picking_panic.finishDelay = 75;
                D_8010E5B0_picking_panic.resultDelay = 0x90;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                D_8010EF80_picking_panic = 6;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 5:
            if (D_8010EFA8_picking_panic == 31) {
                for (i = D_8010EF14_picking_panic * 2; i < D_8010EF14_picking_panic * 2 + 2; i++) {
                    s32 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

                    CharAnimSet(D_8010EF00_picking_panic[i]->model[1], 1,
                                       motions[D_8010EEE0_picking_panic[i]->unk3],
                                       D_8010EEE0_picking_panic[i]->unk8);
                    Hu3DMotionModelSet(D_8010EF00_picking_panic[i]->model[1], D_8010EF00_picking_panic[i]->motion[4]);
                    HuAudCharVoicePlay(D_8010EEE0_picking_panic[i]->unkC);
                }
            }
        case 6:
            if (MgFlowStatGet() == MG_STATE_EXIT) {
                D_8010EF80_picking_panic = 7;
                D_8010EFA8_picking_panic = 0;
            }
            break;
        case 7:
            if (D_8010EFA8_picking_panic == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010EFA8_picking_panic >= 32) {
                D_8010EFBE_picking_panic = 1;
            }
            break;
    }

    if (_CheckFlag(FLAG_MG_PRACTICE) && D_800D530C_main == 0 && D_8010EFA5_picking_panic == 0 && (u16)D_8010EF80_picking_panic == 2) {
        for (j = 0; j < 2; j++) {
            if (D_8010EEE0_picking_panic[j]->unk4 == -1 &&
                (D_800D5558_main[D_8010EEE0_picking_panic[j]->unk2] & R_TRIG)) {
                D_8010EFA5_picking_panic = 1;
            }
        }
    }

    if (D_8010EFBE_picking_panic != 0 || D_800D530C_main != 0 || D_8010EFA5_picking_panic != 0) {
        if (D_800D530C_main != 0 && D_8010EFA5_picking_panic == 0) {
            D_8010EFA5_picking_panic = 1;
        }
        if (D_8010EFA5_picking_panic != 0) {
            if (D_8010EFA5_picking_panic == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                HuAudFXAllFadeOut(20);
            }
            D_8010EFA5_picking_panic++;
            if (D_8010EFA5_picking_panic < 25) {
                return;
            }
        }
        HuAudSeqFadeOut(30);
        omOvlReturnEx(1);
    }
}

void func_8010664C_picking_panic(omObjData *object) {
    s32 fileIds[10] = { 0x0030000A, 0x0030000B, 0x0030000C, 0x0030000D, 0x0030000E,
                        0x00000031, 0x002A0012, 0x0030000F, 0x00300011, 0x00300010 };
    s16 i;
    s16 j;

    for (i = 0; i < 10; i++) {
        D_8010EFF8_picking_panic[i] = HuSprAnimDataRead(fileIds[i]);
        D_8010EFD0_picking_panic[i] = espEntry(D_8010EFF8_picking_panic[i], 0, 0);
        espDispOff(D_8010EFD0_picking_panic[i]);
    }

    object->model[0] = Hu3DModelRead(0x300000, 0x499);
    omSetTra(object, 0.0f, -525.0f, -450.0f);
    omSetSca(object, 1.75f, 1.75f, 1.75f);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    Hu3DModelCameraSet(object->model[0], HU3D_CAM0);
    object->model[1] = Hu3DModelLink(object->model[0]);
    Hu3DModelPosSet(object->model[1], 0.0f, -525.0f, -450.0f);
    Hu3DModelScaleSet(object->model[1], 1.75f, 1.75f, 1.75f);
    Hu3DMotionAttrSet(object->model[1], 1, 1);
    Hu3DModelCameraSet(object->model[1], HU3D_CAM1);

    for (i = 0; i < 2; i++) {
        object->model[4 + i] = Hu3DModelRead((i == 1) ? 0x300005 : 0x300006, 0x43D);
        Hu3DModelPosSet(object->model[4 + i], (i == 0) ? 450.0f : 750.0f, (i == 0) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(object->model[4 + i], 2.75f, 2.75f, 2.75f);
        Hu3DMotionAttrSet(object->model[4 + i], 2, 2);
        object->model[6 + i] = Hu3DModelLink(object->model[4 + i]);
        Hu3DModelPosSet(object->model[6 + i], (i == 1) ? -450.0f : -750.0f, (i == 1) ? -650.0f : -900.0f, -312.5f);
        Hu3DModelScaleSet(object->model[6 + i], 2.75f, 2.75f, 2.75f);
        Hu3DMotionAttrSet(object->model[6 + i], 2, 2);
    }

    for (i = 0; i < 2; i++) {
        object->model[2 + i] = Hu3DModelRead(0x300001, 0x4B9);
        Hu3DModelPosSet(object->model[2 + i], 890.0f, -222.0f, 0.0f);
        Hu3DModelScaleSet(object->model[2 + i], 1.38125f, 1.3f, 1.3f);
        Hu3DMotionAttrSet(object->model[2 + i], 1, 1);
        Hu3DModelCameraSet(object->model[2 + i], (i == 0) ? HU3D_CAM0 : HU3D_CAM1);
    }

    object->model[32] = Hu3DModelRead(0x300007, 0x499);
    Hu3DModelScaleSet(object->model[32], 1.0f, 1.1f, 1.0f);
    for (i = 1; i < 6; i++) {
        object->model[32 + i] = Hu3DModelLink(object->model[32]);
        Hu3DModelScaleSet(object->model[32 + i], 1.0f, 1.1f, 1.0f);
    }

    for (i = 0; i < 2; i++) {
        object->model[10 + i] = Hu3DModelRead(0x300009, 0x4BD);
        Hu3DModelPosSet(object->model[10 + i], -855.0f, 125.0f, 0.0f);
        Hu3DModelScaleSet(object->model[10 + i], 2.0f, 2.0f, 2.0f);
        Hu3DModelCameraSet(object->model[10 + i], (i == 0) ? HU3D_CAM0 : HU3D_CAM1);
    }

    object->model[8] = Hu3DModelRead(0x300008, 0x4B9);
    object->model[9] = Hu3DModelLink(object->model[8]);
    object->model[12] = Hu3DModelRead(0x300002, 0x4B9);
    for (i = 1; i < 20; i++) {
        object->model[12 + i] = Hu3DModelLink(object->model[12]);
    }

    {
        f32 xs[10] = { -510.0f, -555.0f, -663.0f, -692.0f, -797.0f, -823.0f, -947.0f, -1012.0f, -1121.0f, -1169.0f };
        f32 zs[10] = { 449.0f, 331.0f, 470.0f, 341.0f, 237.0f, 403.0f, 293.0f, 409.0f, 276.0f, 432.0f };
        s32 idx;

        for (i = 0; i < 10; i++) {
            for (j = 0, idx = i; j < 2; j++) {
                Hu3DModelPosSet(object->model[(j == 0) ? 12 + idx : 22 + idx], xs[idx] / 4687.5 * 5187.5,
                                zs[idx] / 4687.5 * 5187.5, -500.0f);
                Hu3DModelPosSet(object->model[(j == 0) ? 12 + idx : 22 + idx], 0.0f, 0.0f, -500.0f);
                Hu3DMotionAttrSet(object->model[(j == 0) ? 12 + idx : 22 + idx], 1, 1);
                Hu3DModelCameraSet(object->model[(j == 0) ? 12 + idx : 22 + idx], (j == 0) ? HU3D_CAM0 : HU3D_CAM1);
            }
        }
    }

    object->func = func_80106E84_picking_panic;
}

void func_80106E84_picking_panic(omObjData *object) {
    f32 scaleX[2];
    f32 scaleY[2];
    f32 offsetY[2];
    s32 i;
    s32 loser;
    s32 winner;
    f32 t;
    f32 u;
    f32 ty;
    f32 uy;

    if (D_8010EF14_picking_panic < 2 && D_8010EFA4_picking_panic < 0xFF) {
        winner = D_8010EF14_picking_panic;
        loser = 1 - winner;
        u = t = 1.0 - D_8010EFA4_picking_panic / 46.0;
        t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
                                           : t;
        ty = t * (winner * 2 - 1);
        u = (u < 0.0f) ? 0.0f : (u > 1.0f) ? 1.0f
                                           : u;
        u = (u + (1.0f - (1.0f - u) * (1.0f - u))) / 2.0f;
        uy = u * (winner * 2 - 1);

        D_8010EF78_picking_panic = 0.5 - ty * 0.5;
        D_8010EEF4_picking_panic[winner] = D_8010EFC4_picking_panic[winner] = t + t + 1.0f;
        D_8010EFEC_picking_panic[winner] = 1.0f / D_8010EEF4_picking_panic[winner];
        D_8010EF8C_picking_panic[winner] = 1.0f / D_8010EFC4_picking_panic[winner];
        D_8010EFB4_picking_panic[winner] = 0.5f;
        D_8010EFE4_picking_panic[winner] = winner * 0.5 + 0.25 - ty * 0.25;
        D_8010EF9C_picking_panic[winner] =
            (-D_8010EFB4_picking_panic[winner] * D_8010EEF4_picking_panic[winner] + 0.5) * 320.0 * 4.0;
        D_8010EFAC_picking_panic[winner] = (winner != 0) ? t * -1.5 * 240.0 * 4.0 : 0.0f;

        t = (t >= 0.99) ? 0.99f : t;
        ty = t * (winner * 2 - 1);
        D_8010EEF4_picking_panic[loser] = 1.0f;
        D_8010EFC4_picking_panic[loser] = 1.0f - t;
        D_8010EFEC_picking_panic[loser] = 1.0f / D_8010EEF4_picking_panic[loser];
        D_8010EF8C_picking_panic[loser] = 1.0f / D_8010EFC4_picking_panic[loser];
        D_8010EFB4_picking_panic[loser] = 0.5f;
        D_8010EFE4_picking_panic[loser] = loser * 0.5 + 0.25 - ty * 0.25;
        D_8010EF9C_picking_panic[loser] =
            (-D_8010EFB4_picking_panic[loser] * D_8010EEF4_picking_panic[loser] + 0.5) * 320.0 * 4.0;
        D_8010EFAC_picking_panic[loser] = (loser != 0) ? t * 240.0 * 4.0 : 0.0f;

        scaleX[winner] = scaleY[winner] = u + u + 1.0f;
        offsetY[winner] = winner * 0.5 + 0.25 - uy * 0.25;
        scaleX[loser] = 1.0f;
        scaleY[loser] = 1.0f - t;
        offsetY[loser] = loser * 0.5 + 0.25 - ty * 0.25;

        if (D_8010EF98_picking_panic[winner] != -1) {
            Hu3DModelPosSet(
                *D_8010EF18_picking_panic[winner][D_8010EEF0_picking_panic[winner]][D_8010EF98_picking_panic[winner]],
                t * 200.0f + -855.0f, -25.0f - ((winner != 0) ? t * 460.0f : t * 215.0f), 0.0f);
        }
        if (D_8010EFA4_picking_panic == 30) {
            for (i = 0; i < 10; i++) {
                Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[12 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[22 + i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    } else {
        for (i = 0; i < 2; i++) {
            D_8010EEF4_picking_panic[i] = D_8010EFC4_picking_panic[i] =
                (0.0f < D_8010EF94_picking_panic && D_8010E5D8_picking_panic == 2)
                    ? sindf(sindf(270.0 - D_8010EF94_picking_panic / 120.0 * 360.0) * 90.0f + 90.0f) * 0.125 + 1.0
                : (0.0f < D_8010EF94_picking_panic && D_8010E5D8_picking_panic == 1)
                    ? (D_8010EF94_picking_panic < 52.5 && D_8010EF94_picking_panic >= 37.5)
                          ? 1.125 - (D_8010EF94_picking_panic - 37.5) / 15.0 * 0.125
                      : (D_8010EF94_picking_panic < 37.5 && D_8010EF94_picking_panic >= 22.5) ? 1.125f
                      : (D_8010EF94_picking_panic < 22.5 && D_8010EF94_picking_panic >= 7.5)
                          ? (D_8010EF94_picking_panic - 7.5) / 15.0 * 0.125 + 1.0
                          : 1.0f
                : (D_8010EF80_picking_panic == 0)
                    ? (D_8010EFA8_picking_panic < 35)   ? 2.5f
                      : (D_8010EFA8_picking_panic < 66) ? 2.5 - (D_8010EFA8_picking_panic - 35) * 1.5 / 30.0
                                                        : 1.0f
                    : 1.0f;
            D_8010EFEC_picking_panic[i] = 1.0f / D_8010EEF4_picking_panic[i];
            D_8010EF8C_picking_panic[i] = 1.0f / D_8010EFC4_picking_panic[i];
            D_8010EFB4_picking_panic[i] = 0.5f;
            D_8010EFE4_picking_panic[i] = i * 0.5 + 0.25;
            D_8010EF9C_picking_panic[i] =
                (-D_8010EFB4_picking_panic[i] * D_8010EEF4_picking_panic[i] + 0.5) * 320.0 * 4.0;
            D_8010EFAC_picking_panic[i] =
                (-D_8010EFE4_picking_panic[i] * D_8010EFC4_picking_panic[i] + 0.25 + i * 0.5) * 240.0 * 4.0;
            D_8010EF78_picking_panic = 0.5f;
            scaleX[i] = D_8010EEF4_picking_panic[i];
            scaleY[i] = D_8010EFC4_picking_panic[i];
            offsetY[i] = D_8010EFE4_picking_panic[i];
        }
    }

    D_8010EF84_picking_panic[0] = D_8010EF84_picking_panic[1] = 0.0f;
    func_80107A48_picking_panic();
    ScissorSet(0, 0.0f, 0.0f, 320.0f,
               (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f);
    ScissorSet(1, 0.0f,
               (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f,
               320.0f, 240.0f);
    ViewportSet(0, scaleX[0] * 640.0f, scaleY[0] * 480.0f, 511.0f, 640.0f, offsetY[0] * 4.0f * 240.0f, 511.0f);
    ViewportSet(1, scaleX[1] * 640.0f, scaleY[1] * 480.0f, 511.0f, 640.0f, offsetY[1] * 4.0f * 240.0f, 511.0f);
}

void func_80107A48_picking_panic(void) {
    f32 progress[2];
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 scissorBottom;
    f32 scissorTop;
    f32 iconX;
    f32 iconY;
    f32 scale;
    s32 i;
    s32 j;
    s32 k;
    s32 view;
    s32 w;
    s32 h;
    s32 offset;

    scissorBottom =
        (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f;
    scissorTop =
        (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f;

    gSPDisplayList(gMainGfxPos++, D_8010E5E0_picking_panic);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 0; i < 2; i++) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[(i == 0) ? 0 : 1]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 3; k++) {
                w = (i == 1 && j == 3) ? 40 : 41;
                h = (k == 2) ? 40 : 41;
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 161 : 160, 0,
                                   j * 40, k * 40, j * 40 + w, k * 40 + h, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                for (view = 0; view < 2; view++) {
                    if (view == 0) {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, scissorBottom);
                    } else {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, scissorTop, 320, 240);
                    }
                    gSPScisTextureRectangle(gMainGfxPos++,
                                            (s32)(((j * 40 + i * 160) * 4) * D_8010EEF4_picking_panic[view] +
                                                  D_8010EF9C_picking_panic[view]),
                                            (s32)(((k * 40 + view * 120) * 4) * D_8010EFC4_picking_panic[view] +
                                                  D_8010EFAC_picking_panic[view]),
                                            (s32)(((j * 40 + i * 160 + w) * 4) * D_8010EEF4_picking_panic[view] +
                                                  D_8010EF9C_picking_panic[view]),
                                            (s32)(((k * 40 + view * 120 + h) * 4) * D_8010EFC4_picking_panic[view] +
                                                  D_8010EFAC_picking_panic[view]),
                                            G_TX_RENDERTILE, (j * 40) << 5, (k * 40) << 5,
                                            (s32)(D_8010EFEC_picking_panic[view] * 1024.0f),
                                            (s32)(D_8010EF8C_picking_panic[view] * 1024.0f));
                }
            }
        }
    }

    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);
    iconX = 51.0f;
    iconY = 64.0f;
    scale = 0.2875f;
    for (view = 0; view < 2; view++) {
        progress[view] = (D_8010EF10_picking_panic[view] < 26)   ? 0.0f
                         : (D_8010EF10_picking_panic[view] < 30) ? (D_8010EF10_picking_panic[view] - 26) / 4.0
                         : (D_8010EF10_picking_panic[view] < 37) ? 1.0f
                         : (D_8010EF10_picking_panic[view] < 45) ? (D_8010EF10_picking_panic[view] - 37) / 7.0
                                                                 : 0.0f;
        if (D_8010EF10_picking_panic[view] >= 37 && D_8010EF10_picking_panic[view] < 45) {
            progress[view] = (1.0f - progress[view] * progress[view]) * 0.75 + (1.0f - progress[view]) * 0.25;
        }
        if (D_8010EF10_picking_panic[view] == 26) {
            Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[10 + view], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionTimeSet(D_8010EEFC_picking_panic->model[10 + view], 0);
            Hu3DMotionAttrSet(D_8010EEFC_picking_panic->model[10 + view], 3, 0);
            func_8010B11C_picking_panic(D_8010EEFC_picking_panic->model[10 + view], 0);
        }
        if (D_8010EF10_picking_panic[view] == 27) {
            Hu3DModelAttrSet(
                *D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            Hu3DMotionTimeSet(*D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]],
                              0);
            Hu3DMotionAttrSet(*D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]],
                               1, 1);
        }
        if (D_8010EF10_picking_panic[view] >= 26 && D_8010EF10_picking_panic[view] < 31) {
            Hu3DModelPosSet(*D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]],
                            -855.0f, (1.0f - progress[view]) * 175.0f + -25.0f, 0.0f);
        }
        if (D_8010EF10_picking_panic[view] == 30) {
            Hu3DMotionTimeSet(*D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]],
                              0);
            Hu3DMotionAttrSet(*D_8010EF18_picking_panic[view][D_8010EEF0_picking_panic[view]][D_8010EF98_picking_panic[view]],
                               1, 0);
        }
        if (D_8010EF10_picking_panic[view] >= 10 && D_8010EF10_picking_panic[view] < 21) {
            D_8010EF84_picking_panic[view] = sindf((D_8010EF10_picking_panic[view] - 10) / 15.0 * 1440.0) * 0.625;
        }
    }

    if (progress[0] != 0.0f || progress[1] != 0.0f) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[4]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        for (k = 0; k < 4; k++) {
            gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 64, 0, 0, k * 24, 64,
                               k * 24 + 24 + (k < 3), 0, G_TX_NOMIRROR | G_TX_CLAMP,
                               G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            view = 0;
            do {
                if (progress[view] != 0.0f) {
                    if (view == 0) {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, scissorBottom);
                    } else {
                        gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, scissorTop, 320, 240);
                    }
                    gSPScisTextureRectangle(
                        gMainGfxPos++,
                        (s32)((iconX - scale * 32.0f) * 4.0 * D_8010EEF4_picking_panic[view] +
                              D_8010EF9C_picking_panic[view]),
                        (s32)((iconY + progress[view] * 21.0f - 48.0f + k * 24 * scale + view * 120) * 4.0 *
                                  D_8010EFC4_picking_panic[view] +
                              D_8010EFAC_picking_panic[view]),
                        (s32)((iconX + scale * 32.0f) * 4.0 * D_8010EEF4_picking_panic[view] +
                              D_8010EF9C_picking_panic[view]),
                        (s32)((iconY + progress[view] * 21.0f - 48.0f +
                               (k * 24 + 23 + ((k < 3) ? 2 : 0)) * scale + view * 120) *
                                  4.0 * D_8010EFC4_picking_panic[view] +
                              D_8010EFAC_picking_panic[view]),
                        G_TX_RENDERTILE, 0, (k * 24) << 5, (s32)(1024.0f / scale * D_8010EFEC_picking_panic[view]),
                        (s32)(1024.0f / scale * D_8010EF8C_picking_panic[view]));
                }
                view++;
            } while (view < 2);
        }
    }

    for (i = 0; i < 2; i++) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[(i == 0) ? 2 : 3]].unk04, 0);
        frame = &sprite->data->pat[sprite->patNo];
        if (i == 0) {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        }
        for (j = 0; j < 3; j++) {
            w = (i == 1 && j == 2) ? 32 : 39;
            if (i == 0) {
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, (i == 0) ? 115 : 108, 0,
                                   j * 38, 0, j * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_RGBA, G_IM_SIZ_16b, (i == 0) ? 115 : 108, 0,
                                   j * 38, 0, j * 38 + w, 48, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            }
            for (view = 0; view < 2; view++) {
                offset = 0;
                if (i == 0) {
                    offset = D_8010EF84_picking_panic[view] * 4.0;
                }
                if (view == 0) {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, scissorBottom);
                } else {
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, scissorTop, 320, 240);
                }
                gSPScisTextureRectangle(gMainGfxPos++,
                                        (s32)(((j * 38 + i * 212) * 4 + offset) * D_8010EEF4_picking_panic[view] +
                                              D_8010EF9C_picking_panic[view]),
                                        (s32)((view * 120 * 4) * D_8010EFC4_picking_panic[view] +
                                              D_8010EFAC_picking_panic[view]),
                                        (s32)(((j * 38 + i * 212 + w) * 4 + offset) * D_8010EEF4_picking_panic[view] +
                                              D_8010EF9C_picking_panic[view]),
                                        (s32)(((view * 120 + 48) * 4) * D_8010EFC4_picking_panic[view] +
                                              D_8010EFAC_picking_panic[view]),
                                        G_TX_RENDERTILE, (j * 38) << 5, 0,
                                        (s32)(D_8010EFEC_picking_panic[view] * 1024.0f),
                                        (s32)(D_8010EF8C_picking_panic[view] * 1024.0f));
            }
        }
        gDPSetTextureLUT(gMainGfxPos++, G_TT_NONE);
    }
}

void func_80109C00_picking_panic(Gfx **arg0, s32 arg1, s32 arg2) {
    s32 alpha = 255;
    s32 rects[2][7] = {
        { 23, 39, 25, 36, 20, 42, 1024 },
        { 129, 145, 131, 142, 126, 148, 1024 },
    };
    HuSprAnimPat *frame;
    HuSprite *sprite;
    f32 scissorBottom;
    f32 scissorTop;
    f32 divider;
    f32 t;
    s32 view;
    s32 cur;
    s32 other;
    s32 i;
    s32 size;

    scissorBottom =
        (D_8010EF78_picking_panic * 240.0f - 1.0f < 0.0f) ? 0.0f : D_8010EF78_picking_panic * 240.0f - 1.0f;
    scissorTop =
        (D_8010EF78_picking_panic * 240.0f + 1.0f > 240.0f) ? 240.0f : D_8010EF78_picking_panic * 240.0f + 1.0f;
    divider = D_8010EF78_picking_panic * 240.0f;

    D_8010E628_picking_panic = !D_8010E628_picking_panic;
    if (D_8010E628_picking_panic) {
        return;
    }

    if (D_8010EF14_picking_panic < 2 && D_8010EFA4_picking_panic < 255) {
        cur = D_8010EF14_picking_panic;
        other = 1 - cur;
        t = 1.0 - D_8010EFA4_picking_panic / 46.0;
        t = (t < 0.0f) ? 0.0f : (t > 1.0f) ? 1.0f
                                           : t;
        for (view = 0; view < 6; view++) {
            rects[cur][view] -= cur * t * 101.0f;
            rects[other][view] = rects[other][view] * (1.0f - t) + other * t * 240.0f;
        }
        rects[other][6] = (1.0f - t <= 0.0625) ? 0x3FFF : (s32)(1024.0f / (1.0f - t));
        alpha = (1.0f - t) * 255.0f;
    }

    gSPDisplayList(gMainGfxPos++, D_8010E5E0_picking_panic);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 0, 0, 218, alpha * 212 / 255);
    gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                      PRIMITIVE, 0);
    sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[9]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    for (view = 0; view < 2; view++) {
        if (view == 0) {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, scissorBottom);
        } else {
            gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, scissorTop, 320, 240);
        }
        gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_I, G_IM_SIZ_8b, 60, 0, 0, 0, 60, 22, 0,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);
        gSPScisTextureRectangle(gMainGfxPos++, 239 * 4, (rects[view][4] << 2), 299 * 4, (rects[view][5] << 2),
                                G_TX_RENDERTILE, 0, 0, 1024, rects[view][6]);
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetPrimColor(gMainGfxPos++, 0, 0, 255, 255, 255, alpha);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_NONE);
    gDPSetCombineLERP(gMainGfxPos++, 0, 0, 0, TEXEL0, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, TEXEL0, TEXEL0, 0,
                      PRIMITIVE, 0);
    gDPPipeSync(gMainGfxPos++);

    for (i = 0; i < 4; i++) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[(i == 0) ? 7 : (i == 1) ? 6
                                                                                           : 5]]
                              .unk04,
                          0);
        frame = &sprite->data->pat[sprite->patNo];
        if (i < 2) {
            gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
        } else {
            gDPLoadTLUT_pal256(gMainGfxPos++, sprite->data->pal);
        }
        for (view = 0; view < 2; view++) {
            if (view == 0) {
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, scissorBottom);
            } else {
                gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, scissorTop, 320, 240);
            }
            if (i == 3 && D_8010EF15_picking_panic[view] < 10) {
                continue;
            }
            if (i >= 2) {
                if (i == 2) {
                    if (D_8010EF15_picking_panic[view] < 10) {
                        size = D_8010EF15_picking_panic[view];
                    } else {
                        size = D_8010EF15_picking_panic[view] / 10;
                    }
                } else {
                    size = D_8010EF15_picking_panic[view] % 10;
                }
                frame = &sprite->data->pat[size];
            } else {
                size = (i == 0) ? 16 : 12;
            }
            if (i < 2) {
                gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, size, 0, 0, 0, size, size, 0,
                                      G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK,
                                      G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            } else {
                gDPLoadTextureTile(gMainGfxPos++, frame->data, G_IM_FMT_CI, G_IM_SIZ_8b, 12, 0, 0, 0, 12, 12, 0,
                                   G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                   G_TX_NOLOD, G_TX_NOLOD);
            }
            if (i == 0) {
                gSPScisTextureRectangle(gMainGfxPos++, (i * 12 + 243) * 4, (rects[view][0] << 2), (i * 12 + 258) * 4, (rects[view][1] << 2),
                                        G_TX_RENDERTILE, 0, 0, 1024, rects[view][6]);
            } else {
                gSPScisTextureRectangle(gMainGfxPos++, (i * 12 + 249) * 4, (rects[view][2] << 2), (i * 12 + 260) * 4,
                                        (rects[view][3] << 2), G_TX_RENDERTILE, 0, 0, 1024, rects[view][6]);
            }
        }
    }

    gDPPipeSync(gMainGfxPos++);
    gDPSetRenderMode(gMainGfxPos++, G_RM_AA_TEX_EDGE, G_RM_AA_TEX_EDGE2);
    gDPSetAlphaCompare(gMainGfxPos++, G_AC_THRESHOLD);
    gDPSetBlendColor(gMainGfxPos++, 0x00, 0x00, 0x00, 0xD0);
    gDPSetCombineMode(gMainGfxPos++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    sprite = HuSprGet(D_800CD1DC_main[D_8010EFD0_picking_panic[8]].unk04, 0);
    frame = &sprite->data->pat[sprite->patNo];
    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, 0, 0, 320, 240);
    gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->data->pal);
    gDPPipeSync(gMainGfxPos++);
    gDPLoadTextureTile_4b(gMainGfxPos++, frame->data, G_IM_FMT_CI, 320, 0, 0, 0, 320, 6, 0,
                          G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                          G_TX_NOLOD, G_TX_NOLOD);
    if (D_8010EF78_picking_panic > 0.0f) {
        gSPScisTextureRectangle(gMainGfxPos++, 0, (s32)(divider - 3.0f) * 4, 320 * 4, (s32)(divider + 3.0f) * 4,
                                G_TX_RENDERTILE, 0, 0, 1024, 1024);
    }
    gDPPipeSync(gMainGfxPos++);
    gDPSetBlendColor(gMainGfxPos++, 0xFF, 0xFF, 0xFF, 0x00);
    gDPPipeSync(gMainGfxPos++);
}

void func_8010B11C_picking_panic(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &Hu3DData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}

void func_8010B160_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 0);
    object->func = func_8010B8D0_picking_panic;
}

void func_8010B194_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 1);
    object->func = NULL;
}

void func_8010B1C0_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 2);
    object->func = func_8010B8EC_picking_panic;
}

void func_8010B1F4_picking_panic(omObjData *object) {
    func_8010B220_picking_panic(object, 3);
    object->func = NULL;
}

void func_8010B220_picking_panic(omObjData *object, s8 arg1) {
    s32 files[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 models[8] = { 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 3 };
    s32 linkModels[8] = { 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 1 };
    s32 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 anims[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    PickingPanicPlayer *player;
    u16 chr;
    u16 i;
    u16 j;
    s16 *model;

    chr = D_8010EEE0_picking_panic[arg1]->unk3;
    object->model[0] = Hu3DModelRead((files[chr] << 16) | models[chr], 0x4B9);
    omSetSca(object, 1.3f, 1.3f, 1.3f);
    Hu3DModelObjAttrSet(object->model[0], 0x600, 0x400);
    Hu3DModelCameraSet(object->model[0], (arg1 >= 2) ? HU3D_CAM1 : HU3D_CAM0);
    object->model[1] = Hu3DModelRead((files[chr] << 16) | linkModels[chr], 0x4AD);
    Hu3DModelScaleSet(object->model[1], 1.3f, 1.3f, 1.3f);
    Hu3DModelObjAttrSet(object->model[1], 0x600, 0x400);
    Hu3DModelCameraSet(object->model[1], (arg1 >= 2) ? HU3D_CAM1 : HU3D_CAM0);
    D_8010EEE0_picking_panic[arg1]->unk6 =
        CharAnimCreate(object->model[1], 1, motions[chr], (files[chr] << 16) | anims[0][chr]);
    D_8010EEE0_picking_panic[arg1]->unk8 = Hu3DAnimDataRead((files[chr] << 16) | anims[1][chr]);
    Hu3DModelDynamicFree(object->model[1]);
    player = D_8010EEE0_picking_panic[arg1];
    player->unkC = (rand8() & 1) ? 0x2F : 0x30;
    omObjMotionRead(object, 0, CharMotionDataNumGet(chr, 0));
    omObjMotionRead(object, 1, CharMotionDataNumGet(chr, 0x49));
    omObjMotionRead(object, 2, CharMotionDataNumGet(chr, 0x4A));
    omObjMotionRead(object, 3, CharMotionDataNumGet(chr, 0x1F));
    omObjMotionRead(object, 4, CharMotionDataNumGet(chr, D_8010EEE0_picking_panic[arg1]->unkC));
    D_8010EEE0_picking_panic[arg1]->unkC |= files[chr] << 16;
    Hu3DMotionModelSet(object->model[0], object->motion[1]);
    Hu3DMotionTimeSet(object->model[0], 12.0f);
    Hu3DMotionAttrSet(object->model[0], 1, 1);
    Hu3DMotionModelSet(object->model[1], object->motion[1]);
    Hu3DMotionTimeSet(object->model[1], 12.0f);
    Hu3DMotionAttrSet(object->model[1], 1, 1);

    if (arg1 % 2 == 1) {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 4; j++) {
                model = D_8010EF18_picking_panic[arg1 / 2][j][i] =
                    &D_8010EF00_picking_panic[(arg1 & 2) + (j % 2)]->model[i + ((j / 2 == 0) ? 2 : 5)];
                if (arg1 / 2 == 0 && j == 0) {
                    s32 fileIds[3] = { 2, 3, 4 };

                    *model = Hu3DModelRead(fileIds[i] | 0x300000, 0x8BD);
                } else {
                    *model = Hu3DModelLink(D_8010EF00_picking_panic[0]->model[2 + i]);
                }
                Hu3DModelCameraSet(*model, (arg1 >= 2) ? HU3D_CAM1 : HU3D_CAM0);
                Hu3DModelObjAttrSet(*model, 0x20000000, 0x20000000);
                Hu3DModelAttrSet(*model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(*model, 1.3f, 1.3f, 1.3f);
            }
        }
    }
    D_8010EFBE_picking_panic = 0;
}

void func_8010B8D0_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 0);
}

void func_8010B8EC_picking_panic(omObjData *object) {
    func_8010B908_picking_panic(object, 1);
}

void func_8010B908_picking_panic(omObjData *object, s8 arg1) {
    PickingPanicPlayer *player0 = D_8010EEE0_picking_panic[arg1 * 2];
    PickingPanicPlayer *player1 = D_8010EEE0_picking_panic[arg1 * 2 + 1];
    omObjData *hand0 = D_8010EF00_picking_panic[arg1 * 2];
    omObjData *hand1 = D_8010EF00_picking_panic[arg1 * 2 + 1];
    u8 idx0 = arg1 * 2;
    u8 idx1 = arg1 * 2 + 1;
    u8 cpuTbl[4][8] = {
        { 0xA0, 0x60, 0x20, 0x08, 0x80, 0x60, 0x40, 0x0A },
        { 0x09, 0x05, 0x03, 0x02, 0x07, 0x05, 0x03, 0x02 },
        { 0x10, 0x40, 0x80, 0xC0, 0x40, 0x80, 0xC0, 0xE0 },
        { 0xC0, 0x40, 0x20, 0x04, 0x80, 0x40, 0x20, 0x01 },
    };
    s32 i;
    s32 j;
    s32 k;
    s32 slot;
    s32 type;
    s16 model;
    f32 x;
    f32 y;
    f32 rot;
    f32 dir;
    f32 base;
    f32 c;
    f32 s;
    f32 t;
    f32 power;
    f32 u;
    f32 prevY;
    f32 wallX;
    f32 dist;
    f32 dist2;
    f32 ofs;
    f32 ofs2;
    f32 angle;
    f32 speed;
    f32 amp;
    f32 sumX;
    f32 sumY;
    f32 itemX;
    f32 itemY;

    if (arg1 == 0 && D_8010E6EC_picking_panic == 45) {
        for (j = 1; j < 6; j++) {
            D_8010E718_picking_panic[j] = rand8() / 110;
        }
    }
    if (arg1 == 0) {
        D_8010EF94_picking_panic -= (D_8010EF94_picking_panic > 0.0f) ? 1.0f : 0.0f;
    }
    if (arg1 == 0 && D_8010EF94_picking_panic == 0.0f && D_8010EF80_picking_panic == 2 &&
        D_8010E6EC_picking_panic % 60 == 46) {
        D_8010EF94_picking_panic = 60.0f;
    }
    if (arg1 == 0) {
        i = D_8010E6EC_picking_panic % 30;
        i = (i < 16) ? i : 30 - i;
        if (D_8010E62C_picking_panic[0][i] == 0.0f) {
            sumY = 0.0f;
            sumX = 0.0f;
            amp = sindf(i * 90.0 / 15.0) * 80.0f;
            for (j = 0; j < 3; j++) {
                D_8010E62C_picking_panic[j][i] = amp * ((j * 0.125) / 3.0 + 0.875) + 270.0;
                sumX += cosdf(D_8010E62C_picking_panic[j][i]) * 110.0f;
                sumY += sindf(D_8010E62C_picking_panic[j][i]) * 110.0f;
                D_8010EC20_picking_panic[j][i] = sumX;
                D_8010ECE0_picking_panic[j][i] = sumY;
            }
        }
        for (j = 0; j < 2; j++) {
            u32 frame;

            dir = (D_8010E6EC_picking_panic % 60 < 30) ? 1.0f : -1.0f;
            base = (j == 0) ? -500.0f : 500.0f;
            frame = D_8010E6EC_picking_panic % 30;
            frame = (frame < 16) ? frame : 30 - frame;
            if (j != 0) {
                dir = -dir;
            }
            for (i = 0; i < 3; i++) {
                Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(j == 0) ? i + 32 : i + 35],
                                base + dir * D_8010EC20_picking_panic[i][frame],
                                D_8010ECE0_picking_panic[i][frame] + 250.0f, 0.0f);
                Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(j == 0) ? i + 32 : i + 35], 0.0f, 0.0f,
                                (D_8010E62C_picking_panic[i][frame] - 270.0f) * dir);
            }
            x = base + dir * D_8010EC20_picking_panic[2][frame];
            y = D_8010ECE0_picking_panic[2][frame] + 250.0f;
            rot = (D_8010E62C_picking_panic[2][frame] - 270.0f) * dir;
            Hu3DModelPosSet(D_8010EEFC_picking_panic->model[(j == 0) ? 8 : 9], x, y, 0.0f);
            Hu3DModelRotSet(D_8010EEFC_picking_panic->model[(j == 0) ? 8 : 9], 0.0f, 0.0f, rot);
            rot += (j == 0) ? 35.0f : -35.0f;
            if (D_8010EF80_picking_panic == 0 && D_8010EFA8_picking_panic < 45) {
                f32 swing = (D_8010EFA8_picking_panic < 30) ? 180.0f : 180.0 - (D_8010EFA8_picking_panic + 30) * 180.0 / 15.0;

                if (j == 0) {
                    rot -= swing;
                } else {
                    rot += swing;
                }
            }
            c = cosdf(rot + 270.0f + ((j == 0) ? -14.0f : 14.0f));
            s = sindf(rot + 270.0f + ((j == 0) ? -14.0f : 14.0f));
            if (!(j & 1)) {
                D_8010EE80_picking_panic = -D_8010EE70_picking_panic;
                D_8010EE84_picking_panic = -D_8010EE74_picking_panic;
                D_8010EE70_picking_panic = x + c * 86.0f;
                D_8010EE74_picking_panic = y + s * 86.0f;
                D_8010EE80_picking_panic += D_8010EE70_picking_panic;
                D_8010EE84_picking_panic += D_8010EE74_picking_panic;
            } else {
                D_8010EE78_picking_panic = x + c * 86.0f;
                D_8010EE7C_picking_panic = y + s * 86.0f;
            }
            x -= c * 86.0f;
            y -= s * 86.0f;
            omSetTra(D_8010EF00_picking_panic[j], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[j], 0.0f, (j == 0) ? -90.0f : 90.0f, rot + 180.0f);
            omSetTra(D_8010EF00_picking_panic[j + 2], x, y, 0.0f);
            omSetRot(D_8010EF00_picking_panic[j + 2], 0.0f, (j == 0) ? -90.0f : 90.0f, rot + 180.0f);
            if (D_8010EF80_picking_panic >= 3 && D_8010EF14_picking_panic < 2) {
                s32 flyFrames = 16;
                s32 throwFrame = 7;
                s32 velX = 13;
                s32 velY = 36;

                i = D_8010EF14_picking_panic * 2;
                if (j == 0 && D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    D_8010EE88_picking_panic += D_8010EE94_picking_panic;
                    D_8010EE8C_picking_panic += D_8010EE98_picking_panic;
                    D_8010EE98_picking_panic -= 6.25;
                }
                if (D_8010EFA4_picking_panic == 255 && D_8010E6EC_picking_panic % 60 == throwFrame) {
                    D_8010EFA4_picking_panic = flyFrames + 30;
                    D_8010EE88_picking_panic = x;
                    D_8010EE94_picking_panic = velX;
                    D_8010EE8C_picking_panic = y;
                    D_8010EE98_picking_panic = velY;
                    D_8010EE90_picking_panic = rot;
                    for (k = 0; k < 2; k++) {
                        Hu3DModelAttrSet(D_8010EF00_picking_panic[i + k]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(D_8010EF00_picking_panic[i + k]->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DMotionShiftSet(D_8010EF00_picking_panic[i + k]->model[1],
                                           Hu3DData[D_8010EF00_picking_panic[i + k]->motion[2]].motId, 50,
                                           flyFrames, 0);
                    }
                }
                if (D_8010EFA4_picking_panic > 30 && D_8010EFA4_picking_panic < 255) {
                    t = (f32)(D_8010EFA4_picking_panic - 30) / flyFrames;
                    u = t * t * 0.5 + t * 0.5;
                    Hu3DModelPosSet(D_8010EF00_picking_panic[i + j]->model[1],
                                    (j != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[i + j]->model[1], 0.0f,
                                    (t * 45.0f + 45.0f) * ((j != 0) ? 1.0f : -1.0f),
                                    (u * D_8010EE90_picking_panic + (1.0f - u) * 180.0f) * ((j != 0) ? -1.0f : 1.0f) +
                                        180.0f);
                }
                if (D_8010EFA4_picking_panic < 31) {
                    t = (D_8010EFA4_picking_panic - 1) / 10.0;
                    t = (t > 1.0f) ? 45.0f : (t < 0.0f) ? 0.0f
                                                        : t * 45.0f;
                    Hu3DModelPosSet(D_8010EF00_picking_panic[i + j]->model[1],
                                    (j != 0) ? -D_8010EE88_picking_panic : D_8010EE88_picking_panic,
                                    D_8010EE8C_picking_panic, 50.0f);
                    Hu3DModelRotSet(D_8010EF00_picking_panic[i + j]->model[1], 0.0f, (j == 0) ? -t : t,
                                    (j == 0) ? 360.0f : 0.0f);
                }
                if (D_8010EFA4_picking_panic == 30) {
                    HuAudPlayerFXPlay(D_8010EEE0_picking_panic[i + j]->unk3 + 50,
                                       D_8010EEE0_picking_panic[i + j]->unk0);
                    Hu3DMotionModelSet(D_8010EF00_picking_panic[i + j]->model[1],
                                       D_8010EF00_picking_panic[i + j]->motion[3]);
                    Hu3DMotionTimeSet(D_8010EF00_picking_panic[i + j]->model[1], 2.0f);
                    Hu3DMotionAttrSet(D_8010EF00_picking_panic[i + j]->model[1], 3, 0);
                }
                if (D_8010EFA4_picking_panic == 26) {
                    Hu3DMotionShiftSet(D_8010EF00_picking_panic[i + j]->model[1],
                                       Hu3DData[D_8010EF00_picking_panic[i + j]->motion[0]].motId, 0, 20, 2);
                }
                if (j == 1 && D_8010EFA4_picking_panic < 255) {
                    if (D_8010EFA4_picking_panic == 1) {
                        for (k = 0; k < 3; k++) {
                            Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[k + 32], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[k + 35], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[8], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[9], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    D_8010EFA4_picking_panic -= (D_8010EFA4_picking_panic != 0);
                }
            }
        }
    }

    if (Hu3DData[D_8010EEFC_picking_panic->model[arg1 + 10]].motTime >= 60.0f) {
        Hu3DData[D_8010EEFC_picking_panic->model[arg1 + 10]].motTime = 0.0f;
        Hu3DModelAttrSet(D_8010EEFC_picking_panic->model[arg1 + 10], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
    D_8010EF10_picking_panic[arg1] =
        (D_8010EF10_picking_panic[arg1] < 46) ? D_8010EF10_picking_panic[arg1] + (D_8010EF10_picking_panic[arg1] != 0) : 0;
    if (D_8010EF80_picking_panic == 0 || (D_8010EF80_picking_panic == 1 && D_8010EFA8_picking_panic < 45)) {
        D_8010EF10_picking_panic[arg1] = 1;
    }
    if (D_8010EF10_picking_panic[arg1] == 15) {
        if (D_8010E6F0_picking_panic[arg1][(D_8010EEF0_picking_panic[arg1] + 1) % 4] == 0) {
            D_8010EEF0_picking_panic[arg1] = (D_8010EEF0_picking_panic[arg1] + 1) % 4;
            D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] = 1;
            D_8010EF98_picking_panic[arg1] =
                (D_8010E714_picking_panic[arg1] < 6)
                    ? D_8010E718_picking_panic[D_8010E714_picking_panic[arg1]]
                    : (u32)(rand8() % ((D_8010EF15_picking_panic[arg1] >= 4 &&
                                        D_8010EF15_picking_panic[arg1] - D_8010EF15_picking_panic[1 - arg1] >= 4) +
                                       5)) /
                          2;
            if (D_8010EF98_picking_panic[arg1] == 2 && D_8010EF15_picking_panic[arg1] == 0 &&
                D_8010E5B0_picking_panic.timer < 451) {
                D_8010EF98_picking_panic[arg1] = 0;
            }
            D_8010E714_picking_panic[arg1] += (D_8010E714_picking_panic[arg1] < 6);
        } else {
            D_8010EF10_picking_panic[arg1]--;
        }
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk0 -= (D_8010E704_picking_panic[arg1].unk0 > 0);
    }
    if (D_8010E6EC_picking_panic % 60 == 0) {
        D_8010E704_picking_panic[arg1].unk6 -= (D_8010E704_picking_panic[arg1].unk6 > 0);
    }

    if (D_8010EF80_picking_panic == 2) {
        if (D_8010E700_picking_panic[idx0] == -1 &&
            D_8010E6F0_picking_panic[arg1][D_8010EEF0_picking_panic[arg1]] == 1 &&
            D_8010EF98_picking_panic[arg1] != -1 &&
            (D_8010EF10_picking_panic[arg1] == 0 || D_8010EF10_picking_panic[arg1] >= 30) &&
            ((player0->unk4 == -1 && (D_800D5558_main[player0->unk2] & A_BUTTON)) ||
             (player0->unk4 != -1 && D_8010E704_picking_panic[arg1].unk0 == 0))) {
            f32 dx = D_8010EE70_picking_panic - -855.0f;
            f32 dy = D_8010EE74_picking_panic - -25.0f;
            if (dx * dx + dy * dy < 133.9 * 133.9) {
                slot = D_8010EEF0_picking_panic[arg1];
                D_8010E700_picking_panic[idx0] = slot;
                D_8010E6F0_picking_panic[arg1][slot] = 2;
                D_8010EDA0_picking_panic[arg1][slot] = D_8010EF98_picking_panic[arg1];
                D_8010EF98_picking_panic[arg1] = -1;
                D_8010EF10_picking_panic[arg1] = 1;
                D_8010E6F8_picking_panic[idx0] = 6;
                D_8010E6FC_picking_panic[idx0] = 23;
                Hu3DModelHookSet(*D_8010EF18_picking_panic[arg1][slot][D_8010EDA0_picking_panic[arg1][slot]],
                                 hand0->model[0], "item_hook");
                Hu3DModelAttrSet(*D_8010EF18_picking_panic[arg1][slot][D_8010EDA0_picking_panic[arg1][slot]],
                                   0x4000, 0x4000);
                if (player0->unk4 != -1) {
                    D_8010E704_picking_panic[arg1].unk0 = (cpuTbl[0][player0->unk4] > rand8()) ? 2 : 1;
                    D_8010E704_picking_panic[arg1].unk2 =
                        rand8() % (cpuTbl[1][player0->unk4] * 2) - cpuTbl[1][player0->unk4];
                }
                if (player1->unk4 != -1) {
                    D_8010E704_picking_panic[arg1].unk4 = cpuTbl[2][player1->unk4];
                }
                HuAudPlayerFXPlay((D_8010EDA0_picking_panic[arg1][slot] == 0)   ? 0x36F
                                   : (D_8010EDA0_picking_panic[arg1][slot] == 1) ? 0x36C
                                                                                 : 0x370,
                                   arg1 * 2);
                omVibrate(player0->unk0, 2, 3, 10);
            }
        }
    }
    if (D_8010EF80_picking_panic == 2 && D_8010E700_picking_panic[idx1] == -1 &&
        ((player1->unk4 == -1 && (D_800D5558_main[player1->unk2] & A_BUTTON)) ||
         (player1->unk4 != -1 && D_8010E704_picking_panic[arg1].unk4 > rand8()))) {
        for (i = 0; i < 4; i++) {
            if (D_8010E6F0_picking_panic[arg1][i] == 3) {
                f32 dx = D_8010EE78_picking_panic - D_8010EDB0_picking_panic[arg1][i];
                f32 dy = D_8010EE7C_picking_panic - D_8010EDD0_picking_panic[arg1][i];
                if (dx * dx + dy * dy < 130.0 * 130.0) {
                    D_8010E700_picking_panic[idx1] = i;
                    D_8010E6F0_picking_panic[arg1][i] = 4;
                    D_8010E6F8_picking_panic[idx1] = 6;
                    D_8010E6FC_picking_panic[idx1] = 23;
                    type = D_8010EDA0_picking_panic[arg1][i];
                    Hu3DModelPosSet((!(i & 1) ? hand0 : hand1)->model[(i / 2 == 0) ? type + 2 : type + 5], 0.0f, 0.0f,
                                    0.0f);
                    Hu3DModelHookSet(*D_8010EF18_picking_panic[arg1][i][D_8010EDA0_picking_panic[arg1][i]],
                                     hand1->model[0], "item_hook");
                    Hu3DModelAttrSet(*D_8010EF18_picking_panic[arg1][i][D_8010EDA0_picking_panic[arg1][i]],
                                       0x4000, 0x4000);
                    if (player1->unk4 != -1) {
                        D_8010E704_picking_panic[arg1].unk6 = cpuTbl[3][player1->unk4] > rand8();
                    }
                    HuAudPlayerFXPlay((D_8010EDA0_picking_panic[arg1][i] == 0)   ? 0x36F
                                       : (D_8010EDA0_picking_panic[arg1][i] == 1) ? 0x36C
                                                                                  : 0x370,
                                       arg1 * 2 + 1);
                    omVibrate(player1->unk0, 2, 3, 10);
                    break;
                }
            }
        }
    }

    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[idx0] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[idx0]] == 2 &&
        (D_8010EF80_picking_panic != 2 ||
         ((player0->unk4 == -1) ? !((u16)D_800CDA7C_main[player0->unk2] & A_BUTTON)
                                : D_8010E6EC_picking_panic % 60 == (D_8010E704_picking_panic[arg1].unk2 + 68) % 60))) {
        if (hand0->rot.z > 210.0f) {
            power = 0.0f;
        } else if (hand0->rot.z > 160.0f) {
            power = 1.0f;
        } else {
            power = (210.0f - hand0->rot.z) / 50.0f;
        }
        slot = D_8010E700_picking_panic[idx0];
        D_8010E700_picking_panic[idx0] = -1;
        D_8010E6F0_picking_panic[arg1][slot] = 3;
        D_8010EDB0_picking_panic[arg1][slot] = D_8010EE70_picking_panic;
        D_8010EDD0_picking_panic[arg1][slot] = D_8010EE74_picking_panic;
        D_8010EDF0_picking_panic[arg1][slot] = 0.0f;
        D_8010EE50_picking_panic[arg1][slot] = 0.0f;
        if (D_8010EF80_picking_panic == 2) {
            D_8010EE10_picking_panic[arg1][slot] =
                ((D_8010EE80_picking_panic * 0.875 - 5.0) * power + (1.0f - power) * 24.25) *
                (D_8010EDA0_picking_panic[arg1][slot] * 0.15 + 0.85);
            D_8010EE30_picking_panic[arg1][slot] =
                ((D_8010EE84_picking_panic * 0.875 + 10.0) * power + (1.0f - power) * 57.5) *
                (D_8010EDA0_picking_panic[arg1][slot] * 0.15 + 0.85);
        } else {
            D_8010EE10_picking_panic[arg1][slot] = D_8010EE30_picking_panic[arg1][slot] = 0.0f;
        }
        Hu3DModelAttrSet(*D_8010EF18_picking_panic[arg1][slot][D_8010EDA0_picking_panic[arg1][slot]], 0x4000, 0);
        D_8010E6F8_picking_panic[idx0] = 18;
        D_8010E6FC_picking_panic[idx0] = 0;
        HuAudPlayerFXPlay(0x36D, arg1 * 2);
    }
    if (D_8010EF80_picking_panic >= 2 && D_8010E700_picking_panic[idx1] != -1 &&
        D_8010E6F0_picking_panic[arg1][D_8010E700_picking_panic[idx1]] == 4 &&
        (D_8010EF80_picking_panic != 2 ||
         ((player1->unk4 == -1) ? !((u16)D_800CDA7C_main[player1->unk2] & A_BUTTON)
                                : (D_8010E704_picking_panic[arg1].unk6 == 0 &&
                                   ((D_8010E6EC_picking_panic % 60 >= 43 && D_8010E6EC_picking_panic % 60 < 48 && rand8() % 3 == 0) ||
                                    D_8010E6EC_picking_panic % 60 == 48))))) {
        f32 throwVel[11] = { 30.0f, 30.0f, 26.0f, 25.0f, 24.0f, 26.0f, 23.0f, 23.0f, 25.5f, 26.0f, 30.0f };

        j = D_8010E6EC_picking_panic % 30;
        j = (j < 16) ? j : 30 - j;
        j = (D_8010E6EC_picking_panic + 15) % 60;
        j = (j - 30 > 0) ? 60 - j : j;
        slot = D_8010E700_picking_panic[idx1];
        D_8010E700_picking_panic[idx1] = -1;
        D_8010E6F0_picking_panic[arg1][slot] = 5;
        D_8010EDB0_picking_panic[arg1][slot] = D_8010EE78_picking_panic;
        D_8010EDD0_picking_panic[arg1][slot] = D_8010EE7C_picking_panic;
        D_8010EDF0_picking_panic[arg1][slot] = 0.0f;
        D_8010EDA8_picking_panic[arg1][slot] = 0;
        D_8010EE50_picking_panic[arg1][slot] = 0.0f;
        D_8010EE10_picking_panic[arg1][slot] =
            ((j >= 7 && j < 18) ? throwVel[j - 7] : 23.0) *
            ((j < 5) ? 0.0 : (j < 14) ? (j - 5) / 9.0
                         : (j < 22)   ? 1.0 - (j - 14) / 8.0
                                      : 0.0);
        D_8010EE30_picking_panic[arg1][slot] =
            ((j < 5) ? 0.0 : (j < 14) ? (j - 5) / 9.0
                         : (j < 22)   ? 1.0 - (j - 14) / 8.0
                                      : 0.0) *
            60.0;
        Hu3DModelAttrSet(*D_8010EF18_picking_panic[arg1][slot][D_8010EDA0_picking_panic[arg1][slot]], 0x4000, 0);
        D_8010E6F8_picking_panic[idx1] = 18;
        D_8010E6FC_picking_panic[idx1] = 0;
        HuAudPlayerFXPlay(0x36D, arg1 * 2 + 1);
    }

    for (j = 0; j < 2; j++) {
        i = arg1 * 2 + j;
        if (D_8010E6F8_picking_panic[i] < D_8010E6FC_picking_panic[i]) {
            if (D_8010E6F8_picking_panic[i] + 2 <= D_8010E6FC_picking_panic[i]) {
                D_8010E6F8_picking_panic[i] += 2;
            } else {
                D_8010E6F8_picking_panic[i] = D_8010E6FC_picking_panic[i];
            }
        } else if (D_8010E6FC_picking_panic[i] < D_8010E6F8_picking_panic[i]) {
            if (D_8010E6F8_picking_panic[i] - 2 >= D_8010E6FC_picking_panic[i]) {
                D_8010E6F8_picking_panic[i] -= 2;
            } else {
                D_8010E6F8_picking_panic[i] = D_8010E6FC_picking_panic[i];
            }
        }
        Hu3DMotionTimeSet(D_8010EF00_picking_panic[i]->model[0], D_8010E6F8_picking_panic[i]);
    }

    for (i = 0; i < 4; i++) {
        prevY = D_8010EDD0_picking_panic[arg1][i];
        switch (D_8010E6F0_picking_panic[arg1][i]) {
            case 3:
            case 5:
                type = D_8010EDA0_picking_panic[arg1][i];
                j = 2;
                model = (!(i & 1) ? hand0 : hand1)->model[(i / 2 == 0) ? type + 2 : type + 5];
                D_8010EE30_picking_panic[arg1][i] -= 6.25;
                if (D_8010E6F0_picking_panic[arg1][i] == 5) {
                    itemX = D_8010EDB0_picking_panic[arg1][i] + D_8010EE10_picking_panic[arg1][i];
                    itemY = D_8010EDD0_picking_panic[arg1][i] + D_8010EE30_picking_panic[arg1][i];
                    for (j = 0; j < 2; j++) {
                        wallX = (j == 0) ? 827.0f : 953.0f;
                        if (itemY - 47.5 < -152.0 && itemY + 47.5 > -292.0 && itemX - 47.5 < wallX && wallX < itemX + 47.5) {
                            dist = 2256.25 - (wallX - itemX) * (wallX - itemX);
                            ofs = (dist <= 0.0f) ? 0.0f : HuSqrtf(dist);
                            if (itemY - ofs < -152.0f && itemY + ofs > -292.0f) {
                                dist2 = 2256.25 - (wallX - D_8010EDB0_picking_panic[arg1][i]) *
                                                      (wallX - D_8010EDB0_picking_panic[arg1][i]);
                                ofs2 = (dist2 <= 0.0f) ? 0.0f : HuSqrtf(dist2);
                                if (dist2 > 0.0f && D_8010EDD0_picking_panic[arg1][i] - ofs2 < -152.0f &&
                                    ofs2 + D_8010EDD0_picking_panic[arg1][i] > -292.0f) {
                                    D_8010EDB0_picking_panic[arg1][i] = (j == 0) ? wallX + 47.5 : wallX - 47.5;
                                    D_8010EE10_picking_panic[arg1][i] = 0.0f;
                                    D_8010EDD0_picking_panic[arg1][i] += D_8010EE30_picking_panic[arg1][i];
                                } else {
                                    angle = atan2df(ofs, itemX - wallX);
                                    speed = HuSqrtf(D_8010EE10_picking_panic[arg1][i] * D_8010EE10_picking_panic[arg1][i] +
                                                    D_8010EE30_picking_panic[arg1][i] * D_8010EE30_picking_panic[arg1][i]) *
                                            0.25;
                                    angle = (angle < 0.0f) ? angle + 90.0f : angle + 0.0f;
                                    angle = angle * 2.0f - 90.0f;
                                    if (D_8010EDA8_picking_panic[arg1][i] == 1 || speed < 7.0f ||
                                        (angle > 180.0f && ((j == 0) ? itemX < wallX : wallX < itemX))) {
                                        D_8010EDB0_picking_panic[arg1][i] = (j == 0) ? wallX + 47.5 : wallX - 47.5;
                                        D_8010EE10_picking_panic[arg1][i] = 0.0f;
                                        D_8010EDD0_picking_panic[arg1][i] += D_8010EE30_picking_panic[arg1][i];
                                    } else {
                                        D_8010EDD0_picking_panic[arg1][i] =
                                            (D_8010EDD0_picking_panic[arg1][i] >= -222.0f) ? -104.5f : -339.5f;
                                        D_8010EE10_picking_panic[arg1][i] = cosdf(angle) * speed;
                                        D_8010EE30_picking_panic[arg1][i] = sindf(angle) * speed;
                                        D_8010EDB0_picking_panic[arg1][i] += D_8010EE10_picking_panic[arg1][i];
                                        D_8010EDD0_picking_panic[arg1][i] += D_8010EE30_picking_panic[arg1][i];
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
                if (j == 2) {
                    D_8010EDB0_picking_panic[arg1][i] += D_8010EE10_picking_panic[arg1][i];
                    D_8010EDD0_picking_panic[arg1][i] += D_8010EE30_picking_panic[arg1][i];
                    D_8010EDA8_picking_panic[arg1][i] = 0;
                }
                D_8010EDF0_picking_panic[arg1][i] += D_8010EE50_picking_panic[arg1][i];
                if (D_8010E6F0_picking_panic[arg1][i] == 5 && D_8010EDB0_picking_panic[arg1][i] - 47.5 >= 827.0 &&
                    D_8010EDB0_picking_panic[arg1][i] + 47.5 <= 953.0 && D_8010EDD0_picking_panic[arg1][i] - 47.5 <= -257.0 &&
                    prevY - 47.5 > -257.0) {
                    if (D_8010EF80_picking_panic < 3) {
                        D_8010EF15_picking_panic[arg1] += 3 - D_8010EDA0_picking_panic[arg1][i];
                        D_8010EF15_picking_panic[arg1] = (D_8010EF15_picking_panic[arg1] >= 100) ? 99 : D_8010EF15_picking_panic[arg1];
                        omVibrate(player0->unk0, 5, 0, 5);
                        omVibrate(player1->unk0, 5, 0, 5);
                        // Duplicated in both branches (merged by cross-jumping) for register allocation.
                        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    }
                    Hu3DMotionTimeSet(D_8010EEFC_picking_panic->model[arg1 + 2], 0.0f);
                    Hu3DMotionAttrSet(D_8010EEFC_picking_panic->model[arg1 + 2], 1, 0);
                    Hu3DMotionTimeSet(D_8010EEFC_picking_panic->model[arg1], 0.0f);
                    Hu3DMotionAttrSet(D_8010EEFC_picking_panic->model[arg1], 1, 0);
                    HuAudPlayerFXPlay(0x36E, arg1);
                    D_8010E6F0_picking_panic[arg1][i] = 0;
                } else if (D_8010EDD0_picking_panic[arg1][i] < -500.0f) {
                    // do-while(0) gives loop weighting to `model` for register allocation.
                    do {
                        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    } while (0);
                    D_8010E6F0_picking_panic[arg1][i] = 0;
                } else {
                    Hu3DModelPosSet(*D_8010EF18_picking_panic[arg1][i][D_8010EDA0_picking_panic[arg1][i]],
                                    D_8010EDB0_picking_panic[arg1][i], D_8010EDD0_picking_panic[arg1][i], 0.0f);
                    Hu3DModelRotSet(*D_8010EF18_picking_panic[arg1][i][D_8010EDA0_picking_panic[arg1][i]], 0.0f, 0.0f,
                                    D_8010EDF0_picking_panic[arg1][i]);
                }
                break;
        }
    }
    if (arg1 == 1 && (D_8010EF80_picking_panic != 0 || D_8010EFA8_picking_panic >= 7)) {
        D_8010E6EC_picking_panic++;
    }
}
