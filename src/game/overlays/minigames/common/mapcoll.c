#include "common.h"
#include "game/overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hmfspr.h"
#include "game/hu3d.h"
#include "game/mapspace.h"
#include "math.h"

s32 mgFieldStatReq = 0;
u8 mgMapBaseNo = 0;
u8 mgPlayerBounceF = 1;
s16 mgWallNum = 0;
s8 mgFloorMapNo = -1;
u8 mgShadowAltF = 0;
u8 mgCharMdlF = 0;
u8 mgDebugCamHomingF = 0;
f32 mgPlayerAccel = 15.0f;
f32 mgPlayerFriction = 0.5f;
f32 mgPlayerJumpPower = 1.47f;
f32 mgPlayerGravity = 0.15f;
f32 mgPlayerAirStickDiv = 7.0f;
f32 mgPlayerTurnDiv = 30.0f;
f32 mgPlayerRadius = 60.0f;
f32 mgPlayerPunchRadius = 20.0f;
f32 mgPlayerStickDiv = 3.3333333f;
f32 mgPlayerSpeedMax = 18.0f;
f32 mgPlayerSpeedRun = 13.5f;
f32 mgPlayerSpeedWalk = 9.0f;
f32 mgPlayerSpeedMin = 4.5f;
f32 mgPlayerSpeedZero = 0.0f;
f32 mgPlayerFallMax = 1.7f;
f32 mgPlayerAirSpeedScale = 0.5f;
f32 mgPlayerFallInit = 0.147f;
s8 mgDebugMenuNo = 0;
s16 mgPlayerSeTbl[4][14] = { 0 };

extern Vec mgPlayerPrevPos;
extern Vec mgWallNorTbl[];
extern omObjData *mgItemObjTbl[];
extern s8 mgWallMapNo;
extern u16 mgHitSkipCnt;
extern Vec mgWallNorPrevTbl[];

f32 MgMapPrimHeightGet(omObjData *arg0, MgPlayerWork *arg1, f32 arg2) {
    MgMapWork *data = arg0->data;
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
                MgMtxPosYMult(mgMapMtx, &pos);
            }
            arg1->unk8C = pos.y;
            arg1->unk53[3] = data->unk04;
        }
    }
    return data->unk14;
}

f32 MgMapCeilCheck(omObjData *arg0, MgPlayerWork *arg1, f32 arg2, f32 arg3, Vec *arg4) {
    MgMapWork *data = arg0->data;
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

f32 MgFaceRayCross(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out) {
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

    MapTriNormalGet(p0, &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
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

f32 MgPlayerFloorGet(omObjData *arg0, f32 x, f32 y, f32 z, Vec *normal) {
    MgPlayerWork *data = arg0->data;
    Hu3DSphere sphere;
    Vec tmp;
    Vec dir;
    omObjData *obj;
    MgMapWork *objData;
    Hu3DPoint *points;
    Hu3DQuad *quad;
    f32 best;
    f32 height;
    u8 transformed;
    s16 i;

    best = -65536.0f;
    sphere.radius = 10.0f;
    data->unk53[0] = -1;
    for (i = 0; i < mgMapObjNum; i++) {
        obj = mgMapObjTbl[i];
        objData = obj->data;
        if (i == mgMapBaseNo) {
            continue;
        }
        if (data->unk00[i] & 1) {
            continue;
        }
        sphere.pos.x = x;
        sphere.pos.y = y;
        sphere.pos.z = z;
        MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &sphere.pos, obj);
        if (objData->unk06 & 4) {
            if (MgBoundsCheck(Hu3DData[obj->model[0]].hmf->unk60, &sphere.pos) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 0x7A) {
            if (objData->unk06 & 0x50) {
                if (MgMapAreaCheck(&sphere.pos, objData) == 0) {
                    continue;
                }
            }
            height = MgMapPrimHeightGet(obj, data, sphere.pos.y);
            if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                sphere.pos.y = height;
                MgMtxPosYMult(mgMapMtx, &sphere.pos);
                height = sphere.pos.y;
                if (height >= best && height < y + 150.0f) {
                    best = height;
                    data->unk53[0] = mgFloorMapNo = i;
                    if (normal != NULL) {
                        normal->z = normal->x = 0.0f;
                        normal->y = 1.0f;
                        MgMtxDirMult(mgMapMtx, normal);
                        MapVecNormalize(normal);
                    }
                }
            } else if (height >= best && height < y + 150.0f) {
                best = height;
                mgFloorMapNo = i;
                data->unk53[0] = i;
                if (normal != NULL) {
                    normal->x = 0.0f;
                    normal->y = 1.0f;
                    normal->z = 0.0f;
                }
            }
        } else {
            points = (Hu3DPoint *)Hu3DData[obj->model[0]].hmf->unk50;
            Hu3DQuadPoolCollect(obj->model[0], &mgQuadPool, MgFloorFaceFilter, &sphere.pos);
            for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
                 quad = Hu3DQuadPoolNext(&mgQuadPool)) {
                transformed = 0;
                if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                    obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                    tmp.x = x;
                    tmp.y = y + 101.23f;
                    tmp.z = z;
                    MgMtxPosMult(mgMapInvMtx, &tmp);
                    dir.x = tmp.x - sphere.pos.x;
                    dir.y = tmp.y - sphere.pos.y;
                    dir.z = tmp.z - sphere.pos.z;
                    MapVecNormalize(&dir);
                    MgFaceRayCross(sphere.pos.x, sphere.pos.y, sphere.pos.z, points, quad, &dir, &sphere.pos);
                    MgMtxPosYMult(mgMapMtx, &sphere.pos);
                    MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &dir);
                    MgMtxDirMult(mgMapMtx, &dir);
                    height = MgMapCeilCheck(obj, data, sphere.pos.y, y, &dir);
                    transformed = 1;
                } else {
                    height = MapCalcPoint(sphere.pos.x, sphere.pos.y, sphere.pos.z, points, quad);
                }
                if (height >= best && height < y + 150.0f) {
                    best = height;
                    mgFloorMapNo = i;
                    data->unk53[0] = i;
                    if (normal != NULL) {
                        MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           normal);
                        if (transformed == 1) {
                            tmp.x = normal->x;
                            tmp.y = normal->y;
                            tmp.z = normal->z;
                            MgMtxDirMult(mgMapMtx, &tmp);
                            normal->x = tmp.x;
                            normal->y = tmp.y;
                            normal->z = tmp.z;
                            MapVecNormalize(normal);
                        }
                    }
                }
            }
        }
    }
    return best;
}

// prevY is unused, but callers pass it on the stack.
f32 MgPlayerAirMove(omObjData *arg0, f32 x, f32 y, f32 z, f32 prevY) {
    MgPlayerWork *data = arg0->data;
    Hu3DSphere sphere;
    Vec floorNormal;
    Vec normal2;
    Vec *normal;
    MgMapWork *objData;
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
    newX += mgMoveOfsX;
    newZ = z + cosdf(data->unk3C) * dist;
    newZ += mgMoveOfsZ;
    groundY = -65536.0f;
    best = groundY;
    if (MgPlayerObjHitCheck(arg0, newX, y, newZ) != 2) {
        MgMoveOfsClamp(arg0);
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
        MgPlayerWallCheck(arg0, &sphere, 0);
        MgMoveOfsClamp(arg0);
        sphere.pos.x = newX + mgMoveOfsX;
        sphere.pos.y = y;
        sphere.pos.z = newZ + mgMoveOfsZ;
        if (!(data->unk00[mgMapBaseNo] & 1)) {
            objData = mgMapObjTbl[mgMapBaseNo]->data;
            if (objData->unk06 & 0x7A) {
                if (MgMapAreaCheck(&sphere.pos, objData) == 1) {
                    height = objData->unk14;
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        mgFloorMapNo = mgMapBaseNo;
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
                points = (Hu3DPoint *)Hu3DData[mgMapObjTbl[mgMapBaseNo]->model[0]].hmf->unk50;
                Hu3DQuadPoolCollect(mgMapObjTbl[mgMapBaseNo]->model[0], &mgQuadPool,
                                   MgFloorFaceFilter, &sphere.pos);
                for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
                     quad = Hu3DQuadPoolNext(&mgQuadPool)) {
                    height = MapCalcPoint(newX + mgMoveOfsX, y, newZ + mgMoveOfsZ, points,
                                                quad);
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        mgFloorMapNo = mgMapBaseNo;
                    }
                    if (groundY < height && groundY < y + 35.0f) {
                        groundY = height;
                        MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           &floorNormal);
                        normal = &floorNormal;
                    }
                }
                if (best == -65536.0f) {
                    best = -65536.0f;
                }
            }
        }
        height = MgPlayerFloorGet(arg0, newX + mgMoveOfsX, y, newZ + mgMoveOfsZ, &normal2);
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
            data->unk4C = mgPlayerAirSpeedScale;
            if (data->unk38 < 0.0f) {
                data->unk38 = 0.0f;
            }
            data->unk53[0] = -1;
            if (data->unk8C != 65536.0f) {
                y = data->unk8C - data->unk34;
                MgPlayerCeilHit(arg0, y);
            }
        } else if (y < best) {
            data->unk53[0] = mgFloorMapNo;
            y = MgPlayerSnapYGet(arg0, best);
            data->unk38 = 1000.0f;
            data->unk50 &= ~8;
            if (data->unk00[mgFloorMapNo] & 8) {
                MgFieldStatLand();
            }
        } else {
            data->unk53[0] = -1;
            if (data->unk8C != 65536.0f) {
                y = data->unk8C - data->unk34;
                MgPlayerCeilHit(arg0, y);
            }
        }
    } else {
        sphere.pos.x = newX + mgMoveOfsX;
        sphere.pos.y = y;
        sphere.pos.z = newZ + mgMoveOfsZ;
        sphere.radius = data->unk48;
        MgPlayerWallCheck(arg0, &sphere, 0);
    }
    if (arg0->model[1] != 0) {
        MgPlayerShadowSet(arg0, newX, y, newZ, groundY, normal);
    }
    data->unk90 = data->unk94 = data->unk98 = 0.0f;
    data->unk9C = data->unkA4 = 0.0f;
    arg0->rot.x = arg0->rot.z = 0.0f;
    return y;
}

