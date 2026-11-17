#include "common_duel.h"
#include "game/overlays/duel/common/ovl_81.h"

// Inlined Z rotation matrix build (same as MTX_ROTZ in w02).
#define MTX_ROTZ(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[0][1], &(mtx)[0][0]);                                        \
        (mtx)[1][0] = -(mtx)[0][1];                                                         \
        (mtx)[1][1] = (mtx)[0][0];                                                          \
        (mtx)[0][2] = (mtx)[0][3] = (mtx)[1][3] = (mtx)[1][2] = (mtx)[2][0] = (mtx)[2][1] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[2][2] = (mtx)[3][3] = 1.0f;                                                   \
    }

// Inlined Y rotation matrix build.
#define MTX_ROTY(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[2][0], &(mtx)[2][2]);                                        \
        (mtx)[0][2] = -(mtx)[2][0];                                                         \
        (mtx)[0][0] = (mtx)[2][2];                                                          \
        (mtx)[0][1] = (mtx)[0][3] = (mtx)[1][0] = (mtx)[1][2] = (mtx)[1][3] = (mtx)[2][1] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[1][1] = (mtx)[3][3] = 1.0f;                                                   \
    }

// Inlined X rotation matrix build.
#define MTX_ROTX(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[1][2], &(mtx)[1][1]);                                        \
        (mtx)[2][1] = -(mtx)[1][2];                                                         \
        (mtx)[2][2] = (mtx)[1][1];                                                          \
        (mtx)[0][1] = (mtx)[0][2] = (mtx)[0][3] = (mtx)[1][0] = (mtx)[1][3] = (mtx)[2][0] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[0][0] = (mtx)[3][3] = 1.0f;                                                   \
    }

typedef struct Duel06CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel06CamShakeWork; // sizeof 0x10

typedef struct Duel06SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel06SpriteWork; // sizeof 0x10

typedef struct Duel06PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel06PartnerAttackWork; // sizeof 0x10

typedef struct Duel06WinColorWork {
    /* 0x00 */ s32 window;
    /* 0x04 */ char unk_04[0xC];
} Duel06WinColorWork; // sizeof 0x10

typedef struct Duel06PartnerRouletteWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ char unk_04[0xC];
} Duel06PartnerRouletteWork; // sizeof 0x10

// Board space indices used when a player picks up a partner.
typedef struct Duel06PartnerSpaces {
    /* 0x00 */ s32 returnSpace;
    /* 0x04 */ s32 startSpace;
    /* 0x08 */ s32 partnerSpace;
} Duel06PartnerSpaces; // sizeof 0xC

typedef struct Duel06SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel06SwayWork; // sizeof 0x10


void *memcpy(void *, const void *, unsigned int);
extern const Vec mbd6ev_partnerVanishOfsTbl[];
void MBD6Ev_GateGuyWarpExec(void);
s32 MBD6_ComPartnerRefuseRateGet(void);
void MBD6Ev_PartnerRouletteWinColorProc(void);
Process *MBDVecRotLerpCreate(Vec *, Vec *, Vec *, s32);
void MBDVecForwardSet(Vec *);
void MBDCameraFocusObjSet(Object *);
void MBD6Ev_PartnerRouletteProc(void);
Process *MBDCoinScatterCreate(Object *, s32, s32, s32, s32);
Process *MBDEffMdlCreate(s32, Vec *, Vec *, f32);
Process *MBDMgCallListProcCreate(void);
extern s32 mbKSuitObj[];
void MBD6_KoopaFireObjMain(omObjData *);
Object *MBDAuraCreate(Vec *);
void MBDAuraLandNoSe(s32);
void MBDAuraHoverStart(void);
void *MBDPlayerVibrateObjCreate(s16, s16, s32);
void MBDAuraSpinExec(s32);
void MBDPlayerVibrateObjKill(void *);
void MBDAuraHoverStop(void);
void MBDAuraRiseExec(s32);
void MBDAuraKill(void);
void MBDPlayerMotionSet(s32, s32, s32);
void MBDPartnerAttackMotKill(void);
void MBDPartnerAttackMotSet(Object *, s32, s32);
void MBD6Ev_PartnerBox1SquashProc(void);
extern void MBD6_MissMarkProc(void);
extern void MBD6_CameraShakeProc(void);
extern void MBD6Ev_PartnerBox2SquashProc(void);
void MBD6_ObjectSetup(void);
void MBD6_GateGuyCreate(void);
void MBD6_PartnerBox1Create(void);
void MBD6_PartnerBox2Create(void);
void MBD6_SwitchCreateAll(void);
void MBD6_SwitchCreate(s16);
void MBDStart(s32);
f32 MBDVecAngleGet(Vec *);
s32 MBDCameraStopCheck(void);
void MBDVecDirGet(Vec *, Vec *, Vec *);
Process *MBDPlayerPosMoveCreate(Vec *, Vec *, Vec *, s32);
void MBDPlayerPartyMotionSet(s32, s32, s32);
void MBD6Ev_PartnerGetExec(s32);
void MBD6Ev_StartWarpLinkGet(s8 *, s8 *);
void MBDItemWarpBlockSwapInit(void);
void MBDItemWarpBlockSwapPlayerSet(void);
void MBDItemWarpBlockSwapCreate(void);
void MBDCoinChangeCreate(s32, s32);
void MBDCoinTakeCreate(s32, s32);
void MBD6_DodgeProc(void);
void MBD6Ev_PartnerBox1SwayProc(void);
void MBD6Ev_PartnerBox2SwayProc(void);
void MBDMasuEventTblAdd(event_table_entry *);
void MBDWalkAttackHookSet(s32 (*)(void));
void MBDHatenaFuncSet(process_func);
void MBD6Ev_Hatena(void);
s32 MBD6_WalkAttackHook(void);
void MBDPartnerAttackFuncSet(PartnerFunc *, PartnerFunc *);
void MBD6_NokonokoAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_KuriboAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_KinopioAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_BomheiAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_WhompAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_DossunAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_TeresaAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_BlizzardAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_KoopaJrAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_WanwanAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_SnifitAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD6_PakkunAttackExec(s32, s32, Object *, Object *, s32, s32);

void MBD6Ev_StartMasu1P(void);
void MBD6Ev_StartMasu2P(void);
void MBD6Ev_TurnStart(void);
void MBD6Ev_GateGuyMasu(void);
void MBD6Ev_GateGuyMasuBranch(void);
void MBD6Ev_HatenaHpRecover(void);
void MBD6Ev_HatenaPosSwap(void);
void MBD6Ev_HatenaCoinLose10(void);
void MBD6Ev_HatenaCoinGain10(void);
void MBD6Ev_HatenaStartWarp(void);
void MBD6Ev_HatenaMasuOwnerSwap(void);
void MBD6Ev_HatenaPartnerPowerUp(void);
void MBD6Ev_HatenaPartnerPowerDown(void);
void MBD6Ev_HatenaPartnerSwap(void);
void MBD6Ev_HatenaMasuOwnerClear(void);
void MBD6Ev_HatenaCoinGain20(void);
void MBD6Ev_Merge1(void);
void MBD6Ev_Merge2(void);
void MBD6Ev_Merge3(void);
void MBD6Ev_SwitchMasu(void);
void MBD6Ev_Merge4(void);

s32 mbd6_attackDashMdlTbl[] = { 55, 57 };

s32 mbd6_koopaMot[] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F };

f32 mbd6_gateGuyScrewSpeed = 3.0f;

s32 mbd6_gateGuyMot[] = { 3, 0xA011D, 0xA011E, 0xA0121 };

s16 mbd6_partnerBox1Masu = 27;

s16 mbd6_partnerBox1DirMasu = 26;

Process *mbd6ev_partnerBox1SwayProc = NULL;

s16 mbd6_partnerBox2Masu = 30;

s16 mbd6_partnerBox2DirMasu = 29;

Process *mbd6ev_partnerBox2SwayProc = NULL;

s16 mbd6_switchMasuTbl[] = { 31, 25, 24, 33, 32 };

f32 mbd6_switchRotTbl[] = { 0.0f, -12.0f, 192.0f, -192.0f, 12.0f };

s8 mbd6_comPartnerTbl[] = {
    7, 30, 6, 30, 4, 30, 1, 30,
    11, 30, 8, 20, 3, 20, 10, 20,
    0, 20, 2, 20, 9, 20, 5, 20,
    -1, -1
};

