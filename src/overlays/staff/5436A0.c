#include "staff.h"

s32 D_80110540_staff[8] = {
    0xB003E, 0xB003F, 0xB0040, 0xB0041, 0xB0042, 0xB0043, 0xB0044, 0xB0045
};
MsetupCameraPreset D_80110560_staff = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1390.0f, 32.0f };

const char D_80111208_staff[] = "MARIO PARTY 3 STAFF";

void func_80106E20_staff(void) {
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

    D_800CD280_main = 1;
    func_8010609C_staff(&D_80110560_staff);
    func_8010B514_staff(0, 6);
    func_8010B514_staff(1, 12);
    stat0 = 0;
    omAddPrcObj(func_80107EB8_staff, 0x4200, 0x800, 0)->user_data = &stat0;
    stat1 = 0;
    omAddPrcObj(func_801095E4_staff, 0x4000, 0, 0)->user_data = &stat1;
    stat2 = 0;
    omAddPrcObj(func_8010BF84_staff, 0x4000, 0, 0)->user_data = &stat2;
    stat3 = 0;
    omAddPrcObj(func_80109264_staff, 0x4000, 0, 0)->user_data = &stat3;
    stat4 = 0;
    omAddPrcObj(func_80107508_staff, 0x1000, 0, 0)->user_data = &stat4;
    strId = func_8003A308_main(&gMes, (char *)D_80111208_staff, 0, -1, -1);
    grpId = gMes.strGId[strId];
    HuSprPosSet(grpId, 0, 160, 120);
    for (i = 1; i < 20; i++) {
        HuSprTPLvlSet(grpId, i, 0);
        HuSprDispOff(grpId, i);
    }
    WipeCreateIn(D_80111530_staff, 16);
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
    func_8003B128_main(&gMes);
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
    func_8010B794_staff(0);
    func_8010B794_staff(1);
    stat0 = stat1 = -1;
    HuPrcSleep(2);
    stat5 = 1;
    omAddPrcObj(func_8010D1E8_staff, 0x4000, 0x1800, 0)->user_data = &stat5;
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
    omAddPrcObj(func_8010D998_staff, 0x4000, 0x1000, 0)->user_data = &stat6;
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
        if ((D_800D5558_main[0] & 0xD000) || (D_800D5558_main[1] & 0xD000) || (D_800D5558_main[2] & 0xD000) ||
            (D_800D5558_main[3] & 0xD000)) {
            break;
        }
        HuPrcVSleep();
    }
    D_80110530_staff = 1;
    while (TRUE) {
        HuPrcVSleep();
    }
}

void func_801073EC_staff(UnkStaff_2 *arg0, s32 arg1) {
    u32 random;
    s32 x;
    s32 y;

    random = func_8010601C_staff();
    x = (random & 0xFF) - 128;
    y = -500 - ((random >> 8) & 0xFF);
    func_8010DEF4_staff(arg0, x, y, 0.0f);
    x = func_80106044_staff(100) + arg1 * 500 - 550;
    y = (func_8010601C_staff() & 0x3F) + 218;
    func_8010DEE4_staff(arg0, x, y, func_80106044_staff(500) - 800);
    func_8010DF04_staff(arg0, func_80106044_staff(60) + 30);
}

void func_80107508_staff(void) {
    s16 *stat = HuPrcCurrentGet()->user_data;
    UnkStaff_2 *objs[4];
    s16 timers[3];
    s16 index;
    s32 i;

    index = (D_80111514_staff >= 0 && D_80111514_staff < 6) ? D_80111514_staff : 0;
    for (i = 0; i < 3; i++) {
        objs[i] = func_8010DE50_staff(D_80110540_staff[index]);
        func_801073EC_staff(objs[i], i);
        func_8010DF0C_staff(objs[i], 1, 1);
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
                    func_8010DF0C_staff(objs[i], 4, 4);
                }
                *stat = -1;
                break;
        }
        if (*stat == 1) {
            for (i = 0; i < 3; i++) {
                if (timers[i] != 0) {
                    if (--timers[i] == 0) {
                        func_8010DF0C_staff(objs[i], 1, 0);
                    }
                } else if (func_8010DF24_staff(objs[i]) & 1) {
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
