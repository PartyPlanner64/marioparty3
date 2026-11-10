#include "common.h"
#include "mgresultdealer.h"

extern s16 D_80109A64_mgresultdealer[4];
extern s8 D_8010A266_mgresultdealer[4];
extern s8 D_801098E0_mgresultdealer;
extern u8 D_801098E1_mgresultdealer;
extern s8 D_801098E2_mgresultdealer;
extern Vec D_801098E4_mgresultdealer;
extern Vec D_801098F0_mgresultdealer;
extern f32 D_80109A60_mgresultdealer;
extern s32 D_801098FC_mgresultdealer[];
extern s16 D_8010990C_mgresultdealer;
extern s16 D_801099F8_mgresultdealer[];
extern s32 D_800A178C_main[][6];
extern const s16 D_801099A8_mgresultdealer[][2];

void func_80106A50_mgresultdealer(omObjData *);
void func_80106D94_mgresultdealer(void);
void func_80106B94_mgresultdealer(omObjData *);
void func_80106CC8_mgresultdealer(omObjData *);
void func_80106EC0_mgresultdealer(omObjData *);
void func_80106EEC_mgresultdealer(void);
void func_8010705C_mgresultdealer(omObjData *);
void func_801070EC_mgresultdealer(s16);
void func_801072A8_mgresultdealer(s16);

void func_801065D0_mgresultdealer(void) {
    omObjData *obj;
    s16 chr;

    obj = omAddObj(20, 8, 5, -1, NULL);
    D_8010A250_mgresultdealer.obj = obj;
    chr = GwPlayer[D_8010A266_mgresultdealer[0]].chr;

    obj->model[0] = func_8000B108_main(D_800A178C_main[chr][0] | D_800A178C_main[chr][2], 0x2A9);
    func_8001C814_main(obj->model[0], 2, 2);
    Hu3DModelCameraSet(obj->model[0], 1);

    obj->model[1] = func_8000B108_main(0x83, 0x2B9);
    func_8001C814_main(obj->model[1], 2, 0);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[1], 0.0f, 140.0f, 0.0f);
    Hu3DModelCameraSet(obj->model[1], 2);

    obj->model[2] = func_8000B108_main(0x190003, 0x2B9);
    func_8001C814_main(obj->model[2], 2, 0);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(obj->model[2], 0.0f, 400.0f, -35.0f);
    Hu3DModelCameraSet(obj->model[2], 2);

    obj->model[3] = func_8000B108_main(9, 0x2B9);
    Hu3DModelPosSet(obj->model[3], 0.0f, -5.0f, -35.0f);
    Hu3DModelScaleSet(obj->model[3], 1.0f, 1.0f, 1.0f);
    Hu3DModelCameraSet(obj->model[3], 1);

    obj->model[4] = func_8000B108_main(0x190006, 0x2B9);
    obj->model[5] = func_8000B108_main(0x190007, 0x2B9);
    obj->model[6] = func_8000B108_main(0x190008, 0x2B9);
    Hu3DModelCameraSet(obj->model[4], 2);
    Hu3DModelCameraSet(obj->model[5], 2);
    Hu3DModelCameraSet(obj->model[6], 2);
    func_8001C258_main(obj->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[5], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);

    D_80109A64_mgresultdealer[0] = func_80017790_main(obj->model[0], 2, chr, func_80017BB8_main(chr, 0xA4));
    D_80109A64_mgresultdealer[1] = func_80017AD8_main(func_80017BB8_main(chr, 0xAA));
    D_80109A64_mgresultdealer[2] = func_80017AD8_main(func_80017BB8_main(chr, 0xA5));
    D_80109A64_mgresultdealer[3] = func_80017AD8_main(func_80017BB8_main(chr, 0xA6));
    func_8001C514_main(obj->model[0]);
    func_80017954_main(obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr, D_80109A64_mgresultdealer[0]);

    func_8000B460_main(obj, 0, func_80017BB8_main(chr, 0));
    func_8000B460_main(obj, 1, func_80017BB8_main(chr, 0x2F));
    func_8000B460_main(obj, 2, func_80017BB8_main(chr, D_801099A8_mgresultdealer[chr][1]));
    func_8000B460_main(obj, 3, func_80017BB8_main(chr, 0x25));
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);

    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = -35.0f;
    Hu3DModelPosSet(obj->model[0], obj->trans.x, obj->trans.y, obj->trans.z);
    omPrcSetDestructor(0, func_80106D94_mgresultdealer);
    D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;

    while (TRUE) {
        D_8010A250_mgresultdealer.func(obj);
        HuPrcVSleep();
    }
}

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
            D_8010A250_mgresultdealer.func = func_80106B94_mgresultdealer;
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
        D_8010A250_mgresultdealer.func = func_80106CC8_mgresultdealer;
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
        D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;
    }
    Hu3DModelPosSet(obj->model[2], D_801098E4_mgresultdealer.x, D_801098E4_mgresultdealer.y,
                    D_801098E4_mgresultdealer.z);
    Hu3DModelRotSet(obj->model[2], D_801098F0_mgresultdealer.x, D_801098F0_mgresultdealer.y,
                    D_801098F0_mgresultdealer.z);
}