f32 MgPlayerGroundMove(omObjData *arg0, f32 angle, f32 x, f32 y, f32 z) {
    s8 idx = -1;
    MgPlayerWork *data = arg0->data;
    Hu3DSphere sphere;
    Vec floorNormal;
    Vec normal2;
    Vec *normal;
    MgMapWork *objData;
    MgMapWork *platform;
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
        mgMoveOfsX += data->unk90;
    }
    if (fabs(data->unk98) > 1.0) {
        mgMoveOfsZ += data->unk98;
    }
    newX = x + sindf(angle) * dist;
    newX += mgMoveOfsX;
    newZ = z + cosdf(angle) * dist;
    newZ += mgMoveOfsZ;
    groundY = -65536.0f;
    best = groundY;
    if (MgPlayerObjHitCheck(arg0, newX, y, newZ) != 2) {
        MgMoveOfsClamp(arg0);
        speed = data->unk40;
        mult = data->unkB4;
        if (data->unk50 & 6) {
            dist = speed * 0.6f * mult;
        } else {
            dist = speed * mult;
        }
        newX = x + sindf(angle) * dist;
        newZ = z + cosdf(angle) * dist;
        sphere.pos.x = newX + mgMoveOfsX;
        sphere.pos.y = y;
        sphere.pos.z = newZ + mgMoveOfsZ;
        sphere.radius = data->unk48;
        MgPlayerWallCheck(arg0, &sphere, 0);
        MgMoveOfsClamp(arg0);
        sphere.pos.x = newX + mgMoveOfsX;
        sphere.pos.y = y;
        sphere.pos.z = newZ + mgMoveOfsZ;
        if (!(data->unk00[mgMapBaseNo] & 1)) {
            objData = mgMapObjTbl[mgMapBaseNo]->data;
            if (objData->unk06 & 0x7A) {
                if (MgMapAreaCheck(&sphere.pos, objData) == 1) {
                    height = objData->unk14;
                    if (best < height && height < y + 150.0f) {
                        best = height;
                        idx = mgMapBaseNo;
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
                points = (Hu3DPoint *)Hu3DData[mgMapObjTbl[mgMapBaseNo]->model[0]].hmf->unk50;
                Hu3DQuadPoolCollect(mgMapObjTbl[mgMapBaseNo]->model[0], &mgQuadPool,
                                   MgFloorFaceFilter, &sphere.pos);
                for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
                     quad = Hu3DQuadPoolNext(&mgQuadPool)) {
                    height = MapCalcPoint(newX, y, newZ, points, quad);
                    if (best < height) {
                        best = height;
                        idx = mgMapBaseNo;
                    }
                    if (groundY < height && groundY < y + 35.0f) {
                        groundY = height;
                        MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           &floorNormal);
                        normal = &floorNormal;
                    }
                }
                if (best == -65536.0f) {
                    best = -65536.0f;
                }
            }
        }
        height = MgPlayerFloorGet(arg0, newX + mgMoveOfsX, y, newZ + mgMoveOfsZ, &normal2);
        if (best < height && height < y + 35.0f) {
            idx = mgFloorMapNo;
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
            y = MgPlayerSnapYGet(arg0, best);
            if (data->unk00[idx] & 8) {
                MgFieldStatLand();
            }
            data->unk38 = 1000.0f;
            if (data->unk8C != 65536.0f) {
                MgPlayerCeilHit(arg0, y);
            }
        } else {
            MgPlayerMotSet(arg0, 6);
            data->unk38 = mgPlayerFallInit;
            data->unk53[0] = -1;
            MgPlayerSePlay(data, 13);
            return 65536.0f;
        }
    } else {
        sphere.pos.x = newX + mgMoveOfsX;
        sphere.pos.y = y;
        sphere.pos.z = newZ + mgMoveOfsZ;
        sphere.radius = data->unk48;
        MgPlayerWallCheck(arg0, &sphere, 0);
    }
    if (arg0->model[1] != 0) {
        MgPlayerShadowSet(arg0, newX, y, newZ, groundY, normal);
    }
    if (data->unk53[0] >= 0) {
        platform = mgMapObjTbl[data->unk53[0]]->data;
        data->unk90 = normal->x * platform->unk10;
        data->unk94 = normal->y;
        data->unk98 = normal->z * platform->unk10;
        if (platform->unk06 & 0x400) {
            MgPlayerTiltSet(arg0, normal);
            return y;
        }
    } else {
        data->unk90 = data->unk94 = data->unk98 = 0.0f;
        data->unk9C = data->unkA4 = 0.0f;
        arg0->rot.x = arg0->rot.z = 0.0f;
    }
    return y;
}

f32 MgPlayerSnapYGet(omObjData *arg0, f32 arg1) {
    MgPlayerWork *data = arg0->data;
    u8 player = data->unk53[0];
    f32 ret = arg0->trans.y;

    if (data->unk00[player] & 2) {
        ret = arg1;
    }
    return ret;
}

s32 MgFaceSideGet(Vec *pos, Hu3DQuad *quad, Hu3DPoint *points) {
    Vec normal;
    Hu3DPoint *p0;
    f32 px;
    f32 py;
    f32 pz;

    MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
    p0 = &points[quad->vtx[1]];
    px = p0->x;
    py = p0->y;
    pz = p0->z;
    px -= pos->x;
    py -= pos->y;
    pz -= pos->z;
    return (px * normal.x + py * normal.y + pz * normal.z < 0.0f) ? -1 : 1;
}

s32 MgFaceSphereProject(Hu3DSphere *sphere, Hu3DQuad *quad, Hu3DPoint *points) {
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
    MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]], &normal);
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

f32 MgTriCross(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal) {
    f32 ax = p->x - x;
    f32 ay = p->y - y;
    f32 az = p->z - z;
    f32 bx = q->x - x;
    f32 by = q->y - y;
    f32 bz = q->z - z;

    return (ay * bz - az * by) * normal->x + (az * bx - ax * bz) * normal->y + (ax * by - ay * bx) * normal->z;
}

s32 MgFaceInsideCheck(Vec *pos, s16 *face, Hu3DPoint *points, Vec *normal) {
    f32 x = pos->x;
    f32 y = pos->y;
    f32 z = pos->z;
    s32 count;
    s32 i;
    s32 next;

    count = ((u16)face[0] >> 14) + 2;
    face++;
    if (MgTriCross(x, y, z, &points[face[0]], &points[face[1]], normal) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MgTriCross(x, y, z, &points[face[i]], &points[face[next]], normal) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MgTriCross(x, y, z, &points[face[i]], &points[face[next]], normal) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

s32 MgFaceInsideXZCheck(Vec *pos, s16 *face, Hu3DPoint *points) {
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
    if (MapXZCross(x, z, &points[face[0]], &points[face[1]]) > 0.0f) {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MapXZCross(x, z, &points[face[i]], &points[face[next]]) < 0.0f) {
                return FALSE;
            }
        }
    } else {
        for (i = 1; i < count; i++) {
            next = (i + 1) % count;
            if (MapXZCross(x, z, &points[face[i]], &points[face[next]]) > 0.0f) {
                return FALSE;
            }
        }
    }
    return TRUE;
}

