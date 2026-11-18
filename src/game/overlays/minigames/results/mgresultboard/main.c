#include "common.h"
#include "game/overlays/party/common/player.h"
#include "mgresultboard.h"

extern PlayerResult mgresultboard_prevResultTbl[4];
extern PlayerResult mgresultboard_resultTbl[4];

void mgresultboard_BackDimDraw(Gfx **, s32, s32);
void mgresultboard_CoinIconProc(void);
void mgresultboard_FaceProc(void);
void mgresultboard_ScoreProc(void);
void mgresultboard_RankProc(void);
void mgresultboard_StarIconProc(void);
void mgresultboard_InitProc(void);
void mgresultboard_MainObjMain(omObjData *);
void mgresultboard_CameraInit(void);
void mgresultboard_ExitObjMain(omObjData *);
void mgresultboard_BackInit(void);
void mgresultboard_TitleCreate(void);
void mgresultboard_RankCalc(void);
void MBBackArcInit(u32);
void MBBackCreate(s32, s32);
void mgresultboard_BackDimCreate(void);
void mgresultboard_BackDimDraw(Gfx **, s32, s32);
extern const s32 mgresultboard_boardBackTbl[];
void MBBackClose(void);
void MBBackKill(void);
s32 mgresultboard_RowShuffle(s8);
s32 mgresultboard_RowSet(s8);
s32 mgresultboard_RankShow(s32, s32);
s32 mgresultboard_CoinGainShow(s32, s16);
s32 mgresultboard_CoinShow(s8, s16);
void mgresultboard_RankCalc(void);
void mgresultboard_RowDimOn(s32);
void mgresultboard_RowDimOff(s32);
void mgresultboard_FlipSePlay(s32);
void mgresultboard_FlipSeStop(void);
s32 mgresultboard_CoinPlusFlip(omObjData *, s8, s16);

typedef struct Unk {
    omObjData *unk_00;
} Unk;

extern Unk mgresultboard_scoreObj; // unknown size
extern omObjData *mgresultboard_coinIconObj;
extern omObjData *mgresultboard_starIconObj;
extern omObjData *mgresultboard_faceObj;
extern s32 mgresultboard_mainTimer;
extern s8 mgresultboard_mainCnt;
s32 mgresultboard_RankFlapFlip(omObjData *, s8, s8); /* extern */
extern omObjData *mgresultboard_rankObj;
extern s16 mgresultboard_seIdTbl[3];
extern const u8 mgresultboard_rankFaceTbl[];

// updates mg star coins on results scene load
u32 mgresultboard_mainState = 0;
f32 mgresultboard_speed = 1.0f;
s32 mgresultboard_initDoneF = 0;
s8 mgresultboard_exitWipeF = 0;
s32 mgresultboard_seOnTbl[3] = { 0, 0, 0 };
s32 mgresultboard_seStopDelay = 0;

void mgresultboard_ObjectSetup(void) {
    omObjData *obj;
    s32 minigameType;
    s8 i;

    omInitObjMan(0x1E, 0x1E);
    CamSetupInitMulti(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }

    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    minigameType = mgDataTbl[GwSystem.minigame_index - 1].minigameType;

    if (minigameType < MINIGAME_ITEM) {
        if (minigameType >= MINIGAME_4P) {
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                u16 newMgStarCoins = GwPlayer[i].gameCoin + GwPlayer[i].bonusCoin + GwPlayer[i].gamePrize;
                GwPlayer[i].gamePrize = newMgStarCoins;
            }
        }
    }

    mgresultboard_RankCalc();
    omAddPrcObj(mgresultboard_InitProc, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, mgresultboard_MainObjMain);
    omAddObj(0, 0, 0, -1, mgresultboard_ExitObjMain);
    mgresultboard_BackInit();
    mgresultboard_TitleCreate();
    mgresultboard_CameraInit();
}

void mgresultboard_InitProc(void) {
    mgresultboard_initDoneF = 0;
    HuPrcSleep(2);
    omAddPrcObj(mgresultboard_RankProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultboard_FaceProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultboard_CoinIconProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultboard_StarIconProc, 0x1001, 0x2000, 0);
    omAddPrcObj(mgresultboard_ScoreProc, 0x1001, 0x2000, 0);
    HuPrcVSleep();
    mgresultboard_RowSet(0);
    mgresultboard_RowSet(1);
    mgresultboard_RowSet(2);
    mgresultboard_RowSet(3);
    mgresultboard_initDoneF = 1;
    while (1) {
        HuPrcVSleep();
    }
}

