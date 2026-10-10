#include "common.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/10C230.h"

void func_801064DC_w04(void);
void func_80108558_w04(void);
void func_80117EA8_w04(void);
void func_801183D4_w04(void);
void func_801191B8_w04(void);
void func_8011A4E0_w04(s32);
extern s16 D_8011B760_w04[];
extern s16 D_8011B770_w04[];
extern s16 D_8011B780_w04[];
extern s16 D_8011B80C_w04[][2];
extern s16 D_8011B814_w04[][2];
extern s16 D_8011B9B4_w04[];
extern s16 D_8011B9B8_w04[];
extern s16 D_8011B9C4_w04[];
extern s32 D_8011B948_w04[];
extern s32 D_8011B96C_w04[];
extern s8 D_8011C550_w04[][5][7];
extern s32 D_8011C688_w04;
extern s32 D_8011DC68_w04;
extern Process *D_8011E018_w04[8];
extern Unk3 *D_8011E040_w04;
extern Unk3 *D_8011E044_w04;
extern Unk3 *D_8011E048_w04;
extern Unk3 *D_8011E04C_w04;
extern Unk3 *D_8011E050_w04;
extern s32 D_8011E090_w04;
extern Object *D_8011E09C_w04[3];
extern s32 D_8011E0A8_w04;
extern s32 D_8011E0AC_w04;
extern u8 *D_8011E0B0_w04;
extern Object *D_8011E0F0_w04[4];
extern omObjData *D_8011E100_w04[4];
extern DecisionTreeNonLeafNode *D_8011DDBC_w04[];

s16 func_801059D0_w04(void) {
    return D_8011B780_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801059F8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80105B00_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80105B8C_w04);

s16 func_80105C30_w04(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == D_8011B770_w04[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = D_8011B760_w04[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80105CA4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106094_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106120_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801064DC_w04);

void func_80106A3C_w04(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w04, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106AB0_w04);

void func_80106B38_w04(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106B94_w04);

void func_80106C64_w04(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011E040_w04);
    MBHelpWinKill(D_8011E044_w04);
    MBHelpWinKill(D_8011E050_w04);
    MBHelpWinKill(D_8011E048_w04);
    MBHelpWinKill(D_8011E04C_w04);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106CC4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106F58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107170_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801072A0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107438_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107704_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107724_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107744_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107780_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107828_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107B34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107BB8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107BE4_w04);

void func_80107D0C_w04(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8011E018_w04[i] != NULL) {
            omDelPrcObj(D_8011E018_w04[i]);
            D_8011E018_w04[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107D70_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107E1C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107F3C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107F98_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108094_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108200_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108268_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801083D4_w04);

void func_80108434_w04(void) {
    HuPrcSleep(D_8011B96C_w04[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011B948_w04[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108490_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108558_w04);

void func_80108608_w04(s32 arg) {
    Process *prc = omAddPrcObj(func_80108558_w04, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void func_80108644_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011B9B4_w04[i])->coords,
                                   D_8011B80C_w04[i][0], D_8011B80C_w04[i][1]);
    }
}

void func_801086C4_w04(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011B9B8_w04[i])->coords,
                                   D_8011B814_w04[i][0], D_8011B814_w04[i][1]);
    }
}

void func_8010873C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (GwSystem.boardData.halfWordBytes[D_8011B9C4_w04[i]] == 0) {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = -1.0f;
        } else {
            D_8011E09C_w04[i]->rot.x = 0.0f;
            D_8011E09C_w04[i]->rot.z = 1.0f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801087CC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010886C_w04);

void func_801088C8_w04(void) {
    MBMoveNextMasuSet(-1, 1, 0x15);
    MBMoveBackMasuSet(-1, 1, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801088FC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108934_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801089B0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108A58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108AD4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108B4C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108C00_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108CA8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108D00_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108D58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108DB0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108E08_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108E60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108EB8_w04);

void func_80108F10_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x28) {
        MBMoveNextMasuSet(-1, 0xD, 0xB);
    }
}

void func_80108F70_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x5B) {
        MBMoveNextMasuSet(-1, 1, 0x19);
    }
}

void func_80108FD0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x41) {
        MBMoveNextMasuSet(-1, 1, 0x19);
    }
}

void func_80109030_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x57) {
        MBMoveNextMasuSet(-1, 1, 0x12);
    }
}

void func_80109090_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x51) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void func_801090F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x70) {
        MBMoveNextMasuSet(-1, 4, 4);
    }
}

void func_80109150_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xC) {
        MBMoveNextMasuSet(-1, 4, 4);
    }
}

void func_801091B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 6, 2);
    }
}

void func_80109210_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 9) {
        MBMoveNextMasuSet(-1, 1, 0xE);
    }
}

