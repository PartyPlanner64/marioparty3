#include "common.h"
#include "game/pause.h"
#include "game/mallocblock.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/hmfmath.h"

// Per-object work block, reached via ObjData->data
typedef struct ChipShotChallengeWork {
    /* 0x00 */ char pad_00[0x34];
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ char pad_4C[4];
    /* 0x50 */ s16 unk_50;
    /* 0x52 */ s8 unk_52;
    /* 0x53 */ s8 unk_53;
    /* 0x54 */ s8 unk_54;
    /* 0x55 */ char pad_55[4];
    /* 0x59 */ s8 playerIndex;
    /* 0x5A */ char pad_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ char pad_68[0xC];
    /* 0x74 */ f32 unk_74;
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ s32 unk_7C;
    /* 0x80 */ char pad_80[4];
    /* 0x84 */ s32 unk_84[9];
    /* 0xA8 */ char pad_A8[4];
} ChipShotChallengeWork; // Size 0xAC

// Work block for the course object, reached via ObjData->data
typedef struct ChipShotChallengeCourseWork {
    /* 0x00 */ char pad_00[3];
    /* 0x03 */ s8 unk_03;
    /* 0x04 */ s8 unk_04;
    /* 0x05 */ char pad_05[0xAF];
} ChipShotChallengeCourseWork; // Size 0xB4

typedef struct ChipShotChallengeSphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} ChipShotChallengeSphere; // Size 0x10

extern f32 Hu3DMatColScale;
extern f32 Hu3DMatAmbScale;
extern s32 omCharModelNoTbl[][6];
extern u8 omAllPauseF;

s32 D_8010A820_chip_shot_challenge = 0;
s32 D_8010A824_chip_shot_challenge = 0;
f32 D_8010A828_chip_shot_challenge = 0.0f;
f32 D_8010A82C_chip_shot_challenge = 0.0f;
f32 D_8010A830_chip_shot_challenge = 0.0f;
f32 D_8010A834_chip_shot_challenge = 5.0f;
f32 D_8010A838_chip_shot_challenge = 0.0f;
s32 D_8010A83C_chip_shot_challenge = 0;
s32 D_8010A840_chip_shot_challenge = 0;
s32 D_8010A844_chip_shot_challenge = -1;
s32 D_8010A848_chip_shot_challenge = 1;
s32 D_8010A84C_chip_shot_challenge[4][3] = {
    { -200, 0, 100 },
    { -80, 0, 100 },
    { 80, 0, 100 },
    { 200, 0, 100 }
};
f32 D_8010A87C_chip_shot_challenge[5] = { 125.0f, 155.0f, 180.0f, 215.0f, 245.0f };
f32 D_8010A890_chip_shot_challenge[5] = { 600.0f, 800.0f, 400.0f, 900.0f, 200.0f };
f32 D_8010A8A4_chip_shot_challenge[5] = { 2500.0f, 3000.0f, 3500.0f, 4000.0f, 4500.0f };
f32 D_8010A8B8_chip_shot_challenge[5] = { 0.075f, 0.1f, 0.15f, 0.2f, 0.15f };
f32 D_8010A8CC_chip_shot_challenge[5] = { 0.0f, 270.0f, 180.0f, 30.0f, 190.0f };
s32 D_8010A8E0_chip_shot_challenge[4] = { 1, 1, 1, 1 };
f32 D_8010A8F0_chip_shot_challenge[4] = { 10000.0f, 10000.0f, 10000.0f, 10000.0f };
MinigameFlow D_8010A900_chip_shot_challenge = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_NONE, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    96, -1, -1, 75, 135
};
s32 D_8010A928_chip_shot_challenge[4] = { -1, -1, -1, -1 };
f32 D_8010A938_chip_shot_challenge = -1000.0f;
f32 D_8010A93C_chip_shot_challenge = -30.0f;
f32 D_8010A940_chip_shot_challenge = 0.0f;
f32 D_8010A944_chip_shot_challenge = -0.8f;
s32 D_8010A948_chip_shot_challenge = -1;
s32 D_8010A94C_chip_shot_challenge = 0;
s32 D_8010A950_chip_shot_challenge = -1;
f32 D_8010A954_chip_shot_challenge = 0.0f;
s32 D_8010A958_chip_shot_challenge = -1;
f32 D_8010A95C_chip_shot_challenge[4] = { -300.0f, -600.0f, -900.0f, -1200.0f }; /* Unreferenced. */
u8 D_8010A96C_chip_shot_challenge = 240;
f32 D_8010A970_chip_shot_challenge = 0.0f;
f32 D_8010A974_chip_shot_challenge = 0.0f;
f32 D_8010A978_chip_shot_challenge = 0.0f;
f32 D_8010A97C_chip_shot_challenge = 0.0f;
s32 D_8010A980_chip_shot_challenge = -1;
f32 D_8010A984_chip_shot_challenge[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 D_8010A994_chip_shot_challenge[4] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
f32 D_8010A9A4_chip_shot_challenge[4] = { 1.0f, 0.7f, 0.5f, 0.3f };

f32 D_8010AA60_chip_shot_challenge BSS;
Vec D_8010AA64_chip_shot_challenge BSS;
Vec D_8010AA70_chip_shot_challenge BSS;
Vec D_8010AA7C_chip_shot_challenge BSS;
f32 D_8010AA88_chip_shot_challenge BSS;
Vec D_8010AA8C_chip_shot_challenge BSS;
s32 D_8010AA98_chip_shot_challenge BSS;
s32 D_8010AA9C_chip_shot_challenge BSS;
s32 D_8010AAA0_chip_shot_challenge BSS;
Vec D_8010AAA4_chip_shot_challenge BSS;
Vec D_8010AAB0_chip_shot_challenge BSS;
f32 D_8010AABC_chip_shot_challenge BSS;
s32 D_8010AAC0_chip_shot_challenge BSS;
s32 D_8010AAC4_chip_shot_challenge BSS;
s32 D_8010AAC8_chip_shot_challenge BSS;
s32 D_8010AACC_chip_shot_challenge BSS;
s32 D_8010AAD0_chip_shot_challenge BSS;
u8 D_8010AAD4_chip_shot_challenge[4] BSS; /* Unreferenced. */
s32 D_8010AAD8_chip_shot_challenge[4] BSS;
s16 D_8010AAE8_chip_shot_challenge BSS;
u8 D_8010AAEC_chip_shot_challenge[4] BSS; /* Unreferenced. */
omObjData *D_8010AAF0_chip_shot_challenge BSS;

s32 func_80105DE0_chip_shot_challenge(s32 playerIndex);
void func_80106B84_chip_shot_challenge(omObjData *object);
void func_8010646C_chip_shot_challenge(omObjData *object);
void func_80107048_chip_shot_challenge(void);
void func_80107960_chip_shot_challenge(s16 value);
void func_80107BB0_chip_shot_challenge(void);
void func_80107E94_chip_shot_challenge(void);
f32 func_80109AD0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z);
void func_801085C0_chip_shot_challenge(omObjData *object);
void func_80108638_chip_shot_challenge(omObjData *object);
void func_801086B4_chip_shot_challenge(omObjData *object);
void func_80108730_chip_shot_challenge(omObjData *object);
void func_80107520_chip_shot_challenge(omObjData *object);
void func_80108108_chip_shot_challenge(omObjData *object);
void func_801071A8_chip_shot_challenge(void);
void func_801073D4_chip_shot_challenge(s16 model);
void func_80107238_chip_shot_challenge(s16 model);
void func_801087AC_chip_shot_challenge(omObjData *object);
void func_801091E8_chip_shot_challenge(omObjData *object);
void func_801094D8_chip_shot_challenge(omObjData *object);
void func_80109B24_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z);
f32 func_80109DE0_chip_shot_challenge(omObjData *object, ChipShotChallengeSphere *sphere);
void func_80109EF0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_8010A04C_chip_shot_challenge(ChipShotChallengeSphere *sphere, Vec *normal);
void func_8010A3DC_chip_shot_challenge(omObjData *object, Vec *arg1);
void func_8010A454_chip_shot_challenge(omObjData *object, s32 *stickX, s32 *stickY, s32 *buttons);

