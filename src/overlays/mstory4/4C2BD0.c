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

typedef struct UnkMstory4Work {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ Vec pos;
} UnkMstory4Work; // sizeof 0x10

extern f32 D_800CB890_main;
extern f32 D_800D5210_main;
extern Vec D_80111AD0_mstory4;
extern Vec D_80111ADC_mstory4;
extern Vec D_80111AE8_mstory4;

extern s32 D_80111AC0_mstory4;
extern s32 D_80111AC4_mstory4;
extern s8 D_80111ACC_mstory4;
extern s32 D_80111AF4_mstory4;
extern Vec D_80111DB8_mstory4;
extern Vec D_80111DC4_mstory4;
extern Vec D_80111E78_mstory4;
extern Vec D_80111E84_mstory4;
extern Vec D_80111ECC_mstory4;
extern Vec D_80111EE4_mstory4;
extern s16 D_80112120_mstory4;
extern s16 D_80112122_mstory4;
extern s32 D_80112124_mstory4;
extern u16 D_80112128_mstory4;
extern s32 D_801121B4_mstory4;
extern UnkStoryObj D_801121C0_mstory4[5];
extern u16 D_8011234A_mstory4[2][2];
extern s16 D_80112352_mstory4;
extern const s32 D_80112008_mstory4[8];
extern s16 D_80112358_mstory4[];
extern s16 D_80112366_mstory4;
extern s16 D_80112368_mstory4[];
extern u16 D_80112376_mstory4;
extern UnkStoryObj D_801122A0_mstory4[4];

void MBDBackKill(void);
void MBDBackClose(void);
void func_80106134_mstory4(void);
void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames);
void func_80106DBC_mstory4(omObjData *obj, const Vec *pos, s32 frames, s32 arg3);
void func_8010700C_mstory4(omObjData *obj, Vec *pos, s32 frames, s32 arg3);
void func_801072D8_mstory4(omObjData *obj, Vec *pos, s32 frames);
s32 func_801074F8_mstory4(s16 model);
void func_80108280_mstory4(omObjData *obj);
void func_80109B5C_mstory4(omObjData *object);
void func_8010BAF0_mstory4(omObjData *obj);
void func_8010D1A0_mstory4(omObjData *object);
s16 func_80110394_mstory4(s32 file, s32 flags);
void func_80110528_mstory4(omObjData *obj);
s16 func_801108FC_mstory4(s32 file, s32 flags);
void func_80110E3C_mstory4(void);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801059A0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C18_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80105C90_mstory4);

void func_80105DA8_mstory4(omObjData *obj) {
    if (D_800D530C_main == 1) {
        if (D_80111ACC_mstory4 == 0) {
            if (GwPlayer[0].coin == 0) {
                WipeCreateOut(WIPE_STARS, 20);
            } else {
                WipeCreateOut(WIPE_FADE, 20);
            }
            D_80111ACC_mstory4 = 1;
        } else if (WipeStatGet() == 0) {
            HuWinAllKill();
            if (D_80111AC4_mstory4 == 1) {
                MBDBackKill();
                MBDBackClose();
            }
            SLCommonSet(1);
            omOvlReturnEx(1);
        }
    }
}

void func_80105E58_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    Hu3DMotionTimeSet(D_80112122_mstory4, 0.0f);
    HuAudFXPlay(0x217);
}

void func_80105EAC_mstory4(void) {
    func_8001C814_main(D_80112122_mstory4, 4, 4);
    func_8001C814_main(D_80112122_mstory4, 1, 0);
    Hu3DMotionTimeSet(D_80112122_mstory4, D_800CCF58_main[Hu3DData[D_80112122_mstory4].motId].unk02);
}

void func_80105F40_mstory4(void) {
    D_80112128_mstory4 = espEntry(func_8000B838_main(0x1D0012), 0, 0);
    espPosSet(D_80112128_mstory4, 160, 120);
    espAttrSet(D_80112128_mstory4, 0x4000);
    D_80112122_mstory4 = func_8000B108_main(0x1D0014, 0x2B9);
    Hu3DModelPosSet(D_80112122_mstory4, 591.7f, -81.0f, -1305.7f);
    func_8001C814_main(D_80112122_mstory4, 2, 0);
    func_8001C814_main(D_80112122_mstory4, 1, 1);
}

