#include "common.h"

void func_80105D9C_inst(omObjData *);  /* extern */
void func_801061EC_inst(void);         /* extern */
void func_80106310_inst(omObjData *);  /* extern */
void func_80106388_inst(void);         /* extern */
void func_8010674C_inst(omObjData *);  /* extern */
void func_801067CC_inst(void);         /* extern */
void func_80106850_inst(Vec *, Vec *); /* extern */
void func_80106898_inst(void);         /* extern */
void func_80106EB4_inst(void);         /* extern */
void func_80107308_inst(void);         /* extern */
void func_80107470_inst(void);         /* extern */
void func_80107A24_inst(omObjData *);  /* extern */
void func_80107BF8_inst(omObjData *);  /* extern */
void func_80108350_inst(void);         /* extern */
void func_801094B0_inst(void);         /* extern */
void func_8010986C_inst(omObjData *);  /* extern */
void func_80109A90_inst(void);         /* extern */
void func_8010A1D0_inst(void);         /* extern */
void func_8010B990_inst(void);         /* extern */
void func_8000BC48_main(u16, u16);     /* extern */

extern f32 D_800CB890_main;
extern f32 D_800CE17C_main[];
extern f32 D_800D5210_main;

extern s8 D_8010D400_inst[7];
extern s8 D_8010D407_inst;
extern s8 D_8010D408_inst;
extern s8 D_8010D40A_inst;
extern s8 D_8010D40B_inst;
extern s8 D_8010D411_inst;
extern Vec D_8010D418_inst;
extern Vec D_8010D424_inst;
extern Vec D_8010D430_inst;
extern Vec D_8010D450_inst;
extern Vec D_8010D45C_inst;
extern Vec D_8010D480_inst;
extern Vec D_8010D48C_inst;
extern void *D_8010DC10_inst;
extern void *D_8010DC14_inst;
extern void *D_8010DC18_inst;
extern omObjData *D_8010DDD8_inst;
extern void (*D_8010DDDC_inst)(omObjData *);
extern void (*D_8010DDEC_inst)(omObjData *);
extern s32 D_8010D658_inst[];

void func_801059A0_inst(void) {
    void (*procFunc)(void) = NULL;
    s16 var_a1 = 0;
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_8010D400_inst[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }
    D_8010D40B_inst = GwSystem.minigame_index - 1;
    D_8010D40A_inst = D_800A6D44_main[D_8010D40B_inst].minigameType;

    if (_CheckFlag(0xF) != 0) {
        D_8010D407_inst = 1;
        D_8010D408_inst = 1;
    } else {
        D_8010D407_inst = 0;
        if ((GWMgUnlockCheck(D_8010D40B_inst)) != 0) {
            D_8010D408_inst = 1;
        }
    }

    GWMgUnlockSet(-1);
    _ClearFlag(0xF);
    func_80106EB4_inst();
    func_80106898_inst();
    func_80107308_inst();

    if ((GwSystem.show_minigame_explanations == 1) || (D_8010D40A_inst == 6)) {
        func_801061EC_inst();
        return;
    }

    Hu3DAnimInit(1);
    omInitObjMan(0x1E, 0x1E);
    func_8005A6B0_main();
    func_8000B5F0_main(1);
    ScissorSet(0, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCamSetPerspective(0, 15.0f, 500.0f, 8000.0f);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, func_8010674C_inst), 0xA0U);
    func_800142A0_main(0x28);
    HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    omAddPrcObj(func_80107470_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010B990_inst, 0x1001, 0x1000, 0);
    omAddPrcObj(func_8010A1D0_inst, 0x1001, 0x1000, 0);

    switch (D_8010D40A_inst) {
        case 5:
            procFunc = func_801094B0_inst;
            D_8010D411_inst = 1;
            break;
        case 4:
            if (omovlhisidx <= 0) {
                break;
            }
            if (GwSystem.playMode & 2) {
                procFunc = func_80108350_inst;
                D_8010D411_inst = 0;
                break;
            }
        case 3:
            procFunc = func_80109A90_inst;
            D_8010D411_inst = 2;
            break;
        case 0:
        case 1:
        case 2:
        case 6:
        case 7:
        case 8:
        default:
            procFunc = func_80108350_inst;
            D_8010D411_inst = 0;
            break;
    }

    omAddPrcObj(procFunc, 0x1001, 0x800, 0);
    omAddObj(0, 0, 0, -1, func_80105D9C_inst);
    omAddObj(0, 0, 0, -1, func_80106310_inst);
    func_80106388_inst();
    func_80106850_inst(&D_8010D45C_inst, &D_8010D48C_inst);
    func_801067CC_inst();
    WipeCreateIn(0xFF, 0x10);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80105D9C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_801061EC_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80106310_inst);

