#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"
#include "gcc/memory.h"
#include "game/hmfspr.h"
#include "game/mallocblock.h"
#include "game/util.h"

typedef struct A96F0_Sphere {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
} A96F0_Sphere; // Size 0x10

extern f32 D_800EB720_minigame;
extern f32 D_800EB724_minigame;
extern f32 D_800EB728_minigame;
extern f32 D_800EB72C_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB770_minigame;
extern Vec D_800EBDC0_minigame;
extern f32 D_800EBE2C_minigame;
extern f32 D_800EC5D8_minigame;
extern Vec D_800EC298_minigame[];
extern u8 D_800EB739_minigame;
extern HuMtx4F D_800EBE30_minigame;
extern Hu3DQuadPool D_800EBEB0_minigame;
extern HuMtx4F D_800EC240_minigame;

f32 func_800D6E14_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800D6E74_minigame(omObjData *arg0, Vec *arg1);
void func_800D6F20_minigame(omObjData *arg0, Vec *arg1);
f32 func_800D72B0_minigame(omObjData *arg0, A96F0_Sphere *arg1);
void func_800D7388_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_800D74AC_minigame(omObjData *arg0, A96F0_Sphere *arg1, Vec *normal);
void func_800D7084_minigame(A96F0_ObjData *arg0);
void func_800D710C_minigame(omObjData *arg0);
void func_800D71F0_minigame(omObjData *arg0);
void func_800D7AA8_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800D7C14_minigame(omObjData *arg0, A96F0_Sphere *arg1);
void func_800DFCDC_minigame(f32 x, f32 z, f32 scale);
void func_800E1594_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800D80DC_minigame(omObjData *arg0);
void func_800D7FA8_minigame(omObjData *arg0);
void func_800DC354_minigame(omObjData *arg0, A96F0_Sphere *arg1, Vec *arg2);
void func_800DCCB0_minigame(omObjData *arg0, A96F0_Sphere *arg1, Vec *arg2, f32 arg3);
void func_800DC7D8_minigame(omObjData *arg0, A96F0_Sphere *arg1);
void func_800DC8E4_minigame(omObjData *arg0, A96F0_Sphere *arg1, f32 arg2);
void func_800E28BC_minigame(HuMtx4F mtx, HuMtx4F result, Vec *pos, omObjData *obj);
void func_800E2B58_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2BD4_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1);
s32 func_800E2F40_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos);
s32 func_800E30B8_minigame(Vec *pos, func_800E1BA8_minigame_ObjData *data);
s32 func_800DB704_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
s32 func_800E2FD8_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos, f32 margin);
void func_800E1718_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800E17D4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E17F4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E3628_minigame(s16 model, Vec *normal);

void func_800D6B70_minigame(omObjData *arg0) {
    A96F0_ObjData *data = arg0->data;
    s32 result = 0;
    f32 x, y, z;
    f32 angle;
    f32 floorY;

    if (data->unk50 & 0x20) {
        if (data->unk50 & 0x10) {
            return;
        }
    }
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
    D_800EBDC0_minigame.x = x = arg0->trans.x;
    D_800EBDC0_minigame.y = y = arg0->trans.y;
    D_800EBDC0_minigame.z = z = arg0->trans.z;
    angle = data->unk3C;
    if (data->unk84[0] != NULL && data->unk84[0](arg0) == 1) {
        return;
    }
    x += sindf(angle) * data->unk40;
    z += cosdf(angle) * data->unk40;
    func_800D7084_minigame(data);
    if (data->unk38 != 1000.0f) {
        y += data->unk38 * data->unk38 * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
        data->unk38 += D_800EB72C_minigame;
        if (data->unk38 > D_800EB720_minigame) {
            data->unk38 = D_800EB720_minigame;
        }
        floorY = func_800D6E14_minigame(arg0, x, y, z);
        if (y < floorY) {
            if (data->unk84[4] != NULL) {
                result = data->unk84[4](arg0);
            }
            y = floorY;
            if (result != 1) {
                data->unk38 = -data->unk38 * 0.7f;
                if (data->unk38 >= -0.4f) {
                    data->unk38 = 1000.0f;
                }
                func_800D710C_minigame(arg0);
            }
        }
    } else {
        y = func_800D6E14_minigame(arg0, x, y, z);
        func_800D710C_minigame(arg0);
        func_800D71F0_minigame(arg0);
    }
    func_800E17D4_minigame(arg0, x + D_800EBE2C_minigame, y, z + D_800EC5D8_minigame);
    func_800D80DC_minigame(arg0);
    if (data->unk84[1] != NULL) {
        data->unk84[1](arg0);
    }
}

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

void func_800D6E74_minigame(omObjData *arg0, Vec *arg1) {
    A96F0_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *other;

    if (data->unk53 >= 0 && data->unk38 == 1000.0f) {
        other = D_800EC1C0_minigame[data->unk53]->data;
        data->unk5C = arg1->x * other->unk10;
        data->unk60 = arg1->y;
        data->unk64 = arg1->z * other->unk10;
        if (other->unk06 & 0x400) {
            func_800D6F20_minigame(arg0, arg1);
        }
    } else {
        data->unk5C = 0.0f;
        data->unk60 = 0.0f;
        data->unk64 = 0.0f;
    }
}

