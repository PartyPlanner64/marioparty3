#include "WaluigisIsland.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/scroll.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"
#include "game/overlays/party/common/mapfull.h"
#include "game/overlays/party/common/vec.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/com.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/ksuit.h"
#include "game/overlays/party/common/ksuit.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/window.h"

typedef s16 SpaceTriple[3];
typedef s16 SpacePair[2];

typedef struct ChanceTable {
    /* 0x00 */ s32 entries[4];
} ChanceTable; // size 0x10

typedef struct StarChaseWork {
    /* 0x00 */ Vec dir;
    /* 0x0C */ char pad0C[4];
    /* 0x10 */ Vec pos;
    /* 0x1C */ char pad1C[4];
    /* 0x20 */ ChanceTable chaseChanceA;
    /* 0x30 */ ChanceTable chaseChanceB;
    /* 0x40 */ ChanceTable eventTableA;
    /* 0x50 */ ChanceTable eventTableB;
} StarChaseWork; // size 0x60

/* Star-space order and board model resources. */
s16 mb6ev_starOrderTbl[] = { 2, 3, 4, 5, 6, 7, 0, 1 };
s16 mb6ev_starOrderGroupTbl[] = { 0, 0, 0, 0, 0, 0, 1, 1 };
s16 mb6ev_starFlag[] = { 6, 7, 8, 9, 10, 11, 12, 13 };
s16 mb6ev_starMasu[] = { 22, 9, 19, 39, 47, 78, 69, 85 };
s16 mb6ev_starGuideMasu[] = { 99, 100, 101, 102, 103, 104, 105, 106 };
s32 mb6ev_starGuideFaceTbl[] = {
    0x000A007E,
    0x000A007F,
    0x000A0080,
    0x000A0081,
    0x000A0082,
    0x000A0083,
    0x000A0084,
};
s32 mb6ev_starGuideMesTbl[] = {
    0x00005E02,
    0x00005E03,
    0x00005E04,
    0x00005E05,
    0x00005E06,
    0x00005E07,
    0x00005E08,
};
s32 mb6ev_starGetTeresaF = 0;
s16 mb6_masuBlockExtTbl[] = { 0x5F, -1 };

/* Blocked spaces, board links, and model placement. */
s16 mb6_masuBlockTbl[] = {
    22, 9, 19, 39, 47, 78, 69, 85,
    41, 42, 43, 45, 46, 36, 48, 49,
    50, 32, 35, 37, 38, 40, 51, -1
};

s16 mb6_starGuideMapIconOfsTbl[][2] = {
    { 1, -4 },
    { 1, -4 },
    { 0, -4 },
    { 6, 0 },
    { -4, 0 },
    { -4, 4 },
    { 6, 0 },
    { 0, -2 }
};

s16 mb6_teresaGuideMapIconOfsTbl[][2] = {
    { 2, -2 },
    { 0, 0 }
};

s16 mb6_bankMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, 0 }
};

s16 mb6_shopMapIconOfsTbl[][2] = {
    { 2, -2 },
    { 0, 0 }
};

s16 mb6_gateMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, 0 }
};

s16 mb6_gateDirMasuTbl[][2] = {
    { 131, 137 },
    { 150, 130 }
};

s16 mb6_starGuideMdlMasuTbl[] = { 99, 100, 101, 102, 103, 104, 105, 106 };

s16 mb6_starGuideFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb6_teresaGuideMasuTbl[] = { 128, 0 };

s16 mb6_bankCoinMasuTbl[] = { 147, 146 };

Vec mb6_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb6_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb6_gateMasuTbl[] = { 136, 141 };

s16 mb6_gateMdlTbl[] = { 38, 39, 40, 41, 42, 43 };

u32 mb6_gateMot1[] = { 1, 0x130163 };

u32 mb6_gateMot2[] = { 1, 0x130168 };

u32 mb6_gateMot3[] = { 1, 0x13016F };

u32 mb6_gateMot4[] = { 1, 0x130176 };

u32 mb6_gateMot5[] = { 1, 0x130180 };

u32 mb6_gateMot6[] = { 1, 0x130184 };

u32 *mb6_gateMotTbl[] = { mb6_gateMot1, mb6_gateMot2, mb6_gateMot3, mb6_gateMot4, mb6_gateMot5, mb6_gateMot6 };

s32 mb6_gateOpenSeTbl[] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1
};

s32 mb6_gateOpenDelaySeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb6_gateOpenDelayTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb6_gateCloseSeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s16 mb6_bankMapIconMasuTbl[] = { 143, 142 };

s16 mb6_shopMapIconMasuTbl[] = { 144, 140 };

Object *mb6_holeExitMdl = NULL;

s16 mb6_holeMasuTbl[] = { 133, 120, 135, 0 };

Object *mb6_holeBaseMdl = NULL;

u8 *mb6_bombAnimData = NULL;

s16 mb6_bombAnim = -1;

s16 mb6_bridgeMasuTbl[] = { 117, 112 };

s16 mb6_bridgeDirMasuTbl[][2] = {
    { 115, 116 },
    { 113, 151 }
};

Object *mb6_bridgeBaseMdl = NULL;

