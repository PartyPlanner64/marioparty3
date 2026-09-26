#include "common.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/FFB10.h"

void func_80105CA4_w02(void);
void func_80106094_w02(void *);
void func_801064DC_w02(void);
void func_80108570_w02(void);
void func_8010D854_w02(void);
void func_801199EC_w02(void);
extern s32 D_8011C6B0_w02[];
extern s32 D_8011C6CC_w02[];
extern s32 D_8011C868_w02[];
extern s32 D_8011C88C_w02[];
extern s8 D_8011D45C_w02[][5][7];
extern Object *D_8011EBD8_w02[];
extern Process *D_8011EBF8_w02[];
extern Process *D_8011EC18_w02;
extern Object *D_8011EC1C_w02;
extern Unk3 *D_8011EC20_w02;
extern Unk3 *D_8011EC24_w02;
extern Unk3 *D_8011EC28_w02;
extern Unk3 *D_8011EC2C_w02;
extern Unk3 *D_8011EC30_w02;
extern s32 D_8011EC70_w02;
extern Object *D_8011EC80_w02[4];
extern Object *D_8011ECD8_w02[4];
extern omObjData *D_8011ECE8_w02[4];
extern s32 D_8011EC90_w02;
extern s32 D_8011EC94_w02;
extern s16 D_8011C680_w02[]; // mb2ev_StarFlag
extern s16 D_8011C690_w02[];
extern s16 D_8011C6A0_w02[]; // mb2ev_StarGuideMasu
extern s16 D_8011C72C_w02[][2];
extern s16 D_8011C734_w02[][2];
extern s16 D_8011C8D4_w02[];
extern s16 D_8011C8D8_w02[];
extern Object *D_8011C8E0_w02;
extern s32 D_8011D594_w02;
extern s32 D_8011E914_w02;
extern DecisionTreeNonLeafNode *D_8011EA68_w02[];

s16 func_801059D0_w02(void) {
    return D_8011C6A0_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801059F8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105B00_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105B8C_w02);

s16 func_80105C30_w02(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == D_8011C690_w02[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = D_8011C680_w02[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80105CA4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106094_w02);

#define GET_STAR_MODEL() D_8011EBD8_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]
// MB3Ev_StarMapView
void func_80106120_w02(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *space;
    s32 face;
    s32 mesNum;
    GW_SYSTEM *system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, D_8011C6B0_w02[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(GET_STAR_MODEL());
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w02(guide);

    if ((system->current_star_spawn == 0) && (GWBoardFlagCheck(4) == 0)) {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E00;
        }
    } else {
        if (system->current_board_index == 2) {
            mesNum = 0x5E09;
        } else {
            mesNum = 0x5E01;
        }
    }
    func_8005B43C_main(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    if ((system->current_board_index != SPINY_DESERT) || (rand8() & 1)) {
        space = MBMasuGet(D_8011C6A0_w02[system->star_spawn_indices[system->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    face = MBRand(7.0f);
    MBGuideFaceSet(guide->obj, D_8011C6B0_w02[face]);
    MBMotionSet(guide->obj, -1, 2);

    if (system->current_board_index != 2) {
        proc = omAddPrcObj(func_80105CA4_w02, 0x4800, 0, 0);
        D_8011EC18_w02 = proc;
        proc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_8011EC18_w02 = NULL;
    }

    func_8005B43C_main(guide->amount, D_8011C6CC_w02[face], -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);

    HuAudSeqFadeOut(0x5A);
    HuPrcSleep(30);
    WipeCreateOut(2, 0x10);
    HuPrcSleep(0x11);
    D_800A12D4_main = 1;
    func_80100130_shared_board();
    func_80046558_main(D_8011EC1C_w02->omObj1->model[0]);
    MBModelKill(D_8011EC1C_w02);
    MBModelDispOn(GET_STAR_MODEL());
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801064DC_w02);

void func_80106A3C_w02(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w02, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106AB0_w02);

void func_80106B38_w02(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106B94_w02);

void func_80106C64_w02(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EC20_w02);
    MBHelpWinKill(D_8011EC24_w02);
    MBHelpWinKill(D_8011EC30_w02);
    MBHelpWinKill(D_8011EC28_w02);
    MBHelpWinKill(D_8011EC2C_w02);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106CC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80106F58_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107170_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801072A0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107438_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107704_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107724_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107744_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107780_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107830_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107B4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107BD0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107BFC_w02);

void func_80107D24_w02(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8011EBF8_w02[i] != NULL) {
            omDelPrcObj(D_8011EBF8_w02[i]);
            D_8011EBF8_w02[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107D88_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107E34_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107F54_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80107FB0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801080AC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108218_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108280_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801083EC_w02);

void func_8010844C_w02(void) {
    HuPrcSleep(D_8011C88C_w02[GwSystem.current_board_index]);
    // The sound ID lives in the upper halfword of each D_8011C868_w02 entry
    HuAudFXPlay((s16)D_8011C868_w02[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801084A8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108570_w02);

void func_80108620_w02(s32 arg) {
    Process *prc = omAddPrcObj(func_80108570_w02, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void func_8010865C_w02(void) {
    s32 i;

    D_8011EC70_w02 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011C8D4_w02[i])->coords,
                                   D_8011C72C_w02[i][0], D_8011C72C_w02[i][1]);
    }
}

void func_801086DC_w02(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011C8D8_w02[i])->coords,
                                   D_8011C734_w02[i][0], D_8011C734_w02[i][1]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108754_w02);

void func_801087F8_w02(void) {
    SpaceData *masu = MBMasuGet(0x7B);
    Object *obj = MBModelFileCreate(0x13016B, -1, 1.0f, 0, NULL);

    MBModelTempAllocFree(obj);
    D_8011C8E0_w02 = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &masu->coords);
}

void func_80108870_w02(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if ((GwSystem.boardData.halfWordBytes[0] >> i) & 1) {
            MBModelDispOn(D_8011EC80_w02[i]);
        } else {
            MBModelDispOff(D_8011EC80_w02[i]);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801088EC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801089C0_w02);

// Counts the set bits among the 4 low per-board flags in GwSystem.boardData
s32 func_80108A20_w02(void) {
    s32 flagsSet = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        flagsSet += (GwSystem.boardData.halfWordBytes[0] >> i) & 1;
    }
    return flagsSet >= 3;
}

void func_80108A58_w02(void) {
    MBMoveNextMasuSet(-1, 0, 0xF);
    MBMoveBackMasuSet(-1, 0, 0xF);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108A8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108AC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108B6C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108BA4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108C4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108C7C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108CC0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108CF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108D34_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108D64_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108DA8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108DD8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108E1C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80108E4C_w02);

void func_80108F8C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x12) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void func_80108FEC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x23) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void func_8010904C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x24) {
        MBMoveNextMasuSet(-1, 0, 5);
    }
}

void func_801090AC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(-1, 0, 0x14);
    }
}

