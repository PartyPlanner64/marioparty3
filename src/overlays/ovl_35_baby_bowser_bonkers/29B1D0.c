#include "common.h"
#include "overlays/minigame.h"
#include "gcc/memory.h"
#include "game/mallocblock.h"
#include "game/pause.h"
#include "game/input.h"
#include "math.h"

typedef struct UnkBabyBowserBonkers { // 0x12 bytes
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
} UnkBabyBowserBonkers;

typedef struct BabyBowserBonkersPlayer { // 0x50 bytes, 2 entries
    s16 unk_00;                          // player index
    s16 unk_02;                          // steps taken
    s16 unk_04;                          // whose turn
    s16 unk_06;
    f32 unk_08;
    s32 unk_0C;
    f32 unk_10;
    f32 unk_14;
    f32 unk_18;
    Vec unk_1C;
    s16 unk_28; // GwPlayer index
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    s16 unk_34;
    s16 unk_36;
    f32 unk_38;
    s16 unk_3C;
    s16 unk_3E;
    s16 unk_40;
    s16 unk_42;
    f32 unk_44;
    f32 unk_48;
    s16 unk_4C;
} BabyBowserBonkersPlayer;

typedef struct BabyBowserBonkersActor { // 0x30 bytes, 0xE entries
    s16 unk_00;
    s16 unk_02; // model index
    s16 unk_04;
    s16 unk_06; // state
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s32 unk_14;
    f32 unk_18; // timer
    f32 unk_1C;
    f32 unk_20;
    f32 unk_24;
    void *unk_28;                                    // callback
    void (*unk_2C)(struct BabyBowserBonkersActor *); // callback
} BabyBowserBonkersActor;

typedef struct BabyBowserBonkersStageWork {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ char unk05[0xAF];
} BabyBowserBonkersStageWork; // sizeof 0xB4

typedef struct BabyBowserBonkersSpawn {
    s16 unk_00; // time
    s16 unk_02; // actor index
} BabyBowserBonkersSpawn;

typedef struct BabyBowserBonkersPattern {
    s16 unk_00; // duration
    s16 unk_02;
    s16 unk_04;
    s16 unk_06; // spawn count
    BabyBowserBonkersSpawn *unk_08;
} BabyBowserBonkersPattern;

typedef union BabyBowserBonkersBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} BabyBowserBonkersBytes;

extern const s16 D_8010B950_baby_bowser_bonkers[];
extern BabyBowserBonkersActor *D_8010BC00_baby_bowser_bonkers[14];
extern const s16 D_8010B95C_baby_bowser_bonkers[];
extern omObjData *D_8010BC38_baby_bowser_bonkers;
extern s32 D_8010BC3C_baby_bowser_bonkers;
extern s32 D_8010BC40_baby_bowser_bonkers;
extern s32 D_8010BC44_baby_bowser_bonkers;
extern s32 D_8010BC48_baby_bowser_bonkers;
extern s32 D_8010BC4C_baby_bowser_bonkers;
extern s32 D_8010BC50_baby_bowser_bonkers;
extern s32 D_8010BC54_baby_bowser_bonkers;
extern s16 D_8010BC5C_baby_bowser_bonkers;
extern BabyBowserBonkersPattern *D_8010BC68_baby_bowser_bonkers[4][4];
extern BabyBowserBonkersPattern *D_8010B888_baby_bowser_bonkers;
extern s16 D_8010B88C_baby_bowser_bonkers;
extern s32 D_8010B890_baby_bowser_bonkers;
extern s32 D_8010B894_baby_bowser_bonkers[4];
extern Vec D_8010B8A4_baby_bowser_bonkers[];
extern f32 D_8010B8EC_baby_bowser_bonkers;
extern f32 D_8010B8F0_baby_bowser_bonkers;
extern f32 D_8010B8F4_baby_bowser_bonkers;
extern s32 D_8010B8BC_baby_bowser_bonkers[];
extern s32 D_8010B8DC_baby_bowser_bonkers[];
extern s32 D_8010B8E4_baby_bowser_bonkers[];
extern s32 D_8010B848_baby_bowser_bonkers[];
extern s32 D_8010B868_baby_bowser_bonkers[];
extern BabyBowserBonkersPlayer *D_8010BC58_baby_bowser_bonkers;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern D_80111B50_vine_with_me_Struct D_8010BD08_baby_bowser_bonkers;
extern UnkBabyBowserBonkers *D_8010BCAC_baby_bowser_bonkers;
extern BabyBowserBonkersActor *D_8010BC60_baby_bowser_bonkers;

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *object);
void func_80109E98_baby_bowser_bonkers(s32, s16);
void func_80108F9C_baby_bowser_bonkers(BabyBowserBonkersActor *);
void func_80105BB0_baby_bowser_bonkers(omObjData *object);
void func_80105C0C_baby_bowser_bonkers(omObjData *object);
void func_801062E8_baby_bowser_bonkers(omObjData *object);
void func_8010630C_baby_bowser_bonkers(omObjData *object);
void func_8010660C_baby_bowser_bonkers(omObjData *object);
void func_80106AA4_baby_bowser_bonkers(omObjData *object);
void func_80106CEC_baby_bowser_bonkers(omObjData *object);
f32 func_8010B148_baby_bowser_bonkers(f32 arg0, f32 arg1, f32 arg2);
s32 func_80107648_baby_bowser_bonkers(omObjData *object);
BabyBowserBonkersActor *func_8010919C_baby_bowser_bonkers(s32 arg0);
void func_801091D4_baby_bowser_bonkers(f32 x, f32 z, BabyBowserBonkersActor **list);
s32 func_801093D4_baby_bowser_bonkers(s32 arg0);
s16 func_8010943C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s16 playerIndex);
s16 func_8010958C_baby_bowser_bonkers(BabyBowserBonkersActor **list, s32 count, s16 playerIndex);
void func_8010B380_baby_bowser_bonkers(omObjData *arg0, u32 arg1);
void func_801076D8_baby_bowser_bonkers(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed);
void func_80107678_baby_bowser_bonkers(omObjData *arg0, s32 arg1, s32 arg2);
s32 func_80109080_baby_bowser_bonkers(s32 arg0, s16 arg1, s16 arg2);
s32 func_801096D0_baby_bowser_bonkers(void);
void func_8010AD00_baby_bowser_bonkers(f32 x, f32 y, f32 z, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7);
void func_801063B4_baby_bowser_bonkers(void);
void func_80107CD8_baby_bowser_bonkers(void);
void func_80107D38_baby_bowser_bonkers(omObjData *object);
void func_80107E54_baby_bowser_bonkers(omObjData *object);
void func_80108160_baby_bowser_bonkers(void);
void func_801081C0_baby_bowser_bonkers(omObjData *object);
void func_80109704_baby_bowser_bonkers(void);
void func_80109890_baby_bowser_bonkers(void);
void func_80109EB8_baby_bowser_bonkers(void);

