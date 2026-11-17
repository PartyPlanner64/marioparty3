#include "common.h"
#include "game/overlays/duel/common/ovl_81.h"
#include "game/overlays/minigame.h"

typedef struct BoardResult2Positions {
    s32 x[4];
} BoardResult2Positions;

typedef struct BoardResult2PlayerFiles {
    s32 files[4][3];
} BoardResult2PlayerFiles;

typedef struct BoardResult2Portraits {
    s32 files[8];
} BoardResult2Portraits;

typedef struct BoardResult2Files4 {
    s32 files[4];
} BoardResult2Files4;

typedef struct BoardResult2BoardFiles {
    s32 files[6];
} BoardResult2BoardFiles;

typedef struct BoardResult2StatFiles {
    s32 files[13];
} BoardResult2StatFiles;

extern s16 kakusiMasuItemHis[10];

s32 boardresult2_statScroll = 0;
s32 boardresult2_statCursor = 0;
s32 boardresult2_unusedTbl[2] = { 0 }; /* Unreferenced. */

BoardResult2Positions boardresult2_rankHeaderXTbl = {
    { 55, 111, 171, 252 }
};

BoardResult2PlayerFiles boardresult2_rankRowSprFileTbl = {
    { { 0x00130032, 0x0013003E, 0x00130042 },
      { 0x00130033, 0x0013003F, 0x00130043 },
      { 0x00130034, 0x00130040, 0x00130044 },
      { 0x00130035, 0x00130041, 0x00130045 } }
};

BoardResult2Portraits boardresult2_rankFaceSprFileTbl = {
    { 0x00130036, 0x00130037, 0x00130038, 0x00130039,
      0x0013003A, 0x0013003B, 0x0013003C, 0x0013003D }
};

BoardResult2Positions boardresult2_rankRowXTbl = {
    { 0, 60, 142, 0 }
};

UnkBoard4 *boardresult2_bgSprGrp BSS;
UnkBoard4 *boardresult2_rankHeaderSprGrp BSS;
UnkBoard4 *boardresult2_rankLabelSprGrp BSS;
u8 boardresult2_rankLabelPad[4] BSS; /* Unreferenced. */
UnkBoard4 *boardresult2_rankRowSprGrpTbl[4] BSS;
UnkBoard4 *boardresult2_rankTitleSprGrp BSS;
UnkBoard4 *boardresult2_rankSubtitleSprGrp BSS;
UnkOvl81_2 *boardresult2_hostGuide BSS;
UnkBoard4 *boardresult2_boardNameSprGrp BSS;
UnkBoard4 *boardresult2_gameLengthSprGrp BSS;
UnkBoard4 *boardresult2_statLabelSprGrp BSS;
UnkBoard4 *boardresult2_statRowSprGrpTbl[4] BSS;
UnkBoard4 *boardresult2_statArrowSprGrp BSS;
UnkBoard4 *boardresult2_statNameSprGrp BSS;
UnkBoard4 *boardresult2_statNumSprGrp BSS;
UnkBoard4 *boardresult2_statCursorSprGrp BSS;
s32 boardresult2_hostAnimNoTbl[16] BSS;
s16 boardresult2_hostAnimTbl[10] BSS;
s16 boardresult2_hostAnim BSS;
s16 boardresult2_hostAnimLink BSS;

void boardresult2_ModelAnimSet(s16 model, s16 animIdx);
void boardresult2_RankSprCreate(void);
void boardresult2_RankSprKill(void);
void boardresult2_RankDispOff(void);
void boardresult2_RankDispOn(void);
void boardresult2_StatSprCreate(void);
void boardresult2_StatSprKill(void);
void boardresult2_StatDispOff(void);
void boardresult2_StatDispOn(void);
void boardresult2_StatMesSet(void);
void boardresult2_RankRowDropProc(void);
void boardresult2_TitleDropProc(void);
void boardresult2_StatNumUpdate(void);
s32 boardresult2_StatTopMaskGet(s32);
void boardresult2_MainProc(void);
void boardresult2_ExitObjMain(omObjData *);
void boardresult2_ExitCheckObjMain(omObjData *);
void boardresult2_SysInit(void);
void boardresult2_CameraInit(void);
void boardresult2_SysClose(void);
void boardresult2_CameraClose(void);

void boardresult2_ObjectSetup(void) {
    u32 i;

    omInitObjMan(0x50, 0x50);
    boardresult2_CameraInit();
    boardresult2_SysInit();
    HuWinInit();
    omAddPrcObj(boardresult2_MainProc, 0x300, 0x4000, 0);
    omAddObj(0x1000, 0, 0, -1, boardresult2_ExitCheckObjMain);

    for (i = 0; i < 16; i++) {
        do {
            boardresult2_hostAnimNoTbl[i] = MBDRand(7.0f);
        } while (i != 0 && boardresult2_hostAnimNoTbl[i - 1] == boardresult2_hostAnimNoTbl[i]);
    }
}

