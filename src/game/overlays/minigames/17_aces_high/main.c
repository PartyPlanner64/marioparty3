#include "common.h"
#include "macros.h"
#include "game/pad.h"
#include "math.h"
#include "game/overlays/minigame.h"

typedef struct AceHighPlayer {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 camIdx;
    /* 0x04 */ omObjData *camObj;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 unk_0C;
    /* 0x0E */ char unk_0E[2];
    /* 0x10 */ Vec dir;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u16 unk_1E;
    /* 0x20 */ u16 unk_20;
    /* 0x22 */ char unk_22[2];
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ s16 unk_26;
    /* 0x28 */ u16 espriteSlots[2];
    /* 0x2C */ s16 unk_2C;
    /* 0x2E */ u16 unk_2E;
    /* 0x30 */ u16 unk_30;
    /* 0x32 */ s16 unk_32;
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ s16 unk_36;
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ f32 unk_44;
    /* 0x48 */ f32 unk_48;
    /* 0x4C */ u16 unk_4C;
    /* 0x4E */ u16 unk_4E;
    /* 0x50 */ u16 unk_50;
    /* 0x52 */ u16 unk_52;
    /* 0x54 */ u16 unk_54;
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ u16 unk_58;
    /* 0x5A */ char unk_5A[2];
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ omObjData *unk_6C;
    /* 0x70 */ s16 unk_70;
    /* 0x72 */ char unk_72[2];
    /* 0x74 */ omObjData *unk_74;
    /* 0x78 */ omObjData *unk_78;
    /* 0x7C */ f32 unk_7C;
    /* 0x80 */ f32 unk_80;
    /* 0x84 */ f32 unk_84;
    /* 0x88 */ u16 unk_88;
    /* 0x8A */ char unk_8A[2];
    /* 0x8C */ f32 unk_8C;
    /* 0x90 */ u16 unk_90;
    /* 0x92 */ u16 unk_92;
    /* 0x94 */ s16 unk_94;
    /* 0x96 */ char unk_96[2];
    /* 0x98 */ omObjData *unk_98;
    /* 0x9C */ Vec unk_9C;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ u16 unk_AC;
    /* 0xAE */ u16 unk_AE;
    /* 0xB0 */ u16 unk_B0;
    /* 0xB2 */ char unk_B2[0xE];
} AceHighPlayer; // sizeof 0xC0

typedef struct AceHighShot {
    /* 0x00 */ u16 unk_00;
    /* 0x02 */ u16 unk_02;
    /* 0x04 */ f32 speed;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 radius;
    /* 0x10 */ Vec dir;
    /* 0x1C */ omObjData *owner;
    /* 0x20 */ s16 effectIdx;
    /* 0x22 */ s16 effectModel;
    /* 0x24 */ u16 timer;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ omObjData *target;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ u16 unk_34;
    /* 0x36 */ u16 unk_36;
} AceHighShot; // sizeof 0x38

extern u8 omAllPauseF;
MinigameFlow m223_mgFlow = {
    MG_STATE_OPENING, MINIGAME_4P, MG_TIMER_COUNT_DOWN, MG_TIME_DISP_COUNTDOWN, FALSE, MG_GAUGE_NONE, MG_RESULT_WIN_1, 0,
    { 0.0f, 0.0f, 0.0f, 0.0f },
    { 0, 0, 0, 0 },
    -1, 1800, -1, -1, 135
};
u16 m223_camBitTbl[4] = { 1, 2, 4, 8 };
f32 m223_scissorTbl[4][4] = {
    { 1.0f, 1.0f, 159.0f, 119.0f },
    { 161.0f, 1.0f, 319.0f, 119.0f },
    { 1.0f, 121.0f, 159.0f, 239.0f },
    { 161.0f, 121.0f, 319.0f, 239.0f },
};
f32 m223_viewportTbl[4][4] = {
    { 640.0f, 480.0f, 320.0f, 240.0f },
    { 640.0f, 480.0f, 960.0f, 240.0f },
    { 640.0f, 480.0f, 320.0f, 720.0f },
    { 640.0f, 480.0f, 960.0f, 720.0f },
};
Vec m223_bgColorTbl[2] = { { 20.0f, 130.0f, 255.0f }, { 255.0f, 130.0f, 20.0f } };
u16 m223_exitF = 0;
f32 m223_skyRot = 0.0f;
s32 m223_planeMdlTbl[8] = { 0x38000C, 0x38000D, 0x38000E, 0x38000F, 0x380010, 0x380011, 0x380012, 0x380013 };
s32 m223_radarIconTbl[8] = { 0x380014, 0x380015, 0x380016, 0x380017, 0x380018, 0x380019, 0x38001A, 0x38001B };
s16 m223_lifePosTbl[4][2][2] = {
    { { 28, 100 }, { 28, 92 } },
    { { 292, 100 }, { 292, 92 } },
    { { 28, 220 }, { 28, 212 } },
    { { 292, 220 }, { 292, 212 } },
};
s16 m223_iconPosTbl[4][2] = { { 32, 24 }, { 288, 24 }, { 32, 144 }, { 288, 144 } };
f32 m223_startRotTbl[4] = { 90.0f, 180.0f, 270.0f, 0.0f };
s32 m223_shotMdlFileTbl[8] = { 0x380000, 0x380001, 0x380002, 0x380003, 0x380004, 0x380005, 0x380006, 0x380007 };
u16 m223_finishF = 0;
u16 m223_finishWait = 45;
Vec2f m223_viewCenter = { 160.0f, 120.0f };
Vec2f m223_viewCornerTbl[4] = { { 319.0f, 239.0f }, { 1.0f, 239.0f }, { 319.0f, 1.0f }, { 1.0f, 1.0f } };

u16 m223_cloudTexSize[2] BSS;
f32 m223_cloudTexScroll[2] BSS;
omObjData *m223_introObj BSS;
omObjData *m223_finishObj BSS;
omObjData *m223_stageObj BSS;
omObjData **m223_planeObjTbl BSS;
omObjData *m223_shotMdlObj BSS;
omObjData **m223_shotObjTbl[4] BSS;
omObjData *m223_radarObj BSS;
omObjData *m223_cameraObj BSS;
u16 m223_introPhase BSS;
u16 m223_finishPhase BSS;
s16 m223_aliveNum BSS;
s16 m223_winner BSS;
s16 m223_resultF BSS;
s16 m223_viewLineHSpr BSS;
s16 m223_viewLineVSpr BSS;
s16 m223_engineSe BSS;
Vec m223_bgColor BSS;
s16 m223_warnSprData BSS;
s16 m223_lockSprData BSS;
Vec m223_winCameraPos BSS;
Vec m223_winCameraTarget BSS;
Vec m223_winCameraUp BSS;
u8 m223_winCameraUpPad[4] BSS; /* Unreferenced. */
u16 m223_shotEffUseTbl[20] BSS;
u16 m223_shotEffMdlTbl[20] BSS;
s16 m223_radarSpr BSS;

void m223_MainObjInit(omObjData *object);
void m223_MainObjMain(omObjData *object);
void m223_StageObjInit(omObjData *object);
void m223_StageObjMain(omObjData *object);
void m223_PlaneObjInit(omObjData *object);
void m223_PlaneIntroObjMain(omObjData *object);
void m223_PlaneEndObjMain(omObjData *object);
void m223_PlaneObjMain(omObjData *object);
void m223_PlaneReturnObjMain(omObjData *object);
void m223_PlaneCrashObjMain(omObjData *object);
void m223_PlaneShakeUpdate(omObjData *object);
void m223_LifeSprOffAll(void);
void m223_PlanePushApart(omObjData *object);
void m223_PlaneComInput(omObjData *object, s8 *stickX, s8 *stickY, u16 *btnDown, u16 *btn);
u16 m223_PlaneComSteer(omObjData *object, Vec *target, f32 angleTol, f32 heightTol, s8 *stickX, s8 *stickY);
void m223_PlaneComStateUpdate(omObjData *object);
s16 m223_PlaneComTargetFind(omObjData *object, f32 fov, omObjData **list, omObjData **nearest, f32 *minDist);
f32 m223_ShotNearDistGet(omObjData *object);
void m223_PlaneComEvade(omObjData *object);
void m223_CameraFollowObjMain(omObjData *object);
void m223_CameraPosCalc(omObjData *object);
void m223_CameraIntroObjMain(omObjData *object);
void m223_CameraStartObjMain(omObjData *object);
void m223_CameraOverObjMain(omObjData *object);
void m223_CameraWinStart(omObjData *object);
void m223_CameraWinObjMain(omObjData *object);
void m223_CameraWinHoldObjMain(omObjData *object);
void m223_CameraViewObjMain(omObjData *object);
void m223_CameraViewFix(omObjData *object);
void m223_CameraEndObjMain(omObjData *object);
void m223_ShotInit(void);
void m223_ShotHitObjMain(omObjData *object);
void m223_ShotFire(omObjData *object);
void m223_ShotKillAll(void);
void m223_ShotObjMain(omObjData *object);
void m223_MissileFire(omObjData *object);
void m223_MissileObjMain(omObjData *object);
void m223_RadarInit(void);
void m223_RadarObjMain(omObjData *object);
void m223_IntroObjMain(omObjData *object);
void m223_FinishObjMain(omObjData *object);
void m223_SurvivorCheck(void);
u16 m223_WinViewExpand(u16 winner);
void m223_WarnObjMain(omObjData *object);
void m223_LockObjMain(omObjData *object);
void m223_OvlReturn(void);

void m223_ObjectSetup(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(80, 0);
    omGameSysInit();
    CamSetupInitMulti(4);
    CamSetupMapCullAddMulti(4);
    for (i = 0; i < 4; i++) {
        CZoomM[i] = 1500.0f;
        CRotM[i].x = -5.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 0.0f;
        CenterM[i].z = 0.0f;
        Hu3DCameraPerspectiveSet(i, 90.0f, 80.0f, 14000.0f);
        ScissorSet(i, m223_scissorTbl[i][0], m223_scissorTbl[i][1], m223_scissorTbl[i][2],
                   m223_scissorTbl[i][3]);
        ViewportSet(i, m223_viewportTbl[i][0], m223_viewportTbl[i][1], 511.0f, m223_viewportTbl[i][2],
                    m223_viewportTbl[i][3], 511.0f);
    }
    m223_cameraObj = obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    m223_bgColor.x = m223_bgColorTbl[0].x;
    m223_bgColor.y = m223_bgColorTbl[0].y;
    m223_bgColor.z = m223_bgColorTbl[0].z;
    Hu3DBGColorSet((u8)m223_bgColor.x, (u8)m223_bgColor.y, (u8)m223_bgColor.z);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, m223_MainObjInit);
    m223_stageObj = omAddObj(10, 4, 0, -1, m223_StageObjInit);
    omSetStatBit(m223_stageObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omSetStatBit(m223_stageObj, OM_STAT_MODELPAUSE);
    MgFlowInit(&m223_mgFlow);
    mgFlowSeqNo = 50;
    mgFlowSeqTime = 10;
    omMakeGroup(0, 4);
    m223_planeObjTbl = omGetGroupMemberList(0);
    for (i = 0; i < 4; i++) {
        omAddObj(20, 7, 0, 0, m223_PlaneObjInit)->work[0] = i;
    }
    m223_RadarInit();
    m223_ShotInit();
    m223_warnSprData = HuSprAnimDataRead(0x380027);
    m223_lockSprData = HuSprAnimDataRead(0x380028);
}

void m223_MainObjInit(omObjData *object) {
    m223_finishObj = NULL;
    m223_introObj = NULL;
    m223_aliveNum = 4;
    m223_winner = -1;
    m223_resultF = 0;
    object->func = m223_MainObjMain;
}

