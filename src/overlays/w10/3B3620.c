#include "common.h"
#include "game/aura.h"
#include "game/hu3d.h"
#include "game/input.h"
#include "game/pause.h"
#include "game/malloc.h"
#include "game/wipe.h"
#include "../ovl_80_shared_board/1006F0.h"
#include "../ovl_80_shared_board/1063F0.h"
#include "../ovl_80_shared_board/EA790.h"
#include "../ovl_80_shared_board/EAB00.h"
#include "../ovl_80_shared_board/EC3B0.h"
#include "../ovl_80_shared_board/ECA50.h"
#include "../ovl_80_shared_board/EE660.h"
#include "../ovl_80_shared_board/101840.h"
#include "../ovl_80_shared_board/10C230.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106640.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/F5070.h"
#include "../ovl_80_shared_board/F5B90.h"
#include "../ovl_80_shared_board/F5E80.h"
#include "../ovl_80_shared_board/F2910.h"

// Sets the shared process state and sleeps until another process changes it.
#define SET_STATE_AND_WAIT(state, value) \
    do {                                 \
        s32 _value = (value);            \
        *(state) = _value;               \
        while (*(state) == _value) {     \
            HuPrcVSleep();               \
        }                                \
    } while (0)

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} W10SprGroup; // sizeof 0x08

typedef struct {
    /* 0x00 */ s32 player;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 slot;
    /* 0x0C */ s32 unkC;
} W10RunnerData; // sizeof 0x10

extern s16 D_8010B7F0_w10[4];
extern Vec D_8010B818_w10[];
extern Vec D_8010B854_w10[];
extern s16 D_8010B890_w10[];
extern s16 D_8010B898_w10[];
extern s32 D_8010B8C0_w10[];
extern s32 D_8010B8E8_w10[];
extern s16 D_8010B8FC_w10;
extern Object *D_8010BA24_w10;
extern Process *D_8010BA28_w10;
extern Object *D_8010BA2C_w10;
extern Object *D_8010BA30_w10;
extern Object *D_8010BA38_w10[2];
extern u32 D_8010B900_w10[];
extern u32 D_8010B908_w10[];
extern s32 D_8010B918_w10;
extern f32 D_8010B91C_w10[][2];
extern s32 D_8010BA20_w10;
extern s16 D_8010BA4C_w10;
extern s16 D_8010BA4E_w10;
extern s16 D_8010BA50_w10;
extern s16 D_8010BA52_w10;
extern s16 D_8010BA54_w10;
extern Vec D_8010BA58_w10;
extern Object *D_8010BA68_w10;
extern Object *D_8010BA6C_w10;
extern Object *D_8010BA70_w10;
extern Object *D_8010BA74_w10;
extern event_table_entry D_8010B8B0_w10[];
extern s32 D_8010BA80_w10[];
extern Object *D_8010BA90_w10;
extern s32 D_8010BA94_w10;
extern s32 D_8010B7F8_w10[];
extern s32 D_8010B810_w10[];
extern u32 D_8010B910_w10[];
extern UnkMBGuideData *D_8010BA64_w10;
extern Process *D_8010BA78_w10;

void func_80109444_w10(void);
void func_8010AF68_w10(UnkMBGuideData *guide);

void func_801059D0_w10(void) {
    GwSystem.current_board_index = 6;
    omInitObjMan(0xA, 0);
    omOvlGotoEx(0x47, 0, 0x192);
}

void func_80105A0C_w10(void) {
    s32 i;

    omInitObjMan(0xA, 0);
    MBMoveMasuSet(0, 0, 0);
    MBMoveMasuSet(1, 0, 0);
    MBMoveMasuSet(2, 0, 0);
    MBMoveMasuSet(3, 0, 0);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->chr = D_8010B7F0_w10[i];
    }
    omOvlReturnEx(1);
}

void func_80105AB8_w10(void) {
    Object *obj;

    if (D_8010BA24_w10 != NULL) {
        return;
    }
    obj = MBModelCreate(0x3A, NULL);
    func_800461B4_main(obj->omObj1->model[0]);
    MBModelTempAllocFree(obj);
    D_8010BA24_w10 = obj;
    obj->flags |= 2;
    HuVecCopyXYZ(&obj->scale, 0.6f, 0.6f, 0.6f);
    obj->velocity.x = 10.0f;
    D_8010BA28_w10 = func_800EDB98_shared_board(obj, 6.0f, 2.0f);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x25)->coords);
}

void func_80105B70_w10(void) {
    D_8010BA24_w10 = NULL;
    func_80105AB8_w10();
}

void func_80105B90_w10(void) {
    Object *obj;

    if (D_8010BA2C_w10 != NULL) {
        return;
    }
    obj = MBModelCreate(0xA, NULL);
    func_8001FA68_main(obj->omObj1->model[0]);
    func_8001FA68_main(obj->omObj2->model[0]);
    D_8010BA2C_w10 = obj;
    obj->flags |= 2;
    obj->velocity.x = 15.0f;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x24)->coords);
    MBModelDispOff(obj);
}

void func_80105C28_w10(void) {
    D_8010BA2C_w10 = NULL;
    func_80105B90_w10();
}

void func_80105C48_w10(s16 arg0) {
    Object *obj;

    if (D_8010BA38_w10[arg0] != NULL) {
        return;
    }
    if (D_8010BA30_w10 == NULL) {
        obj = MBModelCreate(0x1E, NULL);
        MBModelTempAllocFree(obj);
        D_8010BA30_w10 = obj;
    } else {
        obj = MBModelLinkCreate(D_8010BA30_w10);
    }
    D_8010BA38_w10[arg0] = obj;
    obj->flags |= 2;
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2F)->coords);
    HuVecAdd(&obj->coords, &D_8010B818_w10[arg0], &obj->coords);
    obj->omObj1->rot.x = D_8010B854_w10[arg0].x;
    obj->omObj1->rot.z = D_8010B854_w10[arg0].z;
}

void func_80105D6C_w10(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        D_8010BA38_w10[i] = NULL;
        func_80105C48_w10(i);
    }
}

void func_80105DC4_w10(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void func_80105E08_w10(void) {
}

void func_80105E10_w10(void) {
    UnkEA790Struct *win;
    s32 count;
    s32 sel;
    s32 i;

    MBPlayerMotionSet(-1, -1, 2);
    func_80105DC4_w10();
    win = func_800D76A0_shared_board(-1, D_8010B890_w10);
    func_800D742C_shared_board(win, -1, 0);
    if (MBPlayerComCheck(-1)) {
        count = D_8010B898_w10[GwSystem.boardData.halfWordBytes[0]++];
        for (i = 0; i < count; i++) {
            func_800D7250_shared_board(win, -2);
        }
        func_800D7250_shared_board(win, -4);
    }
    sel = func_800D7518_shared_board(win);
    func_800D6CA0_shared_board(win);
    func_80105E08_w10();
    if (sel == 0) {
        MBMoveNextMasuSet(-1, 1, 0);
    } else {
        MBMoveNextMasuSet(-1, 2, 0);
    }
    omDelPrcObj(NULL);
}

void func_80105F20_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->stat |= PLAYER_IS_CPU;
    }
}

void func_80105F64_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F292C_shared_board());
    HuPrcChildWatch();
}

void func_80105FA0_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), func_800F29EC_shared_board());
    HuPrcChildWatch();
}