s16 boardresult2_ModelAnimCreate(s16 model, s32 dataNum, char *name) {
    void *data = DataRead(dataNum);
    s32 anim;
    s16 animIdx;

    anim = Hu3DAnimCreate(Hu3DData[model].hmf, data, 0, name);
    boardresult2_hostAnim = anim;
    Hu3DAnimAttrSet(anim, 1, 1);
    DataClose(data);
    animIdx = Hu3DAnimData[(s16)anim].animIdx;
    boardresult2_hostAnimLink = Hu3DAnimLink(Hu3DData[model].hmf, anim, 0, name);
    Hu3DModelRemakeStatic(model);
    return animIdx;
}

void boardresult2_ModelAnimSet(s16 model, s16 animIdx) {
    HmfAnim *anim;

    if (boardresult2_hostAnimLink != 0xFF) {
        if (animIdx == -1) {
            Hu3DModelAnimStop(Hu3DData[model].hmf);
        } else {
            Hu3DModelAnimStart(Hu3DData[model].hmf);
            anim = &Hu3DAnimData[boardresult2_hostAnimLink];
            anim->animIdx = animIdx;
            anim->rot = 0;
            anim->flags = 0;
            anim->interp = 0;
            anim->frame = 0;
        }
    }
}

s16 boardresult2_AnimDataRead(s32 dataNum) {
    void *data = DataRead(dataNum);
    s16 anim = Hu3DAnimDataCreate(data);

    DataClose(data);
    return anim;
}

void boardresult2_RankSprCreate(void) {
    BoardResult2Positions headerX = boardresult2_rankHeaderXTbl;
    BoardResult2PlayerFiles playerFiles = boardresult2_rankRowSprFileTbl;
    BoardResult2Portraits portraits = boardresult2_rankFaceSprFileTbl;
    BoardResult2Positions memberX = boardresult2_rankRowXTbl;
    void *data;
    s32 i;
    s32 j;

    boardresult2_rankHeaderSprGrp = MBDSprGrpCreate(4, 0);
    data = DataRead(0x130030);
    boardresult2_rankHeaderSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (j = 0; j < 4; j++) {
        HuSprGrpMemberSet(boardresult2_rankHeaderSprGrp->unk_0A, j, boardresult2_rankHeaderSprGrp->unk_0C[0], 0);
        HuSprPriSet(boardresult2_rankHeaderSprGrp->unk_0A, j, 99);
        HuSprAttrSet(boardresult2_rankHeaderSprGrp->unk_0A, j, 0x4000);
        HuSprPosSet(boardresult2_rankHeaderSprGrp->unk_0A, j, headerX.x[j], 104);
    }

    boardresult2_rankLabelSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130031);
    boardresult2_rankLabelSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_rankLabelSprGrp->unk_0A, 0, boardresult2_rankLabelSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_rankLabelSprGrp->unk_0A, 0, 99);
    HuSprAttrSet(boardresult2_rankLabelSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_rankLabelSprGrp->unk_0A, 0, 55, 129);

    for (i = 0; i < 4; i++) {
        boardresult2_rankRowSprGrpTbl[i] = MBDSprGrpCreate(10, 2);
        for (j = 0; j < 3; j++) {
            data = DataRead(playerFiles.files[i][j]);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1], 0);
            HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
            HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
            HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, memberX.x[j], 0);
        }

        data = DataRead(portraits.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        boardresult2_rankRowSprGrpTbl[i]->unk_0C[4] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 4, boardresult2_rankRowSprGrpTbl[i]->unk_0C[4], 0);
        HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 4, 95);
        HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 4, 0x4000);
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 4, memberX.x[3], 1);

        j = 4;
        if (GwPlayer[kakusiMasuItemHis[i]].star >= 10) {
            data = DataRead(0xC0086);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                          GwPlayer[kakusiMasuItemHis[i]].star / 10);
        HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 68, 4);

        data = DataRead(0xC0086);
        boardresult2_rankRowSprGrpTbl[i]->unk_0C[6] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 6, boardresult2_rankRowSprGrpTbl[i]->unk_0C[6],
                          GwPlayer[kakusiMasuItemHis[i]].star % 10);
        HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 93);
        HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 0x4000);
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 6, 84, 4);

        j = 6;
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 100) {
            data = DataRead(0xC0086);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        } else {
            data = DataRead(0xC003C);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        }
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                          GwPlayer[kakusiMasuItemHis[i]].coin / 100);
        HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 142, 4);

        j = 7;
        data = DataRead(0xC0086);
        boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1] = HuSprAnimRead(data);
        DataClose(data);
        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                              GwPlayer[kakusiMasuItemHis[i]].coin / 10 % 10);
        } else {
            HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, boardresult2_rankRowSprGrpTbl[i]->unk_0C[j + 1],
                              GwPlayer[kakusiMasuItemHis[i]].coin);
        }
        HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 98 - j);
        HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 0x4000);
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j + 1, 158, 4);

        if (GwPlayer[kakusiMasuItemHis[i]].coin >= 10) {
            data = DataRead(0xC0086);
            boardresult2_rankRowSprGrpTbl[i]->unk_0C[9] = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 9, boardresult2_rankRowSprGrpTbl[i]->unk_0C[9],
                              GwPlayer[kakusiMasuItemHis[i]].coin % 10);
            HuSprPriSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 90);
            HuSprAttrSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 0x4000);
            HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 9, 174, 4);
        }
    }

    for (j = 0; j < 4; j++) {
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[j]->unk_0A, 0, 111, j * 40 + 69);
    }

    boardresult2_rankTitleSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130046);
    boardresult2_rankTitleSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_rankTitleSprGrp->unk_0A, 0, boardresult2_rankTitleSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 90);
    HuSprAttrSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 160, 33);

    boardresult2_rankSubtitleSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130062);
    boardresult2_rankSubtitleSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, boardresult2_rankSubtitleSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 89);
    HuSprAttrSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 55, 41);
}

