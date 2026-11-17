#include "ChillyWaters.h"
#include "game/overlays/party/common/back.h"
#include "game/overlays/party/common/model.h"
#include "game/overlays/party/common/move.h"
#include "game/overlays/party/common/item.h"
#include "game/overlays/party/common/scroll.h"
#include "game/overlays/party/common/pause.h"
#include "game/overlays/party/common/main.h"
#include "game/overlays/party/common/player.h"
#include "game/overlays/party/common/vibrate.h"
#include "game/overlays/party/common/helpwin.h"
#include "game/overlays/party/common/vec.h"
#include "game/overlays/party/common/com.h"
#include "game/overlays/party/common/mapfull.h"
#include "game/overlays/party/common/sai.h"
#include "game/overlays/party/common/window.h"
#include "game/overlays/party/common/status.h"
#include "game/overlays/party/common/coinchange.h"
#include "game/overlays/party/common/ksuit.h"
#include "game/overlays/party/common/brancharrow.h"
#include "game/overlays/party/common/branch.h"

#define GET_STAR_MODEL() mb1_starGuideMdl[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]

//TODO: this is all kinds of a mess, what was this originally?
#define MOTION_ID_GET(n, tmp, cnt)                                       \
    for ((tmp) = (u16 *)mbPlayerMotTbl[0], (cnt) = (n);  \
         (cnt) != 0;                                                     \
         (cnt)--, (tmp) += 2) {                                          \
    }                                                                    \
    motId = tmp[1];

typedef struct UnkStar {
/* 0x00 */ char unk_00[8];
/* 0x08 */ Vec pos;
} UnkStar; //sizeof?

typedef struct UnkStarWork {
    /* 0x00 */ char pad00[0xC];
    /* 0x0C */ Vec unk_0C;
} UnkStarWork; /* size >= 0x18 */

typedef struct UnkChillyWaters {
    Vec coords;
    f32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    Object* unk_18;
    u16 unk_1C;
    char unk_1E[2];
} UnkChillyWaters; //sizeof 0x20

typedef struct UnkThing {
    Object* unk_00;
    Object* unk_04;
    s32 unk_08;
    s32 unk_0C;
    char unk_10[0x10];
} UnkThing;

typedef struct SnowmanMoveWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ Vec dest;
    /* 0x18 */ Vec *out;
    /* 0x1C */ f32 speed;
} SnowmanMoveWork;

typedef struct SnowmanRollWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 order;
    /* 0x0C */ s32 path;
    /* 0x10 */ s32 count;
    /* 0x14 */ char unk14[0xC];
} SnowmanRollWork; // Size 0x20

extern f32 mb1ev_snowmanSpeed;
extern f32 mb1ev_snowmanCurSpeed;
extern Object* mb1ev_gambleCoinMdl;
extern const char mb1ev_numFmtStr[];
extern s32 mb1ev_itemPhoneWaveSpr;
extern s32 mb1ev_shopHostNo;
extern s32 mb1ev_shopItemRow;
extern u8* mb1ev_shopItemEnableTbl;
extern Object *mb1_gateBaseMdl;
extern Object *mb1_gateMdl[];
extern Process* mb1_starGuideHoverProc[8];
extern Object* mb1_starGuideBaseMdl;
extern Object* mb1ev_teresaCoinMdl;
extern s32 mb1_comTeresaType;
extern s32 mb1_comTeresaTarget;
extern Object* mb1_starGuideMdl[];
extern Process* mb1ev_starGuideInProc;
extern Object* mb1ev_starGuideInMdl;
extern Object* mb1_teresaGuideMdl[];
extern Object* mb1_teresaGuideBaseMdl;
extern s32 mb1ev_tereYokeSparkSpr;
extern s32 mb1ev_tereYokePlayer;
extern Object* mb1ev_koopaCardCoinMdl;
extern Object* mb1ev_koopaCardMdl;
extern s32 mb1_comExchangeBoxTarget;
extern s32 mb1_comRobBoxTarget;
extern Object *mb1ev_kinokoMarkMdl[];
extern omObjData *mb1ev_kinokoMarkObj[];
extern s32 mb1_comRKinokoTarget;
extern s32 mb1ev_snowmanHitTbl[];
extern Object *mb1ev_snowmanRollMdl;
extern Process *mb1ev_actionTimeProc;
extern Object *mb1ev_snowmanMdl;
extern f32 mb1ev_snowmanSpeed;

s16 MB1Ev_StarGuideMasuGet(void);
omObjData *MBModelTurnCreate(Object *arg0, Vec *arg1, s32 arg2);
void MB1Ev_StarGetExec(Object*);
s32 MB1Ev_IceCrackCreate(s16, s16); // Defined as void, but this caller uses the result.
void MB1Ev_IceCrackKill(s32);
void MB1Ev_LakeWaveProc(void);
void MB1Ev_LakePlayerJumpProc(void);
void MB1Ev_LakeIceBreakProc(void);
void MB1Ev_BankKoopaCardExec(void);
void MB1Ev_TereYokeSprayProc(void);
void MB1Ev_ItemLampSmokeObjMain(omObjData*);
Process *MB1Ev_SnowmanMoveCreate(Vec *arg0, Vec *arg1, Vec *out, f32 speed);
void MB1Ev_ItemUseFadeOut(void);
void MB1Ev_ShopMasu(void);
void MB1Ev_GambleCoinProc(void);
void MB1Ev_BankMasu(void);
void MB1Ev_Branch1(void);
void MB1Ev_Branch1Rev(void);
void MB1Ev_Branch2(void);
void MB1Ev_Branch2Rev(void);
void MB1Ev_Branch3(void);
void MB1Ev_Branch3Rev(void);
void MB1Ev_Branch4(void);
void MB1Ev_KeyManMasu(void);
void MB1Ev_Lake(void);
void MB1Ev_NKinokoTurnStart(void);
void MB1Ev_RKinokoTurnStart(void);
void MB1Ev_Snowman(void);
void MB1Ev_StarMasu(void);
void MB1Ev_Turuturu(void);
void MB1Ev_Branch5(void);
void MB1Ev_Branch6(void);
void MB1Ev_Branch7RKinoko(void);
void MB1Ev_Branch8RKinoko(void);
void MB1Ev_Branch9RKinoko(void);
void MB1Ev_Branch10RKinoko(void);
void MB1Ev_Branch11RKinoko(void);
void MB1Ev_Branch12RKinoko(void);
void MB1Ev_Merge1(void);
void MB1Ev_Merge2(void);
void MB1Ev_Merge3(void);
void MB1Ev_Merge4(void);
void MB1Ev_Merge5(void);
void MB1Ev_Merge6(void);
void MB1Ev_Merge7(void);
void MB1Ev_Merge8(void);
void MB1Ev_Merge9(void);
void MB1Ev_Merge10(void);
void MB1Ev_Merge11(void);
void MB1Ev_Merge12(void);
void MB1Ev_Merge13(void);
void MB1Ev_Merge14(void);
void MB1Ev_Merge15(void);
void MB1Ev_Merge16(void);
void MB1Ev_Merge17(void);
void MB1Ev_Merge18(void);
void MB1Ev_RevFlagClear(void);
void MB1Ev_Merge19(void);
void MB1Ev_Merge20(void);
void MB1Ev_Merge21(void);
void MB1Ev_Merge22(void);
void MB1Ev_Gate1Close(void);
void MB1Ev_Gate2Close(void);
void MB1Ev_TuruturuCheck(void);

s16 mb1ev_starOrderTbl[] = { 1, 2, 3, 0, 4, 5, 6, 7 };

s16 mb1ev_starOrderGroupTbl[] = { 0, 0, 0, 1, 1, 1, 1, 2 };

s16 mb1ev_starFlag[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb1ev_starMasu[] = { 54, 47, 94, 18, 81, 96, 77, 41 };

s16 mb1ev_starGuideMasu[] = { 98, 99, 100, 101, 102, 103, 104, 105 };

s32 mb1ev_starGuideFaceTbl[] = { 0xA007E, 0xA007F, 0xA0080, 0xA0081, 0xA0082, 0xA0083, 0xA0084 };

s32 mb1ev_starGuideMesTbl[] = { 0x5E02, 0x5E03, 0x5E04, 0x5E05, 0x5E06, 0x5E07, 0x5E08 };

s32 mb1ev_starGetTeresaF = 0;

s32 mb1ev_snowmanRollF = 0;

f32 mb1ev_snowmanLastSpeedNo = -1.0f;

Object *mb1ev_snowmanBaseMdl = NULL;

Object *mb1ev_snowmanBaseEmptyMdl = NULL;

s16 mb1_masuBlockExtTbl = -1;

s16 mb1_masuBlockTbl[] = {
    54, 47, 94, 18, 81, 96, 77, 41,
    -1, 0
};

s16 mb1_starGuideMapIconOfsTbl[][2] = {
    { 7, -1 },
    { 1, -6 },
    { 1, -7 },
    { 1, -7 },
    { -5, -5 },
    { 2, -7 },
    { 1, -7 },
    { -4, -9 }
};

s16 mb1_teresaGuideMapIconOfsTbl[][2] = {
    { 2, 0 },
    { 2, 0 }
};

s16 mb1_bankMapIconOfsTbl[][2] = {
    { 1, -2 },
    { 0, -4 }
};

s16 mb1_shopMapIconOfsTbl[][2] = {
    { 1, -4 },
    { 5, 0 }
};

s16 mb1_gateMapIconOfsTbl[][2] = {
    { 0, 0 },
    { 0, -3 }
};

s16 mb1_gateDirMasuTbl[][2] = {
    { 123, 76 },
    { 121, 63 }
};

s16 mb1_starGuideMdlMasuTbl[] = { 98, 99, 100, 101, 102, 103, 104, 105 };

s16 mb1_starGuideFlagTbl[] = { 6, 7, 8, 9, 10, 11, 12, 13 };

s16 mb1_teresaGuideMasuTbl[] = { 106, 0 };

s16 mb1_bankCoinMasuTbl[] = { 114, 112 };

Vec mb1_bankCoinOfsTbl[] = {
    { -3.0f, 0.0f, -2.0f },
    { 0.0f, 2.0f, 2.0f },
    { 1.0f, 5.5f, -3.0f },
    { 3.5f, 8.0f, 4.0f },
    { -1.0f, 12.0f, 11.0f }
};

Vec mb1_bankCoinRotTbl[] = {
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { -15.0f, 0.0f, 0.0f },
    { 20.0f, 0.0f, -30.0f },
    { 45.0f, 0.0f, 45.0f }
};

s16 mb1_gateMasuTbl[] = { 109, 147 };

u8 mb1_gateMdlTbl[][2] = {
    { 0, 38 },
    { 0, 39 },
    { 0, 40 },
    { 0, 41 },
    { 0, 42 },
    { 0, 43 }
};

u32 mb1_gateMot1[] = { 1, 0x130163 };

u32 mb1_gateMot2[] = { 1, 0x130168 };

u32 mb1_gateMot3[] = { 1, 0x13016F };

u32 mb1_gateMot4[] = { 1, 0x130176 };

u32 mb1_gateMot5[] = { 1, 0x130180 };

u32 mb1_gateMot6[] = { 1, 0x130184 };

u32 *mb1_gateMotTbl[] = { mb1_gateMot1, mb1_gateMot2, mb1_gateMot3, mb1_gateMot4, mb1_gateMot5, mb1_gateMot6 };

s32 mb1_gateOpenSeTbl[] = {
    328, 328, 328, 328, 328, 328, -1, -1,
    -1
};

s32 mb1_gateOpenDelaySeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb1_gateOpenDelayTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s32 mb1_gateCloseSeTbl[] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1
};

s16 mb1_bankMapIconMasuTbl[] = { 113, 111 };

s16 mb1_shopMapIconMasuTbl[] = { 115, 110 };

