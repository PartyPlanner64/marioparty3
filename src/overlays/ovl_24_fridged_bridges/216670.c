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

// Data for the objects created by func_8010B164 (one per player area).
// It jumps back and forth between the two points of D_8010D1FC_fridged_bridges.
typedef struct FridgedBridgesFoe {
    /* 0x00 */ u16 state; // 0 waiting, 1 jumping, 2 turning around
    /* 0x02 */ u16 index;
    /* 0x04 */ s16 dir;  // index of the point it is heading to
    /* 0x06 */ u16 wait; // frames left before the next jump
    /* 0x08 */ f32 jumpDist;
    /* 0x0C */ f32 arcScale;
    /* 0x10 */ f32 jumpPos;
    /* 0x14 */ f32 speed;
    /* 0x18 */ f32 unk_18;
} FridgedBridgesFoe; // sizeof 0x1C

// Work area of the dropped-item objects created by func_801084E0.
typedef struct FridgedBridgesItemWork {
    /* 0x00 */ omObjData *playerObj;
    /* 0x04 */ u32 phase;
    /* 0x08 */ f32 fallSpeed;
} FridgedBridgesItemWork;

// Data for the rescue objects created by func_8010A1A4, which fly in to pick up
// a player that fell off the bridges.
typedef struct FridgedBridgesRescue {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 timer;
    /* 0x04 */ omObjData *playerObj;
    /* 0x08 */ u16 released;
    /* 0x0A */ s16 sfxId;
} FridgedBridgesRescue; // sizeof 0xC

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
extern omObjData *D_8010DA78_fridged_bridges[4];
extern Vec2f D_8010D17C_fridged_bridges[3];
extern s16 D_8010D19C_fridged_bridges;
extern s32 D_8010D1A0_fridged_bridges;
extern Vec D_8010D1A4_fridged_bridges[4];
extern f32 D_8010D340_fridged_bridges;
extern Vec D_8010D344_fridged_bridges;
extern u16 D_8010D350_fridged_bridges;
extern Vec2f D_8010D194_fridged_bridges;
extern Vec2f D_8010D9A0_fridged_bridges[4][3];
extern Vec2f D_8010DA00_fridged_bridges[4];
extern u16 D_8010DA20_fridged_bridges;
extern u16 D_8010D1F4_fridged_bridges[4];
extern Vec2f D_8010D1D4_fridged_bridges[4];
extern Vec2f D_8010D1FC_fridged_bridges[4][2];

void func_80105F34_fridged_bridges(omObjData *arg0);
void func_80108FBC_fridged_bridges(omObjData *arg0);
void func_80105F00_fridged_bridges(omObjData *arg0);
void func_801061C4_fridged_bridges(omObjData *arg0);
void func_8010641C_fridged_bridges(omObjData *arg0);
void func_80106438_fridged_bridges(omObjData *arg0);
void func_80106454_fridged_bridges(omObjData *arg0);
void func_80106470_fridged_bridges(omObjData *arg0);
void func_80108720_fridged_bridges(omObjData *arg0);
void func_80108C60_fridged_bridges(omObjData *arg0);
s32 func_80109D4C_fridged_bridges(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
s32 func_80109D6C_fridged_bridges(Vec *pos, s16 *face, Hu3DPoint *points);
void func_801075A4_fridged_bridges(omObjData *arg0);
void func_801075AC_fridged_bridges(omObjData *arg0);
void func_8010775C_fridged_bridges(omObjData *arg0);
void func_8010AE0C_fridged_bridges(void);
u16 func_8010AE98_fridged_bridges(f32 arg0);
void func_80109154_fridged_bridges(omObjData *arg0);
void func_80108B08_fridged_bridges(omObjData *arg0);
void func_80108BEC_fridged_bridges(omObjData *arg0);
void func_80107870_fridged_bridges(void);
void func_8010BEE8_fridged_bridges(void);
void func_8010C1D8_fridged_bridges(omObjData *arg0);
void func_801091F8_fridged_bridges(omObjData *arg0);
void func_80109390_fridged_bridges(omObjData *arg0);
void func_8010BDF0_fridged_bridges(void);
u16 func_8010ADC0_fridged_bridges(void);
void func_801062F8_fridged_bridges(omObjData *arg0);
void func_8010B164_fridged_bridges(void);
void func_8010B3EC_fridged_bridges(omObjData *arg0);
void func_8010648C_fridged_bridges(omObjData *arg0, s16 playerIndex);
void func_801068F4_fridged_bridges(omObjData *arg0);
s16 func_80108050_fridged_bridges(omObjData *arg0);
void func_8010BE0C_fridged_bridges(omObjData *arg0);
void func_80107164_fridged_bridges(omObjData *arg0);
void func_801079CC_fridged_bridges(omObjData *arg0, s8 *stickX, s8 *stickY);
void func_801082D0_fridged_bridges(omObjData *arg0);
void func_801084E0_fridged_bridges(omObjData *arg0);
s32 func_80109988_fridged_bridges(omObjData *arg0, FridgedBridgesProbe *probe);
u16 func_8010A0F4_fridged_bridges(omObjData *arg0, f32 x, f32 y, f32 z);
void func_8010B7CC_fridged_bridges(omObjData *arg0);
void func_8010733C_fridged_bridges(omObjData *arg0);
void func_80107510_fridged_bridges(omObjData *arg0);
void func_80109F84_fridged_bridges(omObjData *arg0);
void func_8010A1A4_fridged_bridges(omObjData *arg0);
void func_8010A360_fridged_bridges(omObjData *arg0);
void func_8010B8CC_fridged_bridges(omObjData *arg0);
void func_8010BB18_fridged_bridges(FridgedBridgesPlayer *player, Vec2f *a, Vec2f *b);
omObjData *func_8010BFD0_fridged_bridges(u16 type, u16 playerId, f32 x, f32 y, f32 z);
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

void func_801075A4_fridged_bridges(omObjData *arg0) {
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

// CPU input: walks the player along its path points, adjusting speed to avoid the foe.
void func_801079CC_fridged_bridges(omObjData *arg0, s8 *stickX, s8 *stickY) {
    FridgedBridgesPlayer *player;
    FridgedBridgesFoe *foe;
    u16 playerId;
    u16 lane;
    u16 point;
    f32 speed;
    f32 angle;
    f32 foeAngle;
    f32 dist;

    *stickY = 0;
    *stickX = 0;
    player = arg0->data;
    playerId = player->playerId;
    lane = player->unk_1E;
    point = player->unk_20;
    if (player->unk_6A != 0) {
        if (--player->unk_6A == 0) {
            player->unk_22 = -player->unk_22;
            player->unk_20 += player->unk_22;
        }
    }
    if (HuSqrtf((arg0->trans.x - D_8010D3A0_fridged_bridges[playerId][lane][point].x) *
                    (arg0->trans.x - D_8010D3A0_fridged_bridges[playerId][lane][point].x) +
                (arg0->trans.z - D_8010D3A0_fridged_bridges[playerId][lane][point].y) *
                    (arg0->trans.z - D_8010D3A0_fridged_bridges[playerId][lane][point].y)) < 80.0f) {
        player->unk_1E = func_80108050_fridged_bridges(arg0);
        player->unk_20 += player->unk_22;
        if (player->unk_20 == 11 && player->unk_22 == 1) {
            player->unk_22 = -1;
        }
        if (player->unk_20 == 0 && player->unk_22 == -1) {
            player->unk_22 = 1;
        }
        point = player->unk_20;
    }
    switch (GwPlayer[player->playerId].cpu_difficulty) {
        case 0:
            speed = 35.0f;
            break;
        case 1:
            speed = 42.0f;
            break;
        case 2:
            speed = 55.0f;
            break;
        case 3:
            speed = 65.0f;
            break;
    }
    speed *= player->unk_4C;
    if (player->unk_1E != 0) {
        speed *= 0.5f;
    }
    angle = atan2df(-(arg0->trans.x - D_8010D3A0_fridged_bridges[playerId][lane][point].x),
                    arg0->trans.z - D_8010D3A0_fridged_bridges[playerId][lane][point].y);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    foeAngle = atan2df(-(arg0->trans.x - D_8010DA78_fridged_bridges[player->playerId]->trans.x),
                       arg0->trans.z - D_8010DA78_fridged_bridges[player->playerId]->trans.z) -
               360.0f - angle;
    if (foeAngle < 0.0f) {
        foeAngle += 360.0f;
    }
    if (foeAngle > 180.0f) {
        foeAngle -= 360.0f;
    }
    dist = HuSqrtf((arg0->trans.x - D_8010DA78_fridged_bridges[player->playerId]->trans.x) *
                       (arg0->trans.x - D_8010DA78_fridged_bridges[player->playerId]->trans.x) +
                   (arg0->trans.z - D_8010DA78_fridged_bridges[player->playerId]->trans.z) *
                       (arg0->trans.z - D_8010DA78_fridged_bridges[player->playerId]->trans.z));
    foe = D_8010DA78_fridged_bridges[player->playerId]->data;
    if (foe->state == 1) {
        if (dist < 170.0f) {
            if (fabs(foeAngle) > 80.0) {
                speed = 65.0f;
            } else {
                if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                    speed = 65.0f;
                    angle = atan2df(-(arg0->trans.x - D_8010D3A0_fridged_bridges[playerId][lane][point - 1].x),
                                    arg0->trans.z - D_8010D3A0_fridged_bridges[playerId][lane][point - 1].y);
                }
                if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                    speed = 65.0f;
                    angle = atan2df(-(arg0->trans.x - D_8010D3A0_fridged_bridges[playerId][lane][point + 1].x),
                                    arg0->trans.z - D_8010D3A0_fridged_bridges[playerId][lane][point + 1].y);
                }
            }
        } else if (dist < 300.0f) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
        }
    } else if (foe->state == 0) {
        if (dist < 150.0f && foe->wait < 5) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 65.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 65.0f;
            }
        } else if (dist < 400.0f && foe->wait < 5) {
            if (player->unk_22 == 1 && player->unk_20 >= 7 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
            if (player->unk_22 == -1 && player->unk_20 >= 6 && player->unk_20 <= 8) {
                speed = 15.0f;
            }
        }
    }
    *stickX = sindf(angle) * speed;
    *stickY = cosdf(angle) * speed;
}

