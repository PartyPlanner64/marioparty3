#define NO_EXTERN_VARIABLES
#include "common_board.h"
#include "game/board.h"
#include "game/gamemes.h"
#include "game/hvq.h"
#include "mapfull.h"
#include "mgcall.h"
#include "back.h"

/*
 * Some halfword arrays in this overlay's BSS are only halfword aligned, which
 * GCC won't produce for standalone arrays. They are grouped into structs here,
 * and the field symbols used by the original code are aliased in
 * undefined_syms.txt.
 */
typedef struct {
    /* 0x00 */ s16 sprGrp;
    /* 0x02 */ s16 sprAnims[2]; // D_80102D3A_shared_board
} SharedBoardBss2D38;

// mapfull.c
s32 D_80102700_shared_board BSS;
s16 D_80102704_shared_board BSS;
UnkBoard6 D_80102708_shared_board[32] BSS;
s16 D_80102A88_shared_board[4] BSS;
s16 D_80102A90_shared_board[4] BSS;
UnkBoard8 *D_80102A98_shared_board[4] BSS;
s16 D_80102AA8_shared_board BSS;
u8 D_80102AAC_shared_board[4] BSS; /* Unreferenced. */

// model.c
Object *D_80102AB0_shared_board BSS;
u16 D_80102AB4_shared_board BSS;
s16 D_80102AB8_shared_board[128] BSS;
u8 D_80102BB8_shared_board[8] BSS; /* Unreferenced. */

// com.c
s32 D_80102BC0_shared_board BSS;
s32 (*D_80102BC4_shared_board)(void) BSS;
u8 D_80102BC8_shared_board[8] BSS; /* Unreferenced. */

// mgcall.c
ItemSlotEntry D_80102BD0_shared_board[5] BSS; // [0].y is D_80102BD4_shared_board
omObjData *D_80102C04_shared_board BSS;
s8 D_80102C08_shared_board[5] BSS;
s8 D_80102C0D_shared_board BSS;
s16 D_80102C0E_shared_board BSS;
s16 D_80102C10_shared_board BSS;
s16 D_80102C12_shared_board BSS;
s16 D_80102C14_shared_board BSS;
u8 D_80102C18_shared_board[8] BSS; /* Unreferenced. */

// coinchange.c
s16 D_80102C20_shared_board[4] BSS;
s16 D_80102C28_shared_board[4][2] BSS;
omObjData *D_80102C38_shared_board[4] BSS;
u8 D_80102C48_shared_board BSS;
u8 D_80102C4C_shared_board[4] BSS; /* Unreferenced. */

// item.c
s16 D_80102C50_shared_board BSS;
s16 D_80102C52_shared_board BSS;
u8 D_80102C54_shared_board[4] BSS; /* Unreferenced. */
void (*MBItemSubFunctions[22])(void) BSS;
s32 D_80102CB0_shared_board BSS;
s32 D_80102CB4_shared_board BSS;
u8 D_80102CB8_shared_board[8] BSS; /* Unreferenced. */
GAMEMES D_80102CC0_shared_board BSS;
s16 D_80102D34_shared_board BSS;
u8 D_80102D36_shared_board BSS;
SharedBoardBss2D38 D_80102D38_shared_board BSS;
omObjData *D_80102D40_shared_board BSS;
omObjData *D_80102D44_shared_board BSS;
s16 D_80102D48_shared_board[2] BSS;
s16 D_80102D4C_shared_board[2] BSS;
s32 D_80102D50_shared_board BSS;
Object *D_80102D54_shared_board BSS;
s32 D_80102D58_shared_board BSS;
u8 D_80102D5C_shared_board[4] BSS; /* Unreferenced. */
Vec D_80102D60_shared_board BSS;
Vec D_80102D6C_shared_board BSS;
Vec D_80102D78_shared_board BSS;
Vec D_80102D84_shared_board BSS;
Vec D_80102D90_shared_board BSS;
u8 D_80102D9C_shared_board[4] BSS; /* Unreferenced. */

// ksuit.c
s16 D_80102DA0_shared_board BSS;
u8 D_80102DA4_shared_board[0xC] BSS; /* Unreferenced. */