// main state machine behind scoreboard and how it animates
void mgresultboard_MainObjMain(omObjData *arg0) {
    PlayerResult *temp_v0_13;
    s32 coinTotal;
    s32 currentCoin;
    s16 var_a1;
    s32 temp_v0;
    s8 var_a0;
    u16 buttonPressed;
    u16 cpuCount;
    s32 var_s3;
    s32 var_s5;
    u32 state;
    s32 var_v1_3;
    PlayerResult *temp_a0_5;
    s8 i;
    s8 playerIdx;

    var_s5 = 0;
    state = mgresultboard_mainState;
    var_s3 = 0;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x14);
            mgresultboard_mainTimer = 0;
            state++;
            break;
        case 1:
            if (mgresultboard_initDoneF == 1) {
                WipeCreateIn(WIPE_TYPE_PREV, 0x10);
                state++;
            }
            break;
        case 2:
            mgresultboard_mainTimer++;
            if (mgresultboard_mainTimer >= 0x14) {
                mgresultboard_mainCnt = 0;
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 3:
            mgresultboard_mainTimer++;
            if (mgresultboard_mainTimer >= ((s32)(40.0f / mgresultboard_speed) + (s32)(15.0f / mgresultboard_speed))) {
                mgresultboard_mainTimer = 0;
                mgresultboard_mainCnt = 0;
                state++;
            }
            break;
        case 4:
            mgresultboard_mainCnt = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coinTotal = GwPlayer[mgresultboard_resultTbl[i].idx].bonusCoin;
                coinTotal += GwPlayer[mgresultboard_resultTbl[i].idx].gameCoin;
                if (coinTotal <= 0) {
                    mgresultboard_mainCnt++;
                }
            }

            if (mgresultboard_mainCnt >= 4) {
                mgresultboard_mainTimer = 0;
                state = 0x10;
            } else {
                mgresultboard_mainCnt = 0;
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 5:
            var_s3 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                playerIdx = mgresultboard_resultTbl[i].idx;
                coinTotal = GwPlayer[playerIdx].gameCoin;
                coinTotal += GwPlayer[playerIdx].bonusCoin;
                if (coinTotal > 0) {
                    var_s5++;
                    var_s3 = mgresultboard_CoinGainShow(i, ((((rand8()) << 8) | (rand8())) % 1000));
                    mgresultboard_RowDimOff(i);
                } else {
                    mgresultboard_RowDimOn(i);
                }
            }

            if (var_s3 == 1) {
                if (++mgresultboard_mainTimer >= 2) {
                    mgresultboard_mainTimer = 0;
                    state++;
                }
            }
            break;
        case 6:
            var_s3 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coinTotal = GwPlayer[mgresultboard_resultTbl[i].idx].gameCoin;
                coinTotal += GwPlayer[mgresultboard_resultTbl[i].idx].bonusCoin;
                if (coinTotal > 0) {
                    var_s3 = mgresultboard_CoinGainShow(i, coinTotal);
                    mgresultboard_RowDimOff(i);
                    var_s5++;
                } else {
                    mgresultboard_RowDimOn(i);
                }
            }

            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coinTotal = GwPlayer[mgresultboard_resultTbl[i].idx].bonusCoin;
                if (coinTotal >= 10) {
                    mgresultboard_RankShow(i, 4);
                    var_s5++;
                }
            }
            if (var_s3 == 1) {
                mgresultboard_mainTimer = 0;
                state++;
            }

            break;
        case 7:
            mgresultboard_mainTimer++;
            if (!(mgresultboard_mainTimer < ((s32)(40.0f / mgresultboard_speed) + (s32)(15.0f / mgresultboard_speed)))) {
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 8:
            var_s3 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                coinTotal = GwPlayer[mgresultboard_resultTbl[i].idx].gameCoin;
                coinTotal += GwPlayer[mgresultboard_resultTbl[i].idx].bonusCoin;
                if (coinTotal > 0) {
                    var_s5++;
                    var_s3 = mgresultboard_CoinShow(i, ((((rand8()) << 8) | (rand8())) % 1000));
                    mgresultboard_RowDimOff(i);

                } else {
                    mgresultboard_RowDimOn(i);
                }
            }

            if (var_s3 == 1) {
                mgresultboard_mainTimer++;
                if (mgresultboard_mainTimer >= 2) {
                    mgresultboard_mainTimer = 0;
                    state++;
                }
                break;
            }
            break;
        case 9:
            var_s3 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                currentCoin = GwPlayer[mgresultboard_resultTbl[i].idx].coin;
                coinTotal = GwPlayer[mgresultboard_resultTbl[i].idx].gameCoin;
                if ((coinTotal += GwPlayer[mgresultboard_resultTbl[i].idx].bonusCoin) > 0) {
                    var_s3 = mgresultboard_CoinShow(i, currentCoin + coinTotal);
                    mgresultboard_RowDimOff(i);
                    var_s5++;
                } else {
                    mgresultboard_RowDimOn(i);
                }
            }

            if (var_s3 == 1) {
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 10:
            mgresultboard_mainTimer++;
            if (!(mgresultboard_mainTimer < ((s32)(40.0f / mgresultboard_speed) + (s32)(15.0f / mgresultboard_speed)))) {
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 11:
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                mgresultboard_prevResultTbl[i] = mgresultboard_resultTbl[i];
                playerIdx = mgresultboard_resultTbl[i].idx;
                currentCoin = GwPlayer[playerIdx].coin;
                coinTotal = GwPlayer[playerIdx].gameCoin;
                coinTotal += GwPlayer[playerIdx].bonusCoin;

                if (currentCoin + coinTotal < 0x3E8) {
                    GwPlayer[playerIdx].coin = currentCoin + coinTotal;
                } else {
                    GwPlayer[playerIdx].coin = 0x3E7;
                }
                GwPlayer[playerIdx].gameCoin = 0;
                GwPlayer[playerIdx].bonusCoin = 0;
            }
            state++;
            mgresultboard_RankCalc();
            break;
        case 12:
            mgresultboard_mainCnt = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                var_a0 = 0;
                if (mgresultboard_resultTbl[i].rank != mgresultboard_prevResultTbl[i].rank) {
                    mgresultboard_mainCnt++;
                    var_a0 = 1;
                }

                if (mgresultboard_resultTbl[i].idx != mgresultboard_prevResultTbl[i].idx) {
                    mgresultboard_mainCnt++;
                    var_a0++;
                }

                if (mgresultboard_prevResultTbl[i].bonusCoin >= 10) {
                    mgresultboard_mainCnt++;
                    var_a0++;
                }

                if (var_a0 > 0) {
                    playerIdx = mgresultboard_resultTbl[i].idx; //??? why does this help so much
                    if (GwPlayer[playerIdx].stat & PLAYER_IS_CPU) {
                        continue;
                    } else {
                        omVibrate(playerIdx, 5, 0, 5);
                    }
                }
            }

            if (mgresultboard_mainCnt == 0) {
                mgresultboard_mainTimer = 0;
                state = 0xF;
            } else {
                mgresultboard_mainCnt = 0;
                state++;
            }
            break;
        case 13:
            var_s3 = 0;
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                var_a1 = mgresultboard_resultTbl[i].rank != mgresultboard_prevResultTbl[i].rank;
                if (mgresultboard_resultTbl[i].idx != mgresultboard_prevResultTbl[i].idx) {
                    var_a1 = 1;
                }
                if (mgresultboard_prevResultTbl[i].bonusCoin >= 10) {
                    var_a1 = 1;
                }
                if (var_a1 == 1) {
                    var_s3 = mgresultboard_RowShuffle(i);
                    mgresultboard_RowDimOff(i);
                    var_s5 += 1;
                } else {
                    mgresultboard_RowDimOn(i);
                }
            }

            if (var_s3 == 1) {
                mgresultboard_mainCnt += 1;
            }
            if (mgresultboard_mainCnt >= 2) {
                mgresultboard_mainCnt = 0;
                state++;
            }
            break;
        case 14:
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                var_a1 = mgresultboard_resultTbl[i].rank != mgresultboard_prevResultTbl[i].rank;
                if (mgresultboard_resultTbl[i].idx != mgresultboard_prevResultTbl[i].idx) {
                    var_a1 = 1;
                }
                if (mgresultboard_prevResultTbl[i].bonusCoin >= 10) {
                    var_a1 = 1;
                }
                if (var_a1 == 1) {
                    var_s3 = mgresultboard_RowSet(i);
                    mgresultboard_RowDimOff(i);
                    var_s5++;
                }
            }

            if (var_s3 == 1) {
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 15:
            mgresultboard_mainTimer++;
            if (mgresultboard_mainTimer >= 30) {
                for (i = 0; i < MB_MAX_PLAYERS; i++) {
                    mgresultboard_RowDimOff(i);
                }
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 16:
            mgresultboard_mainTimer++;
            if (mgresultboard_mainTimer >= 40) {
                mgresultboard_mainTimer = 0;
                state++;
            }
            break;
        case 17:
            for (i = 0; i < MB_MAX_PLAYERS; i++) {
                MBPlayerCoinAdd(i, 0);
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            HuAudSeqFadeOut(0x1E);
            state++;
            break;
        case 18:
            if (WipeStatGet() == 0) {
                GameMesStub();
                MBBackKill();
                MBBackClose();
                omOvlReturnEx(1);
            }
            break;
    }

    if (var_s5 > 0) {
        mgresultboard_FlipSePlay(var_s5);
    } else {
        mgresultboard_FlipSeStop();
    }

    mgresultboard_mainState = state;
    buttonPressed = 0;
    cpuCount = 0;
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (!(GwPlayer[i].stat & PLAYER_IS_CPU)) {
            buttonPressed |= HuPadBtn[GwPlayer[i].pad];
        } else {
            cpuCount++;
        }
    }

    mgresultboard_speed = ((buttonPressed & A_BUTTON) || (cpuCount >= 4)) ? 4.0f : 1.0f;
}

