#include "common.h"

typedef struct {
    Vec pos;
    f32 unk0C;
    f32 unk10;
    s32 unk14;
    f32 unk18;
    f32 unk1C;
} DorrieDipData;

typedef struct {
    s32 unk00[6];
    f32 unk18[6];
    f32 unk30[6];
} DorrieDipDips;

// One entry per player.
typedef struct {
    f32 posX[5];
    f32 posY[5];
    f32 posZ[5];
    f32 velY[5];
    f32 unk50[5];
    f32 unk64[5];
    f32 unk78[5];
    f32 unk8C[5];
    s32 flags[5];
    s32 playerIdx[5];
} DorrieDipSplashes; // sizeof 0xC8

extern s32 D_8010A1FC_dorrie_dip;

extern omObjData *D_8010A230_dorrie_dip;

extern omObjData *D_8010A234_dorrie_dip;

extern omObjData *D_8010A238_dorrie_dip;

extern omObjData *D_8010A23C_dorrie_dip;

void func_80106BEC_dorrie_dip(void);

void func_801074F8_dorrie_dip(void);

void func_80108174_dorrie_dip(void);

void func_801081D4_dorrie_dip(void);

void func_80108484_dorrie_dip(void);

void func_801086A4_dorrie_dip(void);

void func_8010872C_dorrie_dip(void);

void func_801090F0_dorrie_dip(void);

void func_8010930C_dorrie_dip(void);

void func_80109738_dorrie_dip(void);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801059A0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80105B44_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80105C7C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80105FD0_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010601C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106210_dorrie_dip);

void func_801064FC_dorrie_dip(void) {
    s32 i;
    DorrieDipDips *dips = (DorrieDipDips *)D_8010A230_dorrie_dip->data;

    for (i = 0; i < 6; i++) {
        dips->unk00[i] |= 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106538_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106668_dorrie_dip);

void func_80106BC0_dorrie_dip(void) {
    omAddPrcObj(func_80106BEC_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106BEC_dorrie_dip);

void func_80106D50_dorrie_dip(void) {
    omObjData *obj = D_8010A238_dorrie_dip;
    DorrieDipDips *dips = (DorrieDipDips *)obj->data;

    dips->unk00[0] |= 4;
    func_8001C624_main(obj->model[0], HmfModelData[obj->motion[2]].unk02, 0, 0xA, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106DB8_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80106E14_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107360_dorrie_dip);

void func_801074CC_dorrie_dip(void) {
    omAddPrcObj(func_801074F8_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801074F8_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107690_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801079D4_dorrie_dip);

void func_80107D08_dorrie_dip(void) {
    s32 i;
    DorrieDipSplashes *splashes = (DorrieDipSplashes *)D_8010A23C_dorrie_dip->data;

    for (i = 0; i < 5; i++) {
        splashes->flags[i] |= 2;
        splashes->velY[i] = 0;
        splashes->posY[i] = 1500.0f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107D58_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80107EE0_dorrie_dip);

void func_80108128_dorrie_dip(void) {
    DorrieDipData *data = D_8010A234_dorrie_dip->data;

    data->unk14 |= 1;
    data->unk0C = 0;
}

void func_80108148_dorrie_dip(void) {
    omAddPrcObj(func_80108174_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108174_dorrie_dip);

void func_801081A8_dorrie_dip(void) {
    omAddPrcObj(func_801081D4_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801081D4_dorrie_dip);

void func_80108458_dorrie_dip(void) {
    omAddPrcObj(func_80108484_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A094_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0B4_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0D4_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A0F4_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A114_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A134_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A154_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A174_dorrie_dip);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", D_8010A194_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108484_dorrie_dip);

void func_80108678_dorrie_dip(void) {
    omAddPrcObj(func_801086A4_dorrie_dip, 0x50, 0, 0);
}

void func_801086A4_dorrie_dip(void) {
    while (1) {
        if (D_800D5558_main[D_8010A1FC_dorrie_dip] & A_BUTTON) {
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_80108700_dorrie_dip(void) {
    omAddPrcObj(func_8010872C_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010872C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108800_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010898C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108A74_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108B98_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108C6C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80108EA0_dorrie_dip);

void func_801090C4_dorrie_dip(void) {
    omAddPrcObj(func_801090F0_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801090F0_dorrie_dip);

void func_801092E0_dorrie_dip(void) {
    omAddPrcObj(func_8010930C_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010930C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109520_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_801095FC_dorrie_dip);

void func_801096F0_dorrie_dip(void) {
    omAddPrcObj(func_80109738_dorrie_dip, 0x50, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_8010971C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109738_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109978_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109B28_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109C14_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109E1C_dorrie_dip);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_3E_dorrie_dip/2DC4D0", func_80109F00_dorrie_dip);
