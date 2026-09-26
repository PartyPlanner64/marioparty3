#include "common.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/113520.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/FFB10.h"
#include "../ovl_80_shared_board/EDDB0.h"
#include "../ovl_80_shared_board/EB2F0.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/113750.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/ECA50.h"

void func_801064DC_w05(void);
void func_801085B4_w05(void);
void func_8010D298_w05(void);
extern s16 D_8011D060_w05[];
extern s16 D_8011D070_w05[];
extern s16 D_8011D080_w05[];
extern s16 D_8011D110_w05[][2];
extern s16 D_8011D118_w05[][2];
extern s16 D_8011D2B8_w05[];
extern s16 D_8011D2BC_w05[];
extern s16 D_8011EE48_w05[][6];
extern s8 D_8011EA00_w05[][5][7];
extern s32 D_8011EB38_w05;
extern s32 D_801204B8_w05;
extern s32 D_8011D24C_w05[];
extern s32 D_8011D270_w05[];
extern DecisionTreeNonLeafNode *D_8012060C_w05[];
extern Process *D_80120768_w05[8];
extern Unk3 *D_80120790_w05;
extern Unk3 *D_80120794_w05;
extern Unk3 *D_80120798_w05;
extern Unk3 *D_8012079C_w05;
extern Unk3 *D_801207A0_w05;
extern s32 D_80120818_w05;
extern s32 D_80120824_w05;
extern s32 D_80120828_w05;
extern u8 *D_8012082C_w05;
extern omObjData *D_80120880_w05[4];
extern Object *D_80120870_w05[4];

s16 func_801059D0_w05(void) {
    return D_8011D080_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801059F8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80105B00_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80105B8C_w05);

s16 func_80105C30_w05(s16 arg0) {
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    for (i = 0; i < STAR_POSITIONS_TOTAL; i++) {
        if (arg0 == D_8011D070_w05[i]) {
            if (i == system->star_spawn_indices[system->current_star_spawn]) {
                system->unk_0E = D_8011D060_w05[i];
                return 1;
            }
            break;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80105CA4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106094_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106120_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801064DC_w05);

void func_80106A3C_w05(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w05, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWait();
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106AB0_w05);

void func_80106B38_w05(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), 0x80);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106B94_w05);

void func_80106C64_w05(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_80120790_w05);
    MBHelpWinKill(D_80120794_w05);
    MBHelpWinKill(D_801207A0_w05);
    MBHelpWinKill(D_80120798_w05);
    MBHelpWinKill(D_8012079C_w05);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106CC4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80106F58_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107170_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801072A0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107438_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107704_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107724_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107744_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107780_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010782C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107B90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107C14_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107C40_w05);

