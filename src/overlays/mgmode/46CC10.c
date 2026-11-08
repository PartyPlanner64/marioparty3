#include "common.h"
#include "overlays/mgmode.h"

extern u8 D_80118EB1_mgmode;
extern u8 D_80118EB2_mgmode;
extern s16 D_80118EB4_mgmode;
extern s16 D_8011B950_mgmode;
extern s16 D_8011B95A_mgmode;
extern s16 D_8011B884_mgmode;
extern Gfx D_80119290_mgmode[];
extern s16 D_8011B3E4_mgmode;
extern MgmodeEsprite *D_8011B3EC_mgmode;
extern s16 D_8011B8B2_mgmode;
extern u16 *D_8011B3E0_mgmode;
extern s8 D_8011B3E6_mgmode[];
extern s32 D_80119190_mgmode[];
extern s32 D_801191E4_mgmode[];
extern char D_8011A430_mgmode[];
extern char D_8011A708_mgmode[];
extern s16 D_8011B6A0_mgmode;
extern s16 D_8011B928_mgmode[];
extern s16 D_8011B940_mgmode[];
extern s16 D_8011B6A8_mgmode;
extern u8 D_800D20B0_main;
extern MgmodeSpaceCoord D_80119158_mgmode[];
extern Vec D_8011AA80_mgmode[][25];
extern s16 D_8011B8B6_mgmode[];
extern s16 D_8011B8C4_mgmode;

void func_8010BD98_mgmode(omObjData *arg0);
void func_80108DDC_mgmode(s16 arg0);
void func_801168E0_mgmode(MgmodeEsprite *arg0);
void func_80116968_mgmode(MgmodeEsprite *arg0, s16 index, s16 arg2, s16 arg3);
void func_801169A0_mgmode(MgmodeEsprite *arg0, s16 index);
void func_801169C8_mgmode(MgmodeEsprite *arg0, s16 index);
void func_80116D4C_mgmode(void);
void func_80118CD8_mgmode(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801059A0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A400_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A404_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A40C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010606C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107298_mgmode);

void func_80107610_mgmode(void) {
    s32 angle = 0;

    Hu3DModelScaleSet(D_8011B8B2_mgmode, 0.5f, 0.5f, 0.5f);
    while (TRUE) {
        HuPrcVSleep();
        HmfModelData[D_8011B8B2_mgmode].pos.y = sindf(angle) * 20.0f;
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A430_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A434_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A43C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A444_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A44C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A454_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A45C_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A464_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A46C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801076B0_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A484_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A490_mgmode);

INCLUDE_RODATA("asm/nonmatchings/overlays/mgmode/46CC10", D_8011A49C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80107D0C_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108824_mgmode);

void func_80108C88_mgmode(void) {
    HuWinDispOn(D_8011B6A0_mgmode);
    func_80108DDC_mgmode(D_800D20B0_main);
    func_8011822C_mgmode(D_80119158_mgmode);
    func_801181F4_mgmode(0);
    func_801182B4_mgmode(1);
    HuWinMesSet(D_8011B6A8_mgmode, 0x5702, -1, -1);
    HuWinExAnimIn(D_8011B6A8_mgmode);
}

void func_80108CF4_mgmode(s16 arg0) {
    s32 mesOffset;

    mesOffset = (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] != 0) ? 7 : 0;
    if (D_8011B928_mgmode[D_801191E4_mgmode[arg0]] == D_8011B940_mgmode[D_801191E4_mgmode[arg0]]) {
        mesOffset = 14;
    }
    sprintf(D_8011A708_mgmode, D_8011A430_mgmode, D_8011B928_mgmode[D_801191E4_mgmode[arg0]]);
    HuWinInsertMesSet(D_8011B6A0_mgmode, (u32)D_8011A708_mgmode, 0);
    HuWinMesSet(D_8011B6A0_mgmode, D_80119190_mgmode[mesOffset + arg0], -1, -1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80108DDC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_801090C4_mgmode);

void func_80109C10_mgmode(s16 arg0, s16 arg1) {
    s16 model;
    f32 x;
    f32 z;
    f32 dist;

    if (arg0 == 6 && arg1 == 0) {
        model = D_8011B8C4_mgmode;
    } else {
        model = D_8011B8B6_mgmode[arg0];
    }
    func_8001C258_main(model, 4, 0);
    Hu3DModelRotSet(model, 15.0f, CRot.y, 0.0f);
    x = sindf(CRot.y) * cosdf(CRot.x);
    z = cosdf(CRot.y) * cosdf(CRot.x);
    dist = HuSqrtf(x * x + z * z);
    x = x / dist * 20.0f;
    z = z / dist * 20.0f;
    Hu3DModelPosSet(model, x + D_8011AA80_mgmode[arg0][arg1].x, D_8011AA80_mgmode[arg0][arg1].y - 3.0f,
                    z + D_8011AA80_mgmode[arg0][arg1].z);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_80109DBC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A148_mgmode);

void func_8010A5F0_mgmode(void) {
    func_801168E0_mgmode(D_8011B3EC_mgmode);
    HuWinExAnimOut(D_8011B3E4_mgmode, 0);
    HuWinKill(D_8011B3E4_mgmode);
}

void func_8010A62C_mgmode(s32 arg0, s32 arg1) {
    s16 i;

    for (i = 0; i < 4; i++) {
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i], arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        func_80116968_mgmode(D_8011B3EC_mgmode, D_8011B3E6_mgmode[i] + 10, arg0 + D_8011B3E0_mgmode[i] - 0x54,
                             arg1 + 0x1E);
        func_80116968_mgmode(D_8011B3EC_mgmode, i + 4, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1);
        if (GwPlayer[D_8011B3E6_mgmode[i]].stat & 1) {
            func_801169A0_mgmode(D_8011B3EC_mgmode, i + 14);
            func_80116968_mgmode(D_8011B3EC_mgmode, i + 14, arg0 + D_8011B3E0_mgmode[i] - 0x54, arg1 + 0xE);
        } else {
            func_801169C8_mgmode(D_8011B3EC_mgmode, i + 14);
        }
    }
}

