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
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/EC3B0.h"

void func_80105DB0_w03(void);
void func_80107D54_w03(s16 arg0);
void func_80107ECC_w03(void);
void func_801061A0_w03(UnkMBGuideData *);
void func_801066CC_w03(void);
void func_80108734_w03(void);
s32 func_8011BD24_w03(void);
void func_8010DF54_w03(void);
void func_8010F3D4_w03(void);
void func_8010F79C_w03(void);
void func_8010F808_w03(void);
void func_80117D38_w03(void);
void func_80110A14_w03(void);
void func_80110CA0_w03(void);
void func_8010FCFC_w03(void);
void func_8011026C_w03(void);
void func_801105B8_w03(void);
void func_80117034_w03(void);
void func_801178B4_w03(void);
void func_801110F0_w03(void);
void func_801113B0_w03(void);
void func_80111750_w03(void);
void func_8011214C_w03(void);
void func_80112CA4_w03(void);
void func_801139BC_w03(void);
void func_80114C58_w03(void);
void func_80115C58_w03(void);
void func_80116E84_w03(void);
void func_8011777C_w03(void);
s32 func_8011B71C_w03(void);
void func_80107F30_w03(void);
void func_80108118_w03(void);
void func_801083DC_w03(void);
void func_801085B0_w03(void);
void func_80108820_w03(void);
void func_801088A0_w03(void);
void func_80116B78_w03(void);
void func_8011908C_w03(void);
void func_8011655C_w03(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees);
s32 func_8011C088_w03(void);
extern s16 D_8011C110_w03[];
extern s16 D_8011C120_w03[];
extern s16 D_8011C130_w03[];
extern s16 D_8011C140_w03[];
extern s16 D_8011C150_w03[];
extern s16 D_8011C164_w03[];
extern s16 D_8011C16C_w03[];
extern s32 D_8011C160_w03;
extern s16 D_8011C180_w03[][2];
extern s16 D_8011C1A8_w03[][2];
extern s16 D_8011C1B0_w03[][2];
extern s16 D_8011C1C8_w03[];
extern s16 D_8011C1D8_w03[];
extern s32 D_8011C2E4_w03[];
extern s32 D_8011C308_w03[];
extern s16 D_8011C350_w03[];
extern s16 D_8011C368_w03[];
extern s16 D_8011C378_w03[];
extern s16 D_8011C388_w03[];
extern s16 D_8011C398_w03[];
extern s16 D_8011C3A8_w03[];
extern s16 D_8011C3B8_w03[];
extern s16 D_8011C3C8_w03[];
extern DecisionTreeNonLeafNode *D_8011CABC_w03[];
extern s16 D_8011CDF0_w03[];
extern s16 D_8011CDF8_w03[];
extern s16 D_8011CE00_w03[];
extern s16 D_8011CE08_w03[];
extern s16 D_8011CB20_w03[][3];
extern BranchPair D_8011CB34_w03[];
extern s16 D_8011CB68_w03[][3];
extern BranchPair D_8011CB7C_w03[];
extern s16 D_8011CBB0_w03[][3];
extern BranchPair D_8011CBC4_w03[];
extern s16 D_8011CBF8_w03[][3];
extern BranchPair D_8011CC0C_w03[];
extern s16 D_8011CC40_w03[][3];
extern BranchPair D_8011CC54_w03[];
extern s16 D_8011CC88_w03[][3];
extern BranchPair D_8011CC9C_w03[];
extern s16 D_8011CCD0_w03[][3];
extern BranchPair D_8011CCE4_w03[];
extern s16 D_8011CD18_w03[][3];
extern BranchPair D_8011CD2C_w03[];
extern s16 D_8011CD60_w03[][3];
extern BranchPair D_8011CD74_w03[];
extern s16 D_8011CDA8_w03[][3];
extern BranchPair D_8011CDBC_w03[];
extern DecisionTreeNonLeafNode *D_8011C4C8_w03[];
extern DecisionTreeNonLeafNode *D_8011C528_w03[];
extern DecisionTreeNonLeafNode *D_8011C5F4_w03[];
extern DecisionTreeNonLeafNode *D_8011C6D8_w03[];
extern DecisionTreeNonLeafNode *D_8011C774_w03[];
extern DecisionTreeNonLeafNode *D_8011C804_w03[];
extern DecisionTreeNonLeafNode *D_8011C864_w03[];
extern DecisionTreeNonLeafNode *D_8011C8D0_w03[];
extern DecisionTreeNonLeafNode *D_8011C924_w03[];
extern s16 D_8011CAD8_w03[][3];
extern BranchPair D_8011CAEC_w03[];
extern s16 D_8011C354_w03[];
extern s16 D_8011C358_w03[];
extern s8 D_8011CF98_w03[][5][7];
extern Object *D_8011EAC0_w03;
extern Object *D_8011EAC8_w03[];
extern Process *D_8011EAE8_w03[8];
extern Process *D_8011EB08_w03;
extern Object *D_8011EB0C_w03;
extern Unk3 *D_8011EB10_w03;
extern Unk3 *D_8011EB14_w03;
extern Unk3 *D_8011EB18_w03;
extern Unk3 *D_8011EB1C_w03;
extern Unk3 *D_8011EB20_w03;
extern s32 D_8011EB24_w03;
extern s32 D_8011EB28_w03;
extern Object *D_8011EB54_w03;
extern Object *D_8011EB58_w03[1];
extern Object *D_8011EB5C_w03;
extern Object *D_8011EB60_w03[10];
extern Object *D_8011EB88_w03;
extern Object *D_8011EB8C_w03[2];
extern s16 D_8011C1A0_w03[][2];
extern s16 D_8011C1B8_w03[][2];
extern s16 D_8011C1C0_w03[][2];
extern s16 D_8011C1E8_w03[];
extern s16 D_8011C1EC_w03[];
extern Vec D_8011C1F0_w03[];
extern Vec D_8011C22C_w03[];
extern s16 D_8011C268_w03[];
extern s16 D_8011C26C_w03[];
extern u32 *D_8011C2A8_w03[];
extern s32 D_8011C2C0_w03[];
extern s32 D_8011C32C_w03[];
extern s32 D_8011EB94_w03;
extern s32 D_8011EB98_w03;
extern u8 *D_8011EB9C_w03;
extern Object *D_8011EBE0_w03[4];
extern omObjData *D_8011EBF0_w03[4];
extern s32 D_8011D0D0_w03;
extern s32 D_8011E7A8_w03;
extern DecisionTreeNonLeafNode *D_8011E8FC_w03[];

