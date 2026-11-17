#include "common_board.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/window.h"
#include "game/overlays/party/common/com.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"
#include "game/overlays/party/common/mapfull.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/scroll.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/vec.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/ksuit.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

typedef struct PlayerReactWork {
    /* 0x00 */ s32 playerNo;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 order;
    /* 0x0C */ s32 type;
} PlayerReactWork;

void MB5Ev_StarGet(void);
void MBModelTurnCreate(Object *arg0, Vec *arg1, s32 arg2);
void MB5Ev_ItemLampSmokeObjMain(omObjData *arg0);
void MB5Ev_ItemUseFadeOut(void);
void MB5Ev_TereYokeSprayProc(void);
void MB5Ev_BankKoopaCardExec(void);
s32 MB5_ComNKinokoTargetGet(void);
s32 MB5_ComRKinokoTargetGet(void);
void MB5_ObjectSetup(void);
void MB5Ev_Teresa(void);
void MB5Ev_ItemMajinLamp(void);
void MB5Ev_ItemMajinLampStar(void);
void MB5Ev_ItemWarpBlock(void);
void MB5Ev_ItemRobBox(void);
void MB5Ev_KSuitStart(void);
void MB5Ev_KSuitEnd(void);
void MB5Ev_ItemKinoko(void);
void MB5Ev_ItemShake(void);
void MB5Ev_ItemPhoneMove(void);
void MB5Ev_ItemNKinoko(void);
void MB5Ev_ItemRKinoko(void);
void MB5Ev_ItemShopPhone(void);
void MB5Ev_ItemKoopaPhone(void);
void MB5Ev_ItemStarYoke(void);
void MB5Ev_ItemKeyManUse(void);
void MB5Ev_ItemNullUse(void);
void MB5Ev_ItemExchangeBox(void);
void MB5Ev_ItemGambleCoin(void);
void MB5Ev_ItemAfter5(void);
void MB5Ev_ItemKoopaNKinoko(void);
void MB5Ev_ItemKoopaRKinoko(void);
s32 MB5_ComItemDecide(void);
void MB5_StarGuideCreateAll(void);
void MB5_TeresaGuideCreateAll(void);
void MB5_BankCoinCreateAll(void);
void MB5_GateCreateAll(void);
void MB5_BankMapIconAddAll(void);
void MB5_ShopMapIconAddAll(void);
void MB5Ev_KinokoMarkCreateAll(void);
void MB5_WhompProc(void);
void MB5_CartBlockProc(void);
void MB5Ev_Hatena(void);
void MB5_WhompItemShuffle(void);
s32 MB5_ComShopItemDecide(void);
s32 MB5_ComShopEnterDecide(void);
void MB5_BranchHelpStart(void);
s32 MB5Ev_YesNoChoiceGet(s32 arg0, s32 arg1);
void MB5Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees);
void MB5_GateCloseProc(void);
void MB5Ev_TeresaCoin(void);
void MB5Ev_WhompExec(void);
void MB5Ev_CartRide(void);
void MB5Ev_CartPlayerEscapeProc(void);
void MB5Ev_CartPlayerEscapeSideProc(void);
void MB5Ev_CartRideExec(void);
void MB5Ev_HatenaWhomp(void);
void MB5Ev_HatenaCartA(void);
void MB5Ev_HatenaCartB(void);
void MB5Ev_CartRunExec(s32 arg0, SpaceData *space);
s32 MB5_ComWhompItemCheck(void);
void MB5Ev_Branch1(void);
void MB5Ev_Branch1Rev(void);
void MB5Ev_Branch2(void);
void MB5Ev_Branch3(void);
void MB5Ev_Branch4(void);
void MB5Ev_Branch5(void);
void MB5Ev_Branch6(void);
void MB5Ev_Branch7(void);
void MB5Ev_Branch8(void);
void MB5Ev_Branch9(void);
void MB5Ev_Branch10RKinoko(void);
void MB5Ev_Branch11RKinoko(void);
void MB5Ev_Branch12RKinoko(void);
void MB5Ev_Branch13RKinoko(void);
void MB5Ev_Branch14RKinoko(void);
void MB5Ev_Branch15RKinoko(void);
void MB5Ev_Branch16RKinoko(void);
void MB5Ev_Merge1(void);
void MB5Ev_Merge2(void);
void MB5Ev_Merge3(void);
void MB5Ev_Branch17(void);
void MB5Ev_Merge4(void);
void MB5Ev_Merge5(void);
void MB5Ev_Merge6(void);
void MB5Ev_Merge7(void);
void MB5Ev_Merge8(void);
void MB5Ev_Merge9(void);
void MB5Ev_Merge10(void);
void MB5Ev_WhompMasu129Check(void);
void MB5Ev_CartRideMerge1(void);
void MB5Ev_Merge11(void);
void MB5Ev_Merge12(void);
void MB5Ev_CartRideMerge2(void);
void MB5Ev_Merge13(void);
void MB5Ev_Merge14(void);
void MB5Ev_Merge15(void);
void MB5Ev_Merge16(void);
void MB5Ev_Merge17(void);
void MB5Ev_Merge18(void);
void MB5Ev_Merge19(void);
void MB5Ev_WhompMasu3Check(void);
void MB5Ev_KeyManMasu(void);
void MB5Ev_StarMasu(void);
void MB5Ev_BankMasu(void);
void MB5Ev_ShopMasu(void);
void MB5Ev_Gate1Close(void);
void MB5Ev_Gate2Close(void);
void MB5Ev_NKinokoTurnStart(void);
void MB5Ev_RKinokoTurnStart(void);

extern Vec mbCameraFocusPos;

s16 mb5ev_starOrderTbl[] = { 0, 1, 2, 3, 6, 7, 4, 5 };

s16 mb5ev_starOrderGroupTbl[] = { 0, 0, 0, 0, 0, 0, 1, 1 };

s16 mb5ev_starFlag[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb5ev_starMasu[] = { 11, 31, 40, 19, 72, 92, 86, 49 };

s16 mb5ev_starGuideMasu[] = { 100, 101, 102, 103, 104, 105, 106, 107 };

s32 mb5ev_starGuideFaceTbl[] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };

s32 mb5ev_starGuideMesTbl[] = { 0x5E02, 0x5E03, 0x5E04, 0x5E05, 0x5E06, 0x5E07, 0x5E08 };

s32 mb5ev_starGetTeresaF = 0;

s32 mb5_whompMoveF = 0;

s16 mb5_masuBlockExtTbl[] = { -1, 0 };

s16 mb5_masuBlockTbl[] = {
    11, 31, 40, 19, 72, 92, 86, 49,
    -1, 0
};

s16 mb5_starGuideMapIconOfsTbl[][2] = {
    { 1, -5 },
    { 3, -5 },
    { 2, -10 },
    { -5, 0 },
    { 1, -7 },
    { 9, 24 },
    { -7, 24 },
    { -1, -6 }
};

s16 mb5_teresaGuideMapIconOfsTbl[][2] = {
    { 2, 0 },
    { 2, 0 }
};

s16 mb5_bankMapIconOfsTbl[][2] = {
    { 1, -2 },
    { 0, -4 }
};

s16 mb5_shopMapIconOfsTbl[][2] = {
    { 1, -4 },
    { 3, -2 }
};

s16 mb5_gateMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, -3 }
};

s16 mb5_gateDirMasuTbl[][2] = {
    { 115, 116 },
    { 135, 136 }
};

s16 mb5_starGuideMdlMasuTbl[] = { 100, 101, 102, 103, 104, 105, 106, 107 };

s16 mb5_starGuideFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb5_teresaGuideMasuTbl[] = { 99, 0 };

s16 mb5_bankCoinMasuTbl[] = { 120, 122 };

Vec mb5_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb5_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb5_gateMasuTbl[] = { 117, 137 };

s16 mb5_gateMdlTbl[] = { 38, 39, 40, 41, 42, 43 };

u32 mb5_gateMot1[] = { 1, 0x130163 };

u32 mb5_gateMot2[] = { 1, 0x130168 };

u32 mb5_gateMot3[] = { 1, 0x13016F };

u32 mb5_gateMot4[] = { 1, 0x130176 };

u32 mb5_gateMot5[] = { 1, 0x130180 };

u32 mb5_gateMot6[] = { 1, 0x130184 };

u32 *mb5_gateMotTbl[] = { mb5_gateMot1, mb5_gateMot2, mb5_gateMot3, mb5_gateMot4, mb5_gateMot5, mb5_gateMot6 };

s32 mb5_gateOpenSeTbl[] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1
};

s32 mb5_gateOpenDelaySeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb5_gateOpenDelayTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb5_gateCloseSeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s16 mb5_bankMapIconMasuTbl[] = { 109, 121 };

s16 mb5_shopMapIconMasuTbl[] = { 148, 119 };

