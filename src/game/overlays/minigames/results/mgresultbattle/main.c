#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/player.h"
#include "mgresultbattle.h"

void mgresultbattle_CameraInit(void);
void mgresultbattle_BackInit(void);
void mgresultbattle_CoinCalc(void);
void mgresultbattle_PlayerProc(void);
void mgresultbattle_MainObjMain(omObjData *);
void mgresultbattle_ExitObjMain(omObjData *);
void mgresultbattle_BackDimCreate(void);
void mgresultbattle_BackDimDraw(Gfx **, s32, s32);
void mgresultbattle_PlayerReactWait(omObjData *);
void mgresultbattle_PlayerDestroy(void);
void mgresultbattle_PlayerIdle(omObjData *obj);

extern s32 omCharModelNoTbl[][6];
extern const s32 mgresultbattle_boardBackTbl[];
extern const s8 mgresultbattle_coinShareDivTbl[];
extern const f32 mgresultbattle_coinShareTbl[][4];
extern u16 mgBattleCoinPot;

s8 mgresultbattle_mainState = 0;
s32 mgresultbattle_mainTimer = 0;
s8 mgresultbattle_exitWipeF = 0;

void mgresultbattle_ObjectSetup(void) {
    s16 var_a0_2;
    s16 var_a1;
    s16 i;
    s16 j;

    var_a1 = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            mgresultbattle_playerOrderTbl[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    Hu3DSprModelInit(0x78);
    omInitObjMan(0x1E, 0x1E);
    CamSetupInitMulti(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);

    for (var_a0_2 = 0, i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwPlayer[i].bonusCoin == 3) {
            var_a0_2++;
        }
    }

    if (var_a0_2 >= 4) {
        GameMesStub();
        MBBackKill();
        MBBackClose();
        omOvlReturnEx(1);
        return;
    }
    mgresultbattle_CoinCalc();
    omAddPrcObj(mgresultbattle_CoinNumProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultbattle_HostProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultbattle_PodiumProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultbattle_PlayerProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultbattle_CoinProc, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, mgresultbattle_MainObjMain);
    omAddObj(0, 0, 0, -1, mgresultbattle_ExitObjMain);
    mgresultbattle_BackInit();
    mgresultbattle_CameraInit();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

void mgresultbattle_MainObjMain(omObjData *obj) {
    s32 state;
    s32 i;
    s32 coins;
    s32 newCoins;

    state = mgresultbattle_mainState;
    switch (state) {
        case 0:
            HuAudSeqPlay(0x15);
            mgresultbattle_mainTimer = 0;
            state++;
            break;
        case 1:
            state++;
            break;
        case 2:
            if (mgresultbattle_mainTimer++ >= 6) {
                mgresultbattle_HostFlyStart();
                mgresultbattle_mainTimer = 0;
                state++;
            }
            break;
        case 4:
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coins = GwPlayer[i].coin + GwPlayer[i].gameCoin;
                if (coins <= 999) {
                    newCoins = coins;
                } else {
                    newCoins = 999;
                }
                GwPlayer[i].coin = newCoins;
                MBPlayerCoinAdd(i, 0);
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            state++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                GameMesStub();
                MBBackKill();
                MBBackClose();
                omOvlReturnEx(1);
            }
            break;
    }
    mgresultbattle_mainState = state;
}

void mgresultbattle_CameraInit(void) {
    CZoom = 2300.0f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 390.0f;
    Center.z = -460.0f;
}

void mgresultbattle_ExitObjMain(omObjData *obj) {
    if (omSysExitReq == 1) {
        if (mgresultbattle_exitWipeF == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            mgresultbattle_exitWipeF = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            HuAudFXAllFadeOut(30);
            GameMesStub();
            MBBackKill();
            MBBackClose();
            omOvlReturnEx(1);
        }
    }
}

void mgresultbattle_BackInit(void) {
    GW_SYSTEM *system = &GwSystem;

    MBBackArcInit((u32)hvq_data_ROM_START);

    if (!(system->playMode & 2)) {
        MBBackCreate(mgresultbattle_boardBackTbl[system->current_board_index], 0);
    } else {
        MBBackCreate(0x17, 0);
    }
    mgresultbattle_BackDimCreate();
}

void mgresultbattle_BackDimCreate(void) {
    Hu3DHookFuncCreate(0, mgresultbattle_BackDimDraw, 0);
}

