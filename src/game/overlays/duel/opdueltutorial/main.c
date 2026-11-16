#include "common_duel.h"
#include "macros.h"
#include "game/overlays/duel/common/ovl_81.h"

extern u8 mbdCharPartnerTbl[];

void MBDPlayerModelCreate(s16, u32 *, s16);
void MBDVecForwardSet(Vec *);
Process *MBDVecRotLerpCreate(Vec *, Vec *, Vec *, s32);
Process *MBDPlayerPosMoveCreate(Vec *, Vec *, Vec *, s32);
void MBDWinComKeyAnyWait(s16);
s32 MBDModelTargetMoveRot(Object *, Vec *, f32);
void MBDStatusPosSet(s32, s16, s16);
void MBDCoinTakeCreateSound(s32, s32, s32);
void MBDStatusScaleSet(s32, f32, f32);
void MBDStatusPartnerPosSet(s32, s32, s16, s32);
void MBDStatusCostUpdateSet(s32);
void MBDStatusBounceExec(s32);
void MBDPartnerSet(s32, s32, s32);

void opdueltutorial_SpiralEffHook(s16 model);
void opdueltutorial_ArriveExec(void);
void opdueltutorial_StarTalkExec(void);
void opdueltutorial_MainProc(void);
void opdueltutorial_ExitObjMain(omObjData *obj);
void opdueltutorial_ExitCheckObjMain(omObjData *obj);
void opdueltutorial_SysClose(void);
void opdueltutorial_BackClose(void);
void opdueltutorial_SysInit(void);
void opdueltutorial_BackInit(void);

s32 opdueltutorial_statusCreateF = 0;
Process *opdueltutorial_unusedProc = NULL;

Vec opdueltutorial_guidePos = { -170.0f, 125.0f, 3000.0f };

Vec opdueltutorial_platformPos = { 0.0f, 250.0f, 0.0f };

