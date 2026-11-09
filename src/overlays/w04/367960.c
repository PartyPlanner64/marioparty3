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
extern s16 D_8011B740_w04[];
extern s16 D_8011B750_w04[];
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

extern Process *D_8011E038_w04;
extern Object *D_8011E03C_w04;
void func_80107828_w04(void);
extern s16 D_8011B7E4_w04[][2];
extern s16 D_8011B82C_w04[];
extern Object *D_8011DFF0_w04;
extern Object *D_8011DFF8_w04[8];
extern s16 D_8011B804_w04[][2];
extern s16 D_8011B84C_w04[];
extern Object *D_8011E05C_w04;
extern Object *D_8011E060_w04[1];
extern Object *D_8011E068_w04[10];
extern s16 D_8011B850_w04[];
extern Vec D_8011B854_w04[];
extern Vec D_8011B890_w04[];
extern Object *D_8011E064_w04;
extern s32 D_8011B990_w04[];
extern Object *D_8011E094_w04[2];
extern DecisionTreeNonLeafNode *D_8011BA08_w04[];
extern s16 D_8011BFB8_w04[][3];
extern BranchPair D_8011BFCC_w04[];
void func_80116024_w04(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees);
extern DecisionTreeNonLeafNode *D_8011BCF0_w04[];
extern s16 D_8011C1B0_w04[][3];
extern BranchPair D_8011C1C4_w04[];
extern DecisionTreeNonLeafNode *D_8011BD38_w04[];
extern s16 D_8011C1F8_w04[][3];
extern BranchPair D_8011C20C_w04[];
extern DecisionTreeNonLeafNode *D_8011BD68_w04[];
extern s16 D_8011C240_w04[][3];
extern BranchPair D_8011C254_w04[];
extern DecisionTreeNonLeafNode *D_8011BDE0_w04[];
extern s16 D_8011C288_w04[][3];
extern BranchPair D_8011C29C_w04[];
extern DecisionTreeNonLeafNode *D_8011BE28_w04[];
extern s16 D_8011C2D0_w04[][3];
extern BranchPair D_8011C2E4_w04[];
extern DecisionTreeNonLeafNode *D_8011BE88_w04[];
extern s16 D_8011C318_w04[][3];
extern BranchPair D_8011C32C_w04[];
extern DecisionTreeNonLeafNode *D_8011BF0C_w04[];
extern s16 D_8011C360_w04[][3];
extern BranchPair D_8011C374_w04[];
void func_8010D88C_w04(void);
void func_8010ED84_w04(omObjData *arg0);
extern Vec2f D_8011C804_w04[];
extern Vec2f D_8011C824_w04[];
extern s32 D_8011C8F0_w04[];
extern s32 D_8011E0B8_w04;
extern DecisionTreeNonLeafNode D_8011C904_w04[];
s32 func_80109CD4_w04(s32 arg0, s32 arg1);
extern Vec2f D_8011C69C_w04[];
extern Vec2f D_8011C6BC_w04[];
extern Vec2f D_8011C910_w04[];
extern s32 D_8011E0BC_w04;
extern s32 D_8011E0C0_w04;
extern Object *D_8011E0C8_w04;
extern Object *D_8011E0C4_w04;
void func_8011297C_w04(Object *arg);
extern s32 D_8011C940_w04;
extern Object *D_8011E0D4_w04;
extern s32 D_8011E0D8_w04[4];
extern Object *D_8011E0E8_w04;
extern RectF D_8011CB18_w04;
void func_80106120_w04(void);
extern u8 *D_8011DCEC_w04[];
extern s8 *D_8011DD8C_w04[];
extern DecisionTreeNonLeafNode *D_8011DDAC_w04[];
extern DecisionTreeNonLeafNode *D_8011DDB4_w04[];
s32 func_80107438_w04(u8 *arg0, s32 arg1, s32 arg2);
extern s16 D_8011B83C_w04[];
void func_80108268_w04(s16 arg0);
extern s32 D_8011B924_w04[];
void func_80112378_w04(void);
extern DecisionTreeNonLeafNode D_8011C884_w04[];
void func_8010B1FC_w04(void);
void func_80112828_w04(void);
void func_801165A4_w04(s32 arg);
s16 func_801059D0_w04(void) {
    return D_8011B780_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w04(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011B750_w04[idx2]) {
                continue;
            }
            if (idx2 < D_8011B750_w04[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011B740_w04[idx1];
                D_8011B740_w04[idx1] = D_8011B740_w04[idx2];
                D_8011B740_w04[idx2] = temp;
                temp = D_8011B750_w04[idx1];
                D_8011B750_w04[idx1] = D_8011B750_w04[idx2];
                D_8011B750_w04[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011B740_w04[i];
    }
}

void func_80105B00_w04(void) {
    GW_SYSTEM *loc;
    s32 sp7;
    s32 sp0;

    loc = &GwSystem;
    loc->current_star_spawn++;
    if (loc->current_star_spawn >= 8) {
        sp7 = loc->star_spawn_indices[7];
        loc->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w04();
        sp0 = loc->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            loc->star_spawn_indices[0] = loc->star_spawn_indices[7];
            loc->star_spawn_indices[7] = sp0;
        }
    }
}

void func_80105B8C_w04(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011B760_w04[i]);
    }
    MBMasuTypeSet(D_8011B770_w04[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011B760_w04[loc->star_spawn_indices[loc->current_star_spawn]]);
}

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

