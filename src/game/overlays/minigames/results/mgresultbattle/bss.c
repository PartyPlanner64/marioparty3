#define NO_EXTERN_VARIABLES
#include "common.h"
#include "mgresultbattle.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
ResultBattleEffect mgresultbattle_coinTbl[40] BSS;
u16 mgresultbattle_coinNumIconSprTbl[4] BSS;
u16 mgresultbattle_coinNumDigitSprTbl[4][3] BSS;
ResultBattlePlayerObj mgresultbattle_playerWorkTbl[4] BSS;
s32 mgresultbattle_coinRest BSS;
omObjData *mgresultbattle_coinObj BSS;
omObjFunc mgresultbattle_coinFunc BSS;
omObjData *mgresultbattle_podiumObj BSS;
omObjFunc mgresultbattle_podiumFunc BSS;
omObjData *mgresultbattle_coinNumObj BSS;
omObjFunc mgresultbattle_coinNumFunc BSS;
s8 mgresultbattle_playerOrderTbl[4] BSS;
ResultBattlePlayerObj mgresultbattle_hostWork BSS;
