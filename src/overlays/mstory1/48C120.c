#include "common.h"

typedef struct UnkStoryObj {
    /* 0x00 */ omObjData *obj;
    /* 0x04 */ void (*func)(omObjData *);
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
    /* 0x14 */ s32 unk_14;
} UnkStoryObj; // sizeof 0x18

typedef struct MstoryPath {
    /* 0x00 */ s16 count;
    /* 0x02 */ u16 flags;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec *points;
    /* 0x0C */ f32 (*intervals)[2];
} MstoryPath; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;

extern Vec D_80114A8C_mstory1;
extern Vec D_80114A98_mstory1;
extern Vec D_80114AA4_mstory1;

extern s32 D_80114A80_mstory1;
extern s32 D_80114A84_mstory1;
extern s8 D_80114A88_mstory1;
extern s32 D_80114AB0_mstory1;
extern s32 D_80114AC0_mstory1;
extern Vec D_80114E40_mstory1;
extern Vec D_80114E4C_mstory1;
extern Vec D_80114F00_mstory1;
extern Vec D_80114F0C_mstory1;
extern Vec D_80115038_mstory1;
extern Vec D_80115050_mstory1;
extern s16 D_801158B0_mstory1;
extern s16 D_801158B2_mstory1;
extern u16 D_801158B8_mstory1;
extern s32 D_801158B4_mstory1;
extern s32 D_801158E4_mstory1;
extern UnkStoryObj D_801158F0_mstory1[7];
extern s16 D_80115A10_mstory1;

void func_80105FF4_mstory1(void);
void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames);
void func_80106B30_mstory1(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_80106D80_mstory1(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_8010704C_mstory1(omObjData *obj, Vec *pos, s32 frames);
s32 func_8010726C_mstory1(s16 model);
void func_801081D8_mstory1(omObjData *obj);
void func_80106984_mstory1(void);
void func_801081E0_mstory1(void);
void func_80109140_mstory1(void);
void func_801099F8_mstory1(void);
void func_80109DC0_mstory1(void);
void func_8010A424_mstory1(void);
void func_8010AA98_mstory1(void);
void func_8010B110_mstory1(void);
void func_8010B3B8_mstory1(void);
void func_8010B4E4_mstory1(void);
void func_8010BC68_mstory1(void);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C50_mstory1);

void func_80105C90_mstory1(void) {
    u32 state = D_80114A80_mstory1;
    s32 btn;

    switch (state) {
        case 0:
            HuAudSeqPlay(0x26);
            state++;
            break;
        case 1:
            state += WipeStatGet() == 0;
            break;
        case 2:
            if (D_80114A84_mstory1 == 1) {
                btn = D_800D5558_main[D_801158B4_mstory1] & START_BUTTON;
                state += btn != 0;
            }
            break;
        case 3:
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            state++;
            break;
        case 4:
            if (WipeStatGet() == 0) {
                HuWinAllKill();
                SLCommonSet(1);
                omOvlReturnEx(1);
            }
            break;
    }
    D_80114A80_mstory1 = state;
}

void func_80105D80_mstory1(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80114A88_mstory1 == 0) {
            WipeCreateOut(2, 20);
            HuAudSeqFadeOut(30);
            D_80114A88_mstory1 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E00_mstory1(void) {
    D_801158B8_mstory1 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_801158B8_mstory1, 160, 120);
    espAttrSet(D_801158B8_mstory1, 0x4000);
    D_801158B2_mstory1 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_801158B2_mstory1, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_801158B2_mstory1, 2, 0);
    func_8001C814_main(D_801158B2_mstory1, 1, 1);
}

void func_80105EC0_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_801158B8_mstory1);
}

void func_80105EF4_mstory1(void) {
    func_8001C258_main(D_801158B2_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_801158B8_mstory1);
}

void func_80105F28_mstory1(void) {
    D_800CE17C_main[0] = D_80114A8C_mstory1.x;
    D_800CE17C_main[1] = D_80114A8C_mstory1.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80114A8C_mstory1, &D_80114A98_mstory1, &D_80114AA4_mstory1);
    Hu3DCamUpdateMtx(0);
}

void func_80105FA8_mstory1(void) {
    D_80114A80_mstory1 = 3;
}

