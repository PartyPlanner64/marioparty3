#include "common.h"
#include "game/mallocblock.h"
#include "cosmic_coaster.h"

// Per-object cloud motion state stored in omObjData.data (offset 0x5C). The
// angle swings up to a 40 degree cap, while the height settles from 400 down
// to a floor of 270 at the rate given by heightRate.
typedef struct CosmicCoasterCloudState { // 0x10 bytes
    f32 angle;
    f32 yOffset;
    f32 height;
    f32 heightRate;
} CosmicCoasterCloudState;

extern CosmicCoasterSpawn D_8010C060_cosmic_coaster[51];
extern u16 D_8010C390_cosmic_coaster[2];
extern u16 D_8010C394_cosmic_coaster[2];
extern s16 D_8010C398_cosmic_coaster[11];

void func_80109A38_cosmic_coaster(omObjData *object);
void func_80109BFC_cosmic_coaster(omObjData *object, s16 car, CosmicCoasterSpawn *spawn);
void func_8010ABE0_cosmic_coaster(void);
void func_8010A434_cosmic_coaster(omObjData *object);
void func_8010A744_cosmic_coaster(omObjData *object);
void func_8010B5C4_cosmic_coaster(omObjData *arg0);
void func_8010A244_cosmic_coaster(omObjData *object);
void func_8010A528_cosmic_coaster(omObjData *object);
void func_8010A838_cosmic_coaster(omObjData *object);
void func_8010AF04_cosmic_coaster(omObjData *object);
void func_8010B04C_cosmic_coaster(omObjData *object);
void func_8010B1DC_cosmic_coaster(omObjData *arg0);
void func_8010B234_cosmic_coaster(omObjData *object);

CosmicCoasterSpawn D_8010BBD0_cosmic_coaster[] = {
    { 0, 0.0f, 10.0f, 43.0f },
    { 0, -160.0f, 10.0f, 59.0f },
    { 0, 0.0f, 10.0f, 75.0f },
    { 0, 160.0f, 10.0f, 91.0f },
    { 4, -160.0f, 270.0f, 91.0f },
    { 1, -80.0f, 10.0f, 107.0f },
    { 0, -160.0f, 10.0f, 123.0f },
    { 0, 160.0f, 10.0f, 123.0f },
    { 1, 80.0f, 10.0f, 139.0f },
    { 0, -160.0f, 10.0f, 155.0f },
    { 0, 160.0f, 10.0f, 171.0f },
    { 4, -160.0f, 270.0f, 179.0f },
    { 1, -80.0f, 10.0f, 187.0f },
    { 0, 0.0f, 10.0f, 203.0f },
    { 1, 80.0f, 10.0f, 219.0f },
    { 0, -160.0f, 10.0f, 235.0f },
    { 0, 0.0f, 10.0f, 251.0f },
    { 0, -160.0f, 10.0f, 267.0f },
    { 0, 160.0f, 10.0f, 267.0f },
    { 0, 0.0f, 10.0f, 283.0f },
    { 4, -160.0f, 270.0f, 291.0f },
    { 1, -80.0f, 10.0f, 299.0f },
    { 1, 80.0f, 10.0f, 315.0f },
    { 0, -160.0f, 10.0f, 331.0f },
    { 0, 0.0f, 10.0f, 347.0f },
    { 0, -160.0f, 10.0f, 363.0f },
    { 0, 160.0f, 10.0f, 363.0f },
    { 1, -80.0f, 10.0f, 379.0f },
    { 1, 80.0f, 10.0f, 395.0f },
    { 0, -160.0f, 10.0f, 411.0f },
    { 0, 0.0f, 10.0f, 427.0f },
    { 4, 160.0f, 270.0f, 435.0f },
    { 1, 80.0f, 10.0f, 443.0f },
    { 0, -160.0f, 10.0f, 459.0f },
    { 0, 160.0f, 10.0f, 459.0f },
    { 0, 0.0f, 10.0f, 475.0f },
    { 0, -160.0f, 10.0f, 491.0f },
    { 0, 160.0f, 10.0f, 491.0f },
    { 1, -80.0f, 10.0f, 507.0f },
    { 1, 80.0f, 10.0f, 523.0f },
    { 4, -160.0f, 270.0f, 530.0f },
    { 1, -80.0f, 10.0f, 539.0f },
    { 0, 160.0f, 10.0f, 555.0f },
    { 0, -160.0f, 10.0f, 571.0f },
    { 0, 0.0f, 10.0f, 587.0f },
    { 0, -160.0f, 10.0f, 603.0f },
    { 0, 160.0f, 10.0f, 603.0f },
    { 6, 0.0f, 0.0f, 630.0f },
    { 0xFFFF, 0.0f, 0.0f, 100000.0f },
};

