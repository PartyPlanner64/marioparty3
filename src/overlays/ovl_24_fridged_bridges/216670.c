#include "common.h"
#include "math.h"
#include "overlays/minigame.h"
#include "overlays/ovl_24.h"

// Result of the ice-floor probe performed by func_80109988.
typedef struct FridgedBridgesProbe {
    /* 0x00 */ f32 height[9];
    /* 0x24 */ u16 bridgeIds[9];
    /* 0x38 */ Vec pos;
} FridgedBridgesProbe; // sizeof 0x44

// Per-camera collision work buffer passed to func_80012888_main.
typedef struct FridgedBridgesCamCollWork {
    /* 0x000 */ char unk_00[0xC18];
} FridgedBridgesCamCollWork; // sizeof 0xC18

extern omObjData *D_8010D35C_fridged_bridges;
extern omObjData *D_8010D360_fridged_bridges;
extern s16 D_8010DA60_fridged_bridges;
extern s16 D_8010DA68_fridged_bridges;
extern omObjData **D_8010DA64_fridged_bridges;
extern omObjData *D_8010DA70_fridged_bridges;
extern omObjData *D_8010DA6C_fridged_bridges;
extern FridgedBridgesCamCollWork D_8010DA90_fridged_bridges[4];
extern D_80111B50_vine_with_me_Struct D_8010CF20_fridged_bridges;
extern u16 D_8010CF50_fridged_bridges;
extern u16 D_8010D364_fridged_bridges;
extern u16 D_8010D366_fridged_bridges;
extern s16 D_8010CF48_fridged_bridges[4];
extern s32 D_8010CF54_fridged_bridges[4];
extern s32 D_8010CF64_fridged_bridges[4];
extern char *D_8010CF94_fridged_bridges[4];
extern u16 D_8010D368_fridged_bridges[4][2];
extern Vec2f D_8010D378_fridged_bridges[4];
extern u8 D_800D6A90_main;
extern Vec D_8010CFA4_fridged_bridges[4];
extern f32 D_8010CFD4_fridged_bridges[];
extern s32 D_800A178C_main[][6];
extern u16 D_8010CFF4_fridged_bridges[];
extern Vec2f D_8010CFFC_fridged_bridges[3][12];
extern Vec2f D_8010D11C_fridged_bridges[12];
extern Vec2f D_8010D3A0_fridged_bridges[4][3][12];
extern Vec2f D_8010D820_fridged_bridges[4][12];
extern f32 D_800CCF98_main[];
extern f32 D_800D4198_main[];

void func_80105F34_fridged_bridges(omObjData *arg0);
void func_80108FBC_fridged_bridges(omObjData *arg0);
void func_80105F00_fridged_bridges(omObjData *arg0);
void func_801061C4_fridged_bridges(omObjData *arg0);
void func_8010641C_fridged_bridges(omObjData *arg0);
void func_80106438_fridged_bridges(omObjData *arg0);
void func_80106454_fridged_bridges(omObjData *arg0);
void func_80106470_fridged_bridges(omObjData *arg0);
void func_80108720_fridged_bridges(omObjData *arg0);
void func_80107870_fridged_bridges(void);
void func_8010BEE8_fridged_bridges(void);
void func_8010C1D8_fridged_bridges(omObjData *arg0);
void func_801091F8_fridged_bridges(omObjData *arg0);
void func_80109390_fridged_bridges(omObjData *arg0);
void func_8010BDF0_fridged_bridges(void);
u16 func_8010ADC0_fridged_bridges(void);
void func_801062F8_fridged_bridges(omObjData *arg0);
void func_8010B164_fridged_bridges(void);
void func_8010648C_fridged_bridges(omObjData *arg0, s16 playerIndex);
void func_801068F4_fridged_bridges(omObjData *arg0);
s16 func_80108050_fridged_bridges(omObjData *arg0);
void func_8010BE0C_fridged_bridges(omObjData *arg0);
void func_80107164_fridged_bridges(omObjData *arg0);
void func_801079CC_fridged_bridges(omObjData *arg0, s8 *stickX, s8 *stickY);
void func_801082D0_fridged_bridges(omObjData *arg0);
void func_801084E0_fridged_bridges(omObjData *arg0);
u16 func_80109988_fridged_bridges(omObjData *arg0, FridgedBridgesProbe *probe);
u16 func_8010A0F4_fridged_bridges(omObjData *arg0, f32 x, f32 y, f32 z);
void func_8010B7CC_fridged_bridges(omObjData *arg0);
void func_8010733C_fridged_bridges(omObjData *arg0);
void func_80107510_fridged_bridges(omObjData *arg0);
void func_80109F84_fridged_bridges(omObjData *arg0);
void func_8010A1A4_fridged_bridges(omObjData *arg0);
void func_8010B8CC_fridged_bridges(omObjData *arg0);
void func_8010BFD0_fridged_bridges(u16 arg0, u16 playerId, f32 x, f32 y, f32 z);
void func_80108648_fridged_bridges(omObjData *arg0);