// Picks a CPU player's lane and speed multiplier based on its difficulty.
s16 func_80108050_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 lane;

    player->unk_4C = 1.0f;
    switch (GwPlayer[player->playerId].cpu_difficulty) {
        case 0:
            if ((u8)(rand8() % 10) < 6) {
                lane = 0;
            } else {
                lane = (u8)(rand8() % 3);
            }
            if ((u8)(rand8() % 10) < 4) {
                player->unk_4C = 0.8f;
            }
            break;
        case 1:
            if ((u8)(rand8() % 10) < 7) {
                lane = 0;
            } else {
                lane = (u8)(rand8() % 3);
            }
            if ((u8)(rand8() % 10) < 4) {
                player->unk_4C = 0.8f;
            }
            break;
        case 2:
            lane = 0;
            if ((u8)(rand8() % 10) < 5) {
                player->unk_4C = 0.8f;
            }
            break;
        case 3:
            lane = 0;
            if ((u8)(rand8() % 10) < 6) {
                player->unk_4C = 0.8f;
            }
            break;
    }
    return lane;
}

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

void func_801084E0_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    s16 playerId = player->playerId;
    omObjData *obj;
    FridgedBridgesItemWork *work;

    player->unk_28 = 0;
    func_8001C258_main(D_8010DA70_fridged_bridges->model[playerId * 5], 0x4000, 0);
    func_80108648_fridged_bridges(arg0);
    player->state = 0;
    obj = omAddObj(10, 0, 0, -1, func_80108C60_fridged_bridges);
    work = OM_GET_WORK_PTR(obj, FridgedBridgesItemWork);
    work->playerObj = arg0;
    work->phase = 0;
    work->fallSpeed = 3.0f;
    obj->trans.x = sindf(arg0->rot.y) * 80.0f + arg0->trans.x;
    obj->trans.z = cosdf(arg0->rot.y) * 80.0f + arg0->trans.z;
    obj->trans.y = arg0->trans.y + 80.0f;
    obj->rot.y = arg0->rot.y;
    obj->rot.x = obj->rot.z = 0.0f;
    Hu3DModelPosSet(D_8010DA70_fridged_bridges->model[playerId * 5], arg0->trans.x, arg0->trans.y, arg0->trans.z);
    Hu3DModelRotSet(D_8010DA70_fridged_bridges->model[playerId * 5], arg0->rot.x, arg0->rot.y, arg0->rot.z);
}

void func_80108648_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 motion;

    if (GwPlayer[player->playerId].chr == 5) {
        switch (player->motionState) {
            case 0:
                motion = arg0->motion[0];
                break;
            case 1:
                motion = arg0->motion[1];
                break;
            case 2:
                motion = arg0->motion[2];
                break;
        }
        func_8001C5B4_main(arg0->model[0], motion);
    } else {
        Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    }
}