void func_801059A0_chip_shot_challenge(void) {
    u8 camIndex;
    u16 sprite;
    s32 rank;
    s32 i;

    MapCollInit(50);
    Hu3DQuadPoolInit(&mgQuadPool, 0x40);
    Hu3DSprModelInit(32);
    omInitObjMan(50, 0);
    omGameSysInit();
    MgFieldStatClear();
    CamSetupInit(1);
    camIndex = CamSetupMapCullAdd();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);
    Hu3DGLightDirSet(1, 32.0f, 99.0f, 59.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    MgPlayerParamReset();
    MgShadowAltSet(1);
    mgPlayerFallInit = 0.0f;
    MgMapBaseSet(mgMapObjNum);
    mgMapObjTbl[mgMapObjNum++] = omAddObj(1, 12, 0, -1, func_80106B84_chip_shot_challenge);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, func_801085C0_chip_shot_challenge);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, func_80108638_chip_shot_challenge);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, func_801086B4_chip_shot_challenge);
    mgPlayerObjTbl[mgPlayerObjNum++] = omAddObj(2, 10, 10, -1, func_80108730_chip_shot_challenge);
    omAddObj(3, 25, 10, -1, func_80107520_chip_shot_challenge);
    D_8010AAF0_chip_shot_challenge = omAddObj(3, 10, 0, -1, func_80108108_chip_shot_challenge);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    sprite = espEntry(HuSprAnimDataRead(0x3C001E), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, 0x4000);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    MgFlowInit(&D_8010A900_chip_shot_challenge);
    mgFlowSeqNo = 45;
    mgFlowSeqTime = 60;
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 0.0f;
    CRot.x = 350.0f;
    CRot.y = 0.0f;
    CZoom = 750.0f;
    for (i = 0; i < 4; i++) {
        rank = func_80105DE0_chip_shot_challenge(i);
        while (D_8010A928_chip_shot_challenge[rank] != -1) {
            rank++;
        }
        D_8010A928_chip_shot_challenge[rank] = i;
    }
}

s32 func_80105DE0_chip_shot_challenge(s32 playerIndex) {
    s32 scores[4];
    s32 rank;
    s32 i;

    for (i = 0; i < 4; i++) {
        scores[i] = GwPlayer[i].star * 1000 + GwPlayer[i].coin;
    }
    for (i = 0, rank = 0; i < 4; i++) {
        if (i != playerIndex) {
            rank += scores[playerIndex] < scores[i];
        }
    }
    return rank;
}

