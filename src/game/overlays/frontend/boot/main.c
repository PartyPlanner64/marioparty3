#include "common.h"
#include "macros.h"

void boot_ExitCheckObjMain(omObjData *);
void boot_LogoProc(void);
void boot_ExitObjMain(omObjData *);
void boot_ObjectInit(void);
void boot_SkipCheckObjMain(omObjData *);

s32 boot_skipF = 0;
s32 boot_exitF = 0;

Process *boot_logoProc BSS;

void boot_ObjectInit(void) {
    Hu3DCamInit(1);
    omInitObjMan(0x10, 4);
    omSysPauseDisableF = 1;

    if (boot_skipF == 0) {
        GWContErrorSet();
        boot_logoProc = omAddPrcObj(boot_LogoProc, 0xA, 0, 0);
        omAddObj(0x3E8, 0, 0, -1, boot_ExitCheckObjMain);
    } else {
        boot_logoProc = omAddPrcObj(boot_LogoProc, 0xA, 0, 0);
        omAddObj(0x3E8, 0, 0, -1, boot_ExitCheckObjMain);
        omAddObj(0xA, 0, 0, -1, boot_SkipCheckObjMain);
    }
}

void boot_ObjectSetup(void) {
    boot_skipF = 0;
    boot_ObjectInit();
}

void boot_SkipObjectSetup(void) {
    boot_skipF = 1;
    boot_ObjectInit();
}

void boot_ExitCheckObjMain(omObjData *arg0) {
    if (((omSysExitReq != 0) || (boot_exitF != 0)) && (WipeStatGet() == 0)) {
        WipeColorSet(0, 0, 0U);
        WipeCreateOut(WIPE_FADE, 9);
        arg0->func = &boot_ExitObjMain;

        if ((omSysExitReq != 0) && (WipeStatGet() == 0)) {
            WipeColorSet(0, 0, 0U);
            WipeCreateOut(WIPE_FADE, 9);
            arg0->func = &boot_ExitObjMain;
        }
    }
}

void boot_ExitObjMain(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        if (boot_skipF != 0) {
            omOvlGotoEx(opening, 2, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
            return;
        }
        omOvlCallEx(opening, 2, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
        omOvlHisChg(1, opening, 2, OM_OVL_STAT_BOARD | OM_OVL_STAT_SYSKEY | OM_OVL_STAT_GFXBUF3);
    }
}

void boot_SkipCheckObjMain(omObjData *arg0) {
    s32 temp_v0;

    if (WipeStatGet() == 0) {
        temp_v0 = GWContErrorGet();
        if ((temp_v0 == 1) && (CheckControllerRead(0) != 0) && (HuPadBtnDown[0] & START_BUTTON)) {
            boot_exitF = temp_v0;
        }
    }
}

void boot_LogoProc(void) {
    u16 temp_v0;
    u16 temp_v0_3;
    u16 temp_s0_3;
    u16 temp_v0_2;
    u16 temp_v0_4;

    temp_v0 = HuSprAnimDataRead(0x00110000);
    temp_v0_2 = espEntry(temp_v0, 0, 1);
    espPosSet(temp_v0_2, 0xA0, 0x78);
    espDispOn(temp_v0_2);
    espPriSet(temp_v0_2, 0xFFFF);
    WipeCreateIn(WIPE_FADE, 30);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    HuPrcSleep(37);
    WipeCreateOut(WIPE_FADE, 9);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    espKill(temp_v0_2);
    HuSprAnimKill(temp_v0);
    HuPrcSleep(9);
    temp_v0_3 = HuSprAnimDataRead(0x00110001);
    temp_v0_4 = espEntry(temp_v0_3, 0, 1);
    espPosSet(temp_v0_4, 0xA0, 0x78);
    espDispOn(temp_v0_4);
    espPriSet(temp_v0_4, 0xFFFF);
    WipeCreateIn(WIPE_FADE, 9);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    HuPrcSleep(37);
    WipeCreateOut(WIPE_FADE, 9);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    espKill(temp_v0_4);
    HuSprAnimKill(temp_v0_3);
    HuPrcSleep(9);
    temp_s0_3 = espEntry(HuSprAnimDataRead(0x110002), 0, 1);
    espPosSet(temp_s0_3, 0xA0, 0x78);
    espDispOn(temp_s0_3);
    espPriSet(temp_s0_3, 0xFFFF);
    WipeCreateIn(WIPE_FADE, 9);

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    HuPrcSleep(37);
    omSysExitReq = 1;

    while (1) {
        HuPrcVSleep();
    }
}
