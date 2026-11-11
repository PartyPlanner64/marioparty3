#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/hmfanim.h"
#include "game/hmfspr.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/pause.h"
#include "game/util.h"
#include "game/wipe.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

// Per-player info, indexed by group through D_8010D308_awful_tower
typedef struct {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player;
    /* 0x02 */ s8 group;
    /* 0x03 */ u8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk05[3];
    /* 0x08 */ s32 unk08;
} AwfulTowerPlayer; // Size 0xC

extern s32 D_800A178C_main[][6];

extern s32 D_8010CB60_awful_tower[];
extern D_80111B50_vine_with_me_Struct D_8010CB70_awful_tower;
extern s32 D_8010CB98_awful_tower[];
extern AwfulTowerPlayer D_8010D2D8_awful_tower[4];
extern AwfulTowerPlayer *D_8010D308_awful_tower[4];
extern f32 D_8010D320_awful_tower[4];
extern u16 D_8010D348_awful_tower[4][3];
extern omObjData *D_8010D360_awful_tower[4][3];
extern omObjData *D_8010D390_awful_tower[5];
extern omObjData *D_8010D3A8_awful_tower[4];
extern s16 D_8010D3B8_awful_tower[4];
extern s16 D_8010D3D0_awful_tower[4];
extern u8 D_8010D330_awful_tower[4][5];
extern u8 D_8010D3CC_awful_tower[4];
extern u16 D_8010D3D8_awful_tower;
extern u32 D_8010D3DC_awful_tower;
extern s16 D_8010D3E4_awful_tower;
extern omObjData *D_8010D3E8_awful_tower;
extern s16 D_8010D3EC_awful_tower[2];
extern s8 D_8010D3FC_awful_tower;
extern u8 D_8010D3FD_awful_tower;
extern u8 D_8010D3FE_awful_tower;