void func_80105CA4_w04(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011E03C_w04 = MBModelCreate(0x3A, NULL);
    model = D_8011E03C_w04;
    func_800461B4_main(model->omObj1->model[0]);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    HuVecCopy3F(&model->coords, &space->coords);
    model->velocity.x = 50.0f;
    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 2.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 30.0f);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
    Hu3DModelCameraSet(obj, HU3D_CAM0);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 30.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 30.0f);
    HuPrcSleep(30);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    while (1) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (scale > 0.6f) {
            scale -= 0.04f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        if (model->velocity.x > 10.0f) {
            model->velocity.x -= 1.2f;
        }
        func_8000D018_main(obj, scale * 30.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        if ((model->velocity.x <= 10.0f) & (scale <= 0.6f)) {
            if (angle == 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }

    func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, 0.0f);
    func_8000D044_main(obj);
    D_8011E038_w04 = 0;
    omDelPrcObj(NULL);
}

void func_80106094_w04(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    HuPrcSleep(3);
    while (obj->velocity.z != 0.0f) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106120_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801064DC_w04);

void func_80106A3C_w04(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801064DC_w04, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void func_80106AB0_w04(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106B38_w04(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106B94_w04(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011E040_w04 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011E044_w04 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011E050_w04 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011E048_w04 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011E04C_w04 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106C64_w04(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011E040_w04);
    MBHelpWinKill(D_8011E044_w04);
    MBHelpWinKill(D_8011E050_w04);
    MBHelpWinKill(D_8011E048_w04);
    MBHelpWinKill(D_8011E04C_w04);
}

// Keep rodata definitions interleaved with functions to preserve the original constant order.
const u8 D_8011DDD0_w04[4] = { 1, 2, 4, 8 };

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106CC4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80106F58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107170_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801072A0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107438_w04);

s32 func_80107704_w04(u8 *arg0) {
    return func_80107438_w04(arg0, 0, 1);
}

s32 func_80107724_w04(u8 *arg0) {
    return func_80107438_w04(arg0, 1, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107744_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107780_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107828_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107B34_w04);

void func_80107BB8_w04(void) {
    Hu3DCamInit(1);
    func_80107828_w04();
    MBStart(1);
}

void func_80107BE4_w04(s16 arg0) {
    Object *obj;

    if (D_8011DFF8_w04[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011DFF0_w04 == NULL) {
        D_8011DFF0_w04 = obj;
    }
    D_8011DFF8_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011E018_w04[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B82C_w04[arg0])->coords);
    func_800D771C_shared_board(0xB, obj, D_8011B7E4_w04[arg0][0], D_8011B7E4_w04[arg0][1]);
}

void func_80107D0C_w04(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8011E018_w04[i] != NULL) {
            omDelPrcObj(D_8011E018_w04[i]);
            D_8011E018_w04[i] = NULL;
        }
    }
}

void func_80107D70_w04(void) {
    s32 i;

    D_8011DFF0_w04 = 0;
    for (i = 0; i < 8; i++) {
        D_8011DFF8_w04[i] = 0;
        D_8011E018_w04[i] = NULL;
        MBKinokoEffKillHookSet(func_80107D0C_w04);
        if (!GWBoardFlagCheck(D_8011B83C_w04[i])) {
            func_80107BE4_w04(i);
        }
    }
}

void func_80107E1C_w04(s16 arg0) {
    Object *obj;

    if (D_8011E060_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E05C_w04 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011E05C_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E05C_w04);
    }
    MBModelDispOff(obj);
    D_8011E060_w04[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B84C_w04[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011B804_w04[arg0][0], D_8011B804_w04[arg0][1]);
}

void func_80107F3C_w04(void) {
    s32 i;

    D_8011E05C_w04 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011E060_w04[i] = NULL;
        func_80107E1C_w04(i);
    }
}

void func_80107F98_w04(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011E068_w04[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011E068_w04[i * 5 + j]);
        }
    }
}

void func_80108094_w04(s16 arg0) {
    Object *obj;

    if (D_8011E068_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E064_w04 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011E064_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E064_w04);
    }
    D_8011E068_w04[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B850_w04[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011B854_w04[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011B890_w04[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011B890_w04[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_80108200_w04(void) {
    s32 i;

    D_8011E064_w04 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011E068_w04[i] = NULL;
        func_80108094_w04(i);
    }
    func_80107F98_w04();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108268_w04);

void func_801083D4_w04(void) {
    s32 i;

    D_8011E090_w04 = 0;
    for (i = 0; i < 2; i++) {
        D_8011E094_w04[i] = NULL;
        func_80108268_w04(i);
    }
}

void func_80108434_w04(void) {
    HuPrcSleep(D_8011B96C_w04[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011B948_w04[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_80108490_w04(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011E094_w04[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011E094_w04[arg0]->omObj1->model[0], 5, 0);
    if (D_8011B924_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B924_w04[GwSystem.current_board_index]);
    }

    if (D_8011B948_w04[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108434_w04, 0x1000, 0, 0);
    }
}

void func_80108558_w04(void) {
    s32 index;
    s32 sleep;

    index = (s32)HuPrcCurrentGet()->user_data;

    switch (GwSystem.walk_speed) {
        case 0:
            sleep = 5;
            break;
        case 1:
            sleep = 10;
            break;
        default:
            sleep = 15;
            break;
    }

    HuPrcSleep(sleep);
    func_8001C814_main(D_8011E094_w04[index]->omObj1->model[0], 1, 4);

    if (D_8011B990_w04[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011B990_w04[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

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

void func_801088FC_w04(void) {
    func_80116024_w04(D_8011BFB8_w04, D_8011BFCC_w04, D_8011BA08_w04);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108934_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801089B0_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108A58_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108AD4_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108B4C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80108C00_w04);

void func_80108CA8_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C1B0_w04, D_8011C1C4_w04, D_8011BCF0_w04);
    }
}

void func_80108D00_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C1F8_w04, D_8011C20C_w04, D_8011BD38_w04);
    }
}

void func_80108D58_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C240_w04, D_8011C254_w04, D_8011BD68_w04);
    }
}

void func_80108DB0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C288_w04, D_8011C29C_w04, D_8011BDE0_w04);
    }
}

void func_80108E08_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C2D0_w04, D_8011C2E4_w04, D_8011BE28_w04);
    }
}

void func_80108E60_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C318_w04, D_8011C32C_w04, D_8011BE88_w04);
    }
}

void func_80108EB8_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_80116024_w04(D_8011C360_w04, D_8011C374_w04, D_8011BF0C_w04);
    }
}

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

void func_80109F58_w04(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
    s16 sp10[2];
    s16 winId;

    HuWinMesMaxSizeGet(1, sp10, arg1);
    winId = MBWinCreate(arg0, sp10, arg2);
    mbDlgWinId = winId;
    HuWinMesSet(winId, arg1, -1, -1);
    HuWinExAnimIn(winId);
    func_800EBF98_shared_board(winId, arg3);
    HuWinExAnimOut(winId, 0);
    HuWinKill(winId);
}

void func_8010A014_w04(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010A054_w04);

const char D_8011DDD4_w04[] = "%d";

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

void func_8010B024_w04(void) {
    s32 grp = (s32)HuPrcCurrentGet()->user_data;
    f32 angle;
    f32 scaleX;

    MBPlayerGet(GwSystem.current_player_index);
    MBPlayerVibrate(-1, 2);
    HuAudFXPlay(0x15A);

    for (angle = 0.0f; angle < 180.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 1.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.5f);
        HuPrcVSleep();
    }

    for (; angle < 360.0f; angle += 20.0f) {
        scaleX = sindf(angle) * 0.5f + 1.0f;
        HuSprScaleSet(grp, 0, scaleX, 1.0f - sindf(angle) * 0.25f);
        HuPrcVSleep();
    }

    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010B1FC_w04);

