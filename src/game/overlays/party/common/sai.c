#include "common_board.h"
#include "sai.h"
#include "pause.h"
#include "player.h"
#include "move.h"
#include "back.h"
#include "main.h"
#include "vibrate.h"
#include "window.h"
#include "coinchange.h"
#include "status.h"
#include "model.h"
#include "item.h"

typedef struct UnkDice2 {
    s32 unk0;
    s32 unk4;
} UnkDice2;

typedef struct UnkSharedBoard {
    s32 playerNo;
    s32 unk_04;
    char unk_08[8];
} UnkSharedBoard; //sizeof 0x10

typedef struct UnkCoinProc {
    /* 0x00 */ s32  playerNo;
    /* 0x04 */ s32  state;
    /* 0x08 */ s32  unk_08;    // item ID; also indexes mbItemIconSprTbl
    /* 0x0C */ char unk_0C[4];
} UnkCoinProc;

typedef struct UnkSharedBoard2 {
    char unk_00[0xC];
    Vec unk_0C;
} UnkSharedBoard2;

s32 mbSaiMdlTbl[6] = { 0x130207, 0x130207, 0x130207, 0x130207, 0x130207, 0x130208 };
s32 mbSaiAnimTbl[6] = { 0x1300FE, 0x130206, 0x1301E7, 0x130266, 0x1301E8, 0x13020B };
s32 mbSaiSeF = 1;
s16 mbSaiNumMultiPosTbl[3][2] = {
    { 110, 64 },
    { 210, 64 },
    { 160, 64 }
};

extern u8 mbKakusiWaitF;
extern f32 Hu3DVtxWaveAngle;
extern u8 mbSaiRotDir;
extern s8 mbSaiIdleF;
extern u8 mbSaiNum;
extern f32 mbSaiHeight;
extern u8 mbSaiMode;
extern u8 mbSaiDispF;

static void MBSaiNumPosSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void MBSaiSePlay(s32 arg0) {
    SaiWork* temp_s0;

    temp_s0 = &mbSaiWorkTbl[arg0];
    if ((temp_s0->unk28 == -1) && (temp_s0->dice->work[0] == 1)) {
        temp_s0->unk28 = HuAudFXPlay(0x100);
    }
}

static void MBSaiObjMain(omObjData *arg0) {
    SaiWork *entry;
    f32 base;
    f32 scale;
    f32 decay;
    s32 i;

    entry = &mbSaiWorkTbl[arg0->work[3]];
    if (mbSaiMode == 1) {
        base = 1.0f;
    } else {
        base = 0.1f;
    }

    switch (arg0->work[0]) {
        case 0:
            if (Hu3DPauseF != 0) {
                return;
            }
            arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbSaiHeight;

            scale = (sindf(arg0->work[1] * 2) * entry->unk48 * base) + base;
            arg0->scale.x = arg0->scale.y = arg0->scale.z = scale;

            if (mbSaiRotDir == 0) {
                arg0->rot.y += 22.5f;
            } else {
                arg0->rot.y -= 22.5f;
            }
            arg0->work[1] = (arg0->work[1] + 25) % 180;

            decay = entry->unk48 - 0.05;
            entry->unk48 = decay;
            if (decay <= 0.0f) {
                entry->unk48 = 0.0f;
                arg0->scale.x = arg0->scale.y = arg0->scale.z = base;
                arg0->work[1] = 0;
                arg0->work[0] = 1;

                if (mbSaiMode == 1) {
                    for (i = 0; i < 4; i++) {
                        if (mbSaiWorkTbl[i].unk28 != -1) {
                            break;
                        }
                    }
                    
                    if (i == 4) {
                        if (GwSystem.current_board_index == 8) {
                            return;
                        } else {
                            entry->unk28 = HuAudFXPlay(0x100);
                            return;
                        }
                    }
                    entry->unk28 = mbSaiWorkTbl[i].unk28;
                } else if ((entry->unk2A == 0) && (entry->unk_0A != 5) &&
                           (mbSaiMode != 2) &&
                           (mbSaiDispF != 0)) {
                    entry->unk28 = HuAudFXPlay(0x100);
                    return;
                }
            }
            break;

        case 1:
            if (Hu3DPauseF == 0) {
                arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y
                              + mbSaiHeight
                              + (sindf(arg0->work[1] * 2) * 10.0f * base);
                arg0->work[1] = (arg0->work[1] + 5) % 180;
                return;
            }
            break;

        case 2:
            Hu3DVtxWaveAngle = entry->unk48;
            Hu3DModelObjAttrSet(*arg0->model, 0x22000, 0x20000);
            Hu3DModelVtxWave(*arg0->model, entry->unk40, entry->unk44, 2);
            if (Hu3DPauseF == 0) {
                entry->unk48 += 39.0f;
                entry->unk40 += 0.05f;
                entry->unk44 = ((10.0f - entry->unk44) / 30.0f) + entry->unk44;
                if (entry->unk40 > 1.0f) {
                    MBSaiKill(arg0->work[3]);
                }
            }
            break;
    }
}

static void MBSaiNumObjMain(omObjData *arg0) {
    SaiWork *entry;
    Vec pos;
    f32 pos2d[2];
    f32 scale;
    u32 roll;

    entry = &mbSaiWorkTbl[arg0->work[3]];

    if ((arg0->work[0] == 0) && (Hu3DPauseF == 0)) {
        arg0->scale.x = (sindf(arg0->rot.x) * arg0->scale.z) + 1.0f;
        arg0->rot.x += 20.0f;
        arg0->scale.z -= 0.15;

        if (arg0->rot.x >= 360.0f) {
            arg0->rot.x -= 360.0f;
        }
        if (arg0->scale.z <= 0.0f) {
            arg0->scale.x = 1.0f;
            arg0->work[0] = 1;
        }
    }

    HuSprScaleSet(entry->sprites[arg0->work[1]], 0, arg0->scale.x / 2.0f, arg0->scale.x / 2.0f);
    HuSprScaleSet(entry->sprites[arg0->work[1]], 1, arg0->scale.x / 2.0f, arg0->scale.x / 2.0f);

    roll = arg0->work[1];
    HuSprBankSet(entry->sprites[roll], 0, entry->rollValue[roll] % 10, 0);
    HuSprAnimModeSet(entry->sprites[arg0->work[1]], 0, HUSPR_ANIM_MODE_BANK);

    roll = arg0->work[1];
    HuSprBankSet(entry->sprites[roll], 1, entry->rollValue[roll] / 10, 0);
    HuSprAnimModeSet(entry->sprites[arg0->work[1]], 1, HUSPR_ANIM_MODE_BANK);

    pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbSaiHeight + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBCamera3Dto2D(&pos, pos2d);

    HuSprPosSet(entry->sprites[arg0->work[1]], 0, pos2d[0], pos2d[1] - 8.0f);

    if ((pos2d[0] >= 0.0f) && (pos2d[0] <= 320.0f) &&
        (pos2d[1] >= 0.0f) && (pos2d[1] <= 240.0f)) {
        MBSaiNumPosSet(arg0->work[3], arg0->work[1], 160,
                                         120 - (s32)(MBCameraZoomGet() * 24.0f));
    }
}

