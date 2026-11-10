#include "common.h"
#include "overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/hu3d.h"
#include "game/mapspace.h"
#include "math.h"

extern Vec D_800EBDD0_minigame;
extern u8 D_800EB73B_minigame;
extern f32 D_800EB740_minigame;
extern f32 D_800EB74C_minigame;
extern f32 D_800EB750_minigame;
extern f32 D_800EB754_minigame;
extern f32 D_800EB758_minigame;
extern f32 D_800EB75C_minigame;
extern f32 D_800EB760_minigame;
extern f32 D_800EB764_minigame;
extern f32 D_800EB768_minigame;
extern f32 D_800EB76C_minigame;
extern f32 D_800EB770_minigame;
extern Vec D_800EC298_minigame[];
extern omObjData *D_800EBE70_minigame[];
extern s8 D_800EC286_minigame;
extern u16 D_800EC288_minigame;
extern u8 D_800EB734_minigame;
extern Vec D_800EC28C_minigame[];
extern s8 D_800EB738_minigame;
extern f32 D_800EB778_minigame;
extern s8 D_800EB780_minigame;

f32 func_800D8640_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2) {
    D_800EC1C0_minigame_ObjData *data = arg0->data;
    Vec pos;
    f32 y;

    if (data->unk06 & 0x50) {
        y = data->unk14 - data->unk98;
        if ((y < arg2 + arg1->unk34) & (arg2 < y)) {
            pos.x = 0.0f;
            pos.y = y;
            pos.z = 0.0f;
            if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
                arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
                func_800E2C68_minigame(D_800EC240_minigame, &pos);
            }
            arg1->unk8C = pos.y;
            arg1->unk53[3] = data->unk04;
        }
    }
    return data->unk14;
}

f32 func_800D8778_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2, f32 arg3, Vec *arg4) {
    D_800EC1C0_minigame_ObjData *data = arg0->data;
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

f32 func_800D8818_minigame(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out) {
    Vec normal;
    Hu3DPoint *p0 = &points[quad->vtx[1]];
    f32 px = p0->x;
    f32 py = p0->y;
    f32 pz = p0->z;
    f32 dx = dir->x;
    f32 dy = dir->y;
    f32 dz = dir->z;
    f32 nx, ny, nz;
    f32 denom;
    f32 t;

    func_8002038C_main(p0, &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    nx = normal.x;
    ny = normal.y;
    nz = normal.z;
    denom = nx * dx + ny * dy + nz * dz;
    t = (nx * (px - x) + ny * (py - y) + nz * (pz - z)) / denom;
    out->x = x += dx * t;
    out->y = y += dy * t;
    out->z = z += dz * t;
    return y;
}

f32 func_800D89CC_minigame(omObjData *arg0, f32 x, f32 y, f32 z, Vec *normal) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    Hu3DSphere sphere;
    Vec tmp;
    Vec dir;
    omObjData *obj;
    D_800EC1C0_minigame_ObjData *objData;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 best;
    f32 height;
    u8 transformed;
    s16 i;

    best = -65536.0f;
    sphere.radius = 10.0f;
    data->unk53[0] = -1;
    for (i = 0; i < D_800EBE28_minigame; i++) {
        obj = D_800EC1C0_minigame[i];
        objData = obj->data;
        if (i == D_800EB734_minigame) {
            continue;
        }
        if (data->unk00[i] & 1) {
            continue;
        }
        sphere.pos.x = x;
        sphere.pos.y = y;
        sphere.pos.z = z;
        func_800E28BC_minigame(D_800EC240_minigame, D_800EBE30_minigame, &sphere.pos, obj);
        if (objData->unk06 & 4) {
            if (func_800E2F40_minigame(Hu3DData[obj->model[0]].hmf->unk60, &sphere.pos) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 0x7A) {
            if (objData->unk06 & 0x50) {
                if (func_800E30B8_minigame(&sphere.pos, objData) == 0) {
                    continue;
                }
            }
            height = func_800D8640_minigame(obj, data, sphere.pos.y);
            if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                sphere.pos.y = height;
                func_800E2C68_minigame(D_800EC240_minigame, &sphere.pos);
                height = sphere.pos.y;
                if (height >= best && height < y + 150.0f) {
                    best = height;
                    data->unk53[0] = D_800EB738_minigame = i;
                    if (normal != NULL) {
                        normal->z = normal->x = 0.0f;
                        normal->y = 1.0f;
                        func_800E2B58_minigame(D_800EC240_minigame, normal);
                        func_800202FC_main(normal);
                    }
                }
            } else if (height >= best && height < y + 150.0f) {
                best = height;
                D_800EB738_minigame = i;
                data->unk53[0] = i;
                if (normal != NULL) {
                    normal->x = 0.0f;
                    normal->y = 1.0f;
                    normal->z = 0.0f;
                }
            }
        } else {
            points = (Hu3DPoint *)Hu3DData[obj->model[0]].hmf->unk50;
            func_80021C14_main(obj->model[0], &D_800EBEB0_minigame, func_800DB704_minigame, &sphere.pos);
            for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
                 quad = func_80022198_main(&D_800EBEB0_minigame)) {
                transformed = 0;
                if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                    obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                    tmp.x = x;
                    tmp.y = y + 101.23f;
                    tmp.z = z;
                    func_800E2BD4_minigame(D_800EBE30_minigame, &tmp);
                    dir.x = tmp.x - sphere.pos.x;
                    dir.y = tmp.y - sphere.pos.y;
                    dir.z = tmp.z - sphere.pos.z;
                    func_800202FC_main(&dir);
                    func_800D8818_minigame(sphere.pos.x, sphere.pos.y, sphere.pos.z, points, quad, &dir, &sphere.pos);
                    func_800E2C68_minigame(D_800EC240_minigame, &sphere.pos);
                    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &dir);
                    func_800E2B58_minigame(D_800EC240_minigame, &dir);
                    height = func_800D8778_minigame(obj, data, sphere.pos.y, y, &dir);
                    transformed = 1;
                } else {
                    height = func_800204F4_main(sphere.pos.x, sphere.pos.y, sphere.pos.z, points, quad);
                }
                if (height >= best && height < y + 150.0f) {
                    best = height;
                    D_800EB738_minigame = i;
                    data->unk53[0] = i;
                    if (normal != NULL) {
                        func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           normal);
                        if (transformed == 1) {
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
    return best;
}

// prevY is unused, but callers pass it on the stack.
f32 func_800D9028_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 prevY) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    Hu3DSphere sphere;
    Vec floorNormal;
    Vec normal2;
    Vec *normal;
    D_800EC1C0_minigame_ObjData *objData;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 speed;
    f32 scale;
    f32 mult;
    f32 dist;
    f32 newX;
    f32 newZ;
    f32 best;
    f32 groundY;
    f32 height;

    data->unk53[0] = data->unk53[1] = -1;
    data->unk8C = 65536.0f;
    speed = data->unk40;
    scale = data->unk4C;
    mult = data->unkB4;
    if (data->unk50 & 6) {
        dist = speed * 0.6f * scale;
    } else {
        dist = speed * scale;
    }
    dist *= mult;
    newX = x + sindf(data->unk3C) * dist;
    newX += D_800EBE2C_minigame;
    newZ = z + cosdf(data->unk3C) * dist;
    newZ += D_800EC5D8_minigame;
    groundY = -65536.0f;
    best = groundY;
    if (func_800DA768_minigame(arg0, newX, y, newZ) != 2) {
        func_800DB628_minigame(arg0);
        speed = data->unk40;
        scale = data->unk4C;
        mult = data->unkB4;
        if (data->unk50 & 6) {
            dist = speed * 0.6f * scale;
        } else {
            dist = speed * scale;
        }
        dist *= mult;
        newX = x + sindf(data->unk3C) * dist;
        newZ = z + cosdf(data->unk3C) * dist;
        sphere.pos.x = newX;
        sphere.pos.y = y;
        sphere.pos.z = newZ;
        sphere.radius = data->unk48;
        func_800DD530_minigame(arg0, &sphere, 0);
        func_800DB628_minigame(arg0);
        sphere.pos.x = newX + D_800EBE2C_minigame;
        sphere.pos.y = y;
        sphere.pos.z = newZ + D_800EC5D8_minigame;
        if (!(data->unk00[D_800EB734_minigame] & 1)) {
            objData = D_800EC1C0_minigame[D_800EB734_minigame]->data;
            if (objData->unk06 & 0x7A) {
                if (func_800E30B8_minigame(&sphere.pos, objData) == 1) {
                    height = objData->unk14;
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        D_800EB738_minigame = D_800EB734_minigame;
                        if (groundY < best && groundY < y + 35.0f) {
                            groundY = best;
                            floorNormal.x = 0.0f;
                            floorNormal.y = 1.0f;
                            floorNormal.z = 0.0f;
                            normal = &floorNormal;
                        }
                    }
                }
            } else {
                points = (Hu3DPoint *)Hu3DData[D_800EC1C0_minigame[D_800EB734_minigame]->model[0]].hmf->unk50;
                func_80021C14_main(D_800EC1C0_minigame[D_800EB734_minigame]->model[0], &D_800EBEB0_minigame,
                                   func_800DB704_minigame, &sphere.pos);
                for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
                     quad = func_80022198_main(&D_800EBEB0_minigame)) {
                    height = func_800204F4_main(newX + D_800EBE2C_minigame, y, newZ + D_800EC5D8_minigame, points,
                                                quad);
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        D_800EB738_minigame = D_800EB734_minigame;
                    }
                    if (groundY < height && groundY < y + 35.0f) {
                        groundY = height;
                        func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           &floorNormal);
                        normal = &floorNormal;
                    }
                }
                if (best == -65536.0f) {
                    best = -65536.0f;
                }
            }
        }
        height = func_800D89CC_minigame(arg0, newX + D_800EBE2C_minigame, y, newZ + D_800EC5D8_minigame, &normal2);
        if (best < height && height < y + 150.0f) {
            best = height;
        } else {
            data->unk53[0] = -1;
        }
        if (groundY < height && height < y + 150.0f) {
            groundY = height;
            normal = &normal2;
        }
        if (best == -65536.0f) {
            groundY = -65536.0f;
            data->unk4C = D_800EB778_minigame;
            if (data->unk38 < 0.0f) {
                data->unk38 = 0.0f;
            }
            data->unk53[0] = -1;
            if (data->unk8C != 65536.0f) {
                y = data->unk8C - data->unk34;
                func_800E47D8_minigame(arg0, y);
            }
        } else if (y < best) {
            data->unk53[0] = D_800EB738_minigame;
            y = func_800D9F10_minigame(arg0, best);
            data->unk38 = 1000.0f;
            data->unk50 &= ~8;
            if (data->unk00[D_800EB738_minigame] & 8) {
                func_800E1810_minigame();
            }
        } else {
            data->unk53[0] = -1;
            if (data->unk8C != 65536.0f) {
                y = data->unk8C - data->unk34;
                func_800E47D8_minigame(arg0, y);
            }
        }
    } else {
        sphere.pos.x = newX + D_800EBE2C_minigame;
        sphere.pos.y = y;
        sphere.pos.z = newZ + D_800EC5D8_minigame;
        sphere.radius = data->unk48;
        func_800DD530_minigame(arg0, &sphere, 0);
    }
    if (arg0->model[1] != 0) {
        func_800E4890_minigame(arg0, newX, y, newZ, groundY, normal);
    }
    data->unk90 = data->unk94 = data->unk98 = 0.0f;
    data->unk9C = data->unkA4 = 0.0f;
    arg0->rot.x = arg0->rot.z = 0.0f;
    return y;
}

