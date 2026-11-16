#include "staff.h"

s32 staff_fireworkSprTbl[8] = {
    0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045
};
ModeCameraPreset staff_cameraPreset = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1390.0f, 32.0f };

const char staff_titleStr[] = "MARIO PARTY 3 STAFF";

void staff_MainProc(void) {
    GAMEMES gMes;
    s16 stat0;
    s16 stat1;
    s16 stat2;
    s16 stat3;
    s16 stat4;
    s16 stat5;
    s16 stat6;
    s16 strId;
    s16 grpId;
    s16 tpLvl;
    s16 time;
    s32 i;

    Hu3DScreenClearF = 1;
    staff_CameraPresetSet(&staff_cameraPreset);
    staff_TextLineInit(0, 6);
    staff_TextLineInit(1, 12);
    stat0 = 0;
    omAddPrcObj(staff_BackProc, 0x4200, 0x800, 0)->user_data = &stat0;
    stat1 = 0;
    omAddPrcObj(staff_StarProc, 0x4000, 0, 0)->user_data = &stat1;
    stat2 = 0;
    omAddPrcObj(staff_CreditRollProc, 0x4000, 0, 0)->user_data = &stat2;
    stat3 = 0;
    omAddPrcObj(staff_HostProc, 0x4000, 0, 0)->user_data = &stat3;
    stat4 = 0;
    omAddPrcObj(staff_FireworkShowProc, 0x1000, 0, 0)->user_data = &stat4;
    strId = GameMesStrInit(&gMes, (char *)staff_titleStr, 0, -1, -1);
    grpId = gMes.strGId[strId];
    HuSprPosSet(grpId, 0, 160, 120);
    for (i = 1; i < 20; i++) {
        HuSprTPLvlSet(grpId, i, 0);
        HuSprDispOff(grpId, i);
    }
    WipeCreateIn(staff_wipeType, 16);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(6);
    stat4 = 1;
    for (time = 30; time != 0; time--) {
        HuPrcVSleep();
    }
    for (i = 1; i < 20; i++) {
        HuSprDispOn(grpId, i);
    }
    for (tpLvl = 64; tpLvl <= 256; tpLvl += 64) {
        for (i = 1; i < 20; i++) {
            HuSprTPLvlSet(grpId, i, tpLvl);
        }
        HuPrcVSleep();
    }
    stat4 = 2;
    for (time = 180; time != 0; time--) {
        HuPrcVSleep();
    }
    for (tpLvl = 240; tpLvl >= 0; tpLvl -= 16) {
        for (i = 1; i < 20; i++) {
            HuSprTPLvlSet(grpId, i, tpLvl);
        }
        HuPrcVSleep();
    }
    GMesSprClose(&gMes);
    stat0 = 2;
    HuPrcVSleep();
    stat3 = 1;
    do {
        HuPrcVSleep();
    } while (stat3 >= 0);
    stat0 = stat1 = 1;
    for (time = 120; time != 0; time--) {
        HuPrcVSleep();
    }
    stat2 = 1;
    do {
        HuPrcVSleep();
    } while (stat2 != 0);
    stat1 = 2;
    HuAudFXPlay(0x229);
    HuAudSeqFadeOut(240);
    for (time = 75; time != 0; time--) {
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreateOut(11, 4);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    staff_TextLineClose(0);
    staff_TextLineClose(1);
    stat0 = stat1 = -1;
    HuPrcSleep(2);
    stat5 = 1;
    omAddPrcObj(staff_FinaleProc, 0x4000, 0x1800, 0)->user_data = &stat5;
    while (stat5 != 0) {
        HuPrcVSleep();
    }
    HuAudSeqPlay(0x4E);
    WipeCreateIn(11, 4);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    for (time = 180; time != 0; time--) {
        HuPrcVSleep();
    }
    HuAudSeqFadeOut(0x4A);
    WipeCreateOut(11, 24);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    stat5 = -1;
    stat6 = 1;
    omAddPrcObj(staff_EndProc, 0x4000, 0x1000, 0)->user_data = &stat6;
    while (stat6 != 0) {
        HuPrcVSleep();
    }
    WipeCreateIn(11, 24);
    while (WipeStatGet()) {
        HuPrcVSleep();
    }
    stat6 = 1;
    HuAudFXPlay(0x22A);
    while (stat6 != 0) {
        HuPrcVSleep();
    }
    while (TRUE) {
        if ((HuPadBtnDown[0] & 0xD000) || (HuPadBtnDown[1] & 0xD000) || (HuPadBtnDown[2] & 0xD000) ||
            (HuPadBtnDown[3] & 0xD000)) {
            break;
        }
        HuPrcVSleep();
    }
    staff_exitCnt = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void staff_FireworkRandSet(UnkStaff_2 *arg0, s32 arg1) {
    u32 random;
    s32 x;
    s32 y;

    random = staff_Rand();
    x = (random & 0xFF) - 128;
    y = -500 - ((random >> 8) & 0xFF);
    staff_FireworkStartPosSet(arg0, x, y, 0.0f);
    x = staff_RandMod(100) + arg1 * 500 - 550;
    y = (staff_Rand() & 0x3F) + 218;
    staff_FireworkEndPosSet(arg0, x, y, staff_RandMod(500) - 800);
    staff_FireworkTimeSet(arg0, staff_RandMod(60) + 30);
}

void staff_FireworkShowProc(void) {
    s16 *stat = HuPrcCurrentGet()->user_data;
    UnkStaff_2 *objs[4];
    s16 timers[3];
    s16 index;
    s32 i;

    index = (staff_chrNo >= 0 && staff_chrNo < 6) ? staff_chrNo : 0;
    for (i = 0; i < 3; i++) {
        objs[i] = staff_FireworkCreate(staff_fireworkSprTbl[index]);
        staff_FireworkRandSet(objs[i], i);
        staff_FireworkFlagSet(objs[i], 1, 1);
        timers[i] = 0;
    }
    while (*stat >= 0) {
        switch (*stat) {
            case 0:
                break;
            case 1:
                for (i = 0; i < 3; i++) {
                    timers[i] = 1;
                }
                timers[0] = 1;
                break;
            case 2:
                for (i = 0; i < 3; i++) {
                    staff_FireworkFlagSet(objs[i], 4, 4);
                }
                *stat = -1;
                break;
        }
        if (*stat == 1) {
            for (i = 0; i < 3; i++) {
                if (timers[i] != 0) {
                    if (--timers[i] == 0) {
                        staff_FireworkFlagSet(objs[i], 1, 0);
                    }
                } else if (staff_FireworkFlagGet(objs[i]) & 1) {
                    timers[i] = (rand8() & 0xF) + 1;
                }
            }
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
    while (TRUE) {
        HuPrcVSleep();
    }
}