void m223_MainObjMain(omObjData *object) {
    if (m223_exitF == 0) {
        switch (MgFlowMain()) {
            case 0:
                if (m223_introObj == NULL) {
                    m223_introPhase = 0;
                    m223_introObj = omAddObj(4, 0, 0, -1, m223_IntroObjMain);
                }
                break;
            case 1:
                break;
            case 2:
                if (m223_aliveNum < 2) {
                    MgFlowStatSet(MG_STATE_FINISH);
                }
                break;
            case 3:
                if (m223_finishObj == NULL) {
                    m223_finishPhase = 0;
                    m223_finishObj = omAddObj(4, 0, 0, -1, m223_FinishObjMain);
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudFXStop(m223_engineSe);
                HuAudSeqFadeOut(30);
                HuAudFXAllFadeOut(30);
                m223_exitF = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        m223_OvlReturn();
    }
}

void m223_StageObjInit(omObjData *object) {
    u16 sprite;

    object->model[0] = Hu3DModelRead(0x38000A, 0x6D9);
    Hu3DModelPosSet(object->model[0], 0.0f, -1000.0f, 0.0f);
    object->model[1] = Hu3DModelRead(0x380025, 0x699);
    Hu3DModelPosSet(object->model[1], 0.0f, 900.0f, -8000.0f);
    object->model[2] = Hu3DModelRead(0x380026, 0x699);
    Hu3DModelPosSet(object->model[2], 0.0f, 0.0f, 8000.0f);
    Hu3DModelRotSet(object->model[2], 0.0f, 180.0f, 0.0f);
    object->model[3] = Hu3DModelRead(0x38000B, 0x6C9);
    Hu3DModelPosSet(object->model[3], 0.0f, -1000.0f, 0.0f);
    Hu3DData[object->model[3]].hmf->unk84->unk0[2] = 0;
    Hu3DModelRemakeStatic(object->model[3]);
    Hu3DModelDynamicFree(object->model[3]);
    m223_viewLineHSpr = sprite = espEntry(HuSprAnimDataRead(0x38001E), 0, 0);
    espPosSet(sprite, 160, 120);
    espPriSet(sprite, 0x8096);
    m223_viewLineVSpr = sprite = espEntry(HuSprAnimDataRead(0x38001F), 0, 0);
    espPosSet(sprite, 160, 120);
    espPriSet(sprite, 0x8096);
    m223_cloudTexScroll[0] = m223_cloudTexScroll[1] = 0.0f;
    Hu3DTexSizeGet("m223_03kaze_IA88", m223_cloudTexSize);
    Hu3DModelVtxBufMake(object->model[3]);
    object->func = m223_StageObjMain;
}

void m223_StageObjMain(omObjData *object) {
    if (omPauseChk() + omAllPauseF == 0) {
        m223_cloudTexScroll[1] += 2.0f;
        m223_skyRot -= 0.0f;
        if (m223_skyRot < 0.0f) {
            m223_skyRot += 360.0f;
        }
    }
    Hu3DModelObjTexScroll(object->model[3], m223_cloudTexScroll[0], m223_cloudTexScroll[1], m223_cloudTexSize[0],
                       m223_cloudTexSize[1], "m223_4-cyl11", 0);
    Hu3DModelRotSet(object->model[3], 0.0f, m223_skyRot, 0.0f);
}

const char m223_emptyStr[] = "";

void m223_PlaneObjInit(omObjData *object) {
    AceHighPlayer *player;
    u16 idx;
    s8 chr;
    s16 spr;
    s16 i;
    u16 sprite;

    idx = object->work[0];
    player = object->data = HuMemAllocTag(sizeof(AceHighPlayer), 0x7918);
    player->camIdx = idx;
    chr = GwPlayer[idx].chr;
    object->model[0] = Hu3DModelRead(m223_planeMdlTbl[chr], 0x6B9);
    if (idx == 0) {
        object->model[1] = Hu3DModelRead(0x380008, 0x6D9);
        object->model[2] = Hu3DModelRead(0x380009, 0x6D9);
        object->model[3] = Hu3DModelRead(0x380021, 0x6D9);
        object->model[4] = Hu3DModelRead(0x380022, 0x6D9);
        object->model[5] = Hu3DModelRead(0x380023, 0x6D9);
        object->model[6] = Hu3DModelRead(0x380024, 0x6D9);
    } else {
        object->model[1] = Hu3DModelLink(m223_planeObjTbl[0]->model[1]);
        object->model[2] = Hu3DModelLink(m223_planeObjTbl[0]->model[2]);
        object->model[3] = Hu3DModelLink(m223_planeObjTbl[0]->model[3]);
        object->model[4] = Hu3DModelLink(m223_planeObjTbl[0]->model[4]);
        object->model[5] = Hu3DModelLink(m223_planeObjTbl[0]->model[5]);
        object->model[6] = Hu3DModelLink(m223_planeObjTbl[0]->model[6]);
    }
    Hu3DModelAttrSet(object->model[3], 4, 4);
    Hu3DModelObjAttrSet(object->model[3], 0x70000000, 0x70000000);
    Hu3DModelAttrSet(object->model[2], 4, 4);
    Hu3DMotionAttrSet(object->model[4], 3, 2);
    Hu3DMotionAttrSet(object->model[5], 3, 2);
    Hu3DMotionAttrSet(object->model[6], 3, 2);
    Hu3DModelAttrSet(object->model[4], 4, 4);
    Hu3DModelAttrSet(object->model[6], 4, 4);
    omSetTra(object, sindf(m223_startRotTbl[idx]) * 1150.0f, -250.0f, cosdf(m223_startRotTbl[idx]) * 1150.0f);
    omSetRot(object, 0.0f, atan2df(-object->trans.x, -object->trans.z), 0.0f);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelRotSet(object->model[1], object->rot.x, object->rot.y, object->rot.z);
    spr = HuSprAnimDataRead(m223_radarIconTbl[chr]);
    player->unk_1C = espEntry(spr, 0, 0);
    player->unk_1E = espEntry(spr, 0, 0);
    espDispOff(player->unk_1E);
    spr = HuSprAnimDataRead(0x38001D);
    for (i = 0; i < 2; i++) {
        player->espriteSlots[i] = espEntry(spr, 0, 0);
        espPosSet(player->espriteSlots[i], m223_lifePosTbl[idx][i][0], m223_lifePosTbl[idx][i][1]);
    }
    player->unk_2E = sprite = espEntry(m223_warnSprData, 0, 0);
    espPriSet(sprite, 0x80C8);
    espDispOff(sprite);
    player->unk_30 = sprite = espEntry(m223_lockSprData, 0, 0);
    espPriSet(sprite, 0x80C8);
    espPosSet(sprite, m223_iconPosTbl[idx][0], m223_iconPosTbl[idx][1]);
    espDispOff(sprite);
    player->unk_0C = 0;
    player->unk_3C = 0.0f;
    player->unk_38 = 0.0f;
    player->unk_40 = 0.0f;
    player->unk_32 = 0;
    player->unk_34 = 0;
    player->unk_20 = 0;
    player->unk_24 = 4;
    player->unk_00 = 0;
    player->unk_26 = 2;
    player->unk_2C = -1;
    player->unk_36 = 0;
    player->unk_52 = 0;
    player->unk_54 = 1;
    player->unk_56 = 1;
    player->unk_58 = 0;
    player->unk_4C = 1;
    player->unk_6C = NULL;
    player->unk_5C = 0.0f;
    player->unk_60 = 0.0f;
    player->unk_68 = 0.0f;
    player->unk_64 = 0.0f;
    player->unk_08 = 27.777777f;
    player->dir.x = sindf(object->rot.y);
    player->dir.y = 0.0f;
    player->dir.z = cosdf(object->rot.y);
    player->unk_88 = 0;
    player->unk_44 = 0.0f;
    player->unk_90 = 1;
    player->unk_8C = object->rot.y;
    player->unk_94 = 0;
    player->unk_92 = 0;
    player->unk_AE = 0;
    player->unk_70 = 0;
    player->unk_74 = omAddObj(60, 0, 0, -1, m223_WarnObjMain);
    player->unk_74->work[2] = 0;
    player->unk_74->work[3] = (u32)object;
    player->unk_78 = omAddObj(60, 0, 0, -1, m223_LockObjMain);
    player->unk_78->work[0] = (u32)object;
    player->unk_78->work[1] = 0;
    player->unk_78->scale.x = 0.0f;
    object->work[0] = 30;
    player->camObj = omAddObj(50, 0, 0, -1, m223_CameraIntroObjMain);
    player->camObj->work[0] = 1;
    player->camObj->work[1] = (u32)object;
    object->func = m223_PlaneIntroObjMain;
}

void m223_PlaneMdlUpdate(omObjData *object) {
    AceHighPlayer *player = object->data;

    func_80088910_main(Hu3DData[object->model[0]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
    omSetRot(object, 0.0f, object->rot.y, 0.0f);
    if (player->unk_90 == 0) {
        Hu3DModelAttrSet(object->model[0], 4, 4);
    } else {
        Hu3DModelAttrSet(object->model[0], 4, 0);
    }
    if (player->unk_56 == 1) {
        Hu3DModelPosSet(object->model[1], object->trans.x + player->unk_60, object->trans.y + player->unk_68,
                        object->trans.z + player->unk_64);
        func_80088910_main(Hu3DData[object->model[1]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(object->model[1], 0.0f, object->rot.y, 0.0f);
        Hu3DModelPosSet(object->model[2], object->trans.x + player->unk_60, object->trans.y + player->unk_68,
                        object->trans.z + player->unk_64);
        func_80088910_main(Hu3DData[object->model[2]].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(object->model[2], 0.0f, object->rot.y, 0.0f);
        if (player->unk_58 == 0) {
            Hu3DModelAttrSet(object->model[2], 4, 4);
            Hu3DModelAttrSet(object->model[1], 4, 0);
        } else {
            Hu3DModelAttrSet(object->model[1], 4, 4);
            Hu3DModelAttrSet(object->model[2], 4, 0);
        }
        if (player->unk_90 == 0) {
            Hu3DModelAttrSet(object->model[1], 4, 4);
            Hu3DModelAttrSet(object->model[2], 4, 4);
        }
    }
}

void m223_PlaneSubMdlUpdate(omObjData *object) {
    AceHighPlayer *player = object->data;
    s16 model;

    switch (player->unk_4C) {
        case 0:
            model = object->model[4];
            Hu3DModelAttrSet(object->model[5], 4, 4);
            Hu3DModelAttrSet(object->model[6], 4, 4);
            break;
        case 1:
            model = object->model[5];
            Hu3DModelAttrSet(object->model[4], 4, 4);
            Hu3DModelAttrSet(object->model[6], 4, 4);
            break;
        case 2:
            model = object->model[6];
            Hu3DModelAttrSet(object->model[4], 4, 4);
            Hu3DModelAttrSet(object->model[5], 4, 4);
            break;
        case 3:
            model = -1;
            Hu3DModelAttrSet(object->model[4], 4, 4);
            Hu3DModelAttrSet(object->model[5], 4, 4);
            Hu3DModelAttrSet(object->model[6], 4, 4);
            break;
    }
    if (model >= 0) {
        Hu3DModelAttrSet(model, 4, 0);
        Hu3DModelPosSet(model, object->trans.x, object->trans.y, object->trans.z);
        func_80088910_main(Hu3DData[model].mtx, player->unk_38, 0.0f, player->unk_3C + player->unk_44);
        Hu3DModelRotSet(model, 0.0f, object->rot.y, 0.0f);
    }
    if (player->unk_90 == 0) {
        Hu3DModelAttrSet(object->model[4], 4, 4);
        Hu3DModelAttrSet(object->model[5], 4, 4);
        Hu3DModelAttrSet(object->model[6], 4, 4);
    }
}

void m223_PlaneDebugPad(omObjData *object) {
    AceHighPlayer *player = object->data;

    if (HuPadBtn[0] & L_JPAD) {
        object->rot.y -= 2.0f;
    }
    if (HuPadBtn[0] & R_JPAD) {
        object->rot.y += 2.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (HuPadBtn[0] & U_JPAD) {
        player->unk_38 += 2.0f;
    }
    if (HuPadBtn[0] & D_JPAD) {
        player->unk_38 -= 2.0f;
    }
    if (HuPadBtn[0] & L_CBUTTONS) {
        player->unk_3C -= 2.0f;
    }
    if (HuPadBtn[0] & R_CBUTTONS) {
        player->unk_3C += 2.0f;
    }
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
}

void m223_PlaneIntroObjMain(omObjData *object) {
    AceHighPlayer *player = object->data;

    if (object->work[0] != 0) {
        object->work[0]--;
    } else {
        switch (player->unk_88) {
            case 0:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= -90.0f) {
                    player->unk_38 += 180.0f;
                    player->unk_3C += 180.0f;
                    object->rot.y += 180.0f;
                    player->unk_88 = 1;
                }
                break;
            case 1:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= 0.0f) {
                    player->unk_88 = 2;
                }
                break;
            case 2:
                player->unk_38 += 4.0f;
                player->unk_3C -= 8.0f;
                if (player->unk_38 >= 90.0f) {
                    player->unk_38 = 90.0f;
                    player->unk_3C = 0.0f;
                    player->unk_88 = 3;
                }
                break;
            case 3:
                player->unk_38 -= 4.0f;
                if (player->unk_38 <= 0.0f) {
                    player->unk_38 = 0.0f;
                    object->work[1] = 30;
                    player->camObj->func = m223_CameraStartObjMain;
                    player->camObj->work[2] = 0;
                    player->camObj->scale.x = CRotM[player->camIdx].x;
                    player->unk_88 = 4;
                    if (player->camIdx == 3) {
                        MgFlowStatSet(MG_STATE_START);
                    }
                }
                break;
            case 4:
                if (--object->work[1] == 0) {
                    player->camObj->func = m223_CameraFollowObjMain;
                    object->func = m223_PlaneObjMain;
                }
                break;
        }
    }
    player->dir.y = -sindf(player->unk_38) * cosdf(player->unk_3C);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
}

void m223_PlaneEndObjMain(omObjData *object) {
    AceHighPlayer *player = object->data;
    s8 stickX;
    s8 stickY;
    u16 btnDown;
    u16 btn;
    f32 target;
    f32 speed;

    m223_PlaneComInput(object, &stickX, &stickY, &btnDown, &btn);
    btn = 0;
    btnDown = 0;
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = stickY / 70.0f * 30.0f;
    if (target < player->unk_38) {
        if (target - player->unk_38 < -10.0f) {
            player->unk_38 -= 10.0f;
            player->unk_7C = -10.0f;
        } else {
            player->unk_38 = target;
            player->unk_7C = target;
        }
    } else if (target - player->unk_38 > 10.0f) {
        player->unk_38 += 10.0f;
        player->unk_7C = 10.0f;
    } else {
        player->unk_38 = target;
        player->unk_7C = target;
    }
    target = stickX / 70.0f * 60.0f;
    if (target < player->unk_3C) {
        if (target - player->unk_3C < -10.0f) {
            player->unk_3C -= 10.0f;
            player->unk_80 = -10.0f;
        } else {
            player->unk_3C = target;
            player->unk_80 = target;
        }
    } else if (target - player->unk_3C > 10.0f) {
        player->unk_3C += 10.0f;
        player->unk_80 = 10.0f;
    } else {
        player->unk_3C = target;
        player->unk_80 = target;
    }
    player->unk_84 = player->unk_80 / 30.0f;
    if (btn & 0x4000) {
        speed = 16.666666f;
        player->unk_4C = 0;
    } else if (btn & 0x8000) {
        speed = 41.666664f;
        player->unk_4C = 2;
    } else {
        speed = 27.777777f;
        player->unk_4C = 1;
    }
    if (player->unk_0C == 1) {
        speed *= 2.0f;
    }
    if (speed < player->unk_08) {
        player->unk_08 -= 2.0f;
        if (player->unk_08 < speed) {
            player->unk_08 = speed;
        }
    } else if (player->unk_08 < speed) {
        player->unk_08 += 2.0f;
        if (speed < player->unk_08) {
            player->unk_08 = speed;
        }
    }
    if (stickX == 0) {
        player->unk_32 = 0;
    } else if (stickX < 0) {
        player->unk_32 = 1;
    } else {
        player->unk_32 = 2;
    }
    object->rot.y -= player->unk_3C / 30.0f;
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    m223_PlanePushApart(object);
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
}

void m223_PlaneObjMain(omObjData *object) {
    f32 shake[4] = { 10.0f, 0.0f, -10.0f, 0.0f };
    AceHighPlayer *player = object->data;
    u32 hit;
    s16 mode;
    s8 stickX;
    s8 stickY;
    u16 btnDown;
    u16 btn;
    f32 target;
    f32 speed;
    s8 pad;
    s32 com;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        _HuAudPlayerFXPlay(0x3AF, player->camIdx);
        espDispOff(player->espriteSlots[--player->unk_26]);
        if (player->unk_26 == 0) {
            player->unk_00 = 4;
            player->unk_4E = 45;
            player->unk_4C = 3;
            player->unk_58 = 0;
            m223_CameraPosCalc(object);
            Hu3DModelAttrSet(object->model[3], 4, 0);
            Hu3DMotionAttrSet(object->model[3], 3, 2);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, object->trans.z);
            m223_aliveNum--;
            player->unk_98 = NULL;
            HuAudFXPlay(0x3B0);
            object->func = m223_PlaneCrashObjMain;
            omVibrate(player->camIdx, 30, 0, 30);
            PlayerFXPlay(0x286, player->camIdx);
            return;
        }
        player->unk_00 = 3;
        player->unk_50 = 30;
        omVibrate(player->camIdx, 20, 0, 20);
        PlayerFXPlay(0x2AB, player->camIdx);
    }
    if (hit & 2) {
        player->unk_56 = 1;
        player->unk_5C = 50.0f;
        Hu3DModelAttrSet(object->model[1], 4, 0);
    }
    if (hit & 4) {
        player->unk_74->work[0] = 45;
        player->unk_74->work[1] = 6;
        player->unk_74->work[2] = 1;
    }
    m223_PlaneShakeUpdate(object);
    mode = MgFlowStatGet();
    if (mode == MG_STATE_PLAY || mode == MG_STATE_FINISH || MgFlowStatGet() == MG_STATE_RESULT) {
        com = GwPlayer[player->camIdx].stat & 1;
        if (com || mode == MG_STATE_FINISH || mode == MG_STATE_RESULT) {
            m223_PlaneComInput(object, &stickX, &stickY, &btnDown, &btn);
            if (mode == MG_STATE_FINISH || mode == MG_STATE_RESULT) {
                btn = 0;
                btnDown = 0;
            }
        } else {
            pad = GwPlayer[player->camIdx].pad;
            stickX = HuPadStkX[pad];
            stickY = HuPadStkY[pad];
            btnDown = HuPadBtnDown[pad];
            btn = HuPadBtn[pad];
        }
    } else {
        btn = 0;
        btnDown = 0;
        stickY = 0;
        stickX = 0;
    }
    if (stickX > 70) {
        stickX = 70;
    }
    if (stickX < -70) {
        stickX = -70;
    }
    if (stickY > 70) {
        stickY = 70;
    }
    if (stickY < -70) {
        stickY = -70;
    }
    target = stickY / 70.0f * 30.0f;
    if (target < player->unk_38) {
        if (target - player->unk_38 < -10.0f) {
            player->unk_38 -= 10.0f;
            player->unk_7C = -10.0f;
        } else {
            player->unk_38 = target;
            player->unk_7C = target;
        }
    } else if (target - player->unk_38 > 10.0f) {
        player->unk_38 += 10.0f;
        player->unk_7C = 10.0f;
    } else {
        player->unk_38 = target;
        player->unk_7C = target;
    }
    target = stickX / 70.0f * 60.0f;
    if (target < player->unk_3C) {
        if (target - player->unk_3C < -10.0f) {
            player->unk_3C -= 10.0f;
            player->unk_80 = -10.0f;
        } else {
            player->unk_3C = target;
            player->unk_80 = target;
        }
    } else if (target - player->unk_3C > 10.0f) {
        player->unk_3C += 10.0f;
        player->unk_80 = 10.0f;
    } else {
        player->unk_3C = target;
        player->unk_80 = target;
    }
    player->unk_84 = player->unk_80 / 30.0f;
    if (btn & 0x4000) {
        speed = 16.666666f;
        player->unk_4C = 0;
    } else if (btn & 0x8000) {
        speed = 41.666664f;
        player->unk_4C = 2;
    } else {
        speed = 27.777777f;
        player->unk_4C = 1;
    }
    if (speed < player->unk_08) {
        player->unk_08 -= 2.0f;
        if (player->unk_08 < speed) {
            player->unk_08 = speed;
        }
    } else if (player->unk_08 < speed) {
        player->unk_08 += 2.0f;
        if (speed < player->unk_08) {
            player->unk_08 = speed;
        }
    }
    if (stickX == 0) {
        player->unk_32 = 0;
    } else if (stickX < 0) {
        player->unk_32 = 1;
    } else {
        player->unk_32 = 2;
    }
    object->rot.y -= player->unk_3C / 30.0f;
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.y < 0.0f) {
        object->rot.y += 360.0f;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    if (object->trans.y < -500.0f) {
        object->trans.y = -500.0f;
    }
    if (object->trans.y > 500.0f) {
        object->trans.y = 500.0f;
    }
    player->unk_44 = 0.0f;
    if (player->unk_00 == 3) {
        if (player->unk_50 == 0) {
            player->unk_90 = 1;
            player->unk_00 = 0;
        } else {
            if (--player->unk_50 & 1) {
                player->unk_90 = 0;
            } else {
                player->unk_90 = 1;
            }
            player->unk_44 = shake[player->unk_50 & 3];
        }
    }
    m223_PlanePushApart(object);
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
    if (btn & Z_TRIG) {
        if (player->unk_54 == 1) {
            player->unk_52++;
            if (player->unk_52 >= 30) {
                player->unk_58 ^= 1;
            }
        }
    } else {
        if (player->unk_52 >= 30 && player->unk_54 == 1) {
            m223_MissileFire(object);
            _HuAudPlayerFXPlay(0x3B2, player->camIdx);
        }
        player->unk_52 = 0;
        player->unk_58 = 0;
    }
    if (player->unk_20 == 0) {
        if ((btnDown & Z_TRIG) && player->unk_24 != 0) {
            m223_ShotFire(object);
            _HuAudPlayerFXPlay(0x3AD, player->camIdx);
        }
    } else {
        player->unk_20--;
    }
    if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) >= 3950.0f) {
        player->unk_00 = 1;
        player->unk_48 = (500.0f - object->trans.y) / 45.0f;
        player->unk_4E = 45;
        player->unk_52 = 0;
        player->unk_92 = 0;
        object->func = m223_PlaneReturnObjMain;
    }
}

void m223_PlaneReturnObjMain(omObjData *object) {
    AceHighPlayer *player;
    u32 hit;
    f32 angle;

    hit = object->mode;
    object->mode = 0;
    player = object->data;
    if (hit & 2) {
        player->unk_56 = 1;
        player->unk_5C = 50.0f;
        Hu3DModelAttrSet(object->model[1], 4, 0);
    }
    if (hit & 4) {
        player->unk_74->work[0] = 45;
        player->unk_74->work[1] = 6;
        player->unk_74->work[2] = 1;
    }
    angle = atan2df(-object->trans.x, -object->trans.z);
    player->unk_58 = 0;
    switch (player->unk_00) {
        case 1:
            player->unk_38 -= 15.0f;
            if (player->unk_38 < -90.0f) {
                player->unk_38 = -90.0f;
            }
            object->rot.y += 20.0f;
            if (object->rot.y >= 360.0f) {
                object->rot.y -= 360.0f;
            }
            object->trans.y += player->unk_48;
            if (--player->unk_4E == 0) {
                object->trans.y = 500.0f;
                object->rot.y = angle;
                player->unk_3C = 0.0f;
                player->unk_00 = 2;
                player->unk_90 = 1;
            } else if (player->unk_4E & 1) {
                player->unk_90 = 0;
            } else {
                player->unk_90 = 1;
            }
            break;
        case 2:
            player->unk_38 += 15.0f;
            if (player->unk_38 >= 0.0f) {
                player->unk_38 = 0.0f;
                player->unk_00 = 0;
                object->func = m223_PlaneObjMain;
            }
            player->unk_90 = 1;
            break;
    }
    m223_PlaneShakeUpdate(object);
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
}

void m223_PlaneCrashObjMain(omObjData *object) {
    AceHighPlayer *player = object->data;

    switch (player->unk_00) {
        case 4:
            player->unk_38 += 10.0f;
            if (player->unk_38 >= 90.0f) {
                player->unk_38 = 90.0f;
                player->unk_00 = 5;
            }
            break;
        case 5:
            if (player->unk_36 == 0 && object->trans.y < -1000.0f) {
                player->unk_36 = 1;
            }
            if (object->trans.y < -3000.0f) {
                player->unk_00 = 6;
                object->func = NULL;
                player->unk_90 = 0;
                Hu3DModelAttrSet(object->model[3], 4, 4);
                player->camObj->func = m223_CameraOverObjMain;
                Hu3DModelCameraSet(m223_stageObj->model[3],
                                   Hu3DData[m223_stageObj->model[3]].cameraBit &
                                       ~m223_camBitTbl[player->camIdx]);
            }
            break;
    }
    player->dir.y = -sindf(player->unk_38);
    player->dir.x = sindf(object->rot.y) * (1.0 - fabs(player->dir.y));
    player->dir.z = cosdf(object->rot.y) * (1.0 - fabs(player->dir.y));
    object->trans.x += player->dir.x * player->unk_08;
    object->trans.y += player->dir.y * player->unk_08;
    object->trans.z += player->dir.z * player->unk_08;
    m223_PlaneShakeUpdate(object);
    m223_PlaneMdlUpdate(object);
    m223_PlaneSubMdlUpdate(object);
    Hu3DModelPosSet(object->model[3], object->trans.x, object->trans.y, object->trans.z);
    player->unk_74->work[2] = 0;
    player->unk_78->work[1] = 0;
    espDispOff(player->unk_2E);
    espDispOff(player->unk_30);
    if (player->unk_2C != -1) {
        HuAudFXStop(player->unk_2C);
        player->unk_2C = -1;
    }
}

void m223_PlaneShakeUpdate(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 x;
    f32 y;

    if (player->unk_5C > 0.0f) {
        player->unk_5C -= 10.0f;
        x = -sindf(player->unk_3C);
        y = sindf(player->unk_38);
        player->unk_60 = x * cosdf(-object->rot.y) - y * sindf(-object->rot.y);
        player->unk_64 = x * sindf(-object->rot.y) + y * cosdf(-object->rot.y);
        player->unk_68 = 1.0f - HuSqrtf(player->unk_60 * player->unk_60 + player->unk_64 * player->unk_64);
        player->unk_60 *= player->unk_5C;
        player->unk_68 *= player->unk_5C;
        player->unk_64 *= player->unk_5C;
        if (player->unk_5C <= 0.0f) {
            player->unk_5C = 0.0f;
            player->unk_54 = 1;
            player->unk_52 = 0;
        }
    }
}

void m223_LifeSprOffAll(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        AceHighPlayer *player = OM_GET_DATA_PTR(m223_planeObjTbl[i], AceHighPlayer);

        for (j = 0; j < 2; j++) {
            espDispOff(player->espriteSlots[j]);
        }
    }
}

void m223_PlanePushApart(omObjData *object) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *other;
    omObjData *otherObj;
    u16 tries;
    s32 i;
    f32 dist;
    f32 ofs;

    for (tries = 0; tries < 4; tries++) {
        for (i = 0; i < 4; i++) {
            if (i == player->camIdx) {
                continue;
            }
            otherObj = m223_planeObjTbl[i];
            other = otherObj->data;
            if (other->unk_00 == 6 || other->unk_00 == 1 || other->unk_00 == 3) {
                continue;
            }
            dist = HuSqrtf((object->trans.x - otherObj->trans.x) * (object->trans.x - otherObj->trans.x) +
                           (object->trans.y - otherObj->trans.y) * (object->trans.y - otherObj->trans.y) +
                           (object->trans.z - otherObj->trans.z) * (object->trans.z - otherObj->trans.z));
            if (dist <= HuSqrtf(32400.0f)) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        omVibrate(player->camIdx, 2, 3, 10);
        omVibrate(other->camIdx, 2, 3, 10);
        switch (tries) {
            case 0:
                ofs = -90.0f;
                if (object->trans.y + ofs >= -500.0f) {
                    object->trans.y += ofs;
                }
                break;
            case 1:
                ofs = 90.0f;
                if (object->trans.y + ofs <= 500.0f) {
                    object->trans.y += ofs;
                }
                break;
            case 2:
                ofs = 90.0f;
                object->trans.x += sindf(object->rot.y + ofs) * ofs;
                object->trans.z += cosdf(object->rot.y + ofs) * ofs;
                break;
            case 3:
                ofs = 90.0f;
                object->trans.x += sindf(object->rot.y - ofs) * ofs;
                object->trans.z += cosdf(object->rot.y - ofs) * ofs;
                break;
        }
    }
}

void m223_PlaneComInput(omObjData *object, s8 *stickX, s8 *stickY, u16 *btnDown, u16 *btn) {
    omObjData *list[4];
    Vec target;
    omObjData *nearest;
    f32 minDist;
    AceHighPlayer *player;
    AceHighPlayer *otherData;
    omObjData *other;
    f32 farDist;
    f32 nearDist;
    f32 fov;
    f32 angleTol;
    f32 missileDist;
    f32 dist;
    f32 angle;
    f32 rotY;
    f32 diff;
    f32 stick;
    u16 state;
    u16 result;

    *stickY = 0;
    *stickX = 0;
    *btn = 0;
    *btnDown = 0;
    player = object->data;
    switch (GwPlayer[player->camIdx].cpu_difficulty) {
        case 0:
            farDist = 1000.0f;
            nearDist = 500.0f;
            fov = 30.0f;
            angleTol = 5.0f;
            missileDist = 500.0f;
            break;
        case 1:
            farDist = 900.0f;
            nearDist = 500.0f;
            fov = 30.0f;
            angleTol = 4.0f;
            missileDist = 700.0f;
            break;
        case 2:
            farDist = 800.0f;
            nearDist = 400.0f;
            fov = 40.0f;
            angleTol = 3.0f;
            missileDist = 900.0f;
            break;
        case 3:
            farDist = 700.0f;
            nearDist = 400.0f;
            fov = 40.0f;
            angleTol = 3.0f;
            missileDist = 1200.0f;
            break;
    }
    state = player->unk_92;
    dist = HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z);
    if (dist > 3150.0f && state != 2 && !(state == 5 || state == 6)) {
        angle = atan2df(object->trans.x, object->trans.z);
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        rotY = object->rot.y;
        if (rotY < 0.0f) {
            rotY += 360.0f;
        }
        diff = rotY - angle;
        if (fabs(diff) < 75.0) {
            player->unk_94 = player->unk_92;
            player->unk_92 = 2;
            player->unk_A8 = angle - 180.0f;
            if (player->unk_A8 < 0.0f) {
                player->unk_A8 += 360.0f;
            }
        }
    }
    if (state == 0) {
        m223_PlaneComStateUpdate(object);
    }
    switch (state) {
        case 1:
            other = player->unk_98;
            otherData = other->data;
            if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (otherData->unk_00 == 6) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            dist = HuSqrtf((other->trans.x - object->trans.x) * (other->trans.x - object->trans.x) +
                           (other->trans.z - object->trans.z) * (other->trans.z - object->trans.z)) *
                   0.8f;
            if (dist > 1500.0f) {
                dist = 1500.0f;
            }
            if (dist < 100.0f) {
                dist = 100.0f;
            }
            target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
            target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
            target.y = other->trans.y;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            result = m223_PlaneComSteer(object, &target, angleTol, 60.0f, stickX, stickY);
            if (dist < 2400.0f) {
                *btnDown |= 0x2000;
            }
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (--player->unk_B0 == 0) {
                player->unk_92 = 0;
                player->unk_34 = 0;
            }
            break;
        case 3:
            other = player->unk_98;
            otherData = other->data;
            if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (otherData->unk_00 == 6) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            if (player->unk_AE == 0) {
                player->unk_92 = 0;
                player->unk_34 = 0;
                break;
            }
            dist = HuSqrtf((other->trans.x - object->trans.x) * (other->trans.x - object->trans.x) +
                           (other->trans.z - object->trans.z) * (other->trans.z - object->trans.z)) *
                   0.8f;
            if (dist > 1500.0f) {
                dist = 1500.0f;
            }
            if (dist < 100.0f) {
                dist = 100.0f;
            }
            target.x = sindf(other->rot.y - 180.0f) * dist + other->trans.x;
            target.z = cosdf(other->rot.y - 180.0f) * dist + other->trans.z;
            target.y = other->trans.y;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            result = m223_PlaneComSteer(object, &target, angleTol, 60.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            break;
        case 4:
            target = player->unk_9C;
            dist = HuSqrtf((object->trans.x - player->unk_9C.x) * (object->trans.x - player->unk_9C.x) +
                           (object->trans.y - player->unk_9C.y) * (object->trans.y - player->unk_9C.y) +
                           (object->trans.z - player->unk_9C.z) * (object->trans.z - player->unk_9C.z));
            result = m223_PlaneComSteer(object, &target, angleTol, 20.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (dist < 100.0f) {
                player->unk_92 = 0;
            }
            if (--player->unk_B0 == 0) {
                player->unk_92 = 0;
            }
            break;
        case 2:
            angle = player->unk_A8;
            rotY = object->rot.y;
            if (rotY < 0.0f) {
                rotY += 360.0f;
            }
            diff = rotY - angle;
            if (fabs(diff) < 5.0) {
                player->unk_92 = player->unk_94;
                break;
            }
            if (fabs(diff) > 35.0) {
                stick = 70.0f;
            } else {
                stick = fabs(diff / 2.0f);
            }
            if (stick < 10.0f) {
                stick = 10.0f;
            }
            if (diff < 0.0f) {
                diff += 360.0f;
            }
            if (diff < 180.0f) {
                *stickX = stick;
            } else {
                *stickX = -stick;
            }
            if (HuSqrtf(object->trans.x * object->trans.x + object->trans.z * object->trans.z) > 3600.0f) {
                *btn |= 0x4000;
            }
            break;
        case 5:
            target = player->unk_9C;
            dist = HuSqrtf((object->trans.x - player->unk_9C.x) * (object->trans.x - player->unk_9C.x) +
                           (object->trans.y - player->unk_9C.y) * (object->trans.y - player->unk_9C.y) +
                           (object->trans.z - player->unk_9C.z) * (object->trans.z - player->unk_9C.z));
            result = m223_PlaneComSteer(object, &target, 3.0f, 20.0f, stickX, stickY);
            if ((farDist < dist && !(result & 0x4000)) || (result & 0x8000)) {
                *btn |= 0x8000;
            }
            if ((dist < nearDist && !(result & 0x8000)) || (result & 0x4000)) {
                *btn |= 0x4000;
            }
            if (MgFlowStatGet() == MG_STATE_RESULT) {
                player->unk_92 = 6;
                m223_CameraViewFix(object);
                player->camObj->func = m223_CameraEndObjMain;
                object->func = m223_PlaneEndObjMain;
                player->unk_4E = 25;
            }
            break;
        case 6:
            if (player->unk_4E != 0) {
                *stickY = -45;
                *stickX = -65;
                player->unk_4E--;
            } else {
                *stickY = -70;
                player->unk_0C = 1;
            }
            *btn |= 0x8000;
            break;
    }
    if (state == 5 || state == 6) {
        return;
    }
    if (m223_PlaneComTargetFind(object, fov, list, &nearest, &minDist) != 0) {
        if (minDist <= 2750.0f) {
            *btnDown |= 0x2000;
        }
        if (player->unk_92 == 1 && minDist < 1000.0f) {
            player->unk_B0 = rand8() % 181 + 60;
            player->unk_92 = 1;
            player->unk_98 = nearest;
        }
    }
    if (player->unk_70 != 0 && m223_ShotNearDistGet(object) < missileDist) {
        *btn = (*btn & ~0x4000) | 0x8000;
    }
    if (player->unk_AE != 0) {
        if (player->unk_52 < player->unk_AC) {
            *btn |= 0x2000;
        } else {
            player->unk_AE = 0;
        }
    }
    m223_PlaneComEvade(object);
}

u16 m223_PlaneComSteer(omObjData *object, Vec *target, f32 angleTol, f32 heightTol, s8 *stickX, s8 *stickY) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *other;
    f32 scale;
    f32 angle;
    f32 rotY;
    f32 diff;
    f32 stick;
    f32 dy;
    u16 btn;

    scale = HuSqrtf((target->x - object->trans.x) * (target->x - object->trans.x) +
                    (target->z - object->trans.z) * (target->z - object->trans.z)) /
            600.0f;
    if (scale > 2.0f) {
        scale = 2.0f;
    }
    if (scale < 0.3f) {
        scale = 0.3f;
    }
    btn = 0;
    angle = atan2df(target->x - object->trans.x, target->z - object->trans.z);
    rotY = object->rot.y;
    if (rotY > 180.0f) {
        rotY -= 360.0f;
    }
    diff = rotY - angle;
    if (fabs(diff) < angleTol) {
        *stickX = 0;
    } else {
        if (fabs(diff * scale) > 70.0) {
            stick = 70.0f;
            btn = 0x4000;
        } else {
            stick = fabs(diff * scale);
        }
        if (stick < 10.0f) {
            stick = 0.0f;
        }
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        if (rotY < 0.0f) {
            rotY += 360.0f;
        }
        diff = angle - rotY;
        if (diff < 0.0f) {
            diff += 360.0f;
        }
        if (diff > 180.0f) {
            *stickX = stick;
        } else {
            *stickX = -stick;
        }
        if (player->unk_92 == 1 || player->unk_92 == 3) {
            other = player->unk_98->data;
            if (other->unk_32 == player->unk_32 && other->unk_34 == 0) {
                if (rand8() % 10 < 5) {
                    player->unk_34 ^= 1;
                }
            }
            if (player->unk_34 != 0) {
                *stickX = -*stickX;
            }
        }
    }
    dy = target->y - object->trans.y;
    if (fabs(dy) > heightTol) {
        if (fabs(dy * scale) > 70.0) {
            stick = 70.0f;
        } else {
            stick = fabs(dy * scale);
        }
        if (stick < 10.0f) {
            stick = 0.0f;
        }
        if (target->y > object->trans.y) {
            *stickY = -stick;
        } else {
            *stickY = stick;
        }
    }
    return btn;
}

void m223_PlaneComStateUpdate(omObjData *object) {
    u16 actions[4][8] = {
        { 4, 1, 4, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 4, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
        { 4, 1, 1, 1, 1, 1, 1, 1 },
    };
    AceHighPlayer *player = object->data;
    omObjData *otherObj;
    s16 chance;
    u16 action;
    u16 done;
    s32 i;
    u16 state;
    f32 angle;
    f32 dist;

    switch (GwPlayer[player->camIdx].cpu_difficulty) {
        case 0:
            chance = 2;
            break;
        case 1:
            chance = 3;
            break;
        case 2:
            chance = 4;
            break;
        case 3:
            chance = 4;
            break;
    }
    if (m223_aliveNum == 2) {
        chance *= 2;
    }
    done = 0;
    action = actions[GwPlayer[player->camIdx].cpu_difficulty][rand8() & 7];
    while (done == 0) {
        switch (action) {
            case 1:
                for (i = 0; i < 4; i++) {
                    if (i == player->camIdx) {
                        continue;
                    }
                    otherObj = m223_planeObjTbl[i];
                    state = ((AceHighPlayer *)otherObj->data)->unk_00;
                    if (state == 6 || state == 4) {
                        continue;
                    }
                    if (state == 5 || state == 1) {
                        continue;
                    }
                    break;
                }
                if (i == 4) {
                    action = 4;
                    break;
                }
                player->unk_98 = otherObj;
                if (player->unk_54 == 1 && rand8() % 10 < chance) {
                    player->unk_AC = (rand8() & 0xF) + 30;
                    player->unk_AE = 1;
                    player->unk_92 = 3;
                    done = 1;
                } else {
                    player->unk_B0 = rand8() % 181 + 60;
                    player->unk_92 = 1;
                    done = 1;
                }
                break;
            case 4:
                if (m223_aliveNum == 2 && rand8() % 10 < 2) {
                    action = 1;
                    break;
                }
                angle = atan2df(object->trans.x, object->trans.z) - 180.0f;
                if (angle < 0.0f) {
                    angle += 360.0f;
                }
                angle *= 10.0f;
                angle += (rand8() * rand8()) % 900 - 450.0f;
                angle /= 10.0f;
                dist = (rand8() * rand8()) % 2750 + 200.0f;
                player->unk_9C.x = sindf(angle) * dist;
                player->unk_9C.z = cosdf(angle) * dist;
                player->unk_9C.y = (rand8() * rand8()) % 1000 + -500.0f;
                player->unk_92 = 4;
                player->unk_B0 = rand8() % 121 + 60;
                done = 1;
                break;
        }
    }
}

s16 m223_PlaneComTargetFind(omObjData *object, f32 fov, omObjData **list, omObjData **nearest, f32 *minDist) {
    s16 count = 0;
    AceHighPlayer *player = object->data;
    omObjData *other;
    u16 state;
    s32 i;
    f32 angle;
    f32 rotY;
    f32 dist;

    *list = NULL;
    *minDist = 1000000.0f;
    *nearest = NULL;
    for (i = 0; i < 4; i++) {
        if (player->camIdx == i) {
            continue;
        }
        other = m223_planeObjTbl[i];
        state = ((AceHighPlayer *)other->data)->unk_00;
        if (state == 6 || state == 4) {
            continue;
        }
        if (state == 5 || state == 1) {
            continue;
        }
        angle = atan2df(other->trans.x - object->trans.x, other->trans.z - object->trans.z);
        rotY = object->rot.y;
        if (rotY > 180.0f) {
            rotY -= 360.0f;
        }
        if (fabs(rotY - angle) <= fov / 2.0f) {
            list[count++] = other;
            dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                           (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                           (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
            if (dist < *minDist) {
                *minDist = dist;
                *nearest = other;
            }
        }
    }
    return count;
}

f32 m223_ShotNearDistGet(omObjData *object) {
    AceHighPlayer *player = object->data;
    omObjData **shots;
    omObjData *shot;
    f32 minDist;
    f32 dist;
    s32 i;
    s32 j;

    minDist = 10000000.0f;
    for (i = 0; i < 4; i++) {
        if (i == player->camIdx) {
            continue;
        }
        shots = m223_shotObjTbl[i];
        for (j = 0; j < 5; j++) {
            shot = shots[j];
            if (shot == NULL || ((AceHighShot *)shot->data)->unk_00 != 1) {
                continue;
            }
            dist = HuSqrtf((shot->trans.x - object->trans.x) * (shot->trans.x - object->trans.x) +
                           (shot->trans.y - object->trans.y) * (shot->trans.y - object->trans.y) +
                           (shot->trans.z - object->trans.z) * (shot->trans.z - object->trans.z));
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

void m223_PlaneComEvade(omObjData *object) {
    AceHighPlayer *player = object->data;
    s32 i;
    f32 angle;
    f32 dist;

    for (i = 0; i < 4; i++) {
        if (((AceHighPlayer *)m223_planeObjTbl[i]->data)->unk_98 != object) {
            continue;
        }
        if (player->unk_92 == 4) {
            continue;
        }
        if (rand8() % 10 >= 5) {
            continue;
        }
        player->unk_98 = NULL;
        angle = atan2df(object->trans.x, object->trans.z) - 180.0f;
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        angle *= 10.0f;
        angle += (rand8() * rand8()) % 900 - 450.0f;
        angle /= 10.0f;
        dist = (rand8() * rand8()) % 2750 + 200.0f;
        player->unk_9C.x = sindf(angle) * dist;
        player->unk_9C.z = cosdf(angle) * dist;
        player->unk_9C.y = (rand8() * rand8()) % 1000 + -500.0f;
        player->unk_92 = 4;
        player->unk_B0 = rand8() % 121 + 60;
    }
}

void m223_CameraFollowObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotX;
    f32 rotY;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    if (player->unk_00 != 4 && player->unk_00 != 5) {
        rotY = playerObj->rot.y - 180.0f;
        CRotM[player->camIdx].y = rotY;
        rotX = playerObj->trans.y * 0.06f;
        CRotM[player->camIdx].x = rotX;
        x = playerObj->trans.x + sindf(playerObj->rot.y) * 300.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 300.0f;
        y = playerObj->trans.y + 100.0f;
        CenterM[player->camIdx].x = x;
        CenterM[player->camIdx].y = y;
        CenterM[player->camIdx].z = z;
        if (player->unk_08 > 27.777777f) {
            zoom = (player->unk_08 - 27.777777f) / 13.888887f * 150.0f + 1000.0f;
        } else if (player->unk_08 < 27.777777f) {
            zoom = 1000.0f - (27.777777f - player->unk_08) / 11.111111f * 150.0f;
        } else {
            zoom = 1000.0f;
        }
        CZoomM[player->camIdx] = zoom;
    } else {
        rotX = playerObj->trans.y * 0.06f;
        if (rotX < -90.0f) {
            rotX = -90.0f;
        }
        CRotM[player->camIdx].x = rotX;
        x = playerObj->trans.x + sindf(playerObj->rot.y) * 300.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 300.0f;
        y = playerObj->trans.y + 100.0f;
        CenterM[player->camIdx].x = x;
        CenterM[player->camIdx].y = y;
        CenterM[player->camIdx].z = z;
        CZoomM[player->camIdx] =
            HuSqrtf((object->trans.x - playerObj->trans.x) * (object->trans.x - playerObj->trans.x) +
                    (object->trans.y - playerObj->trans.y) * (object->trans.y - playerObj->trans.y) +
                    (object->trans.z - playerObj->trans.z) * (object->trans.z - playerObj->trans.z));
    }
}

void m223_CameraPosCalc(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 rotX = CRotM[player->camIdx].x;
    f32 rotY = CRotM[player->camIdx].y;

    player->camObj->trans.x = CenterM[player->camIdx].x + sindf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    player->camObj->trans.y = CenterM[player->camIdx].y + -sindf(rotX) * CZoomM[player->camIdx];
    player->camObj->trans.z = CenterM[player->camIdx].z + cosdf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
}

void m223_CameraIntroObjMain(omObjData *object) {
    omObjData *camObj = (omObjData *)object->work[1];
    AceHighPlayer *camData = (AceHighPlayer *)camObj->data;
    f32 rotX = (camObj->trans.y - -250.0f) * 0.08f;

    CRotM[camData->camIdx].x = rotX;
    CRotM[camData->camIdx].z = 0.0f;
    CRotM[camData->camIdx].y = camData->unk_8C;
    CenterM[camData->camIdx].x = camObj->trans.x;
    CenterM[camData->camIdx].y = 0.0f;
    CenterM[camData->camIdx].z = camObj->trans.z;
    CZoomM[camData->camIdx] = 650.0f;
}

void m223_CameraStartObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;

    object->work[2]++;
    CRotM[player->camIdx].x += (playerObj->trans.y * 0.06f - object->scale.x) / 30.0f;
    CenterM[player->camIdx].x = sindf(playerObj->rot.y) * 300.0f / 30.0f * object->work[2] + playerObj->trans.x;
    CenterM[player->camIdx].z = cosdf(playerObj->rot.y) * 300.0f / 30.0f * object->work[2] + playerObj->trans.z;
    CenterM[player->camIdx].y += (playerObj->trans.y + 100.0f) / 30.0f;
    CZoomM[player->camIdx] += 11.666667f;
}

void m223_CameraOverObjMain(omObjData *object) {
    AceHighPlayer *camData = (AceHighPlayer *)((omObjData *)object->work[1])->data;

    CenterM[camData->camIdx].y = 0.0f;
    CZoomM[camData->camIdx] = 2700.0f;
    CRotM[camData->camIdx].x = 90.0f;
}

void m223_CameraWinStart(omObjData *object) {
    AceHighPlayer *player = object->data;
    omObjData *camObj = player->camObj;

    camObj->scale.x = -180.0f;
    camObj->trans.x = (-10.0f - CRotM[player->camIdx].x) / 60.0f;
    camObj->trans.y = CRotM[player->camIdx].x;
    camObj->scale.y = -4.5f;
    camObj->scale.z = (750.0f - CZoomM[player->camIdx]) / 60.0f;
    camObj->trans.z = CZoomM[player->camIdx];
    camObj->work[2] = 0;
    camObj->func = m223_CameraWinObjMain;
}

void m223_CameraWinObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotY;
    f32 rotX;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    rotY = playerObj->rot.y + object->scale.x;
    object->scale.x += 3.0f;
    rotX = object->trans.y + object->work[2] * object->trans.x;
    x = playerObj->trans.x + sindf(playerObj->rot.y) * (object->work[2] * object->scale.y + 300.0f);
    z = playerObj->trans.z + cosdf(playerObj->rot.y) * (object->work[2] * object->scale.y + 300.0f);
    y = playerObj->trans.y + 100.0f;
    zoom = object->trans.z + object->work[2] * object->scale.z;
    if (object->work[2]++ >= 60) {
        rotY = playerObj->rot.y;
        rotX = -10.0f;
        x = playerObj->trans.x + sindf(rotY) * 30.0f;
        z = playerObj->trans.z + cosdf(playerObj->rot.y) * 30.0f;
        y = playerObj->trans.y + 100.0f;
        zoom = 750.0f;
        object->func = m223_CameraWinHoldObjMain;
    }
    CRotM[player->camIdx].y = rotY;
    CRotM[player->camIdx].x = rotX;
    CenterM[player->camIdx].x = x;
    CenterM[player->camIdx].y = y;
    CenterM[player->camIdx].z = z;
    CZoomM[player->camIdx] = zoom;
}

void m223_CameraWinHoldObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotY;
    f32 x;
    f32 y;
    f32 z;
    f32 zoom;

    rotY = playerObj->rot.y;
    CRotM[player->camIdx].y = rotY;
    CRotM[player->camIdx].x = -10.0f;
    x = sindf(playerObj->rot.y) * 30.0f + playerObj->trans.x;
    z = cosdf(playerObj->rot.y) * 30.0f + playerObj->trans.z;
    y = playerObj->trans.y + 100.0f;
    CenterM[player->camIdx].x = x;
    CenterM[player->camIdx].y = y;
    CenterM[player->camIdx].z = z;
    zoom = 750.0f;
    CZoomM[player->camIdx] = zoom;
}

void m223_CameraViewObjMain(omObjData *object) {
    Hu3DCameraPosSetV(OM_GET_WORK_PTR(object, s16)[1], &m223_winCameraPos, &m223_winCameraTarget,
                      &m223_winCameraUp);
    Hu3DCamUpdateMtx(OM_GET_WORK_PTR(object, s16)[1]);
}

void m223_CameraViewFix(omObjData *object) {
    AceHighPlayer *player = object->data;
    f32 rotX = CRotM[player->camIdx].x;
    f32 rotY = CRotM[player->camIdx].y;

    m223_winCameraPos.x = CenterM[player->camIdx].x + sindf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    m223_winCameraPos.y = CenterM[player->camIdx].y + -sindf(rotX) * CZoomM[player->camIdx];
    m223_winCameraPos.z = CenterM[player->camIdx].z + cosdf(rotY) * cosdf(rotX) * CZoomM[player->camIdx];
    m223_winCameraTarget.x = CenterM[player->camIdx].x;
    m223_winCameraTarget.y = CenterM[player->camIdx].y;
    m223_winCameraTarget.z = CenterM[player->camIdx].z;
    m223_winCameraUp.x = sindf(rotY) * sindf(rotX);
    m223_winCameraUp.y = cosdf(rotX);
    m223_winCameraUp.z = cosdf(rotY) * sindf(rotX);
    omDelObj(m223_cameraObj);
    m223_cameraObj = omAddObj(0x7FDA, 0, 0, -1, m223_CameraViewObjMain);
    m223_cameraObj->work[0] = player->camIdx;
    omSetStatBit(m223_cameraObj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void m223_CameraEndObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[1];
    AceHighPlayer *player = playerObj->data;
    f32 rotX;
    f32 rotY;

    m223_winCameraTarget.x = sindf(playerObj->rot.y) * 30.0f + playerObj->trans.x;
    m223_winCameraTarget.z = cosdf(playerObj->rot.y) * 30.0f + playerObj->trans.z;
    m223_winCameraTarget.y = playerObj->trans.y + 100.0f;
    CRotM[player->camIdx].y =
        atan2df(playerObj->trans.x - m223_winCameraPos.x, playerObj->trans.z - m223_winCameraPos.z);
    rotX = CRotM[player->camIdx].x;
    rotY = CRotM[player->camIdx].y;
    m223_winCameraUp.x = sindf(rotY) * sindf(rotX);
    m223_winCameraUp.y = cosdf(rotX);
    m223_winCameraUp.z = cosdf(rotY) * sindf(rotX);
}

void m223_ShotInit(void) {
    s32 i;

    m223_shotMdlObj = omAddObj(28, 4, 0, -1, m223_ShotHitObjMain);
    for (i = 0; i < 4; i++) {
        m223_shotMdlObj->model[i] = Hu3DModelRead(m223_shotMdlFileTbl[GwPlayer[i].chr], 0xADD);
    }
    for (i = 0; i < 20; i++) {
        m223_shotEffUseTbl[i] = 0;
        m223_shotEffMdlTbl[i] = Hu3DModelRead(0x380020, 0xADD);
    }
    for (i = 0; i < 4; i++) {
        omMakeGroup(i + 1, 5);
        m223_shotObjTbl[i] = omGetGroupMemberList(i + 1);
    }
}

void m223_ShotHitObjMain(omObjData *object) {
    omObjData **shots;
    omObjData **otherShots;
    omObjData *shot;
    omObjData *other;
    AceHighShot *shotData;
    AceHighShot *otherData;
    f32 dist;
    s32 i;
    s32 j;
    s32 k;
    s32 m;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    for (i = 0; i < 4; i++) {
        shots = m223_shotObjTbl[i];
        for (j = 0; j < 5; j++) {
            if (shots[j] == NULL) {
                continue;
            }
            shot = shots[j];
            shotData = shot->data;
            if (shotData->unk_02 == 1) {
                continue;
            }
            for (k = 0; k < 4; k++) {
                if (k == i) {
                    continue;
                }
                other = m223_planeObjTbl[k];
                if (((AceHighPlayer *)other->data)->unk_00 != 0) {
                    continue;
                }
                dist = HuSqrtf((other->trans.x - shot->trans.x) * (other->trans.x - shot->trans.x) +
                               (other->trans.y - shot->trans.y) * (other->trans.y - shot->trans.y) +
                               (other->trans.z - shot->trans.z) * (other->trans.z - shot->trans.z));
                if (HuSqrtf((shotData->radius + 90.0f) * (shotData->radius + 90.0f)) < dist) {
                    continue;
                }
                omObjModeSet(other, 1);
                omObjModeSet(shot, 1);
            }
            for (k = 0; k < 4; k++) {
                if (k == i) {
                    continue;
                }
                otherShots = m223_shotObjTbl[k];
                for (m = 0; m < 5; m++) {
                    other = otherShots[m];
                    if (other == NULL) {
                        continue;
                    }
                    if (other == shot) {
                        continue;
                    }
                    otherData = other->data;
                    if (otherData->unk_02 == 1) {
                        continue;
                    }
                    dist = HuSqrtf((shot->trans.x - other->trans.x) * (shot->trans.x - other->trans.x) +
                                   (shot->trans.y - other->trans.y) * (shot->trans.y - other->trans.y) +
                                   (shot->trans.z - other->trans.z) * (shot->trans.z - other->trans.z));
                    if (HuSqrtf((shotData->radius + otherData->radius) * (shotData->radius + otherData->radius)) <
                        dist) {
                        continue;
                    }
                    omObjModeSet(shot, 1);
                    omObjModeSet(other, 1);
                }
            }
        }
    }
}

void m223_ShotFire(omObjData *object) {
    AceHighPlayer *player;
    omObjData *shotObj;
    AceHighShot *shot;
    Vec dir;
    f32 rotY;
    f32 len;
    u16 idx;
    s32 i;

    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    player = object->data;
    player->unk_20 = 10;
    player->unk_24--;
    idx = player->camIdx;
    shotObj = omAddObj(28, 1, 0, idx + 1, m223_ShotObjMain);
    shot = shotObj->data = HuMemAllocTag(sizeof(AceHighShot), 0x7918);
    shotObj->model[0] = Hu3DModelLink(m223_shotMdlObj->model[idx]);
    Hu3DModelAttrSet(shotObj->model[0], 4, 0);
    shot->unk_00 = 0;
    shot->speed = player->unk_08 + 27.777777f;
    dir = player->dir;
    rotY = object->rot.y - player->unk_80;
    shot->dir.y = -sindf(player->unk_38) * 0.5f;
    shot->dir.x = sindf(rotY) * (1.0 - fabs(shot->dir.y));
    shot->dir.z = cosdf(rotY) * (1.0 - fabs(shot->dir.y));
    shot->dir.x += dir.x;
    shot->dir.y += dir.y;
    shot->dir.z += dir.z;
    len = HuSqrtf(shot->dir.x * shot->dir.x + shot->dir.y * shot->dir.y + shot->dir.z * shot->dir.z);
    shot->dir.x /= len;
    shot->dir.y /= len;
    shot->dir.z /= len;
    shot->owner = object;
    shot->unk_02 = 0;
    shot->unk_08 = 2400.0f;
    shot->radius = 30.0f;
    shot->unk_26 = 0;
    for (i = 0; i < 20; i++) {
        if (m223_shotEffUseTbl[i] == 0) {
            break;
        }
    }
    if (i == 20) {
        shot->effectIdx = -1;
    } else {
        shot->effectIdx = i;
        shot->effectModel = m223_shotEffMdlTbl[i];
        m223_shotEffUseTbl[i] = 1;
    }
    omSetTra(shotObj, object->trans.x, object->trans.y, object->trans.z);
}

void m223_ShotKillAll(void) {
    omObjData **shots;
    AceHighPlayer *player;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        shots = m223_shotObjTbl[i];
        for (j = 0; j < 5; j++) {
            if (shots[j] != NULL) {
                omObjModeSet(shots[j], 1);
            }
        }
        player = m223_planeObjTbl[i]->data;
        for (j = 0; j < 4; j++) {
            player->unk_74->work[2] = 0;
        }
    }
}

void m223_ShotObjMain(omObjData *object) {
    AceHighShot *shot = object->data;
    AceHighPlayer *owner;
    u32 hit;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        shot->unk_02 = 1;
        Hu3DModelAttrSet(shot->effectModel, 4, 0);
        Hu3DMotionAttrSet(shot->effectModel, 3, 0);
        Hu3DMotionTimeSet(shot->effectModel, 0.0f);
        Hu3DModelPosSet(shot->effectModel, object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelKill(object->model[0]);
        shot->timer = 30;
        shot->radius = 50.0f;
    }
    switch (shot->unk_02) {
        case 0:
            object->trans.x += shot->dir.x * shot->speed;
            object->trans.y += shot->dir.y * shot->speed;
            object->trans.z += shot->dir.z * shot->speed;
            shot->unk_08 -= shot->speed;
            if (shot->unk_08 < 0.0f) {
                owner = shot->owner->data;
                _HuAudPlayerFXPlay(0x3AE, owner->camIdx);
                omObjModeSet(object, 1);
            }
            break;
        case 1:
            if (shot->timer == 0) {
                Hu3DModelAttrSet(shot->effectModel, 4, 4);
                m223_shotEffUseTbl[shot->effectIdx] = 0;
                owner = shot->owner->data;
                owner->unk_24++;
                omDelObj(object);
            } else {
                shot->timer--;
            }
            break;
    }
}

void m223_MissileFire(omObjData *object) {
    AceHighPlayer *player = object->data;
    AceHighPlayer *otherData;
    omObjData *shotObj;
    omObjData *other;
    AceHighShot *shot;
    f32 minDist;
    f32 dist;
    s32 i;

    Hu3DModelAttrSet(object->model[1], 4, 0);
    Hu3DModelAttrSet(object->model[2], 4, 4);
    player->unk_58 = 0;
    if (MgFlowStatGet() != MG_STATE_PLAY) {
        return;
    }
    player->unk_56 = 0;
    player->unk_54 = 0;
    shotObj = player->unk_6C = omAddObj(28, 1, 0, player->camIdx + 1, m223_MissileObjMain);
    shotObj->data = HuMemAllocTag(sizeof(AceHighShot), 0x7918);
    shotObj->model[0] = object->model[1];
    shotObj->trans.x = object->trans.x;
    shotObj->trans.y = object->trans.y;
    shotObj->trans.z = object->trans.z;
    shotObj->rot.x = object->rot.x;
    shotObj->rot.y = object->rot.y;
    shotObj->rot.z = object->rot.z;
    shot = shotObj->data;
    shot->unk_00 = 1;
    shot->speed = 52.777775f;
    shot->dir = player->dir;
    shot->owner = object;
    shot->unk_02 = 0;
    shot->unk_08 = 7900.0f;
    shot->radius = 35.0f;
    shot->unk_26 = 0;
    shot->unk_2C = player->unk_38;
    shot->unk_30 = object->rot.y;
    if (shot->unk_2C < 0.0f) {
        shot->unk_2C += 360.0f;
    }
    shot->unk_34 = 20;
    shot->unk_36 = 0;
    for (i = 0; i < 20; i++) {
        if (m223_shotEffUseTbl[i] == 0) {
            break;
        }
    }
    if (i == 20) {
        shot->effectIdx = -1;
    } else {
        shot->effectIdx = i;
        shot->effectModel = m223_shotEffMdlTbl[i];
        m223_shotEffUseTbl[i] = 1;
    }
    minDist = 1000000.0f;
    shot->target = NULL;
    for (i = 0; i < 4; i++) {
        if (i == player->camIdx) {
            continue;
        }
        other = m223_planeObjTbl[i];
        otherData = other->data;
        if (otherData->unk_00 == 4 || otherData->unk_00 == 5) {
            continue;
        }
        if (otherData->unk_00 == 6) {
            continue;
        }
        dist = HuSqrtf((object->trans.x - other->trans.x) * (object->trans.x - other->trans.x) +
                       (object->trans.y - other->trans.y) * (object->trans.y - other->trans.y) +
                       (object->trans.z - other->trans.z) * (object->trans.z - other->trans.z));
        if (dist < minDist) {
            minDist = dist;
            shot->target = other;
        }
    }
    if (shot->target != NULL) {
        otherData = shot->target->data;
        otherData->unk_70++;
        omObjModeSet(shot->target, 4);
        otherData->unk_78->work[1] = 1;
    }
    omVibrate(player->camIdx, 10, 0, 10);
}

void m223_MissileObjMain(omObjData *object) {
    AceHighShot *shot = object->data;
    AceHighPlayer *playerData;
    u32 hit;
    f32 yaw;
    f32 pitch;
    f32 yawDelta;
    f32 len;
    f32 diff;

    hit = object->mode;
    object->mode = 0;
    if (hit & 1) {
        shot->unk_02 = 1;
        Hu3DModelAttrSet(shot->effectModel, 4, 0);
        Hu3DMotionAttrSet(shot->effectModel, 3, 0);
        Hu3DMotionTimeSet(shot->effectModel, 0.0f);
        Hu3DModelPosSet(shot->effectModel, object->trans.x, object->trans.y, object->trans.z);
        Hu3DModelAttrSet(object->model[0], 4, 4);
        shot->timer = 30;
        shot->radius = 50.0f;
        playerData = shot->owner->data;
        playerData->unk_6C = NULL;
        if (shot->target != NULL) {
            playerData = shot->target->data;
            if (--playerData->unk_70 < 0) {
                playerData->unk_70 = 0;
            }
        }
    }
    switch (shot->unk_02) {
        case 0:
            if (shot->target != NULL) {
                playerData = shot->target->data;
                if (playerData->unk_00 == 4 || playerData->unk_00 == 5) {
                    shot->target = NULL;
                } else if (playerData->unk_00 == 6) {
                    shot->target = NULL;
                } else {
                    yaw = atan2df(shot->target->trans.x - object->trans.x, shot->target->trans.z - object->trans.z);
                    if (yaw < 0.0f) {
                        yaw += 360.0f;
                    }
                    if (shot->target->trans.y == object->trans.y) {
                        pitch = 0.0f;
                    } else {
                        pitch = atan2df(shot->target->trans.y - object->trans.y,
                                        shot->target->trans.z - object->trans.z);
                    }
                    if (pitch > 90.0f) {
                        pitch = 180.0f - pitch;
                    }
                    if (pitch < -90.0f) {
                        pitch = -180.0f - pitch;
                    }
                    yawDelta = yaw - shot->unk_30;
                    len = HuSqrtf(pitch * pitch + yawDelta * yawDelta);
                    if (len != 0.0f) {
                        len = 1.0f / len;
                        pitch = fabs(pitch * len * 3.5f);
                        yawDelta = fabs(yawDelta * len * 3.5f);
                    } else {
                        pitch = 3.5f;
                        yawDelta = pitch;
                    }
                    diff = yaw - shot->unk_30;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (yawDelta < diff) {
                            shot->unk_30 += yawDelta;
                        } else {
                            shot->unk_30 = yaw;
                        }
                    } else if (yawDelta < 360.0f - diff) {
                        shot->unk_30 -= yawDelta;
                    } else {
                        shot->unk_30 = yaw;
                    }
                    if (shot->unk_30 < 0.0f) {
                        shot->unk_30 += 360.0f;
                    }
                    if (shot->unk_30 >= 360.0f) {
                        shot->unk_30 -= 360.0f;
                    }
                    if (shot->target->trans.y == object->trans.y) {
                        yaw = 0.0f;
                    } else {
                        yaw = atan2df(shot->target->trans.y - object->trans.y,
                                      shot->target->trans.z - object->trans.z);
                    }
                    if (yaw > 90.0f) {
                        yaw = 180.0f - yaw;
                    }
                    if (yaw < -90.0f) {
                        yaw = -180.0f - yaw;
                    }
                    if (yaw < 0.0f) {
                        yaw += 360.0f;
                    }
                    if (yaw >= 360.0f) {
                        yaw -= 360.0f;
                    }
                    diff = yaw - shot->unk_2C;
                    if (diff < 0.0f) {
                        diff += 360.0f;
                    }
                    if (diff < 180.0f) {
                        if (pitch < diff) {
                            shot->unk_2C += pitch;
                        } else {
                            shot->unk_2C = yaw;
                        }
                    } else if (pitch < 360.0f - diff) {
                        shot->unk_2C -= pitch;
                    } else {
                        shot->unk_2C = yaw;
                    }
                    if (shot->unk_2C < 0.0f) {
                        shot->unk_2C += 360.0f;
                    }
                    if (shot->unk_2C >= 360.0f) {
                        shot->unk_2C -= 360.0f;
                    }
                    if (shot->unk_34 == 0) {
                        if (shot->unk_36 == 0) {
                            shot->dir.y = sindf(shot->unk_2C);
                            shot->dir.x = sindf(shot->unk_30) * (1.0 - fabs(shot->dir.y));
                            shot->dir.z = cosdf(shot->unk_30) * (1.0 - fabs(shot->dir.y));
                            shot->unk_36 = 2;
                        } else {
                            shot->unk_36--;
                        }
                    } else {
                        shot->unk_34--;
                    }
                }
            }
            object->trans.x += shot->dir.x * shot->speed;
            object->trans.y += shot->dir.y * shot->speed;
            object->trans.z += shot->dir.z * shot->speed;
            func_80088910_main(Hu3DData[object->model[0]].mtx, -shot->unk_2C, 0.0f, 0.0f);
            object->rot.y = shot->unk_30;
            shot->unk_08 -= shot->speed;
            if (shot->unk_08 < 0.0f) {
                omObjModeSet(object, 1);
            }
            break;
        case 1:
            if (shot->timer == 0) {
                Hu3DModelAttrSet(shot->effectModel, 4, 4);
                m223_shotEffUseTbl[shot->effectIdx] = 0;
                omObjModeSet(shot->owner, 2);
                omDelObj(object);
            } else {
                shot->timer--;
            }
            break;
    }
}

void m223_RadarInit(void) {
    omObjData *obj = omAddObj(0x1E, 0, 0, -1, m223_RadarObjMain);

    m223_radarObj = obj;
    obj->work[0] = 1;
    m223_radarSpr = espEntry(HuSprAnimDataRead(0x38001C), 0, 0);
    espPosSet(m223_radarSpr, 0xA0, 0x78);
    espPriSet(m223_radarSpr, 0x8064);
}

void m223_RadarObjMain(omObjData *object) {
    u16 order[4] = { 0, 1, 2, 3 };
    AceHighPlayer *player;
    f32 scale;
    s16 x;
    s16 y;
    omObjData *obj;
    u16 temp;
    s32 i;
    s32 j;

    if (object->work[0] == 0) {
        for (i = 0; i < 4; i++) {
            player = m223_planeObjTbl[i]->data;
            espDispOff(player->unk_1C);
            espDispOff(player->unk_1E);
        }
        espDispOff(m223_radarSpr);
        object->func = NULL;
        return;
    }
    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            if (m223_planeObjTbl[order[i]]->trans.y < m223_planeObjTbl[order[j]]->trans.y) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        obj = m223_planeObjTbl[order[i]];
        player = obj->data;
        x = obj->trans.x * 0.005063291f + 160.0f;
        y = obj->trans.z * 0.005063291f + 120.0f;
        espPosSet(player->unk_1C, x, y);
        scale = 1.0f + obj->trans.y / 500.0f * 0.25f;
        espScaleSet(player->unk_1C, scale, scale);
        espPriSet(player->unk_1C, (u16)(i + 0x8005));
        espZRotSet(player->unk_1C, obj->rot.y);
        espTPLvlSet(player->unk_1C, 0xC0);
        if (player->unk_6C != NULL) {
            x = player->unk_6C->trans.x * 0.005063291f + 160.0f;
            y = player->unk_6C->trans.z * 0.005063291f + 120.0f;
            espPosSet(player->unk_1E, x, y);
            scale = 1.0f + player->unk_6C->trans.y / 500.0f * 0.25f;
            scale *= 0.5f;
            espScaleSet(player->unk_1E, scale, scale);
            espZRotSet(player->unk_1E, player->unk_6C->rot.y);
            espDispOn(player->unk_1E);
        } else {
            espDispOff(player->unk_1E);
        }
    }
}

void m223_IntroObjMain(omObjData *object) {
    switch (m223_introPhase) {
        case 0:
            WipeCreateIn(0xFF, 16);
            m223_introPhase = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                m223_introPhase = 2;
                m223_engineSe = HuAudFXPlay(0x3AC);
                HuAudFXPlay(0x3B3);
            }
            break;
        case 2:
            if (MgFlowStatGet() == MG_STATE_START) {
                omDelObj(object);
                m223_introObj = NULL;
            }
            break;
    }
}

