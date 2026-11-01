#ifndef _GAME_SPRITE_H
#define _GAME_SPRITE_H

#include "ultra64.h"
#include "humath.h"

#define HUSPR_GRP_MAX 256

#define HUSPR_NONE -1

#define HUSPR_ATTR_DISPOFF 0x8000

#define HuSprDispOff(grpId, memberNo) HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF)
#define HuSprDispOn(grpId, memberNo) HuSprAttrReset(grpId, memberNo, HUSPR_ATTR_DISPOFF)

typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
} HuSprite_Unk84_Unk00_Struct; // Size 0xC

// One frame of a cel animation (built by the cel-anm loader).
typedef struct HuSprCelFrame {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02; // duration; negative loops back to the first frame
    /* 0x04 */ u8 unk04;
    /* 0x05 */ u8 unk05;
    /* 0x06 */ u8 unk06;
    /* 0x07 */ u8 unk07;
} HuSprCelFrame; // Size 0x8

// A cel within a cel animation: a count plus its frame table.
typedef struct HuSprCelAnm {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ HuSprCelFrame *unk04;
} HuSprCelAnm; // Size 0x8

typedef struct {
    /* 0x00 */ HuSprite_Unk84_Unk00_Struct *unk00;
    /* 0x04 */ HuSprCelAnm **unk04;
    /* 0x08 */ void *unk08;
    /* 0x0C */ void *unk0C; // pal data?
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
} HuSprite_Unk84_Struct; // Size 0x1C

// Cel-animation playback state. Embedded in HuSprite at offset 0x68 (unk_68);
// the animation functions receive a pointer to this region.
typedef struct HuSprAnm {
    /* 0x00 */ HuSprite_Unk84_Struct *unk00; // texture descriptor
    /* 0x04 */ u8 unk04;                     // flags
    /* 0x06 */ s16 unk06;                    // playback mode
    /* 0x08 */ s16 unk08;                    // cel index
    /* 0x0A */ s16 unk0A;                    // frame counter
    /* 0x0C */ f32 unk0C;                    // time accumulator
    /* 0x10 */ f32 unk10;                    // frame step
    /* 0x14 */ s16 unk14;                    // current cel output
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
} HuSprAnm; // Size 0x1C

// Palette animation data (built by the palette-animation loader, stored in
// the D_800D0A50_main table). Each group cycles through frames that overwrite
// a set of palette entries.
typedef struct HuSprPalEntry {
    /* 0x00 */ u16 index;
    /* 0x02 */ u16 color;
} HuSprPalEntry; // Size 0x4

typedef struct HuSprPalFrame {
    /* 0x00 */ s16 duration;
    /* 0x04 */ HuSprPalEntry *entries;
} HuSprPalFrame; // Size 0x8

typedef struct HuSprAnmEntry {
    /* 0x00 */ u16 unk00;             // palette entries per frame
    /* 0x02 */ u16 unk02;             // frame count
    /* 0x04 */ HuSprPalFrame **unk04; // frames
} HuSprAnmEntry;                      // Size 0x8

typedef struct HuSprAnmDesc {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;             // group count
    /* 0x04 */ HuSprAnmEntry **unk04; // groups
    /* 0x08 */ u16 unk08;             // palette color count
    /* 0x0C */ u16 *unk0C;            // base palette
} HuSprAnmDesc;                       // Size 0x10

// Palette-animation playback state. Embedded in HuSprite at offset 0x98;
// the palette animation functions receive a pointer to this region.
typedef struct HuSprPalAnm {
    /* 0x00 */ HuSprAnmDesc *unk00;
    /* 0x04 */ u16 unk04[0x10]; // current frame per group
    /* 0x24 */ f32 unk24[0x10]; // remaining frame time per group
    /* 0x64 */ union {
        f32 f;
        s32 i;
    } unk64;                  // speed
    /* 0x68 */ u16 unk68;     // next palette buffer
    /* 0x6C */ u16 *unk6C;    // current palette
    /* 0x70 */ u16 *unk70[3]; // palette buffers
} HuSprPalAnm;                // Size 0x7C