s8 mbd6_comPartnerMarioTbl[] = {
    0, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerLuigiTbl[] = {
    1, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerPeachTbl[] = {
    2, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerYoshiTbl[] = {
    4, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerWarioTbl[] = {
    3, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerDkTbl[] = {
    5, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerWaluigiTbl[] = {
    7, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 mbd6_comPartnerDaisyTbl[] = {
    6, 50, 7, 20, 6, 20, 4, 20,
    1, 20, 11, 20, 8, 10, 3, 10,
    10, 10, 0, 10, 2, 10, 9, 10,
    5, 10, -1, -1
};

s8 *mbd6_comPartnerChrTbl[] = { mbd6_comPartnerMarioTbl, mbd6_comPartnerLuigiTbl, mbd6_comPartnerPeachTbl, mbd6_comPartnerYoshiTbl, mbd6_comPartnerWarioTbl, mbd6_comPartnerDkTbl, mbd6_comPartnerWaluigiTbl, mbd6_comPartnerDaisyTbl };

Duel06PartnerSpaces mbd6ev_partnerMasuTbl[] = {
    { 21, 26, 27 },
    { 22, 29, 30 }
};

s32 mbd6ev_partnerRouletteResult = -1;

Object *mbd6ev_partnerGetMdl = NULL;

s32 mbd6ev_partnerRouletteColorF = 0;

event_list_entry mbd6_startMasu1PEventTbl[] = {
    { 1, 1, MBD6Ev_StartMasu1P },
    { 0, 0, NULL }
};

event_list_entry mbd6_startMasu2PEventTbl[] = {
    { 1, 1, MBD6Ev_StartMasu2P },
    { 0, 0, NULL }
};

event_list_entry mbd6_turnStartEventTbl[] = {
    { 7, 1, MBD6Ev_TurnStart },
    { 0, 0, NULL }
};

event_list_entry mbd6_gateGuyMasuEventTbl[] = {
    { 1, 1, MBD6Ev_GateGuyMasu },
    { 8, 1, MBD6Ev_GateGuyMasuBranch },
    { 0, 0, NULL }
};

void (*mbd6ev_hatenaFuncTbl[])(void) = {
    MBD6Ev_HatenaHpRecover,
    MBD6Ev_HatenaPosSwap,
    MBD6Ev_HatenaCoinLose10,
    MBD6Ev_HatenaCoinGain10,
    MBD6Ev_HatenaStartWarp,
    MBD6Ev_HatenaMasuOwnerSwap,
    MBD6Ev_HatenaPartnerPowerUp,
    MBD6Ev_HatenaPartnerPowerDown,
    MBD6Ev_HatenaPartnerSwap,
    MBD6Ev_HatenaMasuOwnerClear,
    MBD6Ev_HatenaCoinGain20
};

event_table_entry mbd6_commonEventTbl[] = {
    { 21, mbd6_startMasu1PEventTbl },
    { 22, mbd6_startMasu2PEventTbl },
    { -5, mbd6_turnStartEventTbl },
    { 23, mbd6_gateGuyMasuEventTbl },
    { -1, NULL }
};

event_list_entry mbd6_merge1EventTbl[] = {
    { 1, 1, MBD6Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mbd6_merge2EventTbl[] = {
    { 1, 1, MBD6Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mbd6_merge3EventTbl[] = {
    { 1, 1, MBD6Ev_Merge3 },
    { 0, 0, NULL }
};

s16 mbd6ev_switchEventMasuTbl[] = { 20, 4, 8, 0, 16 };

event_list_entry mbd6_switchEventTbl[] = {
    { 3, 1, MBD6Ev_SwitchMasu },
    { 0, 0, NULL }
};

event_list_entry mbd6_switchMerge4EventTbl[] = {
    { 3, 1, MBD6Ev_SwitchMasu },
    { 1, 1, MBD6Ev_Merge4 },
    { 0, 0, NULL }
};

event_table_entry mbd6_specialEventTbl[] = {
    { 19, mbd6_merge1EventTbl },
    { 18, mbd6_merge2EventTbl },
    { 1, mbd6_merge3EventTbl },
    { 20, mbd6_switchMerge4EventTbl },
    { 4, mbd6_switchEventTbl },
    { 8, mbd6_switchEventTbl },
    { 0, mbd6_switchEventTbl },
    { 16, mbd6_switchEventTbl },
    { -1, NULL }
};

DuelHelpWin *mbd6_branchStickHelp BSS;
DuelHelpWin *mbd6_branchItemHelp BSS;
DuelHelpWin *mbd6_branchBtnHelp BSS;
DuelHelpWin *mbd6_branchMapScrollHelp BSS;
Object *mbd6_bomheiFrontMdl BSS;
Object *mbd6_bomheiBackMdl BSS;
Object *mbd6_koopaMdl BSS;
omObjData *mbd6_koopaFireObj BSS;
Object *mbd6_gateGuyMdl BSS;
Process *mbd6_gateGuyScrewProc BSS;
Object *mbd6_partnerBox1Mdl BSS;
f32 mbd6ev_partnerBox1SwayAmp BSS;
Object *mbd6_partnerBox2Mdl BSS;
f32 mbd6ev_partnerBox2SwayAmp BSS;
s16 mbd6_switchMdlTbl[6] BSS;

extern s16 mbd6_switchMot[]; // mbd6_switchMdlTbl[5]

void MBD6_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBDMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MBD6_BranchHelpStart(void) {
    while (MBDCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mbd6_branchStickHelp = MBDHelpWinCreate(0, 0xA0, 1);
    mbd6_branchItemHelp = MBDHelpWinCreate(0xD, 0xAE, 1);
    mbd6_branchBtnHelp = MBDHelpWinCreate(1, 0xBC, 1);
    mbd6_branchMapScrollHelp = MBDHelpWinCreate(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MBD6_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBDHelpWinKill(mbd6_branchStickHelp);
    MBDHelpWinKill(mbd6_branchItemHelp);
    MBDHelpWinKill(mbd6_branchBtnHelp);
    MBDHelpWinKill(mbd6_branchMapScrollHelp);
}

void MBD6_BoardInit(void) {
    GwSystem.current_board_index = 5;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x5A, 0, 0x4190);
}

void MBD6_SaveInit(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    MBDMasuInit();
    MBDMasuCreate(0x13, 0x246);
    MBDMasuLinkIdxGet(0x15, &sp10, &sp11);
    MBDMoveMasuSet(0, sp10, sp11);
    MBDMasuLinkIdxGet(0x16, &sp10, &sp11);
    MBDMoveMasuSet(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    MBDMasuKill();
    MBDMasuClose();
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    MBDMasuOwnerInit();
    omOvlReturnEx(1);
}

void MBD6_AttackEffDirGet(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    MBDVecDirGet(arg0, arg1, arg2);
    angle = MBDVecAngleGet(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

void MBD6_MissMarkProc(void) {
    Duel06SpriteWork *work = HuPrcCurrentGet()->user_data;
    f32 x = work->pos.x;
    f32 y = work->pos.y;
    f32 z = work->pos.z;
    Vec pos;
    Vec2f screenPos;
    UnkBoard4 *sprite;
    void *data;
    f32 amplitude;
    s32 i;

    HuPrcSleep(5);
    HuVecCopyXYZ(&pos, x, y, z);
    MBDCamera3Dto2D(&pos, &screenPos);
    sprite = MBDSprGrpCreate(1, 0);
    data = DataRead(0x1301EC);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 0x2010);
    HuSprAttrSet(sprite->unk_0A, 0, 0);
    HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y);
    HuAudFXPlay(0x202);
    amplitude = 20.0f;
    for (i = 0; i < 20; i++) {
        HuSprPosSet(sprite->unk_0A, 0, screenPos.x, screenPos.y - fabs(sindf(i * 20) * amplitude));
        amplitude -= 1.0f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }
    MBDSprGrpKill(sprite);
    omDelPrcObj(NULL);
}

Process *MBD6_MissMarkCreate(Object *object) {
    Process *process;
    Duel06SpriteWork *work;

    process = omAddPrcObj(MBD6_MissMarkProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

void MBD6_DodgeProc(void) {
    Process *process = HuPrcCurrentGet();
    Duel06PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = work->player;
    Object *obj = work->obj;
    s32 delay = work->delay;
    s32 waitTime = work->waitTime;
    Vec offset;
    Vec origPos;

    delay -= 5;
    if (delay > 0) {
        HuPrcSleep(delay);
    }
    MBD6_MissMarkCreate(obj);
    HuVecSubtract(&offset, &obj->coords, &player->player_obj->coords);
    if (mbdAttackType == 3 || mbdAttackType == 1) {
        MBDVecRotateY(&offset, -90.0f);
    } else {
        MBDVecRotateY(&offset, 90.0f);
    }
    HuVecAdd(&offset, &offset, &obj->coords);
    HuVecCopy3F(&origPos, &obj->coords);
    MBDPartnerModelMotionSet(obj, 3, 0);
    mbdPartnerExtMotUseCnt++;
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &offset, &obj->coords, 2.0f));
    HuPrcChildWatch();
    HuPrcSleep(waitTime);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 2.0f));
    Hu3DMotionAttrSet(obj->omObj1->model[0], 0, 4);
    HuPrcChildWatch();
    MBDModelMotionStartWait(obj);
    MBDMotionSet(obj, -1, 2);
    mbdPartnerExtMotUseCnt--;
    omDelPrcObj(NULL);
}

Process *MBD6_DodgeCreate(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel06PartnerAttackWork *work;

    process = omAddPrcObj(MBD6_DodgeProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void MBD6_AttackTargetPosGet(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
    Vec offset;
    f32 angle;

    HuVecCopy3F(origPos, &obj->coords);
    if (target != NULL) {
        HuVecCopy3F(targetPos, &target->coords);
    } else {
        HuVecCopy3F(targetPos, &player->player_obj->coords);
    }
    MBDVecDirGet(&obj->coords, targetPos, &obj->rot);
    angle = MBDVecAngleGet(&obj->rot) + 180.0f;
    offset.x = sindf(angle) * dist;
    offset.y = 0.0f;
    offset.z = cosdf(angle) * dist;
    HuVecAdd(targetPos, targetPos, &offset);
}

void MBD6_AttackCameraFocusSet(void) {
    MBDCameraFocusVecSet(&mbdAttackCameraPos);
}

Process *MBD6_AttackCameraSpeedMoveCreate(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &arg0->coords, &mbdAttackCameraPos, arg3);
    } else {
        process = MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &arg1->player_obj->coords, &mbdAttackCameraPos, arg3);
    }
    return process;
}

void MBD6_AttackCameraTimeMoveCreate(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 arg3) {
    if (arg2 & 9) {
        MBDPlayerPosMoveCreate(&mbdAttackCameraPos, &arg0->coords, &mbdAttackCameraPos, arg3);
    } else {
        MBDPlayerPosMoveCreate(&mbdAttackCameraPos, &arg1->player_obj->coords, &mbdAttackCameraPos, arg3);
    }
}

void MBD6_CameraShakeProc(void) {
    Duel06CamShakeWork *work = HuPrcCurrentGet()->user_data;
    s32 magnitude = work->magnitude;
    s32 decay = work->decay;
    Vec2f base;
    Vec2f pos;

    MBDCameraPos2DGet(&base);
    MBDCameraFocusModeSet(0);
    for (; magnitude >= 0; magnitude -= decay) {
        pos.x = MBDRand(magnitude) + base.x - magnitude / 2;
        pos.y = MBDRand(magnitude) + base.y - magnitude / 2;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
        pos.x = MBDRand(magnitude) + base.x - magnitude / 2;
        pos.y = MBDRand(magnitude) + base.y - magnitude / 2;
        MBDCameraPos2DSet(&pos);
        HuPrcVSleep();
    }
    MBDCameraFocusModeSet(4);
    omDelPrcObj(NULL);
}

Process *MBD6_CameraShakeCreate(s32 magnitude, s32 decay) {
    Process *process;
    Duel06CamShakeWork *work;

    process = omAddPrcObj(MBD6_CameraShakeProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

void MBD6_BomheiMdlSwap(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *model;

    player = MBDPlayerGet(playerIndex);
    switch (mode) {
        case 0:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                model = MBDModelCreate(0x28, NULL);
                mbd6_bomheiFrontMdl = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                MBDModelDispOff(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                model = MBDModelCreate(0x28, NULL);
                mbd6_bomheiBackMdl = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                MBDModelDispOff(partner);
            }
            break;
        case 1:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                MBDModelKill(mbd6_bomheiFrontMdl);
                MBDModelDispOn(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                MBDModelKill(mbd6_bomheiBackMdl);
                MBDModelDispOn(partner);
            }
            break;
        case 2:
            switch (mbdAttackType) {
                case 1:
                case 3:
                    if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                        partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                        model = MBDModelCreate(0x28, NULL);
                        mbd6_bomheiFrontMdl = model;
                        HuVecCopy3F(&model->coords, &partner->coords);
                        HuVecCopy3F(&model->rot, &partner->rot);
                        MBDModelDispOff(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                        model = MBDModelCreate(0x28, NULL);
                        mbd6_bomheiBackMdl = model;
                        HuVecCopy3F(&model->coords, &partner->coords);
                        HuVecCopy3F(&model->rot, &partner->rot);
                        MBDModelDispOff(partner);
                    }
                    break;
            }
            break;
        case 3:
            switch (mbdAttackType) {
                case 1:
                case 3:
                    if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                        partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                        MBDModelKill(mbd6_bomheiFrontMdl);
                        MBDModelDispOn(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                        MBDModelKill(mbd6_bomheiBackMdl);
                        MBDModelDispOn(partner);
                    }
                    break;
            }
            break;
    }
}

Object *MBD6_AttackEffMdlCreate(s32 arg0) {
    Object *obj;

    obj = MBDModelCreate(arg0 & 0xFF, 0);
    Hu3DModelAttrSet(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    MBDModelTempAllocFree(obj);
    MBDModelDispOff(obj);
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    return obj;
}

void MBD6_AttackEffMdlDispOn(Object *arg0, Vec *arg1) {
    MBDModelDispOn(arg0);
    Hu3DMotionAttrSet(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

void MBD6_NokonokoAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *extra;
    s32 model;
    f32 angle;
    f32 speed;
    Vec targetPos;
    Vec origPos;
    Vec delta;
    Process *spinProcesses[2];
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    spinProcesses[0] = NULL;
    spinProcesses[1] = NULL;
    effect = NULL;
    extra = NULL;
    model = -1;
    MBDPartnerAttackMotLoad(0);
    if (mode == 1) {
        effect = MBD6_AttackEffMdlCreate(0x45);
    }
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    if (mode == 2) {
        extra = MBDModelCreate(0x56, NULL);
        MBDModelTempAllocFree(extra);
        MBDModelDispOff(extra);
    }
    MBD6_AttackCameraFocusSet();
    HuAudFXPlay(0x25A);
    MBDPartnerAttackMotSet(obj, 0, 0);
    MBDModelMotionWait(obj);
    MBDPartnerAttackMotSet(obj, 1, 2);
    if (mode == 2) {
        HuAudFXPlay(0x1D6);
        angle = 0.0f;
        for (speed = 0.0f; speed <= 30.0f; speed += 2.0f) {
            HuPrcVSleep();
            angle += speed;
            MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        }
        spinProcesses[0] = MBDModelSpinCreate(obj, angle, 30.0f, -1);
        HuVecCopy3F(&extra->coords, &obj->coords);
        MBDModelDispOn(extra);
        spinProcesses[1] = MBDModelSpinCreate(extra, 0.0f, 30.0f, -1);
        HuPrcSleep(20);
    }
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    HuVecSubtract(&delta, &obj->coords, &targetPos);
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 3.0f));
    if (mode == 2) {
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&extra->coords, &targetPos, &extra->coords, 3.0f));
    }
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    if (flags & 8) {
        MBD6_DodgeCreate(player, target, HuVecGetLength3F(&delta) / 3.0f, 20);
        HuPrcChildWatch();
        MBDModelDispOff(partner);
    } else {
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        if (mode == 1) {
            MBD6_AttackEffMdlDispOn(effect, &obj->coords);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            MBDEffMdlCreate(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                MBD6_AttackEffDirGet(&target->coords, &effect->coords, &effect->rot);
                MBD6_AttackEffMdlDispOn(effect, &target->coords);
            } else {
                model = MBDEffExplodeCreate(0xB0025, "obj1");
                MBDEffExplodePosSet(model, &midPos);
            }
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            MBDEffMdlCreate(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                MBD6_AttackEffDirGet(&player->player_obj->coords, &effect->coords, &effect->rot);
                MBD6_AttackEffMdlDispOn(effect, &player->player_obj->coords);
            } else {
                model = MBDEffExplodeCreate(0xB0025, "obj1");
                MBDEffExplodePosSet(model, &midPos);
            }
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            HuAudFXPlay((mbdAttackResult & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((mbdAttackResult & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
    if (mode == 2) {
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&extra->coords, &origPos, &extra->coords, 3.0f));
    }
    HuPrcChildWatch();
    MBDModelDispOff(partner);
    if (spinProcesses[0] != NULL) {
        omDelPrcObj(spinProcesses[0]);
    }
    if (mode == 2) {
        if (spinProcesses[1] != NULL) {
            omDelPrcObj(spinProcesses[1]);
        }
        MBDModelDispOff(extra);
    }
    MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    MBDPartnerAttackMotSet(obj, 0, 0);
    Hu3DMotionAttrSet(obj->omObj1->model[0], 0, 4);
    Hu3DMotionTimeSet(obj->omObj1->model[0], 1000.0f);
    MBDModelMotionStartWait(obj);
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDModelKill(partner);
    if (mode == 1) {
        MBDModelKill(effect);
    } else {
        MBDModelKill(extra);
        if (model != -1) {
            while (!MBDEffExplodeEndCheck(model)) {
                HuPrcVSleep();
            }
            MBDEffExplodeKill(model);
        }
    }
    MBDPartnerAttackMotKill();
}

void MBD6_KuriboAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *extra;
    Process *extraProcess;
    s32 i;
    f32 jumpSpeed;
    f32 jumpAccel;
    Vec targetPos;
    Vec origPos;
    s32 effectModels[2];
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    effectModels[0] = 0x48;
    effectModels[1] = 0x49;
    extraProcess = NULL;
    effect = MBD6_AttackEffMdlCreate(effectModels[mode - 1]);
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    if (mode == 2) {
        extra = MBDModelCreate(0x56, NULL);
        MBDModelTempAllocFree(extra);
        MBDModelDispOff(extra);
    }
    MBDPartnerAttackMotLoad(1);
    MBDMotionSet(obj, 0, 2);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 7.0f);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDModelDispOff(partner);
    if (mode == 2) {
        HuVecCopy3F(&extra->coords, &obj->coords);
        MBDModelDispOn(extra);
        extraProcess = MBDModelSpinCreate(extra, 0, 30.0f, -1);
        jumpSpeed = 3.0f;
        jumpAccel = -0.375f;
        MBDModelJumpSet(extra, jumpSpeed, jumpAccel);
        MBDModelDispOn(partner);
        MBDModelJumpSet(partner, jumpSpeed, jumpAccel);
    }
    MBDPartnerAttackMotSet(obj, 0, 2);
    MBDModelJumpSet(obj, mode + 1.0f, -(mode + 1.0f) / 8.0f);
    if (mode == 2) {
        for (i = 0; i < 8; i++) {
            MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, i * 45.0f);
            HuPrcVSleep();
        }
        MTX_ROTY(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    } else {
        HuPrcSleep(8);
    }
    obj->velocity.z = 0.0f;
    MBDPartnerAttackMotSet(obj, 1, 0);
    if (mode == 2) {
        if (extraProcess != NULL) {
            omDelPrcObj(extraProcess);
        }
        MBDModelDispOff(extra);
        MBDModelDispOff(partner);
    }
    if (flags & 8) {
        MBD6_DodgeCreate(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        MBD6_AttackEffMdlDispOn(effect, &obj->coords);
        HuAudFXPlay(0x25B);
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += obj->velocity.x;
        MBD6_AttackEffMdlDispOn(effect, mid);
        if (mode == 2) {
            MBDEffMdlCreate(0x4B, &midPos, 0, 2.0f);
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            HuAudFXPlay((mbdAttackResult & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((mbdAttackResult & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    MBDModelMotionWait(obj);
    obj->velocity.z = -(mode + 1.0f) / 8.0f;
    MBDModelJumpWait(obj);
    MBDVecDirGet(&obj->coords, &origPos, &obj->rot);
    MBDMotionSet(obj, 0, 2);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDModelKill(effect);
    MBDModelKill(partner);
    if (mode == 2) {
        MBDModelKill(extra);
    }
    MBDPartnerAttackMotKill();
}

void MBD6_KinopioAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *hook;
    Vec targetPos;
    Vec origPos;
    s32 effectModels[2];
    s32 effectIds[2];
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    effectModels[0] = 0x54;
    effectModels[1] = 0x55;
    effectIds[0] = 0x4E;
    effectIds[1] = 0x4A;
    MBDPartnerAttackMotLoad(2);
    effect = MBD6_AttackEffMdlCreate(effectModels[mode - 1]);
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    hook = MBDModelCreate(0x3F, NULL);
    MBDModelDispOff(hook);
    MBDModelHookSet(obj, "item_hook", hook->omObj1->model[0]);
    MBDMotionSet(obj, 0, 2);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDModelDispOff(partner);
    MBDModelDispOn(hook);
    if (mode == 2) {
        MBDPartnerAttackMotSet(obj, 0, 0);
        HuAudFXPlay(0x1D8);
        HuPrcSleep(6);
        Hu3DMotionAttrSet(obj->omObj1->model[0], 0, 4);
        MBDModelMotionStartWait(obj);
        MBDPartnerAttackMotSet(obj, 0, 0);
        HuAudFXPlay(0x1D8);
        HuPrcSleep(6);
        Hu3DMotionAttrSet(obj->omObj1->model[0], 0, 4);
        MBDModelMotionStartWait(obj);
    }
    MBDPartnerAttackMotSet(obj, 0, 0);
    HuAudFXPlay(0x1D8);
    if (flags & 8) {
        MBD6_DodgeCreate(player, target, 0, 20);
    } else {
        HuPrcSleep(9);
        HuAudFXPlay(0x1D7);
        if (mode == 2) {
            HuAudFXPlay(0x1F2);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        // The do-while(0) block is needed to match register allocation.
        do {
            MBDModelBillboardSet(effect);
            MBD6_AttackEffMdlDispOn(effect, mid);
        } while (0);
        MBDEffMdlCreate(effectIds[mode - 1], &midPos, 0, 2.0f);
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
        }
    }
    MBDModelMotionWait(obj);
    MBDModelDispOff(hook);
    MBDVecDirGet(&obj->coords, &origPos, &obj->rot);
    MBDMotionSet(obj, 0, 2);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDModelKill(hook);
    MBDModelKill(effect);
    MBDModelKill(partner);
    MBDPartnerAttackMotKill();
}

void MBD6_BomheiAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    Object *orig;
    Object *extra;
    f32 angle;
    Vec targetPos;
    Vec offset;
    s32 effectModels[2];
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    effectModels[0] = 0x4F;
    effectModels[1] = 0x52;
    effect = MBD6_AttackEffMdlCreate(effectModels[mode - 1]);
    HuVecCopyXYZ(&effect->scale, 2.0f, 2.0f, 2.0f);
    if (mode == 2) {
        HuPrcVSleep();
        extra = MBD6_AttackEffMdlCreate(0x5B);
        HuPrcVSleep();
    }
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    MBDPartnerAttackMotLoad(3);
    if (mode == 2) {
        MBDModelDispOff(obj);
        orig = obj;
        obj = MBDModelCreate(0x27, NULL);
        HuVecCopy3F(&obj->coords, &orig->coords);
        HuVecCopy3F(&obj->rot, &orig->rot);
    }
    MBDPartnerAttackMotShiftSet(obj, 0, 0, 5, 2);
    HuAudFXPlay(0x1DC);
    HuPrcSleep(20);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 2.0f);
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
        MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
        angle = MBDVecAngleGet(&obj->rot) + 180.0f;
        offset.x = sindf(angle) * 9.0f;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 9.0f;
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 2.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 2.0f));
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        HuAudFXPlay(0x256);
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
        MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
        MBDModelJumpSet(obj, 7.5f, -0.825f);
        HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &targetPos, &obj->coords, 15));
        HuPrcChildWatch();
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
        MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
        angle = MBDVecAngleGet(&obj->rot) + 180.0f;
        offset.x = sindf(angle) * 6.0f / 2.0f;
        offset.y = 0.0f;
        offset.z = cosdf(angle) * 6.0f / 2.0f;
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 2.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 2.0f));
        HuAudFXPlay(0x256);
        HuPrcChildWatch();
        MBDModelDispOff(partner);
    }
    MBDModelDispOff(obj);
    obj->coords.y += obj->velocity.x;
    mid = &midPos;
    HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
    HuVecMulScalar(mid, 0.5f, mid);
    if (mode == 2) {
        MBD6_AttackEffMdlDispOn(extra, &obj->coords);
        Hu3DMotionSpeedSet(extra->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBD6_AttackEffMdlDispOn(effect, mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (mode == 1) {
        MBD6_AttackEffMdlDispOn(effect, &midPos);
        HuAudFXPlay(0x1DD);
    } else {
        HuAudFXPlay(0x1DE);
    }
    MBDBackTPLvlSet(0xFF);
    HuPrcVSleep();
    MBDBackTPLvlSet(0x40);
    MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
    MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
    HuPrcSleep(30);
    if (mode == 2) {
        MBDModelKill(obj);
        MBDModelKill(extra);
    }
    MBDModelKill(partner);
    MBDModelKill(effect);
    MBDPartnerAttackMotKill();
}

void MBD6_WhompAttackExec(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
    MBDPartnerAttackMotLoad(5);
    if (arg5 == 2) {
        HuAudFXPlay(0x25D);
        MBDPartnerAttackMotSet(arg2, 0, 0);
        MBDModelMotionWait(arg2);
    }
    HuAudFXPlay(0x25D);
    MBDPartnerAttackMotSet(arg2, 0, 0);
    MBDModelMotionWait(arg2);
    MBDMotionSet(arg2, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDPartnerAttackMotKill();
}

void MBD6_DossunAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *smoke;
    s32 model;
    s32 i;
    f32 height;
    f32 scaleY;
    f32 angle;
    Vec targetPos;
    Vec origPos;
    Vec delta;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    model = -1;
    if (target == NULL) {
        HuPrcSleep(20);
        return;
    }
    effect = MBD6_AttackEffMdlCreate(0x55);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        obj->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, 20.0f);
    HuVecSubtract(&delta, &targetPos, &obj->coords);
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &targetPos, &obj->coords, 10));
    for (i = 20; i > 0; i--) {
        MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, i);
        HuPrcVSleep();
    }
    MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    HuPrcSleep(5);
    for (height = 20.0f; height >= 0.0f; height -= 10.0f) {
        obj->velocity.x = height;
        HuPrcVSleep();
    }
    MBDEffBurstNoLayerCreate(0x5A, 1, &obj->coords, 1.0f, 0);
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    HuPrcSleep(10);
    if (target != NULL) {
        HuPrcSleep(10);
        for (height = 0.0f; height <= 24.0f; height += 2.0f) {
            obj->velocity.x = height;
            HuPrcVSleep();
        }
        HuVecCopy3F(&targetPos, &target->coords);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcSleep(10);
        if (flags & 8) {
            if (mode == 1) {
                MBD6_DodgeCreate(player, target, 0, 55);
            } else {
                MBD6_DodgeCreate(player, target, 0, 120);
            }
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                obj->velocity.x = height;
                HuPrcVSleep();
            }
            if (mode == 1) {
                HuAudFXPlay(0x1E7);
                HuAudFXPlay(0x1E8);
            } else {
                HuAudFXPlay(0x1E9);
            }
            MBDEffBurstNoLayerCreate(0x5A, 1, &obj->coords, 1.0f, 0);
        } else {
            for (height = 24.0f; height >= 0.0f; height -= 8.0f) {
                obj->velocity.x = height;
                scaleY = height / 24.0f;
                if (scaleY > 1.0f) {
                    scaleY = 1.0f;
                }
                if (scaleY < 0.1f) {
                    scaleY = 0.1f;
                }
                HuVecCopyXYZ(&target->scale, 1.0f, scaleY, 1.0f);
                HuPrcVSleep();
            }
            if (mode == 1) {
                HuAudFXPlay(0x1F3);
            } else {
                HuAudFXPlay(0x1E9);
            }
            HuVecCopyXYZ(&target->scale, 1.0f, 0.1f, 1.0f);
            MBD6_BomheiMdlSwap(targetPlayer, 2);
            if (mode == 1) {
                MBDModelBillboardSet(effect);
                MBD6_AttackEffMdlDispOn(effect, &target->coords);
                MBDEffMdlCreate(0x47, &target->coords, NULL, 1.0f);
            } else {
                smoke = MBDModelCreate(0x5A, NULL);
                MBDModelMotionKillCreate(smoke);
                HuVecCopy3F(&smoke->coords, &obj->coords);
                model = MBDEffExplodeCreate(0xB0023, "obj1");
                MBDEffExplodePosSet(model, &obj->coords);
            }
        }
        if (mode == 1) {
            MBD6_CameraShakeCreate(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, MBD6_CameraShakeCreate(5, 2));
            HuPrcChildWatch();
            for (i = 0; i < 3; i++) {
                for (height = 0.0f; height < 9.0f; height += 3.0f) {
                    obj->velocity.x = height;
                    HuPrcVSleep();
                }
                for (; height >= 0.0f; height -= 4.5f) {
                    obj->velocity.x = height;
                    HuPrcVSleep();
                }
                if (i == 2) {
                    HuAudFXPlay(0x1F3);
                    MBDModelBillboardSet(effect);
                    MBD6_AttackEffMdlDispOn(effect, &obj->coords);
                    MBDEffMdlCreate(0x47, &obj->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    smoke = MBDModelCreate(0x5A, NULL);
                    MBDModelMotionKillCreate(smoke);
                    HuVecCopy3F(&smoke->coords, &obj->coords);
                }
                HuPrcChildLink(process, MBD6_CameraShakeCreate(5, 2));
                HuPrcChildWatch();
            }
            angle = MBDVecAngleGet(&obj->rot);
            for (i = 0; i < 30; i++) {
                obj->rot.x = sindf(angle + sindf(i * 60) * (30 - i));
                obj->rot.z = cosdf(angle + sindf(i * 60) * (30 - i));
                HuPrcVSleep();
            }
            obj->rot.x = sindf(angle);
            obj->rot.z = cosdf(angle);
            HuPrcSleep(10);
        }
    }
    for (height = 0.0f; height <= 24.0f; height += 2.0f) {
        obj->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, 20.0f);
    HuVecSubtract(&delta, &origPos, &obj->coords);
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &origPos, &obj->coords, 20));
    for (i = 20; i > 0; i--) {
        MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, i);
        HuPrcVSleep();
    }
    MTX_ROTX(Hu3DData[obj->omObj1->model[0]].mtx, 0.0f);
    HuPrcSleep(5);
    for (height = 24.0f; height >= 0.0f; height -= 6.0f) {
        obj->velocity.x = height;
        HuPrcVSleep();
    }
    HuAudFXPlay(0x1E7);
    HuAudFXPlay(0x1E8);
    MBDEffBurstNoLayerCreate(0x5A, 1, &obj->coords, 1.0f, 0);
    MBDPartnerPosFix(playerIndex);
    if (target != NULL && !(flags & 8)) {
        MBD6_BomheiMdlSwap(targetPlayer, 3);
        angle = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&target->scale, 1.0f, sindf(i) * angle + 1.0f, 1.0f);
            angle -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&target->scale, 1.0f, 1.0f, 1.0f);
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        MBDCoinScatterCreate(target, -1, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
    }
    MBDModelKill(effect);
    if (model != -1) {
        while (!MBDEffExplodeEndCheck(model)) {
            HuPrcVSleep();
        }
        MBDEffExplodeKill(model);
    }
}

void MBD6_TeresaCounterExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Vec targetPos;
    Vec origPos;
    Vec dir;
    Vec effectPos;
    s32 steps;
    s32 i;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    HuAudFXPlay(0x1F4);
    MBDMotionSet(obj, 0, 2);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 0.0f);
    HuVecSubtract(&dir, &obj->coords, &targetPos);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    targetPos.y -= 5.0f;
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    steps = HuVecGetLength3F(&dir) / 3.0f;
    obj->flags |= 1;
    if (flags & 8) {
        MBD6_DodgeCreate(player, target, HuVecGetLength3F(&dir) / 3.0f, 20);
        for (i = 0; i < steps; i++) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], ~((i * 128) / steps));
            HuVecCopyXYZ(&obj->scale, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f);
            HuPrcVSleep();
        }
        for (i = 128; i >= 0; i -= 10) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
    } else {
        for (i = 0; i < steps; i++) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], ~((i * 128) / 10));
            HuVecCopyXYZ(&obj->scale, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f, i * 2.0f / steps + 1.0f);
            HuPrcVSleep();
        }
        HuVecCopy3F(&effectPos, &obj->coords);
        effectPos.y += 10.0f;
        MBDEffMdlCreate(0x44, &effectPos, 0, 1.0f);
        HuPrcSleep(10);
        MBDEffMdlCreate(0x44, &effectPos, 0, 1.0f);
        HuPrcSleep(12);
        for (i = 128; i >= 0; i -= 10) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdCounterResult & 8, mbdAttackTargetIdParam);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdCounterResult & 1, -1);
        }
    }
    if (!(mbdAttackResult & 0x10)) {
        MBDPartnerPosFix(playerIndex);
        HuVecCopyXYZ(&obj->scale, 1.0f, 1.0f, 1.0f);
        for (i = 0; i < 256; i += 10) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            HuPrcVSleep();
        }
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 255);
    }
}

