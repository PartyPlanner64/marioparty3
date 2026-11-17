#include "common_duel.h"
#include "game/process.h"
#include "game/malloc.h"
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

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} Duel10SprGroup; // sizeof 0x08

typedef struct Duel10CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel10CamShakeWork; // sizeof 0x10

typedef struct Duel10SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel10SpriteWork; // sizeof 0x10

typedef struct Duel10PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel10PartnerAttackWork; // sizeof 0x10

typedef struct Duel10SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel10SwayWork; // sizeof 0x10

typedef struct Duel10PartnerRouletteWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ char unk_04[0xC];
} Duel10PartnerRouletteWork; // sizeof 0x10

typedef struct Duel10WinColorWork {
    /* 0x00 */ s32 window;
    /* 0x04 */ char unk_04[0xC];
} Duel10WinColorWork; // sizeof 0x10

// Board space indices used when a player picks up a partner.
typedef struct Duel10PartnerSpaces {
    /* 0x00 */ s32 returnSpace;
    /* 0x04 */ s32 startSpace;
    /* 0x08 */ s32 partnerSpace;
} Duel10PartnerSpaces; // sizeof 0xC

extern Vec mbdAttackCameraPos;
extern u8 mbdSaiHitLockF;

void MBDCameraFocusVecSet(Vec *arg0);
void MBDPartnerAttackFuncSet(PartnerFunc *, PartnerFunc *);
void MBD10_DodgeProc(void);
void MBDSaiValueForceSet(s32, s32);
void MBD10Ev_PlayerWalkExecEx(s32, s32);
void MBD10Ev_GuideWinExec(UnkOvl81_2 *guide, u32 mess);
void MBDWinComKeyAnyWait(s16);
void MBDCameraRefresh(void);
Process *MBDMgCallListProcCreate(void);
s32 MBDTurnCoinGet(void);
void MBDMasuEventTblAdd(event_table_entry *);
void MBDWalkAttackHookSet(s32 (*)(void));
void MBDHatenaFuncSet(process_func);
void MBDCameraFocusProc(void);
void MBD10Ev_TutorialProc(void);
void MBD10Ev_Hatena(void);
s32 MBD10_WalkAttackHook(void);
void MBDPlayerPartyMotionSet(s32 playerIndex, s16 arg1, u16 arg2);
void MBDMasuPassSePlay(s16 arg0);
void MBDMasuLandSePlay(s16 arg0);
void MBD10Ev_PartnerRouletteProc(void);
void MBD10Ev_PartnerRouletteWinColorProc(void);
void MBD10_PartnerAttackInit(void);
void MBD10_GateGuyCreate(void);
void MBD10_PartnerBox1Create(void);
void MBD10_PartnerBox2Create(void);
void MBDCameraFocusObjSet(Object *);
void MBDPlayerMotionSet(s32, s32, s32);
void *memcpy(void *, const void *, unsigned int);
extern const Vec mbd10ev_partnerVanishOfsTbl[];
void MBD10Ev_PartnerBox1SwayProc(void);
void MBD10Ev_PartnerBox2SwayProc(void);
s32 MBDCameraStopCheck(void);
void MBDPartnerAttackMotSet(Object *, s32, s32);
Process *MBDCoinScatterCreate(Object *, s32, s32, s32, s32);
void MBD10_KoopaJrChangeExec(Object *obj, s32 swap);
void MBD10_KoopaJrChangeEndExec(Object *obj);
void MBD10_NokonokoAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_KuriboAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_KinopioAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_BomheiAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_WhompAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_DossunAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_TeresaAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_BlizzardAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_KoopaFireObjMain(omObjData *);
void MBD10_KoopaJrAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_WanwanAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_SnifitAttackExec(s32, s32, Object *, Object *, s32, s32);
void MBD10_PakkunAttackExec(s32, s32, Object *, Object *, s32, s32);
extern s16 mbdWinId;
void MBDMgCallListStart(s32 arg0);
void MBDMgCallListClose(void);
void MBDMasuTypeSet(s16 spaceIdx, u16 newSpaceType);
void MBDGuideFaceCreate(Object *obj, s16 slot, s16 chr, s32 dataNum);
void MBDGuideFaceSet(Object *obj, s32 dataNum);
void MBDPartnerDamageExec(s32 playerIndex, s32 frontOrBackIndex, s32 targetIndex, s32 starDamage, s32 hpDamage, s32 selfStarDamage, s32 selfHpDamage);
void MBD10Ev_MasuCoinExec(void);
void MBD10Ev_GuideMotProc(void);
void MBD10Ev_PartnerGetExec(s32 index, s32 comSelectSecond);
void MBD10Ev_PartnerSet(s32 playerIndex, s32 frontOrBack, s32 partner);
void MBD10Ev_PartnerClear(s32 playerIndex, s32 frontOrBack);
void MBD10Ev_PartnerAppearExec(s32 playerIndex, s32 frontOrBack, s32 partnerId);
void MBD10Ev_PartnerVanishExec(s32 playerIndex);
void MBD10Ev_SnifitCoinGiftExec(void);
void MBD10Ev_GateGuyMasu(void);
void MBD10Ev_HatenaEnd(void);

s32 mbd10_mesSpeedSave = 1;

s32 mbd10ev_guideFaceTbl[] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084, 0xA0085 };

s32 mbd10_attackDashMdlTbl[] = { 55, 57 };

s32 mbd10_koopaMot[] = { 4, 0xA0035, 0xA003A, 0xA003B, 0xA003F };

s32 mbd10ev_captionSprTbl[] = { 0x130014, 0x130002, 0x130003, 0x130004, 0x130005, 0x130006, 0x130007, 0x130008 };

s32 mbd10_pauseOnF = 1;

s32 mbd10ev_guideMot[] = { 1, 0xA0078 };

s32 mbd10ev_guideWinDoneF = 0;

s16 mbd10ev_guideMotNo = -1;

f32 mbd10_gateGuyScrewSpeed = 3.0f;

s32 mbd10_gateGuyMot[] = { 3, 0xA011D, 0xA011E, 0xA0121 };

s16 mbd10_partnerBox1Masu = 17;

s16 mbd10_partnerBox1DirMasu = 15;

Process *mbd10ev_partnerBox1SwayProc = NULL;

s16 mbd10_partnerBox2Masu = 18;

s16 mbd10_partnerBox2DirMasu = 16;

Process *mbd10ev_partnerBox2SwayProc = NULL;

s32 mbd10ev_coinScatterCnt = 0;

Duel10PartnerSpaces mbd10ev_partnerMasuTbl[] = {
    { 13, 15, 17 },
    { 14, 16, 18 }
};

s32 mbd10ev_partnerRouletteResult = -1;

Object *mbd10ev_partnerGetMdl = NULL;

s32 mbd10ev_partnerRouletteColorF = 0;

event_list_entry mbd10_gateGuyMasuEventTbl[] = {
    { 1, 1, MBD10Ev_GateGuyMasu },
    { 0, 0, NULL }
};

event_table_entry mbd10_commonEventTbl[] = {
    { 19, mbd10_gateGuyMasuEventTbl },
    { -1, NULL }
};

event_table_entry mbd10_specialEventTbl[] = {
    { -1, NULL }
};

DuelHelpWin *mbd10_branchStickHelp BSS;
DuelHelpWin *mbd10_branchItemHelp BSS;
DuelHelpWin *mbd10_branchBtnHelp BSS;
DuelHelpWin *mbd10_branchMapScrollHelp BSS;
Object *mbd10_bomheiFrontMdl BSS;
Object *mbd10_bomheiBackMdl BSS;
Object *mbd10_koopaMdl BSS;
omObjData *mbd10_koopaFireObj BSS;
UnkOvl81_2 *mbd10ev_guide BSS;
Object *mbd10_gateGuyMdl BSS;
Process *mbd10_gateGuyScrewProc BSS;
Object *mbd10_partnerBox1Mdl BSS;
f32 mbd10ev_partnerBox1SwayAmp BSS;
Object *mbd10_partnerBox2Mdl BSS;
f32 mbd10ev_partnerBox2SwayAmp BSS;
UnkBoard4 *mbd10ev_hatenaSprGrp BSS;

void MBD10_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBDMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MBD10_BranchHelpStart(void) {
    while (MBDCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mbd10_branchStickHelp = MBDHelpWinCreate(0, 0xA0, 1);
    mbd10_branchItemHelp = MBDHelpWinCreate(0xD, 0xAE, 1);
    mbd10_branchBtnHelp = MBDHelpWinCreate(1, 0xBC, 1);
    mbd10_branchMapScrollHelp = MBDHelpWinCreate(3, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MBD10_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBDHelpWinKill(mbd10_branchStickHelp);
    MBDHelpWinKill(mbd10_branchItemHelp);
    MBDHelpWinKill(mbd10_branchBtnHelp);
    MBDHelpWinKill(mbd10_branchMapScrollHelp);
}

void MBD10_BoardInit(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(duelcall, 0, 0x4190);
}

void MBD10_SaveInit(void) {
    s8 sp10;
    s8 sp11;

    omInitObjMan(0xA, 0);
    MBDMasuInit();
    MBDMasuCreate(0x13, 0x247);
    MBDMasuLinkIdxGet(0xD, &sp10, &sp11);
    MBDMoveMasuSet(0, sp10, sp11);
    MBDMasuLinkIdxGet(2, &sp10, &sp11);
    MBDMoveMasuSet(1, sp10, sp11);
    GwPlayer[0].nnlink = -1;
    GwPlayer[0].nnidx = -1;
    GwPlayer[1].nnlink = -1;
    GwPlayer[1].nnidx = -1;
    GwPlayer[0].stat = 1;
    GwPlayer[1].stat = 1;
    GwPlayer[2].stat = 1;
    GwPlayer[3].stat = 1;
    GwPlayer[0].chr = 0;
    GwPlayer[1].chr = 1;
    GwPlayer[0].pad = 0;
    GwPlayer[1].pad = 1;
    GwPlayer[2].pad = 2;
    GwPlayer[3].pad = 3;
    GwPlayer[0].coin = 10;
    GwPlayer[1].coin = 10;
    GwSystem.current_turn = 1;
    GwSystem.current_player_index = 0;
    MBDMasuKill();
    MBDMasuClose();
    MBDPartnerSet(0, 0, 0);
    MBDPartnerSet(1, 1, 1);
    GwSystem.bank_coins = 5;
    GwSystem.playerIndexVisitingBowser = 0;
    MBDMasuOwnerInit();
    omOvlReturnEx(1);
}

void MBD10_AttackEffDirGet(Vec *arg0, Vec *arg1, Vec *arg2) {
    f32 angle;

    MBDVecDirGet(arg0, arg1, arg2);
    angle = MBDVecAngleGet(arg2) + 15.0f;
    arg2->x = sindf(angle);
    arg2->z = cosdf(angle);
}

void MBD10_MissMarkProc(void) {
    Duel10SpriteWork *work = HuPrcCurrentGet()->user_data;
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
    HuSprAttrSet(sprite->unk_0A, 0, HUSPR_ATTR_NONE);
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

Process *MBD10_MissMarkCreate(Object *object) {
    Process *process;
    Duel10SpriteWork *work;

    process = omAddPrcObj(MBD10_MissMarkProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10SpriteWork));
    process->user_data = work;
    work->pos.x = object->coords.x;
    work->pos.y = object->coords.y;
    work->pos.z = object->coords.z;
    return process;
}

void MBD10_DodgeProc(void) {
    Process *process = HuPrcCurrentGet();
    Duel10PartnerAttackWork *work = HuPrcCurrentGet()->user_data;
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
    MBD10_MissMarkCreate(obj);
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

Process *MBD10_DodgeCreate(GW_PLAYER *player, Object *obj, s32 delay, s32 waitTime) {
    Process *process;
    Duel10PartnerAttackWork *work;

    process = omAddPrcObj(MBD10_DodgeProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10PartnerAttackWork));
    process->user_data = work;
    work->player = player;
    work->obj = obj;
    work->delay = delay;
    work->waitTime = waitTime;
    return process;
}

void MBD10_AttackTargetPosGet(Object *obj, Object *target, GW_PLAYER *player, Vec *targetPos, Vec *origPos, f32 dist) {
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

void MBD10_AttackCameraFocusSet(void) {
    MBDCameraFocusVecSet(&mbdAttackCameraPos);
}

Process *MBD10_AttackCameraSpeedMoveCreate(Object *arg0, GW_PLAYER *arg1, s32 arg2, f32 arg3) {
    Process *process;

    arg3 = arg3 + 0.5f;
    if (arg2 & 9) {
        process = MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &arg0->coords, &mbdAttackCameraPos, arg3);
    } else {
        process = MBDVecSpeedMoveCreate(&mbdAttackCameraPos, &arg1->player_obj->coords, &mbdAttackCameraPos, arg3);
    }
    return process;
}

void MBD10_AttackCameraTimeMoveCreate(Object *arg0, GW_PLAYER *arg1, s32 arg2, s32 arg3) {
    if (arg2 & 9) {
        MBDPlayerPosMoveCreate(&mbdAttackCameraPos, &arg0->coords, &mbdAttackCameraPos, arg3);
    } else {
        MBDPlayerPosMoveCreate(&mbdAttackCameraPos, &arg1->player_obj->coords, &mbdAttackCameraPos, arg3);
    }
}

void MBD10_CameraShakeProc(void) {
    Duel10CamShakeWork *work = HuPrcCurrentGet()->user_data;
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

Process *MBD10_CameraShakeCreate(s32 magnitude, s32 decay) {
    Process *process;
    Duel10CamShakeWork *work;

    process = omAddPrcObj(MBD10_CameraShakeProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10CamShakeWork));
    process->user_data = work;
    work->magnitude = magnitude;
    work->decay = decay;
    return process;
}

void MBD10_BomheiMdlSwap(s32 playerIndex, s32 mode) {
    GW_PLAYER *player;
    Object *partner;
    Object *model;

    player = MBDPlayerGet(playerIndex);
    switch (mode) {
        case 0:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                model = MBDModelCreate(0x28, NULL);
                mbd10_bomheiFrontMdl = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                MBDModelDispOff(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                model = MBDModelCreate(0x28, NULL);
                mbd10_bomheiBackMdl = model;
                HuVecCopy3F(&model->coords, &partner->coords);
                HuVecCopy3F(&model->rot, &partner->rot);
                MBDModelDispOff(partner);
            }
            break;
        case 1:
            if (player->stats.partners.frontID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_FRONT);
                MBDModelKill(mbd10_bomheiFrontMdl);
                MBDModelDispOn(partner);
            }
            if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                MBDModelKill(mbd10_bomheiBackMdl);
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
                        mbd10_bomheiFrontMdl = model;
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
                        mbd10_bomheiBackMdl = model;
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
                        MBDModelKill(mbd10_bomheiFrontMdl);
                        MBDModelDispOn(partner);
                    }
                    break;
                case 0:
                case 2:
                    if (player->stats.partners.backID == PARTNER_BOB_OMB) {
                        partner = MBDPartnerObjGet(playerIndex, PARTNER_BACK);
                        MBDModelKill(mbd10_bomheiBackMdl);
                        MBDModelDispOn(partner);
                    }
                    break;
            }
            break;
    }
}

