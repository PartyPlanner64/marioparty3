#define NO_EXTERN_VARIABLES
#include "common.h"
#include "cosmic_coaster.h"

f32 m216_winJumpVelXTbl[2] BSS;
f32 m216_winJumpVelYTbl[2] BSS;
s32 m216_winTimer BSS;
omObjData *m216_winCameraObj BSS;
omObjData *m216_loseCarObj BSS;
f32 m216_introZoomStart BSS;
f32 m216_introRotXStep BSS;
f32 m216_introRotYStep BSS;
f32 m216_introRotZStep BSS;
f32 m216_introCenterXStep BSS;
f32 m216_introCenterYStep BSS;
f32 m216_introCenterZStep BSS;
s32 m216_introKeyTimer BSS;
s32 m216_introKeyNo BSS;
omObjData *m216_introCameraObj BSS;
s32 m216_mainPhase BSS;
s16 m216_coinEffGrp BSS;
u16 m216_introPhase BSS;
u8 m216_introPhasePad[4] BSS; /* Unreferenced. */
CosmicCoasterSpawn m216_asteroidSpawnTbl[51] BSS;
u16 m216_stageSpawnIdxTbl[2] BSS;
u16 m216_asteroidSpawnIdxTbl[2] BSS;
s16 m216_stageMdlTbl[11] BSS;
omObjData *m216_carObjTbl[2] BSS;
omObjData *m216_comTargetObj BSS;
s16 m216_winner BSS;
omObjData *m216_hudObj BSS;
omObjData *m216_stageObj BSS;
