#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "ultra64.h"
#include "common_structs.h"

/* Globals whose owning module is not yet known. Most are main segment BSS
 * shared with board overlays. */
extern s16 D_800CDBC8_main;
extern UnkDiceRelated D_800CDBD0_main[5];
extern s16 D_800CDD64_main;
extern u8 D_800CC0C0_main;
extern s32 D_800A12D4_main;
extern s32 D_800A12D8_main;
extern s8 D_800A12D0_main;
extern s16 D_800D51F8_main;
extern s16 D_800C9930_main;
extern char D_800D5218_main[];
extern u16 D_800D5558_main[4];
extern u16 D_800D530C_main;
extern u8 D_800D6A58_main;

// extern Unk800D6B48 D_800D6B48_main[2];

extern s16 D_800CC0B8_main;
extern s16 D_800D6A48_main;

#endif //_VARIABLES_H_
