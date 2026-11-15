#ifndef _GAME_PAUSE_H
#define _GAME_PAUSE_H

#include "ultra64.h"
#include "game/object.h"

#ifndef NO_EXTERN_VARIABLES
extern u8 winPauseF;
#endif

void MgCoinReset(void);
omObjData *HuAudCharVoicePlay(s32 arg0);
omObjData* HuAudCharVoicePlayPlayer(u32, s16, s16);

void GameMesPauseCreate(void);
void ExecPause(void);
void GamePauseNameSet(s16 arg0, s16 arg1);
void GamePauseEnd(void);
s16 GamePauseWinCreate(s16 arg0, s16 arg1);
s32 HuAudVoiceTypeGet(s32 arg0);
void HuAudCharVoiceInit(void);
void HuAudCharVoiceExec(omObjData *object);
omObjData *HuAudCharVoicePlayPan(u32 arg0, s16 arg1);
omObjData *HuAudCharVoicePlayEx(u32 arg0, s16 arg1, s16 arg2, s16 arg3);

#endif
