#include "common.h"

extern s16 D_80109A68_mgresultdealer;
extern s16 D_80109A6A_mgresultdealer;
extern omObjFunc D_8010A254_mgresultdealer;
extern s8 D_8010A266_mgresultdealer;
extern s8 D_801098D0_mgresultdealer;
extern s8 D_801098E0_mgresultdealer;
extern u8 D_801098E1_mgresultdealer;
extern s8 D_801098E2_mgresultdealer;
extern Vec D_801098E4_mgresultdealer;
extern Vec D_801098F0_mgresultdealer;
extern f32 D_80109A60_mgresultdealer;
extern omObjData *D_8010A250_mgresultdealer;

void func_80106A50_mgresultdealer(omObjData *);
void func_80106B94_mgresultdealer(omObjData *);
void func_80106CC8_mgresultdealer(omObjData *);
void func_80106EC0_mgresultdealer(omObjData *);
void func_80106EEC_mgresultdealer(void);
void func_8010630C_mgresultdealer(s16);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801059A0_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_80105C88_mgresultdealer);

void func_801061C8_mgresultdealer(void) {
    s16 model;

    model = func_8000B108_main(0x190002, 0x2002B9);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_80019828_main(model, 2);
    func_80013320_main(model, 0);
    func_8010630C_mgresultdealer(model);
}

void func_80106234_mgresultdealer(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_801098D0_mgresultdealer == 0) {
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            D_801098D0_mgresultdealer = 1;
            return;
        }
        if (WipeStatGet() == 0) {
            HuAudSeqFadeOut(30);
            func_8004AB0C_main(30);
            GameMesStub();
            omOvlReturnEx(1);
        }
    }
}

void func_801062B4_mgresultdealer(void) {
    u16 espriteSlot;

    espriteSlot = espEntry(func_8000B838_main(0x190000), 0, 0);
    espPosSet(espriteSlot, 0xA0, 0x78);
    espAttrSet(espriteSlot, 0x4000);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_8010630C_mgresultdealer);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultdealer/4EC1B0", func_801065D0_mgresultdealer);

void func_80106A50_mgresultdealer(omObjData *obj) {
    if (D_801098E0_mgresultdealer) {
        D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
        D_80109A60_mgresultdealer += 0.98f;
        D_801098F0_mgresultdealer.x += 30.0f;
        if (D_801098E4_mgresultdealer.y <= 180.0f) {
            func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            D_801098E4_mgresultdealer.y = 180.0f;
            D_80109A60_mgresultdealer = -10.0f;
            D_801098E2_mgresultdealer = 1;
            HuAudFXPlay(0x515);
            HuAudFXPlay(0x518);
            D_8010A254_mgresultdealer = func_80106B94_mgresultdealer;
        }
        Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y,
                        D_801098E4_mgresultdealer.z);
        Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y,
                        D_801098F0_mgresultdealer.z);
    }
}

void func_80106B94_mgresultdealer(omObjData *obj) {
    D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
    D_80109A60_mgresultdealer += 0.98f;
    D_801098E4_mgresultdealer.x += 5.0f;
    D_801098E4_mgresultdealer.z -= 5.0f;
    D_801098F0_mgresultdealer.x -= 5.0f;
    D_801098F0_mgresultdealer.y -= 5.0f;
    if (D_801098E4_mgresultdealer.y <= 20.0f) {
        D_801098E4_mgresultdealer.y = 20.0f;
        func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        D_80109A60_mgresultdealer = -2.0f;
        D_8010A254_mgresultdealer = func_80106CC8_mgresultdealer;
    }
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y,
                    D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y,
                    D_801098F0_mgresultdealer.z);
}

void func_80106CC8_mgresultdealer(omObjData *obj) {
    D_801098E4_mgresultdealer.y -= D_80109A60_mgresultdealer;
    D_80109A60_mgresultdealer += 0.98f;
    if (D_801098E4_mgresultdealer.y <= 0.0f) {
        D_801098E4_mgresultdealer.y = 0.0f;
        D_801098E0_mgresultdealer = 0;
        D_8010A254_mgresultdealer = func_80106A50_mgresultdealer;
    }
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y,
                    D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y,
                    D_801098F0_mgresultdealer.z);
}

void func_80106D94_mgresultdealer(void) {
}

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

extern s16 D_8010990C_mgresultdealer;
extern s16 D_801099F8_mgresultdealer[];

void func_801070EC_mgresultdealer(s16);

void func_8010705C_mgresultdealer(void) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (((D_8010990C_mgresultdealer + i) & 7) == 0) {
            func_801070EC_mgresultdealer(D_801099F8_mgresultdealer[i]);
        }
    }
    D_8010990C_mgresultdealer++;
}

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