void func_80106000_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    espDispOff(D_80112128_mstory4);
}

void func_80106034_mstory4(void) {
    func_8001C258_main(D_80112122_mstory4, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    espDispOn(D_80112128_mstory4);
}

void func_80106068_mstory4(void) {
    D_800CE17C_main[0] = D_80111AD0_mstory4.x;
    D_800CE17C_main[1] = D_80111AD0_mstory4.z;
    D_800CE17C_main[-1] = 0.0f;
    D_800CE17C_main[2] = 35.0f;
    D_800CE17C_main[3] = D_800D5210_main;
    D_800CE17C_main[4] = D_800CB890_main;
    Hu3DCameraPosSetV(0, &D_80111AD0_mstory4, &D_80111ADC_mstory4, &D_80111AE8_mstory4);
    Hu3DCamUpdateMtx(0);
}

void func_801060E8_mstory4(void) {
    D_80111AC0_mstory4 = 3;
}

void func_801060F8_mstory4(s32 arg0) {
    D_801121B4_mstory4 = arg0;
    D_80111AF4_mstory4 = 0;
    omAddPrcObj(func_80106134_mstory4, 0x1000, 0x800, 0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106134_mstory4);

s32 func_80106B20_mstory4(void) {
    return D_80111AF4_mstory4;
}

void func_80106B2C_mstory4(void) {
}

void func_80106B34_mstory4(void) {
}

void func_80106B3C_mstory4(s16 model, s16 animSlot, s16 anim) {
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

void func_80106C10_mstory4(void) {
    D_80112120_mstory4 = func_80060880_main(160, 194, 20);
    HuWinActivePlayerSet(D_80112120_mstory4, 1 << D_80112124_mstory4);
    HuWinInsertMesSet(D_80112120_mstory4, GwStory.unk1 + 0x1C00, 0);
}

void func_80106C78_mstory4(void) {
    HuWinHomeClear(D_80112120_mstory4);
    func_80060C14_main(D_80112120_mstory4, 1);
}

void func_80106CA8_mstory4(void) {
    func_80060EA8_main(D_80112120_mstory4, 1);
}

void func_80106CCC_mstory4(s32 mess) {
    HuWinMesSet(D_80112120_mstory4, mess, -1, -1);
    while (HuWinStatGet(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

void func_80106D20_mstory4(s32 mess) {
    HuWinMesSet(D_80112120_mstory4, mess, -1, -1);
}

void func_80106D4C_mstory4(void) {
    while (HuWinStatGet(D_80112120_mstory4) != 0) {
        HuPrcVSleep();
    }
}

s32 func_80106D88_mstory4(s32 character) {
    return -(character == GwStory.unk1);
}

void func_80106DA0_mstory4(omObjData *obj, const Vec *pos, s32 frames) {
    func_80106DBC_mstory4(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80106DBC_mstory4);

void func_80106FF0_mstory4(omObjData *obj, Vec *pos, s32 frames) {
    func_8010700C_mstory4(obj, pos, frames, 1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010700C_mstory4);

void func_80107220_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DA0_mstory4(obj, &pos, frames);
}

void func_8010724C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106DBC_mstory4(obj, &pos, frames, arg3);
}

void func_8010727C_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_80106FF0_mstory4(obj, &pos, frames);
}

void func_801072A8_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames, s32 arg3) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_8010700C_mstory4(obj, &pos, frames, arg3);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801072D8_mstory4);

void func_80107480_mstory4(omObjData *obj, f32 x, f32 y, f32 z, s32 frames) {
    Vec pos;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    func_801072D8_mstory4(obj, &pos, frames);
}

void func_801074AC_mstory4(s16 model) {
    HuPrcSleep(10);
    while (!func_801074F8_mstory4(model)) {
        HuPrcVSleep();
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801074F8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801075B0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801078B4_mstory4);

void func_8010815C_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010818C_mstory4);

void func_80108280_mstory4(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80108288_mstory4);

void func_801086EC_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C50_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C70_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C7C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C88_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111C94_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CA0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CAC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CCC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111CEC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D2C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D38_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801086F4_mstory4);

void func_801093B0_mstory4(omObjData *obj) {
    s16 model = obj->model[1];

    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[10]].motId, 0, 10, 0);
    func_801074AC_mstory4(model);
    HuPrcSleep(80);
    Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 2);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_80109474_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DB8_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

