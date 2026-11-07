#ifndef _OVL_MINIGAME_H
#define _OVL_MINIGAME_H

#include "ultra64.h"
#include "common_structs.h"
#include "humath.h"
#include "game/object.h"
#include "game/process.h"
#include "game/hu3d.h"
#include "game/hmfcoll.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x08 */ s32 unk08;
} func_800E1BA8_minigame_UnkE8_ObjData; // Size 0xC

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ char unk04[2];
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
} func_800E5638_minigame_UnkD8_ObjData; // Size 0x10

typedef struct {
    /* 0x000 */ char unk00[6];
    u16 unk06;
    /* 0x008 */ f32 unk08;
    /* 0x00C */ f32 unk0C;
    /* 0x010 */ f32 unk10;
    /* 0x014 */ f32 unk14;
    /* 0x018 */ char unk18[9];
    /* 0x021 */ u8 unk21[4];
    /* 0x025 */ char unk25[0xF];
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ f32 unk40;
    /* 0x044 */ f32 unk44;
    /* 0x048 */ f32 unk48;
    /* 0x04C */ f32 unk4C;
    /* 0x050 */ u16 unk50;
    /* 0x052 */ u8 unk52;
    /* 0x053 */ s8 unk53[4];
    /* 0x057 */ s8 unk57;
    /* 0x058 */ u8 unk58;
    /* 0x059 */ s8 unk59;
    /* 0x05A */ u8 unk5A;
    /* 0x05B */ u8 unk5B;
    /* 0x05C */ s32 unk5C;
    /* 0x060 */ f32 unk60;
    /* 0x064 */ f32 unk64;
    /* 0x068 */ f32 unk68;
    /* 0x06C */ f32 unk6C;
    /* 0x070 */ f32 unk70;
    /* 0x074 */ s32 unk74[6];
    /* 0x08C */ f32 unk8C;
    /* 0x090 */ f32 unk90;
    /* 0x094 */ f32 unk94;
    /* 0x098 */ f32 unk98;
    /* 0x09C */ f32 unk9C;
    /* 0x0A0 */ f32 unkA0;
    /* 0x0A4 */ f32 unkA4;
    /* 0x0A8 */ union {
        f32 f;
        u16 u16;
    } unkA8;
    /* 0x0AC */ f32 unkAC;
    /* 0x0B0 */ f32 unkB0;
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ f32 unkB8;
    /* 0x0BC */ u16 unkBC;
    /* 0x0BE */ u16 unkBE;
    /* 0x0C0 */ u16 unkC0;
    /* 0x0C2 */ u8 unkC2;
    /* 0x0C3 */ s8 unkC3;
    /* 0x0C4 */ s8 unkC4;
    /* 0x0C5 */ s8 unkC5;
    /* 0x0C6 */ s16 unkC6;
    /* 0x0C8 */ omObjData *unkC8; // Held item object
    /* 0x0CC */ f32 unkCC;
    /* 0x0D0 */ u16 unkD0;
    /* 0x0D2 */ u16 unkD2;
    /* 0x0D4 */ u16 unkD4;
    /* 0x0D6 */ u16 unkD6;
    /* 0x0D8 */ func_800E5638_minigame_UnkD8_ObjData unkD8;
    /* 0x0E8 */ func_800E1BA8_minigame_UnkE8_ObjData *unkE8;
    /* 0x0EC */ s32 (*unkEC)(omObjData *, omObjData *);
    /* 0x0F0 */ s16 unkF0;
    /* 0x0F2 */ s8 unkF2[0x12];
    /* 0x104 */ s32 (*unk104[21])();
    /* 0x158 */ void *unk158;
} func_800E1BA8_minigame_ObjData; // Size 0x15C

typedef struct A96F0_ObjData A96F0_ObjData;

// Per-object data (omObjData.data) of the item objects driven by A96F0.c.
struct A96F0_ObjData {
    /* 0x00 */ char unk00[0x21];
    /* 0x21 */ u8 unk21[4];
    /* 0x25 */ char unk25[0xF];
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ char unk4C[4];
    /* 0x50 */ u16 unk50;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ s8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ char unk55[3];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    /* 0x6C */ char unk6C[4];
    /* 0x70 */ f32 unk70;
    /* 0x74 */ f32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ omObjData *unk80; // Object holding this one
    /* 0x84 */ s32 (*unk84[9])(omObjData *);
    /* 0xA8 */ void *unkA8;
}; // Size 0xAC

