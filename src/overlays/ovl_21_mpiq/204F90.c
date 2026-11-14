#include "common.h"
#include "math.h"
#include "game/printfunc.h"
#include "game/mallocblock.h"
#include "game/messdata.h"
#include "game/esprite.h"
#include "game/audio.h"
#include "game/gamemes.h"
#include "gcc/memory.h"
#include "game/window.h"
#include "overlays/minigame.h"

// Per-player work for each of the four quads, allocated in func_80107584_mpiq
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ u32 flags;
    /* 0x14 */ s32 timer;
    /* 0x18 */ s32 index;
    /* 0x1C */ f32 scale;
    /* 0x20 */ s32 counter;
    /* 0x24 */ s16 unk_24;
} MpiqObjWork; // Size 0x28

typedef struct {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 rotY;
    /* 0x0C */ s32 flags;
} MpiqDanceObjData; // Size 0x10

// CPU input timing for each player, set up in func_80106664_mpiq
typedef struct {
    /* 0x00 */ s32 delay;
    /* 0x04 */ s32 hold;
    /* 0x08 */ u16 button;
} MpiqCpuInput; // Size 0xC

// Data of the objects registered in D_800EC1C0_minigame
typedef struct {
    /* 0x00 */ D_800EC1C0_minigame_ObjData header;
    /* 0xB0 */ void *unkB0;
} MpiqStageData; // Size 0xB4

// Work for the meter objects created in func_80108178_mpiq
typedef struct {
    /* 0x00 */ char unk_00[8];
    /* 0x08 */ f32 x;
    /* 0x0C */ char unk_0C[0xC];
    /* 0x18 */ f32 posY[4]; // [0] is the base model, [1..3] are the bars
    /* 0x28 */ f32 barScale[3];
    /* 0x34 */ char unk_34[4];
    /* 0x38 */ s32 stage;
    /* 0x3C */ s32 flags;
    /* 0x40 */ s32 index;
} MpiqMeterWork; // Size 0x44

// Work for the sign object created in func_80108B74_mpiq
typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ s32 flags;
    /* 0x0C */ f32 scale;
} MpiqSignWork; // Size 0x10

// Work for the marker object created in func_80107F28_mpiq
typedef struct {
    /* 0x00 */ s32 flags;
    /* 0x04 */ s32 timer;
} MpiqMarkerObjWork; // Size 0x8

extern s32 D_8010CA90_mpiq[];
extern s32 D_8010CAA0_mpiq[];
extern omObjData *D_8010CA78_mpiq;
extern omObjData *D_8010CAC0_mpiq[];
extern omObjData *D_8010CA80_mpiq[];
extern f32 D_8010CAB0_mpiq[];
extern omObjData *D_8010CAD0_mpiq;
extern omObjData *D_8010CAD4_mpiq;
extern omObjData *D_8010CAD8_mpiq[];
extern omObjData *D_8010CAE8_mpiq;
extern s32 D_8010CAF8_mpiq;
extern s16 D_8010CAFA_mpiq;
extern s16 D_8010CAFC_mpiq;
extern u16 D_8010CAEC_mpiq[3];
extern s16 D_8010CAF2_mpiq[3];
extern s32 D_8010C9D8_mpiq;
extern s32 D_8010C6B8_mpiq;
extern MpiqCpuInput D_8010CA08_mpiq[];
extern s16 D_8010CA38_mpiq[];
extern s16 D_8010CA4C_mpiq;
extern s32 D_8010CA50_mpiq[];
extern s32 D_8010CB00_mpiq[][4];
extern s16 D_8010CBA0_mpiq[];
extern s16 D_8010CBB8_mpiq[];
extern s32 D_8010CC04_mpiq;
extern s32 D_8010CC10_mpiq[256];
extern s32 D_8010C6BC_mpiq[];
extern s32 D_8010CBCC_mpiq;
extern s32 D_8010CBD0_mpiq[];
extern s32 D_8010CBF8_mpiq[];
extern s32 D_8010CBFC_mpiq[];
extern s32 D_8010D010_mpiq;
extern s32 D_800A178C_main[][6];
extern u8 D_800D6A90_main;
extern f32 D_8010C6A8_mpiq[];
extern s32 D_8010C9C8_mpiq[];
extern s32 D_8010C9E8_mpiq[];
extern D_80111B50_vine_with_me_Struct D_8010C680_mpiq;
extern f32 D_8010C9B0_mpiq;
extern s32 D_8010C9B4_mpiq;
extern u8 D_8010C9B8_mpiq;
extern s32 D_8010C9BC_mpiq;
extern s16 D_8010C9BE_mpiq;
extern s16 D_8010C9C0_mpiq;
extern s16 D_8010C9BA_mpiq;
extern s16 D_8010C9C2_mpiq;
extern u16 D_8010C9DC_mpiq[2];
extern u16 D_8010C9E0_mpiq;
extern u16 D_8010C9E2_mpiq;
extern s32 D_8010C9F8_mpiq;
extern s32 D_8010C9FC_mpiq;
extern s16 D_8010CA00_mpiq;
extern s32 D_8010D020_mpiq;

void func_80105C60_mpiq(omObjData *obj);
void func_80105D60_mpiq(omObjData *obj);
void func_80105DA4_mpiq(omObjData *obj);
void func_80105DC0_mpiq(omObjData *obj);
void func_80105DDC_mpiq(omObjData *obj);
void func_80105DF8_mpiq(omObjData *obj);
void func_80105E14_mpiq(omObjData *obj, s32 index);
void func_8010651C_mpiq(omObjData *obj);
s32 func_80106658_mpiq(void);
void func_80106B5C_mpiq(void);
void func_80107114_mpiq(void);
void func_80106E98_mpiq(void);
void func_8010720C_mpiq(void);
void func_8010747C_mpiq(omObjData *obj);
void func_80107584_mpiq(void);
void func_80107774_mpiq(omObjData *obj);
void func_80107D70_mpiq(void);
void func_80107DE0_mpiq(omObjData *obj);
void func_80107E90_mpiq(f32 x, f32 y, f32 z);
void func_80107F28_mpiq(void);
void func_80107FC4_mpiq(omObjData *obj);
void func_80108178_mpiq(void);
void func_80108494_mpiq(omObjData *obj);
void func_80108688_mpiq(void);
void func_801087F8_mpiq(omObjData *obj);
void func_80108A3C_mpiq(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ);
void func_80108B74_mpiq(void);
s16 func_801089D0_mpiq(omObjData *objA, omObjData *objB);
void func_80108D10_mpiq(void);
void func_80108E20_mpiq(omObjData *obj);
void func_80109018_mpiq(void);
void func_80109414_mpiq(void);
s32 func_8010C4C0_mpiq(s32 index);
s32 func_801096C0_mpiq(s32 index, s32 question);
void func_8010A010_mpiq(s32 index);
void func_8010A184_mpiq(s32 index);
s16 func_8010AB44_mpiq(s32 index, s32 answer);
s32 func_8010AEDC_mpiq(s32 index);
s32 func_8010AFAC_mpiq(s32 index, s32 range, s32 base, s32 scale);
void func_8010B0CC_mpiq(void);
void func_8010C5B8_mpiq(omObjData *obj);
s16 func_8010BB74_mpiq(void);
void func_8010C2F0_mpiq(void);
void func_8010BA64_mpiq(omObjData *obj);
s16 func_8010BD1C_mpiq(void);

void func_801059A0_mpiq(void) {
    omObjData *obj;

    omInitObjMan(40, 20);
    func_8001FE20_main(16);
    func_80021BE0_main(&D_800EBEB0_minigame, 64);
    func_800142A0_main(64);
    func_80045C2C_main();
    func_8004A208_main();
    obj = omAddObj(0x7FDA, 0, 0, -1, omOutView);
    omSetStatBit(obj, 0xA0);
    func_80108A3C_mpiq(2000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 420.0f, 0.0f);
    omOutView(obj);
    Hu3DBGColorSet(0, 0, 0);
    func_800E5EA0_minigame(&D_8010C680_mpiq);
    WipeCreateIn(0xFF, 16);
    D_800EBE28_minigame = 0;
    D_800EC280_minigame = 0;
    func_800E18D8_minigame();
    D_800EB774_minigame = 1.0f;
    D_8010C9F8_mpiq = 0;
    D_8010D020_mpiq = 58;
    func_800E19F0_minigame(1);
    HuWinInit();
    func_80106B5C_mpiq();
    func_8010720C_mpiq();
    D_8010CA00_mpiq = -1;
    omSetStatBit(omAddObj(0x5000, 0, 0, -1, func_8010C5B8_mpiq), 0xA0);
    omAddObj(4, 10, 60, -1, func_80105DA4_mpiq);
    omAddObj(4, 10, 60, -1, func_80105DC0_mpiq);
    omAddObj(4, 10, 60, -1, func_80105DDC_mpiq);
    omAddObj(4, 10, 60, -1, func_80105DF8_mpiq);
    D_8010C9C2_mpiq = 1;
    func_80108B74_mpiq();
    D_8010C9FC_mpiq = 0;
    func_80109414_mpiq();
    omAddPrcObj(func_8010B0CC_mpiq, 0x5000, 0x1000, 0);
    func_80108688_mpiq();
    func_80108178_mpiq();
    omAddPrcObj(func_80106E98_mpiq, 0x4700, 0x1000, 0);
    omAddObj(0x5000, 0, 0, -1, func_80105C60_mpiq);
    func_80107584_mpiq();
    func_80107D70_mpiq();
    func_80107F28_mpiq();
    D_8010C9B8_mpiq = 0;
    D_8010C9BA_mpiq = 0;
    D_800EBE24_minigame = 0;
    D_800EB930_minigame = 49;
    D_800EB932_minigame = 60;
}

void func_80105C60_mpiq(omObjData *obj) {
    if (D_800D530C_main != 0) {
        HuAudFXAllStop();
        HuAudSeqFadeOut(30);
        WipeCreateOut(WIPE_TYPE_NORMAL, 20);
    }
    switch (func_800E6F40_minigame(obj)) {
        case 0:
        case 1:
        case 2:
        case 4:
            break;
        case 3:
            if (D_8010C9D8_mpiq != -1) {
                D_8010C680_mpiq.unk06 = 0;
                D_8010C680_mpiq.unk18[0] = D_8010C9D8_mpiq;
            } else {
                D_8010C680_mpiq.unk06 = 4;
            }
            break;
        case 5:
            if (D_8010C9D8_mpiq != -1) {
                GwPlayer[D_8010C9D8_mpiq].bonusCoin += 10;
            }
            WipeCreateOut(WIPE_TYPE_NORMAL, 20);
            obj->func = func_80105D60_mpiq;
            break;
    }
}

