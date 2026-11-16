#include "common_duel.h"
#include "game/overlays/duel/common/ovl_81.h"

// In duel mode, GW_SYSTEM's board data (from halfWordBytes[2] onward, running
// past the end of the union) holds six per-player duel records, one s16 for
// each of the two players.
#define DUEL_RECORD(record, player) (GwSystem.boardData.halfWordBytes[(record) * 2 + 2 + (player)])

typedef struct DuelResult2Positions {
    s32 x[4];
} DuelResult2Positions;

typedef struct DuelResult2PlayerFiles {
    s32 files[2][3];
} DuelResult2PlayerFiles;

typedef struct DuelResult2Portraits {
    s32 files[8];
} DuelResult2Portraits;

typedef struct DuelResult2StatFiles {
    s32 files[11];
} DuelResult2StatFiles;

extern const DuelResult2Portraits duelresult2_chrNameSprFileTbl;
extern const DuelResult2Portraits duelresult2_chrFaceSprFileTbl;
extern const DuelResult2StatFiles duelresult2_statNameSprFileTbl;
extern s16 kakusiMasuItemHis[10];

void duelresult2_ModelAnimSet(s16 model, s16 animIdx);
void duelresult2_StatNumUpdate(void);
void duelresult2_MainProc(void);
void duelresult2_ExitObjMain(omObjData *);
void duelresult2_ExitCheckObjMain(omObjData *);
void duelresult2_SysInit(void);
void duelresult2_CameraInit(void);
void duelresult2_SysClose(void);
void duelresult2_CameraClose(void);

UnkBoard4 *duelresult2_rankSubtitleSprGrp = NULL;
s32 duelresult2_statScroll = 0;
s32 duelresult2_statCursor = 0;

const DuelResult2PlayerFiles duelresult2_rankRowSprFileTbl = { { { 0x130035, 0x130071, 0x130045 }, { 0x130032, 0x130070, 0x130042 } } };
const DuelResult2PlayerFiles duelresult2_rankResultSprFileTbl = { { { 0x130066, 0x130067, 0x130068 }, { 0x130063, 0x130064, 0x130065 } } };
const DuelResult2Portraits duelresult2_rankFaceSprFileTbl = { { 0x130036, 0x130037, 0x130038, 0x130039, 0x13003A, 0x13003B, 0x13003C, 0x13003D } };
const DuelResult2Positions duelresult2_rankRowXTbl = { { 0, 60, 142, 0 } };

UnkBoard4 *duelresult2_bgSprGrp BSS;
UnkBoard4 *duelresult2_rankRowSprGrpTbl[2] BSS;
UnkBoard4 *duelresult2_rankTitleSprGrp BSS;
UnkOvl81_2 *duelresult2_hostGuide BSS;
UnkBoard4 *duelresult2_boardNameSprGrp BSS;
UnkBoard4 *duelresult2_gameLengthSprGrp BSS;
UnkBoard4 *duelresult2_statLabelSprGrp BSS;
UnkBoard4 *duelresult2_statRowSprGrpTbl[2] BSS;
UnkBoard4 *duelresult2_statArrowSprGrp BSS;
UnkBoard4 *duelresult2_statNameSprGrp BSS;
UnkBoard4 *duelresult2_statNumSprGrp BSS;
UnkBoard4 *duelresult2_statCursorSprGrp BSS;
s32 duelresult2_hostAnimNoTbl[16] BSS;
s16 duelresult2_hostAnimTbl[10] BSS;
s16 duelresult2_hostAnim BSS;
s16 duelresult2_hostAnimLink BSS;

void duelresult2_ObjectSetup(void) {
    u32 i;

    omInitObjMan(0x50, 0x50);
    duelresult2_CameraInit();
    duelresult2_SysInit();
    HuWinInit();
    omAddPrcObj(duelresult2_MainProc, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, duelresult2_ExitCheckObjMain);

    for (i = 0; i < 16; i++) {
        do {
            duelresult2_hostAnimNoTbl[i] = MBDRand(7.0f);
        } while (i != 0 && duelresult2_hostAnimNoTbl[i - 1] == duelresult2_hostAnimNoTbl[i]);
    }
}