s32 MgPlayerObjHitCheck(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = arg0->data;
    MgPlayerWork *otherData;
    MgItemWork *itemData;
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
    for (i = 0; i < mgItemObjNum; i++) {
        other = mgItemObjTbl[i];
        itemData = other->data;
        if (itemData->unk54 == 0) {
            continue;
        }
        dx = other->trans.x - (x + mgMoveOfsX);
        dy = other->trans.y - y;
        dz = other->trans.z - (z + mgMoveOfsZ);
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
                    mgHitSkipCnt++;
                    continue;
                }
                if (data->unk50 & 0x200) {
                    continue;
                }
                dot = MgDirDot(sindf(data->unk3C), cosdf(data->unk3C), dx, dz);
                if (data->unk50 & 0x10) {
                    MgPlayerItemThrow(arg0, mgPlayerSpeedWalk);
                }
                if (dot > 0.0f) {
                    MgPlayerMotSet(arg0, 9);
                    data->unk40 = -mgPlayerSpeedMax;
                } else {
                    MgPlayerMotSet(arg0, 10);
                    data->unk40 = mgPlayerSpeedMax;
                }
                data->unk38 = -mgPlayerJumpPower * 0.7f;
                data->unkBE = 105;
                MgPlayerEffSet(arg0, 5, other->trans.x, y, other->trans.z, 0.0f, atan2df(dx, dz) + 180.0f);
                MgPlayerSePlay(data, 8);
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
                    itemData->unk38 = -mgPlayerJumpPower * 0.6f;
                    if (MgDirDot(sindf(itemData->unk3C), cosdf(itemData->unk3C), dx, dz) < 0.0f) {
                        itemData->unk40 = -mgPlayerSpeedMin;
                    } else {
                        itemData->unk40 = mgPlayerSpeedMin;
                    }
                } else if (itemData->unk40 == mgPlayerSpeedZero) {
                    if (data->unk38 != 1000.0f) {
                        MgPlayerBounce(arg0, dx, dz);
                        MgPlayerSeReq(data, 9);
                    } else {
                        if (dx == 0.0f && dz == 0.0f) {
                            dx = sindf(data->unk3C);
                            dz = cosdf(data->unk3C);
                        }
                        MgMoveOfsAdd(dx, dz, dist);
                    }
                } else {
                    itemData->unk40 = -itemData->unk40;
                }
            } else if (data->unkBE != 0) {
                mgHitSkipCnt++;
            } else {
                MgItemCoinGet(arg0, other);
            }
        }
    }

    y += data->unk48;
    if (data->unk50 & 0x400) {
        return 0;
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        other = mgPlayerObjTbl[i];
        otherData = other->data;
        if (data == otherData) {
            continue;
        }
        dx = other->trans.x - (x + mgMoveOfsX);
        dy = (other->trans.y + otherData->unk48) - y;
        dz = other->trans.z - (z + mgMoveOfsZ);
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
                                MgPlayerEffSet(arg0, 7, x, y, z, 0.0f, 0.0f);
                                if (!(otherData->unk50 & 0x200)) {
                                    MgPlayerSquashSet(other, 1);
                                    MgPlayerMotSet(other, 0x1E);
                                    if (otherData->unk50 & 0x10) {
                                        MgPlayerItemThrow(other, mgPlayerSpeedMin);
                                    }
                                }
                                otherData->unk38 = data->unk38;
                                otherData->unk40 = mgPlayerSpeedZero;
                                MgPlayerBounce(arg0, dx, dz);
                                MgPlayerSeReq(data, 9);
                            } else {
                                if (mgPlayerBounceF == 1) {
                                    MgPlayerRepelPair(arg0, other);
                                } else {
                                    MgMoveOfsAdd(dx, dz, HuSqrtf(dx * dx + dz * dz) - (otherData->unk48 + data->unk48));
                                }
                                return 0;
                            }
                        } else if (dist < 0.0f && dy < -data->unk34 * 0.2) {
                            if (!(otherData->unk50 & 0x200)) {
                                MgPlayerEffSet(arg0, 6, x, y, z, -90.0f, 0.0f);
                                if (otherData->unk50 & 0x10) {
                                    MgPlayerItemThrow(other, mgPlayerSpeedMin);
                                }
                            }
                            if (otherData->unk38 < 0.0f) {
                                otherData->unk38 = 0.0f;
                            }
                            otherData->unk40 = mgPlayerSpeedZero;
                            MgPlayerBounce(arg0, dx, dz);
                            MgPlayerSeReq(data, 9);
                        } else {
                            if (mgPlayerBounceF == 1) {
                                MgPlayerRepelPair(arg0, other);
                            } else {
                                MgMoveOfsAdd(dx, dz, HuSqrtf(dx * dx + dz * dz) - (otherData->unk48 + data->unk48));
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
                                MgPlayerSquashSet(other, 1);
                                MgPlayerMotSet(other, 0);
                                MgPlayerEffSet(arg0, 7, x, y, z, 0.0f, 0.0f);
                                if (otherData->unk50 & 0x10) {
                                    MgPlayerItemThrow(other, mgPlayerSpeedMin);
                                }
                            } else {
                                MgPlayerEffSet(arg0, 6, x, y, z, -90.0f, 0.0f);
                                MgPlayerSquashSet(other, 2);
                                if (otherData->unk50 & 0x10) {
                                    MgPlayerItemThrow(other, mgPlayerSpeedMin);
                                }
                            }
                        }
                        MgPlayerBounce(arg0, dx, dz);
                        MgPlayerSeReq(data, 9);
                        omVibrate(data->unk59, 2, 3, 10);
                        omVibrate(otherData->unk59, 20, 0, 20);
                        return 2;
                    }
                    MgPlayerBounce(arg0, dx, dz);
                    data->unk38 = -mgPlayerJumpPower * 0.6f;
                    data->unk40 *= 0.5;
                    MgPlayerSeReq(data, 9);
                    omVibrate(data->unk59, 2, 3, 10);
                    omVibrate(otherData->unk59, 20, 0, 20);
                    continue;
                }
                if (data->unk38 != 1000.0f && otherData->unk38 != 1000.0f) {
                    if (data->unkBE != 0 || otherData->unkBE != 0) {
                        if (mgPlayerBounceF == 1) {
                            MgPlayerRepelPair(arg0, other);
                            omVibrate(data->unk59, 2, 3, 10);
                            return 0;
                        }
                        MgMoveOfsAdd(dx, dz, dist2);
                        return 0;
                    }
                    continue;
                }
                if (data->unk5C & 0x200) {
                    MgPlayerEffSet(arg0, 7, x, y, z, 0.0f, 0.0f);
                } else {
                    MgPlayerEffSet(arg0, 6, x, y, z, -90.0f, 0.0f);
                }
                omVibrate(data->unk59, 2, 3, 10);
                MgPlayerBounce(arg0, dx, dz);
                MgPlayerSeReq(data, 9);
                continue;
            }
            if (dist2 < 0.0f) {
                if (mgPlayerBounceF == 1) {
                    MgPlayerRepelPair(arg0, other);
                } else {
                    MgMoveOfsAdd(dx, dz, dist2);
                }
            }
            continue;
        }
        dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (otherData->unk48 + data->unk48);
        if (dist < 0.0f) {
            if (otherData->unk38 != 1000.0f && data->unk38 == 1000.0f) {
                continue;
            }
            MgMoveOfsAdd(dx, dz, dist);
            data->unk53[1] = i;
        }
    }
    return 0;
}

void MgMoveOfsClamp(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
    f32 limit = data->unk48;
    f32 angle;

    if (HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ) > limit ||
        fabs(mgMoveOfsX) > limit || fabs(mgMoveOfsZ) > limit) {
        angle = data->unk3C;
        mgMoveOfsX = -sindf(angle) * data->unk40;
        mgMoveOfsZ = -cosdf(angle) * data->unk40;
    }
}

s32 MgFloorFaceFilter(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos) {
    return MgFaceInsideXZCheck(pos, vtx - 1, points);
}

s32 MgWallFaceHit(s32 count, s16 *vtx, Hu3DPoint *points, Hu3DSphere *arg3) {
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

    prev.pos.x = sphere.pos.x = arg3->pos.x + mgMoveOfsX;
    prev.pos.y = sphere.pos.y = arg3->pos.y;
    prev.pos.z = sphere.pos.z = arg3->pos.z + mgMoveOfsZ;
    sphere.radius = arg3->radius;
    face = vtx - 1;
    side = MgFaceSphereProject(&sphere, (Hu3DQuad *)face, points);
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
        MgWallPosSet(closest.x, closest.y, closest.z);
        MapTriNormalGet(&points[vtx[0]], &points[vtx[1]], &points[vtx[2]], &mgWallNorTbl[mgWallNum]);
        mgWallNum++;
        dx = closest.x - prev.pos.x;
        dz = closest.z - prev.pos.z;
        depth = sphere.radius - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            if (MgFaceSideGet(&mgPlayerPrevPos, (Hu3DQuad *)(vtx - 1), points) < 0) {
                dir.x = mgPlayerPrevPos.x - prev.pos.x;
                dir.y = mgPlayerPrevPos.y - prev.pos.y;
                dir.z = mgPlayerPrevPos.z - prev.pos.z;
                MapVecNormalize(&dir);
                if (MgFaceInsideCheck(&prev.pos, vtx - 1, points, &dir) == hit) {
                    depth = HuSqrtf(dx * dx + dz * dz) + sphere.radius;
                }
            } else {
                depth = 0.0f;
            }
        }
        MgMoveOfsAdd(-dx, -dz, depth);
    }
    return hit;
}