void func_80109270_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0xE) {
        MBMoveNextMasuSet(-1, 6, 2);
    }
}

void func_801092D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x10) {
        MBMoveNextMasuSet(-1, 0xC, 7);
    }
}

void func_80109330_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x4D) {
        MBMoveNextMasuSet(-1, 2, 7);
    }
}

void func_80109390_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x42) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_801093F0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x58) {
        MBMoveNextMasuSet(-1, 2, 4);
    }
}

void func_80109450_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3D) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_801094B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x19) {
        MBMoveNextMasuSet(-1, 0xB, 4);
    }
}

void func_80109510_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x37) {
        MBMoveNextMasuSet(-1, 1, 5);
    }
}

void func_80109570_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x1C) {
        MBMoveNextMasuSet(-1, 0xB, 4);
    }
}

void func_801095D0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x3A) {
        MBMoveNextMasuSet(-1, 0xD, 0xB);
    }
}

void func_80109630_w04(void) {
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x66) {
        MBMoveBackMasuSet(-1, 1, 0x14);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109690_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801098A0_w04);

void func_80109CBC_w04(void) {
}

void func_80109CC4_w04(void) {
}

void func_80109CCC_w04(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109CD4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80109F58_w04);

void func_8010A014_w04(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A054_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A400_w04);

s32 func_8010AF34_w04(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011E0B0_w04[i] != 0 && D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 func_8010AFBC_w04(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011C550_w04[D_8011E0A8_w04][D_8011E0AC_w04][i] == -1) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010B024_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010B1FC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C4B4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C554_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010C5F4_w04);

void func_8010CA3C_w04(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010CA60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010D88C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010D9E0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010DA1C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EBF0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EC0C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EC28_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010ED84_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010EE9C_w04);

void func_8010F264_w04(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011B770_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F2D0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F490_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F6F4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F7C4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010F9F4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010FBC4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010FD34_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110080_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110244_w04);

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE40_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801104DC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110768_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801109A8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110BB8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110E78_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80111218_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80111C14_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011215C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112378_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011276C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112828_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011297C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801129B8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112B48_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112F04_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011319C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801132A8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80113484_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80114130_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801141F0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80114720_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011502C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80115164_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801152D4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011549C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80115720_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116024_w04);

void func_8011621C_w04(s32 arg0) {
    {
        omObjData *obj = D_8011E100_w04[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011E100_w04[arg0] = NULL;
        }
    }

    {
        Object *model = D_8011E0F0_w04[arg0];

        if (model != NULL) {
            MBModelKill(model);
            D_8011E0F0_w04[arg0] = NULL;
        }
    }
}

void func_80116294_w04(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_8011E100_w04[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_8011E100_w04[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801162F8_w04);

void func_801164A4_w04(s32 playerNo, s32 type) {
    GW_PLAYER *player;
    Object *obj;
    s32 modelId;

    player = MBPlayerGet(playerNo);

    if (D_8011E0F0_w04[playerNo] == NULL) {
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
        D_8011E0F0_w04[playerNo] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &player->player_obj->coords);
        obj->velocity.x = 20.0f;
        MBVecForwardSet(&obj->rot);
    } else {
        func_800D9A40_shared_board(D_8011E0F0_w04[playerNo]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801165A4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116640_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116740_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011694C_w04);

void func_80116AAC_w04(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80116AFC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117074_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117244_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011737C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117800_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117EA8_w04);

Process *func_80118240_w04(void) {
    return omAddPrcObj(func_80117EA8_w04, 0x1000, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011826C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801183D4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801191B8_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80119FCC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A4E0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A5DC_w04);

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE80_w04);

// main func for reroll event in woody woods
void func_8011A858_w04(void) {
    GW_PLAYER *curPlayer;
    s16 curPlayerSpace;

    curPlayer = MBPlayerGet(CUR_PLAYER);
    curPlayerSpace = MBMasuLinkMasuIdGet(curPlayer->clink, curPlayer->cidx);
    HuPrcSleep(8);
    switch (curPlayerSpace) {
        // space IDs for reroll event
        case 0x3F:
        case 0x49:
        case 0x4A:
            func_801183D4_w04();
            break;
        case 0x1F:
        case 0x21:
        case 0x22:
            func_801191B8_w04();
            break;
        case 0x4F:
            func_8011A4E0_w04(0);
            break;
        case 0xC:
            func_8011A4E0_w04(1);
            break;
        case 0x3B:
            func_8011A4E0_w04(2);
            break;
    }
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011A91C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AA10_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AA64_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AB34_w04);

s32 func_8011AC0C_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AC60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AD48_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011B350_w04);

s32 func_8011B6B4_w04(void) {
    if (D_8011DC68_w04 != 0) {
        D_8011DC68_w04 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011DDBC_w04[D_8011C688_w04]) + 1;
}
