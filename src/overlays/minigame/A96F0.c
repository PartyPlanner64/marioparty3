#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"
#include "gcc/memory.h"
#include "game/hmfspr.h"
#include "game/mallocblock.h"
#include "game/util.h"

typedef struct A96F0_ObjData A96F0_ObjData;

// Per-object data (omObjData.data) of the objects driven by this file.
struct A96F0_ObjData {
    /* 0x00 */ char unk00[0x21];
    /* 0x21 */ u8 unk21[4];
    /* 0x25 */ char unk25[0xF];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ s8 unk54;
    /* 0x55 */ char unk55[3];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ char unk6C[4];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ char unk74[4];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])(omObjData *);
    /* 0xA8 */ void *unkA8;
}; // Size 0xAC

typedef struct A96F0_Sphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} A96F0_Sphere; // Size 0x10

extern f32 D_800EB724_minigame;
extern f32 D_800EB728_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_800EC298_minigame[];
extern u8 D_800EB739_minigame;

void func_800D6F20_minigame(omObjData *arg0, A96F0_Sphere *arg1);
f32 func_800D72B0_minigame(omObjData *arg0, A96F0_Sphere *arg1);
void func_800D7388_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_800D74AC_minigame(omObjData *arg0, A96F0_Sphere *arg1, Vec *normal);
void func_800D7AA8_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800D7C14_minigame(omObjData *arg0, A96F0_Sphere *arg1);
void func_800E1594_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800E1718_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800E17F4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E3628_minigame(s16 model, Vec *normal);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6B70_minigame);

f32 func_800D6E14_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    A96F0_ObjData *data = arg0->data;
    A96F0_Sphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = data->unk48;
    func_800D7AA8_minigame(arg0, x, y, z);
    func_800D7C14_minigame(arg0, &sphere);
    return func_800D72B0_minigame(arg0, &sphere);
}

void func_800D6E74_minigame(omObjData *arg0, A96F0_Sphere *arg1) {
    A96F0_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *other;

    if (data->unk53 >= 0 && data->unk38 == 1000.0f) {
        other = D_800EC1C0_minigame[data->unk53]->data;
        data->unk5C = arg1->pos.x * other->unk10;
        data->unk60 = arg1->pos.y;
        data->unk64 = arg1->pos.z * other->unk10;
        if (other->unk06 & 0x400) {
            func_800D6F20_minigame(arg0, arg1);
        }
    } else {
        data->unk5C = 0.0f;
        data->unk60 = 0.0f;
        data->unk64 = 0.0f;
    }
}

void func_800D6F20_minigame(omObjData *arg0, A96F0_Sphere *arg1) {
    A96F0_ObjData *data = arg0->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    rotX = -(atan2df(arg1->pos.y, arg1->pos.z) - 90.0f);
    rotZ = atan2df(arg1->pos.y, arg1->pos.x) - 90.0f;
    curX = data->unk68;
    curZ = data->unk70;
    if (curX < rotX) {
        data->unk68 += D_800EB728_minigame;
        if (rotX < data->unk68) {
            data->unk68 = rotX;
        }
    } else if (rotX < curX) {
        data->unk68 -= D_800EB728_minigame;
        if (data->unk68 < rotX) {
            data->unk68 = rotX;
        }
    }
    if (curZ < rotZ) {
        data->unk70 += D_800EB728_minigame;
        if (rotZ < data->unk70) {
            data->unk70 = rotZ;
        }
    } else if (rotZ < curZ) {
        data->unk70 -= D_800EB728_minigame;
        if (data->unk70 < rotZ) {
            data->unk70 = rotZ;
        }
    }
    arg0->rot.x = data->unk68;
    arg0->rot.z = data->unk70;
}

void func_800D7084_minigame(A96F0_ObjData *arg0) {
    if (__builtin_fabs((f64)arg0->unk5C) > 1.0) {
        D_800EBE2C_minigame += arg0->unk5C * arg0->unk58;
    }
    if (__builtin_fabs((f64)arg0->unk64) > 1.0) {
        D_800EC5D8_minigame += arg0->unk64 * arg0->unk58;
    }
}

void func_800D710C_minigame(omObjData *arg0) {
    A96F0_ObjData *data = arg0->data;
    f32 temp;

    if (data->unk53 != -1) {
        if (data->unk84[2] != NULL && data->unk84[2](arg0) == 1) {
            return;
        }
        temp = ((func_800E1BA8_minigame_ObjData *)D_800EC1C0_minigame[data->unk53]->data)->unk08;
        if (temp != 0.0f) {
            data->unk40 -= temp;
        } else {
            data->unk40 -= D_800EB740_minigame;
        }
        if (data->unk40 < D_800EB770_minigame) {
            data->unk40 = D_800EB770_minigame;
        }
        if (data->unk40 > D_800EB724_minigame) {
            data->unk40 = D_800EB724_minigame;
        }
    }
}

void func_800D71F0_minigame(omObjData *arg0) {
    A96F0_ObjData *data = arg0->data;
    Vec dir;

    if (data->unk84[3] != NULL && data->unk84[3](arg0) == 1) {
        return;
    }
    dir.x = -D_800EBE2C_minigame;
    dir.y = 0.0f;
    dir.z = -D_800EC5D8_minigame;
    func_800202FC_main(&dir);
    dir.x = sindf(data->unk3C) - dir.x / 20.0f;
    dir.z = cosdf(data->unk3C) - dir.z / 20.0f;
    data->unk3C = atan2df(dir.x, dir.z);
}

