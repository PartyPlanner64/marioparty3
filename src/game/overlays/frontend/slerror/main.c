#include "common.h"
#include "game/esprite.h"
#include "game/object.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "variables.h"

s16 slerror_animTbl[4] BSS;
s16 slerror_sprTbl[4] BSS;

void slerror_MainProc(void);

void slerror_MainProc(void) {
    u16 count;
    s16 anim;
    s16 sprite;
    u16 i;

    if (SLFormatFlags & 0x10) {
        omOvlGotoEx(0x58, 0, 0x81);
        omOvlKill();
        HuPrcVSleep();
    }
    HuWinInit();
    if (SLFormatFlags == 0xF) {
        count = 1;
        slerror_sprTbl[0] = sprite = espEntry(slerror_animTbl[0] = HuSprAnimDataRead(0x200000), 0, 1);
        espPosSet(sprite, 160, 120);
        espAttrReset(sprite, 0xFFFF);
        espAttrSet(sprite, 0x1000);
        espColorSet(sprite, 255, 255, 255);
        espDispOff(sprite);
    } else {
        count = 0;
        if (SLFormatFlags & 8) {
            slerror_animTbl[0] = anim = HuSprAnimDataRead(0x200004);
            slerror_sprTbl[0] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count = 1;
        }
        if (SLFormatFlags & 1) {
            slerror_animTbl[count] = anim = HuSprAnimDataRead(0x200001);
            slerror_sprTbl[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
        if (SLFormatFlags & 2) {
            slerror_animTbl[count] = anim = HuSprAnimDataRead(0x200002);
            slerror_sprTbl[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
        if (SLFormatFlags & 4) {
            slerror_animTbl[count] = anim = HuSprAnimDataRead(0x200003);
            slerror_sprTbl[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
    }
    for (i = 0; i < count; i++) {
        espDispOn(slerror_sprTbl[i]);
        WipeCreateIn(WIPE_FADE, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        do {
            HuPrcVSleep();
        } while ((HuPadBtnDown[0] | HuPadBtnDown[1] | HuPadBtnDown[2] | HuPadBtnDown[3]) == 0);
        WipeCreateOut(WIPE_FADE, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        espDispOff(slerror_sprTbl[i]);
    }
    for (i = 0; i < count; i++) {
        espKill(slerror_sprTbl[i]);
        HuSprAnimKill(slerror_animTbl[i]);
    }
    HuWinAllKill();
    omOvlGotoEx(0x58, 0, 0x81);
    omOvlKill();
    HuPrcVSleep();
}

void slerror_ObjectSetup(void) {
    omInitObjMan(0xA, 0xA);
    omGameSysInit();
    omAddPrcObj(slerror_MainProc, 0x1005, 0, 0);
}

void slerror_ObjectSetupAlt(void) {
    omInitObjMan(0xA, 0xA);
    omGameSysInit();
    omAddPrcObj(slerror_MainProc, 0x1005, 0, 0);
}
