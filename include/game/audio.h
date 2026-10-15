#ifndef _AUDIO_H
#define _AUDIO_H

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

s16 HuAudSeqPlay(s16 musId);
s16 func_80003310_main(s16 arg0);
s16 func_8004A5C4_main(s16);
void HuAudSeqFadeOut(s16 speed);
s16 HuAudFXPlay(s16 seId);
void func_8004AAD0_main(s16, s8);
void func_8004AB0C_main(s32);
void HuAudFXPitchSet(s32 seNo, s32 pitch);
s16 CharFXPlay(s16 seId, u8 charNo);
s32 func_8004AC5C_main(s16 arg0, s16 arg1);
s16 func_8004AC98_main(s16, s16);
s16 func_8004ACE0_main(s16 seId, s16 playerIdx);
void HuAudFXStop(s32 seNo);
void func_8004AEF0_main(s16, s32);
void omVibrate(s16 player, s16 duration, s16 off, s16 on);

#endif