void func_801059A0_baby_bowser_bonkers(void) {
    omObjData *obj;
    u8 camIndex;

    func_8001FE20_main(50);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800142A0_main(16);
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Hu3DGLightColorSet(0, 0xFF, 0xFF, 0xFF);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    Hu3DGLightDirSet(1, -56.0f, 50.0f, 56.0f);
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 30.0f, 80.0f, 4000.0f);
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    D_800EC1B8_minigame = 0;
    D_8010BC48_baby_bowser_bonkers = 900;
    D_8010BC44_baby_bowser_bonkers = 0;
    D_8010BC40_baby_bowser_bonkers = 0;
    D_8010BC4C_baby_bowser_bonkers = -1;
    D_8010BC50_baby_bowser_bonkers = 0;
    D_8010BC54_baby_bowser_bonkers = -1;
    D_8010BC5C_baby_bowser_bonkers = -1;
    D_8010BC38_baby_bowser_bonkers = omAddObj(0x20, 0, 0, -1, func_80105BB0_baby_bowser_bonkers);
    memset(&D_8010BD08_baby_bowser_bonkers, 0, 0x28);
    D_8010BD08_baby_bowser_bonkers.unk01 = 4;
    func_800E5EA0_minigame(&D_8010BD08_baby_bowser_bonkers);
    func_80045010_main(D_8010B950_baby_bowser_bonkers, 1);
    func_80045010_main(D_8010B95C_baby_bowser_bonkers, 1);
}