// back.c
u32 D_80102DB0_shared_board BSS;
s32 D_80102DB4_shared_board BSS;
s32 D_80102DB8_shared_board BSS;
f32 D_80102DBC_shared_board BSS;
u16 D_80102DC0_shared_board BSS;
s16 D_80102DC2_shared_board BSS;
s16 D_80102DC4_shared_board BSS;
s16 D_80102DC6_shared_board BSS;
s16 D_80102DC8_shared_board BSS;
u8 *D_80102DCC_shared_board BSS;
HvqHeader *D_80102DD0_shared_board BSS;
u8 D_80102DD4_shared_board[4] BSS; /* Unreferenced. */
OverlayBgEntry D_80102DD8_shared_board[36] BSS;
OverlayBgEntry *D_801030A8_shared_board[6][6] BSS;
HvqFileHeader *D_80103138_shared_board BSS;
u8 D_8010313C_shared_board[4] BSS; /* Unreferenced. */
OverlayBgEntry D_80103140_shared_board[36] BSS;
Process *D_80103410_shared_board BSS;
Process *D_80103414_shared_board BSS;
f32 D_80103418_shared_board BSS;
f32 D_8010341C_shared_board BSS;
Vec D_80103420_shared_board BSS;
Vec D_8010342C_shared_board BSS;
Vec D_80103438_shared_board BSS;
Vec D_80103444_shared_board BSS;
Vec D_80103450_shared_board BSS;
s32 D_8010345C_shared_board BSS;
s32 D_80103460_shared_board BSS;
UnkFAF78 *D_80103464_shared_board BSS;
OSMesgQueue D_80103468_shared_board BSS;
OSMesg D_80103480_shared_board[36] BSS;
OSThread D_80103510_shared_board BSS;
u64 D_801036C0_shared_board[0x100] BSS; /* Thread stack, top is D_80103EC0_shared_board. */
OSThread D_80103EC0_shared_board BSS;
s32 D_80104070_shared_board BSS;
u8 D_80104074_shared_board[0xC] BSS; /* Unreferenced. */
u64 D_80104080_shared_board[0x100] BSS; /* Thread stack, top is D_80104880_shared_board. */
OSMesgQueue D_80104880_shared_board BSS;
OSMesg D_80104898_shared_board[36] BSS;
OSMesgQueue D_80104928_shared_board BSS;
OSMesg D_80104940_shared_board[36] BSS;
OSMesgQueue D_801049D0_shared_board BSS;
OSMesg D_801049E8_shared_board[2] BSS;
Vec2f D_801049F0_shared_board BSS;
f32 D_801049F8_shared_board[2] BSS;
UnkBoard7 D_80104A00_shared_board[64] BSS;
s32 D_80105200_shared_board BSS;
u8 D_80105204_shared_board[0xC] BSS; /* Unreferenced. */
u16 gTotalSpaces BSS;
u16 D_80105212_shared_board BSS;
SpaceData *D_80105214_shared_board BSS;
LinkData *D_80105218_shared_board BSS;
u8 D_8010521C_shared_board[4] BSS; /* Unreferenced. */
u8 *D_80105220_shared_board[16] BSS;
s16 D_80105260_shared_board BSS;
u16 D_80105262_shared_board BSS;
u8 D_80105264_shared_board[4] BSS; /* Unreferenced. */
u8 D_80105268_shared_board[16] BSS;
void *D_80105278_shared_board BSS;
void *D_8010527C_shared_board BSS;
void *D_80105280_shared_board BSS;
void *D_80105284_shared_board BSS;
s32 D_80105288_shared_board BSS;
u8 D_8010528C_shared_board[4] BSS; /* Unreferenced. */
f32 D_80105290_shared_board[8] BSS;
s32 D_801052B0_shared_board BSS;
u8 D_801052B4_shared_board[4] BSS; /* Unreferenced. */
s16 D_801052B8_shared_board[255] BSS;
s16 D_801054B6_shared_board BSS;
s16 D_801054B8_shared_board[32] BSS;
s16 D_801054F8_shared_board BSS;
u8 D_801054FC_shared_board[4] BSS; /* Unreferenced. */
s32 D_80105500_shared_board[16] BSS;
s16 D_80105540_shared_board[8] BSS;