void MBD6_TeresaAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    s32 sound;
    Vec nearPos;
    Vec origPos;
    Vec targetPos;
    Vec rot;
    Vec midPos;
    Vec *mid;
    f32 baseAngle;
    f32 angle;
    s32 i;
    s32 iAngle;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    sound = -1;
    if (mode & 0x10) {
        MBD6_TeresaCounterExec(playerIndex, targetPlayer, obj, target, flags, 1);
        return;
    }
    mode &= ~0x10;
    MBDMotionSet(obj, 0, 2);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
    MBD6_AttackTargetPosGet(obj, target, player, &nearPos, &origPos, 8.0f);
    MBD6_AttackCameraFocusSet();
    for (i = 0; i < 10; i++) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], ~((i * 255) / 10));
        Hu3DModelTPLvlSet(obj->omObj2->model[0], ~((i * 255) / 10));
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
    HuPrcChildLink(process, MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f));
    HuPrcChildWatch();
    if (mode == 2) {
        sound = HuAudFXPlay(0x1DF);
        MBDVecDirGet(&mbdAttackCameraPos, &obj->coords, &rot);
        baseAngle = MBDVecAngleGet(&rot);
        iAngle = baseAngle + 90.0f;
        angle = iAngle;
        HuVecCopyXYZ(&obj->coords, mbdAttackCameraPos.x + sindf(angle) * 8.0f, mbdAttackCameraPos.y, mbdAttackCameraPos.z + cosdf(angle) * 8.0f);
        MBDVecDirGet(&obj->coords, &mbdAttackCameraPos, &obj->rot);
        for (i = 0; i <= 128; i += 20) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
        HuPrcVSleep();
        iAngle = baseAngle + -90.0f;
        angle = iAngle;
        HuVecCopyXYZ(&obj->coords, mbdAttackCameraPos.x + sindf(angle) * 8.0f, mbdAttackCameraPos.y, mbdAttackCameraPos.z + cosdf(angle) * 8.0f);
        MBDVecDirGet(&obj->coords, &mbdAttackCameraPos, &obj->rot);
        for (i = 0; i <= 128; i += 20) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        HuAudFXPlay(0x257);
        for (i = 128; i >= 0; i -= 20) {
            Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
            Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
            HuPrcVSleep();
        }
        Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
        HuPrcVSleep();
    }
    HuVecCopy3F(&obj->coords, &nearPos);
    MBDVecDirGet(&obj->coords, &mbdAttackCameraPos, &obj->rot);
    for (i = 0; i < 255; i += 10) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
        HuPrcVSleep();
        if (i == 160) {
            if (sound != -1) {
                HuAudFXStop((s16)sound);
            }
            HuAudFXPlay(0x257);
        }
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 255);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 255);
    HuPrcSleep(mode == 1 ? 10 : 3);
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &targetPos, &obj->coords, 3));
    if (flags & 8) {
        if (mode == 1) {
            MBD6_DodgeCreate(player, target, 0, 20);
        } else {
            MBD6_DodgeCreate(player, target, 0, 40);
        }
        HuPrcChildWatch();
        if (mode == 2) {
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &nearPos, &obj->coords, 10));
            HuPrcChildWatch();
            HuPrcSleep(5);
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &targetPos, &obj->coords, 3));
            HuPrcChildWatch();
        }
    } else {
        HuPrcChildWatch();
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += 3.0f;
        MBDEffMdlCreate(0x59, &midPos, 0, 1.0f);
        HuAudFXPlay(0x1E0);
        if (mode == 2) {
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &nearPos, &obj->coords, 10));
            HuPrcChildWatch();
            HuPrcSleep(5);
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &targetPos, &obj->coords, 3));
            HuPrcChildWatch();
            MBDEffMdlCreate(0x59, &midPos, 0, 1.0f);
            HuAudFXPlay(0x1E0);
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            HuAudFXPlay((mbdAttackResult & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((mbdAttackResult & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&obj->coords, &nearPos, &obj->coords, 10));
    HuPrcChildWatch();
    for (i = 0; i < 10; i++) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], ~((i * 255) / 10));
        Hu3DModelTPLvlSet(obj->omObj2->model[0], ~((i * 255) / 10));
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
    MBDPartnerPosFix(playerIndex);
    for (i = 0; i < 256; i += 10) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 255);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 255);
}

void MBD6_BlizzardAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *extra;
    Object *effect;
    Object *partner;
    Vec targetPos;
    Vec pos;
    Object *pieces[16];
    Vec effectPos;
    Vec startPos;
    Vec dir;
    Vec *vel;
    s32 i;
    s32 count;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    extra = NULL;
    MBDPartnerAttackMotLoad(10);
    if (mode == 2) {
        extra = MBD6_AttackEffMdlCreate(0x51);
        HuVecCopyXYZ(&extra->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    effect = MBD6_AttackEffMdlCreate(0x4C);
    HuVecCopyXYZ(&effect->scale, 2.0f, 2.0f, 2.0f);
    HuPrcVSleep();
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
    }
    MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
    partner = MBDModelCreate(0x57, NULL);
    MBDModelDispOff(partner);
    HuVecCopy3F(&partner->coords, &obj->coords);
    partner->coords.y += 5.0f;
    targetPos.y += 5.0f;
    if (mode == 2) {
        HuVecCopyXYZ(&partner->scale, 2.0f, 2.0f, 2.0f);
        for (i = 0; i < 16; i++) {
            pieces[i] = MBDModelLinkCreate(partner);
            HuVecCopy3F(&pieces[i]->coords, &partner->coords);
            MBDModelDispOff(pieces[i]);
            HuVecCopyXYZ(&pieces[i]->scale, 0.5f, 0.5f, 0.5f);
        }
    }
    MBDPartnerAttackMotSet(obj, 0, 0);
    HuPrcSleep(20);
    MBDModelDispOn(partner);
    MBDModelJumpSet(partner, 3.0f, -0.18f);
    HuPrcChildLink(process, MBDPlayerPosMoveCreate(&partner->coords, &targetPos, &partner->coords, 30));
    if (mode == 2) {
        for (i = 0; i < 16; i++) {
            HuVecCopy3F(&pos, &targetPos);
            pos.x += MBDRand(100.0f) / 15.0f - 3.3f;
            pos.y += MBDRand(100.0f) / 15.0f - 3.3f;
            pos.z += MBDRand(100.0f) / 15.0f - 3.3f;
            MBDModelJumpSet(pieces[i], 3.0f, -0.18f);
            HuPrcChildLink(process, MBDPlayerPosMoveCreate(&pieces[i]->coords, &pos, &pieces[i]->coords, 30));
        }
    }
    HuAudFXPlay(0x1E1);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraTimeMoveCreate(target, player, flags, 30);
    if (flags & 8) {
        HuVecCopy3F(&effectPos, &target->coords);
        effectPos.y += 5.0f;
        MBD6_DodgeCreate(player, target, 25, 40);
        if (mode == 1) {
            HuPrcSleep(32);
        } else {
            HuPrcSleep(20);
            MBDModelDispOff(partner);
            HuVecCopy3F(&startPos, &partner->coords);
            startPos.y += partner->velocity.x;
            HuVecSubtract(&dir, &target->coords, &startPos);
            HuVecMulScalar(&dir, 0.05f, &dir);
            MBDEffMdlCreateEx(0x4E, &startPos, &dir, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                MBDModelDispOn(pieces[i]);
                pieces[i]->velocity.z = MBDRand(100.0f) / 1000.0f + -0.18f - 0.05f;
                pieces[i]->velocity.y += MBDRand(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
            HuPrcChildWatch();
        }
        MBD6_AttackEffMdlDispOn(effect, &effectPos);
        if (mode == 2) {
            MBD6_AttackEffMdlDispOn(extra, &effectPos);
        }
    } else {
        if (mode != 1) {
            HuPrcSleep(20);
            MBDModelDispOff(partner);
            HuVecCopy3F(&effectPos, &partner->coords);
            effectPos.y += partner->velocity.x;
            if (flags & 1) {
                vel = &dir;
                HuVecSubtract(vel, &target->coords, &effectPos);
            } else {
                vel = &dir;
                HuVecSubtract(vel, &player->player_obj->coords, &effectPos);
            }
            HuVecMulScalar(vel, 0.05f, vel);
            MBDEffMdlCreateEx(0x4E, &effectPos, &dir, 1.5f, 0, 2.4f);
            for (i = 0; i < 16; i++) {
                MBDModelDispOn(pieces[i]);
                pieces[i]->velocity.z = MBDRand(100.0f) / 1000.0f + -0.18f - 0.05f;
                pieces[i]->velocity.y += MBDRand(100.0f) / 100.0f;
            }
            HuAudFXPlay(0x1E2);
        }
        HuPrcChildWatch();
        if (flags & 1) {
            HuVecCopy3F(&effectPos, &target->coords);
        } else {
            HuVecCopy3F(&effectPos, &player->player_obj->coords);
        }
        effectPos.y += 5.0f;
        MBD6_AttackEffMdlDispOn(effect, &effectPos);
        if (mode == 2) {
            MBD6_AttackEffMdlDispOn(extra, &effectPos);
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            HuAudFXPlay((mbdAttackResult & 8) ? 0x1CE : 0x1CD);
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (!(flags & 1)) {
                HuAudFXPlay((mbdAttackResult & 1) ? 0x1CE : 0x1CD);
            }
        }
    }
    if (mode == 2) {
        while (TRUE) {
            count = 0;
            for (i = 0; i < 16; i++) {
                if (!MBDModelJumpCheck(pieces[i])) {
                    MBDModelDispOff(pieces[i]);
                    count++;
                }
            }
            if (i == count) {
                break;
            }
            HuPrcVSleep();
        }
        for (i = 0; i < 16; i++) {
            MBDModelKill(pieces[i]);
        }
    }
    MBDModelKill(partner);
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    HuPrcSleep(30);
    MBDModelKill(effect);
    if (mode == 2) {
        MBDModelKill(extra);
    }
    MBDPartnerAttackMotKill();
}

void MBD6_KoopaJrChangeExec(Object *obj, s32 swap) {
    Object *model;
    f32 scale;
    f32 angle;

    if (swap) {
        mbd6_koopaMdl = MBDModelCreate(8, mbd6_koopaMot);
        MBDModelTempAllocFree(mbd6_koopaMdl);
        MBDModelDispOff(mbd6_koopaMdl);
    } else {
        HuPrcSleep(3);
    }
    model = MBDModelCreate(0x21, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &obj->coords);
    model->coords.y += 5.0f;
    HuAudFXPlay(0x1E3);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = scale + 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (swap) {
        HuVecCopy3F(&mbd6_koopaMdl->coords, &obj->coords);
        HuVecCopy3F(&mbd6_koopaMdl->rot, &obj->rot);
        MBDModelDispOn(mbd6_koopaMdl);
        MBDModelDispOff(obj);
    }

    for (; scale >= 1.0f; scale = scale - 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBDModelKill(model);
}

void MBD6_KoopaJrChangeEndExec(Object *obj) {
    Object *model;
    f32 scale;
    f32 angle;

    model = MBDModelCreate(0x21, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &mbd6_koopaMdl->coords);
    model->coords.y += 5.0f;
    if (GwSystem.current_board_index == 6) {
        HuAudFXPlay(0x1E3);
    }

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = scale + 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    HuVecCopy3F(&obj->coords, &mbd6_koopaMdl->coords);
    HuVecCopy3F(&obj->rot, &mbd6_koopaMdl->rot);
    MBDModelKill(mbd6_koopaMdl);
    MBDModelDispOn(obj);
    obj->flags &= ~1;

    for (; scale >= 1.0f; scale = scale - 1.0) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBDModelKill(model);
}

void MBD6_KoopaFireObjCreate(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    Hu3DSprModelInit(0x1A);
    mbd6_koopaFireObj = omAddObj(0x1F4, 0, 0, -1, MBD6_KoopaFireObjMain);
    data = mbd6_koopaFireObj->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
    sprData = DataRead(0xB0047);
    for (i = 0; i < ARRAY_COUNT(data->sprId); i++) {
        if (i == 0) {
            data->sprId[0] = Hu3DSprModelCreate(sprData, 0x1A0D, 8);
        } else {
            data->sprId[i] = Hu3DSprModelLink(data->sprId[0], 8);
        }
        Hu3DSprModelAttrSet(data->sprId[i], 6, 0x180);
        data->modelId[i] = Hu3DSprModelData[data->sprId[i]].modelId;
        Hu3DSprModelColorSet(data->sprId[i], 0xFF, 0x40, 8);
        Hu3DSprModelTPLvlSet(data->sprId[i], 0xC8);
        Hu3DModelObjAttrSet(data->modelId[i], 0x70000000, 0x70000000);
    }
    DataClose(sprData);
    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        data->active[i] = 0;
    }
    mbd6_koopaFireObj->work[0] = 0;
    data->spawnTimer = 0;
}

void MBD6_KoopaFireObjMain(omObjData *object) {
    UnkDuelObjData *data = object->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        if (data->active[i] != 0) {
            data->pos[i].x += data->vel[i].x;
            data->pos[i].y += data->vel[i].y;
            data->pos[i].z += data->vel[i].z;
            if (data->pos[i].y < 0.0f) {
                data->pos[i].y = 0.0f;
            }
            Hu3DModelPosSet(data->modelId[i], data->pos[i].x, data->pos[i].y, data->pos[i].z);
            data->life[i] -= 2.0f;
            if (data->life[i] <= 0.0f) {
                data->active[i] = 0;
                Hu3DModelAttrSet(data->modelId[i], 4, 4);
                Hu3DSprModelAttrSet(data->sprId[i], 0, 0x80);
            }
            data->scale[i] += 0.02f;
            if (data->scale[i] >= 3.0f) {
                data->scale[i] = 3.0f;
            }
            Hu3DModelScaleSet(data->modelId[i], data->scale[i], data->scale[i], data->scale[i]);
        }
    }
    if (object->work[0] == 1) {
        if (data->spawnTimer == 0) {
            for (i = 0; i < ARRAY_COUNT(data->active); i++) {
                if (data->active[i] == 0) {
                    break;
                }
            }
            if (i != ARRAY_COUNT(data->active)) {
                data->active[i] = 1;
                data->spawnTimer = 1;
                data->vel[i].x = mbd6_koopaMdl->rot.x;
                data->vel[i].y = -0.8f;
                data->vel[i].z = mbd6_koopaMdl->rot.z;
                MBDVecNormalize(&data->vel[i]);
                data->vel[i].x *= 2.0f;
                data->vel[i].y *= 2.0f;
                data->vel[i].z *= 2.0f;
                data->pos[i].x = mbd6_koopaMdl->rot.x * 10.0f + mbd6_koopaMdl->coords.x;
                data->pos[i].z = mbd6_koopaMdl->rot.z * 10.0f + mbd6_koopaMdl->coords.z;
                data->pos[i].y = mbd6_koopaMdl->coords.y + 6.0f;
                data->life[i] = 15.0f;
                data->scale[i] = 0.1f;
                Hu3DModelAttrSet(data->modelId[i], 4, 0);
                Hu3DSprModelReset(data->sprId[i]);
                Hu3DModelPosSet(data->modelId[i], data->pos[i].x, data->pos[i].y, data->pos[i].z);
                Hu3DModelScaleSet(data->modelId[i], data->scale[i], data->scale[i], data->scale[i]);
                Hu3DModelCameraSet(data->modelId[i], 1);
            }
        } else {
            data->spawnTimer--;
        }
    }
}

s16 MBD6_KoopaFireActiveCheck(void) {
    UnkDuelObjData *data = mbd6_koopaFireObj->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        if (data->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void MBD6_KoopaFireObjKill(void) {
    UnkDuelObjData *data = mbd6_koopaFireObj->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->sprId); i++) {
        Hu3DSprModelKill(data->sprId[i]);
    }
    omDelObj(mbd6_koopaFireObj);
    Hu3DSprModelAllKill();
}

void MBD6_KoopaFireStart(void) {
    mbd6_koopaFireObj->work[0] = 1;
}

void MBD6_KoopaFireStop(void) {
    mbd6_koopaFireObj->work[0] = 0;
}

void MBD6_KoopaJrAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *partner;
    s32 model;
    f32 angle;
    Vec targetPos;
    Vec origPos;
    Vec offset;
    Vec origRot;
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    model = -1;
    MBDPartnerAttackMotLoad(11);
    if (flags != 0) {
        partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
        Hu3DModelLayerSet(partner->omObj1->model[0], 0);
        Hu3DModelRemakeStatic(partner->omObj1->model[0]);
        MBDModelTempAllocFree(partner);
        MBDModelDispOff(partner);
        MBDPartnerAttackMotSet(obj, 0, 0);
        MBDModelMotionWait(obj);
        MBD6_KoopaJrChangeExec(obj, 1);
        HuAudFXPlay(0x29C);
        MBDMotionSet(mbd6_koopaMdl, 0, 2);
        HuVecCopy3F(&origPos, &mbd6_koopaMdl->coords);
        HuVecCopy3F(&origRot, &mbd6_koopaMdl->rot);
        if (target != NULL) {
            HuVecCopy3F(&targetPos, &target->coords);
        } else {
            HuVecCopy3F(&targetPos, &player->player_obj->coords);
        }
        MBDVecDirGet(&mbd6_koopaMdl->coords, &targetPos, &mbd6_koopaMdl->rot);
        angle = MBDVecAngleGet(&mbd6_koopaMdl->rot) + 180.0f;
        if (mode == 1) {
            offset.x = sindf(angle) * 6.0f * 2.5f;
            offset.y = 0.0f;
            offset.z = cosdf(angle) * 6.0f * 2.5f;
        } else {
            offset.x = sindf(angle) * 6.0f * 3.0f;
            offset.y = 0.0f;
            offset.z = cosdf(angle) * 6.0f * 3.0f;
        }
        HuVecAdd(&targetPos, &targetPos, &offset);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbd6_koopaMdl->coords, &targetPos, &mbd6_koopaMdl->coords, 0.5f));
        MBD6_AttackCameraFocusSet();
        MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 0.8f);
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &mbd6_koopaMdl->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 0.5f));
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        if (mode == 1) {
            MBDMotionSet(mbd6_koopaMdl, 3, 0);
            if (flags & 8) {
                MBD6_DodgeCreate(player, target, 0, 50);
            } else {
                HuPrcSleep(8);
                mid = &midPos;
                if (flags & 1) {
                    HuVecAdd(mid, &target->coords, &mbd6_koopaMdl->coords);
                } else {
                    HuVecAdd(mid, &player->player_obj->coords, &mbd6_koopaMdl->coords);
                }
                HuVecMulScalar(mid, 0.5f, mid);
                midPos.y += 5.0f;
                model = MBDEffExplodeCreate(0xB0025, "obj1");
                MBDEffExplodePosSet(model, &midPos);
                MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
                if (flags & 1) {
                    MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
                    if (mbdAttackResult & 8) {
                        HuAudFXPlay(0x1CE);
                    } else {
                        HuAudFXPlay(0x1CD);
                    }
                }
                if (flags & 2) {
                    MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
                    if (!(flags & 1)) {
                        if (mbdAttackResult & 1) {
                            HuAudFXPlay(0x1CE);
                        } else {
                            HuAudFXPlay(0x1CD);
                        }
                    }
                }
            }
            MBDModelMotionWait(mbd6_koopaMdl);
            MBDMotionSet(mbd6_koopaMdl, -1, 2);
            HuPrcSleep(20);
        } else {
            MBDMotionSet(mbd6_koopaMdl, 1, 0);
            HuPrcSleep(30);
            MBD6_KoopaFireObjCreate();
            MBD6_KoopaFireStart();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                MBD6_DodgeCreate(player, target, 0, 50);
            }
            MBDModelMotionWait(mbd6_koopaMdl);
            MBDMotionSet(mbd6_koopaMdl, 2, 2);
            if (!(flags & 8)) {
                MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
                if (flags & 1) {
                    MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
                }
                if (flags & 2) {
                    MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
                }
            }
            HuPrcSleep(30);
            MBD6_KoopaFireStop();
            while (MBD6_KoopaFireActiveCheck()) {
                HuPrcVSleep();
            }
            MBDMotionShiftSet(mbd6_koopaMdl, -1, 0, 5, 2);
            HuPrcSleep(10);
            MBD6_KoopaFireObjKill();
        }
        MBD6_KoopaJrChangeEndExec(obj);
        MBDVecDirGet(&obj->coords, &origPos, &obj->rot);
        MBDMotionSet(obj, 0, 2);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
        HuPrcChildWatch();
        MBDMotionSet(obj, -1, 2);
        MBDPartnerPosFix(playerIndex);
        MBDModelKill(partner);
        if (mode == 1) {
            if (model != -1) {
                while (!MBDEffExplodeEndCheck(model)) {
                    HuPrcVSleep();
                }
                MBDEffExplodeKill(model);
            }
        }
    } else {
        MBDPartnerAttackMotSet(obj, 0, 0);
        MBDModelMotionWait(obj);
        MBD6_KoopaJrChangeExec(obj, 0);
        HuAudFXPlay(0x2A0);
        MBD6_MissMarkCreate(obj);
        HuPrcSleep(10);
        MBDPartnerAttackMotSet(obj, 1, 0);
        MBDModelMotionWait(obj);
        MBDMotionSet(obj, -1, 2);
    }
    MBDPartnerAttackMotKill();
}

