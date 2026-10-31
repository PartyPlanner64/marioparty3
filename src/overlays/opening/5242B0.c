#include "common.h"
#include "../ovl_80_shared_board/FA250.h"
#include "mallocblock.h"
#include "opening.h"

void opEventInit(void) {
    opDemoEndReset();
}

void opTitleCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opTitleMain, 0x5000, 0x800, 0);
}

void opDemoCreate(void) {
    opEventInit();
    D_80114EA0_opening = omAddPrcObj(opDemoMain, 0x5000, 0x800, 0);
}

Process *opDemoEventCreate(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *eventPrc = omAddPrcObj(opDemoEvent, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, eventPrc);
    return eventPrc;
}

void opDemoMain(void) {
    Process *parentPrc;
    Process *eventPrc;

    Hu3DBGColorSet(0, 0, 0);
    opDemoEventSetup();
    parentPrc = HuPrcCurrentGet();
    eventPrc = opDemoEventCreate();
    WipeCreateIn(11, 16);
    HuPrcSleep(16);
    while (1) {
        HuPrcVSleep();
        if (omovlevtno == 1) {
            if (opBtnStartCheck() && _CheckFlag(50)) {
                WipeColorSet(255, 255, 255);
                WipeCreateOut(11, 20);
                HuAudSeqFadeOut(20);
                break;
            }
        } else if (opBtnStartCheck()) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            break;
        }
        if (!HuPrcChildGet(parentPrc) || opDemoEndGet()) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(50);
            break;
        }
    }
    do {
        HuPrcVSleep();
    } while (WipeStatGet());
    if (HuPrcChildGet(parentPrc)) {
        omDelPrcObj(eventPrc);
    }
    opDemoEventKill();
    HuWinAllKill();
    omOvlKill();
    if (omovlevtno == 0) {
        omOvlGotoEx(122, 0, 0x82);
    } else if (omovlevtno == 1) {
        if (!_CheckFlag(50)) {
            _SetFlag(50);
            SLCommonSet(1);
        }
        omOvlReturnEx(1);
    } else {
        omOvlGotoEx(122, 0, 0x82);
    }
    omDelPrcObj(NULL);
    while (1) {
        HuPrcVSleep();
    }
}

Process *func_80105F68_opening(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *sprPrc = omAddPrcObj(opTitleSprMain, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, sprPrc);
    return sprPrc;
}

void opTitleMain(void) {
    s32 frame;
    Process *parentPrc;
    Process *sprPrc;

    Hu3DBGColorSet(0, 64, 64);
    frame = 0;
    opTitleSetup();
    parentPrc = HuPrcCurrentGet();
    sprPrc = func_80105F68_opening();
    WipeColorSet(255, 255, 255);
    WipeCreateIn(11, 16);
    HuPrcSleep(16);
    HuPrcSleep(60);
    while (1) {
        HuPrcVSleep();
        if (opBtnStartCheck()) {
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            do {
                HuPrcVSleep();
            } while (WipeStatGet());
            if (HuPrcChildGet(parentPrc)) {
                omDelPrcObj(sprPrc);
            }
            opTitleKill();
            HuWinAllKill();
            omOvlKill();
            omOvlGotoEx(121, 0, 0x91);
            omDelPrcObj(NULL);
            while (1) {
                HuPrcVSleep();
            }
        }
        if (HuPrcChildGet(parentPrc) && !opDemoEndGet() && frame < 5401) {
            frame++;
        } else {
            WipeCreateOut(11, 20);
            HuAudSeqFadeOut(20);
            do {
                HuPrcVSleep();
            } while (WipeStatGet());
            if (HuPrcChildGet(parentPrc)) {
                omDelPrcObj(sprPrc);
            }
            opTitleKill();
            HuWinAllKill();
            omOvlKill();
            omOvlGotoEx(88, 1, 0x90);
            omDelPrcObj(NULL);
            while (1) {
                HuPrcVSleep();
            }
        }
    }
}

s32 opBtnStartCheck(void) {
    if (GWContErrorGet() == 1) {
        return (D_800D5558_main[0] & 0x1000) != 0;
    }
    return 0;
}

void opDemoEndReset(void) {
    D_80114EA4_opening = 0;
}

void opDemoEndSet(s32 value) {
    D_80114EA4_opening = value;
}

s32 opDemoEndGet(void) {
    return D_80114EA4_opening;
}
