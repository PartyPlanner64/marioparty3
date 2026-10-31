#include "common.h"
#include "game/pause.h"
#include "mallocblock.h"
#include "overlays/minigame.h"

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

extern s32 D_8010AAA0_chip_shot_challenge;
extern s32 D_8010A824_chip_shot_challenge;
extern f32 D_8010A828_chip_shot_challenge;
extern f32 D_8010A82C_chip_shot_challenge;
extern f32 D_8010A970_chip_shot_challenge;
extern f32 D_8010A974_chip_shot_challenge;
extern f32 D_8010A834_chip_shot_challenge;
extern Vec D_8010AAA4_chip_shot_challenge;
extern s32 D_8010A840_chip_shot_challenge;
extern s16 D_8010A846_chip_shot_challenge;
extern s32 D_8010AAC0_chip_shot_challenge;
extern s32 D_8010AAC4_chip_shot_challenge;
extern s32 D_8010AAC8_chip_shot_challenge;
extern s32 D_8010AACC_chip_shot_challenge;
extern f32 D_800D5410_main;
extern f32 D_800D51FC_main;
extern s16 D_8010AAD2_chip_shot_challenge[];
extern s32 D_8010AAD8_chip_shot_challenge[4];
extern s16 D_8010AAE8_chip_shot_challenge;
extern omObjData *D_8010AAF0_chip_shot_challenge;
extern f32 D_8010A954_chip_shot_challenge;
extern f32 D_8010A984_chip_shot_challenge[4];
extern f32 D_8010A994_chip_shot_challenge[4];
extern f32 D_8010A9A4_chip_shot_challenge[];
extern s32 D_8010A958_chip_shot_challenge;
extern s32 D_8010A928_chip_shot_challenge[4];
extern s32 D_8010A83C_chip_shot_challenge;
extern s32 D_8010A844_chip_shot_challenge;
extern f32 D_8010A8F0_chip_shot_challenge[];
extern f32 D_8010AABC_chip_shot_challenge;
extern HuMtx4F D_800EBE30_minigame;
extern HuMtx4F D_800EC240_minigame;
extern Hu3DQuadPool D_800EBEB0_minigame;
extern f32 D_800EB77C_minigame;
extern f32 D_800EB73C_minigame;
extern f32 D_800EB72C_minigame;
extern f32 D_8010AA60_chip_shot_challenge;
extern Vec D_8010AA64_chip_shot_challenge;
extern Vec D_8010AA70_chip_shot_challenge;
extern Vec D_8010AA7C_chip_shot_challenge;
extern f32 D_8010A938_chip_shot_challenge;
extern f32 D_8010A93C_chip_shot_challenge;
extern f32 D_8010A940_chip_shot_challenge;
extern f32 D_8010A944_chip_shot_challenge;
extern s32 D_8010A948_chip_shot_challenge;
extern s32 D_8010A820_chip_shot_challenge;
extern f32 D_8010A838_chip_shot_challenge;
extern s32 D_8010A848_chip_shot_challenge;
extern f32 D_8010A978_chip_shot_challenge;
extern f32 D_8010A97C_chip_shot_challenge;
extern s32 D_8010A980_chip_shot_challenge;
extern f32 D_800EB720_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_8010AAB0_chip_shot_challenge;
extern s32 D_8010AAD0_chip_shot_challenge;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern D_80111B50_vine_with_me_Struct D_8010A900_chip_shot_challenge;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern s16 D_800EB934_minigame;
extern f32 D_8010A87C_chip_shot_challenge[5];
extern f32 D_8010A890_chip_shot_challenge[5];
extern f32 D_8010A8A4_chip_shot_challenge[5];
extern f32 D_8010A8B8_chip_shot_challenge[5];
extern f32 D_8010A8CC_chip_shot_challenge[5];
extern s32 D_8010A8E0_chip_shot_challenge[4];
extern s32 D_8010A94C_chip_shot_challenge;
extern s32 D_8010A950_chip_shot_challenge;
extern f32 D_8010AA88_chip_shot_challenge;
extern Vec D_8010AA8C_chip_shot_challenge;
extern u8 D_8010A96C_chip_shot_challenge;
extern s32 D_8010AA98_chip_shot_challenge;
extern s32 D_8010AA9C_chip_shot_challenge;
extern f32 D_8010A830_chip_shot_challenge;
extern s32 D_8010A84C_chip_shot_challenge[4][3];

