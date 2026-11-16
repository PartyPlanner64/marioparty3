#define NO_EXTERN_VARIABLES
#include "common.h"
#include "mgresultdealer.h"

// Misaligned s8 array after an s16 (see undefined_syms.txt for aliases).
typedef struct MgResultDealerMainBss {
    /* 0x00 */ s16 unk00; // mgresultdealer_bet
    /* 0x02 */ s8 unk02[4]; // mgresultdealer_playerOrderTbl
} MgResultDealerMainBss; // sizeof 0x06

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
u8 mgresultdealer_bssPad[0x18] BSS; /* Unreferenced. */
s16 mgresultdealer_confettiMdlTbl[4] BSS;
u8 mgresultdealer_confettiMdlPad[0x60] BSS; /* Unreferenced. */
f32 mgresultdealer_dropVel BSS;
s16 mgresultdealer_playerFaceAnimTbl[4] BSS;
u8 mgresultdealer_playerFaceAnimPad[4] BSS; /* Unreferenced. */
u16 mgresultdealer_coinSprMdl BSS;
u16 mgresultdealer_coinEffSprMdl BSS;
u8 mgresultdealer_coinEffSprMdlPad[4] BSS; /* Unreferenced. */
UnkDealerCoin mgresultdealer_coinTbl[40] BSS;
UnkDealerCoin mgresultdealer_coinEffTbl[40] BSS;
u8 mgresultdealer_coinEffPad[8] BSS; /* Unreferenced. */
s16 mgresultdealer_fadeHookMdl BSS;
s32 mgresultdealer_fadeSprData BSS;
HuSprite *mgresultdealer_fadeSpr BSS;
u8 *mgresultdealer_fadeTex BSS;
UnkDealerSprites mgresultdealer_calcSpr BSS;
s32 mgresultdealer_calcOpenF BSS;
s32 mgresultdealer_calcCloseF BSS;
u8 mgresultdealer_calcClosePad[8] BSS; /* Unreferenced. */
ResultDealerObj mgresultdealer_playerWork BSS;
s16 mgresultdealer_payoutRate BSS;
omObjData *mgresultdealer_calcObj BSS;
omObjFunc mgresultdealer_calcFunc BSS;
MgResultDealerMainBss mgresultdealer_mainBss BSS;
UnkDealerFadeProc mgresultdealer_fadeWork BSS;
omObjData *mgresultdealer_coinObj BSS;
omObjFunc mgresultdealer_coinFunc BSS;