void func_80105D60_mpiq(omObjData *obj) {
    if (WipeStatGet() == 0) {
        HuWinAllKill();
        GMesClose();
        HuSprAnimAllKill();
        omOvlReturnEx(1);
    }
}

void func_80105DA4_mpiq(omObjData *obj) {
    func_80105E14_mpiq(obj, 0);
}

void func_80105DC0_mpiq(omObjData *obj) {
    func_80105E14_mpiq(obj, 1);
}

void func_80105DDC_mpiq(omObjData *obj) {
    func_80105E14_mpiq(obj, 2);
}

void func_80105DF8_mpiq(omObjData *obj) {
    func_80105E14_mpiq(obj, 3);
}

void func_80105E14_mpiq(omObjData *obj, s32 index) {
    Vec2f screenPos;
    Vec pos;
    s32 motion0[8] = { 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B, 0x9B };
    s32 motion1[8] = { 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B };
    s32 motion2[8] = { 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F };
    s32 motion3[8] = { 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37, 0x37 };
    s32 motion4[8] = { 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F, 0x2F };
    s32 motion5[8] = { 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C };
    s32 motion6[8] = { 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D, 0x2D };
    s32 motion7[8] = { 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E, 0x2E };
    s32 motion8[8] = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };
    s32 motion9[8] = { 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A };
    s32 motion10[8] = { 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15, 0x15 };
    s32 motion11[8] = { 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23 };
    func_800E1BA8_minigame_ObjData *data;
    s32 chr;
    s32 model;
    s32 motion;
    s32 attr1;
    s32 attr2;

    D_800EC598_minigame[D_800EC280_minigame++] = obj;
    model = D_800A178C_main[GwPlayer[index].chr][0];
    motion = D_800A178C_main[GwPlayer[index].chr][1];
    attr1 = 0x20AB9;
    attr2 = 0x20A99;
    func_800E1BA8_minigame(obj, model, motion, index, attr1, attr2);
    data = obj->data;
    chr = GwPlayer[index].chr;
    func_800E5A00_minigame(obj, 0, func_80017BB8_main(chr, motion0[chr]), 1, 0);
    func_800E5A00_minigame(obj, 6, func_80017BB8_main(chr, motion1[chr]), 1, 19);
    func_800E5A00_minigame(obj, 21, func_80017BB8_main(chr, motion2[chr]), 0, 0);
    func_800E5A00_minigame(obj, 14, func_80017BB8_main(chr, motion3[chr]), 1, 120);
    func_800E5A00_minigame(obj, 13, func_80017BB8_main(chr, motion4[chr]), 1, 120);
    func_800E5A00_minigame(obj, 38, func_80017BB8_main(chr, motion5[chr]), 0, 0);
    func_800E5A00_minigame(obj, 39, func_80017BB8_main(chr, motion6[chr]), 0, 0);
    func_800E5A00_minigame(obj, 40, func_80017BB8_main(chr, motion7[chr]), 0, 0);
    func_800E5A00_minigame(obj, 41, func_80017BB8_main(chr, motion8[chr]), 0, 0);
    func_800E5A00_minigame(obj, 42, func_80017BB8_main(chr, motion9[chr]), 0, 0);
    func_800E5A00_minigame(obj, 43, func_80017BB8_main(chr, motion10[chr]), 1, 0);
    func_800E5A00_minigame(obj, 33, func_80017BB8_main(chr, motion11[chr]), 1, 0);
    screenPos.x = D_8010C6A8_mpiq[index];
    screenPos.y = 180.0f;
    Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
    omSetTra(obj, pos.x, 0.0f, 0.0f);
    obj->trans.x = pos.x;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    obj->rot.y = 180.0f;
    func_800E149C_minigame(obj, 0, 1);
    func_800E149C_minigame(obj, 1, 2);
    func_800E149C_minigame(obj, 2, 2);
    func_800E149C_minigame(obj, 3, 2);
    func_800E149C_minigame(obj, 4, 2);
    func_800E5690_minigame(obj, 0);
    D_8010C9C8_mpiq[index] = 0;
    D_8010C9E8_mpiq[index] = 0;
    data->unk104[2] = func_80106658_mpiq;
    obj->func = func_8010651C_mpiq;
}

void func_8010651C_mpiq(omObjData *obj) {
    func_800E1BA8_minigame_ObjData *data = obj->data;
    f32 x = obj->trans.x;
    f32 z = obj->trans.z;

    D_800CBB6E_main[data->unk57] = 0;
    D_800D20A1_main[data->unk57] = 0;
    if (D_8010C9E8_mpiq[data->unk59] & 1) {
        D_800CDA7C_main[data->unk57] = 0;
        D_800D5558_main[data->unk57] = 0;
    }
    if (D_8010C9C2_mpiq == 1 && !(GwPlayer[data->unk59].stat & 1)) {
        D_800CDA7C_main[data->unk57] &= 0x7FFF;
        D_800D5558_main[data->unk57] &= 0x7FFF;
    }
    func_800DDD94_minigame(obj);
    data->unk60 = 0;
    obj->trans.x = x;
    obj->trans.z = z;
}

s32 func_80106658_mpiq(void) {
    return D_8010C9C2_mpiq;
}

void func_80106664_mpiq(s32 index) {
    u16 buttons[3] = { 0x8000, 0x4000, 0x2000 };
    s32 offset;
    s32 holdRange;
    s32 holdBase;
    s32 accuracy;
    void *mes;
    s32 base;
    s32 choice;
    s32 range;

    accuracy = 0;
    mes = func_800364DC_main((void *)D_8010CA50_mpiq[D_8010CA4C_mpiq]);
    base = func_8005B5EC_main(mes) * 5 - 40;
    holdBase = 0;
    holdRange = 0;
    offset = 0;
    range = 0;
    D_8010CA08_mpiq[index].button = 0;
    switch (GwPlayer[index].cpu_difficulty) {
        case 0:
            range = 60;
            offset = 90;
            holdRange = 2;
            holdBase = 8;
            accuracy = 1;
            break;
        case 1:
            range = 75;
            offset = 60;
            holdRange = 6;
            holdBase = 4;
            accuracy = 3;
            break;
        case 2:
            range = 90;
            offset = 30;
            holdRange = 8;
            holdBase = 2;
            accuracy = 5;
            break;
        case 3:
            range = 105;
            offset = 0;
            holdRange = 9;
            holdBase = 1;
            accuracy = 8;
            break;
    }
    D_8010CA08_mpiq[index].delay = base + offset + (rand8() % (range + 1) - (range >> 1));
    if (D_8010CA08_mpiq[index].delay <= 30) {
        D_8010CA08_mpiq[index].delay = 30;
    }
    D_8010CA08_mpiq[index].hold = (rand8() % holdRange + holdBase) * 10;
    if ((u8)(rand8() % 10) == 0 ? accuracy >= 2 : accuracy > 0) {
        D_8010CA08_mpiq[index].button = buttons[D_8010CA38_mpiq[D_8010CA4C_mpiq]];
    } else {
        choice = (u8)(rand8() % 3);
        if (choice == D_8010CA38_mpiq[D_8010CA4C_mpiq]) {
            choice = (choice + 1) % 3;
        }
        D_8010CA08_mpiq[index].button = buttons[choice];
    }
    func_800365E8_main(mes);
}

void func_801069F8_mpiq(s32 index) {
    func_800E1BA8_minigame_ObjData *data = D_800EC598_minigame[index]->data;

    if (D_8010C9E8_mpiq[index] & 1) {
        return;
    }
    if (D_8010C9C2_mpiq == 0 && D_8010CA08_mpiq[index].delay != 0) {
        D_8010CA08_mpiq[index].delay--;
        if (D_8010CA08_mpiq[index].delay == 0) {
            D_800CDA7C_main[data->unk57] |= 0x8000;
            D_800D5558_main[data->unk57] |= 0x8000;
        }
    } else if (index == D_8010C9BC_mpiq && D_8010CA08_mpiq[index].hold != 0) {
        D_8010CA08_mpiq[index].hold--;
        if (D_8010CA08_mpiq[index].hold == 0) {
            D_800CDA7C_main[data->unk57] |= D_8010CA08_mpiq[index].button;
            D_800D5558_main[data->unk57] |= D_8010CA08_mpiq[index].button;
        }
    }
}

void func_80106B5C_mpiq(void) {
    omObjData *obj;
    MpiqStageData *work;
    u16 sprite;

    obj = omAddObj(5, 2, 0, -1, NULL);
    work = HuMemAllocTag(sizeof(MpiqStageData), TAG_OVERLAY);
    obj->data = work;
    obj->model[0] = 0;
    D_8010C9B0_mpiq = 1.0f;
    obj->trans.x = 0.0f;
    obj->trans.y = 0.0f;
    obj->trans.z = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = obj;
    memset(obj->data, 0, sizeof(MpiqStageData));
    work->header.unk03 = 1;
    work->header.unk08 = 0.5f;
    work->header.unk04 = 0;

    sprite = espEntry(func_8000B838_main(0x420000), 0, 1);
    espAttrSet(sprite, 0x4008);
    espPosSet(sprite, 160, 120);
    espDispOn(sprite);
    espScaleSet(sprite, 1.0f, 1.0f);
    espPriSet(sprite, 255);

    D_8010C9DC_mpiq[0] = espEntry(func_8000B838_main(0x42000C), 0, 1);
    espAttrSet(D_8010C9DC_mpiq[0], 0x4008);
    espPosSet(D_8010C9DC_mpiq[0], 158, 86);
    espDispOff(D_8010C9DC_mpiq[0]);
    espScaleSet(D_8010C9DC_mpiq[0], 1.0f, 1.0f);
    espPriSet(D_8010C9DC_mpiq[0], 3);

    D_8010C9DC_mpiq[1] = espEntry(func_8000B838_main(0x42000D), 0, 1);
    espAttrSet(D_8010C9DC_mpiq[1], 0x4008);
    espPosSet(D_8010C9DC_mpiq[1], 158, 86);
    espDispOff(D_8010C9DC_mpiq[1]);
    espScaleSet(D_8010C9DC_mpiq[1], 1.0f, 1.0f);
    espPriSet(D_8010C9DC_mpiq[1], 3);

    D_8010C9E0_mpiq = espEntry(func_8000B838_main(0x420001), 0, 1);
    espAttrSet(D_8010C9E0_mpiq, 0x4008);
    espPosSet(D_8010C9E0_mpiq, 160, -90);
    espDispOn(D_8010C9E0_mpiq);
    espScaleSet(D_8010C9E0_mpiq, 1.0f, 1.0f);
    espPriSet(D_8010C9E0_mpiq, 254);

    D_8010C9E2_mpiq = espEntry(func_8000B838_main(0x420002), 0, 1);
    espAttrSet(D_8010C9E2_mpiq, 0x4008);
    espPosSet(D_8010C9E2_mpiq, 160, -90);
    espDispOn(D_8010C9E2_mpiq);
    espScaleSet(D_8010C9E2_mpiq, 1.0f, 1.0f);
    espTPLvlSet(D_8010C9E2_mpiq, 230);
    espPriSet(D_8010C9E2_mpiq, 255);

    func_80107114_mpiq();
    obj->func = NULL;
}

