#include "common_board.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/window.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/hmfmath.h"

typedef struct OpBoardPath {
    s16 count;
    u16 flags;
    s32 unk04;
    Vec *points;
    f32 (*intervals)[2];
} OpBoardPath;

extern s32 mbSaiSeF;

s32 opboard_statusCreateF = 0;

Vec opboard_platformPos = { 0.0f, 250.0f, 0.0f };

/* Unreferenced. */
Vec opboard_unusedPosTbl[2] = {
    { 0.0f, 100.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};

Vec opboard_starPos = { 0.0f, 0.0f, 1750.0f };

Vec opboard_playerStartPosTbl[4] = {
    { -18.0f, 250.0f, 0.0f },
    { -6.0f, 250.0f, 0.0f },
    { 6.0f, 250.0f, 0.0f },
    { 18.0f, 250.0f, 0.0f }
};

Vec opboard_playerPosTbl[4] = {
    { -300.0f, 0.0f, 2000.0f },
    { -100.0f, 0.0f, 2000.0f },
    { 100.0f, 0.0f, 2000.0f },
    { 300.0f, 0.0f, 2000.0f }
};

Vec opboard_playerNearPosTbl[4] = {
    { -300.0f, 0.0f, 2250.0f },
    { -125.0f, 0.0f, 2450.0f },
    { 125.0f, 0.0f, 2450.0f },
    { 300.0f, 0.0f, 2250.0f }
};

u32 opboard_playerMotMario[6] = { 5, 0x20001, 0x20002, 0x2002B, 0x20033, 0x20031 };

u32 opboard_playerMotLuigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotPeach[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotYoshi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotWario[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotDk[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotWaluigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboard_playerMotDaisy[6] = { 5, 0, 0, 0, 0, 0 };

u32 *opboard_playerMotTbl[8] = { opboard_playerMotMario, opboard_playerMotLuigi, opboard_playerMotPeach, opboard_playerMotYoshi, opboard_playerMotWario, opboard_playerMotDk, opboard_playerMotWaluigi, opboard_playerMotDaisy };

u32 opboard_starMot[2] = { 1, 0xA0125 };

Object *opboard_centerMdl = NULL;

Object *opboard_stampMdl = NULL;

Object *opboard_shadowMdl = NULL;

omObjData *opboard_centerBobObj = NULL;

s16 opboard_effNo = -1;

Process *opboard_arriveProc = NULL;

UnkBoard8 *opboard_titleGrp = NULL;

UnkBoard8 *opboard_subtitleGrp = NULL;

omObjData *opboard_skipObj = NULL;

s32 opboard_skipF = 0;

Vec opboard_stampPathPosTbl[4] = {
    { 0.0f, 400.0f, 1750.0f },
    { -200.0f, 300.0f, 1550.0f },
    { -100.0f, 480.0f, 1950.0f },
    { 9999.0f, 9999.0f, 9999.0f }
};

u8 opboard_boardNo BSS;
u8 opboard_boardNoPad[4] BSS; /* Unreferenced. */
GW_PLAYER *opboard_playerTbl[4] BSS;

void MBSaiOrderModeSet(void);
void opboard_SpiralEffHook(s16 model);

void opboard_ArriveProc(void);
void opboard_StarTalkExec(void);
void opboard_MainProc(void);
void opboard_ExitCheckObjMain(omObjData *obj);
void opboard_SysInit(void);
void opboard_BackInit(void);
void opboard_ExitObjMain(omObjData *obj);
void opboard_BackClose(void);
void opboard_SysClose(void);

void opboard_ObjectSetup(void) {
    s32 i;
    u32 j;

    opboard_boardNo = GwSystem.current_board_index;
    omInitObjMan(50, 50);
    opboard_BackInit();
    opboard_SysInit();
    MBShadowHeightMaxSet(1000.0f);
    HuWinInit();
    omAddPrcObj(opboard_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, opboard_ExitCheckObjMain);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < opboard_playerMotMario[0]; j++) {
            opboard_playerMotTbl[i][j + 1] = CharMotionDataNumGet(i, opboard_playerMotMario[j + 1]);
        }
    }
    omGameSysInit();
}

s16 opboard_SpiralEffCreate(s32 file, s32 flags) {
    s16 model;
    HmfData *hmf;
    HmfModelData_UnkBC_Struct *effect;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    f32 initialRadius;
    f32 speed;
    f32 rotationSpeed;
    s16 i;

    model = Hu3DModelRead(file, flags);
    Hu3DModelPosSet(model, 0, 0, 0);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, 0, opboard_SpiralEffHook);
    hmf = Hu3DData[model].hmf;
    effect = Hu3DData[model].unkBC;
    particle = effect->unk58;
    effect->unk08.f = 30.0f;
    effect->unk0C.f = 720.0f;
    effect->unk10.f = 80.0f;
    effect->unk14 = 5.0f;
    initialRadius = effect->unk10.f / 10.0f;
    speed = (effect->unk10.f - initialRadius) / effect->unk08.f;
    rotationSpeed = effect->unk0C.f / effect->unk08.f;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        particle->unk18 = 0.0f;
        particle->unk20 = initialRadius;
        particle->unk1C = speed;
        particle->unk24 = rotationSpeed;
        particle->unk28 = 0.0f;
        particle->unk2C = 0.0f;
        particle->unk08 = 0.0f;
        particle->unk04 = 180.0f;
    }
    return model;
}