void MBD6_WanwanAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player = MBDPlayerGet(targetPlayer);
    Process *process = HuPrcCurrentGet();
    Object *frontPartner = NULL;
    Object *backPartner = NULL;
    s32 frontID = -1;
    s32 backID = -1;
    Object *partner;
    s32 i;
    f32 scale;
    f32 amplitude;
    Vec targetPos;
    Vec origPos;
    Vec delta;
    s32 hitDelays[3] = { -1, -1, -1 };
    Process *spinProcesses[3] = { NULL, NULL, NULL };
    Vec effectPos;

    MBDPartnerAttackMotLoad(8);
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    HuVecCopy3F(&origPos, &obj->coords);
    HuVecCopy3F(&targetPos, &player->player_obj->coords);
    MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
    HuVecSubtract(&delta, &obj->coords, &player->player_obj->coords);
    hitDelays[0] = HuVecGetLength3F(&delta) / 7.0f - 1.0f;
    if (hitDelays[0] < 0) {
        hitDelays[0] = 0;
    }
    if (player->stats.partners.frontID != PARTNER_NONE) {
        frontPartner = MBDPartnerObjGet(targetPlayer, 0);
        frontID = GwPlayer[targetPlayer].stats.partners.frontID;
        HuVecSubtract(&delta, &obj->coords, &frontPartner->coords);
        hitDelays[1] = HuVecGetLength3F(&delta) / 7.0f - 1.0f;
        if (hitDelays[1] < 0) {
            hitDelays[1] = 0;
        }
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        backPartner = MBDPartnerObjGet(targetPlayer, 1);
        backID = GwPlayer[targetPlayer].stats.partners.backID;
        HuVecSubtract(&delta, &obj->coords, &backPartner->coords);
        hitDelays[2] = HuVecGetLength3F(&delta) / 7.0f - 1.0f;
        if (hitDelays[2] < 0) {
            hitDelays[2] = 0;
        }
    }
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, 0, 7.0f);
    if (mode == 1) {
        MBDPartnerAttackMotSet(obj, 0, 2);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 7.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 7.0f));
        for (i = 0; ; i++) {
            if (i == hitDelays[0]) {
                HuAudFXPlay((mbdAttackResult & 1) ? 0x1CE : 0x1E5);
                spinProcesses[0] = MBDModelSpinCreate(player->player_obj, MBDVecAngleGet(&player->player_obj->rot), 50.0f, -1);
                MBDModelJumpSet(player->player_obj, 7.0f, -0.4f);
                hitDelays[0] = -1;
                HuVecCopy3F(&effectPos, &player->player_obj->coords);
                effectPos.y += 5.0f;
                MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
            }
            if (i == hitDelays[1]) {
                HuAudFXPlay((mbdAttackResult & 2) ? 0x1CE : 0x1E5);
                spinProcesses[1] = MBDModelSpinCreate(frontPartner, MBDVecAngleGet(&frontPartner->rot), 50.0f, -1);
                MBDModelJumpSet(frontPartner, 7.0f, -0.4f);
                hitDelays[1] = -1;
                HuVecCopy3F(&effectPos, &frontPartner->coords);
                effectPos.y += 5.0f;
                MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
            }
            if (i == hitDelays[2]) {
                HuAudFXPlay((mbdAttackResult & 4) ? 0x1CE : 0x1E5);
                spinProcesses[2] = MBDModelSpinCreate(backPartner, MBDVecAngleGet(&backPartner->rot), 50.0f, -1);
                MBDModelJumpSet(backPartner, 7.0f, -0.4f);
                hitDelays[2] = -1;
                HuVecCopy3F(&effectPos, &backPartner->coords);
                effectPos.y += 5.0f;
                MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
            }
            if (HuPrcChildGet(process) == NULL) {
                break;
            }
            HuPrcVSleep();
        }
        if (hitDelays[0] != -1) {
            spinProcesses[0] = MBDModelSpinCreate(player->player_obj, MBDVecAngleGet(&player->player_obj->rot), 50.0f, -1);
            MBDModelJumpSet(player->player_obj, 7.0f, -0.4f);
            HuVecCopy3F(&effectPos, &player->player_obj->coords);
            effectPos.y += 5.0f;
            MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
        }
        if (hitDelays[1] != -1) {
            spinProcesses[1] = MBDModelSpinCreate(frontPartner, MBDVecAngleGet(&frontPartner->rot), 50.0f, -1);
            MBDModelJumpSet(frontPartner, 7.0f, -0.4f);
            HuVecCopy3F(&effectPos, &frontPartner->coords);
            effectPos.y += 5.0f;
            MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
        }
        if (hitDelays[2] != -1) {
            spinProcesses[2] = MBDModelSpinCreate(backPartner, MBDVecAngleGet(&backPartner->rot), 50.0f, -1);
            MBDModelJumpSet(backPartner, 7.0f, -0.4f);
            HuVecCopy3F(&effectPos, &backPartner->coords);
            effectPos.y += 5.0f;
            MBDEffMdlCreate(0x4A, &effectPos, NULL, 1.5f);
        }
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
        HuPrcChildWatch();
        MBDMotionSet(obj, -1, 2);
        MBDPartnerPosFix(playerIndex);
        MBDModelKill(partner);
        while (TRUE) {
            if (spinProcesses[0] != NULL && !MBDModelJumpCheck(player->player_obj)) {
                MTX_ROTY(Hu3DData[player->player_obj->omObj1->model[0]].mtx, 0.0f);
                omDelPrcObj(spinProcesses[0]);
                spinProcesses[0] = NULL;
            }
            if (spinProcesses[1] != NULL && !MBDModelJumpCheck(frontPartner)) {
                MTX_ROTY(Hu3DData[frontPartner->omObj1->model[0]].mtx, 0.0f);
                omDelPrcObj(spinProcesses[1]);
                spinProcesses[1] = NULL;
            }
            if (spinProcesses[2] != NULL && !MBDModelJumpCheck(backPartner)) {
                MTX_ROTY(Hu3DData[backPartner->omObj1->model[0]].mtx, 0.0f);
                omDelPrcObj(spinProcesses[2]);
                spinProcesses[2] = NULL;
            }
            if (spinProcesses[0] == NULL && spinProcesses[1] == NULL && spinProcesses[2] == NULL) {
                break;
            }
            HuPrcVSleep();
        }
    } else {
        targetPos.y = 20.0f;
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 7.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 7.0f));
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        obj->velocity.x = obj->coords.y;
        obj->coords.y = 0.0f;
        HuPrcSleep(10);
        HuAudFXPlay(0x1E6);
        for (i = 0; i < 20; i++) {
            HuVecCopyXYZ(&obj->scale, i / 10.0f + 1.0f, i / 10.0f + 1.0f, i / 10.0f + 1.0f);
            HuPrcVSleep();
        }
        HuPrcSleep(10);
        if (frontPartner != NULL) {
            MBDEffMdlDelayCreate(0x4C, &frontPartner->coords, NULL, 2.0f, 4);
        }
        if (backPartner != NULL) {
            MBDEffMdlDelayCreate(0x4C, &backPartner->coords, NULL, 2.0f, 4);
        }
        MBDEffMdlDelayCreate(0x51, &player->player_obj->coords, NULL, 3.0f, 4);
        MBDModelJumpSet(obj, -1.0f, -2.0f);
        player->stat |= 4;
        for (i = 0; i < 6; i++) {
            scale = (10 - i) * 0.9f / 10.0f + 0.1f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, scale, 1.0f);
            if (frontPartner != NULL) {
                HuVecCopyXYZ(&frontPartner->scale, 1.0f, scale, 1.0f);
            }
            if (backPartner != NULL) {
                HuVecCopyXYZ(&backPartner->scale, 1.0f, scale, 1.0f);
            }
            HuPrcVSleep();
        }
        MBD6_BomheiMdlSwap(targetPlayer, 0);
        MBDModelJumpWait(obj);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, MBD6_CameraShakeCreate(10, 1));
        HuPrcChildWatch();
        HuPrcSleep(10);
        for (i = 20; i >= 0; i -= 2) {
            HuVecCopyXYZ(&obj->scale, i / 10.0f + 1.0f, i / 10.0f + 1.0f, i / 10.0f + 1.0f);
            HuPrcVSleep();
        }
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
        HuPrcChildWatch();
        MBDMotionSet(obj, -1, 2);
        MBDPartnerPosFix(playerIndex);
        MBDModelKill(partner);
        MBD6_BomheiMdlSwap(targetPlayer, 1);
        amplitude = 1.0f;
        for (i = 0; i < 1080; i += 54) {
            HuVecCopyXYZ(&player->player_obj->scale, 1.0f, sindf(i) * amplitude + 1.0f, 1.0f);
            if (frontPartner != NULL) {
                HuVecCopyXYZ(&frontPartner->scale, 1.0f, sindf(i) * amplitude + 1.0f, 1.0f);
            }
            if (backPartner != NULL) {
                HuVecCopyXYZ(&backPartner->scale, 1.0f, sindf(i) * amplitude + 1.0f, 1.0f);
            }
            amplitude -= 0.025f;
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
        if (frontPartner != NULL) {
            HuVecCopyXYZ(&frontPartner->scale, 1.0f, 1.0f, 1.0f);
        }
        if (backPartner != NULL) {
            HuVecCopyXYZ(&backPartner->scale, 1.0f, 1.0f, 1.0f);
        }
        player->stat &= ~4;
    }
    MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
    if (flags & 0x20) {
        MBDCoinScatterCreate(player->player_obj, 4, 3, mbdAttackResult & 1, -1);
        if (frontPartner != NULL) {
            MBDCoinScatterCreate(frontPartner, 4, 1, mbdAttackResult & 2, frontID);
        }
        if (backPartner != NULL) {
            MBDCoinScatterCreate(backPartner, 4, 1, mbdAttackResult & 4, backID);
        }
    } else if (flags & 0x10) {
        MBDCoinScatterCreate(player->player_obj, 2, 3, mbdAttackResult & 1, -1);
        if (frontPartner != NULL) {
            MBDCoinScatterCreate(frontPartner, 2, 1, mbdAttackResult & 2, frontID);
        }
        if (backPartner != NULL) {
            MBDCoinScatterCreate(backPartner, 2, 1, mbdAttackResult & 4, backID);
        }
    } else {
        MBDCoinScatterCreate(player->player_obj, 1, 3, mbdAttackResult & 1, -1);
        if (frontPartner != NULL) {
            MBDCoinScatterCreate(frontPartner, 1, 1, mbdAttackResult & 2, frontID);
        }
        if (backPartner != NULL) {
            MBDCoinScatterCreate(backPartner, 1, 1, mbdAttackResult & 4, backID);
        }
    }
    MBDPartnerAttackMotKill();
}