f32 func_800202A8_main(f32 angle);
u16 func_8000B0D4_main(s32 arg0, s32 arg1);
void func_800E149C_minigame(omObjData *, s32, s32);
void func_800E3584_minigame(s16);
void func_800E3628_minigame(s16, Vec *);
void func_80013390_main(s16 model, s32 arg1, s32 arg2, void (*callback)(s16));
s16 HmfAnimRead(HmfData *, s32, char *);
s32 func_8000B638_main(void);
void espAttrSet(u16 arg0, u16 arg1);
s32 func_80105DE0_chip_shot_challenge(s32 playerIndex);
void func_80021BE0_main(Hu3DQuadPool *pool, u16 numQuads);
void func_800E1490_minigame(u16 arg0);
void func_80106B84_chip_shot_challenge(omObjData *object);
void func_8010646C_chip_shot_challenge(omObjData *object);
void func_80107048_chip_shot_challenge(void);
void func_80107960_chip_shot_challenge(s16 value);
void func_80107BB0_chip_shot_challenge(void);
void func_80107E94_chip_shot_challenge(void);
f32 func_80109AD0_chip_shot_challenge(omObjData *object, f32 x, f32 y, f32 z);
void func_80088800_main(HuMtx4F mtx, f32 x, f32 y, f32 z);
void func_80017D24_main(f32 *mtx, f32 x, f32 y, f32 z);
void func_800E17D4_minigame(omObjData *object, f32 x, f32 y, f32 z);
void func_800E147C_minigame(omObjData *object);
void func_800E1468_minigame(omObjData *object);
void func_800E1370_minigame(omObjData *object, s32 arg1, f32 arg2);
void func_800E1304_minigame(omObjData *object, f32 arg1);
void func_800E1310_minigame(omObjData *object, f32 arg1);
void func_800E131C_minigame(omObjData *object, f32 arg1);
void func_801085C0_chip_shot_challenge(omObjData *object);
void func_80108638_chip_shot_challenge(omObjData *object);
void func_801086B4_chip_shot_challenge(omObjData *object);
void func_80108730_chip_shot_challenge(omObjData *object);
void func_80107520_chip_shot_challenge(omObjData *object);
void func_80108108_chip_shot_challenge(omObjData *object);
f32 func_800E2ED4_minigame(f32 x, f32 z, f32 sinAngle, f32 cosAngle);
void func_800E28BC_minigame(HuMtx4F arg0, HuMtx4F arg1, Vec *pos, omObjData *object);
void func_800E2B58_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2BD4_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1);
s32 func_800DB704_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
void func_80021C14_main(s16 model, Hu3DQuadPool *pool, s32 (*callback)(s32, s16 *, Hu3DPoint *, Vec *), Vec *pos);
Hu3DQuad *func_80022198_main(Hu3DQuadPool *pool);
f32 func_800204F4_main(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad);
s32 func_8002038C_main(Hu3DPoint *p0, Hu3DPoint *p1, Hu3DPoint *p2, Vec *out);
s32 func_800D8818_minigame(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out);
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
void func_800E6F0C_minigame(s32 arg0);

