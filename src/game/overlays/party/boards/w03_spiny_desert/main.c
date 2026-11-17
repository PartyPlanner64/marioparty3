#include "SpinyDesert.h"
#include "common_board.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/object.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/scroll.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/window.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/mapfull.h"
#include "game/overlays/party/common/com.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/ksuit.h"
#include "game/overlays/party/common/vec.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"

typedef struct HatenaPlayerWork {
    /* 0x00 */ s32 playerNo;
    /* 0x04 */ s32 order;
} HatenaPlayerWork;

void MB3Ev_StarGuideIn(void);
void MB3_StarGuideCreate(s16 arg0);
void MB3_StarGuideKill(void);
void MB3Ev_StarGuideJumpExec(UnkMBGuideData *);
void MB3Ev_StarGet(void);
void MB3_GateCloseProc(void);
s32 MB3_ComShopItemDecide(void);
void MB3Ev_Teresa(void);
void MB3Ev_ItemUseFadeOut(void);
void MB3Ev_ItemLampSmokeObjMain(omObjData *arg0);
void MBModelTurnCreate(Object *arg0, Vec *arg1, s32 arg2);
void MB3Ev_ItemMajinLamp(void);
void MB3Ev_ItemMajinLampStar(void);
void MB3Ev_ItemWarpBlock(void);
void MB3Ev_ItemRobBox(void);
void MB3Ev_KSuitStart(void);
void MB3Ev_KSuitEnd(void);
void MB3Ev_ItemKinoko(void);
void MB3Ev_ItemShake(void);
void MB3Ev_ItemPhoneMove(void);
void MB3Ev_ItemNKinoko(void);
void MB3Ev_ItemRKinoko(void);
void MB3Ev_ItemShopPhone(void);
void MB3Ev_ItemKoopaPhone(void);
void MB3Ev_ItemStarYoke(void);
void MB3Ev_ItemKeyManUse(void);
void MB3Ev_ItemNullUse(void);
void MB3Ev_ItemExchangeBox(void);
void MB3Ev_ItemGambleCoin(void);
void MB3Ev_ItemAfter5(void);
void MB3Ev_ItemKoopaNKinoko(void);
void MB3Ev_ItemKoopaRKinoko(void);
s32 MB3_ComItemDecide(void);
void MB3_StarGuideCreateAll(void);
void MB3_TeresaGuideCreateAll(void);
void MB3_BankCoinCreateAll(void);
void MB3_GateCreateAll(void);
void MB3_BankMapIconAddAll(void);
void MB3_ShopMapIconAddAll(void);
void MB3Ev_KinokoMarkCreateAll(void);
void MB3_SandPitCreateProc(void);
void MB3Ev_SandPitJump(void);
void MB3Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees);
s32 MB3_ComShopEnterDecide(void);
s32 MB3_ComNKinokoTargetGet(void);
s32 MB3_ComRKinokoTargetGet(void);
void MB3Ev_TereYokeSprayProc(void);
void MB3Ev_BankKoopaCardExec(void);
s32 MB3_ComMirageCheck(void);
void MB3Ev_Branch1(void);
void MB3Ev_Branch2(void);
void MB3Ev_Branch3(void);
void MB3Ev_Branch4(void);
void MB3Ev_Branch5(void);
void MB3Ev_Branch6(void);
void MB3Ev_Branch7(void);
void MB3Ev_Branch8(void);
void MB3Ev_Branch9RKinoko(void);
void MB3Ev_Branch10RKinoko(void);
void MB3Ev_Branch11RKinoko(void);
void MB3Ev_Branch12RKinoko(void);
void MB3Ev_Branch13RKinoko(void);
void MB3Ev_Merge1(void);
void MB3Ev_Merge2(void);
void MB3Ev_Merge3(void);
void MB3Ev_Merge4(void);
void MB3Ev_Merge5(void);
void MB3Ev_Merge6(void);
void MB3Ev_Merge7(void);
void MB3Ev_Merge8(void);
void MB3Ev_Merge9(void);
void MB3Ev_Merge10(void);
void MB3Ev_Merge11(void);
void MB3Ev_Merge12(void);
void MB3Ev_Merge13(void);
void MB3Ev_Merge14(void);
void MB3Ev_Merge15(void);
void MB3Ev_Merge16(void);
void MB3Ev_Merge17(void);
void MB3Ev_KeyManMasu(void);
void MB3Ev_StarMasu(void);
void MB3Ev_BankMasu(void);
void MB3Ev_ShopMasu(void);
void MB3Ev_Gate1Close(void);
void MB3Ev_Gate2Close(void);
void MB3Ev_NKinokoTurnStart(void);
void MB3Ev_RKinokoTurnStart(void);
void MB3Ev_SandPitBranch(void);

