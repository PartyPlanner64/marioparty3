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

typedef struct DuelResultWork DuelResultWork;

typedef struct DuelResultSprFiles {
    s32 files[4];
} DuelResultSprFiles;

typedef struct DuelResultSprPositions {
    f32 pos[4][2];
} DuelResultSprPositions;

typedef struct DuelResultCharMotions {
    s32 motions[8];
} DuelResultCharMotions;

typedef struct DuelResultCharActors {
    s32 ids[8];
} DuelResultCharActors;

typedef struct DuelResultCharHeights {
    f32 heights[8];
} DuelResultCharHeights;

extern const DuelResultCharMotions duelresult_chrAnimTbl;
extern const DuelResultCharMotions duelresult_chrWinAnimTbl;
extern const DuelResultCharActors duelresult_cheerMdlNoTbl;
extern s16 kakusiMasuItemHis[10]; // Reused after board play to hold player indices by final rank
extern s32 mbKSuitObj[];

void duelresult_IntroExec(void);
DuelResultWork *duelresult_FireworkCreate(s32);
void duelresult_FireworkSprSet(DuelResultWork *, s32);
void duelresult_FireworkFlagSet(DuelResultWork *, s32, s32);
s16 duelresult_FireworkFlagGet(DuelResultWork *);
void duelresult_FireworkBurstTimeSet(DuelResultWork *, s16);
void duelresult_FireworkEndPosSet(DuelResultWork *, f32, f32, f32);
void duelresult_FireworkStartPosSet(DuelResultWork *, f32, f32, f32);
void duelresult_FireworkTimeSet(DuelResultWork *, s16);
void duelresult_ResultExec(void);
void duelresult_MainProc(void);
void duelresult_ExitObjMain(omObjData *);
void duelresult_ExitCheckObjMain(omObjData *);
void duelresult_SysInit(void);
void duelresult_BackInit(void);
void duelresult_SysClose(void);
void duelresult_BackClose(void);
void MBDPlayerModelCreate(s16, s32 *, s16);
void MBDPlayerModelKill(s16);
void MBDDlgWinExecAllKey(s32, s32);
void MBDMotionEndShiftSet(Object *, s32, s32);
void MBDPlayerKeyWait(void);

s32 duelresult_winClosedF = 0;

Vec duelresult_iconStartPos = { -750.0f, 400.0f, 2000.0f };

Vec duelresult_iconEndPos = { 750.0f, 400.0f, 2000.0f };

Vec duelresult_hostStartPos = { -750.0f, 500.0f, 4000.0f };

Vec duelresult_hostPos = { -250.0f, 0.0f, 2500.0f };

Vec duelresult_hostAsidePos = { -250.0f, -400.0f, 2500.0f }; /* Unreferenced. */

Vec duelresult_hostExitPos = { -500.0f, 400.0f, 3500.0f };

Vec duelresult_platformPosTbl[3] = {
    { 750.0f, 250.0f, 4000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f }
};

Vec duelresult_cloudPosTbl[3] = {
    { 0.0f, -700.0f, 1500.0f },
    { 0.0f, -500.0f, 1000.0f },
    { 0.0f, -300.0f, 500.0f }
};

Vec duelresult_introStarPos = { -200.0f, 400.0f, -150.0f };

Vec duelresult_starStartPos = { 0.0f, 750.0f, 2500.0f };

Vec duelresult_starPos = { 0.0f, 250.0f, 2500.0f };

Vec duelresult_starRisePos = { 0.0f, 400.0f, 2500.0f };

Vec duelresult_starExitPos = { 0.0f, 1000.0f, 2500.0f };

Vec duelresult_starDropPos = { 0.0f, 100.0f, 2500.0f };

Vec duelresult_introPlayerPos = { 500.0f, 50.0f, 500.0f };

Vec duelresult_playerPosTbl[16] = {
    { -150.0f, 750.0f, 2000.0f },
    { 150.0f, 750.0f, 2000.0f },
    { -150.0f, 250.0f, 2000.0f },
    { 150.0f, 250.0f, 2000.0f },
    { -150.0f, 100.0f, 2000.0f },
    { 150.0f, 100.0f, 2000.0f },
    { -150.0f, 0.0f, 2000.0f },
    { 150.0f, 0.0f, 2000.0f },
    { -150.0f, -500.0f, 2000.0f },
    { 150.0f, -500.0f, 2000.0f },
    { -150.0f, 800.0f, 2000.0f },
    { 150.0f, 800.0f, 2000.0f },
    { -150.0f, 150.0f, 2000.0f },
    { 150.0f, 150.0f, 2000.0f },
    { -150.0f, 350.0f, 2000.0f },
    { 150.0f, 350.0f, 2000.0f }
};

Vec duelresult_winnerPosTbl[8] = {
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 270.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f },
    { 0.0f, 240.0f, 3000.0f },
    { 0.0f, 250.0f, 3000.0f },
    { 0.0f, 260.0f, 3000.0f }
};

Vec duelresult_cheerPosTbl[2] = {
    { -750.0f, 150.0f, 1500.0f },
    { 750.0f, 150.0f, 1500.0f }
};

Vec duelresult_cheerEndPosTbl[2] = {
    { -225.0f, 150.0f, 2500.0f },
    { 225.0f, 150.0f, 2500.0f }
};

s32 duelresult_introMotMario[3] = { 2, 0x2001B, 0x20024 };

s32 duelresult_resultMotMario[7] = { 6, 0x2001F, 0x20030, 0x20034, 0x20039, 0x20029, 0x2008F };

s32 duelresult_introMotLuigi[3] = { 2, 0, 0 };