s16 duelresult2_ModelAnimCreate(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    duelresult2_hostAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    duelresult2_hostAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void duelresult2_ModelAnimSet(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (duelresult2_hostAnimLink != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[duelresult2_hostAnimLink];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 duelresult2_AnimDataRead(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void duelresult2_RankSprCreate(void) {
    DuelResult2PlayerFiles playerFiles = duelresult2_rankRowSprFileTbl;
    DuelResult2PlayerFiles rankFiles = duelresult2_rankResultSprFileTbl;
    DuelResult2Portraits portraits = duelresult2_rankFaceSprFileTbl;
    DuelResult2Positions memberX = duelresult2_rankRowXTbl;
    void *data;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        duelresult2_rankRowSprGrpTbl[i] = MBDSprGrpCreate(11, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(playerFiles.files[i][j]);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1], 0);
            HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
            HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
            HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, memberX.x[j], 0);
        }

        data = DataRead(portraits.files[GwPlayer[i].chr]);
        duelresult2_rankRowSprGrpTbl[i]->unk_0C[4] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 4, duelresult2_rankRowSprGrpTbl[i]->unk_0C[4], 0);
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 4, 95);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 4, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 4, memberX.x[3], 1);

        j = 4;
        if (GwPlayer[i].star >= 10) {
            data = DataRead(0xC0086);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                          GwPlayer[i].star / 10);
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 68, 4);

        data = DataRead(0xC0086);
        duelresult2_rankRowSprGrpTbl[i]->unk_0C[6] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 6, duelresult2_rankRowSprGrpTbl[i]->unk_0C[6],
                          GwPlayer[i].star % 10);
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 93);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 84, 4);

        j = 6;
        if (GwPlayer[i].coin >= 100) {
            data = DataRead(0xC0086);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                          GwPlayer[i].coin / 100);
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 142, 4);

        j = 7;
        data = DataRead(0xC0086);
        duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        if (GwPlayer[i].coin >= 10) {
            HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                              GwPlayer[i].coin / 10 % 10);
        } else {
            HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                              GwPlayer[i].coin);
        }
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 158, 4);

        if (GwPlayer[i].coin >= 10) {
            data = DataRead(0xC0086);
            duelresult2_rankRowSprGrpTbl[i]->unk_0C[9] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 9, duelresult2_rankRowSprGrpTbl[i]->unk_0C[9],
                              GwPlayer[i].coin % 10);
            HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 90);
            HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 0x4000);
            HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 174, 4);
        }

        j = 9;
        if (kakusiMasuItemHis[2] == -1) {
            data = DataRead(rankFiles.files[i][2]);
        } else if (kakusiMasuItemHis[0] == i) {
            data = DataRead(rankFiles.files[i][0]);
        } else {
            data = DataRead(rankFiles.files[i][1]);
        }
        duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, duelresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1], 0);
        HuSprPriSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, -56, 0);
    }

    for (j = 0; j < 2; j++) {
        HuSprPosSet(duelresult2_rankRowSprGrpTbl[j]->unk_0A, 0, 111, j * 62 + 91);
    }

    duelresult2_rankTitleSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130046);
    duelresult2_rankTitleSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_rankTitleSprGrp->unk_0A, 0, duelresult2_rankTitleSprGrp->unk_0C[0], 0);
    HuSprPriSet(duelresult2_rankTitleSprGrp->unk_0A, 0, 90);
    HuSprAttrSet(duelresult2_rankTitleSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(duelresult2_rankTitleSprGrp->unk_0A, 0, 160, 33);

    if (kakusiMasuItemHis[2] != -1) {
        duelresult2_rankSubtitleSprGrp = MBDSprGrpCreate(1, 0);
        data = DataRead(0x130062);
        duelresult2_rankSubtitleSprGrp->unk_0C[0] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_rankSubtitleSprGrp->unk_0A, 0, duelresult2_rankSubtitleSprGrp->unk_0C[0], 0);
        HuSprPriSet(duelresult2_rankSubtitleSprGrp->unk_0A, 0, 89);
        HuSprAttrSet(duelresult2_rankSubtitleSprGrp->unk_0A, 0, 0x4000);
        if (kakusiMasuItemHis[0] == 0) {
            HuSprPosSet(duelresult2_rankSubtitleSprGrp->unk_0A, 0, 55, 64);
        } else {
            HuSprPosSet(duelresult2_rankSubtitleSprGrp->unk_0A, 0, 55, 126);
        }
    } else {
        duelresult2_rankSubtitleSprGrp = NULL;
    }
}

