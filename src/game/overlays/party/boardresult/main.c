#include "common_duel.h"
#include "game/overlays/duel/common/ovl_81.h"

#define OBJ_HMF_MODEL(obj) (Hu3DData[(obj)->omObj1->model[0]])

#define OBJ_MODEL_ROT_X(obj, angle)                                                                          \
    {                                                                                                        \
        sincosdf((angle), &OBJ_HMF_MODEL(obj).mtx[1][2], &OBJ_HMF_MODEL(obj).mtx[1][1]);                     \
        OBJ_HMF_MODEL(obj).mtx[2][1] = -OBJ_HMF_MODEL(obj).mtx[1][2];                                        \
        OBJ_HMF_MODEL(obj).mtx[2][2] = OBJ_HMF_MODEL(obj).mtx[1][1];                                         \
        OBJ_HMF_MODEL(obj).mtx[0][1] = OBJ_HMF_MODEL(obj).mtx[0][2] = OBJ_HMF_MODEL(obj).mtx[0][3] =         \
            OBJ_HMF_MODEL(obj).mtx[1][0] = OBJ_HMF_MODEL(obj).mtx[1][3] = OBJ_HMF_MODEL(obj).mtx[2][0] =     \
                OBJ_HMF_MODEL(obj).mtx[2][3] = OBJ_HMF_MODEL(obj).mtx[3][0] = OBJ_HMF_MODEL(obj).mtx[3][1] = \
                    OBJ_HMF_MODEL(obj).mtx[3][2] = 0.0f;                                                     \
        OBJ_HMF_MODEL(obj).mtx[0][0] = OBJ_HMF_MODEL(obj).mtx[3][3] = 1.0f;                                  \
    }

typedef struct BoardResultWork BoardResultWork;

typedef struct BoardResultSprFiles {
    s32 files[4];
} BoardResultSprFiles;

typedef struct BoardResultSprPositions {
    f32 pos[4][2];
} BoardResultSprPositions;

typedef struct BoardResultCharHeights {
    f32 heights[8];
} BoardResultCharHeights;

typedef struct BoardResultCharMotions {
    s32 motions[8];
} BoardResultCharMotions;

void boardresult_IntroExec(void);
void boardresult_ResultExec(void);
void boardresult_MainProc(void);
void boardresult_ExitObjMain(omObjData *);
void boardresult_ExitCheckObjMain(omObjData *);
void boardresult_SysInit(void);
void boardresult_SysClose(void);
void boardresult_BackInit(void);
void boardresult_BackClose(void);
void boardresult_FireworkEndPosSet(BoardResultWork *, f32, f32, f32);
void boardresult_FireworkStartPosSet(BoardResultWork *, f32, f32, f32);
void boardresult_FireworkTimeSet(BoardResultWork *, s16);
BoardResultWork *boardresult_FireworkCreate(s32);
void boardresult_FireworkSprSet(BoardResultWork *, s32);
void boardresult_FireworkFlagSet(BoardResultWork *, s32, s32);
s16 boardresult_FireworkFlagGet(BoardResultWork *);
void boardresult_FireworkBurstTimeSet(BoardResultWork *, s16);
Process *MBDPlayerPosMoveCreate(Vec *from, Vec *to, Vec *dest, s32 time);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void MBDPlayerModelCreate(s16, s32 *, s16);
void MBDPlayerModelKill(s16);
void MBDDlgWinExecAllKey(s32, s32);
void MBDSaiCreate(s32);
void MBDSaiNumSprCreate(s32);
void MBDSaiHit(s32);
void MBDSaiOrderModeSet(void);
void MBDArrayShuffle(u8 *, s32);
void MBDDlgWinMesWaitAllKey(void);
void MBDVecForwardSet(Vec *);
void MBDMotionEndShiftSet(Object *, s32, s32);
void MBDPlayerKeyWaitAll(void);
extern s32 mbSaiSeF;
extern s32 mbKSuitObj[];
extern s16 kakusiMasuItemHis[10];

s32 boardresult_winClosedF = 0;

Vec boardresult_iconStartPos = { -750.0f, 400.0f, 2000.0f };

Vec boardresult_iconEndPos = { 750.0f, 400.0f, 2000.0f };

Vec boardresult_hostStartPos = { -750.0f, 500.0f, 4000.0f };

Vec boardresult_hostPos = { -250.0f, 0.0f, 2500.0f };

Vec boardresult_hostAsidePos = { -250.0f, -400.0f, 2500.0f };

Vec boardresult_hostExitPos = { -500.0f, 400.0f, 3500.0f };

Vec boardresult_platformPosTbl[5] = {
    { 750.0f, 250.0f, 4000.0f },
    { -300.0f, 250.0f, 2000.0f },
    { -100.0f, 250.0f, 2000.0f },
    { 100.0f, 250.0f, 2000.0f },
    { 300.0f, 250.0f, 2000.0f }
};

Vec boardresult_cloudPosTbl[3] = {
    { 0.0f, -700.0f, 1500.0f },
    { 0.0f, -500.0f, 1000.0f },
    { 0.0f, -300.0f, 500.0f }
};

Vec boardresult_introStarPos = { -200.0f, 400.0f, -150.0f };

Vec boardresult_starStartPos = { 0.0f, 750.0f, 2500.0f };

Vec boardresult_starPos = { 0.0f, 250.0f, 2500.0f };

Vec boardresult_starRisePos = { 0.0f, 400.0f, 2500.0f };

Vec boardresult_starExitPos = { 0.0f, 1000.0f, 2500.0f };

Vec boardresult_introPlayerPos = { 500.0f, 50.0f, 500.0f };

Vec boardresult_playerPosTbl[8] = {
    { -300.0f, 750.0f, 2000.0f },
    { -100.0f, 750.0f, 2000.0f },
    { 100.0f, 750.0f, 2000.0f },
    { 300.0f, 750.0f, 2000.0f },
    { -300.0f, 250.0f, 2000.0f },
    { -100.0f, 250.0f, 2000.0f },
    { 100.0f, 250.0f, 2000.0f },
    { 300.0f, 250.0f, 2000.0f }
};

Vec boardresult_playerLinePosTbl[4] = {
    { -300.0f, 100.0f, 2000.0f },
    { -100.0f, 100.0f, 2000.0f },
    { 100.0f, 100.0f, 2000.0f },
    { 300.0f, 100.0f, 2000.0f }
};

Vec boardresult_playerLowPosTbl[4] = {
    { -300.0f, 0.0f, 2000.0f },
    { -100.0f, 0.0f, 2000.0f },
    { 100.0f, 0.0f, 2000.0f },
    { 300.0f, 0.0f, 2000.0f }
};

Vec boardresult_shufflePosTbl[16] = {
    { -300.0f, 50.0f, 2000.0f },
    { -100.0f, 50.0f, 2000.0f },
    { 100.0f, 50.0f, 2000.0f },
    { 300.0f, 50.0f, 2000.0f },
    { -300.0f, 25.0f, 2000.0f },
    { -100.0f, 25.0f, 2000.0f },
    { 100.0f, 25.0f, 2000.0f },
    { 300.0f, 25.0f, 2000.0f },
    { -300.0f, -25.0f, 2000.0f },
    { -100.0f, -25.0f, 2000.0f },
    { 100.0f, -25.0f, 2000.0f },
    { 300.0f, -25.0f, 2000.0f },
    { -300.0f, -50.0f, 2000.0f },
    { -100.0f, -50.0f, 2000.0f },
    { 100.0f, -50.0f, 2000.0f },
    { 300.0f, -50.0f, 2000.0f }
};

Vec boardresult_playerDropPosTbl[4] = {
    { -300.0f, -500.0f, 2000.0f },
    { -100.0f, -500.0f, 2000.0f },
    { 100.0f, -500.0f, 2000.0f },
    { 300.0f, -500.0f, 2000.0f }
};

