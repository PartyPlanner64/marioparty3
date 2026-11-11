#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

extern s32 D_800A178C_main[][6];
extern f32 D_800EB724_minigame;
extern u16 D_800EC288_minigame;
extern Vec D_800EC298_minigame[];
extern omObjData *D_800EBE70_minigame[];

extern s32 D_80109700_boulder_ball[8];
extern Vec D_80109720_boulder_ball;
extern Vec D_8010972C_boulder_ball;
extern Vec D_80109738_boulder_ball;
extern s32 D_8010975C_boulder_ball;
extern D_80111B50_vine_with_me_Struct D_80109760_boulder_ball;
extern f32 D_801097A4_boulder_ball[4];
extern s32 D_80109758_boulder_ball;
extern s32 D_80109794_boulder_ball;
extern s32 D_801097C4_boulder_ball;
extern s32 D_801097C8_boulder_ball;
extern s32 D_801097CC_boulder_ball;
extern s32 D_801097D0_boulder_ball;
extern s32 D_8010988C_boulder_ball;
extern s32 D_80109890_boulder_ball;
extern s32 D_80109894_boulder_ball;
extern s32 D_80109898_boulder_ball;
extern s32 D_8010989C_boulder_ball;
extern omObjData *D_801098A0_boulder_ball;
extern omObjData *D_801098A4_boulder_ball;

void func_80106410_boulder_ball(omObjData *object);
void func_80106B58_boulder_ball(omObjData *object);
void func_80106C8C_boulder_ball(omObjData *object);
void func_80106DAC_boulder_ball(omObjData *object, s32 model, s32 motion, u16 player);
s32 func_8010707C_boulder_ball(omObjData *object, omObjData *other);
s32 func_80107194_boulder_ball(omObjData *object);
s32 func_80107298_boulder_ball(omObjData *object);
void func_80107924_boulder_ball(omObjData *object);
void func_80107A20_boulder_ball(omObjData *object);
void func_80107B0C_boulder_ball(omObjData *object);
void func_80107C08_boulder_ball(omObjData *object);
void func_80108000_boulder_ball(omObjData *object);
void func_801083D8_boulder_ball(omObjData *object);
void func_80108A08_boulder_ball(omObjData *object);
s32 func_80108CF4_boulder_ball(omObjData *object);
s32 func_80108E5C_boulder_ball(omObjData *object);
void func_801093B8_boulder_ball(omObjData *object);
s32 func_80109410_boulder_ball(omObjData *object);
s32 func_801095A0_boulder_ball(omObjData *object);