DecisionTreeNonLeafNode mb5ev_branch2FlagComTree[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2Flag2ComTree[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0Item[] = {
    { 2, { .data = 0x000000F0 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000003 }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000001 }, { .node_data = mb5ev_branch2FlagComTree } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00300000 }, { .node_data = mb5ev_branch2Flag2ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0Star0Flag[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0Star0[] = {
    { 4, { .data = 0x00300000 }, { .node_data = mb5ev_branch2ComTree0Star0Flag } },
    { 3, { .data = 0x00000004 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0Star1[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0Star23[] = {
    { 4, { .data = 0x00000001 }, { .node_data = mb5ev_branch2FlagComTree } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00300000 }, { .node_data = mb5ev_branch2Flag2ComTree } },
    { 3, { .data = 0x00000008 }, { .data = 0x0C96A33C } },
    { 3, { .data = 0x00000020 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree0[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch2ComTree0Item } },
    { 2, { .data = 0x00000001 }, { .node_data = mb5ev_branch2ComTree0Star0 } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5ev_branch2ComTree0Star1 } },
    { 2, { .data = 0x0000000C }, { .node_data = mb5ev_branch2ComTree0Star23 } },
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree1Star0[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0BF6A83C } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A846 } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree1Item[] = {
    { 2, { .data = 0x000000F0 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree1[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5ev_branch2ComTree1Star0 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch2ComTree1Item } },
    { 3, { .data = 0x00000020 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree2Star0Flag[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree2Star0[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 4, { .data = 0x00300000 }, { .node_data = mb5ev_branch2ComTree2Star0Flag } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C96A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch2ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5ev_branch2ComTree2Star0 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode *mb5ev_branch2ComTree[] = { mb5ev_branch2ComTree0, mb5ev_branch2ComTree1, mb5ev_branch2ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch3ComTree0Star1[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .node_data = mb5ev_branch3ComTree0Star1 } },
    { 2, { .data = 0x00000001 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree1[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2Star0[] = {
    { 3, { .data = 0x00000017 }, { .data = 0x0BF6A33C } },
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 4, { .data = 0x00300001 }, { .data = 0x1BF6A33C } },
    { 3, { .data = 0x00000012 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2Star1[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 1, { .data = 0x00000014 }, { .data = 0x1BF6A83C } },
    { 3, { .data = 0x0000002A }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2Star23Flag[] = {
    { 3, { .data = 0x00000080 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2Star23[] = {
    { 4, { .data = 0x00000001 }, { .node_data = mb5ev_branch3ComTree2Star23Flag } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2Sub[] = {
    { 4, { .data = 0x00300000 }, { .data = 0x1BF6A33C } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch3ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5ev_branch3ComTree2Star0 } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5ev_branch3ComTree2Star1 } },
    { 2, { .data = 0x0000000C }, { .node_data = mb5ev_branch3ComTree2Star23 } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_branch3ComTree2Sub } },
    { 8, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000020 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x00000030 }, { .node_data = mb5ev_branch3ComTree2Sub } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb5ev_branch3ComTree[] = { mb5ev_branch3ComTree0, mb5ev_branch3ComTree1, mb5ev_branch3ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch4ComTree0[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch4ComTree1[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A83C } },
    { 4, { .data = 0x00300001 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch4ComTree2Item[] = {
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb5ev_branch4ComTree2[] = {
    { 2, { .data = 0x00000003 }, { .data = 0x1BF6A83C } },
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch4ComTree2Item } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode *mb5ev_branch4ComTree[] = { mb5ev_branch4ComTree0, mb5ev_branch4ComTree1, mb5ev_branch4ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch5ComTree0[] = {
    { 2, { .data = 0x00000034 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch5ComTree1[] = {
    { 2, { .data = 0x00000034 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch5ComTree2[] = {
    { 2, { .data = 0x00000034 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode *mb5ev_branch5ComTree[] = { mb5ev_branch5ComTree0, mb5ev_branch5ComTree1, mb5ev_branch5ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch6ComTree0[] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch6ComTree1[] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch6ComTree2Star7[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode mb5ev_branch6ComTree2[] = {
    { 2, { .data = 0x00000080 }, { .node_data = mb5ev_branch6ComTree2Star7 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A83C } }
};

DecisionTreeNonLeafNode *mb5ev_branch6ComTree[] = { mb5ev_branch6ComTree0, mb5ev_branch6ComTree1, mb5ev_branch6ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch7ComTree0Star5[] = {
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch7ComTree0Star67[] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch7ComTree0[] = {
    { 2, { .data = 0x00000020 }, { .node_data = mb5ev_branch7ComTree0Star5 } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_branch7ComTree0Star67 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch7ComTree1[] = {
    { 3, { .data = 0x00000006 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch7ComTree2[] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch7ComTree[] = { mb5ev_branch7ComTree0, mb5ev_branch7ComTree1, mb5ev_branch7ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch8ComTree0ItemStar67[] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree0Item[] = {
    { 2, { .data = 0x0000000F }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_branch8ComTree0ItemStar67 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree0Star67Flag[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000030 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree0Star67[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb5ev_branch8ComTree0Star67Flag } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree0[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch8ComTree0Item } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_branch8ComTree0Star67 } },
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree1Star4[] = {
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 3, { .data = 0x00000003 }, { .data = 0x1BF6A33C } },
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree1[] = {
    { 2, { .data = 0x00000010 }, { .node_data = mb5ev_branch8ComTree1Star4 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch8ComTree2[] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0BF6A5BC } },
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch8ComTree[] = { mb5ev_branch8ComTree0, mb5ev_branch8ComTree1, mb5ev_branch8ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch9ComTree0[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch9ComTree1[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch9ComTree2[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch9ComTree[] = { mb5ev_branch9ComTree0, mb5ev_branch9ComTree1, mb5ev_branch9ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch10Star245ComTree[] = {
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch10ComTree0[] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000034 }, { .node_data = mb5ev_branch10Star245ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch10ComTree1[] = {
    { 2, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000034 }, { .node_data = mb5ev_branch10Star245ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch10ComTree2[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch10ComTree[] = { mb5ev_branch10ComTree0, mb5ev_branch10ComTree1, mb5ev_branch10ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch11Star45ComTree[] = {
    { 9, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch11ComTree0[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000030 }, { .node_data = mb5ev_branch11Star45ComTree } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch11ComTree1[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000030 }, { .node_data = mb5ev_branch11Star45ComTree } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch11ComTree2[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x1BF6A5BC } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch11ComTree[] = { mb5ev_branch11ComTree0, mb5ev_branch11ComTree1, mb5ev_branch11ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch12ItemComTree[] = {
    { 2, { .data = 0x000000CF }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb5ev_branch12ComTree0[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch12ItemComTree } },
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb5ev_branch12ComTree1[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch12ItemComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch12ComTree2Star2[] = {
    { 9, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch12ComTree2[] = {
    { 2, { .data = 0x00000004 }, { .node_data = mb5ev_branch12ComTree2Star2 } },
    { 2, { .data = 0x00000038 }, { .data = 0x1BF6A5BC } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000001 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch12ComTree[] = { mb5ev_branch12ComTree0, mb5ev_branch12ComTree1, mb5ev_branch12ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch13ComTree0Star01[] = {
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch13ComTree0[] = {
    { 2, { .data = 0x00000040 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x00000003 }, { .node_data = mb5ev_branch13ComTree0Star01 } },
    { 9, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch13ComTree1[] = {
    { 2, { .data = 0x00000043 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000002 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 9, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch13ComTree2[] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x1BF6A5BC } },
    { 9, { .data = 0x00000001 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000002 }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .data = 0x0BF6A33C } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode *mb5ev_branch13ComTree[] = { mb5ev_branch13ComTree0, mb5ev_branch13ComTree1, mb5ev_branch13ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch14ComTree0Star6[] = {
    { 9, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch14ComTree0[] = {
    { 2, { .data = 0x00000040 }, { .node_data = mb5ev_branch14ComTree0Star6 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch14ComTree1Item[] = {
    { 2, { .data = 0x00000003 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch14ComTree1[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb5ev_branch14ComTree1Item } },
    { 3, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_branch14ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb5ev_branch14ComTree[] = { mb5ev_branch14ComTree0, mb5ev_branch14ComTree1, mb5ev_branch14ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch15ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch15ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch15ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb5ev_branch15ComTree[] = { mb5ev_branch15ComTree0, mb5ev_branch15ComTree1, mb5ev_branch15ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch16ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch16ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch16ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb5ev_branch16ComTree[] = { mb5ev_branch16ComTree0, mb5ev_branch16ComTree1, mb5ev_branch16ComTree2 };

DecisionTreeNonLeafNode mb5ev_branch17ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch17ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_branch17ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb5ev_branch17ComTree[] = { mb5ev_branch17ComTree0, mb5ev_branch17ComTree1, mb5ev_branch17ComTree2 };

DecisionTreeNonLeafNode mb5ev_whompMasu142Star3WalkComTree[] = {
    { 4, { .data = 0x00400000 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu142Star3ComTree[] = {
    { 3, { .data = 0x00000002 }, { .node_data = mb5ev_whompMasu142Star3WalkComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu142Star45WalkComTree[] = {
    { 4, { .data = 0x00400001 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu142Star45ComTree[] = {
    { 3, { .data = 0x00000002 }, { .node_data = mb5ev_whompMasu142Star45WalkComTree } },
    { 4, { .data = 0x00400000 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu142ComTree[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5ev_whompMasu142Star3ComTree } },
    { 2, { .data = 0x00000030 }, { .node_data = mb5ev_whompMasu142Star45ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu3ComTree[] = {
    { 2, { .data = 0x000000C3 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124Star01WalkComTree[] = {
    { 4, { .data = 0x00300001 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124Star01ComTree[] = {
    { 3, { .data = 0x00000004 }, { .node_data = mb5ev_whompMasu124Star01WalkComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124Star67WalkComTree[] = {
    { 1, { .data = 0x0000001E }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124Star67Walk2ComTree[] = {
    { 4, { .data = 0x00300000 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124Star67ComTree[] = {
    { 3, { .data = 0x00000001 }, { .node_data = mb5ev_whompMasu124Star67WalkComTree } },
    { 3, { .data = 0x00000004 }, { .node_data = mb5ev_whompMasu124Star67Walk2ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu124ComTree[] = {
    { 2, { .data = 0x00000003 }, { .node_data = mb5ev_whompMasu124Star01ComTree } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_whompMasu124Star67ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_whompMasu129ComTree[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150Star23FlagComTree[] = {
    { 3, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150Star23Flag2ComTree[] = {
    { 3, { .data = 0x00000040 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150Star23ComTree[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb5ev_cartRideMasu150Star23FlagComTree } },
    { 4, { .data = 0x00000001 }, { .node_data = mb5ev_cartRideMasu150Star23Flag2ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150Star45ComTree[] = {
    { 3, { .data = 0x00000019 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150Star7ComTree[] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu150ComTree[] = {
    { 2, { .data = 0x0000000C }, { .node_data = mb5ev_cartRideMasu150Star23ComTree } },
    { 2, { .data = 0x00000030 }, { .node_data = mb5ev_cartRideMasu150Star45ComTree } },
    { 2, { .data = 0x00000040 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5ev_cartRideMasu150Star7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu126Star0ComTree[] = {
    { 3, { .data = 0x00000018 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu126ComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5ev_cartRideMasu126Star0ComTree } },
    { 2, { .data = 0x00000002 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu112Star4ComTree[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu112Star5ComTree[] = {
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu112Star67FlagComTree[] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu112Star67ComTree[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb5ev_cartRideMasu112Star67FlagComTree } },
    { 3, { .data = 0x00000014 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu112ComTree[] = {
    { 2, { .data = 0x00000010 }, { .node_data = mb5ev_cartRideMasu112Star4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5ev_cartRideMasu112Star5ComTree } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_cartRideMasu112Star67ComTree } },
    { 3, { .data = 0x0000000C }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu132Star013ComTree[] = {
    { 3, { .data = 0x0000000C }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu132Star67FlagComTree[] = {
    { 3, { .data = 0x00000010 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu132Star67Flag2ComTree[] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu132Star67ComTree[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x1BF6A33C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb5ev_cartRideMasu132Star67FlagComTree } },
    { 4, { .data = 0x00000001 }, { .node_data = mb5ev_cartRideMasu132Star67Flag2ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartRideMasu132ComTree[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 2, { .data = 0x0000000B }, { .node_data = mb5ev_cartRideMasu132Star013ComTree } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb5ev_cartRideMasu132Star67ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb5ev_cartJumpComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu126ComTree[] = {
    { 2, { .data = 0x00000043 }, { .data = 0x1C97E846 } },
    { 2, { .data = 0x0000003C }, { .data = 0x0C97E846 } },
    { 9, { .data = 0x00000010 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C97E846 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu150Star1ComTree[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0C97E846 } },
    { 12, { .data = 0x00000014 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C97E846 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu150Star4567ComTree[] = {
    { 3, { .data = 0x00000009 }, { .data = 0x1C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu150ComTree[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0C97E846 } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5ev_cartBranchMasu150Star1ComTree } },
    { 2, { .data = 0x000000F0 }, { .node_data = mb5ev_cartBranchMasu150Star4567ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu132ComTree[] = {
    { 2, { .data = 0x00000010 }, { .data = 0x0C97E846 } },
    { 3, { .data = 0x00000004 }, { .data = 0x0C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1A119E32 } }
};

DecisionTreeNonLeafNode mb5ev_cartBranchMasu112ComTree[] = {
    { 2, { .data = 0x00000034 }, { .data = 0x1C97E846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97E846 } }
};

event_list_entry mb5_branch1EventTbl[] = {
    { 8, 1, MB5Ev_Branch1 },
    { 0, 0, NULL }
};

event_list_entry mb5_branch1RevEventTbl[] = {
    { 1, 1, MB5Ev_Branch1Rev },
    { 0, 0, NULL }
};

s16 mb5ev_branch2Masu[][3] = {
    { 77, 42, -1 },
    { 66, 42, -1 },
    { 66, 77, -1 }
};

BranchLink mb5ev_branch2Link[][2] = {
    { { 3, 0, 0 }, { 7, 0, 0 } },
    { { 1, 8, 1 }, { 7, 0, 0 } },
    { { 1, 8, 1 }, { 3, 0, 0 } }
};

event_list_entry mb5_branch2EventTbl[] = {
    { 1, 2, MB5Ev_Branch2 },
    { 0, 0, NULL }
};

s16 mb5ev_branch3Masu[][3] = {
    { 29, 26, -1 },
    { 27, 26, -1 },
    { 27, 29, -1 }
};

BranchLink mb5ev_branch3Link[][2] = {
    { { 2, 0, 0 }, { 4, 8, 1 } },
    { { 1, 0, 0 }, { 4, 8, 1 } },
    { { 1, 0, 0 }, { 2, 0, 0 } }
};

event_list_entry mb5_branch3EventTbl[] = {
    { 1, 2, MB5Ev_Branch3 },
    { 0, 0, NULL }
};

s16 mb5ev_branch4Masu[][3] = {
    { 34, 141, -1 },
    { 2, 141, -1 },
    { 2, 34, -1 }
};

BranchLink mb5ev_branch4Link[][2] = {
    { { 4, 0, 0 }, { 14, 0, 0 } },
    { { 3, 3, 1 }, { 14, 0, 0 } },
    { { 3, 3, 1 }, { 4, 0, 0 } }
};

event_list_entry mb5_branch4EventTbl[] = {
    { 1, 2, MB5Ev_Branch4 },
    { 0, 0, NULL }
};

s16 mb5ev_branch5Masu[][3] = {
    { 38, 17, -1 },
    { 37, 17, -1 },
    { 37, 38, -1 }
};

BranchLink mb5ev_branch5Link[][2] = {
    { { 5, 0, 0 }, { 6, 0, 0 } },
    { { 14, 15, 1 }, { 6, 0, 0 } },
    { { 14, 15, 1 }, { 5, 0, 0 } }
};

event_list_entry mb5_branch5EventTbl[] = {
    { 1, 2, MB5Ev_Branch5 },
    { 0, 0, NULL }
};

s16 mb5ev_branch6Masu[][3] = {
    { 126, 54, -1 },
    { 53, 54, -1 },
    { 53, 126, -1 }
};

BranchLink mb5ev_branch6Link[][2] = {
    { { 8, 0, 0 }, { 9, 0, 0 } },
    { { 16, 16, 1 }, { 9, 0, 0 } },
    { { 16, 16, 1 }, { 8, 0, 0 } }
};

event_list_entry mb5_branch6EventTbl[] = {
    { 1, 2, MB5Ev_Branch6 },
    { 0, 0, NULL }
};

s16 mb5ev_branch7Masu[][3] = {
    { 132, 67, -1 },
    { 65, 67, -1 },
    { 65, 132, -1 }
};

BranchLink mb5ev_branch7Link[][2] = {
    { { 10, 0, 0 }, { 11, 0, 0 } },
    { { 9, 11, 1 }, { 11, 0, 0 } },
    { { 9, 11, 1 }, { 10, 0, 0 } }
};

event_list_entry mb5_branch7EventTbl[] = {
    { 1, 2, MB5Ev_Branch7 },
    { 0, 0, NULL }
};

s16 mb5ev_branch8Masu[][3] = {
    { 73, 97, -1 },
    { 72, 97, -1 },
    { 72, 73, -1 }
};

BranchLink mb5ev_branch8Link[][2] = {
    { { 15, 0, 0 }, { 13, 0, 0 } },
    { { 11, 5, 1 }, { 13, 0, 0 } },
    { { 11, 5, 1 }, { 15, 0, 0 } }
};

event_list_entry mb5_branch8EventTbl[] = {
    { 1, 2, MB5Ev_Branch8 },
    { 0, 0, NULL }
};

s16 mb5ev_branch9Masu[][3] = {
    { 138, 89, -1 },
    { 76, 89, -1 },
    { 76, 138, -1 }
};

BranchLink mb5ev_branch9Link[][2] = {
    { { 15, 5, 0 }, { 12, 0, 0 } },
    { { 15, 3, 1 }, { 12, 0, 0 } },
    { { 15, 3, 1 }, { 15, 5, 0 } }
};

event_list_entry mb5_branch9EventTbl[] = {
    { 1, 2, MB5Ev_Branch9 },
    { 0, 0, NULL }
};

s16 mb5ev_branch10Masu[][3] = {
    { 23, 20, -1 },
    { 36, 20, -1 },
    { 36, 23, -1 }
};

BranchLink mb5ev_branch10Link[][2] = {
    { { 4, 4, 0 }, { 6, 3, 1 } },
    { { 4, 2, 1 }, { 6, 3, 1 } },
    { { 4, 2, 1 }, { 4, 4, 0 } }
};

event_list_entry mb5_branch10EventTbl[] = {
    { 1, 1, MB5Ev_Branch10RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch11Masu[][3] = {
    { 6, 41, -1 },
    { 4, 41, -1 },
    { 4, 6, -1 }
};

BranchLink mb5ev_branch11Link[][2] = {
    { { 14, 5, 0 }, { 5, 4, 1 } },
    { { 14, 3, 1 }, { 5, 4, 1 } },
    { { 14, 3, 1 }, { 14, 5, 0 } }
};

event_list_entry mb5_branch11EventTbl[] = {
    { 1, 1, MB5Ev_Branch11RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch12Masu[][3] = {
    { 7, 136, -1 },
    { 5, 136, -1 },
    { 5, 7, -1 }
};

BranchLink mb5ev_branch12Link[][2] = {
    { { 14, 6, 0 }, { 13, 3, 1 } },
    { { 14, 4, 1 }, { 13, 3, 1 } },
    { { 14, 4, 1 }, { 14, 6, 0 } }
};

event_list_entry mb5_branch12EventTbl[] = {
    { 1, 1, MB5Ev_Branch12RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch13Masu[][3] = {
    { 82, 87, -1 },
    { 80, 87, -1 },
    { 80, 82, -1 }
};

BranchLink mb5ev_branch13Link[][2] = {
    { { 16, 5, 0 }, { 8, 4, 1 } },
    { { 16, 3, 1 }, { 8, 4, 1 } },
    { { 16, 3, 1 }, { 16, 5, 0 } }
};

event_list_entry mb5_branch13EventTbl[] = {
    { 1, 1, MB5Ev_Branch13RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch14Masu[][3] = {
    { 83, 45, -1 },
    { 116, 45, -1 },
    { 116, 83, -1 }
};

BranchLink mb5ev_branch14Link[][2] = {
    { { 16, 6, 1 }, { 16, 8, 0 } },
    { { 7, 3, 1 }, { 16, 8, 0 } },
    { { 7, 3, 1 }, { 16, 6, 1 } }
};

event_list_entry mb5_branch14EventTbl[] = {
    { 1, 1, MB5Ev_Branch14RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch15Masu[][3] = {
    { 60, 93, -1 },
    { 58, 93, -1 },
    { 58, 60, -1 }
};

BranchLink mb5ev_branch15Link[][2] = {
    { { 9, 5, 0 }, { 12, 4, 1 } },
    { { 9, 3, 1 }, { 12, 4, 1 } },
    { { 9, 3, 1 }, { 9, 5, 0 } }
};

event_list_entry mb5_branch15EventTbl[] = {
    { 1, 1, MB5Ev_Branch15RKinoko },
    { 0, 0, NULL }
};

s16 mb5ev_branch16Masu[][3] = {
    { 74, 76, -1 },
    { 96, 76, -1 },
    { 96, 74, -1 }
};

BranchLink mb5ev_branch16Link[][2] = {
    { { 15, 1, 1 }, { 15, 3, 0 } },
    { { 10, 3, 1 }, { 15, 3, 0 } },
    { { 10, 3, 1 }, { 15, 1, 1 } }
};

event_list_entry mb5_branch16EventTbl[] = {
    { 1, 1, MB5Ev_Branch16RKinoko },
    { 0, 0, NULL }
};

event_list_entry mb5_merge1EventTbl[] = {
    { 1, 1, MB5Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge2EventTbl[] = {
    { 1, 1, MB5Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge3EventTbl[] = {
    { 1, 1, MB5Ev_Merge3 },
    { 0, 0, NULL }
};

s16 mb5ev_branch17Masu[][3] = {
    { 32, 88, -1 },
    { 131, 88, -1 },
    { 131, 32, -1 }
};

BranchLink mb5ev_branch17Link[][2] = {
    { { 2, 4, 1 }, { 3, 1, 0 } },
    { { 1, 9, 1 }, { 3, 1, 0 } },
    { { 1, 9, 1 }, { 2, 4, 1 } }
};

event_list_entry mb5_branch17EventTbl[] = {
    { 1, 1, MB5Ev_Branch17 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge4EventTbl[] = {
    { 1, 1, MB5Ev_Merge4 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge5EventTbl[] = {
    { 1, 1, MB5Ev_Merge5 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge6EventTbl[] = {
    { 1, 1, MB5Ev_Merge6 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge7EventTbl[] = {
    { 1, 1, MB5Ev_Merge7 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge8EventTbl[] = {
    { 1, 1, MB5Ev_Merge8 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge9EventTbl[] = {
    { 1, 1, MB5Ev_Merge9 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge10EventTbl[] = {
    { 1, 1, MB5Ev_Merge10 },
    { 0, 0, NULL }
};

event_list_entry mb5_whompMasu129CheckEventTbl[] = {
    { 1, 1, MB5Ev_WhompMasu129Check },
    { 0, 0, NULL }
};

event_list_entry mb5_cartRideMerge1EventTbl[] = {
    { 1, 1, MB5Ev_CartRideMerge1 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge11EventTbl[] = {
    { 1, 1, MB5Ev_Merge11 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge12EventTbl[] = {
    { 1, 1, MB5Ev_Merge12 },
    { 0, 0, NULL }
};

event_list_entry mb5_cartRideMerge2EventTbl[] = {
    { 1, 1, MB5Ev_CartRideMerge2 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge13EventTbl[] = {
    { 1, 1, MB5Ev_Merge13 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge14EventTbl[] = {
    { 1, 1, MB5Ev_Merge14 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge15EventTbl[] = {
    { 1, 1, MB5Ev_Merge15 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge16EventTbl[] = {
    { 1, 1, MB5Ev_Merge16 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge17EventTbl[] = {
    { 1, 1, MB5Ev_Merge17 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge18EventTbl[] = {
    { 1, 1, MB5Ev_Merge18 },
    { 0, 0, NULL }
};

event_list_entry mb5_merge19EventTbl[] = {
    { 1, 1, MB5Ev_Merge19 },
    { 0, 0, NULL }
};

event_list_entry mb5_whompMasu3CheckEventTbl[] = {
    { 1, 1, MB5Ev_WhompMasu3Check },
    { 0, 0, NULL }
};

event_list_entry mb5_keyManMasuEventTbl[] = {
    { 1, 2, MB5Ev_KeyManMasu },
    { 0, 0, NULL }
};

event_list_entry mb5_starMasuEventTbl[] = {
    { 1, 1, MB5Ev_StarMasu },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb5ev_bankComTree[] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } }
};

u32 mb5ev_bankCoinPileMot[] = { 1, 0xA009D };

event_list_entry mb5_bankMasuEventTbl[] = {
    { 1, 1, MB5Ev_BankMasu },
    { 0, 0, NULL }
};

u8 mb5ev_shopItemRowTbl[][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }
};

s8 mb5ev_shopItemTbl[][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } }
};

u8 mb5ev_shopBagRowTbl[][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }
};

s8 mb5ev_shopBagRateTbl[][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } }
};

u8 mb5ev_shopBagItemTbl[][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 }
};

s32 mb5ev_shopItemMesTbl[][2] = {
    { 0x3B05, 0x3D05 },
    { 0x3B06, 0x3D06 },
    { 0x3B07, 0x3D07 },
    { 0x3B08, 0x3D08 },
    { 0x3B09, 0x3D09 }
};

s32 mb5ev_shopEnterMesTbl[] = { 0x3B00, 0x3D00 };

s32 mb5ev_shopNoCoinMesTbl[] = { 0x3B01, 0x3D01 };

s32 mb5ev_shopItemFullMesTbl[] = { 0x3B02, 0x3D02 };

s32 mb5ev_shopLastTurnMesTbl[] = { 0x3B03, 0x3D03 };

s32 mb5ev_shopCancelMesTbl[] = { 0x3B04, 0x3D04 };

u32 mb5ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb5ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

s32 mb5ev_shopNo = 0;

event_list_entry mb5_shopMasuEventTbl[] = {
    { 1, 1, MB5Ev_ShopMasu },
    { 0, 0, NULL }
};

Vec2f mb5ev_teresaSprPosTbl[] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f }
};

Vec2f mb5ev_teresaSprDirTbl[] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f }
};

u8 mb5ev_teresaCoinTurnTbl[][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

u8 mb5ev_teresaCoinPenaltyTbl[][3] = {
    { 0, 0, 0 },
    { 1, 10, 1 },
    { 11, 11, 4 },
    { 12, 14, 2 },
    { 15, 15, 4 },
    { 16, 23, 3 },
    { 24, 33, 4 },
    { 34, 37, 5 },
    { 38, 39, 2 },
    { 40, 49, 6 },
    { 50, 54, 5 },
    { 55, 63, 7 },
    { 64, 64, 8 },
    { 65, 255, 9 }
};

u8 mb5ev_teresaCoinDiffTbl[] = { 9, 7, 4, 1, 0, 0, 0, 0 };

s32 mb5ev_teresaComTargetRateTbl[] = { 50, 80, 100 };

s32 mb5ev_teresaMdlFlipTbl[] = { 1, 0, 1, 0, 0, 1, 0 };

event_list_entry mb5_teresaMasuEventTbl[] = {
    { 1, 1, MB5Ev_Teresa },
    { 0, 0, NULL }
};

event_list_entry mb5_gate1CloseEventTbl[] = {
    { 1, 1, MB5Ev_Gate1Close },
    { 0, 0, NULL }
};

event_list_entry mb5_gate2CloseEventTbl[] = {
    { 1, 1, MB5Ev_Gate2Close },
    { 0, 0, NULL }
};

event_table_entry mb5_commonEventTbl[] = {
    { 11, mb5_starMasuEventTbl },
    { 31, mb5_starMasuEventTbl },
    { 40, mb5_starMasuEventTbl },
    { 19, mb5_starMasuEventTbl },
    { 72, mb5_starMasuEventTbl },
    { 92, mb5_starMasuEventTbl },
    { 86, mb5_starMasuEventTbl },
    { 49, mb5_starMasuEventTbl },
    { 33, mb5_bankMasuEventTbl },
    { 69, mb5_bankMasuEventTbl },
    { 147, mb5_shopMasuEventTbl },
    { 118, mb5_shopMasuEventTbl },
    { 117, mb5_gate1CloseEventTbl },
    { 137, mb5_gate2CloseEventTbl },
    { -1, NULL }
};

event_table_entry mb5_teresaEventTbl[] = {
    { 79, mb5_teresaMasuEventTbl },
    { -1, NULL }
};

Vec2f mb5ev_itemUsePosTbl[] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f }
};

Vec2f mb5ev_itemFadePosTbl[] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f }
};

Vec2f mb5ev_robBoxItemEndPosTbl[] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f }
};

Vec2f mb5ev_robBoxItemStartPosTbl[] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f }
};

DecisionTreeNonLeafNode mb5ev_shopPhoneComTree[] = {
    { 13, { .data = 0x00000000 }, { .data = 0x0A142850 } },
    { 13, { .data = 0x00000001 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000002 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000003 }, { .data = 0x08D1A346 } },
    { 13, { .data = 0x00000004 }, { .data = 0x078F1E3C } },
    { 13, { .data = 0x00000005 }, { .data = 0x064C9932 } },
    { 13, { .data = 0x00000006 }, { .data = 0x03C78F1E } },
    { 13, { .data = 0x00000007 }, { .data = 0x078F1E3C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

s32 mb5ev_itemPhoneWaveAngleTbl[] = { 20, 60, 30, 50, 70 };

DecisionTreeNonLeafNode mb5ev_keyManUseComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } }
};

Vec2f mb5ev_tereYokeSparkOfsTbl[] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f }
};

s32 mb5ev_gambleCoinPlayer = -1;

u8 mb5ev_gambleMgTbl[] = { 67, 68, 69, 0 };

u8 mb5ev_gambleMgRateTbl[] = { 20, 60, 100, 0 };

GameGuyReward mb5ev_gambleRateTbl[] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 }
};

RGB mb5ev_after5NumColorTbl[] = {
    { 240, 222, 53 },
    { 247, 26, 66 }
};

event_list_entry mb5_kinokoTurnEventTbl[] = {
    { 7, 1, MB5Ev_NKinokoTurnStart },
    { 7, 1, MB5Ev_RKinokoTurnStart },
    { 0, 0, NULL }
};

event_table_entry mb5_turnStatusEventTbl[] = {
    { -5, mb5_kinokoTurnEventTbl },
    { -1, NULL }
};

s16 mb5ev_cartEscapeLinkTbl[][6] = {
    { 9, 0, 9, 1, 16, 17 },
    { 1, 0, 1, 1, 4, 9 },
    { 11, 0, 11, 1, 9, 12 },
    { 6, 0, 6, 1, 14, 16 }
};

u32 mb5_whompMot[] = { 3, 0xA00D5, 0xA00D6, 0xA00D7 };

s16 mb5ev_cartTrackMasu0[] = {
    26, 149, 29, 150, 30, 31, 32, 77,
    81, 87, 86, 85, 84, 126, 125, 53,
    -1, 0
};

s16 mb5ev_cartTrackMasu1[] = {
    53, 125, 126, 84, 85, 86, 87, 81,
    77, 32, 31, 30, 150, 29, 149, 26,
    -1, 0
};

s16 mb5ev_cartTrackMasu2[] = {
    16, 37, 111, 38, 112, 39, 40, 41,
    5, 75, 96, 95, 94, 132, 130, -1
};

s16 mb5ev_cartTrackMasu3[] = {
    64, 65, 130, 132, 94, 95, 96, 75,
    5, 41, 40, 39, 112, 38, 111, -1
};

s16 *mb5ev_cartTrackMasuTbl[] = { mb5ev_cartTrackMasu0, mb5ev_cartTrackMasu1, mb5ev_cartTrackMasu2, mb5ev_cartTrackMasu3 };

s16 mb5ev_cartSideMasu2[] = { 65, 64, -1, 0 };

s16 mb5ev_cartSideMasu3[] = { 37, 16, -1, 0 };

s16 *mb5ev_cartSideMasuTbl[] = { mb5ev_cartSideMasu2, mb5ev_cartSideMasu3 };

f32 mb5ev_cartEscapeOfsTbl[][2] = {
    { 0.0f, 0.0f },
    { -10.0f, 0.0f },
    { 10.0f, 0.0f }
};

f32 mb5ev_cartSideOfsTblB[] = { 0.0f, -10.0f, 0.0f, 0.0f, -10.0f, 0.0f, 10.0f, 0.0f };

f32 mb5ev_cartSideOfsTblA[] = { 0.0f, 10.0f };

s16 mb5ev_cartBranchMasu126Tbl[] = { 125, 84, -1, 0 };

s16 mb5ev_cartBranchMasu150Tbl[] = { 29, 30, -1, 0 };

s16 mb5ev_cartBranchMasu132Tbl[] = { 130, 94, -1, 0 };

s16 mb5ev_cartBranchMasu112Tbl[] = { 38, 39, -1, 0 };

event_list_entry mb5_cartRideEventTbl[] = {
    { 1, 1, MB5Ev_CartRide },
    { 0, 0, NULL }
};

event_table_entry mb5_specialEventTbl[] = {
    { 108, mb5_branch1EventTbl },
    { 0, mb5_branch1RevEventTbl },
    { 131, mb5_branch2EventTbl },
    { 149, mb5_branch3EventTbl },
    { 142, mb5_branch4EventTbl },
    { 111, mb5_branch5EventTbl },
    { 125, mb5_branch6EventTbl },
    { 130, mb5_branch7EventTbl },
    { 123, mb5_branch8EventTbl },
    { 124, mb5_branch9EventTbl },
    { 21, mb5_branch10EventTbl },
    { 5, mb5_branch11EventTbl },
    { 6, mb5_branch12EventTbl },
    { 81, mb5_branch13EventTbl },
    { 43, mb5_branch14EventTbl },
    { 59, mb5_branch15EventTbl },
    { 75, mb5_branch16EventTbl },
    { 27, mb5_merge1EventTbl },
    { 29, mb5_merge2EventTbl },
    { 32, mb5_merge3EventTbl },
    { 77, mb5_branch17EventTbl },
    { 34, mb5_merge4EventTbl },
    { 141, mb5_merge5EventTbl },
    { 38, mb5_merge6EventTbl },
    { 41, mb5_merge7EventTbl },
    { 17, mb5_merge8EventTbl },
    { 20, mb5_merge9EventTbl },
    { 42, mb5_merge10EventTbl },
    { 129, mb5_whompMasu129CheckEventTbl },
    { 126, mb5_cartRideMerge1EventTbl },
    { 87, mb5_merge11EventTbl },
    { 54, mb5_merge12EventTbl },
    { 132, mb5_cartRideMerge2EventTbl },
    { 96, mb5_merge13EventTbl },
    { 67, mb5_merge14EventTbl },
    { 73, mb5_merge15EventTbl },
    { 139, mb5_merge16EventTbl },
    { 89, mb5_merge17EventTbl },
    { 93, mb5_merge18EventTbl },
    { 97, mb5_merge19EventTbl },
    { 3, mb5_whompMasu3CheckEventTbl },
    { 150, mb5_cartRideEventTbl },
    { 112, mb5_cartRideEventTbl },
    { 115, mb5_keyManMasuEventTbl },
    { 135, mb5_keyManMasuEventTbl },
    { 116, mb5_keyManMasuEventTbl },
    { 136, mb5_keyManMasuEventTbl },
    { -1, NULL }
};

RectF mb5ev_opStarMapViewRect = { 0.0f, 0.0f, 320.0f, 240.0f };

DecisionTreeNonLeafNode mb5_itemSKinokoStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E080F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar1PosComTree[] = {
    { 4, { .data = 0x00300001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar1Pos2ComTree[] = {
    { 4, { .data = 0x00300000 }, { .data = 0x00000000 } },
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar1ComTree[] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .node_data = mb5_itemSKinokoStar1PosComTree } },
    { 10, { .data = 0x000F0003 }, { .node_data = mb5_itemSKinokoStar1Pos2ComTree } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020304 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E070F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010304 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0010030C }, { .node_data = mb5_itemSKinokoStar1PosComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar23PosComTree[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00030003 }, { .node_data = mb5_itemSKinokoStar23PosComTree } },
    { 10, { .data = 0x000E030B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050304 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00400000 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090007 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0305 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00030003 }, { .node_data = mb5_itemSKinokoStar23PosComTree } },
    { 10, { .data = 0x000E030C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050004 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar4ComTree[] = {
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009000B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0103 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009000B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0205 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar67PosComTree[] = {
    { 6, { .func = MB5_ComWhompItemCheck }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00000000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar6ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0103 }, { .node_data = mb5_itemSKinokoStar67PosComTree } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0010030D }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00300001 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00010508 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020204 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E060F }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoStar7ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100101 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0003 }, { .node_data = mb5_itemSKinokoStar67PosComTree } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00100306 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00100C10 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080104 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009070B }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0103 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0205 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0C96A846 } },
    { 4, { .data = 0x00300001 }, { .data = 0x00000000 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00020000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040108 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060203 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemSKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemSKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemSKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemSKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemSKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemSKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemSKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemSKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemSKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemKSuitComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040608 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00050002 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0009080B }, { .data = 0x0000028A } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00060001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0204 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000F0203 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000C0002 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar6ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100E10 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00080102 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockStar7ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0010070B }, { .data = 0x0000028A } },
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb5_itemWarpBlockComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemWarpBlockStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemWarpBlockStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemWarpBlockStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemWarpBlockStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemWarpBlockStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemWarpBlockStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemWarpBlockStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemWarpBlockStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar0ComTree[] = {
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar1ComTree[] = {
    { 10, { .data = 0x00020002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040608 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00300000 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar2ComTree[] = {
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00050002 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00400000 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x0009080B }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar3ComTree[] = {
    { 10, { .data = 0x000E0D0F }, { .data = 0x0000028A } },
    { 10, { .data = 0x00060001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar4ComTree[] = {
    { 10, { .data = 0x000B0204 }, { .data = 0x0000028A } },
    { 12, { .data = 0x00000019 }, { .data = 0x0BF6A83C } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar5ComTree[] = {
    { 10, { .data = 0x000F0203 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000C0002 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar6ComTree[] = {
    { 10, { .data = 0x00100E10 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00080102 }, { .data = 0x0000028A } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00040708 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampStar7ComTree[] = {
    { 10, { .data = 0x0010070B }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb5_itemMajinLampComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemMajinLampStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemMajinLampStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemMajinLampStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemMajinLampStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemMajinLampStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemMajinLampStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemMajinLampStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemMajinLampStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar0ComTree[] = {
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar1ComTree[] = {
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar2ComTree[] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar3ComTree[] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar4ComTree[] = {
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar5ComTree[] = {
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar6ComTree[] = {
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStar7ComTree[] = {
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemNKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemNKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemNKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemNKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemNKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemNKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemNKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemNKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoPosComTree[] = {
    { 10, { .data = 0x00010204 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemNKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb5_itemNKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb5_itemNKinokoPosComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010405 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010608 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020404 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070000 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028A1E } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00080103 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000E0407 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050404 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028A1E } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000A0102 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x0000001E }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B0303 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00040307 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060303 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar4ItemComTree[] = {
    { 10, { .data = 0x000E0608 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .node_data = mb5_itemRKinokoStar4ItemComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000C0404 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090508 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar6ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStar7ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080101 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemRKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemRKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemRKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemRKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemRKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemRKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemRKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemRKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar0ComTree[] = {
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar1ComTree[] = {
    { 11, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar2ComTree[] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar3ComTree[] = {
    { 11, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar4ComTree[] = {
    { 11, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar5ComTree[] = {
    { 11, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar6ComTree[] = {
    { 11, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStar7ComTree[] = {
    { 11, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemStarYokeStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemStarYokeStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemStarYokeStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemStarYokeStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemStarYokeStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemStarYokeStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemStarYokeStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemStarYokeStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb5_itemRKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb5_itemStarYokeStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar1ComTree[] = {
    { 15, { .data = 0x00020002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300000 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x00100D10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00050002 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00400000 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x0009080B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar3ComTree[] = {
    { 15, { .data = 0x000E0D0F }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x000B0204 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x000F0203 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x000C0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar6ComTree[] = {
    { 15, { .data = 0x00100E10 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00080102 }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00300001 }, { .data = 0x00028F1E } },
    { 15, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00040708 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x0010070B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb5_itemRKinokoTargetComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb5_itemRKinokoTargetStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb5_itemRKinokoTargetStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb5_itemRKinokoTargetStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb5_itemRKinokoTargetStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb5_itemRKinokoTargetStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb5_itemRKinokoTargetStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb5_itemRKinokoTargetStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb5_itemRKinokoTargetStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_itemStarYokeComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb5_itemStarYokeStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopKeyComTree0Star4567[] = {
    { 4, { .data = 0x00300000 }, { .data = 0x00028A1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopKeyComTree0[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x000000F0 }, { .node_data = mb5_comShopKeyComTree0Star4567 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopKeyComTree1Star0123[] = {
    { 4, { .data = 0x00400001 }, { .data = 0x00028A1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopKeyComTree1[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x0000000F }, { .node_data = mb5_comShopKeyComTree1Star0123 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopItemComTree0[] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopItemComTree1[] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb5_comShopEnterComTree0[] = {
    { 2, { .data = 0x0000003C }, { .data = 0x0B54233C } },
    { 1, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000F32 } }
};

DecisionTreeNonLeafNode mb5_comShopEnterComTree1[] = {
    { 2, { .data = 0x000000CB }, { .data = 0x0B54233C } },
    { 1, { .data = 0x0000001E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000F32 } }
};

s32 mb5_comShopCancelF = 0;

u8 mb5_comShopItemOrderMario[] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1
};

u8 mb5_comShopItemOrderLuigi[] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5
};

u8 mb5_comShopItemOrderPeach[] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1
};

u8 mb5_comShopItemOrderYoshi[] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1
};

u8 mb5_comShopItemOrderWario[] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1
};

u8 mb5_comShopItemOrderDk[] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1
};

u8 mb5_comShopItemOrderWaluigi[] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1
};

u8 mb5_comShopItemOrderDaisy[] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5
};

u8 *mb5_comShopItemOrderTbl[] = { mb5_comShopItemOrderMario, mb5_comShopItemOrderLuigi, mb5_comShopItemOrderPeach, mb5_comShopItemOrderYoshi, mb5_comShopItemOrderWario, mb5_comShopItemOrderDk, mb5_comShopItemOrderWaluigi, mb5_comShopItemOrderDaisy };

s8 mb5_comShopItemRateMario[] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb5_comShopItemRateLuigi[] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0
};

s8 mb5_comShopItemRatePeach[] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10
};

s8 mb5_comShopItemRateYoshi[] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10
};

s8 mb5_comShopItemRateWario[] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10
};

s8 mb5_comShopItemRateDk[] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb5_comShopItemRateWaluigi[] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10
};

s8 mb5_comShopItemRateDaisy[] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10
};

s8 *mb5_comShopItemRateTbl[] = { mb5_comShopItemRateMario, mb5_comShopItemRateLuigi, mb5_comShopItemRatePeach, mb5_comShopItemRateYoshi, mb5_comShopItemRateWario, mb5_comShopItemRateDk, mb5_comShopItemRateWaluigi, mb5_comShopItemRateDaisy };

DecisionTreeNonLeafNode *mb5_comShopKeyComTree[] = { mb5_comShopKeyComTree0, mb5_comShopKeyComTree1 };

DecisionTreeNonLeafNode *mb5_comShopItemComTree[] = { mb5_comShopItemComTree0, mb5_comShopItemComTree1 };

DecisionTreeNonLeafNode *mb5_comShopEnterComTree[2] = { mb5_comShopEnterComTree0, mb5_comShopEnterComTree1 };

Object *mb5_starGuideBaseMdl BSS;
u8 mb5_starGuideBaseMdlPad[4] BSS; /* Unreferenced. */
Object *mb5_starGuideMdl[8] BSS;
Process *mb5_starGuideHoverProc[8] BSS;
s32 mb5ev_starGuideInProc BSS;
Object *mb5ev_starGuideInMdl BSS;
Unk3 *mb5_branchStickHelp BSS;
Unk3 *mb5_branchBtnHelp BSS;
Unk3 *mb5_branchMapScrollHelp BSS;
Unk3 *mb5_branchMapOverheadHelp BSS;
Unk3 *mb5_branchItemHelp BSS;
s32 mb5_comTeresaType BSS;
s32 mb5_comTeresaTarget BSS;
u8 mb5_comTeresaTargetPad[4] BSS; /* Unreferenced. */
s32 mb5ev_cartJumpStateTbl[4] BSS;
s32 mb5ev_cartJumpF BSS;
Object *mb5_cartBlockMdlA BSS;
Object *mb5_cartBlockMdlB BSS;
Object *mb5ev_cartMdl BSS;
Process *mb5ev_actionTimeSprProc BSS;
Vec mb5ev_cartCameraPos BSS;
Object *mb5_teresaGuideBaseMdl BSS;
Object *mb5_teresaGuideMdl[1] BSS;
Object *mb5_bankCoinBaseMdl BSS;
u8 mb5_bankCoinBaseMdlPad[4] BSS; /* Unreferenced. */
Object *mb5_bankCoinMdl[10] BSS;
Object *mb5_gateBaseMdl BSS;
Object *mb5_gateMdl[2] BSS;
s32 mb5ev_shopHostNo BSS;
s32 mb5ev_shopItemRow BSS;
u8 *mb5ev_shopItemEnableTbl BSS;
Object *mb5ev_teresaCoinMdl BSS;
s32 mb5ev_itemPhoneWaveSpr BSS;
s32 mb5ev_tereYokePlayer BSS;
s32 mb5ev_tereYokeSparkSpr BSS;
Object *mb5ev_koopaCardCoinMdl BSS;
Object *mb5ev_koopaCardMdl BSS;
s32 mb5_comExchangeBoxTarget BSS;
s32 mb5_comRobBoxTarget BSS;
Object *mb5ev_gambleCoinMdl BSS;
u8 mb5ev_gambleCoinMdlPad[4] BSS; /* Unreferenced. */
s32 mb5ev_after5GrpId[4] BSS;
Object *mb5ev_after5EffMdl BSS;
u8 mb5ev_after5EffMdlPad[4] BSS; /* Unreferenced. */
Object *mb5ev_kinokoMarkMdl[4] BSS;
omObjData *mb5ev_kinokoMarkObj[4] BSS;
s32 mb5_comRKinokoTarget BSS;
s32 mb5_comNKinokoTarget BSS;


s16 MB5Ev_StarGuideMasuGet(void) {
    return mb5ev_starGuideMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void MB5Ev_StarShuffle(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < mb5ev_starOrderGroupTbl[idx2]) {
                continue;
            }
            if (idx2 < mb5ev_starOrderGroupTbl[idx1]) {
                continue;
            }
            {
                s32 temp = mb5ev_starOrderTbl[idx1];
                mb5ev_starOrderTbl[idx1] = mb5ev_starOrderTbl[idx2];
                mb5ev_starOrderTbl[idx2] = temp;
                temp = mb5ev_starOrderGroupTbl[idx1];
                mb5ev_starOrderGroupTbl[idx1] = mb5ev_starOrderGroupTbl[idx2];
                mb5ev_starOrderGroupTbl[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = mb5ev_starOrderTbl[i];
    }
}

void MB5Ev_StarNextPos(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        MB5Ev_StarShuffle();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void MB5Ev_StarMasuInit(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(mb5ev_starFlag[i]);
    }
    MBMasuTypeSet(mb5ev_starMasu[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(mb5ev_starFlag[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s16 MB5Ev_StarCheck(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == mb5ev_starMasu[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = mb5ev_starFlag[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void MB5Ev_StarGuideIn(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    mb5ev_starGuideInMdl = MBModelCreate(0x3A, NULL);
    model = mb5ev_starGuideInMdl;
    AuraCreate(model->omObj1->model[0]);
    model->flags |= 4;
    MBModelBillboardSet(model);
    HuVecCopy3F(&model->coords, &space->coords);
    model->velocity.x = 50.0f;
    obj = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(obj, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(obj, 30.0f);
    EffectPosSet(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
    Hu3DModelCameraSet(obj, HU3D_CAM0);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        EffectRangeSet(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        EffectRangeSet(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    EffectRangeSet(obj, scale * 30.0f);
    HuPrcSleep(30);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    while (1) {
        HuMtxRotYF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (scale > 0.6f) {
            scale -= 0.04f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        if (model->velocity.x > 10.0f) {
            model->velocity.x -= 1.2f;
        }
        EffectRangeSet(obj, scale * 30.0f);
        EffectPosSet(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        if ((model->velocity.x <= 10.0f) & (scale <= 0.6f)) {
            if (angle == 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    HuMtxRotYF(Hu3DData[model->omObj1->model[0]].mtx, 0.0f);
    EffectStop(obj);
    mb5ev_starGuideInProc = 0;
    omDelPrcObj(NULL);
}

void MB5Ev_StarGuideJumpExec(omObjData **arg) {
    omObjData *s0 = *arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

void MB5Ev_StarMapView(void) {
    struct UnkMBGuideData *data;
    GW_SYSTEM *loc = &GwSystem;
    SpaceData *space;
    s32 idx;

    mbTurnUnkF = 0;
    data = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(data->obj, 2, 0xF, mb5ev_starGuideFaceTbl[0]);
    MBPlayerIconMdlSet();
    MBModelDispOff(mb5_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBBackThreadPriLowSet();
    MBCameraSpeedDivSet(3.0f);
    MB5Ev_StarGuideJumpExec((omObjData **)data);
    HuWinMesSet(
        data->amount,
        (loc->current_star_spawn == 0 && GWBoardFlagCheck(4) == 0)
            ? (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E00)
            : (((loc->current_board_index == 2) ? 0x5E09 : 0) | 0x5E01),
        -1, -1);
    HuWinExOpen(data->amount, 1);
    HuAudFXPlay(0x2A7);
    MBWinComKeyAllWaitKeep(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    HuWinExClose(data->amount, 1);
    Hu3DMotionReset(data->obj->omObj1->model[0]);
    if (loc->current_board_index != 2 || (rand8() & 1)) {
        space = MBMasuGet(mb5ev_starGuideMasu[loc->star_spawn_indices[loc->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    idx = MBRand(7.0f);
    MBGuideFaceSet(data->obj, mb5ev_starGuideFaceTbl[idx]);
    MBMotionSet(data->obj, -1, 2);
    if (loc->current_board_index != 2) {
        Process *prc = omAddPrcObj(MB5Ev_StarGuideIn, 0x4800, 0, 0);
        mb5ev_starGuideInProc = (s32)prc;
        prc->user_data = space;
        HuPrcSleep(30);
    } else {
        mb5ev_starGuideInProc = 0;
    }
    HuWinMesSet(data->amount, mb5ev_starGuideMesTbl[idx], -1, -1);
    HuWinExOpen(data->amount, 1);
    MBWinComKeyAllWaitKeep(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    HuWinExClose(data->amount, 1);
    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(WIPE_STARS, 0x10);
    HuPrcSleep(0x11);
    mbTurnUnkF = 1;
    MBPlayerIconMdlReset();
    AuraKill(mb5ev_starGuideInMdl->omObj1->model[0]);
    MBModelKill(mb5ev_starGuideInMdl);
    MBModelDispOn(mb5_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBGuideKill(data);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB5Ev_StarGet(void) {
    Object *playerModel = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *model;
    Vec camPos;
    f32 scale;
    f32 angle;
    s32 obj;
    s32 i;

    HuAudFXPlay(0x11B);
    model = MBModelCreate(0x1A, NULL);
    model->flags |= 4;
    MBModelBillboardSet(model);
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x4F) {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 15.0f;
    } else {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z + 30.0f);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 35.0f;
    }

    obj = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(obj, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(obj, 15.0f);
    Hu3DModelCameraSet(obj, HU3D_CAM0);
    EffectPosSet(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        EffectRangeSet(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        EffectRangeSet(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    EffectRangeSet(obj, scale * 15.0f);
    HuPrcSleep(20);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    HuVecCopyXYZ(&camPos, player->player_obj->coords.x, player->player_obj->coords.y - 10.0f, player->player_obj->coords.z);
    MBPlayerPosMoveCreate(&model->coords, &camPos, &model->coords, 40);

    for (i = 0; i < 40; i++) {
        HuMtxRotYF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        scale -= 0.05f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        EffectRangeSet(obj, scale * 15.0f);
        EffectPosSet(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(model);
    EffectStop(obj);
    MBVecForwardSet(&player->player_obj->rot);
    MBPlayerVibrate(-1, 5);
    if (mb5ev_starGetTeresaF != 0) {
        HuAudSeqVolFadeOut(0xE);
    } else {
        HuAudSeqPlay(0x6F);
    }

    GwPlayer[GwSystem.current_player_index].star += 1;
    if (GwPlayer[GwSystem.current_player_index].star >= 100) {
        GwPlayer[GwSystem.current_player_index].star = 99;
    }

    MBPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x262, GwSystem.current_player_index);
    if (mb5ev_starGetTeresaF != 0) {
        HuPrcSleep(16);
        msmMusPause(HuAudMusNo);
        HuAudSubSeqPlayMute(0x6F);
        HuAudSubSeqVolFadeIn(0);
        HuPrcSleep(110);
        msmMusResume(HuAudMusNo, 0);
        HuAudSeqVolFadeIn(0xF);
    } else {
        HuPrcSleep(60);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_StarGetExec(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(MB5Ev_StarGet, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void MB5_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MB5_MapScrollCancel(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void MB5_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mb5_branchStickHelp = MBHelpWinCreate(0, 0x92, 1);
    mb5_branchBtnHelp = MBHelpWinCreate(1, 0xA0, 1);
    mb5_branchItemHelp = MBHelpWinCreate(0xD, 0xAE, 1);
    mb5_branchMapScrollHelp = MBHelpWinCreate(3, 0xBC, 1);
    mb5_branchMapOverheadHelp = MBHelpWinCreate(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MB5_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBHelpWinKill(mb5_branchStickHelp);
    MBHelpWinKill(mb5_branchBtnHelp);
    MBHelpWinKill(mb5_branchItemHelp);
    MBHelpWinKill(mb5_branchMapScrollHelp);
    MBHelpWinKill(mb5_branchMapOverheadHelp);
}

// Keep rodata definitions interleaved with functions to preserve the original constant order.
const u8 mb5_padBitTbl[4] = { 1, 2, 4, 8 };

s32 MB5_ComShopItemChoice(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb5_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = MB5_ComShopItemDecide();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < 9; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
    } while (arg0[i] == 0);
    return i;
}

s32 MB5_ComShopEnterChoice(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb5_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches MBKettouTargetChoiceGet
                var_s2 = MB5_ComShopEnterDecide();
                sp18[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void MB5_ComTeresaTypeDecide(void) {
    s32 i;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != 4) {
        if (GwPlayer[cur].coin >= 50) {
            if (MBRand(100.0f) < GwPlayer[cur].coin + 10) {
                mb5_comTeresaType = 1;
                if (GwPlayer[cur].star < 99) {
                    return;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != 4) {
        mb5_comTeresaType = 0;
    } else {
        mb5_comTeresaType = 2;
    }
}

void MB5_ComTeresaTargetDecide(void) {
    s32 order[4];
    s32 i;
    s32 j;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        order[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        j = MBPlayerStealRankGet(i);
        while (1) {
            if (order[j] == -1) {
                break;
            }
            j++;
        }
        order[j] = i;
    }
    MB5_ComTeresaTypeDecide();
    if (mb5_comTeresaType == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                mb5_comTeresaTarget = order[i];
                break;
            }
        }
    } else if (mb5_comTeresaType == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                mb5_comTeresaTarget = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        mb5_comTeresaType = 2;
    }
}

s32 MB5_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb5_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    MB5_ComTeresaTargetDecide();
                    var_s2 = mb5_comTeresaType + 1;
                } else {
                    var_s2 = mb5_comTeresaTarget + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    while (1) {
        i = HuWinChoiceGet(mbDlgWinId, i, arg2);
        if (arg2 == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (arg0[i] != 0) {
            return i;
        }
    }
}

s32 MB5_ComTeresaTypeChoice(u8 *arg0) {
    return MB5_ComTeresaChoice(arg0, 0, 1);
}

s32 MB5_ComTeresaPlayerChoice(u8 *arg0) {
    return MB5_ComTeresaChoice(arg0, 1, 0);
}

void MB5_BoardInit(void) {
    GwSystem.current_board_index = 4;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(boardcall, 0, 0x192);
}

void MB5_SaveInit(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    MB5Ev_StarShuffle();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    MB5_WhompItemShuffle();
    GwSystem.boardData.halfWordBytes[3] = 0;
    GwSystem.boardData.halfWordBytes[4] = 1;
    omOvlReturnEx(1);
}

void MB5_ObjectSetup(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(0xF, 0x23E, 0x11, 0);
    MBMasuBlockTblExtSet(mb5_masuBlockExtTbl);
    MBMasuBlockTblSet(mb5_masuBlockTbl);
    MBMasuArrowAngleAdd(0.0f);
    space = MBMasuGet(0x93);
    MBVecDirGet(&space->coords, &MBMasuGet(0x94)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBMasuArrowAngleAdd(0.0f);
    MBMasuArrowAngleAdd(0.0f);
    space = MBMasuGet(0x76);
    MBVecDirGet(&space->coords, &MBMasuGet(0x77)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBMasuArrowAngleAdd(0.0f);
    MBItemHookSet(0, &MB5Ev_Teresa);
    MBItemHookSet(1, &MB5Ev_ItemMajinLamp);
    MBItemHookSet(9, &MB5Ev_ItemMajinLampStar);
    MBItemHookSet(2, &MB5Ev_ItemWarpBlock);
    MBItemHookSet(3, &MB5Ev_ItemRobBox);
    MBItemHookSet(4, &MB5Ev_KSuitStart);
    MBItemHookSet(5, &MB5Ev_KSuitEnd);
    MBItemHookSet(6, &MB5Ev_ItemKinoko);
    MBItemHookSet(7, &MB5Ev_ItemShake);
    MBItemHookSet(8, &MB5Ev_ItemPhoneMove);
    MBItemHookSet(0xA, &MB5Ev_ItemNKinoko);
    MBItemHookSet(0xB, &MB5Ev_ItemRKinoko);
    MBItemHookSet(0xE, &MB5Ev_ItemShopPhone);
    MBItemHookSet(0xF, &MB5Ev_ItemKoopaPhone);
    MBItemHookSet(0x10, &MB5Ev_ItemStarYoke);
    MBItemHookSet(0x11, &MB5Ev_ItemKeyManUse);
    MBItemHookSet(0x12, &MB5Ev_ItemNullUse);
    MBItemHookSet(0x13, &MB5Ev_ItemExchangeBox);
    MBItemHookSet(0x14, &MB5Ev_ItemGambleCoin);
    MBItemHookSet(0x15, &MB5Ev_ItemAfter5);
    MBItemHookSet(0xC, &MB5Ev_ItemKoopaNKinoko);
    MBItemHookSet(0xD, &MB5Ev_ItemKoopaRKinoko);
    MBComItemDecideHookSet(MB5_ComItemDecide);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, mb5ev_starGuideMasu[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        MB5Ev_StarNextPos();
    }

    MB5Ev_StarMasuInit();
    MB5_StarGuideCreateAll();
    MB5_TeresaGuideCreateAll();
    MB5_BankCoinCreateAll();
    MB5_GateCreateAll();
    MB5_BankMapIconAddAll();
    MB5_ShopMapIconAddAll();
    MB5Ev_KinokoMarkCreateAll();
    MBMasuTypeListCreate();
    omAddPrcObj(MB5_WhompProc, 0x4800, 0, 0);
    omAddPrcObj(MB5_CartBlockProc, 0x4800, 0, 0);
}

void MB5_Create(void) {
    HuAudSeqPlay(0x1C);
    mbBoardMusId = 0x1C;
    MBBoardParamSet(0x1C);
    Hu3DCamInit(2);
    MB5_ObjectSetup();
    MBMasuEventTblAdd(mb5_commonEventTbl);
    MBMasuEventTblAdd(mb5_specialEventTbl);
    MBHatenaFuncSet(&MB5Ev_Hatena);
    MBMasuEventTblAdd(mb5_teresaEventTbl);
    MBMasuEventTblAdd(mb5_turnStatusEventTbl);
    MBStart(0);
}

void MB5_BoardReload(void) {
    Hu3DCamInit(1);
    MB5_ObjectSetup();
    MBStart(1);
}

void MB5_StarGuideCreate(s16 arg0) {
    Object *obj;

    if (mb5_starGuideMdl[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    AuraCreate(obj->omObj1->model[0]);
    if (mb5_starGuideBaseMdl == NULL) {
        mb5_starGuideBaseMdl = obj;
    }
    mb5_starGuideMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    mb5_starGuideHoverProc[arg0] = MBModelHoverCreate(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb5_starGuideMdlMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xB, obj, mb5_starGuideMapIconOfsTbl[arg0][0], mb5_starGuideMapIconOfsTbl[arg0][1]);
}

void MB5_StarGuideKill(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (mb5_starGuideHoverProc[i] != NULL) {
            omDelPrcObj(mb5_starGuideHoverProc[i]);
            mb5_starGuideHoverProc[i] = NULL;
        }
    }
}

void MB5_StarGuideCreateAll(void) {
    s32 i;

    mb5_starGuideBaseMdl = 0;
    for (i = 0; i < 8; i++) {
        mb5_starGuideMdl[i] = 0;
        mb5_starGuideHoverProc[i] = NULL;
        MBKinokoEffKillHookSet(MB5_StarGuideKill);
        if (!GWBoardFlagCheck(mb5_starGuideFlagTbl[i])) {
            MB5_StarGuideCreate(i);
        }
    }
}

void MB5_TeresaGuideCreate(s16 arg0) {
    Object *obj;

    if (mb5_teresaGuideMdl[arg0] != NULL) {
        return;
    }
    if (mb5_teresaGuideBaseMdl == NULL) {
        obj = MBModelCreate(0xA, NULL);
        Hu3DModelTPLvlInit(obj->omObj1->model[0]);
        Hu3DModelTPLvlInit(obj->omObj2->model[0]);
        mb5_teresaGuideBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb5_teresaGuideBaseMdl);
    }
    MBModelDispOff(obj);
    mb5_teresaGuideMdl[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb5_teresaGuideMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xA, obj, mb5_teresaGuideMapIconOfsTbl[arg0][0], mb5_teresaGuideMapIconOfsTbl[arg0][1]);
}

void MB5_TeresaGuideCreateAll(void) {
    s32 i;

    mb5_teresaGuideBaseMdl = 0;
    for (i = 0; i <= 0; i++) {
        mb5_teresaGuideMdl[i] = NULL;
        MB5_TeresaGuideCreate(i);
    }
}

void MB5_BankCoinHide(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(mb5_bankCoinMdl[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(mb5_bankCoinMdl[i * 5 + j]);
        }
    }
}

void MB5_BankCoinCreate(s16 arg0) {
    Object *obj;

    if (mb5_bankCoinMdl[arg0] != NULL) {
        return;
    }
    if (mb5_bankCoinBaseMdl == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        mb5_bankCoinBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb5_bankCoinBaseMdl);
    }
    mb5_bankCoinMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb5_bankCoinMasuTbl[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &mb5_bankCoinOfsTbl[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = mb5_bankCoinRotTbl[arg0 % 5].x;
    obj->omObj1->rot.z = mb5_bankCoinRotTbl[arg0 % 5].z;
    MBModelDispOff(obj);
}

void MB5_BankCoinCreateAll(void) {
    s32 i;

    mb5_bankCoinBaseMdl = 0;
    for (i = 0; i < 0xA; i++) {
        mb5_bankCoinMdl[i] = NULL;
        MB5_BankCoinCreate(i);
    }
    MB5_BankCoinHide();
}

void MB5_GateCreate(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (mb5_gateMdl[arg0] != NULL) {
        return;
    }
    if (mb5_gateBaseMdl == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(mb5_gateMdlTbl[board], mb5_gateMotTbl[board]);
        MBModelTempAllocFree(obj);
        mb5_gateBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb5_gateBaseMdl);
    }
    mb5_gateMdl[arg0] = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb5_gateMasuTbl[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(mb5_gateDirMasuTbl[arg0][0]);
        SpaceData *masuB = MBMasuGet(mb5_gateDirMasuTbl[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    MBMapFullIconMdlAdd(0xC, obj, mb5_gateMapIconOfsTbl[arg0][0], mb5_gateMapIconOfsTbl[arg0][1]);
}

void MB5_GateCreateAll(void) {
    s32 i;

    mb5_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        mb5_gateMdl[i] = NULL;
        MB5_GateCreate(i);
    }
}

void MB5_GateOpenSeProc(void) {
    HuPrcSleep(mb5_gateOpenDelayTbl[GwSystem.current_board_index]);
    HuAudFXPlay((s16)mb5_gateOpenDelaySeTbl[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void MB5_GateOpen(s32 arg0, s32 arg1) {
    MBMotionSet(mb5_gateMdl[arg0], arg1 - 1, 0);
    Hu3DMotionAttrSet(mb5_gateMdl[arg0]->omObj1->model[0], 5, 0);
    if (mb5_gateOpenSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb5_gateOpenSeTbl[GwSystem.current_board_index]);
    }

    if (mb5_gateOpenDelaySeTbl[GwSystem.current_board_index] != -1) {
        omAddPrcObj(MB5_GateOpenSeProc, 0x1000, 0, 0);
    }
}

void MB5_GateCloseProc(void) {
    s32 index;
    s32 sleep;

    index = (s32)HuPrcCurrentGet()->user_data;

    switch (GwSystem.walk_speed) {
        case 0:
            sleep = 5;
            break;
        case 1:
            sleep = 10;
            break;
        default:
            sleep = 15;
            break;
    }

    HuPrcSleep(sleep);
    Hu3DMotionAttrSet(mb5_gateMdl[index]->omObj1->model[0], 1, 4);

    if (mb5_gateCloseSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb5_gateCloseSeTbl[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void MB5_GateClose(s32 arg) {
    Process *prc = omAddPrcObj(MB5_GateCloseProc, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB5_BankMapIconAddAll(void) {
    s32 i;

    mb5_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(8, &MBMasuGet(mb5_bankMapIconMasuTbl[i])->coords,
                                   mb5_bankMapIconOfsTbl[i][0], mb5_bankMapIconOfsTbl[i][1]);
    }
}

void MB5_ShopMapIconAddAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(9, &MBMasuGet(mb5_shopMapIconMasuTbl[i])->coords,
                                   mb5_shopMapIconOfsTbl[i][0], mb5_shopMapIconOfsTbl[i][1]);
    }
}

s32 MB5_ComWhompItemCheck(void) {
    s32 result = 1;
    s32 i;

    for (i = 0; i < 3; i++) {
        s32 item = GwPlayer[GwSystem.current_player_index].itemNo[i];

        switch (GwSystem.boardData.halfWordBytes[2]) {
            case 0:
                result *= (item != 1);
                break;
            case 1:
                result *= (item != 0);
                break;
            case 2:
                result *= (item != 2);
                break;
        }
    }
    return result;
}

void MB5Ev_BranchMerge(s32 masuId, s32 link, s32 idx) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == masuId) {
        MBMoveNextMasuSet(-1, link, idx);
    }
}

void MB5Ev_BranchRKinokoMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB5Ev_BranchMain(masu, links, trees);
    }
}

void MB5Ev_Branch1(void) {
    MBMoveNextMasuSet(-1, 1, 2);
}

void MB5Ev_Branch1Rev(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6C) {
        MBMoveBackMasuSet(-1, 1, 2);
    }
}

void MB5Ev_Branch2(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 3, 0);
        player->rev &= ~1;
    } else {
        MB5Ev_BranchMain(mb5ev_branch2Masu, mb5ev_branch2Link, mb5ev_branch2ComTree);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_Branch3(void) {
    MB5Ev_BranchMain(mb5ev_branch3Masu, mb5ev_branch3Link, mb5ev_branch3ComTree);
    omDelPrcObj(NULL);
}

void MB5Ev_Branch4(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8D) {
        MB5Ev_WhompExec();
    } else {
        MB5Ev_BranchMain(mb5ev_branch4Masu, mb5ev_branch4Link, mb5ev_branch4ComTree);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_Branch5(void) {
    MB5Ev_BranchMain(mb5ev_branch5Masu, mb5ev_branch5Link, mb5ev_branch5ComTree);
    omDelPrcObj(NULL);
}

void MB5Ev_Branch6(void) {
    MB5Ev_BranchMain(mb5ev_branch6Masu, mb5ev_branch6Link, mb5ev_branch6ComTree);
    omDelPrcObj(NULL);
}

void MB5Ev_Branch7(void) {
    MB5Ev_BranchMain(mb5ev_branch7Masu, mb5ev_branch7Link, mb5ev_branch7ComTree);
    omDelPrcObj(NULL);
}

void MB5Ev_Branch8(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x61 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 15, 0);
        player->rev &= ~1;
    } else {
        MB5Ev_BranchMain(mb5ev_branch8Masu, mb5ev_branch8Link, mb5ev_branch8ComTree);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_Branch9(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8A) {
        MB5Ev_WhompExec();
    } else {
        MB5Ev_BranchMain(mb5ev_branch9Masu, mb5ev_branch9Link, mb5ev_branch9ComTree);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_Branch10RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch10Masu, mb5ev_branch10Link, mb5ev_branch10ComTree);
}

void MB5Ev_Branch11RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch11Masu, mb5ev_branch11Link, mb5ev_branch11ComTree);
}

void MB5Ev_Branch12RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch12Masu, mb5ev_branch12Link, mb5ev_branch12ComTree);
}

void MB5Ev_Branch13RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch13Masu, mb5ev_branch13Link, mb5ev_branch13ComTree);
}

void MB5Ev_Branch14RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch14Masu, mb5ev_branch14Link, mb5ev_branch14ComTree);
}

void MB5Ev_Branch15RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch15Masu, mb5ev_branch15Link, mb5ev_branch15ComTree);
}

void MB5Ev_Branch16RKinoko(void) {
    MB5Ev_BranchRKinokoMain(mb5ev_branch16Masu, mb5ev_branch16Link, mb5ev_branch16ComTree);
}

void MB5Ev_Merge1(void) {
    MB5Ev_BranchMerge(0x1C, 4, 9);
}

void MB5Ev_Merge2(void) {
    MB5Ev_BranchMerge(0x96, 4, 9);
}

void MB5Ev_Merge3(void) {
    MB5Ev_BranchMerge(0x1F, 3, 0);
}

void MB5Ev_Branch17(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB5Ev_BranchMain(mb5ev_branch17Masu, mb5ev_branch17Link, mb5ev_branch17ComTree);
    } else {
        MB5Ev_BranchMerge(0x58, 1, 9);
    }
}

void MB5Ev_Merge4(void) {
    MB5Ev_BranchMerge(0x23, 3, 4);
}

void MB5Ev_Merge5(void) {
    MB5Ev_BranchMerge(0x8C, 3, 4);
}

void MB5Ev_Merge6(void) {
    MB5Ev_BranchMerge(0x70, 14, 16);
}

void MB5Ev_Merge7(void) {
    MB5Ev_BranchMerge(0x28, 14, 4);
}

void MB5Ev_Merge8(void) {
    MB5Ev_BranchMerge(0x12, 14, 16);
}

void MB5Ev_Merge9(void) {
    MB5Ev_BranchMerge(0x13, 4, 3);
}

void MB5Ev_Merge10(void) {
    MB5Ev_BranchMerge(0x73, 1, 9);
}

void MB5Ev_WhompMasu129Check(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8B) {
        MB5Ev_WhompExec();
    }
}

void MB5Ev_CartRideMerge1(void) {
    MB5Ev_BranchMerge(0x54, 16, 17);
    MB5Ev_CartRide();
}

void MB5Ev_Merge11(void) {
    MB5Ev_BranchMerge(0x56, 16, 4);
}

void MB5Ev_Merge12(void) {
    MB5Ev_BranchMerge(0x38, 16, 17);
}

void MB5Ev_CartRideMerge2(void) {
    MB5Ev_BranchMerge(0x5E, 9, 12);
    MB5Ev_CartRide();
}

void MB5Ev_Merge13(void) {
    MB5Ev_BranchMerge(0x5F, 15, 2);
}

void MB5Ev_Merge14(void) {
    MB5Ev_BranchMerge(0x44, 9, 12);
}

void MB5Ev_Merge15(void) {
    MB5Ev_BranchMerge(0x4A, 11, 6);
}

void MB5Ev_Merge16(void) {
    MB5Ev_BranchMerge(0x8A, 16, 0);
}

void MB5Ev_Merge17(void) {
    MB5Ev_BranchMerge(0x5A, 15, 4);
}

void MB5Ev_Merge18(void) {
    MB5Ev_BranchMerge(0x5C, 9, 4);
}

void MB5Ev_Merge19(void) {
    MB5Ev_BranchMerge(0x87, 11, 6);
}

void MB5Ev_WhompMasu3Check(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu != 0x8C) {
        MB5Ev_WhompExec();
    }
}

void MB5Ev_KeyManMasu(void) {
    s32 moveOn = TRUE;
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    s16 prevMasu;
    s32 choice;
    UnkVibrateProcess *vibrate;

    switch (masu) {
        case 0x74:
        case 0x88:
            prevMasu = MBMasuLinkMasuIdGet(player->blink, player->bidx);
            switch (prevMasu) {
                case 0x75:
                    MBMoveNextMasuSet(-1, 16, 7);
                    goto end;
                case 0x89:
                    MBMoveNextMasuSet(-1, 14, 5);
                    goto end;
            }
            break;
        case 0x73:
        case 0x87:
            prevMasu = MBMasuLinkMasuIdGet(player->blink, player->bidx);
            switch (prevMasu) {
                case 0x75:
                case 0x89:
                    goto end;
            }
            break;
    }

    MBPlayerMotionSet(-1, -1, 2);
    if (MBItemFind(sys->current_player_index, 1) != -1) {
        MBSaiNumKill(sys->current_player_index);
        switch (masu) {
            case 0x73:
            case 0x74:
                MBPlayerRotMasuStart(-1, 8, 0x75);
                break;
            default:
                MBPlayerRotMasuStart(-1, 8, 0x89);
                break;
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        MBPlayerVibrate(-1, 1);
    retry:
        MBDlgWinCreate(0x38, 0x4103);
        choice = MB5Ev_YesNoChoiceGet(2, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                MBDlgWinExec(0x38, 0x4104);
                GwPlayer[sys->current_player_index].itemNo[MBItemFind(sys->current_player_index, 1)] = -1;
                MBItemRemoveEmpty(GwSystem.current_player_index);
                MBStatusItemIconSprReinit(-1);
                switch (masu) {
                    case 0x73:
                        MB5_GateOpen(0, 0);
                        break;
                    case 0x74:
                        MB5_GateOpen(0, 1);
                        break;
                    case 0x87:
                        MB5_GateOpen(1, 0);
                        break;
                    default:
                        MB5_GateOpen(1, 1);
                        break;
                }
                moveOn = FALSE;
                vibrate = MBPlayerVibrateObjCreate(-1, 2, 5);
                HuPrcSleep(20);
                MBPlayerVibrateObjKill(vibrate);
                break;
            case 1:
                MBDlgWinExec(0x38, 0x4105);
                break;
            case 2:
                MB5_MapScroll();
                goto retry;
        }
        MBSaiNumShow(sys->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    } else {
        MBDlgWinExec(-1, 0x4106);
    }

    if (moveOn) {
        switch (masu) {
            case 0x73:
                MBMoveNextMasuSet(-1, 7, 0);
                player->rev |= 1;
                break;
            case 0x74:
                MBMoveNextMasuSet(-1, 16, 7);
                player->rev &= ~1;
                break;
            case 0x87:
                MBMoveNextMasuSet(-1, 13, 0);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 14, 5);
                player->rev &= ~1;
                break;
        }
    }

end:
    omDelPrcObj(NULL);
}

void MB5Ev_BankMasuBranch(void) {
}

void MB5Ev_StarMasuBranch(void) {
}

void MB5Ev_TeresaMasuBranch(void) {
}

s32 MB5Ev_YesNoChoiceGet(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb5_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch (arg0) {
                    case 0:
                        var_s2 = MBPlayerRankRandGet(0) + 1;
                        break;
                    case 1:
                        var_s2 = MBPlayerRankRandGet(1) + 1;
                        break;
                    case 2:
                        var_s2 = arg1 + 1;
                        break;
                    default:
                        var_s2 = MBComTreeExec((void *)arg0) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], MBMesWaitGet());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void MB5Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s16 sp10[2];
    s16 winId;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    winId = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = winId;
    HuWinMesSet(winId, arg1, -1, -1);
    HuWinExAnimIn(winId);
    MBWinIdPlayerKeyWait(winId, arg3);
    HuWinExAnimOut(winId, 0);
    HuWinKill(winId);
}

void MB5Ev_ItemSelAttrProc(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
    }
}

void MB5Ev_StarMasu(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = MB5Ev_StarCheck(spaceIdx);
    if (spaceIdx == 1) {
        MBSaiNumKill(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        MBPlayerRotMasuStart(-1, 8, MB5Ev_StarGuideMasuGet());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuAudFXPlay(0x159);

        if (GwPlayer[loc->current_player_index].itemTurn != 0) {
            MBDlgWinInsertCreate(0x16, 0x4805, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            MBDlgWinMesWait();
            MBDlgWinClose();
            MBDlgWinKill();
        }

        if (GwPlayer[loc->current_player_index].star >= 99) {
            MBDlgWinExec(0x16, 0x4804);
        } else {
            if (GwPlayer[loc->current_player_index].coin >= 20) {
            purchaseMenu:
                MBDlgWinInsertCreate(0x16, 0x4800, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
                choice = MB5Ev_YesNoChoiceGet(2, 0);
                MBDlgWinClose();
                MBDlgWinKill();

                switch (choice) {
                    case 0:
                        MBCoinChangeCreate(loc->current_player_index, -20);
                        MBCoinTakeCreate(loc->current_player_index, -20);
                        HuPrcSleep(30);
                        MBDlgWinExec(0x16, 0x4802);
                        if (mbStarMusF != 0) {
                            HuAudSeqStop();
                            msmMusFadeOut(mbSubMusNo, 60);
                            mbSubMusNo = -1;
                        } else {
                            HuAudSeqFadeOut(0x5A);
                        }
                        MB5Ev_StarGetExec(mb5_starGuideBaseMdl);
                        HuPrcSleep(30);
                        MBBoardRestartSet();
                        MBExitReq(2);
                        MB5Ev_StarMasuBranch();
                        return;
                    case 1:
                        if (mbStarMusF != 0) {
                            msmMusFadeOut(mbSubMusNo, 60);
                            msmMusPlayDefault(mbBoardMusId);
                            HuAudSeqVolFadeOut(0);
                            HuAudSeqVolFadeIn(0x5A);
                            mbSubMusNo = -1;
                        }
                        MBDlgWinExec(0x16, 0x4803);
                        MBSaiNumShow(loc->current_player_index);
                        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                        HuPrcChildWatch();
                        MB5Ev_StarMasuBranch();
                        return;
                    case 2:
                        MB5_MapScroll();
                        goto purchaseMenu;
                    default:
                        MB5Ev_StarMasuBranch();
                        return;
                }
            } else {
                MBDlgWinExec(0x16, 0x4801);
            }
        }

        if (mbStarMusF != 0) {
            msmMusFadeOut(mbSubMusNo, 60);
            msmMusPlayDefault(mbBoardMusId);
            HuAudSeqVolFadeOut(0);
            HuAudSeqVolFadeIn(0x5A);
            mbSubMusNo = -1;
        }

        MBSaiNumShow(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }

    MB5Ev_StarMasuBranch();
}

const char mb5ev_numFmtStr[] = "%d";

void MB5Ev_BankMasu(void) {
    Object *model;
    Object *effectModel;
    SpaceData *spaceA;
    SpaceData *spaceB;
    GW_SYSTEM *sys;
    Vec *vec;
    s16 mgId;
    s32 choice;
    s32 flag;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    char sp20[0x10];
    char sp30[0x10];
    Vec sp40;

    flag = 0;
    mgId = MBMasuCurGet();
    sys = &GwSystem;
    spaceA = NULL;
    spaceB = NULL;
    if (MBSaiValueGet(sys->current_player_index) <= 0) {
        MBPlayerVibrate(-1, 3);
    }
    MBPlayerMotionSet(-1, -1, 2);

    switch (mgId) {
        case 0x21:
            MBPlayerRotMasuStart(-1, 8, 0x6D);
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(0x21);
            break;
        case 0x45:
            MBPlayerRotMasuStart(-1, 8, 0x79);
            spaceA = MBMasuGet(0x79);
            spaceB = MBMasuGet(0x45);
            break;
    }

    HuPrcSleep(8);
    if (MBSaiValueGet(sys->current_player_index) > 0) {
        MBSaiNumKill(sys->current_player_index);
    }
    HuAudFXPlay(0x114);

    model = MBModelCreate(0x32, NULL);
    MBModelTempAllocFree(model);
    vec = &sp40;
    HuVecSubtract(vec, &spaceB->coords, &spaceA->coords);
    MBVecNormalize(vec);
    HuVecCopy3F(&model->rot, vec);
    model->scale.y = 0.0f;
    HuVecCopy3F(&model->coords, &spaceA->coords);
    MBMotionSet(model, -1, 1);
    MBModelDispFlagSet(model);

    effectModel = MBModelCreate(0x35, mb5ev_bankCoinPileMot);
    MBModelTempAllocFree(effectModel);
    HuVecCopy3F(&effectModel->rot, vec);
    HuVecCopy3F(&effectModel->coords, &spaceA->coords);
    effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 0.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    if (50.0f < angle) {
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        do {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
            angle -= scaleStep;
        } while (50.0f < angle);
    }

    model->scale.z = model->scale.x = model->scale.y = 1.0f;
    MBModelDispFlagSet(effectModel);

    if (MBItemFind(-1, 0xF) != -1) {
    dialogLoop:
        MBDlgWinInsertCreate(-1, 0x3A1D, 0, 0, 0, 0, 0);
        choice = MB5Ev_YesNoChoiceGet((s32)mb5ev_bankComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                MB5_MapScroll();
                goto dialogLoop;
        }
    }

    MBMotionSet(model, -1, 0);
    Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
    while (MBMotionCheck(model) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x259);
    MBMotionSet(effectModel, 0, 0);
    while (MBMotionCheck(effectModel) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(effectModel, -1, 2);

    if (flag != 0) {
        sprintf(sp20, mb5ev_numFmtStr, GwSystem.bank_coins);
        if (GwSystem.bank_coins != 0) {
            MBDlgWinInsertCreate(2, 0x3A1E, (s32)sp20, 0, 0, 0, 0);
        } else {
            MBDlgWinInsertCreate(2, 0x3A1F, 0, 0, 0, 0, 0);
        }
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBDlgWinKill();

        if (GwSystem.bank_coins != 0) {
            mbItemBtnF = 0;
            MB5Ev_BankKoopaCardExec();
            mbItemBtnF = 1;
        } else {
            MBDlgWinInsertCreate(2, 0x3A21, 0, 0, 0, 0, 0);
            MBDlgWinMesWait();
            MBDlgWinClose();
            MBDlgWinKill();
            GwPlayer[sys->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
            MBItemRemoveEmpty(sys->current_player_index);
            MBStatusItemIconSprReinit(sys->current_player_index);
        }

        if (MBSaiValueGet(sys->current_player_index) > 0) {
            MBSaiNumShow(sys->current_player_index);
        }
    } else {
        if (MBSaiValueGet(sys->current_player_index) > 0) {
            if ((GwPlayer[sys->current_player_index].coin != 0) && (GwPlayer[sys->current_player_index].coin < 5)) {
                sprintf(sp20, mb5ev_numFmtStr, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, mb5ev_numFmtStr, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                MB5_BankCoinHide();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                MBDlgWinOpen();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, mb5ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, mb5ev_numFmtStr, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                MB5_BankCoinHide();
                MBCoinChangeCreate(sys->current_player_index, -5);
                MBCoinTakeCreate(sys->current_player_index, -5);
                HuPrcSleep(30);
                MBDlgWinOpen();
            }
            MBDlgWinMesWait();
            MBDlgWinClose();
            MBDlgWinKill();
            MBSaiNumShow(sys->current_player_index);
            HuPrcSleep(10);
        } else {
            if (GwSystem.bank_coins != 0) {
                sprintf(sp20, mb5ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinMesWait();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                MB5_BankCoinHide();
                MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
                MBPlayerMotionSet(-1, 5, 0);
                PlayerFXPlay(0x274, sys->current_player_index);
                HuPrcSleep(30);
                MBPlayerMotionSet(-1, -1, 2);
                MBDlgWinOpen();
                MBDlgWinMesWait();
                MBDlgWinClose();
                MBDlgWinKill();
            } else {
                MBDlgWinExec(2, 0x1204);
            }
        }
    }

    HuAudFXPlay(0x115);
    MBMotionSet(model, -1, 4);
    Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
    Hu3DMotionTimeSet(
        model->omObj1->model[0], Hu3DMotion[Hu3DData[model->omObj1->model[0]].motId].unk02);
    while (MBMotionStartCheck(model) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 50.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    angle = 90.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 0.0f;
    for (; scaleLimit < angle; angle -= scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    model->scale.y = 0;
    model->scale.x = 0;
    model->scale.z = 0;
    MBModelKill(model);
    MBModelKill(effectModel);
    MB5Ev_BankMasuBranch();
}

s32 MB5Ev_ShopItemIdxGet(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb5ev_shopItemEnableTbl[i] != 0 && mb5ev_shopItemTbl[mb5ev_shopHostNo][mb5ev_shopItemRow][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 MB5Ev_ShopItemNumGet(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb5ev_shopItemTbl[mb5ev_shopHostNo][mb5ev_shopItemRow][i] == -1) {
            break;
        }
    }
    return i;
}

void MB5Ev_ShopBagBounceProc(void) {
    s32 grp = (s32)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scaleX;

    MBPlayerGet(GwSystem.current_player_index);
    MBPlayerVibrate(-1, 2);
    HuAudFXPlay(0x15A);

    for (angle = 0.0f; angle < 180.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 1.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.5f);
        HuPrcVSleep();
    }

    for (; angle < 360.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MB5Ev_ShopMasu(void) {
    GW_SYSTEM *system = &GwSystem;
    SpaceData *spaceA;
    SpaceData *spaceB;
    Object *model;
    Object *playerObj;
    Unk3 *helpWin;
    void *data;
    Process *prc;
    u8 enabled[9];
    u8 itemFlags[6][4];
    Vec sp48;
    s32 dlgWin;
    s16 shopIdx;
    s32 flag2;
    s32 id;
    s32 slot;
    s32 row;
    s32 row2;
    s32 sel;
    s32 choice;
    s32 count;
    s32 item;
    s8 *itemPtr;
    s8(*shopTable)[5][7];
    s8(*shopItems)[7];
    s32 timer;
    s32 randVal;
    s32 i;
    s32 j;
    s32 grp;
    s32 grp2;
    s16 spriteId;
    s32 spriteId2;
    s16 sprY;
    s16 masuId;
    s16 camMasu;
    GW_PLAYER *player;
    Object *effectModel;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    f32 scale;
    player = MBPlayerGet(-1);
    spaceA = NULL;
    spaceB = NULL;
    model = NULL;
    effectModel = NULL;
    MBPlayerMotionSet(-1, -1, 2);

    masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    switch (masuId) {
        case 0x93:
            camMasu = 0x94;
            spaceA = MBMasuGet(0x94);
            spaceB = MBMasuGet(0x93);
            mb5ev_shopNo = 0;
            break;
        case 0x76:
            camMasu = 0x77;
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x76);
            mb5ev_shopNo = 1;
            break;
        default:
            camMasu = -1;
            break;
    }

    if (camMasu != -1) {
        MBPlayerRotMasuStart(-1, 8, camMasu);
        HuPrcSleep(8);
    }
    MBSaiNumKill(system->current_player_index);

    switch (GwSystem.forceShopHost) {
        case 0:
            shopIdx = !MBRandCheck100(0x42);
            break;
        case 1:
            shopIdx = 0;
            break;
        default:
            shopIdx = 1;
            break;
    }

    dlgWin = 3;
    if (shopIdx != 0) {
        dlgWin = 5;
    }

    if (camMasu != -1) {
        flag2 = (shopIdx << 1) >> 1;
        id = (-shopIdx & 0x31) | 0x30;
        HuAudFXPlay(0x114);
        model = MBModelCreate(id, NULL);
        MBModelTempAllocFree(model);
        HuVecSubtract(&sp48, &spaceB->coords, &spaceA->coords);
        MBVecNormalize(&sp48);
        HuVecCopy3F(&model->rot, &sp48);
        model->scale.y = 0.0f;
        MBMotionSet(model, -1, 1);
        MBModelDispFlagSet(model);
        HuVecCopy3F(&model->coords, &spaceA->coords);

        if (flag2 != 0) {
            effectModel = MBModelCreate(0x39, mb5ev_shopKoopaJrMot);
        } else {
            effectModel = MBModelCreate(0x1B, mb5ev_shopKinopioMot);
        }
        MBModelTempAllocFree(effectModel);
        HuVecCopy3F(&effectModel->rot, &sp48);
        HuVecCopy3F(&effectModel->coords, &spaceA->coords);
        effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 0.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        for (; 50.0f < angle; angle -= scaleStep) {
            scaleK = 0.2f;
            scaleBase = 0.8f;
            scaleStep = 11.25f;
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = model->scale.x = model->scale.z = 1.0f;
        MBModelDispFlagSet(effectModel);
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, 0, 0);

        if (shopIdx != 0) {
            HuAudFXPlay(0x2A0);
        } else {
            if (GwPlayer[system->current_player_index].coin < 5 || MBItemFindEmpty(system->current_player_index) == -1) {
                HuAudFXPlay(0x29A);
            } else if (system->current_turn != system->total_turns) {
                HuAudFXPlay(0x298);
            } else {
                HuAudFXPlay(0x29A);
            }
        }

        while (MBMotionCheck(effectModel) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, -1, 2);
    }

    if (system->current_turn == system->total_turns) {
        MBDlgWinExec(dlgWin, mb5ev_shopLastTurnMesTbl[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, mb5ev_shopItemFullMesTbl[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, mb5ev_shopNoCoinMesTbl[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, mb5ev_shopEnterMesTbl[shopIdx]);
    choice = MB5_ComShopEnterChoice();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = MBTurnTierGet(-1);
            row = mb5ev_shopItemRowTbl[shopIdx][i][MBPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (mb5ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mb5ev_shopItemTbl[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (mb5ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mbItemPriceTbl[mb5ev_shopItemTbl[shopIdx][row][j]] >
                    GwPlayer[system->current_player_index].coin) {
                    enabled[j] = 0;
                    itemFlags[i][0] = 1;
                }
                itemFlags[i][1] = 0;
                count++;
            }
            for (; j < 9; j++) {
                enabled[j] = 1;
            }

            MBDlgWinInsertCreate(dlgWin, mb5ev_shopItemMesTbl[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            MBDlgWinTabWidthSet(0);
            mb5ev_shopHostNo = slot;
            mb5ev_shopItemRow = row;
            mb5ev_shopItemEnableTbl = enabled;
            sel = MB5_ComShopItemChoice(enabled);
            MBDlgWinClose();
            MBDlgWinKill();

            if (sel == count) {
                mbItemBtnF = 0;
                MBItemSelNoClear();
                MBItemDescExec(system->current_player_index);
                mbItemBtnF = 1;
                goto restart;
            }
            if (sel == count + 1 || sel == -1) {
                goto itemSelect;
            }

            playerObj = player->player_obj;
            i = shopIdx;
            shopTable = mb5ev_shopItemTbl;
            shopItems = shopTable[i];
            itemPtr = (s8 *)(row * 7);
            itemPtr += (s32)shopItems;
            itemPtr += sel;
            MBCoinChangeCreate(system->current_player_index, -mbItemPriceTbl[*itemPtr]);
            MBCoinTakeCreate(system->current_player_index, -mbItemPriceTbl[*itemPtr]);
            HuPrcSleep(30);

            if (*itemPtr == 0x13) {
                item = i + 0x13;
            } else {
                GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] =
                    mb5ev_shopItemTbl[shopIdx][row][sel];
                item = mb5ev_shopItemTbl[shopIdx][row][sel];
            }

            grp = HuSprGrpCreate(1, 5);
            i = 0;
            data = DataRead(mbItemIconSprTbl[item]);
            spriteId = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(grp, 0, spriteId, 0);
            HuSprPriSet(grp, 0, 0xA);
            HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
            HuSprAttrSet(grp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
            HuSprPosSet(grp, 0, 0xA0, 0x5A);
            HuSprTPLvlSet(grp, 0, 0);
            MBVecForwardSet(&sp48);
            MBVecRotLerpCreate(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);
            HuAudFXPlay(0x19);
            for (; i < 10; i++) {
                HuSprTPLvlSet(grp, 0, i * 25);
                HuPrcVSleep();
            }
            HuSprTPLvlSet(grp, 0, 0x100);

            if (mb5ev_shopItemTbl[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = mb5ev_shopBagRowTbl[shopIdx][MBTurnTierGet(-1)]
                                         [MBPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < mb5ev_shopBagRateTbl[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = mb5ev_shopBagItemTbl[shopIdx][i];

                    if (camMasu != -1) {
                        helpWin = MBHelpWinCreate(0x15, 0xA0, 1);
                    } else {
                        playerObj->flags |= 0x10;
                        helpWin = MBHelpWinCreate(0x15, 0xA0, 0);
                    }
                    timer = 30;

                    if ((*(u16 *)((u8 *)ContBtnDown + (GwPlayer[system->current_player_index].pad << 1)) & A_BUTTON) == 0) {
                        row = (s32)ContBtnDown;
                        while (1) {
                            if (MBPlayerComCheck(-1) != 0) {
                                timer--;
                                if (timer == -1) {
                                    break;
                                }
                            }
                            HuPrcVSleep();
                            if (((u16 *)row)[GwPlayer[system->current_player_index].pad] & 0x8000) {
                                break;
                            }
                        }
                    }
                    MBHelpWinKill(helpWin);

                    MBPlayerMotionSet(system->current_player_index, 2, 0);
                    MBModelJumpSet(playerObj, 2.0f, -0.3f);
                    HuPrcSleep(5);
                    prc = omAddPrcObj(MB5Ev_ShopBagBounceProc, 0x4002, 0, 0);
                    prc->user_data = (void *)grp;
                    MBModelJumpWait(playerObj);
                    MBPlayerMotionSet(-1, -1, 2);

                    grp2 = HuSprGrpCreate(1, 5);
                    i = 0;
                    data = DataRead(mbItemIconSprTbl[item]);
                    spriteId2 = HuSprAnimRead(data);
                    DataClose(data);
                    HuSprGrpMemberSet(grp2, 0, spriteId2, 0);
                    HuSprPriSet(grp2, 0, 0xB);
                    HuSprAnimModeSet(grp2, 0, HUSPR_ANIM_MODE_STOP);
                    HuSprAttrSet(grp2, 0, HUSPR_ATTR_XLU);
                    HuSprPosSet(grp2, 0, 0xA0, 0x5A);
                    HuSprTPLvlSet(grp2, 0, 0);
                    MBVecForwardSet(&sp48);
                    MBVecRotLerpCreate(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);

                    sprY = 0x5A;
                    scale = 0.0f;
                    do {
                        HuSprPosSet(grp2, 0, 0xA0, sprY);
                        HuSprTPLvlSet(grp2, 0, i * 25);
                        HuSprScaleSet(grp2, 0, scale, scale);
                        i++;
                        HuPrcVSleep();
                        sprY -= 3;
                        scale += 0.1f;
                    } while (i < 10);
                    HuSprScaleSet(grp2, 0, 1.0f, 1.0f);
                    HuSprTPLvlSet(grp2, 0, 0x100);
                    HuPrcSleep(10);
                    GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] = item;
                    HuSprGrpKill(grp2);
                    HuSprAnimKill(spriteId2);
                }
                if (camMasu == -1) {
                    playerObj->flags &= ~0x10;
                }
            }

            HuPrcSleep(5);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, system->current_player_index);
            HuPrcSleep(20);
            HuPrcVSleep();
            MBPlayerMotionShiftSet(-1, -1, 0, 5, 2);
            HuPrcSleep(10);
            HuSprGrpKill(grp);
            HuSprAnimKill(spriteId);
            break;
        case 1:
            MBDlgWinExec(dlgWin, mb5ev_shopCancelMesTbl[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                MB5_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB5_MapScroll();
            }
            goto itemSelect;
    }

end:
    if (camMasu != -1) {
        HuAudFXPlay(0x115);
        MBMotionSet(model, -1, 4);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        Hu3DMotionTimeSet(
            model->omObj1->model[0], Hu3DMotion[Hu3DData[model->omObj1->model[0]].motId].unk02);
        while (MBMotionStartCheck(model) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 50.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        angle = 90.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 0.0f;
        for (; scaleLimit < angle; angle -= scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = 0;
        model->scale.x = 0;
        model->scale.z = 0;
        MBModelKill(model);
        MBModelKill(effectModel);
    }
    MBSaiNumShow(system->current_player_index);
    HuPrcSleep(10);
}

void MB5Ev_TeresaFadeIn(Object *obj) {
    s32 i;

    MBModelDispOn(obj);
    for (i = 0; i < 0x100; i += 0xC) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0xFF);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0xFF);
}

void MB5Ev_TeresaFadeOut(Object *obj) {
    s32 i;

    for (i = 0xFF; i >= 0; i -= 0xC) {
        Hu3DModelTPLvlSet(obj->omObj1->model[0], i);
        Hu3DModelTPLvlSet(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0);
    MBModelDispOff(obj);
}

s32 MB5Ev_TeresaStarSteal(s32 playerIndex) {
    s32 hasRareItem = 0;
    s16 grp;
    void *data;
    s16 spriteId;
    s32 i;
    s32 duration;
    Process *process;

    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAttrSet(grp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(grp, 0, mb5ev_teresaSprPosTbl[playerIndex].x,
                mb5ev_teresaSprPosTbl[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        HuSprPosSet(grp, 0,
                    (i * mb5ev_teresaSprDirTbl[playerIndex].x) +
                        mb5ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                        mb5ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(MB5Ev_TereYokeSprayProc, 0x4002, 0, 0);
        process->user_data = (void *)playerIndex;
    }

    if (!hasRareItem) {
        GwPlayer[playerIndex].star--;
    }
    MBPlayerVibrate(playerIndex, 5);
    HuAudFXPlay(0x257);

    duration = hasRareItem ? 0x78 : 0x1E;
    for (i = 0; i < duration; i++) {
        HuSprPosSet(grp, 0,
                    (mb5ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].x,
                    (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].y +
                        (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        HuSprPosSet(grp, 0,
                    (i * mb5ev_teresaSprDirTbl[playerIndex].x) +
                        mb5ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                        mb5ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    return !hasRareItem;
}

void MB5Ev_TeresaWinCloseProc(void) {
    MBWinClose();
    omDelPrcObj(NULL);
}

s32 MB5Ev_TeresaSteal(s32 playerIndex) {
    s32 hasRareItem;
    s16 grp;
    void *data;
    s16 spriteId;
    s16 playerGrp;
    s16 playerSpriteId;
    s32 i;
    s32 state;
    s32 playerSpriteVisible;
    s16 delay;
    s32 angle;
    s32 attempts;
    void *dialog;
    Process *process;

    hasRareItem = 0;
    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAttrSet(grp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(grp, 0, mb5ev_teresaSprPosTbl[playerIndex].x,
                mb5ev_teresaSprPosTbl[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);

    {
        playerGrp = HuSprGrpCreate(1, 5);
        playerSpriteVisible = 0;
        data = DataRead(mbItemCharSprTbl[GwPlayer[playerIndex].chr]);
        playerSpriteId = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(playerGrp, 0, playerSpriteId, 0);
        HuSprPriSet(playerGrp, 0, 0xA);
        HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
        if (playerIndex & 1) {
            HuSprAttrSet(playerGrp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FLIPX);
        } else {
            HuSprAttrSet(playerGrp, 0, HUSPR_ATTR_XLU);
        }
        if (MBItemFind(playerIndex, 0xC) != -1) {
            HuSprDispOff(playerGrp, 0);
        }
        HuSprPosSet(playerGrp, 0,
                    mb5ev_teresaSprPosTbl[playerIndex].x -
                        (mb5ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    mb5ev_teresaSprPosTbl[playerIndex].y +
                        (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f));
        HuSprTPLvlSet(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            HuSprPosSet(grp, 0,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].x) +
                            mb5ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                            mb5ev_teresaSprPosTbl[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
        HuSprTPLvlSet(grp, 0, 0xFF);
        HuSprTPLvlSet(playerGrp, 0, 0xFF);

        MBWinInsertOpen(MBItemFind(playerIndex, 0xC) == -1 ? 0x620E : 0x620F,
                        (char *)mbCharNameMesTbl[GwPlayer[playerIndex].chr], 0, 0, 0, 0);
        MBPlayerVibrate(playerIndex, 2);
        MBWinKeyWait(playerIndex);
        if (MBItemFind(playerIndex, 0xC) != -1) {
            omAddPrcObj(MB5Ev_TeresaWinCloseProc, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(MB5Ev_TereYokeSprayProc, 0x4002, 0, 0);
            process->user_data = (void *)playerIndex;
        }
        HuAudFXPlay(0x133);
        dialog = MBPlayerVibrateObjCreate(playerIndex, 3, 5);
        delay = MBRand(10.0f) + 1;
        i = 0;
        angle = 0;

        for (; i < 0x78; i++, delay--) {
            if (delay == 0) {
                HuAudFXPlay(0x257);
                delay = MBRand(15.0f) + 0x1E;
            }
            state -= !(state < 2);
            if (state == 0) {
                HuSprPosSet(
                    grp, 0,
                    (mb5ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].x,
                    (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                HuSprPosSet(
                    grp, 0,
                    (mb5ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].y);
                HuSprPosSet(
                    playerGrp, 0,
                    mb5ev_teresaSprPosTbl[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].y);
                angle++;
            }

            if (GwPlayer[playerIndex].stat & 1) {
                if (state == 0) {
                    goto tryInput;
                } else {
                    if (GwPlayer[playerIndex].cpu_difficulty == 0) {
                        if ((6 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 1) {
                        if ((7 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 2) {
                        if ((8 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if ((9 - MBRand(2.0f)) >= state) {
                        goto tryInput;
                    }
                }
            } else if (ContBtnDown[GwPlayer[playerIndex].pad] & A_BUTTON) {
            tryInput:
                if (!hasRareItem) {
                    attempts++;
                    state = 10;
                    if (!playerSpriteVisible) {
                        HuSprBankSet(playerGrp, 0, 1, 0);
                        HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
                        playerSpriteVisible = 1;
                        HuSprPosSet(
                            playerGrp, 0, mb5ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                            (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                                mb5ev_teresaSprPosTbl[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                HuSprBankSet(playerGrp, 0, 0, 0);
                HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
                playerSpriteVisible = 0;
                HuSprPosSet(
                    playerGrp, 0,
                    mb5ev_teresaSprPosTbl[playerIndex].x -
                        (mb5ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    (mb5ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb5ev_teresaSprPosTbl[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(MB5Ev_TeresaWinCloseProc, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].x) +
                            mb5ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                            mb5ev_teresaSprPosTbl[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].x) +
                            mb5ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                            mb5ev_teresaSprPosTbl[playerIndex].y);
            HuSprPosSet(playerGrp, 0,
                        ((i - 0x10) * mb5ev_teresaSprDirTbl[playerIndex].x) +
                            mb5ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                        (i * mb5ev_teresaSprDirTbl[playerIndex].y) +
                            mb5ev_teresaSprPosTbl[playerIndex].y);
            if (hasRareItem) {
                i -= 2;
            }
            HuPrcVSleep();
        }
        HuSprBankSet(playerGrp, 0, 0, 0);
        HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprTPLvlSet(grp, 0, i << 4);
            HuPrcVSleep();
        }
    }

    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    HuSprGrpKill(playerGrp);
    HuSprAnimKill(playerSpriteId);

    playerSpriteVisible = -2;
    if (!hasRareItem) {
        for (i = 0; i < ARRAY_COUNTU(mb5ev_teresaCoinTurnTbl); i++) {
            if ((GwSystem.current_turn >= mb5ev_teresaCoinTurnTbl[i][0]) &&
                (GwSystem.current_turn <= mb5ev_teresaCoinTurnTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible = mb5ev_teresaCoinTurnTbl[i][2];
        for (i = 0; i < ARRAY_COUNTU(mb5ev_teresaCoinPenaltyTbl); i++) {
            if ((attempts >= mb5ev_teresaCoinPenaltyTbl[i][0]) &&
                (attempts <= mb5ev_teresaCoinPenaltyTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= mb5ev_teresaCoinPenaltyTbl[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void MB5Ev_TeresaCoin(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb5ev_teresaCoinMdl);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        HuMtxRotYF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void MB5Ev_TeresaCoinCreate(s32 arg) {
    Process *prc = omAddPrcObj(MB5Ev_TeresaCoin, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB5Ev_Teresa(void) {
    char inserts[4][16];
    u8 choices[8];
    Vec direction;
    s32 rankedPlayers[3];
    Object *model = NULL;
    SpaceData *space;
    Vec *spaceCoords;
    GW_PLAYER *player;
    GW_SYSTEM *sys;
    Process *process;
    void *coinEffect;
    s32 resultAmount;
    s32 selectedByCpu;
    s16 target;
    s32 menuResult;
    s32 playerChoice;
    s32 rank;
    s32 count;
    s32 i;
    s32 j;
    s32 amountDifference;
    s16 spaceId;
    f32 angle;
    f32 scale;
    f32 rate;
    f32 booVelocity;
    Object *boo;
    s32 modelIsLinked;
    s32 estimatedAmount;
    s16 camMasu;
    s16 menu;
    s32 cameraSet;

    resultAmount = 0;
    estimatedAmount = resultAmount;
    MBMasuCurGet();
    sys = &GwSystem;
    player = MBPlayerGet(-1);
    cameraSet = MBSaiNumKill(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    menu = 0;
    spaceId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    if (spaceId != 0x4F) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(mb5_teresaGuideBaseMdl);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x63;
        space = MBMasuGet(0x63);
        boo = mb5_teresaGuideMdl[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            Hu3DModelFaceFlip(model->omObj1->model[0]);
        }
        Hu3DModelRemakeStatic(model->omObj1->model[0]);
        MBModelTempAllocFree(model);
        spaceCoords = &space->coords;
        HuVecSubtract(&direction, &MBMasuGet(spaceId)->coords, spaceCoords);
        MBVecNormalize(&direction);
        HuVecCopy3F(&model->rot, &direction);
        model->scale.y = 0.0f;
        HuVecCopy3F(&model->coords, spaceCoords);
        MBMotionSet(model, -1, 1);
        MBModelDispOn(model);
        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    MB5Ev_TeresaFadeIn(boo);
    space = MBMasuGet(spaceId);
    spaceId = camMasu;
    if (spaceId != -1) {
        MBModelTurnCreate(boo, &space->coords, 5);
        MBPlayerRotMasuStart(-1, 5, spaceId);
        HuPrcSleep(5);
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
    }

    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(7, 0x6201);
        goto finishMenu;
    }

restartMenu:
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index &&
            (GwPlayer[i].coin != 0 || GwPlayer[i].star != 0)) {
            break;
        }
    }
    if (i >= 4) {
        MBDlgWinExec(7, 0x6202);
        goto finishMenu;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].coin != 0) {
            break;
        }
    }
    if (i == 4) {
        inserts[0][0] = 1;
        choices[0] = 0;
    } else {
        inserts[0][0] = 8;
        choices[0] = 1;
    }
    inserts[0][1] = 0;
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i == 4) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].coin < 50) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].star < 99) {
        goto starChoiceAvailable;
    }

starChoiceUnavailable:
    {
        inserts[1][0] = 1;
        choices[1] = 0;
        goto starChoiceDone;
    }

starChoiceAvailable:
    {
        inserts[1][0] = 8;
        choices[1] = 1;
    }

starChoiceDone:
    inserts[1][1] = 0;
    choices[3] = 1;
    choices[2] = 1;
    MBDlgWinInsertCreate(7, 0x6200, (s32)inserts[0], (s32)inserts[1], 0, 0, 0);
    menuResult = MB5_ComTeresaTypeChoice(choices);
    menu = menuResult;
    MBDlgWinClose();
    MBDlgWinKill();
    switch ((s16)menuResult) {
        case 0:
        case 1:
            goto selectPlayer;
        case 2:
            goto menuResultTwo;
        case 3:
            goto menuResultThree;
        default:
            goto finishMenu;
    }

selectPlayer:
    i = 0;
    j = 0;
    while (i < 4) {
        if (i == sys->current_player_index) {
            choices[j] = 0;
            inserts[j][0] = 1;
        } else if (menu == 0) {
            if (GwPlayer[i].coin == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        } else {
            if (GwPlayer[i].star == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        }
        MBCharNameMesConv(i, &inserts[j][1]);
        i++;
        j++;
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(7, 0x5C02, (s32)inserts[0], (s32)inserts[1], (s32)inserts[2], (s32)inserts[3], 0);
    playerChoice = MB5_ComTeresaPlayerChoice(choices);
    target = playerChoice;
    MBDlgWinClose();
    selectedByCpu = 0;
    MBDlgWinKill();
    switch ((s16)playerChoice) {
        case -1:
            goto restartMenu;
        case 4:
            goto selectCpuPlayer;
        case 5:
            if (modelIsLinked == -1) {
                MB5_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB5_MapScroll();
            }
            goto selectPlayer;
        default:
            goto playerSelected;
    }

selectCpuPlayer:
    {
        i = 0;
        count = 0;
        while (i < 4) {
            for (j = 0; j < 4; j++) {
                if (i == MBPlayerRankCalc(j) && sys->current_player_index != j) {
                    rankedPlayers[count++] = j;
                }
            }
            i++;
        }
        rank = MBRand(100.0f);
        for (i = 0; i < 3; i++) {
            if (rank < mb5ev_teresaComTargetRateTbl[i]) {
                break;
            }
        }
        if (menu != 0) {
            while (GwPlayer[rankedPlayers[i]].star == 0 || rankedPlayers[i] == sys->current_player_index) {
                i--;
            }
        } else {
            while (i >= 0 &&
                   (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
                i--;
            }
            i = 2;
            while (i >= 0 &&
                   (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
                i--;
            }
        }
        target = rankedPlayers[i];
        selectedByCpu = 1;
    }

playerSelected:
    if (menu == 0) {
        MBCoinChangeCreate(sys->current_player_index, -5);
        MBCoinTakeCreate(sys->current_player_index, -5);
    } else {
        MBCoinChangeCreate(sys->current_player_index, -50);
        MBCoinTakeCreate(sys->current_player_index, -50);
    }
    HuPrcSleep(30);
    if (menu == 1) {
        if (selectedByCpu != 0) {
            MBDlgWinExec(7, 0x6206);
        }
    } else {
        for (i = 0; (u32)i < 6; i++) {
            if (GwSystem.current_turn >= mb5ev_teresaCoinTurnTbl[i][0] &&
                GwSystem.current_turn <= mb5ev_teresaCoinTurnTbl[i][1]) {
                break;
            }
        }
        estimatedAmount = mb5ev_teresaCoinTurnTbl[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    MB5Ev_TeresaFadeOut(boo);
    if (menu == 0) {
        resultAmount = MB5Ev_TeresaSteal(target);
        MB5Ev_TeresaFadeIn(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], mb5ev_numFmtStr, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], mb5ev_numFmtStr, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= mb5ev_teresaCoinDiffTbl[i]) {
                        break;
                    }
                }
                MBDlgWinInsertCreate(7, i + 0x6210, (s32)inserts[0], 0, 0, 0, 0);
            }
            MBDlgWinClose();
            MBDlgWinKill();
        }
        if (resultAmount != -2) {
            mbItemBtnF = 0;
            rate = (f32)resultAmount / 90.0f;
            angle = 0.0f;
            mb5ev_teresaCoinMdl = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(mb5ev_teresaCoinMdl);
            MBModelDispOff(mb5ev_teresaCoinMdl);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    MB5Ev_TeresaCoinCreate((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(mb5ev_teresaCoinMdl);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = MB5Ev_TeresaStarSteal(target);
        MB5Ev_TeresaFadeIn(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            mb5ev_starGetTeresaF = 1;
            MB5Ev_StarGetExec(boo);
            mb5ev_starGetTeresaF = 0;
            goto outcomeDone;
        } else {
            resultAmount = -2;
        }
    }

outcomeDone:
    if (modelIsLinked == -1) {
        HuPrcSleep(20);
        MBPlayerMotionSet(-1, -1, 2);
    }
    if (resultAmount == -2) {
        HuPrcSleep(30);
        MBDlgWinExec(7, 0x6215);
    }
    goto finishMenu;

menuResultTwo:
    MB5Ev_TeresaFadeOut(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        MB5_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
    } else {
        MB5_MapScroll();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        MB5Ev_TeresaFadeOut(boo);
    }
    MBVecForwardSet(&boo->rot);
    if (modelIsLinked == -1) {
        MBModelKill(boo);
    }
    if (camMasu != -1) {
        HuAudFXPlay(0x126);
        MBMotionSet(model, -1, 4);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        Hu3DMotionTimeSet(
            model->omObj1->model[0], Hu3DMotion[Hu3DData[model->omObj1->model[0]].motId].unk02);
        while (MBMotionStartCheck(model) == 0) {
            HuPrcVSleep();
        }
        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb5ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 0.0f;
        model->scale.x = 0.0f;
        model->scale.z = 0.0f;
        MBModelKill(model);
    }
    if (cameraSet != 0) {
        MBSaiNumShow(sys->current_player_index);
    }
    if (modelIsLinked != -1) {
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }
    MB5Ev_TeresaMasuBranch();
}

void MB5Ev_Gate1Close(void) {
    MB5_GateClose(0);
}

void MB5Ev_Gate2Close(void) {
    MB5_GateClose(1);
}

omObjData *MB5Ev_ItemLampSmokeCreate(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, MB5Ev_ItemLampSmokeObjMain);
    data = obj->data = HuMemAllocTag(0x20, TAG_OVERLAY);
    data->unk0C = 255.0f;
    data->unk10 = arg1;
    data->unk14 = arg2;
    HuVecCopy3F(&data->unk00, arg4);
    if (arg5 != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = arg0->x;
    model->coords.y = arg0->y;
    model->coords.z = arg0->z;
    Hu3DModelTPLvlInit(model->omObj1->model[0]);
    Hu3DModelTPLvlSet(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->unk1C = arg3;
    return obj;
}

void MB5Ev_ItemLampSmokeObjMain(omObjData *arg0) {
    ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->unk00);
    scale = model->scale.z + data->unk10;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->unk0C - data->unk14;
    data->unk0C = alpha;
    if (alpha < 0.0f) {
        data->unk0C = 0.0f;
        if (data->unk1C != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, OM_STAT_FUNCOFF);
    }
    Hu3DModelTPLvlSet(model->omObj1->model[0], (u8)data->unk0C);
}

void MB5Ev_ItemMajinLamp(void) {
    Vec pos;
    s8 link;
    s8 index;
    GW_PLAYER *player;
    Object *lamp;
    UnkVibrateProcess *vib;
    s32 angle;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    MB5Ev_ItemUseFadeOut();
    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
    for (lamp->coords.y = 100.0f; lamp->coords.y > 30.0f;) {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x127);
    HuAudSubSeqVolFadeOut(0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 4, 5);

    angle = 0xB4;
    i = 0;
    while (angle < 0x438) {
        Vec particleDir[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB5Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    MBMasuLinkIdxGet(
        mb5ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
    player->clink = link;
    player->cidx = index;
    player->nlink = link;
    player->nidx = index + 1;
    player->blink = link;
    player->bidx = index - 1;
    player->rev &= ~FLAG_REV;
    MBGameModeMajinLampSet();
    HuAudFXPlay(0x128);
    omAllUPause();

    while (1) {
        Vec particleDir2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB5Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            msmMusPause(0);
        }
    }
}

void MB5Ev_ItemMajinLampStar(void) {
    s16 ret;

    mbStarMusF = 1;
    MBMasuEventCall(mb5ev_starMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    mbStarMusF = 0;
    ret = MBExitFlagGet();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void MB5Ev_ItemWarpBlock(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MB5Ev_ItemUseFadeOut();
    MBSaiKill(currentPlayerIndex);
    MBPlayerVibrate(CUR_PLAYER, 3);
    GWBoardFlagSet(0x11);
    MBSaiCreate(currentPlayerIndex);
    playerIndex = MBPlayerRankRandGet(1);
    omAllUPause();
    MBTurnHelpKill();
    HuPrcSleep(5);
    HuPrcSleep(25);
    MBPlayerMotionSet(currentPlayerIndex, 2, 0);
    MBModelJumpSet(GwPlayer[currentPlayerIndex].player_obj, 2.0f, -0.3f);
    HuPrcSleep(5);
    MBSaiHit(currentPlayerIndex);
    MBPlayerMotionShiftSet(currentPlayerIndex, CUR_PLAYER, 0, 10, 2);
    HuPrcSleep(20);
    MBItemWarpBlockSwapInit();
    MBItemWarpBlockSwapPlayerSet(playerIndex);
    MBItemWarpBlockSwapCreate();
    GWBoardFlagClear(0x11);
    fxId = MBSaiCreate(currentPlayerIndex);
    HuAudFXStop(fxId);
    MBSaiDispOff(currentPlayerIndex);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    MBSaiValueSet(currentPlayerIndex, CUR_PLAYER);
    spaceIndex = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    MBMasuCurSet(spaceIndex);
    MBMasuEventCall(spaceIndex, 1);
    ret = MBExitFlagGet();
    if (ret >= 0) {
        HuPrcSleep(CUR_PLAYER);
    }
    MBSaiSePlay(currentPlayerIndex);
}

void MB5Ev_ItemMove(void) {
    Process *process = HuPrcCurrentGet();
    WarpBlockSwapWork *work = process->user_data;
    f32 deltaX;
    f32 deltaY;
    f32 spriteX;
    f32 spriteY;
    s32 i;

    deltaX = (f32)(work->endX - work->startX) / (f32)work->duration;
    deltaY = (f32)(work->endY - work->startY) / (f32)work->duration;
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &spriteX, &spriteY);

    for (i = 1; i <= work->duration; i++) {
        if (work->spriteGroup != -1) {
            HuSprPosSet(work->spriteGroup, 0,
                        work->startX + (deltaX * i), work->startY + (deltaY * i));
        }

        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                           spriteX + (deltaX * i), spriteY + (deltaY * i));
        HuPrcVSleep();
    }

    if (work->spriteGroup != -1) {
        HuSprPosSet(work->spriteGroup, 0, work->endX, work->endY);
    }

    MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                       work->endX + spriteX - work->startX,
                       work->endY + spriteY - work->startY);
    omDelPrcObj(NULL);
}

Process *MB5Ev_ItemMoveCreate(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                           s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(MB5Ev_ItemMove, 0x4002, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = work;
    work->startX = startX;
    work->startY = startY;
    work->endX = endX;
    work->endY = endY;
    if (duration == -1) {
        duration = 25;
    }
    work->duration = duration;
    work->spriteGroup = spriteGroup;
    return process;
}

void MB5Ev_ItemKinoko(void) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MB5Ev_ItemMoveCreate(
                                mbItemCursorGrpId, position[0], position[1],
                                mb5ev_itemUsePosTbl[system->current_player_index].x,
                                mb5ev_itemUsePosTbl[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        MBStatusItemOfsApply(system->current_player_index,
                             MBItemSelNoGet(), 0, 2.0f);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    MBPlayerMotionSet(-1, 5, 0);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(50);
    MBPlayerMotionSet(-1, -1, 2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB5Ev_ItemUseFadeOut(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    MB5Ev_ItemMoveCreate(
        mbItemCursorGrpId, position[0], position[1],
        mb5ev_itemFadePosTbl[system->current_player_index].x,
        mb5ev_itemFadePosTbl[system->current_player_index].y, -1);
    HuPrcSleep(20);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuPrcSleep(2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB5Ev_ItemCursorReturn(void) {
    f32 position[2];
    s32 targetX;
    s32 targetY;
    Process *process;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusItemSprPosGet(GwSystem.current_player_index,
                               MBItemSelNoGet(), &position[0], &position[1]);
    MBStatusItemPosGet(-1, MBItemSelNoGet(), &targetX, &targetY);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB5Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     targetX, targetY, -1));
    HuPrcChildWatch();

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB5Ev_ItemShake(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;
    s32 j;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB5Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb5ev_itemUsePosTbl[system->current_player_index].x,
                                     mb5ev_itemUsePosTbl[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    if ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 0xB) ||
        (GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 8)) {
        HuAudFXPlay(0x141);
    }

    for (i = 0; i <= 1080; i += 30) {
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
    }

    for (j = 1; j < 10; j++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (j * 25));
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
        i += 30;
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB5Ev_ItemPhoneMove(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB5Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb5ev_itemUsePosTbl[system->current_player_index].x,
                                     mb5ev_itemUsePosTbl[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB5Ev_ItemIconMove(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
    f32 position[2];
    f32 stepX;
    f32 stepY;
    f32 scale;
    s32 i;

    if (mode == 2) {
        HuAudFXPlay(0x145);
    }

    MBStatusItemSprPosGet(arg0, arg1, &position[0], &position[1]);
    stepX = (target[0] - position[0]) / duration;
    stepY = (target[1] - position[1]) / duration;

    for (i = 2; duration != 0; duration--, i++) {
        position[0] += stepX;
        position[1] += stepY;
        MBStatusItemPosSet(arg0, arg1, position[0], position[1]);

        if ((mode == 1) && (i < 11)) {
            MBStatusItemTPLvlSet(arg0, arg1, i * 25);
            scale = i * 0.07f;
            MBStatusItemScaleSet(arg0, arg1, scale + 0.3f,
                                 (f32)((f64)scale + 0.3));
        }
        HuPrcVSleep();
    }

    MBStatusItemPosSet(arg0, arg1, target[0], target[1]);

    if (mode == 0) {
        for (i = 1; i < 10; i++) {
            MBStatusItemTPLvlSet(arg0, arg1, 255 - (i * 25));
            MBStatusItemScaleSet(arg0, arg1, 1.0f - (i * 0.1f), 1.0f - (i * 0.1f));
            HuPrcVSleep();
        }
        MBStatusItemTPLvlSet(arg0, arg1, 0);
    }
}

void MB5Ev_KSuitStart(void) {
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitCreate();
    MBModelDispOff(mbKSuitMdl);
    mbKSuitMdl->omObj1->scale.x = 0.0f;
    mbKSuitMdl->omObj1->scale.y = 0.0f;
    mbKSuitMdl->omObj1->scale.z = 0.0f;
    MBPlayerVibrate(-1, 3);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOff(player->player_obj);
    MBModelDispOn(mbKSuitMdl);

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    HuPrcSleep(20);
    PlayerFXPlay(0x274, GwSystem.current_player_index);
    MBKSuitMotionSet(5, 2);
    HuPrcSleep(40);
    MBKSuitMotionSet(-1, 2);
    MBDlgResultWinExec(0x3A14);
}

void MB5Ev_KSuitEnd(void) {
    Vec direction;
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitMotionSet(-1, 2);
    MBVecForwardSet(&direction);
    MBVecRotLerpCreate(&player->player_obj->rot, &direction, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOn(player->player_obj);
    MBKSuitKill();

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
}

void MB5Ev_ItemPhoneWaveProc(void) {
    s32 index;
    s32 group;
    s32 alpha;
    void *dialog;
    f32 x;
    f32 y;
    f32 angle;

    index = (s32)HuPrcCurrentGet()->user_data;
    dialog = MBPlayerVibrateObjCreate(-1, 1, 5);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, mb5ev_itemPhoneWaveSpr, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, HUSPR_ATTR_XLU);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    HuSprPosSet(group, 0, x, y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)mb5ev_itemPhoneWaveAngleTbl[index];
    for (; alpha >= 0; alpha -= 0x14) {
        x += cosdf(angle) * 5.0f;
        y -= sindf(angle) * 5.0f;
        HuSprPosSet(group, 0, x, y);
        HuSprTPLvlSet(group, 0, alpha);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(group, 0, 0);
    MBPlayerVibrateObjKill(dialog);
    HuSprGrpKill(group);
    omDelPrcObj(0);
}

void MB5Ev_ItemShopPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb5ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB5Ev_ItemPhoneMove();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = MB5Ev_YesNoChoiceGet((s32)mb5ev_shopPhoneComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(MB5Ev_ItemSelAttrProc, 0, 0, 0);
                omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
                MB5_MapScrollCancel();
                one = 1;
                winPauseF = one;
                omAllPause();
                omDelPrcObj(process);
                MBTurnHelpKill();
                continue;
            }
            GwSystem.forceShopHost = choice + 1;
            break;
        }

        process = omAddPrcObj(MB5Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
        MB5_MapScrollCancel();
        one = 1;
        winPauseF = one;
        omAllPause();
        omDelPrcObj(process);
        MBTurnHelpKill();
        continue;
    }

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB5Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB5Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);
    }

    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprAnimKill(mb5ev_itemPhoneWaveSpr);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (choice != 0) {
        HuAudFXPlay(0x2A0);
    } else if (GwPlayer[loc->current_player_index].coin < 5 ||
               loc->current_turn == loc->total_turns) {
        HuAudFXPlay(0x29A);
    } else {
        HuAudFXPlay(0x298);
    }
    MB5Ev_ShopMasu();
    GwSystem.forceShopHost = 0;
}

void MB5Ev_ItemKoopaPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 i;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb5ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB5Ev_ItemPhoneMove();

    HuPrcSleep(30);
    HuAudFXPlay(0x147);
    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB5Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        process->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB5Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        process->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);
    HuAudFXPlay(0x29F);

selectPlayer:
    MBDlgWinInsertCreate(4, 0x3A0A, mbCharNameMesTbl[GwPlayer[0].chr], mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr], mbCharNameMesTbl[GwPlayer[3].chr], 0);
    if (GwPlayer[loc->current_player_index].coin != 0) {
        choice = MB5Ev_YesNoChoiceGet(1, 0);
    } else {
        choice = MB5Ev_YesNoChoiceGet(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = MBPlayerRankRandGet(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(MB5Ev_ItemSelAttrProc, 0, 0, 0);
            omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
            MB5_MapScrollCancel();
            winPauseF = 1;
            omAllPause();
            omDelPrcObj(process);
            MBTurnHelpKill();
            goto selectPlayer;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B, mbCharNameMesTbl[GwPlayer[choice].chr], 0, 0, 0, 0);
            break;
    }

    MBDlgWinClose();
    MBDlgWinKill();
    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    HuSprAnimKill(mb5ev_itemPhoneWaveSpr);

    if (MBSaiTypeGet(loc->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    GwSystem.playerIndexVisitingBowser = choice;
    MBGameModeKoopaSet();
    MBExitOvlCallEx(0x50, 0, 3, 1);
    MBTurnHelpKill();
    MBExitReq(2);
    omAllUPause();
    HuPrcSleep(-1);
}

void MB5Ev_ItemStarYoke(void) {
    s32 i;
    s32 j;
    s32 wipeStarted;
    GW_SYSTEM *system = &GwSystem;
    Object *lamp;
    Object *starModel;
    Object *targetStar;
    Process *process;
    Process *dialogProcess;
    Vec direction;
    Vec pos;
    Vec destination;
    s32 angle;
    s32 alpha;
    f32 speed;
    f32 rotation;
    void *dialog;

    {
        GW_PLAYER *player;

        player = MBPlayerGet(-1);
        lamp = MBModelCreate(0x3C, NULL);
        MBMotionSet(lamp, -1, 1);
        Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
        lamp->velocity.x = 30.0f;
        lamp->flags |= 1;
        HuVecCopyXYZ(&lamp->scale, 0.0f, 0.0f, 0.0f);
        MBModelDispOff(lamp);
        MB5Ev_ItemUseFadeOut();

        {
            s32 itemSlot = MBItemFind(-1, 9);

            GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
        }
        MBItemRemoveEmpty(system->current_player_index);

        starModel = MBModelCreate(0x3D, NULL);
        Hu3DModelTPLvlInit(starModel->omObj1->model[0]);
        Hu3DModelTPLvlSet(starModel->omObj1->model[0], 0xFF);
        Hu3DModelScaleSet(starModel->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&starModel->coords, &player->player_obj->coords);
        starModel->coords.y = 100.0f;
        while (starModel->coords.y > 30.0f) {
            starModel->coords.y -= 1.0f;
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x127);
    msmMusFadeOut(HuAudMusNo, 0xB4);
    dialog = MBPlayerVibrateObjCreate(-1, 3, 5);

    for (angle = 180, i = 0; angle < 1080; angle += 20, i++) {
        Vec velocities[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB5Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
                              &velocities[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        Vec velocities2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB5Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
                              &velocities2[(i / 2) & 7], 1);
        }

        if (alpha > 0) {
            Hu3DModelTPLvlSet(starModel->omObj1->model[0], alpha & 0xFF);
            alpha -= 12;
        } else {
            MBModelDispOff(starModel);
            MBModelDispFlagSet(lamp);
            speed += 0.1f;
            lamp->scale.z = speed;
            lamp->scale.y = speed;
            lamp->scale.x = speed;
            if (speed > 1.0f) {
                HuAudSeqPlay(0x3D);
                break;
            }
        }
        i++;
        HuPrcVSleep();
    }

    lamp->scale.x = lamp->scale.y = lamp->scale.z = 1.0f;
    dialogProcess = MBModelHoverCreate(lamp, 3.0f, 2.0f);
    MBPlayerVibrateObjKill(dialog);
    HuPrcSleep(30);
    MBDlgWinExec(0x3C, 0x3A2F);
    omDelPrcObj(dialogProcess);

    i = 1;
    lamp->coords.y -= lamp->velocity.x;
    HuVecSubtract(&direction, &gCameraList->pos, &lamp->coords);
    MBVecNormalize(&direction);
    lamp->coords.y += lamp->velocity.x;

    while (lamp->velocity.x < 1800.0f) {
        lamp->coords.x += direction.x * 40.2f;
        lamp->velocity.x += direction.y * 40.0f;
        lamp->coords.z += direction.z * 40.2f;
        if ((lamp->velocity.x > 300.0f) && (i != 0)) {
            i = 0;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(WIPE_FADE, 0x32);
            HuAudFXPlay(0x128);
        }
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    {
        SpaceData *space;
        SpaceData *nextSpace;

        space = MBMasuGet(mb5ev_starMasu[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(mb5ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
        HuVecCopy3F(&destination, &space->coords);
        MBCameraPos3DSet(&destination);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&destination);
        lamp->flags &= ~1;
        HuVecCopy3F(&lamp->coords, &space->coords);
        HuVecSubtract(&direction, &nextSpace->coords, &space->coords);
        MBVecNormalize(&direction);
        lamp->coords.x -= direction.x * 20.0f;
        lamp->coords.z -= direction.z * 20.0f;
    }

    HuAudFXPlay(0x129);
    WipeCreateIn(WIPE_FADE, 0x32);
    lamp->velocity.x = 100.0f;
    while (lamp->velocity.x > 30.0f) {
        HuPrcVSleep();
        lamp->velocity.x -= 3.0f;
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MBVecRotLerpCreate(&lamp->rot,
                                              &direction,
                                              &lamp->rot, 0x10));
    i = 0;
    HuPrcChildWatch();
    dialogProcess = MBModelHoverCreate(lamp, 3.0f, 2.0f);
    MBDlgWinExec(0x3C, 0x3A30);
    HuAudFXPlay(0x12C);
    MBMotionSet(lamp, -1, 0);
    HuPrcSleep(20);

    wipeStarted = 1;
    for (j = 0; j < 8; j++) {
        if (mb5_starGuideHoverProc[j] != NULL) {
            omDelPrcObj(mb5_starGuideHoverProc[j]);
            mb5_starGuideHoverProc[j] = NULL;
        }
    }

    targetStar = mb5_starGuideMdl[system->star_spawn_indices[system->current_star_spawn]];
    HuAudSeqFadeOut(0x5A);
    rotation = 0.0f;
    while (targetStar->velocity.x < 400.0f) {
        targetStar->velocity.x += 3.0f;
        targetStar->coords.x += direction.x * 3.0f;
        targetStar->coords.z += direction.z * 3.0f;
        targetStar->rot.x = -sindf(rotation);
        targetStar->rot.z = cosdf(rotation);
        rotation += 45.0f;
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
        if ((targetStar->velocity.x > 50.0f) && (wipeStarted != 0)) {
            if (MBSaiTypeGet(system->current_player_index) == 3) {
                GWBoardFlagSet(0x17);
            } else {
                GWBoardFlagClear(0x17);
            }
            wipeStarted = 0;
            WipeColorSet(0, 0, 0);
            omDelPrcObj(dialogProcess);
            MBBoardRestartSet();
            MBTurnHelpKill();
            MBExitReq(2);
            MBGameModeReloadSet();
            omAllUPause();
        }
        HuPrcVSleep();
    }
    HuPrcSleep(-1);
}

void MB5Ev_ItemKeyManUse(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 player;
    Process *process;
    s32 group;
    void *sprite;
    s32 spriteCount;
    s32 i;
    f32 position[2];
    s32 result;

    player = GwSystem.current_player_index;
    group = HuSprGrpCreate(1, 0);
    sprite = DataRead(mbItemIconSprTbl[1]);
    spriteCount = HuSprAnimRead(sprite);
    DataClose(sprite);
    HuSprGrpMemberSet(group, 0, spriteCount, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB5Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb5ev_itemUsePosTbl[system->current_player_index].x,
                                     mb5ev_itemUsePosTbl[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - i * 25);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
    GwPlayer[player].itemNo[MBItemSelNoGet()] = -1;
    MBStatusItemTPLvlSet(player, MBItemSelNoGet(), 0);
    MBStatusItemSprPosGet(player, MBItemSelNoGet(), &position[0], &position[1]);
    HuSprPosSet(group, 0, position[0], position[1]);
    HuSprDispOn(group, 0);
    MBItemRemoveEmpty(player);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
retry:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    result = MB5Ev_YesNoChoiceGet((s32)&mb5ev_keyManUseComTree, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (result) {
        case 0:
            MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
            break;
        case 1:
            MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
            HuSprDispOff(group, 0);
            GwPlayer[player].itemNo[MBItemFindEmpty(player)] = 1;
            MBItemRemoveEmpty(player);
            GwSystem.cur_player_used_item &= ~1;
            break;
        default:
            HuSprDispOff(group, 0);
            MB5_MapScrollCancel();
            winPauseF = 1;
            omAllPause();
            HuSprDispOn(group, 0);
            goto retry;
    }
    MBDlgWinClose();
    MBDlgWinKill();
    if (result == 0) {
        HuPrcSleep(10);
        for (i = 1; i < 0x40; i++) {
            HuSprTPLvlSet(group, 0, (u16)(255.0f - (f32)i * 3.984f));
            HuPrcVSleep();
        }
        HuSprTPLvlSet(group, 0, 0);
    }
    HuSprGrpKill(group);
    HuSprAnimKill(spriteCount);
}

void MB5Ev_TereYokeSparkProc(void) {
    s32 playerIndex;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    f32 scale;
    s32 alpha;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    group = HuSprGrpCreate(1, 0);
    setupGroup = group;
    HuSprGrpMemberSet(setupGroup, 0, mb5ev_tereYokeSparkSpr, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, HUSPR_ATTR_XLU);
    MBStatusItemPosGet(mb5ev_tereYokePlayer, 0, &xPos, &yPos);

    xPos = (s32)((mb5ev_teresaSprDirTbl[mb5ev_tereYokePlayer].x * 16.0f) +
                 mb5ev_teresaSprPosTbl[mb5ev_tereYokePlayer].x);
    yPos = (s32)((mb5ev_teresaSprDirTbl[mb5ev_tereYokePlayer].y * 16.0f) +
                 mb5ev_teresaSprPosTbl[mb5ev_tereYokePlayer].y);
    HuSprPosSet(
        setupGroup, 0, (f32)xPos + mb5ev_tereYokeSparkOfsTbl[playerIndex].x,
        (f32)yPos + mb5ev_tereYokeSparkOfsTbl[playerIndex].y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(group, 0, 0xFF);

    scale = 0.0f;
    alpha = 0xFF;
    while (alpha >= 0) {
        HuSprScaleSet(group, 0, scale, scale);
        HuSprTPLvlSet(group, 0, alpha);
        HuPrcVSleep();
        alpha -= 10;
        scale += 0.1f;
    }

    HuSprTPLvlSet(group, 0, 0);
    HuSprGrpKill(group);
    omDelPrcObj(NULL);
}

void MB5Ev_TereYokeSprayProc(void) {
    s32 playerIndex;
    void *data;
    s32 itemSpriteId;
    s32 auraSpriteId;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    s32 i;
    s32 j;
    Process *childProcess;
    s32 fxId;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    data = DataRead(0x21002C);
    itemSpriteId = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1301BA);
    auraSpriteId = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1301B9);
    mb5ev_tereYokeSparkSpr = HuSprAnimRead(data);
    DataClose(data);

    group = HuSprGrpCreate(2, 2);
    setupGroup = group;
    HuSprAnimModeSet(setupGroup, 0, HUSPR_ANIM_MODE_BANK);
    HuSprGrpMemberSet(setupGroup, 0, itemSpriteId, 0xC);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, HUSPR_ATTR_XLU);
    HuSprParentSet(setupGroup, 0, -1);
    HuSprGrpMemberSet(setupGroup, 1, auraSpriteId, 0);
    HuSprPriSet(setupGroup, 1, 9);
    HuSprAttrSet(setupGroup, 1, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
    HuSprColorSet(setupGroup, 1, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(setupGroup, 1, 0xFF);
    HuSprScaleSet(setupGroup, 1, 2.0f, 2.0f);
    HuSprParentSet(setupGroup, 1, 0);

    yPos = 0xC8;
    if (playerIndex & 1) {
        HuSprAttrSet(setupGroup, 0, HUSPR_ATTR_FLIPX);
        HuSprAttrSet(setupGroup, 1, HUSPR_ATTR_FLIPX);
        HuSprPosSet(setupGroup, 1, 0x14, -5);
    } else {
        yPos = 0x78;
        HuSprPosSet(group, 1, -0x14, -5);
    }

    xPos = (playerIndex < 2) ? -0x20 : 0x110;
    HuPrcSleep(0x14);
    GwPlayer[playerIndex].itemNo[MBItemFind(playerIndex, 0xC)] = -1;
    MBItemRemoveEmpty(playerIndex);
    MBStatusItemIconSprReinit(playerIndex);

    do {
        if (playerIndex < 2) {
            xPos += 5;
            if (xPos >= 0x33) {
                break;
            }
        } else {
            xPos -= 5;
            if (xPos < 0xD2) {
                break;
            }
        }
        HuSprPosSet(group, 0, yPos, xPos);
        HuPrcVSleep();
    } while (1);

    HuPrcSleep(0xA);
    HuSprDispOn(group, 1);
    fxId = HuAudFXPlay(0x14C);
    mb5ev_tereYokePlayer = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(MB5Ev_TereYokeSparkProc, 0x4002, 0, 0);
            childProcess->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), childProcess);
    HuPrcChildWatch();
    HuAudFXStop(fxId);
    HuSprTPLvlSet(group, 1, 0);

    for (i = 0xFF; i >= 0; i -= 0x1E) {
        HuSprTPLvlSet(group, 0, i);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(group, 0, 0);
    HuSprGrpKill(group);
    HuSprAnimKill(mb5ev_tereYokeSparkSpr);
    HuSprAnimKill(auraSpriteId);
    HuSprAnimKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void MB5Ev_ItemNullUse(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void MB5Ev_KoopaCardCoinProc(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb5ev_koopaCardCoinMdl);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        HuMtxRotYF(Hu3DData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void MB5Ev_KoopaCardCoinCreate(Object *arg) {
    Process *temp = omAddPrcObj(MB5Ev_KoopaCardCoinProc, 0x1000, 0, 0);

    temp->user_data = arg;
}

void MB5Ev_KoopaCardSpinProc(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        mb5ev_koopaCardMdl->rot.x = -sindf(angle);
        mb5ev_koopaCardMdl->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            mb5ev_koopaCardMdl->scale.z = scale;
            mb5ev_koopaCardMdl->scale.y = scale;
            mb5ev_koopaCardMdl->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    mb5ev_koopaCardMdl->scale.x = mb5ev_koopaCardMdl->scale.y = mb5ev_koopaCardMdl->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(mb5ev_koopaCardMdl);
    omDelPrcObj(0);
}

void MB5Ev_BankKoopaCardExec(void) {
    s32 flag = 0;
    GW_SYSTEM *system = &GwSystem;
    void *data;
    UnkVibrateProcess *process;
    s32 positionX;
    s32 positionY;
    s32 bankCoins;
    s32 coinCount;
    s32 spriteId;
    f32 coinStep;
    f32 coinProgress;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    data = DataRead(mbItemCharSprTbl[GwPlayer[system->current_player_index].chr]);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbItemCursorGrpId, 0, spriteId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 10);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuSprDispOff(mbItemCursorGrpId, 0);
    MBStatusItemPosGet(-1, 0, &positionX, &positionY);
    HuSprPosSet(mbItemCursorGrpId, 0, positionX, positionY);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(-1, 0xF));
    MB5Ev_ItemUseFadeOut();

    mb5ev_koopaCardMdl = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&mb5ev_koopaCardMdl->coords, &MBPlayerGet(-1)->player_obj->coords);
    mb5ev_koopaCardMdl->velocity.x = 100.0f;
    while (30.0f < mb5ev_koopaCardMdl->velocity.x) {
        mb5ev_koopaCardMdl->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(MB5Ev_KoopaCardSpinProc, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    mb5ev_koopaCardCoinMdl = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(mb5ev_koopaCardCoinMdl);
    MBModelDispOff(mb5ev_koopaCardCoinMdl);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                MB5Ev_KoopaCardCoinCreate(mb5ev_koopaCardMdl);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                MB5_BankCoinHide();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(mb5ev_koopaCardCoinMdl);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 MB5_ComItemTargetChoice(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)mb5_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = mb5_comExchangeBoxTarget + 1;
                } else {
                    delay = mb5_comRobBoxTarget + 1;
                }
                inputs[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, buttons[GwPlayer[i].pad]);
                inputs[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            inputs[GwPlayer[i].pad] = 0;
        }
    }

    if (delay != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; delay != 0; j++) {
            if (--delay == 0) {
                inputs[GwPlayer[GwSystem.current_player_index].pad] = A_BUTTON;
            }
            if (j == 0) {
                HuWinComKeyWait(inputs[0], inputs[1], inputs[2], inputs[3],
                                MBMesWaitGet());
            } else {
                HuWinComKeyWait(inputs[0], inputs[1], inputs[2], inputs[3], 5);
            }
        }
    } else {
        HuWinComKeySet(inputs[0], inputs[1], inputs[2], inputs[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void MB5Ev_ExchangeItemFadeOutProc(void) {
    Process *prc = HuPrcCurrentGet();
    s32 playerIdx = (s32)prc->user_data;
    s32 j;
    s32 val;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    MBPlayerVibrate(((s16 *)&prc->user_data)[1], 4);

    for (val = 0x80; val > 0; val -= 0xA) {
        for (j = 0; j < 3; j++) {
            if (GwPlayer[playerIdx].itemNo[j] != -1) {
                MBStatusItemTPLvlSet(playerIdx, j, val);
            }
        }
        HuPrcVSleep();
    }

    for (j = 0; j < 3; j++) {
        if (GwPlayer[playerIdx].itemNo[j] != -1) {
            MBStatusItemTPLvlSet(playerIdx, j, 0);
        }
    }
    omDelPrcObj(NULL);
}

void MB5Ev_ExchangeItemFadeInProc(void) {
    Process *process = HuPrcCurrentGet();
    s32 playerIndex = (s32)process->user_data;
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    s32 alpha;
    s32 itemIndex;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;

    for (i = 0, itemIndex = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerIndex, itemIndex, &xPos, &yPos);
            MBStatusItemPosSet(system->current_player_index, i, xPos, yPos);
            itemIndex += (i != MBItemSelNoGet());
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
                if (i != MBItemSelNoGet()) {
                    MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
                }
            }
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            if (i != MBItemSelNoGet()) {
                MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
            }
        }
    }
    omDelPrcObj(NULL);
}

void MB5Ev_ItemExchangeBox(void) {
    char playerNames[4][16];
    u8 choices[16];
    Vec2f position;
    Vec2f target;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    u16 spriteId;
    Object *box;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer;
    s32 noAnimation = 0;
    s32 itemCount;
    s32 itemSlot;
    s32 sleepTime;
    s32 i;
    s32 j;
    s32 item;
    f32 angle;
    f32 angleStep;
    f32 spinStep;
    f32 scale;
    f32 scaleY;
    f32 itemAngle;
    f32 scaleZ;
    f32 finalScale;

    MB5Ev_ItemUseFadeOut();
    box = MBModelCreate(0x20, NULL);
    Hu3DModelObjAttrSet(box->omObj1->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(box->omObj1->model[0]);
    Hu3DModelVtxBufMake(box->omObj1->model[0]);
    Hu3DModelDynamicFree(box->omObj1->model[0]);
    Hu3DModelScaleSet(box->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&box->coords, &MBPlayerGet(-1)->player_obj->coords);
    Hu3DMotionAttrSet(box->omObj1->model[0], 2, 1);
    box->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (box->velocity.x > 30.0f) {
        box->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    for (itemSlot = 0; itemSlot < 4; itemSlot++) {
        if (GwSystem.current_player_index == itemSlot) {
            playerNames[itemSlot][0] = 1;
            choices[itemSlot] = 0;
        } else {
            playerNames[itemSlot][0] = 8;
            choices[itemSlot] = 1;
        }
        MBCharNameMesConv(itemSlot, &playerNames[itemSlot][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = MB5_ComItemTargetChoice(choices, 1);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = MBPlayerRankRandGet(1);
    }

    itemSlot = MBItemSelNoGet();
    if (GwPlayer[GwSystem.current_player_index].itemNo[itemSlot] == 0x10 &&
        MBItemFindEmpty(GwSystem.current_player_index) == 1 && MBItemFindEmpty(targetPlayer) == 0) {
        noAnimation = 1;
    }

    if (!noAnimation) {
        HuAudFXPlay(0x149);
        Hu3DMotionAttrSet(box->omObj1->model[0], 1, 0);
        HuPrcSleep(20);
        position.x = 160.0f;
        position.y = 84.0f;
        for (itemSlot = 0; itemSlot < 3; itemSlot++) {
            for (j = 0; j < 3; j++) {
                spriteId = 0x4790;
                if (j == itemSlot) {
                    spriteId = 0x4786;
                }
                MBStatusItemPriSet(system->current_player_index, j, spriteId);
            }
            if (GwPlayer[system->current_player_index].itemNo[itemSlot] != -1) {
                if (itemSlot != MBItemSelNoGet()) {
                    MB5Ev_ItemIconMove(system->current_player_index, itemSlot, 10, &position.x, 0);
                    HuPrcSleep(2);
                }
            }
        }
        Hu3DMotionAttrSet(box->omObj1->model[0], 4, 4);
        while (Hu3DData[box->omObj1->model[0]].motTime != 0.0f) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x150);
        HuPrcSleep(20);
        process = omAddPrcObj(MB5Ev_ExchangeItemFadeOutProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        HuAudFXPlay(0x151);

        angle = 0.0f;
        spinStep = 5.0f;
        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            spinStep += 2.0f;
            if (spinStep > 45.0f) {
                spinStep = 45.0f;
                if (i++ >= 31) {
                    break;
                }
            }
            HuPrcVSleep();
        }

        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
                if (++i >= 2) {
                    break;
                }
            }
            spinStep -= 2.0f;
            if (spinStep < 5.0f) {
                spinStep = 5.0f;
            }
            HuPrcVSleep();
        }
        box->rot.x = 0.0f;
        box->rot.z = 1.0f;
        HuAudFXPlay(0x152);
        for (itemSlot = 0; itemSlot < 1441; itemSlot += 40) {
            scale = itemSlot;
            angleStep = sindf(scale) / 1.5f + 1.0f;
            scaleY = sindf(scale) / 1.5f + 1.0f;
            scaleZ = sindf(scale) / 1.5f + 1.0f;
            HuVecCopyXYZ(&box->scale, angleStep, scaleY, scaleZ);
            HuPrcVSleep();
        }

        HuAudFXPlay(0x149);
        Hu3DMotionAttrSet(box->omObj1->model[0], 4, 0);
        HuPrcSleep(20);
        process = omAddPrcObj(MB5Ev_ExchangeItemFadeInProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB5Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB5Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB5Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                MB5Ev_ItemIconMove(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB5Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB5Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                MB5Ev_ItemIconMove(targetPlayer, 2, 7, &target.x, 2);
                break;
        }
        HuPrcSleep(2);
    }

    itemSlot = MBItemSelNoGet();
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    for (itemSlot = 0; itemSlot < 3; itemSlot++) {
        item = GwPlayer[targetPlayer].itemNo[itemSlot];
        GwPlayer[targetPlayer].itemNo[itemSlot] = GwPlayer[system->current_player_index].itemNo[itemSlot];
        GwPlayer[system->current_player_index].itemNo[itemSlot] = item;
    }
    if (!noAnimation) {
        MBStatusItemSprKill(-1);
        MBStatusItemSprKill(targetPlayer);
        sleepTime = 10;
    } else {
        sleepTime = 20;
    }
    HuPrcSleep(sleepTime);
    HuAudFXPlay(0x15B);
    finalScale = 0.1f;
    for (i = 0; i < 20; i++) {
        finalScale += 0.044999998f;
        Hu3DModelVtxWave(box->omObj1->model[0], finalScale, finalScale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(box);

    if (noAnimation) {
        PlayerFXPlay(0x286, system->current_player_index);
        MBPlayerMotionSet(-1, 3, 0);
        HuPrcSleep(70);
    } else {
        PlayerFXPlay(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, 5, 0);
        HuPrcSleep(50);
    }
    MBPlayerMotionShiftSet(-1, -1, 0, 10, 2);
    MBDlgWinInsertCreate(-1, noAnimation ? 0x3A2E : 0x3A2D,
                         mbCharNameMesTbl[GwPlayer[system->current_player_index].chr],
                         mbCharNameMesTbl[GwPlayer[targetPlayer].chr], 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
}

void MB5Ev_GambleCoinEffProc(void) {
    ModelAnimWork *data = HuPrcCurrentGet()->user_data;
    Object *obj1 = data->obj1;
    Object *obj2 = data->obj2;

    MBMotionSet(obj1, -1, data->state);
    HuVecCopy3F(&obj1->coords, &obj2->coords);
    obj1->coords.y += obj2->velocity.x - 10.0f;
    MBModelDispFlagSet(obj1);
    while (MBMotionCheck(obj1) == 0 && data->flag == 0) {
        HuPrcVSleep();
    }
    MBModelKill(obj1);
    omDelPrcObj(0);
}

void MB5Ev_GambleCoinProc(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = mb5ev_gambleCoinMdl;
    Object *model;
    Process *process;
    ModelAnimWork *work;
    s32 effect;
    f32 angle;
    f32 angleStep;
    f32 fallSpeed;
    f32 scale;
    s32 i;

    model = MBModelCreate(0x45, NULL);
    MBModelDispOff(model);
    effect = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(effect, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(effect, 10.0f);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    HuAudFXPlay(0x24C);

    angle = 0.0f;
    angleStep = 2.0f;
    while (angleStep < 80.0f) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        angleStep += 1.0f;
        if (angleStep > 80.0f) {
            angleStep = 80.0f;
        }
        EffectPosSet(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14A);
    while (gameGuyModel->velocity.x < 110.0f) {
        gameGuyModel->velocity.x += 7.0f;
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        EffectPosSet(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    *processFlag = 0;
    while (*processFlag == 0) {
        if (mb5ev_gambleCoinPlayer != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(mb5ev_gambleCoinPlayer)->player_obj->coords);
            EffectPosSet(effect, gameGuyModel->coords.x,
                               gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14B);
    fallSpeed = 3.0f;
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= fallSpeed;
        if (fallSpeed > 1.0f) {
            fallSpeed -= 0.2f;
        }
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        EffectPosSet(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (angleStep > 15.0f) {
            angleStep -= 3.0f;
        } else {
            angleStep -= 0.5f;
        }
        if (angleStep < 1.0f) {
            break;
        }
        EffectPosSet(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    EffectStop(effect);
    process = omAddPrcObj(MB5Ev_GambleCoinEffProc, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x20);
    process->user_data = work;
    work->obj1 = model;
    work->obj2 = gameGuyModel;
    work->state = 0;
    work->flag = 0;
    HuPrcSleep(3);
    *processFlag = 0;
    HuAudFXPlay(0x24D);

    i = 0;
    scale = 0.1f;
    for (; i < 20; i++) {
        scale += 0.044999998f;
        Hu3DModelVtxWave(gameGuyModel->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(gameGuyModel);
    omDelPrcObj(NULL);
}

void MB5Ev_ItemGambleCoin(void) {
    Object *coinModel;
    Object *gameGuyModel;
    Object *playerObj;
    Process *process;
    GW_SYSTEM *system;
    s32 choice;
    s32 itemSlot;
    s32 rewardIndex;
    s32 randomValue;
    s32 rewardAmount;
    s32 i;
    struct {
        s32 processFlag;
        s32 pad;
        char rewardText[0x10];
    } locals;

    system = &GwSystem;
    MB5Ev_ItemUseFadeOut();
    itemSlot = MBItemFind(-1, 0x11);
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    coinModel = MBModelCreate(0x3E, 0);
    Hu3DModelScaleSet(coinModel->omObj1->model[0], 0, 0, 0);
    MBModelTempAllocFree(coinModel);
    coinModel->velocity.x = 30.0f;
    MBModelDispOff(coinModel);

    gameGuyModel = MBModelCreate(0x43, 0);
    mb5ev_gambleCoinMdl = gameGuyModel;
    Hu3DModelObjAttrSet(gameGuyModel->omObj1->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(gameGuyModel->omObj1->model[0]);
    Hu3DModelVtxBufMake(gameGuyModel->omObj1->model[0]);
    Hu3DModelDynamicFree(gameGuyModel->omObj1->model[0]);
    HuVecCopy3F(&gameGuyModel->coords, &MBPlayerGet(-1)->player_obj->coords);
    Hu3DMotionAttrSet(gameGuyModel->omObj1->model[0], 2, 1);
    gameGuyModel->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

selectPlayer:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = MB5Ev_YesNoChoiceGet(0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (choice >= 0) {
        if (choice < 4) {
            goto validChoice;
        }
        if (choice == 4) {
            choice = MBPlayerRankRandGet(0);
            goto validChoice;
        }
    }
    MB5_MapScrollCancel();
    winPauseF = 1;
    omAllPause();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(MB5Ev_GambleCoinProc, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        mb5ev_gambleCoinPlayer = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        mb5ev_gambleCoinPlayer = choice;
    }

    locals.processFlag = 1;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    playerObj = MBPlayerGet(choice)->player_obj;
    process = MBModelHoverCreate(coinModel, 5.0f, 2.0f);
    HuVecCopy3F(&coinModel->coords, &playerObj->coords);
    MBModelDispFlagSet(coinModel);
    coinModel->scale.x = coinModel->scale.y = coinModel->scale.z = 0.0f;
    while (coinModel->scale.x < 1.0f) {
        coinModel->scale.x = coinModel->scale.y = coinModel->scale.z += 0.2f;
        HuPrcVSleep();
    }

    MBPlayerVibrate(choice, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[choice].coin != 0) {
        MB5Ev_WinPlayerKeyExec(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        MB5Ev_WinPlayerKeyExec(10, 0x2F02, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x >= 10.0f) {
            coinModel->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        while (coinModel->velocity.x < 100.0f) {
            coinModel->velocity.x += 4.0f;
            playerObj->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        MB5Ev_WinPlayerKeyExec(10, 0x2F01, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x <= 100.0f) {
            coinModel->velocity.x += 4.0f;
            HuPrcVSleep();
        }
        MBModelKill(coinModel);
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBPlayerComCheck((s16)choice) != 0 && system->show_com_minigames != 0) {
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(coinModel);
        MBModelJumpSet(playerObj, 0, 0);
        playerObj->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        randomValue = MBRand(100.0f) + 1;
        for (rewardIndex = 0; rewardIndex < 7; rewardIndex++) {
            if (randomValue <= mb5ev_gambleRateTbl[rewardIndex].threshold) {
                break;
            }
        }
        if (mb5ev_gambleRateTbl[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * mb5ev_gambleRateTbl[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, mb5ev_numFmtStr, rewardAmount);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)locals.rewardText, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(choice, rewardAmount);
            MBCoinTakeCreate(choice, rewardAmount);
            HuPrcSleep(20);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(10);
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBSaiTypeGet(system->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    MBPlayerGet(choice)->group = 0;
    randomValue = MBRand(100.0f);
    for (rewardIndex = 0; (u32)rewardIndex < 3; rewardIndex++) {
        if (randomValue < mb5ev_gambleMgRateTbl[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = mb5ev_gambleMgTbl[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    MBGameModeMgSet();
    omAllUPause();
    MBExitReq(2);
    HuPrcSleep(-1);
}

void MB5Ev_After5ItemMove(s32 arg0, s32 arg1, f32 *arg2) {
    f32 curX;
    f32 curY;
    f32 stepX;
    f32 stepY;

    MBStatusSprPosGet((s16)arg0, 0, &curX, &curY);
    stepX = (arg2[0] - curX) / arg1;
    stepY = (arg2[1] - curY) / arg1;
    while (arg1 != 0) {
        curX += stepX;
        curY += stepY;
        HuSprPosSet(arg0, 0, curX, curY);
        HuPrcVSleep();
        arg1--;
    }
    HuSprPosSet(arg0, 0, arg2[0], arg2[1]);
}

void MB5Ev_After5LineShow(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            HuSprPosSet(mb5ev_after5GrpId[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(mb5ev_after5GrpId[idx], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(mb5ev_after5GrpId[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprDispOn(mb5ev_after5GrpId[idx], 0);
    for (i = 0; i < 255; i += 255 / divisor) {
        HuSprTPLvlSet(mb5ev_after5GrpId[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mb5ev_after5GrpId[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void MB5Ev_After5NumFade(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = mb5ev_after5NumColorTbl[i].r;
        sp18.g = mb5ev_after5NumColorTbl[i].g;
        sp18.b = mb5ev_after5NumColorTbl[i].b;

        sp28.r = (mb5ev_after5NumColorTbl[i + 1].r - sp18.r) / 30;
        sp28.g = (mb5ev_after5NumColorTbl[i + 1].g - sp18.g) / 30;
        sp28.b = (mb5ev_after5NumColorTbl[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(mb5ev_after5GrpId[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(mb5ev_after5GrpId[3], 0, mb5ev_after5NumColorTbl[i + 1].r, mb5ev_after5NumColorTbl[i + 1].g, mb5ev_after5NumColorTbl[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void MB5Ev_After5Effect(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = mb5ev_after5EffMdl;
    MBModelDispFlagSet(model);

    angle = 0.0f;
    for (scale = 1.0f; scale < 18.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 1) {
        wait_angle_step = 20.0f;
        while (*state != 1) {
            HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
            angle += wait_angle_step;
            HuPrcVSleep();
        }
    }

    for (; scale < 40.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 2) {
        scale = 20.0f;
        while (*state != 2) {
            HuMtxRotZF(Hu3DData[model->omObj1->model[0]].mtx, angle);
            angle += scale;
            HuPrcVSleep();
        }
    }

    MBModelKill(model);
    omDelPrcObj(0);
}

void MB5Ev_ItemAfter5(void) {
    s32 sp18[4];
    f32 sp28[2];
    s32 sp30;
    s32 sp34;
    f32 sp38;
    f32 sp3C;
    s32 sp40;
    Process *temp_v0_4;
    f32 temp_f20;
    f32 var_f20;
    s32 temp_s0_3;
    s32 temp_s4;
    s32 temp_s7;
    void *temp_s1_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    void *temp_v0;
    Object *temp_v0_3;
    s32 i;
    s32 j;
    GW_SYSTEM *system = &GwSystem;
    s32 temp;

    temp_s4 = HuSprGrpCreate(1, 0);
    temp_v0 = DataRead(mbItemIconSprTbl[18]);
    temp_s7 = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    HuSprGrpMemberSet(temp_s4, 0, temp_s7, 0);
    HuSprPriSet(temp_s4, 0, 0x4776U);
    HuSprAttrSet(temp_s4, 0, HUSPR_ATTR_XLU);
    for (i = 0; i < 4; i++) {
        mb5ev_after5GrpId[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(mb5ev_after5GrpId[i], 0, sp18[i], 0);
        HuSprPriSet(mb5ev_after5GrpId[i], 0, 0x4780U);
        HuSprAttrSet(mb5ev_after5GrpId[i], 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
        HuSprTPLvlSet(mb5ev_after5GrpId[i], 0, 0U);
        HuSprColorSet(mb5ev_after5GrpId[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    mb5ev_after5EffMdl = temp_v0_3;
    Hu3DModelAttrSet(temp_v0_3->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(temp_v0_3->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(temp_v0_3->omObj1->model[0]);
    Hu3DModelScaleSet(temp_v0_3->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&temp_v0_3->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    MBModelTempAllocFree(temp_v0_3);
    MBModelDispOff(temp_v0_3);
    HuSprDispOff(mbItemCursorGrpId, 0);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBStatusItemPosGet(system->current_player_index, MBItemSelNoGet(), &sp30, &sp34);
    HuSprPosSet(temp_s4, 0, sp30, sp34);
    sp28[0] = 160.0f;
    sp28[1] = 76.0f;
    HuAudFXPlay(0x145);
    MB5Ev_After5ItemMove(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    MB5Ev_After5ItemMove(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(MB5Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    MB5Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(MB5Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    MB5Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    HuAudFXPlay(0x14E);
    MBStatusSprPosGet(temp_s4, 0, &sp38, &sp3C);
    for (var_f20 = 0.0f, var_s1 = 0; var_f20 < 90.0f; var_f20 += 3.6f) {
        HuSprPosSet(temp_s4, 0, ((cosdf((2.0f * var_f20) + 270.0f) * 80.0f) + sp38), (((1.0f - cosdf(var_f20)) * 90.0f) + sp3C));
        if (!(var_f20 > 54.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = 1;
        }
        temp = var_v1 != 0;
        if (temp && var_s1 == 0) {
            var_s1 = 1;
            temp_v0_4 = omAddPrcObj(MB5Ev_After5LineShow, 0x4002U, 0, 0);
            temp_v0_4->user_data = (void *)2;
            HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
        }
        HuPrcVSleep();
    }

    temp_s0_3 = (s16)(s32)((cosdf(450.0f) * 80.0f) + sp38);
    HuSprPosSet(temp_s4, 0, temp_s0_3, (((1.0f - cosdf(90.0f)) * 90.0f) + sp3C));

    for (j = 255; j > 0; j -= 0x19, HuPrcVSleep()) {
        HuSprTPLvlSet(temp_s4, 0, j);
    }

    HuSprGrpKill(temp_s4);
    HuSprAnimKill(temp_s7);
    HuPrcChildWatch();

    for (i = 0; i < 3; i++) {
        HuSprDispOff(mb5ev_after5GrpId[i], 0);
    }

    HuSprDispOn(mb5ev_after5GrpId[3], 0);
    HuSprTPLvlSet(mb5ev_after5GrpId[3], 0, 0xFFU);
    HuSprPosSet(mb5ev_after5GrpId[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB5Ev_After5NumFade, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(MB5Ev_After5Effect, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(mb5ev_after5GrpId[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
        if (i >= (2880 / 2 + 1)) {
            sp40 = 1;
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(WIPE_FADE, 0x32);
    MBPlayerVibrateObjKill(temp_s1_2);

    for (var_f20 = 0.0f; WipeStatGet() != 0; var_f20 += 0.1f) {
        HuSprScaleSet(mb5ev_after5GrpId[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(mb5ev_after5GrpId[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(WIPE_FADE, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void MB5Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    BranchLink *link;
    s32 back;
    s32 sel;
    s32 count;
    s32 row;
    s32 col;
    s32 i;
    s16 *temp;
    DecisionTreeNonLeafNode **tree;

    link = links[0];
    tree = trees;
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    MB5_BranchHelpStart();
    player = MBPlayerGet(GwSystem.current_player_index);
    back = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 2; col++) {
            if (masu[row][col] == back) {
                break;
            }
        }
        if (col == 2) {
            break;
        }
    }

    temp = masu[row];
    link += row * 2;
    win = MBBranchArrowLinkCreate(GwSystem.current_player_index, temp);
    MBBranchSelStart(win, GwSystem.current_player_index, 0);

    if (MBPlayerComCheck(-1)) {
        count = MBComTreeExec(tree[row]);
        for (i = 0; i < count; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }

    sel = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB5_BranchHelpEnd();

    if (sel) {
        link++;
    }

    MBMoveNextMasuSet(-1, link->link, link->idx);
    switch (link->rev) {
        case 0:
            player->rev &= ~1;
            break;
        case 1:
            player->rev |= 1;
            break;
    }
}

void MB5Ev_KinokoMarkKill(s32 arg0) {
    {
        omObjData *obj = mb5ev_kinokoMarkObj[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            mb5ev_kinokoMarkObj[arg0] = NULL;
        }
    }

    {
        Object *model = mb5ev_kinokoMarkMdl[arg0];

        if (model != NULL) {
            MBModelKill(model);
            mb5ev_kinokoMarkMdl[arg0] = NULL;
        }
    }
}

void MB5Ev_KinokoMarkObjKillAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = mb5ev_kinokoMarkObj[i];

        if (obj != NULL) {
            omDelObj(obj);
            mb5ev_kinokoMarkObj[i] = NULL;
        }
    }
}

void MB5Ev_KinokoMarkObjMain(omObjData *obj) {
    s32 playerIdx = obj->work[0];

    if (GwSystem.current_player_index == 4) {
        if (obj->work[2] == 0) {
            if (obj->work[1] != 0) {
                obj->work[1] -= 1;
                if (obj->work[1] != 0) {
                    return;
                }
                obj->work[2] = 1;
            } else {
                obj->work[1] = 40;
                return;
            }
        }
    }

    {
        GW_PLAYER *player = MBPlayerGet(playerIdx);
        Object *effectObj = mb5ev_kinokoMarkMdl[playerIdx];

        HuVecCopy3F(&effectObj->coords, &player->player_obj->coords);
        effectObj->velocity.x = player->player_obj->velocity.x + 20.0f;
        HuVecCopy3F(&effectObj->rot, &player->player_obj->rot);
        effectObj->coords.x += sindf(obj->rot.x) * obj->trans.x;
        effectObj->coords.z += cosdf(obj->rot.x) * obj->trans.x;
        obj->rot.x += 5.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        if (obj->trans.x <= 5.0f) {
            obj->trans.x += 0.25f;
        }
        if (player->player_obj->flags & 8) {
            MBModelDispFlagSet(effectObj);
        } else {
            MBModelDispOff(effectObj);
        }
    }
}

void MB5Ev_KinokoMarkCreate(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (mb5ev_kinokoMarkMdl[playerNo] == NULL) {
        switch (type) {
            case 0:
                modelId = 0x3F;
                break;
            case 1:
                modelId = 0x40;
                break;
            case 2:
                modelId = 0x41;
                break;
            default:
                modelId = 0x42;
                break;
        }

        obj = MBModelCreate(modelId, NULL);
        MBModelTempAllocFree(obj);
        mb5ev_kinokoMarkMdl[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        MBModelDispFlagSet(mb5ev_kinokoMarkMdl[playerNo]);
    }
}

void MB5Ev_KinokoMarkObjCreate(s32 arg) {
    mb5ev_kinokoMarkObj[arg] = omAddObj(0x3FFF, 0, 0, -1, MB5Ev_KinokoMarkObjMain);
    mb5ev_kinokoMarkObj[arg]->work[0] = arg;
    mb5ev_kinokoMarkObj[arg]->work[1] = 0;
    mb5ev_kinokoMarkObj[arg]->work[2] = 0;
    mb5ev_kinokoMarkObj[arg]->rot.x = (f32)MBRand(360.0f);
    mb5ev_kinokoMarkObj[arg]->trans.x = 0;
}

void MB5Ev_KinokoMarkCreateAll(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        mb5ev_kinokoMarkObj[i] = NULL;
        mb5ev_kinokoMarkMdl[i] = NULL;
        idx = -!(MBPlayerGet(i)->rev & 0x2);
        if (MBPlayerGet(i)->rev & 0x4) {
            idx = 1;
        }
        if (MBPlayerGet(i)->rev & 0x20) {
            idx = 2;
        }
        if (MBPlayerGet(i)->rev & 0x40) {
            idx = 3;
        }
        if (idx != -1) {
            MB5Ev_KinokoMarkCreate(i, idx);
            MB5Ev_KinokoMarkObjCreate(i);
        }
    }
    MBExitHookSet(MB5Ev_KinokoMarkObjKillAll);
}

void MB5Ev_NKinokoTurnStart(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    f32 scale;

    if ((((*slowDiceFlags >> loc->current_player_index) & 1))) {
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        if ((player->rev & 0x20) || ((player->rev & 8) && !(player->rev & 2))) {
            MBDlgWinExec(-1, 0x4219);
        } else {
            MBDlgWinExec(-1, 0x3A07);
        }

        if (player->rev & 2) {
            if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB5Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB5Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void MB5Ev_ItemKoopaNKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        MBSaiKill(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB5Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB5Ev_KinokoVibrateProc(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

void MB5Ev_ItemNKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    UnkVibrateProcess *vib;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = MB5Ev_YesNoChoiceGet(2, mb5_comNKinokoTarget);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = MBPlayerRankRandGet(0);
    } else if (choice < 0) {
        targetPlayer = MBPlayerRankRandGet(0);
    } else {
        targetPlayer = choice;
    }

    GwSystem.slow_dice_flags |= 1 << targetPlayer;
    player = MBPlayerGet(targetPlayer);

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        mbTauntOffF = 1;
        HuPrcSleep(0x10);
    }

    MB5Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    MB5Ev_KinokoMarkCreate(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    MB5Ev_KinokoMarkObjCreate(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(MB5Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (player->rev & 0x80) {
        MBDlgWinExec(-1, 0x3A09);
    }
    MBDlgWinExec(-1, 0x3A06);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        mbTauntOffF = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        GWBoardFlagSet(0x10);
        MBDlgWinExec(-1, 0x3A07);
        for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
            HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        MB5Ev_KinokoMarkKill(loc->current_player_index);
        MBSaiKill(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void MB5Ev_RKinokoTurnStart(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x80) {
        if ((player->rev & 0x40) || ((player->rev & 0x10) && !(player->rev & 4))) {
            MBDlgWinExec(-1, 0x421C);
        } else {
            MBDlgWinExec(-1, 0x3A03);
        }
        if (player->rev & 4) {
            if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB5Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB5Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void MB5Ev_ItemKoopaRKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        MBSaiKill(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (mb5ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB5Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB5Ev_ItemRKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;
    UnkVibrateProcess *vib;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = MB5Ev_YesNoChoiceGet(2, mb5_comRKinokoTarget);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = MBPlayerRankRandGet(0);
    } else if (choice < 0) {
        targetPlayer = MBPlayerRankRandGet(0);
    } else {
        targetPlayer = choice;
    }

    player = MBPlayerGet(targetPlayer);
    player->rev |= 0x80;

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        mbTauntOffF = 1;
        HuPrcSleep(0x10);
    }

    MB5Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    MB5Ev_KinokoMarkCreate(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb5ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    MB5Ev_KinokoMarkObjCreate(targetPlayer);
    omAddPrcObj(MB5Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (((previousPlayer == targetPlayer) && (MBSaiTypeGet(previousPlayer) == 3)) ||
        ((GwSystem.slow_dice_flags >> targetPlayer) & 1)) {
        MBDlgWinExec(-1, 0x3A05);
    }
    MBDlgWinExec(-1, 0x3A02);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        mbTauntOffF = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        MB5Ev_RKinokoTurnStart();
    }
}

void MB5Ev_ItemRobBox(void) {
    char playerNames[4][16];
    u8 choices[16];
    Object *chest;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer = 0;
    s32 itemSlot;
    s32 i;
    f32 angle;
    u32 *motion;

    MB5Ev_ItemUseFadeOut();
    chest = MBModelCreate(0x21, NULL);
    Hu3DModelScaleSet(chest->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&chest->coords, &MBPlayerGet(-1)->player_obj->coords);
    Hu3DMotionAttrSet(chest->omObj1->model[0], 2, 1);
    chest->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (chest->velocity.x > 30.0f) {
        chest->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    if (targetPlayer != 0) {
        for (i = 0; i < 1081; i += 30) {
            angle = sindf((f32)i) / 2.0f + 1.0f;
            HuVecCopyXYZ(&chest->scale, angle, sindf((f32)i) / 2.0f + 1.0f,
                         sindf((f32)i) / 2.0f + 1.0f);
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x149);
    Hu3DMotionAttrSet(chest->omObj1->model[0], 1, 0);
    HuPrcSleep(20);

    for (i = 0; i < 4; i++) {
        if (GwSystem.current_player_index == i) {
            playerNames[i][0] = 1;
            choices[i] = 0;
        } else {
            playerNames[i][0] = 8;
            choices[i] = 1;
        }
        MBCharNameMesConv(i, &playerNames[i][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = MB5_ComItemTargetChoice(choices, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = MBPlayerRankRandGet(1);
    }

    if (GwPlayer[targetPlayer].itemNo[0] == -1) {
        MBPlayerMotionSet(-1, 3, 0);
        PlayerFXPlay(0x286, system->current_player_index);
        HuPrcSleep(60);
        MBCharNameMesConv(targetPlayer, playerNames[0]);
        MBWinInsertOpen(0x3A0F, playerNames[0], 0, 0, 0, 0);
        MBWinKeyWait(system->current_player_index);
        MBWinClose();
        MBPlayerMotionShiftSet(-1, -1, 0, 10, 2);
        MBModelKill(chest);
        GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
        MBItemRemoveEmpty(system->current_player_index);
        return;
    }

    itemSlot = MBItemFindEmpty(targetPlayer);
    if (itemSlot == -1) {
        itemSlot = 3;
    }
    itemSlot = MBRand((f32)itemSlot);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] =
        GwPlayer[targetPlayer].itemNo[itemSlot];
    GwPlayer[targetPlayer].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(targetPlayer);
    MBPlayerVibrate((s16)targetPlayer, 3);
    if (MBItemSelNoGet() == itemSlot) {
        MBStatusItemTPLvlSet(targetPlayer, MBItemSelNoGet(), 0);
    }
    MBStatusItemSprKill(-1);
    MBStatusItemPosSet(system->current_player_index, MBItemSelNoGet(),
                       mb5ev_robBoxItemStartPosTbl[system->current_player_index].x,
                       mb5ev_robBoxItemStartPosTbl[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB5Ev_ItemMoveCreate(-1,
                                     mb5ev_robBoxItemStartPosTbl[system->current_player_index].x,
                                     mb5ev_robBoxItemStartPosTbl[system->current_player_index].y,
                                     mb5ev_robBoxItemEndPosTbl[system->current_player_index].x,
                                     mb5ev_robBoxItemEndPosTbl[system->current_player_index].y, 5));
    HuPrcChildWatch();
    PlayerFXPlay(0x274, system->current_player_index);
    MBPlayerMotionLoad(system->current_player_index, 5, 0x31);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(50);
    MBPlayerMotionShiftSet(system->current_player_index, -1, 0, 10, 2);
    HuPrcSleep(11);
    motion = mbPlayerMotTbl[0];
    for (i = 6; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    MBModelKill(chest);
    MBDlgWinInsertCreate(-1, 0x3A0D, GwPlayer[targetPlayer].chr + 0x1C00,
                         GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MB5Ev_ItemCursorReturn();
}

void MB5Ev_PlayerLinkSet(GW_PLAYER *player, s32 index, s16 paths[][6]) {
    s16 *path = paths[index];

    player->clink = *path++;
    player->cidx = *path++;
    player->nlink = *path++;
    player->nidx = *path++;
    player->blink = *path++;
    player->bidx = *path;
}

void MB5Ev_ActionTimeSpr(void) {
    struct {
        s32 choiceAnims[4];
        s32 charAnims[4];
        s32 grps[4];
    } spr;
    s32 titleAnim;
    s32 frameAnim;
    s32 titleGrp;
    Process *process;
    Unk3 *helpWin;
    void *data;
    s32 grp;
    s32 i;
    s32 j;
    s32 count;
    s32 wrapped;
    s32 fading;
    s32 mask;
    s32 clampedAlpha;
    s32 alpha;
    f32 angle;
    f32 speed;

    process = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    spr.choiceAnims[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    spr.choiceAnims[1] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    spr.choiceAnims[2] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    spr.choiceAnims[3] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    frameAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        spr.charAnims[i] = HuSprAnimRead(data);
        DataClose(data);
    }

    titleGrp = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(titleGrp, 0, titleAnim, 0);
    HuSprAttrReset(titleGrp, 0, 0xFFFF);
    HuSprAttrSet(titleGrp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(titleGrp, 0, 0x1000);
    HuSprPosSet(titleGrp, 0, 0xA0, 0x5A);

    angle = 0.0f;
    speed = 30.0f;
    count = 0;
    wrapped = 0;

    while (1) {
        if (angle >= 90.0f && wrapped == 0) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(titleGrp, 0, HUSPR_ATTR_FLIPY);
        } else {
            HuSprAttrReset(titleGrp, 0, HUSPR_ATTR_FLIPY);
        }
        HuSprScaleSet(titleGrp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprAttrReset(titleGrp, 0, HUSPR_ATTR_FLIPY);
    HuSprScaleSet(titleGrp, 0, 1.0f, 1.0f);
    helpWin = MBHelpWinCreate(0x14, 0xA0, 1);

    for (i = 0; i < 4; i++) {
        grp = spr.grps[i] = HuSprGrpCreate(6, 5);
        HuSprGrpMemberSet(grp, 0, frameAnim, 0);
        HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(grp, 0, 0xFFFF);
        if (mb5ev_cartJumpStateTbl[i] != 0) {
            HuSprAttrSet(grp, 0, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(grp, 0);
        }
        HuSprPriSet(grp, 0, 0x1000);
        HuSprParentSet(grp, 0, -1);
        HuSprGrpMemberSet(grp, 1, spr.charAnims[i], 0);
        HuSprAnimModeSet(grp, 1, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(grp, 1, 0xFFFF);
        if (mb5ev_cartJumpStateTbl[i] != 0) {
            HuSprAttrSet(grp, 1, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(grp, 1);
        }
        HuSprPriSet(grp, 1, 0x1000);
        HuSprPosSet(grp, 1, 0, -9);
        HuSprParentSet(grp, 1, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(grp, j + 2, spr.choiceAnims[j], 0);
            HuSprAnimModeSet(grp, j + 2, HUSPR_ANIM_MODE_BANK);
            HuSprAttrReset(grp, j + 2, 0xFFFF);
            if (mb5ev_cartJumpStateTbl[i] == j + 1) {
                HuSprAttrSet(grp, j + 2, HUSPR_ATTR_FILTER_BILERP);
            } else {
                HuSprDispOff(grp, j + 2);
            }
            HuSprPriSet(grp, j + 2, 0x1000);
            HuSprPosSet(grp, j + 2, 0, 9);
            HuSprParentSet(grp, j + 2, 0);
        }
        HuSprPosSet(grp, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);

    angle = 90.0f;
    count = 0;
    fading = 0;
    wrapped = 0;
    alpha = 255;

    while (1) {
        if (angle >= 360.0f && wrapped == 0) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if (fading == 0 && count != 0) {
            if (angle >= 90.0f && angle < 180.0f) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            mask = -(alpha > 0);
            clampedAlpha = mask & alpha;
            alpha = clampedAlpha;
        }
        HuSprTPLvlSet(titleGrp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprScaleSet(titleGrp, 0, 1.0f, 0.0f);
    HuSprGrpKill(titleGrp);
    HuSprAnimKill(titleAnim);
    process->user_data = (void *)1;

    i = 0;
    while (1) {
        switch (mb5ev_cartJumpStateTbl[i]) {
            case 0:
                for (j = 0; j < 6; j++) {
                    HuSprDispOff(spr.grps[i], j);
                }
                break;
            case 1:
                for (j = 0; j < 6; j++) {
                    HuSprDispOn(spr.grps[i], j);
                }
                for (j = 0; j < 4; j++) {
                    HuSprDispOff(spr.grps[i], j + 2);
                }
                HuSprDispOn(spr.grps[i], 2);
                break;
            case 2:
                for (j = 0; j < 6; j++) {
                    HuSprDispOn(spr.grps[i], j);
                }
                for (j = 0; j < 4; j++) {
                    HuSprDispOff(spr.grps[i], j + 2);
                }
                HuSprDispOn(spr.grps[i], 3);
                break;
            case 3:
                for (j = 0; j < 6; j++) {
                    HuSprDispOn(spr.grps[i], j);
                }
                for (j = 0; j < 4; j++) {
                    HuSprDispOff(spr.grps[i], j + 2);
                }
                HuSprDispOn(spr.grps[i], 4);
                break;
            case 4:
                for (j = 0; j < 6; j++) {
                    HuSprDispOn(spr.grps[i], j);
                }
                for (j = 0; j < 4; j++) {
                    HuSprDispOff(spr.grps[i], j + 2);
                }
                HuSprDispOn(spr.grps[i], 5);
                break;
            default:
                goto end;
        }
        i++;
        if (i >= 4) {
            i = 0;
            HuPrcVSleep();
        }
    }
end:
    MBHelpWinKill(helpWin);
    HuSprAnimKill(frameAnim);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(spr.choiceAnims[i]);
        HuSprAnimKill(spr.charAnims[i]);
        HuSprGrpKill(spr.grps[i]);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_Hatena(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x2:
        case 0x4C:
            MB5Ev_HatenaWhomp();
            break;
        case 0x1A:
        case 0x1E:
        case 0x35:
        case 0x4D:
        case 0x51:
        case 0x57:
            MB5Ev_HatenaCartA();
            break;
        default:
            MB5Ev_HatenaCartB();
            break;
    }
    omDelPrcObj(NULL);
}

void MB5_WhompItemShuffle(void) {
    s32 r = MBRand(10.0f);
    s16 itemIndex;

    if (r < 6) {
        itemIndex = 0;
    } else if (r < 8) {
        itemIndex = 1;
    } else {
        itemIndex = 2;
    }
    GwSystem.boardData.halfWordBytes[1] = itemIndex;
    GwSystem.boardData.halfWordBytes[2] = -1;
}

void MB5Ev_WhompExec(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    DecisionTreeNonLeafNode *tree;
    s32 item;
    s32 choice;
    s32 group;
    s32 anim;
    void *data;
    s32 tpLvl;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x8E:
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                MB5Ev_BranchMain(mb5ev_branch4Masu, mb5ev_branch4Link, mb5ev_branch4ComTree);
                return;
            }
            break;
        case 0x7C:
            if (GwSystem.boardData.halfWordBytes[0] == 0) {
                MB5Ev_BranchMain(mb5ev_branch9Masu, mb5ev_branch9Link, mb5ev_branch9ComTree);
                return;
            }
            break;
        case 0x3:
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                return;
            }
            break;
        default:
            if (GwSystem.boardData.halfWordBytes[0] == 0) {
                MBMoveNextMasuSet(-1, 15, 6);
                player->rev |= 1;
                return;
            }
            break;
    }

    MBSaiNumKill(system->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x3:
        case 0x8E:
            MBPlayerRotMasuStart(-1, 8, 0x8D);
            break;
        default:
            MBPlayerRotMasuStart(-1, 8, 0x8B);
            break;
    }
    HuPrcSleep(8);

    switch (GwSystem.boardData.halfWordBytes[1]) {
        case 0:
            item = 1;
            break;
        case 1:
            item = 0;
            break;
        default:
            item = 2;
            break;
    }
    GwSystem.boardData.halfWordBytes[2] = GwSystem.boardData.halfWordBytes[1];
    HuAudFXPlay(0x1AC);

    if (MBItemFind(system->current_player_index, item) != -1) {
        MBDlgWinExec(0xC, 0xC01);
    retry:
        MBDlgWinInsertCreate(0xC, 0xC02, GwSystem.boardData.halfWordBytes[1] + 0xC03, 0, 0, 0, 0);
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            case 0x8E:
                tree = mb5ev_whompMasu142ComTree;
                break;
            case 0x3:
                tree = mb5ev_whompMasu3ComTree;
                break;
            case 0x7C:
                tree = mb5ev_whompMasu124ComTree;
                break;
            default:
                tree = mb5ev_whompMasu129ComTree;
                break;
        }
        choice = MB5Ev_YesNoChoiceGet((s32)tree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                HuPrcSleep(20);
                group = HuSprGrpCreate(1, 5);
                data = DataRead(mbItemIconSprTbl[item]);
                anim = HuSprAnimRead(data);
                DataClose(data);
                HuSprGrpMemberSet(group, 0, anim, 0);
                HuSprPriSet(group, 0, 10);
                HuSprAnimModeSet(group, 0, HUSPR_ANIM_MODE_STOP);
                HuSprAttrSet(group, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
                HuSprPosSet(group, 0, 160, 90);
                HuSprTPLvlSet(group, 0, 0);
                GwPlayer[system->current_player_index].itemNo[MBItemFind(system->current_player_index, item)] = -1;
                MBItemRemoveEmpty(system->current_player_index);
                MBStatusItemIconSprReinit(-1);
                HuAudFXPlay(0x145);
                for (tpLvl = 0; tpLvl < 0x100; tpLvl += 25) {
                    HuSprTPLvlSet(group, 0, tpLvl);
                    HuPrcVSleep();
                }
                HuSprTPLvlSet(group, 0, 0x100);
                HuPrcSleep(30);
                for (tpLvl = 0x100; tpLvl > 0; tpLvl -= 12) {
                    HuSprTPLvlSet(group, 0, tpLvl);
                    HuPrcVSleep();
                }
                HuSprAnimKill(anim);
                HuSprGrpKill(group);
                MBDlgWinExec(0xC, 0xC06);

                mb5_whompMoveF = 1;
                while (mb5_whompMoveF != 0) {
                    HuPrcVSleep();
                }
                MB5_WhompItemShuffle();
                MBSaiNumShow(system->current_player_index);
                HuPrcSleep(10);

                switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
                    case 0x8E:
                        MB5Ev_BranchMain(mb5ev_branch4Masu, mb5ev_branch4Link, mb5ev_branch4ComTree);
                        break;
                    case 0x7C:
                        MB5Ev_BranchMain(mb5ev_branch9Masu, mb5ev_branch9Link, mb5ev_branch9ComTree);
                        break;
                    case 0x3:
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 15, 6);
                        player->rev |= 1;
                        break;
                }
                return;
            case 1:
                MBDlgWinExec(0xC, 0xC07);
                break;
            default:
                MB5_MapScroll();
                goto retry;
        }
    } else {
        MBDlgWinInsertCreate(0xC, 0xC08, GwSystem.boardData.halfWordBytes[1] + 0xC03, 0, 0, 0, 0);
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBDlgWinKill();
    }

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x8E:
            if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 2) {
                MBMoveNextMasuSet(-1, 4, 0);
                player->rev &= ~1;
            } else {
                MBMoveNextMasuSet(-1, 3, 3);
                player->rev |= 1;
            }
            break;
        case 0x7C:
            if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4C) {
                MBMoveNextMasuSet(-1, 12, 0);
                player->rev &= ~1;
            } else {
                MBMoveNextMasuSet(-1, 15, 3);
                player->rev |= 1;
            }
            break;
        case 0x3:
            MBMoveNextMasuSet(-1, 14, 3);
            player->rev &= ~1;
            break;
        default:
            MBMoveNextMasuSet(-1, 16, 1);
            player->rev &= ~1;
            break;
    }
    MBSaiNumShow(system->current_player_index);
    HuPrcSleep(10);
}

void MB5Ev_HatenaWhomp(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    SpaceData *space;
    Vec pos;

    HuPrcSleep(20);
    MBBackThreadPriLowSet();
    space = MBMasuGet(0x62);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 10));
    HuPrcChildWatch();
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);

    mb5_whompMoveF = 1;
    while (mb5_whompMoveF != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0xC00);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &player->player_obj->coords, &pos, 10));
    HuPrcChildWatch();
    MBCameraFocusModeSet(1);
    MBBackThreadPriHighSet();
}

void MB5_WhompRockProc(void) {
    s32 type = (s32)HuPrcCurrentGet()->user_data;
    Object *model;

    model = MBModelCreate(0x4D, NULL);
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &MBMasuGet(0x62)->coords);
    model->velocity.x = 150.0f;

    switch (type) {
        case 0:
            model->coords.z -= 30.0f;
            HuPrcSleep(2);
            break;
        case 1:
            model->coords.x += 20.0f;
            model->coords.z += 30.0f;
            break;
        default:
            model->coords.x -= 15.0f;
            model->coords.z += 40.0f;
            HuPrcSleep(5);
            break;
    }

    MBModelJumpSet(model, 0.0f, -1.0f);
    MBModelJumpWait(model);
    MBModelKill(model);
    omDelPrcObj(NULL);
}

void MB5_WhompProc(void) {
    Object *model;
    GW_PLAYER *player;
    Process *prc;
    Vec pos;
    f32 baseZ;
    f32 angle;
    s32 i;
    s32 shook;
    s32 focusMode;

    model = MBModelCreate(0xB, mb5_whompMot);
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &MBMasuGet(0x62)->coords);
    HuVecCopyXYZ(&model->scale, 2.5f, 2.5f, 2.5f);
    HuVecCopyXYZ(&model->rot, -1.0f, 0.0f, 0.0f);
    if (GwSystem.boardData.halfWordBytes[0] != 0) {
        MBMotionSet(model, 1, 2);
    } else {
        MBMotionSet(model, 2, 2);
    }

    while (TRUE) {
        if (mb5_whompMoveF != 0) {
            player = MBPlayerGet(-1);
            HuAudFXPlay(0x1AC);
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                MBMotionSet(model, 0, 0);
                while (MBMotionCheck(model) == 0) {
                    HuPrcVSleep();
                }
                GwSystem.boardData.halfWordBytes[0] = 0;
            } else {
                MBMotionSet(model, 0, 4);
                Hu3DMotionTimeSet(
                    model->omObj1->model[0], Hu3DMotion[Hu3DData[model->omObj1->model[0]].motId].unk02);
                while (MBMotionStartCheck(model) == 0) {
                    HuPrcVSleep();
                }
                GwSystem.boardData.halfWordBytes[0] = 1;
            }
            HuAudFXPlay(0x1AD);

            for (i = 0; i < 3; i++) {
                prc = omAddPrcObj(MB5_WhompRockProc, 0x4800, 0, 0);
                prc->user_data = (void *)i;
                HuPrcChildLink(HuPrcCurrentGet(), prc);
            }

            MBPlayerVibrate(-1, 3);
            HuVecCopyXYZ(&pos, mbCameraFocusPos.x, mbCameraFocusPos.y, mbCameraFocusPos.z);
            shook = FALSE;
            focusMode = MBCameraFocusModeGet();
            MBCameraFocusModeSet(4);
            MBCameraFocusVecSet(&pos);
            baseZ = pos.z;
            for (angle = 0.0f; angle < 900.0f; angle += 90.0f) {
                HuVecCopyXYZ(&pos, pos.x, pos.y, baseZ + sindf(angle) * 3.0f);
                if (!shook && angle > 450.0f) {
                    MBModelJumpSet(player->player_obj, 5.0f, -1.0f);
                    shook = TRUE;
                }
                HuPrcVSleep();
            }
            HuVecCopyXYZ(&pos, pos.x, pos.y, pos.z);
            MBCameraFocusModeSet(focusMode);
            MBModelJumpWait(player->player_obj);
            HuPrcChildWatch();
            if (GwSystem.boardData.halfWordBytes[0] != 0) {
                MBMotionSet(model, 1, 2);
            } else {
                MBMotionSet(model, 2, 2);
            }
            mb5_whompMoveF = 0;
        }
        HuPrcVSleep();
    }
}

void MB5_CartBlockProc(void) {
    Object *model;

    model = MBModelCreate(0xD, NULL);
    mb5_cartBlockMdlA = model;
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &MBMasuGet(GwSystem.boardData.halfWordBytes[3] != 0 ? 0x7F : 0x97)->coords);
    HuVecCopyXYZ(&model->scale, 1.3f, 1.3f, 1.3f);

    model = MBModelCreate(0xD, NULL);
    mb5_cartBlockMdlB = model;
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &MBMasuGet(GwSystem.boardData.halfWordBytes[4] != 0 ? 0x85 : 0x71)->coords);
    HuVecCopyXYZ(&model->scale, 1.3f, 1.3f, 1.3f);

    while (TRUE) {
        HuPrcVSleep();
    }
}

void MB5Ev_CartPlayerEscapeProc(void) {
    PlayerReactWork *work = HuPrcCurrentGet()->user_data;
    Object *model = mb5ev_cartMdl;
    GW_PLAYER *player = MBPlayerGet(work->playerNo);
    Object *playerObj = player->player_obj;
    s32 unk4 = work->unk4;
    s32 order = work->order;
    s32 type = work->type;
    Process *process = HuPrcCurrentGet();
    UnkVibrateProcess *vib;
    SpaceData *start;
    SpaceData *end;
    Vec pos;
    Vec *p;
    f32 *ofs;
    s32 camMasu;

    switch (type) {
        case 0:
            camMasu = 0x92;
            break;
        case 1:
            camMasu = 0x91;
            break;
        case 2:
            camMasu = 0x90;
            break;
        default:
            camMasu = 0x8F;
            break;
    }
    MBPlayerRotMasuStart(work->playerNo, 8, camMasu);

    while (HuVecDistance(&playerObj->coords, &model->coords) > order * 20.0f + 30.0f) {
        HuPrcVSleep();
    }

    vib = MBPlayerVibrateObjCreate(work->playerNo, 0, 5);
    PlayerFXPlay(0x286, work->playerNo);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, 1, 2);
    } else {
        MBMotionSet(playerObj, 1, 2);
    }

    switch (type) {
        case 0:
            start = MBMasuGet(0x35);
            end = MBMasuGet(0x36);
            break;
        case 1:
            start = MBMasuGet(0x1A);
            end = MBMasuGet(0x1B);
            break;
        case 2:
            start = MBMasuGet(0x82);
            end = MBMasuGet(0x43);
            break;
        default:
            start = MBMasuGet(0x6F);
            end = MBMasuGet(0x11);
            break;
    }

    HuVecCopy3F(&pos, &start->coords);
    MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
    // Keep the movement stages grouped for the original compiler's register allocation.
    do {
        HuPrcChildLink(process, MBVecSpeedMove2Create(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
        HuPrcChildWatch();

        HuVecCopy3F(&pos, &end->coords);
        p = &pos;
        ofs = &mb5ev_cartEscapeOfsTbl[unk4 + order][1];
    } while (0);
    p->x += *--ofs;
    p->z += ofs[1];
    MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
    HuPrcChildLink(process, MBVecSpeedMoveCreate(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
    HuPrcChildWatch();

    MBPlayerVibrateObjKill(vib);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(playerObj, -1, 2);
    }

    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
    do {
        MBVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
        MB5Ev_PlayerLinkSet(player, type, mb5ev_cartEscapeLinkTbl);
    } while (0);
    omDelPrcObj(NULL);
}

void MB5Ev_CartPlayerEscapeSideProc(void) {
    PlayerReactWork *work = HuPrcCurrentGet()->user_data;
    Object *model = mb5ev_cartMdl;
    GW_PLAYER *player = MBPlayerGet(work->playerNo);
    Object *playerObj = player->player_obj;
    s32 order = work->order;
    s32 type = work->type;
    Process *process = HuPrcCurrentGet();
    SpaceData *start;
    SpaceData *end;
    Vec pos;
    s32 camMasu;

    switch (type) {
        case 0:
            camMasu = 0x92;
            break;
        case 1:
            camMasu = 0x91;
            break;
        case 2:
            camMasu = 0x90;
            break;
        default:
            camMasu = 0x8F;
            break;
    }
    MBPlayerRotMasuStart(work->playerNo, 8, camMasu);

    while (HuVecDistance(&playerObj->coords, &model->coords) > order * 20.0f + 30.0f) {
        HuPrcVSleep();
    }

    PlayerFXPlay(0x286, work->playerNo);
    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, 1, 2);
    } else {
        MBMotionSet(playerObj, 1, 2);
    }

    switch (type) {
        case 0:
            start = MBMasuGet(0x35);
            end = MBMasuGet(0x36);
            break;
        case 1:
            start = MBMasuGet(0x1A);
            end = MBMasuGet(0x1B);
            break;
        case 2:
            start = MBMasuGet(0x40);
            end = MBMasuGet(0x43);
            break;
        default:
            start = MBMasuGet(0x10);
            end = MBMasuGet(0x11);
            break;
    }

    HuVecCopy3F(&pos, &start->coords);
    MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
    HuPrcChildLink(process, MBVecSpeedMove2Create(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
    HuPrcChildWatch();

    HuVecCopy3F(&pos, &start->coords);
    if (type == 2) {
        pos.z += -30.0f;
    } else {
        pos.z += 30.0f;
    }
    MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
    HuPrcChildLink(process, MBVecSpeedMoveCreate(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
    HuPrcChildWatch();

    MBPlayerMotionSet(-1, -1, 2);
    if (type == 2) {
        HuVecCopyXYZ(&pos, -1.0f, 0.0f, 0.5f);
    } else {
        HuVecCopyXYZ(&pos, 1.0f, 0.0f, -0.5f);
    }
    MBVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
    HuPrcSleep(30);
    MBPlayerMotionSet(-1, 0, 2);

    HuVecCopy3F(&pos, &end->coords);
    if (type == 2) {
        pos.x += mb5ev_cartSideOfsTblB[0];
        pos.z += mb5ev_cartSideOfsTblB[1];
    } else {
        pos.x += mb5ev_cartSideOfsTblA[0];
        pos.z += mb5ev_cartSideOfsTblA[1];
    }
    MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
    HuPrcChildLink(process, MBVecSpeedMoveCreate(&playerObj->coords, &pos, &playerObj->coords, 1.5f));
    HuPrcChildWatch();

    if (work->playerNo == GwSystem.current_player_index) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(playerObj, -1, 2);
    }

    HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
    MBVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
    MB5Ev_PlayerLinkSet(player, type, mb5ev_cartEscapeLinkTbl);
    omDelPrcObj(NULL);
}

void MB5Ev_CartBlockShakeProc(void) {
    s32 type = (s32)HuPrcCurrentGet()->user_data;
    SpaceData *space;
    Object *model;
    f32 angle;

    switch (type) {
        case 0:
            space = MBMasuGet(0x80);
            model = mb5_cartBlockMdlA;
            break;
        case 1:
            space = MBMasuGet(0x6E);
            model = mb5_cartBlockMdlA;
            break;
        case 2:
            space = MBMasuGet(0x86);
            model = mb5_cartBlockMdlB;
            break;
        default:
            space = MBMasuGet(0x72);
            model = mb5_cartBlockMdlB;
            break;
    }

    angle = 0.0f;
    while (TRUE) {
        model->omObj1->rot.x = sindf(angle) * 5.0f;
        angle += 45.0f;
        if (angle < 360.0f) {
            angle -= 360.0f;
        }
        if (ABS(space->coords.x - model->coords.x) <= 2.0f) {
            break;
        }
        HuPrcVSleep();
    }
    model->omObj1->rot.x = 0.0f;
    omDelPrcObj(NULL);
}

void MB5Ev_CartBlockPushProc(void) {
    s32 type = (s32)HuPrcCurrentGet()->user_data;
    Object *other = mb5ev_cartMdl;
    Object *model;
    SpaceData *space;
    Process *prc;
    Vec pos;
    f32 speed;
    s32 bounced;

    switch (type) {
        case 0:
        case 1:
            model = mb5_cartBlockMdlA;
            break;
        default:
            model = mb5_cartBlockMdlB;
            break;
    }

    HuVecCopy3F(&pos, &model->coords);
    pos.z = other->coords.z;

    while (TRUE) {
        switch (type) {
            case 0:
            case 2:
                if (other->coords.x - model->coords.x < -5.0f) {
                    goto moved;
                }
                break;
            default:
                if (model->coords.x - other->coords.x < -5.0f) {
                    goto moved;
                }
                break;
        }
        HuPrcVSleep();
    }
moved:
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &pos, &model->coords, 10));
    bounced = FALSE;
    speed = 10.0f;
    while (TRUE) {
        model->velocity.x += speed;
        if (bounced && model->velocity.x <= 7.5f) {
            break;
        }
        if (model->velocity.x > 7.5f) {
            bounced = TRUE;
        }
        HuPrcVSleep();
        speed -= 2.0f;
    }
    model->velocity.x = 7.5f;
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);

    switch (type) {
        case 0:
            space = MBMasuGet(0x80);
            break;
        case 1:
            space = MBMasuGet(0x6E);
            break;
        case 2:
            space = MBMasuGet(0x86);
            break;
        default:
            space = MBMasuGet(0x72);
            break;
    }
    HuVecCopy3F(&pos, &space->coords);
    prc = omAddPrcObj(MB5Ev_CartBlockShakeProc, 0x4800, 0, 0);
    prc->user_data = (void *)type;

    while (TRUE) {
        switch (type) {
            case 0:
            case 2:
                model->coords.x -= 2.0f;
                break;
            default:
                model->coords.x += 2.0f;
                break;
        }
        if (ABS(space->coords.x - model->coords.x) <= 2.0f) {
            break;
        }
        HuPrcVSleep();
    }

    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &pos, &model->coords, 10));
    bounced = FALSE;
    speed = 8.0f;
    while (TRUE) {
        model->velocity.x += speed;
        if (bounced && model->velocity.x <= 0.0f) {
            break;
        }
        if (model->velocity.x > 0.0f) {
            bounced = TRUE;
        }
        HuPrcVSleep();
        speed -= 2.0f;
    }
    model->velocity.x = 0.0f;
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

void MB5Ev_CartJumpRotProc(void) {
    s32 masuId = (s32)HuPrcCurrentGet()->user_data;
    s16 masuAbsIndex;

    HuPrcSleep(10);

    switch (masuId) {
        case 0:
            masuAbsIndex = 0x91;
            break;
        case 1:
            masuAbsIndex = 0x92;
            break;
        case 2:
            masuAbsIndex = 0x8F;
            break;
        default:
            masuAbsIndex = 0x90;
    }

    MBPlayerRotMasuStart(-1, 8, masuAbsIndex);
    omDelPrcObj(NULL);
}

void MB5Ev_CartJumpProc(void) {
    s32 type = (s32)HuPrcCurrentGet()->user_data;
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *model = mb5ev_cartMdl;
    SpaceData *space;
    Vec pos;
    Vec dir;
    s32 pressed = FALSE;
    s32 state;
    s32 bounced;
    s32 turned;
    s16 masuId;
    f32 speed;

    HuVecCopy3F(&pos, &player->player_obj->coords);
    pos.z = model->coords.z;
    state = 0;

    while (TRUE) {
        switch (type) {
            case 0:
            case 2:
                if (model->coords.x - player->player_obj->coords.x < 46.0f && state != 2) {
                    mb5ev_cartJumpStateTbl[system->current_player_index] = 2;
                }
                if (model->coords.x - player->player_obj->coords.x < 42.0f) {
                    if ((ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) && state == 0) {
                        state = 1;
                        pressed = TRUE;
                    }
                }
                if (model->coords.x - player->player_obj->coords.x < 22.0f) {
                    goto done;
                }
                if (!pressed) {
                    if ((ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) && state != 2) {
                        PlayerFXPlay(0x286, system->current_player_index);
                        state = 2;
                        mb5ev_cartJumpStateTbl[system->current_player_index] = 4;
                        MBPlayerMotionSet(-1, 4, 2);
                    }
                } else {
                    pressed = FALSE;
                }
                break;
            default:
                if (player->player_obj->coords.x - model->coords.x < 46.0f && state != 2) {
                    mb5ev_cartJumpStateTbl[system->current_player_index] = 2;
                }
                if (player->player_obj->coords.x - model->coords.x < 42.0f) {
                    if ((ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) && state == 0) {
                        state = 1;
                        pressed = TRUE;
                    }
                }
                if (player->player_obj->coords.x - model->coords.x < 22.0f) {
                    goto done;
                }
                if (!pressed) {
                    if ((ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) && state != 2) {
                        PlayerFXPlay(0x286, system->current_player_index);
                        state = 2;
                        mb5ev_cartJumpStateTbl[system->current_player_index] = 4;
                        MBPlayerMotionSet(-1, 4, 2);
                    }
                } else {
                    pressed = FALSE;
                }
                break;
        }
        HuPrcVSleep();
    }
done:
    if (MBPlayerComCheck(system->current_player_index)) {
        if (MBComTreeExec(mb5ev_cartJumpComTree) == 0) {
            state = 1;
        }
    }

    if (state == 1) {
        PlayerFXPlay(0x3A, system->current_player_index);
        mb5ev_cartJumpStateTbl[system->current_player_index] = 3;
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &pos, &player->player_obj->coords, 10));
        MBPlayerMotionSet(-1, 2, 0);
        bounced = FALSE;
        speed = 10.0f;
        while (TRUE) {
            player->player_obj->velocity.x += speed;
            if (bounced && player->player_obj->velocity.x <= 7.5f) {
                break;
            }
            if (player->player_obj->velocity.x > 7.5f) {
                bounced = TRUE;
            }
            HuPrcVSleep();
            speed -= 2.0f;
        }
        player->player_obj->velocity.x = 7.5f;
        PlayerFXPlay(0x31, system->current_player_index);
        PlayerFXPlay(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        omAddPrcObj(MB5Ev_CartJumpRotProc, 0x4800, 0, 0)->user_data = (void *)type;
        mb5ev_cartJumpF = 1;

        switch (type) {
            case 0:
                masuId = 0x7F;
                break;
            case 1:
                masuId = 0x97;
                break;
            case 2:
                masuId = 0x85;
                break;
            default:
                masuId = 0x71;
                break;
        }
        turned = FALSE;
        space = MBMasuGet(masuId);
        HuVecCopy3F(&pos, &space->coords);

        while (TRUE) {
            switch (type) {
                case 0:
                case 2:
                    player->player_obj->coords.x -= 2.0f;
                    break;
                default:
                    player->player_obj->coords.x += 2.0f;
                    break;
            }
            if (ABS(player->player_obj->coords.x - space->coords.x) <= 2.0f) {
                break;
            }
            if (ABS(player->player_obj->coords.x - space->coords.x) <= 24.0f && !turned) {
                turned = TRUE;
                HuVecCopyXYZ(&dir, 0.0f, 0.0f, -1.0f);
                MBVecRotLerpCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, 5);
            }
            HuPrcVSleep();
        }

        PlayerFXPlay(0x3A, system->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &pos, &player->player_obj->coords, 10));
        MBPlayerMotionSet(-1, 2, 0);
        bounced = FALSE;
        speed = 8.0f;
        while (TRUE) {
            player->player_obj->velocity.x += speed;
            if (bounced && player->player_obj->velocity.x <= 0.0f) {
                break;
            }
            if (player->player_obj->velocity.x > 0.0f) {
                bounced = TRUE;
            }
            HuPrcVSleep();
            speed -= 2.0f;
        }
        player->player_obj->velocity.x = 0.0f;
        PlayerFXPlay(0x31, system->current_player_index);
        PlayerFXPlay(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
        MBVecRotLerpCreate(&player->player_obj->rot, &pos, &player->player_obj->rot, 10);
    } else if (state == 0) {
        PlayerFXPlay(0x286, system->current_player_index);
        mb5ev_cartJumpStateTbl[system->current_player_index] = 4;
        MBPlayerMotionSet(-1, 4, 2);
    }
    omDelPrcObj(NULL);
}

void MB5Ev_CartSeProc(void) {
    s32 type = (s32)HuPrcCurrentGet()->user_data;
    Object *model = mb5ev_cartMdl;
    s16 seNo = HuAudFXPlay(0x1B0);
    SpaceData *start;
    SpaceData *end;
    SpaceData *target;
    s16 pan;

    switch (type) {
        case 0:
        case 1:
            start = MBMasuGet(0x91);
            end = MBMasuGet(0x92);
            break;
        default:
            start = MBMasuGet(0x8F);
            end = MBMasuGet(0x90);
            break;
    }

    switch (type) {
        case 0:
            target = MBMasuGet(0x91);
            break;
        case 1:
            target = MBMasuGet(0x92);
            break;
        case 2:
            target = MBMasuGet(0x8F);
            break;
        default:
            target = MBMasuGet(0x90);
            break;
    }

    while (model->coords.x != target->coords.x) {
        pan = ABS(start->coords.x - model->coords.x) * 64.0f / ABS(start->coords.x - end->coords.x) + 32.0f;
        HuAudFXPanning(seNo, pan);
        HuPrcVSleep();
    }
    HuAudFXStop(seNo);
    omDelPrcObj(NULL);
}

void MB5Ev_CartRideBranch(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    UnkEA790Struct *win;
    s16 *choices;
    DecisionTreeNonLeafNode *tree;
    s32 sel;
    s32 count;
    s32 i;

    MB5_BranchHelpStart();
    player = MBPlayerGet(-1);

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x7E:
            choices = mb5ev_cartBranchMasu126Tbl;
            break;
        case 0x96:
            choices = mb5ev_cartBranchMasu150Tbl;
            break;
        case 0x84:
            choices = mb5ev_cartBranchMasu132Tbl;
            break;
        default:
            choices = mb5ev_cartBranchMasu112Tbl;
            break;
    }
    win = MBBranchArrowLinkCreate(system->current_player_index, choices);
    MBBranchSelStart(win, system->current_player_index, 0);

    if (MBPlayerComCheck(-1)) {
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            case 0x7E:
                tree = mb5ev_cartBranchMasu126ComTree;
                break;
            case 0x96:
                tree = mb5ev_cartBranchMasu150ComTree;
                break;
            case 0x84:
                tree = mb5ev_cartBranchMasu132ComTree;
                break;
            default:
                tree = mb5ev_cartBranchMasu112ComTree;
                break;
        }
        count = MBComTreeExec(tree);
        for (i = 0; i < count; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }

    sel = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB5_BranchHelpEnd();

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x7E:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 0x10, 0x11);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 8, 1);
                player->rev &= ~1;
            }
            break;
        case 0x96:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 2, 0);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 2, 2);
                player->rev &= ~1;
            }
            break;
        case 0x84:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 9, 0xC);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 0xA, 1);
                player->rev &= ~1;
            }
            break;
        default:
            if (sel == 0) {
                MBMoveNextMasuSet(-1, 5, 0);
                player->rev |= 1;
            } else {
                MBMoveNextMasuSet(-1, 5, 2);
                player->rev &= ~1;
            }
            break;
    }
    omDelPrcObj(NULL);
}

void MB5Ev_CartPlayerEscapeAll(s16 *masuList, s32 type, s32 mode, s32 arg3) {
    s32 order = 0;
    GW_SYSTEM *system = &GwSystem;
    PlayerReactWork *work;
    Process *process;
    s32 i;

    do {
        for (i = 0; i < 4; i++) {
            GW_PLAYER *player;

            if (i == system->current_player_index && mode == 0) {
                continue;
            }
            player = MBPlayerGet(i);
            if (*masuList != MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
                continue;
            }
            if (mode == 2) {
                process = omAddPrcObj(MB5Ev_CartPlayerEscapeSideProc, 0x4800, 0, 0x40);
            } else {
                process = omAddPrcObj(MB5Ev_CartPlayerEscapeProc, 0x4800, 0, 0x40);
            }
            work = HuMemMemoryAlloc(process->heap, 0x20);
            process->user_data = work;
            work->playerNo = i;
            work->unk4 = arg3;
            work->order = order;
            work->type = type;
            order++;
        }
        masuList++;
    } while (*masuList != -1);
}

s32 MB5Ev_CartEscapeMasuShift(s32 arg0) {
    Vec pos[4];
    SpaceData *space;
    GW_PLAYER *player;
    s32 masuId;
    s32 count;
    s32 i;

    switch (arg0) {
        case 0:
            masuId = 0x36;
            space = MBMasuGet(0x36);
            break;
        case 1:
            masuId = 0x1B;
            space = MBMasuGet(0x1B);
            break;
        case 2:
            masuId = 0x43;
            space = MBMasuGet(0x43);
            break;
        default:
            masuId = 0x11;
            space = MBMasuGet(0x11);
            break;
    }

    for (i = 0, count = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (masuId == MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            HuVecCopy3F(&pos[i], &space->coords);
            pos[i].x += mb5ev_cartEscapeOfsTbl[count][0];
            pos[i].z += mb5ev_cartEscapeOfsTbl[count][1];
            MBVecSpeedMoveCreate(&player->player_obj->coords, &pos[i], &player->player_obj->coords, 2.0f);
            count++;
        }
    }
    return count;
}

void MB5Ev_CartRideExec(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    Object *model;
    SpaceData *space;
    SpaceData *target;
    SpaceData *dest;
    Object *bridge;
    DecisionTreeNonLeafNode *tree;
    Vec pos;
    s32 type;
    s32 masu;
    s32 choice;
    s32 i;

    player = MBPlayerGet(-1);
    mb5ev_cartJumpF = 0;
    MBSaiNumKill(system->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x96:
            MBPlayerRotMasuStart(-1, 8, 0x97);
            space = MBMasuGet(0x6E);
            dest = MBMasuGet(0x97);
            bridge = mb5_cartBlockMdlA;
            type = 0;
            break;
        case 0x7E:
            MBPlayerRotMasuStart(-1, 8, 0x7F);
            space = MBMasuGet(0x80);
            dest = MBMasuGet(0x7F);
            bridge = mb5_cartBlockMdlA;
            type = 1;
            break;
        case 0x70:
            MBPlayerRotMasuStart(-1, 8, 0x71);
            space = MBMasuGet(0x72);
            dest = MBMasuGet(0x71);
            bridge = mb5_cartBlockMdlB;
            type = 2;
            break;
        default:
            MBPlayerRotMasuStart(-1, 8, 0x85);
            space = MBMasuGet(0x86);
            dest = MBMasuGet(0x85);
            bridge = mb5_cartBlockMdlB;
            type = 3;
            break;
    }
    HuPrcSleep(8);

    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(8, 0xD01);
        MBSaiNumShow(system->current_player_index);
        goto end;
    }

    HuAudFXPlay(0x1AE);
retry:
    MBDlgWinInsertCreate(8, 0xD00, 0, 0, 0, 0, 0);
    switch (type) {
        case 0:
            tree = mb5ev_cartRideMasu150ComTree;
            break;
        case 1:
            tree = mb5ev_cartRideMasu126ComTree;
            break;
        case 2:
            tree = mb5ev_cartRideMasu112ComTree;
            break;
        default:
            tree = mb5ev_cartRideMasu132ComTree;
            break;
    }
    choice = MB5Ev_YesNoChoiceGet((s32)tree, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (choice) {
        case 0:
            MBCoinChangeCreate(system->current_player_index, -5);
            MBCoinTakeCreate(system->current_player_index, -5);
            HuPrcSleep(30);
            MBDlgWinExec(8, 0xD03);
            break;
        case 1:
            MBDlgWinExec(8, 0xD02);
            MBSaiNumShow(system->current_player_index);
            goto end;
        default:
            MB5_MapScroll();
            goto retry;
    }

    mbItemBtnF = 0;
    mbTauntOffF = 1;
    MBStatusHideAll();
    MBBackThreadPriLowSet();
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.2f));
    HuPrcChildWatch();

    MBModelJumpSet(bridge, 10.0f, -1.0f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&bridge->coords, &space->coords, &bridge->coords, 20));
    MBPlayerMotionSet(-1, 0, 2);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &dest->coords, &player->player_obj->coords, 20));
    HuPrcChildWatch();
    MBModelJumpWait(bridge);
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    MBPlayerMotionSet(-1, -1, 2);
    MBPlayerRotMasuStart(-1, 8, MBMasuLinkMasuIdGet(player->clink, player->cidx));
    HuPrcSleep(8);

    for (i = 0; i < 4; i++) {
        mb5ev_cartJumpStateTbl[i] = 0;
    }
    mb5ev_actionTimeSprProc = omAddPrcObj(MB5Ev_ActionTimeSpr, 0x4800, 0, 0);
    while (mb5ev_actionTimeSprProc->user_data == NULL) {
        HuPrcVSleep();
    }
    mb5ev_cartJumpStateTbl[system->current_player_index] = 1;

    switch (type) {
        case 0:
            space = MBMasuGet(0x92);
            dest = MBMasuGet(0x91);
            break;
        case 1:
            space = MBMasuGet(0x91);
            dest = MBMasuGet(0x92);
            break;
        case 2:
            space = MBMasuGet(0x90);
            dest = MBMasuGet(0x8F);
            break;
        default:
            space = MBMasuGet(0x8F);
            dest = MBMasuGet(0x90);
            break;
    }
    MB5Ev_CartPlayerEscapeAll(mb5ev_cartTrackMasuTbl[type], type, 0, MB5Ev_CartEscapeMasuShift(type));

    model = MBModelCreate(0x4C, NULL);
    mb5ev_cartMdl = model;
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &space->coords);
    switch (type) {
        case 0:
            model->coords.x += 0.8f;
            HuVecCopyXYZ(&model->rot, -1.0f, 0.0f, 0.0f);
            break;
        case 1:
            HuVecCopyXYZ(&model->rot, 1.0f, 0.0f, 0.0f);
            break;
        case 2:
            model->coords.x += 1.5f;
            HuVecCopyXYZ(&model->rot, -1.0f, 0.0f, 0.0f);
            break;
        default:
            model->coords.x -= 1.5f;
            HuVecCopyXYZ(&model->rot, 1.0f, 0.0f, 0.0f);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&model->coords, &dest->coords, &model->coords, 2.0f));
    omAddPrcObj(MB5Ev_CartSeProc, 0x4800, 0, 0)->user_data = (void *)type;
    omAddPrcObj(MB5Ev_CartBlockPushProc, 0x4800, 0, 0)->user_data = (void *)type;
    omAddPrcObj(MB5Ev_CartJumpProc, 0x4800, 0, 0)->user_data = (void *)type;

    target = MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx));
    switch (type) {
        case 0:
            while (model->coords.x - target->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            target = MBMasuGet(0x7E);
            dest = MBMasuGet(0x7F);
            break;
        case 1:
            while (target->coords.x - model->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            target = MBMasuGet(0x96);
            dest = MBMasuGet(0x97);
            break;
        case 2:
            while (model->coords.x - target->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            target = MBMasuGet(0x84);
            dest = MBMasuGet(0x85);
            break;
        default:
            while (target->coords.x - model->coords.x > -10.0f) {
                HuPrcVSleep();
            }
            target = MBMasuGet(0x70);
            dest = MBMasuGet(0x71);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&pos, &target->coords, &pos, 2.0f));
    HuPrcChildWatch();
    MBModelKill(model);
    mb5ev_cartJumpStateTbl[0] = -1;

    if (mb5ev_cartJumpF != 0) {
        MBPlayerMotionSet(-1, 0, 2);
        MBModelJumpSet(bridge, 10.0f, -1.0f);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&bridge->coords, &dest->coords, &bridge->coords, 20));
        MBSaiNumShow(system->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target->coords, &player->player_obj->coords, 20));
        HuPrcChildWatch();
        MBSaiNumShow(system->current_player_index);
        HuAudFXPlay(0x1AE);
        HuAudFXPlay(0x1AF);
        MBPlayerMotionSet(-1, -1, 2);
        MBCameraFocusModeSet(1);
        MBModelJumpWait(bridge);
        MBBackThreadPriHighSet();
        MBStatusShowAll();
        mbTauntOffF = 0;
        mbItemBtnF = 1;
        switch (type) {
            case 0:
                player->clink = 8;
                player->cidx = 0;
                player->nlink = 8;
                player->nidx = 1;
                player->blink = 0x10;
                player->bidx = 0x11;
                break;
            case 1:
                player->clink = 2;
                player->cidx = 1;
                player->nlink = 2;
                player->nidx = 2;
                player->blink = 2;
                player->bidx = 0;
                break;
            case 2:
                player->clink = 10;
                player->cidx = 0;
                player->nlink = 10;
                player->nidx = 1;
                player->blink = 9;
                player->bidx = 0xC;
                break;
            default:
                player->clink = 5;
                player->cidx = 1;
                player->nlink = 5;
                player->nidx = 2;
                player->blink = 5;
                player->bidx = 0;
                break;
        }
        if (player->rev & 0x80) {
            HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB5Ev_CartRideBranch, 0x4800, 0, 0));
            HuPrcChildWatch();
        }
    } else {
        WipeCreateOut(WIPE_FADE, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        MBBackThreadPriHighSet();
        HuVecCopy3F(&bridge->coords, &dest->coords);
        HuVecCopy3F(&pos, &player->player_obj->coords);
        MBCameraFocusVecSet(&pos);
        HuPrcSleep(5);
        MBCameraFocusModeSet(1);
        WipeCreateIn(WIPE_FADE, 16);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        MBPlayerMotionSet(-1, 0, 2);
        MBSaiNumShow(system->current_player_index);
        switch (type) {
            case 0:
                masu = 0x96;
                break;
            case 1:
                masu = 0x7E;
                break;
            case 2:
                masu = 0x70;
                break;
            default:
                masu = 0x84;
                break;
        }
        target = MBMasuGet(masu);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &target->coords, &player->player_obj->coords, 20));
        HuPrcChildWatch();
        MBStatusShowAll();
        mbTauntOffF = 0;
        mbItemBtnF = 1;
    }

    switch (type) {
        case 0:
        case 1:
            GwSystem.boardData.halfWordBytes[3] ^= 1;
            break;
        default:
            GwSystem.boardData.halfWordBytes[4] ^= 1;
            break;
    }
end:
    HuPrcSleep(10);
}

void MB5Ev_CartRide(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x96:
            if (GwSystem.boardData.halfWordBytes[3] == 0) {
                MB5Ev_CartRideExec();
            }
            break;
        case 0x7E:
            if (GwSystem.boardData.halfWordBytes[3] != 0) {
                MB5Ev_CartRideExec();
            }
            break;
        case 0x70:
            if (GwSystem.boardData.halfWordBytes[4] == 0) {
                MB5Ev_CartRideExec();
            }
            break;
        default:
            if (GwSystem.boardData.halfWordBytes[4] != 0) {
                MB5Ev_CartRideExec();
            }
            break;
    }
}

void MB5Ev_CartRunExec(s32 arg0, SpaceData *space) {
    Vec pos;
    GW_PLAYER *player;
    SpaceData *startSpace;
    Object *model;
    SpaceData *endSpace;
    SpaceData *destSpace;
    SpaceData *camSpace;
    Object *bridge;

    player = MBPlayerGet(-1);
    mbTauntOffF = 1;
    WipeCreateOut(WIPE_QUESTION, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&mb5ev_cartCameraPos, &space->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&mb5ev_cartCameraPos);
    HuPrcSleep(5);
    MBBackThreadPriLowSet();
    MB5Ev_CartPlayerEscapeAll(mb5ev_cartTrackMasuTbl[arg0], arg0, 1, MB5Ev_CartEscapeMasuShift(arg0));
    if (arg0 == 2 || arg0 == 3) {
        MB5Ev_CartPlayerEscapeAll(mb5ev_cartSideMasuTbl[arg0 - 2], arg0, 2, 0);
    }

    switch (arg0) {
        case 0:
            startSpace = MBMasuGet(0x92);
            endSpace = MBMasuGet(0x91);
            bridge = mb5_cartBlockMdlA;
            destSpace = MBMasuGet(0x7F);
            break;
        case 1:
            startSpace = MBMasuGet(0x91);
            endSpace = MBMasuGet(0x92);
            destSpace = MBMasuGet(0x97);
            bridge = mb5_cartBlockMdlA;
            break;
        case 2:
            startSpace = MBMasuGet(0x90);
            endSpace = MBMasuGet(0x8F);
            destSpace = MBMasuGet(0x85);
            bridge = mb5_cartBlockMdlB;
            break;
        default:
            startSpace = MBMasuGet(0x8F);
            endSpace = MBMasuGet(0x90);
            bridge = mb5_cartBlockMdlB;
            destSpace = MBMasuGet(0x71);
            break;
    }

    model = MBModelCreate(0x4C, NULL);
    mb5ev_cartMdl = model;
    MBModelTempAllocFree(model);
    HuVecCopy3F(&model->coords, &startSpace->coords);
    switch (arg0) {
        case 0:
            model->coords.x += 0.8f;
            HuVecCopyXYZ(&model->rot, -1.0f, 0.0f, 0.0f);
            break;
        case 1:
            HuVecCopyXYZ(&model->rot, 1.0f, 0.0f, 0.0f);
            break;
        case 2:
            model->coords.x += 1.5f;
            HuVecCopyXYZ(&model->rot, -1.0f, 0.0f, 0.0f);
            break;
        default:
            model->coords.x -= 2.0f;
            HuVecCopyXYZ(&model->rot, 1.0f, 0.0f, 0.0f);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&model->coords, &endSpace->coords, &model->coords, 2.0f));
    omAddPrcObj(MB5Ev_CartSeProc, 0x4800, 0, 0)->user_data = (void *)arg0;
    omAddPrcObj(MB5Ev_CartBlockPushProc, 0x4800, 0, 0)->user_data = (void *)arg0;
    WipeCreateIn(WIPE_QUESTION, 16);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    HuVecCopy3F(&pos, &space->coords);
    switch (arg0) {
        case 0:
            while (model->coords.x - pos.x > 20.0f) {
                HuPrcVSleep();
            }
            camSpace = MBMasuGet(0x35);
            break;
        case 1:
            while (pos.x - model->coords.x > 20.0f) {
                HuPrcVSleep();
            }
            camSpace = MBMasuGet(0x1A);
            break;
        case 2:
            while (model->coords.x - pos.x > 20.0f) {
                HuPrcVSleep();
            }
            camSpace = MBMasuGet(0x40);
            break;
        default:
            while (pos.x - model->coords.x > 20.0f) {
                HuPrcVSleep();
            }
            camSpace = MBMasuGet(0x10);
            break;
    }
    HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&mb5ev_cartCameraPos, &camSpace->coords, &mb5ev_cartCameraPos, 2.0f));
    HuPrcChildWatch();
    MBModelKill(model);
    MBModelJumpSet(bridge, 10.0f, -1.0f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&bridge->coords, &destSpace->coords, &bridge->coords, 20));
    HuPrcChildWatch();
    HuAudFXPlay(0x1AE);
    HuAudFXPlay(0x1AF);
    switch (arg0) {
        case 0:
        case 1:
            GwSystem.boardData.halfWordBytes[3] ^= 1;
            break;
        default:
            GwSystem.boardData.halfWordBytes[4] ^= 1;
            break;
    }
    if (MBKettouPlayerBitGet(0) != 0) {
        HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&mb5ev_cartCameraPos, &player->player_obj->coords, &mb5ev_cartCameraPos, 2.0f));
        HuPrcChildWatch();
    }
    MBBackThreadPriHighSet();
    mbTauntOffF = 0;
}

void MB5Ev_HatenaCartA(void) {
    s32 index;
    s32 masuIndex;

    index = 1;
    if (GwSystem.boardData.halfWordBytes[3] == 0) {
        index = 0;
        masuIndex = 0x1A;
    } else {
        masuIndex = 0x35;
    }
    MB5Ev_CartRunExec(index, MBMasuGet(masuIndex));
}

void MB5Ev_HatenaCartB(void) {
    s32 index;
    s32 masuIndex;

    index = 3;
    if (GwSystem.boardData.halfWordBytes[4] == 0) {
        index = 2;
        masuIndex = 0x10;
    } else {
        masuIndex = 0x40;
    }
    MB5Ev_CartRunExec(index, MBMasuGet(masuIndex));
}

void MB5Ev_OpStarMapView(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &mb5ev_opStarMapViewRect);
    MB5_ObjectSetup();
    MBStart(2);
    omAddPrcObj(MB5Ev_StarMapView, 0x1005, 0x1000, 0);
}

s32 MB5_ComNKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            MBComTreePlayerSet(i);
            if ((MBComTreeExec(mb5_itemNKinokoStarComTree) == 0) && (MBPlayerRankCalc(i) < bestRank)) {
                bestRank = MBPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}

s32 MB5_ComRKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(mb5_itemRKinokoStarComTree) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                MBComTreePlayerSet(i);
                if ((MBComTreeExec(mb5_itemRKinokoTargetComTree) == 0) && (MBPlayerRankCalc(i) < bestRank)) {
                    bestRank = MBPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}

s32 MB5_ComItemExcessCheck(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

s32 MB5_ComRobItemSafeCheck(s32 arg0, s32 arg1) {
    s32 result = 1;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 j;

        if (i == GwSystem.current_player_index) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            if (GwPlayer[i].itemNo[j] == ITEM_PLUNDER_CHEST || GwPlayer[i].itemNo[j] == ITEM_BARTER_BOX) {
                break;
            }
        }
        if (j < 3) {
            break;
        }
    }
    if (i < 4) {
        result &= -!MBRandCheck100((s8)(arg0 + arg1 * GwPlayer[i].cpu_difficulty));
    }
    return result;
}

s32 MB5_ComItemDecide(void) {
    s32 curPlayer = MBPlayerTurnGet();
    GW_SYSTEM *loc = &GwSystem;
    s32 results[3];
    s32 item;
    s32 i;
    s32 j;
    s32 count;
    s32 best;
    s32 slot;

    if (GwSystem.cur_player_used_item & 1) {
        return -1;
    }
    for (slot = 0; slot < 3; slot++) {
        results[slot] = -1;
        item = GwPlayer[curPlayer].itemNo[slot];
        switch (item) {
            case ITEM_NONE:
                continue;
            case ITEM_SKELETON_KEY:
            case ITEM_BOO_REPELLENT:
            case ITEM_KOOPA_KARD:
                for (i = 0, count = 0; i < 3; i++) {
                    if (GwPlayer[curPlayer].itemNo[i] == item) {
                        count++;
                    }
                }
                if (count < 2) {
                    continue;
                }
                break;
            case ITEM_WACKY_WATCH:
                if (loc->total_turns == loc->current_turn) {
                    if (MBPlayerStealRankGet(loc->current_player_index) != 0) {
                        break;
                    }
                }
                if (loc->total_turns - loc->current_turn < 6) {
                    continue;
                }
                if (MBPlayerStealRankGet(loc->current_player_index) == 0) {
                    break;
                }
                continue;
            case ITEM_MUSHROOM:
            case ITEM_LUCKY_CHARM:
                if (MB5_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBRandCheck100(80) == 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_PHONE:
                if (GwPlayer[curPlayer].coin == 0) {
                    break;
                }
                for (i = 0; i < 4; i++) {
                    if (i != curPlayer && GwPlayer[i].coin == 0) {
                        break;
                    }
                }
                if (i >= 4) {
                    break;
                }
                if (MBRandCheck100(70) != 0 && MB5_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (MB5_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb5_itemSKinokoComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (MB5_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb5_itemKSuitComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(mb5_itemWarpBlockComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(mb5_itemNKinokoComTree) == 0) {
                    s32 target = MB5_ComNKinokoTargetGet();

                    mb5_comNKinokoTarget = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(mb5_itemRKinokoComTree) == 0) {
                    s32 target = MB5_ComRKinokoTargetGet();

                    mb5_comRKinokoTarget = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, mb5_comRobBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < mbItemComWeightTbl[it]) {
                                    best = mbItemComWeightTbl[it];
                                    mb5_comRobBoxTarget = i;
                                }
                            }
                        }
                    }
                }
                if (mb5_comRobBoxTarget == -1) {
                    continue;
                }
                if (best >= 4) {
                    break;
                }
                if (MBRandCheck100(5) == 0) {
                    continue;
                }
                break;
            case ITEM_BARTER_BOX:
                for (i = 0, best = 0; i < 3; i++) {
                    if (i != slot) {
                        s8 it = GwPlayer[loc->current_player_index].itemNo[i];

                        if (it != -1) {
                            best += mbItemComWeightTbl[it];
                        }
                    }
                }
                for (i = 0, mb5_comExchangeBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += mbItemComWeightTbl[it];
                            }
                        }
                        if (best < count) {
                            mb5_comExchangeBoxTarget = i;
                            best = count;
                        }
                    }
                }
                if (mb5_comExchangeBoxTarget == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (MB5_ComRobItemSafeCheck(0x32, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_CELLULAR_SHOPPER:
                if (loc->total_turns == loc->current_turn) {
                    continue;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_MAGIC_LAMP:
                if (MB5_ComRobItemSafeCheck(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(mb5_itemMajinLampComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && MB5_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(mb5_itemStarYokeComTree) != 0) {
                    continue;
                }
                break;
        }
        results[slot] = GwPlayer[curPlayer].itemNo[slot];
    }
    slot = 0;
    i = 0;
    for (j = 0; j < 3; j++) {
        item = results[j];
        if (item == -1) {
            continue;
        }
        if (loc->total_turns == loc->current_turn) {
            if (item == ITEM_WACKY_WATCH) {
                return j;
            }
        }
        if (slot < mbItemComShopWeightTbl[results[j]]) {
            i = j;
            slot = mbItemComShopWeightTbl[results[j]];
        }
    }
    if (slot == 0) {
        return -1;
    }
    return i;
}

s32 MB5_ComShopItemDecide(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = mb5_comShopItemOrderTbl[player->chr][i];

        found = MB5Ev_ShopItemIdxGet(val);
        if (found == -1) {
            continue;
        }
        if (mbItemPriceTbl[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(mb5_comShopItemRateTbl[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (MB5Ev_ShopItemIdxGet(0xE) == found) {
            return found + 1;
        }
        if (MB5Ev_ShopItemIdxGet(0xB) == found && mbItemPriceTbl[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (MB5Ev_ShopItemIdxGet(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(mb5_comShopKeyComTree[mb5ev_shopNo]) == 0 && GwPlayer[loc->current_player_index].coin >= mbItemPriceTbl[1]) {
        s32 route = MB5Ev_ShopItemIdxGet(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(mb5_comShopItemComTree[mb5ev_shopNo]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = mb5_comShopItemOrderTbl[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = MB5Ev_ShopItemIdxGet(val);
            if (found == -1) {
                continue;
            }
            if (mbItemPriceTbl[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(mb5_comShopItemRateTbl[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = MB5Ev_ShopItemIdxGet(0);
    if (found != -1) {
        return found + 1;
    }
    mb5_comShopCancelF = 1;
    return MB5Ev_ShopItemNumGet() + 2;
}

s32 MB5_ComShopEnterDecide(void) {
    if (mb5_comShopCancelF != 0) {
        mb5_comShopCancelF = 0;
        return 2;
    }
    return MBComTreeExec(mb5_comShopEnterComTree[mb5ev_shopNo]) + 1;
}