s32 MgWallFaceHitEx(s32 count, s16 *vtx, Hu3DPoint *points, MgHitSphere *arg3) {
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

    prev.pos.x = sphere.pos.x = arg3->pos.x + mgMoveOfsX;
    prev.pos.y = sphere.pos.y = arg3->pos.y;
    prev.pos.z = sphere.pos.z = arg3->pos.z + mgMoveOfsZ;
    sphere.radius = prev.radius = arg3->radius;
    face = vtx - 1;
    side = MgFaceSphereProject(&sphere, (Hu3DQuad *)face, points);
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
        prev.pos.x = arg3->prev.x + mgMoveOfsX;
        prev.pos.y = arg3->prev.y;
        prev.pos.z = arg3->prev.z + mgMoveOfsZ;
        MgMtxPosMult(mgMapMtx, &closest);
        MgWallPosSet(closest.x, closest.y, closest.z);
        MapTriNormalGet(&points[vtx[0]], &points[vtx[1]], &points[vtx[2]], &mgWallNorTbl[mgWallNum]);
        mgWallNum++;
        dx = closest.x - prev.pos.x;
        dz = closest.z - prev.pos.z;
        depth = sphere.radius - HuSqrtf(dx * dx + dz * dz);
        if (side > 0) {
            sphere.pos.x = mgPlayerPrevPos.x;
            sphere.pos.y = mgPlayerPrevPos.y;
            sphere.pos.z = mgPlayerPrevPos.z;
            MgMtxPosMult(mgMapInvMtx, &sphere.pos);
            if (MgFaceSideGet(&sphere.pos, (Hu3DQuad *)(vtx - 1), points) < 0) {
                dir.x = sphere.pos.x - prev.pos.x;
                dir.y = sphere.pos.y - prev.pos.y;
                dir.z = sphere.pos.z - prev.pos.z;
                MapVecNormalize(&dir);
                if (MgFaceInsideCheck(&prev.pos, vtx - 1, points, &dir) == hit) {
                    depth = HuSqrtf(dx * dx + dz * dz) + sphere.radius;
                }
            } else {
                depth = 0.0f;
            }
        }
        if (0.0f <= depth) {
            MgMoveOfsAdd(-dx, -dz, depth);
        }
    }
    return hit;
}

void MgMapBoxBoundsHit(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2) {
    s32 i = mgWallNum;
    MgPlayerWork *data = arg0->data;
    f32 minX = data->unkA0 + arg1->radius;
    f32 minZ = data->unkA4 + arg1->radius;
    f32 maxX = data->unkA8.f - arg1->radius;
    f32 maxZ = data->unkAC - arg1->radius;
    f32 half;

    if (arg1->pos.x <= minX) {
        MgWallPosSet(data->unkA0, arg1->pos.y, arg1->pos.z);
        MgWallNorSet(1.0f, 0.0f, 0.0f);
        mgWallNum++;
    }
    if (maxX <= arg1->pos.x) {
        MgWallPosSet(data->unkA8.f, arg1->pos.y, arg1->pos.z);
        MgWallNorSet(-1.0f, 0.0f, 0.0f);
        mgWallNum++;
    }
    if (arg1->pos.z <= minZ) {
        MgWallPosSet(arg1->pos.x, arg1->pos.y, data->unkA4);
        MgWallNorSet(0.0f, 0.0f, 1.0f);
        mgWallNum++;
    }
    if (maxZ <= arg1->pos.z) {
        MgWallPosSet(arg1->pos.x, arg1->pos.y, data->unkAC);
        MgWallNorSet(0.0f, 0.0f, -1.0f);
        mgWallNum++;
    }
    if (i == mgWallNum) {
        half = arg1->radius * 0.5f;
        if (arg1->pos.x <= minX - half) {
            MgWallPosSet(data->unkA0, arg1->pos.y, arg1->pos.z);
            MgWallNorSet(1.0f, 0.0f, 0.0f);
            mgWallNum++;
        }
        if (maxX + half <= arg1->pos.x) {
            MgWallPosSet(data->unkA8.f, arg1->pos.y, arg1->pos.z);
            MgWallNorSet(-1.0f, 0.0f, 0.0f);
            mgWallNum++;
        }
        if (arg1->pos.z <= minZ - half) {
            MgWallPosSet(arg1->pos.x, arg1->pos.y, data->unkA4);
            MgWallNorSet(0.0f, 0.0f, 1.0f);
            mgWallNum++;
        }
        if (maxZ + half <= arg1->pos.z) {
            MgWallPosSet(arg1->pos.x, arg1->pos.y, data->unkAC);
            MgWallNorSet(0.0f, 0.0f, -1.0f);
            mgWallNum++;
        }
    }
    // minX/minZ are reused as the offset to each new contact point.
    while (i < mgWallNum) {
        minX = mgWallPosTbl[i].unk00 - arg1->pos.x;
        minZ = mgWallPosTbl[i].unk08 - arg1->pos.z;
        MgMoveOfsAdd(-minX, -minZ, arg1->radius - HuSqrtf(minX * minX + minZ * minZ));
        if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
            arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
            MgMtxPosMult(mgMapMtx, (Vec *)&mgWallPosTbl[i]);
        }
        i++;
    }
}

void MgMapCircleBoundsHit(omObjData *arg0, Hu3DSphere *arg1) {
    MgPlayerWork *data = arg0->data;
    f32 x = arg1->pos.x;
    f32 z = arg1->pos.z;
    f32 dist;
    Vec dir;

    dist = data->unk9C - (HuSqrtf(x * x + z * z) + arg1->radius);
    if (dist <= 0.0f) {
        MgMoveOfsAdd(x, z, dist);
        dir.x = x;
        dir.y = 0.0f;
        dir.z = z;
        MapVecNormalize(&dir);
        MgWallPosSet(arg1->pos.x * dir.x, arg1->pos.y, arg1->pos.z * dir.z);
        MgWallNorSet(-arg1->pos.x, 0.0f, -arg1->pos.z);
        mgWallNum++;
    }
}

void MgMapCylinderHit(omObjData *arg0, Hu3DSphere *arg1, f32 arg2) {
    MgPlayerWork *data = arg0->data;
    f32 x = arg1->pos.x;
    f32 z = arg1->pos.z;
    f32 dist;
    Vec dir;

    if (arg1->pos.y < arg2 + data->unk14 && data->unk14 - data->unk98 - arg2 < arg1->pos.y) {
        dist = HuSqrtf(x * x + z * z) - data->unk9C;
        if (0.0f <= dist && dist <= arg1->radius) {
            MgMoveOfsAdd(x, z, arg1->radius - dist);
            dir.x = x;
            dir.y = 0.0f;
            dir.z = z;
            MapVecNormalize(&dir);
            MgWallPosSet(-arg1->pos.x * dir.x, arg1->pos.y, -arg1->pos.z * dir.z);
            MgWallNorSet(arg1->pos.x, 0.0f, arg1->pos.z);
            mgWallNum++;
        }
    }
}

s32 MgMapBlockCornerHit(Hu3DSphere *arg0, MgPlayerWork *data) {
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
                MgWallPosSet(data->unkA0, y, data->unkA4);
                MgWallNorSet(x - data->unkA0, 0.0f, z - data->unkA4);
                mgWallNum++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                MgWallPosSet(data->unkA0, y, data->unkAC);
                MgWallNorSet(x - data->unkA0, 0.0f, z - data->unkAC);
                mgWallNum++;
                return 0;
            }
        }
    } else if (arg0->pos.x >= data->unkA8.f) {
        dx = data->unkA8.f - x;
        if (z <= data->unkA4) {
            dz = data->unkA4 - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                MgWallPosSet(data->unkA8.f, y, data->unkA4);
                MgWallNorSet(x - data->unkA8.f, 0.0f, z - data->unkA4);
                mgWallNum++;
                return 0;
            }
        } else if (data->unkAC <= z) {
            dz = data->unkAC - z;
            if (HuSqrtf(dx * dx + dz * dz) - arg0->radius < 0.0f) {
                MgWallPosSet(data->unkA8.f, y, data->unkAC);
                MgWallNorSet(x - data->unkA8.f, 0.0f, z - data->unkAC);
                mgWallNum++;
                return 0;
            }
        }
    }
    return 1;
}

void MgMapBlockHit(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2, f32 arg3) {
    s32 i = mgWallNum;
    MgPlayerWork *data = arg0->data;
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
            if (MgMapBlockCornerHit(arg1, data) == 1) {
                if (minX <= x && x <= data->unkA0) {
                    if (data->unkA4 <= arg1->pos.z && arg1->pos.z <= data->unkAC) {
                        edgeX = data->unkA0;
                        if (edgeX == arg1->pos.x) {
                            edgeX += 1.0f;
                        }
                        MgWallPosSet(edgeX, arg1->pos.y, arg1->pos.z);
                        MgWallNorSet(-1.0f, 0.0f, 0.0f);
                        mgWallNum++;
                    }
                } else if (x <= maxX && data->unkA8.f <= x) {
                    if (data->unkA4 <= arg1->pos.z && arg1->pos.z <= data->unkAC) {
                        edgeX = data->unkA8.f;
                        if (edgeX == arg1->pos.x) {
                            edgeX -= 1.0f;
                        }
                        MgWallPosSet(edgeX, arg1->pos.y, arg1->pos.z);
                        MgWallNorSet(1.0f, 0.0f, 0.0f);
                        mgWallNum++;
                    }
                } else if (minZ <= z && z <= data->unkA4) {
                    if (data->unkA0 <= arg1->pos.x && arg1->pos.x <= data->unkA8.f) {
                        edgeZ = data->unkA4;
                        if (edgeZ == arg1->pos.z) {
                            edgeZ += 1.0f;
                        }
                        MgWallPosSet(arg1->pos.x, arg1->pos.y, edgeZ);
                        MgWallNorSet(0.0f, 0.0f, -1.0f);
                        mgWallNum++;
                    }
                } else if (z <= maxZ && data->unkAC <= z) {
                    if (data->unkA0 <= arg1->pos.x && arg1->pos.x <= data->unkA8.f) {
                        edgeZ = data->unkAC;
                        if (edgeZ == arg1->pos.z) {
                            edgeZ -= 1.0f;
                        }
                        MgWallPosSet(arg1->pos.x, arg1->pos.y, edgeZ);
                        MgWallNorSet(0.0f, 0.0f, 1.0f);
                        mgWallNum++;
                    }
                }
            }
            for (; i < mgWallNum; i++) {
                if (arg0->trans.x != 0.0f || arg0->trans.y != 0.0f || arg0->trans.z != 0.0f || arg0->rot.x != 0.0f ||
                    arg0->rot.y != 0.0f || arg0->rot.z != 0.0f) {
                    MgMtxPosMult(mgMapMtx, (Vec *)&mgWallPosTbl[i]);
                }
                minX = mgWallPosTbl[i].unk00 - arg2->x;
                minZ = mgWallPosTbl[i].unk08 - arg2->z;
                MgMoveOfsAdd(minX, minZ, HuSqrtf(minX * minX + minZ * minZ) - arg1->radius);
            }
        }
    }
}

