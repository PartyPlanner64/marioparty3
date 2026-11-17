#include "common.h"
#include "game/overlays/minigame.h"
#include "game/hmfcoll.h"
#include "game/hu3d.h"
#include "math.h"
#include "gcc/memory.h"
#include "game/hmfspr.h"
#include "game/mallocblock.h"
#include "game/util.h"

f32 mgItemFallMax = 1.0f;
f32 mgItemSpeedMax = 20.0f;
f32 mgItemTiltStep = 4.0f;
f32 mgItemGravity = 0.06f;

extern f32 mgPlayerFriction;
extern f32 mgPlayerSpeedMax;
extern f32 mgPlayerSpeedZero;
extern Vec mgItemPrevPos;
extern Vec mgWallNorTbl[];
extern u8 mgShadowAltF;

void MgItemObjMain(omObjData *arg0) {
    MgItemWork *data = arg0->data;
    s32 result = 0;
    f32 x, y, z;
    f32 angle;
    f32 floorY;

    if (data->unk50 & 0x20) {
        if (data->unk50 & 0x10) {
            return;
        }
    }
    mgMoveOfsX = mgMoveOfsZ = 0.0f;
    mgItemPrevPos.x = x = arg0->trans.x;
    mgItemPrevPos.y = y = arg0->trans.y;
    mgItemPrevPos.z = z = arg0->trans.z;
    angle = data->unk3C;
    if (data->unk84[0] != NULL && data->unk84[0](arg0) == 1) {
        return;
    }
    x += sindf(angle) * data->unk40;
    z += cosdf(angle) * data->unk40;
    MgItemFloorMoveAdd(data);
    if (data->unk38 != 1000.0f) {
        y += data->unk38 * data->unk38 * (data->unk38 >= 0.0f ? -35.0f : 35.0f);
        data->unk38 += mgItemGravity;
        if (data->unk38 > mgItemFallMax) {
            data->unk38 = mgItemFallMax;
        }
        floorY = MgItemCollide(arg0, x, y, z);
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
                MgItemSpeedDec(arg0);
            }
        }
    } else {
        y = MgItemCollide(arg0, x, y, z);
        MgItemSpeedDec(arg0);
        MgItemDirUpdate(arg0);
    }
    MgObjPosSet(arg0, x + mgMoveOfsX, y, z + mgMoveOfsZ);
    MgItemLifeUpdate(arg0);
    if (data->unk84[1] != NULL) {
        data->unk84[1](arg0);
    }
}

f32 MgItemCollide(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgItemWork *data = arg0->data;
    Hu3DSphere sphere;

    sphere.pos.x = x;
    sphere.pos.y = y;
    sphere.pos.z = z;
    sphere.radius = data->unk48;
    MgItemPlayerPush(arg0, x, y, z);
    MgItemWallCheck(arg0, &sphere);
    return MgItemFloorCheck(arg0, &sphere);
}

void MgItemFloorVelSet(omObjData *arg0, Vec *arg1) {
    MgItemWork *data = arg0->data;
    MgMapWork *other;

    if (data->unk53 >= 0 && data->unk38 == 1000.0f) {
        other = mgMapObjTbl[data->unk53]->data;
        data->unk5C = arg1->x * other->unk10;
        data->unk60 = arg1->y;
        data->unk64 = arg1->z * other->unk10;
        if (other->unk06 & 0x400) {
            MgItemTiltSet(arg0, arg1);
        }
    } else {
        data->unk5C = 0.0f;
        data->unk60 = 0.0f;
        data->unk64 = 0.0f;
    }
}