static void MBSaiNumSingleObjMain(omObjData *arg0) {
    SaiWork *entry;
    Vec pos;
    f32 pos2d[2];
    f32 scale;
    s8 roll;

    entry = &mbSaiWorkTbl[arg0->work[3]];

    if ((arg0->work[0] == 0) && (Hu3DPauseF == 0)) {
        arg0->scale.x = (sindf(arg0->rot.x) * arg0->scale.z) + 1.0f;

        arg0->rot.x += 20.0f;
        if (arg0->rot.x >= 360.0f) {
            arg0->rot.x -= 360.0f;
        }

        arg0->scale.z -= 0.05;
        if (arg0->scale.z <= 0.0f) {
            arg0->scale.x = 1.0f;
            arg0->work[0] = 1;
        }
    }

    HuSprScaleSet(entry->sprites[entry->rollValueIdx], 0, arg0->scale.x, arg0->scale.x);

    roll = entry->rollValueIdx;
    HuSprBankSet(entry->sprites[roll], 0, entry->rollValue[roll], 0);
    HuSprAnimModeSet(entry->sprites[entry->rollValueIdx], 0, HUSPR_ANIM_MODE_BANK);

    pos.x = GwPlayer[arg0->work[3]].player_obj->coords.x;
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbSaiHeight + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBCamera3Dto2D(&pos, pos2d);

    HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, pos2d[0], pos2d[1]);
}

void MBSaiValueClear(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < DICE_TOTAL; j++) {
            mbSaiWorkTbl[i].rollValue[j] = 0;
            mbSaiWorkTbl[i].predecidedRollValue[j] = 0;
        }
    }
    mbSaiTriple7F = 0;
}

void MBSaiInit(void) {
    SaiWork *entry;
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        entry = &mbSaiWorkTbl[i];

        for (j = 0; j < DICE_TOTAL; j++) {
            entry->sprites[j] = -1;
            entry->predecidedRollValue[j] = 0;
        }

        entry->rollValueIdx = 0;
        entry->unk_16 = -1;
        entry->unk_18 = -1;
        entry->unk_30 = NULL;
        entry->unk_26 = -1;
        entry->unk_14 = -1;
        entry->unk_0C = 0;
        entry->dice = NULL;
        entry->unk_38 = NULL;
        entry->omObj = NULL;
        entry->unk_0B = 0;
        entry->unk28 = -1;
        entry->unk2A = 0;
        entry->unk_09 = -1;
    }

    mbSaiMode = 0;
    mbSaiIdleF = 1;
    mbSaiHeight = 25.0f;
    mbSaiDispF = 1;
    mbSaiNum = 1;
}

void MBSaiNumSprCreate(s32 arg0) {
    SaiWork *entry;
    void *data;
    s32 i;

    entry = &mbSaiWorkTbl[arg0];

    if ((arg0 != 0) && (mbSaiWorkTbl[0].unk_14 != -1)) {
        entry->unk_14 = mbSaiWorkTbl[0].unk_14;
        mbSaiWorkTbl[0].unk_0C++;
    } else if ((entry->rollValueIdx == 0) || (mbSaiNum == 1)) {
        data = DataRead(0x13020D);
        entry->unk_14 = HuSprAnimRead(data);
        entry->unk_0C = 1;
        DataClose(data);
    }

    entry->sprites[entry->rollValueIdx] = HuSprGrpCreate(2, 5);

    for (i = 0; i < 2; i++) {
        HuSprGrpMemberSet(entry->sprites[entry->rollValueIdx], i, entry->unk_14, 0);
        HuSprPriSet(entry->sprites[entry->rollValueIdx], i, 0x4000);
        HuSprAttrSet(entry->sprites[entry->rollValueIdx], i, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
        HuSprSpeedSet(entry->sprites[entry->rollValueIdx], i, 0.0f);
        HuSprScaleSet(entry->sprites[entry->rollValueIdx], i, 0.0f, 0.0f);
        HuSprBankSet(entry->sprites[entry->rollValueIdx], i, 0, 0);
        HuSprAnimModeSet(entry->sprites[entry->rollValueIdx], i, HUSPR_ANIM_MODE_BANK);
    }

    entry->unk_0B = 1;
}

void MBSaiNumShow(s32 arg0) {
    SaiWork *entry;
    omObjData *obj;
    Vec pos;
    f32 pos2d[2];
    s8 roll;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->rollValue[entry->rollValueIdx] != 0) {
        if ((entry->dice == NULL) || (entry->dice->work[0] == 2)) {
            pos.x = GwPlayer[arg0].player_obj->coords.x;
            pos.y = GwPlayer[arg0].player_obj->coords.y + mbSaiHeight;
            pos.z = GwPlayer[arg0].player_obj->coords.z;
            MBCamera3Dto2D(&pos, pos2d);

            if (entry->sprites[entry->rollValueIdx] == -1) {
                MBSaiNumSprCreate(arg0);
                entry->unk_0B = 0;
            } else {
                roll = entry->rollValueIdx;
                HuSprBankSet(entry->sprites[roll], 0, entry->rollValue[roll], 0);
                HuSprPriSet(entry->sprites[entry->rollValueIdx], 0, 0x4000);
                HuSprAnimModeSet(entry->sprites[entry->rollValueIdx], 0, HUSPR_ANIM_MODE_BANK);
            }

            if ((MBOvlCallCheck() == 0) && (mbSaiMode == 0)) {
                MBSaiNumPosSet(arg0, entry->rollValueIdx, pos2d[0], pos2d[1] - 8.0f);
            } else {
                HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, pos2d[0], pos2d[1]);
            }

            if ((pos2d[0] >= 0.0f) && (pos2d[0] <= 320.0f) &&
                (pos2d[1] >= 0.0f) && (pos2d[1] <= 240.0f)) {
                HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, 160,
                                    120 - (s32)(MBCameraZoomGet() * 24.0f));
            }

            HuSprDispOn(entry->sprites[entry->rollValueIdx], 0);

            if (entry->omObj == NULL) {
                if ((MBOvlCallCheck() == 0) && (mbSaiMode == 0)) {
                    obj = omAddObj(-0x8000, 0, 0, -1, MBSaiNumObjMain);
                    entry->omObj = obj;
                    obj->scale.z = 3.0f;
                    obj->work[1] = entry->rollValueIdx;
                } else {
                    obj = omAddObj(-0x8000, 0, 0, -1, MBSaiNumSingleObjMain);
                    entry->omObj = obj;
                    obj->scale.z = 1.0f;
                }
                obj->work[0] = 0;
                obj->work[3] = arg0;
                obj->scale.x = 0.0f;
                obj->rot.x = 270.0f;
                obj->trans.y = 0.0f;
            }
        }
    }
}

