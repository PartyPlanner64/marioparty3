#ifndef _GAME_PAD_H
#define _GAME_PAD_H

#include "ultra64.h"
#include "game/siman.h"
#include "game/input.h"

#define PAD_NOT_INSERTED 0

typedef struct {
    OSContPad pad;
    s32 unk[4];
} HuPad;

extern u16 D_800CBB66_main[];
extern s16 D_800CDA7C_main[];
extern s16 D_800D056A_main[];
extern u16 D_800D1244_main[];
extern s16 D_800D1382_main[];
extern s8 D_800CE2D0_main[][8];
extern s8 D_800D5418_main[][8];
extern s16 D_800D5542_main;
extern s16 gNumOfControllers;
extern s8 D_800D20A1_main[];
s32 _InitController(u16* channel);
s16 InitController(s16 ch, s32 arg1);
s32 _ReadController(s32 arg0);
void SetStickValueLimit(s8 arg0, s8 arg1);
s16 UpdateController(void);
void _AutoReadController(void);
void SetAutoReadController(void);
void ResetAutoReadController(void);
s32 CheckControllerRead(s16 padNum);
s16 FlushController(void);

void ReadController(void);

#endif