void boardresult2_RankSprKill(void) {
    s32 i;

    MBDSprGrpKill(boardresult2_rankHeaderSprGrp);
    MBDSprGrpKill(boardresult2_rankLabelSprGrp);

    for (i = 0; i < 4; i++) {
        MBDSprGrpKill(boardresult2_rankRowSprGrpTbl[i]);
    }

    MBDSprGrpKill(boardresult2_rankTitleSprGrp);
    MBDSprGrpKill(boardresult2_rankSubtitleSprGrp);
}

void boardresult2_RankDispOff(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOff(boardresult2_rankHeaderSprGrp->unk_0A, j);
    }
    HuSprDispOff(boardresult2_rankLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    HuSprDispOff(boardresult2_rankTitleSprGrp->unk_0A, 0);
    HuSprDispOff(boardresult2_rankSubtitleSprGrp->unk_0A, 0);
}

void boardresult2_RankDispOn(void) {
    s32 i;
    s32 j;

    for (j = 0; j < 4; j++) {
        HuSprDispOn(boardresult2_rankHeaderSprGrp->unk_0A, j);
    }
    HuSprDispOn(boardresult2_rankLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(boardresult2_rankRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    HuSprDispOn(boardresult2_rankTitleSprGrp->unk_0A, 0);
    HuSprDispOn(boardresult2_rankSubtitleSprGrp->unk_0A, 0);
}

s32 boardresult2_StatTopMaskGet(s32 category) {
    s32 max;
    s32 mask = 0;
    s32 i;

    switch (category) {
        case 0:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].star) {
                    max = GwPlayer[kakusiMasuItemHis[i]].star;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].star == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 1:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].coin) {
                    max = GwPlayer[kakusiMasuItemHis[i]].coin;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].coin == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 2:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].gamePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].gamePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].gamePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 3:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].coinPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].coinPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].coinPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 4:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bluePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 5:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.redPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 6:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.hatenaPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 7:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.eventPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 8:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.kupaPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 9:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.battlePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 10:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.itemPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 11:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.bankPrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
        case 12:
            for (i = 0, max = -100000; i < 4; i++) {
                if (max < GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize) {
                    max = GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize;
                }
            }
            for (i = 0; i < 4; i++) {
                if (GwPlayer[kakusiMasuItemHis[i]].stats.prize.gamblePrize == max) {
                    mask |= 1 << i;
                }
            }
            break;
    }

    if (mask == 0xF) {
        return 0;
    }
    return mask;
}

