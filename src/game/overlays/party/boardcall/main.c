#include "common.h"

void MBOvlCallInit(void);
void MBOvlCallExec(void);

// entry 0
void boardcall_Start(void) {
    if (_CheckFlag(0) != 0) {
        GWBoardFlagSet(1);
    } else {
        GWBoardFlagClear(1);
    }
    omInitObjMan(0xA, 0);
    MBOvlCallInit();
    omOvlGotoEx(boardcall, 1, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
    omOvlHisChg(0, boardcall, 1, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3 | OM_OVL_STAT_AUDFX1);
}

// entry 1
void boardcall_Exec(void) {
    omInitObjMan(0xA, 0);
    MBOvlCallExec();
}

void boardcall_ReturnProc(void) {
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

// entry 2
void boardcall_ObjectSetup(void) {
    omInitObjMan(0xA, 0xA);
    omGameSysInit();
    omAddPrcObj(boardcall_ReturnProc, 0x1005, 0, 0);
}
