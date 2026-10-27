#include "common.h"

typedef struct {
    /* 0x00 */ omObjData *unk00;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ Vec unk44;
    /* 0x50 */ Vec unk50;
    /* 0x5C */ Vec unk5C;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ Vec unk78;
} CoconutConkData; // sizeof 0x84

extern char *D_8010AF98_coconut_conk[];
extern u8 D_800D6A90_main;
extern char D_8010B0D0_coconut_conk[];
extern char D_8010B0E4_coconut_conk[];
extern HuSprite_Unk84_Struct *D_8010B1C4_coconut_conk;
extern u8 D_8010B1C8_coconut_conk;
extern void *D_8010B1D0_coconut_conk[3];
extern s16 D_8010B1DC_coconut_conk;
extern u16 D_8010B1E2_coconut_conk[2];
extern CoconutConkData D_8010B1F0_coconut_conk[50];
extern omObjData *D_8010B274_coconut_conk;
extern s16 D_8010B2B4_coconut_conk;
extern u16 D_8010B2B6_coconut_conk;
extern f32 D_8010B2B8_coconut_conk;
extern f32 D_8010B2BC_coconut_conk;
extern omObjData *D_8010B37C_coconut_conk;
extern s16 D_8010B3BC_coconut_conk;
extern u16 D_8010B3BE_coconut_conk;
extern f32 D_8010B3C0_coconut_conk;
extern f32 D_8010B3C4_coconut_conk;
extern omObjData *D_8010B400_coconut_conk;
extern omObjData *D_8010B484_coconut_conk;
extern f32 D_8010B418_coconut_conk;
extern f32 D_8010B4A0_coconut_conk;
extern f32 D_8010B4A4_coconut_conk;
extern CoconutConkData D_8010B508_coconut_conk[6];
extern CoconutConkData D_8010B820_coconut_conk[9];
extern CoconutConkData D_8010BCC4_coconut_conk;

void func_80105C60_coconut_conk(omObjData *);
void func_80105D98_coconut_conk(Gfx **, s32, s32);
void func_801060C0_coconut_conk(omObjData *);
void func_801060C8_coconut_conk(omObjData *);
void func_801062D4_coconut_conk(omObjData *);
void func_801061F4_coconut_conk(omObjData *);
void func_80106394_coconut_conk(omObjData *);
void func_80106468_coconut_conk(omObjData *);
void func_8010659C_coconut_conk(omObjData *);
void func_801067E0_coconut_conk(omObjData *);
void func_801069BC_coconut_conk(void);
void func_80106D5C_coconut_conk(omObjData *);
void func_80106F18_coconut_conk(void);
void func_801090C4_coconut_conk(void);
void func_8010A55C_coconut_conk(omObjData *);
void func_8010AE04_coconut_conk(void);
void func_800335BC_main(char *name, u16 *result);
void func_8000BC48_main(u16, u16);
void func_8001E888_main(s16 model, f32 x, f32 y, u16 arg3, u16 arg4, char *name, s32 arg6);

void func_801059A0_coconut_conk(void) {
    func_8010AE04_coconut_conk();
}

f32 func_801059BC_coconut_conk(f32 arg0, f32 arg1) {
    f32 angle = arg0 + arg1;

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    return angle;
}

void func_80105A3C_coconut_conk(void) {
    CoconutConkData *data;
    u32 i;

    for (i = 0, data = D_8010B1F0_coconut_conk; i < 50; i++, data++) {
        data->unk00 = NULL;
        data->unk04 = 0;
        data->unk06 = 0;
        data->unk08 = 0;
        data->unk0A = 0;
        data->unk0C = 0;
        data->unk0E = 0;
        data->unk10 = 0;
        data->unk12 = 0;
        data->unk14 = 0;
        data->unk16 = 0;
        data->unk18 = 0.0f;
        data->unk1C = 0.0f;
        data->unk20 = 0.0f;
        data->unk24 = 0.0f;
        data->unk28 = 0.0f;
        data->unk2C = 0.0f;
        data->unk30 = 0.0f;
        data->unk34 = 0.0f;
        data->unk38 = 0.0f;
        data->unk3C = 0.0f;
        data->unk40 = -1;
        data->unk42 = -1;
        data->unk44.x = data->unk44.y = data->unk44.z = 0.0f;
        data->unk50.x = data->unk50.y = data->unk50.z = 0.0f;
        data->unk5C.x = data->unk5C.y = data->unk5C.z = 0.0f;
        data->unk68 = 0.0f;
        data->unk6C = 0.0f;
        data->unk70 = 0.0f;
        data->unk74 = 0.0f;
        data->unk78.x = data->unk78.y = data->unk78.z = 0.0f;
    }
}

void func_80105B04_coconut_conk(s32 playerIndex) {
    D_800CDA7C_main[GwPlayer[playerIndex].pad] = 0;
    D_800D5558_main[GwPlayer[playerIndex].pad] = 0;
    D_800CBB6E_main[GwPlayer[playerIndex].pad] = 0;
    D_800D20A1_main[GwPlayer[playerIndex].pad] = 0;
}