s32 opboard_SpiralEffAdd(s16 model, f32 x, f32 y, f32 z) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    f32 angle;

    effect->unk1C.f = x;
    effect->unk20.f = y;
    effect->unk24.f = z;
    for (i = 0; i < hmf->unk1A; i++, particle++) {
        if (particle->unk04 >= 180.0f) {
            particle->unk18 = MBRand(360.0f);
            particle->unk20 = effect->unk10.f / 10.0f;
            angle = MBRand(150.0f);
            angle -= 75.0f;
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            particle->unk28 = sindf(angle);
            particle->unk2C = cosdf(angle);
            particle->unk08 = 0;
            particle->unk04 = 0;
            return 1;
        }
    }
    return 0;
}

void opboard_SpiralEffHook(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 radius;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk04 < 180.0f) {
            particle->unk18 += particle->unk24;
            if (particle->unk18 < 0.0f) {
                particle->unk18 += 360.0f;
            } else if (particle->unk18 >= 360.0f) {
                particle->unk18 -= 360.0f;
            }
            radius = particle->unk20;
            radius += particle->unk1C;
            particle->unk20 = radius;
            radius *= particle->unk2C;
            particle->unk0C = radius * sindf(particle->unk18) + effect->unk1C.f;
            radius *= cosdf(particle->unk18);
            radius += effect->unk24.f;
            particle->unk14 = radius;
            particle->unk10 = particle->unk20 * particle->unk28 + effect->unk20.f;
            particle->unk04 += effect->unk14;
            if (particle->unk04 > 180.0f) {
                particle->unk04 = 180.0f;
            }
            particle->unk08 = sindf(particle->unk04) * effect->unk14;
        }
    }
    effect->unk02++;
}

void opboard_PlayerSwap(s32 player1, s32 player2) {
    GW_PLAYER *first = MBPlayerGet(player1);
    GW_PLAYER *second = MBPlayerGet(player2);
    GW_PLAYER *temp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));

    bcopy(first, temp, sizeof(GW_PLAYER));
    bcopy(second, first, sizeof(GW_PLAYER));
    bcopy(temp, second, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(temp);
}

void opboard_PlayerTurnSort(void) {
    s32 i;
    s32 j;

    for (i = 3; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (GwPlayer[j].turn > GwPlayer[j + 1].turn) {
                opboard_PlayerSwap(j, j + 1);
            }
        }
    }
}

