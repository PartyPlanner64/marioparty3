#define NO_EXTERN_VARIABLES
#include "common_duel.h"
#include "game/gamemes.h"
#include "game/hvq.h"
#include "ovl_81.h"

/*
 * Some halfword arrays in this overlay's BSS are only halfword aligned, which
 * GCC won't produce for standalone arrays. They are grouped into structs here,
 * and the field symbols used by the original code are aliased in
 * undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ s16 sprGrp;
    /* 0x02 */ s16 sprAnims[2]; // D_80102CAA_name_81
} NameBss2CA8;

typedef struct {
    /* 0x00 */ u8 unk_00;
    /* 0x02 */ s16 sprGrps[2]; // D_80102CBA_name_81
    /* 0x06 */ s16 sprAnims[2]; // D_80102CBE_name_81
} NameBss2CB8;

// model.c
Object *D_801029C0_name_81 BSS;
u16 D_801029C4_name_81 BSS;
s16 D_801029C8_name_81[130] BSS;
u8 D_80102ACC_name_81[4] BSS; /* Unreferenced. */

// effect.c
Object *D_80102AD0_name_81[32] BSS;
s16 D_80102B50_name_81 BSS;
omObjData *D_80102B54_name_81 BSS;
Vec D_80102B58_name_81 BSS;
Vec D_80102B64_name_81 BSS; /* Unreferenced. */

// mgcall.c
UnkC5770B70 D_80102B70_name_81[5] BSS;
omObjData *D_80102BA4_name_81 BSS;
s8 D_80102BA8_name_81[5] BSS;
s8 D_80102BAD_name_81 BSS;
s8 D_80102BAE_name_81 BSS;
s16 D_80102BB0_name_81 BSS;
s16 D_80102BB2_name_81 BSS;
s16 D_80102BB4_name_81 BSS;
s16 D_80102BB6_name_81 BSS;
s32 D_80102BB8_name_81 BSS;
u8 D_80102BBC_name_81[4] BSS; /* Unreferenced. */
s16 D_80102BC0_name_81[2] BSS;
s16 D_80102BC4_name_81[2][2] BSS;
omObjData *D_80102BCC_name_81[2] BSS;
u8 D_80102BD4_name_81 BSS;
f32 D_80102BD8_name_81[2][2] BSS;
u8 D_80102BE8_name_81[8] BSS; /* Unreferenced. */

// warp.c
s16 D_80102BF0_name_81 BSS;
s16 D_80102BF2_name_81 BSS;
s16 D_80102BF4_name_81 BSS;
s16 D_80102BF6_name_81 BSS;
s16 D_80102BF8_name_81 BSS;
s16 D_80102BFA_name_81 BSS;
u8 D_80102BFC_name_81[4] BSS; /* Unreferenced. */
Vec D_80102C00_name_81 BSS;
Vec D_80102C0C_name_81 BSS;
Vec D_80102C18_name_81 BSS;
Vec D_80102C24_name_81 BSS; /* Unreferenced. */

// telop.c
GAMEMES D_80102C30_name_81 BSS;
s16 D_80102CA4_name_81 BSS;
u8 D_80102CA6_name_81 BSS;
NameBss2CA8 D_80102CA8_name_81 BSS;
omObjData *D_80102CB0_name_81 BSS;
omObjData *D_80102CB4_name_81 BSS;
NameBss2CB8 D_80102CB8_name_81 BSS;
s32 D_80102CC4_name_81 BSS;
s32 D_80102CC8_name_81 BSS;
UnkBoard4 *D_80102CCC_name_81 BSS;
UnkBoard4 *D_80102CD0_name_81 BSS;
u8 D_80102CD4_name_81[0xC] BSS; /* Unreferenced. */
Vec D_80102CE0_name_81 BSS;
Vec D_80102CEC_name_81 BSS;
Vec D_80102CF8_name_81 BSS;
Vec D_80102D04_name_81 BSS;
Vec D_80102D10_name_81 BSS;
u8 D_80102D1C_name_81[4] BSS; /* Unreferenced. */