f32 func_800D972C_minigame(omObjData *arg0, f32 angle, f32 x, f32 y, f32 z) {
    s8 idx = -1;
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    Hu3DSphere sphere;
    Vec floorNormal;
    Vec normal2;
    Vec *normal;
    D_800EC1C0_minigame_ObjData *objData;
    D_800EC1C0_minigame_ObjData *platform;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 speed;
    f32 mult;
    f32 dist;
    f32 newX;
    f32 newZ;
    f32 best;
    f32 groundY;
    f32 height;

    data->unk53[0] = data->unk53[1] = -1;
    data->unk8C = 65536.0f;
    normal = NULL;
    speed = data->unk40;
    mult = data->unkB4;
    if (data->unk50 & 6) {
        dist = speed * 0.6f * mult;
    } else {
        dist = speed * mult;
    }
    if (fabs(data->unk90) > 1.0) {
        D_800EBE2C_minigame += data->unk90;
    }
    if (fabs(data->unk98) > 1.0) {
        D_800EC5D8_minigame += data->unk98;
    }
    newX = x + sindf(angle) * dist;
    newX += D_800EBE2C_minigame;
    newZ = z + cosdf(angle) * dist;
    newZ += D_800EC5D8_minigame;
    groundY = -65536.0f;
    best = groundY;
    if (func_800DA768_minigame(arg0, newX, y, newZ) != 2) {
        func_800DB628_minigame(arg0);
        speed = data->unk40;
        mult = data->unkB4;
        if (data->unk50 & 6) {
            dist = speed * 0.6f * mult;
        } else {
            dist = speed * mult;
        }
        newX = x + sindf(angle) * dist;
        newZ = z + cosdf(angle) * dist;
        sphere.pos.x = newX + D_800EBE2C_minigame;
        sphere.pos.y = y;
        sphere.pos.z = newZ + D_800EC5D8_minigame;
        sphere.radius = data->unk48;
        func_800DD530_minigame(arg0, &sphere, 0);
        func_800DB628_minigame(arg0);
        sphere.pos.x = newX + D_800EBE2C_minigame;
        sphere.pos.y = y;
        sphere.pos.z = newZ + D_800EC5D8_minigame;
        if (!(data->unk00[D_800EB734_minigame] & 1)) {
            objData = D_800EC1C0_minigame[D_800EB734_minigame]->data;
            if (objData->unk06 & 0x7A) {
                if (func_800E30B8_minigame(&sphere.pos, objData) == 1) {
                    height = objData->unk14;
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        idx = D_800EB734_minigame;
                        if (groundY < best && groundY < y + 35.0f) {
                            groundY = best;
                            floorNormal.x = 0.0f;
                            floorNormal.y = 1.0f;
                            floorNormal.z = 0.0f;
                            normal = &floorNormal;
                        }
                    }
                }
            } else {
                points = (Hu3DPoint *)Hu3DData[D_800EC1C0_minigame[D_800EB734_minigame]->model[0]].hmf->unk50;
                func_80021C14_main(D_800EC1C0_minigame[D_800EB734_minigame]->model[0], &D_800EBEB0_minigame,
                                   func_800DB704_minigame, &sphere.pos);
                for (quad = func_80022198_main(&D_800EBEB0_minigame); quad != NULL;
                     quad = func_80022198_main(&D_800EBEB0_minigame)) {
                    height = func_800204F4_main(newX, y, newZ, points, quad);
                    if (best < height) {
                        best = height;
                        idx = D_800EB734_minigame;
                    }
                    if (groundY < height && groundY < y + 35.0f) {
                        groundY = height;
                        func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           &floorNormal);
                        normal = &floorNormal;
                    }
                }
                if (best == -65536.0f) {
                    best = -65536.0f;
                }
            }
        }
        height = func_800D89CC_minigame(arg0, newX + D_800EBE2C_minigame, y, newZ + D_800EC5D8_minigame, &normal2);
        if (best < height && height < y + 35.0f) {
            idx = D_800EB738_minigame;
            best = height;
        } else {
            if (height < y + 150.0f && y + 35.0f < height) {
                best = 65536.0f;
            }
            data->unk53[0] = -1;
        }
        if (groundY < height && height < y + 35.0f) {
            groundY = height;
            normal = &normal2;
        }
        if (y - 35.0f < best && best < y + 35.0f) {
            if (idx != -1) {
                data->unk53[0] = idx;
            }
            y = func_800D9F10_minigame(arg0, best);
            if (data->unk00[idx] & 8) {
                func_800E1810_minigame();
            }
            data->unk38 = 1000.0f;
            if (data->unk8C != 65536.0f) {
                func_800E47D8_minigame(arg0, y);
            }
        } else {
            func_800E5690_minigame(arg0, 6);
            data->unk38 = D_800EB77C_minigame;
            data->unk53[0] = -1;
            func_800E19FC_minigame(data, 13);
            return 65536.0f;
        }
    } else {
        sphere.pos.x = newX + D_800EBE2C_minigame;
        sphere.pos.y = y;
        sphere.pos.z = newZ + D_800EC5D8_minigame;
        sphere.radius = data->unk48;
        func_800DD530_minigame(arg0, &sphere, 0);
    }
    if (arg0->model[1] != 0) {
        func_800E4890_minigame(arg0, newX, y, newZ, groundY, normal);
    }
    if (data->unk53[0] >= 0) {
        platform = D_800EC1C0_minigame[data->unk53[0]]->data;
        data->unk90 = normal->x * platform->unk10;
        data->unk94 = normal->y;
        data->unk98 = normal->z * platform->unk10;
        if (platform->unk06 & 0x400) {
            func_800DDB60_minigame(arg0, normal);
            return y;
        }
    } else {
        data->unk90 = data->unk94 = data->unk98 = 0.0f;
        data->unk9C = data->unkA4 = 0.0f;
        arg0->rot.x = arg0->rot.z = 0.0f;
    }
    return y;
}

f32 func_800D9F10_minigame(omObjData *arg0, f32 arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    u8 player = data->unk53[0];
    f32 ret = arg0->trans.y;

    if (data->unk00[player] & 2) {
        ret = arg1;
    }
    return ret;
}

s32 func_800D9F3C_minigame(Vec *pos, Hu3DQuad *quad, Hu3DPoint *points) {
    Vec normal;
    Hu3DPoint *p0;
    f32 px;
    f32 py;
    f32 pz;

    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    p0 = &points[quad->vtx[1]];
    px = p0->x;
    py = p0->y;
    pz = p0->z;
    px -= pos->x;
    py -= pos->y;
    pz -= pos->z;
    return (px * normal.x + py * normal.y + pz * normal.z < 0.0f) ? -1 : 1;
}

