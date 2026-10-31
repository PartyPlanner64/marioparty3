#include "common.h"
#include "gcc/string.h"

typedef struct MessageCheckEntry {
    u8 *name;
    u32 firstMessage;
    u32 lastMessage;
} MessageCheckEntry;

typedef struct MessageCheckState {
    u16 finished;
    s16 unk02[5];
    f32 unk0C;
    s16 unk10[3];
} MessageCheckState;

MessageCheckState D_80106500_meschk = { 0, { 50, 60, 0, 0, 0 }, 1.0f, { -1, 1200, 0 } };
MessageCheckEntry D_80106518_meschk[] = {
    { (u8 *)"B1_snowman", 0x0200, 0x0204 },
    { (u8 *)"B_kekka", 0x1400, 0x1418 },
    { (u8 *)"B_P_starlift", 0x1500, 0x1532 },
    { (u8 *)"B_R_starlift", 0x1700, 0x1705 },
    { (u8 *)"B_Rule", 0x1600, 0x1633 },
    { (u8 *)"B_S_starlift", 0x1A00, 0x1A16 },
    { (u8 *)"B_start", 0x1800, 0x1817 },
    { (u8 *)"B_syousai", 0x1900, 0x190C },
    { (u8 *)"B1_lake", 0x0100, 0x0101 },
    { (u8 *)"B1_turuturu", 0x0300, 0x0000 },
    { (u8 *)"B2_ankou", 0x0400, 0x0000 },
    { (u8 *)"B2_ika", 0x0500, 0x0000 },
    { (u8 *)"B2_submarine", 0x0600, 0x0602 },
    { (u8 *)"B3_saboten", 0x0700, 0x0000 },
    { (u8 *)"B3_star", 0x0800, 0x0000 },
    { (u8 *)"B4_kinokio", 0x0900, 0x0909 },
    { (u8 *)"B4_mori", 0x0A00, 0x0000 },
    { (u8 *)"B4_tyorobu", 0x0B00, 0x0B05 },
    { (u8 *)"B5_battan", 0x0C00, 0x0C08 },
    { (u8 *)"B5_torokko", 0x0D00, 0x0D03 },
    { (u8 *)"B6_ana", 0x0E00, 0x0E01 },
    { (u8 *)"B6_bomb", 0x0F00, 0x0F04 },
    { (u8 *)"B6_guruguru", 0x1000, 0x0000 },
    { (u8 *)"B6_hasi", 0x1100, 0x0000 },
    { (u8 *)"bankmasu", 0x1200, 0x1204 },
    { (u8 *)"battlemasu", 0x1300, 0x1305 },
    { (u8 *)"chancetime", 0x1B00, 0x1B1D },
    { (u8 *)"charname", 0x1C00, 0x1C5F },
    { (u8 *)"D_battle", 0x1E00, 0x1E01 },
    { (u8 *)"D_event", 0x1F00, 0x1F30 },
    { (u8 *)"D_kekka", 0x2000, 0x2006 },
    { (u8 *)"D_map1", 0x2100, 0x2103 },
    { (u8 *)"D_map5", 0x2200, 0x0000 },
    { (u8 *)"D_map6", 0x2300, 0x0000 },
    { (u8 *)"D_P_starlift", 0x2400, 0x2433 },
    { (u8 *)"D_R_starlift", 0x2600, 0x2605 },
    { (u8 *)"D_Rule", 0x2500, 0x253A },
    { (u8 *)"D_S_starlift", 0x2900, 0x2920 },
    { (u8 *)"D_start", 0x2700, 0x2711 },
    { (u8 *)"D_syousai", 0x2800, 0x2809 },
    { (u8 *)"Dhelp", 0x1D00, 0x1D15 },
    { (u8 *)"fileselect", 0x2A00, 0x2A19 },
    { (u8 *)"gamble1", 0x2B00, 0x2B0F },
    { (u8 *)"gamble2", 0x2C00, 0x2C07 },
    { (u8 *)"gamble3", 0x2D00, 0x2D0A },
    { (u8 *)"gamble4", 0x2E00, 0x2E10 },
    { (u8 *)"gamblemasu", 0x2F00, 0x2F04 },
    { (u8 *)"help", 0x3000, 0x301B },
    { (u8 *)"hiroba", 0x3100, 0x313E },
    { (u8 *)"inst_1vs3", 0x3200, 0x322A },
    { (u8 *)"inst_2vs2", 0x3300, 0x331F },
    { (u8 *)"inst_4player", 0x3400, 0x343C },
    { (u8 *)"inst_battle", 0x3500, 0x3517 },
    { (u8 *)"inst_duel", 0x3600, 0x3631 },
    { (u8 *)"inst_item", 0x3700, 0x3711 },
    { (u8 *)"inst_omake", 0x3800, 0x3814 },
    { (u8 *)"inst_practice", 0x3900, 0x3919 },
    { (u8 *)"item", 0x3A00, 0x3A30 },
    { (u8 *)"itemkinopio", 0x3B00, 0x3B09 },
    { (u8 *)"itemmasu", 0x3C00, 0x3C32 },
    { (u8 *)"itemminikoopa", 0x3D00, 0x3D09 },
    { (u8 *)"itemsetumei", 0x3E00, 0x3E13 },
    { (u8 *)"kakusiblock", 0x3F00, 0x3F0A },
    { (u8 *)"kettou", 0x4000, 0x4007 },
    { (u8 *)"keyman", 0x4100, 0x4106 },
    { (u8 *)"koopamasu", 0x4200, 0x4222 },
    { (u8 *)"last5", 0x4300, 0x4312 },
    { (u8 *)"M_P_starlift", 0x4900, 0x491B },
    { (u8 *)"M_S_starlift", 0x4A00, 0x4A15 },
    { (u8 *)"minigame_book", 0x4400, 0x4443 },
    { (u8 *)"minigame_record", 0x4500, 0x450A },
    { (u8 *)"minigame_settei", 0x4600, 0x460A },
    { (u8 *)"minigame_title", 0x4700, 0x4748 },
    { (u8 *)"Mstar", 0x4800, 0x4805 },
    { (u8 *)"name", 0x4B00, 0x4B6B },
    { (u8 *)"narebox", 0x4C00, 0x4C3C },
    { (u8 *)"OPdemo", 0x4D00, 0x4D26 },
    { (u8 *)"option", 0x4E00, 0x4E13 },
    { (u8 *)"otachara", 0x4F00, 0x4F0D },
    { (u8 *)"party_record", 0x5000, 0x5011 },
    { (u8 *)"pause", 0x5100, 0x512C },
    { (u8 *)"playername", 0x5200, 0x5207 },
    { (u8 *)"quizparty_a", 0x5300, 0x533C },
    { (u8 *)"quizparty_b", 0x5400, 0x541D },
    { (u8 *)"quizparty_c", 0x5500, 0x558F },
    { (u8 *)"Room_battle", 0x5600, 0x5619 },
    { (u8 *)"Room_freeplay", 0x5700, 0x5729 },
    { (u8 *)"Room_gamble", 0x5800, 0x5814 },
    { (u8 *)"save", 0x5900, 0x5901 },
    { (u8 *)"Sdemo", 0x5A00, 0x5A82 },
    { (u8 *)"Sdemo_L", 0x5B00, 0x5B4D },
    { (u8 *)"select", 0x5C00, 0x5C03 },
    { (u8 *)"soundbox", 0x5D00, 0x5D4B },
    { (u8 *)"stariti", 0x5E00, 0x5E0A },
    { (u8 *)"starlevel", 0x5F00, 0x5F02 },
    { (u8 *)"story_record", 0x6100, 0x612D },
    { (u8 *)"storymode", 0x6000, 0x6006 },
    { (u8 *)"teresa", 0x6200, 0x6215 },
    { (u8 *)"wakarukana", 0x6300, 0x6307 },
    { (u8 *)"yakusyoku", 0x6400, 0x642A },
    { (u8 *)"", 0xFFFF, 0xFFFF },
};

