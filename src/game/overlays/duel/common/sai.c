#include "common_duel.h"
#include "ovl_81.h"

typedef struct UnkNameDicePrcData {
    /* 0x00 */ s32 playerIndex;
    /* 0x04 */ s32 state;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
} UnkNameDicePrcData; // sizeof 0x10

extern u8 mbdSaiMode;
extern u8 mbdSaiDispF;
extern f32 mbdSaiHeight;
extern u8 mbdSaiReadyF;
extern u8 mbdKakusiWaitF;
extern f32 Hu3DVtxWaveAngle;

u8 mbdSaiHitLockF = 0;
s32 mbdSaiMdlTbl[] = { 0x130207, 0x130207, 0x130207 };
s32 mbdSaiAnimTbl[] = { 0x1300FE, 0x1300FF, 0x130100 };

void MBDSaiObjMain(omObjData *arg0);
void MBDSaiNumObjMain(omObjData *arg0);
void MBDSaiNumSingleObjMain(omObjData *arg0);
void MBDSaiValueDecide(s32 arg0);
void MBDSaiNumPosSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void MBDSaiKill(s32 arg0);
void MBDSaiPlayerProc(void);
void MBDPlayerMotionSet(s32 playerIndex, s16 motion, u16 arg2);
void MBDPlayerMotionShiftSet(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4);

void MBDSaiSePlay(s32 playerIndex) {
    SaiWork *dice = &mbSaiWorkTbl[playerIndex];

    if (dice->unk28 == -1 && dice->dice->work[0] == 1) {
        if (dice->unk_0A == 1) {
            dice->unk28 = HuAudFXPlay(0x1D5);
        } else {
            dice->unk28 = HuAudFXPlay(0x100);
        }
    }
}

void MBDSaiObjMain(omObjData *arg0) {
    SaiWork *entry;
    f32 base;
    f32 scale;
    f32 decay;
    s32 i;

    entry = &mbSaiWorkTbl[arg0->work[3]];
    if (mbdSaiMode == 1) {
        base = 1.0f;
    } else {
        base = 0.1f;
    }

    switch (arg0->work[0]) {
        case 0:
            if (Hu3DPauseF != 0) {
                return;
            }
            arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbdSaiHeight;

            scale = (sindf(arg0->work[1] * 2) * entry->unk48 * base) + base;
            arg0->scale.x = arg0->scale.y = arg0->scale.z = scale;

            arg0->rot.y += 22.5f;
            arg0->work[1] = (arg0->work[1] + 25) % 180;

            decay = entry->unk48 - 0.05;
            entry->unk48 = decay;
            if (decay <= 0.0f) {
                entry->unk48 = 0.0f;
                arg0->scale.x = arg0->scale.y = arg0->scale.z = base;
                arg0->work[1] = 0;
                arg0->work[0] = 1;

                if (mbdSaiMode == 1) {
                    for (i = 0; i < 4; i++) {
                        if (mbSaiWorkTbl[i].unk28 != -1) {
                            break;
                        }
                    }

                    if (i == 4) {
                        if (GwSystem.current_board_index == 8) {
                            entry->unk28 = HuAudFXPlay(0x10B);
                        } else {
                            entry->unk28 = HuAudFXPlay(0x100);
                        }
                    } else {
                        entry->unk28 = mbSaiWorkTbl[i].unk28;
                    }
                } else if ((entry->unk2A == 0) && (mbdSaiMode != 2) && (entry->unk_0A != 2) &&
                           (mbdSaiDispF != 0)) {
                    if (entry->unk_0A == 1) {
                        entry->unk28 = HuAudFXPlay(0x1D5);
                    } else {
                        entry->unk28 = HuAudFXPlay(0x100);
                    }
                }
            }
            break;

        case 1:
            if (Hu3DPauseF == 0) {
                arg0->trans.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbdSaiHeight +
                                (sindf(arg0->work[1] * 2) * 10.0f * base);
                arg0->work[1] = (arg0->work[1] + 5) % 180;
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
                    MBDSaiKill(arg0->work[3]);
                }
            }
            break;
    }
}

