#include "common_board.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/sprgrp.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/scroll.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/com.h"
#include "game/overlays/party/common/mapfull.h"
#include "game/overlays/party/common/window.h"
#include "game/object.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/ksuit.h"
#include "game/overlays/party/common/vec.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"

// Inlined Z rotation matrix build (same as HuMtxRotZF, but with the
// 1.0f diagonal written last).
#define MTX_ROTZ(mtx, angle)                                                                \
    {                                                                                       \
        sincosdf(angle, &(mtx)[0][1], &(mtx)[0][0]);                                        \
        (mtx)[1][0] = -(mtx)[0][1];                                                         \
        (mtx)[1][1] = (mtx)[0][0];                                                          \
        (mtx)[0][2] = (mtx)[0][3] = (mtx)[1][3] = (mtx)[1][2] = (mtx)[2][0] = (mtx)[2][1] = \
            (mtx)[2][3] = (mtx)[3][0] = (mtx)[3][1] = (mtx)[3][2] = 0.0f;                   \
        (mtx)[2][2] = (mtx)[3][3] = 1.0f;                                                   \
    }

void MB2Ev_StarGuideIn(void);
void MB2Ev_StarGuideJumpExec(UnkMBGuideData *guide);
void MB2Ev_StarGet(void);
void MB2_GateCloseProc(void);
void MB2Ev_TeresaCoin(void);
void MB2Ev_ActionTimeTitleProc(void);
void MB2_ObjectSetup(void);
s32 MB2Ev_YesNoChoiceGet(s32 arg0, s32 arg1);
void MB2_BranchHelpStart(void);
void MB2Ev_KinokoMarkObjCreate(s32 arg);
Process *MB2Ev_ItemMoveCreate(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY, s16 duration);
void MB2Ev_ItemUseFadeOut(void);
void MB2Ev_ItemCursorReturn(void);
s32 MB2_ComItemTargetChoice(u8 *arg0, s32 arg1);
s32 MB2_ComNKinokoTargetGet(void);
s32 MB2_ComRKinokoTargetGet(void);
void MB2_GateCreate(s16 arg0);
void MB2Ev_TereYokeSprayProc(void);
void MB2Ev_ShopMasu(void);
void MB2Ev_KoopaCardCoinProc(void);
void MB2Ev_ItemIconMove(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode);
void MB2Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3);
s32 MB2_ComShopItemDecide(void);
s32 MB2_ComShopEnterDecide(void);
void MB2Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees);
void MB2Ev_ItemLampSmokeObjMain(omObjData *arg0);
s32 MB2_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2);
void MB2Ev_Hatena(void);
void MB2Ev_Vacuum(void);
void MB2Ev_HatenaWarp(s16 masuId);
void MB2Ev_Branch6(void);
void MB2Ev_Branch7(void);
void MB2Ev_Branch8(void);
void MB2Ev_Branch9(void);
omObjData *MB2Ev_ItemLampSmokeCreate(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5);
void MB2Ev_After5ItemMove(s32 arg0, s32 arg1, f32 *arg2);
void MB2Ev_After5LineShow(void);
void MB2Ev_After5NumFade(omObjData *obj);
void MB2Ev_After5Effect(void);
void MB2Ev_VacuumEffObjMain(omObjData *obj);
void MB2Ev_VacuumEffSpeedSet(s16 model, f32 arg1, f32 arg2);
void MB2Ev_VacuumEffPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3);
void MB2Ev_VacuumEffAdd(s16 model);
void MB2Ev_VacuumEffUpdate(s16 model);
void MB2Ev_BankMasuBranch(void);
void MB2Ev_BankKoopaCardExec(void);
s32 MB2_ComShopItemChoice(u8 *arg0);
s32 MB2_ComShopEnterChoice(void);
void MB2Ev_ShopBagBounceProc(void);
void MB2Ev_TeresaWinCloseProc(void);
s32 MB2_ComTeresaTypeChoice(u8 *arg0);
s32 MB2_ComTeresaPlayerChoice(u8 *arg0);
void MB2Ev_TeresaMasuBranch(void);
void MB2Ev_TeresaFadeIn(Object *obj);
void MB2Ev_TeresaFadeOut(Object *obj);
s32 MB2Ev_TeresaStarSteal(s32 playerIndex);
s32 MB2Ev_TeresaSteal(s32 playerIndex);
void MB2Ev_TeresaCoinCreate(s32 arg);
void MBModelTurnCreate(Object *arg0, Vec *arg1, s32 arg2);
void MB2_GateOpen(s32 arg0, s32 arg1);
s32 MB2Ev_KeyManChoiceGet(s32 arg0);
void MB2Ev_StarNextPos(void);
void MB2Ev_StarMasuInit(void);
void MB2_StarGuideCreateAll(void);
void MB2_TeresaGuideCreateAll(void);
void MB2_BankCoinCreateAll(void);
void MB2_GateCreateAll(void);
void MB2_BankMapIconAddAll(void);
void MB2_ShopMapIconAddAll(void);
void MB2_VacuumRouletteCreate(void);
void MB2_ShortcutCreate(void);
void MB2_ShortcutMarkCreateAll(void);
void MB2Ev_Teresa(void);
void MB2Ev_ItemMajinLamp(void);
void MB2Ev_ItemMajinLampStar(void);
void MB2Ev_ItemWarpBlock(void);
void MB2Ev_ItemKinoko(void);
void MB2Ev_ItemShake(void);
void MB2Ev_ItemPhoneMove(void);
void MB2Ev_KSuitStart(void);
void MB2Ev_KSuitEnd(void);
void MB2Ev_ItemShopPhone(void);
void MB2Ev_ItemKoopaPhone(void);
void MB2Ev_ItemStarYoke(void);
void MB2Ev_ItemKeyManUse(void);
void MB2Ev_ItemNullUse(void);
void MB2Ev_ItemExchangeBox(void);
void MB2Ev_ItemGambleCoin(void);
void MB2Ev_ItemAfter5(void);
void MB2Ev_KinokoMarkCreateAll(void);
void MB2Ev_ItemKoopaNKinoko(void);
void MB2Ev_ItemNKinoko(void);
void MB2Ev_ItemKoopaRKinoko(void);
void MB2Ev_ItemRKinoko(void);
void MB2Ev_ItemRobBox(void);
s32 MB2_ComItemDecide(void);
void MB2Ev_TereYokeSparkProc(void);
s32 MB2_ComShortcutMarkCheck(void);
void MB2Ev_Branch1(void);
void MB2Ev_Branch2(void);
void MB2Ev_Branch3(void);
void MB2Ev_Branch4(void);
void MB2Ev_Branch5(void);
void MB2Ev_Branch6RKinoko(void);
void MB2Ev_Branch7RKinoko(void);
void MB2Ev_Branch8RKinoko(void);
void MB2Ev_Branch9RKinoko(void);
void MB2Ev_Branch10Check(void);
void MB2Ev_Merge1(void);
void MB2Ev_Merge2(void);
void MB2Ev_Merge3(void);
void MB2Ev_Merge4(void);
void MB2Ev_Merge5(void);
void MB2Ev_Merge6(void);
void MB2Ev_Merge7(void);
void MB2Ev_Merge8(void);
void MB2Ev_Merge9(void);
void MB2Ev_Merge10(void);
void MB2Ev_Merge11(void);
void MB2Ev_Merge12(void);
void MB2Ev_Merge13(void);
void MB2Ev_Merge14(void);
void MB2Ev_Merge15(void);
void MB2Ev_Merge16(void);
void MB2Ev_Merge17(void);
void MB2Ev_Merge18(void);
void MB2Ev_KeyManMasu(void);
void MB2Ev_StarMasu(void);
void MB2Ev_BankMasu(void);
void MB2Ev_Gate1Close(void);
void MB2Ev_Gate2Close(void);
void MB2Ev_NKinokoTurnStart(void);
void MB2Ev_RKinokoTurnStart(void);
void MB2Ev_Shortcut(void);

s16 mb2ev_starOrderTbl[] = { 0, 1, 2, 3, 5, 4, 6, 7 };

s16 mb2ev_starOrderGroupTbl[] = { 0, 0, 0, 0, 0, 1, 1, 1 };

s16 mb2ev_starFlag[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb2ev_starMasu[] = { 30, 40, 21, 7, 65, 92, 76, 86 };

s16 mb2ev_starGuideMasu[] = { 94, 95, 96, 97, 98, 99, 100, 101 };

s32 mb2ev_starGuideFaceTbl[] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };

s32 mb2ev_starGuideMesTbl[] = { 0x5E02, 0x5E03, 0x5E04, 0x5E05, 0x5E06, 0x5E07, 0x5E08 };

s32 mb2ev_starGetTeresaF = 0;

s16 mb2_masuBlockExtTbl[] = { -1, 0 };

s16 mb2_masuBlockTbl[] = {
    30, 40, 21, 7, 65, 92, 76, 86,
    -1, 0
};

s16 mb2_starGuideMapIconOfsTbl[][2] = {
    { 4, 0 },
    { -2, -2 },
    { 0, -4 },
    { 4, 0 },
    { 4, -2 },
    { -2, 2 },
    { -4, -4 },
    { 0, 0 }
};

s16 mb2_teresaGuideMapIconOfsTbl[][2] = {
    { 0, -2 },
    { 0, 0 }
};

s16 mb2_bankMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, -4 }
};

s16 mb2_shopMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 2, 0 }
};

s16 mb2_gateMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, 2 }
};

s16 mb2_gateDirMasuTbl[][2] = {
    { 133, 134 },
    { 135, 136 }
};

s16 mb2_starGuideMdlMasuTbl[] = { 94, 95, 96, 97, 98, 99, 100, 101 };

s16 mb2_starGuideFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb2_teresaGuideMasuTbl[] = { 102, 0 };

s16 mb2_bankCoinMasuTbl[] = { 111, 113 };

Vec mb2_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb2_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb2_gateMasuTbl[] = { 106, 107 };

s16 mb2_gateMdlTbl[] = { 38, 39, 40, 41, 42, 43 };

u32 mb2_gateMot1[] = { 1, 0x130163 };

u32 mb2_gateMot2[] = { 1, 0x130168 };

u32 mb2_gateMot3[] = { 1, 0x13016F };

u32 mb2_gateMot4[] = { 1, 0x130176 };

u32 mb2_gateMot5[] = { 1, 0x130180 };

u32 mb2_gateMot6[] = { 1, 0x130184 };

u32 *mb2_gateMotTbl[] = { mb2_gateMot1, mb2_gateMot2, mb2_gateMot3, mb2_gateMot4, mb2_gateMot5, mb2_gateMot6 };

s32 mb2_gateOpenSeTbl[] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1
};

s32 mb2_gateOpenDelaySeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb2_gateOpenDelayTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb2_gateCloseSeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s16 mb2_bankMapIconMasuTbl[] = { 110, 112 };

s16 mb2_shopMapIconMasuTbl[] = { 108, 109 };

Object *mb2_vacuumRouletteMdl = NULL;

Object *mb2_shortcutMdl = NULL;

s16 mb2_shortcutMarkMasuTbl[] = { 124, 126, 127, 128 };