void func_801059A0_chip_shot_challenge(void) {
    u8 camIndex;
    u16 sprite;
    s32 rank;
    s32 i;

    Hu3DAnimInit(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 40.0f, 80.0f, 8000.0f);
    HmfLightDirSet(1, 32.0f, 99.0f, 59.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 12, 0, -1, func_80106B84_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_801085C0_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_80108638_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_801086B4_chip_shot_challenge);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(2, 10, 10, -1, func_80108730_chip_shot_challenge);
    omAddObj(3, 25, 10, -1, func_80107520_chip_shot_challenge);
    D_8010AAF0_chip_shot_challenge = omAddObj(3, 10, 0, -1, func_80108108_chip_shot_challenge);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), 0xA0);
    sprite = espEntry(func_8000B838_main(0x3C001E), 0, 1);
    espDispOn(sprite);
    espPosSet(sprite, 160, 120);
    espAttrSet(sprite, 0x4000);
    WipeCreateIn(0xFF, 0x10);
    func_800E5EA0_minigame(&D_8010A900_chip_shot_challenge);
    D_800EB930_minigame = 45;
    D_800EB932_minigame = 60;
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
    s32 time = func_800E6E9C_minigame();
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
        func_8001C258_main(object->model[6], 4, 0);
        func_8001C258_main(object->model[4], 4, 0);
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
        func_800202FC_main(&D_8010AA64_chip_shot_challenge);
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
                func_8004AC98_main(0x3DE, 0);
                D_8010A948_chip_shot_challenge = 0;
            }
        }
    } else {
        func_8001C258_main(object->model[6], 4, 4);
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
        D_8010A944_chip_shot_challenge += D_800EB72C_minigame;
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

    if (omPauseChk() + D_800D6A90_main != 0) {
        return;
    }
    time = func_800E6E9C_minigame();
    switch (func_800E6F40_minigame()) {
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
            func_800202FC_main(&D_8010AA8C_chip_shot_challenge);
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
                    D_8010A900_chip_shot_challenge.unk06 = D_8010A94C_chip_shot_challenge - 1;
                    for (i = 0, j = 0; i < 4; i++) {
                        if (D_8010A8F0_chip_shot_challenge[i] == 0.0f) {
                            D_8010A900_chip_shot_challenge.unk18[j++] = i;
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
                        D_8010A900_chip_shot_challenge.unk06 = 4;
                    } else {
                        D_8010A900_chip_shot_challenge.unk06 = 0;
                        D_8010A900_chip_shot_challenge.unk18[0] = D_8010A950_chip_shot_challenge;
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
            if (D_800EB934_minigame == 1) {
                for (i = 0; i < 4; i++) {
                    player = D_800EC598_minigame[i];
                    if (D_8010A8E0_chip_shot_challenge[D_8010A928_chip_shot_challenge[i]] == 0) {
                        work = player->data;
                        func_800E5690_minigame(player, 5);
                        chr = GwPlayer[work->playerIndex].chr;
                        chrData = D_800A178C_main[chr][0];
                        func_80017954_main(player->model[0], 2, chr, player->model[4]);
                        func_80045ED0_main(chrData | 0x2F);
                        GwPlayer[work->playerIndex].bonusCoin += 10;
                    } else {
                        func_800E5690_minigame(player, 6);
                    }
                }
            }
            break;
        case 5:
            WipeCreateOut(0, 20);
            object->func = func_80105E8C_chip_shot_challenge;
            break;
    }
    func_800E3628_minigame(object->model[4], &D_8010AAB0_chip_shot_challenge);
    for (i = 0; i < 5; i++) {
        x = sindf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i];
        Hu3DModelPosSet(object->model[7 + i], x, D_8010A890_chip_shot_challenge[i],
                        cosdf(D_8010A87C_chip_shot_challenge[i]) * D_8010A8A4_chip_shot_challenge[i] - 1000.0f);
        Hu3DModelRotSet(object->model[7 + i], 0.0f, CRot.y, 0.0f);
        scale = sindf(D_8010A8CC_chip_shot_challenge[i]) * 0.25f + 2.5f;
        Hu3DModelScaleSet(object->model[7 + i], scale, scale, scale);
        D_8010A8CC_chip_shot_challenge[i] =
            func_800202A8_main(D_8010A8B8_chip_shot_challenge[i] * 30.0f + D_8010A8CC_chip_shot_challenge[i]);
        D_8010A87C_chip_shot_challenge[i] =
            func_800202A8_main(D_8010A87C_chip_shot_challenge[i] + D_8010A8B8_chip_shot_challenge[i]);
        if (D_8010A87C_chip_shot_challenge[i] > 260.0f) {
            D_8010A87C_chip_shot_challenge[i] = 100.0f;
        }
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        ((ChipShotChallengeWork *)D_800EC598_minigame[i]->data)->unk_60 = CRot.y;
    }
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
        object->func = func_80105E8C_chip_shot_challenge;
    }
}

