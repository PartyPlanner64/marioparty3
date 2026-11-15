#ifndef _GAME_EFFECT_H
#define _GAME_EFFECT_H

#include "ultra64.h"
#include "game/object.h"

#define EFFECT_GROUP_MAX 8

typedef struct EffectGroupModel {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 model;
    /* 0x04 */ Vec unk04;
} EffectGroupModel; // Size 0x10

typedef struct EffectGroup {
    /* 0x00 */ s16 count;
    /* 0x04 */ EffectGroupModel *models;
} EffectGroup; // Size 0x08

s16 EffectModelCreate(s32 fileId, s32 attr);
s16 EffectModelRead(s32 fileId, s32 attr);
void EffectParamSet(s16 model, f32 arg1, f32 arg2, f32 arg3);
s32 EffectEmit(s16 model, f32 x, f32 y, f32 z);
s16 EffectCreate(s32 fileId, s32 attr);
void EffectPosSet(s16 model, f32 x, f32 y, f32 z);
void EffectTimeSet(s16 model, s16 time);
void EffectRangeSet(s16 model, f32 range);
void EffectStop(s16 model);
void EffectObjExec(omObjData *obj);
void EffectParticleHook(s16 model);
void EffectGroupInit(void);
s16 EffectGroupCreate(s32 fileId, s32 attr, s16 count, void (*func)(s16));
s16 EffectGroupEmit(s16 index, f32 x, f32 y, f32 z);
s16 EffectGroupStarCreate(s32 attr, s16 count);
void EffectGroupStarHook(s16 model);

#endif