extern u16 omdispinfo;
extern s16 D_800A1786_main;
extern u8 D_800CD280_main;
extern u16 D_800D530C_main;

extern void HuWinPushKeySet(s32, s16);
extern s32 func_80016784_main(s32, s32);
extern void func_80016FB4_main(s32, s32, s16);
extern void func_80017320_main(s32);
extern void func_800142A0_main(s32);
extern void func_8004DEC8_main(s16);
extern void func_80105B50_meschk(void);
extern void func_80105B8C_meschk(void);
extern void func_80106334_meschk(omObjData *data);
extern void func_80106390_meschk(omObjData *data);
extern void func_801063BC_meschk(void);

void func_801059A0_meschk() {
    omObjData *temp_v0;

    Hu3DCamInit(1);
    Hu3DAnimInit(1);
    func_800142A0_main(0x19);
    omInitObjMan(0x33, 10);
    HuWinInit();
    temp_v0 = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    Center.y = 100.0f;
    CZoom = 600.0f;
    CRot.x = -30.0f;
    omSetStatBit(temp_v0, 0xA0);
    if (omdispinfo != 0) {
        omdispinfo = 0;
        func_8004DEC8_main(D_800A1786_main);
        D_800A1786_main = -1;
    }
    omAddObj(0x2710, 0, 0, -1, func_80106334_meschk);
    HmfLightMaxSet(3);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0x40, 0x40, 0x60);
    HmfLightDirSet(1, -100.0f, 100.0f, 100.0f);
    HmfLightColorSet(2, 0, 0, 0);
    HmfLightColorSet(3, 0, 0, 0);
    omAddPrcObj(func_80105B50_meschk, 0x3F00, 0x800, 0);
    omAddPrcObj(func_801063BC_meschk, 0x3F00, 0x800, 0);
    WipeCreateIn(0, 0);
    D_800CD280_main = 1;
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
}

