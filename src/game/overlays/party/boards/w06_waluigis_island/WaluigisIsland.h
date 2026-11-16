#ifndef _WALUIGIS_ISLAND_H
#define _WALUIGIS_ISLAND_H

#include "ultra64.h"
#include "game/board.h"

typedef struct MasuIdTable {
    /* 0x00 */ s32 entries[3];
} MasuIdTable; // size 0xC

typedef struct ModelIdTable {
    /* 0x00 */ s32 entries[3];
} ModelIdTable; // size 0xC

typedef struct MessageTable {
    /* 0x00 */ s32 entries[4];
} MessageTable; // size 0x10

/* Overlay functions */
void MB6Ev_Branch1(void);
void MB6Ev_Branch2(void);
void MB6Ev_Branch3(void);
void MB6Ev_Branch4(void);
void MB6Ev_Branch5(void);
void MB6Ev_Branch6(void);
void MB6Ev_Branch7(void);
void MB6Ev_Branch8(void);
void MB6Ev_Branch9(void);
void MB6Ev_Branch10(void);
void MB6Ev_Branch11(void);
void MB6Ev_Branch12(void);
void MB6Ev_Branch13(void);
void MB6Ev_Branch14RKinoko(void);
void MB6Ev_Branch15RKinoko(void);
void MB6Ev_Branch16RKinoko(void);
void MB6Ev_Branch17RKinoko(void);
void MB6Ev_Branch18RKinoko(void);
void MB6Ev_Branch19RKinoko(void);
void MB6Ev_Merge1(void);
void MB6Ev_Merge2(void);
void MB6Ev_Merge3(void);
void MB6Ev_Merge4(void);
void MB6Ev_Merge5(void);
void MB6Ev_Merge6(void);
void MB6Ev_Merge7(void);
void MB6Ev_Merge8(void);
void MB6Ev_Merge9(void);
void MB6Ev_Merge10(void);
void MB6Ev_Merge11(void);
void MB6Ev_Merge12(void);
void MB6Ev_Merge13(void);
void MB6Ev_Merge14(void);
void MB6Ev_Merge15(void);
void MB6Ev_Merge16(void);
void MB6Ev_Merge17(void);
void MB6Ev_Merge18(void);
void MB6Ev_Trapdoor(void);
void MB6Ev_Branch1Rev(void);
void MB6Ev_KeyManMasu(void);
void MB6Ev_StarMasu(void);
void MB6Ev_BankMasu(void);
void MB6Ev_ShopMasu(void);
void MB6Ev_Gate1Close(void);
void MB6Ev_Gate2Close(void);
void MB6Ev_NKinokoTurnStart(void);
void MB6Ev_RKinokoTurnStart(void);
void MB6Ev_ChangeMasuTypeRoll(void);
void MB6Ev_HoleEnter(void);
s32 MB6_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2);
void MB6_ObjectSetup(void);
void MB6_BombAnimKill(void);
void MB6Ev_BranchMain(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);
s32 MB6_ComShopItemDecide(void);
s32 MB6_ComShopEnterDecide(void);
void MB6Ev_StarMapView(void);
void MB6_StarGuideCreate(s16 arg0);
void MB6Ev_Hatena(void);
void MB6Ev_RouletteExec(void);
void MB6Ev_BombCountExec(void);
void MB6Ev_BridgeSwapExec(s32 arg0);
void MB6_GateCloseProc(void);
void MB6Ev_ActionTimeTitleProc(void);
void MB6Ev_TeresaCoin(void);
void MB6Ev_KoopaCardCoinProc(void);
void MB6Ev_BombExplodeMdlEndProc(void);
void MB6Ev_StarGet(void);
void MB6_GateCreate(s16 arg0);
void MB6Ev_KinokoMarkObjMain(omObjData *arg0);
void MB6_TeresaGuideCreate(s16 arg0);
void MB6_BankCoinCreate(s16 arg0);
void MB6_BankCoinHide(void);
void MB6Ev_TereYokeSprayProc(void);
void MB6Ev_Teresa(void);
void MB6Ev_ItemMajinLamp(void);
void MB6Ev_ItemUseFadeOut(void);
void MB6Ev_ItemMajinLampStar(void);
void MB6Ev_ItemWarpBlock(void);
void MB6Ev_ItemRobBox(void);
void MB6Ev_KSuitStart(void);
void MB6Ev_KSuitEnd(void);
void MB6Ev_ItemKinoko(void);
void MB6Ev_ItemShake(void);
void MB6Ev_ItemPhoneMove(void);
void MB6Ev_ItemNKinoko(void);
void MB6Ev_ItemRKinoko(void);
void MB6Ev_ItemShopPhone(void);
void MB6Ev_ItemKoopaPhone(void);
void MB6Ev_ItemStarYoke(void);
void MB6Ev_ItemKeyManUse(void);
void MB6Ev_ItemNullUse(void);
void MB6Ev_ItemExchangeBox(void);
s32 MB6_ComItemTargetChoice(u8 *arg0, s32 arg1);
void MB6Ev_ItemGambleCoin(void);
void MB6Ev_ItemAfter5(void);
void MB6Ev_ItemKoopaNKinoko(void);
void MB6Ev_ItemKoopaRKinoko(void);
s32 MB6_ComItemDecide(void);
void MB6_StarGuideCreateAll(void);
void MB6_TeresaGuideCreateAll(void);
void MB6_BankCoinCreateAll(void);
void MB6_GateCreateAll(void);
void MB6_BankMapIconAddAll(void);
void MB6_ShopMapIconAddAll(void);
void MB6_HoleExitCreate(void);
void MB6_HoleCreateAll(void);
void MB6_BombCreate(void);
void MB6_BridgeCreateAll(void);
void MB6Ev_ChangeMasuTypeSet(void);
void MB6Ev_KinokoMarkCreateAll(void);
void MB6Ev_GambleCoinProc(void);
void MB6Ev_BankKoopaCardExec(void);
void MB6Ev_ItemLampSmokeObjMain(omObjData *arg0);

#endif /* _WALUIGIS_ISLAND_H */
