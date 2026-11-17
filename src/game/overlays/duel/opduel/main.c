#include "common_duel.h"
#include "macros.h"
#include "game/overlays/duel/common/ovl_81.h"

extern s32 mbKSuitObj[];
extern u8 mbdCharPartnerTbl[];

void MBDPlayerModelCreate(s16, u32 *, s16);
void MBDDlgWinExecAllKey(s32, s32);
void MBDDlgWinMesWaitAllKey(void);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void MBDVecForwardSet(Vec *);
Process *MBDVecRotLerpCreate(Vec *, Vec *, Vec *, s32);
Process *MBDPlayerPosMoveCreate(Vec *, Vec *, Vec *, s32);
s32 MBDModelTargetMoveRot(Object *, Vec *, f32);
void MBDStatusPosSet(s32, s16, s16);
void MBDCoinTakeCreateSound(s32, s32, s32);
void MBDStatusScaleSet(s32, f32, f32);
void MBDStatusPartnerPosSet(s32, s32, s16, s32);
void MBDStatusCostUpdateSet(s32);
void MBDStatusBounceExec(s32);
void MBDPartnerSet(s32, s32, s32);
void opduel_SpiralEffHook(s16 model);
void opduel_SkipObjMain(omObjData *obj);
void opduel_ArriveProc(void);
void opduel_StarTalkExec(void);
void opduel_MainProc(void);
void opduel_ExitObjMain(omObjData *obj);
void opduel_ExitCheckObjMain(omObjData *obj);
void opduel_SysInit(void);
void opduel_SysClose(void);
void opduel_BackInit(void);
void opduel_BackClose(void);

s32 opduel_statusCreateF = 0;
Process *opduel_unusedProc = NULL;
Object *opduel_centerMdl = NULL;
Object *opduel_shadowMdl = NULL;
omObjData *opduel_centerBobObj = NULL;
s16 opduel_effNo = -1;
Process *opduel_arriveProc = NULL;
UnkBoard4 *opduel_titleGrp = NULL;
UnkBoard4 *opduel_subtitleGrp = NULL;
omObjData *opduel_skipObj = NULL;
s32 opduel_skipF = 0;

Vec opduel_platformPos = { 0.0f, 250.0f, 0.0f };

