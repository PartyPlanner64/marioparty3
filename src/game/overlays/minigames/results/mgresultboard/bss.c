#define NO_EXTERN_VARIABLES
#include "common.h"
#include "mgresultboard.h"

// Misaligned s16 array after an s8 (see undefined_syms.txt for aliases).
typedef struct MgResultBoardMainBss {
    /* 0x00 */ s8 unk00;     // mgresultboard_mainCnt
    /* 0x02 */ s16 unk02[3]; // mgresultboard_seIdTbl
} MgResultBoardMainBss;      // sizeof 0x08

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
s32 mgresultboard_mainTimer BSS;
MgResultBoardMainBss mgresultboard_mainBss BSS;
u8 mgresultboard_mainBssPad[0x14] BSS; /* Unreferenced. */
s32 mgresultboard_faceAnimTbl[8] BSS;
s32 mgresultboard_scoreAnimTbl[40] BSS;
s32 mgresultboard_scoreAnimDataTbl[2] BSS;
u8 mgresultboard_scoreAnimDataPad[8] BSS; /* Unreferenced. */
s32 mgresultboard_rankAnimTbl[8] BSS;
omObjData *mgresultboard_scoreObj BSS;
void (*mgresultboard_scoreFunc)(omObjData *) BSS;
UnkTemp mgresultboard_scoreFlapTbl[4][5] BSS;
omObjData *mgresultboard_coinIconObj BSS;
void (*mgresultboard_coinIconFunc)(omObjData *) BSS;
omObjData *mgresultboard_starIconObj BSS;
void (*mgresultboard_starIconFunc)(omObjData *) BSS;
omObjData *mgresultboard_faceObj BSS;
void (*mgresultboard_faceFunc)(omObjData *) BSS;
UnkTemp mgresultboard_rankFlapTbl[4] BSS;
omObjData *mgresultboard_rankObj BSS;
void (*mgresultboard_rankFunc)(omObjData *) BSS;
UnkTemp mgresultboard_faceFlapTbl[4] BSS;
PlayerResult mgresultboard_prevResultTbl[4] BSS;
PlayerResult mgresultboard_resultTbl[4] BSS;