void boardresult2_StatNumUpdate(void) {
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

    for (i = 0; i < 13; i++) {
        HuSprDispOff(boardresult2_statNameSprGrp->unk_0A, i);
    }

    for (i = boardresult2_statScroll, row = 0; i < boardresult2_statScroll + 4; i++, row++) {
        HuSprDispOn(boardresult2_statNameSprGrp->unk_0A, i);
        HuSprPosSet(boardresult2_statNameSprGrp->unk_0A, i, row * 44 + 145, 52);
    }

    for (i = 0; i < 64; i++) {
        HuSprDispOff(boardresult2_statNumSprGrp->unk_0A, i);
    }

    for (i = boardresult2_statScroll, row = 0; i < boardresult2_statScroll + 4; i++, row++) {
        for (j = 0; j < 4; j++) {
            player = MBDPlayerGet(kakusiMasuItemHis[j]);
            digits = 1;
            mask = boardresult2_StatTopMaskGet(i);
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
                    value = player->stats.prize.bluePrize;
                    digits = 2;
                    break;
                case 5:
                    value = player->stats.prize.redPrize;
                    digits = 2;
                    break;
                case 6:
                    value = player->stats.prize.hatenaPrize;
                    digits = 2;
                    break;
                case 7:
                    value = player->stats.prize.eventPrize;
                    digits = 2;
                    break;
                case 8:
                    value = player->stats.prize.kupaPrize;
                    digits = 2;
                    break;
                case 9:
                    value = player->stats.prize.battlePrize;
                    digits = 2;
                    break;
                case 10:
                    value = player->stats.prize.itemPrize;
                    digits = 2;
                    break;
                case 11:
                    value = player->stats.prize.bankPrize;
                    digits = 2;
                    break;
                case 12:
                    value = player->stats.prize.gamblePrize;
                    digits = 2;
                    break;
            }
            sprintf((char *)buf, "%4d", value);

            for (k = 0; k < 4; k++) {
                if (buf[k] == ' ') {
                    HuSprDispOff(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k);
                    continue;
                }
                if (mask & (1 << j)) {
                    HuSprGrpMemberSet(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                                      boardresult2_statNumSprGrp->unk_0C[1], 0);
                } else {
                    HuSprGrpMemberSet(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                                      boardresult2_statNumSprGrp->unk_0C[0], 0);
                }
                HuSprDispOn(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k);
                HuSprPosSet(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k,
                            row * 44 + (s16)(k * 10 + 145) + offsets[digits], j * 22 + 73);
                HuSprBankSet(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k, buf[k] - '0', 0);
                HuSprAnimModeSet(boardresult2_statNumSprGrp->unk_0A, row * 16 + j * 4 + k, HUSPR_ANIM_MODE_BANK);
            }
        }
    }

    HuSprPosSet(boardresult2_statCursorSprGrp->unk_0A, 0, boardresult2_statCursor * 44 + 146, 96);
}

const BoardResult2Files4 boardresult2_statRankSprFileTbl = {
    { 0x00130047, 0x00130048, 0x00130049, 0x0013004A }
};

const BoardResult2BoardFiles boardresult2_boardNameSprFileTbl = {
    { 0x00130069, 0x0013006A, 0x0013006B, 0x0013006C,
      0x0013006D, 0x0013006E }
};

const BoardResult2Portraits boardresult2_chrNameSprFileTbl = {
    { 0x00210008, 0x00210009, 0x0021000A, 0x0021000B,
      0x0021000C, 0x0021000D, 0x0021000E, 0x0021000F }
};

const BoardResult2Portraits boardresult2_chrFaceSprFileTbl = {
    { 0x001301D5, 0x001301D6, 0x001301D7, 0x001301D8,
      0x001301D9, 0x001301DA, 0x001301DB, 0x001301DC }
};

const BoardResult2Files4 boardresult2_gameLengthSprFileTbl = {
    { 0x00130072, 0x00130073, 0x00130074, 0x00130075 }
};

const BoardResult2StatFiles boardresult2_statNameSprFileTbl = {
    { 0x0013004D, 0x0013004E, 0x0013004F, 0x00130050,
      0x00130051, 0x00130052, 0x00130053, 0x00130054,
      0x00130055, 0x00130056, 0x00130057, 0x00130058,
      0x00130059 }
};