void func_800D6F20_minigame(omObjData *arg0, Vec *arg1) {
    A96F0_ObjData *data = arg0->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    rotX = -(atan2df(arg1->y, arg1->z) - 90.0f);
    rotZ = atan2df(arg1->y, arg1->x) - 90.0f;
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

f32 func_800D74AC_minigame(omObjData *arg0, A96F0_Sphere *arg1, Vec *normal) {
    A96F0_ObjData *data;
    func_800E1BA8_minigame_ObjData *objData;
    omObjData *obj;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    Vec pos;
    Vec unused1; // Unused, but needed for stack layout
    Vec unused2;
    Vec tmp;
    Vec dir;
    f32 x, y, z;
    f32 floorY;
    f32 hitY;
    s16 model;
    u8 transformed;
    s16 i;

    x = arg1->pos.x;
    y = arg1->pos.y;
    z = arg1->pos.z;
    data = arg0->data;
    floorY = -65536.0f;
    data->unk53 = -1;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        obj = D_800EC1C0_minigame[i];
        objData = obj->data;
        if (data->unk00[i] & 1) {
            continue;
        }
        pos.x = x;
        pos.y = y;
        pos.z = z;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &pos, obj);
        if (objData->unk06 & 4) {
            if (func_800E2F40_minigame(HmfModelData[obj->model[0]].hmf->unk60, &pos) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 0x7A) {
            if (objData->unk06 & 0x50) {
                if (func_800E30B8_minigame(&pos, objData) == 0) {
                    continue;
                }
            }
            hitY = objData->unk14;
            if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                pos.y = hitY;
                func_800E2C68_minigame(D_800EC240_minigame, &pos);
                hitY = pos.y;
                if (floorY <= hitY && hitY < y + 150.0f) {
                    floorY = hitY;
                    data->unk53 = i;
                    if (normal != NULL) {
                        tmp.x = 0.0f;
                        tmp.y = 1.0f;
                        tmp.z = 0.0f;
                        func_800E2B58_minigame(D_800EC240_minigame, &tmp);
                        normal->x = tmp.x;
                        normal->y = tmp.y;
                        normal->z = tmp.z;
                        func_800202FC_main(normal);
                    }
                }
            } else if (floorY <= hitY && hitY < y + 150.0f) {
                floorY = hitY;
                data->unk53 = i;
                if (normal != NULL) {
                    normal->x = 0.0f;
                    normal->y = 1.0f;
                    normal->z = 0.0f;
                }
            }
        } else {
            model = obj->model[0];
            points = (Hu3DPoint *)HmfModelData[model].hmf->unk50;
            func_80021C14_main(model, &D_800EBEB0_minigame, func_800DB704_minigame, &pos);
            for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
                 quad = func_80022198_main(&D_800EBEB0_minigame)) {
                transformed = FALSE;
                if (HmfModelData[model].pos.x != 0.0f || HmfModelData[model].pos.y != 0.0f ||
                    HmfModelData[model].pos.z != 0.0f || HmfModelData[model].rot.x != 0.0f ||
                    HmfModelData[model].rot.y != 0.0f || HmfModelData[model].rot.z != 0.0f) {
                    tmp.x = x;
                    tmp.y = y + 10.0f;
                    tmp.z = z;
                    func_800E2BD4_minigame(D_800EBE30_minigame, &tmp);
                    dir.x = tmp.x - pos.x;
                    dir.y = tmp.y - pos.y;
                    dir.z = tmp.z - pos.z;
                    func_800202FC_main(&dir);
                    func_800D8818_minigame(pos.x, pos.y, pos.z, points, quad, &dir, &pos);
                    func_800E2C68_minigame(D_800EC240_minigame, &pos);
                    hitY = pos.y;
                    transformed = TRUE;
                } else {
                    hitY = func_800204F4_main(pos.x, pos.y, pos.z, points, quad);
                }
                if (floorY <= hitY && hitY < y + 150.0f) {
                    floorY = hitY;
                    data->unk53 = i;
                    if (normal != NULL) {
                        func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           normal);
                        if (transformed == TRUE) {
                            tmp.x = normal->x;
                            tmp.y = normal->y;
                            tmp.z = normal->z;
                            func_800E2B58_minigame(D_800EC240_minigame, &tmp);
                            normal->x = tmp.x;
                            normal->y = tmp.y;
                            normal->z = tmp.z;
                            func_800202FC_main(normal);
                        }
                    }
                }
            }
        }
    }
    func_800D6E74_minigame(arg0, normal);
    return floorY;
}