void func_80106B84_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeCourseWork *work;
    ChipShotChallengeSphere sphere;
    f32 angle;
    f32 dist;
    s32 tag = 0x2B9;

    D_800EB73C_minigame = 20.0f;
    if (rand8() > 128) {
        object->model[0] = func_8000B0A0_main(0x3C0000, tag);
    } else {
        object->model[0] = func_8000B0A0_main(0x3C0001, tag);
    }
    object->model[1] = func_8000B0A0_main(0x3C0002, tag);
    object->model[2] = func_8000B0A0_main(0x3C0003, tag);
    object->model[3] = func_8000B0A0_main(0x3C0004, tag);
    object->model[4] = func_8000B0A0_main(0x3C0005, tag);
    object->model[5] = func_8000B0A0_main(0x3C0009, tag);
    func_800E3584_minigame(object->model[4]);
    D_8010AAD0_chip_shot_challenge = object->model[6] = func_8000B0A0_main(0xA0089, tag);
    object->model[7] = func_8000B0A0_main(0x210029, tag);
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
    work = HuMemAllocTag(sizeof(ChipShotChallengeCourseWork), 0x7918);
    object->data = work;
    memset(work, 0, sizeof(ChipShotChallengeCourseWork));
    object->func = func_8010646C_chip_shot_challenge;
    work->unk_03 = 1;
    func_800E147C_minigame(object);
    func_800E1370_minigame(object, 1, 0.0f);
    func_800E1304_minigame(object, 0.1f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 25.0f);
    func_800E1468_minigame(object);
    work->unk_04 = 0;
    omSetStatBit(object, 0xA0);
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
        model = func_8000B108_main(files[i], 0xAA9);
        D_8010AAD8_chip_shot_challenge[i] = model;
        func_8003302C_main(HmfAnimRead(HmfModelData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        func_8001C448_main(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, 0, func_801073D4_chip_shot_challenge);
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
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
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
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
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

    D_800D51FC_main = D_800D5410_main = 0.0f;
    object->model[1] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[2] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[3] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[4] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[5] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[6] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[7] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[8] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[9] = func_8000B0A0_main(0x3C0007, 0xAD9);
    object->model[10] = func_8000B0A0_main(0x3C0007, 0xAD9);
    D_800D5410_main = 1.0f;
    D_800D51FC_main = 1.0f;
    object->func = func_801091E8_chip_shot_challenge;

    data = DataRead(0x2D);
    image1 = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x3C001F);
    image2 = HuSprAnimRead(data);
    DataClose(data);

    group = D_8010AAC0_chip_shot_challenge = HuSprGrpCreate(4, 5);
    func_80055024_main(group, 0, image1, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    HuSprPosSet(group, 0, 0x80, 0x64);
    HuSprPriSet(group, 0, 1);
    x = 15;
    for (i = 1; i < 4; i++) {
        HuSprPriSet(group, i, 1);
        func_80055024_main(group, i, image1, 0);
        HuSprPosSet(group, i, x, 0);
        HuSprAttrReset(group, i, 0xFFFF);
        HuSprAttrSet(group, i, 0x8000);
        if (i == 1) {
            x += 20;
        } else {
            x += 15;
        }
        func_800554C4_main(group, i, 0);
    }
    HuSprAttrReset(group, 2, 0x8000);

    group = D_8010AAC4_chip_shot_challenge = HuSprGrpCreate(2, 5);
    func_80055024_main(group, 0, image2, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x8000);
    HuSprPosSet(group, 0, 0x9F, 0x64);
    HuSprPriSet(group, 0, 1);
    HuSprPriSet(group, 1, 1);
    func_80055024_main(group, 1, image2, 0);
    HuSprPosSet(group, 1, 0x23, 0);
    HuSprAttrReset(group, 1, 0xFFFF);
    HuSprAttrSet(group, 1, 0x8000);
    func_800554C4_main(group, 1, 0);
    HuSprAttrReset(group, 2, 0x8000);

    D_8010AACC_chip_shot_challenge = func_8000B0A0_main(0x3C001D, 0xAD9);
    D_8010AAC8_chip_shot_challenge = func_8000B0A0_main(0x3C001C, 0xAD9);
}

void func_80107960_chip_shot_challenge(s16 value) {
    s16 digit;

    if ((s16)(value / 1000) != 0) {
        HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
        func_80055140_main(D_8010AAC0_chip_shot_challenge, 0, value / 1000, 0);
        func_800550F4_main(D_8010AAC0_chip_shot_challenge, 0, 1);
    }
    value -= (s16)(value / 1000) * 1000;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    digit = value / 100;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 1, digit, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 1, 1);
    value -= digit * 100;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    digit = value / 10;
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 2, digit, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 2, 1);
    value -= digit * 10;
    HuSprAttrReset(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    func_80055140_main(D_8010AAC0_chip_shot_challenge, 3, value, 0);
    func_800550F4_main(D_8010AAC0_chip_shot_challenge, 3, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 0, 1);
    HuSprAttrReset(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_80054FF8_main(D_8010AAC4_chip_shot_challenge, 1, 0);
}

void func_80107BB0_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&dir);
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
    Hu3DModelPosSet(D_8010AAD2_chip_shot_challenge[0], x, y, z);
    Hu3DModelPosSet(D_8010AAC8_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AAC8_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 0);
}

