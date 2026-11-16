#include "common.h"
#include "game/printfunc.h"

#define DEFAULT_X_POS 24
#define DEFAULT_Y_POS 16

#define GET_TEXT_X_POSITION(j) ((j) * 20 + 48)
#define INCREMENT_TEXT_Y_POSITION() (storydebug_textPosY += 8)

//.data
// screen scissor dimensions
RectF storydebug_scissorRect = { 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT };
s16 storydebug_dumpOfs = 0; // only used once and never written to?
u16 storydebug_textPosY = DEFAULT_Y_POS;

u8 storydebug_dumpBuf[512] BSS;

void storydebug_ExitCheckObjMain(omObjData *);
void storydebug_StoryInfoProc(void);
void storydebug_PlayerInfoDraw(s16 arg0);
void storydebug_StoryInfoDraw(void);

void storydebug_ObjectSetup(void) {
    omInitObjMan(10, 10);
    omGameSysInit();
    Hu3DCamInit(1);
    Hu3DCameraScissorSet(0, &storydebug_scissorRect);
    Hu3DGLightMaxSet(1);
    Hu3DGLightColorSet(0, 120, 120, 120);
    Hu3DGLightColorSet(1, 64, 64, 96);
    Hu3DGLightDirSet(1, -100.0f, 100.0f, 100.0f);
    omAddPrcObj(storydebug_StoryInfoProc, 0xE000, 0, 0);
    omAddObj(0x500, 0, 0, -1, storydebug_ExitCheckObjMain);
    WipeCreateIn(WIPE_TYPE_NORMAL, 0);
}

void storydebug_DumpBufDraw(void) {
    s32 var_s2;
    s32 i, j;

    var_s2 = storydebug_dumpOfs;
    fontcolor = FONT_COLOR_WHITE;

    for (i = 0; i < 16 && (i * 8) < ARRAY_COUNT(storydebug_dumpBuf); i++) {
        sprintf(omDBGStrBuf, "%3X:", var_s2);
        print8(40, (i * 10 + 48), omDBGStrBuf);
        for (j = 0; j < 8; j++) {
            sprintf(omDBGStrBuf, "%02X", storydebug_dumpBuf[var_s2 + j]);
            print8((j * 24 + 80), (i * 10 + 48), omDBGStrBuf);
        }
        var_s2 += 8;
    }
}

void storydebug_PlayerInfoProc(void) {
    s16 var_s1;
    s16 i;

    var_s1 = 0;
    SLCurBoxNoSet(0);
    SLLoadBoardStory();
    while (1) {
        HuPrcVSleep();
        if (HuPadBtnDown[0] & A_BUTTON) {
            var_s1 = (var_s1 == 0) ? 2 : 0;
        }

        storydebug_textPosY = DEFAULT_Y_POS;

        for (i = var_s1; i < var_s1 + 2; i++) {
            storydebug_PlayerInfoDraw(i);
        }
    }
}

void storydebug_PlayerInfoDraw(s16 playerIndex) {
    char buffer[256];

    fontcolor = FONT_COLOR_RED;
    sprintf(buffer, "PLAYER%d", playerIndex);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    fontcolor = FONT_COLOR_WHITE;

    sprintf(buffer, "PAD:%2X,CHR:%2X,STAT:%2x,GCOIN:%4X", GwPlayer[playerIndex].pad, GwPlayer[playerIndex].chr, GwPlayer[playerIndex].stat, GwPlayer[playerIndex].gameCoin);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "BCOIN:%4X,COIN:%4X,CCOIN:%4x", GwPlayer[playerIndex].bonusCoin, GwPlayer[playerIndex].coin, GwPlayer[playerIndex].checkCoin);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "STAR:%2X,CLINK:%2X,CIDX:%2x,NLINK:%2X", GwPlayer[playerIndex].star, GwPlayer[playerIndex].clink, GwPlayer[playerIndex].cidx, GwPlayer[playerIndex].nlink);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "NIDX:%2X,NNLINK:%2X,NNIDX:%2X,BLINK:%2X", GwPlayer[playerIndex].nidx, GwPlayer[playerIndex].nnlink, GwPlayer[playerIndex].nnidx, GwPlayer[playerIndex].blink);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "BIDX:%2X,REV:%2X,ITEM0#%2d,ITEM1#%2d", GwPlayer[playerIndex].bidx, GwPlayer[playerIndex].rev, GwPlayer[playerIndex].itemNo[0], GwPlayer[playerIndex].itemNo[1]);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "ITEM2#%2d,ITURN:%2X,COL:%2X,TURN:%2X", GwPlayer[playerIndex].itemNo[2], GwPlayer[playerIndex].itemTurn, GwPlayer[playerIndex].color, GwPlayer[playerIndex].turn);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "GPRZ:%4X,CPRZ:%4X,HPRZ:%4X", GwPlayer[playerIndex].gamePrize, GwPlayer[playerIndex].coinPrize, GwPlayer[playerIndex].stats.prize.hatenaPrize);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "RPRZ:%2X,BPRZ:%2X,EPRZ:%2X,KPRZ:%2X", GwPlayer[playerIndex].stats.prize.redPrize, GwPlayer[playerIndex].stats.prize.bluePrize, GwPlayer[playerIndex].stats.prize.eventPrize, GwPlayer[playerIndex].stats.prize.kupaPrize);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "BTLPRZ:%2X,IPRZ:%2X,BNKPRZ:%2X", GwPlayer[playerIndex].stats.prize.battlePrize, GwPlayer[playerIndex].stats.prize.itemPrize, GwPlayer[playerIndex].stats.prize.bankPrize);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();

    sprintf(buffer, "GBPRZ#%2d,DUEL#%2d", GwPlayer[playerIndex].stats.prize.gamblePrize, GwPlayer[playerIndex].stats.prize.duelNo);
    print8(DEFAULT_X_POS, storydebug_textPosY, buffer);
    INCREMENT_TEXT_Y_POSITION();
}

