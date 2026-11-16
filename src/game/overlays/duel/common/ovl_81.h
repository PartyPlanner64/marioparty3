#include "common_duel.h"
#include "game/object.h"
#include "game/board.h"
#include "game/window.h"
#include "game/malloc.h"

typedef void (*PartnerFunc)(s32, s32, Object*, Object*, s32, s32);

typedef enum PartnerObjIndex {
    /* 0 */ PARTNEROBJINDEX_FRONT,
    /* 1 */ PARTNEROBJINDEX_BACK,
    /* 2 */ PARTNEROBJINDEX_MAX = MBD_MAX_PLAYERS,
} PartnerObjIndex;

#define POWERUP_NONE 1
#define POWERUP_ACTIVE 2

#define PARTNER_FRONT 0
#define PARTNER_BACK 1

typedef struct PartnerBaseAttributes {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 hp;
    /* 0x02 */ s8 power;
    /* 0x03 */ s8 cost;
    /* 0x04 */ PartnerFunc func1;
    /* 0x08 */ PartnerFunc func2;
    /* 0x0C */ void (*func3)(void);
    /* 0x10 */ void (*func4)(void);
} PartnerBaseAttributes; //sizeof 0x14

typedef struct UnkBoard4 {
    /* 0x00 */ struct UnkBoard4* unk_00; //TODO: is this correct?
    /* 0x04 */ struct UnkBoard4* unk_04; //TODO: is this correct?
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ s16* unk_0C;
    /* 0x10 */ f32* unk_10;
    /* 0x14 */ f32* unk_14;
    /* 0x18 */ s16* unk_18;
    /* 0x1C */ s16* unk_1C;
} UnkBoard4; //sizeof 0x20

typedef struct UnkBoard5 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ Object* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
} UnkBoard5; //sizeof 0x20

typedef struct UnkOvl81_2 {
    /* 0x00 */ Object* obj;
    /* 0x04 */ Process* process;
    /* 0x08 */ s16 win_id;
    /* 0x0A */ s16 unk_0A;
} UnkOvl81_2; //sizeof 0xC

// Duel help window, counterpart of the board overlay's Unk3.
typedef struct DuelHelpWin {
    /* 0x00 */ u8 unk_00; // message index
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ s16 unk_02; // x position, or -1 to center
    /* 0x04 */ s16 unk_04; // y position
    /* 0x08 */ omObjData* unk_08;
    /* 0x0C */ s16 winID;
    /* 0x10 */ char* unk_10;
} DuelHelpWin; //sizeof 0x14

typedef struct UnkC5770B70 {
    /* 0x00 */ s16 windowId;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 w;
    /* 0x08 */ s16 h;
} UnkC5770B70; // sizeof 0xA

// Space form image: a CI texture with a header, palette and texels.
typedef struct MasuBmp {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ u32 palCount;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u16 data[1];
} MasuBmp;

typedef struct UnkD6B00 {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Object *unk_04;
    /* 0x08 */ omObjData *unk_08;
} UnkD6B00; // sizeof 0xC

typedef struct NameSpriteIds {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02[2];
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
} NameSpriteIds; // sizeof 0xC

typedef struct NamePlayerData {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ s8 unk_01;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 spriteGroup;
    /* 0x06 */ char unk_06[0x2];
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ char unk_0A[0x2];
    /* 0x0C */ f32 xPos;
    /* 0x10 */ f32 yPos;
    /* 0x14 */ f32 unk_14;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk_28;
    /* 0x2C */ omObjData *unk_2C;
    /* 0x30 */ char unk_30[0x4];
    /* 0x34 */ s16 unk_34;
    /* 0x36 */ char unk_36[0x4];
    /* 0x3A */ s16 unk_3A[11];
    /* 0x50 */ s16 unk_50[11];
    /* 0x66 */ char unk_66[0x4];
    /* 0x6A */ s8 unk_6A;
    /* 0x6B */ s8 unk_6B;
} NamePlayerData; // sizeof 0x6C

typedef struct UnkE3CD0 {
    char unk_00[0xC];
    Vec unk_0C;
    char unk_18[0x18];
    f32 unk_30;
} UnkE3CD0;