Object *MBD10_AttackEffMdlCreate(s32 arg0) {
    Object *obj;

    obj = MBDModelCreate(arg0 & 0xFF, 0);
    Hu3DModelAttrSet(obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    MBDModelTempAllocFree(obj);
    MBDModelDispOff(obj);
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    return obj;
}

void MBD10_AttackEffMdlDispOn(Object *arg0, Vec *arg1) {
    MBDModelDispOn(arg0);
    Hu3DMotionAttrSet(arg0->omObj1->model[0], 3, 0);
    HuVecCopy3F(&arg0->coords, arg1);
}

void MBD10_NokonokoAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        effect = MBD10_AttackEffMdlCreate(0x45);
    }
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    if (mode == 2) {
        extra = MBDModelCreate(0x56, NULL);
        MBDModelTempAllocFree(extra);
        MBDModelDispOff(extra);
    }
    MBD10_AttackCameraFocusSet();
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
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
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
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    if (flags & 8) {
        MBD10_DodgeCreate(player, target, HuVecGetLength3F(&delta) / 3.0f, 20);
        HuPrcChildWatch();
        MBDModelDispOff(partner);
    } else {
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        if (mode == 1) {
            MBD10_AttackEffMdlDispOn(effect, &obj->coords);
        }
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            MBDEffMdlCreate(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                MBD10_AttackEffDirGet(&target->coords, &effect->coords, &effect->rot);
                MBD10_AttackEffMdlDispOn(effect, &target->coords);
            } else {
                model = MBDEffExplodeCreate(0xB0025, "obj1");
                MBDEffExplodePosSet(model, &midPos);
            }
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
            HuVecMulScalar(mid, 0.5f, mid);
            MBDEffMdlCreate(0x4A, mid, 0, 2.0f);
            if (mode == 1) {
                MBD10_AttackEffDirGet(&player->player_obj->coords, &effect->coords, &effect->rot);
                MBD10_AttackEffMdlDispOn(effect, &player->player_obj->coords);
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

void MBD10_KuriboAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    effect = MBD10_AttackEffMdlCreate(effectModels[mode - 1]);
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
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
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 7.0f);
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
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
        MBD10_DodgeCreate(player, target, 0, 20);
    } else {
        HuPrcSleep(3);
        MBD10_AttackEffMdlDispOn(effect, &obj->coords);
        HuAudFXPlay(0x25B);
        mid = &midPos;
        if (flags & 1) {
            HuVecAdd(mid, &target->coords, &obj->coords);
        } else {
            HuVecAdd(mid, &player->player_obj->coords, &obj->coords);
        }
        HuVecMulScalar(mid, 0.5f, mid);
        midPos.y += obj->velocity.x;
        MBD10_AttackEffMdlDispOn(effect, mid);
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

void MBD10_KinopioAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    effect = MBD10_AttackEffMdlCreate(effectModels[mode - 1]);
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    hook = MBDModelCreate(0x3F, NULL);
    MBDModelDispOff(hook);
    MBDModelHookSet(obj, "item_hook", hook->omObj1->model[0]);
    MBDMotionSet(obj, 0, 2);
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
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
        MBD10_DodgeCreate(player, target, 0, 20);
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
            MBD10_AttackEffMdlDispOn(effect, mid);
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

void MBD10_BomheiAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    effect = MBD10_AttackEffMdlCreate(effectModels[mode - 1]);
    HuVecCopyXYZ(&effect->scale, 2.0f, 2.0f, 2.0f);
    if (mode == 2) {
        HuPrcVSleep();
        extra = MBD10_AttackEffMdlCreate(0x5B);
        HuPrcVSleep();
    }
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
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
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 2.0f);
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
        MBD10_AttackEffMdlDispOn(extra, &obj->coords);
        Hu3DMotionSpeedSet(extra->omObj1->model[0], 2.0f);
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
        MBDBackTPLvlSet(0xFF);
        HuPrcVSleep();
        MBD10_AttackEffMdlDispOn(effect, mid);
        MBDBackTPLvlSet(0x40);
        HuPrcVSleep();
    }
    if (mode == 1) {
        MBD10_AttackEffMdlDispOn(effect, &midPos);
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

void MBD10_WhompAttackExec(s32 playerIndex, s32 arg1, Object *arg2, Object *arg3, s32 arg4, s32 arg5) {
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

void MBD10_DossunAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    effect = MBD10_AttackEffMdlCreate(0x55);
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 9.0f);
    for (height = 0.0f; height <= 20.0f; height += 2.0f) {
        obj->velocity.x = height;
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
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
                MBD10_DodgeCreate(player, target, 0, 55);
            } else {
                MBD10_DodgeCreate(player, target, 0, 120);
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
            MBD10_BomheiMdlSwap(targetPlayer, 2);
            if (mode == 1) {
                MBDModelBillboardSet(effect);
                MBD10_AttackEffMdlDispOn(effect, &target->coords);
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
            MBD10_CameraShakeCreate(10, 1);
            HuPrcSleep(40);
        } else {
            HuPrcChildLink(process, MBD10_CameraShakeCreate(5, 2));
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
                    MBD10_AttackEffMdlDispOn(effect, &obj->coords);
                    MBDEffMdlCreate(0x47, &obj->coords, NULL, 1.0f);
                } else {
                    HuAudFXPlay(0x1E9);
                    smoke = MBDModelCreate(0x5A, NULL);
                    MBDModelMotionKillCreate(smoke);
                    HuVecCopy3F(&smoke->coords, &obj->coords);
                }
                HuPrcChildLink(process, MBD10_CameraShakeCreate(5, 2));
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
        MBD10_BomheiMdlSwap(targetPlayer, 3);
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

void MBD10_TeresaCounterExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 0.0f);
    HuVecSubtract(&dir, &obj->coords, &targetPos);
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
    targetPos.y -= 5.0f;
    HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 3.0f));
    steps = HuVecGetLength3F(&dir) / 3.0f;
    obj->flags |= 1;
    if (flags & 8) {
        MBD10_DodgeCreate(player, target, HuVecGetLength3F(&dir) / 3.0f, 20);
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

void MBD10_TeresaAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        MBD10_TeresaCounterExec(playerIndex, targetPlayer, obj, target, flags, 1);
        return;
    }
    mode &= ~0x10;
    MBDMotionSet(obj, 0, 2);
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 6.0f);
    MBD10_AttackTargetPosGet(obj, target, player, &nearPos, &origPos, 8.0f);
    MBD10_AttackCameraFocusSet();
    for (i = 0; i < 10; i++) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], ~((i * 255) / 10));
        Hu3DModelTPLvlSet(obj->omObj2->model[0], ~((i * 255) / 10));
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
    HuPrcChildLink(process, MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f));
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
            MBD10_DodgeCreate(player, target, 0, 20);
        } else {
            MBD10_DodgeCreate(player, target, 0, 40);
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

void MBD10_BlizzardAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        extra = MBD10_AttackEffMdlCreate(0x51);
        HuVecCopyXYZ(&extra->scale, 2.0f, 2.0f, 2.0f);
        HuPrcVSleep();
    }
    effect = MBD10_AttackEffMdlCreate(0x4C);
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
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraTimeMoveCreate(target, player, flags, 30);
    if (flags & 8) {
        HuVecCopy3F(&effectPos, &target->coords);
        effectPos.y += 5.0f;
        MBD10_DodgeCreate(player, target, 25, 40);
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
        MBD10_AttackEffMdlDispOn(effect, &effectPos);
        if (mode == 2) {
            MBD10_AttackEffMdlDispOn(extra, &effectPos);
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
        MBD10_AttackEffMdlDispOn(effect, &effectPos);
        if (mode == 2) {
            MBD10_AttackEffMdlDispOn(extra, &effectPos);
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

void MBD10_KoopaJrChangeExec(Object *obj, s32 swap) {
    Object *model;
    f32 scale;
    f32 angle;

    if (swap) {
        mbd10_koopaMdl = MBDModelCreate(8, mbd10_koopaMot);
        MBDModelTempAllocFree(mbd10_koopaMdl);
        MBDModelDispOff(mbd10_koopaMdl);
    } else {
        HuPrcSleep(3);
    }
    model = MBDModelCreate(0x21, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
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
        HuVecCopy3F(&mbd10_koopaMdl->coords, &obj->coords);
        HuVecCopy3F(&mbd10_koopaMdl->rot, &obj->rot);
        MBDModelDispOn(mbd10_koopaMdl);
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

void MBD10_KoopaJrChangeEndExec(Object *obj) {
    Object *model;
    f32 scale;
    f32 angle;

    model = MBDModelCreate(0x21, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &mbd10_koopaMdl->coords);
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

    HuVecCopy3F(&obj->coords, &mbd10_koopaMdl->coords);
    HuVecCopy3F(&obj->rot, &mbd10_koopaMdl->rot);
    MBDModelKill(mbd10_koopaMdl);
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

void MBD10_KoopaFireObjCreate(void) {
    UnkDuelObjData *data;
    void *sprData;
    s32 i;

    Hu3DSprModelInit(0x1A);
    mbd10_koopaFireObj = omAddObj(0x1F4, 0, 0, -1, MBD10_KoopaFireObjMain);
    data = mbd10_koopaFireObj->data = HuMemAllocTag(sizeof(UnkDuelObjData), 0x7918);
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
    mbd10_koopaFireObj->work[0] = 0;
    data->spawnTimer = 0;
}

void MBD10_KoopaFireObjMain(omObjData *object) {
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
                Hu3DModelAttrSet(data->modelId[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
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
                data->vel[i].x = mbd10_koopaMdl->rot.x;
                data->vel[i].y = -0.8f;
                data->vel[i].z = mbd10_koopaMdl->rot.z;
                MBDVecNormalize(&data->vel[i]);
                data->vel[i].x *= 2.0f;
                data->vel[i].y *= 2.0f;
                data->vel[i].z *= 2.0f;
                data->pos[i].x = mbd10_koopaMdl->rot.x * 10.0f + mbd10_koopaMdl->coords.x;
                data->pos[i].z = mbd10_koopaMdl->rot.z * 10.0f + mbd10_koopaMdl->coords.z;
                data->pos[i].y = mbd10_koopaMdl->coords.y + 6.0f;
                data->life[i] = 15.0f;
                data->scale[i] = 0.1f;
                Hu3DModelAttrSet(data->modelId[i], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                Hu3DSprModelReset(data->sprId[i]);
                Hu3DModelPosSet(data->modelId[i], data->pos[i].x, data->pos[i].y, data->pos[i].z);
                Hu3DModelScaleSet(data->modelId[i], data->scale[i], data->scale[i], data->scale[i]);
                Hu3DModelCameraSet(data->modelId[i], HU3D_CAM0);
            }
        } else {
            data->spawnTimer--;
        }
    }
}

s16 MBD10_KoopaFireActiveCheck(void) {
    UnkDuelObjData *data = mbd10_koopaFireObj->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->active); i++) {
        if (data->active[i] != 0) {
            return 1;
        }
    }
    return 0;
}

void MBD10_KoopaFireObjKill(void) {
    UnkDuelObjData *data = mbd10_koopaFireObj->data;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(data->sprId); i++) {
        Hu3DSprModelKill(data->sprId[i]);
    }
    omDelObj(mbd10_koopaFireObj);
    Hu3DSprModelAllKill();
}

void MBD10_KoopaFireStart(void) {
    mbd10_koopaFireObj->work[0] = 1;
}

void MBD10_KoopaFireStop(void) {
    mbd10_koopaFireObj->work[0] = 0;
}

void MBD10_KoopaJrAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
        Hu3DModelLayerSet(partner->omObj1->model[0], 0);
        Hu3DModelRemakeStatic(partner->omObj1->model[0]);
        MBDModelTempAllocFree(partner);
        MBDModelDispOff(partner);
        MBDPartnerAttackMotSet(obj, 0, 0);
        MBDModelMotionWait(obj);
        MBD10_KoopaJrChangeExec(obj, 1);
        HuAudFXPlay(0x29C);
        MBDMotionSet(mbd10_koopaMdl, 0, 2);
        HuVecCopy3F(&origPos, &mbd10_koopaMdl->coords);
        HuVecCopy3F(&origRot, &mbd10_koopaMdl->rot);
        if (target != NULL) {
            HuVecCopy3F(&targetPos, &target->coords);
        } else {
            HuVecCopy3F(&targetPos, &player->player_obj->coords);
        }
        MBDVecDirGet(&mbd10_koopaMdl->coords, &targetPos, &mbd10_koopaMdl->rot);
        angle = MBDVecAngleGet(&mbd10_koopaMdl->rot) + 180.0f;
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
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&mbd10_koopaMdl->coords, &targetPos, &mbd10_koopaMdl->coords, 0.5f));
        MBD10_AttackCameraFocusSet();
        MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 0.8f);
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &mbd10_koopaMdl->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 0.5f));
        HuPrcChildWatch();
        MBDModelDispOff(partner);
        if (mode == 1) {
            MBDMotionSet(mbd10_koopaMdl, 3, 0);
            if (flags & 8) {
                MBD10_DodgeCreate(player, target, 0, 50);
            } else {
                HuPrcSleep(8);
                mid = &midPos;
                if (flags & 1) {
                    HuVecAdd(mid, &target->coords, &mbd10_koopaMdl->coords);
                } else {
                    HuVecAdd(mid, &player->player_obj->coords, &mbd10_koopaMdl->coords);
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
            MBDModelMotionWait(mbd10_koopaMdl);
            MBDMotionSet(mbd10_koopaMdl, -1, 2);
            HuPrcSleep(20);
        } else {
            MBDMotionSet(mbd10_koopaMdl, 1, 0);
            HuPrcSleep(30);
            MBD10_KoopaFireObjCreate();
            MBD10_KoopaFireStart();
            HuAudFXPlay(0x1E4);
            if (flags & 8) {
                MBD10_DodgeCreate(player, target, 0, 50);
            }
            MBDModelMotionWait(mbd10_koopaMdl);
            MBDMotionSet(mbd10_koopaMdl, 2, 2);
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
            MBD10_KoopaFireStop();
            while (MBD10_KoopaFireActiveCheck()) {
                HuPrcVSleep();
            }
            MBDMotionShiftSet(mbd10_koopaMdl, -1, 0, 5, 2);
            HuPrcSleep(10);
            MBD10_KoopaFireObjKill();
        }
        MBD10_KoopaJrChangeEndExec(obj);
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
        MBD10_KoopaJrChangeExec(obj, 0);
        HuAudFXPlay(0x2A0);
        MBD10_MissMarkCreate(obj);
        HuPrcSleep(10);
        MBDPartnerAttackMotSet(obj, 1, 0);
        MBDModelMotionWait(obj);
        MBDMotionSet(obj, -1, 2);
    }
    MBDPartnerAttackMotKill();
}

