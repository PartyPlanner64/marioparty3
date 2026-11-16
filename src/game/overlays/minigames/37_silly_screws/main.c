#include "silly_screws.h"
#include "game/overlays/minigame.h"
#include "gcc/memory.h"
#include "game/audio.h"
#include "game/camera.h"
#include "game/gamemes.h"
#include "game/gamework_data.h"
#include "game/hmflight.h"
#include "game/hu3d.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/wipe.h"
#include "game/mallocblock.h"
#include "include_asm.h"
#include "game/hmfcoll.h"
#include "game/camsetup.h"
#include "game/hmfspr.h"
#include "game/printfunc.h"

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define FPS 30.0f

#define PLAYERS_TOTAL 2
#define SIGNS_TOTAL 2
#define SCREWS_TOTAL 6
#define NUTS_TOTAL 6

#define GOAL_POS_X 200.0f
#define JUMP_RANGE_X 25.0f

// camsetup

// hmfspr

// hmfcoll

// 8FB20

// pad
extern u16 HuPadBtn[];
extern u16 HuPadBtnDown[];

// printfunc

// unknown
extern s32 omCharModelNoTbl[][6];
extern char omDBGStrBuf[];
extern u16 omSysExitReq;

// LOCAL

enum {
    FGRP_CAMERA,
    FGRP_MINIGAME,
    FGRP_NUTS_1,
    FGRP_NUTS_2,
    FGRP_PLAYER_1,
    FGRP_PLAYER_2
};

enum {
    MDL_ARROW = 9,
    MDL_BALLOON_B,
    MDL_BALLOON_A
};

enum {
    CUE_ARROW,
    CUE_BALLOON_B,
    CUE_BALLOON_A
};

typedef struct {
    /* 0x00 */ s16 modelId;
    /* 0x04 */ f32 startPosX;
} NutData; // Size 8

typedef struct {
    /* 0x00 */ s16 wallCount;
    /* 0x02 */ s16 screwCount;
    /* 0x04 */ NutData *nuts;
    /* 0x08 */ char unk08[4];
} PlayerWorld; // Size 0xC

typedef struct {
    /* 0x00 */ PlayerWorld *worlds;
    /* 0x04 */ s8 unk04;
    /* 0x08 */ f32 timer; // counted in frames
    /* 0x0C */ Work work;
} MinigameData; // Size 0x3C

#define PLAYER_STATE_ON_PLATFORM 0
#define PLAYER_STATE_1 1
#define PLAYER_STATE_ROTATE 2
#define PLAYER_STATE_TRANSITION 3
#define PLAYER_STATE_JUMP 4
#define PLAYER_STATE_FINISHED 5
#define PLAYER_STATE_WON 6
#define PLAYER_STATE_7 7
#define PLAYER_STATE_WAIT_CAM 8

#define PLAYER_ANIM_IDLE 0
#define PLAYER_ANIM_WALK 1
#define PLAYER_ANIM_RUN 2
#define PLAYER_ANIM_JUMP 6
#define PLAYER_ANIM_WON 13
#define PLAYER_ANIM_LOST 14
#define PLAYER_ANIM_32 32

enum {
    PLAYER_DIR_RIGHT,
    PLAYER_DIR_LEFT
};

typedef struct {
    /* 0x00 */ omObjData *object;
    /* 0x04 */ s16 padId;
    /* 0x08 */ f32 startPosX;
    /* 0x0C */ s16 state;
    /* 0x0E */ s16 direction;
    /* 0x10 */ s8 unk10;
    /* 0x11 */ s8 inputIdleTimer;
    /* 0x12 */ s8 inputEnabled;
    /* 0x13 */ s8 cuesEnabled;
    /* 0x14 */ s8 finished;
    /* 0x15 */ s8 lost;
    /* 0x18 */ f32 speed;
    /* 0x1C */ s8 currNutId;
    /* 0x20 */ f32 accelY;
    /* 0x24 */ s16 nutSeNo;
    /* 0x26 */ s8 nutSeActive;
    /* 0x28 */ Work work;
} PlayerData; // Size 0x58

void m255_ObjectSetup(void);
void m255_WorkCreate(void);
void m255_ExitCheckObjMain(omObjData *object);
void m255_ExitWaitObjMain(omObjData *object);
void m255_ExitObjMain(omObjData *object);
void m255_MainObjInit(omObjData *object);
void m255_MainObjMain(omObjData *object);
void m255_WallObjInit(omObjData *object);
void m255_WallObjMain(omObjData *object);
void m255_SignObjInit(omObjData *object);
void m255_SignObjMain(omObjData *object);
void m255_ScrewObjInit(omObjData *object);
void m255_ScrewObjMain(omObjData *object);
void m255_NutObjInit(omObjData *object);
void m255_NutObjMain(omObjData *object);
void m255_PlayerObjInit(omObjData *object);
void m255_PlayerObjMain(omObjData *object);
void m255_CameraViewInit(FuncContext *ctx);
void m255_CameraFollowUpdate(FuncContext *ctx);
void m255_StartExec(FuncContext *ctx);
void m255_DrawExec(FuncContext *ctx);
void m255_GoalCheckUpdate(FuncContext *ctx);
void m255_NutPosInit(void);
void m255_WallPosSet(s16 modelId, s16 worldId);
void m255_ScrewPosSet(s16 modelId, s16 worldId);
void m255_NutSpinUpdate(FuncContext *ctx);
void m255_PlayerCueUpdate(FuncContext *ctx);
void m255_PlayerWinExec(FuncContext *ctx);
void m255_PlayerSpeedUpdate(FuncContext *ctx);
void m255_PlayerMotUpdate(FuncContext *ctx);
void m255_PlayerRotLerpUpdate(FuncContext *ctx);
void m255_PlayerJumpExec(FuncContext *ctx);
void m255_PlayerComInput(FuncContext *ctx);
f32 m255_StopDistCalc(PlayerData *player);

const s16 m255_startMesTbl[] = {
    0x8272, 0x8273, 0x8260, 0x8271, 0x8273, 0x0000
};

const s16 m255_finishMesTbl[] = {
    0x8265, 0x8268, 0x826D, 0x8268, 0x8272, 0x8267, 0x0000, 0x0000
};

const s16 m255_drawMesTbl[] = {
    0x8263, 0x8271, 0x8260, 0x8276, 0x0000, 0x0000
};

static MinigameData *m255_gameWork;
static PlayerData *m255_playerTbl;
static s16 m255_playerNoTbl[PLAYERS_TOTAL];

s16 m255_finishPhase = -1;
s16 m255_timeUpF = 0;
s16 m255_endF = 0;
s16 m255_startF = 0;
s16 m255_musicTimer = 0;

s32 m255_winAnimTbl[] = {
    0x000200A5, 0x000300A5, 0x000700A5, 0x000400A5, 0x000500A5, 0x000600A5, 0x000800A5, 0x0009001C
};

s16 m255_winReadyF = 0;
s16 m255_winVoiceF = 0;

void m255_Executor(void) {
    m255_ObjectSetup();
}

