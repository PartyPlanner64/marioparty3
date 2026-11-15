#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

#include "ultra64.h"

#ifndef NO_EXTERN_VARIABLES
extern u16 ContBtnDown[];
extern s16 ContBtnRep[];
extern s16 ContRepCnt[];
extern u16 ContBtnOld[];
extern u16 ContBtn[];

extern s8 HuPadStkX[];
extern s16 HuPadBtn[];
extern s8 HuPadStkY[];
#endif

void ContDataInit(void);
void ContDataUpdate(void);

#endif