s32 D_8010BEE0_cosmic_coaster[11] = {
    0x00310004, 0x00310005, 0x0031000B, 0x0031000C, 0x00210024, 0x00310007,
    0x00310008, 0x00310009, 0x0031000A, 0x00310006, 0x0031000D
};

s32 D_8010BF0C_cosmic_coaster[11] = { 0x6D9, 0x6D9, 0x6D9, 0x6D9, 0x6D9, 0x206D9, 0x206D9, 0x6D9, 0x6D9, 0x6D9, 0x6D9 };

// Per type object update.
omObjFunc D_8010BF38_cosmic_coaster[9] = {
    func_8010A244_cosmic_coaster, func_8010A528_cosmic_coaster, NULL, NULL,
    func_8010A838_cosmic_coaster, func_8010B04C_cosmic_coaster, func_8010B234_cosmic_coaster, NULL,
    NULL
};

// Per type object setup.
omObjFunc D_8010BF5C_cosmic_coaster[9] = { NULL, NULL, NULL, NULL, NULL, func_8010AF04_cosmic_coaster, func_8010B1DC_cosmic_coaster, NULL, NULL };

// Per type object priority.
s32 D_8010BF80_cosmic_coaster[9] = { 21, 21, 21, 21, 22, 21, 21, 21, 21 };

void func_80109900_cosmic_coaster(void) {
    omOvlReturnEx(1);
}

