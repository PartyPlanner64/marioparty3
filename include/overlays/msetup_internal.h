#ifndef MSETUP_INTERNAL_H
#define MSETUP_INTERNAL_H

#include "overlays/msetup.h"
#include "game/object.h"

typedef MsetupLinkedModel Array2D[2];

typedef struct MsetupModelTarget {
    Vec pos;
    f32 rotation;
} MsetupModelTarget;

typedef struct MsetupCursorState {
    s16 pos[2];
    s16 (*positions)[2];
    s32 dataId;
    s16 selection;
    s16 state;
    s16 flags;
    s16 priority;
} MsetupCursorState;

typedef struct MsetupSpriteState {
    s16 state;
    s16 unk02;
    s16 spriteSlots[8];
    s16 values[8];
} MsetupSpriteState;

void func_8010B82C_msetup(s32 message);
s32 func_8010B858_msetup(void);
void func_8010B968_msetup(u32 arg0, s8 arg1);
void func_8010B998_msetup(void);
s16 func_8010D4DC_msetup(s16 positions[][2], u8 *disabled, s16 count, s16 selection, s16 controller, s16 buttons);
void func_8010D6D0_msetup(void);
void func_8010DDD8_msetup(omObjData *object);
omObjData *func_8010DE38_msetup(s32 leftX, s32 rightX, s32 y);
s16 func_8010E00C_msetup(omObjData *arg0, s16 arg1);
void func_8010E044_msetup(omObjData *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5);
omObjData *func_8010E21C_msetup(void);
void func_8010E4BC_msetup(Array2D *arg0, s32 arg1, f32 arg2);
void func_8010E4D8_msetup(MsetupLinkedModel *entry, s32 count);
void func_8010E52C_msetup(MsetupLinkedModel *models, MsetupModelTarget *targets, s16 count, s16 frames,
                          s16 *scaleModels, s16 scaleCount, f32 startScale, f32 endScale);
void func_8010E8C8_msetup(Array2D *models, s16 count, s16 frames, f32 rotation, f32 height, f32 scale, f32 endScale,
                          s16 animateBoard);
void func_8010F320_msetup(Process *process, s16 index, s16 spriteSlot, s16 value);

/* Menu and setup dispatch tables. */
s16 func_801077E0_msetup(s16 stateIndex);
s16 func_80107840_msetup(s16 stateIndex);
s16 func_80107964_msetup(s16 stateIndex);
s16 func_80107A58_msetup(s16 stateIndex);
s16 func_80107B8C_msetup(s16 stateIndex);
s16 func_80107CF4_msetup(s16 stateIndex);
s16 func_80107D84_msetup(s16 stateIndex);
s16 func_80107E48_msetup(s16 stateIndex);
s16 func_80107ECC_msetup(s16 stateIndex);
void func_80107FB4_msetup(void);
s16 func_80108464_msetup(s16 stateIndex);
s16 func_801084C4_msetup(s16 stateIndex);
s16 func_801085D4_msetup(s16 stateIndex);
s16 func_801086C8_msetup(s16 stateIndex);
s16 func_801087F4_msetup(s16 stateIndex);
s16 func_801088A8_msetup(s16 stateIndex);
s16 func_80108938_msetup(s16 stateIndex);
s16 func_801089FC_msetup(s16 stateIndex);
void func_80108AB8_msetup(void);
void func_80109218_msetup(void);
void func_80109868_msetup(void);
s16 func_80109EA0_msetup(s16 stateIndex);
s16 func_80109F04_msetup(s16 stateIndex);
s16 func_80109F7C_msetup(s16 step);
s16 func_8010A10C_msetup(s16 step);
s16 func_8010A204_msetup(s16 step);
s16 func_8010A2B0_msetup(s16 step);
void func_8010A780_msetup(void);
void func_8010A7A0_msetup(void);
void func_8010AC78_msetup(void);
void func_8010AC94_msetup(void);
s16 func_8010F87C_msetup(MsetupMenuState *state);
s16 func_80111650_msetup(MsetupMenuState *state);
s16 func_801132C4_msetup(MsetupMenuState *state);
s16 func_80113DEC_msetup(MsetupMenuState *state);
s16 func_80113E20_msetup(MsetupMenuState *state);
s16 func_80113E54_msetup(MsetupMenuState *state);
s16 func_80113E88_msetup(MsetupMenuState *state);
s16 func_80113ED4_msetup(MsetupMenuState *arg0);
s16 func_801145D0_msetup(MsetupMenuState *state);
s16 func_80114AA0_msetup(MsetupMenuState *state);
s16 func_80115EE0_msetup(MsetupMenuState *state);
s16 func_801167B8_msetup(MsetupMenuState *state);
s16 func_80116FE0_msetup(MsetupMenuState *state);
s16 func_80117818_msetup(MsetupMenuState *state);
void func_80118D48_msetup(void);

#endif