void MBDSaiNumObjMain(omObjData *arg0) {
    SaiWork *entry;
    Vec pos;
    Vec2f pos2d;
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
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbdSaiHeight + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBDCamera3Dto2D(&pos, &pos2d);

    HuSprPosSet(entry->sprites[arg0->work[1]], 0, pos2d.x, pos2d.y - 8.0f);

    if ((pos2d.x >= 0.0f) && (pos2d.x <= 320.0f) && (pos2d.y >= 0.0f) && (pos2d.y <= 240.0f)) {
        MBDSaiNumPosSet(arg0->work[3], arg0->work[1], 160, 120 - (s32)(MBDCameraZoomGet() * 24.0f));
    }
}

void MBDSaiNumSingleObjMain(omObjData *arg0) {
    SaiWork *entry;
    Vec pos;
    Vec2f pos2d;
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
    pos.y = GwPlayer[arg0->work[3]].player_obj->coords.y + mbdSaiHeight + arg0->trans.y;
    pos.z = GwPlayer[arg0->work[3]].player_obj->coords.z;
    MBDCamera3Dto2D(&pos, &pos2d);

    HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, pos2d.x, pos2d.y);
}

void MBDSaiValueClear(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 5; i++) {
        for (j = 0; j < DICE_TOTAL; j++) {
            mbSaiWorkTbl[i].rollValue[j] = 0;
            mbSaiWorkTbl[i].predecidedRollValue[j] = 0;
        }
    }
}

void MBDSaiInit(void) {
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

    mbdSaiMode = 0;
    mbdSaiReadyF = 1;
    mbdSaiHeight = 25.0f;
    mbdSaiDispF = 1;
}