// Common header of the per-object data of the minigame objects registered in
// D_800EC1C0_minigame.
typedef struct {
    /* 0x00 */ char unk00[3];
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ HuMtx4F unk18;
    /* 0x58 */ HuMtx4F unk58;
    /* 0x98 */ f32 unk98;
    /* 0x9C */ f32 unk9C;
    /* 0xA0 */ f32 unkA0;
    /* 0xA4 */ f32 unkA4;
    /* 0xA8 */ f32 unkA8;
    /* 0xAC */ f32 unkAC;
} D_800EC1C0_minigame_ObjData; // Size >= 0xB0

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
} D_800EBEB8_minigame_Entry; // Size 0xC

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ u8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ u8 unk03;
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ char unk07;
    /* 0x08 */ f32 unk08[4];
    /* 0x18 */ u8 unk18[4];
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
} D_80111B50_vine_with_me_Struct; // Size unknown (>= 0x26 and <= 0x28)

typedef struct {
    /* 0x00 */ Vec pos;
    /* 0x0C */ f32 radius;
    /* 0x10 */ Vec prev;
} func_800DBCF4_minigame_Arg; // Size 0x1C

// A96F0.c
void func_800D6B70_minigame(omObjData *arg0);
f32 func_800D6E14_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800D6E74_minigame(omObjData *arg0, Vec *arg1);
void func_800D6F20_minigame(omObjData *arg0, Vec *arg1);
void func_800D7084_minigame(A96F0_ObjData *arg0);
void func_800D710C_minigame(omObjData *arg0);
void func_800D71F0_minigame(omObjData *arg0);
f32 func_800D72B0_minigame(omObjData *arg0, Hu3DSphere *arg1);
void func_800D7388_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 floorY, Vec *normal);
f32 func_800D74AC_minigame(omObjData *arg0, Hu3DSphere *arg1, Vec *normal);
void func_800D7AA8_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800D7C14_minigame(omObjData *arg0, Hu3DSphere *arg1);
void func_800D7FA8_minigame(omObjData *arg0);
void func_800D80DC_minigame(omObjData *arg0);
void func_800D81C8_minigame(omObjData *arg0, omObjData *arg1);
void func_800D83D8_minigame(omObjData *arg0, s32 arg1);
void func_800D853C_minigame(omObjData *arg0, omObjData *arg1);
void func_800D861C_minigame(A96F0_ObjData *arg0, s32 arg1, s32 (*arg2)(omObjData *));

// AB1C0.c
f32 func_800D8640_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2);
f32 func_800D8778_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, f32 arg2, f32 arg3, Vec *arg4);
f32 func_800D8818_minigame(f32 x, f32 y, f32 z, Hu3DPoint *points, Hu3DQuad *quad, Vec *dir, Vec *out);
f32 func_800D89CC_minigame(omObjData *arg0, f32 x, f32 y, f32 z, Vec *normal);
f32 func_800D9028_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 prevY);
f32 func_800D972C_minigame(omObjData *arg0, f32 angle, f32 x, f32 y, f32 z);
f32 func_800D9F10_minigame(omObjData *arg0, f32 arg1);
s32 func_800D9F3C_minigame(Vec *pos, Hu3DQuad *quad, Hu3DPoint *points);
s32 func_800DA054_minigame(Hu3DSphere *sphere, Hu3DQuad *quad, Hu3DPoint *points);
f32 func_800DA204_minigame(f32 x, f32 y, f32 z, Hu3DPoint *p, Hu3DPoint *q, Vec *normal);
s32 func_800DA2E0_minigame(Vec *pos, s16 *face, Hu3DPoint *points, Vec *normal);
s32 func_800DA540_minigame(Vec *pos, s16 *face, Hu3DPoint *points);
s32 func_800DA768_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800DB628_minigame(omObjData *arg0);
s32 func_800DB704_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Vec *pos);
s32 func_800DB724_minigame(s32 count, s16 *vtx, Hu3DPoint *points, Hu3DSphere *arg3);
s32 func_800DBCF4_minigame(s32 count, s16 *vtx, Hu3DPoint *points, func_800DBCF4_minigame_Arg *arg3);
void func_800DC354_minigame(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2);
void func_800DC7D8_minigame(omObjData *arg0, Hu3DSphere *arg1);
void func_800DC8E4_minigame(omObjData *arg0, Hu3DSphere *arg1, f32 arg2);
s32 func_800DCA34_minigame(Hu3DSphere *arg0, func_800E1BA8_minigame_ObjData *data);
void func_800DCCB0_minigame(omObjData *arg0, Hu3DSphere *arg1, Vec *arg2, f32 arg3);
void func_800DD1F4_minigame(omObjData *obj, Vec *pos, f32 arg2);
s8 func_800DD530_minigame(omObjData *arg0, Hu3DSphere *arg1, f32 arg2);
void func_800DDB60_minigame(omObjData *obj, Vec *dir);
void func_800DDD70_minigame(omObjData *arg0);
void func_800DDD94_minigame(omObjData *arg0);
void func_800DFCDC_minigame(f32 x, f32 z, f32 scale);
f32 func_800DFD48_minigame(f32 arg0);
void func_800DFD9C_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800DFE44_minigame(omObjData *arg0);
void func_800DFF3C_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E0430_minigame(f32 x, f32 y, f32 z);
void func_800E048C_minigame(f32 arg0, f32 arg1, f32 arg2);
void func_800E04C8_minigame(omObjData *arg0, s32 arg1);