void func_801059A0_fridged_bridges(void) {
    omObjData *obj;
    s32 i;

    omInitObjMan(60, 0);
    func_8004A208_main();
    func_8001FE20_main(16);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_80045C2C_main();
    func_8000B690_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        CZoomM[i] = 1340.0f;
        CRotM[i].x = -60.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = -320.0f;
        CenterM[i].y = 100.0f;
        CenterM[i].z = -420.0f;
        D_800CCF98_main[i] = 5000.0f;
        D_800D4198_main[i] = 1000.0f;
        func_80012888_main(i, (void (*)(void *, struct HmfModel *))func_80020E94_main, &D_8010DA90_fridged_bridges[i]);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, func_8010C1D8_fridged_bridges);
    obj->work[0] = 4;
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    ScissorSet(0, 1.0f, 1.0f, 159.0f, 119.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 240.0f, 511.0f);
    ScissorSet(1, 161.0f, 1.0f, 319.0f, 119.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 240.0f, 511.0f);
    ScissorSet(2, 1.0f, 121.0f, 159.0f, 239.0f);
    ViewportSet(2, 640.0f, 480.0f, 511.0f, 320.0f, 720.0f, 511.0f);
    ScissorSet(3, 161.0f, 121.0f, 319.0f, 239.0f);
    ViewportSet(3, 640.0f, 480.0f, 511.0f, 960.0f, 720.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(1, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(2, 45.0f, 80.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(3, 45.0f, 80.0f, 3000.0f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DGLightMaxSet(3);
    Hu3DGLightColorSet(1, 0x40, 0x40, 0x60);
    Hu3DGLightDirSet(1, 3.0f, 89.0f, 80.0f);
    Hu3DGLightStatSet(1, 1, 1);
    Hu3DGLightColorSet(3, 0, 0, 0);
    Hu3DGLightDirSet(3, -115.0f, 6.0f, -33.0f);
    Hu3DGLightStatSet(2, 1, 1);
    omAddObj(0, 0, 0, -1, func_80105F00_fridged_bridges);
    D_8010DA6C_fridged_bridges = omAddObj(10, 8, 0, -1, func_801061C4_fridged_bridges);
    omSetStatBit(D_8010DA6C_fridged_bridges, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E5EA0_minigame(&D_8010CF20_fridged_bridges);
    D_800EB930_minigame = 46;
    D_800EB932_minigame = 30;
    omMakeGroup(0, 4);
    D_8010DA64_fridged_bridges = omGetGroupMemberList(0);
    omAddObj(20, 6, 9, 0, func_8010641C_fridged_bridges);
    omAddObj(20, 6, 9, 0, func_80106438_fridged_bridges);
    omAddObj(20, 6, 9, 0, func_80106454_fridged_bridges);
    omAddObj(20, 6, 9, 0, func_80106470_fridged_bridges);
    D_8010DA70_fridged_bridges = omAddObj(30, 20, 0, -1, func_80108720_fridged_bridges);
    omSetStat(D_8010DA70_fridged_bridges, 0x100);
    func_80107870_fridged_bridges();
    func_8010BEE8_fridged_bridges();
}

void func_80105F00_fridged_bridges(omObjData *arg0) {
    D_8010D360_fridged_bridges = NULL;
    D_8010D35C_fridged_bridges = NULL;
    D_8010DA68_fridged_bridges = 0;
    D_8010DA60_fridged_bridges = -1;
    arg0->func = func_80105F34_fridged_bridges;
}

void func_80105F34_fridged_bridges(omObjData *arg0) {
    u16 candidates[4];
    u16 count;
    s32 i;

    if (D_8010CF50_fridged_bridges == 0) {
        switch (func_800E6F40_minigame()) {
            case 0:
                if (D_8010D35C_fridged_bridges == NULL) {
                    D_8010D364_fridged_bridges = 0;
                    D_8010D35C_fridged_bridges = omAddObj(4, 0, 0, -1, func_801091F8_fridged_bridges);
                }
                break;
            case 1:
                break;
            case 2:
                if (D_8010DA68_fridged_bridges == 1) {
                    if (D_8010DA60_fridged_bridges == -1) {
                        count = 0;
                        for (i = 0; i < 4; i++) {
                            if (OM_GET_DATA_PTR(D_8010DA64_fridged_bridges[i], FridgedBridgesPlayer)->unk_06 == 1) {
                                candidates[count++] = i;
                            }
                        }
                        if (count == 1) {
                            D_8010DA60_fridged_bridges = candidates[0];
                        } else {
                            D_8010DA60_fridged_bridges = candidates[rand8() % count];
                        }
                        D_8010CF20_fridged_bridges.unk18[0] = D_8010DA60_fridged_bridges;
                    } else if (func_8010ADC0_fridged_bridges() == 1) {
                        func_800E6F0C_minigame(3);
                    }
                } else if (func_800E6E9C_minigame() == 5400) {
                    D_8010DA68_fridged_bridges = 1;
                    D_8010CF20_fridged_bridges.unk06 = 4;
                    func_800E6F0C_minigame(3);
                }
                break;
            case 3:
                if (D_8010D360_fridged_bridges == NULL) {
                    D_8010D360_fridged_bridges = omAddObj(4, 0, 0, -1, func_80109390_fridged_bridges);
                    if (D_8010DA60_fridged_bridges != -1) {
                        D_8010D366_fridged_bridges = 0;
                    } else {
                        D_8010D366_fridged_bridges = 6;
                    }
                }
                break;
            case 4:
                break;
            case 5:
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(30);
                func_8004AB0C_main(30);
                D_8010CF50_fridged_bridges = 1;
                break;
        }
    } else if (WipeStatGet() == 0) {
        func_8010BDF0_fridged_bridges();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D268_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D27C_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D290_fridged_bridges);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", D_8010D2A4_fridged_bridges);

void func_801061C4_fridged_bridges(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        arg0->model[i] = func_8000B108_main(D_8010CF54_fridged_bridges[i], 0x699);
        arg0->model[i + 4] = func_8000B108_main(D_8010CF64_fridged_bridges[i], 0x689);
        Hu3DModelCameraSet(arg0->model[i], D_8010CF48_fridged_bridges[i]);
        Hu3DModelCameraSet(arg0->model[i + 4], D_8010CF48_fridged_bridges[i]);
        D_8010D378_fridged_bridges[i].x = 0.0f;
        D_8010D378_fridged_bridges[i].y = 0.0f;
        func_800335BC_main("sea_01_DEF", D_8010D368_fridged_bridges[i]);
        func_8001C954_main(arg0->model[i + 4]);
    }
    func_8010B164_fridged_bridges();
    arg0->func = func_801062F8_fridged_bridges;
}

void func_801062F8_fridged_bridges(omObjData *arg0) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (omPauseChk() + D_800D6A90_main == 0) {
            D_8010D378_fridged_bridges[i].x += 0.1f;
            D_8010D378_fridged_bridges[i].y += 0.1f;
        }
        func_8001E888_main(arg0->model[i + 4], D_8010D378_fridged_bridges[i].x, D_8010D378_fridged_bridges[i].y,
                           D_8010D368_fridged_bridges[i][0], D_8010D368_fridged_bridges[i][1],
                           D_8010CF94_fridged_bridges[i], 0);
    }
}

void func_8010641C_fridged_bridges(omObjData *arg0) {
    func_8010648C_fridged_bridges(arg0, 0);
}

void func_80106438_fridged_bridges(omObjData *arg0) {
    func_8010648C_fridged_bridges(arg0, 1);
}

void func_80106454_fridged_bridges(omObjData *arg0) {
    func_8010648C_fridged_bridges(arg0, 2);
}

void func_80106470_fridged_bridges(omObjData *arg0) {
    func_8010648C_fridged_bridges(arg0, 3);
}

void func_8010648C_fridged_bridges(omObjData *arg0, s16 playerIndex) {
    FridgedBridgesPlayer *player;
    s8 chr;
    s32 modelFile;

    player = arg0->data = HuMemAllocTag(sizeof(FridgedBridgesPlayer), TAG_OVERLAY);
    player->playerId = playerIndex;
    player->motionState = 0;
    player->unk_08 = player->unk_0C = 0.0f;
    player->slideDist = player->slideDistTarget = 0.0f;
    player->unk_1E = func_80108050_fridged_bridges(arg0);
    player->unk_20 = 1;
    player->unk_22 = 1;
    player->unk_24 = 0;
    player->unk_26 = 0;
    player->state = 1;
    player->unk_28 = 0;
    player->bridgeObj = NULL;
    player->unk_06 = 0;
    player->unk_48 = 0;
    player->unk_4A = 0;
    player->unk_56 = 0;
    player->unk_58 = 0;
    player->unk_6A = 0;
    chr = GwPlayer[playerIndex].chr;
    modelFile = D_800A178C_main[chr][0];
    arg0->model[0] = func_8000B108_main(modelFile | D_800A178C_main[chr][1], 0x20699);
    omSetTra(arg0, D_8010CFA4_fridged_bridges[playerIndex].x, D_8010CFA4_fridged_bridges[playerIndex].y,
             D_8010CFA4_fridged_bridges[playerIndex].z);
    arg0->model[1] = func_8000B0D4_main(9, 0xA89);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    arg0->model[2] = func_8000B108_main(0x450011, 0xA9D);
    arg0->model[3] = func_8000B108_main(0x450012, 0x69D);
    arg0->model[4] = func_8000B108_main(modelFile | D_800A178C_main[chr][2], 0x2068D);
    func_80017790_main(arg0->model[4], 2, chr, func_80017B6C_main(chr, 2, 0));
    func_8001C514_main(arg0->model[4]);
    arg0->model[5] = func_80017AD8_main(func_80017B6C_main(chr, 2, 1));
    Hu3DModelCameraSet(arg0->model[0], D_8010CF48_fridged_bridges[playerIndex]);
    Hu3DModelCameraSet(arg0->model[1], D_8010CF48_fridged_bridges[playerIndex]);
    Hu3DModelCameraSet(arg0->model[2], D_8010CF48_fridged_bridges[playerIndex]);
    Hu3DModelCameraSet(arg0->model[3], D_8010CF48_fridged_bridges[playerIndex]);
    Hu3DModelCameraSet(arg0->model[4], D_8010CF48_fridged_bridges[playerIndex]);
    if (playerIndex < 2) {
        omSetRot(arg0, 0.0f, 0.0f, 0.0f);
    } else {
        omSetRot(arg0, 0.0f, 180.0f, 0.0f);
    }
    func_8000B460_main(arg0, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(arg0, 1, func_80017BB8_main(chr, 1));
    func_8000B460_main(arg0, 2, func_80017BB8_main(chr, 2));
    if (chr == 5) {
        func_8000B460_main(arg0, 3, 0x45000D);
        func_8000B460_main(arg0, 7, 0x45000E);
        func_8000B460_main(arg0, 8, 0x45000F);
    } else {
        func_8000B460_main(arg0, 3, func_80017BB8_main(chr, 0x12));
    }
    func_8000B460_main(arg0, 4, func_80017BB8_main(chr, 0xD));
    func_8000B460_main(arg0, 5, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(arg0, 6, func_80017BB8_main(chr, 0x36));
    func_8001C5B4_main(arg0->model[0], arg0->motion[0]);
    func_8001C814_main(arg0->model[0], 3, 2);
    omSetSca(arg0, D_8010CFD4_fridged_bridges[chr], D_8010CFD4_fridged_bridges[chr], D_8010CFD4_fridged_bridges[chr]);
    func_8010BE0C_fridged_bridges(arg0);
    player->pos.x = arg0->trans.x;
    player->pos.y = arg0->trans.y;
    player->pos.z = arg0->trans.z;
    player->unk_68 = 0x100;
    arg0->func = func_801068F4_fridged_bridges;
}

void func_801068F4_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 port = GwPlayer[player->playerId].pad;
    FridgedBridgesProbe probe;
    s8 stickX;
    s8 stickY;
    f32 speed;
    f32 angle;
    u16 count;

    if (func_800E6E8C_minigame() == 2) {
        if (!(GwPlayer[player->playerId].stat & 1)) {
            stickX = D_800CBB6E_main[port];
            stickY = D_800D20A1_main[port];
        } else {
            func_801079CC_fridged_bridges(arg0, &stickX, &stickY);
        }
    } else {
        stickX = stickY = 0;
    }
    if (player->unk_58 != 0) {
        if (--player->unk_58 == 0) {
            player->unk_56 = 0;
        }
    }
    if (player->state == 0) {
        stickX = stickY = 0;
    }
    speed = HuSqrtf(stickX * stickX + stickY * stickY) * 0.08f;
    angle = atan2df(stickX, -stickY);
    if (stickX != 0 || stickY != 0) {
        player->slideDist = sindf(angle) * speed;
        player->slideDistTarget = cosdf(angle) * speed;
        omSetRot(arg0, 0.0f, angle, 0.0f);
        if (speed > 2.5f) {
            if (player->motionState != 2) {
                if (GwPlayer[player->playerId].chr == 5 && player->unk_28 == 1) {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[8]].motId, 0, 6, 2);
                } else {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[2]].motId, 0, 6, 2);
                }
                player->motionState = 2;
                player->unk_48 = 0;
            }
            if (player->unk_48 == 0) {
                PlayerFXPlay(0x28, player->playerId);
                player->unk_48 = 12;
            } else {
                player->unk_48--;
            }
        } else {
            if (player->motionState != 1) {
                if (GwPlayer[player->playerId].chr == 5 && player->unk_28 == 1) {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 0, 6, 2);
                } else {
                    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[1]].motId, 0, 6, 2);
                }
                player->motionState = 1;
                player->unk_48 = 0;
            }
            if (player->unk_48 == 0) {
                PlayerFXPlay(0x1F, player->playerId);
                player->unk_48 = 22;
            } else {
                player->unk_48--;
            }
        }
        player->unk_4A = 0;
    } else {
        player->slideDist = player->slideDistTarget = 0.0f;
        if (player->motionState != 0) {
            if (GwPlayer[player->playerId].chr == 5 && player->unk_28 == 1) {
                Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[7]].motId, 0, 6, 2);
            } else {
                Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[0]].motId, 0, 6, 2);
            }
            player->motionState = 0;
        }
        if (player->unk_08 != 0.0f || player->unk_0C != 0.0f) {
            if (player->unk_4A == 0) {
                PlayerFXPlay(0xD3, player->playerId);
                player->unk_4A = 11;
            } else {
                player->unk_4A--;
            }
        }
    }
    if (fabs(player->unk_08) < 0.1f) {
        player->unk_08 = 0.0f;
    }
    if (fabs(player->unk_0C) < 0.1f) {
        player->unk_0C = 0.0f;
    }
    if (player->unk_28 != 0) {
        player->slideDist *= 0.85f;
        player->slideDistTarget *= 0.85f;
    }
    player->unk_08 += player->slideDist;
    player->unk_0C += player->slideDistTarget;
    speed = HuSqrtf(player->unk_08 * player->unk_08 + player->unk_0C * player->unk_0C);
    if (speed != 0.0f) {
        player->unk_08 /= speed;
        player->unk_0C /= speed;
        if (speed > 16.0f) {
            speed = 16.0f;
        }
    }
    player->unk_08 = speed * player->unk_08;
    player->unk_0C = speed * player->unk_0C;
    if (player->state == 0 || D_8010DA60_fridged_bridges != -1) {
        player->unk_08 = player->unk_0C = 0.0f;
    }
    if (func_8010A0F4_fridged_bridges(arg0, arg0->trans.x + player->unk_08, arg0->trans.y,
                                      arg0->trans.z + player->unk_0C) == 1) {
        if (player->unk_28 == 0) {
            func_801082D0_fridged_bridges(arg0);
            func_8004AC98_main(0x42D, player->playerId);
            player->unk_1E = func_80108050_fridged_bridges(arg0);
            player->unk_20 = 1;
            player->unk_22 = 1;
        }
        player->unk_08 = player->unk_0C = 0.0f;
    }
    func_8010B7CC_fridged_bridges(arg0);
    omSetTra(arg0, arg0->trans.x + player->unk_08, arg0->trans.y, arg0->trans.z + player->unk_0C);
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, 0.0f, arg0->trans.z);
    player->unk_08 *= 0.8f;
    player->unk_0C *= 0.8f;
    probe.pos.x = arg0->trans.x;
    probe.pos.y = arg0->trans.y;
    probe.pos.z = arg0->trans.z;
    count = func_80109988_fridged_bridges(arg0, &probe);
    if (probe.height[8] != -10000.0f) {
        count = 0;
    }
    if (count >= 6) {
        player->state = 2;
        player->unk_34.x = sindf(angle) * 10.0f;
        player->unk_34.z = cosdf(angle) * 10.0f;
        player->unk_34.y = -1.2f;
        player->motionState = 0;
        player->unk_48 = 0;
        arg0->func = func_80107164_fridged_bridges;
        player->unk_2C->work[0] = 0;
        func_8001C814_main(arg0->model[0], 1, 1);
    }
    if (player->unk_1C == D_8010CFF4_fridged_bridges[player->unk_24] && player->unk_28 == 1) {
        func_801084E0_fridged_bridges(arg0);
        if (player->unk_24 != 2) {
            player->unk_22 = -1;
            player->unk_20--;
        }
    } else if (player->unk_1C == 0x600) {
        D_8010DA68_fridged_bridges = 1;
        player->unk_06 = 1;
    }
    if (player->state != 2) {
        player->unk_68 = player->unk_1C;
        player->pos.x = arg0->trans.x;
        player->pos.y = arg0->trans.y;
        player->pos.z = arg0->trans.z;
    }
}

