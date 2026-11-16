#define NO_EXTERN_VARIABLES
#include "common.h"
#include "game/overlays/minigame.h"

/*
 * Some arrays in this overlay's BSS are only halfword aligned, which GCC won't
 * produce for standalone arrays. They are grouped into structs here, and the
 * field symbols used by the original code are aliased in undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s8 unk02[6];
} MgBssItemObjNum;

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s8 unk02[4];
    /* 0x06 */ s8 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s16 unk0A[1];
} MgBssPlayerObjNum;

Vec mgItemPrevPos BSS;
u8 mgItemPrevPosPad[4] BSS; /* Unreferenced. */
Vec mgPlayerPrevPos BSS;
u8 mgPlayerPrevPosPad[4] BSS; /* Unreferenced. */
MinigameFlow *mgFlow BSS;
s16 mgTimeSprAnim BSS;
s16 mgRecordSprAnim BSS;
s16 mgTimeGrpTbl[4] BSS;
s16 mgGaugeNum BSS;
MgGauge *mgGaugeTbl BSS;
s16 mgGaugeFrameAnim BSS;
s16 mgGaugeBarAnim BSS;
u16 mgGaugeLen BSS;
s16 mgBoxMdlTbl[4] BSS;
u8 mgBoxMdlPad[8] BSS; /* Unreferenced. */
s16 mgPlayerSeNoTbl[4] BSS;
s16 mgStickRotTimeTbl[4] BSS;
u8 mgStickRotQuadTbl[4] BSS;
s32 mgFieldStat BSS;
u16 mgMapObjNum BSS;
f32 mgMoveOfsX BSS;
HuMtx4F mgMapInvMtx BSS;
omObjData *mgItemObjTbl[16] BSS;
Hu3DQuadPool mgQuadPool BSS;
MgWallPos mgWallPosTbl[64] BSS;
MgBssItemObjNum mgBssItemObjNum BSS;
omObjData *mgMapObjTbl[32] BSS;
HuMtx4F mgMapMtx BSS;
MgBssPlayerObjNum mgBssPlayerObjNum BSS;
Vec mgWallNorPrevTbl[1] BSS;
Vec mgWallNorTbl[64] BSS;
omObjData *mgPlayerObjTbl[16] BSS;
f32 mgMoveOfsZ BSS;
u8 mgStickRotStartTbl[4] BSS;