void func_80108720_fridged_bridges(omObjData *arg0) {
    f32 sign[2][4];
    omObjData *obj;
    s32 i;
    s32 j;

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
            D_8010D9A0_fridged_bridges[i][j].x = D_8010D17C_fridged_bridges[j].x * sign[0][i];
            D_8010D9A0_fridged_bridges[i][j].y = D_8010D17C_fridged_bridges[j].y * sign[1][i];
        }
        D_8010DA00_fridged_bridges[i].x = D_8010D194_fridged_bridges.x * sign[0][i];
        D_8010DA00_fridged_bridges[i].y = D_8010D194_fridged_bridges.y * sign[1][i];
    }
    for (i = 0; i < 4; i++) {
        arg0->model[i * 5] = func_8000B108_main(0x450000, 0x20699);
        arg0->model[i * 5 + 1] = func_8000B108_main(0x450001, 0x699);
        arg0->model[i * 5 + 2] = func_8000B108_main(0x450002, 0x699);
        arg0->model[i * 5 + 3] = func_8000B108_main(0x450003, 0x699);
        arg0->model[i * 5 + 4] = func_8000B108_main(0x450000, 0x20699);
        func_8001C258_main(arg0->model[i * 5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(arg0->model[i * 5 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(arg0->model[i * 5 + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(arg0->model[i * 5 + 3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        func_8001C258_main(arg0->model[i * 5 + 4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(arg0->model[i * 5], D_8010CF48_fridged_bridges[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 1], D_8010CF48_fridged_bridges[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 2], D_8010CF48_fridged_bridges[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 3], D_8010CF48_fridged_bridges[i]);
        Hu3DModelCameraSet(arg0->model[i * 5 + 4], D_8010CF48_fridged_bridges[i]);
    }
    arg0->work[2] = 0;
    omMakeGroup(1, 12);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            func_8001C258_main(arg0->model[i * 5 + 1 + j], HU3D_ATTR_DISPOFF, 0);
            obj = omAddObj(10, 1, 0, 1, func_80108B08_fridged_bridges);
            obj->model[0] = arg0->model[i * 5 + 1 + j];
            omSetTra(obj, D_8010D9A0_fridged_bridges[i][j].x, 0.0f, D_8010D9A0_fridged_bridges[i][j].y);
            obj->work[0] = j * 5 + 15;
            obj->work[1] = 0;
            obj->work[2] = i;
        }
    }
    arg0->work[0] = 0;
    arg0->func = func_80108BEC_fridged_bridges;
}

void func_80108B08_fridged_bridges(omObjData *arg0) {
    if (arg0->work[0] == 0) {
        if (arg0->work[1] == 0) {
            func_8010BFD0_fridged_bridges(0, arg0->work[2], arg0->trans.x, -100.0f, arg0->trans.z);
            arg0->work[1] = 1;
            if (D_8010D19C_fridged_bridges == 0) {
                HuAudFXPlay(0x42C);
                D_8010D19C_fridged_bridges = 1;
            }
        }
        if (arg0->trans.y < -120.0f) {
            func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            omDelObj(arg0);
        } else {
            arg0->trans.y -= 8.0f;
        }
    } else {
        arg0->work[0]--;
    }
}

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

void func_80108C60_fridged_bridges(omObjData *arg0) {
    FridgedBridgesItemWork *work = OM_GET_WORK_PTR(arg0, FridgedBridgesItemWork);
    FridgedBridgesPlayer *player = work->playerObj->data;
    u16 modelId;

    if (work->phase == 0) {
        modelId = D_8010DA70_fridged_bridges->model[player->playerId * 5];
        arg0->trans.y -= work->fallSpeed;
        work->fallSpeed *= 1.4f;
        if (arg0->trans.y < -100.0f) {
            work->phase = 1;
            func_8010BFD0_fridged_bridges(0, player->playerId, arg0->trans.x, -160.0f, arg0->trans.z);
            func_8001C258_main(modelId, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            modelId = D_8010DA70_fridged_bridges->model[player->playerId * 5 + 1 + player->unk_24];
            func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5 + 1 + player->unk_24],
                               HU3D_ATTR_DISPOFF, 0);
            func_8004AC98_main(0x42B, player->playerId);
        }
        Hu3DModelPosSet(modelId, arg0->trans.x, arg0->trans.y, arg0->trans.z);
        Hu3DModelRotSet(modelId, arg0->rot.x, arg0->rot.y, arg0->rot.z);
    } else {
        modelId = D_8010DA70_fridged_bridges->model[player->playerId * 5 + 1 + player->unk_24];
        arg0->trans.y += 8.0f;
        if (arg0->trans.y >= 0.0f) {
            arg0->trans.y = 0.0f;
        }
        Hu3DModelPosSet(modelId, D_8010D9A0_fridged_bridges[player->playerId][player->unk_24].x, arg0->trans.y,
                        D_8010D9A0_fridged_bridges[player->playerId][player->unk_24].y);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        if (arg0->trans.y == 0.0f) {
            player->state = 1;
            player->unk_24++;
            omDelObj(arg0);
        }
    }
}

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

void func_80108FBC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    omObjData *obj;
    u32 bit;
    s32 i;

    for (i = 0; i < 4; i++) {
        player = D_8010DA64_fridged_bridges[i]->data;
        bit = 1 << i;
        if (!(bit & arg0->work[2]) && player->unk_26 != 3) {
            obj = omAddObj(30, 1, 0, -1, func_80109154_fridged_bridges);
            obj->model[0] = arg0->model[i * 5 + 4];
            omSetTra(obj, D_8010DA00_fridged_bridges[i].x, 25.0f, D_8010DA00_fridged_bridges[i].y);
            omSetSca(obj, 1.0f, 0.0f, 1.0f);
            omSetRot(obj, 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
            Hu3DModelScaleSet(obj->model[0], 1.0f, 0.0f, 1.0f);
            func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, 0);
            arg0->work[2] |= bit;
        }
    }
}

void func_80109154_fridged_bridges(omObjData *arg0) {
    f32 *scale = OM_GET_WORK_PTR(arg0, f32);

    *scale += 0.05f;
    if (*scale >= 1.0f) {
        *scale = 1.0f;
    }
    omSetSca(arg0, 1.0f, *scale, 1.0f);
    if (*scale == 1.0f) {
        omDelObj(arg0);
    }
}

#ifdef NON_MATCHING
// Register allocation differs (v0/v1 swapped) when indexing D_8010DA64 in the first loop.
void func_801091F8_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    s32 i;

    switch (D_8010D364_fridged_bridges) {
        case 0:
            if (D_8010D1A0_fridged_bridges == 0) {
                for (i = 0; i < 4; i++) {
                    if (OM_GET_DATA_PTR(D_8010DA64_fridged_bridges[i], FridgedBridgesPlayer)->unk_28 == 0) {
                        func_801082D0_fridged_bridges(D_8010DA64_fridged_bridges[i]);
                    }
                }
                D_8010D1A0_fridged_bridges = 1;
                func_8010AE0C_fridged_bridges();
            }
            WipeCreateIn(WIPE_TYPE_PREV, 16);
            D_8010D364_fridged_bridges = 1;
            break;
        case 1:
            if (WipeStatGet() == 0) {
                D_8010D364_fridged_bridges = 2;
                HuAudFXPlay(0x42E);
            }
            break;
        case 2:
            if (D_8010DA70_fridged_bridges->work[0] == 1) {
                D_8010D364_fridged_bridges = 3;
            }
            break;
        case 3:
            if (func_8010AE98_fridged_bridges(40.0f) == 1) {
                for (i = 0; i < 4; i++) {
                    player = D_8010DA64_fridged_bridges[i]->data;
                    player->unk_2C->work[0] = 1;
                }
                omDelObj(arg0);
                D_8010D35C_fridged_bridges = NULL;
                func_800E6F0C_minigame(1);
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_801091F8_fridged_bridges);
#endif

// Winner sequence: the winner walks to the goal and the camera zooms in.
void func_80109390_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player;
    omObjData *obj;
    s16 model;
    s32 i;

    switch (D_8010D366_fridged_bridges) {
        case 0:
            obj = D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges];
            func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            func_8001C258_main(obj->model[4], HU3D_ATTR_DISPOFF, 0);
            model = obj->model[0];
            obj->model[0] = obj->model[4];
            obj->model[4] = model;
            Hu3DMotionShiftSet(obj->model[0], Hu3DData[obj->motion[1]].motId, 0, 6, 2);
            obj->rot.y = atan2df(D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].x - obj->trans.x,
                                 D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].z - obj->trans.z);
            D_8010D366_fridged_bridges = 1;
            break;
        case 1:
            obj = D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges];
            if (HuSqrtf((D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].x - obj->trans.x) *
                            (D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].x - obj->trans.x) +
                        (D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].z - obj->trans.z) *
                            (D_8010D1A4_fridged_bridges[D_8010DA60_fridged_bridges].z - obj->trans.z)) < 80.0f) {
                D_8010D366_fridged_bridges = 2;
            } else {
                obj->trans.x += sindf(obj->rot.y) * 10.0f;
                obj->trans.z += cosdf(obj->rot.y) * 10.0f;
                Hu3DModelPosSet(obj->model[1], obj->trans.x, 0.0f, obj->trans.z);
            }
            break;
        case 2:
            D_8010D340_fridged_bridges = -650.0f / 30.0f;
            D_8010D344_fridged_bridges.x = 20.0f / 30.0f;
            D_8010D344_fridged_bridges.y = 0.0f;
            D_8010D344_fridged_bridges.z = 0.0f;
            D_8010D350_fridged_bridges = 30;
            D_8010D366_fridged_bridges = 3;
            D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->func = func_801075AC_fridged_bridges;
            D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->work[0] = 0;
            break;
        case 3:
            if (--D_8010D350_fridged_bridges != 0) {
                CZoomM[D_8010DA60_fridged_bridges] += D_8010D340_fridged_bridges;
                CRotM[D_8010DA60_fridged_bridges].x += D_8010D344_fridged_bridges.x;
                CRotM[D_8010DA60_fridged_bridges].y += D_8010D344_fridged_bridges.y;
                CRotM[D_8010DA60_fridged_bridges].z += D_8010D344_fridged_bridges.z;
            } else {
                CZoomM[D_8010DA60_fridged_bridges] = 1065.0f;
                CRotM[D_8010DA60_fridged_bridges].x = -40.0f;
                CRotM[D_8010DA60_fridged_bridges].y = 0.0f;
                CRotM[D_8010DA60_fridged_bridges].z = 0.0f;
                D_8010D366_fridged_bridges = 4;
            }
            break;
        case 4:
            if (D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->work[0] == 1 &&
                func_800E6E8C_minigame() == 4) {
                player = D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->data;
                func_80017954_main(D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->model[0], 2,
                                   GwPlayer[player->playerId].chr,
                                   D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->model[5]);
                Hu3DMotionShiftSet(
                    D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->model[0],
                    Hu3DData[D_8010DA64_fridged_bridges[D_8010DA60_fridged_bridges]->motion[5]].motId, 0, 6, 0);
                func_80045ED0_main(D_800A178C_main[GwPlayer[D_8010DA60_fridged_bridges].chr][0] | 0x2F);
                D_8010D366_fridged_bridges = 5;
                for (i = 0; i < 4; i++) {
                    obj = D_8010DA64_fridged_bridges[i];
                    player = obj->data;
                    if (player->state != 3 && player->playerId != D_8010DA60_fridged_bridges) {
                        obj->func = func_8010775C_fridged_bridges;
                    }
                    player->unk_44 = 1.0f;
                    if (player->playerId == D_8010DA60_fridged_bridges) {
                        GwPlayer[player->playerId].bonusCoin = 10;
                    }
                }
            }
            break;
        case 6:
            if (func_800E6E8C_minigame() == 4) {
                for (i = 0; i < 4; i++) {
                    obj = D_8010DA64_fridged_bridges[i];
                    player = obj->data;
                    if (player->state != 3) {
                        obj->func = func_8010775C_fridged_bridges;
                    }
                    player->unk_44 = 1.0f;
                }
                D_8010D366_fridged_bridges = 5;
            }
            break;
        case 5:
            break;
    }
}