s32 duelresult_resultMotLuigi[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotPeach[3] = { 2, 0, 0 };

s32 duelresult_resultMotPeach[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotYoshi[3] = { 2, 0, 0 };

s32 duelresult_resultMotYoshi[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotWario[3] = { 2, 0, 0 };

s32 duelresult_resultMotWario[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotDk[3] = { 2, 0, 0 };

s32 duelresult_resultMotDk[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotWaluigi[3] = { 2, 0, 0 };

s32 duelresult_resultMotWaluigi[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 duelresult_introMotDaisy[3] = { 2, 0, 0 };

s32 duelresult_resultMotDaisy[7] = { 6, 0, 0, 0, 0, 0, 0 };

s32 *duelresult_introMotTbl[8] = { duelresult_introMotMario, duelresult_introMotLuigi, duelresult_introMotPeach, duelresult_introMotYoshi, duelresult_introMotWario, duelresult_introMotDk, duelresult_introMotWaluigi, duelresult_introMotDaisy };

s32 *duelresult_resultMotTbl[8] = { duelresult_resultMotMario, duelresult_resultMotLuigi, duelresult_resultMotPeach, duelresult_resultMotYoshi, duelresult_resultMotWario, duelresult_resultMotDk, duelresult_resultMotWaluigi, duelresult_resultMotDaisy };

s32 duelresult_introMdlMotTbl[5] = { 0x13015C, 0x13015D, 0x13015E, 0x13015F, 0x130160 };

s32 duelresult_hostMot[3] = { 2, 0xA0077, 0xA0078 };

omObjData *duelresult_numPulseObjTbl[4] = { NULL, NULL, NULL, NULL };

s32 duelresult_cloudHideF = 0;

f32 duelresult_cloudSpeed = 50.0f;

s32 duelresult_cloudHiddenTbl[6] = { 0, 0, 0, 0, 0, 0 };

s32 duelresult_fireworkSprTbl[8] = { 0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045 };

const DuelResultSprFiles duelresult_titleSprFileTbl = { { 0x1301C1, 0x1301C2, 0x1301C3, 0x1301C4 } };

const DuelResultSprPositions duelresult_titleSprLPosTbl = { { { 200.0f, 60.0f },
                                                         { 80.0f, 0.0f },
                                                         { 0.0f, 120.0f },
                                                         { 80.0f, 120.0f } } };

const DuelResultSprPositions duelresult_titleSprRPosTbl = { { { 120.0f, 60.0f },
                                                         { -80.0f, 0.0f },
                                                         { 0.0f, 120.0f },
                                                         { -80.0f, 120.0f } } };

const DuelResultCharHeights duelresult_chrHeightTbl = { { 120.0f, 120.0f, 180.0f, 160.0f, 160.0f, 190.0f, 120.0f, 180.0f } };

u8 duelresult_boardNo BSS;
Object *duelresult_starMdl BSS;
s16 duelresult_playerAnimTbl[4][8] BSS;
GW_PLAYER *duelresult_gwPlayerTbl[2] BSS;
Object *duelresult_cloudMdlTbl[6] BSS;
Object *duelresult_platformMdlTbl[2] BSS;
Object *duelresult_cheerPlatformMdlTbl[2] BSS;
Object *duelresult_cheerMdlTbl[2] BSS;
Object *duelresult_hostMdl BSS;
s16 duelresult_hostAnim BSS;
s16 duelresult_hostAnimLink BSS;
s16 duelresult_hostAnimTbl[12] BSS;
s32 duelresult_numSprGrpTbl[4] BSS;
s32 duelresult_numSprAnim BSS;
Object *duelresult_starNumMdlTbl[2] BSS;
void *duelresult_starNumAnimDataTbl[2] BSS;
s32 duelresult_starNumAnimTbl[3] BSS;
f32 duelresult_cloudSpeedOfsTbl[8] BSS;

void duelresult_ObjectSetup(void) {
    s32 i;
    u32 j;

    duelresult_boardNo = GwSystem.current_board_index;
    omInitObjMan(0x32, 0x32);
    duelresult_BackInit();
    duelresult_SysInit();
    MBDShadowHeightMaxSet(700.0f);
    MBDModelScaleMulSet(1.6f);
    HuWinInit();
    omAddPrcObj(duelresult_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, duelresult_ExitCheckObjMain);

    for (i = 1; i < 8; i++) {
        for (j = 0; j < duelresult_introMotMario[0]; j++) {
            duelresult_introMotTbl[i][j + 1] = CharMotionDataNumGet(i, duelresult_introMotMario[j + 1]);
        }
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < duelresult_resultMotMario[0]; j++) {
            duelresult_resultMotTbl[i][j + 1] = CharMotionDataNumGet(i, duelresult_resultMotMario[j + 1]);
        }
    }
}

void duelresult_StarHoverObjMain(omObjData *obj) {
    duelresult_starMdl->velocity.x = sindf(obj->rot.x) * obj->rot.z;
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void duelresult_IntroExec(void) {
    s16 models[5];
    Vec targets[4];
    UnkBoard4 *groups[2];
    DuelResultSprFiles files = duelresult_titleSprFileTbl;
    DuelResultSprPositions leftPos = duelresult_titleSprLPosTbl;
    DuelResultSprPositions rightPos = duelresult_titleSprRPosTbl;
    DuelResultCharHeights heights = duelresult_chrHeightTbl;
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

    for (i = 0; i < 2; i++) {
        duelresult_gwPlayerTbl[i] = MBDPlayerGet(i);
        MBDPlayerModelCreate(i, duelresult_introMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&duelresult_gwPlayerTbl[i]->player_obj->coords, &duelresult_introPlayerPos);
        duelresult_gwPlayerTbl[i]->player_obj->flags |= 1;
        duelresult_gwPlayerTbl[i]->stat |= 4;
        MBDModelTempAllocFree(duelresult_gwPlayerTbl[i]->player_obj);
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

    duelresult_starMdl = MBDModelCreate(0x3B, 0);
    AuraCreate(duelresult_starMdl->omObj1->model[0]);
    MBDModelTempAllocFree(duelresult_starMdl);
    HuVecCopy3F(&duelresult_starMdl->coords, &duelresult_introStarPos);
    obj = omAddObj(0x1000, 0, 0, -1, duelresult_StarHoverObjMain);
    obj->rot.y = 10.0f;
    obj->rot.z = 20.0f;

    model = Hu3DModelRead(0x13015B, 0x4026A9);
    for (i = 0; i < 5; i++) {
        models[i] = Hu3DModelReadNum(duelresult_introMdlMotTbl[i]);
    }
    Hu3DModelVtxBufMake(model);
    Hu3DModelRotSet(model, 0.0f, -45.0f, 0.0f);
    Hu3DModelScaleSet(model, 1.6f, 1.6f, 1.6f);
    Hu3DMotionModelSetEx(model, models[1]);
    Hu3DMotionAttrSet(model, 2, 1);
    HuPrcSleep(10);

    for (i = 0; i < 2; i++) {
        MBDMotionSet(duelresult_gwPlayerTbl[i]->player_obj, 0, 2);
        HuVecCopyXYZ(&targets[i], 0.0f, 0.0f, 0.0f);
        MBDVecDirGet(&targets[i], &duelresult_gwPlayerTbl[i]->player_obj->coords,
                     &duelresult_gwPlayerTbl[i]->player_obj->rot);
        targets[i].y += heights.heights[GwPlayer[i].chr];
        duelresult_gwPlayerTbl[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[i]->player_obj->coords, &targets[i],
                              &duelresult_gwPlayerTbl[i]->player_obj->coords, 20);
        for (j = 0; j < 20; j++) {
            HuVecCopyXYZ(&duelresult_gwPlayerTbl[i]->player_obj->scale, (20.0f - j) / 40.0f + 0.5f,
                         (20.0f - j) / 40.0f + 0.5f, (20.0f - j) / 40.0f + 0.5f);
            HuPrcVSleep();
            if (j == 18) {
                Hu3DMotionAttrSet(model, 1, 0);
                switch (i) {
                    case 0:
                        HuAudFXPlay(0x164);
                        break;
                    case 1:
                        HuAudFXPlay(0x165);
                        break;
                }
            }
        }
        MBDModelDispOff(duelresult_gwPlayerTbl[i]->player_obj);
        HuPrcSleep(9);
    }

    HuAudFXPlay(0x168);
    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(52);
    Hu3DMotionAttrSet(model, 0, 1);

    Hu3DMotionNoMotSet(duelresult_starMdl->omObj1->model[0],
                       Hu3DData[duelresult_starMdl->omObj1->model[0]].motId, "l_mayu", 76, 71);
    node = Hu3DModelObjPtrGet(duelresult_starMdl->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x174);
    Hu3DMotionNoMotSet(duelresult_starMdl->omObj1->model[0],
                       Hu3DData[duelresult_starMdl->omObj1->model[0]].motId, "hige", 23, 70);
    node = Hu3DModelObjPtrGet(duelresult_starMdl->omObj1->model[0], "hige");
    baseY = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + baseY;
        HuPrcVSleep();
    }
    node->basePos.y = baseY;

    Hu3DMotionAttrSet(model, 3, 0);
    HuPrcSleep(3);
    HuAudFXPlay(0x169);
    for (i = 0; i < 2; i++) {
        PlayerFXPlay(0x286, i);
        MBDMotionSet(duelresult_gwPlayerTbl[i]->player_obj, 1, 2);
        Hu3DMotionAttrSet(duelresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, 1);
        HuVecCopyXYZ(&duelresult_gwPlayerTbl[i]->player_obj->coords, 0.0f, 150.0f, 0.0f);
        HuVecCopy3F(&targets[i], &duelresult_introPlayerPos);
        targets[i].y += 400.0f;
        HuMtxRotXF(Hu3DData[duelresult_gwPlayerTbl[i]->player_obj->omObj1->model[0]].mtx, -30.0f);
        MBDModelDispOn(duelresult_gwPlayerTbl[i]->player_obj);
        MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[i]->player_obj->coords, &targets[i],
                              &duelresult_gwPlayerTbl[i]->player_obj->coords, 5);
        HuAudFXPlay(0x16A);
        for (j = 5; j > 0; j--) {
            HuVecCopyXYZ(&duelresult_gwPlayerTbl[i]->player_obj->scale, (5.0f - j) / 10.0f + 0.5f,
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
    AuraKill(duelresult_starMdl->omObj1->model[0]);
    MBDModelKill(duelresult_starMdl);
    for (i = 0; i < 2; i++) {
        MBDPlayerModelKill(i);
    }
}

s16 duelresult_ModelAnimCreate(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    duelresult_hostAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    duelresult_hostAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void duelresult_ModelAnimSet(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (duelresult_hostAnimLink != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[duelresult_hostAnimLink];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 duelresult_AnimDataRead(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void duelresult_CloudScrollObjMain(omObjData *obj) {
    Hu3DModelObjTexScroll(duelresult_cloudMdlTbl[0]->omObj1->model[0], obj->trans.x, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(duelresult_cloudMdlTbl[1]->omObj1->model[0], obj->trans.y, 0, 0x40, 0x2B, "kumo-endkumo", 0);
    Hu3DModelObjTexScroll(duelresult_cloudMdlTbl[2]->omObj1->model[0], obj->trans.z, 0, 0x40, 0x2B, "kumo-endkumo", 0);

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

void duelresult_PlatformSwayObjMain(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        duelresult_platformMdlTbl[i]->rot.x = sindf(obj->rot.x);
        duelresult_platformMdlTbl[i]->rot.z = cosdf(obj->rot.x);
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

void duelresult_PlatformSlideObjMain(omObjData *obj) {
    Object *target = duelresult_platformMdlTbl[obj->work[1]];

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * -700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void duelresult_HostSlideObjMain(omObjData *obj) {
    Object *target = duelresult_hostMdl;

    obj->work[0]++;
    target->coords.x += sindf(obj->work[0] * 180.0f / obj->work[2]) * 700.0f;
    target->coords.y += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    target->coords.z += sindf(obj->work[0] * 180.0f / obj->work[2]) * 0.0f;
    if (obj->work[0] == obj->work[2]) {
        omDelObj(obj);
    }
}

void duelresult_PlayerLandProc(void) {
    s32 index;
    Process *process;
    f32 angle;
    s32 offset;

    index = *(s32 *)HuPrcCurrentGet()->user_data;
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[index]->player_obj->coords,
                                                  &duelresult_playerPosTbl[index + 2],
                                                  &duelresult_gwPlayerTbl[index]->player_obj->coords, 10));
    MBDMotionSet(duelresult_gwPlayerTbl[index]->player_obj, 0, 0);

    for (angle = 90.0f; angle > 0.0f; angle -= 9.0f) {
        OBJ_MODEL_ROT_X(duelresult_platformMdlTbl[1 - index], angle);
        HuPrcVSleep();
    }
    OBJ_MODEL_ROT_X(duelresult_platformMdlTbl[1 - index], 0.0f);

    HuAudFXPlay(0x175);
    for (offset = 0, angle = 30.0f; angle <= 180.0f; angle += 10.0f) {
        HuVecCopyXYZ(&duelresult_gwPlayerTbl[index]->player_obj->coords, duelresult_playerPosTbl[index + 2].x,
                     duelresult_playerPosTbl[index + 2].y - sindf(angle) * 100.0f + offset,
                     duelresult_playerPosTbl[index + 2].z);
        HuVecCopyXYZ(&duelresult_platformMdlTbl[1 - index]->coords, duelresult_playerPosTbl[index + 2].x,
                     duelresult_playerPosTbl[index + 2].y - sindf(angle) * 100.0f + offset,
                     duelresult_playerPosTbl[index + 2].z);
        offset -= 10;
        HuPrcVSleep();
    }
    MBDMotionSet(duelresult_gwPlayerTbl[index]->player_obj, -1, 2);
    omDelPrcObj(NULL);
}

void duelresult_NumPulseObjMain(omObjData *obj) {
    f32 scale;
    u32 i;

    scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.3f + 1.0;
    for (i = 0; i < obj->work[1]; i++) {
        HuSprScaleSet(duelresult_numSprGrpTbl[obj->work[0]], i, scale, scale);
    }

    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void duelresult_CoinNumCreate(void) {
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 coin;
    s32 digits[3];
    Vec pos3d;
    Vec2f pos2d;

    data = DataRead(0x1301C5);
    duelresult_numSprAnim = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 2; i++) {
        duelresult_numSprGrpTbl[i] = HuSprGrpCreate(3, 5);
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
            HuSprGrpMemberSet(duelresult_numSprGrpTbl[i], j, duelresult_numSprAnim, 0);
            HuSprAnimModeSet(duelresult_numSprGrpTbl[i], j, HUSPR_ANIM_MODE_BANK);
            HuSprBankSet(duelresult_numSprGrpTbl[i], j, digits[j], 0);
            HuSprPriSet(duelresult_numSprGrpTbl[i], j, 0x4790);
            HuSprAttrSet(duelresult_numSprGrpTbl[i], j, HUSPR_ATTR_XLU);
            HuSprColorSet(duelresult_numSprGrpTbl[i], j, 0xFF, 0xFF, 0);
            if (j == 0) {
                pos3d.x = GwPlayer[i].player_obj->coords.x;
                pos3d.y = GwPlayer[i].player_obj->coords.y + 280.0f;
                pos3d.z = GwPlayer[i].player_obj->coords.z;
                MBDCamera3Dto2D(&pos3d, &pos2d);
                HuSprPosSet(duelresult_numSprGrpTbl[i], 0, pos2d.x - (count - 1) * 7, pos2d.y);
            } else {
                HuSprPosSet(duelresult_numSprGrpTbl[i], j, j * 14, 0);
            }
        }

        coin = GwPlayer[i].coin;
        for (j = 0; j < 4; j++) {
            if (j != i && coin < GwPlayer[j].coin) {
                coin = GwPlayer[j].coin;
            }
        }
        if (coin == GwPlayer[i].coin) {
            duelresult_numPulseObjTbl[i] = omAddObj(0x1000, 0, 0, -1, duelresult_NumPulseObjMain);
            duelresult_numPulseObjTbl[i]->work[0] = i;
            duelresult_numPulseObjTbl[i]->work[1] = count;
            duelresult_numPulseObjTbl[i]->rot.x = 0.0f;
        }
    }
}

void duelresult_CoinNumKill(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (duelresult_numPulseObjTbl[i] != NULL) {
            omDelObj(duelresult_numPulseObjTbl[i]);
            duelresult_numPulseObjTbl[i] = NULL;
        }
        HuSprGrpKill(duelresult_numSprGrpTbl[i]);
    }
    HuSprAnimKill(duelresult_numSprAnim);
    HuPrcVSleep();
}

void duelresult_StarNumPulseObjMain(omObjData *obj) {
    f32 scale = sinf(obj->rot.x * (M_PI / 180.0)) * 0.2f + 0.5;

    HuVecCopyXYZ(&duelresult_starNumMdlTbl[obj->work[0]]->scale, scale, scale, scale);
    obj->rot.x += 30.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void duelresult_StarNumCreate(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        duelresult_starNumMdlTbl[i] = MBDModelFileCreate(0x14000A, -1, 1.0f, 0.0f, NULL);
        if (GwPlayer[i].star == 0) {
            duelresult_starNumAnimDataTbl[i] = DataRead(0x130135);
            duelresult_starNumAnimTbl[i] = (s16)Hu3DAnimCreate(
                Hu3DData[duelresult_starNumMdlTbl[i]->omObj1->model[0]].hmf, duelresult_starNumAnimDataTbl[i], 0, "sitagocoro_DEF");
        } else {
            duelresult_starNumAnimDataTbl[i] = DataRead(0x140034);
            duelresult_starNumAnimTbl[i] =
                (s16)Hu3DAnimCreate(Hu3DData[duelresult_starNumMdlTbl[i]->omObj1->model[0]].hmf,
                                    duelresult_starNumAnimDataTbl[i], GwPlayer[i].star - 1, "sitagocoro_DEF");
        }
        Hu3DModelRemakeStatic(duelresult_starNumMdlTbl[i]->omObj1->model[0]);
        HuVecCopy3F(&duelresult_starNumMdlTbl[i]->coords, &GwPlayer[i].player_obj->coords);
        duelresult_starNumMdlTbl[i]->velocity.x = 280.0f;
        HuVecCopyXYZ(&duelresult_starNumMdlTbl[i]->scale, 0.5f, 0.5f, 0.5f);
    }

    if (GwPlayer[0].star > GwPlayer[1].star) {
        duelresult_numPulseObjTbl[0] = omAddObj(0x1000, 0, 0, -1, duelresult_StarNumPulseObjMain);
        duelresult_numPulseObjTbl[0]->work[0] = 0;
    } else if (GwPlayer[1].star > GwPlayer[0].star) {
        duelresult_numPulseObjTbl[0] = omAddObj(0x1000, 0, 0, -1, duelresult_StarNumPulseObjMain);
        duelresult_numPulseObjTbl[0]->work[0] = 1;
    }
}

void duelresult_StarNumKill(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        Hu3DAnimModelKill(duelresult_starNumAnimTbl[i]);
        DataClose(duelresult_starNumAnimDataTbl[i]);
        MBDModelKill(duelresult_starNumMdlTbl[i]);
        if (duelresult_numPulseObjTbl[i] != NULL) {
            omDelObj(duelresult_numPulseObjTbl[i]);
            duelresult_numPulseObjTbl[i] = NULL;
        }
    }
    HuPrcVSleep();
}

void duelresult_CloudPassProc(void) {
    s32 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            HuVecCopyXYZ(&duelresult_cloudMdlTbl[i]->coords, duelresult_cloudMdlTbl[i]->coords.x,
                         duelresult_cloudMdlTbl[i]->coords.y + (duelresult_cloudSpeed + duelresult_cloudSpeedOfsTbl[i]),
                         duelresult_cloudMdlTbl[i]->coords.z);
            if (duelresult_cloudMdlTbl[i]->coords.y >= 1000.0f) {
                HuVecCopyXYZ(&duelresult_cloudMdlTbl[i]->coords, (MBDRand(300.0f) - 150) * 5.0f,
                             -(MBDRand(200.0f) + 250) * 5.0f, (300 - i * 50) * 5.0f);
                duelresult_cloudSpeedOfsTbl[i] =
                    MBDRand(duelresult_cloudSpeed / 2.0f) - duelresult_cloudSpeed / 4.0f;
                if (duelresult_cloudHideF) {
                    MBDModelDispOff(duelresult_cloudMdlTbl[i]);
                    duelresult_cloudHiddenTbl[i] = 1;
                }
            }
        }
        HuPrcVSleep();
    }
}

s32 duelresult_CloudPassDoneCheck(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (duelresult_cloudHiddenTbl[i] == 0) {
            break;
        }
    }
    return i == 6;
}

void duelresult_FireworkRandSet(DuelResultWork *work, s32 index) {
    s32 x, y, z;

    x = MBDRand(256.0f) - 128;
    y = -MBDRand(256.0f) - 500;
    duelresult_FireworkStartPosSet(work, x, y, 0.0f);
    x = MBDRand(100.0f) + index * 500 - 550;
    y = MBDRand(64.0f) + 218;
    z = MBDRand(500.0f) - 500;
    duelresult_FireworkEndPosSet(work, x, y, z);
    duelresult_FireworkTimeSet(work, MBDRand(60.0f) + 30);
}

void duelresult_FireworkShowProc(void) {
    DuelResultWork *works[3];
    s32 i;
    s32 count;

    for (i = 0; i < 3; i++) {
        works[i] = duelresult_FireworkCreate(duelresult_fireworkSprTbl[GwPlayer[kakusiMasuItemHis[0]].chr]);
        duelresult_FireworkRandSet(works[i], i);
        duelresult_FireworkFlagSet(works[i], 2, 2);
    }

    while (1) {
        for (i = 0; i < 3; i++) {
            if ((duelresult_FireworkFlagGet(works[i]) & 1) && rand8() < 0x20) {
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        duelresult_FireworkFlagSet(works[i], 2, 0);
                        count += duelresult_FireworkFlagGet(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                duelresult_FireworkRandSet(works[0], 0);
                duelresult_FireworkEndPosSet(works[0], 0.0f, 250.0f, 1500.0f);
                duelresult_FireworkFlagSet(works[0], 1, 0);
                duelresult_FireworkSprSet(works[0], 0xB0046);
                duelresult_FireworkBurstTimeSet(works[0], 120);
                while (1) {
                    for (i = 0, count = 0; i < 3; i++) {
                        duelresult_FireworkFlagSet(works[i], 2, 0);
                        count += duelresult_FireworkFlagGet(works[i]) & 1;
                    }
                    if (count >= 3) {
                        break;
                    }
                    HuPrcVSleep();
                }
                for (i = 0; i < 3; i++) {
                    duelresult_FireworkFlagSet(works[i], 3, 2);
                    duelresult_FireworkSprSet(works[i], duelresult_fireworkSprTbl[GwPlayer[kakusiMasuItemHis[0]].chr]);
                }
                duelresult_FireworkBurstTimeSet(works[0], 60);
                duelresult_FireworkRandSet(works[0], 0);
                break;
            }
            duelresult_FireworkRandSet(works[i], i);
        }
        HuPrcVSleep();
    }
}

const DuelResultCharMotions duelresult_chrAnimTbl = { { 0x200A4, 0x300A4, 0x700A4, 0x400A4, 0x500A4, 0x600A4, 0x800A4, 0x9001B } };

const DuelResultCharMotions duelresult_chrWinAnimTbl = { { 0x200AB, 0x300AB, 0x700AB, 0x400AB, 0x500AB, 0x600AB, 0x800AB, 0x90027 } };

void duelresult_ResultExec(void) {
    s32 values[4];
    s32 rank[4];
    u8 state[8];
    s32 work[4];
    DuelResultCharHeights heights = duelresult_chrHeightTbl;
    DuelResultCharMotions motions;
    DuelResultCharMotions winMotions;
    DuelResultCharActors actors;
    omObjData *cloudObj;
    omObjData *rotObj;
    omObjData *swayObj;
    omObjData *obj;
    Object *actor;
    Object *star;
    Process *process;
    s16 effect;
    Process *fallProc;
    UnkBoard4 *group;
    void *data;
    s32 i;
    s32 j;
    s32 n;

    MBDBackKill();
    MBDBackLoad(1);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
    for (i = 0; i < 2; i++) {
        duelresult_gwPlayerTbl[i] = MBDPlayerGet(i);
        MBDPlayerModelCreate(i, duelresult_resultMotTbl[GwPlayer[i].chr], 2);
        duelresult_gwPlayerTbl[i]->player_obj->flags |= 1;
        duelresult_gwPlayerTbl[i]->stat |= 4;
        motions = duelresult_chrAnimTbl;
        winMotions = duelresult_chrWinAnimTbl;
        duelresult_playerAnimTbl[i][0] =
            CharAnimCreate(duelresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                               motions.motions[GwPlayer[i].chr]);
        duelresult_playerAnimTbl[i][1] = Hu3DAnimDataRead(winMotions.motions[GwPlayer[i].chr]);
        CharAnimSet(duelresult_gwPlayerTbl[i]->player_obj->omObj1->model[0], 2, GwPlayer[i].chr,
                           duelresult_playerAnimTbl[i][0]);
        MBDModelTempAllocFree(duelresult_gwPlayerTbl[i]->player_obj);
    }

    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&duelresult_gwPlayerTbl[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
        HuVecCopy3F(&duelresult_gwPlayerTbl[i]->player_obj->coords, &duelresult_playerPosTbl[i]);
        MBDVecForwardSet(&duelresult_gwPlayerTbl[i]->player_obj->rot);
        HuMtxRotXF(Hu3DData[duelresult_gwPlayerTbl[i]->player_obj->omObj1->model[0]].mtx, 0.0f);
    }

    for (i = 0; i < 3; i++) {
        duelresult_cloudMdlTbl[i] = MBDModelFileCreate(0x1301C7, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(duelresult_cloudMdlTbl[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(duelresult_cloudMdlTbl[i]->omObj1->model[0], 255 - i * 64);
        HuVecCopy3F(&duelresult_cloudMdlTbl[i]->coords, &duelresult_cloudPosTbl[i]);
        Hu3DModelVtxBufMake(duelresult_cloudMdlTbl[i]->omObj1->model[0]);
        HuVecCopyXYZ(&duelresult_cloudMdlTbl[i]->scale, 1.0f - i * 0.2f, 1.0f - i * 0.2f, 1.0f - i * 0.2f);
        MBDModelTempAllocFree(duelresult_cloudMdlTbl[i]);
    }
    cloudObj = omAddObj(0x1000, 0, 0, -1, duelresult_CloudScrollObjMain);

    for (i = 0; i < 2; i++) {
        duelresult_platformMdlTbl[i] = MBDModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, 0);
        HuVecCopy3F(&duelresult_platformMdlTbl[i]->coords, &duelresult_platformPosTbl[0]);
        HuVecCopyXYZ(&duelresult_platformMdlTbl[i]->scale, 0.625f, 0.625f, 0.625f);
        OBJ_MODEL_ROT_X(duelresult_platformMdlTbl[i], 90.0f);
        MBDModelTempAllocFree(duelresult_platformMdlTbl[i]);
    }
    rotObj = omAddObj(0x1000, 0, 0, -1, duelresult_PlatformSwayObjMain);

    duelresult_hostMdl = MBDModelCreate(0x3E, duelresult_hostMot);
    duelresult_hostMdl->flags |= 1;
    HuVecCopy3F(&duelresult_hostMdl->coords, &duelresult_hostStartPos);
    duelresult_hostMdl->rot.x = sindf(10.0f);
    duelresult_hostMdl->rot.z = cosdf(10.0f);
    duelresult_hostAnimTbl[0] =
        duelresult_ModelAnimCreate(duelresult_hostMdl->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    duelresult_hostAnimTbl[1] = duelresult_AnimDataRead(0xA0081);
    duelresult_hostAnimTbl[2] = duelresult_AnimDataRead(0xA0080);
    duelresult_hostAnimTbl[3] = duelresult_AnimDataRead(0xA0084);
    duelresult_hostAnimTbl[4] = duelresult_AnimDataRead(0xA0082);
    duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0], duelresult_hostAnimTbl[0]);

    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 10.0f, 30.0f, 8.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    HuAudSeqPlay(0xF);
    WipeCreateIn(WIPE_STARS, 8);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBDPlayerPosMoveCreate(&duelresult_platformMdlTbl[i]->coords, &duelresult_platformPosTbl[2 - i],
                                             &duelresult_platformMdlTbl[i]->coords, 60));
        obj = omAddObj(0x3FFF, 0, 0, -1, duelresult_PlatformSlideObjMain);
        obj->work[1] = i;
        obj->work[2] = 60;
        HuPrcSleep(10);
    }
    HuPrcSleep(40);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_hostMdl->coords, &duelresult_hostPos,
                                                            &duelresult_hostMdl->coords, 60));
    obj = omAddObj(0x3FFF, 0, 0, -1, duelresult_HostSlideObjMain);
    obj->work[2] = 60;
    MBDMotionSet(duelresult_hostMdl, 0, 2);
    Hu3DParticleAttrSet(effect, 0, 1);
    i = 0;
    while (1) {
        EffectPosSet(effect, duelresult_hostMdl->coords.x, duelresult_hostMdl->coords.y + 100.0f,
                           duelresult_hostMdl->coords.z);
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
    MBDMotionSet(duelresult_hostMdl, 1, 0);
    HuPrcSleep(22);
    duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0], duelresult_hostAnimTbl[0]);
    MBDMotionEndShiftSet(duelresult_hostMdl, -1, 2);
    HuAudFXPlay(0x2A8);
    HuPrcSleep(10);
    for (i = 0; i < 2; i++) {
        process = omAddPrcObj(duelresult_PlayerLandProc, 0x1000, 0, 0x40);
        process->user_data = HuMemMemoryAlloc(process->heap, 0x20);
        *(s32 *)process->user_data = i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(10);
    }
    HuPrcChildWatch();

    MBDDlgWinExecAllKey(-1, 0x2001);
    HuAudFXPlay(0x16B);
    actor = MBDModelCreate(0x1D, NULL);
    HuVecCopy3F(&actor->coords, &duelresult_iconStartPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDModelSpinCreate(actor, 0, 20.0f, 20));
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&actor->coords, &duelresult_iconEndPos, &actor->coords, 20));
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
    duelresult_StarNumCreate();
    MBDPlayerKeyWait();
    duelresult_StarNumKill();

    if (GwPlayer[0].star == GwPlayer[1].star) {
        MBDDlgWinExecAllKey(-1, 0x2003);
        HuAudFXPlay(0x16C);
        actor = MBDModelCreate(0x1A, NULL);
        HuVecCopy3F(&actor->coords, &duelresult_iconStartPos);
        HuPrcChildLink(HuPrcCurrentGet(), MBDModelSpinCreate(actor, 0, 20.0f, 20));
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBDPlayerPosMoveCreate(&actor->coords, &duelresult_iconEndPos, &actor->coords, 20));
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
        duelresult_CoinNumCreate();
        MBDPlayerKeyWait();
        duelresult_CoinNumKill();

        if (GwPlayer[0].coin == GwPlayer[1].coin) {
            // The duel is a draw
            MBDDlgWinExecAllKey(-1, 0x2004);
            HuPrcVSleep();
            for (i = 0; i < 2; i++) {
                MBDMotionSet(duelresult_gwPlayerTbl[i]->player_obj, 3, 0);
            }
            HuAudFXPlay(0x2A9);
            duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0], duelresult_hostAnimTbl[4]);
            group = MBDSprGrpCreate(1, 0);
            data = DataRead(0x130134);
            group->unk_0C[0] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(group->unk_0A, 0, group->unk_0C[0], 0);
            HuSprPriSet(group->unk_0A, 0, 1);
            HuSprAttrSet(group->unk_0A, 0, HUSPR_ATTR_NONE);
            HuSprPosSet(group->unk_0A, 0, 160, 60);

            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
                    break;
                }
            }
            if (i != 2) {
                j = 0;
                n = 0;
                while (1) {
                    for (i = 0; i < 2; i++) {
                        if (!(GwPlayer[i].stat & PLAYER_IS_CPU) &&
                            (ContBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON))) {
                            break;
                        }
                    }
                    if (i != 2) {
                        break;
                    }
                    if (++j % 256 == 0) {
                        n ^= 1;
                        if (n == 0) {
                            duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0],
                                                     duelresult_hostAnimTbl[4]);
                        } else {
                            duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0],
                                                     duelresult_hostAnimTbl[2]);
                        }
                    }
                    HuPrcVSleep();
                }
            } else {
                HuPrcSleep(30);
            }
            kakusiMasuItemHis[0] = 0;
            kakusiMasuItemHis[1] = 1;
            kakusiMasuItemHis[2] = -1;
            return;
        }
    }

    duelresult_ModelAnimSet(duelresult_hostMdl->omObj1->model[0], duelresult_hostAnimTbl[1]);
    MBDDlgWinExecAllKey(-1, 0x2002);

    // Determine rankings
    for (j = 0; j < 2; j++) {
        values[j] = GwPlayer[j].star * 1000 + GwPlayer[j].coin;
    }
    for (i = 0; i < 2; i++) {
        for (j = 0, n = 0; j < 2; j++) {
            if (i != j) {
                n += values[i] < values[j];
            }
        }
        rank[i] = n;
    }
    for (i = 0; i < 2; i++) {
        kakusiMasuItemHis[rank[i]] = i;
    }
    kakusiMasuItemHis[2] = 0;

    duelresult_starMdl = MBDModelCreate(0x3B, NULL);
    AuraCreate(duelresult_starMdl->omObj1->model[0]);
    HuVecCopy3F(&duelresult_starMdl->coords, &duelresult_starStartPos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_hostMdl->coords, &duelresult_hostExitPos,
                                                            &duelresult_hostMdl->coords, 20));
    HuAudFXPlay(0x16D);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starPos,
                                                            &duelresult_starMdl->coords, 40));
    EffectParamSet(effect, 15.0f, 30.0f, 20.0f);
    Hu3DParticleAttrSet(effect, 0, 1);
    EffectRangeSet(effect, 300.0f);
    while (1) {
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, duelresult_StarHoverObjMain);
    swayObj->rot.y = 30.0f;
    swayObj->rot.z = 10.0f;
    HuAudFXPlay(0x159);
    MBDDlgWinExecAllKey(-1, 0x2005);

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
            Hu3DModelTPLvlSet(duelresult_cloudMdlTbl[j]->omObj1->model[0], work[j]);
        }
        HuPrcVSleep();
    }
    omDelObj(cloudObj);
    for (i = 0; i < 3; i++) {
        MBDModelKill(duelresult_cloudMdlTbl[i]);
    }
    HuPrcVSleep();

    for (i = 0; i < 6; i++) {
        duelresult_cloudMdlTbl[i] = MBDModelFileCreate(0x1301C9, -1, 1.0f, 0.0f, 0);
        Hu3DModelTPLvlInit(duelresult_cloudMdlTbl[i]->omObj1->model[0]);
        Hu3DModelTPLvlSet(duelresult_cloudMdlTbl[i]->omObj1->model[0], 255 - i * 32);
        HuVecCopyXYZ(&duelresult_cloudMdlTbl[i]->coords, 0.0f, 5000.0f, 0.0f);
        HuVecCopyXYZ(&duelresult_cloudMdlTbl[i]->scale, 1.0f - i * 0.1f, 1.0f - i * 0.1f, 1.0f - i * 0.1f);
        MBDModelTempAllocFree(duelresult_cloudMdlTbl[i]);
    }
    fallProc = omAddPrcObj(duelresult_CloudPassProc, 0x1000, 0, 0);
    star = MBDModelFileCreate(0x130148, -1, 1.0f, 0.0f, 0);
    HuVecCopyXYZ(&star->scale, 0.8f, 1.0f, 0.8f);
    MBDModelDispOff(star);
    HuAudFXPlay(0x16E);
    omDelObj(swayObj);
    for (i = 0; i < 2; i++) {
        MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[i]->player_obj->coords, &duelresult_playerPosTbl[i + 14],
                              &duelresult_gwPlayerTbl[i]->player_obj->coords, 20);
        MBDPlayerPosMoveCreate(&duelresult_platformMdlTbl[1 - i]->coords, &duelresult_playerPosTbl[i + 14],
                              &duelresult_platformMdlTbl[1 - i]->coords, 20);
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starDropPos,
                                                            &duelresult_starMdl->coords, 2));
    while (1) {
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starPos,
                                                            &duelresult_starMdl->coords, 18));
    HuPrcSleep(18);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBDPlayerPosMoveCreate(&duelresult_platformMdlTbl[1 - i]->coords, &duelresult_playerPosTbl[i + 8],
                                             &duelresult_platformMdlTbl[1 - i]->coords, 20));
    }
    HuPrcSleep(5);
    for (i = 0; i < 2; i++) {
        duelresult_gwPlayerTbl[i]->player_obj->coords.y += heights.heights[GwPlayer[i].chr] - 80.0f;
        MBDMotionSet(duelresult_gwPlayerTbl[i]->player_obj, 4, 2);
        PlayerFXPlay(0x286, i);
    }

    for (j = 0; j < 100; j++) {
        duelresult_cloudSpeed += 1.0f;
        if (j == 20) {
            for (i = 0; i < 2; i++) {
                MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[i]->player_obj->coords, &duelresult_playerPosTbl[i + 6],
                                      &duelresult_gwPlayerTbl[i]->player_obj->coords, 10);
            }
            HuPrcChildLink(HuPrcCurrentGet(),
                           MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starRisePos,
                                                 &duelresult_starMdl->coords, 15));
        }
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        if (j == 40) {
            swayObj = omAddObj(0x1000, 0, 0, -1, duelresult_StarHoverObjMain);
            swayObj->rot.y = 30.0f;
            swayObj->rot.z = 10.0f;
        }
        if (j >= 40) {
            swayObj->rot.y += 2.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(30);

    // Reveal the winner's star
    HuVecCopy3F(&star->coords, &duelresult_platformMdlTbl[1 - kakusiMasuItemHis[0]]->coords);
    MBDModelDispOn(star);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&star->coords,
                                                            &duelresult_playerPosTbl[kakusiMasuItemHis[0] + 10],
                                                            &star->coords, 30));
    HuPrcSleep(2);
    MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords,
                          &duelresult_playerPosTbl[kakusiMasuItemHis[0] + 10],
                          &duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords, 28);
    omDelObj(swayObj);
    MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starDropPos, &duelresult_starMdl->coords,
                          15);
    MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[1 - kakusiMasuItemHis[0]]->player_obj->coords,
                          &duelresult_playerPosTbl[15 - kakusiMasuItemHis[0]],
                          &duelresult_gwPlayerTbl[1 - kakusiMasuItemHis[0]]->player_obj->coords, 15);
    for (i = 0; i < 15; i++) {
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, duelresult_StarHoverObjMain);
    swayObj->rot.y = 80.0f;
    swayObj->rot.z = 10.0f;
    for (i = 0; i < 5; i++) {
        duelresult_cloudSpeed -= 3.0f;
        HuPrcVSleep();
    }
    MBDMotionSet(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, 0, 0);
    MBDMotionEndShiftSet(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, -1, 2);
    for (i = 0; i < 5; i++) {
        duelresult_cloudSpeed -= 3.0f;
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[1 - kakusiMasuItemHis[0]]->player_obj->coords,
                                         &duelresult_playerPosTbl[9 - kakusiMasuItemHis[0]],
                                         &duelresult_gwPlayerTbl[1 - kakusiMasuItemHis[0]]->player_obj->coords, 20));
    PlayerFXPlay(0x286, 1 - kakusiMasuItemHis[0]);
    omDelObj(swayObj);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starRisePos,
                                                            &duelresult_starMdl->coords, 45));
    duelresult_cloudHideF = 1;
    while (duelresult_cloudSpeed > 60.0f) {
        duelresult_cloudSpeed -= 3.0f;
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        HuPrcVSleep();
    }
    msmSeFadeOut(60);
    while (1) {
        EffectPosSet(effect, duelresult_starMdl->coords.x, duelresult_starMdl->coords.y,
                           duelresult_starMdl->coords.z);
        if (HuPrcChildGet(HuPrcCurrentGet()) == 0) {
            break;
        }
        HuPrcVSleep();
    }
    swayObj = omAddObj(0x1000, 0, 0, -1, duelresult_StarHoverObjMain);
    swayObj->rot.y = 10.0f;
    swayObj->rot.z = 10.0f;
    HuPrcSleep(20);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&star->coords,
                                                            &duelresult_playerPosTbl[kakusiMasuItemHis[0] + 6],
                                                            &star->coords, 60));
    MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords,
                          &duelresult_playerPosTbl[kakusiMasuItemHis[0] + 6],
                          &duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords, 60);
    HuPrcChildWatch();

    MBDDlgWinInsertCreateAllKey(-1, 0x2006, mbKSuitObj[GwPlayer[kakusiMasuItemHis[0]].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    for (i = 0; i < 2; i++) {
        actors = duelresult_cheerMdlNoTbl;
        duelresult_cheerPlatformMdlTbl[i] = MBDModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, 0);
        HuVecCopy3F(&duelresult_cheerPlatformMdlTbl[i]->coords, &duelresult_cheerPosTbl[i]);
        HuVecCopyXYZ(&duelresult_cheerPlatformMdlTbl[i]->scale, 0.625f, 0.625f, 0.625f);
        MBDModelTempAllocFree(duelresult_cheerPlatformMdlTbl[i]);
        HuPrcVSleep();
        duelresult_cheerMdlTbl[i] = MBDModelCreate(actors.ids[GwPlayer[kakusiMasuItemHis[0]].chr], NULL);
        HuVecCopy3F(&duelresult_cheerMdlTbl[i]->coords, &duelresult_cheerPosTbl[i]);
        MBDModelTempAllocFree(duelresult_cheerMdlTbl[i]);
        HuPrcVSleep();
        duelresult_cheerMdlTbl[i]->velocity.x = 2.0f;
    }

    duelresult_cloudHideF = 1;
    for (i = 0; !duelresult_CloudPassDoneCheck(); i++) {
        duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        star->coords.y += 2.0f;
        if (i == 40) {
            Hu3DParticleAttrSet(effect, 1, 0);
            MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starExitPos,
                                  &duelresult_starMdl->coords, 30);
        }
        HuPrcVSleep();
    }
    for (; i < 60; i++) {
        duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords.y += 2.0f;
        star->coords.y += 2.0f;
        if (i == 40) {
            Hu3DParticleAttrSet(effect, 1, 0);
            MBDPlayerPosMoveCreate(&duelresult_starMdl->coords, &duelresult_starExitPos,
                                  &duelresult_starMdl->coords, 30);
        }
        HuPrcVSleep();
    }

    MBDCameraNearFarSet(100.0f, 20000.0f);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords,
                                         &duelresult_winnerPosTbl[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->coords, 30));
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDPlayerPosMoveCreate(&star->coords, &duelresult_winnerPosTbl[GwPlayer[kakusiMasuItemHis[0]].chr],
                                         &star->coords, 30));
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        MBDPlayerPosMoveCreate(&duelresult_cheerMdlTbl[i]->coords, &duelresult_cheerEndPosTbl[i],
                              &duelresult_cheerMdlTbl[i]->coords, 60);
        MBDPlayerPosMoveCreate(&duelresult_cheerPlatformMdlTbl[i]->coords, &duelresult_cheerEndPosTbl[i],
                              &duelresult_cheerPlatformMdlTbl[i]->coords, 60);
    }
    for (i = 0; i < 2; i++) {
        if (i != kakusiMasuItemHis[0]) {
            MBDPlayerModelKill(i);
            MBDModelKill(duelresult_platformMdlTbl[1 - i]);
        }
    }
    AuraKill(duelresult_starMdl->omObj1->model[0]);
    MBDModelKill(duelresult_starMdl);
    MBDModelKill(duelresult_hostMdl);
    HuWinAllKill();
    duelresult_winClosedF = 1;
    EffectStop(effect);
    omDelPrcObj(fallProc);
    for (i = 0; i < 6; i++) {
        MBDModelKill(duelresult_cloudMdlTbl[i]);
    }
    HuPrcSleep(5);
    omAddPrcObj(duelresult_FireworkShowProc, 0x1000, 0, 0);
    HuPrcSleep(1);

    PlayerFXPlay(0x27D, kakusiMasuItemHis[0]);
    CharAnimSet(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj->omObj1->model[0], 2,
                       GwPlayer[kakusiMasuItemHis[0]].chr, duelresult_playerAnimTbl[kakusiMasuItemHis[0]][1]);
    MBDMotionSet(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, 2, 0);
    MBDModelMotionWait(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj);
    HuAudFXPlay(0x177);
    MBDMotionSet(duelresult_gwPlayerTbl[kakusiMasuItemHis[0]]->player_obj, 5, 2);
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
    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            break;
        }
    }
    if (i != 2) {
        while (1) {
            for (i = 0; i < 2; i++) {
                if (!(GwPlayer[i].stat & PLAYER_IS_CPU) &&
                    (ContBtnDown[GwPlayer[i].pad] & (A_BUTTON | B_BUTTON | START_BUTTON))) {
                    break;
                }
            }
            if (i != 2) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        HuPrcSleep(30);
    }
}