void mgresultbattle_BackDimDraw(Gfx **gfx, s32 arg1, s32 arg2) {
    Gfx *gdl = *gfx;

    gDPPipeSync(gdl++);
    gDPSetCycleType(gdl++, G_CYC_1CYCLE);
    gSPClearGeometryMode(gdl++, G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR |
                                    G_LOD | G_SHADING_SMOOTH);
    gSPSetGeometryMode(gdl++, G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH);
    gDPSetTexturePersp(gdl++, G_TP_NONE);
    gDPSetPrimColor(gdl++, 0, 0, 0, 0, 0, 127);
    gDPSetRenderMode(gdl++, G_RM_AA_XLU_SURF, G_RM_AA_XLU_SURF2);
    gDPSetCombineMode(gdl++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetTextureLUT(gdl++, G_TT_NONE);
    gDPSetFillColor(gdl++, 0x10001);
    gDPFillRectangle(gdl++, 0, 0, 319, 239);
    *gfx = gdl;
}

void mgresultbattle_CoinCalc(void) {
    s32 order[4];
    s32 ranks[4];
    s8 rankCounts[4];
    s32 rank;
    s32 total;
    s32 type;
    s32 count;
    s32 i;
    s32 j;
    s32 player;

    for (i = 0, j = 0; i < 4; i++) {
        j += (GwPlayer[i].bonusCoin >= 3);
    }
    if (j >= 4) {
        mgresultbattle_coinRest = 0;
        for (i = 0; i < 4; i++) {
            GwPlayer[i].gameCoin = 0;
            GwPlayer[i].coin += GwPlayer[i].checkCoin;
        }
        return;
    }

    rank = 0;
    count = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            if (j == GwPlayer[i].bonusCoin) {
                count++;
                ranks[i] = rank;
            }
        }
        rank += count;
        count = 0;
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].bonusCoin = ranks[i];
    }
    for (i = 0; i < 4; i++) {
        rankCounts[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        rankCounts[GwPlayer[i].bonusCoin]++;
    }

    type = 0;
    if (rankCounts[0] == 1 && rankCounts[1] == 1 && rankCounts[2] == 1 && rankCounts[3] == 1) {
        type = 0;
    } else if (rankCounts[0] == 2 && rankCounts[2] == 2) {
        type = 2;
    } else if (rankCounts[0] == 2) {
        type = 1;
    } else if (rankCounts[0] == 3) {
        type = 3;
    } else if (rankCounts[1] == 2) {
        type = 4;
    } else if (rankCounts[1] == 3) {
        type = 5;
    } else if (rankCounts[2] == 2) {
        type = 6;
    } else if (rankCounts[0] == 4) {
        type = 7;
    }

    total = 0;
    for (i = 0; i < 4; i++) {
        if (mgresultbattle_coinShareDivTbl[type] == 0) {
            GwPlayer[i].gameCoin = mgBattleCoinPot * mgresultbattle_coinShareTbl[type][GwPlayer[i].bonusCoin];
        } else if (mgresultbattle_coinShareTbl[type][GwPlayer[i].bonusCoin] != 0.0f) {
            GwPlayer[i].gameCoin = mgBattleCoinPot / mgresultbattle_coinShareTbl[type][GwPlayer[i].bonusCoin];
        } else {
            GwPlayer[i].gameCoin = 0;
        }
        total += GwPlayer[i].gameCoin;
    }
    mgresultbattle_coinRest = mgBattleCoinPot - total;

    switch (type) {
        case 4:
            if (mgresultbattle_coinRest == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 1) {
                        GwPlayer[i].gameCoin += 1;
                    }
                }
                mgresultbattle_coinRest = 0;
            }
            break;
        case 5:
            if (mgresultbattle_coinRest == 3) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 1) {
                        GwPlayer[i].gameCoin += 1;
                    }
                }
                mgresultbattle_coinRest = 0;
            }
            break;
        case 6:
            if (mgresultbattle_coinRest == 2) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].bonusCoin == 0) {
                        GwPlayer[i].gameCoin += 2;
                        break;
                    }
                }
                mgresultbattle_coinRest = 0;
            }
            break;
    }

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            player = mgresultbattle_playerOrderTbl[j];
            if (i == GwPlayer[player].bonusCoin) {
                order[count++] = player;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        mgresultbattle_playerOrderTbl[i] = order[i];
    }
}

