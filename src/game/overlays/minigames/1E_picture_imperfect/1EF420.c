#include "common.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/input.h"
#include "game/object.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "game/sprite.h"
#include "gcc/memory.h"
#include "game/wipe.h"
#include "math.h"
#include "game/overlays/minigame.h"

typedef struct PictureImperfectWork {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
    /* 0x07 */ s8 unk07;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ char unk1A[0x2];
} PictureImperfectWork; // Size 0x1C

typedef struct PictureImperfectGameData {
    /* 0x00 */ u8 unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ u8 unk0C[0xA8];
} PictureImperfectGameData; // Size 0xB4

typedef struct PictureImperfectScorePos {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} PictureImperfectScorePos; // Size 0x4

// Grouped BSS variables; individual fields are aliased in undefined_syms.txt.
typedef struct PictureImperfectBssA110 {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ s8 unk02[4];
    /* 0x06 */ s8 unk06[4];
    /* 0x0A */ s16 unk0A[4];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
} PictureImperfectBssA110; // Size 0x18

typedef struct PictureImperfectBssA230 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02[5];
    /* 0x0C */ s16 unk0C[5];
    /* 0x16 */ s16 unk16[5];
    /* 0x20 */ s16 unk20[5];
    /* 0x2A */ s16 unk2A[5];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E[4];
    /* 0x46 */ s16 unk46[4];
    /* 0x4E */ s16 unk4E[4];
    /* 0x56 */ s16 unk56[4];
    /* 0x5E */ s16 unk5E[4];
    /* 0x66 */ s16 unk66[4];
    /* 0x6E */ s16 unk6E[4];
    /* 0x76 */ s16 unk76;
    /* 0x78 */ s16 unk78;
    /* 0x7A */ s16 unk7A;
} PictureImperfectBssA230; // Size 0x7C

extern u32 D_800A178C_main[][6];
extern s32 D_800A1790_main[][6];
extern u8 D_800CE20A_main;
extern u8 D_800D6A90_main;

s16 D_80109FE0_picture_imperfect = -1;
s16 D_80109FE2_picture_imperfect = 1;
u8 D_80109FE4_picture_imperfect = 0;
PictureImperfectScorePos D_80109FE8_picture_imperfect[4] = { { 80, 60 }, { 240, 60 }, { 80, 180 }, { 240, 180 } };
s8 D_80109FF8_picture_imperfect[4] = { -1, -1, -1, -1 };
s8 D_80109FFC_picture_imperfect[4][5] = {
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1 }
};
s32 D_8010A010_picture_imperfect = 0;
s8 D_8010A014_picture_imperfect = 0;
PictureImperfectScorePos D_8010A018_picture_imperfect[4] = { { 59, 55 }, { 219, 55 }, { 59, 175 }, { 219, 175 } };
s8 D_8010A028_picture_imperfect = 0;
s32 D_8010A02C_picture_imperfect = 0;
u8 D_8010A030_picture_imperfect[4][5] = {
    { 0, 1, 2, 3, 4 },
    { 4, 2, 0, 3, 1 },
    { 2, 3, 1, 4, 0 },
    { 1, 4, 2, 0, 3 }
};
u32 D_8010A044_picture_imperfect = 0;
s8 D_8010A048_picture_imperfect[8] = { -20, -10, 0, 10, 20, 0, 0, 0 };
f32 D_8010A050_picture_imperfect = 1.0f;
u8 D_8010A054_picture_imperfect = 0;
u8 D_8010A055_picture_imperfect = 0xFF;
u8 D_8010A056_picture_imperfect = 0;

PictureImperfectBssA110 pictureImperfectBssA110 BSS;
MinigameFlow D_8010A128_picture_imperfect BSS;
u8 D_8010A150_picture_imperfect BSS;
u8 D_8010A151_picture_imperfect BSS;
s16 D_8010A152_picture_imperfect BSS;
s16 D_8010A154_picture_imperfect BSS;
s16 D_8010A156_picture_imperfect BSS;
s16 D_8010A158_picture_imperfect BSS;
s16 D_8010A15A_picture_imperfect BSS;
s16 D_8010A15C_picture_imperfect[4] BSS;
u8 D_8010A164_picture_imperfect[4] BSS; /* Unreferenced. */
s16 D_8010A168_picture_imperfect[4][5] BSS;
s16 D_8010A190_picture_imperfect[4][5] BSS;
s16 D_8010A1B8_picture_imperfect[4][5] BSS;
s16 D_8010A1E0_picture_imperfect[4][5] BSS;
s16 D_8010A208_picture_imperfect[4][5] BSS;
PictureImperfectBssA230 pictureImperfectBssA230 BSS;
s8 D_8010A2AC_picture_imperfect[5] BSS;

/* Fields of pictureImperfectBssA110, D_8010A128_picture_imperfect and pictureImperfectBssA230 (aliased in undefined_syms.txt). */
extern s8 D_8010A110_picture_imperfect;
extern s8 D_8010A111_picture_imperfect;
extern s8 D_8010A112_picture_imperfect[4];
extern s8 D_8010A116_picture_imperfect[4];
extern s16 D_8010A11A_picture_imperfect[4];
extern s16 D_8010A122_picture_imperfect;
extern s16 D_8010A124_picture_imperfect;
extern u8 D_8010A140_picture_imperfect[4];
extern s16 D_8010A230_picture_imperfect;
extern s16 D_8010A232_picture_imperfect[5];
extern s16 D_8010A23C_picture_imperfect[5];
extern s16 D_8010A246_picture_imperfect[5];
extern s16 D_8010A250_picture_imperfect[5];
extern s16 D_8010A25A_picture_imperfect[5];
extern s16 D_8010A264_picture_imperfect;
extern s16 D_8010A266_picture_imperfect;
extern s16 D_8010A268_picture_imperfect;
extern s16 D_8010A26A_picture_imperfect;
extern s16 D_8010A26C_picture_imperfect;
extern s16 D_8010A26E_picture_imperfect[4];
extern s16 D_8010A276_picture_imperfect[4];
extern s16 D_8010A27E_picture_imperfect[4];
extern s16 D_8010A286_picture_imperfect[4];
extern s16 D_8010A28E_picture_imperfect[4];
extern s16 D_8010A296_picture_imperfect[4];
extern s16 D_8010A29E_picture_imperfect[4];
extern s16 D_8010A2A6_picture_imperfect;
extern s16 D_8010A2A8_picture_imperfect;
extern s16 D_8010A2AA_picture_imperfect;

