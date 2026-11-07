#include "common.h"

extern s16 D_80109A68_mgresultdealer;
extern s16 D_80109A6A_mgresultdealer;
extern omObjFunc D_8010A254_mgresultdealer;
extern s8 D_8010A266_mgresultdealer;

void func_80106A50_mgresultdealer(omObjData *);
void func_80106EC0_mgresultdealer(omObjData *);
void func_80106EEC_mgresultdealer(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801059A0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80105C88_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801061C8_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80106234_mgresultdealer);

void func_801062B4_mgresultdealer(void) {
    u16 espriteSlot;

    espriteSlot = espEntry(func_8000B838_main(0x190000), 0, 0);
    espPosSet(espriteSlot, 0xA0, 0x78);
    espAttrSet(espriteSlot, 0x4000);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_8010630C_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801065D0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80106A50_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80106B94_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80106CC8_mgresultdealer);

void func_80106D94_mgresultdealer(void) {
}

extern u8 D_801098E0_mgresultdealer;
extern u8 D_801098E1_mgresultdealer;
extern s8 D_801098E2_mgresultdealer;
extern Vec D_801098E4_mgresultdealer;
extern Vec D_801098F0_mgresultdealer;
extern s32 D_80109A60_mgresultdealer;
extern omObjData *D_8010A250_mgresultdealer;

void func_80106D9C_mgresultdealer(void) {
    omObjData *obj = D_8010A250_mgresultdealer;

    D_801098E0_mgresultdealer = 1;
    D_801098E1_mgresultdealer = 0;
    D_801098E2_mgresultdealer = 0;
    D_801098E4_mgresultdealer.x = 0.0f;
    D_801098E4_mgresultdealer.y = 400.0f;
    D_801098E4_mgresultdealer.z = -55.0f;
    D_801098F0_mgresultdealer.x = 160.0f;
    D_801098F0_mgresultdealer.y = 20.0f;
    D_801098F0_mgresultdealer.z = 0.0f;
    D_80109A60_mgresultdealer = 0;
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, 400.0f, -55.0f);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y, D_801098F0_mgresultdealer.z);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

s8 func_80106EA0_mgresultdealer(void) {
    return D_801098E2_mgresultdealer;
}

void func_80106EAC_mgresultdealer(void) {
    D_8010A254_mgresultdealer = func_80106EC0_mgresultdealer;
}

void func_80106EC0_mgresultdealer(omObjData *obj) {
    func_80106EEC_mgresultdealer();
    D_8010A254_mgresultdealer = func_80106A50_mgresultdealer;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", D_801099A8_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80106EEC_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_8010705C_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801070EC_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801072A8_mgresultdealer);

void func_801073F4_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer->model[0], 2, GwPlayer[D_8010A266_mgresultdealer].chr,
                       D_80109A68_mgresultdealer);
}

void func_80107448_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer->model[0], 2, GwPlayer[D_8010A266_mgresultdealer].chr,
                       D_80109A6A_mgresultdealer);
}
