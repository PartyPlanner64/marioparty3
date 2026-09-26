#include "common.h"
#include "mallocblock.h"

// Per-object cloud motion state stored in omObjData.data (offset 0x5C). The
// angle swings up to a 40 degree cap, while the height settles from 400 down
// to a floor of 270 at the rate given by heightRate.
typedef struct CosmicCoasterCloudState { // 0x10 bytes
    f32 angle;
    f32 yOffset;
    f32 height;
    f32 heightRate;
} CosmicCoasterCloudState;

// Cloud slots kept in the object data of the two coaster cars. yOffset doubles
// as the slot state: it holds the 100000.0f sentinel while the slot is free,
// carried is the object riding the slot, and state is its live-assignment flag.
typedef struct CosmicCoasterCarData {
    u8 pad00[0x3C];
    f32 yOffset[2];        // 0x3C
    omObjData *carried[2]; // 0x44
    s16 state[2];          // 0x4C
} CosmicCoasterCarData;

extern s32 D_8010C050_cosmic_coaster;
extern s32 D_8010C054_cosmic_coaster;
extern s32 D_8010BB8C_cosmic_coaster;
extern s16 D_8010C3BC_cosmic_coaster;
extern omObjData *D_8010C3B0_cosmic_coaster[2];

void func_80105DAC_cosmic_coaster(omObjData *arg0);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801059A0_cosmic_coaster);

void func_80105D80_cosmic_coaster(omObjData *arg0) {
    D_8010C054_cosmic_coaster = 0;
    D_8010C050_cosmic_coaster = 0;
    D_8010C3BC_cosmic_coaster = -1;
    arg0->func = func_80105DAC_cosmic_coaster;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80105DAC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80105FEC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801063CC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106530_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106720_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010673C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106758_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80106D10_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80107888_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010803C_cosmic_coaster);

// Counts down a short zoom-out animation for the active camera. Once the
// countdown reaches zero the object flags itself with work[0] = 1 so its
// parent knows to delete it.
void func_801080C8_cosmic_coaster(omObjData *arg0) {
    if (D_8010BB8C_cosmic_coaster != 0) {
        CZoomM[D_8010C3BC_cosmic_coaster] -= 30.0f;
        D_8010BB8C_cosmic_coaster--;
    } else {
        arg0->work[0] = 1;
    }
}

void func_80108124_cosmic_coaster(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010812C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801083D0_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010869C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80108C9C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801090C0_cosmic_coaster);

// Marks the first unused of the 6 coaster cars as in use, returning its index, or -1 if all are in use.
// The in use flags are the s16 values at offset 0x1C of the car data block.
s32 func_8010923C_cosmic_coaster(u16 *cars) {
    s16 i;

    for (i = 0; i < 6; i++) {
        if (cars[i + 0xE] == 0) {
            cars[i + 0xE] = 1;
            return i;
        }
    }

    return -1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109290_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_801096A8_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109900_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010991C_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109A38_cosmic_coaster);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", D_8010BFE4_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_80109BFC_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A244_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A434_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A528_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A744_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010A838_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010ABE0_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010AF04_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B04C_cosmic_coaster);

void func_8010B1DC_cosmic_coaster(omObjData *arg0) {
    CosmicCoasterCloudState *state = arg0->data = HuMemAllocTag(sizeof(CosmicCoasterCloudState), 0x7918);

    state->angle = 0.0f;
    state->yOffset = -5.0f;
    state->height = 400.0f;
    state->heightRate = -5.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B234_cosmic_coaster);

// Marks both cloud slots of both coaster cars as unused: the carried object is
// dropped and the slot goes back to the 100000.0f sentinel.
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
            car->yOffset[j] = 100000.0f;
            car->state[j] = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B644_cosmic_coaster);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_10_cosmic_coaster/18ABD0", func_8010B97C_cosmic_coaster);
