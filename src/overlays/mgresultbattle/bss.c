#define NO_EXTERN_VARIABLES
#include "common.h"
#include "mgresultbattle.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
ResultBattleEffect D_80108A30_mgresultbattle[40] BSS;
u16 D_80108F30_mgresultbattle[4] BSS;
u16 D_80108F38_mgresultbattle[4][3] BSS;
ResultBattlePlayerObj D_80108F50_mgresultbattle[4] BSS;
s32 D_80108F70_mgresultbattle BSS;
omObjData *D_80108F74_mgresultbattle BSS;
omObjFunc D_80108F78_mgresultbattle BSS;
omObjData *D_80108F7C_mgresultbattle BSS;
omObjFunc D_80108F80_mgresultbattle BSS;
omObjData *D_80108F84_mgresultbattle BSS;
omObjFunc D_80108F88_mgresultbattle BSS;
s8 D_80108F8C_mgresultbattle[4] BSS;
ResultBattlePlayerObj D_80108F90_mgresultbattle BSS;