extern Object *D_8011EBA0_w03;
extern Object *D_8011EBB0_w03;
extern DecisionTreeNonLeafNode D_8011DB30_w03[];
extern DecisionTreeNonLeafNode D_8011DB9C_w03[];
extern DecisionTreeNonLeafNode D_8011DDD0_w03[];
extern DecisionTreeNonLeafNode D_8011DF68_w03[];
extern DecisionTreeNonLeafNode D_8011E184_w03[];
extern DecisionTreeNonLeafNode D_8011E568_w03[];
extern DecisionTreeNonLeafNode D_8011E6B8_w03[];
extern s32 D_8011EBB8_w03;
extern s32 D_8011EBBC_w03;
extern s32 D_8011EC00_w03;
extern s32 D_8011EC04_w03;
s32 func_8011B470_w03(void);
s32 func_8011B51C_w03(void);
extern u8 *D_8011E82C_w03[];
extern s8 *D_8011E8CC_w03[];
extern DecisionTreeNonLeafNode *D_8011E8EC_w03[];
extern DecisionTreeNonLeafNode *D_8011E8F4_w03[];
extern Object *D_8011EBB4_w03;
extern Object *D_8011EBD8_w03;
extern s32 D_8011D388_w03;
extern Object *D_8011EBC0_w03;
s16 func_801059D0_w03(void) {
    return D_8011C150_w03[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]];
}

void func_801059F8_w03(void) {
    s32 i;
    s32 idx1;
    s32 idx2;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 0x3C; i++) {
        idx1 = rand8() & 7;
        idx2 = rand8() & 7;

        if (idx1 != idx2) {
            if (idx1 < D_8011C120_w03[idx2]) {
                continue;
            }
            if (idx2 < D_8011C120_w03[idx1]) {
                continue;
            }
            {
                s32 temp = D_8011C110_w03[idx1];
                D_8011C110_w03[idx1] = D_8011C110_w03[idx2];
                D_8011C110_w03[idx2] = temp;
                temp = D_8011C120_w03[idx1];
                D_8011C120_w03[idx1] = D_8011C120_w03[idx2];
                D_8011C120_w03[idx2] = temp;
            }
        }
    }

    for (i = 0; i < 8; i++) {
        loc->star_spawn_indices[i] = D_8011C110_w03[i];
    }

    do {
        GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f) + 1];
    } while (GwSystem.boardData.halfWordBytes[0] == 7);
    GWBoardFlagClear(0x12);
}

void func_80105B44_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_SYSTEM *system = &GwSystem;
    s32 sp7;
    s32 sp0;

    system->current_star_spawn++;
    if (system->current_star_spawn >= 8) {
        sp7 = system->star_spawn_indices[7];
        system->current_star_spawn = 0;
        GWBoardFlagSet(4);
        func_801059F8_w03();
        sp0 = system->star_spawn_indices[0];
        if ((sp7 ^ sp0) == 0) {
            system->star_spawn_indices[0] = system->star_spawn_indices[7];
            system->star_spawn_indices[7] = sp0;
        }
    }

    if (loc->current_star_spawn >= 7) {
        GwSystem.boardData.halfWordBytes[0] = loc->star_spawn_indices[MBRand(6.0f)];
    } else {
        GwSystem.boardData.halfWordBytes[0] =
            loc->star_spawn_indices[MBRand(7 - loc->current_star_spawn) + loc->current_star_spawn + 1];
    }
    GWBoardFlagClear(0x12);
}

void func_80105C50_w03(void) {
    s32 i;
    GW_SYSTEM *loc = &GwSystem;

    for (i = 0; i < 8; i++) {
        GWBoardFlagSet(D_8011C130_w03[i]);
    }
    MBMasuTypeSet(D_8011C140_w03[loc->star_spawn_indices[loc->current_star_spawn]], 0xE);
    GWBoardFlagClear(D_8011C130_w03[loc->star_spawn_indices[loc->current_star_spawn]]);
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        MBMasuTypeSet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]], 0xE);
    }
}

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

void func_80105DB0_w03(void) {
    SpaceData *space = HuPrcCurrentGet()->user_data;
    Object *model;
    s32 obj;
    f32 scale;
    f32 angle;
    s32 i;

    HuAudFXPlay(0x11B);
    D_8011EB0C_w03 = MBModelCreate(0x3A, NULL);
    model = D_8011EB0C_w03;
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
    D_8011EB08_w03 = 0;
    omDelPrcObj(NULL);
}

void func_801061A0_w03(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    HuPrcSleep(3);
    while (obj->velocity.z != 0.0f) {
        HuPrcVSleep();
    }
}

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
    winData[guide->amount].stat = HUWIN_STAT_DRAWMES;
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
    winData[guide->amount].stat = HUWIN_STAT_DRAWMES;
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

void func_801066CC_w03(void) {
    Object *playerModel = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Object *model;
    Vec camPos;
    f32 scale;
    f32 angle;
    s32 obj;
    s32 i;

    HuAudFXPlay(0x11B);
    model = MBModelCreate(0x1A, NULL);
    model->flags |= 4;
    func_800ECC54_shared_board(model);
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8E) {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 15.0f;
    } else {
        HuVecCopyXYZ(&model->coords, playerModel->coords.x, playerModel->coords.y + 10.0f, playerModel->coords.z + 30.0f);
        HuVecCopyXYZ(&camPos, gCameraList->pos.x, gCameraList->pos.y, gCameraList->pos.z);
        model->velocity.x = 35.0f;
    }

    obj = func_8000CED8_main(0xB0004, 0xAA9);
    func_8000CD00_main(obj, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(obj, 15.0f);
    Hu3DModelCameraSet(obj, HU3D_CAM0);
    func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);

    scale = 0.0f;
    for (i = 0; i < 6; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale += 0.5f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    for (i = 0; i < 3; i++) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        scale -= 0.4f;
        func_8000D018_main(obj, scale * 15.0f);
        HuPrcVSleep();
    }

    func_8000D018_main(obj, scale * 15.0f);
    HuPrcSleep(20);
    HuAudFXPlay(0x132);

    angle = 0.0f;
    HuVecCopyXYZ(&camPos, player->player_obj->coords.x, player->player_obj->coords.y - 10.0f, player->player_obj->coords.z);
    MBPlayerPosMoveCreate(&model->coords, &camPos, &model->coords, 40);

    for (i = 0; i < 40; i++) {
        func_8008A2A0_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        scale -= 0.05f;
        if (scale < 0.0f) {
            scale = 0.0f;
        }
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8000D018_main(obj, scale * 15.0f);
        func_8000CFA4_main(obj, model->coords.x, model->coords.y + model->velocity.x, model->coords.z);
        HuPrcVSleep();
    }

    MBModelKill(model);
    func_8000D044_main(obj);
    MBVecForwardSet(&player->player_obj->rot);
    MBPlayerVibrate(-1, 5);
    if (D_8011C160_w03 != 0) {
        func_8004A670_main(0xE);
    } else {
        HuAudSeqPlay(0x6F);
    }

    GwPlayer[GwSystem.current_player_index].star += 1;
    if (GwPlayer[GwSystem.current_player_index].star >= 100) {
        GwPlayer[GwSystem.current_player_index].star = 99;
    }

    MBPlayerMotionSet(-1, 6, 0);
    PlayerFXPlay(0x262, GwSystem.current_player_index);
    if (D_8011C160_w03 != 0) {
        HuPrcSleep(16);
        func_80003A70_main(D_800CDBC8_main);
        func_8004A918_main(0x6F);
        func_8004A880_main(0);
        HuPrcSleep(110);
        func_80003B70_main(D_800CDBC8_main, 0);
        func_8004A72C_main(0xF);
    } else {
        HuPrcSleep(60);
    }
    omDelPrcObj(NULL);
}