void func_80106E98_mpiq(void) {
    Vec2f screenPos;
    Vec pos;
    s32 i;
    s32 offset;

    HuPrcSleep(15);
    HuAudFXPlay(0x413);
    for (i = 0; i < 30; i++) {
        screenPos.x = 260.0f;
        screenPos.y = (i - 30.0f) * 4.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        D_8010CA78_mpiq->trans.y = pos.y;
        offset = (30 - i) * 6;
        espPosSet(D_8010C9E0_mpiq, 160, 90 - offset);
        espPosSet(D_8010C9E2_mpiq, 158, 82 - offset);
        HuPrcVSleep();
    }
    espPosSet(D_8010C9E0_mpiq, 160, 84);
    espPosSet(D_8010C9E2_mpiq, 158, 78);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 94);
    espPosSet(D_8010C9E2_mpiq, 158, 88);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 88);
    espPosSet(D_8010C9E2_mpiq, 158, 82);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 92);
    espPosSet(D_8010C9E2_mpiq, 158, 86);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 89);
    espPosSet(D_8010C9E2_mpiq, 158, 83);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 91);
    espPosSet(D_8010C9E2_mpiq, 158, 85);
    HuPrcVSleep();
    espPosSet(D_8010C9E0_mpiq, 160, 90);
    espPosSet(D_8010C9E2_mpiq, 158, 84);
    omDelPrcObj(NULL);
}

void func_80107168_mpiq(omObjData *obj);

void func_80107114_mpiq(void) {
    omObjData *obj = omAddObj(5, 0, 0, -1, func_80107168_mpiq);
    f32 *angle = HuMemAllocTag(sizeof(f32), TAG_OVERLAY);

    obj->data = angle;
    *angle = 0.0f;
}

void func_80107168_mpiq(omObjData *obj) {
    f32 *angle = obj->data;
    f32 scale = sindf(*angle) * 0.02f + 1.02;

    espScaleSet(D_8010C9E0_mpiq, scale, scale);
    *angle += 5.0f;
    if (*angle >= 360.0f) {
        *angle -= 360.0f;
    }
}

void func_8010720C_mpiq(void) {
    Vec2f screenPos;
    Vec pos;
    f32 heights[3] = { 47.0f, 94.0f, 141.0f };
    omObjData *obj;
    MpiqStageData *work;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 2, 0, -1, func_8010747C_mpiq);
        obj->data = HuMemAllocTag(sizeof(MpiqStageData), TAG_OVERLAY);
        D_8010CA80_mpiq[i] = obj;
        work = obj->data;
        work->unkB0 = HuMemAllocTag(0x14, TAG_OVERLAY);
        if (i == 0) {
            obj->model[0] = func_8000B0A0_main(0x42000E, 0x29D);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CA80_mpiq[0]->model[0]);
        }
        D_8010C9B0_mpiq = 1.0f;
        screenPos.x = D_8010C6A8_mpiq[i];
        screenPos.y = 180.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, 0.0f, 0.0f);
        D_800EC1C0_minigame[D_800EBE28_minigame++] = obj;
        memset(obj->data, 0, sizeof(MpiqStageData));
        work->header.unk03 = 1;
        work->header.unk08 = 0.5f;
        work->header.unk04 = i + 1;
        func_800E13CC_minigame(obj, 0.0f, 100.0f, -100.0f, -100.0f, 100.0f, 100.0f);
        D_8010CA90_mpiq[i] = 0;
        D_8010CAA0_mpiq[i] = 0;
    }
    for (j = 0; j < 3; j++) {
        D_8010CAB0_mpiq[j] = heights[j];
    }
    obj->func = func_8010747C_mpiq;
}

void func_8010747C_mpiq(omObjData *obj) {
    MpiqObjWork *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == D_8010CA80_mpiq[i]) {
            break;
        }
    }
    if (D_8010CA90_mpiq[i] & 1) {
        obj->trans.y += 4.7f;
        work = D_8010CAC0_mpiq[i]->data;
        work->y += 4.7f;
        if (obj->trans.y >= D_8010CAB0_mpiq[D_8010CAA0_mpiq[i] - 1]) {
            obj->trans.y = D_8010CAB0_mpiq[D_8010CAA0_mpiq[i] - 1];
            work->unk_0C = work->y;
            D_8010CA90_mpiq[i] &= ~1;
        }
    }
}

void func_80107558_mpiq(s32 index, s32 value) {
    D_8010CAA0_mpiq[index] = value;
    D_8010CA90_mpiq[index] |= 1;
}

void func_80107584_mpiq(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *obj;
    MpiqObjWork *work;
    s32 i;
    s32 attr = 0x699;
    s32 attr2 = 0xA89;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(10, 3, 0, -1, func_80107774_mpiq);
        D_8010CAC0_mpiq[i] = obj;
        obj->data = HuMemAllocTag(sizeof(MpiqObjWork), TAG_OVERLAY);
        work = obj->data;
        if (i == 0) {
            obj->model[0] = func_8000B0A0_main(0x42000B, attr);
            obj->model[1] = func_8000B0A0_main(0x42000F, attr2 | 4);
            func_8001FA68_main(obj->model[1]);
            obj->model[2] = func_8000B108_main(0x5D0008, attr | 4);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[0]);
            obj->model[1] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[1]);
            obj->model[2] = Hu3DModelLink(D_8010CAC0_mpiq[0]->model[2]);
        }
        func_8001C814_main(obj->model[0], 1, 1);
        screenPos.x = D_8010C6A8_mpiq[i];
        screenPos.y = 52.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, pos.y, 0.0f);
        work->x = pos.x;
        work->y = pos.y;
        work->unk_0C = pos.y;
        work->flags = 0;
        work->unk_08 = 0.0f;
        work->index = i;
        work->unk_24 = 0;
        Hu3DModelPosSet(obj->model[1], work->x, work->y, 0.0f);
    }
}

void func_80107774_mpiq(omObjData *obj) {
    f32 bounce[12] = { 0.0f, 10.0f, 25.0f, 40.0f, 52.0f, 50.0f, 50.0f, 48.0f, 38.0f, 29.0f, 25.0f, 160.0f };
    MpiqObjWork *work = obj->data;
    f32 limit;
    s16 model;
    s32 i;

    obj->trans.y = work->y;
    if (work->flags & 1) {
        work->y -= work->unk_08;
        work->unk_08 += 8.0f;
        limit = D_8010CA80_mpiq[work->index]->trans.y + 30.0f;
        if (work->y <= limit) {
            work->y = limit;
            work->flags &= ~1;
            work->flags |= 2;
            func_80107E90_mpiq(obj->trans.x, obj->trans.y - 50.0f, obj->trans.z);
        }
    }
    if (work->flags & 2) {
        work->y += 16.0f;
        if (work->y >= work->unk_0C) {
            work->y = work->unk_0C;
            work->flags &= ~2;
        }
    }
    if (work->flags & 8) {
        func_8001C814_main(obj->model[0], 4, 4);
        work->flags &= ~8;
    }
    if (work->flags & 0x10) {
        if (--work->timer == 12) {
            func_8001C258_main(obj->model[0], 4, 4);
        }
        model = obj->model[2];
        if (Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
            func_8001C258_main(model, 4, 4);
            work->flags &= ~0x10;
        }
    }
    if (work->flags & 0x20) {
        work->timer--;
        Hu3DModelScaleSet(obj->model[1], work->scale, work->scale, work->scale);
        Hu3DModelPosSet(obj->model[1], work->x, work->y + bounce[7 - work->timer], 0.0f);
        func_8001F9E4_main(obj->model[1], work->counter);
        work->scale += 0.2f;
        work->counter -= 35;
        if (work->timer == 0) {
            func_8001C258_main(obj->model[1], 4, 4);
            work->flags &= ~0x20;
        }
    }
    if (func_801089D0_mpiq(obj, D_800EC598_minigame[D_8010C9BC_mpiq])) {
        if (work->flags & 3) {
            if (work->unk_24 == 0) {
                func_8004AC5C_main(0x411, D_8010C9BE_mpiq);
                work->unk_24 = 1;
            }
            func_800E561C_minigame(D_800EC598_minigame[D_8010C9BC_mpiq], 1);
            omVibrate(D_8010C9BE_mpiq, 20, 0, 20);
        } else if (D_8010C9C2_mpiq == 0) {
            func_8001C814_main(obj->model[0], 4, 0);
            func_8001C814_main(obj->model[0], 1, 0);
            func_800E58F8_minigame(D_800EC598_minigame[D_8010C9BC_mpiq], 0x26, 0);
            D_8010C9C2_mpiq = 1;
            for (i = 0; i < 4; i++) {
                func_800E12EC_minigame(D_800EC598_minigame[i], 1000.0f);
            }
            work->flags |= 0x20;
            work->timer = 7;
            func_8001C258_main(obj->model[1], 4, 0);
            work->scale = 1.0f;
            work->counter = 255;
        }
    } else {
        work->unk_24 = 0;
    }
}

void func_80107C18_mpiq(s32 index) {
    MpiqObjWork *work = OM_GET_DATA_PTR(D_8010CAC0_mpiq[index], MpiqObjWork);
    work->flags |= 1;
    work->unk_08 = 4.0f;
    work->index = index;
}

void func_80107C50_mpiq(s32 index) {
    OM_GET_DATA_PTR(D_8010CAC0_mpiq[index], MpiqObjWork)->flags |= 8;
}

