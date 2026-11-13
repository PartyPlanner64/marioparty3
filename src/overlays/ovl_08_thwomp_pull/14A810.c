#include "common.h"
#include "overlays/minigame.h"

typedef struct ThwompPullPlayer {
    /* 0x00 */ s8 playerNo;
    /* 0x01 */ s8 group;
    /* 0x02 */ s8 pad;
    /* 0x03 */ s8 chr;
    /* 0x04 */ s8 cpuDifficulty; // -1 for human players
    /* 0x05 */ char unk_05[0xB];
} ThwompPullPlayer; // sizeof 0x10

extern D_80111B50_vine_with_me_Struct D_8010ED60_thwomp_pull;
extern ThwompPullPlayer D_8010F4B8_thwomp_pull[4];
extern ThwompPullPlayer *D_8010F4F8_thwomp_pull[4]; // players indexed by group
extern f32 D_8010F520_thwomp_pull[4];
extern omObjData *D_8010F52C_thwomp_pull;
extern s16 D_8010F530_thwomp_pull;
extern s32 D_8010F53C_thwomp_pull;
extern s16 D_8010F550_thwomp_pull[10]; // sprite data ids
extern u8 D_8010F564_thwomp_pull[2];
extern s8 D_8010F566_thwomp_pull;
extern omObjData *D_8010F568_thwomp_pull[2];
extern s16 D_8010F570_thwomp_pull;
extern f32 D_8010F588_thwomp_pull;
extern u16 D_8010F590_thwomp_pull[10]; // sprite ids
extern s32 D_8010F5A4_thwomp_pull;
extern u8 D_8010F5A8_thwomp_pull;
extern u8 D_8010F5B4_thwomp_pull[4]; // group of each player

const s16 D_8010EFD0_thwomp_pull[] = {
    0x8260, 0x8261, 0x8262, 0x8263, 0x8264, 0x8265, 0x8266, 0x8267, 0x8268, 0x8269, 0x826A, 0x826B, 0x826C, 0x826D,
    0x826E, 0x826F, 0x8270, 0x8271, 0x8272, 0x8273, 0x8274, 0x8275, 0x8276, 0x8277, 0x8278, 0x8279, 0x0000, 0x0000
};

void func_80105D3C_thwomp_pull(omObjData *object);
void func_80106D5C_thwomp_pull(omObjData *object);
void func_8010974C_thwomp_pull(omObjData *object);
void func_80109780_thwomp_pull(omObjData *object);

void func_80105F14_thwomp_pull(omObjData *object);
void func_80106E78_thwomp_pull(omObjData *object);
void func_801089B4_thwomp_pull(Gfx **gfxPos, s32 arg1, s32 arg2);