// B3CE0.c
void func_800E1160_minigame(omObjData *arg0, u16 arg1, u16 player, s32 arg3, s32 arg4, f32 arg5);
void func_800E123C_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, f32 arg4);
void func_800E12B0_minigame(omObjData *arg0, f32 arg1);
void func_800E12E0_minigame(omObjData *arg0, f32 arg1);
void func_800E12EC_minigame(omObjData *arg0, f32 arg1);
void func_800E12F8_minigame(omObjData *arg0, f32 arg1);
void func_800E1304_minigame(omObjData *arg0, f32 arg1);
void func_800E1310_minigame(omObjData *arg0, f32 arg1);
void func_800E131C_minigame(omObjData *arg0, f32 arg1);
void func_800E1328_minigame(omObjData *arg0, f32 arg1);
void func_800E1334_minigame(omObjData *arg0, f32 arg1);
void func_800E1340_minigame(omObjData *arg0, f32 arg1);
void func_800E134C_minigame(omObjData *arg0, f32 arg1);
void func_800E1358_minigame(omObjData *arg0, f32 arg1);
void func_800E1364_minigame(omObjData *arg0, f32 arg1);
void func_800E1370_minigame(omObjData *arg0, s32 arg1, f32 arg2);
void func_800E139C_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5);
void func_800E13CC_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void func_800E1404_minigame(omObjData *arg0, f32 arg1, f32 arg2);
void func_800E1420_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3);
void func_800E1440_minigame(omObjData *arg0);
void func_800E1454_minigame(omObjData *arg0);
void func_800E1468_minigame(omObjData *arg0);
void func_800E147C_minigame(omObjData *arg0);
void func_800E1490_minigame(s32 arg0);
void func_800E149C_minigame(omObjData *arg0, u8 arg1, s8 arg2);
void func_800E14B0_minigame(omObjData *arg0, s32 arg1, s32 arg2);
s32 func_800E1510_minigame(s8 arg0);
void func_800E1594_minigame(omObjData *arg0, s32 arg1, s32 arg2, s32 arg3);
void func_800E1610_minigame(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, char *arg4, s32 arg5);
void func_800E1718_minigame(omObjData *arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_800E17D4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E17E4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E17F4_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E1804_minigame(void);
void func_800E1810_minigame(void);
void func_800E1820_minigame(void);
void func_800E1830_minigame(void);
void func_800E1840_minigame(void);
s32 func_800E1854_minigame(s32 arg0);
void func_800E18B4_minigame(void);
void func_800E18D8_minigame(void);
void func_800E19E4_minigame(s32 arg0);
void func_800E19F0_minigame(s8 arg0);
void func_800E19FC_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 arg1);
void func_800E1A9C_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 arg1);
void func_800E1B3C_minigame(void);
void func_800E1BA8_minigame(omObjData *arg0, u32 arg1, s32 arg2, u16 arg3, s32 arg4, s32 arg5);
void func_800E210C_minigame(omObjData *arg0, s16 arg1, s16 arg2);
void func_800E21B8_minigame(omObjData *arg0, s32 arg1, s32 arg2);
s32 func_800E2250_minigame(omObjData *arg0, s16 arg1, s16 arg2);
void func_800E2308_minigame(s16 *arg0, s16 *arg1);
void func_800E23E0_minigame(omObjData *arg0);
s16 func_800E240C_minigame(s16 idx, s16 arg1, s8 x, s8 y);
void func_800E2780_minigame(omObjData *obj);
void func_800E28BC_minigame(HuMtx4F mtx, HuMtx4F result, Vec *pos, omObjData *obj);
void func_800E2B58_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2BD4_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2C68_minigame(HuMtx4F mtx, Vec *arg1);
void func_800E2CA4_minigame(omObjData *arg0, f32 arg1);
s32 func_800E2DA4_minigame(omObjData *arg0, omObjData *item);
void func_800E2E98_minigame(omObjData *arg0);
f32 func_800E2ED4_minigame(f32 x1, f32 z1, f32 x2, f32 z2);
s32 func_800E2F40_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos);
s32 func_800E2FD8_minigame(HmfModelData_Unk64_Unk60_Struct *obj, Vec *pos, f32 margin);
s32 func_800E30B8_minigame(Vec *pos, D_800EC1C0_minigame_ObjData *data);
void func_800E317C_minigame(omObjData *arg0, f32 x, f32 z);
void func_800E341C_minigame(func_800E1BA8_minigame_ObjData *arg0, f32 x, f32 z);
void func_800E34D8_minigame(omObjData *arg0, omObjData *arg1);
void func_800E3568_minigame(func_800E1BA8_minigame_ObjData *arg0, s32 index, s32 (*func)());
void func_800E3584_minigame(s16 model);
void func_800E3628_minigame(s16 model, Vec *normal);