s32 mgresultboard_FaceFlapFlip(omObjData *, s32, s8, s8); /* extern */
s32 mgresultboard_StarFlip(omObjData *, s32, s16);    /* extern */
s32 mgresultboard_CoinFlip(omObjData *, s32, s16);    /* extern */

s32 mgresultboard_RowShuffle(s8 arg0) {
    u16 var_s0;
    s32 var_s3;

    var_s0 = rand16();
    var_s3 = 0;

    if (mgresultboard_RankFlapFlip(mgresultboard_rankObj, arg0, var_s0 & 3) == 1) {
        var_s3 = 1;
        var_s0 = rand16();
    }
    if (mgresultboard_FaceFlapFlip(mgresultboard_faceObj, arg0, mgresultboard_resultTbl[var_s0 & 3].chr, ((var_s0 / 8) % 3)) == 1) {
        var_s0 = rand16();
    }
    if (mgresultboard_StarFlip(mgresultboard_scoreObj.unk_00, arg0, ((var_s0) % 100)) == 1) {
        var_s0 = rand16();
    }
    if (mgresultboard_CoinFlip(mgresultboard_scoreObj.unk_00, arg0, ((var_s0) % 1000)) == 1) {
        rand8();
        rand8();
    }
    return var_s3;
}

s32 mgresultboard_RowSet(s8 arg0) {
    s32 temp_s3;

    temp_s3 = mgresultboard_RankFlapFlip(mgresultboard_rankObj, arg0, mgresultboard_resultTbl[arg0].rank) == 1;
    mgresultboard_FaceFlapFlip(mgresultboard_faceObj, arg0, mgresultboard_resultTbl[arg0].chr, mgresultboard_resultTbl[arg0].unk_03);
    mgresultboard_StarFlip(mgresultboard_scoreObj.unk_00, arg0, mgresultboard_resultTbl[arg0].star);
    mgresultboard_CoinFlip(mgresultboard_scoreObj.unk_00, arg0, mgresultboard_resultTbl[arg0].coin);
    return temp_s3;
}