void func_80105BB0_baby_bowser_bonkers(omObjData *object) {
    object->func = func_80105C0C_baby_bowser_bonkers;
    func_80107CD8_baby_bowser_bonkers();
    func_80108160_baby_bowser_bonkers();
    func_801063B4_baby_bowser_bonkers();
    func_80109890_baby_bowser_bonkers();
    func_80109EB8_baby_bowser_bonkers();
    if (_CheckFlag(10)) {
        D_8010BC3C_baby_bowser_bonkers = 1;
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B950_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010B95C_baby_bowser_bonkers);

void func_80105C0C_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player1;
    BabyBowserBonkersPlayer *player2;
    s32 i;
    s32 done;
    s32 group;

    done = 0;
    switch (D_8010BC4C_baby_bowser_bonkers) {
        case -1:
            if (D_8010BC44_baby_bowser_bonkers > 0) {
                D_8010BC54_baby_bowser_bonkers = HuAudFXPlay(0x4AE);
                WipeCreateIn(WIPE_TYPE_PREV, 16);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 0:
            if (WipeStatGet() == 0) {
                GMesCreate(6);
                HuAudFXPlay(0xE);
                HuAudSeqPlay(0x36);
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 1:
            if (GMesStatGet() == 0) {
                GMesCreate(0x1A, (D_8010BC48_baby_bowser_bonkers + 29) / 30, 156, 32);
                func_800E6F0C_minigame(2);
                if (D_8010B888_baby_bowser_bonkers == NULL) {
                    D_8010BC44_baby_bowser_bonkers = 3;
                    D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[0][0];
                }
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 2:
            D_8010BC48_baby_bowser_bonkers--;
            func_8003F578_main((D_8010BC48_baby_bowser_bonkers + 29) / 30);
            if (D_8010BC48_baby_bowser_bonkers <= 0) {
                D_8010BC48_baby_bowser_bonkers = 0;
            }
            if (D_8010BC48_baby_bowser_bonkers >= 60) {
                for (i = 0; i < D_8010B888_baby_bowser_bonkers->unk_06; i++) {
                    if (D_8010BC44_baby_bowser_bonkers == D_8010B888_baby_bowser_bonkers->unk_08[i].unk_00) {
                        func_80109080_baby_bowser_bonkers(D_8010B888_baby_bowser_bonkers->unk_08[i].unk_02, 12,
                                                          D_8010B888_baby_bowser_bonkers->unk_02);
                    }
                }
            }
            if (D_8010B888_baby_bowser_bonkers->unk_04 == 0 || func_801096D0_baby_bowser_bonkers() != 0) {
                done = 1;
            }
            if (D_8010BC44_baby_bowser_bonkers >= D_8010B888_baby_bowser_bonkers->unk_00 && done) {
                if (D_8010BC48_baby_bowser_bonkers >= 600) {
                    group = 0;
                } else if (D_8010BC48_baby_bowser_bonkers >= 450) {
                    group = 1;
                } else {
                    group = (D_8010BC48_baby_bowser_bonkers < 300) ? 3 : 2;
                }
                if (++D_8010BC50_baby_bowser_bonkers >= 4) {
                    D_8010BC50_baby_bowser_bonkers = 0;
                }
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010B888_baby_bowser_bonkers = D_8010BC68_baby_bowser_bonkers[group][D_8010BC50_baby_bowser_bonkers];
            }
            if (D_8010BC48_baby_bowser_bonkers <= 0) {
                func_8003F5C0_main();
                GMesCreate(0x11);
                func_800E6F0C_minigame(3);
                func_80107678_baby_bowser_bonkers(D_800EC598_minigame[0], 0, 13);
                func_80107678_baby_bowser_bonkers(D_800EC598_minigame[1], 0, 13);
                HuAudSeqFadeOut(120);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 3:
            if (D_8010BC44_baby_bowser_bonkers == 15) {
                if (D_8010BC54_baby_bowser_bonkers != -1) {
                    func_8004AEF0_main((s16)D_8010BC54_baby_bowser_bonkers, 15);
                }
                D_8010BC54_baby_bowser_bonkers = -1;
            }
            if (GMesStatGet() == 0) {
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 4:
            if (D_8010BC44_baby_bowser_bonkers >= 15) {
                player1 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[0]);
                player2 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[1]);
                if (player1->unk_02 > player2->unk_02) {
                    GMesCreate(0x16, player1->unk_2C);
                    GwPlayer[player1->unk_28].bonusCoin += 10;
                    D_8010BC5C_baby_bowser_bonkers = player1->unk_2C;
                    D_8010BC50_baby_bowser_bonkers = 140;
                    player1->unk_04 = 0;
                    player2->unk_04 = 1;
                    HuAudSeqPlay(0x67);
                    func_8010AD00_baby_bowser_bonkers(D_800EC598_minigame[0]->trans.x, D_800EC598_minigame[0]->trans.y + 50.0,
                                                      D_800EC598_minigame[0]->trans.z, 65535.0f, 65535.0f, 65535.0f,
                                                      600.0f, 30);
                } else if (player1->unk_02 < player2->unk_02) {
                    GMesCreate(0x16, player2->unk_2C);
                    GwPlayer[player2->unk_28].bonusCoin += 10;
                    D_8010BC5C_baby_bowser_bonkers = player2->unk_2C;
                    D_8010BC50_baby_bowser_bonkers = 140;
                    player1->unk_04 = 1;
                    player2->unk_04 = 0;
                    HuAudSeqPlay(0x67);
                    func_8010AD00_baby_bowser_bonkers(D_800EC598_minigame[1]->trans.x, D_800EC598_minigame[1]->trans.y + 50.0,
                                                      D_800EC598_minigame[1]->trans.z, 65535.0f, 65535.0f, 65535.0f,
                                                      600.0f, 30);
                } else {
                    GMesCreate(0x20);
                    D_8010BC50_baby_bowser_bonkers = 144;
                    HuAudSeqPlay(0x6C);
                    player2->unk_04 = 1;
                    player1->unk_04 = 1;
                }
                func_800E6F0C_minigame(4);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 5:
            if (GMesStatGet() == 0) {
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        case 6:
            if (D_8010BC44_baby_bowser_bonkers >= 15) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 16);
                HuAudSeqFadeOut(16);
                func_8004AB0C_main(16);
                D_8010BC44_baby_bowser_bonkers = 0;
                D_8010BC4C_baby_bowser_bonkers++;
            }
            break;
        default:
            if (WipeStatGet() == 0) {
                object->func = func_801062E8_baby_bowser_bonkers;
            }
            break;
    }
    player1 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers]);
    player2 = func_8010B3AC_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers ^ 1]);
    func_801076D8_baby_bowser_bonkers(D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers],
                                      D_800EC598_minigame[D_8010B88C_baby_bowser_bonkers ^ 1], &player1->unk_1C,
                                      &player2->unk_1C, 0);
    D_8010B88C_baby_bowser_bonkers ^= 1;
    func_8010630C_baby_bowser_bonkers(object);
    D_8010BC40_baby_bowser_bonkers++;
    D_8010BC44_baby_bowser_bonkers++;
}