void MBD10_WanwanAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
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
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, 0, 7.0f);
    if (mode == 1) {
        MBDPartnerAttackMotSet(obj, 0, 2);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&obj->coords, &targetPos, &obj->coords, 7.0f));
        MBDModelDispOn(partner);
        Hu3DMotionTimeSet(partner->omObj1->model[0], 0.0f);
        HuVecCopy3F(&partner->coords, &obj->coords);
        MBDVecDirGet(&partner->coords, &targetPos, &partner->rot);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&partner->coords, &targetPos, &partner->coords, 7.0f));
        for (i = 0;; i++) {
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
        MBD10_BomheiMdlSwap(targetPlayer, 0);
        MBDModelJumpWait(obj);
        HuAudFXPlay(0x1F0);
        HuPrcChildLink(process, MBD10_CameraShakeCreate(10, 1));
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
        MBD10_BomheiMdlSwap(targetPlayer, 1);
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

void MBD10_SnifitAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        effect1 = MBD10_AttackEffMdlCreate(0x4C);
        HuPrcVSleep();
        effect2 = MBD10_AttackEffMdlCreate(0x53);
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
    MBD10_AttackCameraFocusSet();
    MBDModelDispOn(partner);
    HuPrcChildLink(process, MBDVecSpeedMove2Create(&partner->coords, &targetPos, &partner->coords, 4.0f));
    HuPrcChildLink(process, MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 4.0f));
    HuVecCopy3F(&pos, &obj->rot);
    MBDVecNormalize(&pos);
    HuVecMulScalar(&pos, 6.0f, &pos);
    HuVecAdd(&pos, &pos, &partner->coords);
    pos.y += 5.0f;
    MBDEffMdlCreate(0x4E, &pos, 0, 0.5f);
    if (mode == 2) {
        MBDModelDispOn(partner2);
        Hu3DModelAttrSet(partner2->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
        Hu3DModelLayerSet(partner2->omObj1->model[0], 0x800);
        HuVecCopy3F(&partner2->coords, &partner->coords);
        partner2->velocity.x = 5.0f;
        HuPrcChildLink(process, MBDVecSpeedMove2Create(&partner2->coords, &targetPos, &partner2->coords, 4.0f));
        HuAudFXPlay(0x1DA);
    } else {
        HuAudFXPlay(0x1D9);
    }
    if (flags & 8) {
        MBD10_DodgeCreate(player, target, 0, 20);
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
            MBD10_AttackEffMdlDispOn(effect1, &pos);
            HuVecCopyXYZ(&effect1->scale, 2.0f, 2.0f, 2.0f);
            MBD10_AttackEffMdlDispOn(effect2, &pos);
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

void MBD10_PakkunAttackExec(s32 playerIndex, s32 targetPlayer, Object *obj, Object *target, s32 flags, s32 mode) {
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
        effect = MBD10_AttackEffMdlCreate(0x45);
    }
    partner = MBDModelCreate(mbd10_attackDashMdlTbl[mode - 1], NULL);
    Hu3DModelLayerSet(partner->omObj1->model[0], 0);
    Hu3DModelRemakeStatic(partner->omObj1->model[0]);
    MBDModelTempAllocFree(partner);
    MBDModelDispOff(partner);
    MBDPartnerAttackMotLoad(7);
    MBDMotionSet(obj, 0, 2);
    MBD10_AttackTargetPosGet(obj, target, player, &targetPos, &origPos, 7.5f);
    MBD10_AttackCameraFocusSet();
    MBD10_AttackCameraSpeedMoveCreate(target, player, flags, 3.0f);
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
        MBD10_DodgeCreate(player, target, 0, 30);
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
            MBD10_AttackEffMdlDispOn(effect, &midPos);
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

void MBD10_PartnerAttackInit(void) {
    PartnerFunc attackFuncs[12] = {
        MBD10_NokonokoAttackExec,
        MBD10_KuriboAttackExec,
        MBD10_KinopioAttackExec,
        MBD10_BomheiAttackExec,
        MBD10_TeresaAttackExec,
        MBD10_WhompAttackExec,
        MBD10_SnifitAttackExec,
        MBD10_PakkunAttackExec,
        MBD10_WanwanAttackExec,
        MBD10_DossunAttackExec,
        MBD10_BlizzardAttackExec,
        MBD10_KoopaJrAttackExec,
    };
    PartnerFunc otherFuncs[12] = {
        NULL,
        NULL,
        NULL,
        NULL,
        MBD10_TeresaAttackExec,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    MBDPartnerAttackFuncSet(attackFuncs, otherFuncs);
}

void MBD10_ObjectSetup(void) {
    omInitObjMan(0xA0, 0x50);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBDObjectSetup(0x1E, 0x247, 0);
    MBDMasuOwnerTypeUpdate();
    MBDMasuTypeListCreate();
    MBD10_GateGuyCreate();
    MBD10_PartnerBox1Create();
    MBD10_PartnerBox2Create();
    MBD10_PartnerAttackInit();
}

void MBD10Ev_ScissorWipeOut(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBDScissorWipeOutStart());
    HuPrcChildWatch();
}

void MBD10Ev_ScissorWipeIn(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBDScissorWipeInStart());
    HuPrcChildWatch();
}

Duel10SprGroup *MBD10Ev_CaptionCreate(s16 arg0, s16 x, s16 y) {
    Duel10SprGroup *group;
    void *data;

    group = HuMemMemoryAllocPerm(sizeof(Duel10SprGroup));
    group->spriteGroup = HuSprGrpCreate(3, 0);

    data = DataRead(0x130000);
    group->sprites[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 0, group->sprites[0], 0);
    HuSprPriSet(group->spriteGroup, 0, 0xB);
    HuSprAttrSet(group->spriteGroup, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 0, x + 5, y);
    DataClose(data);

    data = DataRead(0x130001);
    group->sprites[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 1, group->sprites[1], 0);
    HuSprPriSet(group->spriteGroup, 1, 0xC);
    HuSprAttrSet(group->spriteGroup, 1, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 1, x + 5, y);
    HuSprColorSet(group->spriteGroup, 1, 0x1F, 0xB0, 0x3F);
    DataClose(data);

    data = DataRead(mbd10ev_captionSprTbl[arg0]);
    group->sprites[2] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 2, group->sprites[2], 0);
    HuSprPriSet(group->spriteGroup, 2, 0xA);
    HuSprAttrSet(group->spriteGroup, 2, HUSPR_ATTR_XLU);
    HuSprPosSet(group->spriteGroup, 2, x, y);
    DataClose(data);

    return group;
}

void MBD10Ev_CaptionKill(Duel10SprGroup *arg0) {
    HuSprAnimKill(arg0->sprites[0]);
    HuSprAnimKill(arg0->sprites[1]);
    HuSprAnimKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreePerm(arg0);
}

s16 MBD10_PauseQuitCheck(s32 player) {
    UnkBoard4 *dimmer;
    UnkBoard4 *icon;
    void *data;
    s16 size[2];
    s16 win;
    s16 choice;

    HuAudSeqVolSet(0x60);
    dimmer = MBDSprGrpCreate(1, 0);
    data = DataRead(0x13025D);
    dimmer->unk_0C[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(dimmer->unk_0A, 0, dimmer->unk_0C[0], 0);
    HuSprPriSet(dimmer->unk_0A, 0, 9);
    HuSprAttrSet(dimmer->unk_0A, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(dimmer->unk_0A, 0, 0xA0, 0x78);
    HuSprScaleSet(dimmer->unk_0A, 0, 40.0f, 30.0f);
    HuSprColorTPLvlSet(dimmer->unk_0A, 0, 0, 0, 0, 0xC0);
    DataClose(data);

    icon = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130009);
    icon->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(icon->unk_0A, 0, icon->unk_0C[0], 0);
    HuSprPriSet(icon->unk_0A, 0, 8);
    HuSprAttrSet(icon->unk_0A, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(icon->unk_0A, 0, 0xA0, 0x78);
    HuSprColorSet(icon->unk_0A, 0, 0x89, 0xCA, 0xB2);

    HuWinMesMaxSizeGet(1, size, 0x253A);
    win = HuWinCreate(160 - size[0] / 2, 120 - size[1] / 2, size[0], size[1], 0, 2);
    HuWinPriSet(win, 5);
    HuWinBGTPLvlSet(win, 0);
    HuWinDummy(win);
    HuWinMesPalSet(win, 7, 0, 0, 0xE0);
    HuWinMesPalSet(win, 0, 0x89, 0xCA, 0xB2);
    HuWinMesPalSet(win, 4, 0, 0x80, 0);
    HuWinBGColSet(win, 0x89, 0xCA, 0xB2);
    HuWinMesSet(win, 0x253A, -1, -1);
    HuWinMesSpeedSet(win, 0);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinActivePlayerSet(win, 1 << player);
    choice = HuWinChoiceGet(win, 0, 0);
    HuWinKill(win);
    HuAudSeqVolSet(0x7F);
    MBDSprGrpKill(dimmer);
    MBDSprGrpKill(icon);
    return choice == 1;
}

void MBD10_PauseProc(void) {
    Vec2f pos;
    s32 player;
    s32 i;

    while (TRUE) {
        HuPrcVSleep();
        if (WipeStatGet() != 0 || wipeMode == 3) {
            continue;
        }
        player = MBDPlayerTurnGet();
        for (i = 0; i < 4; i++) {
            if (!(ContBtnDown[i] & START_BUTTON) || mbd10_pauseOnF == 0) {
                continue;
            }
            MBDSaiSeStop(player);
            MBDCameraPos2DGet(&pos);
            MBDCameraPos2DSet(&pos);
            winPauseF = 1;
            omAllPause();
            Hu3DPauseF = 1;
            if (MBD10_PauseQuitCheck(i)) {
                GwSystem.message_speed = mbd10_mesSpeedSave;
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
                HuPrcSleep(0x11);
                MBDExit();
                MBDBoardReturnOff();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            Hu3DPauseF = 0;
            omAllUPause();
            winPauseF = 0;
            MBDSaiSeResume(player);
            break;
        }
    }
}

void MBD10Ev_ComSetAll(void) {
}

void MBD10Ev_PlayerColorReset(void) {
}

void MBD10Ev_TurnNext(void) {
    GW_PLAYER *player;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    if (++system->current_player_index >= 2) {
        system->current_player_index = 0;
    }
    for (i = 0; i < 2; i++) {
        player = MBDPlayerGet(i);
        MBDPlayerForwardSet(i);
        MBDMotionSet(player->player_obj, -1, 2);
        MBDPlayerPosFixSet(i, 1);
    }
    HuPrcVSleep();
    MBDCameraZoomSet(1.4f);
}

void MBD10Ev_CameraRefresh(s32 arg0) {
    MBDCameraRefresh();
}

void MBD10Ev_TelopExec(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBDTelopCreate(GwSystem.current_player_index));
    HuPrcChildWatch();
}

void MBD10Ev_SaiExec(s16 arg0) {
    Process *process;
    Process *child;
    GW_SYSTEM *system = &GwSystem;

    MBDSaiValueForceSet(system->current_player_index, arg0);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBDCameraZoomMotStart(1.7f));
    child = MBDSaiPlayerCreate(system->current_player_index);
    HuPrcChildWatch();
    HuPrcChildLink(process, child);
    HuPrcChildWatch();
}

void MBD10Ev_SaiStart(s16 arg0) {
    Process *process;
    Process *child;
    GW_SYSTEM *system = &GwSystem;

    MBDSaiValueForceSet(system->current_player_index, arg0);
    mbdSaiHitLockF = 1;
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBDCameraZoomMotStart(1.7f));
    child = MBDSaiPlayerCreate(system->current_player_index);
    HuPrcChildWatch();
    HuPrcChildLink(process, child);
}