void MBD6_SnifitAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *partner;
    Object *partner2;
    Object *effect1;
    Object *effect2;
    Vec targetPos;
    Vec pos;
    s32 effectIds[2];
    s32 i;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    effectIds[0] = 0x4D;
    effectIds[1] = 0x53;
    partner2 = NULL;
    effect1 = NULL;
    effect2 = NULL;
    MBDPartnerAttackMotLoad(6);
    if (mode == 2) {
        effect1 = MBD6_AttackEffMdlCreate(0x4C);
        HuPrcVSleep();
        effect2 = MBD6_AttackEffMdlCreate(0x53);
        HuPrcVSleep();
    }
    if (target != NULL) {
        HuVecCopy3F(&targetPos, &target->coords);
    } else {
        HuVecCopy3F(&targetPos, &player->player_obj->coords);
    }
    MBDVecDirGet(&obj->coords, &targetPos, &obj->rot);
    partner = MBDModelCreate(0x58, NULL);
    MBDModelDispOff(partner);
    HuPrcVSleep();
    if (mode == 2) {
        partner2 = MBDModelCreate(0x53, NULL);
        MBDModelDispOff(partner2);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2A3);
    MBDPartnerAttackMotShiftSet(obj, mode - 1, 0, 5, 2);
    if (mode == 1) {
        HuPrcSleep(7);
    } else {
        HuPrcSleep(15);
    }
    MBDModelDispOn(partner);
    HuVecCopy3F(&partner->coords, &obj->coords);
    partner->velocity.x = 5.0f;
    MBDModelDispOff(partner);
    MBD6_AttackCameraFocusSet();
    MBDModelDispOn(partner);
    HuPrcChildLink(process, MBDVecSpeedMove2Create(&partner->coords, &targetPos, &partner->coords, 4.0f));
    HuPrcChildLink(process, MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 4.0f));
    HuVecCopy3F(&pos, &obj->rot);
    MBDVecNormalize(&pos);
    HuVecMulScalar(&pos, 6.0f, &pos);
    HuVecAdd(&pos, &pos, &partner->coords);
    pos.y += 5.0f;
    MBDEffMdlCreate(0x4E, &pos, 0, 0.5f);
    if (mode == 2) {
        MBDModelDispOn(partner2);
        Hu3DModelAttrSet(partner2->omObj1->model[0], 0x180, 0);
        Hu3DModelLayerSet(partner2->omObj1->model[0], 0x800);
        HuVecCopy3F(&partner2->coords, &partner->coords);
        partner2->velocity.x = 5.0f;
        HuPrcChildLink(process, MBDVecSpeedMove2Create(&partner2->coords, &targetPos, &partner2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
    } else {
        HuAudFXPlay(0x1D9);
    }
    if (flags & 8) {
        MBD6_DodgeCreate(player, target, 0, 20);
        HuPrcChildWatch();
        MBDCameraFocusModeSet(3);
        MBDModelDispOff(partner);
        if (mode == 2) {
            MBDModelDispOff(partner2);
        }
    } else {
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        if (mode == 2) {
            MBDModelDispOff(partner2);
        }
        if (flags & 1) {
            HuVecCopy3F(&pos, &target->coords);
        } else {
            HuVecCopy3F(&pos, &player->player_obj->coords);
        }
        pos.y += partner->velocity.x;
        if (mode == 1) {
            MBDEffMdlCreate(effectIds[0], &pos, 0, 2.0f);
        } else {
            MBD6_AttackEffMdlDispOn(effect1, &pos);
            HuVecCopyXYZ(&effect1->scale, 2.0f, 2.0f, 2.0f);
            MBD6_AttackEffMdlDispOn(effect2, &pos);
            HuVecCopyXYZ(&effect2->scale, 2.0f, 2.0f, 2.0f);
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            if (mode == 2) {
                if (mbdAttackResult & 8) {
                    HuAudFXPlay(0x1EF);
                } else {
                    HuAudFXPlay(0x1EE);
                }
            } else {
                if (mbdAttackResult & 8) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (mode == 2) {
                if (!(flags & 1)) {
                    if (mbdAttackResult & 1) {
                        HuAudFXPlay(0x1EF);
                    } else {
                        HuAudFXPlay(0x1EE);
                    }
                }
            } else if (!(flags & 1)) {
                if (mbdAttackResult & 1) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (mode == 2) {
            for (i = 0; i < 3; i++) {
                MBDBackTPLvlSet(0xFF);
                HuPrcVSleep();
                MBDBackTPLvlSet(0x40);
                HuPrcVSleep();
            }
        }
    }
    MBDModelKill(partner);
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    if (mode == 2) {
        HuPrcSleep(30);
        MBDModelKill(effect1);
        MBDModelKill(effect2);
        MBDModelKill(partner2);
    }
    MBDPartnerAttackMotKill();
}

void MBD6_PakkunAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
    GW_PLAYER *player;
    Process *process;
    Object *effect;
    Object *partner;
    s32 model;
    Vec targetPos;
    Vec origPos;
    Vec midPos;
    Vec *mid;

    player = MBDPlayerGet(targetPlayer);
    process = HuPrcCurrentGet();
    model = -1;
    effect = NULL;
    if (mode == 1) {
        effect = MBD6_AttackEffMdlCreate(0x45);
    }
    partner = MBDModelCreate(mbd6_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    MBDPartnerAttackMotLoad(7);
    MBDMotionSet(obj, 0, 2);
    MBD6_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 7.5f);
    MBD6_AttackCameraFocusSet();
    MBD6_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDModelDispOff(partner);
    if (mode == 1) {
        MBDPartnerAttackMotSet(obj, 0, 2);
    } else {
        MBDPartnerAttackMotSet(obj, 1, 0);
    }
    if (flags & 8) {
        if (mode == 2) {
            HuPrcSleep(10);
        }
        MBD6_DodgeCreate(player, target, 0, 30);
        if (mode == 1) {
            HuPrcSleep(30);
        } else {
            MBDModelMotionWait(obj);
        }
    } else {
        if (mode == 1) {
            HuPrcSleep(10);
        } else {
            HuPrcSleep(17);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += 5.0f;
        if (mode == 1) {
            MBDEffMdlCreate(0x4B, &midPos, 0, 2.0f);
            MBDModelBillboardSet(effect);
            MBD6_AttackEffMdlDispOn(effect, &midPos);
        } else {
            model = MBDEffExplodeCreate(0xB0024, "obj1");
            MBDEffExplodePosSet(model, &midPos);
            HuAudFXPlay(0x1DB);
            HuAudFXPlay(0x1F1);
        }
        MBDPartnerCameraFocusSet(&mbdAttackCameraPos);
        if (flags & 1) {
            MBDCoinScatterCreate(target, mbdAttackHpDamage, 1, mbdAttackResult & 8, mbdAttackTargetIdParam);
            if (mbdAttackResult & 8) {
                HuAudFXPlay(0x1CE);
            } else {
                HuAudFXPlay(0x1CD);
            }
        }
        if (flags & 2) {
            MBDCoinScatterCreate(player->player_obj, mbdAttackStarDamage, 3, mbdAttackResult & 1, -1);
            if (!(flags & 1)) {
                if (mbdAttackResult & 1) {
                    HuAudFXPlay(0x1CE);
                } else {
                    HuAudFXPlay(0x1CD);
                }
            }
        }
        if (mode == 2) {
            MBDModelMotionWait(obj);
        } else {
            HuPrcSleep(10);
        }
    }
    MBDVecDirGet(&obj->coords, &origPos, &obj->rot);
    MBDMotionSet(obj, 0, 2);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &origPos, &obj->coords, 3.0f));
    MBDModelDispOn(partner);
    Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
    HuVecCopy3F(&partner->coords, &obj->coords);
    MBDVecDirGet(&partner->coords, &origPos, &partner->rot);
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &origPos, &partner->coords, 3.0f));
    HuPrcChildWatch();
    MBDMotionSet(obj, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDModelKill(partner);
    if (mode == 2) {
        if (model != -1) {
            while (!MBDEffExplodeEndCheck(model)) {
                HuPrcVSleep();
            }
            MBDEffExplodeKill(model);
        }
    } else {
        MBDModelKill(effect);
    }
    MBDPartnerAttackMotKill();
}

void MBD6_PartnerAttackInit(void) {
    PartnerFunc attackFuncs[12] = {
        MBD6_NokonokoAttackExec, MBD6_KuriboAttackExec, MBD6_KinopioAttackExec, MBD6_BomheiAttackExec,
        MBD6_TeresaAttackExec, MBD6_WhompAttackExec, MBD6_SnifitAttackExec, MBD6_PakkunAttackExec,
        MBD6_WanwanAttackExec, MBD6_DossunAttackExec, MBD6_BlizzardAttackExec, MBD6_KoopaJrAttackExec,
    };
    PartnerFunc otherFuncs[12] = {
        NULL, NULL, NULL, NULL,
        MBD6_TeresaAttackExec, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL,
    };

    MBDPartnerAttackFuncSet(attackFuncs, otherFuncs);
}

void MBD6_ObjectSetup(void) {
    omInitObjMan(0xA0, 0x50);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBDObjectSetup(0x1D, 0x246, 0);
    MBDMasuOwnerTypeUpdate();
    MBDMasuTypeListCreate();
    MBD6_GateGuyCreate();
    MBD6_PartnerBox1Create();
    MBD6_PartnerBox2Create();
    MBD6_SwitchCreateAll();
    MBD6_PartnerAttackInit();
}

void MBD6_Create(void) {
    if (GwSystem.playMode & 4) {
        HuAudSeqPlay(0x20);
    } else {
        HuAudSeqPlay(0x1E);
    }
    Hu3DCamInit(2);
    MBD6_ObjectSetup();
    MBDMasuEventTblAdd(mbd6_commonEventTbl);
    MBDMasuEventTblAdd(mbd6_specialEventTbl);
    MBDHatenaFuncSet(MBD6Ev_Hatena);
    MBDWalkAttackHookSet(MBD6_WalkAttackHook);
    MBDStart(0);
}

void MBD6_BoardReload(void) {
    Hu3DCamInit(1);
    MBD6_ObjectSetup();
    MBDStart(1);
}

void MBD6_GateGuyScrewProc(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], Hu3DData[mbd6_gateGuyMdl->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = Hu3DModelObjPtrGet(mbd6_gateGuyMdl->omObj1->model[0], "neji");
        angle += mbd6_gateGuyScrewSpeed;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void MBD6_GateGuyBellSet(void) {
    HmfMotionNode *node;

    Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], Hu3DData[mbd6_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd6_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

void MBD6_GateGuyCreate(void) {
    Object *obj = MBDModelCreate(0x34, mbd6_gateGuyMot);

    MBDModelTempAllocFree(obj);
    mbd6_gateGuyMdl = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x1C)->coords);
    MBD6_GateGuyBellSet();
    mbd6_gateGuyScrewProc = omAddPrcObj(MBD6_GateGuyScrewProc, 0xA, 0, 0);
    omPrcSetStatBit(mbd6_gateGuyScrewProc, 0xA0);
}

void MBD6_PartnerBox1Create(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = MBDModelCreate(0x32, NULL);
    MBDModelTempAllocFree(obj);
    mbd6_partnerBox1Mdl = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(mbd6_partnerBox1Masu);
    space2 = MBDMasuGet(mbd6_partnerBox1DirMasu);
    HuVecCopy3F(&obj->coords, &space1->coords);
    MBDVecDirGet(&space1->coords, &space2->coords, &obj->rot);
}

void MBD6Ev_PartnerBox1SwayProc(void) {
    Duel06SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[mbd6_partnerBox1Mdl->omObj1->model[0]].mtx, sindf(angle) * mbd6ev_partnerBox1SwayAmp);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void MBD6Ev_PartnerBox1SwayCreate(Vec *pos) {
    Process *process;
    Duel06SwayWork *work;

    mbd6ev_partnerBox1SwayAmp = 10.0f;
    process = omAddPrcObj(MBD6Ev_PartnerBox1SwayProc, 0xA, 0, 0x40);
    mbd6ev_partnerBox1SwayProc = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SwayWork));
    process->user_data = work;
    if (pos->x <= mbd6_partnerBox1Mdl->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void MBD6Ev_PartnerBox1SwayStop(void) {
    if (mbd6ev_partnerBox1SwayProc != NULL) {
        while (mbd6ev_partnerBox1SwayAmp >= 0.0f) {
            mbd6ev_partnerBox1SwayAmp -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(mbd6ev_partnerBox1SwayProc);
        MTX_ROTZ(Hu3DData[mbd6_partnerBox1Mdl->omObj1->model[0]].mtx, 0.0f);
    }
}

void MBD6Ev_PartnerBox1SquashProc(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    Hu3DMotionAttrSet(mbd6_partnerBox1Mdl->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(mbd6_partnerBox1Mdl->omObj1->model[0], 1.5f);
    MBDModelMotionWait(mbd6_partnerBox1Mdl);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&mbd6_partnerBox1Mdl->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mbd6_partnerBox1Mdl->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MBD6Ev_PartnerBox1SquashCreate(void) {
    omAddPrcObj(MBD6Ev_PartnerBox1SquashProc, 0xA, 0, 0);
}

void MBD6Ev_PartnerBox1MotionReset(void) {
    Hu3DMotionAttrSet(mbd6_partnerBox1Mdl->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(mbd6_partnerBox1Mdl->omObj1->model[0], 1.0f);
}

void MBD6_PartnerBox2Create(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = MBDModelCreate(0x33, NULL);
    MBDModelTempAllocFree(obj);
    mbd6_partnerBox2Mdl = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(mbd6_partnerBox2Masu);
    space2 = MBDMasuGet(mbd6_partnerBox2DirMasu);
    HuVecCopy3F(&obj->coords, &space1->coords);
    MBDVecDirGet(&space1->coords, &space2->coords, &obj->rot);
}

void MBD6Ev_PartnerBox2SwayProc(void) {
    Duel06SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[mbd6_partnerBox2Mdl->omObj1->model[0]].mtx, sindf(angle) * mbd6ev_partnerBox2SwayAmp);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void MBD6Ev_PartnerBox2SwayCreate(Vec *pos) {
    Process *process;
    Duel06SwayWork *work;

    mbd6ev_partnerBox2SwayAmp = 10.0f;
    process = omAddPrcObj(MBD6Ev_PartnerBox2SwayProc, 0xA, 0, 0x40);
    mbd6ev_partnerBox2SwayProc = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06SwayWork));
    process->user_data = work;
    if (pos->x <= mbd6_partnerBox2Mdl->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void MBD6Ev_PartnerBox2SwayStop(void) {
    if (mbd6ev_partnerBox2SwayProc != NULL) {
        while (mbd6ev_partnerBox2SwayAmp >= 0.0f) {
            mbd6ev_partnerBox2SwayAmp -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(mbd6ev_partnerBox2SwayProc);
        MTX_ROTZ(Hu3DData[mbd6_partnerBox2Mdl->omObj1->model[0]].mtx, 0.0f);
    }
}

void MBD6Ev_PartnerBox2SquashProc(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    Hu3DMotionAttrSet(mbd6_partnerBox2Mdl->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(mbd6_partnerBox2Mdl->omObj1->model[0], 1.5f);
    MBDModelMotionWait(mbd6_partnerBox2Mdl);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&mbd6_partnerBox2Mdl->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mbd6_partnerBox2Mdl->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MBD6Ev_PartnerBox2SquashCreate(void) {
    omAddPrcObj(MBD6Ev_PartnerBox2SquashProc, 0xA, 0, 0);
}

void MBD6Ev_PartnerBox2MotionReset(void) {
    Hu3DMotionAttrSet(mbd6_partnerBox2Mdl->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(mbd6_partnerBox2Mdl->omObj1->model[0], 1.0f);
}

void MBD6_SwitchCreate(s16 index) {
    s16 model;
    SpaceData *space;

    if (mbd6_switchMdlTbl[index] == -1) {
        if (index == 0) {
            model = mbd6_switchMdlTbl[0] = Hu3DModelRead(0x130153, 0x4026A9);
            mbd6_switchMot[0] = Hu3DModelReadNum(0x130154);
            Hu3DModelVtxBufMake(model);
            Hu3DMotionModelSetEx(model, mbd6_switchMot[0]);
            Hu3DMotionAttrSet(model, 2, 1);
            Hu3DModelCameraSet(model, 1);
            Hu3DModelDynamicFree(model);
        } else {
            model = mbd6_switchMdlTbl[index] = Hu3DModelLink(mbd6_switchMdlTbl[0]);
        }
        Hu3DModelScaleSet(model, 0.1f, 0.1f, 0.1f);
        space = MBDMasuGet(mbd6_switchMasuTbl[index]);
        Hu3DModelPosSet(model, space->coords.x, space->coords.y, space->coords.z);
        Hu3DModelRotSet(model, 0.0f, mbd6_switchRotTbl[index], 0.0f);
    }
}

void MBD6_SwitchCreateAll(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        mbd6_switchMdlTbl[i] = -1;
        MBD6_SwitchCreate(i);
    }
    if (GwSystem.boardData.halfWordBytes[0] == 0) {
        Hu3DMotionTimeSet(mbd6_switchMdlTbl[0], Hu3DMotion[Hu3DData[mbd6_switchMdlTbl[0]].motId].unk02);
    } else {
        Hu3DMotionTimeSet(mbd6_switchMdlTbl[0], 0.0f);
    }
}

void MBD6Ev_SwitchPressExec(void) {
    HuAudFXPlay(0x1ED);
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        Hu3DMotionAttrSet(mbd6_switchMdlTbl[0], 5, 0);
        while (Hu3DData[mbd6_switchMdlTbl[0]].motTime != Hu3DMotion[Hu3DData[mbd6_switchMdlTbl[0]].motId].unk02) {
            HuPrcVSleep();
        }
    } else {
        Hu3DMotionAttrSet(mbd6_switchMdlTbl[0], 1, 4);
        while (Hu3DData[mbd6_switchMdlTbl[0]].motTime != 0.0f) {
            HuPrcVSleep();
        }
    }
    HuPrcSleep(5);
}

s32 MBD6_ComPartnerRefuseRateGet(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBDPlayerGet(sys->current_player_index ^ 1);
    s32 curPlayer = sys->current_player_index;
    s32 chance = (5 - GwPlayer[curPlayer].star) * 10;

    if (mbWalkNum < 6) {
        if (curPlayer == 0) {
            if (GwSystem.boardData.halfWordBytes[curPlayer] == 0) {
                s32 dist = player->cidx - 18;

                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            } else {
                s32 dist = 18 - player->cidx;

                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            }
        } else {
            if (GwSystem.boardData.halfWordBytes[0] == 0) {
                s32 dist = player->cidx - 6;

                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            } else {
                s32 dist = 6 - player->cidx;

                if (dist == mbWalkNum) {
                    chance = 0;
                }
                if (dist < mbWalkNum) {
                    chance += 20;
                }
            }
        }
    }
    return chance;
}

s32 MBD6_ComPartnerSlotRateGet(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s16 partnerValues[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };

    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

s32 MBD6_ComPartnerIdRefuseRateGet(s32 index) {
    s16 shakeAngles[12] = { 70, 10, 50, 20, 30, 90, 10, 10, 20, 80, 60, 30 };

    return shakeAngles[index];
}

s32 MBD6_ComPartnerRouletteDecide(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s32 partner = -1;
    s32 roll = MBDRand(10.0f);
    s32 i;

    switch (player->cpu_difficulty) {
        case 0:
        case 1:
            break;
        case 2:
        case 3:
            if (player->stats.partners.frontID != PARTNER_NONE || player->stats.partners.backID != PARTNER_NONE) {
                if (roll < 6) {
                    if (player->stats.partners.frontID != PARTNER_NONE) {
                        partner = player->stats.partners.frontID;
                    }
                    if (player->stats.partners.backID != PARTNER_NONE) {
                        partner = player->stats.partners.backID;
                    }
                    break;
                }
                if (roll < 8) {
                    for (i = 0; mbd6_comPartnerTbl[i * 2] != -1; i++) {
                        if (mbd6_comPartnerTbl[i * 2 + 1] > MBDRand(100.0f)) {
                            break;
                        }
                    }
                    partner = mbd6_comPartnerTbl[i * 2];
                    break;
                }
            }
            for (i = 0; mbd6_comPartnerChrTbl[player->chr][i * 2] != -1; i++) {
                if (mbd6_comPartnerChrTbl[player->chr][i * 2 + 1] > MBDRand(100.0f)) {
                    break;
                }
            }
            partner = mbd6_comPartnerChrTbl[player->chr][i * 2];
            break;
    }
    if (partner == -1) {
        partner = MBDRand(12.0f);
    }
    if ((u32)partner >= 12) {
        partner = 0;
    }
    return partner;
}

void MBD6Ev_PartnerRouletteWinColorProc(void) {
    Duel06WinColorWork *work = HuPrcCurrentGet()->user_data;
    s32 unused[2]; // Unreferenced, but present in the original stack frame
    s32 window;
    u8 red = 0x43;
    s16 green;
    u8 blue;
    s32 value;
    f32 blueAngle = 0.0f;
    f32 greenAngle = 90.0f;

    window = work->window;
    HuWinBGColSet(work->window, 0x43, 0x80, 1);
    while (TRUE) {
        if (mbd6ev_partnerRouletteColorF != 0) {
            value = (s16)(sindf(greenAngle) * 128.0f);
            if (value < 0) {
                value = -value;
            }
            green = value;
            greenAngle += 6.0f;
            if (greenAngle > 360.0f) {
                greenAngle -= 360.0f;
            }
            value = (s16)(sindf(blueAngle) * 64.0f);
            blue = (value < 0) ? -value : value;
            blueAngle += 3.0f;
            if (blueAngle > 360.0f) {
                blueAngle -= 360.0f;
            }
            HuWinBGColSet(window, red, green & 0xFF, blue);
        }
        HuPrcVSleep();
    }
}

void MBD6Ev_PartnerRouletteProc(void) {
    s16 pos[3][2] = { { 160, -80 }, { 160, -160 }, { 160, -80 } };
    s32 files[6] = { 0x13011C, 0x13011F, 0x13011E, 0x13011D, 0x130120, 0x13011E };
    u8 order[32]; // Only 12 are used; the size matches the original stack frame.
    s32 player;
    DuelHelpWin *msgWindow;
    s16 window;
    Process *colorProcess;
    s32 state;
    s32 cpuPartner;
    Duel06WinColorWork *colorWork;
    UnkBoard4 *spr;
    void *data;
    s32 i;
    s32 angle;
    s32 count;
    u8 last;
    s32 max;
    s32 delay;

    player = ((Duel06PartnerRouletteWork *)HuPrcCurrentGet()->user_data)->player;
    colorProcess = NULL;
    cpuPartner = -1;
    mbItemBtnF = 0;
    if (player == 0) {
        state = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        state = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    window = HuWinCreate(60, -160, 200, 160, 0, 0);
    HuWinBGColSet(window, 0x43, 5, 1);
    HuWinBGTPLvlSet(window, 0xC0);
    if (state == 2) {
        colorProcess = omAddPrcObj(MBD6Ev_PartnerRouletteWinColorProc, 10, 0, 0x40);
        colorWork = HuMemMemoryAlloc(colorProcess->heap, sizeof(Duel06WinColorWork));
        colorProcess->user_data = colorWork;
        colorWork->window = window;
    }
    spr = MBDSprGrpCreate(3, 0);
    for (i = 0; i < 3; i++) {
        data = DataRead(files[player * 3 + i]);
        spr->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(spr->unk_0A, i, spr->unk_0C[i], 0);
        HuSprPriSet(spr->unk_0A, i, i + 1);
        HuSprAttrSet(spr->unk_0A, i, 0);
        HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1]);
        DataClose(data);
        if (i == 2) {
            HuSprBankSet(spr->unk_0A, 2, MBDRand(12.0f), 0);
        }
    }
    for (angle = 90; angle < 180; angle += 15) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -200.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -200.0f + 55.0f);
        HuPrcVSleep();
    }
    for (angle = 0; angle < 180; angle += 20) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -50.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -50.0f + 55.0f);
        HuPrcVSleep();
    }
    for (angle = 0; angle < 180; angle += 20) {
        for (i = 0; i < 3; i++) {
            HuSprPosSet(spr->unk_0A, i, pos[i][0], pos[i][1] + 215 + sindf(angle) * -30.0f);
        }
        HuWinPosSet(window, 60, sindf(angle) * -30.0f + 55.0f);
        HuPrcVSleep();
    }
    max = 11;
    if (MBDPlayerComCheck(-1)) {
        count = MBDRand(10.0f) + 10;
        cpuPartner = MBD6_ComPartnerRouletteDecide();
        if (state == 2 && cpuPartner != -1) {
            count = 5;
        }
    } else {
        count = -1;
    }
    msgWindow = MBDHelpWinCreate(0x13, 0xB9, 0);
    mbd6ev_partnerRouletteColorF = 1;
    last = 0xFF;
    do {
        MBDArrayShuffle(order, max);
        if (last == order[0]) {
            last = order[max];
            order[max] = order[0];
            order[0] = last;
            last = 0xFF;
        }
        for (i = 0; i <= max; i++) {
            HuAudFXPlay(0x1C8);
            last = order[i];
            HuSprBankSet(spr->unk_0A, 2, order[i], 0);
            HuSprAnimModeSet(spr->unk_0A, 2, HUSPR_ANIM_MODE_BANK);
            for (delay = (state == 2) ? 15 : 1; delay != 0; delay--) {
                if (count > 0) {
                    if (state != 2 || cpuPartner == -1 || cpuPartner == order[i]) {
                        if (--count == 0) {
                            break;
                        }
                    }
                } else if (ContBtnDown[GwPlayer[player].pad] & A_BUTTON) {
                    break;
                }
                HuPrcVSleep();
            }
            if (delay != 0) {
                break;
            }
        }
    } while (i == max + 1);
    {
        s32 sfx[12] = { 0x25A, 0x25B, 0x298, 0x256, 0x257, 0x25D, 0x2A3, 0x2A4, 0x2A2, 0x1E7, 0x2A5, 0x2A0 };

        HuAudFXPlay(sfx[order[i]]);
    }
    mbd6ev_partnerRouletteColorF = 0;
    if (player == 0) {
        if (state == 2) {
            GwSystem.playerIndexVisitingBowser &= 0xFF00;
        } else {
            GwSystem.playerIndexVisitingBowser++;
        }
    } else if (state == 2) {
        GwSystem.playerIndexVisitingBowser = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        GwSystem.playerIndexVisitingBowser += 0x100;
    }
    HuPrcSleep(30);
    mbd6ev_partnerRouletteResult = order[i];
    MBDHelpWinKill(msgWindow);
    if (colorProcess != NULL) {
        omDelPrcObj(colorProcess);
    }
    MBDSprGrpKill(spr);
    HuWinKill(window);
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

const Vec mbd6ev_partnerAppearOfsTbl[] = {
    { 4.0f, 4.0f, -4.0f },
    { -4.0f, -2.0f, -4.0f },
    { 4.0f, 0.0f, 4.0f },
    { -4.0f, 2.0f, 4.0f }
};

s32 MBD6Ev_PartnerRouletteExec(s32 index) {
    Vec camPos;
    Vec pos;
    Vec target;
    Object *copies[10]; // Only 4 are used; the size matches the original stack frame.
    Vec offsets[4];
    s32 unused[2]; // Unused, but needed to match the stack frame.
    SpaceData *startSpace;
    SpaceData *partnerSpace;
    GW_PLAYER *player;
    Process *process;
    Duel06PartnerRouletteWork *work;
    Object *model;
    Object *partner;
    SpaceData *returnSpace;
    SpaceData *destSpace;
    s32 i;
    s32 state;

    startSpace = MBDMasuGet(mbd6ev_partnerMasuTbl[index].startSpace);
    partnerSpace = MBDMasuGet(mbd6ev_partnerMasuTbl[index].partnerSpace);
    player = MBDPlayerGet(index);
    if (index == 0) {
        state = GwSystem.playerIndexVisitingBowser & 0xFF;
    } else {
        state = (GwSystem.playerIndexVisitingBowser / 256) & 0xFF;
    }
    if (state == 2) {
        MBDDlgWinExec(0x16, 0x1F07);
    }
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&pos);
    HuVecCopy3F(&target, &startSpace->coords);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &target, &pos, 3.0f));
    MBDPlayerMotionSet(-1, 0, 2);
    MBDVecDirGet(&player->player_obj->coords, &startSpace->coords, &player->player_obj->rot);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDVecSpeedMoveCreate(&player->player_obj->coords, &startSpace->coords,
                                         &player->player_obj->coords, 3.0f));
    HuPrcChildWatch();
    MBDVecDirGet(&player->player_obj->coords, &partnerSpace->coords, &player->player_obj->rot);
    MBDPlayerMotionSet(-1, 7, 0);
    HuPrcSleep(8);
    HuAudFXPlay(0x1C9);
    if (index == 0) {
        MBD6Ev_PartnerBox1SwayCreate(&player->player_obj->coords);
    } else {
        MBD6Ev_PartnerBox2SwayCreate(&player->player_obj->coords);
    }
    MBDModelMotionWait(player->player_obj);
    MBDPlayerMotionSet(-1, -1, 2);
    mbd6ev_partnerRouletteResult = -1;
    process = omAddPrcObj(MBD6Ev_PartnerRouletteProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel06PartnerRouletteWork));
    process->user_data = work;
    work->player = index;
    returnSpace = MBDMasuGet(mbd6ev_partnerMasuTbl[index].returnSpace);
    MBDVecDirGet(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->rot);
    MBDPlayerMotionSet(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDVecSpeedMoveCreate(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->coords, 2.0f));
    HuPrcChildWatch();
    MBDPlayerMotionSet(-1, -1, 2);
    MBDVecForwardSet(&camPos);
    MBDVecRotLerpCreate(&player->player_obj->rot, &camPos, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    while (mbd6ev_partnerRouletteResult == -1) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&target, &partnerSpace->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &target, &pos, 2.0f));
    HuPrcChildWatch();
    if (index == 0) {
        MBD6Ev_PartnerBox1SwayStop();
    } else {
        MBD6Ev_PartnerBox2SwayStop();
    }
    model = MBDModelCreate(0x35, NULL);
    MBDModelDispOff(model);
    partner = MBDPartnerModelCreate(mbd6ev_partnerRouletteResult);
    HuVecCopy3F(&partner->coords, &partnerSpace->coords);
    partner->coords.y += 26.0f;
    MBDModelDispOff(partner);
    HuAudFXPlay(0x1CA);
    if (index == 0) {
        MBD6Ev_PartnerBox1SquashCreate();
    } else {
        MBD6Ev_PartnerBox2SquashCreate();
    }
    HuPrcSleep(20);
    memcpy(offsets, mbd6ev_partnerAppearOfsTbl, sizeof(offsets));
    for (i = 0; i < 4; i++) {
        copies[i] = MBDModelLinkCreate(model);
        Hu3DModelLayerSet(copies[i]->omObj1->model[0], 0x800);
        Hu3DModelAttrSet(copies[i]->omObj1->model[0], 0x180, 0);
        Hu3DMotionAttrSet(copies[i]->omObj1->model[0], 2, 0);
        HuVecCopy3F(&copies[i]->coords, &partnerSpace->coords);
        copies[i]->velocity.x = 26.0f;
        copies[i]->coords.x += offsets[i].x;
        copies[i]->coords.y += offsets[i].y;
        copies[i]->coords.z += offsets[i].z;
        if (i == 3) {
            MBDModelDispOn(partner);
        }
        HuPrcSleep(4);
    }
    HuPrcSleep(25);
    for (i = 0; i < 4; i++) {
        MBDModelKill(copies[i]);
    }
    MBDModelKill(model);
    MBDCameraFocusModeSet(5);
    MBDCameraFocusObjSet(partner);
    destSpace = MBDMasuGet(mbd6ev_partnerMasuTbl[index].startSpace);
    MBDVecDirGet(&partner->coords, &destSpace->coords, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    MBDModelJumpSet(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&partner->coords, &destSpace->coords, &partner->coords, 20));
    HuPrcChildWatch();
    MBDModelJumpWait(partner);
    if (index == 0) {
        MBD6Ev_PartnerBox1MotionReset();
    } else {
        MBD6Ev_PartnerBox2MotionReset();
    }
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&pos);
    HuVecCopy3F(&pos, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &player->player_obj->coords, &pos, 2.0f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
    mbd6ev_partnerGetMdl = partner;
    return mbd6ev_partnerRouletteResult;
}