/* Unreferenced. */
Vec opdueltutorial_unusedPosTbl[2] = {
    { 0.0f, 100.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};

Vec opdueltutorial_starPos = { 0.0f, 0.0f, 1500.0f };

Vec opdueltutorial_playerStartPosTbl[4] = {
    { -10.0f, 250.0f, 0.0f },
    { 10.0f, 250.0f, 0.0f },
    { -500.0f, 0.0f, 2360.0f },
    { 500.0f, 0.0f, 2360.0f }
};

Vec opdueltutorial_playerFarPosTbl[2] = {
    { -200.0f, 0.0f, 2360.0f },
    { 200.0f, 0.0f, 2360.0f }
};

Vec opdueltutorial_playerNearPosTbl[4] = {
    { -175.0f, 0.0f, 2250.0f },
    { 175.0f, 0.0f, 2250.0f },
    { 0.0f, 0.0f, 2150.0f },
    { 0.0f, 0.0f, 2350.0f }
};

Vec opdueltutorial_playerPosTbl[2] = {
    { -125.0f, 0.0f, 2000.0f },
    { 125.0f, 0.0f, 2000.0f }
};

Vec opdueltutorial_partnerStartPosTbl[2] = {
    { -750.0f, 0.0f, 1750.0f },
    { 750.0f, 0.0f, 1750.0f }
};

Vec opdueltutorial_partnerPosTbl[2] = {
    { -100.0f, 0.0f, 1750.0f },
    { 100.0f, 0.0f, 1750.0f }
};

Vec opdueltutorial_partnerSlotPosTbl[4] = {
    { -100.0f, 0.0f, 2000.0f },
    { 100.0f, 0.0f, 2000.0f },
    { -300.0f, 0.0f, 2000.0f },
    { 300.0f, 0.0f, 2000.0f }
};

u32 opdueltutorial_playerMotMario[6] = { 5, 0x20000, 0x20001, 0x20002, 0x20033, 0x20031 };

u32 opdueltutorial_playerMotLuigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotPeach[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotYoshi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotWario[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotDk[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotWaluigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opdueltutorial_playerMotDaisy[6] = { 5, 0, 0, 0, 0, 0 };

u32 *opdueltutorial_playerMotTbl[8] = { opdueltutorial_playerMotMario, opdueltutorial_playerMotLuigi, opdueltutorial_playerMotPeach, opdueltutorial_playerMotYoshi, opdueltutorial_playerMotWario, opdueltutorial_playerMotDk, opdueltutorial_playerMotWaluigi, opdueltutorial_playerMotDaisy };

s32 opdueltutorial_partnerMotMario[2] = { 1, 0xA0090 };

s32 opdueltutorial_partnerMotLuigi[2] = { 1, 0xA00A7 };

s32 opdueltutorial_partnerMotPeach[2] = { 1, 0xA0002 };

s32 opdueltutorial_partnerMotWario[2] = { 1, 0xA00BD };

s32 opdueltutorial_partnerMotDk[2] = { 1, 0xA00D0 };

s32 opdueltutorial_partnerMotWaluigi[2] = { 1, 0xA010F };

s32 *opdueltutorial_partnerMotTbl[8] = { opdueltutorial_partnerMotMario, opdueltutorial_partnerMotLuigi, opdueltutorial_partnerMotPeach, NULL, opdueltutorial_partnerMotWario, opdueltutorial_partnerMotDk, opdueltutorial_partnerMotWaluigi, NULL };

s32 opdueltutorial_starMot[2] = { 1, 0xA0125 };

u8 opdueltutorial_boardNo BSS;
GW_PLAYER *opdueltutorial_playerTbl[2] BSS;
Object *opdueltutorial_centerMdl BSS;
Object *opdueltutorial_partnerMdlTbl[2] BSS;
Object *opdueltutorial_guideMdl BSS;
s16 opdueltutorial_guideWin BSS;
s16 opdueltutorial_guideAnimTbl[10] BSS;
s16 opdueltutorial_guideAnim BSS;
s16 opdueltutorial_guideAnimLink BSS;

void opdueltutorial_ObjectSetup(void) {
    GW_PLAYER *player;
    s32 i;
    s32 j;

    opdueltutorial_boardNo = GwSystem.current_board_index = 6;
    omInitObjMan(50, 20);
    Hu3DGLightColorSet(1, 255, 255, 255);
    Hu3DGLightColorSet(2, 200, 200, 200);
    opdueltutorial_BackInit();
    opdueltutorial_SysInit();
    MBDShadowHeightMaxSet(700.0f);
    MBDModelScaleMulSet(1.6f);
    HuWinInit();
    omAddPrcObj(opdueltutorial_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, opdueltutorial_ExitCheckObjMain);
    for (j = 0; j < 2; j++) {
        player = MBDGetPlayerStruct(j);
        player->stats.partners.frontID = -1;
        player->stats.partners.backID = -1;
    }
    for (i = 1; i < 8; i++) {
        for (j = 0; j < opdueltutorial_playerMotMario[0]; j++) {
            opdueltutorial_playerMotTbl[i][j + 1] = CharMotionDataNumGet(i, opdueltutorial_playerMotMario[j + 1]);
        }
    }
    GwPlayer[0].stat = 1;
    GwPlayer[1].stat = 1;
    GwPlayer[0].chr = 0;
    GwPlayer[1].chr = 1;
    omGameSysInit();
}

s16 opdueltutorial_SpiralEffCreate(s32 file, s32 flags) {
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
    Hu3DParticleCreate(model, -1, 0, opdueltutorial_SpiralEffHook);
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

s32 opdueltutorial_SpiralEffAdd(s16 model, f32 x, f32 y, f32 z) {
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

void opdueltutorial_SpiralEffHook(s16 model) {
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

s16 opdueltutorial_ModelAnimCreate(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    s16 animIdx;

    data = DataRead(file);
    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    opdueltutorial_guideAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    opdueltutorial_guideAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void opdueltutorial_ModelAnimSet(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (opdueltutorial_guideAnimLink != 255) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[opdueltutorial_guideAnimLink];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 opdueltutorial_AnimDataRead(s32 file) {
    void *data = DataRead(file);
    s16 id = Hu3DAnimDataCreate(data);

    DataClose(data);
    return id;
}

void opdueltutorial_CenterBobObjMain(omObjData *obj) {
    s32 i;

    opdueltutorial_centerMdl->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 2; i++) {
        opdueltutorial_playerTbl[i]->player_obj->coords.y = opdueltutorial_centerMdl->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void opdueltutorial_ArriveExec(void) {
    Object *shadow;
    omObjData *obj;
    s16 effect;
    s32 i;
    f32 scale;

    for (i = 0; i < 2; i++) {
        opdueltutorial_playerTbl[i] = MBDGetPlayerStruct(i);
        MBDPlayerModelCreate(i, opdueltutorial_playerMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&opdueltutorial_playerTbl[i]->player_obj->coords, &opdueltutorial_playerStartPosTbl[i]);
        MBDModelTempAllocFree(opdueltutorial_playerTbl[i]->player_obj);
        opdueltutorial_playerTbl[i]->stat |= PLAYER_UNK_04;
    }
    opdueltutorial_centerMdl = MBDModelFileCreate(0x1301FF, -1, 1.0f, 0, 0);
    HuVecCopyXYZ(&opdueltutorial_centerMdl->scale, 0.625f, 0.625f, 0.625f);
    shadow = MBDModelFileCreate(0x1301FD, -1, 1.0f, 0, 0);
    HuVecCopy3F(&opdueltutorial_centerMdl->coords, &opdueltutorial_platformPos);
    HuVecCopy3F(&shadow->coords, &opdueltutorial_platformPos);
    shadow->coords.y = 0;
    HuVecCopyXYZ(&shadow->scale, shadow->coords.y, shadow->coords.y, shadow->coords.y);
    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(effect, 40.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    WipeCreateIn(2, 16);
    HuPrcSleep(17);
    HuAudFXPlay(0x2ED);
    while (opdueltutorial_centerMdl->coords.y >= 10.0f) {
        opdueltutorial_centerMdl->coords.y -= 3.0f;
        for (i = 0; i < 2; i++) {
            opdueltutorial_playerTbl[i]->player_obj->coords.y -= 3.0f;
        }
        HuVecCopyXYZ(&shadow->scale,
                     0.625f - opdueltutorial_centerMdl->coords.y * 0.625f / 250.0f,
                     0.625f - opdueltutorial_centerMdl->coords.y * 0.625f / 250.0f,
                     0.625f - opdueltutorial_centerMdl->coords.y * 0.625f / 250.0f);
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, opdueltutorial_CenterBobObjMain);
    obj->rot.x = 180.0f;
    obj->rot.y = 5.0f;
    obj->rot.z = opdueltutorial_centerMdl->coords.y;
    HuPrcSleep(30);
    EffectPosSet(effect, opdueltutorial_centerMdl->coords.x,
                       opdueltutorial_centerMdl->coords.y + 40.0f, opdueltutorial_centerMdl->coords.z);
    Hu3DParticleAttrSet(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 2; i++) {
            HuVecCopyXYZ(&opdueltutorial_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        MBDModelDispOff(opdueltutorial_playerTbl[i]->player_obj);
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&opdueltutorial_centerMdl->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    EffectStop(effect);
    MBDModelKill(opdueltutorial_centerMdl);
    MBDModelKill(shadow);
    omDelObj(obj);
}

void opdueltutorial_CenterHoverObjMain(omObjData *obj) {
    opdueltutorial_centerMdl->velocity.x = obj->trans.y - sindf(obj->rot.y) * 10.0f;
    obj->rot.y += 5.0f;
}

void opdueltutorial_AnimMdlProc(void) {
    Object *obj;
    void *data[2];
    s32 anim;
    s32 alpha;

    obj = MBDModelFileCreate(0x14000A, -1, 1.0f, 0, 0);
    Hu3DModelTPLvlInit(obj->omObj1->model[0]);
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 255);
    data[0] = DataRead(0x130135);
    Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    data[1] = DataRead(0x140034);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 4, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuVecCopyXYZ(&obj->coords, 0, 150.0f, 500.0f);
    HuPrcSleep(15);
    Hu3DAnimModelKill(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 3, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    Hu3DAnimModelKill(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 2, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    Hu3DAnimModelKill(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 1, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    Hu3DAnimModelKill(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[1], 0, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(15);
    Hu3DAnimModelKill(anim);
    anim = (s16)Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data[0], 0, "sitagocoro_DEF");
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuPrcSleep(5);
    for (alpha = 255; alpha > 0; alpha -= 10) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], alpha);
        HuPrcVSleep();
    }
    Hu3DAnimModelKill(anim);
    DataClose(data[0]);
    DataClose(data[1]);
    MBDModelKill(obj);
    omDelPrcObj(NULL);
}

void opdueltutorial_StarTalkExec(void) {
    Vec directions[2];
    s16 effects[2];
    omObjData *obj;
    s32 i;
    s32 j;
    s16 effect;
    f32 scale;
    f32 angle;
    f32 radius;
    f32 speed;

    MBDBackKill();
    MBDBackLoad(23);
    MBDCameraNearFarSet(1000.0f, 10000.0f);
    opdueltutorial_guideMdl = MBDModelCreate(62, NULL);
    HuVecCopy3F(&opdueltutorial_guideMdl->coords, &opdueltutorial_guidePos);
    HuVecCopyXYZ(&opdueltutorial_guideMdl->scale, 0.6f, 0.6f, 0.6f);
    opdueltutorial_guideMdl->rot.x = sindf(10.0f);
    opdueltutorial_guideMdl->rot.z = cosdf(10.0f);
    opdueltutorial_guideMdl->flags |= 1;
    opdueltutorial_guideWin = HuWinExCreateStyled(75, 197, 16);
    HuWinMesPalSet(opdueltutorial_guideWin, 4, 0, 224, 224);
    HuWinMesSpeedSet(opdueltutorial_guideWin, 0);
    opdueltutorial_guideAnimTbl[0] =
        opdueltutorial_ModelAnimCreate(opdueltutorial_guideMdl->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    opdueltutorial_guideAnimTbl[1] = opdueltutorial_AnimDataRead(0xA007F);
    opdueltutorial_guideAnimTbl[2] = opdueltutorial_AnimDataRead(0xA0080);
    opdueltutorial_guideAnimTbl[3] = opdueltutorial_AnimDataRead(0xA0081);
    opdueltutorial_guideAnimTbl[4] = opdueltutorial_AnimDataRead(0xA0082);
    opdueltutorial_guideAnimTbl[5] = opdueltutorial_AnimDataRead(0xA0083);
    opdueltutorial_guideAnimTbl[6] = opdueltutorial_AnimDataRead(0xA0084);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[0]);
    opdueltutorial_centerMdl = MBDModelCreate(59, opdueltutorial_starMot);
    AuraCreate(opdueltutorial_centerMdl->omObj1->model[0]);
    HuVecCopy3F(&opdueltutorial_centerMdl->coords, &opdueltutorial_starPos);
    opdueltutorial_centerMdl->velocity.x = 900.0f;
    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 15.0f, 20.0f, 8.0f);
    EffectRangeSet(effect, 200.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuVecCopy3F(&opdueltutorial_playerTbl[i]->player_obj->coords, &opdueltutorial_playerPosTbl[i]);
        effects[i] = opdueltutorial_SpiralEffCreate(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (j = 0; j < 20; j++) {
        for (i = 0; i < 2; i++) {
            opdueltutorial_SpiralEffAdd(effects[i], opdueltutorial_playerTbl[i]->player_obj->coords.x,
                                         opdueltutorial_playerTbl[i]->player_obj->coords.y + 50.0f,
                                         opdueltutorial_playerTbl[i]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (i = 0; i < 2; i++) {
            MBDModelDispOn(opdueltutorial_playerTbl[i]->player_obj);
            HuVecCopyXYZ(&opdueltutorial_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 2; i++) {
        HuVecCopyXYZ(&opdueltutorial_playerTbl[i]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(11);
    HuWinMesSet(opdueltutorial_guideWin, 0x2500, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    j = 0;
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(opdueltutorial_AnimMdlProc, 0x300, 0, 0));
    HuWinMesSet(opdueltutorial_guideWin, 0x2501, -1, -1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    HuPrcChildWatch();
    HuWinMesSet(opdueltutorial_guideWin, 0x2502, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[1]);
    HuAudFXPlay(0x2DD);
    Hu3DParticleAttrSet(effect, 0, 1);
    angle = 0.0f;
    radius = 500.0f;
    while (opdueltutorial_centerMdl->velocity.x >= 300.0f) {
        opdueltutorial_centerMdl->coords.x = sindf(angle) * radius;
        opdueltutorial_centerMdl->coords.z = cosdf(angle) * radius + opdueltutorial_starPos.z;
        opdueltutorial_centerMdl->velocity.x -= 5.0f;
        angle += 6.0;
        radius -= 4.1666665f;
        if (radius < 0.0f) {
            radius = 0.0f;
        }
        EffectPosSet(effect, opdueltutorial_centerMdl->coords.x, opdueltutorial_centerMdl->velocity.x - 50.0f,
                           opdueltutorial_centerMdl->coords.z);
        j++;
        if (j == 40) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&opdueltutorial_playerTbl[i]->player_obj->coords,
                                      &opdueltutorial_playerFarPosTbl[i],
                                      &opdueltutorial_playerTbl[i]->player_obj->rot);
                MBDPlayerPosMoveCreate(&opdueltutorial_playerTbl[i]->player_obj->coords,
                                      &opdueltutorial_playerFarPosTbl[i],
                                      &opdueltutorial_playerTbl[i]->player_obj->coords, 20);
                MBDMotionSet(opdueltutorial_playerTbl[i]->player_obj, 2, 2);
            }
        }
        if (j == 60) {
            for (i = 0; i < 2; i++) {
                MBDVecDirGet(&opdueltutorial_playerTbl[i]->player_obj->coords,
                                      &opdueltutorial_starPos, &directions[i]);
                MBDVecRotLerpCreate(&opdueltutorial_playerTbl[i]->player_obj->rot, &directions[i],
                                      &opdueltutorial_playerTbl[i]->player_obj->rot, 10);
                MBDMotionShiftSet(opdueltutorial_playerTbl[i]->player_obj, -1, 0, 5, 2);
            }
        }
        HuPrcVSleep();
    }
    obj = omAddObj(0x1000, 0, 0, -1, opdueltutorial_CenterHoverObjMain);
    obj->trans.y = opdueltutorial_centerMdl->velocity.x;
    Hu3DParticleAttrSet(effect, 1, 0);
    for (i = 0; i < 2; i++) {
        HuPrcChildLink(HuPrcCurrentGet(), MBDPlayerPosMoveCreate(&opdueltutorial_playerTbl[i]->player_obj->coords,
                                                                &opdueltutorial_playerNearPosTbl[i],
                                                                &opdueltutorial_playerTbl[i]->player_obj->coords, 20));
        MBDMotionSet(opdueltutorial_playerTbl[i]->player_obj, 2, 2);
    }
    HuPrcChildWatch();
    for (i = 0; i < 2; i++) {
        MBDMotionShiftSet(opdueltutorial_playerTbl[i]->player_obj, -1, 0, 5, 2);
    }
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[0]);
    HuWinMesSet(opdueltutorial_guideWin, 0x2503, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    Hu3DParticleAttrSet(effect, 0, 1);
    for (angle = 0.0f; angle <= 360.0f; angle += 20.0f) {
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    MBDVecForwardSet(&directions[0]);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[0]->player_obj->rot, &directions[0],
                          &opdueltutorial_playerTbl[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    HuWinMesSet(opdueltutorial_guideWin, 0x2504, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDVecDirGet(&opdueltutorial_playerTbl[0]->player_obj->coords, &opdueltutorial_centerMdl->coords,
                          &directions[0]);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[0]->player_obj->rot, &directions[0],
                          &opdueltutorial_playerTbl[0]->player_obj->rot, 10);
    HuPrcSleep(10);
    Hu3DParticleAttrSet(effect, 0, 1);
    for (angle = 0.0f; angle <= 180.0f; angle += 20.0f) {
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    MBDVecForwardSet(&directions[1]);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[1]->player_obj->rot, &directions[1],
                          &opdueltutorial_playerTbl[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    HuWinMesSet(opdueltutorial_guideWin, 0x2505, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDVecDirGet(&opdueltutorial_playerTbl[1]->player_obj->coords, &opdueltutorial_centerMdl->coords,
                          &directions[1]);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[1]->player_obj->rot, &directions[1],
                          &opdueltutorial_playerTbl[1]->player_obj->rot, 10);
    HuPrcSleep(10);
    Hu3DParticleAttrSet(effect, 0, 1);
    for (; angle <= 360.0f; angle += 30.0f) {
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    opdueltutorial_centerMdl->rot.x = sindf(0.0f);
    opdueltutorial_centerMdl->rot.z = cosdf(0.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    HuWinMesSet(opdueltutorial_guideWin, 0x2506, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    j = 0;
    HuWinExClose(opdueltutorial_guideWin, 1);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[5]);
    HuAudFXPlay(0x2DE);
    Hu3DParticleAttrSet(effect, 0, 1);
    for (speed = 0.0f; speed <= 30.0f; speed += 1.0f) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    speed = 30.0f;
    for (i = 0; i < 30; i++) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    while (TRUE) {
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
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
        opdueltutorial_centerMdl->rot.x = sindf(angle);
        opdueltutorial_centerMdl->rot.z = cosdf(angle);
        HuPrcVSleep();
    }
    angle = 0.0f;
    opdueltutorial_centerMdl->rot.x = sindf(angle);
    opdueltutorial_centerMdl->rot.z = cosdf(angle);
    Hu3DParticleAttrSet(effect, 1, 0);
    HuPrcSleep(20);
    HuWinMesSet(opdueltutorial_guideWin, 0x2507, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[6]);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[0]);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDVecForwardSet(&opdueltutorial_playerTbl[0]->player_obj->rot);
    MBDMotionSet(opdueltutorial_playerTbl[0]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 0);
    MBDStatusCreate();
    {
        s16 positions[][2] = { { 30, 40 }, { 194, 40 } };

        MBDStatusPosSet(0, positions[0][0], positions[0][1]);
        MBDStatusPosSet(1, positions[1][0], positions[1][1]);
    }
    MBDStatusScaleSet(0, 0.0f, 0.0f);
    MBDStatusScaleSet(1, 0.0f, 0.0f);
    opdueltutorial_statusCreateF = 1;
    MBDStatusBounceExec(0);
    MBDModelMotionWait(opdueltutorial_playerTbl[0]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet(opdueltutorial_playerTbl[0]->player_obj, 0, 2);
    HuWinMesSet(opdueltutorial_guideWin, 0x2508, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[3]);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[0]);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDVecForwardSet(&opdueltutorial_playerTbl[1]->player_obj->rot);
    MBDMotionSet(opdueltutorial_playerTbl[1]->player_obj, 3, 0);
    PlayerFXPlay(0x274, 1);
    MBDStatusBounceExec(1);
    MBDModelMotionWait(opdueltutorial_playerTbl[1]->player_obj);
    HuPrcSleep(10);
    MBDMotionSet(opdueltutorial_playerTbl[1]->player_obj, 0, 2);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[6]);
    HuAudFXPlay(0x2E3);
    omDelObj(obj);
    Hu3DParticleAttrSet(effect, 0, 1);
    while (opdueltutorial_centerMdl->velocity.x < 800.0f) {
        opdueltutorial_centerMdl->velocity.x += 10.0f;
        EffectPosSet(effect, opdueltutorial_centerMdl->coords.x, opdueltutorial_centerMdl->velocity.x - 50.0f,
                           opdueltutorial_centerMdl->coords.z);
        HuPrcVSleep();
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    opdueltutorial_ModelAnimSet(opdueltutorial_guideMdl->omObj1->model[0], opdueltutorial_guideAnimTbl[0]);
    HuPrcSleep(10);
    {
        s32 models[] = { 0x25, 0x0C, 0x09, 0x0A, 0x26, 0x0B, 0x2C, 0x24 };
        s32 sounds[] = { 0x25A, 0x25B, 0x298, 0x257, 0x256, 0x25D, 0x2A4, 0x2A3 };

        for (i = 0; i < 2; i++) {
            opdueltutorial_partnerMdlTbl[i] =
                MBDModelCreate(models[GwPlayer[i].chr], opdueltutorial_partnerMotTbl[GwPlayer[i].chr]);
            HuVecCopy3F(&opdueltutorial_partnerMdlTbl[i]->coords, &opdueltutorial_partnerStartPosTbl[i]);
            HuAudFXPlay(sounds[GwPlayer[i].chr]);
        }
    }
    MBDMotionSet(opdueltutorial_partnerMdlTbl[0], 0, 2);
    MBDMotionSet(opdueltutorial_partnerMdlTbl[1], 0, 2);
    while (TRUE) {
        j = MBDModelTargetMoveRot(opdueltutorial_partnerMdlTbl[0], &opdueltutorial_partnerPosTbl[0], 20.0f);
        if (MBDModelTargetMoveRot(opdueltutorial_partnerMdlTbl[1], &opdueltutorial_partnerPosTbl[1], 20.0f) && j) {
            break;
        }
        HuPrcVSleep();
    }
    MBDVecForwardSet(&directions[0]);
    MBDVecForwardSet(&directions[1]);
    MBDVecRotLerpCreate(&opdueltutorial_partnerMdlTbl[0]->rot, &directions[0], &opdueltutorial_partnerMdlTbl[0]->rot, 10);
    MBDVecRotLerpCreate(&opdueltutorial_partnerMdlTbl[1]->rot, &directions[1], &opdueltutorial_partnerMdlTbl[1]->rot, 10);
    HuPrcSleep(10);
    MBDMotionSet(opdueltutorial_partnerMdlTbl[0], -1, 2);
    MBDMotionSet(opdueltutorial_partnerMdlTbl[1], -1, 2);
    HuWinMesSet(opdueltutorial_guideWin, 0x2509, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDVecDirGet(&opdueltutorial_playerTbl[0]->player_obj->coords,
                          &opdueltutorial_playerTbl[1]->player_obj->coords, &directions[0]);
    MBDVecDirGet(&opdueltutorial_playerTbl[1]->player_obj->coords,
                          &opdueltutorial_playerTbl[0]->player_obj->coords, &directions[1]);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[0]->player_obj->rot, &directions[0],
                          &opdueltutorial_playerTbl[0]->player_obj->rot, 5);
    MBDVecRotLerpCreate(&opdueltutorial_playerTbl[1]->player_obj->rot, &directions[1],
                          &opdueltutorial_playerTbl[1]->player_obj->rot, 5);
    HuPrcSleep(5);
    HuWinMesSet(opdueltutorial_guideWin, 0x250A, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    {
        s32 choices[2];
        DuelHelpWin *window1;
        DuelHelpWin *window2;

        choices[0] = 0;
        choices[1] = 0;
        window1 = MBDHelpWinCreate(20, 174, 1);
        window2 = MBDHelpWinCreate(21, 188, 1);
        HuPrcSleep(20);
        choices[0] = 1;
        choices[1] = 2;
        MBDHelpWinKill(window1);
        MBDHelpWinKill(window2);
        MBDMotionSet(opdueltutorial_partnerMdlTbl[0], 0, 2);
        MBDMotionSet(opdueltutorial_partnerMdlTbl[1], 0, 2);
        MBDVecDirGet(&opdueltutorial_partnerMdlTbl[0]->coords, &opdueltutorial_partnerSlotPosTbl[(choices[0] - 1) * 2],
                              &opdueltutorial_partnerMdlTbl[0]->rot);
        MBDVecDirGet(&opdueltutorial_partnerMdlTbl[1]->coords,
                              &opdueltutorial_partnerSlotPosTbl[(choices[1] - 1) * 2 + 1], &opdueltutorial_partnerMdlTbl[1]->rot);
        MBDPlayerPosMoveCreate(&opdueltutorial_partnerMdlTbl[0]->coords, &opdueltutorial_partnerSlotPosTbl[(choices[0] - 1) * 2],
                              &opdueltutorial_partnerMdlTbl[0]->coords, 20);
        MBDPlayerPosMoveCreate(&opdueltutorial_partnerMdlTbl[1]->coords,
                              &opdueltutorial_partnerSlotPosTbl[(choices[1] - 1) * 2 + 1],
                              &opdueltutorial_partnerMdlTbl[1]->coords, 20);
        HuPrcSleep(20);
        MBDVecDirGet(&opdueltutorial_partnerMdlTbl[0]->coords, &opdueltutorial_playerTbl[1]->player_obj->coords,
                              &directions[0]);
        MBDVecDirGet(&opdueltutorial_partnerMdlTbl[1]->coords, &opdueltutorial_playerTbl[0]->player_obj->coords,
                              &directions[1]);
        MBDVecRotLerpCreate(&opdueltutorial_partnerMdlTbl[0]->rot, &directions[0], &opdueltutorial_partnerMdlTbl[0]->rot,
                              10);
        MBDVecRotLerpCreate(&opdueltutorial_partnerMdlTbl[1]->rot, &directions[1], &opdueltutorial_partnerMdlTbl[1]->rot,
                              10);
        HuPrcSleep(10);
        MBDMotionSet(opdueltutorial_partnerMdlTbl[0], -1, 2);
        MBDMotionSet(opdueltutorial_partnerMdlTbl[1], -1, 2);
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
    HuWinMesSet(opdueltutorial_guideWin, 0x250B, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    MBDCoinTakeCreateSound(0, 10, 1);
    MBDCoinTakeCreateSound(1, 10, 0);
    MBDVecForwardSet(&opdueltutorial_playerTbl[0]->player_obj->rot);
    MBDVecForwardSet(&opdueltutorial_playerTbl[1]->player_obj->rot);
    MBDMotionSet(opdueltutorial_playerTbl[0]->player_obj, 4, 0);
    MBDMotionSet(opdueltutorial_playerTbl[1]->player_obj, 4, 0);
    HuPrcSleep(60);
    MBDMotionShiftSet(opdueltutorial_playerTbl[0]->player_obj, 0, 0, 5, 2);
    MBDMotionShiftSet(opdueltutorial_playerTbl[1]->player_obj, 0, 0, 5, 2);
    HuWinMesSet(opdueltutorial_guideWin, 0x250C, -1, -1);
    HuWinExOpen(opdueltutorial_guideWin, 1);
    MBDWinComKeyAnyWait(opdueltutorial_guideWin);
    HuWinExClose(opdueltutorial_guideWin, 1);
    HuWinExCleanup(opdueltutorial_guideWin);
}

void opdueltutorial_MainProc(void) {
    opdueltutorial_ArriveExec();
    opdueltutorial_StarTalkExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void opdueltutorial_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        opdueltutorial_BackClose();
        opdueltutorial_SysClose();
        HuWinAllKill();
        if (opdueltutorial_statusCreateF != 0) {
            MBDStatusKill();
        }
        omOvlReturnEx(1);
    }
}

void opdueltutorial_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(2, 20);
        obj->func = opdueltutorial_ExitObjMain;
    }
}

void opdueltutorial_SysInit(void) {
    MBDModelInit();
    MBDPlayerMotInit();
    MBDSprGrpInit();
}

void opdueltutorial_SysClose(void) {
    MBDPlayerClose();
    MBDModelClose();
    MBDSprGrpClose();
    if (opdueltutorial_unusedProc != NULL) {
        omDelPrcObj(opdueltutorial_unusedProc);
    }
}

void opdueltutorial_BackInit(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    MBDBackArcInit(hvq_data_ROM_START);
    MBDBackLoad(30);
}

void opdueltutorial_BackClose() {
    MBDBackKill();
    MBDBackClose();
}
