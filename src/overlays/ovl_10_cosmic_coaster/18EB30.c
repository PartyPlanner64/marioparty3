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

// Track object placement entry. Lists are terminated by a 0xFFFF type, and
// each entry is spawned once a car comes within range of its z distance.
typedef struct CosmicCoasterSpawn { // 0x10 bytes
    u16 type;
    f32 x;
    f32 y;
    f32 z;
} CosmicCoasterSpawn;

extern CosmicCoasterSpawn D_8010BBD0_cosmic_coaster[];
extern s32 D_8010BEE0_cosmic_coaster[11];
extern s32 D_8010BF0C_cosmic_coaster[11];
extern CosmicCoasterSpawn D_8010C060_cosmic_coaster[];
extern u16 D_8010C390_cosmic_coaster[2];
extern u16 D_8010C394_cosmic_coaster[2];
extern s16 D_8010C398_cosmic_coaster[11];

void func_80109A38_cosmic_coaster(omObjData *object);
void func_80109BFC_cosmic_coaster(omObjData *object, s16 car, CosmicCoasterSpawn *spawn);
void func_8010ABE0_cosmic_coaster(void);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_80109BFC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010A244_cosmic_coaster);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010A528_cosmic_coaster);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010A838_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010ABE0_cosmic_coaster);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010B234_cosmic_coaster);

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

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010B644_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18EB30", func_8010B97C_cosmic_coaster);
