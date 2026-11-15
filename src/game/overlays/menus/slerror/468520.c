#include "common.h"
#include "game/esprite.h"
#include "game/object.h"
#include "game/saveload.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/wipe.h"
#include "variables.h"

s16 D_80105F40_slerror[4] BSS;
s16 D_80105F48_slerror[4] BSS;

void func_801059D0_slerror(void);

void func_801059D0_slerror(void) {
    u16 count;
    s16 anim;
    s16 sprite;
    u16 i;

    if (D_800D20EC_main & 0x10) {
        omOvlGotoEx(0x58, 0, 0x81);
        omOvlKill();
        HuPrcVSleep();
    }
    HuWinInit();
    if (D_800D20EC_main == 0xF) {
        count = 1;
        D_80105F48_slerror[0] = sprite = espEntry(D_80105F40_slerror[0] = HuSprAnimDataRead(0x200000), 0, 1);
        espPosSet(sprite, 160, 120);
        espAttrReset(sprite, 0xFFFF);
        espAttrSet(sprite, 0x1000);
        espColorSet(sprite, 255, 255, 255);
        espDispOff(sprite);
    } else {
        count = 0;
        if (D_800D20EC_main & 8) {
            D_80105F40_slerror[0] = anim = HuSprAnimDataRead(0x200004);
            D_80105F48_slerror[0] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count = 1;
        }
        if (D_800D20EC_main & 1) {
            D_80105F40_slerror[count] = anim = HuSprAnimDataRead(0x200001);
            D_80105F48_slerror[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
        if (D_800D20EC_main & 2) {
            D_80105F40_slerror[count] = anim = HuSprAnimDataRead(0x200002);
            D_80105F48_slerror[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
        if (D_800D20EC_main & 4) {
            D_80105F40_slerror[count] = anim = HuSprAnimDataRead(0x200003);
            D_80105F48_slerror[count] = sprite = espEntry(anim, 0, 1);
            espPosSet(sprite, 160, 120);
            espAttrReset(sprite, 0xFFFF);
            espAttrSet(sprite, 0x1000);
            espColorSet(sprite, 255, 255, 255);
            espDispOff(sprite);
            count++;
        }
    }
    for (i = 0; i < count; i++) {
        espDispOn(D_80105F48_slerror[i]);
        WipeCreateIn(0xB, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        do {
            HuPrcVSleep();
        } while ((D_800D5558_main[0] | D_800D5558_main[1] | D_800D5558_main[2] | D_800D5558_main[3]) == 0);
        WipeCreateOut(0xB, 8);
        while (WipeStatGet() != 0) {
            HuPrcVSleep();
        }
        espDispOff(D_80105F48_slerror[i]);
    }
    for (i = 0; i < count; i++) {
        espKill(D_80105F48_slerror[i]);
        HuSprAnimKill(D_80105F40_slerror[i]);
    }
    HuWinAllKill();
    omOvlGotoEx(0x58, 0, 0x81);
    omOvlKill();
    HuPrcVSleep();
}

void func_80105E9C_slerror(void) {
    omInitObjMan(0xA, 0xA);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}

void func_80105EDC_slerror(void) {
    omInitObjMan(0xA, 0xA);
    func_8004A208_main();
    omAddPrcObj(func_801059D0_slerror, 0x1005, 0, 0);
}