void func_801062E8_baby_bowser_bonkers(omObjData *object) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

void func_8010630C_baby_bowser_bonkers(omObjData *object) {
    if (D_8010B890_baby_bowser_bonkers != 0) {
        if (D_8010B890_baby_bowser_bonkers == 1) {
            object->func = func_801062E8_baby_bowser_bonkers;
        }
        D_8010B890_baby_bowser_bonkers--;
        return;
    }
    if (D_800D530C_main == 1 && WipeStatGet() == 0) {
        D_8010B890_baby_bowser_bonkers = 16;
        WipeCreateOut(WIPE_TYPE_NORMAL, (s16)D_8010B890_baby_bowser_bonkers);
        HuAudSeqFadeOut((s16)D_8010B890_baby_bowser_bonkers);
        func_8004AB0C_main((s16)D_8010B890_baby_bowser_bonkers);
    }
}

void func_801063B4_baby_bowser_bonkers(void) {
    s32 used[2];
    BabyBowserBonkersPlayer *player;
    s32 i;
    s32 j;
    s32 k;
    s32 found;
    s32 minGroup;

    used[0] = -1;
    used[1] = -1;
    D_8010BC58_baby_bowser_bonkers = HuMemAllocTag(sizeof(BabyBowserBonkersPlayer) * 2, TAG_OVERLAY);
    player = D_8010BC58_baby_bowser_bonkers;
    memset(player, 0, sizeof(BabyBowserBonkersPlayer) * 2);
    for (i = 0; i < 2; i++) {
        for (j = 0, minGroup = 99; j < 4; j++) {
            found = 0;
            for (k = 0; k < i; k++) {
                if (used[k] == D_8010B894_baby_bowser_bonkers[j]) {
                    found = 1;
                }
            }
            if (!found && GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group < minGroup) {
                minGroup = GwPlayer[D_8010B894_baby_bowser_bonkers[j]].group;
                D_8010BC58_baby_bowser_bonkers[i].unk_28 = D_8010B894_baby_bowser_bonkers[j];
            }
        }
        used[i] = D_8010BC58_baby_bowser_bonkers[i].unk_28;
    }
    func_800E19F0_minigame(1);
    func_800E18D8_minigame();
    D_800EB744_minigame = 1.4f;
    D_800EB748_minigame = 0.14f;
    D_800EB774_minigame = 1.46f;
    for (i = 0; i < 2; i++, player++) {
        player->unk_00 = i;
        D_800EC598_minigame[D_800EC280_minigame] = omAddObj(0x10, 14, 60, -1, func_8010660C_baby_bowser_bonkers);
        D_800EC598_minigame[D_800EC280_minigame]->trans.x = D_8010B8A4_baby_bowser_bonkers[i].x;
        D_800EC598_minigame[D_800EC280_minigame]->trans.z = D_8010B8A4_baby_bowser_bonkers[i].z;
        D_800EC598_minigame[D_800EC280_minigame]->trans.y = 39.100002f;
        func_8010B380_baby_bowser_bonkers(D_800EC598_minigame[D_800EC280_minigame], (u32)player);
        D_800EC280_minigame++;
    }
}

void func_8010660C_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    s32 variant;
    s16 gwIndex;
    s16 chr;
    s16 i;
    u32 model;
    s32 motionFile;
    s32 linkModel;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    gwIndex = player->unk_28;
    chr = GwPlayer[gwIndex].chr;
    player->unk_2C = chr;
    player->unk_2A = GwPlayer[gwIndex].pad;
    player->unk_2E = GwPlayer[gwIndex].stat & 1;
    player->unk_30 = GwPlayer[gwIndex].cpu_difficulty;
    model = D_800A178C_main[chr][0];
    motionFile = D_800A178C_main[chr][1];
    linkModel = D_800A178C_main[chr][2];
    func_800E1BA8_minigame(object, model, motionFile, gwIndex, 0x289, 0x299);
    data = object->data;
    data->unk50 &= ~1;
    data->unkEC = 0;
    object->model[3] = func_8000B108_main(3, 0x68D);
    object->model[4] = func_8000B108_main(4, 0x68D);
    for (i = 0; i < 3; i++) {
        object->model[7 + i] = func_8000B108_main(8, 0x68D);
    }
    object->model[13] = func_8000B108_main(model | linkModel, 0x28D);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5A00_minigame(object, 0x11, func_80017BB8_main(chr, 0xE), 0, 0);
    func_800E5A00_minigame(object, 0x12, func_80017BB8_main(chr, 0xF), 2, 0);
    func_800E5A00_minigame(object, 0x15, func_80017BB8_main(chr, 0x1F), 0, 0);
    func_800E5A00_minigame(object, 0x14, func_80017BB8_main(chr, 0x1D), 0, 0);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(object, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5978_minigame(object, 0x21, func_80017BB8_main(chr, 0x23), 2, 0);
    func_800E5A00_minigame(object, 0x22, func_80017BB8_main(chr, 0x24), 2, 0);
    variant = rand8() & 1;
    func_800E5A00_minigame(object, 0xD, func_80017BB8_main(chr, D_8010B8DC_baby_bowser_bonkers[variant]), 1, 120);
    player->unk_0C = D_8010B8BC_baby_bowser_bonkers[chr] | D_8010B8DC_baby_bowser_bonkers[variant];
    func_800E5A00_minigame(object, 0xE, func_80017BB8_main(chr, D_8010B8E4_baby_bowser_bonkers[rand8() & 1]), 1, 120);
    func_800E5690_minigame(object, 0);
    func_800E149C_minigame(object, 0, 2);
    player->unk_10 = player->unk_1C.x = 0.0f;
    player->unk_02 = 0;
    player->unk_04 = -1;
    player->unk_32 = -1;
    player->unk_34 = 0;
    player->unk_36 = 0;
    player->unk_38 = 1000.0 - player->unk_30 * 225.0;
    player->unk_08 = 0.0f;
    player->unk_3C = player->unk_30 * 6 + ((rand8() & 3) + 4);
    player->unk_3E = 0;
    player->unk_40 = 0;
    player->unk_42 = 0;
    player->unk_44 = player->unk_48 = 0.0f;
    object->func = func_80106AA4_baby_bowser_bonkers;
}