void boardresult2_StatSprCreate(void) {
    BoardResult2Files4 rankFiles = boardresult2_statRankSprFileTbl;
    BoardResult2BoardFiles boardFiles = boardresult2_boardNameSprFileTbl;
    BoardResult2Portraits nameFiles = boardresult2_chrNameSprFileTbl;
    BoardResult2Portraits faceFiles = boardresult2_chrFaceSprFileTbl;
    BoardResult2Files4 lengthFiles = boardresult2_gameLengthSprFileTbl;
    BoardResult2StatFiles statFiles = boardresult2_statNameSprFileTbl;
    void *data;
    s32 i;

    boardresult2_boardNameSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(boardFiles.files[GwSystem.current_board_index]);
    boardresult2_boardNameSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_boardNameSprGrp->unk_0A, 0, boardresult2_boardNameSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_boardNameSprGrp->unk_0A, 0, 110);
    HuSprAttrSet(boardresult2_boardNameSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_boardNameSprGrp->unk_0A, 0, 74, 39);

    boardresult2_gameLengthSprGrp = MBDSprGrpCreate(2, 0);
    data = DataRead(0x13004B);
    boardresult2_gameLengthSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_gameLengthSprGrp->unk_0A, 0, boardresult2_gameLengthSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_gameLengthSprGrp->unk_0A, 0, 100);
    HuSprAttrSet(boardresult2_gameLengthSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_gameLengthSprGrp->unk_0A, 0, 210, 28);

    if (GwSystem.playMode & 4) {
        data = DataRead(0x13007C);
    } else {
        data = DataRead(lengthFiles.files[GwSystem.current_game_length]);
    }
    boardresult2_gameLengthSprGrp->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_gameLengthSprGrp->unk_0A, 1, boardresult2_gameLengthSprGrp->unk_0C[1], 0);
    HuSprPriSet(boardresult2_gameLengthSprGrp->unk_0A, 1, 99);
    HuSprAttrSet(boardresult2_gameLengthSprGrp->unk_0A, 1, 0x4000);
    HuSprPosSet(boardresult2_gameLengthSprGrp->unk_0A, 1, 210, 28);

    boardresult2_statLabelSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x13004C);
    boardresult2_statLabelSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_statLabelSprGrp->unk_0A, 0, boardresult2_statLabelSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_statLabelSprGrp->unk_0A, 0, 99);
    HuSprAttrSet(boardresult2_statLabelSprGrp->unk_0A, 0, 0x4000);
    HuSprPosSet(boardresult2_statLabelSprGrp->unk_0A, 0, 218, 51);

    for (i = 0; i < 4; i++) {
        boardresult2_statRowSprGrpTbl[i] = MBDSprGrpCreate(10, 2);
        data = DataRead(rankFiles.files[i]);
        boardresult2_statRowSprGrpTbl[i]->unk_0C[1] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 1, boardresult2_statRowSprGrpTbl[i]->unk_0C[1], 0);
        HuSprPriSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 1, 98);
        HuSprAttrSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 1, 0x4000);
        HuSprPosSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 1, 172, 0);

        data = DataRead(nameFiles.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        boardresult2_statRowSprGrpTbl[i]->unk_0C[2] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 2, boardresult2_statRowSprGrpTbl[i]->unk_0C[2], 0);
        HuSprPriSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 2, 97);
        HuSprAttrSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 2, 0x4000);
        HuSprPosSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 2, 36, 1);

        data = DataRead(faceFiles.files[GwPlayer[kakusiMasuItemHis[i]].chr]);
        boardresult2_statRowSprGrpTbl[i]->unk_0C[3] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 3, boardresult2_statRowSprGrpTbl[i]->unk_0C[3], 0);
        HuSprPriSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 3, 96);
        HuSprAttrSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 3, 0x4000);
        HuSprPosSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 3, 77, 1);
    }

    for (i = 0; i < 4; i++) {
        HuSprPosSet(boardresult2_statRowSprGrpTbl[i]->unk_0A, 0, 0, i * 22 + 73);
    }

    boardresult2_statArrowSprGrp = MBDSprGrpCreate(2, 0);
    for (i = 0; i < 2; i++) {
        data = DataRead(0x13002E);
        boardresult2_statArrowSprGrp->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_statArrowSprGrp->unk_0A, i, boardresult2_statArrowSprGrp->unk_0C[i], 0);
        HuSprPriSet(boardresult2_statArrowSprGrp->unk_0A, i, 90);
        HuSprAttrSet(boardresult2_statArrowSprGrp->unk_0A, i, 0x4000);
        HuSprPosSet(boardresult2_statArrowSprGrp->unk_0A, i, i * 154 + 133, 161);
    }
    HuSprAttrSet(boardresult2_statArrowSprGrp->unk_0A, 0, 1);

    boardresult2_statNameSprGrp = MBDSprGrpCreate(13, 0);
    for (i = 0; i < 13; i++) {
        data = DataRead(statFiles.files[i]);
        boardresult2_statNameSprGrp->unk_0C[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(boardresult2_statNameSprGrp->unk_0A, i, boardresult2_statNameSprGrp->unk_0C[i], 0);
        HuSprPriSet(boardresult2_statNameSprGrp->unk_0A, i, 80);
        HuSprAttrSet(boardresult2_statNameSprGrp->unk_0A, i, 0xC000);
    }

    boardresult2_statNumSprGrp = MBDSprGrpCreate(64, 0);
    data = DataRead(0x130077);
    boardresult2_statNumSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x130078);
    boardresult2_statNumSprGrp->unk_0C[1] = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 64; i++) {
        HuSprGrpMemberSet(boardresult2_statNumSprGrp->unk_0A, i, boardresult2_statNumSprGrp->unk_0C[0], 0);
        HuSprPriSet(boardresult2_statNumSprGrp->unk_0A, i, 70);
        HuSprAttrSet(boardresult2_statNumSprGrp->unk_0A, i, 0xC000);
    }

    boardresult2_statCursorSprGrp = MBDSprGrpCreate(1, 0);
    data = DataRead(0x130076);
    boardresult2_statCursorSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(boardresult2_statCursorSprGrp->unk_0A, 0, boardresult2_statCursorSprGrp->unk_0C[0], 0);
    HuSprPriSet(boardresult2_statCursorSprGrp->unk_0A, 0, 60);
    HuSprAttrSet(boardresult2_statCursorSprGrp->unk_0A, 0, 0x4000);

    boardresult2_hostGuide = MBDGuideCreate(0, 8);
    MBDGuidePosSet(boardresult2_hostGuide, 105, 8);
    HuVecCopyXYZ(&boardresult2_hostGuide->obj->scale, 0.1f, 0.1f, 0.1f);
    HuWinScaleSet(boardresult2_hostGuide->win_id, 1.0f, 1.0f);
    HuWinAttrSet(boardresult2_hostGuide->win_id, 0x4000, 0x4000);
    HuWinMesPalSet(boardresult2_hostGuide->win_id, 2, 255, 96, 96);
    HuWinMesPalSet(boardresult2_hostGuide->win_id, 4, 96, 255, 64);
    HuWinMesPalSet(boardresult2_hostGuide->win_id, 6, 64, 255, 255);
    MBDGuidePosSet(boardresult2_hostGuide, 113, 8);

    boardresult2_hostAnimTbl[0] =
        boardresult2_ModelAnimCreate(boardresult2_hostGuide->obj->omObj1->model[0], 0xA007E, "c204n_0_DEF");
    boardresult2_hostAnimTbl[1] = boardresult2_AnimDataRead(0xA007F);
    boardresult2_hostAnimTbl[2] = boardresult2_AnimDataRead(0xA0080);
    boardresult2_hostAnimTbl[3] = boardresult2_AnimDataRead(0xA0081);
    boardresult2_hostAnimTbl[4] = boardresult2_AnimDataRead(0xA0082);
    boardresult2_hostAnimTbl[5] = boardresult2_AnimDataRead(0xA0083);
    boardresult2_hostAnimTbl[6] = boardresult2_AnimDataRead(0xA0084);
    boardresult2_ModelAnimSet(boardresult2_hostGuide->obj->omObj1->model[0], boardresult2_hostAnimTbl[0]);
}

