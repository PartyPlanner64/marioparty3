#include "common.h"
#include "mstory4.h"

// Misaligned u16 array after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory4Scene1Bss {
    /* 0x00 */ s16 unk00;       // mstory4_scene1TumbleFaceSlot
    /* 0x02 */ u16 unk02[2][2]; // mstory4_scene1VignetteSprTbl
} Mstory4Scene1Bss;             // sizeof 0x0A

// Misaligned s16 array after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory4Scene1SprBss {
    /* 0x00 */ s16 unk00;    // mstory4_scene1SparkAnim
    /* 0x02 */ s16 unk02[2]; // mstory4_scene1TitleSprTbl
} Mstory4Scene1SprBss;       // sizeof 0x06

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 mstory4_winId BSS;
s16 mstory4_backMdl BSS;
s32 mstory4_padNo BSS;
u16 mstory4_backSpr BSS;
u8 mstory4_backSprPad[4] BSS; /* Unreferenced. */
s16 mstory4_stampCardSprTbl[8] BSS;
s16 mstory4_stampSparkSprTbl[7][8] BSS;
s16 mstory4_stampFadeSpr BSS;
s32 mstory4_stampNo BSS;
u8 mstory4_stampNoPad[8] BSS; /* Unreferenced. */

/* scene0.c */
StoryObjWork mstory4_scene0WorkTbl[5] BSS;
s32 mstory4_scene0TumbleFaceAnimTbl[4] BSS; // [i] low halves: mstory4_scene0TumbleFaceAnim0-3
s16 mstory4_scene0TumbleFaceSlot BSS;
u8 mstory4_scene0TumbleFaceSlotPad[4] BSS; /* Unreferenced. */
Vec mstory4_scene0PlayerPos BSS;
Vec mstory4_scene0TumblePos BSS;
Vec mstory4_scene0WaluigiPos BSS;
Vec mstory4_scene0StarPos BSS;
Vec mstory4_scene0StampPos BSS;
s16 mstory4_scene0ShadowMdl BSS;
s16 mstory4_scene0StampEff BSS;
s16 mstory4_scene0PlayerFaceAnimTbl[4] BSS;
u8 mstory4_scene0PlayerFaceAnimTblPad[8] BSS; /* Unreferenced. */

/* scene1.c */
StoryObjWork mstory4_scene1WorkTbl[4] BSS;
Vec mstory4_scene1PlayerPos BSS;
Vec mstory4_scene1TumblePos BSS;
Vec mstory4_scene1StarPos BSS;
s16 mstory4_scene1ShadowMdl BSS;
s16 mstory4_scene1StarEff BSS;
s16 mstory4_scene1PlayerFaceAnimTbl[5] BSS;
u8 mstory4_scene1PlayerFaceAnimTblPad[4] BSS;  /* Unreferenced. */
s32 mstory4_scene1TumbleFaceAnimTbl[4] BSS; // [3] low half: mstory4_scene1TumbleFaceAnim3
Mstory4Scene1Bss mstory4_scene1Bss BSS;
s16 mstory4_scene1VignetteAnim BSS;
u8 mstory4_scene1VignetteAnimPad[4] BSS;  /* Unreferenced. */
s16 mstory4_scene1PicAnimTbl[8] BSS; // [7]: mstory4_scene1PicAnim7
s16 mstory4_scene1PicSprTbl[8] BSS; // [7]: mstory4_scene1PicSpr7
s16 mstory4_scene1SparkSprTbl[22] BSS;
Mstory4Scene1SprBss mstory4_scene1SprBss BSS;
u8 mstory4_scene1TitleSprTblPad[4] BSS; /* Unreferenced. */

/* main.c */
s32 mstory4_playerOrderTbl[4] BSS;
