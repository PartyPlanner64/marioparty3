#include "common.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s16 mgenter_arrowPosF BSS;
s16 mgenter_arrowDispF BSS;
s16 mgenter_slideInReq BSS;
s16 mgenter_mgPicState BSS;
s16 mgenter_optionState BSS;
s16 mgenter_mgNo BSS;
s16 mgenter_stageNo BSS;
s16 mgenter_stageNum BSS;
s16 mgenter_stageScrollDir BSS;
s16 mgenter_optionNo BSS;
s16 mgenter_arrowLX BSS;
s16 mgenter_arrowRX BSS;
s16 mgenter_arrowLY BSS;
s16 mgenter_arrowRY BSS;
u8 mgenter_arrowRYPad[4] BSS; /* Unreferenced. */
s16 mgenter_mgPicAnim BSS;
s16 mgenter_mgPicSpr BSS;
s16 mgenter_mgPicBufNo BSS;
u8 *mgenter_mgPicBufTbl[3] BSS;
u8 *mgenter_mgPicOrigData BSS;
u8 mgenter_mgPicOrigDataPad[12] BSS; /* Unreferenced. */
f32 mgenter_cameraNear BSS;
u8 mgenter_cameraNearPad[12] BSS; /* Unreferenced. */
s16 mgenter_padNo BSS;
s16 mgenter_exitOvlNo BSS;
f32 mgenter_cameraFar BSS;
s16 mgenter_exitMode BSS;
u8 mgenter_exitModePad[8] BSS; /* Unreferenced. */
Vec mgenter_cameraTarget BSS;
u8 mgenter_cameraTargetPad[4] BSS; /* Unreferenced. */
s16 mgenter_exitEvtNo BSS;
u8 mgenter_exitEvtNoPad[8] BSS; /* Unreferenced. */
Vec mgenter_cameraPos BSS;
u8 mgenter_cameraPosPad[0x80] BSS; /* Unreferenced. */