s32 mgresultboard_RankShow(s32 arg0, s32 arg1) {
    if (mgresultboard_RankFlapFlip(mgresultboard_rankObj, arg0, arg1) ^ 1) {
        return 0;
    } else {
        return 1;
    }
}

s32 mgresultboard_CoinGainShow(s32 arg0, s16 arg1) {
    return mgresultboard_CoinPlusFlip(mgresultboard_scoreObj.unk_00, arg0, arg1);
}

s32 mgresultboard_CoinShow(s8 arg0, s16 arg1) {
    return mgresultboard_CoinFlip(mgresultboard_scoreObj.unk_00, arg0, arg1);
}

void mgresultboard_CameraInit(void) {
    f32 fov = 30.0f;
    s8 i;

    CZoom = 1652.7628f;
    CRot.x = 0.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 26.4f;
    Center.z = -1050.0f;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCameraPerspectiveSet(i, fov, 80.0f, 8000.0f);
    }
}

void mgresultboard_ExitObjMain(omObjData *arg0) {
    if (omSysExitReq == 1) {
        if (mgresultboard_exitWipeF == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            mgresultboard_exitWipeF = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            GameMesStub();
            MBBackKill();
            MBBackClose();
            omOvlReturnEx(1);
        }
    }
}

void mgresultboard_BackInit(void) {
    GW_SYSTEM *system = &GwSystem;

    MBBackArcInit((u32)hvq_data_ROM_START);

    if (!(system->playMode & 2)) {
        MBBackCreate(mgresultboard_boardBackTbl[system->current_board_index], 0);
    } else {
        MBBackCreate(0x17, 0);
    }
    mgresultboard_BackDimCreate();
}