#ifdef NON_MATCHING
// Float register allocation differs: target puts x/z in f30/f28 and the 0.0f
// constant in f26, but this allocates 0.0f to f30 and x/z to f28/f26.
void func_800D7AA8_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    A96F0_ObjData *data = arg0->data;
    A96F0_ObjData *otherData;
    omObjData *other;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 i;

    if ((data->unk52 & 7) != 0) {
        return;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherData = other->data;
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        dist = HuSqrtf(dx * dx + dz * dz) - (data->unk48 + otherData->unk48);
        if (dist < 0.0f && data->unk38 == 1000.0f && otherData->unk38 == 1000.0f) {
            func_800DFCDC_minigame(dx, dz, dist);
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/overlays/minigame/A96F0", func_800D7AA8_minigame);
#endif

void func_800D7C14_minigame(omObjData *arg0, A96F0_Sphere *arg1) {
    A96F0_ObjData *data = arg0->data;
    A96F0_Sphere sphere;
    func_800DBCF4_minigame_Arg local;
    omObjData *obj;
    func_800E1BA8_minigame_ObjData *objData;
    s16 count;
    s16 i;

    sphere.pos.x = arg1->pos.x;
    sphere.pos.y = data->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z;
    sphere.radius = arg1->radius;
    D_800EB736_minigame = 0;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        obj = D_800EC1C0_minigame[i];
        objData = obj->data;
        if (objData->unk06 & 2) {
            continue;
        }
        if (data->unk00[i] & 1) {
            continue;
        }
        count = D_800EB736_minigame;
        local.pos.x = local.prev.x = arg1->pos.x;
        local.pos.y = local.prev.y = data->unk34 / 2 + arg1->pos.y;
        local.pos.z = local.prev.z = arg1->pos.z;
        local.radius = sphere.radius = arg1->radius;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &local.pos, obj);
        if (objData->unk06 & 4) {
            if (func_800E2FD8_minigame(HmfModelData[obj->model[0]].hmf->unk60, &local.pos, data->unk48) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 8) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC354_minigame(obj, (A96F0_Sphere *)&local, &local.prev);
        } else if (objData->unk06 & 0x10) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(obj, (A96F0_Sphere *)&local, &local.prev, data->unk34 / 2);
        } else if (objData->unk06 & 0x20) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(obj, (A96F0_Sphere *)&local);
        } else if (objData->unk06 & 0x40) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(obj, (A96F0_Sphere *)&local, data->unk34 / 2);
        } else {
            func_80021C14_main(D_800EC1C0_minigame[i]->model[0], &D_800EBEB0_minigame,
                               (s32 (*)(s32, s16 *, Hu3DPoint *, Vec *))func_800DBCF4_minigame, &local.pos);
        }
        if (count != D_800EB736_minigame) {
            func_800E2B58_minigame(D_800EC240_minigame, &D_800EC298_minigame[count]);
        }
    }
    func_800D7FA8_minigame(arg0);
}

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

void func_800D81C8_minigame(omObjData *arg0, omObjData *arg1) {
    A96F0_ObjData *data = arg1->data;
    func_800E1BA8_minigame_ObjData *playerData = arg0->data;
    u8 sprite;
    u8 model;

    if (data->unk84[8] != NULL && data->unk84[8](arg0) == 1) {
        return;
    }
    sprite = data->unk21[3];
    model = arg1->model[3];
    func_8001C258_main(model, 4, 0);
    func_80014714_main(sprite, 0);
    func_800146DC_main(sprite, 4, 4);
    Hu3DModelPosSet(model, arg1->trans.x, arg1->trans.y, arg1->trans.z);
    Hu3DModelScaleSet(model, 5.0f, 5.0f, 5.0f);
    switch (data->unk52) {
        case 3:
            GwPlayer[playerData->unk59].gameCoin += 1;
            HuAudFXPlay(0);
            break;
        case 4:
            GwPlayer[playerData->unk59].gameCoin += 3;
            HuAudFXPlay(0);
            break;
        case 5:
            GwPlayer[playerData->unk59].gameCoin += 2;
            HuAudFXPlay(0);
            break;
        case 6:
            GwPlayer[playerData->unk59].gameCoin += 5;
            HuAudFXPlay(0);
            omVibrate(playerData->unk59, 2, 3, 10);
            break;
    }
    data->unk54 = 0;
    data->unk78 = 0;
    func_8001C258_main(arg1->model[0], 4, 4);
    func_8001C258_main(arg1->model[1], 4, 4);
}

void func_800D83D8_minigame(omObjData *arg0, s32 arg1) {
    A96F0_ObjData *data;
    s32 shadowFile = 0x299;
    s32 i;

    arg0->data = HuMemAllocTag(sizeof(A96F0_ObjData), TAG_OVERLAY);
    memset(arg0->data, 0, sizeof(A96F0_ObjData));
    data = arg0->data;
    data->unkA8 = HuMemAllocTag(4, TAG_OVERLAY);
    // Empty loop needed to match; keeps shadowFile | 0x400 from being
    // constant-folded.
    for (i = 0; i < 0; i++) {
    }
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
    data1->unk80 = NULL;
    arg1->trans.x = arg0->trans.x;
    arg1->trans.y = data0->unk34 + data1->unk48 + arg0->trans.y;
    arg1->trans.z = arg0->trans.z;
}

void func_800D861C_minigame(A96F0_ObjData *arg0, s32 arg1, s32 (*arg2)(omObjData *)) {
    if (arg1 < 9) {
        arg0->unk84[arg1] = arg2;
    }
}