s32 func_800DA054_minigame(Hu3DSphere *sphere, Hu3DQuad *quad, Hu3DPoint *points) {
    Vec normal;
    Hu3DPoint *p0;
    f32 px;
    f32 py;
    f32 pz;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 proj;
    s32 side = -1;
    s32 flags;

    flags = (u16)quad->vtx[0] & 0x3F00;
    if (flags <= 0x200) {
        return FALSE;
    }
    func_8002038C_main(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    p0 = &points[quad->vtx[1]];
    px = p0->x;
    py = p0->y;
    pz = p0->z;
    dx = px - sphere->pos.x;
    dy = py - sphere->pos.y;
    dz = pz - sphere->pos.z;
    dist = dx * normal.x + dy * normal.y + dz * normal.z;
    if (dist >= 0.0f) {
        side = 1;
    }
    if (fabsf(dist) > sphere->radius) {
        return FALSE;
    }
    proj = dx * normal.x + dy * normal.y + dz * normal.z;
    sphere->pos.x += proj * normal.x;
    sphere->pos.y += proj * normal.y;
    sphere->pos.z += proj * normal.z;
    return side;
}

f32 func_800DA204_minigame(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal) {
    f32 ax = p->x - x;
    f32 ay = p->y - y;
    f32 az = p->z - z;
    f32 bx = q->x - x;
    f32 by = q->y - y;
    f32 bz = q->z - z;

    return (ay * bz - az * by) * normal->x + (az * bx - ax * bz) * normal->y + (ax * by - ay * bx) * normal->z;
}

s32 func_800DA2E0_minigame(Vec *pos, s16 *face, Hu3DPoint *points, Vec *normal) {
    f32 x = pos->x;
    f32 y = pos->y;
    f32 z = pos->z;
    s32 count;
    s32 i;
    s32 next;

    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (func_800DA204_minigame(x, y, z, &points[face[0]], &points[face[1]], normal) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_800DA204_minigame(x, y, z, &points[face[i]], &points[face[next]], normal) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_800DA204_minigame(x, y, z, &points[face[i]], &points[face[next]], normal) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

s32 func_800DA540_minigame(Vec *pos, s16 *face, Hu3DPoint *points) {
    f32 x;
    f32 z;
    s32 count;
    s32 i;
    s32 next;

    if (((u16)face[0] & 0x3F00) > 0x200) {
        return FALSE;
    }
    x = pos->x;
    z = pos->z;
    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (func_8002048C_main(x, z, &points[face[0]], &points[face[1]]) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (func_8002048C_main(x, z, &points[face[i]], &points[face[next]]) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

s32 func_800DA768_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData;
    A96F0_ObjData *itemData;
    omObjData *other;
    f32 radius = data->unk48;
    f32 speed = data->unk40;
    f32 dx, dy, dz;
    f32 dist;
    f32 dist2;
    f32 dot;
    u16 i;

    if (data->unk50 & 6) {
        speed *= 0.6f;
    }
    speed *= (data->unk38 != 1000.0f) ? data->unk4C * data->unkB4 : data->unkB4;
    x += sindf(data->unk3C) * speed;
    z += cosdf(data->unk3C) * speed;
    data->unkF0 = 0;
    for (i = 0; i < D_800EC1B8_minigame; i++) {
        other = D_800EBE70_minigame[i];
        itemData = other->data;
        if (itemData->unk54 == 0) {
            continue;
        }
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dy = other->trans.y - y;
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        dist2 = 100.0f;
        if (itemData->unk34 != 0.0f && other->trans.y <= y && y <= other->trans.y + itemData->unk34) {
            dist2 = HuSqrtf(dx * dx + dz * dz) - (radius + itemData->unk48);
        }
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (radius + itemData->unk48);
        if (dist < 0.0f || dist2 < 0.0f) {
            if (data->unkEC != NULL && data->unkEC(arg0, other) == 1) {
                continue;
            }
            if (itemData->unk52 == 7) {
                if (data->unkBE != 0) {
                    D_800EC288_minigame++;
                    continue;
                }
                if (data->unk50 & 0x200) {
                    continue;
                }
                dot = func_800E2ED4_minigame(sindf(data->unk3C), cosdf(data->unk3C), dx, dz);
                if (data->unk50 & 0x10) {
                    func_800E2CA4_minigame(arg0, D_800EB768_minigame);
                }
                if (dot > 0.0f) {
                    func_800E5690_minigame(arg0, 9);
                    data->unk40 = -D_800EB760_minigame;
                } else {
                    func_800E5690_minigame(arg0, 10);
                    data->unk40 = D_800EB760_minigame;
                }
                data->unk38 = -D_800EB744_minigame * 0.7f;
                data->unkBE = 105;
                func_800E4C88_minigame(arg0, 5, other->trans.x, y, other->trans.z, 0.0f, atan2df(dx, dz) + 180.0f);
                func_800E19FC_minigame(data, 8);
                omVibrate(data->unk59, 20, 0, 20);
                continue;
            }
            if (itemData->unk50 & 0x20) {
                if (itemData->unk50 & 0x10) {
                    continue;
                }
                dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (itemData->unk48 + data->unk48);
                if (!(dist < 0.0f)) {
                    continue;
                }
                if (itemData->unk38 < 1000.0f) {
                    itemData->unk38 = -D_800EB744_minigame * 0.6f;
                    if (func_800E2ED4_minigame(sindf(itemData->unk3C), cosdf(itemData->unk3C), dx, dz) < 0.0f) {
                        itemData->unk40 = -D_800EB76C_minigame;
                    } else {
                        itemData->unk40 = D_800EB76C_minigame;
                    }
                } else if (itemData->unk40 == D_800EB770_minigame) {
                    if (data->unk38 != 1000.0f) {
                        func_800E317C_minigame(arg0, dx, dz);
                        func_800E1A9C_minigame(data, 9);
                    } else {
                        if (dx == 0.0f && dz == 0.0f) {
                            dx = sindf(data->unk3C);
                            dz = cosdf(data->unk3C);
                        }
                        func_800DFCDC_minigame(dx, dz, dist);
                    }
                } else {
                    itemData->unk40 = -itemData->unk40;
                }
            } else if (data->unkBE != 0) {
                D_800EC288_minigame++;
            } else {
                func_800D81C8_minigame(arg0, other);
            }
        }
    }

    y += data->unk48;
    if (data->unk50 & 0x400) {
        return 0;
    }
    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherData = other->data;
        if (data == otherData) {
            continue;
        }
        dx = other->trans.x - (x + D_800EBE2C_minigame);
        dy = (other->trans.y + otherData->unk48) - y;
        dz = other->trans.z - (z + D_800EC5D8_minigame);
        if (otherData->unk50 & 0x400) {
            continue;
        }
        dist = HuSqrtf(dx * dx + dz * dz) - (data->unk48 + otherData->unk48) * 0.6f;
        dist2 = HuSqrtf(dx * dx + dy * dy + dz * dz) - (otherData->unk48 + data->unk48);
        if ((dist < 0.0f || dist2 < 0.0f) && data->unk38 != 1000.0f && !(data->unk50 & 0x8000)) {
            if (y - (otherData->unk34 + otherData->unk48) <= other->trans.y && other->trans.y <= y - data->unk48 + data->unk34) {
                if (!(otherData->unk50 & 7) && data->unkBE == 0 && otherData->unkBE == 0) {
                    if (otherData->unk38 != 1000.0f) {
                        if (data->unk5C & 0x200) {
                            if (dist < 0.0f && dy < -data->unk34 * 0.5f) {
                                func_800E4C88_minigame(arg0, 7, x, y, z, 0.0f, 0.0f);
                                if (!(otherData->unk50 & 0x200)) {
                                    func_800E561C_minigame(other, 1);
                                    func_800E5690_minigame(other, 0x1E);
                                    if (otherData->unk50 & 0x10) {
                                        func_800E2CA4_minigame(other, D_800EB76C_minigame);
                                    }
                                }
                                otherData->unk38 = data->unk38;
                                otherData->unk40 = D_800EB770_minigame;
                                func_800E317C_minigame(arg0, dx, dz);
                                func_800E1A9C_minigame(data, 9);
                            } else {
                                if (D_800EB735_minigame == 1) {
                                    func_800E34D8_minigame(arg0, other);
                                } else {
                                    func_800DFCDC_minigame(dx, dz, HuSqrtf(dx * dx + dz * dz) - (otherData->unk48 + data->unk48));
                                }
                                return 0;
                            }
                        } else if (dist < 0.0f && dy < -data->unk34 * 0.2) {
                            if (!(otherData->unk50 & 0x200)) {
                                func_800E4C88_minigame(arg0, 6, x, y, z, -90.0f, 0.0f);
                                if (otherData->unk50 & 0x10) {
                                    func_800E2CA4_minigame(other, D_800EB76C_minigame);
                                }
                            }
                            if (otherData->unk38 < 0.0f) {
                                otherData->unk38 = 0.0f;
                            }
                            otherData->unk40 = D_800EB770_minigame;
                            func_800E317C_minigame(arg0, dx, dz);
                            func_800E1A9C_minigame(data, 9);
                        } else {
                            if (D_800EB735_minigame == 1) {
                                func_800E34D8_minigame(arg0, other);
                            } else {
                                func_800DFCDC_minigame(dx, dz, HuSqrtf(dx * dx + dz * dz) - (otherData->unk48 + data->unk48));
                            }
                            return 0;
                        }
                        omVibrate(data->unk59, 2, 3, 10);
                        omVibrate(otherData->unk59, 2, 3, 10);
                        return 2;
                    }
                    if (dist < 0.0f && dy < 0.0f) {
                        if (!(otherData->unk50 & 0x200)) {
                            if (data->unk5C & 0x200) {
                                func_800E561C_minigame(other, 1);
                                func_800E5690_minigame(other, 0);
                                func_800E4C88_minigame(arg0, 7, x, y, z, 0.0f, 0.0f);
                                if (otherData->unk50 & 0x10) {
                                    func_800E2CA4_minigame(other, D_800EB76C_minigame);
                                }
                            } else {
                                func_800E4C88_minigame(arg0, 6, x, y, z, -90.0f, 0.0f);
                                func_800E561C_minigame(other, 2);
                                if (otherData->unk50 & 0x10) {
                                    func_800E2CA4_minigame(other, D_800EB76C_minigame);
                                }
                            }
                        }
                        func_800E317C_minigame(arg0, dx, dz);
                        func_800E1A9C_minigame(data, 9);
                        omVibrate(data->unk59, 2, 3, 10);
                        omVibrate(otherData->unk59, 20, 0, 20);
                        return 2;
                    }
                    func_800E317C_minigame(arg0, dx, dz);
                    data->unk38 = -D_800EB744_minigame * 0.6f;
                    data->unk40 *= 0.5;
                    func_800E1A9C_minigame(data, 9);
                    omVibrate(data->unk59, 2, 3, 10);
                    omVibrate(otherData->unk59, 20, 0, 20);
                    continue;
                }
                if (data->unk38 != 1000.0f && otherData->unk38 != 1000.0f) {
                    if (data->unkBE != 0 || otherData->unkBE != 0) {
                        if (D_800EB735_minigame == 1) {
                            func_800E34D8_minigame(arg0, other);
                            omVibrate(data->unk59, 2, 3, 10);
                            return 0;
                        }
                        func_800DFCDC_minigame(dx, dz, dist2);
                        return 0;
                    }
                    continue;
                }
                if (data->unk5C & 0x200) {
                    func_800E4C88_minigame(arg0, 7, x, y, z, 0.0f, 0.0f);
                } else {
                    func_800E4C88_minigame(arg0, 6, x, y, z, -90.0f, 0.0f);
                }
                omVibrate(data->unk59, 2, 3, 10);
                func_800E317C_minigame(arg0, dx, dz);
                func_800E1A9C_minigame(data, 9);
                continue;
            }
            if (dist2 < 0.0f) {
                if (D_800EB735_minigame == 1) {
                    func_800E34D8_minigame(arg0, other);
                } else {
                    func_800DFCDC_minigame(dx, dz, dist2);
                }
            }
            continue;
        }
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (otherData->unk48 + data->unk48);
        if (dist < 0.0f) {
            if (otherData->unk38 != 1000.0f && data->unk38 == 1000.0f) {
                continue;
            }
            func_800DFCDC_minigame(dx, dz, dist);
            data->unk53[1] = i;
        }
    }
    return 0;
}

void func_800DB628_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 limit = data->unk48;
    f32 angle;

    if (HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) > limit ||
        fabs(D_800EBE2C_minigame) > limit || fabs(D_800EC5D8_minigame) > limit) {
        angle = data->unk3C;
        D_800EBE2C_minigame = -sindf(angle) * data->unk40;
        D_800EC5D8_minigame = -cosdf(angle) * data->unk40;
    }
}

s32 func_800DB704_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos) {
    return func_800DA540_minigame(pos, vtx - 1, points);
}

s32 func_800DB724_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Hu3DSphere *arg3) {
    Hu3DSphere sphere;
    Hu3DSphere prev;
    Vec closest;
    Vec quad[4];
    Vec tri[3];
    Vec dir;
    s32 side;
    s32 hit;
    f32 dx;
    f32 dz;
    f32 depth;
    s16 *face;

    prev.pos.x = sphere.pos.x = arg3->pos.x + D_800EBE2C_minigame;
    prev.pos.y = sphere.pos.y = arg3->pos.y;
    prev.pos.z = sphere.pos.z = arg3->pos.z + D_800EC5D8_minigame;
    sphere.radius = arg3->radius;
    face = vtx - 1;
    side = func_800DA054_minigame(&sphere, (Hu3DQuad *)face, points);
    if (side == 0) {
        return 0;
    }
    if (((u16)face[0] >> 14) + 2 == 4) {
        quad[0].x = points[vtx[0]].x;
        quad[0].y = points[vtx[0]].y;
        quad[0].z = points[vtx[0]].z;
        quad[1].x = points[vtx[1]].x;
        quad[1].y = points[vtx[1]].y;
        quad[1].z = points[vtx[1]].z;
        quad[2].x = points[vtx[2]].x;
        quad[2].y = points[vtx[2]].y;
        quad[2].z = points[vtx[2]].z;
        quad[3].x = points[vtx[3]].x;
        quad[3].y = points[vtx[3]].y;
        quad[3].z = points[vtx[3]].z;
        hit = Hitcheck_Quadrangle_with_Sphere(quad, &prev.pos, sphere.radius, &closest);
    } else {
        tri[0].x = points[vtx[0]].x;
        tri[0].y = points[vtx[0]].y;
        tri[0].z = points[vtx[0]].z;
        tri[1].x = points[vtx[1]].x;
        tri[1].y = points[vtx[1]].y;
        tri[1].z = points[vtx[1]].z;
        tri[2].x = points[vtx[2]].x;
        tri[2].y = points[vtx[2]].y;
        tri[2].z = points[vtx[2]].z;
        hit = Hitcheck_Triangle_with_Sphere(tri, &prev.pos, sphere.radius, &closest);
    }
    if (hit == 1) {
        func_800E048C_minigame(closest.x, closest.y, closest.z);
        func_8002038C_main(&points[vtx[0]], &points[vtx[1]], &points[vtx[2]], &D_800EC298_minigame[D_800EB736_minigame]);
        D_800EB736_minigame++;
        dx = closest.x - prev.pos.x;
        dz = closest.z - prev.pos.z;
        depth = sphere.radius - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            if (func_800D9F3C_minigame(&D_800EBDD0_minigame, (Hu3DQuad *)(vtx - 1), points) < 0) {
                dir.x = D_800EBDD0_minigame.x - prev.pos.x;
                dir.y = D_800EBDD0_minigame.y - prev.pos.y;
                dir.z = D_800EBDD0_minigame.z - prev.pos.z;
                func_800202FC_main(&dir);
                if (func_800DA2E0_minigame(&prev.pos, vtx - 1, points, &dir) == hit) {
                    depth = HuSqrtf(dx * dx + dz * dz) + sphere.radius;
                }
            } else {
                depth = 0.0f;
            }
        }
        func_800DFCDC_minigame(-dx, -dz, depth);
    }
    return hit;
}