void m255_ObjectSetup(void) {
    omObjData *temp_v0;

    MapCollInit(50);
    Hu3DSprModelInit(0x20);
    omInitObjMan(50, 0);
    omGameSysInit();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    temp_v0->work[0] = 2;
    omSetStatBit(temp_v0, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    CamSetupInit(2);
    CamSetupMapCullAddMulti(2);
    ScissorSet(0, 0.0f, 0.0f, 159.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 60.0f, 80.0f, 4000.0f);
    ScissorSet(1, 161.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(1, 60.0f, 80.0f, 4000.0f);
    mgItemObjNum = 0;
    mgPlayerObjNum = 0;
    mgMapObjNum = 0;
    m255_SystemCreate();
    m255_WorkCreate();
    m255_FuncSet(FGRP_CAMERA, 0, -1, 0, m255_CameraViewInit, FALSE, FALSE);
    omAddObj(100, 0, 0, -1, m255_MainObjInit);
    omAddObj(1000, 0, 0, -1, m255_ExitCheckObjMain);
    GMesFontMesCreate(m255_startMesTbl, 1);
    GMesFontMesCreate(m255_finishMesTbl, 1);
    GMesFontMesCreate(m255_drawMesTbl, 1);
}

void m255_WorkCreate(void) {
    s16 i;

    m255_gameWork = HuMemAllocTag(sizeof(MinigameData), TAG_OVERLAY);
    memset(m255_gameWork, 0, sizeof(MinigameData));
    m255_gameWork->worlds = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerWorld), TAG_OVERLAY);
    memset(m255_gameWork->worlds, 0, PLAYERS_TOTAL * sizeof(PlayerWorld));
    for (i = 0; i < PLAYERS_TOTAL; i++) {
        m255_gameWork->worlds[i].nuts = HuMemAllocTag(NUTS_TOTAL * sizeof(NutData), TAG_OVERLAY);
        memset(m255_gameWork->worlds[i].nuts, 0, NUTS_TOTAL * sizeof(NutData));
    }
    m255_playerTbl = HuMemAllocTag(PLAYERS_TOTAL * sizeof(PlayerData), TAG_OVERLAY);
    memset(m255_playerTbl, 0, PLAYERS_TOTAL * sizeof(PlayerData));
    m255_NutPosInit();
}

void m255_ExitCheckObjMain(omObjData *object) {
    if (omSysExitReq == 1) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
        object->func = m255_ExitWaitObjMain;
    }
}

void m255_ExitWaitObjMain(omObjData *object) {
    if (WipeStatGet() == 0) {
        object->func = m255_ExitObjMain;
    }
}

void m255_ExitObjMain(omObjData *object) {
    osViBlack(0);
    omOvlReturnEx(1);
}

void m255_CameraUpdate(void) {
    s16 i;

    for (i = 0; i < PLAYERS_TOTAL; i++) {
        if (CRotM[i].x > 360.0f) {
            CRotM[i].x -= 360.0f;
        } else if (CRotM[i].x < 0.0f) {
            CRotM[i].x += 360.0f;
        }
        if (CRotM[i].y > 360.0f) {
            CRotM[i].y -= 360.0f;
        } else if (CRotM[i].y < 0.0f) {
            CRotM[i].y += 360.0f;
        }
    }
    m255_FuncGroupUpdate(FGRP_CAMERA);
}

void m255_MainObjInit(omObjData *object) {
    s16 player1Set = FALSE;
    s16 player2Set = FALSE;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (GwPlayer[i].group == 0) {
            if (!player1Set) {
                m255_playerNoTbl[0] = i;
                player1Set = TRUE;
            }
        } else if (GwPlayer[i].group == 1) {
            if (!player2Set) {
                m255_playerNoTbl[1] = i;
                player2Set = TRUE;
            }
        }
    }
    MgPlayerParamReset();
    MgShadowAltSet(1);
    for (i = 0; i < PLAYERS_TOTAL; i++) {
        omAddObj(10, 8, 0, -1, m255_WallObjInit);
        omAddObj(10, 2, 0, -1, m255_SignObjInit);
        omAddObj(10, 7, 0, -1, m255_ScrewObjInit);
        omAddObj(10, 6, 0, -1, m255_NutObjInit);
        mgPlayerObjTbl[i] = omAddObj(300, 12, 38, -1, m255_PlayerObjInit);
    }
    m255_SprDispOn(m255_SprCreate(0x58, 0xF, 0, 0), 160, 120);
    m255_FuncSet(FGRP_MINIGAME, 1, -1, 0, m255_StartExec, TRUE, FALSE);
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
    object->func = m255_MainObjMain;
}

void m255_MainObjMain(omObjData *object) {
    m255_FuncGroupUpdate(FGRP_MINIGAME);
    m255_CameraUpdate();
    m255_SprUpdate();
}

void m255_WallObjInit(omObjData *object) {
    s16 var_a1;
    s16 i;

    object->work[0] = m255_gameWork->work.s8[0];
    object->model[0] = Hu3DModelRead(0x580000, 0x9D); // checkered flat wall segment
    for (i = 1; i < 5; i++) {
        if (i == 4) {
            object->model[i] = Hu3DModelRead(0x580001, 0x9D); // ending platform + wall
        } else {
            object->model[i] = Hu3DModelLink(object->model[0]);
        }
    }
    for (i = 5; i < 8; i++) {
        if (i == 5) {
            object->model[i] = Hu3DModelRead(0x580009, 0x9D); // wall pipes
        } else {
            object->model[i] = Hu3DModelLink(object->model[5]);
        }
        Hu3DModelPosSet(object->model[i], 0.0f, 0.0f, -(200.0f + (i - 5) * 900.0f));
    }
    for (i = 0; i < 4; i++) {
        m255_WallPosSet(object->model[i], object->work[0]);
    }
    Hu3DModelPosSet(object->model[4], 0.0f, 0.0f, -2050.0f);
    m255_MdlSync(object);
    var_a1 = (object->work[0] == 0) ? 1 : 2;
    for (i = 0; i < 8; i++) {
        Hu3DModelCameraSet(object->model[i], var_a1);
    }
    m255_gameWork->work.s8[0]++;
    object->func = m255_WallObjMain;
}