void func_8010C4B4_w04(Object *obj) {
    s32 i;

    MBModelDispOn(obj);
    for (i = 0; i < 0x100; i += 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
}

void func_8010C554_w04(Object *obj) {
    s32 i;

    for (i = 0xFF; i >= 0; i -= 0xC) {
        func_8001F9E4_main(obj->omObj1->model[0], i);
        func_8001F9E4_main(obj->omObj2->model[0], i);
        HuPrcVSleep();
    }
    func_8001F9E4_main(obj->omObj1->model[0], 0);
    func_8001F9E4_main(obj->omObj2->model[0], 0);
    MBModelDispOff(obj);
}

s32 func_8010C5F4_w04(s32 playerIndex) {
    s32 hasRareItem = 0;
    s16 grp;
    void *data;
    s16 spriteId;
    s32 i;
    s32 duration;
    Process *process;

    grp = HuSprGrpCreate(1, 5);
    data = DataRead(0x13020E);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    HuSprPriSet(grp, 0, 0xA);
    func_800550F4_main(grp, 0, 0);
    HuSprAttrSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, D_8011C69C_w04[playerIndex].x,
                D_8011C69C_w04[playerIndex].y);
    HuSprTPLvlSet(grp, 0, 0);
    HuAudFXPlay(0x134);

    for (i = 0; i < 0x11; i++) {
        HuSprPosSet(grp, 0,
                    (i * D_8011C6BC_w04[playerIndex].x) +
                        D_8011C69C_w04[playerIndex].x,
                    (i * D_8011C6BC_w04[playerIndex].y) +
                        D_8011C69C_w04[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(grp, 0, 0xFF);

    if (MBItemFind(playerIndex, 0xC) != -1) {
        hasRareItem = 1;
        process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
        process->user_data = (void *)playerIndex;
    }

    if (!hasRareItem) {
        GwPlayer[playerIndex].star--;
    }
    MBPlayerVibrate(playerIndex, 5);
    HuAudFXPlay(0x257);

    duration = hasRareItem ? 0x78 : 0x1E;
    for (i = 0; i < duration; i++) {
        HuSprPosSet(grp, 0,
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y +
                        (sindf(i * 90) * 4.0f));
        HuPrcVSleep();
    }

    for (i = 0x10; i >= 0; i--) {
        HuSprPosSet(grp, 0,
                    (i * D_8011C6BC_w04[playerIndex].x) +
                        D_8011C69C_w04[playerIndex].x,
                    (i * D_8011C6BC_w04[playerIndex].y) +
                        D_8011C69C_w04[playerIndex].y);
        HuSprTPLvlSet(grp, 0, i << 4);
        HuPrcVSleep();
    }
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    return !hasRareItem;
}

void func_8010CA3C_w04(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010CA60_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010D88C_w04);

void func_8010D9E0_w04(Object *arg) {
    Process *temp = omAddPrcObj(func_8010D88C_w04, 0x1000, 0, 0);

    temp->user_data = arg;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8010DA1C_w04);

void func_8010EBF0_w04(void) {
    func_80108608_w04(0);
}

void func_8010EC0C_w04(void) {
    func_80108608_w04(1);
}

omObjData *func_8010EC28_w04(Vec *arg0, f32 arg1, f32 arg2, s16 arg3, Vec *arg4, s32 arg5) {
    omObjData *obj;
    ModelFadeWork *data;
    Object *model;

    obj = omAddObj(0x1F4, 0, 0, -1, func_8010ED84_w04);
    data = obj->data = HuMemAllocTag(0x20, TAG_OVERLAY);
    data->unk0C = 255.0f;
    data->unk10 = arg1;
    data->unk14 = arg2;
    HuVecCopy3F(&data->unk00, arg4);
    if (arg5 != 0) {
        model = MBModelFileCreate(0x1301F8, 0, 1.0f, 0, 0);
    } else {
        model = MBModelFileCreate(0x1301F7, 0, 1.0f, 0, 0);
    }
    Hu3DModelScaleSet(model->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    model->coords.x = arg0->x;
    model->coords.y = arg0->y;
    model->coords.z = arg0->z;
    func_8001FA68_main(model->omObj1->model[0]);
    func_8001F9E4_main(model->omObj1->model[0], 0xFF);
    data->model = model;
    data->unk1C = arg3;
    return obj;
}

void func_8010ED84_w04(omObjData *arg0) {
    ModelFadeWork *data = arg0->data;
    Object *model = data->model;
    f32 scale;
    f32 alpha;

    HuVecAdd(&model->coords, &model->coords, &data->unk00);
    scale = model->scale.z + data->unk10;
    model->scale.z = scale;
    model->scale.y = scale;
    model->scale.x = scale;
    alpha = data->unk0C - data->unk14;
    data->unk0C = alpha;
    if (alpha < 0.0f) {
        data->unk0C = 0.0f;
        if (data->unk1C != 0) {
            MBModelKill(data->model);
            omDelObj(arg0);
            return;
        }
        omSetStatBit(arg0, OM_STAT_FUNCOFF);
    }
    func_8001F9E4_main(model->omObj1->model[0], (u8)data->unk0C);
}

// Shared particle direction table; replaced by local initializers once its users are matched.
const Vec D_8011DDE0_w04[8] = {
    { 1.0f, 1.0f, 1.0f },  { 1.0f, 2.0f, 1.0f },   { 0.0f, 2.0f, 1.0f },  { -1.0f, 1.0f, 1.0f },
    { -1.0f, -1.0f, 1.0f }, { 0.0f, -1.0f, 1.0f }, { -1.0f, 2.0f, 1.0f }, { 1.0f, -1.0f, 1.0f },
};

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

void func_8010F490_w04(void) {
    Process *process = HuPrcCurrentGet();
    WarpBlockSwapWork *work = process->user_data;
    f32 deltaX;
    f32 deltaY;
    f32 spriteX;
    f32 spriteY;
    s32 i;

    deltaX = (f32)(work->endX - work->startX) / (f32)work->duration;
    deltaY = (f32)(work->endY - work->startY) / (f32)work->duration;
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &spriteX, &spriteY);

    for (i = 1; i <= work->duration; i++) {
        if (work->spriteGroup != -1) {
            HuSprPosSet(work->spriteGroup, 0,
                        work->startX + (deltaX * i), work->startY + (deltaY * i));
        }

        MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                           spriteX + (deltaX * i), spriteY + (deltaY * i));
        HuPrcVSleep();
    }

    if (work->spriteGroup != -1) {
        HuSprPosSet(work->spriteGroup, 0, work->endX, work->endY);
    }

    MBStatusItemPosSet(GwSystem.current_player_index, MBItemSelNoGet(),
                       work->endX + spriteX - work->startX,
                       work->endY + spriteY - work->startY);
    omDelPrcObj(NULL);
}

Process *func_8010F6F4_w04(s32 spriteGroup, s16 startX, s16 startY, s16 endX, s16 endY,
                           s16 duration) {
    Process *process;
    WarpBlockSwapWork *work;

    process = omAddPrcObj(func_8010F490_w04, 0x4002, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x10);
    process->user_data = work;
    work->startX = startX;
    work->startY = startY;
    work->endX = endX;
    work->endY = endY;
    if (duration == -1) {
        duration = 25;
    }
    work->duration = duration;
    work->spriteGroup = spriteGroup;
    return process;
}

void func_8010F7C4_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, func_8010F6F4_w04(
                                mbItemCursorGrpId, position[0], position[1],
                                D_8011C804_w04[system->current_player_index].x,
                                D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        MBStatusItemOfsApply(system->current_player_index,
                             MBItemSelNoGet(), 0, 2.0f);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    MBPlayerMotionSet(-1, 5, 0);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(50);
    MBPlayerMotionSet(-1, -1, 2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void func_8010F9F4_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    func_8010F6F4_w04(
        mbItemCursorGrpId, position[0], position[1],
        D_8011C824_w04[system->current_player_index].x,
        D_8011C824_w04[system->current_player_index].y, -1);
    HuPrcSleep(20);

    for (i = 1; i < 10; i++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (i * 25));
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuPrcSleep(2);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void func_8010FBC4_w04(void) {
    f32 position[2];
    s32 targetX;
    s32 targetY;
    Process *process;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    func_800F6848_shared_board(GwSystem.current_player_index,
                               MBItemSelNoGet(), &position[0], &position[1]);
    MBStatusItemPosGet(-1, MBItemSelNoGet(), &targetX, &targetY);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                     targetX, targetY, -1));
    HuPrcChildWatch();

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void func_8010FD34_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;
    s32 j;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                     D_8011C804_w04[system->current_player_index].x,
                                     D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    if ((GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 0xB) ||
        (GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] == 8)) {
        HuAudFXPlay(0x141);
    }

    for (i = 0; i <= 1080; i += 30) {
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
    }

    for (j = 1; j < 10; j++) {
        MBStatusItemTPLvlSet(system->current_player_index,
                             MBItemSelNoGet(), 255 - (j * 25));
        MBStatusItemRotSet(system->current_player_index,
                           MBItemSelNoGet(), sindf(i) * 30.0f);
        HuPrcVSleep();
        i += 30;
    }

    MBStatusItemTPLvlSet(system->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

void func_80110080_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    f32 position[2];
    Process *process;
    s32 i;

    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                     D_8011C804_w04[system->current_player_index].x,
                                     D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);

    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - (i * 25));
        HuPrcVSleep();
    }

    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110244_w04);