typedef struct HuSprite {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ s16 bank;
    /* 0x0E */ s16 unk_0E;
    /* 0x10 */ f32 speed;
    /* 0x14 */ u16 prio;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ u8 color[4];
    /* 0x2C */ u16 tpLvl;
    /* 0x2E */ s16 unk_2E;
    /* 0x30 */ union {
        f32 f;
        s32 i;
    } unk_30;
    /* 0x34 */ union {
        f32 f;
        s32 i;
    } unk_34;
    /* 0x38 */ u16 unk_38;
    /* 0x3A */ u16 unk_3A;
    /* 0x3C */ u16 unk_3C;
    /* 0x3E */ u16 unk_3E;
    /* 0x40 */ u16 unk_40;
    /* 0x42 */ u16 unk_42;
    /* 0x44 */ s32 unk_44;
    /* 0x48 */ Vec2f pos;
    /* 0x50 */ Vec2f scale;
    /* 0x58 */ f32 zRot;
    /* 0x5C */ s32 attr;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ HuSprAnm unk_68;
    /* 0x84 */ HuSprite_Unk84_Struct *unk_84;
    /* 0x88 */ s8 unk_88;
    /* 0x8A */ s16 unk_8A;
    /* 0x8C */ f32 unk_8C;
    /* 0x90 */ s16 unk_90;
    /* 0x92 */ u8 unk_92;
    /* 0x93 */ u8 unk_93;
    /* 0x94 */ u8 unk_94;
    /* 0x95 */ char unk_95_pad[0x3];
    /* 0x98 */ HuSprPalAnm unk_98;
    /* 0x114 */ s16 unk_114;
    /* 0x116 */ s16 unk_116;
    /* 0x118 */ struct HuSprite *unk_118; // next sprite in the priority-sorted draw list
    /* 0x11C */ struct HuSprite *unk_11C; // previous sprite in the priority-sorted draw list
    /* 0x120 */ s32 unk_120;
    /* 0x124 */ Gfx *unk_124;
    /* 0x128 */ Gfx *unk_128[3];
    /* 0x134 */ Vtx *unk_134[3];
    /* 0x140 */ Mtx unk_140[3];
    /* 0x200 */ s32 unk_200; // attributes from the previous frame
    /* 0x204 */ u16 unk_204;
    /* 0x206 */ u16 unk_206;
    /* 0x208 */ u16 unk_208;
    /* 0x20A */ u16 unk_20A;
    /* 0x20C */ char unk_20C_pad[0x4];
} HuSprite; // Size 0x210

typedef struct HuSprGrp {
    struct HuSprGrp *next;
    struct HuSprGrp *prev;
    u16 unk_08; // hierarchy mode
    u16 unk_0A;
    s32 dirty;
    HuSprite *members[4]; // unknown size
} HuSprGrp;               // unknown size

extern HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX];

void HuSprInit(void);
void HuSprGrpKill(s16);
s16 HuSprGrpCreate(u16 arg0, u16 arg1);
void HuSprPosSet(s16 group, s16 member, s16 arg2, s16 arg3);
void func_80054FF8_main(s16 group, s16 member, s32 arg2);
void HuSprGrpMemberSet(s16 group, s16 member, s16 arg2, u16 arg3);
void HuSprSpeedSet(s16 group, s16 member, f32 arg2);
void func_800550F4_main(s16, s16, s32);
void HuSprBankSet(s16, s16, u16, s32);
u8 func_800551AC_main(s16 group, s16 member);
HuSprite_Unk84_Struct *func_80055194_main(s16 arg0);
void HuSprScaleSet(s16 group, s16 member, f32 x, f32 y);
void HuSprPriSet(s16 group, s16 member, u16 prio);
void HuSprZRotSet(s16, s16, f32);
void HuSprAttrReset(s16 group, s16 member, s32 attr);
void HuSprAttrSet(s16 group, s16 member, s32 attr);
void HuSprColorSet(s16, s16, u8, u8, u8);
void HuSprTPLvlSet(s16, s16, u16);
void func_800554C4_main(s16 group, s16 member, s16 arg2);
HuSprite *HuSprGet(s16 group, s16 member);
void HuSprAnimKill(s16);
s16 HuSprAnimRead(void *);
void HuSprClose(void);