void func_80105BA8_picture_imperfect(void);
void func_80105E68_picture_imperfect(MinigameFlow *flow);
void func_80105EF4_picture_imperfect(void);
void func_80106154_picture_imperfect(omObjData *object);
void func_8010629C_picture_imperfect(omObjData *object);
void func_801081E4_picture_imperfect(omObjData *object);
void func_801083C0_picture_imperfect(s8 player);
void func_80108688_picture_imperfect(omObjData *object);
void func_80108A64_picture_imperfect(PictureImperfectWork *work, s8 player);
void func_80108C20_picture_imperfect(PictureImperfectWork *work, s8 player);
void func_80109284_picture_imperfect(PictureImperfectWork *work, s8 player);
void func_80109608_picture_imperfect(omObjData *object);
void func_80107820_picture_imperfect(omObjData *object);
void func_80109AC4_picture_imperfect(omObjData *object);

void func_801059A0_picture_imperfect(void) {
    omObjData *object;
    s32 i;

    func_8001FE20_main(0x20);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x40);
    omInitObjMan(0x20, 0);
    func_8004A208_main();
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E1804_minigame();
    func_80105EF4_picture_imperfect();
    D_8010A150_picture_imperfect = 2 - D_800CE20A_main;
    func_80105BA8_picture_imperfect();
    func_80105E68_picture_imperfect(&D_8010A128_picture_imperfect);
    func_800E5EA0_minigame(&D_8010A128_picture_imperfect);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x40);
    Hu3DGLightDirSet(1, 0.0f, 0.0f, 100.0f);
    D_8010A151_picture_imperfect = rand8() >> 6;
    object = omAddObj(0, 0, 0, -1, func_80106154_picture_imperfect);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(0, 1, 0, -1, func_80109608_picture_imperfect);
    for (i = 0; i < 4; i++) {
        D_800EC598_minigame[i] = omAddObj(1, 4, 60, -1, func_8010629C_picture_imperfect);
        omSetStatBit(D_800EC598_minigame[i], OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    }
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->work[0] = 4;
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void func_80105BA8_picture_imperfect(void) {
    s32 i;

    switch (D_8010A150_picture_imperfect) {
        case 0:
            D_8010A230_picture_imperfect = HuSprAnimDataRead(0x3F0005);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = HuSprAnimDataRead((i + 14) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = HuSprAnimDataRead((i + 19) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = HuSprAnimDataRead((i + 24) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = HuSprAnimDataRead((i + 29) | 0x3F0000);
                D_8010A25A_picture_imperfect[i] = HuSprAnimDataRead((i + 34) | 0x3F0000);
            }
            break;
        case 1:
            D_8010A230_picture_imperfect = HuSprAnimDataRead(0x3F0006);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = HuSprAnimDataRead((i + 39) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = HuSprAnimDataRead((i + 44) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = HuSprAnimDataRead((i + 49) | 0x3F0000);
                D_8010A250_picture_imperfect[i] = HuSprAnimDataRead((i + 54) | 0x3F0000);
            }
            break;
        case 2:
        default:
            D_8010A230_picture_imperfect = HuSprAnimDataRead(0x3F0007);
            for (i = 0; i < 5; i++) {
                D_8010A232_picture_imperfect[i] = HuSprAnimDataRead((i + 59) | 0x3F0000);
                D_8010A23C_picture_imperfect[i] = HuSprAnimDataRead((i + 64) | 0x3F0000);
                D_8010A246_picture_imperfect[i] = HuSprAnimDataRead((i + 69) | 0x3F0000);
            }
            break;
    }
    D_8010A264_picture_imperfect = HuSprAnimDataRead(0x40001C);
    D_8010A266_picture_imperfect = HuSprAnimDataRead(0x40001B);
    D_8010A268_picture_imperfect = HuSprAnimDataRead(0x40001D);
    D_8010A26A_picture_imperfect = HuSprAnimDataRead(0x2E);
    D_8010A26C_picture_imperfect = HuSprAnimDataRead(0x3E0019);
}

void func_80105E68_picture_imperfect(MinigameFlow *flow) {
    s32 i;

    D_800EB932_minigame = 10;
    flow->state = MG_STATE_OPENING;
    flow->type = MINIGAME_4P;
    flow->timerMode = MG_TIMER_COUNT_DOWN;
    flow->timeDisp = MG_TIME_DISP_COUNTDOWN;
    flow->newRecord = FALSE;
    flow->gauge = MG_GAUGE_NONE;
    flow->resultType = MG_RESULT_NONE;
    flow->startDelay = -1;
    flow->timer = 1800;
    flow->timeLimit = -1;
    flow->finishDelay = 360;
    flow->resultDelay = 162;
    for (i = 0; i < 4; i++) {
        flow->gaugeValue[i] = 0;
        flow->winners[i] = 0xFF;
    }
}

void func_80105EF4_picture_imperfect(void) {
    s32 i;

    func_8000B710_main(4);
    func_8000B5F0_main(4);
    for (i = 0; i < 4; i++) {
        CenterM[i].x = -200.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = CRotM[i].y = CRotM[i].z = 0.0f;
        CZoomM[i] = 2100.0f;
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }
    ScissorSet(0, 0.0f, 0.0f, 160.0f, 120.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 160.0f, 0.0f, 320.0f, 120.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 0.0f, 120.0f, 160.0f, 240.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 160.0f, 120.0f, 320.0f, 240.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
}

void func_80106154_picture_imperfect(omObjData *object) {
    if (omPauseChk() + D_800D6A90_main == 0) {
        if (D_8010A014_picture_imperfect == 0 && D_800D530C_main == 1) {
            HuAudFXAllStop();
            if (!(D_800A1906_main & 4)) {
                HuAudSeqFadeOut(30);
            } else {
                HuAudSeqStop();
            }
            MgFlowStatSet(MG_STATE_EXIT);
            D_8010A014_picture_imperfect = 1;
        }
        func_800E1840_minigame();
        switch (MgFlowMain()) {
            case 0:
                D_800EB930_minigame = 49;
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                if (D_8010A010_picture_imperfect == 0) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                } else if (WipeStatGet() == 0 && !(D_800A1906_main & 4)) {
                    GameMesStub();
                    omOvlReturnEx(1);
                }
                D_8010A010_picture_imperfect++;
                break;
        }
    }
}

void func_8010629C_picture_imperfect(omObjData *object) {
    func_800E1BA8_minigame_ObjData *playerData;
    PictureImperfectWork *work;
    s8 character;
    u32 model;
    s32 motion;
    s32 camera;
    s32 i;

    character = GwPlayer[D_8010A028_picture_imperfect].chr;
    model = D_800A178C_main[character][0];
    motion = D_800A1790_main[character][0];
    func_800E19F0_minigame(1);
    func_800E1BA8_minigame(object, model, motion, D_8010A028_picture_imperfect, 0x2A9, 0x2B9);
    playerData = object->data;
    playerData->unk158 = HuMemAllocTag(sizeof(PictureImperfectWork), TAG_OVERLAY);
    memset(playerData->unk158, 0, sizeof(PictureImperfectWork));
    work = playerData->unk158;
    object->rot.x = object->rot.y = object->rot.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    object->trans.x = 0.0f;
    object->trans.y = -8.0f;
    object->trans.z = 0.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], object->scale.x, object->scale.y, object->scale.z);
    work->unk10 = 272.0f;
    object->model[2] = func_8000B108_main(0x3F0000, 0x2B9);
    Hu3DModelPosSet(object->model[2], object->trans.x, work->unk10, object->trans.z);
    Hu3DModelScaleSet(object->model[2], 1.2f, 1.2f, 1.2f);
    object->model[3] = func_8000B108_main(8, 0x88D);
    switch (D_8010A028_picture_imperfect) {
        case 0:
        default:
            camera = 1;
            break;
        case 1:
            camera = 2;
            break;
        case 2:
            camera = 4;
            break;
        case 3:
            camera = 8;
            break;
    }
    Hu3DModelCameraSet(object->model[0], camera);
    Hu3DModelCameraSet(object->model[1], camera);
    Hu3DModelCameraSet(object->model[2], camera);
    Hu3DModelCameraSet(object->model[3], camera);
    func_800E149C_minigame(object, 0, 2);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(character, 0), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(character, 4), 1, 19);
    func_800E5A00_minigame(object, 21, func_80017BB8_main(character, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 13, func_80017BB8_main(character, 0x2F), 1, 120);
    func_800E5A00_minigame(object, 14, func_80017BB8_main(character, 0x36), 1, 120);
    func_800E5690_minigame(object, 0);
    object->func = func_80107820_picture_imperfect;
    work->unk00 = 0;
    work->unk01 = 0;
    work->unk02 = 0;
    work->unk08 = 0;
    work->unk03 = 0;
    work->unk04 = 0;
    work->unk0A = 0xFF;
    work->unk0C = 1.0f;
    work->unk14 = 0.0f;
    work->unk05 = 0;
    work->unk06 = 0;
    work->unk07 = 0;
    work->unk18 = ((rand8() * 15) >> 7) + 30;
    switch (D_8010A150_picture_imperfect) {
        case 0:
            D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, D_8010A230_picture_imperfect, 0);
            HuSprAttrReset(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            HuSprAttrSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0x5000);
            HuSprPosSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
            HuSprPriSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A232_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A23C_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A246_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A250_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A208_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A25A_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A208_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A208_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A208_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A208_picture_imperfect[D_8010A028_picture_imperfect][i]);
            }
            break;
        case 1:
            D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, D_8010A230_picture_imperfect, 0);
            HuSprAttrReset(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            HuSprAttrSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0x5000);
            HuSprPosSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
            HuSprPriSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A232_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A23C_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A246_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A250_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A1E0_picture_imperfect[D_8010A028_picture_imperfect][i]);
            }
            break;
        case 2:
        default:
            D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect] = HuSprGrpCreate(1, 0);
            HuSprGrpMemberSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, D_8010A230_picture_imperfect, 0);
            HuSprAttrReset(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            HuSprAttrSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0x5000);
            HuSprPosSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                        D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
            HuSprPriSet(D_8010A15C_picture_imperfect[D_8010A028_picture_imperfect], 0, 0xFFFF);
            for (i = 0; i < 5; i++) {
                D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A232_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A168_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A23C_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A190_picture_imperfect[D_8010A028_picture_imperfect][i]);
                D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i] = espEntry(D_8010A246_picture_imperfect[i], 0, 1);
                espPosSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i],
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
                          D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
                espAttrSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0x5000);
                espPriSet(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i], 0xFFF0);
                espDispOff(D_8010A1B8_picture_imperfect[D_8010A028_picture_imperfect][i]);
            }
            break;
    }
    D_8010A26E_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A264_picture_imperfect, 0, 1);
    espPosSet(D_8010A26E_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A26E_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A26E_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A26E_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A276_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A266_picture_imperfect, 0, 1);
    espPosSet(D_8010A276_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A276_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A276_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A276_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A27E_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A266_picture_imperfect, 0, 1);
    espPosSet(D_8010A27E_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A27E_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A27E_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A27E_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A286_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A268_picture_imperfect, 0, 1);
    espPosSet(D_8010A286_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A286_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A286_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A286_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A28E_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A26A_picture_imperfect, 0, 1);
    espPosSet(D_8010A28E_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A28E_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A28E_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A28E_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A296_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A26A_picture_imperfect, 0, 1);
    espPosSet(D_8010A296_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A296_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A296_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A296_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A29E_picture_imperfect[D_8010A028_picture_imperfect] = espEntry(D_8010A26C_picture_imperfect, 0, 1);
    espPosSet(D_8010A29E_picture_imperfect[D_8010A028_picture_imperfect],
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].x,
              D_8010A018_picture_imperfect[D_8010A028_picture_imperfect].y);
    espAttrSet(D_8010A29E_picture_imperfect[D_8010A028_picture_imperfect], 0x1000);
    espPriSet(D_8010A29E_picture_imperfect[D_8010A028_picture_imperfect], 15);
    espDispOff(D_8010A29E_picture_imperfect[D_8010A028_picture_imperfect]);
    D_8010A028_picture_imperfect++;
}