s16 mb3ev_starOrderTbl[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

s16 mb3ev_starOrderGroupTbl[] = { 0, 0, 0, 0, 0, 0, 0, 1 };

s16 mb3ev_starFlag[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb3ev_starMasu[] = { 4, 90, 20, 30, 40, 79, 2, 62 };

s16 mb3ev_starGuideMasu[] = { 100, 101, 102, 103, 104, 105, 106, 107 };

s32 mb3ev_starGetTeresaF = 0;

s16 mb3_masuBlockExtTbl[] = { 54, 57, -1, 0 };

s16 mb3_masuBlockTbl[] = {
    4, 90, 20, 30, 40, 79, 2, 62,
    -1, 0
};

s16 mb3_starGuideMapIconOfsTbl[][2] = {
    { 7, -8 },
    { 7, -1 },
    { 8, -5 },
    { 5, -9 },
    { -1, -8 },
    { 7, 0 },
    { 0, -7 },
    { -3, -6 }
};

s16 mb3_teresaGuideMapIconOfsTbl[][2] = {
    { 2, 0 },
    { 2, 0 }
};

s16 mb3_bankMapIconOfsTbl[][2] = {
    { 0, -2 },
    { 4, -1 }
};

s16 mb3_shopMapIconOfsTbl[][2] = {
    { 2, -2 },
    { 2, -3 }
};

s16 mb3_gateMapIconOfsTbl[][2] = {
    { -1, -2 },
    { 0, -3 }
};

s16 mb3_gateDirMasuTbl[][2] = {
    { 116, 117 },
    { 140, 141 }
};

s16 mb3_starGuideMdlMasuTbl[] = { 100, 101, 102, 103, 104, 105, 106, 107 };

s16 mb3_starGuideFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb3_teresaGuideMasuTbl[] = { 108, 0 };

s16 mb3_bankCoinMasuTbl[] = { 124, 122 };

Vec mb3_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb3_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb3_gateMasuTbl[] = { 125, 126 };

s16 mb3_gateMdlTbl[] = { 38, 39, 40, 41, 42, 43 };

u32 mb3_gateMot1[] = { 1, 0x130163 };

u32 mb3_gateMot2[] = { 1, 0x130168 };

u32 mb3_gateMot3[] = { 1, 0x13016F };

u32 mb3_gateMot4[] = { 1, 0x130176 };

u32 mb3_gateMot5[] = { 1, 0x130180 };

u32 mb3_gateMot6[] = { 1, 0x130184 };

u32 *mb3_gateMotTbl[] = { mb3_gateMot1, mb3_gateMot2, mb3_gateMot3, mb3_gateMot4, mb3_gateMot5, mb3_gateMot6 };

s32 mb3_gateOpenSeTbl[] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1
};

s32 mb3_gateOpenDelaySeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb3_gateOpenDelayTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb3_gateCloseSeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s16 mb3_bankMapIconMasuTbl[] = { 123, 120 };

s16 mb3_shopMapIconMasuTbl[] = { 118, 119 };

s16 mb3_comMirageStarFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb3_comMirageOrder0Tbl[] = { 0, 1, 2, 3, 4, 6, 5, 7 };

s16 mb3_comMirageOrder1Tbl[] = { 0, 1, 2, 3, 4, 6, 5, 7 };

s16 mb3_comMirageOrder2Tbl[] = { 1, 2, 3, 4, 6, 5, 7, 0 };

s16 mb3_comMirageOrder3Tbl[] = { 4, 6, 1, 5, 7, 3, 0, 2 };

s16 mb3_comMirageOrder4Tbl[] = { 6, 1, 5, 7, 3, 4, 0, 2 };

s16 mb3_comMirageOrder5Tbl[] = { 6, 7, 1, 5, 3, 0, 4, 2 };

s16 mb3_comMirageOrder6Tbl[] = { 1, 6, 5, 7, 3, 4, 0, 2 };

DecisionTreeNonLeafNode mb3ev_branch3StarComTree[] = {
    { 3, { .data = 0x00000028 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch3SubComTree[] = {
    { 3, { .data = 0x00000280 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch3ComTree0Item[] = {
    { 2, { .data = 0x000000EA }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C96A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch3ComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = mb3ev_branch3ComTree0Item } },
    { 2, { .data = 0x0000000F }, { .node_data = mb3ev_branch3StarComTree } },
    { 2, { .data = 0x000000F0 }, { .node_data = mb3ev_branch3SubComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch3ComTree1Item[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1B541E32 } },
    { 0, { .data = 0x00000000 }, { .node_data = mb3ev_branch3SubComTree } }
};

DecisionTreeNonLeafNode mb3ev_branch3ComTree1[] = {
    { 8, { .data = 0x00000001 }, { .node_data = mb3ev_branch3ComTree1Item } },
    { 2, { .data = 0x0000000F }, { .data = 0x1B541E32 } },
    { 2, { .data = 0x000000F0 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch3ComTree2[] = {
    { 2, { .data = 0x0000000F }, { .data = 0x1B541E32 } },
    { 2, { .data = 0x00000030 }, { .node_data = mb3ev_branch3StarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb3ev_branch3ComTree[] = { mb3ev_branch3ComTree0, mb3ev_branch3ComTree1, mb3ev_branch3ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch4ComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 2, { .data = 0x0000000E }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch4ComTree1[] = {
    { 2, { .data = 0x0000000E }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch4ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb3ev_branch4ComTree[] = { mb3ev_branch4ComTree0, mb3ev_branch4ComTree1, mb3ev_branch4ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch5ComTree0LowCoin[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000020 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } }
};

DecisionTreeNonLeafNode mb3ev_branch5ComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000002 }, { .data = 0x1C96A33C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0C96A33C } },
    { 3, { .data = 0x00004000 }, { .data = 0x1B542332 } },
    { 3, { .data = 0x00000008 }, { .data = 0x1A119E32 } },
    { 12, { .data = 0x0000000A }, { .node_data = mb3ev_branch5ComTree0LowCoin } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } }
};

DecisionTreeNonLeafNode mb3ev_branch5ComTree1[] = {
    { 2, { .data = 0x00000005 }, { .data = 0x0C96A33C } },
    { 2, { .data = 0x0000000A }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch5ComTree2[] = {
    { 2, { .data = 0x00000003 }, { .data = 0x0C96A33C } },
    { 2, { .data = 0x0000000C }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb3ev_branch5ComTree[] = { mb3ev_branch5ComTree0, mb3ev_branch5ComTree1, mb3ev_branch5ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch6ComTree0Star13[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch6ComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000015 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x000000E0 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x0000000A }, { .node_data = mb3ev_branch6ComTree0Star13 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch6ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb3ev_branch6ComTree0 } }
};

DecisionTreeNonLeafNode mb3ev_branch6ComTree2Star0123[] = {
    { 3, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000022 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } }
};

DecisionTreeNonLeafNode mb3ev_branch6ComTree2Sub[] = {
    { 3, { .data = 0x00000033 }, { .data = 0x0A119E32 } },
    { 3, { .data = 0x000000C8 }, { .data = 0x1A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x08D1A346 } }
};

DecisionTreeNonLeafNode mb3ev_branch6ComTree2[] = {
    { 2, { .data = 0x0000000F }, { .node_data = mb3ev_branch6ComTree2Star0123 } },
    { 2, { .data = 0x000000E0 }, { .node_data = mb3ev_branch6ComTree2Sub } },
    { 12, { .data = 0x00000014 }, { .node_data = mb3ev_branch6ComTree2Sub } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C97ED50 } }
};

DecisionTreeNonLeafNode *mb3ev_branch6ComTree[] = { mb3ev_branch6ComTree0, mb3ev_branch6ComTree1, mb3ev_branch6ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch7ComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .data = 0x1C96A33C } },
    { 3, { .data = 0x00000004 }, { .data = 0x0B541E32 } },
    { 3, { .data = 0x00000100 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000212 }, { .data = 0x1B541E32 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A332 } }
};

DecisionTreeNonLeafNode mb3ev_branch7ComTree1[] = {
    { 2, { .data = 0x00000015 }, { .data = 0x0C96A33C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch7ComTree2[] = {
    { 2, { .data = 0x00000015 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb3ev_branch7ComTree[] = { mb3ev_branch7ComTree0, mb3ev_branch7ComTree1, mb3ev_branch7ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch8ComTree0Star6[] = {
    { 1, { .data = 0x00000014 }, { .data = 0x1BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb3ev_branch8ComTree0[] = {
    { 2, { .data = 0x00000040 }, { .node_data = mb3ev_branch8ComTree0Star6 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb3ev_branch8ComTree1[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000085 }, { .data = 0x0C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb3ev_branch8ComTree2Star7[] = {
    { 1, { .data = 0x00000014 }, { .data = 0x0BF6A83C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode mb3ev_branch8ComTree2[] = {
    { 2, { .data = 0x00000080 }, { .node_data = mb3ev_branch8ComTree2Star7 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A5BC } }
};

DecisionTreeNonLeafNode *mb3ev_branch8ComTree[] = { mb3ev_branch8ComTree0, mb3ev_branch8ComTree1, mb3ev_branch8ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch9ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A5BC } }
};

DecisionTreeNonLeafNode mb3ev_branch9ComTree1[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1BF6A5BC } },
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1A119E32 } }
};

DecisionTreeNonLeafNode mb3ev_branch9ComTree2[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0BF6A5BC } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E32 } }
};

DecisionTreeNonLeafNode *mb3ev_branch9ComTree[] = { mb3ev_branch9ComTree0, mb3ev_branch9ComTree1, mb3ev_branch9ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch11Star5ComTree[] = {
    { 9, { .data = 0x00000008 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B541E32 } }
};

DecisionTreeNonLeafNode mb3ev_branch11ComTree0[] = {
    { 2, { .data = 0x00000020 }, { .node_data = mb3ev_branch11Star5ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B541E32 } }
};

DecisionTreeNonLeafNode mb3ev_branch11ComTree1[] = {
    { 2, { .data = 0x00000020 }, { .node_data = mb3ev_branch11Star5ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch11ComTree2[] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb3ev_branch11ComTree[] = { mb3ev_branch11ComTree0, mb3ev_branch11ComTree1, mb3ev_branch11ComTree2 };

DecisionTreeNonLeafNode mb3ev_branch12ComTree0[] = {
    { 9, { .data = 0x00000004 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb3ev_branch12ComTree1[] = {
    { 2, { .data = 0x00000028 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb3ev_branch12ComTree2[] = {
    { 2, { .data = 0x00000028 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb3ev_branch12ComTree[] = { mb3ev_branch12ComTree0, mb3ev_branch12ComTree1, mb3ev_branch12ComTree2 };

DecisionTreeNonLeafNode mb3ev_sandPitBranchComTree0Star5[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitBranchComTree0[] = {
    { 6, { .func = MB3_ComMirageCheck }, { .data = 0x00000000 } },
    { 2, { .data = 0x00000010 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3ev_sandPitBranchComTree0Star5 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitBranchComTree1Star45[] = {
    { 12, { .data = 0x00000005 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000008 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitBranchComTree1[] = {
    { 2, { .data = 0x00000030 }, { .node_data = mb3ev_sandPitBranchComTree1Star45 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitMissComTree0Star1[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitMissComTree0Star3[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitMissWalkComTree[] = {
    { 5, { .data = 0x0000000C }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitMissComTree0[] = {
    { 2, { .data = 0x000000C5 }, { .data = 0x1BF6A33C } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3ev_sandPitMissComTree0Star1 } },
    { 3, { .data = 0x00000004 }, { .data = 0x0BF6A33C } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3ev_sandPitMissComTree0Star3 } },
    { 3, { .data = 0x00000001 }, { .node_data = mb3ev_sandPitMissWalkComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitMissComTree1[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000001 }, { .node_data = mb3ev_sandPitMissWalkComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_sandPitRevComTree[] = {
    { 2, { .data = 0x00000005 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch2ComTree0[] = {
    { 2, { .data = 0x00000005 }, { .data = 0x1BF6A33C } },
    { 9, { .data = 0x00000100 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch2ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A33C } }
};

DecisionTreeNonLeafNode mb3ev_branch2ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb3ev_branch2ComTree[] = { mb3ev_branch2ComTree0, mb3ev_branch2ComTree1, mb3ev_branch2ComTree2 };

event_list_entry mb3_branch1EventTbl[] = {
    { 8, 1, MB3Ev_Branch1 },
    { 0, 0, NULL }
};

s16 mb3ev_branch2Masu[][3] = {
    { 64, 12, -1 },
    { 45, 65, -1 },
    { 45, 56, -1 }
};

BranchLink mb3ev_branch2Link[][2] = {
    { { 1, 6, 1 }, { 1, 8, 0 } },
    { { 1, 12, 1 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 2, 0, 0 } }
};

event_list_entry mb3_branch2EventTbl[] = {
    { 1, 1, MB3Ev_Branch2 },
    { 0, 0, NULL }
};

s16 mb3ev_branch3Masu[][3] = {
    { 56, 65, -1 },
    { 45, 65, -1 },
    { 45, 56, -1 }
};

BranchLink mb3ev_branch3Link[][2] = {
    { { 2, 0, 0 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 10, 0, 0 } },
    { { 1, 12, 1 }, { 2, 0, 0 } }
};

event_list_entry mb3_branch3EventTbl[] = {
    { 1, 2, MB3Ev_Branch3 },
    { 0, 0, NULL }
};

s16 mb3ev_branch4Masu[][3] = {
    { 7, 11, -1 },
    { 6, 11, -1 },
    { 6, 7, -1 }
};

BranchLink mb3ev_branch4Link[][2] = {
    { { 3, 0, 0 }, { 4, 0, 0 } },
    { { 2, 8, 1 }, { 4, 0, 0 } },
    { { 2, 8, 1 }, { 3, 0, 0 } }
};

event_list_entry mb3_branch4EventTbl[] = {
    { 1, 2, MB3Ev_Branch4 },
    { 0, 0, NULL }
};

s16 mb3ev_branch5Masu[][3] = {
    { 14, 83, -1 },
    { 13, 83, -1 },
    { 13, 14, -1 }
};

BranchLink mb3ev_branch5Link[][2] = {
    { { 5, 0, 0 }, { 6, 0, 0 } },
    { { 4, 1, 1 }, { 6, 0, 0 } },
    { { 4, 1, 1 }, { 5, 0, 0 } }
};

event_list_entry mb3_branch5EventTbl[] = {
    { 1, 2, MB3Ev_Branch5 },
    { 0, 0, NULL }
};

s16 mb3ev_branch6Masu[][3] = {
    { 41, 49, -1 },
    { 40, 49, -1 },
    { 40, 41, -1 }
};

BranchLink mb3ev_branch6Link[][2] = {
    { { 7, 0, 0 }, { 8, 0, 0 } },
    { { 5, 24, 1 }, { 8, 0, 0 } },
    { { 5, 24, 1 }, { 7, 0, 0 } }
};

event_list_entry mb3_branch6EventTbl[] = {
    { 1, 2, MB3Ev_Branch6 },
    { 0, 0, NULL }
};

s16 mb3ev_branch7Masu[][3] = {
    { 93, 50, -1 },
    { 49, 50, -1 },
    { 49, 93, -1 }
};

BranchLink mb3ev_branch7Link[][2] = {
    { { 9, 0, 0 }, { 11, 0, 0 } },
    { { 8, 0, 1 }, { 11, 0, 0 } },
    { { 8, 0, 1 }, { 9, 0, 0 } }
};

event_list_entry mb3_branch7EventTbl[] = {
    { 1, 2, MB3Ev_Branch7 },
    { 0, 0, NULL }
};

s16 mb3ev_branch8Masu[][3] = {
    { 57, 99, -1 },
    { 58, 99, -1 },
    { 58, 57, -1 }
};

BranchLink mb3ev_branch8Link[][2] = {
    { { 11, 10, 1 }, { 12, 0, 0 } },
    { { 1, 0, 0 }, { 12, 0, 0 } },
    { { 1, 0, 0 }, { 11, 10, 1 } }
};

event_list_entry mb3_branch8EventTbl[] = {
    { 1, 2, MB3Ev_Branch8 },
    { 0, 0, NULL }
};

s16 mb3ev_branch9Masu[][3] = {
    { 89, 10, -1 },
    { 67, 10, -1 },
    { 67, 89, -1 }
};

BranchLink mb3ev_branch9Link[][2] = {
    { { 2, 3, 0 }, { 3, 3, 1 } },
    { { 2, 1, 1 }, { 3, 3, 1 } },
    { { 2, 1, 1 }, { 2, 3, 0 } }
};

event_list_entry mb3_branch9EventTbl[] = {
    { 1, 1, MB3Ev_Branch9RKinoko },
    { 0, 0, NULL }
};

s16 mb3ev_branch10Masu[][3] = {
    { 26, 92, -1 },
    { 24, 92, -1 },
    { 24, 26, -1 }
};

BranchLink mb3ev_branch10Link[][2] = {
    { { 5, 11, 0 }, { 6, 9, 1 } },
    { { 5, 9, 1 }, { 6, 9, 1 } },
    { { 5, 9, 1 }, { 5, 11, 0 } }
};

event_list_entry mb3_branch10EventTbl[] = {
    { 1, 1, MB3Ev_Branch10RKinoko },
    { 0, 0, NULL }
};

s16 mb3ev_branch11Masu[][3] = {
    { 35, 82, -1 },
    { 32, 82, -1 },
    { 32, 35, -1 }
};

BranchLink mb3ev_branch11Link[][2] = {
    { { 5, 19, 0 }, { 9, 20, 1 } },
    { { 5, 17, 1 }, { 9, 20, 1 } },
    { { 5, 17, 1 }, { 5, 19, 0 } }
};

event_list_entry mb3_branch11EventTbl[] = {
    { 1, 1, MB3Ev_Branch11RKinoko },
    { 0, 0, NULL }
};

s16 mb3ev_branch12Masu[][3] = {
    { 37, 48, -1 },
    { 35, 48, -1 },
    { 35, 37, -1 }
};

BranchLink mb3ev_branch12Link[][2] = {
    { { 5, 21, 0 }, { 7, 6, 1 } },
    { { 5, 19, 1 }, { 7, 6, 1 } },
    { { 5, 19, 1 }, { 5, 21, 0 } }
};

event_list_entry mb3_branch12EventTbl[] = {
    { 1, 1, MB3Ev_Branch12RKinoko },
    { 0, 0, NULL }
};

s16 mb3ev_branch13RKinokoFrom98Masu[] = { 70, 69, 2, -1 };

s16 mb3ev_branch13RKinokoFrom70Masu[] = { 98, 69, 2, -1 };

s16 mb3ev_branch13RKinokoFrom69Masu[] = { 98, 70, 2, -1 };

s16 mb3ev_branch13RKinokoMasu[] = { 98, 70, 69, -1 };

event_list_entry mb3_branch13EventTbl[] = {
    { 1, 1, MB3Ev_Branch13RKinoko },
    { 0, 0, NULL }
};

event_list_entry mb3_merge1EventTbl[] = {
    { 1, 1, MB3Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge2EventTbl[] = {
    { 1, 1, MB3Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge3EventTbl[] = {
    { 1, 1, MB3Ev_Merge3 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge4EventTbl[] = {
    { 1, 1, MB3Ev_Merge4 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge5EventTbl[] = {
    { 1, 1, MB3Ev_Merge5 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge6EventTbl[] = {
    { 1, 1, MB3Ev_Merge6 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge7EventTbl[] = {
    { 1, 1, MB3Ev_Merge7 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge8EventTbl[] = {
    { 1, 1, MB3Ev_Merge8 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge9EventTbl[] = {
    { 1, 1, MB3Ev_Merge9 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge10EventTbl[] = {
    { 1, 1, MB3Ev_Merge10 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge11EventTbl[] = {
    { 1, 1, MB3Ev_Merge11 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge12EventTbl[] = {
    { 1, 1, MB3Ev_Merge12 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge13EventTbl[] = {
    { 1, 1, MB3Ev_Merge13 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge14EventTbl[] = {
    { 1, 1, MB3Ev_Merge14 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge15EventTbl[] = {
    { 1, 1, MB3Ev_Merge15 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge16EventTbl[] = {
    { 1, 1, MB3Ev_Merge16 },
    { 0, 0, NULL }
};

event_list_entry mb3_merge17EventTbl[] = {
    { 1, 1, MB3Ev_Merge17 },
    { 0, 0, NULL }
};

event_list_entry mb3_keyManMasuEventTbl[] = {
    { 1, 2, MB3Ev_KeyManMasu },
    { 0, 0, NULL }
};

event_list_entry mb3_starMasuEventTbl[] = {
    { 1, 1, MB3Ev_StarMasu },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb3ev_bankComTree[] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } }
};

u32 mb3ev_bankCoinPileMot[] = { 1, 0xA009D };

event_list_entry mb3_bankMasuEventTbl[] = {
    { 1, 1, MB3Ev_BankMasu },
    { 0, 0, NULL }
};

u8 mb3ev_shopItemRowTbl[][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }
};

s8 mb3ev_shopItemTbl[][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } }
};

u8 mb3ev_shopBagRowTbl[][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }
};

s8 mb3ev_shopBagRateTbl[][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } }
};

u8 mb3ev_shopBagItemTbl[][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 }
};

s32 mb3ev_shopItemMesTbl[][2] = {
    { 0x3B05, 0x3D05 },
    { 0x3B06, 0x3D06 },
    { 0x3B07, 0x3D07 },
    { 0x3B08, 0x3D08 },
    { 0x3B09, 0x3D09 }
};

s32 mb3ev_shopEnterMesTbl[] = { 0x3B00, 0x3D00 };

s32 mb3ev_shopNoCoinMesTbl[] = { 0x3B01, 0x3D01 };

s32 mb3ev_shopItemFullMesTbl[] = { 0x3B02, 0x3D02 };

s32 mb3ev_shopLastTurnMesTbl[] = { 0x3B03, 0x3D03 };

s32 mb3ev_shopCancelMesTbl[] = { 0x3B04, 0x3D04 };

u32 mb3ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb3ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

s32 mb3ev_shopNo = 0;

event_list_entry mb3_shopMasuEventTbl[] = {
    { 1, 1, MB3Ev_ShopMasu },
    { 0, 0, NULL }
};

Vec2f mb3ev_teresaSprPosTbl[] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f }
};

Vec2f mb3ev_teresaSprDirTbl[] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f }
};

u8 mb3ev_teresaCoinTurnTbl[][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

u8 mb3ev_teresaCoinPenaltyTbl[][3] = {
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

u8 mb3ev_teresaCoinDiffTbl[] = { 9, 7, 4, 1, 0, 0, 0, 0 };

s32 mb3ev_teresaComTargetRateTbl[] = { 50, 80, 100 };

s32 mb3ev_teresaMdlFlipTbl[] = { 1, 0, 1, 0, 0, 1, 0 };

event_list_entry mb3_teresaMasuEventTbl[] = {
    { 1, 1, MB3Ev_Teresa },
    { 0, 0, NULL }
};

event_list_entry mb3_gate1CloseEventTbl[] = {
    { 1, 1, MB3Ev_Gate1Close },
    { 0, 0, NULL }
};

event_list_entry mb3_gate2CloseEventTbl[] = {
    { 1, 1, MB3Ev_Gate2Close },
    { 0, 0, NULL }
};

event_table_entry mb3_commonEventTbl[] = {
    { 4, mb3_starMasuEventTbl },
    { 90, mb3_starMasuEventTbl },
    { 20, mb3_starMasuEventTbl },
    { 30, mb3_starMasuEventTbl },
    { 40, mb3_starMasuEventTbl },
    { 79, mb3_starMasuEventTbl },
    { 2, mb3_starMasuEventTbl },
    { 62, mb3_starMasuEventTbl },
    { 28, mb3_bankMasuEventTbl },
    { 95, mb3_bankMasuEventTbl },
    { 110, mb3_shopMasuEventTbl },
    { 113, mb3_shopMasuEventTbl },
    { 125, mb3_gate1CloseEventTbl },
    { 126, mb3_gate2CloseEventTbl },
    { -1, NULL }
};

event_table_entry mb3_teresaEventTbl[] = {
    { 142, mb3_teresaMasuEventTbl },
    { -1, NULL }
};

Vec2f mb3ev_itemUsePosTbl[] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f }
};

Vec2f mb3ev_itemFadePosTbl[] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f }
};

Vec2f mb3ev_robBoxItemEndPosTbl[] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f }
};

Vec2f mb3ev_robBoxItemStartPosTbl[] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f }
};

DecisionTreeNonLeafNode mb3ev_shopPhoneComTree[] = {
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

s32 mb3ev_itemPhoneWaveAngleTbl[] = { 20, 60, 30, 50, 70 };

DecisionTreeNonLeafNode mb3ev_keyManUseComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } }
};

Vec2f mb3ev_tereYokeSparkOfsTbl[] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f }
};

s32 mb3ev_gambleCoinPlayer = -1;

u8 mb3ev_gambleMgTbl[] = { 67, 68, 69, 0 };

u8 mb3ev_gambleMgRateTbl[] = { 20, 60, 100, 0 };

GameGuyReward mb3ev_gambleRateTbl[] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 }
};

RGB mb3ev_after5NumColorTbl[] = {
    { 240, 222, 53 },
    { 247, 26, 66 }
};

event_list_entry mb3_kinokoTurnEventTbl[] = {
    { 7, 1, MB3Ev_NKinokoTurnStart },
    { 7, 1, MB3Ev_RKinokoTurnStart },
    { 0, 0, NULL }
};

event_table_entry mb3_turnStatusEventTbl[] = {
    { -5, mb3_kinokoTurnEventTbl },
    { -1, NULL }
};

s16 mb3ev_sandPitFall0Masu[] = { 58, 57, 99, -1 };

s16 mb3ev_sandPitFall1Masu[] = { 24, 26, 92, -1 };

s16 mb3ev_sandPitRevMasu[] = { 86, 87, -1, 0 };

s16 mb3ev_quicksand1HatenaMasuTbl[] = { 89, 3, 9, 10, -1, 0 };

s16 mb3ev_quicksand1MasuTbl[] = {
    78, 89, 1, 3, 4, 5, 6, 7,
    8, 9, 10, -1
};

s16 mb3ev_quicksand2MasuTbl[] = {
    36, 37, 38, 39, 40, 41, 42, 43,
    44, 46, 47, 48, -1, 0
};

Vec2f mb3ev_quicksandExitOfsTbl[] = {
    { 0.0f, 0.0f },
    { -10.0f, 0.0f },
    { 0.0f, -10.0f },
    { 10.0f, 0.0f }
};

s16 mb3ev_sandPitBranchFrom74Masu[] = { 115, 75, -1, 0 };

s16 mb3ev_sandPitBranchMasu[] = { 115, 74, -1, 0 };

event_list_entry mb3_sandPitBranchEventTbl[] = {
    { 1, 2, MB3Ev_SandPitBranch },
    { 0, 0, NULL }
};

event_table_entry mb3_specialEventTbl[] = {
    { 109, mb3_branch1EventTbl },
    { 0, mb3_branch2EventTbl },
    { 121, mb3_branch3EventTbl },
    { 132, mb3_branch4EventTbl },
    { 137, mb3_branch5EventTbl },
    { 138, mb3_branch6EventTbl },
    { 139, mb3_branch7EventTbl },
    { 111, mb3_branch8EventTbl },
    { 78, mb3_branch9EventTbl },
    { 25, mb3_branch10EventTbl },
    { 33, mb3_branch11EventTbl },
    { 36, mb3_branch12EventTbl },
    { 112, mb3_branch13EventTbl },
    { 58, mb3_merge1EventTbl },
    { 56, mb3_merge2EventTbl },
    { 7, mb3_merge3EventTbl },
    { 10, mb3_merge4EventTbl },
    { 11, mb3_merge5EventTbl },
    { 14, mb3_merge6EventTbl },
    { 83, mb3_merge7EventTbl },
    { 92, mb3_merge8EventTbl },
    { 41, mb3_merge9EventTbl },
    { 48, mb3_merge10EventTbl },
    { 49, mb3_merge11EventTbl },
    { 93, mb3_merge12EventTbl },
    { 82, mb3_merge13EventTbl },
    { 65, mb3_merge14EventTbl },
    { 69, mb3_merge15EventTbl },
    { 50, mb3_merge16EventTbl },
    { 99, mb3_merge17EventTbl },
    { 116, mb3_keyManMasuEventTbl },
    { 140, mb3_keyManMasuEventTbl },
    { 117, mb3_keyManMasuEventTbl },
    { 141, mb3_keyManMasuEventTbl },
    { 114, mb3_sandPitBranchEventTbl },
    { -1, NULL }
};

RectF mb3ev_opStarMapViewRect = { 0.0f, 0.0f, 320.0f, 240.0f };

DecisionTreeNonLeafNode mb3_itemSKinokoStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00020000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001000C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00060000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020008 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010A0C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00090208 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B000A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020008 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010A0C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar3ItemComTree[] = {
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001050C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x0000001E }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051718 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050009 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060009 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020608 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B080A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 8, { .data = 0x00000001 }, { .node_data = mb3_itemSKinokoStar3ItemComTree } },
    { 12, { .data = 0x0000001E }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051718 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001050C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00050412 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070005 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00090414 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar5ItemComTree[] = {
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001040C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009020A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B000A }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 8, { .data = 0x00000001 }, { .node_data = mb3_itemSKinokoStar5ItemComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar6ItemComTree[] = {
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050E18 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00091114 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001020C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar6ComTree[] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = mb3_itemSKinokoStar6ItemComTree } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0101 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051218 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0001020C }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar7ItemComTree[] = {
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080000 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070406 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051118 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00091414 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010205 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoStar7ComTree[] = {
    { 12, { .data = 0x0000000F }, { .data = 0x00000000 } },
    { 8, { .data = 0x00000001 }, { .node_data = mb3_itemSKinokoStar7ItemComTree } },
    { 10, { .data = 0x000B0606 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000014 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000B0809 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0009020C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0101 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00090001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00051418 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00010205 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemSKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemSKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemSKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemSKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemSKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemSKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemSKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemSKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemSKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemKSuitComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020105 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00060106 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090A0C }, { .data = 0x0000028A } },
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050105 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050A0E }, { .data = 0x0000028A } },
    { 11, { .data = 0x00050D0E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028A1E } },
    { 11, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00051317 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00070606 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090B10 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar6ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000C0000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B060A }, { .data = 0x0000028A } },
    { 10, { .data = 0x0009080C }, { .data = 0x0000028A } },
    { 11, { .data = 0x000C0000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B060A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0009080C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockStar7ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00010003 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0A0A }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0000028A } },
    { 11, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0A0A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb3_itemWarpBlockComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemWarpBlockStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemWarpBlockStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemWarpBlockStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemWarpBlockStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemWarpBlockStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemWarpBlockStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemWarpBlockStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemWarpBlockStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar0ComTree[] = {
    { 10, { .data = 0x00020105 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar1ComTree[] = {
    { 10, { .data = 0x00060106 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090A0C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar2ComTree[] = {
    { 10, { .data = 0x00050105 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar3OtherPosComTree[] = {
    { 1, { .data = 0x00000019 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar3ComTree[] = {
    { 10, { .data = 0x00050A0E }, { .data = 0x0000028A } },
    { 11, { .data = 0x00090C0C }, { .node_data = mb3_itemMajinLampStar3OtherPosComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar4ComTree[] = {
    { 10, { .data = 0x00051317 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00070606 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar5ComTree[] = {
    { 10, { .data = 0x00090B10 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar6ComTree[] = {
    { 10, { .data = 0x000C0000 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B060A }, { .data = 0x0000028A } },
    { 10, { .data = 0x0009080C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampStar7ComTree[] = {
    { 10, { .data = 0x00010003 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0A0A }, { .data = 0x0000028A } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb3_itemMajinLampComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemMajinLampStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemMajinLampStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemMajinLampStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemMajinLampStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemMajinLampStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemMajinLampStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemMajinLampStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemMajinLampStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar0ComTree[] = {
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar1ComTree[] = {
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar2ComTree[] = {
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar3ComTree[] = {
    { 11, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar4ComTree[] = {
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar5ComTree[] = {
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar6ComTree[] = {
    { 11, { .data = 0x000C0000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B060A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0009080C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStar7ComTree[] = {
    { 11, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0A0A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemNKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemNKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemNKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemNKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemNKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemNKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemNKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemNKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoPosComTree[] = {
    { 10, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090C0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemNKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb3_itemNKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb3_itemNKinokoPosComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar0ComTree[] = {
    { 10, { .data = 0x00040001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060000 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00020708 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar1ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00050A0C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060809 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090E10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar2ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0005070B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090E0F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar3ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00051014 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00090E10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar4ComTree[] = {
    { 10, { .data = 0x00080000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0002 }, { .data = 0x0A119E32 } },
    { 10, { .data = 0x00090003 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00070004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar5ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x00091214 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00051313 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar6ComTree[] = {
    { 10, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090E11 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0009070C }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x00000000 } },
    { 10, { .data = 0x000A0506 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStar7ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00028F1E } },
    { 10, { .data = 0x0001050A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoStarComTree[] = {
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemRKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemRKinokoStar7ComTree } },
    { 12, { .data = 0x00000005 }, { .data = 0x00028F1E } },
    { 10, { .data = 0x000B080A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000C0001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemRKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemRKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemRKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemRKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemRKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemRKinokoStar5ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar0ComTree[] = {
    { 11, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar1ComTree[] = {
    { 11, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar2ComTree[] = {
    { 11, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar3ComTree[] = {
    { 11, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar4ComTree[] = {
    { 11, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar5ComTree[] = {
    { 11, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01450F1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar6ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStar7ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemStarYokeStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemStarYokeStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemStarYokeStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemStarYokeStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemStarYokeStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemStarYokeStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemStarYokeStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemStarYokeStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb3_itemRKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb3_itemStarYokeStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x00020105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar1ComTree[] = {
    { 15, { .data = 0x00060106 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00090A0C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00050105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar3ComTree[] = {
    { 15, { .data = 0x00050A0E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x00051317 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00070606 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x00090B10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar6ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetStar7ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb3_itemRKinokoTargetComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb3_itemRKinokoTargetStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb3_itemRKinokoTargetStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb3_itemRKinokoTargetStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb3_itemRKinokoTargetStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb3_itemRKinokoTargetStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb3_itemRKinokoTargetStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb3_itemRKinokoTargetStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb3_itemRKinokoTargetStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_itemStarYokeComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb3_itemStarYokeStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_comShopKeyComTree0[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x000000EA }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_comShopKeyComTree1[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x0000007A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_comShopItemComTree0[] = {
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_comShopItemComTree1[] = {
    { 1, { .data = 0x00000037 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb3_comShopEnterComTree0[] = {
    { 2, { .data = 0x000000FA }, { .data = 0x0B54233C } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } }
};

DecisionTreeNonLeafNode mb3_comShopEnterComTree1Star3[] = {
    { 1, { .data = 0x0000001E }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } }
};

DecisionTreeNonLeafNode mb3_comShopEnterComTree1[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb3_comShopEnterComTree1Star3 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } }
};

s32 mb3_comShopCancelF = 0;

u8 mb3_comShopItemOrderMario[] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1
};

u8 mb3_comShopItemOrderLuigi[] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5
};

u8 mb3_comShopItemOrderPeach[] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1
};

u8 mb3_comShopItemOrderYoshi[] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1
};

u8 mb3_comShopItemOrderWario[] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1
};

u8 mb3_comShopItemOrderDk[] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1
};

u8 mb3_comShopItemOrderWaluigi[] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1
};

u8 mb3_comShopItemOrderDaisy[] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5
};

u8 *mb3_comShopItemOrderTbl[] = { mb3_comShopItemOrderMario, mb3_comShopItemOrderLuigi, mb3_comShopItemOrderPeach, mb3_comShopItemOrderYoshi, mb3_comShopItemOrderWario, mb3_comShopItemOrderDk, mb3_comShopItemOrderWaluigi, mb3_comShopItemOrderDaisy };

s8 mb3_comShopItemRateMario[] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb3_comShopItemRateLuigi[] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0
};

s8 mb3_comShopItemRatePeach[] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10
};

s8 mb3_comShopItemRateYoshi[] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10
};

s8 mb3_comShopItemRateWario[] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10
};

s8 mb3_comShopItemRateDk[] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb3_comShopItemRateWaluigi[] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10
};

s8 mb3_comShopItemRateDaisy[] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10
};

s8 *mb3_comShopItemRateTbl[] = { mb3_comShopItemRateMario, mb3_comShopItemRateLuigi, mb3_comShopItemRatePeach, mb3_comShopItemRateYoshi, mb3_comShopItemRateWario, mb3_comShopItemRateDk, mb3_comShopItemRateWaluigi, mb3_comShopItemRateDaisy };

DecisionTreeNonLeafNode *mb3_comShopKeyComTree[] = { mb3_comShopKeyComTree0, mb3_comShopKeyComTree1 };

DecisionTreeNonLeafNode *mb3_comShopItemComTree[] = { mb3_comShopItemComTree0, mb3_comShopItemComTree1 };

DecisionTreeNonLeafNode *mb3_comShopEnterComTree[2] = { mb3_comShopEnterComTree0, mb3_comShopEnterComTree1 };

Object *mb3_starGuideBaseMdl BSS;
u8 mb3_starGuideBaseMdlPad[4] BSS; /* Unreferenced. */
Object *mb3_starGuideMdl[8] BSS;
Process *mb3_starGuideHoverProc[8] BSS;
Process *mb3ev_starGuideInProc BSS;
Object *mb3ev_starGuideInMdl BSS;
Unk3 *mb3_branchStickHelp BSS;
Unk3 *mb3_branchBtnHelp BSS;
Unk3 *mb3_branchMapScrollHelp BSS;
Unk3 *mb3_branchMapOverheadHelp BSS;
Unk3 *mb3_branchItemHelp BSS;
s32 mb3_comTeresaType BSS;
s32 mb3_comTeresaTarget BSS;
Process *mb3ev_actionTimeSprProc BSS;
Object *mb3ev_quicksandMdl BSS;
Object *mb3_sandPit0Mdl BSS;
Object *mb3_sandPit1Mdl BSS;
SpaceData *mb3ev_quicksandExitMasu BSS;
s32 mb3ev_sandPitJumpStateTbl[4] BSS;
s32 mb3ev_quicksandExitNum BSS;
Object *mb3_teresaGuideBaseMdl BSS;
Object *mb3_teresaGuideMdl[1] BSS;
Object *mb3_bankCoinBaseMdl BSS;
Object *mb3_bankCoinMdl[10] BSS;
Object *mb3_gateBaseMdl BSS;
Object *mb3_gateMdl[2] BSS;
s32 mb3ev_shopHostNo BSS;
s32 mb3ev_shopItemRow BSS;
u8 *mb3ev_shopItemEnableTbl BSS;
Object *mb3ev_teresaCoinMdl BSS;
s32 mb3ev_itemPhoneWaveSpr BSS;
s32 mb3ev_tereYokePlayer BSS;
s32 mb3ev_tereYokeSparkSpr BSS;
Object *mb3ev_koopaCardCoinMdl BSS;
Object *mb3ev_koopaCardMdl BSS;
s32 mb3_comExchangeBoxTarget BSS;
s32 mb3_comRobBoxTarget BSS;
Object *mb3ev_gambleCoinMdl BSS;
u8 mb3ev_gambleCoinMdlPad[4] BSS; /* Unreferenced. */
s32 mb3ev_after5GrpId[4] BSS;
Object *mb3ev_after5EffMdl BSS;
u8 mb3ev_after5EffMdlPad[4] BSS; /* Unreferenced. */
Object *mb3ev_kinokoMarkMdl[4] BSS;
omObjData *mb3ev_kinokoMarkObj[4] BSS;
s32 mb3_comRKinokoTarget BSS;
s32 mb3_comNKinokoTarget BSS;

s16 MB3Ev_StarGuideMasuGet(void) {
    return mb3ev_starGuideMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void MB3Ev_StarShuffle(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < mb3ev_starOrderGroupTbl[idx2]) {
                continue;
            }
            if (idx2 < mb3ev_starOrderGroupTbl[idx1]) {
                continue;
            }
            {
                s32 temp = mb3ev_starOrderTbl[idx1];
                mb3ev_starOrderTbl[idx1] = mb3ev_starOrderTbl[idx2];
                mb3ev_starOrderTbl[idx2] = temp;
                temp = mb3ev_starOrderGroupTbl[idx1];
                mb3ev_starOrderGroupTbl[idx1] = mb3ev_starOrderGroupTbl[idx2];
                mb3ev_starOrderGroupTbl[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = mb3ev_starOrderTbl[i];
    }

    do {
        GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f) + 1];
    } while (GwSystem.boardData.halfWordBytes[0] == 7);
    GWBoardFlagClear(0x12);
}

void MB3Ev_StarNextPos(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_SYSTEM *system = &GwSystem;
    s32 sp7;
    s32 sp0;

    system->current_star_spawn++;
    if (system->current_star_spawn >= 8) {
        sp7 = system->star_spawn_indices[7];
        system->current_star_spawn = 0;
        GWBoardFlagSet(4);
        MB3Ev_StarShuffle();
        sp0 = system->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            system->star_spawn_indices[0] = system->star_spawn_indices[7];
            system->star_spawn_indices[7] = sp0;
        }
    }

    if (loc->current_star_spawn >= 7) {
        GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f)];
    } else {
        GwSystem.boardData.halfWordBytes[0] =
            loc->star_spawn_indices[MBRand(7 - loc->current_star_spawn) + loc->current_star_spawn + 1];
    }
    GWBoardFlagClear(0x12);
}

void MB3Ev_StarMasuInit(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(mb3ev_starFlag[i]);
    }
    MBMasuTypeSet(mb3ev_starMasu[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(mb3ev_starFlag[loc->star_spawn_indices[loc->current_star_spawn]]);
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        MBMasuTypeSet(mb3ev_starMasu[GwSystem.boardData.halfWordBytes[0]], 0xE);
    }
}

s16 MB3Ev_StarCheck(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == mb3ev_starMasu[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = mb3ev_starFlag[i];
                return 1;
            }
            if (i == GwSystem.boardData.halfWordBytes[0]) {
                return 2;
            }
            break;
        }
    }
    return 0;
}

void MB3Ev_StarGuideIn(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    mb3ev_starGuideInMdl = MBModelCreate(0x3A, NULL);
    model = mb3ev_starGuideInMdl;
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
    mb3ev_starGuideInProc = 0;
    omDelPrcObj(NULL);
}

void MB3Ev_StarGuideJumpExec(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    HuPrcSleep(3);
    while (obj->velocity.z != 0.0f) {
        HuPrcVSleep();
    }
}

// Star tour.
void MB3Ev_StarMapView(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *first;
    SpaceData *second;
    SpaceData *temp;
    s32 mesNum;
    GW_SYSTEM *system = &GwSystem;

    mbTurnUnkF = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, 0xA007E);
    MBPlayerIconMdlSet();
    MBModelDispOff(mb3_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOff(mb3_starGuideMdl[GwSystem.boardData.halfWordBytes[0]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBBackThreadPriLowSet();
    MBCameraSpeedDivSet(3.0f);
    MB3Ev_StarGuideJumpExec(guide);

    first = MBMasuGet(mb3ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
    second = MBMasuGet(mb3ev_starGuideMasu[GwSystem.boardData.halfWordBytes[0]]);

    if (MBRandCheck100(50) != 0) {
        temp = first;
        first = second;
        second = temp;
    }

    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        mesNum = 0x5E09;
    } else {
        mesNum = 0x5E0A;
    }

    HuWinMesSet(guide->amount, mesNum, -1, -1);
    HuWinExOpen(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    temp = first;
    MBWinComKeyAllWaitKeep(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    HuWinExClose(guide->amount, 1);
    Hu3DMotionReset(guide->obj->omObj1->model[0]);

    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    MBMotionSet(guide->obj, -1, 2);
    proc = omAddPrcObj(MB3Ev_StarGuideIn, 0x4800, 0, 0);
    mb3ev_starGuideInProc = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    winData[guide->amount].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    HuWinExOpen(guide->amount, 1);
    MBWinComKeyAllWaitKeep(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    HuWinExClose(guide->amount, 1);

    while (mb3ev_starGuideInProc != NULL) {
        HuPrcVSleep();
    }
    temp = second;
    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    proc = omAddPrcObj(MB3Ev_StarGuideIn, 0x4800, 0, 0);
    mb3ev_starGuideInProc = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    winData[guide->amount].stat = HUWIN_STAT_DRAWMES;
    HuPrcVSleep();
    HuWinExOpen(guide->amount, 1);
    MBWinComKeyAllWaitKeep(guide->amount);
    HuWinExClose(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    mbTurnUnkF = 1;
    MBPlayerIconMdlReset();
    AuraKill(mb3ev_starGuideInMdl->omObj1->model[0]);
    MBModelKill(mb3ev_starGuideInMdl);
    MBModelDispOn(mb3_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOn(mb3_starGuideMdl[GwSystem.boardData.halfWordBytes[0]]);
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB3Ev_StarGet(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8E) {
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
    if (mb3ev_starGetTeresaF != 0) {
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
    if (mb3ev_starGetTeresaF != 0) {
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

void MB3Ev_StarGetExec(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(MB3Ev_StarGet, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void MB3_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MB3_MapScrollCancel(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void MB3_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mb3_branchStickHelp = MBHelpWinCreate(0, 0x92, 1);
    mb3_branchBtnHelp = MBHelpWinCreate(1, 0xA0, 1);
    mb3_branchItemHelp = MBHelpWinCreate(0xD, 0xAE, 1);
    mb3_branchMapScrollHelp = MBHelpWinCreate(3, 0xBC, 1);
    mb3_branchMapOverheadHelp = MBHelpWinCreate(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MB3_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBHelpWinKill(mb3_branchStickHelp);
    MBHelpWinKill(mb3_branchBtnHelp);
    MBHelpWinKill(mb3_branchItemHelp);
    MBHelpWinKill(mb3_branchMapScrollHelp);
    MBHelpWinKill(mb3_branchMapOverheadHelp);
}

const u8 mb3_padBitTbl[4] = { 1, 2, 4, 8 };

s32 MB3_ComShopItemChoice(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb3_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = MB3_ComShopItemDecide();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
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

s32 MB3_ComShopEnterChoice(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb3_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches MBKettouTargetChoiceGet
                var_s2 = MB3_ComShopEnterDecide();
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
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

void MB3_ComTeresaTypeDecide(void) {
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
                mb3_comTeresaType = 1;
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
        mb3_comTeresaType = 0;
    } else {
        mb3_comTeresaType = 2;
    }
}

void MB3_ComTeresaTargetDecide(void) {
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
    MB3_ComTeresaTypeDecide();
    if (mb3_comTeresaType == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                mb3_comTeresaTarget = order[i];
                break;
            }
        }
    } else if (mb3_comTeresaType == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                mb3_comTeresaTarget = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        mb3_comTeresaType = 2;
    }
}

s32 MB3_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb3_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    MB3_ComTeresaTargetDecide();
                    var_s2 = mb3_comTeresaType + 1;
                } else {
                    var_s2 = mb3_comTeresaTarget + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
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

s32 MB3_ComTeresaTypeChoice(u8 *arg0) {
    return MB3_ComTeresaChoice(arg0, 0, 1);
}

s32 MB3_ComTeresaPlayerChoice(u8 *arg0) {
    return MB3_ComTeresaChoice(arg0, 1, 0);
}

// entrypoint 0
void MB3_BoardInit(void) {
    GwSystem.current_board_index = 2;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

// entrypoint 1
void MB3_SaveInit(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    MB3Ev_StarShuffle();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[2] = 0;
    omOvlReturnEx(1);
}

void MB3_ObjectSetup(void) {
    s32 i;

    omInitObjMan(0xA0, 0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(9, 0x23C, 0xB, 0);
    MBMasuBlockTblExtSet(mb3_masuBlockExtTbl);
    MBMasuBlockTblSet(mb3_masuBlockTbl);
    MBItemHookSet(0, &MB3Ev_Teresa);
    MBItemHookSet(1, &MB3Ev_ItemMajinLamp);
    MBItemHookSet(9, &MB3Ev_ItemMajinLampStar);
    MBItemHookSet(2, &MB3Ev_ItemWarpBlock);
    MBItemHookSet(3, &MB3Ev_ItemRobBox);
    MBItemHookSet(4, &MB3Ev_KSuitStart);
    MBItemHookSet(5, &MB3Ev_KSuitEnd);
    MBItemHookSet(6, &MB3Ev_ItemKinoko);
    MBItemHookSet(7, &MB3Ev_ItemShake);
    MBItemHookSet(8, &MB3Ev_ItemPhoneMove);
    MBItemHookSet(0xA, &MB3Ev_ItemNKinoko);
    MBItemHookSet(0xB, &MB3Ev_ItemRKinoko);
    MBItemHookSet(0xE, &MB3Ev_ItemShopPhone);
    MBItemHookSet(0xF, &MB3Ev_ItemKoopaPhone);
    MBItemHookSet(0x10, &MB3Ev_ItemStarYoke);
    MBItemHookSet(0x11, &MB3Ev_ItemKeyManUse);
    MBItemHookSet(0x12, &MB3Ev_ItemNullUse);
    MBItemHookSet(0x13, &MB3Ev_ItemExchangeBox);
    MBItemHookSet(0x14, &MB3Ev_ItemGambleCoin);
    MBItemHookSet(0x15, &MB3Ev_ItemAfter5);
    MBItemHookSet(0xC, &MB3Ev_ItemKoopaNKinoko);
    MBItemHookSet(0xD, &MB3Ev_ItemKoopaRKinoko);
    MBComItemDecideHookSet(MB3_ComItemDecide);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, mb3ev_starGuideMasu[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        MB3Ev_StarNextPos();
    }

    MB3Ev_StarMasuInit();
    MB3_StarGuideCreateAll();
    MB3_TeresaGuideCreateAll();
    MB3_BankCoinCreateAll();
    MB3_GateCreateAll();
    MB3_BankMapIconAddAll();
    MB3_ShopMapIconAddAll();
    MB3Ev_KinokoMarkCreateAll();
    MBMasuTypeListCreate();
    omAddPrcObj(MB3_SandPitCreateProc, 0x4800, 0, 0);
}

// entrypoint 2
void MB3_Create(void) {
    HuAudSeqPlay(0x1A);
    mbBoardMusId = 0x1A;
    MBBoardParamSet(0x1A);
    Hu3DCamInit(2);
    MB3_ObjectSetup();
    MBMasuEventTblAdd(mb3_commonEventTbl);
    MBMasuEventTblAdd(mb3_specialEventTbl);
    MBHatenaFuncSet(MB3Ev_Quicksand);
    MBMasuEventTblAdd(mb3_teresaEventTbl);
    MBMasuEventTblAdd(mb3_turnStatusEventTbl);
    MBStart(0);
}

// entrypoint 3
void MB3_BoardReload(void) {
    Hu3DCamInit(1);
    MB3_ObjectSetup();
    MBStart(1);
}

void MB3_StarGuideCreate(s16 arg0) {
    Object *obj;

    if (mb3_starGuideMdl[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    Hu3DModelTPLvlInit(obj->omObj1->model[0]);
    Hu3DModelTPLvlSet(obj->omObj1->model[0], 0xFF);
    Hu3DModelTPLvlInit(obj->omObj2->model[0]);
    Hu3DModelTPLvlSet(obj->omObj2->model[0], 0xFF);
    AuraCreate(obj->omObj1->model[0]);
    if (mb3_starGuideBaseMdl == NULL) {
        mb3_starGuideBaseMdl = obj;
    }
    mb3_starGuideMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    mb3_starGuideHoverProc[arg0] = MBModelHoverCreate(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb3_starGuideMdlMasuTbl[arg0])->coords);
    GwSystem.boardData.halfWordBytes[1] =
        MBMapFullIconMdlAdd(0xB, obj, mb3_starGuideMapIconOfsTbl[arg0][0], mb3_starGuideMapIconOfsTbl[arg0][1]);
}

void MB3_StarGuideKill(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (mb3_starGuideHoverProc[i] != NULL) {
            omDelPrcObj(mb3_starGuideHoverProc[i]);
            mb3_starGuideHoverProc[i] = NULL;
        }
    }
}

void MB3_StarGuideCreateAll(void) {
    s32 i;

    mb3_starGuideBaseMdl = NULL;
    for (i = 0; i < 8; i++) {
        mb3_starGuideMdl[i] = NULL;
        mb3_starGuideHoverProc[i] = NULL;
        MBKinokoEffKillHookSet(MB3_StarGuideKill);
        if (!GWBoardFlagCheck(mb3_starGuideFlagTbl[i])) {
            MB3_StarGuideCreate(i);
        }
    }
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        MB3_StarGuideCreate(GwSystem.boardData.halfWordBytes[0]);
    }
}

void MB3_TeresaGuideCreate(s16 arg0) {
    Object *obj;

    if (mb3_teresaGuideMdl[arg0] != NULL) {
        return;
    }
    if (mb3_teresaGuideBaseMdl == NULL) {
        obj = MBModelCreate(0xA, NULL);
        Hu3DModelTPLvlInit(obj->omObj1->model[0]);
        Hu3DModelTPLvlInit(obj->omObj2->model[0]);
        mb3_teresaGuideBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb3_teresaGuideBaseMdl);
    }
    MBModelDispOff(obj);
    mb3_teresaGuideMdl[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb3_teresaGuideMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xA, obj, mb3_teresaGuideMapIconOfsTbl[arg0][0], mb3_teresaGuideMapIconOfsTbl[arg0][1]);
}

void MB3_TeresaGuideCreateAll(void) {
    s32 i;

    mb3_teresaGuideBaseMdl = 0;
    for (i = 0; i <= 0; i++) {
        mb3_teresaGuideMdl[i] = NULL;
        MB3_TeresaGuideCreate(i);
    }
}

void MB3_BankCoinHide(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(mb3_bankCoinMdl[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(mb3_bankCoinMdl[i * 5 + j]);
        }
    }
}

void MB3_BankCoinCreate(s16 arg0) {
    Object *obj;

    if (mb3_bankCoinMdl[arg0] != NULL) {
        return;
    }
    if (mb3_bankCoinBaseMdl == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        mb3_bankCoinBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb3_bankCoinBaseMdl);
    }
    mb3_bankCoinMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb3_bankCoinMasuTbl[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &mb3_bankCoinOfsTbl[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = mb3_bankCoinRotTbl[arg0 % 5].x;
    obj->omObj1->rot.z = mb3_bankCoinRotTbl[arg0 % 5].z;
    MBModelDispOff(obj);
}

void MB3_BankCoinCreateAll(void) {
    s32 i;

    mb3_bankCoinBaseMdl = 0;
    for (i = 0; i < 0xA; i++) {
        mb3_bankCoinMdl[i] = NULL;
        MB3_BankCoinCreate(i);
    }
    MB3_BankCoinHide();
}

void MB3_GateCreate(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (mb3_gateMdl[arg0] != NULL) {
        return;
    }
    if (mb3_gateBaseMdl == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(mb3_gateMdlTbl[board], mb3_gateMotTbl[board]);
        MBModelTempAllocFree(obj);
        mb3_gateBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb3_gateBaseMdl);
    }
    mb3_gateMdl[arg0] = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb3_gateMasuTbl[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(mb3_gateDirMasuTbl[arg0][0]);
        SpaceData *masuB = MBMasuGet(mb3_gateDirMasuTbl[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    MBMapFullIconMdlAdd(0xC, obj, mb3_gateMapIconOfsTbl[arg0][0], mb3_gateMapIconOfsTbl[arg0][1]);
}

void MB3_GateCreateAll(void) {
    s32 i;

    mb3_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        mb3_gateMdl[i] = NULL;
        MB3_GateCreate(i);
    }
}

void MB3_GateOpenSeProc(void) {
    HuPrcSleep(mb3_gateOpenDelayTbl[GwSystem.current_board_index]);
    HuAudFXPlay((s16)mb3_gateOpenDelaySeTbl[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void MB3_GateOpen(s32 arg0, s32 arg1) {
    MBMotionSet(mb3_gateMdl[arg0], arg1 - 1, 0);
    Hu3DMotionAttrSet(mb3_gateMdl[arg0]->omObj1->model[0], 5, 0);
    if (mb3_gateOpenSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb3_gateOpenSeTbl[GwSystem.current_board_index]);
    }

    if (mb3_gateOpenDelaySeTbl[GwSystem.current_board_index] != -1) {
        omAddPrcObj(MB3_GateOpenSeProc, 0x1000, 0, 0);
    }
}

void MB3_GateCloseProc(void) {
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
    Hu3DMotionAttrSet(mb3_gateMdl[index]->omObj1->model[0], 1, 4);

    if (mb3_gateCloseSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb3_gateCloseSeTbl[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void MB3_GateClose(s32 arg) {
    Process *prc = omAddPrcObj(MB3_GateCloseProc, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB3_BankMapIconAddAll(void) {
    s32 i;

    mb3_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(8, &MBMasuGet(mb3_bankMapIconMasuTbl[i])->coords, mb3_bankMapIconOfsTbl[i][0],
                                   mb3_bankMapIconOfsTbl[i][1]);
    }
}

void MB3_ShopMapIconAddAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(9, &MBMasuGet(mb3_shopMapIconMasuTbl[i])->coords,
                                   mb3_shopMapIconOfsTbl[i][0], mb3_shopMapIconOfsTbl[i][1]);
    }
}

s32 MB3_ComMirageFirstCheck(s16 *arg0) {
    s16 *ptr = arg0;
    s32 i = 0;
    s32 ret = 0;

    for (; i < 8; i++) {
        if (*ptr == GwSystem.boardData.halfWordBytes[0]) {
            ret = 1;
            break;
        }
        if (GWBoardFlagCheck(mb3_comMirageStarFlagTbl[*ptr]) == 0) {
            break;
        }
        ptr++;
    }
    return ret;
}

s32 MB3_ComMirageCheck(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *list;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x79:
            list = mb3_comMirageOrder0Tbl;
            break;
        case 0x84:
            list = mb3_comMirageOrder1Tbl;
            break;
        case 0x89:
            list = mb3_comMirageOrder2Tbl;
            break;
        case 0x8A:
            list = mb3_comMirageOrder3Tbl;
            break;
        case 0x8B:
            list = mb3_comMirageOrder4Tbl;
            break;
        case 0x6F:
            list = mb3_comMirageOrder5Tbl;
            break;
        default:
            list = mb3_comMirageOrder6Tbl;
            break;
    }

    if (MB3_ComMirageFirstCheck(list)) {
        GwSystem.boardData.halfWordBytes[2] |= 1 << GwSystem.current_player_index;
    } else {
        GwSystem.boardData.halfWordBytes[2] &= ~(1 << GwSystem.current_player_index);
    }
    return 0;
}

void MB3Ev_Branch1(void) {
    MBMoveNextMasuSet(-1, 1, 7);
}

void MB3Ev_Branch2(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6D) {
        if (player->rev & 0x80) {
            if (mbWalkNum != 0) {
                MB3Ev_BranchMain(mb3ev_branch2Masu, mb3ev_branch2Link, mb3ev_branch2ComTree);
            } else {
                MBMoveBackMasuSet(-1, 1, 8);
            }
        } else {
            MBMoveBackMasuSet(-1, 1, 6);
        }
    }
}

void MB3Ev_Branch3(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x41 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 2, 0);
        player->rev &= ~1;
    } else {
        MB3Ev_BranchMain(mb3ev_branch3Masu, mb3ev_branch3Link, mb3ev_branch3ComTree);
    }
    omDelPrcObj(NULL);
}

void MB3Ev_Branch4(void) {
    MB3Ev_BranchMain(mb3ev_branch4Masu, mb3ev_branch4Link, mb3ev_branch4ComTree);
    omDelPrcObj(NULL);
}

void MB3Ev_Branch5(void) {
    MB3Ev_BranchMain(mb3ev_branch5Masu, mb3ev_branch5Link, mb3ev_branch5ComTree);
    omDelPrcObj(NULL);
}

void MB3Ev_Branch6(void) {
    MB3Ev_BranchMain(mb3ev_branch6Masu, mb3ev_branch6Link, mb3ev_branch6ComTree);
    omDelPrcObj(NULL);
}

void MB3Ev_Branch7(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x32 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 9, 0);
        player->rev &= ~1;
    } else {
        MB3Ev_BranchMain(mb3ev_branch7Masu, mb3ev_branch7Link, mb3ev_branch7ComTree);
    }
    omDelPrcObj(NULL);
}

void MB3Ev_Branch8(void) {
    MB3Ev_BranchMain(mb3ev_branch8Masu, mb3ev_branch8Link, mb3ev_branch8ComTree);
    omDelPrcObj(NULL);
}

void MB3Ev_Branch9RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB3Ev_BranchMain(mb3ev_branch9Masu, mb3ev_branch9Link, mb3ev_branch9ComTree);
    }
}

void MB3Ev_Branch10RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB3Ev_BranchMain(mb3ev_branch10Masu, mb3ev_branch10Link, mb3ev_branch9ComTree);
    }
}

void MB3Ev_Branch11RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB3Ev_BranchMain(mb3ev_branch11Masu, mb3ev_branch11Link, mb3ev_branch11ComTree);
    }
}

void MB3Ev_Branch12RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB3Ev_BranchMain(mb3ev_branch12Masu, mb3ev_branch12Link, mb3ev_branch12ComTree);
    }
}

void MB3Ev_Branch13RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    UnkEA790Struct *win;
    s32 sel;
    s32 comChoice;
    s32 count;
    s32 i;

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        MB3_BranchHelpStart();
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb3ev_branch13RKinokoFrom98Masu);
                comChoice = MBRand(3.0f);
                break;
            case 0x46:
                win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb3ev_branch13RKinokoFrom70Masu);
                comChoice = 2;
                break;
            case 0x45:
                win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb3ev_branch13RKinokoFrom69Masu);
                comChoice = MBRand(3.0f);
                break;
            default:
                win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb3ev_branch13RKinokoMasu);
                comChoice = MBRand(3.0f);
                break;
        }
        MBBranchSelStart(win, GwSystem.current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            count = comChoice;
            for (i = 0; i < count; i++) {
                MBBranchSelMesSend(win, -2);
            }
            MBBranchSelMesSend(win, -4);
        }
        sel = MBBranchSelWait(win);
        MBBranchArrowGrpKill(win);
        MB3_BranchHelpEnd();
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x46:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x45:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            default:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                }
                break;
        }
    }
}

void MB3Ev_Merge1(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3B) {
        MBMoveNextMasuSet(-1, 0xB, 0xB);
    }
}

void MB3Ev_Merge2(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x43) {
        MBMoveNextMasuSet(-1, 1, 0xD);
    }
}

void MB3Ev_Merge3(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 8) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void MB3Ev_Merge4(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 2, 2);
    }
}

void MB3Ev_Merge5(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xD) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void MB3Ev_Merge6(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xF) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void MB3Ev_Merge7(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x54) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void MB3Ev_Merge8(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5B) {
        MBMoveNextMasuSet(-1, 5, 0xA);
    }
}

void MB3Ev_Merge9(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 0x19);
    }
}

void MB3Ev_Merge10(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2F) {
        MBMoveNextMasuSet(-1, 5, 0x14);
    }
}

void MB3Ev_Merge11(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x8B) {
        MBMoveNextMasuSet(-1, 5, 0x19);
    }
}

void MB3Ev_Merge12(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5E) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void MB3Ev_Merge13(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x51) {
        MBMoveNextMasuSet(-1, 5, 0x12);
    }
}

void MB3Ev_Merge14(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(-1, 1, 0xD);
    }
}

void MB3Ev_Merge15(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x44) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void MB3Ev_Merge16(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x33) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void MB3Ev_Merge17(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2) {
        MBMoveNextMasuSet(-1, 0xB, 0xB);
    }
}

s32 MB3Ev_KeyManChoiceGet(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb3_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1;
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
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

void MB3Ev_KeyManMasu(void) {
    s32 moveOn = TRUE;
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    s32 choice;
    UnkVibrateProcess *vibrate;

    if ((masu == 0x74 || masu == 0x8C) && (player->rev & 1)) {
        goto end;
    }
    if ((masu == 0x75 || masu == 0x8D) && !(player->rev & 1)) {
        goto end;
    }

    MBPlayerMotionSet(-1, -1, 2);
    if (MBItemFind(sys->current_player_index, 1) != -1) {
        MBSaiNumKill(sys->current_player_index);
        switch (masu) {
            case 0x74:
            case 0x75:
                MBPlayerRotMasuStart(-1, 8, 0x7D);
                break;
            default:
                MBPlayerRotMasuStart(-1, 8, 0x7E);
                break;
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        MBPlayerVibrate(-1, 1);
    retry:
        MBDlgWinCreate(0x38, 0x4103);
        choice = MB3Ev_KeyManChoiceGet(0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                MBDlgWinExec(0x38, 0x4104);
                GwPlayer[sys->current_player_index].itemNo[MBItemFind(sys->current_player_index, 1)] = -1;
                MBItemRemoveEmpty(GwSystem.current_player_index);
                MBStatusItemIconSprReinit(-1);
                switch (masu) {
                    case 0x74:
                        MB3_GateOpen(0, 0);
                        break;
                    case 0x75:
                        MB3_GateOpen(0, 1);
                        break;
                    case 0x8C:
                        MB3_GateOpen(1, 0);
                        break;
                    default:
                        MB3_GateOpen(1, 1);
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
                MB3_MapScroll();
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
            case 0x74:
                MBMoveNextMasuSet(-1, 10, 1);
                player->rev |= 1;
                break;
            case 0x75:
                MBMoveNextMasuSet(-1, 10, 5);
                player->rev &= ~1;
                break;
            case 0x8C:
                MBMoveNextMasuSet(-1, 11, 2);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 11, 6);
                player->rev &= ~1;
                break;
        }
    }

end:
    omDelPrcObj(NULL);
}

void MB3Ev_BankMasuBranch(void) {
}

void MB3Ev_StarMasuBranch(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 2 &&
        MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x63) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void MB3Ev_TeresaMasuBranch(void) {
}

s32 MB3Ev_YesNoChoiceGet(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb3_padBitTbl;

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
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
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

void MB3Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void MB3Ev_ItemSelAttrProc(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void MB3Ev_StarMasu(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;
    Object *star;
    s32 alpha;
    SpaceData *space;
    f32 scale;
    f32 origScale;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = MB3Ev_StarCheck(spaceIdx);
    if (spaceIdx == 1) {
        MBSaiNumKill(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        MBPlayerRotMasuStart(-1, 8, MB3Ev_StarGuideMasuGet());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuPrcSleep(20);
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
                choice = MB3Ev_YesNoChoiceGet(2, 0);
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
                        MB3Ev_StarGetExec(mb3_starGuideBaseMdl);
                        HuPrcSleep(30);
                        MBBoardRestartSet();
                        MBExitReq(2);
                        goto end;
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
                        goto end;
                    case 2:
                        MB3_MapScroll();
                        goto purchaseMenu;
                    default:
                        goto end;
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

end:
    if (spaceIdx == 2) {
        MBSaiNumKill(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        MBPlayerRotMasuStart(-1, 8, mb3ev_starGuideMasu[GwSystem.boardData.halfWordBytes[0]]);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuPrcSleep(20);
        HuAudFXPlay(0x19C);

        star = mb3_starGuideMdl[GwSystem.boardData.halfWordBytes[0]];
        for (alpha = 0xFF; alpha > 0; alpha -= 10) {
            Hu3DModelTPLvlSet(star->omObj1->model[0], alpha);
            Hu3DModelTPLvlSet(star->omObj2->model[0], alpha);
            HuPrcVSleep();
        }
        MBModelDispOff(star);
        GWBoardFlagSet(0x12);
        MBMapFullIconRemove(GwSystem.boardData.halfWordBytes[1]);

        space = MBMasuGet(mb3ev_starMasu[GwSystem.boardData.halfWordBytes[0]]);
        origScale = space->rot.x;
        for (scale = origScale; scale > 0.0f; scale -= origScale / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, 0.0f, 0.0f, 0.0f);
        MBMasuTypeSet(mb3ev_starMasu[GwSystem.boardData.halfWordBytes[0]], 1);
        MBMasuTypeListCreate();
        for (; scale < origScale; scale += origScale / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, origScale, origScale, origScale);

        GwSystem.boardData.halfWordBytes[0] = -1;
        MBDlgResultWinExec(0x800);
        MBSaiNumShow(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }

    MB3Ev_StarMasuBranch();
}

const char mb3ev_numFmtStr[] = "%d";

void MB3Ev_BankMasu(void) {
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
        case 0x1C:
            MBPlayerRotMasuStart(-1, 8, 0x7B);
            spaceA = MBMasuGet(0x7B);
            spaceB = MBMasuGet(0x1C);
            break;
        case 0x5F:
            MBPlayerRotMasuStart(-1, 8, 0x78);
            spaceA = MBMasuGet(0x78);
            spaceB = MBMasuGet(0x5F);
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

    effectModel = MBModelCreate(0x35, mb3ev_bankCoinPileMot);
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
        choice = MB3Ev_YesNoChoiceGet((s32)mb3ev_bankComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                MB3_MapScroll();
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
        sprintf(sp20, mb3ev_numFmtStr, GwSystem.bank_coins);
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
            MB3Ev_BankKoopaCardExec();
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
                sprintf(sp20, mb3ev_numFmtStr, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, mb3ev_numFmtStr, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                MB3_BankCoinHide();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                MBDlgWinOpen();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, mb3ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, mb3ev_numFmtStr, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                MB3_BankCoinHide();
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
                sprintf(sp20, mb3ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinMesWait();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                MB3_BankCoinHide();
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
    MB3Ev_BankMasuBranch();
}

s32 MB3Ev_ShopItemIdxGet(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb3ev_shopItemEnableTbl[i] != 0 && mb3ev_shopItemTbl[mb3ev_shopHostNo][mb3ev_shopItemRow][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 MB3Ev_ShopItemNumGet(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb3ev_shopItemTbl[mb3ev_shopHostNo][mb3ev_shopItemRow][i] == -1) {
            break;
        }
    }
    return i;
}

void MB3Ev_ShopBagBounceProc(void) {
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

void MB3Ev_ShopMasu(void) {
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
        case 0x6E:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x6E);
            mb3ev_shopNo = 0;
            break;
        case 0x71:
            camMasu = 0x77;
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x71);
            mb3ev_shopNo = 1;
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
            effectModel = MBModelCreate(0x39, mb3ev_shopKoopaJrMot);
        } else {
            effectModel = MBModelCreate(0x1B, mb3ev_shopKinopioMot);
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
        MBDlgWinExec(dlgWin, mb3ev_shopLastTurnMesTbl[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, mb3ev_shopItemFullMesTbl[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, mb3ev_shopNoCoinMesTbl[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, mb3ev_shopEnterMesTbl[shopIdx]);
    choice = MB3_ComShopEnterChoice();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = MBTurnTierGet(-1);
            row = mb3ev_shopItemRowTbl[shopIdx][i][MBPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (mb3ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mb3ev_shopItemTbl[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (mb3ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mbItemPriceTbl[mb3ev_shopItemTbl[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, mb3ev_shopItemMesTbl[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            MBDlgWinTabWidthSet(0);
            mb3ev_shopHostNo = slot;
            mb3ev_shopItemRow = row;
            mb3ev_shopItemEnableTbl = enabled;
            sel = MB3_ComShopItemChoice(enabled);
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
            shopTable = mb3ev_shopItemTbl;
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
                    mb3ev_shopItemTbl[shopIdx][row][sel];
                item = mb3ev_shopItemTbl[shopIdx][row][sel];
            }

            grp = HuSprGrpCreate(1, 5);
            i = 0;
            data = DataRead(mbItemIconSprTbl[item]);
            spriteId = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(grp, 0, spriteId, 0);
            HuSprPriSet(grp, 0, 0xA);
            HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
            HuSprAttrSet(grp, 0, 0x180C);
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

            if (mb3ev_shopItemTbl[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = mb3ev_shopBagRowTbl[shopIdx][MBTurnTierGet(-1)]
                                         [MBPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < mb3ev_shopBagRateTbl[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = mb3ev_shopBagItemTbl[shopIdx][i];

                    if (camMasu != -1) {
                        helpWin = MBHelpWinCreate(0x15, 0xA0, 1);
                    } else {
                        playerObj->flags |= 0x10;
                        helpWin = MBHelpWinCreate(0x15, 0xA0, 0);
                    }
                    timer = 30;

                    if ((*(u16 *)((u8 *)ContBtnDown + (GwPlayer[system->current_player_index].pad << 1)) & 0x8000) == 0) {
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
                    prc = omAddPrcObj(MB3Ev_ShopBagBounceProc, 0x4002, 0, 0);
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
                    HuSprAttrSet(grp2, 0, 0x1000);
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
            MBDlgWinExec(dlgWin, mb3ev_shopCancelMesTbl[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                MB3_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB3_MapScroll();
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

void MB3Ev_TeresaFadeIn(Object *obj) {
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

void MB3Ev_TeresaFadeOut(Object *obj) {
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

s32 MB3Ev_TeresaStarSteal(s32 playerIndex) {
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
    HuSprAttrSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, mb3ev_teresaSprPosTbl[playerIndex].x,
                mb3ev_teresaSprPosTbl[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        HuSprPosSet(grp, 0,
                    (i * mb3ev_teresaSprDirTbl[playerIndex].x) +
                        mb3ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                        mb3ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(MB3Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                    (mb3ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].x,
                    (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].y +
                        (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        HuSprPosSet(grp, 0,
                    (i * mb3ev_teresaSprDirTbl[playerIndex].x) +
                        mb3ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                        mb3ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    return !hasRareItem;
}

void MB3Ev_TeresaWinCloseProc(void) {
    MBWinClose();
    omDelPrcObj(NULL);
}

s32 MB3Ev_TeresaSteal(s32 playerIndex) {
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
    HuSprAttrSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, mb3ev_teresaSprPosTbl[playerIndex].x,
                mb3ev_teresaSprPosTbl[playerIndex].y);
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
            HuSprAttrSet(playerGrp, 0, 0x1001);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x1000);
        }
        if (MBItemFind(playerIndex, 0xC) != -1) {
            HuSprDispOff(playerGrp, 0);
        }
        HuSprPosSet(playerGrp, 0,
                    mb3ev_teresaSprPosTbl[playerIndex].x -
                        (mb3ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    mb3ev_teresaSprPosTbl[playerIndex].y +
                        (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f));
        HuSprTPLvlSet(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            HuSprPosSet(grp, 0,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].x) +
                            mb3ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                            mb3ev_teresaSprPosTbl[playerIndex].y);
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
            omAddPrcObj(MB3Ev_TeresaWinCloseProc, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(MB3Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                    (mb3ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].x,
                    (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                HuSprPosSet(
                    grp, 0,
                    (mb3ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].y);
                HuSprPosSet(
                    playerGrp, 0,
                    mb3ev_teresaSprPosTbl[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].y);
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
                            playerGrp, 0, mb3ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                            (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                                mb3ev_teresaSprPosTbl[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                HuSprBankSet(playerGrp, 0, 0, 0);
                HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
                playerSpriteVisible = 0;
                HuSprPosSet(
                    playerGrp, 0,
                    mb3ev_teresaSprPosTbl[playerIndex].x -
                        (mb3ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    (mb3ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb3ev_teresaSprPosTbl[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(MB3Ev_TeresaWinCloseProc, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].x) +
                            mb3ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                            mb3ev_teresaSprPosTbl[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].x) +
                            mb3ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                            mb3ev_teresaSprPosTbl[playerIndex].y);
            HuSprPosSet(playerGrp, 0,
                        ((i - 0x10) * mb3ev_teresaSprDirTbl[playerIndex].x) +
                            mb3ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                        (i * mb3ev_teresaSprDirTbl[playerIndex].y) +
                            mb3ev_teresaSprPosTbl[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(mb3ev_teresaCoinTurnTbl); i++) {
            if ((GwSystem.current_turn >= mb3ev_teresaCoinTurnTbl[i][0]) &&
                (GwSystem.current_turn <= mb3ev_teresaCoinTurnTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible = mb3ev_teresaCoinTurnTbl[i][2];
        for (i = 0; i < ARRAY_COUNTU(mb3ev_teresaCoinPenaltyTbl); i++) {
            if ((attempts >= mb3ev_teresaCoinPenaltyTbl[i][0]) &&
                (attempts <= mb3ev_teresaCoinPenaltyTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= mb3ev_teresaCoinPenaltyTbl[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void MB3Ev_TeresaCoin(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb3ev_teresaCoinMdl);
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

void MB3Ev_TeresaCoinCreate(s32 arg) {
    Process *prc = omAddPrcObj(MB3Ev_TeresaCoin, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB3Ev_Teresa(void) {
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
    if (spaceId != 0x8E) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(mb3_teresaGuideBaseMdl);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x6C;
        space = MBMasuGet(0x6C);
        boo = mb3_teresaGuideMdl[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
            if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    MB3Ev_TeresaFadeIn(boo);
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
    menuResult = MB3_ComTeresaTypeChoice(choices);
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
    playerChoice = MB3_ComTeresaPlayerChoice(choices);
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
                MB3_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB3_MapScroll();
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
            if (rank < mb3ev_teresaComTargetRateTbl[i]) {
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
            if (GwSystem.current_turn >= mb3ev_teresaCoinTurnTbl[i][0] &&
                GwSystem.current_turn <= mb3ev_teresaCoinTurnTbl[i][1]) {
                break;
            }
        }
        estimatedAmount = mb3ev_teresaCoinTurnTbl[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    MB3Ev_TeresaFadeOut(boo);
    if (menu == 0) {
        resultAmount = MB3Ev_TeresaSteal(target);
        MB3Ev_TeresaFadeIn(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], mb3ev_numFmtStr, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], mb3ev_numFmtStr, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= mb3ev_teresaCoinDiffTbl[i]) {
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
            mb3ev_teresaCoinMdl = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(mb3ev_teresaCoinMdl);
            MBModelDispOff(mb3ev_teresaCoinMdl);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    MB3Ev_TeresaCoinCreate((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(mb3ev_teresaCoinMdl);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = MB3Ev_TeresaStarSteal(target);
        MB3Ev_TeresaFadeIn(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            mb3ev_starGetTeresaF = 1;
            MB3Ev_StarGetExec(boo);
            mb3ev_starGetTeresaF = 0;
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
    MB3Ev_TeresaFadeOut(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        MB3_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
    } else {
        MB3_MapScroll();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        MB3Ev_TeresaFadeOut(boo);
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
            if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb3ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
    MB3Ev_TeresaMasuBranch();
}

void MB3Ev_Gate1Close(void) {
    MB3_GateClose(0);
}

void MB3Ev_Gate2Close(void) {
    MB3_GateClose(1);
}

omObjData *MB3Ev_ItemLampSmokeCreate(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, MB3Ev_ItemLampSmokeObjMain);
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

void MB3Ev_ItemLampSmokeObjMain(omObjData *arg0) {
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

void MB3Ev_ItemMajinLamp(void) {
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
    MB3Ev_ItemUseFadeOut();
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
            MB3Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    MBMasuLinkIdxGet(
        mb3ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
            MB3Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            msmMusPause(0);
        }
    }
}

void MB3Ev_ItemMajinLampStar(void) {
    s16 ret;

    mbStarMusF = 1;
    MBMasuEventCall(mb3ev_starMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    mbStarMusF = 0;
    ret = MBExitFlagGet();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void MB3Ev_ItemWarpBlock(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MB3Ev_ItemUseFadeOut();
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

void MB3Ev_ItemMove(void) {
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

Process *MB3Ev_ItemMoveCreate(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                           s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(MB3Ev_ItemMove, 0x4002, 0, 0x40);
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

void MB3Ev_ItemKinoko(void) {
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
    HuPrcChildLink(process, MB3Ev_ItemMoveCreate(
                                mbItemCursorGrpId, position[0], position[1],
                                mb3ev_itemUsePosTbl[system->current_player_index].x,
                                mb3ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB3Ev_ItemUseFadeOut(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    MB3Ev_ItemMoveCreate(
        mbItemCursorGrpId, position[0], position[1],
        mb3ev_itemFadePosTbl[system->current_player_index].x,
        mb3ev_itemFadePosTbl[system->current_player_index].y, -1);
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

void MB3Ev_ItemCursorReturn(void) {
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
                   MB3Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     targetX, targetY, -1));
    HuPrcChildWatch();

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB3Ev_ItemShake(void) {
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
                   MB3Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb3ev_itemUsePosTbl[system->current_player_index].x,
                                     mb3ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB3Ev_ItemPhoneMove(void) {
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
                   MB3Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb3ev_itemUsePosTbl[system->current_player_index].x,
                                     mb3ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB3Ev_ItemIconMove(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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

void MB3Ev_KSuitStart(void) {
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
    Hu3DModelAttrSet(model->omObj1->model[0], 0x180, 0);
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

void MB3Ev_KSuitEnd(void) {
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
    Hu3DModelAttrSet(model->omObj1->model[0], 0x180, 0);
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

void MB3Ev_ItemPhoneWaveProc(void) {
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
    HuSprGrpMemberSet(group, 0, mb3ev_itemPhoneWaveSpr, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    HuSprPosSet(group, 0, x, y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)mb3ev_itemPhoneWaveAngleTbl[index];
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

void MB3Ev_ItemShopPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb3ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB3Ev_ItemPhoneMove();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = MB3Ev_YesNoChoiceGet((s32)mb3ev_shopPhoneComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(MB3Ev_ItemSelAttrProc, 0, 0, 0);
                omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
                MB3_MapScrollCancel();
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

        process = omAddPrcObj(MB3Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
        MB3_MapScrollCancel();
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
            process = omAddPrcObj(MB3Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB3Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb3ev_itemPhoneWaveSpr);
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
    MB3Ev_ShopMasu();
    GwSystem.forceShopHost = 0;
}

void MB3Ev_ItemKoopaPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 i;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb3ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB3Ev_ItemPhoneMove();

    HuPrcSleep(30);
    HuAudFXPlay(0x147);
    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB3Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        process->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB3Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
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
        choice = MB3Ev_YesNoChoiceGet(1, 0);
    } else {
        choice = MB3Ev_YesNoChoiceGet(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = MBPlayerRankRandGet(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(MB3Ev_ItemSelAttrProc, 0, 0, 0);
            omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
            MB3_MapScrollCancel();
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
    HuSprAnimKill(mb3ev_itemPhoneWaveSpr);

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

void MB3Ev_ItemStarYoke(void) {
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
        MB3Ev_ItemUseFadeOut();

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
            MB3Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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
            MB3Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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
            WipeCreateOut(0xB, 0x32);
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

        space = MBMasuGet(mb3ev_starMasu[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(mb3ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
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
    WipeCreateIn(0xB, 0x32);
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
        if (mb3_starGuideHoverProc[j] != NULL) {
            omDelPrcObj(mb3_starGuideHoverProc[j]);
            mb3_starGuideHoverProc[j] = NULL;
        }
    }

    targetStar = mb3_starGuideMdl[system->star_spawn_indices[system->current_star_spawn]];
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

void MB3Ev_ItemKeyManUse(void) {
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
    HuSprAttrSet(group, 0, 0x9000);
    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB3Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb3ev_itemUsePosTbl[system->current_player_index].x,
                                     mb3ev_itemUsePosTbl[system->current_player_index].y, -1));
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
    result = MB3Ev_YesNoChoiceGet((s32)&mb3ev_keyManUseComTree, 0);
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
            MB3_MapScrollCancel();
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

void MB3Ev_TereYokeSparkProc(void) {
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
    HuSprGrpMemberSet(setupGroup, 0, mb3ev_tereYokeSparkSpr, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    MBStatusItemPosGet(mb3ev_tereYokePlayer, 0, &xPos, &yPos);

    xPos = (s32)((mb3ev_teresaSprDirTbl[mb3ev_tereYokePlayer].x * 16.0f) +
                 mb3ev_teresaSprPosTbl[mb3ev_tereYokePlayer].x);
    yPos = (s32)((mb3ev_teresaSprDirTbl[mb3ev_tereYokePlayer].y * 16.0f) +
                 mb3ev_teresaSprPosTbl[mb3ev_tereYokePlayer].y);
    HuSprPosSet(
        setupGroup, 0, (f32)xPos + mb3ev_tereYokeSparkOfsTbl[playerIndex].x,
        (f32)yPos + mb3ev_tereYokeSparkOfsTbl[playerIndex].y);
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

void MB3Ev_TereYokeSprayProc(void) {
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
    mb3ev_tereYokeSparkSpr = HuSprAnimRead(data);
    DataClose(data);

    group = HuSprGrpCreate(2, 2);
    setupGroup = group;
    HuSprAnimModeSet(setupGroup, 0, HUSPR_ANIM_MODE_BANK);
    HuSprGrpMemberSet(setupGroup, 0, itemSpriteId, 0xC);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    HuSprParentSet(setupGroup, 0, -1);
    HuSprGrpMemberSet(setupGroup, 1, auraSpriteId, 0);
    HuSprPriSet(setupGroup, 1, 9);
    HuSprAttrSet(setupGroup, 1, 0x9000);
    HuSprColorSet(setupGroup, 1, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(setupGroup, 1, 0xFF);
    HuSprScaleSet(setupGroup, 1, 2.0f, 2.0f);
    HuSprParentSet(setupGroup, 1, 0);

    yPos = 0xC8;
    if (playerIndex & 1) {
        HuSprAttrSet(setupGroup, 0, 1);
        HuSprAttrSet(setupGroup, 1, 1);
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
    mb3ev_tereYokePlayer = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(MB3Ev_TereYokeSparkProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb3ev_tereYokeSparkSpr);
    HuSprAnimKill(auraSpriteId);
    HuSprAnimKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void MB3Ev_ItemNullUse(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void MB3Ev_KoopaCardCoinProc(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb3ev_koopaCardCoinMdl);
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

void MB3Ev_KoopaCardCoinCreate(Object *arg) {
    Process *temp = omAddPrcObj(MB3Ev_KoopaCardCoinProc, 0x1000, 0, 0);

    temp->user_data = arg;
}

void MB3Ev_KoopaCardSpinProc(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        mb3ev_koopaCardMdl->rot.x = -sindf(angle);
        mb3ev_koopaCardMdl->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            mb3ev_koopaCardMdl->scale.z = scale;
            mb3ev_koopaCardMdl->scale.y = scale;
            mb3ev_koopaCardMdl->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    mb3ev_koopaCardMdl->scale.x = mb3ev_koopaCardMdl->scale.y = mb3ev_koopaCardMdl->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(mb3ev_koopaCardMdl);
    omDelPrcObj(0);
}

void MB3Ev_BankKoopaCardExec(void) {
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
    MB3Ev_ItemUseFadeOut();

    mb3ev_koopaCardMdl = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&mb3ev_koopaCardMdl->coords, &MBPlayerGet(-1)->player_obj->coords);
    mb3ev_koopaCardMdl->velocity.x = 100.0f;
    while (30.0f < mb3ev_koopaCardMdl->velocity.x) {
        mb3ev_koopaCardMdl->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(MB3Ev_KoopaCardSpinProc, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    mb3ev_koopaCardCoinMdl = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(mb3ev_koopaCardCoinMdl);
    MBModelDispOff(mb3ev_koopaCardCoinMdl);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                MB3Ev_KoopaCardCoinCreate(mb3ev_koopaCardMdl);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                MB3_BankCoinHide();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(mb3ev_koopaCardCoinMdl);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 MB3_ComItemTargetChoice(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)mb3_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = mb3_comExchangeBoxTarget + 1;
                } else {
                    delay = mb3_comRobBoxTarget + 1;
                }
                inputs[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, buttons[GwPlayer[i].pad]);
                inputs[GwPlayer[i].pad] = -1;
            }
        } else {
            inputs[GwPlayer[i].pad] = 0;
        }
    }

    if (delay != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; delay != 0; j++) {
            if (--delay == 0) {
                inputs[GwPlayer[GwSystem.current_player_index].pad] = 0x8000;
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

void MB3Ev_ExchangeItemFadeOutProc(void) {
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

void MB3Ev_ExchangeItemFadeInProc(void) {
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

void MB3Ev_ItemExchangeBox(void) {
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

    MB3Ev_ItemUseFadeOut();
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
    targetPlayer = MB3_ComItemTargetChoice(choices, 1);
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
                    MB3Ev_ItemIconMove(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(MB3Ev_ExchangeItemFadeOutProc, 0x4800, 0, 0);
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
        process = omAddPrcObj(MB3Ev_ExchangeItemFadeInProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB3Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB3Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB3Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                MB3Ev_ItemIconMove(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB3Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB3Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                MB3Ev_ItemIconMove(targetPlayer, 2, 7, &target.x, 2);
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

void MB3Ev_GambleCoinEffProc(void) {
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

void MB3Ev_GambleCoinProc(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = mb3ev_gambleCoinMdl;
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
        if (mb3ev_gambleCoinPlayer != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(mb3ev_gambleCoinPlayer)->player_obj->coords);
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
    process = omAddPrcObj(MB3Ev_GambleCoinEffProc, 0x4800, 0, 0x40);
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

void MB3Ev_ItemGambleCoin(void) {
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
    MB3Ev_ItemUseFadeOut();
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
    mb3ev_gambleCoinMdl = gameGuyModel;
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
    choice = MB3Ev_YesNoChoiceGet(0, 0);
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
    MB3_MapScrollCancel();
    winPauseF = 1;
    omAllPause();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(MB3Ev_GambleCoinProc, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        mb3ev_gambleCoinPlayer = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        mb3ev_gambleCoinPlayer = choice;
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
        MB3Ev_WinPlayerKeyExec(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        MB3Ev_WinPlayerKeyExec(10, 0x2F02, -1, choice);
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
        MB3Ev_WinPlayerKeyExec(10, 0x2F01, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x <= 100.0f) {
            coinModel->velocity.x += 4.0f;
            HuPrcVSleep();
        }
        MBModelKill(coinModel);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBPlayerComCheck((s16)choice) != 0 && system->show_com_minigames != 0) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(coinModel);
        MBModelJumpSet(playerObj, 0, 0);
        playerObj->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        randomValue = MBRand(100.0f) + 1;
        for (rewardIndex = 0; rewardIndex < 7; rewardIndex++) {
            if (randomValue <= mb3ev_gambleRateTbl[rewardIndex].threshold) {
                break;
            }
        }
        if (mb3ev_gambleRateTbl[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * mb3ev_gambleRateTbl[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, mb3ev_numFmtStr, rewardAmount);
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
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
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
        if (randomValue < mb3ev_gambleMgRateTbl[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = mb3ev_gambleMgTbl[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    MBGameModeMgSet();
    omAllUPause();
    MBExitReq(2);
    HuPrcSleep(-1);
}

void MB3Ev_After5ItemMove(s32 arg0, s32 arg1, f32 *arg2) {
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

void MB3Ev_After5LineShow(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            HuSprPosSet(mb3ev_after5GrpId[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(mb3ev_after5GrpId[idx], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(mb3ev_after5GrpId[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprDispOn(mb3ev_after5GrpId[idx], 0);
    for (i = 0; i < 255; i += 255 / divisor) {
        HuSprTPLvlSet(mb3ev_after5GrpId[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mb3ev_after5GrpId[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void MB3Ev_After5NumFade(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = mb3ev_after5NumColorTbl[i].r;
        sp18.g = mb3ev_after5NumColorTbl[i].g;
        sp18.b = mb3ev_after5NumColorTbl[i].b;

        sp28.r = (mb3ev_after5NumColorTbl[i + 1].r - sp18.r) / 30;
        sp28.g = (mb3ev_after5NumColorTbl[i + 1].g - sp18.g) / 30;
        sp28.b = (mb3ev_after5NumColorTbl[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(mb3ev_after5GrpId[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(mb3ev_after5GrpId[3], 0, mb3ev_after5NumColorTbl[i + 1].r, mb3ev_after5NumColorTbl[i + 1].g, mb3ev_after5NumColorTbl[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void MB3Ev_After5Effect(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = mb3ev_after5EffMdl;
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

void MB3Ev_ItemAfter5(void) {
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
    HuSprAttrSet(temp_s4, 0, 0x1000U);
    for (i = 0; i < 4; i++) {
        mb3ev_after5GrpId[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(mb3ev_after5GrpId[i], 0, sp18[i], 0);
        HuSprPriSet(mb3ev_after5GrpId[i], 0, 0x4780U);
        HuSprAttrSet(mb3ev_after5GrpId[i], 0, 0x980CU);
        HuSprTPLvlSet(mb3ev_after5GrpId[i], 0, 0U);
        HuSprColorSet(mb3ev_after5GrpId[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    mb3ev_after5EffMdl = temp_v0_3;
    Hu3DModelAttrSet(temp_v0_3->omObj1->model[0], 0x180, 0);
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
    MB3Ev_After5ItemMove(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    MB3Ev_After5ItemMove(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(MB3Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    MB3Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(MB3Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    MB3Ev_After5ItemMove(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(MB3Ev_After5LineShow, 0x4002U, 0, 0);
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
        HuSprDispOff(mb3ev_after5GrpId[i], 0);
    }

    HuSprDispOn(mb3ev_after5GrpId[3], 0);
    HuSprTPLvlSet(mb3ev_after5GrpId[3], 0, 0xFFU);
    HuSprPosSet(mb3ev_after5GrpId[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB3Ev_After5NumFade, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(MB3Ev_After5Effect, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(mb3ev_after5GrpId[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
        if (i >= (2880 / 2 + 1)) {
            sp40 = 1;
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 0x32);
    MBPlayerVibrateObjKill(temp_s1_2);

    for (var_f20 = 0.0f; WipeStatGet() != 0; var_f20 += 0.1f) {
        HuSprScaleSet(mb3ev_after5GrpId[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(mb3ev_after5GrpId[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void MB3Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees) {
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
    MB3_BranchHelpStart();
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
    MB3_BranchHelpEnd();

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

void MB3Ev_KinokoMarkKill(s32 arg0) {
    {
        omObjData *obj = mb3ev_kinokoMarkObj[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            mb3ev_kinokoMarkObj[arg0] = NULL;
        }
    }

    {
        Object *model = mb3ev_kinokoMarkMdl[arg0];

        if (model != NULL) {
            MBModelKill(model);
            mb3ev_kinokoMarkMdl[arg0] = NULL;
        }
    }
}

void MB3Ev_KinokoMarkObjKillAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = mb3ev_kinokoMarkObj[i];

        if (obj != NULL) {
            omDelObj(obj);
            mb3ev_kinokoMarkObj[i] = NULL;
        }
    }
}

void MB3Ev_KinokoMarkObjMain(omObjData *obj) {
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
        Object *effectObj = mb3ev_kinokoMarkMdl[playerIdx];

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

void MB3Ev_KinokoMarkCreate(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (mb3ev_kinokoMarkMdl[playerNo] == NULL) {
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
        mb3ev_kinokoMarkMdl[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        MBModelDispFlagSet(mb3ev_kinokoMarkMdl[playerNo]);
    }
}

void MB3Ev_KinokoMarkObjCreate(s32 arg) {
    mb3ev_kinokoMarkObj[arg] = omAddObj(0x3FFF, 0, 0, -1, MB3Ev_KinokoMarkObjMain);
    mb3ev_kinokoMarkObj[arg]->work[0] = arg;
    mb3ev_kinokoMarkObj[arg]->work[1] = 0;
    mb3ev_kinokoMarkObj[arg]->work[2] = 0;
    mb3ev_kinokoMarkObj[arg]->rot.x = (f32)MBRand(360.0f);
    mb3ev_kinokoMarkObj[arg]->trans.x = 0;
}

void MB3Ev_KinokoMarkCreateAll(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        mb3ev_kinokoMarkObj[i] = NULL;
        mb3ev_kinokoMarkMdl[i] = NULL;
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
            MB3Ev_KinokoMarkCreate(i, idx);
            MB3Ev_KinokoMarkObjCreate(i);
        }
    }
    MBExitHookSet(MB3Ev_KinokoMarkObjKillAll);
}

void MB3Ev_NKinokoTurnStart(void) {
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
            if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB3Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB3Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void MB3Ev_ItemKoopaNKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        MBSaiKill(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB3Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB3Ev_KinokoVibrateProc(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

void MB3Ev_ItemNKinoko(void) {
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
    choice = MB3Ev_YesNoChoiceGet(2, mb3_comNKinokoTarget);
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

    MB3Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    MB3Ev_KinokoMarkCreate(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    MB3Ev_KinokoMarkObjCreate(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(MB3Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        MB3Ev_KinokoMarkKill(loc->current_player_index);
        MBSaiKill(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void MB3Ev_RKinokoTurnStart(void) {
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
            if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB3Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB3Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void MB3Ev_ItemKoopaRKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        MBSaiKill(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (mb3ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB3Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB3Ev_ItemRKinoko(void) {
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
    choice = MB3Ev_YesNoChoiceGet(2, mb3_comRKinokoTarget);
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

    MB3Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    MB3Ev_KinokoMarkCreate(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb3ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    MB3Ev_KinokoMarkObjCreate(targetPlayer);
    omAddPrcObj(MB3Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
        MB3Ev_RKinokoTurnStart();
    }
}

void MB3Ev_ItemRobBox(void) {
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

    MB3Ev_ItemUseFadeOut();
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
    targetPlayer = MB3_ComItemTargetChoice(choices, 0);
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
                       mb3ev_robBoxItemStartPosTbl[system->current_player_index].x,
                       mb3ev_robBoxItemStartPosTbl[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB3Ev_ItemMoveCreate(-1,
                                     mb3ev_robBoxItemStartPosTbl[system->current_player_index].x,
                                     mb3ev_robBoxItemStartPosTbl[system->current_player_index].y,
                                     mb3ev_robBoxItemEndPosTbl[system->current_player_index].x,
                                     mb3ev_robBoxItemEndPosTbl[system->current_player_index].y, 5));
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
    MB3Ev_ItemCursorReturn();
}

void MB3Ev_ActionTimeSpr(void) {
    s32 anims[4];
    s32 playerAnims[4];
    s32 grps[4];
    s32 i;
    s32 j;
    void *data;
    s32 bgAnim;
    s32 boxAnim;
    s32 grp;
    Process *process;
    s32 g;
    s32 count;
    s32 flag;
    s32 fading;
    s32 tpLvl;
    f32 angle;
    f32 speed;
    Unk3 *helpWin;

    process = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    bgAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    anims[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    anims[1] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    anims[2] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    anims[3] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    boxAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        playerAnims[i] = HuSprAnimRead(data);
        DataClose(data);
    }

    grp = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(grp, 0, bgAnim, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPriSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, 160, 90);

    angle = 0.0f;
    speed = 30.0f;
    count = 0;
    flag = 0;
    while (TRUE) {
        if (angle >= 90.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(grp, 0, 2);
        } else {
            HuSprAttrReset(grp, 0, 2);
        }
        HuSprScaleSet(grp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprAttrReset(grp, 0, 2);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    helpWin = MBHelpWinCreate(0x14, 0xA0, 1);

    for (i = 0; i < 4; i++) {
        grps[i] = HuSprGrpCreate(6, 5);
        g = grps[i];
        HuSprGrpMemberSet(g, 0, boxAnim, 0);
        HuSprAnimModeSet(g, 0, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(g, 0, 0xFFFF);
        if (mb3ev_sandPitJumpStateTbl[i] != 0) {
            HuSprAttrSet(g, 0, 8);
        } else {
            HuSprDispOff(g, 0);
        }
        HuSprPriSet(g, 0, 0x1000);
        HuSprParentSet(g, 0, -1);
        HuSprGrpMemberSet(g, 1, playerAnims[i], 0);
        HuSprAnimModeSet(g, 1, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(g, 1, 0xFFFF);
        if (mb3ev_sandPitJumpStateTbl[i] != 0) {
            HuSprAttrSet(g, 1, 8);
        } else {
            HuSprDispOff(g, 1);
        }
        HuSprPriSet(g, 1, 0x1000);
        HuSprPosSet(g, 1, 0, -9);
        HuSprParentSet(g, 1, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(g, j + 2, anims[j], 0);
            HuSprAnimModeSet(g, j + 2, HUSPR_ANIM_MODE_BANK);
            HuSprAttrReset(g, j + 2, 0xFFFF);
            if (mb3ev_sandPitJumpStateTbl[i] == j + 1) {
                HuSprAttrSet(g, j + 2, 8);
            } else {
                HuSprDispOff(g, j + 2);
            }
            HuSprPriSet(g, j + 2, 0x1000);
            HuSprPosSet(g, j + 2, 0, 9);
            HuSprParentSet(g, j + 2, 0);
        }
        HuSprPosSet(g, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);

    angle = 90.0f;
    count = 0;
    fading = 0;
    flag = 0;
    tpLvl = 255;
    while (TRUE) {
        if (angle >= 360.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (!fading && count != 0 && angle >= 90.0f && angle < 180.0f) {
            fading = 1;
        }
        if (fading) {
            tpLvl -= 21;
            if (tpLvl <= 0) {
                tpLvl = 0;
            }
        }
        HuSprTPLvlSet(grp, 0, tpLvl);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }
    HuSprScaleSet(grp, 0, 1.0f, 0.0f);
    HuSprGrpKill(grp);
    HuSprAnimKill(bgAnim);
    process->user_data = (void *)1;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            switch (mb3ev_sandPitJumpStateTbl[i]) {
                case 0:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOff(grps[i], j);
                    }
                    break;
                case 1:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grps[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grps[i], j + 2);
                    }
                    HuSprDispOn(grps[i], 2);
                    break;
                case 2:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grps[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grps[i], j + 2);
                    }
                    HuSprDispOn(grps[i], 3);
                    break;
                case 3:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grps[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grps[i], j + 2);
                    }
                    HuSprDispOn(grps[i], 4);
                    break;
                case 4:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grps[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grps[i], j + 2);
                    }
                    HuSprDispOn(grps[i], 5);
                    break;
                default:
                    goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(helpWin);
    HuSprAnimKill(boxAnim);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(anims[i]);
        HuSprAnimKill(playerAnims[i]);
        HuSprGrpKill(grps[i]);
    }
    omDelPrcObj(NULL);
}

void MB3Ev_Quicksand1ScrollObjMain(omObjData *obj) {
    Hu3DModelObjTexScroll(mb3ev_quicksandMdl->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "R3-cyl4", 0);
    obj->trans.x += 1.0f;

    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void MB3Ev_Quicksand2ScrollObjMain(omObjData *obj) {
    Hu3DModelObjTexScroll(mb3ev_quicksandMdl->omObj1->model[0], 0, obj->trans.x, 0x40, 0x40, "R3-cyl5_2", 0);
    obj->trans.x += 1.0f;

    if (obj->trans.x >= 64.0f) {
        obj->trans.x -= 64.0f;
    }
    if (obj->trans.y >= 64.0f) {
        obj->trans.y -= 64.0f;
    }
    if (obj->trans.x <= -64.0f) {
        obj->trans.x += 64.0f;
    }
    if (obj->trans.y <= -64.0f) {
        obj->trans.y += 64.0f;
    }
}

void MB3_SandPitCreateProc(void) {
    Object *obj;

    obj = mb3_sandPit0Mdl = MBModelCreate(0x4A, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x85)->coords);
    obj = mb3_sandPit1Mdl = MBModelCreate(0x4B, NULL);
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x87)->coords);
    while (1) {
        HuPrcVSleep();
    }
}

void MB3Ev_SandPitShakeProc(void) {
    Object *obj;
    omObjData *model;
    f32 angle;
    f32 scale;
    s32 count;

    if (HuPrcCurrentGet()->user_data == NULL) {
        obj = mb3_sandPit0Mdl;
    } else {
        obj = mb3_sandPit1Mdl;
    }

    angle = 0.0f;
    scale = 1.0f;
    while (angle < 90.0f) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        scale = sindf(angle) * 0.3f + 1.0f;
        HuPrcVSleep();
        angle += 22.5f;
    }

    count = 0;
    model = obj->omObj1;
    model->rot.z = 0.0f;
    angle = model->rot.z;
    scale = 5.0f;
    while (count < 4) {
        obj->omObj1->rot.z = sindf(angle) * scale;
        if (angle > 360.0f) {
            count++;
            angle -= 360.0f;
            scale -= 1.0f;
        }
        HuPrcVSleep();
        angle += 45.0f;
    }
    obj->omObj1->rot.z = 0.0f;
    omDelPrcObj(NULL);
}

void MB3Ev_SandPitJump(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *obj = player->player_obj;
    Vec dir;
    Vec pos;
    s32 comMissA;
    s32 comMissB;
    SpaceData *space;
    UnkEA790Struct *win;
    UnkVibrateProcess *vibrate;
    Process *process;
    u32 *motion;
    s32 state;
    s32 ring;
    s32 count;
    s32 choice;
    s32 sel;
    s32 i;
    s32 j;

    mbItemBtnF = 0;
    MBStatusHideAll();
    // Empty loops split the basic block so these GwSystem reads are not
    // rewritten relative to `system`. TODO: find the original construct.
    do {
    } while (0);
    MBSaiNumKill(GwSystem.current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    comMissA = MBComTreeExec(mb3ev_sandPitMissComTree0);
    comMissB = MBComTreeExec(mb3ev_sandPitMissComTree1);
    MBBackThreadPriLowSet();
    do {
    } while (0);
    MBPlayerRotMasuStart(GwSystem.current_player_index, 10, 0x85);
    MBPlayerMotionSet(-1, 0, 2);
    space = MBMasuGet(0x85);
    HuVecCopy3F(&pos, &obj->coords);
    HuVecSubtract(&dir, &space->coords, &obj->coords);
    MBVecNormalize(&dir);
    pos.x -= dir.x * 20.0f;
    pos.z -= dir.z * 20.0f;
    process = MBVecSpeedMove2Create(&obj->coords, &pos, &obj->coords, 2.0f);
    HuPrcChildLink(HuPrcCurrentGet(), process);
    HuPrcChildWatch();
    MBPlayerMotionSet(-1, -1, 2);
    for (i = 0; i < 4; i++) {
        mb3ev_sandPitJumpStateTbl[i] = 0;
    }
    mb3ev_actionTimeSprProc = omAddPrcObj(MB3Ev_ActionTimeSpr, 0x4800, 0, 0);
    while (mb3ev_actionTimeSprProc->user_data == NULL) {
        HuPrcVSleep();
    }

    mb3ev_sandPitJumpStateTbl[system->current_player_index] = 1;
    MBPlayerMotionSet(-1, 1, 2);
    MBVecDirGet(&obj->coords, &MBMasuGet(0x73)->coords, &obj->rot);
    state = 0;
    ring = 0;
    while (TRUE) {
        obj->coords.x += obj->rot.x * 2.0f;
        obj->coords.z += obj->rot.z * 2.0f;
        if (HuVecDistance(&obj->coords, &mb3_sandPit0Mdl->coords) < 44.0f && state != 2) {
            mb3ev_sandPitJumpStateTbl[system->current_player_index] = 2;
        }
        if (HuVecDistance(&obj->coords, &mb3_sandPit0Mdl->coords) < 40.0f) {
            if (HuVecDistance(&obj->coords, &mb3_sandPit0Mdl->coords) < 20.0f) {
                break;
            }
            if ((ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) && state != 2) {
                state = 1;
                break;
            }
            if (MBPlayerComCheck(system->current_player_index) && comMissA == 0) {
                state = 1;
                break;
            }
        } else if (ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) {
            state = 2;
            mb3ev_sandPitJumpStateTbl[system->current_player_index] = 4;
        }
        HuPrcVSleep();
    }

    if (state == 1) {
        PlayerFXPlay(0x3A, system->current_player_index);
        PlayerFXPlay(0x274, system->current_player_index);
        mb3ev_sandPitJumpStateTbl[system->current_player_index] = 3;
        MBPlayerMotionSet(-1, 2, 0);
        MBModelJumpSet(obj, 7.0f, -0.5f);
        for (i = 0; MBModelJumpCheck(obj); i++) {
            obj->coords.x += obj->rot.x * 2.0f;
            obj->coords.z += obj->rot.z * 2.0f;
            if (i > 20) {
                mb3ev_sandPitJumpStateTbl[system->current_player_index] = 1;
            }
            HuPrcVSleep();
        }
        PlayerFXPlay(0x31, system->current_player_index);
        MBPlayerMotionSet(-1, 1, 2);

        state = 0;
        ring = 1;
        while (TRUE) {
            obj->coords.x += obj->rot.x * 2.0f;
            obj->coords.z += obj->rot.z * 2.0f;
            if (HuVecDistance(&obj->coords, &mb3_sandPit1Mdl->coords) < 44.0f) {
                mb3ev_sandPitJumpStateTbl[system->current_player_index] = 2;
            }
            if (HuVecDistance(&obj->coords, &mb3_sandPit1Mdl->coords) < 40.0f) {
                if (HuVecDistance(&obj->coords, &mb3_sandPit1Mdl->coords) < 20.0f) {
                    break;
                }
                if (ContBtnDown[GwPlayer[system->current_player_index].pad] & A_BUTTON) {
                    state = 1;
                    break;
                }
                if (MBPlayerComCheck(system->current_player_index) && comMissB == 0) {
                    state = 1;
                    break;
                }
            }
            HuPrcVSleep();
        }

        if (state != 0) {
            PlayerFXPlay(0x3A, system->current_player_index);
            PlayerFXPlay(0x274, system->current_player_index);
            mb3ev_sandPitJumpStateTbl[system->current_player_index] = 3;
            MBPlayerMotionSet(-1, 2, 0);
            MBModelJumpSet(obj, 7.0f, -0.5f);
            while (MBModelJumpCheck(obj)) {
                obj->coords.x += obj->rot.x * 2.0f;
                obj->coords.z += obj->rot.z * 2.0f;
                HuPrcVSleep();
            }
            PlayerFXPlay(0x31, system->current_player_index);
            MBPlayerMotionSet(-1, 1, 2);
            HuVecCopy3F(&pos, &MBMasuGet(0x73)->coords);
            HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&obj->coords, &pos, &obj->coords, 2.0f));
            HuPrcChildWatch();
            MBPlayerMotionSet(-1, -1, 2);
            HuPrcSleep(10);
            mb3ev_sandPitJumpStateTbl[0] = -1;
            MBStatusShowAll();
            MBSaiNumShow(system->current_player_index);
            HuPrcSleep(10);
            mbItemBtnF = 1;
            player->clink = 6;
            player->cidx = 4;
            player->nlink = 6;
            player->nidx = 5;
            player->blink = 6;
            player->bidx = 3;
            if (player->rev & 0x80) {
                MB3_BranchHelpStart();
                win = MBBranchArrowLinkCreate(system->current_player_index, mb3ev_sandPitRevMasu);
                MBBranchSelStart(win, system->current_player_index, 0);
                if (MBPlayerComCheck(-1)) {
                    count = MBComTreeExec(mb3ev_sandPitRevComTree);
                    for (i = 0; i < count; i++) {
                        MBBranchSelMesSend(win, -2);
                    }
                    MBBranchSelMesSend(win, -4);
                }
                sel = MBBranchSelWait(win);
                MBBranchArrowGrpKill(win);
                MB3_BranchHelpEnd();
                if (sel == 0) {
                    MBMoveNextMasuSet(-1, 6, 3);
                    player->rev |= 1;
                } else {
                    MBMoveNextMasuSet(-1, 6, 5);
                    player->rev &= ~1;
                }
            }
            MBBackThreadPriHighSet();
            omDelPrcObj(NULL);
            return;
        }
    }

    vibrate = MBPlayerVibrateObjCreate(-1, 2, 5);
    HuAudFXPlay(0x19A);
    PlayerFXPlay(0x286, system->current_player_index);
    mb3ev_sandPitJumpStateTbl[system->current_player_index] = 4;
    MBPlayerMotionLoad(system->current_player_index, 5, 0x1A);
    MBPlayerMotionSet(-1, 5, 2);
    if (ring == 0) {
        space = MBMasuGet(0x71);
    } else {
        space = MBMasuGet(0x19);
    }
    process = omAddPrcObj(MB3Ev_SandPitShakeProc, 0x4800, 0, 0);
    process->user_data = (void *)ring;
    MBVecDirGet(&obj->coords, &space->coords, &dir);
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            WipeCreateOut(11, 16);
        }
        MBModelJumpSet(obj, 7.0f, -0.5f);
        while (MBModelJumpCheck(obj)) {
            obj->coords.x += dir.x * 2.0f;
            obj->coords.z += dir.z * 2.0f;
            HuPrcVSleep();
        }
        HuAudFXPlay(0x19B);
    }
    while (WipeStatGet()) {
        HuPrcVSleep();
    }

    if (ring == 0) {
        space = MBMasuGet(0x6F);
    } else {
        space = MBMasuGet(0x19);
    }
    HuVecCopy3F(&dir, &space->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&dir);
    MBBackThreadPriHighSet();
    HuPrcSleep(5);
    HuVecCopyXYZ(&mb3_sandPit0Mdl->scale, 1.0f, 1.0f, 1.0f);
    HuVecCopyXYZ(&mb3_sandPit1Mdl->scale, 1.0f, 1.0f, 1.0f);
    WipeCreateIn(11, 16);
    if (ring == 0) {
        HuVecCopyXYZ(&obj->coords, 113.0f, 0.0f, -30.0f);
    } else {
        HuVecCopyXYZ(&obj->coords, -153.0f, 0.0f, -5.0f);
    }
    if (ring == 0) {
        player->clink = 11;
        player->cidx = 11;
        player->nlink = 11;
        player->nidx = 11;
        player->blink = 11;
        player->bidx = 10;
    } else {
        player->clink = 5;
        player->cidx = 10;
        player->nlink = 5;
        player->nidx = 11;
        player->blink = 5;
        player->bidx = 9;
    }
    for (i = 0; i < 4; i++) {
        if (i != system->current_player_index) {
            MBPlayerPosFixSet(i, 20);
        }
    }
    MBVecDirGet(&obj->coords, &space->coords, &pos);
    for (i = 0; i < 2; i++) {
        MBModelJumpSet(obj, 7.0f, -0.5f);
        while (MBModelJumpCheck(obj)) {
            obj->coords.x += pos.x * 2.0f;
            obj->coords.z += pos.z * 2.0f;
            HuPrcVSleep();
        }
        HuAudFXPlay(0x19B);
    }
    while (WipeStatGet()) {
        HuPrcVSleep();
    }

    MBCameraFocusModeSet(1);
    MBPlayerVibrateObjKill(vibrate);
    mb3ev_sandPitJumpStateTbl[0] = -1;
    MBPlayerMotionLoad(system->current_player_index, 6, 0xF);
    MBPlayerMotionSet(-1, 6, 0);
    MBPlayerMotionWait(-1);
    MBPlayerMotionSet(-1, -1, 2);
    motion = mbPlayerMotTbl[0];
    for (j = 6; j != 0; j--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    motion = mbPlayerMotTbl[0];
    for (j = 7; j != 0; j--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 6, ((u16 *)motion)[1]);
    MBStatusShowAll();
    MBDlgResultWinExec(0x700);
    MBSaiNumShow(system->current_player_index);
    HuPrcSleep(10);
    mbItemBtnF = 1;
    if (ring == 0) {
        if (player->rev & 0x80) {
            MB3_BranchHelpStart();
            win = MBBranchArrowLinkCreate(system->current_player_index, mb3ev_sandPitFall0Masu);
            MBBranchSelStart(win, system->current_player_index, 0);
            if (MBPlayerComCheck(-1)) {
                switch (system->star_spawn_indices[system->current_star_spawn]) {
                    case 6:
                        if (GwPlayer[system->current_player_index].coin < 20) {
                            count = 1;
                        } else {
                            count = 2;
                        }
                        if (GwPlayer[system->current_player_index].coin >= 20 && mbWalkNum >= 2) {
                            count = 2;
                        }
                        break;
                    case 7:
                        if (GwPlayer[system->current_player_index].coin < 20) {
                            count = 1;
                        } else {
                            count = 2;
                        }
                        if (GwPlayer[system->current_player_index].coin >= 20 && mbWalkNum >= 5) {
                            count = 0;
                        }
                        break;
                    default:
                        count = 2;
                        if (GwPlayer[system->current_player_index].coin >= 5 && mbWalkNum >= 4) {
                            count = 1;
                        }
                        break;
                }
                for (i = 0; i < count; i++) {
                    MBBranchSelMesSend(win, -2);
                }
                MBBranchSelMesSend(win, -4);
            }
            sel = MBBranchSelWait(win);
            MBBranchArrowGrpKill(win);
            MB3_BranchHelpEnd();
            switch (sel) {
                case 0:
                    MBMoveNextMasuSet(-1, 1, 0);
                    player->rev &= ~1;
                    break;
                case 1:
                    MBMoveNextMasuSet(-1, 11, 10);
                    player->rev |= 1;
                    break;
                default:
                    MBMoveNextMasuSet(-1, 12, 0);
                    player->rev &= ~1;
                    break;
            }
        } else {
            HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB3Ev_Branch8, 0x4800, 0, 0));
            HuPrcChildWatch();
        }
    } else if (player->rev & 0x80) {
        MB3_BranchHelpStart();
        win = MBBranchArrowLinkCreate(system->current_player_index, mb3ev_sandPitFall1Masu);
        MBBranchSelStart(win, system->current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            switch (system->star_spawn_indices[system->current_star_spawn]) {
                case 2:
                    choice = 0;
                    break;
                case 1:
                    choice = 2;
                    break;
                default:
                    choice = 1;
                    if (GwPlayer[system->current_player_index].coin < 20) {
                        choice = mbWalkNum == 3;
                    }
                    break;
            }
            for (i = 0; i < choice; i++) {
                MBBranchSelMesSend(win, -2);
            }
            MBBranchSelMesSend(win, -4);
        }
        sel = MBBranchSelWait(win);
        MBBranchArrowGrpKill(win);
        MB3_BranchHelpEnd();
        switch (sel) {
            case 0:
                MBMoveNextMasuSet(-1, 5, 9);
                player->rev |= 1;
                break;
            case 1:
                MBMoveNextMasuSet(-1, 5, 11);
                player->rev &= ~1;
                break;
            default:
                MBMoveNextMasuSet(-1, 6, 9);
                player->rev |= 1;
                break;
        }
    }
    omDelPrcObj(NULL);
}

void MB3Ev_QuicksandSinkProc(void) {
    s32 i = 0;
    GW_PLAYER *player = MBPlayerGet((s32)HuPrcCurrentGet()->user_data);
    f32 velocityStep = 5.0f / 12.0f;

    do {
        player->player_obj->velocity.x -= velocityStep;
        HuPrcVSleep();
        i++;
    } while (i < 0x3C);

    omDelPrcObj(NULL);
}

void MB3Ev_QuicksandExitProc(void) {
    HatenaPlayerWork *work = HuPrcCurrentGet()->user_data;
    GW_SYSTEM *sys = &GwSystem;
    s32 playerNo = work->playerNo;
    GW_PLAYER *player = MBPlayerGet(playerNo);
    SpaceData *dest;
    Object *model;

    if (mb3ev_quicksandExitMasu == MBMasuGet(0x7F)) {
        dest = MBMasuGet(0x24);
    } else {
        dest = MBMasuGet(0x4E);
    }
    HuAudPlayerFXPlay(0x199, sys->current_player_index);
    player->player_obj->velocity.x = 0.0f;
    HuVecCopy3F(&player->player_obj->coords, &mb3ev_quicksandExitMasu->coords);
    model = MBModelCreate(0x36, NULL);
    HuVecCopy3F(&model->coords, &mb3ev_quicksandExitMasu->coords);
    MBMotionSet(model, -1, 0);
    MBModelJumpSet(player->player_obj, 15.0f, -0.1f);
    HuPrcSleep(10);
    player->player_obj->velocity.x = 100.0f;
    HuVecCopy3F(&player->player_obj->coords, &dest->coords);
    player->player_obj->coords.x += mb3ev_quicksandExitOfsTbl[mb3ev_quicksandExitNum + work->order].x;
    player->player_obj->coords.z += mb3ev_quicksandExitOfsTbl[mb3ev_quicksandExitNum + work->order].y;
    MBModelJumpSet(player->player_obj, 0.0f, -1.0f);
    MBModelJumpWait(player->player_obj);
    MBPlayerVibrate(playerNo, 1);
    MBModelKill(model);
    if (mb3ev_quicksandExitMasu == MBMasuGet(0x7F)) {
        player->clink = 5;
        player->cidx = 0x14;
        player->nlink = 5;
        player->nidx = 0x15;
        player->blink = 5;
        player->bidx = 0x13;
    } else {
        player->clink = 2;
        player->cidx = 2;
        player->nlink = 2;
        player->nidx = 3;
        player->blink = 2;
        player->bidx = 1;
    }
    omDelPrcObj(NULL);
}

void MB3Ev_QuicksandStruggleProc(void) {
    s32 playerNo;
    s32 isSecond = FALSE;
    GW_SYSTEM *sys;
    GW_PLAYER *player;
    SpaceData *space;
    Vec dir;
    f32 speed;

    playerNo = (s32)HuPrcCurrentGet()->user_data;
    sys = &GwSystem;
    if (playerNo >= 4) {
        isSecond = TRUE;
        playerNo -= 4;
    }
    player = MBPlayerGet(playerNo);
    if (!isSecond) {
        space = MBMasuGet(0x80);
    } else {
        space = MBMasuGet(0x7F);
    }
    MBPlayerMotionSet(-1, 2, 0);
    MBModelJumpSet(player->player_obj, 15.0f, -2.5f);
    MBModelJumpWait(player->player_obj);
    HuVecSubtract(&dir, &player->player_obj->coords, &space->coords);
    MBVecNormalize(&dir);
    HuVecCopy3F(&player->player_obj->rot, &dir);
    PlayerFXPlay(0x286, playerNo);
    if (playerNo == sys->current_player_index) {
        MBPlayerMotionSet(-1, 1, 2);
        MBPlayerSpeedSet(sys->current_player_index, 1.5f);
    } else {
        MBMotionSet(player->player_obj, 1, 2);
        Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.5f);
    }

    for (speed = 1.0f; speed > 0.0f; speed -= 0.1f) {
        player->player_obj->coords.x += speed * dir.x;
        player->player_obj->coords.z += speed * dir.z;
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

#ifdef NON_MATCHING
// Matches except for the if/else right after the hatena space search loop: the
// target tests *hatena != -1 (-> 0x47 branch), reloads *hatena, and tests it
// again (== -1 -> 0x48 branch, no extra `li -1`); we emit a single test.
// RTL analysis (-O1): the second test survives only if, at CSE time, a label
// separates it from the first test (CSE blocks end at labels); the pre-CSE
// thread_jumps pass creates exactly such a label when it threads the loop
// entry test through the first test. The label must then vanish before the
// final jump pass (post-loop thread_jumps redirecting the entry test on to
// the 0x48 branch, which needs the second test to be RTL-identical to the
// entry test by then), so that the final jump pass deletes the second test's
// redundant `li -1` (find_equiv_reg). So the source must have two tests in
// `if (T1 || T2)` shape, T1 == entry test, and T2 differing before CSE but
// identical after CSE. Closest forms (both meaningless, not acceptable):
//     if (mb3ev_quicksand1HatenaMasuTbl[hatena - mb3ev_quicksand1HatenaMasuTbl] != -1 || *hatena != -1)
//         -> 220: v0/v1 swapped in 2nd test, entry branch lands on 1st test
//     if (*hatena != -1 || mb3ev_quicksand1HatenaMasuTbl[hatena - mb3ev_quicksand1HatenaMasuTbl] != -1)
//         -> 2325: right threading, but extra `li v0,-1` and `li a0,0x47`
// Identical-operand forms (||, &&, nested else-if, goto, casts, hatena[0],
// *(hatena + 0), (u16)/+1 variants, a copy pointer in T2) are folded by the
// tree folder, threaded pre-CSE or CSE'd into one test. Also tried: for/while/
// do-while/continue/goto/compound-condition search loops, an if-wrapped
// do-while, index-based loops (break strength reduction), switch, ternaries,
// flag variables.
void MB3Ev_Quicksand(void) {
    Vec pos;
    UnkVibrateProcess *vibrate[4];
    s32 anim;
    s16 *hatena;
    s16 *masuList;
    GW_PLAYER *player;
    s32 i;
    SpaceData *space;
    SpaceData *destSpace;
    Object *eye;
    omObjData *scroll;
    Process *process;
    HatenaPlayerWork *work;
    void *data;
    s32 masuId;
    s32 order;
    f32 scale;

    mbItemBtnF = 0;
    mbTauntOffF = 1;
    MBStatusHideAll();
    hatena = mb3ev_quicksand1HatenaMasuTbl;
    player = MBPlayerGet(-1);
    for (; *hatena != -1; hatena++) {
        if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *hatena) {
            break;
        }
    }
    if (*hatena != -1) {
        mb3ev_quicksandMdl = MBModelCreate(0x47, NULL);
        space = MBMasuGet(0x80);
        masuList = mb3ev_quicksand1MasuTbl;
    } else {
        mb3ev_quicksandMdl = MBModelCreate(0x48, NULL);
        space = MBMasuGet(0x7F);
        masuList = mb3ev_quicksand2MasuTbl;
    }
    Hu3DModelVtxBufMake(mb3ev_quicksandMdl->omObj1->model[0]);
    HuVecCopy3F(&mb3ev_quicksandMdl->coords, &space->coords);
    HuVecCopyXYZ(&mb3ev_quicksandMdl->scale, 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 10));
    HuPrcChildWatch();
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);
    HuPrcSleep(10);

    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                vibrate[i] = MBPlayerVibrateObjCreate(i, 1, 5);
            }
        }
    }

    HuAudFXPlay(0x198);
    if (*hatena != -1) {
        scroll = omAddObj(0x1000, 0, 0, -1, MB3Ev_Quicksand1ScrollObjMain);
    } else {
        scroll = omAddObj(0x1000, 0, 0, -1, MB3Ev_Quicksand2ScrollObjMain);
    }
    scroll->trans.x = 0.0f;
    for (scale = scroll->trans.x; scale < 1.0f; scale += 0.1f) {
        HuVecCopyXYZ(&mb3ev_quicksandMdl->scale, scale, scale, scale);
        HuPrcVSleep();
    }

    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                if (*hatena != -1) {
                    MBPlayerRotMasuStart(i, 10, 0x80);
                } else {
                    MBPlayerRotMasuStart(i, 10, 0x7F);
                }
            }
        }
    }

    if (*hatena != -1) {
        masuList = mb3ev_quicksand1MasuTbl;
    } else {
        masuList = mb3ev_quicksand2MasuTbl;
    }
    HuPrcSleep(10);
    eye = MBModelCreate(0x49, NULL);
    HuVecCopy3F(&eye->coords, &space->coords);
    data = DataRead(0x130205);
    anim = (s16)Hu3DAnimCreate(Hu3DData[eye->omObj1->model[0]].hmf, data, 0, "f_heleye_I8");
    Hu3DAnimAttrSet(anim, 0, 0);
    DataClose(data);
    Hu3DModelAttrSet(eye->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(eye->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(eye->omObj1->model[0]);
    HuPrcSleep(12);

    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                process = omAddPrcObj(MB3Ev_QuicksandStruggleProc, 0x4800, 0, 0);
                if (*hatena != -1) {
                    process->user_data = (void *)i;
                } else {
                    process->user_data = (void *)(i + 4);
                }
                HuPrcChildLink(HuPrcCurrentGet(), process);
            }
        }
    }
    HuPrcChildWatch();

    if (*hatena != -1) {
        masuList = mb3ev_quicksand1MasuTbl;
    } else {
        masuList = mb3ev_quicksand2MasuTbl;
    }
    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords,
                                                                        &space->coords,
                                                                        &player->player_obj->coords, 60));
                process = omAddPrcObj(MB3Ev_QuicksandSinkProc, 0x4800, 0, 0);
                process->user_data = (void *)i;
            }
        }
    }
    HuPrcChildWatch();

    if (*hatena != -1) {
        masuList = mb3ev_quicksand1MasuTbl;
    } else {
        masuList = mb3ev_quicksand2MasuTbl;
    }
    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                MBPlayerVibrateObjKill(vibrate[i]);
            }
        }
    }

    WipeCreateOut(0xB, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    if (*hatena != -1) {
        mb3ev_quicksandExitMasu = space = MBMasuGet(0x7F);
        masuList = mb3ev_quicksand1MasuTbl;
    } else {
        mb3ev_quicksandExitMasu = space = MBMasuGet(0x80);
        masuList = mb3ev_quicksand2MasuTbl;
    }
    HuVecCopy3F(&pos, &space->coords);
    MBCameraFocusModeSet(2);
    MBCameraFocusStaticPosSet(&pos);
    omDelObj(scroll);
    Hu3DAnimKill(anim);
    MBModelKill(eye);
    MBModelKill(mb3ev_quicksandMdl);

    if (*hatena != -1) {
        masuId = 0x24;
        destSpace = MBMasuGet(0x24);
    } else {
        masuId = 0x4E;
        destSpace = MBMasuGet(0x4E);
    }
    mb3ev_quicksandExitNum = 0;
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == masuId) {
            HuVecCopy3F(&player->player_obj->coords, &destSpace->coords);
            player->player_obj->coords.x += mb3ev_quicksandExitOfsTbl[mb3ev_quicksandExitNum].x;
            player->player_obj->coords.z += mb3ev_quicksandExitOfsTbl[mb3ev_quicksandExitNum].y;
            mb3ev_quicksandExitNum++;
        }
    }
    MBCameraZoomSet(1.1f);
    HuPrcSleep(5);
    WipeCreateIn(4, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    order = 0;
    for (; *masuList != -1; masuList++) {
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masuList) {
                HuVecCopyXYZ(&player->player_obj->rot, 0.0f, 0.0f, 1.0f);
                if (i == GwSystem.current_player_index) {
                    MBPlayerMotionSet(-1, -1, 2);
                } else {
                    MBMotionSet(player->player_obj, -1, 2);
                }
                process = omAddPrcObj(MB3Ev_QuicksandExitProc, 0x4800, 0, 0x40);
                work = HuMemMemoryAlloc(process->heap, sizeof(HatenaPlayerWork) * 4);
                process->user_data = work;
                work->playerNo = i;
                work->order = order;
                HuPrcChildLink(HuPrcCurrentGet(), process);
                order++;
                HuPrcSleep(10);
            }
        }
    }
    HuPrcChildWatch();
    MBStatusShowAll();

    if (MBKettouPlayerBitGet(0) != 0) {
        MBBackThreadPriLowSet();
        player = MBPlayerGet(-1);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&pos);
        HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&pos, &player->player_obj->coords, &pos, 2.0f));
        HuPrcChildWatch();
        MBBackThreadPriHighSet();
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&pos);
    }
    mbTauntOffF = 0;
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/party/boards/w03_spiny_desert/main", MB3Ev_Quicksand);
#endif

void MB3Ev_SandPitBranch(void) {
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    UnkEA790Struct *win;
    Process *prc;
    s32 count;
    s32 sel;
    s32 i;

    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    MB3_BranchHelpStart();
    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
        win = MBBranchArrowLinkCreate(sys->current_player_index, mb3ev_sandPitBranchFrom74Masu);
    } else {
        win = MBBranchArrowLinkCreate(sys->current_player_index, mb3ev_sandPitBranchMasu);
    }
    MBBranchSelStart(win, sys->current_player_index, 0);
    if (MBPlayerComCheck(-1)) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
            count = MBComTreeExec(mb3ev_sandPitBranchComTree0);
        } else {
            count = MBComTreeExec(mb3ev_sandPitBranchComTree1);
        }
        for (i = 0; i < count; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }
    sel = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB3_BranchHelpEnd();
    if (sel == 0) {
        prc = omAddPrcObj(MB3Ev_SandPitJump, 0x4800, 0, 0);
        HuPrcChildLink(HuPrcCurrentGet(), prc);
        HuPrcChildWatch();
    } else if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4A) {
        MBMoveNextMasuSet(-1, 9, 0xE);
    } else {
        MBMoveNextMasuSet(-1, 9, 0xC);
    }
    omDelPrcObj(NULL);
}

// entrypoint 4
void MB3Ev_OpStarMapView(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &mb3ev_opStarMapViewRect);
    MB3_ObjectSetup();
    MBStart(2);
    omAddPrcObj(MB3Ev_StarMapView, 0x1005, 0x1000, 0);
}

s32 MB3_ComNKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            MBComTreePlayerSet(i);
            if ((MBComTreeExec(mb3_itemNKinokoStarComTree) == 0) && (MBPlayerRankCalc(i) < bestRank)) {
                bestRank = MBPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}

s32 MB3_ComRKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(mb3_itemRKinokoStarComTree) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                MBComTreePlayerSet(i);
                if ((MBComTreeExec(mb3_itemRKinokoTargetComTree) == 0) && (MBPlayerRankCalc(i) < bestRank)) {
                    bestRank = MBPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}

s32 MB3_ComItemExcessCheck(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

s32 MB3_ComRobItemSafeCheck(s32 arg0, s32 arg1) {
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

s32 MB3_ComItemDecide(void) {
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
                if (MB3_ComItemExcessCheck() != 0) {
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
                if (MBRandCheck100(70) != 0 && MB3_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (MB3_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb3_itemSKinokoComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (MB3_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb3_itemKSuitComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(mb3_itemWarpBlockComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(mb3_itemNKinokoComTree) == 0) {
                    s32 target = MB3_ComNKinokoTargetGet();

                    mb3_comNKinokoTarget = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(mb3_itemRKinokoComTree) == 0) {
                    s32 target = MB3_ComRKinokoTargetGet();

                    mb3_comRKinokoTarget = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, mb3_comRobBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < mbItemComWeightTbl[it]) {
                                    best = mbItemComWeightTbl[it];
                                    mb3_comRobBoxTarget = i;
                                }
                            }
                        }
                    }
                }
                if (mb3_comRobBoxTarget == -1) {
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
                for (i = 0, mb3_comExchangeBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += mbItemComWeightTbl[it];
                            }
                        }
                        if (best < count) {
                            mb3_comExchangeBoxTarget = i;
                            best = count;
                        }
                    }
                }
                if (mb3_comExchangeBoxTarget == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (MB3_ComRobItemSafeCheck(0x32, 0xA) == 0) {
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
                if (MB3_ComRobItemSafeCheck(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(mb3_itemMajinLampComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && MB3_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(mb3_itemStarYokeComTree) != 0) {
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

s32 MB3_ComShopItemDecide(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = mb3_comShopItemOrderTbl[player->chr][i];

        found = MB3Ev_ShopItemIdxGet(val);
        if (found == -1) {
            continue;
        }
        if (mbItemPriceTbl[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(mb3_comShopItemRateTbl[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (MB3Ev_ShopItemIdxGet(0xE) == found) {
            return found + 1;
        }
        if (MB3Ev_ShopItemIdxGet(0xB) == found && mbItemPriceTbl[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (MB3Ev_ShopItemIdxGet(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(mb3_comShopKeyComTree[mb3ev_shopNo]) == 0 && GwPlayer[loc->current_player_index].coin >= mbItemPriceTbl[1]) {
        s32 route = MB3Ev_ShopItemIdxGet(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(mb3_comShopItemComTree[mb3ev_shopNo]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = mb3_comShopItemOrderTbl[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = MB3Ev_ShopItemIdxGet(val);
            if (found == -1) {
                continue;
            }
            if (mbItemPriceTbl[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(mb3_comShopItemRateTbl[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = MB3Ev_ShopItemIdxGet(0);
    if (found != -1) {
        return found + 1;
    }
    mb3_comShopCancelF = 1;
    return MB3Ev_ShopItemNumGet() + 2;
}

s32 MB3_ComShopEnterDecide(void) {
    if (mb3_comShopCancelF != 0) {
        mb3_comShopCancelF = 0;
        return 2;
    }
    return MBComTreeExec(mb3_comShopEnterComTree[mb3ev_shopNo]) + 1;
}