void m255_WallObjMain(omObjData *object) {
    s16 i;

    if (m255_gameWork->unk04 != 0) {
        for (i = 0; i < 8; i++) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < 8; i++) {
        HmfModel *model = &Hu3DData[object->model[i]];

        if (i < 5) {
            if (CenterM[object->work[0]].z - 1050.0f < model->pos.z) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (CenterM[object->work[0]].z + 1600.0f < model->pos.z) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (i != 4) {
                    m255_WallPosSet(object->model[i], object->work[0]);
                }
            }
        } else {
            if (CenterM[object->work[0]].z - 1500.0f < model->pos.z) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            }
            if (CenterM[object->work[0]].z + 1700.0f < model->pos.z) {
                Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
    m255_MdlSync(object);
}

void m255_SignObjInit(omObjData *object) {
    s16 var_a1;
    s16 i;

    object->work[0] = m255_gameWork->work.s8[3];
    object->model[0] = Hu3DModelRead(0x58000C, 0x9D);
    for (i = 1; i < SIGNS_TOTAL; i++) {
        object->model[i] = Hu3DModelLink(object->model[0]);
    }
    for (i = 0; i < SIGNS_TOTAL; i++) {
        Hu3DModelPosSet(object->model[i], 0.0f, 1300.0f, -(675.0f + i * 900.0f));
    }
    m255_MdlSync(object);
    var_a1 = (object->work[0] == 0) ? 1 : 2;
    for (i = 0; i < SIGNS_TOTAL; i++) {
        Hu3DModelCameraSet(object->model[i], var_a1);
    }
    m255_gameWork->work.s8[3]++;
    object->func = m255_SignObjMain;
}

void m255_SignObjMain(omObjData *object) {
    s16 i;

    for (i = 0; i < SIGNS_TOTAL; i++) {
        HmfModel *model = &Hu3DData[object->model[i]];

        if (CenterM[object->work[0]].z - 1050.0f < model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (CenterM[object->work[0]].z + 1600.0f < model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 4) {
                m255_WallPosSet(object->model[i], object->work[0]);
            }
        }
    }
    m255_MdlSync(object);
}

void m255_ScrewObjInit(omObjData *object) {
    s16 var_a1;
    s16 i;

    object->work[0] = m255_gameWork->work.s8[2];
    object->model[0] = Hu3DModelRead(0x580002, 0x9D);
    for (i = 1; i < SCREWS_TOTAL + 1; i++) {
        if (i == 6) {
            object->model[i] = Hu3DModelRead(0x58000A, 0x9D);
        } else {
            object->model[i] = Hu3DModelLink(object->model[0]);
        }
    }
    for (i = 0; i < SCREWS_TOTAL; i++) {
        m255_ScrewPosSet(object->model[i], object->work[0]);
    }
    Hu3DModelPosSet(object->model[6], 0.0f, 1800.0f, -2650.0f);
    m255_MdlSync(object);
    var_a1 = (object->work[0] == 0) ? 1 : 2;
    for (i = 0; i < SCREWS_TOTAL + 1; i++) {
        Hu3DModelCameraSet(object->model[i], var_a1);
    }
    m255_gameWork->work.s8[2]++;
    object->func = m255_ScrewObjMain;
}

void m255_ScrewObjMain(omObjData *object) {
    s16 i;

    for (i = 0; i < SCREWS_TOTAL; i++) {
        HmfModel *model = &Hu3DData[object->model[i]];

        if (CenterM[object->work[0]].z - 800.0f < model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        if (CenterM[object->work[0]].z + 800.0f < model->pos.z) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (i != 6) {
                m255_ScrewPosSet(object->model[i], object->work[0]);
            }
        }
    }
    m255_MdlSync(object);
}

void m255_NutObjInit(omObjData *object) {
    PlayerWorld *world = &m255_gameWork->worlds[m255_gameWork->work.s8[1]];
    s32 file[] = { 3, 4, 5, 6, 7, 8 };
    s16 var_s4;
    s16 i;

    object->work[0] = m255_gameWork->work.s8[1];
    var_s4 = (object->work[0] == 0) ? 1 : 2;
    for (i = 0; i < NUTS_TOTAL; i++) {
        object->model[i] = world->nuts[i].modelId = Hu3DModelRead(0x580000 | file[i], 0x9D);
        Hu3DModelPosSet(object->model[i], m255_gameWork->worlds[object->work[0]].nuts[i].startPosX, 1800.0f, 0.0f - i * 450.0f);
        Hu3DModelCameraSet(object->model[i], var_s4);
    }
    m255_MdlSync(object);
    m255_gameWork->work.s8[1]++;
    m255_FuncSet(FGRP_NUTS_1 + object->work[0], 0, object->work[0], &m255_gameWork->worlds[object->work[0]], m255_NutSpinUpdate, FALSE, FALSE);
    object->func = m255_NutObjMain;
}

void m255_NutObjMain(omObjData *object) {
    s16 i;

    if (m255_gameWork->unk04 != 0) {
        for (i = 0; i < NUTS_TOTAL; i++) {
            Hu3DModelAttrSet(object->model[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        }
    }
    m255_FuncGroupUpdate(FGRP_NUTS_1 + object->work[0]);
    m255_MdlSync(object);
}

void m255_PlayerObjInit(omObjData *object) {
    s8 *unkData;
    s32 temp_v0_2;
    s32 temp_a1;
    s16 var_a1;
    s16 chr;
    s16 i;

    object->work[0] = mgPlayerObjNum;
    object->work[1] = m255_playerNoTbl[object->work[0]];
    chr = GwPlayer[object->work[1]].chr;
    temp_a1 = omCharModelNoTbl[GwPlayer[object->work[1]].chr][0];
    temp_v0_2 = omCharModelNoTbl[GwPlayer[object->work[1]].chr][2];
    MgPlayerCreate(object, temp_a1, temp_v0_2, object->work[1], 0x2A9, 0x2B9);
    object->model[MDL_ARROW] = Hu3DModelRead(0x58000B, 0x2B9);
    object->model[MDL_BALLOON_B] = Hu3DModelRead(0x58000D, 0x2B9);
    object->model[MDL_BALLOON_A] = Hu3DModelRead(0x58000E, 0x2B9);
    Hu3DModelScaleSet(object->model[MDL_ARROW], 1.25f, 1.25f, 1.25f);
    Hu3DModelScaleSet(object->model[MDL_BALLOON_B], 1.25f, 1.25f, 1.25f);
    Hu3DModelScaleSet(object->model[MDL_BALLOON_A], 1.25f, 1.25f, 1.25f);
    Hu3DModelAttrSet(object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    MgPlayerMotLoad(object, PLAYER_ANIM_IDLE, CharMotionDataNumGet(chr, 0), 1, 0);
    MgPlayerMotLoad(object, PLAYER_ANIM_WALK, CharMotionDataNumGet(chr, 1), 1, 0);
    MgPlayerMotLoad(object, PLAYER_ANIM_RUN, CharMotionDataNumGet(chr, 2), 1, 0);
    MgPlayerMotLoad(object, PLAYER_ANIM_JUMP, CharMotionDataNumGet(chr, 4), 1, 19);
    MgPlayerMotLoad(object, PLAYER_ANIM_32, CharMotionDataNumGet(chr, 0x22), 0, 0);
    MgPlayerMotLoad(object, PLAYER_ANIM_LOST, CharMotionDataNumGet(chr, 0x36), 1, 999);
    MgPlayerMotLoad(object, PLAYER_ANIM_WON, CharMotionDataNumGet(chr, 0x2F), 1, 999);
    object->trans.x = m255_playerTbl[object->work[0]].startPosX;
    object->trans.y = 2000.0f;
    object->trans.z = 0.0f;
    object->rot.y = 180.0f;
    MgPlayerMotSet(object, PLAYER_ANIM_IDLE);
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelAttrSet(object->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    mgPlayerObjNum++;
    unkData = object->data;
    m255_playerTbl[object->work[0]].padId = unkData[0x57]; // TODO: figure out type.
    m255_playerTbl[object->work[0]].object = object;
    m255_playerTbl[object->work[0]].direction = PLAYER_DIR_RIGHT;
    m255_playerTbl[object->work[0]].currNutId = 0;
    m255_playerTbl[object->work[0]].inputEnabled = TRUE;
    m255_playerTbl[object->work[0]].cuesEnabled = TRUE;
    m255_playerTbl[object->work[0]].nutSeActive = FALSE;
    var_a1 = (object->work[0] == 0) ? 1 : 2;
    for (i = 0; i < 12; i++) {
        Hu3DModelCameraSet(object->model[i], var_a1);
    }
    m255_FuncSet(FGRP_PLAYER_1 + object->work[0], 9, -1, &m255_playerTbl[object->work[0]], m255_PlayerMotUpdate, FALSE, FALSE);
    object->func = m255_PlayerObjMain;
}

void m255_PlayerObjMain(omObjData *object) {
    m255_FuncGroupUpdate(FGRP_PLAYER_1 + object->work[0]);
    MgPlayerMotUpdate(object);
}

void m255_CameraViewInit(FuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            for (i = 0; i < PLAYERS_TOTAL; i++) {
                CenterM[i].x = 372.0f;
                CenterM[i].y = 2019.0f;
                if (i == 0) {
                    CenterM[i].z = -2890.0f;
                } else {
                    CenterM[i].z = -2970.0f;
                }
                CRotM[i].x = 323.0f;
                CRotM[i].y = 77.0f;
                CRotM[i].z = 0.0f;
                CZoomM[i] = 1240.0f;
            }
            m255_FuncReset(FGRP_CAMERA, ctx);
            break;
    }
}

void m255_CameraStartMove(FuncContext *ctx) {
    s16 camId = ctx->param;
    f32 temp_f22;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            temp_f22 = ctx->work.s8[0] * 0.008333334f;
            temp_f22 = sindf(temp_f22 * 90.0f) * sindf(temp_f22 * 90.0f);
            CZoomM[camId] = temp_f22 * 0.0f + 1240.0f;
            CenterM[camId].x = temp_f22 * 0.0f + 372.0f;
            CenterM[camId].y = temp_f22 * 0.0f + 2019.0f;
            if (camId == 0) {
                CenterM[camId].z = temp_f22 * 2693.0f + -2890.0f;
            } else {
                CenterM[camId].z = temp_f22 * 2693.0f + -2970.0f;
            }
            CRotM[camId].x = temp_f22 * 0.0f + 323.0f;
            CRotM[camId].y = temp_f22 * 0.0f + 77.0f;
            ctx->work.s8[0]++;
            if (ctx->work.s8[0] > 120.0f) {
                CZoomM[camId] = 1240.0f;
                CenterM[camId].x = 372.0f;
                CenterM[camId].y = 2019.0f;
                if (camId == 0) {
                    CenterM[camId].z = -197.0f;
                } else {
                    CenterM[camId].z = -277.0f;
                }
                CRotM[camId].x = 323.0f;
                CRotM[camId].y = 77.0f;
                m255_FuncReset(FGRP_CAMERA, ctx);
                m255_gameWork->unk04 = 1;
                m255_FuncSet(FGRP_CAMERA, 0, camId, &m255_gameWork->worlds[camId], m255_CameraFollowUpdate, FALSE, FALSE);
            }
            break;
    }
}

void m255_CameraWinMove(FuncContext *ctx) {
    PlayerData *player = ctx->data;
    s16 camId = player->object->work[0];
    f32 temp_f0;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.f32[0] = CenterM[camId].z;
            ctx->work.f32[1] = player->object->trans.z - 70.0f;
            player->state = PLAYER_STATE_WAIT_CAM;
            ctx->state = 1;
            break;
        case 1:
            temp_f0 = ctx->work.s8[0] * 0.02f;
            temp_f0 = sindf(temp_f0 * 90.0f);
            CZoomM[camId] = temp_f0 * -1010.0f + 1240.0f;
            CenterM[camId].x = temp_f0 * -113.0f + 372.0f;
            CenterM[camId].y = temp_f0 * 5.0f + 2019.0f;
            if (camId == 0) {
                CenterM[camId].z = (ctx->work.f32[1] - ctx->work.f32[0]) * temp_f0 + ctx->work.f32[0];
            } else {
                CenterM[camId].z = (ctx->work.f32[1] - ctx->work.f32[0]) * temp_f0 + ctx->work.f32[0];
            }
            CRotM[camId].x = temp_f0 * 26.0f + 323.0f;
            CRotM[camId].y = temp_f0 * 50.0f + 77.0f;
            player->object->rot.y = temp_f0 * -53.0f + 180.0f;
            ctx->work.s8[0]++;
            if (ctx->work.s8[0] > 50.0f) {
                CZoomM[camId] = 230.0f;
                CenterM[camId].x = 259.0f;
                CenterM[camId].y = 2024.0f;
                if (camId == 0) {
                    CenterM[camId].z = ctx->work.f32[1];
                } else {
                    CenterM[camId].z = ctx->work.f32[1];
                }
                CRotM[camId].x = 349.0f;
                CRotM[camId].y = 127.0f;
                m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 3, -1, player, m255_PlayerWinExec, FALSE, FALSE);
                m255_FuncReset(FGRP_CAMERA, ctx);
            }
            break;
    }
}

void m255_CameraFollowUpdate(FuncContext *ctx) {
    PlayerData *player;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = ctx->param;
            ctx->state = 1;
            break;
        case 1:
            m255_gameWork->unk04 = 0;
            player = &m255_playerTbl[ctx->work.s8[0]];
            if (player->state == PLAYER_STATE_FINISHED || player->state == PLAYER_STATE_7 || player->state == PLAYER_STATE_WAIT_CAM) {
                m255_FuncReset(FGRP_CAMERA, ctx);
                break;
            }
            if (player->object->trans.z < CenterM[ctx->work.s8[0]].z + 197.0f) {
                CenterM[ctx->work.s8[0]].z = player->object->trans.z - 197.0f;
            }
            break;
    }
}