s32 func_800DBCF4_minigame(s32 count, s16 *vtx, Hu3DPoint *points, func_800DBCF4_minigame_Arg *arg3) {
    Hu3DSphere sphere;
    Hu3DSphere prev;
    Vec closest;
    Vec quad[4];
    Vec tri[3];
    Vec dir;
    s32 side;
    s32 hit;
    f32 dx;
    f32 dz;
    f32 depth;
    s16 *face;

    prev.pos.x = sphere.pos.x = arg3->pos.x + D_800EBE2C_minigame;
    prev.pos.y = sphere.pos.y = arg3->pos.y;
    prev.pos.z = sphere.pos.z = arg3->pos.z + D_800EC5D8_minigame;
    sphere.radius = prev.radius = arg3->radius;
    face = vtx - 1;
    side = func_800DA054_minigame(&sphere, (Hu3DQuad *)face, points);
    if (side == 0) {
        return 0;
    }
    if (((u16)face[0] >> 14) + 2 == 4) {
        quad[0].x = points[vtx[0]].x;
        quad[0].y = points[vtx[0]].y;
        quad[0].z = points[vtx[0]].z;
        quad[1].x = points[vtx[1]].x;
        quad[1].y = points[vtx[1]].y;
        quad[1].z = points[vtx[1]].z;
        quad[2].x = points[vtx[2]].x;
        quad[2].y = points[vtx[2]].y;
        quad[2].z = points[vtx[2]].z;
        quad[3].x = points[vtx[3]].x;
        quad[3].y = points[vtx[3]].y;
        quad[3].z = points[vtx[3]].z;
        hit = Hitcheck_Quadrangle_with_Sphere(quad, &prev.pos, sphere.radius, &closest);
    } else {
        tri[0].x = points[vtx[0]].x;
        tri[0].y = points[vtx[0]].y;
        tri[0].z = points[vtx[0]].z;
        tri[1].x = points[vtx[1]].x;
        tri[1].y = points[vtx[1]].y;
        tri[1].z = points[vtx[1]].z;
        tri[2].x = points[vtx[2]].x;
        tri[2].y = points[vtx[2]].y;
        tri[2].z = points[vtx[2]].z;
        hit = Hitcheck_Triangle_with_Sphere(tri, &prev.pos, sphere.radius, &closest);
    }
    if (hit == 1) {
        prev.pos.x = arg3->prev.x + D_800EBE2C_minigame;
        prev.pos.y = arg3->prev.y;
        prev.pos.z = arg3->prev.z + D_800EC5D8_minigame;
        func_800E2BD4_minigame(D_800EC240_minigame, &closest);
        func_800E048C_minigame(closest.x, closest.y, closest.z);
        func_8002038C_main(&points[vtx[0]], &points[vtx[1]], &points[vtx[2]], &D_800EC298_minigame[D_800EB736_minigame]);
        D_800EB736_minigame++;
        dx = closest.x - prev.pos.x;
        dz = closest.z - prev.pos.z;
        depth = sphere.radius - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            sphere.pos.x = D_800EBDD0_minigame.x;
            sphere.pos.y = D_800EBDD0_minigame.y;
            sphere.pos.z = D_800EBDD0_minigame.z;
            func_800E2BD4_minigame(D_800EBE30_minigame, &sphere.pos);
            if (func_800D9F3C_minigame(&sphere.pos, (Hu3DQuad *)(vtx - 1), points) < 0) {
                dir.x = sphere.pos.x - prev.pos.x;
                dir.y = sphere.pos.y - prev.pos.y;
                dir.z = sphere.pos.z - prev.pos.z;
                func_800202FC_main(&dir);
                if (func_800DA2E0_minigame(&prev.pos, vtx - 1, points, &dir) == hit) {
                    depth = HuSqrtf(dx * dx + dz * dz) + sphere.radius;
                }
            } else {
                depth = 0.0f;
            }
        }
        if (0.0f <= depth) {
            func_800DFCDC_minigame(-dx, -dz, depth);
        }
    }
    return hit;
}

