#include "common.h"
#include "msetup_internal.h"

typedef struct MsetupMenuContext {
    s16 playerCount;
    MsetupMenuState menu;
    u8 unused[8];
} MsetupMenuContext;

typedef struct MsetupMessageWindows {
    s16 current;
    s16 windows[2];
    s16 unused;
} MsetupMessageWindows;

/* Field symbols used by the original code are aliased in undefined_syms.txt. */
MsetupMenuContext msetupMenuContext BSS;
MsetupMessageWindows msetupMessageWindows BSS;
Process *msetup_playerProcTbl[4] BSS;
u8 msetup_playerProcPad[8] BSS;
MsetupSpriteState msetup_summaryWork BSS;
u8 msetup_summaryWorkPad[12] BSS;
s16 msetup_menuSlotTbl[4][4] BSS;
Process *msetup_chrInfoProc BSS;
MsetupPortraitState msetup_chrInfoWork BSS;
f32 msetup_turnDialAngle BSS;
s32 msetup_turnDialPad BSS;
s16 msetup_storyWinId BSS;
s16 msetup_storyWinPad BSS;
u8 msetup_storyWinPadB[12] BSS;
Vec msetup_cameraTarget BSS;
Vec msetup_cameraPos BSS;
s16 msetup_setupMode BSS;
s16 msetup_wipeTime BSS;
f32 msetup_cameraFar BSS;
f32 msetup_cameraNear BSS;
s16 msetup_exitMode BSS;
s16 msetup_exitEvtNo BSS;
s16 msetup_padNo BSS;
s16 msetup_padNoPad BSS;
s32 msetup_padNoPadB BSS;
s16 msetup_entryMdlTbl[32] BSS;
s16 msetup_winMode BSS;
s16 msetup_winModePad BSS;
Vec msetup_cameraRot BSS;
s16 msetup_entryMotTbl[32] BSS;
MsetupEntryAnim msetup_playerWorkTbl[4] BSS;
MsetupPlayerConfig msetup_playerConfig BSS;
s16 msetup_wipeType BSS;
s16 msetup_backNarrowF BSS;
s16 msetup_exitOvlNo BSS;
s16 msetup_exitOvlNoPad BSS;
