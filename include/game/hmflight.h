#ifndef _GAME_HMFLIGHT_H
#define _GAME_HMFLIGHT_H

#include "ultra64.h"
#include "game/hu3d.h"

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

void Hu3DLightExec(s16);
void Hu3DGLightMaxSet(s16);
void Hu3DGLightStatSet(s16, u8, u8);
void Hu3DGLightColorSet(s16, u8, u8, u8);
void Hu3DGLightDirSet(s16, f32, f32, f32);
void func_80019968_main(s16);

void Hu3DLighInit(void);
void Hu3DLightClose(void);
void Hu3DLightReset(void);
void func_80019668_main(HmfData_UnkD0 *arg0);
s16 func_80019828_main(s16 arg0, s16 arg1);

#endif
