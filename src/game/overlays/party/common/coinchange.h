#ifndef _PARTY_COMMON_COINCHANGE_H
#define _PARTY_COMMON_COINCHANGE_H

#include "common_board.h"
#include "game/board.h"

void MBCoinChangeInit(void);
void MBCoinChangeClose(void);
void MBCoinChangeStatusCreate(s32 arg0, s32 arg1);
void MBCoinChangeCreate(s32 player, s32 coins);

#endif //_PARTY_COMMON_COINCHANGE_H