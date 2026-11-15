#ifndef _GAME_HMFSHAPE_H
#define _GAME_HMFSHAPE_H

#include "ultra64.h"
#include "game/hu3d.h"

typedef struct {
    HmfData *model;
    u8 *data;
    u8 *frames;
    s16 duration;
    s16 frameCount;
    s16 frameStep;
} HmfVertexAnim;

void Hu3DShapeInit(void);
s32 Hu3DShapeCreate(HmfData *model, u8 *data);
void Hu3DShapeKill(s32 arg0);
void Hu3DShapeAllKill(void);
void Hu3DShapeCacheMake(HmfData *model);
void Hu3DShapeExec(HmfModel *model, f32 time);
void Hu3DShapeAnimExec(HmfData *model, s16 animIndex, f32 time);
void Hu3DShapeMorphExec(HmfData *model, f32 time);

#endif