void func_80105FB8_mstory1(s32 arg0) {
    D_801158E4_mstory1 = arg0;
    D_80114AB0_mstory1 = 0;
    omAddPrcObj(func_80105FF4_mstory1, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80105FF4_mstory1);

s32 func_80106894_mstory1(void) {
    return D_80114AB0_mstory1;
}

void func_801068A0_mstory1(void) {
}

void func_801068A8_mstory1(void) {
}

void func_801068B0_mstory1(s16 model, s16 animSlot, s16 anim) {
    HmfAnim *entry;

    if (animSlot >= 0) {
        if (anim == -1) {
            func_80033910_main(Hu3DData[model].hmf);
        } else {
            func_80033970_main(Hu3DData[model].hmf);
            entry = &D_800D1714_main[animSlot];
            entry->animIdx = anim;
            entry->rot = 0;
            entry->flags = 0;
            entry->interp = 0;
            entry->frame = 0;
        }
    }
}

void func_80106984_mstory1(void) {
    D_801158B0_mstory1 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_801158B0_mstory1, 1 << D_801158B4_mstory1);
    HuWinInsertMesSet(D_801158B0_mstory1, GwStory.unk1 + 0x1C00, 0);
}

void func_801069EC_mstory1(void) {
    HuWinHomeClear(D_801158B0_mstory1);
    func_80060C14_main(D_801158B0_mstory1, 1);
}

void func_80106A1C_mstory1(void) {
    func_80060EA8_main(D_801158B0_mstory1, 1);
}

void func_80106A40_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

void func_80106A94_mstory1(s32 mess) {
    HuWinMesSet(D_801158B0_mstory1, mess, -1, -1);
}

void func_80106AC0_mstory1(void) {
    while (HuWinStatGet(D_801158B0_mstory1) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106AFC_mstory1(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106B14_mstory1(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106B30_mstory1(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106B30_mstory1);

void func_80106D64_mstory1(omObjData *obj, Vec *pos, s32 frames) {
    func_80106D80_mstory1(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80106D80_mstory1);

void func_80106F94_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B14_mstory1(obj, &pos, frames);
}

void func_80106FC0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106B30_mstory1(obj, &pos, frames, arg3);
}

void func_80106FF0_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D64_mstory1(obj, &pos, frames);
}

void func_8010701C_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106D80_mstory1(obj, &pos, frames, arg3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010704C_mstory1);

void func_801071F4_mstory1(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010704C_mstory1(obj, &pos, frames);
}

void func_80107220_mstory1(s16 model) {
    HuPrcSleep(10);
    while (!func_8010726C_mstory1(model)) {
        HuPrcVSleep();
    }
}

s32 func_8010726C_mstory1(s16 model) {
    f32 time = Hu3DMotionShiftTimeGet(model);
    s32 ret = 0;

    if (time == -1.0f && D_800CCF58_main[Hu3DData[model].motId].unk02 <= Hu3DData[model].motTime) {
        ret = -1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80107318_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801074C0_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801077C4_mstory1);

void func_8010806C_mstory1(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

void func_8010809C_mstory1(void) {
    func_80106984_mstory1();
    D_80115A10_mstory1 = func_8000B108_main(9, 0x2B9);
    omAddPrcObj(func_801081E0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109140_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_801099F8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_80109DC0_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010A424_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010AA98_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B110_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B3B8_mstory1, 0x1001, 0x800, 0);
    omAddPrcObj(func_8010B4E4_mstory1, 0x384, 0x800, 0);
    omAddPrcObj(func_8010BC68_mstory1, 0x384, 0x800, 0);
    HuPrcVSleep();
    func_8001C258_main(D_80115A10_mstory1, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_801081D8_mstory1(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801081E0_mstory1);

void func_801085F0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114C88_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CB0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CBC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CC8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CD4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CE0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CEC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114CF8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D04_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D10_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D50_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D70_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114D9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DCC_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801085F8_mstory1);

void func_80109014_mstory1(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[9]].motId, 0, 10, 0);
    func_80107220_mstory1(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_801090D8_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114E40_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

void func_8010910C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114E4C_mstory1, 10);
    D_801158F0_mstory1[0].func = func_801081D8_mstory1;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114DFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E08_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E14_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E20_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E30_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E38_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E40_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E4C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109140_mstory1);

void func_80109470_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E64_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109478_mstory1);

void func_8010980C_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80114F0C_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80114F00_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801158F0_mstory1[1].func = func_801081D8_mstory1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109888_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_801099F8_mstory1);

void func_80109C20_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E7C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114E94_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EA0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EAC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EB8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EC4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114ED0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EDC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114EE8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F00_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F0C_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109C28_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109DC0_mstory1);