void func_801061FC_awful_tower(omObjData *object);
void func_80107734_awful_tower(omObjData *object);
void func_80107858_awful_tower(void);
void func_80108880_awful_tower(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void func_80108E8C_awful_tower(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_801059A0_awful_tower);

void func_8010600C_awful_tower(void) {
    func_80107858_awful_tower();
}

void func_80106028_awful_tower(omObjData *object) {
    s32 i;
    s32 group;

    D_8010D3D8_awful_tower = 0;
    D_8010D3E4_awful_tower = 0;
    D_8010D3DC_awful_tower = 0;
    D_8010D3FC_awful_tower = 5;
    D_8010D3FD_awful_tower = 0;
    D_8010D3FE_awful_tower = 0;
    D_8010D320_awful_tower[0] = 650.0f;
    D_8010D320_awful_tower[1] = 650.0f;
    D_8010D320_awful_tower[2] = 650.0f;
    D_8010D320_awful_tower[3] = 650.0f;
    for (i = 0; i < 4; i++) {
        D_8010D330_awful_tower[i][0] = D_8010D330_awful_tower[i][1] = D_8010D330_awful_tower[i][2] =
            D_8010D330_awful_tower[i][3] = D_8010D330_awful_tower[i][4] = 1;
        D_8010D308_awful_tower[i] = &D_8010D2D8_awful_tower[i];
        bzero(&D_8010D2D8_awful_tower[i], sizeof(AwfulTowerPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = D_8010D3CC_awful_tower[i] = GwPlayer[i].group;
        D_8010D308_awful_tower[group]->player = i;
        D_8010D308_awful_tower[group]->pad = GwPlayer[i].pad;
        D_8010D308_awful_tower[group]->chr = GwPlayer[i].chr;
        D_8010D308_awful_tower[group]->group = group;
        D_8010D308_awful_tower[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    object->func = func_801061FC_awful_tower;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CCE0_awful_tower);

void func_801061FC_awful_tower(omObjData *object) {
    u8 motions[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 winFiles[2][8] = {
        { 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0xA4, 0x1B },
        { 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0xA5, 0x1C },
    };
    s8 chr;
    s16 i;

    D_8010D3DC_awful_tower++;
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (D_8010D3DC_awful_tower == 51 && D_8010D3D8_awful_tower == 0 && D_800D530C_main == 0) {
                HuAudSeqPlay(0x33);
            }
            break;
        case 3:
            if (D_8010D3FE_awful_tower >= 20) {
                func_800E6F1C_minigame();
            }
            break;
    }
    func_800E6F40_minigame();
    switch (D_8010D3E4_awful_tower) {
        case 0:
            if (func_800E6E8C_minigame() == 1) {
                D_8010D3E4_awful_tower = 1;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 1:
            if (func_800E6E8C_minigame() == 2) {
                D_8010D3E4_awful_tower = 2;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 2:
            if (D_8010D3FC_awful_tower != 5 || func_800E6E8C_minigame() == 3) {
                if (D_8010D3FC_awful_tower == 5) {
                    D_8010D3E4_awful_tower = 6;
                    D_8010D3FC_awful_tower = 4;
                } else {
                    D_8010D3E4_awful_tower = 3;
                }
                D_8010D3DC_awful_tower = 0;
            }
            if (D_8010D3E4_awful_tower != 3) {
                break;
            }
        case 3:
            if (D_8010D3DC_awful_tower == 0) {
                D_8010CB70_awful_tower.unk22 = 210;
                if (func_800E6E8C_minigame() != 3) {
                    func_800E6F1C_minigame();
                }
                D_8010CB70_awful_tower.unk06 = 0;
                D_8010CB70_awful_tower.unk18[0] = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->player;
                GwPlayer[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->player].bonusCoin = 10;
            }
            if (D_8010D3DC_awful_tower == 2) {
                func_800E6F34_minigame(30);
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010D3E4_awful_tower = 4;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 6:
            if (D_8010D3DC_awful_tower == 1) {
                D_8010CB70_awful_tower.unk06 = 4;
                D_8010CB70_awful_tower.unk24 = 0x90;
            }
            if (func_800E6E8C_minigame() == 4) {
                D_8010D3E4_awful_tower = 5;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 4:
            if (D_8010D3DC_awful_tower == 1) {
                chr = D_8010D308_awful_tower[D_8010D3FC_awful_tower]->chr;
                D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9] =
                    func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x4AD);
                D_8010D3EC_awful_tower[0] =
                    func_80017790_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1, motions[chr],
                                       (chrDirs[chr] << 16) | winFiles[0][chr]);
                D_8010D3EC_awful_tower[1] = func_80017AD8_main((chrDirs[chr] << 16) | winFiles[1][chr]);
                func_8001C514_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]);
                Hu3DModelCameraSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0], 4, 4);
                func_8001C258_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 4, 0);
                Hu3DMotionTimeSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                  Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[0]].motTime);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 2);
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.x =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.x;
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.y =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.y;
                Hu3DData[D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9]].pos.z =
                    D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->trans.z;
            }
            if (D_8010D3DC_awful_tower < 16) {
                Hu3DModelRotSet(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 0.0f,
                                D_8010D3DC_awful_tower / 15.0f * 90.0f + -90.0f, 0.0f);
            }
            if (D_8010D3DC_awful_tower == 30) {
                func_8001C5B4_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9],
                                   D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[10]);
                func_8001C814_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 2, 0);
                func_80017954_main(D_8010D3A8_awful_tower[D_8010D3FC_awful_tower]->model[9], 1,
                                   motions[D_8010D308_awful_tower[D_8010D3FC_awful_tower]->chr],
                                   D_8010D3EC_awful_tower[1]);
                func_80045ED0_main(D_8010D308_awful_tower[D_8010D3FC_awful_tower]->unk08);
            }
        case 5:
            if (D_8010D3E4_awful_tower == 5 && D_8010D3DC_awful_tower == 1) {
                for (i = 0; i < 4; i++) {
                    func_800E5690_minigame(D_8010D3A8_awful_tower[i], 14);
                }
            }
            if (func_800E6E8C_minigame() == 5) {
                D_8010D3E4_awful_tower = 7;
                D_8010D3DC_awful_tower = 0;
            }
            break;
        case 7:
            if (D_8010D3DC_awful_tower == 1) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            } else if (D_8010D3DC_awful_tower >= 32) {
                D_8010D3D8_awful_tower = 1;
            }
            break;
    }
    if (D_8010D3D8_awful_tower != 0 || D_800D530C_main != 0) {
        if (D_800D530C_main != 0) {
            if (D_8010D3FD_awful_tower == 0) {
                WipeCreateOut(WIPE_TYPE_NORMAL, 20);
                HuAudSeqFadeOut(20);
                func_8004AB0C_main(20);
            }
            D_8010D3FD_awful_tower++;
            if (D_8010D3FD_awful_tower < 25) {
                return;
            }
        } else {
            HuAudSeqFadeOut(30);
        }
        omOvlReturnEx(1);
    }
}