void func_80107E94_chip_shot_challenge(void) {
    Vec dir;
    f32 x, y, z;

    x = dir.x = D_8010AAF0_chip_shot_challenge->trans.x;
    dir.y = D_8010AAF0_chip_shot_challenge->trans.y;
    z = dir.z = D_8010AAF0_chip_shot_challenge->trans.z;
    func_800202FC_main(&dir);
    if (D_8010A840_chip_shot_challenge == 1) {
        func_8004AC98_main(0x3DC, D_8010A846_chip_shot_challenge);
    }
    if (D_8010A840_chip_shot_challenge < 31) {
        y = D_8010A840_chip_shot_challenge * 10.0f + -200.0f;
    } else {
        y = 100.0f;
    }
    x += dir.x * 200.0f;
    z += dir.z * 200.0f;
    Hu3DModelPosSet(D_8010AAD2_chip_shot_challenge[0], x, y, z);
    Hu3DModelPosSet(D_8010AACC_chip_shot_challenge, x, y, z);
    Hu3DModelRotSet(D_8010AAD2_chip_shot_challenge[0], 0.0f, CRot.y, 0.0f);
    Hu3DModelRotSet(D_8010AACC_chip_shot_challenge, 0.0f, CRot.y, 0.0f);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 0);
    func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 0);
}

void func_8010802C_chip_shot_challenge(void) {
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 1, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 2, 0x8000);
    HuSprAttrSet(D_8010AAC0_chip_shot_challenge, 3, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 0, 0x8000);
    HuSprAttrSet(D_8010AAC4_chip_shot_challenge, 1, 0x8000);
    func_8001C258_main(D_8010AACC_chip_shot_challenge, 4, 4);
    func_8001C258_main(D_8010AAC8_chip_shot_challenge, 4, 4);
    if (func_800E6E8C_minigame() >= 2) {
        func_8001C258_main(D_8010AAD2_chip_shot_challenge[0], 4, 4);
    }
}

void func_80108108_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeWork *work;
    s32 i;

    object->data = HuMemAllocTag(sizeof(ChipShotChallengeWork), 0x7918);
    memset(object->data, 0, sizeof(ChipShotChallengeWork));
    work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    object->model[0] = func_8000B0A0_main(0x3C0008, 0xAB9);
    object->model[1] = func_8000B0D4_main(9, 0xAB9);
    func_800E3584_minigame(object->model[1]);
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
    func_800E149C_minigame(object, 0, 2);
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelScaleSet(object->model[1], 0.4f, 0.4f, 0.4f);
    object->func = func_801094D8_chip_shot_challenge;
}

