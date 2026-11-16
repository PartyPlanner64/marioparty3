#include "inst.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here.
 * Interior halfword and callback symbols are aliased in undefined_syms.txt.
 */
s32 inst_mainTimer BSS;
u8 inst_mainTimerPad[12] BSS;
void *inst_picData BSS;
void *inst_picAlpha BSS;
void *inst_picHeader BSS;
u8 inst_picPad[4] BSS;
s32 inst_hostAnimTbl[2] BSS;
s16 inst_hostAnimLink BSS;
s32 inst_hostAnimPad BSS;
s32 inst_itemHostAnim BSS;
u8 inst_itemHostAnimPad[12] BSS;
s32 inst_battleHostAnim BSS;
u8 inst_battleHostAnimPad[12] BSS;
HuMtx4F inst_playerMtx BSS;
omObjData *inst_playerObj BSS;
void (*inst_playerFunc)(omObjData *) BSS;
s16 inst_chrMdlTbl[4] BSS;
omObjData *inst_winObj BSS;
void (*inst_winFunc)(s32) BSS;
UnkInstWin inst_win BSS;
s32 inst_winPad[2] BSS;
u16 inst_titleSprTbl[2] BSS;
u16 inst_coinPotDigitSprTbl[3] BSS;
s16 inst_coinPotDigitPad BSS;
s32 inst_winMes BSS;
const MinigameTable *inst_mgData BSS;
s8 inst_winPage BSS;
GAMEMES inst_titleMes BSS;
u8 inst_titleMesPad[4] BSS;
GAMEMES inst_practiceMes BSS;
u8 inst_practiceMesPad[12] BSS;
omObjData *inst_battleHostObj BSS;
void (*inst_battleHostFunc)(omObjData *) BSS;
InstObjectState inst_boxWork BSS;
InstObjectState inst_hostWork BSS;
InstObjectState inst_itemHostWork BSS;