void func_80106A9C_awful_tower(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->model[0] = func_8000B0A0_main(0x460006, 0x499);
    func_8001C2FC_main(object->model[0], 0x600, 0);
    Hu3DLLightCreate(object->model[0], 1);
    Hu3DLLightColorSet(object->model[0], 0xFF, 0xFF, 0xFF);
    Hu3DLLightDirSet(object->model[0], 0.0f, 0.0f, 127.0f);
    object->trans.y = object->trans.z = 0.0f;
    object->trans.x = 1500.0f;
    object->trans.y = -60.0f;
    object->trans.z = 300.0f;
    omSetRot(object, 90.0f, 0.0f, 0.0f);
    omSetSca(object, 1000.0f, 1.0f, 1.0f);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E139C_minigame(object, 0.0f, -670.0f, -380.0f, 670.0f, 250.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    func_800E1468_minigame(object);
    work->unk04 = 0;
    object->func = NULL;
}

s32 func_80106C44_awful_tower(omObjData *player, omObjData *object) {
    A96F0_ObjData *data = object->data;

    GwPlayer[((func_800E1BA8_minigame_ObjData *)player->data)->unk59].gameCoin++;
    HuAudFXPlay(9);
    data->unk54 = 0;
    data->unk78 = 0;
    func_8001C258_main(object->model[0], 4, 4);
    func_8001C258_main(object->model[1], 4, 4);
    return 1;
}

#ifdef NON_MATCHING
void func_80106CDC_awful_tower(omObjData *object) {
    A96F0_ObjData *data;
    s16 i;

    object->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(A96F0_ObjData));
    data = object->data;
    if (D_8010CB98_awful_tower[0] == -1) {
        func_800E1594_minigame(object, 0x210026, 0x41D, 8);
        D_8010CB98_awful_tower[0] = data->unk55;
    } else {
        data->unk55 = func_80014618_main(D_8010CB98_awful_tower[0], 8);
        object->model[0] = D_800CBB60_main[data->unk55].modelId;
        func_8001C2FC_main(object->model[0], 0x70000000, 0x70000000);
    }
    data->unk44 = 0.0f;
    data->unk48 = 40.0f;
    data->unk34 = 50.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 3;
    data->unk7C = 2000;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    data->unk58 = 1.2f;
    data->unk56 = 0;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    data->unk84[8] = (void *)func_80106C44_awful_tower;
    func_800E17F4_minigame(object, 3.0f, 3.0f, 3.0f);
    func_8001C258_main(object->model[0], 4, 4);
    object->func = NULL;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80106CDC_awful_tower);
#endif