void MgPlayerWallBump(omObjData *obj, Vec *pos, f32 arg2) {
    MgPlayerWork *data;
    f32 speed;
    f32 dx, dy, dz;
    f32 limit;
    s32 i;

    if (mgWallNum == 0) {
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
    for (i = 0; i < mgWallNum; i++) {
        dx = mgWallPosTbl[i].unk00 - pos->x;
        dy = mgWallPosTbl[i].unk04 - pos->y;
        dz = mgWallPosTbl[i].unk08 - pos->z;
        HuSqrtf(dx * dx + dy * dy + dz * dz);
        if (MgDirDot(sindf(data->unk3C) * speed + mgMoveOfsX,
                                   cosdf(data->unk3C) * speed + mgMoveOfsZ, dx, dz) > 0.9f &&
            data->unk38 != 1000.0f && data->unk40 > mgPlayerSpeedRun) {
            limit = data->unk40;
            if (data->unk50 & 6) {
                limit *= 0.6f;
            }
            limit *= data->unk4C * data->unkB4 * 0.98f;
            if (HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ) <
                limit) {
                if (data->unk50 & 8) {
                    data->unk40 = -mgPlayerSpeedMax;
                } else {
                    data->unk40 = -mgPlayerSpeedMin;
                }
                MgPlayerMotSet(obj, 30);
                MgPlayerSePlay(data, 7);
                omVibrate(data->unk59, 5, 0, 5);
                return;
            }
        }
        if (arg2 != 0.0f) {
            data->unk40 = arg2;
            MgPlayerSePlay(data, 7);
            omVibrate(data->unk59, 2, 3, 10);
            return;
        }
    }
}

s8 MgPlayerWallCheck(omObjData *arg0, Hu3DSphere *arg1, f32 arg2) {
    MgPlayerWork *data = arg0->data;
    Hu3DSphere sphere;
    MgHitSphere local;
    omObjData *obj;
    MgMapWork *objData;
    s16 count;
    s16 i;

    sphere.pos.x = arg1->pos.x;
    sphere.pos.y = data->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z;
    sphere.radius = arg1->radius;
    mgWallMapNo = -1;
    mgWallNum = 0;
    count = 0;
    if (!(data->unk00[mgMapBaseNo] & 1)) {
        obj = mgMapObjTbl[mgMapBaseNo];
        objData = obj->data;
        if (objData->unk06 & 8) {
            sphere.pos.x += mgMoveOfsX;
            sphere.pos.y += mgMoveOfsZ;
            MgMapBoxBoundsHit(obj, &sphere, &sphere.pos);
        } else if (objData->unk06 & 0x10) {
            sphere.pos.x += mgMoveOfsX;
            sphere.pos.y += mgMoveOfsZ;
            MgMapBlockHit(obj, &sphere, &sphere.pos, data->unk34 / 2);
        } else if (objData->unk06 & 0x20) {
            sphere.pos.x += mgMoveOfsX;
            sphere.pos.y += mgMoveOfsZ;
            MgMapCircleBoundsHit(obj, &sphere);
        } else if (objData->unk06 & 0x40) {
            sphere.pos.x += mgMoveOfsX;
            sphere.pos.y += mgMoveOfsZ;
            MgMapCylinderHit(obj, &sphere, data->unk34 / 2);
        } else if (!(objData->unk06 & 2)) {
            Hu3DQuadPoolCollect(mgMapObjTbl[mgMapBaseNo]->model[0], &mgQuadPool,
                               (s32 (*)(s32, s16 *, Hu3DPoint *, Vec *))MgWallFaceHit, &sphere.pos);
        }
        if (count != mgWallNum) {
            mgWallMapNo = objData->unk04;
        }
    }
    for (i = 0; i < mgMapObjNum; i++) {
        obj = mgMapObjTbl[i];
        objData = obj->data;
        if (i == mgMapBaseNo) {
            continue;
        }
        if (objData->unk06 & 2) {
            continue;
        }
        if (data->unk00[i] & 1) {
            continue;
        }
        count = mgWallNum;
        local.pos.x = local.prev.x = arg1->pos.x;
        local.pos.y = local.prev.y = data->unk34 / 2 + arg1->pos.y;
        local.pos.z = local.prev.z = arg1->pos.z;
        local.radius = sphere.radius = arg1->radius;
        MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &local.pos, obj);
        if (objData->unk06 & 4) {
            if (MgBoundsMarginCheck(Hu3DData[obj->model[0]].hmf->unk60, &local.pos, data->unk48) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 8) {
            local.pos.x += mgMoveOfsX;
            local.pos.y += mgMoveOfsZ;
            MgMapBoxBoundsHit(obj, (Hu3DSphere *)&local, &local.prev);
        } else if (objData->unk06 & 0x10) {
            local.pos.x += mgMoveOfsX;
            local.pos.y += mgMoveOfsZ;
            MgMapBlockHit(obj, (Hu3DSphere *)&local, &local.prev, data->unk34 / 2);
        } else if (objData->unk06 & 0x20) {
            local.pos.x += mgMoveOfsX;
            local.pos.y += mgMoveOfsZ;
            MgMapCircleBoundsHit(obj, (Hu3DSphere *)&local);
        } else if (objData->unk06 & 0x40) {
            local.pos.x += mgMoveOfsX;
            local.pos.y += mgMoveOfsZ;
            MgMapCylinderHit(obj, (Hu3DSphere *)&local, data->unk34 / 2);
        } else {
            Hu3DQuadPoolCollect(mgMapObjTbl[i]->model[0], &mgQuadPool,
                               (s32 (*)(s32, s16 *, Hu3DPoint *, Vec *))MgWallFaceHitEx, &local.pos);
        }
        if (count != mgWallNum) {
            mgWallMapNo = objData->unk04;
            MgMtxDirMult(mgMapMtx, &mgWallNorPrevTbl[mgWallNum]);
        }
    }
    sphere.pos.x = arg1->pos.x + mgMoveOfsX;
    sphere.pos.y = data->unk34 / 2 + arg1->pos.y;
    sphere.pos.z = arg1->pos.z + mgMoveOfsZ;
    sphere.radius = arg1->radius;
    if (MgMapBumpCheck(mgWallMapNo) == 1) {
        MgPlayerWallBump(arg0, &sphere.pos, arg2);
    }
    return mgWallMapNo;
}

