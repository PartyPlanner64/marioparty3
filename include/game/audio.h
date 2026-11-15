#ifndef _GAME_AUDIO_H
#define _GAME_AUDIO_H

#include "ultra64.h"

typedef struct {
    f32 *unk00;
    f32 *unk04;
    f32 *unk08;
    f32 *unk0C;
    u8 *unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s16 unk34;
} UnkAudioObjData;

extern u16 HuAudSeEnableF;
extern u16 HuAudStat;

s16 HuAudSeqPlay(s16 musId);
s16 HuAudSubSeqPlay(s16);
void HuAudSeqFadeOut(s16 speed);
s16 HuAudFXPlay(s16 seId);
void HuAudFXVolSet(s16, s8);
void HuAudFXAllFadeOut(s32);
void HuAudFXPitchSet(s32 seNo, s32 pitch);
s16 CharFXPlay(s16 seId, u8 charNo);
s32 _HuAudPlayerFXPlay(s16 arg0, s16 arg1);
s16 HuAudPlayerFXPlay(s16, s16);
s16 PlayerFXPlay(s16 seId, s16 playerIdx);
void HuAudFXPanning(s16 arg0, s16 arg1);
void HuAudFXStop(s32 seNo);
void HuAudFXFadeOut(s16, s32);
void omVibrate(s16 player, s16 duration, s16 off, s16 on);

void HuAudSubSeqParamSet(s32 arg0);
void HuAudSeqVolFadeOut(s16 duration);
void HuAudSeqVolFadeIn(s16 duration);
void HuAudSubSeqVolFadeOut(s16 duration);
void HuAudSubSeqVolFadeIn(s16 duration);
void HuAudSubSeqPlayMute(s16 musId);
void HuAudSeqStop(void);
void HuAudSeqVolSet(s8 volume);
void HuAudSeqMasterVolSet(s8 volume);
void HuAudSeqTempoSet(s16 arg0);
s16 HuAudSeqTempoGet(void);
void HuAudFXMasterVolSet(s8 volume);
void HuAudFXAllStop(void);
s16 HuAudFXIdStop(s16 seId);
void HuAudFXAllPanning(s16 arg0);
void HuAudStatUpdate(void);
void HuAudFXAllVolFadeDown(s16 duration);
void HuAudFXAllVolRestore(void);
void HuAudPlayerParamCopy(void);
u16 HuAudDummy(void);
void HuAudInit(void);

#endif
