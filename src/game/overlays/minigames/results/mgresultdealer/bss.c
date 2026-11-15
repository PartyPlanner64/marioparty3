#define NO_EXTERN_VARIABLES
#include "common.h"
#include "mgresultdealer.h"

// Misaligned s8 array after an s16 (see undefined_syms.txt for aliases).
typedef struct MgResultDealerBssA264 {
    /* 0x00 */ s16 unk00; // D_8010A264_mgresultdealer
    /* 0x02 */ s8 unk02[4]; // D_8010A266_mgresultdealer
} MgResultDealerBssA264; // sizeof 0x06

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */
u8 D_801099E0_mgresultdealer[0x18] BSS; /* Unreferenced. */
s16 D_801099F8_mgresultdealer[4] BSS;
u8 D_80109A00_mgresultdealer[0x60] BSS; /* Unreferenced. */
f32 D_80109A60_mgresultdealer BSS;
s16 D_80109A64_mgresultdealer[4] BSS;
u8 D_80109A6C_mgresultdealer[4] BSS; /* Unreferenced. */
u16 D_80109A70_mgresultdealer BSS;
u16 D_80109A72_mgresultdealer BSS;
u8 D_80109A74_mgresultdealer[4] BSS; /* Unreferenced. */
UnkDealerCoin D_80109A78_mgresultdealer[40] BSS;
UnkDealerCoin D_80109E38_mgresultdealer[40] BSS;
u8 D_8010A1F8_mgresultdealer[8] BSS; /* Unreferenced. */
s16 D_8010A200_mgresultdealer BSS;
s32 D_8010A204_mgresultdealer BSS;
HuSprite *D_8010A208_mgresultdealer BSS;
u8 *D_8010A20C_mgresultdealer BSS;
UnkDealerSprites D_8010A210_mgresultdealer BSS;
s32 D_8010A240_mgresultdealer BSS;
s32 D_8010A244_mgresultdealer BSS;
u8 D_8010A248_mgresultdealer[8] BSS; /* Unreferenced. */
ResultDealerObj D_8010A250_mgresultdealer BSS;
s16 D_8010A258_mgresultdealer BSS;
omObjData *D_8010A25C_mgresultdealer BSS;
omObjFunc D_8010A260_mgresultdealer BSS;
MgResultDealerBssA264 mgResultDealerBssA264 BSS;
UnkDealerFadeProc D_8010A26C_mgresultdealer BSS;
omObjData *D_8010A274_mgresultdealer BSS;
omObjFunc D_8010A278_mgresultdealer BSS;