void m223_FinishObjMain(omObjData *object) {
    switch (m223_finishPhase) {
        case 0:
            if (m223_finishF == 0) {
                m223_finishF = 1;
                m223_radarObj->work[0] = 0;
                m223_ShotKillAll();
                m223_LifeSprOffAll();
                HuAudFXStop(m223_engineSe);
            }
            m223_SurvivorCheck();
            if (m223_resultF != 0) {
                if (m223_finishWait != 0) {
                    m223_finishWait--;
                } else if (m223_winner != -1) {
                    m223_finishPhase = 2;
                    m223_CameraWinStart(m223_planeObjTbl[m223_winner]);
                    HuAudFXPlay(0x3B4);
                } else {
                    MgFlowStatSet(MG_STATE_RESULT);
                    m223_mgFlow.resultType = MG_RESULT_DRAW;
                    m223_finishPhase = 1;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (m223_WinViewExpand(m223_winner) == 1) {
                MgFlowStatSet(MG_STATE_RESULT);
                m223_finishPhase = 3;
                m223_mgFlow.winners[0] = m223_winner;
                GwPlayer[m223_winner].bonusCoin = 10;
                PlayerFXPlay(0x28F, m223_winner);
            }
            break;
    }
}

void m223_SurvivorCheck(void) {
    s32 count = 0;
    u16 numAlive = 0;
    s16 maxLives = 0;
    u16 alive[4];
    AceHighPlayer *player;
    s32 i;
    omObjData *obj;

    if (m223_resultF == 1) {
        return;
    }
    m223_resultF = 0;
    for (i = 0; i < 4; i++) {
        obj = m223_planeObjTbl[i];
        player = obj->data;
        count++;
        if (player->unk_00 == 4 || player->unk_00 == 5) {
            continue;
        }
        if (player->unk_00 == 6) {
            continue;
        }
        alive[numAlive++] = i;
    }
    if (count != 4) {
        return;
    }
    m223_resultF = 1;
    m223_winner = -1;
    for (i = 0; i < numAlive; i++) {
        player = m223_planeObjTbl[alive[i]]->data;
        if (player->unk_26 > maxLives) {
            maxLives = player->unk_26;
        }
    }
    for (i = 0; i < numAlive; i++) {
        player = m223_planeObjTbl[alive[i]]->data;
        if (player->unk_26 != maxLives) {
            continue;
        }
        if (m223_winner != -1) {
            m223_winner = -1;
            return;
        }
        m223_winner = alive[i];
    }
    if (numAlive != 0 && m223_winner != -1) {
        obj = m223_planeObjTbl[m223_winner];
        player = obj->data;
        player->unk_92 = 5;
        player->unk_9C.x = 0.0f;
        player->unk_9C.y = 0.0f;
        player->unk_9C.z = 0.0f;
    }
}

// NON_MATCHING: only register allocation differs. Target keeps the scissor
// walking pointer in s0 and the viewport pointer in s1 (4 saved regs, 0x50
// frame); here one `rect` variable gets s1 for both (s0 is taken by the local
// `winner` zero-extension pseudo that overlaps the viewport part). Using separate
// scissor and viewport variables gets the scissor part in s0, but the viewport
// pointer is then a block-local, non-call-crossing pseudo that local-alloc ties
// to the shift temp (a0, 3 saved regs). To land in s1 it must be a global
// pseudo that crosses a call, yet the target shows no other use of s1 there.
// Writing [1][0]/[3][0] through the global array (instead of rect[0]) is needed
// so the reads after the stores reload from memory. Also tried: per-section
// `rect = m223_scissorTbl[i]`, all-global indexing, a Vec2f pointer for the
// target position, deriving the viewport pointer from rect, do-while(0) around
// the scissor or viewport part, s32 x/y/w/h, declaration order.
// -O1 has no insn scheduling, so the target's viewport pointer is computed
// after ScissorSet(3) and dead before ViewportSet, i.e. it crosses no call in
// RTL; local- and global-alloc both give such pseudos a caller-saved register,
// so s1 is unexplained. Also tried: do-while(0) around each candidate
// statement (no effect); `view = m223_viewportTbl[0]` before ScissorSet(3)
// then `view += winner * 4` (gets s1, but the la stays before the call).
#ifdef NON_MATCHING
u16 m223_WinViewExpand(u16 winner) {
    f32 angle;
    f32 moveX;
    f32 moveY;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    f32 *rect;

    angle = atan2df(m223_viewCornerTbl[winner].x - m223_viewCenter.x,
                    m223_viewCornerTbl[winner].y - m223_viewCenter.y);
    moveX = sindf(angle) * 2.5f;
    moveY = cosdf(angle) * 2.5f;
    m223_viewCenter.x += moveX;
    m223_viewCenter.y += moveY;
    if (moveX < 0.0f) {
        if (m223_viewCenter.x < m223_viewCornerTbl[winner].x) {
            m223_viewCenter.x = m223_viewCornerTbl[winner].x;
        }
    } else if (m223_viewCenter.x > m223_viewCornerTbl[winner].x) {
        m223_viewCenter.x = m223_viewCornerTbl[winner].x;
    }
    if (moveY < 0.0f) {
        if (m223_viewCenter.y < m223_viewCornerTbl[winner].y) {
            m223_viewCenter.y = m223_viewCornerTbl[winner].y;
        }
    } else if (m223_viewCenter.y > m223_viewCornerTbl[winner].y) {
        m223_viewCenter.y = m223_viewCornerTbl[winner].y;
    }
    rect = m223_scissorTbl[0];
    rect[2] = m223_viewCenter.x - 1.0f;
    rect[3] = m223_viewCenter.y - 1.0f;
    ScissorSet(0, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    m223_scissorTbl[1][0] = m223_viewCenter.x + 1.0f;
    rect[3] = m223_viewCenter.y - 1.0f;
    ScissorSet(1, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    rect[2] = m223_viewCenter.x - 1.0f;
    rect[1] = m223_viewCenter.y + 1.0f;
    ScissorSet(2, rect[0], rect[1], rect[2], rect[3]);
    rect += 4;
    m223_scissorTbl[3][0] = m223_viewCenter.x + 1.0f;
    rect[1] = m223_viewCenter.y + 1.0f;
    ScissorSet(3, rect[0], rect[1], rect[2], rect[3]);
    rect = m223_viewportTbl[winner];
    x = rect[0] + fabs(m223_viewCenter.x - 160.0f) * 320.0 / 158.0;
    y = rect[1] + fabs(m223_viewCenter.y - 120.0f) * 240.0 / 118.0;
    w = (m223_viewCenter.x - 160.0f) * 320.0f / 158.0f + rect[2];
    h = (m223_viewCenter.y - 120.0f) * 240.0f / 158.0f + rect[3];
    ViewportSet(winner, x, y, 511.0f, w, h, 511.0f);
    espPosSet(m223_viewLineHSpr, 160, m223_viewCenter.y);
    espPosSet(m223_viewLineVSpr, m223_viewCenter.x, 120);
    return m223_viewCenter.x == m223_viewCornerTbl[winner].x &&
           m223_viewCenter.y == m223_viewCornerTbl[winner].y;
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/minigames/17_aces_high/main", m223_WinViewExpand);
#endif

void m223_WarnObjMain(omObjData *object) {
    omObjData *playerObj = (omObjData *)object->work[3];
    AceHighPlayer *player = playerObj->data;
    Vec pos;
    Vec2f screen;
    f32 scale;
    f32 minX;
    f32 maxX;
    f32 minY;
    f32 maxY;

    if (object->work[2] == 0) {
        espDispOff(player->unk_2E);
        if (player->unk_2C != -1) {
            HuAudFXStop(player->unk_2C);
            player->unk_2C = -1;
        }
    } else if (object->work[0] != 0 && player->unk_70 != 0) {
        object->work[0]--;
        if (object->work[1] != 0) {
            scale = 1.2f;
            object->scale.y = 0.0f;
            object->work[1]--;
        } else {
            scale = 1.0f - sindf(object->scale.y) * 0.25f;
            object->scale.y += 30.0f;
            if (object->scale.y >= 360.0f) {
                object->scale.y -= 360.0f;
            }
        }
        pos.x = playerObj->trans.x;
        pos.y = playerObj->trans.y + 160.0f + playerObj->trans.y / 25.0f;
        pos.z = playerObj->trans.z;
        Hu3DCam3Dto2D(player->camIdx, &pos, &screen);
        minX = minY = 15.400001f;
        maxX = 144.6f;
        maxY = 104.6f;
        if (player->camIdx & 1) {
            minX = 175.4f;
            maxX = 304.6f;
        }
        if (player->camIdx >= 2) {
            minY += 120.0f;
            maxY += 120.0f;
        }
        if (screen.x < minX) {
            screen.x = minX;
        }
        if (screen.x > maxX) {
            screen.x = maxX;
        }
        if (screen.y < minY) {
            screen.y = minY;
        }
        if (screen.y > maxY) {
            screen.y = maxY;
        }
        espPosSet(player->unk_2E, screen.x, screen.y);
        espScaleSet(player->unk_2E, scale, scale);
        espDispOn(player->unk_2E);
        if (player->unk_2C == -1) {
            player->unk_2C = HuAudPlayerFXPlay(0x3B1, player->camIdx);
        }
    } else {
        object->work[2] = 0;
    }
}

void m223_LockObjMain(omObjData *object) {
    AceHighPlayer *player = ((omObjData *)object->work[0])->data;

    if (object->work[1] == 0) {
        espDispOff(player->unk_30);
        return;
    }
    switch (object->work[1]) {
        case 1:
            if (object->scale.x < 1.0f) {
                object->scale.x += 0.2f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
            } else {
                object->scale.x = 1.0f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
                object->work[1] = 2;
            }
        case 2:
            if (player->unk_70 == 0) {
                object->work[1] = 3;
            }
            break;
        case 3:
            if (object->scale.x > 0.0f) {
                object->scale.x -= 0.200001f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
            } else {
                object->scale.x = 0.0f;
                espScaleSet(player->unk_30, object->scale.x, object->scale.x);
                object->work[1] = 0;
            }
            break;
    }
    espDispOn(player->unk_30);
}
