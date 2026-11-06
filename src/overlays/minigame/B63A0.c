#include "common.h"
#include "overlays/minigame.h"

extern f32 D_800EB744_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;

void func_800DFE44_minigame(omObjData *);
void func_800DFF3C_minigame(omObjData *, f32, f32, f32);
void func_800E19FC_minigame(func_800E1BA8_minigame_ObjData *, s32);
void func_800E23E0_minigame(omObjData *);
void func_800E2CA4_minigame(omObjData *, f32);
void func_800E2E98_minigame(omObjData *);
void func_800E3928_minigame(omObjData *, func_800E1BA8_minigame_ObjData *);
void func_800E3EA4_minigame(omObjData *, func_800E1BA8_minigame_ObjData *);
void func_800E4C88_minigame(omObjData *, u8, f32, f32, f32, f32, f32);

void func_800E3820_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (arg1->unk50 & 0x40) {
        if (arg1->unk38 == 1000.0f) {
            if (arg1->unk104[10] == NULL || arg1->unk104[10](arg0) != 1) {
                func_800E5690_minigame(arg0, 0x23);
            }
        }
    } else {
        func_800E3928_minigame(arg0, arg1);
    }
}

void func_800E38A4_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (arg1->unk50 & 0x40) {
        if (arg1->unk38 == 1000.0f) {
            if (arg1->unk104[11] == NULL || arg1->unk104[11](arg0) != 1) {
                func_800E5690_minigame(arg0, 0x24);
            }
        }
    } else {
        func_800E3EA4_minigame(arg0, arg1);
    }
}

void func_800E3928_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (arg1->unk104[2] != NULL && arg1->unk104[2](arg0) == 1) {
        return;
    }
    if (arg1->unkB0 == 1.0f) {
        if (func_800E5690_minigame(arg0, 6) == 1) {
            arg1->unk38 = -D_800EB744_minigame;
            arg1->unk50 &= ~0x80;
            func_800E19FC_minigame(arg1, 3);
        }
    }
}

void func_800E39CC_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, s32 arg2, s16 arg3, s16 arg4) {
    if (arg1->unk104[3] != NULL && arg1->unk104[3](arg0, arg2) == 1) {
        return;
    }
    if (abs(arg3) < 8 && abs(arg4) < 8) {
        arg1->unk40 = D_800EB770_minigame;
        func_800E5690_minigame(arg0, 0x15);
        func_800E19FC_minigame(arg1, 4);
        func_800E23E0_minigame(arg0);
    } else {
        func_800E5690_minigame(arg0, 1);
        arg1->unk40 = D_800EB764_minigame;
        func_800E19FC_minigame(arg1, 1);
    }
}

void func_800E3AB8_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (func_800E5690_minigame(arg0, 8) != 1) {
        return;
    }
    if (arg1->unk104[5] != NULL && arg1->unk104[5](arg0) == 1) {
        return;
    }
    arg1->unk40 = D_800EB770_minigame;
    arg1->unk38 = -D_800EB744_minigame * 0.1f;
    if (arg1->unk50 & 0x10) {
        func_800E2CA4_minigame(arg0, D_800EB76C_minigame * 0.6f);
    }
    func_800E19FC_minigame(arg1, 0xA);
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3B98_minigame);

void func_800E3CA0_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, s32 arg2, f32 arg3, f32 arg4,
                            f32 arg5) {
    if (arg1->unk104[7] != NULL && arg1->unk104[7](arg0, arg2) == 1) {
        return;
    }
    func_800E5690_minigame(arg0, 0x12);
    func_800E4C88_minigame(arg0, 8, arg3, arg4, arg5, 0.0f, 0.0f);
    arg1->unk50 &= ~0x80;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3D3C_minigame);

void func_800E3E24_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;

    if (data->unk104[15] != NULL && data->unk104[15](arg0) == 1) {
        return;
    }
    func_800DFF3C_minigame(arg0, arg1, arg2, arg3);
}

void func_800E3EA4_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (arg1->unk104[8] != NULL && arg1->unk104[8](arg0) == 1) {
        return;
    }
    if (arg1->unk50 & 0x10) {
        if (func_800E5690_minigame(arg0, 0x14) == 1) {
            func_800E2E98_minigame(arg0);
            func_800E19FC_minigame(arg1, 0xC);
        }
    } else if (func_800E5690_minigame(arg0, 5) == 1) {
        func_800E19FC_minigame(arg1, 5);
    }
}

void func_800E3F44_minigame(omObjData *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;

    if (data->unk104[9] != NULL && data->unk104[9](arg0) == 1) {
        return;
    }
    if (arg1 & 0x80) {
        func_800DFE44_minigame(arg0);
    } else {
        func_800DFF3C_minigame(arg0, arg2, arg3, arg4);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E3FD8_minigame);

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E4248_minigame);

s32 func_800E4510_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    if (temp_v0->unk104[16] != NULL) {
        if (temp_v0->unk104[16](arg0) == 1) {
            return 0;
        }
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E454C_minigame);

void func_800E47D8_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;

    if (data->unk104[4] != NULL && data->unk104[4](arg0, &arg1) == 1) {
        return;
    }
    if (data->unk38 == 1000.0f) {
        data->unkB0 = (data->unk8C - arg1) / data->unk34;
    } else if (data->unk38 < 0.0f) {
        data->unk38 = D_800EB744_minigame * 0.1f;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/minigame/B63A0", func_800E4890_minigame);