void mgresultboard_BackDimCreate(void) {
    s16 modelId = Hu3DHookFuncCreate(0, mgresultboard_BackDimDraw, 2);

    Hu3DModelCameraSet(modelId, HU3D_CAM0);
}

void mgresultboard_BackDimDraw(Gfx **gfx, s32 arg1, s32 arg2) {
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

void mgresultboard_TitleCreate(void) {
    u16 temp_s0;

    temp_s0 = espEntry(HuSprAnimDataRead(0x18000A), 0, 0);
    espPosSet(temp_s0, 0xA0, 0x20);
    espAttrSet(temp_s0, HUSPR_ATTR_XLU);
    espTPLvlSet(temp_s0, 0xFF);
    espColorSet(temp_s0, 0xFF, 0xFF, 0xFF);
    espPosSet(espEntry(HuSprAnimDataRead(0x180009), 0, 0), 0xA0, 0x20);
}

void mgresultboard_RankCalc(void) {
    s32 ranks[4];
    s32 values[2];
    PlayerResult temp;
    s32 i;
    s32 j;
    s32 rank;
    s32 place;
    s32 count;

    for (i = 0; i < 4; i++) {
        mgresultboard_resultTbl[i].idx = i;
        mgresultboard_resultTbl[i].rank = 0;
        mgresultboard_resultTbl[i].unk_03 = 0;
        mgresultboard_resultTbl[i].chr = GwPlayer[i].chr;
        mgresultboard_resultTbl[i].star = GwPlayer[i].star;
        mgresultboard_resultTbl[i].coin = GwPlayer[i].coin;
        mgresultboard_resultTbl[i].gameCoin = GwPlayer[i].gameCoin;
        mgresultboard_resultTbl[i].gameCoin += GwPlayer[i].bonusCoin;
        mgresultboard_resultTbl[i].bonusCoin = GwPlayer[i].bonusCoin;
    }

    for (i = 0; i < 3; i++) {
        for (j = i + 1; j < 4; j++) {
            values[0] = mgresultboard_resultTbl[i].star * 1000 + mgresultboard_resultTbl[i].coin;
            values[1] = mgresultboard_resultTbl[j].star * 1000 + mgresultboard_resultTbl[j].coin;
            if (values[0] < values[1]) {
                temp = mgresultboard_resultTbl[i];
                mgresultboard_resultTbl[i] = mgresultboard_resultTbl[j];
                mgresultboard_resultTbl[j] = temp;
            } else if (values[0] == values[1] && mgresultboard_resultTbl[i].idx > mgresultboard_resultTbl[j].idx) {
                temp = mgresultboard_resultTbl[i];
                mgresultboard_resultTbl[i] = mgresultboard_resultTbl[j];
                mgresultboard_resultTbl[j] = temp;
            }
        }
    }

    rank = 0;
    mgresultboard_resultTbl[0].rank = 0;
    mgresultboard_resultTbl[0].unk_03 = mgresultboard_rankFaceTbl[0];
    for (i = 1; i < 4; i++) {
        values[0] = mgresultboard_resultTbl[i - 1].star * 1000 + mgresultboard_resultTbl[i - 1].coin;
        values[1] = mgresultboard_resultTbl[i].star * 1000 + mgresultboard_resultTbl[i].coin;
        rank += (values[0] != values[1]);
        mgresultboard_resultTbl[i].rank = rank;
    }

    place = 0;
    count = 0;
    for (j = 0; j < 4; j++) {
        for (i = 0; i < 4; i++) {
            if (j == mgresultboard_resultTbl[i].rank) {
                count++;
                ranks[i] = place;
            }
        }
        place += count;
        count = 0;
    }

    for (i = 0; i < 4; i++) {
        mgresultboard_resultTbl[i].rank = ranks[i];
        mgresultboard_resultTbl[i].unk_03 = mgresultboard_rankFaceTbl[ranks[i]];
    }
}

void mgresultboard_RowDimOn(s32 player) {
    omObjData *obj;

    obj = mgresultboard_rankObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player + 5], HU3D_CAM0);
    obj = mgresultboard_faceObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player + 5], HU3D_CAM0);
    obj = mgresultboard_starIconObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM0);
    obj = mgresultboard_coinIconObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM0);
    obj = mgresultboard_scoreObj.unk_00;
    Hu3DModelCameraSet(obj->model[player * 2 + 1], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 2 + 2], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 2 + 21], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 2 + 22], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 9], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 10], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 11], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 29], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 30], HU3D_CAM0);
    Hu3DModelCameraSet(obj->model[player * 3 + 31], HU3D_CAM0);
}

