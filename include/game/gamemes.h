#ifndef _GAME_GAMEMES_H
#define _GAME_GAMEMES_H

#include "ultra64.h"
#include "humath.h"

#define GMES_ID_NONE -1

#define GMES_MAX 8

#define GMES_STRMAX 16

typedef struct {
    /* 0x00 */ u8 mesNo;
    /* 0x01 */ u8 stat;
    /* 0x02 */ s8 unk02;
    /* 0x03 */ u8 tpLvl;
    /* 0x04 */ s16 time;
    /* 0x06 */ s16 timeMax;
    /* 0x08 */ s16 subMode;
    /* 0x0A */ s16 work;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s16 strGId[GMES_STRMAX];
    /* 0x40 */ s16 strSprId[GMES_STRMAX];
    /* 0x60 */ Vec2f pos;
    /* 0x68 */ Vec2f scale;
    /* 0x70 */ f32 angle;
} GAMEMES; // Size 0x74

#define GMES_MES_0 0 // START (ALT?)
#define GMES_MES_1 1 // START (ALT?)
#define GMES_MES_2 2 // START (ALT?)
#define GMES_MES_3 3
#define GMES_MES_4 4
#define GMES_MES_5 5
#define GMES_MES_MG_START 6
#define GMES_MES_7 7
#define GMES_MES_8 8
#define GMES_MES_9 9
#define GMES_MES_10 10
#define GMES_MES_11 11 // FINISH (ALT?)
#define GMES_MES_12 12 // FINISH (ALT?)
#define GMES_MES_13 13 // TIME UP
#define GMES_MES_14 14
#define GMES_MES_15 15
#define GMES_MES_16 16
#define GMES_MES_MG_FINISH 17
#define GMES_MES_18 18
#define GMES_MES_19 19
#define GMES_MES_20 20
#define GMES_MES_21 21
#define GMES_MES_MG_WINNER 22
#define GMES_MES_MG_LOSER 23
#define GMES_MES_24 24
#define GMES_MES_25 25
#define GMES_MES_TIMER 26
#define GMES_MES_MG_RECORD 27
#define GMES_MES_28 28
#define GMES_MES_29 29 // GAME_OVER
#define GMES_MES_MG_WINNERS_2 30
#define GMES_MES_31 31 // TIME UP (ALT?)
#define GMES_MES_MG_DRAW 32
#define GMES_MES_33 33 // GOAL
#define GMES_MES_MG_WINNERS_3 34
#define GMES_MES_MG_WINNERS_4 35
#define GMES_MES_36 36 // GOT ITEM
#define GMES_MES_37 37 // GOT ITEM?

#define GMES_STAT_NONE 0
#define GMES_STAT_EXIST (1 << 0)
#define GMES_STAT_TIMEEND (1 << 1)
#define GMES_STAT_KILL (1 << 2)

void GMesInit(void);
s16 GMesCreate(s16 mesNo, ...);
void GMesSprKill(GAMEMES *gMes);
s32 GMesStatGet(void);
void GMesPosSet(s16 mesId, f32 x, f32 y);
void GMesKill(s16 mesId);
void GMesClose(void);
void GameMesStub(void);
void GMesTimerValueSet(s16);
void GMesTimerEnd(void);
void GMesFontMesCreate(const s16 *, s32);
s32 GameMesStrConv2(void *, void *);

s32 GMesMgNoGet(void);
void GMesExec(Gfx **arg0);
u8 GMesStatIdGet(s16 i);
void GMesTimeMaxSet(s16 i, s16 value);
s32 GameMesKillCheck(void);
void GMesMaxWaitSet(s16 countdown);
s32 GameMesStart0Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart1Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart2Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStartStrCreate(GAMEMES *gMes);
s32 GameMesStart3Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart4Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart5Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgStartExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart7Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart8Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart9Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStart10Exec(GAMEMES *gMes, Gfx **gfx);
s16 GameMesStrInit(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4);
s16 GameMesStrCreate(GAMEMES *gMes, char *str, u8 flags, s16 arg3, s16 arg4);
s16 GameMesStrCreateScale(GAMEMES *gMes, u8 *str, u8 flags, s16 x, s16 y, f32 scaleX, f32 scaleY);
u32 GameMesCharCreate(u8 *str, u8 flags);
s32 GameMesCharFileGet(u8 *str, s32 flags, s32 *idx);
s32 GameMesCharWidthGet(u8 *str, s32 mode, u8 flags, s32 *width);
s16 GameMesAnimRead(s16 fileNo);
s16 CreateFontChar(u8 c, u8 flags);
void GMesSprClose(GAMEMES *gMes);
s32 GameMesFinish11Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesStrPopExec(GAMEMES *gMes, char *str, s32 seNo);
s32 GameMesImageExec(GAMEMES *gMes, s32 fileNo, s32 seNo);
s32 GameMesFinish12Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesTimeUpExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinishStrCreate(GAMEMES *gMes);
s32 GameMesFinish14Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish15Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish16Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgFinishExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish18Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish19Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish20Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesFinish21Exec(GAMEMES *gMes, Gfx **gfx);
void GameMesImageCreate(GAMEMES *gMes, s32 fileNo);
s32 GameMesMgWinnerExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgLoserExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMes24Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMes25Exec(GAMEMES *gMes, Gfx **gfx);
s32 GMesTimerExec(GAMEMES *gMes, Gfx **arg1);
s32 GameMesMgRecordExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesTimeUp2Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesGoalExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesGameOverExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesReadyGoExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgWinners2Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgDrawExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgWinners3Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesMgWinners4Exec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesGotItemExec(GAMEMES *gMes, Gfx **gfx);
s32 GameMesGotItem2Exec(GAMEMES *gMes, Gfx **gfx);
u16 GameMesCharConv(u16 code);
s32 GameMesStrConv(u8 *dst, u8 *src);
void GameMesMgStub(s32 mgIndex);
s32 GameMesOvlTypeGet(void);
s32 GameMesOvlOfsGet(void);

#endif
