#ifndef _PARTY_COMMON_WINDOW_H
#define _PARTY_COMMON_WINDOW_H

#include "common_board.h"
#include "game/board.h"

void MBWinIdPlayerKeyWait(s16 arg0, s32 arg1);
s16 MBWinCreate(s16 arg0, s16 *arg1, s16 arg2);
void MBWinOpen(s32 arg0);
void MBWinInsertOpen(s32 arg0, char *arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5);
void MBWinKeyWaitKeep(s32 arg0);
void MBWinKeyWait(s32 arg0);
void MBWinClose(void);
void MBDlgResultWinExec(s32 arg0);
void MBDlgWinExecY(s16 arg0, s32 arg1, s32 arg2);
void MBDlgWinExec(s32 arg0, s32 arg1);
void MBDlgWinExecAllKey(s16 arg0, s32 arg1);
void MBDlgWinExecYAllKey(s16 arg0, s32 arg1, s16 arg2);
void MBDlgWinCreate(s32 arg0, s32 arg1);
void MBDlgWinOpen(void);
void MBDlgWinClose(void);
void MBDlgWinKill(void);
void MBDlgWinInsertCreateY(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7);
void MBDlgWinInsertCreate(s16 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void MBDlgWinInsertCreateAllKey(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6);
void MBDlgWinInsertCreateYAllKey(s16 arg0, s32 arg1, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, s16 arg7);
void MBDlgWinMesWait(void);
void MBDlgWinMesWaitAllKey(void);
void MBDlgWinTabWidthSet(s32 arg0);
void MBDlgWinParamReset(void);

#endif //_PARTY_COMMON_WINDOW_H
