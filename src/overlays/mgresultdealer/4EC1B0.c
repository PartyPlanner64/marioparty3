#include "common.h"
#include "game/gamework_data.h"
#include "game/object.h"
#include "game/wipe.h"

extern s8 D_801098D0_mgresultdealer;
extern s16 D_8010A258_mgresultdealer;
extern s16 D_8010A264_mgresultdealer;
extern s8 D_8010A266_mgresultdealer[4];

void func_80105C88_mgresultdealer(omObjData *);
void func_80106234_mgresultdealer(omObjData *);
void func_801061C8_mgresultdealer(void);
void func_801062B4_mgresultdealer(void);
void func_8010630C_mgresultdealer(s16);
void func_801065D0_mgresultdealer(void);
void func_801074A0_mgresultdealer(void);
void func_80108040_mgresultdealer(void);
void func_80108570_mgresultdealer(void);

void func_801059A0_mgresultdealer(void) {
    omObjData *obj;
    s16 count;
    s16 i;
    s16 j;

    count = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < MB_MAX_PLAYERS; j++) {
            if (i != GwPlayer[j].group) {
                continue;
            }
            D_8010A266_mgresultdealer[count] = j;
            count++;
            if (count >= 4) {
                break;
            }
        }
        if (count >= 4) {
            break;
        }
    }
    func_800142A0_main(100);
    omInitObjMan(0x1E, 0x28);
    func_8000B690_main(2);
    for (i = 0; i < 2; i++) {
        ScissorSet(i, 0.0f, 0.0f, 320.0f, 240.0f);
        ViewportSet(i, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
        Hu3DCameraPerspectiveSet(i, 30.0f, 80.0f, 8000.0f);
    }
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutViewMulti);
    omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    obj->work[0] = 2;
    D_8010A264_mgresultdealer = GwPlayer[D_8010A266_mgresultdealer[0]].gameCoin;
    D_8010A258_mgresultdealer = GwPlayer[D_8010A266_mgresultdealer[0]].bonusCoin;
    omAddPrcObj(func_801065D0_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_801074A0_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80108040_mgresultdealer, 0x1001, 0x2000, 0);
    omAddPrcObj(func_80108570_mgresultdealer, 0x1001, 0x2000, 0);
    omAddObj(0, 0, 0, -1, func_80105C88_mgresultdealer);
    omAddObj(0, 0, 0, -1, func_80106234_mgresultdealer);
    func_801062B4_mgresultdealer();
    func_801061C8_mgresultdealer();
    WipeCreateIn(WIPE_TYPE_PREV, 0x10);
}

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