Vec boardresult_winnerPosTbl[8] = {
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 240.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f }
};

Vec boardresult_bonus1PosTbl[1] = {
    { 0.0f, 100.0f, 2500.0f }
};

Vec boardresult_bonus2PosTbl[2] = {
    { -100.0f, 100.0f, 2500.0f },
    { 100.0f, 100.0f, 2500.0f }
};

Vec boardresult_bonus3PosTbl[3] = {
    { -200.0f, 100.0f, 2500.0f },
    { 0.0f, 100.0f, 2500.0f },
    { 200.0f, 100.0f, 2500.0f }
};

s32 boardresult_introMotMario[] = { 2, 0x2001B, 0x20024 };

s32 boardresult_resultMotMario[] = { 7, 0x2001F, 0x20030, 0x20034, 0x2002B, 0x20029, 0x2008F, 0x20090 };

s32 boardresult_introMotLuigi[] = { 2, 0, 0 };

s32 boardresult_resultMotLuigi[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotPeach[] = { 2, 0, 0 };

s32 boardresult_resultMotPeach[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotYoshi[] = { 2, 0, 0 };

s32 boardresult_resultMotYoshi[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotWario[] = { 2, 0, 0 };

s32 boardresult_resultMotWario[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotDk[] = { 2, 0, 0 };

s32 boardresult_resultMotDk[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotWaluigi[] = { 2, 0, 0 };

s32 boardresult_resultMotWaluigi[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 boardresult_introMotDaisy[] = { 2, 0, 0 };

s32 boardresult_resultMotDaisy[] = { 7, 0, 0, 0, 0, 0, 0, 0 };

s32 *boardresult_introMotTbl[8] = { boardresult_introMotMario, boardresult_introMotLuigi, boardresult_introMotPeach, boardresult_introMotYoshi, boardresult_introMotWario, boardresult_introMotDk, boardresult_introMotWaluigi, boardresult_introMotDaisy };

s32 *boardresult_resultMotTbl[8] = { boardresult_resultMotMario, boardresult_resultMotLuigi, boardresult_resultMotPeach, boardresult_resultMotYoshi, boardresult_resultMotWario, boardresult_resultMotDk, boardresult_resultMotWaluigi, boardresult_resultMotDaisy };

s32 boardresult_introMdlMotTbl[5] = { 0x13015C, 0x13015D, 0x13015E, 0x13015F, 0x130160 };

s32 boardresult_hostMot[] = { 2, 0xA0077, 0xA0078 };

/* Indexed by player (0-3); index 3 overlaps boardresult_bonusPosTbl[0]. */
omObjData *boardresult_numPulseObjTbl[3] = { NULL, NULL, NULL };

Vec *boardresult_bonusPosTbl[4] = { NULL, boardresult_bonus1PosTbl, boardresult_bonus2PosTbl, boardresult_bonus3PosTbl };

s32 boardresult_cloudHideF = 0;

f32 boardresult_cloudSpeed = 50.0f;

s32 boardresult_cloudHiddenTbl[6] = { 0, 0, 0, 0, 0, 0 };

s32 boardresult_fireworkSprTbl[] = {
    0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045
};

const BoardResultSprFiles boardresult_titleSprFileTbl = { { 0x1301C1, 0x1301C2, 0x1301C3, 0x1301C4 } };

const BoardResultSprPositions boardresult_titleSprLPosTbl = { {
    { 200.0f, 60.0f },
    { 80.0f, 0.0f },
    { 0.0f, 120.0f },
    { 80.0f, 120.0f },
} };

const BoardResultSprPositions boardresult_titleSprRPosTbl = { {
    { 120.0f, 60.0f },
    { -80.0f, 0.0f },
    { 0.0f, 120.0f },
    { -80.0f, 120.0f },
} };

const BoardResultCharHeights boardresult_chrHeightTbl = { { 120.0f, 120.0f, 180.0f, 160.0f, 160.0f, 190.0f, 120.0f, 180.0f } };

u8 boardresult_boardNo BSS;
Object *boardresult_starMdl BSS;
s16 boardresult_playerAnimTbl[4][8] BSS;
GW_PLAYER *boardresult_gwPlayerTbl[4] BSS;
Object *boardresult_cloudMdlTbl[6] BSS;
Object *boardresult_platformMdlTbl[4] BSS;
Object *boardresult_hostMdl BSS;
s16 boardresult_hostAnim BSS;
s16 boardresult_hostAnimLink BSS;
s16 boardresult_hostAnimTbl[8] BSS;
s32 boardresult_numSprGrpTbl[4] BSS;
s32 boardresult_numSprAnim BSS;
u8 boardresult_numSprAnimPad[4] BSS; /* Unreferenced. */
Object *boardresult_starIconMdlTbl[4] BSS;
s16 boardresult_starEffTbl[4] BSS;
f32 boardresult_cloudSpeedOfsTbl[6] BSS;

void boardresult_ObjectSetup(void) {
    s32 i;
    u32 j;

    boardresult_boardNo = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    boardresult_BackInit();
    boardresult_SysInit();
    MBDShadowHeightMaxSet(700.0f);
    MBDModelScaleMulSet(1.6f);
    HuWinInit();
    omAddPrcObj(boardresult_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, boardresult_ExitCheckObjMain);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < boardresult_introMotMario[0]; j++) {
            boardresult_introMotTbl[i][j + 1] = CharMotionDataNumGet(i, boardresult_introMotMario[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < boardresult_resultMotMario[0]; j++) {
            boardresult_resultMotTbl[i][j + 1] = CharMotionDataNumGet(i, boardresult_resultMotMario[j + 1]);
        }
    }

    MBDWinComKeyAllNumSet(4);
}

void boardresult_StarHoverObjMain(omObjData *obj) {
    boardresult_starMdl->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void boardresult_IntroExec(void) {
    s16 models[5];
    Vec targets[4];
    UnkBoard4 *groups[2];
    BoardResultSprFiles files = boardresult_titleSprFileTbl;
    BoardResultSprPositions leftPos = boardresult_titleSprLPosTbl;
    BoardResultSprPositions rightPos = boardresult_titleSprRPosTbl;
    BoardResultCharHeights heights = boardresult_chrHeightTbl;
    omObjData *obj;
    HmfMotionNode *node;
    void *data;
    s16 model;
    f32 baseY;
    s32 i;
    s32 j;

    groups[0] = MBDSprGrpCreate(4, 2);
    for (i = 0; i < 4; i++) {
        data = DataRead(files.files[i]);
        groups[0]->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(groups[0]->unk_0A, i, groups[0]->unk_0C[i], 0);
        HuSprPriSet(groups[0]->unk_0A, i, 1);
        HuSprAttrSet(groups[0]->unk_0A, i, HUSPR_ATTR_NONE);
        HuSprPosSet(groups[0]->unk_0A, i, leftPos.pos[i][0], leftPos.pos[i][1]);
        DataClose(data);
    }

    groups[1] = MBDSprGrpCreate(4, 2);
    for (i = 0; i < 4; i++) {
        data = DataRead(files.files[i]);
        groups[1]->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(groups[1]->unk_0A, i, groups[0]->unk_0C[i], 0);
        HuSprPriSet(groups[1]->unk_0A, i, 1);
        HuSprAttrSet(groups[1]->unk_0A, i, HUSPR_ATTR_FLIPX);
        HuSprPosSet(groups[1]->unk_0A, i, rightPos.pos[i][0], rightPos.pos[i][1]);
        DataClose(data);
    }

    for (i = 0; i < 4; i++) {
        boardresult_gwPlayerTbl[i] = MBDPlayerGet(i);
        MBDPlayerModelCreate(i, boardresult_introMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&boardresult_gwPlayerTbl[i]->player_obj->coords, &boardresult_introPlayerPos);
        MBDModelTempAllocFree(boardresult_gwPlayerTbl[i]->player_obj);
        boardresult_gwPlayerTbl[i]->player_obj->flags |= 1;
        boardresult_gwPlayerTbl[i]->stat |= 4;
    }

    WipeCreateIn(WIPE_STARS, 16);
    HuPrcSleep(17);
    MBDBackTPLvlSet(0);
    HuAudFXPlay(0x173);
    for (i = 0; i < 160; i += 3) {
        HuSprPosSet(groups[0]->unk_0A, 0, leftPos.pos[0][0] + i, leftPos.pos[0][1]);
        HuSprPosSet(groups[1]->unk_0A, 0, rightPos.pos[0][0] - i, rightPos.pos[0][1]);
        HuPrcVSleep();
    }
    MBDSprGrpKill(groups[0]);
    MBDSprGrpKill(groups[1]);
    HuPrcSleep(10);
    MBDBackTPLvlSet(255);

    boardresult_starMdl = MBDModelCreate(0x3B, 0);
    AuraCreate(boardresult_starMdl->omObj1->model[0]);
    MBDModelTempAllocFree(boardresult_starMdl);
    HuVecCopy3F(&boardresult_starMdl->coords, &boardresult_introStarPos);
    obj = omAddObj(0x1000, 0, 0, -1, boardresult_StarHoverObjMain);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;

    model = Hu3DModelRead(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = Hu3DModelReadNum(boardresult_introMdlMotTbl[i]);
    }
    Hu3DModelVtxBufMake(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    Hu3DMotionModelSetEx(model, models[0]);
    Hu3DMotionAttrSet(model, 2, 1);
    HuPrcSleep(10);

    for (i = 0; i < 4; i++) {
        MBDMotionSet(boardresult_gwPlayerTbl[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&targets[i], 0.0f, 0.0f, 0.0f);
        MBDVecDirGet(&targets[i], &boardresult_gwPlayerTbl[i]->player_obj->coords,
                     &boardresult_gwPlayerTbl[i]->player_obj->rot);
        targets[i].y += heights.heights[GwPlayer[i].chr];
        boardresult_gwPlayerTbl[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords, &targets[i],
                              &boardresult_gwPlayerTbl[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&boardresult_gwPlayerTbl[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f,
                         (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 8) {
                Hu3DMotionAttrSet(model, 0, 1);
            }
            if (j == 18) {
                Hu3DMotionAttrSet(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                    case 2:
                        HuAudFXPlay(0x166);
                        break;
                    case 3:
                        HuAudFXPlay(0x167);
                        break;
                }
            }
        }
        MBDModelDispOff(boardresult_gwPlayerTbl[i]->player_obj);
    }

    HuPrcSleep(10);
    HuAudFXPlay(0x168);
    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(47);
    Hu3DMotionAttrSet(model, 0, 1);

    Hu3DMotionNoMotSet(boardresult_starMdl->omObj1->model[0],
                       Hu3DData[boardresult_starMdl->omObj1->model[0]].motId, "l_mayu", 76, 71);
    node = Hu3DModelObjPtrGet(boardresult_starMdl->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x174);
    Hu3DMotionNoMotSet(boardresult_starMdl->omObj1->model[0],
                       Hu3DData[boardresult_starMdl->omObj1->model[0]].motId, "hige", 23, 70);
    node = Hu3DModelObjPtrGet(boardresult_starMdl->omObj1->model[0], "hige");
    baseY = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + baseY;
        HuPrcVSleep();
    }
    node->basePos.y = baseY;

    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x169);
    for (i = 0; i < 4; i++) {
        PlayerFXPlay(0x286, i);
        MBDMotionSet(boardresult_gwPlayerTbl[i]->player_obj, 1, 2);
        Hu3DMotionAttrSet(boardresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&boardresult_gwPlayerTbl[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&targets[i], &boardresult_introPlayerPos);
        targets[i].y += 400.0f;
        HuMtxRotXF(Hu3DData[boardresult_gwPlayerTbl[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        MBDModelDispOn(boardresult_gwPlayerTbl[i]->player_obj);
        MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords, &targets[i],
                              &boardresult_gwPlayerTbl[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; j--) {
            HuVecCopyXYZ(&boardresult_gwPlayerTbl[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f,
                         (5.0f - j) / 10.0f + 0.5f, (5.0f - j) / 10.0f + 0.5f);
            HuPrcVSleep();
        }
    }

    WipeCreateOut(WIPE_STARS, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    Hu3DModelKill(model);
    for (i = 0; i < 5; i++) {
        Hu3DModelKill(models[i]);
    }
    omDelObj(obj);
    AuraKill(boardresult_starMdl->omObj1->model[0]);
    MBDModelKill(boardresult_starMdl);
    for (i = 0; i < 4; i++) {
        MBDPlayerModelKill(i);
    }
}

s16 boardresult_ModelAnimCreate(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    boardresult_hostAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    boardresult_hostAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void boardresult_ModelAnimSet(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (boardresult_hostAnimLink != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[boardresult_hostAnimLink];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 boardresult_AnimDataRead(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void boardresult_CloudScrollObjMain(omObjData *obj) {
    Hu3DModelObjTexScroll(boardresult_cloudMdlTbl[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(boardresult_cloudMdlTbl[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(boardresult_cloudMdlTbl[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

    obj->trans.x -= 4.0f;
    obj->trans.y -= 2.0f;
    obj->trans.z -= 1.0f;

    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.z >= 64.0f) {
        obj->trans.z -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
    if (obj->trans.z <= -64.0f) {
        obj->trans.z += 64.0f;
    }
}

void boardresult_PlatformSwayObjMain(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        boardresult_platformMdlTbl[i]->rot.x = sindf(obj->rot.x);
        boardresult_platformMdlTbl[i]->rot.z = cosdf(obj->rot.x);
    }

    if (obj->work[0] == 0) {
        obj->rot.x += 20.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
    } else if (obj->rot.x < 360.0f) {
        obj->rot.x += 20.0f;
    } else {
        obj->rot.x = 360.0f;
    }
}

void boardresult_PlatformSlideObjMain(omObjData *obj) {
    Object *target = boardresult_platformMdlTbl[obj->work[1]];

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void boardresult_HostSlideObjMain(omObjData *obj) {
    Object *target = boardresult_hostMdl;

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void boardresult_PlayerLandProc(void) {
    s32 index;
    Process *process;
    f32 angle;
    s32 offset;

    index = *(s32 *)HuPrcCurrentGet()->user_data;
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[index]->player_obj->coords,
                                                  &boardresult_playerPosTbl[index + 4],
                                                  &boardresult_gwPlayerTbl[index]->player_obj->coords, 10));
    MBDMotionSet(boardresult_gwPlayerTbl[index]->player_obj, 0, 0);

    for (angle = 90.0f; angle > 0.0f; angle -= 9.0f) {
        OBJ_MODEL_ROT_X(boardresult_platformMdlTbl[3 - index], angle);
        HuPrcVSleep();
    }
    OBJ_MODEL_ROT_X(boardresult_platformMdlTbl[3 - index], 0.0f);

    HuAudFXPlay(0x175);
    for (offset = 0, angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&boardresult_gwPlayerTbl[index]->player_obj->coords, boardresult_playerPosTbl[index + 4].x,
                     boardresult_playerPosTbl[index + 4].y - sindf(angle) * 100.0f + offset,
                     boardresult_playerPosTbl[index + 4].z);
        HuVecCopyXYZ(&boardresult_platformMdlTbl[3 - index]->coords, boardresult_playerPosTbl[index + 4].x,
                     boardresult_playerPosTbl[index + 4].y - sindf(angle) * 100.0f + offset,
                     boardresult_playerPosTbl[index + 4].z);
        offset -= 10;
        HuPrcVSleep();
    }
    MBDMotionSet(boardresult_gwPlayerTbl[index]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void boardresult_NumPulseObjMain(omObjData *obj) {
    f32 scale;
    u32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(boardresult_numSprGrpTbl[obj->work[0]], i, scale, scale);
    }

    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void boardresult_CoinNumCreate(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 coin;
    s32 digits[3];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    boardresult_numSprAnim = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 4; i++) {
        boardresult_numSprGrpTbl[i] = HuSprGrpCreate(3, 5);
        coin = GwPlayer[i].coin;
        if (coin >= 100) {
            count = 3;
            digits[0] = coin / 100;
            coin %= 100;
            digits[1] = coin / 10;
            coin %= 10;
            digits[2] = coin;
        } else if (coin >= 10) {
            count = 2;
            coin %= 100;
            digits[0] = coin / 10;
            coin %= 10;
            digits[1] = coin;
        } else {
            count = 1;
            digits[0] = coin;
        }

        for (j = 0; j < count; j++) {
            HuSprGrpMemberSet(boardresult_numSprGrpTbl[i], j, boardresult_numSprAnim, 0);
            HuSprAnimModeSet(boardresult_numSprGrpTbl[i], j, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(boardresult_numSprGrpTbl[i], j, digits[j], 0);
            HuSprPriSet(boardresult_numSprGrpTbl[i], j, 0x4790);
            HuSprAttrSet(boardresult_numSprGrpTbl[i], j, HUSPR_ATTR_XLU);
            HuSprColorSet(boardresult_numSprGrpTbl[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(boardresult_numSprGrpTbl[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(boardresult_numSprGrpTbl[i], j, j * 14, 0);
            }
        }

        coin = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && coin < GwPlayer[j].coin) {
                coin = GwPlayer[j].coin;
            }
        }
        if (coin == GwPlayer[i].coin) {
            boardresult_numPulseObjTbl[i] = omAddObj(0x1000, 0, 0, -1, boardresult_NumPulseObjMain);
            boardresult_numPulseObjTbl[i]->work[0] = i;
            boardresult_numPulseObjTbl[i]->work[1] = count;
            boardresult_numPulseObjTbl[i]->rot.x = 0.0f;
        }
    }
}

void boardresult_CoinNumKill(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (boardresult_numPulseObjTbl[i] != NULL) {
            omDelObj(boardresult_numPulseObjTbl[i]);
            boardresult_numPulseObjTbl[i] = NULL;
        }
        HuSprGrpKill(boardresult_numSprGrpTbl[i]);
    }
    HuSprAnimKill(boardresult_numSprAnim);
    HuPrcVSleep();
}

void boardresult_StarNumCreate(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 star;
    s32 digits[2];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    boardresult_numSprAnim = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 4; i++) {
        boardresult_numSprGrpTbl[i] = HuSprGrpCreate(2, 5);
        star = GwPlayer[i].star;
        count = 1;
        if (star >= 10) {
            count = 2;
            star %= 100;
            digits[0] = star / 10;
            star %= 10;
            digits[1] = star;
        } else {
            digits[0] = star;
        }

        for (j = 0; j < count; j++) {
            HuSprGrpMemberSet(boardresult_numSprGrpTbl[i], j, boardresult_numSprAnim, 0);
            HuSprAnimModeSet(boardresult_numSprGrpTbl[i], j, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(boardresult_numSprGrpTbl[i], j, digits[j], 0);
            HuSprPriSet(boardresult_numSprGrpTbl[i], j, 0x4790);
            HuSprAttrSet(boardresult_numSprGrpTbl[i], j, HUSPR_ATTR_XLU);
            HuSprColorSet(boardresult_numSprGrpTbl[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(boardresult_numSprGrpTbl[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(boardresult_numSprGrpTbl[i], j, j * 14, 0);
            }
        }

        star = GwPlayer[i].star;
        for (j = 0; j < 4; j++) {
            if (j != i && star < GwPlayer[j].star) {
                star = GwPlayer[j].star;
            }
        }
        if (star == GwPlayer[i].star) {
            boardresult_numPulseObjTbl[i] = omAddObj(0x1000, 0, 0, -1, boardresult_NumPulseObjMain);
            boardresult_numPulseObjTbl[i]->work[0] = i;
            boardresult_numPulseObjTbl[i]->work[1] = count;
            boardresult_numPulseObjTbl[i]->rot.x = 0.0f;
        }
    }
}

void boardresult_StarNumKill(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (boardresult_numPulseObjTbl[i] != NULL) {
            omDelObj(boardresult_numPulseObjTbl[i]);
            boardresult_numPulseObjTbl[i] = NULL;
        }
        HuSprGrpKill(boardresult_numSprGrpTbl[i]);
    }
    HuSprAnimKill(boardresult_numSprAnim);
    HuPrcVSleep();
}

void boardresult_StarGiveExec(u8 *flags) {
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        if (flags[i] != 0) {
            GwPlayer[i].star++;
            if (GwPlayer[i].star >= 100) {
                GwPlayer[i].star = 99;
            }
            MBDMotionShiftSetDef(GwPlayer[i].player_obj, 1, 0);
            PlayerFXPlay(0x274, i);
            Hu3DParticleAttrSet(boardresult_starEffTbl[i], 0, 1);
            for (j = 800; j >= 250; j -= 15) {
                f32 angle;

                MBDModelDispOn(boardresult_starIconMdlTbl[i]);
                HuVecCopyXYZ(&boardresult_starIconMdlTbl[i]->scale, 0.75f, 0.75f, 0.75f);
                HuVecCopyXYZ(&boardresult_starIconMdlTbl[i]->coords, GwPlayer[i].player_obj->coords.x,
                             j + GwPlayer[i].player_obj->coords.y, GwPlayer[i].player_obj->coords.z - 50.0f);
                angle = j * 2 - 160;
                boardresult_starIconMdlTbl[i]->rot.x = sindf(angle);
                boardresult_starIconMdlTbl[i]->rot.z = cosdf(angle);
                EffectPosSet(boardresult_starEffTbl[i], boardresult_starIconMdlTbl[i]->coords.x,
                                   boardresult_starIconMdlTbl[i]->coords.y - 20.0f, boardresult_starIconMdlTbl[i]->coords.z);
                if (j == 650) {
                    HuAudFXPlay(0x176);
                }
                HuPrcVSleep();
            }
            Hu3DParticleAttrSet(boardresult_starEffTbl[i], 1, 0);
        }
    }
    for (j = 0; j < 4; j++) {
        if (flags[j] != 0) {
            MBDModelMotionWait(GwPlayer[j].player_obj);
        }
    }
    HuPrcSleep(10);
    HuAudFXPlay(0x171);
    while (1) {
        for (i = 0; i < 4; i++) {
            boardresult_starIconMdlTbl[i]->scale.x -= 0.1f;
            boardresult_starIconMdlTbl[i]->scale.y -= 0.1f;
            boardresult_starIconMdlTbl[i]->scale.z -= 0.1f;
            boardresult_starIconMdlTbl[i]->coords.y -= 20.0f;
        }
        HuPrcVSleep();
        if (boardresult_starIconMdlTbl[0]->scale.x <= 0.05f) {
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        MBDModelDispOff(boardresult_starIconMdlTbl[i]);
        HuVecCopyXYZ(&boardresult_starIconMdlTbl[i]->scale, 0.75f, 0.75f, 0.75f);
    }
    for (j = 0; j < 4; j++) {
        if (flags[j] != 0) {
            MBDMotionShiftSetDef(GwPlayer[j].player_obj, -1, 2);
        }
    }
}

void boardresult_BonusStarExec(s16 effect) {
    u8 winners[4];
    s32 chars[4];
    s32 i;
    s32 j;
    s32 k;
    s32 max;
    s32 gameCount;
    s32 coinCount;
    s32 eventCount;
    Vec *dests;

    for (i = 0; i < 4; i++) {
        boardresult_starIconMdlTbl[i] = MBDModelCreate(0x1D, NULL);
        MBDModelDispOff(boardresult_starIconMdlTbl[i]);
        HuPrcVSleep();
        boardresult_starEffTbl[i] = EffectCreate(0xB0004, 0x6A9);
        EffectParamSet(boardresult_starEffTbl[i], 10.0f, 20.0f, 8.0f);
        Hu3DParticleAttrSet(boardresult_starEffTbl[i], 1, 0);
        HuPrcVSleep();
    }

    MBDDlgWinExecAllKey(-1, 0x1402);
    MBDDlgWinExecAllKey(-1, 0x1403);

    // Minigame star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].gamePrize) {
            max = GwPlayer[i].gamePrize;
        }
    }
    for (i = 0, gameCount = 0; i < 4; i++) {
        if (GwPlayer[i].gamePrize == max) {
            winners[i] = 1;
            gameCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = mbKSuitObj[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x1404, 0x1405, 0x1406, 0x1407 };

        if (gameCount == 4) {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[2]);
        } else {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[3]);
        }
        MBDDlgWinInsertCreateAllKey(-1, msgs[gameCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[0]);
        if (gameCount == 3) {
            MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostAsidePos,
                                  &boardresult_hostMdl->coords, 10);
        }
        if (gameCount != 4) {
            dests = boardresult_bonusPosTbl[gameCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[k], &boardresult_gwPlayerTbl[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[k++],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            boardresult_StarGiveExec(winners);
            dests = boardresult_playerLinePosTbl;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[i], &boardresult_gwPlayerTbl[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[i],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (gameCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostPos,
                                                                    &boardresult_hostMdl->coords, 10));
        }
    }

    MBDDlgWinExecAllKey(-1, 0x1408);
    // Coin star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].coinPrize) {
            max = GwPlayer[i].coinPrize;
        }
    }
    for (i = 0, coinCount = 0; i < 4; i++) {
        if (GwPlayer[i].coinPrize == max) {
            winners[i] = 1;
            coinCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = mbKSuitObj[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x1409, 0x140A, 0x140B, 0x140C };

        if (coinCount == 4) {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[2]);
        } else {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[3]);
        }
        MBDDlgWinInsertCreateAllKey(-1, msgs[coinCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[0]);
        if (coinCount == 3) {
            MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostAsidePos,
                                  &boardresult_hostMdl->coords, 10);
        }
        if (coinCount != 4) {
            dests = boardresult_bonusPosTbl[coinCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[k], &boardresult_gwPlayerTbl[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[k++],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            boardresult_StarGiveExec(winners);
            dests = boardresult_playerLinePosTbl;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[i], &boardresult_gwPlayerTbl[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[i],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (coinCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostPos,
                                                                    &boardresult_hostMdl->coords, 10));
        }
    }

    MBDDlgWinExecAllKey(-1, 0x140D);

    // Happening star
    for (i = 0, max = -100000; i < 4; i++) {
        if (max < GwPlayer[i].stats.prize.hatenaPrize) {
            max = GwPlayer[i].stats.prize.hatenaPrize;
        }
    }
    for (i = 0, eventCount = 0; i < 4; i++) {
        if (GwPlayer[i].stats.prize.hatenaPrize == max) {
            winners[i] = 1;
            eventCount++;
        } else {
            winners[i] = 0;
        }
    }
    for (i = 0, j = 0; i < 4; i++) {
        if (winners[i] != 0) {
            chars[j] = mbKSuitObj[GwPlayer[i].chr];
            j++;
        }
    }
    for (; j < 4; j++) {
        chars[j] = 0;
    }
    {
        s32 msgs[] = { 0x140E, 0x140F, 0x1410, 0x1411 };

        if (eventCount == 4) {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[2]);
        } else {
            boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[3]);
        }
        MBDDlgWinInsertCreateAllKey(-1, msgs[eventCount - 1], chars[0], chars[1], chars[2], chars[3], 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[0]);
        if (eventCount == 3) {
            MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostAsidePos,
                                  &boardresult_hostMdl->coords, 10);
        }
        if (eventCount != 4) {
            dests = boardresult_bonusPosTbl[eventCount];
            for (k = 0, i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[k], &boardresult_gwPlayerTbl[i]->player_obj->coords, 20));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[k++],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 20));
                }
            }
            HuPrcChildWatch();
            boardresult_StarGiveExec(winners);
            dests = boardresult_playerLinePosTbl;
            for (i = 0; i < 4; i++) {
                if (winners[i] != 0) {
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords,
                                                                            &dests[i], &boardresult_gwPlayerTbl[i]->player_obj->coords, 10));
                    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &dests[i],
                                                                            &boardresult_platformMdlTbl[3 - i]->coords, 10));
                }
            }
            HuPrcChildWatch();
        }
        if (eventCount == 3) {
            HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostPos,
                                                                    &boardresult_hostMdl->coords, 10));
        }
    }
    for (i = 0; i < 4; i++) {
        MBDModelKill(boardresult_starIconMdlTbl[i]);
        EffectStop(boardresult_starEffTbl[i]);
    }
}

void boardresult_CloudPassProc(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            HuVecCopyXYZ(&boardresult_cloudMdlTbl[i]->coords, boardresult_cloudMdlTbl[i]->coords.x,
                         boardresult_cloudMdlTbl[i]->coords.y - (boardresult_cloudSpeed + boardresult_cloudSpeedOfsTbl[i]),
                         boardresult_cloudMdlTbl[i]->coords.z);
            if (boardresult_cloudMdlTbl[i]->coords.y <= -1000.0f) {
                HuVecCopyXYZ(&boardresult_cloudMdlTbl[i]->coords, (MBDRand(300.0f) - 150) * 5.0f,
                             (MBDRand(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                boardresult_cloudSpeedOfsTbl[i] =
                    MBDRand(boardresult_cloudSpeed / 2.0f) - boardresult_cloudSpeed / 4.0f;
                if (boardresult_cloudHideF) {
                    MBDModelDispOff(boardresult_cloudMdlTbl[i]);
                    boardresult_cloudHiddenTbl[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

s32 boardresult_CloudPassDoneCheck(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (boardresult_cloudHiddenTbl[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void boardresult_FireworkRandSet(BoardResultWork *work, s32 index) {
    s32 x, y, z;

    x = MBDRand(256.0f) - 128;
    y = -MBDRand(256.0f) - 500;
    boardresult_FireworkStartPosSet(work, x, y, 0.0f);
    x = MBDRand(100.0f) + index * 500 - 550;
    y = MBDRand(64.0f) + 218;
    z = MBDRand(500.0f) - 500;
    boardresult_FireworkEndPosSet(work, x, y, z);
    boardresult_FireworkTimeSet(work, MBDRand(60.0f) + 30);
}

void boardresult_FireworkShowProc(void) {
    BoardResultWork *works[3];
    s32 i;
    s32 count;

    for (i = 0; i < 3; i++) {
        works[i] = boardresult_FireworkCreate(boardresult_fireworkSprTbl[GwPlayer[kakusiMasuItemHis[0]].chr]);
        boardresult_FireworkRandSet(works[i], i);
        boardresult_FireworkFlagSet(works[i], 2, 2);
    }

    while (1) {
        for (i = 0; i < 3; i++) {
            if ((boardresult_FireworkFlagGet(works[i]) & 1) && rand8() < 0x20) {
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        boardresult_FireworkFlagSet(works[i], 2, 0);
                        count += boardresult_FireworkFlagGet(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                boardresult_FireworkRandSet(works[0], 0);
                boardresult_FireworkEndPosSet(works[0], 0.0f, 250.0f, 1500.0f);
                boardresult_FireworkFlagSet(works[0], 1, 0);
                boardresult_FireworkSprSet(works[0], 0xB0046);
                boardresult_FireworkBurstTimeSet(works[0], 120);
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        boardresult_FireworkFlagSet(works[i], 2, 0);
                        count += boardresult_FireworkFlagGet(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    boardresult_FireworkFlagSet(works[i], 3, 2);
                    boardresult_FireworkSprSet(works[i], boardresult_fireworkSprTbl[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                boardresult_FireworkBurstTimeSet(works[0], 60);
                boardresult_FireworkRandSet(works[0], 0);
                break;
            }
            boardresult_FireworkRandSet(works[i], i);
        }
        HuPrcVSleep();
    }
}

// Defined here (rather than at the top of the file) to keep rodata ordering.
const BoardResultCharMotions boardresult_chrAnimTbl = { {
    0x000200A4,
    0x000300A4,
    0x000700A4,
    0x000400A4,
    0x000500A4,
    0x000600A4,
    0x000800A4,
    0x0009001B,
} };

const BoardResultCharMotions boardresult_chrWinAnimTbl = { {
    0x000200AB,
    0x000300AB,
    0x000700AB,
    0x000400AB,
    0x000500AB,
    0x000600AB,
    0x000800AB,
    0x00090027,
} };

void boardresult_ResultExec(void) {
    s32 values[4];
    s32 rank[4];
    s32 chars[4];
    u8 state[4];
    u8 count[4];
    s32 work[4];
    s32 order[4];
    BoardResultCharHeights heights = boardresult_chrHeightTbl;
    BoardResultCharMotions motions;
    BoardResultCharMotions winMotions;
    omObjData *cloudObj;
    omObjData *rotObj;
    omObjData *swayObj;
    omObjData *obj;
    Object *actor;
    Process *process;
    s16 effect;
    Process *fallProc;
    UnkBoard4 *group;
    void *data;
    s32 seNo;
    s32 i;
    s32 j;
    s32 n;
    s32 k;

    MBDBackKill();
    MBDBackLoad(1);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
    for (i = 0; i < 4; i++) {
        boardresult_gwPlayerTbl[i] = MBDPlayerGet(i);
        MBDPlayerModelCreate(i, boardresult_resultMotTbl[GwPlayer[i].chr], 2);
        boardresult_gwPlayerTbl[i]->player_obj->flags |= 1;
        boardresult_gwPlayerTbl[i]->stat |= 4;
        motions = boardresult_chrAnimTbl;
        winMotions = boardresult_chrWinAnimTbl;
        boardresult_playerAnimTbl[i][0] =
            CharAnimCreate(boardresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                               motions.motions[GwPlayer[i].chr]);
        boardresult_playerAnimTbl[i][1] = Hu3DAnimDataRead(winMotions.motions[GwPlayer[i].chr]);
        CharAnimSet(boardresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                           boardresult_playerAnimTbl[i][0]);
        MBDModelTempAllocFree(boardresult_gwPlayerTbl[i]->player_obj);
    }

    for (i = 0; i < 4; i++) {
        HuVecCopyXYZ(&boardresult_gwPlayerTbl[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
        HuVecCopy3F(&boardresult_gwPlayerTbl[i]->player_obj->coords, &boardresult_playerPosTbl[i]);
        MBDVecForwardSet(&boardresult_gwPlayerTbl[i]->player_obj->rot);
        HuMtxRotXF(Hu3DData[boardresult_gwPlayerTbl[i]->player_obj->omObj1->model[0]].mtx, 0.0f);
    }

    for (i = 0; i < 3; i++) {
        boardresult_cloudMdlTbl[i] = MBDModelFileCreate(0x1301C7, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(boardresult_cloudMdlTbl[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(boardresult_cloudMdlTbl[i]->omObj1->model[0], 255 - i * 64);
        HuVecCopy3F(&boardresult_cloudMdlTbl[i]->coords, &boardresult_cloudPosTbl[i]);
        Hu3DModelVtxBufMake(boardresult_cloudMdlTbl[i]->omObj1->model[0]);
        HuVecCopyXYZ(&boardresult_cloudMdlTbl[i]->scale, 1.0f - i * 0.2f, 1.0f - i * 0.2f, 1.0f - i * 0.2f);
        MBDModelTempAllocFree(boardresult_cloudMdlTbl[i]);
    }
    cloudObj = omAddObj(0x1000, 0, 0, -1, boardresult_CloudScrollObjMain);

    for (i = 0; i < 4; i++) {
        boardresult_platformMdlTbl[i] = MBDModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, 0);
        HuVecCopy3F(&boardresult_platformMdlTbl[i]->coords, &boardresult_platformPosTbl[0]);
        HuVecCopyXYZ(&boardresult_platformMdlTbl[i]->scale, 0.625f, 0.625f, 0.625f);
        OBJ_MODEL_ROT_X(boardresult_platformMdlTbl[i], 90.0f);
        MBDModelTempAllocFree(boardresult_platformMdlTbl[i]);
    }
    rotObj = omAddObj(0x1000, 0, 0, -1, boardresult_PlatformSwayObjMain);

    boardresult_hostMdl = MBDModelCreate(0x3E, boardresult_hostMot);
    boardresult_hostMdl->flags |= 1;
    HuVecCopy3F(&boardresult_hostMdl->coords, &boardresult_hostStartPos);
    boardresult_hostMdl->rot.x = sindf(10.0f);
    boardresult_hostMdl->rot.z = cosdf(10.0f);
    boardresult_hostAnimTbl[0] =
        boardresult_ModelAnimCreate(boardresult_hostMdl->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    boardresult_hostAnimTbl[1] = boardresult_AnimDataRead(0xA0081);
    boardresult_hostAnimTbl[2] = boardresult_AnimDataRead(0xA0083);
    boardresult_hostAnimTbl[3] = boardresult_AnimDataRead(0xA0084);
    boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[0]);

    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 10.0f, 30.0f, 8.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    HuAudSeqPlay(0xF);
    WipeCreateIn(WIPE_STARS, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    for (i = 0; i < 4; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[i]->coords, &boardresult_platformPosTbl[4 - i],
                                             &boardresult_platformMdlTbl[i]->coords, 60));
        obj = omAddObj(0x3FFF, 0, 0, -1, boardresult_PlatformSlideObjMain);
        obj->work[1] = i;
        obj->work[2] = 60;
        HuPrcSleep(10);
    }
    HuPrcSleep(40);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostPos,
                                                            &boardresult_hostMdl->coords, 60));
    obj = omAddObj(0x3FFF, 0, 0, -1, boardresult_HostSlideObjMain);
    obj->work[2] = 60;
    MBDMotionSet(boardresult_hostMdl, 0, 2);
    Hu3DParticleAttrSet(effect, 0, 1);
    i = 0;
    while (1) {
        EffectPosSet(effect, boardresult_hostMdl->coords.x, boardresult_hostMdl->coords.y + 100.0f,
                           boardresult_hostMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
        if (++i == 8) {
            HuAudFXPlay(0x172);
        }
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    rotObj->work[0] = 1;
    MBDMotionSet(boardresult_hostMdl, 1, 0);
    HuPrcSleep(22);
    boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[0]);
    MBDMotionEndShiftSet(boardresult_hostMdl, -1, 2);
    HuAudFXPlay(0x2A8);
    HuPrcSleep(10);
    for (i = 0; i < 4; i++) {
        process = omAddPrcObj(boardresult_PlayerLandProc, 0x1000, 0, 0x40);
        process->user_data = HuMemMemoryAlloc(process->heap, 0x20);
        *(s32 *)process->user_data = i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(10);
    }
    HuPrcChildWatch();

    MBDDlgWinExecAllKey(-1, 0x1400);
    HuAudFXPlay(0x16B);
    actor = MBDModelCreate(0x1D, NULL);
    HuVecCopy3F(&actor->coords, &boardresult_iconStartPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDModelSpinCreate(actor, 0, 20.0f, 30));
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&actor->coords, &boardresult_iconEndPos, &actor->coords, 30));
    EffectParamSet(effect, 15.0f, 30.0f, 10.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    while (1) {
        EffectPosSet(effect, actor->coords.x, actor->coords.y, actor->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    MBDModelKill(actor);
    boardresult_StarNumCreate();
    MBDPlayerKeyWaitAll();
    boardresult_StarNumKill();

    MBDDlgWinExecAllKey(-1, 0x1401);
    HuAudFXPlay(0x16C);
    actor = MBDModelCreate(0x1A, NULL);
    HuVecCopy3F(&actor->coords, &boardresult_iconStartPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDModelSpinCreate(actor, 0, 20.0f, 30));
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&actor->coords, &boardresult_iconEndPos, &actor->coords, 30));
    EffectParamSet(effect, 15.0f, 30.0f, 10.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    while (1) {
        EffectPosSet(effect, actor->coords.x, actor->coords.y, actor->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    MBDModelKill(actor);
    boardresult_CoinNumCreate();
    MBDPlayerKeyWaitAll();
    boardresult_CoinNumKill();

    if (GWBoardFlagCheck(0xF)) {
        boardresult_BonusStarExec(effect);
    } else {
        boardresult_ModelAnimSet(boardresult_hostMdl->omObj1->model[0], boardresult_hostAnimTbl[1]);
        MBDDlgWinExecAllKey(-1, 0x1412);
    }

    // Determine rankings
    for (j = 0; j < 4; j++) {
        values[j] = GwPlayer[j].star * 1000 + GwPlayer[j].coin;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0, n = 0; j < 4; j++) {
            if (i != j) {
                n += values[i] < values[j];
            }
        }
        rank[i] = n;
    }
    for (i = 0; i < 4; i++) {
        values[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        values[rank[i]]++;
    }

    // Break ties
    for (i = 0; i < 4; i++) {
        if (values[i] < 2) {
            continue;
        }
        {
            s32 msgs[] = { 0x1413, 0x1414, 0x1415 };

            for (j = 0, n = 0; j < 4; j++) {
                if (rank[j] == i) {
                    chars[n] = mbKSuitObj[GwPlayer[j].chr];
                    n++;
                }
            }
            for (j = n; j < 4; j++) {
                chars[j] = 0;
            }
            MBDDlgWinInsertCreateAllKey(-1, msgs[n - 2], chars[0], chars[1], chars[2], chars[3], 0);
        }
        MBDDlgWinMesWaitAllKey();
        MBDDlgWinMesWaitAllKey();
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBDSaiInit();
        MBDSaiValueClear();
        for (j = 0, k = 0; j < 4; j++) {
            if (rank[j] == i) {
                if (k != 0) {
                    mbSaiSeF = 0;
                }
                MBDSaiCreate(j);
                MBDSaiNumSprCreate(j);
                k++;
                state[j] = 1;
            } else {
                state[j] = 0;
            }
            count[j] = 0;
            work[j] = (u8)(rand8() % 30) + 5;
        }
        MBDSaiOrderModeSet();
        HuPrcSleep(20);
        while (1) {
            for (j = 0; j < 4; j++) {
                work[j]--;
                switch (state[j]) {
                    case 1:
                        if ((GwPlayer[j].stat & PLAYER_IS_CPU) ? work[j] <= 0
                                                               : (ContBtnDown[GwPlayer[j].pad] & A_BUTTON)) {
                            state[j] = 2;
                            MBDMotionSet(GwPlayer[j].player_obj, 3, 0);
                            MBDMotionEndShiftSet(GwPlayer[j].player_obj, -1, 2);
                        }
                        break;
                    case 2:
                        count[j]++;
                        if (count[j] == 5) {
                            MBDSaiHit(j);
                            state[j] = 0;
                        }
                        break;
                }
            }
            for (j = 0; j < 4; j++) {
                if (state[j] != 0) {
                    break;
                }
            }
            if (j == 4) {
                break;
            }
            HuPrcVSleep();
        }
        HuPrcSleep(20);
        for (j = 0; j < 4; j++) {
            state[j] = MBDSaiValueGet(j);
            order[j] = j;
        }
        for (n = 0; n < 4; n++) {
            for (j = n; j < 4; j++) {
                if (state[n] < state[j]) {
                    work[0] = state[n];
                    state[n] = state[j];
                    state[j] = work[0];
                    work[0] = order[n];
                    order[n] = order[j];
                    order[j] = work[0];
                }
            }
        }
        chars[0] = mbKSuitObj[GwPlayer[order[0]].chr];
        if (values[i] == 2 || values[i] == 4) {
            rank[order[1]] = i + 1;
            if (values[i] == 4) {
                rank[order[2]] = i + 2;
                rank[order[3]] = i + 3;
            }
        } else {
            for (j = 0; j < 3; j++) {
                rank[order[j]] = i + j;
            }
        }
        MBDDlgWinInsertCreateAllKey(-1, 0x1416, chars[0], 0, 0, 0, 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBDSaiClose();
    }
    for (i = 0; i < 4; i++) {
        kakusiMasuItemHis[rank[i]] = i;
    }

    boardresult_starMdl = MBDModelCreate(0x3B, NULL);
    AuraCreate(boardresult_starMdl->omObj1->model[0]);
    HuVecCopy3F(&boardresult_starMdl->coords, &boardresult_starStartPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_hostMdl->coords, &boardresult_hostExitPos,
                                                            &boardresult_hostMdl->coords, 20));
    HuAudFXPlay(0x16D);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_starMdl->coords, &boardresult_starPos,
                                                            &boardresult_starMdl->coords, 40));
    EffectParamSet(effect, 20.0f, 30.0f, 20.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    EffectRangeSet(effect, 300.0f);
    while (1) {
        EffectPosSet(effect, boardresult_starMdl->coords.x, boardresult_starMdl->coords.y,
                           boardresult_starMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, boardresult_StarHoverObjMain);
    swayObj->rot.y = 30.0f;
    swayObj->rot.z = 10.0f;
    HuAudFXPlay(0x159);
    MBDDlgWinExecAllKey(-1, 0x1417);

    // Fade out the clouds
    state[0] = 0xFF;
    state[1] = 0xBF;
    state[2] = 0x7F;
    for (i = 0; i < 255; i += 10) {
        for (j = 0; j < 3; j++) {
            work[j] = state[j] - i;
            if (work[j] < 0) {
                work[j] = 0;
            }
            Hu3DModelTPLvlSet(boardresult_cloudMdlTbl[j]->omObj1->model[0], work[j]);
        }
        HuPrcVSleep();
    }
    omDelObj(cloudObj);
    for (i = 0; i < 3; i++) {
        MBDModelKill(boardresult_cloudMdlTbl[i]);
    }
    HuPrcVSleep();

    for (i = 0; i < 6; i++) {
        boardresult_cloudMdlTbl[i] = MBDModelFileCreate(0x1301C9, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(boardresult_cloudMdlTbl[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(boardresult_cloudMdlTbl[i]->omObj1->model[0], 255 - i * 32);
        HuVecCopyXYZ(&boardresult_cloudMdlTbl[i]->coords, 0.0f, -5000.0f, 0.0f);
        HuVecCopyXYZ(&boardresult_cloudMdlTbl[i]->scale, 1.0f - i * 0.1f, 1.0f - i * 0.1f, 1.0f - i * 0.1f);
        MBDModelTempAllocFree(boardresult_cloudMdlTbl[i]);
    }
    fallProc = omAddPrcObj(boardresult_CloudPassProc, 0x1000, 0, 0);
    seNo = HuAudFXPlay(0x16E);
    omDelObj(swayObj);
    for (i = 0; i < 4; i++) {
        MBDMotionShiftSet(boardresult_gwPlayerTbl[i]->player_obj, 6, 0, 5, 2);
        MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[i]->player_obj->coords, &boardresult_playerLowPosTbl[i],
                              &boardresult_gwPlayerTbl[i]->player_obj->coords, 20);
        MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - i]->coords, &boardresult_playerLowPosTbl[i],
                              &boardresult_platformMdlTbl[3 - i]->coords, 20);
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&boardresult_starMdl->coords, &boardresult_starRisePos,
                                                            &boardresult_starMdl->coords, 20));
    while (1) {
        EffectPosSet(effect, boardresult_starMdl->coords.x, boardresult_starMdl->coords.y,
                           boardresult_starMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, boardresult_StarHoverObjMain);
    swayObj->rot.y = 30.0f;
    swayObj->rot.z = 10.0f;

    // Shuffle the players, revealing them from last to first place
    for (i = 0; i < 4; i++) {
        count[i] = 2;
    }
    for (j = 0;; j++) {
        MBDArrayShuffle(state, 3);
        for (i = 0; i < 4; i++) {
            if (count[state[i]] == 2) {
                if ((j == 10 && kakusiMasuItemHis[3] == state[i]) || (j == 20 && kakusiMasuItemHis[2] == state[i]) ||
                    (j == 30 && kakusiMasuItemHis[1] == state[i])) {
                    count[state[i]] = 1;
                    boardresult_gwPlayerTbl[state[i]]->player_obj->coords.y +=
                        heights.heights[GwPlayer[state[i]].chr] - 80.0f;
                    seNo = PlayerFXPlay(0x2AB, state[i]);
                    MBDMotionSet(boardresult_gwPlayerTbl[state[i]]->player_obj, 4, 2);
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - state[i]]->coords,
                                                         &boardresult_playerDropPosTbl[state[i]],
                                                         &boardresult_platformMdlTbl[3 - state[i]]->coords, 20));
                } else {
                    n = 10 - j / 8;
                    if (n <= 0) {
                        n = 1;
                    }
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[state[i]]->player_obj->coords,
                                                         &boardresult_shufflePosTbl[i * 4 + state[i]],
                                                         &boardresult_gwPlayerTbl[state[i]]->player_obj->coords, n));
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - state[i]]->coords,
                                                         &boardresult_shufflePosTbl[i * 4 + state[i]],
                                                         &boardresult_platformMdlTbl[3 - state[i]]->coords, n));
                }
            } else if (count[state[i]] == 1) {
                if ((j == 12 && kakusiMasuItemHis[3] == state[i]) || (j == 22 && kakusiMasuItemHis[2] == state[i]) ||
                    (j == 32 && kakusiMasuItemHis[1] == state[i])) {
                    count[state[i]] = 0;
                    HuAudFXStop(seNo);
                    PlayerFXPlay(0x286, state[i]);
                    HuPrcChildLink(HuPrcCurrentGet(),
                                   MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[state[i]]->player_obj->coords,
                                                         &boardresult_playerDropPosTbl[state[i]],
                                                         &boardresult_gwPlayerTbl[state[i]]->player_obj->coords, 10));
                    swayObj->rot.y += 40.0f;
                    boardresult_cloudSpeed += 30.0f;
                }
            }
        }
        HuPrcChildWatch();
        if (j == 32) {
            break;
        }
    }

    MBDDlgWinInsertCreateAllKey(-1, 0x1418, mbKSuitObj[GwPlayer[kakusiMasuItemHis[0]].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    MBDMotionShiftSet(boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, -1, 0, 10, 2);
    boardresult_cloudHideF = 1;
    while (boardresult_cloudSpeed > 50.0f) {
        boardresult_cloudSpeed -= 6.0f;
        swayObj->rot.y -= 10.0f;
        HuPrcVSleep();
    }
    msmSeFadeOut(60);
    for (i = 0; !boardresult_CloudPassDoneCheck(); i++) {
        boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        boardresult_platformMdlTbl[3 - kakusiMasuItemHis[0]]->coords.y += 2.0f;
        if (i == 60) {
            Hu3DParticleAttrSet(effect, 1, 0);
            MBDPlayerPosMoveCreate(&boardresult_starMdl->coords, &boardresult_starExitPos,
                                  &boardresult_starMdl->coords, 30);
        }
        HuPrcVSleep();
    }
    for (; i < 90; i++) {
        boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        boardresult_platformMdlTbl[3 - kakusiMasuItemHis[0]]->coords.y += 2.0f;
        if (i == 60) {
            Hu3DParticleAttrSet(effect, 1, 0);
            MBDPlayerPosMoveCreate(&boardresult_starMdl->coords, &boardresult_starExitPos,
                                  &boardresult_starMdl->coords, 30);
        }
        HuPrcVSleep();
    }

    MBDCameraNearFarSet(100.0f, 20000.0f);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords,
                                         &boardresult_winnerPosTbl[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords, 20));
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&boardresult_platformMdlTbl[3 - kakusiMasuItemHis[0]]->coords,
                                         &boardresult_winnerPosTbl[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &boardresult_platformMdlTbl[3 - kakusiMasuItemHis[0]]->coords, 20));
    HuPrcChildWatch();
    for (i = 0; i < 4; i++) {
        if (i != kakusiMasuItemHis[0]) {
            MBDPlayerModelKill(i);
            MBDModelKill(boardresult_platformMdlTbl[3 - i]);
        }
    }
    AuraKill(boardresult_starMdl->omObj1->model[0]);
    MBDModelKill(boardresult_starMdl);
    MBDModelKill(boardresult_hostMdl);
    HuWinAllKill();
    boardresult_winClosedF = 1;
    EffectStop(effect);
    omDelPrcObj(fallProc);
    for (i = 0; i < 6; i++) {
        MBDModelKill(boardresult_cloudMdlTbl[i]);
    }
    HuPrcSleep(5);
    omAddPrcObj(boardresult_FireworkShowProc, 0x1000, 0, 0);
    HuPrcSleep(1);

    HuAudFXPlay(GwPlayer[kakusiMasuItemHis[0]].chr + 0x27E);
    CharAnimSet(boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->omObj1->model[0], 2,
                       GwPlayer[kakusiMasuItemHis[0]].chr, boardresult_playerAnimTbl[kakusiMasuItemHis[0]][1]);
    MBDMotionSet(boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, 2, 0);
    MBDModelMotionWait(boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj);
    HuAudFXPlay(0x177);
    MBDMotionSet(boardresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, 5, 2);
    group = MBDSprGrpCreate(1, 0);
    data = DataRead(0x1301C6);
    group->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(group->unk_0A, 0, group->unk_0C[0], 0);
    HuSprPriSet(group->unk_0A, 0, 1);
    HuSprAttrSet(group->unk_0A, 0, HUSPR_ATTR_NONE);
    HuSprPosSet(group->unk_0A, 0, 160, 184);
    HuPrcSleep(30);

    // Wait for a human player to press a button
    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            break;
        }
    }
    if (i != 4) {
        while (1) {
            for (i = 0; i < 4; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU) &&
                    (ContBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON | START_BUTTON))) {
                    break;
                }
            }
            if (i != 4) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        HuPrcSleep(30);
    }
}

void boardresult_MainProc(void) {
    boardresult_IntroExec();
    boardresult_ResultExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void boardresult_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        boardresult_BackClose();
        boardresult_SysClose();
        if (boardresult_winClosedF == 0) {
            HuWinAllKill();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0)) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x16);
            SLSaveBoard(1);
        } else {
            SLCommonSet(1);
        }
        omOvlGotoEx(boardresult2, 0, 0x4190);
    }
}

void boardresult_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(WIPE_STARS, 20);
        msmSeFadeOut(40);
        obj->func = boardresult_ExitObjMain;
    }
}

void boardresult_SysInit(void) {
    MBDModelInit();
    MBDPlayerMotInit();
    MBDMotShiftInit();
    MBDSprGrpInit();
}

void boardresult_SysClose(void) {
    MBDSprGrpClose();
    MBDMotShiftClose();
    MBDPlayerClose();
    MBDModelClose();
}

void boardresult_BackInit(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackLoad(0);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
}

void boardresult_BackClose(void) {
    MBDBackKill();
    MBDBackClose();
}
