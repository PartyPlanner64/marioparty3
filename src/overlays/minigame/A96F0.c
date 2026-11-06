#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"

typedef struct A96F0_ObjData A96F0_ObjData;

// Per-object data (omObjData.data) of the objects driven by this file.
struct A96F0_ObjData {
    /* 0x00 */ char unk00[0x34];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[7];
    /* 0x53 */ s8 unk53;
    /* 0x54 */ s8 unk54;
    /* 0x55 */ char unk55[3];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ char unk68[0x10];
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 (*unk84[9])(omObjData *);
}; // Size 0xA8

extern f32 D_800EB724_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB770_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6B70_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6E14_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6E74_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D6F20_minigame);

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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D72B0_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7388_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D74AC_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7AA8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7C14_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7FA8_minigame);

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

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D83D8_minigame);

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