#ifndef NO_EXTERN_VARIABLES
extern UnkBoard4* mbdSprGrpListHead;
extern u16 mbdSprGrpNum;
extern PartnerBaseAttributes PartnersBaseStats[];
extern Object* mbdPartnerObj[][PARTNEROBJINDEX_MAX];
extern process_func mbdHatenaFunc;
extern s32 (*mbdWalkAttackHook)(void);
extern void (*mbdWalkEndHook)(void);
extern s16 mbdExitFlag;
extern s16 mbdExitMusFadeF;
extern s32 mbdCoinScatterNum;
extern s32 mbdCoinScatterDoneNum;
extern Object* mbdCoinScatterMdl;
extern void (*mbdCoinScatterHook)(void);
extern s32* mbdPartnerMdlMotTbl[];
extern Process* mbdPartnerProc;
extern s32* mbdPartnerAttackMotFileTbl[];
extern s16 mbdPartnerAttackMotNum;
extern s16 mbdPartnerAttackMotTbl[];
extern s32* mbdPartnerExtMotFileTbl[];
extern s16 mbdPartnerExtMotTbl[];
extern s16 mbdPartnerExtMotNum;
extern s32 mbdPartnerDescMesTbl[];
extern s16 mbdPartnerDescFaceTbl[];
extern s16 mbdDlgWinId;
extern s16 mbdDlgWinTabWidth;
extern s16 mbdDlgWinAllKeyF;
extern Process* mbdAuraHoverProc;
extern u8 mbdComLevelTbl[];
extern Object* mbdModelListHead;
extern s16 mbdMotionRefTbl[];
extern s16 mbdItemWarpPlayerA;
extern s16 mbdItemWarpPlayerB;
extern s16 mbdWarpLink;
extern s16 mbdWarpIdx;
extern s16 mbdWarpBackLink;
extern s16 mbdWarpBackIdx;
extern Vec mbdWarpPosA;
extern Vec mbdWarpPosB;
extern Vec mbdWarpPosC;
extern s16 duelUnkF0;
#endif

