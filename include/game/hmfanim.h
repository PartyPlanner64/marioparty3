#ifndef _GAME_HMFANIM_H
#define _GAME_HMFANIM_H

#include "ultra64.h"
#include "game/hu3d.h"

void func_80031560_main(void);
void func_80031630_main(HmfData *hmf);
void func_8003186C_main(HmfData *hmf);
HmfData_Unk84_Entry2 *func_80031A08_main(HmfData *hmf, s16 index);
HmfData_Unk84_Entry2 *func_80031A44_main(HmfData *hmf, char *name);
HmfData_Unk84_Entry2 *func_80031A60_main(HmfData *hmf, char *name);
void func_80031B30_main(u8 *data, HmfData *hmf, HmfData_Unk84_Entry2 *tex);
void func_80031DF4_main(HmfData *hmf);
HmfPaletteData *func_80032038_main(HmfData *hmf, s16 index);
void func_80032104_main(void *unk);
void func_80032194_main(HmfPaletteData *pal);
void func_800321B8_main(u8 *data, HmfData *hmf, HmfPaletteData *pal);
void func_800322AC_main(HmfData_Unk84_Entry2 *tex);
void func_8003235C_main(void);
s32 HmfAnimCreate(HmfData *hmf, void *data, s16 bank, char *name);
s16 HmfAnimLink(HmfData *hmf, u16 linkIdx, s16 bank, char *name);
void func_80032950_main(void);
s32 func_800329B4_main(u8 *data);
void func_80032FC0_main(s16 animIdx, u8 bitmask, u8 flags);
void func_80032FF8_main(s16 animIdx, u8 rot);
void func_8003302C_main(s16 animIdx, u8 frame);
u8 func_800330D4_main(s16 animIdx);
void HmfAnimExec(u16 vcount);
void func_800332D4_main(s16 animIdx, f32 speed);
void func_80033354_main(s16 animIdx);
void func_800333B0_main(s16 animIdx);
void func_80033430_main(s16 animIdx);
void func_80033450_main(void);
void func_80033510_main(void);
void func_800335BC_main(char *name, u16 *out);
void func_80033694_main(HmfData *hmf);
void func_80033910_main(HmfData *arg0);
void func_80033970_main(HmfData *arg0);
s32 func_800339D0_main(HmfData *hmf);
s16 func_80033D0C_main(HmfData *hmf, u8 *data);
s16 func_80033F8C_main(void);
s16 func_80033FEC_main(void);
void func_80034048_main(s16 animIdx, s16 count);

#endif