void func_80106C2C_w03(Object *arg) {
    Process *prc;

    mbItemBtnF = 0;
    prc = omAddPrcObj(func_801066CC_w03, 0x4800, 0, 0);
    prc->user_data = arg;
    HuPrcChildLink(HuPrcCurrentGet(), prc);
    HuPrcChildWatch();
    mbItemBtnF = 1;
}

void func_80106CA0_w03(void) {
    mbCameraBtnF = 1;
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    omPrcResetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    mbCameraBtnF = 0;
    mbItemBtnF = 1;
}

void func_80106D28_w03(void) {
    mbItemBtnF = 0;
    omPrcSetStatBit(HuPrcCurrentGet(), OM_STAT_NOALLPAUSE);
    MBMapScrollExec(GwPlayer[GwSystem.current_player_index].pad);
    mbItemBtnF = 1;
}

void func_80106D84_w03(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    D_8011EB10_w03 = func_800E210C_shared_board(0, 0x92, 1);
    D_8011EB14_w03 = func_800E210C_shared_board(1, 0xA0, 1);
    D_8011EB20_w03 = func_800E210C_shared_board(0xD, 0xAE, 1);
    D_8011EB18_w03 = func_800E210C_shared_board(3, 0xBC, 1);
    D_8011EB1C_w03 = func_800E210C_shared_board(0xB, 0xCA, 1);
    HuPrcSleep(3);
    mbCameraBtnF = 1;
    D_800D51F8_main = 1;
}

void func_80106E54_w03(void) {
    mbCameraBtnF = 0;
    D_800D51F8_main = 0;
    MBHelpWinKill(D_8011EB10_w03);
    MBHelpWinKill(D_8011EB14_w03);
    MBHelpWinKill(D_8011EB20_w03);
    MBHelpWinKill(D_8011EB18_w03);
    MBHelpWinKill(D_8011EB1C_w03);
}

const u8 D_8011E910_w03[4] = { 1, 2, 4, 8 };

s32 func_80106EB4_w03(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011BD24_w03();
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < 9; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 0);
        if (i == -1) {
            return -1;
        }
    } while (arg0[i] == 0);
    return i;
}

s32 func_80107148_w03(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011C088_w03();
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void func_80107360_w03(void) {
    s32 i;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i != 4) {
        if (GwPlayer[cur].coin >= 50) {
            if (MBRand(100.0f) < GwPlayer[cur].coin + 10) {
                D_8011EB24_w03 = 1;
                if (GwPlayer[cur].star < 99) {
                    return;
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        if (i != cur && GwPlayer[i].coin >= 5) {
            break;
        }
    }
    if (i != 4) {
        D_8011EB24_w03 = 0;
    } else {
        D_8011EB24_w03 = 2;
    }
}

void func_80107490_w03(void) {
    s32 order[4];
    s32 i;
    s32 j;
    s32 cur = GwSystem.current_player_index;

    for (i = 0; i < 4; i++) {
        order[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        j = MBPlayerStealRankGet(i);
        while (1) {
            if (order[j] == -1) {
                break;
            }
            j++;
        }
        order[j] = i;
    }
    func_80107360_w03();
    if (D_8011EB24_w03 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    } else if (D_8011EB24_w03 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_8011EB28_w03 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_8011EB24_w03 = 2;
    }
}

s32 func_80107628_w03(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_80107490_w03();
                    var_s2 = D_8011EB24_w03 + 1;
                } else {
                    var_s2 = D_8011EB28_w03 + 1;
                }
                sp18[GwPlayer[GwSystem.current_player_index].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    while (1) {
        i = HuWinChoiceGet(mbDlgWinId, i, arg2);
        if (arg2 == 0) {
            if (i == -1) {
                return -1;
            }
        }
        if (arg0[i] != 0) {
            return i;
        }
    }
}

s32 func_801078F4_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 0, 1);
}

s32 func_80107914_w03(u8 *arg0) {
    return func_80107628_w03(arg0, 1, 0);
}

// entrypoint 0
void func_80107934_w03(void) {
    GwSystem.current_board_index = 2;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

// entrypoint 1
void func_80107970_w03(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w03();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[2] = 0;
    omOvlReturnEx(1);
}

void func_80107A04_w03(void) {
    s32 i;

    omInitObjMan(0xA0, 0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightColorSet(2, 0xC8, 0xC8, 0xC8);
    MBObjectSetup(9, 0x23C, 0xB, 0);
    MBMasuBlockTblExtSet(D_8011C164_w03);
    MBMasuBlockTblSet(D_8011C16C_w03);
    MBItemHookSet(0, &func_8010DF54_w03);
    MBItemHookSet(1, &func_8010F3D4_w03);
    MBItemHookSet(9, &func_8010F79C_w03);
    MBItemHookSet(2, &func_8010F808_w03);
    MBItemHookSet(3, &func_80117D38_w03);
    MBItemHookSet(4, &func_80110A14_w03);
    MBItemHookSet(5, &func_80110CA0_w03);
    MBItemHookSet(6, &func_8010FCFC_w03);
    MBItemHookSet(7, &func_8011026C_w03);
    MBItemHookSet(8, &func_801105B8_w03);
    MBItemHookSet(0xA, &func_80117034_w03);
    MBItemHookSet(0xB, &func_801178B4_w03);
    MBItemHookSet(0xE, &func_801110F0_w03);
    MBItemHookSet(0xF, &func_801113B0_w03);
    MBItemHookSet(0x10, &func_80111750_w03);
    MBItemHookSet(0x11, &func_8011214C_w03);
    MBItemHookSet(0x12, &func_80112CA4_w03);
    MBItemHookSet(0x13, &func_801139BC_w03);
    MBItemHookSet(0x14, &func_80114C58_w03);
    MBItemHookSet(0x15, &func_80115C58_w03);
    MBItemHookSet(0xC, &func_80116E84_w03);
    MBItemHookSet(0xD, &func_8011777C_w03);
    MBComItemDecideHookSet(func_8011B71C_w03);

    for (i = 0; i < 8; i++) {
        MBMasuStarSet(i, D_8011C150_w03[i]);
    }

    if (GWBoardFlagCheck(0xE) != 0) {
        GWBoardFlagClear(0xE);
        func_80105B44_w03();
    }

    func_80105C50_w03();
    func_80107F30_w03();
    func_80108118_w03();
    func_801083DC_w03();
    func_801085B0_w03();
    func_80108820_w03();
    func_801088A0_w03();
    func_80116B78_w03();
    func_800EBDAC_shared_board();
    omAddPrcObj(func_8011908C_w03, 0x4800, 0, 0);
}

// entrypoint 2
void func_80107CA4_w03(void) {
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
void func_80107D28_w03(void) {
    Hu3DCamInit(1);
    func_80107A04_w03();
    MBStart(1);
}

void func_80107D54_w03(s16 arg0) {
    Object *obj;

    if (D_8011EAC8_w03[arg0] != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001F9E4_main(obj->omObj1->model[0], 0xFF);
    func_8001FA68_main(obj->omObj2->model[0]);
    func_8001F9E4_main(obj->omObj2->model[0], 0xFF);
    func_800461B4_main(obj->omObj1->model[0]);
    if (D_8011EAC0_w03 == NULL) {
        D_8011EAC0_w03 = obj;
    }
    D_8011EAC8_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8011EAE8_w03[arg0] = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1C8_w03[arg0])->coords);
    GwSystem.boardData.halfWordBytes[1] =
        func_800D771C_shared_board(0xB, obj, D_8011C180_w03[arg0][0], D_8011C180_w03[arg0][1]);
}

void func_80107ECC_w03(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        if (D_8011EAE8_w03[i] != NULL) {
            omDelPrcObj(D_8011EAE8_w03[i]);
            D_8011EAE8_w03[i] = NULL;
        }
    }
}

void func_80107F30_w03(void) {
    s32 i;

    D_8011EAC0_w03 = NULL;
    for (i = 0; i < 8; i++) {
        D_8011EAC8_w03[i] = NULL;
        D_8011EAE8_w03[i] = NULL;
        MBKinokoEffKillHookSet(func_80107ECC_w03);
        if (!GWBoardFlagCheck(D_8011C1D8_w03[i])) {
            func_80107D54_w03(i);
        }
    }
    if (GwSystem.boardData.halfWordBytes[0] != -1) {
        func_80107D54_w03(GwSystem.boardData.halfWordBytes[0]);
    }
}

void func_80107FF8_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB58_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB54_w03 == NULL) {
        obj = MBModelCreate(0xA, NULL);
        func_8001FA68_main(obj->omObj1->model[0]);
        func_8001FA68_main(obj->omObj2->model[0]);
        D_8011EB54_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB54_w03);
    }
    MBModelDispOff(obj);
    D_8011EB58_w03[arg0] = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1E8_w03[arg0])->coords);
    func_800D771C_shared_board(0xA, obj, D_8011C1A0_w03[arg0][0], D_8011C1A0_w03[arg0][1]);
}