void func_800DC354_minigame(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2) {
    s32 i = D_800EB736_minigame;
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 minX = data->unkA0 + arg1->radius;
    f32 minZ = data->unkA4 + arg1->radius;
    f32 maxX = data->unkA8.f - arg1->radius;
    f32 maxZ = data->unkAC - arg1->radius;
    f32 half;

    if (arg1->pos.x <= minX) {
        func_800E048C_minigame(data->unkA0, arg1->pos.y, arg1->pos.z);
        func_800E0430_minigame(1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (maxX <= arg1->pos.x) {
        func_800E048C_minigame(data->unkA8.f, arg1->pos.y, arg1->pos.z);
        func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
        D_800EB736_minigame++;
    }
    if (arg1->pos.z <= minZ) {
        func_800E048C_minigame(arg1->pos.x, arg1->pos.y, data->unkA4);
        func_800E0430_minigame(0.0f, 0.0f, 1.0f);
        D_800EB736_minigame++;
    }
    if (maxZ <= arg1->pos.z) {
        func_800E048C_minigame(arg1->pos.x, arg1->pos.y, data->unkAC);
        func_800E0430_minigame(0.0f, 0.0f, -1.0f);
        D_800EB736_minigame++;
    }
    if (i == D_800EB736_minigame) {
        half = arg1->radius * 0.5f;
        if (arg1->pos.x <= minX - half) {
            func_800E048C_minigame(data->unkA0, arg1->pos.y, arg1->pos.z);
            func_800E0430_minigame(1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (maxX + half <= arg1->pos.x) {
            func_800E048C_minigame(data->unkA8.f, arg1->pos.y, arg1->pos.z);
            func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
            D_800EB736_minigame++;
        }
        if (arg1->pos.z <= minZ - half) {
            func_800E048C_minigame(arg1->pos.x, arg1->pos.y, data->unkA4);
            func_800E0430_minigame(0.0f, 0.0f, 1.0f);
            D_800EB736_minigame++;
        }
        if (maxZ + half <= arg1->pos.z) {
            func_800E048C_minigame(arg1->pos.x, arg1->pos.y, data->unkAC);
            func_800E0430_minigame(0.0f, 0.0f, -1.0f);
            D_800EB736_minigame++;
        }
    }
    // minX/minZ are reused as the offset to each new contact point.
    while (i < D_800EB736_minigame) {
        minX = D_800EBEB8_minigame[i].unk00 - arg1->pos.x;
        minZ = D_800EBEB8_minigame[i].unk08 - arg1->pos.z;
        func_800DFCDC_minigame(-minX, -minZ, arg1->radius - HuSqrtf(minX * minX + minZ * minZ));
        if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
            arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
            func_800E2BD4_minigame(D_800EC240_minigame, (Vec *)&D_800EBEB8_minigame[i]);
        }
        i++;
    }
}

void func_800DC7D8_minigame(omObjData *arg0, Hu3DSphere *arg1) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->pos.x;
    f32 z = arg1->pos.z;
    f32 dist;
    Vec dir;

    dist = data->unk9C - (HuSqrtf(x * x + z * z) + arg1->radius);
    if (dist <= 0.0f) {
        func_800DFCDC_minigame(x, z, dist);
        dir.x = x;
        dir.y = 0.0f;
        dir.z = z;
        func_800202FC_main(&dir);
        func_800E048C_minigame(arg1->pos.x * dir.x, arg1->pos.y, arg1->pos.z * dir.z);
        func_800E0430_minigame(-arg1->pos.x, 0.0f, -arg1->pos.z);
        D_800EB736_minigame++;
    }
}

void func_800DC8E4_minigame(omObjData *arg0, Hu3DSphere *arg1, f32 arg2) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->pos.x;
    f32 z = arg1->pos.z;
    f32 dist;
    Vec dir;

    if (arg1->pos.y < arg2 + data->unk14 && data->unk14 - data->unk98 - arg2 < arg1->pos.y) {
        dist = HuSqrtf(x * x + z * z) - data->unk9C;
        if (0.0f <= dist && dist <= arg1->radius) {
            func_800DFCDC_minigame(x, z, arg1->radius - dist);
            dir.x = x;
            dir.y = 0.0f;
            dir.z = z;
            func_800202FC_main(&dir);
            func_800E048C_minigame(-arg1->pos.x * dir.x, arg1->pos.y, -arg1->pos.z * dir.z);
            func_800E0430_minigame(arg1->pos.x, 0.0f, arg1->pos.z);
            D_800EB736_minigame++;
        }
    }
}

s32 func_800DCA34_minigame(Hu3DSphere *arg0, func_800E1BA8_minigame_ObjData *data) {
    f32 x = arg0->pos.x;
    f32 y = arg0->pos.y;
    f32 z = arg0->pos.z;
    f32 dx;
    f32 dz;

    if (x <= data->unkA0) {
        dx = data->unkA0 - x;
        if (z <= data->unkA4) {
            dz = data->unkA4 - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                func_800E048C_minigame(data->unkA0, y, data->unkA4);
                func_800E0430_minigame(x - data->unkA0, 0.0f, z - data->unkA4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                func_800E048C_minigame(data->unkA0, y, data->unkAC);
                func_800E0430_minigame(x - data->unkA0, 0.0f, z - data->unkAC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    } else if (arg0->pos.x >= data->unkA8.f) {
        dx = data->unkA8.f - x;
        if (z <= data->unkA4) {
            dz = data->unkA4 - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                func_800E048C_minigame(data->unkA8.f, y, data->unkA4);
                func_800E0430_minigame(x - data->unkA8.f, 0.0f, z - data->unkA4);
                D_800EB736_minigame++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                func_800E048C_minigame(data->unkA8.f, y, data->unkAC);
                func_800E0430_minigame(x - data->unkA8.f, 0.0f, z - data->unkAC);
                D_800EB736_minigame++;
                return 0;
            }
        }
    }
    return 1;
}

void func_800DCCB0_minigame(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2, f32 arg3) {
    s32 i = D_800EB736_minigame;
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 x = arg1->pos.x;
    f32 z = arg1->pos.z;
    f32 minX;
    f32 minZ;
    f32 maxX;
    f32 maxZ;
    f32 edgeX;
    f32 edgeZ;

    if (arg1->pos.y < arg3 + data->unk14 && data->unk14 - data->unk98 - arg3 < arg1->pos.y) {
        minX = data->unkA0 - arg1->radius;
        minZ = data->unkA4 - arg1->radius;
        maxX = data->unkA8.f + arg1->radius;
        maxZ = data->unkAC + arg1->radius;
        if (((minX <= x) & (x < maxX)) && ((minZ < z) & (z < maxZ))) {
            if (func_800DCA34_minigame(arg1, data) == 1) {
                if (minX <= x && x <= data->unkA0) {
                    if (data->unkA4 <= arg1->pos.z && arg1->pos.z <= data->unkAC) {
                        edgeX = data->unkA0;
                        if (edgeX == arg1->pos.x) {
                            edgeX += 1.0f;
                        }
                        func_800E048C_minigame(edgeX, arg1->pos.y, arg1->pos.z);
                        func_800E0430_minigame(-1.0f, 0.0f, 0.0f);
                        D_800EB736_minigame++;
                    }
                } else if (x <= maxX && data->unkA8.f <= x) {
                    if (data->unkA4 <= arg1->pos.z && arg1->pos.z <= data->unkAC) {
                        edgeX = data->unkA8.f;
                        if (edgeX == arg1->pos.x) {
                            edgeX -= 1.0f;
                        }
                        func_800E048C_minigame(edgeX, arg1->pos.y, arg1->pos.z);
                        func_800E0430_minigame(1.0f, 0.0f, 0.0f);
                        D_800EB736_minigame++;
                    }
                } else if (minZ <= z && z <= data->unkA4) {
                    if (data->unkA0 <= arg1->pos.x && arg1->pos.x <= data->unkA8.f) {
                        edgeZ = data->unkA4;
                        if (edgeZ == arg1->pos.z) {
                            edgeZ += 1.0f;
                        }
                        func_800E048C_minigame(arg1->pos.x, arg1->pos.y, edgeZ);
                        func_800E0430_minigame(0.0f, 0.0f, -1.0f);
                        D_800EB736_minigame++;
                    }
                } else if (z <= maxZ && data->unkAC <= z) {
                    if (data->unkA0 <= arg1->pos.x && arg1->pos.x <= data->unkA8.f) {
                        edgeZ = data->unkAC;
                        if (edgeZ == arg1->pos.z) {
                            edgeZ -= 1.0f;
                        }
                        func_800E048C_minigame(arg1->pos.x, arg1->pos.y, edgeZ);
                        func_800E0430_minigame(0.0f, 0.0f, 1.0f);
                        D_800EB736_minigame++;
                    }
                }
            }
            for (; i < D_800EB736_minigame; i++) {
                if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
                    arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
                    func_800E2BD4_minigame(D_800EC240_minigame, (Vec *)&D_800EBEB8_minigame[i]);
                }
                minX = D_800EBEB8_minigame[i].unk00 - arg2->x;
                minZ = D_800EBEB8_minigame[i].unk08 - arg2->z;
                func_800DFCDC_minigame(minX, minZ, HuSqrtf(minX * minX + minZ * minZ) - arg1->radius);
            }
        }
    }
}

void func_800DD1F4_minigame(omObjData *obj, Vec *pos, f32 arg2) {
    func_800E1BA8_minigame_ObjData *data;
    f32 speed;
    f32 dx, dy, dz;
    f32 limit;
    s32 i;

    if (D_800EB736_minigame == 0) {
        return;
    }
    data = obj->data;
    if (data->unk52 == 0) {
        f32 base = data->unk40;
        f32 scale = data->unkB4;

        if (data->unk50 & 6) {
            speed = base * 0.6f * scale;
        } else {
            speed = base * scale;
        }
    } else {
        speed = data->unk40;
    }
    if (data->unk38 != 1000.0f) {
        speed *= data->unk4C;
    }
    for (i = 0; i < D_800EB736_minigame; i++) {
        dx = D_800EBEB8_minigame[i].unk00 - pos->x;
        dy = D_800EBEB8_minigame[i].unk04 - pos->y;
        dz = D_800EBEB8_minigame[i].unk08 - pos->z;
        HuSqrtf(dx * dx + dy * dy + dz * dz);
        if (func_800E2ED4_minigame(sindf(data->unk3C) * speed + D_800EBE2C_minigame,
                                   cosdf(data->unk3C) * speed + D_800EC5D8_minigame, dx, dz) > 0.9f &&
            data->unk38 != 1000.0f && data->unk40 > D_800EB764_minigame) {
            limit = data->unk40;
            if (data->unk50 & 6) {
                limit *= 0.6f;
            }
            limit *= data->unk4C * data->unkB4 * 0.98f;
            if (HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame) <
                limit) {
                if (data->unk50 & 8) {
                    data->unk40 = -D_800EB760_minigame;
                } else {
                    data->unk40 = -D_800EB76C_minigame;
                }
                func_800E5690_minigame(obj, 30);
                func_800E19FC_minigame(data, 7);
                omVibrate(data->unk59, 5, 0, 5);
                return;
            }
        }
        if (arg2 != 0.0f) {
            data->unk40 = arg2;
            func_800E19FC_minigame(data, 7);
            omVibrate(data->unk59, 2, 3, 10);
            return;
        }
    }
}

s8 func_800DD530_minigame(omObjData *arg0, Hu3DSphere *arg1, f32 arg2) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    Hu3DSphere sphere;
    func_800DBCF4_minigame_Arg local;
    omObjData *obj;
    D_800EC1C0_minigame_ObjData *objData;
    s16 count;
    s16 i;

    sphere.pos.x = arg1->pos.x;
    sphere.pos.y = data->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z;
    sphere.radius = arg1->radius;
    D_800EC286_minigame = -1;
    D_800EB736_minigame = 0;
    count = 0;
    if (!(data->unk00[D_800EB734_minigame] & 1)) {
        obj = D_800EC1C0_minigame[D_800EB734_minigame];
        objData = obj->data;
        if (objData->unk06 & 8) {
            sphere.pos.x += D_800EBE2C_minigame;
            sphere.pos.y += D_800EC5D8_minigame;
            func_800DC354_minigame(obj, &sphere, &sphere.pos);
        } else if (objData->unk06 & 0x10) {
            sphere.pos.x += D_800EBE2C_minigame;
            sphere.pos.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(obj, &sphere, &sphere.pos, data->unk34 / 2);
        } else if (objData->unk06 & 0x20) {
            sphere.pos.x += D_800EBE2C_minigame;
            sphere.pos.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(obj, &sphere);
        } else if (objData->unk06 & 0x40) {
            sphere.pos.x += D_800EBE2C_minigame;
            sphere.pos.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(obj, &sphere, data->unk34 / 2);
        } else if (!(objData->unk06 & 2)) {
            func_80021C14_main(D_800EC1C0_minigame[D_800EB734_minigame]->model[0], &D_800EBEB0_minigame,
                               (s32 (*)(s32, s16 *, Hu3DPoint *, Vec *))func_800DB724_minigame, &sphere.pos);
        }
        if (count != D_800EB736_minigame) {
            D_800EC286_minigame = objData->unk04;
        }
    }
    for (i = 0; i < D_800EBE28_minigame; i++) {
        obj = D_800EC1C0_minigame[i];
        objData = obj->data;
        if (i == D_800EB734_minigame) {
            continue;
        }
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
            if (func_800E2FD8_minigame(Hu3DData[obj->model[0]].hmf->unk60, &local.pos, data->unk48) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 8) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC354_minigame(obj, (Hu3DSphere *)&local, &local.prev);
        } else if (objData->unk06 & 0x10) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DCCB0_minigame(obj, (Hu3DSphere *)&local, &local.prev, data->unk34 / 2);
        } else if (objData->unk06 & 0x20) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC7D8_minigame(obj, (Hu3DSphere *)&local);
        } else if (objData->unk06 & 0x40) {
            local.pos.x += D_800EBE2C_minigame;
            local.pos.y += D_800EC5D8_minigame;
            func_800DC8E4_minigame(obj, (Hu3DSphere *)&local, data->unk34 / 2);
        } else {
            func_80021C14_main(D_800EC1C0_minigame[i]->model[0], &D_800EBEB0_minigame,
                               (s32 (*)(s32, s16 *, Hu3DPoint *, Vec *))func_800DBCF4_minigame, &local.pos);
        }
        if (count != D_800EB736_minigame) {
            D_800EC286_minigame = objData->unk04;
            func_800E2B58_minigame(D_800EC240_minigame, &D_800EC28C_minigame[D_800EB736_minigame]);
        }
    }
    sphere.pos.x = arg1->pos.x + D_800EBE2C_minigame;
    sphere.pos.y = data->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z + D_800EC5D8_minigame;
    sphere.radius = arg1->radius;
    if (func_800E1510_minigame(D_800EC286_minigame) == 1) {
        func_800DD1F4_minigame(arg0, &sphere.pos, arg2);
    }
    return D_800EC286_minigame;
}

void func_800DDB60_minigame(omObjData *obj, Vec *dir) {
    func_800E1BA8_minigame_ObjData *data = obj->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    if (data->unk40 > D_800EB764_minigame) {
        rotX = -(atan2df(dir->y, dir->z) - 90.0f);
        rotZ = atan2df(dir->y, dir->x) - 90.0f;
        curX = data->unk9C;
        curZ = data->unkA4;
        if (curX < rotX) {
            if (rotX < (data->unk9C += 4.0f)) {
                data->unk9C = rotX;
            }
        } else if (rotX < curX) {
            if ((data->unk9C -= 4.0f) < rotX) {
                data->unk9C = rotX;
            }
        }
        if (curZ < rotZ) {
            if (rotZ < (data->unkA4 += 4.0f)) {
                data->unkA4 = rotZ;
            }
        } else if (rotZ < curZ) {
            if ((data->unkA4 -= 4.0f) < rotZ) {
                data->unkA4 = rotZ;
            }
        }
    } else {
        if (fabs(data->unk9C) > 2.0) {
            obj->rot.x = data->unk9C *= 0.3;
        }
        if (fabs(data->unkA4) > 2.0) {
            obj->rot.z = data->unkA4 *= 0.3;
        }
    }
    obj->rot.x = data->unk9C;
    obj->rot.z = data->unkA4;
}