void func_80107164_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    arg0->trans.x += player->unk_08;
    arg0->trans.y += player->unk_34.y;
    arg0->trans.z += player->unk_0C;
    func_8010B7CC_fridged_bridges(arg0);
    func_80109F84_fridged_bridges(arg0);
    player->unk_08 *= 0.91f;
    player->unk_0C *= 0.91f;
    player->unk_34.y *= 1.3f;
    if (arg0->trans.y <= -150.0f) {
        arg0->trans.y = -150.0f;
        omVibrate(player->playerId, 2, 2, 20);
        PlayerFXPlay(0x70, player->playerId);
        func_8010BFD0_fridged_bridges(0, player->playerId, arg0->trans.x, -150.0f, arg0->trans.z);
        func_8001C258_main(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        player->unk_54 = 29;
        player->scale = 0.1f;
        player->state = 3;
        Hu3DModelPosSet(arg0->model[3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
        Hu3DModelScaleSet(arg0->model[3], player->scale, player->scale, player->scale);
        func_8004AC98_main(0x42F, player->playerId);
        arg0->func = func_8010733C_fridged_bridges;
        player->unk_56 = 0;
        player->unk_58 = 0;
        if (D_8010DA68_fridged_bridges == 0) {
            func_8010A1A4_fridged_bridges(arg0);
            func_8010B8CC_fridged_bridges(arg0);
        }
    }
    Hu3DModelPosSet(arg0->model[1], arg0->trans.x, -100.0f, arg0->trans.z);
}

void func_8010733C_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    if (--player->unk_54 != 0) {
        if (player->unk_54 & 1) {
            func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, 0);
            func_8001C258_main(arg0->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (player->unk_28 == 1) {
                func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF, 0);
            }
        } else {
            func_8001C258_main(arg0->model[3], HU3D_ATTR_DISPOFF, 0);
            func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            if (player->unk_28 == 1) {
                func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                   HU3D_ATTR_DISPOFF);
            }
        }
        player->scale += 0.03f;
        Hu3DModelScaleSet(arg0->model[3], player->scale, player->scale, player->scale);
    } else {
        func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                           HU3D_ATTR_DISPOFF);
        func_8001C258_main(arg0->model[3], HU3D_ATTR_DISPOFF, 0);
        player->unk_40 = 0.0f;
        Hu3DModelScaleSet(arg0->model[3], 1.0f, 1.0f, 1.0f);
        arg0->func = func_80107510_fridged_bridges;
    }
}