void func_80107C74_mpiq(void) {
    omObjData *obj;
    MpiqObjWork *work;
    f32 x;
    f32 y;
    f32 z;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = D_8010CAC0_mpiq[i];
        x = obj->trans.x;
        y = obj->trans.y;
        z = obj->trans.z + 200.0f;
        work = obj->data;
        work->flags |= 0x10;
        work->timer = 15;
        Hu3DModelPosSet(D_8010CAC0_mpiq[i]->model[2], x, y, z);
        Hu3DModelScaleSet(D_8010CAC0_mpiq[i]->model[2], 1.0f, 1.0f, 1.0f);
        func_8001C258_main(D_8010CAC0_mpiq[i]->model[2], 4, 0);
    }
}

void func_80107D70_mpiq(void) {
    omObjData *obj;
    s32 *flags;

    obj = omAddObj(0xFF, 1, 0, -1, func_80107DE0_mpiq);
    D_8010CAD0_mpiq = obj;
    flags = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);
    obj->data = flags;
    *flags = 0;
    *obj->model = func_8000B108_main(8, 0x69D);
}

void func_80107DE0_mpiq(omObjData *obj) {
    s32 *flags = obj->data;
    s16 model;

    if (*flags & 1) {
        model = obj->model[0];
        if (Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
            func_8001C258_main(model, 4, 4);
            *flags &= ~1;
        }
    }
}

void func_80107E90_mpiq(f32 x, f32 y, f32 z) {
    omObjData *obj = D_8010CAD0_mpiq;
    s32 *flags = obj->data;

    *flags |= 1;
    func_8001C258_main(obj->model[0], 4, 0);
    Hu3DMotionTimeSet(D_8010CAD0_mpiq->model[0], 0.0f);
    omSetTra(D_8010CAD0_mpiq, x, y, z);
}

void func_80107F28_mpiq(void) {
    omObjData *obj;
    MpiqMarkerObjWork *work;

    obj = omAddObj(0xFF, 1, 0, -1, func_80107FC4_mpiq);
    D_8010CAD4_mpiq = obj;
    work = HuMemAllocTag(sizeof(MpiqMarkerObjWork), TAG_OVERLAY);
    obj->data = work;
    work->flags = 0;
    obj->model[0] = func_8000B108_main(0x230009, 0x69D);
    Hu3DModelScaleSet(obj->model[0], 1.5f, 1.5f, 1.5f);
    work->timer = 0;
}

void func_80107FC4_mpiq(omObjData *obj) {
}

void func_80107FCC_mpiq(s32 index) {
    f32 heights[8] = { 100.0f, 110.0f, 100.0f, 110.0f, 100.0f, 120.0f, 110.0f, 100.0f };
    omObjData *player = D_800EC598_minigame[index];
    s32 chr = GwPlayer[index].chr;
    f32 x = player->trans.x;
    f32 y = player->trans.y + heights[chr];
    f32 z = player->trans.z;
    omObjData *obj = D_8010CAD4_mpiq;
    MpiqMarkerObjWork *work = obj->data;

    work->flags |= 1;
    if (work->timer == 0) {
        func_8001C258_main(obj->model[0], 4, 0);
        Hu3DMotionTimeSet(D_8010CAD4_mpiq->model[0], 0.0f);
        func_8001C814_main(D_8010CAD4_mpiq->model[0], 2, 2);
    }
    omSetTra(D_8010CAD4_mpiq, x, y, z);
    work->timer++;
}

void func_8010811C_mpiq(void) {
    MpiqMarkerObjWork *work = OM_GET_DATA_PTR(D_8010CAD4_mpiq, MpiqMarkerObjWork);

    if (--work->timer == 0) {
        func_8001C258_main(*D_8010CAD4_mpiq->model, HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
        work->flags &= ~1;
    }
}

void func_80108178_mpiq(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *obj;
    MpiqMeterWork *work;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        obj = omAddObj(2, 5, 0, -1, func_80108494_mpiq);
        D_8010CAD8_mpiq[i] = obj;
        obj->data = HuMemAllocTag(sizeof(MpiqMeterWork), TAG_OVERLAY);
        work = obj->data;
        omSetSca(obj, 2.0f, 3.0f, 2.0f);
        if (i == 0) {
            obj->model[0] = func_8000B108_main(0x42000A, 0x6B9);
            obj->model[1] = func_8000B108_main(0x420007, 0x6BD);
            obj->model[2] = func_8000B108_main(0x420008, 0x6BD);
            obj->model[3] = func_8000B108_main(0x420009, 0x6BD);
            obj->model[4] = func_8000B108_main(0x420006, 0x6B9);
        } else {
            obj->model[0] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[0]);
            obj->model[1] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[1]);
            obj->model[2] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[2]);
            obj->model[3] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[3]);
            obj->model[4] = Hu3DModelLink(D_8010CAD8_mpiq[0]->model[4]);
        }
        work->stage = 0;
        work->flags = 0;
        screenPos.x = D_8010C6A8_mpiq[i];
        screenPos.y = 180.0f;
        Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
        omSetTra(obj, pos.x, -144.0f, 0.0f);
        omSetSca(obj, 2.0f, 4.0f, 2.0f);
        work->x = pos.x;
        work->posY[0] = 0.0f;
        Hu3DModelPosSet(obj->model[4], pos.x, work->posY[0], work->posY[0]);
        Hu3DModelScaleSet(obj->model[4], 2.0f, 1.0f, 2.0f);
        for (j = 0; j < 3; j++) {
            Hu3DModelScaleSet(obj->model[j + 1], 2.0f, 2.0f, 2.0f);
            work->posY[j + 1] = j * 50.0f - 44.0f;
            Hu3DModelPosSet(obj->model[j + 1], pos.x, work->posY[j + 1], 0.0f);
            work->barScale[j] = 0.0f;
        }
    }
}

void func_80108494_mpiq(omObjData *obj) {
    MpiqMeterWork *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (obj == D_8010CAD8_mpiq[i]) {
            break;
        }
    }
    work = obj->data;
    for (i = 0; i < 3; i++) {
        Hu3DData[obj->model[i + 1]].scale.y = work->barScale[i];
    }
    if (work->flags & 1) {
        work->barScale[work->stage] += 0.2f;
        Hu3DData[obj->model[4]].pos.y = D_8010CA80_mpiq[D_8010C9BC_mpiq]->trans.y;
        if (work->barScale[work->stage] >= 2.0f) {
            work->barScale[work->stage] = 2.0f;
        }
        if (!(D_8010CA90_mpiq[work->index] & 1)) {
            work->stage++;
            work->flags &= ~1;
        }
    }
}

void func_801085F4_mpiq(s32 index) {
    MpiqMeterWork *work = D_8010CAD8_mpiq[index]->data;

    work->flags |= 1;
    work->index = index;
    func_8001C258_main(D_8010CAD8_mpiq[index]->model[work->stage + 1], 4, 0);
    func_8004AC5C_main(0x410, index);
    omVibrate(index, 10, 0, 10);
}

void func_80108688_mpiq(void) {
    Vec pos;
    Vec2f screenPos;
    omObjData *obj;
    MpiqDanceObjData *work;

    obj = omAddObj(10, 1, 1, -1, func_801087F8_mpiq);
    obj->data = HuMemAllocTag(sizeof(MpiqDanceObjData), TAG_OVERLAY);
    D_8010CA78_mpiq = obj;
    work = obj->data;
    obj->model[0] = func_8000B108_main(0xA005D, 0x6D9);
    func_8001C814_main(obj->model[0], 2, 2);
    screenPos.x = 260.0f;
    screenPos.y = -120.0f;
    Hu3D2Dto3D(0, CZoom, &screenPos, &pos);
    omSetTra(obj, pos.x, pos.y, 200.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.1f, 1.1f, 1.1f);
    func_8000B460_main(obj, 0, 0xA005F);
    func_8000B460_main(obj, 1, 0xA0060);
    func_8000B460_main(obj, 2, 0xA0061);
    func_8001C5B4_main(obj->model[0], obj->motion[0]);
    func_8001C814_main(obj->model[0], 2, 2);
    work->rotY = 0.0f;
}

void func_801087F8_mpiq(omObjData *obj) {
    MpiqDanceObjData *work = obj->data;
    s16 model;

    omSetRot(obj, 0.0f, work->rotY, 0.0f);
    if (work->flags & 1) {
        model = obj->model[0];
        if (Hu3DData[model].motTime >= D_800CCF58_main[Hu3DData[model].motId].unk02) {
            Hu3DMotionShiftSet(model, Hu3DData[obj->motion[0]].motId, 0, 10, 0);
            func_8001C814_main(obj->model[0], 2, 2);
            work->flags &= ~1;
        }
    }
    if (work->flags & 4) {
        work->rotY -= 12.0f;
        if (work->rotY <= -120.0f) {
            work->rotY = -120.0f;
            work->flags &= ~4;
        }
    }
    if (work->flags & 2) {
        work->rotY += 12.0f;
        if (work->rotY >= 0.0f) {
            work->rotY = 0.0f;
            work->flags &= ~2;
        }
    }
}

void func_801089A4_mpiq(s32 flags) {
    MpiqDanceObjData *work = OM_GET_DATA_PTR(D_8010CA78_mpiq, MpiqDanceObjData);
    work->flags &= ~2;
    work->flags &= ~4;
    work->flags |= flags;
}

