#include "common_board.h"
#include "player.h"
#include "model.h"
#include "back.h"
#include "ksuit.h"

// TODO: properly split data/rodata in item.c and ksuit.c

u32 mbKSuitMotTbl[] = { 7, 0xA004D, 0xA004D, 0xA004E, 0xA0051, 0xA0052, 0xA0050, 0xA0058 };
extern s16 mbKoopaMasuId;
extern Object *mbKoopaPosMdl;

// void MBKSuitKill(void);
// void Hu3DModelObjCopy(s16, s32, s16, const char*);
// void MBMasuLinkIdxGet(s16 arg0, s8 *chainOut, s8 *linkOut);
// void MBMotionKill(s16 arg0);
// s16 MBMotionCreate(s32);

static void MBKSuitMain(omObjData *arg0) {
    GW_PLAYER *player;

    player = MBPlayerGet(arg0->work[0]);
    HuVecCopy3F(&mbKSuitMdl->coords, &player->player_obj->coords);
    HuVecCopy3F(&mbKSuitMdl->rot, &player->player_obj->rot);
    HuVecCopy3F(&mbKSuitMdl->scale, &player->player_obj->scale);
    mbKSuitMdl->velocity.x = player->player_obj->velocity.x;
    mbKSuitMdl->flags &= ~1;
    mbKSuitMdl->flags = mbKSuitMdl->flags | (player->player_obj->flags & 1);
}

const char mbMgType1vs1Str[] = " 1 VS 1 GAME";
const char mbMgTypeBattleStr[] = " BATTLE GAME";
const char mbMgTypeItemStr[] = " ITEM   GAME";
const char mbMgType2vs2Str[] = " 2 VS 2 GAME";
const char mbMgType1vs3Str[] = " 1 VS 3 GAME";
const char mbMgType4PStr[] = "4=PLAYER GAME";

const u8 mbTelopLast5FrameTbl[] = { 0, 0, 1, 2, 3, 3, 3, 3, 3, 4 };
const u16 mbTelopPlayerSprTbl[] = { 0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5 };

char *mbKSuitHeadObjTbl[] = {
    "atama_2",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
    "c003_000-head_1",
    "Luigi1-atama_1",
    "c005_000-bmerge1",
    "c001_000-atama_2",
    "C002_000b-bmerge10_1",
};
u32 mbKoopaMotTbl[] = { 6, 0xA0037, 0xA0033, 0xA0031, 0xA0034, 0xA0036, 0xA003C };
Object *mbKSuitMdl = NULL;
omObjData *mbKSuitObj = NULL;
u16 mbKSuitMotConvTbl[] = {
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
        mbKSuitMdl = MBModelCreate(0x23, mbKSuitMotTbl);
        obj = omAddObj(0x3FFF, 0, 0, -1, MBKSuitMain);
        mbKSuitObj = obj;
        obj->work[0] = playerIndex & 0xFF;
        Hu3DModelObjCopy(player->player_obj->omObj1->model[0], mbKSuitHeadObjTbl[GwPlayer[playerIndex].chr],
                           mbKSuitMdl->omObj1->model[0], "atama_3");
        HuVecCopy3F(&mbKSuitMdl->coords, &player->player_obj->coords);
    } else {
        mbKSuitMdl = MBModelCreate(8, mbKoopaMotTbl);
        GwPlayer[4].player_obj = mbKSuitMdl;
        MBModelDispOff(mbKSuitMdl);
    }
    return mbKSuitMdl;
}

void MBKSuitKill(void) {
    if (mbKSuitMdl != NULL) {
        MBModelKill(mbKSuitMdl);
        mbKSuitMdl = NULL;
    }
    if (mbKSuitObj != NULL) {
        omDelObj(mbKSuitObj);
        mbKSuitObj = NULL;
    }
}

void MBKSuitInit(void) {
    mbKSuitMdl = NULL;
    mbKSuitObj = NULL;
}

void MBKSuitClose(void) {
    MBKSuitKill();
}

void MBKSuitMotionSet(s16 arg0, s32 arg1) {
    MBMotionSet(mbKSuitMdl, arg0, arg1);
}

void MBKSuitMotionShiftSet(s16 arg0, s16 arg1, s16 arg2, s32 arg3) {
    MBMotionShiftSet(mbKSuitMdl, arg0, arg1, arg2, arg3);
}

void MBKoopaPlayerPosSet(void) {
    HuVecCopy3F(&mbKSuitMdl->coords, &mbKoopaPosMdl->coords);
    MBMasuLinkIdxGet(mbKoopaMasuId, &GwPlayer[4].clink, &GwPlayer[4].clink + 1);
    MBMasuLinkIdxGet(mbKoopaMasuId, &GwPlayer[4].nlink, &GwPlayer[4].nlink + 1);
    GwPlayer[4].nidx = GwPlayer[4].nidx + 1;
}

void MBKoopaMasuSet(s16 arg0) {
    mbKoopaMasuId = arg0;
}

void MBKSuitDispOn(void) {
    if (mbKSuitMdl != NULL) {
        MBModelDispOff(mbKSuitMdl);
    }
}

void MBKSuitDispOff(void) {
    if (mbKSuitMdl != NULL) {
        MBModelDispOn(mbKSuitMdl);
    }
}

void MBKSuitMotionLoad(s32 arg0, s32 arg1) {
    omObjData *objData;
    s16 motion;
    s32 dataNum;
    u32 i;
    Object *obj = mbKSuitMdl;

    objData = obj->omObj1;

    for (i = 0; i < ARRAY_COUNT(mbKSuitMotConvTbl); i += 2) {
        if (mbKSuitMotConvTbl[i] == arg1) {
            break;
        }
    }

    dataNum = mbKSuitMotConvTbl[i + 1] | 0x000A0000;
    motion = objData->motion[arg0];

    if ((motion != -1) && (obj->unk46 != arg0)) {
        MBMotionKill(motion);
    }

    objData->motion[arg0] = MBMotionCreate(dataNum);
}