void func_80107820_picture_imperfect(omObjData *object) {
    func_800E1BA8_minigame_ObjData *playerData;
    PictureImperfectWork *work;
    PictureImperfectWork *otherWork;
    s16 sound;
    s32 rounds;
    s32 character;
    s8 i;
    s8 count;

    playerData = object->data;
    work = playerData->unk158;
    switch (MgFlowStatGet()) {
        case MG_STATE_OPENING:
            func_800DDD94_minigame(object);
            break;
        case MG_STATE_PLAY:
            D_800CBB6E_main[playerData->unk57] = D_800D20A1_main[playerData->unk57] = 0;
            if (omPauseChk() + D_800D6A90_main != 0) {
                func_80108688_picture_imperfect(object);
                break;
            }
            if (GwPlayer[playerData->unk59].stat & 1) {
                func_801081E4_picture_imperfect(object);
            }
            if (work->unk05 == 0 && work->unk06 == 0 && playerData->unk38 != 1000.0f &&
                200.0f - playerData->unk34 <= object->trans.y) {
                sound = func_8004AC98_main(0x3F3, playerData->unk59);
                if (playerData->unk59 & 1) {
                    HuAudFXPanning(sound, 92);
                } else {
                    HuAudFXPanning(sound, 32);
                }
                omVibrate(playerData->unk59, 2, 3, 10);
                func_800E4C88_minigame(object, 3, object->trans.x, work->unk10 - 25.0f, object->trans.z, 180.0f, 0.0f);
                work->unk14 = 0.0f;
                work->unk05 = 1;
                D_8010A02C_picture_imperfect++;
                switch (D_8010A150_picture_imperfect) {
                    case 0:
                    default:
                        rounds = 5;
                        break;
                    case 1:
                        rounds = 4;
                        break;
                    case 2:
                        rounds = 3;
                        break;
                }
                if (rounds * 4 == D_8010A02C_picture_imperfect && D_80109FE0_picture_imperfect != -1) {
                    HuAudFXStop(D_80109FE0_picture_imperfect);
                    D_80109FE0_picture_imperfect = -1;
                    D_80109FE2_picture_imperfect = 0;
                }
            }
            if (work->unk05 == 1) {
                if (work->unk14 == 180.0f) {
                    work->unk10 = 272.0f;
                    work->unk14 = 0.0f;
                    work->unk05 = 0;
                } else {
                    work->unk14 += 20.0f;
                    work->unk10 = sindf(work->unk14) * 100.0f + 272.0f;
                }
                Hu3DModelPosSet(object->model[2], object->trans.x, work->unk10, object->trans.z);
            }
            if (work->unk06 == 1 || work->unk03 != 0) {
                D_800CDA7C_main[playerData->unk57] &= ~A_BUTTON;
                D_800D5558_main[playerData->unk57] &= ~A_BUTTON;
            }
            func_801083C0_picture_imperfect(playerData->unk59);
            func_80108688_picture_imperfect(object);
            func_80108C20_picture_imperfect(work, playerData->unk59);
            D_800EB748_minigame = 0.7f;
            func_800DDD94_minigame(object);
            break;
        case MG_STATE_FINISH:
            if (D_80109FE0_picture_imperfect != -1) {
                HuAudFXStop(D_80109FE0_picture_imperfect);
                D_80109FE0_picture_imperfect = -1;
                D_80109FE2_picture_imperfect = 0;
            }
            if (omPauseChk() + D_800D6A90_main != 0) {
                break;
            }
            if (work->unk03 == 0) {
                func_80108A64_picture_imperfect(work, playerData->unk59);
            }
            switch (D_80109FE4_picture_imperfect) {
                case 1:
                    func_80109284_picture_imperfect(work, playerData->unk59);
                    break;
                case 2:
                    for (i = 0; i < 4; i++) {
                        if (object != D_800EC598_minigame[i]) {
                            otherWork = ((func_800E1BA8_minigame_ObjData *)D_800EC598_minigame[i]->data)->unk158;
                            if (work->unk04 < otherWork->unk04) {
                                work->unk07++;
                            }
                        }
                    }
                    if (playerData->unk59 == 3) {
                        count = 0;
                        D_8010A110_picture_imperfect = 0;
                        for (i = 0; i < 4; i++) {
                            otherWork = ((func_800E1BA8_minigame_ObjData *)D_800EC598_minigame[i]->data)->unk158;
                            if (otherWork->unk07 == 0) {
                                D_8010A110_picture_imperfect++;
                                D_80109FF8_picture_imperfect[count] = i;
                                count++;
                            }
                        }
                        D_80109FE4_picture_imperfect = 8;
                    }
                    break;
                case 8:
                    if (playerData->unk59 == 3) {
                        if (D_8010A110_picture_imperfect == 1) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                        } else if (D_8010A110_picture_imperfect == 2) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                            D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                        } else if (D_8010A110_picture_imperfect == 3) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                            D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                            D_8010A140_picture_imperfect[2] = D_80109FF8_picture_imperfect[2];
                        } else if (work->unk04 != 0) {
                            D_8010A140_picture_imperfect[0] = D_80109FF8_picture_imperfect[0];
                            D_8010A140_picture_imperfect[1] = D_80109FF8_picture_imperfect[1];
                            D_8010A140_picture_imperfect[2] = D_80109FF8_picture_imperfect[2];
                            D_8010A140_picture_imperfect[3] = D_80109FF8_picture_imperfect[3];
                        } else {
                            D_80109FF8_picture_imperfect[0] = D_80109FF8_picture_imperfect[1] =
                                D_80109FF8_picture_imperfect[2] = D_80109FF8_picture_imperfect[3] = -1;
                        }
                        D_80109FE4_picture_imperfect = 16;
                        if (playerData->unk59 == 3) {
                            MgFlowStatSet(MG_STATE_RESULT);
                        }
                    }
                    break;
            }
            func_800DDD94_minigame(object);
            break;
        case MG_STATE_RESULT:
            if (func_800E6E9C_minigame() == 12) {
                if (D_80109FE4_picture_imperfect == 16) {
                    if (playerData->unk59 == D_80109FF8_picture_imperfect[0] ||
                        playerData->unk59 == D_80109FF8_picture_imperfect[1] ||
                        playerData->unk59 == D_80109FF8_picture_imperfect[2] ||
                        playerData->unk59 == D_80109FF8_picture_imperfect[3]) {
                        func_800E5690_minigame(object, 13);
                        switch (GwPlayer[playerData->unk59].chr) {
                            case 0:
                            default:
                                character = 2;
                                break;
                            case 1:
                                character = 3;
                                break;
                            case 2:
                                character = 7;
                                break;
                            case 3:
                                character = 4;
                                break;
                            case 4:
                                character = 5;
                                break;
                            case 5:
                                character = 6;
                                break;
                            case 6:
                                character = 8;
                                break;
                            case 7:
                                character = 9;
                                break;
                        }
                        func_80045ED0_main((character << 16) | 0x2F);
                        GwPlayer[playerData->unk59].bonusCoin += 10;
                    } else {
                        func_800E5690_minigame(object, 14);
                    }
                    func_800DDD94_minigame(object);
                }
                if (playerData->unk59 == 3) {
                    if (D_8010A110_picture_imperfect == 1) {
                        GMesCreate(0x16, GwPlayer[D_8010A140_picture_imperfect[0]].chr);
                        HuAudSeqPlay(0x65);
                    } else if (D_8010A110_picture_imperfect == 2) {
                        GMesCreate(0x1E, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[1]].chr);
                        HuAudSeqPlay(0x66);
                    } else if (D_8010A110_picture_imperfect == 3) {
                        GMesCreate(0x22, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[1]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[2]].chr);
                        HuAudSeqPlay(0x66);
                    } else if (work->unk04 != 0) {
                        GMesCreate(0x23, GwPlayer[D_8010A140_picture_imperfect[0]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[1]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[2]].chr,
                                   GwPlayer[D_8010A140_picture_imperfect[3]].chr);
                        HuAudSeqPlay(0x66);
                    } else {
                        GMesCreate(0x20);
                        HuAudSeqPlay(0x6C);
                    }
                    D_8010A128_picture_imperfect.resultType = MG_RESULT_NONE;
                }
            } else {
                D_8010A128_picture_imperfect.resultType = MG_RESULT_NONE;
            }
            break;
    }
    func_8001C258_main(object->model[1], 4, 4);
}