void func_80107510_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;

    arg0->trans.y += sindf(player->unk_40);
    Hu3DModelPosSet(arg0->model[3], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    player->unk_40 += 5.0f;
    if (player->unk_40 >= 360.0f) {
        player->unk_40 -= 360.0f;
    }
}

void func_801075A4_fridged_bridges(void) {
}

void func_801075AC_fridged_bridges(omObjData *arg0) {
    f32 diff = -arg0->rot.y;

    if (diff < 0.0f) {
        diff += 360.0f;
    }
    if (diff < 180.0f) {
        if (diff > 5.0f) {
            arg0->rot.y += 5.0f;
        } else {
            arg0->rot.y += diff;
        }
    } else {
        if (360.0f - diff > 5.0f) {
            arg0->rot.y -= 5.0f;
        } else {
            arg0->rot.y -= 360.0f - diff;
        }
    }
    if (arg0->rot.y >= 360.0f) {
        arg0->rot.y -= 360.0f;
    }
    if (arg0->rot.y < 0.0f) {
        arg0->rot.y += 360.0f;
    }
    if (arg0->rot.y < 0.0001f) {
        arg0->work[0] = 1;
        Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[0]].motId, 0, 6, 2);
        arg0->func = NULL;
    }
}

void func_8010775C_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    HmfMotionNode *hook;

    if (player->unk_28 == 1) {
        hook = func_8001D33C_main(arg0->model[0], "item_hook");
        player->unk_44 -= 0.1f;
        hook->scale.x = player->unk_44;
        hook->scale.y = player->unk_44;
        hook->scale.z = player->unk_44;
        if (!(player->unk_44 <= 0.0f)) {
            return;
        }
        func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], 0x4004, HU3D_ATTR_DISPOFF);
        func_80108648_fridged_bridges(arg0);
    }
    Hu3DMotionShiftSet(arg0->model[0], Hu3DData[arg0->motion[6]].motId, 0, 6, 0);
    arg0->func = NULL;
}

