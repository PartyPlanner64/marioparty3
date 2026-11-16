#include "common.h"
#include "mstory1.h"

/* The overlay's BSS is shared by all of its code units. Keep allocation order here. */

/* common.c */
s16 mstory1_winId BSS;
s16 mstory1_backMdl BSS;
s32 mstory1_padNo BSS;
u16 mstory1_backSpr BSS;
u8 mstory1_backSprPad[4] BSS; /* Unreferenced. */
s16 mstory1_stampCardSprTbl[8] BSS;
s16 mstory1_stampSparkSprTbl[8] BSS;
s16 mstory1_stampFadeSpr BSS;
s32 mstory1_stampNo BSS;
u8 mstory1_stampNoPad[8] BSS; /* Unreferenced. */

/* scene0.c */
StoryObjWork mstory1_scene0WorkTbl[8] BSS;
Vec mstory1_scene0PlayerPos BSS;
Vec mstory1_scene0TumblePos BSS;
Vec mstory1_scene0RivalPos BSS;
Vec mstory1_scene0KoopaPos BSS;
Vec mstory1_scene0KoopaJrAPos BSS;
Vec mstory1_scene0KoopaJrBPos BSS;
Vec mstory1_scene0StarPos BSS;
Vec mstory1_scene0StampPos BSS;
s16 mstory1_scene0ShadowMdl BSS;
s16 mstory1_scene0StampEff BSS;
s16 mstory1_scene0PlayerFaceAnimTbl[4] BSS;
s32 mstory1_scene0TumbleFaceAnimTbl[3] BSS; // [i] low halves: mstory1_scene0TumbleFaceAnim0-2
s16 mstory1_scene0TumbleFaceSlot BSS;
u8 mstory1_scene0TumbleFaceSlotPad[4] BSS; /* Unreferenced. */

/* scene1.c */
StoryObjWork mstory1_scene1WorkTbl[8] BSS;
Vec mstory1_scene1PlayerPos BSS;
Vec mstory1_scene1TumblePos BSS;
Vec mstory1_scene1RivalPos BSS;
Vec mstory1_scene1KoopaPos BSS;
Vec mstory1_scene1KoopaJrAPos BSS;
Vec mstory1_scene1KoopaJrBPos BSS;
Vec mstory1_scene1StarPos BSS;
Vec mstory1_scene1StampPos BSS;
s16 mstory1_scene1ShadowMdl BSS;
s16 mstory1_scene1StampEff BSS;
s16 mstory1_scene1PlayerFaceAnimTbl[4] BSS;
s32 mstory1_scene1TumbleFaceAnimTbl[3] BSS; // [i] low halves: mstory1_scene1TumbleFaceAnim0-2
s16 mstory1_scene1TumbleFaceSlot BSS;
u8 mstory1_scene1TumbleFaceSlotPad[4] BSS; /* Unreferenced. */

/* scene2.c */
StoryObjWork mstory1_scene2WorkTbl[8] BSS;
Vec mstory1_scene2PlayerPos BSS;
Vec mstory1_scene2TumblePos BSS;
Vec mstory1_scene2RivalPos BSS;
Vec mstory1_scene2KoopaPos BSS;
Vec mstory1_scene2KoopaJrAPos BSS;
Vec mstory1_scene2KoopaJrBPos BSS;
Vec mstory1_scene2StarPos BSS;
Vec mstory1_scene2StampPos BSS;
s16 mstory1_scene2ShadowMdl BSS;
s16 mstory1_scene2StampEff BSS;
s16 mstory1_scene2PlayerFaceAnimTbl[4] BSS;
s32 mstory1_scene2TumbleFaceAnimTbl[3] BSS; // [i] low halves: mstory1_scene2TumbleFaceAnim0-2
s16 mstory1_scene2TumbleFaceSlot BSS;
u8 mstory1_scene2TumbleFaceSlotPad[4] BSS; /* Unreferenced. */

/* main.c */
s32 mstory1_playerOrderTbl[4] BSS;