// Probes the floor height at 8 points around probe->pos plus the center, against
// both the ice floor and the player's bridges. Returns the number of probe points
// that found no floor at all.
s32 func_80109988_fridged_bridges(omObjData *arg0, FridgedBridgesProbe *probe) {
    FridgedBridgesPlayer *player = arg0->data;
    Vec pos;
    s32 missCount = 0;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 angle;
    f32 height;
    f32 best;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    player->unk_1C = -1;
    for (i = 0; i < 9; i++) {
        if (i != 8) {
            angle = i * 45.0f;
            x = pos.x = sindf(angle) * 55.0f + probe->pos.x;
            y = pos.y = probe->pos.y;
            z = pos.z = cosdf(angle) * 55.0f + probe->pos.z;
        } else {
            x = pos.x = probe->pos.x;
            y = pos.y = probe->pos.y;
            z = pos.z = probe->pos.z;
        }
        best = probe->height[i] = -10000.0f;
        probe->bridgeIds[i] = 0xFFFF;
        points = (Hu3DPoint *)Hu3DData[D_8010DA6C_fridged_bridges->model[player->playerId]].hmf->unk50;
        func_80021C14_main(D_8010DA6C_fridged_bridges->model[player->playerId], &D_800EBEB0_minigame,
                           func_80109D4C_fridged_bridges, &pos);
        for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
             quad = func_80022198_main(&D_800EBEB0_minigame)) {
            height = func_800204F4_main(x, y, z, points, quad);
            if (height > best) {
                probe->height[i] = best = height;
                probe->bridgeIds[i] = quad->vtx[0] & 0x3F00;
                if (i == 8) {
                    player->unk_1C = probe->bridgeIds[8];
                }
            }
        }
        for (j = 0; j < player->unk_24; j++) {
            pos.x = x - D_8010D9A0_fridged_bridges[player->playerId][j].x;
            pos.z = z - D_8010D9A0_fridged_bridges[player->playerId][j].y;
            points = (Hu3DPoint *)Hu3DData[D_8010DA70_fridged_bridges->model[player->playerId * 5 + 1 + j]]
                         .hmf->unk50;
            func_80021C14_main(D_8010DA70_fridged_bridges->model[player->playerId * 5 + 1 + j],
                               &D_800EBEB0_minigame, func_80109D4C_fridged_bridges, &pos);
            for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
                 quad = func_80022198_main(&D_800EBEB0_minigame)) {
                height = func_800204F4_main(x, y, z, points, quad);
                if (height > best) {
                    probe->height[i] = best = height;
                    probe->bridgeIds[i] = player->unk_1C = quad->vtx[0] & 0x3F00;
                    if (i == 8) {
                        player->unk_1C = probe->bridgeIds[8];
                    }
                }
            }
        }
        if (best == -10000.0f) {
            missCount++;
        }
    }
    return missCount;
}