// B63A0.c
void func_800E3820_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E38A4_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E3928_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E39CC_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2, s16 arg3, s16 arg4);
void func_800E3AB8_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E3B98_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_800E3CA0_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1, D_800EC1C0_minigame_ObjData *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_800E3D3C_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E3E24_minigame(omObjData *arg0, f32 arg1, f32 arg2, f32 arg3);
void func_800E3EA4_minigame(omObjData *arg0, func_800E1BA8_minigame_ObjData *arg1);
void func_800E3F44_minigame(omObjData *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4);
void func_800E3FD8_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
void func_800E4248_minigame(omObjData *arg0, f32 x, f32 y, f32 z);
s32 func_800E4510_minigame(omObjData *arg0, omObjData *arg1);
void func_800E454C_minigame(omObjData *arg0, omObjData *arg1, f32 x, f32 z, u16 arg4);
void func_800E47D8_minigame(omObjData *arg0, f32 arg1);
void func_800E4890_minigame(omObjData *arg0, f32 x, f32 y, f32 z, f32 groundY, Vec *normal);

// B7600.c
s32 func_800E4A80_minigame(omObjData *arg0);
u32 func_800E4A90_minigame(omObjData *arg0);
void func_800E4BA4_minigame(s32 arg0);
void func_800E4C2C_minigame(omObjData *arg0);
void func_800E4C88_minigame(omObjData *arg0, u8 arg1, f32 x, f32 y, f32 z, f32 rotX, f32 rotY);
void func_800E4D9C_minigame(omObjData *arg0);
void func_800E4E30_minigame(omObjData *arg0);
void func_800E5138_minigame(omObjData *arg0);
void func_800E561C_minigame(omObjData *arg0, u8 arg1);
void func_800E5638_minigame(func_800E5638_minigame_UnkD8_ObjData *arg0, u16 arg1, u16 arg2, u16 arg3, s16 arg4);
s32 func_800E5664_minigame(omObjData *arg0, u16 arg1);
s32 func_800E567C_minigame(func_800E1BA8_minigame_ObjData *arg0, u16 arg1);
s32 func_800E5690_minigame(omObjData *arg0, u16 arg1);
s32 func_800E5798_minigame(omObjData *arg0, s32 arg1);
s32 func_800E5848_minigame(omObjData *arg0, u16 arg1, u16 arg2);
void func_800E58B4_minigame(omObjData *arg0, s32 arg1, s32 arg2);
void func_800E58D4_minigame(omObjData *arg0, s32 arg1, s16 arg2, s16 arg3);
void func_800E58F8_minigame(omObjData *arg0, s32 arg1, s32 arg2);
void func_800E5978_minigame(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4);
void func_800E5A00_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4);
s16 func_800E5A98_minigame(omObjData *arg0, s32 arg1);
void func_800E5B08_minigame(omObjData *arg0, u16 arg1, s32 arg2, u16 arg3, u16 arg4, s16 arg5);
void func_800E5C18_minigame(omObjData *arg0, u16 arg1, s32 arg2, s32 arg3, u16 arg4, s16 arg5);

// B88C0.c
u32 func_800E5D40_minigame(u32 seed);
u32 func_800E5E14_minigame(void);
u32 func_800E5E3C_minigame(u32 max);

