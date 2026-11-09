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
#include "game/object.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F9DE0.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"

#define GET_STAR_MODEL() D_8011DFF8_w04[GwSystem.star_spawn_indices[GwSystem.current_star_spawn]]

void func_801064DC_w04(void);
void func_80108558_w04(void);
void func_80117EA8_w04(void);
void func_801183D4_w04(void);
void func_801191B8_w04(void);
void func_8011A858_w04(void);
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
extern Object *D_8011E090_w04;
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
s32 func_8011B350_w04(void);
s32 func_8011B6B4_w04(void);
extern s32 D_8011E054_w04;
extern s32 D_8011E058_w04;
extern Object *D_8011E0B4_w04;
void func_8010F9F4_w04(void);
extern s32 D_8011E0CC_w04;
extern s32 D_8011E0D0_w04;
void func_80110244_w04(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode);
extern s32 D_8011E114_w04;
extern s32 D_8011E110_w04;
extern Vec2f D_8011C844_w04[];
extern Vec2f D_8011C864_w04[];
extern DecisionTreeNonLeafNode D_8011D530_w04[];
extern DecisionTreeNonLeafNode *D_8011D65C_w04[];
extern DecisionTreeNonLeafNode *D_8011DAC0_w04[];
extern DecisionTreeNonLeafNode *D_8011DAE0_w04[];
extern DecisionTreeNonLeafNode D_8011CF48_w04[];
extern DecisionTreeNonLeafNode D_8011CFB4_w04[];
extern DecisionTreeNonLeafNode D_8011D1D0_w04[];
extern DecisionTreeNonLeafNode D_8011D314_w04[];
extern DecisionTreeNonLeafNode D_8011D494_w04[];
extern DecisionTreeNonLeafNode D_8011D838_w04[];
extern DecisionTreeNonLeafNode D_8011DB00_w04[];
extern DecisionTreeNonLeafNode *D_8011BA68_w04[];
extern s16 D_8011C000_w04[][3];
extern BranchPair D_8011C014_w04[];
extern DecisionTreeNonLeafNode *D_8011BB40_w04[];
extern s16 D_8011C090_w04[][3];
extern BranchPair D_8011C0A4_w04[];
extern DecisionTreeNonLeafNode *D_8011BBAC_w04[];
extern s16 D_8011C0D8_w04[][3];
extern BranchPair D_8011C0EC_w04[];
extern DecisionTreeNonLeafNode *D_8011BC24_w04[];
extern s16 D_8011C120_w04[][3];
extern BranchPair D_8011C134_w04[];
extern s16 D_8011B9BC_w04[];
void func_80119FCC_w04(s32 arg0, s32 arg1);

extern DecisionTreeNonLeafNode *D_8011BAEC_w04[];
extern s16 D_8011C048_w04[][3];
extern BranchPair D_8011C05C_w04[];
extern DecisionTreeNonLeafNode *D_8011BC84_w04[];
extern s16 D_8011C168_w04[][3];
extern BranchPair D_8011C17C_w04[];
extern s32 D_8011B7C8_w04;
extern s16 D_8011B81C_w04[][2];
extern s16 D_8011B824_w04[][2];
extern s16 D_8011B8CC_w04[];
extern s16 D_8011B8D0_w04[];
extern u32 *D_8011B90C_w04[];
extern s32 D_8011B790_w04[];
extern s32 D_8011B7AC_w04[];
extern event_table_entry D_8011C77C_w04[];
extern event_table_entry D_8011C7F4_w04[];
extern event_table_entry D_8011C988_w04[];
extern event_table_entry D_8011C9C0_w04[];
extern RGB D_8011C968_w04[];
extern u8 D_8011C944_w04[];
extern u8 D_8011C948_w04[];
extern GameGuyReward D_8011C94C_w04[];
extern u8 D_8011C6DC_w04[6][3];
extern u8 D_8011C71C_w04[];
extern s32 D_8011C724_w04[];
extern s32 D_8011C730_w04[];
s32 func_8010CA60_w04(s32 playerIndex);
void func_800D9F5C_shared_board(Object *arg0, Vec *arg1, s32 arg2);
extern u8 D_8011C6F0_w04[14][3];
extern u8 D_8011C538_w04[2][3][4];
extern u8 D_8011C598_w04[2][3][4];
extern s8 D_8011C5B0_w04[2][5][10];
extern u8 D_8011C614_w04[2][10];
extern s32 D_8011C628_w04[5][2];
extern s32 D_8011C650_w04[2];
extern s32 D_8011C658_w04[2];
extern s32 D_8011C660_w04[2];
extern s32 D_8011C668_w04[2];
extern s32 D_8011C670_w04[2];
extern u32 D_8011C678_w04[];
extern u32 D_8011C680_w04[];
extern DecisionTreeNonLeafNode D_8011C508_w04[];
extern u32 D_8011C520_w04[];
void func_80112B48_w04(void);
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

void func_80106120_w04(void) {
    UnkMBGuideData *guide;
    Process *proc;
    SpaceData *space;
    s32 face;
    s32 mesNum;
    GW_SYSTEM *system = &GwSystem;

    D_800A12D4_main = 0;
    guide = MBGuideCreate(0, 0);
    HuAudSeqPlay(0x12);
    MBGuideFaceCreate(guide->obj, 2, 0xF, D_8011B790_w04[0]);
    func_800FFF44_shared_board();
    MBModelDispOff(GET_STAR_MODEL());
    WipeCreateIn(2, 0x10);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    func_800E6FCC_shared_board();
    func_800E9730_shared_board(3.0f);
    func_80106094_w04(guide);

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
    HuWinMesSet(guide->amount, mesNum, -1, -1);
    func_80060C14_main(guide->amount, 1);
    HuAudFXPlay(0x2A7);
    func_800EE2C0_shared_board(guide->amount);
    MBMotionShiftSet(guide->obj, -1, 0, 6, 2);
    func_80060EA8_main(guide->amount, 1);
    func_8001FDE8_main(guide->obj->omObj1->model[0]);

    if ((system->current_board_index != SPINY_DESERT) || (rand8() & 1)) {
        space = MBMasuGet(D_8011B780_w04[system->star_spawn_indices[system->current_star_spawn]]);
    }
    MBCameraPos3DSet(&space->coords);
    MBCameraSpeedSet(5.0f);
    HuPrcSleep(5);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);

    face = MBRand(7.0f);
    MBGuideFaceSet(guide->obj, D_8011B790_w04[face]);
    MBMotionSet(guide->obj, -1, 2);

    if (system->current_board_index != 2) {
        proc = omAddPrcObj(func_80105CA4_w04, 0x4800, 0, 0);
        D_8011E038_w04 = proc;
        proc->user_data = space;
        HuPrcSleep(30);
    } else {
        D_8011E038_w04 = NULL;
    }

    HuWinMesSet(guide->amount, D_8011B7AC_w04[face], -1, -1);
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
    func_80046558_main(D_8011E03C_w04->omObj1->model[0]);
    MBModelKill(D_8011E03C_w04);
    MBModelDispOn(GET_STAR_MODEL());
    MBGuideKill(guide);
    MBExit();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void func_801064DC_w04(void) {
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
    if (MBMasuLinkMasuIdGet(MBPlayerGet(-1)->clink, MBPlayerGet(-1)->cidx) == 0x8D) {
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
    if (D_8011B7C8_w04 != 0) {
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
    if (D_8011B7C8_w04 != 0) {
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

s32 func_80106CC4_w04(u8 *arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = func_8011B350_w04();
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

s32 func_80106F58_w04(void) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                var_s2 = 1; // dead store; matches func_800FA104_shared_board
                var_s2 = func_8011B6B4_w04();
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

void func_80107170_w04(void) {
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
                D_8011E054_w04 = 1;
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
        D_8011E054_w04 = 0;
    } else {
        D_8011E054_w04 = 2;
    }
}

void func_801072A0_w04(void) {
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
    func_80107170_w04();
    if (D_8011E054_w04 == 1) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].star != 0) {
                D_8011E058_w04 = order[i];
                break;
            }
        }
    } else if (D_8011E054_w04 == 0) {
        for (i = 0; i < 4; i++) {
            if (order[i] != cur && GwPlayer[order[i]].coin >= 5) {
                D_8011E058_w04 = order[i];
                break;
            }
        }
    }
    if (i == 4) {
        D_8011E054_w04 = 2;
    }
}

s32 func_80107438_w04(u8 *arg0, s32 arg1, s32 arg2) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                if (arg1 == 0) {
                    func_801072A0_w04();
                    var_s2 = D_8011E054_w04 + 1;
                } else {
                    var_s2 = D_8011E058_w04 + 1;
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

s32 func_80107704_w04(u8 *arg0) {
    return func_80107438_w04(arg0, 0, 1);
}

s32 func_80107724_w04(u8 *arg0) {
    return func_80107438_w04(arg0, 1, 0);
}

void func_80107744_w04(void) {
    GwSystem.current_board_index = 3;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80107780_w04(void) {
    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    GWBoardFlagSet(3);
    func_801059F8_w04();
    GwSystem.bank_coins = 0;
    GwSystem.slow_dice_flags = 0;
    GwSystem.forceShopHost = 0;
    GwSystem.wackyWatchUsedState = 0;
    GwSystem.boardData.halfWordBytes[0] = 1;
    GwSystem.boardData.halfWordBytes[1] = 1;
    GwSystem.boardData.halfWordBytes[2] = 1;
    GwSystem.boardData.halfWordBytes[3] = 0;
    GwSystem.boardData.halfWordBytes[4] = 0;
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_80107828_w04);

void func_80107B34_w04(void) {
    HuAudSeqPlay(0x1B);
    D_800CE198_main = 0x1B;
    func_800F8D6C_shared_board(0x1B);
    Hu3DCamInit(2);
    func_80107828_w04();
    MBMasuEventTblAdd(D_8011C77C_w04);
    MBMasuEventTblAdd(D_8011C9C0_w04);
    MBHatenaFuncSet(&func_8011A858_w04);
    MBMasuEventTblAdd(D_8011C7F4_w04);
    MBMasuEventTblAdd(D_8011C988_w04);
    MBStart(0);
}

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

void func_80108268_w04(s16 arg0) {
    Object *obj;
    s32 unk[2]; // unreferenced; preserves an 8-byte stack slot

    if (D_8011E094_w04[arg0] != NULL) {
        return;
    }
    if (D_8011E090_w04 == NULL) {
        s32 board = GwSystem.current_board_index;

        obj = MBModelCreate(D_8011B8D0_w04[board], D_8011B90C_w04[board]);
        MBModelTempAllocFree(obj);
        D_8011E090_w04 = obj;
    } else {
        obj = MBModelLinkCreate(D_8011E090_w04);
    }
    D_8011E094_w04[arg0] = obj;
    obj->flags |= 2;
    func_8001C814_main(obj->omObj1->model[0], 2, 1);
    HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B8CC_w04[arg0])->coords);
    {
        SpaceData *masuA = MBMasuGet(D_8011B824_w04[arg0][0]);
        SpaceData *masuB = MBMasuGet(D_8011B824_w04[arg0][1]);

        MBVecDirGet(&masuB->coords, &masuA->coords, &obj->rot);
    }
    func_800D771C_shared_board(0xC, obj, D_8011B81C_w04[arg0][0], D_8011B81C_w04[arg0][1]);
}

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

void func_801087CC_w04(s32 index) {
    Object *obj;

    if (D_8011E09C_w04[index] == NULL) {
        obj = MBModelFileCreate(0x130177, 0, 3.0f, 0, NULL);
        MBModelTempAllocFree(obj);
        D_8011E09C_w04[index] = obj;
        obj->flags |= 2;
        HuVecCopy3F(&obj->coords, &MBMasuGet(D_8011B9BC_w04[index])->coords);
    }
}

void func_8010886C_w04(void) {
    s32 i;

    for (i = 0; i < 3; i++) {
        D_8011E09C_w04[i] = NULL;
        func_801087CC_w04(i);
    }
    func_8010873C_w04();
}

void func_801088C8_w04(void) {
    MBMoveNextMasuSet(-1, 1, 0x15);
    MBMoveBackMasuSet(-1, 1, 0x15);
}

void func_801088FC_w04(void) {
    func_80116024_w04(D_8011BFB8_w04, D_8011BFCC_w04, D_8011BA08_w04);
    omDelPrcObj(NULL);
}

void func_80108934_w04(void) {
    if (MBPlayerGet(-1)->rev & 0x80) {
        func_80116024_w04(D_8011C000_w04, D_8011C014_w04, D_8011BA68_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[0] == 0) {
            MBMoveNextMasuSet(-1, 4, 0);
        } else {
            MBMoveNextMasuSet(-1, 9, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_801089B0_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x5C && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 6, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C048_w04, D_8011C05C_w04, D_8011BAEC_w04);
    }
}

void func_80108A58_w04(void) {
    if (MBPlayerGet(-1)->rev & 0x80) {
        func_80116024_w04(D_8011C090_w04, D_8011C0A4_w04, D_8011BB40_w04);
    } else {
        if (GwSystem.boardData.halfWordBytes[1] == 0) {
            MBMoveNextMasuSet(-1, 7, 0);
        } else {
            MBMoveNextMasuSet(-1, 8, 0);
        }
    }
    omDelPrcObj(NULL);
}

void func_80108AD4_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(-1, 9, 5);
        player->rev |= 1;
    } else {
        func_80116024_w04(D_8011C0D8_w04, D_8011C0EC_w04, D_8011BBAC_w04);
    }
    omDelPrcObj(NULL);
}

void func_80108B4C_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);

    if (GwSystem.boardData.halfWordBytes[4] != 0) {
        MBMoveNextMasuSet(-1, 0xB, 3);
        player->rev |= 1;
    } else if (player->rev & 0x80) {
        func_80116024_w04(D_8011C120_w04, D_8011C134_w04, D_8011BC24_w04);
    } else if (GwSystem.boardData.halfWordBytes[2] == 0) {
        MBMoveNextMasuSet(-1, 0xC, 0);
    } else {
        MBMoveNextMasuSet(-1, 0xD, 0);
    }
    omDelPrcObj(NULL);
}