void mgresultbattle_PlayerProc(void) {
    omObjData *obj;
    s32 i;
    s32 chr;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(0x14, 4, 8, -1, NULL);
        mgresultbattle_playerWorkTbl[i].obj = obj;
        chr = GwPlayer[mgresultbattle_playerOrderTbl[i]].chr;

        obj->model[1] = Hu3DModelRead(omCharModelNoTbl[chr][0] | omCharModelNoTbl[chr][1], 0x2B9);
        Hu3DMotionAttrSet(obj->model[1], 2, 2);
        obj->model[2] = Hu3DModelRead(9, 0x2B9);
        Hu3DModelPosSet(obj->model[2], 0.0f, -5.0f, 0.0f);

        omObjMotionRead(obj, 0, CharMotionDataNumGet(chr, 0));
        omObjMotionRead(obj, 1, CharMotionDataNumGet(chr, 0x2F));
        omObjMotionRead(obj, 2, CharMotionDataNumGet(chr, 0x36));
        omObjMotionRead(obj, 3, CharMotionDataNumGet(chr, 0x25));
        Hu3DMotionModelSet(obj->model[1], obj->motion[0]);
        Hu3DMotionAttrSet(obj->model[1], 2, 2);
        Hu3DModelPosSet(obj->model[1], mgresultbattle_playerPosTbl[i].x, mgresultbattle_playerPosTbl[i].y,
                        mgresultbattle_playerPosTbl[i].z);
        Hu3DModelPosSet(obj->model[2], mgresultbattle_playerPosTbl[i].x, mgresultbattle_playerPosTbl[i].y,
                        mgresultbattle_playerPosTbl[i].z);

        obj->trans.x = 0.0f;
        obj->trans.y = 0.0f;
        obj->trans.z = 0.0f;
        Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
        omPrcSetDestructor(NULL, mgresultbattle_PlayerDestroy);
        mgresultbattle_playerWorkTbl[i].func = mgresultbattle_PlayerIdle;
    }

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            mgresultbattle_playerWorkTbl[i].func(obj);
            HuPrcVSleep();
        }
    }
}

void mgresultbattle_PlayerDestroy(void) {
}

void mgresultbattle_PlayerIdle(omObjData *obj) {
}

void mgresultbattle_PlayerReactStart(void) {
    omObjData *obj;
    s32 motion;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = mgresultbattle_playerWorkTbl[i].obj;
        if (GwPlayer[mgresultbattle_playerOrderTbl[i]].gameCoin > 0) {
            motion = 1;
            PlayerFXPlay(0x274, mgresultbattle_playerOrderTbl[i]);
        } else {
            motion = 2;
        }
        Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[motion]].motId, 0, 0x14, 0);
    }
    mgresultbattle_playerWorkTbl[0].func = mgresultbattle_PlayerReactWait;
}

void mgresultbattle_PlayerReactWait(omObjData *obj) {
    s32 pressed;
    s32 i;
    s32 j;

    HuPrcSleep(5);
    while (!(Hu3DMotionShiftTimeGet(obj->model[1]) < 0.0f)) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if (Hu3DMotion[Hu3DData[obj->model[1]].motId].unk02 <= Hu3DData[obj->model[1]].motTime) {
            pressed = 0;
            for (i = 0; i < 40; i++) {
                for (j = 0; j < 4; j++) {
                    if (!(GwPlayer[j].stat & PLAYER_IS_CPU) && (HuPadBtnDown[GwPlayer[j].pad] & A_BUTTON)) {
                        pressed = 1;
                        break;
                    }
                }
                if (pressed == 1) {
                    break;
                }
                HuPrcVSleep();
            }
            mgresultbattle_mainState = 4;
            break;
        }
        HuPrcVSleep();
    }
    mgresultbattle_playerWorkTbl[0].func = mgresultbattle_PlayerIdle;
}

const s32 mgresultbattle_boardBackTbl[] = { 4, 7, 10, 13, 16, 19 };

const f32 mgresultbattle_coinShareTbl[][4] = {
    { 0.7f, 0.3f, 0.0f, 0.0f },
    { 0.5f, 0.0f, 0.0f, 0.0f },
    { 0.5f, 0.0f, 0.0f, 0.0f },
    { 3.0f, 0.0f, 0.0f, 0.0f },
    { 0.6f, 0.2f, 0.0f, 0.0f },
    { 0.7f, 0.1f, 0.0f, 0.0f },
    { 0.7f, 0.3f, 0.0f, 0.0f },
    { 0.25f, 0.0f, 0.0f, 0.0f }
};
