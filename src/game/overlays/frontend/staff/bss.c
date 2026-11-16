#define NO_EXTERN_VARIABLES
#include "staff.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s16 staff_roleFontAnimTbl[27] BSS;
UnkStaff_6 *staff_roleLineTbl BSS;
u8 staff_roleLinePad[4] BSS; /* Unreferenced. */
s16 staff_nameFontAnimTbl[28] BSS;
UnkStaff_6 *staff_nameLineTbl BSS;
s16 staff_roleLineNum BSS;
s16 staff_nameLineNum BSS;
s16 staff_padNo BSS;
s16 staff_storyF BSS;
s16 staff_chrNo BSS;
s16 staff_exitOvlNo BSS;
MsetupPlayerConfig staff_playerConfig BSS;
s16 staff_wipeType BSS;
s16 staff_exitEvtNo BSS;
Vec staff_cameraTarget BSS;
Vec staff_cameraPos BSS;
s16 staff_wipeTime BSS;
Vec staff_cameraRot BSS;
s16 staff_exitMode BSS;
f32 staff_cameraFar BSS;
f32 staff_cameraNear BSS;