void func_80108C00_w04(void) {
    GW_PLAYER *player = MBPlayerGet(-1);
    s16 masu = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    if (masu == 0x39 && !(player->rev & 0x80)) {
        MBMoveNextMasuSet(-1, 1, 0);
        player->rev &= ~1;
    } else {
        func_80116024_w04(D_8011C168_w04, D_8011C17C_w04, D_8011BC84_w04);
    }
}

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

s32 func_80109690_w04(s32 arg0) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011DDD0_w04;

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
                HuWinComKeyWait(sp18[0], sp18[1], sp18[2], sp18[3], 0x10);
            }
        }
    } else {
        HuWinComKeySet(sp18[0], sp18[1], sp18[2], sp18[3]);
    }

    HuWinChoiceGet(mbDlgWinId, 0, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w04/367960", func_801098A0_w04);

void func_80109CBC_w04(void) {
}

void func_80109CC4_w04(void) {
}

void func_80109CCC_w04(void) {
}

s32 func_80109CD4_w04(s32 arg0, s32 arg1) {
    s32 var_s2 = 0;
    s16 sp18[MB_MAX_PLAYERS];
    u8 sp20[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)sp20 = *(Unk4Bytes *)D_8011DDD0_w04;

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

void func_8010A054_w04(void) {
    GW_SYSTEM *loc;
    s16 spaceIdx;
    s16 choice;

    spaceIdx = MBMasuCurGet();
    loc = &GwSystem;
    spaceIdx = func_80105C30_w04(spaceIdx);
    if (spaceIdx == 1) {
        func_800DBEC0_shared_board(loc->current_player_index);
        MBPlayerMotionSet(-1, -1, 2);
        func_800ED20C_shared_board(-1, 8, func_801059D0_w04());
        HuPrcChildLink(HuPrcCurrentGet(), MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
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
                choice = func_80109CD4_w04(2, 0);
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
                        func_80106A3C_w04(D_8011DFF0_w04);
                        HuPrcSleep(30);
                        func_800EDA58_shared_board();
                        func_800FF7F0_shared_board(2);
                        func_80109CC4_w04();
                        return;
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
                        func_80109CC4_w04();
                        return;
                    case 2:
                        func_80106AB0_w04();
                        goto purchaseMenu;
                    default:
                        func_80109CC4_w04();
                        return;
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

    func_80109CC4_w04();
}

const char D_8011DDD4_w04[] = "%d";

void func_8010A400_w04(void) {
    Object *model;
    Object *effectModel;
    SpaceData *spaceA;
    SpaceData *spaceB;
    GW_SYSTEM *sys;
    Vec *vec;
    s16 mgId;
    s32 choice;
    s32 flag;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    char sp20[0x10];
    char sp30[0x10];
    Vec sp40;

    flag = 0;
    mgId = MBMasuCurGet();
    sys = &GwSystem;
    spaceA = NULL;
    spaceB = NULL;
    if (func_800DCD9C_shared_board(sys->current_player_index) <= 0) {
        MBPlayerVibrate(-1, 3);
    }
    MBPlayerMotionSet(-1, -1, 2);

    switch (mgId) {
        case 0x3D:
            func_800ED20C_shared_board(-1, 8, 0x77);
            spaceA = MBMasuGet(0x77);
            spaceB = MBMasuGet(0x3D);
            break;
        case 0x6:
            func_800ED20C_shared_board(-1, 8, 0x6D);
            spaceA = MBMasuGet(0x6D);
            spaceB = MBMasuGet(0x6);
            break;
    }

    HuPrcSleep(8);
    if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
        func_800DBEC0_shared_board(sys->current_player_index);
    }
    HuAudFXPlay(0x114);

    model = MBModelCreate(0x32, NULL);
    MBModelTempAllocFree(model);
    vec = &sp40;
    HuVecSubtract(vec, &spaceB->coords, &spaceA->coords);
    MBVecNormalize(vec);
    HuVecCopy3F(&model->rot, vec);
    model->scale.y = 0.0f;
    HuVecCopy3F(&model->coords, &spaceA->coords);
    MBMotionSet(model, -1, 1);
    func_800D9A40_shared_board(model);

    effectModel = MBModelCreate(0x35, D_8011C520_w04);
    MBModelTempAllocFree(effectModel);
    HuVecCopy3F(&effectModel->rot, vec);
    HuVecCopy3F(&effectModel->coords, &spaceA->coords);
    effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 0.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    if (50.0f < angle) {
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        do {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
            angle -= scaleStep;
        } while (50.0f < angle);
    }

    model->scale.z = model->scale.x = model->scale.y = 1.0f;
    func_800D9A40_shared_board(effectModel);

    if (MBItemFind(-1, 0xF) != -1) {
    dialogLoop:
        MBDlgWinInsertCreate(-1, 0x3A1D, 0, 0, 0, 0, 0);
        choice = func_80109CD4_w04((s32)D_8011C508_w04, 0);
        MBDlgWinClose();
        MBDlgWinKill();
        switch (choice) {
            case 0:
                flag = 1;
                break;
            case 2:
                func_80106AB0_w04();
                goto dialogLoop;
        }
    }

    MBMotionSet(model, -1, 0);
    Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
    while (MBMotionCheck(model) == 0) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x259);
    MBMotionSet(effectModel, 0, 0);
    while (MBMotionCheck(effectModel) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(effectModel, -1, 2);

    if (flag != 0) {
        sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
        if (GwSystem.bank_coins != 0) {
            MBDlgWinInsertCreate(2, 0x3A1E, (s32)sp20, 0, 0, 0, 0);
        } else {
            MBDlgWinInsertCreate(2, 0x3A1F, 0, 0, 0, 0, 0);
        }
        func_800EC9DC_shared_board();
        MBDlgWinClose();
        MBDlgWinKill();

        if (GwSystem.bank_coins != 0) {
            mbItemBtnF = 0;
            func_80112B48_w04();
            mbItemBtnF = 1;
        } else {
            MBDlgWinInsertCreate(2, 0x3A21, 0, 0, 0, 0, 0);
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            GwPlayer[sys->current_player_index].itemNo[MBItemFind(-1, 0xF)] = -1;
            MBItemRemoveEmpty(sys->current_player_index);
            MBStatusItemIconSprReinit(sys->current_player_index);
        }

        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            func_800DB884_shared_board(sys->current_player_index);
        }
    } else {
        if (func_800DCD9C_shared_board(sys->current_player_index) > 0) {
            if ((GwPlayer[sys->current_player_index].coin != 0) && (GwPlayer[sys->current_player_index].coin < 5)) {
                sprintf(sp20, D_8011DDD4_w04, GwPlayer[sys->current_player_index].coin);
                sprintf(sp30, D_8011DDD4_w04, GwSystem.bank_coins + GwPlayer[sys->current_player_index].coin);
                MBDlgWinInsertCreate(2, 0x1201, (s32)sp20, (s32)sp30, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += GwPlayer[sys->current_player_index].coin;
                func_80107F98_w04();
                MBCoinChangeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                MBCoinTakeCreate(sys->current_player_index, -GwPlayer[sys->current_player_index].coin);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            } else if (GwPlayer[sys->current_player_index].coin == 0) {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1202, (s32)sp20, 0, 0, 0, 0);
            } else {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins + 5);
                MBDlgWinInsertCreate(2, 0x1200, (s32)sp20, 0, 0, 0, 0);
                MBDlgWinClose();
                GwSystem.bank_coins += 5;
                func_80107F98_w04();
                MBCoinChangeCreate(sys->current_player_index, -5);
                MBCoinTakeCreate(sys->current_player_index, -5);
                HuPrcSleep(30);
                func_800EC6A8_shared_board();
            }
            func_800EC9DC_shared_board();
            MBDlgWinClose();
            MBDlgWinKill();
            func_800DB884_shared_board(sys->current_player_index);
            HuPrcSleep(10);
        } else {
            if (GwSystem.bank_coins != 0) {
                sprintf(sp20, D_8011DDD4_w04, GwSystem.bank_coins);
                MBDlgWinInsertCreate(2, 0x1203, (s32)sp20, 0, 0, 0, 0);
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBCoinChangeCreate(sys->current_player_index, GwSystem.bank_coins);
                MBCoinTakeCreate(sys->current_player_index, GwSystem.bank_coins);
                GwSystem.bank_coins = 0;
                func_80107F98_w04();
                MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
                MBPlayerMotionSet(-1, 5, 0);
                PlayerFXPlay(0x274, sys->current_player_index);
                HuPrcSleep(30);
                MBPlayerMotionSet(-1, -1, 2);
                func_800EC6A8_shared_board();
                func_800EC9DC_shared_board();
                MBDlgWinClose();
                MBDlgWinKill();
            } else {
                MBDlgWinExec(2, 0x1204);
            }
        }
    }

    HuAudFXPlay(0x115);
    MBMotionSet(model, -1, 4);
    Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
    Hu3DMotionTimeSet(
        model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].motId].unk02);
    while (func_800D9E80_shared_board(model) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(effectModel);

    speed = 1.0f / sindf(50.0f);
    angle = 50.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 90.0f;
    for (; angle < scaleLimit; angle += scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    angle = 90.0f;
    scaleK = 0.2f;
    scaleBase = 0.8f;
    scaleStep = 11.25f;
    scaleLimit = 0.0f;
    for (; scaleLimit < angle; angle -= scaleStep) {
        model->scale.y = sindf(angle) * speed;
        sp38 = sindf(angle) * speed;
        model->scale.x = sp38 * scaleK + scaleBase;
        sp38 = sindf(angle) * speed;
        model->scale.z = sp38 * scaleK + scaleBase;
        HuPrcVSleep();
    }

    model->scale.y = 0;
    model->scale.x = 0;
    model->scale.z = 0;
    MBModelKill(model);
    MBModelKill(effectModel);
    func_80109CBC_w04();
}

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

void func_8010B1FC_w04(void) {
    GW_SYSTEM *system = &GwSystem;
    SpaceData *spaceA;
    SpaceData *spaceB;
    Object *model;
    Object *playerObj;
    Unk3 *helpWin;
    void *data;
    Process *prc;
    u8 enabled[9];
    u8 itemFlags[6][4];
    Vec sp48;
    s32 dlgWin;
    s16 shopIdx;
    s32 flag2;
    s32 id;
    s32 slot;
    s32 row;
    s32 row2;
    s32 sel;
    s32 choice;
    s32 count;
    s32 item;
    s8 *itemPtr;
    s8(*shopTable)[5][7];
    s8(*shopItems)[7];
    s32 timer;
    s32 randVal;
    s32 i;
    s32 j;
    s32 grp;
    s32 grp2;
    s16 spriteId;
    s32 spriteId2;
    s16 sprY;
    s16 masuId;
    s16 camMasu;
    GW_PLAYER *player;
    Object *effectModel;
    f32 angle;
    f32 speed;
    f32 scaleK;
    f32 scaleBase;
    f32 scaleStep;
    f32 scaleLimit;
    f32 sp38;
    f32 scale;
    player = MBPlayerGet(-1);
    spaceA = NULL;
    spaceB = NULL;
    model = NULL;
    effectModel = NULL;
    MBPlayerMotionSet(-1, -1, 2);

    masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    switch (masuId) {
        case 0x71:
            camMasu = 0x75;
            spaceA = MBMasuGet(0x75);
            spaceB = MBMasuGet(0x71);
            D_8011C688_w04 = 0;
            break;
        case 0x8C:
            camMasu = 0x76;
            spaceA = MBMasuGet(0x76);
            spaceB = MBMasuGet(0x8C);
            D_8011C688_w04 = 1;
            break;
        default:
            camMasu = -1;
            break;
    }

    if (camMasu != -1) {
        func_800ED20C_shared_board(-1, 8, camMasu);
        HuPrcSleep(8);
    }
    func_800DBEC0_shared_board(system->current_player_index);

    switch (GwSystem.forceShopHost) {
        case 0:
            shopIdx = !MBRandCheck100(0x42);
            break;
        case 1:
            shopIdx = 0;
            break;
        default:
            shopIdx = 1;
            break;
    }

    dlgWin = 3;
    if (shopIdx != 0) {
        dlgWin = 5;
    }

    if (camMasu != -1) {
        flag2 = (shopIdx << 1) >> 1;
        id = (-shopIdx & 0x31) | 0x30;
        HuAudFXPlay(0x114);
        model = MBModelCreate(id, NULL);
        MBModelTempAllocFree(model);
        HuVecSubtract(&sp48, &spaceB->coords, &spaceA->coords);
        MBVecNormalize(&sp48);
        HuVecCopy3F(&model->rot, &sp48);
        model->scale.y = 0.0f;
        MBMotionSet(model, -1, 1);
        func_800D9A40_shared_board(model);
        HuVecCopy3F(&model->coords, &spaceA->coords);

        if (flag2 != 0) {
            effectModel = MBModelCreate(0x39, D_8011C680_w04);
        } else {
            effectModel = MBModelCreate(0x1B, D_8011C678_w04);
        }
        MBModelTempAllocFree(effectModel);
        HuVecCopy3F(&effectModel->rot, &sp48);
        HuVecCopy3F(&effectModel->coords, &spaceA->coords);
        effectModel->scale.y = effectModel->scale.x = effectModel->scale.z = 1.2f;
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 0.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        for (; 50.0f < angle; angle -= scaleStep) {
            scaleK = 0.2f;
            scaleBase = 0.8f;
            scaleStep = 11.25f;
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = model->scale.x = model->scale.z = 1.0f;
        func_800D9A40_shared_board(effectModel);
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, 0, 0);

        if (shopIdx != 0) {
            HuAudFXPlay(0x2A0);
        } else {
            if (GwPlayer[system->current_player_index].coin < 5 || MBItemFindEmpty(system->current_player_index) == -1) {
                HuAudFXPlay(0x29A);
            } else if (system->current_turn != system->total_turns) {
                HuAudFXPlay(0x298);
            } else {
                HuAudFXPlay(0x29A);
            }
        }

        while (MBMotionCheck(effectModel) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(effectModel, -1, 2);
    }

    if (system->current_turn == system->total_turns) {
        MBDlgWinExec(dlgWin, D_8011C668_w04[shopIdx]);
        goto end;
    }
    if (MBItemFindEmpty(system->current_player_index) == -1) {
        MBDlgWinExec(dlgWin, D_8011C660_w04[shopIdx]);
        goto end;
    }
    if (GwPlayer[system->current_player_index].coin < 5) {
        MBDlgWinExec(dlgWin, D_8011C658_w04[shopIdx]);
        goto end;
    }

itemSelect:
    MBDlgWinCreate(dlgWin, D_8011C650_w04[shopIdx]);
    choice = func_80106F58_w04();
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 0:

        restart:
            i = BoardGetTurnTier(-1);
            row = D_8011C538_w04[shopIdx][i][BoardPlayerRankCalc(system->current_player_index)];
            count = 0;
            for (j = 0; j < 7; j++) {
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_8011C550_w04[shopIdx][row][j] >= 6) {
                    break;
                }
                enabled[j] = 1;
                count++;
            }
            i = 0;
            for (; j < 7; j++, i++) {
                enabled[j] = 1;
                itemFlags[i][0] = 0;
                if (D_8011C550_w04[shopIdx][row][j] == -1) {
                    continue;
                }
                if (D_80100F94_shared_board[D_8011C550_w04[shopIdx][row][j]] >
                    GwPlayer[system->current_player_index].coin) {
                    enabled[j] = 0;
                    itemFlags[i][0] = 1;
                }
                itemFlags[i][1] = 0;
                count++;
            }
            for (; j < 9; j++) {
                enabled[j] = 1;
            }

            MBDlgWinInsertCreate(dlgWin, D_8011C628_w04[row][slot = shopIdx], (s32)itemFlags[0],
                                 (s32)itemFlags[1], (s32)itemFlags[2], (s32)itemFlags[3], (s32)itemFlags[4]);
            func_800ECAA8_shared_board(0);
            D_8011E0A8_w04 = slot;
            D_8011E0AC_w04 = row;
            D_8011E0B0_w04 = enabled;
            sel = func_80106CC4_w04(enabled);
            MBDlgWinClose();
            MBDlgWinKill();

            if (sel == count) {
                mbItemBtnF = 0;
                MBItemSelNoClear();
                MBItemDescExec(system->current_player_index);
                mbItemBtnF = 1;
                goto restart;
            }
            if (sel == count + 1 || sel == -1) {
                goto itemSelect;
            }

            playerObj = player->player_obj;
            i = shopIdx;
            shopTable = D_8011C550_w04;
            shopItems = shopTable[i];
            itemPtr = (s8 *)(row * 7);
            itemPtr += (s32)shopItems;
            itemPtr += sel;
            MBCoinChangeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            MBCoinTakeCreate(system->current_player_index, -D_80100F94_shared_board[*itemPtr]);
            HuPrcSleep(30);

            if (*itemPtr == 0x13) {
                item = i + 0x13;
            } else {
                GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] =
                    D_8011C550_w04[shopIdx][row][sel];
                item = D_8011C550_w04[shopIdx][row][sel];
            }

            grp = HuSprGrpCreate(1, 5);
            i = 0;
            data = DataRead(D_8010197C_shared_board[item]);
            spriteId = HuSprAnimRead(data);
            DataClose(data);
            HuSprGrpMemberSet(grp, 0, spriteId, 0);
            HuSprPriSet(grp, 0, 0xA);
            func_800550F4_main(grp, 0, 0);
            HuSprAttrSet(grp, 0, 0x180C);
            HuSprPosSet(grp, 0, 0xA0, 0x5A);
            HuSprTPLvlSet(grp, 0, 0);
            MBVecForwardSet(&sp48);
            func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);
            HuAudFXPlay(0x19);
            for (; i < 10; i++) {
                HuSprTPLvlSet(grp, 0, i * 25);
                HuPrcVSleep();
            }
            HuSprTPLvlSet(grp, 0, 0x100);

            if (D_8011C550_w04[shopIdx][row][sel] == 0x13) {
                while (MBItemFindEmpty(system->current_player_index) != -1) {
                    row2 = D_8011C598_w04[shopIdx][BoardGetTurnTier(-1)]
                                         [BoardPlayerRankCalc(system->current_player_index)];
                    randVal = MBRand(100.0f);
                    for (i = 0; i < 10; i++) {
                        if (randVal < D_8011C5B0_w04[shopIdx][row2][i]) {
                            break;
                        }
                    }
                    item = D_8011C614_w04[shopIdx][i];

                    if (camMasu != -1) {
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 1);
                    } else {
                        playerObj->flags |= 0x10;
                        helpWin = func_800E210C_shared_board(0x15, 0xA0, 0);
                    }
                    timer = 30;

                    if ((*(u16 *)((u8 *)D_800C9520_main + (GwPlayer[system->current_player_index].pad << 1)) & 0x8000) == 0) {
                        row = (s32)D_800C9520_main;
                        while (1) {
                            if (MBPlayerComCheck(-1) != 0) {
                                timer--;
                                if (timer == -1) {
                                    break;
                                }
                            }
                            HuPrcVSleep();
                            if (((u16 *)row)[GwPlayer[system->current_player_index].pad] & 0x8000) {
                                break;
                            }
                        }
                    }
                    MBHelpWinKill(helpWin);

                    MBPlayerMotionSet(system->current_player_index, 2, 0);
                    func_800EE688_shared_board(playerObj, 2.0f, -0.3f);
                    HuPrcSleep(5);
                    prc = omAddPrcObj(func_8010B024_w04, 0x4002, 0, 0);
                    prc->user_data = (void *)grp;
                    func_800EE6C0_shared_board(playerObj);
                    MBPlayerMotionSet(-1, -1, 2);

                    grp2 = HuSprGrpCreate(1, 5);
                    i = 0;
                    data = DataRead(D_8010197C_shared_board[item]);
                    spriteId2 = HuSprAnimRead(data);
                    DataClose(data);
                    HuSprGrpMemberSet(grp2, 0, spriteId2, 0);
                    HuSprPriSet(grp2, 0, 0xB);
                    func_800550F4_main(grp2, 0, 0);
                    HuSprAttrSet(grp2, 0, 0x1000);
                    HuSprPosSet(grp2, 0, 0xA0, 0x5A);
                    HuSprTPLvlSet(grp2, 0, 0);
                    MBVecForwardSet(&sp48);
                    func_800ED128_shared_board(&player->player_obj->rot, &sp48, &player->player_obj->rot, 0xA);

                    sprY = 0x5A;
                    scale = 0.0f;
                    do {
                        HuSprPosSet(grp2, 0, 0xA0, sprY);
                        HuSprTPLvlSet(grp2, 0, i * 25);
                        HuSprScaleSet(grp2, 0, scale, scale);
                        i++;
                        HuPrcVSleep();
                        sprY -= 3;
                        scale += 0.1f;
                    } while (i < 10);
                    HuSprScaleSet(grp2, 0, 1.0f, 1.0f);
                    HuSprTPLvlSet(grp2, 0, 0x100);
                    HuPrcSleep(10);
                    GwPlayer[system->current_player_index].itemNo[MBItemFindEmpty(system->current_player_index)] = item;
                    HuSprGrpKill(grp2);
                    HuSprAnimKill(spriteId2);
                }
                if (camMasu == -1) {
                    playerObj->flags &= ~0x10;
                }
            }

            HuPrcSleep(5);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, system->current_player_index);
            HuPrcSleep(20);
            HuPrcVSleep();
            func_800F2388_shared_board(-1, -1, 0, 5, 2);
            HuPrcSleep(10);
            HuSprGrpKill(grp);
            HuSprAnimKill(spriteId);
            break;
        case 1:
            MBDlgWinExec(dlgWin, D_8011C670_w04[shopIdx]);
            break;
        case 2:
            if (camMasu == -1) {
                func_80106B38_w04();
                D_800CB99C_main = 1;
                omAllPause();
            } else {
                func_80106AB0_w04();
            }
            goto itemSelect;
    }

