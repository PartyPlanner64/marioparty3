#ifndef _GAME_HMFLOAD_H
#define _GAME_HMFLOAD_H

#include "ultra64.h"
#include "game/hu3d.h"

void LoadHMF(HmfData *hmf, void *fileData, s32 flags);
void MotionNodeFree(HmfData *hmf);
s16 HmfRecordCount(void *arg0, s16 arg1);
u8 *HmfChunkSearch(s32 tag, void *start, void *end);
void *HmfChunkNext(void *arg0);
void FaceNormalCalc(s8 *arg0, u16 *arg1, u16 *arg2, u16 *arg3);
s16 GetString(HmfData *hmf, void *arg1, s16 index);
s16 HmfNameHash(const u8 *arg0);

#endif