/* CPU decisions for the board junctions. */
DecisionTreeNonLeafNode mb6ev_branch2ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch2ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch2ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch2ComTree[] = { mb6ev_branch2ComTree0, mb6ev_branch2ComTree1, mb6ev_branch2ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch3ComTree0Star7[] = {
    { 12, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch3ComTree0[] = {
    { 3, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6ev_branch3ComTree0Star7 } },
    { 3, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch3ComTree1[] = {
    { 2, { .data = 0x0000007C }, { .data = 0x0B54233C } },
    { 8, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch3ComTree2[] = {
    { 2, { .data = 0x0000007C }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch3ComTree[] = { mb6ev_branch3ComTree0, mb6ev_branch3ComTree1, mb6ev_branch3ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch4ComTree0[] = {
    { 2, { .data = 0x00000060 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000018 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch4ComTree1[] = {
    { 2, { .data = 0x00000084 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000018 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch4ComTree2[] = {
    { 2, { .data = 0x0000009C }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000060 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch4ComTree[] = { mb6ev_branch4ComTree0, mb6ev_branch4ComTree1, mb6ev_branch4ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch5ComTree0Star5[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch5ComTree0[] = {
    { 2, { .data = 0x00000040 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6ev_branch5ComTree0Star5 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch5ComTree1[] = {
    { 2, { .data = 0x00000040 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x0000001C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch5ComTree2[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x0000001C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch5ComTree[] = { mb6ev_branch5ComTree0, mb6ev_branch5ComTree1, mb6ev_branch5ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch6ComTree0[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch6ComTree1[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000060 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch6ComTree2[] = {
    { 2, { .data = 0x00000060 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch6ComTree[] = { mb6ev_branch6ComTree0, mb6ev_branch6ComTree1, mb6ev_branch6ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch7ComTree0[] = {
    { 2, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000006 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch7ComTree1[] = {
    { 2, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch7ComTree2[] = {
    { 2, { .data = 0x00000006 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch7ComTree[] = { mb6ev_branch7ComTree0, mb6ev_branch7ComTree1, mb6ev_branch7ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch8ComTree0[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch8ComTree1[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch8ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch8ComTree[] = { mb6ev_branch8ComTree0, mb6ev_branch8ComTree1, mb6ev_branch8ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch9ComTree0[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch9ComTree1[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch9ComTree2[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch9ComTree[] = { mb6ev_branch9ComTree0, mb6ev_branch9ComTree1, mb6ev_branch9ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch10ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch10ComTree[] = { mb6ev_branch10ComTree0, mb6ev_branch10ComTree0, mb6ev_branch10ComTree0 };

DecisionTreeNonLeafNode mb6ev_branch11ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch11ComTree[] = { mb6ev_branch11ComTree0, mb6ev_branch11ComTree0, mb6ev_branch11ComTree0 };

DecisionTreeNonLeafNode mb6ev_branch12ComTree0[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch12ComTree1[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch12ComTree2Star3[] = {
    { 9, { .data = 0x00000007 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch12ComTree2Star4WalkMin[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch12ComTree2Star4[] = {
    { 9, { .data = 0x00000003 }, { .node_data = mb6ev_branch12ComTree2Star4WalkMin } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch12ComTree2[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb6ev_branch12ComTree2Star3 } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6ev_branch12ComTree2Star4 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch12ComTree[] = { mb6ev_branch12ComTree0, mb6ev_branch12ComTree1, mb6ev_branch12ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch13ComTree0[] = {
    { 2, { .data = 0x00000006 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch13ComTree1[] = {
    { 2, { .data = 0x00000006 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000019 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch13ComTree2Star3[] = {
    { 1, { .data = 0x00000019 }, { .data = 0x1B54233C } },
    { 9, { .data = 0x00000005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch13ComTree2Star4[] = {
    { 9, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch13ComTree2[] = {
    { 2, { .data = 0x00000008 }, { .node_data = mb6ev_branch13ComTree2Star3 } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6ev_branch13ComTree2Star4 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch13ComTree[] = { mb6ev_branch13ComTree0, mb6ev_branch13ComTree1, mb6ev_branch13ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch14ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch14ComTree1[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch14ComTree2[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_branch14ComTree[] = { mb6ev_branch14ComTree0, mb6ev_branch14ComTree1, mb6ev_branch14ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch15ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch15ComTree1[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch15ComTree2[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch15ComTree[] = { mb6ev_branch15ComTree0, mb6ev_branch15ComTree1, mb6ev_branch15ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch16ComTree0[] = {
    { 2, { .data = 0x00000081 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch16ComTree1[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch16ComTree2[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000081 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch16ComTree[] = { mb6ev_branch16ComTree0, mb6ev_branch16ComTree1, mb6ev_branch16ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch17ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch17ComTree1[] = {
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch17ComTree2[] = {
    { 2, { .data = 0x00000080 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch17ComTree[] = { mb6ev_branch17ComTree0, mb6ev_branch17ComTree1, mb6ev_branch17ComTree2 };

DecisionTreeNonLeafNode mb6ev_holeExitBranchComTree0[] = {
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode *mb6ev_holeExitBranchComTree[] = { mb6ev_holeExitBranchComTree0, mb6ev_holeExitBranchComTree0, mb6ev_holeExitBranchComTree0 };

DecisionTreeNonLeafNode mb6ev_branch18ComTree0[] = {
    { 2, { .data = 0x00000078 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch18ComTree1[] = {
    { 2, { .data = 0x0000001C }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000080 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb6ev_branch18ComTree2Star34Flag[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch18ComTree2Star34[] = {
    { 4, { .data = 0x00000000 }, { .node_data = mb6ev_branch18ComTree2Star34Flag } },
    { 3, { .data = 0x00000008 }, { .data = 0x1A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch18ComTree2[] = {
    { 2, { .data = 0x00000060 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000018 }, { .node_data = mb6ev_branch18ComTree2Star34 } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch18ComTree[] = { mb6ev_branch18ComTree0, mb6ev_branch18ComTree1, mb6ev_branch18ComTree2 };

DecisionTreeNonLeafNode mb6ev_branch19ComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch19ComTree1[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb6ev_branch19ComTree2[] = {
    { 2, { .data = 0x00000018 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode *mb6ev_branch19ComTree[] = { mb6ev_branch19ComTree0, mb6ev_branch19ComTree1, mb6ev_branch19ComTree2 };

event_list_entry mb6_branch1EventTbl[] = {
    { 8, 1, MB6Ev_Branch1 },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb6ev_rouletteDir1Star34ComTree[] = {
    { 4, { .data = 0x00000000 }, { .data = 0x0C97ED55 } },
    { 3, { .data = 0x00000008 }, { .data = 0x0C97ED55 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6ev_rouletteDir1ComTree[] = {
    { 2, { .data = 0x00000018 }, { .node_data = mb6ev_rouletteDir1Star34ComTree } },
    { 2, { .data = 0x00000060 }, { .data = 0x0C97ED55 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6ev_rouletteDir3ComTree[] = {
    { 2, { .data = 0x00000080 }, { .data = 0x0C97ED55 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

s16 mb6ev_branch2Masu[] = {
    153, 3, -1, 1, 3, -1, 1, 153,
    -1, 0
};

s32 mb6ev_branch2Link[] = {
    0x150000, 2, 0, 0x2000C, 0x10002, 0, 0x2000C, 0x10015,
    0
};

event_list_entry mb6_branch2EventTbl[] = {
    { 1, 2, MB6Ev_Branch2 },
    { 0, 0, NULL }
};

s16 mb6ev_branch3Masu[] = {
    89, 92, -1, 91, 92, -1, 91, 89,
    -1, 0
};

s32 mb6ev_branch3Link[] = {
    0x30004, 1, 0, 0x30002, 0x10001, 0, 0x30002, 0x10003,
    0x40000
};

event_list_entry mb6_branch3EventTbl[] = {
    { 1, 1, MB6Ev_Branch3 },
    { 0, 0, NULL }
};

s16 mb6ev_branch4Masu[] = {
    60, 59, -1, 2, 59, -1, 2, 60,
    -1, 0
};

s32 mb6ev_branch4Link[] = {
    0xF0000, 13, 0, 0x40002, 0x1000D, 0, 0x40002, 0x1000F,
    0
};

event_list_entry mb6_branch4EventTbl[] = {
    { 1, 2, MB6Ev_Branch4 },
    { 0, 0, NULL }
};

s16 mb6ev_branch5Masu[] = {
    80, 63, -1, 62, 63, -1, 62, 80,
    -1, 0
};

s32 mb6ev_branch5Link[] = {
    0x100000, 17, 0, 0xF0003, 0x10011, 0, 0xF0003, 0x10010,
    0
};

event_list_entry mb6_branch5EventTbl[] = {
    { 1, 2, MB6Ev_Branch5 },
    { 0, 0, NULL }
};

s16 mb6ev_branch6Masu[] = {
    52, 117, -1, 56, 117, -1, 56, 52,
    -1, 0
};

s32 mb6ev_branch6Link[] = {
    0xE0000, 10, 0, 0xD0003, 0x1000A, 0, 0xD0003, 0x1000E,
    0
};

event_list_entry mb6_branch6EventTbl[] = {
    { 1, 2, MB6Ev_Branch6 },
    { 0, 0, NULL }
};

s16 mb6ev_branch7Masu[] = {
    27, 112, -1, 28, 112, -1, 28, 27,
    -1, 0
};

s32 mb6ev_branch7Link[] = {
    0x60000, 9, 0, 0x50004, 0x10009, 0, 0x50004, 0x10006,
    0
};

event_list_entry mb6_branch7EventTbl[] = {
    { 1, 2, MB6Ev_Branch7 },
    { 0, 0, NULL }
};

s16 mb6ev_branch8Masu[] = {
    41, 134, -1, 51, 134, -1, 51, 41,
    -1, 0
};

s32 mb6ev_branch8Link[] = {
    0xB0000, 12, 0, 0xB0013, 0x1000C, 0, 0xB0013, 0x1000B,
    0
};

event_list_entry mb6_branch8EventTbl[] = {
    { 1, 2, MB6Ev_Branch8 },
    { 0, 0, NULL }
};

s16 mb6ev_branch9Masu[] = {
    11, 150, -1, 13, 150, -1, 13, 11,
    -1, 0
};

s32 mb6ev_branch9Link[] = {
    0x70000, 8, 0, 0x6000D, 0x10008, 0, 0x6000D, 0x10007,
    0
};

event_list_entry mb6_branch9EventTbl[] = {
    { 1, 2, MB6Ev_Branch9 },
    { 0, 0, NULL }
};

s16 mb6ev_branch10Masu[] = {
    124, 125, -1, 124, 125, -1, 124, 125,
    -1, 0
};

s32 mb6ev_branch10Link[] = {
    0x140000, 19, 0, 0x140000, 19, 0, 0x140000, 19,
    0
};

event_list_entry mb6_branch10EventTbl[] = {
    { 1, 1, MB6Ev_Branch10 },
    { 0, 0, NULL }
};

s16 mb6ev_branch11Masu[] = {
    124, 125, -1, 124, 125, -1, 124, 125,
    -1, 0
};

s32 mb6ev_branch11Link[] = {
    0x140000, 19, 0, 0x140000, 19, 0, 0x140000, 19,
    0
};

event_list_entry mb6_branch11EventTbl[] = {
    { 1, 1, MB6Ev_Branch11 },
    { 0, 0, NULL }
};

s16 mb6ev_branch12Masu[] = {
    46, 117, -1, 45, 117, -1, 45, 46,
    -1, 0
};

s32 mb6ev_branch12Link[] = {
    0xB0005, 10, 0, 0xB0003, 0x1000A, 0, 0xB0003, 0x1000B,
    0x50000
};

event_list_entry mb6_branch12EventTbl[] = {
    { 1, 2, MB6Ev_Branch12 },
    { 0, 0, NULL }
};

s16 mb6ev_branch13Masu[] = {
    32, 112, -1, 50, 112, -1, 50, 32,
    -1, 0
};

s32 mb6ev_branch13Link[] = {
    0xB000C, 9, 0, 0xB000A, 0x10009, 0, 0xB000A, 0x1000B,
    0xC0000
};

event_list_entry mb6_branch13EventTbl[] = {
    { 1, 2, MB6Ev_Branch13 },
    { 0, 0, NULL }
};

s16 mb6ev_branch14Masu[] = {
    66, 10, -1, 44, 10, -1, 44, 66,
    -1, 0
};

s32 mb6ev_branch14Link[] = {
    0x20009, 2, 0x70001, 0x1000F, 0x10002, 0x70001, 0x1000F, 0x10002,
    0x90000
};

event_list_entry mb6_branch14EventTbl[] = {
    { 1, 1, MB6Ev_Branch14RKinoko },
    { 0, 0, NULL }
};

s16 mb6ev_branch15Masu[] = {
    8, 6, -1, 11, 6, -1, 11, 8,
    -1, 0
};

s32 mb6ev_branch15Link[] = {
    0x20005, 2, 0x30001, 0x70000, 0x10002, 0x30001, 0x70000, 0x10002,
    0x50000
};

event_list_entry mb6_branch15EventTbl[] = {
    { 1, 1, MB6Ev_Branch15RKinoko },
    { 0, 0, NULL }
};

s16 mb6ev_branch16Masu[] = {
    81, 70, -1, 72, 70, -1, 72, 81,
    -1, 0
};

s32 mb6ev_branch16Link[] = {
    0x100009, 18, 0x70001, 0x100007, 0x10012, 0x70001, 0x100007, 0x10010,
    0x90000
};

event_list_entry mb6_branch16EventTbl[] = {
    { 1, 1, MB6Ev_Branch16RKinoko },
    { 0, 0, NULL }
};

s16 mb6ev_branch17Masu[] = {
    83, 81, -1, 85, 81, -1, 85, 83,
    -1, 0
};

s32 mb6ev_branch17Link[] = {
    0x30009, 16, 0x90001, 0x30007, 0x10010, 0x90001, 0x30007, 0x10003,
    0x90000
};

event_list_entry mb6_branch17EventTbl[] = {
    { 1, 1, MB6Ev_Branch17RKinoko },
    { 0, 0, NULL }
};

s16 mb6ev_holeExitBranchMasu[] = {
    97, 95, -1, 97, 95, -1, 97, 95,
    -1, 0
};

s32 mb6ev_holeExitBranchLink[] = {
    0x10008, 1, 0x60001, 0x10008, 1, 0x60001, 0x10008, 1,
    0x60001
};

s16 mb6ev_branch18Masu[] = {
    110, 111, -1, 109, 111, -1, 109, 110,
    -1, 0
};

s32 mb6ev_branch18Link[] = {
    0x40000, 3, 0, 0x50000, 3, 0, 0x50000, 4,
    0
};

event_list_entry mb6_branch18EventTbl[] = {
    { 1, 1, MB6Ev_Branch18RKinoko },
    { 0, 0, NULL }
};

s16 mb6ev_branch19Masu[] = {
    20, 130, -1, 23, 130, -1, 23, 20,
    -1, 0
};

s32 mb6ev_branch19Link[] = {
    0x60006, 8, 0x20001, 0x60004, 0x10008, 0x20001, 0x60004, 0x10006,
    0x60000
};

event_list_entry mb6_branch19EventTbl[] = {
    { 1, 1, MB6Ev_Branch19RKinoko },
    { 0, 0, NULL }
};

event_list_entry mb6_merge1EventTbl[] = {
    { 1, 1, MB6Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge2EventTbl[] = {
    { 1, 1, MB6Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge3EventTbl[] = {
    { 1, 1, MB6Ev_Merge3 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge4EventTbl[] = {
    { 1, 1, MB6Ev_Merge4 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge5EventTbl[] = {
    { 1, 1, MB6Ev_Merge5 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge6EventTbl[] = {
    { 1, 1, MB6Ev_Merge6 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge7EventTbl[] = {
    { 1, 1, MB6Ev_Merge7 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge8EventTbl[] = {
    { 1, 1, MB6Ev_Merge8 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge9EventTbl[] = {
    { 1, 1, MB6Ev_Merge9 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge10EventTbl[] = {
    { 1, 1, MB6Ev_Merge10 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge11EventTbl[] = {
    { 1, 1, MB6Ev_Merge11 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge12EventTbl[] = {
    { 1, 1, MB6Ev_Merge12 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge13EventTbl[] = {
    { 1, 1, MB6Ev_Merge13 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge14EventTbl[] = {
    { 1, 1, MB6Ev_Merge14 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge15EventTbl[] = {
    { 1, 1, MB6Ev_Merge15 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge16EventTbl[] = {
    { 1, 1, MB6Ev_Merge16 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge17EventTbl[] = {
    { 1, 1, MB6Ev_Merge17 },
    { 0, 0, NULL }
};

event_list_entry mb6_merge18EventTbl[] = {
    { 1, 1, MB6Ev_Merge18 },
    { 0, 0, NULL }
};

event_list_entry mb6_trapdoorMasu124EventTbl[] = {
    { 1, 1, MB6Ev_Trapdoor },
    { 0, 0, NULL }
};

event_list_entry mb6_trapdoorMasu125EventTbl[] = {
    { 1, 1, MB6Ev_Trapdoor },
    { 0, 0, NULL }
};

event_list_entry mb6_branch1RevEventTbl[] = {
    { 1, 1, MB6Ev_Branch1Rev },
    { 0, 0, NULL }
};

event_list_entry mb6_keyManMasuEventTbl[] = {
    { 1, 2, MB6Ev_KeyManMasu },
    { 0, 0, NULL }
};

event_list_entry mb6_starMasuEventTbl[] = {
    { 1, 1, MB6Ev_StarMasu },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb6ev_bankComTree[] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } }
};

u32 mb6ev_bankCoinPileMot[] = { 1, 0xA009D };

event_list_entry mb6_bankMasuEventTbl[] = {
    { 1, 1, MB6Ev_BankMasu },
    { 0, 0, NULL }
};

/* Item shop selection tables, indexed by shop and difficulty/rank. */
u8 mb6ev_shopItemRowTbl[2][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }
};

s8 mb6ev_shopItemTbl[][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } }
};

u8 mb6ev_shopBagRowTbl[2][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }
};

s8 mb6ev_shopBagRateTbl[2][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } }
};

u8 mb6ev_shopBagItemTbl[2][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 }
};

s32 mb6ev_shopItemMesTbl[5][2] = {
    { 0x3B05, 0x3D05 },
    { 0x3B06, 0x3D06 },
    { 0x3B07, 0x3D07 },
    { 0x3B08, 0x3D08 },
    { 0x3B09, 0x3D09 }
};

s32 mb6ev_shopEnterMesTbl[2] = { 0x3B00, 0x3D00 };

s32 mb6ev_shopNoCoinMesTbl[2] = { 0x3B01, 0x3D01 };

s32 mb6ev_shopItemFullMesTbl[2] = { 0x3B02, 0x3D02 };

s32 mb6ev_shopLastTurnMesTbl[2] = { 0x3B03, 0x3D03 };

s32 mb6ev_shopCancelMesTbl[2] = { 0x3B04, 0x3D04 };

u32 mb6ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb6ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

s32 mb6ev_shopNo = 0;

event_list_entry mb6_shopMasuEventTbl[] = {
    { 1, 1, MB6Ev_ShopMasu },
    { 0, 0, NULL }
};

Vec2f mb6ev_teresaSprPosTbl[] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f }
};

Vec2f mb6ev_teresaSprDirTbl[] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f }
};

u8 mb6ev_teresaCoinTurnTbl[][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

u8 mb6ev_teresaCoinPenaltyTbl[][3] = {
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

u8 mb6ev_teresaCoinDiffTbl[] = { 9, 7, 4, 1, 0, 0, 0, 0 };

s32 mb6ev_teresaComTargetRateTbl[] = { 50, 80, 100 };

s32 mb6ev_teresaMdlFlipTbl[] = { 1, 0, 1, 0, 0, 1, 0 };

event_list_entry mb6_teresaMasuEventTbl[] = {
    { 1, 1, MB6Ev_Teresa },
    { 0, 0, NULL }
};

event_list_entry mb6_gate1CloseEventTbl[] = {
    { 1, 1, MB6Ev_Gate1Close },
    { 0, 0, NULL }
};

event_list_entry mb6_gate2CloseEventTbl[] = {
    { 1, 1, MB6Ev_Gate2Close },
    { 0, 0, NULL }
};

event_table_entry mb6_commonEventTbl[] = {
    { 22, mb6_starMasuEventTbl },
    { 9, mb6_starMasuEventTbl },
    { 19, mb6_starMasuEventTbl },
    { 39, mb6_starMasuEventTbl },
    { 47, mb6_starMasuEventTbl },
    { 78, mb6_starMasuEventTbl },
    { 69, mb6_starMasuEventTbl },
    { 85, mb6_starMasuEventTbl },
    { 89, mb6_bankMasuEventTbl },
    { 34, mb6_bankMasuEventTbl },
    { 108, mb6_shopMasuEventTbl },
    { 121, mb6_shopMasuEventTbl },
    { 136, mb6_gate1CloseEventTbl },
    { 141, mb6_gate2CloseEventTbl },
    { -1, NULL }
};

event_table_entry mb6_teresaEventTbl[] = {
    { 127, mb6_teresaMasuEventTbl },
    { -1, NULL }
};

Vec2f mb6ev_itemUsePosTbl[] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f }
};

Vec2f mb6ev_itemFadePosTbl[] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f }
};

Vec2f mb6ev_robBoxItemEndPosTbl[] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f }
};

Vec2f mb6ev_robBoxItemStartPosTbl[] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f }
};

DecisionTreeNonLeafNode mb6ev_shopPhoneComTree[] = {
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

s32 mb6ev_itemPhoneWaveAngleTbl[] = { 20, 60, 30, 50, 70 };

DecisionTreeNonLeafNode mb6ev_keyManUseComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } }
};

Vec2f mb6ev_tereYokeSparkOfsTbl[] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f }
};

s32 mb6ev_gambleCoinPlayer = -1;

u8 mb6ev_gambleMgTbl[] = { 67, 68, 69, 0 };

u8 mb6ev_gambleMgRateTbl[] = { 20, 60, 100, 0 };

GameGuyReward mb6ev_gambleRateTbl[] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 }
};

RGB mb6ev_after5NumColorTbl[] = {
    { 240, 222, 53 },
    { 247, 26, 66 }
};

event_list_entry mb6_kinokoTurnEventTbl[] = {
    { 7, 1, MB6Ev_NKinokoTurnStart },
    { 7, 1, MB6Ev_RKinokoTurnStart },
    { 0, 0, NULL }
};

event_table_entry mb6_turnStatusEventTbl[] = {
    { -5, mb6_kinokoTurnEventTbl },
    { -1, NULL }
};

s16 mb6ev_bombMasuTbl[] = {
    3, 4, 5, 6, 7, 8, 9, 10,
    55, 66, 77, 88, 1, 119, -1, 0
};

s16 mb6_changeMasuTbl[] = {
    32, 35, 36, 37, 38, 39, 40, 41,
    42, 43, 45, 46, 47, 48, 49, 50,
    51, -1
};

u8 mb6_changeMasuTypeTbl[] = {
    1, 1, 2, 2, 6, 6, 12, 9,
    15, 5, 0, 0
};

event_list_entry mb6_changeMasuSetEventTbl[] = {
    { 7, 1, MB6Ev_ChangeMasuTypeSet },
    { 0, 0, NULL }
};

event_list_entry mb6_changeMasuRollEventTbl[] = {
    { 7, 1, MB6Ev_ChangeMasuTypeRoll },
    { 0, 0, NULL }
};

event_list_entry mb6_holeEnterEventTbl[] = {
    { 1, 1, MB6Ev_HoleEnter },
    { 0, 0, NULL }
};

event_table_entry mb6_specialEventTbl[] = {
    { 107, mb6_branch1EventTbl },
    { 119, mb6_branch2EventTbl },
    { 129, mb6_branch3EventTbl },
    { 145, mb6_branch4EventTbl },
    { 122, mb6_branch5EventTbl },
    { 116, mb6_branch6EventTbl },
    { 151, mb6_branch7EventTbl },
    { 114, mb6_branch8EventTbl },
    { 149, mb6_branch9EventTbl },
    { 123, mb6_branch10EventTbl },
    { 126, mb6_branch11EventTbl },
    { 115, mb6_branch12EventTbl },
    { 113, mb6_branch13EventTbl },
    { 55, mb6_branch14EventTbl },
    { 7, mb6_branch15EventTbl },
    { 71, mb6_branch16EventTbl },
    { 82, mb6_branch17EventTbl },
    { 153, mb6_branch18EventTbl },
    { 21, mb6_branch19EventTbl },
    { 92, mb6_merge1EventTbl },
    { 44, mb6_merge2EventTbl },
    { 3, mb6_merge3EventTbl },
    { 111, mb6_merge4EventTbl },
    { 110, mb6_merge5EventTbl },
    { 109, mb6_merge6EventTbl },
    { 27, mb6_merge7EventTbl },
    { 11, mb6_merge8EventTbl },
    { 112, mb6_merge9EventTbl },
    { 117, mb6_merge10EventTbl },
    { 41, mb6_merge11EventTbl },
    { 59, mb6_merge12EventTbl },
    { 52, mb6_merge13EventTbl },
    { 60, mb6_merge14EventTbl },
    { 80, mb6_merge15EventTbl },
    { 81, mb6_merge16EventTbl },
    { 63, mb6_merge17EventTbl },
    { 70, mb6_merge18EventTbl },
    { 124, mb6_trapdoorMasu124EventTbl },
    { 125, mb6_trapdoorMasu125EventTbl },
    { 0, mb6_branch1RevEventTbl },
    { 131, mb6_keyManMasuEventTbl },
    { 150, mb6_keyManMasuEventTbl },
    { 137, mb6_keyManMasuEventTbl },
    { 130, mb6_keyManMasuEventTbl },
    { -2, mb6_changeMasuSetEventTbl },
    { -3, mb6_changeMasuRollEventTbl },
    { 132, mb6_holeEnterEventTbl },
    { 118, mb6_holeEnterEventTbl },
    { 134, mb6_holeEnterEventTbl },
    { -1, NULL }
};

RectF mb6ev_opStarMapViewRect = { 0.0f, 0.0f, 320.0f, 240.0f };

/* CPU item-use and player-target decisions. */
DecisionTreeNonLeafNode mb6_itemSKinokoStar0ComTree[] = {
    { 12, { .data = 0x00000005 }, { .data = 0x00000000 } },
    { 10, { .data = 0x00120003 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0003050B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0D14 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000E0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100009 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B050C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0001050F }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0006000E }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00070000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar3FlagComTree[] = {
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B000B }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B1114 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb6_itemSKinokoStar3FlagComTree } },
    { 10, { .data = 0x00050005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar4FlagComTree[] = {
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar4ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B0D14 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 4, { .data = 0x00000000 }, { .node_data = mb6_itemSKinokoStar4FlagComTree } },
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x000B070C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar5ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00010B0F }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar6ComTree[] = {
    { 12, { .data = 0x00000005 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00110001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoStar7ComTree[] = {
    { 12, { .data = 0x00000019 }, { .data = 0x01428A1E } },
    { 10, { .data = 0x00010B0F }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemSKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb6_itemSKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb6_itemSKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb6_itemSKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb6_itemSKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6_itemSKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6_itemSKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_itemSKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6_itemSKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemKSuitComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A141932 } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar0ComTree[] = {
    { 10, { .data = 0x0001050C }, { .data = 0x0001038A } },
    { 11, { .data = 0x0001050C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar1ComTree[] = {
    { 10, { .data = 0x0002000D }, { .data = 0x0001038A } },
    { 11, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar2ComTree[] = {
    { 10, { .data = 0x00060006 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00060006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar3ComTree[] = {
    { 10, { .data = 0x000B0A10 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000B0A10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar4ComTree[] = {
    { 10, { .data = 0x000B0006 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000B0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar5ComTree[] = {
    { 10, { .data = 0x00040003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x000F0004 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00100001 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00100001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar6ComTree[] = {
    { 10, { .data = 0x000F0004 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00110001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00120005 }, { .data = 0x0001038A } },
    { 11, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00110001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00120005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockStar7ComTree[] = {
    { 10, { .data = 0x00030006 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00010001 }, { .data = 0x0001038A } },
    { 11, { .data = 0x00030006 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A1E } }
};

DecisionTreeNonLeafNode mb6_itemWarpBlockComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb6_itemWarpBlockStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb6_itemWarpBlockStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb6_itemWarpBlockStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb6_itemWarpBlockStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6_itemWarpBlockStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6_itemWarpBlockStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_itemWarpBlockStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6_itemWarpBlockStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar0ComTree[] = {
    { 10, { .data = 0x0001050C }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar1ComTree[] = {
    { 10, { .data = 0x00020005 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar2ComTree[] = {
    { 10, { .data = 0x00060006 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar3ComTree[] = {
    { 10, { .data = 0x000B0A10 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar4ComTree[] = {
    { 10, { .data = 0x000B0006 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar5ComTree[] = {
    { 10, { .data = 0x00040003 }, { .data = 0x0001038A } },
    { 10, { .data = 0x000F0004 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00100001 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar6ComTree[] = {
    { 10, { .data = 0x00110001 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00120005 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampStar7ComTree[] = {
    { 10, { .data = 0x00030006 }, { .data = 0x0001038A } },
    { 10, { .data = 0x00010001 }, { .data = 0x0001038A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0C992D50 } }
};

DecisionTreeNonLeafNode mb6_itemMajinLampComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb6_itemMajinLampStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb6_itemMajinLampStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb6_itemMajinLampStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb6_itemMajinLampStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6_itemMajinLampStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6_itemMajinLampStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_itemMajinLampStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6_itemMajinLampStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar0ComTree[] = {
    { 11, { .data = 0x00010509 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x0003080B }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B1114 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0003 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar1ComTree[] = {
    { 11, { .data = 0x0002000D }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar2ComTree[] = {
    { 11, { .data = 0x00060005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar3ComTree[] = {
    { 11, { .data = 0x000B0D0F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar4ComTree[] = {
    { 11, { .data = 0x000B0005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar5ComTree[] = {
    { 11, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00100000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar6ComTree[] = {
    { 11, { .data = 0x00110001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00120004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoStar7ComTree[] = {
    { 11, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoComTree[] = {
    { 10, { .data = 0x00010001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030002 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B090C }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000001 }, { .node_data = mb6_itemNKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb6_itemNKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb6_itemNKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb6_itemNKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6_itemNKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6_itemNKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_itemNKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6_itemNKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoSelfComTree[] = {
    { 15, { .data = 0x00010001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00030002 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B090C }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x00010509 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x0003080B }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B1114 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000E0003 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar1ComTree[] = {
    { 15, { .data = 0x0002000D }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00060005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar3ComTree[] = {
    { 15, { .data = 0x000B0D0F }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x000B0005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x000F0004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100000 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar6ComTree[] = {
    { 15, { .data = 0x00110001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120004 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemNKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x00010001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00030005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode *mb6_itemNKinokoTargetComTree[] = { mb6_itemNKinokoTargetStar0ComTree, mb6_itemNKinokoTargetStar1ComTree, mb6_itemNKinokoTargetStar2ComTree, mb6_itemNKinokoTargetStar3ComTree, mb6_itemNKinokoTargetStar4ComTree, mb6_itemNKinokoTargetStar5ComTree, mb6_itemNKinokoTargetStar6ComTree, mb6_itemNKinokoTargetStar7ComTree };

DecisionTreeNonLeafNode mb6_itemRKinokoStar0ComTree[] = {
    { 10, { .data = 0x00010D0F }, { .data = 0x0B54233C } },
    { 10, { .data = 0x0002090D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar1ComTree[] = {
    { 10, { .data = 0x0002060A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00020005 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar2ComTree[] = {
    { 10, { .data = 0x0006070C }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00060006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar3ComTree[] = {
    { 10, { .data = 0x00030003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B1114 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000B0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0A10 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar4ComTree[] = {
    { 10, { .data = 0x000B070D }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000E0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar5ComTree[] = {
    { 10, { .data = 0x00030003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000D0004 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100208 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00110001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00100001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar6ComTree[] = {
    { 10, { .data = 0x0003080A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100809 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120607 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000F0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00110001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00120002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoStar7ComTree[] = {
    { 10, { .data = 0x0003070A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050005 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00100909 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00120407 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030006 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb6_itemRKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb6_itemRKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb6_itemRKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb6_itemRKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb6_itemRKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb6_itemRKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_itemRKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb6_itemRKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x01428A14 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar0ComTree[] = {
    { 15, { .data = 0x00010D0F }, { .data = 0x0C993264 } },
    { 15, { .data = 0x0002090D }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar1ComTree[] = {
    { 15, { .data = 0x0002060A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar2ComTree[] = {
    { 15, { .data = 0x0006070C }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar3ComTree[] = {
    { 15, { .data = 0x00030003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00060004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B1114 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000B0003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar4ComTree[] = {
    { 15, { .data = 0x000B070D }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000E0003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000F0003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar5ComTree[] = {
    { 15, { .data = 0x00030003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00050005 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x000D0004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100208 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00110001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar6ComTree[] = {
    { 15, { .data = 0x0003080A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100809 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120607 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoSelfStar7ComTree[] = {
    { 15, { .data = 0x0003070A }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00040003 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00050005 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100909 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120407 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar0ComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar1ComTree[] = {
    { 15, { .data = 0x00020005 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00060006 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar3ComTree[] = {
    { 15, { .data = 0x000B0A10 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x000B0006 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x000F0004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00100001 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar6ComTree[] = {
    { 15, { .data = 0x000F0004 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00110001 }, { .data = 0x0C993264 } },
    { 15, { .data = 0x00120002 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_itemRKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x00030006 }, { .data = 0x0C993264 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode *mb6_itemRKinokoSelfComTree[] = { mb6_itemRKinokoSelfStar0ComTree, mb6_itemRKinokoSelfStar1ComTree, mb6_itemRKinokoSelfStar2ComTree, mb6_itemRKinokoSelfStar3ComTree, mb6_itemRKinokoSelfStar4ComTree, mb6_itemRKinokoSelfStar5ComTree, mb6_itemRKinokoSelfStar6ComTree, mb6_itemRKinokoSelfStar7ComTree };

DecisionTreeNonLeafNode *mb6_itemRKinokoTargetComTree[] = { mb6_itemRKinokoTargetStar0ComTree, mb6_itemRKinokoTargetStar1ComTree, mb6_itemRKinokoTargetStar2ComTree, mb6_itemRKinokoTargetStar3ComTree, mb6_itemRKinokoTargetStar4ComTree, mb6_itemRKinokoTargetStar5ComTree, mb6_itemRKinokoTargetStar6ComTree, mb6_itemRKinokoTargetStar7ComTree };

DecisionTreeNonLeafNode mb6_itemStarYokeComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb6_itemWarpBlockComTree } }
};

DecisionTreeNonLeafNode mb6_comShopKeyComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_comShopKeyComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_comShopItemComTree0[] = {
    { 2, { .data = 0x00000058 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_comShopItemComTree1[] = {
    { 2, { .data = 0x0000009F }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree0Star0WalkMin[] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree0Star0[] = {
    { 9, { .data = 0x00000002 }, { .node_data = mb6_comShopEnterComTree0Star0WalkMin } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree0[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb6_comShopEnterComTree0Star0 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree1Star6WalkMin[] = {
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree1Star6[] = {
    { 9, { .data = 0x00000007 }, { .node_data = mb6_comShopEnterComTree1Star6WalkMin } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree1Star5WalkMin[] = {
    { 1, { .data = 0x00000028 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00028A1E } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree1Star5[] = {
    { 9, { .data = 0x00000004 }, { .node_data = mb6_comShopEnterComTree1Star5WalkMin } },
    { 1, { .data = 0x00000032 }, { .data = 0x0C96A846 } },
    { 1, { .data = 0x00000028 }, { .data = 0x0A11A0BC } },
    { 1, { .data = 0x0000001E }, { .data = 0x064C9932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x02879432 } }
};

DecisionTreeNonLeafNode mb6_comShopEnterComTree1[] = {
    { 2, { .data = 0x00000020 }, { .node_data = mb6_comShopEnterComTree1Star5 } },
    { 2, { .data = 0x00000040 }, { .node_data = mb6_comShopEnterComTree1Star6 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

s32 mb6_comShopCancelF = 0;

/* Item priorities and weights for each star position. */
u8 mb6_comShopItemOrderMario[] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1
};

u8 mb6_comShopItemOrderLuigi[] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5
};

u8 mb6_comShopItemOrderPeach[] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1
};

u8 mb6_comShopItemOrderYoshi[] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1
};

u8 mb6_comShopItemOrderWario[] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1
};

u8 mb6_comShopItemOrderDk[] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1
};

u8 mb6_comShopItemOrderWaluigi[] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1
};

u8 mb6_comShopItemOrderDaisy[] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5
};

u8 *mb6_comShopItemOrderTbl[] = { mb6_comShopItemOrderMario, mb6_comShopItemOrderLuigi, mb6_comShopItemOrderPeach, mb6_comShopItemOrderYoshi, mb6_comShopItemOrderWario, mb6_comShopItemOrderDk, mb6_comShopItemOrderWaluigi, mb6_comShopItemOrderDaisy };

s8 mb6_comShopItemRateMario[] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb6_comShopItemRateLuigi[] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0
};

s8 mb6_comShopItemRatePeach[] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10
};

s8 mb6_comShopItemRateYoshi[] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10
};

s8 mb6_comShopItemRateWario[] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10
};

s8 mb6_comShopItemRateDk[] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb6_comShopItemRateWaluigi[] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10
};

s8 mb6_comShopItemRateDaisy[] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10
};

s8 *mb6_comShopItemRateTbl[] = { mb6_comShopItemRateMario, mb6_comShopItemRateLuigi, mb6_comShopItemRatePeach, mb6_comShopItemRateYoshi, mb6_comShopItemRateWario, mb6_comShopItemRateDk, mb6_comShopItemRateWaluigi, mb6_comShopItemRateDaisy };

DecisionTreeNonLeafNode *mb6_comShopKeyComTree[] = { mb6_comShopKeyComTree0, mb6_comShopKeyComTree1 };

DecisionTreeNonLeafNode *mb6_comShopItemComTree[] = { mb6_comShopItemComTree0, mb6_comShopItemComTree1 };

DecisionTreeNonLeafNode *mb6_comShopEnterComTree[] = { mb6_comShopEnterComTree0, mb6_comShopEnterComTree1, NULL };

/* Runtime board state. */
static Object *mb6_starGuideBaseMdl;
static s32 mb6_starGuideBaseMdlPad; /* Unused word between model state and the following array. */
static Object *mb6_starGuideMdl[8];
static Process *mb6_starGuideHoverProc[8];
static s32 mb6ev_starGuideInProc;
static Object *mb6ev_starGuideInMdl;
static Unk3 *mb6_branchStickHelp;
static Unk3 *mb6_branchBtnHelp;
static Unk3 *mb6_branchMapScrollHelp;
static Unk3 *mb6_branchMapOverheadHelp;
static Unk3 *mb6_branchItemHelp;
static s32 mb6_comTeresaType;
static s32 mb6_comTeresaTarget;
static Object *mb6_teresaGuideBaseMdl;
static Object *mb6_teresaGuideMdl[1];
static Object *mb6_bankCoinBaseMdl;
static Object *mb6_bankCoinMdl[10];
static Object *mb6_gateBaseMdl;
static Object *mb6_gateMdl[2];
static Object *mb6_holeMdl[3];
static Object *mb6_bombMdl;
static Object *mb6_bridgeMdl[2];
static s32 mb6ev_rouletteStopDir;
static s32 mb6ev_rouletteDir;
static s32 mb6ev_shopHostNo;
static s32 mb6ev_shopItemRow;
static u8 *mb6ev_shopItemEnableTbl;
static Object *mb6ev_teresaCoinMdl;
static s32 mb6ev_itemPhoneWaveSpr;
static s32 mb6ev_tereYokePlayer;
static s32 mb6ev_tereYokeSparkSpr;
static Object *mb6ev_koopaCardCoinMdl;
static Object *mb6ev_koopaCardMdl;
static s32 mb6_comExchangeBoxTarget;
static s32 mb6_comRobBoxTarget;
static Object *mb6ev_gambleCoinMdl;
static s32 mb6ev_gambleCoinMdlPad; /* Unused word between model state and the following array. */
static s32 mb6ev_after5GrpId[4];
static Object *mb6ev_after5EffMdl;
static s32 mb6ev_after5EffMdlPad; /* Unused word between model state and the following array. */
static Object *mb6ev_kinokoMarkMdl[4];
static omObjData *mb6ev_kinokoMarkObj[4];
static s32 mb6_comRKinokoTarget;
static s32 mb6_comNKinokoTarget;

/* Definitions stay beside their users to preserve the order of .rodata literals. */
extern const u8 mb6_padBitTbl[];
extern const ChanceTable mb6ev_rouletteComHitRateTbl;
extern const ChanceTable mb6ev_rouletteComJumpRateTbl;
extern const ChanceTable mb6ev_rouletteLinkTbl;
extern const ChanceTable mb6ev_rouletteLinkIdxTbl;
extern const char mb6ev_numFmtStr[];
extern const ModelIdTable mb6ev_bombExplodeMdlTbl;
extern const MessageTable mb6ev_bombCountMesTbl;
extern const MasuIdTable mb6ev_holeMasuTbl;

void MBDDebugCheatKill(Object *arg0, Vec *arg1, s32 arg2);
void MB6_BombKill(void);

s16 MB6Ev_StarGuideMasuGet(void) {
    return mb6ev_starGuideMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void MB6Ev_StarShuffle(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < mb6ev_starOrderGroupTbl[idx2]) {
                continue;
            }
            if (idx2 < mb6ev_starOrderGroupTbl[idx1]) {
                continue;
            }
            {
                s32 temp = mb6ev_starOrderTbl[idx1];
                mb6ev_starOrderTbl[idx1] = mb6ev_starOrderTbl[idx2];
                mb6ev_starOrderTbl[idx2] = temp;
                temp = mb6ev_starOrderGroupTbl[idx1];
                mb6ev_starOrderGroupTbl[idx1] = mb6ev_starOrderGroupTbl[idx2];
                mb6ev_starOrderGroupTbl[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = mb6ev_starOrderTbl[i];
    }
}

void MB6Ev_StarNextPos(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        MB6Ev_StarShuffle();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void MB6Ev_StarMasuInit(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(mb6ev_starFlag[i]);
    }
    MBMasuTypeSet(mb6ev_starMasu[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(mb6ev_starFlag[loc->star_spawn_indices[loc->current_star_spawn]]);
}

s32 MB6Ev_StarCheck(s16 arg0) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        if (arg0 == mb6ev_starMasu[i]) {
            if (i == loc->star_spawn_indices[loc->current_star_spawn]) {
                loc->unk_0E = mb6ev_starFlag[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void MB6Ev_StarGuideIn(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    mb6ev_starGuideInMdl = MBModelCreate(0x3A, NULL);
    model = mb6ev_starGuideInMdl;
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
    mb6ev_starGuideInProc = 0;
    omDelPrcObj(NULL);
}

void MB6Ev_StarGuideJumpExec(omObjData **arg) {
    omObjData *s0 = *arg;

    s0->scale.y = 4.0f;
    s0->scale.z = -0.6f;
    HuPrcSleep(3);
    while (s0->scale.z != 0.0f) {
        HuPrcVSleep();
    }
}

void MB6Ev_StarMapView(void) {
    struct UnkMBGuideData *data;
    GW_SYSTEM *loc = &GwSystem;
    SpaceData *space;
    s32 idx;

    mbTurnUnkF = 0;
    data = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(data->obj, 2, 0xF, mb6ev_starGuideFaceTbl[0]);
    MBPlayerIconMdlSet();
    MBModelDispOff(mb6_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    MBBackThreadPriLowSet();
    MBCameraSpeedDivSet(3.0f);
    MB6Ev_StarGuideJumpExec((omObjData **)data);
    HuWinMesSet(
        data->amount,
        (loc->current_star_spawn == 0 && GWBoardFlagCheck(4) == 0)
            ? (((loc->current_board_index == BOARD_SPINY_DESERT) ? 0x5E09 : 0) | 0x5E00)
            : (((loc->current_board_index == BOARD_SPINY_DESERT) ? 0x5E09 : 0) | 0x5E01),
        -1, -1);
    HuWinExOpen(data->amount, 1);
    HuAudFXPlay(0x2A7);
    MBWinComKeyAllWaitKeep(data->amount);
    MBMotionShiftSet(data->obj, -1, 0, 6, 2);
    HuWinExClose(data->amount, 1);
    Hu3DMotionReset(data->obj->omObj1->model[0]);
    if (loc->current_board_index != BOARD_SPINY_DESERT || (rand8() & 1)) {
        space = MBMasuGet(mb6ev_starGuideMasu[loc->star_spawn_indices[loc->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    idx = MBRand(7.0f);
    MBGuideFaceSet(data->obj, mb6ev_starGuideFaceTbl[idx]);
    MBMotionSet(data->obj, -1, 2);
    if (loc->current_board_index != BOARD_SPINY_DESERT) {
        Process *prc = omAddPrcObj(MB6Ev_StarGuideIn, 0x4800, 0, 0);
        mb6ev_starGuideInProc = (s32)prc;
        prc->user_data = space;
        HuPrcSleep(30);
    } else {
        mb6ev_starGuideInProc = 0;
    }
    HuWinMesSet(data->amount, mb6ev_starGuideMesTbl[idx], -1, -1);
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
    AuraKill(mb6ev_starGuideInMdl->omObj1->model[0]);
    MBModelKill(mb6ev_starGuideInMdl);
    MBModelDispOn(mb6_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBGuideKill(data);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB6Ev_StarGet(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x7F) {
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
    if (mb6ev_starGetTeresaF != 0) {
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
    if (mb6ev_starGetTeresaF != 0) {
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

void MB6Ev_StarGetExec(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(MB6Ev_StarGet, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void MB6_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void MB6_MapScrollCancel(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void MB6_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mb6_branchStickHelp = MBHelpWinCreate(0, 0x92, 1);
    mb6_branchBtnHelp = MBHelpWinCreate(1, 0xA0, 1);
    mb6_branchItemHelp = MBHelpWinCreate(0xD, 0xAE, 1);
    mb6_branchMapScrollHelp = MBHelpWinCreate(3, 0xBC, 1);
    mb6_branchMapOverheadHelp = MBHelpWinCreate(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

void MB6_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBHelpWinKill(mb6_branchStickHelp);
    MBHelpWinKill(mb6_branchBtnHelp);
    MBHelpWinKill(mb6_branchItemHelp);
    MBHelpWinKill(mb6_branchMapScrollHelp);
    MBHelpWinKill(mb6_branchMapOverheadHelp);
}

s32 MB6_ComShopItemChoice(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                var_s2 = MB6_ComShopItemDecide();
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

s32 MB6_ComShopEnterChoice(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                var_s2 = 1; // dead store; matches MBKettouTargetChoiceGet
                var_s2 = MB6_ComShopEnterDecide();
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

void MB6_ComTeresaTypeDecide(void) {
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
                mb6_comTeresaType = 1;
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
        mb6_comTeresaType = 0;
    } else {
        mb6_comTeresaType = 2;
    }
}

void MB6_ComTeresaTargetDecide(void) {
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
    MB6_ComTeresaTypeDecide();
    if (mb6_comTeresaType == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                mb6_comTeresaTarget = order[i];
                break;
            }
        }
    } else if (mb6_comTeresaType == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                mb6_comTeresaTarget = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        mb6_comTeresaType = 2;
    }
}

s32 MB6_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                if (arg1 == 0) {
                    MB6_ComTeresaTargetDecide();
                    var_s2 = mb6_comTeresaType + 1;
                } else {
                    var_s2 = mb6_comTeresaTarget + 1;
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

s32 MB6_ComTeresaTypeChoice(u8 *arg0) {
    return MB6_ComTeresaChoice(arg0, 0, 1);
}

s32 MB6_ComTeresaPlayerChoice(u8 *arg0) {
    return MB6_ComTeresaChoice(arg0, 1, 0);
}

void MB6_BoardInit(void) {
    GwSystem.current_board_index = BOARD_WALUIGIS_ISLAND;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(boardcall, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
}

void MB6_SaveInit(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    MB6Ev_StarShuffle();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 0;
    GwSystem.boardData.halfWordBytes[1] = 5;
    GwSystem.boardData.halfWordBytes[2] = -1;
    MB6Ev_ChangeMasuTypeRoll();
    omOvlReturnEx(1);
}

void MB6_ObjectSetup(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(0x12, 0x23F, 0x14, 0);
    MBMasuBlockTblExtSet(mb6_masuBlockExtTbl);
    MBMasuBlockTblSet(mb6_masuBlockTbl);
    space = MBMasuGet(0x6C);
    MBVecDirGet(&space->coords, &MBMasuGet(0x90)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x79);
    MBVecDirGet(&space->coords, &MBMasuGet(0x8C)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &MB6Ev_Teresa); // boo event
    MBItemHookSet(1, &MB6Ev_ItemMajinLamp); // magic lamp
    MBItemHookSet(9, &MB6Ev_ItemMajinLampStar);
    MBItemHookSet(2, &MB6Ev_ItemWarpBlock); // warp block
    MBItemHookSet(3, &MB6Ev_ItemRobBox); // plunder chest
    MBItemHookSet(4, &MB6Ev_KSuitStart); // activate bowser suit
    MBItemHookSet(5, &MB6Ev_KSuitEnd); // when landing on a space as bowser suit
    MBItemHookSet(6, &MB6Ev_ItemKinoko); // mushroom/golden mushroom/bowser suit
    MBItemHookSet(7, &MB6Ev_ItemShake); // dueling glove/boo bell (?)
    MBItemHookSet(8, &MB6Ev_ItemPhoneMove);
    MBItemHookSet(0xA, &MB6Ev_ItemNKinoko); // poison mushroom
    MBItemHookSet(0xB, &MB6Ev_ItemRKinoko); // reverse mushroom
    MBItemHookSet(0xE, &MB6Ev_ItemShopPhone);
    MBItemHookSet(0xF, &MB6Ev_ItemKoopaPhone);  // bowser phone
    MBItemHookSet(0x10, &MB6Ev_ItemStarYoke); // lucky lamp
    MBItemHookSet(0x11, &MB6Ev_ItemKeyManUse); // skeleton key throw away event
    MBItemHookSet(0x12, &MB6Ev_ItemNullUse); // boo repellant/koopa kard thrown away
    MBItemHookSet(0x13, &MB6Ev_ItemExchangeBox); // barter box
    MBItemHookSet(0x14, &MB6Ev_ItemGambleCoin); // game guy coin
    MBItemHookSet(0x15, &MB6Ev_ItemAfter5); // wacky watch
    MBItemHookSet(0xC, &MB6Ev_ItemKoopaNKinoko);
    MBItemHookSet(0xD, &MB6Ev_ItemKoopaRKinoko);
    MBComItemDecideHookSet(MB6_ComItemDecide);

    for (i = 0; i < ARRAY_COUNT(mb6ev_starGuideMasu); i++) {
        MBMasuStarSet(i, mb6ev_starGuideMasu[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        MB6Ev_StarNextPos();
    }

    MB6Ev_StarMasuInit();
    MB6_StarGuideCreateAll();
    MB6_TeresaGuideCreateAll();
    MB6_BankCoinCreateAll();
    MB6_GateCreateAll();
    MB6_BankMapIconAddAll();
    MB6_ShopMapIconAddAll();
    MB6_HoleExitCreate();
    MB6_HoleCreateAll();
    MB6_BombCreate();
    MB6_BridgeCreateAll();
    MB6Ev_ChangeMasuTypeSet();
    MB6Ev_KinokoMarkCreateAll();
    MBMasuTypeListCreate();
}

void MB6_Create(void) {
    HuAudSeqPlay(0x1D);
    mbBoardMusId = 0x1D;
    MBBoardParamSet(0x1D);
    Hu3DCamInit(2);
    MB6_ObjectSetup();
    MBMasuEventTblAdd(mb6_commonEventTbl);
    MBMasuEventTblAdd(mb6_specialEventTbl);
    MBHatenaFuncSet(&MB6Ev_Hatena);
    MBMasuEventTblAdd(mb6_teresaEventTbl);
    MBMasuEventTblAdd(mb6_turnStatusEventTbl);
    MBStart(0);
}

void MB6_BoardReload(void) {
    Hu3DCamInit(1);
    MB6_ObjectSetup();
    MBStart(1);
}

void MB6_StarGuideCreate(s16 arg0) {
    Object *obj;

    if (mb6_starGuideMdl[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    AuraCreate(obj->omObj1->model[0]);
    if (mb6_starGuideBaseMdl == NULL) {
        mb6_starGuideBaseMdl = obj;
    }
    mb6_starGuideMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    mb6_starGuideHoverProc[arg0] = MBModelHoverCreate(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb6_starGuideMdlMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xB, obj, mb6_starGuideMapIconOfsTbl[arg0][0], mb6_starGuideMapIconOfsTbl[arg0][1]);
}

void MB6_StarGuideKill(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        Process *prc = mb6_starGuideHoverProc[i];

        if (prc != NULL) {
            omDelPrcObj(prc);
            mb6_starGuideHoverProc[i] = NULL;
        }
    }
    MB6_BombKill();
}

void MB6_StarGuideCreateAll(void) {
    s32 i;

    mb6_starGuideBaseMdl = 0;
    for (i = 0; i < 8; i++) {
        mb6_starGuideMdl[i] = 0;
        mb6_starGuideHoverProc[i] = NULL;
        MBKinokoEffKillHookSet(MB6_StarGuideKill);
        if (!GWBoardFlagCheck(mb6_starGuideFlagTbl[i])) {
            MB6_StarGuideCreate(i);
        }
    }
}

void MB6_TeresaGuideCreate(s16 arg0) {
    Object *obj;

    if (mb6_teresaGuideMdl[arg0] != NULL) {
        return;
    }
    if (mb6_teresaGuideBaseMdl == NULL) {
        obj = MBModelCreate(0xA, NULL);
        Hu3DModelTPLvlInit(obj->omObj1->model[0]);
        Hu3DModelTPLvlInit(obj->omObj2->model[0]);
        mb6_teresaGuideBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb6_teresaGuideBaseMdl);
    }
    MBModelDispOff(obj);
    mb6_teresaGuideMdl[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb6_teresaGuideMasuTbl[arg0])->coords);
    MBMapFullIconMdlAdd(0xA, obj, mb6_teresaGuideMapIconOfsTbl[arg0][0], mb6_teresaGuideMapIconOfsTbl[arg0][1]);
}

void MB6_TeresaGuideCreateAll(void) {
    s32 i;

    mb6_teresaGuideBaseMdl = 0;
    for (i = 0; i <= 0; i++) {
        mb6_teresaGuideMdl[i] = NULL;
        MB6_TeresaGuideCreate(i);
    }
}

void MB6_BankCoinHide(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(mb6_bankCoinMdl[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(mb6_bankCoinMdl[i * 5 + j]);
        }
    }
}

void MB6_BankCoinCreate(s16 arg0) {
    Object *obj;

    if (mb6_bankCoinMdl[arg0] != NULL) {
        return;
    }
    if (mb6_bankCoinBaseMdl == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        mb6_bankCoinBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb6_bankCoinBaseMdl);
    }
    mb6_bankCoinMdl[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb6_bankCoinMasuTbl[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &mb6_bankCoinOfsTbl[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = mb6_bankCoinRotTbl[arg0 % 5].x;
    obj->omObj1->rot.z = mb6_bankCoinRotTbl[arg0 % 5].z;
    MBModelDispOff(obj);
}

void MB6_BankCoinCreateAll(void) {
    s32 i;

    mb6_bankCoinBaseMdl = 0;
    for (i = 0; i < 0xA; i++) {
        mb6_bankCoinMdl[i] = NULL;
        MB6_BankCoinCreate(i);
    }
    MB6_BankCoinHide();
}

void MB6_GateCreate(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (mb6_gateMdl[arg0] != NULL) {
        return;
    }
    if (mb6_gateBaseMdl == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(mb6_gateMdlTbl[board], mb6_gateMotTbl[board]);
        MBModelTempAllocFree(obj);
        mb6_gateBaseMdl = obj;
    } else {
        obj = MBModelLinkCreate(mb6_gateBaseMdl);
    }
    mb6_gateMdl[arg0] = obj;
    obj->flags |= 2;
    Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(mb6_gateMasuTbl[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(mb6_gateDirMasuTbl[arg0][0]);
        SpaceData *masuB = MBMasuGet(mb6_gateDirMasuTbl[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    MBMapFullIconMdlAdd(0xC, obj, mb6_gateMapIconOfsTbl[arg0][0], mb6_gateMapIconOfsTbl[arg0][1]);
}

void MB6_GateCreateAll(void) {
    s32 i;

    mb6_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        mb6_gateMdl[i] = NULL;
        MB6_GateCreate(i);
    }
}

void MB6_GateOpenSeProc(void) {
    HuPrcSleep(mb6_gateOpenDelayTbl[GwSystem.current_board_index]);
    HuAudFXPlay((s16)mb6_gateOpenDelaySeTbl[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void MB6_GateOpen(s32 arg0, s32 arg1) {
    MBMotionSet(mb6_gateMdl[arg0], arg1 - 1, 0);
    Hu3DMotionAttrSet(mb6_gateMdl[arg0]->omObj1->model[0], 5, 0);
    if (mb6_gateOpenSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb6_gateOpenSeTbl[GwSystem.current_board_index]);
    }

    if (mb6_gateOpenDelaySeTbl[GwSystem.current_board_index] != -1) {
        omAddPrcObj(MB6_GateOpenSeProc, 0x1000, 0, 0);
    }
}

void MB6_GateCloseProc(void) {
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
    Hu3DMotionAttrSet(mb6_gateMdl[index]->omObj1->model[0], 1, 4);

    if (mb6_gateCloseSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb6_gateCloseSeTbl[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

void MB6_GateClose(s32 arg) {
    Process *temp = omAddPrcObj(MB6_GateCloseProc, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void MB6_BankMapIconAddAll(void) {
    s32 i;

    mb6_gateBaseMdl = 0;
    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(8, &MBMasuGet(mb6_bankMapIconMasuTbl[i])->coords,
                                         mb6_bankMapIconOfsTbl[i][0], mb6_bankMapIconOfsTbl[i][1]);
    }
}

void MB6_ShopMapIconAddAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(9, &MBMasuGet(mb6_shopMapIconMasuTbl[i])->coords,
                                         mb6_shopMapIconOfsTbl[i][0], mb6_shopMapIconOfsTbl[i][1]);
    }
}

void MB6_HoleExitCreate(void) {
    SpaceData *masu = MBMasuGet(0x8B);
    Object *obj = MBModelFileCreate(0x130186, -1, 1.0f, 0, 0);

    MBModelTempAllocFree(obj);
    mb6_holeExitMdl = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void MB6_HoleCreateAll(void) {
    s32 i;
    Object *obj;

    for (i = 0; i < 3; i++) {
        if (i == 0) {
            obj = MBModelFileCreate(0x130185, -1, 1.0f, 0, 0);
            MBModelTempAllocFree(obj);
            mb6_holeBaseMdl = obj;
        } else {
            obj = MBModelLinkCreate(mb6_holeBaseMdl);
        }
        mb6_holeMdl[i] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBMasuGet(mb6_holeMasuTbl[i])->coords);
    }
}

void MB6_BombCountUpdate(void) {
    Hu3DAnimBankSet(mb6_bombAnim, (u8)GwSystem.boardData.bytes[3]);
    Hu3DModelRemakeStatic(mb6_bombMdl->omObj1->model[0]);
}

void MB6_BombAnimKill(void) {
    if (mb6_bombAnimData != NULL) {
        DataClose(mb6_bombAnimData);
        mb6_bombAnimData = NULL;
    }
    if (mb6_bombAnim != -1) {
        Hu3DAnimModelKill(mb6_bombAnim);
        mb6_bombAnim = -1;
    }
}

// Keep rodata definitions interleaved with functions to preserve the original constant order.
const u8 mb6_padBitTbl[4] = { 1, 2, 4, 8 };

void MB6_BombCreate(void) {
    Object *obj = MBModelFileCreate(0x130189, -1, 1.0f, 0, 0);
    void *data;

    mb6_bombMdl = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x94)->coords);
    data = DataRead(0x13018A);
    mb6_bombAnimData = data;
    mb6_bombAnim = Hu3DAnimCreate(Hu3DData[obj->omObj1->model[0]].hmf, data, 0, "count_1_DEF");
    MB6_BombCountUpdate();
}

void MB6_BombKill(void) {
    MB6_BombAnimKill();
}

void MB6_BridgeCreateAll(void) {
    s32 i;
    Object *obj;
    SpaceData *masuA;

    for (i = 0; i < 2; i++) {
        Object **objArr = mb6_bridgeMdl;
        s16 *coordsArr = mb6_bridgeMasuTbl;
        SpacePair *masuAArr = mb6_bridgeDirMasuTbl;
        SpacePair *masuBArr = (SpacePair *)&mb6_bridgeDirMasuTbl[0][1];

        if (i == 0) {
            obj = MBModelFileCreate(0x130187, -1, 1.0f, 0, 0);
            MBModelTempAllocFree(obj);
            mb6_bridgeBaseMdl = obj;
        } else {
            obj = MBModelLinkCreate(mb6_bridgeBaseMdl);
        }
        objArr[i] = obj;
        obj->flags |= 2;
        masuA = MBMasuGet(coordsArr[i]);
        HuVecCopy3F(&obj->coords, &masuA->coords);
        masuA = MBMasuGet(masuAArr[i][0]);
        MBVecDirGet(&masuA->coords, &MBMasuGet(masuBArr[i][0])->coords, &obj->rot);
        if (GwSystem.boardData.halfWordBytes[0] == i) {
            Hu3DMotionTimeSet(obj->omObj1->model[0], 1000.0f);
        }
        Hu3DMotionAttrSet(obj->omObj1->model[0], 6, 1);
    }
}

void MB6Ev_Branch1(void) {
    MBMoveNextMasuSet(-1, 1, 0xA);
    MBMoveBackMasuSet(-1, 1, 0xA);
}

void MB6Ev_ActionTimeTitleProc(void) {
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

Process *MB6Ev_ActionTimeTitleCreate(void) {
    return omAddPrcObj(MB6Ev_ActionTimeTitleProc, 0x1000, 0, 0);
}

void MB6Ev_RouletteArrowProc(void) {
    s32 masuTable[4] = { 0x6E, 0x6F, 0x98, 0x6D };
    u8 delayTable[10] = { 2, 4, 4, 4, 8, 8, 8, 8, 8, 8 };
    Process *prc = HuPrcCurrentGet();
    Object *model;
    SpaceData *space;
    s32 idx;
    s32 playedSfx = 0;
    s32 delay;

    model = MBModelFileCreate(0x130188, -1, 1.1f, 0, 0);
    MBModelTempAllocFree(model);
    delay = delayTable[MBRand(10.0f)];
    idx = MBRand(4.0f);

    while (prc->user_data == NULL) {
        idx++;
        idx &= 3;
        mb6ev_rouletteDir = idx;
        space = MBMasuGet(masuTable[idx]);
        HuVecCopy3F(&model->coords, &space->coords);
        model->coords.z -= 1.0f;
        model->rot.x = sindf(180 - (idx * 90));
        model->rot.z = cosdf(180 - (idx * 90));
        HuAudFXPlay(0x1B6);
        HuPrcSleep(delay - 1);
    }

    mb6ev_rouletteStopDir = idx;
    HuPrcSleep(10);
    idx = 0;

    if ((s32)prc->user_data != 2) {
        while ((s32)prc->user_data != 2) {
            if (playedSfx == 0) {
                HuAudFXPlay(0x1B7);
                playedSfx = 1;
            }
            idx++;
            if (idx & 2) {
                MBModelDispOff(model);
            } else {
                MBModelDispOn(model);
            }
            HuPrcVSleep();
        }
    }

    MBModelKill(model);
    prc->user_data = NULL;
    omDelPrcObj(NULL);
}

void MB6Ev_RouletteExec(void) {
    StarChaseWork work;
    Unk3 *helpWin;
    s16 msgWin;
    SpaceData *starMasu = MBMasuGet(0x99);
    GW_PLAYER *player = MBPlayerGet(-1);
    Process *starPrc;
    s16 comResult;
    s32 playerIdx;
    s32 i;

    playerIdx = GwSystem.current_player_index;

    work.chaseChanceA = mb6ev_rouletteComHitRateTbl;
    work.chaseChanceB = mb6ev_rouletteComJumpRateTbl;
    comResult = 0;
    MBStatusHideAll();
    MBSaiNumKill(playerIdx);
    MBVecDirGet(&player->player_obj->coords, &starMasu->coords, &work.dir);
    HuPrcChildLink(HuPrcCurrentGet(), MBVecRotLerpCreate(&player->player_obj->rot, &work.dir, &player->player_obj->rot, 5));
    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.0f));
    HuPrcChildWatch();
    HuVecCopy3F(&work.pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&work.pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&work.pos, &starMasu->coords, &work.pos, 30));
    HuPrcChildWatch();
    starPrc = omAddPrcObj(MB6Ev_RouletteArrowProc, 0x1000, 0, 0);
    HuPrcChildLink(HuPrcCurrentGet(), MB6Ev_ActionTimeTitleCreate());
    HuPrcSleep(30);
    msgWin = HuWinCreate(0x6E, 0xB2, 0x64, 0x18, 0, 0);
    HuWinBGTPLvlSet(msgWin, 0x100);
    HuWinBGColSet(msgWin, 0x8C, 0xC8, 0x3C);
    helpWin = MBHelpWinCreate(0x14, 0xB4, 1);
    HuPrcChildWatch();

    if (MBPlayerComCheck(-1) != 0) {
        if (MBComTreeExec(mb6ev_rouletteDir1ComTree) != 0) {
            comResult = 1;
            if (MBComTreeExec(mb6ev_rouletteDir3ComTree) != 0) {
                comResult |= 2;
            } else {
                comResult = 1;
            }
        } else {
            comResult = 0;
        }
    }
    i = 0;

    while (1) {
        if (MBPlayerComCheck(-1) != 0) {
            if ((mb6ev_rouletteDir == comResult && MBRand(100.0f) < work.chaseChanceA.entries[player->cpu_difficulty])) {
                goto move;
            }
            if (MBRand(100.0f) < work.chaseChanceB.entries[player->cpu_difficulty]) {
                goto move;
            }
            goto sleep;
        }
        if (!(ContBtnDown[GwPlayer[playerIdx].pad] & A_BUTTON)) {
            goto sleep;
        }

    move:
        PlayerFXPlay(0x3A, playerIdx);
        MBPlayerMotionSet(-1, 2, 0);
        MBModelJumpSet(player->player_obj, 16.0f, -0.95f);
        HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(
                                              &player->player_obj->coords, &starMasu->coords, &player->player_obj->coords, 31));
        break;

    sleep:
        HuPrcVSleep();
        i++;
        if (i >= 150) {
            break;
        }
    }

    MBHelpWinKill(helpWin);
    HuWinKill(msgWin);

    if (i == 150) {
        starPrc->user_data = (void *)2;
        MBDlgResultWinExec(0x1000);
    } else {

        HuPrcChildWatch();
        MBPlayerVibrate(-1, 2);
        MBPlayerMotionSet(-1, -1, 2);
        PlayerFXPlay(0x31, playerIdx);
        starPrc->user_data = (void *)1;
        HuPrcSleep(40);
        starPrc->user_data = (void *)2;

        if (mb6ev_rouletteStopDir != 2) {
            s16 eventId;
            s16 eventArg;

            MBMoveMasuSet(-1, 0x15, 0);
            work.eventTableA = mb6ev_rouletteLinkTbl;
            work.eventTableB = mb6ev_rouletteLinkIdxTbl;
            eventId = ((s16 *)work.eventTableA.entries)[mb6ev_rouletteStopDir * 2 + 1];
            eventArg = ((s16 *)work.eventTableB.entries)[mb6ev_rouletteStopDir * 2 + 1];
            MBMoveNextMasuSet(-1, eventId, eventArg);
            MBCameraFocusModeSet(1);
            MBStatusShowAll();
            MBSaiNumShow(playerIdx);
            HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
            HuPrcChildWatch();
            return;
        } else {
            starMasu = MBMasuGet(0x77);
            MBVecDirGet(&player->player_obj->coords, &starMasu->coords, &player->player_obj->rot);
            PlayerFXPlay(0x3A, playerIdx);
            MBPlayerMotionSet(-1, 2, 0);
            MBModelJumpSet(player->player_obj, 15.0f, -2.0f);
            HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(
                                                  &player->player_obj->coords, &starMasu->coords, &player->player_obj->coords, 14));
            HuPrcChildWatch();
            MBPlayerMotionSet(-1, -1, 2);
            PlayerFXPlay(0x31, playerIdx);
        }
    }

    MBMoveNextMasuSet(-1, 2, 0);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&work.pos, &player->player_obj->coords, &work.pos, 20));
    HuPrcChildWatch();

    MBCameraFocusModeSet(1);
    MBStatusShowAll();
    MBSaiNumShow(playerIdx);
    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
    HuPrcChildWatch();
}

void MB6Ev_Branch2(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch2Masu, (BranchPair *)mb6ev_branch2Link, mb6ev_branch2ComTree);
    if (player->nlink == 0x15) {
        MB6Ev_RouletteExec();
    }
    omDelPrcObj(NULL);
}

void MB6Ev_Branch3(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5C && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 3, 4);
        player->rev &= ~1;
    } else {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch3Masu, (BranchPair *)mb6ev_branch3Link, mb6ev_branch3ComTree);
    }
}

void MB6Ev_Branch4(void) {
    MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch4Masu, (BranchPair *)mb6ev_branch4Link, mb6ev_branch4ComTree);
    omDelPrcObj(NULL);
}

void MB6Ev_Branch5(void) {
    MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch5Masu, (BranchPair *)mb6ev_branch5Link, mb6ev_branch5ComTree);
    omDelPrcObj(NULL);
}

void MB6Ev_Branch6(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[0] == 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch6Masu, (BranchPair *)mb6ev_branch6Link, mb6ev_branch6ComTree);
    } else {
        s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

        if (masu == 0x38) {
            MBMoveNextMasuSet(-1, 0xE, 0);
        } else {
            MBMoveNextMasuSet(-1, 0xD, 3);
            player->rev |= 1;
        }
    }
    omDelPrcObj(NULL);
}

void MB6Ev_Branch7(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[0] == 1) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch7Masu, (BranchPair *)mb6ev_branch7Link, mb6ev_branch7ComTree);
    } else {
        s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

        if (masu == 0x1C) {
            MBMoveNextMasuSet(-1, 6, 0);
        } else {
            MBMoveNextMasuSet(-1, 5, 4);
            player->rev |= 1;
        }
    }
    omDelPrcObj(NULL);
}

void MB6Ev_Branch8(void) {
    MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch8Masu, (BranchPair *)mb6ev_branch8Link, mb6ev_branch8ComTree);
    omDelPrcObj(NULL);
}

void MB6Ev_Branch9(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x96 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 7, 0);
        player->rev &= ~1;
    } else {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch9Masu, (BranchPair *)mb6ev_branch9Link, mb6ev_branch9ComTree);
    }
    omDelPrcObj(NULL);
}

void MB6Ev_Branch10(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu != 0x3F) {
        MBMoveNextMasuSet(-1, 0x11, 0);
        player->rev |= 1;
    } else {
        MBDlgResultWinExec(0xE01);
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch10Masu, (BranchPair *)mb6ev_branch10Link, mb6ev_branch10ComTree);
    }
}

void MB6Ev_Branch11(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu != 0x40) {
        MBMoveNextMasuSet(-1, 0x12, 1);
        player->rev &= ~1;
    } else {
        MBDlgResultWinExec(0xE01);
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch11Masu, (BranchPair *)mb6ev_branch11Link, mb6ev_branch11ComTree);
    }
}

void MB6Ev_Branch12(void) {
    GW_PLAYER *player;
    s32 masu;

    player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[0] == 0 && (player->rev & 0x80)) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch12Masu, (BranchPair *)mb6ev_branch12Link, mb6ev_branch12ComTree);
    } else {
        masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);
        if (masu == 0x2D) {
            MBMoveNextMasuSet(-1, 0xB, 5);
        } else if (masu == 0x75) {
            MBMoveNextMasuSet(-1, 0xB, 5);
        } else {
            MBMoveNextMasuSet(-1, 0xB, 3);
            player->rev |= 1;
        }
    }
    omDelPrcObj(0);
}

void MB6Ev_Branch13(void) {
    GW_PLAYER *player;
    s32 masu;

    player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[0] == 1 && (player->rev & 0x80)) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch13Masu, (BranchPair *)mb6ev_branch13Link, mb6ev_branch13ComTree);
    } else {
        masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);
        if (masu == 0x32) {
            MBMoveNextMasuSet(-1, 0xB, 0xC);
        } else if (masu == 0x70) {
            MBMoveNextMasuSet(-1, 0xB, 0xC);
        } else {
            MBMoveNextMasuSet(-1, 0xB, 0xA);
            player->rev |= 1;
        }
    }
    omDelPrcObj(0);
}

void MB6Ev_Branch14RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch14Masu, (BranchPair *)mb6ev_branch14Link, mb6ev_branch14ComTree);
    }
}

void MB6Ev_Branch15RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch15Masu, (BranchPair *)mb6ev_branch15Link, mb6ev_branch15ComTree);
    }
}

void MB6Ev_Branch16RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch16Masu, (BranchPair *)mb6ev_branch16Link, mb6ev_branch16ComTree);
    }
}

void MB6Ev_Branch17RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch17Masu, (BranchPair *)mb6ev_branch17Link, mb6ev_branch17ComTree);
    }
}

void MB6Ev_HoleExitBranch(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_holeExitBranchMasu, (BranchPair *)mb6ev_holeExitBranchLink, mb6ev_holeExitBranchComTree);
    }
}

void MB6Ev_Branch18RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch18Masu, (BranchPair *)mb6ev_branch18Link, mb6ev_branch18ComTree);
    }
}

void MB6Ev_Branch19RKinoko(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MB6Ev_BranchMain((SpaceTriple *)mb6ev_branch19Masu, (BranchPair *)mb6ev_branch19Link, mb6ev_branch19ComTree);
    }
}

void MB6Ev_Merge1(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5D) {
        MBMoveNextMasuSet(-1, 3, 3);
    }
}

void MB6Ev_Merge2(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x21) {
        MBMoveNextMasuSet(-1, 2, 8);
    }
}

void MB6Ev_Merge3(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x04) {
        MBMoveNextMasuSet(-1, 2, 0xD);
    }
}

void MB6Ev_Merge4(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5A) {
        MBMoveNextMasuSet(-1, 0x15, 0);
    }
}

void MB6Ev_Merge5(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x62) {
        MBMoveNextMasuSet(-1, 0x15, 0);
    }
}

void MB6Ev_Merge6(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x1F) {
        MBMoveNextMasuSet(-1, 0x15, 0);
    }
}

void MB6Ev_Merge7(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x1A) {
        MBMoveNextMasuSet(-1, 5, 5);
    }
}

void MB6Ev_Merge8(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 7) {
        MBMoveNextMasuSet(-1, 6, 0xE);
    } else {
        MBMoveNextMasuSet(-1, 2, 4);
    }
}

void MB6Ev_Merge9(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x97) {
        MBMoveNextMasuSet(-1, 0xB, 0xB);
    } else {
        MBMoveNextMasuSet(-1, 5, 5);
    }
}

void MB6Ev_Merge10(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x74) {
        MBMoveNextMasuSet(-1, 0xB, 4);
    } else {
        MBMoveNextMasuSet(-1, 0xD, 4);
    }
}

void MB6Ev_Merge11(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x2A) {
        MBMoveNextMasuSet(-1, 0xB, 0x14);
    }
}

void MB6Ev_Merge12(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x3A) {
        MBMoveNextMasuSet(-1, 4, 3);
    }
}

void MB6Ev_Merge13(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x35) {
        MBMoveNextMasuSet(-1, 0xD, 4);
    }
}

void MB6Ev_Merge14(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x3D) {
        MBMoveNextMasuSet(-1, 4, 3);
    }
}

void MB6Ev_Merge15(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x4F) {
        MBMoveNextMasuSet(-1, 0xF, 4);
    }
}

void MB6Ev_Merge16(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x47) {
        MBMoveNextMasuSet(-1, 3, 8);
    }
}

void MB6Ev_Merge17(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x7B) {
        MBMoveNextMasuSet(-1, 0xF, 4);
    }
}

void MB6Ev_Merge18(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x45) {
        MBMoveNextMasuSet(-1, 0x10, 8);
    }
}

void MB6Ev_Trapdoor(void) {
    Vec sp18;
    GW_PLAYER *player;
    Object *model1;
    Object *model2;
    SpaceData *masu;
    f32 scale;
    s32 playerIdx = GwSystem.current_player_index;

    player = MBPlayerGet(-1);
    MBPlayerMotionSet(-1, -1, 2);
    MBVecForwardSet(&sp18);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBVecRotLerpCreate(&player->player_obj->rot, &sp18, &player->player_obj->rot, 5));
    HuPrcSleep(0x1E);
    if (MBRand(2.0f) == 0) {
        MBSaiNumKill(playerIdx);
        model1 = MBModelFileCreate(0x13018B, -1, 1.0f, 0, 0);
        Hu3DModelAttrSet(model1->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
        Hu3DModelLayerSet(model1->omObj1->model[0], 0);
        Hu3DModelRemakeStatic(model1->omObj1->model[0]);
        MBModelTempAllocFree(model1);
        HuVecCopy3F(&model1->coords, &player->player_obj->coords);
        model2 = MBModelFileCreate(0x13018C, -1, 1.0f, 0, 0);
        Hu3DModelLayerSet(model2->omObj1->model[0], 0);
        Hu3DModelAttrSet(model2->omObj1->model[0], HU3D_ATTR_ZMASK, HU3D_ATTR_ZMASK);
        Hu3DModelRemakeStatic(model2->omObj1->model[0]);
        MBModelTempAllocFree(model2);
        HuVecCopy3F(&model2->coords, &player->player_obj->coords);
        HuAudFXPlay(0x1BD);
        PlayerFXPlay(0x286, playerIdx);
        MBPlayerVibrate(-1, 4);
        scale = 1.0f;
        player->stat |= 4;
        while (player->player_obj->velocity.x >= -25.0f) {
            player->player_obj->velocity.x -= 3.0f;
            HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
            scale -= 0.1f;
            if (scale < 0.0f) {
                scale = 0.0f;
            }
            HuPrcVSleep();
        }
        scale = 0.0f;
        HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
        HuPrcChildWatch();
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        MBModelKill(model2);
        MBModelKill(model1);
        HuVecCopy3F(&player->player_obj->coords, &MBMasuGet(0x8B)->coords);
        player->player_obj->velocity.x = -4.0f;
        MBVecForwardSet(&player->player_obj->rot);
        HuPrcSleep(2);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x1BC);
        while (player->player_obj->velocity.x <= 15.0f) {
            player->player_obj->velocity.x += 1.5f;
            HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
            scale += 0.08f;
            if (scale > 1.0f) {
                scale = 1.0f;
            }
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
        player->stat &= ~4;
        masu = MBMasuGet(0x8A);
        MBVecDirGet(&player->player_obj->coords, &masu->coords, &player->player_obj->rot);
        MBPlayerMotionSet(-1, 2, 0);
        MBModelJumpSet(player->player_obj, 10.0f, -1.5f);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&player->player_obj->coords, &masu->coords, &player->player_obj->coords, 0xE));
        HuPrcChildWatch();
        MBPlayerMotionSet(-1, -1, 2);
        MBVecForwardSet(&sp18);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBVecRotLerpCreate(&player->player_obj->rot, &sp18, &player->player_obj->rot, 5));
        HuPrcChildWatch();
        MBDlgResultWinExec(0xE00);
        MBMoveMasuSet(-1, 1, 7);
        MBMoveBackMasuSet(-1, 1, 0);
        MBSaiNumShow(playerIdx);
        HuPrcSleep(0xA);
        MB6Ev_HoleExitBranch();
    } else {
        s16 masuId = MBMasuLinkMasuIdGet(player->blink, player->bidx);

        if (masuId == 0x7B) {
            MBMoveNextMasuSet(-1, 0x12, 0);
        } else {
            MBMoveNextMasuSet(-1, 0x11, 1);
        }
    }
}

void MB6Ev_Branch1Rev(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x6B) {
        MBMoveBackMasuSet(-1, 1, 9);
    }
}

s32 MB6Ev_KeyManChoiceGet(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
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

void MB6Ev_KeyManMasu(void) {
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

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x88) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8D) {
            if (MBItemFind(GwSystem.current_player_index, 1) != -1) {
                MBSaiNumKill(GwSystem.current_player_index);
                MBPlayerMotionSet(-1, -1, 2);
                sp18 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
                switch (sp18) {
                    case 0x83:
                    case 0x89:
                        MBPlayerRotMasuStart(-1, 8, 0x88);
                        break;
                    default:
                        MBPlayerRotMasuStart(-1, 8, 0x8D);
                        break;
                }
                HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
                HuPrcChildWatch();
                MBPlayerVibrate(-1, 1);

                while (1) {
                    MBDlgWinCreate(0x38, 0x4103);
                    choice = MB6Ev_KeyManChoiceGet(0);
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
                                case 0x83:
                                    MB6_GateOpen(0, 0);
                                    break;
                                case 0x89:
                                    MB6_GateOpen(0, 1);
                                    break;
                                case 0x96:
                                    MB6_GateOpen(1, 0);
                                    break;
                                default:
                                    MB6_GateOpen(1, 1);
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
                            MB6_MapScroll();
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
            case 0x83:
                MBMoveNextMasuSet(-1, 1, 1);
                player->rev |= 1;
                break;
            case 0x89:
                MBMoveNextMasuSet(-1, 1, 5);
                player->rev &= ~1;
                break;
            case 0x96:
                MBMoveNextMasuSet(-1, 6, 0xE);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 6, 5);
                player->rev &= ~1;
                break;
        }
    }

    omDelPrcObj(NULL);
}

void MB6Ev_BankMasuBranch(void) {
}

void MB6Ev_StarMasuBranch(void) {
}

void MB6Ev_TeresaMasuBranch(void) {
}

s32 MB6Ev_YesNoChoiceGet(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
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

void MB6Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void MB6Ev_ItemSelAttrProc(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
    }
}

void MB6Ev_StarMasu(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = MB6Ev_StarCheck(spaceIdx);
    if (spaceIdx == 1) {
        MBSaiNumKill(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        MBPlayerRotMasuStart(-1, 8, MB6Ev_StarGuideMasuGet());
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
                choice = MB6Ev_YesNoChoiceGet(2, 0);
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
                        MB6Ev_StarGetExec(mb6_starGuideBaseMdl);
                        HuPrcSleep(30);
                        MBBoardRestartSet();
                        MBExitReq(2);
                        MB6Ev_StarMasuBranch();
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
                        MB6Ev_StarMasuBranch();
                        return;
                    case 2:
                        MB6_MapScroll();
                        goto purchaseMenu;
                    default:
                        MB6Ev_StarMasuBranch();
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

    MB6Ev_StarMasuBranch();
}

void MB6Ev_BankMasu(void) {
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
        case 0x59:
            MBPlayerRotMasuStart(-1, 8, 0x8F);
            spaceA = MBMasuGet(0x8F);
            spaceB = MBMasuGet(0x59);
            break;
        case 0x22:
            MBPlayerRotMasuStart(-1, 8, 0x8E);
            spaceA = MBMasuGet(0x8E);
            spaceB = MBMasuGet(0x22);
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

    effectModel = MBModelCreate(0x35, mb6ev_bankCoinPileMot);
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
        choice = MB6Ev_YesNoChoiceGet((s32)mb6ev_bankComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                MB6_MapScroll();
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
        sprintf(sp20, mb6ev_numFmtStr, GwSystem.bank_coins);
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
            MB6Ev_BankKoopaCardExec();
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
                sprintf(sp20, mb6ev_numFmtStr, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, mb6ev_numFmtStr, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                MB6_BankCoinHide();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                MBDlgWinOpen();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, mb6ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, mb6ev_numFmtStr, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                MB6_BankCoinHide();
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
                sprintf(sp20, mb6ev_numFmtStr, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinMesWait();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                MB6_BankCoinHide();
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
    MB6Ev_BankMasuBranch();
}

s32 MB6Ev_ShopItemIdxGet(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb6ev_shopItemEnableTbl[i] != 0) {
            if (mb6ev_shopItemTbl[mb6ev_shopHostNo][mb6ev_shopItemRow][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 MB6Ev_ShopItemNumGet(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb6ev_shopItemTbl[mb6ev_shopHostNo][mb6ev_shopItemRow][i] == -1) {
            break;
        }
    }
    return i;
}

void MB6Ev_ShopBagBounceProc(void) {
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

void MB6Ev_ShopMasu(void) {
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
        case 0x6C:
            camMasu = 0x90;
            spaceA = MBMasuGet(0x90);
            spaceB = MBMasuGet(0x6C);
            mb6ev_shopNo = 0;
            break;
        case 0x79:
            camMasu = 0x8C;
            spaceA = MBMasuGet(0x8C);
            spaceB = MBMasuGet(0x79);
            mb6ev_shopNo = 1;
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
            effectModel = MBModelCreate(0x39, mb6ev_shopKoopaJrMot);
        } else {
            effectModel = MBModelCreate(0x1B, mb6ev_shopKinopioMot);
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
        MBDlgWinExec(dlgWin, mb6ev_shopLastTurnMesTbl[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, mb6ev_shopItemFullMesTbl[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, mb6ev_shopNoCoinMesTbl[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, mb6ev_shopEnterMesTbl[shopIdx]);
    choice = MB6_ComShopEnterChoice();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = MBTurnTierGet(-1);
            row = mb6ev_shopItemRowTbl[shopIdx][i][MBPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (mb6ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mb6ev_shopItemTbl[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (mb6ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mbItemPriceTbl[mb6ev_shopItemTbl[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, mb6ev_shopItemMesTbl[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            MBDlgWinTabWidthSet(0);
            mb6ev_shopHostNo = slot;
            mb6ev_shopItemRow = row;
            mb6ev_shopItemEnableTbl = enabled;
            sel = MB6_ComShopItemChoice(enabled);
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
            shopTable = mb6ev_shopItemTbl;
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
                    mb6ev_shopItemTbl[shopIdx][row][sel];
                item = mb6ev_shopItemTbl[shopIdx][row][sel];
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

            if (mb6ev_shopItemTbl[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = mb6ev_shopBagRowTbl[shopIdx][MBTurnTierGet(-1)]
                                                [MBPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < mb6ev_shopBagRateTbl[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = mb6ev_shopBagItemTbl[shopIdx][i];

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
                    prc = omAddPrcObj(MB6Ev_ShopBagBounceProc, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, mb6ev_shopCancelMesTbl[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                MB6_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB6_MapScroll();
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

void MB6Ev_TeresaFadeIn(Object *obj) {
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

void MB6Ev_TeresaFadeOut(Object *obj) {
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

s32 MB6Ev_TeresaStarSteal(s32 playerIndex) {
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
    HuSprPosSet(grp, 0, mb6ev_teresaSprPosTbl[playerIndex].x,
                        mb6ev_teresaSprPosTbl[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        HuSprPosSet(grp, 0,
                            (i * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                mb6ev_teresaSprPosTbl[playerIndex].x,
                            (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                mb6ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(MB6Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                            (mb6ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                                mb6ev_teresaSprPosTbl[playerIndex].x,
                            (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                                mb6ev_teresaSprPosTbl[playerIndex].y +
                                (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        HuSprPosSet(grp, 0,
                            (i * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                mb6ev_teresaSprPosTbl[playerIndex].x,
                            (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                mb6ev_teresaSprPosTbl[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    return !hasRareItem;
}

void MB6Ev_TeresaWinCloseProc(void) {
    MBWinClose();
    omDelPrcObj(NULL);
}

s32 MB6Ev_TeresaSteal(s32 playerIndex) {
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
    HuSprPosSet(grp, 0, mb6ev_teresaSprPosTbl[playerIndex].x,
                        mb6ev_teresaSprPosTbl[playerIndex].y);
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
                            mb6ev_teresaSprPosTbl[playerIndex].x -
                                (mb6ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                            mb6ev_teresaSprPosTbl[playerIndex].y +
                                (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f));
        HuSprTPLvlSet(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            HuSprPosSet(grp, 0,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                    mb6ev_teresaSprPosTbl[playerIndex].x,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                    mb6ev_teresaSprPosTbl[playerIndex].y);
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
            omAddPrcObj(MB6Ev_TeresaWinCloseProc, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(MB6Ev_TereYokeSprayProc, 0x4002, 0, 0);
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
                    (mb6ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].x,
                    (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                HuSprPosSet(
                    grp, 0,
                    (mb6ev_teresaSprDirTbl[playerIndex].x * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].y);
                HuSprPosSet(
                    playerGrp, 0,
                    mb6ev_teresaSprPosTbl[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].y);
                angle++;
            }

            if (GwPlayer[playerIndex].stat & PLAYER_IS_CPU) {
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
                            playerGrp, 0, mb6ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                            (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                                mb6ev_teresaSprPosTbl[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                HuSprBankSet(playerGrp, 0, 0, 0);
                HuSprAnimModeSet(playerGrp, 0, HUSPR_ANIM_MODE_BANK);
                playerSpriteVisible = 0;
                HuSprPosSet(
                    playerGrp, 0,
                    mb6ev_teresaSprPosTbl[playerIndex].x -
                        (mb6ev_teresaSprDirTbl[playerIndex].x * 16.0f) - 8.0f,
                    (mb6ev_teresaSprDirTbl[playerIndex].y * 16.0f) +
                        mb6ev_teresaSprPosTbl[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(MB6Ev_TeresaWinCloseProc, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprPosSet(grp, 0,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                    mb6ev_teresaSprPosTbl[playerIndex].x,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                    mb6ev_teresaSprPosTbl[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            HuSprPosSet(grp, 0,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                    mb6ev_teresaSprPosTbl[playerIndex].x,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                    mb6ev_teresaSprPosTbl[playerIndex].y);
            HuSprPosSet(playerGrp, 0,
                                ((i - 0x10) * mb6ev_teresaSprDirTbl[playerIndex].x) +
                                    mb6ev_teresaSprPosTbl[playerIndex].x - 8.0f,
                                (i * mb6ev_teresaSprDirTbl[playerIndex].y) +
                                    mb6ev_teresaSprPosTbl[playerIndex].y);
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
        for (i = 0; i < ARRAY_COUNTU(mb6ev_teresaCoinTurnTbl); i++) {
            if ((GwSystem.current_turn >= mb6ev_teresaCoinTurnTbl[i][0]) &&
                (GwSystem.current_turn <= mb6ev_teresaCoinTurnTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible = mb6ev_teresaCoinTurnTbl[i][2];
        for (i = 0; i < ARRAY_COUNTU(mb6ev_teresaCoinPenaltyTbl); i++) {
            if ((attempts >= mb6ev_teresaCoinPenaltyTbl[i][0]) &&
                (attempts <= mb6ev_teresaCoinPenaltyTbl[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= mb6ev_teresaCoinPenaltyTbl[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

const ChanceTable mb6ev_rouletteComHitRateTbl = { { 50, 70, 90, 100 } };

const ChanceTable mb6ev_rouletteComJumpRateTbl = { { 10, 7, 3, 0 } };

const ChanceTable mb6ev_rouletteLinkTbl = { { 4, 3, 2, 5 } };

const ChanceTable mb6ev_rouletteLinkIdxTbl = { { 0, 0, 13, 0 } };

const char mb6ev_numFmtStr[] = "%d";

void MB6Ev_TeresaCoin(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb6ev_teresaCoinMdl);
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

void MB6Ev_TeresaCoinCreate(s32 arg) {
    Process *temp = omAddPrcObj(MB6Ev_TeresaCoin, 0x1000, 0, 0);

    temp->user_data = (void *)arg;
}

void MB6Ev_Teresa(void) {
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
    if (spaceId != 0x7F) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(mb6_teresaGuideBaseMdl);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x80;
        space = MBMasuGet(0x80);
        boo = mb6_teresaGuideMdl[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
            if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    MB6Ev_TeresaFadeIn(boo);
    space = MBMasuGet(spaceId);
    spaceId = camMasu;
    if (spaceId != -1) {
        MBDDebugCheatKill(boo, &space->coords, 5);
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

starChoiceUnavailable: {
    inserts[1][0] = 1;
    choices[1] = 0;
    goto starChoiceDone;
}

starChoiceAvailable: {
    inserts[1][0] = 8;
    choices[1] = 1;
}

starChoiceDone:
    inserts[1][1] = 0;
    choices[3] = 1;
    choices[2] = 1;
    MBDlgWinInsertCreate(7, 0x6200, (s32)inserts[0], (s32)inserts[1], 0, 0, 0);
    menuResult = MB6_ComTeresaTypeChoice(choices);
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
    playerChoice = MB6_ComTeresaPlayerChoice(choices);
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
                MB6_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB6_MapScroll();
            }
            goto selectPlayer;
        default:
            goto playerSelected;
    }

selectCpuPlayer: {
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
        if (rank < mb6ev_teresaComTargetRateTbl[i]) {
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
            if (GwSystem.current_turn >= mb6ev_teresaCoinTurnTbl[i][0] &&
                GwSystem.current_turn <= mb6ev_teresaCoinTurnTbl[i][1]) {
                break;
            }
        }
        estimatedAmount = mb6ev_teresaCoinTurnTbl[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    MB6Ev_TeresaFadeOut(boo);
    if (menu == 0) {
        resultAmount = MB6Ev_TeresaSteal(target);
        MB6Ev_TeresaFadeIn(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], mb6ev_numFmtStr, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], mb6ev_numFmtStr, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= mb6ev_teresaCoinDiffTbl[i]) {
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
            mb6ev_teresaCoinMdl = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(mb6ev_teresaCoinMdl);
            MBModelDispOff(mb6ev_teresaCoinMdl);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    MB6Ev_TeresaCoinCreate((s32)boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(mb6ev_teresaCoinMdl);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = MB6Ev_TeresaStarSteal(target);
        MB6Ev_TeresaFadeIn(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            mb6ev_starGetTeresaF = 1;
            MB6Ev_StarGetExec(boo);
            mb6ev_starGetTeresaF = 0;
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
    MB6Ev_TeresaFadeOut(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        MB6_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
    } else {
        MB6_MapScroll();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        MB6Ev_TeresaFadeOut(boo);
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
            if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb6ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
    MB6Ev_TeresaMasuBranch();
}

void MB6Ev_Gate1Close(void) {
    MB6_GateClose(0);
}

void MB6Ev_Gate2Close(void) {
    MB6_GateClose(1);
}

omObjData *MB6Ev_ItemLampSmokeCreate(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, MB6Ev_ItemLampSmokeObjMain);
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

void MB6Ev_ItemLampSmokeObjMain(omObjData *arg0) {
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

void MB6Ev_ItemMajinLamp(void) {
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
    MB6Ev_ItemUseFadeOut();
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
            MB6Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    MBMasuLinkIdxGet(
        mb6ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
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
            MB6Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            msmMusPause(0);
        }
    }
}

void MB6Ev_ItemMajinLampStar(void) {
    s16 ret;

    mbStarMusF = 1;
    MBMasuEventCall(mb6ev_starMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    mbStarMusF = 0;
    ret = MBExitFlagGet();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

void MB6Ev_ItemWarpBlock(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MB6Ev_ItemUseFadeOut();
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

void MB6Ev_ItemMove(void) {
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

Process *MB6Ev_ItemMoveCreate(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                                  s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(MB6Ev_ItemMove, 0x4002, 0, 0x40);
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

void MB6Ev_ItemKinoko(void) {
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
    HuPrcChildLink(process, MB6Ev_ItemMoveCreate(
                                mbItemCursorGrpId, position[0], position[1],
                                mb6ev_itemUsePosTbl[system->current_player_index].x,
                                mb6ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB6Ev_ItemUseFadeOut(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    MB6Ev_ItemMoveCreate(
        mbItemCursorGrpId, position[0], position[1],
        mb6ev_itemFadePosTbl[system->current_player_index].x,
        mb6ev_itemFadePosTbl[system->current_player_index].y, -1);
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

void MB6Ev_ItemCursorReturn(void) {
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
                   MB6Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                            targetX, targetY, -1));
    HuPrcChildWatch();

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB6Ev_ItemShake(void) {
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
                   MB6Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                            mb6ev_itemUsePosTbl[system->current_player_index].x,
                                            mb6ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB6Ev_ItemPhoneMove(void) {
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
                   MB6Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                            mb6ev_itemUsePosTbl[system->current_player_index].x,
                                            mb6ev_itemUsePosTbl[system->current_player_index].y, -1));
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

void MB6Ev_ItemIconMove(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
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

void MB6Ev_KSuitStart(void) {
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

void MB6Ev_KSuitEnd(void) {
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

void MB6Ev_ItemPhoneWaveProc(void) {
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
    HuSprGrpMemberSet(group, 0, mb6ev_itemPhoneWaveSpr, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, HUSPR_ATTR_XLU);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    HuSprPosSet(group, 0, x, y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)mb6ev_itemPhoneWaveAngleTbl[index];
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

void MB6Ev_ItemShopPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb6ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB6Ev_ItemPhoneMove();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = MB6Ev_YesNoChoiceGet((s32)mb6ev_shopPhoneComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(MB6Ev_ItemSelAttrProc, 0, 0, 0);
                omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
                MB6_MapScrollCancel();
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

        process = omAddPrcObj(MB6Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
        MB6_MapScrollCancel();
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
            process = omAddPrcObj(MB6Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB6Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb6ev_itemPhoneWaveSpr);
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
    MB6Ev_ShopMasu();
    GwSystem.forceShopHost = 0;
}

void MB6Ev_ItemKoopaPhone(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    mb6ev_itemPhoneWaveSpr = HuSprAnimRead(data);
    DataClose(data);
    MB6Ev_ItemPhoneMove();

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB6Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(MB6Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);
    }

    HuAudFXPlay(0x29F);
retry:
    MBDlgWinInsertCreate(4, 0x3A0A,
                         mbCharNameMesTbl[GwPlayer[0].chr],
                         mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr],
                         mbCharNameMesTbl[GwPlayer[3].chr], 0);
    if (GwPlayer[loc->current_player_index].coin != 0) {
        choice = MB6Ev_YesNoChoiceGet(1, 0);
    } else {
        choice = MB6Ev_YesNoChoiceGet(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = MBPlayerRankRandGet(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(MB6Ev_ItemSelAttrProc, 0, 0, 0);
            omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
            MB6_MapScrollCancel();
            one = 1;
            winPauseF = one;
            omAllPause();
            omDelPrcObj(process);
            MBTurnHelpKill();
            goto retry;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B,
                                 (s32)((char **)0x801014A0)[GwPlayer[choice].chr],
                                 0, 0, 0, 0);
            break;
    }
    MBDlgWinClose();
    MBDlgWinKill();

    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprAnimKill(mb6ev_itemPhoneWaveSpr);

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

void MB6Ev_ItemStarYoke(void) {
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
        MB6Ev_ItemUseFadeOut();

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
            MB6Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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
            MB6Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1,
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

        space = MBMasuGet(mb6ev_starMasu[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(mb6ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
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
        if (mb6_starGuideHoverProc[j] != NULL) {
            omDelPrcObj(mb6_starGuideHoverProc[j]);
            mb6_starGuideHoverProc[j] = NULL;
        }
    }

    targetStar = mb6_starGuideMdl[system->star_spawn_indices[system->current_star_spawn]];
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

void MB6Ev_ItemKeyManUse(void) {
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
                   MB6Ev_ItemMoveCreate(mbItemCursorGrpId, position[0], position[1],
                                            mb6ev_itemUsePosTbl[system->current_player_index].x,
                                            mb6ev_itemUsePosTbl[system->current_player_index].y, -1));
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
    result = MB6Ev_YesNoChoiceGet((s32)&mb6ev_keyManUseComTree, 0);
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
            MB6_MapScrollCancel();
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

void MB6Ev_TereYokeSparkProc(void) {
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
    HuSprGrpMemberSet(setupGroup, 0, mb6ev_tereYokeSparkSpr, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, HUSPR_ATTR_XLU);
    MBStatusItemPosGet(mb6ev_tereYokePlayer, 0, &xPos, &yPos);

    xPos = (s32)((mb6ev_teresaSprDirTbl[mb6ev_tereYokePlayer].x * 16.0f) +
                 mb6ev_teresaSprPosTbl[mb6ev_tereYokePlayer].x);
    yPos = (s32)((mb6ev_teresaSprDirTbl[mb6ev_tereYokePlayer].y * 16.0f) +
                 mb6ev_teresaSprPosTbl[mb6ev_tereYokePlayer].y);
    HuSprPosSet(
        setupGroup, 0, (f32)xPos + mb6ev_tereYokeSparkOfsTbl[playerIndex].x,
        (f32)yPos + mb6ev_tereYokeSparkOfsTbl[playerIndex].y);
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

void MB6Ev_TereYokeSprayProc(void) {
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
    mb6ev_tereYokeSparkSpr = HuSprAnimRead(data);
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
    mb6ev_tereYokePlayer = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(MB6Ev_TereYokeSparkProc, 0x4002, 0, 0);
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
    HuSprAnimKill(mb6ev_tereYokeSparkSpr);
    HuSprAnimKill(auraSpriteId);
    HuSprAnimKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void MB6Ev_ItemNullUse(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void MB6Ev_KoopaCardCoinProc(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(mb6ev_koopaCardCoinMdl);
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

void MB6Ev_KoopaCardCoinCreate(Object *arg) {
    Process *temp = omAddPrcObj(MB6Ev_KoopaCardCoinProc, 0x1000, 0, 0);

    temp->user_data = arg;
}

void MB6Ev_KoopaCardSpinProc(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        mb6ev_koopaCardMdl->rot.x = -sindf(angle);
        mb6ev_koopaCardMdl->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            mb6ev_koopaCardMdl->scale.z = scale;
            mb6ev_koopaCardMdl->scale.y = scale;
            mb6ev_koopaCardMdl->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    mb6ev_koopaCardMdl->scale.x = mb6ev_koopaCardMdl->scale.y = mb6ev_koopaCardMdl->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(mb6ev_koopaCardMdl);
    omDelPrcObj(0);
}

void MB6Ev_BankKoopaCardExec(void) {
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
    MB6Ev_ItemUseFadeOut();

    mb6ev_koopaCardMdl = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&mb6ev_koopaCardMdl->coords, &MBPlayerGet(-1)->player_obj->coords);
    mb6ev_koopaCardMdl->velocity.x = 100.0f;
    while (30.0f < mb6ev_koopaCardMdl->velocity.x) {
        mb6ev_koopaCardMdl->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(MB6Ev_KoopaCardSpinProc, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    mb6ev_koopaCardCoinMdl = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(mb6ev_koopaCardCoinMdl);
    MBModelDispOff(mb6ev_koopaCardCoinMdl);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                MB6Ev_KoopaCardCoinCreate(mb6ev_koopaCardMdl);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                MB6_BankCoinHide();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(mb6ev_koopaCardCoinMdl);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 MB6_ComItemTargetChoice(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)mb6_padBitTbl;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = mb6_comExchangeBoxTarget + 1;
                } else {
                    delay = mb6_comRobBoxTarget + 1;
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

void MB6Ev_ExchangeItemFadeOutProc(void) {
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

void MB6Ev_ExchangeItemFadeInProc(void) {
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

void MB6Ev_ItemExchangeBox(void) {
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

    MB6Ev_ItemUseFadeOut();
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
    targetPlayer = MB6_ComItemTargetChoice(choices, 1);
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
                    MB6Ev_ItemIconMove(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(MB6Ev_ExchangeItemFadeOutProc, 0x4800, 0, 0);
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
        process = omAddPrcObj(MB6Ev_ExchangeItemFadeInProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB6Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB6Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB6Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                MB6Ev_ItemIconMove(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB6Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB6Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                MB6Ev_ItemIconMove(targetPlayer, 2, 7, &target.x, 2);
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

void MB6Ev_GambleCoinEffProc(void) {
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

void MB6Ev_GambleCoinProc(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = mb6ev_gambleCoinMdl;
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
        if (mb6ev_gambleCoinPlayer != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(mb6ev_gambleCoinPlayer)->player_obj->coords);
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
    process = omAddPrcObj(MB6Ev_GambleCoinEffProc, 0x4800, 0, 0x40);
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

void MB6Ev_ItemGambleCoin(void) {
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
    MB6Ev_ItemUseFadeOut();
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
    mb6ev_gambleCoinMdl = gameGuyModel;
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
    choice = MB6Ev_YesNoChoiceGet(0, 0);
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
    MB6_MapScrollCancel();
    winPauseF = 1;
    omAllPause();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(MB6Ev_GambleCoinProc, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        mb6ev_gambleCoinPlayer = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        mb6ev_gambleCoinPlayer = choice;
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
        MB6Ev_WinPlayerKeyExec(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        MB6Ev_WinPlayerKeyExec(10, 0x2F02, -1, choice);
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
        MB6Ev_WinPlayerKeyExec(10, 0x2F01, -1, choice);
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
            if (randomValue <= mb6ev_gambleRateTbl[rewardIndex].threshold) {
                break;
            }
        }
        if (mb6ev_gambleRateTbl[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * mb6ev_gambleRateTbl[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, mb6ev_numFmtStr, rewardAmount);
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
        if (randomValue < mb6ev_gambleMgRateTbl[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = mb6ev_gambleMgTbl[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    MBGameModeMgSet();
    omAllUPause();
    MBExitReq(2);
    HuPrcSleep(-1);
}

void MB6Ev_After5ItemMove(s32 arg0, s32 arg1, f32 *arg2) {
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

void MB6Ev_After5LineShow(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            HuSprPosSet(mb6ev_after5GrpId[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(mb6ev_after5GrpId[idx], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(mb6ev_after5GrpId[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprDispOn(mb6ev_after5GrpId[idx], 0);
    for (i = 0; i < 255; i += 255 / divisor) {
        HuSprTPLvlSet(mb6ev_after5GrpId[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mb6ev_after5GrpId[idx], 0, 0xFF);
    omDelPrcObj(0);
}

void MB6Ev_After5NumFade(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = mb6ev_after5NumColorTbl[i].r;
        sp18.g = mb6ev_after5NumColorTbl[i].g;
        sp18.b = mb6ev_after5NumColorTbl[i].b;

        sp28.r = (mb6ev_after5NumColorTbl[i + 1].r - sp18.r) / 30;
        sp28.g = (mb6ev_after5NumColorTbl[i + 1].g - sp18.g) / 30;
        sp28.b = (mb6ev_after5NumColorTbl[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(mb6ev_after5GrpId[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(mb6ev_after5GrpId[3], 0, mb6ev_after5NumColorTbl[i + 1].r, mb6ev_after5NumColorTbl[i + 1].g, mb6ev_after5NumColorTbl[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void MB6Ev_After5Effect(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = mb6ev_after5EffMdl;
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

void MB6Ev_ItemAfter5(void) {
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
        mb6ev_after5GrpId[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(mb6ev_after5GrpId[i], 0, sp18[i], 0);
        HuSprPriSet(mb6ev_after5GrpId[i], 0, 0x4780U);
        HuSprAttrSet(mb6ev_after5GrpId[i], 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
        HuSprTPLvlSet(mb6ev_after5GrpId[i], 0, 0U);
        HuSprColorSet(mb6ev_after5GrpId[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    mb6ev_after5EffMdl = temp_v0_3;
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
    MB6Ev_After5ItemMove(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    MB6Ev_After5ItemMove(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(MB6Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    MB6Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(MB6Ev_After5LineShow, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    MB6Ev_After5ItemMove(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(MB6Ev_After5LineShow, 0x4002U, 0, 0);
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
        HuSprDispOff(mb6ev_after5GrpId[i], 0);
    }

    HuSprDispOn(mb6ev_after5GrpId[3], 0);
    HuSprTPLvlSet(mb6ev_after5GrpId[3], 0, 0xFFU);
    HuSprPosSet(mb6ev_after5GrpId[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB6Ev_After5NumFade, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(MB6Ev_After5Effect, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(mb6ev_after5GrpId[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(mb6ev_after5GrpId[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(mb6ev_after5GrpId[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(WIPE_FADE, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void MB6Ev_BranchMain(SpaceTriple *masu, BranchPair *links, DecisionTreeNonLeafNode **trees) {
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
    MB6_BranchHelpStart();
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
    MB6_BranchHelpEnd();

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

void MB6Ev_KinokoMarkKill(s32 arg0) {
    if (mb6ev_kinokoMarkObj[arg0] != NULL) {
        omDelObj(mb6ev_kinokoMarkObj[arg0]);
        mb6ev_kinokoMarkObj[arg0] = NULL;
    }
    if (mb6ev_kinokoMarkMdl[arg0] != NULL) {
        MBModelKill(mb6ev_kinokoMarkMdl[arg0]);
        mb6ev_kinokoMarkMdl[arg0] = NULL;
    }
}

void MB6Ev_KinokoMarkObjKillAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = mb6ev_kinokoMarkObj[i];

        if (obj != NULL) {
            omDelObj(obj);
            mb6ev_kinokoMarkObj[i] = NULL;
        }
    }
}

void MB6Ev_KinokoMarkObjMain(omObjData *obj) {
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
        Object *effectObj = mb6ev_kinokoMarkMdl[playerIdx];

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

void MB6Ev_KinokoMarkCreate(s32 arg0, s32 arg1) {
    GW_PLAYER *player = MBPlayerGet(arg0);
    Object *obj;
    u8 modelId;

    if (mb6ev_kinokoMarkMdl[arg0] == NULL) {
        switch (arg1) {
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
        mb6ev_kinokoMarkMdl[arg0] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        MBModelDispFlagSet(mb6ev_kinokoMarkMdl[arg0]);
    }
}

void MB6Ev_KinokoMarkObjCreate(s32 arg) {
    mb6ev_kinokoMarkObj[arg] = omAddObj(0x3FFF, 0, 0, -1, MB6Ev_KinokoMarkObjMain);
    mb6ev_kinokoMarkObj[arg]->work[0] = arg;
    mb6ev_kinokoMarkObj[arg]->work[1] = 0;
    mb6ev_kinokoMarkObj[arg]->work[2] = 0;
    mb6ev_kinokoMarkObj[arg]->rot.x = (f32)MBRand(360.0f);
    mb6ev_kinokoMarkObj[arg]->trans.x = 0;
}

void MB6Ev_KinokoMarkCreateAll(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        mb6ev_kinokoMarkObj[i] = NULL;
        mb6ev_kinokoMarkMdl[i] = NULL;
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
            MB6Ev_KinokoMarkCreate(i, idx);
            MB6Ev_KinokoMarkObjCreate(i);
        }
    }
    MBExitHookSet(MB6Ev_KinokoMarkObjKillAll);
}

void MB6Ev_NKinokoTurnStart(void) {
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
            if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB6Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB6Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void MB6Ev_ItemKoopaNKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        MBSaiKill(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB6Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB6Ev_KinokoVibrateProc(void) {
    void *data;
    s32 i;

    i = 0x3C;
    data = HuPrcCurrentGet()->user_data;

    while (i != 0) {
        HuPrcVSleep();
        i--;
    }

    MBPlayerVibrateObjKill(data);
    omDelPrcObj(NULL);
}

void MB6Ev_ItemNKinoko(void) {
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
    choice = MB6Ev_YesNoChoiceGet(2, mb6_comNKinokoTarget);
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

    MB6Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    MB6Ev_KinokoMarkCreate(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    MB6Ev_KinokoMarkObjCreate(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(MB6Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
            HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        MB6Ev_KinokoMarkKill(loc->current_player_index);
        MBSaiKill(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void MB6Ev_RKinokoTurnStart(void) {
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
            if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB6Ev_KinokoMarkKill(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB6Ev_KinokoMarkKill(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void MB6Ev_ItemKoopaRKinoko(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        MBSaiKill(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (mb6ev_kinokoMarkMdl[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB6Ev_KinokoMarkKill(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB6Ev_ItemRKinoko(void) {
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
    choice = MB6Ev_YesNoChoiceGet(2, mb6_comRKinokoTarget);
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

    MB6Ev_KinokoMarkKill(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    MB6Ev_KinokoMarkCreate(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb6ev_kinokoMarkMdl[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    MB6Ev_KinokoMarkObjCreate(targetPlayer);
    omAddPrcObj(MB6Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
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
        MB6Ev_RKinokoTurnStart();
    }
}

void MB6Ev_ItemRobBox(void) {
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

    MB6Ev_ItemUseFadeOut();
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
    targetPlayer = MB6_ComItemTargetChoice(choices, 0);
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
                       mb6ev_robBoxItemStartPosTbl[system->current_player_index].x,
                       mb6ev_robBoxItemStartPosTbl[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   MB6Ev_ItemMoveCreate(-1,
                                            mb6ev_robBoxItemStartPosTbl[system->current_player_index].x,
                                            mb6ev_robBoxItemStartPosTbl[system->current_player_index].y,
                                            mb6ev_robBoxItemEndPosTbl[system->current_player_index].x,
                                            mb6ev_robBoxItemEndPosTbl[system->current_player_index].y, 5));
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
    MB6Ev_ItemCursorReturn();
}

void MB6Ev_BombExplodeMdlEndProc(void) {
    Object *obj = *(Object **)HuPrcCurrentGet()->user_data;

    Hu3DMotionAttrSet(obj->omObj1->model[0], 3, 0);
    MBModelMotionWait(obj);
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

void MB6Ev_BombExplodeMdlEndStart(Object *arg) {
    Process *temp = omAddPrcObj(MB6Ev_BombExplodeMdlEndProc, 0, 0, 0x40);
    s32 *data = HuMemMemoryAlloc(temp->heap, 0x10);

    temp->user_data = data;
    *data = (s32)arg;
}

void MB6Ev_BombCountExec(void) {
    Vec camPos;
    Vec targetPos;
    Object *models[3];
    ModelIdTable animIds;
    void *data[4];
    s8 link;
    s8 index;
    s32 i;
    s32 j;
    s32 mask;
    s32 maxCoins;
    f32 scale;
    SpaceData *masu;
    GW_PLAYER *player;

    masu = MBMasuGet(0x94);
    player = MBPlayerGet(-1);
    animIds = mb6ev_bombExplodeMdlTbl;
    MBBackThreadPriLowSet();
    if (GwSystem.boardData.halfWordBytes[1] == 1) {
        HuAudFXPlay(0x1BA);
    }
    HuVecCopy3F(&camPos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&camPos);
    HuVecCopy3F(&targetPos, &masu->coords);
    targetPos.z += 10.0f;
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&camPos, &targetPos, &camPos, 0x1E));
    HuPrcChildWatch();
    HuPrcSleep(5);

    GwSystem.boardData.halfWordBytes[1]--;
    MB6_BombCountUpdate();
    if (GwSystem.boardData.halfWordBytes[1] != 0) {
        HuAudFXPlay(0x1B8);
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);

            for (j = 0; mb6ev_bombMasuTbl[j] != -1; j++) {
                MBMasuLinkIdxGet(mb6ev_bombMasuTbl[j], &link, &index);
                if (player->clink == link && player->cidx == index) {
                    MBPlayerVibrate(i, 3);
                    break;
                }
            }
        }
    } else {
        HuAudFXPlay(0x1B9);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.0f));
        HuPrcChildWatch();
    }
    HuPrcSleep(0x14);

    if (GwSystem.boardData.halfWordBytes[1] == 0) {
        mask = 0;
        MBStatusHideAll();
        mbTauntOffF = 1;
        for (i = 0; i < 4; i++) {
            player = MBPlayerGet(i);

            for (j = 0; mb6ev_bombMasuTbl[j] != -1; j++) {
                MBMasuLinkIdxGet(mb6ev_bombMasuTbl[j], &link, &index);
                if (player->clink == link && player->cidx == index) {
                    s32 bit = 1 << i;

                    mask |= bit;
                    data[i] = MBPlayerVibrateObjCreate(i, 4, 5);
                    break;
                }
            }
            if (mb6ev_bombMasuTbl[j] == -1) {
                data[i] = MBPlayerVibrateObjCreate(i, 2, 5);
            }
        }
        HuAudFXPlay(0x1BB);
        for (i = 0; i < 3; i++) {
            scale = 25.0f;
            models[i] = MBModelFileCreate(animIds.entries[i], -1, 1.0f, 0, 0);
            Hu3DModelAttrSet(models[i]->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
            Hu3DModelLayerSet(models[i]->omObj1->model[0], 0x1800);
            Hu3DModelRemakeStatic(models[i]->omObj1->model[0]);
            MB6Ev_BombExplodeMdlEndStart(models[i]);
            MBModelTempAllocFree(models[i]);
            HuVecCopy3F(&models[i]->coords, &masu->coords);
            HuVecCopyXYZ(&models[i]->scale, scale, scale, scale);
            HuPrcSleep(0xC);
        }
        for (i = 0; i < 4; i++) {
            if ((mask & (1 << i)) != 0) {
                MBMotionSet(MBPlayerGet(i)->player_obj, 4, 2);
                PlayerFXPlay(0x286, i);
            }
        }
        HuPrcSleep(0x28);
        MBStatusShowAll();
        maxCoins = -1;
        mbTauntOffF = 0;
        j = -1;
        for (i = 0; i < 4; i++) {
            MBPlayerVibrateObjKill(data[i]);
            if ((mask & (1 << i)) != 0 && maxCoins < GwPlayer[i].coin) {
                maxCoins = GwPlayer[i].coin;
                j = i;
            }
        }
        for (i = 0; i < 4; i++) {
            if ((mask & (1 << i)) != 0) {
                MBCoinChangeStatusCreate(i, -GwPlayer[i].coin);
                if (i == j) {
                    MBCoinTakeCreateSound(i, -GwPlayer[i].coin, 1);
                } else {
                    MBCoinTakeCreateSound(i, -GwPlayer[i].coin, 0);
                }
            }
        }
        HuPrcSleep(0x1E);
        GwSystem.boardData.halfWordBytes[1] = 5;
        MB6_BombCountUpdate();
    } else {
        MessageTable msgs;

        msgs = mb6ev_bombCountMesTbl;
        MBWinInsertOpen(0xF00, (char *)msgs.entries[GwSystem.boardData.halfWordBytes[1] - 1], 0, 0, 0, 0);
        MBWinKeyWaitKeep(GwSystem.current_player_index);
        MBWinClose();
    }

    if (MBKettouPlayerBitGet(0) == 0) {
        MBCameraFocusModeSet(3);
    } else {
        player = MBPlayerGet(-1);
        HuPrcChildLink(HuPrcCurrentGet(),
                       MBPlayerPosMoveCreate(&camPos, &player->player_obj->coords, &camPos, 0x14));
        HuPrcChildWatch();
        MBCameraFocusModeSet(1);
    }
    MBBackThreadPriHighSet();
}

void MB6Ev_BridgeSwapExec(s32 arg0) {
    Vec cameraPos;
    s32 masuIds[2];
    s32 index;
    SpaceData *masu;
    GW_PLAYER *player;
    Process *process;
    Object *model;

    player = MBPlayerGet(-1);
    masuIds[0] = 0x75;
    masuIds[1] = 0x70;
    switch (arg0) {
        case 0x34:
        case 0x38:
            index = 0;
            break;
        default:
            index = 1;
            break;
    }

    masu = MBMasuGet(masuIds[index]);
    HuVecCopy3F(&cameraPos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&cameraPos);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBPlayerPosMoveCreate(&cameraPos, &masu->coords, &cameraPos, 0x1E));
    HuPrcChildWatch();

    model = mb6_bridgeMdl[index];
    if (GwSystem.boardData.halfWordBytes[0] == index) {
        HuAudFXPlay(0x1BE);
        Hu3DMotionAttrSet(model->omObj1->model[0], 3, 4);
        while (MBMotionStartCheck(model) == 0) {
            HuPrcVSleep();
        }
    } else {
        HuAudFXPlay(0x1BF);
        Hu3DMotionAttrSet(model->omObj1->model[0], 7, 0);
        MBModelMotionWait(model);
    }

    WipeCreateOut(WIPE_QUESTION, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    index ^= 1;
    masu = MBMasuGet(masuIds[index]);
    HuVecCopy3F(&cameraPos, &masu->coords);
    HuPrcSleep(2);
    WipeCreateIn(WIPE_QUESTION, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    model = mb6_bridgeMdl[index];
    if (GwSystem.boardData.halfWordBytes[0] == index) {
        HuAudFXPlay(0x1BE);
        Hu3DMotionAttrSet(model->omObj1->model[0], 3, 4);
        while (MBMotionStartCheck(model) == 0) {
            HuPrcVSleep();
        }
    } else {
        HuAudFXPlay(0x1BF);
        Hu3DMotionAttrSet(model->omObj1->model[0], 7, 0);
        MBModelMotionWait(model);
    }

    MBDlgResultWinExec(0x1100);
    GwSystem.boardData.halfWordBytes[0] ^= 1;
    if (MBKettouPlayerBitGet(0) == 0) {
        MBCameraFocusModeSet(3);
    } else {
        WipeCreateOut(WIPE_QUESTION, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        MBCameraFocusModeSet(1);
        HuPrcSleep(2);
        WipeCreateIn(WIPE_QUESTION, 0x10);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
    }
}

void MB6Ev_Hatena(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    HuPrcSleep(8);
    switch (masu) {
        case 1:
        case 4:
        case 6:
        case 8:
        case 0x37:
        case 0x4D:
            MB6Ev_BombCountExec();
            break;
        default:
            MB6Ev_BridgeSwapExec(masu);
            break;
    }
    omDelPrcObj(0);
}

void MB6Ev_ChangeMasuTypeSet(void) {
    s32 i;

    for (i = 0; mb6_changeMasuTbl[i] != -1; i++) {
        if (MBMasuGet(mb6_changeMasuTbl[i])->space_type != SPACE_STAR) {
            MBMasuTypeSet(mb6_changeMasuTbl[i], mb6_changeMasuTypeTbl[GwSystem.boardData.halfWordBytes[2]]);
        }
    }
    MBMasuTypeListCreate();
}

void MB6Ev_ChangeMasuTypeRoll(void) {
    s32 next;
    s32 prev;

    do {
        next = MBRand(10.0f);
        prev = GwSystem.boardData.halfWordBytes[2];
    } while (prev != -1 && mb6_changeMasuTypeTbl[prev] == mb6_changeMasuTypeTbl[next]);
    GwSystem.boardData.halfWordBytes[2] = next;
}

void MB6Ev_HoleEnter(void) {
    MasuIdTable masuIds;
    Vec rotation;
    GW_PLAYER *player;
    SpaceData *masu;
    void *dialog;
    f32 scale;
    s32 playerIdx;
    s32 index;

    player = MBPlayerGet(-1);
    playerIdx = GwSystem.current_player_index;
    masuIds = mb6ev_holeMasuTbl;
    MBSaiNumKill(playerIdx);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x84:
            index = 0;
            break;
        case 0x76:
            index = 1;
            break;
        case 0x85:
        default:
            index = 2;
            break;
    }
    masu = MBMasuGet(masuIds.entries[index]);
    MBVecDirGet(&player->player_obj->coords, &masu->coords, &player->player_obj->rot);
    MBPlayerMotionSet(-1, 2, 0);
    MBModelJumpSet(player->player_obj, 10.0f, -1.4f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords,
                                                            &masu->coords,
                                                            &player->player_obj->coords, 10));
    HuPrcChildWatch();
    player->player_obj->velocity.y = player->player_obj->velocity.z = 0.0f;
    MBPlayerMotionSet(-1, -1, 2);
    MBVecForwardSet(&rotation);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBVecRotLerpCreate(&player->player_obj->rot, &rotation,
                                                     &player->player_obj->rot, 10));
    HuAudFXPlay(0x1BC);
    dialog = MBPlayerVibrateObjCreate(-1, 2, 5);
    scale = 1.0f;
    player->stat |= 4;
    while (player->player_obj->velocity.x >= -3.0f) {
        player->player_obj->velocity.x -= 1.0f;
        HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
        scale -= 0.1f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuPrcVSleep();
    }
    scale = 0.0f;
    HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
    HuPrcChildWatch();
    MBPlayerVibrateObjKill(dialog);
    WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuVecCopy3F(&player->player_obj->coords, &MBMasuGet(0x8B)->coords);
    HuPrcSleep(2);
    WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x1BC);
    while (player->player_obj->velocity.x <= 15.0f) {
        player->player_obj->velocity.x += 1.5f;
        HuVecCopyXYZ(&player->player_obj->scale, scale, scale, scale);
        scale += 0.08f;
        if (scale > 1.0f) {
            scale = 1.0f;
        }
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    player->stat &= ~4;
    masu = MBMasuGet(0x8A);
    MBVecDirGet(&player->player_obj->coords, &masu->coords, &player->player_obj->rot);
    MBPlayerMotionSet(-1, 2, 0);
    MBModelJumpSet(player->player_obj, 10.0f, -1.5f);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&player->player_obj->coords,
                                                            &masu->coords,
                                                            &player->player_obj->coords, 14));
    HuPrcChildWatch();
    MBPlayerMotionSet(-1, -1, 2);
    MBVecForwardSet(&rotation);
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBVecRotLerpCreate(&player->player_obj->rot, &rotation,
                                                     &player->player_obj->rot, 5));
    HuPrcChildWatch();
    MBMoveMasuSet(-1, 1, 7);
    MBMoveBackMasuSet(-1, 1, 0);
    MBSaiNumShow(playerIdx);
    HuPrcSleep(10);
    MB6Ev_HoleExitBranch();
}

void MB6Ev_OpStarMapView(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &mb6ev_opStarMapViewRect);
    MB6_ObjectSetup();
    MBStart(2);
    omAddPrcObj(MB6Ev_StarMapView, 0x1005, 0x1000, 0);
}

s32 MB6_ComNKinokoTargetGet(void) {
    s32 i;
    DecisionTreeNonLeafNode *data;
    GW_SYSTEM *loc = &GwSystem;

    data = mb6_itemNKinokoTargetComTree[loc->star_spawn_indices[loc->current_star_spawn]];
    MBComTreePlayerSet(loc->current_player_index);
    if (MBComTreeExec(mb6_itemNKinokoSelfComTree) == 0) {
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

s32 MB6_ComRKinokoTargetGet(void) {
    s32 i;
    DecisionTreeNonLeafNode *data1;
    DecisionTreeNonLeafNode *data2;
    GW_SYSTEM *loc = &GwSystem;

    data1 = mb6_itemRKinokoSelfComTree[loc->star_spawn_indices[loc->current_star_spawn]];
    data2 = mb6_itemRKinokoTargetComTree[loc->star_spawn_indices[loc->current_star_spawn]];
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

s32 MB6_ComItemExcessCheck(void) {
    s32 temp_s0;
    s32 phi_v1;
    GW_SYSTEM *loc;
    loc = &GwSystem;

    temp_s0 = loc->total_turns - loc->current_turn + 1;

    phi_v1 = MBItemFindEmpty(-1);
    if (phi_v1 == -1) {
        phi_v1 = 3;
    }

    return (phi_v1 < temp_s0) ? 0 : 1;
}

s32 MB6_ComRobItemSafeCheck(s32 arg0, s32 arg1) {
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

const ModelIdTable mb6ev_bombExplodeMdlTbl = { { 0x000B0010, 0x000B0011, 0x000B001B } };

const MessageTable mb6ev_bombCountMesTbl = { { 0xF04, 0xF03, 0xF02, 0xF01 } };

const MasuIdTable mb6ev_holeMasuTbl = { { 0x85, 0x78, 0x87 } };

s32 MB6_ComItemDecide(void) {
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
                if (MB6_ComItemExcessCheck() != 0) {
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
                if (MBRandCheck100(70) != 0 && MB6_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (MB6_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb6_itemSKinokoComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (MB6_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb6_itemKSuitComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(mb6_itemWarpBlockComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(mb6_itemNKinokoComTree) == 0) {
                    s32 target = MB6_ComNKinokoTargetGet();

                    mb6_comNKinokoTarget = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(mb6_itemRKinokoComTree) == 0) {
                    s32 target = MB6_ComRKinokoTargetGet();

                    mb6_comRKinokoTarget = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, mb6_comRobBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < mbItemComWeightTbl[it]) {
                                    best = mbItemComWeightTbl[it];
                                    mb6_comRobBoxTarget = i;
                                }
                            }
                        }
                    }
                }
                if (mb6_comRobBoxTarget == -1) {
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
                for (i = 0, mb6_comExchangeBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += mbItemComWeightTbl[it];
                            }
                        }
                        if (best < count) {
                            mb6_comExchangeBoxTarget = i;
                            best = count;
                        }
                    }
                }
                if (mb6_comExchangeBoxTarget == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (MB6_ComRobItemSafeCheck(0x32, 0xA) == 0) {
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
                if (MB6_ComRobItemSafeCheck(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(mb6_itemMajinLampComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && MB6_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(mb6_itemStarYokeComTree) != 0) {
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

s32 MB6_ComShopItemDecide(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = mb6_comShopItemOrderTbl[player->chr][i];

        found = MB6Ev_ShopItemIdxGet(val);
        if (found == -1) {
            continue;
        }
        if (mbItemPriceTbl[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(mb6_comShopItemRateTbl[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (MB6Ev_ShopItemIdxGet(0xE) == found) {
            return found + 1;
        }
        if (MB6Ev_ShopItemIdxGet(0xB) == found && mbItemPriceTbl[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (MB6Ev_ShopItemIdxGet(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(mb6_comShopKeyComTree[mb6ev_shopNo]) == 0 && GwPlayer[loc->current_player_index].coin >= mbItemPriceTbl[1]) {
        s32 route = MB6Ev_ShopItemIdxGet(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(mb6_comShopItemComTree[mb6ev_shopNo]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = mb6_comShopItemOrderTbl[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = MB6Ev_ShopItemIdxGet(val);
            if (found == -1) {
                continue;
            }
            if (mbItemPriceTbl[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(mb6_comShopItemRateTbl[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = MB6Ev_ShopItemIdxGet(0);
    if (found != -1) {
        return found + 1;
    }
    mb6_comShopCancelF = 1;
    return MB6Ev_ShopItemNumGet() + 2;
}

s32 MB6_ComShopEnterDecide(void) {
    if (mb6_comShopCancelF != 0) {
        mb6_comShopCancelF = 0;
        return 2;
    }
    return MBComTreeExec(mb6_comShopEnterComTree[mb6ev_shopNo]) + 1;
}