s32 func_80109D4C_fridged_bridges(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos) {
    return func_80109D6C_fridged_bridges(pos, vtx - 1, points);
}

// Same as func_800DA540_minigame, without the face type check.
s32 func_80109D6C_fridged_bridges(Vec *pos, s16 *face, Hu3DPoint *points) {
    f32 x;
    f32 z;
    s32 count;
    s32 i;
    s32 next;

    x = pos->x;
    z = pos->z;
    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (func_8002048C_main(x, z, &points[face[0]], &points[face[1]]) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

// Pushes a falling player away from the floor edges it is still touching.
void func_80109F84_fridged_bridges(omObjData *arg0) {
    FridgedBridgesProbe probe;
    f32 angle;
    f32 dx;
    f32 dz;
    u16 attempt;
    u16 missCount;
    u16 dir;
    u16 i;

    attempt = 0;
    do {
        probe.pos.x = arg0->trans.x;
        probe.pos.y = arg0->trans.y;
        probe.pos.z = arg0->trans.z;
        func_80109988_fridged_bridges(arg0, &probe);
        missCount = 0;
        for (i = 0; i < 8; i++) {
            if (probe.height[i] == -10000.0f) {
                missCount++;
            } else {
                dir = i + 4;
                if (dir >= 9) {
                    dir = i - 4;
                }
                angle = dir * 45.0f;
                dx = sindf(angle) * 5.0f;
                dz = cosdf(angle) * 5.0f;
                arg0->trans.x += dx;
                arg0->trans.z += dz;
            }
        }
    } while (missCount != 8 && ++attempt < 4);
}

// Returns 1 if the position is within reach of the player's dropped item.
u16 func_8010A0F4_fridged_bridges(omObjData *arg0, f32 x, f32 y, f32 z) {
    FridgedBridgesPlayer *player = arg0->data;
    u16 playerId = player->playerId;
    f32 dist;

    if (!(D_8010DA70_fridged_bridges->work[2] & (1 << playerId))) {
        return 0;
    }
    dist = HuSqrtf((x - D_8010DA00_fridged_bridges[playerId].x) * (x - D_8010DA00_fridged_bridges[playerId].x) +
                   (z - D_8010DA00_fridged_bridges[playerId].y) * (z - D_8010DA00_fridged_bridges[playerId].y));
    if (dist > HuSqrtf(6400.0f)) {
        return 0;
    }
    return 1;
}

void func_8010A1A4_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    FridgedBridgesRescue *rescue;
    omObjData *obj;
    f32 angle;
    f32 x;

    obj = player->bridgeObj = omAddObj(40, 1, 0, -1, func_8010A360_fridged_bridges);
    rescue = obj->data = HuMemAllocTag(sizeof(FridgedBridgesRescue), TAG_OVERLAY);
    rescue->playerObj = arg0;
    obj->model[0] = arg0->model[2];
    func_8001C258_main(obj->model[0], HU3D_ATTR_DISPOFF, 0);
    angle = (rand8() * rand8()) % 3600 / 10.0f;
    x = sindf(angle) * 600.0f + arg0->trans.x;
    omSetTra(obj, x, 500.0f, cosdf(angle) * 600.0f + arg0->trans.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    rescue->state = 0;
    rescue->released = 0;
    rescue->sfxId = -1;
    obj->func = func_8010A360_fridged_bridges;
}

// Rescue sequence for a player that fell off the bridges: fly in, pick the player
// up, carry them back to the start of the course and drop them off.
void func_8010A360_fridged_bridges(omObjData *arg0) {
    FridgedBridgesRescue *rescue = arg0->data;
    FridgedBridgesPlayer *player = rescue->playerObj->data;
    u16 playerId = player->playerId;
    Vec pos;
    Vec2f screen;
    f32 dist;

    switch (rescue->state) {
        case 0:
            if (D_8010DA68_fridged_bridges == 1) {
                rescue->state = 6;
                break;
            }
            dist = HuSqrtf((arg0->trans.x - rescue->playerObj->trans.x) * (arg0->trans.x - rescue->playerObj->trans.x) +
                           (arg0->trans.z - (rescue->playerObj->trans.z - 30.0f)) *
                               (arg0->trans.z - (rescue->playerObj->trans.z - 30.0f)));
            pos.x = arg0->trans.x;
            pos.y = arg0->trans.y;
            pos.z = arg0->trans.z;
            func_80012B14_main(player->playerId, &pos, &screen);
            screen.x -= D_8010D1D4_fridged_bridges[player->playerId].x;
            screen.y -= D_8010D1D4_fridged_bridges[player->playerId].y;
            if (screen.x >= 0.0f && screen.x < 160.0 && screen.y >= 0.0f && screen.y < 120.0f &&
                rescue->sfxId == -1) {
                rescue->sfxId = func_8004AC98_main(0x431, player->playerId);
            }
            if (dist > 18.0f) {
                arg0->trans.x += (rescue->playerObj->trans.x - arg0->trans.x) / dist * 18.0f;
                arg0->trans.z += (rescue->playerObj->trans.z - 30.0f - arg0->trans.z) / dist * 18.0f;
            } else {
                arg0->trans.x = rescue->playerObj->trans.x;
                arg0->trans.z = rescue->playerObj->trans.z - 30.0f;
                rescue->state = 1;
            }
            break;
        case 1:
            if (D_8010DA68_fridged_bridges == 1) {
                rescue->state = 6;
                break;
            }
            arg0->trans.y -= 30.0f;
            if (arg0->trans.y <= 10.0f) {
                arg0->trans.y = 10.0f;
                rescue->playerObj->func = func_801075A4_fridged_bridges;
                rescue->state = 2;
                func_8001C814_main(rescue->playerObj->model[0], 1, 1);
            }
            break;
        case 2:
            if (D_8010DA68_fridged_bridges == 1) {
                rescue->state = 7;
                break;
            }
            arg0->trans.y += 34.0f;
            omSetTra(rescue->playerObj, rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                     rescue->playerObj->trans.z);
            Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                            rescue->playerObj->trans.z);
            if (arg0->trans.y > 900.0f) {
                rescue->state = 3;
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
            break;
        case 3:
            if (D_8010DA68_fridged_bridges == 1) {
                rescue->state = 6;
                break;
            }
            dist = HuSqrtf((CenterM[playerId].x - player->pos.x) * (CenterM[playerId].x - player->pos.x) +
                           (CenterM[playerId].z - player->pos.z) * (CenterM[playerId].z - player->pos.z));
            if (dist > 18.0f) {
                CenterM[playerId].x += (player->pos.x - CenterM[playerId].x) / dist * 18.0f;
                CenterM[playerId].z += (player->pos.z - CenterM[playerId].z) / dist * 18.0f;
            } else {
                CenterM[playerId].x = player->pos.x;
                CenterM[playerId].z = player->pos.z;
                rescue->state = 4;
                omSetTra(arg0, player->pos.x, 900.0f, player->pos.z - 30.0f);
                omSetTra(rescue->playerObj, player->pos.x, 740.0f, player->pos.z);
                Hu3DModelPosSet(rescue->playerObj->model[0], rescue->playerObj->trans.x, rescue->playerObj->trans.y,
                                rescue->playerObj->trans.z);
                Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, rescue->playerObj->trans.y,
                                rescue->playerObj->trans.z);
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, 0);
                func_8001C258_main(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, 0);
            }
            break;
        case 4:
            if (D_8010DA68_fridged_bridges == 1) {
                rescue->state = 7;
                break;
            }
            arg0->trans.y -= 24.0f;
            omSetTra(rescue->playerObj, player->pos.x, arg0->trans.y - 160.0f, player->pos.z);
            Hu3DModelPosSet(rescue->playerObj->model[3], player->pos.x, arg0->trans.y - 160.0f, player->pos.z);
            if (arg0->trans.y < 160.0f) {
                arg0->trans.y = 160.0f;
                rescue->state = 5;
                func_8001C5B4_main(rescue->playerObj->model[0], rescue->playerObj->motion[0]);
                func_8001C814_main(rescue->playerObj->model[0], 2, 2);
                Hu3DModelPosSet(rescue->playerObj->model[1], rescue->playerObj->trans.x, 0.0f,
                                rescue->playerObj->trans.z);
                func_8001C258_main(rescue->playerObj->model[1], HU3D_ATTR_DISPOFF, 0);
                rescue->timer = 0;
                player->scale = 1.0f;
                func_8004AC98_main(0x430, player->playerId);
            }
            break;
        case 5:
            if (D_8010DA68_fridged_bridges == 1 && rescue->released == 1) {
                rescue->state = 6;
                func_8001C258_main(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, 0);
                player->state = 1;
                break;
            }
            arg0->trans.y += 40.0f;
            if (arg0->trans.y > 1500.0f) {
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
                break;
            }
            rescue->timer++;
            if (rescue->timer >= 30) {
                if (rescue->released == 0) {
                    rescue->released = 1;
                    func_8001C258_main(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, 0);
                    if (player->unk_28 == 1) {
                        func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           0);
                    }
                    func_8001C258_main(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    player->state = 1;
                    player->unk_08 = player->unk_0C = 0.0f;
                    player->unk_2C->work[0] = 1;
                    rescue->playerObj->func = func_801068F4_fridged_bridges;
                    if (player->unk_24 == 3) {
                        player->unk_1E = 0;
                        player->unk_22 = 1;
                    } else {
                        player->unk_1E = 0;
                        if (player->unk_28 == 0) {
                            player->unk_22 = -1;
                        } else {
                            player->unk_22 = 1;
                        }
                    }
                }
            } else {
                if (rescue->timer & 1) {
                    func_8001C258_main(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    if (player->unk_28 == 1) {
                        func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           HU3D_ATTR_DISPOFF);
                    }
                    func_8001C258_main(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, 0);
                } else {
                    func_8001C258_main(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, 0);
                    if (player->unk_28 == 1) {
                        func_8001C258_main(D_8010DA70_fridged_bridges->model[player->playerId * 5], HU3D_ATTR_DISPOFF,
                                           0);
                    }
                    func_8001C258_main(rescue->playerObj->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                }
                player->scale -= 0.03f;
                Hu3DModelScaleSet(rescue->playerObj->model[3], player->scale, player->scale, player->scale);
            }
            break;
        case 6:
            arg0->trans.y += 40.0f;
            if (arg0->trans.y > 1500.0f) {
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
            }
            break;
        case 7:
            arg0->trans.y += 40.0f;
            omSetTra(rescue->playerObj, arg0->trans.x, arg0->trans.y - 160.0f, arg0->trans.z + 30.0f);
            Hu3DModelPosSet(rescue->playerObj->model[3], rescue->playerObj->trans.x, arg0->trans.y - 160.0f,
                            rescue->playerObj->trans.z);
            if (arg0->trans.y > 1500.0f) {
                func_8001C258_main(rescue->playerObj->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                func_8001C258_main(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                if (rescue->sfxId != -1) {
                    HuAudFXStop(rescue->sfxId);
                }
                omDelObj(arg0);
            }
            break;
    }
}

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

void func_8010AE0C_fridged_bridges(void) {
    s32 i;

    D_8010DA20_fridged_bridges = 10;
    for (i = 0; i < 4; i++) {
        CenterM[i].x = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].x;
        CenterM[i].y = 100.0f;
        CenterM[i].z = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].y;
    }
}

// Pans each camera back along its path and zooms out. Returns 1 when every
// camera has reached the start of its path and is fully zoomed out.
u16 func_8010AE98_fridged_bridges(f32 speed) {
    f32 targetX;
    f32 targetZ;
    f32 centerX;
    f32 centerZ;
    f32 angle;
    f32 dx;
    f32 dz;
    f32 zoomStep = 12.5f;
    s32 doneCount = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (D_8010D1F4_fridged_bridges[i] == 0) {
            targetX = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].x;
            targetZ = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].y;
            centerX = CenterM[i].x;
            centerZ = CenterM[i].z;
            if (HuSqrtf((centerX - targetX) * (centerX - targetX) + (centerZ - targetZ) * (centerZ - targetZ)) <=
                speed) {
                if (D_8010DA20_fridged_bridges == 0) {
                    CenterM[i].x = D_8010D820_fridged_bridges[i][0].x;
                    CenterM[i].z = D_8010D820_fridged_bridges[i][0].y;
                    D_8010D1F4_fridged_bridges[i]++;
                } else {
                    D_8010DA20_fridged_bridges--;
                    targetX = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].x;
                    targetZ = D_8010D820_fridged_bridges[i][D_8010DA20_fridged_bridges].y;
                }
            }
            if (D_8010D1F4_fridged_bridges[i] == 0) {
                angle = atan2df(-(centerX - targetX), centerZ - targetZ);
                dx = sindf(angle) * speed;
                dz = -cosdf(angle) * speed;
                CenterM[i].x += dx;
                CenterM[i].z += dz;
            }
        } else {
            doneCount++;
        }
        if (CZoomM[i] < 1715.0f) {
            CZoomM[i] += zoomStep;
        }
        if (CZoomM[i] >= 1715.0f) {
            CZoomM[i] = 1715.0f;
            doneCount++;
        }
    }
    return doneCount == 8;
}

