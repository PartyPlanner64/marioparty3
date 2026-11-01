#ifndef _GAME_HMFDRAW_H
#define _GAME_HMFDRAW_H

#include "ultra64.h"
#include "game/mallocblock.h"
#include "game/hu3d.h"
#include "types.h"

void func_800222B0_main(HuAllocFunc alloc, HuFreeFunc free, u16 vertexCount, u16 matrixCount, u16 gfxCount, u8 bufferCount);
void func_800224BC_main(void);
void func_800225D4_main(void);
void func_80022660_main(HmfData *arg0);
void func_80022F08_main(HmfData *arg0);
void func_80022FF4_main(HmfData *arg0);
void func_800230F8_main(HmfData *arg0);
s32 func_80023264_main(HmfData *arg0);
void func_80023404_main(HmfData *arg0, HuMtx4F arg1, HuMtx4F arg2);
void func_8002367C_main(HuMtx4F dst, HuMtx4F src);
void func_80023700_main(HmfData *arg0, s16 arg1);
void func_80023AF8_main(HmfData *arg0, s16 arg1);
void func_8002404C_main(HmfData *arg0, s16 arg1);
void func_80024354_main(HmfData *arg0, s16 arg1);
void func_80024814_main(HmfData *arg0, s16 arg1, HmfDrawObject *arg2);
void func_80024D94_main(HmfData *arg0, s16 arg1, Mtx *arg2);
void func_80024DF0_main(HmfData *arg0, s16 arg1, Mtx *arg2, HuMtx4F arg3);
Gfx *func_800250D4_main(s16 arg0, Gfx *arg1, Gfx *arg2);
void func_800257BC_main(HmfData *hmf, s16 objectIndex);
void func_800260F0_main(HmfData *hmf, s32 *flags);
void func_80029FB4_main(HmfData *hmf, s16 objectIndex);
void func_8002A358_main(HmfMaterialData *material, HmfData_Unk84_Entry *texture, u32 flags);
void func_8002AC5C_main(u16 flags);
void func_8002AF40_main(void);
void func_8002AFEC_main(HmfData *hmf, s32 flags, s16 objectIndex);
void func_8002B104_main(HmfData *hmf, s16 objectIndex);
void func_8002B2AC_main(HmfData_Unk84_Entry2 *texture, s16 wrapS, s16 wrapT);
void func_8002C0EC_main(HmfData *hmf, s16 objectIndex);
s32 func_8002C4C0_main(HmfData *arg0, s16 arg1, HuMtx4F arg2, HuMtx4F arg3);
void func_8002C520_main(HmfData *hmf, s16 nodeIndex, HuMtx4F mtx);
s32 func_8002C5B8_main(HmfData *hmf, s16 nodeIndex, s16 targetIndex);
s16 func_8002C834_main(HmfData *arg0, char *name);
void func_8002C914_main(HmfData *hmf, char *name, HmfData *replacement);
void func_8002C960_main(HmfData *hmf, s16 objectIndex, HmfData *replacement);
void func_8002CAE4_main(HmfData *hmf);
void func_8002CB6C_main(HmfData *hmf, s16 nodeIndex);
void func_8002CDF4_main(HmfData *hmf, s16 nodeIndex);
void func_8002D094_main(Gfx **arg0, s16 arg1, s32 color);
void func_8002D260_main(void);
s16 func_8002D2D8_main(HmfMotionFile *file, HmfData *hmf);
s32 func_8002D3AC_main(HmfMotionFile *file);
s32 func_8002D3D0_main(HmfData *hmf, HmfMotionFile *file, s32 arg2);
void func_8002D4B8_main(s32 arg0);
void func_8002D514_main(void);
s32 func_8002D5B0_main(HmfModelData_Unk64_Unk8C_Struct *motion, HmfData *hmf);
s32 func_8002DA98_main(HmfModelData_Unk64_Unk8C_Struct *motion, s16 channelIndex, u8 *data);
s32 func_8002DD4C_main(HmfData *hmf, s16 trackIndex, u8 *data);
s32 func_8002DF2C_main(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionFile *file);
void func_8002DFF8_main(HmfData *hmf, f32 frame, HmfModelData_Unk64_Unk8C_Struct *motion, s32 reset);
f32 func_8002E78C_main(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame);
f32 func_8002E8E8_main(HmfModelData_Unk64_Unk8C_Struct *motion, HmfMotionChannel *channel, f32 frame);
void func_8002EAC0_main(HmfData *hmf, f32 frame, f32 weight);
s32 func_8002F60C_main(HmfData *hmf);
void func_8002FB08_main(HmfData *arg0, f32 arg1);
void func_8002FB98_main(HmfData *arg0, f32 arg1);
void func_8002FC14_main(HmfData *arg0, f32 arg1);
f32 func_8002FC7C_main(HmfModelData_Unk64_Unk8C_Struct *arg0, u16 flags, f32 frame, f32 start, f32 speed);
void func_8002FD48_main(HmfData *arg0);
void func_8002FD50_main(HmfData *arg0);
s16 func_8002FD70_main(HmfData *arg0);
void func_8002FD8C_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void func_8002FDCC_main(s16 arg0, s16 arg1, char *arg2, s16 arg3, s16 arg4);
void func_8002FE08_main(s16 modelIndex, s16 motionIndex, char *name, s16 target, s16 component, s16 flags);
void func_80030030_main(f32 arg0);

#endif