// pause.c
UnkMBGuideData *D_80105550_shared_board BSS;
s16 D_80105554_shared_board BSS;
s16 D_80105556_shared_board BSS;
s32 D_80105558_shared_board BSS;
s32 D_8010555C_shared_board BSS;
s16 D_80105560_shared_board[2] BSS;
s16 D_80105564_shared_board BSS;
u8 D_80105568_shared_board[8] BSS; /* Unreferenced. */

// sprgrp.c
UnkBoard8 *D_80105570_shared_board BSS;
u16 D_80105574_shared_board BSS;
u8 D_80105578_shared_board[8] BSS; /* Unreferenced. */

// status.c
Process *D_80105580_shared_board BSS;
u8 D_80105584_shared_board[4] BSS; /* Unreferenced. */
s16 D_80105588_shared_board[29] BSS;
s16 D_801055C2_shared_board BSS;
s16 D_801055C4_shared_board BSS;
f32 D_801055C8_shared_board BSS;
Vec2f D_801055CC_shared_board BSS;
Vec2f D_801055D4_shared_board BSS;
Vec2f D_801055DC_shared_board BSS;
s16 D_801055E4_shared_board BSS;
omObjData *D_801055E8_shared_board[4] BSS;
s32 D_801055F8_shared_board BSS;
s16 D_801055FC_shared_board[4] BSS;
u8 D_80105604_shared_board[4] BSS; /* Unreferenced. */
s16 D_80105608_shared_board[4][3] BSS;

// itemmasu.c
Object *D_80105620_shared_board BSS;
Object *D_80105624_shared_board BSS;
Object *D_80105628_shared_board BSS;
u8 D_8010562C_shared_board[4] BSS; /* Unreferenced. */
s32 D_80105630_shared_board[3] BSS; // [1] is D_80105634_shared_board, [2] is D_80105638_shared_board
u8 D_8010563C_shared_board[0x14] BSS; /* Unreferenced. */
f32 D_80105650_shared_board BSS;
s32 D_80105654_shared_board BSS;
s32 D_80105658_shared_board BSS;
s32 D_8010565C_shared_board BSS;

// main.c
s32 D_80105660_shared_board BSS;
s16 D_80105664_shared_board BSS;
s16 D_80105666_shared_board BSS;
s32 D_80105668_shared_board BSS;
s16 D_8010566C_shared_board BSS;
s16 D_8010566E_shared_board BSS;
Vec D_80105670_shared_board BSS;
Vec *D_8010567C_shared_board BSS;
Vec D_80105680_shared_board[4] BSS;
Object *mbBattleKuriboMdl BSS;
Object *mbBattleKuriboUpperMdl BSS;
omObjData *mbBattleKuriboObj BSS;
u8 D_801056BC_shared_board[4] BSS; /* Unreferenced. */

// scroll.c
omObjData *D_801056C0_shared_board BSS;
UnkBoard8 *D_801056C4_shared_board BSS;
s16 D_801056C8_shared_board[4][2] BSS;
Object *D_801056D8_shared_board[4] BSS;
f32 D_801056E8_shared_board BSS;
Vec2f D_801056EC_shared_board BSS;
u8 D_801056F4_shared_board[0xC] BSS; /* Unreferenced. */

// Variables shared between files
u8 D_80105700_shared_board BSS;
s16 mbDlgWinId BSS;
s8 D_80105704_shared_board BSS;
s16 D_80105706_shared_board BSS;
f32 D_80105708_shared_board BSS;
s16 mbItemCursorGrpId BSS;
u8 D_8010570E_shared_board BSS;
u8 D_8010570F_shared_board BSS;
Object *D_80105710_shared_board BSS;
s16 mbWinId BSS;
UnkBoard D_80105718_shared_board[16] BSS;
u8 D_801057D8_shared_board BSS;
u8 D_801057D9_shared_board BSS;
u8 D_801057DC_shared_board[4] BSS; /* Unreferenced. */
BoardStatus mbStatusData[MB_MAX_PLAYERS] BSS;
s32 D_80105990_shared_board BSS;
