#ifndef _GAME_SAVEENCODE_H
#define _GAME_SAVEENCODE_H

#include "ultra64.h"
#include "game/gamework_data.h"

void SaveSchemeInit(void);
s32 SaveBoardSystemEncode(GW_SYSTEM *system);
s32 SaveStorySystemEncode(GW_SYSTEM *system);
s32 SavePlayerStruct(GW_PLAYER *player);
s32 SaveCommonEncode(GW_COMMON *common);
s32 SaveStoryEncode(GW_STORY *story);
s32 SaveFileEncode(u8 *sourceData, u8 *encodingScheme);
void SaveBitWrite(s32 arg0);
void SaveBoardSystemDecode(u8 *src, GW_SYSTEM *system);
void SaveStorySystemDecode(u8 *src, GW_SYSTEM *system);
void SavePlayerDecode(u8 *src, GW_PLAYER *player);
void SaveCommonDecode(u8 *src, GW_COMMON *common);
void SaveStoryDecode(u8 *src, GW_STORY *story);
void SaveFileDecode(u8 *src, u8 *destData, u8 *encodingScheme);
s32 SaveBitRead(void);

#endif