void func_80106E84_awful_tower(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    object->model[0] = -1;
    object->trans.x = object->trans.y = object->trans.z = 250.0f;
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E13CC_minigame(object, 50.0f, 100.0f, -50.0f, -50.0f, 50.0f, 50.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    work->unk04 = 0;
    object->func = NULL;
}

s16 func_80106F58_awful_tower(s32 file, u16 *sprite) {
    void *data = DataRead(file);
    s16 anim = func_800329B4_main(data);
    u16 idx;

    HuMemMemoryFreePerm(data);
    *sprite = idx = Hu3DSprModelCreate((void *)-1, 0x6B9, 0);
    D_800CBB60_main[idx].unk_02 = anim;
    return D_800CBB60_main[idx].modelId;
}

void func_80106FDC_awful_tower(omObjData *object) {
    s32 sprFiles[4] = { 0x46000A, 0x46000B, 0x46000C, 0x46000D };
    s16 i;
    s16 j;
    s16 k;

    for (i = 0; i < 4; i++) {
        D_8010D3B8_awful_tower[i] = func_8000B838_main(sprFiles[i]);
        D_8010D3B8_awful_tower[i] = func_8000B838_main(sprFiles[i]);
        D_8010D3D0_awful_tower[i] = espEntry(D_8010D3B8_awful_tower[i], 0, 0);
        espDispOff(D_8010D3D0_awful_tower[i]);
    }
    for (j = 0; j < 3; j++) {
        for (i = 0; i < 4; i++) {
            s32 modelIdx[3] = { 8, 12, 16 };
            s32 animFiles[3] = { 7, 8, 9 };

            object->model[modelIdx[j] + i] =
                func_80106F58_awful_tower(animFiles[j] | 0x460000, &D_8010D348_awful_tower[i][j]);
            func_8001C258_main(object->model[modelIdx[j] + i], 4, 4);
            Hu3DModelCameraSet(object->model[modelIdx[j] + i], D_8010CB60_awful_tower[i]);
            if (j < 2) {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 6.0525f, 6.0525f, 6.0525f);
            } else {
                Hu3DModelScaleSet(object->model[modelIdx[j] + i], 3.02625f, 3.02625f, 3.02625f);
            }
        }
    }
    for (i = 0; i < 5; i++) {
        f32 posX[5] = { 1.0f, -1.0f, 1.0f, -1.0f, 0.25f };
        f32 posY[5] = { 13.5f, 8.5f, 24.0f, 34.0f, 40.5f };
        A96F0_ObjData *data = D_8010D390_awful_tower[i]->data;

        D_8010D390_awful_tower[i]->trans.x = posX[i] * 150.0f;
        D_8010D390_awful_tower[i]->trans.y = posY[i] * 100.0f + 50.0f;
        D_8010D390_awful_tower[i]->trans.z = 0.0f;
        data->unk56 = i;
        func_8001C258_main(D_8010D390_awful_tower[i]->model[0], 4, 0);
    }
    for (i = 0; i < 3; i++) {
        s32 files[3] = { 2, 3, 4 };

        object->model[i] = func_8000B108_main(files[i] | 0x460000, 0x4BD);
    }
    object->model[20] = func_8000B108_main(0x460005, 0x4BD);
    Hu3DModelCameraSet(object->model[20], 0);
    Hu3DModelScaleSet(object->model[20], 0.666666f, 0.666666f, 0.666666f);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            ((D_800EC1C0_minigame_ObjData *)D_8010D360_awful_tower[i][j]->data)->unk04 = i * 3 + j + 1;
            for (k = 0; k < 3; k++) {
                D_8010D360_awful_tower[i][j]->model[k + 1] = Hu3DModelLink(D_8010D3E8_awful_tower->model[j]);
                func_8001C258_main(D_8010D360_awful_tower[i][j]->model[k + 1], 4, 4);
                Hu3DModelScaleSet(D_8010D360_awful_tower[i][j]->model[k + 1], 0.666666f, 0.666666f, 0.666666f);
                Hu3DModelCameraSet(D_8010D360_awful_tower[i][j]->model[k + 1], D_8010CB60_awful_tower[i]);
            }
        }
    }
    object->model[3] = func_8000B108_main(0xA011A, 0x4BD);
    func_8001C814_main(object->model[3], 2, 2);
    Hu3DModelPosSet(object->model[3], 0.0f, 4500.0f, 300.0f);
    Hu3DModelScaleSet(object->model[3], 0.5f, 0.5f, 0.5f);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 3) {
            object->model[i + 4] = func_8000B108_main(i == 3 ? 0x460001 : 0x460000, 0x4B9);
        } else {
            object->model[i + 4] = Hu3DModelLink(object->model[4]);
        }
        Hu3DModelCameraSet(object->model[i + 4], 15);
        func_8001C814_main(object->model[i + 4], 1, 1);
        Hu3DModelPosSet(object->model[i + 4], 0.0f, i * 1120.0 - 9.0, -300.0f);
        Hu3DModelScaleSet(object->model[i + 4], 0.75f, 0.75f, 0.75f);
    }
    object->func = func_80107734_awful_tower;
}