void MBD10Ev_SaiWait(void) {
    mbdSaiHitLockF = 0;
    HuPrcChildWatch();
}

void MBD10Ev_PlayerWalkExecEx(s32 maxSteps, s32 steps) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    Process *process;
    SpaceData *space;
    Vec rot;
    s32 walkSpeed;
    s32 attackType;
    s16 walkNum;
    s16 masuId;

    player = MBDPlayerGet(CUR_PLAYER);
    walkSpeed = 1;
    process = HuPrcCurrentGet();
    if (steps != 0) {
        walkNum = steps;
    } else {
        walkNum = MBDSaiValueGet(system->current_player_index);
    }
    MBDPlayerDirNextSet(system->current_player_index);
    if (!(player->rev & 2)) {
        MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
    } else {
        MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
    }

    while (walkNum != 0 && maxSteps != 0) {
        if (MBD10_WalkAttackHook() != 0) {
            attackType = MBD10_WalkAttackHook();
            if (attackType != -1) {
                MBDPlayerPartyMotionSet(-1, -1, 2);
                MBDSaiNumKill(player->turn);
                MBDPartnerAttackExec(attackType);
                MBDSaiNumShow(player->turn);
                HuPrcChildLink(process, MBDCameraZoomMotStart(1.7f));
                HuPrcChildWatch();
                if (!(player->rev & 2)) {
                    MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
                } else {
                    MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
                }
            }
        }

        {
            s16 curLink = player->clink;
            s16 curIdx = player->cidx;

            player->clink = player->nlink;
            player->cidx = player->nidx;
            MBDPlayerPosFixSet((s8)(system->current_player_index ^ 1), (walkSpeed * 7) + 8);
            player->clink = curLink;
            player->cidx = curIdx;
        }

        space = MBDMasuGet(MBDMasuLinkMasuIdGet(player->nlink, player->nidx));

        if (player->player_obj->unk48 != 0) {
            if (!(player->rev & 2)) {
                MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 2);
            } else {
                MBDPlayerPartyMotionShiftSet(-1, 0, 0, 5, 6);
            }
        }

        switch (walkSpeed) {
            case 0:
                MBDPlayerSpeedSet(-1, 1.5f);
                MBDPlayerPartnerMoveExec(system->current_player_index, 5.0f);
                break;
            case 1:
                MBDPlayerSpeedSet(-1, 1.0f);
                MBDPlayerPartnerMoveExec(system->current_player_index, 4.0f);
                break;
            case 2:
                MBDPlayerSpeedSet(-1, 0.75f);
                MBDPlayerPartnerMoveExec(system->current_player_index, 3.0f);
                break;
        }
        MBDPlayerSpeedSet(-1, 1.0f);

        player->blink = player->clink;
        player->bidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;

        if (!(player->rev & 1)) {
            player->nidx++;
        } else {
            player->nidx--;
        }

        masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBDMasuGet(masuId);
        MBDMasuCurSet(masuId);

        switch (space->space_type) {
            case MBD_MASU_TYPE_HAPPENING:
            case MBD_MASU_TYPE_GAMEGUY:
            case MBD_MASU_TYPE_REVERSE:
            case MBD_MASU_TYPE_BASIC:
            case MBD_MASU_TYPE_MINIGAME:
            case MBD_MASU_TYPE_POWERUP:
            case MBD_MASU_TYPE_CHR(CHAR_MARIO):
            case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
            case MBD_MASU_TYPE_CHR(CHAR_PEACH):
            case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
            case MBD_MASU_TYPE_CHR(CHAR_WARIO):
            case MBD_MASU_TYPE_CHR(CHAR_DK):
            case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
            case MBD_MASU_TYPE_CHR(CHAR_DAISY):
                MBDSaiNumCountDown(system->current_player_index);
                walkNum--;
                maxSteps--;
                MBDMasuBounceCreate(masuId);
                break;
        }

        if (steps == 0) {
            if (walkNum != 0) {
                MBDMasuPassSePlay(space->space_type);
            } else {
                MBDMasuLandSePlay(space->space_type);
            }
        }
    }

    MBDPlayerPartyMotionSet(-1, -1, 2);
    MBDVecForwardSet(&rot);
    MBDVecRotLerpCreate(&player->player_obj->rot, &rot, &player->player_obj->rot, 8);
}

void MBD10Ev_PlayerWalkExec(void) {
    MBD10Ev_PlayerWalkExecEx(-1, 0);
}

void MBD10Ev_MasuCoinExec(void) {
    Vec rot;
    Vec pos;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    Process *process;
    s16 masuId;
    SpaceData *space;
    s32 coins;
    Object *partner;

    player = MBDPlayerGet(CUR_PLAYER);
    process = HuPrcCurrentGet();
    masuId = MBDMasuLinkMasuIdGet(player->clink, player->cidx);
    space = MBDMasuGet(masuId);
    switch (space->space_type) {
        case MBD_MASU_TYPE_CHR(CHAR_MARIO):
        case MBD_MASU_TYPE_CHR(CHAR_LUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_PEACH):
        case MBD_MASU_TYPE_CHR(CHAR_YOSHI):
        case MBD_MASU_TYPE_CHR(CHAR_WARIO):
        case MBD_MASU_TYPE_CHR(CHAR_DK):
        case MBD_MASU_TYPE_CHR(CHAR_WALUIGI):
        case MBD_MASU_TYPE_CHR(CHAR_DAISY):
            // The do-while (0) blocks keep GwSystem reads from being CSE'd with system.
            do {
                coins = MBDTurnCoinGet();
            } while (0);
            if (space->space_type - MBD_MASU_TYPE_CHR_BASE == GwPlayer[GwSystem.current_player_index].chr) {
                do {
                    MBDCoinChangeCreate(GwSystem.current_player_index, coins);
                } while (0);
                MBDCoinTakeCreate(GwSystem.current_player_index, coins);
                HuPrcSleep(30);
            } else if (player->stats.partners.frontID == 2 || player->stats.partners.backID == 2) {
                if (player->stats.partners.backID == 2) {
                    partner = MBDPartnerObjGet(system->current_player_index, 1);
                } else {
                    partner = MBDPartnerObjGet(system->current_player_index, 0);
                }
                HuPrcChildLink(process, MBDCameraZoomMotStart(2.0f));
                HuPrcChildWatch();
                HuVecCopy3F(&pos, &player->player_obj->coords);
                MBDCameraFocusModeSet(4);
                MBDCameraFocusVecSet(&pos);
                HuPrcChildLink(process, MBDVecSpeedMoveCreate(&pos, &partner->coords, &pos, 2.0f));
                HuPrcChildWatch();
                MBDVecForwardSet(&rot);
                MBDVecRotLerpCreate(&partner->rot, &rot, &partner->rot, 8);
                HuPrcSleep(8);
                MBDPartnerAttackMotLoad(2);
                MBDPartnerAttackMotSet(partner, 1, 0);
                MBDModelMotionWait(partner);
                MBDMotionSet(partner, -1, 2);
                MBDPartnerAttackMotKill();
                MBDDlgResultWinExec(0x1F1C);
            } else {
                if (GwPlayer[system->current_player_index].coin == 0) {
                    coins = 0;
                    MBDDlgResultWinExec(0x1F1B);
                } else if (GwPlayer[system->current_player_index].coin < coins) {
                    coins = GwPlayer[system->current_player_index].coin;
                }
                if (coins != 0) {
                    MBDCoinChangeCreate(system->current_player_index, -coins);
                    MBDCoinTakeCreate(system->current_player_index, -coins);
                    HuPrcSleep(30);
                    MBDCoinChangeStatusCreate(system->current_player_index ^ 1, coins);
                    MBDCoinTakeCreate(system->current_player_index ^ 1, coins);
                    HuPrcSleep(30);
                }
            }
            break;
        case MBD_MASU_TYPE_BASIC:
            HuPrcSleep(8);
            MBDMasuOwnerAdd(masuId, system->current_player_index);
            MBDMasuOwnerTypeUpdate();
            MBDMasuTypeListCreate();
            HuAudFXPlay(0x201);
            break;
    }
}

void MBD10Ev_PlayerRevOn(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 7;
}

void MBD10Ev_PlayerRevOff(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s8 nlink = player->nlink;
    s8 nidx = player->nidx;

    player->nlink = player->blink;
    player->nidx = player->bidx;
    player->blink = nlink;
    player->bidx = nidx;
    player->rev = 0;
}

void MBD10Ev_GuideWinExec(UnkOvl81_2 *guide, u32 mess) {
    HuWinMesSet(guide->win_id, mess, -1, -1);
    HuWinExOpen(guide->win_id, 1);
    MBDWinComKeyAnyWait(guide->win_id);
    mbd10ev_guideWinDoneF = 1;
    HuWinExClose(guide->win_id, 1);
    HuWinHomeClear(guide->win_id);
    HuPrcVSleep();
}

void MBD10Ev_GuideWinOpen(UnkOvl81_2 *guide, u32 mess) {
    HuWinMesSet(guide->win_id, mess, -1, -1);
    HuWinExOpen(guide->win_id, 1);
}

void MBD10Ev_GuideWinClose(UnkOvl81_2 *guide) {
    MBDWinComKeyAnyWait(guide->win_id);
    HuWinExClose(guide->win_id, 1);
    HuWinHomeClear(guide->win_id);
    HuPrcVSleep();
}

void MBD10Ev_GuideJump(UnkOvl81_2 *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    MBDModelJumpWait(guide->obj);
    MBDMotionSet(guide->obj, -1, 2);
}

void MBD10Ev_GuideMove(UnkOvl81_2 *guide, s16 pos) {
    s32 i;
    s16 step;
    s16 curPos = guide->unk_0A;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (pos - curPos) / 14;
    for (i = 0; i < 14; i++) {
        curPos = guide->unk_0A;
        MBDGuidePosSet(guide, curPos + step, 0);
        HuPrcVSleep();
    }
    MBDGuidePosSet(guide, pos, 0);
    MBDMotionSet(guide->obj, -1, 2);
}

void MBD10Ev_GuideMotProc(void) {
    UnkOvl81_2 *guide = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        do {
            HuPrcVSleep();
        } while (mbd10ev_guideMotNo == -1);
        MBDMotionShiftSet(guide->obj, mbd10ev_guideMotNo, 0, 10, 0);
        mbd10ev_guideMotNo = -1;
        while (MBDMotionCheck(guide->obj) == 0 && mbd10ev_guideMotNo == -1) {
            HuPrcVSleep();
        }
        MBDMotionSet(guide->obj, -1, 2);
    }
}

void MBD10_GateGuyScrewProc(void) {
    HmfMotionNode *node;
    f32 angle;

    angle = 0.0f;
    while (TRUE) {
        Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], Hu3DData[mbd10_gateGuyMdl->omObj1->model[0]].motId, "neji", 0x4C, 0x46);
        node = Hu3DModelObjPtrGet(mbd10_gateGuyMdl->omObj1->model[0], "neji");
        angle += mbd10_gateGuyScrewSpeed;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        node->baseRot.y = angle;
        HuPrcVSleep();
    }
}

void MBD10_GateGuyBellSet(void) {
    HmfMotionNode *node;

    Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], Hu3DData[mbd10_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd10_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

void MBD10_GateGuyCreate(void) {
    Object *obj = MBDModelCreate(0x34, mbd10_gateGuyMot);

    MBDModelTempAllocFree(obj);
    mbd10_gateGuyMdl = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBDMasuGet(0x14)->coords);
    MBD10_GateGuyBellSet();
    mbd10_gateGuyScrewProc = omAddPrcObj(MBD10_GateGuyScrewProc, 0xA, 0, 0);
    omPrcSetStatBit(mbd10_gateGuyScrewProc, 0xA0);
}