void MBDSaiNumSprCreate(s32 arg0) {
    SaiWork *entry;
    void *data;
    s32 i;

    entry = &mbSaiWorkTbl[arg0];

    if ((arg0 != 0) && (mbSaiWorkTbl[0].unk_14 != -1)) {
        entry->unk_14 = mbSaiWorkTbl[0].unk_14;
        mbSaiWorkTbl[0].unk_0C++;
    } else {
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

void MBDSaiNumShow(s32 arg0) {
    SaiWork *entry;
    omObjData *obj;
    Vec pos;
    Vec2f pos2d;
    s8 roll;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->rollValue[entry->rollValueIdx] != 0) {
        if ((entry->dice == NULL) || (entry->dice->work[0] == 2)) {
            pos.x = GwPlayer[arg0].player_obj->coords.x;
            pos.y = GwPlayer[arg0].player_obj->coords.y + mbdSaiHeight;
            pos.z = GwPlayer[arg0].player_obj->coords.z;
            MBDCamera3Dto2D(&pos, &pos2d);

            if (entry->sprites[entry->rollValueIdx] == -1) {
                MBDSaiNumSprCreate(arg0);
                entry->unk_0B = 0;
            } else {
                roll = entry->rollValueIdx;
                HuSprBankSet(entry->sprites[roll], 0, entry->rollValue[roll], 0);
                HuSprPriSet(entry->sprites[entry->rollValueIdx], 0, 0x4000);
                HuSprAnimModeSet(entry->sprites[entry->rollValueIdx], 0, HUSPR_ANIM_MODE_BANK);
            }

            if ((MBDOvlCallCheck() == 0) && (mbdSaiMode == 0)) {
                MBDSaiNumPosSet(arg0, entry->rollValueIdx, pos2d.x, pos2d.y - 8.0f);
            } else {
                HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, pos2d.x, pos2d.y);
            }

            if ((pos2d.x >= 0.0f) && (pos2d.x <= 320.0f) && (pos2d.y >= 0.0f) && (pos2d.y <= 240.0f)) {
                HuSprPosSet(entry->sprites[entry->rollValueIdx], 0, 160, 120 - (s32)(MBDCameraZoomGet() * 24.0f));
            }

            HuSprDispOn(entry->sprites[entry->rollValueIdx], 0);

            if (entry->omObj == NULL) {
                if ((MBDOvlCallCheck() == 0) && (mbdSaiMode == 0)) {
                    obj = omAddObj(-0x8000, 0, 0, -1, MBDSaiNumObjMain);
                    entry->omObj = obj;
                    obj->scale.z = 3.0f;
                    obj->work[1] = entry->rollValueIdx;
                } else {
                    obj = omAddObj(-0x8000, 0, 0, -1, MBDSaiNumSingleObjMain);
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

void MBDSaiValueDecide(s32 arg0) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    s32 i;

    if (entry->unk_0B == 0) {
        if (entry->rollValueIdx == 0) {
            MBDSaiNumKill(arg0);
        }
    }

    entry->unk_0B = 0;

    if (mbdSaiMode == 1) {
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
                if (mbSaiWorkTbl[i].rollValue[mbSaiWorkTbl[i].rollValueIdx] ==
                    entry->rollValue[entry->rollValueIdx]) {
                    break;
                }
            }
        } while (i != 5);
    } else {
        switch (entry->unk_0A) {
            case 0:
            case 1:
                if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                    entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                    entry->predecidedRollValue[entry->rollValueIdx] = 0;
                } else {
                    entry->rollValue[entry->rollValueIdx] = (rand8() % 10) + 1;
                }
                break;

            case 2:
                if (entry->predecidedRollValue[entry->rollValueIdx] != 0) {
                    entry->rollValue[entry->rollValueIdx] = entry->predecidedRollValue[entry->rollValueIdx];
                    entry->predecidedRollValue[entry->rollValueIdx] = 0;
                } else {
                    entry->rollValue[entry->rollValueIdx] = (rand8() % 3) + 1;
                }
                break;
        }
    }

    MBDSaiNumShow(arg0);
}

void MBDSaiNumObjKill(s32 playerIndex) {
    SaiWork *dice = &mbSaiWorkTbl[playerIndex];

    if (dice->omObj != NULL) {
        omDelObj(dice->omObj);
        dice->omObj = NULL;
    }
}

s32 MBDSaiNumKill(s32 arg0) {
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

void MBDSaiNumCountDown(s32 arg0) {
    SaiWork *dice = &mbSaiWorkTbl[arg0];

    dice->rollValue[dice->rollValueIdx]--;
    if (dice->rollValue[dice->rollValueIdx] <= 0) {
        MBDSaiNumKill(arg0);
    }
}

void MBDSaiMdlDispOff(s32 arg0) {
    if (mbSaiWorkTbl[arg0].unk_16 != -1) {
        Hu3DModelAttrSet(mbSaiWorkTbl[arg0].unk_16, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    }
}

void MBDSaiDispOff(s32 arg0) {
    mbdSaiDispF = 0;
    MBDSaiMdlDispOff(arg0);
}

void MBDSaiMdlDispOn(s32 playerIndex) {
    if (mbdSaiDispF && mbSaiWorkTbl[playerIndex].unk_16 != -1) {
        Hu3DModelAttrSet(mbSaiWorkTbl[playerIndex].unk_16, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
}

void MBDSaiDispOn(s32 arg0) {
    mbdSaiDispF = 1;
    MBDSaiMdlDispOn(arg0);
}

void MBDSaiTypeSet(s32 arg0, s8 arg1) {
    mbSaiWorkTbl[arg0].unk_09 = arg1;
}

s16 MBDSaiCreate(s32 arg0) {
    SaiWork *entry;
    omObjData *dice;
    s32 rot;
    s32 tile;
    s32 i;
    s16 ret;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->unk_16 != -1) {
        return -1;
    }

    if (entry->rollValueIdx == 0) {
        MBDSaiNumKill(arg0);
    }

    if (entry->unk_09 != -1) {
        entry->unk_0A = entry->unk_09;
        entry->unk_09 = -1;
    } else {
        entry->unk_0A = 0;
    }

    entry->unk_16 = Hu3DModelCreate(DataRead(mbdSaiMdlTbl[entry->unk_0A]), 0x6A9);
    Hu3DModelCameraSet(entry->unk_16, HU3D_CAM0);
    Hu3DModelScaleSet(entry->unk_16, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(entry->unk_16, 0x20000, 0x20000);

    entry->unk_2C = DataRead(mbdSaiAnimTbl[entry->unk_0A]);
    entry->unk_1A[0] = Hu3DAnimCreate(Hu3DData[entry->unk_16].hmf, entry->unk_2C, 0, "tile01_DEF");
    entry->unk_1A[1] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile02_DEF");
    entry->unk_1A[2] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile03_DEF");
    entry->unk_1A[3] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile04_DEF");
    entry->unk_1A[4] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile06_DEF");
    entry->unk_1A[5] = Hu3DAnimLink(Hu3DData[entry->unk_16].hmf, entry->unk_1A[0], 0, "tile10_DEF");

    tile = rand8() % 10;
    rot = rand8() & 3;
    for (i = 0; i < 6; i++) {
        if (entry->unk_0A < 2) {
            if (entry->unk_0A >= 0) {
                Hu3DAnimBankSet(entry->unk_1A[i], rot);
            }
        }
        Hu3DAnmNoSet(entry->unk_1A[i], tile);
    }

    Hu3DModelRemakeStatic(entry->unk_16);
    Hu3DModelVtxBufMake(entry->unk_16);

    dice = omAddObj(-0x8000, 1, 1, -1, MBDSaiObjMain);
    entry->dice = dice;
    *dice->model = entry->unk_16;
    omSetStatBit(dice, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);

    dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
    dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbdSaiHeight;
    dice->trans.z = GwPlayer[arg0].player_obj->coords.z;

    dice->rot.y = -90.0f;
    dice->scale.z = dice->scale.y = dice->scale.x = dice->rot.x = dice->rot.z = 0.0f;
    dice->work[0] = 0;
    dice->work[1] = 0x87;
    dice->work[2] = 0;
    dice->work[3] = arg0;

    entry->unk48 = 1.0f;
    entry->unk40 = 0.0f;
    entry->unk44 = 1.0f;

    mbdSaiMode = 0;
    ret = -1;
    switch (entry->unk_0A) {
        case 0:
            if (mbdSaiMode != 2) {
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
        default:
            HuAudFXPlay(0x10E);
            break;
    }

    return ret;
}

void MBDSaiCreateEx(s32 arg0, s32 arg1, s32 arg2, char *arg3[]) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
    omObjData *dice;
    s32 i;

    if (entry->unk_16 == -1) {
        if (mbdSaiMode == 1) {
            mbdSaiHeight = 250.0f;
        } else {
            mbdSaiHeight = 25.0f;
        }

        MBDSaiNumKill(arg0);
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

        dice = omAddObj(-0x8000, 1, 1, -1, MBDSaiObjMain);
        entry->dice = dice;
        dice->model[0] = entry->unk_16;
        omSetStatBit(dice, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
        dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbdSaiHeight;
        dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
        dice->rot.y = -90.0f;
        dice->scale.z = dice->scale.y = dice->scale.x = dice->rot.x = dice->rot.z = 0.0f;
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

void MBDSaiKill(s32 arg0) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];
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

void MBDSaiClose(void) {
    s32 i;

    for (i = 0; i < 5; i++) {
        MBDSaiKill(i);
        MBDSaiNumKill(i);
    }
}

void MBDSaiHit(s32 arg0) {
    SaiWork *entry;
    s32 count;
    s32 i;

    entry = &mbSaiWorkTbl[arg0];

    if (entry->unk_16 != -1) {
        entry->dice->work[0] = 2;

        if (mbdSaiMode != 2) {
            MBDSaiValueDecide(arg0);
        }

        if (mbdSaiMode == 1) {
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

        if (mbdSaiMode == 2) {
            HuAudFXPlay(0x10D);
        } else {
            HuAudFXPlay(0x103);
        }
    }
}

void MBDSaiOrderModeSet(void) {
    mbdSaiMode = 1;
    mbdSaiHeight = 250.0f;
}

s32 MBDSaiExistCheck(s32 arg0) {
    if (~mbSaiWorkTbl[arg0].unk_16) {
        return 1;
    } else {
        return 0;
    }
}

void MBDSaiValueSet(s32 arg0, s8 arg1) {
    mbSaiWorkTbl[arg0].rollValue[mbSaiWorkTbl[arg0].rollValueIdx] = arg1;
}

void MBDSaiValueForceSet(s32 arg0, s8 arg1) {
    mbSaiWorkTbl[arg0].predecidedRollValue[mbSaiWorkTbl[arg0].rollValueIdx] = arg1;
}

s32 MBDSaiValueGet(s32 arg0) {
    return mbSaiWorkTbl[arg0].rollValue[mbSaiWorkTbl[arg0].rollValueIdx];
}

void MBDSaiPlayerProc(void) {
    UnkNameDicePrcData *work;
    s32 count;

    work = HuPrcCurrentGet()->user_data;
    count = 0;
    while (1) {
        switch (work->state) {
            case 0:
                mbdSaiReadyF = 0;
                MBDSaiCreate(work->playerIndex);
                mbdSaiReadyF = 1;
                work->state++;
                HuPrcSleep(20);
                break;
            case 1:
                if (((GwPlayer[work->playerIndex].stat & PLAYER_IS_CPU) ||
                     (HuPadBtnDown[GwPlayer[work->playerIndex].pad] & A_BUTTON)) &&
                    !(Hu3DData[mbSaiWorkTbl[work->playerIndex].unk_16].attr & 4) && (GWBoardFlagCheck(0x11) == 0) &&
                    (mbdSaiHitLockF == 0)) {
                    work->state++;
                    MBDPlayerMotionSet(work->playerIndex, 1, 0);
                    MBDModelJumpSet(GwPlayer[work->playerIndex].player_obj, 2.0f, -0.3f);
                    mbCameraBtnF = 0;
                    duelCancelEnableF = 0;
                }
                break;
            case 2:
                if (++count >= 5) {
                    MBDSaiHit(work->playerIndex);
                    MBDPlayerMotionShiftSet(work->playerIndex, -1, 0, 10, 2);
                    work->state++;
                }
                break;
            case 3:
                HuPrcSleep(20);
                omDelPrcObj(NULL);
                break;
        }
        HuPrcVSleep();
    }
}

Process *MBDSaiPlayerCreate(s32 playerIndex) {
    Process *process;
    UnkNameDicePrcData *work;

    process = omAddPrcObj(MBDSaiPlayerProc, 0, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, sizeof(UnkNameDicePrcData));
    process->user_data = work;
    work->playerIndex = playerIndex;
    work->state = 0;
    return process;
}

u8 MBDKakusiWaitCheck(void) {
    return mbdKakusiWaitF;
}

void MBDKakusiWaitOn(void) {
    mbdKakusiWaitF = 1;
}

void MBDKakusiWaitOff(void) {
    mbdKakusiWaitF = 0;
}

void MBDSaiSeStop(s32 playerIndex) {
    SaiWork *dice = &mbSaiWorkTbl[playerIndex];

    if (dice->unk28 != -1) {
        HuAudFXStop(dice->unk28);
        dice->unk28 = -1;
    }
    dice->unk2A = 1;
}

void MBDSaiSeResume(s32 playerIndex) {
    SaiWork *dice = &mbSaiWorkTbl[playerIndex];

    if (dice->unk2A == 1 && dice->unk_16 != -1) {
        if (dice->dice != NULL && dice->dice->work[0] != 2 && mbdSaiMode != 2) {
            if (dice->unk_0A == 1) {
                dice->unk28 = HuAudFXPlay(0x1D5);
            } else {
                dice->unk28 = HuAudFXPlay(0x100);
            }
        }
    }
    dice->unk2A = 0;
}

void MBDSaiModeSet(s8 arg0) {
    mbdSaiMode = arg0;
}

void MBDSaiValueNoSet(s32 arg0, s8 arg1) {
    mbSaiWorkTbl[arg0].rollValueIdx = arg1;
}

void MBDSaiNumPosSet(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
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

void MBDSaiPosSet(s32 arg0) {
    SaiWork *entry = &mbSaiWorkTbl[arg0];

    if (entry->dice != NULL) {
        entry->dice->trans.x = GwPlayer[arg0].player_obj->coords.x;
        entry->dice->trans.y = GwPlayer[arg0].player_obj->coords.y + mbdSaiHeight;
        entry->dice->trans.z = GwPlayer[arg0].player_obj->coords.z;
    }
}
