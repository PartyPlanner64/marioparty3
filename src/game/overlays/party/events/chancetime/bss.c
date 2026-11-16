#define NO_EXTERN_VARIABLES
#include "common.h"
#include "chancetime.h"

// Misaligned s16 array after an s8 (see undefined_syms.txt for aliases).
typedef struct ChanceTimeHitWork {
    /* 0x00 */ s8 unk00;     // chancetime_hitBlockNo
    /* 0x02 */ s16 unk02[3]; // chancetime_playerAnimTbl
} ChanceTimeHitWork;         // sizeof 0x08

// Misaligned s8 array after an s8 (see undefined_syms.txt for aliases).
typedef struct ChanceTimeResultWork {
    /* 0x00 */ s8 unk00;    // chancetime_turnTier
    /* 0x01 */ s8 unk01[3]; // chancetime_blockResultTbl, [2] = chancetime_actionNo
} ChanceTimeResultWork;        // sizeof 0x04

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s32 chancetime_flowTimer BSS;
s8 chancetime_blockOrderTbl[3] BSS;
u8 chancetime_blockOrderPad[8] BSS; /* Unreferenced. */
s32 chancetime_playerEnterF BSS;
s32 chancetime_playerEnterDoneF BSS;
ChanceTimeHitWork chancetime_hitWork BSS;
s16 chancetime_hostEffSprMdlTbl[2] BSS;
s32 chancetime_hostAnimTbl[2] BSS;
s32 chancetime_hostFaceAnim BSS;
s16 chancetime_panelHookMdl BSS;
s16 chancetime_panelSprAnim BSS;
s16 chancetime_blockHatenaSprTbl[3] BSS;
u16 chancetime_panelFrameSpr BSS;
HuSprite *chancetime_panelSpr BSS;
void *chancetime_panelTex BSS;
void *chancetime_panelPal BSS;
s16 chancetime_panelSize[2] BSS;
u8 chancetime_panelSizePad[4] BSS; /* Unreferenced. */
s16 chancetime_reelAnimTbl[3][3] BSS;
s32 chancetime_unusedCnt BSS;
s8 chancetime_unusedOnF BSS;
s8 chancetime_unusedOffF BSS;
u8 chancetime_unusedOffPad[4] BSS; /* Unreferenced. */
ChanceTimeReel chancetime_reelTbl[3] BSS;
s32 chancetime_reelSeTbl[3] BSS;
u8 chancetime_reelSePad[12] BSS; /* Unreferenced. */
ChanceTimeTransfer chancetime_transferTbl[20] BSS;
s8 chancetime_reelStartNo BSS;
s32 chancetime_eventWin BSS;
s32 chancetime_blockSpinNo BSS;
u8 chancetime_blockSpinPad[4] BSS; /* Unreferenced. */
s16 chancetime_starEffTbl[10] BSS;
u8 chancetime_starEffPad[4] BSS; /* Unreferenced. */
s16 chancetime_coinSprTbl[20] BSS;
u8 chancetime_coinSprPad[0x30] BSS; /* Unreferenced. */
omObjData *chancetime_eventObj BSS;
void (*chancetime_eventFunc)() BSS;
ChanceTimeObjState chancetime_dancerWorkTbl[5] BSS;
ChanceTimeObjState chancetime_hostLWork BSS;
ChanceTimeObjState chancetime_hostRWork BSS;
ChanceTimeObjState chancetime_playerWork BSS;
omObjData *chancetime_blockObj BSS;
void (*chancetime_blockFunc)(omObjData *) BSS;
s8 chancetime_playerOrderTbl[4] BSS;
ChanceTimeObjState chancetime_hostWork BSS;
ChanceTimeResultWork chancetime_resultWork BSS;
