#ifndef _COMMON_DUEL_H_
#define _COMMON_DUEL_H_

// For overlays that run alongside the duel overlay (ovl_81_name).

#include "common.h"

// Duel board space types (SpaceData.space_type). These differ from the party board SPACE_* values.
#define MBD_MASU_TYPE_UNK1 1
#define MBD_MASU_TYPE_HAPPENING 2
#define MBD_MASU_TYPE_GAMEGUY 3
#define MBD_MASU_TYPE_UNK4 4 // seen on spaces that have events
#define MBD_MASU_TYPE_REVERSE 5
#define MBD_MASU_TYPE_BASIC 6 // basic space without an owner
#define MBD_MASU_TYPE_START_RED 7
#define MBD_MASU_TYPE_MINIGAME 8
#define MBD_MASU_TYPE_START_BLUE 9
#define MBD_MASU_TYPE_POWERUP 10
#define MBD_MASU_TYPE_CHR_BASE 11 // basic spaces owned by a character, one per CHAR_* value
#define MBD_MASU_TYPE_CHR(chr) ((chr) + MBD_MASU_TYPE_CHR_BASE)
#define MBD_MASU_TYPE_MAX 19

// The duel overlay's copy of the board model code adds a motion count at 0x44,
// shifting the board layout's unk44/unk46 to 0x46/0x48.
struct Object_s {
/* 0x00 */ struct Object_s *prev;
/* 0x04 */ struct Object_s *next;
/* 0x08 */ u8 unk8;
/* 0x09 */ s8 unk9;
/* 0x0A */ u16 flags;
/* 0x0C */ Vec coords;
/* 0x18 */ Vec rot;
/* 0x24 */ Vec scale;
/* 0x30 */ Vec velocity;
/* 0x3C */ omObjData* omObj1;
/* 0x40 */ omObjData* omObj2;
/* 0x44 */ s16 mtncnt; // -1 when the model has no motion table
/* 0x46 */ s16 unk46; // board layout's unk44
/* 0x48 */ s16 unk48; // board layout's unk46
}; //sizeof 0x4C

#endif
