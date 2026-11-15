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

#ifndef NO_EXTERN_VARIABLES
extern u8 msmMonoF;
#endif

s32 msmSysLoadFx(void);
void msmInit(str800D5298 *cfg);
s32 msmSysInit(str800D5298 *cfg);
s32 msmSysIsPlay(void);
void msmSysGetConfig(str800D5298 *cfg);
s32 msmSysGetFxCount(void);
s32 msmSysGetVersion(void);
s32 msmSysDummy(s32 arg0);
s32 msmSysGetUnk72(void);
void msmSysSetOutputMode(u32 mono);
s32 msmSysGetFxId(void);
void msmFioRead(void *dst, void *romAddr, s32 size, s32 chunkSize);
void *msmMemAlloc(s32 size);
void msmSysSetUnk72(s16 arg0);
s32 msmSysError(s32 arg0, s32 arg1);
s16 msmSysVolExpand(s32 arg0);
void msmMusEventProc(void);
void msmMusPushEvent(s32 player, s32 type, s32 arg);
void msmMusPeriodicProc(void);
void msmMusDeleteAll(void);
void msmMusClear(void);
ALMicroTime msmMusInitOsc(void **oscState, f32 *initVal, u8 oscType, u8 oscRate, u8 oscDepth, u8 oscDelay);
ALMicroTime msmMusUpdateOsc(void *oscState, f32 *updateVal);
void msmMusStopOsc(void *oscState);
f32 msmPitchToRatio(s32 arg0);
s32 msmMusPlayDefault(s32 trackId);
s32 msmMusGetStatus(s32 playerIdx);
s32 msmMusGetTrackCount(void);
s32 msmMusGetTrack(s32 playerIdx);
s32 msmMusGetPlayerCount(void);
s32 msmMusGetNumPlay(void);
void msmMusStop(s32 playerIdx);
void msmMusSetVolume(s32 playerIdx, s32 vol);
s32 msmMusGetVolume(s32 playerIdx);
void msmMusSetMasterVolume(s32 vol);
void msmMusSetTempo(s32 playerIdx, s32 bpm);
s32 msmMusGetTempo(s32 playerIdx);
void msmMusFadeOut(s32 playerIdx, s32 time);
s32 msmMusGetFadeTime(s32 playerIdx);
void msmMusPause(s32 playerIdx);
void msmMusResume(s32 playerIdx, s32 fadeTime);
void msmSeCmdProc(void);
s32 msmSeReadVarLen(u8 **cursor);
void msmSePauseSub(void);
void msmSeFade(void);
void msmSePushCmd(s32 voiceSlot, s32 cmdType, s32 cmdArg);
void msmSePushCmdF(s32 voiceSlot, s32 cmdType, f32 cmdArg);
void msmSePeriodicProc(void);
void msmSeStopAllSounds(void);
void msmSeClear(void);
s32 msmSePlayDefault(s32 seId);
s32 msmSePlay(s32 seId, SePlayParam *param);
s32 msmSeAllocVoice(s32 seId, s32 layer, s32 slot, s32 variant);
void msmSeSetupVoice(s32 seId, s32 slot, u8 priority, SePlayParam *param);
s32 msmSeGetCount(void);
s32 msmSeGetNumPlay(void);
s32 msmSeGetStatus(s32 slot);
s32 msmSeSearchEntry(s32 seId);
s32 msmSeGetEntryLayers(s32 seId);
void msmSeSetMasterVolume(s32 vol);
void msmSeSetVolume(s32 slot, s32 vol);
void msmSeSetPitch(s32 slot, s32 pitch);
void msmSeSetPan(s32 slot, s32 pan);
void msmSeSetFxMix(s32 slot, s32 fxMix);
void msmSeStop(s32 slot);
void msmSeFadeOut(s32 time);
s32 msmSeGetFadeTime(void);
void msmSePauseAll(void);
void msmSeResumeAll(s32 time);

#endif
