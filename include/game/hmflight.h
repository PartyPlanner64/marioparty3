#ifndef _GAME_HMFLIGHT_H
#define _GAME_HMFLIGHT_H

#include "ultra64.h"

typedef struct {
    /* 0x00 */ u8 r;
    /* 0x01 */ u8 g;
    /* 0x02 */ u8 b;
    /* 0x03 */ u8 stat;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ s8 unk05;
    /* 0x06 */ s8 unk06;
} UnkLightData_unk02; // Size 7

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ UnkLightData_unk02 unk02[8];
    /* 0x3A */ char unk3A[6];
    /* 0x40 */ Light unk40[3][8][8];
} UnkLightData; // Size 0xC40

void HmfLightExec(s16);
void HmfLightMaxSet(s16);
void HmfLightStatSet(s16, u8, u8);
void HmfLightColorSet(s16, u8, u8, u8);
void HmfLightDirSet(s16, f32, f32, f32);
void func_80019968_main(s16);

#endif