void MBD10_PartnerBox1Create(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = MBDModelCreate(0x32, NULL);
    MBDModelTempAllocFree(obj);
    mbd10_partnerBox1Mdl = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(mbd10_partnerBox1Masu);
    space2 = MBDMasuGet(mbd10_partnerBox1DirMasu);
    HuVecCopy3F(&obj->coords, &space1->coords);
    MBDVecDirGet(&space1->coords, &space2->coords, &obj->rot);
}

void MBD10Ev_PartnerBox1SwayProc(void) {
    Duel10SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[mbd10_partnerBox1Mdl->omObj1->model[0]].mtx, sindf(angle) * mbd10ev_partnerBox1SwayAmp);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void MBD10Ev_PartnerBox1SwayCreate(Vec *pos) {
    Process *process;
    Duel10SwayWork *work;

    mbd10ev_partnerBox1SwayAmp = 10.0f;
    process = omAddPrcObj(MBD10Ev_PartnerBox1SwayProc, 0xA, 0, 0x40);
    mbd10ev_partnerBox1SwayProc = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10SwayWork));
    process->user_data = work;
    if (pos->x <= mbd10_partnerBox1Mdl->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void MBD10Ev_PartnerBox1SwayStop(void) {
    if (mbd10ev_partnerBox1SwayProc != NULL) {
        while (mbd10ev_partnerBox1SwayAmp >= 0.0f) {
            mbd10ev_partnerBox1SwayAmp -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(mbd10ev_partnerBox1SwayProc);
        MTX_ROTZ(Hu3DData[mbd10_partnerBox1Mdl->omObj1->model[0]].mtx, 0.0f);
    }
}

void MBD10Ev_PartnerBox1SquashProc(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    Hu3DMotionAttrSet(mbd10_partnerBox1Mdl->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(mbd10_partnerBox1Mdl->omObj1->model[0], 1.5f);
    MBDModelMotionWait(mbd10_partnerBox1Mdl);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&mbd10_partnerBox1Mdl->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mbd10_partnerBox1Mdl->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MBD10Ev_PartnerBox1SquashCreate(void) {
    omAddPrcObj(MBD10Ev_PartnerBox1SquashProc, 0xA, 0, 0);
}

void MBD10Ev_PartnerBox1MotionReset(void) {
    Hu3DMotionAttrSet(mbd10_partnerBox1Mdl->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(mbd10_partnerBox1Mdl->omObj1->model[0], 1.0f);
}

void MBD10_PartnerBox2Create(void) {
    Object *obj;
    SpaceData *space1;
    SpaceData *space2;

    obj = MBDModelCreate(0x33, NULL);
    MBDModelTempAllocFree(obj);
    mbd10_partnerBox2Mdl = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    space1 = MBDMasuGet(mbd10_partnerBox2Masu);
    space2 = MBDMasuGet(mbd10_partnerBox2DirMasu);
    HuVecCopy3F(&obj->coords, &space1->coords);
    MBDVecDirGet(&space1->coords, &space2->coords, &obj->rot);
}

void MBD10Ev_PartnerBox2SwayProc(void) {
    Duel10SwayWork *work = HuPrcCurrentGet()->user_data;
    s32 angle = work->angle;

    while (TRUE) {
        MTX_ROTZ(Hu3DData[mbd10_partnerBox2Mdl->omObj1->model[0]].mtx, sindf(angle) * mbd10ev_partnerBox2SwayAmp);
        angle += 45;
        if (angle >= 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
}

void MBD10Ev_PartnerBox2SwayCreate(Vec *pos) {
    Process *process;
    Duel10SwayWork *work;

    mbd10ev_partnerBox2SwayAmp = 10.0f;
    process = omAddPrcObj(MBD10Ev_PartnerBox2SwayProc, 0xA, 0, 0x40);
    mbd10ev_partnerBox2SwayProc = process;
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10SwayWork));
    process->user_data = work;
    if (pos->x <= mbd10_partnerBox2Mdl->coords.x) {
        work->angle = 180;
    } else {
        work->angle = 0;
    }
}

void MBD10Ev_PartnerBox2SwayStop(void) {
    if (mbd10ev_partnerBox2SwayProc != NULL) {
        while (mbd10ev_partnerBox2SwayAmp >= 0.0f) {
            mbd10ev_partnerBox2SwayAmp -= 1.0f;
            HuPrcVSleep();
        }
        omDelPrcObj(mbd10ev_partnerBox2SwayProc);
        MTX_ROTZ(Hu3DData[mbd10_partnerBox2Mdl->omObj1->model[0]].mtx, 0.0f);
    }
}

void MBD10Ev_PartnerBox2SquashProc(void) {
    f32 amplitude;
    s32 angle;
    f32 offset;

    Hu3DMotionAttrSet(mbd10_partnerBox2Mdl->omObj1->model[0], 5, 0);
    Hu3DMotionSpeedSet(mbd10_partnerBox2Mdl->omObj1->model[0], 1.5f);
    MBDModelMotionWait(mbd10_partnerBox2Mdl);
    for (angle = 0, amplitude = 0.5f; angle < 2160; angle += 60) {
        offset = 1.0f - cosdf(angle) * amplitude;
        amplitude -= 1.0 / 72;
        HuVecCopyXYZ(&mbd10_partnerBox2Mdl->scale, 1.0f, offset, 1.0f);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mbd10_partnerBox2Mdl->scale, 1.0f, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MBD10Ev_PartnerBox2SquashCreate(void) {
    omAddPrcObj(MBD10Ev_PartnerBox2SquashProc, 0xA, 0, 0);
}

void MBD10Ev_PartnerBox2MotionReset(void) {
    Hu3DMotionAttrSet(mbd10_partnerBox2Mdl->omObj1->model[0], 1, 4);
    Hu3DMotionSpeedSet(mbd10_partnerBox2Mdl->omObj1->model[0], 1.0f);
}

void MBD10Ev_CoinScatterHook(void) {
    if (mbd10ev_coinScatterCnt == 1) {
        MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2524);
    }
    mbd10ev_coinScatterCnt++;
}

void MBD10Ev_TutorialProc(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBDPlayerGet(0);
    Process *process = HuPrcCurrentGet();
    Process *child;
    Duel10SprGroup *sprGroup;
    SpaceData *space;
    HmfMotionNode *node;
    f32 offset;
    s32 i;

    mbd10_mesSpeedSave = GwSystem.message_speed;
    GwSystem.message_speed = 1;
    MBDMesSpeedSet(1);
    MBDCameraFocusModeSet(1);
    MBDPlayerPosFixSet(0, 1);
    MBDPlayerPosFixSet(1, 1);
    MBDCameraZoomSet(1.4f);
    MBDCameraPos3DSet(&MBDPlayerGet(-1)->player_obj->coords);
    HuPrcSleep(1);
    WipeCreateIn(WIPE_STARS, 0x10);
    MBDBackThreadPriLowSet();
    mbd10ev_guide = MBDGuideCreate((s32)mbd10ev_guideMot, 0);
    HuVecCopyXYZ(&mbd10ev_guide->obj->scale, 1.1f, 1.1f, 1.1f);
    mbd10ev_guide->obj->coords.x -= 1.0f;
    mbd10ev_guide->obj->coords.y -= 2.0f;
    MBDGuideFaceCreate(mbd10ev_guide->obj, 2, 0xF, mbd10ev_guideFaceTbl[0]);
    MBDGuidePosSet(mbd10ev_guide, 0x5A, 0);
    omAddPrcObj(MBD10Ev_GuideMotProc, 0x4800, 0, 0)->user_data = mbd10ev_guide;
    HuWinAttrSet(mbd10ev_guide->win_id, 0x40, 0x40);
    MBD10Ev_ComSetAll();
    MBD10Ev_PlayerColorReset();
    MBDMasuTypeSet(5, MBD_MASU_TYPE_CHR(CHAR_LUIGI));
    MBDMasuTypeSet(6, MBD_MASU_TYPE_CHR(CHAR_MARIO));
    MBDMasuTypeListCreate();
    MBDPlayerPartyMotionSet(-1, -1, 2);
    Hu3DMotionReset(MBDPlayerGet(1)->player_obj->omObj1->model[0]);
    MBDPartnerMotionReset(1);
    HuPrcSleep(3);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(3);
    MBD10Ev_GuideJump(mbd10ev_guide);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x250D);
    system->current_player_index = 0;
    MBD10Ev_TelopExec();
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    sprGroup = MBD10Ev_CaptionCreate(0, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x250E);
    MBD10Ev_CaptionKill(sprGroup);
    MBD10Ev_MasuCoinExec();
    HuPrcSleep(10);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x250F);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    sprGroup = MBD10Ev_CaptionCreate(2, 100, 100);
    MBD10Ev_GuideWinOpen(mbd10ev_guide, 0x2510);
    MBDGuideFaceSet(mbd10ev_guide->obj, mbd10ev_guideFaceTbl[2]);
    MBD10Ev_GuideWinClose(mbd10ev_guide);
    MBD10Ev_CaptionKill(sprGroup);
    MBD10Ev_MasuCoinExec();
    MBDGuideFaceSet(mbd10ev_guide->obj, mbd10ev_guideFaceTbl[0]);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    sprGroup = MBD10Ev_CaptionCreate(1, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2511);
    MBD10Ev_CaptionKill(sprGroup);
    MBD10Ev_MasuCoinExec();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2512);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    sprGroup = MBD10Ev_CaptionCreate(5, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2513);
    MBD10Ev_CaptionKill(sprGroup);
    MBDStatusShrink(-1);
    MBD10Ev_GuideMove(mbd10ev_guide, -30);
    mbd10_pauseOnF = 0;
    HuPrcSleep(1);
    GwSystem.minigame_index = -1;
    MBDMgCallListStart(0);
    HuPrcSleep(15);
    MBDMgCallListClose();
    while (GwSystem.minigame_index == -1) {
        HuPrcVSleep();
    }
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2514);
    MBDMgCallClose();
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideMove(mbd10ev_guide, 0x5A);
    MBDStatusGrow(-1);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    {
        Object *obj;
        Process *child;

        obj = MBDModelCreate(0x3D, NULL);
        MBDModelTempAllocFree(obj);
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 100.0f;
        do {
            obj->velocity.x -= 3.0f;
            HuPrcVSleep();
        } while (obj->velocity.x >= 30.0f);
        child = MBDModelHoverCreate(obj, 5.0f, 2.0f);
        sprGroup = MBD10Ev_CaptionCreate(7, 100, 100);
        MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2515);
        MBD10Ev_CaptionKill(sprGroup);
        omDelPrcObj(child);
        while (obj->velocity.x <= 100.0f) {
            obj->velocity.x += 5.0f;
            HuPrcVSleep();
        }
        MBDModelKill(obj);
    }
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLandNoSe(1);
    MBDAuraHoverStart();
    HuAudFXPlay(0x1F6);
    MBDAuraSpinExec(0);
    MBDAuraHoverStop();
    MBDAuraRiseExec(2);
    MBDAuraKill();
    {
        Object *obj;

        obj = MBDModelCreate(0x38, NULL);
        MBDModelTempAllocFree(obj);
        HuVecCopy3F(&obj->coords, &MBDPartnerObjGet(system->current_player_index, 0)->coords);
        Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 0);
        HuAudFXPlay(0x1FA);
        MBDModelMotionWait(obj);
        MBDModelKill(obj);
    }
    MBDPartnerPowerUp(system->current_player_index);
    HuPrcChildLink(process, MBDTelopBannerCreate(0));
    HuPrcChildWatch();
    sprGroup = MBD10Ev_CaptionCreate(6, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2516);
    MBD10Ev_CaptionKill(sprGroup);
    MBDPartnerPowerDown(system->current_player_index);
    MBD10Ev_SaiExec(2);
    MBD10Ev_PlayerWalkExec();
    MBDSaiTypeSet(system->current_player_index, 1);
    MBD10Ev_PlayerRevOn();
    MBD10Ev_SaiStart(1);
    sprGroup = MBD10Ev_CaptionCreate(4, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2517);
    MBD10Ev_CaptionKill(sprGroup);
    MBD10Ev_SaiWait();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2518);
    MBD10Ev_PlayerWalkExec();
    player->rev = 0;
    MBD10Ev_Hatena();
    sprGroup = MBD10Ev_CaptionCreate(3, 100, 100);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2519);
    MBD10Ev_CaptionKill(sprGroup);
    MBD10Ev_HatenaEnd();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251A);
    HuPrcSleep(10);
    MBD10Ev_GuideJump(mbd10ev_guide);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251B);
    MBDStatusShrink(-1);
    Hu3DMotionReset(MBDPlayerGet(0)->player_obj->omObj1->model[0]);
    Hu3DMotionReset(MBDPlayerGet(1)->player_obj->omObj1->model[0]);
    MBDPartnerMotionReset(0);
    MBDPartnerMotionReset(1);
    mbd10_pauseOnF = 0;
    {
        Vec camPos;

        space = MBDMasuGet(0x14);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuVecCopy3F(&camPos, &player->player_obj->coords);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&camPos, &space->coords, &camPos, 4.0f));
        HuPrcChildWatch();
    }
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251C);
    MBD10Ev_GateGuyMasu();
    HuPrcSleep(10);
    for (i = 0; i < 3; i++) {
        Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], Hu3DData[mbd10_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
        node = Hu3DModelObjPtrGet(mbd10_gateGuyMdl->omObj1->model[0], "bell");
        node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
        HuAudFXPlay(0x1C7);
        for (offset = 0.0f; offset >= -60.0f; offset -= 4.0f) {
            node->baseRot.y = (GwSystem.bank_coins - 5) * 60 + offset;
            HuPrcVSleep();
        }
        if (GwSystem.bank_coins != 0) {
            GwSystem.bank_coins--;
        }
        MBD10_GateGuyBellSet();
        HuPrcSleep(10);
    }
    MBD10Ev_GateGuyMasu();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251D);
    MBD10Ev_ScissorWipeOut();
    MBDCameraFocusModeSet(1);
    MBDMotionSet(mbd10_gateGuyMdl, -1, 2);
    Hu3DMotionReset(mbd10_gateGuyMdl->omObj1->model[0]);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(0xD, &link, &idx);
        MBDMoveMasuSet(0, link, idx);
    }
    MBDPlayerPosFixSet(0, 1);
    MBDPartnerClear(0, 0);
    MBDPartnerModelUpdate(0);
    MBDStatusFrontDispOff(0);
    system->current_player_index = 0;
    MBD10Ev_CameraRefresh(0);
    MBD10Ev_ScissorWipeIn();
    MBDAuraCreate(&player->player_obj->coords);
    MBDAuraLand(0);
    MBDAuraHoverStart();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251E);
    MBDPlayerMotionSet(-1, 6, 0);
    MBDCoinChangeCreate(0, 10);
    MBDCoinTakeCreate(0, 10);
    HuPrcSleep(30);
    MBDPlayerMotionSet(-1, -1, 2);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x251F);
    MBD10Ev_PartnerGetExec(0, 0);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2520);
    MBD10Ev_PartnerVanishExec(0);
    GwSystem.playerIndexVisitingBowser = 2;
    MBD10Ev_PartnerGetExec(0, 1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2521);
    MBD10Ev_ScissorWipeOut();
    MBDAuraHoverStop();
    MBDAuraKill();
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(7, &link, &idx);
        MBDMoveMasuSet(0, link, idx);
        MBDMasuLinkIdxGet(8, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(0, 1);
    MBDPlayerPosFixSet(1, 1);
    MBDPartnerClear(0, 0);
    MBDPartnerClear(0, 1);
    MBDPartnerClear(1, 0);
    MBDPartnerClear(1, 1);
    MBDPartnerModelUpdate(0);
    MBDPartnerModelUpdate(1);
    MBDStatusFrontDispOff(0);
    MBDStatusBackDispOff(0);
    MBDStatusFrontDispOff(1);
    MBDStatusBackDispOff(1);
    MBDPartnerSet(0, 1, 0);
    MBDPartnerSet(1, 2, 1);
    MBDPartnerModelReset(0, 0);
    MBDPartnerModelReset(1, 1);
    MBDPartnerMotionSet(0, 0, -1, 2);
    MBDPartnerMotionSet(1, 1, -1, 2);
    MBDPartnerPosFix(0);
    MBDPartnerPosFix(1);
    MBDStatusFrontUpdate(0);
    MBDStatusBackUpdate(1);
    MBDMasuTypeSet(9, MBD_MASU_TYPE_REVERSE);
    MBDMasuTypeListCreate();
    system->current_player_index = 0;
    MBD10Ev_CameraRefresh(0);
    MBD10Ev_ScissorWipeIn();
    MBDStatusGrow(-1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2522);
    mbd10_pauseOnF = 0;
    HuPrcChildLink(process, MBDTelopTitleCreate());
    HuPrcChildWatch();
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2523);
    mbd10ev_coinScatterCnt = 0;
    mbdCoinScatterHook = MBD10Ev_CoinScatterHook;
    mbdAttackResult = 10;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 1, 1, 0, 0);
    mbd10_pauseOnF = 1;
    mbdCoinScatterHook = NULL;
    MBDPartnerSet(1, 2, 1);
    MBDPartnerModelReset(1, 1);
    MBDPartnerMotionSet(1, 1, -1, 2);
    MBDPartnerPosFix(1);
    MBDStatusBackUpdate(1);
    mbd10_pauseOnF = 0;
    HuPrcChildLink(process, MBDTelopTitleCreate());
    HuPrcChildWatch();
    mbd10_pauseOnF = 1;
    mbdAttackResult = 12;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 0, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2525);
    MBD10Ev_ScissorWipeOut();
    MBD10Ev_TurnNext();
    MBD10Ev_CameraRefresh(0);
    MBD10Ev_ScissorWipeIn();
    player = MBDPlayerGet(1);
    MBD10Ev_TelopExec();
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    MBDSaiTypeSet(system->current_player_index, 1);
    MBD10Ev_PlayerRevOn();
    MBD10Ev_SaiExec(4);
    MBD10Ev_PlayerWalkExecEx(1, 0);
    MBDSaiNumKill(1);
    mbd10_pauseOnF = 0;
    HuPrcChildLink(process, MBDTelopTitleCreate());
    HuPrcChildWatch();
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2526);
    mbdAttackResult = 10;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(1, 1, 0, 0, 1, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2527);
    mbd10_pauseOnF = 0;
    HuPrcChildLink(process, MBDTelopTitleCreate());
    HuPrcChildWatch();
    mbd10_pauseOnF = 1;
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(1, 1, -1, 1, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBDSaiNumShow(1);
    HuPrcChildLink(process, MBDCameraZoomMotStart(1.7f));
    HuPrcChildWatch();
    MBD10Ev_PlayerWalkExec();
    MBD10Ev_PlayerRevOff();
    HuPrcSleep(10);
    MBD10Ev_TelopExec();
    MBD10Ev_SaiExec(2);
    MBD10Ev_PlayerWalkExecEx(1, 0);
    MBDSaiNumKill(1);
    HuPrcChildLink(process, MBDCameraZoomMotStart(1.0f));
    HuPrcChildWatch();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2528);
    MBDWinOpen(0x1E00);
    MBDWinComKeyAnyWait(mbdWinId);
    MBDWinClose();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2529);
    MBD10Ev_ScissorWipeOut();
    GwPlayer[0].star = 5;
    GwPlayer[1].star = 5;
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(5, &link, &idx);
        MBDMoveMasuSet(0, link, idx);
        MBDMasuLinkIdxGet(6, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(0, 1);
    MBDPlayerPosFixSet(1, 1);
    MBDPartnerClear(0, 0);
    MBDPartnerClear(0, 1);
    MBDPartnerClear(1, 0);
    MBDPartnerClear(1, 1);
    MBDPartnerModelUpdate(0);
    MBDPartnerModelUpdate(1);
    MBDStatusFrontDispOff(0);
    MBDStatusBackDispOff(0);
    MBDStatusFrontDispOff(1);
    MBDStatusBackDispOff(1);
    MBDMasuTypeSet(6, MBD_MASU_TYPE_CHR(CHAR_LUIGI));
    MBDMasuTypeSet(5, MBD_MASU_TYPE_CHR(CHAR_MARIO));
    MBDMasuTypeSet(0, MBD_MASU_TYPE_BASIC);
    MBDMasuTypeListCreate();
    system->current_player_index = 1;
    MBD10Ev_CameraRefresh(0);
    MBD10Ev_ScissorWipeIn();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252A);
    MBD10Ev_PartnerAppearExec(1, 1, 0);
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(1, 1, -1, 1, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252B);
    {
        Vec camPos;
        GW_PLAYER *from = MBDPlayerGet(1);

        HuVecCopy3F(&camPos, &from->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &MBDPlayerGet(0)->player_obj->coords, &camPos, 3.0f));
        HuPrcChildWatch();
    }
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    MBD10Ev_PartnerAppearExec(0, 0, 1);
    mbdAttackResult = 12;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 0, 2, 0, 0);
    mbd10_pauseOnF = 1;
    MBDCameraFocusModeSet(3);
    system->current_player_index = 1;
    MBD10Ev_PlayerWalkExecEx(1, 1);
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252C);
    MBD10Ev_PartnerVanishExec(0);
    MBD10Ev_PartnerAppearExec(0, 0, 2);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    {
        Vec camPos;
        Vec rot;
        Object *partner = MBDPartnerObjGet(system->current_player_index, 0);

        HuPrcChildLink(process, MBDCameraZoomMotStart(2.0f));
        HuPrcChildWatch();
        player = MBDPlayerGet(0);
        HuVecCopy3F(&camPos, &player->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &partner->coords, &camPos, 2.0f));
        HuPrcChildWatch();
        MBDVecForwardSet(&rot);
        MBDVecRotLerpCreate(&partner->rot, &rot, &partner->rot, 8);
        HuPrcSleep(8);
        MBDPartnerAttackMotLoad(2);
        HuAudFXPlay(0x298);
        MBDPartnerAttackMotSet(partner, 1, 0);
        MBDModelMotionWait(partner);
        MBDMotionSet(partner, -1, 2);
        MBDPartnerAttackMotKill();
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &player->player_obj->coords, &camPos, 2.0f));
        HuPrcChildWatch();
    }
    MBDCameraFocusModeSet(1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252D);
    MBD10Ev_PartnerVanishExec(0);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(8, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(1, 1);
    MBD10Ev_PartnerSet(1, 1, 1);
    MBDCameraFocusModeSet(3);
    system->current_player_index = 1;
    MBD10Ev_PlayerRevOn();
    MBD10Ev_PlayerWalkExecEx(1, 1);
    MBD10Ev_PlayerRevOff();
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    MBD10Ev_PartnerAppearExec(0, 0, 3);
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 1, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBDCameraFocusModeSet(3);
    system->current_player_index = 1;
    MBD10Ev_PlayerWalkExecEx(1, 1);
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252E);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(5, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(1, 1);
    MBD10Ev_PartnerClear(1, 1);
    HuPrcVSleep();
    MBD10Ev_PartnerAppearExec(0, 1, 4);
    HuPrcVSleep();
    MBD10Ev_PartnerSet(1, 0, 2);
    {
        Vec camPos;
        GW_PLAYER *from = MBDPlayerGet(0);

        HuVecCopy3F(&camPos, &from->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &MBDPlayerGet(1)->player_obj->coords, &camPos, 3.0f));
        HuPrcChildWatch();
    }
    system->current_player_index = 1;
    MBDCameraFocusModeSet(1);
    mbdCounterResult = 10;
    mbdAttackResult = 16;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(1, 0, 1, 0, 1, 0, 1);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x252F);
    {
        Vec camPos;
        GW_PLAYER *from = MBDPlayerGet(1);

        HuVecCopy3F(&camPos, &from->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &MBDPlayerGet(0)->player_obj->coords, &camPos, 3.0f));
        HuPrcChildWatch();
    }
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(8, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(1, 1);
    MBD10Ev_PartnerSet(1, 0, 2);
    MBD10Ev_PartnerSet(1, 1, 5);
    MBDCameraFocusModeSet(3);
    system->current_player_index = 1;
    MBD10Ev_PlayerRevOn();
    MBD10Ev_PlayerWalkExecEx(1, 1);
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    {
        Vec camPos;
        GW_PLAYER *from = MBDPlayerGet(0);

        HuVecCopy3F(&camPos, &from->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &MBDPlayerGet(1)->player_obj->coords, &camPos, 3.0f));
        HuPrcChildWatch();
    }
    system->current_player_index = 1;
    MBDCameraFocusModeSet(1);
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(1, 1, -1, 0, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2530);
    {
        Vec camPos;
        GW_PLAYER *from = MBDPlayerGet(1);

        HuVecCopy3F(&camPos, &from->player_obj->coords);
        MBDCameraFocusModeSet(4);
        MBDCameraFocusVecSet(&camPos);
        HuPrcChildLink(process, MBDVecSpeedMoveCreate(&camPos, &MBDPlayerGet(0)->player_obj->coords, &camPos, 3.0f));
        HuPrcChildWatch();
    }
    system->current_player_index = 0;
    MBDCameraFocusModeSet(1);
    MBD10Ev_PartnerAppearExec(0, 0, 8);
    mbdAttackResult = 10;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 0, 200, 0, 0);
    mbd10_pauseOnF = 1;
    MBDPartnerMotionReset(1);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2531);
    MBD10Ev_PartnerVanishExec(0);
    MBD10Ev_PartnerAppearExec(0, 0, 9);
    mbdAttackResult = 12;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 1, 0, 3, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2532);
    MBD10Ev_PartnerVanishExec(0);
    MBD10Ev_PartnerAppearExec(0, 0, 10);
    HuPrcVSleep();
    MBD10Ev_PartnerSet(1, 0, 2);
    mbdAttackResult = 10;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, 0, 0, 1, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2533);
    MBD10Ev_PartnerVanishExec(0);
    GwPlayer[0].star = 5;
    GwPlayer[1].star = 5;
    MBD10Ev_PartnerAppearExec(0, 0, 11);
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, -1, 3, 0, 0, 0);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2534);
    mbdAttackResult = 0;
    mbd10_pauseOnF = 0;
    MBDPartnerDamageExec(0, 0, -1, 0, 0, -1, -1);
    mbd10_pauseOnF = 1;
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2535);
    MBD10Ev_PartnerVanishExec(0);
    MBD10Ev_PartnerAppearExec(0, 1, 6);
    MBD10Ev_SnifitCoinGiftExec();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2536);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(9, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(1, 1);
    MBD10Ev_PartnerAppearExec(0, 0, 7);
    MBD10Ev_SaiExec(1);
    MBD10Ev_PlayerWalkExec();
    player = MBDPlayerGet(0);
    {
        Vec dir;
        Vec origRot;
        Object *partner;

        MBDVecForwardSet(&dir);
        MBDVecRotLerpCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
        MBDPlayerPartyMotionSet(-1, -1, 2);
        MBDPartnerAttackMotLoad(7);
        partner = MBDPartnerObjGet(system->current_player_index, 0);
        MBDVecDirGet(&partner->coords, &player->player_obj->coords, &dir);
        HuVecCopy3F(&origRot, &partner->rot);
        MBDVecRotLerpCreate(&partner->rot, &dir, &partner->rot, 2);
        MBDPartnerAttackMotSet(partner, 2, 0);
        HuPrcSleep(5);
        HuPrcChildLink(HuPrcCurrentGet(), MBDCameraZoomMotStart(2.0f));
        MBDSaiValueForceSet(system->current_player_index, 1);
        MBDSaiTypeSet(system->current_player_index, 2);
        child = MBDSaiPlayerCreate(system->current_player_index);
        GWBoardFlagSet(0x11);
        MBDModelMotionWait(partner);
        MBDPartnerAttackMotSet(partner, 3, 2);
        HuPrcSleep(20);
        MBDMotionShiftSet(partner, -1, 0, 5, 2);
        MBDVecRotLerpCreate(&partner->rot, &origRot, &partner->rot, 6);
    }
    HuPrcSleep(6);
    MBDPartnerAttackMotKill();
    MBDCameraFocusModeSet(1);
    GWBoardFlagClear(0x11);
    MBDSaiSePlay(system->current_player_index);
    HuPrcChildLink(process, child);
    HuPrcChildWatch();
    MBD10Ev_PlayerWalkExec();
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2537);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2538);
    MBDCoinChangeCreate(system->current_player_index, -30);
    MBDCoinTakeCreate(system->current_player_index, -30);
    HuPrcSleep(30);
    MBD10Ev_PartnerVanishExec(0);
    MBDCameraFocusModeSet(3);
    {
        s8 link;
        s8 idx;

        MBDMasuLinkIdxGet(9, &link, &idx);
        MBDMoveMasuSet(1, link, idx);
    }
    MBDPlayerPosFixSet(1, 1);
    {
        Vec targetPos[2];

        space = MBDMasuGet(8);
        HuVecCopy3F(&targetPos[0], &space->coords);
        targetPos[0].x += 10.0f;
        HuVecCopy3F(&targetPos[1], &space->coords);
        targetPos[1].x -= 10.0f;
        player = MBDPlayerGet(0);
        MBDVecDirGet(&player->player_obj->coords, &targetPos[0], &player->player_obj->rot);
        MBDMotionSet(player->player_obj, 0, 2);
        HuPrcChildLink(process, MBDPlayerPosMoveCreate(&player->player_obj->coords, &targetPos[0], &player->player_obj->coords, 30));
        player = MBDPlayerGet(1);
        MBDVecDirGet(&player->player_obj->coords, &targetPos[0], &player->player_obj->rot);
        MBDMotionSet(player->player_obj, 0, 2);
        HuPrcChildLink(process, MBDPlayerPosMoveCreate(&player->player_obj->coords, &targetPos[1], &player->player_obj->coords, 30));
        HuPrcChildWatch();
        MBDVecForwardSet(&targetPos[0]);
        MBDVecForwardSet(&targetPos[1]);
        player = MBDPlayerGet(0);
        MBDMotionSet(player->player_obj, -1, 2);
        MBDVecRotLerpCreate(&player->player_obj->rot, &targetPos[0], &player->player_obj->rot, 8);
        player = MBDPlayerGet(1);
        MBDMotionSet(player->player_obj, -1, 2);
        MBDVecRotLerpCreate(&player->player_obj->rot, &targetPos[1], &player->player_obj->rot, 8);
    }
    HuPrcSleep(8);
    MBD10Ev_GuideWinExec(mbd10ev_guide, 0x2539);
    MBDGuideFaceSet(mbd10ev_guide->obj, mbd10ev_guideFaceTbl[6]);
    HuPrcSleep(30);
    GwSystem.message_speed = mbd10_mesSpeedSave;
    HuAudSeqFadeOut(0x3C);
    WipeCreateOut(WIPE_STARS, 0x10);
    HuPrcSleep(16);
    MBDGuideKill(mbd10ev_guide);
    MBDExit();
    MBDBoardReturnOff();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MBD10_Create(void) {
    HuAudSeqPlay(0xB);
    Hu3DCamInit(2);
    MBD10_ObjectSetup();
    omGameSysInit();
    MBDMasuEventTblAdd(mbd10_commonEventTbl);
    MBDMasuEventTblAdd(mbd10_specialEventTbl);
    MBDHatenaFuncSet(MBD10Ev_Hatena);
    MBDWalkAttackHookSet(MBD10_WalkAttackHook);
    omAddPrcObj(MBD10Ev_TutorialProc, 0xEFFF, 0x2000, 0);
    omAddPrcObj(MBDCameraFocusProc, 0x1005, 0, 0);
    omPrcSetStatBit(omAddPrcObj(MBD10_PauseProc, 0x1005, 0, 0), 0x80);
}

