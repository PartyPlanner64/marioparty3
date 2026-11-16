#ifndef _PARTY_COMMON_HELPWIN_H
#define _PARTY_COMMON_HELPWIN_H

#include "common_board.h"
#include "game/board.h"

void MBHelpWinOpen(Unk3 *arg0);
Unk3 *MBHelpWinCreate(s16 arg0, s16 arg1, u8 arg2);
void MBHelpWinKill(Unk3 *arg0);

#endif //_PARTY_COMMON_HELPWIN_H