void MgPlayerTiltSet(omObjData *obj, Vec *dir) {
    MgPlayerWork *data = obj->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    if (data->unk40 > mgPlayerSpeedRun) {
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

void MgPlayerPrevPosSet(omObjData *arg0) {
    mgPlayerPrevPos.x = arg0->trans.x;
    mgPlayerPrevPos.y = arg0->trans.y;
    mgPlayerPrevPos.z = arg0->trans.z;
}

void MgPlayerObjMain(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
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
    MgMapWork *otherData;
    s16 turn;
    u16 motion;
    s32 idle;

    x = arg0->trans.x;
    y = arg0->trans.y;
    z = arg0->trans.z;
    MgPlayerPrevPosSet(arg0);
    model = arg0->model[0];
    prevVy = data->unk38;
    mgMoveOfsX = mgMoveOfsZ = speed;
    mgHitSkipCnt = 0;
    mgWallMapNo = data->unk53[2] = -1;
    if (data->unk104[0] != NULL) {
        data->unk104[0](arg0);
    }
    if (MgFlowStatGet() == MG_STATE_PLAY && pad >= 0 && !(data->unk50 & 1)) {
        stickX = HuPadStkX[pad];
        stickY = HuPadStkY[pad];
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
        MgStickClamp(&stickX, &stickY);
        held = 0;
        if (!(data->unk50 & 6)) {
            pressed = HuPadBtnDown[pad];
            held = HuPadBtn[pad];
        } else {
            pressed = 0;
        }
    } else {
        stickY = 0;
        stickX = 0;
        held = 0;
        pressed = 0;
    }
    state = MgPlayerMotStatGet(arg0);
    if (state & 1) {
        idle = 1;
        if (data->unk38 == 1000.0f) {
            if (MgPlayerGroundMove(arg0, data->unk3C, x, y, z) != 65536.0f && (pressed & 0x8000)) {
                MgPlayerJumpStart(arg0, data);
                idle = 0;
            }
        } else {
            f32 vy = data->unk38;
            if (vy > mgPlayerFallMax) {
                vy = mgPlayerFallMax;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += mgPlayerGravity;
            if (MgPlayerMotSet(arg0, 6) == 1) {
                MgPlayerSePlay(data, 3);
                idle = 0;
            }
            y = MgPlayerAirMove(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = mgMapObjTbl[data->unk53[0]];
                if (((MgMapWork *)other->data)->unk03 == 2) {
                    MgPlayerSinkStart(arg0, x, other->trans.y, z);
                }
            }
        }
        if (idle == 1) {
            MgPlayerMotSet(arg0, 0);
        }
        data->unkC6 = 0;
    } else if (state & 0x100000) {
        data->unkC0--;
        if (data->unkC0 == 0) {
            MgPlayerMotSet(arg0, 0x13);
        }
        if (data->unkC0 - 52 < 0) {
            data->unk40 = mgPlayerSpeedZero;
            arg0->rot.y = 0.0f;
        } else {
            arg0->rot.y = HuAngleWrap(data->unkC0 * 45.0f);
            if (data->unk40 < mgPlayerSpeedZero) {
                data->unk40 += mgPlayerFriction * 0.2f;
                if (mgPlayerSpeedZero <= data->unk40) {
                    data->unk40 = mgPlayerSpeedZero;
                }
            } else if (mgPlayerSpeedZero <= data->unk40) {
                data->unk40 += -mgPlayerFriction * 0.2f;
                if (data->unk40 <= mgPlayerSpeedZero) {
                    data->unk40 = mgPlayerSpeedZero;
                }
            }
        }
        newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
        }
    } else if (state & 0x18C18) {
        f32 vy;

        if (state & 0x10000) {
            if (pressed & 0x8000) {
                MgPlayerJumpStart(arg0, data);
            }
        } else if (data->unk40 == mgPlayerSpeedZero) {
            if (state & 0x400) {
                MgPlayerMotSet(arg0, 0x21);
            } else if (state & 0x10) {
                MgPlayerMotSet(arg0, 0x12);
            } else if (state & 0x800) {
                MgPlayerMotSet(arg0, 0x22);
            } else if (state & 8) {
                MgPlayerMotSet(arg0, 0x13);
            } else {
                MgPlayerMotSet(arg0, 0);
            }
        } else if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 += mgPlayerFriction * 2.0f;
            if (mgPlayerSpeedZero <= data->unk40) {
                data->unk40 = mgPlayerSpeedZero;
            }
        } else if (mgPlayerSpeedZero <= data->unk40) {
            data->unk40 += -mgPlayerFriction * 2.0f;
            if (data->unk40 <= mgPlayerSpeedZero) {
                data->unk40 = mgPlayerSpeedZero;
            }
        }
        vy = data->unk38;
        if (vy == 1000.0f) {
            if (state & 0x10) {
                if (data->unk40 > mgPlayerSpeedMax) {
                    data->unk3C += -(f32)stickX / mgPlayerTurnDiv;
                } else {
                    f32 rate = (data->unk40 <= mgPlayerSpeedMin) ? mgPlayerSpeedMin : data->unk40;

                    data->unk3C += -(stickX / mgPlayerTurnDiv) * (rate / mgPlayerSpeedMax);
                }
            }
            newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
            if (newY != 65536.0f) {
                y = newY;
            }
        } else {
            if (vy > mgPlayerFallMax) {
                vy = mgPlayerFallMax;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += mgPlayerGravity;
            y = MgPlayerAirMove(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = mgMapObjTbl[data->unk53[0]];
                if (((MgMapWork *)other->data)->unk03 == 2) {
                    MgPlayerSinkStart(arg0, x, other->trans.y, z);
                } else if (state & 0x10) {
                    MgPlayerMotSet(arg0, 0x12);
                } else if (state & 8) {
                    MgPlayerMotSet(arg0, 0x13);
                } else if (!(state & 0xC00)) {
                    MgPlayerMotSet(arg0, 0);
                }
            }
        }
        data->unkC6 = 0;
    } else if (state & 0x6000) {
        f32 time;

        MgPlayerStickAvgGet(arg0, stickX, stickY);
        time = Hu3DMotionShiftTimeGet(model);
        if (time == -1.0f) {
            time = Hu3DData[model].motTime;
        }
        if (state & 0x4000) {
            data->unk3C += 25.0f;
            if (time >= 14.0f) {
                MgPlayerMotSet(arg0, 1);
                data->unk40 = mgPlayerSpeedMin;
                MgPlayerSePlay(data, 1);
            }
        } else if (time >= 10.0f) {
            if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                if (data->unk40 < mgPlayerSpeedMin) {
                    if (MgDirDot(stickX, -stickY, sindf(data->unk3C), cosdf(data->unk3C)) < 0.0f) {
                        MgPlayerMotSet(arg0, 0x20);
                    }
                }
            }
            if (time >= 15.0f && data->unk40 < mgPlayerSpeedMin) {
                if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                    if (data->unk40 < mgPlayerSpeedMin) {
                        if (MgDirDot(stickX, -stickY, sindf(data->unk3C), cosdf(data->unk3C)) < 0.0f) {
                            MgPlayerMotSet(arg0, 0x20);
                        } else {
                            MgPlayerMotSet(arg0, 2);
                            data->unk40 = mgPlayerSpeedRun;
                            MgPlayerSePlay(data, 1);
                        }
                    }
                } else {
                    MgPlayerMotSet(arg0, 0);
                }
            }
        }
        if (data->unk53[0] >= 0) {
            accel = ((MgMapWork *)mgMapObjTbl[data->unk53[0]]->data)->unk08;
        } else {
            accel = mgPlayerFriction;
        }
        accel *= 2.0f;
        if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 += accel;
            if (mgPlayerSpeedZero <= data->unk40) {
                data->unk40 = mgPlayerSpeedZero;
            }
        } else if (mgPlayerSpeedZero <= data->unk40) {
            data->unk40 -= accel;
            if (data->unk40 <= mgPlayerSpeedZero) {
                data->unk40 = mgPlayerSpeedZero;
            }
        }
        newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
            if (pressed & 0x8000) {
                MgPlayerJumpStart(arg0, data);
            } else if (pressed & 0x4000) {
                MgPlayerActStart(arg0, data);
                MgPlayerStickReset(arg0);
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
                data->unk38 = -mgPlayerJumpPower * 0.2f;
            }
            if (abs(stickX) >= 9 || abs(stickY) >= 9) {
                mgMoveOfsX = stickX / mgPlayerAirStickDiv * data->unkB4;
                mgMoveOfsZ = -(f32)stickY / mgPlayerAirStickDiv * data->unkB4;
                dist = HuSqrtf(mgMoveOfsX * mgMoveOfsX + mgMoveOfsZ * mgMoveOfsZ);
                angle = atan2df(mgMoveOfsX, mgMoveOfsZ) + data->unk60;
                mgMoveOfsX = sindf(angle) * dist;
                mgMoveOfsZ = cosdf(angle) * dist;
                if (data->unk50 & 8) {
                    mgMoveOfsX *= 0.2f;
                    mgMoveOfsZ *= 0.2f;
                }
            }
            if (pressed & 0x4000) {
                MgPlayerAirAttack(arg0, data);
            }
            if ((pressed & 0x2000) && !(data->unk50 & 8)) {
                MgPlayerHipDrop(arg0, data);
            }
            if (vy > mgPlayerFallMax) {
                vy = mgPlayerFallMax;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            data->unk38 += mgPlayerGravity;
        } else {
            if (vy > mgPlayerFallMax) {
                vy = mgPlayerFallMax;
            }
            if (time > 26.0f) {
                newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
                data->unk38 += mgPlayerGravity * 2.0f;
            } else if (state & 0x100) {
                newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
                data->unk38 += mgPlayerGravity / 2.0f;
            } else {
                newY = y;
            }
            if (state & 0x100) {
                MgPlayerAirAttackUpdate(arg0, x, newY, z);
            }
        }
        y = MgPlayerAirMove(arg0, x, newY, z, y);
        if (data->unk38 == 1000.0f) {
            other = mgMapObjTbl[data->unk53[0]];
            otherData = other->data;
            if (otherData->unk03 == 2) {
                MgPlayerSinkStart(arg0, x, other->trans.y, z);
            } else if (state & 0x200) {
                if (!(data->unk50 & 0x80) && data->unkBE == 0) {
                    MgPlayerHipDropLand(arg0, data, otherData, x, y, z);
                } else {
                    MgPlayerHipDropEnd(arg0, data, otherData, x, y, z);
                }
            } else {
                MgPlayerLand(arg0, data, otherData, stickX, stickY);
            }
        }
        data->unkC6 = 0;
    } else if (state & 0xC0) {
        MgPlayerAttackUpdate(arg0, state, x, y, z);
        if (data->unk38 == 1000.0f) {
            if (data->unk40 < mgPlayerSpeedZero) {
                data->unk40 += mgPlayerFriction * 2.0f;
                if (mgPlayerSpeedZero < data->unk40) {
                    data->unk40 = mgPlayerSpeedZero;
                }
            } else if (mgPlayerSpeedZero < data->unk40) {
                data->unk40 += -mgPlayerFriction * 2.0f;
                if (data->unk40 < mgPlayerSpeedZero) {
                    data->unk40 = mgPlayerSpeedZero;
                }
            }
            newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
            if (newY != 65536.0f) {
                y = newY;
            }
        } else {
            f32 vy = data->unk38;
            f32 time;

            if (vy > mgPlayerFallMax) {
                vy = mgPlayerFallMax;
            }
            time = Hu3DMotionShiftTimeGet(model);
            if (time == -1.0f) {
                time = Hu3DData[model].motTime;
            }
            newY = y + vy * vy * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
            if (time > 30.0f) {
                data->unk38 += mgPlayerGravity * 2.0f;
            } else {
                data->unk38 += mgPlayerGravity / 2.0f;
            }
            y = MgPlayerAirMove(arg0, x, newY, z, y);
            if (data->unk38 == 1000.0f) {
                other = mgMapObjTbl[data->unk53[0]];
                if (((MgMapWork *)other->data)->unk03 == 2) {
                    MgPlayerSinkStart(arg0, x, other->trans.y, z);
                } else if (abs(stickX) < 8 && abs(stickY) < 8) {
                    data->unk40 = mgPlayerSpeedZero;
                    MgPlayerMotSet(arg0, 0x15);
                    MgPlayerSePlay(data, 4);
                } else {
                    MgPlayerMotSet(arg0, 1);
                    data->unk40 = mgPlayerSpeedWalk;
                    MgPlayerSePlay(data, 1);
                }
            }
        }
        data->unkC6 = 0;
    } else if (state & 6) {
        avg = MgPlayerStickAvgGet(arg0, stickX, stickY);
        avgX = avg >> 16;
        avgY = avg;
        speed = HuSqrtf(avgX * avgX + avgY * avgY) / mgPlayerStickDiv;
        if (data->unk53[0] >= 0) {
            MgMapWork *otherData = mgMapObjTbl[data->unk53[0]]->data;

            if (otherData->unk0C != 0.0f) {
                data->unk40 += speed / otherData->unk0C;
            } else {
                data->unk40 += speed / mgPlayerAccel;
            }
            if (stickX | stickY) {
                data->unk40 -= otherData->unk08;
            } else {
                data->unk40 += -otherData->unk08 * 3.0f;
            }
        } else {
            data->unk40 += speed / mgPlayerAccel;
            if (stickX | stickY) {
                data->unk40 -= mgPlayerFriction;
            } else {
                data->unk40 += -mgPlayerFriction * 3.0f;
            }
        }
        speed = MgPlayerSpeedSnap(speed);
        if (speed < data->unk40) {
            data->unk40 = speed;
        }
        if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 = mgPlayerSpeedZero;
        }
        if (abs(avgX) >= 9 || abs(avgY) >= 9) {
            data->unk3C = atan2df(avgX, -avgY) + data->unk60;
        }
        newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
            if (!(MgPlayerMotStatGet(arg0) & 0xC00)) {
                if (pressed & 0x8000) {
                    MgPlayerJumpStart(arg0, data);
                } else if (pressed & 0x4000) {
                    MgPlayerActStart(arg0, data);
                } else {
                    dx = stickX - avgX;
                    dz = stickY - avgY;
                    if (HuSqrtf(dx * dx + dz * dz) > 65.0f) {
                        if (fabs(data->unk40) >= mgPlayerSpeedRun) {
                            MgPlayerMotSet(arg0, 0x11);
                            data->unk40 = mgPlayerSpeedWalk;
                            MgPlayerSePlay(data, 2);
                            px = x + sindf(data->unk3C) * 70.0f;
                            MgPlayerEffSet(arg0, 4, px, y, z + cosdf(data->unk3C) * 70.0f, 0.0f,
                                                   data->unk3C + 180.0f);
                        }
                    } else if (HuSqrtf(avgX * avgX + avgY * avgY) > 43.0f && abs(stickX) < 8 && abs(stickY) < 8) {
                        if (fabs(data->unk40) >= mgPlayerSpeedRun) {
                            MgPlayerMotSet(arg0, 0x11);
                            data->unk40 = mgPlayerSpeedWalk;
                            MgPlayerSePlay(data, 2);
                            px = x + sindf(data->unk3C) * 70.0f;
                            MgPlayerEffSet(arg0, 4, px, y, z + cosdf(data->unk3C) * 70.0f, 0.0f,
                                                   data->unk3C + 180.0f);
                        }
                    } else if (data->unk40 == mgPlayerSpeedZero) {
                        data->unkC6 = 0;
                        MgPlayerMotSet(arg0, 0);
                        if (data->unkC4 > 0) {
                            if (data->unkC5 > 0) {
                                HuAudFXStop(data->unkC5);
                            }
                            data->unkC4 = -1;
                        }
                    } else if (mgPlayerSpeedRun < speed) {
                        f32 time;

                        motion = 2;
                        turn = MgStickRotGet(data->unk59, 12, stickX, stickY);
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
                        if (MgPlayerMotSet(arg0, motion) == 1) {
                            MgPlayerSeReq(data, 1);
                        } else {
                            time = Hu3DMotionShiftTimeGet(model);
                            if (time == -1.0f) {
                                time = Hu3DData[model].motTime;
                            }
                            if (time == 0.0f) {
                                MgPlayerSeReq(data, 1);
                            }
                        }
                        if (data->unkBC < 60) {
                            px = x - sindf(data->unk3C) * 20.0f;
                            MgPlayerEffSet(arg0, 3, px, y, z - cosdf(data->unk3C) * 20.0f, 0.0f, data->unk3C);
                        }
                        data->unkBC++;
                        if (data->unkBC > 200) {
                            data->unkBC = 200;
                        }
                        if (data->unk90 > mgPlayerSpeedWalk || data->unk98 > mgPlayerSpeedWalk) {
                            px = x - sindf(data->unk3C) * 20.0f;
                            MgPlayerEffSet(arg0, 3, px, y, z - cosdf(data->unk3C) * 20.0f, 0.0f, data->unk3C);
                        }
                    } else {
                        f32 time;

                        data->unkC6 = 0;
                        if (MgPlayerMotSet(arg0, 1) == 1) {
                            MgPlayerSeReq(data, 0);
                        } else {
                            time = Hu3DMotionShiftTimeGet(model);
                            if (time == -1.0f) {
                                time = Hu3DData[model].motTime;
                            }
                            if (time == 0.0f) {
                                MgPlayerSeReq(data, 0);
                            }
                        }
                        data->unkBC = 0;
                    }
                }
            }
        }
    } else if (state & 0x20000) {
        omObjData *other = mgMapObjTbl[data->unk53[0]];

        y -= 20.0f;
        if (y < other->trans.y - 75.0f) {
            y = other->trans.y - 75.0f;
        }
        if (data->unk40 > mgPlayerSpeedZero) {
            data->unk40 -= mgPlayerFriction;
            if (data->unk40 <= mgPlayerSpeedZero) {
                data->unk40 = mgPlayerSpeedZero;
            }
        } else if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 += mgPlayerFriction;
            if (mgPlayerSpeedZero <= data->unk40) {
                data->unk40 = mgPlayerSpeedZero;
            }
        }
        if (arg0->model[2] != 0) {
            Hu3DModelPosSet(arg0->model[2], x, other->trans.y - 64.0f, z);
            Hu3DModelScaleSet(arg0->model[2], 6.0f, 6.0f, 6.0f);
        }
    } else if (state & 0xC0000) {
        if (state & 0x40000) {
            MgPlayerPoundHit(arg0, x, y, z);
        } else {
            MgPlayerSwingHit(arg0, x, y, z);
        }
        if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 += mgPlayerFriction * 2.0f;
            if (mgPlayerSpeedZero < data->unk40) {
                data->unk40 = mgPlayerSpeedZero;
            }
        } else if (mgPlayerSpeedZero < data->unk40) {
            data->unk40 += -mgPlayerFriction * 2.0f;
            if (data->unk40 < mgPlayerSpeedZero) {
                data->unk40 = mgPlayerSpeedZero;
            }
        }
        newY = MgPlayerGroundMove(arg0, data->unk3C, x, y, z);
        if (newY != 65536.0f) {
            y = newY;
        }
    } else if (state & 0x1000) {
        data->unk40 = mgPlayerSpeedZero;
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
    x += sindf(data->unk3C) * speed + mgMoveOfsX;
    z += cosdf(data->unk3C) * speed + mgMoveOfsZ;
    func_80088910_main(Hu3DData[arg0->model[0]].mtx, 0.0f, data->unk3C, 0.0f);
    MgObjPosSet(arg0, x, y, z);
    if (data->unk104[1] != NULL) {
        data->unk104[1](arg0);
    }
    MgPlayerMotUpdate(arg0);
    MgPlayerScaleUpdate(arg0);
}