DecisionTreeNonLeafNode mb2ev_branch2Star47ComTree[] = {
    { 3, { .data = 0x00000140 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch2ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000090 }, { .node_data = mb2ev_branch2Star47ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch2Star0ComTree[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch2ComTree1[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2ev_branch2Star0ComTree } },
    { 2, { .data = 0x00000090 }, { .node_data = mb2ev_branch2Star47ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch2ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2ev_branch2Star0ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb2ev_branch2ComTree[] = { mb2ev_branch2ComTree0, mb2ev_branch2ComTree1, mb2ev_branch2ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch3Star13ComTree[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch3ComTree0[] = {
    { 2, { .data = 0x0000000A }, { .node_data = mb2ev_branch3Star13ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch3ComTree1[] = {
    { 2, { .data = 0x0000000A }, { .node_data = mb2ev_branch3Star13ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch3ComTree2Star3[] = {
    { 9, { .data = 0x00000009 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch3ComTree2Star7[] = {
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch3ComTree2[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb2ev_branch3ComTree2Star3 } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2ev_branch3ComTree2Star7 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb2ev_branch3ComTree[] = { mb2ev_branch3ComTree0, mb2ev_branch3ComTree1, mb2ev_branch3ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch4ComTree0Star0[] = {
    { 3, { .data = 0x00000050 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch4ComTree0Star4[] = {
    { 3, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch4Star5ComTree[] = {
    { 3, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch4Star67ComTree[] = {
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000050 }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch4ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2ev_branch4ComTree0Star0 } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2ev_branch4ComTree0Star4 } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2ev_branch4Star5ComTree } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb2ev_branch4Star67ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch4Star012ComTree[] = {
    { 3, { .data = 0x00000046 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch4ComTree1[] = {
    { 2, { .data = 0x00000007 }, { .node_data = mb2ev_branch4Star012ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2ev_branch4Star5ComTree } },
    { 2, { .data = 0x000000C0 }, { .node_data = mb2ev_branch4Star67ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch4ComTree2Star467[] = {
    { 3, { .data = 0x00000050 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch4ComTree2[] = {
    { 2, { .data = 0x00000007 }, { .node_data = mb2ev_branch4Star012ComTree } },
    { 2, { .data = 0x000000D0 }, { .node_data = mb2ev_branch4ComTree2Star467 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb2ev_branch4ComTree[] = { mb2ev_branch4ComTree0, mb2ev_branch4ComTree1, mb2ev_branch4ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch5ComTree0Star456[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch5ComTree0[] = {
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000070 }, { .node_data = mb2ev_branch5ComTree0Star456 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch5ComTree1Star6[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch5ComTree1[] = {
    { 2, { .data = 0x00000040 }, { .node_data = mb2ev_branch5ComTree1Star6 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch5ComTree2Star7[] = {
    { 1, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch5ComTree2[] = {
    { 2, { .data = 0x00000080 }, { .node_data = mb2ev_branch5ComTree2Star7 } },
    { 2, { .data = 0x00000040 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb2ev_branch5ComTree[] = { mb2ev_branch5ComTree0, mb2ev_branch5ComTree1, mb2ev_branch5ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch6ComTree0Star0[] = {
    { 3, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch6ComTree0Star123[] = {
    { 3, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000005 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch6ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2ev_branch6ComTree0Star0 } },
    { 2, { .data = 0x0000000E }, { .node_data = mb2ev_branch6ComTree0Star123 } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x0000000A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch6Star4567ComTree[] = {
    { 3, { .data = 0x00000058 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch6ComTree1[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000F0 }, { .node_data = mb2ev_branch6Star4567ComTree } },
    { 3, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch6ComTree2Star0[] = {
    { 3, { .data = 0x0000000A }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch6ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2ev_branch6ComTree2Star0 } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000F0 }, { .node_data = mb2ev_branch6Star4567ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb2ev_branch6ComTree[] = { mb2ev_branch6ComTree0, mb2ev_branch6ComTree1, mb2ev_branch6ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch7ComTree0Star3[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch7ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2ev_branch7ComTree0Star3 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch7ComTree1[] = {
    { 2, { .data = 0x0000000A }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch7ComTree2Star3[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch7ComTree2[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb2ev_branch7ComTree2Star3 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode *mb2ev_branch7ComTree[] = { mb2ev_branch7ComTree0, mb2ev_branch7ComTree1, mb2ev_branch7ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch8ComTree0Star4567[] = {
    { 3, { .data = 0x0000000C }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch8ComTree0[] = {
    { 2, { .data = 0x000000F0 }, { .node_data = mb2ev_branch8ComTree0Star4567 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch8ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch8ComTree2Star4567[] = {
    { 3, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch8ComTree2[] = {
    { 2, { .data = 0x000000F0 }, { .node_data = mb2ev_branch8ComTree2Star4567 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb2ev_branch8ComTree[] = { mb2ev_branch8ComTree0, mb2ev_branch8ComTree1, mb2ev_branch8ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch9ComTree0[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x000000C0 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_branch9ComTree1[] = {
    { 9, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode mb2ev_branch9ComTree2[] = {
    { 9, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb2ev_branch9ComTree[] = { mb2ev_branch9ComTree0, mb2ev_branch9ComTree1, mb2ev_branch9ComTree2 };

DecisionTreeNonLeafNode mb2ev_branch10ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x0000000C }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x000000A0 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb2ev_branch10ComTree[] = { mb2ev_branch10ComTree0, mb2ev_branch10ComTree0, mb2ev_branch10ComTree0 };

DecisionTreeNonLeafNode mb2ev_shortcutBranchComTree0Star0123[] = {
    { 6, { .func = MB2_ComShortcutMarkCheck }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb2ev_shortcutBranchComTree0[] = {
    { 2, { .data = 0x0000000F }, { .node_data = mb2ev_shortcutBranchComTree0Star0123 } },
    { 6, { .func = MB2_ComShortcutMarkCheck }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode *mb2ev_shortcutBranchComTree[] = { mb2ev_shortcutBranchComTree0, mb2ev_shortcutBranchComTree0, mb2ev_shortcutBranchComTree0 };

DecisionTreeNonLeafNode mb2ev_shortcutEnd0ComTree0[] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } }
};

DecisionTreeNonLeafNode mb2ev_shortcutEnd0ComTree1[] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 2, { .data = 0x00000080 }, { .data = 0x0B56AD5A } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } }
};

DecisionTreeNonLeafNode mb2ev_shortcutEnd1ComTree0[] = {
    { 2, { .data = 0x00000007 }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } }
};

DecisionTreeNonLeafNode mb2ev_shortcutEnd1ComTree1[] = {
    { 2, { .data = 0x0000000F }, { .data = 0x0A142850 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1C993264 } }
};

event_list_entry mb2_branch1EventTbl[] = {
    { 8, 1, MB2Ev_Branch1 },
    { 0, 0, NULL }
};

s16 mb2ev_branch2Masu[][3] = {
    { 55, 34, -1 },
    { 44, 34, -1 },
    { 44, 55, -1 }
};

BranchLink mb2ev_branch2Link[][2] = {
    { { 2, 0, 0 }, { 1, 0, 0 } },
    { { 0, 19, 1 }, { 1, 0, 0 } },
    { { 0, 19, 1 }, { 2, 0, 0 } }
};

event_list_entry mb2_branch2EventTbl[] = {
    { 1, 2, MB2Ev_Branch2 },
    { 0, 0, NULL }
};

s16 mb2ev_branch3Masu[][3] = {
    { 17, 38, -1 },
    { 16, 38, -1 },
    { 16, 17, -1 }
};

BranchLink mb2ev_branch3Link[][2] = {
    { { 0, 0, 0 }, { 3, 0, 0 } },
    { { 4, 4, 1 }, { 3, 0, 0 } },
    { { 4, 4, 1 }, { 0, 0, 0 } }
};

event_list_entry mb2_branch3EventTbl[] = {
    { 1, 1, MB2Ev_Branch3 },
    { 0, 0, NULL }
};

s16 mb2ev_branch4Masu[][3] = {
    { 54, 91, -1 },
    { 53, 91, -1 },
    { 53, 54, -1 }
};

BranchLink mb2ev_branch4Link[][2] = {
    { { 7, 0, 0 }, { 8, 0, 0 } },
    { { 6, 10, 1 }, { 8, 0, 0 } },
    { { 6, 10, 1 }, { 7, 0, 0 } }
};

event_list_entry mb2_branch4EventTbl[] = {
    { 1, 2, MB2Ev_Branch4 },
    { 0, 0, NULL }
};

s16 mb2ev_branch5Masu[][3] = {
    { 79, 89, -1 },
    { 76, 89, -1 },
    { 76, 79, -1 }
};

BranchLink mb2ev_branch5Link[][2] = {
    { { 10, 0, 0 }, { 9, 0, 0 } },
    { { 7, 21, 1 }, { 9, 0, 0 } },
    { { 7, 21, 1 }, { 10, 0, 0 } }
};

event_list_entry mb2_branch5EventTbl[] = {
    { 1, 1, MB2Ev_Branch5 },
    { 0, 0, NULL }
};

s16 mb2ev_branch6Masu[][3] = {
    { 24, 37, -1 },
    { 21, 37, -1 },
    { 21, 24, -1 }
};

BranchLink mb2ev_branch6Link[][2] = {
    { { 0, 6, 0 }, { 1, 3, 1 } },
    { { 0, 4, 1 }, { 1, 3, 1 } },
    { { 0, 4, 1 }, { 0, 6, 0 } }
};

event_list_entry mb2_branch6EventTbl[] = {
    { 1, 1, MB2Ev_Branch6RKinoko },
    { 0, 0, NULL }
};

s16 mb2ev_branch7Masu[][3] = {
    { 4, 41, -1 },
    { 2, 41, -1 },
    { 2, 4, -1 }
};

BranchLink mb2ev_branch7Link[][2] = {
    { { 2, 8, 0 }, { 3, 6, 1 } },
    { { 2, 6, 1 }, { 3, 6, 1 } },
    { { 2, 6, 1 }, { 2, 8, 0 } }
};

event_list_entry mb2_branch7EventTbl[] = {
    { 1, 1, MB2Ev_Branch7RKinoko },
    { 0, 0, NULL }
};

s16 mb2ev_branch8Masu[][3] = {
    { 49, 90, -1 },
    { 47, 90, -1 },
    { 47, 49, -1 }
};

BranchLink mb2ev_branch8Link[][2] = {
    { { 6, 6, 0 }, { 9, 4, 1 } },
    { { 6, 4, 1 }, { 9, 4, 1 } },
    { { 6, 4, 1 }, { 6, 6, 0 } }
};

event_list_entry mb2_branch8EventTbl[] = {
    { 1, 1, MB2Ev_Branch8RKinoko },
    { 0, 0, NULL }
};

s16 mb2ev_branch9Masu[][3] = {
    { 74, 93, -1 },
    { 72, 93, -1 },
    { 72, 74, -1 }
};

BranchLink mb2ev_branch9Link[][2] = {
    { { 7, 19, 0 }, { 8, 3, 1 } },
    { { 7, 17, 1 }, { 8, 3, 1 } },
    { { 7, 17, 1 }, { 7, 19, 0 } }
};

event_list_entry mb2_branch9EventTbl[] = {
    { 1, 1, MB2Ev_Branch9RKinoko },
    { 0, 0, NULL }
};

s16 mb2ev_branch10Masu[][3] = {
    { 11, 32, -1 }
};

BranchLink mb2ev_branch10Link[][2] = {
    { { 0, 16, 0 }, { 0, 14, 1 } }
};

event_list_entry mb2_branch10EventTbl[] = {
    { 1, 1, MB2Ev_Branch10Check },
    { 0, 0, NULL }
};

event_list_entry mb2_merge1EventTbl[] = {
    { 1, 1, MB2Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge2EventTbl[] = {
    { 1, 1, MB2Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge3EventTbl[] = {
    { 1, 1, MB2Ev_Merge3 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge4EventTbl[] = {
    { 1, 1, MB2Ev_Merge4 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge5EventTbl[] = {
    { 1, 1, MB2Ev_Merge5 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge6EventTbl[] = {
    { 1, 1, MB2Ev_Merge6 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge7EventTbl[] = {
    { 1, 1, MB2Ev_Merge7 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge8EventTbl[] = {
    { 1, 1, MB2Ev_Merge8 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge9EventTbl[] = {
    { 1, 1, MB2Ev_Merge9 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge10EventTbl[] = {
    { 1, 1, MB2Ev_Merge10 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge11EventTbl[] = {
    { 1, 1, MB2Ev_Merge11 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge12EventTbl[] = {
    { 1, 1, MB2Ev_Merge12 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge13EventTbl[] = {
    { 1, 1, MB2Ev_Merge13 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge14EventTbl[] = {
    { 1, 1, MB2Ev_Merge14 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge15EventTbl[] = {
    { 1, 1, MB2Ev_Merge15 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge16EventTbl[] = {
    { 1, 1, MB2Ev_Merge16 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge17EventTbl[] = {
    { 1, 1, MB2Ev_Merge17 },
    { 0, 0, NULL }
};

event_list_entry mb2_merge18EventTbl[] = {
    { 1, 1, MB2Ev_Merge18 },
    { 0, 0, NULL }
};

event_list_entry mb2_keyManMasuEventTbl[] = {
    { 1, 2, MB2Ev_KeyManMasu },
    { 0, 0, NULL }
};

event_list_entry mb2_starMasuEventTbl[] = {
    { 1, 1, MB2Ev_StarMasu },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb2ev_bankComTree[] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } }
};

u32 mb2ev_bankCoinPileMot[] = { 1, 0xA009D };

event_list_entry mb2_bankMasuEventTbl[] = {
    { 1, 1, MB2Ev_BankMasu },
    { 0, 0, NULL }
};

u8 mb2ev_shopItemRowTbl[][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }
};

s8 mb2ev_shopItemTbl[][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } }
};

u8 mb2ev_shopBagRowTbl[][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }
};

s8 mb2ev_shopBagRateTbl[][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } }
};

u8 mb2ev_shopBagItemTbl[][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 }
};

s32 mb2ev_shopItemMesTbl[][2] = {
    { 0x3B05, 0x3D05 },
    { 0x3B06, 0x3D06 },
    { 0x3B07, 0x3D07 },
    { 0x3B08, 0x3D08 },
    { 0x3B09, 0x3D09 }
};

s32 mb2ev_shopEnterMesTbl[] = { 0x3B00, 0x3D00 };

s32 mb2ev_shopNoCoinMesTbl[] = { 0x3B01, 0x3D01 };

s32 mb2ev_shopItemFullMesTbl[] = { 0x3B02, 0x3D02 };

s32 mb2ev_shopLastTurnMesTbl[] = { 0x3B03, 0x3D03 };

s32 mb2ev_shopCancelMesTbl[] = { 0x3B04, 0x3D04 };

u32 mb2ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb2ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

s32 mb2ev_shopNo = 0;

event_list_entry mb2_shopMasuEventTbl[] = {
    { 1, 1, MB2Ev_ShopMasu },
    { 0, 0, NULL }
};

Vec2f mb2ev_teresaSprPosTbl[] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f }
};

Vec2f mb2ev_teresaSprDirTbl[] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f }
};

u8 mb2ev_teresaCoinTurnTbl[][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

u8 mb2ev_teresaCoinPenaltyTbl[][3] = {
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

u8 mb2ev_teresaCoinDiffTbl[] = { 9, 7, 4, 1, 0, 0, 0, 0 };

s32 mb2ev_teresaComTargetRateTbl[] = { 50, 80, 100 };

s32 mb2ev_teresaMdlFlipTbl[] = { 1, 0, 1, 0, 0, 1, 0 };

event_list_entry mb2_teresaMasuEventTbl[] = {
    { 1, 1, MB2Ev_Teresa },
    { 0, 0, NULL }
};

event_list_entry mb2_gate1CloseEventTbl[] = {
    { 1, 1, MB2Ev_Gate1Close },
    { 0, 0, NULL }
};

event_list_entry mb2_gate2CloseEventTbl[] = {
    { 1, 1, MB2Ev_Gate2Close },
    { 0, 0, NULL }
};

event_table_entry mb2_commonEventTbl[] = {
    { 30, mb2_starMasuEventTbl },
    { 40, mb2_starMasuEventTbl },
    { 21, mb2_starMasuEventTbl },
    { 7, mb2_starMasuEventTbl },
    { 65, mb2_starMasuEventTbl },
    { 92, mb2_starMasuEventTbl },
    { 76, mb2_starMasuEventTbl },
    { 86, mb2_starMasuEventTbl },
    { 33, mb2_bankMasuEventTbl },
    { 75, mb2_bankMasuEventTbl },
    { 115, mb2_shopMasuEventTbl },
    { 105, mb2_shopMasuEventTbl },
    { 106, mb2_gate1CloseEventTbl },
    { 107, mb2_gate2CloseEventTbl },
    { -1, NULL }
};

event_table_entry mb2_teresaEventTbl[] = {
    { 121, mb2_teresaMasuEventTbl },
    { -1, NULL }
};

Vec2f mb2ev_itemUsePosTbl[] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f }
};

Vec2f mb2ev_itemFadePosTbl[] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f }
};

Vec2f mb2ev_robBoxItemEndPosTbl[] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f }
};

Vec2f mb2ev_robBoxItemStartPosTbl[] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f }
};

DecisionTreeNonLeafNode mb2ev_shopPhoneComTree[] = {
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

s32 mb2ev_itemPhoneWaveAngleTbl[] = { 20, 60, 30, 50, 70 };

DecisionTreeNonLeafNode mb2ev_keyManUseComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } }
};

Vec2f mb2ev_tereYokeSparkOfsTbl[] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f }
};

s32 mb2ev_gambleCoinPlayer = -1;

u8 mb2ev_gambleMgTbl[] = { 67, 68, 69, 0 };

u8 mb2ev_gambleMgRateTbl[] = { 20, 60, 100, 0 };

GameGuyReward mb2ev_gambleRateTbl[] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 }
};

RGB mb2ev_after5NumColorTbl[] = {
    { 240, 222, 53 },
    { 247, 26, 66 }
};

event_list_entry mb2_kinokoTurnEventTbl[] = {
    { 7, 1, MB2Ev_NKinokoTurnStart },
    { 7, 1, MB2Ev_RKinokoTurnStart },
    { 0, 0, NULL }
};

event_table_entry mb2_turnStatusEventTbl[] = {
    { -5, mb2_kinokoTurnEventTbl },
    { -1, NULL }
};

s16 mb2ev_shortcutBranchMasu[][3] = {
    { 42, 12, -1 }
};

BranchLink mb2ev_shortcutBranchLink[][2] = {
    { { 6, 0, 0 }, { 4, 0, 0 } }
};

u32 mb2ev_shortcutMotMario[] = { 1, 0x2001A };

u32 mb2ev_shortcutMotLuigi[] = { 1, 0 };

u32 mb2ev_shortcutMotPeach[] = { 1, 0 };

u32 mb2ev_shortcutMotYoshi[] = { 1, 0 };

u32 mb2ev_shortcutMotWario[] = { 1, 0 };

u32 mb2ev_shortcutMotDk[] = { 1, 0 };

u32 mb2ev_shortcutMotWaluigi[] = { 1, 0 };

u32 mb2ev_shortcutMotDaisy[] = { 1, 0 };

u32 *mb2ev_shortcutMotTbl[] = { mb2ev_shortcutMotMario, mb2ev_shortcutMotLuigi, mb2ev_shortcutMotPeach, mb2ev_shortcutMotYoshi, mb2ev_shortcutMotWario, mb2ev_shortcutMotDk, mb2ev_shortcutMotWaluigi, mb2ev_shortcutMotDaisy };

s32 mb2ev_shortcutChrMdlTbl[] = { 14, 15, 16, 17, 18, 19, 20, 21 };

s16 mb2ev_shortcutEnd0Masu[] = { 10, 87, 42, -1 };

s16 mb2ev_shortcutEnd1Masu[] = { 12, 10, 87, -1 };

event_list_entry mb2_shortcutEventTbl[] = {
    { 1, 1, MB2Ev_Shortcut },
    { 0, 0, NULL }
};

s32 mb2ev_vacuumEffOnF = 1;

s32 mb2ev_vacuumEffRate = 1;

s32 mb2ev_vacuumFlyMasuTbl[] = { 85, 80, 82 };

s32 mb2ev_vacuumDestMasuTbl[] = { 4, 68, 103 };

s32 mb2ev_vacuumExitMasuTbl[] = { 117, 118, 116 };

f32 mb2ev_vacuumLandOfsTbl[][2] = {
    { 0.0f, 0.0f },
    { 0.0f, 14.0f },
    { 7.0f, 7.0f },
    { -7.0f, 7.0f }
};

s16 mb2ev_hatenaWarpMasuTbl[] = {
    15, 46, 47, 16, 17, 49, 18, 50,
    51, 19, 52, 20, 25, 58, 59, 26,
    27, 60, 61, 28
};

event_table_entry mb2_specialEventTbl[] = {
    { 103, mb2_branch1EventTbl },
    { 104, mb2_branch2EventTbl },
    { 132, mb2_branch3EventTbl },
    { 137, mb2_branch4EventTbl },
    { 78, mb2_branch5EventTbl },
    { 23, mb2_branch6EventTbl },
    { 3, mb2_branch7EventTbl },
    { 48, mb2_branch8EventTbl },
    { 73, mb2_branch9EventTbl },
    { 0, mb2_branch10EventTbl },
    { 17, mb2_merge1EventTbl },
    { 34, mb2_merge2EventTbl },
    { 37, mb2_merge3EventTbl },
    { 55, mb2_merge4EventTbl },
    { 10, mb2_merge5EventTbl },
    { 38, mb2_merge6EventTbl },
    { 41, mb2_merge7EventTbl },
    { 12, mb2_merge8EventTbl },
    { 42, mb2_merge9EventTbl },
    { 54, mb2_merge10EventTbl },
    { 91, mb2_merge11EventTbl },
    { 93, mb2_merge12EventTbl },
    { 89, mb2_merge13EventTbl },
    { 90, mb2_merge14EventTbl },
    { 79, mb2_merge15EventTbl },
    { 87, mb2_merge16EventTbl },
    { 130, mb2_merge17EventTbl },
    { 131, mb2_merge18EventTbl },
    { 133, mb2_keyManMasuEventTbl },
    { 135, mb2_keyManMasuEventTbl },
    { 134, mb2_keyManMasuEventTbl },
    { 136, mb2_keyManMasuEventTbl },
    { 125, mb2_shortcutEventTbl },
    { -1, NULL }
};

RectF mb2ev_opStarMapViewRect = { 0.0f, 0.0f, 320.0f, 240.0f };

DecisionTreeNonLeafNode mb2_itemSKinokoStar0ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00010003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00001315 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000E12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar1ItemComTree[] = {
    { 10, { .data = 0x0002000E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 8, { .data = 0x00000001 }, { .node_data = mb2_itemSKinokoStar1ItemComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00040005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00020006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00001315 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00000C12 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0006000B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00090104 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00060006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0008 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002080E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar6ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x0007000E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0006000B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoStar7ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x00000000 } },
    { 10, { .data = 0x0007070E }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00071416 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00070F13 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemSKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2_itemSKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb2_itemSKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb2_itemSKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2_itemSKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2_itemSKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2_itemSKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_itemSKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2_itemSKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemKSuitComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A141932 } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar0ComTree[] = {
    { 10, { .data = 0x0000050B }, { .data = 0x0001038A } },
    { 11, { .data = 0x0000050B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar1ComTree[] = {
    { 10, { .data = 0x00030104 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00030104 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar2ComTree[] = {
    { 10, { .data = 0x00000003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00040305 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040305 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar3ComTree[] = {
    { 10, { .data = 0x0002050A }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030406 }, { .data = 0x0001038A } },
    { 11, { .data = 0x0002050A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030406 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar4ComTree[] = {
    { 10, { .data = 0x00070409 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00070409 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar5ComTree[] = {
    { 10, { .data = 0x00080001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x0006060B }, { .data = 0x0001038A } },
    { 11, { .data = 0x00080001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0006060B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar6ComTree[] = {
    { 10, { .data = 0x00070E14 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00070E14 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00080003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockStar7ComTree[] = {
    { 10, { .data = 0x000A0006 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000A0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb2_itemWarpBlockComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2_itemWarpBlockStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb2_itemWarpBlockStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb2_itemWarpBlockStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2_itemWarpBlockStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2_itemWarpBlockStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2_itemWarpBlockStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_itemWarpBlockStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2_itemWarpBlockStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar0ComTree[] = {
    { 10, { .data = 0x0000050B }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar1ComTree[] = {
    { 10, { .data = 0x00030104 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar2ComTree[] = {
    { 10, { .data = 0x00000003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00040305 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar3ComTree[] = {
    { 10, { .data = 0x0002050A }, { .data = 0x0001038A } },
    { 10, { .data = 0x00030406 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar4ComTree[] = {
    { 10, { .data = 0x00070409 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar5ComTree[] = {
    { 10, { .data = 0x00080001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x0006060B }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar6ComTree[] = {
    { 10, { .data = 0x00070E14 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00080003 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampStar7ComTree[] = {
    { 10, { .data = 0x000A0006 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb2_itemMajinLampComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2_itemMajinLampStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb2_itemMajinLampStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb2_itemMajinLampStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2_itemMajinLampStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2_itemMajinLampStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2_itemMajinLampStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_itemMajinLampStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2_itemMajinLampStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar0ComTree[] = {
    { 11, { .data = 0x00000509 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar1ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar2ComTree[] = {
    { 11, { .data = 0x00000000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00040205 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar3ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar4ComTree[] = {
    { 11, { .data = 0x00070105 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar5ComTree[] = {
    { 11, { .data = 0x00060507 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar6ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoStar7ComTree[] = {
    { 11, { .data = 0x000A0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoComTree[] = {
    { 10, { .data = 0x00000F11 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00080303 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071113 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = mb2_itemNKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb2_itemNKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb2_itemNKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2_itemNKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2_itemNKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2_itemNKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_itemNKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2_itemNKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoSelfComTree[] = {
    { 15, { .data = 0x00000F11 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00080303 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071113 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x00000509 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar1ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00000000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00030000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040205 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar3ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x00070105 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x00060507 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar6ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemNKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x000A0004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode *mb2_itemNKinokoTargetComTree[] = { mb2_itemNKinokoTargetStar0ComTree, mb2_itemNKinokoTargetStar1ComTree, mb2_itemNKinokoTargetStar2ComTree, mb2_itemNKinokoTargetStar3ComTree, mb2_itemNKinokoTargetStar4ComTree, mb2_itemNKinokoTargetStar5ComTree, mb2_itemNKinokoTargetStar6ComTree, mb2_itemNKinokoTargetStar7ComTree };

DecisionTreeNonLeafNode mb2_itemRKinokoStar0ComTree[] = {
    { 10, { .data = 0x00000D12 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0000050B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar1ComTree[] = {
    { 10, { .data = 0x00030606 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002080B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar2ComTree[] = {
    { 10, { .data = 0x0000050A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00000003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar3ComTree[] = {
    { 10, { .data = 0x00020C0E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar4ComTree[] = {
    { 10, { .data = 0x00070B12 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00070904 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar5ComTree[] = {
    { 10, { .data = 0x00080303 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071316 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00071016 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar6ComTree[] = {
    { 10, { .data = 0x00090000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoStar7ComTree[] = {
    { 10, { .data = 0x000A0808 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000A0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb2_itemRKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb2_itemRKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb2_itemRKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb2_itemRKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb2_itemRKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb2_itemRKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_itemRKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb2_itemRKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar0ComTree[] = {
    { 15, { .data = 0x00000D12 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar1ComTree[] = {
    { 15, { .data = 0x00030606 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x0002080B }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar2ComTree[] = {
    { 15, { .data = 0x0000050A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar3ComTree[] = {
    { 15, { .data = 0x00020C0E }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00060002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar4ComTree[] = {
    { 15, { .data = 0x00070B12 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar5ComTree[] = {
    { 15, { .data = 0x00080303 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071316 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00071016 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar6ComTree[] = {
    { 15, { .data = 0x00090000 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000A0005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoSelfStar7ComTree[] = {
    { 15, { .data = 0x000A0808 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00060004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x0000050B }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar1ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00000003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar3ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x00070904 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar5ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar6ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_itemRKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x000A0006 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode *mb2_itemRKinokoSelfComTree[] = { mb2_itemRKinokoSelfStar0ComTree, mb2_itemRKinokoSelfStar1ComTree, mb2_itemRKinokoSelfStar2ComTree, mb2_itemRKinokoSelfStar3ComTree, mb2_itemRKinokoSelfStar4ComTree, mb2_itemRKinokoSelfStar5ComTree, mb2_itemRKinokoSelfStar6ComTree, mb2_itemRKinokoSelfStar7ComTree };

DecisionTreeNonLeafNode *mb2_itemRKinokoTargetComTree[] = { mb2_itemRKinokoTargetStar0ComTree, mb2_itemRKinokoTargetStar1ComTree, mb2_itemRKinokoTargetStar2ComTree, mb2_itemRKinokoTargetStar3ComTree, mb2_itemRKinokoTargetStar4ComTree, mb2_itemRKinokoTargetStar5ComTree, mb2_itemRKinokoTargetStar6ComTree, mb2_itemRKinokoTargetStar7ComTree };

DecisionTreeNonLeafNode mb2_itemStarYokeComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb2_itemWarpBlockComTree } }
};

DecisionTreeNonLeafNode mb2_comShopKeyComTree0[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_comShopKeyComTree1[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_comShopItemComTree0[] = {
    { 2, { .data = 0x000000F1 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_comShopItemComTree1[] = {
    { 2, { .data = 0x0000001F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree0Star3WalkMin[] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree0Star3[] = {
    { 9, { .data = 0x00000008 }, { .node_data = mb2_comShopEnterComTree0Star3WalkMin } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree0[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb2_comShopEnterComTree0Star3 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree1Star6WalkMin[] = {
    { 1, { .data = 0x0000002D }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree1Star6[] = {
    { 9, { .data = 0x00000006 }, { .node_data = mb2_comShopEnterComTree1Star6WalkMin } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree1Star5[] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb2_comShopEnterComTree1[] = {
    { 2, { .data = 0x00000020 }, { .node_data = mb2_comShopEnterComTree1Star5 } },
    { 2, { .data = 0x00000040 }, { .node_data = mb2_comShopEnterComTree1Star6 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

s32 mb2_comShopCancelF = 0;

u8 mb2_comShopItemOrderMario[] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1
};

u8 mb2_comShopItemOrderLuigi[] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5
};

u8 mb2_comShopItemOrderPeach[] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1
};

u8 mb2_comShopItemOrderYoshi[] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1
};

u8 mb2_comShopItemOrderWario[] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1
};

u8 mb2_comShopItemOrderDk[] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1
};

u8 mb2_comShopItemOrderWaluigi[] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1
};

u8 mb2_comShopItemOrderDaisy[] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5
};

u8 *mb2_comShopItemOrderTbl[] = { mb2_comShopItemOrderMario, mb2_comShopItemOrderLuigi, mb2_comShopItemOrderPeach, mb2_comShopItemOrderYoshi, mb2_comShopItemOrderWario, mb2_comShopItemOrderDk, mb2_comShopItemOrderWaluigi, mb2_comShopItemOrderDaisy };

s8 mb2_comShopItemRateMario[] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb2_comShopItemRateLuigi[] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0
};

s8 mb2_comShopItemRatePeach[] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10
};

s8 mb2_comShopItemRateYoshi[] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10
};

s8 mb2_comShopItemRateWario[] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10
};

s8 mb2_comShopItemRateDk[] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb2_comShopItemRateWaluigi[] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10
};

s8 mb2_comShopItemRateDaisy[] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10
};

s8 *mb2_comShopItemRateTbl[] = { mb2_comShopItemRateMario, mb2_comShopItemRateLuigi, mb2_comShopItemRatePeach, mb2_comShopItemRateYoshi, mb2_comShopItemRateWario, mb2_comShopItemRateDk, mb2_comShopItemRateWaluigi, mb2_comShopItemRateDaisy };

DecisionTreeNonLeafNode *mb2_comShopKeyComTree[] = { mb2_comShopKeyComTree0, mb2_comShopKeyComTree1 };

DecisionTreeNonLeafNode *mb2_comShopItemComTree[] = { mb2_comShopItemComTree0, mb2_comShopItemComTree1 };

DecisionTreeNonLeafNode *mb2_comShopEnterComTree[] = { mb2_comShopEnterComTree0, mb2_comShopEnterComTree1 };

Object *mb2_starGuideBaseMdl BSS;
u8 mb2_starGuideBaseMdlPad[4] BSS; /* Unreferenced. */
Object *mb2_starGuideMdl[8] BSS;
Process *mb2_starGuideHoverProc[8] BSS;
Process *mb2ev_starGuideInProc BSS;
Object *mb2ev_starGuideInMdl BSS;
Unk3 *mb2_branchStickHelp BSS;
Unk3 *mb2_branchBtnHelp BSS;
Unk3 *mb2_branchMapScrollHelp BSS;
Unk3 *mb2_branchMapOverheadHelp BSS;
Unk3 *mb2_branchItemHelp BSS;
s32 mb2_comTeresaType BSS;
s32 mb2_comTeresaTarget BSS;
Object *mb2_teresaGuideBaseMdl BSS;
Object *mb2_teresaGuideMdl[1] BSS;
Object *mb2_bankCoinBaseMdl BSS;
Object *mb2_bankCoinMdl[10] BSS;
Object *mb2_gateBaseMdl BSS;
Object *mb2_gateMdl[2] BSS;
u8 mb2_gateMdlPad[4] BSS; /* Unreferenced. */
Object *mb2_shortcutMarkMdl[4] BSS;
s32 mb2ev_shopHostNo BSS;
s32 mb2ev_shopItemRow BSS;
u8 *mb2ev_shopItemEnableTbl BSS;
Object *mb2ev_teresaCoinMdl BSS;
s32 mb2ev_itemPhoneWaveSpr BSS;
s32 mb2ev_tereYokePlayer BSS;
s32 mb2ev_tereYokeSparkSpr BSS;
Object *mb2ev_koopaCardCoinMdl BSS;
Object *mb2ev_koopaCardMdl BSS;
s32 mb2_comExchangeBoxTarget BSS;
s32 mb2_comRobBoxTarget BSS;
Object *mb2ev_gambleCoinMdl BSS;
s32 mb2ev_after5GrpId[4] BSS;
Object *mb2ev_after5EffMdl BSS;
u8 mb2ev_after5EffMdlPad[4] BSS; /* Unreferenced. */
Object *mb2ev_kinokoMarkMdl[4] BSS;
omObjData *mb2ev_kinokoMarkObj[4] BSS;
s32 mb2_comRKinokoTarget BSS;
s32 mb2_comNKinokoTarget BSS;
s16 mb2ev_vacuumEffMdl BSS;
omObjData *mb2ev_vacuumEffObj BSS;

s16 MB2Ev_StarGuideMasuGet(void) {
    return mb2ev_starGuideMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void MB2Ev_StarShuffle(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < mb2ev_starOrderGroupTbl[idx2]) {
                continue;
            }
            if (idx2 < mb2ev_starOrderGroupTbl[idx1]) {
                continue;
            }
            {
                s32 temp = mb2ev_starOrderTbl[idx1];
                mb2ev_starOrderTbl[idx1] = mb2ev_starOrderTbl[idx2];
                mb2ev_starOrderTbl[idx2] = temp;
                temp = mb2ev_starOrderGroupTbl[idx1];
                mb2ev_starOrderGroupTbl[idx1] = mb2ev_starOrderGroupTbl[idx2];
                mb2ev_starOrderGroupTbl[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = mb2ev_starOrderTbl[i];
    }
}

void MB2Ev_StarNextPos(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        MB2Ev_StarShuffle();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void MB2Ev_StarMasuInit(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(mb2ev_starFlag[i]);
    }
    MBMasuTypeSet(mb2ev_starMasu[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(mb2ev_starFlag[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s16 MB2Ev_StarCheck(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == mb2ev_starMasu[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = mb2ev_starFlag[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void MB2Ev_StarGuideIn(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    mb2ev_starGuideInMdl = MBModelCreate(0x3A, NULL);
    model = mb2ev_starGuideInMdl;
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
    mb2ev_starGuideInProc = 0;
    omDelPrcObj(NULL);
}

void MB2Ev_StarGuideJumpExec(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    HuPrcSleep(3);
    while (obj->velocity.z != 0.0f) {
        HuPrcVSleep();
    }
}

#define GET_STAR_MODEL() mb2_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]
// MB3Ev_StarMapView
void MB2Ev_StarMapView(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *space;
    s32 face;
    s32 mesNum;
    GW_SYSTEM *system = &GwSystem;

    mbTurnUnkF = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, mb2ev_starGuideFaceTbl[0]);
    MBPlayerIconMdlSet();
    MBModelDispOff(GET_STAR_MODEL());
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBBackThreadPriLowSet();
    MBCameraSpeedDivSet(3.0f);
    MB2Ev_StarGuideJumpExec(guide);

    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E00;
        }
    } else {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E01;
        }
    }
    HuWinMesSet(guide->amount, mesNum, -1, -1);
    HuWinExOpen(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    MBWinComKeyAllWaitKeep(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    HuWinExClose(guide->amount, 1);
    Hu3DMotionReset(guide->obj->omObj1->model[0]);

    if ((system->current_board_index != SPINY_DESERT) || (rand8() & 1)) {
        space = MBMasuGet(mb2ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    face = MBRand(7.0f);
    MBGuideFaceSet(guide->obj, mb2ev_starGuideFaceTbl[face]);
    MBMotionSet(guide->obj, -1, 2);

    if (system->current_board_index != 2) {
        proc = omAddPrcObj(MB2Ev_StarGuideIn, 0x4800, 0, 0);
        mb2ev_starGuideInProc = proc;
        proc->user_data = space;
        HuPrcSleep(30);
    } else {
        mb2ev_starGuideInProc = NULL;
    }

    HuWinMesSet(guide->amount, mb2ev_starGuideMesTbl[face], -1, -1);
    HuWinExOpen(guide->amount, 1);
    MBWinComKeyAllWaitKeep(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    HuWinExClose(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(WIPE_STARS, 0x10);
    HuPrcSleep(0x11);
    mbTurnUnkF = 1;
    MBPlayerIconMdlReset();
    AuraKill(mb2ev_starGuideInMdl->omObj1->model[0]);
    MBModelKill(mb2ev_starGuideInMdl);
    MBModelDispOn(GET_STAR_MODEL());
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB2Ev_StarGet(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x79) {
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
    if (mb2ev_starGetTeresaF != 0) {
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
    if (mb2ev_starGetTeresaF != 0) {
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

void MB2Ev_StarGetExec(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(MB2Ev_StarGet, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void MB2_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MB2_MapScrollCancel(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void MB2_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mb2_branchStickHelp = MBHelpWinCreate(0, 0x92, 1);
    mb2_branchBtnHelp = MBHelpWinCreate(1, 0xA0, 1);
    mb2_branchItemHelp = MBHelpWinCreate(0xD, 0xAE, 1);
    mb2_branchMapScrollHelp = MBHelpWinCreate(3, 0xBC, 1);
    mb2_branchMapOverheadHelp = MBHelpWinCreate(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MB2_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBHelpWinKill(mb2_branchStickHelp);
    MBHelpWinKill(mb2_branchBtnHelp);
    MBHelpWinKill(mb2_branchItemHelp);
    MBHelpWinKill(mb2_branchMapScrollHelp);
    MBHelpWinKill(mb2_branchMapOverheadHelp);
}

// Keep rodata definitions interleaved with functions to preserve the original constant order.
const u8 mb2_padBitTbl[4] = { 1, 2, 4, 8 };

s32 MB2_ComShopItemChoice(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb2_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = MB2_ComShopItemDecide();
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

s32 MB2_ComShopEnterChoice(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb2_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches MBKettouTargetChoiceGet
                var_s2 = MB2_ComShopEnterDecide();
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

void MB2_ComTeresaTypeDecide(void) {
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
                mb2_comTeresaType = 1;
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
        mb2_comTeresaType = 0;
    } else {
        mb2_comTeresaType = 2;
    }
}

void MB2_ComTeresaTargetDecide(void) {
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
    MB2_ComTeresaTypeDecide();
    if (mb2_comTeresaType == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                mb2_comTeresaTarget = order[i];
                break;
            }
        }
    } else if (mb2_comTeresaType == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                mb2_comTeresaTarget = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        mb2_comTeresaType = 2;
    }
}

s32 MB2_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb2_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    MB2_ComTeresaTargetDecide();
                    var_s2 = mb2_comTeresaType + 1;
                } else {
                    var_s2 = mb2_comTeresaTarget + 1;
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

s32 MB2_ComTeresaTypeChoice(u8 *arg0) {
    return MB2_ComTeresaChoice(arg0, 0, 1);
}

s32 MB2_ComTeresaPlayerChoice(u8 *arg0) {
    return MB2_ComTeresaChoice(arg0, 1, 0);
}

void MB2_BoardInit(void) {
    GwSystem.current_board_index = 1;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(boardcall, 0, 0x192);
}

void MB2_SaveInit(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0xB, 0);
    MBMoveMasuSet(1, 0xB, 0);
    MBMoveMasuSet(2, 0xB, 0);
    MBMoveMasuSet(3, 0xB, 0);
    GWBoardFlagSet(3);
    MB2Ev_StarShuffle();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    GwSystem.boardData.halfWordBytes[1] = MBRand(4.0f);
    omOvlReturnEx(1);
}

void MB2_ObjectSetup(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(6, 0x23B, 8, 0);
    MBMasuBlockTblExtSet(mb2_masuBlockExtTbl);
    MBMasuBlockTblSet(mb2_masuBlockTbl);
    space = MBMasuGet(0x69);
    MBVecDirGet(&space->coords, &MBMasuGet(0x6D)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x73);
    MBVecDirGet(&space->coords, &MBMasuGet(0x6C)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &MB2Ev_Teresa);
    MBItemHookSet(1, &MB2Ev_ItemMajinLamp);
    MBItemHookSet(9, &MB2Ev_ItemMajinLampStar);
    MBItemHookSet(2, &MB2Ev_ItemWarpBlock);
    MBItemHookSet(3, &MB2Ev_ItemRobBox);
    MBItemHookSet(4, &MB2Ev_KSuitStart);
    MBItemHookSet(5, &MB2Ev_KSuitEnd);
    MBItemHookSet(6, &MB2Ev_ItemKinoko);
    MBItemHookSet(7, &MB2Ev_ItemShake);
    MBItemHookSet(8, &MB2Ev_ItemPhoneMove);
    MBItemHookSet(0xA, &MB2Ev_ItemNKinoko);
    MBItemHookSet(0xB, &MB2Ev_ItemRKinoko);
    MBItemHookSet(0xE, &MB2Ev_ItemShopPhone);
    MBItemHookSet(0xF, &MB2Ev_ItemKoopaPhone);
    MBItemHookSet(0x10, &MB2Ev_ItemStarYoke);
    MBItemHookSet(0x11, &MB2Ev_ItemKeyManUse);
    MBItemHookSet(0x12, &MB2Ev_ItemNullUse);
    MBItemHookSet(0x13, &MB2Ev_ItemExchangeBox);
    MBItemHookSet(0x14, &MB2Ev_ItemGambleCoin);
    MBItemHookSet(0x15, &MB2Ev_ItemAfter5);
    MBItemHookSet(0xC, &MB2Ev_ItemKoopaNKinoko);
    MBItemHookSet(0xD, &MB2Ev_ItemKoopaRKinoko);
    MBComItemDecideHookSet(MB2_ComItemDecide);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, mb2ev_starGuideMasu[i]);
    }
    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        MB2Ev_StarNextPos();
    }

    MB2Ev_StarMasuInit();
    MB2_StarGuideCreateAll();
    MB2_TeresaGuideCreateAll();
    MB2_BankCoinCreateAll();
    MB2_GateCreateAll();
    MB2_BankMapIconAddAll();
    MB2_ShopMapIconAddAll();
    MB2_ShortcutCreate();
    MB2_VacuumRouletteCreate();
    MB2_ShortcutMarkCreateAll();
    MB2Ev_KinokoMarkCreateAll();
    MBMasuTypeListCreate();
}

void MB2_Create(void) {
    HuAudSeqPlay(0x19);
    mbBoardMusId = 0x19;
    MBBoardParamSet(0x19);
    Hu3DCamInit(2);
    MB2_ObjectSetup();
    MBMasuEventTblAdd(mb2_commonEventTbl);
    MBMasuEventTblAdd(mb2_specialEventTbl);
    MBHatenaFuncSet(&MB2Ev_Hatena);
    MBMasuEventTblAdd(mb2_teresaEventTbl);
    MBMasuEventTblAdd(mb2_turnStatusEventTbl);
    MBStart(0);
}

void MB2_BoardReload(void) {
    Hu3DCamInit(1);
    MB2_ObjectSetup();
    MBStart(1);
}

void MB2_StarGuideCreate(s16 arg0) {
    Object *obj;

    if (mb2_starGuideMdl[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    AuraCreate(obj->omObj1->model[0]);
    if (mb2_starGuideBaseMdl == NULL) {
        mb2_starGuideBaseMdl = obj;
    }
    mb2_starGuideMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    mb2_starGuideHoverProc[arg0] = MBModelHoverCreate(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb2_starGuideMdlMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xB, obj, mb2_starGuideMapIconOfsTbl[arg0][0], mb2_starGuideMapIconOfsTbl[arg0][1]);
}

void MB2_StarGuideKill(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (mb2_starGuideHoverProc[i] != NULL) {
            omDelPrcObj(mb2_starGuideHoverProc[i]);
            mb2_starGuideHoverProc[i] = NULL;
        }
    }
}

void MB2_StarGuideCreateAll(void) {
    s32 i;

    mb2_starGuideBaseMdl = 0;
    for (i = 0; i < 8; i++) {
        mb2_starGuideMdl[i] = 0;
        mb2_starGuideHoverProc[i] = NULL;
        MBKinokoEffKillHookSet(MB2_StarGuideKill);
        if (!GWBoardFlagCheck(mb2_starGuideFlagTbl[i])) {
            MB2_StarGuideCreate(i);
        }
    }
}

void MB2_TeresaGuideCreate(s16 arg0) {
    Object *obj;

    if (mb2_teresaGuideMdl[arg0] != NULL) {
        return;
    }
    if (mb2_teresaGuideBaseMdl == NULL) {
        obj = MBModelCreate(0xA, NULL);
        Hu3DModelTPLvlInit(obj->omObj1->model[0]);
        Hu3DModelTPLvlInit(obj->omObj2->model[0]);
        mb2_teresaGuideBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb2_teresaGuideBaseMdl);
    }
    MBModelDispOff(obj);
    mb2_teresaGuideMdl[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb2_teresaGuideMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xA, obj, mb2_teresaGuideMapIconOfsTbl[arg0][0], mb2_teresaGuideMapIconOfsTbl[arg0][1]);
}

void MB2_TeresaGuideCreateAll(void) {
    s32 i;

    mb2_teresaGuideBaseMdl = 0;
    for (i = 0; i <= 0; i++) {
        mb2_teresaGuideMdl[i] = NULL;
        MB2_TeresaGuideCreate(i);
    }
}

void MB2_BankCoinHide(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(mb2_bankCoinMdl[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(mb2_bankCoinMdl[i * 5 + j]);
        }
    }
}

void MB2_BankCoinCreate(s16 arg0) {
    Object *obj;

    if (mb2_bankCoinMdl[arg0] != NULL) {
        return;
    }
    if (mb2_bankCoinBaseMdl == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        mb2_bankCoinBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb2_bankCoinBaseMdl);
    }
    mb2_bankCoinMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb2_bankCoinMasuTbl[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &mb2_bankCoinOfsTbl[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = mb2_bankCoinRotTbl[arg0 % 5].x;
    obj->omObj1->rot.z = mb2_bankCoinRotTbl[arg0 % 5].z;
    MBModelDispOff(obj);
}

void MB2_BankCoinCreateAll(void) {
    s32 i;

    mb2_bankCoinBaseMdl = 0;
    for (i = 0; i < 0xA; i++) {
        mb2_bankCoinMdl[i] = NULL;
        MB2_BankCoinCreate(i);
    }
    MB2_BankCoinHide();
}

void MB2_GateCreate(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (mb2_gateMdl[arg0] != NULL) {
        return;
    }
    if (mb2_gateBaseMdl == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(mb2_gateMdlTbl[board], mb2_gateMotTbl[board]);
        MBModelTempAllocFree(obj);
        mb2_gateBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb2_gateBaseMdl);
    }
    mb2_gateMdl[arg0] = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb2_gateMasuTbl[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(mb2_gateDirMasuTbl[arg0][0]);
        SpaceData *masuB = MBMasuGet(mb2_gateDirMasuTbl[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    MBMapFullIconMdlAdd(0xC, obj, mb2_gateMapIconOfsTbl[arg0][0], mb2_gateMapIconOfsTbl[arg0][1]);
}

void MB2_GateCreateAll(void) {
    s32 i;

    mb2_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        mb2_gateMdl[i] = NULL;
        MB2_GateCreate(i);
    }
}

void MB2_GateOpenSeProc(void) {
    HuPrcSleep(mb2_gateOpenDelayTbl[GwSystem.current_board_index]);
    // The sound ID lives in the upper halfword of each mb2_gateOpenDelaySeTbl entry
    HuAudFXPlay((s16)mb2_gateOpenDelaySeTbl[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void MB2_GateOpen(s32 arg0, s32 arg1) {
    MBMotionSet(mb2_gateMdl[arg0], arg1 - 1, 0);
    Hu3DMotionAttrSet(mb2_gateMdl[arg0]->omObj1->model[0], 5, 0);
    if (mb2_gateOpenSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb2_gateOpenSeTbl[GwSystem.current_board_index]);
    }

    if (mb2_gateOpenDelaySeTbl[GwSystem.current_board_index] != -1) {
        omAddPrcObj(MB2_GateOpenSeProc, 0x1000, 0, 0);
    }
}

void MB2_GateCloseProc(void) {
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
    Hu3DMotionAttrSet(mb2_gateMdl[index]->omObj1->model[0], 1, 4);

    if (mb2_gateCloseSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb2_gateCloseSeTbl[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void MB2_GateClose(s32 arg) {
    Process *prc = omAddPrcObj(MB2_GateCloseProc, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB2_BankMapIconAddAll(void) {
    s32 i;

    mb2_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(8, &MBMasuGet(mb2_bankMapIconMasuTbl[i])->coords,
                                   mb2_bankMapIconOfsTbl[i][0], mb2_bankMapIconOfsTbl[i][1]);
    }
}

void MB2_ShopMapIconAddAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(9, &MBMasuGet(mb2_shopMapIconMasuTbl[i])->coords,
                                   mb2_shopMapIconOfsTbl[i][0], mb2_shopMapIconOfsTbl[i][1]);
    }
}

void MB2_VacuumRouletteCreate(void) {
    SpaceData *masu = MBMasuGet(0x81);
    Object *obj = MBModelFileCreate(0x13016D, -1, 0.8f, 0, NULL);

    MBModelTempAllocFree(obj);
    mb2_vacuumRouletteMdl = obj;
    obj->flags |= 2;
    obj->rot.x = sindf(-138.0f);
    obj->rot.z = cosdf(-138.0f);
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void MB2_ShortcutCreate(void) {
    SpaceData *masu = MBMasuGet(0x7B);
    Object *obj = MBModelFileCreate(0x13016B, -1, 1.0f, 0, NULL);

    MBModelTempAllocFree(obj);
    mb2_shortcutMdl = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void MB2_ShortcutMarkDispSet(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((GwSystem.boardData.halfWordBytes[0] >> i) & 1) {
            MBModelDispOn(mb2_shortcutMarkMdl[i]);
        } else {
            MBModelDispOff(mb2_shortcutMarkMdl[i]);
        }
    }
}

void MB2_ShortcutMarkCreate(s16 arg0) {
    Object *obj;

    if (mb2_shortcutMarkMdl[arg0] == NULL) {
        obj = MBModelFileCreate(0x13016C, -1, 1.0f, 0, NULL);
        MBModelTempAllocFree(obj);
        mb2_shortcutMarkMdl[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBMasuGet(mb2_shortcutMarkMasuTbl[arg0])->coords);
        obj->coords.x -= 4.0f;
        obj->coords.z -= 2.0f;
    }
}

void MB2_ShortcutMarkCreateAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mb2_shortcutMarkMdl[i] = NULL;
        MB2_ShortcutMarkCreate(i);
    }
    MB2_ShortcutMarkDispSet();
}

// Counts the set bits among the 4 low per-board flags in GwSystem.boardData
s32 MB2_ComShortcutMarkCheck(void) {
    s32 flagsSet = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        flagsSet += (GwSystem.boardData.halfWordBytes[0] >> i) & 1;
    }
    return flagsSet >= 3;
}

void MB2Ev_Branch1(void) {
    MBMoveNextMasuSet(-1, 0, 0xF);
    MBMoveBackMasuSet(-1, 0, 0xF);
}

void MB2Ev_Branch2(void) {
    MB2Ev_BranchMain(mb2ev_branch2Masu, mb2ev_branch2Link, mb2ev_branch2ComTree);
    omDelPrcObj(NULL);
}

void MB2Ev_Branch3(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x26 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 0, 0);
        player->rev &= ~1;
    } else {
        MB2Ev_BranchMain(mb2ev_branch3Masu, mb2ev_branch3Link, mb2ev_branch3ComTree);
    }
}

void MB2Ev_Branch4(void) {
    MB2Ev_BranchMain(mb2ev_branch4Masu, mb2ev_branch4Link, mb2ev_branch4ComTree);
    omDelPrcObj(NULL);
}

void MB2Ev_Branch5(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x59 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 0xA, 0);
        player->rev &= ~1;
    } else {
        MB2Ev_BranchMain(mb2ev_branch5Masu, mb2ev_branch5Link, mb2ev_branch5ComTree);
    }
}

void MB2Ev_Branch6(void) {
    MB2Ev_BranchMain(mb2ev_branch6Masu, mb2ev_branch6Link, mb2ev_branch6ComTree);
}

void MB2Ev_Branch6RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB2Ev_Branch6();
    }
}

void MB2Ev_Branch7(void) {
    MB2Ev_BranchMain(mb2ev_branch7Masu, mb2ev_branch7Link, mb2ev_branch7ComTree);
}

void MB2Ev_Branch7RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB2Ev_Branch7();
    }
}

void MB2Ev_Branch8(void) {
    MB2Ev_BranchMain(mb2ev_branch8Masu, mb2ev_branch8Link, mb2ev_branch8ComTree);
}

void MB2Ev_Branch8RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB2Ev_Branch8();
    }
}

void MB2Ev_Branch9(void) {
    MB2Ev_BranchMain(mb2ev_branch9Masu, mb2ev_branch9Link, mb2ev_branch9ComTree);
}

void MB2Ev_Branch9RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB2Ev_Branch9();
    }
}

void MB2Ev_Branch10(void) {
    MB2Ev_BranchMain(mb2ev_branch10Masu, mb2ev_branch10Link, mb2ev_branch10ComTree);
}

void MB2Ev_Branch10Check(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if ((player->rev & 0x80) && mbWalkNum != 0 && MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67) {
        MB2Ev_Branch10();
    } else if ((player->rev & 0x80) && MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67) {
        MBMoveBackMasuSet(-1, 0, 0x10);
        MBMoveNextMasuSet(-1, 0, 0xE);
    } else if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x67) {
        MBMoveBackMasuSet(-1, 0, 0xE);
    }
}

void MB2Ev_Merge1(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x12) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void MB2Ev_Merge2(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x23) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void MB2Ev_Merge3(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x24) {
        MBMoveNextMasuSet(-1, 0, 5);
    }
}

void MB2Ev_Merge4(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void MB2Ev_Merge5(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void MB2Ev_Merge6(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x85) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void MB2Ev_Merge7(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x28) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void MB2Ev_Merge8(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xD) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void MB2Ev_Merge9(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2B) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void MB2Ev_Merge10(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x38) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void MB2Ev_Merge11(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x69) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void MB2Ev_Merge12(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5C) {
        MBMoveNextMasuSet(-1, 7, 0x12);
    }
}

void MB2Ev_Merge13(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x87) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void MB2Ev_Merge14(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x88) {
        MBMoveNextMasuSet(-1, 6, 5);
    }
}

void MB2Ev_Merge15(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x50) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void MB2Ev_Merge16(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x56) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void MB2Ev_Merge17(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void MB2Ev_Merge18(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xC) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

s32 MB2Ev_KeyManChoiceGet(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb2_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1;
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
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void MB2Ev_KeyManMasu(void) {
    GW_SYSTEM *loc;
    GW_PLAYER *player;
    s32 flag;
    s32 choice;
    void *prc;
    s16 sp18;
    s16 masuId;

    loc = &GwSystem;
    player = MBPlayerGet(GwSystem.current_player_index);
    flag = 1;

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6A) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x6B) {
            if (MBItemFind(GwSystem.current_player_index, 1) != -1) {
                MBSaiNumKill(GwSystem.current_player_index);
                MBPlayerMotionSet(-1, -1, 2);
                sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (sp18) {
                    case 0x85:
                    case 0x86:
                        MBPlayerRotMasuStart(-1, 8, 0x6A);
                        break;
                    default:
                        MBPlayerRotMasuStart(-1, 8, 0x6B);
                        break;
                }
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
                HuPrcChildWatch();
                MBPlayerVibrate(-1, 1);

                while (1) {
                    MBDlgWinCreate(0x38, 0x4103);
                    choice = MB2Ev_KeyManChoiceGet(0);
                    MBDlgWinClose();
                    MBDlgWinKill();

                    switch (choice) {
                        case 0:
                            MBDlgWinExec(0x38, 0x4104);
                            GwPlayer[loc->current_player_index].itemNo[MBItemFind(loc->current_player_index, 1)] = -1;
                            MBItemRemoveEmpty(GwSystem.current_player_index);
                            MBStatusItemIconSprReinit(-1);
                            sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                            switch (sp18) {
                                case 0x85:
                                    MB2_GateOpen(0, 0);
                                    break;
                                case 0x86:
                                    MB2_GateOpen(0, 1);
                                    break;
                                case 0x87:
                                    MB2_GateOpen(1, 0);
                                    break;
                                default:
                                    MB2_GateOpen(1, 1);
                                    break;
                            }
                            flag = 0;
                            prc = MBPlayerVibrateObjCreate(-1, 2, 5);
                            HuPrcSleep(0x14);
                            MBPlayerVibrateObjKill(prc);
                            break;
                        case 1:
                            MBDlgWinExec(0x38, 0x4105);
                            break;
                        case 2:
                            MB2_MapScroll();
                            continue;
                        default:
                            break;
                    }
                    break;
                }

                MBSaiNumShow(loc->current_player_index);
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                HuPrcChildWatch();
            } else {
                MBDlgWinExec(-1, 0x4106);
            }
        }
    }

    if (flag != 0) {
        masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        switch (masuId) {
            case 0x85:
                MBMoveNextMasuSet(-1, 3, 0);
                player->rev |= 1;
                break;
            case 0x86:
                MBMoveNextMasuSet(-1, 3, 4);
                player->rev &= ~1;
                break;
            case 0x87:
                MBMoveNextMasuSet(-1, 9, 0);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 9, 4);
                player->rev &= ~1;
                break;
        }
    }

    omDelPrcObj(NULL);
}

void MB2Ev_BankMasuBranch(void) {
}

void MB2Ev_StarMasuBranch(void) {
}

void MB2Ev_TeresaMasuBranch(void) {
}

s32 MB2Ev_YesNoChoiceGet(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb2_padBitTbl;

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

void MB2Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void MB2Ev_ItemSelAttrProc(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
    }
}

void MB2Ev_StarMasu(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = MB2Ev_StarCheck(spaceIdx);
    if (spaceIdx == 1) {
        MBSaiNumKill(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        MBPlayerRotMasuStart(-1, 8, MB2Ev_StarGuideMasuGet());
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
                choice = MB2Ev_YesNoChoiceGet(2, 0);
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
                        MB2Ev_StarGetExec(mb2_starGuideBaseMdl);
                        HuPrcSleep(30);
                        MBBoardRestartSet();
                        MBExitReq(2);
                        MB2Ev_StarMasuBranch();
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
                        MB2Ev_StarMasuBranch();
                        return;
                    case 2:
                        MB2_MapScroll();
                        goto purchaseMenu;
                    default:
                        MB2Ev_StarMasuBranch();
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

    MB2Ev_StarMasuBranch();
}

const char mb2ev_numFmtStr[] = "%d";

void MB2Ev_BankMasu(void) {
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
            MBPlayerRotMasuStart(-1, 8, 0x6E);
            spaceA = MBMasuGet(0x6E);
            spaceB = MBMasuGet(0x21);
            break;
        case 0x4B:
            MBPlayerRotMasuStart(-1, 8, 0x70);
            spaceA = MBMasuGet(0x70);
            spaceB = MBMasuGet(0x4B);
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

    effectModel = MBModelCreate(0x35, mb2ev_bankCoinPileMot);
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
        choice = MB2Ev_YesNoChoiceGet((s32)mb2ev_bankComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                MB2_MapScroll();
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
        sprintf(sp20, mb2ev_numFmtStr, GwSystem.bank_coins);
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
            MB2Ev_BankKoopaCardExec();
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
                sprintf(sp20, mb2ev_numFmtStr, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, mb2ev_numFmtStr, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                MB2_BankCoinHide();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                MBDlgWinOpen();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, mb2ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, mb2ev_numFmtStr, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                MB2_BankCoinHide();
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
                sprintf(sp20, mb2ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinMesWait();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                MB2_BankCoinHide();
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
    MB2Ev_BankMasuBranch();
}

s32 MB2Ev_ShopItemIdxGet(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb2ev_shopItemEnableTbl[i] != 0 && mb2ev_shopItemTbl[mb2ev_shopHostNo][mb2ev_shopItemRow][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 MB2Ev_ShopItemNumGet(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb2ev_shopItemTbl[mb2ev_shopHostNo][mb2ev_shopItemRow][i] == -1) {
            break;
        }
    }
    return i;
}

void MB2Ev_ShopBagBounceProc(void) {
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

void MB2Ev_ShopMasu(void) {
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
        case 0x73:
            camMasu = 0x6C;
            spaceA = MBMasuGet(0x6C);
            spaceB = MBMasuGet(0x73);
            mb2ev_shopNo = 0;
            break;
        case 0x69:
            camMasu = 0x6D;
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(0x69);
            mb2ev_shopNo = 1;
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
            effectModel = MBModelCreate(0x39, mb2ev_shopKoopaJrMot);
        } else {
            effectModel = MBModelCreate(0x1B, mb2ev_shopKinopioMot);
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
        MBDlgWinExec(dlgWin, mb2ev_shopLastTurnMesTbl[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, mb2ev_shopItemFullMesTbl[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, mb2ev_shopNoCoinMesTbl[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, mb2ev_shopEnterMesTbl[shopIdx]);
    choice = MB2_ComShopEnterChoice();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = MBTurnTierGet(-1);
            row = mb2ev_shopItemRowTbl[shopIdx][i][MBPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (mb2ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mb2ev_shopItemTbl[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (mb2ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mbItemPriceTbl[mb2ev_shopItemTbl[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, mb2ev_shopItemMesTbl[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            MBDlgWinTabWidthSet(0);
            mb2ev_shopHostNo = slot;
            mb2ev_shopItemRow = row;
            mb2ev_shopItemEnableTbl = enabled;
            sel = MB2_ComShopItemChoice(enabled);
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
            shopTable = mb2ev_shopItemTbl;
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
                    mb2ev_shopItemTbl[shopIdx][row][sel];
                item = mb2ev_shopItemTbl[shopIdx][row][sel];
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

            if (mb2ev_shopItemTbl[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = mb2ev_shopBagRowTbl[shopIdx][MBTurnTierGet(-1)]
                                         [MBPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < mb2ev_shopBagRateTbl[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = mb2ev_shopBagItemTbl[shopIdx][i];

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
                    prc = omAddPrcObj(MB2Ev_ShopBagBounceProc, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, mb2ev_shopCancelMesTbl[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                MB2_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB2_MapScroll();
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

void MB2Ev_TeresaFadeIn(Object *obj) {
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

void MB2Ev_TeresaFadeOut(Object *obj) {
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

s32 MB2Ev_TeresaStarSteal(s32 playerIndex) {
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
    HuSprPosSet(grp, 0, mb2ev_teresaSprPosTbl[playerIndex].x,
                mb2ev_teresaSprPosTbl[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        HuSprPosSet(grp, 0,
                    (i * mb2ev_teresaSprDirTbl[playerIndex].x) +
                        mb2ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                        mb2ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(MB2Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                    (mb2ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].x,
                    (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].y +
                        (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        HuSprPosSet(grp, 0,
                    (i * mb2ev_teresaSprDirTbl[playerIndex].x) +
                        mb2ev_teresaSprPosTbl[playerIndex].x,
                    (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                        mb2ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    return !hasRareItem;
}

void MB2Ev_TeresaWinCloseProc(void) {
    MBWinClose();
    omDelPrcObj(NULL);
}

s32 MB2Ev_TeresaSteal(s32 playerIndex) {
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
    HuSprPosSet(grp, 0, mb2ev_teresaSprPosTbl[playerIndex].x,
                mb2ev_teresaSprPosTbl[playerIndex].y);
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
                    mb2ev_teresaSprPosTbl[playerIndex].x -
                        (mb2ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    mb2ev_teresaSprPosTbl[playerIndex].y +
                        (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f));
        HuSprTPLvlSet(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            HuSprPosSet(grp, 0,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].x) +
                            mb2ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                            mb2ev_teresaSprPosTbl[playerIndex].y);
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
            omAddPrcObj(MB2Ev_TeresaWinCloseProc, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(MB2Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                    (mb2ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].x,
                    (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                HuSprPosSet(
                    grp, 0,
                    (mb2ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].y);
                HuSprPosSet(
                    playerGrp, 0,
                    mb2ev_teresaSprPosTbl[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].y);
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
                            playerGrp, 0, mb2ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                            (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                                mb2ev_teresaSprPosTbl[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                HuSprBankSet(playerGrp, 0, 0, 0);
                HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
                playerSpriteVisible = 0;
                HuSprPosSet(
                    playerGrp, 0,
                    mb2ev_teresaSprPosTbl[playerIndex].x -
                        (mb2ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    (mb2ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb2ev_teresaSprPosTbl[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(MB2Ev_TeresaWinCloseProc, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].x) +
                            mb2ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                            mb2ev_teresaSprPosTbl[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].x) +
                            mb2ev_teresaSprPosTbl[playerIndex].x,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                            mb2ev_teresaSprPosTbl[playerIndex].y);
            HuSprPosSet(playerGrp, 0,
                        ((i - 0x10) * mb2ev_teresaSprDirTbl[playerIndex].x) +
                            mb2ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                        (i * mb2ev_teresaSprDirTbl[playerIndex].y) +
                            mb2ev_teresaSprPosTbl[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(mb2ev_teresaCoinTurnTbl); i++) {
            if ((GwSystem.current_turn >= mb2ev_teresaCoinTurnTbl[i][0]) &&
                (GwSystem.current_turn <= mb2ev_teresaCoinTurnTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible = mb2ev_teresaCoinTurnTbl[i][2];
        for (i = 0; i < ARRAY_COUNTU(mb2ev_teresaCoinPenaltyTbl); i++) {
            if ((attempts >= mb2ev_teresaCoinPenaltyTbl[i][0]) &&
                (attempts <= mb2ev_teresaCoinPenaltyTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= mb2ev_teresaCoinPenaltyTbl[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void MB2Ev_TeresaCoin(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb2ev_teresaCoinMdl);
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

void MB2Ev_TeresaCoinCreate(s32 arg) {
    Process *prc = omAddPrcObj(MB2Ev_TeresaCoin, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void MB2Ev_Teresa(void) {
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
    if (spaceId != 0x79) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(mb2_teresaGuideBaseMdl);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x66;
        space = MBMasuGet(0x66);
        boo = mb2_teresaGuideMdl[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
            if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    MB2Ev_TeresaFadeIn(boo);
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
    menuResult = MB2_ComTeresaTypeChoice(choices);
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
    playerChoice = MB2_ComTeresaPlayerChoice(choices);
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
                MB2_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB2_MapScroll();
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
            if (rank < mb2ev_teresaComTargetRateTbl[i]) {
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
            if (GwSystem.current_turn >= mb2ev_teresaCoinTurnTbl[i][0] &&
                GwSystem.current_turn <= mb2ev_teresaCoinTurnTbl[i][1]) {
                break;
            }
        }
        estimatedAmount = mb2ev_teresaCoinTurnTbl[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    MB2Ev_TeresaFadeOut(boo);
    if (menu == 0) {
        resultAmount = MB2Ev_TeresaSteal(target);
        MB2Ev_TeresaFadeIn(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], mb2ev_numFmtStr, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], mb2ev_numFmtStr, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= mb2ev_teresaCoinDiffTbl[i]) {
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
            mb2ev_teresaCoinMdl = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(mb2ev_teresaCoinMdl);
            MBModelDispOff(mb2ev_teresaCoinMdl);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    MB2Ev_TeresaCoinCreate((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(mb2ev_teresaCoinMdl);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = MB2Ev_TeresaStarSteal(target);
        MB2Ev_TeresaFadeIn(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            mb2ev_starGetTeresaF = 1;
            MB2Ev_StarGetExec(boo);
            mb2ev_starGetTeresaF = 0;
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
    MB2Ev_TeresaFadeOut(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        MB2_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
    } else {
        MB2_MapScroll();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        MB2Ev_TeresaFadeOut(boo);
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
            if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb2ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
    MB2Ev_TeresaMasuBranch();
}

void MB2Ev_Gate1Close(void) {
    MB2_GateClose(0);
}

void MB2Ev_Gate2Close(void) {
    MB2_GateClose(1);
}

omObjData *MB2Ev_ItemLampSmokeCreate(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, MB2Ev_ItemLampSmokeObjMain);
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

void MB2Ev_ItemLampSmokeObjMain(omObjData *arg0) {
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

void MB2Ev_ItemMajinLamp(void) {
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
    MB2Ev_ItemUseFadeOut();
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
            MB2Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    MBMasuLinkIdxGet(
        mb2ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
            MB2Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            msmMusPause(0);
        }
    }
}

void MB2Ev_ItemMajinLampStar(void) {
    s16 ret;

    mbStarMusF = 1;
    MBMasuEventCall(mb2ev_starMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    mbStarMusF = 0;
    ret = MBExitFlagGet();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void MB2Ev_ItemWarpBlock(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MB2Ev_ItemUseFadeOut();
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

void MB2Ev_ItemMove(void) {
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

Process *MB2Ev_ItemMoveCreate(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                           s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(MB2Ev_ItemMove, 0x4002, 0, 0x40);
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

void MB2Ev_ItemKinoko(void) {
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
    HuPrcChildLink(process, MB2Ev_ItemMoveCreate(
                                mbItemCursorGrpId, position[0], position[1],
                                mb2ev_itemUsePosTbl[system->current_player_index].x,
                                mb2ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB2Ev_ItemUseFadeOut(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    MB2Ev_ItemMoveCreate(
        mbItemCursorGrpId, position[0], position[1],
        mb2ev_itemFadePosTbl[system->current_player_index].x,
        mb2ev_itemFadePosTbl[system->current_player_index].y, -1);
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

void MB2Ev_ItemCursorReturn(void) {
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
                   MB2Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     targetX, targetY, -1));
    HuPrcChildWatch();

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB2Ev_ItemShake(void) {
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
                   MB2Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb2ev_itemUsePosTbl[system->current_player_index].x,
                                     mb2ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB2Ev_ItemPhoneMove(void) {
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
                   MB2Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb2ev_itemUsePosTbl[system->current_player_index].x,
                                     mb2ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB2Ev_ItemIconMove(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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

void MB2Ev_KSuitStart(void) {
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

void MB2Ev_KSuitEnd(void) {
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

void MB2Ev_ItemPhoneWaveProc(void) {
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
    HuSprGrpMemberSet(group, 0, mb2ev_itemPhoneWaveSpr, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, HUSPR_ATTR_XLU);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    HuSprPosSet(group, 0, x, y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)mb2ev_itemPhoneWaveAngleTbl[index];
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

void MB2Ev_ItemShopPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb2ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB2Ev_ItemPhoneMove();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = MB2Ev_YesNoChoiceGet((s32)mb2ev_shopPhoneComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(MB2Ev_ItemSelAttrProc, 0, 0, 0);
                omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
                MB2_MapScrollCancel();
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

        process = omAddPrcObj(MB2Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
        MB2_MapScrollCancel();
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
            process = omAddPrcObj(MB2Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB2Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb2ev_itemPhoneWaveSpr);
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
    MB2Ev_ShopMasu();
    GwSystem.forceShopHost = 0;
}

void MB2Ev_ItemKoopaPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 i;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb2ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB2Ev_ItemPhoneMove();

    HuPrcSleep(30);
    HuAudFXPlay(0x147);
    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB2Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        process->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), process);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    for (i = 0; i < 5; i++) {
        process = omAddPrcObj(MB2Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
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
        choice = MB2Ev_YesNoChoiceGet(1, 0);
    } else {
        choice = MB2Ev_YesNoChoiceGet(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = MBPlayerRankRandGet(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(MB2Ev_ItemSelAttrProc, 0, 0, 0);
            omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
            MB2_MapScrollCancel();
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
    HuSprAnimKill(mb2ev_itemPhoneWaveSpr);

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

void MB2Ev_ItemStarYoke(void) {
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
        MB2Ev_ItemUseFadeOut();

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
            MB2Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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
            MB2Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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

        space = MBMasuGet(mb2ev_starMasu[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(mb2ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
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
        if (mb2_starGuideHoverProc[j] != NULL) {
            omDelPrcObj(mb2_starGuideHoverProc[j]);
            mb2_starGuideHoverProc[j] = NULL;
        }
    }

    targetStar = mb2_starGuideMdl[system->star_spawn_indices[system->current_star_spawn]];
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

void MB2Ev_ItemKeyManUse(void) {
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
                   MB2Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                     mb2ev_itemUsePosTbl[system->current_player_index].x,
                                     mb2ev_itemUsePosTbl[system->current_player_index].y, -1));
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
    result = MB2Ev_YesNoChoiceGet((s32)&mb2ev_keyManUseComTree, 0);
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
            MB2_MapScrollCancel();
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

void MB2Ev_TereYokeSparkProc(void) {
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
    HuSprGrpMemberSet(setupGroup, 0, mb2ev_tereYokeSparkSpr, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, HUSPR_ATTR_XLU);
    MBStatusItemPosGet(mb2ev_tereYokePlayer, 0, &xPos, &yPos);

    xPos = (s32)((mb2ev_teresaSprDirTbl[mb2ev_tereYokePlayer].x * 16.0f) +
                 mb2ev_teresaSprPosTbl[mb2ev_tereYokePlayer].x);
    yPos = (s32)((mb2ev_teresaSprDirTbl[mb2ev_tereYokePlayer].y * 16.0f) +
                 mb2ev_teresaSprPosTbl[mb2ev_tereYokePlayer].y);
    HuSprPosSet(
        setupGroup, 0, (f32)xPos + mb2ev_tereYokeSparkOfsTbl[playerIndex].x,
        (f32)yPos + mb2ev_tereYokeSparkOfsTbl[playerIndex].y);
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

void MB2Ev_TereYokeSprayProc(void) {
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
    mb2ev_tereYokeSparkSpr = HuSprAnimRead(data);
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
    mb2ev_tereYokePlayer = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(MB2Ev_TereYokeSparkProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb2ev_tereYokeSparkSpr);
    HuSprAnimKill(auraSpriteId);
    HuSprAnimKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void MB2Ev_ItemNullUse(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void MB2Ev_KoopaCardCoinProc(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb2ev_koopaCardCoinMdl);
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

void MB2Ev_KoopaCardCoinCreate(Object *arg) {
    Process *temp = omAddPrcObj(MB2Ev_KoopaCardCoinProc, 0x1000, 0, 0);

    temp->user_data = arg;
}

void MB2Ev_KoopaCardSpinProc(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        mb2ev_koopaCardMdl->rot.x = -sindf(angle);
        mb2ev_koopaCardMdl->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            mb2ev_koopaCardMdl->scale.z = scale;
            mb2ev_koopaCardMdl->scale.y = scale;
            mb2ev_koopaCardMdl->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    mb2ev_koopaCardMdl->scale.x = mb2ev_koopaCardMdl->scale.y = mb2ev_koopaCardMdl->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(mb2ev_koopaCardMdl);
    omDelPrcObj(0);
}

void MB2Ev_BankKoopaCardExec(void) {
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
    MB2Ev_ItemUseFadeOut();

    mb2ev_koopaCardMdl = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&mb2ev_koopaCardMdl->coords, &MBPlayerGet(-1)->player_obj->coords);
    mb2ev_koopaCardMdl->velocity.x = 100.0f;
    while (30.0f < mb2ev_koopaCardMdl->velocity.x) {
        mb2ev_koopaCardMdl->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(MB2Ev_KoopaCardSpinProc, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    mb2ev_koopaCardCoinMdl = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(mb2ev_koopaCardCoinMdl);
    MBModelDispOff(mb2ev_koopaCardCoinMdl);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                MB2Ev_KoopaCardCoinCreate(mb2ev_koopaCardMdl);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                MB2_BankCoinHide();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(mb2ev_koopaCardCoinMdl);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 MB2_ComItemTargetChoice(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)mb2_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = mb2_comExchangeBoxTarget + 1;
                } else {
                    delay = mb2_comRobBoxTarget + 1;
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

void MB2Ev_ExchangeItemFadeOutProc(void) {
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

void MB2Ev_ExchangeItemFadeInProc(void) {
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

void MB2Ev_ItemExchangeBox(void) {
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

    MB2Ev_ItemUseFadeOut();
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
    targetPlayer = MB2_ComItemTargetChoice(choices, 1);
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
                    MB2Ev_ItemIconMove(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(MB2Ev_ExchangeItemFadeOutProc, 0x4800, 0, 0);
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
        process = omAddPrcObj(MB2Ev_ExchangeItemFadeInProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB2Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB2Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB2Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                MB2Ev_ItemIconMove(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB2Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB2Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                MB2Ev_ItemIconMove(targetPlayer, 2, 7, &target.x, 2);
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

void MB2Ev_GambleCoinEffProc(void) {
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

void MB2Ev_GambleCoinProc(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = mb2ev_gambleCoinMdl;
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
        if (mb2ev_gambleCoinPlayer != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(mb2ev_gambleCoinPlayer)->player_obj->coords);
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
    process = omAddPrcObj(MB2Ev_GambleCoinEffProc, 0x4800, 0, 0x40);
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

void MB2Ev_ItemGambleCoin(void) {
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
    MB2Ev_ItemUseFadeOut();
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
    mb2ev_gambleCoinMdl = gameGuyModel;
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
    choice = MB2Ev_YesNoChoiceGet(0, 0);
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
    MB2_MapScrollCancel();
    winPauseF = 1;
    omAllPause();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(MB2Ev_GambleCoinProc, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        mb2ev_gambleCoinPlayer = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        mb2ev_gambleCoinPlayer = choice;
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
        MB2Ev_WinPlayerKeyExec(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        MB2Ev_WinPlayerKeyExec(10, 0x2F02, -1, choice);
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
        MB2Ev_WinPlayerKeyExec(10, 0x2F01, -1, choice);
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
            if (randomValue <= mb2ev_gambleRateTbl[rewardIndex].threshold) {
                break;
            }
        }
        if (mb2ev_gambleRateTbl[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * mb2ev_gambleRateTbl[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, mb2ev_numFmtStr, rewardAmount);
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
        if (randomValue < mb2ev_gambleMgRateTbl[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = mb2ev_gambleMgTbl[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    MBGameModeMgSet();
    omAllUPause();
    MBExitReq(2);
    HuPrcSleep(-1);
}

void MB2Ev_After5ItemMove(s32 arg0, s32 arg1, f32 *arg2) {
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

void MB2Ev_After5LineShow(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            HuSprPosSet(mb2ev_after5GrpId[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(mb2ev_after5GrpId[idx], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(mb2ev_after5GrpId[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprDispOn(mb2ev_after5GrpId[idx], 0);
    for (i = 0; i < 255; i += 255 / divisor) {
        HuSprTPLvlSet(mb2ev_after5GrpId[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mb2ev_after5GrpId[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void MB2Ev_After5NumFade(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = mb2ev_after5NumColorTbl[i].r;
        sp18.g = mb2ev_after5NumColorTbl[i].g;
        sp18.b = mb2ev_after5NumColorTbl[i].b;

        sp28.r = (mb2ev_after5NumColorTbl[i + 1].r - sp18.r) / 30;
        sp28.g = (mb2ev_after5NumColorTbl[i + 1].g - sp18.g) / 30;
        sp28.b = (mb2ev_after5NumColorTbl[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(mb2ev_after5GrpId[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(mb2ev_after5GrpId[3], 0, mb2ev_after5NumColorTbl[i + 1].r, mb2ev_after5NumColorTbl[i + 1].g, mb2ev_after5NumColorTbl[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void MB2Ev_After5Effect(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = mb2ev_after5EffMdl;
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

void MB2Ev_ItemAfter5(void) {
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
        mb2ev_after5GrpId[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(mb2ev_after5GrpId[i], 0, sp18[i], 0);
        HuSprPriSet(mb2ev_after5GrpId[i], 0, 0x4780U);
        HuSprAttrSet(mb2ev_after5GrpId[i], 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
        HuSprTPLvlSet(mb2ev_after5GrpId[i], 0, 0U);
        HuSprColorSet(mb2ev_after5GrpId[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    mb2ev_after5EffMdl = temp_v0_3;
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
    MB2Ev_After5ItemMove(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    MB2Ev_After5ItemMove(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(MB2Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    MB2Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(MB2Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    MB2Ev_After5ItemMove(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(MB2Ev_After5LineShow, 0x4002U, 0, 0);
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
        HuSprDispOff(mb2ev_after5GrpId[i], 0);
    }

    HuSprDispOn(mb2ev_after5GrpId[3], 0);
    HuSprTPLvlSet(mb2ev_after5GrpId[3], 0, 0xFFU);
    HuSprPosSet(mb2ev_after5GrpId[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB2Ev_After5NumFade, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(MB2Ev_After5Effect, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(mb2ev_after5GrpId[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(mb2ev_after5GrpId[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(mb2ev_after5GrpId[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(WIPE_FADE, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void MB2Ev_BranchMain(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees) {
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
    MB2_BranchHelpStart();
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
    MB2_BranchHelpEnd();

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

void MB2Ev_KinokoMarkKill(s32 arg0) {
    {
        omObjData *obj = mb2ev_kinokoMarkObj[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            mb2ev_kinokoMarkObj[arg0] = NULL;
        }
    }

    {
        Object *model = mb2ev_kinokoMarkMdl[arg0];

        if (model != NULL) {
            MBModelKill(model);
            mb2ev_kinokoMarkMdl[arg0] = NULL;
        }
    }
}

void MB2Ev_KinokoMarkObjKillAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = mb2ev_kinokoMarkObj[i];

        if (obj != NULL) {
            omDelObj(obj);
            mb2ev_kinokoMarkObj[i] = NULL;
        }
    }
}

void MB2Ev_KinokoMarkObjMain(omObjData *obj) {
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
        Object *effectObj = mb2ev_kinokoMarkMdl[playerIdx];

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

void MB2Ev_KinokoMarkCreate(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (mb2ev_kinokoMarkMdl[playerNo] == NULL) {
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
        mb2ev_kinokoMarkMdl[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        MBModelDispFlagSet(mb2ev_kinokoMarkMdl[playerNo]);
    }
}

void MB2Ev_KinokoMarkObjCreate(s32 arg) {
    mb2ev_kinokoMarkObj[arg] = omAddObj(0x3FFF, 0, 0, -1, MB2Ev_KinokoMarkObjMain);
    mb2ev_kinokoMarkObj[arg]->work[0] = arg;
    mb2ev_kinokoMarkObj[arg]->work[1] = 0;
    mb2ev_kinokoMarkObj[arg]->work[2] = 0;
    mb2ev_kinokoMarkObj[arg]->rot.x = (f32)MBRand(360.0f);
    mb2ev_kinokoMarkObj[arg]->trans.x = 0;
}

void MB2Ev_KinokoMarkCreateAll(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        mb2ev_kinokoMarkObj[i] = NULL;
        mb2ev_kinokoMarkMdl[i] = NULL;
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
            MB2Ev_KinokoMarkCreate(i, idx);
            MB2Ev_KinokoMarkObjCreate(i);
        }
    }
    MBExitHookSet(MB2Ev_KinokoMarkObjKillAll);
}

void MB2Ev_NKinokoTurnStart(void) {
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
            if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB2Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB2Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void MB2Ev_ItemKoopaNKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        MBSaiKill(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB2Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB2Ev_KinokoVibrateProc(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

void MB2Ev_ItemNKinoko(void) {
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
    choice = MB2Ev_YesNoChoiceGet(2, mb2_comNKinokoTarget);
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

    MB2Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    MB2Ev_KinokoMarkCreate(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    MB2Ev_KinokoMarkObjCreate(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(MB2Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        MB2Ev_KinokoMarkKill(loc->current_player_index);
        MBSaiKill(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void MB2Ev_RKinokoTurnStart(void) {
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
            if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB2Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB2Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void MB2Ev_ItemKoopaRKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        MBSaiKill(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (mb2ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB2Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB2Ev_ItemRKinoko(void) {
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
    choice = MB2Ev_YesNoChoiceGet(2, mb2_comRKinokoTarget);
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

    MB2Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    MB2Ev_KinokoMarkCreate(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb2ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    MB2Ev_KinokoMarkObjCreate(targetPlayer);
    omAddPrcObj(MB2Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
        MB2Ev_RKinokoTurnStart();
    }
}

void MB2Ev_ItemRobBox(void) {
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

    MB2Ev_ItemUseFadeOut();
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
    targetPlayer = MB2_ComItemTargetChoice(choices, 0);
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
                       mb2ev_robBoxItemStartPosTbl[system->current_player_index].x,
                       mb2ev_robBoxItemStartPosTbl[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB2Ev_ItemMoveCreate(-1,
                                     mb2ev_robBoxItemStartPosTbl[system->current_player_index].x,
                                     mb2ev_robBoxItemStartPosTbl[system->current_player_index].y,
                                     mb2ev_robBoxItemEndPosTbl[system->current_player_index].x,
                                     mb2ev_robBoxItemEndPosTbl[system->current_player_index].y, 5));
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
    MB2Ev_ItemCursorReturn();
}

s32 MB2Ev_ShortcutGuessChoice(void) {
    s32 curPlayer = MBPlayerTurnGet();
    s32 files[] = { 0x1301E1, 0x1301E2, 0x1301E3, 0x1301E4, 0x1301E5 };
    Vec2f pos[] = {
        { 160.0f, 120.0f },
        { -68.0f, -8.0f },
        { -23.0f, -8.0f },
        { 23.0f, -8.0f },
        { 68.0f, -8.0f },
    };
    UnkBoard8 *sprites;
    UnkBoard8 *cursor;
    void *data;
    Unk3 *helpWin1;
    Unk3 *helpWin2;
    s32 timer;
    s32 prev;
    s32 sel;
    s32 i;

    sprites = MBSprGrpCreate(5, 2);
    for (i = 0; i < 5; i++) {
        data = DataRead(files[i]);
        sprites->model[i] = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(sprites->spriteGroup, i, sprites->model[i], 0);
        HuSprAttrReset(sprites->spriteGroup, i, 0xFFFF);
        HuSprAttrSet(sprites->spriteGroup, i, HUSPR_ATTR_NONE);
        HuSprPriSet(sprites->spriteGroup, i, 0x1000);
        HuSprPosSet(sprites->spriteGroup, i, pos[i].x, pos[i].y);
    }
    for (i = 1; i < 5; i++) {
        if ((GwSystem.boardData.halfWordBytes[0] >> (i - 1)) & 1) {
            HuSprDispOff(sprites->spriteGroup, i);
        }
    }

    cursor = MBSprGrpCreate(1, 2);
    data = DataRead(0x1301E6);
    cursor->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(cursor->spriteGroup, 0, cursor->model[0], 0);
    HuSprAttrReset(cursor->spriteGroup, 0, 0xFFFF);
    HuSprAttrSet(cursor->spriteGroup, 0, HUSPR_ATTR_NONE);
    HuSprPriSet(cursor->spriteGroup, 0, 0xFFF);
    for (i = 0; i < 4; i++) {
        if (!((GwSystem.boardData.halfWordBytes[0] >> i) & 1)) {
            break;
        }
    }
    sel = i;
    HuSprPosSet(cursor->spriteGroup, 0, pos[0].x + pos[sel + 1].x, pos[0].y + pos[sel + 1].y - 36.0f);
    helpWin1 = MBHelpWinCreate(0, 0xB4, 1);
    helpWin2 = MBHelpWinCreate(1, 0xC2, 1);

    timer = 10;
    while (TRUE) {
        prev = sel;
        HuPrcVSleep();
        if (MBPlayerComCheck(-1)) {
            if (--timer == 0) {
                goto decide;
            }
            if (timer % 3 != 0) {
                continue;
            }
            if (MBRand(5.0f) == 0) {
                goto moveLeft;
            }
            if (MBRand(5.0f) == 0) {
                goto moveRight;
            }
            continue;
        }
        if (ContBtnDown[GwPlayer[curPlayer].pad] & A_BUTTON) {
        decide:
            HuAudFXPlay(0x18E);
            break;
        }
        if (ContBtnDown[GwPlayer[curPlayer].pad] & L_JPAD) {
        moveLeft:
            do {
                sel--;
                if (sel < 0) {
                    sel = 3;
                }
            } while ((GwSystem.boardData.halfWordBytes[0] >> sel) & 1);
        }
        if (ContBtnDown[GwPlayer[curPlayer].pad] & R_JPAD) {
        moveRight:
            do {
                sel++;
                if (sel >= 4) {
                    sel = 0;
                }
            } while ((GwSystem.boardData.halfWordBytes[0] >> sel) & 1);
        }
        if (prev != sel) {
            HuSprPosSet(cursor->spriteGroup, 0, pos[0].x + pos[sel + 1].x,
                        pos[0].y + pos[sel + 1].y - 36.0f);
        }
    }
    GwSystem.boardData.halfWordBytes[0] |= 1 << sel;
    MB2_ShortcutMarkDispSet();
    HuSprPosSet(cursor->spriteGroup, 0, pos[0].x + pos[sel + 1].x, pos[0].y + pos[sel + 1].y - 16.0f);
    HuSprDispOff(sprites->spriteGroup, sel + 1);
    HuPrcSleep(20);
    MBHelpWinKill(helpWin1);
    MBHelpWinKill(helpWin2);
    MBSprGrpKill(sprites);
    MBSprGrpKill(cursor);
    return sel;
}

void MB2Ev_Shortcut(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masuId = MBMasuLinkMasuIdGet(player->blink, player->bidx);
    GW_SYSTEM *system = &GwSystem;
    Vec pos;
    Vec dir;
    s16 masuIds[2] = { 0x82, 0x83 };
    UnkEA790Struct *win;
    Object *model;
    SpaceData *space;
    SpaceData *start;
    SpaceData *dest;
    Object *obj;
    u32 *motion;
    s32 isOther;
    s32 sel;
    f32 scale;
    s32 i;
    s32 j;

    switch (masuId) {
        case 0x0A:
        case 0x57:
            MB2Ev_BranchMain(mb2ev_shortcutBranchMasu, mb2ev_shortcutBranchLink, mb2ev_shortcutBranchComTree);
            isOther = MBMasuLinkMasuIdGet(player->nlink, player->nidx) != 0x2A;
            MBSaiNumKill(system->current_player_index);
            MBPlayerMotionSet(-1, -1, 2);
            MBPlayerRotMasuStart(-1, 5, 0x77);
            MBDlgWinExec(0x3B, 0x600);
            if (MB2Ev_ShortcutGuessChoice() == GwSystem.boardData.halfWordBytes[1]) {
                MBPlayerMotionLoad(system->current_player_index, 5, 0x1A);
                MBPlayerMotionLoad(system->current_player_index, 6, 0xF);
                if (GwPlayer[system->current_player_index].itemTurn == 0) {
                    HuPrcVSleep();
                    for (i = 1; i < 8; i++) {
                        for (j = 0; j < mb2ev_shortcutMotMario[0]; j++) {
                            mb2ev_shortcutMotTbl[i][j + 1] = CharMotionDataNumGet(i, mb2ev_shortcutMotMario[j + 1]);
                        }
                    }
                    model = MBModelCreate(mb2ev_shortcutChrMdlTbl[GwPlayer[system->current_player_index].chr],
                                          mb2ev_shortcutMotTbl[GwPlayer[system->current_player_index].chr]);
                    MBModelTempAllocFree(model);
                    model->flags |= 1;
                    MBMotionSet(model, 0, 2);
                    Hu3DMotionSpeedSet(model->omObj1->model[0], 0.5f);
                    MBModelDispOff(model);
                } else {
                    model = player->player_obj;
                }

                space = MBMasuGet(masuIds[isOther]);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords,
                                                                        &player->player_obj->coords, 20));
                MBPlayerMotionSet(-1, 0, 2);
                Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 0.5f);
                MBVecDirGet(&player->player_obj->coords, &space->coords, &player->player_obj->rot);
                HuPrcChildWatch();
                HuAudFXPlay(0x18F);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&mb2_shortcutMdl->coords, &space->coords,
                                                                        &mb2_shortcutMdl->coords, 10));
                HuPrcSleep(2);
                MBVecDirGet(&player->player_obj->coords, &mb2_shortcutMdl->coords, &dir);
                MBVecRotLerpCreate(&player->player_obj->rot, &dir, &player->player_obj->rot, 5);
                HuPrcSleep(6);
                MBModelDispOff(mb2_shortcutMdl);
                HuAudFXPlay(0x190);
                obj = MBModelFileCreate(0xB0013, -1, 10.0f, 0.0f, NULL);
                Hu3DModelLayerSet(obj->omObj1->model[0], 0);
                Hu3DModelAttrSet(obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
                Hu3DModelRemakeStatic(obj->omObj1->model[0]);
                Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 0);
                Hu3DMotionSpeedSet(obj->omObj1->model[0], 0.5f);
                HuVecCopy3F(&obj->coords, &player->player_obj->coords);
                start = MBMasuGet(masuIds[isOther]);
                dest = MBMasuGet(masuIds[isOther ^ 1]);
                HuVecCopy3F(&pos, &player->player_obj->coords);
                MBCameraFocusModeSet(4);
                MBCameraFocusVecSet(&pos);
                MBPlayerPosMoveCreate(&pos, &dest->coords, &pos, 60);
                MBPlayerVibrate(-1, 4);
                MBVecForwardSet(&player->player_obj->rot);
                MBPlayerMotionSet(GwSystem.current_player_index, 5, 2);
                Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 0.5f);
                player->player_obj->flags |= 1;
                HuVecSubtract(&dir, &dest->coords, &start->coords);
                player->stat |= 4;
                mbItemBtnF = 0;
                PlayerFXPlay(0x286, system->current_player_index);
                if (GwPlayer[system->current_player_index].itemTurn == 0) {
                    MBModelDispOff(player->player_obj);
                    HuVecCopy3F(&model->coords, &player->player_obj->coords);
                    HuVecCopy3F(&model->rot, &player->player_obj->rot);
                    MBModelDispOn(model);
                } else {
                    model = player->player_obj;
                }

                for (i = 0; i < 181; i += 3) {
                    player->player_obj->velocity.x = sindf(i) * 100.0f;
                    model->velocity.x = sindf(i) * 100.0f;
                    if (i < 90) {
                        player->player_obj->coords.z = sindf(i) * 100.0f + start->coords.z + i * dir.z / 90.0f;
                        player->player_obj->coords.x = sindf(i) * 10.0f + start->coords.x + i * dir.x / 90.0f;
                        model->coords.z = sindf(i) * 100.0f + start->coords.z + i * dir.z / 90.0f;
                        model->coords.x = sindf(i) * 10.0f + start->coords.x + i * dir.x / 90.0f;
                    } else {
                        player->player_obj->coords.z = sindf(i) * 100.0f + dest->coords.z;
                        player->player_obj->coords.x = sindf(i) * 10.0f + dest->coords.x;
                        model->coords.z = sindf(i) * 100.0f + dest->coords.z;
                        model->coords.x = sindf(i) * 10.0f + dest->coords.x;
                    }
                    if (i < 90) {
                        scale = i / 40.0f + 1.0f;
                    } else {
                        scale = (180 - i) / 40.0f + 1.0f;
                    }
                    if (scale < 1.0f) {
                        scale = 1.0f;
                    }
                    HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
                    HuVecCopyXYZ(&model->scale, scale, scale, scale);
                    HuPrcVSleep();
                }

                if (GwPlayer[system->current_player_index].itemTurn == 0) {
                    MBModelDispOn(player->player_obj);
                    MBModelKill(model);
                }
                mbItemBtnF = 1;
                player->stat &= ~4;
                player->player_obj->flags &= ~1;
                HuVecCopy3F(&player->player_obj->coords, &dest->coords);
                player->player_obj->velocity.x = 0.0f;
                MBCameraFocusModeSet(1);
                MBPlayerMotionSet(GwSystem.current_player_index, 4, 2);
                Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.0f);
                HuPrcSleep(20);
                HuVecCopy3F(&mb2_shortcutMdl->coords, &MBMasuGet(0x7B)->coords);
                MBModelDispOn(mb2_shortcutMdl);
                MBModelKill(obj);
                MBDlgResultWinExec(0x601);
                MBPlayerMotionSet(GwSystem.current_player_index, 6, 0);
                MBPlayerMotionWait(GwSystem.current_player_index);
                MBPlayerMotionSet(GwSystem.current_player_index, -1, 2);
                motion = mbPlayerMotTbl[0];
                for (i = 6; i != 0; i--) {
                    motion++;
                }
                MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
                motion = mbPlayerMotTbl[0];
                for (i = 7; i != 0; i--) {
                    motion++;
                }
                MBPlayerMotionLoad(system->current_player_index, 6, ((u16 *)motion)[1]);
                GwSystem.boardData.halfWordBytes[0] = 0;
                GwSystem.boardData.halfWordBytes[1] = MBRand(4.0f);
                MB2_ShortcutMarkDispSet();
                if (isOther == 0) {
                    MBMoveMasuSet(system->current_player_index, 0xD, 0);
                    MBMoveNextMasuSet(system->current_player_index, 4, 0);
                } else {
                    MBMoveMasuSet(system->current_player_index, 0xC, 0);
                    MBMoveNextMasuSet(system->current_player_index, 6, 0);
                }
            } else {
                HuPrcSleep(2);
                space = MBMasuGet(masuIds[isOther]);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &space->coords,
                                                                        &player->player_obj->coords, 20));
                MBPlayerMotionSet(-1, 0, 2);
                Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 0.5f);
                MBVecDirGet(&player->player_obj->coords, &space->coords, &player->player_obj->rot);
                HuPrcChildWatch();
                if (isOther == 0) {
                    MBMoveMasuSet(system->current_player_index, 0xC, 0);
                    MBMoveNextMasuSet(system->current_player_index, 6, 0);
                } else {
                    MBMoveMasuSet(system->current_player_index, 0xD, 0);
                    MBMoveNextMasuSet(system->current_player_index, 4, 0);
                }
                HuPrcSleep(5);
            }
            MBSaiNumShow(system->current_player_index);
            HuPrcSleep(10);
            break;
        case 0x0C:
        case 0x83:
            MBPlayerMotionSet(-1, -1, 2);
            MBPlayerRotMasuStart(-1, 8, 0x77);
            HuPrcSleep(8);
            MBDlgResultWinExec(0x602);
            MBPlayerMotionSet(-1, -1, 2);
            HuPrcVSleep();
            MB2_BranchHelpStart();
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb2ev_shortcutEnd0Masu);
            MBBranchSelStart(win, GwSystem.current_player_index, 0);
            if (MBPlayerComCheck(-1)) {
                if (MBComTreeExec(mb2ev_shortcutEnd0ComTree0) == 0) {
                    j = 0;
                } else {
                    j = 1;
                    if (MBComTreeExec(mb2ev_shortcutEnd0ComTree1)) {
                        j = 2;
                    }
                }
                for (sel = 0; sel < j; sel++) {
                    MBBranchSelMesSend(win, -2);
                }
                MBBranchSelMesSend(win, -4);
            }
            sel = MBBranchSelWait(win);
            MBBranchArrowGrpKill(win);
            MB2_BranchHelpEnd();
            switch (sel) {
                case 0:
                    MBMoveNextMasuSet(-1, 2, 0xE);
                    player->rev |= 1;
                    break;
                case 1:
                    MBMoveNextMasuSet(-1, 0xA, 8);
                    player->rev |= 1;
                    break;
                default:
                    MBMoveNextMasuSet(-1, 6, 0);
                    player->rev &= ~1;
                    break;
            }
            break;
        case 0x2A:
        case 0x82:
            MBPlayerMotionSet(-1, -1, 2);
            MBPlayerRotMasuStart(-1, 8, 0x77);
            HuPrcSleep(8);
            MBDlgResultWinExec(0x602);
            MBPlayerMotionSet(-1, -1, 2);
            HuPrcVSleep();
            MB2_BranchHelpStart();
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb2ev_shortcutEnd1Masu);
            MBBranchSelStart(win, GwSystem.current_player_index, 0);
            if (MBPlayerComCheck(-1)) {
                if (MBComTreeExec(mb2ev_shortcutEnd1ComTree0) == 0) {
                    j = 0;
                } else {
                    j = 1;
                    if (MBComTreeExec(mb2ev_shortcutEnd1ComTree1)) {
                        j = 2;
                    }
                }
                for (sel = 0; sel < j; sel++) {
                    MBBranchSelMesSend(win, -2);
                }
                MBBranchSelMesSend(win, -4);
            }
            sel = MBBranchSelWait(win);
            MBBranchArrowGrpKill(win);
            MB2_BranchHelpEnd();
            switch (sel) {
                case 0:
                    MBMoveNextMasuSet(-1, 4, 0);
                    player->rev &= ~1;
                    break;
                case 1:
                    MBMoveNextMasuSet(-1, 2, 0xE);
                    player->rev |= 1;
                    break;
                default:
                    MBMoveNextMasuSet(-1, 0xA, 8);
                    player->rev |= 1;
                    break;
            }
            break;
    }
}

void MB2Ev_VacuumEffCreate(void) {
    SpaceData *space = MBMasuGet(0x78);
    s16 model;

    model = mb2ev_vacuumEffMdl = Hu3DModelRead(0xB0033, 0xAA9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelCameraSet(model, HU3D_CAM0);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DParticleCreate(model, -1, NULL, MB2Ev_VacuumEffUpdate);
    MB2Ev_VacuumEffPosSet(model, space->coords.x + 142.0f, space->coords.y, space->coords.z);
    MB2Ev_VacuumEffSpeedSet(model, 1.0f, 1000.0f);
    mb2ev_vacuumEffOnF = 0;
    mb2ev_vacuumEffObj = omAddObj(0x7D0, 0xA, 0xA, -1, MB2Ev_VacuumEffObjMain);
}

void MB2Ev_VacuumEffObjMain(omObjData *obj) {
    s32 i;

    if (mb2ev_vacuumEffOnF != 0) {
        for (i = 0; i < mb2ev_vacuumEffRate; i++) {
            MB2Ev_VacuumEffAdd(mb2ev_vacuumEffMdl);
        }
    }
}

void MB2Ev_VacuumEffOn(void) {
    mb2ev_vacuumEffOnF = 1;
}

void MB2Ev_VacuumEffOff(void) {
    mb2ev_vacuumEffOnF = 0;
}

void MB2Ev_VacuumEffKill(void) {
    Hu3DModelKill(mb2ev_vacuumEffMdl);
    omDelObj(mb2ev_vacuumEffObj);
}

void MB2Ev_VacuumEffSpeedSet(s16 model, f32 arg1, f32 arg2) {
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;

    bc->unk08.f = arg2;
    bc->unk0C.f = arg1;
}

void MB2Ev_VacuumEffPosSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    HmfModelData_UnkBC_Struct *model = Hu3DData[arg0].unkBC;
    model->unk1C.f = arg1;
    model->unk20.f = arg2;
    model->unk24.f = arg3;
}

void MB2Ev_VacuumEffAdd(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = effect->unk58;
    s16 i;
    s16 count = hmf->unk1A;
    f32 angle;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            dist = (u8)(rand8() / 10) + 300;
            angle = (s32)(rand8() * 25U >> 7) + 15;
            particle->unk0C = sindf(angle) * dist + effect->unk1C.f;
            particle->unk10 = 0.0f;
            particle->unk14 = cosdf(angle) * dist + effect->unk24.f;
            if (effect->unk0C.f > 0.0f) {
                particle->unk18 = particle->unk1C = particle->unk20 = 0.0f;
            } else {
                dx = effect->unk1C.f - particle->unk0C;
                dy = effect->unk20.f - particle->unk10;
                dz = effect->unk24.f - particle->unk14;
                dist = HuSqrtf(dx * dx + dy * dy + dz * dz);
                particle->unk18 = dx / dist * effect->unk0C.f;
                particle->unk1C = dy / dist * effect->unk0C.f;
                particle->unk20 = dz / dist * effect->unk0C.f;
                particle->unk0C = effect->unk1C.f;
                particle->unk10 = effect->unk20.f;
                particle->unk14 = effect->unk24.f;
            }
            particle->unk08 = 1.0f;
            break;
        }
    }
}

void MB2Ev_VacuumEffUpdate(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 scale;
    f32 speed;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        effect->unk02++;
    }

    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            if (effect->unk0C.f > 0.0f) {
                particle->unk0C += particle->unk18;
                particle->unk10 += particle->unk1C;
                particle->unk14 += particle->unk20;
                dx = effect->unk1C.f - particle->unk0C;
                dy = effect->unk20.f - particle->unk10;
                dz = effect->unk24.f - particle->unk14;
                speed = HuSqrtf(dx * dx + dy * dy + dz * dz);
                dist = speed;
                scale = speed / 1000.0f * 3.0f;
                if ((speed < 100.0f) | (scale < 0.1f)) {
                    particle->unk08 = 0.0f;
                } else {
                    particle->unk08 = scale;
                    speed = (effect->unk08.f - speed) / speed;
                    if (speed < 0.05f) {
                        speed = 0.05f;
                    }
                    speed *= effect->unk0C.f;
                    particle->unk18 = dx / dist * speed;
                    particle->unk1C = dy / dist * speed;
                    particle->unk20 = dz / dist * speed;
                }
            } else {
                particle->unk0C += particle->unk18;
                particle->unk10 += particle->unk1C;
                particle->unk14 += particle->unk20;
                particle->unk18 *= 0.98;
                particle->unk1C *= 0.98f;
                particle->unk20 *= 0.98f;
                particle->unk08 -= 0.001f;
                if (particle->unk08 < 0.0f) {
                    particle->unk08 = 0.0f;
                }
            }
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void MB2Ev_ActionTimeTitleProc(void) {
    void *data;
    s32 spriteId;
    s32 grp;
    s32 count;
    s32 wrapped;
    s32 fading;
    s32 mask;
    s32 clampedAlpha;
    s32 alpha;
    f32 angle;
    f32 speed;

    data = DataRead(0x1300F7);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    grp = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, 0xA0, 0x5A);

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
            HuSprAttrSet(grp, 0, HUSPR_ATTR_FLIPY);
        } else {
            HuSprAttrReset(grp, 0, HUSPR_ATTR_FLIPY);
        }
        HuSprScaleSet(grp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprAttrReset(grp, 0, HUSPR_ATTR_FLIPY);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
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
        HuSprTPLvlSet(grp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprScaleSet(grp, 0, 1.0f, 0.0f);
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    omDelPrcObj(NULL);
}

Process *MB2Ev_ActionTimeTitleCreate(void) {
    return omAddPrcObj(MB2Ev_ActionTimeTitleProc, 0x1000, 0, 0);
}

#ifdef NON_MATCHING
// Instructions and register allocation match. The only remaining difference is
// the stack frame: the target reserves one extra 8-byte spill slot (0x128, never
// accessed), so the frame is 0x190 instead of 0x188 and the callee-saved register
// save offsets are shifted by 8. Reload spill slots here are 0x108 space, 0x110
// player, 0x118 model, 0x120 helpWin, then the loop-hoisted &moveTimes[result]
// (0x128 here, 0x130 in the target), so the target has one more pseudo (numbered
// after helpWin) that failed allocation yet has no remaining references.
// Tried without effect on the frame: shuffling local declaration order, s32
// masuId / switch on the call directly, moving or splitting moveTimes and its
// float conversion, reusing destSpace/curPlayer for other MBMasuGet/MBPlayerGet
// calls, dead uses of the second cosdf() result, and else-if chains for result.
// Also tried (checked with an instrumented cc1 that logs reload slot allocation):
// separate locals for the spin speed/lap count, for MBMasuGet(0x53/0x7A/
// mb2ev_vacuumFlyMasuTbl[result]), for MBRand's result and for HuPrcCurrentGet(), and a
// `time` local for moveTimes[result]. None adds a slot without changing the code.
// The slot is a pseudo that combine (2.7.2) leaves with a stale reg_n_refs:
// either (1) i2dest of a three-insn combine that keeps i1 (camsetup.c's
// `for (i = 0; i < camSetupNum; i++)`), or (2) a variable live at function
// entry (possibly read before set) whose read combine simplifies away. The
// target has no folded compare-against-zero that (1) could explain. Confirmed
// form (2): adding `s32 tmp;` as the last local and writing `mask = (u8)tmp >> 8;`
// instead of `mask = 0;` gives the exact 0x190 frame and a full ROM match
// (with the mb2ev_vacuumExitTimeTbl INCLUDE_RODATA dropped), but that is an
// uninitialized read, so it is not used. Also tried without effect: a
// separate `stop` angle set in the spin-loop break paths, reversed or
// rewritten comparisons (`5 <= j`, `-360 > angle`, `<=`/`>` variants), and
// `for (j = 0; j < 6; j++)` style motion pointer loops.
void MB2Ev_Vacuum(void) {
    SpaceData *space = MBMasuGet(0x78);
    SpaceData *destSpace = MBMasuGet(0x52);
    GW_PLAYER *player = MBPlayerGet(-1);
    Vec focus;
    Vec center;
    Vec startPos[4];
    Vec offset[4];
    Vec move[4];
    f32 speed[4];
    s32 pressCount[4];
    UnkVibrateProcess *vibrate[4];
    GW_PLAYER *curPlayer;
    Object *model;
    Unk3 *helpWin;
    s16 win;
    s32 result;
    s32 angle;
    s32 mask;
    s32 winners;
    s32 played;
    u32 *motion;
    f32 scale;
    s16 masuId;
    s32 i;
    s32 j;

    MBStatusHideAll();
    HuVecAdd(&center, &space->coords, &destSpace->coords);
    HuVecMulScalar(&center, 0.5f, &center);
    center.z -= 40.0f;
    HuVecCopy3F(&focus, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&focus);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&focus, &center, &focus, 40));
    HuPrcChildWatch();
    MBDlgWinExec(0x39, 0x400);

    result = MBRand(7.0f);
    if (result >= 1 && result <= 3) {
        result = 1;
    }
    if (result >= 4 && result <= 6) {
        result = 2;
    }

    // i and j are reused here as the spin speed and lap count.
    j = 0;
    i = 0;
    angle = -138;
    HuAudFXPlay(0x192);
    while (TRUE) {
        mb2_vacuumRouletteMdl->rot.x = sindf(angle);
        mb2_vacuumRouletteMdl->rot.z = cosdf(angle);
        if (j >= 5) {
            if (result == 0) {
                if (angle >= -180 && angle + i < -179) {
                    angle = -180;
                    break;
                }
            }
            if (result == 1) {
                if (angle >= -90 && angle + i < -89) {
                    angle = -90;
                    break;
                }
            }
            if (result == 2) {
                if (angle >= -135 && angle + i < -134) {
                    angle = -135;
                    break;
                }
            }
        }
        angle += i;
        i -= 2;
        if (angle < -360) {
            j++;
            angle += 360;
        }
        if (i < -50) {
            i = -50;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x193);
    mb2_vacuumRouletteMdl->rot.x = sindf(angle);
    mb2_vacuumRouletteMdl->rot.z = cosdf(angle);

    angle = 0;
    for (i = 0; i < 30; i++) {
        angle += 39.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        scale = cosdf(angle) * 0.3f + 1.0f;
        cosdf(angle); // result unused, but the call is present in the target
        HuVecCopyXYZ(&mb2_vacuumRouletteMdl->scale, 1.0f, 1.0f, scale);
        HuPrcVSleep();
    }

    mb2ev_vacuumEffRate = 1;
    MB2Ev_VacuumEffCreate();
    mask = 0;
    HuVecCopy3F(&center, &MBMasuGet(0x53)->coords);
    center.z -= 20.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&focus, &center, &focus, 30));
    HuPrcChildWatch();
    model = MBModelFileCreate(0x130169, -1, 1.0f, 0, NULL);
    Hu3DModelAttrSet(model->omObj1->model[0], HU3D_ATTR_ZMASK, HU3D_ATTR_ZMASK);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    MBModelTempAllocFree(model);
    for (i = 0; i < 4; i++) {
        curPlayer = MBPlayerGet(i);
        masuId = MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx);
        switch (masuId) {
            case 0x50:
            case 0x51:
            case 0x52:
            case 0x53:
            case 0x54:
            case 0x55:
                mask |= 1 << i;
                vibrate[i] = MBPlayerVibrateObjCreate(i, 1, 5);
                break;
        }
    }
    mbTauntOffF = 1;
    MB2Ev_VacuumEffOn();
    HuAudFXPlay(0x194);
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            curPlayer = MBPlayerGet(i);
            MBPlayerMotionLoad(i, 5, 0x3D);
            MBPlayerMotionLoad(i, 6, 0x3B);
            MBMotionSet(curPlayer->player_obj, 5, 2);
            MBVecDirGet(&space->coords, &curPlayer->player_obj->coords, &curPlayer->player_obj->rot);
            HuVecCopy3F(&startPos[i], &curPlayer->player_obj->coords);
            HuVecSubtract(&offset[i], &space->coords, &curPlayer->player_obj->coords);
            HuVecMulScalar(&offset[i], 0.1f, &offset[i]);
            HuVecAdd(&offset[i], &offset[i], &curPlayer->player_obj->coords);
            offset[i].y += (i - 1) * 7.0f;
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&curPlayer->player_obj->coords, &offset[i],
                                                                    &curPlayer->player_obj->coords, 20));
            curPlayer->player_obj->flags |= 1;
        }
    }
    HuPrcChildWatch();
    HuPrcChildLink(HuPrcCurrentGet(), MB2Ev_ActionTimeTitleCreate());
    HuPrcSleep(30);
    win = HuWinCreate(0x66, 0xB2, 0x74, 0x18, 0, 0);
    HuWinBGTPLvlSet(win, 0x100);
    HuWinBGColSet(win, 0x8C, 0xC8, 0x3C);
    helpWin = MBHelpWinCreate(0x16, 0xB4, 1);
    HuPrcChildWatch();
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            MBMotionSet(MBPlayerGet(i)->player_obj, 6, 2);
        }
    }
    HuPrcSleep(10);
    for (i = 0; i < 4; i++) {
        pressCount[i] = 0;
        speed[i] = 1.0f;
        curPlayer = MBPlayerGet(i);
        HuVecSubtract(&offset[i], &space->coords, &curPlayer->player_obj->coords);
        HuVecMulScalar(&offset[i], 0.002f, &offset[i]);
    }

    for (j = 0; j < 120; j++) {
        for (i = 0; i < 4; i++) {
            curPlayer = MBPlayerGet(i);
            if (mask & (1 << i)) {
                if (MBPlayerComCheck(i)) {
                    if (MBRand(5.0f) == 0 || GwSystem.star_spawn_indices[GwSystem.current_star_spawn] == 7) {
                        pressCount[i]++;
                        if (speed[i] == 0.0f) {
                            speed[i] = 1.0f;
                        } else {
                            speed[i] += 0.3f;
                        }
                        if (speed[i] > 3.0f) {
                            speed[i] = 3.0f;
                        }
                    }
                } else if (ContBtnDown[GwPlayer[i].pad] & A_BUTTON) {
                    pressCount[i]++;
                    if (speed[i] == 0.0f) {
                        speed[i] = 1.0f;
                    } else {
                        speed[i] += 0.3f;
                    }
                    if (speed[i] > 3.0f) {
                        speed[i] = 3.0f;
                    }
                }
                HuVecCopy3F(&move[i], &offset[i]);
                if (speed[i] < 1.0f) {
                    HuVecMulScalar(&move[i], 1.0f - speed[i] / 2.0f, &move[i]);
                } else {
                    HuVecMulScalar(&move[i], 0.3f, &move[i]);
                }
                HuVecAdd(&curPlayer->player_obj->coords, &move[i], &curPlayer->player_obj->coords);
                speed[i] -= 0.1f;
                if (speed[i] < 0.0f) {
                    speed[i] = 0.0f;
                }
                Hu3DMotionSpeedSet(curPlayer->player_obj->omObj1->model[0], speed[i]);
            }
        }
        MB2Ev_VacuumEffSpeedSet(mb2ev_vacuumEffMdl, j / 24.0f + 1.0f, 1000.0f);
        HuPrcVSleep();
    }

    MB2Ev_VacuumEffOff();
    msmSeFadeOut(30);
    MBHelpWinKill(helpWin);
    HuWinKill(win);
    played = FALSE;
    winners = 0;
    for (i = 0; i < 4; i++) {
        curPlayer = MBPlayerGet(i);
        if (mask & (1 << i)) {
            MBPlayerVibrateObjKill(vibrate[i]);
            if (pressCount[i] >= 25) {
                Hu3DMotionSpeedSet(curPlayer->player_obj->omObj1->model[0], 2.0f);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&curPlayer->player_obj->coords, &startPos[i],
                                                                        &curPlayer->player_obj->coords, 20));
            } else {
                Hu3DMotionSpeedSet(curPlayer->player_obj->omObj1->model[0], 2.0f);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&curPlayer->player_obj->coords, &space->coords,
                                                                        &curPlayer->player_obj->coords, 10));
                winners |= 1 << i;
                if (!played) {
                    played = TRUE;
                    HuAudFXPlay(0x195);
                }
            }
        }
    }
    HuPrcSleep(20);
    for (i = 0; i < 4; i++) {
        curPlayer = MBPlayerGet(i);
        if (!(winners & (1 << i))) {
            curPlayer->player_obj->flags &= ~1;
        }
    }
    for (i = 0; i < 4; i++) {
        if (mask & (1 << i)) {
            curPlayer = MBPlayerGet(i);
            MBMotionSet(curPlayer->player_obj, -1, 2);
            motion = mbPlayerMotTbl[0];
            for (j = 6; j != 0; j--) {
                motion++;
            }
            MBPlayerMotionLoad(i, 5, ((u16 *)motion)[1]);
            motion = mbPlayerMotTbl[0];
            for (j = 7; j != 0; j--) {
                motion++;
            }
            MBPlayerMotionLoad(i, 6, ((u16 *)motion)[1]);
            MBVecForwardSet(&curPlayer->player_obj->rot);
        }
    }

    if (winners != 0) {
        mb2ev_vacuumEffRate = 2;
        MB2Ev_VacuumEffSpeedSet(mb2ev_vacuumEffMdl, -40.0f, 1000.0f);
        MB2Ev_VacuumEffOn();
        HuAudFXPlay(0x196);
        HuPrcSleep(30);
        for (i = 0; i < 4; i++) {
            curPlayer = MBPlayerGet(i);
            if (winners & (1 << i)) {
                MBPlayerMotionLoad(i, 5, 0x3C);
                MBPlayerMotionLoad(i, 6, 7);
                MBMotionSet(curPlayer->player_obj, 5, 0);
                HuPrcVSleep();
                Hu3DMotionAttrSet(curPlayer->player_obj->omObj1->model[0], 2, 1);
                HuVecCopy3F(&curPlayer->player_obj->coords, &MBMasuGet(0x7A)->coords);
                // destSpace is briefly reused here; this affects register allocation.
                destSpace = MBMasuGet(mb2ev_vacuumFlyMasuTbl[result]);
                HuVecSubtract(&offset[i], &destSpace->coords, &curPlayer->player_obj->coords);
                HuVecMulScalar(&offset[i], 2.5f, &offset[i]);
                HuVecAdd(&offset[i], &offset[i], &curPlayer->player_obj->coords);
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&curPlayer->player_obj->coords, &offset[i],
                                                                        &curPlayer->player_obj->coords, 15));
                MBVecDirGet(&curPlayer->player_obj->coords, &offset[i], &curPlayer->player_obj->rot);
                HuAudFXPlay(0x197);
                HuPrcSleep(5);
            }
        }
        HuPrcSleep(5);
        WipeCreateOut(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuPrcChildWatch();
        MB2Ev_VacuumEffKill();
        MBModelKill(model);
        space = MBMasuGet(mb2ev_vacuumExitMasuTbl[result]);
        destSpace = MBMasuGet(mb2ev_vacuumDestMasuTbl[result]);
        MBCameraFocusVecSet(&destSpace->coords);
        MBBackRefresh(&destSpace->coords, 0);
        HuPrcVSleep();
        MBCameraFocusModeSet(3);
        for (i = 0; i < 4; i++) {
            curPlayer = MBPlayerGet(i);
            if (winners & (1 << i)) {
                MBMasuLinkIdxGet(mb2ev_vacuumDestMasuTbl[result], &curPlayer->clink, &curPlayer->cidx);
                curPlayer->nlink = curPlayer->blink = curPlayer->clink;
                curPlayer->nidx = curPlayer->cidx + 1;
                curPlayer->bidx = curPlayer->cidx - 1;
            }
        }
        for (i = 0; i < 4; i++) {
            if (!(winners & (1 << i))) {
                MBPlayerPosFixSet(i, 1);
            }
        }
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        j = 0;
        for (i = 0; i < 4; i++) {
            if (winners & (1 << i)) {
                curPlayer = MBPlayerGet(i);
                {
                    s32 moveTimes[3] = { 20, 20, 30 };

                    HuPrcChildLink(HuPrcCurrentGet(), MBVecSpeedMoveCreate(&curPlayer->player_obj->coords, &space->coords,
                                                                                 &curPlayer->player_obj->coords, moveTimes[result]));
                }
                MBVecDirGet(&curPlayer->player_obj->coords, &space->coords, &curPlayer->player_obj->rot);
                HuPrcChildWatch();
                HuAudFXPlay(GwPlayer[i].chr + 0x287);
                MBPlayerVibrate(i, 3);
                MBMotionSet(curPlayer->player_obj, 6, 0);
                curPlayer->player_obj->flags &= ~1;
                MBVecForwardSet(&curPlayer->player_obj->rot);
                HuVecCopy3F(&offset[i], &destSpace->coords);
                offset[i].x += mb2ev_vacuumLandOfsTbl[j][0];
                offset[i].z += mb2ev_vacuumLandOfsTbl[j][1];
                j++;
                HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&curPlayer->player_obj->coords, &offset[i],
                                                                        &curPlayer->player_obj->coords, 16));
                MBModelJumpSet(curPlayer->player_obj, 15.0f, -1.875f);
                HuPrcChildWatch();
                MBModelJumpWait(curPlayer->player_obj);
                MBMotionSet(curPlayer->player_obj, 4, 2);
            }
        }
        HuPrcSleep(20);
        for (i = 0; i < 4; i++) {
            if (winners & (1 << i)) {
                curPlayer = MBPlayerGet(i);
                motion = mbPlayerMotTbl[0];
                for (j = 6; j != 0; j--) {
                    motion++;
                }
                MBPlayerMotionLoad(i, 5, ((u16 *)motion)[1]);
                motion = mbPlayerMotTbl[0];
                for (j = 7; j != 0; j--) {
                    motion++;
                }
                MBPlayerMotionLoad(i, 6, ((u16 *)motion)[1]);
            }
        }
        MBStatusShowAll();
    } else {
        HuVecCopy3F(&center, &player->player_obj->coords);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&focus, &center, &focus, 20));
        HuPrcChildWatch();
        MBStatusShowAll();
        MBCameraFocusModeSet(3);
        MB2Ev_VacuumEffKill();
        MBModelKill(model);
    }
    HuVecCopyXYZ(&mb2_vacuumRouletteMdl->scale, 1.0f, 1.0f, 1.0f);
    mb2_vacuumRouletteMdl->rot.x = sindf(-138.0f);
    mb2_vacuumRouletteMdl->rot.z = cosdf(-138.0f);
    mbTauntOffF = 0;
}
#else
INCLUDE_ASM("asm/nonmatchings/game/overlays/party/boards/w02_deep_bloober_sea/main", MB2Ev_Vacuum);
#endif

void MB2Ev_HatenaWarp(s16 masuId) {
    f32 screenPos[2];
    Vec focus;
    Vec center;
    GW_PLAYER *player;
    SpaceData *space;
    SpaceData *destSpace;
    Object *model;
    UnkVibrateProcess *vibrate;
    s32 useWipe;
    s32 destMasu;
    s32 i;

    player = MBPlayerGet(-1);
    space = MBMasuGet(0x72);
    destMasu = 0;
    for (i = 0; i < ARRAY_COUNTU(mb2ev_hatenaWarpMasuTbl); i += 2) {
        if (mb2ev_hatenaWarpMasuTbl[i] == masuId) {
            destMasu = mb2ev_hatenaWarpMasuTbl[i + 1];
            break;
        }
    }
    destSpace = MBMasuGet(destMasu);
    MBCamera3Dto2D(&space->coords, screenPos);
    if (screenPos[0] >= 24.0f && screenPos[0] <= 296.0f && screenPos[1] >= 12.0f && screenPos[1] <= 228.0f) {
        useWipe = FALSE;
        HuVecCopy3F(&center, &space->coords);
        HuVecCopy3F(&focus, &player->player_obj->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&focus);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&focus, &center, &focus, 20));
        HuPrcChildWatch();
    } else {
        useWipe = TRUE;
        WipeCreateOut(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuVecCopy3F(&focus, &space->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&focus);
        MBBackRefresh(&focus, 0);
        HuPrcVSleep();
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    }
    MBDlgWinExec(0x3A, 0x500);
    HuVecAdd(&center, &player->player_obj->coords, &destSpace->coords);
    HuVecMulScalar(&center, 0.5f, &center);
    if (!useWipe) {
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&focus, &center, &focus, 20));
        HuPrcChildWatch();
    } else {
        WipeCreateOut(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuVecCopy3F(&focus, &center);
        MBBackRefresh(&focus, 0);
        HuPrcVSleep();
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    }

    model = MBModelFileCreate(0x13016A, -1, 1.0f, 0, NULL);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);
    model->velocity.x = 150.0f;
    for (i = 90; i <= 180; i += 3) {
        model->velocity.x = sindf(i) * 150.0f;
        MTX_ROTZ(Hu3DData[model->omObj1->model[0]].mtx, 180 - i);
        HuPrcVSleep();
    }

    MBMasuLinkIdxGet(destMasu, &player->clink, &player->cidx);
    MBMoveMasuSet(MBPlayerTurnGet(), player->clink, player->cidx);
    for (i = 0; i < 4; i++) {
        if (MBPlayerTurnGet() != i) {
            MBPlayerPosFixSet(i, 5);
        }
    }
    HuAudFXPlay(0x191);
    vibrate = MBPlayerVibrateObjCreate(-1, 2, 5);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords, &destSpace->coords,
                                                            &player->player_obj->coords, 18));
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&model->coords, &destSpace->coords, &model->coords, 18));
    for (i = 0; i <= 180; i += 10) {
        model->velocity.x = sindf(i) * 50.0f;
        MTX_ROTZ(Hu3DData[model->omObj1->model[0]].mtx, -sindf(i) * 30.0f);
        player->player_obj->velocity.x = sindf(i) * 50.0f;
        HuPrcVSleep();
    }
    MBPlayerVibrateObjKill(vibrate);
    player->player_obj->velocity.x = 0.0f;
    for (i = 0; i <= 90; i += 10) {
        model->velocity.x = sindf(i) * 150.0f;
        MTX_ROTZ(Hu3DData[model->omObj1->model[0]].mtx, i);
        HuPrcVSleep();
    }
    MBModelKill(model);
    MBCameraFocusModeSet(3);
    HuPrcSleep(5);
}

void MB2Ev_Hatena(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    HuPrcSleep(8);
    switch (masuId) {
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
            MB2Ev_Vacuum();
            break;
        default:
            MB2Ev_HatenaWarp(masuId);
            break;
    }
    omDelPrcObj(NULL);
}

void MB2Ev_OpStarMapView(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &mb2ev_opStarMapViewRect);
    MB2_ObjectSetup();
    MBStart(2);
    omAddPrcObj(MB2Ev_StarMapView, 0x1005, 0x1000, 0);
}

s32 MB2_ComNKinokoTargetGet(void) {
    s32 i;
    DecisionTreeNonLeafNode *data;
    GW_SYSTEM *loc = &GwSystem;

    data = mb2_itemNKinokoTargetComTree[loc->star_spawn_indices[loc->current_star_spawn]];
    MBComTreePlayerSet(loc->current_player_index);
    if (MBComTreeExec(mb2_itemNKinokoSelfComTree) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            MBComTreePlayerSet(i);
            if (MBComTreeExec(data) == 0) {
                return i;
            }
        }
    }
    MBRand(4.0f);
}

s32 MB2_ComRKinokoTargetGet(void) {
    s32 i;
    DecisionTreeNonLeafNode *data1;
    DecisionTreeNonLeafNode *data2;
    GW_SYSTEM *loc = &GwSystem;

    data1 = mb2_itemRKinokoSelfComTree[loc->star_spawn_indices[loc->current_star_spawn]];
    data2 = mb2_itemRKinokoTargetComTree[loc->star_spawn_indices[loc->current_star_spawn]];
    MBComTreePlayerSet(loc->current_player_index);
    if (MBComTreeExec(data1) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            MBComTreePlayerSet(i);
            if (MBComTreeExec(data2) == 0) {
                return i;
            }
        }
    }
    MBRand(4.0f);
}

s32 MB2_ComItemExcessCheck(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

s32 MB2_ComRobItemSafeCheck(s32 arg0, s32 arg1) {
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

#ifndef NON_MATCHING
const s32 mb2ev_vacuumExitTimeTbl[] = { 20, 20, 30 };
#endif

s32 MB2_ComItemDecide(void) {
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
                if (MB2_ComItemExcessCheck() != 0) {
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
                if (MBRandCheck100(70) != 0 && MB2_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (MB2_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb2_itemSKinokoComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (MB2_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb2_itemKSuitComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(mb2_itemWarpBlockComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(mb2_itemNKinokoComTree) == 0) {
                    s32 target = MB2_ComNKinokoTargetGet();

                    mb2_comNKinokoTarget = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(mb2_itemRKinokoComTree) == 0) {
                    s32 target = MB2_ComRKinokoTargetGet();

                    mb2_comRKinokoTarget = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, mb2_comRobBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < mbItemComWeightTbl[it]) {
                                    best = mbItemComWeightTbl[it];
                                    mb2_comRobBoxTarget = i;
                                }
                            }
                        }
                    }
                }
                if (mb2_comRobBoxTarget == -1) {
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
                for (i = 0, mb2_comExchangeBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += mbItemComWeightTbl[it];
                            }
                        }
                        if (best < count) {
                            mb2_comExchangeBoxTarget = i;
                            best = count;
                        }
                    }
                }
                if (mb2_comExchangeBoxTarget == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (MB2_ComRobItemSafeCheck(0x32, 0xA) == 0) {
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
                if (MB2_ComRobItemSafeCheck(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(mb2_itemMajinLampComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && MB2_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(mb2_itemStarYokeComTree) != 0) {
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

s32 MB2_ComShopItemDecide(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = mb2_comShopItemOrderTbl[player->chr][i];

        found = MB2Ev_ShopItemIdxGet(val);
        if (found == -1) {
            continue;
        }
        if (mbItemPriceTbl[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(mb2_comShopItemRateTbl[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (MB2Ev_ShopItemIdxGet(0xE) == found) {
            return found + 1;
        }
        if (MB2Ev_ShopItemIdxGet(0xB) == found && mbItemPriceTbl[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (MB2Ev_ShopItemIdxGet(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(mb2_comShopKeyComTree[mb2ev_shopNo]) == 0 && GwPlayer[loc->current_player_index].coin >= mbItemPriceTbl[1]) {
        s32 route = MB2Ev_ShopItemIdxGet(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(mb2_comShopItemComTree[mb2ev_shopNo]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = mb2_comShopItemOrderTbl[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = MB2Ev_ShopItemIdxGet(val);
            if (found == -1) {
                continue;
            }
            if (mbItemPriceTbl[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(mb2_comShopItemRateTbl[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = MB2Ev_ShopItemIdxGet(0);
    if (found != -1) {
        return found + 1;
    }
    mb2_comShopCancelF = 1;
    return MB2Ev_ShopItemNumGet() + 2;
}

s32 MB2_ComShopEnterDecide(void) {
    if (mb2_comShopCancelF != 0) {
        mb2_comShopCancelF = 0;
        return 2;
    }
    return MBComTreeExec(mb2_comShopEnterComTree[mb2ev_shopNo]) + 1;
}
