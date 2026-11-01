#ifndef _GAME_MSM_H
#define _GAME_MSM_H

#include "ultra64.h"
#include "common_structs.h"

/* Optional parameters for starting a sound effect. */
typedef struct {
    /* 0x00 */ s32 flags; // which of the fields below are valid
    /* 0x04 */ s32 slot;
    /* 0x08 */ s32 variant;
    /* 0x0C */ s32 vol;
    /* 0x10 */ s32 pitch;
    /* 0x14 */ s32 pan;
    /* 0x18 */ s32 fxMix;
    /* 0x1C */ s32 angle;
    /* 0x20 */ f32 dist;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
} SePlayParam; // size: 0x2C

s32 func_80000650_main(void);
void func_800007FC_main(str800D5298 *cfg);
s32 msmSysInit(str800D5298 *cfg);
s32 func_80000DF0_main(void);
void func_80000EA8_main(str800D5298 *cfg);
s32 func_80000EDC_main(void);
s32 func_80000EFC_main(void);
s32 func_80000F08_main(s32 arg0);
s32 func_80000F10_main(void);
void func_80000F30_main(u32 mono);
s32 func_80000FC4_main(void);
void func_80000FE4_main(void *dst, void *romAddr, s32 size, s32 chunkSize);
void *func_800010B8_main(s32 size);
void func_8000110C_main(s16 arg0);
s32 func_80001134_main(s32 arg0, s32 arg1);
s16 func_8000113C_main(s32 arg0);
void func_80001408_main(void);
void func_80002300_main(s32 player, s32 type, s32 arg);
void func_800023B4_main(void);
void func_80002528_main(void);
void func_800025C0_main(void);
ALMicroTime func_800025CC_main(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay);
ALMicroTime func_80002A28_main(void *oscState, f32 *updateVal);
void func_800032B4_main(void *oscState);
f32 func_800032CC_main(s32 arg0);
s32 msmMusPlayDefault(s32 trackId);
s32 msmMusGetStatus(s32 playerIdx);
s32 func_80003524_main(void);
s32 func_8000354C_main(s32 playerIdx);
s32 func_80003598_main(void);
s32 func_800035C0_main(void);
void msmMusStop(s32 playerIdx);
void msmMusSetVolume(s32 playerIdx, s32 vol);
s32 func_800037C4_main(s32 playerIdx);
void msmMusSetMasterVolume(s32 vol);
void msmMusSetTempo(s32 playerIdx, s32 bpm);
s32 func_800038EC_main(s32 playerIdx);
void func_800039A4_main(s32 playerIdx, s32 time);
s32 func_80003A24_main(s32 playerIdx);
void func_80003A70_main(s32 playerIdx);
void func_80003B70_main(s32 playerIdx, s32 fadeTime);
void func_80003FB4_main(void);
s32 func_80005804_main(u8 **cursor);
void func_80006830_main(void);
void func_800068B8_main(void);
void func_80006CD4_main(s32 voiceSlot, s32 cmdType, s32 cmdArg);
void func_80006D80_main(s32 voiceSlot, s32 cmdType, f32 cmdArg);
void func_80006E30_main(void);
void func_80006FC4_main(void);
void func_80007058_main(void);
s32 msmSePlayDefault(s32 seId);
s32 msmSePlay(s32 seId, SePlayParam *param);
s32 func_800072A4_main(s32 seId, s32 layer, s32 slot, s32 variant);
void func_800076B8_main(s32 seId, s32 slot, u8 priority, SePlayParam *param);
s32 func_800078A4_main(void);
s32 func_800078CC_main(void);
s32 msmSeGetStatus(s32 slot);
s32 func_8000793C_main(s32 seId);
s32 func_800079CC_main(s32 seId);
void msmSeSetMasterVolume(s32 vol);
void msmSeSetVolume(s32 slot, s32 vol);
void msmSeSetPitch(s32 slot, s32 pitch);
void msmSeSetPan(s32 slot, s32 pan);
void func_80007D2C_main(s32 slot, s32 fxMix);
void msmSeStop(s32 slot);
void func_80007EC0_main(s32 time);
s32 func_80007EF8_main(void);
void func_80007F24_main(void);
void func_80007FD4_main(s32 time);

#endif
