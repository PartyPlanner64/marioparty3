#include "common.h"
#include "game/gamemes.h"
#include "mgmode.h"

// Misaligned s8 array after an s16 (see undefined_syms.txt for aliases).
typedef struct MgmodeTeamWork {
    /* 0x00 */ s16 unk00;   // mgmode_teamWinId
    /* 0x02 */ s8 unk02[4]; // mgmode_teamOrderTbl
} MgmodeTeamWork;            // sizeof 0x06

// Misaligned s16 arrays after a u8 (see undefined_syms.txt for aliases).
typedef struct MgmodeStarWork {
    /* 0x00 */ u8 unk00;     // mgmode_starPlayerNum
    /* 0x02 */ s16 unk02[4]; // mgmode_battlePlayerAnimTbl
    /* 0x0A */ s16 unk0A[4]; // mgmode_battlePlayerChrTbl
    /* 0x12 */ s16 unk12[4]; // mgmode_battleConfettiTbl
} MgmodeStarWork;             // sizeof 0x1A

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s16 mgmode_roomSpotNo BSS;
u8 mgmode_roomSpotNoPad[4] BSS; /* Unreferenced. */
char mgmode_strBuf[0x100] BSS;
HuMtx4F mgmode_roomMonitorMtx BSS;
HuMtx4F mgmode_roomBattleDoorMtx BSS;
HuMtx4F mgmode_roomGambleDoorMtx BSS;
u8 mgmode_markMgTbl[8][20] BSS;
u8 mgmode_markMgNumTbl[8] BSS;
u8 mgmode_plainMgTbl[8][20] BSS;
u8 mgmode_plainMgNumTbl[8] BSS;
MgmodeSpaceCoord mgmode_bookCursorPosTbl[26] BSS;
Vec mgmode_bookPosTbl[8][25] BSS;
u16 *mgmode_teamPosXTbl BSS;
MgmodeTeamWork mgmode_teamWork BSS;
MgmodeEsprite *mgmode_teamSprTbl BSS;

HuMtx4F mgmode_battleDoorMtx BSS;
u8 mgmode_starPlayerTbl[4] BSS;
MgmodeStarWork mgmode_starWork BSS;
MgmodeEsprite *mgmode_battleMenuSprTbl BSS;
s16 mgmode_battleTypeNum BSS;
s16 mgmode_battleTypeTbl[8] BSS;
MgmodeSpaceCoord mgmode_battleTypeCursorTbl[6] BSS;
MgmodeEsprite *mgmode_battleBoardSprTbl BSS;
s16 mgmode_battleStarAnim BSS;
u16 mgmode_battleStarSprTbl[28] BSS;
s16 mgmode_battleStarSprNum BSS;
u8 mgmode_battleStarSprNumPad[12] BSS; /* Unreferenced. */

HuMtx4F mgmode_gambleDoorMtx BSS;
u8 mgmode_gambleTitleStr[256] BSS;
u8 *mgmode_spotBufTbl[3] BSS;
s16 mgmode_spotAnim BSS;
s16 mgmode_spotGrp BSS;
s16 mgmode_gamblePlayerAnim BSS;
s16 mgmode_gamblePlayerChr BSS;
s16 mgmode_gambleConfettiNo BSS;
u8 mgmode_gambleConfettiNoPad[8] BSS; /* Unreferenced. */

u8 mgmode_cursorDisableTbl[0x20] BSS;
s16 mgmode_mgPicSpr BSS;
s16 mgmode_mgPicBufNo BSS;
u16 *mgmode_mgPicBufTbl[3] BSS;
void *mgmode_mgPicOrigData BSS;
s16 mgmode_cursorX BSS;
s16 mgmode_cursorY BSS;
s16 mgmode_cursorMoveTime BSS;
s16 mgmode_cursorSel BSS;
s16 mgmode_cursorSpr BSS;
s16 mgmode_cursorDispF BSS;
MgmodeSpaceCoord *mgmode_cursorPosTbl BSS;
u8 mgmode_cursorPosTblPad[4] BSS; /* Unreferenced. */
s16 mgmode_confettiMdlTbl[4][4] BSS;
s16 mgmode_confettiCntTbl[4] BSS;

s16 mgmode_menuWinId BSS;
f32 mgmode_cameraFov BSS;
s16 mgmode_winId BSS;
u8 mgmode_winIdPad[4] BSS; /* Unreferenced. */
u8 mgmode_typeMgTbl[8][25] BSS;
u8 mgmode_battleOpenF BSS;
s16 mgmode_mgNum BSS;
u8 mgmode_mgNumPad[4] BSS; /* Unreferenced. */
s16 mgmode_motTbl[64] BSS;
s16 mgmode_playerNo BSS;
f32 mgmode_cameraNear BSS;
s16 mgmode_padNo BSS;
s16 mgmode_mgUnlockNum BSS;
u8 mgmode_mgUnlockNumPad[4] BSS; /* Unreferenced. */
GAMEMES mgmode_gambleTitleMes BSS;
s16 mgmode_zClearF BSS;
f32 mgmode_cameraFar BSS;
Vec mgmode_cameraCenter BSS;
Vec mgmode_cameraRot BSS;
u8 mgmode_gambleOpenF BSS;
s16 mgmode_mdlTbl[64] BSS;
s16 mgmode_typeUnlockNumTbl[8] BSS;
f32 mgmode_cameraZoom BSS;
u8 mgmode_cameraZoomPad[4] BSS; /* Unreferenced. */
s16 mgmode_typeMgNumTbl[8] BSS;
s16 mgmode_exitEvtNo BSS;
ModeCameraPreset *mgmode_cameraPresetTbl BSS;
u8 mgmode_cameraPresetNo BSS;
s16 mgmode_exitOvlNo BSS;
