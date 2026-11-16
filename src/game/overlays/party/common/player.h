#ifndef _PARTY_COMMON_PLAYER_H
#define _PARTY_COMMON_PLAYER_H

#include "common_board.h"
#include "game/board.h"

extern u32 *mbPlayerMotTbl[];

s16 MBPlayerTurnGet(void);
GW_PLAYER *MBPlayerGet(s32 playerNo);
s32 MBPlayerCurrentCheck(s16 playerNo);
s32 MBPlayerComCheck(s16 playerNo);
void MBPlayerCoinAdd(s32 playerNo, s32 amount);
s32 MBPlayerCoinCheck(s32 playerNo, s32 requiredCoins);
void MBPlayerSpeedSet(s32 playerNo, f32 arg1);
void MBPlayerMotionWait(s32 playerNo);
void MBPlayerMotionSet(s32 playerNo, s16 arg1, u16 arg2) ;
void MBPlayerMotionShiftSet(s32 playerNo, s16 arg1, s16 arg2, s16 arg3, u16 arg4) ;
void MBPlayerComLevelSet(s32 playerNo, u8 arg1);
void MBPlayerInit(s32 arg0);
void MBPlayerModelCreate(s16 playerNo, u32 *arg1, s32 arg2);
void MBPlayerModelCreateMot(s16 arg0, u32 *arg1); //unused
void MBPlayerModelCreateDef(s16 playerNo);
void MBPlayerModelCreateNoMot(s16 playerNo); //unused
void MBPlayerModelKill(s16 playerNo); //unused
void MBPlayerMotInit(void);
void MBPlayerClose(void);

#endif //_PARTY_COMMON_PLAYER_H