void boardresult2_StatSprKill(void) {
    s32 i;

    MBDSprGrpKill(boardresult2_boardNameSprGrp);
    MBDSprGrpKill(boardresult2_gameLengthSprGrp);
    MBDSprGrpKill(boardresult2_statLabelSprGrp);

    for (i = 0; i < 4; i++) {
        MBDSprGrpKill(boardresult2_statRowSprGrpTbl[i]);
    }

    MBDSprGrpKill(boardresult2_statArrowSprGrp);
    MBDSprGrpKill(boardresult2_statNameSprGrp);
    MBDSprGrpKill(boardresult2_statNumSprGrp);
    MBDSprGrpKill(boardresult2_statCursorSprGrp);
    MBDGuideKill(boardresult2_hostGuide);
}

void boardresult2_StatDispOff(void) {
    s32 i;
    s32 j;

    HuSprDispOff(boardresult2_boardNameSprGrp->unk_0A, 0);
    HuSprDispOff(boardresult2_gameLengthSprGrp->unk_0A, 0);
    HuSprDispOff(boardresult2_gameLengthSprGrp->unk_0A, 1);
    HuSprDispOff(boardresult2_statLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOff(boardresult2_statRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOff(boardresult2_statArrowSprGrp->unk_0A, j);
    }

    for (j = 0; j < 13; j++) {
        HuSprDispOff(boardresult2_statNameSprGrp->unk_0A, j);
    }

    for (j = 0; j < 64; j++) {
        HuSprDispOff(boardresult2_statNumSprGrp->unk_0A, j);
    }

    HuSprDispOff(boardresult2_statCursorSprGrp->unk_0A, 0);
    MBDModelDispOff(boardresult2_hostGuide->obj);
    HuWinDispOff(boardresult2_hostGuide->win_id);
}

void boardresult2_StatDispOn(void) {
    s32 i;
    s32 j;

    HuSprDispOn(boardresult2_boardNameSprGrp->unk_0A, 0);
    HuSprDispOn(boardresult2_gameLengthSprGrp->unk_0A, 0);
    HuSprDispOn(boardresult2_gameLengthSprGrp->unk_0A, 1);
    HuSprDispOn(boardresult2_statLabelSprGrp->unk_0A, 0);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            HuSprDispOn(boardresult2_statRowSprGrpTbl[i]->unk_0A, j);
        }
    }

    for (j = 0; j < 2; j++) {
        HuSprDispOn(boardresult2_statArrowSprGrp->unk_0A, j);
    }

    boardresult2_StatNumUpdate();
    HuSprDispOn(boardresult2_statCursorSprGrp->unk_0A, 0);
    MBDModelDispOn(boardresult2_hostGuide->obj);
    HuWinDispOn(boardresult2_hostGuide->win_id);

    if (boardresult2_statScroll == 0 && boardresult2_statCursor == 0) {
        HuSprDispOff(boardresult2_statArrowSprGrp->unk_0A, 0);
    }
    if (boardresult2_statScroll == 9 && boardresult2_statCursor == 3) {
        HuSprDispOff(boardresult2_statArrowSprGrp->unk_0A, 1);
    }
}