void func_801094A8_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111DC4_mstory4, 10);
    D_801121C0_mstory4[0].func = func_80108280_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D74_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D80_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D8C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111D98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DB0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DC4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801094DC_mstory4);

void func_80109838_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DDC_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80109840_mstory4);

void func_80109AE0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111E84_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111E78_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80109B5C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80109CCC_mstory4);

void func_80109E3C_mstory4(void) {
    HuPrcSleep(5);
    D_801121C0_mstory4[1].func = func_80109B5C_mstory4;
}

void func_80109E68_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 0.0f, 0.0f, 10);
    D_801121C0_mstory4[1].func = func_80108280_mstory4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80109EA4_mstory4);

void func_8010A05C_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111DF4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E0C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E18_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E24_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E30_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E3C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E48_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E54_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E60_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E78_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111E84_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A064_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A1C4_mstory4);

void func_8010A3C8_mstory4(void) {
}

const Vec D_80111EB4_mstory4 = { 700.0f, 0.0f, 150.0f };
const Vec D_80111EC0_mstory4 = { 216.66666f, 0.0f, 150.0f };

void func_8010A3D0_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111ECC_mstory4, 10);
    func_80106DA0_mstory4(obj, &D_80111EB4_mstory4, 50);
    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

void func_8010A44C_mstory4(omObjData *obj) {
    func_801072D8_mstory4(obj, &D_80111EE4_mstory4, 20);
    D_801121C0_mstory4[3].func = func_80108280_mstory4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A480_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A5AC_mstory4);

void func_8010A764_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010A76C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010AA88_mstory4);

void func_8010ABD0_mstory4(s32 index, s32 seNo) {
    if (D_801121C0_mstory4[index].unk_0C == 0) {
        D_801121C0_mstory4[index].unk_0C = 1;
        D_801121C0_mstory4[index].unk_10 = seNo;
        switch (index) {
            case 0:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
                break;
            case 2:
                D_801121C0_mstory4[index].unk_14 = CharFXPlay(seNo, 6);
                break;
        }
    }
}

void func_8010AC84_mstory4(s32 index) {
    if (D_801121C0_mstory4[index].unk_0C == 1) {
        D_801121C0_mstory4[index].unk_0C = 0;
        switch (index) {
            case 0:
            case 2:
                HuAudFXStop((s16)D_801121C0_mstory4[index].unk_14);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010ACF4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010AE20_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B124_mstory4);

void func_8010B9CC_mstory4(MstoryPath *path) {
    HuMemFree(path->intervals);
    HuMemFree(path);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010B9FC_mstory4);

void func_8010BAF0_mstory4(omObjData *obj) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010BAF8_mstory4);

void func_8010BF3C_mstory4(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010BF44_mstory4);

void func_8010C080_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 180.0f, 0.0f, 40);
    D_801122A0_mstory4[0].func = func_8010BAF0_mstory4;
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111ECC_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111EE4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F08_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F10_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F1C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F28_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F34_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F54_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C0BC_mstory4);

void func_8010C54C_mstory4(void) {
}

