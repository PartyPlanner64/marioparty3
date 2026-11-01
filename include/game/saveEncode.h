#ifndef _GAME_SAVEENCODE_H
#define _GAME_SAVEENCODE_H

#include "ultra64.h"
#include "game/gamework_data.h"

void func_8004F290_main(void);
s32 func_8004F504_main(GW_SYSTEM *system);
s32 func_8004F524_main(GW_SYSTEM *system);
s32 SavePlayerStruct(GW_PLAYER *player);
s32 func_8004F564_main(GW_COMMON *common);
s32 func_8004F584_main(GW_STORY *story);
s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme);
void func_8004F83C_main(s32 arg0);
void func_8004F8BC_main(u8 *src, GW_SYSTEM *system);
void func_8004F90C_main(u8 *src, GW_SYSTEM *system);
void func_8004F95C_main(u8 *src, GW_PLAYER *player);
void func_8004F9AC_main(u8 *src, GW_COMMON *common);
void func_8004F9FC_main(u8 *src, GW_STORY *story);
void func_8004FA4C_main(u8 *src, u8 *destData, u8 *encodingScheme);
s32 func_8004FC84_main(void);

#endif