void func_801059A0_boulder_ball(void) {
    u8 camIndex;

    func_8001FE20_main(50);
    func_80021BE0_main(&D_800EBEB0_minigame, 0x40);
    func_800142A0_main(32);
    omInitObjMan(50, 0);
    func_8004A208_main();
    func_800E1804_minigame();
    func_8000B5F0_main(1);
    camIndex = func_8000B638_main();
    ScissorSet(camIndex, 0.0f, 0.0f, 320.0f, 240.0f);
    ViewportSet(camIndex, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    Hu3DCameraPerspectiveSet(0, 32.0f, 80.0f, 5000.0f);
    Hu3DGLightDirSet(1, -94.0f, 65.0f, 34.0f);
    D_800EC1B8_minigame = 0;
    D_800EC280_minigame = 0;
    D_800EBE28_minigame = 0;
    func_800E18D8_minigame();
    func_800E19F0_minigame(1);
    D_800EB77C_minigame = 0.0f;
    func_800E1490_minigame(D_800EBE28_minigame);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 10, 0, -1, func_80106B58_boulder_ball);
    D_800EC1C0_minigame[D_800EBE28_minigame++] = omAddObj(1, 5, 0, -1, func_80106C8C_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107924_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107A20_boulder_ball);
    D_800EC598_minigame[D_800EC280_minigame++] = omAddObj(3, 10, 60, -1, func_80107B0C_boulder_ball);
    D_801098A4_boulder_ball = omAddObj(3, 10, 60, -1, func_80107C08_boulder_ball);
    D_801098A0_boulder_ball = D_800EBE70_minigame[D_800EC1B8_minigame++] =
        omAddObj(2, 4, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    D_800EBE70_minigame[D_800EC1B8_minigame++] = omAddObj(2, 10, 0, -1, func_80108A08_boulder_ball);
    omSetStatBit(omAddObj(0x7FDA, 0, 0, -1, omOutView), OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    Center.x = 0.0f;
    Center.y = 200.0f;
    Center.z = 900.0f;
    CRot.x = 358.0f;
    CRot.y = 0.0f;
    CZoom = 1400.0f;
    WipeCreateIn(WIPE_TYPE_PREV, 16);
    func_800E5EA0_minigame(&D_80109760_boulder_ball);
    if (GwPlayer[0].group == 0) {
        D_8010989C_boulder_ball = 0;
    }
    if (GwPlayer[1].group == 0) {
        D_8010989C_boulder_ball = 1;
    }
    if (GwPlayer[2].group == 0) {
        D_8010989C_boulder_ball = 2;
    }
    if (GwPlayer[3].group == 0) {
        D_8010989C_boulder_ball = 3;
    }
    D_800EB930_minigame = 47;
    D_800EB932_minigame = 36;
}

void func_80105E74_boulder_ball(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

void func_80105EA0_boulder_ball(void) {
    f32 minY = 2000.0f;
    f32 maxZ = 0.0f;
    s32 i;

    for (i = 0; i < D_800EC280_minigame; i++) {
        if (maxZ < D_800EC598_minigame[i]->trans.z) {
            maxZ = D_800EC598_minigame[i]->trans.z;
        }
        if (D_800EC598_minigame[i]->trans.y < minY) {
            minY = D_800EC598_minigame[i]->trans.y;
        }
    }
    Center.x = 0.0f;
    Center.y = minY + 200.0f;
    Center.z = maxZ;
    if (890.0f < maxZ) {
        Center.z = 890.0f;
    }
    if (Center.y < 325.0f) {
        Center.y = 325.0f;
    }
    if (Center.y > 550.0f) {
        Center.y = 550.0f;
    }
    CRot.x = 362.0f - (Center.z - 600.0f) / 60.0f;
    CZoom = 1500.0f - (Center.y - 325.0f);
    if (CRot.x > 370.0f) {
        CRot.x = 370.0f;
    }
    if (CRot.x < 358.0f) {
        CRot.x = 358.0f;
    }
    if (CZoom < 1300.0f) {
        CZoom = 1300.0f;
    }
}

void func_801060D0_boulder_ball(void) {
    s32 time = func_800E6E9C_minigame();
    func_800E1BA8_minigame_ObjData *playerData = D_801098A4_boulder_ball->data;
    A96F0_ObjData *boulderData = D_801098A0_boulder_ball->data;

    if (time < 5) {
        Center.x = 0.0f;
        Center.y = 800.0f;
        Center.z = -700.0f;
        CZoom = 1000.0f;
        D_801098A0_boulder_ball->trans.x = sindf(D_801098A4_boulder_ball->rot.y) * 150.0f + 0.0f;
        D_801098A0_boulder_ball->trans.y = 700.0f;
        D_801098A0_boulder_ball->trans.z = cosdf(D_801098A4_boulder_ball->rot.y) * 150.0f + -900.0f;
    } else if (time < 40 && D_80109794_boulder_ball == 0) {
        D_801098A4_boulder_ball->rot.y -= 1.5f;
        if (D_801098A4_boulder_ball->rot.y < -26.0f) {
            D_801098A4_boulder_ball->rot.y = -26.0f;
        }
        if (D_801098A4_boulder_ball->rot.y == -26.0f) {
            Hu3DMotionTimeSet(D_801098A4_boulder_ball->model[1], 0.0f);
            playerData->unk50 = 0;
            D_80109758_boulder_ball = 0;
            D_801098A0_boulder_ball->rot.y = boulderData->unk3C = D_801098A4_boulder_ball->rot.y;
            boulderData->unk40 = 7.0f;
            boulderData->unk78 = 0;
            boulderData->unk38 = -0.75f;
            D_80109794_boulder_ball = 1;
            func_8004AC98_main(0x31F, D_8010989C_boulder_ball);
        }
        D_801098A0_boulder_ball->trans.x = sindf(D_801098A4_boulder_ball->rot.y) * 150.0f + 0.0f;
        D_801098A0_boulder_ball->trans.y = 700.0f;
        D_801098A0_boulder_ball->trans.z = cosdf(D_801098A4_boulder_ball->rot.y) * 150.0f + -900.0f;
    } else {
        D_801098A4_boulder_ball->rot.y *= 0.8f;
        Center.y -= 6.6666665f;
        Center.z += 17.777779f;
        CZoom += 4.4444447f;
        if (Center.y < 325.0f) {
            Center.y = 325.0f;
        }
        if (Center.z > 890.0f) {
            Center.z = 890.0f;
        }
        if (CZoom > 1500.0f) {
            CZoom = 1500.0f;
        }
    }
    Hu3DModelRotSet(D_801098A4_boulder_ball->model[1], 0.0f, D_801098A4_boulder_ball->rot.y, 0.0f);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80106410_boulder_ball);

void func_80106B58_boulder_ball(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    D_800EB73C_minigame = 15.0f;
    object->model[0] = func_8000B0A0_main(0x250000, 0x6B9);
    object->model[1] = func_8000B0A0_main(0x250003, 0xAB9);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = func_80106410_boulder_ball;
    work->unk03 = 1;
    func_800E147C_minigame(object);
    func_800E1370_minigame(object, 1, 0.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 22.5f);
    func_800E1468_minigame(object);
    work->unk04 = 0;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_80106C8C_boulder_ball(omObjData *object) {
    D_800EC1C0_minigame_ObjData *work;

    D_800EB73C_minigame = 15.0f;
    object->model[0] = func_8000B0A0_main(0x250001, 0x29D);
    object->trans.x = 0.0f;
    object->trans.y = 0.0f;
    object->trans.z = 0.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, object->trans.z);
    work = HuMemAllocTag(0xB4, TAG_OVERLAY);
    object->data = work;
    memset(work, 0, 0xB4);
    object->func = NULL;
    work->unk03 = 1;
    func_800E147C_minigame(object);
    func_800E1370_minigame(object, 1, 0.0f);
    func_800E1304_minigame(object, 0.2f);
    func_800E1310_minigame(object, D_800EB73C_minigame);
    func_800E131C_minigame(object, 22.5f);
    func_800E1468_minigame(object);
    work->unk04 = 1;
    omSetStatBit(object, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
}

void func_80106DAC_boulder_ball(omObjData *object, s32 model, s32 motion, u16 player) {
    func_800E1BA8_minigame_ObjData *data;
    s32 chr;
    s32 attr1 = 0xAC9;
    s32 attr2 = 0xA99;

    func_800E1BA8_minigame(object, model, motion, player, attr1, attr2);
    data = object->data;
    chr = GwPlayer[data->unk59].chr;
    object->model[3] = func_8000B108_main(3, 0x88D);
    object->model[4] = func_8000B108_main(4, 0x88D);
    object->model[5] = func_8000B108_main(6, 0x88D);
    object->model[7] = func_8000B108_main(8, 0x88D);
    func_800E5A00_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5A00_minigame(object, 1, func_80017BB8_main(chr, 1), 1, 0);
    func_800E5A00_minigame(object, 2, func_80017BB8_main(chr, 2), 1, 0);
    func_800E5A00_minigame(object, 0x11, func_80017BB8_main(chr, 0xE), 1, 0xF);
    func_800E5A00_minigame(object, 3, func_80017BB8_main(chr, 0x1D), 1, 0);
    func_800E5A00_minigame(object, 4, func_80017BB8_main(chr, 0x1E), 1, 0);
    func_800E5A00_minigame(object, 0x1E, func_80017BB8_main(chr, 0x20), 2, 0);
    func_800E5A00_minigame(object, 0x1F, func_80017BB8_main(chr, 0x21), 2, 0);
    func_800E5A00_minigame(object, 0x20, func_80017BB8_main(chr, 0x22), 0, 0);
    func_800E5978_minigame(object, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    func_800E5978_minigame(object, 0xE, func_80017BB8_main(chr, 0x36), 1, 0x78);
    data->unk4C = 0.05f;
    data->unkB4 = 0.8f;
    data->unkEC = func_8010707C_boulder_ball;
    func_800E149C_minigame(object, 0, 2);
    func_800E149C_minigame(object, 1, 1);
    func_800E3568_minigame(data, 0, func_80107298_boulder_ball);
    func_800E3568_minigame(data, 1, func_80107194_boulder_ball);
}

s32 func_8010707C_boulder_ball(omObjData *object, omObjData *other) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    f32 x, y, z;

    if (func_800E6E8C_minigame() == 2) {
        if (data->unkBE != 0) {
            D_800EC288_minigame++;
        } else {
            x = object->trans.x;
            y = object->trans.y;
            z = object->trans.z;
            func_8004AC98_main(GwPlayer[data->unk59].chr + 0x287, data->unk59);
            func_8004AC98_main(0x320, data->unk59);
            func_800E561C_minigame(object, 1);
            func_800E5690_minigame(object, 0);
            func_800E4C88_minigame(object, 7, x, y, z, 0.0f, 0.0f);
            data->unkBE = 105;
            omVibrate(data->unk59, 20, 0, 20);
        }
    }
    return 1;
}

s32 func_80107194_boulder_ball(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;

    if (GwPlayer[data->unk59].stat & 1) {
        D_800D5558_main[data->unk57] = D_80109890_boulder_ball;
        D_800CDA7C_main[data->unk57] = D_8010988C_boulder_ball;
        D_800CBB6E_main[data->unk57] = D_80109894_boulder_ball;
        D_800D20A1_main[data->unk57] = D_80109898_boulder_ball;
    }
    if (func_800E6E8C_minigame() == 2 && object->trans.z <= -600.0f) {
        func_800E6F0C_minigame(3);
        D_8010975C_boulder_ball = 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107298_boulder_ball);

void func_80107924_boulder_ball(omObjData *object) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(object, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_80109720_boulder_ball.x - 80.0f;
    object->trans.x = D_80109720_boulder_ball.x;
    object->trans.y = D_80109720_boulder_ball.y;
    object->trans.z = D_80109720_boulder_ball.z;
    D_801097C4_boulder_ball++;
}

void func_80107A20_boulder_ball(omObjData *object) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(object, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_8010972C_boulder_ball.x;
    object->trans.x = D_8010972C_boulder_ball.x;
    object->trans.y = D_8010972C_boulder_ball.y;
    object->trans.z = D_8010972C_boulder_ball.z;
    D_801097C4_boulder_ball++;
}

void func_80107B0C_boulder_ball(omObjData *object) {
    if (GwPlayer[D_801097C4_boulder_ball].group == 0) {
        D_801097C4_boulder_ball++;
    }
    func_80106DAC_boulder_ball(object, D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][0],
                               D_800A178C_main[GwPlayer[D_801097C4_boulder_ball].chr][2], D_801097C4_boulder_ball);
    D_801097A4_boulder_ball[D_801097C4_boulder_ball] = D_80109738_boulder_ball.x + 80.0f;
    object->trans.x = D_80109738_boulder_ball.x;
    object->trans.y = D_80109738_boulder_ball.y;
    object->trans.z = D_80109738_boulder_ball.z;
    D_801097C4_boulder_ball++;
}

void func_80107C08_boulder_ball(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    s32 effectAttr = 0x89D;
    s32 motion = D_800A178C_main[GwPlayer[D_8010989C_boulder_ball].chr][2];
    s32 model = D_800A178C_main[GwPlayer[D_8010989C_boulder_ball].chr][0];
    s32 attr = 0xAD9;
    s32 chr;
    s32 i;

    for (i = 0; i < object->mdlcnt; i++) {
        object->model[i] = 0;
    }
    object->data = HuMemAllocTag(sizeof(func_800E1BA8_minigame_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(func_800E1BA8_minigame_ObjData));
    data = object->data;
    data->unkE8 = HuMemAllocTag(object->mtncnt * sizeof(func_800E1BA8_minigame_UnkE8_ObjData), TAG_OVERLAY);
    for (i = 0; i < object->mtncnt; i++) {
        object->motion[i] = -1;
    }
    for (i = 0; i < object->mtncnt; i++) {
        data->unkE8[i].unk00 = 0;
        data->unkE8[i].unk02 = 0;
        data->unkE8[i].unk04 = -1;
        data->unkE8[i].unk08 = -1;
    }
    chr = GwPlayer[D_8010989C_boulder_ball].chr;
    object->model[0] = func_8000B108_main(model | motion, attr | 4);
    object->model[1] = func_8000B108_main((GwPlayer[D_8010989C_boulder_ball].chr + 4) | 0x250000, attr);
    object->model[5] = func_8000B0D4_main(9, attr);
    object->model[2] = func_8000B108_main(4, effectAttr);
    object->model[3] = func_8000B108_main(4, effectAttr);
    object->model[4] = func_8000B108_main(4, effectAttr);
    Hu3DModelScaleSet(object->model[2], 2.1f, 2.1f, 2.1f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[4], 2.2f, 2.2f, 2.2f);
    func_800E5978_minigame(object, 6, func_80017BB8_main(chr, 4), 1, 0x13);
    func_800E5978_minigame(object, 0, func_80017BB8_main(chr, 0), 1, 0);
    func_800E5978_minigame(object, 0xD, func_80017BB8_main(chr, 0x2F), 1, 0x78);
    data->unk57 = GwPlayer[D_8010989C_boulder_ball].pad;
    data->unk59 = D_8010989C_boulder_ball;
    data->unk50 = 0;
    object->func = func_801083D8_boulder_ball;
    object->trans.x = 0.0f;
    object->trans.y = 700.0f;
    object->trans.z = -900.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y, object->trans.z);
    Hu3DModelScaleSet(object->model[1], 1.5f, 1.5f, 1.5f);
    Hu3DMotionSpeedSet(object->model[1], 1.5f);
    Hu3DModelPosSet(object->model[5], object->trans.x, object->trans.y, object->trans.z);
}

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109818_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109828_boulder_ball);

void func_80108000_boulder_ball(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    f32 speeds[4] = { 0.8f, 0.85f, 0.9f, 1.0f };
    f32 ranges[4] = { 100.0f, 75.0f, 50.0f, 0.0f };
    omObjData *player;
    s32 difficulty;
    s32 target;
    f32 targetX;
    f32 targetZ;
    f32 maxY;
    f32 angle;
    s32 i;

    if (data->unk50 != 1) {
        return;
    }
    target = -1;
    difficulty = GwPlayer[data->unk59].cpu_difficulty;
    D_80109894_boulder_ball = 0;
    D_8010988C_boulder_ball = 0;
    D_80109890_boulder_ball = 0;
    targetX = targetZ = 0.0f;
    maxY = -10.0f;
    for (i = 0; i < D_800EC280_minigame; i++) {
        player = D_800EC598_minigame[i];
        if (((func_800E1BA8_minigame_ObjData *)player->data)->unkBE == 0 && maxY < player->trans.y) {
            targetX = player->trans.x;
            maxY = player->trans.y;
            targetZ = player->trans.z;
            target = i;
        }
    }
    if (D_801097C8_boulder_ball == 5) {
        if (maxY < ranges[difficulty] + 300.0f) {
            if (rand8() > 128) {
                D_801097C8_boulder_ball = 3;
            } else {
                D_801097C8_boulder_ball = 4;
            }
        } else {
            D_801097C8_boulder_ball = target;
        }
    }
    switch (D_801097C8_boulder_ball) {
        case 0:
        case 1:
        case 2:
            angle = atan2df(targetX, targetZ - object->trans.z);
            if (angle > 0.0f) {
                D_80109894_boulder_ball = speeds[difficulty] * 60.0f;
                if (data->unk3C > 30.0f) {
                    D_80109890_boulder_ball |= A_BUTTON;
                }
                if (data->unk3C > angle) {
                    D_80109890_boulder_ball |= A_BUTTON;
                }
            } else {
                D_80109894_boulder_ball = speeds[difficulty] * -60.0f;
                if (data->unk3C < -30.0f) {
                    D_80109890_boulder_ball |= A_BUTTON;
                }
                if (data->unk3C < angle) {
                    D_80109890_boulder_ball |= A_BUTTON;
                }
            }
            break;
        case 3:
            D_80109894_boulder_ball = speeds[difficulty] * 60.0f;
            if (data->unk3C > speeds[difficulty] * 55.0f) {
                D_80109890_boulder_ball |= A_BUTTON;
            }
            break;
        case 4:
            D_80109894_boulder_ball = speeds[difficulty] * -60.0f;
            if (data->unk3C < speeds[difficulty] * -55.0f) {
                D_80109890_boulder_ball |= A_BUTTON;
            }
            break;
    }
    if (D_80109890_boulder_ball != 0) {
        D_801097C8_boulder_ball = 5;
    }
}

void func_801083D8_boulder_ball(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data = object->data;
    s32 player = data->unk59;
    s32 pad = data->unk57;
    A96F0_ObjData *boulderData;

    if (func_800E6E8C_minigame() != 2) {
        return;
    }
    D_80109890_boulder_ball = D_800D5558_main[pad];
    D_8010988C_boulder_ball = (u16)D_800CDA7C_main[pad];
    D_80109894_boulder_ball = D_800CBB6E_main[pad];
    D_80109898_boulder_ball = D_800D20A1_main[pad];
    D_800D20A1_main[pad] = 0;
    D_800CBB6E_main[pad] = 0;
    D_800D5558_main[pad] = 0;
    D_800CDA7C_main[pad] = 0;
    if (GwPlayer[player].stat & 1) {
        func_80108000_boulder_ball(object);
    }
    switch (data->unk50) {
        case 0:
            data->unk3C *= 0.8f;
            if (fabs(data->unk3C) < 1.0) {
                data->unk3C = 0.0f;
            }
            if (fabs(data->unk3C) < 1.0) {
                data->unk3C = 0.0f;
            }
            if (D_80109758_boulder_ball == 1) {
                data->unk50 = 1;
            }
            break;
        case 1:
            boulderData = D_801098A0_boulder_ball->data;
            data->unk3C += D_80109894_boulder_ball / 15.0f;
            if (data->unk3C > 60.0f) {
                data->unk3C = 60.0f;
            }
            if (data->unk3C < -60.0f) {
                data->unk3C = -60.0f;
            }
            if (D_80109890_boulder_ball & A_BUTTON) {
                Hu3DMotionTimeSet(object->model[1], 0.0f);
                data->unk50 = 0;
                D_80109758_boulder_ball = 0;
                boulderData->unk3C = data->unk3C;
                boulderData->unk40 = rand8() / 64.0f + 7.0f;
                boulderData->unk78 = 0;
                boulderData->unk38 = -0.75f;
                func_8004AC98_main(0x31F, player);
            }
            D_801098A0_boulder_ball->trans.x = sindf(data->unk3C) * 150.0f + 0.0f;
            D_801098A0_boulder_ball->trans.y = 700.0f;
            D_801098A0_boulder_ball->trans.z = cosdf(data->unk3C) * 150.0f + -900.0f;
            Hu3DModelPosSet(D_801098A0_boulder_ball->model[1], D_801098A0_boulder_ball->trans.x, 705.0f,
                            D_801098A0_boulder_ball->trans.z);
            boulderData->unk3C = data->unk3C;
            break;
    }
    object->rot.y = data->unk3C;
    Hu3DModelRotSet(object->model[1], 0.0f, object->rot.y, 0.0f);
    D_800D5558_main[pad] = D_80109890_boulder_ball;
    D_800CDA7C_main[pad] = D_8010988C_boulder_ball;
    D_800CBB6E_main[pad] = D_80109894_boulder_ball;
    D_800D20A1_main[pad] = D_80109898_boulder_ball;
}

void func_80108798_boulder_ball(omObjData *object) {
    func_800E1BA8_minigame_ObjData *data;
    f32 y;
    f32 velocity;
    f32 speedSq;

    if (func_800E4A90_minigame(object) & 0x20) {
        data = object->data;
        velocity = data->unk38;
        y = object->trans.y;
        if (velocity > D_800EB774_minigame) {
            velocity = D_800EB774_minigame;
        }
        speedSq = velocity * velocity;
        if (data->unk38 >= 0.0f) {
            y += speedSq * -35.0f;
        } else {
            y += speedSq * 35.0f;
        }
        data->unk38 += D_800EB748_minigame;
        if (y < 700.0f) {
            func_800E5690_minigame(object, 0);
            y = 700.0f;
        }
        object->trans.y = y;
    }
    switch (D_801097CC_boulder_ball) {
        case 1:
            Hu3DModelPosSet(object->model[2], object->trans.x - 10.0f, object->trans.y + 20.0f,
                            object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[2], 0.0f);
            func_8001C258_main(object->model[2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 4:
            Hu3DModelPosSet(object->model[3], object->trans.x + 10.0f, object->trans.y + 40.0f,
                            object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[3], 0.0f);
            func_8001C258_main(object->model[3], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
        case 6:
            Hu3DModelPosSet(object->model[4], object->trans.x, object->trans.y + 30.0f, object->trans.z + 30.0f);
            Hu3DMotionTimeSet(object->model[4], 0.0f);
            func_8001C258_main(object->model[4], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
            break;
    }
    func_800E4E30_minigame(object);
    D_801097CC_boulder_ball++;
}

void func_80108A08_boulder_ball(omObjData *object) {
    A96F0_ObjData *data;
    s32 i;

    object->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(object->data, 0, sizeof(A96F0_ObjData));
    data = object->data;
    object->model[0] = func_8000B0A0_main(0x250002, 0xAD9);
    object->model[1] = func_8000B0D4_main(9, 0xAD9);
    func_800E3584_minigame(object->model[1]);
    object->model[2] = func_8000B108_main(4, 0x89D);
    object->model[3] = func_8000B108_main(4, 0x89D);
    object->model[4] = func_8000B108_main(4, 0x89D);
    object->model[5] = func_8000B108_main(4, 0x89D);
    Hu3DModelScaleSet(object->model[2], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[3], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[4], 2.0f, 2.0f, 2.0f);
    Hu3DModelScaleSet(object->model[5], 2.0f, 2.0f, 2.0f);
    object->func = func_800D6B70_minigame;
    data->unk44 = 0.3f;
    data->unk48 = 70.0f;
    data->unk34 = 180.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = 7;
    data->unk7C = 0;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    data->unk74 = 0.5f;
    data->unk56 = D_801097D0_boulder_ball;
    data->unk54 = 1;
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
    func_800E149C_minigame(object, 0, 1);
    func_800E149C_minigame(object, 1, 2);
    object->trans.x = 0.0f;
    object->trans.y = 700.0f;
    object->trans.z = -600.0f;
    object->scale.x = object->scale.y = object->scale.z = 1.0f;
    func_80088700_main(Hu3DData[object->model[1]].mtx, 2.0f, 2.0f, 2.0f);
    D_801097D0_boulder_ball++;
    func_800D861C_minigame(data, 2, func_80108CF4_boulder_ball);
    func_800D861C_minigame(data, 0, func_80108E5C_boulder_ball);
    // The return value of slot 1 is ignored by func_800D6B70_minigame.
    func_800D861C_minigame(data, 1, (void *)func_801093B8_boulder_ball);
    func_800D861C_minigame(data, 4, func_80109410_boulder_ball);
    func_800D861C_minigame(data, 5, func_801095A0_boulder_ball);
    D_800EB724_minigame = 35.0f;
}

s32 func_80108CF4_boulder_ball(omObjData *object) {
    return 1;
}

void func_80108CFC_boulder_ball(omObjData *object) {
    A96F0_ObjData *data = object->data;
    s32 slot = data->unk56;
    s32 time;
    f32 maxTime;
    f32 motTime;
    s32 i;

    if (D_80109700_boulder_ball[slot] < 4) {
        if (D_80109700_boulder_ball[slot] > 0) {
            time = func_800E6E9C_minigame();
            switch (time) {
                case 1:
                case 6:
                    maxTime = 0.0f;
                    for (i = 0; i < 4; i++) {
                        motTime = Hu3DData[object->model[i + 2]].motTime;
                        if (motTime == 0.0f) {
                            slot = i;
                            break;
                        }
                        if (maxTime < motTime) {
                            maxTime = motTime;
                            slot = i;
                        }
                    }
                    Hu3DModelPosSet(object->model[slot + 2], object->trans.x, time * 10.0f + object->trans.y,
                                    object->trans.z);
                    Hu3DMotionTimeSet(object->model[slot + 2], 0.0f);
                    func_8001C258_main(object->model[slot + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108E5C_boulder_ball);

void func_801093B8_boulder_ball(omObjData *arg0) {
    A96F0_ObjData *data = arg0->data;

    data->unk40 += 0.3f;
    data->unk78++;
    if (35.0f < data->unk40) {
        data->unk40 = 35.0f;
    }
}

s32 func_80109410_boulder_ball(omObjData *object) {
    A96F0_ObjData *data = object->data;
    s32 slot = data->unk56;
    f32 maxTime;
    f32 motTime;
    s32 i;

    if (D_80109700_boulder_ball[slot] == 3 && data->unk38 > 0.4f) {
        slot = 0;
        maxTime = 0.0f;
        for (i = 0; i < 4; i++) {
            motTime = Hu3DData[object->model[i + 2]].motTime;
            if (motTime == 0.0f) {
                slot = i;
                break;
            }
            if (maxTime < motTime) {
                maxTime = motTime;
                slot = i;
            }
        }
        Hu3DModelPosSet(object->model[slot + 2], object->trans.x, object->trans.y + 10.0f, object->trans.z);
        Hu3DMotionTimeSet(object->model[slot + 2], 0.0f);
        func_8001C258_main(object->model[slot + 2], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    data->unk38 = rand8() / 500.0f + 0.0f;
    return 1;
}

s32 func_801095A0_boulder_ball(omObjData *object) {
    A96F0_ObjData *data = object->data;
    Vec pos;
    Vec dir;
    Vec out;
    f32 dot;
    s32 i;

    pos.x = D_800EC298_minigame[0].x;
    pos.y = dir.y = 0.0f;
    pos.z = D_800EC298_minigame[0].z;
    dir.x = sindf(data->unk3C + 180.0f);
    dir.z = cosdf(data->unk3C + 180.0f);
    dot = HuVecDot3F(&pos, &dir);
    pos.x = dot * pos.x;
    pos.z = dot * pos.z;
    HuVecSubtract(&out, &pos, &dir);
    HuVecAdd(&out, &pos, &out);
    data->unk3C = atan2df(out.x, out.z);
    for (i = 0; i < 4; i++) {
        omVibrate(i, 2, 3, 10);
    }
    HuAudFXPanning(HuAudFXPlay(0x31E), pos.x > 0.0f ? 0x20 : 0x60);
    return 1;
}