void func_80105B50_meschk() {
    func_80105B8C_meschk();
    D_80106500_meschk.finished = 1;
    HuWinAllKill();
    while (1) {
        HuPrcVSleep();
    }
}

void func_80105B8C_meschk() {
    s16 size[2];
    s16 window;
    s16 nameWindow;
    s16 count;
    s16 done;
    s16 entry;
    s16 i;
    s16 message;
    MessageCheckEntry *check;
    u8 *text;
    u8 *cursor;
    s16 hasChoice;
    s32 portrait;

    for (count = 0; D_80106518_meschk[count].firstMessage != 0xFFFF; count++) {}
    nameWindow = HuWinExCreate(-1, 60, 20, 200, 20, 0);
    HuWinExAnimIn(nameWindow);
    entry = 0;
    done = 0;
    do {
        check = &D_80106518_meschk[entry];
        for (i = 0; i < strlen((char *)check->name); i++) {
            if (check->name[i] == '.') {
                check->name[i] = 0x85;
            }
            if (check->name[i] == '!') {
                check->name[i] = 0xC2;
            }
            if ((check->name[i] == '_') | (check->name[i] == '-')) {
                check->name[i] = 0x3D;
            }
        }
        HuWinHomeClear(nameWindow);
        HuWinMesSet(nameWindow, (s32)check->name, -1, -1);
        if (check->lastMessage == 0) {
            check->lastMessage = check->firstMessage;
        }
        HuWinMesMaxSizeBetGet(size, check->firstMessage, check->lastMessage);
        text = func_800364DC_main((void *)check->firstMessage);
        for (i = 0, cursor = text; i < 5; i++, cursor++) {
            if (((cursor[0] == 0x10) | (cursor[0] == 0x20) || cursor[0] == 0x1A) &&
                ((cursor[1] == 0x10) | (cursor[1] == 0x20) || cursor[1] == 0x1A) &&
                ((cursor[2] == 0x10) | (cursor[2] == 0x20) || cursor[2] == 0x1A)) {
                break;
            }
        }
        func_800365E8_main(text);
        if (i == 5) {
            window = HuWinExCreate(0, 50, 44, size[0], size[1], 0);
            portrait = 0;
        } else {
            window = HuWinExCreate(7, 50, 44, size[0], size[1], 0);
            portrait = 1;
        }
        HuWinPushKeySet(window, 0x3F);
        HuWinBGColSet(window, 0xC0, 0x20, 0xC0);
        HuWinExAnimIn(window);
        for (message = (s16)check->firstMessage; (u32)message <= check->lastMessage; message++) {
            HuWinHomeClear(window);
            text = func_800364DC_main((void *)(s32)message);
            cursor = text;
            hasChoice = 0;
            for (; *cursor != 0; cursor++) {
                if (*cursor == 0xFF) {
                    hasChoice = 1;
                    break;
                }
                cursor += (*cursor == 0x18);
            }
            cursor = text;
            for (i = 0; i < 5; i++, cursor++) {
                if (((cursor[0] == 0x10) | (cursor[0] == 0x20) || cursor[0] == 0x1A) &&
                    ((cursor[1] == 0x10) | (cursor[1] == 0x20) || cursor[1] == 0x1A) &&
                    ((cursor[2] == 0x10) | (cursor[2] == 0x20) || cursor[2] == 0x1A)) {
                    break;
                }
            }
            if ((portrait == 1) & (i == 5)) {
                HuWinExAnimPopIn(window, 0);
                portrait = 0;
            } else if ((i != 5) & (portrait != 1)) {
                HuWinExAnimPopIn(window, 7);
                portrait = 1;
            }
            func_800365E8_main(text);
            HuWinMesSet(window, message, -1, -1);
            while (HuWinStatGet(window) != 0) {
                HuPrcVSleep();
            }
            if (winData[window].num_choices != 0) {
                HuWinChoiceGet(window, 0, 0);
            } else if (hasChoice == 0) {
                while (!(D_800D5558_main[0] & 0xC03F)) {
                    HuPrcVSleep();
                }
            }
            if ((winData[window].input & 0x4000) || (D_800D5558_main[0] & 0x4000)) {
                if ((u32)message > check->firstMessage) {
                    message -= 2;
                } else {
                    message--;
                }
            }
            if ((winData[window].input & 8) || (D_800D5558_main[0] & 8)) {
                if (entry != 0) {
                    entry -= 2;
                } else {
                    entry--;
                }
                break;
            }
            if ((winData[window].input & 4) || (D_800D5558_main[0] & 4)) {
                break;
            }
            if ((winData[window].input & 2) || (D_800D5558_main[0] & 2)) {
                if (entry - 5 >= 0) {
                    entry -= 6;
                } else {
                    entry = -1;
                }
                break;
            }
            if ((winData[window].input & 1) || (D_800D5558_main[0] & 1)) {
                if (entry + 5 < count) {
                    entry += 4;
                } else {
                    entry = count - 1;
                }
                break;
            }
            if ((D_800CDA7C_main[0] & 0x30) == 0x30) {
                done = 1;
                break;
            }
        }
        HuWinKill(window);
        winData[window].input = 0;
        entry++;
        if (entry >= count) {
            entry--;
        }
    } while (done == 0);
}

void func_80106334_meschk(omObjData *arg0) {
    if ((D_80106500_meschk.finished != 0) || (D_800D530C_main != 0)) {
        WipeCreateOut(0, 8);
        arg0->func = &func_80106390_meschk;
        HuAudSeqFadeOut(0x3C);
    }
}

void func_80106390_meschk(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_801063BC_meschk() {
    s16 model;
    s16 motion;
    s32 animation;
    s16 frame;

    model = func_8000B108_main(0x700A0, 0x2A9);
    motion = func_8000B108_main(0x70001, 8);
    func_8001C5B4_main(model, motion);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 100.0f);
    animation = func_80016784_main(model, 2);
    frame = 0;
    while (1) {
        HuPrcVSleep();
        if (D_80106500_meschk.finished != 0) {
            break;
        }
        func_80016FB4_main(model, animation, frame);
        if (frame >= D_800CCF58_main[HmfModelData[motion].motId].unk02) {
            frame = 0;
        }
        frame += 2;
    }
    func_80017320_main(animation);
    while (1) {
        HuPrcVSleep();
    }
}