void func_8010B164_fridged_bridges(void) {
    FridgedBridgesFoe *foe;
    omObjData *obj;
    f32 angle;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_8010DA78_fridged_bridges[i] = omAddObj(30, 1, 0, -1, func_8010B3EC_fridged_bridges);
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x450010, 0x20699);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010DA78_fridged_bridges[0]->model[0]);
        }
        foe = obj->data = HuMemAllocTag(sizeof(FridgedBridgesFoe), TAG_OVERLAY);
        foe->state = 0;
        foe->dir = 0;
        foe->wait = 0;
        foe->index = i;
        omSetTra(obj, D_8010D1FC_fridged_bridges[i][0].x, -150.0f, D_8010D1FC_fridged_bridges[i][0].y);
        omSetSca(obj, 0.5f, 0.5f, 0.5f);
        Hu3DModelCameraSet(obj->model[0], D_8010CF48_fridged_bridges[i]);
        angle = atan2df(-(obj->trans.x - D_8010D1FC_fridged_bridges[i][1].x),
                        -(obj->trans.z - D_8010D1FC_fridged_bridges[i][1].y));
        if (angle < 0.0f) {
            angle += 360.0f;
        }
        omSetRot(obj, 0.0f, angle, 0.0f);
        func_8001C814_main(obj->model[0], 2, 2);
        foe->jumpDist = HuSqrtf((D_8010D1FC_fridged_bridges[i][0].x - D_8010D1FC_fridged_bridges[i][1].x) *
                                    (D_8010D1FC_fridged_bridges[i][0].x - D_8010D1FC_fridged_bridges[i][1].x) +
                                (D_8010D1FC_fridged_bridges[i][0].y - D_8010D1FC_fridged_bridges[i][1].y) *
                                    (D_8010D1FC_fridged_bridges[i][0].y - D_8010D1FC_fridged_bridges[i][1].y));
        foe->arcScale = 200.0f / ((foe->jumpDist / 2.0f) * (foe->jumpDist / 2.0f));
        foe->speed = 16.0f;
        foe->jumpPos = 0.0f;
        foe->unk_18 = -obj->rot.y;
        if (foe->unk_18 < 0.0f) {
            foe->unk_18 += 360.0f;
        }
    }
}