void func_80106AA4_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    f32 prevRot;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    data = object->data;
    player->unk_10 = object->trans.x;
    player->unk_14 = object->trans.y;
    player->unk_18 = object->trans.z;
    data->unk50 |= 0x8000;
    switch (func_800E6E8C_minigame()) {
        case 2:
            if (data->unk38 != 1000.0f) {
                object->trans.y -= 1.5000000596046448;
            }
            if (player->unk_2E != 0) {
                func_80106CEC_baby_bowser_bonkers(object);
            }
            break;
        case 3:
            data->unk3C = func_8010B148_baby_bowser_bonkers(0.0f, data->unk3C, 15.0f);
            break;
        case 4:
            switch (player->unk_04) {
                case 0:
                    if (func_800E5690_minigame(object, 0xD) != 0) {
                        func_80017790_main(object->model[0], 2, player->unk_2C,
                                           D_8010B848_baby_bowser_bonkers[player->unk_2C]);
                        func_80045F1C_main(player->unk_0C, -1, player->unk_00);
                        player->unk_04 = -1;
                    }
                    break;
                case 1:
                    if (func_800E5690_minigame(object, 0xE) != 0) {
                        func_80017790_main(object->model[0], 2, player->unk_2C,
                                           D_8010B868_baby_bowser_bonkers[player->unk_2C]);
                        player->unk_04 = -1;
                    }
                    break;
            }
            break;
    }
    prevRot = data->unk3C;
    func_800DDD94_minigame(object);
    player->unk_1C.x = object->trans.x - player->unk_10;
    player->unk_1C.y = object->trans.y - player->unk_14;
    player->unk_1C.z = object->trans.z - player->unk_18;
    data->unk3C = func_8010B148_baby_bowser_bonkers(data->unk3C, prevRot, 30.0f);
    func_80088910_main(Hu3DData[object->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
}

#ifdef NON_MATCHING
// Register allocation differs (player/data and dist/dz swap) and the original duplicates the dist != 0 test into
// the first branch of the retarget check.
void func_80106CEC_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersPlayer *player;
    func_800E1BA8_minigame_ObjData *data;
    BabyBowserBonkersActor *actor;
    HmfModel *model;
    f32 dist;
    f32 dz;
    f32 dx;
    f32 scale;
    f32 dx2;
    f32 dz2;
    s32 ready;
    s32 count;
    s32 i;

    player = func_8010B3AC_baby_bowser_bonkers(object);
    data = object->data;
    D_800CDA7C_main[player->unk_2A] = D_800D5558_main[player->unk_2A] = 0;
    D_800CBB6E_main[player->unk_2A] = 0;
    D_800D20A1_main[player->unk_2A] = 0;
    ready = (D_8010BC48_baby_bowser_bonkers >= 450 ? player->unk_3C / 2 : player->unk_3C) <= player->unk_02;
    if (data->unk38 != 1000.0f) {
        player->unk_42 = player->unk_02;
    }
    if (player->unk_42 < player->unk_02 && (ready || player->unk_30 == 0)) {
        dx = player->unk_44 - object->trans.x;
        dz = player->unk_44 - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist != 0.0f) {
            dx /= dist;
            dz /= dist;
        } else {
            dx = dz = 0.0f;
        }
        scale = dist / 100.0;
        if (scale >= 1.0f) {
            scale = 1.0f;
        }
        D_800CBB6E_main[player->unk_2A] = dx * 64.0f * scale;
        D_800D20A1_main[player->unk_2A] = -(dz * 64.0f * scale);
        D_800CDA7C_main[player->unk_2A] |= 0x8000;
        D_800D5558_main[player->unk_2A] = 0;
        return;
    }
    if (ready) {
        if (player->unk_3E != 0) {
            D_800CBB6E_main[player->unk_2A] = 0;
            D_800D20A1_main[player->unk_2A] = 0;
            if (!(player->unk_3E & 7) && player->unk_32 != -1) {
                D_800D5558_main[player->unk_2A] |= 0x8000;
                D_800CDA7C_main[player->unk_2A] |= 0x8000;
            }
            if (--player->unk_3E <= 0) {
                player->unk_40 = (u8)(rand8() % 15) + 15.0f + player->unk_30 * 5;
                player->unk_3E = 0;
            }
            return;
        }
        if (--player->unk_40 <= 0) {
            player->unk_3E = (u8)(rand8() % 15) + 15.0f - player->unk_30 * 5;
            player->unk_40 = 0;
        }
    }
    if (player->unk_32 != -1) {
        actor = func_8010919C_baby_bowser_bonkers(player->unk_32);
        if (actor == NULL) {
            player->unk_32 = -1;
            return;
        }
        model = &Hu3DData[actor->unk_02];
        dx = model->pos.x - object->trans.x;
        dz = model->pos.z - object->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 150.0 && dist > 50.0 && player->unk_34 >= 12 - player->unk_30 * 2 &&
            func_80107648_baby_bowser_bonkers(object) == 0 && actor->unk_04 != 0) {
            D_800D5558_main[player->unk_2A] |= 0x8000;
        }
        if (data->unk38 != 1000.0f) {
            D_800CDA7C_main[player->unk_2A] |= 0x8000;
        } else if ((func_801093D4_baby_bowser_bonkers(actor->unk_00) < 15.0f && player->unk_34 >= player->unk_36 &&
                    player->unk_38 <= dist) ||
                   (ready && !(rand8() & 0xF))) {
            func_801091D4_baby_bowser_bonkers(object->trans.x, object->trans.z, D_8010BC00_baby_bowser_bonkers);
            for (i = 0; i < 14; i++) {
                if (func_801093D4_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers[i]->unk_00) >= 225) {
                    model = &Hu3DData[D_8010BC00_baby_bowser_bonkers[i]->unk_02];
                    dx2 = model->pos.x - object->trans.x;
                    dz2 = model->pos.z - object->trans.z;
                    if (sqrtf(dx2 * dx2 + dz2 * dz2) <= player->unk_38) {
                        player->unk_32 = i;
                        return;
                    }
                }
            }
        }
        if ((actor->unk_06 == 4 || actor->unk_06 == 5 ||
             (actor->unk_04 == 0 && func_80107648_baby_bowser_bonkers(object) == 0)) &&
            player->unk_34 >= player->unk_36) {
            player->unk_32 = -1;
        } else {
            if (dist != 0.0f) {
                dx /= dist;
                dz /= dist;
            } else {
                dx = dz = 0.0f;
            }
            scale = dist / 100.0;
            if (scale >= 1.0f) {
                scale = 1.0f;
            }
            D_800CBB6E_main[player->unk_2A] = dx * 64.0f * scale;
            D_800D20A1_main[player->unk_2A] = -(dz * 64.0f * scale);
        }
    } else {
        func_801091D4_baby_bowser_bonkers(object->trans.x, object->trans.z, D_8010BC00_baby_bowser_bonkers);
        count = 7 - (s32)(player->unk_30 * 1.5f);
        if (count <= 0) {
            count = 1;
        }
        player->unk_32 = func_8010943C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, count, player->unk_00 ^ 1);
        if (player->unk_32 == -1) {
            player->unk_32 =
                func_8010958C_baby_bowser_bonkers(D_8010BC00_baby_bowser_bonkers, count, player->unk_00 ^ 1);
        }
        player->unk_36 = 39.0f - player->unk_30 * 7.5f;
        player->unk_34 = 0;
    }
    player->unk_34++;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80106CEC_baby_bowser_bonkers);
