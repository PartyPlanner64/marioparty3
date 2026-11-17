#include "common.h"
#include "game/overlays/party/common/back.h"
#include "game/mallocblock.h"
#include "game/overlays/opening.h"

void op_EventInit(void) {
    op_DemoEndReset();
}

void op_TitleCreate(void) {
    op_EventInit();
    op_mainProc = omAddPrcObj(op_TitleMain, 0x5000, 0x800, 0);
}

void op_DemoCreate(void) {
    op_EventInit();
    op_mainProc = omAddPrcObj(op_DemoMain, 0x5000, 0x800, 0);
}

Process *op_DemoEventCreate(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *eventPrc = omAddPrcObj(op_DemoEvent, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, eventPrc);
    return eventPrc;
}

void op_DemoMain(void) {
    Process *parentPrc;
    Process *eventPrc;

    Hu3DBGColorSet(0, 0, 0);
    op_DemoEventSetup();
    parentPrc = HuPrcCurrentGet();
    eventPrc = op_DemoEventCreate();
    WipeCreateIn(WIPE_FADE, 16);
    HuPrcSleep(16);
    while (1) {
        HuPrcVSleep();
        if (omovlevtno == 1) {
            if (op_BtnStartCheck() && _CheckFlag(50)) {
                WipeColorSet(255, 255, 255);
                WipeCreateOut(WIPE_FADE, 20);
                HuAudSeqFadeOut(20);
                break;
            }
        } else if (op_BtnStartCheck()) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 20);
            HuAudSeqFadeOut(20);
            break;
        }
        if (!HuPrcChildGet(parentPrc) || op_DemoEndGet()) {
            WipeColorSet(255, 255, 255);
            WipeCreateOut(WIPE_FADE, 20);
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
    op_DemoEventKill();
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

Process *op_TitleSprCreate(void) {
    Process *parentPrc = HuPrcCurrentGet();
    Process *sprPrc = omAddPrcObj(op_TitleSprMain, 0x5000, 0x2000, 0);

    HuPrcChildLink(parentPrc, sprPrc);
    return sprPrc;
}

void op_TitleMain(void) {
    s32 frame;
    Process *parentPrc;
    Process *sprPrc;

    Hu3DBGColorSet(0, 64, 64);
    frame = 0;
    op_TitleSetup();
    parentPrc = HuPrcCurrentGet();
    sprPrc = op_TitleSprCreate();
    WipeColorSet(255, 255, 255);
    WipeCreateIn(WIPE_FADE, 16);
    HuPrcSleep(16);
    HuPrcSleep(60);
    while (1) {
        HuPrcVSleep();
        if (op_BtnStartCheck()) {
            WipeCreateOut(WIPE_FADE, 20);
            HuAudSeqFadeOut(20);
            do {
                HuPrcVSleep();
            } while (WipeStatGet());
            if (HuPrcChildGet(parentPrc)) {
                omDelPrcObj(sprPrc);
            }
            op_TitleKill();
            HuWinAllKill();
            omOvlKill();
            omOvlGotoEx(121, 0, 0x91);
            omDelPrcObj(NULL);
            while (1) {
                HuPrcVSleep();
            }
        }
        if (HuPrcChildGet(parentPrc) && !op_DemoEndGet() && frame < 5401) {
            frame++;
        } else {
            WipeCreateOut(WIPE_FADE, 20);
            HuAudSeqFadeOut(20);
            do {
                HuPrcVSleep();
            } while (WipeStatGet());
            if (HuPrcChildGet(parentPrc)) {
                omDelPrcObj(sprPrc);
            }
            op_TitleKill();
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

s32 op_BtnStartCheck(void) {
    if (GWContErrorGet() == 1) {
        return (HuPadBtnDown[0] & START_BUTTON) != 0;
    }
    return 0;
}

void op_DemoEndReset(void) {
    op_demoEndF = 0;
}

void op_DemoEndSet(s32 value) {
    op_demoEndF = value;
}

s32 op_DemoEndGet(void) {
    return op_demoEndF;
}