W10SprGroup *func_80105FDC_w10(s16 arg0, s16 x, s16 y) {
    W10SprGroup *group;
    void *data;

    group = HuMemMemoryAllocTemp(sizeof(W10SprGroup));
    group->spriteGroup = HuSprGrpCreate(3, 0);

    data = DataRead(0x130000);
    group->sprites[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 0, group->sprites[0], 0);
    HuSprPriSet(group->spriteGroup, 0, 0xB);
    HuSprAttrSet(group->spriteGroup, 0, 0x1000);
    HuSprPosSet(group->spriteGroup, 0, x + 5, y);
    DataClose(data);

    data = DataRead(0x130001);
    group->sprites[1] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 1, group->sprites[1], 0);
    HuSprPriSet(group->spriteGroup, 1, 0xC);
    HuSprAttrSet(group->spriteGroup, 1, 0x1000);
    HuSprPosSet(group->spriteGroup, 1, x + 5, y);
    HuSprTPLvlSet(group->spriteGroup, 1, 0xFF);
    HuSprColorSet(group->spriteGroup, 1, 0x1F, 0xB0, 0x3F);
    DataClose(data);

    data = DataRead(D_8010B8C0_w10[arg0]);
    group->sprites[2] = HuSprAnimRead(data);
    HuSprGrpMemberSet(group->spriteGroup, 2, group->sprites[2], 0);
    HuSprPriSet(group->spriteGroup, 2, 0xA);
    HuSprAttrSet(group->spriteGroup, 2, 0x1000);
    HuSprPosSet(group->spriteGroup, 2, x, y);
    DataClose(data);

    return group;
}

void func_801061E8_w10(W10SprGroup *arg0) {
    HuSprAnimKill(arg0->sprites[0]);
    HuSprAnimKill(arg0->sprites[1]);
    HuSprAnimKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreeTemp(arg0);
}

void func_80106230_w10(s16 arg0, s16 x, s16 y) {
    void *data;

    D_8010BA4C_w10 = HuSprGrpCreate(1, 0);
    data = DataRead(D_8010B8E8_w10[arg0]);
    D_8010BA4E_w10 = HuSprAnimRead(data);
    HuSprGrpMemberSet(D_8010BA4C_w10, 0, D_8010BA4E_w10, 0);
    HuSprPriSet(D_8010BA4C_w10, 0, 0xB);
    HuSprAttrSet(D_8010BA4C_w10, 0, 0x1000);
    HuSprPosSet(D_8010BA4C_w10, 0, x, y);
    DataClose(data);
}

void func_80106314_w10(s16 x, s16 y) {
    void *data;
    f32 scale;

    D_8010BA50_w10 = HuSprGrpCreate(1, 0);
    data = DataRead(0x130015);
    D_8010BA52_w10 = HuSprAnimRead(data);
    HuSprGrpMemberSet(D_8010BA50_w10, 0, D_8010BA52_w10, 0);
    HuSprPriSet(D_8010BA50_w10, 0, 0xC);
    HuSprAttrSet(D_8010BA50_w10, 0, 0x1000);
    HuSprColorSet(D_8010BA50_w10, 0, 0, 0xFF, 0);
    HuSprPosSet(D_8010BA50_w10, 0, x, y);
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 0.0f);
    DataClose(data);
    for (scale = 0.0f; scale < 1.0f; scale += 1.0f / 6.0f) {
        HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 1.0f);
}

void func_8010649C_w10(void) {
    HuSprAnimKill(D_8010BA4E_w10);
    HuSprGrpKill(D_8010BA4C_w10);
}

void func_801064C8_w10(void) {
    f32 scale;

    for (scale = 1.0f; scale > 0.0f; scale -= 1.0f / 6.0f) {
        HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, scale);
        HuPrcVSleep();
    }
    HuSprScaleSet(D_8010BA50_w10, 0, 1.0f, 0.0f);
    HuSprAnimKill(D_8010BA52_w10);
    HuSprGrpKill(D_8010BA50_w10);
}

void func_80106574_w10(void) {
    D_8010BA54_w10 = -1;
    MBPlayerPosFixSet(0, 1);
    MBPlayerPosFixSet(1, 1);
    MBPlayerPosFixSet(2, 1);
    MBPlayerPosFixSet(3, 1);
    WipeCreateIn(2, 0x10);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    func_800E6FCC_shared_board();
    while (TRUE) {
        if (D_8010BA54_w10 < 0) {
            if (D_8010BA54_w10 == -2) {
                MBCameraPos3DSet(&D_8010BA58_w10);
            } else {
                MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
            }
        } else {
            MBCameraPos3DSet(&MBMasuGet(D_8010BA54_w10)->coords);
        }
        HuPrcVSleep();
    }
}

void func_80106670_w10(s16 arg0) {
    D_8010BA54_w10 = arg0;
    MBCameraSpeedSet(4.0f);
}

void func_8010669C_w10(void) {
    HuPrcSleep(3);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    MBCameraSpeedSet(-1.0f);
}

void func_801066E8_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBPlayerGet(i);
        player->color = 0;
        player->stat &= ~2;
    }
}

void func_80106730_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBStatusColorSet(i, MBPlayerGet(i)->color);
    }
}

void func_80106774_w10(void) {
    GW_PLAYER *player;
    s32 i;
    GW_SYSTEM *system = &GwSystem;

    if (++system->current_player_index >= 4) {
        system->current_player_index = 0;
    }
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        MBPlayerForwardSet(i);
        MBMotionSet(player->player_obj, -1, 2);
        MBPlayerPosFixSet(i, 1);
    }
    MBCameraZoomSet(1.0f);
}

void func_8010681C_w10(Vec *arg0) {
    func_800FF840_shared_board(arg0);
}

void func_80106838_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBTelopCreate(GwSystem.current_player_index));
    HuPrcChildWatch();
}

void func_8010687C_w10(s16 arg0) {
    Process *process;
    Process *child;
    GW_SYSTEM *system = &GwSystem;

    func_800DCD64_shared_board(system->current_player_index, arg0);
    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
    child = func_800DD6C4_shared_board(system->current_player_index);
    HuPrcChildWatch();
    HuPrcChildLink(process, child);
    HuPrcChildWatch();
}