void MBD6Ev_PartnerGetExec(s32 index) {
    Vec pos;
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    u8 playerBits[4] = { 1, 2, 4, 8 };
    s16 comKeys[4] = { 0, 0, 0, 0 };
    Vec offsets[3];
    Vec frontPos;
    Vec backPos;
    Vec frontRot;
    Vec backRot;
    s16 partnerId;
    s16 choice;
    Object *partner;
    s32 i;

    MBDSaiNumKill(index);
    MBDPlayerPartyMotionSet(-1, -1, 2);
    MBDVecForwardSet(&pos);
    MBDVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 8);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuPrcChildWatch();
    if ((player->stats.partners.frontID != PARTNER_NONE && player->stats.partners.frontPoweredUp == POWERUP_ACTIVE) ||
        (player->stats.partners.backID != PARTNER_NONE && player->stats.partners.backPoweredUp == POWERUP_ACTIVE)) {
        MBDDlgResultWinExec(0x1F00);
        MBDPartnerPowerDown(index);
    }
    MBDAuraCreate(&MBDMasuGet(mbd6ev_partnerMasuTbl[index].returnSpace)->coords);
    MBDAuraLand(0);
    MBDAuraHoverStart();
    HuAudFXPlay(0x159);
    MBDDlgWinExec(0x16, 0x1F01);
    MBDPlayerMotionSet(-1, 6, 0);
    MBDCoinChangeCreate(index, 10);
    MBDCoinTakeCreate(index, 10);
    HuPrcSleep(30);
    MBDPlayerMotionSet(-1, -1, 2);
    if (player->stats.partners.frontID == PARTNER_NONE && player->stats.partners.backID == PARTNER_NONE) {
        MBDDlgWinExec(0x16, 0x1F04);
        partnerId = MBD6Ev_PartnerRouletteExec(index);
    retryA:
        MBDDlgWinCreate(0x16, 0x1F05);
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(mbdDlgWinId, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (MBD6_ComPartnerRefuseRateGet() >= MBDRand(100.0f) ||
                MBD6_ComPartnerIdRefuseRateGet(partnerId) >= MBDRand(100.0f)) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(mbdDlgWinId, 2, 2);
        }
        choice = HuWinChoiceGet(mbdDlgWinId, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        MBDDlgWinClose();
        MBDDlgWinKill();
        if (choice == 2) {
            MBD6_MapScroll();
            goto retryA;
        }
        if (choice == 3) {
            mbItemBtnF = 0;
            MBDPartnerDescExec(index);
            mbItemBtnF = 1;
            goto retryA;
        }
    } else {
        MBDDlgWinExec(0x16, 0x1F02);
    retryB:
        MBDDlgWinCreate(0x16, 0x1F03);
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(mbdDlgWinId, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (player->stats.partners.backID == PARTNER_NONE ||
                MBD6_ComPartnerSlotRateGet() >= MBDRand(100.0f)) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(mbdDlgWinId, 2, 2);
        }
        choice = HuWinChoiceGet(mbdDlgWinId, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        MBDDlgWinClose();
        MBDDlgWinKill();
        if (choice == 2) {
            MBD6_MapScroll();
            goto retryB;
        }
        if (choice == 3) {
            mbItemBtnF = 0;
            MBDPartnerDescExec(index);
            mbItemBtnF = 1;
            goto retryB;
        }
        partner = MBDPartnerObjGet(index, choice);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            memcpy(offsets, mbd6ev_partnerVanishOfsTbl, sizeof(offsets));
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), MBDEffMdlCreate(0x4E, &pos, &offsets[i], 3.0f));
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            MBDModelDispOff(partner);
            HuPrcChildWatch();
            MBDPartnerClear(index, choice);
            MBDPartnerModelUpdate(index);
            MBDStatusFrontDispOff(index);
            MBDStatusBackDispOff(index);
        }
        partnerId = MBD6Ev_PartnerRouletteExec(index);
    }
    MBDPartnerOfsGet(index, &frontPos, &backPos);
    MBDPartnerDirGet(index, &frontRot, &backRot);
    MBDMotionShiftSet(mbd6ev_partnerGetMdl, 0, 0, 5, 2);
    if (GwSystem.current_board_index == 2) {
        MBDModelJumpSet(mbd6ev_partnerGetMdl, 2.0f, -0.2f);
    }
    if (choice == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        MBDVecDirGet(&mbd6ev_partnerGetMdl->coords, &frontPos, &mbd6ev_partnerGetMdl->rot);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&mbd6ev_partnerGetMdl->coords, &frontPos,
                                                                &mbd6ev_partnerGetMdl->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecRotLerpCreate(&mbd6ev_partnerGetMdl->rot, &frontRot,
                                                                &mbd6ev_partnerGetMdl->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        MBDVecDirGet(&mbd6ev_partnerGetMdl->coords, &backPos, &mbd6ev_partnerGetMdl->rot);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&mbd6ev_partnerGetMdl->coords, &backPos,
                                                                &mbd6ev_partnerGetMdl->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecRotLerpCreate(&mbd6ev_partnerGetMdl->rot, &backRot,
                                                                &mbd6ev_partnerGetMdl->rot, 7));
    }
    HuPrcChildWatch();
    MBDModelKill(mbd6ev_partnerGetMdl);
    MBDPartnerSet(index, partnerId, choice);
    MBDPartnerModelReset(index, choice);
    MBDPartnerMotionSet(index, PARTNER_FRONT, -1, 2);
    MBDPartnerMotionSet(index, PARTNER_BACK, -1, 2);
    MBDPartnerPosFix(index);
    MBDStatusFrontUpdate(index);
    MBDStatusBackUpdate(index);
    if (player->stats.partners.frontID == player->stats.partners.backID) {
        switch (player->stats.partners.frontID) {
        case PARTNER_WHOMP:
        case PARTNER_THWOMP:
            MBDDlgWinInsertCreate(0x16, 0x1F09, mbdPartnerNameMesTbl[player->stats.partners.frontID], 0, 0, 0, 0);
            MBDDlgWinMesWait();
            MBDDlgWinMesWait();
            MBDDlgWinMesWait();
            MBDDlgWinClose();
            MBDDlgWinKill();
            player->stats.partners.frontCost--;
            player->stats.partners.backCost--;
            HuAudFXPlay(0x205);
            MBDStatusMemberGrow(index, 1);
            MBDStatusMemberShrink(index, 1);
            break;
        default:
            MBDDlgWinInsertCreate(0x16, 0x1F08, mbdPartnerNameMesTbl[player->stats.partners.frontID], 0, 0, 0, 0);
            MBDDlgWinMesWait();
            MBDDlgWinClose();
            MBDDlgWinKill();
            player->stats.partners.frontPower++;
            player->stats.partners.backPower++;
            HuAudFXPlay(0x205);
            MBDStatusMemberGrow(index, 0);
            MBDStatusMemberShrink(index, 0);
            break;
        }
        if (index == 0) {
            GWBoardFlagSet(0x12);
        } else {
            GWBoardFlagSet(0x13);
        }
    }
    MBDPartnerComboMesExec();
    MBDDlgWinExec(0x16, 0x1F06);
    MBDAuraHoverStop();
    MBDAuraRiseExec(0);
    MBDAuraKill();
    MBDSaiNumShow(index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWatch();
}

void MBD6Ev_StartMasu1P(void) {
    GW_PLAYER *player;

    player = MBDPlayerGet(CUR_PLAYER);
    if (MBDPlayerTurnGet() == 0 && !(player->rev & 4)) {
        MBDPlayerPartyMotionSet(-1, -1, 2);
        MBD6Ev_PartnerGetExec(0);
    }
}

void MBD6Ev_StartMasu2P(void) {
    GW_PLAYER *player;

    player = MBDPlayerGet(CUR_PLAYER);
    if (MBDPlayerTurnGet() == 1 && !(player->rev & 4)) {
        MBDPlayerPartyMotionSet(-1, -1, 2);
        MBD6Ev_PartnerGetExec(1);
    }
}

const Vec mbd6ev_partnerVanishOfsTbl[] = {
    { 0.0f, 0.5f, 0.0f },
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f }
};

