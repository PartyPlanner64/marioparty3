#include "common.h"
#include "overlays/msetup_internal.h"

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
Process *D_8011A898_msetup[4] BSS;
u8 D_8011A8A8_msetup[8] BSS;
MsetupSpriteState D_8011A8B0_msetup BSS;
u8 D_8011A8D4_msetup[12] BSS;
s16 D_8011A8E0_msetup[4][4] BSS;
Process *D_8011A900_msetup BSS;
MsetupPortraitState D_8011A904_msetup BSS;
f32 D_8011A908_msetup BSS;
s32 D_8011A90C_msetup BSS;
s16 D_8011A910_msetup BSS;
s16 D_8011A912_msetup BSS;
u8 D_8011A914_msetup[12] BSS;
Vec D_8011A920_msetup BSS;
Vec D_8011A92C_msetup BSS;
s16 D_8011A938_msetup BSS;
s16 D_8011A93A_msetup BSS;
f32 D_8011A93C_msetup BSS;
f32 D_8011A940_msetup BSS;
s16 D_8011A944_msetup BSS;
s16 D_8011A946_msetup BSS;
s16 D_8011A948_msetup BSS;
s16 D_8011A94A_msetup BSS;
s32 D_8011A94C_msetup BSS;
s16 D_8011A950_msetup[32] BSS;
s16 D_8011A990_msetup BSS;
s16 D_8011A992_msetup BSS;
Vec D_8011A994_msetup BSS;
s16 D_8011A9A0_msetup[32] BSS;
MsetupEntryAnim D_8011A9E0_msetup[4] BSS;
MsetupPlayerConfig D_8011AA30_msetup BSS;
s16 D_8011AA48_msetup BSS;
s16 D_8011AA4A_msetup BSS;
s16 D_8011AA4C_msetup BSS;
s16 D_8011AA4E_msetup BSS;