void m255_CameraDebugPad(FuncContext *ctx) {
    s16 camId = ctx->work.s8[3];
    u16 temp_a0;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 1;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s8[3] = 0;
            ctx->state = 1;
            break;
        case 1:
            if (ctx->work.s8[1] != 0) {
                if (ctx->work.s8[1] == 1) {
                    sprintf(omDBGStrBuf, "C: TRANSLATE ADD: %d", ctx->work.s8[0]);
                } else {
                    sprintf(omDBGStrBuf, "C: ROTATE");
                }
                print8(16, 56, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CZOOMM %.2f", CZoomM[camId]);
                print8(16, 64, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CCENTER_X %.2f Y %.2f Z %.2f", CenterM[camId].x, CenterM[camId].y, CenterM[camId].z);
                print8(16, 72, omDBGStrBuf);
                sprintf(omDBGStrBuf, "CROTATE_X %.2f Y %.2f Z %.2f", CRotM[camId].x, CRotM[camId].y, CRotM[camId].z);
                print8(16, 80, omDBGStrBuf);
            }
            temp_a0 = HuPadBtn[0];
            if (HuPadBtnDown[0] & Z_TRIG) {
                ctx->work.s8[1]++;
            }
            if (ctx->work.s8[1] >= 3) {
                ctx->work.s8[1] = 0;
            }
            if (HuPadBtnDown[0] & R_TRIG) {
                ctx->work.s8[3]++;
            }
            if (ctx->work.s8[3] >= 2) {
                ctx->work.s8[3] = 0;
            }
            if (ctx->work.s8[1] == 1) {
                if (temp_a0 & D_JPAD) {
                    CenterM[camId].z += ctx->work.s8[0];
                }
                if (temp_a0 & L_JPAD) {
                    CenterM[camId].x += ctx->work.s8[0];
                }
                if (temp_a0 & U_JPAD) {
                    CenterM[camId].z -= ctx->work.s8[0];
                }
                if (temp_a0 & R_JPAD) {
                    CenterM[camId].x -= ctx->work.s8[0];
                }
                if (temp_a0 & U_CBUTTONS) {
                    CenterM[camId].y += ctx->work.s8[0];
                }
                if (temp_a0 & D_CBUTTONS) {
                    CenterM[camId].y -= ctx->work.s8[0];
                }
                if (ctx->work.s8[2] == 15) {
                    ctx->work.s8[2] = 0;
                    if (temp_a0 & A_BUTTON) {
                        ctx->work.s8[0]++;
                    }
                    if (temp_a0 & B_BUTTON) {
                        ctx->work.s8[0]--;
                    }
                    if (ctx->work.s8[0] >= 125) {
                        ctx->work.s8[0] = 0;
                    }
                } else {
                    ctx->work.s8[2]++;
                }
            } else if (ctx->work.s8[1] == 2) {
                if (temp_a0 & D_JPAD) {
                    CRotM[camId].x += 1.0f;
                }
                if (temp_a0 & U_JPAD) {
                    CRotM[camId].x -= 1.0f;
                }
                if (temp_a0 & L_JPAD) {
                    CRotM[camId].y -= 1.0f;
                }
                if (temp_a0 & R_JPAD) {
                    CRotM[camId].y += 1.0f;
                }
                if (temp_a0 & U_CBUTTONS) {
                    CZoomM[camId] += 10.0f;
                }
                if (temp_a0 & D_CBUTTONS) {
                    CZoomM[camId] -= 10.0f;
                }
            }
            break;
    }
}

void m255_TimerUpdate(FuncContext *ctx) {
    s16 i;

    if (m255_endF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->state = 1;
            break;
        case 1:
            m255_gameWork->timer -= 1.0f;
            if (m255_gameWork->timer < 30.0f * FPS) {
                ctx->state = 3;
            }
            break;
        case 3:
            m255_gameWork->timer -= 1.0f;
            GMesCreate(GMES_MES_TIMER, m255_gameWork->timer / FPS, 160, 28);
            GMesTimerValueSet((m255_gameWork->timer + (FPS - 1.0f)) / FPS);
            ctx->state = 4;
            break;
        case 4:
            m255_gameWork->timer -= 1.0f;
            GMesTimerValueSet((m255_gameWork->timer + (FPS - 1.0f)) / FPS);
            if (m255_gameWork->timer < 0.0f) {
                m255_timeUpF = 1;
                GMesTimerEnd();
                m255_FuncReset(FGRP_MINIGAME, ctx);
                m255_FuncSet(FGRP_MINIGAME, 0, -1, NULL, m255_DrawExec, FALSE, FALSE);
                for (i = 0; i < PLAYERS_TOTAL; i++) {
                    m255_playerTbl[i].lost = TRUE;
                }
            }
            break;
    }
}

void m255_StartExec(FuncContext *ctx) {
    PlayerData *player = m255_playerTbl;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 5:
                    for (i = 0; i < PLAYERS_TOTAL; i++) {
                        m255_FuncSet(FGRP_CAMERA, 0, i, NULL, m255_CameraStartMove, FALSE, FALSE);
                    }
                    break;
                case 125:
                    GMesCreate(GMES_MES_MG_START);
                    HuAudFXPlay(0xE);
                    m255_musicTimer = 1;
                    break;
                case 140:
                    m255_startF = 1;
                    break;
                default:
                    if (m255_startF != 0 && GMesStatGet() == GMES_STAT_TIMEEND) {
                        for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
                            if (GwPlayer[m255_playerNoTbl[i]].stat & PLAYER_IS_CPU) {
                                m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 1, -1, player, m255_PlayerComInput, FALSE, FALSE);
                                m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 2, -1, player, m255_PlayerSpeedUpdate, FALSE, FALSE);
                            } else {
                                m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 2, -1, player, m255_PlayerSpeedUpdate, FALSE, FALSE);
                            }
                            m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 0, -1, player, m255_PlayerCueUpdate, FALSE, FALSE);
                        }
                        m255_FuncSet(FGRP_MINIGAME, 0, -1, NULL, m255_TimerUpdate, FALSE, FALSE);
                        m255_FuncSet(FGRP_MINIGAME, 1, -1, NULL, m255_GoalCheckUpdate, FALSE, FALSE);
                        m255_FuncReset(FGRP_MINIGAME, ctx);
                    }
                    break;
            }
    }
    if (m255_musicTimer != 0 && GMesStatGet() != GMES_STAT_NONE) {
        m255_musicTimer++;
        if (m255_musicTimer >= 45) {
            HuAudSeqPlay(0x38);
            m255_musicTimer = 0;
        }
    }
}