void duelresult2_RankSprKill(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBDSprGrpKill(duelresult2_rankRowSprGrpTbl[i]);
    }

    MBDSprGrpKill(duelresult2_rankTitleSprGrp);

    if (duelresult2_rankSubtitleSprGrp != NULL) {
        MBDSprGrpKill(duelresult2_rankSubtitleSprGrp);
    }
}

void duelresult2_RankDispOff(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprDispOff(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    HuSprDispOff(duelresult2_rankTitleSprGrp->unk_0A, 0);

    if (duelresult2_rankSubtitleSprGrp != NULL) {
        HuSprDispOff(duelresult2_rankSubtitleSprGrp->unk_0A, 0);
    }
}

void duelresult2_RankDispOn(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 11; j++) {
            HuSprDispOn(duelresult2_rankRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    HuSprDispOn(duelresult2_rankTitleSprGrp->unk_0A, 0);

    if (duelresult2_rankSubtitleSprGrp != NULL) {
        HuSprDispOn(duelresult2_rankSubtitleSprGrp->unk_0A, 0);
    }
}

s32 duelresult2_StatTopMaskGet(s32 category) {
    s32 max;
    s32 mask = 0;
    s32 i;

    switch (category) {
        case 0:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].star) {
                    max = GwPlayer[i].star;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].star == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 1:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].coin) {
                    max = GwPlayer[i].coin;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].coin == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 2:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].gamePrize) {
                    max = GwPlayer[i].gamePrize;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].gamePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 3:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < GwPlayer[i].coinPrize) {
                    max = GwPlayer[i].coinPrize;
                }
            }
            for (i = 0; i < 2; i++) {
                if (GwPlayer[i].coinPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 4:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(5, i)) {
                    max = DUEL_RECORD(5, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(5, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 5:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(0, i)) {
                    max = DUEL_RECORD(0, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(0, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 6:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(3, i)) {
                    max = DUEL_RECORD(3, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(3, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 7:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(4, i)) {
                    max = DUEL_RECORD(4, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(4, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 8:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(1, i)) {
                    max = DUEL_RECORD(1, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(1, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 9:
            for (i = 0, max = -100000; i < 2; i++) {
                if (max < DUEL_RECORD(2, i)) {
                    max = DUEL_RECORD(2, i);
                }
            }
            for (i = 0; i < 2; i++) {
                if (DUEL_RECORD(2, i) == max) {
                    mask |= 1 << i;
                }
            }
            break;
    }

    if (mask == 3) {
        return 0;
    }
    return mask;
}

void duelresult2_StatNumUpdate(void) {
    u8 buf[8];
    s32 offsets[] = { 0, -30, -25, -20, -15 };
    GW_PLAYER *player;
    s32 mask;
    s32 value;
    s32 digits;
    s32 row;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 10; i++) {
        HuSprDispOff(duelresult2_statNameSprGrp->unk_0A, i);
    }

    for (i = duelresult2_statScroll, row = 0; i < duelresult2_statScroll + 4; i++, row++) {
        HuSprDispOn(duelresult2_statNameSprGrp->unk_0A, i);
        HuSprPosSet(duelresult2_statNameSprGrp->unk_0A, i, row * 44 + 145, 73);
    }

    for (i = 0; i < 64; i++) {
        HuSprDispOff(duelresult2_statNumSprGrp->unk_0A, i);
    }

    for (i = duelresult2_statScroll, row = 0; i < duelresult2_statScroll + 4; i++, row++) {
        for (j = 0; j < 2; j++) {
            player = MBDGetPlayerStruct(j);
            mask = duelresult2_StatTopMaskGet(i);
            digits = 1;
            value = 1;
            switch (i) {
                case 0:
                    value = player->star;
                    digits = 2;
                    break;
                case 1:
                    value = player->coin;
                    digits = 3;
                    break;
                case 2:
                    value = player->gamePrize;
                    if (value >= 1000) {
                        value = 999;
                    }
                    digits = 3;
                    break;
                case 3:
                    value = player->coinPrize;
                    digits = 3;
                    break;
                case 4:
                    value = DUEL_RECORD(5, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 5:
                    value = DUEL_RECORD(0, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 6:
                    value = DUEL_RECORD(3, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 7:
                    value = DUEL_RECORD(4, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 8:
                    value = DUEL_RECORD(1, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
                case 9:
                    value = DUEL_RECORD(2, j);
                    if (value >= 100) {
                        value = 99;
                    }
                    digits = 2;
                    break;
            }
            if (value < 0) {
                value = 0;
            }
            sprintf((char *)buf, "%4d", value);

            for (k = 0; k < 4; k++) {
                if (buf[k] == ' ') {
                    HuSprDispOff(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k);
                    continue;
                }
                if (mask & (1 << j)) {
                    HuSprGrpMemberSet(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                                      duelresult2_statNumSprGrp->unk_0C[1], 0);
                } else {
                    HuSprGrpMemberSet(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                                      duelresult2_statNumSprGrp->unk_0C[0], 0);
                }
                HuSprDispOn(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k);
                HuSprPosSet(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                            row * 44 + (s16)(k * 10 + 145) + offsets[digits], j * 26 + 99);
                HuSprBankSet(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k, buf[k] - '0', 0);
                HuSprAnimModeSet(duelresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k, HUSPR_ANIM_MODE_BANK);
            }
        }
    }

    HuSprPosSet(duelresult2_statCursorSprGrp->unk_0A, 0, duelresult2_statCursor * 44 + 146, 100);
}

const DuelResult2Portraits duelresult2_chrNameSprFileTbl = { { 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F } };

const DuelResult2Portraits duelresult2_chrFaceSprFileTbl = { { 0x1301D5, 0x1301D6, 0x1301D7, 0x1301D8, 0x1301D9, 0x1301DA, 0x1301DB, 0x1301DC } };

const DuelResult2StatFiles duelresult2_statNameSprFileTbl = { { 0x13005A, 0x13004E, 0x13004F, 0x130050, 0x13005B, 0x13005C, 0x13005D, 0x13005E, 0x13005F, 0x130060, 0x130061 } };

void duelresult2_StatSprCreate(void) {
    s32 rankFiles[2] = { 0x13004A, 0x130047 };
    DuelResult2Portraits nameFiles = duelresult2_chrNameSprFileTbl;
    DuelResult2Portraits faceFiles = duelresult2_chrFaceSprFileTbl;
    s32 lengthFiles[2] = { 0x130072, 0x130074 };
    DuelResult2StatFiles statFiles = duelresult2_statNameSprFileTbl;
    void *data;
    s32 i;

    duelresult2_boardNameSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x13006F);
    duelresult2_boardNameSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_boardNameSprGrp->unk_0A, 0, duelresult2_boardNameSprGrp->unk_0C[0], 0);
    HuSprPriSet(duelresult2_boardNameSprGrp->unk_0A, 0, 110);
    HuSprAttrSet(duelresult2_boardNameSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(duelresult2_boardNameSprGrp->unk_0A, 0, 74, 39);

    duelresult2_gameLengthSprGrp = MBDSprGrpCreate(2, 0);
    data = DataRead(0x13004B);
    duelresult2_gameLengthSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_gameLengthSprGrp->unk_0A, 0, duelresult2_gameLengthSprGrp->unk_0C[0], 0);
    HuSprPriSet(duelresult2_gameLengthSprGrp->unk_0A, 0, 100);
    HuSprAttrSet(duelresult2_gameLengthSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(duelresult2_gameLengthSprGrp->unk_0A, 0, 210, 36);

    if (GwSystem.playMode & 4) {
        data = DataRead(0x13007C);
    } else if (GwSystem.total_turns == 20) {
        data = DataRead(lengthFiles[0]);
    } else {
        data = DataRead(lengthFiles[1]);
    }
    duelresult2_gameLengthSprGrp->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_gameLengthSprGrp->unk_0A, 1, duelresult2_gameLengthSprGrp->unk_0C[1], 0);
    HuSprPriSet(duelresult2_gameLengthSprGrp->unk_0A, 1, 99);
    HuSprAttrSet(duelresult2_gameLengthSprGrp->unk_0A, 1, 0x4000);
    HuSprPosSet(duelresult2_gameLengthSprGrp->unk_0A, 1, 210, 36);

    duelresult2_statLabelSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x13004C);
    duelresult2_statLabelSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_statLabelSprGrp->unk_0A, 0, duelresult2_statLabelSprGrp->unk_0C[0], 0);
    HuSprPriSet(duelresult2_statLabelSprGrp->unk_0A, 0, 99);
    HuSprAttrSet(duelresult2_statLabelSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(duelresult2_statLabelSprGrp->unk_0A, 0, 218, 73);

    for (i = 0; i < 2; i++) {
        duelresult2_statRowSprGrpTbl[i] = MBDSprGrpCreate(10, 2);
        data = DataRead(rankFiles[i]);
        duelresult2_statRowSprGrpTbl[i]->unk_0C[1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 1, duelresult2_statRowSprGrpTbl[i]->unk_0C[1], 0);
        HuSprPriSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 1, 98);
        HuSprAttrSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 1, 0x4000);
        HuSprPosSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 1, 172, 0);

        data = DataRead(nameFiles.files[GwPlayer[i].chr]);
        duelresult2_statRowSprGrpTbl[i]->unk_0C[2] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 2, duelresult2_statRowSprGrpTbl[i]->unk_0C[2], 0);
        HuSprPriSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 2, 97);
        HuSprAttrSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 2, 0x4000);
        HuSprPosSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 2, 36, 1);

        data = DataRead(faceFiles.files[GwPlayer[i].chr]);
        duelresult2_statRowSprGrpTbl[i]->unk_0C[3] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 3, duelresult2_statRowSprGrpTbl[i]->unk_0C[3], 0);
        HuSprPriSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 3, 96);
        HuSprAttrSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 3, 0x4000);
        HuSprPosSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 3, 77, 1);
    }

    for (i = 0; i < 2; i++) {
        HuSprPosSet(duelresult2_statRowSprGrpTbl[i]->unk_0A, 0, 0, i * 26 + 99);
    }

    duelresult2_statArrowSprGrp = MBDSprGrpCreate(2, 0);
    for (i = 0; i < 2; i++) {
        data = DataRead(0x13002E);
        duelresult2_statArrowSprGrp->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_statArrowSprGrp->unk_0A, i, duelresult2_statArrowSprGrp->unk_0C[i], 0);
        HuSprPriSet(duelresult2_statArrowSprGrp->unk_0A, i, 90);
        HuSprAttrSet(duelresult2_statArrowSprGrp->unk_0A, i, 0x4000);
        HuSprPosSet(duelresult2_statArrowSprGrp->unk_0A, i, i * 154 + 133, 161);
    }
    HuSprAttrSet(duelresult2_statArrowSprGrp->unk_0A, 0, 1);

    duelresult2_statNameSprGrp = MBDSprGrpCreate(10, 0);
    for (i = 0; i < 10; i++) {
        if (i == 9 && GwSystem.current_board_index == 5) {
            data = DataRead(statFiles.files[10]);
        } else {
            data = DataRead(statFiles.files[i]);
        }
        duelresult2_statNameSprGrp->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(duelresult2_statNameSprGrp->unk_0A, i, duelresult2_statNameSprGrp->unk_0C[i], 0);
        HuSprPriSet(duelresult2_statNameSprGrp->unk_0A, i, 80);
        HuSprAttrSet(duelresult2_statNameSprGrp->unk_0A, i, 0xC000);
    }

    duelresult2_statNumSprGrp = MBDSprGrpCreate(64, 0);
    data = DataRead(0x130077);
    duelresult2_statNumSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x130078);
    duelresult2_statNumSprGrp->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 64; i++) {
        HuSprGrpMemberSet(duelresult2_statNumSprGrp->unk_0A, i, duelresult2_statNumSprGrp->unk_0C[0], 0);
        HuSprPriSet(duelresult2_statNumSprGrp->unk_0A, i, 70);
        HuSprAttrSet(duelresult2_statNumSprGrp->unk_0A, i, 0xC000);
    }

    duelresult2_statCursorSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x13007B);
    duelresult2_statCursorSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(duelresult2_statCursorSprGrp->unk_0A, 0, duelresult2_statCursorSprGrp->unk_0C[0], 0);
    HuSprPriSet(duelresult2_statCursorSprGrp->unk_0A, 0, 60);
    HuSprAttrSet(duelresult2_statCursorSprGrp->unk_0A, 0, 0x4000);

    duelresult2_hostGuide = MBDGuideCreate(0, 8);
    MBDGuidePosSet(duelresult2_hostGuide, 105, 8);
    HuVecCopyXYZ(&duelresult2_hostGuide->obj->scale, 0.1f, 0.1f, 0.1f);
    HuWinScaleSet(duelresult2_hostGuide->win_id, 1.0f, 1.0f);
    HuWinAttrSet(duelresult2_hostGuide->win_id, 0x4000, 0x4000);
    HuWinMesPalSet(duelresult2_hostGuide->win_id, 2, 255, 96, 96);
    HuWinMesPalSet(duelresult2_hostGuide->win_id, 4, 96, 255, 64);
    HuWinMesPalSet(duelresult2_hostGuide->win_id, 6, 64, 255, 255);
    MBDGuidePosSet(duelresult2_hostGuide, 113, 8);

    duelresult2_hostAnimTbl[0] =
        duelresult2_ModelAnimCreate(duelresult2_hostGuide->obj->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    duelresult2_hostAnimTbl[1] = duelresult2_AnimDataRead(0xA007F);
    duelresult2_hostAnimTbl[2] = duelresult2_AnimDataRead(0xA0080);
    duelresult2_hostAnimTbl[3] = duelresult2_AnimDataRead(0xA0081);
    duelresult2_hostAnimTbl[4] = duelresult2_AnimDataRead(0xA0082);
    duelresult2_hostAnimTbl[5] = duelresult2_AnimDataRead(0xA0083);
    duelresult2_hostAnimTbl[6] = duelresult2_AnimDataRead(0xA0084);
    duelresult2_ModelAnimSet(duelresult2_hostGuide->obj->omObj1->model[0], duelresult2_hostAnimTbl[0]);
}

