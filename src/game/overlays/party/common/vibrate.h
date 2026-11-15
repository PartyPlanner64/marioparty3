#ifndef _PARTY_COMMON_VIBRATE_H
#define _PARTY_COMMON_VIBRATE_H

#include "common_board.h"
#include "game/board.h"

void MBPlayerVibrate(s16 playerIndex, s16 vibrationStrength);
UnkVibrateProcess* MBPlayerVibrateObjCreate(s16 playerNo, s16 vibrateStrength, s32 sleepTime);
void MBPlayerVibrateObjKill(UnkVibrateProcess* arg0);

#endif //_PARTY_COMMON_VIBRATE_H