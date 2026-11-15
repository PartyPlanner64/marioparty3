#ifndef _GAME_HMFANIM_H
#define _GAME_HMFANIM_H

#include "ultra64.h"
#include "game/hu3d.h"

void Hu3DTexInit(void);
void Hu3DTexLoad(HmfData *hmf);
void Hu3DTexRelease(HmfData *hmf);
HmfData_Unk84_Entry2 *Hu3DTexSearchIdx(HmfData *hmf, s16 index);
HmfData_Unk84_Entry2 *Hu3DTexSearchName(HmfData *hmf, char *name);
HmfData_Unk84_Entry2 *Hu3DTexSearch(HmfData *hmf, char *name);
void Hu3DTexDataSet(u8 *data, HmfData *hmf, HmfData_Unk84_Entry2 *tex);
void Hu3DPalLoad(HmfData *hmf);
HmfPaletteData *Hu3DPalSearch(HmfData *hmf, s16 index);
void Hu3DPalOwnerKill(void *unk);
void Hu3DPalKill(HmfPaletteData *pal);
void Hu3DPalDataSet(u8 *data, HmfData *hmf, HmfPaletteData *pal);
void Hu3DTexRefClear(HmfData_Unk84_Entry2 *tex);
void Hu3DAnimWorkInit(void);
s32 Hu3DAnimCreate(HmfData *hmf, void *data, s16 bank, const char *name);
s16 Hu3DAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, const char *name);
void Hu3DAnimInit(void);
s32 Hu3DAnimDataCreate(u8 *data);
void Hu3DAnimAttrSet(s16 animIdx, u8 bitmask, u8 flags);
void Hu3DAnimBankSet(s16 animIdx, u8 rot);
void Hu3DAnmNoSet(s16 animIdx, u8 frame);
u8 Hu3DAnimFrameGet(s16 animIdx);
void Hu3DAnimExec(u16 vcount);
void Hu3DAnimSpeedSet(s16 animIdx, f32 speed);
void Hu3DAnimKill(s16 animIdx);
void Hu3DAnimDataKill(s16 animIdx);
void Hu3DAnimModelKill(s16 animIdx);
void Hu3DAnimAllKill(void);
void Hu3DTexAllKill(void);
void Hu3DTexSizeGet(char *name, u16 *out);
void Hu3DAnimSegmentSet(HmfData *hmf);
void Hu3DModelAnimStop(HmfData *arg0);
void Hu3DModelAnimStart(HmfData *arg0);
s32 Hu3DModelAnimLoad(HmfData *hmf);
s16 Hu3DAnimSetCreate(HmfData *hmf, u8 *data);
s16 Hu3DAnimSlotGet(void);
s16 Hu3DAnimDataSlotGet(void);
void Hu3DAnimTimeSet(s16 animIdx, s16 count);

#endif