void func_80108118_w03(void) {
    s32 i;

    D_8011EB54_w03 = 0;
    for (i = 0; i <= 0; i++) {
        D_8011EB58_w03[i] = NULL;
        func_80107FF8_w03(i);
    }
}

void func_80108174_w03(void) {
    s32 i;
    s32 j;
    s32 count;

    for (i = 0; i < 2; i++) {
        count = (GwSystem.bank_coins + 9) / 10;
        if (count > 5) {
            count = 5;
        }
        for (j = 0; j < count; j++) {
            MBModelDispOn(D_8011EB60_w03[i * 5 + j]);
        }
        for (; j < 5; j++) {
            MBModelDispOff(D_8011EB60_w03[i * 5 + j]);
        }
    }
}

void func_80108270_w03(s16 arg0) {
    Object *obj;

    if (D_8011EB60_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB5C_w03 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8011EB5C_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB5C_w03);
    }
    D_8011EB60_w03[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C1EC_w03[arg0 / 5])->coords);
    HuVecAdd(&obj->coords, &D_8011C1F0_w03[arg0 % 5], &obj->coords);
    obj->omObj1->rot.x = D_8011C22C_w03[arg0 % 5].x;
    obj->omObj1->rot.z = D_8011C22C_w03[arg0 % 5].z;
    MBModelDispOff(obj);
}

void func_801083DC_w03(void) {
    s32 i;

    D_8011EB5C_w03 = 0;
    for (i = 0; i < 0xA; i++) {
        D_8011EB60_w03[i] = NULL;
        func_80108270_w03(i);
    }
    func_80108174_w03();
}

void func_80108444_w03(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011EB8C_w03[arg0] != NULL) {
        return;
    }
    if (D_8011EB88_w03 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011C26C_w03[board], D_8011C2A8_w03[board]);
        MBModelTempAllocFree(obj);
        D_8011EB88_w03 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011EB88_w03);
    }
    D_8011EB8C_w03[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011C268_w03[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011C1C0_w03[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011C1C0_w03[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011C1B8_w03[arg0][0], D_8011C1B8_w03[arg0][1]);
}

void func_801085B0_w03(void) {
    s32 i;

    D_8011EB88_w03 = 0;
    for (i = 0; i < 2; i++) {
        D_8011EB8C_w03[i] = NULL;
        func_80108444_w03(i);
    }
}

void func_80108610_w03(void) {
    HuPrcSleep(D_8011C308_w03[GwSystem.current_board_index]);
    HuAudFXPlay((s16)D_8011C2E4_w03[GwSystem.current_board_index]);
    omDelPrcObj(NULL);
}

void func_8010866C_w03(s32 arg0, s32 arg1) {
    MBMotionSet(D_8011EB8C_w03[arg0], arg1 - 1, 0);
    func_8001C814_main(D_8011EB8C_w03[arg0]->omObj1->model[0], 5, 0);
    if (D_8011C2C0_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C2C0_w03[GwSystem.current_board_index]);
    }

    if (D_8011C2E4_w03[GwSystem.current_board_index] != -1) {
        omAddPrcObj(func_80108610_w03, 0x1000, 0, 0);
    }
}

void func_80108734_w03(void) {
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
    func_8001C814_main(D_8011EB8C_w03[index]->omObj1->model[0], 1, 4);

    if (D_8011C32C_w03[GwSystem.current_board_index] != -1) {
        HuAudFXPlay(D_8011C32C_w03[GwSystem.current_board_index]);
    }

    omDelPrcObj(NULL);
}

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

s32 func_801089AC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 *list;

    switch (MBMasuLinkMasuIdGet(player->clink, player->cidx)) {
        case 0x79:
            list = D_8011C368_w03;
            break;
        case 0x84:
            list = D_8011C378_w03;
            break;
        case 0x89:
            list = D_8011C388_w03;
            break;
        case 0x8A:
            list = D_8011C398_w03;
            break;
        case 0x8B:
            list = D_8011C3A8_w03;
            break;
        case 0x6F:
            list = D_8011C3B8_w03;
            break;
        default:
            list = D_8011C3C8_w03;
            break;
    }

    if (func_80108918_w03(list)) {
        GwSystem.boardData.halfWordBytes[2] |= 1 << GwSystem.current_player_index;
    } else {
        GwSystem.boardData.halfWordBytes[2] &= ~(1 << GwSystem.current_player_index);
    }
    return 0;
}

