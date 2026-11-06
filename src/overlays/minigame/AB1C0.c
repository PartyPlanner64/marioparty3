#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"

typedef struct {
    /* 0x00 */ char unk00[4];
    /* 0x04 */ u8 unk04;
} func_800D8778_minigame_ObjData;

extern Vec D_800EBDD0_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_800EC298_minigame[];

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8640_minigame);

f32 func_800D8778_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2, f32 arg3, Vec *arg4) {
    func_800D8778_minigame_ObjData *data = arg0->data;
    Vec unused;

    if ((arg2 < arg3 + arg1->unk34) & (arg3 < arg2)) {
        if (arg4->y < 0.0f) {
            unused.x = 0.0f;
            unused.y = arg2;
            unused.z = 0.0f;
            arg1->unk8C = arg2;
            arg1->unk53[3] = data->unk04;
            (void)unused;
            return -65536.0f;
        }
    }
    return arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D8818_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D89CC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9028_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D972C_minigame);

f32 func_800D9F10_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    u8 player = data->unk53[0];
    f32 ret = arg0->trans.y;

    if (data->unk00[player] & 2) {
        ret = arg1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800D9F3C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA054_minigame);

f32 func_800DA204_minigame(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal) {
    f32 ax = p->x - x;
    f32 ay = p->y - y;
    f32 az = p->z - z;
    f32 bx = q->x - x;
    f32 by = q->y - y;
    f32 bz = q->z - z;

    return (ay * bz - az * by) * normal->x + (az * bx - ax * bz) * normal->y + (ax * by - ay * bx) * normal->z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA2E0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA540_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DA768_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB628_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB704_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DB724_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DBCF4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC354_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC7D8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DC8E4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCA34_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DCCB0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD1F4_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DD530_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDB60_minigame);

void func_800DDD70_minigame(omObjData *arg0) {
    D_800EBDD0_minigame.x = arg0->trans.x;
    D_800EBDD0_minigame.y = arg0->trans.y;
    D_800EBDD0_minigame.z = arg0->trans.z;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DDD94_minigame);

void func_800DFCDC_minigame(f32 x, f32 z, f32 scale) {
    Vec dir;

    dir.x = x;
    dir.y = 0.0f;
    dir.z = z;
    func_800202FC_main(&dir);
    D_800EBE2C_minigame += scale * dir.x;
    D_800EC5D8_minigame += scale * dir.z;
}

f32 func_800DFD48_minigame(f32 arg0) {
    if (arg0 < D_800EB76C_minigame) {
        return D_800EB76C_minigame;
    }
    if (arg0 < D_800EB768_minigame) {
        return D_800EB768_minigame;
    }
    if (arg0 < D_800EB764_minigame) {
        return D_800EB764_minigame;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFD9C_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFE44_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800DFF3C_minigame);

void func_800E0430_minigame(f32 x, f32 y, f32 z) {
    D_800EC298_minigame[D_800EB736_minigame].x = x;
    D_800EC298_minigame[D_800EB736_minigame].y = y;
    D_800EC298_minigame[D_800EB736_minigame].z = z;
    func_800202FC_main(&D_800EC298_minigame[D_800EB736_minigame]);
}

void func_800E048C_minigame(f32 arg0, f32 arg1, s32 arg2) {
    D_800EBEB8_minigame[D_800EB736_minigame].unk00 = arg0;
    D_800EBEB8_minigame[D_800EB736_minigame].unk04 = arg1;
    D_800EBEB8_minigame[D_800EB736_minigame].unk08 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/AB1C0", func_800E04C8_minigame);
