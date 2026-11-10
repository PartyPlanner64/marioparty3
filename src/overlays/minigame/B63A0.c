#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"

extern u8 D_800EB739_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;

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

void func_800E39CC_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2,
                            s16 arg3, s16 arg4) {
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

void func_800E3B98_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2,
                            f32 arg3, f32 arg4, f32 arg5) {
    if (arg1->unk104[6] != NULL && arg1->unk104[6](arg0, arg2) == 1) {
        return;
    }
    arg1->unk38 = -D_800EB744_minigame * 0.6f;
    func_800E4C88_minigame(arg0, 7, arg3, arg4, arg5, 0.0f, 0.0f);
    func_800E4C88_minigame(arg0, 8, arg3, arg4, arg5, 0.0f, 0.0f);
    arg1->unk50 |= 0x80;
    func_800E19FC_minigame(arg1, 0xB);
    omVibrate(arg1->unk59, 10, 0, 10);
}

void func_800E3CA0_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2,
                            f32 arg3, f32 arg4, f32 arg5) {
    if (arg1->unk104[7] != NULL && arg1->unk104[7](arg0, arg2) == 1) {
        return;
    }
    func_800E5690_minigame(arg0, 0x12);
    func_800E4C88_minigame(arg0, 8, arg3, arg4, arg5, 0.0f, 0.0f);
    arg1->unk50 &= ~0x80;
}

void func_800E3D3C_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1) {
    if (arg1->unk104[14] != NULL && arg1->unk104[14](arg0) == 1) {
        return;
    }
    if (arg1->unk50 & 0x10) {
        if (func_800E5690_minigame(arg0, 0x14) == 1) {
            arg1->unk38 = -D_800EB744_minigame * 0.4f;
            func_800E2E98_minigame(arg0);
            func_800E19FC_minigame(arg1, 0xC);
        }
    } else if (func_800E5690_minigame(arg0, 7) == 1) {
        arg1->unk38 = -D_800EB744_minigame * 0.4f;
        func_800E19FC_minigame(arg1, 6);
    }
}

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

void func_800E3FD8_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData;
    omObjData *other;
    f32 time;
    f32 dx, dy, dz;
    s32 i;

    if (data->unk104[12] != NULL && data->unk104[12](arg0, &x, &y, &z) == 1) {
        return;
    }
    Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 30.0f && time <= 50.0f) {
        x += sindf(data->unk3C) * (data->unk6C + data->unk48);
        z += cosdf(data->unk3C) * (data->unk6C + data->unk48);
        for (i = 0; i < D_800EC280_minigame; i++) {
            other = D_800EC598_minigame[i];
            otherData = other->data;
            if (data == otherData) {
                continue;
            }
            dx = other->trans.x - x;
            dy = other->trans.y - y;
            dz = other->trans.z - z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + data->unk70) {
                func_800E561C_minigame(other, 1);
                func_800E5690_minigame(other, 0);
                func_800E4C88_minigame(arg0, 7, x, y, z, 0.0f, 0.0f);
            }
        }
    }
}

void func_800E4248_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData;
    omObjData *other;
    f32 time;
    f32 angle;
    f32 dx, dy, dz;
    s32 i;

    if (data->unk104[13] != NULL && data->unk104[13](arg0, &x, &y, &z) == 1) {
        return;
    }
    Hu3DData[arg0->model[0]].motIdShape = 0xFF;
    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 10.0f && time <= 25.0f) {
        angle = data->unk3C - 90.0f + (time - 10.0f) * 12.0f;
        x += sindf(angle) * (data->unk6C + data->unk48);
        z += cosdf(angle) * (data->unk6C + data->unk48);
        for (i = 0; i < D_800EC280_minigame; i++) {
            other = D_800EC598_minigame[i];
            otherData = other->data;
            if (data == otherData) {
                continue;
            }
            dx = other->trans.x - x;
            dy = other->trans.y - y;
            dz = other->trans.z - z;
            if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + data->unk70) {
                func_800E5690_minigame(other, 0x25);
                otherData->unk40 = D_800EB760_minigame + D_800EB760_minigame;
                otherData->unk3C = func_800202A8_main(atan2df(dx, dz) + 90.0f);
                otherData->unkC0 = 90;
            }
        }
    }
}

s32 func_800E4510_minigame(omObjData *arg0, omObjData *arg1) {
    func_800E1BA8_minigame_ObjData *temp_v0 = arg0->data;

    if (temp_v0->unk104[16] != NULL) {
        if (temp_v0->unk104[16](arg0, arg1) == 1) {
            return 0;
        }
    }
    return 1;
}

void func_800E454C_minigame(omObjData *arg0, omObjData *arg1, f32 x, f32 z, u16 arg4) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData = arg1->data;
    f32 dot;

    if (data->unk104[17] != NULL && data->unk104[17](arg0, arg1) == 1) {
        return;
    }
    if (!(otherData->unk50 & 0x200)) {
        dot = func_800E2ED4_minigame(sindf(otherData->unk3C), cosdf(otherData->unk3C), x, z);
        if (otherData->unk50 & 0x10) {
            func_800E2CA4_minigame(arg1, D_800EB768_minigame);
        }
        if (dot < 0.0f) {
            func_800E5690_minigame(arg1, 0x1E);
            if (otherData->unk38 == 1000.0f) {
                otherData->unk40 = -D_800EB760_minigame;
            } else {
                otherData->unk40 = -D_800EB760_minigame;
                otherData->unk38 = -D_800EB744_minigame * 0.6f;
            }
            otherData->unk3C = func_800202A8_main(data->unk3C + 180.0f);
        } else {
            func_800E5690_minigame(arg1, 0x1F);
            if (otherData->unk38 == 1000.0f) {
                otherData->unk40 = D_800EB760_minigame;
            } else {
                otherData->unk40 = D_800EB760_minigame;
                otherData->unk38 = -D_800EB744_minigame * 0.6f;
            }
            otherData->unk3C = data->unk3C;
        }
        func_800E4C88_minigame(arg0, 6, arg1->trans.x, arg1->trans.y, arg1->trans.z, 0.0f, atan2df(x, z) + 180.0f);
        func_800E19FC_minigame(data, 8);
        omVibrate(data->unk59, 2, 3, 10);
        omVibrate(otherData->unk59, 20, 0, 20);
    }
    data->unk53[1] = arg4;
    otherData->unkC3 = data->unk59;
}

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

void func_800E4890_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 groundY, Vec *normal) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 scale;

    if (data->unk104[18] != NULL && data->unk104[18](arg0, &x, &y, &z, &groundY, normal) == 1) {
        return;
    }
    if (groundY != -65536.0f) {
        if (y != groundY) {
            if (D_800EB739_minigame == 1) {
                groundY += 2.0f;
            }
            Hu3DModelPosSet(arg0->model[1], x, groundY, z);
            groundY = y - groundY;
            if (groundY > 200.0f) {
                scale = 0.6f;
            } else {
                scale = 1.0 - fabs(groundY) / 500.0;
            }
            Hu3DModelScaleSet(arg0->model[1], scale, scale, scale);
        } else {
            if (D_800EB739_minigame == 1) {
                groundY += 2.0f;
            }
            Hu3DModelPosSet(arg0->model[1], x, groundY, z);
        }
        func_800E3628_minigame(arg0->model[1], normal);
        func_8001C258_main(arg0->model[1], 4, 0);
    } else {
        func_8001C258_main(arg0->model[1], 4, 4);
    }
}