// back.c
u32 D_80102D20_name_81 BSS;
s32 D_80102D24_name_81 BSS;
u32 D_80102D28_name_81 BSS;
f32 D_80102D2C_name_81 BSS;
u16 D_80102D30_name_81 BSS;
s16 D_80102D32_name_81 BSS;
s16 D_80102D34_name_81 BSS;
s16 D_80102D36_name_81 BSS;
s16 D_80102D38_name_81 BSS;
u8 *D_80102D3C_name_81 BSS;
HvqHeader *D_80102D40_name_81 BSS;
u8 D_80102D44_name_81[4] BSS; /* Unreferenced. */
OverlayBgEntry D_80102D48_name_81[50] BSS;
OverlayBgEntry *D_80103130_name_81[6][6] BSS;
HvqFileHeader *D_801031C0_name_81 BSS;
Process *D_801031C4_name_81 BSS;
Process *D_801031C8_name_81 BSS;
f32 D_801031CC_name_81 BSS;
f32 D_801031D0_name_81 BSS;
Vec D_801031D4_name_81 BSS;
Vec D_801031E0_name_81 BSS;
Vec D_801031EC_name_81 BSS;
Vec D_801031F8_name_81 BSS;
Vec D_80103204_name_81 BSS;
OSMesgQueue D_80103210_name_81 BSS;
OSMesg D_80103228_name_81[50] BSS;
OSThread D_801032F0_name_81 BSS;
u8 D_801034A0_name_81[0x800] BSS; // Stack of the D_801032F0_name_81 thread.
OSThread D_80103CA0_name_81 BSS;
OSPri D_80103E50_name_81 BSS;
u8 D_80103E54_name_81[0x80C] BSS; // Stack of the D_80103CA0_name_81 thread.
OSMesgQueue D_80104660_name_81 BSS;
OSMesg D_80104678_name_81[50] BSS;
OSMesgQueue D_80104740_name_81 BSS;
OSMesg D_80104758_name_81[50] BSS;
OSMesgQueue D_80104820_name_81 BSS;
OSMesg D_80104838_name_81[2] BSS;
Vec2f D_80104840_name_81 BSS;
f32 D_80104848_name_81[2] BSS;
UnkBoard7 D_80104850_name_81[64] BSS;
s32 D_80105050_name_81 BSS;
u8 D_80105054_name_81[4] BSS; /* Unreferenced. */
Object *D_80105058_name_81[16] BSS;
u8 D_80105098_name_81[8] BSS; /* Unreferenced. */

// masu.c
u16 D_801050A0_name_81 BSS;
u16 D_801050A2_name_81 BSS;
SpaceData *D_801050A4_name_81 BSS;
LinkData *D_801050A8_name_81 BSS;
u8 D_801050AC_name_81[4] BSS; /* Unreferenced. */
MasuBmp *D_801050B0_name_81[19] BSS;
s16 D_801050FC_name_81 BSS;
u16 D_801050FE_name_81 BSS;
u8 D_80105100_name_81[19] BSS;
event_list_entry *D_80105114_name_81 BSS;
event_list_entry *D_80105118_name_81 BSS;
event_list_entry *D_8010511C_name_81 BSS;
event_list_entry *D_80105120_name_81 BSS;
s32 D_80105124_name_81 BSS;
f32 D_80105128_name_81[8] BSS;
s32 D_80105148_name_81 BSS;
u8 D_8010514C_name_81[4] BSS; /* Unreferenced. */
s16 D_80105150_name_81[255] BSS;
s16 D_8010534E_name_81 BSS;
s16 D_80105350_name_81[16] BSS;
s16 D_80105370_name_81 BSS;
s16 D_80105372_name_81 BSS; /* Unreferenced. */
u8 D_80105374_name_81[4] BSS; /* Unreferenced. */
s32 D_80105378_name_81[0x13] BSS;
u8 D_801053C4_name_81[4] BSS; /* Unreferenced. */
s16 D_801053C8_name_81[12] BSS;