void func_80108AB8_w03(void) {
    MBMoveNextMasuSet(-1, 1, 7);
}

void func_80108ADC_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x6D) {
        if (player->rev & 0x80) {
            if (mbWalkNum != 0) {
                func_8011655C_w03(D_8011CAD8_w03, D_8011CAEC_w03, D_8011CABC_w03);
            } else {
                MBMoveBackMasuSet(-1, 1, 8);
            }
        } else {
            MBMoveBackMasuSet(-1, 1, 6);
        }
    }
}

void func_80108B98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x41 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 2, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03(D_8011CB20_w03, D_8011CB34_w03, D_8011C4C8_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108C48_w03(void) {
    func_8011655C_w03(D_8011CB68_w03, D_8011CB7C_w03, D_8011C528_w03);
    omDelPrcObj(NULL);
}

void func_80108C80_w03(void) {
    func_8011655C_w03(D_8011CBB0_w03, D_8011CBC4_w03, D_8011C5F4_w03);
    omDelPrcObj(NULL);
}

void func_80108CB8_w03(void) {
    func_8011655C_w03(D_8011CBF8_w03, D_8011CC0C_w03, D_8011C6D8_w03);
    omDelPrcObj(NULL);
}

void func_80108CF0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x32 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 9, 0);
        player->rev &= ~1;
    } else {
        func_8011655C_w03(D_8011CC40_w03, D_8011CC54_w03, D_8011C774_w03);
    }
    omDelPrcObj(NULL);
}

void func_80108DA0_w03(void) {
    func_8011655C_w03(D_8011CC88_w03, D_8011CC9C_w03, D_8011C804_w03);
    omDelPrcObj(NULL);
}

void func_80108DD8_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03(D_8011CCD0_w03, D_8011CCE4_w03, D_8011C864_w03);
    }
}

void func_80108E30_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03(D_8011CD18_w03, D_8011CD2C_w03, D_8011C864_w03);
    }
}

void func_80108E88_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03(D_8011CD60_w03, D_8011CD74_w03, D_8011C8D0_w03);
    }
}

void func_80108EE0_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        func_8011655C_w03(D_8011CDA8_w03, D_8011CDBC_w03, D_8011C924_w03);
    }
}

void func_80108F38_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    UnkEA790Struct *win;
    s32 sel;
    s32 comChoice;
    s32 count;
    s32 i;

    if ((player->rev & 0x80) && mbWalkNum != 0) {
        MBPlayerMotionSet(-1, -1, 2);
        HuPrcVSleep();
        func_80106D84_w03();
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF0_w03);
                comChoice = MBRand(3.0f);
                break;
            case 0x46:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CDF8_w03);
                comChoice = 2;
                break;
            case 0x45:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE00_w03);
                comChoice = MBRand(3.0f);
                break;
            default:
                win = func_800D76A0_shared_board(GwSystem.current_player_index, D_8011CE08_w03);
                comChoice = MBRand(3.0f);
                break;
        }
        func_800D742C_shared_board(win, GwSystem.current_player_index, 0);
        if (MBPlayerComCheck(-1)) {
            count = comChoice;
            for (i = 0; i < count; i++) {
                func_800D7250_shared_board(win, -2);
            }
            func_800D7250_shared_board(win, -4);
        }
        sel = func_800D7518_shared_board(win);
        func_800D6CA0_shared_board(win);
        func_80106E54_w03();
        switch (MBMasuLinkMasuIdGet(player->blink, player->bidx)) {
            case 0x62:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x46:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            case 0x45:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 12, 1);
                        player->rev |= 1;
                        break;
                }
                break;
            default:
                switch (sel) {
                    case 0:
                        MBMoveNextMasuSet(-1, 9, 5);
                        player->rev |= 1;
                        break;
                    case 1:
                        MBMoveNextMasuSet(-1, 9, 7);
                        player->rev &= ~1;
                        break;
                    default:
                        MBMoveNextMasuSet(-1, 10, 6);
                        player->rev |= 1;
                        break;
                }
                break;
        }
    }
}

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

s32 func_801098C8_w03(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1;
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void func_80109AD8_w03(void) {
    s32 moveOn = TRUE;
    GW_SYSTEM *sys = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 masu = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    s32 choice;
    UnkVibrateProcess *vibrate;

    if ((masu == 0x74 || masu == 0x8C) && (player->rev & 1)) {
        goto end;
    }
    if ((masu == 0x75 || masu == 0x8D) && !(player->rev & 1)) {
        goto end;
    }

    MBPlayerMotionSet(-1, -1, 2);
    if (MBItemFind(sys->current_player_index, 1) != -1) {
        func_800DBEC0_shared_board(sys->current_player_index);
        switch (masu) {
            case 0x74:
            case 0x75:
                func_800ED20C_shared_board(-1, 8, 0x7D);
                break;
            default:
                func_800ED20C_shared_board(-1, 8, 0x7E);
                break;
        }
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        MBPlayerVibrate(-1, 1);
    retry:
        MBDlgWinCreate(0x38, 0x4103);
        choice = func_801098C8_w03(0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                MBDlgWinExec(0x38, 0x4104);
                GwPlayer[sys->current_player_index].itemNo[MBItemFind(sys->current_player_index, 1)] = -1;
                MBItemRemoveEmpty(GwSystem.current_player_index);
                MBStatusItemIconSprReinit(-1);
                switch (masu) {
                    case 0x74:
                        func_8010866C_w03(0, 0);
                        break;
                    case 0x75:
                        func_8010866C_w03(0, 1);
                        break;
                    case 0x8C:
                        func_8010866C_w03(1, 0);
                        break;
                    default:
                        func_8010866C_w03(1, 1);
                        break;
                }
                moveOn = FALSE;
                vibrate = MBPlayerVibrateObjCreate(-1, 2, 5);
                HuPrcSleep(20);
                MBPlayerVibrateObjKill(vibrate);
                break;
            case 1:
                MBDlgWinExec(0x38, 0x4105);
                break;
            case 2:
                func_80106CA0_w03();
                goto retry;
        }
        func_800DB884_shared_board(sys->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    } else {
        MBDlgWinExec(-1, 0x4106);
    }

    if (moveOn) {
        switch (masu) {
            case 0x74:
                MBMoveNextMasuSet(-1, 10, 1);
                player->rev |= 1;
                break;
            case 0x75:
                MBMoveNextMasuSet(-1, 10, 5);
                player->rev &= ~1;
                break;
            case 0x8C:
                MBMoveNextMasuSet(-1, 11, 2);
                player->rev |= 1;
                break;
            default:
                MBMoveNextMasuSet(-1, 11, 6);
                player->rev &= ~1;
                break;
        }
    }

end:
    omDelPrcObj(NULL);
}

void func_80109E90_w03(void) {
}

void func_80109E98_w03(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (MBMasuLinkMasuIdGet(player->clink, player->cidx) == 2 &&
        MBMasuLinkMasuIdGet(player->blink, player->bidx) == 0x63) {
        MBMoveNextMasuSet(-1, 9, 6);
    }
}

void func_80109F3C_w03(void) {
}

s32 func_80109F44_w03(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                switch (arg0) {
                    case 0:
                        var_s2 = func_800EF0D8_shared_board(0) + 1;
                        break;
                    case 1:
                        var_s2 = func_800EF0D8_shared_board(1) + 1;
                        break;
                    case 2:
                        var_s2 = arg1 + 1;
                        break;
                    default:
                        var_s2 = MBComTreeExec((void *)arg0) + 1;
                        break;
                }
                sp18[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, sp20[GwPlayer[i].pad]);
                sp18[GwPlayer[i].pad] = -1;
            }
        } else {
            sp18[GwPlayer[i].pad] = 0;
        }
    }

    if (var_s2 != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; var_s2 != 0; j++) {
            if (--var_s2 == 0) {
                sp18[GwPlayer[GwSystem.current_player_index].pad] = -0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 5);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    return HuWinChoiceGet(mbDlgWinId, 0, 1);
}

