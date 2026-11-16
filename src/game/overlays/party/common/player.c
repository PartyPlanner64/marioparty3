#include "common_board.h"
#include "player.h"
#include "pause.h"
#include "model.h"
#include "ksuit.h"

u8 mbComLevelTbl[] = { 0, 1, 2, 3 };

u32 mbMarioMotTbl[] = {
    7,
    0x00020001,
    0x00020002,
    0x00020004,
    0x00020036,
    0x00020015,
    0x00020032,
    0x00020035,
};

u32 mbLuigiMotTbl[] = {
    7,
    0x00030001,
    0x00030002,
    0x00030004,
    0x00030036,
    0x00030015,
    0x00030032,
    0x00030035
};

u32 mbPeachMotTbl[] = {
    7,
    0x00070001,
    0x00070002,
    0x00070004,
    0x00070036,
    0x00070015,
    0x00070032,
    0x00070035,
};

u32 mbYoshiMotTbl[] = {
    7,
    0x00040001,
    0x00040002,
    0x00040004,
    0x00040036,
    0x00040015,
    0x00040032,
    0x00040035,
};

u32 mbWarioMotTbl[] = {
    7,
    0x00050001,
    0x00050002,
    0x00050004,
    0x00050036,
    0x00050015,
    0x00050032,
    0x00050035,
};

u32 mbDonkeyMotTbl[] = {
    7,
    0x00060001,
    0x00060002,
    0x00060004,
    0x00060036,
    0x00060015,
    0x00060032,
    0x00060035,
};

u32 mbWaluigiMotTbl[] = {
    7,
    0x00020001,
    0x00020002,
    0x00020004,
    0x00020036,
    0x00020015,
    0x00020032,
    0x00020035,
};

u32 mbDaisyMotTbl[] = {
    7,
    0x00070001,
    0x00070002,
    0x00070004,
    0x00070036,
    0x00070015,
    0x00070032,
    0x00070035,
};

u32 *mbPlayerMotTbl[] = {
    mbMarioMotTbl,
    mbLuigiMotTbl,
    mbPeachMotTbl,
    mbYoshiMotTbl,
    mbWarioMotTbl,
    mbDonkeyMotTbl,
    mbWaluigiMotTbl,
    mbDaisyMotTbl
};

u8 mbPlayerModelTbl[] = {
    0, 1, 2, 3, 4, 5, 6, 7
};

u8 mbPlayerModelAltTbl[] = {
    14, 15, 16, 17, 18, 19, 20, 21
};

s16 MBPlayerTurnGet(void) {
    return GwSystem.current_player_index;
}

GW_PLAYER *MBPlayerGet(s32 playerNo) {
    if (playerNo < 0) {
        playerNo = MBPlayerTurnGet();
    }
    return &GwPlayer[playerNo];
}

s32 MBPlayerCurrentCheck(s16 playerNo) {
    if (playerNo == GwSystem.current_player_index) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 MBPlayerComCheck(s16 playerNo) {
    return MBPlayerGet(playerNo)->stat & PLAYER_IS_CPU;
}

void MBPlayerCoinAdd(s32 playerNo, s32 amount) {
    GW_PLAYER *player;

    player = MBPlayerGet(playerNo);
    player->coin = player->coin + amount;
    if (player->coin > 999) {
        player->coin = 999;
    }
    if (player->coin < 0) {
        player->coin = 0;
    }
    if (player->coinPrize <= player->coin) {
        player->coinPrize = player->coin;
    }
}

s32 MBPlayerCoinCheck(s32 playerNo, s32 requiredCoins) {
    if (MBPlayerGet(playerNo)->coin >= requiredCoins) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void MBPlayerSpeedSet(s32 playerNo, f32 arg1) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    if (player->itemTurn != 0) {
        Hu3DMotionSpeedSet(mbKSuitMdl->omObj1->model[0], arg1);
    } else {
        Hu3DMotionSpeedSet(player->player_obj->omObj1->model[0], arg1);
    }
}

void MBPlayerMotionWait(s32 playerNo) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    if (player->itemTurn != 0) {
        MBModelMotionWait(mbKSuitMdl);
    } else {
        MBModelMotionWait(player->player_obj);
    }
}