void func_80106D94_mgresultdealer(void) {
}

void func_80106D9C_mgresultdealer(void) {
    omObjData *obj = D_8010A250_mgresultdealer.obj;

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
    D_8010A250_mgresultdealer.func = func_80106EC0_mgresultdealer;
}

void func_80106EC0_mgresultdealer(omObjData *obj) {
    func_80106EEC_mgresultdealer();
    D_8010A250_mgresultdealer.func = func_80106A50_mgresultdealer;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mgresultdealer/4ECDE0", D_801099A8_mgresultdealer);

void func_80106EEC_mgresultdealer(void) {
    s16 model;
    s16 i;

    for (i = 0; i < 4; i++) {
        model = func_8000B108_main(D_801098FC_mgresultdealer[i], 0x2A9);
        D_801099F8_mgresultdealer[i] = model;
        Hu3DAnmNoSet(Hu3DAnimRead(Hu3DData[model].hmf, 0xB0048, "e268p01_I8"), i * 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        func_8001C2FC_main(model, 0x20000, 0x20000);
        Hu3DModelRemakeStatic(model);
        func_8001C954_main(model);
        func_8001C514_main(model);
        func_80013390_main(model, -1, 0, func_801072A8_mgresultdealer);
        Hu3DModelCameraSet(model, 2);
    }
    omAddObj(10, 10, 10, -1, func_8010705C_mgresultdealer);
}

void func_8010705C_mgresultdealer(omObjData *obj) {
    s16 i;

    for (i = 0; i < 4; i++) {
        if (((D_8010990C_mgresultdealer + i) & 7) == 0) {
            func_801070EC_mgresultdealer(D_801099F8_mgresultdealer[i]);
        }
    }
    D_8010990C_mgresultdealer++;
}

void func_801070EC_mgresultdealer(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle = bc->unk58;
    s16 count = hmf->unk1A;
    s16 i;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 <= 0.0f) {
            particle->unk0C = (100.0f - rand8() % 200) * 2.0f;
            particle->unk10 = 500.0f;
            particle->unk14 = ((rand8() * 125) >> 5) - 500;
            particle->unk18 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk1C = 0.0f;
            particle->unk20 = ((s32)((rand8() * 5U) >> 7) - 5) / 2.0f;
            particle->unk08 = 3.0f;
            break;
        }
    }
}

void func_801072A8_mgresultdealer(s16 model) {
    HmfData *hmf = Hu3DData[model].hmf;
    HmfModelData_UnkBC_Struct *bc = Hu3DData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (bc->unk02 == 0) {
        bc->unk04 &= ~4;
        particle = bc->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
            particle->unk24 = particle->unk28 = particle->unk2C = 0.0f;
            particle->unk08 = 0.0f;
            particle->unk04 = 1.0f;
        }
        bc->unk02++;
    }
    particle = bc->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk10 > 0.0f) {
            particle->unk0C += particle->unk18;
            particle->unk10 += particle->unk1C - 8.0f;
            particle->unk14 += particle->unk20;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_801073F4_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer.obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr,
                       D_80109A64_mgresultdealer[2]);
}

void func_80107448_mgresultdealer(void) {
    func_80017954_main(D_8010A250_mgresultdealer.obj->model[0], 2, GwPlayer[D_8010A266_mgresultdealer[0]].chr,
                       D_80109A64_mgresultdealer[3]);
}