void MgMoveOfsAdd(f32 x, f32 z, f32 scale) {
    Vec dir;

    dir.x = x;
    dir.y = 0.0f;
    dir.z = z;
    MapVecNormalize(&dir);
    mgMoveOfsX += scale * dir.x;
    mgMoveOfsZ += scale * dir.z;
}

f32 MgPlayerSpeedSnap(f32 arg0) {
    if (arg0 < mgPlayerSpeedMin) {
        return mgPlayerSpeedMin;
    }
    if (arg0 < mgPlayerSpeedWalk) {
        return mgPlayerSpeedWalk;
    }
    if (arg0 < mgPlayerSpeedRun) {
        return mgPlayerSpeedRun;
    }
    return arg0;
}

void MgPlayerSinkStart(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = arg0->data;
    s16 temp;

    MgPlayerMotSet(arg0, 0x10);
    temp = data->unk21[2];
    Hu3DSprModelReset(temp);
    Hu3DSprModelAttrSet(temp, 4, 4);
    Hu3DModelPosSet(arg0->model[2], x, y, z);
    data->unk40 = mgPlayerSpeedZero;
    MgFieldStatLand();
}

void MgPlayerThrowRelease(omObjData *arg0) {
    MgPlayerWork *data = arg0->data;
    f32 time;

    time = Hu3DMotionShiftTimeGet(arg0->model[0]);
    if (time == -1.0f) {
        time = Hu3DData[arg0->model[0]].motTime;
    }
    if (time >= 28.0f && time <= 29.0f) {
        MgPlayerItemThrow(arg0, (data->unk40 + mgPlayerSpeedWalk) * data->unkCC);
    }
}