func_800E1BA8_minigame_ObjData *func_80108274_chip_shot_challenge(omObjData *object, s32 player) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;
    s32 chr;
    s32 model;
    s32 motion;
    s32 tag;

    motion = D_800A178C_main[GwPlayer[player].chr][2];
    model = D_800A178C_main[GwPlayer[player].chr][0];
    tag = 0xAA9;
    chr = GwPlayer[player].chr;
    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    data = HuMemAllocTag(0x15C, 0x7918);
    object->data = data;
    memset(data, 0, 0x15C);
    data->unkE8 = HuMemAllocTag(object->mtncnt * 3 * sizeof(s32), 0x7918);
    object->model[0] = func_8000B0A0_main(model | motion, tag);
    object->model[1] = func_8000B0A0_main(9, tag);
    func_80017790_main(object->model[0], 2, chr, func_80017B6C_main(chr, 2, 0));
    object->model[4] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
    func_800E5978_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5978_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5978_minigame(object, 2, func_80017BB8_main(chr, 0x5E), 1, 0);
    func_800E5978_minigame(object, 3, func_80017BB8_main(chr, 0x5F), 0, 0);
    func_800E5978_minigame(object, 5, func_80017BB8_main(chr, 0x2F), 0, 0);
    func_800E5978_minigame(object, 6, func_80017BB8_main(chr, 0x36), 0, 0);
    object->model[2] = func_8000B0A0_main((chr + 10) | 0x3C0000, tag);
    object->model[3] = func_8000B0A0_main((chr + 0x12) | 0x3C0000, 0x4AD);
    func_8001EF6C_main(object->model[2], object->model[0], "item_hook");
    func_8001C258_main(object->model[2], 0x4000, 0x4000);
    func_8001FA68_main(object->model[3]);
    func_8001F9E4_main(object->model[3], 0x80);
    data->unk40 = 50.0f;
    object->func = func_801087AC_chip_shot_challenge;
    data->unk50 = 0;
    func_8001C5B4_main(object->model[0], object->motion[0]);
    func_8001C814_main(object->model[0], 2, 2);
    object->rot.y = 90.0f;
    data->unk59 = player;
    data->unk57 = GwPlayer[player].pad;
    return data;
}

void func_801085C0_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[0]);

    object->trans.x = -300.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 0;
}

void func_80108638_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[1]);

    object->trans.x = -600.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 1;
}

void func_801086B4_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[2]);

    object->trans.x = -900.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 2;
}

void func_80108730_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = func_80108274_chip_shot_challenge(object, D_8010A928_chip_shot_challenge[3]);

    object->trans.x = -1200.0f;
    object->trans.z = 20.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    data->unk53[0] = 3;
}