#endif

void func_801075F4_baby_bowser_bonkers(omObjData *arg0, f32 arg1, f32 arg2) {
    BabyBowserBonkersPlayer *player = func_8010B3AC_baby_bowser_bonkers(arg0);

    player->unk_02++;
    player->unk_44 = arg1;
    player->unk_48 = arg2;
    func_80109E98_baby_bowser_bonkers(player->unk_00, player->unk_02);
}

s32 func_80107648_baby_bowser_bonkers(omObjData *object) {
    return object->trans.y >= 44.1000009328126907;
}

void func_80107678_baby_bowser_bonkers(omObjData *arg0, s32 arg1, s32 arg2) {
    HmfModel *model;
    HmfModel *otherModel;
    HmfData *temp;

    model = &Hu3DData[arg0->model[(s16)arg1]];
    otherModel = &Hu3DData[arg0->model[(s16)arg2]];

    temp = model->hmf;
    model->hmf = otherModel->hmf;
    otherModel->hmf = temp;
}

void func_801076D8_baby_bowser_bonkers(omObjData *obj1, omObjData *obj2, Vec *vel1, Vec *vel2, s16 recursed) {
    omObjData *mover;
    omObjData *other;
    func_800E1BA8_minigame_ObjData *moverData;
    func_800E1BA8_minigame_ObjData *otherData;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 minDist;
    f32 scale;
    f32 limit;
    f32 pushX;
    f32 pushZ;
    u16 pushed;

    pushed = 0;
    if (recursed == 0) {
        if ((vel1->x != 0.0f || vel1->z != 0.0f) && vel2->x == 0.0f && vel2->z == 0.0f) {
            mover = obj1;
            other = obj2;
        } else if ((vel2->x != 0.0f || vel2->z != 0.0f) && vel1->x == 0.0f && vel1->z == 0.0f) {
            mover = obj2;
            other = obj1;
        } else if (obj1->trans.y > obj2->trans.y) {
            mover = obj1;
            other = obj2;
        } else if (obj2->trans.y > obj1->trans.y) {
            mover = obj2;
            other = obj1;
        } else {
            mover = obj1;
            other = obj2;
        }
    } else {
        mover = obj1;
        other = obj2;
    }
    moverData = mover->data;
    otherData = other->data;
    dx = mover->trans.x - other->trans.x;
    dz = mover->trans.z - other->trans.z;
    dist = sqrtf(dx * dx + dz * dz);
    minDist = (moverData->unk48 + otherData->unk48) * 0.75f;
    if (dist < minDist && mover->trans.y >= other->trans.y &&
        mover->trans.y <= other->trans.y + otherData->unk34) {
        if (dist != 0.0f) {
            scale = minDist / dist;
        } else {
            if (minDist == 0.0f) {
                dx = dz = 0.0f;
            } else {
                if (other->trans.x >= 0.0f) {
                    dx = minDist / 1.4142f;
                } else {
                    dx = -minDist / 1.4142f;
                }
                if (other->trans.z >= 0.0f) {
                    dz = minDist / 1.4142f;
                } else {
                    dz = -minDist / 1.4142f;
                }
            }
            scale = 1.0f;
        }
        mover->trans.x = dx * scale + other->trans.x;
        mover->trans.z = dz * scale + other->trans.z;
        pushed = 1;
    }
    pushZ = 0.0f;
    pushX = 0.0f;
    limit = 469.999980926513672 - moverData->unk48;
    if (mover->trans.x > limit) {
        pushX = limit - mover->trans.x;
        mover->trans.x = limit;
    } else if (mover->trans.x < -limit) {
        pushX = -limit - mover->trans.x;
        mover->trans.x = -limit;
    }
    if (mover->trans.z > limit) {
        pushZ = limit - mover->trans.x;
        mover->trans.z = limit;
    } else if (mover->trans.z < -limit) {
        pushZ = -limit - mover->trans.x;
        mover->trans.z = -limit;
    }
    limit = 469.999980926513672 - otherData->unk48;
    if (other->trans.x > limit) {
        other->trans.x = limit;
    } else if (other->trans.x < -limit) {
        other->trans.x = -limit;
    }
    if (other->trans.z > limit) {
        other->trans.z = limit;
    } else if (other->trans.z < -limit) {
        other->trans.z = -limit;
    }
    if (pushX == 0.0f && pushZ == 0.0f) {
        return;
    }
    if (pushed) {

        dx = mover->trans.x - other->trans.x;
        dz = mover->trans.z - other->trans.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < minDist && mover->trans.y >= other->trans.y &&

            mover->trans.y <= otherData->unk34 * 0.5f + other->trans.y) {
            other->trans.x += pushX;
            other->trans.z += pushZ;
            if (other->trans.x > limit) {
                other->trans.x = limit;
            } else if (other->trans.x < -limit) {
                other->trans.x = -limit;
            }
            if (other->trans.z > limit) {
                other->trans.z = limit;
            } else if (other->trans.z < -limit) {
                other->trans.z = -limit;
            }
        }
        if (recursed == 0) {
            func_801076D8_baby_bowser_bonkers(other, mover, NULL, NULL, 1);
        }
    }
}

