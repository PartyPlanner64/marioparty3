#ifndef _OVL_MINIGAME_H
#define _OVL_MINIGAME_H

#include "ultra64.h"
#include "game/object.h"

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
    /* 0x0BC */ char unkBC[2];
    /* 0x0BE */ u16 unkBE;
    /* 0x0C0 */ s16 unkC0;
    /* 0x0C2 */ u8 unkC2;
    /* 0x0C3 */ s8 unkC3;
    /* 0x0C4 */ s8 unkC4;
    /* 0x0C5 */ char unkC5[3];
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
    /* 0x54 */ s8 unk54;
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

void func_800E18D8_minigame(void);
void func_800E19F0_minigame(s8);
void func_800E1804_minigame(void);
void func_800E1810_minigame(void);
void func_800E1BA8_minigame(omObjData *, u32, s32, u16, s32, s32);
void func_800E4E30_minigame(omObjData *);
void func_800E5638_minigame(func_800E5638_minigame_UnkD8_ObjData *, u16, u16, u16, s16);
s32 func_800E5690_minigame(omObjData *, u16);
void func_800E5978_minigame(omObjData *, u16, s32, u16, u16);
void func_800E5A00_minigame(omObjData *, u16, s32, s32, u16);
void func_800E5EA0_minigame(D_80111B50_vine_with_me_Struct *);
u8 func_800E6E8C_minigame(void);
u16 func_800E6E9C_minigame(void);
void func_800E6F1C_minigame(void);
void func_800E6F34_minigame(s32);
u8 func_800E6F40_minigame();

extern u16 D_800EBE28_minigame;
extern u16 D_800EB910_minigame;
extern u16 D_800EB912_minigame;
extern u16 D_800EB914_minigame;
extern u16 D_800EB916_minigame;
extern u16 D_800EB918_minigame;
extern s16 D_800EB736_minigame;
extern D_800EBEB8_minigame_Entry D_800EBEB8_minigame[64];
extern u16 D_800EC1B8_minigame;
extern omObjData *D_800EC1C0_minigame[];
/* Indexed by D_800EBE28_minigame one slot before D_800EC1C0_minigame, only read
   by the stardust battle overlay. */
extern omObjData *D_800EC1BC_minigame[];
extern u16 D_800EC280_minigame;
extern omObjData *D_800EC598_minigame[];
extern D_80111B50_vine_with_me_Struct *D_800EBDE0_minigame;

#endif