void func_801059A0_thwomp_pull(void) {
    omObjData *object;

    func_800142A0_main(0x20);
    omInitObjMan(50, 0);
    func_8004A208_main();
    D_800CD280_main = 1;
    func_8000B5F0_main(2);
    func_8000B710_main(2);
    ScissorSet(0, 0.0f, 0.0f, 140.0f, 240.0f);
    ScissorSet(1, 180.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 320.0f, 480.0f, 511.0f);
    ViewportSet(1, 640.0f, 480.0f, 511.0f, 960.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 65.0f, 500.0f, 3000.0f);
    Hu3DCameraPerspectiveSet(1, 65.0f, 500.0f, 3000.0f);
    Hu3DFogSet(950, 1000, 0xFF, 0xFF, 0xFF);
    Hu3DBGColorSet(0xFF, 0xFF, 0xFF);
    Hu3DGLightMaxSet(2);
    Hu3DGLightDirSet(0, 0.0f, 0.0f, 90.0f);
    Hu3DGLightColorSet(0, 0x90, 0x90, 0x90);
    Hu3DGLightDirSet(1, -39.0f, 45.0f, 104.0f);
    Hu3DGLightColorSet(1, 0xFF, 0xFF, 0xFF);
    CenterM[0].x = 0.0f;
    CenterM[0].y = 115.0f;
    CenterM[0].z = -500.0f;
    CRotM[0].x = -16.0f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[0] = 1260.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 115.0f;
    CenterM[1].z = -500.0f;
    CRotM[1].x = -16.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    CZoomM[1] = 1260.0f;
    omAddObj(0, 0, 0, -1, func_80105D3C_thwomp_pull);
    D_8010F52C_thwomp_pull = omAddObj(8, 1, 1, -1, func_80106D5C_thwomp_pull);
    omSetStatBit(D_8010F52C_thwomp_pull, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    D_8010F568_thwomp_pull[0] = omAddObj(3, 52, 21, -1, func_8010974C_thwomp_pull);
    D_8010F568_thwomp_pull[1] = omAddObj(3, 52, 21, -1, func_80109780_thwomp_pull);
    object = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    object->work[0] = 2;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    func_80045010_main(D_8010EFD0_thwomp_pull, 1);
    WipeCreateIn(0xFF, 16);
    D_8010ED60_thwomp_pull.unk01 = 2;
    D_8010ED60_thwomp_pull.unk1C = -1;
    D_8010ED60_thwomp_pull.unk1C = 75;
    D_8010ED60_thwomp_pull.unk1E = 1800;
    D_8010ED60_thwomp_pull.unk03 = 2;
    D_8010ED60_thwomp_pull.unk02 = 1;
    D_8010ED60_thwomp_pull.unk22 = 45;
    D_8010ED60_thwomp_pull.unk24 = 165;
    D_8010ED60_thwomp_pull.unk04 = 0;
    D_8010ED60_thwomp_pull.unk05 = 0;
    D_8010ED60_thwomp_pull.unk20 = -1;
    func_800E5EA0_minigame(&D_8010ED60_thwomp_pull);
}

void func_80105D3C_thwomp_pull(omObjData *object) {
    s32 group;
    s32 i;

    D_8010F570_thwomp_pull = 0;
    D_8010F530_thwomp_pull = 0;
    D_8010F5A4_thwomp_pull = 0;
    D_8010F53C_thwomp_pull = 0;
    D_8010F566_thwomp_pull = 5;
    D_8010F5A8_thwomp_pull = 0;
    D_8010F520_thwomp_pull[0] = D_8010F520_thwomp_pull[1] = D_8010F520_thwomp_pull[2] = D_8010F520_thwomp_pull[3] = 0.0f;
    D_8010F588_thwomp_pull = 0.0f;
    D_8010F564_thwomp_pull[0] = D_8010F564_thwomp_pull[1] = 0;
    for (i = 0; i < 4; i++) {
        D_8010F4F8_thwomp_pull[i] = &D_8010F4B8_thwomp_pull[i];
        bzero(D_8010F4F8_thwomp_pull[i], sizeof(ThwompPullPlayer));
    }
    for (i = 0; i < 4; i++) {
        group = GwPlayer[i].group;
        group = (group == 3) ? 1 : (group == 1) ? 3
                                                : group;
        D_8010F5B4_thwomp_pull[i] = group;
        D_8010F4F8_thwomp_pull[group]->playerNo = i;
        D_8010F4F8_thwomp_pull[group]->pad = GwPlayer[i].pad;
        D_8010F4F8_thwomp_pull[group]->chr = GwPlayer[i].chr;
        D_8010F4F8_thwomp_pull[group]->group = group;
        D_8010F4F8_thwomp_pull[group]->cpuDifficulty = (GwPlayer[i].stat & 1) ? GwPlayer[i].cpu_difficulty : -1;
    }
    Hu3DHookFuncCreate(0, func_801089B4_thwomp_pull, 2);
    object->func = func_80105F14_thwomp_pull;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F008_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F018_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F028_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80105F14_thwomp_pull);

void func_80106D5C_thwomp_pull(omObjData *object) {
    s32 spriteFiles[10] = { 0x29001F, 0x290020, 0x210008, 0x210009, 0x21000A, 0x21000B, 0x21000C, 0x21000D, 0x21000E, 0x21000F };
    s16 i;

    for (i = 0; i < 10; i++) {
        D_8010F590_thwomp_pull[i] = espEntry(D_8010F550_thwomp_pull[i] = func_8000B838_main(spriteFiles[i]), 0, 0);
        espDispOff(D_8010F590_thwomp_pull[i]);
    }
    object->func = func_80106E78_thwomp_pull;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80106E78_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80107FF4_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801089B4_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_8010974C_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_80109780_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F140_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F150_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F170_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F190_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1B0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F1F0_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_801097AC_thwomp_pull);

void func_8010AF18_thwomp_pull(s16 arg0, s16 arg1) {
    HmfModel *model = &Hu3DData[arg0];
    f32 value = arg1;

    Hu3DMotionTimeSet(arg0, value);
    model->hmf->unk98->unk08 = value;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F238_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F244_thwomp_pull);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", func_8010AF88_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F280_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2A0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2C0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2D8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F2F0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F308_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F320_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F338_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F350_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F358_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F360_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F368_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F370_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F378_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F380_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F388_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F390_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F398_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3A8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3B8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3C8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3D8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3E8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F0_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F3F8_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F400_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F408_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F410_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F418_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F420_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F428_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F430_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F438_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F440_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F448_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F450_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F458_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F460_thwomp_pull);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_08_thwomp_pull/14A810", D_8010F468_thwomp_pull);