void opboard_SkipObjMain(omObjData *obj) {
    s32 i;

    if (WipeStatGet() != 0) {
        return;
    }
    if (opboard_effNo != -1) {
        EffectStop(opboard_effNo);
        opboard_effNo = -1;
    }
    if (opboard_centerMdl != NULL) {
        MBModelKill(opboard_centerMdl);
        opboard_centerMdl = NULL;
    }
    if (opboard_shadowMdl != NULL) {
        MBModelKill(opboard_shadowMdl);
        opboard_shadowMdl = NULL;
    }
    if (opboard_centerBobObj != NULL) {
        omDelObj(opboard_centerBobObj);
        opboard_centerBobObj = NULL;
    }
    if (opboard_arriveProc != NULL) {
        omDelPrcObj(opboard_arriveProc);
        opboard_arriveProc = NULL;
    }
    if (opboard_titleGrp != NULL) {
        MBSprGrpKill(opboard_titleGrp);
        opboard_titleGrp = NULL;
    }
    if (opboard_subtitleGrp != NULL) {
        MBSprGrpKill(opboard_subtitleGrp);
        opboard_subtitleGrp = NULL;
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(opboard_playerTbl[i]->player_obj);
    }
    omDelObj(obj);
}

void opboard_SkipCheckObjMain(omObjData *obj) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            if (ContBtnDown[GwPlayer[i].pad] & START_BUTTON) {
                break;
            }
        }
    }
    if (i != 4) {
        opboard_skipF = 1;
        WipeColorSet(255, 255, 255);
        WipeCreateOut(11, 16);
        HuAudSeqFadeOut(32);
        msmSeFadeOut(32);
        obj->func = opboard_SkipObjMain;
    }
}