void func_8010A824_mgmode(s32 arg0, s32 arg1) {
    s32 offset = 0x54;

    func_80116968_mgmode(D_8011B3EC_mgmode, 18, D_8011B3E0_mgmode[4] + (arg0 - offset), arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 8, D_8011B3E0_mgmode[0] + arg0 - 0x70, arg1);
    func_80116968_mgmode(D_8011B3EC_mgmode, 9, D_8011B3E0_mgmode[3] + arg0 - 0x38, arg1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010A8E4_mgmode);

void func_8010AF78_mgmode(Gfx **arg0, s32 arg1, s32 arg2) {
    if (D_8011B884_mgmode != 0) {
        gDPSetDepthImage((*arg0)++, 0x3D0800);
        gDPSetColorImage((*arg0)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 320, 0x3D0800);
        gSPDisplayList((*arg0)++, D_80119290_mgmode);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010AFEC_mgmode);

INCLUDE_ASM("asm/nonmatchings/overlays/mgmode/46CC10", func_8010B574_mgmode);

void func_8010BD28_mgmode(omObjData *arg0) {
    if ((D_80118EB1_mgmode != 0) || (D_800D530C_main != 0)) {
        if ((D_80118EB4_mgmode & 0x80) == 0) {
            WipeCreateOut(0xB, 8);
            HuAudSeqFadeOut(0x3C);
        }
        arg0->func = func_8010BD98_mgmode;
    }
}

void func_8010BD98_mgmode(omObjData *arg0) {
    if (WipeStatGet() != 0) {
        return;
    }
    HuWinAllKill();
    if (D_80118EB2_mgmode != 0) {
        func_80118CD8_mgmode();
    }
    func_80116D4C_mgmode();
    D_80118EB4_mgmode &= 0xF;
    _ClearFlag(0x1C);
    if (D_80118EB4_mgmode == 0) {
        omOvlReturnEx(1);
    } else if (D_80118EB4_mgmode == 2) {
        if (D_8011B95A_mgmode == 0x68) {
            _SetFlag(0x1C);
        }
        if (D_8011B95A_mgmode == 0x70) {
            _SetFlag(0x1C);
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
        } else {
            omOvlCallEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x84);
        }
    } else {
        omOvlGotoEx(D_8011B95A_mgmode, D_8011B950_mgmode, 0x82);
    }
}
