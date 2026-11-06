#ifndef _GAME_GAMEWORK_H
#define _GAME_GAMEWORK_H

#include "ultra64.h"

extern s32 D_800A12C0_main;
extern s32 D_800A12C4_main;
extern s16 D_800A12C8_main;
extern s32 D_800A12CC_main;
extern s8 D_800A12D0_main;
extern s32 D_800A12D4_main;
extern s32 D_800A12D8_main;

void GWInit(void);
void GWMgNoSet(s8 arg0);
void GWMgBitGet(s16 bitPos, s16 *byteIdx, s16 *bitIdx);
void GWMgUnlockSet(s16 bitPos);
void GWMgUnlockReset(s16 bitPos);
s16 GWMgUnlockCheck(s16 arg0);
void GWMgRecordSet(s16 arg0, u32 arg1);
u16 GWMgRecordGet(s16 arg0);
void GWBoardNoSet(s8 boardIndex);
u8 *GWBoardRecordGet(s16 arg0);
u8 GWPlayNumGet(s16 arg0);
void GWPlayNumInc(s16 arg0);
void GWCharPlayNumInc(s16 boardNo, s16 charNo);
s32 func_80035E3C_main(s16 arg0);
void func_80035E60_main(s16 arg0);
void func_80035E88_main(s16 arg0);
s32 _CheckFlag(s32 flag);
void _SetFlag(s32 flag);
void _ClearFlag(s32 flag);
s32 GWBoardFlagCheck(s32 flag);
void GWBoardFlagSet(s32 flag);
void GWBoardFlagClear(s32 flag);
void GWContErrorSet(void);
s32 GWContErrorGet(void);

#endif