void func_8010C554_mstory4(omObjData *obj) {
    func_80107480_mstory4(obj, 0.0f, 230.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C590_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C7F8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010C8D0_mstory4);

void func_8010CAE8_mstory4(void) {
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F80_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CAF0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CD40_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CE90_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010CFE0_mstory4);

void func_8010D128_mstory4(void) {
    omObjData *obj = omAddObj(0x14, 0, 0, -1, NULL);

    D_801122A0_mstory4[3].obj = obj;
    D_801122A0_mstory4[3].unk_08 = 0;
    D_801122A0_mstory4[3].unk_0C = 0;
    D_801122A0_mstory4[3].func = func_8010D1A0_mstory4;

    for (;;) {
        D_801122A0_mstory4[3].func(obj);
        HuPrcVSleep();
    }
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111F98_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FA8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FB8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FC8_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010D1A0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010E5C4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010E7C0_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EA34_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010EC38_mstory4);

void func_8010EDA0_mstory4(void) {
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            espDispOff(D_8011234A_mstory4[i][j]);
            espKill(D_8011234A_mstory4[i][j]);
        }
    }
    HuSprAnimKill(D_80112352_mstory4);
}

void func_8010EE3C_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        D_80112358_mstory4[i] = func_8000B838_main(D_80112008_mstory4[i]);
        D_80112368_mstory4[i] = espEntry(D_80112358_mstory4[i], 0, 0);
        espPosSet(D_80112368_mstory4[i], 160, 120);
        espAttrSet(D_80112368_mstory4[i], 0x4000);
        espDispOff(D_80112368_mstory4[i]);
    }
}

void func_8010EF00_mstory4(s32 index) {
    espDispOn(D_80112368_mstory4[index]);
}

void func_8010EF28_mstory4(s32 index) {
    espDispOff(D_80112368_mstory4[index]);
}

void func_8010EF50_mstory4(s32 index, s16 level) {
    espTPLvlSet(D_80112368_mstory4[index], level);
}

void func_8010EF80_mstory4(void) {
    s32 i;

    for (i = 0; i < 8; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
    }
    HuPrcSleep(3);
}

void func_8010F010_mstory4(void) {
    s32 i;

    for (i = 0; i < 7; i++) {
        espDispOff(D_80112368_mstory4[i]);
        espKill(D_80112368_mstory4[i]);
        HuSprAnimKill(D_80112358_mstory4[i]);
        HuPrcSleep(3);
    }
}

void func_8010F0A0_mstory4(void) {
    u16 *espriteSlot = &D_80112376_mstory4;
    s16 *sprite = &D_80112366_mstory4;

    espDispOff(*espriteSlot);
    espKill(*espriteSlot);
    HuSprAnimKill(*sprite);
}

void func_8010F0E0_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void func_8010F12C_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[0].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
}