void func_80107CD8_baby_bowser_bonkers(void) {
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 16, 0, -1, func_80107D38_baby_bowser_bonkers);
    func_800E1490_minigame(0);
}

void func_80107D38_baby_bowser_bonkers(omObjData *object) {
    BabyBowserBonkersStageWork *work;

    work = HuMemAllocTag(sizeof(BabyBowserBonkersStageWork), TAG_OVERLAY);
    object->data = work;
    memset(work, 0, sizeof(BabyBowserBonkersStageWork));
    work->unk03 = 1;
    work->unk04 = 0;
    func_800E131C_minigame(object, 20.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 10.0f);
    func_800E139C_minigame(object, 39.100002f, -939.99994f, -939.99994f, 939.99994f, 939.99994f);
    object->model[0] = func_8000B0A0_main(0x560000, 0x10099);
    func_8001C954_main(object->model[0]);
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    object->model[1] = func_8000B0A0_main(0x560001, 0x99);
    object->model[2] = func_8000B0A0_main(0x560002, 0x99);
    object->func = func_80107E54_baby_bowser_bonkers;
}

void func_80107E54_baby_bowser_bonkers(omObjData *object) {
    func_8001E65C_main(object->model[0], sindf(D_8010B8EC_baby_bowser_bonkers) * 15.0f,
                       -D_8010B8F0_baby_bowser_bonkers, 64, 64);
    func_8001F6BC_main(object->model[0], (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f), 0, 0,
                       (u8)(cosdf(D_8010B8F4_baby_bowser_bonkers) * 32.0f + 32.0f));
    func_8001F6F8_main(object->model[0], 64, 32, 32, 0);
    if (omPauseChk() + D_800D6A90_main == 0) {
        D_8010B8EC_baby_bowser_bonkers += 0.5f;
        if (D_8010B8EC_baby_bowser_bonkers >= 360.0f) {
            D_8010B8EC_baby_bowser_bonkers -= 360.0f;
        }
        D_8010B8F0_baby_bowser_bonkers += 0.2f;
        if (D_8010B8F0_baby_bowser_bonkers >= 64.0f) {
            D_8010B8F0_baby_bowser_bonkers -= 64.0f;
        }
        D_8010B8F4_baby_bowser_bonkers += 2.4f;
        if (D_8010B8F4_baby_bowser_bonkers >= 360.0f) {
            D_8010B8F4_baby_bowser_bonkers -= 360.0f;
        }
    }
}

