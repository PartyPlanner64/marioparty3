#define NO_EXTERN_VARIABLES
#include "common.h"
#include "game/overlays/opening.h"

Process *op_mainProc BSS;
s32 op_demoEndF BSS;
u8 op_demoEndPad[8] BSS; /* Unreferenced. */
OpSpr op_sprTbl[0x40] BSS;
OpAnimSlot op_animTbl[0x40] BSS;
OpModel op_modelTbl[0xA0] BSS;
s16 op_bgAnim BSS;
u16 op_bgSpr BSS;
u8 op_bgSprPad[4] BSS; /* Unreferenced. */
OpSlot op_winTbl[0x20] BSS;
OpShake op_cameraShake BSS;
u8 op_cameraShakePad[4] BSS; /* Unreferenced. */
OpCamVecs op_cameraWork BSS;
Vec op_effPos BSS;
s32 op_effNum BSS;
OpObj op_demoObjTbl[0x10] BSS;
u8 op_demoObjPad[8] BSS; /* Unreferenced. */
OpContError op_contError BSS;