void func_80106388_inst(void) {
    u16 espriteSlot;

    espriteSlot = InitEspriteSlot(func_8000B838_main(D_8010D658_inst[D_8010D40A_inst]), 0, 0);
    func_8000BBD4_main(espriteSlot, 0xA0, 0x78);
    func_8000BC48_main(espriteSlot, 0x4000);
}

void func_801063F4_inst(void) {
    func_80037258_main();
    func_8005F524_main();
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D658_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80106418_inst);

void func_8010674C_inst(omObjData *object) {
    D_800CE17C_main[0] = D_8010D418_inst.x;
    D_800CE17C_main[1] = D_8010D418_inst.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = gCameraList->fov[0];
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCamSetPositionOrientation(0, &D_8010D418_inst, &D_8010D424_inst, &D_8010D430_inst);
    Hu3DCamUpdateMtx(0);
}

void func_801067CC_inst(void) {
    D_8010D418_inst.x = D_8010D450_inst.x;
    D_8010D418_inst.y = D_8010D450_inst.y;
    D_8010D418_inst.z = D_8010D450_inst.z;
    D_8010D424_inst.x = D_8010D480_inst.x;
    D_8010D424_inst.y = D_8010D480_inst.y;
    D_8010D424_inst.z = D_8010D480_inst.z;
    D_8010D430_inst.x = 0.0f;
    D_8010D430_inst.y = 1.0f;
    D_8010D430_inst.z = -0.000001f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80106850_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80106898_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6B0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6D8_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D6E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D70C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D718_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D724_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80106EB4_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107308_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107470_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107938_inst);

void func_801079CC_inst(omObjData *obj) {
    func_8001C814_main(obj->model[3], 1, 0);
    func_8001C258_main(obj->model[3], 4, 0);
    D_8010DDDC_inst = func_80107A24_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107A24_inst);

void func_80107BE4_inst(void) {
    D_8010DDDC_inst = func_80107BF8_inst;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D770_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D784_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D78C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D794_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D79C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7A4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7AC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7B0_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7C4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7CC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7D4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7DC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D7EC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D800_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D808_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D810_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D818_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D820_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D828_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D83C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D844_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D84C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D854_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D85C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D864_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D870_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D878_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D880_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D888_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D890_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D89C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8B4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8BC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8C4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8CC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8D4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8DC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8E4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8EC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8F4_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D8FC_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D904_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D90C_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D910_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D954_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D978_inst);

INCLUDE_RODATA("asm/nonmatchings/overlays/inst/4DEB60", D_8010D980_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107BF8_inst);

void func_80107E18_inst(void) {
}

s32 func_80107E20_inst(void) {
    s16 modelId = D_8010DDD8_inst->model[0];
    f32 unk40 = HmfModelData[modelId].unk40;
    return D_800CCF58_main[HmfModelData[modelId].unk02].unk02 <= unk40;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107E98_inst);

void func_80107EE0_inst(void) {
    DataClose(D_8010DC18_inst);
    DataClose(D_8010DC10_inst);
    DataClose(D_8010DC14_inst);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107F18_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80107F98_inst);

s32 func_801080A8_inst(void) {
    f32 unk40 = HmfModelData[D_8010DDD8_inst->model[0]].unk40;
    return unk40 == 0.0f;
}

void func_801080FC_inst(void) {
    omObjData *obj = D_8010DDD8_inst;

    func_8001C814_main(obj->model[0], 1, 0);
    func_8001C258_main(obj->model[0], 4, 0);
    func_8001C814_main(obj->model[0], 4, 4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_8010815C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108350_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_8010872C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108808_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108870_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108954_inst);

void func_80108A10_inst(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108A18_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_80108AF0_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_801094B0_inst);

void func_801097DC_inst(omObjData *object) {
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(*object->model, object->trans.x, object->trans.y, object->trans.z);
    D_8010DDEC_inst = func_8010986C_inst;
}

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_8010986C_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_801098D8_inst);

INCLUDE_ASM("asm/nonmatchings/overlays/inst/4DEB60", func_801099C0_inst);

void func_80109A84_inst(void) {
}
