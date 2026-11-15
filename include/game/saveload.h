#ifndef _GAME_SAVELOAD_H
#define _GAME_SAVELOAD_H

#include "ultra64.h"

typedef struct SaveCommonBuf {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 boxNo;
    /* 0x02 */ u8 unk_02[0x14];
    /* 0x16 */ u16 checksum;
} SaveCommonBuf; // sizeof 0x18

#ifndef NO_EXTERN_VARIABLES
extern u8 SLFormatFlags;
#endif

void SLSaveDataInit(void);
s32 SLInit(void);
void SLStub0(void);
void SLStub1(void);
void SLStub2(void);
void SLStub3(void);
s32 SLCommonSet(s32 writeBox);
s32 SLSaveBoard(s32 writeBox);
s32 SLSaveBoardStory(s32 writeBox);
s32 SLSaveStory(s32 writeBox);
s32 SLSaveStorySystem(s32 writeBox);
s32 SLLoadGameStat(void);
s32 SLLoadBoard(void);
s32 SLLoadBoardStory(void);
s32 SLLoadStory(void);
s32 SLLoadCommon(void);
s32 SLSaveCommon(void);
void SLCheckSumBoxSet(void);
s32 SLCheckSumCheck(void);
s32 SLBoxCopy(s16 srcBoxNo, s16 dstBoxNo);
void SLCurBoxNoSet(s32 boxNo);
void SLPadAssign(void);

#endif