void func_8010991C_cosmic_coaster(omObjData *object) {
    s32 i;

    omMakeGroup(0, 55);
    omMakeGroup(1, 55);
    for (i = 0; i < 55; i++) {
        object->model[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        D_8010C390_cosmic_coaster[i] = 0;
        D_8010C394_cosmic_coaster[i] = 0;
    }
    for (i = 0; i < 11; i++) {
        D_8010C398_cosmic_coaster[i] = func_8000B108_main(D_8010BEE0_cosmic_coaster[i], D_8010BF0C_cosmic_coaster[i] | 4);
    }
    func_8010ABE0_cosmic_coaster();
    object->func = func_80109A38_cosmic_coaster;
}

// Spawns the track objects of both lists that each car has come within range of.
void func_80109A38_cosmic_coaster(omObjData *object) {
    CosmicCoasterSpawn *spawn;
    f32 dist;
    s32 i;

    for (i = 0; i < 2; i++) {
        dist = ((CosmicCoasterCarData *)D_8010C3B0_cosmic_coaster[i]->data)->progress + 9000.0f;
        for (spawn = &D_8010BBD0_cosmic_coaster[D_8010C390_cosmic_coaster[i]]; spawn->type != 0xFFFF; spawn++) {
            if (spawn->z * 100.0f <= dist) {
                func_80109BFC_cosmic_coaster(object, i, spawn);
                D_8010C390_cosmic_coaster[i]++;
            }
        }
        for (spawn = &D_8010C060_cosmic_coaster[D_8010C394_cosmic_coaster[i]]; spawn->type != 0xFFFF; spawn++) {
            if (spawn->z * 100.0f <= dist) {
                func_80109BFC_cosmic_coaster(object, i, spawn);
                D_8010C394_cosmic_coaster[i]++;
            }
        }
    }
}

// Spawns the track object described by spawn for the given car, linking its
// models into free slots of the track object manager.
void func_80109BFC_cosmic_coaster(omObjData *object, s16 carIdx, CosmicCoasterSpawn *spawn) {
    CosmicCoasterCarData *car;
    omObjData *newObj;
    s16 cam;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 55; i++) {
        if (object->model[i] == -1) {
            break;
        }
    }
    if (i == 55) {
        osSyncPrintf("obj over\n");
        return;
    }
    car = D_8010C3B0_cosmic_coaster[carIdx]->data;
    if (spawn->type != 1) {
        object->model[i] = Hu3DModelLink(D_8010C398_cosmic_coaster[spawn->type]);
    } else if (spawn->x < 0.0f) {
        object->model[i] = Hu3DModelLink(D_8010C398_cosmic_coaster[9]);
    } else {
        object->model[i] = Hu3DModelLink(D_8010C398_cosmic_coaster[1]);
    }
    cam = 2;
    if (carIdx == 0) {
        cam = 1;
    }
    if (spawn->type != 6) {
        newObj = omAddObj(D_8010BF80_cosmic_coaster[spawn->type], 1, 0, carIdx, D_8010BF38_cosmic_coaster[spawn->type]);
        omSetStat(newObj, 0x100);
        newObj->model[0] = object->model[i];
        newObj->work[0] = i;
        newObj->work[1] = spawn->type;
        newObj->work[2] = carIdx;
    } else {
        newObj = omAddObj(D_8010BF80_cosmic_coaster[spawn->type], 3, 0, carIdx, D_8010BF38_cosmic_coaster[spawn->type]);
        omSetStat(newObj, 0x100);
        newObj->model[0] = object->model[i];
        newObj->work[1] = spawn->type;
        newObj->work[2] = carIdx;
        newObj->work[3] = -1;
        for (j = 0; j < 55; j++) {
            if (object->model[j] == -1) {
                break;
            }
        }
        if (j != 55) {
            object->model[j] = Hu3DModelLink(D_8010C398_cosmic_coaster[7]);
            newObj->work[3] &= 0xFFFF;
            newObj->model[1] = object->model[j];
            newObj->work[3] |= j << 16;
        } else {
            osSyncPrintf("obj over\n");
        }
        for (k = 0; k < 55; k++) {
            if (object->model[k] == -1) {
                break;
            }
        }
        if (k != 55) {
            object->model[k] = Hu3DModelLink(D_8010C398_cosmic_coaster[8]);
            newObj->work[3] &= 0xFFFF0000;
            newObj->model[2] = object->model[k];
            newObj->work[3] |= k & 0xFFFF;
        } else {
            osSyncPrintf("obj over\n");
        }
        func_8001C258_main(object->model[j], 4, 0);
        Hu3DModelPosSet(object->model[j], spawn->x, spawn->y + 400.0f, car->progress - spawn->z * 100.0 - 1185.0);
        Hu3DModelPosSet(object->model[k], spawn->x, spawn->y + 400.0f, car->progress - spawn->z * 100.0 - 1185.0);
        Hu3DModelCameraSet(object->model[j], cam);
        Hu3DModelCameraSet(object->model[k], cam);
        Hu3DLLightCreate(object->model[j], 1);
        Hu3DLLightColorSet(object->model[j], 0, 0, 0);
        Hu3DLLightDirSet(object->model[j], 0.0f, -127.0f, 0.0f);
        Hu3DLLightCreate(object->model[k], 1);
        Hu3DLLightColorSet(object->model[k], 0, 0, 0);
        Hu3DLLightDirSet(object->model[k], 0.0f, -127.0f, 0.0f);
    }
    Hu3DLLightCreate(object->model[i], 1);
    Hu3DLLightColorSet(object->model[i], 0, 0, 0);
    Hu3DLLightDirSet(object->model[i], 0.0f, -127.0f, 0.0f);
    func_8001C258_main(object->model[i], 4, 0);
    func_8001C814_main(object->model[i], 2, 2);
    Hu3DModelCameraSet(object->model[i], cam);
    omSetTra(newObj, spawn->x, spawn->y, spawn->z * 100.0f);
    Hu3DModelPosSet(newObj->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    Hu3DModelRotSet(newObj->model[0], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(newObj->model[0], 1.0f, 1.0f, 1.0f);
    if (D_8010BF5C_cosmic_coaster[spawn->type] != NULL) {
        D_8010BF5C_cosmic_coaster[spawn->type](newObj);
    }
}

void func_8010A244_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    s16 slot;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    if (object->mode == 1) {
        func_8010B5C4_cosmic_coaster(object);
        Hu3DModelKill(object->model[0]);
        slot = object->work[0];
        object->model[0] = D_8010C3C4_cosmic_coaster->model[slot] = Hu3DModelLink(D_8010C398_cosmic_coaster[2]);
        if (object->work[2] == 0) {
            Hu3DModelCameraSet(object->model[0], 1);
        } else {
            Hu3DModelCameraSet(object->model[0], 2);
        }
        object->work[1] = 2;
        object->func = func_8010A434_cosmic_coaster;
        Hu3DLLightCreate(object->model[0], 1);
        Hu3DLLightColorSet(object->model[0], 0, 0, 0);
        Hu3DLLightDirSet(object->model[0], 0.0f, -127.0f, 0.0f);
        func_8001C258_main(object->model[0], 4, 0);
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    } else if (car->progress - object->trans.z >= 3300.0f) {
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

// Keeps a one-shot track object positioned relative to its car and removes it
// once its motion has finished playing.
void func_8010A434_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    if (D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 <= Hu3DData[object->model[0]].motTime) {
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

void func_8010A528_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    s16 slot;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    if (object->mode == 1) {
        func_8010B5C4_cosmic_coaster(object);
        Hu3DModelKill(object->model[0]);
        slot = object->work[0];
        object->model[0] = D_8010C3C4_cosmic_coaster->model[slot] =
            Hu3DModelLink(object->trans.x > 0.0f ? D_8010C398_cosmic_coaster[3] : D_8010C398_cosmic_coaster[10]);
        if (object->work[2] == 0) {
            Hu3DModelCameraSet(object->model[0], 1);
        } else {
            Hu3DModelCameraSet(object->model[0], 2);
        }
        object->work[1] = 2;
        object->func = func_8010A744_cosmic_coaster;
        Hu3DLLightCreate(object->model[0], 1);
        Hu3DLLightColorSet(object->model[0], 0, 0, 0);
        Hu3DLLightDirSet(object->model[0], 0.0f, -127.0f, 0.0f);
        func_8001C258_main(object->model[0], 4, 0);
        Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    } else if (car->progress - object->trans.z >= 3300.0f) {
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

void func_8010A744_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    if (D_800CCF58_main[Hu3DData[object->model[0]].motId].unk02 <= Hu3DData[object->model[0]].motTime) {
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

// Light source track object: lights every object of its car's group within
// 1600 units, brighter the closer it is.
void func_8010A838_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    omObjData **list;
    omObjData *other;
    f32 dist;
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    u8 r;
    u8 g;
    u8 b;
    s32 i;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    omSetSca(object, 2.5f, 2.5f, 2.5f);
    Hu3DModelScaleSet(object->model[0], 2.5f, 2.5f, 2.5f);
    Hu3DLLightDirSet(object->model[0], 69.0f, 69.0f, 69.0f);
    Hu3DLLightColorSet(object->model[0], 255, 255, 255);
    list = omGetGroupMemberList(object->work[2]);
    for (i = 0; i < 55; i++) {
        if (list[i] == NULL) {
            continue;
        }
        other = list[i];
        if (other->work[1] == 4) {
            continue;
        }
        dist = HuSqrtf((other->trans.x - object->trans.x) * (other->trans.x - object->trans.x) +
                       (other->trans.y - object->trans.y) * (other->trans.y - object->trans.y) +
                       (other->trans.z - object->trans.z) * (other->trans.z - object->trans.z));
        if (dist > 1600.0f) {
            continue;
        }
        if (COSMIC_COASTER_LIGHT_DIST(other) < dist) {
            continue;
        }
        COSMIC_COASTER_LIGHT_DIST(other) = dist;
        dirX = (object->trans.x - other->trans.x) / dist * 127.0f;
        dirY = (object->trans.y - other->trans.y) / dist * 127.0f;
        dirZ = (object->trans.z - other->trans.z) / dist * 127.0f;
        r = (1600.0f - dist) * (255.0f / 1600.0f);
        g = (1600.0f - dist) * (255.0f / 1600.0f);
        b = (1600.0f - dist) * (255.0f / 1600.0f);
        Hu3DGLightColorSet(other->model[0], r, g, b);
        Hu3DGLightDirSet(other->model[0], dirX, dirY, dirZ);
    }
    if (car->progress - object->trans.z >= 5900.0f || object->mode == 1) {
        func_8010B5C4_cosmic_coaster(object);
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

// Fills the second track object list with 50 randomly placed objects of type 5
// on a ring around the track, followed by the list terminator.
void func_8010ABE0_cosmic_coaster(void) {
    CosmicCoasterSpawn *spawn = D_8010C060_cosmic_coaster;
    f32 z = (u8)(rand8() % 15) + 17;
    f32 angle;
    f32 radius;
    f32 x;
    f32 y;
    s32 i;

    for (i = 0; i != 50; i++, spawn++) {
        spawn->type = 5;
        spawn->z = z;
        angle = (rand8() * rand8()) % 3600 / 10.0f;
        radius = (rand8() * rand8()) % 4500 / 10.0f + 500.0f;
        x = cosdf(angle) * radius;
        y = sindf(angle) * radius;
        spawn->x = x;
        if ((y > 0.0f && y < 800.0f && x > -300.0f && x < 300.0f) || (spawn->z > 625.0f && spawn->z < 685.0f)) {
            y = 650.0f;
        }
        spawn->y = y + 150.0f;
        z += (u8)(rand8() % 7) + 11.0f;
    }
    spawn->type = 0xFFFF;
}

// Picks a random per-frame spin of 0.5 to 3.9 degrees on each axis.
void func_8010AF04_cosmic_coaster(omObjData *object) {
    Vec *spin = object->data = HuMemAllocTag(sizeof(Vec), TAG_OVERLAY);

    spin->x = ((u8)(rand8() % 35) + 5) / 10.0f;
    spin->y = ((u8)(rand8() % 35) + 5) / 10.0f;
    spin->z = ((u8)(rand8() % 35) + 5) / 10.0f;
}

// Spins a track object relative to its car until the car is 3300 units past it.
void func_8010B04C_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    Vec *spin;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    spin = object->data;
    object->rot.x += spin->x;
    object->rot.y += spin->y;
    object->rot.z += spin->z;
    if (object->rot.x >= 360.0f) {
        object->rot.x -= 360.0f;
    }
    if (object->rot.y >= 360.0f) {
        object->rot.y -= 360.0f;
    }
    if (object->rot.z >= 360.0f) {
        object->rot.z -= 360.0f;
    }
    Hu3DModelRotSet(object->model[0], object->rot.x, object->rot.y, object->trans.z);
    if (car->progress - object->trans.z >= 3300.0f) {
        Hu3DModelKill(object->model[0]);
        D_8010C3C4_cosmic_coaster->model[object->work[0]] = -1;
        omDelObj(object);
    }
}

void func_8010B1DC_cosmic_coaster(omObjData *arg0) {
    CosmicCoasterCloudState *state = arg0->data = HuMemAllocTag(sizeof(CosmicCoasterCloudState), TAG_OVERLAY);

    state->angle = 0.0f;
    state->yOffset = -5.0f;
    state->height = 400.0f;
    state->heightRate = -5.0f;
}

void func_8010B234_cosmic_coaster(omObjData *object) {
    CosmicCoasterCarData *car = D_8010C3B0_cosmic_coaster[object->work[2]]->data;
    CosmicCoasterCloudState *state;
    omObjData *otherCar;
    s16 otherIdx;

    Hu3DModelPosSet(object->model[0], object->trans.x, object->trans.y, car->progress - object->trans.z);
    object->motion = NULL;
    Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + 400.0f, car->progress - object->trans.z - 1185.0f);
    Hu3DModelPosSet(object->model[2], object->trans.x, object->trans.y + 400.0f, car->progress - object->trans.z - 1185.0f);
    state = object->data;
    if (D_8010C3BC_cosmic_coaster != -1 && D_8010C3BC_cosmic_coaster == object->work[2]) {
        func_8001C258_main(object->model[1], 4, 4);
        func_8001C258_main(object->model[2], 4, 0);
        state->angle += 8.0f;
        if (state->angle >= 360.0f) {
            state->angle -= 360.0f;
        }
        Hu3DModelRotSet(object->model[2], 0.0f, 0.0f, sindf(state->angle) * 45.0f);
        Hu3DLLightColorSet(object->model[0], 255, 255, 255);
        Hu3DLLightDirSet(object->model[0], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[1], 255, 255, 255);
        Hu3DLLightDirSet(object->model[1], 69.0f, 69.0f, 69.0f);
        Hu3DLLightColorSet(object->model[2], 255, 255, 255);
        Hu3DLLightDirSet(object->model[2], 69.0f, 69.0f, 69.0f);
    }
    otherIdx = D_8010C3BC_cosmic_coaster ^ 1;
    otherCar = D_8010C3B0_cosmic_coaster[otherIdx];
    if (D_8010C3BC_cosmic_coaster != -1 && otherCar->work[0] != 0 && otherIdx == object->work[2]) {
        if (otherCar->work[1] != 0) {
            otherCar->work[1]--;
        } else {
            state->height += state->heightRate;
            state->heightRate *= 1.45f;
            state->angle += 8.0f;
            if (state->height <= 270.0f) {
                state->height = 270.0f;
            }
            if (state->angle > 40.0f) {
                state->angle = 40.0f;
            }
            Hu3DModelPosSet(object->model[1], object->trans.x, object->trans.y + state->height,
                            car->progress - object->trans.z - 1185.0f);
            Hu3DModelRotSet(object->model[1], 0.0f, 0.0f, state->angle);
        }
    }
}

// Clears the rider targets of both coaster cars: a target chosen for this
// object is dropped and every targetX goes back to the 100000.0f sentinel.
void func_8010B5C4_cosmic_coaster(omObjData *arg0) {
    CosmicCoasterCarData *car;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        car = D_8010C3B0_cosmic_coaster[i]->data;

        for (j = 0; j < 2; j++) {
            if (car->carried[j] == arg0) {
                car->carried[j] = NULL;
            }
            car->targetX[j] = 100000.0f;
            car->state[j] = 0;
        }
    }
}

// Finds, for each rider of a car, the first track object of type 0, 1 or 4 that
// overlaps the rider's lane between the ahead and behind distances. Returns the
// types that were found (0xFFFF if none), the second rider's in the upper half.
u32 func_8010B644_cosmic_coaster(omObjData **found, CosmicCoasterCarData *car, f32 ahead, f32 behind, u16 notify) {
    u16 hits[2];
    Vec objMin;
    Vec objMax;
    Vec laneMin[2];
    Vec laneMax[2];
    omObjData **list;
    omObjData *other;
    s32 i;
    s32 j;

    list = omGetGroupMemberList(car->group);
    laneMin[0].x = car->x[0] - 30.0f;
    laneMin[0].y = 225.0f;
    laneMin[0].z = ahead + 130.0f;
    laneMax[0].x = car->x[0] + 30.0f;
    laneMax[0].y = 125.0f;
    laneMax[0].z = behind - -100.0f + 30.0f;
    laneMin[1].x = car->x[1] - 30.0f;
    laneMin[1].y = 225.0f;
    laneMin[1].z = ahead + -130.0f;
    laneMax[1].x = car->x[1] + 30.0f;
    laneMax[1].y = 125.0f;
    laneMax[1].z = behind - 100.0f - 30.0f;
    hits[0] = hits[1] = 0xFFFF;
    for (i = 0; i < 55; i++) {
        if (list[i] == NULL) {
            continue;
        }
        other = list[i];
        if (other->work[1] != 0 && other->work[1] != 1 && other->work[1] != 4) {
            continue;
        }
        switch (other->work[1]) {
            case 0:
                objMin.x = other->trans.x - 70.0f;
                objMin.y = other->trans.y - 100.0f;
                objMin.z = other->trans.z;
                objMax.x = other->trans.x + 70.0f;
                objMax.y = other->trans.y + 100.0f;
                objMax.z = other->trans.z;
                break;
            case 1:
                objMin.x = other->trans.x - 150.0f;
                objMin.y = other->trans.y - 100.0f;
                objMin.z = other->trans.z;
                objMax.x = other->trans.x + 150.0f;
                objMax.y = other->trans.y + 100.0f;
                objMax.z = other->trans.z;
                break;
            case 4:
                objMin.x = other->trans.x - 70.0f;
                objMin.y = other->trans.y - 100.0f;
                objMin.z = other->trans.z;
                objMax.x = other->trans.x + 70.0f;
                objMax.y = other->trans.y + 100.0f;
                objMax.z = other->trans.z;
                break;
        }
        for (j = 0; j < 2; j++) {
            if (hits[j] == 0xFFFF && objMin.z <= laneMin[j].z && laneMax[j].z <= objMin.z &&
                laneMin[j].x < objMax.x && laneMax[j].x > objMin.x) {
                found[j] = other;
                hits[j] = other->work[1];
                if (notify == 1) {
                    func_80047E90_main(other, 1);
                }
            }
        }
    }
    return (hits[1] << 16) | hits[0];
}

s32 func_8010B97C_cosmic_coaster(omObjData *object, s32 slot, omObjData *target) {
    omObjData **list;
    omObjData *other;
    s32 mask = 0;
    s32 i;

    if (target == NULL) {
        return 0;
    }
    list = omGetGroupMemberList(((CosmicCoasterCarData *)object->data)->group);
    for (i = 0; i < 55; i++) {
        if (list[i] == NULL) {
            continue;
        }
        other = list[i];
        if (other->work[1] != 0 && other->work[1] != 1 && other->work[1] != 4) {
            continue;
        }
        if (other->trans.z != target->trans.z) {
            continue;
        }
        switch (other->work[1]) {
            case 0:
                if (other->trans.x < 0.0f) {
                    mask |= 0x20;
                }
                if (other->trans.x == 0.0f) {
                    mask |= 8;
                }
                if (other->trans.x > 0.0f) {
                    mask |= 2;
                }
                break;
            case 1:
                if (other->trans.x < 0.0f) {
                    mask |= 0x28;
                }
                if (other->trans.x > 0.0f) {
                    mask |= 0xA;
                }
                break;
            case 4:
                if (other->trans.x < 0.0f) {
                    mask |= 0x10;
                }
                if (other->trans.x == 0.0f) {
                    mask |= 4;
                }
                if (other->trans.x > 0.0f) {
                    mask |= 1;
                }
                break;
        }
    }
    return mask;
}
