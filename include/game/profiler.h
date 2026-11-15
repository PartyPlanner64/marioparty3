#ifndef _GAME_PROFILER_H
#define _GAME_PROFILER_H

#include "ultra64.h"

void HuProfInit(s16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void HuProfRecordAwaitRsp(void);
s16 HuProfCpuBegin(u8 red, u8 green, u8 blue);
void HuProfCpuEnd(s16 sampleIdx);
s16 HuProfRspBegin(u8 arg0, u8 arg1, u8 arg2);
void HuProfRspEnd(s16 sampleIdx);
void HuProfFrameBegin(void);
void HuProfFrameEnd(void);
void HuProfRspReset(void);
void HuProfDummy(void);
void HuProfDrawTask(void);

#endif