#ifdef NON_MATCHING
void func_80107734_awful_tower(omObjData *object) {
    func_80107858_awful_tower();
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010D3DC_awful_tower == 1) {
            func_8001C258_main(object->model[3], 4, 0);
            Hu3DModelCameraSet(object->model[3], D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
        }
        if (D_8010D3DC_awful_tower != 0 && D_8010D3DC_awful_tower < 46) {
            f32 t = D_8010D3DC_awful_tower / 45.0f;

            Hu3DModelPosSet(object->model[3], 0.0f, (1.0f - t) * (1.0f - t) * 700.0f + 4430.0, 300.0f);
        }
    }
    omPauseChk();
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107734_awful_tower);
#endif

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE40_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE50_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE60_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE70_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE80_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80107858_awful_tower);

void func_80108880_awful_tower(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z) {
    s32 chrDirs[8] = { 2, 3, 7, 4, 5, 6, 8, 9 };
    s32 attr1 = 0x4B9;
    s32 attr2 = 0x49D;
    u16 chr = D_8010D308_awful_tower[group]->chr;
    func_800E1BA8_minigame_ObjData *data;
    s32 i;

    func_800E18D8_minigame();
    func_800E1BA8_minigame(object, model, motion, D_8010D308_awful_tower[group]->player, attr1, attr2);
    Hu3DModelCameraSet(object->model[0], D_8010CB60_awful_tower[group]);
    data = object->data;
    data->unk59 = D_8010D308_awful_tower[group]->player;
    data->unk50 |= 0x400;
    data->unk4C = 1.0f;
    data->unkB4 = 1.0f;
    object->model[6] = func_8000B108_main(5, 0x80D);
    Hu3DModelCameraSet(object->model[6], D_8010CB60_awful_tower[group]);
    Hu3DModelCameraSet(object->model[9], D_8010CB60_awful_tower[group]);
    D_8010D308_awful_tower[group]->unk08 = (rand8() & 1) ? 0x2F : 0x30;
    object->model[10] = func_8000B108_main(func_80017BB8_main(chr, D_8010D308_awful_tower[group]->unk08), attr1 | 4);
    D_8010D308_awful_tower[group]->unk08 |= chrDirs[chr] << 16;
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 19);
    func_800E5A00_minigame(object, 17, func_80017BB8_main(chr, 14), 1, 15);
    func_800E5978_minigame(object, 21, func_80017BB8_main(chr, 31), 0, 0);
    func_800E5978_minigame(object, 30, func_80017BB8_main(chr, 32), 2, 0);
    func_800E5978_minigame(object, 31, func_80017BB8_main(chr, 33), 2, 0);
    func_800E5978_minigame(object, 32, func_80017BB8_main(chr, 34), 0, 0);
    func_800E5A00_minigame(object, 14, func_80017BB8_main(chr, 58), 1, 120);
    object->trans.x = x;
    object->trans.y = y;
    object->trans.z = z;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    for (i = 0; i < 12; i++) {
        func_800E149C_minigame(object, i + 1, 1);
    }
    func_800E149C_minigame(object, 0, 2);
    func_800E149C_minigame(object, group * 3 + 1, 2);
    func_800E149C_minigame(object, group * 3 + 2, 2);
    func_800E149C_minigame(object, group * 3 + 3, 2);
}

void func_80108CCC_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[0]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 0, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108D3C_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[1]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 1, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108DAC_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[2]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 2, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

void func_80108E1C_awful_tower(omObjData *object) {
    s8 chr = D_8010D308_awful_tower[3]->chr;
    s32 motion = D_800A178C_main[chr][1];
    s32 model = D_800A178C_main[chr][0];

    func_80108880_awful_tower(object, model, motion, 3, 0.0f, 0.0f, 0.0f);
    object->func = func_80108E8C_awful_tower;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CEE0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CEF0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF30_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF40_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF48_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF64_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF68_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF74_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF7C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF88_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF8C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF90_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CF94_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CFDC_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108E8C_awful_tower);

void func_8010CB1C_awful_tower(s16 arg0, s16 arg1) {
    HmfModel *hmfModel = &Hu3DData[arg0];

    hmfModel->hmf->unk98->unk08 = (f32)arg1;
}