void MgItemTiltSet(omObjData *arg0, Vec *arg1) {
    MgItemWork *data = arg0->data;
    f32 rotX;
    f32 rotZ;
    f32 curX;
    f32 curZ;

    rotX = -(atan2df(arg1->y, arg1->z) - 90.0f);
    rotZ = atan2df(arg1->y, arg1->x) - 90.0f;
    curX = data->unk68;
    curZ = data->unk70;
    if (curX < rotX) {
        data->unk68 += mgItemTiltStep;
        if (rotX < data->unk68) {
            data->unk68 = rotX;
        }
    } else if (rotX < curX) {
        data->unk68 -= mgItemTiltStep;
        if (data->unk68 < rotX) {
            data->unk68 = rotX;
        }
    }
    if (curZ < rotZ) {
        data->unk70 += mgItemTiltStep;
        if (rotZ < data->unk70) {
            data->unk70 = rotZ;
        }
    } else if (rotZ < curZ) {
        data->unk70 -= mgItemTiltStep;
        if (data->unk70 < rotZ) {
            data->unk70 = rotZ;
        }
    }
    arg0->rot.x = data->unk68;
    arg0->rot.z = data->unk70;
}

void MgItemFloorMoveAdd(MgItemWork *arg0) {
    if (__builtin_fabs((f64)arg0->unk5C) > 1.0) {
        mgMoveOfsX += arg0->unk5C * arg0->unk58;
    }
    if (__builtin_fabs((f64)arg0->unk64) > 1.0) {
        mgMoveOfsZ += arg0->unk64 * arg0->unk58;
    }
}

void MgItemSpeedDec(omObjData *arg0) {
    MgItemWork *data = arg0->data;
    f32 temp;

    if (data->unk53 != -1) {
        if (data->unk84[2] != NULL && data->unk84[2](arg0) == 1) {
            return;
        }
        temp = ((MgMapWork *)mgMapObjTbl[data->unk53]->data)->unk08;
        if (temp != 0.0f) {
            data->unk40 -= temp;
        } else {
            data->unk40 -= mgPlayerFriction;
        }
        if (data->unk40 < mgPlayerSpeedZero) {
            data->unk40 = mgPlayerSpeedZero;
        }
        if (data->unk40 > mgItemSpeedMax) {
            data->unk40 = mgItemSpeedMax;
        }
    }
}

void MgItemDirUpdate(omObjData *arg0) {
    MgItemWork *data = arg0->data;
    Vec dir;

    if (data->unk84[3] != NULL && data->unk84[3](arg0) == 1) {
        return;
    }
    dir.x = -mgMoveOfsX;
    dir.y = 0.0f;
    dir.z = -mgMoveOfsZ;
    MapVecNormalize(&dir);
    dir.x = sindf(data->unk3C) - dir.x / 20.0f;
    dir.z = cosdf(data->unk3C) - dir.z / 20.0f;
    data->unk3C = atan2df(dir.x, dir.z);
}

f32 MgItemFloorCheck(omObjData *arg0, Hu3DSphere *arg1) {
    MgItemWork *data = arg0->data;
    f32 y = arg1->pos.y;
    Vec normal;
    f32 floorY;
    f32 newY;

    newY = MgItemFloorGet(arg0, arg1, &normal);
    floorY = newY;
    if (newY < y - data->unk34 || y + data->unk34 <= newY) {
        if (data->unk38 == 1000.0f) {
            data->unk38 = 0.0f;
        }
        newY = y;
    }
    MgItemShadowSet(arg0, arg1->pos.x, newY, arg1->pos.z, floorY, &normal);
    return newY;
}

void MgItemShadowSet(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal) {
    MgItemWork *data = arg0->data;
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
        MgShadowSlopeSet(arg0->model[1], normal);
    }
}