void func_80105B7C_coconut_conk(u8 arg0) {
    D_8010B1C8_coconut_conk = arg0;
}

f32 func_80105B88_coconut_conk(f32 arg0, f32 *arg1, f32 arg2) {
    f32 value = *arg1;

    *arg1 = value - arg2;
    return arg0 + value;
}

void func_80105BA4_coconut_conk(omObjData *arg0, u8 arg1) {
    s32 character = GwPlayer[arg0->work[0]].chr;

    func_80033354_main(D_8010B1DC_coconut_conk);
    D_8010B1DC_coconut_conk = HmfAnimCreate(HmfModelData[arg0->model[0]].hmf, D_8010B1D0_coconut_conk[arg1], 0,
                                            D_8010AF98_coconut_conk[character]);
}

void func_80105C58_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105C60_coconut_conk);

void func_80105D58_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3E8, 1, 0xA, -1, func_80105C60_coconut_conk);
    obj->work[0] = 0;
    D_8010B1F0_coconut_conk[0].unk00 = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80105D98_coconut_conk);

void func_801060C0_coconut_conk(omObjData *arg0) {
}

void func_801060C8_coconut_conk(omObjData *arg0) {
    D_8010B2B4_coconut_conk = func_8000B838_main(0x23000D);
    D_8010B2B6_coconut_conk = InitEspriteSlot(D_8010B2B4_coconut_conk, 0, 0);
    func_8000BC48_main(D_8010B2B6_coconut_conk, 0x4000);
    D_8010B2B8_coconut_conk = 160.0f;
    D_8010B2BC_coconut_conk = 67.0f;
    func_8000BBD4_main(D_8010B2B6_coconut_conk, 160, 67);
    D_8010B1C4_coconut_conk = func_80055194_main(func_8000B838_main(0x23000E));
    func_8001C8A8_main(func_8001AC8C_main(0, func_80105D98_coconut_conk, 2), 1);
    arg0->func = func_801060C0_coconut_conk;
}

void func_801061AC_coconut_conk(void) {
    omObjData *obj = omAddObj(0x384, 1, 0xA, -1, func_801060C8_coconut_conk);
    obj->work[0] = 0;
    D_8010B274_coconut_conk = obj;
}

void func_801061EC_coconut_conk(omObjData *arg0) {
}

void func_801061F4_coconut_conk(omObjData *arg0) {
    D_8010B3BC_coconut_conk = func_8000B838_main(0x23000F);
    D_8010B3BE_coconut_conk = InitEspriteSlot(D_8010B3BC_coconut_conk, 0, 0);
    func_8000BC48_main(D_8010B3BE_coconut_conk, 0);
    D_8010B3C0_coconut_conk = 160.0f;
    D_8010B3C4_coconut_conk = 219.0f;
    func_8000BBD4_main(D_8010B3BE_coconut_conk, 160, 219);
    arg0->func = func_801061EC_coconut_conk;
}

void func_80106294_coconut_conk(void) {
    omObjData *obj = omAddObj(0x3B6, 1, 0xA, -1, func_801061F4_coconut_conk);
    obj->work[0] = 0;
    D_8010B37C_coconut_conk = obj;
}

void func_801062D4_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B1F0_coconut_conk[4];

    if (func_80049F98_main() + D_800D6A90_main == 0) {
        data->unk18 += 0.2f;
    }
    func_8001E888_main(arg0->model[0], 0.0f, data->unk18, D_8010B1E2_coconut_conk[0], D_8010B1E2_coconut_conk[1],
                       D_8010B0D0_coconut_conk, 0);
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, arg0->trans.z);
}

void func_80106394_coconut_conk(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x230004, 0x289);
    func_8001C954_main(arg0->model[0]);
    func_800335BC_main(D_8010B0E4_coconut_conk, D_8010B1E2_coconut_conk);
    D_8010B418_coconut_conk = 0.0f;
    arg0->trans.x = 0.0f;
    arg0->trans.y = 0.0f;
    arg0->trans.z = 0.0f;
    func_8001C8A8_main(arg0->model[0], 1);
    arg0->func = func_801062D4_coconut_conk;
}

void func_8010641C_coconut_conk(void) {
    omObjData *obj = omAddObj(0x35C, 1, 0, -1, func_80106394_coconut_conk);
    obj->work[0] = 0;
    D_8010B400_coconut_conk = obj;
    omSetStatBit(obj, 0xA0);
}

void func_80106468_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B1F0_coconut_conk[5];

    switch (data->unk04) {
        case 0:
            data->unk1C += 0.005f;
            data->unk20 -= 0.005f;
            if (data->unk1C > 1.1f) {
                data->unk04 = 1;
            }
            break;
        case 1:
            data->unk1C -= 0.005f;
            data->unk20 += 0.005f;
            if (data->unk1C < 1.0f) {
                data->unk04 = 0;
            }
            break;
    }
    arg0->scale.x = arg0->scale.y = arg0->scale.z = data->unk1C;
    Hu3DModelScaleSet(arg0->model[0], arg0->scale.x, arg0->scale.y, arg0->scale.z);
    Hu3DModelScaleSet(arg0->model[1], data->unk20, data->unk20, data->unk20);
}