void MgPlayerPunchHit(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgPlayerWork *data = arg0->data;
    MgPlayerWork *otherData;
    MgItemWork *itemData;
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
        mgHitSkipCnt++;
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
    for (i = 0; i < mgPlayerObjNum; i++) {
        other = mgPlayerObjTbl[i];
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
        if (MgPlayerAttackCheck(arg0, other) != 1) {
            continue;
        }
        dx = other->trans.x - px;
        dy = other->trans.y - py;
        dz = other->trans.z - pz;
        if (HuSqrtf(dx * dx + dy * dy + dz * dz) < otherData->unk48 + 30.0f) {
            MgPlayerHit(arg0, other, dx, dz, i);
        }
    }
    if (!(data->unk50 & 0x17)) {
        for (i = 0; i < mgItemObjNum; i++) {
            other = mgItemObjTbl[i];
            itemData = other->data;
            if (!(itemData->unk50 & 0x20)) {
                continue;
            }
            if (itemData->unk50 & 0x10) {
                continue;
            }
            if (data->unkBE != 0) {
                mgHitSkipCnt++;
                continue;
            }
            dx = other->trans.x - px;
            dy = other->trans.y - py;
            dz = other->trans.z - pz;
            dist = HuSqrtf(dx * dx + dy * dy + dz * dz) - (itemData->unk48 + data->unk48);
            if (dist < 0.0f) {
                if (data->unkEC == NULL || data->unkEC(arg0, other) != 1) {
                    MgPlayerItemHold(arg0, other);
                }
            }
        }
    }
    sphere.pos.x = sindf(angle) * data->unk48 + arg0->trans.x;
    sphere.pos.y = py;
    sphere.pos.z = cosdf(angle) * data->unk48 + arg0->trans.z;
    sphere.radius = data->unk64;
    data->unk53[2] = MgPlayerWallCheck(arg0, &sphere, -mgPlayerSpeedMax);
    if (mgWallNum != 0 && MgMapBumpCheck(mgWallMapNo) == 1) {
        rot = atan2df(mgWallPosTbl[0].unk00 - arg0->trans.x, mgWallPosTbl[0].unk08 - arg0->trans.z);
        MgPlayerEffSet(arg0, 6, px, py, pz, 0.0f, rot + 180.0f);
    }
    mgWallNum = 0;
    mgMoveOfsX = mgMoveOfsZ = 0.0f;
}

void MgWallNorSet(f32 x, f32 y, f32 z) {
    mgWallNorTbl[mgWallNum].x = x;
    mgWallNorTbl[mgWallNum].y = y;
    mgWallNorTbl[mgWallNum].z = z;
    MapVecNormalize(&mgWallNorTbl[mgWallNum]);
}

void MgWallPosSet(f32 arg0, f32 arg1, f32 arg2) {
    mgWallPosTbl[mgWallNum].unk00 = arg0;
    mgWallPosTbl[mgWallNum].unk04 = arg1;
    mgWallPosTbl[mgWallNum].unk08 = arg2;
}

void MgDebugParamExec(omObjData *arg0, s32 arg1) {
    MgPlayerWork *data;
    s32 i;

    if (arg1 != 0) {
        return;
    }
    if (HuPadBtn[arg1] & R_TRIG) {
        CZoom -= 20.0f;
    }
    if (HuPadBtn[arg1] & L_TRIG) {
        CZoom += 20.0f;
    }
    if (HuPadBtn[arg1] & U_CBUTTONS) {
        CRot.x += 0.3f;
    }
    if (HuPadBtn[arg1] & D_CBUTTONS) {
        CRot.x -= 0.3f;
    }
    if (HuPadBtn[arg1] & R_CBUTTONS) {
        CRot.y += 1.0f;
    }
    if (HuPadBtn[arg1] & L_CBUTTONS) {
        CRot.y -= 1.0f;
    }
    if (HuPadBtnDown[arg1] & U_JPAD) {
        mgDebugMenuNo--;
    } else if (HuPadBtnDown[arg1] & D_JPAD) {
        mgDebugMenuNo++;
    }
    if (mgDebugMenuNo < 0) {
        mgDebugMenuNo = 0;
    }
    if (mgDebugMenuNo > 0) {
        mgDebugMenuNo = 0;
    }
    switch (mgDebugMenuNo) {
        case 0:
            if (HuPadBtnDown[arg1] & (L_JPAD | R_JPAD)) {
                if (mgDebugCamHomingF != 0) {
                    mgDebugCamHomingF = 0;
                } else {
                    mgDebugCamHomingF = 1;
                }
            }
            break;
        case 1:
            break;
        case 2:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerAccel += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerAccel -= 0.1f;
            }
            if (mgPlayerAccel > 50.0f) {
                mgPlayerAccel = 50.0f;
            }
            if (mgPlayerAccel < 1.0f) {
                mgPlayerAccel = 1.0f;
            }
            break;
        case 3:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerFriction += 0.001f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerFriction -= 0.001f;
            }
            if (mgPlayerFriction > 0.999f) {
                mgPlayerFriction = 0.999f;
            }
            if (mgPlayerFriction < 0.001f) {
                mgPlayerFriction = 0.001f;
            }
            break;
        case 4:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerJumpPower += 0.01f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerJumpPower -= 0.01f;
            }
            if (mgPlayerJumpPower > 2.0f) {
                mgPlayerJumpPower = 2.0f;
            }
            if (mgPlayerJumpPower < 0.7f) {
                mgPlayerJumpPower = 0.7f;
            }
            break;
        case 5:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerGravity += 0.001f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerGravity -= 0.001f;
            }
            if (mgPlayerGravity > 0.2f) {
                mgPlayerGravity = 0.2f;
            }
            if (mgPlayerGravity < 0.01f) {
                mgPlayerGravity = 0.01f;
            }
            break;
        case 6:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerAirStickDiv += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerAirStickDiv -= 0.1f;
            }
            if (mgPlayerAirStickDiv > 30.0f) {
                mgPlayerAirStickDiv = 30.0f;
            }
            if (mgPlayerAirStickDiv < 0.0f) {
                mgPlayerAirStickDiv = 0.0f;
            }
            break;
        case 7:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerTurnDiv += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerTurnDiv -= 0.1f;
            }
            if (mgPlayerTurnDiv > 100.0f) {
                mgPlayerTurnDiv = 100.0f;
            }
            if (mgPlayerTurnDiv < 20.0f) {
                mgPlayerTurnDiv = 20.0f;
            }
            break;
        case 8:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerSpeedMax += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerSpeedMax -= 0.1f;
            }
            if (mgPlayerSpeedMax > 30.0f) {
                mgPlayerSpeedMax = 30.0f;
            }
            if (mgPlayerSpeedMax < 10.0f) {
                mgPlayerSpeedMax = 10.0f;
            }
            mgPlayerSpeedMin = mgPlayerSpeedMax / 4.0f;
            mgPlayerSpeedWalk = mgPlayerSpeedMax / 2.0f;
            mgPlayerSpeedRun = mgPlayerSpeedMin * 3.0f;
            mgPlayerStickDiv = 60.0f / mgPlayerSpeedMax;
            break;
        case 9:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerRadius += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerRadius -= 0.1f;
            }
            if (mgPlayerRadius > 100.0f) {
                mgPlayerRadius = 100.0f;
            }
            if (mgPlayerRadius < 40.0f) {
                mgPlayerRadius = 40.0f;
            }
            for (i = 0; i < mgPlayerObjNum; i++) {
                data = mgPlayerObjTbl[i]->data;
                data->unk48 = mgPlayerRadius;
            }
            break;
        case 10:
            if (HuPadBtn[arg1] & R_JPAD) {
                mgPlayerPunchRadius += 0.1f;
            }
            if (HuPadBtn[arg1] & L_JPAD) {
                mgPlayerPunchRadius -= 0.1f;
            }
            if (mgPlayerPunchRadius > 100.0f) {
                mgPlayerPunchRadius = 100.0f;
            }
            if (mgPlayerPunchRadius < 10.0f) {
                mgPlayerPunchRadius = 40.0f;
            }
            for (i = 0; i < mgPlayerObjNum; i++) {
                data = mgPlayerObjTbl[i]->data;
                data->unk64 = mgPlayerPunchRadius;
            }
            break;
    }
    fontcolor = 15;
    sprintf(omDBGStrBuf, "*");
    print8(16, (mgDebugMenuNo + 2) * 8, omDBGStrBuf);
    sprintf(omDBGStrBuf, "CAMERA :[%s]", mgDebugCamHomingF ? "HOMING" : "LOCK");
    print8(24, 16, omDBGStrBuf);
    if (mgDebugCamHomingF) {
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
