#ifndef _GAME_HMFPARTICLE_H
#define _GAME_HMFPARTICLE_H

#include "ultra64.h"

void Hu3DParticleCreate(s16 model, s16 type, char *name, void (*func)(s16));
void Hu3DParticleAttrSet(s16 arg0, s32 arg1, s32 arg2);
s16 Hu3DParticleAttrGet(s16 arg0);
void Hu3DParticleCntSet(s16 arg0, s16 arg1);
s16 Hu3DParticleCntGet(s16 arg0);
void Hu3DParticleDraw(s16 model, s16 group);
void Hu3DParticleHookNull(s16 model);
void Hu3DParticleHook1(s16 model);
void Hu3DParticleHook2(s16 model);

#endif