s16 func_801089D0_mpiq(omObjData *objA, omObjData *objB) {
    s32 result = 0;
    f32 ax = objA->trans.x;
    f32 ay = objA->trans.y;
    f32 bx = objB->trans.x;
    f32 by = objB->trans.y;

    if (HuSqrtf((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) < 150.0f) {
        result = 1;
    }
    return result;
}

void func_80108A3C_mpiq(f32 zoom, f32 rotX, f32 rotY, f32 rotZ, f32 centerX, f32 centerY, f32 centerZ) {
    func_8000B5F0_main(1);
    D_8010C9B4_mpiq = func_8000B638_main();
    ScissorSet(D_8010C9B4_mpiq, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(D_8010C9B4_mpiq, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    CZoom = zoom;
    CRot.x = rotX;
    CRot.y = rotY;
    CRot.z = rotZ;
    Center.x = centerX;
    Center.y = centerY;
    Center.z = centerZ;
    Hu3DCameraPerspectiveSet(D_8010C9B4_mpiq, 30.0f, 80.0f, 8000.0f);
}

void func_80108B74_mpiq(void) {
    s32 images[3] = { 3, 4, 5 };
    omObjData *obj;
    MpiqSignWork *work;
    s32 i;

    obj = omAddObj(10, 0, 0, -1, func_80108E20_mpiq);
    obj->data = work = HuMemAllocTag(sizeof(MpiqSignWork), TAG_OVERLAY);
    D_8010CAE8_mpiq = obj;
    work->flags = 0;
    work->scale = 0.0f;
    work->x = 0.0f;
    work->y = 0.0f;
    for (i = 0; i < 3; i++) {
        D_8010CAF2_mpiq[i] = func_8000B838_main(images[i] | 0x420000);
        D_8010CAEC_mpiq[i] = espEntry(D_8010CAF2_mpiq[i], 0, 1);
        espAttrSet(D_8010CAEC_mpiq[i], 8);
        espPosSet(D_8010CAEC_mpiq[i], 160, 120);
        espDispOn(D_8010CAEC_mpiq[i]);
        espScaleSet(D_8010CAEC_mpiq[i], 1.0f, 1.0f);
        espPriSet(D_8010CAEC_mpiq[i], 255);
    }
    omAddPrcObj(func_80109018_mpiq, 0x4800, 0, 0);
    omAddPrcObj(func_80108D10_mpiq, 0x5100, 0, 0);
}

void func_80108D10_mpiq(void) {
    s32 i;

    while (TRUE) {
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].stat & 1) {
                D_800CDA7C_main[GwPlayer[i].pad] &= 0x1FFF;
                D_800D5558_main[GwPlayer[i].pad] &= 0x1FFF;
            }
            if (func_800E6E8C_minigame() == 2 && (GwPlayer[i].stat & 1)) {
                func_801069F8_mpiq(i);
            }
        }
        HuPrcVSleep();
    }
}

void func_80108E20_mpiq(omObjData *obj) {
    MpiqSignWork *work = obj->data;
    s32 i;

    if (work->flags & 4) {
        espDispOn(D_8010CAEC_mpiq[0]);
    } else {
        espDispOff(D_8010CAEC_mpiq[0]);
    }
    if (work->flags & 8) {
        espDispOn(D_8010CAEC_mpiq[1]);
    } else {
        espDispOff(D_8010CAEC_mpiq[1]);
    }
    if (work->flags & 0x10) {
        espDispOn(D_8010CAEC_mpiq[2]);
    } else {
        espDispOff(D_8010CAEC_mpiq[2]);
    }
    for (i = 0; i < 3; i++) {
        espPosSet(D_8010CAEC_mpiq[i], work->x, work->y);
        espScaleSet(D_8010CAEC_mpiq[i], work->scale, work->scale);
    }
    if (work->flags & 1) {
        work->scale += 0.2f;
        if (work->scale >= 1.0f) {
            work->scale = 1.0f;
            work->flags &= ~1;
        }
    }
    if (work->flags & 2) {
        work->scale -= 0.2f;
        if (work->scale <= 0.2f) {
            work->scale = 0.2f;
            work->flags &= ~0x1E;
            D_8010C9C0_mpiq &= ~0x20;
        }
    }
}

