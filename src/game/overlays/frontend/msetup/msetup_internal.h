#ifndef MSETUP_INTERNAL_H
#define MSETUP_INTERNAL_H

#include "game/overlays/msetup.h"
#include "game/object.h"

typedef MsetupLinkedModel Array2D[2];

typedef struct MsetupModelTarget {
    Vec pos;
    f32 rotation;
} MsetupModelTarget;

typedef struct MsetupCursorState {
    s16 pos[2];
    s16 (*positions)[2];
    s32 dataId;
    s16 selection;
    s16 state;
    s16 flags;
    s16 priority;
} MsetupCursorState;

typedef struct MsetupSpriteState {
    s16 state;
    s16 unk02;
    s16 spriteSlots[8];
    s16 values[8];
} MsetupSpriteState;

void msetup_WinMesSet(s32 message);
s32 msetup_WinMesWait(void);
void msetup_WinInsertMesSet(u32 arg0, s8 arg1);
void msetup_WinHomeClear(void);
s16 msetup_CursorPadNextGet(s16 positions[][2], u8 *disabled, s16 count, s16 selection, s16 controller, s16 buttons);
void msetup_CursorProc(void);
void msetup_ArrowObjKill(omObjData *object);
omObjData *msetup_ArrowObjCreate(s32 leftX, s32 rightX, s32 y);
s16 msetup_EffEmitNumSet(omObjData *arg0, s16 arg1);
void msetup_EffEmitPosSet(omObjData *arg0, s16 arg1, s16 arg2, f32 arg3, f32 arg4, f32 arg5);
omObjData *msetup_EffObjCreate(void);
void msetup_PanelCreate(Array2D *arg0, s32 arg1, f32 arg2);
void msetup_PanelDynamicFree(MsetupLinkedModel *entry, s32 count);
void msetup_PanelMove(MsetupLinkedModel *models, MsetupModelTarget *targets, s16 count, s16 frames,
                          s16 *scaleModels, s16 scaleCount, f32 startScale, f32 endScale);
void msetup_PanelSpinMove(Array2D *models, s16 count, s16 frames, f32 rotation, f32 height, f32 scale, f32 endScale,
                          s16 animateBoard);
void msetup_SummaryEntrySet(Process *process, s16 index, s16 spriteSlot, s16 value);

/* Menu and setup dispatch tables. */
s16 msetup_PartyPlayerNumStep(s16 stateIndex);
s16 msetup_PartyChrStep(s16 stateIndex);
s16 msetup_PartyComLevelStep(s16 stateIndex);
s16 msetup_PartyHandicapStep(s16 stateIndex);
s16 msetup_PartyBoardStep(s16 stateIndex);
s16 msetup_PartyTurnStep(s16 stateIndex);
s16 msetup_PartyMgPackStep(s16 stateIndex);
s16 msetup_PartyBonusStep(s16 stateIndex);
s16 msetup_PartyConfirmStep(s16 stateIndex);
void msetup_PartySetupProc(void);
s16 msetup_DuelPlayerNumStep(s16 stateIndex);
s16 msetup_DuelChrStep(s16 stateIndex);
s16 msetup_DuelComLevelStep(s16 stateIndex);
s16 msetup_DuelHandicapStep(s16 stateIndex);
s16 msetup_DuelBoardStep(s16 stateIndex);
s16 msetup_DuelTurnStep(s16 stateIndex);
s16 msetup_DuelMgPackStep(s16 stateIndex);
s16 msetup_DuelConfirmStep(s16 stateIndex);
void msetup_DuelSetupProc(void);
void msetup_StoryPartySetupProc(void);
void msetup_StoryDuelSetupProc(void);
s16 msetup_MgModeIntroStep(s16 stateIndex);
s16 msetup_MgMode1PIntroStep(s16 stateIndex);
s16 msetup_MgMode1PChrStep(s16 step);
s16 msetup_MgMode1PComLevelStep(s16 step);
s16 msetup_MgModeConfirmStep(s16 step);
s16 msetup_MgMode1PConfirmStep(s16 step);
void msetup_MgModeSetupProc(void);
void msetup_MgMode1PSetupProc(void);
void msetup_TutorialPartySetupProc(void);
void msetup_TutorialDuelSetupProc(void);
s16 msetup_PlayerNumSelect(MsetupMenuState *state);
s16 msetup_ChrSelect(MsetupMenuState *state);
s16 msetup_ComLevelSelect(MsetupMenuState *state);
s16 msetup_HandicapChoice(MsetupMenuState *state);
s16 msetup_BonusChoice(MsetupMenuState *state);
s16 msetup_DuelHandicapChoice(MsetupMenuState *state);
s16 msetup_MgPackChoice(MsetupMenuState *state);
s16 msetup_BoardSelect(MsetupMenuState *arg0);
s16 msetup_StoryBoardShow(MsetupMenuState *state);
s16 msetup_HandicapSelect(MsetupMenuState *state);
s16 msetup_TurnSelect(MsetupMenuState *state);
s16 msetup_DuelPlayerNumSelect(MsetupMenuState *state);
s16 msetup_DuelHandicapSelect(MsetupMenuState *state);
s16 msetup_MenuIdle(MsetupMenuState *state);
void msetup_StorySetupProc(void);

#endif