void func_801087AC_chip_shot_challenge(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = OM_GET_DATA_PTR(object, func_800E1BA8_minigame_ObjData);
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
    if (func_800E6E8C_minigame() == 2) {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        buttons = (u16)D_800CDA7C_main[pad];
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
                func_800E5690_minigame(object, 1);
                data->unk50 = 1;
                break;
            case 1:
                object->trans.x += 5.0f;
                if (object->trans.x > -90.0f) {
                    func_800E5690_minigame(object, 2);
                    data->unk50 = 2;
                    D_8010A824_chip_shot_challenge = 1;
                    object->trans.x = -90.0f;
                    GMesCreate(0x1A, 10, 0xA0, 0x18);
                    D_8010AA9C_chip_shot_challenge = 300;
                }
                func_800E3628_minigame(D_8010AAF0_chip_shot_challenge->model[1], &pos);
                D_8010A96C_chip_shot_challenge -= 5;
                if (D_8010A96C_chip_shot_challenge < 100) {
                    D_8010A96C_chip_shot_challenge = 100;
                }
                break;
            case 2:
                func_8003F578_main(D_8010AA9C_chip_shot_challenge / 30 + 1);
                if ((buttons & 0x8000) || D_8010AA9C_chip_shot_challenge == 0) {
                    func_800E5690_minigame(object, 3);
                    data->unk50 = 3;
                    D_8010A824_chip_shot_challenge = 0;
                    D_8010AA98_chip_shot_challenge = 0;
                    func_8003F5C0_main();
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
                    func_8004AC98_main(0x3DA, player);
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
                    func_800E6F0C_minigame(3);
                    for (i = 0; i < 4; i++) {
                        D_800EC598_minigame[i]->trans.x = D_8010A84C_chip_shot_challenge[i][0];
                        D_800EC598_minigame[i]->trans.y = D_8010A84C_chip_shot_challenge[i][1];
                        D_800EC598_minigame[i]->trans.z = D_8010A84C_chip_shot_challenge[i][2];
                        D_800EC598_minigame[i]->rot.y = 0.0f;
                        Hu3DModelPosSet(D_800EC598_minigame[i]->model[1], D_8010A84C_chip_shot_challenge[i][0],
                                        D_8010A84C_chip_shot_challenge[i][1], D_8010A84C_chip_shot_challenge[i][2]);
                        func_8001C258_main(D_800EC598_minigame[i]->model[0], 4, 0);
                        func_8001C258_main(D_800EC598_minigame[i]->model[1], 4, 0);
                        func_8001C258_main(D_800EC598_minigame[i]->model[2], 4, 4);
                        if (D_8010A848_chip_shot_challenge != 1) {
                            func_8001C258_main(object->model[3], 4, 0);
                            Hu3DModelPosSet(object->model[3], D_8010AAF0_chip_shot_challenge->trans.x,
                                            D_8010AAF0_chip_shot_challenge->trans.y - 50.0f,
                                            D_8010AAF0_chip_shot_challenge->trans.z);
                        }
                    }
                    func_8001C258_main(D_8010AAF0_chip_shot_challenge->model[0], 4, 4);
                    func_8001C258_main(D_8010AAF0_chip_shot_challenge->model[1], 4, 4);
                } else {
                    D_800EC598_minigame[D_8010A844_chip_shot_challenge]->trans.x = -200.0f;
                    data->unk50 = 5;
                    Hu3DModelPosSet(D_8010AAF0_chip_shot_challenge->model[1], 0.0f, 3.0f, 0.0f);
                    func_800E3628_minigame(D_8010AAF0_chip_shot_challenge->model[1], &pos);
                    func_8001C258_main(D_8010AAF0_chip_shot_challenge->model[1], 4, 0);
                    if (D_8010A848_chip_shot_challenge != 1) {
                        func_8001C258_main(object->model[3], 4, 0);
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
                    func_8001C258_main(object->model[0], 4, 4);
                    func_8001C258_main(object->model[1], 4, 4);
                    func_8001C258_main(object->model[2], 4, 4);
                    Center.x = 0.0f;
                    Center.y = 200.0f;
                    Center.z = 0.0f;
                    CRot.y = 0.0f;
                }
                func_800E5690_minigame(object, 0);
                D_8010A840_chip_shot_challenge = 0;
                D_8010A828_chip_shot_challenge = D_8010A82C_chip_shot_challenge = 0.0f;
                break;
            case 5:
            case 6:
                break;
        }
        Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    }
    func_800E4E30_minigame(object);
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
            func_8001C258_main(object->model[i + 1], 4, 0);
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
        D_8010A970_chip_shot_challenge = func_800202A8_main(D_8010A970_chip_shot_challenge + 10.0f);
    } else {
        for (i = 0; i < 20; i++) {
            func_8001C258_main(object->model[i + 1], 4, 4);
        }
    }
}