void func_800DDD70_minigame(omObjData *arg0) {
    D_800EBDD0_minigame.x = arg0->trans.x;
    D_800EBDD0_minigame.y = arg0->trans.y;
    D_800EBDD0_minigame.z = arg0->trans.z;
}

void func_800DDD94_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    s8 pad = data->unk57;
    f32 speed = 0.0f;
    f32 x, y, z;
    s16 stickX, stickY;
    u16 held;
    u16 pressed;
    u32 state;
    s16 model;
    f32 prevVy;
    f32 newY;
    f32 accel;
    f32 angle;
    f32 dx, dz;
    f32 px;
    s32 avg;
    s16 avgX, avgY;
    omObjData *other;
    D_800EC1C0_minigame_ObjData *otherData;
    s16 turn;
    u16 motion;
    s32 idle;

    x = arg0->trans.x;
    y = arg0->trans.y;
    z = arg0->trans.z;
    func_800DDD70_minigame(arg0);
    model = arg0->model[0];
    prevVy = data->unk38;
    D_800EBE2C_minigame = D_800EC5D8_minigame = speed;
    D_800EC288_minigame = 0;
    D_800EC286_minigame = data->unk53[2] = -1;
    if (data->unk104[0] != NULL) {
        data->unk104[0](arg0);
    }
    if (func_800E6E8C_minigame() == 2 && pad >= 0 && !(data->unk50 & 1)) {
        stickX = D_800CBB6E_main[pad];
        stickY = D_800D20A1_main[pad];
        if (stickX > 60) {
            stickX = 60;
        }
        if (stickY > 60) {
            stickY = 60;
        }
        if (stickX < -60) {
            stickX = -60;
        }
        if (stickY < -60) {
            stickY = -60;
        }
        func_800E2308_minigame(&stickX, &stickY);
        held = 0;
        if (!(data->unk50 & 6)) {
            pressed = D_800D5558_main[pad];
            held = D_800CDA7C_main[pad];
        } else {
            pressed = 0;
        }
    } else {
        stickY = 0;
        stickX = 0;
        held = 0;
        pressed = 0;
    }
    state = func_800E4A90_minigame(arg0);
    if (state & 1) {
        idle = 1;
        if (data->unk38 == 1000.0f) {
            if (func_800D972C_minigame(arg0, data->unk3C, x, y, z) != 65536.0f && (pressed & 0x8000)) {
                func_800E3820_minigame(arg0, data);
                idle = 0;
            }
        } else {
            f32 vy = data->unk38;
            if (vy > D_800EB774_minigame) {
                vy = D_800EB774_minigame;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += D_800EB748_minigame;
            if (func_800E5690_minigame(arg0, 6) == 1) {
                func_800E19FC_minigame(data, 3);
                idle = 0;
            }
            y = func_800D9028_minigame(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = D_800EC1C0_minigame[data->unk53[0]];
                if (((D_800EC1C0_minigame_ObjData *)other->data)->unk03 == 2) {
                    func_800DFD9C_minigame(arg0, x, other->trans.y, z);
                }
            }
        }
        if (idle == 1) {
            func_800E5690_minigame(arg0, 0);
        }
        data->unkC6 = 0;
    } else if (state & 0x100000) {
        data->unkC0--;
        if (data->unkC0 == 0) {
            func_800E5690_minigame(arg0, 0x13);
        }
        if (data->unkC0 - 52 < 0) {
            data->unk40 = D_800EB770_minigame;
            arg0->rot.y = 0.0f;
        } else {
            arg0->rot.y = func_800202A8_main(data->unkC0 * 45.0f);
            if (data->unk40 < D_800EB770_minigame) {
                data->unk40 += D_800EB740_minigame * 0.2f;
                if (D_800EB770_minigame <= data->unk40) {
                    data->unk40 = D_800EB770_minigame;
                }
            } else if (D_800EB770_minigame <= data->unk40) {
                data->unk40 += -D_800EB740_minigame * 0.2f;
                if (data->unk40 <= D_800EB770_minigame) {
                    data->unk40 = D_800EB770_minigame;
                }
            }
        }
        newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
        }
    } else if (state & 0x18C18) {
        f32 vy;

        if (state & 0x10000) {
            if (pressed & 0x8000) {
                func_800E3820_minigame(arg0, data);
            }
        } else if (data->unk40 == D_800EB770_minigame) {
            if (state & 0x400) {
                func_800E5690_minigame(arg0, 0x21);
            } else if (state & 0x10) {
                func_800E5690_minigame(arg0, 0x12);
            } else if (state & 0x800) {
                func_800E5690_minigame(arg0, 0x22);
            } else if (state & 8) {
                func_800E5690_minigame(arg0, 0x13);
            } else {
                func_800E5690_minigame(arg0, 0);
            }
        } else if (data->unk40 < D_800EB770_minigame) {
            data->unk40 += D_800EB740_minigame * 2.0f;
            if (D_800EB770_minigame <= data->unk40) {
                data->unk40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame <= data->unk40) {
            data->unk40 += -D_800EB740_minigame * 2.0f;
            if (data->unk40 <= D_800EB770_minigame) {
                data->unk40 = D_800EB770_minigame;
            }
        }
        vy = data->unk38;
        if (vy == 1000.0f) {
            if (state & 0x10) {
                if (data->unk40 > D_800EB760_minigame) {
                    data->unk3C += -(f32)stickX / D_800EB750_minigame;
                } else {
                    f32 rate = (data->unk40 <= D_800EB76C_minigame) ? D_800EB76C_minigame : data->unk40;

                    data->unk3C += -(stickX / D_800EB750_minigame) * (rate / D_800EB760_minigame);
                }
            }
            newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
            if (newY != 65536.0f) {
                y = newY;
            }
        } else {
            if (vy > D_800EB774_minigame) {
                vy = D_800EB774_minigame;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += D_800EB748_minigame;
            y = func_800D9028_minigame(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = D_800EC1C0_minigame[data->unk53[0]];
                if (((D_800EC1C0_minigame_ObjData *)other->data)->unk03 == 2) {
                    func_800DFD9C_minigame(arg0, x, other->trans.y, z);
                } else if (state & 0x10) {
                    func_800E5690_minigame(arg0, 0x12);
                } else if (state & 8) {
                    func_800E5690_minigame(arg0, 0x13);
                } else if (!(state & 0xC00)) {
                    func_800E5690_minigame(arg0, 0);
                }
            }
        }
        data->unkC6 = 0;
    } else if (state & 0x6000) {
        f32 time;

        func_800E2250_minigame(arg0, stickX, stickY);
        time = Hu3DMotionShiftTimeGet(model);
        if (time == -1.0f) {
            time = Hu3DData[model].motTime;
        }
        if (state & 0x4000) {
            data->unk3C += 25.0f;
            if (time >= 14.0f) {
                func_800E5690_minigame(arg0, 1);
                data->unk40 = D_800EB76C_minigame;
                func_800E19FC_minigame(data, 1);
            }
        } else if (time >= 10.0f) {
            if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                if (data->unk40 < D_800EB76C_minigame) {
                    if (func_800E2ED4_minigame(stickX, -stickY, sindf(data->unk3C), cosdf(data->unk3C)) < 0.0f) {
                        func_800E5690_minigame(arg0, 0x20);
                    }
                }
            }
            if (time >= 15.0f && data->unk40 < D_800EB76C_minigame) {
                if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                    if (data->unk40 < D_800EB76C_minigame) {
                        if (func_800E2ED4_minigame(stickX, -stickY, sindf(data->unk3C), cosdf(data->unk3C)) < 0.0f) {
                            func_800E5690_minigame(arg0, 0x20);
                        } else {
                            func_800E5690_minigame(arg0, 2);
                            data->unk40 = D_800EB764_minigame;
                            func_800E19FC_minigame(data, 1);
                        }
                    }
                } else {
                    func_800E5690_minigame(arg0, 0);
                }
            }
        }
        if (data->unk53[0] >= 0) {
            accel = ((D_800EC1C0_minigame_ObjData *)D_800EC1C0_minigame[data->unk53[0]]->data)->unk08;
        } else {
            accel = D_800EB740_minigame;
        }
        accel *= 2.0f;
        if (data->unk40 < D_800EB770_minigame) {
            data->unk40 += accel;
            if (D_800EB770_minigame <= data->unk40) {
                data->unk40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame <= data->unk40) {
            data->unk40 -= accel;
            if (data->unk40 <= D_800EB770_minigame) {
                data->unk40 = D_800EB770_minigame;
            }
        }
        newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
            if (pressed & 0x8000) {
                func_800E3820_minigame(arg0, data);
            } else if (pressed & 0x4000) {
                func_800E38A4_minigame(arg0, data);
                func_800E23E0_minigame(arg0);
            }
        }
        data->unkC6 = 0;
    } else if (state & 0x320) {
        f32 time;
        f32 vy;
        f32 dist;

        time = Hu3DMotionShiftTimeGet(model);
        if (time == -1.0f) {
            time = Hu3DData[model].motTime;
        }
        vy = data->unk38;
        if (!(state & 0x300)) {
            if (((time > 5.0f) & (time < 7.0f)) && !(held & 0x8000) && (!(data->unk50 & 8) & (vy < 0.0f))) {
                data->unk38 = -D_800EB744_minigame * 0.2f;
            }
            if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                D_800EBE2C_minigame = stickX / D_800EB74C_minigame * data->unkB4;
                D_800EC5D8_minigame = -(f32)stickY / D_800EB74C_minigame * data->unkB4;
                dist = HuSqrtf(D_800EBE2C_minigame * D_800EBE2C_minigame + D_800EC5D8_minigame * D_800EC5D8_minigame);
                angle = atan2df(D_800EBE2C_minigame, D_800EC5D8_minigame) + data->unk60;
                D_800EBE2C_minigame = sindf(angle) * dist;
                D_800EC5D8_minigame = cosdf(angle) * dist;
                if (data->unk50 & 8) {
                    D_800EBE2C_minigame *= 0.2f;
                    D_800EC5D8_minigame *= 0.2f;
                }
            }
            if (pressed & 0x4000) {
                func_800E3D3C_minigame(arg0, data);
            }
            if ((pressed & 0x2000) && !(data->unk50 & 8)) {
                func_800E3AB8_minigame(arg0, data);
            }
            if (vy > D_800EB774_minigame) {
                vy = D_800EB774_minigame;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += D_800EB748_minigame;
        } else {
            if (vy > D_800EB774_minigame) {
                vy = D_800EB774_minigame;
            }
            if (time > 26.0f) {
                newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
                data->unk38 += D_800EB748_minigame * 2.0f;
            } else if (state & 0x100) {
                newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
                data->unk38 += D_800EB748_minigame / 2.0f;
            } else {
                newY = y;
            }
            if (state & 0x100) {
                func_800E3E24_minigame(arg0, x, newY, z);
            }
        }
        y = func_800D9028_minigame(arg0, x, newY, z, y);
        if (data->unk38 == 1000.0f) {
            other = D_800EC1C0_minigame[data->unk53[0]];
            otherData = other->data;
            if (otherData->unk03 == 2) {
                func_800DFD9C_minigame(arg0, x, other->trans.y, z);
            } else if (state & 0x200) {
                if (!(data->unk50 & 0x80) && data->unkBE == 0) {
                    func_800E3B98_minigame(arg0, data, otherData, x, y, z);
                } else {
                    func_800E3CA0_minigame(arg0, data, otherData, x, y, z);
                }
            } else {
                func_800E39CC_minigame(arg0, data, otherData, stickX, stickY);
            }
        }
        data->unkC6 = 0;
    } else if (state & 0xC0) {
        func_800E3F44_minigame(arg0, state, x, y, z);
        if (data->unk38 == 1000.0f) {
            if (data->unk40 < D_800EB770_minigame) {
                data->unk40 += D_800EB740_minigame * 2.0f;
                if (D_800EB770_minigame < data->unk40) {
                    data->unk40 = D_800EB770_minigame;
                }
            } else if (D_800EB770_minigame < data->unk40) {
                data->unk40 += -D_800EB740_minigame * 2.0f;
                if (data->unk40 < D_800EB770_minigame) {
                    data->unk40 = D_800EB770_minigame;
                }
            }
            newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
            if (newY != 65536.0f) {
                y = newY;
            }
        } else {
            f32 vy = data->unk38;
            f32 time;

            if (vy > D_800EB774_minigame) {
                vy = D_800EB774_minigame;
            }
            time = Hu3DMotionShiftTimeGet(model);
            if (time == -1.0f) {
                time = Hu3DData[model].motTime;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            if (time > 30.0f) {
                data->unk38 += D_800EB748_minigame * 2.0f;
            } else {
                data->unk38 += D_800EB748_minigame / 2.0f;
            }
            y = func_800D9028_minigame(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = D_800EC1C0_minigame[data->unk53[0]];
                if (((D_800EC1C0_minigame_ObjData *)other->data)->unk03 == 2) {
                    func_800DFD9C_minigame(arg0, x, other->trans.y, z);
                } else if (abs(stickX) < 8 && abs(stickY) < 8) {
                    data->unk40 = D_800EB770_minigame;
                    func_800E5690_minigame(arg0, 0x15);
                    func_800E19FC_minigame(data, 4);
                } else {
                    func_800E5690_minigame(arg0, 1);
                    data->unk40 = D_800EB768_minigame;
                    func_800E19FC_minigame(data, 1);
                }
            }
        }
        data->unkC6 = 0;
    } else if (state & 6) {
        avg = func_800E2250_minigame(arg0, stickX, stickY);
        avgX = avg >> 16;
        avgY = avg;
        speed = HuSqrtf(avgX * avgX + avgY * avgY) / D_800EB75C_minigame;
        if (data->unk53[0] >= 0) {
            D_800EC1C0_minigame_ObjData *otherData = D_800EC1C0_minigame[data->unk53[0]]->data;

            if (otherData->unk0C != 0.0f) {
                data->unk40 += speed / otherData->unk0C;
            } else {
                data->unk40 += speed / D_800EB73C_minigame;
            }
            if (stickX | stickY) {
                data->unk40 -= otherData->unk08;
            } else {
                data->unk40 += -otherData->unk08 * 3.0f;
            }
        } else {
            data->unk40 += speed / D_800EB73C_minigame;
            if (stickX | stickY) {
                data->unk40 -= D_800EB740_minigame;
            } else {
                data->unk40 += -D_800EB740_minigame * 3.0f;
            }
        }
        speed = func_800DFD48_minigame(speed);
        if (speed < data->unk40) {
            data->unk40 = speed;
        }
        if (data->unk40 < D_800EB770_minigame) {
            data->unk40 = D_800EB770_minigame;
        }
        if (abs(avgX) >= 9 || abs(avgY) >= 9) {
            data->unk3C = atan2df(avgX, -avgY) + data->unk60;
        }
        newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
            if (!(func_800E4A90_minigame(arg0) & 0xC00)) {
                if (pressed & 0x8000) {
                    func_800E3820_minigame(arg0, data);
                } else if (pressed & 0x4000) {
                    func_800E38A4_minigame(arg0, data);
                } else {
                    dx = stickX - avgX;
                    dz = stickY - avgY;
                    if (HuSqrtf(dx * dx + dz * dz) > 65.0f) {
                        if (fabs(data->unk40) >= D_800EB764_minigame) {
                            func_800E5690_minigame(arg0, 0x11);
                            data->unk40 = D_800EB768_minigame;
                            func_800E19FC_minigame(data, 2);
                            px = x + sindf(data->unk3C) * 70.0f;
                            func_800E4C88_minigame(arg0, 4, px, y, z + cosdf(data->unk3C) * 70.0f, 0.0f,
                                                   data->unk3C + 180.0f);
                        }
                    } else if (HuSqrtf(avgX * avgX + avgY * avgY) > 43.0f && abs(stickX) < 8 && abs(stickY) < 8) {
                        if (fabs(data->unk40) >= D_800EB764_minigame) {
                            func_800E5690_minigame(arg0, 0x11);
                            data->unk40 = D_800EB768_minigame;
                            func_800E19FC_minigame(data, 2);
                            px = x + sindf(data->unk3C) * 70.0f;
                            func_800E4C88_minigame(arg0, 4, px, y, z + cosdf(data->unk3C) * 70.0f, 0.0f,
                                                   data->unk3C + 180.0f);
                        }
                    } else if (data->unk40 == D_800EB770_minigame) {
                        data->unkC6 = 0;
                        func_800E5690_minigame(arg0, 0);
                        if (data->unkC4 > 0) {
                            if (data->unkC5 > 0) {
                                HuAudFXStop(data->unkC5);
                            }
                            data->unkC4 = -1;
                        }
                    } else if (D_800EB764_minigame < speed) {
                        f32 time;

                        motion = 2;
                        turn = func_800E240C_minigame(data->unk59, 12, stickX, stickY);
                        if (turn > 0) {
                            data->unkC6++;
                            if (data->unkC6 >= 0) {
                                if (data->unkC6 > 12) {
                                    data->unkC6 = 12;
                                    motion = 4;
                                }
                            }
                        } else if (turn < 0) {
                            data->unkC6--;
                            if (data->unkC6 < 0) {
                                if (data->unkC6 < -12) {
                                    data->unkC6 = -12;
                                    motion = 3;
                                }
                            }
                        } else {
                            data->unkC6 = 0;
                        }
                        if (func_800E5690_minigame(arg0, motion) == 1) {
                            func_800E1A9C_minigame(data, 1);
                        } else {
                            time = Hu3DMotionShiftTimeGet(model);
                            if (time == -1.0f) {
                                time = Hu3DData[model].motTime;
                            }
                            if (time == 0.0f) {
                                func_800E1A9C_minigame(data, 1);
                            }
                        }
                        if (data->unkBC < 60) {
                            px = x - sindf(data->unk3C) * 20.0f;
                            func_800E4C88_minigame(arg0, 3, px, y, z - cosdf(data->unk3C) * 20.0f, 0.0f, data->unk3C);
                        }
                        data->unkBC++;
                        if (data->unkBC > 200) {
                            data->unkBC = 200;
                        }
                        if (data->unk90 > D_800EB768_minigame || data->unk98 > D_800EB768_minigame) {
                            px = x - sindf(data->unk3C) * 20.0f;
                            func_800E4C88_minigame(arg0, 3, px, y, z - cosdf(data->unk3C) * 20.0f, 0.0f, data->unk3C);
                        }
                    } else {
                        f32 time;

                        data->unkC6 = 0;
                        if (func_800E5690_minigame(arg0, 1) == 1) {
                            func_800E1A9C_minigame(data, 0);
                        } else {
                            time = Hu3DMotionShiftTimeGet(model);
                            if (time == -1.0f) {
                                time = Hu3DData[model].motTime;
                            }
                            if (time == 0.0f) {
                                func_800E1A9C_minigame(data, 0);
                            }
                        }
                        data->unkBC = 0;
                    }
                }
            }
        }
    } else if (state & 0x20000) {
        omObjData *other = D_800EC1C0_minigame[data->unk53[0]];

        y -= 20.0f;
        if (y < other->trans.y - 75.0f) {
            y = other->trans.y - 75.0f;
        }
        if (data->unk40 > D_800EB770_minigame) {
            data->unk40 -= D_800EB740_minigame;
            if (data->unk40 <= D_800EB770_minigame) {
                data->unk40 = D_800EB770_minigame;
            }
        } else if (data->unk40 < D_800EB770_minigame) {
            data->unk40 += D_800EB740_minigame;
            if (D_800EB770_minigame <= data->unk40) {
                data->unk40 = D_800EB770_minigame;
            }
        }
        if (arg0->model[2] != 0) {
            Hu3DModelPosSet(arg0->model[2], x, other->trans.y - 64.0f, z);
            Hu3DModelScaleSet(arg0->model[2], 6.0f, 6.0f, 6.0f);
        }
    } else if (state & 0xC0000) {
        if (state & 0x40000) {
            func_800E3FD8_minigame(arg0, x, y, z);
        } else {
            func_800E4248_minigame(arg0, x, y, z);
        }
        if (data->unk40 < D_800EB770_minigame) {
            data->unk40 += D_800EB740_minigame * 2.0f;
            if (D_800EB770_minigame < data->unk40) {
                data->unk40 = D_800EB770_minigame;
            }
        } else if (D_800EB770_minigame < data->unk40) {
            data->unk40 += -D_800EB740_minigame * 2.0f;
            if (data->unk40 < D_800EB770_minigame) {
                data->unk40 = D_800EB770_minigame;
            }
        }
        newY = func_800D972C_minigame(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
        }
    } else if (state & 0x1000) {
        data->unk40 = D_800EB770_minigame;
    } else if (state & 0x200000) {
        if (data->unk104[20] != NULL) {
            data->unk104[20](arg0, &x, &y, &z);
        }
    }
    speed = data->unk40;
    if (data->unk50 & 6) {
        speed *= 0.6f;
    }
    speed *= (prevVy != 1000.0f) ? data->unk4C * data->unkB4 : data->unkB4;
    x += sindf(data->unk3C) * speed + D_800EBE2C_minigame;
    z += cosdf(data->unk3C) * speed + D_800EC5D8_minigame;
    func_80088910_main(Hu3DData[arg0->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
    func_800E17D4_minigame(arg0, x, y, z);
    if (data->unk104[1] != NULL) {
        data->unk104[1](arg0);
    }
    func_800E4E30_minigame(arg0);
    func_800E5138_minigame(arg0);
}

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

void func_800DFD9C_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    s16 temp;

    func_800E5690_minigame(arg0, 0x10);
    temp = data->unk21[2];
    func_80014850_main(temp);
    func_800146DC_main(temp, 4, 4);
    Hu3DModelPosSet(arg0->model[2], x, y, z);
    data->unk40 = D_800EB770_minigame;
    func_800E1810_minigame();
}

