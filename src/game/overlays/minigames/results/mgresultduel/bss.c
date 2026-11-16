#include "common.h"
#include "mgresultduel.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
u16 mgresultduel_coinSprMdl BSS;
u16 mgresultduel_coinEffSprMdl BSS;
u8 mgresultduel_coinSprMdlPad[4] BSS; /* Unreferenced. */
UnkResultDuelStruct mgresultduel_coinTbl[20] BSS;
UnkResultDuelStruct mgresultduel_coinEffTbl[20] BSS;
s8 mgresultduel_coinDir BSS;
u8 mgresultduel_coinDirPad[4] BSS; /* Unreferenced. */
s32 mgresultduel_hostAnimTbl[3] BSS;
s16 mgresultduel_hostAnimLink BSS;
s8 mgresultduel_playerOrderTbl[2] BSS;
s32 mgresultduel_prizeCoin BSS;
s8 mgresultduel_winSide BSS;
omObjData *mgresultduel_coinObj BSS;
omObjFunc mgresultduel_coinFunc BSS;
ResultDuelObj mgresultduel_hostWork BSS;
ResultDuelObj mgresultduel_player2PWork BSS;
u8 mgresultduel_player2PWorkPad[4] BSS; /* Unreferenced. */
ResultDuelObj mgresultduel_gateGuyWork BSS;
ResultDuelObj mgresultduel_player1PWork BSS;