s32 MBD10_ComPartnerSlotRateGet(void) {
    GW_PLAYER *player = MBDPlayerGet(CUR_PLAYER);
    s16 partnerValues[12] = { 40, 90, 30, 50, 90, 10, 80, 15, 60, 80, 70, 90 };

    if (player->stats.partners.frontID == PARTNER_NONE) {
        return 0;
    }
    return partnerValues[player->stats.partners.frontID];
}

void MBD10Ev_PartnerRouletteWinColorProc(void) {
    Duel10WinColorWork *work = HuPrcCurrentGet()->user_data;
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
        if (mbd10ev_partnerRouletteColorF != 0) {
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

void MBD10Ev_PartnerRouletteProc(void) {
    s16 pos[3][2] = { { 160, -80 }, { 160, -160 }, { 160, -80 } };
    s32 files[6] = { 0x13011C, 0x13011F, 0x13011E, 0x13011D, 0x130120, 0x13011E };
    u8 order[32]; // Only 12 are used; the size matches the original stack frame.
    s32 player;
    DuelHelpWin *msgWindow;
    s16 window;
    Process *colorProcess;
    s32 state;
    Duel10WinColorWork *colorWork;
    UnkBoard4 *spr;
    void *data;
    s32 i;
    s32 angle;
    s32 count;
    s32 max = 11;
    s32 delay;

    player = ((Duel10PartnerRouletteWork *)HuPrcCurrentGet()->user_data)->player;
    colorProcess = NULL;
    mbd10_pauseOnF = 0;
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
        colorProcess = omAddPrcObj(MBD10Ev_PartnerRouletteWinColorProc, 10, 0, 0x40);
        colorWork = HuMemMemoryAlloc(colorProcess->heap, sizeof(Duel10WinColorWork));
        colorProcess->user_data = colorWork;
        colorWork->window = window;
    }
    spr = MBDSprGrpCreate(3, 0);
    for (i = 0; i < 3; i++) {
        data = DataRead(files[player * 3 + i]);
        spr->unk_0C[i] = HuSprAnimRead(data);
        HuSprGrpMemberSet(spr->unk_0A, i, spr->unk_0C[i], 0);
        HuSprPriSet(spr->unk_0A, i, i + 1);
        HuSprAttrSet(spr->unk_0A, i, HUSPR_ATTR_NONE);
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
    if (MBDPlayerComCheck(-1)) {
        count = MBDRand(10.0f) + 100;
    } else {
        count = -1;
    }
    msgWindow = MBDHelpWinCreate(0x13, 0xB9, 0);
    mbd10ev_partnerRouletteColorF = 1;
    do {
        MBDArrayShuffle(order, max);
        for (i = 0; i <= max; i++) {
            HuAudFXPlay(0x1C8);
            HuSprBankSet(spr->unk_0A, 2, order[i], 0);
            HuSprAnimModeSet(spr->unk_0A, 2, HUSPR_ANIM_MODE_BANK);
            for (delay = (state == 2) ? 15 : 1; delay != 0; delay--) {
                if (count > 0) {
                    if (--count == 0) {
                        break;
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
    mbd10ev_partnerRouletteColorF = 0;
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
    mbd10ev_partnerRouletteResult = order[i];
    MBDHelpWinKill(msgWindow);
    if (colorProcess != NULL) {
        omDelPrcObj(colorProcess);
    }
    MBDSprGrpKill(spr);
    HuWinKill(window);
    mbd10_pauseOnF = 1;
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

const Vec mbd10ev_partnerAppearOfsTbl[] = {
    { 4.0f, 4.0f, -4.0f },
    { -4.0f, -2.0f, -4.0f },
    { 4.0f, 0.0f, 4.0f },
    { -4.0f, 2.0f, 4.0f }
};

s32 MBD10Ev_PartnerRouletteExec(s32 index) {
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
    Duel10PartnerRouletteWork *work;
    Object *model;
    Object *partner;
    SpaceData *returnSpace;
    SpaceData *destSpace;
    s32 i;
    s32 state;

    startSpace = MBDMasuGet(mbd10ev_partnerMasuTbl[index].startSpace);
    partnerSpace = MBDMasuGet(mbd10ev_partnerMasuTbl[index].partnerSpace);
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
        MBD10Ev_PartnerBox1SwayCreate(&player->player_obj->coords);
    } else {
        MBD10Ev_PartnerBox2SwayCreate(&player->player_obj->coords);
    }
    MBDModelMotionWait(player->player_obj);
    MBDPlayerMotionSet(-1, -1, 2);
    mbd10ev_partnerRouletteResult = -1;
    process = omAddPrcObj(MBD10Ev_PartnerRouletteProc, 0xA, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(Duel10PartnerRouletteWork));
    process->user_data = work;
    work->player = index;
    returnSpace = MBDMasuGet(mbd10ev_partnerMasuTbl[index].returnSpace);
    MBDVecDirGet(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->rot);
    MBDPlayerMotionSet(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBDVecSpeedMoveCreate(&player->player_obj->coords, &returnSpace->coords, &player->player_obj->coords, 2.0f));
    HuPrcChildWatch();
    MBDPlayerMotionSet(-1, -1, 2);
    MBDVecForwardSet(&camPos);
    MBDVecRotLerpCreate(&player->player_obj->rot, &camPos, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    while (mbd10ev_partnerRouletteResult == -1) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&target, &partnerSpace->coords);
    target.y += 26.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &target, &pos, 2.0f));
    HuPrcChildWatch();
    if (index == 0) {
        MBD10Ev_PartnerBox1SwayStop();
    } else {
        MBD10Ev_PartnerBox2SwayStop();
    }
    model = MBDModelCreate(0x35, NULL);
    MBDModelDispOff(model);
    partner = MBDPartnerModelCreate(mbd10ev_partnerRouletteResult);
    HuVecCopy3F(&partner->coords, &partnerSpace->coords);
    partner->coords.y += 26.0f;
    MBDModelDispOff(partner);
    HuAudFXPlay(0x1CA);
    if (index == 0) {
        MBD10Ev_PartnerBox1SquashCreate();
    } else {
        MBD10Ev_PartnerBox2SquashCreate();
    }
    HuPrcSleep(20);
    memcpy(offsets, mbd10ev_partnerAppearOfsTbl, sizeof(offsets));
    for (i = 0; i < 4; i++) {
        copies[i] = MBDModelLinkCreate(model);
        Hu3DModelLayerSet(copies[i]->omObj1->model[0], 0x800);
        Hu3DModelAttrSet(copies[i]->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
        Hu3DMotionAttrSet(copies[i]->omObj1->model[0], 2, 0);
        HuVecCopy3F(&copies[i]->coords, &partnerSpace->coords);
        copies[i]->velocity.x = 26.0f;
        copies[i]->coords.x += offsets[i].x;
        copies[i]->coords.y += offsets[i].y;
        copies[i]->coords.z += offsets[i].z;
        if (i == 3) {
            MBDModelDispOn(partner);
        }
        HuPrcSleep(5);
    }
    HuPrcSleep(25);
    for (i = 0; i < 4; i++) {
        MBDModelKill(copies[i]);
    }
    MBDModelKill(model);
    MBDCameraFocusModeSet(5);
    MBDCameraFocusObjSet(partner);
    destSpace = MBDMasuGet(mbd10ev_partnerMasuTbl[index].startSpace);
    MBDVecDirGet(&partner->coords, &destSpace->coords, &partner->rot);
    partner->velocity.x = partner->coords.y;
    partner->coords.y = 0.0f;
    MBDModelJumpSet(partner, 2.0f, -0.255f);
    HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&partner->coords, &destSpace->coords, &partner->coords, 20));
    HuPrcChildWatch();
    MBDModelJumpWait(partner);
    if (index == 0) {
        MBD10Ev_PartnerBox1MotionReset();
    } else {
        MBD10Ev_PartnerBox2MotionReset();
    }
    MBDCameraFocusModeSet(4);
    MBDCameraFocusVecSet(&pos);
    HuVecCopy3F(&pos, &partner->coords);
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&pos, &player->player_obj->coords, &pos, 2.0f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
    mbd10ev_partnerGetMdl = partner;
    return mbd10ev_partnerRouletteResult;
}

void MBD10Ev_PartnerGetExec(s32 index, s32 comSelectSecond) {
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

    if (player->stats.partners.frontID == PARTNER_NONE && player->stats.partners.backID == PARTNER_NONE) {
        HuAudFXPlay(0x159);
        MBDDlgWinExec(0x16, 0x1F04);
        partnerId = MBD10Ev_PartnerRouletteExec(index);
    retryA:
        MBDDlgWinCreate(0x16, 0x1F05);
        if (!MBDPlayerComCheck(index)) {
            HuWinActivePlayerSet(mbdDlgWinId, playerBits[GwPlayer[index].pad]);
            comKeys[GwPlayer[index].pad] = HUWIN_COMKEY_PAD;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (comSelectSecond) {
                comKeys[GwPlayer[index].pad] = D_JPAD;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = A_BUTTON;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(mbdDlgWinId, 2, 2);
        }
        choice = HuWinChoiceGet(mbdDlgWinId, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        MBDDlgWinClose();
        MBDDlgWinKill();
        if (choice == 2) {
            MBD10_MapScroll();
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
            comKeys[GwPlayer[index].pad] = HUWIN_COMKEY_PAD;
            HuWinComKeySet(comKeys[0], comKeys[1], comKeys[2], comKeys[3]);
        } else {
            if (player->stats.partners.backID == PARTNER_NONE ||
                MBD10_ComPartnerSlotRateGet() >= MBDRand(100.0f)) {
                comKeys[GwPlayer[index].pad] = D_JPAD;
                HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            }
            comKeys[GwPlayer[index].pad] = A_BUTTON;
            HuWinComKeyWait(comKeys[0], comKeys[1], comKeys[2], comKeys[3], MBDMesWaitGet());
            HuWinAttrSet(mbdDlgWinId, 2, 2);
        }
        choice = HuWinChoiceGet(mbdDlgWinId, 0, 1);
        comKeys[GwPlayer[index].pad] = 0;
        MBDDlgWinClose();
        MBDDlgWinKill();
        if (choice == 2) {
            MBD10_MapScroll();
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
            memcpy(offsets, mbd10ev_partnerVanishOfsTbl, sizeof(offsets));
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
        partnerId = MBD10Ev_PartnerRouletteExec(index);
    }
    MBDPartnerOfsGet(index, &frontPos, &backPos);
    MBDPartnerDirGet(index, &frontRot, &backRot);
    MBDMotionShiftSet(mbd10ev_partnerGetMdl, 0, 0, 5, 2);
    if (choice == 0) {
        HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
        MBDVecDirGet(&mbd10ev_partnerGetMdl->coords, &frontPos, &mbd10ev_partnerGetMdl->rot);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&mbd10ev_partnerGetMdl->coords, &frontPos,
                                                                &mbd10ev_partnerGetMdl->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecRotLerpCreate(&mbd10ev_partnerGetMdl->rot, &frontRot,
                                                                &mbd10ev_partnerGetMdl->rot, 7));
    } else {
        HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
        MBDVecDirGet(&mbd10ev_partnerGetMdl->coords, &backPos, &mbd10ev_partnerGetMdl->rot);
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&mbd10ev_partnerGetMdl->coords, &backPos,
                                                                &mbd10ev_partnerGetMdl->coords, 3.0f));
        HuPrcChildWatch();
        HuPrcChildLink(HuPrcCurrentGet(), MBDVecRotLerpCreate(&mbd10ev_partnerGetMdl->rot, &backRot,
                                                                &mbd10ev_partnerGetMdl->rot, 7));
    }
    HuPrcChildWatch();
    MBDModelKill(mbd10ev_partnerGetMdl);
    MBDPartnerSet(index, partnerId, choice);
    MBDPartnerModelReset(index, choice);
    MBDPartnerMotionSet(index, PARTNER_FRONT, -1, 2);
    MBDPartnerMotionSet(index, PARTNER_BACK, -1, 2);
    MBDPartnerPosFix(index);
    MBDStatusFrontUpdate(index);
    MBDStatusBackUpdate(index);
}

void MBD10Ev_PartnerSet(s32 playerIndex, s32 frontOrBack, s32 partner) {
    MBDPartnerSet(playerIndex, partner, frontOrBack);
    MBDPartnerModelReset(playerIndex, frontOrBack);
    MBDPartnerMotionSet(playerIndex, frontOrBack, -1, 2);
    MBDPartnerPosFix(playerIndex);
    MBDStatusFrontUpdate(playerIndex);
    MBDStatusBackUpdate(playerIndex);
}

void MBD10Ev_PartnerClear(s32 playerIndex, s32 frontOrBack) {
    MBDPartnerClear(playerIndex, frontOrBack);
    MBDPartnerModelKillAll(playerIndex);
    MBDStatusFrontDispOff(playerIndex);
    MBDStatusBackDispOff(playerIndex);
}

void MBD10Ev_PartnerPuffEffCreate(s32 playerIndex, s32 back) {
    Vec frontPos;
    Vec backPos;
    Vec pos;
    Vec offsets[3];
    GW_PLAYER *player;
    s32 i;

    player = MBDPlayerGet(playerIndex);
    MBDPartnerOfsGet(playerIndex, &frontPos, &backPos);
    HuVecAdd(&frontPos, &player->player_obj->coords, &frontPos);
    HuVecAdd(&backPos, &player->player_obj->coords, &backPos);
    HuVecCopy3F(&pos, back == 0 ? &frontPos : &backPos);
    pos.y += 2.0f;
    memcpy(offsets, mbd10ev_partnerVanishOfsTbl, sizeof(offsets));
    for (i = 0; i < 3; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), MBDEffMdlCreate(0x4E, &pos, &offsets[i], 3.0f));
    }
    HuAudFXPlay(0x1CB);
}

void MBD10Ev_PartnerAppearExec(s32 playerIndex, s32 frontOrBack, s32 partnerId) {
    Vec pos;
    Vec offsets[3];
    Object *partner;
    s32 i;

    MBD10Ev_PartnerSet(playerIndex, frontOrBack, partnerId);
    partner = MBDPartnerObjGet(playerIndex, frontOrBack);
    MBDModelDispOff(partner);
    HuVecCopy3F(&pos, &partner->coords);
    pos.y += 2.0f;
    memcpy(offsets, mbd10ev_partnerVanishOfsTbl, sizeof(offsets));
    for (i = 0; i < 3; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), MBDEffMdlCreate(0x4E, &pos, &offsets[i], 3.0f));
    }
    HuAudFXPlay(0x1CB);
    HuPrcSleep(20);
    MBDModelDispOn(partner);
    HuPrcChildWatch();
}