end:
    if (camMasu != -1) {
        HuAudFXPlay(0x115);
        MBMotionSet(model, -1, 4);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        Hu3DMotionTimeSet(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].motId].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(effectModel);

        speed = 1.0f / sindf(50.0f);
        angle = 50.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 90.0f;
        for (; angle < scaleLimit; angle += scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        angle = 90.0f;
        scaleK = 0.2f;
        scaleBase = 0.8f;
        scaleStep = 11.25f;
        scaleLimit = 0.0f;
        for (; scaleLimit < angle; angle -= scaleStep) {
            model->scale.y = sindf(angle) * speed;
            sp38 = sindf(angle) * speed;
            model->scale.x = sp38 * scaleK + scaleBase;
            sp38 = sindf(angle) * speed;
            model->scale.z = sp38 * scaleK + scaleBase;
            HuPrcVSleep();
        }

        model->scale.y = 0;
        model->scale.x = 0;
        model->scale.z = 0;
        MBModelKill(model);
        MBModelKill(effectModel);
    }
    func_800DB884_shared_board(system->current_player_index);
    HuPrcSleep(10);
}

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

s32 func_8010CA60_w04(s32 playerIndex) {
    s32 hasRareItem;
    s16 grp;
    void *data;
    s16 spriteId;
    s16 playerGrp;
    s16 playerSpriteId;
    s32 i;
    s32 state;
    s32 playerSpriteVisible;
    s16 delay;
    s32 angle;
    s32 attempts;
    void *dialog;
    Process *process;

    hasRareItem = 0;
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

    {
        playerGrp = HuSprGrpCreate(1, 5);
        playerSpriteVisible = 0;
        data = DataRead(D_80101040_shared_board[GwPlayer[playerIndex].chr]);
        playerSpriteId = HuSprAnimRead(data);
        DataClose(data);
        HuSprGrpMemberSet(playerGrp, 0, playerSpriteId, 0);
        HuSprPriSet(playerGrp, 0, 0xA);
        func_800550F4_main(playerGrp, 0, 1);
        if (playerIndex & 1) {
            HuSprAttrSet(playerGrp, 0, 0x1001);
        } else {
            HuSprAttrSet(playerGrp, 0, 0x1000);
        }
        if (MBItemFind(playerIndex, 0xC) != -1) {
            HuSprDispOff(playerGrp, 0);
        }
        HuSprPosSet(playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x -
                        (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                    D_8011C69C_w04[playerIndex].y +
                        (D_8011C6BC_w04[playerIndex].y * 16.0f));
        HuSprTPLvlSet(playerGrp, 0, 0);
        HuAudFXPlay(0x133);

        for (i = 0; i < 0x11; i++) {
            HuSprPosSet(grp, 0,
                        (i * D_8011C6BC_w04[playerIndex].x) +
                            D_8011C69C_w04[playerIndex].x,
                        (i * D_8011C6BC_w04[playerIndex].y) +
                            D_8011C69C_w04[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
        HuSprTPLvlSet(grp, 0, 0xFF);
        HuSprTPLvlSet(playerGrp, 0, 0xFF);

        MBWinInsertOpen(MBItemFind(playerIndex, 0xC) == -1 ? 0x620E : 0x620F,
                        (char *)mbCharNameMesTbl[GwPlayer[playerIndex].chr], 0, 0, 0, 0);
        MBPlayerVibrate(playerIndex, 2);
        func_800EC3C0_shared_board(playerIndex);
        if (MBItemFind(playerIndex, 0xC) != -1) {
            omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
            HuPrcSleep(0x14);
        }

        attempts = 0;
        state = 0;
        if (MBItemFind(playerIndex, 0xC) != -1) {
            attempts = 1;
            hasRareItem = 1;
            process = omAddPrcObj(func_80112378_w04, 0x4002, 0, 0);
            process->user_data = (void *)playerIndex;
        }
        HuAudFXPlay(0x133);
        dialog = MBPlayerVibrateObjCreate(playerIndex, 3, 5);
        delay = MBRand(10.0f) + 1;
        i = 0;
        angle = 0;

        for (; i < 0x78; i++, delay--) {
            if (delay == 0) {
                HuAudFXPlay(0x257);
                delay = MBRand(15.0f) + 0x1E;
            }
            state -= !(state < 2);
            if (state == 0) {
                HuSprPosSet(
                    grp, 0,
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y + (sindf(i * 90) * 2.0f));
            } else if (state == 9) {
                HuSprPosSet(
                    grp, 0,
                    (D_8011C6BC_w04[playerIndex].x * 16.0f) +
                        D_8011C69C_w04[playerIndex].x + (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
                HuSprPosSet(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x - 8.0f +
                        (sindf(angle * 90) * 2.0f),
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
                angle++;
            }

            if (GwPlayer[playerIndex].stat & 1) {
                if (state == 0) {
                    goto tryInput;
                } else {
                    if (GwPlayer[playerIndex].cpu_difficulty == 0) {
                        if ((6 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 1) {
                        if ((7 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if (GwPlayer[playerIndex].cpu_difficulty == 2) {
                        if ((8 - MBRand(3.0f)) >= state) {
                            goto tryInput;
                        }
                    } else if ((9 - MBRand(2.0f)) >= state) {
                        goto tryInput;
                    }
                }
            } else if (D_800C9520_main[GwPlayer[playerIndex].pad] & A_BUTTON) {
            tryInput:
                if (!hasRareItem) {
                    attempts++;
                    state = 10;
                    if (!playerSpriteVisible) {
                        HuSprBankSet(playerGrp, 0, 1, 0);
                        func_800550F4_main(playerGrp, 0, 1);
                        playerSpriteVisible = 1;
                        HuSprPosSet(
                            playerGrp, 0, D_8011C69C_w04[playerIndex].x - 8.0f,
                            (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                                D_8011C69C_w04[playerIndex].y);
                    }
                }
            }
            if ((state == 0) && (playerSpriteVisible == 1)) {
                HuSprBankSet(playerGrp, 0, 0, 0);
                func_800550F4_main(playerGrp, 0, 1);
                playerSpriteVisible = 0;
                HuSprPosSet(
                    playerGrp, 0,
                    D_8011C69C_w04[playerIndex].x -
                        (D_8011C6BC_w04[playerIndex].x * 16.0f) - 8.0f,
                    (D_8011C6BC_w04[playerIndex].y * 16.0f) +
                        D_8011C69C_w04[playerIndex].y);
            }
            HuPrcVSleep();
        }
    }

    MBPlayerVibrateObjKill(dialog);
    if (!hasRareItem) {
        omAddPrcObj(func_8010CA3C_w04, 0x1000, 0, 0);
    }

    if (attempts == 0) {
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * D_8011C6BC_w04[playerIndex].x) +
                            D_8011C69C_w04[playerIndex].x,
                        (i * D_8011C6BC_w04[playerIndex].y) +
                            D_8011C69C_w04[playerIndex].y);
            HuSprTPLvlSet(grp, 0, i << 4);
            HuSprTPLvlSet(playerGrp, 0, i << 4);
            HuPrcVSleep();
        }
    } else {
        for (i = 0x10; i >= -0x10; i -= 2) {
            HuSprPosSet(grp, 0,
                        (i * D_8011C6BC_w04[playerIndex].x) +
                            D_8011C69C_w04[playerIndex].x,
                        (i * D_8011C6BC_w04[playerIndex].y) +
                            D_8011C69C_w04[playerIndex].y);
            HuSprPosSet(playerGrp, 0,
                        ((i - 0x10) * D_8011C6BC_w04[playerIndex].x) +
                            D_8011C69C_w04[playerIndex].x - 8.0f,
                        (i * D_8011C6BC_w04[playerIndex].y) +
                            D_8011C69C_w04[playerIndex].y);
            if (hasRareItem) {
                i -= 2;
            }
            HuPrcVSleep();
        }
        HuSprBankSet(playerGrp, 0, 0, 0);
        func_800550F4_main(playerGrp, 0, 1);
        for (i = 0x10; i >= 0; i -= 2) {
            HuSprTPLvlSet(grp, 0, i << 4);
            HuPrcVSleep();
        }
    }

    HuSprGrpKill(grp);
    HuSprAnimKill(spriteId);
    HuSprGrpKill(playerGrp);
    HuSprAnimKill(playerSpriteId);

    playerSpriteVisible = -2;
    if (!hasRareItem) {
        for (i = 0; i < ARRAY_COUNTU(D_8011C6DC_w04); i++) {
            if ((GwSystem.current_turn >= D_8011C6DC_w04[i][0]) &&
                (GwSystem.current_turn <= D_8011C6DC_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible = D_8011C6DC_w04[i][2];
        for (i = 0; i < ARRAY_COUNTU(D_8011C6F0_w04); i++) {
            if ((attempts >= D_8011C6F0_w04[i][0]) &&
                (attempts <= D_8011C6F0_w04[i][1])) {
                break;
            }
        }
        playerSpriteVisible -= D_8011C6F0_w04[i][2];
        if (playerSpriteVisible >= GwPlayer[playerIndex].coin) {
            playerSpriteVisible = -1;
        }
    }
    return playerSpriteVisible;
}

void func_8010D88C_w04(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011E0B4_w04);
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

void func_8010D9E0_w04(Object *arg) {
    Process *temp = omAddPrcObj(func_8010D88C_w04, 0x1000, 0, 0);

    temp->user_data = arg;
}

void func_8010DA1C_w04(void) {
    char inserts[4][16];
    u8 choices[8];
    Vec direction;
    s32 rankedPlayers[3];
    Object *model = NULL;
    SpaceData *space;
    Vec *spaceCoords;
    GW_PLAYER *player;
    GW_SYSTEM *sys;
    Process *process;
    void *coinEffect;
    s32 resultAmount;
    s32 selectedByCpu;
    s16 target;
    s32 menuResult;
    s32 playerChoice;
    s32 rank;
    s32 count;
    s32 i;
    s32 j;
    s32 amountDifference;
    s16 spaceId;
    f32 angle;
    f32 scale;
    f32 rate;
    f32 booVelocity;
    Object *boo;
    s32 modelIsLinked;
    s32 estimatedAmount;
    s16 camMasu;
    s16 menu;
    s32 cameraSet;

    resultAmount = 0;
    estimatedAmount = resultAmount;
    MBMasuCurGet();
    sys = &GwSystem;
    player = MBPlayerGet(-1);
    cameraSet = func_800DBEC0_shared_board(sys->current_player_index);
    MBPlayerMotionSet(-1, -1, 2);
    menu = 0;
    spaceId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    if (spaceId != 0x8D) {
        modelIsLinked = -1;
        camMasu = -1;
        boo = MBModelLinkCreate(D_8011E05C_w04);
        MBModelDispOff(boo);
        booVelocity = 30.0f;
        boo->velocity.x = booVelocity;
        space = MBMasuGet(spaceId);
        HuVecCopyXYZ(&boo->coords, space->coords.x, space->coords.y + 10.0f, space->coords.z);
    } else {
        modelIsLinked = 0;
        camMasu = 0x7D;
        space = MBMasuGet(0x7D);
        boo = D_8011E060_w04[0];
        HuAudFXPlay(0x125);
        model = MBModelCreate(0x33, NULL);
        if (D_8011C730_w04[sys->current_board_index] != 0) {
            func_8001ED54_main(model->omObj1->model[0]);
        }
        Hu3DModelRemakeStatic(model->omObj1->model[0]);
        MBModelTempAllocFree(model);
        spaceCoords = &space->coords;
        HuVecSubtract(&direction, &MBMasuGet(spaceId)->coords, spaceCoords);
        MBVecNormalize(&direction);
        HuVecCopy3F(&model->rot, &direction);
        model->scale.y = 0.0f;
        HuVecCopy3F(&model->coords, spaceCoords);
        MBMotionSet(model, -1, 1);
        MBModelDispOn(model);
        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
            model->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 1.0f;
        model->scale.x = 1.0f;
        model->scale.z = 1.0f;
        if (D_8011C730_w04[sys->current_board_index] != 0) {
            model->scale.x = -1.0f;
        }
        MBMotionSet(model, -1, 0);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        while (MBMotionCheck(model) == 0) {
            HuPrcVSleep();
        }
    }
    HuAudFXPlay(0x257);
    func_8010C4B4_w04(boo);
    space = MBMasuGet(spaceId);
    spaceId = camMasu;
    if (spaceId != -1) {
        func_800D9F5C_shared_board(boo, &space->coords, 5);
        func_800ED20C_shared_board(-1, 5, spaceId);
        HuPrcSleep(5);
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
        HuPrcChildWatch();
    }

    if (GwPlayer[sys->current_player_index].coin < 5) {
        MBDlgWinExec(7, 0x6201);
        goto finishMenu;
    }

restartMenu:
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index &&
            (GwPlayer[i].coin != 0 || GwPlayer[i].star != 0)) {
            break;
        }
    }
    if (i >= 4) {
        MBDlgWinExec(7, 0x6202);
        goto finishMenu;
    }
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].coin != 0) {
            break;
        }
    }
    if (i == 4) {
        inserts[0][0] = 1;
        choices[0] = 0;
    } else {
        inserts[0][0] = 8;
        choices[0] = 1;
    }
    inserts[0][1] = 0;
    for (i = 0; i < 4; i++) {
        if (i != sys->current_player_index && GwPlayer[i].star != 0) {
            break;
        }
    }
    if (i == 4) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].coin < 50) {
        goto starChoiceUnavailable;
    }
    if (GwPlayer[sys->current_player_index].star < 99) {
        goto starChoiceAvailable;
    }

starChoiceUnavailable:
    {
        inserts[1][0] = 1;
        choices[1] = 0;
        goto starChoiceDone;
    }

starChoiceAvailable:
    {
        inserts[1][0] = 8;
        choices[1] = 1;
    }

starChoiceDone:
    inserts[1][1] = 0;
    choices[3] = 1;
    choices[2] = 1;
    MBDlgWinInsertCreate(7, 0x6200, (s32)inserts[0], (s32)inserts[1], 0, 0, 0);
    menuResult = func_80107704_w04(choices);
    menu = menuResult;
    MBDlgWinClose();
    MBDlgWinKill();
    switch ((s16)menuResult) {
        case 0:
        case 1:
            goto selectPlayer;
        case 2:
            goto menuResultTwo;
        case 3:
            goto menuResultThree;
        default:
            goto finishMenu;
    }

selectPlayer:
    i = 0;
    j = 0;
    while (i < 4) {
        if (i == sys->current_player_index) {
            choices[j] = 0;
            inserts[j][0] = 1;
        } else if (menu == 0) {
            if (GwPlayer[i].coin == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        } else {
            if (GwPlayer[i].star == 0) {
                choices[j] = 0;
                inserts[j][0] = 1;
            } else {
                choices[j] = 1;
                inserts[j][0] = 8;
            }
        }
        func_800E2260_shared_board(i, &inserts[j][1]);
        i++;
        j++;
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(7, 0x5C02, (s32)inserts[0], (s32)inserts[1], (s32)inserts[2], (s32)inserts[3], 0);
    playerChoice = func_80107724_w04(choices);
    target = playerChoice;
    MBDlgWinClose();
    selectedByCpu = 0;
    MBDlgWinKill();
    switch ((s16)playerChoice) {
        case -1:
            goto restartMenu;
        case 4:
            goto selectCpuPlayer;
        case 5:
            if (modelIsLinked == -1) {
                func_80106B38_w04();
                D_800CB99C_main = 1;
                omAllPause();
            } else {
                func_80106AB0_w04();
            }
            goto selectPlayer;
        default:
            goto playerSelected;
    }

selectCpuPlayer:
    {
        i = 0;
        count = 0;
        while (i < 4) {
            for (j = 0; j < 4; j++) {
                if (i == BoardPlayerRankCalc(j) && sys->current_player_index != j) {
                    rankedPlayers[count++] = j;
                }
            }
            i++;
        }
        rank = MBRand(100.0f);
        for (i = 0; i < 3; i++) {
            if (rank < D_8011C724_w04[i]) {
                break;
            }
        }
        if (menu != 0) {
            while (GwPlayer[rankedPlayers[i]].star == 0 || rankedPlayers[i] == sys->current_player_index) {
                i--;
            }
        } else {
            while (i >= 0 &&
                   (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
                i--;
            }
            i = 2;
            while (i >= 0 &&
                   (GwPlayer[rankedPlayers[i]].coin == 0 || rankedPlayers[i] == sys->current_player_index)) {
                i--;
            }
        }
        target = rankedPlayers[i];
        selectedByCpu = 1;
    }

playerSelected:
    if (menu == 0) {
        MBCoinChangeCreate(sys->current_player_index, -5);
        MBCoinTakeCreate(sys->current_player_index, -5);
    } else {
        MBCoinChangeCreate(sys->current_player_index, -50);
        MBCoinTakeCreate(sys->current_player_index, -50);
    }
    HuPrcSleep(30);
    if (menu == 1) {
        if (selectedByCpu != 0) {
            MBDlgWinExec(7, 0x6206);
        }
    } else {
        for (i = 0; (u32)i < 6; i++) {
            if (GwSystem.current_turn >= D_8011C6DC_w04[i][0] &&
                GwSystem.current_turn <= D_8011C6DC_w04[i][1]) {
                break;
            }
        }
        estimatedAmount = D_8011C6DC_w04[i][2];
        if (selectedByCpu == 0) {
            MBDlgWinExec(7, MBRand(6.0f) + 0x6207);
        } else {
            MBDlgWinExec(7, 0x620D);
        }
    }
    func_8010C554_w04(boo);
    if (menu == 0) {
        resultAmount = func_8010CA60_w04(target);
        func_8010C4B4_w04(boo);
        if (resultAmount != -2) {
            if (resultAmount == -1) {
                resultAmount = GwPlayer[target].coin;
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                MBDlgWinInsertCreate(7, 0x6214, (s32)inserts[0], 0, 0, 0, 0);
            } else {
                sprintf(inserts[0], D_8011DDD4_w04, resultAmount);
                amountDifference = estimatedAmount - resultAmount;
                for (i = 0; i < 4; i++) {
                    if (amountDifference >= D_8011C71C_w04[i]) {
                        break;
                    }
                }
                MBDlgWinInsertCreate(7, i + 0x6210, (s32)inserts[0], 0, 0, 0, 0);
            }
            MBDlgWinClose();
            MBDlgWinKill();
        }
        if (resultAmount != -2) {
            mbItemBtnF = 0;
            rate = (f32)resultAmount / 90.0f;
            angle = 0.0f;
            D_8011E0B4_w04 = MBModelCreate(0x19, NULL);
            MBModelTempAllocFree(D_8011E0B4_w04);
            MBModelDispOff(D_8011E0B4_w04);
            coinEffect = MBPlayerVibrateObjCreate(target, 3, 5);
            while (resultAmount != 0) {
                angle += rate;
                if (angle >= 1.0f) {
                    angle -= 1.0f;
                    func_8010D9E0_w04(boo);
                    MBCoinTakeCreate(sys->current_player_index, 1);
                    MBCoinTakeCreateSound(target, -1, 0);
                    resultAmount--;
                }
                HuPrcVSleep();
            }
            MBPlayerVibrateObjKill(coinEffect);
            HuPrcSleep(20);
            MBModelKill(D_8011E0B4_w04);
            MBVecForwardSet(&MBPlayerGet(-1)->player_obj->rot);
            MBPlayerMotionSet(-1, 5, 0);
            HuPrcSleep(5);
            PlayerFXPlay(0x274, sys->current_player_index);
            HuPrcSleep(45);
            mbItemBtnF = 1;
            goto outcomeDone;
        }
    } else {
        i = func_8010C5F4_w04(target);
        func_8010C4B4_w04(boo);
        if (i != 0) {
            MBDlgWinExec(7, 0x6205);
            D_8011B7C8_w04 = 1;
            func_80106A3C_w04(boo);
            D_8011B7C8_w04 = 0;
            goto outcomeDone;
        } else {
            resultAmount = -2;
        }
    }

outcomeDone:
    if (modelIsLinked == -1) {
        HuPrcSleep(20);
        MBPlayerMotionSet(-1, -1, 2);
    }
    if (resultAmount == -2) {
        HuPrcSleep(30);
        MBDlgWinExec(7, 0x6215);
    }
    goto finishMenu;

menuResultTwo:
    func_8010C554_w04(boo);
    MBDlgWinExec(7, 0x6203);
    goto finishMenu;

menuResultThree:
    if (modelIsLinked == -1) {
        func_80106B38_w04();
        D_800CB99C_main = 1;
        omAllPause();
    } else {
        func_80106AB0_w04();
    }
    goto restartMenu;

finishMenu:
    if (menu != 2) {
        func_8010C554_w04(boo);
    }
    MBVecForwardSet(&boo->rot);
    if (modelIsLinked == -1) {
        MBModelKill(boo);
    }
    if (camMasu != -1) {
        HuAudFXPlay(0x126);
        MBMotionSet(model, -1, 4);
        Hu3DMotionSpeedSet(model->omObj1->model[0], 1.2f);
        Hu3DMotionTimeSet(
            model->omObj1->model[0], D_800CCF58_main[HmfModelData[model->omObj1->model[0]].motId].unk02);
        while (func_800D9E80_shared_board(model) == 0) {
            HuPrcVSleep();
        }
        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            model->scale.y = sindf(angle) * scale;
            model->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            model->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            if (D_8011C730_w04[sys->current_board_index] != 0) {
                model->scale.x = -model->scale.x;
            }
            HuPrcVSleep();
        }
        model->scale.y = 0.0f;
        model->scale.x = 0.0f;
        model->scale.z = 0.0f;
        MBModelKill(model);
    }
    if (cameraSet != 0) {
        func_800DB884_shared_board(sys->current_player_index);
    }
    if (modelIsLinked != -1) {
        process = HuPrcCurrentGet();
        HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
        HuPrcChildWatch();
    }
    func_80109CCC_w04();
}

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

void func_8010EE9C_w04(void) {
    Vec pos;
    s8 link;
    s8 index;
    GW_PLAYER *player;
    Object *lamp;
    UnkVibrateProcess *vib;
    s32 angle;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9F4_w04();
    lamp = MBModelCreate(0x24, NULL);
    Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
    for (lamp->coords.y = 100.0f; lamp->coords.y > 30.0f;) {
        lamp->coords.y -= 1.0f;
        HuPrcVSleep();
    }

    HuAudFXPlay(0x127);
    func_8004A7C4_main(0xB4);
    vib = MBPlayerVibrateObjCreate(CUR_PLAYER, 4, 5);

    angle = 0xB4;
    i = 0;
    while (angle < 0x438) {
        Vec particleDir[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir[(i / 2) & 7], 0);
        }
        angle += 0x14;
        HuPrcVSleep();
        i++;
    }

    MBPlayerVibrateObjKill(vib);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    func_800EB24C_shared_board(
        D_8011B770_w04[system->star_spawn_indices[system->current_star_spawn]], &link, &index);
    player->clink = link;
    player->cidx = index;
    player->nlink = link;
    player->nidx = index + 1;
    player->blink = link;
    player->bidx = index - 1;
    player->rev &= ~FLAG_REV;
    func_800FC9E0_shared_board();
    HuAudFXPlay(0x128);
    omAllUPause();

    while (1) {
        Vec particleDir2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        lamp->coords.y = (2.0f * sindf(angle)) + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, lamp->coords.x, lamp->coords.y, lamp->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1, &particleDir2[(i / 2) & 7], 0);
        }
        i++;
        HuPrcVSleep();
        angle += 0x14;
        if (angle == 0x500) {
            func_80003A70_main(0);
        }
    }
}

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

void func_8010F2D0_w04(void) {
    s32 currentPlayerIndex;
    GW_PLAYER *player;
    s16 playerIndex;
    s16 spaceIndex;
    s16 fxId;
    s16 ret;

    currentPlayerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    func_8010F9F4_w04();
    func_800DCA64_shared_board(currentPlayerIndex);
    MBPlayerVibrate(CUR_PLAYER, 3);
    GWBoardFlagSet(0x11);
    func_800DC128_shared_board(currentPlayerIndex);
    playerIndex = func_800EF0D8_shared_board(1);
    omAllUPause();
    func_800FC8A4_shared_board();
    HuPrcSleep(5);
    HuPrcSleep(25);
    MBPlayerMotionSet(currentPlayerIndex, 2, 0);
    func_800EE688_shared_board(GwPlayer[currentPlayerIndex].player_obj, 2.0f, -0.3f);
    HuPrcSleep(5);
    func_800DCBCC_shared_board(currentPlayerIndex);
    func_800F2388_shared_board(currentPlayerIndex, CUR_PLAYER, 0, 10, 2);
    HuPrcSleep(20);
    MBItemWarpBlockSwapInit();
    MBItemWarpBlockSwapPlayerSet(playerIndex);
    MBItemWarpBlockSwapCreate();
    GWBoardFlagClear(0x11);
    fxId = func_800DC128_shared_board(currentPlayerIndex);
    HuAudFXStop(fxId);
    func_800DC06C_shared_board(currentPlayerIndex);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    func_800DCD2C_shared_board(currentPlayerIndex, CUR_PLAYER);
    spaceIndex = MBMasuLinkMasuIdGet(player->clink, player->cidx);
    MBMasuCurSet(spaceIndex);
    MBMasuEventCall(spaceIndex, 1);
    ret = func_800FF834_shared_board();
    if (ret >= 0) {
        HuPrcSleep(CUR_PLAYER);
    }
    func_800DAA40_shared_board(currentPlayerIndex);
}

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

void func_80110244_w04(s32 arg0, s32 arg1, s32 duration, f32 *target, s32 mode) {
    f32 position[2];
    f32 stepX;
    f32 stepY;
    f32 scale;
    s32 i;

    if (mode == 2) {
        HuAudFXPlay(0x145);
    }

    func_800F6848_shared_board(arg0, arg1, &position[0], &position[1]);
    stepX = (target[0] - position[0]) / duration;
    stepY = (target[1] - position[1]) / duration;

    for (i = 2; duration != 0; duration--, i++) {
        position[0] += stepX;
        position[1] += stepY;
        MBStatusItemPosSet(arg0, arg1, position[0], position[1]);

        if ((mode == 1) && (i < 11)) {
            MBStatusItemTPLvlSet(arg0, arg1, i * 25);
            scale = i * 0.07f;
            MBStatusItemScaleSet(arg0, arg1, scale + 0.3f,
                                 (f32)((f64)scale + 0.3));
        }
        HuPrcVSleep();
    }

    MBStatusItemPosSet(arg0, arg1, target[0], target[1]);

    if (mode == 0) {
        for (i = 1; i < 10; i++) {
            MBStatusItemTPLvlSet(arg0, arg1, 255 - (i * 25));
            MBStatusItemScaleSet(arg0, arg1, 1.0f - (i * 0.1f), 1.0f - (i * 0.1f));
            HuPrcVSleep();
        }
        MBStatusItemTPLvlSet(arg0, arg1, 0);
    }
}

void func_801104DC_w04(void) {
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

void func_80110768_w04(void) {
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

void func_80110E78_w04(void) {
    GW_SYSTEM *loc;
    void *data;
    s32 choice;
    Process *process;
    s32 i;

    loc = &GwSystem;
    data = DataRead(0x001301B8);
    D_8011E0B8_w04 = HuSprAnimRead(data);
    DataClose(data);
    func_80110080_w04();

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
    HuAudFXPlay(0x29F);

selectPlayer:
    MBDlgWinInsertCreate(4, 0x3A0A, mbCharNameMesTbl[GwPlayer[0].chr], mbCharNameMesTbl[GwPlayer[1].chr],
                         mbCharNameMesTbl[GwPlayer[2].chr], mbCharNameMesTbl[GwPlayer[3].chr], 0);
    if (GwPlayer[loc->current_player_index].coin != 0) {
        choice = func_80109CD4_w04(1, 0);
    } else {
        choice = func_80109CD4_w04(2, loc->current_player_index);
    }
    MBDlgWinClose();
    MBDlgWinKill();

    switch (choice) {
        case 4:
            choice = func_800EF0D8_shared_board(0);
            MBDlgWinInsertCreate(4, 0x3A0C, 0, 0, 0, 0, 0);
            break;
        case 5:
            process = omAddPrcObj(func_8010A014_w04, 0, 0, 0);
            omPrcSetStatBit(process, OM_STAT_NOALLPAUSE);
            func_80106B38_w04();
            D_800CB99C_main = 1;
            omAllPause();
            omDelPrcObj(process);
            func_800FC8A4_shared_board();
            goto selectPlayer;
        default:
            MBDlgWinInsertCreate(4, 0x3A0B, mbCharNameMesTbl[GwPlayer[choice].chr], 0, 0, 0, 0);
            break;
    }

    MBDlgWinClose();
    MBDlgWinKill();
    HuAudFXPlay(0x29C);
    GwPlayer[loc->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(loc->current_player_index);
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    HuSprAnimKill(D_8011E0B8_w04);

    if (func_800DEB2C_shared_board(loc->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FCA4C_shared_board();
    func_800FF794_shared_board(0x50, 0, 3, 1);
    func_800FC8A4_shared_board();
    func_800FF7F0_shared_board(2);
    omAllUPause();
    HuPrcSleep(-1);
}

void func_80111218_w04(void) {
    s32 i;
    s32 j;
    s32 wipeStarted;
    GW_SYSTEM *system = &GwSystem;
    Object *lamp;
    Object *starModel;
    Object *targetStar;
    Process *process;
    Process *dialogProcess;
    Vec direction;
    Vec pos;
    Vec destination;
    s32 angle;
    s32 alpha;
    f32 speed;
    f32 rotation;
    void *dialog;

    {
        GW_PLAYER *player;

        player = MBPlayerGet(-1);
        lamp = MBModelCreate(0x3C, NULL);
        MBMotionSet(lamp, -1, 1);
        Hu3DModelScaleSet(lamp->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&lamp->coords, &player->player_obj->coords);
        lamp->velocity.x = 30.0f;
        lamp->flags |= 1;
        HuVecCopyXYZ(&lamp->scale, 0.0f, 0.0f, 0.0f);
        MBModelDispOff(lamp);
        func_8010F9F4_w04();

        {
            s32 itemSlot = MBItemFind(-1, 9);

            GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
        }
        MBItemRemoveEmpty(system->current_player_index);

        starModel = MBModelCreate(0x3D, NULL);
        func_8001FA68_main(starModel->omObj1->model[0]);
        func_8001F9E4_main(starModel->omObj1->model[0], 0xFF);
        Hu3DModelScaleSet(starModel->omObj1->model[0], 0.0f, 0.0f, 0.0f);
        HuVecCopy3F(&starModel->coords, &player->player_obj->coords);
        starModel->coords.y = 100.0f;
        while (starModel->coords.y > 30.0f) {
            starModel->coords.y -= 1.0f;
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x127);
    func_800039A4_main(D_800CDBC8_main, 0xB4);
    dialog = MBPlayerVibrateObjCreate(-1, 3, 5);

    for (angle = 180, i = 0; angle < 1080; angle += 20, i++) {
        Vec velocities[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1,
                              &velocities[(i / 2) & 7], 1);
        }
        HuPrcVSleep();
    }

    alpha = 0xFF;
    speed = 0.0f;
    while (1) {
        Vec velocities2[8] = {
            {
                1.0f,
                1.0f,
                1.0f,
            },
            { 1.0f, 2.0f, 1.0f },
            { 0.0f, 2.0f, 1.0f },
            { -1.0f, 1.0f, 1.0f },
            { -1.0f, -1.0f, 1.0f },
            { 0.0f, -1.0f, 1.0f },
            { -1.0f, 2.0f, 1.0f },
            { 1.0f, -1.0f, 1.0f }
        };

        starModel->coords.y = sindf((f32)angle) * 2.0f + 30.0f;
        if (i & 1) {
            HuVecCopyXYZ(&pos, starModel->coords.x, starModel->coords.y, starModel->coords.z);
            pos.x -= 15.0f;
            pos.y += 15.0f;
            func_8010EC28_w04(&pos, 0.1f, 2.0f, 1,
                              &velocities2[(i / 2) & 7], 1);
        }

        if (alpha > 0) {
            func_8001F9E4_main(starModel->omObj1->model[0], alpha & 0xFF);
            alpha -= 12;
        } else {
            MBModelDispOff(starModel);
            func_800D9A40_shared_board(lamp);
            speed += 0.1f;
            lamp->scale.z = speed;
            lamp->scale.y = speed;
            lamp->scale.x = speed;
            if (speed > 1.0f) {
                HuAudSeqPlay(0x3D);
                break;
            }
        }
        i++;
        HuPrcVSleep();
    }

    lamp->scale.x = lamp->scale.y = lamp->scale.z = 1.0f;
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBPlayerVibrateObjKill(dialog);
    HuPrcSleep(30);
    MBDlgWinExec(0x3C, 0x3A2F);
    omDelPrcObj(dialogProcess);

    i = 1;
    lamp->coords.y -= lamp->velocity.x;
    HuVecSubtract(&direction, &gCameraList->pos, &lamp->coords);
    MBVecNormalize(&direction);
    lamp->coords.y += lamp->velocity.x;

    while (lamp->velocity.x < 1800.0f) {
        lamp->coords.x += direction.x * 40.2f;
        lamp->velocity.x += direction.y * 40.0f;
        lamp->coords.z += direction.z * 40.2f;
        if ((lamp->velocity.x > 300.0f) && (i != 0)) {
            i = 0;
            WipeColorSet(0xFF, 0xFF, 0xFF);
            WipeCreateOut(0xB, 0x32);
            HuAudFXPlay(0x128);
        }
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    {
        SpaceData *space;
        SpaceData *nextSpace;

        space = MBMasuGet(D_8011B770_w04[system->star_spawn_indices[system->current_star_spawn]]);
        nextSpace = MBMasuGet(D_8011B780_w04[system->star_spawn_indices[system->current_star_spawn]]);
        HuVecCopy3F(&destination, &space->coords);
        MBCameraPos3DSet(&destination);
        MBCameraFocusModeSet(4);
        MBCameraFocusVecSet(&destination);
        lamp->flags &= ~1;
        HuVecCopy3F(&lamp->coords, &space->coords);
        HuVecSubtract(&direction, &nextSpace->coords, &space->coords);
        MBVecNormalize(&direction);
        lamp->coords.x -= direction.x * 20.0f;
        lamp->coords.z -= direction.z * 20.0f;
    }

    HuAudFXPlay(0x129);
    WipeCreateIn(0xB, 0x32);
    lamp->velocity.x = 100.0f;
    while (lamp->velocity.x > 30.0f) {
        HuPrcVSleep();
        lamp->velocity.x -= 3.0f;
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_800ED128_shared_board(&lamp->rot,
                                              &direction,
                                              &lamp->rot, 0x10));
    i = 0;
    HuPrcChildWatch();
    dialogProcess = func_800EDB98_shared_board(lamp, 3.0f, 2.0f);
    MBDlgWinExec(0x3C, 0x3A30);
    HuAudFXPlay(0x12C);
    MBMotionSet(lamp, -1, 0);
    HuPrcSleep(20);

    wipeStarted = 1;
    for (j = 0; j < 8; j++) {
        if (D_8011E018_w04[j] != NULL) {
            omDelPrcObj(D_8011E018_w04[j]);
            D_8011E018_w04[j] = NULL;
        }
    }

    targetStar = D_8011DFF8_w04[system->star_spawn_indices[system->current_star_spawn]];
    HuAudSeqFadeOut(0x5A);
    rotation = 0.0f;
    while (targetStar->velocity.x < 400.0f) {
        targetStar->velocity.x += 3.0f;
        targetStar->coords.x += direction.x * 3.0f;
        targetStar->coords.z += direction.z * 3.0f;
        targetStar->rot.x = -sindf(rotation);
        targetStar->rot.z = cosdf(rotation);
        rotation += 45.0f;
        if (rotation > 360.0f) {
            rotation -= 360.0f;
        }
        if ((targetStar->velocity.x > 50.0f) && (wipeStarted != 0)) {
            if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
                GWBoardFlagSet(0x17);
            } else {
                GWBoardFlagClear(0x17);
            }
            wipeStarted = 0;
            WipeColorSet(0, 0, 0);
            omDelPrcObj(dialogProcess);
            func_800EDA58_shared_board();
            func_800FC8A4_shared_board();
            func_800FF7F0_shared_board(2);
            func_800FCA14_shared_board();
            omAllUPause();
        }
        HuPrcVSleep();
    }
    HuPrcSleep(-1);
}

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

void func_80112828_w04(void) {
    Object *src = HuPrcCurrentGet()->user_data;
    Object *obj = MBModelLinkCreate(D_8011E0C4_w04);
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

s32 func_80112F04_w04(u8 *arg0, s32 arg1) {
    s32 delay = 0;
    s16 inputs[MB_MAX_PLAYERS];
    u8 buttons[MB_MAX_PLAYERS];
    s32 i;
    s32 j;

    *(Unk4Bytes *)buttons = *(Unk4Bytes *)D_8011DDD0_w04;

    for (i = 0; i < MB_MAX_PLAYERS; i++) {
        if (i == GwSystem.current_player_index) {
            if (GwPlayer[i].stat & 1) {
                delay = 1; // Required for matching register allocation.
                if (arg1 != 0) {
                    delay = D_8011E0CC_w04 + 1;
                } else {
                    delay = D_8011E0D0_w04 + 1;
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

void func_80113484_w04(void) {
    char playerNames[4][16];
    u8 choices[16];
    Vec2f position;
    Vec2f target;
    s32 xPos;
    s16 fadeGroup;
    s32 yPos;
    u16 spriteId;
    Object *box;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer;
    s32 noAnimation = 0;
    s32 itemCount;
    s32 itemSlot;
    s32 sleepTime;
    s32 i;
    s32 j;
    s32 item;
    f32 angle;
    f32 angleStep;
    f32 spinStep;
    f32 scale;
    f32 scaleY;
    f32 itemAngle;
    f32 scaleZ;
    f32 finalScale;

    func_8010F9F4_w04();
    box = MBModelCreate(0x20, NULL);
    func_8001C2FC_main(box->omObj1->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(box->omObj1->model[0]);
    func_8001C954_main(box->omObj1->model[0]);
    func_8001C514_main(box->omObj1->model[0]);
    Hu3DModelScaleSet(box->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&box->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(box->omObj1->model[0], 2, 1);
    box->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (box->velocity.x > 30.0f) {
        box->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    for (itemSlot = 0; itemSlot < 4; itemSlot++) {
        if (GwSystem.current_player_index == itemSlot) {
            playerNames[itemSlot][0] = 1;
            choices[itemSlot] = 0;
        } else {
            playerNames[itemSlot][0] = 8;
            choices[itemSlot] = 1;
        }
        func_800E2260_shared_board(itemSlot, &playerNames[itemSlot][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_80112F04_w04(choices, 1);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    itemSlot = MBItemSelNoGet();
    if (GwPlayer[GwSystem.current_player_index].itemNo[itemSlot] == 0x10 &&
        MBItemFindEmpty(GwSystem.current_player_index) == 1 && MBItemFindEmpty(targetPlayer) == 0) {
        noAnimation = 1;
    }

    if (!noAnimation) {
        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 1, 0);
        HuPrcSleep(20);
        position.x = 160.0f;
        position.y = 84.0f;
        for (itemSlot = 0; itemSlot < 3; itemSlot++) {
            for (j = 0; j < 3; j++) {
                spriteId = 0x4790;
                if (j == itemSlot) {
                    spriteId = 0x4786;
                }
                MBStatusItemPriSet(system->current_player_index, j, spriteId);
            }
            if (GwPlayer[system->current_player_index].itemNo[itemSlot] != -1) {
                if (itemSlot != MBItemSelNoGet()) {
                    func_80110244_w04(system->current_player_index, itemSlot, 10, &position.x, 0);
                    HuPrcSleep(2);
                }
            }
        }
        func_8001C814_main(box->omObj1->model[0], 4, 4);
        while (HmfModelData[box->omObj1->model[0]].motTime != 0.0f) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x150);
        HuPrcSleep(20);
        process = omAddPrcObj(func_8011319C_w04, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        HuAudFXPlay(0x151);

        angle = 0.0f;
        spinStep = 5.0f;
        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
            spinStep += 2.0f;
            if (spinStep > 45.0f) {
                spinStep = 45.0f;
                if (i++ >= 31) {
                    break;
                }
            }
            HuPrcVSleep();
        }

        i = 0;
        while (1) {
            box->rot.x = -sindf(angle);
            box->rot.z = cosdf(angle);
            angle += spinStep;
            if (angle > 360.0f) {
                angle -= 360.0f;
                if (++i >= 2) {
                    break;
                }
            }
            spinStep -= 2.0f;
            if (spinStep < 5.0f) {
                spinStep = 5.0f;
            }
            HuPrcVSleep();
        }
        box->rot.x = 0.0f;
        box->rot.z = 1.0f;
        HuAudFXPlay(0x152);
        for (itemSlot = 0; itemSlot < 1441; itemSlot += 40) {
            scale = itemSlot;
            angleStep = sindf(scale) / 1.5f + 1.0f;
            scaleY = sindf(scale) / 1.5f + 1.0f;
            scaleZ = sindf(scale) / 1.5f + 1.0f;
            HuVecCopyXYZ(&box->scale, angleStep, scaleY, scaleZ);
            HuPrcVSleep();
        }

        HuAudFXPlay(0x149);
        func_8001C814_main(box->omObj1->model[0], 4, 0);
        HuPrcSleep(20);
        process = omAddPrcObj(func_801132A8_w04, 0x4800, 0, 0);
        process->user_data = (void *)targetPlayer;
        itemCount = MBItemFindEmpty(targetPlayer);
        target.y = 70.0f;

        switch (itemCount) {
            case 0:
                break;
            case 1:
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                break;
            case 2:
                target.x = 130.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                target.x = 190.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_80110244_w04(targetPlayer, 1, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_80110244_w04(targetPlayer, 1, 7, &target.x, 2);
                break;
            default:
                target.x = 110.0f;
                MBStatusItemPosSet(targetPlayer, 0, 160, 84);
                func_80110244_w04(targetPlayer, 0, 10, &target.x, 1);
                target.x = 210.0f;
                MBStatusItemPosSet(targetPlayer, 1, 160, 84);
                func_80110244_w04(targetPlayer, 1, 10, &target.x, 1);
                target.x = 160.0f;
                MBStatusItemPosSet(targetPlayer, 2, 160, 84);
                func_80110244_w04(targetPlayer, 2, 10, &target.x, 1);
                HuPrcSleep(20);
                MBStatusItemPosGet(system->current_player_index, 0, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 0, 0x4790);
                func_80110244_w04(targetPlayer, 0, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 1, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 1, 0x478F);
                func_80110244_w04(targetPlayer, 1, 7, &target.x, 2);
                MBStatusItemPosGet(system->current_player_index, 2, &xPos, &yPos);
                target.x = xPos;
                target.y = yPos;
                MBStatusItemPriSet(targetPlayer, 2, 0x478E);
                func_80110244_w04(targetPlayer, 2, 7, &target.x, 2);
                break;
        }
        HuPrcSleep(2);
    }

    itemSlot = MBItemSelNoGet();
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    for (itemSlot = 0; itemSlot < 3; itemSlot++) {
        item = GwPlayer[targetPlayer].itemNo[itemSlot];
        GwPlayer[targetPlayer].itemNo[itemSlot] = GwPlayer[system->current_player_index].itemNo[itemSlot];
        GwPlayer[system->current_player_index].itemNo[itemSlot] = item;
    }
    if (!noAnimation) {
        MBStatusItemSprKill(-1);
        MBStatusItemSprKill(targetPlayer);
        sleepTime = 10;
    } else {
        sleepTime = 20;
    }
    HuPrcSleep(sleepTime);
    HuAudFXPlay(0x15B);
    finalScale = 0.1f;
    for (i = 0; i < 20; i++) {
        finalScale += 0.044999998f;
        func_8001D558_main(box->omObj1->model[0], finalScale, finalScale * 10.0f, 1);
        HuPrcVSleep();
    }
    MBModelKill(box);

    if (noAnimation) {
        PlayerFXPlay(0x286, system->current_player_index);
        MBPlayerMotionSet(-1, 3, 0);
        HuPrcSleep(70);
    } else {
        PlayerFXPlay(0x274, system->current_player_index);
        MBPlayerMotionSet(-1, 5, 0);
        HuPrcSleep(50);
    }
    func_800F2388_shared_board(-1, -1, 0, 10, 2);
    MBDlgWinInsertCreate(-1, noAnimation ? 0x3A2E : 0x3A2D,
                         mbCharNameMesTbl[GwPlayer[system->current_player_index].chr],
                         mbCharNameMesTbl[GwPlayer[targetPlayer].chr], 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
}

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

void func_80114720_w04(void) {
    Object *coinModel;
    Object *gameGuyModel;
    Object *playerObj;
    Process *process;
    GW_SYSTEM *system;
    s32 choice;
    s32 itemSlot;
    s32 rewardIndex;
    s32 randomValue;
    s32 rewardAmount;
    s32 i;
    struct {
        s32 processFlag;
        s32 pad;
        char rewardText[0x10];
    } locals;

    system = &GwSystem;
    func_8010F9F4_w04();
    itemSlot = MBItemFind(-1, 0x11);
    GwPlayer[system->current_player_index].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusItemIconSprReinit(system->current_player_index);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    coinModel = MBModelCreate(0x3E, 0);
    Hu3DModelScaleSet(coinModel->omObj1->model[0], 0, 0, 0);
    MBModelTempAllocFree(coinModel);
    coinModel->velocity.x = 30.0f;
    MBModelDispOff(coinModel);

    gameGuyModel = MBModelCreate(0x43, 0);
    D_8011E0D4_w04 = gameGuyModel;
    func_8001C2FC_main(gameGuyModel->omObj1->model[0], 0x20000, 0x20000);
    Hu3DModelRemakeStatic(gameGuyModel->omObj1->model[0]);
    func_8001C954_main(gameGuyModel->omObj1->model[0]);
    func_8001C514_main(gameGuyModel->omObj1->model[0]);
    HuVecCopy3F(&gameGuyModel->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(gameGuyModel->omObj1->model[0], 2, 1);
    gameGuyModel->velocity.x = 100.0f;
    HuAudFXPlay(0x14B);
    while (gameGuyModel->velocity.x > 30.0f) {
        gameGuyModel->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

selectPlayer:
    MBDlgWinInsertCreate(-1, 0x5C00, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109CD4_w04(0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (choice >= 0) {
        if (choice < 4) {
            goto validChoice;
        }
        if (choice == 4) {
            choice = func_800EF0D8_shared_board(0);
            goto validChoice;
        }
    }
    func_80106B38_w04();
    D_800CB99C_main = 1;
    omAllPause();
    goto selectPlayer;

validChoice:
    locals.processFlag = 1;
    process = omAddPrcObj(func_801141F0_w04, 0x4002, 0, 0);
    process->user_data = &locals.processFlag;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    if (choice != system->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        D_8011C940_w04 = choice;
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&MBPlayerGet(choice)->player_obj->coords);
        MBCameraPos3DSet(&MBPlayerGet(choice)->player_obj->coords);
        HuPrcVSleep();
        HuPrcSleep(10);
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    } else {
        HuPrcSleep(30);
        D_8011C940_w04 = choice;
    }

    locals.processFlag = 1;
    while (locals.processFlag != 0) {
        HuPrcVSleep();
    }

    playerObj = MBPlayerGet(choice)->player_obj;
    process = func_800EDB98_shared_board(coinModel, 5.0f, 2.0f);
    HuVecCopy3F(&coinModel->coords, &playerObj->coords);
    func_800D9A40_shared_board(coinModel);
    coinModel->scale.x = coinModel->scale.y = coinModel->scale.z = 0.0f;
    while (coinModel->scale.x < 1.0f) {
        coinModel->scale.x = coinModel->scale.y = coinModel->scale.z += 0.2f;
        HuPrcVSleep();
    }

    MBPlayerVibrate(choice, 4);
    HuAudFXPlay(0x2A1);
    if (GwPlayer[choice].coin != 0) {
        func_80109F58_w04(10, 0x2F00, -1, choice);
        GwPlayer[choice].gameCoin = GwPlayer[choice].coin;
        MBCoinChangeCreate(choice, -GwPlayer[choice].coin);
        MBCoinTakeCreate(choice, -GwPlayer[choice].coin);
        HuPrcSleep(30);
        func_80109F58_w04(10, 0x2F02, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x >= 10.0f) {
            coinModel->velocity.x -= 2.0f;
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        while (coinModel->velocity.x < 100.0f) {
            coinModel->velocity.x += 4.0f;
            playerObj->velocity.x += 4.0f;
            HuPrcVSleep();
        }
    } else {
        func_80109F58_w04(10, 0x2F01, -1, choice);
        omDelPrcObj(process);
        while (coinModel->velocity.x <= 100.0f) {
            coinModel->velocity.x += 4.0f;
            HuPrcVSleep();
        }
        MBModelKill(coinModel);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (MBPlayerComCheck((s16)choice) != 0 && system->show_com_minigames != 0) {
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBModelKill(coinModel);
        func_800EE688_shared_board(playerObj, 0, 0);
        playerObj->velocity.x = 0.0f;
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        randomValue = MBRand(100.0f) + 1;
        for (rewardIndex = 0; rewardIndex < 7; rewardIndex++) {
            if (randomValue <= D_8011C94C_w04[rewardIndex].threshold) {
                break;
            }
        }
        if (D_8011C94C_w04[rewardIndex].multiplier != 0) {
            rewardAmount = GwPlayer[choice].gameCoin * D_8011C94C_w04[rewardIndex].multiplier;
            if (rewardAmount >= 1000) {
                rewardAmount = 999;
            }
            sprintf(locals.rewardText, D_8011DDD4_w04, rewardAmount);
            MBDlgWinInsertCreate(-1, 0x2F03, (s32)locals.rewardText, 0, 0, 0, 0);
            MBDlgWinClose();
            MBDlgWinKill();
            MBCoinChangeCreate(choice, rewardAmount);
            MBCoinTakeCreate(choice, rewardAmount);
            HuPrcSleep(20);
        } else {
            MBDlgWinExec(-1, 0x2F04);
        }
        HuPrcSleep(10);
        WipeCreateOut(9, 0x10);
        HuPrcSleep(0x11);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcSleep(5);
        WipeCreateIn(9, 0x10);
        HuPrcSleep(0x11);
        return;
    }

    if (func_800DEB2C_shared_board(system->current_player_index) == 3) {
        GWBoardFlagSet(0x17);
    } else {
        GWBoardFlagClear(0x17);
    }
    for (i = 0; i < 4; i++) {
        GwPlayer[i].group = 1;
    }
    MBPlayerGet(choice)->group = 0;
    randomValue = MBRand(100.0f);
    for (rewardIndex = 0; (u32)rewardIndex < 3; rewardIndex++) {
        if (randomValue < D_8011C948_w04[rewardIndex]) {
            break;
        }
    }
    if (rewardIndex == 3) {
        rewardIndex = 2;
    }
    system->minigame_index = D_8011C944_w04[rewardIndex];
    GwSystem.playerIndexVisitingBowser = choice;
    func_800FC998_shared_board();
    omAllUPause();
    func_800FF7F0_shared_board(2);
    HuPrcSleep(-1);
}

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

void func_801152D4_w04(omObjData *obj) {
    RGB2 sp18;
    RGB2 sp28;
    s32 i;
    s32 j;

    for (i = 0; i <= 0; i++) {
        sp18.r = D_8011C968_w04[i].r;
        sp18.g = D_8011C968_w04[i].g;
        sp18.b = D_8011C968_w04[i].b;

        sp28.r = (D_8011C968_w04[i + 1].r - sp18.r) / 30;
        sp28.g = (D_8011C968_w04[i + 1].g - sp18.g) / 30;
        sp28.b = (D_8011C968_w04[i + 1].b - sp18.b) / 30;

        for (j = 0; j < 30; j++) {
            HuSprColorSet(D_8011E0D8_w04[3], 0, sp18.r, sp18.g, sp18.b);
            sp18.r += sp28.r;
            sp18.g += sp28.g;
            sp18.b += sp28.b;
            HuPrcVSleep();
        }
        HuSprColorSet(D_8011E0D8_w04[3], 0, D_8011C968_w04[i + 1].r, D_8011C968_w04[i + 1].g, D_8011C968_w04[i + 1].b);
        HuPrcSleep(0xA);
    }

    omDelPrcObj(0);
}

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

void func_80115720_w04(void) {
    s32 sp18[4];
    f32 sp28[2];
    s32 sp30;
    s32 sp34;
    f32 sp38;
    f32 sp3C;
    s32 sp40;
    Process *temp_v0_4;
    f32 temp_f20;
    f32 var_f20;
    s32 temp_s0_3;
    s32 temp_s4;
    s32 temp_s7;
    void *temp_s1_2;
    s32 var_s1;
    s32 var_v0;
    s32 var_v1;
    void *temp_v0;
    Object *temp_v0_3;
    s32 i;
    s32 j;
    GW_SYSTEM *system = &GwSystem;
    s32 temp;

    temp_s4 = HuSprGrpCreate(1, 0);
    temp_v0 = DataRead(D_8010197C_shared_board[18]);
    temp_s7 = HuSprAnimRead(temp_v0);
    DataClose(temp_v0);
    HuSprGrpMemberSet(temp_s4, 0, temp_s7, 0);
    HuSprPriSet(temp_s4, 0, 0x4776U);
    HuSprAttrSet(temp_s4, 0, 0x1000U);
    for (i = 0; i < 4; i++) {
        D_8011E0D8_w04[i] = HuSprGrpCreate(1, 0);
        temp_v0 = DataRead((i + 0x1BB) | 0x130000);
        sp18[i] = HuSprAnimRead(temp_v0);
        DataClose(temp_v0);
        HuSprGrpMemberSet(D_8011E0D8_w04[i], 0, sp18[i], 0);
        HuSprPriSet(D_8011E0D8_w04[i], 0, 0x4780U);
        HuSprAttrSet(D_8011E0D8_w04[i], 0, 0x980CU);
        HuSprTPLvlSet(D_8011E0D8_w04[i], 0, 0U);
        HuSprColorSet(D_8011E0D8_w04[i], 0, 0xFF, 0xFF, 0);
    }
    temp_v0_3 = MBModelCreate(0x46, NULL);
    D_8011E0E8_w04 = temp_v0_3;
    func_8001C258_main(temp_v0_3->omObj1->model[0], 0x180, 0);
    Hu3DModelLayerSet(temp_v0_3->omObj1->model[0], 0x1800);
    Hu3DModelRemakeStatic(temp_v0_3->omObj1->model[0]);
    Hu3DModelScaleSet(temp_v0_3->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&temp_v0_3->coords, &MBPlayerGet(CUR_PLAYER)->player_obj->coords);
    MBModelTempAllocFree(temp_v0_3);
    MBModelDispOff(temp_v0_3);
    HuSprDispOff(mbItemCursorGrpId, 0);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0);
    MBStatusItemPosGet(system->current_player_index, MBItemSelNoGet(), &sp30, &sp34);
    HuSprPosSet(temp_s4, 0, sp30, sp34);
    sp28[0] = 160.0f;
    sp28[1] = 76.0f;
    HuAudFXPlay(0x145);
    func_8011502C_w04(temp_s4, 0x1E, sp28);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
    MBItemRemoveEmpty(system->current_player_index);
    MBStatusShrink(CUR_PLAYER);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(CUR_PLAYER);
    HuPrcSleep(0x1E);
    sp28[0] = 203.0f;
    sp28[1] = 44.0f;
    func_8011502C_w04(temp_s4, 0xA, sp28);
    temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002U, 0, 0);
    temp_v0_4->user_data = NULL;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[0] -= 76.0f;
    HuAudFXPlay(0x14D);
    func_8011502C_w04(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002U, 0, 0);
    temp_v0_4->user_data = (void *)1;
    HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
    sp28[1] += 64.0f;
    HuAudFXPlay(0x14D);
    func_8011502C_w04(temp_s4, 0xA, sp28);
    HuPrcChildWatch();
    HuPrcSleep(0xA);
    HuAudFXPlay(0x14E);
    MBStatusSprPosGet(temp_s4, 0, &sp38, &sp3C);
    for (var_f20 = 0.0f, var_s1 = 0; var_f20 < 90.0f; var_f20 += 3.6f) {
        HuSprPosSet(temp_s4, 0, ((cosdf((2.0f * var_f20) + 270.0f) * 80.0f) + sp38), (((1.0f - cosdf(var_f20)) * 90.0f) + sp3C));
        if (!(var_f20 > 54.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = 1;
        }
        temp = var_v1 != 0;
        if (temp && var_s1 == 0) {
            var_s1 = 1;
            temp_v0_4 = omAddPrcObj(func_80115164_w04, 0x4002U, 0, 0);
            temp_v0_4->user_data = (void *)2;
            HuPrcChildLink(HuPrcCurrentGet(), temp_v0_4);
        }
        HuPrcVSleep();
    }

    temp_s0_3 = (s16)(s32)((cosdf(450.0f) * 80.0f) + sp38);
    HuSprPosSet(temp_s4, 0, temp_s0_3, (((1.0f - cosdf(90.0f)) * 90.0f) + sp3C));

    for (j = 255; j > 0; j -= 0x19, HuPrcVSleep()) {
        HuSprTPLvlSet(temp_s4, 0, j);
    }

    HuSprGrpKill(temp_s4);
    HuSprAnimKill(temp_s7);
    HuPrcChildWatch();

    for (i = 0; i < 3; i++) {
        HuSprDispOff(D_8011E0D8_w04[i], 0);
    }

    HuSprDispOn(D_8011E0D8_w04[3], 0);
    HuSprTPLvlSet(D_8011E0D8_w04[3], 0, 0xFFU);
    HuSprPosSet(D_8011E0D8_w04[3], 0, 0xA0, 0x78);
    HuPrcChildLink(HuPrcCurrentGet(), omAddPrcObj(func_801152D4_w04, 0x4002U, 0, 0));
    sp40 = 0;
    omAddPrcObj(func_8011549C_w04, 0x4002U, 0, 0)->user_data = &sp40;
    HuPrcChildWatch();
    HuAudFXPlay(0x14F);
    temp_s1_2 = MBPlayerVibrateObjCreate(-1, 4, 5);

    for (i = 0; i <= 2880; i += 50) {
        temp_f20 = (sindf(i) / 2.0f) + 1.0f;
        HuSprScaleSet(D_8011E0D8_w04[3], 0, temp_f20, (sindf(i) / 3.0f) + 1.0f);
        if (i >= (2880 / 2 + 1)) {
            sp40 = 1;
        }
        HuPrcVSleep();
    }

    HuAudFXPlay(0x129);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    WipeCreateOut(0xB, 0x32);
    MBPlayerVibrateObjKill(temp_s1_2);

    for (var_f20 = 0.0f; WipeStatGet() != 0; var_f20 += 0.1f) {
        HuSprScaleSet(D_8011E0D8_w04[3], 0, var_f20, var_f20);
        HuPrcVSleep();
    }

    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    sp40 = 2;
    for (i = 0; i < 4; i++) {
        HuSprGrpKill(D_8011E0D8_w04[i]);
        HuSprAnimKill(sp18[i]);
    }

    WipeCreateIn(0xB, 0x5A);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }

    MBDlgResultWinExec(0x3A23);
    GwSystem.wackyWatchUsedState = 2;
}

void func_80116024_w04(s16 (*masu)[3], BranchPair *links, DecisionTreeNonLeafNode **trees) {
    GW_PLAYER *player;
    UnkEA790Struct *win;
    BranchLink *link;
    s32 back;
    s32 sel;
    s32 count;
    s32 row;
    s32 col;
    s32 i;
    s16 *temp;
    DecisionTreeNonLeafNode **tree;

    link = links[0];
    tree = trees;
    MBPlayerMotionSet(-1, -1, 2);
    HuPrcVSleep();
    func_80106B94_w04();
    player = MBPlayerGet(GwSystem.current_player_index);
    back = MBMasuLinkMasuIdGet(player->blink, player->bidx);

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 2; col++) {
            if (masu[row][col] == back) {
                break;
            }
        }
        if (col == 2) {
            break;
        }
    }

    temp = masu[row];
    link += row * 2;
    win = func_800D76A0_shared_board(GwSystem.current_player_index, temp);
    func_800D742C_shared_board(win, GwSystem.current_player_index, 0);

    if (MBPlayerComCheck(-1)) {
        count = MBComTreeExec(tree[row]);
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }

    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80106C64_w04();

    if (sel) {
        link++;
    }

    MBMoveNextMasuSet(-1, link->link, link->idx);
    switch (link->rev) {
        case 0:
            player->rev &= ~1;
            break;
        case 1:
            player->rev |= 1;
            break;
    }
}

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

void func_801165A4_w04(s32 arg) {
    D_8011E100_w04[arg] = omAddObj(0x3FFF, 0, 0, -1, func_801162F8_w04);
    D_8011E100_w04[arg]->work[0] = arg;
    D_8011E100_w04[arg]->work[1] = 0;
    D_8011E100_w04[arg]->work[2] = 0;
    D_8011E100_w04[arg]->rot.x = (f32)MBRand(360.0f);
    D_8011E100_w04[arg]->trans.x = 0;
}

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

void func_8011694C_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    s16 *slowDiceFlags = &loc->slow_dice_flags;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 8) {
        func_800DCA64_shared_board(loc->current_player_index);
        GWBoardFlagSet(0x10);
        *slowDiceFlags &= ~(1 << loc->current_player_index);
        MBDlgWinExec(-1, 0x4219);
        if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_8011621C_w04(loc->current_player_index);
        player->rev &= 0xD7;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

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

void func_80116AFC_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    UnkVibrateProcess *vib;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109CD4_w04(2, D_8011E114_w04);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    GwSystem.slow_dice_flags |= 1 << targetPlayer;
    player = MBPlayerGet(targetPlayer);

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }

    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);
    MBStatusShrink(-1);
    MBStatusItemDispSetAll(0);
    MBStatusGrow(-1);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_8011621C_w04(targetPlayer);
    player->rev = (player->rev & 0x99) | 2;
    func_801164A4_w04(targetPlayer, 0);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    func_801165A4_w04(targetPlayer);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    omAddPrcObj(func_80116AAC_w04, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (player->rev & 0x80) {
        MBDlgWinExec(-1, 0x3A09);
    }
    MBDlgWinExec(-1, 0x3A06);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        GWBoardFlagSet(0x10);
        MBDlgWinExec(-1, 0x3A07);
        for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
            HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
            HuPrcVSleep();
        }
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 0.0f, 0.0f, 0.0f);
        func_8011621C_w04(loc->current_player_index);
        func_800DCA64_shared_board(GwSystem.current_player_index);
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(GwSystem.current_player_index);
        HuPrcSleep(0xF);
        GwSystem.slow_dice_flags &= ~(1 << GwSystem.current_player_index);
        player->rev &= ~2;
    }
}

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

void func_80117244_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(-1);
    f32 scale;

    if (player->rev & 0x10) {
        func_800DCA64_shared_board(loc->current_player_index);
        MBDlgWinExec(-1, 0x421C);
        if (D_8011E0F0_w04[loc->current_player_index] != NULL) {
            for (scale = 1.0f; scale >= 0.0f; scale -= 0.08f) {
                HuVecCopyXYZ(&D_8011E0F0_w04[loc->current_player_index]->scale, scale, scale, scale);
                HuPrcVSleep();
            }
        }
        func_8011621C_w04(loc->current_player_index);
        player->rev &= 0xAF;
        MBPlayerVibrate(-1, 2);
        func_800DC128_shared_board(loc->current_player_index);
        HuPrcSleep(0xF);
    }
}

void func_8011737C_w04(void) {
    GW_SYSTEM *loc = &GwSystem;
    GW_PLAYER *player;
    s32 choice;
    s16 targetPlayer;
    s16 previousPlayer;
    f32 scale;
    f32 hudScale;
    UnkVibrateProcess *vib;

    MBDlgWinInsertCreate(-1, 0x5C01, GwPlayer[0].chr + 0x1C00, GwPlayer[1].chr + 0x1C00,
                         GwPlayer[2].chr + 0x1C00, GwPlayer[3].chr + 0x1C00, 0);
    choice = func_80109CD4_w04(2, D_8011E110_w04);
    MBDlgWinClose();
    MBDlgWinKill();

    if (choice >= MB_MAX_PLAYERS) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else if (choice < 0) {
        targetPlayer = func_800EF0D8_shared_board(0);
    } else {
        targetPlayer = choice;
    }

    player = MBPlayerGet(targetPlayer);
    player->rev |= 0x80;

    for (scale = 1.0f, hudScale = 1.0f; scale > 0.0f;) {
        scale -= 0.1f;
        hudScale += 0.07f;
        MBStatusItemScaleSet(loc->current_player_index, MBItemSelNoGet(), scale, hudScale);
        HuPrcVSleep();
    }
    MBStatusItemTPLvlSet(loc->current_player_index, MBItemSelNoGet(), 0);

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(2);
        MBCameraFocusStaticPosSet(&player->player_obj->coords);
        MBCameraPos3DSet(&player->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        D_800A12D8_main = 1;
        HuPrcSleep(0x10);
    }

    func_8011621C_w04(targetPlayer);
    player->rev = (player->rev & 0x99) | 4;
    MBPlayerVibrate(targetPlayer, 3);
    func_801164A4_w04(targetPlayer, 1);
    for (scale = 0.0f; scale <= 1.0f; scale += 0.08f) {
        HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, scale, scale, scale);
        HuPrcVSleep();
    }
    HuVecCopyXYZ(&D_8011E0F0_w04[targetPlayer]->scale, 1.0f, 1.0f, 1.0f);

    if (targetPlayer == loc->current_player_index) {
        MBPlayerMotionSet(targetPlayer, 4, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, 4, 2);
    }
    CharFXPlay(0x286, GwPlayer[targetPlayer].chr);
    vib = MBPlayerVibrateObjCreate(targetPlayer, 1, 5);
    func_801165A4_w04(targetPlayer);
    omAddPrcObj(func_80116AAC_w04, 0x4002, 0, 0)->user_data = vib;
    HuPrcSleep(0x14);

    previousPlayer = loc->current_player_index;
    loc->current_player_index = targetPlayer;
    if (((previousPlayer == targetPlayer) && (func_800DEB2C_shared_board(previousPlayer) == 3)) ||
        ((GwSystem.slow_dice_flags >> targetPlayer) & 1)) {
        MBDlgWinExec(-1, 0x3A05);
    }
    MBDlgWinExec(-1, 0x3A02);
    loc->current_player_index = previousPlayer;
    if (targetPlayer == (s8)previousPlayer) {
        MBPlayerMotionSet(-1, -1, 2);
    } else {
        MBMotionSet(MBPlayerGet(targetPlayer)->player_obj, -1, 2);
        D_800A12D8_main = 0;
    }

    if (targetPlayer != loc->current_player_index) {
        WipeCreateOut(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
        MBCameraFocusModeSet(1);
        MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
        HuPrcVSleep();
        WipeCreateIn(WIPE_TYPE_NORMAL, 0x10);
        HuPrcSleep(0x10);
    }

    if (targetPlayer == loc->current_player_index) {
        func_80117074_w04();
    }
}

void func_80117800_w04(void) {
    char playerNames[4][16];
    u8 choices[16];
    Object *chest;
    Process *process;
    GW_SYSTEM *system = &GwSystem;
    s32 targetPlayer = 0;
    s32 itemSlot;
    s32 i;
    f32 angle;
    u32 *motion;

    func_8010F9F4_w04();
    chest = MBModelCreate(0x21, NULL);
    Hu3DModelScaleSet(chest->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&chest->coords, &MBPlayerGet(-1)->player_obj->coords);
    func_8001C814_main(chest->omObj1->model[0], 2, 1);
    chest->velocity.x = 100.0f;
    HuAudFXPlay(0x142);
    while (chest->velocity.x > 30.0f) {
        chest->velocity.x -= 1.0f;
        HuPrcVSleep();
    }

    if (targetPlayer != 0) {
        for (i = 0; i < 1081; i += 30) {
            angle = sindf((f32)i) / 2.0f + 1.0f;
            HuVecCopyXYZ(&chest->scale, angle, sindf((f32)i) / 2.0f + 1.0f,
                         sindf((f32)i) / 2.0f + 1.0f);
            HuPrcVSleep();
        }
    }

    HuAudFXPlay(0x149);
    func_8001C814_main(chest->omObj1->model[0], 1, 0);
    HuPrcSleep(20);

    for (i = 0; i < 4; i++) {
        if (GwSystem.current_player_index == i) {
            playerNames[i][0] = 1;
            choices[i] = 0;
        } else {
            playerNames[i][0] = 8;
            choices[i] = 1;
        }
        func_800E2260_shared_board(i, &playerNames[i][1]);
    }
    choices[4] = 1;
    choices[5] = 1;
    MBDlgWinInsertCreate(-1, 0x5C01, (s32)playerNames[0], (s32)playerNames[1], (s32)playerNames[2],
                         (s32)playerNames[3], 0);
    targetPlayer = func_80112F04_w04(choices, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    if (targetPlayer == 4) {
        targetPlayer = func_800EF0D8_shared_board(1);
    }

    if (GwPlayer[targetPlayer].itemNo[0] == -1) {
        MBPlayerMotionSet(-1, 3, 0);
        PlayerFXPlay(0x286, system->current_player_index);
        HuPrcSleep(60);
        func_800E2260_shared_board(targetPlayer, playerNames[0]);
        MBWinInsertOpen(0x3A0F, playerNames[0], 0, 0, 0, 0);
        func_800EC3C0_shared_board(system->current_player_index);
        func_800EC3E4_shared_board();
        func_800F2388_shared_board(-1, -1, 0, 10, 2);
        MBModelKill(chest);
        GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] = -1;
        MBItemRemoveEmpty(system->current_player_index);
        return;
    }

    itemSlot = MBItemFindEmpty(targetPlayer);
    if (itemSlot == -1) {
        itemSlot = 3;
    }
    itemSlot = MBRand((f32)itemSlot);
    GwPlayer[system->current_player_index].itemNo[MBItemSelNoGet()] =
        GwPlayer[targetPlayer].itemNo[itemSlot];
    GwPlayer[targetPlayer].itemNo[itemSlot] = -1;
    MBItemRemoveEmpty(targetPlayer);
    MBPlayerVibrate((s16)targetPlayer, 3);
    if (MBItemSelNoGet() == itemSlot) {
        MBStatusItemTPLvlSet(targetPlayer, MBItemSelNoGet(), 0);
    }
    MBStatusItemSprKill(-1);
    MBStatusItemPosSet(system->current_player_index, MBItemSelNoGet(),
                       D_8011C864_w04[system->current_player_index].x,
                       D_8011C864_w04[system->current_player_index].y);
    MBStatusItemTPLvlSet(system->current_player_index, MBItemSelNoGet(), 0x100);
    MBStatusItemTPLvlSet(targetPlayer, itemSlot, 0);
    MBStatusItemPriSet(system->current_player_index, MBItemSelNoGet(), 0x4786);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process,
                   func_8010F6F4_w04(-1,
                                     D_8011C864_w04[system->current_player_index].x,
                                     D_8011C864_w04[system->current_player_index].y,
                                     D_8011C844_w04[system->current_player_index].x,
                                     D_8011C844_w04[system->current_player_index].y, 5));
    HuPrcChildWatch();
    PlayerFXPlay(0x274, system->current_player_index);
    MBPlayerMotionLoad(system->current_player_index, 5, 0x31);
    MBPlayerMotionSet(-1, 5, 0);
    HuPrcSleep(50);
    func_800F2388_shared_board(system->current_player_index, -1, 0, 10, 2);
    HuPrcSleep(11);
    motion = D_80101734_shared_board[0];
    for (i = 6; i != 0; i--) {
        motion++;
    }
    MBPlayerMotionLoad(system->current_player_index, 5, ((u16 *)motion)[1]);
    MBModelKill(chest);
    MBDlgWinInsertCreate(-1, 0x3A0D, GwPlayer[targetPlayer].chr + 0x1C00,
                         GwPlayer[system->current_player_index].chr + 0x1C00, 0, 0, 0);
    MBDlgWinClose();
    MBDlgWinKill();
    func_8010FBC4_w04();
}

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

void func_8011A4E0_w04(s32 arg0) {
    Vec pos;
    SpaceData *space = MBMasuGet(D_8011B9BC_w04[arg0]);
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);

    HuVecCopy3F(&pos, &player->player_obj->coords);
    MBCameraFocusModeSet(4);
    MBCameraFocusVecSet(&pos);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &space->coords, &pos, 15));
    HuPrcChildWatch();
    func_80119FCC_w04(arg0, 0);
    HuPrcChildLink(HuPrcCurrentGet(), MBPlayerPosMoveCreate(&pos, &player->player_obj->coords, &pos, 10));
    HuPrcChildWatch();
    MBCameraFocusModeSet(1);
}

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

s32 func_8011AA64_w04(void) {
    s32 i;
    DecisionTreeNonLeafNode *data;
    GW_SYSTEM *loc = &GwSystem;

    data = D_8011D65C_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(D_8011D530_w04) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(data) == 0) {
                return i;
            }
        }
    }
    MBRand(4.0f);
}

s32 func_8011AB34_w04(void) {
    s32 i;
    DecisionTreeNonLeafNode *data1;
    DecisionTreeNonLeafNode *data2;
    GW_SYSTEM *loc = &GwSystem;

    data1 = D_8011DAC0_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    data2 = D_8011DAE0_w04[loc->star_spawn_indices[loc->current_star_spawn]];
    func_800DA778_shared_board(loc->current_player_index);
    if (MBComTreeExec(data1) == 0) {
        return loc->current_player_index;
    }
    for (i = 0; i < 4; i++) {
        if (i != loc->current_player_index) {
            func_800DA778_shared_board(i);
            if (MBComTreeExec(data2) == 0) {
                return i;
            }
        }
    }
    MBRand(4.0f);
}

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

s32 func_8011AD48_w04(void) {
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
                if (func_8011AC0C_w04() != 0) {
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
                if (MBRandCheck100(70) != 0 && func_8011AC0C_w04() == 0) {
                    continue;
                }
                break;
            case ITEM_GOLDEN_MUSHROOM:
                if (func_8011AC0C_w04() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011CF48_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_BOWSER_SUIT:
                if (func_8011AC0C_w04() != 0) {
                    break;
                }
                if (MBComTreeExec(D_8011CFB4_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_WARP_BLOCK:
                if (MBComTreeExec(D_8011D1D0_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_POISON_MUSHROOM:
                if (MBComTreeExec(D_8011D494_w04) == 0) {
                    s32 target = func_8011AA64_w04();

                    D_8011E114_w04 = target;
                    if ((GwSystem.slow_dice_flags >> target) & 1) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_REVERSE_MUSHROOM:
                if (MBComTreeExec(D_8011D838_w04) == 0) {
                    s32 target = func_8011AB34_w04();

                    D_8011E110_w04 = target;
                    if (GwPlayer[target].rev & 0x80) {
                        continue;
                    }
                    break;
                }
                continue;
            case ITEM_PLUNDER_CHEST:
                for (i = 0, best = 0, D_8011E0D0_w04 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                if (best < D_80100FA8_shared_board[it]) {
                                    best = D_80100FA8_shared_board[it];
                                    D_8011E0D0_w04 = i;
                                }
                            }
                        }
                    }
                }
                if (D_8011E0D0_w04 == -1) {
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
                for (i = 0, D_8011E0CC_w04 = -1; i < 4; i++) {
                    if (i != curPlayer) {
                        count = 0;
                        for (j = 0; j < 3; j++) {
                            s8 it = GwPlayer[i].itemNo[j];

                            if (it != -1) {
                                count += D_80100FA8_shared_board[it];
                            }
                        }
                        if (best < count) {
                            D_8011E0CC_w04 = i;
                            best = count;
                        }
                    }
                }
                if (D_8011E0CC_w04 == -1) {
                    continue;
                }
                break;
            case ITEM_BOO_BELL:
                if (func_8011AC60_w04(0x32, 0xA) == 0) {
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
                if (func_8011AC60_w04(0x3C, 0xA) == 0) {
                    break;
                }
                if (GwPlayer[curPlayer].coin < 20) {
                    continue;
                }
                if (MBComTreeExec(D_8011D314_w04) != 0) {
                    continue;
                }
                break;
            case ITEM_DUEL_GLOVE:
                if (GwPlayer[curPlayer].coin < 10 && func_8011AC0C_w04() == 0) {
                    continue;
                }
                break;
            case ITEM_LUCKY_LAMP:
                if (MBComTreeExec(D_8011DB00_w04) != 0) {
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
