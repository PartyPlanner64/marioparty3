#ifndef _GAME_PAUSE_H
#define _GAME_PAUSE_H

#include "ultra64.h"
#include "game/object.h"

extern u8 D_800CB99C_main;

void func_80045350_main(void);
omObjData *func_80045ED0_main(s32 arg0);
omObjData* func_80045F1C_main(u32, s16, s16);

void GameMesPauseCreate(void);
void ExecPause(void);
void func_80045964_main(s16 arg0, s16 arg1);
void func_80045A90_main(void);
s16 func_80045B24_main(s16 arg0, s16 arg1);
s32 func_80045BF0_main(s32 arg0);
void func_80045C2C_main(void);
void func_80045D38_main(omObjData *object);
omObjData *func_80045EF4_main(u32 arg0, s16 arg1);
omObjData *func_80045F48_main(u32 arg0, s16 arg1, s16 arg2, s16 arg3);
void func_80046030_main(s16 arg0, s16 arg1);
void func_800461B4_main(s16 arg0);
void func_800461D8_main(void);
void func_80046558_main(s16 arg0);
void func_800465A8_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3);

#endif
