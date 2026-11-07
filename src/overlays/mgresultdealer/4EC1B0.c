#include "common.h"

extern s8 D_801098D0_mgresultdealer;

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

void func_8010630C_mgresultdealer(s16 model) {
    HmfData_UnkBC *camera = HmfModelData[model].hmf->unkBC;
    HuMtx4F matrix;
    f32 x = camera->unk08 - camera->unk14;
    f32 y = camera->unk0C - camera->unk18;
    f32 z = camera->unk10 - camera->unk1C;
    f32 angle;
    f32 rotatedX, rotatedY;
    s8 i;

    CZoom = HuSqrtf(x * x + y * y + z * z);
    angle = atan2df(z, x);
    CRot.y = -(angle - 90.0f);
    angle = -angle;
    matrix[0][0] = matrix[2][2] = cosdf(angle);
    matrix[2][0] = -sindf(angle);
    matrix[0][2] = sindf(angle);
    matrix[1][1] = matrix[3][3] = 1.0f;
    matrix[1][0] = matrix[3][0] = matrix[0][1] = matrix[2][1] = matrix[3][1] = matrix[1][2] =
        matrix[3][2] = matrix[0][3] = matrix[1][3] = matrix[2][3] = 0.0f;
    rotatedX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0];
    rotatedY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1];
    CRot.x = -atan2df(rotatedY, rotatedX);
    CRot.z = 0.0f;
    if (CZoom > 32000.0f) {
        CZoom = 32000.0f;
    }
    Center.x = camera->unk14;
    Center.y = camera->unk18;
    Center.z = camera->unk1C;
    for (i = 0; i < 4; i++) {
        CRotM[i] = CRot;
        CenterM[i] = Center;
        CZoomM[i] = CZoom;
        Hu3DCameraPerspectiveSet(i, camera->unk2C, 80.0f, 8000.0f);
    }
}