s32 func_801080D0_baby_bowser_bonkers(f32 arg0, f32 arg1) {
    if (__builtin_fabs((f64)arg0) < 200.0 && __builtin_fabs((f64)arg1) < 200.0) {
        return 0;
    }
    if (arg0 > 0.0f) {
        if (arg1 > 0.0f) {
            return 1;
        }
        return 2;
    }
    if (arg1 > 0.0f) {
        return 3;
    }
    return 4;
}

void func_80108160_baby_bowser_bonkers(void) {
    D_8010BC60_baby_bowser_bonkers = HuMemAllocTag(sizeof(BabyBowserBonkersActor) * 14, TAG_OVERLAY);
    memset(D_8010BC60_baby_bowser_bonkers, 0, sizeof(BabyBowserBonkersActor) * 14);
    omAddObj(2, 8, 0, -1, func_801081C0_baby_bowser_bonkers);
    func_80109704_baby_bowser_bonkers();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801081C0_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010831C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108454_baby_bowser_bonkers);

void func_801089CC_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;

    actor->unk_06 = 0;
    actor->unk_04 = 0;
    actor->unk_08 = -1;
    actor->unk_18 = 0;
    model->attr |= HU3D_ATTR_DISPOFF;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108A0C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108B84_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108D6C_baby_bowser_bonkers);

void func_80108E90_baby_bowser_bonkers(BabyBowserBonkersActor *actor) {
    HmfModel *model = Hu3DData + actor->unk_02;
    f32 scale;

    actor->unk_06 = 4;
    actor->unk_04 = 0;
    actor->unk_18 = 110.0f;
    scale = 1.0f - (f32)actor->unk_0A / 5.0f;
    if (scale <= 0.0f) {
        scale = 0.0f;
    }
    model->scale.x = 1.0f;
    model->scale.z = 1.0f;
    model->scale.y = 0.4f - scale * 0.35f;
    model->motSpeed = 0.0f;
    if (15.0f <= (f32)actor->unk_0A) {
        actor->unk_0A = 0;
        actor->unk_2C = func_80108F9C_baby_bowser_bonkers;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80108F9C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109080_baby_bowser_bonkers);

BabyBowserBonkersActor *func_8010919C_baby_bowser_bonkers(s32 arg0) {
    if (arg0 < 14) {
        if (arg0 >= 0) {
            return &D_8010BC60_baby_bowser_bonkers[arg0];
        }
    }
    return NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_801091D4_baby_bowser_bonkers);

s32 func_80109388_baby_bowser_bonkers(UnkBabyBowserBonkers *arg0, s32 arg1) {
    if (arg0->unk_08 == 0) {
        return 0;
    }
    switch (arg0->unk_06) {
        case 1:
            return 1;
        case 2:
            if (arg0->unk_0A > arg0->unk_0E - arg1) {
                return 1;
            }
            break;
    }
    return 0;
}

s32 func_801093D4_baby_bowser_bonkers(s32 arg0) {
    BabyBowserBonkersActor *actor = &D_8010BC60_baby_bowser_bonkers[arg0];

    if (actor->unk_08 != 0) {
        switch (actor->unk_06) {
            case 1:
                return actor->unk_0E;
            case 2:
                return actor->unk_0E - actor->unk_0A;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010943C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010958C_baby_bowser_bonkers);

s32 func_801096D0_baby_bowser_bonkers(void) {
    s32 i;
    BabyBowserBonkersActor *actor;

    for (i = 0, actor = D_8010BC60_baby_bowser_bonkers; i < 14; i++, actor++) {
        if (actor->unk_06 != 0) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109704_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010984C_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109890_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109990_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109BFC_baby_bowser_bonkers);

void func_80109E98_baby_bowser_bonkers(s32 arg0, s16 arg1) {
    s16 *field = &D_8010BCAC_baby_bowser_bonkers[arg0].unk_0E;

    *field = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109EB8_baby_bowser_bonkers);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", D_8010BA00_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_80109FE8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010A6D8_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AB14_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AD00_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010AEF0_baby_bowser_bonkers);

f32 func_8010B044_baby_bowser_bonkers(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B148_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B308_baby_bowser_bonkers);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_35_baby_bowser_bonkers/29B1D0", func_8010B320_baby_bowser_bonkers);

void func_8010B380_baby_bowser_bonkers(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

BabyBowserBonkersPlayer *func_8010B3AC_baby_bowser_bonkers(omObjData *arg0) {
    BabyBowserBonkersBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return (BabyBowserBonkersPlayer *)packed.word;
}