void MBD10Ev_PartnerVanishExec(s32 playerIndex) {
    Vec pos;
    Vec offsets[3];
    Object *partner;
    s32 side;
    s32 i;

    for (side = 0; side < 2; side++) {
        partner = MBDPartnerObjGet(playerIndex, side);
        if (partner != NULL) {
            HuVecCopy3F(&pos, &partner->coords);
            pos.y += 2.0f;
            memcpy(offsets, mbd10ev_partnerVanishOfsTbl, sizeof(offsets));
            for (i = 0; i < 3; i++) {
                HuPrcChildLink(HuPrcCurrentGet(), MBDEffMdlCreate(0x4E, &pos, &offsets[i], 3.0f));
            }
            MBDModelDispOff(partner);
        }
    }
    HuAudFXPlay(0x1CB);
    HuPrcChildWatch();
    MBDPartnerClear(playerIndex, PARTNER_FRONT);
    MBDPartnerClear(playerIndex, PARTNER_BACK);
    MBDPartnerModelKillAll(playerIndex);
    MBDStatusFrontDispOff(playerIndex);
    MBDStatusBackDispOff(playerIndex);
}

void MBD10Ev_SnifitCoinGiftExec(void) {
    Vec rot;
    Vec origRot;
    Vec camPos;
    Vec effectPos;
    GW_PLAYER *player;
    Object *partner;
    Object *coin;
    s32 index;
    s32 coins;
    s32 i;
    s32 j;

    index = GwSystem.current_player_index;
    player = MBDPlayerGet(index);
    coins = 4;
    if (player->stats.partners.frontID != 6 && player->stats.partners.backID != 6) {
        return;
    }
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
    HuPrcChildLink(HuPrcCurrentGet(), MBDVecSpeedMoveCreate(&camPos, &player->player_obj->coords, &camPos, 2.0f));
    HuPrcChildWatch();
    MBDCameraFocusModeSet(1);
}

