#include "common.h"
#include "inst.h"

extern s8 D_8010D408_inst;
extern s32 D_8010DC30_inst;
extern s16 D_8010DC32_inst;
extern InstObjectState D_8010DDE8_inst;
extern void (*D_8010DDEC_inst)(omObjData *);
extern s32 D_8010D530_inst;
extern s32 D_8010D534_inst;

void func_801097DC_inst(omObjData *);
void func_8010986C_inst(omObjData *);
void func_801098D8_inst(omObjData *);
void func_801099C0_inst(omObjData *);
void func_80109A84_inst(omObjData *);
void func_8010C848_inst(void);
void func_8010C8D0_inst(void);

void func_801094B0_inst(void) {
    omObjData *object;
    void *data;

    object = omAddObj(25, 5, 8, -1, NULL);
    D_8010DDE8_inst.object = object;
    object->model[0] = func_8000B108_main(0xA0000, 0x16A9);
    func_8000B460_main(object, 0, 0xA0001);
    func_8000B460_main(object, 1, 0xA0002);
    func_8000B460_main(object, 2, 0xA0006);
    func_8000B460_main(object, 3, 0xA0023);
    func_8000B460_main(object, 4, 0xA0018);
    func_8001C5B4_main(object->model[0], object->motion[1]);
    func_8001C814_main(object->model[0], 2, 2);
    data = DataRead(0xA002A);
    D_8010DC30_inst = (s16)HmfAnimCreate(HmfModelData[object->model[0]].hmf, data, 0, "c160n_0_DEF");
    HuMemMemoryFreePerm(data);
    func_8001C448_main(object->model[0]);
    func_8001C514_main(object->model[0]);
    func_80032FC0_main(D_8010DC32_inst, 1, 0);
    func_80032FF8_main(D_8010DC32_inst, 0);
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    object->scale.x = object->scale.y = object->scale.z = 0.5f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    object->scale.x = object->scale.y = object->scale.z = 0.4f;
    Hu3DModelScaleSet(object->model[0], 0.4f, 0.4f, 0.4f);
    func_8001C258_main(object->model[0], 4, 4);
    if (D_8010D408_inst == 1) {
        func_8001C5B4_main(object->model[0], object->motion[3]);
        func_8001C814_main(object->model[0], 2, 2);
        func_8001C258_main(object->model[0], 4, 0);
        object->trans.x = -91.0f;
        object->trans.y = 29.0f;
        object->trans.z = 210.0f;
        object->rot.x = -20.0f;
        object->rot.y = 15.0f;
        D_8010DDE8_inst.update = func_80109A84_inst;
    } else {
        D_8010DDEC_inst = func_801097DC_inst;
    }
    while (1) {
        D_8010DDEC_inst(object);
        HuPrcVSleep();
    }
}

void func_801097DC_inst(omObjData *object) {
    object->trans.x = -91.0f;
    object->trans.y = -171.0f;
    object->trans.z = 210.0f;
    object->rot.x = -20.0f;
    object->rot.y = 15.0f;
    Hu3DModelPosSet(*object->model, object->trans.x, object->trans.y, object->trans.z);
    D_8010DDEC_inst = func_8010986C_inst;
}

void func_8010986C_inst(omObjData *object) {
    D_8010D530_inst++;
    if (D_8010D530_inst >= 100) {
        D_8010DDEC_inst = func_801098D8_inst;
        D_8010D530_inst = 0;
        func_8001C258_main(object->model[0], 4, 0);
        HuAudFXPlay(0x298);
        func_8010C8D0_inst();
    }
}

void func_801098D8_inst(omObjData *object) {
    D_8010D534_inst++;
    object->trans.y = sindf(D_8010D534_inst * 5) * 200.0f + -171.0f;
    if (D_8010D534_inst == 13) {
        func_8001C5B4_main(object->model[0], object->motion[4]);
        func_8001C814_main(object->model[0], 2, 0);
    }
    if (D_8010D534_inst >= 17) {
        object->trans.y = 29.0f;
        D_8010D534_inst = 0;
        D_8010DDEC_inst = func_801099C0_inst;
    }
}

void func_801099C0_inst(omObjData *object) {
    s16 model = object->model[0];

    if (D_800CCF58_main[HmfModelData[model].unk02].unk02 <= HmfModelData[model].unk40) {
        func_8001C624_main(model, HmfModelData[object->motion[3]].unk02, 0, 30, 2);
        func_8010C848_inst();
        D_8010DDEC_inst = func_80109A84_inst;
    }
}

void func_80109A84_inst(omObjData *object) {
}