void func_800DFE44_minigame(omObjData *arg0) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    f32 time;

    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 28.0f && time <= 29.0f) {
        func_800E2CA4_minigame(arg0, (data->unk40 + D_800EB768_minigame) * data->unkCC);
    }
}

void func_800DFF3C_minigame(omObjData *arg0, f32 x, f32 y, f32 z) {
    func_800E1BA8_minigame_ObjData *data = arg0->data;
    func_800E1BA8_minigame_ObjData *otherData;
    A96F0_ObjData *itemData;
    omObjData *other;
    Hu3DSphere sphere;
    f32 time;
    f32 angle;
    f32 dist;
    f32 dx, dy, dz;
    f32 px, py, pz;
    f32 rot;
    u16 i;

    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if ((time < 16.0f) | (time > 20.0f)) {
        return;
    }
    if (data->unkBE != 0) {
        D_800EC288_minigame++;
        return;
    }
    if (data->unk50 & 0x400) {
        return;
    }
    dist = data->unk64 + data->unk48;
    angle = data->unk3C;
    px = x + sindf(angle) * dist;
    py = y;
    pz = z + cosdf(angle) * dist;
    data->unkF0 = 1;
    for (i = 0; i < D_800EC280_minigame; i++) {
        other = D_800EC598_minigame[i];
        otherData = other->data;
        if (otherData->unk5C & 0x8C00) {
            continue;
        }
        if (otherData->unk50 & 7) {
            continue;
        }
        if (otherData->unkBE != 0) {
            continue;
        }
        if (otherData->unk50 & 0x400) {
            continue;
        }
        if (data == otherData) {
            continue;
        }
        if (func_800E4510_minigame(arg0, other) != 1) {
            continue;
        }
        dx = other->trans.x - px;
        dy = other->trans.y - py;
        dz = other->trans.z - pz;
        if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + 30.0f) {
            func_800E454C_minigame(arg0, other, dx, dz, i);
        }
    }
    if (!(data->unk50 & 0x17)) {
        for (i = 0; i < D_800EC1B8_minigame; i++) {
            other = D_800EBE70_minigame[i];
            itemData = other->data;
            if (!(itemData->unk50 & 0x20)) {
                continue;
            }
            if (itemData->unk50 & 0x10) {
                continue;
            }
            if (data->unkBE != 0) {
                D_800EC288_minigame++;
                continue;
            }
            dx = other->trans.x - px;
            dy = other->trans.y - py;
            dz = other->trans.z - pz;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (itemData->unk48 + data->unk48);
            if (dist < 0.0f) {
                if (data->unkEC == NULL || data->unkEC(arg0, other) != 1) {
                    func_800E2DA4_minigame(arg0, other);
                }
            }
        }
    }
    sphere.pos.x = sindf(angle) * data->unk48 + arg0->trans.x;
    sphere.pos.y = py;
    sphere.pos.z = cosdf(angle) * data->unk48 + arg0->trans.z;
    sphere.radius = data->unk64;
    data->unk53[2] = func_800DD530_minigame(arg0, &sphere, -D_800EB760_minigame);
    if (D_800EB736_minigame != 0 && func_800E1510_minigame(D_800EC286_minigame) == 1) {
        rot = atan2df(D_800EBEB8_minigame[0].unk00 - arg0->trans.x, D_800EBEB8_minigame[0].unk08 - arg0->trans.z);
        func_800E4C88_minigame(arg0, 6, px, py, pz, 0.0f, rot + 180.0f);
    }
    D_800EB736_minigame = 0;
    D_800EBE2C_minigame = D_800EC5D8_minigame = 0.0f;
}