void MBDBackKill(void);
void MBDBackClose(void);
void MBDMesSpeedSet(s16);
void MBDMasuLinkIdxGet(s16 spaceIdx, s8 *chainOut, s8 *linkOut);
void MBDBackRefresh(Vec *, s32);
void MBDWarpMasuExec(s32, s32, s32, s32);
void MBDItemWarpBlockSwapInit(void);
void MBDPlayerMasuSwap(s16 playerNoOne, s16 playerNoTwo);
void MBDVecForwardSet(Vec *);
void MBDPlayerComLevelSet(s32 playerIndex, u8 cpuDifficulty);
void MBDPlayerScaleSet(s32, Vec *);
Object *MBDAuraCreate(Vec *);
void MBDAuraLandNoSe(s32);
void MBDAuraHoverStart(void);
void MBDAuraHoverStop(void);
void MBDAuraKill(void);
void MBDAuraSpinExec(s32);
void MBDSaveInit(void);
void MBDExit(void);
void MBDBoardReturnOff(void);
void MBDModelClose(void);
void MBDSaiClose(void);
void MBDMgCallClose(void);
void MBDCoinChangeClose(void);
void MBDTelopClose(void);
void MBDBackReset(void);
void MBDBackSprKillAll(void);
void MBDMasuClose(void);
void MBDMasuKill(void);
void MBDPlayerClose(void);
void MBDSprGrpClose(void);
void MBDTurnHelpKill(void);
void MBDSaiValueClear(void);
void MBDMgCallHisInit(void);
void MBDBackSprDispOn(void);
void MBDBackSprDispOff(void);
s32 MBDPlayerComCheck(s16 playerIndex);
void MBDPlayerCoinAdd(s32 playerIndex, s32 amount);
DuelHelpWin* MBDHelpWinCreate(s16, s16, u16);
DuelHelpWin* MBDHelpWinCreateEx(s16, s16, s16, u16);
void MBDHelpWinKill(DuelHelpWin*);
Process* MBDMgCallCreate(void);
void MBDModelHoverProc(void);
void MBDAuraRiseProc(void);
void MBDMapScrollExec(s32 padIdx);
void MBDBackThreadPriHighSet(void);
void MBDBackStreamStart(void);
void MBDBackStreamStop(void);
void MBDCameraSpeedDivSet(f32);
void MBDCameraSpeedSet(f32);
f32 MBDCameraSpeedGet(void);
void MBDCameraZoomSet(f32);
void MBDCamera3Dto2D(Vec*, Vec2f*);
f32 MBDCameraZoomGet(void);
Process* MBDCameraZoomMotStart(f32);
u16 MBDCameraPos3DSet(Vec*);
u16 MBDCameraPos2DSet(Vec2f*);
void MBDCameraPos2DGet(Vec2f*);
void MBDCameraPos3DGet(Vec2f*);
f32 MBDCameraSpeedGet(void);
void MBDMapScrollMiniMapUpdate(UnkBoard4*, s32);
Object* MBDModelFileCreate(s32, s32, f32, f32, u32*);
void MBDPlayerPosFixSet(s32, s32);
Process *MBDPlayerPosMoveCreate(Vec *, Vec *, Vec *, s32);
void MBDMasuPosGet(s16 playerIdx, s16 spaceIdx, Vec *outCoords);
void MBDSaiSeStop(s32 playerIndex);
void MBDSaiSeResume(s32 playerIndex);
void MBDPauseCreate(s32 playerIndex);
void MBDPlayerPosMasuSet(s16 playerIdx, s16 spaceIdx);
void MBDScissorEmptySet(void);
void MBDSeqVolUpStart(void);
void MBDModelAttrSetDispOn(Object*);
void MBDModelAttrSetDispOff(Object*);
f32 MBDBackMdlScaleGet(void);
void MBDModelDispOn(Object*);
void MBDModelKill(Object*);
Process *MBDEffMdlCreateEx(s32 modelId, Vec *pos, Vec *vel, f32 scale, s32 delay, f32 speed);
void MBDMasuOwnerClear(void);
void MBDMasuTypeListCreate(void);
void MBDObjectSetup(s32 arg0, s16 arg1, s32 arg2);
s16 MBDMasuLinkMasuIdGet(u16 linkIdx, u16 spaceIdx);
void MBDWarpPosExec(s32 playerIndex, Vec *pos, Vec *pos1, Vec *pos2);
void MBDMasuOwnerTypeUpdate(void);
void MBDMasuOwnerSwap(s32 playerIndex, s32 newPlayerIndex);
void MBDPartnerCameraFocusSet(Vec *);
void MBDDlgWinExec(s16, s32);
void MBDPartnerMotionReset(s32);
void MBDPartnerSpeedSet(s32 playerIndex, f32 arg1);
void MBDPlayerIconMdlSet(void);
s32 MBDPartnerMotionSet(s32 playerIndex, s32 frontOrBackIndex, s16 arg2, u16 arg3);
void MBDPlayerIconMdlReset(void);
void MBDBackThreadPriHighSet(void);
void MBDBackThreadPriLowSet(void);
void MBDMapScrollProc(void);
void MBDMapScrollFocusProc(void);
void MBDSaiNumShow(s32);
s32 MBDSaiNumKill(s32);
void MBDSaiMdlDispOff(s32);
void MBDSaiMdlDispOn(s32);
void MBDBackThreadPriHighSet(void);
void MBDBackStreamStart(void);
void MBDBackStreamStop(void);
void MBDCameraSpeedDivSet(f32);
f32 MBDCameraSpeedDivGet(void);
s32 MBDStatusHideCheck(void);
void MBDStatusHideAll(void);
void MBDStatusShowAll(void);
s16 MBDOvlCallCheck(void);
void MBDMapScrollIconSet(void);
void MBDMapScrollIconReset(void);
UnkBoard4* MBDMapScrollArrowCreate(void);
void MBDMapScrollArrowDispSet(UnkBoard4* arg0, u16 arg1);
void MBDCameraSpeedSet(f32);
s16 MBDWinCreate(s16, s16*, s16);
UnkBoard4* MBDSprGrpCreate(s16 arg0, s16 arg1);
void MBDSprGrpKill(UnkBoard4*);
void MBDArrayShuffle(u8 *, s32);
void MBDGuideKill(UnkOvl81_2*);
UnkOvl81_2* MBDGuideCreate(s32, s32);
void MBDGuidePosSet(UnkOvl81_2*, s16, s16);
void MBDPartnerAttackMotLoad(s32 arg0);
void MBDModelDispOff(Object*);
Object* MBDModelLinkCreate(Object*);
void MBDModelMotionKillProc(void);
void MBDModelMotionKillCreate(Object*);
Object* MBDGetPlayerPartnerRef(s32 playerIndex, s32 frontOrBackIndex);
void MBDPartnerOfsGet(s32, Vec*, Vec*);
f32 MBDVecBetweenAngleGet(Vec *vec_1, Vec *vec_2);
f32 MBDVecAngleGet(Vec*);
void MBDVecNormalize(Vec*);
void MBDVecRotateY(Vec*, f32);
void MBDModelInit(void);
void MBDModelTempAllocFree(Object*);
void MBDSaiInit(void);
void MBDMgCallInit(void);
void MBDCoinChangeInit(void);
void MBDTelopInit(void);
void MBDBackArcInit(Addr arg0);
void MBDBackLoad(s32);
void MBDBackSprInit(void);
void MBDMasuInit(void);
s32 MBDMasuCreate(s32, s16);
void MBDMasuOwnerInit(void);
void MBDMoveMasuSet(s16 playerIdx, s16 nlink, s16 nidx);
void MBDMoveNextMasuSet(s16 playerIdx, s16 nlink, s16 nidx);
Process *MBDPlayerRotMasuStart(s16 playerIndex, s32 time, s16 spaceIndex);
void MBDPartnerFrontFollowExec(s32 playerIndex);
void MBDPlayerRevOn(void);
void MBDPlayerRevOff(void);
Process *MBDPartnerFrontFollowCreate(s32 playerIdx, s32 arg);
Process *MBDPartnerBackFollowCreate(s32 playerIdx, s32 arg);
UnkBoard2 *MBDBranchArrowCreate(s32 arg0);
UnkEA790Struct *MBDBranchArrowGrpCreate(void);
void MBDBranchArrowGrpAdd(UnkEA790Struct *arg0, UnkBoard2 *arg1, u16 arg2);
UnkBoard2 *MBDBranchArrowGrpArrowGet(UnkEA790Struct *arg0, s16 arg1);
UnkEA790Struct *MBDBranchArrowLinkCreate(s16 playerNo, s16 *choices);
s32 MBDBranchSelStart(UnkEA790Struct *win, s16 playerNo, s32 arg2);
s32 MBDBranchSelMesSend(UnkEA790Struct *win, s32 input);
s32 MBDBranchSelWait(UnkEA790Struct *win);
s16 MBDComTreeExec(DecisionTreeNonLeafNode *tree);
s16 MBDRandCheck100(s8 percent);
s16 MBDTurnRemain(void);
s32 MBDPlayerRankCalc(s32 playerIndex);
s32 MBDPlayerCoinCheck(s32 playerIndex, s32 requiredCoins);
void MBDDlgWinParamReset(void);
void MBDMotShiftInit(void);
void MBDMotShiftClose(void);
void MBDPlayerModelSetup(s16 playerIndex);
void MBDPlayerMotInit(void);
void MBDScissorFullSet(void);
void MBDSprGrpInit(void);
void MBDStatusFrontUpdate(s32 playerIndex);
void MBDStatusBackUpdate(s32);
void MBDStatusCreate(void);
void MBDPlayerTauntProc(omObjData*);
void MBDCameraNearFarSet(f32, f32);
void MBDBackArcInit(Addr arg0);
void MBDCameraKill(void);
void MBDCameraNearFarSet(f32, f32);
void MBDPartnerFrontMoveProc(void);
void MBDPartnerBackMoveProc(void);
void MBDPartnerPosFix(s32 playerIndex);
void MBDPartnerFrontJumpProc(void);
void MBDPartnerFrontWalkProc(void);
void MBDPartnerBackJumpProc(void);
void MBDPartnerBackWalkProc(void);
void MBDPauseMesMain(void);
void MBDPartnerModelKillAll(s32);
void MBDPartnerObjClear(void);
void MBDPartnerClose(void);
void MBDModelChange(Object *arg0, u8 arg1);
s32 MBDPartnerMotionShiftSet(s32 playerIndex, s32 arg1, s16 arg2, s16 arg3, s16 arg4, u16 flags);
Object* MBDModelCreate(u8, s32*);
Object* MBDPartnerPakkunModelCreate(s32);
Object* MBDPartnerModelCreate(s32);
void MBDPartnerModelSetup(s32 playerIndex);
void MBDPartnerClear(s32 playerIndex, s32 frontOrBackIndex);
void MBDMotionSet(Object*, s16, u16);
s16 MBDGetCurrentPlayerIndex(void);
void MBDMotionShiftSet(Object*, s16, s16, s16, u16);
s32 MBDRand(f32);
void MBDPartnerDescProc(void);
void MBDPartnerExtMotLoad(s32);
void MBDPartnerExtMotSet(Object*, s16, u16);
void MBDDlgWinClose(void);
void MBDDlgWinKill(void);
void MBDDlgWinMesWait(void);
void MBDCoinScatterProc(void);
Process *MBDEffMdlCreate(s32, Vec *, Vec *, f32);
void MBDCameraFocusVecSet(Vec *arg0);
void MBDWinIdPlayerKeyWaitKeep(s16, s32);

