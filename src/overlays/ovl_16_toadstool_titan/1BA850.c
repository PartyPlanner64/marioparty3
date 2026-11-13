#include "common.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

typedef struct ToadstoolTitanPlayer {
    /* 0x00 */ s8 chr;
    /* 0x01 */ s8 playerNo;
    /* 0x02 */ s8 group;
    /* 0x03 */ s8 pad;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0C */ s32 unk_0C;
} ToadstoolTitanPlayer; // sizeof 0x10

extern s16 D_800CDBC8_main;
extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern omObjData *D_800D6A40_main;
extern ToadstoolTitanPlayer D_8010F528_toadstool_titan[4];
extern ToadstoolTitanPlayer *D_8010F568_toadstool_titan[4]; // players indexed by group
extern s32 D_8010F580_toadstool_titan;
extern u8 D_8010F584_toadstool_titan;
extern s16 D_8010F586_toadstool_titan;
extern s8 D_8010F58A_toadstool_titan;
extern s16 D_8010F5BC_toadstool_titan;
extern u8 D_8010F5F4_toadstool_titan;
extern s16 D_8010F5FC_toadstool_titan;
extern s8 D_8010F60E_toadstool_titan;
extern u8 D_8010F614_toadstool_titan[2];
extern u8 D_8010F616_toadstool_titan[4];
extern s32 D_8010F61C_toadstool_titan;
extern u8 D_8010F650_toadstool_titan[9];
extern u8 D_8010F65D_toadstool_titan[4];      // group of each player
extern u8 D_8010F668_toadstool_titan[4];      // start corner of each group
extern u8 D_8010F66C_toadstool_titan;         // number of human players
extern u8 D_8010EDA0_toadstool_titan;         // number of mushrooms created so far
extern s32 D_8010EE38_toadstool_titan;        // set once the camera has been initialized
extern Vec D_8010F5C0_toadstool_titan;        // camera target
extern omObjData *D_8010F5D0_toadstool_titan; // first mushroom object
extern f32 D_8010F600_toadstool_titan;        // music volume
extern f32 D_8010F624_toadstool_titan;        // camera fov
extern Vec D_8010F628_toadstool_titan;        // camera position

void func_801060AC_toadstool_titan(omObjData *object);
void func_8010B510_toadstool_titan(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_801059A0_toadstool_titan);

void func_80105E48_toadstool_titan(void) {
}

void func_80105E50_toadstool_titan(omObjData *object) {
    s32 i;
    s32 j;

    D_8010F5BC_toadstool_titan = 0;
    D_8010F5FC_toadstool_titan = 0;
    D_8010F580_toadstool_titan = 0;
    D_8010F58A_toadstool_titan = 5;
    D_8010F584_toadstool_titan = 0;
    D_8010F586_toadstool_titan = 0;
    D_8010F61C_toadstool_titan = 0;
    D_8010F60E_toadstool_titan = -1;
    D_8010F616_toadstool_titan[0] = D_8010F616_toadstool_titan[1] = D_8010F616_toadstool_titan[2] = D_8010F616_toadstool_titan[3] = 0;
    D_8010F5F4_toadstool_titan = 0;
    D_8010F66C_toadstool_titan = 0;
    D_8010F614_toadstool_titan[0] = D_8010F614_toadstool_titan[1] = 0;
    D_8010F600_toadstool_titan = -1.0f;
    for (i = 0; i < 4; i++) {
        D_8010F568_toadstool_titan[i] = &D_8010F528_toadstool_titan[i];
        bzero(D_8010F568_toadstool_titan[i], sizeof(ToadstoolTitanPlayer));
    }
    for (i = 0; i < 4; i++) {
        // j holds the player's group here; a separate variable changes the register allocation.
        j = D_8010F65D_toadstool_titan[i] = GwPlayer[i].group;
        D_8010F568_toadstool_titan[j]->playerNo = i;
        D_8010F568_toadstool_titan[j]->pad = GwPlayer[i].pad;
        D_8010F568_toadstool_titan[j]->chr = GwPlayer[i].chr;
        D_8010F568_toadstool_titan[j]->group = j;
        D_8010F568_toadstool_titan[j]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
        D_8010F66C_toadstool_titan += (D_8010F568_toadstool_titan[j]->cpuDifficulty == -1) ? 1 : 0;
    }
    for (i = 0; i < 4; i++) {
        D_8010F668_toadstool_titan[i] = rand8() & 3;
        for (j = 0; j < i; j++) {
            if (D_8010F668_toadstool_titan[i] == D_8010F668_toadstool_titan[j]) {
                i--;
                break;
            }
        }
    }
    object->func = func_801060AC_toadstool_titan;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EE80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EECC_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_801060AC_toadstool_titan);