void boardresult2_StatMesSet(void) {
    s32 messages[] = {
        0x1900,
        0x1901,
        0x1902,
        0x1903,
        0x1904,
        0x1905,
        0x1906,
        0x1907,
        0x1908,
        0x1909,
        0x190A,
        0x190B,
        0x190C,
    };

    HuWinHomeClear(boardresult2_hostGuide->win_id);
    HuWinMesSet(boardresult2_hostGuide->win_id, messages[boardresult2_statScroll + boardresult2_statCursor], -1, -1);
    boardresult2_ModelAnimSet(boardresult2_hostGuide->obj->omObj1->model[0],
                               boardresult2_hostAnimTbl[boardresult2_hostAnimNoTbl[boardresult2_statScroll + boardresult2_statCursor]]);
}

void boardresult2_RankRowDropProc(void) {
    s32 index = *(s32 *)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scale;

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[index]->unk_0A, 0, 111,
                    (index * 40 + 69) + sindf(angle) * -(index * 40 + 109));
        HuPrcVSleep();
    }

    scale = -8.0f;
    HuAudFXPlay(0x178);
    for (angle = 0.0f; angle <= 1260.0f; angle += 50.0f) {
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[index]->unk_0A, 0, 111, (index * 40 + 69) + sindf(angle) * scale);
        scale += 0.3174603f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }

    HuSprPosSet(boardresult2_rankRowSprGrpTbl[index]->unk_0A, 0, 111, index * 40 + 69);
    omDelPrcObj(NULL);
}

void boardresult2_TitleDropProc(void) {
    f32 angle;
    f32 scale;

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 160, sindf(angle) * -73.0f + 33.0f);
        HuPrcVSleep();
    }

    scale = -4.0f;
    HuAudFXPlay(0x179);
    for (angle = 0.0f; angle <= 720.0f; angle += 50.0f) {
        HuSprPosSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 160, sindf(angle) * scale + 33.0f);
        scale += 0.2777778f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }

    HuSprPosSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 160, 33);
    omDelPrcObj(NULL);
}

