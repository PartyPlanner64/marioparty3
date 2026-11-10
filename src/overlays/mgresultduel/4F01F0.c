#include "common.h"
#include "game/object.h"
#include "math.h"
#include "../ovl_81_name/ovl_81.h"

typedef struct UnkOmData {
    omObjData *unk_00;
    void (*objFunc)(omObjData *); // func pointer
} UnkOmData;

extern UnkOmData D_80109338_mgresultduel;
extern s8 D_80108E70_mgresultduel;
extern s32 D_80108E74_mgresultduel;
extern s8 D_80109310_mgresultduel[];
extern s8 D_80109318_mgresultduel;
extern s8 D_80108E78_mgresultduel;
extern char D_80108EC0_mgresultduel[];
extern s32 D_80109314_mgresultduel;
extern s16 D_80109316_mgresultduel;
const s16 D_80108EA0_mgresultduel[2][2] = { { 30, 40 }, { 194, 40 } };
extern Addr D_128CC60;

void func_800F6550_name_81(s32, s16, s16);
void func_800F7458_name_81(s32, f32, f32);
void func_80105E90_mgresultduel(omObjData *);
void func_80105FD4_mgresultduel(omObjData *);
void func_80106054_mgresultduel(void);
void func_80106080_mgresultduel(void);
void func_80106930_mgresultduel(void);
void func_80106F38_mgresultduel(void);
void func_80107710_mgresultduel(void);
void func_801084B0_mgresultduel(void);
void func_80106544_mgresultduel(omObjData *);
void func_80106270_mgresultduel(omObjData *);
void func_80106278_mgresultduel(omObjData *);
void func_80106574_mgresultduel(omObjData *);
void func_80106744_mgresultduel(omObjData *);
void func_80106850_mgresultduel(omObjData *, s32);
void func_801074B8_mgresultduel(void);
void func_801074DC_mgresultduel(s8);
void func_80107C74_mgresultduel(s32, s32);

void func_801059A0_mgresultduel(void) {
    s16 coins[2];
    s8 count = 0;
    s8 i;
    s8 j;
    s8 player;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayer[j].group) {
                D_80109310_mgresultduel[count] = j;
                count++;
                if (count >= 4) {
                    break;
                }
            }
        }
        if (count >= 4) {
            break;
        }
    }

    omInitObjMan(50, 20);
    func_800142A0_main(120);
    func_800F6390_name_81();
    func_800F6550_name_81(0, D_80108EA0_mgresultduel[0][0], D_80108EA0_mgresultduel[0][1]);
    func_800F6550_name_81(1, D_80108EA0_mgresultduel[1][0], D_80108EA0_mgresultduel[1][1]);
    func_800F7458_name_81(0, 0.0f, 0.0f);
    func_800F7458_name_81(1, 0.0f, 0.0f);
    Hu3DCamInit(1);
    func_800E4F50_name_81(D_128CC60);
    MBDBackLoad(23);
    func_800E8180_name_81(1000.0f, 10000.0f);

    coins[0] = GwPlayer[D_80109310_mgresultduel[0]].gameCoin + GwPlayer[D_80109310_mgresultduel[0]].bonusCoin;
    coins[1] = GwPlayer[D_80109310_mgresultduel[1]].gameCoin + GwPlayer[D_80109310_mgresultduel[1]].bonusCoin;
    if (coins[0] >= coins[1]) {
        if (coins[0] == coins[1]) {
            D_80109318_mgresultduel = 2;
            D_80109314_mgresultduel = 0;
        } else {
            player = D_80109310_mgresultduel[0];
            D_80109318_mgresultduel = -1;
            D_80109314_mgresultduel = GwPlayer[D_80109310_mgresultduel[player]].gameCoin + GwPlayer[player].bonusCoin;
            if (GwSystem.bank_coins == 0) {
                if (GwSystem.current_turn < 11) {
                    D_80109314_mgresultduel *= 2;
                } else if (GwSystem.current_turn < 20) {
                    D_80109314_mgresultduel *= 3;
                } else {
                    D_80109314_mgresultduel *= 4;
                }
            }
        }
    } else {
        player = D_80109310_mgresultduel[1];
        D_80109318_mgresultduel = 1;
        D_80109314_mgresultduel = GwPlayer[D_80109310_mgresultduel[player]].gameCoin + GwPlayer[player].bonusCoin;
        if (GwSystem.bank_coins == 0) {
            if (GwSystem.current_turn < 11) {
                D_80109314_mgresultduel *= 2;
            } else if (GwSystem.current_turn < 20) {
                D_80109314_mgresultduel *= 3;
            } else {
                D_80109314_mgresultduel *= 4;
            }
        }
    }

    if (coins[0] != coins[1]) {
        if (coins[0] >= coins[1]) {
            GwPlayer[D_80109310_mgresultduel[0]].gamePrize += D_80109316_mgresultduel;
        } else {
            GwPlayer[D_80109310_mgresultduel[1]].gamePrize += D_80109316_mgresultduel;
        }
    }

    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, 0.0f, 50.0f, 100.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    omAddPrcObj(func_80106930_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106F38_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80106080_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_801084B0_mgresultduel, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80107710_mgresultduel, 0x1001, 0x2000, 0);
    omAddObj(10, 0, 0, -1, func_80105E90_mgresultduel);
    omAddObj(10, 0, 0, -1, func_80105FD4_mgresultduel);
    WipeCreateIn(WIPE_TYPE_PREV, 16);
}