void m255_FinishExec(FuncContext *ctx) {
    s16 temp_v1;

    switch (ctx->state) {
        case 0:
            ctx->state = 1;
            break;
        case 1:
            temp_v1 = ctx->work.s16[0]++;
            if (temp_v1 == 3) {
                HuAudSeqFadeOut(120);
                GMesCreate(GMES_MES_MG_FINISH);
                ctx->work.s16[0] = 0;
                ctx->state = 10;
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
        case 10:
            if (m255_finishPhase == 0) {
                if (GMesStatGet() == GMES_STAT_NONE) {
                    ctx->work.s16[0] = 0;
                    m255_finishPhase = 1;
                }
            } else if (m255_finishPhase == 1) {
                ctx->work.s16[0]++;
                if (ctx->work.s16[0] >= 15) {
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    ctx->state = 2;
                }
            }
            break;
    }
}

void m255_DrawExec(FuncContext *ctx) {
    s16 i;

    switch (ctx->state) {
        case 0:
            for (i = 0; i < PLAYERS_TOTAL; i++) {
                m255_playerTbl[i].cuesEnabled = FALSE;
                Hu3DModelAttrSet(m255_playerTbl[i].object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[i].object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[i].object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            ctx->work.s16[0] = 0;
            ctx->state = 1;
            break;
        case 1:
            switch (ctx->work.s16[0]++) {
                case 0:
                    HuAudSeqFadeOut(120);
                    GMesCreate(GMES_MES_MG_FINISH);
                    ctx->state = 3;
                    break;
                case 15:
                    GMesCreate(GMES_MES_MG_DRAW);
                    HuAudSeqPlay(0x6C);
                    ctx->state = 3;
                    break;
                case 30:
                    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                    ctx->state = 2;
                    break;
            }
            break;
        case 2:
            if (WipeStatGet() == 0) {
                omOvlReturnEx(1);
            }
            break;
        case 3:
            if (GMesStatGet() == GMES_STAT_NONE) {
                ctx->state = 1;
            }
            break;
    }
}

void m255_GoalCheckUpdate(FuncContext *ctx) {
    PlayerData *player = m255_playerTbl;
    s16 winnerCount = 0;
    s16 winners[] = { -1, -1 };
    u8 unused_stack[8];
    s16 i;

    if (m255_timeUpF != 0) {
        return;
    }
    switch (ctx->state) {
        case 0:
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < PLAYERS_TOTAL; i++, player++) {
                if (player->finished) {
                    winners[winnerCount] = i;
                    winnerCount++;
                }
            }
            if (winnerCount == 0) {
                break;
            }
            m255_endF = 1;
            i = (winnerCount == PLAYERS_TOTAL) ? (rand16() & 1) : winners[0];
            if (i == 0) {
                m255_playerTbl[1].lost = TRUE;
                m255_playerTbl[1].cuesEnabled = FALSE;
                Hu3DModelAttrSet(m255_playerTbl[1].object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[1].object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[1].object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            } else {
                m255_playerTbl[0].lost = TRUE;
                m255_playerTbl[0].cuesEnabled = FALSE;
                Hu3DModelAttrSet(m255_playerTbl[0].object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[0].object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(m255_playerTbl[0].object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            GMesTimerEnd();
            m255_FuncSet(FGRP_MINIGAME, 1, i, &m255_playerTbl[i], m255_FinishExec, FALSE, FALSE);
            m255_FuncReset(FGRP_MINIGAME, ctx);
            break;
    }
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m255_NutPosInit(void) {
    PlayerWorld *world = m255_gameWork->worlds;
    f32 nutBasePosX[][6] = {
        {
            4.5f,
            6.5f,
            2.5f,
            4.5f,
            2.5f,
            5.0f,
        },
        { 4.5f, 2.5f, 6.5f, 2.5f, 4.5f, 6.5f }
    };
    s16 rand = rand16() & 1;
    s16 i, j;

    for (i = 0; i < PLAYERS_TOTAL; i++, world++) {
        for (j = 0; j < NUTS_TOTAL; j++) {
            world->nuts[j].startPosX = nutBasePosX[rand][j] * 20.0f * 5.0f;
        }
    }
    m255_playerTbl[0].startPosX = m255_playerTbl[1].startPosX = m255_gameWork->worlds->nuts[0].startPosX;
    m255_gameWork->timer = 180.0f * FPS;
}

void m255_WallPosSet(s16 modelId, s16 worldId) {
    if (m255_gameWork->worlds[worldId].wallCount < 4) {
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 1150.0f - m255_gameWork->worlds[worldId].wallCount * 800.0f);
        m255_gameWork->worlds[worldId].wallCount++;
    }
}

void m255_ScrewPosSet(s16 modelId, s16 worldId) {
    if (m255_gameWork->worlds[worldId].screwCount < SCREWS_TOTAL) {
        Hu3DModelPosSet(modelId, 50.0f, 1800.0f, 0.0f - m255_gameWork->worlds[worldId].screwCount * 450.0f);
        m255_gameWork->worlds[worldId].screwCount++;
    }
}

static inline void m255_NutMdlRotUpdate(HmfModel *model, PlayerData *player) {
    model->rot.x -= player->speed;
    if (model->rot.x > 360.0f) {
        model->rot.x -= 360.0f;
    } else if (model->rot.x < 0.0f) {
        model->rot.x += 360.0f;
    }
    model->pos.x -= player->speed * 0.22222222f;
    if (model->pos.x < 150.0f) {
        model->pos.x = 150.0f;
    } else if (model->pos.x > 700.0f) {
        model->pos.x = 700.0f;
    }
}

void m255_NutSpinUpdate(FuncContext *ctx) {
    PlayerWorld *world = ctx->data;
    NutData *nut = world->nuts;
    s16 i;

    switch (ctx->state) {
        case 0:
            ctx->work.s16[0] = ctx->param;
            ctx->state = 1;
            break;
        case 1:
            for (i = 0; i < NUTS_TOTAL; i++, nut++) {
                HmfModel *nutModel = &Hu3DData[nut->modelId];
                PlayerData *player = &m255_playerTbl[ctx->work.s16[0]];

                if (CenterM[ctx->work.s16[0]].z - 800.0f < nutModel->pos.z) {
                    Hu3DModelAttrSet(nut->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                }
                if (CenterM[ctx->work.s16[0]].z + 900.0f < nutModel->pos.z) {
                    Hu3DModelAttrSet(nut->modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                if (player->inputEnabled && player->currNutId == i) {
                    m255_NutMdlRotUpdate(nutModel, player);
                    player->object->trans.x = nutModel->pos.x;
                    Hu3DData[player->object->model[1]].pos.x = nutModel->pos.x;
                    Hu3DData[player->object->model[1]].pos.y = player->object->trans.y;
                    if (player->speed != 0.0f) {
                        continue;
                    }
                    if (i == NUTS_TOTAL - 1) {
                        s32 jumpGapX = nutModel->pos.x - GOAL_POS_X;

                        if (ABS(jumpGapX) < JUMP_RANGE_X) {
                            player->inputEnabled = FALSE;
                            player->currNutId++;
                            HuAudFXStop(player->nutSeNo);
                            player->nutSeActive = FALSE;
                            m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 3, -1, player, m255_PlayerJumpExec, FALSE, FALSE);
                        }
                    } else {
                        s32 jumpGapX = nutModel->pos.x - nut[1].startPosX;

                        if (ABS(jumpGapX) < JUMP_RANGE_X) {
                            player->inputEnabled = FALSE;
                            player->currNutId++;
                            HuAudFXStop(player->nutSeNo);
                            player->nutSeActive = FALSE;
                            m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 3, -1, player, m255_PlayerJumpExec, FALSE, FALSE);
                        }
                    }
                }
            }
            break;
    }
}

void m255_PlayerCueUpdate(FuncContext *ctx) {
    PlayerData *player = ctx->data;
    HmfModel *cueModel = NULL;
    PlayerWorld *world = &m255_gameWork->worlds[player->object->work[0]];
    f32 cuePosY = 0.0f;
    f32 cuePosZ = 0.0f;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[1] = CUE_ARROW;
            ctx->work.f32[0] = 0.0f;
            ctx->state = 1;
            break;
        case 1:
            if (!player->cuesEnabled) {
                break;
            }
            if (player->inputEnabled) {
                NutData *nut = &world->nuts[player->currNutId];
                f32 currNutPosX;
                f32 nextNutPosX;

                if (player->currNutId < NUTS_TOTAL - 1) {
                    currNutPosX = Hu3DData[nut->modelId].pos.x;
                    nextNutPosX = nut[1].startPosX;
                } else {
                    currNutPosX = Hu3DData[nut->modelId].pos.x;
                    nextNutPosX = GOAL_POS_X;
                }
                Hu3DModelAttrSet(player->object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(player->object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(player->object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (ABS((s32)(currNutPosX - nextNutPosX)) < JUMP_RANGE_X) {
                    ctx->work.s8[1] = ctx->work.s8[0];
                    ctx->work.s8[0] = CUE_ARROW;
                } else if (currNutPosX - nextNutPosX < 0.0f) {
                    ctx->work.s8[1] = ctx->work.s8[0];
                    ctx->work.s8[0] = CUE_BALLOON_A;
                } else if (currNutPosX - nextNutPosX > 0.0f) {
                    ctx->work.s8[1] = ctx->work.s8[0];
                    ctx->work.s8[0] = CUE_BALLOON_B;
                }
            } else {
                ctx->work.s8[1] = ctx->work.s8[0];
                ctx->work.s8[0] = CUE_ARROW;
            }
            if (ctx->work.s8[0] != ctx->work.s8[1]) {
                ctx->work.f32[0] = 0.0f;
            }
            switch (ctx->work.s8[0]) {
                case CUE_ARROW:
                    player->unk10 = 2;
                    ctx->work.f32[0] += 0.1f;
                    if (ctx->work.f32[0] > 1.0f) {
                        ctx->work.f32[0] = 0.0f;
                    }
                    cuePosY = player->object->trans.y + 100.0f;
                    cuePosZ = player->object->trans.z - 125.0f - sindf(ctx->work.f32[0] * 90.0f) * 20.0f * 5.0f * 0.5f;
                    cueModel = &Hu3DData[player->object->model[MDL_ARROW]];
                    Hu3DModelAttrSet(player->object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
                case CUE_BALLOON_B:
                    player->unk10 = 1;
                    ctx->work.f32[0] += 0.05f;
                    if (ctx->work.f32[0] > 1.0f) {
                        ctx->work.f32[0] = 0.0f;
                    }
                    cuePosY = player->object->trans.y + 300.0f - sindf(ctx->work.f32[0] * 90.0f) * 20.0f * 5.0f * 0.25f;
                    cuePosZ = player->object->trans.z;
                    cueModel = &Hu3DData[player->object->model[MDL_BALLOON_B]];
                    Hu3DModelAttrSet(player->object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
                case CUE_BALLOON_A:
                    player->unk10 = 0;
                    ctx->work.f32[0] += 0.05f;
                    if (ctx->work.f32[0] > 1.0f) {
                        ctx->work.f32[0] = 0.0f;
                    }
                    cuePosY = player->object->trans.y + 300.0f - sindf(ctx->work.f32[0] * 90.0f) * 20.0f * 5.0f * 0.25f;
                    cuePosZ = player->object->trans.z;
                    cueModel = &Hu3DData[player->object->model[MDL_BALLOON_A]];
                    Hu3DModelAttrSet(player->object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
            }
            cueModel->pos.x = player->object->trans.x;
            cueModel->pos.y = cuePosY;
            cueModel->pos.z = cuePosZ;
            cueModel->rot.y = 90.0f;
            break;
    }
}

void m255_PlayerWinExec(FuncContext *ctx) {
    PlayerData *player = ctx->data;

    if (GMesStatGet() == GMES_STAT_NONE) {
        m255_winReadyF = 1;
    }
    if (m255_winReadyF != 0) {
        s16 temp_15;

        switch (ctx->state) {
            case 0:
                ctx->state = 1;
                break;
            case 1:
                temp_15 = 15;
                if (ctx->work.s16[0]++ == temp_15) {
                    s16 chr = GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr;
                    s32 temp_a2 = m255_winAnimTbl[GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr];

                    CharAnimCreate(player->object->model[0], 2, chr, temp_a2);
                    player->state = PLAYER_STATE_WON;
                    HuAudSeqPlay(0x67);
                    GMesCreate(GMES_MES_MG_WINNER, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                    GwPlayer[m255_playerNoTbl[player->object->work[0]]].bonusCoin += 10;
                    m255_finishPhase = 0;
                }
                break;
        }
    }
}

void m255_PlayerSpeedUpdate(FuncContext *ctx) {
    PlayerData *player = ctx->data;
    f32 newSpeed;
    s16 absSpeed;
    s16 pitch;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            ctx->work.s8[2] = 0;
            ctx->work.s16[3] = 999;
            ctx->state = 1;
            break;
        case 1:
            if (!player->inputEnabled) {
                break;
            }
            if (player->lost) {
                player->state = PLAYER_STATE_ON_PLATFORM;
                m255_FuncReset(FGRP_PLAYER_1 + player->object->work[0], ctx);
                break;
            }
            if (player->state != PLAYER_STATE_ROTATE) {
                player->state = PLAYER_STATE_ON_PLATFORM;
            }
            if (HuPadBtn[player->padId] & B_BUTTON) {
                if (ctx->work.s8[0] == 0 && player->state != PLAYER_STATE_ROTATE) {
                    player->inputIdleTimer = 0;
                    if (player->direction == PLAYER_DIR_RIGHT) {
                        player->work.f32[0] = 180.0f;
                        player->work.f32[1] = 0.0f;
                        m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 5, -1, player, m255_PlayerRotLerpUpdate, FALSE, TRUE);
                    }
                    player->state = PLAYER_STATE_TRANSITION;
                    player->direction = PLAYER_DIR_LEFT;
                    ctx->work.s8[0] = 1;
                    if (player->speed + 1.0f > 15.0f) {
                        newSpeed = 15.0f;
                    } else {
                        newSpeed = player->speed + 1.0f;
                    }
                    player->speed = newSpeed;
                    if (!player->nutSeActive) {
                        player->nutSeNo = _HuAudPlayerFXPlay(0x4B3, m255_playerNoTbl[player->object->work[0]]);
                        player->nutSeActive = TRUE;
                    }
                    if (ABS(player->speed) < 5.0f) {
                        pitch = -50;
                    } else if (ABS(player->speed) < 10.0f) {
                        pitch = 0;
                    } else {
                        pitch = 50;
                    }
                    HuAudFXPitchSet(player->nutSeNo, pitch);
                    absSpeed = ABS(player->speed);
                    HuAudFXVolSet(player->nutSeNo, 100 + (s32)((absSpeed / 15.0f) * 27.0f));
                }
            } else if (HuPadBtn[player->padId] & A_BUTTON) {
                if (ctx->work.s8[1] == 0 && player->state != PLAYER_STATE_ROTATE) {
                    player->inputIdleTimer = 0;
                    if (player->direction == PLAYER_DIR_LEFT) {
                        player->work.f32[0] = 0.0f;
                        player->work.f32[1] = 180.0f;
                        m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 5, -1, player, m255_PlayerRotLerpUpdate, FALSE, TRUE);
                    }
                    player->state = PLAYER_STATE_TRANSITION;
                    player->direction = PLAYER_DIR_RIGHT;
                    ctx->work.s8[1] = 1;
                    if (player->speed - 1.0f < -15.0f) {
                        newSpeed = -15.0f;
                    } else {
                        newSpeed = player->speed - 1.0f;
                    }
                    player->speed = newSpeed;
                    if (!player->nutSeActive) {
                        player->nutSeNo = _HuAudPlayerFXPlay(0x4B3, m255_playerNoTbl[player->object->work[0]]);
                        player->nutSeActive = TRUE;
                    }
                    if (ABS(player->speed) < 5.0f) {
                        pitch = -50;
                    } else if (ABS(player->speed) < 10.0f) {
                        pitch = 0;
                    } else {
                        pitch = 50;
                    }
                    HuAudFXPitchSet(player->nutSeNo, pitch);
                    absSpeed = ABS(player->speed);
                    HuAudFXVolSet(player->nutSeNo, 100 + (s32)((absSpeed / 15.0f) * 27.0f));
                }
            }
            if (!(HuPadBtn[player->padId] & B_BUTTON)) {
                ctx->work.s8[0] = 0;
            }
            if (!(HuPadBtn[player->padId] & A_BUTTON)) {
                ctx->work.s8[1] = 0;
            }
            break;
    }
}

void m255_PlayerMotUpdate(FuncContext *ctx) {
    PlayerData *player = ctx->data;

    switch (ctx->state) {
        case 0:
            player->state = PLAYER_STATE_ON_PLATFORM;
            player->inputIdleTimer = 0;
            ctx->state = 1;
            ctx->work.s8[0] = 0;
            ctx->work.s8[1] = 0;
            break;
        case 1:
            switch (player->state) {
                case PLAYER_STATE_ON_PLATFORM:
                    ctx->work.s8[0] = 0;
                    if (player->speed == 0.0f) {
                        if (!player->lost) {
                            MgPlayerMotSet(player->object, PLAYER_ANIM_IDLE);
                        } else {
                            MgPlayerMotSet(player->object, PLAYER_ANIM_LOST);
                        }
                        if (player->nutSeActive) {
                            HuAudFXStop(player->nutSeNo);
                            player->nutSeActive = FALSE;
                        }
                    } else if (player->speed > 0.0f) {
                        player->inputIdleTimer++;
                        if (player->inputIdleTimer >= 6) {
                            player->speed -= 0.5f;
                        }
                        MgPlayerMotSet(player->object, PLAYER_ANIM_RUN);
                        if (Hu3DData[player->object->model[0]].motTime == 0.0f) {
                            CharFXPlay(0x28, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                        }
                    } else {
                        player->inputIdleTimer++;
                        if (player->inputIdleTimer >= 6) {
                            player->speed += 0.5f;
                        }
                        MgPlayerMotSet(player->object, PLAYER_ANIM_RUN);
                        if (Hu3DData[player->object->model[0]].motTime == 0.0f) {
                            CharFXPlay(0x28, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                        }
                    }
                    break;
                case PLAYER_STATE_WAIT_CAM:
                    MgPlayerMotSet(player->object, PLAYER_ANIM_IDLE);
                    break;
                case PLAYER_STATE_1:
                    if (Hu3DData[player->object->model[0]].motTime == 0.0f) {
                        CharFXPlay(0x1F, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                    }
                    MgPlayerMotSet(player->object, PLAYER_ANIM_WALK);
                    break;
                case PLAYER_STATE_FINISHED:
                    if (Hu3DData[player->object->model[0]].motTime == 0.0f) {
                        CharFXPlay(0x28, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                    }
                    MgPlayerMotSet(player->object, PLAYER_ANIM_WALK);
                    break;
                case PLAYER_STATE_JUMP:
                    MgPlayerMotSet(player->object, PLAYER_ANIM_JUMP);
                    if (ctx->work.s8[0] == 0) {
                        ctx->work.s8[0] = 1;
                        CharFXPlay(0x3A, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                    }
                    break;
                case PLAYER_STATE_WON:
                    if (m255_winVoiceF == 0) {
                        MgPlayerMotSet(player->object, PLAYER_ANIM_WON);
                        HuAudCharVoicePlayPlayer(omCharModelNoTbl[GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr][0] | 0x2F, -1, m255_playerNoTbl[player->object->work[0]]);
                        m255_winVoiceF = 1;
                    }
                    break;
                default:
                    if (Hu3DData[player->object->model[0]].motTime == 0.0f) {
                        CharFXPlay(0x28, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                    }
                    MgPlayerMotSet(player->object, PLAYER_ANIM_RUN);
                    break;
            }
            break;
    }
}

void m255_PlayerRotLerpUpdate(FuncContext *ctx) {
    PlayerData *player = ctx->data;

    switch (ctx->state) {
        case 0:
            ctx->work.s8[0] = 0;
            player->state = PLAYER_STATE_ROTATE;
            ctx->state = 1;
            break;
        case 1:
            if (m255_LerpCalc(&player->object->rot.y, (u8 *)&ctx->work.s8[0], player->work.f32[0], player->work.f32[1], 5.0f)) {
                m255_FuncReset(FGRP_PLAYER_1 + player->object->work[0], ctx);
                player->state = PLAYER_STATE_ON_PLATFORM;
            }
            break;
    }
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void m255_PlayerJumpExec(FuncContext *ctx) {
    PlayerData *player = ctx->data;
    Work *ctxWork = &ctx->work;
    f32 accelY;
    f32 scale;

    switch (ctx->state) {
        case 0:
            if (player->direction != PLAYER_DIR_RIGHT) {
                player->work.f32[0] = 0.0f;
                player->work.f32[1] = 180.0f;
                m255_FuncSet(FGRP_PLAYER_1 + player->object->work[0], 5, -1, player, m255_PlayerRotLerpUpdate, FALSE, TRUE);
                player->direction = PLAYER_DIR_RIGHT;
            }
            ctxWork->s8[0] = 0;
            ctxWork->s8[1] = 0;
            ctxWork->s8[2] = 0;
            ctxWork->f32[0] = player->object->trans.z;
            ctx->state = 1;
            break;
        case 1:
            if (player->state == PLAYER_STATE_ROTATE) {
                break;
            }
            switch (ctxWork->s8[1]) {
                case 0:
                    player->state = PLAYER_STATE_TRANSITION; // moving forward before jumping
                    if (m255_LerpCalc(&player->object->trans.z, (u8 *)&ctxWork->s8[0], ctxWork->f32[0], ctxWork->f32[0] - 80.0f, 10.0f)) {
                        ctxWork->s8[1] = 1;
                        ctxWork->f32[0] = player->object->trans.z;
                        if (player->currNutId < NUTS_TOTAL) {
                            ctxWork->f32[1] = 2000.0f;
                            ctxWork->f32[2] = 0.0f - player->currNutId * 450.0f;
                            ctxWork->f32[3] = 28.0f;
                            player->accelY = -1.22f;
                        } else {
                            if (player->work.s8[0] == 0) {
                                ctxWork->f32[1] = 1900.0f;
                                ctxWork->f32[2] = -2650.0f;
                                ctxWork->f32[3] = 25.0f;
                                player->accelY = -1.0f;
                                player->work.s8[0] = 1;
                                player->cuesEnabled = FALSE;
                                Hu3DModelAttrSet(player->object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrSet(player->object->model[MDL_BALLOON_B], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrSet(player->object->model[MDL_BALLOON_A], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            } else {
                                ctxWork->f32[1] = 1800.0f;
                                ctxWork->f32[2] = -3300.0f;
                                ctxWork->f32[3] = 45.0f;
                                player->accelY = -1.0f;
                                player->work.s8[0] = 2;
                                player->cuesEnabled = FALSE;
                                Hu3DModelAttrSet(player->object->model[MDL_ARROW], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                    Hu3DModelPosSet(player->object->model[1], player->object->trans.x, player->object->trans.y, player->object->trans.z);
                    break;
                case 1:
                    player->state = PLAYER_STATE_JUMP;
                    accelY = player->accelY;
                    if (accelY > 1.7f) {
                        accelY = 1.7f;
                    }
                    player->object->trans.y += accelY * accelY * (accelY >= 0.0f ? -35.0f : 35.0f);
                    player->accelY += 0.11f;
                    if (player->object->trans.y < ctxWork->f32[1]) {
                        if (ctxWork->s8[2] == 0) {
                            ctxWork->s8[2] = 1;
                            CharFXPlay(0x31, GwPlayer[m255_playerNoTbl[player->object->work[0]]].chr);
                        }
                        if (player->work.s8[0] == 1) {
                            player->object->trans.y = ctxWork->f32[1];
                            player->finished = TRUE;
                        } else {
                            player->object->trans.y = ctxWork->f32[1];
                        }
                        player->state = PLAYER_STATE_TRANSITION;
                    }
                    scale = 1.0f - (player->object->trans.y - ctxWork->f32[1]) * 0.01f;
                    if (scale < 0.0f) {
                        scale = 0.0f;
                    }
                    if (scale > 1.0f) {
                        scale = 1.0f;
                    }
                    Hu3DModelScaleSet(player->object->model[1], scale, 1.0f, scale);
                    Hu3DModelPosSet(player->object->model[1], player->object->trans.x, ctxWork->f32[1] + 1.0f, player->object->trans.z);
                    if (m255_LerpCalc(&player->object->trans.z, (u8 *)&ctxWork->s8[0], ctxWork->f32[0], ctxWork->f32[2], ctxWork->f32[3])) {
                        m255_FuncReset(FGRP_PLAYER_1 + player->object->work[0], ctx);
                        Hu3DModelScaleSet(player->object->model[1], 1.0f, 1.0f, 1.0f);
                        if (player->lost) {
                            player->state = PLAYER_STATE_ON_PLATFORM;
                        } else if (player->currNutId < NUTS_TOTAL) {
                            player->inputEnabled = TRUE;
                            player->state = PLAYER_STATE_ON_PLATFORM;
                        } else {
                            player->state = PLAYER_STATE_FINISHED;
                            m255_FuncSet(FGRP_CAMERA, 0, 0, player, m255_CameraWinMove, FALSE, FALSE);
                        }
                    }
                    break;
            }
            break;
    }
}

void m255_PlayerComInput(FuncContext *ctx) {
    PlayerData *player = ctx->data;
    u8 unused_stack[0x18];

    switch (ctx->state) {
        case 0:
            switch (GwPlayer[m255_playerNoTbl[player->object->work[0]]].cpu_difficulty) {
                case 0:
                    ctx->work.s8[2] = 9;  // controls the delay between button presses
                    ctx->work.s8[3] = 12; // controls precision when deciding when to stop running
                    break;
                case 1:
                    ctx->work.s8[2] = 7;
                    ctx->work.s8[3] = 10;
                    break;
                case 2:
                    ctx->work.s8[2] = 6;
                    ctx->work.s8[3] = 8;
                    break;
                case 3:
                    ctx->work.s8[2] = 4;
                    ctx->work.s8[3] = 6;
                    break;
            }
            ctx->work.f32[0] = (rand16() % (ctx->work.s8[3] + 1)) * 0.1f * 20.0f * 5.0f;
            ctx->work.f32[0] = (rand16() & 1) ? -ctx->work.f32[0] : ctx->work.f32[0];
            ctx->state = 1;
            break;
        case 1:
            if (player->finished) {
                break;
            }
            if (player->lost) {
                break;
            }
            if (player->currNutId != NUTS_TOTAL) {
                f32 temp_f6 = m255_StopDistCalc(player);
                NutData *nut = &m255_gameWork->worlds[player->object->work[0]].nuts[player->currNutId];
                HmfModel *nutModel = &Hu3DData[nut->modelId];
                f32 nextNutPosX;
                s8 temp_v1_3;

                if (player->currNutId == NUTS_TOTAL - 1) {
                    nextNutPosX = GOAL_POS_X;
                } else {
                    nextNutPosX = nut[1].startPosX;
                }
                if (player->state == PLAYER_STATE_JUMP) {
                    ctx->work.s8[4] = 0;
                }
                if (ABS((s32)(nutModel->pos.x + temp_f6 - (nextNutPosX + ctx->work.f32[0]))) < JUMP_RANGE_X) {
                    ctx->work.s8[4] = ctx->work.s8[4] - 1 - (rand16() & 1);
                    temp_v1_3 = rand16() % (ctx->work.s8[3] + 1) + ctx->work.s8[4];
                    ctx->work.f32[0] = (temp_v1_3 >= 0 ? temp_v1_3 : 0) * 0.1f * 20.0f * 5.0f;
                    ctx->work.f32[0] = (rand16() & 1) ? -ctx->work.f32[0] : ctx->work.f32[0];
                    HuPadBtn[player->padId] = 0;
                } else if (nutModel->pos.x + temp_f6 - (nextNutPosX + ctx->work.f32[0]) < 0.0f) {
                    ctx->work.s8[0]--;
                    if (ctx->work.s8[0] < 0) {
                        ctx->work.s8[0] = rand16() % ctx->work.s8[2] + 1;
                        HuPadBtn[player->padId] = A_BUTTON;
                    } else {
                        HuPadBtn[player->padId] = 0;
                    }
                } else if (nutModel->pos.x + temp_f6 - (nextNutPosX + ctx->work.f32[0]) > 0.0f) {
                    ctx->work.s8[1]--;
                    if (ctx->work.s8[1] < 0) {
                        ctx->work.s8[1] = rand16() % ctx->work.s8[2] + 1;
                        HuPadBtn[player->padId] = B_BUTTON;
                    } else {
                        HuPadBtn[player->padId] = 0;
                    }
                }
            }
            break;
    }
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
f32 m255_StopDistCalc(PlayerData *player) {
    f32 var_f4 = 0.0f;
    f32 absSpeed;
    f32 var_f2;

    absSpeed = ABS((s32)player->speed);
    for (var_f2 = 0.0f; var_f2 <= absSpeed; var_f2 += 0.5f) {
        var_f4 += var_f2 * 0.22222222f;
    }
    for (var_f2 = 0.0f; var_f2 < 6.0f; var_f2 += 1.0f) {
        var_f4 += absSpeed * 0.22222222f;
    }
    return (player->speed < 0.0f) ? var_f4 : -var_f4;
}