// pause.c
UnkOvl81_2 *D_801053E0_name_81 BSS;
s16 D_801053E4_name_81 BSS;
s16 D_801053E6_name_81 BSS;
s32 D_801053E8_name_81 BSS;
s32 D_801053EC_name_81 BSS;
s16 D_801053F0_name_81[2] BSS;
s16 D_801053F4_name_81 BSS;
s16 D_801053F6_name_81 BSS; /* Unreferenced. */
u8 D_801053F8_name_81[8] BSS; /* Unreferenced. */

// sprgrp.c
UnkBoard4 *D_80105400_name_81 BSS;
u16 D_80105404_name_81 BSS;
s16 D_80105406_name_81 BSS; /* Unreferenced. */
u8 D_80105408_name_81[8] BSS; /* Unreferenced. */

// status.c
Process *D_80105410_name_81 BSS;
NameSpriteIds D_80105414_name_81 BSS;
s16 D_80105420_name_81 BSS;
s16 D_80105422_name_81 BSS;
f32 D_80105424_name_81 BSS;
Vec2f D_80105428_name_81 BSS;
Vec2f D_80105430_name_81 BSS;
Vec2f D_80105438_name_81 BSS;
s16 D_80105440_name_81 BSS;
omObjData *D_80105444_name_81[3] BSS;

// partner.c
Object *mbdPartnerObj[MBD_MAX_PLAYERS][PARTNEROBJINDEX_MAX] BSS;
Vec D_80105460_name_81 BSS;
u8 D_8010546C_name_81[4] BSS; /* Unreferenced. */
s16 D_80105470_name_81[8] BSS;
s16 D_80105480_name_81[8] BSS;

// main.c
s32 D_80105490_name_81 BSS;
s16 D_80105494_name_81 BSS;
s16 D_80105496_name_81 BSS;
s32 D_80105498_name_81 BSS;
s16 D_8010549C_name_81 BSS;
s16 D_8010549E_name_81 BSS;
Vec D_801054A0_name_81 BSS;
Vec *D_801054AC_name_81 BSS;
UnkE3CD0 *D_801054B0_name_81 BSS;
u8 D_801054B4_name_81[4] BSS; /* Unreferenced. */
Vec D_801054B8_name_81[2] BSS;
Vec D_801054D0_name_81[2][2] BSS;

// scroll.c
omObjData *D_80105500_name_81 BSS;
UnkBoard4 *D_80105504_name_81 BSS;
s16 D_80105508_name_81[4][2] BSS;
UnkBoard4 *D_80105518_name_81 BSS;
Process *D_8010551C_name_81 BSS;
Object *D_80105520_name_81[MBD_MAX_PLAYERS] BSS;
f32 D_80105528_name_81 BSS;
Vec2f D_8010552C_name_81 BSS;
u8 D_80105534_name_81[0xC] BSS; /* Unreferenced. */

// Shared between files.
Vec D_80105540_name_81 BSS;
s32 D_8010554C_name_81 BSS;
s32 D_80105550_name_81 BSS;
u8 D_80105554_name_81 BSS;
u8 D_80105555_name_81 BSS;
s32 D_80105558_name_81 BSS;
s16 D_8010555C_name_81 BSS;
UnkD6B00 D_80105560_name_81[16] BSS;
s32 D_80105620_name_81 BSS;
s16 D_80105624_name_81 BSS;
s32 D_80105628_name_81 BSS;
u8 D_8010562C_name_81 BSS;
NamePlayerData D_80105630_name_81[2] BSS;
f32 D_80105708_name_81 BSS;
s32 D_8010570C_name_81 BSS;
u8 D_80105710_name_81 BSS;
s16 D_80105712_name_81 BSS;
u8 D_80105714_name_81[4] BSS; /* Unreferenced. */
s32 D_80105718_name_81 BSS;
s32 D_8010571C_name_81 BSS;
