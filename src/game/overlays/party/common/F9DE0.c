#include "common_board.h"
#include "105D50.h"
#include "ECA50.h"
#include "FA250.h"
#include "F9DE0.h"

// TODO: properly split data/rodata in F5E80.c and F9DE0.c

u32 D_801011A0_shared_board[] = { 7, 0xA004D, 0xA004D, 0xA004E, 0xA0051, 0xA0052, 0xA0050, 0xA0058 };
extern s16 D_80102DA0_shared_board;
extern Object *D_80105710_shared_board;

// void MBKSuitKill(void);
// void Hu3DModelObjCopy(s16, s32, s16, const char*);
// void func_800EB24C_shared_board(s16 arg0, s8 *chainOut, s8 *linkOut);
// void MBMotionKill(s16 arg0);
// s16 func_800D8E88_shared_board(s32);

static void MBKSuitMain(omObjData *arg0) {
    GW_PLAYER *player;

    player = MBPlayerGet(arg0->work[0]);
    HuVecCopy3F(&D_801011FC_shared_board->coords, &player->player_obj->coords);
    HuVecCopy3F(&D_801011FC_shared_board->rot, &player->player_obj->rot);
    HuVecCopy3F(&D_801011FC_shared_board->scale, &player->player_obj->scale);
    D_801011FC_shared_board->velocity.x = player->player_obj->velocity.x;
    D_801011FC_shared_board->flags &= ~1;
    D_801011FC_shared_board->flags = D_801011FC_shared_board->flags | (player->player_obj->flags & 1);
}

const char D_801021F0_shared_board[] = " 1 VS 1 GAME";
const char D_80102200_shared_board[] = " BATTLE GAME";
const char D_80102210_shared_board[] = " ITEM   GAME";
const char D_80102220_shared_board[] = " 2 VS 2 GAME";
const char D_80102230_shared_board[] = " 1 VS 3 GAME";
const char D_80102240_shared_board[] = "4=PLAYER GAME";

const u8 D_80102250_shared_board[] = { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 };
const u16 D_8010225C_shared_board[] = { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 };

char *D_801011C0_shared_board[] = {
    "atama_2",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "c003_000-head_1",
    "Luigi1-atama_1",
    "c005_000-bmerge1",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
};
u32 D_801011E0_shared_board[] = { 6, 0xA0037, 0xA0033, 0xA0031, 0xA0034, 0xA0036, 0xA003C };
Object *D_801011FC_shared_board = NULL;
omObjData *D_80101200_shared_board = NULL;
u16 D_80101204_shared_board[] = {
    1, 0x4D, 2, 0x4D, 4, 0x4E, 0x36, 0x51, 0x15, 0x52, 0x32, 0x50,
    0x35, 0x58, 0x0A, 0x53, 0x70, 0x55, 0x10, 0x54, 0x1A, 0x56, 0x0F, 0x57
};

Object *MBKSuitCreate(void) {
    GW_PLAYER *player;
    omObjData *obj;
    u32 playerIndex;

    playerIndex = GwSystem.current_player_index;
    player = MBPlayerGet(CUR_PLAYER);
    MBKSuitKill();
    if (playerIndex < 4) {
        D_801011FC_shared_board = MBModelCreate(0x23, D_801011A0_shared_board);
        obj = omAddObj(0x3FFF, 0, 0, -1, MBKSuitMain);
        D_80101200_shared_board = obj;
        obj->work[0] = playerIndex & 0xFF;
        Hu3DModelObjCopy(player->player_obj->omObj1->model[0], D_801011C0_shared_board[GwPlayer[playerIndex].chr],
                           D_801011FC_shared_board->omObj1->model[0], "atama_3");
        HuVecCopy3F(&D_801011FC_shared_board->coords, &player->player_obj->coords);
    } else {
        D_801011FC_shared_board = MBModelCreate(8, D_801011E0_shared_board);
        GwPlayer[4].player_obj = D_801011FC_shared_board;
        MBModelDispOff(D_801011FC_shared_board);
    }
    return D_801011FC_shared_board;
}

void MBKSuitKill(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelKill(D_801011FC_shared_board);
        D_801011FC_shared_board = NULL;
    }
    if (D_80101200_shared_board != NULL) {
        omDelObj(D_80101200_shared_board);
        D_80101200_shared_board = NULL;
    }
}

void MBKSuitInit(void) {
    D_801011FC_shared_board = NULL;
    D_80101200_shared_board = NULL;
}

void MBKSuitClose(void) {
    MBKSuitKill();
}

void MBKSuitMotionSet(s16 arg0, s32 arg1) {
    MBMotionSet(D_801011FC_shared_board, arg0, arg1);
}

void MBKSuitMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    MBMotionShiftSet(D_801011FC_shared_board, arg0, arg1, arg2, arg3);
}

void func_800E648C_shared_board(void) {
    HuVecCopy3F(&D_801011FC_shared_board->coords, &D_80105710_shared_board->coords);
    func_800EB24C_shared_board(D_80102DA0_shared_board, &GwPlayer[4].clink, &GwPlayer[4].clink + 1);
    func_800EB24C_shared_board(D_80102DA0_shared_board, &GwPlayer[4].nlink, &GwPlayer[4].nlink + 1);
    GwPlayer[4].nidx = GwPlayer[4].nidx + 1;
}

void func_800E6500_shared_board(s16 arg0) {
    D_80102DA0_shared_board = arg0;
}

void MBKSuitDispOn(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelDispOff(D_801011FC_shared_board);
    }
}

void MBKSuitDispOff(void) {
    if (D_801011FC_shared_board != NULL) {
        MBModelDispOn(D_801011FC_shared_board);
    }
}

void MBKSuitMotionLoad(s32 arg0, s32 arg1) {
    omObjData *objData;
    s16 motion;
    s32 dataNum;
    u32 i;
    Object *obj = D_801011FC_shared_board;

    objData = obj->omObj1;

    for (i = 0; i < ARRAY_COUNT(D_80101204_shared_board); i += 2) {
        if (D_80101204_shared_board[i] == arg1) {
            break;
        }
    }

    dataNum = D_80101204_shared_board[i + 1] | 0x000A0000;
    motion = objData->motion[arg0];

    if ((motion != -1) && (obj->unk46 != arg0)) {
        MBMotionKill(motion);
    }

    objData->motion[arg0] = func_800D8E88_shared_board(dataNum);
}