f32 MgItemFloorGet(omObjData *arg0, Hu3DSphere *arg1, Vec *normal) {
    MgItemWork *data;
    MgMapWork *objData;
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
    for (i = 0; i < mgMapObjNum; i++) {
        obj = mgMapObjTbl[i];
        objData = obj->data;
        if (data->unk00[i] & 1) {
            continue;
        }
        pos.x = x;
        pos.y = y;
        pos.z = z;
        MgMapPosLocalGet(mgMapMtx, mgMapInvMtx, &pos, obj);
        if (objData->unk06 & 4) {
            if (MgBoundsCheck(Hu3DData[obj->model[0]].hmf->unk60, &pos) == 0) {
                continue;
            }
        }
        if (objData->unk06 & 0x7A) {
            if (objData->unk06 & 0x50) {
                if (MgMapAreaCheck(&pos, objData) == 0) {
                    continue;
                }
            }
            hitY = objData->unk14;
            if (obj->trans.x != 0.0f || obj->trans.y != 0.0f || obj->trans.z != 0.0f || obj->rot.x != 0.0f ||
                obj->rot.y != 0.0f || obj->rot.z != 0.0f) {
                pos.y = hitY;
                MgMtxPosYMult(mgMapMtx, &pos);
                hitY = pos.y;
                if (floorY <= hitY && hitY < y + 150.0f) {
                    floorY = hitY;
                    data->unk53 = i;
                    if (normal != NULL) {
                        tmp.x = 0.0f;
                        tmp.y = 1.0f;
                        tmp.z = 0.0f;
                        MgMtxDirMult(mgMapMtx, &tmp);
                        normal->x = tmp.x;
                        normal->y = tmp.y;
                        normal->z = tmp.z;
                        MapVecNormalize(normal);
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
            points = (Hu3DPoint *)Hu3DData[model].hmf->unk50;
            Hu3DQuadPoolCollect(model, &mgQuadPool, MgFloorFaceFilter, &pos);
            for (quad = Hu3DQuadPoolNext(&mgQuadPool); quad != NULL;
                 quad = Hu3DQuadPoolNext(&mgQuadPool)) {
                transformed = FALSE;
                if (Hu3DData[model].pos.x != 0.0f || Hu3DData[model].pos.y != 0.0f ||
                    Hu3DData[model].pos.z != 0.0f || Hu3DData[model].rot.x != 0.0f ||
                    Hu3DData[model].rot.y != 0.0f || Hu3DData[model].rot.z != 0.0f) {
                    tmp.x = x;
                    tmp.y = y + 10.0f;
                    tmp.z = z;
                    MgMtxPosMult(mgMapInvMtx, &tmp);
                    dir.x = tmp.x - pos.x;
                    dir.y = tmp.y - pos.y;
                    dir.z = tmp.z - pos.z;
                    MapVecNormalize(&dir);
                    MgFaceRayCross(pos.x, pos.y, pos.z, points, quad, &dir, &pos);
                    MgMtxPosYMult(mgMapMtx, &pos);
                    hitY = pos.y;
                    transformed = TRUE;
                } else {
                    hitY = MapCalcPoint(pos.x, pos.y, pos.z, points, quad);
                }
                if (floorY <= hitY && hitY < y + 150.0f) {
                    floorY = hitY;
                    data->unk53 = i;
                    if (normal != NULL) {
                        MapTriNormalGet(&points[quad->vtx[1]], &points[quad->vtx[2]], &points[quad->vtx[3]],
                                           normal);
                        if (transformed == TRUE) {
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
    MgItemFloorVelSet(arg0, normal);
    return floorY;
}

void MgItemPlayerPush(omObjData *arg0, f32 x, f32 y, f32 z) {
    MgItemWork *data = arg0->data;
    MgItemWork *otherData;
    omObjData *other;
    f32 dx;
    f32 dz;
    f32 dist;
    s32 i;

    if ((data->unk52 & 7) != 0) {
        return;
    }
    for (i = 0; i < mgPlayerObjNum; i++) {
        other = mgPlayerObjTbl[i];
        otherData = other->data;
        dx = other->trans.x - (x + mgMoveOfsX);
        dz = other->trans.z - (z + mgMoveOfsZ);
        dist = HuSqrtf(dx * dx + dz * dz) - (data->unk48 + otherData->unk48);
        // The do-while(0) raises the loop depth weighting of the 0.0f/1000.0f
        // constant uses, needed to match float register allocation.
        do {
            if (dist < 0.0f && data->unk38 == 1000.0f && otherData->unk38 == 1000.0f) {
                MgMoveOfsAdd(dx, dz, dist);
            }
        } while (0);
    }
}

void MgItemWallCheck(omObjData *arg0, Hu3DSphere *arg1) {
    MgItemWork *data = arg0->data;
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
    mgWallNum = 0;
    for (i = 0; i < mgMapObjNum; i++) {
        obj = mgMapObjTbl[i];
        objData = obj->data;
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
            MgMtxDirMult(mgMapMtx, &mgWallNorTbl[count]);
        }
    }
    MgItemWallReflect(arg0);
}

void MgItemWallReflect(omObjData *arg0) {
    MgItemWork *data;
    Vec wall;
    Vec dir;
    Vec reflect;
    f32 dot;

    if (mgWallNum == 0) {
        return;
    }
    data = arg0->data;
    if (data->unk84[5] != NULL && data->unk84[5](arg0) == 1) {
        return;
    }
    wall.x = mgWallNorTbl[0].x;
    wall.y = dir.y = 0.0f;
    wall.z = mgWallNorTbl[0].z;
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

void MgItemLifeUpdate(omObjData *arg0) {
    MgItemWork *data = arg0->data;
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
                    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                    break;
                case 2:
                    Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
                    break;
            }
            if (data->unk7C <= data->unk78) {
                data->unk54 = 0;
                Hu3DModelAttrSet(arg0->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(arg0->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
            }
        }
    }
}

void MgItemCoinGet(omObjData *arg0, omObjData *arg1) {
    MgItemWork *data = arg1->data;
    MgPlayerWork *playerData = arg0->data;
    u8 sprite;
    u8 model;

    if (data->unk84[8] != NULL && data->unk84[8](arg0) == 1) {
        return;
    }
    sprite = data->unk21[3];
    model = arg1->model[3];
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    Hu3DSprModelFrameSet(sprite, 0);
    Hu3DSprModelAttrSet(sprite, 4, 4);
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
    Hu3DModelAttrSet(arg1->model[0], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(arg1->model[1], HU3D_ATTR_DISPOFF, HU3D_ATTR_DISPOFF);
}

void MgItemInit(omObjData *arg0, s32 arg1) {
    MgItemWork *data;
    s32 shadowFile = 0x299;
    s32 i;

    arg0->data = HuMemAllocTag(sizeof(MgItemWork), TAG_OVERLAY);
    memset(arg0->data, 0, sizeof(MgItemWork));
    data = arg0->data;
    data->unkA8 = HuMemAllocTag(4, TAG_OVERLAY);
    // Empty loop needed to match; keeps shadowFile | 0x400 from being
    // constant-folded.
    for (i = 0; i < 0; i++) {
    }
    if (arg1 == 3) {
        MgObjSprMdlCreate(arg0, 10, 0x689, 8);
        MgObjSprCreate(arg0, 3, 12, shadowFile | 0x400, 8);
        Hu3DSprModelTPLvlSet(data->unk21[3], 240);
        Hu3DSprModelColorSet(data->unk21[3], 255, 255, 134);
    }
    if (mgShadowAltF == 0) {
        arg0->model[1] = Hu3DModelRead3(0, shadowFile);
    } else {
        arg0->model[1] = Hu3DModelRead3(9, shadowFile);
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
    MgObjScaleSet(arg0, 2.0f, 2.0f, 2.0f);
    for (i = 0; i < 9; i++) {
        data->unk84[i] = NULL;
    }
}

void MgItemRelease(omObjData *arg0, omObjData *arg1) {
    MgItemWork *data1 = arg1->data;
    MgItemWork *data0 = arg0->data;

    if (data1->unk84[6] != NULL && data1->unk84[6](arg0) == 1) {
        return;
    }
    data1->unk38 = -mgPlayerJumpPower * 0.6f;
    data1->unk3C = data0->unk3C;
    data1->unk40 = data0->unk40;
    if (data1->unk40 < mgPlayerSpeedMax) {
        data1->unk40 = mgPlayerSpeedMax;
    }
    data1->unk80 = NULL;
    arg1->trans.x = arg0->trans.x;
    arg1->trans.y = data0->unk34 + data1->unk48 + arg0->trans.y;
    arg1->trans.z = arg0->trans.z;
}

void MgItemHookSet(MgItemWork *arg0, s32 arg1, s32 (*arg2)(omObjData *)) {
    if (arg1 < 9) {
        arg0->unk84[arg1] = arg2;
    }
}
