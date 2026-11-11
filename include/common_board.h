#ifndef _COMMON_BOARD_H_
#define _COMMON_BOARD_H_

// For overlays that run alongside the board overlay (ovl_80_shared_board).

#include "common.h"

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
/* 0x44 */ s16 unk44;
/* 0x46 */ s16 unk46;
}; //sizeof 0x48

#endif