void duelresult_MainProc(void) {
    duelresult_IntroExec();
    duelresult_ResultExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void duelresult_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        duelresult_BackClose();
        duelresult_SysClose();
        if (duelresult_winClosedF == 0) {
            HuWinAllKill();
        }
        if (!(GwSystem.playMode & 4)) {
            GWPlayNumInc(-1);
            if (kakusiMasuItemHis[2] == 0) {
                GWCharPlayNumInc(-1, GwPlayer[kakusiMasuItemHis[0]].chr);
            }
        }
        if (GwSystem.playMode & 4) {
            if (_CheckFlag(0)) {
                _ClearFlag(0);
                _ClearFlag(0x28);
            }
        } else if (_CheckFlag(0)) {
            _ClearFlag(0);
            _ClearFlag(0x17);
            SLSaveBoardStory(1);
        } else {
            SLCommonSet(1);
        }
        omOvlGotoEx(duelresult2, 0, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
    }
}

void duelresult_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(WIPE_STARS, 20);
        msmSeFadeOut(40);
        obj->func = duelresult_ExitObjMain;
    }
}

void duelresult_SysInit() {
    MBDModelInit();
    MBDPlayerMotInit();
    MBDMotShiftInit();
    MBDSprGrpInit();
}

void duelresult_SysClose() {
    MBDSprGrpClose();
    MBDMotShiftClose();
    MBDPlayerClose();
    MBDModelClose();
}

void duelresult_BackInit(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackLoad(0);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
}

void duelresult_BackClose() {
    MBDBackKill();
    MBDBackClose();
}

const DuelResultCharActors duelresult_cheerMdlNoTbl = { { 37, 12, 9, 10, 38, 11, 44, 36 } };