void func_8010910C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010916C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x85) {
        MBMoveNextMasuSet(-1, 4, 5);
    }
}

void func_801091CC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x28) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void func_8010922C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xD) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010928C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2B) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_801092EC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x38) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void func_8010934C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x69) {
        MBMoveNextMasuSet(-1, 6, 0xB);
    }
}

void func_801093AC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5C) {
        MBMoveNextMasuSet(-1, 7, 0x12);
    }
}

void func_8010940C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x87) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void func_8010946C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x88) {
        MBMoveNextMasuSet(-1, 6, 5);
    }
}

void func_801094CC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x50) {
        MBMoveNextMasuSet(-1, 7, 0x16);
    }
}

void func_8010952C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x56) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_8010958C_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x2A) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

void func_801095EC_w02(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xC) {
        MBMoveNextMasuSet(-1, 5, 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010964C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010985C_w02);

void func_80109C80_w02(void) {
}

void func_80109C88_w02(void) {
}

void func_80109C90_w02(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80109C98_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80109F1C_w02);

void func_80109FD8_w02(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010A018_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010A3C4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010AF00_w02);

s32 func_8010AF88_w02(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011D45C_w02[D_8011EC90_w02][D_8011EC94_w02][i] == -1) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010AFF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010B1C8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C47C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C51C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010C5BC_w02);

void func_8010CA04_w02(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010CA28_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010D854_w02);

void func_8010D9A8_w02(s32 arg) {
    Process *prc = omAddPrcObj(func_8010D854_w02, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010D9E4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBB8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBD4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EBF0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010ED4C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010EE64_w02);

void func_8010F22C_w02(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011C690_w02[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F298_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F458_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F6BC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F78C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010F9BC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010FB8C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8010FCFC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110048_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011020C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801104A4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110730_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110970_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110B80_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80110E40_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801111E0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80111BDC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112124_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112340_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112734_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801127F0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112944_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112980_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112B10_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80112ECC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80113164_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80113270_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011344C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801140F8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801141B8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801146E8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80114FF4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011512C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011529C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80115464_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801156E8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80115FEC_w02);

void func_801161E4_w02(s32 arg0) {
    {
        omObjData *obj = D_8011ECE8_w02[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011ECE8_w02[arg0] = NULL;
        }
    }

    {
        Object *model = D_8011ECD8_w02[arg0];

        if (model != NULL) {
            MBModelKill(model);
            D_8011ECD8_w02[arg0] = NULL;
        }
    }
}

void func_8011625C_w02(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011ECE8_w02[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011ECE8_w02[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801162C0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011646C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011656C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116608_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116708_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116914_w02);

void func_80116A74_w02(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80116AC4_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011703C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011720C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80117344_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801177C8_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80117E70_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80118480_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119244_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119360_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193C0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193D0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801193DC_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119408_w02);

void func_80119438_w02(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    HmfModelData_UnkBC_Struct *model = HmfModelData[arg0].unkBC;
    model->unk1C.f = arg1;
    model->unk20.f = arg2;
    model->unk24.f = arg3;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011946C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119680_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_801199EC_w02);

Process *func_80119D84_w02(void) {
    return omAddPrcObj(func_801199EC_w02, 0x1000, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_80119DB0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B038_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B8A0_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B934_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011B988_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BA58_w02);

s32 func_8011BB30_w02(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BB84_w02);

INCLUDE_RODATA("asm/nonmatchings/overlays/w02/335610", D_8011EB68_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011BC6C_w02);

INCLUDE_ASM("asm/nonmatchings/overlays/w02/335610", func_8011C274_w02);

s32 func_8011C5D8_w02(void) {
    if (D_8011E914_w02 != 0) {
        D_8011E914_w02 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011EA68_w02[D_8011D594_w02]) + 1;
}