void func_801081E4_picture_imperfect(omObjData *object) {
    PictureImperfectWork *work;
    func_800E1BA8_minigame_ObjData *playerData;
    s32 chance3;
    s32 chance2;
    s32 chance1;
    u8 roll;

    playerData = object->data;
    work = playerData->unk158;
    if (work->unk18 != 0) {
        work->unk18--;
        return;
    }
    switch (GwPlayer[playerData->unk59].cpu_difficulty) {
        case 3:
            chance3 = 9;
            chance2 = 7;
            chance1 = 5;
            break;
        case 2:
            chance3 = 30;
            chance2 = 10;
            chance1 = 5;
            break;
        case 1:
        default:
            chance3 = 75;
            chance2 = 40;
            chance1 = 20;
            break;
        case 0:
            chance3 = 90;
            chance2 = 70;
            chance1 = 40;
            break;
    }
    roll = (rand8() * 100) >> 8;
    if (roll < chance1) {
        if (work->unk01 == 4) {
            D_800D5558_main[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance2) {
        if (work->unk01 == 3) {
            D_800D5558_main[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance3) {
        if (work->unk01 == 2) {
            D_800D5558_main[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (roll < chance2) {
        if (work->unk01 == 1) {
            D_800D5558_main[playerData->unk57] |= A_BUTTON;
            work->unk18 = ((rand8() * 15) >> 6) + 30;
        }
    } else if (work->unk01 == 0) {
        D_800D5558_main[playerData->unk57] |= A_BUTTON;
        work->unk18 = ((rand8() * 15) >> 6) + 30;
    }
}

void func_801083C0_picture_imperfect(s8 player) {
    if (player == 0) {
        if (D_8010A044_picture_imperfect % 10 == 9) {
            if (++D_8010A2AC_picture_imperfect[0] >= 5) {
                D_8010A2AC_picture_imperfect[0] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 8 == 7) {
            if (++D_8010A2AC_picture_imperfect[2] >= 5) {
                D_8010A2AC_picture_imperfect[2] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 6 == 5) {
            if (++D_8010A2AC_picture_imperfect[3] >= 5) {
                D_8010A2AC_picture_imperfect[3] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 4 == 3) {
            if (++D_8010A2AC_picture_imperfect[4] >= 5) {
                D_8010A2AC_picture_imperfect[4] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
        if (D_8010A044_picture_imperfect % 2 == 1) {
            if (++D_8010A2AC_picture_imperfect[1] >= 5) {
                D_8010A2AC_picture_imperfect[1] = 0;
            }
            if (D_80109FE0_picture_imperfect == -1 && D_80109FE2_picture_imperfect == 1) {
                D_80109FE0_picture_imperfect = HuAudFXPlay(0x3F4);
            }
        }
    } else if (player == 3) {
        D_8010A044_picture_imperfect++;
    }
}

void func_80108688_picture_imperfect(omObjData *object) {
    func_800E1BA8_minigame_ObjData *playerData;
    PictureImperfectWork *work;
    s8 player;
    s16(*sprites)[5];
    s16 delay;
    s8 i;

    playerData = object->data;
    work = playerData->unk158;
    player = playerData->unk59;
    switch (work->unk00) {
        case 0:
            sprites = D_8010A168_picture_imperfect;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                default:
                    delay = 10;
                    break;
                case 1:
                    delay = 8;
                    break;
                case 2:
                    delay = 6;
                    break;
            }
            break;
        case 1:
            sprites = D_8010A190_picture_imperfect;
            delay = 2;
            break;
        case 2:
            sprites = D_8010A1B8_picture_imperfect;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                default:
                    delay = 8;
                    break;
                case 1:
                    delay = 6;
                    break;
                case 2:
                    delay = 4;
                    break;
            }
            break;
        case 3:
            sprites = D_8010A1E0_picture_imperfect;
            if (D_8010A150_picture_imperfect == 0) {
                delay = 6;
            } else {
                delay = 4;
            }
            break;
        case 4:
            sprites = D_8010A208_picture_imperfect;
            delay = 4;
            break;
        default:
            if (playerData->unk38 == 1000.0f) {
                work->unk06 = 1;
            }
            return;
    }
    if (omPauseChk() + D_800D6A90_main != 0) {
        for (i = 0; i < 5; i++) {
            espDispOff(sprites[player][i]);
        }
        return;
    }
    work->unk01 = D_8010A030_picture_imperfect[D_8010A151_picture_imperfect][D_8010A2AC_picture_imperfect[work->unk00]];
    if (work->unk08 == 0) {
        work->unk08 = delay;
    } else {
        work->unk08--;
    }
    for (i = 0; i < 5; i++) {
        if (work->unk01 == i) {
            espDispOn(sprites[player][work->unk01]);
        } else {
            espDispOff(sprites[player][i]);
        }
    }
    if (D_800D5558_main[playerData->unk57] & A_BUTTON) {
        work->unk08 = delay - 2;
        switch (work->unk01) {
            case 0:
                work->unk03 = 10;
                break;
            case 1:
                work->unk03 = 7;
                break;
            case 2:
                work->unk03 = 5;
                break;
            case 3:
                work->unk03 = 3;
                break;
            case 4:
                work->unk03 = 1;
                break;
        }
        work->unk04 += work->unk03;
        D_80109FFC_picture_imperfect[player][work->unk00] = work->unk01;
        work->unk01 = (rand8() * 5) >> 8;
        if (work->unk00 == 0) {
            work->unk00 = 2;
        } else if (work->unk00 == 1) {
            work->unk00 = 10;
        } else {
            work->unk00++;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                    if (work->unk00 >= 5) {
                        work->unk00 = 1;
                    }
                    break;
                case 1:
                    if (work->unk00 >= 4) {
                        work->unk00 = 1;
                    }
                    break;
                case 2:
                default:
                    if (work->unk00 >= 3) {
                        work->unk00 = 1;
                    }
                    break;
            }
        }
    }
}

void func_80108A64_picture_imperfect(PictureImperfectWork *work, s8 player) {
    s32 i;

    switch (work->unk00) {
        case 0:
            for (i = 0; i < 5; i++) {
                espDispOff(D_8010A168_picture_imperfect[player][i]);
            }
            break;
        case 1:
            for (i = 0; i < 5; i++) {
                espDispOff(D_8010A190_picture_imperfect[player][i]);
            }
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                espDispOff(D_8010A1B8_picture_imperfect[player][i]);
            }
            break;
        case 3:
            for (i = 0; i < 5; i++) {
                espDispOff(D_8010A1E0_picture_imperfect[player][i]);
            }
            break;
        case 4:
            for (i = 0; i < 5; i++) {
                espDispOff(D_8010A208_picture_imperfect[player][i]);
            }
            break;
    }
}

void func_80108C20_picture_imperfect(PictureImperfectWork *work, s8 player) {
    u8 color[3];
    s32 y;
    s32 offset;
    s32 rounds;

    if (work->unk03 != 0) {
        switch (work->unk03) {
            case 1:
                if (D_8010A116_picture_imperfect[player]) {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0;
                    color[2] = 0xFF;
                }
                break;
            case 3:
                if (D_8010A116_picture_imperfect[player]) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0x80;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0xFF;
                }
                break;
            case 5:
                if (D_8010A116_picture_imperfect[player]) {
                    color[0] = 0;
                    color[1] = 0x80;
                    color[2] = 0;
                } else {
                    color[0] = 0;
                    color[1] = 0xFF;
                    color[2] = 0;
                }
                break;
            case 7:
                if (D_8010A116_picture_imperfect[player]) {
                    color[0] = 0x80;
                    color[1] = 0x40;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0x80;
                    color[2] = 0;
                }
                break;
            case 10:
                if (D_8010A116_picture_imperfect[player]) {
                    color[0] = 0x80;
                    color[1] = 0;
                    color[2] = 0;
                } else {
                    color[0] = 0xFF;
                    color[1] = 0;
                    color[2] = 0;
                }
                break;
        }
        switch (D_8010A150_picture_imperfect) {
            case 0:
                offset = work->unk00 - 1;
                break;
            case 1:
                if (work->unk00 == 1) {
                    offset = 0;
                } else if (work->unk00 == 2) {
                    offset = 1;
                } else if (work->unk00 == 3) {
                    offset = 2;
                } else {
                    offset = 4;
                }
                break;
            case 2:
            default:
                if (work->unk00 == 1) {
                    offset = 1;
                } else if (work->unk00 == 2) {
                    offset = 3;
                } else {
                    offset = 4;
                }
                break;
        }
        y = D_80109FE8_picture_imperfect[player].y + D_8010A048_picture_imperfect[offset];
        espColorSet(D_8010A26E_picture_imperfect[player], color[0], color[1], color[2]);
        espScaleSet(D_8010A26E_picture_imperfect[player], work->unk0C, work->unk0C);
        espTPLvlSet(D_8010A26E_picture_imperfect[player], work->unk0A);
        espPosSet(D_8010A26E_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 25, y);
        espDispOn(D_8010A26E_picture_imperfect[player]);
        if (work->unk03 == 10) {
            espColorSet(D_8010A276_picture_imperfect[player], color[0], color[1], color[2]);
            espScaleSet(D_8010A276_picture_imperfect[player], work->unk0C, work->unk0C);
            espTPLvlSet(D_8010A276_picture_imperfect[player], work->unk0A);
            func_8000BD50_main(D_8010A276_picture_imperfect[player], work->unk03 / 10);
            espPosSet(D_8010A276_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 14, y);
            espDispOn(D_8010A276_picture_imperfect[player]);
        } else {
            espDispOff(D_8010A276_picture_imperfect[player]);
        }
        espColorSet(D_8010A27E_picture_imperfect[player], color[0], color[1], color[2]);
        espScaleSet(D_8010A27E_picture_imperfect[player], work->unk0C, work->unk0C);
        espTPLvlSet(D_8010A27E_picture_imperfect[player], work->unk0A);
        func_8000BD50_main(D_8010A27E_picture_imperfect[player], work->unk03 % 10);
        espPosSet(D_8010A27E_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x + 2, y);
        espDispOn(D_8010A27E_picture_imperfect[player]);
        espColorSet(D_8010A286_picture_imperfect[player], color[0], color[1], color[2]);
        espScaleSet(D_8010A286_picture_imperfect[player], work->unk0C, work->unk0C);
        espTPLvlSet(D_8010A286_picture_imperfect[player], work->unk0A);
        espPosSet(D_8010A286_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x + 30, y);
        espDispOn(D_8010A286_picture_imperfect[player]);
        if (D_8010A112_picture_imperfect[player] > 10) {
            work->unk0C += 0.05f;
            work->unk0A -= 10;
            D_8010A116_picture_imperfect[player] = 0;
        } else {
            D_8010A112_picture_imperfect[player]++;
            D_8010A116_picture_imperfect[player] ^= 1;
        }
        if (work->unk0A <= 0) {
            work->unk0C = 1.0f;
            work->unk0A = 0xFF;
            work->unk03 = 0;
            D_8010A112_picture_imperfect[player] = 0;
            D_8010A116_picture_imperfect[player] = 0;
            switch (D_8010A150_picture_imperfect) {
                case 0:
                default:
                    rounds = 5;
                    break;
                case 1:
                    rounds = 4;
                    break;
                case 2:
                    rounds = 3;
                    break;
            }
            D_8010A111_picture_imperfect++;
            if (rounds * 4 == D_8010A111_picture_imperfect) {
                MgFlowStatSet(MG_STATE_FINISH);
            }
        }
    } else {
        espDispOff(D_8010A26E_picture_imperfect[player]);
        espDispOff(D_8010A276_picture_imperfect[player]);
        espDispOff(D_8010A27E_picture_imperfect[player]);
        espDispOff(D_8010A286_picture_imperfect[player]);
    }
}

void func_80109284_picture_imperfect(PictureImperfectWork *work, s8 player) {
    if (D_8010A11A_picture_imperfect[player] < 30) {
        if (D_8010A11A_picture_imperfect[player] == 0) {
            HuAudFXPlay(0x3EC);
        }
        func_8000BD50_main(D_8010A28E_picture_imperfect[player], (rand8() * 10U) >> 8);
        espPosSet(D_8010A28E_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 32,
                  D_80109FE8_picture_imperfect[player].y);
        espDispOn(D_8010A28E_picture_imperfect[player]);
        func_8000BD50_main(D_8010A296_picture_imperfect[player], (rand8() * 10U) >> 8);
        espPosSet(D_8010A296_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 12,
                  D_80109FE8_picture_imperfect[player].y);
        espDispOn(D_8010A296_picture_imperfect[player]);
        espPosSet(D_8010A29E_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x + 20,
                  D_80109FE8_picture_imperfect[player].y + 4);
        espDispOn(D_8010A29E_picture_imperfect[player]);
    } else if (D_8010A11A_picture_imperfect[player] == 30) {
        HuAudFXPlay(0x3ED);
        if (work->unk04 >= 10) {
            func_8000BD50_main(D_8010A28E_picture_imperfect[player], work->unk04 / 10);
            espPosSet(D_8010A28E_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 32,
                      D_80109FE8_picture_imperfect[player].y);
        } else {
            espDispOff(D_8010A28E_picture_imperfect[player]);
        }
        func_8000BD50_main(D_8010A296_picture_imperfect[player], work->unk04 % 10);
        espPosSet(D_8010A296_picture_imperfect[player], D_80109FE8_picture_imperfect[player].x - 12,
                  D_80109FE8_picture_imperfect[player].y);
    } else if (D_8010A11A_picture_imperfect[player] == 90) {
        espDispOff(D_8010A296_picture_imperfect[player]);
        espDispOff(D_8010A28E_picture_imperfect[player]);
        espDispOff(D_8010A29E_picture_imperfect[player]);
        if (player == 3) {
            D_80109FE4_picture_imperfect = 2;
        }
    }
    D_8010A11A_picture_imperfect[player]++;
}

void func_80109608_picture_imperfect(omObjData *object) {
    PictureImperfectGameData *data;
    s32 i;
    s32 x;
    s32 y;

    object->func = func_80109AC4_picture_imperfect;
    for (i = 0; i < 4; i++) {
        if (i == 0) {
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F0002);
        }
        D_8010A152_picture_imperfect = HuSprGrpCreate(1, 0);
        HuSprGrpMemberSet(D_8010A152_picture_imperfect, 0, D_8010A122_picture_imperfect, 0);
        HuSprAttrReset(D_8010A152_picture_imperfect, 0, 0xFFFF);
        HuSprAttrSet(D_8010A152_picture_imperfect, 0, 0x5000);
        HuSprPosSet(D_8010A152_picture_imperfect, 0, D_80109FE8_picture_imperfect[i].x,
                    D_80109FE8_picture_imperfect[i].y);
        HuSprPriSet(D_8010A152_picture_imperfect, 0, 0xFF);
    }
    D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F0003);
    D_8010A154_picture_imperfect = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(D_8010A154_picture_imperfect, 0, D_8010A122_picture_imperfect, 0);
    HuSprAttrReset(D_8010A154_picture_imperfect, 0, 0xFFFF);
    HuSprAttrSet(D_8010A154_picture_imperfect, 0, 0x1000);
    HuSprPosSet(D_8010A154_picture_imperfect, 0, 160, 120);
    HuSprPriSet(D_8010A154_picture_imperfect, 0, 0xF0);
    D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F0001);
    D_8010A156_picture_imperfect = espEntry(D_8010A122_picture_imperfect, 0, 1);
    espPosSet(D_8010A156_picture_imperfect, 160, 120);
    espAttrSet(D_8010A156_picture_imperfect, 0x1000);
    espPriSet(D_8010A156_picture_imperfect, 15);
    espDispOn(D_8010A156_picture_imperfect);
    x = 128;
    y = 108;
    switch (D_8010A150_picture_imperfect) {
        case 0:
        default:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F0008);
            break;
        case 1:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F000A);
            break;
        case 2:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F000C);
            break;
    }
    D_8010A158_picture_imperfect = espEntry(D_8010A122_picture_imperfect, 0, 1);
    espPosSet(D_8010A158_picture_imperfect, x, y);
    espAttrSet(D_8010A158_picture_imperfect, 0x1000);
    espPriSet(D_8010A158_picture_imperfect, 15);
    espDispOn(D_8010A158_picture_imperfect);
    switch (D_8010A150_picture_imperfect) {
        case 0:
        default:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F0009);
            break;
        case 1:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F000B);
            break;
        case 2:
            D_8010A122_picture_imperfect = HuSprAnimDataRead(0x3F000D);
            break;
    }
    D_8010A15A_picture_imperfect = espEntry(D_8010A122_picture_imperfect, 0, 1);
    espPosSet(D_8010A15A_picture_imperfect, x, y);
    espAttrSet(D_8010A15A_picture_imperfect, 0x1000);
    espPriSet(D_8010A15A_picture_imperfect, 15);
    espDispOn(D_8010A15A_picture_imperfect);
    D_8010A2A6_picture_imperfect = espEntry(D_8010A26A_picture_imperfect, 0, 1);
    espPosSet(D_8010A2A6_picture_imperfect, 225, 100);
    espAttrSet(D_8010A2A6_picture_imperfect, 0x1000);
    espPriSet(D_8010A2A6_picture_imperfect, 15);
    espDispOff(D_8010A2A6_picture_imperfect);
    D_8010A2A8_picture_imperfect = espEntry(D_8010A26A_picture_imperfect, 0, 1);
    espPosSet(D_8010A2A8_picture_imperfect, 245, 100);
    espAttrSet(D_8010A2A8_picture_imperfect, 0x1000);
    espPriSet(D_8010A2A8_picture_imperfect, 15);
    espDispOff(D_8010A2A8_picture_imperfect);
    D_8010A2AA_picture_imperfect = espEntry(D_8010A26C_picture_imperfect, 0, 1);
    espPosSet(D_8010A2AA_picture_imperfect, 277, 104);
    espAttrSet(D_8010A2AA_picture_imperfect, 0x1000);
    espPriSet(D_8010A2AA_picture_imperfect, 15);
    espDispOff(D_8010A2AA_picture_imperfect);
    data = object->data = HuMemAllocTag(sizeof(PictureImperfectGameData), TAG_OVERLAY);
    memset(data, 0, sizeof(PictureImperfectGameData));
    data->unk03 = 1;
    data->unk04 = 0;
    data->unk08 = 0.5f;
    func_800E1370_minigame(object, 2, -8.0f);
}

