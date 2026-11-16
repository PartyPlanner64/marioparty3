#ifndef _PARTY_COMMON_MGCALL_H
#define _PARTY_COMMON_MGCALL_H

#include "common_board.h"

typedef struct ItemSlotEntry {
    /* 0x00 */ s16 obj;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 w;
    /* 0x08 */ s16 h;
} ItemSlotEntry; // sizeof 0xA

void MBMgCallHisInit(void);
void MBMgCallInit(void);
void MBMgCallClose(void);
void MBMgCallListCreate(s32 arg0);
void MBMgCallListClose(void);
void MBArrayShuffle(u8 *output, s32 count);
Process *MBMgCallCreate(void);
Process *MBMgCallBattleCreate(void);
Process *MBMgCallGambleCreate(void);
Process *MBMgCallKettouCreate(s32 arg0, s32 arg1);
Process *MBMgCallTutorialCreate(void);

#endif //_PARTY_COMMON_MGCALL_H