void func_8010A1C8_w03(s16 arg0, s32 arg1, s16 arg2, s32 arg3) {
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

void func_8010A284_w03(void) {
    while (1) {
        MBStatusItemAttrSet(GwSystem.current_player_index, MBItemSelNoGet(), 0x8000);
        HuPrcVSleep();
    }
}

void func_8010A2C4_w03(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;
    Object *star;
    s32 alpha;
    SpaceData *space;
    f32 scale;
    f32 origScale;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105D20_w03(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w03());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuPrcSleep(20);
        HuAudFXPlay(0x159);

        if (GwPlayer[loc->current_player_index].itemTurn != 0) {
            MBDlgWinInsertCreate(0x16, 0x4805, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
        }

        if (GwPlayer[loc->current_player_index].star >= 99) {
            MBDlgWinExec(0x16, 0x4804);
        } else {
            if (GwPlayer[loc->current_player_index].coin >= 20) {
            purchaseMenu:
                MBDlgWinInsertCreate(0x16, 0x4800, GwPlayer[loc->current_player_index].chr + 0x1C00, 0, 0, 0, 0);
                choice = func_80109F44_w03(2, 0);
                MBDlgWinClose();
                MBDlgWinKill();

                switch (choice) {
                    case 0:
                        MBCoinChangeCreate(loc->current_player_index, -20);
                        MBCoinTakeCreate(loc->current_player_index, -20);
                        HuPrcSleep(30);
                        MBDlgWinExec(0x16, 0x4802);
                        if (D_800A12D0_main != 0) {
                            HuAudSeqStop();
                            func_800039A4_main(D_800C9930_main, 60);
                            D_800C9930_main = -1;
                        } else {
                            HuAudSeqFadeOut(0x5A);
                        }
                        func_80106C2C_w03(D_8011EAC0_w03);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        goto end;
                    case 1:
                        if (D_800A12D0_main != 0) {
                            func_800039A4_main(D_800C9930_main, 60);
                            msmMusPlayDefault(D_800CE198_main);
                            func_8004A670_main(0);
                            func_8004A72C_main(0x5A);
                            D_800C9930_main = -1;
                        }
                        MBDlgWinExec(0x16, 0x4803);
                        func_800DB884_shared_board(loc->current_player_index);
                        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
                        HuPrcChildWatch();
                        goto end;
                    case 2:
                        func_80106CA0_w03();
                        goto purchaseMenu;
                    default:
                        goto end;
                }
            } else {
                MBDlgWinExec(0x16, 0x4801);
            }
        }

        if (D_800A12D0_main != 0) {
            func_800039A4_main(D_800C9930_main, 60);
            msmMusPlayDefault(D_800CE198_main);
            func_8004A670_main(0);
            func_8004A72C_main(0x5A);
            D_800C9930_main = -1;
        }

        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }

end:
    if (spaceIdx == 2) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, D_8011C150_w03[GwSystem.boardData.halfWordBytes[0]]);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
        HuPrcSleep(20);
        HuAudFXPlay(0x19C);

        star = D_8011EAC8_w03[GwSystem.boardData.halfWordBytes[0]];
        for (alpha = 0xFF; alpha > 0; alpha -= 10) {
            func_8001F9E4_main(star->omObj1->model[0], alpha);
            func_8001F9E4_main(star->omObj2->model[0], alpha);
            HuPrcVSleep();
        }
        MBModelDispOff(star);
        GWBoardFlagSet(0x12);
        func_800D7770_shared_board(GwSystem.boardData.halfWordBytes[1]);

        space = MBMasuGet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]]);
        origScale = space->rot.x;
        for (scale = origScale; scale > 0.0f; scale -= origScale / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, 0.0f, 0.0f, 0.0f);
        MBMasuTypeSet(D_8011C140_w03[GwSystem.boardData.halfWordBytes[0]], 1);
        func_800EBDAC_shared_board();
        for (; scale < origScale; scale += origScale / 10.0f) {
            HuVecCopyXYZ(&space->rot, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&space->rot, origScale, origScale, origScale);

        GwSystem.boardData.halfWordBytes[0] = -1;
        MBDlgResultWinExec(0x800);
        func_800DB884_shared_board(loc->current_player_index);
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }

    func_80109E98_w03();
}

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

void func_8010B55C_w03(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010B734_w03);

void func_8010C9EC_w03(Object *obj) {
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

void func_8010CA8C_w03(Object *obj) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CB2C_w03);

void func_8010CF74_w03(void) {
    func_800EC3E4_shared_board();
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010CF98_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E98C_w03);

void func_8010DDC4_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBA0_w03);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF18_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010DF54_w03);

void func_8010F128_w03(void) {
    func_801087E4_w03(0);
}