#ifndef NO_EXTERN_VARIABLES
extern Vec mbdPartnerCameraPos;
extern s32 mbdPartnerComboTbl[][2];
extern s32 mbdPartnerComboMesTbl[];
extern s32 mbdPartnerNameMesTbl[];
extern s16 mbdPartnerExtMotNum;
extern s16 mbdPartnerExtMotUseCnt;
extern s8* mbdAttackHp;
extern s8* mbdAttackTargetHp;
extern s8* mbdAttackOtherHp;
extern s8* mbdAttackPartnerId;
extern s8* mbdAttackTargetId;
extern s8* mbdAttackOtherId;
extern Vec mbdAttackCameraPos;
extern s32 mbdCounterResult;
extern s32 mbdAttackHpDamage;
extern s32 mbdAttackStarDamage;
extern s32 mbdAttackType;
extern s32 mbdAttackOtherIdParam;
extern s32 mbdAttackResult;
extern s32 mbdAttackTargetIdParam;
#endif

Process *MBDModelSpinCreate(Object *, f32, f32, s32);
void MBDTelopTitleProc(void);
Process* MBDTelopTitleCreate(void);
Process* MBDTelopAttackCreate(s32, s32, Vec*, Vec*, s32);
void MBDBackThreadPriHighSet(void);
void MBDBackThreadPriLowSet(void);
void MBDBackTPLvlSet(u8);
void MBDDlgResultWinExec(s32);
Process* MBDVecSpeedMoveCreate(Vec*, Vec*, Vec*, f32);
Process* MBDVecSpeedMove2Create(Vec*, Vec*, Vec*, f32);
void MBDModelJumpSet(Object *, f32, f32);
void MBDModelJumpWait(Object *);
void MBDPartnerAttackMotShiftSet(Object *, s16, s16, s16, s16);
void MBDMotionShiftSetDef(Object*, s16, s32);
void MBDModelMotionWait(Object*);
void MBDModelMotionStartWait(Object*);
void MBDModelHookSet(Object *obj, char *hookName, s16 model);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void MBDModelBillboardSet(Object *obj);
s32 MBDEffExplodeCreate(s32 dataNum, char *objName);
void MBDEffExplodeKill(s32 model);
void MBDEffExplodePosSet(s32 model, Vec *pos);
s32 MBDEffExplodeEndCheck(s32 model);
Process *MBDEffBurstNoLayerCreate(s32, s32, Vec *, f32, s32);
Process *MBDEffMdlDelayCreate(s32, Vec *, Vec *, f32, s32);
void MBDPartnerModelMotionSet(Object*, s32, s32);
void MBDStatusFrontDispOff(s32);
void MBDStatusBackDispOff(s32);
s16 MBDMasuCurGet(void);
void MBDStatusShrink(s32);
void MBDStatusGrow(s32);
void MBDPartnerModelUpdate(s32);
void MBDPartnerAttackPairGet(s32, s32*, s32*);
void MBDPartnerDamageCalc(u32 partnerID, s32 arg1, s32* damageAmount, s32* arg3, s32 arg4);
void MBDCoinScatterInit(void);
void MBDCoinScatterClose(void);
void MBDPartnerExtMotInit(void);
void MBDPartnerExtMotKill(void);
void MBDCameraFocusModeSet(s32);
void MBDCameraFocusVecSet(Vec *arg0);
Vec* MBDCameraFocusVecGet(void);
void MBDPlayerVibrate(s16, s16);
void MBDDlgWinInsertCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void MBDDlgWinInsertCreateAllKey(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void MBDModelScaleMulSet(f32);
void MBDShadowHeightMaxSet(f32);
void MBDWinComKeyAllNumSet(s32);
s32 MBDModelJumpCheck(Object*);
SpaceData* MBDMasuGet(s16 spaceIdx);
void MBDStatusKill(void);
Process *MBDTelopBannerCreate(s32 arg0);
Process *MBDAuraRiseCreate(s32 arg0);
void MBDPartnerPowerUp(s32 playerIndex);
void MBDPartnerPowerDown(s32 playerIndex);
void MBDPartnerPosSwap(s32 playerIndex);
void MBDEffSwirlCreate(Vec *);
void MBDEffSwirlOn(void);
void MBDEffSwirlOff(void);
void MBDEffSwirlKill(void);
void MBDAuraLand(s32);
void MBDDlgWinCreate(s16, s32);
s32 MBDMesWaitGet(void);
void MBDPartnerDescExec(s32 playerIndex);
void MBDPartnerDirGet(s32, Vec *, Vec *);
void MBDPartnerSet(s32, s32, s32);
void MBDPartnerModelReset(s32, s32);
void MBDStatusMemberGrow(s32, s32);
void MBDStatusMemberShrink(s32, s32);
void MBDPartnerComboMesExec(void);
void MBDWinInsertOpen(s32, char *, s32, s32, s32, s32);
void MBDWinKeyWaitKeep(s32);
void MBDWinClose(void);
s32 MBDPartnerCostGet(s32 playerIndex);
u16 MBDMotionCheck(Object *);
u16 MBDMotionStartCheck(Object *);
Object *MBDAuraAltCreate(Vec *);
void MBDExitHookSet(void (*)(void));
void MBDGameModeMgSet(void);
Process *MBDSaiPlayerCreate(s32 playerIndex);
Process *MBDTelopCreate(s32 playerIndex);
Process *MBDVecRotLerpCreate(Vec *from, Vec *to, Vec *out, s32 time);
void MBDPlayerForwardSet(s16 playerIdx);
void MBDPlayerPartnerMoveExec(s16 playerIndex, f32 speed);
Process *MBDModelHoverCreate(Object *obj, f32 arg1, f32 arg2);
void MBDPlayerSpeedSet(s32 playerIndex, f32 arg1);
Process *MBDScissorWipeOutStart(void);
Process *MBDScissorWipeInStart(void);
s32 MBDScissorFullCheck(void);
void MBDSaiSePlay(s32 playerIndex);
void MBDSaiNumCountDown(s32 arg0);
void MBDSaiTypeSet(s32 arg0, s8 arg1);
s32 MBDSaiValueGet(s32 arg0);
void MBDCoinChangeStatusCreate(s32 arg0, s32 arg1);
void MBDCoinChangeCreate(s32 arg0, s32 arg1);
void MBDMasuBounceCreate(s16 spaceIdx);
s32 MBDMasuEventCall(s16 spaceIdx, s16 activationType);
void MBDMasuCurSet(s16 spaceIdx);
void MBDMasuOwnerAdd(s16 unk_17_value, s8 unk_2A_value);
s32 MBDMasuOwnerGet(s16 unk_17_value);
s32 MBDMasuOwnerNumGet(s32 playerIndex);
void MBDWinOpen(s32 arg0);
void MBDPlayerDirNextSet(s32 playerIndex);
void MBDAuraRiseExec(s32 arg0);
void MBDPlayerMotionShiftSet(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void MBDPlayerPartyMotionShiftSet(s32 playerIndex, s16 arg1, s16 arg2, s16 arg3, u16 arg4);
void MBDCoinTakeCreate(s32 playerIndex, s32 coins);
void MBDPartnerAttackExec(s32 attackType);
void MBDPartnerAttackMotKill(void);

#ifndef NO_EXTERN_VARIABLES
extern Object *mbdMgCallMdlObj;
#endif
