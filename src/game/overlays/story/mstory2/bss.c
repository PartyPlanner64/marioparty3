#include "common.h"
#include "mstory2.h"

// Per-scene s16 variables, some arrays misaligned (see undefined_syms.txt for aliases).
typedef struct Mstory2SceneBss {
    /* 0x00 */ s16 unk00[3]; // scene<N>TumbleFaceAnimTbl
    /* 0x06 */ s16 unk06;    // scene<N>TumbleFaceSlot
    /* 0x08 */ s16 unk08;    // scene<N>StarFloatStopF
    /* 0x0A */ s16 unk0A[3]; // scene<N>PlayerFaceAnimTbl
    /* 0x10 */ s16 unk10;    // scene<N>PlayerFaceSlot
    /* 0x12 */ s16 unk12[3]; // scene<N>RivalFaceAnimTbl
    /* 0x18 */ s16 unk18;    // scene<N>RivalFaceSlot
    /* 0x1A */ s16 unk1A;    // scene<N>ShadowMdl
    /* 0x1C */ s16 unk1C;    // scene<N>PlayerChr
    /* 0x1E */ s16 unk1E;    // scene<N>RivalChr
} Mstory2SceneBss; // sizeof 0x20

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 mstory2_sceneNo BSS;
s16 mstory2_padNo BSS;
s16 mstory2_winId BSS;
u16 mstory2_backSpr BSS;
s16 mstory2_backMdl BSS;
u8 mstory2_backMdlPad[4] BSS; /* Unreferenced. */
s16 mstory2_stampCardSprTbl[8] BSS;
s16 mstory2_stampSparkSprTbl[8] BSS;
s16 mstory2_stampFadeSpr BSS;
s32 mstory2_stampNo BSS;
u8 mstory2_stampNoPad[8] BSS; /* Unreferenced. */

/* scene1.c */
Mstory2ObjWork mstory2_scene1WorkTbl[6] BSS;
u8 mstory2_scene1WorkTblPad[12] BSS; /* Unreferenced. */
Vec mstory2_scene1RivalPos BSS;
Vec mstory2_scene1TumblePos BSS;
Vec mstory2_scene1StarPos BSS;
Vec mstory2_scene1StampPos BSS;
Vec mstory2_scene1UnusedPos1 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2_scene1Bss BSS;

/* scene2.c */
Mstory2ObjWork mstory2_scene2WorkTbl[6] BSS;
u8 mstory2_scene2WorkTblPad[12] BSS; /* Unreferenced. */
Vec mstory2_scene2RivalPos BSS;
Vec mstory2_scene2TumblePos BSS;
Vec mstory2_scene2StarPos BSS;
Vec mstory2_scene2StampPos BSS;
Vec mstory2_scene2UnusedPos1 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2_scene2Bss BSS;

/* scene3.c */
Mstory2ObjWork mstory2_scene3WorkTbl[6] BSS;
u8 mstory2_scene3WorkTblPad[12] BSS; /* Unreferenced. */
Vec mstory2_scene3RivalPos BSS;
Vec mstory2_scene3TumblePos BSS;
Vec mstory2_scene3StarPos BSS;
Vec mstory2_scene3StampPos BSS;
Vec mstory2_scene3UnusedPos1 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2_scene3Bss BSS;

/* scene4.c */
Mstory2ObjWork mstory2_scene4WorkTbl[6] BSS;
u8 mstory2_scene4WorkTblPad[12] BSS; /* Unreferenced. */
Vec mstory2_scene4RivalPos BSS;
Vec mstory2_scene4TumblePos BSS;
Vec mstory2_scene4StarPos BSS;
Vec mstory2_scene4StampPos BSS;
Vec mstory2_scene4UnusedPos1 BSS; /* Unreferenced. */
Mstory2SceneBss mstory2_scene4Bss BSS;

/* scene0.c */
u8 mstory2_scene0BssPad[4] BSS; /* Unreferenced. */
f32 mstory2_scene0StarY BSS;
u8 mstory2_scene0StarYPad[8] BSS; /* Unreferenced. */
Mstory2ObjWork mstory2_scene0WorkTbl[3] BSS;
s16 mstory2_scene0ShadowMdl BSS;
Vec mstory2_scene0TumblePos BSS;
Vec mstory2_scene0StarPos BSS;
Vec mstory2_scene0UnusedPos1 BSS; /* Unreferenced. */
s16 mstory2_scene0TumbleFaceAnimTbl[3] BSS;
s16 mstory2_scene0TumbleFaceSlot BSS;
u8 mstory2_scene0TumbleFaceSlotPad[4] BSS; /* Unreferenced. */

/* main.c */
s16 mstory2_playerOrderTbl[4] BSS;