void func_80106908_w10(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    SpaceData *space;
    Vec dir;
    s16 walkNum;
    s16 masuId = 0;
    s16 clink;
    s16 cidx;
    s32 i;

    walkNum = func_800DCD9C_shared_board(system->current_player_index);
    MBPlayerMotionSet(-1, 0, 2);
    while (walkNum != 0) {
        clink = player->clink;
        cidx = player->cidx;
        player->clink = player->nlink;
        player->cidx = player->nidx;
        for (i = 0; i < 4; i++) {
            MBPlayerPosFixSet(i, 10);
        }
        player->clink = clink;
        player->cidx = cidx;

        space = GET_SPACE_FROM_LINK(player->nlink, player->nidx);
        if ((space->unk_02 & 0x8000) || func_800F9A68_shared_board(system->current_player_index)) {
            PlayerFXPlay(0x3A, system->current_player_index);
            MBPlayerMotionSet(-1, 2, 0);
            player->player_obj->velocity.y = 4.0f;
            player->player_obj->velocity.z = -0.5f;
            switch (system->walk_speed) {
                case 0:
                    player->player_obj->velocity.y = 8.0f;
                    player->player_obj->velocity.z = -2.0f;
                    MBPlayerPosMoveSet(system->current_player_index, 7);
                    break;
                case 1:
                    player->player_obj->velocity.y = 4.0f;
                    player->player_obj->velocity.z = -0.5f;
                    MBPlayerPosMoveSet(system->current_player_index, 15);
                    break;
                case 2:
                    player->player_obj->velocity.y = 2.0f;
                    player->player_obj->velocity.z = -0.125f;
                    MBPlayerPosMoveSet(system->current_player_index, 30);
                    break;
            }
        } else {
            if (player->player_obj->unk46 != 0) {
                MBPlayerMotionSet(-1, 0, 2);
            }
            switch (system->walk_speed) {
                case 0:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 2.0f);
                    MBPlayerPosMoveSet(system->current_player_index, 5);
                    break;
                case 1:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.0f);
                    MBPlayerPosMoveSet(system->current_player_index, 10);
                    break;
                case 2:
                    Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 0.75f);
                    MBPlayerPosMoveSet(system->current_player_index, 15);
                    break;
            }
            Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], 1.0f);
        }

        player->clink = player->nlink;
        player->cidx = player->nidx;
        player->nidx++;
        masuId = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        space = MBMasuGet(masuId);
        MBMasuCurSet(masuId);

        switch (space->space_type) {
            case SPACE_BLUE:
            case SPACE_RED:
            case SPACE_HAPPENING:
            case SPACE_CHANCE_TIME:
            case SPACE_ITEM:
            case SPACE_BANK:
            case SPACE_BATTLE:
            case SPACE_BOWSER:
            case SPACE_GAME_GUY:
                func_800DBFBC_shared_board(system->current_player_index);
                walkNum--;
                func_800EB97C_shared_board(masuId);
                break;
        }

        if (walkNum != 0) {
            switch (space->space_type) {
                case SPACE_STAR:
                    HuAudFXPlay(0x123);
                    break;
                case SPACE_BLUE:
                case SPACE_RED:
                case SPACE_HAPPENING:
                case SPACE_CHANCE_TIME:
                case SPACE_ITEM:
                case SPACE_BANK:
                case SPACE_BATTLE:
                case SPACE_BOWSER:
                case SPACE_GAME_GUY:
                    HuAudFXPlay(0x101);
                    break;
            }
        } else {
            switch (space->space_type) {
                case SPACE_HAPPENING:
                case SPACE_ITEM:
                    HuAudFXPlay(0x108);
                    break;
                case SPACE_BLUE:
                    HuAudFXPlay(0x121);
                    break;
                case SPACE_RED:
                    HuAudFXPlay(0x122);
                    break;
                case SPACE_BOWSER:
                    HuAudFXPlay(0x124);
                    break;
                case SPACE_CHANCE_TIME:
                    HuAudFXPlay(0x12F);
                    break;
                case SPACE_BATTLE:
                case SPACE_GAME_GUY:
                    HuAudFXPlay(0x12E);
                    break;
                case SPACE_BANK:
                    HuAudFXPlay(0x130);
                    break;
                case SPACE_STAR:
                    HuAudFXPlay(0x123);
                    break;
            }
        }
        MBMasuEventCall(masuId, 1);
    }
    MBPlayerMotionSet(-1, -1, 2);
    MBMasuEventCall(masuId, 3);
    MBVecForwardSet(&dir);
    func_800ED1E4_shared_board(&player->player_obj->rot, &dir, &player->player_obj->rot, 8);
    func_800F591C_shared_board(system->current_player_index);
}

void func_80106DEC_w10(void) {
    GW_SYSTEM *system = &GwSystem;
    GW_PLAYER *player = MBPlayerGet(CUR_PLAYER);
    SpaceData *space = GET_SPACE_FROM_LINK(player->clink, player->cidx);

    MBPlayerMasuColorSet(-1, space->space_type);
    MBStatusColorSet(system->current_player_index, player->color);
    switch (space->space_type) {
        case SPACE_BLUE:
            MBCoinChangeCreate(system->current_player_index, 3);
            MBCoinTakeCreate(system->current_player_index, 3);
            HuPrcSleep(30);
            break;
        case SPACE_RED:
            MBCoinChangeCreate(system->current_player_index, -3);
            MBCoinTakeCreate(system->current_player_index, -3);
            HuPrcSleep(30);
            break;
    }
}

void func_80106ED8_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

void func_80106F40_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
}

void func_80106F7C_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinMesSet(guide->amount, mess, -1, -1);
    func_80060C14_main(guide->amount, 1);
    while (HuWinStatGet(guide->amount) != 0) {
        HuPrcVSleep();
    }
}

void func_80106FE0_w10(UnkMBGuideData *guide) {
    func_800EE614_shared_board(guide->amount);
    func_80060EA8_main(guide->amount, 1);
    HuWinHomeClear(guide->amount);
    HuPrcVSleep();
}

void func_80107028_w10(UnkMBGuideData *guide, u32 mess) {
    HuWinActivePlayerSet(guide->amount, 15);
    HuWinComKeySet(-1, -1, -1, -1);
    HuWinMesSet(guide->amount, mess, -1, -1);
    while (HuWinStatGet(guide->amount) != 0) {
        HuPrcVSleep();
    }
    HuWinComKeyReset();
}