void MBD10Ev_GateGuyMasu(void) {
    HmfMotionNode *node;
    f32 offset;

    MBDMotionSet(mbd10_gateGuyMdl, 2, 0);
    Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], Hu3DData[mbd10_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], mbd10_gateGuyMdl->omObj1->motion[2], "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd10_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    HuPrcSleep(10);
    HuAudFXPlay(0x1C5);
    MBDModelMotionWait(mbd10_gateGuyMdl);
    HuAudFXPlay(0x1C7);
    Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], Hu3DData[mbd10_gateGuyMdl->omObj1->model[0]].motId, "bell", 0x4C, 0x46);
    node = Hu3DModelObjPtrGet(mbd10_gateGuyMdl->omObj1->model[0], "bell");
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    HuAudFXPlay(0x1C7);
    for (offset = 0.0f; offset >= -60.0f; offset -= 4.0f) {
        node->baseRot.y = (GwSystem.bank_coins - 5) * 60 + offset;
        HuPrcVSleep();
    }
    if (GwSystem.bank_coins != 0) {
        GwSystem.bank_coins--;
    }
    MBD10_GateGuyBellSet();
    mbd10_gateGuyScrewSpeed = 12.0f;
    if (GwSystem.bank_coins != 0) {
        MBDMotionShiftSet(mbd10_gateGuyMdl, 0, 0, 5, 2);
        Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], mbd10_gateGuyMdl->omObj1->motion[0], "bell", 0x4C, 0x46);
        Hu3DMotionSpeedSet(mbd10_gateGuyMdl->omObj1->model[0], (5.0f - GwSystem.bank_coins) / 4.0f + 1.0f);
        HuPrcSleep(24);
        MBDMotionSet(mbd10_gateGuyMdl, -1, 2);
    } else {
        HuAudFXPlay(0x1C6);
        MBDMotionShiftSet(mbd10_gateGuyMdl, 1, 0, 5, 2);
        Hu3DMotionNoMotSet(mbd10_gateGuyMdl->omObj1->model[0], mbd10_gateGuyMdl->omObj1->motion[1], "bell", 0x4C, 0x46);
        Hu3DMotionSpeedSet(mbd10_gateGuyMdl->omObj1->model[0], 1.0f);
        MBD10_GateGuyBellSet();
    }
    mbd10_gateGuyScrewSpeed = 3.0f;
}

void MBD10Ev_Hatena(void) {
    void *data;
    s32 i;
    s32 offset;

    mbd10_pauseOnF = 0;
    mbItemBtnF = 0;
    MBDStatusShrink(-1);
    HuAudFXPlay(0x204);
    mbd10ev_hatenaSprGrp = MBDSprGrpCreate(2, 2);
    data = DataRead(0x130103);
    mbd10ev_hatenaSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbd10ev_hatenaSprGrp->unk_0A, 0, mbd10ev_hatenaSprGrp->unk_0C[0], 0);
    HuSprPriSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 0xB);
    HuSprAttrSet(mbd10ev_hatenaSprGrp->unk_0A, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, -32);
    HuSprScissorSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 16, 12, 304, 228);
    data = DataRead(0x130104);
    mbd10ev_hatenaSprGrp->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbd10ev_hatenaSprGrp->unk_0A, 1, mbd10ev_hatenaSprGrp->unk_0C[1], 0);
    HuSprPriSet(mbd10ev_hatenaSprGrp->unk_0A, 1, 0xC);
    HuSprAttrSet(mbd10ev_hatenaSprGrp->unk_0A, 1, HUSPR_ATTR_XLU);
    HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 1, 0, 0);
    HuSprScissorSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 16, 12, 304, 228);
    HuSprColorSet(mbd10ev_hatenaSprGrp->unk_0A, 1, 251, 203, 0);
    for (i = 90; i < 180; i += 10) {
        HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, sindf(i) * -152.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 15) {
        HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, sindf(i) * -60.0f + 120.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 180; i += 20) {
        HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, sindf(i) * -30.0f + 120.0f);
        HuPrcVSleep();
    }
    HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, 120);
    offset = 0;
    for (i = 0; i < 9; i++) {
        offset += i * 2;
        HuSprPosSet(mbd10ev_hatenaSprGrp->unk_0A, 0, 160, 120 - offset);
        HuPrcVSleep();
    }
}

void MBD10Ev_HatenaEnd(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBDMgCallListProcCreate());
    HuPrcChildWatch();
    MBDSprGrpKill(mbd10ev_hatenaSprGrp);
    MBDStatusGrow(-1);
    mbd10_pauseOnF = 1;
    mbItemBtnF = 1;
}

s32 MBD10_WalkAttackHook(void) {
    s32 playerIndex = GwSystem.current_player_index;
    s32 otherIndex = (playerIndex + 1) & 1;
    GW_PLAYER *player = MBDPlayerGet(playerIndex);
    GW_PLAYER *otherPlayer = MBDPlayerGet(otherIndex);

    if (player->nlink == otherPlayer->clink && player->nidx == otherPlayer->cidx) {
        return 0;
    }
    return -1;
}

const Vec mbd10ev_partnerVanishOfsTbl[] = {
    { 0.0f, 0.5f, 0.0f },
    { -0.5f, 0.5f, 0.0f },
    { 0.5f, 0.5f, 0.0f }
};