void duelresult2_StatSprKill(void) {
    s32 i;

    MBDSprGrpKill(duelresult2_boardNameSprGrp);
    MBDSprGrpKill(duelresult2_gameLengthSprGrp);
    MBDSprGrpKill(duelresult2_statLabelSprGrp);

    for (i = 0; i < 2; i++) {
        MBDSprGrpKill(duelresult2_statRowSprGrpTbl[i]);
    }

    MBDSprGrpKill(duelresult2_statArrowSprGrp);
    MBDSprGrpKill(duelresult2_statNameSprGrp);
    MBDSprGrpKill(duelresult2_statNumSprGrp);
    MBDSprGrpKill(duelresult2_statCursorSprGrp);
    MBDGuideKill(duelresult2_hostGuide);
}

void duelresult2_StatDispOff(void) {
    s32 i;
    s32 j;

    HuSprDispOff(duelresult2_boardNameSprGrp->unk_0A, 0);
    HuSprDispOff(duelresult2_gameLengthSprGrp->unk_0A, 0);
    HuSprDispOff(duelresult2_gameLengthSprGrp->unk_0A, 1);
    HuSprDispOff(duelresult2_statLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(duelresult2_statRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOff(duelresult2_statArrowSprGrp->unk_0A, j);
    }

    for (j = 0; j < 10; j++) {
        HuSprDispOff(duelresult2_statNameSprGrp->unk_0A, j);
    }

    for (j = 0; j < 64; j++) {
        HuSprDispOff(duelresult2_statNumSprGrp->unk_0A, j);
    }

    HuSprDispOff(duelresult2_statCursorSprGrp->unk_0A, 0);
    MBDModelDispOff(duelresult2_hostGuide->obj);
    HuWinDispOff(duelresult2_hostGuide->win_id);
}

void duelresult2_StatDispOn(void) {
    s32 i;
    s32 j;

    HuSprDispOn(duelresult2_boardNameSprGrp->unk_0A, 0);
    HuSprDispOn(duelresult2_gameLengthSprGrp->unk_0A, 0);
    HuSprDispOn(duelresult2_gameLengthSprGrp->unk_0A, 1);
    HuSprDispOn(duelresult2_statLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(duelresult2_statRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOn(duelresult2_statArrowSprGrp->unk_0A, j);
    }

    duelresult2_StatNumUpdate();
    HuSprDispOn(duelresult2_statCursorSprGrp->unk_0A, 0);
    MBDModelDispOn(duelresult2_hostGuide->obj);
    HuWinDispOn(duelresult2_hostGuide->win_id);

    if (duelresult2_statScroll == 0 && duelresult2_statCursor == 0) {
        HuSprDispOff(duelresult2_statArrowSprGrp->unk_0A, 0);
    }
    if (duelresult2_statScroll == 6 && duelresult2_statCursor == 3) {
        HuSprDispOff(duelresult2_statArrowSprGrp->unk_0A, 1);
    }
}

void duelresult2_StatMesSet(void) {
    s32 messages[] = {
        0x2800,
        0x2801,
        0x2802,
        0x2803,
        0x2804,
        0x2805,
        0x2806,
        0x2807,
        0x2808,
        0x2809,
    };

    HuWinHomeClear(duelresult2_hostGuide->win_id);
    HuWinMesSet(duelresult2_hostGuide->win_id, messages[duelresult2_statScroll + duelresult2_statCursor], -1, -1);
    duelresult2_ModelAnimSet(duelresult2_hostGuide->obj->omObj1->model[0],
                              duelresult2_hostAnimTbl[duelresult2_hostAnimNoTbl[duelresult2_statScroll + duelresult2_statCursor]]);
}

void duelresult2_MainProc(void) {
    void *data;
    s32 prevPage;
    s32 prevRow;
    s32 timer;
    s32 allCpu;
    s32 showingDetails;
    DuelHelpWin *leftWindow = NULL;
    DuelHelpWin *rightWindow = NULL;
    s32 i;

    duelresult2_bgSprGrp = MBDSprGrpCreate(6, 0);
    data = DataRead(0x13002F);
    duelresult2_bgSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 6; i++) {
        HuSprGrpMemberSet(duelresult2_bgSprGrp->unk_0A, i, duelresult2_bgSprGrp->unk_0C[0], 0);
        HuSprPriSet(duelresult2_bgSprGrp->unk_0A, i, 200);
        HuSprAttrSet(duelresult2_bgSprGrp->unk_0A, i, 0x4000);
        HuSprPosSet(duelresult2_bgSprGrp->unk_0A, i, (i / 2) * 128 + 64, (i & 1) * 128 + 64);
    }

    duelresult2_RankSprCreate();
    showingDetails = 0;
    duelresult2_StatSprCreate();
    duelresult2_StatMesSet();
    duelresult2_StatDispOff();
    duelresult2_RankDispOn();

    WipeCreateIn(2, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    allCpu = 0;
    for (i = 0; i < 2; i++) {
        if (!MBDPlayerComCheck(i)) {
            break;
        }
    }
    if (i == 2) {
        allCpu = 1;
    }

    timer = 60;
    while (1) {
        if (allCpu) {
            if (--timer == 0) {
                break;
            }
            if (leftWindow == NULL) {
                leftWindow = MBDHelpWinCreateEx(0x16, 60, 207, 1);
            }
            if (rightWindow == NULL) {
                rightWindow = MBDHelpWinCreateEx(0x17, 200, 207, 1);
            }
        } else {
            for (i = 0; i < 2; i++) {
                if (MBDPlayerComCheck(i)) {
                    continue;
                }
                if (!showingDetails) {
                    if (leftWindow == NULL) {
                        leftWindow = MBDHelpWinCreateEx(0x16, 60, 207, 1);
                    }
                    if (rightWindow == NULL) {
                        rightWindow = MBDHelpWinCreateEx(0x17, 200, 207, 1);
                    }
                    if (ContBtnDown[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 1;
                        duelresult2_RankDispOff();
                        duelresult2_StatDispOn();
                        if (leftWindow != NULL) {
                            MBDHelpWinKill(leftWindow);
                            leftWindow = NULL;
                        }
                        if (rightWindow != NULL) {
                            MBDHelpWinKill(rightWindow);
                            rightWindow = NULL;
                        }
                    } else if (ContBtnDown[GwPlayer[i].pad] & A_BUTTON) {
                        goto exit;
                    }
                } else {
                    prevRow = duelresult2_statCursor;
                    prevPage = duelresult2_statScroll;
                    if (ContBtnDown[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 0;
                        duelresult2_StatDispOff();
                        duelresult2_RankDispOn();
                    } else if (ContBtnRep[GwPlayer[i].pad] & R_JPAD) {
                        if (++duelresult2_statCursor >= 4) {
                            duelresult2_statCursor = 3;
                            if (++duelresult2_statScroll >= 7) {
                                duelresult2_statScroll = 6;
                            }
                        }
                    } else if (ContBtnRep[GwPlayer[i].pad] & L_JPAD) {
                        if (--duelresult2_statCursor < 0) {
                            duelresult2_statCursor = 0;
                            if (--duelresult2_statScroll < 0) {
                                duelresult2_statScroll = 0;
                            }
                        }
                    }
                    if (duelresult2_statCursor != prevRow || duelresult2_statScroll != prevPage) {
                        duelresult2_StatMesSet();
                        duelresult2_StatNumUpdate();
                    }
                }
            }

            if (showingDetails == 1) {
                if (duelresult2_statScroll == 0 && duelresult2_statCursor == 0) {
                    HuSprAttrSet(duelresult2_statArrowSprGrp->unk_0A, 0, 0x8000);
                } else {
                    HuSprAttrReset(duelresult2_statArrowSprGrp->unk_0A, 0, 0x8000);
                }
                if (duelresult2_statScroll == 6 && duelresult2_statCursor == 3) {
                    HuSprAttrSet(duelresult2_statArrowSprGrp->unk_0A, 1, 0x8000);
                } else {
                    HuSprAttrReset(duelresult2_statArrowSprGrp->unk_0A, 1, 0x8000);
                }
            }
        }
        HuPrcVSleep();
    }

exit:
    if (leftWindow != NULL) {
        MBDHelpWinKill(leftWindow);
    }
    if (rightWindow != NULL) {
        MBDHelpWinKill(rightWindow);
    }
    if (!(GwSystem.playMode & 4) || kakusiMasuItemHis[2] == -1 ||
        (GwPlayer[kakusiMasuItemHis[0]].stat & PLAYER_IS_CPU)) {
        HuAudSeqFadeOut(60);
    }
    WipeCreateOut(0, 20);
    HuPrcSleep(20);
    duelresult2_RankSprKill();
    duelresult2_StatSprKill();
    MBDSprGrpKill(duelresult2_bgSprGrp);
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void duelresult2_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        duelresult2_CameraClose();
        duelresult2_SysClose();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void duelresult2_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq != 0) {
        arg0->func = duelresult2_ExitObjMain;
    }
}

void duelresult2_SysInit(void) {
    MBDModelInit();
    MBDPlayerMotInit();
    MBDSprGrpInit();
}

void duelresult2_SysClose(void) {
    MBDPlayerClose();
    MBDModelClose();
    MBDSprGrpClose();
}

void duelresult2_CameraInit(void) {
    Hu3DCamInit(2);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void duelresult2_CameraClose(void) {
}