void func_801070B8_w10(UnkMBGuideData *guide) {
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.6f;
    MBMotionSet(guide->obj, 0, 0);
    HuPrcSleep(3);
    while (MBMotionCheck(guide->obj) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(guide->obj, -1, 2);
}

void func_8010714C_w10(UnkMBGuideData *guide, s16 pos) {
    s32 i;
    s16 step;
    s16 curPos = guide->spriteGroup;
    Object *obj = guide->obj;

    obj->velocity.y = 4.0f;
    obj->velocity.z = -0.5f;
    step = (pos - curPos) / 14;
    for (i = 0; i < 14; i++) {
        curPos = guide->spriteGroup;
        MBGuidePosSet(guide, curPos + step, 0);
        HuPrcVSleep();
    }
    MBGuidePosSet(guide, pos, 0);
}

void func_80107228_w10(void) {
    UnkMBGuideData *guide = HuPrcCurrentGet()->user_data;
    s16 motion;

    while (TRUE) {
        HuPrcVSleep();
        if (D_8010B8FC_w10 == -1) {
            continue;
        }
        if (D_8010B8FC_w10 == -2) {
            D_8010B8FC_w10 = -1;
            MBMotionShiftSet(guide->obj, -1, 0, 10, 0);
        } else {
            MBMotionShiftSet(guide->obj, D_8010B8FC_w10, 0, 10, 0);
        }
        motion = D_8010B8FC_w10;
        D_8010B8FC_w10 = -1;
        while (MBMotionCheck(guide->obj) == 0 && D_8010B8FC_w10 == -1) {
            HuPrcVSleep();
        }
        switch (motion) {
            case 1:
                MBMotionSet(guide->obj, 3, 2);
                break;
            case 2:
                MBMotionSet(guide->obj, 4, 2);
                break;
            default:
                MBMotionSet(guide->obj, -1, 2);
                break;
        }
    }
}

void func_80107344_w10(s16 arg0) {
    D_8010B8FC_w10 = arg0;
}

void func_80107350_w10(omObjData *obj) {
    D_8010BA68_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    D_8010BA6C_w10->coords.y = -sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 3.0f;
}

void func_801073C8_w10(omObjData *obj) {
    D_8010BA70_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    D_8010BA74_w10->coords.y = sindf(obj->rot.x) * 3.0f;
    obj->rot.x += 10.0f;
}

void func_80107444_w10(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;
    s32 effect;

    D_8010BA68_w10 = MBModelCreate(9, NULL);
    D_8010BA6C_w10 = MBModelFileCreate(0x1301C8, -1, 1.0f, 0.0f, NULL);
    effect = func_8000CED8_main(0xB0004, 0xAA9);
    HuAudFXPlay(0x119);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 15.0f);
    MBModelTempAllocFree(D_8010BA68_w10);
    D_8010BA68_w10->flags |= 1;
    MBModelTempAllocFree(D_8010BA6C_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA6C_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 120.0f;
    D_8010BA6C_w10->velocity.x = 120.0f;
    while (D_8010BA68_w10->velocity.x > 50.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x -= 4.0f;
        D_8010BA6C_w10->velocity.x -= 4.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, func_80107350_w10);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (D_8010BA68_w10->velocity.x < 120.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x += 4.0f;
        D_8010BA6C_w10->velocity.x += 4.0f;
    }
    *state = 3;
    func_8000D044_main(effect);
    MBModelKill(D_8010BA68_w10);
    MBModelKill(D_8010BA6C_w10);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void func_80107780_w10(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;
    s32 effect;

    D_8010BA68_w10 = MBModelCreate(0x39, NULL);
    D_8010BA6C_w10 = MBModelFileCreate(0x130203, -1, 1.0f, 0.0f, NULL);
    effect = func_8000CED8_main(0xB0005, 0xAA9);
    HuAudFXPlay(0x11A);
    Hu3DModelCameraSet(effect, HU3D_CAM0);
    func_8000CD00_main(effect, 1.0f, 20.0f, 1.0f);
    func_8000D018_main(effect, 15.0f);
    MBModelTempAllocFree(D_8010BA68_w10);
    D_8010BA68_w10->flags |= 1;
    MBModelTempAllocFree(D_8010BA6C_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA6C_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 120.0f;
    D_8010BA6C_w10->velocity.x = 120.0f;
    while (D_8010BA68_w10->velocity.x > 50.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x -= 4.0f;
        D_8010BA6C_w10->velocity.x -= 4.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, func_80107350_w10);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (D_8010BA68_w10->velocity.x < 120.0f) {
        func_8000CFA4_main(effect, D_8010BA68_w10->coords.x, D_8010BA68_w10->velocity.x - 10.0f,
                           D_8010BA68_w10->coords.z);
        HuPrcVSleep();
        D_8010BA68_w10->velocity.x += 4.0f;
        D_8010BA6C_w10->velocity.x += 4.0f;
    }
    *state = 3;
    func_8000D044_main(effect);
    MBModelKill(D_8010BA68_w10);
    MBModelKill(D_8010BA6C_w10);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void func_80107ABC_w10(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    omObjData *bobObj;

    D_8010BA70_w10 = MBModelCreate(0xC, NULL);
    Hu3DModelScaleSet(D_8010BA70_w10->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    func_8001FDE8_main(D_8010BA70_w10->omObj1->model[0]);
    D_8010BA70_w10->flags |= 1;
    D_8010BA74_w10 = MBModelCreate(0x1F, NULL);
    Hu3DModelScaleSet(D_8010BA74_w10->omObj1->model[0], 0.0f, 0.0f, 0.0f);
    HuVecCopy3F(&D_8010BA70_w10->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_8010BA74_w10->coords, &player->player_obj->coords);
    D_8010BA70_w10->velocity.x = 120.0f;
    D_8010BA74_w10->velocity.x = 122.0f;
    while (D_8010BA70_w10->velocity.x > 30.0f) {
        HuPrcVSleep();
        D_8010BA70_w10->velocity.x -= 2.0f;
        D_8010BA74_w10->velocity.x -= 2.0f;
    }
    bobObj = omAddObj(500, 0, 0, -1, func_801073C8_w10);
    bobObj->rot.x = 180.0f;
    SET_STATE_AND_WAIT(state, 1);
    while (D_8010BA70_w10->velocity.x < 120.0f) {
        HuPrcVSleep();
        D_8010BA70_w10->velocity.x += 2.0f;
        D_8010BA74_w10->velocity.x += 2.0f;
    }
    *state = 3;
    MBModelKill(D_8010BA70_w10);
    MBModelKill(D_8010BA74_w10);
    omDelObj(bobObj);
    omDelPrcObj(NULL);
}

void func_80107D64_w10(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    GW_PLAYER *player = MBPlayerGet(-1);
    Process *process;

    D_8010BA68_w10 = MBModelCreate(0x3E, NULL);
    MBModelTempAllocFree(D_8010BA68_w10);
    HuVecCopy3F(&D_8010BA68_w10->coords, &player->player_obj->coords);
    D_8010BA68_w10->velocity.x = 100.0f;
    do {
        D_8010BA68_w10->velocity.x -= 2.0f;
        HuPrcVSleep();
    } while (D_8010BA68_w10->velocity.x >= 30.0f);
    process = func_800EDB98_shared_board(D_8010BA68_w10, 5.0f, 2.0f);
    SET_STATE_AND_WAIT(state, 1);
    omDelPrcObj(process);

    while (D_8010BA68_w10->velocity.x < 100.0f) {
        D_8010BA68_w10->velocity.x += 2.0f;
        HuPrcVSleep();
    }
    *state = 3;
    MBModelKill(D_8010BA68_w10);
    omDelPrcObj(NULL);
}

void func_80107F0C_w10(void) {
    s32 *state = HuPrcCurrentGet()->user_data;
    s16 chestModel = D_8010B918_w10 != 0 ? 0x31 : 0x30;
    Object *chest;
    Object *contents;
    s16 model;
    f32 angle;
    f32 scale;

    HuAudFXPlay(0x114);
    chest = MBModelCreate(chestModel, NULL);
    MBModelTempAllocFree(chest);
    HuVecCopyXYZ(&chest->rot, 0.0f, 0.0f, 1.0f);
    chest->scale.y = 0.0f;
    MBMotionSet(chest, -1, 1);
    func_800D9A40_shared_board(chest);
    HuVecCopy3F(&chest->coords, &MBMasuGet(0x2B)->coords);
    if (D_8010B918_w10 != 0) {
        contents = MBModelCreate(0x39, D_8010B908_w10);
    } else {
        contents = MBModelCreate(0x1B, D_8010B900_w10);
    }
    MBModelTempAllocFree(contents);
    HuVecCopy3F(&contents->rot, &chest->rot);
    HuVecCopy3F(&contents->coords, &chest->coords);
    contents->scale.y = contents->scale.x = contents->scale.z = 1.2f;
    MBModelDispOff(contents);

    scale = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (; angle > 50.0f; angle -= 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    chest->scale.y = chest->scale.x = chest->scale.z = 1.0f;

    func_800D9A40_shared_board(contents);
    MBMotionSet(chest, -1, 0);
    Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
    while (MBMotionCheck(chest) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(contents, 0, 0);
    HuAudFXPlay(D_8010B918_w10 != 0 ? 0x2A0 : 0x298);
    while (MBMotionCheck(contents) == 0) {
        HuPrcVSleep();
    }
    MBMotionSet(contents, -1, 2);
    SET_STATE_AND_WAIT(state, 1);

    HuAudFXPlay(0x115);
    MBMotionSet(chest, -1, 4);
    Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
    model = chest->omObj1->model[0];
    Hu3DMotionTimeSet(model, D_800CCF58_main[HmfModelData[model].motId].unk02);
    while (func_800D9E80_shared_board(chest) == 0) {
        HuPrcVSleep();
    }
    MBModelDispOff(contents);

    scale = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
        chest->scale.y = sindf(angle) * scale;
        chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    chest->scale.y = 0.0f;
    chest->scale.x = 0.0f;
    chest->scale.z = 0.0f;
    MBModelKill(chest);
    MBModelKill(contents);
    *state = 3;
    omDelPrcObj(NULL);
}

void func_801084CC_w10(void) {
    s32 sprites[3][4]; // [0] = rank anims, [1] = character anims, [2] = sprite groups
    s32 titleAnim;
    s32 boxAnim;
    s32 group;
    Process *process;
    s32 box;
    Unk3 *help;
    void *data;
    s32 i;
    s32 j;
    s32 count;
    s32 flag;
    s32 fading;
    s32 alpha;
    f32 angle;
    f32 step;

    process = HuPrcCurrentGet();
    data = DataRead(0x1300F7);
    titleAnim = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F8);
    sprites[0][0] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FB);
    sprites[0][1] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300F9);
    sprites[0][2] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FA);
    sprites[0][3] = HuSprAnimRead(data);
    DataClose(data);
    data = DataRead(0x1300FC);
    boxAnim = HuSprAnimRead(data);
    DataClose(data);
    for (i = 0; i < 4; i++) {
        data = DataRead((GwPlayer[i].chr + 8) | 0x210000);
        sprites[1][i] = HuSprAnimRead(data);
        DataClose(data);
    }

    group = HuSprGrpCreate(1, 5);
    HuSprGrpMemberSet(group, 0, titleAnim, 0);
    HuSprAttrReset(group, 0, 0xFFFF);
    HuSprAttrSet(group, 0, 0x1008);
    HuSprPriSet(group, 0, 0x1000);
    HuSprPosSet(group, 0, 0xA0, 0x5A);
    angle = 0.0f;
    step = 30.0f;
    count = 0;
    flag = 0;
    for (;; angle += step) {
        if (angle >= 90.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (angle >= 180.0f && angle <= 360.0f) {
            HuSprAttrSet(group, 0, 2);
        } else {
            HuSprAttrReset(group, 0, 2);
        }
        HuSprScaleSet(group, 0, 1.0f, sindf(angle >= 180.0f ? angle - 180.0f : angle));
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprAttrReset(group, 0, 2);
    HuSprScaleSet(group, 0, 1.0f, 1.0f);
    help = func_800E210C_shared_board(0x14, 0xA0, 1);

    for (i = 0; i < 4; i++) {
        box = sprites[2][i] = HuSprGrpCreate(6, 5);
        HuSprGrpMemberSet(box, 0, boxAnim, 0);
        func_800550F4_main(box, 0, 0);
        HuSprAttrReset(box, 0, 0xFFFF);
        if (D_8010BA80_w10[i] != 0) {
            HuSprAttrSet(box, 0, 8);
        } else {
            HuSprDispOff(box, 0);
        }
        HuSprPriSet(box, 0, 0x1000);
        func_800554C4_main(box, 0, -1);
        HuSprGrpMemberSet(box, 1, sprites[1][i], 0);
        func_800550F4_main(box, 1, 0);
        HuSprAttrReset(box, 1, 0xFFFF);
        if (D_8010BA80_w10[i] != 0) {
            HuSprAttrSet(box, 1, 8);
        } else {
            HuSprDispOff(box, 1);
        }
        HuSprPriSet(box, 1, 0x1000);
        HuSprPosSet(box, 1, 0, -9);
        func_800554C4_main(box, 1, 0);
        for (j = 0; j < 4; j++) {
            HuSprGrpMemberSet(box, j + 2, sprites[0][j], 0);
            func_800550F4_main(box, j + 2, 1);
            HuSprAttrReset(box, j + 2, 0xFFFF);
            if (D_8010BA80_w10[i] == j + 1) {
                HuSprAttrSet(box, j + 2, 8);
            } else {
                HuSprDispOff(box, j + 2);
            }
            HuSprPriSet(box, j + 2, 0x1000);
            HuSprPosSet(box, j + 2, 0, 9);
            func_800554C4_main(box, j + 2, 0);
        }
        HuSprPosSet(box, 0, i * 70 + 55, 200);
    }
    HuPrcSleep(20);

    angle = 90.0f;
    count = 0;
    fading = 0;
    flag = 0;
    alpha = 0xFF;
    for (;; angle += step) {
        if (angle >= 360.0f && !flag) {
            flag = 1;
            count++;
        }
        if (angle >= 360.0f) {
            flag = 0;
            angle -= 360.0f;
        }
        if (!fading && count != 0 && angle >= 90.0f && angle < 180.0f) {
            fading = 1;
        }
        if (fading) {
            alpha -= 21;
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        HuSprTPLvlSet(group, 0, alpha);
        if (count >= 2) {
            break;
        }
        HuPrcVSleep();
    }
    HuSprScaleSet(group, 0, 1.0f, 0.0f);
    HuSprGrpKill(group);
    HuSprAnimKill(titleAnim);
    process->user_data = (void *)1;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            switch (D_8010BA80_w10[i]) {
                case 0:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOff(sprites[2][i], j);
                    }
                    break;
                case 1:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 2);
                    break;
                case 2:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 3);
                    break;
                case 3:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 4);
                    break;
                case 4:
                    for (j = 0; j < 6; j++) {
                        HuSprDispOn(sprites[2][i], j);
                    }
                    for (j = 0; j < 4; j++) {
                        HuSprDispOff(sprites[2][i], j + 2);
                    }
                    HuSprDispOn(sprites[2][i], 5);
                    break;
                default:
                    goto end;
            }
        }
        HuPrcVSleep();
    }
end:
    MBHelpWinKill(help);
    HuSprAnimKill(boxAnim);
    for (i = 0; i < 4; i++) {
        HuSprAnimKill(sprites[0][i]);
        HuSprAnimKill(sprites[1][i]);
        HuSprGrpKill(sprites[2][i]);
    }
    omDelPrcObj(NULL);
}