// B8A20.c
void func_800E5EA0_minigame(D_80111B50_vine_with_me_Struct *arg0);
void func_800E6248_minigame(s32 arg0, s32 arg1);
void func_800E625C_minigame(s32 arg0);
void func_800E6268_minigame(void);
void func_800E62A8_minigame(void);
s16 func_800E6300_minigame(s32 x, s32 y);
s16 func_800E64B8_minigame(s32 x, s32 y);
void func_800E6670_minigame(s16 index, s16 time);
void func_800E6968_minigame(s16 index, s16 time);
void func_800E6E4C_minigame(s16 arg0);
void func_800E6E5C_minigame(s16 arg0);
void func_800E6E6C_minigame(s16 arg0);
void func_800E6E7C_minigame(s8 arg0);
u8 func_800E6E8C_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F0C_minigame(u8 arg0);
void func_800E6F1C_minigame(void);
void func_800E6F34_minigame(s32 arg0);
// Unprototyped: Dorrie Dip passes an object argument that the other callers omit.
u8 func_800E6F40_minigame();

// BA4B0.c
void func_800E7930_minigame(s16 group, s16 member, s16 graphic, s16 prio, s16 x, s16 y);
void func_800E7F60_minigame(void);
Process *func_800E8EC4_minigame(u16 arg0, s16 arg1);
s32 func_800E8F78_minigame(Process *prc);
s16 func_800E8FE4_minigame(Process *prc, s16 value);
s16 func_800E8FF8_minigame(Process *prc);
void func_800E9004_minigame(Process *prc, s16 value);
s16 func_800E905C_minigame(s16 arg0);
void func_800E9170_minigame(void);
void func_800E989C_minigame(void);

// BC7A0.c
void func_800E9C20_minigame(s16 count, u16 length);
void func_800E9E28_minigame(void);
void func_800E9F40_minigame(s16 arg0, s16 x, s16 y, s16 arg3);
void func_800EA0FC_minigame(s16 arg0, f32 arg1, f32 arg2);
void func_800EA128_minigame(s16 arg0, f32 arg1);
void func_800EA178_minigame(s16 arg0, f32 arg1);
void func_800EA1E4_minigame(s16 arg0, s32 arg1);
void func_800EA2A8_minigame(s16 arg0);
void func_800EA444_minigame(s16 arg0);
void func_800EA518_minigame(void);

// BD210.c
void func_800EA690_minigame(void);
omObjData *func_800EA6C4_minigame(s16 prio, s16 arg1, s16 arg2, s16 arg3, s16 arg4);
void func_800EA7D0_minigame(omObjData *obj, f32 x, f32 y, f32 z);
void func_800EA7E0_minigame(omObjData *obj, f32 x, f32 y, f32 z);
void func_800EA7F0_minigame(omObjData *obj, f32 arg1, f32 arg2, f32 arg3);
void func_800EA8F0_minigame(omObjData *obj, f32 value);
void func_800EA8FC_minigame(omObjData *obj, f32 x, f32 y, f32 z);
void func_800EA910_minigame(omObjData *obj, s32 value);
s32 func_800EA91C_minigame(omObjData *obj);
void func_800EA928_minigame(omObjData *obj, u16 arg1);
void func_800EAA58_minigame(omObjData *obj);
void func_800EAE14_minigame(omObjData *arg0);
s32 func_800EAE7C_minigame(omObjData *obj);
void func_800EB3CC_minigame(omObjData *obj);
void func_800EB5E4_minigame(omObjData *obj);

extern f32 D_800EB720_minigame;
extern f32 D_800EB72C_minigame;
extern u8 D_800EB735_minigame;
extern s16 D_800EB736_minigame;
extern f32 D_800EB73C_minigame;
extern f32 D_800EB744_minigame;
extern f32 D_800EB748_minigame;
extern f32 D_800EB774_minigame;
extern f32 D_800EB77C_minigame;
extern u16 D_800EB910_minigame;
extern u16 D_800EB912_minigame;
extern u16 D_800EB914_minigame;
extern u16 D_800EB916_minigame;
extern u16 D_800EB918_minigame;
extern s16 D_800EB930_minigame;
extern s16 D_800EB932_minigame;
extern s16 D_800EB934_minigame;
extern D_80111B50_vine_with_me_Struct *D_800EBDE0_minigame;
extern s32 D_800EBE24_minigame;
extern u16 D_800EBE28_minigame;
extern f32 D_800EBE2C_minigame;
extern HuMtx4F D_800EBE30_minigame;
extern Hu3DQuadPool D_800EBEB0_minigame;
extern D_800EBEB8_minigame_Entry D_800EBEB8_minigame[64];
extern u16 D_800EC1B8_minigame;
/* Indexed by D_800EBE28_minigame one slot before D_800EC1C0_minigame, only read
   by the stardust battle overlay. */
extern omObjData *D_800EC1BC_minigame[];
extern omObjData *D_800EC1C0_minigame[];
extern HuMtx4F D_800EC240_minigame;
extern u16 D_800EC280_minigame;
extern omObjData *D_800EC598_minigame[];
extern f32 D_800EC5D8_minigame;

#endif