void func_800E0430_minigame(f32 x, f32 y, f32 z) {
    D_800EC298_minigame[D_800EB736_minigame].x = x;
    D_800EC298_minigame[D_800EB736_minigame].y = y;
    D_800EC298_minigame[D_800EB736_minigame].z = z;
    func_800202FC_main(&D_800EC298_minigame[D_800EB736_minigame]);
}

void func_800E048C_minigame(f32 arg0, f32 arg1, f32 arg2) {
    D_800EBEB8_minigame[D_800EB736_minigame].unk00 = arg0;
    D_800EBEB8_minigame[D_800EB736_minigame].unk04 = arg1;
    D_800EBEB8_minigame[D_800EB736_minigame].unk08 = arg2;
}

void func_800E04C8_minigame(omObjData *arg0, s32 arg1) {
    func_800E1BA8_minigame_ObjData *data;
    s32 i;

    if (arg1 != 0) {
        return;
    }
    if (D_800CDA7C_main[arg1] & R_TRIG) {
        CZoom -= 20.0f;
    }
    if (D_800CDA7C_main[arg1] & L_TRIG) {
        CZoom += 20.0f;
    }
    if (D_800CDA7C_main[arg1] & U_CBUTTONS) {
        CRot.x += 0.3f;
    }
    if (D_800CDA7C_main[arg1] & D_CBUTTONS) {
        CRot.x -= 0.3f;
    }
    if (D_800CDA7C_main[arg1] & R_CBUTTONS) {
        CRot.y += 1.0f;
    }
    if (D_800CDA7C_main[arg1] & L_CBUTTONS) {
        CRot.y -= 1.0f;
    }
    if (D_800D5558_main[arg1] & U_JPAD) {
        D_800EB780_minigame--;
    } else if (D_800D5558_main[arg1] & D_JPAD) {
        D_800EB780_minigame++;
    }
    if (D_800EB780_minigame < 0) {
        D_800EB780_minigame = 0;
    }
    if (D_800EB780_minigame > 0) {
        D_800EB780_minigame = 0;
    }
    switch (D_800EB780_minigame) {
        case 0:
            if (D_800D5558_main[arg1] & (L_JPAD | R_JPAD)) {
                if (D_800EB73B_minigame != 0) {
                    D_800EB73B_minigame = 0;
                } else {
                    D_800EB73B_minigame = 1;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB73C_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB73C_minigame -= 0.1f;
            }
            if (D_800EB73C_minigame > 50.0f) {
                D_800EB73C_minigame = 50.0f;
            }
            if (D_800EB73C_minigame < 1.0f) {
                D_800EB73C_minigame = 1.0f;
            }
            break;
        case 3:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB740_minigame += 0.001f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB740_minigame -= 0.001f;
            }
            if (D_800EB740_minigame > 0.999f) {
                D_800EB740_minigame = 0.999f;
            }
            if (D_800EB740_minigame < 0.001f) {
                D_800EB740_minigame = 0.001f;
            }
            break;
        case 4:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB744_minigame += 0.01f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB744_minigame -= 0.01f;
            }
            if (D_800EB744_minigame > 2.0f) {
                D_800EB744_minigame = 2.0f;
            }
            if (D_800EB744_minigame < 0.7f) {
                D_800EB744_minigame = 0.7f;
            }
            break;
        case 5:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB748_minigame += 0.001f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB748_minigame -= 0.001f;
            }
            if (D_800EB748_minigame > 0.2f) {
                D_800EB748_minigame = 0.2f;
            }
            if (D_800EB748_minigame < 0.01f) {
                D_800EB748_minigame = 0.01f;
            }
            break;
        case 6:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB74C_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB74C_minigame -= 0.1f;
            }
            if (D_800EB74C_minigame > 30.0f) {
                D_800EB74C_minigame = 30.0f;
            }
            if (D_800EB74C_minigame < 0.0f) {
                D_800EB74C_minigame = 0.0f;
            }
            break;
        case 7:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB750_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB750_minigame -= 0.1f;
            }
            if (D_800EB750_minigame > 100.0f) {
                D_800EB750_minigame = 100.0f;
            }
            if (D_800EB750_minigame < 20.0f) {
                D_800EB750_minigame = 20.0f;
            }
            break;
        case 8:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB760_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB760_minigame -= 0.1f;
            }
            if (D_800EB760_minigame > 30.0f) {
                D_800EB760_minigame = 30.0f;
            }
            if (D_800EB760_minigame < 10.0f) {
                D_800EB760_minigame = 10.0f;
            }
            D_800EB76C_minigame = D_800EB760_minigame / 4.0f;
            D_800EB768_minigame = D_800EB760_minigame / 2.0f;
            D_800EB764_minigame = D_800EB76C_minigame * 3.0f;
            D_800EB75C_minigame = 60.0f / D_800EB760_minigame;
            break;
        case 9:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB754_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB754_minigame -= 0.1f;
            }
            if (D_800EB754_minigame > 100.0f) {
                D_800EB754_minigame = 100.0f;
            }
            if (D_800EB754_minigame < 40.0f) {
                D_800EB754_minigame = 40.0f;
            }
            for (i = 0; i < D_800EC280_minigame; i++) {
                data = D_800EC598_minigame[i]->data;
                data->unk48 = D_800EB754_minigame;
            }
            break;
        case 10:
            if (D_800CDA7C_main[arg1] & R_JPAD) {
                D_800EB758_minigame += 0.1f;
            }
            if (D_800CDA7C_main[arg1] & L_JPAD) {
                D_800EB758_minigame -= 0.1f;
            }
            if (D_800EB758_minigame > 100.0f) {
                D_800EB758_minigame = 100.0f;
            }
            if (D_800EB758_minigame < 10.0f) {
                D_800EB758_minigame = 40.0f;
            }
            for (i = 0; i < D_800EC280_minigame; i++) {
                data = D_800EC598_minigame[i]->data;
                data->unk64 = D_800EB758_minigame;
            }
            break;
    }
    fontcolor = 15;
    sprintf(D_800D5218_main, "*");
    print8(16, (D_800EB780_minigame + 2) * 8, D_800D5218_main);
    sprintf(D_800D5218_main, "CAMERA :[%s]", D_800EB73B_minigame ? "HOMING" : "LOCK");
    print8(24, 16, D_800D5218_main);
    if (D_800EB73B_minigame) {
        f32 y = Hu3DData[arg0->model[1]].pos.y;

        if (y != Center.y) {
            y = Center.y + (y - Center.y) / 20.0f;
        }
        Center.x = Hu3DData[arg0->model[1]].pos.x;
        Center.y = y;
        Center.z = Hu3DData[arg0->model[1]].pos.z;
        // Bug: data is only set by the case 9/10 loops above.
        data->unk60 = CRot.y;
    }
}