void func_80105E8C_chip_shot_challenge(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80105EB8_chip_shot_challenge(omObjData *object) {
    s32 time = MgFlowStatTimeGet();
    f32 velocity;
    f32 speedSq;

    if (time == 1) {
        HuAudFXPlay(0x3E0);
    }
    if (time < 5) {
        Center.x = D_8010AAA4_chip_shot_challenge.x;
        Center.y = D_8010AAA4_chip_shot_challenge.y + 200.0f;
        Center.z = D_8010AAA4_chip_shot_challenge.z;
        D_8010AA70_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x + 1000.0f;
        D_8010AA70_chip_shot_challenge.y = D_8010AAA4_chip_shot_challenge.y + 300.0f;
        D_8010AA70_chip_shot_challenge.z = D_8010AAA4_chip_shot_challenge.z;
        Hu3DModelPosSet(object->model[5], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
    } else if (time < 35) {
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelAttrSet(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        Hu3DModelPosSet(object->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        Hu3DModelPosSet(object->model[5], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        D_8010AA70_chip_shot_challenge.x -= 100.0f / 3.0f;
        D_8010AA70_chip_shot_challenge.y -= 10.0f / 3.0f;
        D_8010AA70_chip_shot_challenge.z += 0.0f;
        if (time < 21) {
            D_8010A938_chip_shot_challenge = D_8010AA70_chip_shot_challenge.y;
            D_8010AA7C_chip_shot_challenge.x -= 200.0f / 3.0f;
            D_8010A940_chip_shot_challenge = 30.0f;
        } else {
            D_8010AA7C_chip_shot_challenge.x = D_8010AA70_chip_shot_challenge.x;
            D_8010AA7C_chip_shot_challenge.y = D_8010AA70_chip_shot_challenge.y;
            D_8010AA7C_chip_shot_challenge.z = D_8010AA70_chip_shot_challenge.z;
        }
    } else if (time < 65) {
        Hu3DModelPosSet(object->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        D_8010AA64_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x;
        D_8010AA64_chip_shot_challenge.y = D_8010AAA4_chip_shot_challenge.y;
        D_8010AA64_chip_shot_challenge.z = D_8010AAA4_chip_shot_challenge.z;
        MapVecNormalize(&D_8010AA64_chip_shot_challenge);
        D_8010AA60_chip_shot_challenge =
            HuSqrtf(D_8010AAA4_chip_shot_challenge.x * D_8010AAA4_chip_shot_challenge.x +
                    D_8010AAA4_chip_shot_challenge.y * D_8010AAA4_chip_shot_challenge.y +
                    D_8010AAA4_chip_shot_challenge.z * D_8010AAA4_chip_shot_challenge.z) /
            30.0f;
        D_8010AA70_chip_shot_challenge.x -= 100.0f / 3.0f;
        D_8010AA70_chip_shot_challenge.y += 10.0f / 3.0f;
        D_8010AA70_chip_shot_challenge.z += 0.0f;
        D_8010AA7C_chip_shot_challenge.x -= 200.0f / 3.0f;
        if (D_8010AA7C_chip_shot_challenge.x < D_8010AAA4_chip_shot_challenge.x) {
            D_8010AA7C_chip_shot_challenge.x = D_8010AAA4_chip_shot_challenge.x;
            if (D_8010A948_chip_shot_challenge != 0) {
                HuAudPlayerFXPlay(0x3DE, 0);
                D_8010A948_chip_shot_challenge = 0;
            }
        }
    } else {
        Hu3DModelAttrSet(object->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Center.x -= D_8010AA64_chip_shot_challenge.x * D_8010AA60_chip_shot_challenge;
        Center.y -= D_8010AA64_chip_shot_challenge.y * D_8010AA60_chip_shot_challenge;
        Center.z -= D_8010AA64_chip_shot_challenge.z * D_8010AA60_chip_shot_challenge;
    }
    if (D_8010A938_chip_shot_challenge > -1000.0f) {
        velocity = D_8010A944_chip_shot_challenge;
        speedSq = velocity * velocity;
        if (velocity >= 0.0f) {
            D_8010A938_chip_shot_challenge += speedSq * -37.5f;
        } else {
            D_8010A938_chip_shot_challenge += speedSq * 37.5f;
        }
        D_8010A944_chip_shot_challenge += mgItemGravity;
        if (D_8010A944_chip_shot_challenge > 1.2f) {
            D_8010A944_chip_shot_challenge = 1.2f;
        }
        if (D_8010A938_chip_shot_challenge < 0.0f) {
            D_8010A938_chip_shot_challenge = 0.0f;
        }
        if (D_8010A938_chip_shot_challenge == 0.0f) {
            D_8010A940_chip_shot_challenge *= 0.9f;
            D_8010A93C_chip_shot_challenge += 50.0f;
        }
        D_8010AA7C_chip_shot_challenge.y = D_8010A938_chip_shot_challenge;
        Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, sindf(D_8010A93C_chip_shot_challenge) * D_8010A940_chip_shot_challenge);
        Hu3DModelPosSet(object->model[5], D_8010AA7C_chip_shot_challenge.x,
                        D_8010AAA4_chip_shot_challenge.y + D_8010AA7C_chip_shot_challenge.y,
                        D_8010AA7C_chip_shot_challenge.z);
    } else {
        Hu3DModelPosSet(object->model[6], D_8010AA70_chip_shot_challenge.x, D_8010AA70_chip_shot_challenge.y,
                        D_8010AA70_chip_shot_challenge.z);
        Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, 30.0f);
    }
}

void func_8010646C_chip_shot_challenge(omObjData *object) {
    omObjData *player;
    ChipShotChallengeWork *work;
    f32 best;
    f32 x;
    f32 scale;
    s32 time;
    s32 chrData;
    s32 chr;
    s32 i;
    s32 j;

    if (omPauseChk() + omAllPauseF != 0) {
        return;
    }
    time = MgFlowStatTimeGet();
    switch (MgFlowMain()) {
        case 0:
            func_80105EB8_chip_shot_challenge(object);
            break;
        case 1:
            Hu3DModelRotSet(object->model[5], 0.0f, 0.0f, 0.0f);
            break;
        case 2:
            if (D_8010A844_chip_shot_challenge < 0) {
                D_8010A844_chip_shot_challenge = 0;
            }
            D_8010AA8C_chip_shot_challenge.x = Center.x;
            D_8010AA8C_chip_shot_challenge.y = Center.y - 200.0f;
            D_8010AA8C_chip_shot_challenge.z = Center.z;
            MapVecNormalize(&D_8010AA8C_chip_shot_challenge);
            D_8010AA88_chip_shot_challenge = HuSqrtf(Center.x * Center.x + Center.y * Center.y + Center.z * Center.z) / 30.0f;
            break;
        case 3:
            if (time == 0) {
                best = 10000.0f;
                for (i = 0; i < 4; i++) {
                    if (D_8010A8F0_chip_shot_challenge[i] < best) {
                        best = D_8010A8F0_chip_shot_challenge[i];
                        D_8010A950_chip_shot_challenge = i;
                    }
                    if (D_8010A8F0_chip_shot_challenge[i] == 0.0f) {
                        D_8010A94C_chip_shot_challenge++;
                        D_8010A8E0_chip_shot_challenge[i] = 0;
                    }
                }
                if (D_8010A94C_chip_shot_challenge != 0) {
                    D_8010A900_chip_shot_challenge.resultType = D_8010A94C_chip_shot_challenge - 1;
                    for (i = 0, j = 0; i < 4; i++) {
                        if (D_8010A8F0_chip_shot_challenge[i] == 0.0f) {
                            D_8010A900_chip_shot_challenge.winners[j++] = i;
                        }
                    }
                } else {
                    for (i = 0; i < 4; i++) {
                        if (i != D_8010A950_chip_shot_challenge &&
                            (s32)best == (s32)D_8010A8F0_chip_shot_challenge[i]) {
                            D_8010A950_chip_shot_challenge = -1;
                        }
                    }
                    if (D_8010A950_chip_shot_challenge == -1) {
                        D_8010A900_chip_shot_challenge.resultType = MG_RESULT_DRAW;
                    } else {
                        D_8010A900_chip_shot_challenge.resultType = MG_RESULT_WIN_1;
                        D_8010A900_chip_shot_challenge.winners[0] = D_8010A950_chip_shot_challenge;
                        D_8010A8E0_chip_shot_challenge[D_8010A950_chip_shot_challenge] = 0;
                        D_8010A94C_chip_shot_challenge++;
                    }
                }
            }
            Center.x -= D_8010AA8C_chip_shot_challenge.x * D_8010AA88_chip_shot_challenge;
            Center.y -= D_8010AA8C_chip_shot_challenge.y * D_8010AA88_chip_shot_challenge;
            Center.z -= D_8010AA8C_chip_shot_challenge.z * D_8010AA88_chip_shot_challenge;
            CRot.y *= 0.9f;
            if (Center.z >= 0.0f) {
                Center.x = 0.0f;
                Center.y = 200.0f;
                Center.z = 0.0f;
                CRot.y = 0.0f;
            }
            break;
        case 4:
            if (mgFlowResultF == 1) {
                for (i = 0; i < 4; i++) {
                    player = mgPlayerObjTbl[i];
                    if (D_8010A8E0_chip_shot_challenge[D_8010A928_chip_shot_challenge[i]] == 0) {
                        work = player->data;
                        MgPlayerMotSet(player, 5);
                        chr = GwPlayer[work->playerIndex].chr;
                        chrData = omCharModelNoTbl[chr][0];
                        CharAnimSet(player->model[0], 2, chr, player->model[4]);
                        HuAudCharVoicePlay(chrData | 0x2F);
                        GwPlayer[work->playerIndex].bonusCoin += 10;
                    } else {
                        MgPlayerMotSet(player, 6);
                    }
                }
            }
            break;
        case 5:
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            object->func = func_80105E8C_chip_shot_challenge;
            break;
    }
    MgShadowSlopeSet(object->model[4], &D_8010AAB0_chip_shot_challenge);
    for (i = 0; i < 5; i++) {
        x = sindf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i];
        Hu3DModelPosSet(object->model[7 + i], x, D_8010A890_chip_shot_challenge[i],
                        cosdf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i] - 1000.0f);
        Hu3DModelRotSet(object->model[7 + i], 0.0f, CRot.y, 0.0f);
        scale = sindf(D_8010A8CC_chip_shot_challenge[i]) * 0.25f + 2.5f;
        Hu3DModelScaleSet(object->model[7 + i], scale, scale, scale);
        D_8010A8CC_chip_shot_challenge[i] =
            HuAngleWrap(D_8010A8B8_chip_shot_challenge[i] * 30.0f + D_8010A8CC_chip_shot_challenge[i]);
        D_8010A87C_chip_shot_challenge[i] =
            HuAngleWrap(D_8010A87C_chip_shot_challenge[i] + D_8010A8B8_chip_shot_challenge[i]);
        if (D_8010A87C_chip_shot_challenge[i] > 260.0f) {
            D_8010A87C_chip_shot_challenge[i] = 100.0f;
        }
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        ((ChipShotChallengeWork *)mgPlayerObjTbl[i]->data)->unk_60 = CRot.y;
    }
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        HuAudSeqFadeOut(30);
        HuAudFXAllFadeOut(30);
        object->func = func_80105E8C_chip_shot_challenge;
    }
}

void func_80106B84_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeCourseWork *work;
    ChipShotChallengeSphere sphere;
    f32 angle;
    f32 dist;
    s32 tag = 0x2B9;

    mgPlayerAccel = 20.0f;
    if (rand8() > 128) {
        object->model[0] = Hu3DModelRead2(0x3C0000, tag);
    } else {
        object->model[0] = Hu3DModelRead2(0x3C0001, tag);
    }
    object->model[1] = Hu3DModelRead2(0x3C0002, tag);
    object->model[2] = Hu3DModelRead2(0x3C0003, tag);
    object->model[3] = Hu3DModelRead2(0x3C0004, tag);
    object->model[4] = Hu3DModelRead2(0x3C0005, tag);
    object->model[5] = Hu3DModelRead2(0x3C0009, tag);
    MgShadowMdlInit(object->model[4]);
    D_8010AAD0_chip_shot_challenge = object->model[6] = Hu3DModelRead2(0xA0089, tag);
    object->model[7] = Hu3DModelRead2(0x210029, tag);
    object->model[8] = Hu3DModelLink(object->model[7]);
    object->model[9] = Hu3DModelLink(object->model[7]);
    object->model[10] = Hu3DModelLink(object->model[7]);
    object->model[11] = Hu3DModelLink(object->model[7]);
    Hu3DModelScaleSet(object->model[7], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[8], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[9], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[10], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[11], 2.0f, 2.0f, 2.0f);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = -1000.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(sizeof(ChipShotChallengeCourseWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(ChipShotChallengeCourseWork));
    object->func = func_8010646C_chip_shot_challenge;
    work->unk_03 = 1;
    MgMapTiltOn(object);
    MgMapAttrSet(object, 1, 0.0f);
    MgMapFrictionSet(object, 0.1f);
    MgMapAccelSet(object, mgPlayerAccel);
    MgMapSlideSet(object, 25.0f);
    MgMapNoBumpOn(object);
    work->unk_04 = 0;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    while (TRUE) {
        angle = rand8() * (360.0f / 255.0f);
        if (angle > 10.0f && (!(angle > 170.0f) | !(angle < 190.0f)) && angle < 350.0f) {
            break;
        }
    }
    dist = rand8() * 1.5f;
    if (dist < 200.0f) {
        dist = 200.0f;
    }
    D_8010AAA4_chip_shot_challenge.x = sindf(angle) * dist;
    D_8010AAA4_chip_shot_challenge.y = 50.0f;
    D_8010AAA4_chip_shot_challenge.z = cosdf(angle) * dist + -1000.0f;
    sphere.pos.x = D_8010AAA4_chip_shot_challenge.x;
    sphere.pos.y = 50.0f;
    sphere.pos.z = D_8010AAA4_chip_shot_challenge.z;
    D_8010AAA4_chip_shot_challenge.y = func_8010A04C_chip_shot_challenge(&sphere, &D_8010AAB0_chip_shot_challenge);
    Hu3DModelScaleSet(object->model[4], 0.625f, 0.625f, 0.625f);
    Hu3DModelPosSet(object->model[4], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y + 5.0f,
                    D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(object->model[5], D_8010AAA4_chip_shot_challenge.x, D_8010AAA4_chip_shot_challenge.y - 10.0f,
                    D_8010AAA4_chip_shot_challenge.z);
    func_80107048_chip_shot_challenge();
}

void func_80107048_chip_shot_challenge(void) {
    s32 files[4] = { 0xB002B, 0xB002C, 0xB002D, 0xB002E };
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = Hu3DModelRead(files[i], 0xAA9);
        D_8010AAD8_chip_shot_challenge[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        Hu3DModelVtxBufMake(model);
        Hu3DModelDynamicFree(model);
        Hu3DParticleCreate(model, -1, 0, func_801073D4_chip_shot_challenge);
    }
}

void func_801071A8_chip_shot_challenge(void) {
    s32 *entries;
    s16 i;

    for (i = 0, entries = D_8010AAD8_chip_shot_challenge; i < 4; i++) {
        if (((D_8010AAE8_chip_shot_challenge + i) & 3) == 0) {
            func_80107238_chip_shot_challenge(entries[i]);
        }
    }
    D_8010AAE8_chip_shot_challenge++;
}

void func_80107238_chip_shot_challenge(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (rand8() - 127.0f) * 2.0f;
            particle->unk10 = D_8010AAA4_chip_shot_challenge.y + 700.0f;
            particle->unk14 = ((rand8() * 125) >> 5) - 500;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk08 = 5.0f;
            break;
        }
    }
}

void func_801073D4_chip_shot_challenge(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }
    for (i = 0, particle = effect->unk58; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 15.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_80107520_chip_shot_challenge(omObjData *object) {
    void *data;
    s16 image1;
    s16 image2;
    s16 group;
    s16 i;
    s16 x;

    Hu3DMatAmbScale = Hu3DMatColScale = 0.0f;
    object->model[1] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[2] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[3] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[4] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[5] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[6] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[7] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[8] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[9] = Hu3DModelRead2(0x3C0007, 0xAD9);
    object->model[10] = Hu3DModelRead2(0x3C0007, 0xAD9);
    Hu3DMatColScale = 1.0f;
    Hu3DMatAmbScale = 1.0f;
    object->func = func_801091E8_chip_shot_challenge;

    data = DataRead(0x2D);
    image1 = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x3C001F);
    image2 = HuSprAnimRead(data);
    DataClose(data);

    group = D_8010AAC0_chip_shot_challenge = HuSprGrpCreate(4, 5);
    HuSprGrpMemberSet(group, 0, image1, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, 0x80, 0x64);
    HuSprPriSet(group, 0, 1);
    x = 15;
    for (i = 1; i < 4; i++) {
        HuSprPriSet(group, i, 1);
        HuSprGrpMemberSet(group, i, image1, 0);
        HuSprPosSet(group, i, x, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprDispOff(group, i);
        if (i == 1) {
            x += 20;
        } else {
            x += 15;
        }
        HuSprParentSet(group, i, 0);
    }
    HuSprDispOn(group, 2);

    group = D_8010AAC4_chip_shot_challenge = HuSprGrpCreate(2, 5);
    HuSprGrpMemberSet(group, 0, image2, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprDispOff(group, 0);
    HuSprPosSet(group, 0, 0x9F, 0x64);
    HuSprPriSet(group, 0, 1);
    HuSprPriSet(group, 1, 1);
    HuSprGrpMemberSet(group, 1, image2, 0);
    HuSprPosSet(group, 1, 0x23, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprDispOff(group, 1);
    HuSprParentSet(group, 1, 0);
    HuSprDispOn(group, 2);

    D_8010AACC_chip_shot_challenge = Hu3DModelRead2(0x3C001D, 0xAD9);
    D_8010AAC8_chip_shot_challenge = Hu3DModelRead2(0x3C001C, 0xAD9);
}

void func_80107960_chip_shot_challenge(s16 value) {
    s16 digit;

    if ((s16)(value / 1000) != 0) {
        HuSprDispOn(D_8010AAC0_chip_shot_challenge, 0);
        HuSprBankSet(D_8010AAC0_chip_shot_challenge, 0, value / 1000, 0);
        HuSprAnimModeSet(D_8010AAC0_chip_shot_challenge, 0, HUSPR_ANIM_MODE_BANK);
    }
    value -= (s16)(value / 1000) * 1000;
    HuSprDispOn(D_8010AAC0_chip_shot_challenge, 1);
    digit = value / 100;
    HuSprBankSet(D_8010AAC0_chip_shot_challenge, 1, digit, 0);
    HuSprAnimModeSet(D_8010AAC0_chip_shot_challenge, 1, HUSPR_ANIM_MODE_BANK);
    value -= digit * 100;
    HuSprDispOn(D_8010AAC0_chip_shot_challenge, 2);
    digit = value / 10;
    HuSprBankSet(D_8010AAC0_chip_shot_challenge, 2, digit, 0);
    HuSprAnimModeSet(D_8010AAC0_chip_shot_challenge, 2, HUSPR_ANIM_MODE_BANK);
    value -= digit * 10;
    HuSprDispOn(D_8010AAC0_chip_shot_challenge, 3);
    HuSprBankSet(D_8010AAC0_chip_shot_challenge, 3, value, 0);
    HuSprAnimModeSet(D_8010AAC0_chip_shot_challenge, 3, HUSPR_ANIM_MODE_BANK);
    HuSprDispOn(D_8010AAC4_chip_shot_challenge, 0);
    HuSprPatNoSet(D_8010AAC4_chip_shot_challenge, 0, 1);
    HuSprDispOn(D_8010AAC4_chip_shot_challenge, 1);
    HuSprPatNoSet(D_8010AAC4_chip_shot_challenge, 1, 0);
}

void func_80107BB0_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    MapVecNormalize(&dir);
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010AAA4_chip_shot_challenge.y + 700.0f - D_8010A840_chip_shot_challenge * 10.0f;
        Center.y *= 1.02f;
        D_8010A954_chip_shot_challenge = -9.0f;
        if (D_8010A958_chip_shot_challenge != 0) {
            HuAudFXPlay(0x3DF);
            D_8010A958_chip_shot_challenge = 0;
        }
    } else {
        y = D_8010AAA4_chip_shot_challenge.y + 400.0f + sindf(D_8010A954_chip_shot_challenge) * 100.0f;
        D_8010A954_chip_shot_challenge -= 9.0f;
        Center.y *= 1.02f;
        D_8010A958_chip_shot_challenge = -1;
    }
    if (D_8010A840_chip_shot_challenge < 101) {
        func_801071A8_chip_shot_challenge();
    }
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[0], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[1], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[2], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    Hu3DModelPosSet(D_8010AAD8_chip_shot_challenge[3], D_8010AAA4_chip_shot_challenge.x,
                    D_8010AAA4_chip_shot_challenge.y, D_8010AAA4_chip_shot_challenge.z);
    if (D_8010AAA4_chip_shot_challenge.y + 400.0f < Center.y) {
        Center.y = D_8010AAA4_chip_shot_challenge.y + 400.0f;
    }
    Hu3DModelPosSet((s16)D_8010AAD0_chip_shot_challenge, x, y, z);
    Hu3DModelPosSet(D_8010AAC8_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet((s16)D_8010AAD0_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AAC8_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelAttrSet(D_8010AAC8_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet((s16)D_8010AAD0_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_80107E94_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    MapVecNormalize(&dir);
    if (D_8010A840_chip_shot_challenge == 1) {
        HuAudPlayerFXPlay(0x3DC, (s16)D_8010A844_chip_shot_challenge);
    }
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010A840_chip_shot_challenge * 10.0f + -200.0f;
    } else {
        y = 100.0f;
    }
    x += dir.x * 200.0f;
    z += dir.z * 200.0f;
    Hu3DModelPosSet((s16)D_8010AAD0_chip_shot_challenge, x, y, z);
    Hu3DModelPosSet(D_8010AACC_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet((s16)D_8010AAD0_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACC_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    Hu3DModelAttrSet(D_8010AACC_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelAttrSet((s16)D_8010AAD0_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010802C_chip_shot_challenge(void) {
    HuSprDispOff(D_8010AAC0_chip_shot_challenge, 0);
    HuSprDispOff(D_8010AAC0_chip_shot_challenge, 1);
    HuSprDispOff(D_8010AAC0_chip_shot_challenge, 2);
    HuSprDispOff(D_8010AAC0_chip_shot_challenge, 3);
    HuSprDispOff(D_8010AAC4_chip_shot_challenge, 0);
    HuSprDispOff(D_8010AAC4_chip_shot_challenge, 1);
    Hu3DModelAttrSet(D_8010AACC_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(D_8010AAC8_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    if (MgFlowStatGet() >= MG_STATE_PLAY) {
        Hu3DModelAttrSet((s16)D_8010AAD0_chip_shot_challenge, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void func_80108108_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ChipShotChallengeWork), TAG_OVERLAY);
    memset(object->data, 0, sizeof(ChipShotChallengeWork));
    work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    object->model[0] = Hu3DModelRead2(0x3C0008, 0xAB9);
    object->model[1] = Hu3DModelRead3(9, 0xAB9);
    MgShadowMdlInit(object->model[1]);
    work->unk_44 = 0.3f;
    work->unk_48 = 60.0f;
    work->unk_34 = 50.0f;
    work->unk_3C = 0.0f;
    work->unk_78 = 0;
    work->unk_52 = 7;
    work->unk_7C = 0;
    work->unk_50 = 0;
    work->unk_40 = 0.0f;
    work->unk_38 = 1000.0f;
    work->unk_74 = 0.5f;
    work->unk_54 = 1;
    for (i = 0; i < 9; i++) {
        work->unk_84[i] = 0;
    }
    MgPlayerMapAttrSet(object, 0, 2);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelScaleSet(object->model[1], 0.4f, 0.4f, 0.4f);
    object->func = func_801094D8_chip_shot_challenge;
}

MgPlayerWork *func_80108274_chip_shot_challenge(omObjData *object, s32 player) {
    MgPlayerWork *data;
    s32 i;
    s32 chr;
    s32 model;
    s32 motion;
    s32 tag;

    motion = omCharModelNoTbl[GwPlayer[player].chr][2];
    model = omCharModelNoTbl[GwPlayer[player].chr][0];
    tag = 0xAA9;
    chr = GwPlayer[player].chr;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    data = HuMemAllocTag(0x15C, TAG_OVERLAY);
    object->data = data;
    memset(data, 0, 0x15C);
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), TAG_OVERLAY);
    object->model[0] = Hu3DModelRead2(model | motion, tag);
    object->model[1] = Hu3DModelRead2(9, tag);
    CharAnimCreate(object->model[0], 2, chr, CharMotionDataNumGetTbl(chr, 2, 0));
    object->model[4] = Hu3DAnimDataRead(CharMotionDataNumGetTbl(chr, 2, 1));
    MgPlayerMotRead(object, 0, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotRead(object, 1, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotRead(object, 2, CharMotionDataNumGet(chr, 0x5E), 1, 0);
    MgPlayerMotRead(object, 3, CharMotionDataNumGet(chr, 0x5F), 0, 0);
    MgPlayerMotRead(object, 5, CharMotionDataNumGet(chr, 0x2F), 0, 0);
    MgPlayerMotRead(object, 6, CharMotionDataNumGet(chr, 0x36), 0, 0);
    object->model[2] = Hu3DModelRead2((chr + 10) | 0x3C0000, tag);
    object->model[3] = Hu3DModelRead2((chr + 0x12) | 0x3C0000, 0x4AD);
    Hu3DModelHookSet(object->model[2], object->model[0], "item_hook");
    Hu3DModelAttrSet(object->model[2], 0x4000, 0x4000);
    Hu3DModelTPLvlInit(object->model[3]);
    Hu3DModelTPLvlSet(object->model[3], 0x80);
    data->unk40 = 50.0f;
    object->func = func_801087AC_chip_shot_challenge;
    data->unk50 = 0;
    Hu3DMotionModelSet(object->model[0], object->motion[0]);
    Hu3DMotionAttrSet(object->model[0], 2, 2);
    object->rot.y = 90.0f;
    data->unk59 = player;
    data->unk57 = GwPlayer[player].pad;
    return data;
}

void func_801085C0_chip_shot_challenge(omObjData *object) {
    MgPlayerWork *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[0]);

    object->trans.x = -300.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 0;
}

void func_80108638_chip_shot_challenge(omObjData *object) {
    MgPlayerWork *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[1]);

    object->trans.x = -600.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 1;
}

void func_801086B4_chip_shot_challenge(omObjData *object) {
    MgPlayerWork *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[2]);

    object->trans.x = -900.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 2;
}

void func_80108730_chip_shot_challenge(omObjData *object) {
    MgPlayerWork *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[3]);

    object->trans.x = -1200.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 3;
}

void func_801087AC_chip_shot_challenge(omObjData *object) {
    MgPlayerWork *data = OM_GET_DATA_PTR(object, MgPlayerWork);
    // z is left implicit so GCC doesn't merge this with the identical initializer in func_80109DE0
    Vec pos = { .x = 0.0f, .y = 1.0f };
    s32 stickX;
    s32 stickY;
    s32 buttons;
    ChipShotChallengeWork *shot;
    ChipShotChallengeWork *ball;
    s32 pad;
    s32 player;
    s32 i;

    pad = data->unk57;
    player = data->unk59;
    if (MgFlowStatGet() == MG_STATE_PLAY) {
        stickX = HuPadStkX[pad];
        stickY = HuPadStkY[pad];
        buttons = (u16)HuPadBtn[pad];
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
    } else {
        stickX = stickY = buttons = 0;
    }
    if (D_8010A844_chip_shot_challenge == data->unk53[0]) {
        func_8010A454_chip_shot_challenge(object, &stickX, &stickY, &buttons);
        switch (data->unk50) {
            case 0:
                MgPlayerMotSet(object, 1);
                data->unk50 = 1;
                break;
            case 1:
                object->trans.x += 5.0f;
                if (object->trans.x > -90.0f) {
                    MgPlayerMotSet(object, 2);
                    data->unk50 = 2;
                    D_8010A824_chip_shot_challenge = 1;
                    object->trans.x = -90.0f;
                    GMesCreate(0x1A, 10, 0xA0, 0x18);
                    D_8010AA9C_chip_shot_challenge = 300;
                }
                MgShadowSlopeSet(D_8010AAF0_chip_shot_challenge->model[1], &pos);
                D_8010A96C_chip_shot_challenge -= 5;
                if (D_8010A96C_chip_shot_challenge < 100) {
                    D_8010A96C_chip_shot_challenge = 100;
                }
                break;
            case 2:
                GMesTimerValueSet(D_8010AA9C_chip_shot_challenge / 30 + 1);
                if ((buttons & 0x8000) || D_8010AA9C_chip_shot_challenge == 0) {
                    MgPlayerMotSet(object, 3);
                    data->unk50 = 3;
                    D_8010A824_chip_shot_challenge = 0;
                    D_8010AA98_chip_shot_challenge = 0;
                    GMesTimerEnd();
                }
                data->unk3C -= stickX / 50.0f;
                if (data->unk3C > 30.0f) {
                    data->unk3C = 30.0f;
                }
                if (data->unk3C < -30.0f) {
                    data->unk3C = -30.0f;
                }
                data->unk40 -= stickY / 50.0f;
                if (data->unk40 > 100.0f) {
                    data->unk40 = 100.0f;
                }
                if (data->unk40 < 60.0f) {
                    data->unk40 = 60.0f;
                }
                D_8010A828_chip_shot_challenge = data->unk3C;
                D_8010A82C_chip_shot_challenge = data->unk40;
                D_8010A830_chip_shot_challenge = D_8010A82C_chip_shot_challenge / 20.0f;
                object->trans.x = sindf(data->unk3C + 90.0f) * -90.0f;
                object->trans.z = cosdf(data->unk3C + 90.0f) * -90.0f + 20.0f;
                object->rot.y = data->unk3C + 90.0f;
                CRot.y = data->unk3C / 40.0f;
                D_8010AA9C_chip_shot_challenge--;
                break;
            case 3:
                if (D_8010AA98_chip_shot_challenge == 38) {
                    data->unk50 = 4;
                    shot = OM_GET_DATA_PTR(D_8010AAF0_chip_shot_challenge, ChipShotChallengeWork);
                    shot->unk_40 = data->unk40 / 5.0f;
                    shot->unk_3C = data->unk3C + 180.0f;
                    shot->unk_38 = -1.2f - data->unk40 / 300.0f;
                    D_8010A820_chip_shot_challenge = 1;
                    D_8010A83C_chip_shot_challenge = 0;
                    D_8010A848_chip_shot_challenge = 0;
                    HuAudPlayerFXPlay(0x3DA, player);
                    omVibrate(player, 5, 0, 5);
                }
                D_8010AA98_chip_shot_challenge++;
                D_8010A96C_chip_shot_challenge += 2;
                if (D_8010A96C_chip_shot_challenge > 240) {
                    D_8010A96C_chip_shot_challenge = 240;
                }
                break;
            case 4:
                if (fabs(CRot.y) < fabs(data->unk3C)) {
                    CRot.y *= 1.05f;
                }
                D_8010A96C_chip_shot_challenge += 2;
                if (D_8010A96C_chip_shot_challenge > 240) {
                    D_8010A96C_chip_shot_challenge = 240;
                }
                D_8010A828_chip_shot_challenge -= D_8010AABC_chip_shot_challenge;
                Center.x += sindf(D_8010A828_chip_shot_challenge + 180.0f) * D_8010A838_chip_shot_challenge;
                Center.z += cosdf(D_8010A828_chip_shot_challenge + 180.0f) * D_8010A838_chip_shot_challenge;
                if (D_8010A840_chip_shot_challenge < 70) {
                    break;
                }
                ball = OM_GET_DATA_PTR(D_8010AAF0_chip_shot_challenge, ChipShotChallengeWork);
                if (D_8010A83C_chip_shot_challenge == 1 && D_8010A840_chip_shot_challenge < 151) {
                    break;
                }
                D_8010A844_chip_shot_challenge++;
                ball->unk_5C = 0.0f;
                ball->unk_60 = 0.0f;
                ball->unk_64 = 0.0f;
                if (D_8010A844_chip_shot_challenge == 4) {
                    MgFlowStatSet(MG_STATE_FINISH);
                    for (i = 0; i < 4; i++) {
                        mgPlayerObjTbl[i]->trans.x = D_8010A84C_chip_shot_challenge[i][0];
                        mgPlayerObjTbl[i]->trans.y = D_8010A84C_chip_shot_challenge[i][1];
                        mgPlayerObjTbl[i]->trans.z = D_8010A84C_chip_shot_challenge[i][2];
                        mgPlayerObjTbl[i]->rot.y = 0.0f;
                        Hu3DModelPosSet(mgPlayerObjTbl[i]->model[1], D_8010A84C_chip_shot_challenge[i][0],
                                        D_8010A84C_chip_shot_challenge[i][1], D_8010A84C_chip_shot_challenge[i][2]);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelAttrSet(mgPlayerObjTbl[i]->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                        if (D_8010A848_chip_shot_challenge != 1) {
                            Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                            Hu3DModelPosSet(object->model[3], D_8010AAF0_chip_shot_challenge->trans.x,
                                            D_8010AAF0_chip_shot_challenge->trans.y - 50.0f,
                                            D_8010AAF0_chip_shot_challenge->trans.z);
                        }
                    }
                    Hu3DModelAttrSet(D_8010AAF0_chip_shot_challenge->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(D_8010AAF0_chip_shot_challenge->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                } else {
                    mgPlayerObjTbl[D_8010A844_chip_shot_challenge]->trans.x = -200.0f;
                    data->unk50 = 5;
                    Hu3DModelPosSet(D_8010AAF0_chip_shot_challenge->model[1], 0.0f, 3.0f, 0.0f);
                    MgShadowSlopeSet(D_8010AAF0_chip_shot_challenge->model[1], &pos);
                    Hu3DModelAttrSet(D_8010AAF0_chip_shot_challenge->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    if (D_8010A848_chip_shot_challenge != 1) {
                        Hu3DModelAttrSet(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                        Hu3DModelPosSet(object->model[3], D_8010AAF0_chip_shot_challenge->trans.x,
                                        D_8010AAF0_chip_shot_challenge->trans.y - 50.0f,
                                        D_8010AAF0_chip_shot_challenge->trans.z);
                    }
                    D_8010A820_chip_shot_challenge = 0;
                    object->trans.x = -90.0f;
                    D_8010AAF0_chip_shot_challenge->trans.x = D_8010AAF0_chip_shot_challenge->trans.y =
                        D_8010AAF0_chip_shot_challenge->trans.z = 0.0f;
                    ball->unk_3C = ball->unk_40 = 0.0f;
                    ball->unk_38 = 1000.0f;
                    Hu3DModelAttrSet(object->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    Center.x = 0.0f;
                    Center.y = 200.0f;
                    Center.z = 0.0f;
                    CRot.y = 0.0f;
                }
                MgPlayerMotSet(object, 0);
                D_8010A840_chip_shot_challenge = 0;
                D_8010A828_chip_shot_challenge = D_8010A82C_chip_shot_challenge = 0.0f;
                break;
            case 5:
            case 6:
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    }
    MgPlayerMotUpdate(object);
    if (D_8010A840_chip_shot_challenge == 0) {
        func_8010802C_chip_shot_challenge();
    }
}

void func_801091E8_chip_shot_challenge(omObjData *object) {
    Vec delta;
    f32 rotX;
    f32 x;
    f32 y;
    f32 z;
    f32 step;
    f32 baseScale;
    f32 scaleStep;
    f32 scale;
    s32 i;

    if (D_8010A824_chip_shot_challenge == 1) {
        rotX = 90.0f;
        x = z = 0.0f;
        y = 20.0f;
        step = D_8010A82C_chip_shot_challenge / 3.0f;
        baseScale = (D_8010A82C_chip_shot_challenge - 60.0f) / 40.0f * 20.0f;
        scaleStep = D_8010A82C_chip_shot_challenge / 100.0f;
        for (i = 0; i < 10; i++) {
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            delta.x = x;
            delta.y = y;
            delta.z = z;
            y += step;
            step -= 0.1f;
            x += sindf(D_8010A828_chip_shot_challenge + 180.0f) * step;
            z += cosdf(D_8010A828_chip_shot_challenge + 180.0f) * step;
            delta.x -= x;
            delta.y -= y;
            delta.z -= z;
            Hu3DModelPosSet(object->model[i + 1], x, y, z);
            Hu3DModelRotSet(object->model[i + 1], rotX, 0.0f, 0.0f);
            scale = baseScale + scaleStep * i + sindf(D_8010A974_chip_shot_challenge) * 0.5f;
            if (scale >= 30.0f) {
                scale = 30.0f;
            }
            Hu3DMotionTimeSet(object->model[i + 1], scale);
            rotX -= 7.0f;
        }
        D_8010A974_chip_shot_challenge += D_8010A82C_chip_shot_challenge / 10.0f;
        D_8010A970_chip_shot_challenge = HuAngleWrap(D_8010A970_chip_shot_challenge + 10.0f);
    } else {
        for (i = 0; i < 20; i++) {
            Hu3DModelAttrSet(object->model[i + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
}

void func_801094D8_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 floorY;
    u8 bounce = TRUE;

    func_80088800_main(Hu3DData[object->model[0]].mtx, 0.0f, 30.0f, 0.0f);
    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    mgMoveOfsX = mgMoveOfsZ = 0.0f;
    if (D_8010A820_chip_shot_challenge != 1) {
        D_8010A980_chip_shot_challenge = -1;
        return;
    }
    x = object->trans.x;
    y = object->trans.y;
    z = object->trans.z;
    angle = work->unk_3C;
    if (work->unk_38 != 1000.0f) {
        work->unk_40 -= 0.08f;
    } else {
        work->unk_40 -= 0.2f;
    }
    if (work->unk_40 < 0.0f) {
        work->unk_40 = 0.0f;
    }
    x += sindf(angle) * work->unk_40;
    z += cosdf(angle) * work->unk_40;
    if (work->unk_40 != 0.0f) {
        x += work->unk_5C;
        z += work->unk_64;
    }
    D_8010A838_chip_shot_challenge = work->unk_40;
    if (work->unk_38 != 1000.0f) {
        y += work->unk_38 * work->unk_38 * (work->unk_38 >= 0.0f ? -25.0f : 25.0f);
        work->unk_38 += mgItemGravity;
        if (work->unk_38 > mgItemFallMax) {
            work->unk_38 = mgItemFallMax;
        }
        if (D_8010A83C_chip_shot_challenge == 1) {
            if (y <= D_8010AAA4_chip_shot_challenge.y - 40.0f) {
                work->unk_40 = 0.0f;
            }
            Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        } else {
            floorY = func_80109AD0_chip_shot_challenge(object, x, y, z);
            if (y < floorY) {
                y = floorY;
                HuAudPlayerFXPlay(0x3DD, (s16)D_8010A844_chip_shot_challenge);
                if (bounce) {
                    work->unk_38 = -work->unk_38 * 0.45f;
                    if (work->unk_38 >= -0.3f) {
                        work->unk_38 = 1000.0f;
                    }
                }
            }
        }
    } else {
        y = func_80109AD0_chip_shot_challenge(object, x, y, z);
    }
    MgObjPosSet(object, x + mgMoveOfsX, y, z + mgMoveOfsZ);
    D_8010A978_chip_shot_challenge -= cosdf(angle) * work->unk_40 + mgMoveOfsZ;
    D_8010A978_chip_shot_challenge = HuAngleWrap(D_8010A978_chip_shot_challenge);
    D_8010A97C_chip_shot_challenge = HuAngleWrap(D_8010A97C_chip_shot_challenge);
    object->rot.y = angle;
    mtxRotCat(Hu3DData[object->model[0]].mtx, D_8010A978_chip_shot_challenge, 0.0f, 0.0f);
    if (D_8010AAF0_chip_shot_challenge->trans.y < -100.0f ||
        (D_8010A838_chip_shot_challenge == 0.0f && D_8010A83C_chip_shot_challenge != 1)) {
        D_8010A840_chip_shot_challenge++;
        if (!(D_8010AAF0_chip_shot_challenge->trans.y < -100.0f) && D_8010AAA0_chip_shot_challenge == 1) {
            x -= D_8010AAA4_chip_shot_challenge.x;
            y -= D_8010AAA4_chip_shot_challenge.y;
            z -= D_8010AAA4_chip_shot_challenge.z;
            func_80107960_chip_shot_challenge(HuSqrtf(x * x + y * y + z * z));
        } else if (D_8010A83C_chip_shot_challenge == 1) {
            func_80107BB0_chip_shot_challenge();
            if (D_8010A980_chip_shot_challenge == -1) {
                HuAudPlayerFXPlay(0x3DE, (s16)D_8010A844_chip_shot_challenge);
                D_8010A980_chip_shot_challenge = 0;
                omVibrate(OM_GET_DATA_PTR(mgPlayerObjTbl[D_8010A844_chip_shot_challenge], ChipShotChallengeWork)
                              ->playerIndex,
                          10, 0, 10);
            }
        } else {
            func_80107E94_chip_shot_challenge();
            D_8010A8F0_chip_shot_challenge[D_8010A928_chip_shot_challenge[D_8010A844_chip_shot_challenge]] = 10000.0f;
        }
    }
    if (D_8010AAF0_chip_shot_challenge->trans.y < -100.0f) {
        D_8010A848_chip_shot_challenge = 1;
    }
}

f32 func_80109AD0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = object->data;
    ChipShotChallengeSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = data->unk48;
    func_80109B24_chip_shot_challenge(object, x, y, z);
    return func_80109DE0_chip_shot_challenge(object, &sphere);
}

void func_80109B24_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 dx = D_8010AAA4_chip_shot_challenge.x - x;
    f32 dy = D_8010AAA4_chip_shot_challenge.y - y;
    f32 dz = D_8010AAA4_chip_shot_challenge.z - z;
    f32 dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
    f32 angle;
    f32 sinAngle;

    if (dist < 11.875f) {
        if (D_8010A83C_chip_shot_challenge != 1) {
            work->unk_40 = 0.5f;
            D_8010A83C_chip_shot_challenge = 1;
        }
        if (work->unk_38 == 1000.0f) {
            work->unk_38 = 0.0f;
        }
        D_8010AABC_chip_shot_challenge = 0.0f;
        D_8010A8F0_chip_shot_challenge[D_8010A928_chip_shot_challenge[D_8010A844_chip_shot_challenge]] = 0.0f;
    } else if (dist < 25.0f) {
        D_8010A8F0_chip_shot_challenge[D_8010A928_chip_shot_challenge[D_8010A844_chip_shot_challenge]] = dist;
        if (work->unk_38 == 1000.0f) {
            dist = 1.0f - (25.0f - dist) / 13.125f;
            angle = work->unk_3C - 90.0f;
            sinAngle = sindf(angle);
            D_8010AABC_chip_shot_challenge = MgDirDot(dx, dz, sinAngle, cosdf(angle)) * dist * 20.0f;
            work->unk_3C -= D_8010AABC_chip_shot_challenge;
            work->unk_40 -= dist * 0.5f;
            if (work->unk_40 < 2.0f) {
                work->unk_3C = atan2df(dx, dz);
                work->unk_40 = 5.0f;
                D_8010AABC_chip_shot_challenge = 0.0f;
            }
        }
    } else {
        D_8010A8F0_chip_shot_challenge[D_8010A928_chip_shot_challenge[D_8010A844_chip_shot_challenge]] = dist;
        D_8010AABC_chip_shot_challenge = 0.0f;
    }
}

f32 func_80109DE0_chip_shot_challenge(omObjData *object, ChipShotChallengeSphere *sphere) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    Vec normal = { 0.0f, 1.0f, 0.0f };
    f32 y = sphere->pos.y;
    f32 floorY = func_8010A04C_chip_shot_challenge(sphere, &normal);
    f32 resultY = floorY;

    if (floorY < y - work->unk_34 || y + work->unk_34 <= floorY) {
        if (work->unk_38 == 1000.0f) {
            work->unk_38 = 0.0f;
        }
        resultY = y;
    }
    func_8010A3DC_chip_shot_challenge(object, &normal);
    func_80109EF0_chip_shot_challenge(object, sphere->pos.x, resultY, sphere->pos.z, floorY, &normal);
    return resultY;
}

void func_80109EF0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 scale = 0.5f;
    f32 height = y - floorY;

    if (floorY == -65536.0f) {
        Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        return;
    }
    if (height != 0.0f) {
        if (height > 400.0f) {
            scale = 0.1f;
        } else {
            scale = 0.5 - fabs(height) / 1000.0;
        }
        work->unk_53 = -1;
    }
    Hu3DModelPosSet(object->model[1], x, floorY + 3.0f, z);
    Hu3DModelScaleSet(object->model[1], scale, 0.5f, scale);
    MgShadowSlopeSet(object->model[1], normal);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

f32 func_8010A04C_chip_shot_challenge(ChipShotChallengeSphere *sphere, Vec *normal) {
    Vec pos;
    Vec tmp;
    Vec dir;
    omObjData *object;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 x, y, z;
    f32 floorY;
    f32 hitY;
    s16 model;
    u8 transformed;

    D_8010AAA0_chip_shot_challenge = 0;
    object = mgMapObjTbl[0];
    x = sphere->pos.x;
    y = sphere->pos.y;
    z = sphere->pos.z;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &pos, object);
    floorY = -65536.0f;
    model = object->model[0];
    points = (Hu3DPoint *)Hu3DData[model].hmf->unk50;
    Hu3DQuadPoolCollect(model, &mgQuadPool, MgFloorFaceFilter, &pos);
    for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL; quad = Hu3DQuadPoolNext(&mgQuadPool)) {
        transformed = FALSE;
        if (Hu3DData[model].pos.x != 0.0f || Hu3DData[model].pos.y != 0.0f ||
            Hu3DData[model].pos.z != 0.0f || Hu3DData[model].rot.x != 0.0f ||
            Hu3DData[model].rot.y != 0.0f || Hu3DData[model].rot.z != 0.0f) {
            tmp.x = x;
            tmp.y = y + 10.0f;
            tmp.z = z;
            MgMtxPosMult(mgMapInvMtx, &tmp);
            dir.x = tmp.x - pos.x;
            dir.y = tmp.y - pos.y;
            dir.z = tmp.z - pos.z;
            MapVecNormalize(&dir);
            MgFaceRayCross(pos.x, pos.y, pos.z, points, quad, &dir, &pos);
            MgMtxPosYMult(mgMapMtx, &pos);
            hitY = pos.y;
            transformed = TRUE;
        } else {
            hitY = MapCalcPoint(pos.x, pos.y, pos.z, points, quad);
        }
        if (floorY <= hitY && hitY < y + 150.0f) {
            D_8010AAA0_chip_shot_challenge = 1;
            floorY = hitY;
            if (normal != NULL) {
                MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], normal);
                if (transformed == TRUE) {
                    tmp.x = normal->x;
                    tmp.y = normal->y;
                    tmp.z = normal->z;
                    MgMtxDirMult(mgMapMtx, &tmp);
                    normal->x = tmp.x;
                    normal->y = tmp.y;
                    normal->z = tmp.z;
                    MapVecNormalize(normal);
                }
            }
        }
    }
    return floorY;
}

void func_8010A3DC_chip_shot_challenge(omObjData *object, Vec *arg1) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);

    if (D_8010AAA0_chip_shot_challenge == 1 && work->unk_38 == 1000.0f) {
        work->unk_5C = arg1->x * D_8010A834_chip_shot_challenge;
        work->unk_60 = arg1->y;
        work->unk_64 = arg1->z * D_8010A834_chip_shot_challenge;
    } else {
        work->unk_5C = 0.0f;
        work->unk_60 = 0.0f;
        work->unk_64 = 0.0f;
    }
}

void func_8010A454_chip_shot_challenge(omObjData *object, s32 *stickX, s32 *stickY, s32 *buttons) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 dist;
    s32 playerIndex;
    s32 difficulty;

    if (GwPlayer[work->playerIndex].stat & 1) {
        *buttons = 0;
        *stickY = 0;
        *stickX = 0;
        x = D_8010AAA4_chip_shot_challenge.x;
        y = D_8010AAA4_chip_shot_challenge.y;
        z = D_8010AAA4_chip_shot_challenge.z;
        playerIndex = work->playerIndex;
        difficulty = GwPlayer[playerIndex].cpu_difficulty;
        if (D_8010A984_chip_shot_challenge[playerIndex] == 1000.0f) {
            angle = (rand8() - 127.0f) / 128.0f * 5.0f * D_8010A9A4_chip_shot_challenge[difficulty];
            D_8010A984_chip_shot_challenge[playerIndex] = angle;
        }
        if (D_8010A994_chip_shot_challenge[playerIndex] == 1000.0f) {
            dist = (rand8() - 127.0f) / 128.0f * 10.0f * D_8010A9A4_chip_shot_challenge[difficulty];
            D_8010A994_chip_shot_challenge[playerIndex] = dist;
        }
        dist = HuSqrtf(x * x + y * y + z * z);
        angle = atan2df(x, z) + D_8010A984_chip_shot_challenge[playerIndex];
        if (angle < 0.0f) {
            angle += 180.0f;
        } else {
            angle -= 180.0f;
        }
        if (fabs(angle - work->unk_3C) > 1.0) {
            if (work->unk_3C < angle) {
                *stickX = -30;
            }
            if (angle < work->unk_3C) {
                *stickX = 30;
            }
        }
        dist = (dist - 150.0f) / 10.0f + D_8010A994_chip_shot_challenge[playerIndex];
        dist *= 1.1f;
        if (dist < 65.0f) {
            dist = 65.0f;
        }
        if (dist > 100.0f) {
            dist = 100.0f;
        }
        if (fabs(dist - work->unk_40) > 10.0) {
            *stickY = !(work->unk_40 < dist) ? 30 : -30;
        }
        if (*stickX == 0 && *stickY == 0) {
            *buttons |= 0x8000;
        }
    }
}