DecisionTreeNonLeafNode mb1ev_branch2ComTree0[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1C96A846 } },
    { 2, { .data = 0x00000042 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch2ComTree1[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x1C96A846 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch2ComTree2[] = {
    { 2, { .data = 0x00000042 }, { .data = 0x1C96A846 } },
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch2ComTree[] = { mb1ev_branch2ComTree0, mb1ev_branch2ComTree1, mb1ev_branch2ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch2RevComTree0[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x0C96A846 } },
    { 2, { .data = 0x00000040 }, { .data = 0x1C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch2RevComTree1[] = {
    { 2, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 2, { .data = 0x00000040 }, { .data = 0x1C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch2RevComTree2[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x1C96A846 } },
    { 2, { .data = 0x00000001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch2RevComTree[] = { mb1ev_branch2RevComTree0, mb1ev_branch2RevComTree1, mb1ev_branch2RevComTree2 };

DecisionTreeNonLeafNode mb1ev_branch3ComTree0[] = {
    { 2, { .data = 0x00000043 }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000004 }, { .data = 0x064C9932 } },
    { 2, { .data = 0x00000038 }, { .data = 0x1C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch3ComTree1[] = {
    { 2, { .data = 0x00000038 }, { .data = 0x1C96A846 } },
    { 2, { .data = 0x00000047 }, { .data = 0x0A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch3ComTree2[] = {
    { 2, { .data = 0x00000047 }, { .data = 0x1A119E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch3ComTree[] = { mb1ev_branch3ComTree0, mb1ev_branch3ComTree1, mb1ev_branch3ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch3RevWalkComTree[] = {
    { 3, { .data = 0x00000004 }, { .data = 0x1BF6A33C } },
    { 3, { .data = 0x00000010 }, { .data = 0x0BF6A33C } },
    { 3, { .data = 0x00000003 }, { .data = 0x0BF6A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevKeyRankComTree[] = {
    { 3, { .data = 0x00000002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .node_data = mb1ev_branch3RevWalkComTree } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevKeyCoinComTree[] = {
    { 3, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .node_data = mb1ev_branch3RevWalkComTree } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevKeyComTree[] = {
    { 2, { .data = 0x00000004 }, { .data = 0x0C96A846 } },
    { 5, { .data = 0x0000000C }, { .node_data = mb1ev_branch3RevKeyRankComTree } },
    { 12, { .data = 0x0000000A }, { .node_data = mb1ev_branch3RevKeyCoinComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x164C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevStar13ComTree[] = {
    { 3, { .data = 0x00000008 }, { .data = 0x1B54233C } },
    { 3, { .data = 0x00000020 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .node_data = mb1ev_branch3RevWalkComTree } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevComTree0[] = {
    { 2, { .data = 0x0000000A }, { .node_data = mb1ev_branch3RevStar13ComTree } },
    { 8, { .data = 0x00000001 }, { .node_data = mb1ev_branch3RevKeyComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb1ev_branch3RevWalkComTree } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevComTree1[] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch3RevComTree2[] = {
    { 2, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch3RevComTree[] = { mb1ev_branch3RevComTree0, mb1ev_branch3RevComTree1, mb1ev_branch3RevComTree2 };

DecisionTreeNonLeafNode mb1ev_branch4ComTree = { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } };

DecisionTreeNonLeafNode mb1ev_branch5ComTree0[] = {
    { 2, { .data = 0x0000001C }, { .data = 0x0B54233C } },
    { 2, { .data = 0x000000E3 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch5ComTree1[] = {
    { 2, { .data = 0x0000000E }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B54233C } }
};

DecisionTreeNonLeafNode mb1ev_branch5ComTree2[] = {
    { 2, { .data = 0x0000000E }, { .data = 0x0B54233C } },
    { 2, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch5ComTree[] = { mb1ev_branch5ComTree0, mb1ev_branch5ComTree1, mb1ev_branch5ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch6ComTree0[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1B54233C } },
    { 2, { .data = 0x00000020 }, { .data = 0x0C96A846 } },
    { 2, { .data = 0x000000C3 }, { .data = 0x1C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch6ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x18CF1928 } }
};

DecisionTreeNonLeafNode mb1ev_branch6ComTree2[] = {
    { 2, { .data = 0x00000020 }, { .data = 0x1C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A846 } }
};

DecisionTreeNonLeafNode *mb1ev_branch6ComTree[] = { mb1ev_branch6ComTree0, mb1ev_branch6ComTree1, mb1ev_branch6ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch7ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch7ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch7ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch7ComTree[] = { mb1ev_branch7ComTree0, mb1ev_branch7ComTree1, mb1ev_branch7ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch8ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch8ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch8ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch8ComTree[] = { mb1ev_branch8ComTree0, mb1ev_branch8ComTree1, mb1ev_branch8ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch9ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch9ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch9ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch9ComTree[] = { mb1ev_branch9ComTree0, mb1ev_branch9ComTree1, mb1ev_branch9ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch10ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch10ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch10ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch10ComTree[] = { mb1ev_branch10ComTree0, mb1ev_branch10ComTree1, mb1ev_branch10ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch11ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch11ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch11ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch11ComTree[] = { mb1ev_branch11ComTree0, mb1ev_branch11ComTree1, mb1ev_branch11ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch12ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch12ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch12ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch12ComTree[] = { mb1ev_branch12ComTree0, mb1ev_branch12ComTree1, mb1ev_branch12ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch13ComTree0[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch13ComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode mb1ev_branch13ComTree2[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch13ComTree[] = { mb1ev_branch13ComTree0, mb1ev_branch13ComTree1, mb1ev_branch13ComTree2 };

DecisionTreeNonLeafNode mb1ev_branch14ComTree0Star5[] = {
    { 9, { .data = 0x00000010 }, { .data = 0x1B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb1ev_branch14ComTree0[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0B541E32 } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1ev_branch14ComTree0Star5 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb1ev_branch14ComTree1Star7[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1C96A33C } },
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb1ev_branch14ComTree1[] = {
    { 2, { .data = 0x00000080 }, { .node_data = mb1ev_branch14ComTree1Star7 } },
    { 0, { .data = 0x00000000 }, { .data = 0x1BF6A33C } }
};

DecisionTreeNonLeafNode mb1ev_branch14ComTree2Star7[] = {
    { 9, { .data = 0x00000008 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x1A119E32 } }
};

DecisionTreeNonLeafNode mb1ev_branch14ComTree2[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x1B541E32 } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1ev_branch14ComTree2Star7 } },
    { 0, { .data = 0x00000000 }, { .data = 0x064C9932 } }
};

DecisionTreeNonLeafNode *mb1ev_branch14ComTree[] = { mb1ev_branch14ComTree0, mb1ev_branch14ComTree1, mb1ev_branch14ComTree2 };

event_list_entry mb1_branch1EventTbl[] = {
    { 8, 1, MB1Ev_Branch1 },
    { 0, 0, NULL }
};

event_list_entry mb1_branch1RevEventTbl[] = {
    { 1, 1, MB1Ev_Branch1Rev },
    { 0, 0, NULL }
};

s16 mb1ev_branch2Masu[][3] = {
    { 77, 53, -1 },
    { 66, 53, -1 },
    { 66, 77, -1 }
};

BranchLink mb1ev_branch2Link[][2] = {
    { { 15, 0, 0 }, { 2, 0, 0 } },
    { { 1, 12, 1 }, { 2, 0, 0 } },
    { { 1, 12, 1 }, { 15, 0, 0 } }
};

event_list_entry mb1_branch2EventTbl[] = {
    { 1, 2, MB1Ev_Branch2 },
    { 0, 0, NULL }
};

s16 mb1ev_branch2RevMasu[][3] = {
    { 50, 51, -1 },
    { 57, 51, -1 },
    { 57, 50, -1 }
};

BranchLink mb1ev_branch2RevLink[][2] = {
    { { 3, 5, 1 }, { 4, 0, 0 } },
    { { 2, 3, 0 }, { 4, 0, 0 } },
    { { 2, 3, 0 }, { 3, 5, 1 } }
};

event_list_entry mb1_branch2RevEventTbl[] = {
    { 1, 2, MB1Ev_Branch2Rev },
    { 0, 0, NULL }
};

s16 mb1ev_branch3Masu[][3] = {
    { 45, 8, -1 },
    { 7, 8, -1 },
    { 7, 45, -1 }
};

BranchLink mb1ev_branch3Link[][2] = {
    { { 3, 0, 0 }, { 5, 0, 0 } },
    { { 15, 9, 1 }, { 5, 0, 0 } },
    { { 15, 9, 1 }, { 3, 0, 0 } }
};

event_list_entry mb1_branch3EventTbl[] = {
    { 1, 2, MB1Ev_Branch3 },
    { 0, 0, NULL }
};

s16 mb1ev_branch3RevMasu[][3] = {
    { 75, 20, -1 },
    { 19, 20, -1 },
    { 19, 75, -1 }
};

BranchLink mb1ev_branch3RevLink[][2] = {
    { { 6, 0, 0 }, { 10, 0, 0 } },
    { { 5, 10, 1 }, { 10, 0, 0 } },
    { { 5, 10, 1 }, { 6, 0, 0 } }
};

event_list_entry mb1_branch3RevEventTbl[] = {
    { 1, 2, MB1Ev_Branch3Rev },
    { 0, 0, NULL }
};

s16 mb1ev_branch4Masu[] = { 87, 70, 61, -1 };

s16 mb1ev_branch4From61Masu[] = { 87, 70, -1, 0 };

s16 mb1ev_branch4RKinokoFrom60Masu[] = { 87, 70, 61, 86, -1, 0 };

s16 mb1ev_branch4RKinokoFrom87Masu[] = { 60, 70, 61, 86, -1, 0 };

s16 mb1ev_branch4RKinokoFrom70Masu[] = { 60, 87, 61, 86, -1, 0 };

s16 mb1ev_branch4RKinokoFrom61Masu[] = { 60, 87, 70, 86, -1, 0 };

s16 mb1ev_branch4RKinokoMasu[] = { 60, 87, 70, 61, -1, 0 };

event_list_entry mb1_branch4EventTbl[] = {
    { 1, 2, MB1Ev_Branch4 },
    { 0, 0, NULL }
};

s16 mb1ev_branch5Masu[][3] = {
    { 79, 31, -1 },
    { 30, 31, -1 },
    { 30, 79, -1 }
};

BranchLink mb1ev_branch5Link[][2] = {
    { { 11, 0, 0 }, { 12, 1, 0 } },
    { { 10, 10, 1 }, { 12, 1, 0 } },
    { { 10, 10, 1 }, { 11, 0, 0 } }
};

event_list_entry mb1_branch5EventTbl[] = {
    { 1, 2, MB1Ev_Branch5 },
    { 0, 0, NULL }
};

s16 mb1ev_branch6Masu[][3] = {
    { 95, 35, -1 },
    { 34, 35, -1 },
    { 34, 95, -1 }
};

BranchLink mb1ev_branch6Link[][2] = {
    { { 13, 0, 0 }, { 14, 0, 0 } },
    { { 12, 3, 1 }, { 14, 0, 0 } },
    { { 12, 3, 1 }, { 13, 0, 0 } }
};

event_list_entry mb1_branch6EventTbl[] = {
    { 1, 2, MB1Ev_Branch6 },
    { 0, 0, NULL }
};

s16 mb1ev_branch7Masu[][3] = {
    { 33, 69, -1 },
    { 11, 69, -1 },
    { 11, 33, -1 }
};

BranchLink mb1ev_branch7Link[][2] = {
    { { 1, 9, 0 }, { 16, 4, 1 } },
    { { 1, 7, 1 }, { 16, 4, 1 } },
    { { 1, 7, 1 }, { 1, 9, 0 } }
};

event_list_entry mb1_branch7EventTbl[] = {
    { 1, 1, MB1Ev_Branch7RKinoko },
    { 0, 0, NULL }
};

s16 mb1ev_branch8Masu[][3] = {
    { 2, 52, -1 },
    { 88, 52, -1 },
    { 88, 2, -1 }
};

BranchLink mb1ev_branch8Link[][2] = {
    { { 15, 3, 0 }, { 4, 1, 1 } },
    { { 15, 1, 1 }, { 4, 1, 1 } },
    { { 15, 1, 1 }, { 15, 3, 0 } }
};

event_list_entry mb1_branch8EventTbl[] = {
    { 1, 1, MB1Ev_Branch8RKinoko },
    { 0, 0, NULL }
};

s16 mb1ev_branch9Masu[][3] = {
    { 92, 94, -1 },
    { 78, 94, -1 },
    { 78, 92, -1 }
};

BranchLink mb1ev_branch9Link[][2] = {
    { { 7, 5, 1 }, { 7, 7, 0 } },
    { { 6, 4, 1 }, { 7, 7, 0 } },
    { { 6, 4, 1 }, { 7, 5, 1 } }
};

event_list_entry mb1_branch9EventTbl[] = {
    { 1, 1, MB1Ev_Branch9RKinoko },
    { 0, 0, NULL }
};

s16 mb1ev_branch10Masu[][3] = {
    { 84, 97, -1 },
    { 82, 97, -1 },
    { 82, 84, -1 }
};

BranchLink mb1ev_branch10Link[][2] = {
    { { 11, 5, 0 }, { 13, 2, 1 } },
    { { 11, 3, 1 }, { 13, 2, 1 } },
    { { 11, 3, 1 }, { 11, 5, 0 } }
};

event_list_entry mb1_branch10EventTbl[] = {
    { 1, 1, MB1Ev_Branch10RKinoko },
    { 0, 0, NULL }
};

s16 mb1ev_branch11Masu[][3] = {
    { 13, 94, -1 },
    { 10, 94, -1 },
    { 10, 13, -1 }
};

BranchLink mb1ev_branch11Link[][2] = {
    { { 5, 4, 0 }, { 7, 7, 1 } },
    { { 5, 2, 1 }, { 7, 7, 1 } },
    { { 5, 2, 1 }, { 5, 4, 0 } }
};

event_list_entry mb1_branch11EventTbl[] = {
    { 1, 1, MB1Ev_Branch11RKinoko },
    { 0, 0, NULL }
};

s16 mb1ev_branch12Masu[][3] = {
    { 58, 122, -1 },
    { 56, 122, -1 },
    { 56, 58, -1 }
};

BranchLink mb1ev_branch12Link[][2] = {
    { { 2, 4, 0 }, { 3, 6, 1 } },
    { { 2, 2, 1 }, { 3, 6, 1 } },
    { { 2, 2, 1 }, { 2, 4, 0 } }
};

event_list_entry mb1_branch12EventTbl[] = {
    { 1, 1, MB1Ev_Branch12RKinoko },
    { 0, 0, NULL }
};

event_list_entry mb1_merge1EventTbl[] = {
    { 1, 1, MB1Ev_Merge1 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge2EventTbl[] = {
    { 1, 1, MB1Ev_Merge2 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge3EventTbl[] = {
    { 1, 1, MB1Ev_Merge3 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge4EventTbl[] = {
    { 1, 1, MB1Ev_Merge4 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge5EventTbl[] = {
    { 1, 1, MB1Ev_Merge5 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge6EventTbl[] = {
    { 1, 1, MB1Ev_Merge6 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge7EventTbl[] = {
    { 1, 1, MB1Ev_Merge7 },
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

event_list_entry mb1_merge8EventTbl[] = {
    { 1, 1, MB1Ev_Merge8 },
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

event_list_entry mb1_merge9EventTbl[] = {
    { 1, 1, MB1Ev_Merge9 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge10EventTbl[] = {
    { 1, 1, MB1Ev_Merge10 },
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

event_list_entry mb1_merge11EventTbl[] = {
    { 1, 1, MB1Ev_Merge11 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge12EventTbl[] = {
    { 1, 1, MB1Ev_Merge12 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge13EventTbl[] = {
    { 1, 1, MB1Ev_Merge13 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge14EventTbl[] = {
    { 1, 1, MB1Ev_Merge14 },
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

event_list_entry mb1_merge15EventTbl[] = {
    { 1, 1, MB1Ev_Merge15 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge16EventTbl[] = {
    { 1, 1, MB1Ev_Merge16 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge17EventTbl[] = {
    { 1, 1, MB1Ev_Merge17 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge18EventTbl[] = {
    { 1, 1, MB1Ev_Merge18 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge19EventTbl[] = {
    { 8, 1, MB1Ev_RevFlagClear },
    { 1, 1, MB1Ev_Merge19 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge20EventTbl[] = {
    { 1, 1, MB1Ev_Merge20 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge21EventTbl[] = {
    { 1, 1, MB1Ev_Merge21 },
    { 0, 0, NULL }
};

event_list_entry mb1_merge22EventTbl[] = {
    { 1, 1, MB1Ev_Merge22 },
    { 0, 0, NULL }
};

event_list_entry mb1_keyManMasuEventTbl[] = {
    { 1, 2, MB1Ev_KeyManMasu },
    { 0, 0, NULL }
};

s16 mb1ev_branch13Masu[][3] = {
    { 21, 24, -1 },
    { 74, 24, -1 },
    { 74, 21, -1 }
};

BranchLink mb1ev_branch13Link[][2] = {
    { { 10, 1, 1 }, { 10, 3, 0 } },
    { { 8, 6, 1 }, { 10, 3, 0 } },
    { { 8, 6, 1 }, { 10, 1, 1 } }
};

s16 mb1ev_branch14Masu[][3] = {
    { 64, 37, -1 },
    { 38, 37, -1 },
    { 38, 64, -1 }
};

BranchLink mb1ev_branch14Link[][2] = {
    { { 9, 6, 1 }, { 14, 2, 1 } },
    { { 1, 0, 0 }, { 14, 2, 1 } },
    { { 1, 0, 0 }, { 9, 6, 1 } }
};

event_list_entry mb1_starMasuEventTbl[] = {
    { 1, 1, MB1Ev_StarMasu },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb1ev_bankComTree[] = {
    { 4, { .data = 0x00F50014 }, { .data = 0x0B541E1E } },
    { 0, { .data = 0x00000000 }, { .data = 0x1B541E1E } }
};

u32 mb1ev_bankCoinPileMot[] = { 1, 0xA009D };

event_list_entry mb1_bankMasuEventTbl[] = {
    { 1, 1, MB1Ev_BankMasu },
    { 0, 0, NULL }
};

u8 mb1ev_shopItemRowTbl[][3][4] = {
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } },
    { { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 2, 3, 4, 4 } }
};

s8 mb1ev_shopItemTbl[][5][7] = {
    { { 0, 1, 4, 5, 10, 14, 19 }, { 0, 1, 4, 5, 10, 12, 19 }, { 0, 1, 4, 5, 10, 19, -1 }, { 0, 1, 4, 8, 10, 12, 19 }, { 0, 1, 8, 10, 12, 14, 19 } },
    { { 1, 2, 3, 6, 13, 11, 19 }, { 1, 2, 3, 6, 9, 13, 19 }, { 1, 2, 3, 7, 13, 19, -1 }, { 1, 3, 6, 7, 9, 13, 19 }, { 1, 3, 6, 7, 9, 11, 19 } }
};

u8 mb1ev_shopBagRowTbl[][3][4] = {
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } },
    { { 0, 0, 1, 1 }, { 1, 2, 2, 3 }, { 2, 3, 3, 4 } }
};

s8 mb1ev_shopBagRateTbl[][5][10] = {
    { { 25, 55, 65, 76, 81, 86, 91, 96, 98, 100 }, { 30, 50, 60, 70, 75, 85, 90, 95, 97, 100 }, { 25, 45, 52, 62, 67, 82, 88, 95, 97, 100 }, { 20, 35, 40, 45, 55, 75, 85, 95, 97, 100 }, { 15, 25, 30, 40, 45, 70, 80, 92, 95, 100 } },
    { { 33, 53, 68, 73, 78, 83, 93, 98, 100, 0 }, { 25, 40, 55, 63, 73, 81, 91, 98, 100, 0 }, { 20, 38, 58, 68, 75, 82, 90, 98, 100, 0 }, { 15, 35, 55, 65, 72, 79, 85, 97, 100, 0 }, { 15, 25, 45, 55, 65, 75, 80, 95, 100, 0 } }
};

u8 mb1ev_shopBagItemTbl[][10] = {
    { 0, 1, 4, 5, 8, 10, 12, 14, 15, 16 },
    { 1, 2, 3, 6, 7, 9, 13, 11, 17, 1 }
};

s32 mb1ev_shopItemMesTbl[][2] = {
    { 0x3B05, 0x3D05 },
    { 0x3B06, 0x3D06 },
    { 0x3B07, 0x3D07 },
    { 0x3B08, 0x3D08 },
    { 0x3B09, 0x3D09 }
};

s32 mb1ev_shopEnterMesTbl[] = { 0x3B00, 0x3D00 };

s32 mb1ev_shopNoCoinMesTbl[] = { 0x3B01, 0x3D01 };

s32 mb1ev_shopItemFullMesTbl[] = { 0x3B02, 0x3D02 };

s32 mb1ev_shopLastTurnMesTbl[] = { 0x3B03, 0x3D03 };

s32 mb1ev_shopCancelMesTbl[] = { 0x3B04, 0x3D04 };

u32 mb1ev_shopKinopioMot[] = { 1, 0xA0017 };

u32 mb1ev_shopKoopaJrMot[] = { 1, 0xA00F0 };

s32 mb1ev_shopNo = 0;

event_list_entry mb1_shopMasuEventTbl[] = {
    { 1, 1, MB1Ev_ShopMasu },
    { 0, 0, NULL }
};

f32 mb1ev_teresaSprPosTbl[][2] = {
    { 76.0f, 52.0f },
    { 244.0f, 52.0f },
    { 76.0f, 192.0f },
    { 244.0f, 192.0f }
};

f32 mb1ev_teresaSprDirTbl[][2] = {
    { -1.0f, -1.0f },
    { 1.0f, -1.0f },
    { -1.0f, 1.0f },
    { 1.0f, 1.0f }
};

u8 mb1ev_teresaCoinTurnTbl[][3] = {
    { 1, 5, 15 },
    { 6, 15, 25 },
    { 16, 25, 27 },
    { 26, 35, 30 },
    { 36, 45, 32 },
    { 46, 50, 35 }
};

u8 mb1ev_teresaCoinPenaltyTbl[][3] = {
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

u8 mb1ev_teresaCoinDiffTbl[] = { 9, 7, 4, 1, 0, 0, 0, 0 };

s32 mb1ev_teresaComTargetRateTbl[] = { 50, 80, 100 };

s32 mb1ev_teresaMdlFlipTbl[] = { 1, 0, 1, 0, 0, 1, 0 };

event_list_entry mb1_teresaMasuEventTbl[] = {
    { 1, 1, MB1Ev_Teresa },
    { 0, 0, NULL }
};

event_list_entry mb1_gate1CloseEventTbl[] = {
    { 1, 1, MB1Ev_Gate1Close },
    { 0, 0, NULL }
};

event_list_entry mb1_gate2CloseEventTbl[] = {
    { 1, 1, MB1Ev_Gate2Close },
    { 0, 0, NULL }
};

event_table_entry mb1_commonEventTbl[] = {
    { 54, mb1_starMasuEventTbl },
    { 47, mb1_starMasuEventTbl },
    { 94, mb1_starMasuEventTbl },
    { 18, mb1_starMasuEventTbl },
    { 81, mb1_starMasuEventTbl },
    { 96, mb1_starMasuEventTbl },
    { 77, mb1_starMasuEventTbl },
    { 41, mb1_starMasuEventTbl },
    { 55, mb1_bankMasuEventTbl },
    { 23, mb1_bankMasuEventTbl },
    { 119, mb1_shopMasuEventTbl },
    { 124, mb1_shopMasuEventTbl },
    { 109, mb1_gate1CloseEventTbl },
    { 147, mb1_gate2CloseEventTbl },
    { -1, NULL }
};

event_table_entry mb1_teresaEventTbl[] = {
    { 146, mb1_teresaMasuEventTbl },
    { -1, NULL }
};

f32 mb1ev_itemUsePosTbl[][2] = {
    { 164.0f, 76.0f },
    { 140.0f, 76.0f },
    { 164.0f, 76.0f },
    { 140.0f, 76.0f }
};

f32 mb1ev_itemFadePosTbl[][2] = {
    { 132.0f, 62.0f },
    { 220.0f, 62.0f },
    { 132.0f, 180.0f },
    { 220.0f, 180.0f }
};

f32 mb1ev_robBoxItemEndPosTbl[][2] = {
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f },
    { 164.0f, 66.0f }
};

f32 mb1ev_robBoxItemStartPosTbl[][2] = {
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f },
    { 164.0f, 76.0f }
};

DecisionTreeNonLeafNode mb1ev_shopPhoneComTree[] = {
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

s32 mb1ev_itemPhoneWaveAngleTbl[] = { 20, 60, 30, 50, 70 };

DecisionTreeNonLeafNode mb1ev_keyManUseComTree = { 0, { .data = 0x00000000 }, { .data = 0x0C993264 } };

f32 mb1ev_tereYokeSparkOfsTbl[][2] = {
    { -10.0f, 0.0f },
    { 10.0f, -5.0f },
    { 10.0f, 5.0f },
    { -5.0f, -5.0f },
    { 10.0f, 0.0f },
    { -5.0f, 5.0f }
};

s32 mb1ev_gambleCoinPlayer = -1;

u8 mb1ev_gambleMgTbl[] = { 67, 68, 69, 0 };

u8 mb1ev_gambleMgRateTbl[] = { 20, 60, 100, 0 };

u16 mb1ev_gambleRateTbl[][2] = {
    { 0, 50 },
    { 2, 80 },
    { 4, 90 },
    { 8, 94 },
    { 16, 97 },
    { 32, 99 },
    { 64, 100 }
};

RGB mb1ev_after5NumColorTbl[] = {
    { 240, 222, 53 },
    { 247, 26, 66 }
};

event_list_entry mb1_kinokoTurnEventTbl[] = {
    { 7, 1, MB1Ev_NKinokoTurnStart },
    { 7, 1, MB1Ev_RKinokoTurnStart },
    { 0, 0, NULL }
};

event_table_entry mb1_turnStatusEventTbl[] = {
    { -5, mb1_kinokoTurnEventTbl },
    { -1, NULL }
};

event_list_entry mb1_turuturuEventTbl[] = {
    { 9, 1, MB1Ev_TuruturuCheck },
    { 1, 1, MB1Ev_Turuturu },
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

DecisionTreeNonLeafNode mb1ev_snowmanComTree[] = {
    { 2, { .data = 0x00000043 }, { .data = 0x0A119E32 } },
    { 12, { .data = 0x00000019 }, { .data = 0x00000F32 } },
    { 2, { .data = 0x000000A8 }, { .data = 0x0C96A332 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A28F32 } }
};

DecisionTreeNonLeafNode mb1ev_snowmanPath0ComTree[] = {
    { 2, { .data = 0x000000E1 }, { .data = 0x0B542332 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A50F32 } }
};

DecisionTreeNonLeafNode mb1ev_snowmanPath1ComTree[] = {
    { 2, { .data = 0x000000C1 }, { .data = 0x0B542332 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A50F32 } }
};

DecisionTreeNonLeafNode mb1ev_snowmanPath2ComTree[] = {
    { 2, { .data = 0x0000000E }, { .data = 0x0B542332 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A50F32 } }
};

DecisionTreeNonLeafNode mb1ev_snowmanPath3Star2ComTree[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x0B541E32 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A50F32 } }
};

DecisionTreeNonLeafNode mb1ev_snowmanPath3ComTree[] = {
    { 2, { .data = 0x00000002 }, { .data = 0x0B542332 } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1ev_snowmanPath3Star2ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00A50F32 } }
};

DecisionTreeNonLeafNode *mb1ev_snowmanPathComTree[] = { mb1ev_snowmanPath0ComTree, mb1ev_snowmanPath1ComTree, mb1ev_snowmanPath2ComTree, mb1ev_snowmanPath3ComTree };

s16 mb1ev_snowmanPath0Masu[] = {
    134, 17, 18, 19, 141, 20, 21, 23,
    24, 25, 143, 26, 27, 28, 29, 30,
    144, -1
};

s16 mb1ev_snowmanPath1Masu[] = {
    31, 32, 34, 145, 35, 36, 37, 146,
    38, -1
};

s16 mb1ev_snowmanPath2Masu[] = {
    127, 144, 30, 29, 28, 27, 26, 143,
    25, 24, 23, 21, 20, 141, 19, 18,
    17, -1
};

s16 mb1ev_snowmanPath3Masu[] = {
    16, 15, 14, 13, 12, 10, 9, 8,
    -1, 0
};

s16 *mb1ev_snowmanPathMasuTbl[] = { mb1ev_snowmanPath0Masu, mb1ev_snowmanPath1Masu, mb1ev_snowmanPath2Masu, mb1ev_snowmanPath3Masu };

s16 mb1ev_snowmanEndMasuTbl[] = { 31, 39, 16, 45 };

s16 mb1ev_snowmanDirMasuTbl[] = { 127, 38, 126, 8 };

s16 mb1ev_snowmanStartMasuTbl[] = { 18, 31, 144, 16 };

f32 mb1ev_snowmanOfs2Tbl[][2] = {
    { -7.0f, 0.0f },
    { 7.0f, 0.0f }
};

f32 mb1ev_snowmanOfs3Tbl[][2] = {
    { -7.0f, 4.0f },
    { 7.0f, 4.0f },
    { 0.0f, -8.0f }
};

f32 mb1ev_snowmanOfs4Tbl[][2] = {
    { -7.0f, 4.0f },
    { 7.0f, 4.0f },
    { -7.0f, -8.0f },
    { 7.0f, -8.0f }
};

f32 mb1ev_lakeJumpOfsTbl[][2] = {
    { -7.0f, -7.0f },
    { 7.0f, 7.0f }
};

event_list_entry mb1_snowmanEventTbl[] = {
    { 1, 2, MB1Ev_Snowman },
    { 0, 0, NULL }
};

s32 mb1ev_lakeWaveTbl[][2] = {
    { 90, 17 },
    { 71, 20 },
    { 70, 35 },
    { 87, 38 }
};

s16 mb1ev_lakeMasuTbl[] = {
    90, 89, 87, 71, 70, 84, 85, 86,
    62, 61, 58, 59, 60, -1
};

event_list_entry mb1_lakeEventTbl[] = {
    { 5, 2, MB1Ev_Lake },
    { 0, 0, NULL }
};

event_table_entry mb1_specialEventTbl[] = {
    { 107, mb1_branch1EventTbl },
    { 0, mb1_branch1RevEventTbl },
    { 108, mb1_branch2EventTbl },
    { 122, mb1_branch2RevEventTbl },
    { 130, mb1_branch3EventTbl },
    { 141, mb1_branch3RevEventTbl },
    { 125, mb1_branch4EventTbl },
    { 144, mb1_branch5EventTbl },
    { 145, mb1_branch6EventTbl },
    { 22, mb1_branch7EventTbl },
    { 1, mb1_branch8EventTbl },
    { 93, mb1_branch9EventTbl },
    { 83, mb1_branch10EventTbl },
    { 12, mb1_branch11EventTbl },
    { 57, mb1_branch12EventTbl },
    { 53, mb1_merge1EventTbl },
    { 45, mb1_merge2EventTbl },
    { 51, mb1_merge3EventTbl },
    { 52, mb1_merge4EventTbl },
    { 75, mb1_merge5EventTbl },
    { 78, mb1_merge6EventTbl },
    { 87, mb1_merge7EventTbl },
    { 70, mb1_merge8EventTbl },
    { 74, mb1_merge9EventTbl },
    { 61, mb1_merge10EventTbl },
    { 64, mb1_merge11EventTbl },
    { 20, mb1_merge12EventTbl },
    { 79, mb1_merge13EventTbl },
    { 86, mb1_merge14EventTbl },
    { 95, mb1_merge15EventTbl },
    { 97, mb1_merge16EventTbl },
    { 35, mb1_merge17EventTbl },
    { 69, mb1_merge18EventTbl },
    { 120, mb1_merge19EventTbl },
    { 8, mb1_merge20EventTbl },
    { 38, mb1_merge21EventTbl },
    { 31, mb1_merge22EventTbl },
    { 90, mb1_turuturuEventTbl },
    { 71, mb1_turuturuEventTbl },
    { 62, mb1_turuturuEventTbl },
    { 143, mb1_snowmanEventTbl },
    { 123, mb1_keyManMasuEventTbl },
    { 121, mb1_keyManMasuEventTbl },
    { 76, mb1_keyManMasuEventTbl },
    { 63, mb1_keyManMasuEventTbl },
    { 89, mb1_lakeEventTbl },
    { 84, mb1_lakeEventTbl },
    { 85, mb1_lakeEventTbl },
    { 58, mb1_lakeEventTbl },
    { 59, mb1_lakeEventTbl },
    { 60, mb1_lakeEventTbl },
    { -1, NULL }
};

RectF mb1ev_opStarMapViewRect = { 0.0f, 0.0f, 320.0f, 240.0f };

DecisionTreeNonLeafNode mb1_itemSKinokoStar06SubComTree[] = {
    { 10, { .data = 0x000C0004 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000D0002 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E0003 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar06ComTree[] = {
    { 12, { .data = 0x0000000A }, { .data = 0x0000001E } },
    { 16, { .data = 0x0000000A }, { .node_data = mb1_itemSKinokoStar06SubComTree } },
    { 12, { .data = 0x00000019 }, { .data = 0x0000001E } },
    { 10, { .data = 0x00010008 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00100004 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x0000001E }, { .data = 0x0000001E } },
    { 10, { .data = 0x000A0204 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000023 }, { .data = 0x0000001E } },
    { 10, { .data = 0x0005080A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00060000 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar1ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0000001E } },
    { 10, { .data = 0x00010B0C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030305 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x0000001E } },
    { 10, { .data = 0x0001040A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00100104 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar2ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0000001E } },
    { 10, { .data = 0x00010B0C }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000F0609 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030005 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x0000001E } },
    { 10, { .data = 0x0001060A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00100304 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar3ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0000001E } },
    { 10, { .data = 0x000F0009 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00020006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00030305 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00040001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00050003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00070007 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar45ComTree[] = {
    { 12, { .data = 0x00000014 }, { .data = 0x0000001E } },
    { 10, { .data = 0x000A0208 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x00000019 }, { .data = 0x0000001E } },
    { 10, { .data = 0x00020206 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x0005030A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x00080006 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000B0307 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoStar7ComTree[] = {
    { 12, { .data = 0x00000005 }, { .data = 0x0000001E } },
    { 10, { .data = 0x000A020A }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000C0003 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000E0001 }, { .data = 0x0C96A846 } },
    { 12, { .data = 0x0000000A }, { .data = 0x0000001E } },
    { 10, { .data = 0x00080406 }, { .data = 0x0C96A846 } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemSKinokoComTree[] = {
    { 2, { .data = 0x00000041 }, { .node_data = mb1_itemSKinokoStar06ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemSKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemSKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemSKinokoStar3ComTree } },
    { 2, { .data = 0x00000030 }, { .node_data = mb1_itemSKinokoStar45ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemSKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemKSuitComTree[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x0A119E32 } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar0ComTree[] = {
    { 10, { .data = 0x0001090C }, { .data = 0x0000028A } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 11, { .data = 0x0001090C }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar1ComTree[] = {
    { 10, { .data = 0x000F0709 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000F0709 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar2ComTree[] = {
    { 10, { .data = 0x00070106 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00070106 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar3ComTree[] = {
    { 10, { .data = 0x00050408 }, { .data = 0x0000028A } },
    { 11, { .data = 0x00050408 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0004 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000A0004 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar4ComTree[] = {
    { 10, { .data = 0x000A080A }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000A080A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar5ComTree[] = {
    { 10, { .data = 0x000C0103 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0000028A } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar6ComTree[] = {
    { 10, { .data = 0x0001080C }, { .data = 0x0000028A } },
    { 11, { .data = 0x0001080C }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0002 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockStar7ComTree[] = {
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000E0102 }, { .data = 0x0000028A } },
    { 11, { .data = 0x0001080C }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0102 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x02878F1E } }
};

DecisionTreeNonLeafNode mb1_itemWarpBlockComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemWarpBlockStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemWarpBlockStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemWarpBlockStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemWarpBlockStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemWarpBlockStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemWarpBlockStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemWarpBlockStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemWarpBlockStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar0ComTree[] = {
    { 10, { .data = 0x0001090C }, { .data = 0x0000028A } },
    { 10, { .data = 0x00020000 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar1ComTree[] = {
    { 10, { .data = 0x000F0709 }, { .data = 0x0000028A } },
    { 10, { .data = 0x00030001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar2ComTree[] = {
    { 10, { .data = 0x00070106 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar3ComTree[] = {
    { 10, { .data = 0x00050408 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar4ComTree[] = {
    { 10, { .data = 0x000A080A }, { .data = 0x0000028A } },
    { 10, { .data = 0x000B0001 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar5ComTree[] = {
    { 10, { .data = 0x000C0103 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000D0000 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar6ComTree[] = {
    { 10, { .data = 0x0001080C }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampStar7ComTree[] = {
    { 10, { .data = 0x00010002 }, { .data = 0x0000028A } },
    { 10, { .data = 0x000E0102 }, { .data = 0x0000028A } },
    { 0, { .data = 0x00000000 }, { .data = 0x0BF6A83C } }
};

DecisionTreeNonLeafNode mb1_itemMajinLampComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemMajinLampStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemMajinLampStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemMajinLampStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemMajinLampStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemMajinLampStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemMajinLampStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemMajinLampStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemMajinLampStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar0ComTree[] = {
    { 11, { .data = 0x0001090B }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar1ComTree[] = {
    { 11, { .data = 0x000F0709 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar2ComTree[] = {
    { 11, { .data = 0x00070104 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar3ComTree[] = {
    { 11, { .data = 0x00050406 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar4ComTree[] = {
    { 11, { .data = 0x000A080A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar5ComTree[] = {
    { 11, { .data = 0x000C0102 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000A0A0A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar6ComTree[] = {
    { 11, { .data = 0x0001080A }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStar7ComTree[] = {
    { 11, { .data = 0x00010000 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0102 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemNKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemNKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemNKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemNKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemNKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemNKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemNKinokoStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemNKinokoStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoPosComTree[] = {
    { 10, { .data = 0x0001080A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00050A0A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemNKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb1_itemNKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .node_data = mb1_itemNKinokoPosComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar0ComTree[] = {
    { 10, { .data = 0x00020206 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000F0003 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030305 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar1ComTree[] = {
    { 10, { .data = 0x00020404 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00030305 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar2ComTree[] = {
    { 10, { .data = 0x00050407 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar3ComTree[] = {
    { 10, { .data = 0x00050A0A }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00060000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000A0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar4ComTree[] = {
    { 10, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar5ComTree[] = {
    { 10, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar6ComTree[] = {
    { 10, { .data = 0x000F0106 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00020006 }, { .data = 0x0B54233C } },
    { 10, { .data = 0x00040001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStar7ComTree[] = {
    { 10, { .data = 0x00010405 }, { .data = 0x0B54233C } },
    { 12, { .data = 0x0000000A }, { .data = 0x00028A1E } },
    { 10, { .data = 0x00010607 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoStarComTree[] = {
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemRKinokoStar7ComTree } },
    { 12, { .data = 0x00000005 }, { .data = 0x00000A1E } },
    { 10, { .data = 0x00010004 }, { .data = 0x0BF6A33C } },
    { 12, { .data = 0x00000014 }, { .data = 0x00028A1E } },
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemRKinokoStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemRKinokoStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemRKinokoStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemRKinokoStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemRKinokoStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemRKinokoStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemRKinokoStar6ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar0ComTree[] = {
    { 11, { .data = 0x0001090C }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar1ComTree[] = {
    { 11, { .data = 0x000F0709 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar2ComTree[] = {
    { 11, { .data = 0x00070106 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar3ComTree[] = {
    { 11, { .data = 0x00050408 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar4ComTree[] = {
    { 11, { .data = 0x000A080A }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar5ComTree[] = {
    { 11, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar6ComTree[] = {
    { 11, { .data = 0x0001080C }, { .data = 0x0C94233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStar7ComTree[] = {
    { 11, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 11, { .data = 0x000E0102 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeStarComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemStarYokeStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemStarYokeStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemStarYokeStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemStarYokeStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemStarYokeStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemStarYokeStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemStarYokeStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemStarYokeStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb1_itemRKinokoStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar0ComTree[] = {
    { 15, { .data = 0x0001090C }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00020000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar1ComTree[] = {
    { 15, { .data = 0x000F0709 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x00030001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar2ComTree[] = {
    { 15, { .data = 0x00070106 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar3ComTree[] = {
    { 15, { .data = 0x00050408 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar4ComTree[] = {
    { 15, { .data = 0x000A080A }, { .data = 0x0B54233C } },
    { 15, { .data = 0x000B0001 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar5ComTree[] = {
    { 15, { .data = 0x000C0103 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x000D0000 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar6ComTree[] = {
    { 15, { .data = 0x0001080C }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetStar7ComTree[] = {
    { 15, { .data = 0x00010002 }, { .data = 0x0B54233C } },
    { 15, { .data = 0x000E0102 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000A1E } }
};

DecisionTreeNonLeafNode mb1_itemRKinokoTargetComTree[] = {
    { 2, { .data = 0x00000001 }, { .node_data = mb1_itemRKinokoTargetStar0ComTree } },
    { 2, { .data = 0x00000002 }, { .node_data = mb1_itemRKinokoTargetStar1ComTree } },
    { 2, { .data = 0x00000004 }, { .node_data = mb1_itemRKinokoTargetStar2ComTree } },
    { 2, { .data = 0x00000008 }, { .node_data = mb1_itemRKinokoTargetStar3ComTree } },
    { 2, { .data = 0x00000010 }, { .node_data = mb1_itemRKinokoTargetStar4ComTree } },
    { 2, { .data = 0x00000020 }, { .node_data = mb1_itemRKinokoTargetStar5ComTree } },
    { 2, { .data = 0x00000040 }, { .node_data = mb1_itemRKinokoTargetStar6ComTree } },
    { 2, { .data = 0x00000080 }, { .node_data = mb1_itemRKinokoTargetStar7ComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_itemStarYokeComTree[] = {
    { 0, { .data = 0x00000000 }, { .node_data = mb1_itemStarYokeStarComTree } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_comShopKeyComTree0[] = {
    { 8, { .data = 0x00000001 }, { .data = 0x00000514 } },
    { 2, { .data = 0x00000004 }, { .data = 0x0B54233C } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_comShopKeyComTree1[] = {
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_comShopItemComTree0[] = {
    { 2, { .data = 0x000000B0 }, { .data = 0x08CF1932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_comShopItemComTree1[] = {
    { 2, { .data = 0x00000041 }, { .data = 0x08CF1932 } },
    { 0, { .data = 0x00000000 }, { .data = 0x00000000 } }
};

DecisionTreeNonLeafNode mb1_comShopEnterComTree0Star1[] = {
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } }
};

DecisionTreeNonLeafNode mb1_comShopEnterComTree0[] = {
    { 2, { .data = 0x00000002 }, { .node_data = mb1_comShopEnterComTree0Star1 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

DecisionTreeNonLeafNode mb1_comShopEnterComTree1Star45[] = {
    { 1, { .data = 0x0000001E }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0000051E } }
};

DecisionTreeNonLeafNode mb1_comShopEnterComTree1[] = {
    { 2, { .data = 0x00000030 }, { .node_data = mb1_comShopEnterComTree1Star45 } },
    { 1, { .data = 0x00000019 }, { .data = 0x0C96A846 } },
    { 0, { .data = 0x00000000 }, { .data = 0x0B54233C } }
};

s32 mb1_comShopCancelF = 0;

u8 mb1_comShopItemOrderMario[] = {
    14, 10, 0, 3, 2, 4, 19, 11,
    5, 6, 12, 13, 9, 7, 8, 1
};

u8 mb1_comShopItemOrderLuigi[] = {
    14, 1, 11, 10, 19, 12, 0, 6,
    9, 3, 13, 4, 8, 7, 2, 5
};

u8 mb1_comShopItemOrderPeach[] = {
    14, 11, 6, 9, 12, 7, 3, 13,
    2, 4, 10, 19, 0, 8, 5, 1
};

u8 mb1_comShopItemOrderYoshi[] = {
    14, 5, 9, 10, 11, 7, 19, 12,
    0, 6, 3, 13, 4, 8, 2, 1
};

u8 mb1_comShopItemOrderWario[] = {
    14, 8, 13, 11, 10, 19, 6, 7,
    12, 0, 9, 3, 4, 2, 5, 1
};

u8 mb1_comShopItemOrderDk[] = {
    14, 3, 11, 10, 19, 12, 0, 6,
    9, 13, 4, 8, 7, 2, 5, 1
};

u8 mb1_comShopItemOrderWaluigi[] = {
    14, 2, 9, 3, 6, 7, 8, 5,
    4, 19, 11, 13, 10, 12, 0, 1
};

u8 mb1_comShopItemOrderDaisy[] = {
    14, 4, 19, 9, 11, 10, 3, 12,
    7, 0, 1, 6, 13, 8, 2, 5
};

u8 *mb1_comShopItemOrderTbl[] = { mb1_comShopItemOrderMario, mb1_comShopItemOrderLuigi, mb1_comShopItemOrderPeach, mb1_comShopItemOrderYoshi, mb1_comShopItemOrderWario, mb1_comShopItemOrderDk, mb1_comShopItemOrderWaluigi, mb1_comShopItemOrderDaisy };

s8 mb1_comShopItemRateMario[] = {
    90, 70, 60, 30, 20, 20, 20, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb1_comShopItemRateLuigi[] = {
    80, 50, 20, 20, 20, 10, 20, 10,
    10, 10, 20, 10, 10, 10, 10, 0
};

s8 mb1_comShopItemRatePeach[] = {
    80, 30, 50, 30, 30, 20, 20, 20,
    20, 20, 30, 20, 30, 10, 10, 10
};

s8 mb1_comShopItemRateYoshi[] = {
    90, 50, 20, 30, 20, 10, 20, 10,
    30, 10, 10, 10, 10, 10, 10, 10
};

s8 mb1_comShopItemRateWario[] = {
    90, 50, 30, 30, 30, 20, 20, 20,
    10, 30, 10, 10, 10, 10, 10, 10
};

s8 mb1_comShopItemRateDk[] = {
    90, 50, 30, 60, 20, 20, 30, 20,
    10, 10, 10, 10, 10, 10, 10, 10
};

s8 mb1_comShopItemRateWaluigi[] = {
    70, 40, 40, 40, 30, 20, 30, 30,
    20, 40, 40, 30, 40, 10, 40, 10
};

s8 mb1_comShopItemRateDaisy[] = {
    80, 50, 60, 20, 20, 30, 20, 30,
    10, 30, 20, 10, 10, 10, 10, 10
};

s8 *mb1_comShopItemRateTbl[] = { mb1_comShopItemRateMario, mb1_comShopItemRateLuigi, mb1_comShopItemRatePeach, mb1_comShopItemRateYoshi, mb1_comShopItemRateWario, mb1_comShopItemRateDk, mb1_comShopItemRateWaluigi, mb1_comShopItemRateDaisy };

DecisionTreeNonLeafNode *mb1_comShopKeyComTree[] = { mb1_comShopKeyComTree0, mb1_comShopKeyComTree1 };

DecisionTreeNonLeafNode *mb1_comShopItemComTree[] = { mb1_comShopItemComTree0, mb1_comShopItemComTree1 };

DecisionTreeNonLeafNode *mb1_comShopEnterComTree[] = { mb1_comShopEnterComTree0, mb1_comShopEnterComTree1 };

// Get toad space index for current start space index.
s16 MB1Ev_StarGuideMasuGet(void) {
    return mb1ev_starGuideMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void MB1Ev_StarShuffle(void) {
    s32 temp;
    s32 a;
    s32 b;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    for (i = 0; i < 60; i++) {
        a = rand8() % STAR_POSITIONS_TOTAL;
        b = rand8() % STAR_POSITIONS_TOTAL;
        if (a != b) {
            if (a >= mb1ev_starOrderGroupTbl[b]) {
                if (b >= mb1ev_starOrderGroupTbl[a]) {
                    temp = mb1ev_starOrderTbl[a];
                    mb1ev_starOrderTbl[a] = mb1ev_starOrderTbl[b];
                    mb1ev_starOrderTbl[b] = temp;

                    temp = mb1ev_starOrderGroupTbl[a];
                    mb1ev_starOrderGroupTbl[a] = mb1ev_starOrderGroupTbl[b];
                    mb1ev_starOrderGroupTbl[b] = temp;
                }
            }
        }
    }

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        system->star_spawn_indices[i] = mb1ev_starOrderTbl[i];
    }
}

void MB1Ev_StarNextPos(void) {
    s32 temp_s0;
    s32 temp_v1;
    GW_SYSTEM* system = &GwSystem;

    if (++system->current_star_spawn >= STAR_POSITIONS_TOTAL) {
        temp_s0 = system->star_spawn_indices[STAR_POSITIONS_TOTAL-1];
        system->current_star_spawn = 0;
        GWBoardFlagSet(4);
        MB1Ev_StarShuffle();
        if (temp_s0 == system->star_spawn_indices[0]) {
            temp_s0 = system->star_spawn_indices[0];
            system->star_spawn_indices[0] = system->star_spawn_indices[STAR_POSITIONS_TOTAL-1];
            system->star_spawn_indices[STAR_POSITIONS_TOTAL-1] = temp_s0;
        }
    }
}

void MB1Ev_StarMasuInit(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        GWBoardFlagSet(mb1ev_starFlag[i]);
    }

    MBMasuTypeSet(mb1ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], 0xE);
    GWBoardFlagClear(mb1ev_starFlag[system->star_spawn_indices[system->current_star_spawn]]);
}

s16 MB1Ev_StarCheck(s16 arg0) {
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == mb1ev_starMasu[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = mb1ev_starFlag[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

void MB1Ev_StarGuideIn(void) {
    UnkStar *unkStar;
    Object *star;
    s32 light;
    f32 scale;
    f32 angle;
    s32 i;

    unkStar = HuPrcCurrentGet()->user_data;

    HuAudFXPlay(0x11B);
    star = mb1ev_starGuideInMdl = MBModelCreate(0x3A, NULL);
    AuraCreate(star->omObj1->model[0]);
    star->flags |= 4;
    MBModelBillboardSet(star);
    HuVecCopy3F(&star->coords, &unkStar->pos);
    star->velocity.x = 50.0f;

    light = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(light, 2.0f, 20.0f, 1.0f);
    EffectRangeSet(light, 30.0f);
    EffectPosSet(light, star->coords.x, star->coords.y + star->velocity.x, star->coords.z);
    Hu3DModelCameraSet(light, HU3D_CAM0);

    scale = 0.0f;

    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&star->scale, scale, scale, scale);
        scale += 0.5f;
        EffectRangeSet(light, scale * 30.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&star->scale, scale, scale, scale);
        scale -= 0.4f;
        EffectRangeSet(light, scale * 30.0f);
        HuPrcVSleep();
    }

    EffectRangeSet(light, scale * 30.0f);

    HuPrcSleep(30);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    while (1) {
        HuMtxRotYF(Hu3DData[star->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (scale > 0.6f) {
            scale -= 0.04f;
        }
        HuVecCopyXYZ(&star->scale, scale, scale, scale);

        if (star->velocity.x > 10.0f) {
            star->velocity.x -= 1.2f;
        }

        EffectRangeSet(light, scale * 30.0f);
        EffectPosSet(light, star->coords.x, star->coords.y + star->velocity.x, star->coords.z);

        if ((star->velocity.x <= 10.0f) && (scale <= 0.6f) && (angle == 0.0f)) {
            break;
        }
        HuPrcVSleep();
    }

    HuMtxRotYF(Hu3DData[star->omObj1->model[0]].mtx, 0.0f);
    EffectStop(light);
    mb1ev_starGuideInProc = 0;
    omDelPrcObj(NULL);
}

void MB1Ev_StarGuideJumpExec(UnkMBGuideData* arg0) {
    Object* obj;

    obj = arg0->obj;
    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    
    HuPrcSleep(3);
    while (obj->velocity.z != 0.0f) {
        HuPrcVSleep();
    }
}

void MB1Ev_StarMapView(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *space;
    s32 face;
    s32 mesNum;
    GW_SYSTEM* system = &GwSystem;

    mbTurnUnkF = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, mb1ev_starGuideFaceTbl[0]);
    MBPlayerIconMdlSet();
    MBModelDispOff(GET_STAR_MODEL());
    WipeCreateIn(WIPE_STARS, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBBackThreadPriLowSet();
    MBCameraSpeedDivSet(3.0f);
    MB1Ev_StarGuideJumpExec(guide);

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

    if ((system->current_board_index != SPINY_DESERT) || (rand8() % 2)) {
        space = MBMasuGet(mb1ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
    }

    //@bug: this can be unintialized (except not because SPINY_DESERT has different code for this)
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    face = MBRand(7.0f);
    MBGuideFaceSet(guide->obj, mb1ev_starGuideFaceTbl[face]);
    MBMotionSet(guide->obj, -1, 2);

    if (system->current_board_index != 2) {
        proc = omAddPrcObj(MB1Ev_StarGuideIn, 0x4800, 0, 0);
        mb1ev_starGuideInProc = proc;
        proc->user_data = space;
        HuPrcSleep(30);
    } else {
        mb1ev_starGuideInProc = NULL;
    }

    HuWinMesSet(guide->amount, mb1ev_starGuideMesTbl[face], -1, -1);
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
    AuraKill(mb1ev_starGuideInMdl->omObj1->model[0]);
    MBModelKill(mb1ev_starGuideInMdl);
    MBModelDispOn(GET_STAR_MODEL());
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void MB1Ev_StarGet(void) {
    Vec sp10;
    GW_PLAYER *player;
    Object *star;
    Object *playerObj;
    Vec *coords;
    UnkStarWork *work;
    s32 light;
    f32 scale;
    f32 angle;
    s32 i;

    work = HuPrcCurrentGet()->user_data;
    player = MBPlayerGet(CUR_PLAYER);

    HuAudFXPlay(0x11B);
    star = MBModelCreate(0x1A, NULL);
    star->flags |= 4;
    MBModelBillboardSet(star);

    if (MBMasuLinkMasuIdGet(MBPlayerGet(CUR_PLAYER)->clink, MBPlayerGet(CUR_PLAYER)->cidx) == 0x92) {
        HuVecCopyXYZ(&star->coords, work->unk_0C.x, work->unk_0C.y + 10.0f, work->unk_0C.z);
        HuVecCopyXYZ(&sp10, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        star->velocity.x = 15.0f;
    } else {
        HuVecCopyXYZ(&star->coords, work->unk_0C.x, work->unk_0C.y + 10.0f, work->unk_0C.z + 30.0f);
        HuVecCopyXYZ(&sp10, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        star->velocity.x = 35.0f;
    }

    light = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(light, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(light, 15.0f);
    Hu3DModelCameraSet(light, HU3D_CAM0);
    EffectPosSet(light, star->coords.x, star->coords.y + star->velocity.x, star->coords.z);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&star->scale, scale, scale, scale);
        scale += 0.5f;
        EffectRangeSet(light, scale * 15.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&star->scale, scale, scale, scale);
        scale -= 0.4f;
        EffectRangeSet(light, scale * 15.0f);
        HuPrcVSleep();
    }
    EffectRangeSet(light, scale * 15.0f);

    HuPrcSleep(20);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    playerObj = player->player_obj;
    HuVecCopyXYZ(&sp10, playerObj->coords.x, playerObj->coords.y - 10.0f, playerObj->coords.z);
    coords = &star->coords;
    MBPlayerPosMoveCreate(coords, &sp10, coords, 40);

    for (i = 0; i < 40; i++) {
        HuMtxRotYF(Hu3DData[star->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        scale -= 0.05f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuVecCopyXYZ(&star->scale, scale, scale, scale);
        EffectRangeSet(light, scale * 15.0f);
        EffectPosSet(light, star->coords.x, star->coords.y + star->velocity.x, star->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(star);
    EffectStop(light);
    MBVecForwardSet(&player->player_obj->rot);
    MBPlayerVibrate(-1, 5);

    if (mb1ev_starGetTeresaF != 0) {
        HuAudSeqVolFadeOut(0xE);
    } else {
        HuAudSeqPlay(0x6F);
    }

    GwPlayer[GwSystem.current_player_index].star++;
    if (GwPlayer[GwSystem.current_player_index].star > STARS_MAX) {
        GwPlayer[GwSystem.current_player_index].star = STARS_MAX;
    }

    MBPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x262, GwSystem.current_player_index);

    if (mb1ev_starGetTeresaF != 0) {
        HuPrcSleep(0x10);
        msmMusPause(HuAudMusNo);
        HuAudSubSeqPlayMute(0x6F);
        HuAudSubSeqVolFadeIn(0);
        HuPrcSleep(0x6E);
        msmMusResume(HuAudMusNo, 0);
        HuAudSeqVolFadeIn(0xF);
    } else {
        HuPrcSleep(60);
    }
    omDelPrcObj(NULL);
}

void MB1Ev_StarGetExec(Object* arg0) {
    Process* temp_v0;

    mbItemBtnF = 0;
    temp_v0 = omAddPrcObj(MB1Ev_StarGet, 0x4800U, 0, 0);
    temp_v0->user_data = (void*)arg0;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

// View board map
void MB1_MapScroll(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

// Exit the board map?
void MB1_MapScrollCancel(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

// setup arrows used during player direction decisions.
void MB1_BranchHelpStart(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    mb1_branchStickHelp = MBHelpWinCreate(0, 0x92, 1);
    mb1_branchBtnHelp = MBHelpWinCreate(1, 0xA0, 1);
    mb1_branchItemHelp = MBHelpWinCreate(0xD, 0xAE, 1);
    mb1_branchMapScrollHelp = MBHelpWinCreate(3, 0xBC, 1);
    mb1_branchMapOverheadHelp = MBHelpWinCreate(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    duelCancelEnableF = 1;
}

// teardown arrows
void MB1_BranchHelpEnd(void) {
    mbCameraBtnF = 0;
    duelCancelEnableF = 0;
    MBHelpWinKill(mb1_branchStickHelp);
    MBHelpWinKill(mb1_branchBtnHelp);
    MBHelpWinKill(mb1_branchItemHelp);
    MBHelpWinKill(mb1_branchMapScrollHelp);
    MBHelpWinKill(mb1_branchMapOverheadHelp);
}

s32 MB1_ComShopItemChoice(u8 *arg0) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                count = MB1_ComShopItemDecide();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (count != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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

    for (i = 0;;) {
        i = HuWinChoiceGet(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
        if (arg0[i] != 0) {
            return i;
        }        
    }
}

s32 MB1_ComShopEnterChoice(void) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                count = MB1_ComShopEnterDecide();
                sp18[GwPlayer[i].pad] = D_JPAD;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = HUWIN_COMKEY_PAD;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (count != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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


extern s32 mb1_comTeresaType;

void MB1_ComTeresaTypeDecide(void) {
    s32 current;
    s32 i;
    s32 j;

    current = GwSystem.current_player_index;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if ((i != current) && (GwPlayer[i].star != 0)) {
            break;
        }
    }

    if (i != MB_MAX_PLAYERS) {
        if (GwPlayer[current].coin >= 50) {
            if (MBRand(100.0f) < (GwPlayer[current].coin + 10)) {
                mb1_comTeresaType = 1;
                if (GwPlayer[current].star < STARS_MAX) {
                    return;
                }
            }
        }
    }

    for (j = 0; j < MB_MAX_PLAYERS; j++) {
        if ((j != current) && (GwPlayer[j].coin >= 5)) {
            break;
        }
    }

    if (j != MB_MAX_PLAYERS) {
        mb1_comTeresaType = 0;
        return;
    }
    mb1_comTeresaType = 2;
}

void MB1_ComTeresaTargetDecide(void) {
    s32 sp10[MB_MAX_PLAYERS];
    s32 current;
    s32 target;
    s32 rank;
    s32 i;

    current = GwSystem.current_player_index;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        sp10[i] = -1;
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        rank = MBPlayerStealRankGet(i);
        while (1) {
            if (sp10[rank] == -1) {
                break;
            }
            rank++;
        }
        sp10[rank] = i;
    }

    MB1_ComTeresaTypeDecide();

    if (mb1_comTeresaType == 1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            target = sp10[i];
            if ((target != current) && (GwPlayer[target].star != 0)) {
                mb1_comTeresaTarget = target;
                break;
            }
        }
    } else if (mb1_comTeresaType == 0) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            target = sp10[i];
            if ((target != current) && (GwPlayer[target].coin >= 5)) {
                mb1_comTeresaTarget = target;
                break;
            }
        }
    }

    if (i == MB_MAX_PLAYERS) {
        mb1_comTeresaType = 2;
    }
}

s32 MB1_ComTeresaChoice(u8 *arg0, s32 arg1, s32 arg2) {
    s32 pct;
    s32 ret;
    s16 sel;
    s32 i;
    s32 j;
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                if (arg1 == 0) {
                    MB1_ComTeresaTargetDecide();
                    count = mb1_comTeresaType + 1;
                } else {
                    count = mb1_comTeresaTarget + 1;
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

    if (count != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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

    for (i = 0;;) {
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

s32 MB1_ComTeresaTypeChoice(u8* arg0) {
    return MB1_ComTeresaChoice(arg0, 0, 1);
}

s32 MB1_ComTeresaPlayerChoice(u8* arg0) {
    return MB1_ComTeresaChoice(arg0, 1, 0);
}

// entrypoint 0
void MB1_BoardInit(void) {
    GwSystem.current_board_index = 0;
    omInitObjMan(10, 0);
    omOvlGotoEx(boardcall, 0, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
}

// entrypoint 1
void MB1_SaveInit(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    MB1Ev_StarShuffle();
    GWBoardFlagClear(0x12);
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.boardData.halfWordBytes[1] = 0;
    omOvlReturnEx(1);
}

void MB1_ObjectSetup(void) {
    Vec sp10;
    SpaceData *space;
    s32 i;

    omInitObjMan(0xA0, 0x28);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(3, 0x23A, 5, 0);
    MBMasuBlockTblExtSet(&mb1_masuBlockExtTbl);
    MBMasuBlockTblSet(mb1_masuBlockTbl);
    space = MBMasuGet(0x77);
    MBVecDirGet(&space->coords, &MBMasuGet(0x73)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x7C);
    MBVecDirGet(&space->coords, &MBMasuGet(0x6E)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    space = MBMasuGet(0x8F);
    MBVecDirGet(&space->coords, &MBMasuGet(0x80)->coords, &sp10);
    MBMasuArrowAngleAdd(MBVecAngleGet(&sp10) + 180.0f);
    MBItemHookSet(0, &MB1Ev_Teresa); // boo event
    MBItemHookSet(1, &MB1Ev_ItemMajinLamp); // magic lamp
    MBItemHookSet(9, &MB1Ev_ItemMajinLampStar);
    MBItemHookSet(2, &MB1Ev_ItemWarpBlock); // warp block
    MBItemHookSet(3, &MB1Ev_ItemRobBox); // plunder chest
    MBItemHookSet(4, &MB1Ev_KSuitStart); // activate bowser suit
    MBItemHookSet(5, &MB1Ev_KSuitEnd); // when landing on a space as bowser suit
    MBItemHookSet(6, &MB1Ev_ItemKinoko); // mushroom/golden mushroom/bowser suit
    MBItemHookSet(7, &MB1Ev_ItemShake); // dueling glove/boo bell (?)
    MBItemHookSet(8, &MB1Ev_ItemPhoneMove);
    MBItemHookSet(0xA, &MB1Ev_ItemNKinoko); // poison mushroom
    MBItemHookSet(0xB, &MB1Ev_ItemRKinoko); // reverse mushroom
    MBItemHookSet(0xE, &MB1Ev_ItemShopPhone);
    MBItemHookSet(0xF, &MB1Ev_ItemKoopaPhone);  // bowser phone
    MBItemHookSet(0x10, &MB1Ev_ItemStarYoke); // lucky lamp
    MBItemHookSet(0x11, &MB1Ev_ItemKeyManUse); // skeleton key throw away event
    MBItemHookSet(0x12, &MB1Ev_ItemNullUse); // boo repellant/koopa kard thrown away
    MBItemHookSet(0x13, &MB1Ev_ItemExchangeBox); // barter box
    MBItemHookSet(0x14, &MB1Ev_ItemGambleCoin); // game guy coin
    MBItemHookSet(0x15, &MB1Ev_ItemAfter5);                 // wacky watch
    MBItemHookSet(0xC, &MB1Ev_ItemKoopaNKinoko);
    MBItemHookSet(0xD, &MB1Ev_ItemKoopaRKinoko);
    MBComItemDecideHookSet(&MB1_ComItemDecide);

    for (i = 0; i < ARRAY_COUNT(mb1ev_starGuideMasu); i++) {
        MBMasuStarSet(i, mb1ev_starGuideMasu[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        MB1Ev_StarNextPos();
    }

    MB1Ev_StarMasuInit();
    MB1_StarGuideCreateAll();
    MB1_TeresaGuideCreateAll();
    MB1_BankCoinCreateAll();
    MB1_GateCreateAll();
    MB1_BankMapIconAddAll();
    MB1_ShopMapIconAddAll();
    MB1Ev_KinokoMarkCreateAll();
    MBMasuTypeListCreate();
    omAddPrcObj(MB1Ev_SnowmanObjMain, 0x4800, 0, 0);
}

// entrypoint 2
void MB1_Create(void) {
    HuAudSeqPlay(0x18);
    mbBoardMusId = 0x18;
    MBBoardParamSet(0x18);
    Hu3DCamInit(2);
    MB1_ObjectSetup();
    MBMasuEventTblAdd(mb1_commonEventTbl);
    MBMasuEventTblAdd(mb1_specialEventTbl);
    MBHatenaFuncSet(&MB1Ev_SnowmanStart);
    MBMasuEventTblAdd(mb1_teresaEventTbl);
    MBMasuEventTblAdd(mb1_turnStatusEventTbl);
    MBStart(0);
}

// entrypoint 3
void MB1_BoardReload(void) {
    Hu3DCamInit(1);
    MB1_ObjectSetup();
    MBStart(1);
}

void MB1_StarGuideCreate(s16 arg0) {
    Object* temp_v0;
    s32 temp_s1;

    if (mb1_starGuideMdl[arg0] == 0) {
        
        temp_v0 = MBModelCreate(0x3A, NULL);
        AuraCreate(temp_v0->omObj1->model[0]);
        if (mb1_starGuideBaseMdl == NULL) {
            mb1_starGuideBaseMdl = temp_v0;
        }
        
        mb1_starGuideMdl[arg0] = temp_v0;
        temp_v0->flags |= 2;
        HuVecCopyXYZ(&temp_v0->scale, 0.6f, 0.6f, 0.6f);
        temp_v0->velocity.x = 10.0f;
        mb1_starGuideHoverProc[arg0] = MBModelHoverCreate(temp_v0, 6.0f, 2.0f);
        HuVecCopy3F(&temp_v0->coords, &MBMasuGet(mb1_starGuideMdlMasuTbl[arg0])->coords);
        MBMapFullIconMdlAdd(0xB, temp_v0, mb1_starGuideMapIconOfsTbl[arg0][0], mb1_starGuideMapIconOfsTbl[arg0][1]);
    }
}

void MB1_StarGuideKill(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(mb1_starGuideHoverProc); i++) {
        if (mb1_starGuideHoverProc[i] != NULL) {
            omDelPrcObj(mb1_starGuideHoverProc[i]);
            mb1_starGuideHoverProc[i] = NULL;
        }
    }
}

void MB1_StarGuideCreateAll(void) {
    s32 i;

    mb1_starGuideBaseMdl = NULL;

    for (i = 0; i < ARRAY_COUNT(mb1_starGuideFlagTbl); i++) {
        mb1_starGuideMdl[i] = 0;
        mb1_starGuideHoverProc[i] = 0;
        MBKinokoEffKillHookSet(&MB1_StarGuideKill);
        if (GWBoardFlagCheck(mb1_starGuideFlagTbl[i]) == 0) {
            MB1_StarGuideCreate(i);
        }
    }
}

void MB1_TeresaGuideCreate(s16 arg0) {
    Object *teresa;

    if (mb1_teresaGuideMdl[arg0] == NULL) {
        if (mb1_teresaGuideBaseMdl == NULL) {
            teresa = MBModelCreate(0xA, NULL);
            Hu3DModelTPLvlInit(teresa->omObj1->model[0]);
            Hu3DModelTPLvlInit(teresa->omObj2->model[0]);
            mb1_teresaGuideBaseMdl = teresa;
        } else {
            teresa = MBModelLinkCreate(mb1_teresaGuideBaseMdl);
        }
        MBModelDispOff(teresa);
        mb1_teresaGuideMdl[arg0] = teresa;
        teresa->flags |= 2;
        teresa->velocity.x = 15.0f;
        HuVecCopy3F(&teresa->coords, &MBMasuGet(mb1_teresaGuideMasuTbl[arg0])->coords);
        MBMapFullIconMdlAdd(0xA, teresa,
                                         mb1_teresaGuideMapIconOfsTbl[arg0][0],
                                         mb1_teresaGuideMapIconOfsTbl[arg0][1]);
    }
}

void MB1_TeresaGuideCreateAll(void) {
    s32 i;

    mb1_teresaGuideBaseMdl = 0;
    for (i = 0; i < 1; i++) {
        mb1_teresaGuideMdl[i] = 0;
        MB1_TeresaGuideCreate(i);
    }
}

void MB1_BankCoinHide(void) {
    s32 count;
    s32 i;
    s32 bank;

    for (bank = 0; bank < 2; bank++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (i = 0; i < count; i++) {
            MBModelDispOn(mb1_bankCoinMdl[(bank * 5) + i]);
        }
        for (; i < 5; i++) {
            MBModelDispOff(mb1_bankCoinMdl[(bank * 5) + i]);
        }
    }
}

void MB1_BankCoinCreate(s16 arg0) {
    Object *coin;
    Vec *pos;
    s32 bank;
    s16 slot;

    if (mb1_bankCoinMdl[arg0] == NULL) {
        if (mb1_bankCoinBaseMdl == NULL) {
            coin = MBModelCreate(0x1E, NULL);
            MBModelTempAllocFree(coin);
            mb1_bankCoinBaseMdl = coin;
        } else {
            coin = MBModelLinkCreate(mb1_bankCoinBaseMdl);
        }
        mb1_bankCoinMdl[arg0] = coin;
        coin->flags |= 2;

        bank = arg0 / 5;
        pos = &coin->coords;
        HuVecCopy3F(pos, &MBMasuGet(mb1_bankCoinMasuTbl[bank])->coords);

        slot = arg0 % ARRAY_COUNT(mb1_bankCoinOfsTbl);
        HuVecAdd(pos, &mb1_bankCoinOfsTbl[slot], pos);
        coin->omObj1->rot.x = mb1_bankCoinRotTbl[slot].x;
        coin->omObj1->rot.z = mb1_bankCoinRotTbl[slot].z;
        MBModelDispOff(coin);
    }
}

void MB1_BankCoinCreateAll(void) {
    s32 i;

    mb1_bankCoinBaseMdl = NULL;
    for (i = 0; i < ARRAY_COUNT(mb1_bankCoinMdl); i++) {
        mb1_bankCoinMdl[i] = 0;
        MB1_BankCoinCreate(i);
    }
    MB1_BankCoinHide();
}

void MB1_GateCreate(s16 arg0) {
    Object *obj;
    SpaceData *space;
    char pad[4];

    if (mb1_gateMdl[arg0] == NULL) {
        if (mb1_gateBaseMdl == NULL) {
            obj = MBModelCreate(mb1_gateMdlTbl[GwSystem.current_board_index][1],
                                mb1_gateMotTbl[GwSystem.current_board_index]);
            MBModelTempAllocFree(obj);
            mb1_gateBaseMdl = obj;
        } else {
            obj = MBModelLinkCreate(mb1_gateBaseMdl);
        }
        mb1_gateMdl[arg0] = obj;
        obj->flags |= 2;
        Hu3DMotionAttrSet(obj->omObj1->model[0], 2, 1);
        HuVecCopy3F(&obj->coords, &MBMasuGet(mb1_gateMasuTbl[arg0])->coords);

        space = MBMasuGet(mb1_gateDirMasuTbl[arg0][0]);
        MBVecDirGet(&MBMasuGet(mb1_gateDirMasuTbl[arg0][1])->coords,
                    &space->coords, &obj->rot);
        MBMapFullIconMdlAdd(0xC, obj,
                                         mb1_gateMapIconOfsTbl[arg0][0],
                                         mb1_gateMapIconOfsTbl[arg0][1]);
    }
}

void MB1_GateCreateAll(void) {
    s32 i;

    mb1_gateBaseMdl = NULL;
    for (i = 0; i < 2; i++) {
        mb1_gateMdl[i] = 0;
        MB1_GateCreate(i);
    }
}

void MB1_GateOpenSeProc(void) {
    HuPrcSleep(mb1_gateOpenDelayTbl[GwSystem.current_board_index]);
    HuAudFXPlay(mb1_gateOpenDelaySeTbl[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void MB1_GateOpen(s32 arg0, s32 arg1) {
    MBMotionSet(mb1_gateMdl[arg0], (arg1 - 1), 0);
    Hu3DMotionAttrSet(mb1_gateMdl[arg0]->omObj1->model[0], 5, 0);
    
    if (mb1_gateOpenSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb1_gateOpenSeTbl[GwSystem.current_board_index]);
    }
    
    if (mb1_gateOpenDelaySeTbl[GwSystem.current_board_index] != -1) {
        omAddPrcObj(MB1_GateOpenSeProc, 0x1000U, 0, 0);
    }
}

void MB1_GateCloseProc(void) {
    GW_SYSTEM* system = &GwSystem;
    s32 temp_s0 = (s32)HuPrcCurrentGet()->user_data;
    s32 sleepTime;

    switch (system->walk_speed) {
    case 0:
        HuPrcSleep(5);
        break;
    case 1:
        HuPrcSleep(10);
        break;
    default:
        HuPrcSleep(15);
        break;
    }
    
    Hu3DMotionAttrSet(mb1_gateMdl[temp_s0]->omObj1->model[0], 1, 4);
    
    if (mb1_gateCloseSeTbl[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(mb1_gateCloseSeTbl[GwSystem.current_board_index]);
    }
    
    omDelPrcObj(NULL);
}

void MB1_GateClose(s32 arg0) {
    omAddPrcObj(MB1_GateCloseProc, 0x1000, 0, 0)->user_data = (void*)arg0;
}

void MB1_BankMapIconAddAll(void) {
    s32 i;

    mb1_gateBaseMdl = NULL;
    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(8, &MBMasuGet(mb1_bankMapIconMasuTbl[i])->coords, mb1_bankMapIconOfsTbl[i][0], mb1_bankMapIconOfsTbl[i][1]);
    }
}

void MB1_ShopMapIconAddAll(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        MBMapFullIconPosAdd(9, &MBMasuGet(mb1_shopMapIconMasuTbl[i])->coords, mb1_shopMapIconOfsTbl[i][0], mb1_shopMapIconOfsTbl[i][1]);
    }
}

void MB1Ev_BranchMerge(s32 masuAbsIndex, s16 arg1, s16 arg2) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == masuAbsIndex) {
        MBMoveNextMasuSet(-1, arg1, arg2);
    }
}

void MB1Ev_Branch1(void) {
    MBMoveNextMasuSet(-1, 1, 6);
}

void MB1Ev_Branch1Rev(void) {
    GW_PLAYER* temp_v0 = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(temp_v0->blink, temp_v0->bidx) == 0x6B) {
        MBMoveBackMasuSet(-1, 1, 6);
    }
}


void MB1Ev_Branch2(void) {
    MB1Ev_BranchMain(mb1ev_branch2Masu, mb1ev_branch2Link, mb1ev_branch2ComTree);
    omDelPrcObj(0);
}

void MB1Ev_Branch2Rev(void) {
    MB1Ev_BranchMain(mb1ev_branch2RevMasu, mb1ev_branch2RevLink, mb1ev_branch2RevComTree);
    omDelPrcObj(NULL);
}

void MB1Ev_Branch3(void) {
    MB1Ev_BranchMain(mb1ev_branch3Masu, mb1ev_branch3Link, mb1ev_branch3ComTree);
    omDelPrcObj(NULL);
}

void MB1Ev_Branch3Rev(void) {
    GW_PLAYER *player;

    player = MBPlayerGet(CUR_PLAYER);
    if ((MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4B) && !(player->rev & FLAG_UNK_80)) {
        MBMoveNextMasuSet(-1, 0xA, 0);
        player->rev &= ~FLAG_REV;
    } else {
        MB1Ev_BranchMain(mb1ev_branch3RevMasu, mb1ev_branch3RevLink, mb1ev_branch3RevComTree);
    }
    omDelPrcObj(0);
}

void MB1Ev_Branch4(void) {
    GW_PLAYER *player;
    DecisionTreeNonLeafNode *tree;
    UnkEA790Struct* win;
    s32 sel;
    s32 sel2;
    s32 i;

    player = MBPlayerGet(CUR_PLAYER);
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    MB1_BranchHelpStart();

    if (!(player->rev & FLAG_UNK_80)) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3D) {
            player->rev &= ~1;
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4From61Masu);
        } else {
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4Masu);
        }
    } else {
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
        case 0x3C:
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4RKinokoFrom60Masu);
            break;
        case 0x57:
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4RKinokoFrom87Masu);
            break;
        case 0x46:
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4RKinokoFrom70Masu);
            break;
        case 0x3D:
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4RKinokoFrom61Masu);
            break;
        default:
            win = MBBranchArrowLinkCreate(GwSystem.current_player_index, mb1ev_branch4RKinokoMasu);
            break;
        }
    }

    MBBranchSelStart(win, GwSystem.current_player_index, 0);

    if (MBPlayerComCheck(-1) != 0) {
        sel = MBComTreeExec(&mb1ev_branch4ComTree);
        for (i = 0; i < sel; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }

    sel2 = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB1_BranchHelpEnd();

    if (!(player->rev & FLAG_UNK_80)) {
        if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3D) {
            if (sel2 == 0) {
                MBMoveNextMasuSet(-1, 7, 0);
            } else {
                MBMoveNextMasuSet(-1, 8, 0);
            }
        } else {
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 7, 0);
                break;
            case 1:
                MBMoveNextMasuSet(-1, 8, 0);
                break;
            default:
                MBMoveNextMasuSet(-1, 9, 0);
                break;
            }
        }
    } else {
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
        case 0x3C:
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 7, 0);
                break;
            case 1:
                MBMoveNextMasuSet(-1, 8, 0);
                break;
            case 2:
                MBMoveNextMasuSet(-1, 9, 0);
                break;
            default:
                MBMoveNextMasuSet(-1, 0xB, 7);
                player->rev |= 1;
                break;
            }
            break;
        case 0x57:
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 2, 6);
                break;
            case 1:
                MBMoveNextMasuSet(-1, 8, 0);
                player->rev &= ~1;
                break;
            case 2:
                MBMoveNextMasuSet(-1, 9, 0);
                player->rev &= ~1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xB, 7);
                break;
            }
            break;
        case 0x46:
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 2, 6);
                break;
            case 1:
                MBMoveNextMasuSet(-1, 7, 0);
                player->rev &= ~1;
                break;
            case 2:
                MBMoveNextMasuSet(-1, 9, 0);
                player->rev &= ~1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xB, 7);
                break;
            }
            break;
        case 0x3D:
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 2, 6);
                break;
            case 1:
                MBMoveNextMasuSet(-1, 7, 0);
                player->rev &= ~1;
                break;
            case 2:
                MBMoveNextMasuSet(-1, 8, 0);
                player->rev &= ~1;
                break;
            default:
                MBMoveNextMasuSet(-1, 0xB, 7);
                break;
            }
            break;
        default:
            switch (sel2) {
            case 0:
                MBMoveNextMasuSet(-1, 2, 6);
                player->rev |= 1;
                break;
            case 1:
                MBMoveNextMasuSet(-1, 7, 0);
                break;
            case 2:
                MBMoveNextMasuSet(-1, 8, 0);
                break;
            default:
                MBMoveNextMasuSet(-1, 9, 0);
                break;
            }
            break;
        }
    }
    omDelPrcObj(NULL);
}

void MB1Ev_Branch5(void) {
    MB1Ev_BranchMain(mb1ev_branch5Masu, mb1ev_branch5Link, mb1ev_branch5ComTree);
    omDelPrcObj(NULL);
}

void MB1Ev_Branch6(void) {
    MB1Ev_BranchMain(mb1ev_branch6Masu, mb1ev_branch6Link, mb1ev_branch6ComTree);
    omDelPrcObj(NULL);
}

void MB1Ev_Branch7(void) {
    MB1Ev_BranchMain(mb1ev_branch7Masu, mb1ev_branch7Link, mb1ev_branch7ComTree);
}

void MB1Ev_Branch7RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch7();
    }
}

void MB1Ev_Branch8(void) {
    MB1Ev_BranchMain(mb1ev_branch8Masu, mb1ev_branch8Link, mb1ev_branch8ComTree);
}

void MB1Ev_Branch8RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch8();
    }
}

void MB1Ev_Branch9(void) {
    MB1Ev_BranchMain(mb1ev_branch9Masu, mb1ev_branch9Link, mb1ev_branch9ComTree);
}

void MB1Ev_Branch9RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch9();
    }
}

void MB1Ev_Branch10(void) {
    MB1Ev_BranchMain(mb1ev_branch10Masu, mb1ev_branch10Link, mb1ev_branch10ComTree);
}

void MB1Ev_Branch10RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch10();
    }
}

void MB1Ev_Branch11(void) {
    MB1Ev_BranchMain(mb1ev_branch11Masu, mb1ev_branch11Link, mb1ev_branch11ComTree);
}

void MB1Ev_Branch11RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch11();
    }
}

void MB1Ev_Branch12(void) {
    MB1Ev_BranchMain(mb1ev_branch12Masu, mb1ev_branch12Link, mb1ev_branch12ComTree);
}

void MB1Ev_Branch12RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch12();
    }
}

void MB1Ev_Merge1(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x36) {
        MBMoveNextMasuSet(-1, 1, 0xD);
    }
}

void MB1Ev_Merge2(void) {
    MB1Ev_BranchMerge(0x2E, 0xF, 0xA);
}

void MB1Ev_Merge3(void) {
    MB1Ev_BranchMerge(0x34, 3, 6);
}

void MB1Ev_Merge4(void) {
    MB1Ev_BranchMerge(0x33, 15, 2);
}

void MB1Ev_Merge5(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x8D) {
        MBMoveNextMasuSet(-1, 5, 0xB);
    }
}

void MB1Ev_Merge6(void) {
    MB1Ev_BranchMerge(0x4C, 7, 6);
}

void MB1Ev_Merge7() {
    MB1Ev_BranchMerge(0x59, 2, 7);
}

void MB1Ev_Merge8() {
    MB1Ev_BranchMerge(0x47, 2, 7);
}

void MB1Ev_Merge9() {
    MB1Ev_BranchMerge(0x7C, 10, 2);
}

void MB1Ev_Merge10(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) != 0x7D) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void MB1Ev_Merge11(void) {
    MB1Ev_BranchMerge(0x3F, 0xE, 3);
}

void MB1Ev_Merge12() {
    MB1Ev_BranchMerge(0x15, 5, 11);
}

void MB1Ev_Merge13(void) {
    MB1Ev_BranchMerge(0x50, 0xA, 0xB);
}

void MB1Ev_Merge14(void) {
    MB1Ev_BranchMerge(0x55, 2, 7);
}

void MB1Ev_Merge15(void) {
    MB1Ev_BranchMerge(0x60, 0xC, 4);
}

void MB1Ev_Merge16(void) {
    MB1Ev_BranchMerge(0x60, 0xB, 4);
}

void MB1Ev_Merge17(void) {
    MB1Ev_BranchMerge(0x24, 0xC, 4);
}

void MB1Ev_Merge18(void) {
    MB1Ev_BranchMerge(0x44, 1, 8);
}

void MB1Ev_RevFlagClear(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (player->rev & 1) {
        player->rev &= ~1;
    }
}

void MB1Ev_Merge19(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    MBMoveNextMasuSet(-1, 0x10, 1);
    player->rev &= ~1;
}

void MB1Ev_Merge20(void) {
    MB1Ev_BranchMerge(9, 0xF, 0xA);
}

void MB1Ev_Merge21(void) {
    MB1Ev_BranchMerge(0x27, 0xE, 3);
}

void MB1Ev_Merge22(void) {
    MB1Ev_BranchMerge(0x20, 0xA, 0xB);
}

void MB1Ev_KeyManMasu(void) {
    GW_PLAYER *player;
    Process *proc;
    UnkVibrateProcess *vib;
    s32 masu;
    s32 faceSpace;
    s32 next;
    s32 arg;
    s32 ret;
    s32 a;
    s32 b;
    s32 blocked = 1;
    GW_SYSTEM* system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);

    if ((((masu == 0x7B) | (masu == 0x79)) == 0 || !(player->rev & FLAG_REV)) &&
        (((masu == 0x4C) | (masu == 0x3F)) == 0 || (player->rev & FLAG_REV))) {
        MBPlayerMotionSet(-1, -1, 2);

        if (MBItemFind(system->current_player_index, ITEM_SKELETON_KEY) != -1) {
            MBSaiNumKill(system->current_player_index);
            switch (masu) {
            case 0x4C:
            case 0x7B:
                MBPlayerRotMasuStart(-1, 8, 0x6D);
                break;
            default: 
                MBPlayerRotMasuStart(-1, 8, 0x93);
            }
            
            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.6f));
            HuPrcChildWatch();
            MBPlayerVibrate(-1, 1);

            while (1) {
                MBDlgWinCreate(0x38, 0x4103);
                ret = MB1Ev_YesNoChoiceGet((void*)2, 0);
                MBDlgWinClose();
                MBDlgWinKill();
                switch (ret) {
                case 0:
                    MBDlgWinExec(0x38, 0x4104);
                    GwPlayer[system->current_player_index]
                        .itemNo[MBItemFind(system->current_player_index, ITEM_SKELETON_KEY)] = ITEM_NONE;
                    
                    MBItemRemoveEmpty(GwSystem.current_player_index);
                    MBStatusItemIconSprReinit(-1);
                    
                    switch (masu) {
                    case 0x7B:
                        MB1_GateOpen(0, 0);
                        break;
                    case 0x79:
                        MB1_GateOpen(1, 0);
                        break;
                    case 0x4C:
                        MB1_GateOpen(0, 1);
                        break;
                    default:
                        MB1_GateOpen(1, 1);
                        break;
                    }
                    blocked = 0;
                    vib = MBPlayerVibrateObjCreate(-1, 2, 5);
                    HuPrcSleep(0x14);
                    MBPlayerVibrateObjKill(vib);
                    break;
                case 1:
                    MBDlgWinExec(0x38, 0x4105);
                    break;
                case 2:
                    MB1_MapScroll();
                    continue;
                }
                break;
            }
            MBSaiNumShow(system->current_player_index);
            proc = HuPrcCurrentGet();
            HuPrcChildLink(proc, MBCameraZoomMotStart(1.3f));
            HuPrcChildWatch();
        } else {
            MBDlgWinExec(-1, 0x4106);
        }

        if (blocked != 0) {
            switch (masu) {
            case 0x7B:
                MBMoveNextMasuSet(-1, 6, 0);
                player->rev |= 1;
                break;
            case 0x4C:
                MBMoveNextMasuSet(-1, 6, 4);
                player->rev &= ~1;
                break;
            case 0x79:
                MBMoveNextMasuSet(-1, 9, 2);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 9, 6);
                player->rev &= ~1;
                break;
            }
        }
    }
    omDelPrcObj(NULL);
}

void MB1Ev_Branch13(void) {
    MB1Ev_BranchMain(mb1ev_branch13Masu, mb1ev_branch13Link, mb1ev_branch13ComTree);
}

void MB1Ev_Branch13RKinoko(void) {
    if ((MBPlayerGet(CUR_PLAYER)->rev & FLAG_UNK_80) && (mbWalkNum != 0)) {
        MB1Ev_Branch13();
    }
}

void MB1Ev_BankMasuBranch(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 0x17) {
        MB1Ev_Branch13RKinoko();
    }
}

void MB1Ev_StarMasuBranch(void) {
    GW_PLAYER* temp_v0 = MBPlayerGet(CUR_PLAYER);
    s16 temp_v0_2 = MBMasuLinkMasuIdGet(temp_v0->clink, temp_v0->cidx);

    switch (temp_v0_2) {
    case 0x5E:
        if (MBMasuLinkMasuIdGet(temp_v0->blink, temp_v0->bidx) == 0x5D) {
            MBMoveNextMasuSet(-1, 5, 3);
            return;
        }
        return;
    case 0x4D:
        if (MBMasuLinkMasuIdGet(temp_v0->blink, temp_v0->bidx) == 0x58) {
            MBMoveNextMasuSet(-1, 1, 0xD);
        }
        if (temp_v0->bidx == -1) {
            temp_v0->blink = 1;
            temp_v0->bidx = 0xD;
        }
        break;
    }
}

void MB1Ev_Branch14(void) {
    MB1Ev_BranchMain(mb1ev_branch14Masu, mb1ev_branch14Link, mb1ev_branch14ComTree);
}

void MB1Ev_TeresaMasuBranch(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 0x92) {
        if (player->rev & FLAG_UNK_80) {
            if (mbWalkNum != 0) {
                MB1Ev_Branch14();
                return;
            }
        }
        MBMoveNextMasuSet(-1, 1, 0);
    }
}

s32 MB1Ev_YesNoChoiceGet(DecisionTreeNonLeafNode *arg0, s32 arg1) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 pct;
    s32 i;
    s32 j;

    
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                switch ((s32)arg0) {
                case 0:
                    count = MBPlayerRankRandGet(0) + 1;
                    break;
                case 1:
                    count = MBPlayerRankRandGet(1) + 1;
                    break;
                case 2:
                    count = arg1 + 1;
                    break;
                default:
                    count = MBComTreeExec(arg0) + 1;
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

    if (count != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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

void MB1Ev_WinPlayerKeyExec(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s16 sp10[2];
    s16 temp_v0;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    temp_v0 = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = temp_v0;
    HuWinMesSet(temp_v0, arg1, -1, -1);
    HuWinExAnimIn(temp_v0);
    MBWinIdPlayerKeyWait(temp_v0, arg3);
    HuWinExAnimOut(temp_v0, 0);
    HuWinKill(temp_v0);
}

void MB1Ev_ItemSelAttrProc(void) {
    while (TRUE) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), HUSPR_ATTR_DISPOFF);
        HuPrcVSleep();
    }
}

void MB1Ev_StarMasu(void) {
    Process* temp_s0;
    s16 ret;
    s32 var_a0;
    s32 var_a1;
    s16 space = MBMasuCurGet();
    GW_SYSTEM* system = &GwSystem;

    if (MB1Ev_StarCheck(space) == 1) {
        MBSaiNumKill(system->current_player_index);
        MBPlayerMotionSet(-1, -1, 2U);
        MBPlayerRotMasuStart(-1, 8, MB1Ev_StarGuideMasuGet());
        temp_s0 = HuPrcCurrentGet();
        HuPrcChildLink(temp_s0, MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuAudFXPlay(0x159);
        if (GwPlayer[system->current_player_index].itemTurn != 0) {
            MBDlgWinInsertCreate(0x16, 0x4805, GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            MBDlgWinMesWait();
            MBDlgWinClose();
            MBDlgWinKill();
        }
        if (GwPlayer[system->current_player_index].star >= STARS_MAX) {
            MBDlgWinExec(0x16, 0x4804);
            if (mbStarMusF != 0) {
                msmMusFadeOut(mbSubMusNo, 0x3C);
                msmMusPlayDefault(mbBoardMusId);
                HuAudSeqVolFadeOut(0);
                HuAudSeqVolFadeIn(0x5A);
                mbSubMusNo = -1;
            }
            MBSaiNumShow(system->current_player_index);
            temp_s0 = HuPrcCurrentGet();
            HuPrcChildLink(temp_s0, MBCameraZoomMotStart(1.3f));
            HuPrcChildWatch();
        } else if (GwPlayer[system->current_player_index].coin >= 20) {
            choiceLoop:
            MBDlgWinInsertCreate(0x16, 0x4800, GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            ret = MB1Ev_YesNoChoiceGet((void*)2, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            switch (ret) {
            case 0:
                MBCoinChangeCreate(system->current_player_index, -0x14);
                MBCoinTakeCreate(system->current_player_index, -0x14);
                HuPrcSleep(30);
                MBDlgWinExec(0x16, 0x4802);
                if (mbStarMusF != 0) {
                    HuAudSeqStop();
                    msmMusFadeOut(mbSubMusNo, 0x3C);
                    ret = -1;
                    mbSubMusNo = -1;
                } else {
                    HuAudSeqFadeOut(0x5A);
                }
                MB1Ev_StarGetExec(mb1_starGuideBaseMdl);
                HuPrcSleep(30);
                MBBoardRestartSet();
                MBExitReq(2);
                break;
            case 1:
                if (mbStarMusF != 0) {
                    msmMusFadeOut(mbSubMusNo, 0x3C);
                    msmMusPlayDefault(mbBoardMusId);
                    HuAudSeqVolFadeOut(0);
                    HuAudSeqVolFadeIn(0x5A);
                    mbSubMusNo = -1;
                }
                MBDlgWinExec(0x16, 0x4803);
                MBSaiNumShow(system->current_player_index);
                temp_s0 = HuPrcCurrentGet();
                HuPrcChildLink(temp_s0, MBCameraZoomMotStart(1.3f));
                HuPrcChildWatch();
                break;
            case 2:
                MB1_MapScroll();
                goto choiceLoop;
            }
        } else {
            MBDlgWinExec(0x16, 0x4801);
            if (mbStarMusF != 0) {
                msmMusFadeOut(mbSubMusNo, 0x3C);
                msmMusPlayDefault(mbBoardMusId);
                HuAudSeqVolFadeOut(0);
                HuAudSeqVolFadeIn(0x5A);
                mbSubMusNo = -1;
            }
            MBSaiNumShow(system->current_player_index);
            temp_s0 = HuPrcCurrentGet();
            HuPrcChildLink(temp_s0, MBCameraZoomMotStart(1.3f));
            HuPrcChildWatch();
        }
    }
    MB1Ev_StarMasuBranch();
    return;
}

void MB1Ev_BankMasu(void) {
    char sp20[16];
    char sp30[16];
    Vec dir;
    SpaceData *bankSpace;
    SpaceData *pos;
    Object *bank;
    Object *coins;
    f32 base;
    f32 angle;
    s16 masu = MBMasuCurGet();
    s32 useItem = 0;
    s32 ret;
    s32 idx;
    s16 coin;
    GW_SYSTEM* system = &GwSystem;

    pos = NULL;
    bankSpace = NULL;

    if (MBSaiValueGet(system->current_player_index) <= 0) {
        MBPlayerVibrate(-1, 3);
    }
    MBPlayerMotionSet(-1, -1, 2);

    switch(masu) {
    case 0x37:
        MBPlayerRotMasuStart(-1, 8, 0x71);
        pos = MBMasuGet(0x71);
        bankSpace = MBMasuGet(0x37);
        break;
    case 0x17:
        MBPlayerRotMasuStart(-1, 8, 0x6F);
        pos = MBMasuGet(0x6F);
        bankSpace = MBMasuGet(0x17);
        break;
    }

    HuPrcSleep(8);
    if (MBSaiValueGet(system->current_player_index) > 0) {
        MBSaiNumKill(system->current_player_index);
    }

    HuAudFXPlay(0x114);
    bank = MBModelCreate(0x32, NULL);
    MBModelTempAllocFree(bank);
    HuVecSubtract(&dir, &bankSpace->coords, &pos->coords);
    MBVecNormalize(&dir);
    HuVecCopy3F(&bank->rot, &dir);
    bank->scale.y = 0.0f;
    HuVecCopy3F(&bank->coords, &pos->coords);
    MBMotionSet(bank, -1, 1);
    MBModelDispFlagSet(bank);

    coins = MBModelCreate(0x35, mb1ev_bankCoinPileMot);
    MBModelTempAllocFree(coins);
    HuVecCopy3F(&coins->rot, &dir);
    HuVecCopy3F(&coins->coords, &pos->coords);
    coins->scale.z = 1.2f;
    coins->scale.x = 1.2f;
    coins->scale.y = 1.2f;
    MBModelDispOff(coins);

    base = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        bank->scale.y = sindf(angle) * base;
        bank->scale.x = (sindf(angle) * base * 0.2f) + 0.8f;
        bank->scale.z = (sindf(angle) * base * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    for (; 50.0f < angle; angle -= 11.25f) {
        bank->scale.y = sindf(angle) * base;
        bank->scale.x = (sindf(angle) * base * 0.2f) + 0.8f;
        bank->scale.z = (sindf(angle) * base * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    bank->scale.y = 1.0f;
    bank->scale.x = 1.0f;
    bank->scale.z = 1.0f;
    MBModelDispFlagSet(coins);

    if (MBItemFind(-1, 0xF) != -1) {
        loopstart:
        MBDlgWinInsertCreate(-1, 0x3A1D, 0, 0, 0, 0, 0);
        ret = MB1Ev_YesNoChoiceGet(mb1ev_bankComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        switch (ret) {
        case 0:
            useItem = 1;
            break;
        case 2:
            MB1_MapScroll();
            goto loopstart;
        }
    }

    MBMotionSet(bank, -1, 0);
    Hu3DMotionSpeedSet(bank->omObj1->model[0], 1.2f);
    while (MBMotionCheck(bank) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x259);
    MBMotionSet(coins, 0, 0);
    while (MBMotionCheck(coins) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(coins, -1, 2);

    if (useItem != 0) {
        sprintf(sp20, mb1ev_numFmtStr, GwSystem.bank_coins);
        if (GwSystem.bank_coins != 0) {
            MBDlgWinInsertCreate(2, 0x3A1E, (s32)sp20, 0, 0, 0, 0);
        } else {
            MBDlgWinInsertCreate(2, 0x3A1F, (s32)NULL, 0, 0, 0, 0);
        }
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBDlgWinKill();

        if (GwSystem.bank_coins != 0) {
            mbItemBtnF = 0;
            MB1Ev_BankKoopaCardExec();
            mbItemBtnF = 1;
        } else {
            MBDlgWinInsertCreate(2, 0x3A21, 0, 0, 0, 0, 0);
            MBDlgWinMesWait();
            MBDlgWinClose();
            MBDlgWinKill();
            idx = MBItemFind(-1, 0xF);
            GwPlayer[system->current_player_index].itemNo[idx] = -1;
            MBItemRemoveEmpty(system->current_player_index);
            MBStatusItemIconSprReinit(system->current_player_index);
        }
        if (MBSaiValueGet(system->current_player_index) > 0) {
            MBSaiNumShow(system->current_player_index);
        }
    } else if (MBSaiValueGet(system->current_player_index) > 0) {
        coin = GwPlayer[system->current_player_index].coin;
        if ((coin != 0) & (coin < 5)) {
            sprintf(sp20, mb1ev_numFmtStr, coin);
            sprintf(sp30, mb1ev_numFmtStr,
                    GwSystem.bank_coins + GwPlayer[system->current_player_index].coin);
            MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
            MBDlgWinClose();
            GwSystem.bank_coins += GwPlayer[system->current_player_index].coin;
            MB1_BankCoinHide();
            MBCoinChangeCreate(system->current_player_index,
                               -GwPlayer[system->current_player_index].coin);
            MBCoinTakeCreate(system->current_player_index,
                             -GwPlayer[system->current_player_index].coin);
            HuPrcSleep(30);
            MBDlgWinOpen();
        } else if (GwPlayer[system->current_player_index].coin == 0) {
            sprintf(sp20, mb1ev_numFmtStr, GwSystem.bank_coins);
            MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
        } else {
            sprintf(sp20, mb1ev_numFmtStr, GwSystem.bank_coins + 5);
            MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
            MBDlgWinClose();
            GwSystem.bank_coins += 5;
            MB1_BankCoinHide();
            MBCoinChangeCreate(system->current_player_index, -5);
            MBCoinTakeCreate(system->current_player_index, -5);
            HuPrcSleep(30);
            MBDlgWinOpen();
        }
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBDlgWinKill();
        MBSaiNumShow(system->current_player_index);
        HuPrcSleep(10);
    } else if (GwSystem.bank_coins != 0) {
        sprintf(sp20, mb1ev_numFmtStr, GwSystem.bank_coins);
        MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBCoinChangeCreate(system->current_player_index, GwSystem.bank_coins);
        MBCoinTakeCreate(system->current_player_index, GwSystem.bank_coins);
        GwSystem.bank_coins = 0;
        MB1_BankCoinHide();
        MBVecForwardSet(&MBPlayerGet(CUR_PLAYER)->player_obj->rot);
        MBPlayerMotionSet(-1, 5, 0);
        PlayerFXPlay(0x274, system->current_player_index);
        HuPrcSleep(30);
        MBPlayerMotionSet(-1, -1, 2);
        MBDlgWinOpen();
        MBDlgWinMesWait();
        MBDlgWinClose();
        MBDlgWinKill();
    } else {
        MBDlgWinExec(2, 0x1204);
    }

    HuAudFXPlay(0x115);
    MBMotionSet(bank, -1, 4);
    Hu3DMotionSpeedSet(bank->omObj1->model[0], 1.2f);
    Hu3DMotionTimeSet(bank->omObj1->model[0],
                        (f32)Hu3DMotion[Hu3DData[bank->omObj1->model[0]].motId].unk02);
    while (MBMotionStartCheck(bank) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(coins);

    base = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        bank->scale.y = sindf(angle) * base;
        bank->scale.x = (sindf(angle) * base * 0.2f) + 0.8f;
        bank->scale.z = (sindf(angle) * base * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; 0.0f < angle; angle -= 11.25f) {
        bank->scale.y = sindf(angle) * base;
        bank->scale.x = (sindf(angle) * base * 0.2f) + 0.8f;
        bank->scale.z = (sindf(angle) * base * 0.2f) + 0.8f;
        HuPrcVSleep();
    }
    bank->scale.y = 0.0f;
    bank->scale.x = 0.0f;
    bank->scale.z = 0.0f;

    MBModelKill(bank);
    MBModelKill(coins);
    MB1Ev_BankMasuBranch();
}

s32 MB1Ev_ShopItemIdxGet(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb1ev_shopItemEnableTbl[i] != 0) {
            if (mb1ev_shopItemTbl[mb1ev_shopHostNo]
                                              [mb1ev_shopItemRow][i] == arg0) {
                return i;
            }
        }
    }
    return -1;
}

s32 MB1Ev_ShopItemNumGet(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (mb1ev_shopItemTbl[mb1ev_shopHostNo]
                                          [mb1ev_shopItemRow][i] == -1) {
            break;
        }
    }
    return i;
}

void MB1Ev_ShopBagBounceProc(void) {
    f32 var_f20;
    s32 temp_s1;
    f32 temp;

    temp_s1 = (s32)HuPrcCurrentGet()->user_data;
    MBPlayerGet(GwSystem.current_player_index);
    MBPlayerVibrate(-1, 2);
    HuAudFXPlay(0x15A);
    for (var_f20 = 0.0f; var_f20 < 180.0f; var_f20 += 20.0f) {
        temp = (sindf(var_f20) * 1.5f) + 1.0f;
        HuSprScaleSet(temp_s1, 0, temp, 1.0f - (sindf(var_f20) * 0.5f));
        HuPrcVSleep();
    }
    
    for (; var_f20 < 360.0f; var_f20 += 20.0f) {
        temp = (sindf(var_f20) * 0.5f) + 1.0f;
        HuSprScaleSet(temp_s1, 0, temp, 1.0f - (sindf(var_f20) * 0.25f));
        HuPrcVSleep();
    }
    HuSprScaleSet(temp_s1, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

void MB1Ev_ShopMasu(void) {
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
        case 0x77:
            camMasu = 0x73;
            spaceA = MBMasuGet(0x73);
            spaceB = MBMasuGet(0x77);
            mb1ev_shopNo = 0;
            break;
        case 0x7C:
            camMasu = 0x6E;
            spaceA = MBMasuGet(0x6E);
            spaceB = MBMasuGet(0x7C);
            mb1ev_shopNo = 1;
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
            effectModel = MBModelCreate(0x39, mb1ev_shopKoopaJrMot);
        } else {
            effectModel = MBModelCreate(0x1B, mb1ev_shopKinopioMot);
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
        MBDlgWinExec(dlgWin, mb1ev_shopLastTurnMesTbl[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, mb1ev_shopItemFullMesTbl[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, mb1ev_shopNoCoinMesTbl[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, mb1ev_shopEnterMesTbl[shopIdx]);
    choice = MB1_ComShopEnterChoice();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = MBTurnTierGet(-1);
            row = mb1ev_shopItemRowTbl[shopIdx][i][MBPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (mb1ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mb1ev_shopItemTbl[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (mb1ev_shopItemTbl[shopIdx][row][j] == -1) {
                    continue;
                }
                if (mbItemPriceTbl[mb1ev_shopItemTbl[shopIdx][row][j]] >
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

            MBDlgWinInsertCreate(dlgWin, mb1ev_shopItemMesTbl[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            MBDlgWinTabWidthSet(0);
            mb1ev_shopHostNo = slot;
            mb1ev_shopItemRow = row;
            mb1ev_shopItemEnableTbl = enabled;
            sel = MB1_ComShopItemChoice(enabled);
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
            shopTable = mb1ev_shopItemTbl;
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
                    mb1ev_shopItemTbl[shopIdx][row][sel];
                item = mb1ev_shopItemTbl[shopIdx][row][sel];
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

            if (mb1ev_shopItemTbl[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = mb1ev_shopBagRowTbl[shopIdx][MBTurnTierGet(-1)]
                                         [MBPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < mb1ev_shopBagRateTbl[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = mb1ev_shopBagItemTbl[shopIdx][i];

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
                    prc = omAddPrcObj(MB1Ev_ShopBagBounceProc, 0x4002, 0, 0);
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
            MBDlgWinExec(dlgWin, mb1ev_shopCancelMesTbl[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                MB1_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB1_MapScroll();
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

void MB1Ev_TeresaFadeIn(Object* arg0) {
    s32 i;

    MBModelDispOn(arg0);
    
    for (i = 0; i < 256; i += 12, HuPrcVSleep()) {
        Hu3DModelTPLvlSet(arg0->omObj1->model[0], i);
        Hu3DModelTPLvlSet(arg0->omObj2->model[0], i);
    }
    Hu3DModelTPLvlSet(arg0->omObj1->model[0], 0xFF);
    Hu3DModelTPLvlSet(arg0->omObj2->model[0], 0xFF);
}

void MB1Ev_TeresaFadeOut(Object* arg0) {
    s32 i;

    for (i = 255; i >= 0; i -= 12, HuPrcVSleep()) {
        Hu3DModelTPLvlSet(arg0->omObj1->model[0], i);
        Hu3DModelTPLvlSet(arg0->omObj2->model[0], i);
    }

    Hu3DModelTPLvlSet(arg0->omObj1->model[0], 0);
    Hu3DModelTPLvlSet(arg0->omObj2->model[0], 0);
    MBModelDispOff(arg0);
}

s32 MB1Ev_TeresaStarSteal(s32 arg0) {
    void *data;
    s16 grpId;
    s16 sprId;
    s32 hasCharm;
    s32 frames;
    s32 i;

    hasCharm = 0;
    grpId = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    sprId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(grpId, 0, sprId, 0);
    HuSprPriSet(grpId, 0, 0xA);
    HuSprAnimModeSet(grpId, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAttrSet(grpId, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(grpId, 0,
                        mb1ev_teresaSprPosTbl[arg0][0],
                        mb1ev_teresaSprPosTbl[arg0][1]);
    HuSprTPLvlSet(grpId, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 17; i++) {
        HuSprPosSet(grpId, 0,
        (i * mb1ev_teresaSprDirTbl[arg0][0]) + mb1ev_teresaSprPosTbl[arg0][0],
        (i * mb1ev_teresaSprDirTbl[arg0][1]) + mb1ev_teresaSprPosTbl[arg0][1]);
        HuSprTPLvlSet(grpId, 0, i * 0x10);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grpId, 0, 0xFF);

    if (MBItemFind(arg0, ITEM_BOO_REPELLENT) != -1) {
        hasCharm = 1;
        omAddPrcObj(MB1Ev_TereYokeSprayProc, 0x4002, 0, 0)->user_data = (void *)arg0;
    }

    if (hasCharm == 0) {
        GwPlayer[arg0].star--;
    }

    MBPlayerVibrate(arg0, 5);
    HuAudFXPlay(0x257);

    
    if (hasCharm != 0) {
        frames = 120;
    } else {
        frames = 30;
    }
    
    for (i = 0; i < frames; i++) {
        HuSprPosSet(grpId, 0,
            (mb1ev_teresaSprDirTbl[arg0][0] * 16.0f) + mb1ev_teresaSprPosTbl[arg0][0],
            (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) + mb1ev_teresaSprPosTbl[arg0][1]
                + (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 16; i >= 0; i--) {
        HuSprPosSet(grpId, 0,
            (i * mb1ev_teresaSprDirTbl[arg0][0]) + mb1ev_teresaSprPosTbl[arg0][0],
            (i * mb1ev_teresaSprDirTbl[arg0][1]) + mb1ev_teresaSprPosTbl[arg0][1]);
        HuSprTPLvlSet(grpId, 0, i * 0x10);
        HuPrcVSleep();
    }

    HuSprGrpKill(grpId);
    HuSprAnimKill(sprId);
    return hasCharm == 0;
}


void MB1Ev_TeresaWinCloseProc(void) {
    MBWinClose();
    omDelPrcObj(NULL);
}

//TODO: gotos and why is "i" compared against unsigned values in the loop at the end?
s32 MB1Ev_TeresaSteal(s32 arg0) {
    s32 hasCharm;
    s16 booGrp;
    s16 booSpr;
    s16 chrGrp;
    s16 chrSpr;
    UnkVibrateProcess *vib;
    void *file;
    s16 sfxTimer;
    s32 count;
    s32 hold;
    s32 shake;
    s32 pulled;
    s16 pull;
    s32 mesNum;
    f32 angle;
    s32 i;
    s32 j;
    s32 coinsRet;
    s32 rand;
    s32 base;

    hasCharm = 0;
    booGrp = HuSprGrpCreate(1, 5);
    file = DataRead(0x13020E);
    booSpr = HuSprAnimRead(file);
    DataClose(file);
    HuSprGrpMemberSet(booGrp, 0, booSpr, 0);
    HuSprPriSet(booGrp, 0, 0xA);
    HuSprAnimModeSet(booGrp, 0, HUSPR_ANIM_MODE_STOP);
    HuSprAttrSet(booGrp, 0, HUSPR_ATTR_XLU);
    HuSprPosSet(booGrp, 0,
                        mb1ev_teresaSprPosTbl[arg0][0],
                        mb1ev_teresaSprPosTbl[arg0][1]);
    HuSprTPLvlSet(booGrp, 0, 0);

    chrGrp = HuSprGrpCreate(1, 5);
    pulled = 0;
    file = DataRead(mbItemCharSprTbl[GwPlayer[arg0].chr]);
    chrSpr = HuSprAnimRead(file);
    DataClose(file);
    HuSprGrpMemberSet(chrGrp, 0, chrSpr, 0);
    HuSprPriSet(chrGrp, 0, 0xA);
    HuSprAnimModeSet(chrGrp, 0, HUSPR_ANIM_MODE_BANK);

    if (arg0 & 1) {
        HuSprAttrSet(chrGrp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FLIPX);
    } else {
        HuSprAttrSet(chrGrp, 0, HUSPR_ATTR_XLU);
    }
    

    if (MBItemFind(arg0, ITEM_BOO_REPELLENT) != -1) {
        HuSprDispOff(chrGrp, 0);
    }

    HuSprPosSet(chrGrp, 0,
        (mb1ev_teresaSprPosTbl[arg0][0] -
         (mb1ev_teresaSprDirTbl[arg0][0] * 16.0f)) - 8.0f,
        (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
         mb1ev_teresaSprPosTbl[arg0][1]);
    HuSprTPLvlSet(chrGrp, 0, 0);

    HuAudFXPlay(0x133);
    for (i = 0; i < 17; i++, HuPrcVSleep()) {
        HuSprPosSet(booGrp, 0,
            (i * mb1ev_teresaSprDirTbl[arg0][0]) + mb1ev_teresaSprPosTbl[arg0][0],
            (i * mb1ev_teresaSprDirTbl[arg0][1]) + mb1ev_teresaSprPosTbl[arg0][1]);
        HuSprTPLvlSet(booGrp, 0, i * 0x10);
        HuSprTPLvlSet(chrGrp, 0, i * 0x10);
    }
    HuSprTPLvlSet(booGrp, 0, 0xFF);
    HuSprTPLvlSet(chrGrp, 0, 0xFF);

    if (MBItemFind(arg0, ITEM_BOO_REPELLENT) != -1) {
        mesNum = 0x620F;
    } else {
        mesNum = 0x620E;
    }
    MBWinInsertOpen(mesNum, (char*)mbCharNameMesTbl[GwPlayer[arg0].chr], 0, 0, 0, 0);
    MBPlayerVibrate(arg0, 2);
    MBWinKeyWait(arg0);

    if (MBItemFind(arg0, ITEM_BOO_REPELLENT) != -1) {
        omAddPrcObj(MB1Ev_TeresaWinCloseProc, 0x1000, 0, 0);
        HuPrcSleep(0x14);
    }

    count = 0;
    hold = 0;
    if (MBItemFind(arg0, ITEM_BOO_REPELLENT) != -1) {
        count = 1;
        hasCharm = 1;
        omAddPrcObj(MB1Ev_TereYokeSprayProc, 0x4002, 0, 0)->user_data = (void *)arg0;
    }

    HuAudFXPlay(0x133);
    vib = MBPlayerVibrateObjCreate(arg0, 3, 5);
    sfxTimer = MBRand(10.0f) + 1;

    for (i = 0, shake = 0; i < 0x78; i++, HuPrcVSleep(), sfxTimer--) {
        if (sfxTimer == 0) {
            HuAudFXPlay(0x257);
            sfxTimer = MBRand(15.0f) + 30;
        }
        if (hold >= 2) {
            hold--;
        }

        if (hold == 0) {
            HuSprPosSet(booGrp, 0,
                (mb1ev_teresaSprDirTbl[arg0][0] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][0],
                (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][1] + (2.0f * sindf(i * 90)));
        } else if (hold == 9) {
            angle = shake * 90;
            HuSprPosSet(booGrp, 0,
                (mb1ev_teresaSprDirTbl[arg0][0] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][0] + (2.0f * sindf(angle)),
                (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
            HuSprPosSet(chrGrp, 0,
                (mb1ev_teresaSprPosTbl[arg0][0] - 8.0f) + (2.0f * sindf(angle)),
                (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
            shake++;
        }

        if (GwPlayer[arg0].stat & PLAYER_IS_CPU) {
            if (hold != 0) {
                if (GwPlayer[arg0].cpu_difficulty == CPU_EASY) {
                    if ((6 - MBRand(3.0f)) >= hold) {
                        goto skip;
                    }
                } else if (GwPlayer[arg0].cpu_difficulty == CPU_NORMAL) {
                    if ((7 - MBRand(3.0f)) >= hold) {
                        goto skip;
                    }
                } else if (GwPlayer[arg0].cpu_difficulty == CPU_HARD) {
                    if ((8 - MBRand(3.0f)) >= hold) {
                        goto skip;
                    }
                } else {
                    if ((9 - MBRand(2.0f)) >= hold) { //CPU_VERY_HARD
                        goto skip;
                    }
                }
                goto dummy;
            }
            goto skip;
        } else {
            pull = ContBtnDown[GwPlayer[arg0].pad] & A_BUTTON;
        }

        if (pull != 0) {
            skip:
            if (hasCharm == 0) {
                count++;
                hold = 0xA;
                if (pulled == 0) {
                    HuSprBankSet(chrGrp, 0, 1, 0);
                    HuSprAnimModeSet(chrGrp, 0, HUSPR_ANIM_MODE_BANK);
                    pulled = 1;
                    HuSprPosSet(chrGrp, 0,
                        mb1ev_teresaSprPosTbl[arg0][0] - 8.0f,
                        (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
                         mb1ev_teresaSprPosTbl[arg0][1]);
                }
            }
        }

        dummy:
        if ((hold == 0) && (pulled == 1)) {
            HuSprBankSet(chrGrp, 0, 0, 0);
            HuSprAnimModeSet(chrGrp, 0, HUSPR_ANIM_MODE_BANK);
            pulled = 0;
            HuSprPosSet(chrGrp, 0,
                (mb1ev_teresaSprPosTbl[arg0][0] -
                 (mb1ev_teresaSprDirTbl[arg0][0] * 16.0f)) - 8.0f,
                (mb1ev_teresaSprDirTbl[arg0][1] * 16.0f) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
        }
    }

    MBPlayerVibrateObjKill(vib);
    if (hasCharm == 0) {
        omAddPrcObj(MB1Ev_TeresaWinCloseProc, 0x1000, 0, 0);
    }

    if (count == 0) {
        for (i = 0x10; i >= 0; i -= 2, HuPrcVSleep()) {
            HuSprPosSet(booGrp, 0,
                (i * mb1ev_teresaSprDirTbl[arg0][0]) +
                 mb1ev_teresaSprPosTbl[arg0][0],
                (i * mb1ev_teresaSprDirTbl[arg0][1]) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
            HuSprTPLvlSet(booGrp, 0, i * 0x10);
            HuSprTPLvlSet(chrGrp, 0, i * 0x10);
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2, HuPrcVSleep()) {
            HuSprPosSet(booGrp, 0,
                (i * mb1ev_teresaSprDirTbl[arg0][0]) +
                 mb1ev_teresaSprPosTbl[arg0][0],
                (i * mb1ev_teresaSprDirTbl[arg0][1]) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
            HuSprPosSet(chrGrp, 0,
                (((i - 0x10) * mb1ev_teresaSprDirTbl[arg0][0]) +
                  mb1ev_teresaSprPosTbl[arg0][0]) - 8.0f,
                (i * mb1ev_teresaSprDirTbl[arg0][1]) +
                 mb1ev_teresaSprPosTbl[arg0][1]);
            if (hasCharm != 0) {
                i -= 2;
            }
        }

        HuSprBankSet(chrGrp, 0, 0, 0);
        HuSprAnimModeSet(chrGrp, 0, HUSPR_ANIM_MODE_BANK);
        for (i = 0x10; i >= 0; i -= 2, HuPrcVSleep()) {
            HuSprTPLvlSet(booGrp, 0, i * 0x10);
        }
    }

    HuSprGrpKill(booGrp);
    HuSprAnimKill(booSpr);
    HuSprGrpKill(chrGrp);
    HuSprAnimKill(chrSpr);

    pulled = -2;
    if (hasCharm == 0) {
        for (i = 0; i < sizeof(mb1ev_teresaCoinTurnTbl) / sizeof(mb1ev_teresaCoinTurnTbl[0]); i++) {
            if ((GwSystem.current_turn >= mb1ev_teresaCoinTurnTbl[i][0]) &&
                (GwSystem.current_turn <= mb1ev_teresaCoinTurnTbl[i][1])) {
                break;
            }
        }
        pulled = mb1ev_teresaCoinTurnTbl[i][2];
        for (i = 0; i < (sizeof(mb1ev_teresaCoinPenaltyTbl) / sizeof(u8)) / 3; i++) {
            if ((count >= mb1ev_teresaCoinPenaltyTbl[i][0]) &&
                (count <= mb1ev_teresaCoinPenaltyTbl[i][1])) {
                break;
            }
        }
        pulled = pulled - mb1ev_teresaCoinPenaltyTbl[i][2];
        if (pulled >= GwPlayer[arg0].coin) {
            pulled = -1;
        }
    }
    return pulled;
}


const char mb1ev_numFmtStr[] = "%d";

void MB1Ev_TeresaCoin(void) {
    Object *coin;
    Object *src;
    f32 angle;
    f32 y;

    src = HuPrcCurrentGet()->user_data;

    coin = MBModelLinkCreate(mb1ev_teresaCoinMdl);
    HuVecCopy3F(&coin->coords, &src->coords);
    HuVecCopyXYZ(&coin->scale, 2.0f, 2.0f, 2.0f);
    coin->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(coin);

    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        coin->velocity.x += 1.5;
        if ((src->velocity.x + 35.0f) <= coin->velocity.x) {
            break;
        }
        angle += 40.0f;
        HuMtxRotYF(Hu3DData[coin->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(coin);
    omDelPrcObj(NULL);
}

void MB1Ev_TeresaCoinCreate(void* arg0) {
    omAddPrcObj(MB1Ev_TeresaCoin, 0x1000, 0, 0)->user_data = arg0;
}

void MB1Ev_Teresa(void) {
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
    if (spaceId != 0x92) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(mb1_teresaGuideBaseMdl);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x6A;
        space = MBMasuGet(0x6A);
        boo = mb1_teresaGuideMdl[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
            if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    MB1Ev_TeresaFadeIn(boo);
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
    menuResult = MB1_ComTeresaTypeChoice(choices);
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
    playerChoice = MB1_ComTeresaPlayerChoice(choices);
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
                MB1_MapScrollCancel();
                winPauseF = 1;
                omAllPause();
            } else {
                MB1_MapScroll();
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
            if (rank < mb1ev_teresaComTargetRateTbl[i]) {
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
            if (GwSystem.current_turn >= mb1ev_teresaCoinTurnTbl[i][0] &&
                GwSystem.current_turn <= mb1ev_teresaCoinTurnTbl[i][1]) {
                break;
            }
        }
        estimatedAmount = mb1ev_teresaCoinTurnTbl[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    MB1Ev_TeresaFadeOut(boo);
    if (menu == 0) {
        resultAmount = MB1Ev_TeresaSteal(target);
        MB1Ev_TeresaFadeIn(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], mb1ev_numFmtStr, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], mb1ev_numFmtStr, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= mb1ev_teresaCoinDiffTbl[i]) {
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
            mb1ev_teresaCoinMdl = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(mb1ev_teresaCoinMdl);
            MBModelDispOff(mb1ev_teresaCoinMdl);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    MB1Ev_TeresaCoinCreate(boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(mb1ev_teresaCoinMdl);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = MB1Ev_TeresaStarSteal(target);
        MB1Ev_TeresaFadeIn(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            mb1ev_starGetTeresaF = 1;
            MB1Ev_StarGetExec(boo);
            mb1ev_starGetTeresaF = 0;
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
    MB1Ev_TeresaFadeOut(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        MB1_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
    } else {
        MB1_MapScroll();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        MB1Ev_TeresaFadeOut(boo);
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
            if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (mb1ev_teresaMdlFlipTbl[sys->current_board_index] != 0) {
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
    MB1Ev_TeresaMasuBranch();
}

void MB1Ev_Gate1Close(void) {
    MB1_GateClose(0);
}

void MB1Ev_Gate2Close(void) {
    MB1_GateClose(1);
}

omObjData* MB1Ev_ItemLampSmokeCreate(Vec* arg0, f32 arg1, f32 arg2, s16 arg3, Vec* arg4, s32 arg5) {
    Object* temp_v0_2;
    UnkChillyWaters* temp_v0;
    omObjData* temp_s4;
    s32 var_a0;

    temp_s4 = omAddObj(0x1F4, 0, 0, -1, MB1Ev_ItemLampSmokeObjMain);
    temp_v0 = temp_s4->data = HuMemAllocTag(sizeof(UnkChillyWaters), TAG_OVERLAY);
    temp_v0->unk_0C = 255.0f;
    temp_v0->unk_10 = arg1;
    temp_v0->unk_14 = arg2;
    
    HuVecCopy3F(&temp_v0->coords, arg4);
    if (arg5 != 0) {
        temp_v0_2 = MBModelFileCreate(0x1301F8, 0, 1.0f, 0.0f, 0);
    } else {
        temp_v0_2 = MBModelFileCreate(0x1301F7, 0, 1.0f, 0.0f, 0);
    }
    
    Hu3DModelScaleSet(temp_v0_2->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    temp_v0_2->coords.x = arg0->x;
    temp_v0_2->coords.y = arg0->y;
    temp_v0_2->coords.z = arg0->z;
    Hu3DModelTPLvlInit(temp_v0_2->omObj1->model[0]);
    Hu3DModelTPLvlSet(temp_v0_2->omObj1->model[0], 0xFF);
    temp_v0->unk_18 = temp_v0_2;
    temp_v0->unk_1C = arg3;
    return temp_s4;
}

void MB1Ev_ItemLampSmokeObjMain(omObjData* arg0) {
    Object* obj;
    UnkChillyWaters* temp_s0;
    f32 temp_f0;

    temp_s0 = arg0->data;
    obj = temp_s0->unk_18;
    HuVecAdd(&obj->coords, &obj->coords, &temp_s0->coords);
    temp_f0 = obj->scale.z + temp_s0->unk_10;
    obj->scale.z = temp_f0;
    obj->scale.y = temp_f0;
    obj->scale.x = temp_f0;
    temp_s0->unk_0C = temp_s0->unk_0C - temp_s0->unk_14;
    if (temp_s0->unk_0C < 0.0f) {
        temp_s0->unk_0C = 0.0f;
        if (temp_s0->unk_1C != 0) {
            MBModelKill(temp_s0->unk_18);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, OM_STAT_FUNCOFF);
    }
    Hu3DModelTPLvlSet(obj->omObj1->model[0], temp_s0->unk_0C);
}

void MB1Ev_ItemMajinLamp(void) {
    Vec pos;
    s8 link;
    s8 idx;
    GW_PLAYER *player;
    Object *lamp;
    UnkVibrateProcess *vib;
    f32 y;
    s32 angle;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    MB1Ev_ItemUseFadeOut();

    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);

    for (lamp->coords.y = 100.0f; lamp->coords.y > 30.0f; ) {
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
            {1.0f, 1.0f, 1.0f,},
            {1.0f, 2.0f, 1.0f},
            {0.0f, 2.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {0.0f, -1.0f, 1.0f},
            {-1.0f, 2.0f, 1.0f},
            {1.0f, -1.0f, 1.0f}
        };
        
        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB1Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }
    

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);

        
    MBMasuLinkIdxGet(
        mb1ev_starMasu[system->star_spawn_indices[system->current_star_spawn]], &link, &idx);
    player->clink = link;
    player->cidx = idx;
    player->nlink = link;
    player->nidx = idx + 1;
    player->blink = link;
    player->bidx = idx - 1;
    player->rev &= ~FLAG_REV;

    MBGameModeMajinLampSet();
    HuAudFXPlay(0x128);
    omAllUPause();
    while(1) {
    // for (; angle != 0x500; i++, HuPrcVSleep(), angle += 0x14) {
        Vec particleDir2[8] = {
            {1.0f, 1.0f, 1.0f,},
            {1.0f, 2.0f, 1.0f},
            {0.0f, 2.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {0.0f, -1.0f, 1.0f},
            {-1.0f, 2.0f, 1.0f},
            {1.0f, -1.0f, 1.0f}
        };
        
        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB1Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }

        i++;
        HuPrcVSleep();
        angle += 0x14;
        
        if (angle == 0x500) {
            msmMusPause(0);
        }
    }
}

void MB1Ev_ItemMajinLampStar(void) {
    mbStarMusF = 1;
    MBMasuEventCall(mb1ev_starMasu[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    mbStarMusF = 0;
    if ((MBExitFlagGet()) >= 0) {
        HuPrcSleep(-1);
    }
}

void MB1Ev_ItemWarpBlock(void) {
    s16 temp_v0;
    s32 temp_s0;
    s32 temp_s2 = GwSystem.current_player_index;
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);

    MB1Ev_ItemUseFadeOut();
    MBSaiKill(temp_s2);
    MBPlayerVibrate(-1, 3);
    GWBoardFlagSet(0x11);
    MBSaiCreate(temp_s2);
    temp_s0 = MBPlayerRankRandGet(1);
    omAllUPause();
    MBTurnHelpKill();
    HuPrcSleep(5);
    HuPrcSleep(0x19);
    MBPlayerMotionSet(temp_s2, 2, 0);
    MBModelJumpSet(GwPlayer[temp_s2].player_obj, 2.0f, -0.3f);
    HuPrcSleep(5);
    MBSaiHit(temp_s2);
    MBPlayerMotionShiftSet(temp_s2, -1, 0, 0xA, 2);
    HuPrcSleep(0x14);
    MBItemWarpBlockSwapInit();
    MBItemWarpBlockSwapPlayerSet(temp_s0);
    MBItemWarpBlockSwapCreate();
    GWBoardFlagClear(0x11);
    HuAudFXStop(MBSaiCreate(temp_s2));
    MBSaiDispOff(temp_s2);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    MBSaiValueSet(temp_s2, -1);
    temp_v0 = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    MBMasuCurSet(temp_v0);
    MBMasuEventCall(temp_v0, 1);
    if (MBExitFlagGet() >= 0) {
        HuPrcSleep(-1);
    }
    MBSaiSePlay(temp_s2);
}


typedef struct ItemMoveWork {
    /* 0x00 */ s16 startX;
    /* 0x02 */ s16 startY;
    /* 0x04 */ s16 endX;
    /* 0x06 */ s16 endY;
    /* 0x08 */ s16 frames;
    /* 0x0A */ s16 sprGrp;
} ItemMoveWork;

void MB1Ev_ItemMove(void) {
    f32 sp10[2];
    ItemMoveWork *work;
    f32 stepX;
    f32 stepY;
    s32 i;

    work = HuPrcCurrentGet()->user_data;
    stepX = (f32)(work->endX - work->startX) / work->frames;
    stepY = (f32)(work->endY - work->startY) / work->frames;

    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &sp10[0], &sp10[1]);

    for (i = 1; i <= work->frames; i++) {
        if (work->sprGrp != -1) {
            HuSprPosSet(work->sprGrp, 0, work->startX + (stepX * i), work->startY + (stepY * i));
        }
        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                           (stepX * i) + sp10[0],
                           (stepY * i) + sp10[1]);
        HuPrcVSleep();
    }

    if (work->sprGrp != -1) {
        HuSprPosSet(work->sprGrp, 0, work->endX, work->endY);
    }
    MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                       (work->endX + sp10[0]) - work->startX,
                       (work->endY + sp10[1]) - work->startY);
    omDelPrcObj(NULL);
}


Process* MB1Ev_ItemMoveCreate(s32 sprGrp, s16 startX, s16 startY, s16 endX, s16 endY, s16 frames) {
    Process* temp_v0;
    ItemMoveWork* temp_v0_2;

    temp_v0 = omAddPrcObj(MB1Ev_ItemMove, 0x4002, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, 0x10);
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->startX = startX;
    temp_v0_2->startY = startY;
    temp_v0_2->endX = endX;
    temp_v0_2->endY = endY;

    if (frames == -1) {
        frames = 25;
    }

    temp_v0_2->frames = frames;
    temp_v0_2->sprGrp = sprGrp;
    return temp_v0;
}


// ItemFunctions[IFUNC_MUSHROOM]
void MB1Ev_ItemKinoko(void) {
    f32 sp18[2];
    Process *process;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp18[0], &sp18[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MB1Ev_ItemMoveCreate(mbItemCursorGrpId, sp18[0], sp18[1], mb1ev_itemUsePosTbl[system->current_player_index][0], mb1ev_itemUsePosTbl[GwSystem.current_player_index][1], -1));
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), (255 - (i * 25)));
        MBStatusItemOfsApply(system->current_player_index, MBItemSelNoGet(), 0, 2.0f);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBPlayerMotionSet(-1, 5, 0);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(50);
    MBPlayerMotionSet(-1, -1, 2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB1Ev_ItemUseFadeOut(void) {
    GW_SYSTEM* system = &GwSystem;
    f32 sp18[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp18[0], &sp18[1]);
    MB1Ev_ItemMoveCreate(mbItemCursorGrpId, sp18[0], sp18[1], mb1ev_itemFadePosTbl[system->current_player_index][0], mb1ev_itemFadePosTbl[system->current_player_index][1], -1);
    HuPrcSleep(0x14);
    for (i = 1; i < 10; i++, HuPrcVSleep()) {
        MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 255 - (i * 25));
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
    }

    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuPrcSleep(2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB1Ev_ItemCursorReturn(void) {
    f32 sp18[2];
    s32 sp20;
    s32 sp24;
    Process* temp_s0;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1U, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &sp18[0], &sp18[1]);
    MBStatusItemPosGet(-1, MBItemSelNoGet(), &sp20, &sp24);
    temp_s0 = HuPrcCurrentGet();
    HuPrcChildLink(temp_s0, MB1Ev_ItemMoveCreate(mbItemCursorGrpId, sp18[0], sp18[1], sp20, sp24, -1));
    HuPrcChildWatch();
    for (i = 1; i < 10; i++, HuPrcVSleep()) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
    }
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB1Ev_ItemShake(void) {
    f32 sp18[2];
    Process* temp_s0;
    s32 var_s1_2;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp18[0], &sp18[1]);

    temp_s0 = HuPrcCurrentGet();
    HuPrcChildLink(temp_s0,
        MB1Ev_ItemMoveCreate(mbItemCursorGrpId,sp18[0], sp18[1],
        mb1ev_itemUsePosTbl[system->current_player_index][0],
        mb1ev_itemUsePosTbl[system->current_player_index][1],
        -1
        )
    );
    HuPrcChildWatch();
    HuPrcSleep(0xA);

    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 10; i++, HuPrcVSleep()) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, (255 - (i * 25)));
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);

    if ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == ITEM_BOO_BELL) ||
        ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == ITEM_DUEL_GLOVE))) {
        HuAudFXPlay(0x141);
    }

    for (i = 0; i <= (30 * 36); i += 30) {
        MBStatusItemRotSet(system->current_player_index, MBItemSelNoGet(), sindf((f32)i) * 30.0f);
        HuPrcVSleep();
        
    }

    for (var_s1_2 = 1; var_s1_2 < 10; var_s1_2++, i += 30, HuPrcVSleep()) {
        MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), (255 - (var_s1_2 * 25)));
        MBStatusItemRotSet(system->current_player_index, MBItemSelNoGet(), sindf((f32)i) * 30.0f);
    }

    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB1Ev_ItemPhoneMove(void) {
    f32 sp18[2];
    Process* proc;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp18[0], &sp18[1]);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MB1Ev_ItemMoveCreate(mbItemCursorGrpId, sp18[0], sp18[1], mb1ev_itemUsePosTbl[GwSystem.current_player_index][0], mb1ev_itemUsePosTbl[GwSystem.current_player_index][1], -1));
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    
    for (i = 1; i < 0xA; i++, HuPrcVSleep()) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, (255 - (i * 25)));
    }
    
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void MB1Ev_ItemIconMove(s32 arg0, s32 arg1, s32 arg2, f32* arg3, s32 arg4) {
    f32 sp10[2];
    f32 temp_f20;
    f32 temp_f22;
    s32 i;


    if (arg4 == 2) {
        HuAudFXPlay(0x145);
    }

    MBStatusItemSprPosGet(arg0, arg1, &sp10[0], &sp10[1]);
    temp_f22 = (arg3[0] - sp10[0]) / arg2;
    temp_f20 = (arg3[1] - sp10[1]) / arg2;

    
    for (i = 2; arg2 != 0; arg2--, HuPrcVSleep(), i++) {
        sp10[0] += temp_f22;
        sp10[1] += temp_f20;
        MBStatusItemPosSet(arg0, arg1, sp10[0], sp10[1]);
        if ((arg4 == 1) & (i < 0xB)) {
            MBStatusItemTPLvlSet(arg0, arg1, (i * 25));
            MBStatusItemScaleSet(arg0, arg1, (i * 0.07f + 0.3f), (i * 0.07f + 0.3));
        }
    }
    
    MBStatusItemPosSet(arg0, arg1, arg3[0], arg3[1]);

    if (arg4 == 0) {
        for (i = 1; i < 10; i++, HuPrcVSleep()) {
            MBStatusItemTPLvlSet(arg0, arg1, (255 - (i * 25)));
            MBStatusItemScaleSet(arg0, arg1, (1.0f - i * 0.1f), (1.0f - i * 0.1f));
        }
        MBStatusItemTPLvlSet(arg0, arg1, 0);
    }
}

void MB1Ev_KSuitStart(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);
    Object* obj;
    f32 var_f20;
    f32 var_f22;

    MBKSuitCreate();
    MBModelDispOff(mbKSuitMdl);
    mbKSuitMdl->omObj1->scale.x = 0.0f;
    mbKSuitMdl->omObj1->scale.y = 0.0f;
    mbKSuitMdl->omObj1->scale.z = 0.0f;
    MBPlayerVibrate(-1, 3);
    HuAudFXPlay(0x143);
    obj = MBModelCreate(0x22U, NULL);
    Hu3DModelAttrSet(obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);

    for (var_f22 = 0.0f, var_f20 = 1.0f; var_f20 < 10.0f; var_f22 += 20.0f, HuPrcVSleep(), var_f20 += 0.5) {
        HuVecCopyXYZ(&obj->scale, var_f20, var_f20, var_f20);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, var_f22);
    }
    
    MBModelDispOff(player->player_obj);
    MBModelDispOn(mbKSuitMdl);

    for (; var_f20 >= 1.0f; var_f22 += 20.0f, HuPrcVSleep(), var_f20 -= 0.5) {
        HuVecCopyXYZ(&obj->scale, var_f20, var_f20, var_f20);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, var_f22);
    }

    MBModelKill(obj);
    HuPrcSleep(0x14);
    PlayerFXPlay(0x274, GwSystem.current_player_index);
    MBKSuitMotionSet(5, 2);
    HuPrcSleep(0x28);
    MBKSuitMotionSet(-1, 2);
    MBDlgResultWinExec(0x3A14);
}


void MB1Ev_KSuitEnd(void) {
    GW_PLAYER* player = MBPlayerGet(CUR_PLAYER);
    Vec sp10;
    Object* obj;
    Vec* temp_a2;
    f32 var_f20;
    f32 var_f22;

    MBKSuitMotionSet(-1, 2);
    MBVecForwardSet(&sp10);
    MBVecRotLerpCreate(&player->player_obj->rot, &sp10, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    HuAudFXPlay(0x143);
    obj = MBModelCreate(0x22U, NULL);
    Hu3DModelAttrSet(obj->omObj1->model[0], HU3D_ATTR_ZBUF_MASK, HU3D_ATTR_ZBUF_OFF);
    Hu3DModelLayerSet(obj->omObj1->model[0], 0x1800U);
    Hu3DModelRemakeStatic(obj->omObj1->model[0]);
    HuVecCopy3F(&obj->coords, &player->player_obj->coords);

    for (var_f22 = 0.0f, var_f20 = 1.0f; var_f20 < 10.0f; var_f22 += 20.0f, HuPrcVSleep(), var_f20 += 0.5) {
        HuVecCopyXYZ(&obj->scale, var_f20, var_f20, var_f20);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, var_f22);
    }
    
    MBModelDispOn(player->player_obj);
    MBKSuitKill();
    
    for (; var_f20 >= 1.0f; var_f22 += 20.0f, HuPrcVSleep(), var_f20 -= 0.5) {
        HuVecCopyXYZ(&obj->scale, var_f20, var_f20, var_f20);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, var_f22);
    }
    MBModelKill(obj);
}

void MB1Ev_ItemPhoneWaveProc(void) {
    f32 sp18[2];
    UnkVibrateProcess* temp_s3;
    f32 temp_f20;
    s32 temp_v0;
    s32 temp_s1;
    s32 i;

    temp_s1 = (s32)HuPrcCurrentGet()->user_data;
    temp_s3 = MBPlayerVibrateObjCreate(-1, 1, 5);
    temp_v0 = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(temp_v0, 0, mb1ev_itemPhoneWaveSpr, 0);
    HuSprPriSet(temp_v0, 0, 0x4780);
    HuSprAttrSet(temp_v0, 0, HUSPR_ATTR_XLU);
    MBStatusItemSprPosGet(GwSystem.current_player_index, MBItemSelNoGet(), &sp18[0], &sp18[1]);
    sp18[0] += 20.0f;
    sp18[1] -= 20.0f;
    HuSprPosSet(temp_v0, 0, sp18[0], sp18[1]);
    HuSprColorSet(temp_v0, 0, 0xFF, 0xFF, 0);

    for (i = 255, temp_f20 = mb1ev_itemPhoneWaveAngleTbl[temp_s1]; i >= 0; i -= 20, HuPrcVSleep()) {
        sp18[0] += (cosdf(temp_f20) * 5.0f);
        sp18[1] -= (sindf(temp_f20) * 5.0f);
        HuSprPosSet(temp_v0, 0, sp18[0], sp18[1]);
        HuSprTPLvlSet(temp_v0, 0, i);
    }

    HuSprTPLvlSet(temp_v0, 0, 0);
    MBPlayerVibrateObjKill(temp_s3);
    HuSprGrpKill(temp_v0);
    omDelPrcObj(NULL);
}

void MB1Ev_ItemShopPhone(void) {
    Process *proc;
    void *file;
    s32 sel;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    file = DataRead(0x1301B8);
    mb1ev_itemPhoneWaveSpr = HuSprAnimRead(file);
    DataClose(file);
    MB1Ev_ItemPhoneMove();
    
    label:
    MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
    sel = MB1Ev_YesNoChoiceGet(mb1ev_shopPhoneComTree, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch (sel) {
    case 0:
    case 1:
        GwSystem.forceShopHost = sel + 1;
        break;
    default:
        proc = omAddPrcObj(MB1Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(proc, OM_STAT_NOALLPAUSE); MB1_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
        omDelPrcObj(proc);
        MBTurnHelpKill();
        goto label;
    }

    HuPrcSleep(30);
    HuAudFXPlay(0x147);

    for (i = 0; i < 5; i++) {
        proc = omAddPrcObj(MB1Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        proc->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    for (i = 0; i < 5; i++) {
        proc = omAddPrcObj(MB1Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        proc->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    HuSprAnimKill(mb1ev_itemPhoneWaveSpr);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);

    if (sel != 0) {
        HuAudFXPlay(0x2A0);
    } else if (GwPlayer[system->current_player_index].coin < 5 || system->current_turn == system->total_turns) {
        HuAudFXPlay(0x29A);
    } else {
        HuAudFXPlay(0x298);
    }

    MB1Ev_ShopMasu();
    GwSystem.forceShopHost = 0;
}

void MB1Ev_ItemKoopaPhone(void) {
    Process *proc;
    void *file;
    DecisionTreeNonLeafNode *tree;
    s32 arg;
    s32 sel;
    s32 mesNum;
    s32 insert;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    file = DataRead(0x1301B8);
    mb1ev_itemPhoneWaveSpr = HuSprAnimRead(file);
    DataClose(file);

    MB1Ev_ItemPhoneMove();
    HuPrcSleep(30);
    HuAudFXPlay(0x147);

    for (i = 0; i < 5; i++) {
        proc = omAddPrcObj(MB1Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        proc->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);

    for (i = 0; i < 5; i++) {
        proc = omAddPrcObj(MB1Ev_ItemPhoneWaveProc, 0x4002, 0, 0);
        proc->user_data = (void *)i;
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcSleep(3);
    }
    HuPrcChildWatch();
    HuPrcSleep(20);
    HuAudFXPlay(0x29F);


    choiceLoop:
    MBDlgWinInsertCreate(4, 0x3A0A,
                         mbCharNameMesTbl[GwPlayer[0].chr],
                         mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr],
                         mbCharNameMesTbl[GwPlayer[3].chr], 0);

    if (GwPlayer[system->current_player_index].coin != 0) {
        sel = MB1Ev_YesNoChoiceGet((DecisionTreeNonLeafNode *)1, 0);
    } else {
        sel = MB1Ev_YesNoChoiceGet((DecisionTreeNonLeafNode *)2, system->current_player_index);
    }
    
    MBDlgWinClose();
    MBDlgWinKill();

    switch (sel) {
    case 4:
        sel = MBPlayerRankRandGet(0);
        MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
        break;
    case 5:
        proc = omAddPrcObj(MB1Ev_ItemSelAttrProc, 0, 0, 0);
        omPrcSetStatBit(proc, OM_STAT_NOALLPAUSE);
        MB1_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
        omDelPrcObj(proc);
        MBTurnHelpKill();
        goto choiceLoop;
    default:
        MBDlgWinInsertCreate(4, 0x3A0B, mbCharNameMesTbl[GwPlayer[sel].chr], 0, 0, 0, 0);
        break;
    }
    
    MBDlgWinClose();
    MBDlgWinKill();
    HuAudFXPlay(0x29C);

    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    HuSprAnimKill(mb1ev_itemPhoneWaveSpr);

    if (MBSaiTypeGet(system->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }

    GwSystem.playerIndexVisitingBowser = sel;
    MBGameModeKoopaSet();
    MBExitOvlCallEx(0x50, 0, 3, 1);
    MBTurnHelpKill();
    MBExitReq(2);
    omAllUPause();
    HuPrcSleep(-1);
}

void MB1Ev_ItemStarYoke(void) {
    Vec dir;
    Vec pos;
    Vec starPos;
    UnkVibrateProcess *vib;
    GW_PLAYER *player;
    Object *star;
    Object *lamp;
    Object *starMdl;
    Process *proc;
    Process *shake;
    SpaceData *guideSpace;
    SpaceData *starSpace;
    f32 y;
    f32 scale;
    f32 spin;
    s32 alpha;
    s32 angle;
    s32 i, j;
    s32 wiped;
    s32 flagged;
    GW_SYSTEM* system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    star = MBModelCreate(0x3C, NULL);
    MBMotionSet(star, -1, 1);
    Hu3DModelScaleSet(star->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&star->coords, &player->player_obj->coords);
    star->velocity.x = 30.0f;
    star->flags |= 1;
    HuVecCopyXYZ(&star->scale, 0.0f, 0.0f, 0.0f);
    MBModelDispOff(star);

    MB1Ev_ItemUseFadeOut();
    GwPlayer[system->current_player_index].itemNo[MBItemFind(CUR_PLAYER, ITEM_LUCKY_LAMP)] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);

    lamp = MBModelCreate(0x3D, NULL);
    Hu3DModelTPLvlInit(lamp->omObj1->model[0]);
    Hu3DModelTPLvlSet(lamp->omObj1->model[0], 0xFF);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);

    lamp->coords.y = 100.0f;
    while (lamp->coords.y > 30.0f) {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x127);
    msmMusFadeOut(HuAudMusNo, 0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 3, 5);

    for (angle = 0xB4, i = 0; angle < 0x438; ) {
        Vec particleDir[8] = {
            {1.0f, 1.0f, 1.0f,},
            {1.0f, 2.0f, 1.0f},
            {0.0f, 2.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {0.0f, -1.0f, 1.0f},
            {-1.0f, 2.0f, 1.0f},
            {1.0f, -1.0f, 1.0f}
        };
        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB1Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 1);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    alpha = 0xFF;
    scale = 0.0f;
    while (1) {
        Vec particleDir2[8] = {
            {1.0f, 1.0f, 1.0f,},
            {1.0f, 2.0f, 1.0f},
            {0.0f, 2.0f, 1.0f},
            {-1.0f, 1.0f, 1.0f},
            {-1.0f, -1.0f, 1.0f},
            {0.0f, -1.0f, 1.0f},
            {-1.0f, 2.0f, 1.0f},
            {1.0f, -1.0f, 1.0f}
        };
        
        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            MB1Ev_ItemLampSmokeCreate(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 1);
        }

        if (alpha <= 0) {
            MBModelDispOff(lamp);
            MBModelDispFlagSet(star);
            scale += 0.1f;
            star->scale.z = scale;
            star->scale.y = scale;
            star->scale.x = scale;        
            if (1.0f < scale) {
                HuAudSeqPlay(0x3D);
                break;
            }
        } else {
            Hu3DModelTPLvlSet(lamp->omObj1->model[0], alpha);
            alpha -= 0xC;
        }
    
        i++;
        HuPrcVSleep();
    }

    
    star->scale.z = 1.0f;
    star->scale.y = 1.0f;
    star->scale.x = 1.0f;
    shake = MBModelHoverCreate(star, 3.0f, 2.0f);
    MBPlayerVibrateObjKill(vib);
    HuPrcSleep(30);
    MBDlgWinExec(0x3C, 0x3A2F);
    omDelPrcObj(shake);

    wiped = 1;
    star->coords.y -= star->velocity.x;
    HuVecSubtract(&dir, &gCameraList->pos, &star->coords);
    MBVecNormalize(&dir);
    star->coords.y += star->velocity.x;
    while (star->velocity.x < 1800.0f) {
        star->coords.x += dir.x * 40.2f;
        star->velocity.x += dir.y * 40.0f;
        star->coords.z += dir.z * 40.2f;
        if ((star->velocity.x > 300.0f) & (wiped != 0)) {
            wiped = 0;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(WIPE_FADE, 0x32);
            HuAudFXPlay(0x128);
        }
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    starSpace = MBMasuGet(mb1ev_starMasu[system->star_spawn_indices[system->current_star_spawn]]);
    guideSpace = MBMasuGet(mb1ev_starGuideMasu[system->star_spawn_indices[system->current_star_spawn]]);
    HuVecCopy3F(&starPos, &starSpace->coords);
    MBCameraPos3DSet(&starPos);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&starPos);
    star->flags &= ~1;
    HuVecCopy3F(&star->coords, &starSpace->coords);
    HuVecSubtract(&dir, &guideSpace->coords, &starSpace->coords);
    MBVecNormalize(&dir);
    star->coords.x -= dir.x * 20.0f;
    star->coords.z -= dir.z * 20.0f;
    HuAudFXPlay(0x129);
    WipeCreateIn(WIPE_FADE, 0x32);

    for (star->velocity.x = 100.0f; star->velocity.x > 30.0f; star->velocity.x -= 3.0f) {
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBVecRotLerpCreate(&star->rot, &dir, &star->rot, 0x10));
    HuPrcChildWatch();

    shake = MBModelHoverCreate(star, 3.0f, 2.0f);
    MBDlgWinExec(0x3C, 0x3A30);
    HuAudFXPlay(0x12C);
    MBMotionSet(star, -1, 0);
    HuPrcSleep(20);

    
    for (flagged = 1, j = 0; j < 8; j++) {
        if (mb1_starGuideHoverProc[j] != NULL) {
            omDelPrcObj(mb1_starGuideHoverProc[j]);
            mb1_starGuideHoverProc[j] = NULL;
        }
    }

    starMdl = mb1_starGuideMdl[system->star_spawn_indices[system->current_star_spawn]];
    HuAudSeqFadeOut(0x5A);
    spin = 0.0f;
    while (starMdl->velocity.x < 400.0f) {
        starMdl->velocity.x += 3.0f;
        starMdl->coords.x += dir.x * 3.0f;
        starMdl->coords.z += dir.z * 3.0f;
        starMdl->rot.x = -sindf(spin);
        starMdl->rot.z = cosdf(spin);
        spin += 45.0f;
        if (spin > 360.0f) {
            spin -= 360.0f;
        }
        if ((starMdl->velocity.x > 50.0f) & (flagged != 0)) {
            if (MBSaiTypeGet(system->current_player_index) == 3) {
                GWBoardFlagSet(0x17);
            } else {
                GWBoardFlagClear(0x17);
            }
            flagged = 0;
            WipeColorSet(0, 0, 0);
            omDelPrcObj(shake);
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

Process* MB1Ev_ItemMoveCreate(s32 sprGrp, s16 startX, s16 startY, s16 endX, s16 endY, s16 frames);
// ItemFunctions[IFUNC_KEYMAN] - throwing away a skeleton key
void MB1Ev_ItemKeyManUse(void) {
    f32 sp20[2];
    Process *proc;
    void *file;
    s32 grpId;
    s32 sprId;
    s32 ret;
    s32 i;
    GW_SYSTEM* system = &GwSystem;
    s32 curPlayer = GwSystem.current_player_index;

    grpId = HuSprGrpCreate(1, 0);
    file = DataRead(mbItemIconSprTbl[1]);
    sprId = HuSprAnimRead(file);
    DataClose(file);
    HuSprGrpMemberSet(grpId, 0, sprId, 0);
    HuSprPriSet(grpId, 0, 0x4780);
    HuSprAttrSet(grpId, 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuPrcSleep(0x14);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &sp20[0], &sp20[1]);

    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc,
        MB1Ev_ItemMoveCreate(mbItemCursorGrpId, sp20[0], sp20[1],
                             mb1ev_itemUsePosTbl[system->current_player_index][0],
                             mb1ev_itemUsePosTbl[system->current_player_index][1],
                             -1));
    HuPrcChildWatch();
    HuPrcSleep(0xA);

    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);

    for (i = 1; i < 0xA; i++, HuPrcVSleep()) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, (255 - (i * 25)));
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);

    GwPlayer[curPlayer].itemNo[MBItemSelNoGet()] = ITEM_NONE;
    MBStatusItemTPLvlSet(curPlayer, MBItemSelNoGet(), 0);
    MBStatusItemSprPosGet(curPlayer, MBItemSelNoGet(), &sp20[0], &sp20[1]);
    HuSprPosSet(grpId, 0, sp20[0], sp20[1]);
    HuSprDispOn(grpId, 0);
    MBItemRemoveEmpty(curPlayer);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

choiceLoop:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    ret = MB1Ev_YesNoChoiceGet(&mb1ev_keyManUseComTree, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch (ret) {
    case 0:
        MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
        break;
    case 1:
        MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
        HuSprDispOff(grpId, 0);
        GwPlayer[curPlayer].itemNo[MBItemFindEmpty(curPlayer)] = ITEM_SKELETON_KEY;
        MBItemRemoveEmpty(curPlayer);
        GwSystem.cur_player_used_item &= ~1;
        break;
    default:
        HuSprDispOff(grpId, 0);
        MB1_MapScrollCancel();
        winPauseF = 1;
        omAllPause();
        HuSprDispOn(grpId, 0);
        goto choiceLoop;
    }

    MBDlgWinClose();
    MBDlgWinKill();

    if (ret == 0) {
        HuPrcSleep(0xA);
        for (i = 1; i < 0x40; i++, HuPrcVSleep()) {
            HuSprTPLvlSet(grpId, 0, 255.0f - (i * 3.984f));
        }
        HuSprTPLvlSet(grpId, 0, 0);
    }

    HuSprGrpKill(grpId);
    HuSprAnimKill(sprId);
}

void MB1Ev_TereYokeSparkProc(void) {
    s32 x;
    s32 y;
    s32 grpId;
    s32 idx;
    f32 scale;
    s32 alpha;

    idx = (s32)HuPrcCurrentGet()->user_data;

    grpId = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(grpId, 0, mb1ev_tereYokeSparkSpr, 0);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, HUSPR_ATTR_XLU);

    MBStatusItemPosGet(mb1ev_tereYokePlayer, 0, &x, &y);
    x = (mb1ev_teresaSprDirTbl[mb1ev_tereYokePlayer][0] * 16.0f) +
         mb1ev_teresaSprPosTbl[mb1ev_tereYokePlayer][0];
    y = (mb1ev_teresaSprDirTbl[mb1ev_tereYokePlayer][1] * 16.0f) +
         mb1ev_teresaSprPosTbl[mb1ev_tereYokePlayer][1];

    HuSprPosSet(grpId, 0,
                        x + mb1ev_tereYokeSparkOfsTbl[idx][0],
                        y + mb1ev_tereYokeSparkOfsTbl[idx][1]);
    HuSprColorSet(grpId, 0, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(grpId, 0, 0xFF);

    for (scale = 0.0f, alpha = 0xFF; alpha >= 0; alpha -= 0xA, scale += 0.1f) {
        HuSprScaleSet(grpId, 0, scale, scale);
        HuSprTPLvlSet(grpId, 0, alpha);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(grpId, 0, 0);
    HuSprGrpKill(grpId);
    omDelPrcObj(NULL);
}

void MB1Ev_TereYokeSprayProc(void) {
    Process *proc;
    void *file;
    s32 grpId;
    s32 charmSpr;
    s32 booSpr;
    s32 sfx;
    s32 x;
    s32 startX;
    s32 playerNo;
    s32 y;
    s32 i;
    s32 j;
    s32 alpha;

    playerNo = (s32)HuPrcCurrentGet()->user_data;

    file = DataRead(0x21002C);
    booSpr = HuSprAnimRead(file);
    DataClose(file);
    file = DataRead(0x1301BA);
    charmSpr = HuSprAnimRead(file);
    DataClose(file);
    file = DataRead(0x1301B9);
    mb1ev_tereYokeSparkSpr = HuSprAnimRead(file);
    DataClose(file);

    grpId = HuSprGrpCreate(2, 2);
    HuSprAnimModeSet(grpId, 0, HUSPR_ANIM_MODE_BANK);
    HuSprGrpMemberSet(grpId, 0, booSpr, 0xC);
    HuSprPriSet(grpId, 0, 9);
    HuSprAttrSet(grpId, 0, HUSPR_ATTR_XLU);
    HuSprParentSet(grpId, 0, -1);
    HuSprGrpMemberSet(grpId, 1, charmSpr, 0);
    HuSprPriSet(grpId, 1, 9);
    HuSprAttrSet(grpId, 1, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU);
    HuSprColorSet(grpId, 1, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(grpId, 1, 0xFF);
    HuSprScaleSet(grpId, 1, 2.0f, 2.0f);
    HuSprParentSet(grpId, 1, 0);

    if (playerNo & 1) {
        x = 0xC8;
        HuSprAttrSet(grpId, 0, HUSPR_ATTR_FLIPX);
        HuSprAttrSet(grpId, 1, HUSPR_ATTR_FLIPX);
        HuSprPosSet(grpId, 1, 0x14, -5);
    } else {
        x = 0x78;
        HuSprPosSet(grpId, 1, -0x14, -5);
    }
    

    if (playerNo < 2) {
        y = -0x20;
    } else {
        y = 0x110;
    }

    HuPrcSleep(0x14);
    GwPlayer[playerNo].itemNo[MBItemFind(playerNo, ITEM_BOO_REPELLENT)] = ITEM_NONE;
    MBItemRemoveEmpty(playerNo);
    MBStatusItemIconSprReinit(playerNo);

    //TODO: this sure is some cod...
    while (1) {
        if (playerNo < 2) {
            y += 5;
            if (y > 50) {
                break;
            }
        } else {
            y -= 5;
            if (y < 210) {
                break;
            }
        }
        loop:
        HuSprPosSet(grpId, 0, x, y);
        HuPrcVSleep();
    
        if (playerNo < 2) {
            y += 5;
            if (y < 51) {
                goto loop;
            }
            break;
        }
    }

    HuPrcSleep(0xA);
    HuSprDispOn(grpId, 1);
    sfx = HuAudFXPlay(0x14C);
    mb1ev_tereYokePlayer = playerNo;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            proc = omAddPrcObj(MB1Ev_TereYokeSparkProc, 0x4002, 0, 0);
            proc->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), proc);
    HuPrcChildWatch();
    HuAudFXStop(sfx);
    HuSprTPLvlSet(grpId, 1, 0);

    for (alpha = 0xFF; alpha >= 0; alpha -= 30) {
        HuSprTPLvlSet(grpId, 0, alpha);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(grpId, 0, 0);
    HuSprGrpKill(grpId);
    HuSprAnimKill(mb1ev_tereYokeSparkSpr);
    HuSprAnimKill(charmSpr);
    HuSprAnimKill(booSpr);
    omDelPrcObj(NULL);
}

void MB1Ev_ItemNullUse() {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void MB1Ev_KoopaCardCoinProc(void) {
    Object* modelObj;
    f32 angle;
    Object* obj;

    obj = HuPrcCurrentGet()->user_data;
    modelObj = MBModelLinkCreate(mb1ev_koopaCardCoinMdl);
    HuVecCopy3F(&modelObj->coords, &obj->coords);
    HuVecCopyXYZ(&modelObj->scale, 2.0f, 2.0f, 2.0f);
    modelObj->velocity.x = obj->velocity.x + 10.0f;
    MBModelDispOn(modelObj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        modelObj->velocity.x += 1.5;
        if ((obj->velocity.x + 35.0f) <= modelObj->velocity.x) {
            break;
        }
        angle += 40.0f;
        HuMtxRotYF(Hu3DData[modelObj->omObj1->model[0]].mtx, angle);
    }

    MBModelKill(modelObj);
    omDelPrcObj(NULL);
}


void MB1Ev_KoopaCardCoinCreate(Object* arg0) {
    omAddPrcObj(MB1Ev_KoopaCardCoinProc, 0x1000, 0, 0)->user_data = arg0;
}

void MB1Ev_KoopaCardSpinProc(void) {
    s32 *done = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *system = &GwSystem;

    while (1) {
        mb1ev_koopaCardMdl->rot.x = -sindf(angle);
        mb1ev_koopaCardMdl->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }

        if (*done != 0) {
            mb1ev_koopaCardMdl->scale.x =
            mb1ev_koopaCardMdl->scale.y =
            mb1ev_koopaCardMdl->scale.z = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    mb1ev_koopaCardMdl->scale.x =
    mb1ev_koopaCardMdl->scale.y =
    mb1ev_koopaCardMdl->scale.z = 0.0f;
    GwPlayer[system->current_player_index].itemNo[MBItemFind(CUR_PLAYER, ITEM_KOOPA_KARD)] = ITEM_NONE;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBModelKill(mb1ev_koopaCardMdl);
    omDelPrcObj(NULL);
}

extern Object *mb1ev_koopaCardCoinMdl;
extern Object *mb1ev_koopaCardMdl;
void MB1Ev_KoopaCardCoinCreate(Object *);

void MB1Ev_BankKoopaCardExec(void) {
    s32 pos[2];
    UnkVibrateProcess *vib;
    Object *coin;
    void *file;
    s32 sprId;
    s32 amount;
    s32 n;
    f32 step;
    f32 frac;
    s32 done = 0;
    GW_SYSTEM *system = &GwSystem;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    file = DataRead(mbItemCharSprTbl[GwPlayer[system->current_player_index].chr]);
    sprId = HuSprAnimRead(file);
    DataClose(file);
    HuSprGrpMemberSet(mbItemCursorGrpId, 0, sprId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 0xA);
    HuSprAnimModeSet(mbItemCursorGrpId, 0, HUSPR_ANIM_MODE_BANK);
    HuSprDispOff(mbItemCursorGrpId, 0);
    MBStatusItemPosGet(-1, 0, &pos[0], &pos[1]);
    HuSprPosSet(mbItemCursorGrpId, 0, pos[0], pos[1]);

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(CUR_PLAYER, 0xF));
    MB1Ev_ItemUseFadeOut();

    mb1ev_koopaCardMdl = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&mb1ev_koopaCardMdl->coords,
                &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    mb1ev_koopaCardMdl->velocity.x = 100.0f;
    while (mb1ev_koopaCardMdl->velocity.x > 30.0f) {
        mb1ev_koopaCardMdl->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(MB1Ev_KoopaCardSpinProc, 0x4002, 0, 0)->user_data = &done;
    vib = MBPlayerVibrateObjCreate(-1, 4, 5);

    amount = GwSystem.bank_coins;
    step = (f32)amount / 30.0f;
    frac = 0.0f;
    coin = MBModelCreate(0x19, NULL);
    mb1ev_koopaCardCoinMdl = coin;
    MBModelTempAllocFree(coin);
    MBModelDispOff(mb1ev_koopaCardCoinMdl);

    while (amount != 0) {
        frac += step;
        n = 0;
        while (frac >= 1.0f) {
            frac -= 1.0f;
            n++;
        }
        if (n != 0) {
            MB1Ev_KoopaCardCoinCreate(mb1ev_koopaCardMdl);
            if ((amount - n) < 0) {
                n = amount;
            }
            amount -= n;
            MBPlayerCoinAdd(system->current_player_index, n);
            HuAudFXPlay(0x106);
            GwSystem.bank_coins -= n;
            MB1_BankCoinHide();
            HuPrcSleep(5);
        }
    }

    MBPlayerVibrateObjKill(vib);
    done = 1;
    HuPrcSleep(0x14);
    MBModelKill(mb1ev_koopaCardCoinMdl);
    MBVecForwardSet(&MBPlayerGet(CUR_PLAYER)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

s32 MB1_ComItemTargetChoice(u8 *arg0, s32 arg1) {
    s32 count = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS] = {1, 2, 4, 8};
    s32 i;
    s32 j;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & PLAYER_IS_CPU) {
                if (arg1 != 0) {
                    count = mb1_comExchangeBoxTarget + 1;
                } else {
                    count = mb1_comRobBoxTarget + 1;
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

    if (count != 0) {
        HuWinAttrSet(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; count != 0; j++) {
            if (--count == 0) {
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
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void MB1Ev_ExchangeItemFadeOutProc(void) {
    Process *proc;
    s32 playerNo;
    s32 alpha;
    s32 i;

    proc = HuPrcCurrentGet();
    playerNo = (s32)proc->user_data;
    MBPlayerVibrate(playerNo, 4);

    for (alpha = 0x80; alpha > 0; alpha -= 0xA, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
                MBStatusItemTPLvlSet(playerNo, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[playerNo].itemNo[i] != ITEM_NONE) {
            MBStatusItemTPLvlSet(playerNo, i, 0);
        }
    }

    omDelPrcObj(NULL);
}

void MB1Ev_ExchangeItemFadeInProc(void) {
    s32 pos[2];
    s32 alpha;
    s32 i;
    s32 slot;
    s32 playerNo = (s32)HuPrcCurrentGet()->user_data;
    GW_SYSTEM* system = &GwSystem;

    for (i = 0, slot = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerNo, slot, &pos[0], &pos[1]);
            MBStatusItemPosSet(system->current_player_index, i, pos[0], pos[1]);
            slot += i != MBItemSelNoGet();
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14, HuPrcVSleep()) {
        for (i = 0; i < 3; i++) {
            if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
                (i != MBItemSelNoGet())) {
                MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
            }
        }
    }

    for (i = 0; i < 3; i++) {
        if ((GwPlayer[system->current_player_index].itemNo[i] != ITEM_NONE) &&
            (i != MBItemSelNoGet())) {
            MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
        }
    }

    omDelPrcObj(NULL);
}

void MB1Ev_ItemExchangeBox(void) {
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

    MB1Ev_ItemUseFadeOut();
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
    targetPlayer = MB1_ComItemTargetChoice(choices, 1);
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
                    MB1Ev_ItemIconMove(system->current_player_index, itemSlot, 10, &position.x, 0);
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
        process = omAddPrcObj(MB1Ev_ExchangeItemFadeOutProc, 0x4800, 0, 0);
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
        process = omAddPrcObj(MB1Ev_ExchangeItemFadeInProc, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB1Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB1Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB1Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                MB1Ev_ItemIconMove(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                MB1Ev_ItemIconMove(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                MB1Ev_ItemIconMove(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                MB1Ev_ItemIconMove(targetPlayer, 2, 7, &target.x, 2);
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

void MB1Ev_GambleCoinEffProc(void) {
    Object* temp_s1;
    Object* temp_s0;
    UnkThing* temp_s2;

    temp_s2 = HuPrcCurrentGet()->user_data;
    temp_s1 = temp_s2->unk_00;
    temp_s0 = temp_s2->unk_04;
    MBMotionSet(temp_s1, -1, temp_s2->unk_08);
    HuVecCopy3F(&temp_s1->coords, &temp_s0->coords);
    temp_s1->coords.y += temp_s0->velocity.x - 10.0f;
    MBModelDispFlagSet(temp_s1);
    while (!(MBMotionCheck(temp_s1)) && (temp_s2->unk_0C == 0)) {
        HuPrcVSleep();
    }
    MBModelKill(temp_s1);
    omDelPrcObj(NULL);
}

void MB1Ev_GambleCoinProc(void) {
    Object *coin;
    Object *obj;
    Process *proc;
    UnkThing *work;
    s32 *flag;
    s32 light;
    f32 angle;
    f32 speed;
    f32 decel;
    f32 scale;
    s32 i;

    flag = HuPrcCurrentGet()->user_data;
    coin = mb1ev_gambleCoinMdl;
    obj = MBModelCreate(0x45, NULL);
    MBModelDispOff(obj);

    light = EffectCreate(0xB0004, 0xAA9);
    EffectParamSet(light, 1.0f, 20.0f, 1.0f);
    EffectRangeSet(light, 10.0f);
    Hu3DModelCameraSet(light, HU3D_CAM0);
    HuAudFXPlay(0x24C);

    for (angle = 0.0f, speed = 2.0f; speed < 80.0f; HuPrcVSleep()) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        speed += 1.0f;
        if (speed > 80.0f) {
            speed = 80.0f;
        }
        EffectPosSet(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);        
    }

    HuAudFXPlay(0x14A);
    
    while (coin->velocity.x < 110.0f) {
        coin->velocity.x += 7.0f;
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        EffectPosSet(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    for (*flag = 0; *flag == 0; HuPrcVSleep()) {
        if (mb1ev_gambleCoinPlayer != -1) {
            HuVecCopy3F(&coin->coords,
                        &MBPlayerGet(mb1ev_gambleCoinPlayer)->player_obj->coords);
            EffectPosSet(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                               coin->coords.z);
        }        
    }

    HuAudFXPlay(0x14B);
    
    decel = 3.0f;
    while (coin->velocity.x > 30.0f) {
        coin->velocity.x -= decel;
        if (decel > 1.0f) {
            decel -= 0.2f;
        }
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        EffectPosSet(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        coin->rot.x = -sindf(angle);
        coin->rot.z = cosdf(angle);
        angle += speed;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (speed > 15.0f) {
            speed -= 3.0f;
        } else {
            speed -= 0.5f;
        }
        if (speed < 1.0f) {
            break;
        }
        EffectPosSet(light, coin->coords.x, coin->coords.y + coin->velocity.x,
                           coin->coords.z);
        HuPrcVSleep();
    }

    EffectStop(light);
    proc = omAddPrcObj(MB1Ev_GambleCoinEffProc, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(proc->heap, sizeof(UnkThing));
    proc->user_data = work;
    work->unk_00 = obj;
    work->unk_04 = coin;
    work->unk_08 = 0;
    work->unk_0C = 0;
    HuPrcSleep(3);

    *flag = 0;
    HuAudFXPlay(0x24D);
    
    for (i = 0, scale = 0.1f; i < 0x14; i++) {
        scale += 0.044999998f;
        Hu3DModelVtxWave(coin->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }

    MBModelKill(coin);
    omDelPrcObj(NULL);
}

void MB1Ev_ItemGambleCoin(void) {
    s32 sp20;
    GW_SYSTEM* system = &GwSystem;
    Object* temp_s3;
    Object* temp_v0;
    Object* temp_v0_2;
    Process* temp_s4;
    s32 temp_a0;
    s32 var_s1;
    s32 sel;
    s32 i;
    u32 var_v1_3;

    MB1Ev_ItemUseFadeOut();
    GwPlayer[system->current_player_index].itemNo[MBItemFind(-1, 0x11)] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    temp_v0 = MBModelCreate(0x3EU, NULL);
    Hu3DModelScaleSet(temp_v0->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    MBModelTempAllocFree(temp_v0);
    temp_v0->velocity.x = 30.0f;
    MBModelDispOff(temp_v0);
    temp_v0_2 = MBModelCreate(0x43U, NULL);
    mb1ev_gambleCoinMdl = temp_v0_2;
    Hu3DModelObjAttrSet(temp_v0_2->omObj1->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(temp_v0_2->omObj1->model[0]);
    Hu3DModelVtxBufMake(temp_v0_2->omObj1->model[0]);
    Hu3DModelDynamicFree(temp_v0_2->omObj1->model[0]);
    HuVecCopy3F(&temp_v0_2->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    Hu3DMotionAttrSet(temp_v0_2->omObj1->model[0], 2, 1);
    temp_v0_2->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (temp_v0_2->velocity.x > 30.0f) {
        temp_v0_2->velocity.x -= 1.0f;
        HuPrcVSleep();
    } 
loop:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00, GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    sel = MB1Ev_YesNoChoiceGet(NULL, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    switch(sel) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
        case 4:
            sel = MBPlayerRankRandGet(0);
            break;
        default:
            MB1_MapScrollCancel();
            winPauseF = 1;
            omAllPause();
            goto loop;
    }

    sp20 = 1;
    omAddPrcObj(MB1Ev_GambleCoinProc, 0x4002U, 0, 0)->user_data = &sp20;
    while(sp20) {
        HuPrcVSleep();
    }
    
    if (sel != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        mb1ev_gambleCoinPlayer = sel;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(sel)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(sel)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(0xA);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(0x1E);
        mb1ev_gambleCoinPlayer = sel;
    }
    sp20 = 1;
    while (sp20) {
        HuPrcVSleep();
    }
    
    temp_s3 = MBPlayerGet(sel)->player_obj;
    temp_s4 = MBModelHoverCreate(temp_v0, 5.0f, 2.0f);
    HuVecCopy3F(&temp_v0->coords, &temp_s3->coords);
    MBModelDispFlagSet(temp_v0);
    temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z = 0.0f;
    while (temp_v0->scale.x < 1.0f) {
        temp_v0->scale.x = temp_v0->scale.y = temp_v0->scale.z += 0.2f;
        HuPrcVSleep();
    }
    MBPlayerVibrate(sel, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[sel].coin != 0) {
        MB1Ev_WinPlayerKeyExec(0xA, 0x2F00, -1, sel);
        GwPlayer[sel].gameCoin = GwPlayer[sel].coin;
        MBCoinChangeCreate(sel, -GwPlayer[sel].coin);
        MBCoinTakeCreate(sel, -GwPlayer[sel].coin);
        HuPrcSleep(0x1E);
        MB1Ev_WinPlayerKeyExec(0xA, 0x2F02, -1, sel);
        omDelPrcObj(temp_s4);
        while(10.0f <= temp_v0->velocity.x) {
            temp_v0->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(0x1E);
        while (temp_v0->velocity.x < 100.0f) {
            temp_v0->velocity.x += 4.0f;
            temp_s3->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        MB1Ev_WinPlayerKeyExec(0xA, 0x2F01, -1, sel);
        omDelPrcObj(temp_s4);
            while (temp_v0->velocity.x <= 100.0f) {
                temp_v0->velocity.x += 4.0f;
                HuPrcVSleep();
            } 
        MBModelKill(temp_v0);
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        return;
    }
    
    if ((MBPlayerComCheck(sel) != 0) && (system->show_com_minigames != 0)) {
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(temp_v0);
        MBModelJumpSet(temp_s3, 0.0f, 0.0f);
        temp_s3->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        temp_a0 = MBRand(100.0f) + 1;
        for (i = 0; i < 7; i++) {
            if (mb1ev_gambleRateTbl[i][1] >= temp_a0) {
                break;
            }
        }
        if (mb1ev_gambleRateTbl[i][0] != 0) {
            char sp28[16]; // required to be here or the codegen changes(?!)
            
            var_s1 = GwPlayer[sel].gameCoin * mb1ev_gambleRateTbl[i][0];
            if (var_s1 >= 1000) {
                var_s1 = 999;
            }
            sprintf(sp28, mb1ev_numFmtStr, var_s1);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)sp28, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(sel, var_s1);
            MBCoinTakeCreate(sel, var_s1);
            HuPrcSleep(0x14);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(0xA);
        WipeCreateOut(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(WIPE_GAME_GUY, 0x10);
        HuPrcSleep(0x11);
    } else {
        if (MBSaiTypeGet(system->current_player_index) == 3) {
            GWBoardFlagSet(0x17);
        } else {
            GWBoardFlagClear(0x17);
        }
        for (i = 0; i < 4; i++) {
            GwPlayer[i].group = 1;
        }
        MBPlayerGet(sel)->group = 0;
        temp_a0 = MBRand(100.0f);
        for(var_v1_3 = 0; var_v1_3 < 3; var_v1_3++) {
            if (temp_a0 < mb1ev_gambleMgRateTbl[var_v1_3]) {
                break;
            }
        }
    
        if (var_v1_3 == 3) {
            var_v1_3 = 2;
        }
        system->minigame_index = mb1ev_gambleMgTbl[var_v1_3];
        GwSystem.playerIndexVisitingBowser = sel;
        MBGameModeMgSet();
        omAllUPause();
        MBExitReq(2);
        HuPrcSleep(-1);
    }
}

void MB1Ev_After5ItemMove(s32 sprGrp, s32 frames, f32 *dest) {
    f32 x;
    f32 y;
    f32 stepX;
    f32 stepY;
    s32 i;

    MBStatusSprPosGet(sprGrp, 0, &x, &y);
    stepX = (dest[0] - x) / frames;
    stepY = (dest[1] - y) / frames;

    for (; frames != 0; frames--) {
        x += stepX;
        y += stepY;
        HuSprPosSet(sprGrp, 0, x, y);
        HuPrcVSleep();
    }

    HuSprPosSet(sprGrp, 0, dest[0], dest[1]);
}

void MB1Ev_After5LineShow(omObjData *obj) {
    s32 temp_s1;
    s32 temp_v0;
    s32 var_s0;
    s32 var_s3;
    s32 var_v0;
    s32 i;

    temp_s1 = (s32)HuPrcCurrentGet()->user_data;
    var_s3 = 10;

    switch (temp_s1) {
        case 0:
            HuSprPosSet(mb1ev_after5GrpId[temp_s1], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(mb1ev_after5GrpId[temp_s1], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(mb1ev_after5GrpId[temp_s1], 0, 0xA0, 0x98);
            var_s3 = 30;
            break;
    }

    HuSprDispOn(mb1ev_after5GrpId[temp_s1], 0);
    for (i = 0; i < 255; i += 255 / var_s3) {
        HuSprTPLvlSet(mb1ev_after5GrpId[temp_s1], 0, i);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mb1ev_after5GrpId[temp_s1], 0, 0xFF);
    omDelPrcObj(0);
}

void MB1Ev_After5NumFade(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i, j;

    for (i = 0; i <= 0; i++) {
        sp18.r = mb1ev_after5NumColorTbl[i].r;
        sp18.g = mb1ev_after5NumColorTbl[i].g;
        sp18.b = mb1ev_after5NumColorTbl[i].b;

        sp28.r = (mb1ev_after5NumColorTbl[i + 1].r - sp18.r) / 30;
        sp28.g = (mb1ev_after5NumColorTbl[i + 1].g - sp18.g) / 30;
        sp28.b = (mb1ev_after5NumColorTbl[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(mb1ev_after5GrpId[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(mb1ev_after5GrpId[3], 0, mb1ev_after5NumColorTbl[i + 1].r, mb1ev_after5NumColorTbl[i + 1].g, mb1ev_after5NumColorTbl[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

void MB1Ev_After5Effect(void) {
    Object *obj;
    s32 *state;
    f32 spin;
    f32 scale;

    state = HuPrcCurrentGet()->user_data;
    HuAudFXPlay(0x143);
    obj = mb1ev_after5EffMdl;
    MBModelDispFlagSet(obj);

    for (spin = 0.0f, scale = 1.0f; scale < 18.0f; scale += 0.8) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 1) {
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    for (; scale < 40.0f; scale += 0.8) {
        HuVecCopyXYZ(&obj->scale, scale, scale, scale);
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    while (*state != 2) {
        HuMtxRotZF(Hu3DData[obj->omObj1->model[0]].mtx, spin);
        spin += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(obj);
    omDelPrcObj(NULL);
}


// main function for using a wacky watch?
void MB1Ev_ItemAfter5(void) {
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
    s32 *temp_s0;
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
        mb1ev_after5GrpId[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(mb1ev_after5GrpId[i], 0, sp18[i], 0);
        HuSprPriSet(mb1ev_after5GrpId[i], 0, 0x4780U);
        HuSprAttrSet(mb1ev_after5GrpId[i], 0, HUSPR_ATTR_DISPOFF | HUSPR_ATTR_XLU | HUSPR_ATTR_AA | HUSPR_ATTR_FILTER_AVERAGE);
        HuSprTPLvlSet(mb1ev_after5GrpId[i], 0, 0U);
        HuSprColorSet(mb1ev_after5GrpId[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    mb1ev_after5EffMdl = temp_v0_3;
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
    MB1Ev_After5ItemMove(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    MB1Ev_After5ItemMove(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(MB1Ev_After5LineShow, 0x4002, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    MB1Ev_After5ItemMove(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(MB1Ev_After5LineShow, 0x4002, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    MB1Ev_After5ItemMove(temp_s4, 0xA, sp28);
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
            temp_v0_4 = omAddPrcObj(MB1Ev_After5LineShow, 0x4002, 0, 0);
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
        HuSprDispOff(mb1ev_after5GrpId[i], 0);
    }

    HuSprDispOn(mb1ev_after5GrpId[3], 0);
    HuSprTPLvlSet(mb1ev_after5GrpId[3], 0, 0xFFU);
    HuSprPosSet(mb1ev_after5GrpId[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(MB1Ev_After5NumFade, 0x4002, 0, 0));
    sp40 = 0;
    omAddPrcObj(MB1Ev_After5Effect, 0x4002, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(mb1ev_after5GrpId[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
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
        HuSprScaleSet(mb1ev_after5GrpId[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(mb1ev_after5GrpId[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(WIPE_FADE, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = WATCH_USED;
}

void MB1Ev_BranchMain(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    BranchLink *link;
    s32 back;
    s32 sel;
    s32 count;
    s32 row;
    s32 col;
    s32 i;
    s16* temp;

    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    MB1_BranchHelpStart();

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

    //TODO: matching hack
    if (temp) {
        temp = masu[row];
        link = links[row];
        win = MBBranchArrowLinkCreate(GwSystem.current_player_index, temp);
        MBBranchSelStart(win, GwSystem.current_player_index, 0);
    } else {
        temp = masu[row];
        link = links[row];
        win = MBBranchArrowLinkCreate(GwSystem.current_player_index, temp);
        MBBranchSelStart(win, GwSystem.current_player_index, 0);
    }


    if (MBPlayerComCheck(-1)) {
        count = MBComTreeExec(trees[row]);
        for (i = 0; i < count; i++) {
            MBBranchSelMesSend(win, -2);
        }
        MBBranchSelMesSend(win, -4);
    }

    sel = MBBranchSelWait(win);
    MBBranchArrowGrpKill(win);
    MB1_BranchHelpEnd();
    
    if (sel) {
        link++;
    }

    MBMoveNextMasuSet(-1, link->link, link->idx);

    switch (link->rev) {
    case 0:
        player->rev &= ~FLAG_REV;
        break;
    case 1:
        player->rev |= FLAG_REV;
        break;
    }
}

void MB1Ev_KinokoMarkKill(s32 arg0) {
    if (mb1ev_kinokoMarkObj[arg0] != NULL) {
        omDelObj(mb1ev_kinokoMarkObj[arg0]);
        mb1ev_kinokoMarkObj[arg0] = NULL;
    }
    if (mb1ev_kinokoMarkMdl[arg0] != NULL) {
        MBModelKill(mb1ev_kinokoMarkMdl[arg0]);
        mb1ev_kinokoMarkMdl[arg0] = NULL;
    }
}

void MB1Ev_KinokoMarkObjKillAll(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (mb1ev_kinokoMarkObj[i] != NULL) {
            omDelObj(mb1ev_kinokoMarkObj[i]);
            mb1ev_kinokoMarkObj[i] = NULL;
        }
    }
}

void MB1Ev_KinokoMarkObjMain(omObjData *obj) {
    GW_PLAYER *player;
    Object *model;
    s32 playerNo;

    playerNo = obj->work[0];

    if ((GwSystem.current_player_index == 4) && (obj->work[2] == 0)) {
        if (obj->work[1] == 0) {
            obj->work[1] = 0x28;
            return;
        }
        obj->work[1]--;
        if (obj->work[1] != 0) {
            return;
        }
        obj->work[2] = 1;
    }

    player = MBPlayerGet(playerNo);
    model = mb1ev_kinokoMarkMdl[playerNo];
    HuVecCopy3F(&model->coords, &player->player_obj->coords);
    model->velocity.x = player->player_obj->velocity.x + 20.0f;
    HuVecCopy3F(&model->rot, &player->player_obj->rot);
    model->coords.x += sindf(obj->rot.x) * obj->trans.x;
    model->coords.z += cosdf(obj->rot.x) * obj->trans.x;

    obj->rot.x += 5.0f;
    if (obj->rot.x >= 360.0f) {
        obj->rot.x -= 360.0f;
    }
    if (obj->trans.x <= 5.0f) {
        obj->trans.x += 0.25f;
    }

    if (player->player_obj->flags & 8) {
        MBModelDispFlagSet(model);
    } else {
        MBModelDispOff(model);
    }
}

void MB1Ev_KinokoMarkCreate(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (mb1ev_kinokoMarkMdl[playerNo] == NULL) {
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
        mb1ev_kinokoMarkMdl[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        MBModelDispFlagSet(mb1ev_kinokoMarkMdl[playerNo]);
    }
}

void MB1Ev_KinokoMarkObjCreate(u32 arg0) {
    omObjData* temp_v0 = omAddObj(0x3FFF, 0, 0, -1, MB1Ev_KinokoMarkObjMain);
    
    mb1ev_kinokoMarkObj[arg0] = temp_v0;
    temp_v0->work[0] = arg0;
    mb1ev_kinokoMarkObj[arg0]->work[1] = 0;
    mb1ev_kinokoMarkObj[arg0]->work[2] = 0;
    mb1ev_kinokoMarkObj[arg0]->rot.x = MBRand(360.0f);
    mb1ev_kinokoMarkObj[arg0]->trans.x = 0.0f;
}

void MB1Ev_KinokoMarkCreateAll(void) {
    s32 var_s1;
    s32 i;

    for (i = 0; i < 4; i++) {
        mb1ev_kinokoMarkObj[i] = 0;
        mb1ev_kinokoMarkMdl[i] = 0;
        
        if (MBPlayerGet(i)->rev & 2) {
            var_s1 = 0;
        } else {
            var_s1 = -1;
        }
        
        if (MBPlayerGet(i)->rev & 4) {
            var_s1 = 1;
        }
        if (MBPlayerGet(i)->rev & 0x20) {
            var_s1 = 2;
        }
        if (MBPlayerGet(i)->rev & 0x40) {
            var_s1 = 3;
        }
        if (var_s1 != -1) {
            MB1Ev_KinokoMarkCreate(i, var_s1);
            MB1Ev_KinokoMarkObjCreate(i);
        }        
    }


    MBExitHookSet(&MB1Ev_KinokoMarkObjKillAll);
}

void MB1Ev_NKinokoTurnStart(void) {
    GW_PLAYER *player;
    f32 scale;
    s32 mesNum;
    GW_SYSTEM* system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);

    if ((GwSystem.slow_dice_flags >> system->current_player_index) & 1) {
        GWBoardFlagSet(0x10);
        system->slow_dice_flags &= ~(1 << system->current_player_index);
        if ((player->rev & 0x20) || ((player->rev & 0x8) && !(player->rev & 0x2))) {
            MBDlgWinExec(-1, 0x4219);
        } else {
            MBDlgWinExec(-1, 0x3A07);
        }

        if (player->rev & 2) {
            if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(
                        &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                        scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB1Ev_KinokoMarkKill(system->current_player_index);
        }

        if (player->rev & 8) {
            if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(
                        &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                        scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB1Ev_KinokoMarkKill(system->current_player_index);
        }

        player->rev &= ~(0x20 | 0x8 | 0x2);
    }
}

void MB1Ev_ItemKoopaNKinoko(void) {
    GW_PLAYER *player;
    f32 scale;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);

    if (player->rev & 8) {
        MBSaiKill(system->current_player_index);
        GWBoardFlagSet(0x10);
        GwSystem.slow_dice_flags &= ~(1 << system->current_player_index);
        MBDlgWinExec(-1, 0x4219);

        if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(
                    &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                    scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB1Ev_KinokoMarkKill(system->current_player_index);

        player->rev &= ~(0x20 | 0x08);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(system->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB1Ev_KinokoVibrateProc() {
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

extern s32 mb1_comNKinokoTarget;

void MB1Ev_ItemNKinoko(void) {
    GW_PLAYER *player;
    UnkVibrateProcess *vib;
    f32 scaleX;
    f32 scaleY;
    f32 scale;
    s16 target;
    s16 saved;
    s32 sel;
    GW_SYSTEM* system = &GwSystem;

    MBDlgWinInsertCreate(-1, 0x5C01,
                         GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    sel = MB1Ev_YesNoChoiceGet((DecisionTreeNonLeafNode *)2, mb1_comNKinokoTarget);
    MBDlgWinClose();
    MBDlgWinKill();

    
    if (sel >= MB_MAX_PLAYERS) {
        target = MBPlayerRankRandGet(0);
    } else if (sel < 0) {
        target = MBPlayerRankRandGet(0);
    } else {
        target = sel;
    }

    GwSystem.slow_dice_flags |= 1 << target;
    player = MBPlayerGet(target);

    for (scaleX = 1.0f, scaleY = 1.0f; scaleX > 0.0f;) {
        scaleX -= 0.1f;
        scaleY += 0.07f;
        MBStatusItemScaleSet(system->current_player_index, MBItemSelNoGet(), scaleX, scaleY);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (target != system->current_player_index) {
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

    MB1Ev_KinokoMarkKill(target);
    player->rev = (player->rev & 0x99) | 2;
    MB1Ev_KinokoMarkCreate(target, 0);

    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, 1.0f, 1.0f, 1.0f);

    if (target == system->current_player_index) {
        MBPlayerMotionSet(target, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(target)->player_obj, 4, 2);
    }

    CharFXPlay(0x286, GwPlayer[target].chr);
    MB1Ev_KinokoMarkObjCreate(target);
    vib = MBPlayerVibrateObjCreate(target, 1, 5);
    omAddPrcObj(MB1Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    saved = system->current_player_index;
    system->current_player_index = target;
    if (player->rev & 0x80) {
        MBDlgWinExec(-1, 0x3A09);
    }
    MBDlgWinExec(-1, 0x3A06);
    system->current_player_index = saved;

    if (target == (s8)saved) { //TODO: casting hack
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(target)->player_obj, -1, 2);
        mbTauntOffF = 0;
    }

    if (target != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (target == system->current_player_index) {
        GWBoardFlagSet(0x10);
        MBDlgWinExec(-1, 0x3A07);
        for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
            HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, 0.0f, 0.0f, 0.0f);
        MB1Ev_KinokoMarkKill(system->current_player_index);
        MBSaiKill(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

void MB1Ev_RKinokoTurnStart(void) {
    GW_PLAYER *player;
    f32 scale;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);

    if (player->rev & 0x80) {
        //TODO: why is it loading this as a u32?
        if ((player->rev & 0x40) || ((*((u32*)&player->nnidx) & 0x14) == 0x10)) {
            MBDlgWinExec(-1, 0x421C);
        } else {
            MBDlgWinExec(-1, 0x3A03);
        }

        if (player->rev & 4) {
            if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(
                        &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                        scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB1Ev_KinokoMarkKill(system->current_player_index);
        }

        if (player->rev & 0x10) {
            if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(
                        &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                        scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            MB1Ev_KinokoMarkKill(system->current_player_index);
        }

        player->rev &= ~0x54;
    }
}

void MB1Ev_ItemKoopaRKinoko(void) {
    GW_PLAYER *player;
    f32 scale;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);

    if (player->rev & 0x10) {
        MBSaiKill(system->current_player_index);
        MBDlgWinExec(-1, 0x421C);

        if (mb1ev_kinokoMarkMdl[system->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(
                    &mb1ev_kinokoMarkMdl[system->current_player_index]->scale,
                    scale, scale, scale);
                HuPrcVSleep();
            }
        }
        MB1Ev_KinokoMarkKill(system->current_player_index);

        player->rev &= ~0x50;
        MBPlayerVibrate(-1, 2);
        MBSaiCreate(system->current_player_index);
        HuPrcSleep(0xF);
    }
}

void MB1Ev_ItemRKinoko(void) {
    GW_PLAYER *player;
    UnkVibrateProcess *vib;
    f32 scaleX;
    f32 scaleY;
    f32 scale;
    s16 target;
    s16 saved;
    s32 sel;
    GW_SYSTEM *system = &GwSystem;

    MBDlgWinInsertCreate(-1, 0x5C01,
                         GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    sel = MB1Ev_YesNoChoiceGet((DecisionTreeNonLeafNode *)2, mb1_comRKinokoTarget);
    MBDlgWinClose();
    MBDlgWinKill();

    if (sel >= MB_MAX_PLAYERS) {
        target = MBPlayerRankRandGet(0);
    } else if (sel < 0) {
        target = MBPlayerRankRandGet(0);
    } else {
        target = sel;
    }

    player = MBPlayerGet(target);
    player->rev |= 0x80;

    for (scaleX = 1.0f, scaleY = 1.0f; scaleX > 0.0f;) {
        scaleX -= 0.1f;
        scaleY += 0.07f;
        MBStatusItemScaleSet(system->current_player_index, MBItemSelNoGet(), scaleX, scaleY);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);

    if (target != system->current_player_index) {
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

    MB1Ev_KinokoMarkKill(target);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(target, 3);
    MB1Ev_KinokoMarkCreate(target, 1);

    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&mb1ev_kinokoMarkMdl[target]->scale, 1.0f, 1.0f, 1.0f);

    if (target == system->current_player_index) {
        MBPlayerMotionSet(target, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(target)->player_obj, 4, 2);
    }

    CharFXPlay(0x286, GwPlayer[target].chr);
    vib = MBPlayerVibrateObjCreate(target, 1, 5);
    MB1Ev_KinokoMarkObjCreate(target);
    omAddPrcObj(MB1Ev_KinokoVibrateProc, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    saved = system->current_player_index;
    system->current_player_index = target;
    if (((saved == target) && (MBSaiTypeGet(saved) == 3)) ||
        ((GwSystem.slow_dice_flags >> target) & 1)) {
        MBDlgWinExec(-1, 0x3A05);
    }
    MBDlgWinExec(-1, 0x3A02);
    system->current_player_index = saved;

    if (target == (s8)saved) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(target)->player_obj, -1, 2);
        mbTauntOffF = 0;
    }

    if (target != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(CUR_PLAYER)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (target == system->current_player_index) {
        MB1Ev_RKinokoTurnStart();
    }
}



void MB1Ev_ItemRobBox(void) {
    char inserts[4][0x10];
    u8 enabled[6];
    Object *box;
    s32 slot;
    s32 count;
    f32 scale;
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    s32 j;
    u16* temp;
    u16 motId;
    char pad[8];
    s32 target = 0;
    
    MB1Ev_ItemUseFadeOut();
    box = MBModelCreate(0x21, NULL);
    Hu3DModelScaleSet(box->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&box->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    Hu3DMotionAttrSet(box->omObj1->model[0], 2, 1);
    box->velocity.x = 100.0f;
    HuAudFXPlay(0x142);

    while (box->velocity.x > 30.0f) {
        box->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    if (target != 0) {
        for (i = 0; i < 0x439; i += 0x1E) {
            HuVecCopyXYZ(&box->scale, (sindf(i) / 2.0f) + 1.0f, (sindf(i) / 2.0f) + 1.0f, (sindf(i) / 2.0f) + 1.0f);
            HuPrcVSleep();
        }        
    }


    HuAudFXPlay(0x149);
    Hu3DMotionAttrSet(box->omObj1->model[0], 1, 0);
    HuPrcSleep(0x14);

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (GwSystem.current_player_index == i) {
            inserts[i][0] = 1;
            enabled[i] = 0;
        } else {
            inserts[i][0] = 8;
            enabled[i] = 1;
        }
        MBCharNameMesConv(i, &inserts[i][1]);
    }
    enabled[4] = 1;
    enabled[5] = 1;

    MBDlgWinInsertCreate(-1, 0x5C01, (s32)inserts[0], (s32)inserts[1],
                         (s32)inserts[2], (s32)inserts[3], 0);
    target = MB1_ComItemTargetChoice(enabled, 0);
    MBDlgWinClose();
    MBDlgWinKill();

    if (target == MB_MAX_PLAYERS) {
        target = MBPlayerRankRandGet(1);
    }

    if (GwPlayer[target].itemNo[0] == ITEM_NONE) {
        MBPlayerMotionSet(-1, 3, 0);
        PlayerFXPlay(0x286, system->current_player_index);
        HuPrcSleep(0x3C);
        MBCharNameMesConv(target, inserts[0]);
        MBWinInsertOpen(0x3A0F, inserts[0], 0, 0, 0, 0);
        MBWinKeyWait(system->current_player_index);
        MBWinClose();
        MBPlayerMotionShiftSet(-1, -1, 0, 0xA, 2);
        MBModelKill(box);
        GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = ITEM_NONE;
        MBItemRemoveEmpty(system->current_player_index);
        return;
    }

    i = MBItemFindEmpty(target);
    if (i == -1) {
        i = ARRAY_COUNT(GwPlayer->itemNo);
    }
    slot = MBRand(i);

    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] =
        GwPlayer[target].itemNo[slot];
    GwPlayer[target].itemNo[slot] = ITEM_NONE;
    MBItemRemoveEmpty(target);
    MBPlayerVibrate(target, 3);

    if (MBItemSelNoGet() == slot) {
        MBStatusItemTPLvlSet(target, MBItemSelNoGet(), 0);
    }
    MBStatusItemSprKill(-1);
    MBStatusItemPosSet(system->current_player_index, MBItemSelNoGet(),
                       mb1ev_robBoxItemStartPosTbl[system->current_player_index][0],
                       mb1ev_robBoxItemStartPosTbl[system->current_player_index][1]);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(target, slot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);

    HuPrcChildLink(HuPrcCurrentGet(),
        MB1Ev_ItemMoveCreate(-1,
            mb1ev_robBoxItemStartPosTbl[system->current_player_index][0],
            mb1ev_robBoxItemStartPosTbl[system->current_player_index][1],
            mb1ev_robBoxItemEndPosTbl[system->current_player_index][0],
            mb1ev_robBoxItemEndPosTbl[system->current_player_index][1],
            5));
    HuPrcChildWatch();

    PlayerFXPlay(0x274, system->current_player_index);
    MBPlayerMotionLoad(system->current_player_index, 5, 0x31);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(0x32);
    MBPlayerMotionShiftSet(system->current_player_index, -1, 0, 0xA, 2);
    HuPrcSleep(0xB);
       
    MOTION_ID_GET(6, temp, i);
    
    MBPlayerMotionLoad(system->current_player_index, 5,
                       motId);
    MBModelKill(box);

    MBDlgWinInsertCreate(-1, 0x3A0D,
                         GwPlayer[target].chr + 0x1C00,
                         GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    MB1Ev_ItemCursorReturn();
}

void MB1Ev_TuruturuMain(void) {
    Vec dest;
    Vec target;
    GW_SYSTEM *system;
    GW_PLAYER *player;
    GW_PLAYER *curPlayer;
    GW_PLAYER *other;
    GW_PLAYER *nearby;
    Object *playerObj;
    SpaceData *nextSpace;
    SpaceData *slideSpace;
    SpaceData *endSpace;
    Vec *pos;
    Process *proc;
    u16 *motion;
    s32 success;
    s32 soundId;
    s32 played;
    s32 i;
    f32 angle;
    f32 speed;

    soundId = 0;
    other = NULL;
    system = &GwSystem;
    MBPlayerMotionLoad(system->current_player_index, 5, 10);
    MBPlayerMotionLoad(system->current_player_index, 6, 16);
    if ((GwSystem.boardData.halfWordBytes[1] >> system->current_player_index) & 1) {
        success = MBRandCheck100(90) != 0;
    } else {
        success = MBRandCheck100(70) != 0;
    }
    if (!success) {
        GwSystem.boardData.halfWordBytes[1] |= 1 << system->current_player_index;
        mbWalkNum = 0;
    } else {
        GwSystem.boardData.halfWordBytes[1] &= ~(1 << system->current_player_index);
    }
    MBSaiNumKill(system->current_player_index);
    player = MBPlayerGet(CUR_PLAYER);
    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x5A:
            MBMasuGet(0x5B);
            nextSpace = MBMasuGet(0x74);
            slideSpace = MBMasuGet(0x5A);
            endSpace = MBMasuGet(0x8A);
            break;
        case 0x47:
            MBMasuGet(0x48);
            nextSpace = MBMasuGet(0x75);
            slideSpace = MBMasuGet(0x47);
            endSpace = MBMasuGet(0x8B);
            break;
        default:
            MBMasuGet(0x79);
            nextSpace = MBMasuGet(0x76);
            slideSpace = MBMasuGet(0x3E);
            endSpace = MBMasuGet(0x8C);
            break;
    }
    curPlayer = MBPlayerGet(CUR_PLAYER);
    playerObj = curPlayer->player_obj;
    HuVecCopy3F(&target, &nextSpace->coords);
    MBVecDirGet(&playerObj->coords, &target, &playerObj->rot);
    MBPlayerMotionSet(CUR_PLAYER, 0, 2);
    angle = atan2df(playerObj->rot.x, -playerObj->rot.z) + 180.0f;
    speed = 2.0f;
    for (i = 0; i < 3; i++) {
        playerObj->coords.x += sindf(angle) * speed;
        playerObj->coords.z -= cosdf(angle) * speed;
        HuPrcVSleep();
    }
    MBPlayerMotionShiftSet(-1, -1, 0, 2, 2);
    HuPrcSleep(2);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBCameraZoomMotStart(1.6f));
    HuPrcChildWatch();
    MBPlayerMotionSet(CUR_PLAYER, 1, 2);
    for (i = 0; i < 4; i++) {
        if (i == system->current_player_index) {
            continue;
        }
        nearby = MBPlayerGet(i);
        switch (MBMasuLinkMasuIdGet(nearby->clink, nearby->cidx)) {
            case 0x5A:
                pos = &nearby->player_obj->coords;
                HuVecCopy3F(&dest, pos);
                dest.x += 5.0f;
                dest.z -= 5.0f;
                MBVecSpeedMove2Create(pos, &dest, pos, 2.0f);
                break;
            case 0x47:
                pos = &nearby->player_obj->coords;
                HuVecCopy3F(&dest, pos);
                dest.x += 10.0f;
                dest.z -= 5.0f;
                MBVecSpeedMove2Create(pos, &dest, pos, 2.0f);
                break;
        }
    }
    MBPlayerVibrate(CUR_PLAYER, 1);
    angle -= 180.0f;
    speed = 4.0f;
    for (i = 0, played = FALSE; i < 30; i++) {
        playerObj->coords.x += sindf(angle) * speed;
        playerObj->coords.z -= cosdf(angle) * speed;
        if (0.0f < speed) {
            speed -= 0.25f;
        } else if (!played) {
            played = TRUE;
            soundId = HuAudFXPlay(0x187);
            MBPlayerSpeedSet(system->current_player_index, 2.0f);
        }
        HuPrcVSleep();
    }
    HuAudFXStop(soundId);
    if (success) {
        MBSaiNumShow(system->current_player_index);
        proc = HuPrcCurrentGet();
        HuPrcChildLink(proc, MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
            case 0x5A:
                curPlayer->clink = 7;
                curPlayer->cidx = 3;
                curPlayer->nlink = 7;
                curPlayer->nidx = 4;
                curPlayer->blink = 7;
                curPlayer->bidx = 2;
                break;
            case 0x47:
                curPlayer->clink = 8;
                curPlayer->cidx = 2;
                curPlayer->nlink = 8;
                curPlayer->nidx = 3;
                curPlayer->blink = 8;
                curPlayer->bidx = 1;
                break;
            default:
                curPlayer->clink = 9;
                curPlayer->cidx = 2;
                curPlayer->nlink = 9;
                curPlayer->nidx = 3;
                curPlayer->blink = 9;
                curPlayer->bidx = 1;
                break;
        }
    } else {
        MBPlayerVibrate(CUR_PLAYER, 3);
        HuAudFXPlay(0x188);
        MBPlayerMotionSet(CUR_PLAYER, 5, 0);
        MBPlayerMotionWait(CUR_PLAYER);
        MBPlayerMotionSet(CUR_PLAYER, 6, 1);
        HuVecCopy3F(&dest, &slideSpace->coords);
        MBVecDirGet(&dest, &playerObj->coords, &playerObj->rot);
        proc = MBVecSpeedMove2Create(&playerObj->coords, &dest, &playerObj->coords, 2.0f);
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        for (i = 0; i < 4; i++) {
            if (system->current_player_index == i) {
                continue;
            }
            other = MBPlayerGet(i);
            if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == MBMasuLinkMasuIdGet(other->clink, other->cidx)) {
                break;
            }
        }
        if (i < 4) {
            MBVecSpeedMoveCreate(&other->player_obj->coords, &endSpace->coords, &other->player_obj->coords, 2.0f);
        }
        HuPrcChildWatch();
        MBWinOpen(0x300);
        MBWinKeyWaitKeep(system->current_player_index);
        MBWinClose();
        MBPlayerMotionSet(CUR_PLAYER, 6, 0);
        MBPlayerMotionWait(CUR_PLAYER);
        MBPlayerMotionSet(CUR_PLAYER, -1, 2);
    }
    motion = (u16 *)mbPlayerMotTbl[0];
    for (i = 6; i != 0; i--) {
        motion += 2;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, motion[1]);
    motion = (u16 *)mbPlayerMotTbl[0];
    for (i = 7; i != 0; i--) {
        motion += 2;
    }
    MBPlayerMotionLoad(system->current_player_index, 6, motion[1]);
    if (!success) {
        HuPrcSleep(5);
        MBItemKSuitEnd();
    }
}

void MB1Ev_Turuturu() {
    GW_PLAYER *player;

    player = MBPlayerGet(CUR_PLAYER);
    if (mbWalkNum != 0) {
        if (!(player->rev & FLAG_REV)) {
            HuPrcSleep(0xA);
            MB1Ev_TuruturuMain();
        }
    }
}

void MB1Ev_TuruturuCheck(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (!(player->rev & FLAG_REV)) {
        switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x3E:
        case 0x47:
        case 0x5A:
            MB1Ev_TuruturuMain();
            break;
        }
    }
}

void MB1Ev_SnowmanObjMain(void) {
    Object *obj;
    SpaceData *space;
    f32 baseZ;
    f32 angle;

    obj = MBModelCreate(0x2F, NULL);
    mb1ev_snowmanMdl = obj;
    space = MBMasuGet(0x83);

    mb1ev_snowmanBaseMdl = MBModelCreate(0x2D, NULL);
    HuVecCopy3F(&mb1ev_snowmanBaseMdl->coords, &MBMasuGet(0x81)->coords);
    mb1ev_snowmanBaseMdl->coords.x += 1.0f;
    mb1ev_snowmanBaseMdl->coords.z -= 20.0f;
    mb1ev_snowmanBaseMdl->scale.x = 1.2f;
    mb1ev_snowmanBaseMdl->scale.z = 1.2f;
    MBModelDispOn(mb1ev_snowmanBaseMdl);

    while (1) {
        Hu3DMotionAttrSet(obj->omObj1->model[0], 1, 1);
        HuVecCopy3F(&obj->coords, &space->coords);
        obj->coords.x -= 10.0f;
        MBModelDispOn(obj);

        while (mb1ev_snowmanRollF == 0) {
            HuPrcVSleep();
        }

        for (angle = 0.0f, baseZ = obj->coords.z; angle < 720.0f; angle += 40.0f) {
            obj->coords.z = baseZ + (2.0f * sindf(angle));
            HuPrcVSleep();
        }
        obj->coords.z = baseZ;
        HuAudFXPlay(0x189);

        while (mb1ev_snowmanRollF != 0) {
            obj->coords.y += 10.0f;
            HuPrcVSleep();
        }

        MBModelDispOff(obj);
    }
}

void MB1Ev_SnowmanBaseEmptySet() {
    Object *temp_a0;
    Object *temp_ret;
    Object *temp_v0;
    Object *temp_v0_2;

    temp_v0 = mb1ev_snowmanBaseEmptyMdl;
    if (temp_v0 == NULL) {
        temp_v0_2 = MBModelCreate(0x2E, 0);
        mb1ev_snowmanBaseEmptyMdl = temp_v0_2;
        MBModelTempAllocFree(temp_v0_2);
        HuVecCopy3F(&(mb1ev_snowmanBaseEmptyMdl->coords), &(MBMasuGet(0x81)->coords));
        temp_a0 = mb1ev_snowmanBaseEmptyMdl;
        temp_a0->coords.x = temp_a0->coords.x + 1.0f;
        temp_a0->coords.z = temp_a0->coords.z - 20.0f;
        temp_a0->scale.x = 1.2f;
        temp_a0->scale.z = 1.2f;
        MBModelDispOn(temp_a0);
        MBModelKill(mb1ev_snowmanBaseMdl);
        mb1ev_snowmanBaseMdl = NULL;
    }
}

void MB1Ev_SnowmanBaseReset() {
    Object *temp_a0;
    Object *temp_ret;
    Object *temp_v0;
    Object *temp_v0_2;

    temp_v0 = mb1ev_snowmanBaseMdl;
    if (temp_v0 == NULL) {
        temp_v0_2 = MBModelCreate(0x2D, 0);
        mb1ev_snowmanBaseMdl = temp_v0_2;
        MBModelTempAllocFree(temp_v0_2);
        HuVecCopy3F(&(mb1ev_snowmanBaseMdl->coords), &(MBMasuGet(0x81)->coords));
        temp_a0 = mb1ev_snowmanBaseMdl;
        temp_a0->coords.x = temp_a0->coords.x + 1.0f;
        temp_a0->coords.z = temp_a0->coords.z - 20.0f;
        temp_a0->scale.x = 1.2f;
        temp_a0->scale.z = 1.2f;
        MBModelDispOn(temp_a0);
        MBModelKill(mb1ev_snowmanBaseEmptyMdl);
        mb1ev_snowmanBaseEmptyMdl = NULL;
    }
}

void MB1Ev_SnowmanRoll(void) {
    Vec playerPos;
    Vec snowmanPos;
    SnowmanRollWork *work;
    GW_PLAYER *player;
    Object *playerObj;
    Object *snowman;
    SpaceData *space;
    Process *proc;
    UnkVibrateProcess *vib;
    s16 *masuList;
    u16 *motion;
    s32 order;
    s32 path;
    s32 state;
    s32 frames;
    s32 count;
    s32 idx;
    s32 temp;
    f32 spacing;
    f32 dist;
    f32 gravity;
    f32 height;
    f32 velocity;

    work = HuPrcCurrentGet()->user_data;
    spacing = 20.0f;
    snowman = mb1ev_snowmanRollMdl;
    player = MBPlayerGet(work->player);
    playerObj = player->player_obj;
    order = work->order;
    path = work->path;
    masuList = mb1ev_snowmanPathMasuTbl[path];
    proc = HuPrcCurrentGet();
    MBPlayerMotionLoad(work->player, 6, 0x70);
    if (path & 1) {
        spacing = 15.0f;
    }
    vib = MBPlayerVibrateObjCreate(work->player, 0, 5);
    state = 0;
    while (TRUE) {
        space = MBMasuGet(MBMasuLinkMasuIdGet(player->clink, player->cidx));
        HuVecCopy3F(&playerPos, &playerObj->coords);
        HuVecCopy3F(&snowmanPos, &snowman->coords);
        if (path & 1) {
            playerPos.x = snowmanPos.x = 0.0f;
        } else {
            playerPos.z = snowmanPos.z = 0.0f;
        }
        if (HuVecDistance(&playerPos, &snowmanPos) < mb1ev_snowmanSpeed * 2.0f + 100.0f + order * spacing &&
            state == 0) {
            mb1ev_snowmanHitTbl[work->player] = 2;
        }
        if (HuVecDistance(&playerPos, &snowmanPos) < order * spacing + 100.0f) {
            if ((ContBtnDown[GwPlayer[work->player].pad] & A_BUTTON) && state != 0) {
                if (state != 2) {
                    mb1ev_snowmanHitTbl[work->player] = 4;
                    if (work->player == GwSystem.current_player_index) {
                        MBPlayerMotionSet(-1, 4, 2);
                    } else {
                        MBMotionSet(playerObj, 4, 2);
                    }
                }
                state = 2;
            }
            if ((ContBtnDown[GwPlayer[work->player].pad] & A_BUTTON) && state == 0) {
                state = 1;
            }
        } else if ((ContBtnDown[GwPlayer[work->player].pad] & A_BUTTON) && state == 0) {
            if (state != 2) {
                mb1ev_snowmanHitTbl[work->player] = 4;
                if (work->player == GwSystem.current_player_index) {
                    MBPlayerMotionSet(-1, 4, 2);
                } else {
                    MBMotionSet(playerObj, 4, 2);
                }
            }
            state = 2;
        }
        if (HuVecDistance(&playerPos, &snowmanPos) < order * spacing + 31.0f) {
            break;
        }
        MBVecDirGet(&playerObj->coords, &snowman->coords, &playerObj->rot);
        HuPrcVSleep();
    }
    if (MBPlayerComCheck(work->player) && MBComTreeExec(mb1ev_snowmanPathComTree[path])) {
        state = 1;
    }
    if (state == 1) {
        MBPlayerVibrateObjKill(vib);
        mb1ev_snowmanHitTbl[work->player] = 3;
        if (work->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 2, 0);
        } else {
            MBMotionSet(playerObj, 2, 0);
        }
        PlayerFXPlay(0x274, work->player);
        PlayerFXPlay(0x3A, work->player);
        dist = HuVecDistance(&playerPos, &snowmanPos);
        frames = ((mb1ev_snowmanSpeed > mb1ev_snowmanCurSpeed) ? dist + 50.0f : dist + 40.0f) /
                 mb1ev_snowmanSpeed;
        for (gravity = -0.5f; gravity < -0.2f; gravity += 0.05f) {
            for (height = 0.0f, velocity = 7.0f, count = 0; height >= 0.0f; count++) {
                velocity += gravity;
                height += velocity;
            }
            if (frames < count) {
                break;
            }
        }
        MBModelJumpSet(playerObj, 7.0f, gravity);
        MBModelJumpWait(playerObj);
        PlayerFXPlay(0x31, work->player);
        MBPlayerMotionShiftSet(work->player, -1, 0, 5, 2);
        if (work->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
    } else {
        mb1ev_snowmanHitTbl[work->player] = 4;
        if (work->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 6, 2);
        } else {
            MBMotionSet(playerObj, 1, 2);
        }
        while (*masuList != -1) {
            space = MBMasuGet(*masuList);
            masuList++;
        }
        HuVecCopy3F(&playerPos, &space->coords);
        MBVecDirGet(&playerObj->coords, &playerPos, &playerObj->rot);
        PlayerFXPlay(0x286, work->player);
        HuPrcChildLink(proc, MB1Ev_SnowmanMoveCreate(&playerObj->coords, &playerPos, &playerObj->coords,
                                                        mb1ev_snowmanCurSpeed));
        HuPrcChildWatch();
        HuVecCopy3F(&playerPos, &MBMasuGet(mb1ev_snowmanEndMasuTbl[path])->coords);
        idx = (order - (work->count - 1) < 0) ? -(order - (work->count - 1)) : order - (work->count - 1);
        switch (work->count) {
            case 2:
                playerPos.x += mb1ev_snowmanOfs2Tbl[idx][0];
                playerPos.z += mb1ev_snowmanOfs2Tbl[idx][1];
                break;
            case 3:
                playerPos.x += mb1ev_snowmanOfs3Tbl[idx][0];
                playerPos.z += mb1ev_snowmanOfs3Tbl[idx][1];
                break;
            case 4:
                playerPos.x += mb1ev_snowmanOfs4Tbl[idx][0];
                playerPos.z += mb1ev_snowmanOfs4Tbl[idx][1];
                break;
        }
        if (path == 1) {
            playerPos.x -= 20.0f;
        }
        MBVecDirGet(&playerObj->coords, &playerPos, &playerObj->rot);
        HuPrcChildLink(proc, MBVecSpeedMoveCreate(&playerObj->coords, &playerPos, &playerObj->coords,
                                                        mb1ev_snowmanSpeed));
        HuPrcChildWatch();
        if (!(path & 1)) {
            playerPos.z += 35.0f;
            MBVecDirGet(&playerObj->coords, &playerPos, &playerObj->rot);
            HuPrcChildLink(proc, MBVecSpeedMoveCreate(&playerObj->coords, &playerPos, &playerObj->coords,
                                                            mb1ev_snowmanSpeed));
            HuPrcChildWatch();
        }
        MBPlayerVibrateObjKill(vib);
        if (work->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
        if (!(path & 1)) {
            MBPlayerRotMasuStart(work->player, 10, mb1ev_snowmanDirMasuTbl[path]);
        }
        switch (path) {
            case 0:
                player->clink = 12;
                player->cidx = 1;
                player->nlink = 12;
                player->nidx = 2;
                player->blink = 10;
                player->bidx = 11;
                break;
            case 1:
                player->clink = 1;
                player->cidx = 1;
                player->nlink = 1;
                player->nidx = 2;
                player->blink = 1;
                player->bidx = 0;
                break;
            case 2:
                player->clink = 5;
                player->cidx = 7;
                player->nlink = 5;
                player->nidx = 8;
                player->blink = 5;
                player->bidx = 6;
                break;
            default:
                player->clink = 3;
                player->cidx = 0;
                player->nlink = 3;
                player->nidx = 1;
                player->blink = 15;
                player->bidx = 10;
                break;
        }
        if (GwSystem.current_player_index == work->player && (player->rev & 0x80)) {
            temp = player->nlink;
            player->nlink = player->blink;
            player->blink = temp;
            temp = player->nidx;
            player->nidx = player->bidx;
            player->bidx = temp;
        }
    }
    motion = (u16 *)mbPlayerMotTbl[0];
    for (count = 7; count != 0; count--) {
        motion += 2;
    }
    MBPlayerMotionLoad(work->player, 6, motion[1]);
    omDelPrcObj(NULL);
}

s32 MB1Ev_SnowmanPathGet(s32 path) {
    GW_PLAYER *player;
    s16 *list;
    s32 count;
    s32 i;

    list = mb1ev_snowmanPathMasuTbl[path];
    count = 0;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        mb1ev_snowmanHitTbl[i] = 0;
    }

    do {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            player = MBPlayerGet(i);
            if (*list == MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
                mb1ev_snowmanHitTbl[i] = 1;
                count++;
            }
        }
        list++;
    } while (*list != -1);

    return count;
}

s32 MB1Ev_SnowmanPathPairGet(s32 arg0) {
    s32 temp_s1;

    temp_s1 = MB1Ev_SnowmanPathGet(arg0++);
    return temp_s1 + MB1Ev_SnowmanPathGet(arg0);
}

void MB1Ev_SnowmanSpeedSet(s32 arg0) {
    f32 var_f0;

    if (arg0 == -1) {
        do {
            arg0 = rand8() % 4;
        } while (mb1ev_snowmanLastSpeedNo == (f32) arg0);
        mb1ev_snowmanLastSpeedNo = (f32) arg0;
    }
    switch (arg0) {
    case 0:
        mb1ev_snowmanSpeed = 2.0f;
        break;
    case 1:
        mb1ev_snowmanSpeed = 2.3f;
        break;
    case 2:
        mb1ev_snowmanSpeed = 2.5f;
        break;
    default:
        mb1ev_snowmanSpeed = 2.7f;
        break;
    }
}

void MB1Ev_SnowmanMoveProc(void) {
    SnowmanMoveWork *work;
    f32 speed;

    work = HuPrcCurrentGet()->user_data;
    speed = work->speed;

    while (!(speed > HuVecDistance(&work->pos, &work->dest))) {
        HuVecSubtract(work->out, &work->dest, &work->pos);
        MBVecNormalize(work->out);
        HuVecMulScalar(work->out, speed, work->out);
        HuVecAdd(work->out, work->out, &work->pos);
        HuVecCopy3F(&work->pos, work->out);

        if (speed < mb1ev_snowmanSpeed) {
            speed += 0.05f;
        }
        if (mb1ev_snowmanSpeed < speed) {
            speed = mb1ev_snowmanSpeed;
        }
        mb1ev_snowmanCurSpeed = speed;
        HuPrcVSleep();
    }

    HuVecCopy3F(work->out, &work->dest);
    omDelPrcObj(NULL);
}

Process* MB1Ev_SnowmanMoveCreate(Vec* arg0, Vec* arg1, Vec* out, f32 speed) {
    Process* temp_v0;
    SnowmanMoveWork* temp_v0_2;

    temp_v0 = omAddPrcObj(MB1Ev_SnowmanMoveProc, 0x4002, 0, 0x50);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(SnowmanMoveWork));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->pos = *arg0;
    temp_v0_2->dest = *arg1;
    temp_v0_2->out = out;
    temp_v0_2->speed = speed;
    return temp_v0;
}

void MB1Ev_ActionTimeSpr(void) {
    s32 numAnim[4];
    s32 charAnim[4];
    s32 grpId[4];
    s32 titleAnim;
    s32 markAnim;
    s32 titleGrp;
    Process *proc;
    Unk3 *helpWin;
    void *data;
    s32 grp;
    s32 alpha;
    s32 fade;
    s32 flag;
    s32 count;
    s32 i;
    s32 j;
    f32 angle;
    f32 step;

    i = 0;
    proc = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    numAnim[0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    numAnim[1] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    numAnim[2] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    numAnim[3] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    markAnim = HuSprAnimRead(data);
    DataClose(data);
    for (; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        charAnim[i] = HuSprAnimRead(data);
        DataClose(data);
    }
    titleGrp = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(titleGrp, 0, titleAnim, 0);
    HuSprAttrReset(titleGrp, 0, 0xFFFF);
    HuSprAttrSet(titleGrp, 0, HUSPR_ATTR_XLU | HUSPR_ATTR_FILTER_BILERP);
    HuSprPriSet(titleGrp, 0, 0x1000);
    HuSprPosSet(titleGrp, 0, 160, 90);
    for (angle = 0.0f, step = 30.0f, count = 0, flag = 0;; angle += step) {
        if (angle >= 90.0f && flag == 0) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(titleGrp, 0, HUSPR_ATTR_FLIPY);
        } else {
            HuSprAttrReset(titleGrp, 0, HUSPR_ATTR_FLIPY);
        }
        HuSprScaleSet(titleGrp, 0, 1.0f, sindf((angle >= 180.0f) ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprAttrReset(titleGrp, 0, HUSPR_ATTR_FLIPY);
    HuSprScaleSet(titleGrp, 0, 1.0f, 1.0f);
    helpWin = MBHelpWinCreate(0x14, 0xA0, 1);
    for (i = 0; i < 4; i++) {
        grp = grpId[i] = HuSprGrpCreate(6, 5);
        HuSprGrpMemberSet(grp, 0, markAnim, 0);
        HuSprAnimModeSet(grp, 0, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(grp, 0, 0xFFFF);
        if (mb1ev_snowmanHitTbl[i] != 0) {
            HuSprAttrSet(grp, 0, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(grp, 0);
        }
        HuSprPriSet(grp, 0, 0x1000);
        HuSprParentSet(grp, 0, -1);
        HuSprGrpMemberSet(grp, 1, charAnim[i], 0);
        HuSprAnimModeSet(grp, 1, HUSPR_ANIM_MODE_STOP);
        HuSprAttrReset(grp, 1, 0xFFFF);
        if (mb1ev_snowmanHitTbl[i] != 0) {
            HuSprAttrSet(grp, 1, HUSPR_ATTR_FILTER_BILERP);
        } else {
            HuSprDispOff(grp, 1);
        }
        HuSprPriSet(grp, 1, 0x1000);
        HuSprPosSet(grp, 1, 0, -9);
        HuSprParentSet(grp, 1, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(grp, j + 2, numAnim[j], 0);
            HuSprAnimModeSet(grp, j + 2, HUSPR_ANIM_MODE_BANK);
            HuSprAttrReset(grp, j + 2, 0xFFFF);
            if (mb1ev_snowmanHitTbl[i] == j + 1) {
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
    for (angle = 90.0f, count = 0, fade = 0, flag = 0, alpha = 255;; angle += step) {
        if (angle >= 360.0f && flag == 0) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (fade == 0 && count != 0) {
            if (angle >= 90.0f && angle < 180.0f) {
                fade = 1;
            }
        }
        if (fade != 0) {
            alpha -= 21;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        HuSprTPLvlSet(titleGrp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprScaleSet(titleGrp, 0, 1.0f, 0.0f);
    HuSprGrpKill(titleGrp);
    HuSprAnimKill(titleAnim);
    proc->user_data = (void *)1;
    while (TRUE) {
        for (i = 0; i < 4; i++) {
            switch (mb1ev_snowmanHitTbl[i]) {
                case 0:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOff(grpId[i], j);
                    }
                    break;
                case 1:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grpId[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grpId[i], j + 2);
                    }
                    HuSprDispOn(grpId[i], 2);
                    break;
                case 2:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grpId[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grpId[i], j + 2);
                    }
                    HuSprDispOn(grpId[i], 3);
                    break;
                case 3:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grpId[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grpId[i], j + 2);
                    }
                    HuSprDispOn(grpId[i], 4);
                    break;
                case 4:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(grpId[i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(grpId[i], j + 2);
                    }
                    HuSprDispOn(grpId[i], 5);
                    break;
                default:
                    goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(helpWin);
    HuSprAnimKill(markAnim);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(numAnim[i]);
        HuSprAnimKill(charAnim[i]);
        HuSprGrpKill(grpId[i]);
    }
    omDelPrcObj(NULL);
}

void MB1Ev_SnowmanEffInit() {
    Object *temp_v0;

    temp_v0 = MBModelCreate(0x36, 0);
    mb1ev_snowmanEffMdl = temp_v0;
    MBModelDispOff(temp_v0);
}

void MB1Ev_SnowmanEffProc(void) {
    UnkThing *work;
    Object *obj;
    Object *src;

    //TODO: matching hack
    if (work) {
        work = HuPrcCurrentGet()->user_data;
        src = work->unk_04;
        obj = MBModelLinkCreate(mb1ev_snowmanEffMdl);
        MBMotionSet(obj, -1, work->unk_08);
        HuVecCopy3F(&obj->coords, &src->coords);        
    } else {
        work = HuPrcCurrentGet()->user_data;
        src = work->unk_04;
        obj = MBModelLinkCreate(mb1ev_snowmanEffMdl);
        MBMotionSet(obj, -1, work->unk_08);
        HuVecCopy3F(&obj->coords, &src->coords);
    }


    while ((MBMotionCheck(obj) == 0) && (work->unk_0C == 0)) {
        HuPrcVSleep();
    }

    MBModelKill(obj);
    omDelPrcObj(NULL);
}

Process* MB1Ev_SnowmanEffCreate(Object* arg0, Object* arg1, s32 arg2) {
    Process* temp_v0;
    UnkThing* temp_v0_2;

    temp_v0 = omAddPrcObj(MB1Ev_SnowmanEffProc, 0x4800U, 0, 0x40);
    temp_v0_2 = HuMemMemoryAlloc(temp_v0->heap, sizeof(UnkThing));
    temp_v0->user_data = temp_v0_2;
    temp_v0_2->unk_00 = arg0;
    temp_v0_2->unk_04 = arg1;
    temp_v0_2->unk_08 = arg2;
    temp_v0_2->unk_0C = 0;
    return temp_v0;
}
void MB1Ev_SnowmanEffClose() {
    MBModelKill(mb1ev_snowmanEffMdl);
}

void MB1Ev_SnowmanStart(void) {
    Vec pos;
    Vec dir;
    s32 order1[4];
    s32 order2[4];
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player;
    GW_PLAYER *curPlayer;
    SpaceData *space;
    SpaceData *prevSpace;
    Object *snowman;
    Process *proc;
    SnowmanRollWork *work;
    SnowmanRollWork *work2;
    s16 *masuList;
    s32 path;
    s16 count;
    s16 slot;
    s16 sfx;
    s32 swap;
    s32 temp;
    s32 n;
    s32 i;
    s32 j;
    f32 x;
    f32 z;

    MBPlayerGet(-1);
    mbItemBtnF = 0;
    mbTauntOffF = 1;
    path = (rand8() & 1) ? 2 : 0;
    count = MB1Ev_SnowmanPathGet(path);
    if (count != 0) {
        MB1Ev_SnowmanSpeedSet(-1);
    } else {
        MB1Ev_SnowmanSpeedSet(3);
    }
    MB1Ev_SnowmanEffInit();
    MBStatusHideAll();
    MBSaiNumKill(system->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    WipeCreateOut(WIPE_QUESTION, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    HuVecCopy3F(&pos, &MBMasuGet(0x8F)->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    MBCameraZoomSet(1.0f);
    if (MB1Ev_SnowmanPathPairGet(path)) {
        MBMasuDispOff();
    }

    space = MBMasuGet(mb1ev_snowmanEndMasuTbl[path]);
    j = mb1ev_snowmanEndMasuTbl[path];
    for (i = 0, n = 0; i < 4; i++) {
        if (MBMasuLinkMasuIdGet(MBPlayerGet(i)->clink, MBPlayerGet(i)->cidx) == j) {
            n++;
        }
    }
    count += n;
    n = (path == 0) ? 32 : 15;
    for (i = 0, slot = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == j) {
            switch (count) {
                case 2:
                    x = mb1ev_snowmanOfs2Tbl[slot][0];
                    z = mb1ev_snowmanOfs2Tbl[slot][1];
                    break;
                case 3:
                    x = mb1ev_snowmanOfs3Tbl[slot][0];
                    z = mb1ev_snowmanOfs3Tbl[slot][1];
                    break;
                case 4:
                    x = mb1ev_snowmanOfs4Tbl[slot][0];
                    z = mb1ev_snowmanOfs4Tbl[slot][1];
                    break;
                default:
                    z = x = 0.0f;
                    break;
            }
            player->player_obj->coords.x = x + space->coords.x;
            player->player_obj->coords.z = z + space->coords.z + 35.0f;
            slot++;
        } else if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == n) {
            player->player_obj->coords.z += 15.0f;
        }
    }
    WipeCreateIn(WIPE_QUESTION, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }

    if (MB1Ev_SnowmanPathPairGet(path) == 0) {
        MBDlgResultWinExec(0x200);
        WipeCreateOut(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuPrcSleep(5);
        MBCameraFocusModeSet(1);
        MBCameraZoomSet(1.3f);
        MBMasuDispOn();
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    } else {
        MB1Ev_SnowmanBaseEmptySet();
        HuPrcSleep(20);
        mb1ev_snowmanRollF = 1;
        HuPrcSleep(38);
        WipeCreateOut(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
        HuPrcSleep(5);
        MB1Ev_SnowmanBaseReset();
        HuVecCopy3F(&pos, &MBMasuGet(mb1ev_snowmanStartMasuTbl[path])->coords);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&pos);
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }

        MB1Ev_SnowmanPathGet(path);
        mb1ev_actionTimeProc = omAddPrcObj(MB1Ev_ActionTimeSpr, 0x4800, 0, 0);
        snowman = MBModelLinkCreate(mb1ev_snowmanMdl);
        mb1ev_snowmanRollMdl = snowman;
        Hu3DMotionAttrSet(snowman->omObj1->model[0], 1, 1);
        HuVecCopy3F(&snowman->coords, &MBMasuGet(mb1ev_snowmanPathMasuTbl[path][0])->coords);
        MBVecDirGet(&snowman->coords, &MBMasuGet(mb1ev_snowmanDirMasuTbl[path])->coords, &snowman->rot);
        snowman->velocity.x = 100.0f;
        MBModelJumpSet(snowman, 0.0f, -1.0f);
        MBModelJumpWait(snowman);
        MB1Ev_SnowmanEffCreate(NULL, mb1ev_snowmanRollMdl, 0);
        x = 8.0f;
        while (mb1ev_actionTimeProc->user_data == NULL) {
            for (i = 0; i < 4; i++) {
                if (mb1ev_snowmanHitTbl[i] != 0) {
                    MBPlayerVibrate(i, 4);
                }
            }
            HuAudFXPlay(0x186);
            MBModelJumpSet(snowman, x, -1.0f);
            MBModelJumpWait(snowman);
            x -= 1.0f;
            if (x <= 0.0f) {
                x = 3.0f;
            }
        }

        masuList = mb1ev_snowmanPathMasuTbl[path];
        for (i = 0; i < 4; i++) {
            order1[i] = i;
        }
        for (i = 0; i < 3; i++) {
            for (j = i + 1; j < 4; j++) {
                swap = 0;
                if (path != 0) {
                    if (MBPlayerGet(order1[i])->player_obj->coords.x < MBPlayerGet(order1[j])->player_obj->coords.x) {
                        swap = 1;
                    }
                } else {
                    if (MBPlayerGet(order1[i])->player_obj->coords.x > MBPlayerGet(order1[j])->player_obj->coords.x) {
                        swap = 1;
                    }
                }
                if (swap) {
                    swap = order1[i];
                    order1[i] = order1[j];
                    order1[j] = swap;
                }
            }
        }
        n = 0;
        do {
            for (i = 0; i < 4; i++) {
                curPlayer = MBPlayerGet(order1[i]);
                if (*masuList == MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx)) {
                    proc = omAddPrcObj(MB1Ev_SnowmanRoll, 0x4800, 0, 0x40);
                    proc->user_data = work = HuMemMemoryAlloc(proc->heap, sizeof(SnowmanRollWork));
                    work->player = order1[i];
                    work->unk04 = slot;
                    work->order = n;
                    work->path = path;
                    work->count = count;
                    n++;
                }
            }
            masuList++;
        } while (*masuList != -1);

        MBBackThreadPriLowSet();
        sfx = HuAudFXPlay(0x185);
        MBMotionSet(snowman, -1, 2);
        proc = MB1Ev_SnowmanMoveCreate(&snowman->coords, &MBMasuGet(mb1ev_snowmanDirMasuTbl[path])->coords,
                                          &snowman->coords, 0.0f);
        space = MBMasuGet(mb1ev_snowmanStartMasuTbl[path]);
        HuPrcChildLink(HuPrcCurrentGet(), MB1Ev_SnowmanMoveCreate(&pos, &space->coords, &pos, 0.0f));
        HuPrcChildWatch();
        MB1Ev_SnowmanMoveCreate(&pos, &MBMasuGet(mb1ev_snowmanStartMasuTbl[path + 1])->coords, &pos, 0.0f);
        HuPrcChildLink(HuPrcCurrentGet(), proc);
        HuPrcChildWatch();
        HuAudFXStop(sfx);

        path++;
        MBVecDirGet(&snowman->coords, &MBMasuGet(mb1ev_snowmanDirMasuTbl[path])->coords, &snowman->rot);
        Hu3DMotionAttrSet(snowman->omObj1->model[0], 1, 1);
        HuAudFXPlay(0x186);
        MBModelJumpSet(snowman, 5.0f, -0.2f);
        MBModelJumpWait(snowman);
        count = MB1Ev_SnowmanPathGet(path);
        MB1Ev_SnowmanEffCreate(NULL, mb1ev_snowmanRollMdl, 0);
        for (i = 0; i < 4; i++) {
            if (mb1ev_snowmanHitTbl[i] != 0) {
                MBPlayerVibrate(i, 4);
            }
        }
        MBMotionSet(snowman, -1, 2);
        HuAudFXPlay(0x186);
        MBModelJumpSet(snowman, 4.0f, -0.5f);
        MBModelJumpWait(snowman);
        for (i = 0; i < 4; i++) {
            if (mb1ev_snowmanHitTbl[i] != 0) {
                MBPlayerVibrate(i, 4);
            }
        }
        HuAudFXPlay(0x186);
        MBModelJumpSet(snowman, 2.0f, -0.5f);
        MBModelJumpWait(snowman);
        for (i = 0; i < 4; i++) {
            if (mb1ev_snowmanHitTbl[i] != 0) {
                MBPlayerVibrate(i, 4);
            }
        }

        if (MB1Ev_SnowmanPathGet(path) == 0) {
            mb1ev_snowmanHitTbl[0] = -1;
            sfx = HuAudFXPlay(0x185);
        } else {
            MB1Ev_SnowmanSpeedSet(-1);
            space = MBMasuGet(mb1ev_snowmanEndMasuTbl[path]);
            j = mb1ev_snowmanEndMasuTbl[path];
            for (i = 0, n = 0; i < 4; i++) {
                if (MBMasuLinkMasuIdGet(MBPlayerGet(i)->clink, MBPlayerGet(i)->cidx) == j) {
                    n++;
                }
            }
            count += n;
            for (i = 0, slot = 0; i < 4; i++) {
                player = MBPlayerGet(i);
                if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == j) {
                    switch (count) {
                        case 2:
                            x = mb1ev_snowmanOfs2Tbl[slot][0];
                            z = mb1ev_snowmanOfs2Tbl[slot][1];
                            break;
                        case 3:
                            x = mb1ev_snowmanOfs3Tbl[slot][0];
                            z = mb1ev_snowmanOfs3Tbl[slot][1];
                            break;
                        case 4:
                            x = mb1ev_snowmanOfs4Tbl[slot][0];
                            z = mb1ev_snowmanOfs4Tbl[slot][1];
                            break;
                        default:
                            z = x = 0.0f;
                            break;
                    }
                    player->player_obj->coords.x = x + space->coords.x;
                    player->player_obj->coords.z = z + space->coords.z;
                    slot++;
                    if (path == 1) {
                        f32 ofs = 20.0f;
                        player->player_obj->coords.x -= ofs;
                    }
                }
            }

            masuList = mb1ev_snowmanPathMasuTbl[path];
            for (i = 0; i < 4; i++) {
                order2[i] = i;
            }
            for (i = 0; i < 3; i++) {
                for (j = i + 1; j < 4; j++) {
                    if (MBPlayerGet(order2[i])->player_obj->coords.z > MBPlayerGet(order2[j])->player_obj->coords.z) {
                        temp = order2[i];
                        order2[i] = order2[j];
                        order2[j] = temp;
                    }
                }
            }
            n = 0;
            do {
                for (i = 0; i < 4; i++) {
                    curPlayer = MBPlayerGet(order2[i]);
                    if (*masuList == MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx)) {
                        proc = omAddPrcObj(MB1Ev_SnowmanRoll, 0x4800, 0, 0x40);
                        proc->user_data = work2 = HuMemMemoryAlloc(proc->heap, sizeof(SnowmanRollWork));
                        work2->player = order2[i];
                        work2->unk04 = slot;
                        work2->order = n;
                        work2->path = path;
                        work2->count = count;
                        n++;
                    }
                }
                masuList++;
            } while (*masuList != -1);

            sfx = HuAudFXPlay(0x185);
            space = MBMasuGet(mb1ev_snowmanDirMasuTbl[path]);
            HuPrcChildLink(HuPrcCurrentGet(),
                           MB1Ev_SnowmanMoveCreate(&snowman->coords, &space->coords, &snowman->coords, 0.0f));
            MB1Ev_SnowmanMoveCreate(&pos, &MBMasuGet(mb1ev_snowmanDirMasuTbl[path])->coords, &pos, 0.0f);
            HuPrcChildWatch();
            mb1ev_snowmanHitTbl[0] = -1;
        }

        WipeCreateOut(WIPE_QUESTION, 16);
        space = MBMasuGet(mb1ev_snowmanDirMasuTbl[path]);
        prevSpace = MBMasuGet(mb1ev_snowmanDirMasuTbl[path - 1]);
        while (WipeStatGet()) {
            MBVecDirGet(&prevSpace->coords, &space->coords, &dir);
            x = atan2df(dir.x, -dir.z);
            snowman->coords.x += sindf(x) * mb1ev_snowmanSpeed;
            snowman->coords.z -= cosdf(x) * mb1ev_snowmanSpeed;
            HuPrcVSleep();
        }
        HuPrcSleep(5);
        HuAudFXStop(sfx);
        for (i = 0; i < 4; i++) {
            MBPlayerPosFixSet(i, 1);
        }
        MBCameraFocusModeSet(1);
        MBModelKill(snowman);
        mb1ev_snowmanRollF = 0;
        MBMasuDispOn();
        MBBackThreadPriHighSet();
        WipeCreateIn(WIPE_QUESTION, 16);
        while (WipeStatGet()) {
            HuPrcVSleep();
        }
    }
    MB1Ev_SnowmanEffClose();
    MBStatusShowAll();
    mbTauntOffF = 0;
    mbItemBtnF = 1;
    omDelPrcObj(NULL);
}

void MB1Ev_Snowman(void) {
    Process* proc;
    Process* objProc;
    s32 sel;
    GW_SYSTEM* system = &GwSystem;

    MBSaiNumKill(system->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    MBPlayerRotMasuStart(-1, 8, 0x80);
    proc = HuPrcCurrentGet();
    HuPrcChildLink(proc, MBCameraZoomMotStart(1.6f));
    HuPrcChildWatch();
    MB1Ev_SnowmanBaseEmptySet();
    HuPrcSleep(10);
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(0x37, 0x204);
        MB1Ev_SnowmanBaseReset();
    } else {
        choiceLoop:
        MBDlgWinInsertCreate(0x37, 0x201, 0, 0, 0, 0, 0);
        sel = MB1Ev_YesNoChoiceGet(mb1ev_snowmanComTree, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (sel) {
        case 0:
            MBCoinChangeCreate(system->current_player_index, -5);
            MBCoinTakeCreate(system->current_player_index, -5);
            HuPrcSleep(0x1E);
            MBDlgWinExec(0x37, 0x202);
            objProc = omAddPrcObj(MB1Ev_SnowmanStart, 0x4800, 0, 0);
            HuPrcChildLink(HuPrcCurrentGet(), objProc);
            HuPrcChildWatch();
            break;
        case 1:
            MBDlgWinExec(0x37, 0x203);
            MB1Ev_SnowmanBaseReset();
            break;
        default:
            MB1_MapScroll();
            goto choiceLoop;
        }
    }
    MBSaiNumShow(system->current_player_index);
    objProc = HuPrcCurrentGet();
    HuPrcChildLink(objProc, MBCameraZoomMotStart(1.3f));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

void MB1Ev_LakeWaveProc(void) {
    SpaceData *space;
    f32 scale;
    s32 model;
    s32 idx;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;

    HuPrcSleep(mb1ev_lakeWaveTbl[idx][1]);
    model = Hu3DModelRead2(0x130165, 0x689);
    Hu3DModelObjAttrSet(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    Hu3DModelVtxBufMake(model);
    Hu3DModelDynamicFree(model);
    Hu3DModelScaleSet(model, MBBackMdlScaleGet(), MBBackMdlScaleGet(), MBBackMdlScaleGet());
    Hu3DModelCameraSet(model, HU3D_CAM0);

    space = MBMasuGet(mb1ev_lakeWaveTbl[idx][0]);
    Hu3DModelScaleSet(model, MBBackMdlScaleGet(), MBBackMdlScaleGet(), MBBackMdlScaleGet());
    Hu3DModelPosSet(model, space->coords.x, space->coords.y, space->coords.z);

    for (i = 0, scale = 0.1f; i < 0x1E; i++) {
        scale += 0.03f;
        Hu3DModelVtxWave(model, scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }

    Hu3DModelKill(model);
    omDelPrcObj(NULL);
}

s32 MB1Ev_LakeJumpDelayGet(s32 arg0) {
    s32 var_v1 = 1;

    switch (arg0) {
    case 0x46:
    case 0x47:
    case 0x57:
    case 0x5A:
        var_v1 = 1;
        break;
    case 0x3A:
    case 0x3B:
    case 0x3C:
    case 0x54:
    case 0x55:
    case 0x56:
        var_v1 = 0x14;
        break;
    case 0x3D:
    case 0x3E:
        var_v1 = 0x28;
        break;
    }
    return var_v1;
}

void MB1Ev_LakePlayerJumpProc(void) {
    Vec dest;
    GW_PLAYER *player;
    Object *obj;
    Vec *coords;
    s32 other;
    s32 playerNo;
    s32 side;
    GW_SYSTEM* system = &GwSystem;

    playerNo = (s32)HuPrcCurrentGet()->user_data;
    player = MBPlayerGet(playerNo);
    obj = player->player_obj;

    HuPrcSleep(MB1Ev_LakeJumpDelayGet(
        MBMasuLinkMasuIdGet(player->clink, player->cidx)));
    MBPlayerRotMasuStart(playerNo, 8, 0x8E);
    HuPrcSleep(8);
    MBModelJumpSet(obj, 5.0f, -1.0f);
    HuPrcSleep(0xA);
    MBPlayerRotMasuStart(playerNo, 1, 0x78);
    MBPlayerMotionLoad(playerNo, 5, 0x1A);
    MBMotionSet(obj, 1, 2);

    if (playerNo == GwSystem.current_player_index) {
        player = MBPlayerGet(GwSystem.boardData.halfWordBytes[0]);
    } else {
        player = MBPlayerGet(-1);
    }

    if (obj->coords.x < player->player_obj->coords.x) {
        side = 0;
    } else {
        side = 1;
    }

    PlayerFXPlay(0x286, playerNo);
    HuVecCopy3F(&dest, &MBMasuGet(0x78)->coords);
    dest.x += mb1ev_lakeJumpOfsTbl[side][0];
    dest.z += mb1ev_lakeJumpOfsTbl[side][1];
    HuPrcChildLink(HuPrcCurrentGet(),
                   MBVecSpeedMoveCreate(&obj->coords, &dest, &obj->coords, 2.0f));
    HuPrcChildWatch();
    omDelPrcObj(NULL);
}

void MB1Ev_LakeIceBreakProc(void) {
    Vec pos;
    f32 sp28[2];
    Vec offset;
    GW_PLAYER *player;
    GW_PLAYER *other;
    Object *playerObj;
    Object *otherObj;
    Process *proc;
    SpaceData *space;
    s32 sprId;
    s32 motId;
    f32 angle;
    s32 i;
    u32 j;
    u16* temp;
    f32 tempFloat;

    playerObj = MBPlayerGet(CUR_PLAYER)->player_obj;
    otherObj = MBPlayerGet(GwSystem.boardData.halfWordBytes[0])->player_obj;

    MBStatusHideAll();
    MBMasuDispOff();
    mbTauntOffF = 1;

    HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.0f));
    HuPrcChildWatch();

    space = MBMasuGet(0x7D);
    HuVecCopy3F(&pos, &playerObj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 5));
    HuPrcChildWatch();
    HuPrcSleep(0xF);

    MBPlayerVibrate(-1, 4);
    MBPlayerVibrate(GwSystem.boardData.halfWordBytes[0], 4);
    HuAudFXPlay(0x183);
    
    tempFloat = pos.z;
    
    for (angle = 0.0f; angle < 2700.0f; angle += 90.0f) {
        HuVecCopyXYZ(&pos, pos.x, pos.y, tempFloat + (sindf(angle)* 3.0f));
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&pos, pos.x, pos.y, pos.z);

    MBPlayerVibrate(-1, 2);
    MBPlayerVibrate(GwSystem.boardData.halfWordBytes[0], 2);
    HuAudFXPlay(0x184);

    HuVecCopyXYZ(&offset, 0.0f, 0.0f, -12.0f);
    MBCamera3Dto2D(&offset, &sp28[0]);
    sprId = MB1Ev_IceCrackCreate(sp28[0], sp28[1]);

    proc = (void*)0;
    omAddPrcObj(MB1Ev_LakeWaveProc, 0x4800, 0, 0)->user_data = (void *)proc;
    proc = (void*)1;
    omAddPrcObj(MB1Ev_LakeWaveProc, 0x4800, 0, 0)->user_data = (void *)proc;
    proc = (void*)2;
    omAddPrcObj(MB1Ev_LakeWaveProc, 0x4800, 0, 0)->user_data = (void *)proc;
    proc = (void*)3;
    omAddPrcObj(MB1Ev_LakeWaveProc, 0x4800, 0, 0)->user_data = (void *)proc;

    proc = omAddPrcObj(MB1Ev_LakePlayerJumpProc, 0x4800, 0, 0);
    proc->user_data = (void*)(s32)GwSystem.current_player_index;
    HuPrcChildLink(HuPrcCurrentGet(), proc);
    proc = omAddPrcObj(MB1Ev_LakePlayerJumpProc, 0x4800, 0, 0);
    proc->user_data = (void*)(s32)GwSystem.boardData.halfWordBytes[0];
    HuPrcChildLink(HuPrcCurrentGet(), proc);

    HuPrcSleep(0x32);
    HuPrcSleep(0xA);
    WipeCreateOut(WIPE_FADE, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    //TODO: matching hack. The if and else have the same code, so the if statement is pointless
    if (angle) {
        HuPrcChildWatch();
        player = MBPlayerGet(CUR_PLAYER);
        other = MBPlayerGet(GwSystem.boardData.halfWordBytes[0]);
    } else {
        HuPrcChildWatch();
        player = MBPlayerGet(CUR_PLAYER);
        other = MBPlayerGet(GwSystem.boardData.halfWordBytes[0]);
    }
    player->clink = other->clink = 0x10;
    player->cidx = other->cidx = 0;
    player->nlink = other->nlink = 0x10;
    player->nidx = other->nidx = 1;
    player->blink = other->blink = 0x10;
    player->bidx = other->bidx = 1;
    player->rev &= ~FLAG_REV;
    other->rev &= ~FLAG_REV;
    HuVecCopyXYZ(&playerObj->rot, 0.0f, 0.0f, 0.0f);
    HuVecCopyXYZ(&otherObj->rot, 0.0f, 0.0f, 0.0f);
    
    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        MBPlayerPosFixSet(i, 1);
    }
    HuPrcVSleep();

    //TODO: this is all kinds of a mess, what was this originally?
    MOTION_ID_GET(6, temp, j);
    
    MBPlayerMotionLoad(GwSystem.current_player_index, 5, motId);
    MBPlayerMotionLoad(GwSystem.boardData.halfWordBytes[0], 5, motId);
    MBPlayerMotionShiftSet(-1, -1, 0, 5, 2);
    MBMotionShiftSet(otherObj, -1, 0, 5, 2);

    MBCameraFocusModeSet(1);
    MBCameraZoomSet(1.3f);
    MBStatusShowAll();
    MB1Ev_IceCrackKill(sprId);
    WipeCreateIn(WIPE_FADE, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    HuPrcSleep(0xA);
    MBDlgResultWinExec(0x101);
    GWBoardFlagSet(0x12);
    HuPrcSleep(0x14);
    mbTauntOffF = 0;
    omDelPrcObj(NULL);
}

void MB1Ev_Lake(void) {
    GW_PLAYER *player;
    s16 *masu;
    s32 i;

    masu = mb1ev_lakeMasuTbl;

    while (*masu != -1) {
        for (i = 0; i < MB_MAX_PLAYERS; i++) {
            if (i != GwSystem.current_player_index) {
                player = MBPlayerGet(i);
                if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == *masu) {
                    goto exit;
                }
            }
        }
        masu++;
    }

    exit:
    if (*masu != -1) {
        GwSystem.boardData.halfWordBytes[0] = i;
        HuPrcChildLink(HuPrcCurrentGet(),
                       omAddPrcObj(MB1Ev_LakeIceBreakProc, 0x4800, 0, 0));
        HuPrcChildWatch();
    } else {
        MBDlgResultWinExec(0x100);
    }

    omDelPrcObj(NULL);
}

// entrypoint 4
void MB1Ev_OpStarMapView(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &mb1ev_opStarMapViewRect);
    MB1_ObjectSetup();
    MBStart(2);
    omAddPrcObj(MB1Ev_StarMapView, 0x1005, 0x1000, 0);
}

s32 MB1_ComNKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    for (i = 0, bestRank = 99, best = MBPlayerTurnGet(); i < 4; i++) {
        if (i != MBPlayerTurnGet()) {
            MBComTreePlayerSet(i);
            if ((MBComTreeExec(mb1_itemNKinokoStarComTree) == 0) &&
                (MBPlayerRankCalc(i) < bestRank)) {
                bestRank = MBPlayerRankCalc(i);
                best = i;
            }
        }
    }
    return best;
}

s32 MB1_ComRKinokoTargetGet(void) {
    s32 best;
    s32 bestRank;
    s32 i;

    best = MBPlayerTurnGet();
    if (MBComTreeExec(mb1_itemRKinokoStarComTree) != 0) {
        for (i = 0, bestRank = 99; i < 4; i++) {
            if (i != MBPlayerTurnGet()) {
                MBComTreePlayerSet(i);
                if ((MBComTreeExec(mb1_itemRKinokoTargetComTree) == 0) &&
                    (MBPlayerRankCalc(i) < bestRank)) {
                    bestRank = MBPlayerRankCalc(i);
                    best = i;
                }
            }
        }
    }
    return best;
}

s32 MB1_ComItemExcessCheck() {
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

s32 MB1_ComRobItemSafeCheck(s32 arg0, s32 arg1) {
    s32 ret;
    s32 i;
    s32 j;

    ret = 1;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i != GwSystem.current_player_index) {
            for (j = 0; j < ARRAY_COUNT(GwPlayer->itemNo); j++) {
                if ((GwPlayer[i].itemNo[j] == ITEM_PLUNDER_CHEST) ||
                    (GwPlayer[i].itemNo[j] == ITEM_BARTER_BOX)) {
                    break;
                }
            }
            if (j < 3) {
                break;
            }
        }
    }

    if ((i < MB_MAX_PLAYERS) && MBRandCheck100(arg0 + (arg1 * GwPlayer[i].cpu_difficulty)) != 0) {
        ret = 0;
    }

    return ret;
}

s32 MB1_ComItemDecide(void) {
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
                if (MB1_ComItemExcessCheck() != 0) {
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
                if (MBRandCheck100(70) != 0 && MB1_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (MB1_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb1_itemSKinokoComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (MB1_ComItemExcessCheck() != 0) {
                    break;
                }
                if (MBComTreeExec(mb1_itemKSuitComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(mb1_itemWarpBlockComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(mb1_itemNKinokoComTree) == 0) {
                    s32 target = MB1_ComNKinokoTargetGet();

                    mb1_comNKinokoTarget = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(mb1_itemRKinokoComTree) == 0) {
                    s32 target = MB1_ComRKinokoTargetGet();

                    mb1_comRKinokoTarget = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, mb1_comRobBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < mbItemComWeightTbl[it]) {
                                    best = mbItemComWeightTbl[it];
                                    mb1_comRobBoxTarget = i;
                                }
                            }
                        }
                    }
                }
                if (mb1_comRobBoxTarget == -1) {
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
                for (i = 0, mb1_comExchangeBoxTarget = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += mbItemComWeightTbl[it];
                            }
                        }
                        if (best < count) {
                            mb1_comExchangeBoxTarget = i;
                            best = count;
                        }
                    }
                }
                if (mb1_comExchangeBoxTarget == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (MB1_ComRobItemSafeCheck(0x32, 0xA) == 0) {
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
                if (MB1_ComRobItemSafeCheck(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(mb1_itemMajinLampComTree) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && MB1_ComItemExcessCheck() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(mb1_itemStarYokeComTree) != 0) {
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

s32 MB1_ComShopItemDecide(void) {
    s32 sp14;
    GW_PLAYER* temp_s3;
    s32 var_s1_2;
    s32 temp_v0;
    s32 var_s2;
    s32 var_s2_2;
    s32 temp_s0;
    u8 temp_s0_2;
    s32 i;
    GW_SYSTEM* system = &GwSystem;

    temp_s3 = MBPlayerGet(CUR_PLAYER);
    sp14 = 1;

    for (i = 0; i < 16; i++) {
        temp_s0 = mb1_comShopItemOrderTbl[temp_s3->chr][i];
        var_s2 = MB1Ev_ShopItemIdxGet(temp_s0);
        if (var_s2 != -1 && mbItemPriceTbl[temp_s0] + 20 <= GwPlayer[system->current_player_index].coin &&
            MBRandCheck100(mb1_comShopItemRateTbl[temp_s3->chr][i])) {
            break;
        }
    }
    if (i == 16) {
        var_s2 = -1;
    }

    if (var_s2 != -1) {
        if ((MB1Ev_ShopItemIdxGet(0xE) != var_s2) &&
        ((MB1Ev_ShopItemIdxGet(0xB) != var_s2) ||
        ((mbItemPriceTbl[0xB] + 50) > (GwPlayer[system->current_player_index].coin)) != 0)) {
            if ((MB1Ev_ShopItemIdxGet(4) == var_s2) &&
            (MBItemFind(system->current_player_index, 4) != -1)) {
                var_s2 = -1;
                sp14 = 0;
            }
        } else {
            return var_s2 + 1;
        }
    }
    if ((MBComTreeExec(mb1_comShopKeyComTree[mb1ev_shopNo]) == 0) && GwPlayer[system->current_player_index].coin >= mbItemPriceTbl[1]) {
        temp_v0 = MB1Ev_ShopItemIdxGet(1);
        if (temp_v0 != -1) {
            return temp_v0 + 1;
        }
    }
    if (var_s2 == -1) {
        i = MBComTreeExec(mb1_comShopItemComTree[mb1ev_shopNo]);
        if (i == 0) {
            do {
                temp_s0_2 = mb1_comShopItemOrderTbl[temp_s3->chr][i];
                //this line below has to be written very specific
                if ((temp_s0_2 == 4 && sp14 == 0) == 0) {
                    var_s2_2 = MB1Ev_ShopItemIdxGet(temp_s0_2);
                    if ((var_s2_2 != -1) && !(mbItemPriceTbl[temp_s0_2] > (GwPlayer[system->current_player_index].coin))) {
                        if ((MBRandCheck100(mb1_comShopItemRateTbl[temp_s3->chr][i]))) {
                            return var_s2_2 + 1;
                        }
                    }
                }
            } while (++i < 16);
        }

        var_s2_2 = MB1Ev_ShopItemIdxGet(0);
        if (var_s2_2 == -1) {
            mb1_comShopCancelF = 1;
            return MB1Ev_ShopItemNumGet() + 2;
        }
        return var_s2_2 + 1;
    }
    return var_s2 + 1;
}

s32 MB1_ComShopEnterDecide(void) {
    if (mb1_comShopCancelF != 0) {
        mb1_comShopCancelF = 0;
        return 2;
    }
    return MBComTreeExec(mb1_comShopEnterComTree[mb1ev_shopNo]) + 1;
}