// なにをつけますか？１Ｐまえ行　＜ノコノコ＞　　＜クリホ゛ー＞行　＜キノヒオ＞　　＜ホ゛ムへい＞行　＜テレサ　＞　　＜ハ゛ッタン＞行　＜ムーチョ＞　　＜フラワー＞行　＜ワンワン＞　　＜ト゛ッスン＞行　＜スノーマ＞　　＜ミニクハ＞行
const u8 mbd6ev_partnerSelFront1PStr[] = "\x82\xC8\x82\xC9\x82\xF0\x82\xC2\x82\xAF\x82\xDC\x82\xB7\x82\xA9\x81\x48\x82\x50\x82\x6F\x82\xDC\x82\xA6\x8D\x73"
    "\x81\x40\x81\x83\x83\x6D\x83\x52\x83\x6D\x83\x52\x81\x84\x81\x40\x81\x40\x81\x83\x83\x4E\x83\x8A\x83\x7A\x81\x4A\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x4C\x83\x6D\x83\x71\x83\x49\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7A\x81\x4A\x83\x80\x82\xD6\x82\xA2\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x65\x83\x8C\x83\x54\x81\x40\x81\x84\x81\x40\x81\x40\x81\x83\x83\x6E\x81\x4A\x83\x62\x83\x5E\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x80\x81\x5B\x83\x60\x83\x87\x81\x84\x81\x40\x81\x40\x81\x83\x83\x74\x83\x89\x83\x8F\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x8F\x83\x93\x83\x8F\x83\x93\x81\x84\x81\x40\x81\x40\x81\x83\x83\x67\x81\x4A\x83\x62\x83\x58\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x58\x83\x6D\x81\x5B\x83\x7D\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7E\x83\x6A\x83\x4E\x83\x6E\x81\x84\x8D\x73";

// なにをつけますか？１Ｐうしろ行　＜ノコノコ＞　　＜クリホ゛ー＞行　＜キノヒオ＞　　＜ホ゛ムへい＞行　＜テレサ　＞　　＜ハ゛ッタン＞行　＜ムーチョ＞　　＜フラワー＞行　＜ワンワン＞　　＜ト゛ッスン＞行　＜スノーマ＞　　＜ミニクハ＞行
const u8 mbd6ev_partnerSelBack1PStr[] = "\x82\xC8\x82\xC9\x82\xF0\x82\xC2\x82\xAF\x82\xDC\x82\xB7\x82\xA9\x81\x48\x82\x50\x82\x6F\x82\xA4\x82\xB5\x82\xEB\x8D\x73"
    "\x81\x40\x81\x83\x83\x6D\x83\x52\x83\x6D\x83\x52\x81\x84\x81\x40\x81\x40\x81\x83\x83\x4E\x83\x8A\x83\x7A\x81\x4A\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x4C\x83\x6D\x83\x71\x83\x49\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7A\x81\x4A\x83\x80\x82\xD6\x82\xA2\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x65\x83\x8C\x83\x54\x81\x40\x81\x84\x81\x40\x81\x40\x81\x83\x83\x6E\x81\x4A\x83\x62\x83\x5E\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x80\x81\x5B\x83\x60\x83\x87\x81\x84\x81\x40\x81\x40\x81\x83\x83\x74\x83\x89\x83\x8F\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x8F\x83\x93\x83\x8F\x83\x93\x81\x84\x81\x40\x81\x40\x81\x83\x83\x67\x81\x4A\x83\x62\x83\x58\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x58\x83\x6D\x81\x5B\x83\x7D\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7E\x83\x6A\x83\x4E\x83\x6E\x81\x84\x8D\x73";

// なにをつけますか？２Ｐまえ行　＜ノコノコ＞　　＜クリホ゛ー＞行　＜キノヒオ＞　　＜ホ゛ムへい＞行　＜テレサ　＞　　＜ハ゛ッタン＞行　＜ムーチョ＞　　＜フラワー＞行　＜ワンワン＞　　＜ト゛ッスン＞行　＜スノーマ＞　　＜ミニクハ＞行
const u8 mbd6ev_partnerSelFront2PStr[] = "\x82\xC8\x82\xC9\x82\xF0\x82\xC2\x82\xAF\x82\xDC\x82\xB7\x82\xA9\x81\x48\x82\x51\x82\x6F\x82\xDC\x82\xA6\x8D\x73"
    "\x81\x40\x81\x83\x83\x6D\x83\x52\x83\x6D\x83\x52\x81\x84\x81\x40\x81\x40\x81\x83\x83\x4E\x83\x8A\x83\x7A\x81\x4A\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x4C\x83\x6D\x83\x71\x83\x49\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7A\x81\x4A\x83\x80\x82\xD6\x82\xA2\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x65\x83\x8C\x83\x54\x81\x40\x81\x84\x81\x40\x81\x40\x81\x83\x83\x6E\x81\x4A\x83\x62\x83\x5E\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x80\x81\x5B\x83\x60\x83\x87\x81\x84\x81\x40\x81\x40\x81\x83\x83\x74\x83\x89\x83\x8F\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x8F\x83\x93\x83\x8F\x83\x93\x81\x84\x81\x40\x81\x40\x81\x83\x83\x67\x81\x4A\x83\x62\x83\x58\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x58\x83\x6D\x81\x5B\x83\x7D\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7E\x83\x6A\x83\x4E\x83\x6E\x81\x84\x8D\x73";

// なにをつけますか？２Ｐうしろ行　＜ノコノコ＞　　＜クリホ゛ー＞行　＜キノヒオ＞　　＜ホ゛ムへい＞行　＜テレサ　＞　　＜ハ゛ッタン＞行　＜ムーチョ＞　　＜フラワー＞行　＜ワンワン＞　　＜ト゛ッスン＞行　＜スノーマ＞　　＜ミニクハ＞行
const u8 mbd6ev_partnerSelBack2PStr[] = "\x82\xC8\x82\xC9\x82\xF0\x82\xC2\x82\xAF\x82\xDC\x82\xB7\x82\xA9\x81\x48\x82\x51\x82\x6F\x82\xA4\x82\xB5\x82\xEB\x8D\x73"
    "\x81\x40\x81\x83\x83\x6D\x83\x52\x83\x6D\x83\x52\x81\x84\x81\x40\x81\x40\x81\x83\x83\x4E\x83\x8A\x83\x7A\x81\x4A\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x4C\x83\x6D\x83\x71\x83\x49\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7A\x81\x4A\x83\x80\x82\xD6\x82\xA2\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x65\x83\x8C\x83\x54\x81\x40\x81\x84\x81\x40\x81\x40\x81\x83\x83\x6E\x81\x4A\x83\x62\x83\x5E\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x80\x81\x5B\x83\x60\x83\x87\x81\x84\x81\x40\x81\x40\x81\x83\x83\x74\x83\x89\x83\x8F\x81\x5B\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x8F\x83\x93\x83\x8F\x83\x93\x81\x84\x81\x40\x81\x40\x81\x83\x83\x67\x81\x4A\x83\x62\x83\x58\x83\x93\x81\x84\x8D\x73"
    "\x81\x40\x81\x83\x83\x58\x83\x6D\x81\x5B\x83\x7D\x81\x84\x81\x40\x81\x40\x81\x83\x83\x7E\x83\x6A\x83\x4E\x83\x6E\x81\x84\x8D\x73";

void MBD6Ev_TurnStart(void) {
    s32 index = GwSystem.current_player_index;
    GW_PLAYER *player = MBDPlayerGet(index);
    u8 mes[0x200];
    u8 playerBits[4] = { 1, 2, 4, 8 };
    s16 comKeys[4] = { 0, 0, 0, 0 };
    Vec rot;
    Vec origRot;
    Vec camPos;
    char coinStr[8];
    Vec effectPos;
    Vec pos;
    Vec offsets[3];
    s16 win;
    s32 frontChoice;
    s32 backChoice;
    Object *partner;
    Object *coin;
    Object *ref;
    s32 coins;
    s32 curCoins;
    s32 side;
    s32 i;
    s32 j;
    s32 k;

    if (index == 0 && GwSystem.current_turn == 1 && player->stats.partners.frontID == -1 &&
        player->stats.partners.backID == -1) {
        win = HuWinExCreate(-1, 80, 80, 160, 105, 0);
        HuWinAttrSet(win, 64, 64);
        HuWinExAnimIn(win);
        HuWinMesConv(mes, (s32)mbd6ev_partnerSelFront1PStr);
        HuWinMesSet(win, (u32)mes, -1, -1);
        while (HuWinStatGet(win) != 0) {
            HuPrcVSleep();
        }
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(win, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (GwPlayer[index].chr == 5) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(win, 2, 2);
        }
        frontChoice = (s16)HuWinChoiceGet(win, 0, 1);
        HuWinExAnimOut(win, 0);
        HuWinKill(win);

        win = HuWinExCreate(-1, 80, 80, 160, 105, 0);
        HuWinAttrSet(win, 64, 64);
        HuWinExAnimIn(win);
        HuWinMesConv(mes, (s32)mbd6ev_partnerSelBack1PStr);
        HuWinMesSet(win, (u32)mes, -1, -1);
        while (HuWinStatGet(win) != 0) {
            HuPrcVSleep();
        }
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(win, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (GwPlayer[index].chr == 5) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(win, 2, 2);
        }
        backChoice = (s16)HuWinChoiceGet(win, 0, 1);
        HuWinExAnimOut(win, 0);
        HuWinKill(win);
        MBDPartnerSet(index, frontChoice, PARTNER_FRONT);
        MBDPartnerSet(index, backChoice, PARTNER_BACK);
        MBDPartnerModelSetup(index);
        MBDPartnerPosFix(index);
        MBDStatusFrontUpdate(index);
        MBDStatusBackUpdate(index);
        if (ContBtn[0] & 0x1000) {
            MBDPartnerPowerUp(index);
        }

        win = HuWinExCreate(-1, 80, 80, 160, 105, 0);
        HuWinAttrSet(win, 64, 64);
        HuWinExAnimIn(win);
        HuWinMesConv(mes, (s32)mbd6ev_partnerSelFront2PStr);
        HuWinMesSet(win, (u32)mes, -1, -1);
        while (HuWinStatGet(win) != 0) {
            HuPrcVSleep();
        }
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(win, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (GwPlayer[index].chr == 5) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(win, 2, 2);
        }
        frontChoice = (s16)HuWinChoiceGet(win, 0, 0);
        HuWinExAnimOut(win, 0);
        HuWinKill(win);

        win = HuWinExCreate(-1, 80, 80, 160, 105, 0);
        HuWinAttrSet(win, 64, 64);
        HuWinExAnimIn(win);
        HuWinMesConv(mes, (s32)mbd6ev_partnerSelBack2PStr);
        HuWinMesSet(win, (u32)mes, -1, -1);
        while (HuWinStatGet(win) != 0) {
            HuPrcVSleep();
        }
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(win, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = -1;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (GwPlayer[index].chr == 5) {
                comKeys[GwPlayer[index].pad] = 0x400;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = -0x8000;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(win, 2, 2);
        }
        backChoice = (s16)HuWinChoiceGet(win, 0, 0);
        HuWinExAnimOut(win, 0);
        HuWinKill(win);
        MBDPartnerSet(1, frontChoice, PARTNER_FRONT);
        MBDPartnerSet(1, backChoice, PARTNER_BACK);
        MBDPartnerModelSetup(1);
        MBDPartnerPosFix(1);
        MBDStatusFrontUpdate(1);
        MBDStatusBackUpdate(1);
        if (ContBtn[0] & 0x1000) {
            MBDPartnerPowerUp(1);
        }
    }
    if ((player->stats.partners.frontID == 6 || player->stats.partners.backID == 6) &&
        MBDRand(100.0f) < 34) {
        coins = MBDRand(3.0f) + 2;
        MBDPartnerAttackMotLoad(6);
        if (player->stats.partners.backID == 6) {
            partner = MBDPartnerObjGet(index, PARTNER_BACK);
        } else {
            partner = MBDPartnerObjGet(index, PARTNER_FRONT);
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
        HuPrcChildWatch();
        HuVecCopy3F(&camPos, &player->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&camPos, &partner->coords, &camPos, 2.0f));
        HuPrcChildWatch();
        MBDVecDirGet(&partner->coords, &player->player_obj->coords, &rot);
        HuVecCopy3F(&origRot, &partner->rot);
        MBDVecRotLerpCreate(&partner->rot, &rot, &partner->rot, 8);
        HuPrcSleep(8);
        for (i = 0; i < 31; i += 5) {
            HuMtxRotXF(Hu3DData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x += 1.0f;
            HuPrcVSleep();
        }
        MBDPartnerAttackMotShiftSet(partner, 2, 0, 5, 2);
        coin = NULL;
        for (i = 0; i < coins; i++) {
            if (coin != NULL) {
                for (j = 6; j < 12; j++) {
                    f32 scale = j / 6.0f + 0.5f;

                    if (scale > 1.0f) {
                        scale = 1.0f;
                    }
                    HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                    HuMtxRotYF(Hu3DData[coin->omObj1->model[0]].mtx, j * 40);
                    HuPrcVSleep();
                }
            } else {
                HuPrcSleep(3);
                HuVecCopy3F(&effectPos, &partner->coords);
                effectPos.y += 12.0f;
                MBDEffMdlCreate(0x4E, &effectPos, NULL, 1.0f);
                HuPrcSleep(1);
            }
            if (coin != NULL) {
                MBDCoinTakeCreate(index, 1);
                MBDModelKill(coin);
                HuVecCopy3F(&effectPos, &partner->coords);
                effectPos.y += 12.0f;
                MBDEffMdlCreate(0x4E, &effectPos, NULL, 1.0f);
            }
            coin = MBDModelCreate(0x1C, NULL);
            coin->velocity.x = 13.0f;
            HuVecCopy3F(&coin->coords, &partner->coords);
            HuVecCopyXYZ(&coin->scale, 0.0f, 0.0f, 0.0f);
            MBDModelJumpSet(coin, 2.0f, -0.2f);
            MBDPlayerPosMoveCreate(&coin->coords, &player->player_obj->coords, &coin->coords, 10);
            HuAudFXPlay(0x200);
            for (j = 0; j < 6; j++) {
                f32 scale = j / 6.0f;

                if (scale > 1.0f) {
                    scale = 1.0f;
                }
                HuVecCopyXYZ(&coin->scale, scale, scale, scale);
                HuMtxRotYF(Hu3DData[coin->omObj1->model[0]].mtx, j * 40);
                HuPrcVSleep();
            }
        }
        for (j = 6; j < 12; j++) {
            f32 scale = j / 6.0f;

            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuVecCopyXYZ(&coin->scale, scale, scale, scale);
            HuMtxRotYF(Hu3DData[coin->omObj1->model[0]].mtx, j * 40);
            HuPrcVSleep();
        }
        MBDCoinTakeCreate(index, 1);
        MBDModelKill(coin);
        MBDMotionSet(partner, -1, 2);
        for (i = 30; i >= 0; i -= 10) {
            HuMtxRotXF(Hu3DData[partner->omObj1->model[0]].mtx, -i);
            partner->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        partner->velocity.x = 0.0f;
        MBDVecRotLerpCreate(&partner->rot, &origRot, &partner->rot, 4);
        HuPrcSleep(4);
        MBDPartnerAttackMotKill();
        sprintf(coinStr, "%d", coins);
        MBDWinInsertOpen(0x4F0C, coinStr, 0, 0, 0, 0);
        MBDWinKeyWaitKeep(index);
        MBDWinClose();
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&camPos, &player->player_obj->coords, &camPos, 2.0f));
        HuPrcChildWatch();
        MBDCameraFocusModeSet(1);
    }
    if (GwSystem.current_turn != 1) {
        coins = MBDPartnerCostGet(index);
        curCoins = GwPlayer[index].coin;
        if (curCoins < coins) {
            MBDCoinChangeCreate(index, -curCoins);
            MBDCoinTakeCreate(index, -curCoins);
            HuPrcSleep(30);
            for (side = 0; side < 2; side++) {
                ref = MBDPartnerObjGet(index, side);
                if (ref != NULL) {
                    HuVecCopy3F(&pos, &ref->coords);
                    pos.y += 2.0f;
                    memcpy(offsets, mbd6ev_partnerVanishOfsTbl, sizeof(offsets));
                    for (k = 0; k < 3; k++) {
                        HuPrcChildLink(HuPrcCurrentGet(), MBDEffMdlCreate(0x4E, &pos, &offsets[k], 3.0f));
                    }
                    MBDModelDispOff(ref);
                }
            }
            HuPrcVSleep();
            HuAudFXPlay(0x1CB);
            HuPrcChildWatch();
            MBDPartnerClear(index, PARTNER_FRONT);
            MBDPartnerClear(index, PARTNER_BACK);
            MBDPartnerModelKillAll(index);
            MBDStatusFrontDispOff(index);
            MBDStatusBackDispOff(index);
            MBDDlgResultWinExec(0x1E01);
        } else if (coins != 0) {
            MBDCoinChangeCreate(index, -coins);
            MBDCoinTakeCreate(index, -coins);
            HuPrcSleep(30);
        }
    }
}

void MBD6Ev_GateGuyMasu(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    SpaceData *space;
    HmfMotionNode *node;
    s32 i;
    f32 offset;
    Vec pos;
    char text[8];

    player = MBDPlayerGet(CUR_PLAYER);
    space = MBDMasuGet(0x1C);
    MBDSaiNumKill(sys->current_player_index);
    MBDPlayerPartyMotionSet(-1, -1, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &space->coords, &pos, 4.0f));
    MBDMotionSet(mbd6_gateGuyMdl, 2, 0);
    Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], Hu3DData[mbd6_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], mbd6_gateGuyMdl->omObj1->motion[2], "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd6_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    i = 0;
    while (!(MBDMotionCheck(mbd6_gateGuyMdl) & 1)) {
        if (++i == 8) {
            HuAudFXPlay(0x1C5);
        }
        HuPrcVSleep();
    }
    Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], Hu3DData[mbd6_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd6_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (offset = 0.0f; offset >= -60.0f; offset -= 4.0f) {
        node->baseRot.y = (GwSystem.bank_coins - 5) * 60 + offset;
        HuPrcVSleep();
    }
    HuPrcChildWatch();
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    MBD6_GateGuyBellSet();
    mbd6_gateGuyScrewSpeed = 12.0f;
    if (GwSystem.bank_coins != 0) {
        HuAudFXPlay(0x207);
        MBDMotionShiftSet(mbd6_gateGuyMdl, 0, 0, 5, 2);
        Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], mbd6_gateGuyMdl->omObj1->motion[0], "bell", 0x4C, 0x46);
        Hu3DMotionSpeedSet(mbd6_gateGuyMdl->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(24);
        MBDMotionSet(mbd6_gateGuyMdl, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        MBDMotionShiftSet(mbd6_gateGuyMdl, 1, 0, 5, 2);
        Hu3DMotionNoMotSet(mbd6_gateGuyMdl->omObj1->model[0], mbd6_gateGuyMdl->omObj1->motion[1], "bell", 0x4C, 0x46);
        Hu3DMotionSpeedSet(mbd6_gateGuyMdl->omObj1->model[0], 1.0f);
        MBD6_GateGuyBellSet();
        MBDStatusShrink(-1);
        MBDAuraAltCreate(&pos);
        if (sys->current_turn < 11) {
            sprintf(text, "20");
        } else if (sys->current_turn >= 20) {
            sprintf(text, "40");
        } else {
            sprintf(text, "30");
        }
        HuAudFXPlay(0x2A7);
        MBDDlgWinInsertCreate(0x15, 0x1F30, (s32)text, 0, 0, 0, 0);
        MBDDlgWinMesWait();
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBD6Ev_GateGuyWarpExec();
        mbdMgCallMdlObj = mbd6_gateGuyMdl;
        MBDGameModeMgSet();
        HuPrcSleep(-1);
    }
    mbd6_gateGuyScrewSpeed = 3.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &player->player_obj->coords, &pos, 4.0f));
    MBDSaiNumShow(sys->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(1.7f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
}

void MBD6Ev_HatenaHpRecover(void) {
    GW_PLAYER *player;
    void *handle;

    player = MBDPlayerGet(CUR_PLAYER);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuAudFXPlay(0x1FF);
    handle = MBDPlayerVibrateObjCreate(-1, 3, 5);
    MBDAuraSpinExec(3);
    MBDPlayerVibrateObjKill(handle);
    MBDAuraHoverStop();
    MBDAuraRiseExec(2);
    MBDAuraKill();
    MBDPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x2BD, GwSystem.current_player_index);
    MBDModelMotionWait(player->player_obj);
    MBDPlayerMotionSet(-1, -1, 2);
    GwPlayer[GwSystem.current_player_index].star = 5;
}

