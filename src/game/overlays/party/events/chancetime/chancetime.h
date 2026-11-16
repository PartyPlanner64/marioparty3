#ifndef _CHANCETIME_H
#define _CHANCETIME_H

#include "common.h"

typedef struct ChanceTimeObjState {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
} ChanceTimeObjState;

typedef struct ChanceTimeReel {
    /* 0x00 */ s8 unk00;
    /* 0x01 */ char unk01[3];
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14[3];
    /* 0x1A */ s8 unk1A;
    /* 0x1B */ s8 unk1B[4];
    /* 0x1F */ char unk1F[9];
} ChanceTimeReel; // size = 0x28

typedef struct ChanceTimeTransfer {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
} ChanceTimeTransfer; // size = 0x8

#ifndef NO_EXTERN_VARIABLES
extern s32 chancetime_statusVsF;
extern s8 chancetime_playerOrderTbl[4];
extern s8 chancetime_turnTier;
#endif

void chancetime_PlayerProc(void);
void chancetime_PlayerEnterStart(void);
void chancetime_PlayerJoyExec(void);
void chancetime_PlayerNeutralExec(void);
void chancetime_PlayerSadExec(void);
void chancetime_HostProc(void);
void chancetime_HostHopStart(void);
void chancetime_HostTalkEnd(void);
void chancetime_HostTalkStart(void);
void chancetime_DancerProc(void);
void chancetime_Dancer1Proc(void);
void chancetime_Dancer2Proc(void);
void chancetime_Dancer3Proc(void);
void chancetime_Dancer4Proc(void);
void chancetime_HostLJumpProc(void);
void chancetime_HostRJumpProc(void);
void chancetime_HostTurn(void);
void chancetime_BlockProc(void);
void chancetime_ReelStop(s8 arg0);
void chancetime_EventProc(void);

#endif
