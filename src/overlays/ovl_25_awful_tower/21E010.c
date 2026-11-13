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
extern Gfx *gMainGfxPos;
extern omObjData *D_800EBE70_minigame[];

extern s32 D_8010CB60_awful_tower[];
extern D_80111B50_vine_with_me_Struct D_8010CB70_awful_tower;
extern s32 D_8010CB98_awful_tower[];
extern Gfx D_8010CBA0_awful_tower[];
extern const s16 D_8010CCE0_awful_tower[];
extern s16 D_8010D2CC_awful_tower[4];
extern AwfulTowerPlayer D_8010D2D8_awful_tower[4];
extern AwfulTowerPlayer *D_8010D308_awful_tower[4];
extern f32 D_8010D320_awful_tower[4];
extern omObjData *D_8010D344_awful_tower;
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

void func_80106028_awful_tower(omObjData *object);
void func_801061FC_awful_tower(omObjData *object);
void func_80106A9C_awful_tower(omObjData *object);
void func_80106CDC_awful_tower(omObjData *object);
void func_80106E84_awful_tower(omObjData *object);
void func_80106FDC_awful_tower(omObjData *object);
void func_80107734_awful_tower(omObjData *object);
void func_80107858_awful_tower(void);
void func_80108880_awful_tower(omObjData *object, s32 model, s32 motion, u16 group, f32 x, f32 y, f32 z);
void func_80108CCC_awful_tower(omObjData *object);
void func_80108D3C_awful_tower(omObjData *object);
void func_80108DAC_awful_tower(omObjData *object);
void func_80108E1C_awful_tower(omObjData *object);
void func_80108E8C_awful_tower(omObjData *object);

void func_801059A0_awful_tower(void) {
    omObjData *object;
    s32 i;
    s32 j;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(0x20);
    omInitObjMan(100, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(4);
    func_8000B710_main(4);
    for (i = 0; i < 4; i++) {
        s32 lefts[4] = { 0, 93, 161, 229 };
        s32 rights[4] = { 92, 160, 228, 320 };

        ScissorSet(i, lefts[i], 0.0f, rights[i], 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, i * 272 + 236, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 7.152669f, 8000.0f, 16000.0f);
        CenterM[i].x = 0.0f;
        CenterM[i].y = 650.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CZoomM[i] = 12000.0f;
    }
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 80.0f, 130.0f);
    Hu3DGLightColorSet(0, 0x80, 0x80, 0x90);
    Hu3DGLightDirSet(1, 20.0f, 80.0f, 110.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xF0);
    omAddObj(0, 0, 0, -1, func_80106028_awful_tower);
    D_8010D3E8_awful_tower = omAddObj(4, 21, 21, -1, func_80106FDC_awful_tower);
    omSetStatBit(D_8010D3E8_awful_tower, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010D344_awful_tower = omAddObj(2, 21, 21, -1, func_80106A9C_awful_tower);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_800EC1C0_minigame[D_800EBE28_minigame++] = D_8010D360_awful_tower[i][j] = omAddObj(2, 4, 4, -1, func_80106E84_awful_tower);
        }
    }
    for (i = 0; i < 5; i++) {
        D_800EBE70_minigame[D_800EC1B8_minigame++] = D_8010D390_awful_tower[i] = omAddObj(2, 4, 2, -1, func_80106CDC_awful_tower);
    }
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[0] = omAddObj(3, 12, 60, -1, func_80108CCC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[1] = omAddObj(3, 12, 60, -1, func_80108D3C_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[2] = omAddObj(3, 12, 60, -1, func_80108DAC_awful_tower);
    D_800EC598_minigame[D_800EC280_minigame++] = D_8010D3A8_awful_tower[3] = omAddObj(3, 12, 60, -1, func_80108E1C_awful_tower);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 4;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    WipeCreateIn(0xFF, 30);
    func_80045010_main(D_8010CCE0_awful_tower, 1);
    D_8010CB70_awful_tower.unk01 = 0;
    D_8010CB70_awful_tower.unk1C = 60;
    D_8010CB70_awful_tower.unk1E = 1800;
    D_8010CB70_awful_tower.unk03 = 2;
    D_8010CB70_awful_tower.unk02 = 1;
    D_8010CB70_awful_tower.unk22 = 75;
    D_8010CB70_awful_tower.unk24 = 165;
    D_8010CB70_awful_tower.unk04 = 0;
    D_8010CB70_awful_tower.unk05 = 0;
    D_8010CB70_awful_tower.unk20 = -1;
    func_800E5EA0_minigame(&D_8010CB70_awful_tower);
    for (i = 0; i < 4; i++) {
        D_8010D2CC_awful_tower[i] = func_8000D658_main(0x6A9, 4);
    }
}

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

void func_80107734_awful_tower(omObjData *object) {
    func_80107858_awful_tower();
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010D3DC_awful_tower == 1) {
            func_8001C258_main(object->model[3], 4, 0);
            Hu3DModelCameraSet(object->model[3], D_8010CB60_awful_tower[D_8010D3FC_awful_tower]);
        }
        if (D_8010D3DC_awful_tower != 0 && D_8010D3DC_awful_tower < 46) {
            f32 t = D_8010D3DC_awful_tower / 45.0f;

            t = (1.0f - t) * (1.0f - t);
            Hu3DModelPosSet(object->model[3], 0.0f, t * 700.0f + 4430.0, 300.0f);
        }
    }
    omPauseChk();
}

