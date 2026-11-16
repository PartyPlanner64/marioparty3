#include "common.h"
#include "mstory3.h"

// Misaligned s16 arrays between s16 scalars (see undefined_syms.txt for aliases).
typedef struct Mstory3Scene1Bss {
    /* 0x00 */ s16 unk00[3]; // mstory3_scene1TumbleFaceAnimTbl
    /* 0x06 */ s16 unk06;    // mstory3_scene1TumbleFaceSlot
    /* 0x08 */ s16 unk08;    // mstory3_scene1StarFloatStopF
    /* 0x0A */ s16 unk0A[3]; // mstory3_scene1PlayerFaceAnimTbl
    /* 0x10 */ s16 unk10;    // mstory3_scene1PlayerFaceSlot
    /* 0x12 */ s16 unk12[3]; // mstory3_scene1RivalFaceAnimTbl
    /* 0x18 */ s16 unk18;    // mstory3_scene1RivalFaceSlot
    /* 0x1A */ s16 unk1A;    // mstory3_scene1ShadowMdl
} Mstory3Scene1Bss; // sizeof 0x1C

// Two s16 arrays, the second one misaligned (see undefined_syms.txt for aliases).
typedef struct Mstory3Scene1ChrBss {
    /* 0x00 */ s16 unk00[3]; // mstory3_scene1PlayerChr ([1]: mstory3_scene1RivalChr)
    /* 0x06 */ s16 unk06[7]; // mstory3_scene0CloudStarTimeTbl
} Mstory3Scene1ChrBss; // sizeof 0x14

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 mstory3_padNo BSS;
s16 mstory3_winId BSS;
u16 mstory3_backSpr BSS;
s16 mstory3_backMdl BSS;
s16 mstory3_stampCardSprTbl[8] BSS;
s16 mstory3_stampSparkSprTbl[8] BSS;
s16 mstory3_stampFadeSpr BSS;
s32 mstory3_stampNo BSS;

/* scene1.c */
Mstory3ObjWork mstory3_scene1WorkTbl[6] BSS;
u8 mstory3_scene1WorkTblPad[12] BSS; /* Unreferenced. */
Vec mstory3_scene1RivalPos BSS;
Vec mstory3_scene1TumblePos BSS;
Vec mstory3_scene1StarPos BSS;
Vec mstory3_scene1StampPos BSS;
Vec mstory3_scene1UnusedPos1 BSS; /* Unreferenced. */
Mstory3Scene1Bss mstory3_scene1Bss BSS;
Mstory3Scene1ChrBss mstory3_scene1ChrBss BSS;

/* scene0.c */
Mstory3ObjWork mstory3_scene0WorkTbl[11] BSS;
s16 mstory3_scene0ShadowMdl BSS;
s16 mstory3_scene0TumbleFaceSlot BSS;
s16 mstory3_scene0TumbleFaceAnimTbl[3] BSS;
s16 mstory3_scene0StampBSpinF BSS;
s16 mstory3_scene0PlayerFaceAnimTbl[5] BSS;
s16 mstory3_scene0PlayerFaceSlot BSS;
s16 mstory3_scene0WaluigiFaceAnimTbl[5] BSS;
s16 mstory3_scene0WaluigiFaceSlot BSS;
s16 mstory3_scene0PlayerChr BSS;
u8 mstory3_scene0BssPad[12] BSS; /* Unreferenced. */

/* main.c */
s16 mstory3_playerOrderTbl[4] BSS;
