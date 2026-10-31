#include "SpinyDesert.h"
#include "common.h"
#include "../ovl_80_shared_board/113520.h"
#include "game/object.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/EDDB0.h"

void func_80105DB0_w03(void);
void func_801061A0_w03(UnkMBGuideData *);
void func_801066CC_w03(void);
void func_80108734_w03(void);
extern s16 D_8011C130_w03[];
extern s16 D_8011C140_w03[];
extern s16 D_8011C150_w03[];
extern s16 D_8011C1A8_w03[][2];
extern s16 D_8011C1B0_w03[][2];
extern s32 D_8011C2E4_w03[];
extern s32 D_8011C308_w03[];
extern s16 D_8011C350_w03[];
extern s16 D_8011C354_w03[];
extern s16 D_8011C358_w03[];
extern s8 D_8011CF98_w03[][5][7];
extern Object *D_8011EAC8_w03[];
extern Process *D_8011EAE8_w03[8];
extern Process *D_8011EB08_w03;
extern Object *D_8011EB0C_w03;
extern Unk3 *D_8011EB10_w03;
extern Unk3 *D_8011EB14_w03;
extern Unk3 *D_8011EB18_w03;
extern Unk3 *D_8011EB1C_w03;
extern Unk3 *D_8011EB20_w03;
extern s32 D_8011EB88_w03;
extern s32 D_8011EB94_w03;
extern s32 D_8011EB98_w03;
extern u8 *D_8011EB9C_w03;
extern Object *D_8011EBE0_w03[4];
extern omObjData *D_8011EBF0_w03[4];
extern s32 D_8011D0D0_w03;
extern s32 D_8011E7A8_w03;
extern DecisionTreeNonLeafNode *D_8011E8FC_w03[];

s16 func_801059D0_w03(void) {
    return D_8011C150_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801059F8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105B44_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105C50_w03);

s16 func_80105D20_w03(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == D_8011C140_w03[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = D_8011C130_w03[i];
                return 1;
            }
            if (i == GwSystem.boardData.halfWordBytes[0]) {
                return 2;
            }
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80105DB0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801061A0_w03);

// Star tour.
void func_8010622C_w03(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *first;
    SpaceData *second;
    SpaceData *temp;
    s32 mesNum;
    GW_SYSTEM *system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, 0xA007E);
    func_800FFF44_shared_board();
    MBModelDispOff(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOff(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_801061A0_w03(guide);

    first = MBMasuGet(D_8011C150_w03[system->star_spawn_indices[system->current_star_spawn]]);
    second = MBMasuGet(D_8011C150_w03[GwSystem.boardData.halfWordBytes[0]]);

    if (MBRandCheck100(50) != 0) {
        temp = first;
        first = second;
        second = temp;
    }

    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        mesNum = 0x5E09;
    } else {
        mesNum = 0x5E0A;
    }

    HuWinMesSet(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    temp = first;
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    MBMotionSet(guide->obj, -1, 2);
    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    winData[guide->amount].stat = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);

    while (D_8011EB08_w03 != NULL) {
        HuPrcVSleep();
    }
    temp = second;
    MBCameraPos3DSet(&temp->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    proc = omAddPrcObj(func_80105DB0_w03, 0x4800, 0, 0);
    D_8011EB08_w03 = proc;
    proc->user_data = temp;
    HuPrcSleep(30);
    winData[guide->amount].stat = 1;
    HuPrcVSleep();
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011EB0C_w03->omObj1->model[0]);
    MBModelKill(D_8011EB0C_w03);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]);
    MBModelDispOn(D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]]);
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801066CC_w03);

void func_80106C2C_w03(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801066CC_w03, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106CA0_w03);

void func_80106D28_w03(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106D84_w03);

void func_80106E54_w03(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EB10_w03);
    MBHelpWinKill(D_8011EB14_w03);
    MBHelpWinKill(D_8011EB20_w03);
    MBHelpWinKill(D_8011EB18_w03);
    MBHelpWinKill(D_8011EB1C_w03);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80106EB4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107148_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107360_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107490_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107628_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801078F4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107914_w03);

// entrypoint 0
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107934_w03);

// entrypoint 1
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107970_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107A04_w03);

// entrypoint 2
void func_80107CA4_w03() {
    HuAudSeqPlay(0x1A);
    D_800CE198_main = 0x1A;
    func_800F8D6C_shared_board(0x1A);
    Hu3DCamInit(2);
    func_80107A04_w03();
    MBMasuEventTblAdd(D_8011D1C4_w03);
    MBMasuEventTblAdd(D_8011D478_w03);
    MBHatenaFuncSet(func_8011A704_w03);
    MBMasuEventTblAdd(D_8011D23C_w03);
    MBMasuEventTblAdd(D_8011D3D0_w03);
    MBStart(0);
}

// entrypoint 3
INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107D28_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107D54_w03);

void func_80107ECC_w03(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8011EAE8_w03[i] != NULL) {
            omDelPrcObj(D_8011EAE8_w03[i]);
            D_8011EAE8_w03[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107F30_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80107FF8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108118_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108174_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108270_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801083DC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108444_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801085B0_w03);

void func_80108610_w03(void) {
    HuPrcSleep(D_8011C308_w03[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011C2E4_w03[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010866C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108734_w03);

void func_801087E4_w03(s32 arg) {
    Process *prc = omAddPrcObj(func_80108734_w03, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void func_80108820_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011C350_w03[i])->coords, D_8011C1A8_w03[i][0],
                                   D_8011C1A8_w03[i][1]);
    }
}

void func_801088A0_w03(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011C354_w03[i])->coords,
                                   D_8011C1B0_w03[i][0], D_8011C1B0_w03[i][1]);
    }
}