void func_80108F28_w10(void) {
    Object *obj;

    D_8010BA94_w10 = 0;
    obj = MBModelCreate(0x4E, NULL);
    D_8010BA90_w10 = obj;
    MBModelTempAllocFree(obj);
    HuVecCopy3F(&obj->coords, &MBMasuGet(0x2E)->coords);
    HuVecCopyXYZ(&obj->rot, 0.0f, 0.0f, -1.0f);
    obj->velocity.x = 15.0f;
    while (D_8010BA94_w10 == 0) {
        HuPrcVSleep();
    }
    while (D_8010BA94_w10 != 0) {
        obj->omObj1->rot.z -= 15.0f;
        if (obj->omObj1->rot.z < 0.0f) {
            obj->omObj1->rot.z += 360.0f;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80109050_w10(void) {
    W10RunnerData *data = HuPrcCurrentGet()->user_data;
    Object *target = D_8010BA90_w10;
    GW_PLAYER *player = MBPlayerGet(data->player);
    Object *playerObj = player->player_obj;
    s32 slot = data->slot;
    Process *process = HuPrcCurrentGet();
    SpaceData *start;
    SpaceData *end;
    Vec pos;

    func_800ED20C_shared_board(data->player, 8, 0x2E);
    while (HuVecDistance(&playerObj->coords, &target->coords) > slot * 20.0f + 30.0f + 20.0f) {
        HuPrcVSleep();
    }
    D_8010BA80_w10[data->player] = 2;
    while (HuVecDistance(&playerObj->coords, &target->coords) > slot * 20.0f + 30.0f) {
        HuPrcVSleep();
    }
    if (data->player == 1) {
        D_8010BA80_w10[1] = 3;
        PlayerFXPlay(0x274, data->player);
        PlayerFXPlay(0x3A, data->player);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 2, 0);
        } else {
            MBMotionSet(playerObj, 2, 0);
        }
        func_800EE688_shared_board(playerObj, 7.0f, -0.45f);
        func_800EE6C0_shared_board(playerObj);
        PlayerFXPlay(0x31, data->player);
        func_800F2388_shared_board(data->player, -1, 0, 5, 2);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
    } else {
        D_8010BA80_w10[data->player] = 4;
        PlayerFXPlay(0x286, data->player);
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, 1, 2);
        } else {
            MBMotionSet(playerObj, 1, 2);
        }
        start = MBMasuGet(0x26);
        end = MBMasuGet(0x10);
        HuVecCopy3F(&pos, &start->coords);
        MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
        HuPrcChildLink(process, func_800ED75C_shared_board(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
        HuPrcChildWatch();
        HuVecCopy3F(&pos, &end->coords);
        pos.x += D_8010B91C_w10[slot][0];
        pos.z += D_8010B91C_w10[slot][1];
        MBVecDirGet(&playerObj->coords, &pos, &playerObj->rot);
        HuPrcChildLink(process, func_800ED5E0_shared_board(&playerObj->coords, &pos, &playerObj->coords, 2.0f));
        HuPrcChildWatch();
        if (data->player == GwSystem.current_player_index) {
            MBPlayerMotionSet(-1, -1, 2);
        } else {
            MBMotionSet(playerObj, -1, 2);
        }
        HuVecCopyXYZ(&pos, 0.0f, 0.0f, 1.0f);
        func_800ED128_shared_board(&player->player_obj->rot, &pos, &player->player_obj->rot, 5);
        HuPrcSleep(5);
    }
    omDelPrcObj(NULL);
}

void func_80109444_w10(void) {
    s32 state;
    Process *process;
    W10SprGroup *spr;
    SpaceData *from;
    SpaceData *to;
    Object *chest;
    Object *contents;
    Object *box;
    Process *runner;
    W10RunnerData *data;
    s16 model;
    s16 sfx;
    s32 i;
    s32 alpha;
    f32 angle;
    f32 scale;

    process = HuPrcCurrentGet();
    GwSystem.boardData.halfWordBytes[0] = 0;
    func_80105F20_w10();
    D_8010BA64_w10 = MBGuideCreate(NULL, 0);
    HuWinMesPalSet(D_8010BA64_w10->amount, 4, 0, 0xB0, 0xC0);
    HuVecCopyXYZ(&D_8010BA64_w10->obj->scale, 1.1f, 1.1f, 1.1f);
    D_8010BA64_w10->obj->coords.x -= 1.0f;
    D_8010BA64_w10->obj->coords.y -= 2.0f;
    MBGuideFaceCreate(D_8010BA64_w10->obj, 2, 0xF, D_8010B7F8_w10[0]);
    MBGuidePosSet(D_8010BA64_w10, 0x42, 0);
    func_8005B63C_main(D_8010BA64_w10->amount, 0x40, 0x40);
    func_801066E8_w10();
    func_80106730_w10();
    HuPrcSleep(3);
    while (WipeStatGet() != 0) {
        HuPrcVSleep();
    }
    HuPrcSleep(3);

    func_80106ED8_w10(D_8010BA64_w10, 0x1608);
    func_80106838_w10();
    func_80106ED8_w10(D_8010BA64_w10, 0x1609);
    func_8010687C_w10(1);
    func_80106ED8_w10(D_8010BA64_w10, 0x160A);
    func_80106908_w10();
    HuPrcVSleep();
    func_80106ED8_w10(D_8010BA64_w10, 0x160B);
    spr = func_80105FDC_w10(0, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x160C);
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(2);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(1, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x160D);
    func_80107344_w10(-2);
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(3);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(2, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x160E);
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(5);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(3, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x160F);
    func_801061E8_w10(spr);
    func_80106DEC_w10();
    HuPrcSleep(10);
    func_80106ED8_w10(D_8010BA64_w10, 0x1610);

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_801066E8_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(4);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(4, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x1611);
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(5);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(5, 100, 90);
    func_80106ED8_w10(D_8010BA64_w10, 0x1612);
    state = 0;
    omAddPrcObj(func_80107444_w10, 0x4800, 0, 0)->user_data = &state;
    do {
        HuPrcVSleep();
    } while (state == 0);
    func_80106ED8_w10(D_8010BA64_w10, 0x1613);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    HuPrcSleep(4);
    state = 0;
    omAddPrcObj(func_80107780_w10, 0x4800, 0, 0)->user_data = &state;
    do {
        HuPrcVSleep();
    } while (state == 0);
    func_80106ED8_w10(D_8010BA64_w10, 0x1614);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(1);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(9, 100, 90);
    state = 0;
    omAddPrcObj(func_80107ABC_w10, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x1615);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(1);
    func_80106908_w10();
    HuPrcVSleep();
    spr = func_80105FDC_w10(6, 100, 90);
    state = 0;
    omAddPrcObj(func_80107D64_w10, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x1616);
    state = 2;
    while (state == 2) {
        HuPrcVSleep();
    }
    func_801061E8_w10(spr);
    func_80106DEC_w10();

    func_80105F64_w10();
    func_80106774_w10();
    func_8010681C_w10(NULL);
    func_80105FA0_w10();
    func_80106730_w10();
    func_80106838_w10();
    func_8010687C_w10(1);
    func_80106908_w10();
    func_8010AF68_w10(D_8010BA64_w10);
    func_80106DEC_w10();
    func_800F7108_shared_board();
    func_80106ED8_w10(D_8010BA64_w10, 0x161A);

    MBStatusDispMoveSet(4);
    func_8010714C_w10(D_8010BA64_w10, -30);
    while (func_800F5278_shared_board()) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x161B);
    HuPrcChildLink(process, MBMgCallTutorialCreate());
    HuPrcChildWatch();
    MBStatusColorSet(0, 1);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 1);
    MBStatusColorSet(3, 1);
    HuPrcSleep(30);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (func_800F5278_shared_board()) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x161C);
    MBVsSprKill();
    MBStatusColorSet(0, 2);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 2);
    MBStatusColorSet(3, 1);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (func_800F5278_shared_board()) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x161D);
    MBVsSprKill();
    MBStatusColorSet(0, 1);
    MBStatusColorSet(1, 2);
    MBStatusColorSet(2, 2);
    MBStatusColorSet(3, 2);
    MBStatusDispMoveSet(2);
    MBVsSprCreate();
    while (func_800F5278_shared_board()) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x161E);
    MBStatusColorSet(0, 2);
    MBStatusColorSet(1, 1);
    MBStatusColorSet(2, 1);
    MBStatusColorSet(3, 1);
    func_80106ED8_w10(D_8010BA64_w10, 0x161F);
    HuPrcSleep(15);
    HuPrcSleep(1);
    GwSystem.minigame_index = -1;
    MBMgCallListCreate(-1);
    func_80106ED8_w10(D_8010BA64_w10, 0x1620);
    func_800E00EC_shared_board();
    MBStatusDispMoveSet(5);
    while (GwSystem.minigame_index == -1) {
        HuPrcVSleep();
    }
    MBVsSprKill();
    MBMgCallClose();
    func_80106ED8_w10(D_8010BA64_w10, 0x1621);
    MBStatusHideAll();
    func_800E6FCC_shared_board();
    func_8001FDE8_main(MBPlayerGet(0)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBPlayerGet(1)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBPlayerGet(2)->player_obj->omObj1->model[0]);
    func_8001FDE8_main(MBPlayerGet(3)->player_obj->omObj1->model[0]);
    func_8010714C_w10(D_8010BA64_w10, 0x69);
    func_80106ED8_w10(D_8010BA64_w10, 0x1622);

    {
        Vec dir;

        func_80106670_w10(0x2D);
        func_8010669C_w10();
        from = MBMasuGet(0x2D);
        to = MBMasuGet(0x15);
        HuAudFXPlay(0x114);
        chest = MBModelCreate(0x32, NULL);
        MBModelTempAllocFree(chest);
        HuVecSubtract(&dir, &to->coords, &from->coords);
        MBVecNormalize(&dir);
        HuVecCopy3F(&chest->rot, &dir);
        chest->scale.y = 0.0f;
        HuVecCopy3F(&chest->coords, &from->coords);
        MBMotionSet(chest, -1, 1);
        func_800D9A40_shared_board(chest);
        contents = MBModelCreate(0x35, D_8010B910_w10);
        MBModelTempAllocFree(contents);
        HuVecCopy3F(&contents->rot, &dir);
        HuVecCopy3F(&contents->coords, &from->coords);
        contents->scale.y = contents->scale.x = contents->scale.z = 1.2f;
        MBModelDispOff(contents);

        scale = 1.0f / sindf(50.0f);
        for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        for (; angle > 50.0f; angle -= 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        chest->scale.z = chest->scale.x = chest->scale.y = 1.0f;

        func_800D9A40_shared_board(contents);
        MBMotionSet(chest, -1, 0);
        Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
        while (MBMotionCheck(chest) == 0) {
            HuPrcVSleep();
        }
        HuAudFXPlay(0x259);
        MBMotionSet(contents, 0, 0);
        while (MBMotionCheck(contents) == 0) {
            HuPrcVSleep();
        }
        MBMotionSet(contents, -1, 2);
        func_80106ED8_w10(D_8010BA64_w10, 0x1623);
        HuPrcSleep(10);

        HuAudFXPlay(0x115);
        MBMotionSet(chest, -1, 4);
        Hu3DMotionSpeedSet(chest->omObj1->model[0], 1.2f);
        model = chest->omObj1->model[0];
        Hu3DMotionTimeSet(model, D_800CCF58_main[HmfModelData[model].motId].unk02);
        while (func_800D9E80_shared_board(chest) == 0) {
            HuPrcVSleep();
        }
        MBModelDispOff(contents);

        scale = 1.0f / sindf(50.0f);
        for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
            chest->scale.y = sindf(angle) * scale;
            chest->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
            chest->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
            HuPrcVSleep();
        }
        chest->scale.y = 0.0f;
        chest->scale.x = 0.0f;
        chest->scale.z = 0.0f;
        MBModelKill(chest);
        MBModelKill(contents);
    }

    func_80106670_w10(0x2A);
    func_8010669C_w10();
    func_80106ED8_w10(D_8010BA64_w10, 0x1624);
    HuPrcSleep(10);
    state = 0;
    D_8010B918_w10 = 0;
    omAddPrcObj(func_80107F0C_w10, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    func_80106F7C_w10(D_8010BA64_w10, 0x1625);
    state = 2;
    while (state != 3) {
        HuPrcVSleep();
    }
    state = 0;
    D_8010B918_w10 = 1;
    omAddPrcObj(func_80107F0C_w10, 0x4800, 0, 0)->user_data = &state;
    while (state == 0) {
        HuPrcVSleep();
    }
    func_80107028_w10(D_8010BA64_w10, 0x1626);
    state = 2;
    while (state != 3) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x1627);
    func_80106ED8_w10(D_8010BA64_w10, 0x1628);

    func_80106670_w10(0x25);
    func_8010669C_w10();
    HuAudFXPlay(0x159);
    func_80106ED8_w10(D_8010BA64_w10, 0x1629);
    HuPrcSleep(10);
    func_80106670_w10(0x24);
    func_8010669C_w10();
    HuAudFXPlay(0x125);
    box = MBModelCreate(0x33, NULL);
    Hu3DModelRemakeStatic(box->omObj1->model[0]);
    MBModelTempAllocFree(box);
    HuVecCopyXYZ(&box->rot, 1.0f, 0.0f, 0.0f);
    box->scale.y = 0.0f;
    HuVecCopy3F(&box->coords, &MBMasuGet(0x24)->coords);
    MBMotionSet(box, -1, 1);
    MBModelDispOn(box);

    scale = 1.0f / sindf(50.0f);
    for (angle = 0.0f; angle < 90.0f; angle += 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
        box->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
        HuPrcVSleep();
    }
    for (; angle > 50.0f; angle -= 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.99f + 0.01f;
        box->scale.z = sindf(angle) * scale * 0.99f + 0.01f;
        HuPrcVSleep();
    }
    box->scale.z = box->scale.x = box->scale.y = 1.0f;
    MBMotionSet(box, -1, 0);
    Hu3DMotionSpeedSet(box->omObj1->model[0], 1.2f);
    while (MBMotionCheck(box) == 0) {
        HuPrcVSleep();
    }

    HuAudFXPlay(0x257);
    MBModelDispOn(D_8010BA2C_w10);
    for (alpha = 0; alpha < 256; alpha += 12) {
        func_8001F9E4_main(D_8010BA2C_w10->omObj1->model[0], alpha);
        func_8001F9E4_main(D_8010BA2C_w10->omObj2->model[0], alpha);
        HuPrcVSleep();
    }
    func_8001F9E4_main(D_8010BA2C_w10->omObj1->model[0], 0xFF);
    func_8001F9E4_main(D_8010BA2C_w10->omObj2->model[0], 0xFF);
    func_80106ED8_w10(D_8010BA64_w10, 0x162A);
    for (alpha = 255; alpha >= 0; alpha -= 12) {
        func_8001F9E4_main(D_8010BA2C_w10->omObj1->model[0], alpha);
        func_8001F9E4_main(D_8010BA2C_w10->omObj2->model[0], alpha);
        HuPrcVSleep();
    }
    func_8001F9E4_main(D_8010BA2C_w10->omObj1->model[0], 0);
    func_8001F9E4_main(D_8010BA2C_w10->omObj2->model[0], 0);
    MBModelDispOff(D_8010BA2C_w10);

    HuAudFXPlay(0x126);
    MBMotionSet(box, -1, 4);
    Hu3DMotionSpeedSet(box->omObj1->model[0], 1.2f);
    model = box->omObj1->model[0];
    Hu3DMotionTimeSet(model, D_800CCF58_main[HmfModelData[model].motId].unk02);
    while (func_800D9E80_shared_board(box) == 0) {
        HuPrcVSleep();
    }
    scale = 1.0f / sindf(50.0f);
    for (angle = 50.0f; angle < 90.0f; angle += 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        box->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    for (angle = 90.0f; angle > 0.0f; angle -= 11.25f) {
        box->scale.y = sindf(angle) * scale;
        box->scale.x = sindf(angle) * scale * 0.2f + 0.8f;
        box->scale.z = sindf(angle) * scale * 0.2f + 0.8f;
        HuPrcVSleep();
    }
    box->scale.y = 0.0f;
    box->scale.x = 0.0f;
    box->scale.z = 0.0f;
    MBModelKill(box);

    func_8010714C_w10(D_8010BA64_w10, -30);
    func_80106670_w10(0x22);
    func_8010669C_w10();
    D_8010BA20_w10 = 1;
    for (i = 0; i < 4; i++) {
        D_8010BA80_w10[i] = 0;
    }
    D_8010BA78_w10 = omAddPrcObj(func_801084CC_w10, 0x4800, 0, 0);
    while (D_8010BA78_w10->user_data == NULL) {
        HuPrcVSleep();
    }
    func_80106ED8_w10(D_8010BA64_w10, 0x162B);
    func_80106ED8_w10(D_8010BA64_w10, 0x162C);
    D_8010BA80_w10[0] = 1;
    D_8010BA80_w10[1] = 1;
    D_8010BA80_w10[2] = 1;

    runner = omAddPrcObj(func_80109050_w10, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 0;
    data->unk4 = 0;
    data->slot = 0;
    data->unkC = 0;
    runner = omAddPrcObj(func_80109050_w10, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 1;
    data->unk4 = 0;
    data->slot = 0;
    data->unkC = 0;
    runner = omAddPrcObj(func_80109050_w10, 0x4800, 0, 0x40);
    runner->user_data = data = HuMemMemoryAlloc(runner->heap, 0x20);
    data->player = 2;
    data->unk4 = 0;
    data->slot = 1;
    data->unkC = 0;

    {
        Vec pos;
        Object *target;

        sfx = HuAudFXPlay(0x185);
        D_8010BA94_w10 = 1;
        from = MBMasuGet(0x26);
        HuVecCopy3F(&pos, &from->coords);
        pos.x += 100.0f;
        target = D_8010BA90_w10;
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&target->coords, &pos, &target->coords, 2.0f));
        func_80106670_w10(-2);
        HuVecCopy3F(&D_8010BA58_w10, &MBMasuGet(0x22)->coords);
        MBCameraFocusVecSet(&D_8010BA58_w10);
        HuPrcChildLink(HuPrcCurrentGet(), func_800ED5E0_shared_board(&D_8010BA58_w10, &from->coords,
                                                                     &D_8010BA58_w10, 2.0f));
        HuPrcChildWatch();
        func_8004AEF0_main(sfx, 30);
    }
    D_8010BA80_w10[0] = -1;
    D_8010BA20_w10 = 0;

    func_8010714C_w10(D_8010BA64_w10, 0x69);
    func_80106ED8_w10(D_8010BA64_w10, 0x162D);
    func_80106314_w10(0xA0, 0x4C);
    HuPrcSleep(10);
    func_80106230_w10(0, 0xA0, 0x4C);
    func_80106ED8_w10(D_8010BA64_w10, 0x162E);
    func_8010649C_w10();
    func_80106230_w10(1, 0xA0, 0x4C);
    func_80106ED8_w10(D_8010BA64_w10, 0x162F);
    func_8010649C_w10();
    func_80106230_w10(2, 0xA0, 0x4C);
    func_80106ED8_w10(D_8010BA64_w10, 0x1630);
    func_8010649C_w10();
    HuPrcSleep(10);
    func_801064C8_w10();
    HuPrcSleep(10);
    func_80106ED8_w10(D_8010BA64_w10, 0x1631);
    func_80106ED8_w10(D_8010BA64_w10, 0x1632);
    MBGuideFaceSet(D_8010BA64_w10->obj, D_8010B810_w10[0]);
    HuPrcSleep(30);
    HuAudSeqFadeOut(60);
    WipeCreateOut(2, 16);
    WipeColorSet(0xFF, 0xFF, 0xFF);
    HuPrcSleep(16);
    MBGuideKill(D_8010BA64_w10);
    MBExit();
    func_800F884C_shared_board();
    omOvlReturnEx(1);
    omOvlKill();
    HuPrcVSleep();
}

