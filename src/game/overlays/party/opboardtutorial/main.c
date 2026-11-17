#include "common_board.h"
#include "game/malloc.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/helpwin.h"

extern s32 mbSaiSeF;

s32 opboardtutorial_statusCreateF = 0;

Vec opboardtutorial_guidePos = { -170.0f, 125.0f, 3000.0f };

Vec opboardtutorial_platformPos = { 0.0f, 250.0f, 0.0f };

/* Unreferenced. */
Vec opboardtutorial_unusedPosTbl[2] = {
    { 0.0f, 100.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};

Vec opboardtutorial_starPos = { 0.0f, 0.0f, 1750.0f };

Vec opboardtutorial_playerStartPosTbl[4] = {
    { -18.0f, 250.0f, 0.0f },
    { -6.0f, 250.0f, 0.0f },
    { 6.0f, 250.0f, 0.0f },
    { 18.0f, 250.0f, 0.0f }
};

Vec opboardtutorial_playerPosTbl[4] = {
    { -175.0f, 0.0f, 2000.0f },
    { 0.0f, 0.0f, 2000.0f },
    { 175.0f, 0.0f, 2000.0f },
    { 350.0f, 0.0f, 2000.0f }
};

u32 opboardtutorial_playerMotMario[6] = { 5, 0x20001, 0x20002, 0x2002B, 0x20033, 0x20031 };

u32 opboardtutorial_playerMotLuigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotPeach[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotYoshi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotWario[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotDk[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotWaluigi[6] = { 5, 0, 0, 0, 0, 0 };

u32 opboardtutorial_playerMotDaisy[6] = { 5, 0, 0, 0, 0, 0 };

u32 *opboardtutorial_playerMotTbl[8] = { opboardtutorial_playerMotMario, opboardtutorial_playerMotLuigi, opboardtutorial_playerMotPeach, opboardtutorial_playerMotYoshi, opboardtutorial_playerMotWario, opboardtutorial_playerMotDk, opboardtutorial_playerMotWaluigi, opboardtutorial_playerMotDaisy };

u8 opboardtutorial_boardNo BSS;
Object *opboardtutorial_guideMdl BSS;
s16 opboardtutorial_guideWin BSS;
u8 opboardtutorial_guideWinPad[4] BSS; /* Unreferenced. */
s16 opboardtutorial_guideAnimTbl[10] BSS;
s16 opboardtutorial_guideAnim BSS;
s16 opboardtutorial_guideAnimLink BSS;
GW_PLAYER *opboardtutorial_playerTbl[4] BSS;
Object *opboardtutorial_centerMdl BSS;

void MBSaiOrderModeSet(void);
void MBSaiValueForceSet(s32 player, s32 value);
void MBWinComKeyAnyWait(s32 window);
void opboardtutorial_SpiralEffHook(s16 model);
void opboardtutorial_MainProc(void);
void opboardtutorial_ExitCheckObjMain(omObjData *obj);
void opboardtutorial_SysInit(void);
void opboardtutorial_BackInit(void);
void opboardtutorial_ExitObjMain(omObjData *obj);
void opboardtutorial_SysClose(void);
void opboardtutorial_BackClose(void);

void opboardtutorial_ObjectSetup(void) {
    s32 i;
    u32 j;

    opboardtutorial_boardNo = GwSystem.current_board_index;
    omInitObjMan(50, 50);
    opboardtutorial_BackInit();
    opboardtutorial_SysInit();
    MBShadowHeightMaxSet(1000.0f);
    HuWinInit();
    omAddPrcObj(opboardtutorial_MainProc, 0x300, 0x2000, 0);
    omAddObj(0x1000, 0, 0, -1, opboardtutorial_ExitCheckObjMain);
    for (i = 1; i < 8; i++) {
        for (j = 0; j < opboardtutorial_playerMotMario[0]; j++) {
            opboardtutorial_playerMotTbl[i][j + 1] = CharMotionDataNumGet(i, opboardtutorial_playerMotMario[j + 1]);
        }
    }
    GwPlayer[0].chr = 3;
    GwPlayer[1].chr = 2;
    GwPlayer[2].chr = 0;
    GwPlayer[3].chr = 4;
    omGameSysInit();
}

s16 opboardtutorial_SpiralEffCreate(s32 file, s32 flags) {
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
    Hu3DParticleCreate(model, -1, 0, opboardtutorial_SpiralEffHook);
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

s32 opboardtutorial_SpiralEffAdd(s16 model, f32 x, f32 y, f32 z) {
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

void opboardtutorial_SpiralEffHook(s16 model) {
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

s16 opboardtutorial_ModelAnimCreate(s16 model, s32 file, char *name) {
    void *data;
    s32 anim;
    s16 animIdx;

    data = DataRead(file);
    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    opboardtutorial_guideAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    opboardtutorial_guideAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, (u16)anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void opboardtutorial_ModelAnimSet(s16 model, s16 anim) {
    HmfAnim *entry;

    if (opboardtutorial_guideAnimLink != 0xFF) {
        if (anim == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            entry = &Hu3DAnimData[opboardtutorial_guideAnimLink];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

s16 opboardtutorial_AnimDataRead(s32 file) {
    void *data = DataRead(file);
    s32 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void opboardtutorial_PlayerSwap(s32 player1, s32 player2) {
    GW_PLAYER *first = MBPlayerGet(player1);
    GW_PLAYER *second = MBPlayerGet(player2);
    GW_PLAYER *temp = HuMemMemoryAllocPerm(sizeof(GW_PLAYER));

    bcopy(first, temp, sizeof(GW_PLAYER));
    bcopy(second, first, sizeof(GW_PLAYER));
    bcopy(temp, second, sizeof(GW_PLAYER));
    HuMemMemoryFreePerm(temp);
}

void opboardtutorial_PlayerTurnSort(void) {
    s32 i;
    s32 j;

    for (i = 3; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (GwPlayer[j].turn > GwPlayer[j + 1].turn) {
                opboardtutorial_PlayerSwap(j, j + 1);
            }
        }
    }
}

void opboardtutorial_CenterBobObjMain(omObjData *obj) {
    s32 i;

    opboardtutorial_centerMdl->coords.y = sindf(obj->rot.x) * 5.0f + obj->rot.z;
    for (i = 0; i < 4; i++) {
        opboardtutorial_playerTbl[i]->player_obj->coords.y = opboardtutorial_centerMdl->coords.y;
    }
    obj->rot.x += obj->rot.y;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
}

void opboardtutorial_ArriveExec(void) {
    s32 i;
    Object *shadow;
    omObjData *bob;
    s16 effect;
    f32 scale;
    f32 shadowScale;

    for (i = 0; i < 4; i++) {
        opboardtutorial_playerTbl[i] = MBPlayerGet(i);
        MBPlayerModelCreate(i, opboardtutorial_playerMotTbl[GwPlayer[i].chr], 2);
        HuVecCopy3F(&opboardtutorial_playerTbl[i]->player_obj->coords, &opboardtutorial_playerStartPosTbl[i]);
        MBModelTempAllocFree(opboardtutorial_playerTbl[i]->player_obj);
        opboardtutorial_playerTbl[i]->stat |= PLAYER_UNK_04;
    }
    opboardtutorial_centerMdl = MBModelFileCreate(0x1301FE, -1, 1.0f, 0, NULL);
    shadow = MBModelFileCreate(0x1301FD, -1, 1.0f, 0, NULL);
    HuVecCopy3F(&opboardtutorial_centerMdl->coords, &opboardtutorial_platformPos);
    HuVecCopy3F(&shadow->coords, &opboardtutorial_platformPos);
    shadow->coords.y = 0;
    HuVecCopyXYZ(&shadow->scale, shadow->coords.y, shadow->coords.y, shadow->coords.y);
    effect = EffectCreate(0xB0004, 0x6A9);
    EffectParamSet(effect, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(effect, 40.0f);
    Hu3DParticleAttrSet(effect, 1, 0);
    MBBackTPLvlSet(128);
    WipeCreateIn(WIPE_STARS, 16);
    HuPrcSleep(17);
    for (i = 128; i < 256; i += 8) {
        MBBackTPLvlSet(i);
        HuPrcVSleep();
    }
    MBBackTPLvlSet(255);
    HuAudFXPlay(0x2ED);
    while (opboardtutorial_centerMdl->coords.y >= 10.0f) {
        opboardtutorial_centerMdl->coords.y -= 3.0f;
        for (i = 0; i < 4; i++) {
            opboardtutorial_playerTbl[i]->player_obj->coords.y -= 3.0f;
        }
        shadowScale = 1.0f - opboardtutorial_centerMdl->coords.y / 250.0f;
        HuVecCopyXYZ(&shadow->scale, shadowScale, shadowScale, shadowScale);
        HuPrcVSleep();
    }
    bob = omAddObj(0x1000, 0, 0, -1, opboardtutorial_CenterBobObjMain);
    bob->rot.x = 180.0f;
    bob->rot.y = 5.0f;
    bob->rot.z = opboardtutorial_centerMdl->coords.y;
    HuPrcSleep(30);
    EffectPosSet(effect, opboardtutorial_centerMdl->coords.x,
                       opboardtutorial_centerMdl->coords.y + 40.0f, opboardtutorial_centerMdl->coords.z);
    Hu3DParticleAttrSet(effect, 0, 1);
    HuAudFXPlay(0x2E4);
    HuPrcSleep(30);
    for (scale = 1.0f; scale >= 0.0f; scale -= 0.1f) {
        for (i = 0; i < 4; i++) {
            HuVecCopyXYZ(&opboardtutorial_playerTbl[i]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        MBModelDispOff(opboardtutorial_playerTbl[i]->player_obj);
    }
    Hu3DParticleAttrSet(effect, 1, 0);
    HuPrcSleep(20);
    for (i = 0, scale = 1.0f; scale < 10.0f; i++, scale += 0.5f) {
        HuVecCopyXYZ(&opboardtutorial_centerMdl->scale, scale, scale, scale);
        HuPrcVSleep();
        if (i == 5) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 16);
        }
    }
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    EffectStop(effect);
    MBModelKill(opboardtutorial_centerMdl);
    MBModelKill(shadow);
    omDelObj(bob);
}

void opboardtutorial_GuideJump(Object *obj) {
    HuPrcSleep(5);
    obj->velocity.y = 20.0f;
    obj->velocity.z = -2.5f;
    HuPrcSleep(10);
    obj->velocity.y = 0;
    obj->velocity.z = 0;
    HuWinExCleanup(opboardtutorial_guideWin);
    opboardtutorial_guideWin = HuWinExCreateStyled(75, 159, 16);
    HuWinMesPalSet(opboardtutorial_guideWin, 4, 0, 224, 224);
    HuWinMesSpeedSet(opboardtutorial_guideWin, 0);
}

void opboardtutorial_TurnOrderExec(void) {
    s32 state[4];
    s32 frames[4];
    s32 order[4];
    u8 motion[4] = { 3, 6, 5, 0 };
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
    HuWinMesSet(opboardtutorial_guideWin, 0x1601, -1, -1);
    HuWinExOpen(opboardtutorial_guideWin, 1);
    MBWinComKeyAnyWait(opboardtutorial_guideWin);
    HuWinExClose(opboardtutorial_guideWin, 1);
    help = MBHelpWinCreate(2, 190, 1);
    for (i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                j = (rand8() & 3) + 2;
                break;
            case 1:
                j = (rand8() & 3) + 6;
                break;
            case 2:
                j = 10;
                break;
            case 3:
                j = 1;
                break;
            default:
                j = 5;
                break;
        }
        MBSaiValueForceSet(i, j);
    }
    for (i = 0; i < 4; i++) {
        state[i] = 1;
        frames[i] = 0;
    }
    HuPrcSleep(20);
    while (1) {
        for (i = 0; i < 4; i++) {
            if (state[i] == 1) {
                state[i] = 2;
                MBMotionSet(opboardtutorial_playerTbl[i]->player_obj, 2, 0);
                MBMotionEndShiftSet(opboardtutorial_playerTbl[i]->player_obj, -1, 2);
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
    opboardtutorial_PlayerTurnSort();
    MBStatusCreate();
    opboardtutorial_statusCreateF = 1;
    for (i = 0; i < 4; i++) {
        MBStatusDispSideSet(i, 1);
    }
    HuPrcSleep(5);
    HuWinMesPalSet(opboardtutorial_guideWin, 4, 0, 255, 255);
    HuWinMesSet(opboardtutorial_guideWin, 0x1602, -1, -1);
    HuWinExOpen(opboardtutorial_guideWin, 1);
    MBWinComKeyAnyWait(opboardtutorial_guideWin);
    for (i = 0; i < 4; i++) {
        s32 messages[4] = { 0x1603, 0x1604, 0x1605, 0x1606 };

        opboardtutorial_ModelAnimSet(opboardtutorial_guideMdl->omObj1->model[0], opboardtutorial_guideAnimTbl[motion[i]]);
        HuWinMesSet(opboardtutorial_guideWin, messages[i], -1, -1);
        if (i != 0) {
            HuWinExOpen(opboardtutorial_guideWin, 1);
        }
        MBWinComKeyAnyWait(opboardtutorial_guideWin);
        HuWinExClose(opboardtutorial_guideWin, 1);
        PlayerFXPlay(0x274, i);
        MBMotionShiftSetDef(opboardtutorial_playerTbl[i]->player_obj, 3, 0);
        MBMotionEndShiftSet(opboardtutorial_playerTbl[i]->player_obj, -1, 2);
        MBSaiNumKill(order[i]);
        if (i == 2) {
            opboardtutorial_GuideJump(opboardtutorial_guideMdl);
        }
        MBStatusDispMoveSet(i + 10);
        while (MBStatusMoveCheck() != 0) {
            HuPrcVSleep();
        }
        HuPrcSleep(20);
    }
    opboardtutorial_ModelAnimSet(opboardtutorial_guideMdl->omObj1->model[0], opboardtutorial_guideAnimTbl[0]);
}

void opboardtutorial_GuideTalkExec(void) {
    s16 effects[4];
    s32 i;
    s32 j;
    f32 scale;

    MBBackKill();
    MBBackLoad(22);
    MBCameraNearFarSet(1000.0f, 10000.0f);
    opboardtutorial_guideMdl = MBModelCreate(59, NULL);
    HuVecCopy3F(&opboardtutorial_guideMdl->coords, &opboardtutorial_guidePos);
    HuVecCopyXYZ(&opboardtutorial_guideMdl->scale, 0.9f, 0.9f, 0.9f);
    opboardtutorial_guideMdl->rot.x = sindf(10.0f);
    opboardtutorial_guideMdl->rot.z = cosdf(10.0f);
    opboardtutorial_guideMdl->flags |= 1;
    opboardtutorial_guideWin = HuWinExCreateStyled(75, 197, 16);
    HuWinMesSpeedSet(opboardtutorial_guideWin, 0);
    opboardtutorial_guideAnimTbl[0] = opboardtutorial_ModelAnimCreate(opboardtutorial_guideMdl->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    opboardtutorial_guideAnimTbl[1] = opboardtutorial_AnimDataRead(0xA007F);
    opboardtutorial_guideAnimTbl[2] = opboardtutorial_AnimDataRead(0xA0080);
    opboardtutorial_guideAnimTbl[3] = opboardtutorial_AnimDataRead(0xA0081);
    opboardtutorial_guideAnimTbl[4] = opboardtutorial_AnimDataRead(0xA0082);
    opboardtutorial_guideAnimTbl[5] = opboardtutorial_AnimDataRead(0xA0083);
    opboardtutorial_guideAnimTbl[6] = opboardtutorial_AnimDataRead(0xA0084);
    opboardtutorial_ModelAnimSet(opboardtutorial_guideMdl->omObj1->model[0], opboardtutorial_guideAnimTbl[0]);
    opboardtutorial_centerMdl = MBModelCreate(58, NULL);
    AuraCreate(opboardtutorial_centerMdl->omObj1->model[0]);
    HuVecCopy3F(&opboardtutorial_centerMdl->coords, &opboardtutorial_starPos);
    opboardtutorial_centerMdl->velocity.x = 1000.0f;
    for (j = 0; j < 4; j++) {
        HuVecCopy3F(&opboardtutorial_playerTbl[j]->player_obj->coords, &opboardtutorial_playerPosTbl[j]);
        effects[j] = opboardtutorial_SpiralEffCreate(0xB0004, 0x689);
    }
    WipeColorSet(255, 255, 255);
    WipeCreateIn(WIPE_FADE, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2DB);
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 4; j++) {
            opboardtutorial_SpiralEffAdd(effects[j], opboardtutorial_playerTbl[j]->player_obj->coords.x,
                                          opboardtutorial_playerTbl[j]->player_obj->coords.y + 50.0f, opboardtutorial_playerTbl[j]->player_obj->coords.z);
        }
        HuPrcVSleep();
    }
    for (scale = 0.0f; scale <= 1.0f; scale += 0.1f) {
        for (j = 0; j < 4; j++) {
            MBModelDispOn(opboardtutorial_playerTbl[j]->player_obj);
            HuVecCopyXYZ(&opboardtutorial_playerTbl[j]->player_obj->scale, scale, 1.0f, scale);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 4; j++) {
        HuVecCopyXYZ(&opboardtutorial_playerTbl[j]->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
    HuPrcSleep(20);
    HuAudSeqPlay(11);
    HuWinMesSet(opboardtutorial_guideWin, 0x1600, -1, -1);
    HuWinExOpen(opboardtutorial_guideWin, 1);
    MBWinComKeyAnyWait(opboardtutorial_guideWin);
    HuWinExClose(opboardtutorial_guideWin, 1);
    opboardtutorial_TurnOrderExec();
    HuWinMesSet(opboardtutorial_guideWin, 0x1607, -1, -1);
    HuWinExOpen(opboardtutorial_guideWin, 1);
    MBWinComKeyAnyWait(opboardtutorial_guideWin);
    HuWinExClose(opboardtutorial_guideWin, 1);
    HuWinExCleanup(opboardtutorial_guideWin);
}

void opboardtutorial_MainProc(void) {
    opboardtutorial_ArriveExec();
    opboardtutorial_GuideTalkExec();
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void opboardtutorial_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        opboardtutorial_BackClose();
        opboardtutorial_SysClose();
        HuWinAllKill();
        if (opboardtutorial_statusCreateF != 0) {
            MBStatusKill();
        }
        omOvlReturnEx(1);
    }
}

void opboardtutorial_ExitCheckObjMain(omObjData *obj) {
    if (omSysExitReq != 0) {
        WipeCreateOut(WIPE_STARS, 20);
        obj->func = opboardtutorial_ExitObjMain;
    }
}

void opboardtutorial_SysInit(void) {
    MBModelInit();
    MBPlayerMotInit();
    MBMotShiftInit();
    MBSprGrpInit();
}

void opboardtutorial_SysClose(void) {
    MBSprGrpClose();
    MBMotShiftClose();
    MBPlayerClose();
    MBModelClose();
}

void opboardtutorial_BackInit(void) {
    Hu3DCamInit(1);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    MBBackArcInit((u32)hvq_data_ROM_START);
    MBBackLoad(0x15);
}

void opboardtutorial_BackClose() {
    MBBackKill();
    MBBackClose();
}