void func_8010F178_mstory4(void) {
    omObjData *obj = D_801122A0_mstory4[1].obj;

    func_8001C258_main(obj->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    func_8001C258_main(obj->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->model[1]);
    Hu3DModelKill(obj->model[3]);
    Hu3DModelKill(obj->model[4]);
    Hu3DModelKill(obj->model[5]);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80111FF8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112008_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F1F4_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F588_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F660_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_8010F910_mstory4);

void func_800E4F50_name_81(u8 *);
void MBDBackCreate(s32, s32);                                /* extern */
void func_8010E5C4_mstory4(void *, f32, f32, f32, s32, s32); /* extern */
void func_8010EF28_mstory4(s32);                             /* extern */
void func_8010F0A0_mstory4(void);                            /* extern */
void func_8010F12C_mstory4(void);                            /* extern */
void func_80110270_mstory4(void);                            /* extern */
void func_80110DB0_mstory4(f32, f32, f32, s16);              /* extern */
void func_801118F8_mstory4(s32, s32);                        /* extern */
void func_8011196C_mstory4(s32);                             /* extern */
extern Addr D_128CC60;

extern s32 D_80111B8C_mstory4;

typedef struct Unk {
    s16 unk_00;
    char unk_02[6];
} Unk; // sizeof 0x8

extern const Unk D_80112088_mstory4[6];

extern s16 D_80112330_mstory4;
extern s16 D_80112378_mstory4[];
extern s16 D_801123A4_mstory4;

void func_8010FC98_mstory4(void) {
    omObjData *temp_s5;
    omObjData *temp_s7;
    s32 var_s3;
    u16 temp_fp;
    s32 i, j;

    temp_s5 = D_801122A0_mstory4[0].obj;
    temp_s7 = D_801122A0_mstory4[1].obj;
    temp_fp = temp_s5->model[1];
    Hu3DCameraPerspectiveSet(0, 40.0f, 80.0f, 8000.0f);

    D_80111AD0_mstory4.x = 0.0f;
    D_80111AD0_mstory4.y = 190.0f;
    D_80111AD0_mstory4.z = 3770.0f;

    D_80111ADC_mstory4.x = 0.0f;
    D_80111ADC_mstory4.y = 130.0f;
    D_80111ADC_mstory4.z = 450.0f;

    D_80111AC4_mstory4 = 1;
    var_s3 = 0;
    func_800E4F50_name_81(hvq_data_ROM_START);
    MBDBackCreate(0x20, 0);
    func_8010EF28_mstory4(7);
    for (i = 0; i < 6; i++) {
        for (j = 0; j < D_80112088_mstory4[i].unk_00; var_s3++, j++) {
            espBankSet(D_80112378_mstory4[var_s3], 0, 0);
            func_8000BDDC_main(D_80112378_mstory4[var_s3], 1);
            espDispOff(D_80112378_mstory4[var_s3]);
            espKill(D_80112378_mstory4[var_s3]);
        }
    }

    HuSprAnimKill(D_801123A4_mstory4);
    func_8010F12C_mstory4();
    func_8001C5B4_main(temp_s5->model[1], temp_s5->motion[13]);
    func_8001C814_main(temp_s5->model[1], 2, 2);
    Hu3DModelPosSet(temp_s5->model[1], 0.0f, 0.0f, 2220.0f);
    Hu3DModelPosSet(temp_s5->model[2], 0.0f, -5.0f, 2220.0f);
    Hu3DModelRotSet(temp_s5->model[1], 0, 0, 0);
    Hu3DModelScaleSet(temp_s5->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DModelScaleSet(temp_s5->model[2], 1.5f, 1.5f, 1.5f);
    HuPrcVSleep();
    func_8010F0A0_mstory4();
    HuPrcSleep(30);
    func_8001C258_main(temp_s7->model[6], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DModelPosSet(temp_s7->model[6], 0.0f, 1000.0f, 2120.0f);
    Hu3DModelRotSet(temp_s7->model[6], 0, 0, 0);
    Hu3DModelScaleSet(temp_s7->model[6], 1.5f, 1.5f, 1.5f);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2120.0f, 0x3C, 0);
    D_80111B8C_mstory4 = 0;
    HuPrcSleep(20);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 180.0f, 0.0f, 8);
    HuPrcSleep(20);
    func_80106C78_mstory4();
    func_80106CCC_mstory4(0x5A7E);
    func_80106CA8_mstory4();
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[4]].motId, 0, 0xA, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    func_80107480_mstory4(temp_s5, 0.0f, 0.0f, 0.0f, 0xA);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[11]].motId, 0, 0xA, 2);
    func_801118F8_mstory4(0, 0x1F);
    func_8010724C_mstory4(temp_s5, 0.0f, 0.0f, 2930.0f, 0x28, 0);
    func_8011196C_mstory4(0);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[0]].motId, 0, 0xA, 2);
    HuPrcSleep(20);
    CharFXPlay(0x2C6, GwStory.unk1);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[2]].motId, 0, 0xA, 0);
    func_80017954_main(temp_fp, 2, GwStory.unk1, D_80112330_mstory4);
    func_8010E5C4_mstory4(temp_s7, 0.0f, 400.0f, 2500.0f, 0x14, 0);
    func_801074AC_mstory4(temp_fp);
    Hu3DMotionShiftSet(temp_fp, Hu3DData[temp_s5->motion[3]].motId, 0, 0xA, 2);
    func_80110270_mstory4();
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        func_80110DB0_mstory4(0.0f, 400.0f, 2500.0f, i << 3);
        HuPrcSleep(2);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110270_mstory4);