#ifdef NON_MATCHING
// Register allocation differs in case 2 (f2/f4 swapped for the turn angle and difference).
void func_8010B3EC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesFoe *foe = arg0->data;
    FridgedBridgesPlayer *player = D_8010DA64_fridged_bridges[foe->index]->data;
    f32 step;
    f32 t;
    f32 prevY;
    f32 angle;
    f32 diff;

    switch (foe->state) {
        case 0:
            if (player->state != 2 && player->state != 3 && func_800E6E8C_minigame() == 2) {
                if (foe->wait == 0) {
                    foe->state = 1;
                    foe->jumpPos = 0.0f;
                } else {
                    foe->wait--;
                }
            }
            break;
        case 1:
            if (foe->jumpPos > foe->jumpDist) {
                step = foe->jumpPos - foe->jumpDist;
                foe->state = 2;
            } else {
                step = foe->speed;
            }
            foe->jumpPos += step;
            t = foe->jumpPos - foe->jumpDist / 2.0f;
            prevY = arg0->trans.y;
            arg0->trans.y = -foe->arcScale * t * t + 60.0f;
            arg0->rot.x = atan2df(prevY - arg0->trans.y, step);
            arg0->trans.x += sindf(arg0->rot.y) * step;
            arg0->trans.z += cosdf(arg0->rot.y) * step;
            if (foe->state == 2) {
                func_8010BFD0_fridged_bridges(0, foe->index, arg0->trans.x, -100.0f, arg0->trans.z);
            }
            break;
        case 2:
            angle = atan2df(-(arg0->trans.x - D_8010D1FC_fridged_bridges[foe->index][foe->dir].x),
                            -(arg0->trans.z - D_8010D1FC_fridged_bridges[foe->index][foe->dir].y));
            arg0->rot.x = 0.0f;
            if (angle < arg0->rot.x) {
                angle += 360.0f;
            }
            if (angle != arg0->rot.y) {
                diff = angle - arg0->rot.y;
                if (diff < 0.0f) {
                    diff += 360.0f;
                }
                if (diff < 180.0f) {
                    if (diff > 13.5f) {
                        arg0->rot.y += 13.5f;
                    } else {
                        arg0->rot.y = angle;
                    }
                } else if (360.0f - diff > 13.5f) {
                    arg0->rot.y -= 13.5f;
                } else {
                    arg0->rot.y = angle;
                }
                if (arg0->rot.y < 0.0f) {
                    arg0->rot.y += 360.0f;
                }
                if (arg0->rot.y >= 360.0f) {
                    arg0->rot.y -= 360.0f;
                }
            } else if (player->state != 2 && player->state != 3 && func_800E6E8C_minigame() == 2) {
                foe->state = 0;
                foe->wait = (u8)(rand8() % 10) * 2 + 20;
                foe->dir ^= 1;
            }
            break;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_24_fridged_bridges/216670", func_8010B3EC_fridged_bridges);
#endif

// Pushes the player out of the foe's reach, stunning the player on first contact.
void func_8010B7CC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    omObjData *foeObj = D_8010DA78_fridged_bridges[player->playerId];
    f32 dist;
    f32 reach;

    dist = HuSqrtf((arg0->trans.x - foeObj->trans.x) * (arg0->trans.x - foeObj->trans.x) +
                   (arg0->trans.z - foeObj->trans.z) * (arg0->trans.z - foeObj->trans.z));
    reach = HuSqrtf(12100.0f);
    if (dist > reach) {
        return;
    }
    dist = reach - dist;
    arg0->trans.x += sindf(foeObj->rot.y) * dist;
    arg0->trans.z += cosdf(foeObj->rot.y) * dist;
    if (player->unk_56 == 0) {
        player->unk_56 = 1;
        player->unk_58 = 20;
        omVibrate(player->playerId, 20, 0, 20);
    }
}