void MBPlayerMotionSet(s32 playerNo, s16 arg1, u16 arg2) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    if (player == MBPlayerGet(CUR_PLAYER)) {
        MBMotionSet(player->player_obj, arg1, arg2);
        if ((player->itemTurn != 0) & (arg1 < 7)) {
            MBKSuitMotionSet(arg1, arg2);
        }
    }
}

void MBPlayerMotionShiftSet(s32 playerNo, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    if (player == MBPlayerGet(CUR_PLAYER)) {
        MBMotionShiftSet(player->player_obj, arg1, arg2, arg3, arg4);
        if ((player->itemTurn != 0) & (arg1 < 7)) {
            MBKSuitMotionShiftSet(arg1, arg2, arg3, arg4);
        }
    }
}

void MBPlayerComLevelSet(s32 playerNo, u8 arg1) {
    MBPlayerGet(playerNo)->cpu_difficulty = mbComLevelTbl[arg1];
}

void MBPlayerInit(s32 arg0) {
}

static void MBPlayerScaleResetProc(void) {
    GW_PLAYER *player = HuPrcCurrentGet()->user_data;

    while (1) {
        HuPrcVSleep();
        if (player->stat & PLAYER_UNK_04) {
            continue;
        }
        HuVecCopyXYZ(&player->player_obj->scale, 1.0f, 1.0f, 1.0f);
    }
}

// create player sprite
void MBPlayerModelCreate(s16 playerNo, u32 *arg1, s32 arg2) {
    GW_PLAYER *player = MBPlayerGet(playerNo);
    Process *proc;
    u8 chr;

    player->turn = playerNo;
    chr = player->chr;

    switch (arg2) {
        case 0:
            player->player_obj = MBModelCreate(mbPlayerModelTbl[chr], arg1);
            break;
        case 1:
        case 2:
            player->player_obj = MBModelCreate(mbPlayerModelAltTbl[chr], arg1);
            break;
    }

    proc = omAddPrcObj(MBPlayerScaleResetProc, 0x5000, 0, 0);
    player->unk_20 = proc;
    proc->user_data = player;
}

void MBPlayerModelCreateMot(s16 arg0, u32 *arg1) {
    MBPlayerModelCreate(arg0, arg1, 0);
}

void MBPlayerModelCreateDef(s16 playerNo) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    MBPlayerModelCreate(playerNo, mbPlayerMotTbl[player->chr], 0);
}

void MBPlayerModelCreateNoMot(s16 playerNo) {
    GW_PLAYER *player = MBPlayerGet(playerNo); // remnants of a debug build or the below function was changed to take a playerNo

    MBPlayerModelCreate(playerNo, 0, 0);
}

u8 MBPlayerModelAltNoGet(s16 playerNo) {
    return mbPlayerModelAltTbl[MBPlayerGet(playerNo)->chr];
}

void MBPlayerModelKill(s16 playerNo) {
    GW_PLAYER *player = MBPlayerGet(playerNo);

    if (player->player_obj != NULL) {
        if (player->unk_20 != NULL) {
            omDelPrcObj(player->unk_20);
        }
        MBModelKill(player->player_obj);
        player->player_obj = NULL;
    }
}

void MBPlayerMotInit(void) {
    s32 i, j;

    for (j = 0; j < ARRAY_COUNT(GwPlayer); j++) { // clear all 5 "players" (bowser bomb remnants)
        MBPlayerGet(j)->player_obj = NULL;
    }

    for (i = 1; i < 8; i++) {
        for (j = 0; j < mbMarioMotTbl[0]; j++) {
            mbPlayerMotTbl[i][j + 1] = CharMotionDataNumGet(i, mbMarioMotTbl[j + 1]);
        }
    }
}

void MBPlayerClose(void) {
}
