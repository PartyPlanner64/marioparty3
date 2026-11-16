#ifndef _PARTY_COMMON_ITEM_H
#define _PARTY_COMMON_ITEM_H

#include "common_board.h"
#include "game/board.h"

extern u8 mbItemPriceTbl[];
extern s32 mbItemComWeightTbl[];
extern s32 mbItemComShopWeightTbl[];
extern s32 mbItemCharSprTbl[];

void MBCharNameMesConv(s32 arg0, char *arg1);
void MBItemWarpBlockSwapInit(void);
s32 MBItemWarpBlockSwapPlayerSet(s16 arg0);
void MBItemWarpBlockSwapCreate(void);
void MBItemHookSet(s32 idx, void (*func)());
void MBItemSelExec(s32 playerNo, s32 arg1);
void MBItemViewExec(s32 playerNo);
void MBItemDescExec(s32 arg0);
void MBItemKSuitWalkExec(void);
void MBItemKSuitEnd(void);
void MBItemMajinLampStarExec(void);
s32 MBItemFind(s32 playerNo, s32 item);
s32 MBItemFindEmpty(s32 arg0);
void MBItemRemoveEmpty(s32 arg0);
s32 MBItemSelNoGet(void);
void MBItemSelNoSet(s32 arg0);
void MBItemSelNoClear(void);
void MBTelopInit(void);
void MBTelopClose(void);
void MBTelopMgTypeCreate(s32 arg0, u32 arg1);
s32 MBTelopMgTypeStatGet(void);
void MBTelopMgTypeKill(void);
Process* MBTelopCreate(s32 playerNo);
UnkMBGuideData* MBGuideCreate(u32* arg0, s32 arg1);
void MBGuideKill(UnkMBGuideData* arg0);
void MBGuidePosSet(UnkMBGuideData* arg0, s16 arg1, s16 arg2);
void MBItemKoopaNKinokoExec(void);
void MBItemKoopaRKinokoExec(void);

#endif //_PARTY_COMMON_ITEM_H