static void MBSaiValueDecide(s32 arg0) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    s8 forcedRoll;
    s32 i;

    if ((entry->unk_0B == 0) ) {
        if ((entry->rollValueIdx == 0)) {
            MBSaiNumKill(arg0);
        }
    }

    entry->unk_0B = 0;

    if (mbSaiMode == 1) {
        do {
            if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                entry->predecidedRollValue[entry->rollValueIdx] = 0;
            } else {
                entry->rollValue[entry->rollValueIdx] = (rand8() % 10) + 1;
            }

            for (i = 0; i < 5; i++) {
                if (i == arg0) {
                    continue;
                }
                if (mbSaiWorkTbl[i].rollValue[mbSaiWorkTbl[i].rollValueIdx] == entry->rollValue[entry->rollValueIdx]) {
                    break;
                }
            }
        } while (i != 5);
    } else {
        switch (entry->unk_0A) {
            case 0:
            case 1:
            case 2:
            case 4:
                forcedRoll = entry->predecidedRollValue[entry->rollValueIdx];
                if (forcedRoll != 0) {
                    entry->rollValue[entry->rollValueIdx] = forcedRoll;
                    entry->predecidedRollValue[entry->rollValueIdx] = 0;
                } else {
                    entry->rollValue[entry->rollValueIdx] = (rand8() % 10) + 1;
                }
                break;

            case 3:
                entry->rollValue[entry->rollValueIdx] = (rand8() % 3) + 1;
                break;

            case 5:
                entry->rollValue[entry->rollValueIdx] = 0;
                break;
        }
    }

    MBSaiNumShow(arg0);
}

void MBSaiNumObjKill(s32 arg0) {
    SaiWork* dice = &mbSaiWorkTbl[arg0];

    if (dice->omObj != NULL) {
        omDelObj(dice->omObj);
        dice->omObj = NULL;
    }
}

s32 MBSaiNumKill(s32 arg0) {
    s32 count = 0;
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    s32 i;

    for (i = 0; i < DICE_TOTAL; i++) {
        if (entry->sprites[i] != -1) {
            count++;
            HuSprGrpKill(entry->sprites[i]);
            entry->sprites[i] = -1;
        }
    }

    if (entry->unk_14 != -1) {
        if (entry->unk_0C != 0) {
            entry->unk_0C--;
            if (entry->unk_0C == 0) {
                HuSprAnimKill(entry->unk_14);
                entry->unk_14 = -1;
            }
        }
        count++;
    }

    if (entry->omObj != NULL) {
        omDelObj(entry->omObj);
        entry->omObj = NULL;
        count++;
    }

    return count;
}

void MBSaiNumCountDown(s32 arg0) {
    SaiWork* dice = &mbSaiWorkTbl[arg0];

    dice->rollValue[dice->rollValueIdx]--;
    if (dice->rollValue[dice->rollValueIdx] <= 0) {
        MBSaiNumKill(arg0);
    }
}