void func_80106984_toadstool_titan(void) {
    UnkAudioObjData *data;

    if (D_800D6A40_main != NULL) {
        data = D_800D6A40_main->data;
        D_8010F600_toadstool_titan = data->unk24 = data->unk2C = func_800037C4_main(D_800CDBC8_main);
    }
}

void func_801069DC_toadstool_titan(omObjData *object) {
    f32 xs[9] = { 0.0f, 110.0f, 250.0f, 250.0f, 110.0f, -110.0f, -250.0f, -250.0f, -110.0f };
    f32 zs[9] = { 0.0f, -230.0f, -110.0f, 110.0f, 240.0f, 240.0f, 110.0f, -110.0f, -230.0f };
    D_800EC1C0_minigame_ObjData *work;

    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[0] = func_8000B108_main(0x370000, 0xBD);
    } else {
        object->model[0] = Hu3DModelLink(D_8010F5D0_toadstool_titan->model[0]);
    }
    omSetTra(object, xs[D_8010EDA0_toadstool_titan] * 1.11, 375.0f, zs[D_8010EDA0_toadstool_titan] * 1.11 + 20.0);
    omSetSca(object, 0.6666667f, 0.6666667f, 0.6666667f);
    if (D_8010EDA0_toadstool_titan == 0) {
        object->model[1] = func_8000B108_main(0x370001, 0xBD);
    } else {
        object->model[1] = Hu3DModelLink(D_8010F5D0_toadstool_titan->model[1]);
    }
    Hu3DModelPosSet(object->model[1], object->trans.x, 0.0f, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 0.6666667f, 0.6666667f, 0.6666667f);
    work = object->data = HuMemAllocTag(0xB4, TAG_OVERLAY);
    memset(work, 0, 0xB4);
    work->unk03 = 1;
    func_800E13CC_minigame(object, 50.0f, 100.0f, -60.0f, -60.0f, 60.0f,
                           (D_8010EDA0_toadstool_titan >= 4 && D_8010EDA0_toadstool_titan < 6) ? 120.0f : 60.0f);
    func_800E1304_minigame(object, 1.0f);
    func_800E1310_minigame(object, 6.0f);
    work->unk04 = D_8010EDA0_toadstool_titan + 1;
    D_8010F650_toadstool_titan[D_8010EDA0_toadstool_titan] = 0;
    D_8010EDA0_toadstool_titan++;
    object->func = NULL;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80106C98_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF68_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF80_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010EF88_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_80107360_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010AD8C_toadstool_titan);

void func_8010B4D4_toadstool_titan(s16 model, s16 time) {
    Hu3DMotionTimeSet(model, time);
}

void func_8010B510_toadstool_titan(omObjData *object) {
    Vec up;

    if (D_8010EE38_toadstool_titan == 0) {
        D_8010EE38_toadstool_titan = 1;
        D_8010F628_toadstool_titan.x = 0.0f;
        D_8010F628_toadstool_titan.y = 868.0f;
        D_8010F628_toadstool_titan.z = 1561.0f;
        D_8010F5C0_toadstool_titan.x = 0.0f;
        D_8010F5C0_toadstool_titan.y = -100.0f;
        D_8010F5C0_toadstool_titan.z = -485.0f;
        D_8010F624_toadstool_titan = 32.5f;
    }
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    D_800CE17C_main[0] = D_8010F628_toadstool_titan.x;
    D_800CE17C_main[1] = D_8010F628_toadstool_titan.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPerspectiveSet(0, D_8010F624_toadstool_titan, 800.0f, 2750.0f);
    Hu3DCameraPosSetV(0, &D_8010F628_toadstool_titan, &D_8010F5C0_toadstool_titan, &up);
    Hu3DCamUpdateMtx(0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B658_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010B99C_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BA80_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BB64_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BC48_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F218_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F238_toadstool_titan);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", D_8010F278_toadstool_titan);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_16_toadstool_titan/1BA850", func_8010BD2C_toadstool_titan);