INCLUDE_RODATA("asm/nonmatchings/overlays/w04/367960", D_8011DE40_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801104DC_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110768_w04);

void func_801109A8_w04(void) {
    s32 index;
    s32 group;
    s32 alpha;
    void *dialog;
    f32 x;
    f32 y;
    f32 angle;

    index = (s32)HuPrcCurrentGet()->user_data;
    dialog = MBPlayerVibrateObjCreate(-1, 1, 5);
    group = HuSprGrpCreate(1, 0);
    HuSprGrpMemberSet(group, 0, D_8011E0B8_w04, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x1000);
    func_800F6848_shared_board(GwSystem.current_player_index, MBItemSelNoGet(), &x, &y);
    x += 20.0f;
    y -= 20.0f;
    HuSprPosSet(group, 0, x, y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0);

    alpha = 0xFF;
    angle = (f32)D_8011C8F0_w04[index];
    for (; alpha >= 0; alpha -= 0x14) {
        x += cosdf(angle) * 5.0f;
        y -= sindf(angle) * 5.0f;
        HuSprPosSet(group, 0, x, y);
        HuSprTPLvlSet(group, 0, alpha);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(group, 0, 0);
    MBPlayerVibrateObjKill(dialog);
    HuSprGrpKill(group);
    omDelPrcObj(0);
}

void func_80110BB8_w04(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 one;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011E0B8_w04 = HuSprAnimRead(data);
    DataClose(data);
    func_80110080_w04();

    while (1) {
        MBDlgWinInsertCreate(-1, 0x3A01, 0, 0, 0, 0, 0);
        choice = func_80109CD4_w04((s32)D_8011C884_w04, 0);
        MBDlgWinClose();
        MBDlgWinKill();

        if (choice < 2) {
            if (choice < 0) {
                process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
                omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
                func_80106B38_w04();
                one = 1;
                D_800CB99C_main = one;
                omAllPause();
                omDelPrcObj(process);
                func_800FC8A4_shared_board();
                continue;
            }
            GwSystem.forceShopHost = choice + 1;
            break;
        }

        process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
        omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
        func_80106B38_w04();
        one = 1;
        D_800CB99C_main = one;
        omAllPause();
        omDelPrcObj(process);
        func_800FC8A4_shared_board();
        continue;
    }

    {
        s32 i;

        HuPrcSleep(30);
        HuAudFXPlay(0x147);
        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);

        for (i = 0; i < 5; i++) {
            process = omAddPrcObj(func_801109A8_w04, 0x4002, 0, 0);
            process->user_data = (void *)i;
            HuPrcChildLink(HuPrcCurrentGet(), process);
            HuPrcSleep(3);
        }
        HuPrcChildWatch();
        HuPrcSleep(20);
    }

    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index,
                         MBItemSelNoGet(), 0);
    HuSprAnimKill(D_8011E0B8_w04);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (choice != 0) {
        HuAudFXPlay(0x2A0);
    } else if (GwPlayer[loc->current_player_index].coin < 5 ||
               loc->current_turn == loc->total_turns) {
        HuAudFXPlay(0x29A);
    } else {
        HuAudFXPlay(0x298);
    }
    func_8010B1FC_w04();
    GwSystem.forceShopHost = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80110E78_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80111218_w04);