HuSprGrp *func_80052468_main(s16 arg0, u16 arg1);
void func_80052518_main(HuSprite *arg0);
void func_80052700_main(void);
s32 HuSprGrpMemberKill(s16 group, s16 member, u16 count);
s32 func_80052A90_main(s16 group, s16 member, u16 count);
void func_80052DD8_main(HuSprAnm *arg0);
void func_80052E14_main(HuSprite *arg0);
void func_80052E68_main(HuSprGrp *group, u16 count);
HuSprite *func_800530AC_main(void);
s16 func_8005338C_main(HuSprGrp *arg0);
void func_800534C8_main(f32 a0[][2], f32 a1[][2], f32 a2[][2]);
void func_80053558_main(void);
void func_80054170_main(void);
void func_80054218_main(Gfx **gdl, s32 arg1, s32 arg2);
void func_80054658_main(Gfx **gdl, s32 arg1, s32 arg2);
void func_800549C0_main(s16 group, s16 member, s16 arg2);
void func_800549F4_main(Mtx *m, f32 x, f32 y, f32 z, f32 w, f32 *ox, f32 *oy, f32 *oz, f32 *ow);
f32 func_80054B1C_main(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z);
void func_80054EE0_main(s16 group, s16 member, s16 camera, f32 x, f32 y, f32 z);
void func_80055484_main(s16 group, s16 member, u8 arg2, u8 arg3, u8 arg4, u16 arg5);
void func_800554F0_main(s16 group, s16 member, u8 arg2, u8 arg3);
void func_80055548_main(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5);
void func_80055588_main(s16 group, s16 member, s32 arg2, s32 arg3);
void func_800555B8_main(s16 group, s16 member, u16 arg2, u16 arg3);
void HuSprScissorSet(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5);
void func_80055628_main(void);
void HuSprAnimAllKill(void);
s32 func_80055DBC_main(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4);
void func_80055FF4_main(HuSprAnm *arg0, s16 arg1, u16 arg2, u16 arg3);
s16 func_80056054_main(void *arg0, HuSprAnm *arg1, u16 arg2, u16 arg3);
HuSprite_Unk84_Unk00_Struct *func_800560B8_main(HuSprite_Unk84_Struct **arg0, u16 arg1);
HuSprite_Unk84_Unk00_Struct *func_800560D8_main(s16 arg0, u16 arg1);
HuSprite_Unk84_Unk00_Struct *func_80056108_main(HuSprAnm *arg0);
void *func_80056128_main(HuSprite_Unk84_Struct **arg0, u16 arg1);
void *func_8005614C_main(s16 arg0, u16 arg1);
void func_80056180_main(HuSprite_Unk84_Struct **arg0, u16 arg1, void *arg2);
void func_800561D0_main(s16 arg0, u16 arg1, void *arg2);
void *func_80056230_main(HuSprAnm *arg0);
void *func_80056254_main(HuSprite_Unk84_Struct **arg0);
void *func_80056260_main(s16 arg0);
void func_8005627C_main(HuSprite_Unk84_Struct **arg0, void *arg1);
void func_800562BC_main(s16 arg0, void *arg1);
s16 func_8005630C_main(HuSprAnm *arg0);
void func_800563A4_main(HuSprAnm *arg0);
void func_80056650_main(HuSprite *sprite);
void func_80056758_main(HuSprite *sprite);
void func_80056C28_main(void);
u16 func_80056C74_main(u8 **arg0);
u32 func_80056C98_main(u8 **arg0);
void func_80056CD0_main(void);
s16 func_80056D18_main(u8 *data);
void func_80056F80_main(s16 arg0);
void func_800570A8_main(s16 group, s16 member, s16 arg2);
void func_8005712C_main(s16 group, s16 member, s32 arg2);
void func_80057158_main(void);
void func_800571C8_main(HuSprPalAnm *arg0);
s32 func_80057400_main(HuSprite *sprite);
s32 func_800575D8_main(f32 vertices[][2]);
void func_800579E4_main(Gfx **gfx, HuSprite *sprite, s32 arg2);
Gfx *func_800589F4_main(Gfx *gfx, HuSprite *sprite, Vtx *vertices, Mtx *matrix, s32 arg4);
void func_8005988C_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt);
void func_80059CDC_main(Gfx **gfx, HuSprite *sprite, u16 height, u16 uls, u16 ult, u16 lrs, u16 lrt, u16 cms, u16 cmt, u16 masks, u16 maskt);

#endif