void func_80107870_fridged_bridges(void) {
    f32 sign[2][4];
    s32 i;
    s32 j;
    s32 k;

    sign[0][0] = 1.0f;
    sign[0][1] = -1.0f;
    sign[0][2] = 1.0f;
    sign[0][3] = -1.0f;
    sign[1][0] = 1.0f;
    sign[1][1] = 1.0f;
    sign[1][2] = -1.0f;
    sign[1][3] = -1.0f;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 12; k++) {
                D_8010D3A0_fridged_bridges[i][j][k].x = D_8010CFFC_fridged_bridges[j][k].x * sign[0][i];
                D_8010D3A0_fridged_bridges[i][j][k].y = D_8010CFFC_fridged_bridges[j][k].y * sign[1][i];
            }
        }
        for (k = 0; k < 12; k++) {
            D_8010D820_fridged_bridges[i][k].x = D_8010D11C_fridged_bridges[k].x * sign[0][i];
            D_8010D820_fridged_bridges[i][k].y = D_8010D11C_fridged_bridges[k].y * sign[1][i];
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801079CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108050_fridged_bridges);

void func_801082D0_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 playerId = player->playerId;
    u16 motion;

    player->unk_28 = 1;
    player->unk_26++;
    D_8010DA70_fridged_bridges->work[2] &= ~(1 << player->playerId);
    func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5 + 4], HU3D_ATTR_DISPOFF,
                       HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(D_8010DA70_fridged_bridges->model[playerId * 5], 1.0f, 1.0f, 1.0f);
    Hu3DModelHookSet(D_8010DA70_fridged_bridges->model[playerId * 5], arg0->model[0], "item_hook");
    func_8001C258_main(D_8010DA70_fridged_bridges->model[playerId * 5], 0x4004, 0x4000);
    if (GwPlayer[player->playerId].chr == 5) {
        switch (player->motionState) {
            case 0:
                motion = arg0->motion[7];
                break;
            case 1:
                motion = arg0->motion[3];
                break;
            case 2:
                motion = arg0->motion[8];
                break;
        }
        func_8001C5B4_main(arg0->model[0], motion);
        func_8001C814_main(arg0->model[0], 2, 2);
    } else {
        Hu3DMotionShapeSet(arg0->model[0], Hu3DData[arg0->motion[3]].motId, 2);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801084E0_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108648_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108720_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108B08_fridged_bridges);

