#include "common.h"
#include "macros.h"
#include "fridged_bridges.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
f32 m236_winZoomStep BSS;
Vec m236_winRotStep BSS;
u16 m236_winCameraTimer BSS;
s16 m236_winCameraTimerPad BSS;   /* Unreferenced. */
u8 m236_winCameraTimerPadB[8] BSS; /* Unreferenced. */
omObjData *m236_introObj BSS;
omObjData *m236_winObj BSS;
u16 m236_introPhase BSS;
u16 m236_winPhase BSS;
u16 m236_seaTexSizeTbl[4][2] BSS;
Vec2f m236_seaScrollTbl[4] BSS;
u8 m236_seaScrollPad[8] BSS; /* Unreferenced. */
Vec2f m236_comPathPosTbl[4][3][12] BSS;
Vec2f m236_cameraPathPosTbl[4][12] BSS;
Vec2f m236_bridgeSlotPosTbl[4][3] BSS;
Vec2f m236_pieceStockPosTbl[4] BSS;
u16 m236_cameraPathNo BSS;
s16 m236_cameraPathNoPad BSS;    /* Unreferenced. */
u8 m236_cameraPathNoPadB[12] BSS; /* Unreferenced. */
s16 m236_effMdlTbl[1][12] BSS;
u16 m236_effUseTbl[1][12] BSS;
s16 m236_winner BSS;
s16 m236_winnerPad BSS; /* Unreferenced. */
omObjData **m236_playerObjTbl BSS;
s16 m236_goalF BSS;
s16 m236_goalPad BSS; /* Unreferenced. */
omObjData *m236_stageObj BSS;
omObjData *m236_pieceObj BSS;
u8 m236_pieceObjPad[4] BSS; /* Unreferenced. */
omObjData *m236_foeObjTbl[4] BSS;
omObjData *m236_effObj BSS;
u8 m236_effObjPad[4] BSS; /* Unreferenced. */
FridgedBridgesCamCollWork m236_camCollWorkTbl[4] BSS;