void func_80109FD0_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F30_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_80109FD8_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A424_mstory1);

void func_8010A608_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010A610_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AA98_mstory1);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010AC40_mstory1);

void func_8010B108_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B110_mstory1);

void func_8010B300_mstory1(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F48_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F54_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F6C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F78_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F84_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F90_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114F9C_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FA8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FB4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FC0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FCC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FD8_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FE4_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FF0_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80114FFC_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115008_mstory1);

const Vec D_80115020_mstory1 = { 700.0f, 0.0f, 150.0f };
const Vec D_8011502C_mstory1 = { 216.66666f, 0.0f, 150.0f };

void func_8010B308_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115038_mstory1, 10);
    func_80106B14_mstory1(obj, &D_80115020_mstory1, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

void func_8010B384_mstory1(omObjData *obj) {
    func_8010704C_mstory1(obj, &D_80115050_mstory1, 20);
    D_801158F0_mstory1[6].func = func_801081D8_mstory1;
}

void func_8010B3B8_mstory1(void) {
    f32 angle = 0.0f;
    Vec pos;
    f32 ofs;
    s16 model;

    if (D_80114AC0_mstory1 != 0) {
        model = D_801158F0_mstory1[6].obj->model[1];
        pos.y = Hu3DData[model].pos.y;
        while (TRUE) {
            pos.x = Hu3DData[model].pos.x;
            pos.z = Hu3DData[model].pos.z;
            ofs = sindf(angle) * 25.0f + 25.0f;
            angle += 2.0f;
            angle = (angle >= 360.0f) ? angle - 360.0f : angle;
            Hu3DModelPosSet(model, pos.x, ofs + pos.y, pos.z);
            HuPrcVSleep();
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B4E4_mstory1);

void func_8010B69C_mstory1(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010B6A4_mstory1);

void func_8010B9C0_mstory1(omObjData *obj, omObjData *target) {
    s16 model[2];
    Vec pos[2];
    Vec rot;
    Vec diff;
    s32 i;

    model[0] = obj->model[1];
    model[1] = target->model[1];
    for (i = 0; i < 2; i++) {
        pos[i].x = Hu3DData[model[i]].pos.x;
        pos[i].y = Hu3DData[model[i]].pos.y;
        pos[i].z = Hu3DData[model[i]].pos.z;
    }
    rot.x = Hu3DData[model[0]].rot.x;
    rot.y = Hu3DData[model[0]].rot.y;
    rot.z = Hu3DData[model[0]].rot.z;
    diff.x = pos[1].x - pos[0].x;
    diff.y = pos[1].y - pos[0].y;
    diff.z = pos[1].z - pos[0].z;
    rot.y = -(atan2df(diff.z, diff.x) - 90.0f);
    Hu3DModelRotSet(model[0], rot.x, rot.y, rot.z);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115038_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_80115050_mstory1);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory1/48C120", D_8011505C_mstory1);

void func_8010BB08_mstory1(s32 index, s32 seNo) {
    if (D_801158F0_mstory1[index].unk_0C == 0) {
        D_801158F0_mstory1[index].unk_0C = 1;
        D_801158F0_mstory1[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                if (func_80106AFC_mstory1(4) == 0) {
                    D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, 4);
                } else {
                    D_801158F0_mstory1[index].unk_14 = CharFXPlay(seNo, 1);
                }
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

void func_8010BBEC_mstory1(s32 index) {
    if (D_801158F0_mstory1[index].unk_0C == 1) {
        D_801158F0_mstory1[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801158F0_mstory1[index].unk_14);
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                break;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory1/48C120", func_8010BC68_mstory1);