void func_80108BEC_fridged_bridges(omObjData *arg0) {
    omObjData **bridgeObjs = omGetGroupMemberList(1);
    s32 deletedCount = 0;
    s32 i;

    for (i = 0; i < 12; i++) {
        deletedCount += bridgeObjs[i] == NULL;
    }

    if (deletedCount == 12) {
        arg0->work[0] = 1;
        arg0->func = func_80108FBC_fridged_bridges;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108C60_fridged_bridges);

// Shrinking phase of a player's bridge-sink object (created with func_80108C60).
// Sinks the player model 10 units per frame while scaling it away; when the
// scale runs out, stops the animation and deletes the object.
void func_80108EBC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = OM_GET_DATA_PTR((omObjData *)arg0->work[0], FridgedBridgesPlayer);
    s16 playerId = player->playerId;
    u16 modelId = D_8010DA70_fridged_bridges->model[playerId * 5];
    f32 *scale;

    arg0->trans.y -= 10.0f;
    Hu3DModelPosSet(modelId, arg0->trans.x, arg0->trans.y, arg0->trans.z);
    scale = (f32 *)&arg0->work[2];
    *scale -= 0.04f;
    if (*scale <= 0.0f) {
        func_8001C258_main(modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        omDelObj(arg0);
    } else {
        Hu3DModelScaleSet(modelId, *scale, *scale, *scale);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80108FBC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109154_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801091F8_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109390_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109988_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D4C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109D6C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_80109F84_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A0F4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A1A4_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010A360_fridged_bridges);

// True once every player has left the frozen (state 2) pose.
u16 func_8010ADC0_fridged_bridges(void) {
    s32 notFrozenCount = 0;
    s32 i = 0;
    omObjData **playerObjs = D_8010DA64_fridged_bridges;

    for (; i < 4; i++) {
        notFrozenCount += OM_GET_DATA_PTR(playerObjs[i], FridgedBridgesPlayer)->state != 2;
    }
    return notFrozenCount == 4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE0C_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010AE98_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B164_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B3EC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B7CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B8CC_fridged_bridges);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010BB18_fridged_bridges);
