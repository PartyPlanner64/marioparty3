#ifndef _GAME_SAVELOAD_H
#define _GAME_SAVELOAD_H

#include "ultra64.h"

void func_8004FCF0_main(void);
s32 func_8004FDC0_main(void);
void func_80050044_main(void);
void func_8005004C_main(void);
void func_80050054_main(void);
void func_8005005C_main(void);
s32 SLCommonSet(s32 writeBox);
s32 SLSaveBoard(s32 writeBox);
s32 SLSaveBoardStory(s32 writeBox);
s32 func_8005035C_main(s32 writeBox);
s32 func_80050614_main(s32 writeBox);
s32 SLLoadGameStat(void);
s32 SLLoadBoard(void);
s32 SLLoadBoardStory(void);
s32 func_80050ABC_main(void);
s32 func_80050CDC_main(void);
s32 func_80050CFC_main(void);
void SLCheckSumBoxSet(void);
s32 SLCheckSumCheck(void);
s32 func_80050DDC_main(s16 srcBoxNo, s16 dstBoxNo);
void SLCurBoxNoSet(s32 boxNo);
void func_80050E84_main(void);

#endif