f32 func_800D72B0_minigame(omObjData *arg0, A96F0_Sphere *arg1) {
    A96F0_ObjData *data = arg0->data;
    f32 y = arg1->pos.y;
    Vec normal;
    f32 floorY;
    f32 newY;

    newY = func_800D74AC_minigame(arg0, arg1, &normal);
    floorY = newY;
    if (newY < y - data->unk34 || y + data->unk34 <= newY) {
        if (data->unk38 == 1000.0f) {
            data->unk38 = 0.0f;
        }
        newY = y;
    }
    func_800D7388_minigame(arg0, arg1->pos.x, newY, arg1->pos.z, floorY, &normal);
    return newY;
}

void func_800D7388_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    A96F0_ObjData *data = arg0->data;
    f32 scale = 1.0f;
    f32 height;

    if (arg0->model[1] != 0) {
        height = y - floorY;
        if (height != 0.0f) {
            if (height > 400.0f) {
                scale = 0.6f;
            } else {
                scale = 1.0 - __builtin_fabs((f64)height) / 1000.0;
            }
            data->unk53 = -1;
        }
        Hu3DModelPosSet(arg0->model[1], x, floorY + 5.0f, z);
        Hu3DModelScaleSet(arg0->model[1], scale, 1.0f, scale);
        func_800E3628_minigame(arg0->model[1], normal);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D74AC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7AA8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7C14_minigame);

void func_800D7FA8_minigame(omObjData *arg0) {
    A96F0_ObjData *data;
    Vec wall;
    Vec dir;
    Vec reflect;
    f32 dot;

    if (D_800EB736_minigame == 0) {
        return;
    }
    data = arg0->data;
    if (data->unk84[5] != NULL && data->unk84[5](arg0) == 1) {
        return;
    }
    wall.x = D_800EC298_minigame[0].x;
    wall.y = dir.y = 0.0f;
    wall.z = D_800EC298_minigame[0].z;
    dir.x = sindf(data->unk3C + 180.0f);
    dir.z = cosdf(data->unk3C + 180.0f);
    dot = HuVecDot3F(&wall, &dir);
    wall.x = dot * wall.x;
    wall.z = dot * wall.z;
    HuVecSubtract(&reflect, &wall, &dir);
    HuVecAdd(&reflect, &wall, &reflect);
    data->unk3C = atan2df(reflect.x, reflect.z);
    data->unk40 *= 0.8f;
}

void func_800D80DC_minigame(omObjData *arg0) {
    A96F0_ObjData *data = arg0->data;
    s32 remaining;

    data->unk78++;
    if (data->unk84[7] != NULL && data->unk84[7](arg0) == 1) {
        return;
    }
    if (data->unk7C > 0) {
        remaining = data->unk7C - data->unk78;
        if (remaining < 45) {
            switch (remaining & 2) {
                case 0:
                    func_8001C258_main(arg0->model[0], 4, 4);
                    break;
                case 2:
                    func_8001C258_main(arg0->model[0], 4, 0);
                    break;
            }
            if (data->unk7C <= data->unk78) {
                data->unk54 = 0;
                func_8001C258_main(arg0->model[0], 4, 4);
                func_8001C258_main(arg0->model[1], 4, 4);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D81C8_minigame);

#ifdef NON_MATCHING
// CSE folds shadowFile | 0x400 into a constant (target keeps it as an ori from
// a saved register), and the arg1/shadowFile saved registers end up swapped.
// Placing a loop before the arg1 == 3 block avoids the folding, which hints
// that the target had a basic block boundary there.
void func_800D83D8_minigame(omObjData *arg0, s32 arg1) {
    A96F0_ObjData *data;
    s32 shadowFile = 0x299;
    s32 i;

    arg0->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(arg0->data, 0, sizeof(A96F0_ObjData));
    data = arg0->data;
    data->unkA8 = HuMemAllocTag(4, TAG_OVERLAY);
    if (arg1 == 3) {
        func_800E1594_minigame(arg0, 10, 0x689, 8);
        func_800E1718_minigame(arg0, 3, 12, shadowFile | 0x400, 8);
        func_80014794_main(data->unk21[3], 240);
        func_800147FC_main(data->unk21[3], 255, 255, 134);
    }
    if (D_800EB739_minigame == 0) {
        arg0->model[1] = func_8000B0D4_main(0, shadowFile);
    } else {
        arg0->model[1] = func_8000B0D4_main(9, shadowFile);
    }
    data->unk44 = 0.0f;
    data->unk48 = 20.0f;
    data->unk34 = 50.0f;
    data->unk3C = 0.0f;
    data->unk78 = 0;
    data->unk52 = arg1;
    data->unk7C = 300;
    data->unk50 = 0;
    data->unk40 = 0.0f;
    func_800E17F4_minigame(arg0, 2.0f, 2.0f, 2.0f);
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D83D8_minigame);
#endif

void func_800D853C_minigame(omObjData *arg0, omObjData *arg1) {
    A96F0_ObjData *data1 = arg1->data;
    A96F0_ObjData *data0 = arg0->data;

    if (data1->unk84[6] != NULL && data1->unk84[6](arg0) == 1) {
        return;
    }
    data1->unk38 = -D_800EB744_minigame * 0.6f;
    data1->unk3C = data0->unk3C;
    data1->unk40 = data0->unk40;
    if (data1->unk40 < D_800EB760_minigame) {
        data1->unk40 = D_800EB760_minigame;
    }
    data1->unk80 = 0;
    arg1->trans.x = arg0->trans.x;
    arg1->trans.y = data0->unk34 + data1->unk48 + arg0->trans.y;
    arg1->trans.z = arg0->trans.z;
}

void func_800D861C_minigame(A96F0_ObjData *arg0, s32 arg1, s32 (*arg2)(omObjData *)) {
    if (arg1 < 9) {
        arg0->unk84[arg1] = arg2;
    }
}