s32 func_80108918_w03(s16 *arg0) {
    s16 *ptr = arg0;
    s32 i = 0;
    s32 ret = 0;

    for (; i < 8; i++) {
        if (*ptr == GwSystem.boardData.halfWordBytes[0]) {
            ret = 1;
            break;
        }
        if (GWBoardFlagCheck(D_8011C358_w03[*ptr]) == 0) {
            break;
        }
        ptr++;
    }
    return ret;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E910_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801089AC_w03);

void func_80108AB8_w03(void) {
    MBMoveNextMasuSet(-1, 1, 7);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108ADC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108B98_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108C48_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108C80_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108CB8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108CF0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108DA0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108DD8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108E30_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108E88_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108EE0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80108F38_w03);

void func_80109268_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3B) {
        MBMoveNextMasuSet(-1, 0xB, 0xB);
    }
}

void func_801092C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x43) {
        MBMoveNextMasuSet(-1, 1, 0xD);
    }
}

void func_80109328_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 8) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109388_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 2, 2);
    }
}

void func_801093E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xD) {
        MBMoveNextMasuSet(-1, 2, 9);
    }
}

void func_80109448_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xF) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_801094A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x54) {
        MBMoveNextMasuSet(-1, 4, 2);
    }
}

void func_80109508_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5B) {
        MBMoveNextMasuSet(-1, 5, 0xA);
    }
}

void func_80109568_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 0x19);
    }
}

void func_801095C8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2F) {
        MBMoveNextMasuSet(-1, 5, 0x14);
    }
}

void func_80109628_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x8B) {
        MBMoveNextMasuSet(-1, 5, 0x19);
    }
}

void func_80109688_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5E) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_801096E8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x51) {
        MBMoveNextMasuSet(-1, 5, 0x12);
    }
}

void func_80109748_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(-1, 1, 0xD);
    }
}

void func_801097A8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x44) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109808_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x33) {
        MBMoveNextMasuSet(-1, 8, 1);
    }
}

void func_80109868_w03(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2) {
        MBMoveNextMasuSet(-1, 0xB, 0xB);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801098C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109AD8_w03);

void func_80109E90_w03(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109E98_w03);

void func_80109F3C_w03(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80109F44_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A1C8_w03);

void func_8010A284_w03(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A2C4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010A930_w03);

s32 func_8010B46C_w03(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EB9C_w03[i] != 0 && D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 func_8010B4F4_w03(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011CF98_w03[D_8011EB94_w03][D_8011EB98_w03][i] == -1) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B55C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B734_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010C9EC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CA8C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CB2C_w03);

void func_8010CF74_w03(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CF98_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E98C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DDC4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF18_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF54_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F128_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F144_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F160_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F2BC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F3D4_w03);

void func_8010F79C_w03(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011C140_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F808_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F9C8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FC2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FCFC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FF2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801100FC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011026C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801105B8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011077C_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E998_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E9F8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110A14_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110CA0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110EE0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801110F0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801113B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80111750_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011214C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112694_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801128B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112CA4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112D60_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112EB4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112EF0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80113080_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011343C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801136D4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801137E0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801139BC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114668_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114728_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114C58_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80115564_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011569C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011580C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801159D4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80115C58_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011655C_w03);

void func_80116754_w03(s32 arg0) {
    {
        omObjData *obj = D_8011EBF0_w03[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011EBF0_w03[arg0] = NULL;
        }
    }

    {
        Object *model = D_8011EBE0_w03[arg0];

        if (model != NULL) {
            MBModelKill(model);
            D_8011EBE0_w03[arg0] = NULL;
        }
    }
}

void func_801167CC_w03(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011EBF0_w03[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011EBF0_w03[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116830_w03);

void func_801169DC_w03(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (D_8011EBE0_w03[playerNo] == NULL) {
        switch (type) {
            case 0:
                modelId = 0x3F;
                break;
            case 1:
                modelId = 0x40;
                break;
            case 2:
                modelId = 0x41;
                break;
            default:
                modelId = 0x42;
                break;
        }

        obj = MBModelCreate(modelId, NULL);
        MBModelTempAllocFree(obj);
        D_8011EBE0_w03[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011EBE0_w03[playerNo]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116ADC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116B78_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116C78_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116E84_w03);

void func_80116FE4_w03(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80117034_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801175AC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011777C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801178B4_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80117D38_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801183E0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80118E3C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80118F64_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011908C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80119120_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80119290_w03);

void func_8011A2BC_w03(void) {
    s32 i = 0;
    GW_PLAYER *player = MBPlayerGet((s32)HuPrcCurrentGet()->user_data);
    f32 velocityStep = 5.0f / 12.0f;

    do {
        player->player_obj->velocity.x -= velocityStep;
        HuPrcVSleep();
        i++;
    } while (i < 0x3C);

    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A338_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A550_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011A704_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B1FC_w03);

// entrypoint 4
void func_8011B41C_w03() {
    Hu3DCamInit(2);
    CameraScissorSet(1, &D_8011D598_w03);
    func_80107A04_w03();
    MBStart(2);
    omAddPrcObj(func_8010622C_w03, 0x1005, 0x1000, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B470_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B51C_w03);

s32 func_8011B5E0_w03(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B634_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011B71C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011BD24_w03);

s32 func_8011C088_w03(void) {
    if (D_8011E7A8_w03 != 0) {
        D_8011E7A8_w03 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011E8FC_w03[D_8011D0D0_w03]) + 1;
}
