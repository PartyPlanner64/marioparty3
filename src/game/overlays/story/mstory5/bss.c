#include "common.h"
#include "mstory5.h"

// Misaligned s16 arrays after an s16 (see undefined_syms.txt for aliases).
typedef struct Mstory5Scene1Bss {
    /* 0x00 */ s16 unk00;    // mstory5_scene1TumbleFaceSlot
    /* 0x02 */ s16 unk02[4]; // mstory5_scene1PlayerFaceAnimTbl ([1]: mstory5_scene1PlayerFaceAnim1)
    /* 0x0A */ s16 unk0A[4]; // mstory5_scene1DaisyFaceAnimTbl
} Mstory5Scene1Bss;          // sizeof 0x14

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* main.c */
s16 mstory5_winId BSS;
s16 mstory5_backMdl BSS;
s32 mstory5_padNo BSS;
u16 mstory5_backSpr BSS;
u8 mstory5_backSprPad[4] BSS; /* Unreferenced. */
s16 mstory5_stampCardSprTbl[8] BSS;
s16 mstory5_stampSparkSprTbl[8] BSS;
s16 mstory5_stampFadeSpr BSS;
s32 mstory5_stampNo BSS;
u8 mstory5_stampNoPad[8] BSS; /* Unreferenced. */

/* scene1.c */
StoryObjWork mstory5_scene1WorkTbl[9] BSS;
StoryObjWork mstory5_scene1EventWork BSS;
StoryObjWork mstory5_scene1SubEventWork BSS;
Vec mstory5_scene1PlayerPos BSS;
Vec mstory5_scene1TumblePos BSS;
Vec mstory5_scene1RivalPos BSS;
Vec mstory5_scene1DaisyPos BSS;
Vec mstory5_scene1KoopaPos BSS;
Vec mstory5_scene1KoopaJrAPos BSS;
Vec mstory5_scene1KoopaJrBPos BSS;
Vec mstory5_scene1StarPos BSS;
Vec mstory5_scene1StampPos BSS;
s16 mstory5_scene1ShadowMdl BSS;
s16 mstory5_scene1StampEff BSS;
s16 mstory5_scene1ShockMdl BSS;
u8 mstory5_scene1ShockMdlPad[4] BSS;  /* Unreferenced. */
s32 mstory5_scene1TumbleFaceAnimTbl[4] BSS; // [i] low halves: mstory5_scene1TumbleFaceAnim0-3
Mstory5Scene1Bss mstory5_scene1Bss BSS;
u8 mstory5_scene1DaisyFaceAnimTblPad[12] BSS; /* Unreferenced. */

/* scene0.c */
StoryObjWork mstory5_scene0WorkTbl[8] BSS;
StoryObjWork mstory5_scene0FireWork BSS;
Vec mstory5_scene0PlayerPos BSS;
Vec mstory5_scene0TumblePos BSS;
Vec mstory5_scene0RivalPos BSS;
Vec mstory5_scene0KoopaPos BSS;
Vec mstory5_scene0KoopaJrAPos BSS;
Vec mstory5_scene0KoopaJrBPos BSS;
Vec mstory5_scene0StarPos BSS;
Vec mstory5_scene0StampPos BSS;
s16 mstory5_scene0ShadowMdl BSS;
s16 mstory5_scene0StampEff BSS;
s16 mstory5_scene0PlayerFaceAnimTbl[4] BSS;
s32 mstory5_scene0TumbleFaceAnimTbl[3] BSS; // [i] low halves: mstory5_scene0TumbleFaceAnim0-2
s16 mstory5_scene0TumbleFaceSlot BSS;
u8 mstory5_scene0TumbleFaceSlotPad[4] BSS; /* Unreferenced. */
Mstory5FireParticle mstory5_scene0FireParticleTbl[16] BSS;
u8 mstory5_scene0FireParticleTblPad[0x18] BSS; /* Unreferenced. */