void func_80107D68_w05(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_80120768_w05[i] != NULL) {
            omDelPrcObj(D_80120768_w05[i]);
            D_80120768_w05[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107DCC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107E78_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107F98_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80107FF4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801080F0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010825C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801082C4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108430_w05);

void func_80108490_w05(void) {
    HuPrcSleep(D_8011D270_w05[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011D24C_w05[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801084EC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801085B4_w05);

void func_80108664_w05(s32 arg) {
    Process *prc = omAddPrcObj(func_801085B4_w05, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

void func_801086A0_w05(void) {
    s32 i;

    D_80120818_w05 = 0;
    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(8, &MBMasuGet(D_8011D2B8_w05[i])->coords,
                                   D_8011D110_w05[i][0], D_8011D110_w05[i][1]);
    }
}

void func_80108720_w05(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_800D7790_shared_board(9, &MBMasuGet(D_8011D2BC_w05[i])->coords,
                                   D_8011D118_w05[i][0], D_8011D118_w05[i][1]);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108798_w05);

void func_80108830_w05(s32 masuId, s32 link, s32 idx) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == masuId) {
        MBMoveNextMasuSet(-1, link, idx);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801088B8_w05);

void func_80108924_w05(void) {
    MBMoveNextMasuSet(-1, 1, 2);
}

void func_80108948_w05(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6C) {
        MBMoveBackMasuSet(-1, 1, 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801089A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108A58_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108A90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108B18_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108B50_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108B88_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108BC0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108C70_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108CF8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108D28_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108D58_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108D88_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108DB8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108DE8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E18_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E48_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E6C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108E90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108EB4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F20_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F44_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F68_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108F8C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FD4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80108FF8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010901C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109078_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090A4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090C8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801090EC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109118_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010913C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109160_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109184_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091CC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801091F0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109214_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109270_w05);

void func_801096C4_w05(void) {
}

void func_801096CC_w05(void) {
}

void func_801096D4_w05(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801096DC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109960_w05);

void func_80109A1C_w05(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109A5C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80109E08_w05);

s32 func_8010A944_w05(s32 arg0) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8012082C_w05[i] != 0 && D_8011EA00_w05[D_80120824_w05][D_80120828_w05][i] == arg0) {
            return i;
        }
    }
    return -1;
}

s32 func_8010A9CC_w05(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        if (D_8011EA00_w05[D_80120824_w05][D_80120828_w05][i] == -1) {
            break;
        }
    }
    return i;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010AA34_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010AC0C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010BEC0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010BF60_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010C000_w05);

void func_8010C448_w05(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010C46C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010D298_w05);

void func_8010D3EC_w05(s32 arg) {
    Process *prc = omAddPrcObj(func_8010D298_w05, 0x1000, 0, 0);

    prc->user_data = (void *)arg;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010D428_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E5FC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E618_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E634_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E790_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010E8A8_w05);

void func_8010EC70_w05(void) {
    s16 ret;

    D_800A12D0_main = 1;
    MBMasuEventCall(D_8011D070_w05[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]], 1);
    D_800A12D0_main = 0;
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(-1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010ECDC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010EE9C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F100_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F1D0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F400_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F5D0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010F740_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FA8C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FC50_w05);

INCLUDE_RODATA("asm/nonmatchings/overlays/w05/37FFB0", D_80120690_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8010FEE8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110174_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801103B4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801105C4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110884_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80110C24_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111620_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111B68_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80111D84_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112178_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112234_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112388_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801123C4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112554_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112910_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112BA8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112CB4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80112E90_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80113B3C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80113BFC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011412C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114A38_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114B70_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114CE0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80114EA8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011512C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115A30_w05);

void func_80115C28_w05(s32 arg0) {
    {
        omObjData *obj = D_80120880_w05[arg0];

        if (obj != NULL) {
            omDelObj(obj);
            D_80120880_w05[arg0] = NULL;
        }
    }

    {
        Object *model = D_80120870_w05[arg0];

        if (model != NULL) {
            MBModelKill(model);
            D_80120870_w05[arg0] = NULL;
        }
    }
}

void func_80115CA0_w05(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        omObjData *obj = D_80120880_w05[i];

        if (obj != NULL) {
            omDelObj(obj);
            D_80120880_w05[i] = NULL;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115D04_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115EB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80115FB0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011604C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011614C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116358_w05);

void func_801164B8_w05(void) {
    s32 i = 0x3C;
    UnkVibrateProcess *vib = HuPrcCurrentGet()->user_data;

    do {
        i--;
        HuPrcVSleep();
    } while (i != 0);

    MBPlayerVibrateObjKill(vib);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116508_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116A80_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116C50_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80116D88_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011720C_w05);

void func_801178B4_w05(GW_PLAYER *player, s32 index, s16 paths[][6]) {
    s16 *path = paths[index];

    player->clink = *path++;
    player->cidx = *path++;
    player->nlink = *path++;
    player->nidx = *path++;
    player->blink = *path++;
    player->bidx = *path;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80117908_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118364_w05);

void func_80118464_w05(void) {
    s32 r = MBRand(10.0f);
    s16 itemIndex;

    if (r < 6) {
        itemIndex = 0;
    } else if (r < 8) {
        itemIndex = 1;
    } else {
        itemIndex = 2;
    }
    GwSystem.boardData.halfWordBytes[1] = itemIndex;
    GwSystem.boardData.halfWordBytes[2] = -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801184C0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118BBC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118CF8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80118E2C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801191C0_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_801192AC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119610_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119A4C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119BC4_w05);

void func_80119F04_w05(void) {
    s32 masuId = (s32)HuPrcCurrentGet()->user_data;
    s16 masuAbsIndex;

    HuPrcSleep(10);

    switch (masuId) {
        case 0:
            masuAbsIndex = 0x91;
            break;
        case 1:
            masuAbsIndex = 0x92;
            break;
        case 2:
            masuAbsIndex = 0x8F;
            break;
        default:
            masuAbsIndex = 0x90;
    }

    func_800ED20C_shared_board(-1, 8, masuAbsIndex);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_80119F7C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011A6E8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011A8D8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011ABEC_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011AD34_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011AEA4_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011BB74_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011BC40_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C2A8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C2F8_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C348_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C39C_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C448_w05);

s32 func_8011C50C_w05(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 turnsLeft = system->total_turns - system->current_turn + 1;
    s32 emptyItemSlot = MBItemFindEmpty(-1);

    if (emptyItemSlot == ITEM_NONE) {
        emptyItemSlot = 3;
    }
    return emptyItemSlot >= turnsLeft;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C560_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011C648_w05);

INCLUDE_ASM("asm/nonmatchings/overlays/w05/37FFB0", func_8011CC50_w05);

s32 func_8011CFB4_w05(void) {
    if (D_801204B8_w05 != 0) {
        D_801204B8_w05 = 0;
        return 2;
    }
    return MBComTreeExec(D_8012060C_w05[D_8011EB38_w05]) + 1;
}