// Snaps the player back onto the line between its two nearest path points.
void func_8010B8CC_fridged_bridges(omObjData *arg0) {
    FridgedBridgesPlayer *player = arg0->data;
    Vec2f a;
    Vec2f b;
    Vec2f unused; // unreferenced, pads the stack frame
    f32 slope;
    f32 offset;
    f32 t;

    if ((player->unk_68 == 0x1200) | (player->unk_68 == 0x100)) {
        player->pos.x = D_8010CFA4_fridged_bridges[player->playerId].x;
        player->pos.y = D_8010CFA4_fridged_bridges[player->playerId].y;
        player->pos.z = D_8010CFA4_fridged_bridges[player->playerId].z;
    } else if (player->unk_68 == 0x300) {
        player->pos.x = D_8010D9A0_fridged_bridges[player->playerId][0].x;
        player->pos.z = D_8010D9A0_fridged_bridges[player->playerId][0].y;
    } else if (player->unk_68 == 0x400) {
        player->pos.x = D_8010D9A0_fridged_bridges[player->playerId][1].x;
        player->pos.z = D_8010D9A0_fridged_bridges[player->playerId][1].y;
    } else if (player->unk_68 == 0x500) {
        player->pos.x = D_8010D9A0_fridged_bridges[player->playerId][2].x;
        player->pos.z = D_8010D9A0_fridged_bridges[player->playerId][2].y;
    }
    func_8010BB18_fridged_bridges(player, &a, &b);
    if (a.x != b.x) {
        slope = (a.y - b.y) / (a.x - b.x);
        if (slope != 0.0f) {
            offset = slope * a.x - a.y;
            slope = -slope;
            t = -((slope * player->pos.x + player->pos.z + offset) / (slope * slope + 1.0f));
            player->pos.x = slope * t + player->pos.x;
            player->pos.z = t + player->pos.z;
        } else {
            player->pos.z = a.y;
        }
    } else {
        player->pos.x = a.x;
    }
}

// Finds the CPU path point nearest to the player (a) and the closer of its two
// neighbors (b).
void func_8010BB18_fridged_bridges(FridgedBridgesPlayer *player, Vec2f *a, Vec2f *b) {
    Vec2f pos;
    Vec2f point;
    f32 dist;
    f32 best;
    s32 bestIndex;
    s32 prev;
    s32 next;
    s32 i;

    pos.x = player->pos.x;
    pos.y = player->pos.z;
    best = 100000.0f;
    bestIndex = 0;
    for (i = 0; i < 12; i++) {
        point.x = D_8010D3A0_fridged_bridges[player->playerId][0][i].x;
        point.y = D_8010D3A0_fridged_bridges[player->playerId][0][i].y;
        dist = HuSqrtf((point.x - pos.x) * (point.x - pos.x) + (point.y - pos.y) * (point.y - pos.y));
        if (dist < best) {
            best = dist;
            bestIndex = i;
        }
    }
    a->x = D_8010D3A0_fridged_bridges[player->playerId][0][bestIndex].x;
    a->y = D_8010D3A0_fridged_bridges[player->playerId][0][bestIndex].y;
    prev = bestIndex - 1;
    next = bestIndex + 1;
    if (prev < 0) {
        b->x = D_8010D3A0_fridged_bridges[player->playerId][0][next].x;
        b->y = D_8010D3A0_fridged_bridges[player->playerId][0][next].y;
    } else if (next == 12) {
        b->x = D_8010D3A0_fridged_bridges[player->playerId][0][prev].x;
        b->y = D_8010D3A0_fridged_bridges[player->playerId][0][prev].y;
    } else {
        dist = HuSqrtf((D_8010D3A0_fridged_bridges[player->playerId][0][prev].x - pos.x) *
                           (D_8010D3A0_fridged_bridges[player->playerId][0][prev].x - pos.x) +
                       (D_8010D3A0_fridged_bridges[player->playerId][0][prev].y - pos.y) *
                           (D_8010D3A0_fridged_bridges[player->playerId][0][prev].y - pos.y));
        if (dist < HuSqrtf((D_8010D3A0_fridged_bridges[player->playerId][0][next].x - pos.x) *
                               (D_8010D3A0_fridged_bridges[player->playerId][0][next].x - pos.x) +
                           (D_8010D3A0_fridged_bridges[player->playerId][0][next].y - pos.y) *
                               (D_8010D3A0_fridged_bridges[player->playerId][0][next].y - pos.y))) {
            b->x = D_8010D3A0_fridged_bridges[player->playerId][0][prev].x;
            b->y = D_8010D3A0_fridged_bridges[player->playerId][0][prev].y;
        } else {
            b->x = D_8010D3A0_fridged_bridges[player->playerId][0][next].x;
            b->y = D_8010D3A0_fridged_bridges[player->playerId][0][next].y;
        }
    }
}