void mgresultboard_RowDimOff(s32 player) {
    omObjData *obj;

    obj = mgresultboard_rankObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player + 5], HU3D_CAM1);
    obj = mgresultboard_faceObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player + 5], HU3D_CAM1);
    obj = mgresultboard_starIconObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM1);
    obj = mgresultboard_coinIconObj;
    Hu3DModelCameraSet(obj->model[player + 1], HU3D_CAM1);
    obj = mgresultboard_scoreObj.unk_00;
    Hu3DModelCameraSet(obj->model[player * 2 + 1], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 2 + 2], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 2 + 21], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 2 + 22], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 9], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 10], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 11], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 29], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 30], HU3D_CAM1);
    Hu3DModelCameraSet(obj->model[player * 3 + 31], HU3D_CAM1);
}

void mgresultboard_FlipSePlay(s32 arg0) {
    s32 *played;

    if (arg0 > 0) {
        if (mgresultboard_speed == 4.0f) {
            played = &mgresultboard_seOnTbl[0];
            if (*played == 0) {
                mgresultboard_seIdTbl[0] = HuAudFXPlay(0x11E);
                *played = 1;
            }
        } else {
            played = &mgresultboard_seOnTbl[1];
            if (*played == 0) {
                mgresultboard_seIdTbl[1] = HuAudFXPlay(0x11F);
                *played = 1;
            }
        }
    }
    mgresultboard_seStopDelay = 20;
}

void mgresultboard_FlipSeStop(void) {
    s32 i;

    if (mgresultboard_speed == 4.0f) {
        mgresultboard_seStopDelay = 0;
    }
    if (mgresultboard_seStopDelay > 0) {
        mgresultboard_seStopDelay--;
        return;
    }
    for (i = 0; i < 3; i++) {
        if (mgresultboard_seOnTbl[i] == 1) {
            HuAudFXStop(mgresultboard_seIdTbl[i]);
            mgresultboard_seOnTbl[i] = 0;
            HuAudFXPlay(0x15F);
        }
    }
}

const s32 mgresultboard_boardBackTbl[6] = { 4, 7, 10, 13, 16, 19 };

const u8 mgresultboard_rankFaceTbl[4] = { 1, 0, 0, 2 };