void func_8010AF68_w10(UnkMBGuideData *guide) {
    GW_SYSTEM *system = &GwSystem;
    Process *process;
    Process *proc;

    process = HuPrcCurrentGet();
    HuPrcChildLink(process, MBCameraZoomMotStart(1.6f));
    proc = func_800DDDD4_shared_board(system->current_player_index);
    func_800DE858_shared_board();
    HuPrcChildWatch();
    func_80106F40_w10(guide, 0x1617);
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    func_80106FE0_w10(guide);
    func_800DE868_shared_board();
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();

    proc = func_800DE7E4_shared_board(system->current_player_index);
    func_800DE858_shared_board();
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();
    func_80106ED8_w10(guide, 0x1618);

    proc = func_800DE414_shared_board(system->current_player_index, 0);
    func_800DE858_shared_board();
    func_800DE868_shared_board();
    while (!func_800DE84C_shared_board()) {
        HuPrcVSleep();
    }
    HuPrcChildLink(process, proc);
    HuPrcChildWatch();
    func_80106ED8_w10(guide, 0x1619);

    HuPrcChildLink(process, MBCameraZoomMotStart(1.3f));
    HuPrcChildWatch();
    HuPrcSleep(1);
}

s16 func_8010B12C_w10(s32 player) {
    UnkBoard8 *dimmer;
    UnkBoard8 *icon;
    void *data;
    s16 size[2];
    s16 win;
    s16 choice;

    func_8004A9DC_main(0x60);
    dimmer = func_800F2C48_shared_board(1, 0);
    data = DataRead(0x13025D);
    dimmer->model[0] = HuSprAnimRead(data);
    HuSprGrpMemberSet(dimmer->spriteGroup, 0, dimmer->model[0], 0);
    HuSprPriSet(dimmer->spriteGroup, 0, 9);
    HuSprAttrSet(dimmer->spriteGroup, 0, 0x1000);
    HuSprPosSet(dimmer->spriteGroup, 0, 0xA0, 0x78);
    HuSprScaleSet(dimmer->spriteGroup, 0, 40.0f, 30.0f);
    func_80055484_main(dimmer->spriteGroup, 0, 0, 0, 0, 0xC0);
    DataClose(data);

    icon = func_800F2C48_shared_board(2, 0);
    data = DataRead(0x130009);
    icon->model[0] = HuSprAnimRead(data);
    DataClose(data);
    HuSprGrpMemberSet(icon->spriteGroup, 0, icon->model[0], 0);
    HuSprPriSet(icon->spriteGroup, 0, 8);
    HuSprAttrSet(icon->spriteGroup, 0, 0x1000);
    HuSprPosSet(icon->spriteGroup, 0, 0x9E, 0x78);
    HuSprColorSet(icon->spriteGroup, 0, 0x89, 0xCA, 0xB2);

    HuWinMesMaxSizeGet(1, size, 0x1633);
    win = HuWinCreate(0x49, 0x4B, size[0], size[1], 0, 2);
    HuWinPriSet(win, 5);
    HuWinBGTPLvlSet(win, 0);
    func_80060144_main(win);
    HuWinMesPalSet(win, 7, 0, 0, 0xE0);
    HuWinMesPalSet(win, 0, 0x89, 0xCA, 0xB2);
    HuWinMesPalSet(win, 4, 0, 0x80, 0);
    HuWinBGColSet(win, 0x89, 0xCA, 0xB2);
    HuWinMesSet(win, 0x1633, -1, -1);
    HuWinMesSpeedSet(win, 0);
    while (HuWinStatGet(win) != 0) {
        HuPrcVSleep();
    }
    HuWinActivePlayerSet(win, 1 << player);
    choice = HuWinChoiceGet(win, 0, 0);
    HuWinKill(win);
    func_8004A9DC_main(0x7F);
    func_800F2CA4_shared_board(dimmer);
    func_800F2CA4_shared_board(icon);
    return choice == 1;
}

