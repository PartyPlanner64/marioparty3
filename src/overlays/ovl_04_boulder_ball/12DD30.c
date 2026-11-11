#include "common.h"
#include "game/mallocblock.h"
#include "gcc/memory.h"
#include "overlays/minigame.h"

// Per-object state for this minigame. Lives in the `data` pointer (0x5C) of the
// omObjData for the players as well as for the boulder. func_800D6B70_minigame
// walks it every frame: it places the model using `size` scaled by sin/cos of
// `phase`, and dispatches the nine callback slots at 0x84.
typedef struct BoulderBallData {
    /* 0x00 */ char unk_00[0x38];
    /* 0x38 */ f32 unk_38;
    /* 0x3C */ f32 phase;
    /* 0x40 */ f32 size;
    /* 0x44 */ char unk_44[0x12];
    /* 0x56 */ u16 unk_56;
    /* 0x58 */ char unk_58[0x20];
    /* 0x78 */ s32 unk_78;
    /* 0x7C */ char unk_7C[0x30];
} BoulderBallData; // sizeof 0xAC

extern s32 D_800A178C_main[][6];
extern u16 D_800EC288_minigame;
extern Vec D_800EC298_minigame[];

extern s32 D_80109700_boulder_ball[8];
extern Vec D_80109720_boulder_ball;
extern Vec D_8010972C_boulder_ball;
extern Vec D_80109738_boulder_ball;
extern s32 D_8010975C_boulder_ball;
extern f32 D_801097A4_boulder_ball[4];
extern s32 D_801097C4_boulder_ball;
extern u16 D_8010988E_boulder_ball;
extern u16 D_80109892_boulder_ball;
extern s8 D_80109897_boulder_ball;
extern s8 D_8010989B_boulder_ball;

void func_80106410_boulder_ball(omObjData *object);
void func_80106DAC_boulder_ball(omObjData *object, s32 model, s32 motion, u16 player);
s32 func_8010707C_boulder_ball(omObjData *object, omObjData *other);
s32 func_80107194_boulder_ball(omObjData *object);
s32 func_80107298_boulder_ball(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801059A0_boulder_ball);

void func_80105E74_boulder_ball(omObjData *object) {
    if (WipeStatGet() == 0) {
        omOvlReturnEx(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80105EA0_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801060D0_boulder_ball);

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
        D_800D5558_main[data->unk57] = D_80109892_boulder_ball;
        D_800CDA7C_main[data->unk57] = D_8010988E_boulder_ball;
        D_800CBB6E_main[data->unk57] = D_80109897_boulder_ball;
        D_800D20A1_main[data->unk57] = D_8010989B_boulder_ball;
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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80107C08_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108000_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109818_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109828_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109838_boulder_ball);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", D_80109848_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_801083D8_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108798_boulder_ball);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_04_boulder_ball/12DD30", func_80108A08_boulder_ball);

s32 func_80108CF4_boulder_ball(void) {
    return 1;
}

void func_80108CFC_boulder_ball(omObjData *object) {
    BoulderBallData *data = OM_GET_DATA_PTR(object, BoulderBallData);
    s32 slot = data->unk_56;
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
    BoulderBallData *data = OM_GET_DATA_PTR(arg0, BoulderBallData);

    data->size += 0.3f;
    data->unk_78++;
    if (35.0f < data->size) {
        data->size = 35.0f;
    }
}

s32 func_80109410_boulder_ball(omObjData *object) {
    BoulderBallData *data = OM_GET_DATA_PTR(object, BoulderBallData);
    s32 slot = data->unk_56;
    f32 maxTime;
    f32 motTime;
    s32 i;

    if (D_80109700_boulder_ball[slot] == 3 && data->unk_38 > 0.4f) {
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
    data->unk_38 = rand8() / 500.0f + 0.0f;
    return 1;
}

s32 func_801095A0_boulder_ball(omObjData *object) {
    BoulderBallData *data = OM_GET_DATA_PTR(object, BoulderBallData);
    Vec pos;
    Vec dir;
    Vec out;
    f32 dot;
    s32 i;

    pos.x = D_800EC298_minigame[0].x;
    pos.y = dir.y = 0.0f;
    pos.z = D_800EC298_minigame[0].z;
    dir.x = sindf(data->phase + 180.0f);
    dir.z = cosdf(data->phase + 180.0f);
    dot = HuVecDot3F(&pos, &dir);
    pos.x = dot * pos.x;
    pos.z = dot * pos.z;
    HuVecSubtract(&out, &pos, &dir);
    HuVecAdd(&out, &pos, &out);
    data->phase = atan2df(out.x, out.z);
    for (i = 0; i < 4; i++) {
        omVibrate(i, 2, 3, 10);
    }
    HuAudFXPanning(HuAudFXPlay(0x31E), pos.x > 0.0f ? 0x20 : 0x60);
    return 1;
}