void func_80109AC4_picture_imperfect(omObjData *object) {
    f32 t;
    s32 x;
    s32 y;

    if (MgFlowStatGet() == MG_STATE_OPENING) {
        switch (D_8010A150_picture_imperfect) {
            case 0:
            default:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 5);
                break;
            case 1:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 4);
                break;
            case 2:
                func_8000BD50_main(D_8010A2A6_picture_imperfect, 3);
                break;
        }
        func_8000BD50_main(D_8010A2A8_picture_imperfect, 0);
        if (func_800E6E9C_minigame() == 1) {
            espDispOn(D_8010A2A6_picture_imperfect);
            espDispOn(D_8010A2A8_picture_imperfect);
            espDispOn(D_8010A2AA_picture_imperfect);
        } else if (func_800E6E9C_minigame() > 26) {
            switch (D_8010A054_picture_imperfect) {
                case 0:
                    if (D_8010A055_picture_imperfect == 0xFF) {
                        HuAudFXPlay(0x3F6);
                    }
                    espTPLvlSet(D_8010A15A_picture_imperfect, D_8010A055_picture_imperfect);
                    D_8010A055_picture_imperfect -= 5;
                    if (D_8010A055_picture_imperfect == 0) {
                        espDispOff(D_8010A2A6_picture_imperfect);
                        espDispOff(D_8010A2A8_picture_imperfect);
                        espDispOff(D_8010A2AA_picture_imperfect);
                        D_8010A054_picture_imperfect++;
                    }
                    break;
                case 1:
                    D_8010A050_picture_imperfect -= 0.04f;
                    t = D_8010A056_picture_imperfect / 50.0f;
                    x = (1.0f - t) * 128.0f + t * 160.0f;
                    y = (1.0f - t) * 108.0f + t * 120.0f;
                    if (D_8010A056_picture_imperfect == 0) {
                        D_8010A124_picture_imperfect = HuAudFXPlay(0x3F5);
                    }
                    D_8010A056_picture_imperfect++;
                    if (D_8010A050_picture_imperfect > 0.02f) {
                        espScaleSet(D_8010A156_picture_imperfect, D_8010A050_picture_imperfect,
                                    D_8010A050_picture_imperfect);
                        espScaleSet(D_8010A158_picture_imperfect, D_8010A050_picture_imperfect,
                                    D_8010A050_picture_imperfect);
                        espPosSet(D_8010A158_picture_imperfect, x, y);
                    } else {
                        D_8010A050_picture_imperfect = 0.0f;
                        D_8010A056_picture_imperfect = 0;
                        D_8010A054_picture_imperfect++;
                    }
                    break;
                case 2:
                    espDispOff(D_8010A156_picture_imperfect);
                    espDispOff(D_8010A158_picture_imperfect);
                    espDispOff(D_8010A15A_picture_imperfect);
                    if (D_8010A056_picture_imperfect > 10) {
                        D_8010A054_picture_imperfect++;
                    } else {
                        D_8010A056_picture_imperfect++;
                    }
                    break;
                case 3:
                    D_8010A056_picture_imperfect = 0;
                    MgFlowStatSet(MG_STATE_START);
                    HuAudFXStop(D_8010A124_picture_imperfect);
                    break;
            }
        }
    } else if (MgFlowStatGet() == MG_STATE_FINISH) {
        if (GMesStatGet() == 0 && func_800E6E9C_minigame() > 10) {
            D_8010A050_picture_imperfect += 0.04f;
            if (D_8010A050_picture_imperfect > 0.5f) {
                D_8010A050_picture_imperfect = 0.5f;
                if (D_80109FE4_picture_imperfect == 0) {
                    D_80109FE4_picture_imperfect = 1;
                }
            }
        }
        switch (D_80109FE4_picture_imperfect) {
            case 4:
            case 8:
            case 16:
                HuSprAttrSet(D_8010A154_picture_imperfect, 0, 0x5000);
                break;
            default:
                espScaleSet(D_8010A158_picture_imperfect, D_8010A050_picture_imperfect, D_8010A050_picture_imperfect);
                espPosSet(D_8010A158_picture_imperfect, 160, 120);
                espDispOn(D_8010A158_picture_imperfect);
                espScaleSet(D_8010A15A_picture_imperfect, D_8010A050_picture_imperfect, D_8010A050_picture_imperfect);
                espTPLvlSet(D_8010A15A_picture_imperfect, 0xFF);
                espPosSet(D_8010A15A_picture_imperfect, 160, 120);
                espDispOn(D_8010A15A_picture_imperfect);
                break;
        }
    }
}