void func_801094D8_chip_shot_challenge(omObjData *object) {
    ChipShotChallengeWork *work = OM_GET_DATA_PTR(object, ChipShotChallengeWork);
    f32 x, y, z;
    f32 angle;
    f32 floorY;
    u8 bounce = TRUE;

    func_80088800_main(HmfModelData[object->model[0]].mtx, 0.0f, 30.0f, 0.0f);
    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
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
        work->unk_38 += D_800EB72C_minigame;
        if (work->unk_38 > D_800EB720_minigame) {
            work->unk_38 = D_800EB720_minigame;
        }
        if (D_8010A83C_chip_shot_challenge == 1) {
            if (y <= D_8010AAA4_chip_shot_challenge.y - 40.0f) {
                work->unk_40 = 0.0f;
            }
            func_8001C258_main(object->model[1], 4, 4);
        } else {
            floorY = func_80109AD0_chip_shot_challenge(object, x, y, z);
            if (y < floorY) {
                y = floorY;
                func_8004AC98_main(0x3DD, D_8010A846_chip_shot_challenge);
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
    func_800E17D4_minigame(object, x + D_800EBE2C_minigame, y, z + D_800EC5D8_minigame);
    D_8010A978_chip_shot_challenge -= cosdf(angle) * work->unk_40 + D_800EC5D8_minigame;
    D_8010A978_chip_shot_challenge = func_800202A8_main(D_8010A978_chip_shot_challenge);
    D_8010A97C_chip_shot_challenge = func_800202A8_main(D_8010A97C_chip_shot_challenge);
    object->rot.y = angle;
    func_80017D24_main(HmfModelData[object->model[0]].mtx[0], D_8010A978_chip_shot_challenge, 0.0f, 0.0f);
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
                func_8004AC98_main(0x3DE, D_8010A846_chip_shot_challenge);
                D_8010A980_chip_shot_challenge = 0;
                omVibrate(OM_GET_DATA_PTR(D_800EC598_minigame[D_8010A844_chip_shot_challenge], ChipShotChallengeWork)
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
    func_800E1BA8_minigame_ObjData *data = object->data;
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
            D_8010AABC_chip_shot_challenge = func_800E2ED4_minigame(dx, dz, sinAngle, cosdf(angle)) * dist * 20.0f;
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
        func_8001C258_main(object->model[1], 4, 4);
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
    func_800E3628_minigame(object->model[1], normal);
    func_8001C258_main(object->model[1], 4, 0);
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
    object = D_800EC1C0_minigame[0];
    x = sphere->pos.x;
    y = sphere->pos.y;
    z = sphere->pos.z;
    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &pos, object);
    floorY = -65536.0f;
    model = object->model[0];
    points = (Hu3DPoint *)HmfModelData[model].hmf->unk50;
    func_80021C14_main(model, &D_800EBEB0_minigame, func_800DB704_minigame, &pos);
    for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL; quad = func_80022198_main(&D_800EBEB0_minigame)) {
        transformed = FALSE;
        if (HmfModelData[model].pos.x != 0.0f || HmfModelData[model].pos.y != 0.0f ||
            HmfModelData[model].pos.z != 0.0f || HmfModelData[model].rot.x != 0.0f ||
            HmfModelData[model].rot.y != 0.0f || HmfModelData[model].rot.z != 0.0f) {
            tmp.x = x;
            tmp.y = y + 10.0f;
            tmp.z = z;
            func_800E2BD4_minigame(D_800EBE30_minigame, &tmp);
            dir.x = tmp.x - pos.x;
            dir.y = tmp.y - pos.y;
            dir.z = tmp.z - pos.z;
            func_800202FC_main(&dir);
            func_800D8818_minigame(pos.x, pos.y, pos.z, points, quad, &dir, &pos);
            func_800E2C68_minigame(D_800EC240_minigame, &pos);
            hitY = pos.y;
            transformed = TRUE;
        } else {
            hitY = func_800204F4_main(pos.x, pos.y, pos.z, points, quad);
        }
        if (floorY <= hitY && hitY < y + 150.0f) {
            D_8010AAA0_chip_shot_challenge = 1;
            floorY = hitY;
            if (normal != NULL) {
                func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], normal);
                if (transformed == TRUE) {
                    tmp.x = normal->x;
                    tmp.y = normal->y;
                    tmp.z = normal->z;
                    func_800E2B58_minigame(D_800EC240_minigame, &tmp);
                    normal->x = tmp.x;
                    normal->y = tmp.y;
                    normal->z = tmp.z;
                    func_800202FC_main(normal);
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