void func_80105E90_mgresultduel(omObjData *object) {
    s32 state;
    s16 playerIdx;

    state = D_80108E70_mgresultduel;
    switch (state) {
        case 0:
            HuAudSeqPlay(0x16);
            D_80108E74_mgresultduel = 0;
            state++;
            break;
        case 1:
            D_80108E74_mgresultduel++;
            if (D_80108E74_mgresultduel >= 20) {
                state++;
            }
            break;
        case 2:
            func_801074B8_mgresultduel();
            state++;
            break;
        case 4:
            if (D_80109318_mgresultduel != 2) {
                if (D_80109318_mgresultduel == -1) {
                    playerIdx = D_80109310_mgresultduel[0];
                } else {
                    playerIdx = D_80109310_mgresultduel[1];
                }
                GwPlayer[playerIdx].gameCoin = 0;
                GwPlayer[playerIdx].bonusCoin = 0;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            state++;
            break;
        case 5:
            if (WipeStatGet() == 0) {
                func_80106054_mgresultduel();
                omOvlReturnEx(1);
            }
            break;
    }
    D_80108E70_mgresultduel = state;
}

void func_80105FD4_mgresultduel(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80108E78_mgresultduel == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 0x14);
            D_80108E78_mgresultduel = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            func_80106054_mgresultduel();
            omOvlReturnEx(1);
        }
    }
}

void func_80106054_mgresultduel(void) {
    MBDBackKill();
    MBDBackClose();
    func_800F64FC_name_81();
}

void func_80106080_mgresultduel(void) {
    omObjData *temp_v0;

    temp_v0 = omAddObj(0x14, 5, 8, -1, NULL);
    D_80109338_mgresultduel.unk_00 = temp_v0;
    temp_v0->model[1] = func_8000B108_main(0xA011B, 0x2B9);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    Hu3DModelScaleSet(temp_v0->model[1], 0.9f, 0.9f, 0.9f);
    temp_v0->model[2] = func_8000B108_main(9, 0x2B9);
    Hu3DModelScaleSet(temp_v0->model[2], 2.0f, 1.0f, 2.0f);
    func_8000B460_main(temp_v0, 0, 0xA011C);
    func_8000B460_main(temp_v0, 1, 0xA011D);
    func_8000B460_main(temp_v0, 2, 0xA011E);
    func_8000B460_main(temp_v0, 3, 0xA011F);
    func_8000B460_main(temp_v0, 4, 0xA0120);
    func_8001C5B4_main(temp_v0->model[1], temp_v0->motion[4]);
    func_8001C814_main(temp_v0->model[1], 2, 2);
    func_80106850_mgresultduel(temp_v0, -1);
    temp_v0->trans.x = 0.0f;
    temp_v0->trans.y = 0.0f;
    temp_v0->trans.z = 0.0f;
    Hu3DModelPosSet(temp_v0->model[0], temp_v0->trans.x, temp_v0->trans.y, temp_v0->trans.z);
    Hu3DModelPosSet(temp_v0->model[1], 0.0f, 0.0f, 2300.0f);
    Hu3DModelPosSet(temp_v0->model[2], 0.0f, 0.0f, 2300.0f);
    omPrcSetDestructor(0, func_80106544_mgresultduel);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
    while (1) {
        D_80109338_mgresultduel.objFunc(temp_v0);
        HuPrcVSleep();
    }
}