void func_8010B434_w10(void) {
    Vec2f pos;
    s32 player;
    s32 i;

    D_8010BA20_w10 = 0;
    while (TRUE) {
        HuPrcVSleep();
        if (WipeStatGet() != 0 || wipeMode == 3) {
            continue;
        }
        player = MBPlayerTurnGet();
        for (i = 0; i < 4; i++) {
            if (!(D_800C9520_main[i] & START_BUTTON) || D_8010BA20_w10 != 0) {
                continue;
            }
            func_800DE874_shared_board(player);
            MBCameraPos2DGet(&pos);
            MBCameraPos2DSet(&pos);
            D_800CB99C_main = 1;
            omAllPause();
            HmfPauseF = 1;
            if (func_8010B12C_w10(i)) {
                HuAudSeqFadeOut(0x5A);
                WipeCreateOut(0, 0x10);
                HuPrcSleep(0x11);
                omDelPrcObj(D_8010BA28_w10);
                MBExit();
                func_800F884C_shared_board();
                omOvlReturnEx(1);
                omOvlKill();
                HuPrcVSleep();
            }
            HmfPauseF = 0;
            omAllUPause();
            D_800CB99C_main = 0;
            func_800DE8D8_shared_board(player);
            break;
        }
    }
}

void func_8010B5A4_w10(void) {
    Vec dir;
    SpaceData *space;
    GW_PLAYER *player;
    s16 spaceIdx;
    s32 i;

    Hu3DCamInit(2);
    omInitObjMan(0x50, 0x28);
    func_8004A208_main();
    HmfLightMaxSet(1);
    HmfLightColorSet(0, 0x78, 0x78, 0x78);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    HmfLightDirSet(1, -100.0f, 100.0f, 300.0f);
    MBObjectSetup(0x15, 0x240, 0, 0);
    space = MBMasuGet(0x2A);
    MBVecDirGet(&space->coords, &MBMasuGet(0x2B)->coords, &dir);
    MBMasuArrowAngleAdd(MBVecAngleGet(&dir) + 180.0f);
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->coin = 10;
    }
    func_80105B70_w10();
    func_80105C28_w10();
    func_80105D6C_w10();
    MBMasuEventTblAdd(D_8010B8B0_w10);
    for (i = 0; i < 4; i++) {
        player = MBPlayerGet(i);
        spaceIdx = MBMasuLinkMasuIdGet(player->clink, player->cidx);
        MBPlayerPosMasuSet(i, spaceIdx);
        MBPlayerForwardSet(i);
    }
    func_800EBDAC_shared_board();
    func_800E6FBC_shared_board();
    func_800E9730_shared_board(1.0f);
    MBCameraSpeedSet(-1.0f);
    MBCameraPos3DSet(&MBPlayerGet(-1)->player_obj->coords);
    omAddPrcObj(func_80109444_w10, 0xEFFF, 0, 0);
    omAddPrcObj(func_80106574_w10, 0x1005, 0, 0);
    omPrcSetStatBit(omAddPrcObj(func_8010B434_w10, 0x1005, 0, 0), OM_STAT_NOALLPAUSE);
    omAddPrcObj(func_80108F28_w10, 0x4800, 0, 0);
}