void opboard_CenterBobObjMain(omObjData *obj) {
    s32 i;

    opboard_centerMdl->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 4; i++) {
        opboard_playerTbl[i]->player_obj->coords.y = opboard_centerMdl->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void opboard_BoardTitleExec(void) {
    s32 titleFiles[] = { 0x130016, 0x130017, 0x130018, 0x130019, 0x13001A, 0x13001B };
    s32 subtitleFiles[] = { 0x13001C, 0x13001D, 0x13001E, 0x13001F, 0x130020, 0x130021 };
    void *data;
    f32 amplitude;
    f32 angle;

    HuPrcSleep(10);
    opboard_titleGrp = MBSprGrpCreate(1, 0);
    data = DataRead(titleFiles[GwSystem.current_board_index]);
    opboard_titleGrp->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(opboard_titleGrp->spriteGroup, 0, opboard_titleGrp->model[0], 0);
    HuSprPriSet(opboard_titleGrp->spriteGroup, 0, 10);
    HuSprAttrSet(opboard_titleGrp->spriteGroup, 0, 0);
    HuSprPosSet(opboard_titleGrp->spriteGroup, 0, 160, 100);
    HuSprScaleSet(opboard_titleGrp->spriteGroup, 0, 0.0f, 0.0f);
    for (amplitude = 0.5f, angle = 0.0f; angle <= 720.0f; angle += 45.0f) {
        HuSprScaleSet(opboard_titleGrp->spriteGroup, 0,
                      sindf(angle) * amplitude + 1.0f, sindf(angle) * amplitude + 1.0f);
        amplitude -= 0.03125f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuSprScaleSet(opboard_titleGrp->spriteGroup, 0, 1.0f, 1.0f);
    opboard_subtitleGrp = MBSprGrpCreate(1, 0);
    data = DataRead(subtitleFiles[GwSystem.current_board_index]);
    opboard_subtitleGrp->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(opboard_subtitleGrp->spriteGroup, 0, opboard_subtitleGrp->model[0], 0);
    HuSprPriSet(opboard_subtitleGrp->spriteGroup, 0, 9);
    HuSprAttrSet(opboard_subtitleGrp->spriteGroup, 0, 0);
    HuSprPosSet(opboard_subtitleGrp->spriteGroup, 0, 160, 70);
    HuPrcSleep(75);
    MBSprGrpKill(opboard_subtitleGrp);
    MBSprGrpKill(opboard_titleGrp);
    opboard_subtitleGrp = NULL;
    opboard_titleGrp = NULL;
}

void opboard_ArriveProc(void) {
    s32 i;
    f32 scale;

    for (i = 0; i < 4; i++) {
        opboard_playerTbl[i] = MBPlayerGet(i);
        MBPlayerModelCreate(i, opboard_playerMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&opboard_playerTbl[i]->player_obj->coords, &opboard_playerStartPosTbl[i]);
        MBModelTempAllocFree(opboard_playerTbl[i]->player_obj);
        opboard_playerTbl[i]->stat |= PLAYER_UNK_04;
    }
    opboard_centerMdl = MBModelFileCreate(0x1301FE, -1, 1.0f, 0, NULL);
    opboard_shadowMdl = MBModelFileCreate(0x1301FD, -1, 1.0f, 0, NULL);
    HuVecCopy3F(&opboard_centerMdl->coords, &opboard_platformPos);
    HuVecCopy3F(&opboard_shadowMdl->coords, &opboard_platformPos);
    opboard_shadowMdl->coords.y = 0;
    HuVecCopyXYZ(&opboard_shadowMdl->scale, opboard_shadowMdl->coords.y, opboard_shadowMdl->coords.y, opboard_shadowMdl->coords.y);
    opboard_effNo = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(opboard_effNo, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(opboard_effNo, 40.0f);
    Hu3DParticleAttrSet(opboard_effNo, 1, 0);
    MBBackTPLvlSet(128);
    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    opboard_skipObj = omAddObj(0x1000, 0, 0, -1, opboard_SkipCheckObjMain);
    HuAudSeqPlay(110);
    opboard_BoardTitleExec();
    for (i = 128; i < 256; i += 8) {
        MBBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBBackTPLvlSet(255);
    HuAudFXPlay(0x2ED);
    while (opboard_centerMdl->coords.y >= 10.0f) {
        opboard_centerMdl->coords.y -= 3.0f;
        for (i = 0; i < 4; i++) {
            opboard_playerTbl[i]->player_obj->coords.y -= 3.0f;
        }
        HuVecCopyXYZ(&opboard_shadowMdl->scale,
                     1.0f - opboard_centerMdl->coords.y / 250.0f,
                     1.0f - opboard_centerMdl->coords.y / 250.0f,
                     1.0f - opboard_centerMdl->coords.y / 250.0f);
        HuPrcVSleep();
    }
    opboard_centerBobObj = omAddObj(0x1000, 0, 0, -1, opboard_CenterBobObjMain);
    opboard_centerBobObj->rot.x = 180.0f;
    opboard_centerBobObj->rot.y = 5.0f;
    opboard_centerBobObj->rot.z = opboard_centerMdl->coords.y;
    HuPrcSleep(30);
    EffectPosSet(opboard_effNo, opboard_centerMdl->coords.x,
                       opboard_centerMdl->coords.y + 40.0f, opboard_centerMdl->coords.z);
    Hu3DParticleAttrSet(opboard_effNo, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 4; i++) {
            HuVecCopyXYZ(&opboard_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(opboard_playerTbl[i]->player_obj);
    }
    Hu3DParticleAttrSet(opboard_effNo, 1, 0);
    HuPrcSleep(20);
    if (opboard_skipF != 0) {
        HuPrcSleep(-1);
    } else {
        omDelObj(opboard_skipObj);
        opboard_skipObj = NULL;
    }
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&opboard_centerMdl->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    EffectStop(opboard_effNo);
    opboard_effNo = -1;
    MBModelKill(opboard_centerMdl);
    opboard_centerMdl = NULL;
    MBModelKill(opboard_shadowMdl);
    opboard_shadowMdl = NULL;
    omDelObj(opboard_centerBobObj);
    opboard_centerBobObj = NULL;
    omDelPrcObj(NULL);
}

void opboard_TurnOrderExec(void) {
    s32 state[4];
    s32 frames[4];
    s32 delay[4];
    s32 order[4];
    s32 i;
    s32 j;
    s32 temp;
    Unk3 *help;

    MBSaiInit();
    MBSaiValueClear();
    for (i = 0; i < 4; i++) {
        if (i != 0) {
            mbSaiSeF = 0;
        }
        MBSaiCreate(i);
        MBSaiNumSprCreate(i);
    }
    MBSaiOrderModeSet();
    HuPrcSleep(20);
    help = MBHelpWinCreate(2, 190, 1);
    for (i = 0; i < 4; i++) {
        state[i] = 1;
        frames[i] = 0;
        delay[i] = (u8)(rand8() % 30) + 5;
    }
    while (1) {
        for (i = 0; i < 4; i++) {
            delay[i]--;
            if (state[i] == 1) {
                if ((GwPlayer[i].stat & PLAYER_IS_CPU) ? delay[i] <= 0 : (ContBtnDown[GwPlayer[i].pad] & A_BUTTON)) {
                    state[i] = 2;
                    MBMotionSet(opboard_playerTbl[i]->player_obj, 2, 0);
                    MBMotionEndShiftSet(opboard_playerTbl[i]->player_obj, -1, 2);
                }
            } else if (state[i] == 2) {
                if (++frames[i] == 5) {
                    MBSaiHit(i);
                    state[i] = 0;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (state[i] != 0) {
                break;
            }
        }
        if (i == 4) {
            break;
        }
        HuPrcVSleep();
    }
    MBHelpWinKill(help);
    HuPrcSleep(20);
    for (i = 0; i < 4; i++) {
        state[i] = MBSaiValueGet(i);
        order[i] = i;
    }
    for (i = 0; i < 4; i++) {
        for (j = i; j < 4; j++) {
            if (state[i] < state[j]) {
                temp = state[i];
                state[i] = state[j];
                state[j] = temp;
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[order[i]].turn = i;
        MBSaiNumObjKill(i);
    }
    opboard_PlayerTurnSort();
    MBStatusCreate();
    opboard_statusCreateF = 1;
    for (i = 0; i < 4; i++) {
        MBStatusDispSideSet(i, 1);
    }
    HuPrcSleep(5);
    for (i = 0; i < 4; i++) {
        s32 messages[4] = { 0x1812, 0x1813, 0x1814, 0x1815 };

        MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
        MBDlgWinInsertCreateAllKey(-1, messages[i], mbCharNameMesTbl[GwPlayer[i].chr], 0, 0, 0, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
        PlayerFXPlay(0x274, i);
        MBMotionShiftSetDef(opboard_playerTbl[i]->player_obj, 3, 0);
        MBMotionEndShiftSet(opboard_playerTbl[i]->player_obj, -1, 2);
        MBSaiNumKill(order[i]);
        MBStatusDispMoveSet(i + 10);
        while (MBStatusMoveCheck() != 0) {
            HuPrcVSleep();
        }
        MBPlayerVibrate(i, 3);
        HuPrcSleep(20);
    }
}

void opboard_CenterHoverObjMain(omObjData *obj) {
    opboard_centerMdl->velocity.x = sindf(obj->rot.x) * 20.0f + obj->rot.y;
    obj->rot.x += 5.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

OpBoardPath *opboard_PathCreate(Vec *points, s32 flags) {
    OpBoardPath *path;
    Vec *current;
    Vec *next;
    f32(*interval)[2];
    f32 totalLength;
    f32 length;
    f32 dx;
    f32 dy;
    f32 dz;
    s16 count;
    s16 i;

    path = HuMemAllocTag(sizeof(OpBoardPath), TAG_OVERLAY);
    path->flags = flags;
    path->points = points;
    current = points;
    next = current + 1;
    totalLength = 0.0f;
    for (count = 0; next->x != 9999.0f || next->y != 9999.0f || next->z != 9999.0f; count++, next++, current++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    if (flags & 1) {
        dx = points->x - current->x;
        dy = points->y - current->y;
        dz = points->z - current->z;
        totalLength += HuSqrtf(dx * dx + dy * dy + dz * dz);
    }
    count++;
    path->count = count;
    interval = HuMemAllocTag(count * sizeof(*interval), TAG_OVERLAY);
    path->intervals = interval;
    current = points;
    next = current + 1;
    length = 0.0f;
    for (i = 0; i < count; i++, current++, next++, interval++) {
        dx = next->x - current->x;
        dy = next->y - current->y;
        dz = next->z - current->z;
        if (flags & 1) {
            if (i == count - 1) {
                dx = points->x - current->x;
                dy = points->y - current->y;
                dz = points->z - current->z;
            }
        }
        dz = HuSqrtf(dx * dx + dy * dy + dz * dz);
        (*interval)[0] = length / totalLength;
        (*interval)[1] = (length + dz) / totalLength;
        if ((*interval)[1] > 1.0f) {
            (*interval)[1] = 1.0001f;
        }
        length += dz;
    }
    return path;
}

void opboard_PathPosGet(OpBoardPath *path, f32 time, Vec *result) {
    f32 values[4];
    f32 times[4];
    Vec *points;
    f32(*interval)[2];
    s16 i;

    if (time >= 1.0f) {
        result->x = path->points[path->count - 1].x;
        result->y = path->points[path->count - 1].y;
        result->z = path->points[path->count - 1].z;
        return;
    }
    interval = path->intervals;
    for (i = 0; i < path->count; i++, interval++) {
        if (time <= (*interval)[0]) {
            break;
        }
    }
    i--;
    if (i < 0) {
        i = 0;
    }
    if (i >= path->count - 1) {
        i--;
    }
    interval = path->intervals;
    if (path->flags & 1) {
        times[0] = i == 0 ? -(1.0f - interval[path->count - 1][0]) : interval[i - 1][0];
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[path->count - 1].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[0].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[0].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[path->count - 1].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[0].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[0].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    } else {
        if (i == 0) {
            times[0] = -1.0f;
        } else {
            times[0] = interval[i - 1][0];
        }
        times[1] = interval[i][0];
        times[2] = i >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 1][0];
        times[3] = i + 1 >= path->count - 1 ? interval[path->count - 1][1] : interval[i + 2][0];
        points = path->points;
        if (i == 0) {
            values[0] = points[0].x;
        } else {
            values[0] = points[i - 1].x;
        }
        values[1] = points[i].x;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].x;
        } else {
            values[2] = points[i + 1].x;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].x;
        } else {
            values[3] = points[i + 2].x;
        }
        result->x = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].y;
        } else {
            values[0] = points[i - 1].y;
        }
        values[1] = points[i].y;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].y;
        } else {
            values[2] = points[i + 1].y;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].y;
        } else {
            values[3] = points[i + 2].y;
        }
        result->y = InterpolateBMLine(values, times, time);
        if (i == 0) {
            values[0] = points[0].z;
        } else {
            values[0] = points[i - 1].z;
        }
        values[1] = points[i].z;
        if (i >= path->count - 1) {
            values[2] = points[path->count - 1].z;
        } else {
            values[2] = points[i + 1].z;
        }
        if (i + 1 >= path->count - 1) {
            values[3] = points[path->count - 1].z;
        } else {
            values[3] = points[i + 2].z;
        }
        result->z = InterpolateBMLine(values, times, time);
    }
}

void opboard_PathKill(OpBoardPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void opboard_StarTalkExec(void) {
    s32 backgrounds[] = { 4, 7, 10, 13, 16, 19 };
    Vec directions[4];
    s16 effects[4];
    omObjData *obj;
    s32 i;
    s32 j;
    f32 scale;

    MBBackKill();
    MBBackLoad(backgrounds[GwSystem.current_board_index]);
    MBCameraNearFarSet(1000.0f, 10000.0f);
    opboard_centerMdl = MBModelCreate(58, opboard_starMot);
    AuraCreate(opboard_centerMdl->omObj1->model[0]);
    HuVecCopy3F(&opboard_centerMdl->coords, &opboard_starPos);
    opboard_centerMdl->velocity.x = 1000.0f;
    opboard_effNo = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(opboard_effNo, 10.0f, 20.0f, 10.0f);
    EffectRangeSet(opboard_effNo, 300.0f);
    Hu3DParticleAttrSet(opboard_effNo, 1, 0);
    for (j = 0; j < 4; j++) {
        HuVecCopy3F(&opboard_playerTbl[j]->player_obj->coords, &opboard_playerPosTbl[j]);
        effects[j] = opboard_SpiralEffCreate(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 4; j++) {
            opboard_SpiralEffAdd(effects[j], opboard_playerTbl[j]->player_obj->coords.x,
                                  opboard_playerTbl[j]->player_obj->coords.y + 50.0f,
                                  opboard_playerTbl[j]->player_obj->coords.z);
            if (i == 0) {
                MBPlayerVibrate(j, 1);
            }
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (j = 0; j < 4; j++) {
            MBModelDispOn(opboard_playerTbl[j]->player_obj);
            HuVecCopyXYZ(&opboard_playerTbl[j]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 4; j++) {
        HuVecCopyXYZ(&opboard_playerTbl[j]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    Hu3DParticleAttrSet(opboard_effNo, 1, 0);
    HuPrcSleep(20);
    EffectParamSet(opboard_effNo, 10.0f, 20.0f, 15.0f);
    EffectRangeSet(opboard_effNo, 300.0f);
    Hu3DParticleAttrSet(opboard_effNo, 0, 1);
    HuAudFXPlay(0x157);
    i = 0;
    while (opboard_centerMdl->velocity.x >= 400.0f) {
        opboard_centerMdl->velocity.x -= 10.0f;
        EffectPosSet(opboard_effNo, opboard_centerMdl->coords.x,
                           opboard_centerMdl->velocity.x - 100.0f, opboard_centerMdl->coords.z);
        i++;
        if (i == 20) {
            for (j = 0; j < 4; j++) {
                MBVecDirGet(&opboard_playerTbl[j]->player_obj->coords, &opboard_playerNearPosTbl[j],
                            &opboard_playerTbl[j]->player_obj->rot);
                MBPlayerPosMoveCreate(&opboard_playerTbl[j]->player_obj->coords, &opboard_playerNearPosTbl[j],
                                      &opboard_playerTbl[j]->player_obj->coords, 20);
                MBMotionSet(opboard_playerTbl[j]->player_obj, 1, 2);
            }
        }
        if (i == 40) {
            for (j = 0; j < 4; j++) {
                MBVecDirGet(&opboard_playerTbl[j]->player_obj->coords, &opboard_centerMdl->coords, &directions[j]);
                MBVecRotLerpCreate(&opboard_playerTbl[j]->player_obj->rot, &directions[j],
                                           &opboard_playerTbl[j]->player_obj->rot, 10);
                MBMotionShiftSet(opboard_playerTbl[j]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, opboard_CenterHoverObjMain);
    obj->rot.y = opboard_centerMdl->velocity.x;
    obj->rot.x = 180.0f;
    HuAudSeqPlay(13);
    HuAudFXPlay(0x159);
    if (GwSystem.playMode & 4) {
        s32 messages[] = { 0x1800, 0x1802, 0x1804, 0x1806, 0x1808, 0x180A };

        MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
        MBDlgWinInsertCreateAllKey(-1, messages[GwSystem.current_board_index], mbCharNameMesTbl[GwStory.unk1], 0, 0, 0, 0);
        MBDlgWinMesWaitAllKey();
        MBDlgWinMesWaitAllKey();
        if (GwSystem.current_board_index == 5) {
            MBDlgWinMesWaitAllKey();
        }
        MBDlgWinClose();
        MBDlgWinKill();
        MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
        {
            s32 files[] = { 0x1D0003, 0x1D0004, 0x1D0005, 0x1D0006, 0x1D0007, 0x1D0008 };

            if (GwSystem.current_board_index != 5) {
                Vec pos;
                OpBoardPath *path;
                s16 effect;
                f32 time;
                s32 k;

                opboard_stampMdl = MBModelFileCreate(files[GwSystem.current_board_index], -1, 1.0f, 0, NULL);
                path = opboard_PathCreate(opboard_stampPathPosTbl, 0);
                effect = EffectCreate(0xB0004, 0x6A9);
                EffectParamSet(effect, 4.0f, 20.0f, 4.0f);
                EffectRangeSet(effect, 60.0f);
                Hu3DParticleAttrSet(effect, 1, 1);
                Hu3DModelAttrSet(effect, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                HuAudFXPlay(0x215);
                for (k = 0; k < 50; k++) {
                    time = k * 0.02f;
                    opboard_PathPosGet(path, time * time, &pos);
                    HuVecCopy3F(&opboard_stampMdl->coords, &pos);
                    EffectPosSet(effect, pos.x, pos.y - 50.0f, pos.z);
                    HuPrcVSleep();
                }
                opboard_PathKill(path);
            }
        }
        {
            {
                s32 messages[] = { 0x1801, 0x1803, 0x1805, 0x1807, 0x1809, 0x180B };

                if (GwSystem.current_board_index != 5) {
                    MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
                    MBDlgWinInsertCreateAllKey(-1, messages[GwSystem.current_board_index], 0, 0, 0, 0, 0);
                    MBDlgWinMesWaitAllKey();
                    MBDlgWinClose();
                    MBDlgWinKill();
                    MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
                }
            }
        }
    } else {
        {
            s32 messages[] = { 0x180C, 0x180D, 0x180E, 0x180F, 0x1810, 0x1811 };

            MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
            MBDlgWinInsertCreateAllKey(-1, messages[GwSystem.current_board_index], 0, 0, 0, 0, 0);
            MBDlgWinMesWaitAllKey();
            MBDlgWinMesWaitAllKey();
            MBDlgWinClose();
            MBDlgWinKill();
            MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
        }
    }
    for (j = 0; j < 4; j++) {
        MBVecDirGet(&opboard_playerTbl[j]->player_obj->coords, &opboard_playerPosTbl[j],
                    &opboard_playerTbl[j]->player_obj->rot);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&opboard_playerTbl[j]->player_obj->coords,
                                                                &opboard_playerPosTbl[j], &opboard_playerTbl[j]->player_obj->coords, 20));
        MBMotionSet(opboard_playerTbl[j]->player_obj, 1, 2);
    }
    HuPrcChildWatch();
    for (j = 0; j < 4; j++) {
        f32 angles[] = { 5.0f, 0.0f, 0.0f, -5.0f };

        directions[j].x = sindf(angles[j]);
        directions[j].z = cosdf(angles[j]);
        directions[j].y = 0;
        HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&opboard_playerTbl[j]->player_obj->rot,
                                                                     &directions[j], &opboard_playerTbl[j]->player_obj->rot, 10));
        MBMotionShiftSet(opboard_playerTbl[j]->player_obj, -1, 0, 5, 2);
    }
    HuPrcChildWatch();
    opboard_TurnOrderExec();
    MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
    MBDlgWinInsertCreateAllKey(-1, 0x1816, 0, 0, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
    for (j = 0; j < 4; j++) {
        if (j == 0) {
            MBCoinTakeCreate(0, 10);
        } else {
            MBCoinTakeCreateSound(j, 10, 0);
        }
        MBMotionShiftSetDef(opboard_playerTbl[j]->player_obj, 4, 0);
    }
    HuPrcSleep(60);
    for (j = 0; j < 4; j++) {
        MBMotionShiftSetDef(opboard_playerTbl[j]->player_obj, -1, 2);
    }
    MBMotionShiftSet(opboard_centerMdl, 0, 0, 5, 2);
    MBDlgWinInsertCreateAllKey(-1, 0x1817, 0, 0, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MBMotionShiftSet(opboard_centerMdl, -1, 0, 5, 2);
    EffectStop(opboard_effNo);
}

void opboard_MainProc(void) {
    opboard_arriveProc = omAddPrcObj(opboard_ArriveProc, 0x300, 0x2000, 0);
    HuPrcChildLink(HuPrcCurrentGet(), opboard_arriveProc);
    HuPrcChildWatch();
    opboard_StarTalkExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void opboard_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        opboard_BackClose();
        opboard_SysClose();
        HuWinAllKill();
        if (opboard_statusCreateF != 0) {
            MBStatusKill();
        }
        omOvlReturnEx(1);
    }
}

void opboard_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(2, 20);
        HuAudSeqFadeOut(60);
        obj->func = opboard_ExitObjMain;
    }
}

void opboard_SysInit(void) {
    MBModelInit();
    MBPlayerMotInit();
    MBMotShiftInit();
    MBSprGrpInit();
}

void opboard_SysClose(void) {
    MBSprGrpClose();
    MBMotShiftClose();
    MBPlayerClose();
    MBModelClose();
}

void opboard_BackInit(void) {
    s32 sp10[] = { 3, 6, 9, 0xC, 0xF, 0x12 };

    Hu3DCamInit(1);
    MBBackArcInit((u32)hvq_data_ROM_START);
    MBBackLoad(sp10[GwSystem.current_board_index]);
}

void opboard_BackClose() {
    MBBackKill();
    MBBackClose();
}