void boardresult2_MainProc(void) {
    Process *process;
    void *data;
    f32 angle;
    f32 scale;
    s32 prevPage;
    s32 prevRow;
    s32 timer;
    s32 allCpu;
    s32 showingDetails;
    DuelHelpWin *leftWindow = NULL;
    DuelHelpWin *rightWindow = NULL;
    s32 i;

    boardresult2_bgSprGrp = MBDSprGrpCreate(6, 0);
    data = DataRead(0x13002F);
    boardresult2_bgSprGrp->unk_0C[0] = HuSprAnimRead(data);
    DataClose(data);

    for (i = 0; i < 6; i++) {
        HuSprGrpMemberSet(boardresult2_bgSprGrp->unk_0A, i, boardresult2_bgSprGrp->unk_0C[0], 0);
        HuSprPriSet(boardresult2_bgSprGrp->unk_0A, i, 200);
        HuSprAttrSet(boardresult2_bgSprGrp->unk_0A, i, 0x4000);
        HuSprPosSet(boardresult2_bgSprGrp->unk_0A, i, (i / 2) * 128 + 64, (i & 1) * 128 + 64);
    }

    boardresult2_RankSprCreate();
    showingDetails = 0;
    boardresult2_StatSprCreate();
    boardresult2_StatMesSet();
    boardresult2_StatDispOff();
    boardresult2_RankDispOn();

    for (i = 0; i < 4; i++) {
        HuSprPosSet(boardresult2_rankRowSprGrpTbl[i]->unk_0A, 0, 111, -40);
    }
    HuSprPosSet(boardresult2_rankTitleSprGrp->unk_0A, 0, 160, -40);
    HuSprPosSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 55, -40);

    WipeCreateIn(WIPE_STARS, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    for (i = 3; i >= 0; i--) {
        process = omAddPrcObj(boardresult2_RankRowDropProc, 0x1000, 0, 0x40);
        process->user_data = HuMemMemoryAlloc(process->heap, 0x20);
        *(s32 *)process->user_data = i;
        HuPrcSleep(15);
    }
    omAddPrcObj(boardresult2_TitleDropProc, 0x1000, 0, 0);
    HuPrcSleep(20);

    for (angle = 90.0f; angle < 180.0f; angle += 10.0f) {
        HuSprPosSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 55, sindf(angle) * -73.0f + 41.0f);
        HuPrcVSleep();
    }

    scale = -4.0f;
    HuAudFXPlay(0x17A);
    for (angle = 0.0f; angle <= 720.0f; angle += 50.0f) {
        HuSprPosSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 55, sindf(angle) * scale + 41.0f);
        scale += 0.2777778f;
        if (scale > 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }
    HuSprPosSet(boardresult2_rankSubtitleSprGrp->unk_0A, 0, 55, 41);

    allCpu = 0;
    for (i = 0; i < 4; i++) {
        if (!MBDPlayerComCheck(i)) {
            break;
        }
    }
    if (i == 4) {
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
            for (i = 0; i < 4; i++) {
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
                        boardresult2_RankDispOff();
                        boardresult2_StatDispOn();
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
                    prevRow = boardresult2_statCursor;
                    prevPage = boardresult2_statScroll;
                    if (ContBtnDown[GwPlayer[i].pad] & START_BUTTON) {
                        showingDetails = 0;
                        boardresult2_StatDispOff();
                        boardresult2_RankDispOn();
                    } else if (ContBtnRep[GwPlayer[i].pad] & R_JPAD) {
                        if (++boardresult2_statCursor >= 4) {
                            boardresult2_statCursor = 3;
                            if (++boardresult2_statScroll >= 10) {
                                boardresult2_statScroll = 9;
                            }
                        }
                    } else if (ContBtnRep[GwPlayer[i].pad] & L_JPAD) {
                        if (--boardresult2_statCursor < 0) {
                            boardresult2_statCursor = 0;
                            if (--boardresult2_statScroll < 0) {
                                boardresult2_statScroll = 0;
                            }
                        }
                    }
                    if (boardresult2_statCursor != prevRow || boardresult2_statScroll != prevPage) {
                        boardresult2_StatMesSet();
                        boardresult2_StatNumUpdate();
                    }
                }
            }

            if (showingDetails == 1) {
                if (boardresult2_statScroll == 0 && boardresult2_statCursor == 0) {
                    HuSprDispOff(boardresult2_statArrowSprGrp->unk_0A, 0);
                } else {
                    HuSprDispOn(boardresult2_statArrowSprGrp->unk_0A, 0);
                }
                if (boardresult2_statScroll == 9 && boardresult2_statCursor == 3) {
                    HuSprDispOff(boardresult2_statArrowSprGrp->unk_0A, 1);
                } else {
                    HuSprDispOn(boardresult2_statArrowSprGrp->unk_0A, 1);
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
    if (!(GwSystem.playMode & 4) || (GwPlayer[kakusiMasuItemHis[0]].stat & PLAYER_IS_CPU)) {
        HuAudSeqFadeOut(60);
    }
    WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    HuPrcSleep(20);
    boardresult2_RankSprKill();
    boardresult2_StatSprKill();
    MBDSprGrpKill(boardresult2_bgSprGrp);
    omSysExitReq = 1;
    while (1) {
        HuPrcVSleep();
    }
}

void boardresult2_ExitObjMain(omObjData *obj) {
    if (WipeStatGet() == 0) {
        boardresult2_CameraClose();
        boardresult2_SysClose();
        HuWinAllKill();
        omOvlReturnEx(1);
    }
}

void boardresult2_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq != 0) {
        arg0->func = boardresult2_ExitObjMain;
    }
}

void boardresult2_SysInit(void) {
    MBDModelInit();
    MBDPlayerMotInit();
    MBDSprGrpInit();
}

void boardresult2_SysClose(void) {
    MBDPlayerClose();
    MBDModelClose();
    MBDSprGrpClose();
}

void boardresult2_CameraInit(void) {
    Hu3DCamInit(2);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
}

void boardresult2_CameraClose(void) {
}
