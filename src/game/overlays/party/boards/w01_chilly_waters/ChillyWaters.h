#include "common_board.h"
#include "game/mallocblock.h"
#include "game/board.h"

void MB1Ev_StarShuffle(void);
void MB1Ev_StarNextPos(void);
void MB1Ev_StarMasuInit(void);
void MB1Ev_StarMapView(void);
void MB1_StarGuideCreateAll(void);
void MB1_TeresaGuideCreateAll(void);
void MB1_BankCoinCreateAll(void);
void MB1_GateCreateAll(void);
void MB1_BankMapIconAddAll(void);
void MB1_ShopMapIconAddAll(void);
void MB1Ev_BranchMerge(s32 masuAbsIndex, s16 arg1, s16 arg2);
void MB1Ev_KinokoMarkCreateAll(void);
void MB1Ev_TuruturuMain(void);
void MB1Ev_SnowmanObjMain(void);
void MB1Ev_SnowmanRoll(void);
s32 MB1Ev_SnowmanPathGet(s32);
void MB1Ev_Teresa(void);
void MB1Ev_ItemMajinLamp(void);
void MB1Ev_ItemMajinLampStar(void);
void MB1Ev_ItemWarpBlock(void);
void MB1Ev_ItemKinoko(void);
void MB1Ev_ItemShake(void);
void MB1Ev_ItemPhoneMove(void);
void MB1Ev_KSuitStart(void);
void MB1Ev_KSuitEnd(void);
void MB1Ev_ItemShopPhone(void);
void MB1Ev_ItemKoopaPhone(void);
void MB1Ev_ItemStarYoke(void);
void MB1Ev_ItemKeyManUse(void);
void MB1Ev_ItemNullUse(void);
void MB1Ev_ItemExchangeBox(void);
void MB1Ev_ItemGambleCoin(void);
void MB1Ev_ItemAfter5(void);
void MB1Ev_ItemKoopaNKinoko(void);
void MB1Ev_ItemNKinoko(void);
void MB1Ev_ItemKoopaRKinoko(void);
void MB1Ev_ItemRKinoko(void);
void MB1Ev_ItemRobBox(void);
s32 MB1_ComItemDecide(void);
void MB1_ObjectSetup(void);
void MB1Ev_SnowmanStart(void);
void MB1_BankCoinHide(void);
void MB1_BankCoinCreate(s16);

s16 MBComTreeExec(DecisionTreeNonLeafNode *arg0);
void MB1_BranchHelpEnd(void);
void MB1Ev_BranchMain(s16 (*masu)[3], BranchLink (*links)[2], DecisionTreeNonLeafNode **trees);

void MB1Ev_After5LineShow(omObjData*);
void MB1Ev_After5NumFade(omObjData*);
void MB1Ev_After5Effect(void);
void MB1Ev_After5ItemMove(s32, s32, f32*);
s32 MB1_ComShopItemDecide(void);
s32 MB1_ComShopEnterDecide(void);
s32 MB1Ev_YesNoChoiceGet(DecisionTreeNonLeafNode *arg0, s32 arg1);

#ifndef NO_EXTERN_VARIABLES
extern s32 mbWalkNum;
extern RGB mb1ev_after5NumColorTbl[2];
extern s32 mb1ev_after5GrpId[4];
extern void* mb1ev_after5EffMdl;
extern Object *mb1ev_snowmanBaseMdl;
extern Object *mb1ev_snowmanBaseEmptyMdl;
extern Object* mb1_bankCoinBaseMdl;
extern Object* mb1_bankCoinMdl[10];
extern omObjData *omSysTimerObj;
extern event_table_entry mb1_commonEventTbl[]; //unknown type
extern event_table_entry mb1_teresaEventTbl[]; //unknown type
extern event_table_entry mb1_turnStatusEventTbl[]; //unknown type
extern event_table_entry mb1_specialEventTbl[]; //unknown type
extern RectF mb1ev_opStarMapViewRect;
extern s16 mb1ev_starGuideMasu[8];
extern s16 mb1_masuBlockExtTbl; //unknown type
extern s16 mb1_masuBlockTbl[]; //unknown type
extern s16 mb1ev_starFlag[STAR_POSITIONS_TOTAL];
extern s16 mb1ev_starMasu[STAR_POSITIONS_TOTAL];
extern s16 mb1ev_starOrderTbl[STAR_POSITIONS_TOTAL];
extern s16 mb1ev_starOrderGroupTbl[STAR_POSITIONS_TOTAL];
extern Unk3* mb1_branchStickHelp;
extern Unk3* mb1_branchBtnHelp;
extern Unk3* mb1_branchMapScrollHelp;
extern Unk3* mb1_branchMapOverheadHelp;
extern Unk3* mb1_branchItemHelp;
extern Object *mb1ev_snowmanEffMdl;
extern DecisionTreeNonLeafNode *mb1ev_branch3RevComTree[];  // ai
extern s16 mb1ev_branch3RevMasu[][3];                       // spaces
extern BranchLink mb1ev_branch3RevLink[][2];                // chain
extern DecisionTreeNonLeafNode *mb1ev_branch2ComTree[];     // ai
extern s16 mb1ev_branch2Masu[][3];                          // spaces
extern BranchLink mb1ev_branch2Link[][2];                   // chain
extern s16 mb1ev_branch2RevMasu[][3];             // spaces
extern BranchLink mb1ev_branch2RevLink[][2];      // chain
extern DecisionTreeNonLeafNode *mb1ev_branch2RevComTree[];  // ai
extern s16 mb1ev_branch14Masu[][3];             // spaces
extern BranchLink mb1ev_branch14Link[][2];      // chain
extern DecisionTreeNonLeafNode *mb1ev_branch14ComTree[];  // ai
extern DecisionTreeNonLeafNode *mb1ev_branch3ComTree[];  // ai
extern s16 mb1ev_branch3Masu[][3];                    // spaces
extern BranchLink mb1ev_branch3Link[][2];             // links
extern DecisionTreeNonLeafNode *mb1ev_branch12ComTree[];
extern s16 mb1ev_branch12Masu[][3];
extern BranchLink mb1ev_branch12Link[][2];
#endif
