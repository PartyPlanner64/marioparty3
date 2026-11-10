#ifndef _GAME_HMFLOAD_H
#define _GAME_HMFLOAD_H

#include "ultra64.h"
#include "game/hu3d.h"

void LoadHMF(HmfData *hmf, void *fileData, s32 flags);
void func_8000F978_main(HmfData *hmf);
s16 func_8000FDAC_main(void *arg0, s16 arg1);
u8 *func_80010A38_main(s32 tag, void *start, void *end);
void *func_80010AC8_main(void *arg0);
void func_8001116C_main(s8 *arg0, u16 *arg1, u16 *arg2, u16 *arg3);
s16 func_80011334_main(HmfData *hmf, void *arg1, s16 index);
s16 func_80011460_main(const u8 *arg0);

#endif
