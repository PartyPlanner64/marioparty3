#include "common.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/hmfanim.h"
#include "game/hmfspr.h"
#include "game/malloc.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/util.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

// Per-player info, indexed by group through D_8010D308_awful_tower
typedef struct {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 player;
    /* 0x02 */ s8 group;
    /* 0x03 */ u8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk05[7];
} AwfulTowerPlayer; // Size 0xC

extern s32 D_800A178C_main[][6];

extern s16 D_8010CB60_awful_tower[][2];
extern s32 D_8010CB98_awful_tower[];
extern AwfulTowerPlayer D_8010D2D8_awful_tower[4];
extern AwfulTowerPlayer *D_8010D308_awful_tower[4];
extern f32 D_8010D320_awful_tower[4];
extern u8 D_8010D330_awful_tower[4][5];
extern u8 D_8010D3CC_awful_tower[4];
extern s16 D_8010D3D8_awful_tower;
extern u32 D_8010D3DC_awful_tower;
extern s16 D_8010D3E4_awful_tower;
extern s8 D_8010D3FC_awful_tower;
extern s8 D_8010D3FD_awful_tower;
extern s8 D_8010D3FE_awful_tower;

void func_801061FC_awful_tower(omObjData *object);
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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD2C_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD34_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CD54_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_801061FC_awful_tower);

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

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDC0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDD0_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDDC_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDE8_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CDFC_awful_tower);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", D_8010CE10_awful_tower);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80106FDC_awful_tower);

#ifdef NON_MATCHING
void func_80107734_awful_tower(omObjData *object) {
    func_80107858_awful_tower();
    if (D_8010D3E4_awful_tower == 3) {
        if (D_8010D3DC_awful_tower == 1) {
            func_8001C258_main(object->model[3], 4, 0);
            Hu3DModelCameraSet(object->model[3], D_8010CB60_awful_tower[D_8010D3FC_awful_tower][1]);
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_25_awful_tower/21E010", func_80108880_awful_tower);

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
