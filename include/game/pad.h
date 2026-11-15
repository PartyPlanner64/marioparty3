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

#ifndef NO_EXTERN_VARIABLES
extern u16 HuPadBtnOld[];
extern s16 HuPadBtn[];
extern s16 HuPadStkXSum[];
extern u16 HuPadBtnRep[];
extern s16 HuPadStkYSum[];
extern s8 HuPadStkXHis[][8];
extern s8 HuPadStkYHis[][8];
extern s16 HuPadReadNum;
extern s16 gNumOfControllers;
extern s8 HuPadStkY[];
#endif
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