void func_80107858_awful_tower(void) {
    s32 groups[4] = { 3, 2, 1, 0 };
    s32 lefts[4] = { 0, 93, 161, 229 };
    s32 rights[4] = { 92, 160, 228, 320 };
    s32 texLefts[4] = { 0, 25, 25, 25 };
    s32 zoomLefts[4] = { 0, 0, 0, 0 };
    s32 zoomRights[4] = { 320, 320, 320, 320 };
    s32 zoomTexLefts[4] = { 0, 0, 0, 0 };
    u8 order[4] = { 0, 1, 2, 3 };
    s32 curLefts[4] = { 0, 93, 161, 229 };
    s32 curRights[4] = { 92, 160, 228, 320 };
    HuSprite *sprite;
    HuSprite_Unk84_Unk00_Struct *frame;
    f32 t = 0.0f;
    f32 a;
    f32 b;
    f32 scale;
    s32 left;
    s32 right;
    s32 y;
    s32 yEnd;
    s32 offset;
    s32 xl;
    s32 xh;
    s32 yl;
    s32 yh;
    s32 s;
    s32 dsdx;
    s16 player;
    s16 i;
    s16 j;
    s16 k;

    if (D_8010D3FC_awful_tower < 4) {
        for (i = 0, k = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower == i) {
                if (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower < 30) {
                    t = 1.0f - D_8010D3DC_awful_tower / 29.0f;
                    t = ((1.0f - t) + 1.0f - t * t * t) * 0.5;
                } else if (D_8010D3E4_awful_tower == 7 ||
                           (D_8010D3E4_awful_tower == 4 && D_8010D3DC_awful_tower >= 30)) {
                    t = 1.0f;
                }
            } else {
                order[k++] = i;
            }
        }
        order[k] = D_8010D3FC_awful_tower;
    }
    if (t > 0.0f) {
        a = 1.0f - t;
        b = 1.0f - a;
        scale = ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) / (a * 67.0f + b * 113.0f);
        left = curLefts[D_8010D3FC_awful_tower] =
            lefts[D_8010D3FC_awful_tower] * a + zoomLefts[D_8010D3FC_awful_tower] * b;
        right = curRights[D_8010D3FC_awful_tower] =
            rights[D_8010D3FC_awful_tower] * a + zoomRights[D_8010D3FC_awful_tower] * b;
        ScissorSet(D_8010D3FC_awful_tower, left, 0.0f, right, 240.0f);
        ViewportSet(D_8010D3FC_awful_tower, scale * 320.0f * 2.0f, scale * 240.0f * 2.0f, 511.0f,
                    ((D_8010D3FC_awful_tower * 68 + 59) * a + b * 160.0f) * 4.0f, 480.0f, 511.0f);
        CenterM[D_8010D3FC_awful_tower].y = a * D_8010D320_awful_tower[D_8010D3FC_awful_tower] + b * 4605.0f;
        for (i = 0; i < 4; i++) {
            if (D_8010D3FC_awful_tower != i) {
                if (i < D_8010D3FC_awful_tower) {
                    curLefts[i] = MIN(left, curLefts[i]);
                    curRights[i] = MIN(left, curRights[i]);
                } else {
                    curLefts[i] = MAX(right, curLefts[i]);
                    curRights[i] = MAX(right, curRights[i]);
                }
            }
        }
    }
    gSPDisplayList(gMainGfxPos++, D_8010CBA0_awful_tower);
    gDPSetTextureLUT(gMainGfxPos++, G_TT_RGBA16);
    for (i = 3; i >= 0; i--) {
        sprite = HuSprGet(D_800CD1DC_main[D_8010D3D0_awful_tower[groups[i]]].unk04, 0);
        frame = &sprite->unk_84->unk00[sprite->unk_90];
        for (j = 0; j < 9; j++) {
            y = j * 16;
            yEnd = (y + 17 > 130) ? 130 : y + 17;
            if (i != 0) {
                gDPLoadTextureTile(gMainGfxPos++, (u8 *)frame->unk00 + y * 114, G_IM_FMT_CI, G_IM_SIZ_8b, 114, 0, 0, 0,
                                   114, yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                   G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal256(gMainGfxPos++, sprite->unk_84->unk0C);
            } else {
                gDPLoadTextureTile_4b(gMainGfxPos++, (u8 *)frame->unk00 + y * 57, G_IM_FMT_CI, 114, 0, 0, 0, 114,
                                      yEnd - y, 0, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP,
                                      G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
                gDPLoadTLUT_pal16(gMainGfxPos++, 0, sprite->unk_84->unk0C);
            }
            for (k = 0; k < 4; k++) {
                player = order[k];
                if (t > 0.0f) {
                    if (curLefts[player] == curRights[player]) {
                        continue;
                    }
                    gDPSetScissor(gMainGfxPos++, G_SC_NON_INTERLACE, curLefts[player], 0,
                                  curRights[player] - ((player == D_8010D3FC_awful_tower) ? 1 : 0), 240);
                }
                if (player == D_8010D3FC_awful_tower) {
                    a = 1.0f - t;
                    b = 1.0f - a;
                } else {
                    a = 1.0f;
                    b = 0.0f;
                }
                offset = (D_8010D320_awful_tower[player] - 650.0f) / 3850.0 * -284.0 + 284.0;
                xl = (lefts[player] * a + zoomLefts[player] * b) * 4.0f;
                xh = (rights[player] * a + zoomRights[player] * b) * 4.0f;
                yl = ((y + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0;
                yh = ((yEnd + 2 + i * 131 - offset - 120) * (a + b * 2.83185840707964598) + 120.0) * 4.0 - 1.0;
                if ((xl > 1280) | (xh < 0)) {
                    continue;
                }
                if ((yl > 960) | (yh < 0)) {
                    continue;
                }
                s = (texLefts[player] * a + zoomTexLefts[player] * b) * 32.0;
                dsdx = (a * 67.0f + b * 113.0f) / ((a * 160.0f + b * 320.0f) - (a * 93.0f + b * 0.0f)) * 1024.0;
                gSPScisTextureRectangle(gMainGfxPos++, xl, yl, xh, yh, G_TX_RENDERTILE, s, 0, dsdx, dsdx);
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ScissorSet(i, curLefts[i], 0.0f, curRights[i], 240.0f);
    }
}

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
