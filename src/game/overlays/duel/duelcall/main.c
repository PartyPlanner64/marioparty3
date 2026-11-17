#include "common.h"

void MBDOvlCallInit(void);
void MBDOvlCallExec(void);

void duelcall_Start(void) {
    if (_CheckFlag(0)) {
        GWBoardFlagSet(1);
    } else {
        GWBoardFlagClear(1);
    }
    omInitObjMan(0xA, 0);
    MBDOvlCallInit();
    omOvlGotoEx(duelcall, 1, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
    omOvlHisChg(0, 0x5A, 1, OM_OVL_STAT_DUEL | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
}

void duelcall_Exec(void) {
    omInitObjMan(0xA, 0);
    MBDOvlCallExec();
}

void duelcall_ReturnProc(void) {
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void duelcall_ObjectSetup(void) {
    omInitObjMan(0xA, 0xA);
    omGameSysInit();
    omAddPrcObj(duelcall_ReturnProc, 0x1005, 0, 0);
}