void func_80106270_mgresultduel(omObjData *arg0) {
}

void func_80106278_mgresultduel(omObjData *obj) {
    f32 scale;
    s8 i;

    scale = 0.9f;
    Hu3DModelScaleSet(obj->model[1], scale, scale, scale);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[1]].motId, 0, 0x1E, 2);
    func_80106850_mgresultduel(obj, Hu3DData[obj->motion[1]].motId);
    HuAudFXPlay(0x20F);
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f - sindf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    HuPrcSleep(2);
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f - cosdf(i * 22.5f) * 0.24f, 0.9f);
        HuPrcVSleep();
    }
    Hu3DModelScaleSet(obj->model[1], 0.9f, 0.9f, 0.9f);
    HuAudFXPlay(0x20D);
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 0x1E, 2);
    func_80106850_mgresultduel(obj, Hu3DData[obj->motion[3]].motId);
    Hu3DMotionSpeedSet(obj->model[1], 2.0f);
    func_801074DC_mgresultduel(D_80109318_mgresultduel);
    func_80107C74_mgresultduel(D_80109314_mgresultduel, D_80109318_mgresultduel);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}

void func_80106544_mgresultduel(omObjData *arg0) {
}

void func_8010654C_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106278_mgresultduel;
}

void func_80106560_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106574_mgresultduel;
}

void func_80106574_mgresultduel(omObjData *obj) {
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[3]].motId, 0, 0x1E, 0);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C814_main(obj->model[1], 4, 4);
    func_80106850_mgresultduel(obj, Hu3DData[obj->motion[3]].motId);
    Hu3DMotionSpeedSet(obj->model[1], 1.0f);
    while (Hu3DData[obj->model[1]].motTime > 0.0f) {
        HuPrcVSleep();
    }
    Hu3DMotionShiftSet(obj->model[1], Hu3DData[obj->motion[4]].motId, 0, 0x1E, 2);
    func_80106850_mgresultduel(obj, Hu3DData[obj->motion[4]].motId);
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}

void func_80106730_mgresultduel(void) {
    D_80109338_mgresultduel.objFunc = func_80106744_mgresultduel;
}

void func_80106744_mgresultduel(omObjData *obj) {
    HmfMotionNode *node;
    f32 rot;

    node = func_8001D33C_main(obj->model[1], D_80108EC0_mgresultduel);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
    if (GwSystem.bank_coins == 0) {
        for (rot = 0.0f; rot >= -60.0f; rot -= 2.0f) {
            node->baseRot.y = (GwSystem.bank_coins - 5) * 60 + rot;
            HuPrcVSleep();
        }
        GwSystem.bank_coins = 5;
        HuPrcSleep(10);
    }
    D_80108E70_mgresultduel = 4;
    D_80109338_mgresultduel.objFunc = func_80106270_mgresultduel;
}

void func_80106850_mgresultduel(omObjData *obj, s32 motId) {
    HmfMotionNode *node;

    func_8002FD8C_main(obj->model[1], Hu3DData[obj->model[1]].motId, D_80108EC0_mgresultduel, 0x4C, 0x46);
    if ((s16)motId >= 0) {
        func_8002FD8C_main(obj->model[1], motId, D_80108EC0_mgresultduel, 0x4C, 0x46);
    }
    node = func_8001D33C_main(obj->model[1], D_80108EC0_mgresultduel);
    node->baseRot.y = (GwSystem.bank_coins - 5) * 60;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultduel/4F01F0", D_80108EC0_mgresultduel);