void func_8010659C_coconut_conk(omObjData *arg0) {
    arg0->model[0] = func_8000B108_main(0x230005, 0x289);
    arg0->model[1] = func_8000B108_main(0x230005, 0x289);
    arg0->trans.x = -400.0f;
    arg0->trans.y = 700.0f;
    arg0->trans.z = -1000.0f;
    Hu3DModelPosSet(arg0->model[0], arg0->trans.x, arg0->trans.y, -1000.0f);
    Hu3DModelPosSet(arg0->model[1], 450.0f, 750.0f, -1000.0f);
    D_8010B4A0_coconut_conk = 1.0f;
    D_8010B4A4_coconut_conk = 1.0f;
    func_8001C8A8_main(arg0->model[0], 2);
    func_8001C8A8_main(arg0->model[1], 2);
    arg0->func = func_80106468_coconut_conk;
}

void func_801066A4_coconut_conk(void) {
    omObjData *obj = omAddObj(0x366, 5, 0xA, -1, func_8010659C_coconut_conk);
    obj->work[0] = 0;
    D_8010B484_coconut_conk = obj;
}

void func_801066E4_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010B508_coconut_conk[arg0->work[0]];

    switch (data->unk04) {
        case 0:
            func_8001C6A8_main(arg0->model[0], 0.0f);
            func_8001C92C_main(arg0->model[0], 0.0f);
            break;
        case 1:
            func_8001C92C_main(arg0->model[0], 1.0f);
            if (D_800CCF58_main[HmfModelData[arg0->model[0]].unk02].unk02 == HmfModelData[arg0->model[0]].unk40) {
                data->unk04 = 0;
            }
            break;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801067E0_coconut_conk);

void func_80106924_coconut_conk(void) {
    u8 i;

    for (i = 0; i < 6; i++) {
        CoconutConkData *data = &D_8010B508_coconut_conk[i];
        omObjData *obj = omAddObj(0x352, 1, 0xA, -1, func_801067E0_coconut_conk);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801069BC_coconut_conk);

void func_80106D40_coconut_conk(void) {
    func_801069BC_coconut_conk();
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106D5C_coconut_conk);

void func_80106E80_coconut_conk(void) {
    u8 i;

    for (i = 0; i < 9; i++) {
        CoconutConkData *data = &D_8010B820_coconut_conk[i];
        omObjData *obj = omAddObj(0x320, 5, 0xA, -1, func_80106D5C_coconut_conk);

        obj->work[0] = i;
        data->unk00 = obj;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80106F18_coconut_conk);

void func_80107674_coconut_conk(void) {
    func_80106F18_coconut_conk();
}

void func_80107690_coconut_conk(omObjData *arg0) {
    CoconutConkData *data = &D_8010BCC4_coconut_conk;

    data->unk04 = 0;
    if (D_800CBB6E_main[arg0->work[3]] <= -30) {
        data->unk04 = 1;
    }
    if (D_800CBB6E_main[arg0->work[3]] >= 30) {
        data->unk04 = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801076EC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801078BC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80107B8C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010815C_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801089DC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80108FA0_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801090C4_coconut_conk);

void func_801095A4_coconut_conk(void) {
    func_801090C4_coconut_conk();
}

void func_801095C0_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_801095C8_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80109940_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_80109DEC_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A344_coconut_conk);

void func_8010A4AC_coconut_conk(void) {
    u32 i;

    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1270.8f;
        CRotM[i].x = 350.94f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 415.0f;
        CenterM[i].z = -115.0f;
    }
}

void func_8010A55C_coconut_conk(omObjData *arg0) {
    u8 i;

    for (i = 0; i < 3; i++) {
        DataClose(D_8010B1D0_coconut_conk[i]);
    }
    func_80033354_main(D_8010B1DC_coconut_conk);
    osViBlack(0);
    HuAudFXStop(-1);
    omOvlReturnEx(1);
}

void func_8010A5D8_coconut_conk(omObjData *arg0) {
    if (WipeStatGet() == 0) {
        arg0->func = func_8010A55C_coconut_conk;
    }
}

void func_8010A610_coconut_conk(omObjData *arg0) {
    if (D_800D530C_main == 1) {
        WipeCreateOut(0, 20);
        arg0->func = func_8010A5D8_coconut_conk;
        HuAudSeqFadeOut(30);
        func_8004AB0C_main(30);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010A668_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AB4C_coconut_conk);

void func_8010AC88_coconut_conk(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AC90_coconut_conk);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", func_8010AE04_coconut_conk);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_02_coconut_conk/120BC0", D_8010B1B8_coconut_conk);