void func_8010F144_w03(void) {
    func_801087E4_w03(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010F160_w03);

void func_8010F2BC_w03(omObjData *arg0) {
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

void func_8010F9C8_w03(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FC2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FCFC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8010FF2C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801100FC_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011026C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801105B8_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011077C_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E998_w03);

INCLUDE_RODATA("asm/nonmatchings/overlays/w03/34E840", D_8011E9F8_w03);

void func_80110A14_w03(void) {
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitCreate();
    MBModelDispOff(D_801011FC_shared_board);
    D_801011FC_shared_board->omObj1->scale.x = 0.0f;
    D_801011FC_shared_board->omObj1->scale.y = 0.0f;
    D_801011FC_shared_board->omObj1->scale.z = 0.0f;
    MBPlayerVibrate(-1, 3);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOff(player->player_obj);
    MBModelDispOn(D_801011FC_shared_board);

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
    HuPrcSleep(20);
    PlayerFXPlay(0x274, GwSystem.current_player_index);
    MBKSuitMotionSet(5, 2);
    HuPrcSleep(40);
    MBKSuitMotionSet(-1, 2);
    MBDlgResultWinExec(0x3A14);
}

void func_80110CA0_w03(void) {
    Vec direction;
    GW_PLAYER *player;
    Object *model;
    f32 scale;
    f32 angle;

    player = MBPlayerGet(-1);
    MBKSuitMotionSet(-1, 2);
    MBVecForwardSet(&direction);
    func_800ED128_shared_board(&player->player_obj->rot, &direction, &player->player_obj->rot, 8);
    HuPrcSleep(8);
    HuAudFXPlay(0x143);

    model = MBModelCreate(0x22, NULL);
    func_8001C258_main(model->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(model->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(model->omObj1->model[0]);
    HuVecCopy3F(&model->coords, &player->player_obj->coords);

    angle = 0.0f;
    for (scale = 1.0f; scale < 10.0f; scale = (f32)((f64)scale + 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelDispOn(player->player_obj);
    MBKSuitKill();

    for (; scale >= 1.0f; scale = (f32)((f64)scale - 0.5)) {
        HuVecCopyXYZ(&model->scale, scale, scale, scale);
        func_8008A430_main(HmfModelData[model->omObj1->model[0]].mtx, angle);
        angle += 20.0f;
        HuPrcVSleep();
    }

    MBModelKill(model);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80110EE0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801110F0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801113B0_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80111750_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011214C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112694_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801128B0_w03);

void func_80112CA4_w03(void) {
    s32 i;

    HuPrcSleep(10);
    for (i = 1; i < 64; i++) {
        MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 255.0f - (i * 3.984f));
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(GwSystem.current_player_index, MBItemSelNoGet(), 0);
}

void func_80112D60_w03(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011EBB0_w03);
    f32 angle;

    HuVecCopy3F(&obj->coords, &src->coords);
    HuVecCopyXYZ(&obj->scale, 2.0f, 2.0f, 2.0f);
    obj->velocity.x = src->velocity.x + 10.0f;
    MBModelDispOn(obj);
    angle = MBRand(360.0f);
    while (1) {
        HuPrcVSleep();
        obj->velocity.x += 1.5;
        if (src->velocity.x + 35.0f <= obj->velocity.x) {
            break;
        }
        angle += 40.0f;
        func_8008A2A0_main(HmfModelData[obj->omObj1->model[0]].mtx, angle);
    }
    MBModelKill(obj);
    omDelPrcObj(NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80112EB4_w03);

void func_80112EF0_w03(void) {
    s32 *flag = HuPrcCurrentGet()->user_data;
    f32 angle = 0.0f;
    f32 scale = 1.0f;
    GW_SYSTEM *loc = &GwSystem;

    while (1) {
        D_8011EBB4_w03->rot.x = -sindf(angle);
        D_8011EBB4_w03->rot.z = cosdf(angle);
        angle += 30.0f;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        if (*flag != 0) {
            D_8011EBB4_w03->scale.z = scale;
            D_8011EBB4_w03->scale.y = scale;
            D_8011EBB4_w03->scale.x = scale;
            scale -= 0.1f;
            if (scale <= 0.0f) {
                break;
            }
        }
        HuPrcVSleep();
    }
    D_8011EBB4_w03->scale.x = D_8011EBB4_w03->scale.y = D_8011EBB4_w03->scale.z = 0.0f;
    GwPlayer[loc->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemIconSprReinit(loc->current_player_index);
    MBModelKill(D_8011EBB4_w03);
    omDelPrcObj(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80113080_w03);

s32 func_8011343C_w03(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)D_8011E910_w03;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = D_8011EBB8_w03 + 1;
                } else {
                    delay = D_8011EBBC_w03 + 1;
                }
                inputs[GwPlayer[i].pad] = 0x400;
            } else {
                HuWinActivePlayerSet(mbDlgWinId, buttons[GwPlayer[i].pad]);
                inputs[GwPlayer[i].pad] = -1;
            }
        } else {
            inputs[GwPlayer[i].pad] = 0;
        }
    }

    if (delay != 0) {
        func_8005B63C_main(mbDlgWinId, HUWIN_ATTR_COMKEY, HUWIN_ATTR_COMKEY);
        for (j = 0; delay != 0; j++) {
            if (--delay == 0) {
                inputs[GwPlayer[GwSystem.current_player_index].pad] = 0x8000;
            }
            if (j == 0) {
                HuWinComKeyWait(inputs[0], inputs[1], inputs[2], inputs[3],
                                func_800EDC40_shared_board());
            } else {
                HuWinComKeyWait(inputs[0], inputs[1], inputs[2], inputs[3], 5);
            }
        }
    } else {
        HuWinComKeySet(inputs[0], inputs[1], inputs[2], inputs[3]);
    }

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (arg0[i] == 0) {
            HuWinChoiceDisable(mbDlgWinId, i);
        }
    }

    i = 0;
    do {
        i = HuWinChoiceGet(mbDlgWinId, i, 1);
    } while (arg0[i] == 0);
    return i;
}

void func_801136D4_w03(void) {
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

void func_801137E0_w03(void) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_801139BC_w03);

void func_80114668_w03(void) {
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

void func_80114728_w03(void) {
    s32 *processFlag = HuPrcCurrentGet()->user_data;
    Object *gameGuyModel = D_8011EBC0_w03;
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
        if (D_8011D388_w03 != -1) {
            HuVecCopy3F(&gameGuyModel->coords,
                        &MBPlayerGet(D_8011D388_w03)->player_obj->coords);
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
    process = omAddPrcObj(func_80114668_w03, 0x4800, 0, 0x40);
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80114C58_w03);

void func_80115564_w03(s32 arg0, s32 arg1, f32 *arg2) {
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

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011569C_w03);

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_8011580C_w03);

void func_801159D4_w03(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    Object *model;
    f32 scale;
    f32 angle;
    f32 wait_angle_step;

    HuAudFXPlay(0x143);
    model = D_8011EBD8_w03;
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

void func_80116830_w03(omObjData *obj) {
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
        Object *effectObj = D_8011EBE0_w03[playerIdx];

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

void func_80116ADC_w03(s32 arg) {
    D_8011EBF0_w03[arg] = omAddObj(0x3FFF, 0, 0, -1, func_80116830_w03);
    D_8011EBF0_w03[arg]->work[0] = arg;
    D_8011EBF0_w03[arg]->work[1] = 0;
    D_8011EBF0_w03[arg]->work[2] = 0;
    D_8011EBF0_w03[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011EBF0_w03[arg]->trans.x = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/w03/34E840", func_80116B78_w03);

void func_80116C78_w03(void) {
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
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 8) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xD5;
    }
}

void func_80116E84_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

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

void func_801175AC_w03(void) {
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
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        if (player->rev & 0x10) {
            if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
                for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                    HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                    HuPrcVSleep();
                }
            }
            func_80116754_w03(loc->current_player_index);
        }
        player->rev &= 0xAB;
    }
}

void func_8011777C_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011EBE0_w03[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011EBE0_w03[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_80116754_w03(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

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
void func_8011B41C_w03(void) {
    Hu3DCamInit(2);
    Hu3DCameraScissorSet(1, &D_8011D598_w03);
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

s32 func_8011B634_w03(s32 arg0, s32 arg1) {
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

s32 func_8011B71C_w03(void) {
    s32 curPlayer = MBPlayerTurnGet();
    GW_SYSTEM *loc = &GwSystem;
    s32 results[3];
    s32 item;
    s32 i;
    s32 j;
    s32 count;
    s32 best;
    s32 slot;

    if (GwSystem.cur_player_used_item & 1) {
        return -1;
    }
    for (slot = 0; slot < 3; slot++) {
        results[slot] = -1;
        item = GwPlayer[curPlayer].itemNo[slot];
        switch (item) {
            case ITEM_NONE:
                continue;
            case ITEM_SKELETON_KEY:
            case ITEM_BOO_REPELLENT:
            case ITEM_KOOPA_KARD:
                for (i = 0, count = 0; i < 3; i++) {
                    if (GwPlayer[curPlayer].itemNo[i] == item) {
                        count++;
                    }
                }
                if (count < 2) {
                    continue;
                }
                break;
            case ITEM_WACKY_WATCH:
                if (loc->total_turns == loc->current_turn) {
                    if (MBPlayerStealRankGet(loc->current_player_index) != 0) {
                        break;
                    }
                }
                if (loc->total_turns - loc->current_turn < 6) {
                    continue;
                }
                if (MBPlayerStealRankGet(loc->current_player_index) == 0) {
                    break;
                }
                continue;
            case ITEM_MUSHROOM:
            case ITEM_LUCKY_CHARM:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBRandCheck100(80) == 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_PHONE:
                if (GwPlayer[curPlayer].coin == 0) {
                    break;
                }
                for (i = 0; i < 4; i++) {
                    if (i != curPlayer && GwPlayer[i].coin == 0) {
                        break;
                    }
                }
                if (i >= 4) {
                    break;
                }
                if (MBRandCheck100(70) != 0 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB30_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011B5E0_w03() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011DB9C_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011DDD0_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011E184_w03) == 0) {
                    s32 target = func_8011B470_w03();

                    D_8011EC04_w03 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011E568_w03) == 0) {
                    s32 target = func_8011B51C_w03();

                    D_8011EC00_w03 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011EBBC_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011EBBC_w03 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011EBBC_w03 == -1) {
                    continue;
                }
                if (best >= 4) {
                    break;
                }
                if (MBRandCheck100(5) == 0) {
                    continue;
                }
                break;
            case ITEM_BARTER_BOX:
                for (i = 0, best = 0; i < 3; i++) {
                    if (i != slot) {
                        s8 it = GwPlayer[loc->current_player_index].itemNo[i];

                        if (it != -1) {
                            best += D_80100FA8_shared_board[it];
                        }
                    }
                }
                for (i = 0, D_8011EBB8_w03 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011EBB8_w03 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011EBB8_w03 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011B634_w03(0x32, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_CELLULAR_SHOPPER:
                if (loc->total_turns == loc->current_turn) {
                    continue;
                }
                if (GwPlayer[curPlayer].coin < 5) {
                    continue;
                }
                break;
            case ITEM_MAGIC_LAMP:
                if (func_8011B634_w03(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011DF68_w03) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011B5E0_w03() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011E6B8_w03) != 0) {
                    continue;
                }
                break;
        }
        results[slot] = GwPlayer[curPlayer].itemNo[slot];
    }
    slot = 0;
    i = 0;
    for (j = 0; j < 3; j++) {
        item = results[j];
        if (item == -1) {
            continue;
        }
        if (loc->total_turns == loc->current_turn) {
            if (item == ITEM_WACKY_WATCH) {
                return j;
            }
        }
        if (slot < D_80100FF4_shared_board[results[j]]) {
            i = j;
            slot = D_80100FF4_shared_board[results[j]];
        }
    }
    if (slot == 0) {
        return -1;
    }
    return i;
}

s32 func_8011BD24_w03(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    s32 found;
    s32 i;
    u32 flag = 1;

    for (i = 0; i < 16; i++) {
        u8 val = D_8011E82C_w03[player->chr][i];

        found = func_8010B46C_w03(val);
        if (found == -1) {
            continue;
        }
        if (D_80100F94_shared_board[val] + 20 > GwPlayer[loc->current_player_index].coin) {
            continue;
        }
        if (MBRandCheck100(D_8011E8CC_w03[player->chr][i]) != 0) {
            break;
        }
    }
    if (i == 16) {
        found = -1;
    }

    if (found != -1) {
        if (func_8010B46C_w03(0xE) == found) {
            return found + 1;
        }
        if (func_8010B46C_w03(0xB) == found && D_80100F94_shared_board[0xB] + 50 <= GwPlayer[loc->current_player_index].coin) {
            return found + 1;
        }
        if (func_8010B46C_w03(0x4) == found && MBItemFind(loc->current_player_index, 0x4) != -1) {
            found = -1;
            flag = 0;
        }
    }

    if (MBComTreeExec(D_8011E8EC_w03[D_8011D0D0_w03]) == 0 && GwPlayer[loc->current_player_index].coin >= D_80100F94_shared_board[1]) {
        s32 route = func_8010B46C_w03(1);

        if (route != -1) {
            return route + 1;
        }
    }
    if (found != -1) {
        return found + 1;
    }

    i = MBComTreeExec(D_8011E8F4_w03[D_8011D0D0_w03]);
    if (i == 0) {
        for (; i < 16; i++) {
            u8 val = D_8011E82C_w03[player->chr][i];

            if (val == 4 && flag == 0) {
                continue;
            }
            found = func_8010B46C_w03(val);
            if (found == -1) {
                continue;
            }
            if (D_80100F94_shared_board[val] > GwPlayer[loc->current_player_index].coin) {
                continue;
            }
            if (MBRandCheck100(D_8011E8CC_w03[player->chr][i]) != 0) {
                return found + 1;
            }
        }
    }

    found = func_8010B46C_w03(0);
    if (found != -1) {
        return found + 1;
    }
    D_8011E7A8_w03 = 1;
    return func_8010B4F4_w03() + 2;
}

s32 func_8011C088_w03(void) {
    if (D_8011E7A8_w03 != 0) {
        D_8011E7A8_w03 = 0;
        return 2;
    }
    return MBComTreeExec(D_8011E8FC_w03[D_8011D0D0_w03]) + 1;
}