void MBSaiMdlDispOff(s32 arg0) {
    if (mbSaiWorkTbl[arg0].unk_16 != -1) {
        Hu3DModelAttrSet(mbSaiWorkTbl[arg0].unk_16, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void MBSaiDispOff(s32 arg0) {
    mbSaiDispF = 0;
    MBSaiMdlDispOff(arg0);
}

void MBSaiMdlDispOn(s32 arg0) {
    if (mbSaiDispF != 0) {
        if (mbSaiWorkTbl[arg0].unk_16 != -1) {
            Hu3DModelAttrSet(mbSaiWorkTbl[arg0].unk_16, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
    }
}

void MBSaiDispOn(s32 arg0) {
    mbSaiDispF = 1;
    MBSaiMdlDispOn(arg0);
}

void MBSaiTypeSet(s32 arg0, s8 arg1) {
    mbSaiWorkTbl[arg0].unk_09 = arg1;
}

s16 MBSaiCreate(s32 arg0) {
    SaiWork *entry;
    omObjData *dice;
    f32 chance;
    s8 mode;
    s8 val;
    s16 sound;
    s32 rot;
    s32 tile;
    s32 i;
    s16 ret;
    s32* temp;

    mbSaiRotDir = 0;
    entry = &mbSaiWorkTbl[arg0];
    
    if (entry->unk_16 != -1) {
        return -1;
    }
    
    if (entry->rollValueIdx == 0) {
        MBSaiNumKill(arg0);
    }

    if (entry->unk_09 != -1) {
        entry->unk_0A = entry->unk_09;
        entry->unk_09 = -1;
    } else {
        entry->unk_0A = 0;
        if (GWBoardFlagCheck(0x10) != 0) {
            entry->unk_0A = 3;
            GWBoardFlagClear(0x10);
        }
        if (mbSaiNum == 2) {
            entry->unk_0A = 2;
        } else if (mbSaiNum == 3) {
            entry->unk_0A = 4;
            if (entry->rollValueIdx == 0) {
                if (mbSaiTriple7F != 0) {
                    chance = 6.0f;
                } else {
                    chance = 10.0f;
                }
                if (MBRand(chance) == 0) {
                    val = (rand8() % 10) + 1;
                    entry->predecidedRollValue[1] = val;
                    entry->predecidedRollValue[0] = val;
                    mbSaiRotDir = 1;
                }
            }
        }
        if (GWBoardFlagCheck(0x11) != 0) {
            entry->unk_0A = 5;
        }
    }

    entry->unk_16 = Hu3DModelCreate(DataRead(mbSaiMdlTbl[entry->unk_0A]), 0x6A9);
    Hu3DModelCameraSet(entry->unk_16, HU3D_CAM0);
    Hu3DModelScaleSet(entry->unk_16, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(entry->unk_16, 0x20000, 0x20000);

    if (entry->unk_0A != 5) {
        entry->unk_2C = DataRead(mbSaiAnimTbl[entry->unk_0A]);
        entry->unk_1A[0] = Hu3DAnimCreate(Hu3DData[entry->unk_16].hmf, entry->unk_2C, 0, "tile01_DEF");
        entry->unk_1A[1] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile02_DEF");
        entry->unk_1A[2] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile03_DEF");
        entry->unk_1A[3] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile04_DEF");
        entry->unk_1A[4] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile06_DEF");
        entry->unk_1A[5] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile10_DEF");

        tile = rand8() % 10;
        rot = rand8() & 3;
        for (i = 0; i < 6; i++) {
            if ((entry->unk_0A < 3)) {
                if ((entry->unk_0A >= 0)) {
                    Hu3DAnimBankSet(entry->unk_1A[i], rot);
                }
            }
            Hu3DAnmNoSet(entry->unk_1A[i], tile);
        }
    } else {
        entry->unk_2C = NULL;
        for (i = 0; i < 6; i++) {
            entry->unk_1A[i] = -1;
        }
        Hu3DMotionAttrSet(entry->unk_16, 0, 2);
    }

    Hu3DModelRemakeStatic(entry->unk_16);
    Hu3DModelVtxBufMake(entry->unk_16);

    dice = omAddObj(-0x8000, 1, 1, -1, MBSaiObjMain);
    entry->dice = dice;
    *dice->model = entry->unk_16;
    omSetStatBit(dice, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);

    dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
    dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbSaiHeight;
    dice->trans.z = GwPlayer[arg0].player_obj->coords.z;

    if (mbSaiRotDir == 0) {
        dice->rot.y = -90.0f;
    } else {
        dice->rot.y = 90.0f;
    }
    dice->scale.z =
    dice->scale.y =
    dice->scale.x =
    dice->rot.x =
    dice->rot.z = 0.0f;
    dice->work[0] = 0;
    dice->work[1] = 0x87;
    dice->work[2] = 0;
    dice->work[3] = arg0;

    entry->unk48 = 1.0f;
    entry->unk40 = 0.0f;
    entry->unk44 = 1.0f;

    mbSaiMode = 0;
    ret = -1;
    if (mbSaiSeF != 0) {
        switch (entry->unk_0A) {
            case 0:
                if (mbSaiMode != 2) {
                    ret = HuAudFXPlay(0x102);
                } else {
                    HuAudFXPlay(0x10E);
                }
                break;
            case 1:
                HuAudFXPlay(0x102);
                break;
            case 2:
                HuAudFXPlay(0x111);
                break;
            case 3:
                HuAudFXPlay(0x102);
                break;
            case 4:
                HuAudFXPlay(0x110);
                break;
            case 5:
                HuAudFXPlay(0x10F);
                break;
            default:
                HuAudFXPlay(0x10E);
                break;
        }
    }

    mbSaiSeF = 1;
    return ret;
}

static void MBSaiCreateEx(s32 arg0, s32 arg1, s32 arg2, char *arg3[]) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    omObjData *dice;
    f32 height;
    s32 i;

    if (entry->unk_16 == -1) {
        if (mbSaiMode == 1) {
            mbSaiHeight = 250.0f;
        } else {
            mbSaiHeight = 25.0f;
        }

        MBSaiNumKill(arg0);
        entry->unk_0A = 0;

        entry->unk_16 = Hu3DModelCreate(DataRead(arg1), 0x6A9);
        Hu3DModelCameraSet(entry->unk_16, HU3D_CAM0);
        Hu3DModelScaleSet(entry->unk_16, 0.0f, 0.0f, 0.0f);
        Hu3DModelObjAttrSet(entry->unk_16, 0x20000, 0x20000);
        
        
        if (arg2 != -1) {
            entry->unk_2C = DataRead(arg2);
        } else {
            entry->unk_2C = NULL;
        }

        for (i = 0; i < 6; i++) {
            if (arg3[i] != 0) {
                if (i == 0) {
                    entry->unk_1A[0] = Hu3DAnimCreate(Hu3DData[entry->unk_16].hmf, entry->unk_2C, 0, arg3[0]);
                } else {
                    entry->unk_1A[1] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, arg3[i]);
                }
            } else {
                entry->unk_1A[i] = -1;
            }
        }

        Hu3DModelRemakeStatic(entry->unk_16);
        Hu3DModelVtxBufMake(entry->unk_16);
        mbSaiRotDir = 0;

        dice = omAddObj(-0x8000, 1, 1, -1, MBSaiObjMain);
        entry->dice = dice;
        dice->model[0] = entry->unk_16;
        omSetStatBit(dice, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbSaiHeight;
        dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
        dice->rot.y = -90.0f;
        dice->scale.z =
        dice->scale.y =
        dice->scale.x =
        dice->rot.x =
        dice->rot.z = 0.0f;
        dice->work[0] = 0;
        dice->work[1] = 0x87;
        dice->work[2] = 0;
        dice->work[3] = arg0;

        entry->unk48 = 1.0f;
        entry->unk40 = 0.0f;
        entry->unk44 = 1.0f;

        HuAudFXPlay(0x10E);
    }
}

static void MBSaiBlankCreate(s32 arg0) {
    char* anims[6] =  {NULL, NULL, NULL, NULL, NULL, NULL}; //TODO: is this right?

    MBSaiCreateEx(arg0, 0x1301FB, -1, anims);
    mbSaiMode = 2;
}

s32 const pad2[2] = {0 , 0};

void MBSaiKill(s32 arg0) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    s16 id;
    s32 i;

    if (entry->unk_16 != -1) {
        Hu3DModelKill(entry->unk_16);
        for (i = 0; i < 6; i++) {
            if (entry->unk_1A[i] != -1) {
                Hu3DAnimModelKill(entry->unk_1A[i]);
            }
        }
        if (entry->unk_2C != NULL) {
            DataClose(entry->unk_2C);
        }
        omDelObj(entry->dice);
        entry->dice = NULL;
        entry->unk_16 = -1;
    }

    if (entry->unk_18 != -1) {
        Hu3DModelKill(entry->unk_18);
        entry->unk_18 = -1;
        if (entry->unk_38 != NULL) {
            omDelObj(entry->unk_38);
            entry->unk_38 = NULL;
        }
    }

    if (entry->unk_26 != -1) {
        Hu3DAnimModelKill(entry->unk_26);
        entry->unk_26 = -1;
    }

    if (entry->unk_30 != NULL) {
        DataClose(entry->unk_30);
        entry->unk_30 = NULL;
    }
}

void MBSaiClose(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        MBSaiKill(i);
        MBSaiNumKill(i);
    }
}

void MBSaiHit(s32 arg0) {
    SaiWork *entry;
    s16 sound;
    s32 count;
    s32 i;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->unk_16 != -1) {
        entry->dice->work[0] = 2;

        if (mbSaiMode != 2) {
            MBSaiValueDecide(arg0);
        }

        
        if (mbSaiMode == 1) {
            count = 0;
            for (i = 0; i < 4; i++) {
                if (mbSaiWorkTbl[i].unk28 != -1) {
                    count++;
                }
            }
        } else {
            count = 1;
        }

        if (count == 1) {
            HuAudFXStop(entry->unk28);
        }
        entry->unk28 = -1;
        entry->unk2A = 0;

        if ((mbSaiMode == 2) || (entry->unk_0A == 5)) {
            HuAudFXPlay(0x10D);
        } else {
            HuAudFXPlay(0x103);
        }
        
    }
}

void MBSaiOrderModeSet(void) {
    mbSaiMode = 1;
    mbSaiHeight = 250.0f;
}

s32 MBSaiExistCheck(s32 arg0) {
    if (~mbSaiWorkTbl[arg0].unk_16) {
        return 1;
    } else {
        return 0;
    }
}

void MBSaiValueSet(s32 arg0, s32 arg1) {
    mbSaiWorkTbl[arg0].rollValue[mbSaiWorkTbl[arg0].rollValueIdx] = arg1;
}

void MBSaiValueForceSet(s32 arg0, s32 arg1) {
    mbSaiWorkTbl[arg0].predecidedRollValue[mbSaiWorkTbl[arg0].rollValueIdx] = arg1;
}

s32 MBSaiValueGet(s32 arg0) {
    return mbSaiWorkTbl[arg0].rollValue[mbSaiWorkTbl[arg0].rollValueIdx];
}

static void MBSaiPlayerProc(void) {
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f20_4;
    f32 temp_f20_5;
    f32 temp_f20_6;
    f32 temp_f20_7;
    f32 temp_f20_8;
    f32 temp_f20_9;
    f32 temp_f20_10;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    s16 var_a0;
    s16 var_a1;
    s32 temp_s0;
    s32 var_s1;
    s32 var_s5;
    s32 i, j;
    UnkDice2 *temp_s3;
    SaiWork *temp_s4;
    var_s1 = 0;
    temp_s3 = HuPrcCurrentGet()->user_data;
    temp_s4 = &mbSaiWorkTbl[temp_s3->unk0];
    var_s5 = 0;
    while (1) {
        switch (temp_s3->unk4) {
            case 0:
                mbSaiIdleF = 0;
                MBSaiCreate(temp_s3->unk0);
                mbSaiIdleF = 1;
                temp_s3->unk4++;
                HuPrcSleep(0x14);
                break;
            case 1:
                if (((GwPlayer[temp_s3->unk0].stat & PLAYER_IS_CPU) || (HuPadBtnDown[GwPlayer[temp_s3->unk0].pad] & A_BUTTON)) && !(Hu3DData[mbSaiWorkTbl[temp_s3->unk0].unk_16].attr & 4) && (GWBoardFlagCheck(0x11) == 0)) {
                    temp_s3->unk4++;
                    MBPlayerMotionSet(temp_s3->unk0, 2, 0);
                    MBModelJumpSet(GwPlayer[temp_s3->unk0].player_obj, 2.0f, -0.3f);
                    mbCameraBtnF = 0;
                    mbSaiBtnF = 0;
                }
                break;
            case 2:
                if (++var_s1 >= 5) {
                    MBSaiHit(temp_s3->unk0);
                    MBPlayerMotionShiftSet(temp_s3->unk0, -1, 0, 0xA, 2);
                    temp_s3->unk4++;
                }
                break;
            case 3:
                HuPrcSleep(20);
                var_s5++;
                if (var_s5 != mbSaiNum) {
                    HuPrcSleep(10);
                    var_s1 = 0;
                    MBSaiNumObjKill(temp_s3->unk0);
                    {
                        s16 *temp0 = &mbSaiNumMultiPosTbl[var_s5-1][0];
                        s16 *temp1 = &mbSaiNumMultiPosTbl[var_s5-1][1];
                        MBSaiNumPosSet(temp_s3->unk0, temp_s4->rollValueIdx, *temp0, *temp1);
                    }
                    temp_s4->rollValueIdx++;
                    temp_s3->unk4 = 0;
                } else {
                    if (mbSaiNum != 1) {
                        HuPrcSleep(10);
                        MBSaiNumObjKill(temp_s3->unk0);
                        {
                            s16 *temp0 = &mbSaiNumMultiPosTbl[var_s5-1][0];
                            s16 *temp1 = &mbSaiNumMultiPosTbl[var_s5-1][1];
                            MBSaiNumPosSet(temp_s3->unk0, temp_s4->rollValueIdx, *temp0, *temp1);
                        }
                        HuPrcSleep(20);
                        if (mbSaiNum == 2) {
                            if (temp_s4->rollValue[0] != temp_s4->rollValue[1]) {
                            } else {
                                HuAudFXPlay(0x15D);
                                if (temp_s4->rollValue[0] == 7) {
                                    MBPlayerVibrate(-1, 3);
                                } else {
                                    MBPlayerVibrate(-1, 2);
                                }
                                for (j = 0; j < 37; j++) {
                                    temp_f22 = (f32)(((j * 4) + j) * 4);
                                    temp_f20 = (sindf(temp_f22) * 0.5f) + 1.0f;
                                    HuSprScaleSet(temp_s4->sprites[0], 0, temp_f20, (sindf(temp_f22) * 0.5f) + 1.0f);
                                    temp_f20_2 = (sindf(temp_f22) * 0.5f) + 1.0f;
                                    HuSprScaleSet(temp_s4->sprites[1], 0, temp_f20_2, (sindf(temp_f22) * 0.5f) + 1.0f);
                                    if (temp_s4->rollValue[0] == 0xA) {
                                        temp_f20_3 = (sindf(temp_f22) * 0.5f) + 1.0f;
                                        HuSprScaleSet(temp_s4->sprites[0], 1, temp_f20_3, (sindf(temp_f22) * 0.5f) + 1.0f);
                                        temp_f20_4 = (sindf(temp_f22) * 0.5f) + 1.0f;
                                        HuSprScaleSet(temp_s4->sprites[1], 1, temp_f20_4, (sindf(temp_f22) * 0.5f) + 1.0f);
                                    }
                                    HuPrcVSleep();
                                }
                                if (temp_s4->rollValue[0] == 7) {
                                    MBDlgWinExec(0x16, 0x3A24);
                                    MBCoinChangeCreate(temp_s3->unk0, 20);
                                    MBCoinTakeCreate(temp_s3->unk0, 20);
                                } else {
                                    MBDlgWinExec(0x16, 0x3A26);
                                    MBCoinChangeCreate(temp_s3->unk0, 10);
                                    MBCoinTakeCreate(temp_s3->unk0, 10);
                                }
                                PlayerFXPlay(0x274, temp_s3->unk0);
                                MBPlayerMotionSet(temp_s3->unk0, 5, 0);
                                HuPrcSleep(0x1E);
                                MBPlayerMotionSet(temp_s3->unk0, -1, 2);
                            }
                        } else {
                            if (mbSaiNum == 3) {
                                if ((temp_s4->rollValue[0] == temp_s4->rollValue[1]) && (temp_s4->rollValue[0] == temp_s4->rollValue[2])) {
                                    if (temp_s4->rollValue[0] == 7) {
                                        mbItemBtnF = 0;
                                        HuAudFXPlay(0x15E);
                                        HuAudSeqVolFadeOut(0);
                                        HuAudSubSeqPlayMute(0x69);
                                        HuAudSubSeqVolFadeIn(0);
                                        HuAudSubSeqParamSet(0xF);
                                        MBPlayerVibrate(-1, 4);
                                    } else {
                                        HuAudFXPlay(0x15D);
                                        MBPlayerVibrate(-1, 3);
                                    }
                                    for (i = 0; i < 73; i++, HuPrcVSleep()) {
                                        var_s1 = i;
                                        temp_s0 = (i * 4) + var_s1;
                                        temp_f24 = (f32)(temp_s0 * 4);
                                        temp_f20_5 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                        HuSprScaleSet(temp_s4->sprites[0], 0, temp_f20_5, (sindf(temp_s0) * 0.5f) + 1.0f);
                                        temp_f20_6 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                        HuSprScaleSet(temp_s4->sprites[1], 0, temp_f20_6, (sindf(temp_s0) * 0.5f) + 1.0f);
                                        temp_f20_7 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                        HuSprScaleSet(temp_s4->sprites[2], 0, temp_f20_7, (sindf(temp_s0) * 0.5f) + 1.0f);
                                        if (temp_s4->rollValue[0] == 0xA) {
                                            temp_f20_8 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                            HuSprScaleSet(temp_s4->sprites[0], 1, temp_f20_8, (sindf(temp_s0) * 0.5f) + 1.0f);
                                            temp_f20_9 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                            HuSprScaleSet(temp_s4->sprites[1], 1, temp_f20_9, (sindf(temp_s0) * 0.5f) + 1.0f);
                                            temp_f20_10 = (sindf(temp_f24) * 0.5f) + 1.0f;
                                            HuSprScaleSet(temp_s4->sprites[2], 1, temp_f20_10, (sindf(temp_s0) * 0.5f) + 1.0f);
                                        }
                                    }
                                    if (temp_s4->rollValue[0] == 7) {
                                        MBDlgWinExec(0x16, 0x3A25);
                                        MBCoinChangeCreate(temp_s3->unk0, 50);
                                        MBCoinTakeCreate(temp_s3->unk0, 50);
                                        mbSaiTriple7F = 1;
                                    } else {
                                        MBDlgWinExec(0x16, 0x3A24);
                                        MBCoinChangeCreate(temp_s3->unk0, 20);
                                        MBCoinTakeCreate(temp_s3->unk0, 20);
                                    }
                                    PlayerFXPlay(0x274, temp_s3->unk0);
                                    MBPlayerMotionSet(temp_s3->unk0, 5, 0);
                                    HuPrcSleep(0x1E);
                                    if (temp_s4->rollValue[0] == 7) {
                                        mbItemBtnF = 1;
                                    }
                                    MBPlayerMotionSet(temp_s3->unk0, -1, 2);
                                }
                            }
                        }
                        for (var_s1 = 0; var_s1 < 50; HuPrcVSleep(), var_s1 += 2) {
                            MBSaiNumPosSet(temp_s3->unk0, 0, mbSaiNumMultiPosTbl[0][0] + var_s1, mbSaiNumMultiPosTbl[0][1] + (var_s1 / 2));
                            MBSaiNumPosSet(temp_s3->unk0, 1, mbSaiNumMultiPosTbl[1][0] - var_s1, mbSaiNumMultiPosTbl[1][1] + (var_s1 / 2));
                            if (mbSaiNum == 3) {
                                MBSaiNumPosSet(temp_s3->unk0, 2, mbSaiNumMultiPosTbl[2][0], mbSaiNumMultiPosTbl[2][1] + (var_s1 / 2));
                            }
                        }
                        if (mbSaiNum == 2) {
                            HuAudFXPlay(0x140);
                        } else if (mbSaiNum == 3) {
                            HuAudFXPlay(0x146);
                        }
                        mbSaiNum = 1;
                        temp_s4->rollValueIdx = 0;
                        temp_s4->rollValue[0] += temp_s4->rollValue[1] + temp_s4->rollValue[2];
                        temp_s4->rollValue[2] = 0;
                        temp_s4->rollValue[1] = 0;
                        MBSaiNumKill(temp_s3->unk0);
                        MBSaiNumShow(temp_s3->unk0);
                        HuPrcSleep(20);
                    }
                    omDelPrcObj(0);
                }
                break;
        }
        HuPrcVSleep();
    }
}

Process* MBSaiPlayerCreate(s32 playerNo) {
    Process* proc = omAddPrcObj(MBSaiPlayerProc, 0, 0, 0x40);
    UnkSharedBoard* temp_v0_2 = HuMemMemoryAlloc(proc->heap, sizeof(UnkSharedBoard));

    proc->user_data = temp_v0_2;
    temp_v0_2->playerNo = playerNo;
    temp_v0_2->unk_04 = 0;
    return proc;
}

static void MBKakusiStarProc(void) {
    Vec sp10;
    GW_PLAYER* temp_s4;
    Object* temp_v0;
    Object* temp_v0_3;
    Vec* temp_a2;
    f32 var_f20;
    f32 var_f22;
    s32 temp_v0_2;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    UnkSharedBoard2* temp_s0;
    s32 i;

    temp_s0 = HuPrcCurrentGet()->user_data;
    temp_s4 = MBPlayerGet(CUR_PLAYER);
    HuAudFXPlay(0x11B);
    temp_v0 = MBModelCreate(0x1AU, NULL);
    temp_v0->flags |= 4;
    MBModelBillboardSet(temp_v0);
    HuVecCopyXYZ(&temp_v0->coords, temp_s0->unk_0C.x, temp_s0->unk_0C.y + 10.0f, temp_s0->unk_0C.z - 10.0f);
    HuVecCopyXYZ(&sp10, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
    temp_v0->velocity.x = 15.0f;
    temp_v0_2 = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(temp_v0_2, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(temp_v0_2, 15.0f);
    Hu3DModelCameraSet(temp_v0_2, HU3D_CAM0);
    EffectPosSet(temp_v0_2, temp_v0->coords.x, temp_v0->coords.y + temp_v0->velocity.x, temp_v0->coords.z);
    
    for (var_f20 = 0.0f, i = 0; i < 6; i++) {
        HuVecCopyXYZ(&temp_v0->scale, var_f20, var_f20, var_f20);
        var_f20 += 0.5f;
        EffectRangeSet(temp_v0_2, var_f20 * 15.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&temp_v0->scale, var_f20, var_f20, var_f20);
        var_f20 -= 0.4f;
        EffectRangeSet(temp_v0_2, var_f20 * 15.0f);
        HuPrcVSleep();
    }

    EffectRangeSet(temp_v0_2, var_f20 * 15.0f);
    HuPrcSleep(0x14);
    MBKakusiWaitOn();

    //? this seems overlay complex for how simple it is
    while (1) {
        if (mbKakusiWaitF != 0) {
            HuPrcVSleep();
        } else {
            break;
        }        
    }

    
    HuAudFXPlay(0x132);
    var_f22 = 0.0f;
    temp_v0_3 = temp_s4->player_obj;
    HuVecCopyXYZ(&sp10, temp_v0_3->coords.x, temp_v0_3->coords.y - 10.0f, temp_v0_3->coords.z);
    temp_a2 = &temp_v0->coords;
    MBPlayerPosMoveCreate(temp_a2, &sp10, temp_a2, 0x28);

    for (i = 0; i < 0x28; i++) {
        HuMtxRotYF(Hu3DData[temp_v0->omObj1->model[0]].mtx, var_f22);
        var_f22 += 20.0f;
        var_f20 -= 0.05f;
        
        if (var_f20 < 0.0f) {
            var_f20 = 0.0f;
        }
        HuVecCopyXYZ(&temp_v0->scale, var_f20, var_f20, var_f20);
        EffectRangeSet(temp_v0_2, var_f20 * 15.0f);
        EffectPosSet(temp_v0_2, temp_v0->coords.x, temp_v0->coords.y + temp_v0->velocity.x, temp_v0->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(temp_v0);
    EffectStop(temp_v0_2);
    MBPlayerVibrate(-1, 5);
    HuAudSeqVolFadeOut(0xE);

    GwPlayer[GwSystem.current_player_index].star++;

    if (GwPlayer[GwSystem.current_player_index].star > STARS_MAX) {
        GwPlayer[GwSystem.current_player_index].star = STARS_MAX;
    }
    
    MBVecForwardSet(&temp_s4->player_obj->rot);
    MBPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x262, GwSystem.current_player_index);
    HuPrcSleep(16);
    msmMusPause(HuAudMusNo);
    HuAudSubSeqPlayMute(0x6F);
    HuAudSubSeqVolFadeIn(0);
    HuPrcSleep(110);
    msmMusResume(HuAudMusNo, 0);
    HuAudSeqVolFadeIn(0xF);
    omDelPrcObj(NULL);
}

static void MBKakusiStarExec(void* arg0) {
    Process* temp_v0;

    mbItemBtnF = 0;
    temp_v0 = omAddPrcObj(MBKakusiStarProc, 0x4800U, 0, 0);
    temp_v0->user_data = arg0;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

static void MBKakusiStarBlockProc(void) {
    UnkCoinProc *work;
    s32 timer;

    work = HuPrcCurrentGet()->user_data;
    timer = 0;

    while (TRUE) {
        switch (work->state) {
            case 0:
                mbSaiIdleF = 0;
                MBSaiBlankCreate(work->playerNo);
                mbSaiIdleF = 1;
                work->state++;
                HuPrcSleep(20);
                break;

            case 1:
                if (mbKakusiWaitF == 0) {
                    work->state++;
                    MBPlayerMotionSet(work->playerNo, 2, 0);
                    MBModelJumpSet(GwPlayer[work->playerNo].player_obj, 2.0f, -0.3f);
                    mbCameraBtnF = 0;
                    mbSaiBtnF = 0;
                }
                break;

            case 2:
                timer++;
                if (timer >= 5) {
                    MBSaiHit(work->playerNo);
                    MBPlayerMotionShiftSet(work->playerNo, -1, 0, 10, 2);
                    work->state++;
                }
                break;

            case 3:
                MBKakusiStarExec(GwPlayer[work->playerNo].player_obj);
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process* MBKakusiStarBlockCreate(s32 arg0) {
    Process* temp_v0;
    UnkCoinProc* temp_v0_2;

    temp_v0 = omAddPrcObj(MBKakusiStarBlockProc, 0, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkCoinProc));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->playerNo = arg0;
    temp_v0_2->state = 0;
    mbKakusiWaitF = 0;
    return temp_v0;
}

static void MBKakusiItemBlockProc(void) {
    UnkCoinProc *work;
    f32 scale, amp, angle;
    s32 grp, anim, motion;
    s32 gotItem, timer, i;
    void *data;

    gotItem = 0;
    work = HuPrcCurrentGet()->user_data;
    timer = 0;

    while (TRUE) {
        switch (work->state) {
            case 0:
                mbSaiIdleF = 0;
                MBSaiBlankCreate(work->playerNo);
                mbSaiIdleF = 1;
                work->state++;
                HuPrcSleep(20);
                break;

            case 1:
                if (mbKakusiWaitF == 0) {
                    work->state++;
                    MBPlayerMotionSet(work->playerNo, 2, 0);
                    MBModelJumpSet(GwPlayer[work->playerNo].player_obj, 2.0f, -0.3f);
                    mbCameraBtnF = 0;
                    mbSaiBtnF = 0;
                }
                break;

            case 2:
                timer++;
                if (timer >= 5) {
                    MBSaiHit(work->playerNo);
                    MBPlayerMotionShiftSet(work->playerNo, -1, 0, 10, 2);
                    work->state++;
                }
                break;

            case 3:
                HuAudFXPlay(0x19);
                grp = HuSprGrpCreate(1, 5);
                data = DataRead(mbItemIconSprTbl[work->unk_08]);
                anim = HuSprAnimRead(data);
                DataClose(data);
                HuSprGrpMemberSet(grp, 0, anim, 0);
                HuSprPriSet(grp, 0, 0xB);
                HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
                HuSprAttrSet(grp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
                HuSprPosSet(grp, 0, 160, 90);
                HuSprTPLvlSet(grp, 0, 0);

                amp = 1.0f / sindf(20.0f);
                
                for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
                    //temp variables seem to not impact codegen?
                    f32 temp1 = sindf(angle) * amp * 0.8f + 0.2f;
                    f32 temp2 = sindf(angle) * amp * 0.8f + 0.2f;
                    HuSprScaleSet(grp, 0, temp1, temp2);
                    HuSprTPLvlSet(grp, 0, 0x100);
                    HuPrcVSleep();
                }
                
                while (angle > 20.0f) {
                    f32 temp1 = sindf(angle) * amp * 0.8f + 0.2f;
                    f32 temp2 = sindf(angle) * amp * 0.8f + 0.2f;
                    HuSprScaleSet(grp, 0, temp1, temp2);
                    HuPrcVSleep();
                    angle -= 11.25f;
                }
                HuSprScaleSet(grp, 0, 1.0f, 1.0f);
                HuSprTPLvlSet(grp, 0, 0x100);

                MBKakusiWaitOn();
                HuPrcSleep(5);
                while (!MBKakusiWaitCheck()) {
                    HuPrcVSleep();
                }
                MBKakusiWaitOff();
                HuPrcSleep(10);

                if (MBItemFindEmpty(work->playerNo) != -1) {
                    gotItem = 1;
                    GwPlayer[work->playerNo].itemNo[MBItemFindEmpty(work->playerNo)] = work->unk_08;
                    HuAudFXPlay(0x10);
                } else {
                    for (i = 1; i < 64; i++) {
                        HuSprTPLvlSet(grp, 0, 255.0f - (i * 3.984f));
                        HuPrcVSleep();
                    }
                    HuSprTPLvlSet(grp, 0, 0);
                }

                HuSprAnimKill(anim);
                HuSprGrpKill(grp);

                if (gotItem != 0) {
                    PlayerFXPlay(0x274, work->playerNo);
                    MBPlayerMotionSet(work->playerNo, 5, 0);
                } else {
                    PlayerFXPlay(0x286, work->playerNo);
                    MBPlayerMotionSet(work->playerNo, 3, 0);
                }
                
                MBPlayerMotionWait(work->playerNo);
                MBPlayerMotionShiftSet(work->playerNo, -1, 0, 10, 2);
                MBKakusiWaitOn();
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process* MBKakusiItemBlockCreate(s32 arg0, s32 arg1) {
    Process* temp_v0;
    UnkCoinProc* temp_v0_2;

    temp_v0 = omAddPrcObj(MBKakusiItemBlockProc, 0, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkCoinProc));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->playerNo = arg0;
    temp_v0_2->state = 0;
    temp_v0_2->unk_08 = arg1;
    mbKakusiWaitF = 0;
    return temp_v0;
}

static void MBKakusiCoinEffProc(void) {
    Object* temp_v0;
    Object* temp_s0;
    f32 var_f20;
    s32 i;
    
    temp_s0 = HuPrcCurrentGet()->user_data;
    temp_v0 = MBModelCreate(0x19U, NULL);
    HuVecCopyXYZ(&temp_v0->coords, temp_s0->coords.x, 0.0f, temp_s0->coords.z);
    HuVecCopyXYZ(&temp_v0->scale, 2.0f, 2.0f, 2.0f);
    temp_v0->velocity.x = 35.0f;
    var_f20 = (f32) MBRand(360.0f);

    for (i = 0; i < 5; i++) {
        HuPrcVSleep();
        temp_v0->velocity.x += 3.0f;
        var_f20 += 40.0f;
        HuMtxRotYF(Hu3DData[temp_v0->omObj1->model[0]].mtx, var_f20);
    }

    MBModelKill(temp_v0);
    omDelPrcObj(NULL);
}

static void MBKakusiCoinEffCreate(void* arg0) {
    omAddPrcObj(MBKakusiCoinEffProc, 0x4800, 0, 0)->user_data = arg0;
}

static void MBKakusiCoinBlockProc(void) {
    UnkCoinProc *work;
    s32 i;

    work = HuPrcCurrentGet()->user_data;

    while (TRUE) {
        switch (work->state) {
            case 0:
                mbSaiIdleF = 0;
                MBSaiBlankCreate(work->playerNo);
                mbSaiIdleF = 1;
                work->state++;
                HuPrcSleep(20);
                break;

            case 1:
                if (mbKakusiWaitF == 0) {
                    work->state++;
                    mbCameraBtnF = 0;
                    mbSaiBtnF = 0;
                }
                break;

            case 2:
                MBKakusiWaitOn();
                for (i = 0; i < 20; i++) {
                    MBPlayerMotionSet(work->playerNo, 2, 0);
                    MBModelJumpSet(GwPlayer[work->playerNo].player_obj, 8.0f, -2.4f);
                    HuPrcSleep(2);
                    MBKakusiCoinEffCreate(GwPlayer[work->playerNo].player_obj);
                    MBCoinTakeCreate(work->playerNo, 1);
                    if (i == 19) {
                        MBSaiHit(work->playerNo);
                    }
                    MBModelJumpWait(GwPlayer[work->playerNo].player_obj);
                }
                PlayerFXPlay(0x274, work->playerNo);
                MBPlayerMotionSet(work->playerNo, 5, 0);
                HuPrcSleep(30);
                MBPlayerMotionSet(work->playerNo, -1, 2);
                work->state++;
                break;

            case 3:
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process* MBKakusiCoinBlockCreate(s32 arg0) {
    Process* temp_v0;
    UnkCoinProc* temp_v0_2;

    temp_v0 = omAddPrcObj(MBKakusiCoinBlockProc, 0, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkCoinProc));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->playerNo = arg0;
    temp_v0_2->state = 0;
    mbKakusiWaitF = 0;
    return temp_v0;
}

u8 MBKakusiWaitCheck(void) {
    return mbKakusiWaitF;
}

void MBKakusiWaitOn(void) {
    mbKakusiWaitF = 1;
}

void MBKakusiWaitOff(void) {
    mbKakusiWaitF = 0;
}


void MBSaiSeStop(s32 arg0) {
    SaiWork* temp_s0 = &mbSaiWorkTbl[arg0];

    if (temp_s0->unk28 != -1) {
        HuAudFXStop(temp_s0->unk28);
        temp_s0->unk28 = -1;
    }
    temp_s0->unk2A = 1;
}

void MBSaiSeResume(s32 arg0) {
    SaiWork* temp_s0;
    
    temp_s0 = &mbSaiWorkTbl[arg0];
    if ((temp_s0->unk2A == 1) && (temp_s0->unk_16 != -1)) {
        if ((temp_s0->dice != NULL) && (temp_s0->dice->work[0] != 2) && (temp_s0->unk_0A != 5) && (mbSaiMode != 2)) {
            temp_s0->unk28 = HuAudFXPlay(0x100);
        }
    }
    temp_s0->unk2A = 0;
}

void MBSaiModeSet(s8 arg0) {
    mbSaiMode = arg0;
}

//unused
void MBSaiValueNoSet(s32 arg0, s32 arg1) {
    mbSaiWorkTbl[arg0].rollValueIdx = arg1;
}

void MBSaiNumSet(s32 arg0, s32 arg1) {
    mbSaiNum = arg1;
}

static void MBSaiNumPosSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    SaiWork *entry;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->rollValue[arg1] >= 10) {
        HuSprDispOn(entry->sprites[arg1], 1);
        HuSprPosSet(entry->sprites[arg1], 0, arg2 + 10, arg3);
        HuSprPosSet(entry->sprites[arg1], 1, -0x1C, 0);
    } else {
        HuSprDispOff(entry->sprites[arg1], 1);
        HuSprPosSet(entry->sprites[arg1], 0, arg2, arg3);
    }
}

void MBSaiPosSet(s32 arg0) {
    SaiWork* temp_a1 = &mbSaiWorkTbl[arg0];
    
    if (temp_a1->dice != NULL) {
        temp_a1->dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        temp_a1->dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbSaiHeight;
        temp_a1->dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
    }
}

s32 MBSaiTypeGet(s32 arg0) {
    return mbSaiWorkTbl[arg0].unk_0A;
}

static void MBSeqVolUpProc(void) {
    f32 var_f20 = 96.0f;

    HuAudSeqVolSet(0x60);

    while (var_f20 < 127.0f) {
        HuPrcVSleep();
        var_f20 += 1.9375f;
        if (var_f20 >= 127.0f) {
            var_f20 = 127.0f;
        }
        HuAudSeqVolSet(var_f20);
    }
    omDelPrcObj(NULL);
}

static void MBSeqVolDownProc(void) {
    f32 var_f20 = 127.0f;
    
    HuAudSeqVolSet(0x7F);
    while (var_f20 > 96.0f) {
        HuPrcVSleep();
        var_f20 -= 1.9375f;
        if (var_f20 <= 96.0f) {
            var_f20 = 96.0f;
        }
        HuAudSeqVolSet(var_f20);
    }
    omDelPrcObj(NULL);
}

void MBSeqVolDownStart(void) {
    omAddPrcObj(MBSeqVolDownProc, 0xEFFF, 0, 0);
}

void MBSeqVolUpStart(void) {
    omAddPrcObj(MBSeqVolUpProc, 0xEFFF, 0, 0);
}
