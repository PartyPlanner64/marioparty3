#ifndef _GAME_SPRITE_H
#define _GAME_SPRITE_H

#include "ultra64.h"
#include "humath.h"

#define HUSPR_GRP_MAX 256

#define HUSPR_NONE -1

#define HUSPR_ATTR_DISPOFF 0x8000
#define HUSPR_ATTR_NOPAUSE 0x1000000

// Playback modes (HuSprite.animMode)
#define HUSPR_ANIM_MODE_STOP 0          // no animation
#define HUSPR_ANIM_MODE_BANK 1          // play the frames of the current bank
#define HUSPR_ANIM_MODE_PAT_LOOP 2      // step through every pattern, looping
#define HUSPR_ANIM_MODE_PAT_PINGPONG 3  // step through every pattern, reversing at each end

// Playback status flags (HuSprite.animStat)
#define HUSPR_ANIM_STAT_UPDATE 0x1  // the animation was stepped this frame
#define HUSPR_ANIM_STAT_END 0x2     // a bank finished playing
#define HUSPR_ANIM_STAT_FRAME 0x4   // advanced to a new frame
#define HUSPR_ANIM_STAT_LOOP 0x8    // looped or reversed
#define HUSPR_ANIM_STAT_INIT 0x80   // the initial frame has been applied

#define HuSprDispOff(grpId, memberNo) HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF)
#define HuSprDispOn(grpId, memberNo) HuSprAttrReset(grpId, memberNo, HUSPR_ATTR_DISPOFF)

// One image (pattern) of sprite animation data. Frames select a pattern by
// index, and the pattern is drawn relative to its center point.
typedef struct HuSprAnimPat {
    /* 0x00 */ void *data;
    /* 0x04 */ u16 sizeX;
    /* 0x06 */ u16 sizeY;
    /* 0x08 */ s16 centerX;
    /* 0x0A */ s16 centerY;
} HuSprAnimPat; // Size 0xC

// One frame of an animation bank.
typedef struct HuSprAnimFrame {
    /* 0x00 */ u16 pat;
    /* 0x02 */ s16 time; // negative loops back to the first frame
    /* 0x04 */ u8 shiftX;
    /* 0x05 */ u8 shiftY;
    /* 0x06 */ u8 flip; // XORed into the sprite attributes
    /* 0x07 */ u8 unk07;
} HuSprAnimFrame; // Size 0x8

// An animation sequence: a frame count plus its frame table.
typedef struct HuSprAnimBank {
    /* 0x00 */ u16 timeNum;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ HuSprAnimFrame *frame;
} HuSprAnimBank; // Size 0x8

// Sprite animation data, as produced by HuSprAnimRead or HuSprAnimMake.
typedef struct HuSprAnimData {
    /* 0x00 */ HuSprAnimPat *pat;
    /* 0x04 */ HuSprAnimBank **bank;
    /* 0x08 */ void *data; // pixel data of the first pattern
    /* 0x0C */ void *pal;
    /* 0x10 */ u16 patNum;
    /* 0x12 */ u16 bankNum;
    /* 0x14 */ s16 sizeX;
    /* 0x16 */ s16 sizeY;
    /* 0x18 */ u16 pixelBits; // low 15 bits: bits per pixel; bit 15 selects the intensity draw path
    /* 0x1A */ u16 palNum;
} HuSprAnimData; // Size 0x1C

// Animation playback state. Embedded in HuSprite at offset 0x68 (anim);
// the animation functions receive a pointer to this region.
typedef struct HuSprAnm {
    /* 0x00 */ HuSprAnimData *data;
    /* 0x04 */ u8 animStat;  // HUSPR_ANIM_STAT_* flags
    /* 0x06 */ s16 animMode; // HUSPR_ANIM_MODE_*
    /* 0x08 */ s16 bank;
    /* 0x0A */ s16 animNo;   // frame within the bank, or pattern for the pattern modes
    /* 0x0C */ f32 time;
    /* 0x10 */ f32 speed;
    /* 0x14 */ s16 patNo;    // current pattern
    /* 0x16 */ u8 flip;
    /* 0x17 */ u8 shiftX;
    /* 0x18 */ u8 shiftY;
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
    /* 0x0E */ s16 animMode;
    /* 0x10 */ f32 speed;
    /* 0x14 */ u16 prio;
    /* 0x18 */ f32 unk_18;
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ f32 unk_20;
    /* 0x24 */ s32 dispAttr; // attr with the current frame's flip applied
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
    /* 0x68 */ HuSprAnm anim;
    /* 0x84 */ HuSprAnimData *data;
    /* 0x88 */ s8 animStat;
    /* 0x8A */ s16 animNo;
    /* 0x8C */ f32 time;
    /* 0x90 */ s16 patNo;
    /* 0x92 */ u8 flip;
    /* 0x93 */ u8 shiftX;
    /* 0x94 */ u8 shiftY;
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
    /* 0x200 */ s32 prevAttr; // attributes from the previous frame
    /* 0x204 */ u16 scissorX;
    /* 0x206 */ u16 scissorY;
    /* 0x208 */ u16 scissorX2;
    /* 0x20A */ u16 scissorY2;
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

#ifndef NO_EXTERN_VARIABLES
extern HuSprGrp *HuSprGrpData[HUSPR_GRP_MAX];

extern s16 D_800D10F2_main;
#endif

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
HuSprAnimData *func_80055194_main(s16 arg0);
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
void func_80055588_main(s16 group, s16 member, f32 arg2, f32 arg3);
void func_800555B8_main(s16 group, s16 member, u16 arg2, u16 arg3);
void HuSprScissorSet(s16 group, s16 member, u16 arg2, u16 arg3, u16 arg4, u16 arg5);
void func_80055628_main(void);
void HuSprAnimAllKill(void);
s32 func_80055DBC_main(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4);
void func_80055FF4_main(HuSprAnm *arg0, s16 arg1, u16 arg2, u16 arg3);
s16 func_80056054_main(void *arg0, HuSprAnm *arg1, u16 arg2, u16 arg3);
HuSprAnimPat *func_800560B8_main(HuSprAnimData **arg0, u16 arg1);
HuSprAnimPat *func_800560D8_main(s16 arg0, u16 arg1);
HuSprAnimPat *func_80056108_main(HuSprAnm *arg0);
void *func_80056128_main(HuSprAnimData **arg0, u16 arg1);
void *func_8005614C_main(s16 arg0, u16 arg1);
void func_80056180_main(HuSprAnimData **arg0, u16 arg1, void *arg2);
void func_800561D0_main(s16 arg0, u16 arg1, void *arg2);
void *func_80056230_main(HuSprAnm *arg0);
void *func_80056254_main(HuSprAnimData **arg0);
void *func_80056260_main(s16 arg0);
void func_8005627C_main(HuSprAnimData **arg0, void *arg1);
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