void MBD6Ev_HatenaPosSwap(void) {
    MBDItemWarpBlockSwapInit();
    MBDItemWarpBlockSwapPlayerSet();
    MBDItemWarpBlockSwapCreate();
    MBDPartnerPosFix(0);
    MBDPartnerPosFix(1);
}

void MBD6Ev_HatenaCoinLose10(void) {
    GW_SYSTEM *sys = &GwSystem;
    s32 coins = GwPlayer[sys->current_player_index].coin;

    if (coins > 10) {
        coins = 10;
    }
    MBDCoinChangeCreate(sys->current_player_index, -coins);
    MBDCoinTakeCreate(sys->current_player_index, -coins);
    HuPrcSleep(30);
}

void MBD6Ev_HatenaCoinGain10(void) {
    GW_SYSTEM *sys = &GwSystem;

    MBDCoinChangeCreate(sys->current_player_index, 10);
    MBDCoinTakeCreate(sys->current_player_index, 10);
    HuPrcSleep(30);
}

void MBD6Ev_HatenaStartWarp(void) {
    s8 nnlink;
    s8 nnidx;
    s8 link2 = -1;
    s8 idx2 = -1;

    if (MBDPlayerTurnGet() == 0) {
        MBDMasuLinkIdxGet(0x15, &nnlink, &nnidx);
    } else {
        MBDMasuLinkIdxGet(0x16, &nnlink, &nnidx);
    }
    MBD6Ev_StartWarpLinkGet(&link2, &idx2);
    MBDWarpMasuExec(nnlink, nnidx, link2, idx2);
    MBDPartnerPosFix(GwSystem.current_player_index);
    MBD6Ev_PartnerGetExec(MBDPlayerTurnGet());
}

void MBD6Ev_HatenaMasuOwnerSwap(void) {
    GW_PLAYER *player;
    Object *obj;
    void *handles[2];
    f32 scale;
    f32 angle;
    s32 curPlayer;
    s32 otherPlayer;

    curPlayer = MBDPlayerTurnGet();
    otherPlayer = (curPlayer + 1) & 1;
    player = MBDPlayerGet(CUR_PLAYER);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuPrcSleep(10);
    HuAudFXPlay(0x1F6);
    MBDAuraSpinExec(1);
    HuPrcSleep(15);
    obj = MBDModelCreate(0x21, NULL);
    Hu3DModelAttrSet(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1F9);
    handles[0] = MBDPlayerVibrateObjCreate(0, 3, 5);
    handles[1] = MBDPlayerVibrateObjCreate(1, 3, 5);
    angle = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }
    MBDMasuOwnerSwap(otherPlayer, curPlayer);
    MBDMasuOwnerTypeUpdate();
    MBDMasuTypeListCreate();
    while (scale >= 1.0f) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
        scale -= 0.5;
    }
    MBDPlayerVibrateObjKill(handles[0]);
    MBDPlayerVibrateObjKill(handles[1]);
    MBDModelKill(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    MBDDlgWinInsertCreate(0x16, 0x1F2B, mbKSuitObj[GwPlayer[(s8)(GwSystem.current_player_index ^ 1)].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    MBDAuraHoverStop();
    MBDAuraRiseExec(2);
    MBDAuraKill();
    MBDPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x2BD, GwSystem.current_player_index);
    MBDModelMotionWait(player->player_obj);
    MBDPlayerMotionSet(-1, -1, 2);
}

void MBD6Ev_HatenaPartnerPowerUp(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    void *handle;
    Object *partners[2];

    player = MBDPlayerGet(CUR_PLAYER);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuAudFXPlay(0x1F6);
    handle = MBDPlayerVibrateObjCreate(-1, 0, 5);
    MBDAuraSpinExec(0);
    MBDPlayerVibrateObjKill(handle);
    MBDAuraHoverStop();
    HuPrcChildLink(HuPrcCurrentGet(), MBDAuraRiseCreate(2));
    partners[PARTNER_FRONT] = NULL;
    partners[PARTNER_BACK] = NULL;
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partners[PARTNER_FRONT] = MBDModelCreate(0x38, NULL);
        MBDModelTempAllocFree(partners[PARTNER_FRONT]);
        HuVecCopy3F(&partners[PARTNER_FRONT]->coords, &MBDPartnerObjGet(sys->current_player_index, PARTNER_FRONT)->coords);
        Hu3DMotionAttrSet(partners[PARTNER_FRONT]->omObj1->model[0], 2, 0);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partners[PARTNER_BACK] = MBDModelCreate(0x38, NULL);
        MBDModelTempAllocFree(partners[PARTNER_BACK]);
        HuVecCopy3F(&partners[PARTNER_BACK]->coords, &MBDPartnerObjGet(sys->current_player_index, PARTNER_BACK)->coords);
        Hu3DMotionAttrSet(partners[PARTNER_BACK]->omObj1->model[0], 2, 0);
    }
    HuAudFXPlay(0x1FA);
    if (partners[PARTNER_FRONT] != NULL) {
        MBDModelMotionWait(partners[PARTNER_FRONT]);
        MBDModelKill(partners[PARTNER_FRONT]);
    }
    if (partners[PARTNER_BACK] != NULL) {
        MBDModelMotionWait(partners[PARTNER_BACK]);
        MBDModelKill(partners[PARTNER_BACK]);
    }
    MBDPartnerPowerUp(sys->current_player_index);
    HuPrcChildLink(HuPrcCurrentGet(), MBDTelopBannerCreate(0));
    HuPrcChildWatch();
    MBDAuraKill();
}

void MBD6Ev_HatenaPartnerPowerDown(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player;
    void *handle;
    Object *partners[2];

    player = MBDPlayerGet(CUR_PLAYER);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuAudFXPlay(0x1FB);
    handle = MBDPlayerVibrateObjCreate(-1, 0, 5);
    MBDAuraSpinExec(4);
    MBDPlayerVibrateObjKill(handle);
    MBDAuraHoverStop();
    HuPrcChildLink(HuPrcCurrentGet(), MBDAuraRiseCreate(2));
    partners[PARTNER_FRONT] = NULL;
    partners[PARTNER_BACK] = NULL;
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partners[PARTNER_FRONT] = MBDModelCreate(0x3A, NULL);
        MBDModelTempAllocFree(partners[PARTNER_FRONT]);
        HuVecCopy3F(&partners[PARTNER_FRONT]->coords, &MBDPartnerObjGet(sys->current_player_index, PARTNER_FRONT)->coords);
        Hu3DMotionAttrSet(partners[PARTNER_FRONT]->omObj1->model[0], 2, 0);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partners[PARTNER_BACK] = MBDModelCreate(0x3A, NULL);
        MBDModelTempAllocFree(partners[PARTNER_BACK]);
        HuVecCopy3F(&partners[PARTNER_BACK]->coords, &MBDPartnerObjGet(sys->current_player_index, PARTNER_BACK)->coords);
        Hu3DMotionAttrSet(partners[PARTNER_BACK]->omObj1->model[0], 2, 0);
    }
    if (partners[PARTNER_FRONT] != NULL) {
        MBDModelMotionWait(partners[PARTNER_FRONT]);
        MBDModelKill(partners[PARTNER_FRONT]);
    }
    if (partners[PARTNER_BACK] != NULL) {
        MBDModelMotionWait(partners[PARTNER_BACK]);
        MBDModelKill(partners[PARTNER_BACK]);
    }
    MBDPartnerPowerDown(sys->current_player_index);
    HuAudFXPlay(0x1FC);
    HuPrcChildLink(HuPrcCurrentGet(), MBDTelopBannerCreate(1));
    HuPrcChildWatch();
    MBDAuraKill();
}

void MBD6Ev_HatenaPartnerSwap(void) {
    GW_PLAYER *player;
    s32 playerIndex;
    void *handle;
    Object *partner;
    f32 angle;

    player = MBDPlayerGet(CUR_PLAYER);
    playerIndex = MBDPlayerTurnGet();
    MBDEffSwirlCreate(&player->player_obj->coords);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuAudFXPlay(0x1F6);
    MBDAuraSpinExec(1);
    HuAudFXPlay(0x1FD);
    MBDEffSwirlOn();
    handle = MBDPlayerVibrateObjCreate(-1, 1, 5);
    for (angle = 0.0f; angle < 120.0f; angle += 5.0f) {
        if (player->stats.partners.frontID != PARTNER_NONE) {
            partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        if (player->stats.partners.backID != PARTNER_NONE) {
            partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        HuPrcVSleep();
    }
    MBDPartnerPosSwap(playerIndex);
    MBDEffSwirlOff();
    for (angle = 120.0f; angle > 0.0f; angle -= 5.0f) {
        if (player->stats.partners.frontID != PARTNER_NONE) {
            partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        if (player->stats.partners.backID != PARTNER_NONE) {
            partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
            partner->velocity.x = angle;
            MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
        }
        HuPrcVSleep();
    }
    MBDPlayerVibrateObjKill(handle);
    if (player->stats.partners.frontID != PARTNER_NONE) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
        partner->velocity.x = 0.0f;
        MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
    }
    if (player->stats.partners.backID != PARTNER_NONE) {
        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
        partner->velocity.x = 0.0f;
        MTX_ROTY(Hu3DData[partner->omObj1->model[0]].mtx, angle * 10.0f);
    }
    MBDEffSwirlKill();
    HuAudFXPlay(0x159);
    MBDDlgWinExec(0x16, 0x1F2C);
    MBDAuraHoverStop();
    MBDAuraRiseExec(1);
    MBDAuraKill();
}

void MBD6Ev_HatenaMasuOwnerClear(void) {
    GW_PLAYER *player;
    Object *obj;
    void *handles[2];
    f32 scale;
    f32 angle;

    player = MBDPlayerGet(CUR_PLAYER);
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuPrcSleep(10);
    HuAudFXPlay(0x1FB);
    MBDAuraSpinExec(4);
    HuPrcSleep(15);
    obj = MBDModelCreate(0x22, NULL);
    Hu3DModelAttrSet(obj->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);
    obj->coords.y += 30.0f;
    HuAudFXPlay(0x1FE);
    handles[0] = MBDPlayerVibrateObjCreate(0, 2, 5);
    handles[1] = MBDPlayerVibrateObjCreate(1, 2, 5);
    angle = 0.0f;
    for (scale = 1.0f; scale < 20.0f; scale += 0.5) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }
    MBDMasuOwnerClear();
    MBDMasuTypeListCreate();
    while (scale >= 1.0f) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
        scale -= 0.5;
    }
    MBDPlayerVibrateObjKill(handles[0]);
    MBDPlayerVibrateObjKill(handles[1]);
    MBDModelKill(obj);
    HuPrcSleep(15);
    HuAudFXPlay(0x159);
    MBDDlgWinExec(0x16, 0x1F2D);
    MBDAuraHoverStop();
    MBDAuraRiseExec(2);
    MBDAuraKill();
    CharFXPlay(0x286, GwPlayer[GwSystem.current_player_index].chr);
    MBDPlayerMotionSet(-1, 5, 0);
    MBDModelMotionWait(player->player_obj);
}

void MBD6Ev_HatenaCoinGain20(void) {
    GW_SYSTEM *sys = &GwSystem;

    MBDCoinChangeCreate(sys->current_player_index, 20);
    MBDCoinTakeCreate(sys->current_player_index, 20);
    HuPrcSleep(30);
}

void MBD6Ev_Hatena(void) {
    UnkBoard4 *sprite;
    void *data;
    s32 i;
    s32 offset;

    mbItemBtnF = 0;
    MBDStatusShrink(-1);
    HuAudFXPlay(0x204);
    sprite = MBDSprGrpCreate(2, 2);
    data = DataRead(0x130103);
    sprite->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 0, sprite->unk_0C[0], 0);
    HuSprPriSet(sprite->unk_0A, 0, 1);
    HuSprAttrSet(sprite->unk_0A, 0, 0x1000);
    HuSprPosSet(sprite->unk_0A, 0, 160, -32);
    HuSprScissorSet(sprite->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    sprite->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(sprite->unk_0A, 1, sprite->unk_0C[1], 0);
    HuSprPriSet(sprite->unk_0A, 1, 2);
    HuSprAttrSet(sprite->unk_0A, 1, 0x1000);
    HuSprPosSet(sprite->unk_0A, 1, 0, 0);
    HuSprScissorSet(sprite->unk_0A, 0, 16, 12, 304, 228);
    HuSprColorSet(sprite->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        HuSprPosSet(sprite->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    HuSprPosSet(sprite->unk_0A, 0, 160, 120);
    offset = 0;
    for (i = 0; i < 9; i++) {
        offset += i * 2;
        HuSprPosSet(sprite->unk_0A, 0, 160, 120 - offset);
        HuPrcVSleep();
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBDMgCallListProcCreate());
    HuPrcChildWatch();
    MBDSprGrpKill(sprite);
    MBDStatusGrow(-1);
    mbd6ev_hatenaFuncTbl[GwSystem.minigame_index - 1]();
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

void MBD6Ev_Merge4(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s32 spaceIndex = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (spaceIndex == MBDMasuLinkMasuIdGet(player->clink, player->cidx + 1)) {
        MBDMasuLinkIdxGet(0x13, &player->nlink, &player->nidx);
    }
}

void MBD6Ev_Merge1(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s32 spaceIndex = MBDMasuLinkMasuIdGet(player->blink, player->bidx);

    if (spaceIndex == MBDMasuLinkMasuIdGet(player->clink, player->cidx - 1)) {
        MBDMasuLinkIdxGet(0x14, &player->nlink, &player->nidx);
    }
}

void MBD6Ev_Merge2(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);

    if (!(player->rev & 1)) {
        MBDMasuLinkIdxGet(0x14, &player->nnlink, &player->nnidx);
    }
}

void MBD6Ev_Merge3(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);

    if (player->rev & 1) {
        MBDMasuLinkIdxGet(0x13, &player->nnlink, &player->nnidx);
    }
}

void MBD6Ev_StartWarpLinkGet(s8 *arg0, s8 *arg1) {
}

s32 MBD6_WalkAttackHook(void) {
    s32 playerIndex = GwSystem.current_player_index;
    s32 otherIndex = (playerIndex + 1) & 1;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    GW_PLAYER *otherPlayer = MBDPlayerGet(otherIndex);

    if (player->nlink == otherPlayer->clink && player->nidx == otherPlayer->cidx) {
        return 0;
    }
    return -1;
}

void MBD6Ev_PlayerDirFlip(s32 playerIndex) {
    s8 link[2];
    GW_PLAYER *player = MBDPlayerGet(playerIndex);

    link[0] = player->nlink;
    link[1] = player->nidx;
    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = link[0];
    player->bidx = link[1];
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        player->rev = 1;
        MBDMasuLinkIdxGet(1, &link[0], &link[1]);
        if (player->cidx == link[1]) {
            MBDMasuLinkIdxGet(0x13, &player->nnlink, &player->nnidx);
        } else {
            player->nnlink = -1;
            player->nnidx = -1;
        }
    } else {
        player->rev = 0;
        MBDMasuLinkIdxGet(0x12, &link[0], &link[1]);
        if (player->cidx == link[1]) {
            MBDMasuLinkIdxGet(0x14, &player->nnlink, &player->nnidx);
        } else {
            player->nnlink = -1;
            player->nnidx = -1;
        }
    }
}

void MBD6Ev_SwitchMasu(void) {
    Vec pos;
    Vec rot;
    s16 spaceIndex = MBDMasuCurGet();
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    SpaceData *space;
    s32 i;

    MBDPlayerMotionSet(-1, -1, 2);
    MBDVecForwardSet(&rot);
    MBDVecRotLerpCreate(&player->player_obj->rot, &rot, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    MBDStatusShrink(-1);
    for (i = 0; i < 5; i++) {
        if (mbd6ev_switchEventMasuTbl[i] == spaceIndex) {
            break;
        }
    }
    space = MBDMasuGet(mbd6_switchMasuTbl[i]);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &space->coords, &pos, 4.0f));
    HuPrcChildWatch();
    MBD6Ev_SwitchPressExec();
    GwSystem.boardData.halfWordBytes[0] ^= 1;
    MBD6Ev_PlayerDirFlip(0);
    MBD6Ev_PlayerDirFlip(1);
    MBDPartnerPosSwap(0);
    MBDPartnerPosSwap(1);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &player->player_obj->coords, &pos, 4.0f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
    MBDStatusGrow(-1);
    MBDDlgResultWinExec(0x2300);
}

void MBD6Ev_GateGuyWarpExec(void) {
    s8 link[2];
    Vec pos[3];
    s32 playerIndex = (s8)(GwSystem.current_player_index ^ 1);
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    SpaceData *space;

    MBDMasuLinkIdxGet(0x17, &link[0], &link[1]);
    MBDMoveMasuSet(playerIndex, link[0], link[1]);
    player->rev = 0;
    player->nnlink = -1;
    player->nnidx = -1;
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        MBD6Ev_PlayerDirFlip(playerIndex);
    }
    space = MBDMasuGet(0x17);
    HuVecAdd(&pos[0], &space->coords, &MBDMasuGet(0x1C)->coords);
    HuVecMulScalar(&pos[0], 0.5f, &pos[0]);
    HuVecCopy3F(&pos[1], &pos[0]);
    HuVecCopy3F(&pos[2], &pos[0]);
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        pos[1].x += 12.0f;
        pos[2].x -= 12.0f;
    } else {
        pos[1].x -= 12.0f;
        pos[2].x += 12.0f;
    }
    MBDWarpPosExec(playerIndex, &pos[0], &pos[1], &pos[2]);
}

void MBD6Ev_GateGuyMasuBranch(void) {
}
