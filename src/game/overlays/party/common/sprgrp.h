#ifndef _PARTY_COMMON_SPRGRP_H
#define _PARTY_COMMON_SPRGRP_H

#include "common_board.h"
#include "game/board.h"

void MBSprGrpInit(void);
void MBSprGrpClose(void);
UnkBoard8 *MBSprGrpCreate(s16 arg0, s16 arg1);
void MBSprGrpKill(UnkBoard8* arg0);
void MBSprGrpPosSet(UnkBoard8* arg0, s16 member, s16 x, s16 y); //unused
void MBSprGrpScaleSet(UnkBoard8 *arg0, s16 member, f32 arg2, f32 arg3);

#endif //_PARTY_COMMON_SPRGRP_H