s16 func_80110394_mstory4(s32 file, s32 flags) {
    omObjData *obj;
    HmfModelData_UnkBC_Struct *effect;
    s16 model;

    obj = omAddObj(1000, 0, 0, -1, func_80110528_mstory4);
    obj->work[0] = model = func_801108FC_mstory4(file, flags);
    effect = Hu3DData[model].unkBC;
    effect->unk1C.f = effect->unk20.f = effect->unk24.f = 0.0f;
    effect->unk04 |= 1;
    effect->unk10.f = 100.0f;
    effect->unk14 = -1.0f;
    return model;
}

void func_80110460_mstory4(s16 modelId, s32 x, s32 y, s32 z) {
    HmfModelData_UnkBC_Struct *model = Hu3DData[modelId].unkBC;
    model->unk1C.i = x;
    model->unk20.i = y;
    model->unk24.i = z;
}

void func_80110494_mstory4(s16 modelId, s16 value) {
    Hu3DData[modelId].unkBC->unk14 = value;
}

void func_801104D4_mstory4(s16 modelId, s32 value) {
    Hu3DData[modelId].unkBC->unk10.i = value;
}

void func_80110500_mstory4(s16 model) {
    func_800138EC_main(model, 5, 4);
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110528_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110724_mstory4);

void func_80110888_mstory4(s16 modelId, s32 x, s32 y, f32 z) {
    HmfData *hmf = Hu3DData[modelId].hmf;
    HmfModelData_UnkBC_Struct *unkBC = Hu3DData[modelId].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *entry = unkBC->unk58;
    s16 i;

    unkBC->unk08.i = x;
    unkBC->unk0C.i = y;
    for (i = 0; i < hmf->unk1A; i++) {
        entry->unk1C = -z;
        entry++;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801108FC_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801109EC_mstory4);

s16 func_80110B4C_mstory4(s32 dataNum, s32 attr) {
    s16 model = func_8000B108_main(dataNum, attr);

    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    func_8001C2FC_main(model, 0x20000, 0x20000);
    Hu3DModelRemakeStatic(model);
    func_8001C954_main(model);
    func_8001C514_main(model);
    return model;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110BB4_mstory4);

void func_80110D5C_mstory4(omObjData *obj) {
    HuPrcSleep(30);
    func_80107480_mstory4(obj, -30.0f, -45.0f, 0.0f, 30);
    D_801122A0_mstory4[1].func = func_8010BAF0_mstory4;
}

void func_80110DB0_mstory4(f32 x, f32 y, f32 z, s16 arg3) {
    Process *process = omAddPrcObj(func_80110E3C_mstory4, 0x3F00, 0x2000, 0);
    UnkMstory4Work *work = HuMemAllocTag(sizeof(UnkMstory4Work), 0x7918);

    process->user_data = work;
    work->pos.x = x;
    work->pos.y = y;
    work->pos.z = z;
    work->unk_02 = arg3;
    work->unk_00 = 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80110E3C_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80111430_mstory4);

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_80111740_mstory4);

void func_801118F8_mstory4(s32 index, s32 seNo) {
    if (D_801122A0_mstory4[index].unk_0C == 0) {
        D_801122A0_mstory4[index].unk_0C = 1;
        D_801122A0_mstory4[index].unk_10 = seNo;
        if (index == 0) {
            D_801122A0_mstory4[index].unk_14 = CharFXPlay(seNo, GwStory.unk1);
        }
    }
}

void func_8011196C_mstory4(s32 index) {
    if (D_801122A0_mstory4[index].unk_0C == 1) {
        D_801122A0_mstory4[index].unk_0C = 0;
        if (index == 0) {
            HuAudFXStop((s16)D_801122A0_mstory4[0].unk_14);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mstory4/4C2BD0", func_801119C0_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112088_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_8011208C_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120B8_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120D4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_801120F4_mstory4);

INCLUDE_RODATA("asm/nonmatchings/overlays/mstory4/4C2BD0", D_80112114_mstory4);
