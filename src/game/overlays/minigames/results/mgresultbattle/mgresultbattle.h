#ifndef _MGRESULTBATTLE_H
#define _MGRESULTBATTLE_H

#include "game/object.h"

typedef struct {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ omObjFunc func;
} ResultBattlePlayerObj;

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 x;
    /* 0x10 */ f32 y;
    /* 0x14 */ f32 z;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
} ResultBattleEffect; /* size = 0x20 */

#ifndef NO_EXTERN_VARIABLES
extern ResultBattlePlayerObj mgresultbattle_playerWorkTbl[4];
extern s32 mgresultbattle_coinRest;
extern s8 mgresultbattle_playerOrderTbl[4];
extern const Vec mgresultbattle_playerPosTbl[4];
#endif

/* main.c */
void mgresultbattle_PlayerReactStart(void);

/* host.c */
void mgresultbattle_CoinProc(void);
void mgresultbattle_HostProc(void);
void mgresultbattle_HostFlyStart(void);

/* player.c */
void mgresultbattle_PodiumProc(void);
void mgresultbattle_CoinNumProc(void);
void mgresultbattle_CoinNumShowStart(void);

#endif
