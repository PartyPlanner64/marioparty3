#ifndef _PARTY_COMMON_SCISSOR_H
#define _PARTY_COMMON_SCISSOR_H

#include "common_board.h"
#include "game/board.h"

void MBScissorFullSet(void);
void MBScissorEmptySet(void);
Process *MBScissorWipeOutStart(void);
Process *MBScissorWipeInStart(void);

#endif //_PARTY_COMMON_SCISSOR_H