void func_80109018_mpiq(void) {
    Vec2f screenPos;
    Vec pos;
    omObjData *player;
    MpiqSignWork *work;
    u16 buttons;

    while (TRUE) {
        player = D_800EC598_minigame[D_8010C9BC_mpiq];
        if (D_8010C9C2_mpiq == 1 && D_8010C6B8_mpiq == -1 && (D_8010C9C0_mpiq & 4) &&
            func_8010C4C0_mpiq(D_8010C9BC_mpiq)) {
            buttons = D_800D5558_main[GwPlayer[D_8010C9BC_mpiq].pad];
            work = D_8010CAE8_mpiq->data;
            pos.x = player->trans.x;
            pos.y = player->trans.y;
            pos.z = player->trans.z;
            Hu3D3Dto2D(0, &pos, &screenPos);
            work->x = screenPos.x + 28.0f;
            work->y = screenPos.y - 46.0f;
            work->scale = 0.0f;
            if ((buttons & 0xE000) == 0x8000) {
                D_8010C6B8_mpiq = 0;
                func_800E58F8_minigame(player, 0x26, 0);
                func_800E5798_minigame(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < D_800CCF58_main[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                func_800E5798_minigame(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 5;
                HuPrcSleep(30);
                work->flags |= 2;
                D_8010C9C0_mpiq &= ~0x20;
            }
            if ((buttons & 0xE000) == 0x4000) {
                D_8010C6B8_mpiq = 1;
                func_800E58F8_minigame(player, 0x26, 0);
                func_800E5798_minigame(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < D_800CCF58_main[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                func_800E5798_minigame(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 9;
                HuPrcSleep(30);
                work->flags |= 2;
                D_8010C9C0_mpiq &= ~0x20;
            }
            if ((buttons & 0xE000) == 0x2000) {
                D_8010C6B8_mpiq = 2;
                func_800E58F8_minigame(player, 0x26, 0);
                func_800E5798_minigame(player, 0x27);
                while (Hu3DData[player->model[0]].motTime < D_800CCF58_main[Hu3DData[player->model[0]].motId].unk02) {
                    HuPrcVSleep();
                }
                func_800E5798_minigame(player, 0x28);
                HuPrcSleep(2);
                work->flags |= 0x11;
                HuPrcSleep(30);
                work->flags |= 2;
                D_8010C9C0_mpiq &= ~0x20;
            }
        }
        HuPrcVSleep();
    }
}

// Logic and instruction sequence match; only register allocation differs.
// The target keeps i in s3 and 0xAAAAAAAB (for % 3) in s8, spilling
// &D_8010CB00_mpiq[i] to the stack, and stores D_8010CBA0_mpiq[i] without
// hoisting the symbol into a register. Here, loop.c hoists D_8010CBA0_mpiq out of
// the i loop and global-alloc gives s8 to &D_8010CB00_mpiq[i] instead.
// Local declaration order permutations had no effect.
#ifdef NON_MATCHING
void func_80109414_mpiq(void) {
    s32 used[64];
    s32 answerUsed[5];
    s32 mes = 0;
    s32 i;
    s32 j;
    s32 question;
    s32 answer;

    for (i = 0; i < 64; i++) {
        used[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        D_8010CBA0_mpiq[i] = 0;
        while (TRUE) {
            question = rand8() & 0x3F;
            if (D_8010C9F8_mpiq != 0) {
                question = D_8010D020_mpiq;
                D_8010D020_mpiq++;
                if (D_8010D020_mpiq > 64) {
                    D_8010D020_mpiq = 0;
                }
            }
            if (question >= 36) {
                if (question < 49) {
                    mes = question * 2 + 0x52B8;
                } else {
                    mes = question * 2 + 0x539E;
                }
                D_8010CA50_mpiq[i] = mes;
                func_8010A010_mpiq(i);
            }
            if (used[question] == 0 && func_801096C0_mpiq(i, question)) {
                if (question < 36) {
                    mes = question * 4 + 0x5500;
                    D_8010CA50_mpiq[i] = mes;
                    D_8010CBD0_mpiq[i] = 0x5307;
                }
                if (D_8010C9F8_mpiq == 0) {
                    used[question]++;
                }
                for (j = 0; j < 3; j++) {
                    answerUsed[j] = 0;
                    D_8010CB00_mpiq[i][j] = -1;
                }
                if (question >= 36) {
                    func_8010A184_mpiq(i);
                }
                D_8010CBCC_mpiq = 0;
                for (j = 0; j < 3; j++) {
                    while (TRUE) {
                        answer = (u8)(rand8() % 3);
                        if (answerUsed[answer] == 0) {
                            if (question < 36) {
                                D_8010CB00_mpiq[i][j] = mes + 1 + answer;
                            } else {
                                D_8010CB00_mpiq[i][j] = func_8010AB44_mpiq(i, answer);
                            }
                            if (answer == 0) {
                                D_8010CA38_mpiq[i] = j;
                            }
                            answerUsed[answer]++;
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_80109414_mpiq);
#endif

s32 func_801096C0_mpiq(s32 index, s32 question) {
    s32 list[2][6];
    s32 result = TRUE;
    s32 mes;
    s32 value;
    s32 count;
    s32 pick;
    s32 temp;
    s32 swap;
    s32 i;
    s32 j;

    if (D_8010C9F8_mpiq != 0) {
        return TRUE;
    }
    if (question >= 36) {
        if (question >= 49) {
            if (_CheckFlag(0x1C)) {
                return FALSE;
            }
        }
        if (question < 49) {
            mes = question * 2 + 0x52B8;
        } else {
            mes = question * 2 + 0x539E;
        }
        switch (mes) {
            case 0x5302:
                value = D_8010CBB8_mpiq[index] - 0x1C60;
                count = func_800E905C_minigame(value);
                if (count == -1) {
                    return FALSE;
                }
                break;
            case 0x5304:
                if (GWMgUnlockCheck(12) == 0) {
                    result = FALSE;
                }
                break;
            case 0x5306:
                if (GWMgUnlockCheck(34) == 0) {
                    result = FALSE;
                }
                break;
            case 0x5308:
                if (GWMgUnlockCheck(51) == 0) {
                    result = FALSE;
                }
                break;
            case 0x530A:
                if (GWMgUnlockCheck(43) == 0) {
                    result = FALSE;
                }
                break;
            case 0x530C:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(5) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x530E:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(6) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x5310:
                if (GWMgUnlockCheck(70) == 0 || GWMgRecordGet(7) == 1800) {
                    result = FALSE;
                }
                break;
            case 0x5312:
            case 0x5314:
                for (i = 0; i < 6; i++) {
                    if (mes == 0x5312) {
                        list[0][i] = GwCommon.boardRecord[0][i].playCount;
                    } else {
                        list[0][i] = GwCommon.boardRecord[1][i].playCount;
                    }
                    list[1][i] = i;
                }
                for (i = 0; i < 6; i++) {
                    for (j = i; j < 6; j++) {
                        if (list[0][j] >= list[0][i]) {
                            swap = list[0][i];
                            list[0][i] = list[0][j];
                            list[0][j] = swap;
                            swap = list[1][i];
                            list[1][i] = list[1][j];
                            list[1][j] = swap;
                        }
                    }
                }
                count = 0;
                for (i = 0; i < 6; i++) {
                    if (list[0][i] == list[0][0]) {
                        count++;
                    }
                }
                if (count >= 5) {
                    return FALSE;
                }
                pick = 0;
                if (count != 0) {
                    pick = rand8() % count;
                }
                D_8010CBF8_mpiq[0] = list[1][pick];
                for (i = 0; i < 2; i++) {
                    do {
                        pick = rand8() % (6 - count) + count;
                        for (j = 0, temp = 0; j < i + 1; j++) {
                            if (list[1][pick] == D_8010CBF8_mpiq[j]) {
                                temp++;
                            }
                        }
                    } while (temp != 0);
                    D_8010CBF8_mpiq[i + 1] = list[1][pick];
                }
                break;
            case 0x5316:
                value = 0;
                for (i = 0; i < 6; i++) {
                    if (GwCommon.boardRecord[0][i].playCount != 0) {
                        list[0][value] = i;
                        value++;
                    }
                }
                if (value == 0) {
                    result = FALSE;
                } else {
                    D_8010CC04_mpiq = list[0][rand8() % value];
                }
                break;
            case 0x5318:
                value = 0;
                for (i = 0; i < 6; i++) {
                    if (GwCommon.boardRecord[1][i].playCount != 0) {
                        list[0][value] = i;
                        value++;
                    }
                }
                if (value == 0) {
                    result = FALSE;
                } else {
                    D_8010CC04_mpiq = list[0][rand8() % value];
                }
                break;
            case 0x5404:
            case 0x5412:
            case 0x5414:
                value = 0;
                for (i = 0; i < 4; i++) {
                    switch (mes) {
                        case 0x5404:
                            count = GwPlayer[i].gamePrize;
                            break;
                        case 0x5412:
                            count = GwPlayer[i].star;
                            break;
                        default:
                            count = GwPlayer[i].coin;
                            break;
                    }
                    if (count == 0) {
                        value++;
                    }
                }
                if (value == 4) {
                    result = FALSE;
                }
                break;
            case 0x5400:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].star;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5402:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].coin;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5406:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.redPrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x5408:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.bluePrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x540A:
                value = 0;
                for (i = 0; i < 4; i++) {
                    value += GwPlayer[i].stats.prize.hatenaPrize;
                }
                if (value == 0) {
                    result = FALSE;
                }
                break;
            case 0x540C:
                if (GwSystem.bank_coins == 0) {
                    result = FALSE;
                }
                break;
            case 0x541A:
                value = D_8010CBB8_mpiq[index] - 0x1C60;
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].chr == value) {
                        break;
                    }
                }
                if (GwPlayer[i].coin == 0) {
                    result = FALSE;
                }
                break;
            case 0x541C:
                value = D_8010CBB8_mpiq[index] - 0x1C60;
                for (i = 0; i < 4; i++) {
                    if (GwPlayer[i].chr == value) {
                        break;
                    }
                }
                if (GwPlayer[i].star == 0) {
                    result = FALSE;
                }
                break;
            case 0x5410:
                result = FALSE;
                break;
        }
    } else {
        mes = question * 4 + 0x5500;
        switch (mes) {
            case 0x5578:
                if (GwCommon.boardRecord[0][0].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x557C:
                if (GwCommon.boardRecord[0][1].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5580:
                if (GwCommon.boardRecord[0][2].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5584:
                if (GwCommon.boardRecord[0][3].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x5588:
                if (GwCommon.boardRecord[0][4].playCount == 0) {
                    result = FALSE;
                }
                break;
            case 0x558C:
                if (GwCommon.boardRecord[0][5].playCount == 0) {
                    result = FALSE;
                }
                break;
        }
    }
    return result;
}

#ifdef NON_MATCHING
void func_8010A010_mpiq(s32 index) {
    s32 value;

    switch (D_8010CA50_mpiq[index]) {
        case 0x5300:
        case 0x540C:
            value = func_8010AFAC_mpiq(index, 11, -5, 1);
            break;
        case 0x5302:
            value = (u8)(rand8() % 6) + 0x1C60;
            break;
        case 0x5316:
            value = D_8010CC04_mpiq + 0x532B;
            break;
        case 0x5318:
            value = D_8010CC04_mpiq + 0x5331;
            break;
        case 0x541A:
        case 0x541C:
            value = GwPlayer[rand8() & 3].chr + 0x1C60;
            break;
        default:
            D_8010CBB8_mpiq[index] = 0;
            return;
    }
    D_8010CBB8_mpiq[index] = value;
    D_8010CBA0_mpiq[index] |= 2;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010A010_mpiq);
#endif

void func_8010A184_mpiq(s32 index) {
    s32 list[4];
    s32 value;
    s32 other;
    s32 count;
    s32 rank;
    s32 i;

    for (i = 0; i < 256; i++) {
        D_8010CC10_mpiq[i] = 0;
    }
    switch (D_8010CA50_mpiq[index]) {
        case 0x5300:
            D_8010CBA0_mpiq[index] |= 1;
            value = D_8010CBB8_mpiq[index] - 0x531B;
            D_8010D010_mpiq = D_8010C6BC_mpiq[value];
            break;
        case 0x5302:
            value = D_8010CBB8_mpiq[index] - 0x1C60;
            rank = func_800E905C_minigame(value);
            other = 0x533B;
            D_8010D010_mpiq = other - rank;
            if (D_8010C9F8_mpiq != 0) {
                D_8010D010_mpiq = 0x5337;
            }
            break;
        case 0x5304:
            D_8010CBA0_mpiq[index] |= 1;
            D_8010D010_mpiq = GWMgRecordGet(0);
            break;
        case 0x5306:
            D_8010CBA0_mpiq[index] |= 4;
            D_8010D010_mpiq = GWMgRecordGet(2);
            break;
        case 0x5308:
            D_8010CBA0_mpiq[index] |= 32;
            D_8010D010_mpiq = GWMgRecordGet(4);
            break;
        case 0x530A:
            D_8010CBA0_mpiq[index] |= 4;
            D_8010D010_mpiq = GWMgRecordGet(3) * 2;
            break;
        case 0x530C:
            D_8010CBA0_mpiq[index] |= 4;
            D_8010D010_mpiq = GWMgRecordGet(5);
            break;
        case 0x530E:
            D_8010CBA0_mpiq[index] |= 4;
            D_8010D010_mpiq = GWMgRecordGet(6);
            break;
        case 0x5310:
            D_8010CBA0_mpiq[index] |= 4;
            D_8010D010_mpiq = GWMgRecordGet(7);
            break;
        case 0x5312:
            D_8010D010_mpiq = D_8010CBF8_mpiq[0] + 0x532B;
            break;
        case 0x5314:
            D_8010D010_mpiq = D_8010CBF8_mpiq[0] + 0x5331;
            break;
        case 0x5316:
            D_8010CBA0_mpiq[index] |= 1;
            value = D_8010CBB8_mpiq[index] - 0x532B;
            D_8010D010_mpiq = GwCommon.boardRecord[0][value].playCount;
            break;
        case 0x5318:
            D_8010CBA0_mpiq[index] |= 1;
            value = D_8010CBB8_mpiq[index] - 0x5331;
            D_8010D010_mpiq = GwCommon.boardRecord[1][value].playCount;
            break;
        case 0x5400:
            D_8010CBA0_mpiq[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                value += GwPlayer[i].star & 0x7F;
            }
            D_8010D010_mpiq = value;
            break;
        case 0x5402:
            D_8010CBA0_mpiq[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                value += GwPlayer[i].coin;
            }
            D_8010D010_mpiq = value;
            break;
        case 0x5404:
        case 0x5412:
        case 0x5414:
        case 0x5416:
        case 0x5418:
            other = D_8010CA50_mpiq[index];
            value = 1000;
            if (other == 0x5404 || other == 0x5412 || other == 0x5414) {
                value = 0;
            }
            for (i = 0; i < 4; i++) {
                switch (D_8010CA50_mpiq[index]) {
                    case 0x5404:
                        other = GwPlayer[i].gamePrize;
                        break;
                    case 0x5412:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    case 0x5416:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    default:
                        other = GwPlayer[i].coin;
                        break;
                }
                if (D_8010CA50_mpiq[index] == 0x5404 || D_8010CA50_mpiq[index] == 0x5412 ||
                    D_8010CA50_mpiq[index] == 0x5414) {
                    if (value < other) {
                        value = other;
                    }
                } else {
                    if (other < value) {
                        value = other;
                    }
                }
            }
            count = 0;
            for (i = 0; i < 4; i++) {
                switch (D_8010CA50_mpiq[index]) {
                    case 0x5404:
                        other = GwPlayer[i].gamePrize;
                        break;
                    case 0x5412:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    case 0x5416:
                        other = GwPlayer[i].star & 0x7F;
                        break;
                    default:
                        other = GwPlayer[i].coin;
                        break;
                }
                if (other == value) {
                    list[count] = i;
                    count++;
                }
            }
            value = rand8() % count;
            D_8010D010_mpiq = GwPlayer[list[value]].chr + 0x1C60;
            break;
        case 0x5406:
        case 0x5408:
        case 0x540A:
            D_8010CBA0_mpiq[index] |= 1;
            value = 0;
            for (i = 0; i < 4; i++) {
                switch (D_8010CA50_mpiq[index]) {
                    case 0x5406:
                        value += GwPlayer[i].stats.prize.redPrize & 0x7F;
                        break;
                    case 0x5408:
                        value += GwPlayer[i].stats.prize.bluePrize & 0x7F;
                        break;
                    default:
                        value += GwPlayer[i].stats.prize.hatenaPrize & 0x7F;
                        break;
                }
            }
            D_8010D010_mpiq = value;
            break;
        case 0x540C:
            D_8010CBA0_mpiq[index] |= 1;
            D_8010D010_mpiq = GwSystem.bank_coins;
            break;
        case 0x540E:
            D_8010CBA0_mpiq[index] |= 1;
            D_8010D010_mpiq = index + D_8010C9FC_mpiq + 1;
            break;
        case 0x5410:
            D_8010CBA0_mpiq[index] |= 1;
            D_8010D010_mpiq = (GwSystem.current_turn + 1) & 0x7F;
            break;
        case 0x541A:
        case 0x541C:
            D_8010CBA0_mpiq[index] |= 1;
            value = D_8010CBB8_mpiq[index] - 0x1C60;
            for (i = 0; i < 4; i++) {
                if (GwPlayer[i].chr == value) {
                    break;
                }
            }
            if (D_8010CA50_mpiq[index] == 0x541A) {
                D_8010D010_mpiq = GwPlayer[i].coin;
            } else {
                D_8010D010_mpiq = GwPlayer[i].star & 0x7F;
            }
            break;
    }
    D_8010CBD0_mpiq[index] = D_8010CA50_mpiq[index] + 1;
}

#ifdef NON_MATCHING
s16 func_8010AB44_mpiq(s32 index, s32 answer) {
    s32 offset;
    s32 value = 0;
    s32 found;
    s32 i;

    if (answer == 0) {
        return D_8010D010_mpiq;
    }
    switch (D_8010CA50_mpiq[index]) {
        case 0x5300:
            value = func_8010AFAC_mpiq(index, 11, -5, 1);
            break;
        case 0x5302:
            do {
                found = 0;
                offset = rand8() & 3;
                if (D_8010C9F8_mpiq != 0) {
                    return offset + 0x5337;
                }
                for (i = 0; i < 3; i++) {
                    value = offset + 0x5337;
                    if (value == D_8010CB00_mpiq[index][i] || value == D_8010D010_mpiq || value < 0) {
                        found++;
                        break;
                    }
                }
            } while (found != 0);
            break;
        case 0x5304:
            value = func_8010AFAC_mpiq(index, 16, -5, 10);
            break;
        case 0x5306:
        case 0x530A:
        case 0x530C:
        case 0x530E:
        case 0x5310:
            value = func_8010AFAC_mpiq(index, 9, -3, 60);
            break;
        case 0x5308:
            value = func_8010AFAC_mpiq(index, 16, -5, 100);
            break;
        case 0x5312:
            value = D_8010CBFC_mpiq[D_8010CBCC_mpiq++] + 0x532B;
            break;
        case 0x5314:
            value = D_8010CBFC_mpiq[D_8010CBCC_mpiq++] + 0x5331;
            break;
        case 0x5316:
        case 0x5318:
        case 0x540E:
        case 0x541C:
            value = func_8010AFAC_mpiq(index, 4, -1, 1);
            break;
        case 0x5400:
            value = func_8010AFAC_mpiq(index, 5, -2, 1);
            break;
        case 0x5402:
        case 0x541A:
            value = func_8010AFAC_mpiq(index, 21, -10, 1);
            break;
        case 0x5404:
        case 0x5412:
        case 0x5414:
        case 0x5416:
        case 0x5418:
            value = func_8010AEDC_mpiq(index);
            break;
        case 0x5406:
        case 0x5408:
        case 0x540A:
            value = func_8010AFAC_mpiq(index, 7, -3, 1);
            break;
        case 0x5410:
            value = func_8010AFAC_mpiq(index, 9, -3, 1);
            break;
    }
    return value;
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/ovl_21_mpiq/204F90", func_8010AB44_mpiq);
#endif

s32 func_8010AEDC_mpiq(s32 index) {
    s32 value = 0;
    s32 found;
    s32 chr;
    s32 i;

    do {
        found = 0;
        chr = rand8() & 7;
        for (i = 0; i < 4; i++) {
            if (GwPlayer[i].chr == chr) {
                break;
            }
        }
        if (i == 4) {
            value = chr + 0x1C60;
            for (i = 0; i < 3; i++) {
                if (value == D_8010CB00_mpiq[index][i]) {
                    break;
                }
            }
            if (i == 3) {
                found++;
            }
        }
    } while (found == 0);
    return value;
}

s32 func_8010AFAC_mpiq(s32 index, s32 range, s32 base, s32 scale) {
    s32 offset;
    s32 tries = 0;
    s32 value;
    s32 found;
    s32 i;

    while (TRUE) {
        offset = (rand8() % range + base) * scale;
        found = 0;
        for (i = 0; i < 3; i++) {
            value = offset + D_8010D010_mpiq;
            if (value == D_8010CB00_mpiq[index][i] || value == D_8010D010_mpiq || value <= 0) {
                found++;
                break;
            }
        }
        if (found == 0 || (D_8010C9F8_mpiq != 0 && tries == 100)) {
            break;
        }
        tries++;
    }
    return value;
}

void func_8010B0CC_mpiq(void) {
    s32 counts[4];
    omObjData *player;
    MpiqDanceObjData *data;
    s32 i;
    s32 round;
    s32 count;
    s32 wins;
    s32 tied;

    while (func_800E6E8C_minigame() != 2) {
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        counts[i] = 0;
    }
    D_8010C9D8_mpiq = -1;
    while (1) {
        for (round = 0; round < 10; round++) {
            D_8010C9C0_mpiq = 0;
            D_8010CA4C_mpiq = round;
            D_8010C6B8_mpiq = -1;
            for (i = 0; i < 4; i++) {
                func_80106664_mpiq(i);
            }
            func_801089A4_mpiq(4);
            D_8010CA00_mpiq = func_8010BB74_mpiq();
            omAddPrcObj(func_8010C2F0_mpiq, 0x4900, 0, 0);
            HuPrcVSleep();
            D_8010C9C2_mpiq = 0;
            omAddObj(6, 0, 0, -1, func_8010BA64_mpiq);
            while (HuWinStatGet(D_8010CA00_mpiq) != 0) {
                if (D_8010C9C0_mpiq & 4) {
                    break;
                }
                HuPrcVSleep();
            }
            if (!(D_8010C9C0_mpiq & 4)) {
                D_8010C9C0_mpiq |= 0x10;
                while (D_8010C9C0_mpiq & 0x10) {
                    HuPrcVSleep();
                }
            }
            HuWinKill(D_8010CA00_mpiq);
            D_8010CA00_mpiq = -1;
            if (D_8010C9C0_mpiq & 4) {
                func_8004AC5C_main(0x40D, D_8010C9BC_mpiq);
                PlayerFXPlay(0xCA, D_8010C9BC_mpiq);
                D_8010CA00_mpiq = func_8010BD1C_mpiq();
                func_801089A4_mpiq(2);
                D_8010C9C0_mpiq |= 0x20;
                while (D_8010C9C0_mpiq & 0x20) {
                    HuPrcVSleep();
                }
                HuWinKill(D_8010CA00_mpiq);
                D_8010CA00_mpiq = -1;
                func_80107C50_mpiq(D_8010C9BC_mpiq);
                player = D_800EC598_minigame[D_8010C9BC_mpiq];
                data = D_8010CA78_mpiq->data;
                if (D_8010C6B8_mpiq == D_8010CA38_mpiq[round]) {
                    func_8004AC5C_main(0x40E, D_8010C9BC_mpiq);
                    PlayerFXPlay(0x274, D_8010C9BC_mpiq);
                    espDispOn(D_8010C9DC_mpiq[0]);
                    func_800E5798_minigame(player, 0x29);
                    Hu3DMotionShiftSet(D_8010CA78_mpiq->model[0], Hu3DData[D_8010CA78_mpiq->motion[1]].motId, 0, 10, 0);
                    data->flags |= 1;
                    HuPrcSleep(30);
                    if (D_8010C9F8_mpiq == 0) {
                        func_80107558_mpiq(D_8010C9BC_mpiq, ++D_8010C9C8_mpiq[D_8010C9BC_mpiq]);
                        func_801085F4_mpiq(D_8010C9BC_mpiq);
                        HuPrcSleep(30);
                    }
                } else {
                    func_8004AC5C_main(0x40F, D_8010C9BC_mpiq);
                    PlayerFXPlay(0x286, D_8010C9BC_mpiq);
                    espDispOn(D_8010C9DC_mpiq[1]);
                    func_800E5798_minigame(player, 0x2A);
                    Hu3DMotionShiftSet(D_8010CA78_mpiq->model[0], Hu3DData[D_8010CA78_mpiq->motion[2]].motId, 0, 10, 0);
                    data->flags |= 1;
                    HuPrcSleep(30);
                    func_80107C18_mpiq(D_8010C9BC_mpiq);
                    HuPrcSleep(70);
                    if (D_8010C6B8_mpiq == -1) {
                        func_800E58F8_minigame(player, 0x26, 0);
                    }
                    func_800E5798_minigame(player, 0x2B);
                    D_8010C9E8_mpiq[D_8010C9BC_mpiq] |= 1;
                    counts[D_8010C9BC_mpiq] = 2;
                    HuPrcSleep(20);
                    func_80107FCC_mpiq(D_8010C9BC_mpiq);
                }
                espDispOff(D_8010C9DC_mpiq[0]);
                espDispOff(D_8010C9DC_mpiq[1]);
            }
            count = 0;
            for (i = 0; i < 4; i++) {
                player = D_800EC598_minigame[i];
                if (D_8010C9E8_mpiq[i] & 1) {
                    counts[i]--;
                    if (round == 9) {
                        counts[i] = 0;
                    }
                    if (counts[i] == 0) {
                        func_800E5798_minigame(player, 0x21);
                        func_8010811C_mpiq();
                        count++;
                    }
                }
            }
            if (count != 0) {
                HuPrcSleep(30);
            }
            for (i = 0; i < 4; i++) {
                player = D_800EC598_minigame[i];
                if (D_8010C9E8_mpiq[i] & 1) {
                    if (counts[i] == 0) {
                        func_800E5798_minigame(player, 0);
                        D_8010C9E8_mpiq[i] &= ~1;
                    }
                }
            }
            HuPrcSleep(30);
            for (i = 0; i < 4; i++) {
                if (D_8010C9C8_mpiq[i] == 3) {
                    D_8010C9D8_mpiq = i;
                }
            }
            if (D_8010C9D8_mpiq != -1) {
                break;
            }
        }
        if (D_8010C9F8_mpiq == 0) {
            break;
        }
        D_8010C9FC_mpiq += 10;
        func_80109414_mpiq();
    }
    if (D_8010C9D8_mpiq == -1) {
        for (round = 0; round < 2; round++) {
            wins = 2 - round;
            tied = 0;
            D_8010C9D8_mpiq = -1;
            for (i = 0; i < 4; i++) {
                if (D_8010C9C8_mpiq[i] == wins) {
                    tied++;
                    D_8010C9D8_mpiq = i;
                }
            }
            if (tied == 1) {
                break;
            }
            if (tied > 1) {
                D_8010C9D8_mpiq = -1;
                break;
            }
        }
    }
    func_800E6F0C_minigame(3);
    func_80107C74_mpiq();
    func_801089A4_mpiq(2);
    for (i = 0; i < 16; i++) {
        for (round = 0; round < 4; round++) {
            D_800EC598_minigame[round]->rot.y = i * 12 + 180.0f;
        }
        HuPrcVSleep();
    }
    while (D_800EB934_minigame != 1) {
        HuPrcVSleep();
    }
    for (round = 0; round < 4; round++) {
        if (round == D_8010C9D8_mpiq) {
            func_800E5798_minigame(D_800EC598_minigame[round], 0xD);
            func_80045ED0_main(D_800A178C_main[GwPlayer[round].chr][0] | 0x2F);
        } else {
            func_800E5798_minigame(D_800EC598_minigame[round], 0xE);
        }
    }
    omDelPrcObj(NULL);
}

void func_8010B900_mpiq(void) {
    s32 pressed[4];
    s32 count;
    s32 i;

    while (!(D_8010C9C0_mpiq & 2)) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (D_8010C9E8_mpiq[i] & 1) {
                continue;
            }
            if (D_800D5558_main[GwPlayer[i].pad] & 0x8000) {
                pressed[count++] = i;
                D_8010C9C0_mpiq &= ~0x10;
                D_8010C9C0_mpiq |= 4;
            }
        }
        if (count != 0) {
            D_8010C9BC_mpiq = pressed[rand8() % count];
            break;
        }
        HuPrcVSleep();
    }
    omDelPrcObj(NULL);
}

void func_8010BA64_mpiq(omObjData *obj) {
    s32 pressed[4];
    s32 count;
    s32 i;

    if (!(D_8010C9C0_mpiq & 2)) {
        count = 0;
        for (i = 0; i < 4; i++) {
            if (D_800D5558_main[GwPlayer[i].pad] & 0x8000) {
                pressed[count++] = i;
                D_8010C9C0_mpiq &= ~0x10;
                D_8010C9C0_mpiq |= 4;
            }
        }
        if (count == 0) {
            return;
        }
        D_8010C9BC_mpiq = pressed[rand8() % count];
    }
    omDelObj(obj);
}

const char D_8010C964_mpiq[] = "%d";
const char D_8010C968_mpiq[] = "%02d%c%02d%c%02d";
const char D_8010C97C_mpiq[] = "%d%c%02d";

s16 func_8010BB74_mpiq(void) {
    s16 size[2];
    char buf[256];
    s32 mes;
    s16 win;

    mes = D_8010CA50_mpiq[D_8010CA4C_mpiq];
    sprintf(buf, D_8010C964_mpiq, D_8010CA4C_mpiq + 1 + D_8010C9FC_mpiq);
    HuWinInsertMesSizeGet((u32)buf, 1);
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 2) {
        HuWinInsertMesSizeGet(D_8010CBB8_mpiq[D_8010CA4C_mpiq], 0);
    }
    HuWinMesMaxSizeGet(1, size, mes);
    win = HuWinCreate(79, 45, 165, 80, 0, 0);
    D_8010CAFC_mpiq = win;
    func_8005B63C_main(win, 64, 64);
    HuWinMesSpeedSet(win, 5);
    func_80060144_main(win);
    HuWinBGTPLvlSet(win, 0);
    HuWinActivePlayerSet(win, 1 << GwPlayer[0].pad);
    HuWinInsertMesSet(win, (u32)buf, 1);
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 2) {
        HuWinInsertMesSet(win, D_8010CBB8_mpiq[D_8010CA4C_mpiq], 0);
    }
    HuWinHomeClear(win);
    HuWinMesSet(win, mes, -1, -1);
    return win;
}

s16 func_8010BD1C_mpiq(void) {
    s16 size[2];
    char buf[3][256];
    char *bufs[3];
    s32 mes = 0x533C;
    s32 count = 0;
    s32 i;
    s32 value;
    s32 quotient;
    s32 minutes;
    s32 seconds;
    s32 fraction;
    s16 win;

    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 1) {
        sprintf(buf[0], D_8010C964_mpiq, D_8010CB00_mpiq[D_8010CA4C_mpiq][0]);
        sprintf(buf[1], D_8010C964_mpiq, D_8010CB00_mpiq[D_8010CA4C_mpiq][1]);
        sprintf(buf[2], D_8010C964_mpiq, D_8010CB00_mpiq[D_8010CA4C_mpiq][2]);
        HuWinInsertMesSizeGet((u32)buf[0], 0);
        HuWinInsertMesSizeGet((u32)buf[1], 1);
        HuWinInsertMesSizeGet((u32)buf[2], 2);
        HuWinInsertMesSizeGet(D_8010CBD0_mpiq[D_8010CA4C_mpiq], 3);
        count = 1;
    }
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 4) {
        bufs[0] = buf[0];
        bufs[1] = buf[1];
        bufs[2] = buf[2];
        for (i = 0; i < 3; i++) {
            value = D_8010CB00_mpiq[D_8010CA4C_mpiq][i];
            quotient = value / 3600;
            value %= 3600;
            minutes = value / 60;
            seconds = value % 60;
            fraction = seconds * 100 / 60;
            if (D_8010CA50_mpiq[D_8010CA4C_mpiq] == 0x530A) {
                fraction = seconds * 99 / 60;
            }
            sprintf(bufs[i], D_8010C968_mpiq, quotient, 0x5C, minutes, 0x5B, fraction);
            HuWinInsertMesSizeGet((u32)bufs[i], i);
        }
        count++;
    }
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 0x20) {
        bufs[0] = buf[0];
        bufs[1] = buf[1];
        bufs[2] = buf[2];
        for (i = 0; i < 3; i++) {
            value = D_8010CB00_mpiq[D_8010CA4C_mpiq][i];
            quotient = value / 100;
            value %= 100;
            sprintf(bufs[i], D_8010C97C_mpiq, quotient, 0x85, value);
            HuWinInsertMesSizeGet((u32)bufs[i], i);
        }
        count++;
    }
    if (count == 0) {
        for (i = 0; i < 3; i++) {
            HuWinInsertMesSizeGet(D_8010CB00_mpiq[D_8010CA4C_mpiq][i], (s8)i);
        }
    }
    HuWinMesMaxSizeGet(1, size, mes);
    win = HuWinCreate(79, 45, 165, 80, 0, 0);
    func_8005B63C_main(win, 64, 64);
    HuWinMesSpeedSet(win, 0);
    func_80060144_main(win);
    HuWinBGTPLvlSet(win, 0);
    HuWinActivePlayerSet(win, 1 << GwPlayer[0].pad);
    count = 0;
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 0x21) {
        HuWinInsertMesSet(win, (u32)buf[0], 0);
        HuWinInsertMesSet(win, (u32)buf[1], 1);
        HuWinInsertMesSet(win, (u32)buf[2], 2);
        HuWinInsertMesSet(win, D_8010CBD0_mpiq[D_8010CA4C_mpiq], 3);
        count = 1;
    }
    if (D_8010CBA0_mpiq[D_8010CA4C_mpiq] & 4) {
        HuWinInsertMesSet(win, (u32)buf[0], 0);
        HuWinInsertMesSet(win, (u32)buf[1], 1);
        HuWinInsertMesSet(win, (u32)buf[2], 2);
        count++;
    }
    if (count == 0) {
        for (i = 0; i < 3; i++) {
            HuWinInsertMesSet(win, D_8010CB00_mpiq[D_8010CA4C_mpiq][i], i);
        }
        HuWinInsertMesSet(win, D_8010CBD0_mpiq[D_8010CA4C_mpiq], 3);
    }
    HuWinHomeClear(win);
    HuWinMesSet(win, mes, -1, -1);
    return win;
}

void func_8010C2F0_mpiq(void) {
    s32 timer;
    s32 mode;
    s32 i;

    D_8010CAF8_mpiq = 5;
    timer = 30;
    while (TRUE) {
        if (D_8010C9C0_mpiq & 0x10) {
            mode = 1;
            break;
        }
        if (D_8010C9C0_mpiq & 4) {
            mode = 2;
            break;
        }
        HuPrcVSleep();
    }
    GMesPosSet(GMesCreate(0x1A, D_8010CAF8_mpiq, 160, 28), 154.0f, 28.0f);
    while (D_8010CAF8_mpiq > 0) {
        if (--timer == 0) {
            timer = 30;
            D_8010CAF8_mpiq--;
        }
        func_8003F578_main(D_8010CAFA_mpiq);
        if (mode == 1 && (D_8010C9C0_mpiq & 4)) {
            D_8010CAF8_mpiq = 5;
            timer = 30;
            mode = 3;
        }
        if (D_8010C6B8_mpiq != -1 || D_8010CAF8_mpiq == 0) {
            break;
        }
        HuPrcVSleep();
    }
    D_8010C9C0_mpiq = (D_8010C9C0_mpiq | 2) & ~0x14;
    D_8010C9C2_mpiq = 1;
    if (D_8010CAF8_mpiq == 0) {
        D_8010C9C0_mpiq &= ~0x20;
        for (i = 0; i < 4; i++) {
            func_800E12EC_minigame(D_800EC598_minigame[i], 1000.0f);
        }
    }
    func_8003F5C0_main();
    omDelPrcObj(NULL);
}

s32 func_8010C4C0_mpiq(s32 index) {
    s32 result = 0;
    if (D_800EC598_minigame[index]->trans.y == D_8010CA80_mpiq[index]->trans.y) {
        result = 1;
    }
    return result;
}

void func_8010C558_mpiq(omObjData *obj);

void func_8010C504_mpiq(void) {
    omObjData *obj = omAddObj(0xA, 0, 0, -1, func_8010C558_mpiq);
    s32 *value = HuMemAllocTag(sizeof(s32), TAG_OVERLAY);

    obj->data = value;
    *value = 0;
}

const char D_8010C988_mpiq[] = "ENDLESS";

void func_8010C558_mpiq(omObjData *obj) {
    s32 *counter = obj->data;

    if (((*counter += 1) & 0x10) != 0) {
        fontcolor = FONT_COLOR_WHITE;
        sprintf(D_800D5218_main, D_8010C988_mpiq);
        print8(0xE8, 0x10, D_800D5218_main);
    }
}

void func_8010C5B8_mpiq(omObjData *obj) {
    if (omPauseChk() + D_800D6A90_main != 0) {
        if (D_8010CA00_mpiq != -1) {
            HuWinDispOff(D_8010CA00_mpiq);
        }
    } else if (D_8010CA00_mpiq != -1) {
        HuWinDispOn(D_8010CA00_mpiq);
    }
}

const char D_8010C990_mpiq[] = "MOTION ERROR! WINNER=%d\n";
const char D_8010C9AC_mpiq[] = "";

void func_8010C624_mpiq(void) {
    fontcolor = FONT_COLOR_WHITE;
    sprintf(D_800D5218_main, D_8010C990_mpiq, D_8010C9D8_mpiq);
    print8(0x20, 0xB0, D_800D5218_main);
}