void storydebug_ExitCheckObjMain(omObjData *arg0) {
    if (omSysExitReq != 0) {
        omOvlReturnEx(1);
    }
}

void storydebug_StoryInfoProc(void) {
    s16 i, j;

    SLCurBoxNoSet(0);
    SLLoadStory();
    while (1) {
        HuPrcVSleep();
        storydebug_StoryInfoDraw();
        if (HuPadBtnDown[0] & A_BUTTON) {
            for (j = 0; j < ARRAY_COUNT(GwStory.progress.fields.unk3); j++) {
                GwStory.progress.fields.unk3[j] = 0;
            }
            for (i = 0; i < ARRAY_COUNT_2D_ROWS(GwStory.unk10); i++) {
                for (j = 0; j < ARRAY_COUNT_2D_COLS(GwStory.unk10); j++) {
                    GwStory.unk10[i][j] = 0;
                }
            }
            for (j = 0; j < ARRAY_COUNT(GwStory.unk58); j++) {
                GwStory.unk58[j] = 0;
            }
            for (j = 0; j < ARRAY_COUNT(GwStory.unk5E); j++) {
                GwStory.unk5E[j] = 0;
            }
            SLSaveStory(1);
        }
        storydebug_textPosY = DEFAULT_Y_POS;
    }
}

void storydebug_StoryInfoDraw(void) {
    char sp18[0x120];
    s16 i, j;

    fontcolor = FONT_COLOR_WHITE;
    sprintf(sp18, "INDEX:%2X,CHR:%2X,DIF:%2X,LAST:%2X", GwStory.unk0, GwStory.unk1, GwStory.unk2, GwStory.progress.fields.unkF);
    print8(DEFAULT_X_POS, storydebug_textPosY, sp18);
    INCREMENT_TEXT_Y_POSITION();

    print8(DEFAULT_X_POS, storydebug_textPosY, "SC:");
    // iterate over first half of the array
    for (j = 0; j < ARRAY_COUNT(GwStory.progress.fields.unk3) / 2; j++) {
        sprintf(sp18, "%2X", GwStory.progress.fields.unk3[j]);
        print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
    }

    INCREMENT_TEXT_Y_POSITION();

    // iterate over last half of the array
    for (j = 0; j < ARRAY_COUNT(GwStory.progress.fields.unk3) / 2; j++) {
        sprintf(sp18, "%2X", GwStory.progress.fields.unk3[j + 6]);
        print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
    }

    INCREMENT_TEXT_Y_POSITION();

    print8(DEFAULT_X_POS, storydebug_textPosY, "HS:");

    for (i = 0; i < ARRAY_COUNT_2D_ROWS(GwStory.unk10); i++) {
        // iterate over first half of array
        for (j = 0; j < ARRAY_COUNT_2D_COLS(GwStory.unk10) / 2; j++) {
            sprintf(sp18, "%2X", GwStory.unk10[i][j]);
            print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
        }

        INCREMENT_TEXT_Y_POSITION();

        // iterate over last half of array
        for (j = 0; j < ARRAY_COUNT_2D_COLS(GwStory.unk10) / 2; j++) {
            sprintf(sp18, "%2X", GwStory.unk10[i][j + 6]);
            print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
        }

        INCREMENT_TEXT_Y_POSITION();
    }

    print8(DEFAULT_X_POS, storydebug_textPosY, "HL:");

    for (j = 0; j < ARRAY_COUNT(GwStory.unk58); j++) {
        sprintf(sp18, "%2X", GwStory.unk58[j]);
        print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
    }

    INCREMENT_TEXT_Y_POSITION();

    print8(DEFAULT_X_POS, storydebug_textPosY, "HD:");

    for (j = 0; j < ARRAY_COUNT(GwStory.unk5E); j++) {
        sprintf(sp18, "%2X", GwStory.unk5E[j]);
        print8(GET_TEXT_X_POSITION(j), storydebug_textPosY, sp18);
    }

    INCREMENT_TEXT_Y_POSITION();
}