/* Unreferenced. */
Vec opduel_unusedPosTbl[2] = {
    { 0.0f, 100.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};

Vec opduel_starPos = { 0.0f, 0.0f, 1500.0f };

Vec opduel_playerStartPosTbl[4] = {
    { -10.0f, 250.0f, 0.0f },
    { 10.0f, 250.0f, 0.0f },
    { -500.0f, 0.0f, 2360.0f },
    { 500.0f, 0.0f, 2360.0f }
};

Vec opduel_playerFarPosTbl[2] = {
    { -200.0f, 0.0f, 2360.0f },
    { 200.0f, 0.0f, 2360.0f }
};

Vec opduel_playerNearPosTbl[2] = {
    { -175.0f, 0.0f, 2250.0f },
    { 175.0f, 0.0f, 2250.0f }
};

Vec opduel_playerSwapPosTbl[2] = {
    { 0.0f, 0.0f, 2150.0f },
    { 0.0f, 0.0f, 2350.0f }
};

Vec opduel_playerPosTbl[2] = {
    { -125.0f, 0.0f, 2000.0f },
    { 125.0f, 0.0f, 2000.0f }
};

Vec opduel_partnerStartPosTbl[2] = {
    { -750.0f, 0.0f, 1750.0f },
    { 750.0f, 0.0f, 1750.0f }
};

Vec opduel_partnerPosTbl[2] = {
    { -100.0f, 0.0f, 1750.0f },
    { 100.0f, 0.0f, 1750.0f }
};

Vec opduel_partnerSlotPosTbl[4] = {
    { -100.0f, 0.0f, 2000.0f },
    { 100.0f, 0.0f, 2000.0f },
    { -300.0f, 0.0f, 2000.0f },
    { 300.0f, 0.0f, 2000.0f }
};

u32 opduel_playerMotMario[6] = { 5, 0x20000, 0x20001, 0x20002, 0x20033, 0x20031 };

u32 opduel_playerMotLuigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotPeach[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotYoshi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotWario[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotDk[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotWaluigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opduel_playerMotDaisy[6] = { 5, 0, 0, 0, 0, 0 };

u32 *opduel_playerMotTbl[8] = { opduel_playerMotMario, opduel_playerMotLuigi, opduel_playerMotPeach, opduel_playerMotYoshi, opduel_playerMotWario, opduel_playerMotDk, opduel_playerMotWaluigi, opduel_playerMotDaisy };

s32 opduel_partnerMotMario[2] = { 1, 0xA0090 };

s32 opduel_partnerMotLuigi[2] = { 1, 0xA00A7 };

s32 opduel_partnerMotPeach[2] = { 1, 0xA0002 };

s32 opduel_partnerMotWario[2] = { 1, 0xA00BD };

s32 opduel_partnerMotDk[2] = { 1, 0xA00D0 };

s32 opduel_partnerMotDaisy[2] = { 1, 0xA0138 };

s32 opduel_partnerMotWaluigi[2] = { 1, 0xA010F };

s32 *opduel_partnerMotTbl[8] = { opduel_partnerMotMario, opduel_partnerMotLuigi, opduel_partnerMotPeach, NULL, opduel_partnerMotWario, opduel_partnerMotDk, opduel_partnerMotWaluigi, opduel_partnerMotDaisy };

s32 opduel_starMot[2] = { 1, 0xA0125 };

u8 opduel_boardNo BSS;
GW_PLAYER *opduel_playerTbl[2] BSS;
Object *opduel_partnerMdlTbl[2] BSS;

void opduel_ObjectSetup(void) {
    GW_PLAYER *player;
    s32 i;
    s32 j;

    opduel_boardNo = GwSystem.current_board_index;
    omInitObjMan(50, 20);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightColorSet(2, 200, 200, 200);
    opduel_BackInit();
    opduel_SysInit();
    MBDShadowHeightMaxSet(700.0f);
    MBDModelScaleMulSet(1.6f);
    HuWinInit();
    omAddPrcObj(opduel_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, opduel_ExitCheckObjMain);
    for (j = 0; j < 2; j++) {
        player = MBDPlayerGet(j);
        player->stats.partners.frontID = -1;
        player->stats.partners.backID = -1;
    }
    for (i = 1; i < 8; i++) {
        for (j = 0; j < opduel_playerMotMario[0]; j++) {
            opduel_playerMotTbl[i][j + 1] = CharMotionDataNumGet(i, opduel_playerMotMario[j + 1]);
        }
    }
    omGameSysInit();
}

s16 opduel_SpiralEffCreate(s32 file, s32 flags) {
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
    Hu3DParticleCreate(model, -1, 0, opduel_SpiralEffHook);
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

s32 opduel_SpiralEffAdd(s16 model, f32 x, f32 y, f32 z) {
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
            particle->unk18 = MBDRand(360.0f);
            particle->unk20 = effect->unk10.f / 10.0f;
            angle = MBDRand(150.0f);
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

void opduel_SpiralEffHook(s16 model) {
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

void opduel_PlayerSwap(s32 player1, s32 player2) {
    GW_PLAYER *first = MBDPlayerGet(player1);
    GW_PLAYER *second = MBDPlayerGet(player2);
    GW_PLAYER *temp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));

    bcopy(first, temp, sizeof(GW_PLAYER));
    bcopy(second, first, sizeof(GW_PLAYER));
    bcopy(temp, second, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(temp);
}

void opduel_SkipObjMain(omObjData *obj) {
    s32 i;

    if (WipeStatGet() != 0) {
        return;
    }
    if (opduel_effNo != -1) {
        EffectStop(opduel_effNo);
        opduel_effNo = -1;
    }
    if (opduel_centerMdl != NULL) {
        MBDModelKill(opduel_centerMdl);
        opduel_centerMdl = NULL;
    }
    if (opduel_shadowMdl != NULL) {
        MBDModelKill(opduel_shadowMdl);
        opduel_shadowMdl = NULL;
    }
    if (opduel_centerBobObj != NULL) {
        omDelObj(opduel_centerBobObj);
        opduel_centerBobObj = NULL;
    }
    if (opduel_arriveProc != NULL) {
        omDelPrcObj(opduel_arriveProc);
        opduel_arriveProc = NULL;
    }
    if (opduel_titleGrp != NULL) {
        MBDSprGrpKill(opduel_titleGrp);
        opduel_titleGrp = NULL;
    }
    if (opduel_subtitleGrp != NULL) {
        MBDSprGrpKill(opduel_subtitleGrp);
        opduel_subtitleGrp = NULL;
    }
    for (i = 0; i < 2; i++) {
        MBDModelDispOff(opduel_playerTbl[i]->player_obj);
    }
    omDelObj(obj);
}

void opduel_SkipCheckObjMain(omObjData *obj) {
    s32 i;

    for (i = 0; i < 2; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            if (ContBtnDown[GwPlayer[i].pad] & START_BUTTON) {
                break;
            }
        }
    }
    if (i != 2) {
        opduel_skipF = 1;
        WipeColorSet(255, 255, 255);
        WipeCreateOut(WIPE_FADE, 16);
        HuAudSeqFadeOut(32);
        msmSeFadeOut(32);
        obj->func = opduel_SkipObjMain;
    }
}

void opduel_CenterBobObjMain(omObjData *obj) {
    s32 i;

    opduel_centerMdl->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        opduel_playerTbl[i]->player_obj->coords.y = opduel_centerMdl->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void opduel_BoardTitleExec(void) {
    s32 titleFiles[] = { 0x130022, 0x130023, 0x130024, 0x130025, 0x130026, 0x130027 };
    s32 subtitleFiles[] = { 0x130028, 0x130029, 0x13002A, 0x13002B, 0x13002C, 0x13002D };
    void *data;
    f32 amplitude;
    f32 angle;

    HuPrcSleep(10);
    opduel_titleGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(titleFiles[opduel_boardNo]);
    opduel_titleGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(opduel_titleGrp->unk_0A, 0, opduel_titleGrp->unk_0C[0], 0);
    HuSprPriSet(opduel_titleGrp->unk_0A, 0, 10);
    HuSprAttrSet(opduel_titleGrp->unk_0A, 0, HUSPR_ATTR_NONE);
    HuSprPosSet(opduel_titleGrp->unk_0A, 0, 160, 100);
    HuSprScaleSet(opduel_titleGrp->unk_0A, 0, 0.0f, 0.0f);
    for (amplitude = 0.5f, angle = 0.0f; angle <= 720.0f; angle += 45.0f) {
        HuSprScaleSet(opduel_titleGrp->unk_0A, 0,
                      sindf(angle) * amplitude + 1.0f, sindf(angle) * amplitude + 1.0f);
        amplitude -= 0.03125f;
        if (amplitude < 0.0f) {
            amplitude = 0.0f;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(20);
    HuSprScaleSet(opduel_titleGrp->unk_0A, 0, 1.0f, 1.0f);
    opduel_subtitleGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(subtitleFiles[opduel_boardNo]);
    opduel_subtitleGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(opduel_subtitleGrp->unk_0A, 0, opduel_subtitleGrp->unk_0C[0], 0);
    HuSprPriSet(opduel_subtitleGrp->unk_0A, 0, 9);
    HuSprAttrSet(opduel_subtitleGrp->unk_0A, 0, HUSPR_ATTR_NONE);
    HuSprPosSet(opduel_subtitleGrp->unk_0A, 0, 160, 130);
    HuPrcSleep(75);
    MBDSprGrpKill(opduel_subtitleGrp);
    MBDSprGrpKill(opduel_titleGrp);
    opduel_subtitleGrp = NULL;
    opduel_titleGrp = NULL;
}

void opduel_ArriveProc(void) {
    s32 i;
    f32 scale;

    for (i = 0; i < 2; i++) {
        opduel_playerTbl[i] = MBDPlayerGet(i);
        MBDPlayerModelCreate(i, opduel_playerMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&opduel_playerTbl[i]->player_obj->coords, &opduel_playerStartPosTbl[i]);
        MBDModelTempAllocFree(opduel_playerTbl[i]->player_obj);
        opduel_playerTbl[i]->stat |= PLAYER_UNK_04;
    }
    opduel_centerMdl = MBDModelFileCreate(0x1301FF, -1, 1.0f, 0, 0);
    HuVecCopyXYZ(&opduel_centerMdl->scale, 0.625f, 0.625f, 0.625f);
    opduel_shadowMdl = MBDModelFileCreate(0x1301FD, -1, 1.0f, 0, 0);
    HuVecCopy3F(&opduel_centerMdl->coords, &opduel_platformPos);
    HuVecCopy3F(&opduel_shadowMdl->coords, &opduel_platformPos);
    opduel_shadowMdl->coords.y = 0;
    HuVecCopyXYZ(&opduel_shadowMdl->scale, opduel_shadowMdl->coords.y, opduel_shadowMdl->coords.y, opduel_shadowMdl->coords.y);
    opduel_effNo = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(opduel_effNo, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(opduel_effNo, 40.0f);
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    WipeCreateIn(WIPE_STARS, 16);
    HuPrcSleep(17);
    opduel_skipObj = omAddObj(0x1000, 0, 0, -1, opduel_SkipCheckObjMain);
    HuAudSeqPlay(110);
    opduel_BoardTitleExec();
    HuPrcSleep(15);
    HuAudFXPlay(0x2ED);
    while (opduel_centerMdl->coords.y >= 10.0f) {
        opduel_centerMdl->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            opduel_playerTbl[i]->player_obj->coords.y -= 3.0f;
        }
        HuVecCopyXYZ(&opduel_shadowMdl->scale,
                     0.625f - opduel_centerMdl->coords.y * 0.625f / 250.0f,
                     0.625f - opduel_centerMdl->coords.y * 0.625f / 250.0f,
                     0.625f - opduel_centerMdl->coords.y * 0.625f / 250.0f);
        HuPrcVSleep();
    }
    opduel_centerBobObj = omAddObj(0x1000, 0, 0, -1, opduel_CenterBobObjMain);
    opduel_centerBobObj->rot.x = 180.0f;
    opduel_centerBobObj->rot.y = 5.0f;
    opduel_centerBobObj->rot.z = opduel_centerMdl->coords.y;
    HuPrcSleep(30);
    EffectPosSet(opduel_effNo, opduel_centerMdl->coords.x,
                       opduel_centerMdl->coords.y + 40.0f, opduel_centerMdl->coords.z);
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&opduel_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        MBDModelDispOff(opduel_playerTbl[i]->player_obj);
    }
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    HuPrcSleep(20);
    if (opduel_skipF != 0) {
        HuPrcSleep(-1);
    } else {
        omDelObj(opduel_skipObj);
        opduel_skipObj = NULL;
    }
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&opduel_centerMdl->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    EffectStop(opduel_effNo);
    opduel_effNo = -1;
    MBDModelKill(opduel_centerMdl);
    opduel_centerMdl = NULL;
    MBDModelKill(opduel_shadowMdl);
    opduel_shadowMdl = NULL;
    omDelObj(opduel_centerBobObj);
    opduel_centerBobObj = NULL;
    omDelPrcObj(NULL);
}

void opduel_CenterHoverObjMain(omObjData *obj) {
    opduel_centerMdl->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

void opduel_StarTalkExec(void) {
    Vec directions[2];
    s32 backgrounds[] = { 0x17, 0x17, 0x17, 0x17, 0x17, 0x17 };
    s16 effects[2];
    HmfMotionNode *node;
    omObjData *obj;
    s32 i;
    s32 j;
    s32 retried;
    f32 scale;
    f32 angle;
    f32 radius;
    f32 speed;
    f32 base;

    MBDBackKill();
    MBDBackLoad(backgrounds[GwSystem.current_board_index]);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
    opduel_centerMdl = MBDModelCreate(59, opduel_starMot);
    AuraCreate(opduel_centerMdl->omObj1->model[0]);
    HuVecCopy3F(&opduel_centerMdl->coords, &opduel_starPos);
    opduel_centerMdl->velocity.x = 900.0f;
    opduel_effNo = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(opduel_effNo, 15.0f, 20.0f, 8.0f);
    EffectRangeSet(opduel_effNo, 200.0f);
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&opduel_playerTbl[i]->player_obj->coords, &opduel_playerPosTbl[i]);
        effects[i] = opduel_SpiralEffCreate(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(WIPE_FADE, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            opduel_SpiralEffAdd(effects[i], opduel_playerTbl[i]->player_obj->coords.x,
                                 opduel_playerTbl[i]->player_obj->coords.y + 50.0f,
                                 opduel_playerTbl[i]->player_obj->coords.z);
            if (j == 0) {
                MBDPlayerVibrate(i, 1);
            }
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            MBDModelDispOn(opduel_playerTbl[i]->player_obj);
            HuVecCopyXYZ(&opduel_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&opduel_playerTbl[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuAudFXPlay(0x2DD);
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    angle = 0.0f;
    radius = 500.0f;
    j = 0;
    while (opduel_centerMdl->velocity.x >= 300.0f) {
        opduel_centerMdl->coords.x = sindf(angle) * radius;
        opduel_centerMdl->coords.z = cosdf(angle) * radius + opduel_starPos.z;
        opduel_centerMdl->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        EffectPosSet(opduel_effNo, opduel_centerMdl->coords.x,
                           opduel_centerMdl->velocity.x - 50.0f, opduel_centerMdl->coords.z);
        j++;
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&opduel_playerTbl[i]->player_obj->coords, &opduel_playerFarPosTbl[i],
                                      &opduel_playerTbl[i]->player_obj->rot);
                MBDPlayerPosMoveCreate(&opduel_playerTbl[i]->player_obj->coords, &opduel_playerFarPosTbl[i],
                                      &opduel_playerTbl[i]->player_obj->coords, 20);
                MBDMotionSet(opduel_playerTbl[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&opduel_playerTbl[i]->player_obj->coords, &opduel_starPos,
                                      &directions[i]);
                MBDVecRotLerpCreate(&opduel_playerTbl[i]->player_obj->rot, &directions[i],
                                      &opduel_playerTbl[i]->player_obj->rot, 10);
                MBDMotionShiftSet(opduel_playerTbl[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, opduel_CenterHoverObjMain);
    obj->trans.y = opduel_centerMdl->velocity.x;
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&opduel_playerTbl[i]->player_obj->coords,
                                                                &opduel_playerNearPosTbl[i],
                                                                &opduel_playerTbl[i]->player_obj->coords, 20));
        MBDMotionSet(opduel_playerTbl[i]->player_obj, 2, 2);
    }
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        MBDMotionShiftSet(opduel_playerTbl[i]->player_obj, -1, 0, 5, 2);
    }
    HuAudSeqPlay(13);
    HuAudFXPlay(0x159);
    {
        s32 messages[] = { 0x2701, 0x2702, 0x2703, 0x2704, 0x2705, 0x2706 };

        MBDMotionSet(opduel_centerMdl, 0, 2);
        MBDDlgWinInsertCreateAllKey(-1, 0x2700, messages[opduel_boardNo], 0, 0, 0, 0);
        MBDDlgWinMesWaitAllKey();
        MBDDlgWinMesWaitAllKey();
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBDMotionSet(opduel_centerMdl, -1, 2);
    }
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        opduel_centerMdl->rot.x = sindf(angle);
        opduel_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    MBDVecForwardSet(&directions[0]);
    MBDVecRotLerpCreate(&opduel_playerTbl[0]->player_obj->rot, &directions[0],
                          &opduel_playerTbl[0]->player_obj->rot, 10);
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinInsertCreateAllKey(-1, 0x2707, mbKSuitObj[GwPlayer[0].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    MBDMotionSet(opduel_centerMdl, -1, 2);
    MBDVecDirGet(&opduel_playerTbl[0]->player_obj->coords, &opduel_centerMdl->coords, &directions[0]);
    MBDVecRotLerpCreate(&opduel_playerTbl[0]->player_obj->rot, &directions[0],
                          &opduel_playerTbl[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        opduel_centerMdl->rot.x = sindf(angle);
        opduel_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    MBDVecForwardSet(&directions[1]);
    MBDVecRotLerpCreate(&opduel_playerTbl[1]->player_obj->rot, &directions[1],
                          &opduel_playerTbl[1]->player_obj->rot, 10);
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinInsertCreateAllKey(-1, 0x2708, mbKSuitObj[GwPlayer[1].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    MBDMotionSet(opduel_centerMdl, -1, 2);
    MBDVecDirGet(&opduel_playerTbl[1]->player_obj->coords, &opduel_centerMdl->coords, &directions[1]);
    MBDVecRotLerpCreate(&opduel_playerTbl[1]->player_obj->rot, &directions[1],
                          &opduel_playerTbl[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        opduel_centerMdl->rot.x = sindf(angle);
        opduel_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    retried = 0;
    opduel_centerMdl->rot.x = sindf(0.0f);
    opduel_centerMdl->rot.z = cosdf(0.0f);
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinExecAllKey(-1, 0x2709);
    MBDMotionSet(opduel_centerMdl, -1, 2);
    j = MBDRand(2.0f);
spin:
    HuAudFXPlay(0x2DE);
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        opduel_centerMdl->rot.x = sindf(angle);
        opduel_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        opduel_centerMdl->rot.x = sindf(angle);
        opduel_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    switch (MBDRand(20.0f)) {
        case 0:
            if (retried == 0) {
                retried = 1;
                while (!(angle >= 160.0f && angle <= 200.0f)) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    opduel_centerMdl->rot.x = sindf(angle);
                    opduel_centerMdl->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                for (speed = 30.0f; speed >= 0.0f; speed -= 1.0f) {
                    angle += speed;
                    if (angle > 360.0f) {
                        angle -= 360.0f;
                    }
                    opduel_centerMdl->rot.x = sindf(angle);
                    opduel_centerMdl->rot.z = cosdf(angle);
                    HuPrcVSleep();
                }
                Hu3DParticleAttrSet(opduel_effNo, 1, 0);
                HuPrcSleep(30);
                MBDMotionSet(opduel_centerMdl, 0, 2);
                MBDDlgWinExecAllKey(-1, 0x270A);
                MBDMotionSet(opduel_centerMdl, -1, 2);
                goto spin;
            }
            // fallthrough
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle);
                opduel_centerMdl->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (j != 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else {
                    if (angle >= 70.0f && angle <= 110.0f) {
                        break;
                    }
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.0f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle);
                opduel_centerMdl->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            Hu3DParticleAttrSet(opduel_effNo, 1, 0);
            HuPrcSleep(20);
            Hu3DParticleAttrSet(opduel_effNo, 0, 1);
            speed = -25.0f;
            for (i = 0; i < 6; i++) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle);
                opduel_centerMdl->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = 180.0f;
            if (j == 0) {
                angle = 0.0f;
            }
            opduel_centerMdl->rot.x = sindf(angle);
            opduel_centerMdl->rot.z = cosdf(angle);
            for (i = 0; i < 30; i++) {
                angle += 90.0f;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle) / (i + 10.0f);
                HuPrcVSleep();
            }
            break;
        default:
            while (TRUE) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle);
                opduel_centerMdl->rot.z = cosdf(angle);
                HuPrcVSleep();
                if (j == 0) {
                    if (angle >= 250.0f && angle <= 290.0f) {
                        break;
                    }
                } else {
                    if (angle >= 70.0f && angle <= 110.0f) {
                        break;
                    }
                }
            }
            for (speed = 30.0f; speed > 3.0f; speed -= 1.04f) {
                angle += speed;
                if (angle > 360.0f) {
                    angle -= 360.0f;
                }
                opduel_centerMdl->rot.x = sindf(angle);
                opduel_centerMdl->rot.z = cosdf(angle);
                HuPrcVSleep();
            }
            angle = 180.0f;
            if (j == 0) {
                angle = 0.0f;
            }
            opduel_centerMdl->rot.x = sindf(angle);
            opduel_centerMdl->rot.z = cosdf(angle);
            break;
    }
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    MBDPlayerVibrate(j, 2);
    HuPrcSleep(20);
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinExecAllKey(-1, 0x270B);
    MBDMotionSet(opduel_centerMdl, -1, 2);
    if (j == 0) {
        MBDMotionSet(opduel_centerMdl, 0, 2);
        MBDDlgWinInsertCreateAllKey(-1, 0x270C, mbKSuitObj[GwPlayer[0].chr], 0, 0, 0, 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBDMotionSet(opduel_centerMdl, -1, 2);
    } else {
        MBDMotionSet(opduel_centerMdl, 0, 2);
        MBDDlgWinInsertCreateAllKey(-1, 0x270C, mbKSuitObj[GwPlayer[1].chr], 0, 0, 0, 0);
        MBDDlgWinClose();
        MBDDlgWinKill();
        MBDMotionSet(opduel_centerMdl, -1, 2);
        MBDVecDirGet(&opduel_playerTbl[0]->player_obj->coords, &opduel_playerTbl[1]->player_obj->coords,
                              &opduel_playerTbl[0]->player_obj->rot);
        MBDVecDirGet(&opduel_playerTbl[1]->player_obj->coords, &opduel_playerTbl[0]->player_obj->coords,
                              &opduel_playerTbl[1]->player_obj->rot);
        MBDMotionSet(opduel_playerTbl[0]->player_obj, 2, 2);
        MBDMotionSet(opduel_playerTbl[1]->player_obj, 2, 2);
        while (TRUE) {
            j = MBDModelTargetMoveRot(opduel_playerTbl[0]->player_obj, &opduel_playerSwapPosTbl[0], 10.0f);
            if (MBDModelTargetMoveRot(opduel_playerTbl[1]->player_obj, &opduel_playerSwapPosTbl[1], 10.0f) && j) {
                break;
            }
            HuPrcVSleep();
        }
        while (TRUE) {
            j = MBDModelTargetMoveRot(opduel_playerTbl[0]->player_obj, &opduel_playerNearPosTbl[1], 10.0f);
            if (MBDModelTargetMoveRot(opduel_playerTbl[1]->player_obj, &opduel_playerNearPosTbl[0], 10.0f) && j) {
                break;
            }
            HuPrcVSleep();
        }
        opduel_PlayerSwap(0, 1);
        MBDVecDirGet(&opduel_playerTbl[1]->player_obj->coords, &opduel_centerMdl->coords, &directions[1]);
        MBDVecRotLerpCreate(&opduel_playerTbl[1]->player_obj->rot, &directions[1],
                              &opduel_playerTbl[1]->player_obj->rot, 5);
        MBDMotionSet(opduel_playerTbl[0]->player_obj, 0, 2);
        MBDMotionSet(opduel_playerTbl[1]->player_obj, 0, 2);
    }
    MBDVecForwardSet(&opduel_playerTbl[0]->player_obj->rot);
    MBDMotionSet(opduel_playerTbl[0]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 0);
    MBDStatusCreate();
    {
        s16 positions[][2] = { { 30, 40 }, { 194, 40 } };

        MBDStatusPosSet(0, positions[0][0], positions[0][1]);
        MBDStatusPosSet(1, positions[1][0], positions[1][1]);
    }
    MBDStatusScaleSet(0, 0.0f, 0.0f);
    MBDStatusScaleSet(1, 0.0f, 0.0f);
    opduel_statusCreateF = 1;
    MBDStatusBounceExec(0);
    MBDPlayerVibrate(0, 3);
    MBDModelMotionWait(opduel_playerTbl[0]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet(opduel_playerTbl[0]->player_obj, 0, 2);
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinInsertCreateAllKey(-1, 0x270D, mbKSuitObj[GwPlayer[1].chr], 0, 0, 0, 0);
    MBDDlgWinClose();
    MBDDlgWinKill();
    MBDMotionSet(opduel_centerMdl, -1, 2);
    MBDVecForwardSet(&opduel_playerTbl[1]->player_obj->rot);
    MBDMotionSet(opduel_playerTbl[1]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 1);
    MBDStatusBounceExec(1);
    MBDPlayerVibrate(1, 3);
    MBDModelMotionWait(opduel_playerTbl[1]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet(opduel_playerTbl[1]->player_obj, 0, 2);
    if (j != 0) {
        Hu3DParticleAttrSet(opduel_effNo, 0, 1);
        MBDVecForwardSet(&directions[0]);
        MBDVecRotLerpCreate(&opduel_centerMdl->rot, &directions[0], &opduel_centerMdl->rot, 5);
        HuPrcSleep(6);
        Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    }
    MBDMotionSet(opduel_centerMdl, 0, 2);
    MBDDlgWinExecAllKey(-1, 0x270E);
    MBDMotionSet(opduel_centerMdl, -1, 2);
    Hu3DMotionNoMotSet(opduel_centerMdl->omObj1->model[0], Hu3DData[opduel_centerMdl->omObj1->model[0]].motId,
                       "l_mayu", 0x4C, 0x47);
    node = Hu3DModelObjPtrGet(opduel_centerMdl->omObj1->model[0], "l_mayu");
    for (i = 0; i < 30; i += 2) {
        node->baseRot.z = i;
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(opduel_effNo, 0, 1);
    HuAudFXPlay(0x174);
    Hu3DMotionNoMotSet(opduel_centerMdl->omObj1->model[0], Hu3DData[opduel_centerMdl->omObj1->model[0]].motId,
                       "hige", 0x17, 0x46);
    node = Hu3DModelObjPtrGet(opduel_centerMdl->omObj1->model[0], "hige");
    base = node->basePos.y;
    for (i = 0; i < 30; i += 2) {
        node->basePos.y = sindf(i * 45) * 10.0f + base;
        HuPrcVSleep();
    }
    node->basePos.y = base;
    Hu3DParticleAttrSet(opduel_effNo, 1, 0);
    {
        s32 models[] = { 0x25, 0x0C, 0x09, 0x0A, 0x26, 0x0B, 0x2C, 0x24 };
        s32 sounds[] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };

        for (i = 0; i < 2; i++) {
            opduel_partnerMdlTbl[i] = MBDModelCreate(models[GwPlayer[i].chr], opduel_partnerMotTbl[GwPlayer[i].chr]);
            HuVecCopy3F(&opduel_partnerMdlTbl[i]->coords, &opduel_partnerStartPosTbl[i]);
            HuAudFXPlay(sounds[GwPlayer[i].chr]);
        }
    }
    MBDMotionSet(opduel_partnerMdlTbl[0], 0, 2);
    MBDMotionSet(opduel_partnerMdlTbl[1], 0, 2);
    while (TRUE) {
        j = MBDModelTargetMoveRot(opduel_partnerMdlTbl[0], &opduel_partnerPosTbl[0], 20.0f);
        if (MBDModelTargetMoveRot(opduel_partnerMdlTbl[1], &opduel_partnerPosTbl[1], 20.0f) && j) {
            break;
        }
        HuPrcVSleep();
    }
    MBDVecForwardSet(&directions[0]);
    MBDVecForwardSet(&directions[1]);
    MBDVecRotLerpCreate(&opduel_partnerMdlTbl[0]->rot, &directions[0], &opduel_partnerMdlTbl[0]->rot, 10);
    MBDVecRotLerpCreate(&opduel_partnerMdlTbl[1]->rot, &directions[1], &opduel_partnerMdlTbl[1]->rot, 10);
    HuPrcSleep(10);
    MBDMotionSet(opduel_partnerMdlTbl[0], -1, 2);
    MBDMotionSet(opduel_partnerMdlTbl[1], -1, 2);
    MBDVecDirGet(&opduel_playerTbl[0]->player_obj->coords, &opduel_playerTbl[1]->player_obj->coords,
                          &directions[0]);
    MBDVecDirGet(&opduel_playerTbl[1]->player_obj->coords, &opduel_playerTbl[0]->player_obj->coords,
                          &directions[1]);
    MBDVecRotLerpCreate(&opduel_playerTbl[0]->player_obj->rot, &directions[0],
                          &opduel_playerTbl[0]->player_obj->rot, 5);
    MBDVecRotLerpCreate(&opduel_playerTbl[1]->player_obj->rot, &directions[1],
                          &opduel_playerTbl[1]->player_obj->rot, 5);
    MBDMotionShiftSet(opduel_centerMdl, 0, 0, 5, 2);
    MBDDlgWinExecAllKey(-1, 0x270F);
    MBDMotionShiftSet(opduel_centerMdl, -1, 0, 5, 2);
    {
        s32 choices[2];
        DuelHelpWin *window1;
        DuelHelpWin *window2;

        choices[0] = 0;
        choices[1] = 0;
        window1 = MBDHelpWinCreate(20, 174, 1);
        window2 = MBDHelpWinCreate(21, 188, 1);
        while (choices[0] == 0 || choices[1] == 0) {
            for (i = 0; i < 2; i++) {
                if (choices[i] != 0) {
                    continue;
                }
                if (MBDPlayerComCheck(i) == 0) {
                    if (ContBtnDown[GwPlayer[i].pad] & A_BUTTON) {
                        choices[i] = 1;
                    } else if (ContBtnDown[GwPlayer[i].pad] & B_BUTTON) {
                        choices[i] = 2;
                    }
                } else {
                    choices[i] = 1;
                    switch (GwPlayer[i].chr) {
                        case 5:
                            choices[i] = 2;
                            break;
                        case 2:
                            if (MBDRand(100.0f) < 50) {
                                choices[i] = 2;
                            }
                            break;
                        case 0:
                            if (MBDRand(100.0f) < 20) {
                                choices[i] = 2;
                            }
                            break;
                    }
                }
            }
            HuPrcVSleep();
        }
        MBDHelpWinKill(window1);
        MBDHelpWinKill(window2);
        MBDMotionSet(opduel_partnerMdlTbl[0], 0, 2);
        MBDMotionSet(opduel_partnerMdlTbl[1], 0, 2);
        MBDVecDirGet(&opduel_partnerMdlTbl[0]->coords, &opduel_partnerSlotPosTbl[(choices[0] - 1) * 2],
                              &opduel_partnerMdlTbl[0]->rot);
        MBDVecDirGet(&opduel_partnerMdlTbl[1]->coords, &opduel_partnerSlotPosTbl[(choices[1] - 1) * 2 + 1],
                              &opduel_partnerMdlTbl[1]->rot);
        MBDPlayerPosMoveCreate(&opduel_partnerMdlTbl[0]->coords, &opduel_partnerSlotPosTbl[(choices[0] - 1) * 2],
                              &opduel_partnerMdlTbl[0]->coords, 20);
        MBDPlayerPosMoveCreate(&opduel_partnerMdlTbl[1]->coords, &opduel_partnerSlotPosTbl[(choices[1] - 1) * 2 + 1],
                              &opduel_partnerMdlTbl[1]->coords, 20);
        HuPrcSleep(20);
        MBDVecDirGet(&opduel_partnerMdlTbl[0]->coords, &opduel_playerTbl[1]->player_obj->coords,
                              &directions[0]);
        MBDVecDirGet(&opduel_partnerMdlTbl[1]->coords, &opduel_playerTbl[0]->player_obj->coords,
                              &directions[1]);
        MBDVecRotLerpCreate(&opduel_partnerMdlTbl[0]->rot, &directions[0], &opduel_partnerMdlTbl[0]->rot, 10);
        MBDVecRotLerpCreate(&opduel_partnerMdlTbl[1]->rot, &directions[1], &opduel_partnerMdlTbl[1]->rot, 10);
        HuPrcSleep(10);
        MBDMotionSet(opduel_partnerMdlTbl[0], -1, 2);
        MBDMotionSet(opduel_partnerMdlTbl[1], -1, 2);
        MBDPartnerSet(0, mbdCharPartnerTbl[GwPlayer[0].chr], choices[0] - 1);
        MBDStatusCostUpdateSet(0);
        if (choices[0] == 1) {
            MBDStatusFrontUpdate(0);
            MBDStatusPartnerPosSet(0, 0, 28, 0);
        } else {
            MBDStatusBackUpdate(0);
            MBDStatusPartnerPosSet(0, 0, -28, 1);
        }
        MBDPartnerSet(1, mbdCharPartnerTbl[GwPlayer[1].chr], choices[1] - 1);
        if (choices[1] == 1) {
            MBDStatusFrontUpdate(1);
            MBDStatusPartnerPosSet(1, 0, 28, 0);
        } else {
            MBDStatusBackUpdate(1);
            MBDStatusPartnerPosSet(1, 0, -28, 1);
        }
        for (i = 28; i >= 0; i--) {
            if (choices[0] == 1) {
                MBDStatusPartnerPosSet(0, 0, i, 0);
            } else {
                MBDStatusPartnerPosSet(0, 0, -i, 1);
            }
            if (choices[1] == 1) {
                MBDStatusPartnerPosSet(1, 0, i, 0);
            } else {
                MBDStatusPartnerPosSet(1, 0, -i, 1);
            }
            HuPrcVSleep();
        }
    }
    MBDStatusCostUpdateSet(1);
    MBDMotionShiftSet(opduel_centerMdl, 0, 0, 5, 2);
    MBDDlgWinExecAllKey(-1, 0x2710);
    MBDMotionShiftSet(opduel_centerMdl, -1, 0, 5, 2);
    MBDCoinTakeCreateSound(0, 10, 1);
    MBDCoinTakeCreateSound(1, 10, 0);
    MBDVecForwardSet(&opduel_playerTbl[0]->player_obj->rot);
    MBDVecForwardSet(&opduel_playerTbl[1]->player_obj->rot);
    MBDMotionSet(opduel_playerTbl[0]->player_obj, 4, 0);
    MBDMotionSet(opduel_playerTbl[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    MBDMotionShiftSet(opduel_playerTbl[0]->player_obj, 0, 0, 5, 2);
    MBDMotionShiftSet(opduel_playerTbl[1]->player_obj, 0, 0, 5, 2);
    MBDMotionShiftSet(opduel_centerMdl, 0, 0, 5, 2);
    MBDDlgWinExecAllKey(-1, 0x2711);
    MBDMotionShiftSet(opduel_centerMdl, -1, 0, 5, 2);
}

void opduel_MainProc(void) {
    opduel_arriveProc = omAddPrcObj(opduel_ArriveProc, 0x300, 0x2000, 0);
    HuPrcChildLink(HuPrcCurrentGet(), opduel_arriveProc);
    HuPrcChildWatch();
    opduel_StarTalkExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void opduel_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        opduel_BackClose();
        opduel_SysClose();
        HuWinAllKill();
        if (opduel_statusCreateF != 0) {
            MBDStatusKill();
        }
        omOvlReturnEx(1);
    }
}

void opduel_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(WIPE_STARS, 20);
        HuAudSeqFadeOut(60);
        obj->func = opduel_ExitObjMain;
    }
}

void opduel_SysInit(void) {
    MBDModelInit();
    MBDPlayerMotInit();
}

void opduel_SysClose(void) {
    MBDPlayerClose();
    MBDModelClose();
    if (opduel_unusedProc != NULL) {
        omDelPrcObj(opduel_unusedProc);
    }
}

void opduel_BackInit(void) {
    s32 sp10[] = { 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };

    Hu3DCamInit(1);
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackLoad(sp10[GwSystem.current_board_index]);
}

void opduel_BackClose(void) {
    MBDBackKill();
    MBDBackClose();
}