void func_80111C14_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    s32 player;
    Process *process;
    s32 group;
    void *sprite;
    s32 spriteCount;
    s32 i;
    f32 position[2];
    s32 result;

    player = GwSystem.current_player_index;
    group = HuSprGrpCreate(1, 0);
    sprite = DataRead(D_8010197C_shared_board[1]);
    spriteCount = HuSprAnimRead(sprite);
    DataClose(sprite);
    HuSprGrpMemberSet(group, 0, spriteCount, 0);
    HuSprPriSet(group, 0, 0x4780);
    HuSprAttrSet(group, 0, 0x9000);
    HuSprBankSet(mbItemCursorGrpId, 0, 1, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuPrcSleep(20);
    HuAudFXPlay(0x145);
    MBStatusSprPosGet(mbItemCursorGrpId, 0, &position[0], &position[1]);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(mbItemCursorGrpId, position[0], position[1],
                                     D_8011C804_w04[system->current_player_index].x,
                                     D_8011C804_w04[system->current_player_index].y, -1));
    HuPrcChildWatch();
    HuPrcSleep(10);
    HuSprBankSet(mbItemCursorGrpId, 0, 0, 0);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    for (i = 1; i < 10; i++) {
        HuSprTPLvlSet(mbItemCursorGrpId, 0, 255 - i * 25);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(mbItemCursorGrpId, 0, 0);
    HuSprDispOff(mbItemCursorGrpId, 0);
    GwPlayer[player].itemNo[MBItemSelNoGet()] = -1;
    MBStatusItemTPLvlSet(player, MBItemSelNoGet(), 0);
    func_800F6848_shared_board(player, MBItemSelNoGet(), &position[0], &position[1]);
    HuSprPosSet(group, 0, position[0], position[1]);
    HuSprDispOn(group, 0);
    MBItemRemoveEmpty(player);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
retry:
    MBDlgWinInsertCreate(0x38, 0x4100, 0, 0, 0, 0, 0);
    result = func_80109CD4_w04((s32)&D_8011C904_w04, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    switch (result) {
        case 0:
            MBDlgWinInsertCreate(0x38, 0x4101, 0, 0, 0, 0, 0);
            break;
        case 1:
            MBDlgWinInsertCreate(0x38, 0x4102, 0, 0, 0, 0, 0);
            HuSprDispOff(group, 0);
            GwPlayer[player].itemNo[MBItemFindEmpty(player)] = 1;
            MBItemRemoveEmpty(player);
            GwSystem.cur_player_used_item &= ~1;
            break;
        default:
            HuSprDispOff(group, 0);
            func_80106B38_w04();
            D_800CB99C_main = 1;
            omAllPause();
            HuSprDispOn(group, 0);
            goto retry;
    }
    MBDlgWinClose();
    MBDlgWinKill();
    if (result == 0) {
        HuPrcSleep(10);
        for (i = 1; i < 0x40; i++) {
            HuSprTPLvlSet(group, 0, (u16)(255.0f - (f32)i * 3.984f));
            HuPrcVSleep();
        }
        HuSprTPLvlSet(group, 0, 0);
    }
    HuSprGrpKill(group);
    HuSprAnimKill(spriteCount);
}

void func_8011215C_w04(void) {
    s32 playerIndex;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    f32 scale;
    s32 alpha;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    group = HuSprGrpCreate(1, 0);
    setupGroup = group;
    HuSprGrpMemberSet(setupGroup, 0, D_8011E0C0_w04, 0);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    MBStatusItemPosGet(D_8011E0BC_w04, 0, &xPos, &yPos);

    xPos = (s32)((D_8011C6BC_w04[D_8011E0BC_w04].x * 16.0f) +
                 D_8011C69C_w04[D_8011E0BC_w04].x);
    yPos = (s32)((D_8011C6BC_w04[D_8011E0BC_w04].y * 16.0f) +
                 D_8011C69C_w04[D_8011E0BC_w04].y);
    HuSprPosSet(
        setupGroup, 0, (f32)xPos + D_8011C910_w04[playerIndex].x,
        (f32)yPos + D_8011C910_w04[playerIndex].y);
    HuSprColorSet(group, 0, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(group, 0, 0xFF);

    scale = 0.0f;
    alpha = 0xFF;
    while (alpha >= 0) {
        HuSprScaleSet(group, 0, scale, scale);
        HuSprTPLvlSet(group, 0, alpha);
        HuPrcVSleep();
        alpha -= 10;
        scale += 0.1f;
    }

    HuSprTPLvlSet(group, 0, 0);
    HuSprGrpKill(group);
    omDelPrcObj(NULL);
}

void func_80112378_w04(void) {
    s32 playerIndex;
    void *data;
    s32 itemSpriteId;
    s32 auraSpriteId;
    s32 group;
    s16 setupGroup;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    s32 i;
    s32 j;
    Process *childProcess;
    s32 fxId;

    playerIndex = (s32)HuPrcCurrentGet()->user_data;
    data = DataRead(0x21002C);
    itemSpriteId = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1301BA);
    auraSpriteId = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1301B9);
    D_8011E0C0_w04 = HuSprAnimRead(data);
    DataClose(data);

    group = HuSprGrpCreate(2, 2);
    setupGroup = group;
    func_800550F4_main(setupGroup, 0, 1);
    HuSprGrpMemberSet(setupGroup, 0, itemSpriteId, 0xC);
    HuSprPriSet(setupGroup, 0, 9);
    HuSprAttrSet(setupGroup, 0, 0x1000);
    func_800554C4_main(setupGroup, 0, -1);
    HuSprGrpMemberSet(setupGroup, 1, auraSpriteId, 0);
    HuSprPriSet(setupGroup, 1, 9);
    HuSprAttrSet(setupGroup, 1, 0x9000);
    HuSprColorSet(setupGroup, 1, 0xFF, 0xFF, 0xFF);
    HuSprTPLvlSet(setupGroup, 1, 0xFF);
    HuSprScaleSet(setupGroup, 1, 2.0f, 2.0f);
    func_800554C4_main(setupGroup, 1, 0);

    yPos = 0xC8;
    if (playerIndex & 1) {
        HuSprAttrSet(setupGroup, 0, 1);
        HuSprAttrSet(setupGroup, 1, 1);
        HuSprPosSet(setupGroup, 1, 0x14, -5);
    } else {
        yPos = 0x78;
        HuSprPosSet(group, 1, -0x14, -5);
    }

    xPos = (playerIndex < 2) ? -0x20 : 0x110;
    HuPrcSleep(0x14);
    GwPlayer[playerIndex].itemNo[MBItemFind(playerIndex, 0xC)] = -1;
    MBItemRemoveEmpty(playerIndex);
    MBStatusItemIconSprReinit(playerIndex);

    do {
        if (playerIndex < 2) {
            xPos += 5;
            if (xPos >= 0x33) {
                break;
            }
        } else {
            xPos -= 5;
            if (xPos < 0xD2) {
                break;
            }
        }
        HuSprPosSet(group, 0, yPos, xPos);
        HuPrcVSleep();
    } while (1);

    HuPrcSleep(0xA);
    HuSprDispOn(group, 1);
    fxId = HuAudFXPlay(0x14C);
    D_8011E0BC_w04 = playerIndex;

    for (j = 0; j < 4; j++) {
        for (i = 0; i < 6; i++) {
            childProcess = omAddPrcObj(func_8011215C_w04, 0x4002, 0, 0);
            childProcess->user_data = (void *)i;
            HuPrcSleep(2);
        }
        HuPrcSleep(5);
    }

    HuPrcChildLink(HuPrcCurrentGet(), childProcess);
    HuPrcChildWatch();
    HuAudFXStop(fxId);
    HuSprTPLvlSet(group, 1, 0);

    for (i = 0xFF; i >= 0; i -= 0x1E) {
        HuSprTPLvlSet(group, 0, i);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(group, 0, 0);
    HuSprGrpKill(group);
    HuSprAnimKill(D_8011E0C0_w04);
    HuSprAnimKill(auraSpriteId);
    HuSprAnimKill(itemSpriteId);
    omDelPrcObj(NULL);
}

void func_8011276C_w04(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112828_w04);

void func_8011297C_w04(Object *arg) {
    Process *temp = omAddPrcObj(func_80112828_w04, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_801129B8_w04(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        D_8011E0C8_w04->rot.x = -sindf(angle);
        D_8011E0C8_w04->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            D_8011E0C8_w04->scale.z = scale;
            D_8011E0C8_w04->scale.y = scale;
            D_8011E0C8_w04->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    D_8011E0C8_w04->scale.x = D_8011E0C8_w04->scale.y = D_8011E0C8_w04->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(D_8011E0C8_w04);
    omDelPrcObj(0);
}

void func_80112B48_w04(void) {
    s32 flag = 0;
    GW_SYSTEM *system = &GwSystem;
    void *data;
    UnkVibrateProcess *process;
    s32 positionX;
    s32 positionY;
    s32 bankCoins;
    s32 coinCount;
    s32 spriteId;
    f32 coinStep;
    f32 coinProgress;

    mbItemCursorGrpId = HuSprGrpCreate(1, 5);
    data = DataRead(D_80101040_shared_board[GwPlayer[system->current_player_index].chr]);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(mbItemCursorGrpId, 0, spriteId, 0);
    HuSprPriSet(mbItemCursorGrpId, 0, 10);
    func_800550F4_main(mbItemCursorGrpId, 0, 1);
    HuSprDispOff(mbItemCursorGrpId, 0);
    MBStatusItemPosGet(-1, 0, &positionX, &positionY);
    HuSprPosSet(mbItemCursorGrpId, 0, positionX, positionY);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(1);
    MBStatusGrow(-1);
    MBItemSelNoSet(MBItemFind(-1, 0xF));
    func_8010F9F4_w04();

    D_8011E0C8_w04 = MBModelCreate(0x44, NULL);
    HuVecCopy3F(&D_8011E0C8_w04->coords, &MBPlayerGet(-1)->player_obj->coords);
    D_8011E0C8_w04->velocity.x = 100.0f;
    while (30.0f < D_8011E0C8_w04->velocity.x) {
        D_8011E0C8_w04->velocity.x -= 1.0f;
        HuPrcVSleep();
    }
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);
    omAddPrcObj(func_801129B8_w04, 0x4002, 0, 0)->user_data = &flag;
    process = MBPlayerVibrateObjCreate(-1, 4, 5);

    bankCoins = GwSystem.bank_coins;
    coinStep = (f32)bankCoins / 30.0f;
    coinProgress = 0.0f;
    D_8011E0C4_w04 = MBModelCreate(0x19, NULL);
    MBModelTempAllocFree(D_8011E0C4_w04);
    MBModelDispOff(D_8011E0C4_w04);
    if (bankCoins != 0) {
        while (bankCoins != 0) {
            coinProgress += coinStep;
            coinCount = 0;
            while (coinProgress >= 1.0f) {
                coinProgress -= 1.0f;
                coinCount++;
            }
            if (coinCount != 0) {
                func_8011297C_w04(D_8011E0C8_w04);
                if (bankCoins - coinCount < 0) {
                    coinCount = bankCoins;
                }
                bankCoins -= coinCount;
                MBPlayerCoinAdd(system->current_player_index, coinCount);
                HuAudFXPlay(0x106);
                GwSystem.bank_coins -= coinCount;
                func_80107F98_w04();
                HuPrcSleep(5);
            }
        }
    }

    MBPlayerVibrateObjKill(process);
    flag = 1;
    HuPrcSleep(20);
    MBModelKill(D_8011E0C4_w04);
    MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(5);
    PlayerFXPlay(0x274, system->current_player_index);
    HuPrcSleep(0x2D);
    MBPlayerMotionSet(-1, -1, 2);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80112F04_w04);

void func_8011319C_w04(void) {
    Process *prc = HuPrcCurrentGet();
    s32 playerIdx = (s32)prc->user_data;
    s32 j;
    s32 val;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    MBPlayerVibrate(((s16 *)&prc->user_data)[1], 4);

    for (val = 0x80; val > 0; val -= 0xA) {
        for (j = 0; j < 3; j++) {
            if (GwPlayer[playerIdx].itemNo[j] != -1) {
                MBStatusItemTPLvlSet(playerIdx, j, val);
            }
        }
        HuPrcVSleep();
    }

    for (j = 0; j < 3; j++) {
        if (GwPlayer[playerIdx].itemNo[j] != -1) {
            MBStatusItemTPLvlSet(playerIdx, j, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801132A8_w04(void) {
    Process *process = HuPrcCurrentGet();
    s32 playerIndex = (s32)process->user_data;
    GW_SYSTEM *system = &GwSystem;
    s32 i;
    s32 alpha;
    s32 itemIndex;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;

    for (i = 0, itemIndex = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            MBStatusItemScaleSet(system->current_player_index, i, 1.0f, 1.0f);
            MBStatusItemPosGet(playerIndex, itemIndex, &xPos, &yPos);
            MBStatusItemPosSet(system->current_player_index, i, xPos, yPos);
            itemIndex += (i != MBItemSelNoGet());
        }
    }

    for (alpha = 0; alpha < 0x80; alpha += 0x14) {
        for (i = 0; i < 3; i++) {
            if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
                if (i != MBItemSelNoGet()) {
                    MBStatusItemTPLvlSet(system->current_player_index, i, alpha);
                }
            }
        }
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        if (GwPlayer[system->current_player_index].itemNo[i] != -1) {
            if (i != MBItemSelNoGet()) {
                MBStatusItemTPLvlSet(system->current_player_index, i, 0x80);
            }
        }
    }
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80113484_w04);

void func_80114130_w04(void) {
    ModelAnimWork *data = HuPrcCurrentGet()->user_data;
    Object *obj1 = data->obj1;
    Object *obj2 = data->obj2;

    MBMotionSet(obj1, -1, data->state);
    HuVecCopy3F(&obj1->coords, &obj2->coords);
    obj1->coords.y += obj2->velocity.x - 10.0f;
    func_800D9A40_shared_board(obj1);
    while (MBMotionCheck(obj1) == 0 && data->flag == 0) {
        HuPrcVSleep();
    }
    MBModelKill(obj1);
    omDelPrcObj(0);
}

void func_801141F0_w04(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = D_8011E0D4_w04;
    Object *model;
    Process *process;
    ModelAnimWork *work;
    s32 effect;
    f32 angle;
    f32 angleStep;
    f32 fallSpeed;
    f32 scale;
    s32 i;

    model = MBModelCreate(0x45, NULL);
    MBModelDispOff(model);
    effect = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 10.0f);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    HuAudFXPlay(0x24C);

    angle = 0.0f;
    angleStep = 2.0f;
    while (angleStep < 80.0f) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        angleStep += 1.0f;
        if (angleStep > 80.0f) {
            angleStep = 80.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14A);
    while (gameGuyModel->velocity.x < 110.0f) {
        gameGuyModel->velocity.x += 7.0f;
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    *processFlag = 0;
    while (*processFlag == 0) {
        if (D_8011C940_w04 != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(D_8011C940_w04)->player_obj->coords);
            func_8000CFA4_main(effect, gameGuyModel->coords.x,
                               gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x14B);
    fallSpeed = 3.0f;
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= fallSpeed;
        if (fallSpeed > 1.0f) {
            fallSpeed -= 0.2f;
        }
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    while (1) {
        gameGuyModel->rot.x = -sindf(angle);
        gameGuyModel->rot.z = cosdf(angle);
        angle += angleStep;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (angleStep > 15.0f) {
            angleStep -= 3.0f;
        } else {
            angleStep -= 0.5f;
        }
        if (angleStep < 1.0f) {
            break;
        }
        func_8000CFA4_main(effect, gameGuyModel->coords.x,
                           gameGuyModel->coords.y + gameGuyModel->velocity.x, gameGuyModel->coords.z);
        HuPrcVSleep();
    }

    func_8000D044_main(effect);
    process = omAddPrcObj(func_80114130_w04, 0x4800, 0, 0x40);
    work = HuMemMemoryAlloc(process->heap, 0x20);
    process->user_data = work;
    work->obj1 = model;
    work->obj2 = gameGuyModel;
    work->state = 0;
    work->flag = 0;
    HuPrcSleep(3);
    *processFlag = 0;
    HuAudFXPlay(0x24D);

    i = 0;
    scale = 0.1f;
    for (; i < 20; i++) {
        scale += 0.044999998f;
        func_8001D558_main(gameGuyModel->omObj1->model[0], scale, scale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(gameGuyModel);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80114720_w04);

void func_8011502C_w04(s32 arg0, s32 arg1, f32 *arg2) {
    f32 curX;
    f32 curY;
    f32 stepX;
    f32 stepY;

    MBStatusSprPosGet((s16)arg0, 0, &curX, &curY);
    stepX = (arg2[0] - curX) / arg1;
    stepY = (arg2[1] - curY) / arg1;
    while (arg1 != 0) {
        curX += stepX;
        curY += stepY;
        HuSprPosSet(arg0, 0, curX, curY);
        HuPrcVSleep();
        arg1--;
    }
    HuSprPosSet(arg0, 0, arg2[0], arg2[1]);
}

void func_80115164_w04(void) {
    s32 idx;
    s32 divisor;
    s32 i;

    idx = (s32)HuPrcCurrentGet()->user_data;
    divisor = 10;

    switch (idx) {
        case 0:
            HuSprPosSet(D_8011E0D8_w04[idx], 0, 0xB1, 0x2C);
            break;
        case 1:
            HuSprPosSet(D_8011E0D8_w04[idx], 0, 0x7A, 0x39);
            break;
        default:
            HuSprPosSet(D_8011E0D8_w04[idx], 0, 0xA0, 0x98);
            divisor = 30;
            break;
    }

    HuSprDispOn(D_8011E0D8_w04[idx], 0);
    for (i = 0; i < 255; i += 255 / divisor) {
        HuSprTPLvlSet(D_8011E0D8_w04[idx], 0, i & 0xFFFF);
        HuPrcVSleep();
    }

    HuSprTPLvlSet(D_8011E0D8_w04[idx], 0, 0xFF);
    omDelPrcObj(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801152D4_w04);

void func_8011549C_w04(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = D_8011E0E8_w04;
    func_800D9A40_shared_board(model);

    angle = 0.0f;
    for (scale = 1.0f; scale < 18.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 1) {
        wait_angle_step = 20.0f;
        while (*state != 1) {
            func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += wait_angle_step;
            HuPrcVSleep();
        }
    }

    for (; scale < 40.0f; scale = (f32)((f64)scale + 0.8)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    if (*state != 2) {
        scale = 20.0f;
        while (*state != 2) {
            func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
            angle += scale;
            HuPrcVSleep();
        }
    }

    MBModelKill(model);
    omDelPrcObj(0);
}

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

void func_801162F8_w04(omObjData *obj) {
    s32 playerIdx = obj->work[0];

    if (GwSystem.current_player_index == 4) {
        if (obj->work[2] == 0) {
            if (obj->work[1] != 0) {
                obj->work[1] -= 1;
                if (obj->work[1] != 0) {
                    return;
                }
                obj->work[2] = 1;
            } else {
                obj->work[1] = 40;
                return;
            }
        }
    }

    {
        GW_PLAYER *player = MBPlayerGet(playerIdx);
        Object *effectObj = D_8011E0F0_w04[playerIdx];

        HuVecCopy3F(&effectObj->coords, &player->player_obj->coords);
        effectObj->velocity.x = player->player_obj->velocity.x + 20.0f;
        HuVecCopy3F(&effectObj->rot, &player->player_obj->rot);
        effectObj->coords.x += sindf(obj->rot.x) * obj->trans.x;
        effectObj->coords.z += cosdf(obj->rot.x) * obj->trans.x;
        obj->rot.x += 5.0f;
        if (obj->rot.x >= 360.0f) {
            obj->rot.x -= 360.0f;
        }
        if (obj->trans.x <= 5.0f) {
            obj->trans.x += 0.25f;
        }
        if (player->player_obj->flags & 8) {
            func_800D9A40_shared_board(effectObj);
        } else {
            MBModelDispOff(effectObj);
        }
    }
}

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

void func_80116640_w04(void) {
    s32 i;
    s32 idx;

    for (i = 0; i < 4; i++) {
        D_8011E100_w04[i] = NULL;
        D_8011E0F0_w04[i] = NULL;
        idx = -!(MBPlayerGet(i)->rev & 0x2);
        if (MBPlayerGet(i)->rev & 0x4) {
            idx = 1;
        }
        if (MBPlayerGet(i)->rev & 0x20) {
            idx = 2;
        }
        if (MBPlayerGet(i)->rev & 0x40) {
            idx = 3;
        }
        if (idx != -1) {
            func_801164A4_w04(i, idx);
            func_801165A4_w04(i);
        }
    }
    func_800F8D54_shared_board(func_80116294_w04);
}

void func_80116740_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    f32 scale;

    if ((((*slowDiceFlags >> loc->current_player_index) & 1))) {
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        if ((player->rev & 0x20) || ((player->rev & 8) && !(player->rev & 2))) {
            MBDlgWinExec(-1, 0x4219);
        } else {
            MBDlgWinExec(-1, 0x3A07);
        }

        if (player->rev & 2) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

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

void func_80117074_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x80) {
        if ((player->rev & 0x40) || ((player->rev & 0x10) && !(player->rev & 4))) {
            MBDlgWinExec(-1, 0x421C);
        } else {
            MBDlgWinExec(-1, 0x3A03);
        }
        if (player->rev & 4) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_8011621C_w04(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117244_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011737C_w04);

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80117800_w04);

void func_80117EA8_w04(void) {
    void *data;
    s32 spriteId;
    s32 grp;
    s32 count;
    s32 wrapped;
    s32 fading;
    s32 mask;
    s32 clampedAlpha;
    s32 alpha;
    f32 angle;
    f32 speed;

    data = DataRead(0x1300F7);
    spriteId = HuSprAnimRead(data);
    DataClose(data);
    grp = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(grp, 0, spriteId, 0);
    HuSprAttrReset(grp, 0, 0xFFFF);
    HuSprAttrSet(grp, 0, 0x1008);
    HuSprPriSet(grp, 0, 0x1000);
    HuSprPosSet(grp, 0, 0xA0, 0x5A);

    angle = 0.0f;
    speed = 30.0f;
    count = 0;
    wrapped = 0;

    while (1) {
        if (angle >= 90.0f && wrapped == 0) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(grp, 0, 2);
        } else {
            HuSprAttrReset(grp, 0, 2);
        }
        HuSprScaleSet(grp, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprAttrReset(grp, 0, 2);
    HuSprScaleSet(grp, 0, 1.0f, 1.0f);
    HuPrcSleep(20);

    angle = 90.0f;
    count = 0;
    fading = 0;
    wrapped = 0;
    alpha = 255;

    while (1) {
        if (angle >= 360.0f && wrapped == 0) {
            wrapped = 1;
            count++;
        }
        if (angle >= 360.0f) {
            wrapped = 0;
            angle -= 360.0f;
        }
        if (fading == 0 && count != 0) {
            if (angle >= 90.0f && angle < 180.0f) {
                fading = 1;
            }
        }
        if (fading != 0) {
            alpha -= 21;
            mask = -(alpha > 0);
            clampedAlpha = mask & alpha;
            alpha = clampedAlpha;
        }
        HuSprTPLvlSet(grp, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
        angle += speed;
    }

    HuSprScaleSet(grp, 0, 1.0f, 0.0f);
    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    omDelPrcObj(NULL);
}

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

void func_8011AA10_w04(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &D_8011CB18_w04);
    func_80107828_w04();
    MBStart(2);
    omAddPrcObj(func_80106120_w04, 0x1005, 0x1000, 0);
}

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

s32 func_8011AC60_w04(s32 arg0, s32 arg1) {
    s32 result = 1;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 j;

        if (i == GwSystem.current_player_index) {
            continue;
        }
        for (j = 0; j < 3; j++) {
            if (GwPlayer[i].itemNo[j] == ITEM_PLUNDER_CHEST || GwPlayer[i].itemNo[j] == ITEM_BARTER_BOX) {
                break;
            }
        }
        if (j < 3) {
            break;
        }
    }
    if (i < 4) {
        result &= -!MBRandCheck100((s8)(arg0 + arg1 * GwPlayer[i].cpu_difficulty));
    }
    return result;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_8011AD48_w04);

s32 func_8011B350_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = D_8011DCEC_w04[player->chr][i];

        found = func_8010AF34_w04(val);
        if (found == -1) {
            continue;
        }
        if (D_80100F94_shared_board[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(D_8011DD8C_w04[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (func_8010AF34_w04(0xE) == found) {
            return found + 1;
        }
        if (func_8010AF34_w04(0xB) == found && D_80100F94_shared_board[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (func_8010AF34_w04(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(D_8011DDAC_w04[D_8011C688_w04]) == 0 && GwPlayer[loc->current_player_index].coin >= D_80100F94_shared_board[1]) {
        s32 route = func_8010AF34_w04(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(D_8011DDB4_w04[D_8011C688_w04]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = D_8011DCEC_w04[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = func_8010AF34_w04(val);
            if (found == -1) {
                continue;
            }
            if (D_80100F94_shared_board[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(D_8011DD8C_w04[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = func_8010AF34_w04(0);
    if (found != -1) {
        return found + 1;
    }
    D_8011DC68_w04 = 1;
    return func_8010AFBC_w04() + 2;
}

s32 func_8011B6B4_w04(void) {
    if (D_8011DC68_w04 != 0) {
        D_8011DC68_w04 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011DDBC_w04[D_8011C688_w04]) + 1;
}
