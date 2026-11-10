#include "common.h"
#include "game/process.h"
#include "common_structs.h"
#include "game/malloc.h"
#include "game/board.h"

typedef struct unkStruct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} unkStruct;
typedef struct unkStruct01 {
    /* 0x00 */ f32 unk_00;
    /* 0x04 */ char unk_04[4];
    /* 0x08 */ f32 unk_08;
} unkStruct01;

typedef struct unkStruct02 {
    /* 0x00 */ Vec unk_00;
    /* 0x0C */ char unk_0C[4];
} unkStruct02;

typedef struct unkStruct03 {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ HeapNode *unk_18;
    /* 0x1C */ char unk_1C[0x70];
    /* 0x8C */ unkStruct02 *unk_8C;
} unkStruct03;

typedef struct unkStruct04 {
    /* 0x00 */ char unk_00[0x0C];
    /* 0x0C */ Vec unk_0C;
} unkStruct04;

typedef struct unkStruct05 {
    /* 0x00 */ char unk_00[0x24];
    /* 0x24 */ s32 unk_24;
} unkStruct05;

typedef struct unkStruct06 {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ char unk_0C[4];
} unkStruct06;

typedef void (*PartnerFunc)(s16, s32, Object *, Object *, s32, s32);

typedef struct Duel01PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel01PartnerAttackWork; // sizeof 0x10

typedef struct Duel01SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel01SwayWork; // sizeof 0x10

extern s16 omovlevtno;
f32 func_800D76D0_name_81(void *);
void func_80100CEC_name_81(s32 padIdx);
s32 func_800E1824_name_81(s32, s32, s32);
s32 func_800E88FC_name_81(void);
void func_800E1854_name_81(s32);
extern s32 D_80119470_duel01;
extern s32 D_80119474_duel01;
extern s32 D_80119478_duel01;
extern s32 D_8011947C_duel01;
extern omObjData *D_8011948C_duel01;
extern Object *D_80119498_duel01;
extern Object *D_801194A0_duel01;
extern Object *D_801194AC_duel01[5];
extern s32 D_8011875C_duel01;
void func_800E94D0_name_81(void);
void func_800E9564_name_81(void);
void func_800E9B10_name_81(s32, s32);
void func_800E9D9C_name_81(void);
void func_800E9F4C_name_81(s32, s8 *, s8 *);
void func_800EA760_name_81(void);
void func_800ECD0C_name_81(s16, s16, s16);
void func_800EB708_name_81(s32, s32, unkStruct01 *);
unkStruct03 *func_80047EA0_main(void *, s32, s32, s32);
void func_80105CC0_duel01(void); // probably takes object as arg
void func_800FC8C4_name_81(Vec *arg0);
extern Vec D_80105540_name_81;
void func_800EC1E4_name_81(void *, s32, void *, f32);
void func_800EBF2C_name_81(void *, s32, void *);
void func_80106308_duel01(void);
void *func_800D8010_name_81(s32, s32);
void func_800D8944_name_81(Object *);
void func_800D8F0C_name_81(Object *);
void func_80089A20_main(Vec *, s32);
void func_800D8E88_name_81(void);
s16 MBDGetCurrentPlayerIndex(void);
void func_800F38DC_name_81(s32, s32, s32);
void func_8010D9F4_duel01(void);
void func_800FF640_name_81(s32);
void func_8010E1B4_duel01(void);
void func_8010E7C0_duel01(void);
void func_8010EAD4_duel01(s32);
void func_80110068_duel01(s32);
void func_80105F20_duel01(void);
void func_80106828_duel01(s16, s32, Object *, Object *, s32, s32);
void func_80107188_duel01(s16, s32, Object *, Object *, s32, s32);
void func_801079B8_duel01(s16, s32, Object *, Object *, s32, s32);
void func_80107EBC_duel01(s16, s32, Object *, Object *, s32, s32);
void func_801084A4_duel01(s16, s32, Object *, Object *, s32, s32);
void func_80108550_duel01(s16, s32, Object *, Object *, s32, s32);
void func_80109888_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010A210_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010B54C_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010BCD4_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010CE68_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010D424_duel01(s16, s32, Object *, Object *, s32, s32);
void func_8010DDEC_duel01(void);
void func_8010E3F8_duel01(void);
void func_8011390C_duel01(void);
s32 func_80118328_duel01(void);
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_800EA46C_name_81(event_table_entry *);
void func_800FC5A8_name_81(process_func);
void func_800FC59C_name_81(s32 (*)(void));
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800ED214_name_81(s32 playerIndex);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
extern event_table_entry D_80118914_duel01[];
extern event_table_entry D_80118DEC_duel01[];
extern Process *D_80118744_duel01;
extern Process *D_8011874C_duel01;
extern f32 D_8011949C_duel01;
extern f32 D_801194A4_duel01;
