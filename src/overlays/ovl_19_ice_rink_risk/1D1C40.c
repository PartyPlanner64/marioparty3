#include "common.h"
#include "overlays/minigame.h"

typedef struct {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ char unk05[0x0F];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ char unk18[0x1C];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ char unk44[0x04];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[0x07];
    /* 0x53 */ s8 unk53;
    /* 0x54 */ char unk54[0x60];
} IceRinkRiskWork; // Size 0xB4

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_801059A0_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80105E34_ice_rink_risk);

extern s32 D_801085EC_ice_rink_risk[];
extern s32 D_801085F8_ice_rink_risk;

void func_80105E60_ice_rink_risk(void) {
    D_801085EC_ice_rink_risk[D_801085F8_ice_rink_risk] = 1;
    D_801085F8_ice_rink_risk++;
    HuAudFXPlay(0x3D3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80105EA4_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80105FAC_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106198_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106554_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106710_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106A60_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106C54_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106E20_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80106FC0_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107590_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107604_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107678_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_801076EC_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107760_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_8010796C_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107CB4_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107D14_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107DEC_ice_rink_risk);

f32 func_80107F24_ice_rink_risk(omObjData *arg0, s32 arg1, Vec *arg2) {
    IceRinkRiskWork *work = arg0->data;
    f32 temp_f0;

    work->unk53 = 0;
    temp_f0 = ((IceRinkRiskWork *)D_800EC1C0_minigame[0]->data)->unk14;
    arg2->x = 0.0f;
    arg2->y = 1.0f;
    arg2->z = 0.0f;
    return temp_f0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80107F58_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80108134_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_8010826C_ice_rink_risk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_19_ice_rink_risk/1D1C40", func_80108384_ice_rink_risk);
