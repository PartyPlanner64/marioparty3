#include "common_duel.h"
#include "game/process.h"
#include "common_structs.h"
#include "game/malloc.h"
#include "game/board.h"
#include "game/overlays/duel/common/ovl_81.h"

typedef struct unkStruct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ s16 unk_04;
} unkStruct;

typedef struct Duel01SpriteWork {
    /* 0x00 */ Vec pos;
    /* 0x0C */ char unk_0C[0x4];
} Duel01SpriteWork; // sizeof 0x10

typedef struct Duel01CamShakeWork {
    /* 0x00 */ s32 magnitude;
    /* 0x04 */ s32 decay;
    /* 0x08 */ char unk_08[0x8];
} Duel01CamShakeWork; // sizeof 0x10

typedef struct Duel01WinColorWork {
    /* 0x00 */ s32 window;
    /* 0x04 */ char unk_04[0xC];
} Duel01WinColorWork; // sizeof 0x10

typedef struct Duel01PartnerAttackWork {
    /* 0x00 */ GW_PLAYER *player;
    /* 0x04 */ Object *obj;
    /* 0x08 */ s32 delay;
    /* 0x0C */ s32 waitTime;
} Duel01PartnerAttackWork; // sizeof 0x10

typedef struct Duel01PartnerRouletteWork {
    /* 0x00 */ s32 player;
    /* 0x04 */ char unk_04[0xC];
} Duel01PartnerRouletteWork; // sizeof 0x10

// Board space indices used when a player picks up a partner.
typedef struct Duel01PartnerSpaces {
    /* 0x00 */ s32 returnSpace;
    /* 0x04 */ s32 startSpace;
    /* 0x08 */ s32 partnerSpace;
} Duel01PartnerSpaces; // sizeof 0xC

typedef struct Duel01SwayWork {
    /* 0x00 */ s32 angle;
    /* 0x04 */ char unk_04[0xC];
} Duel01SwayWork; // sizeof 0x10

extern s16 omovlevtno;
f32 MBDVecAngleGet(Vec *);
s32 func_800E88FC_name_81(void);
// Defined in ovl_81_name with a u8 return, but callers here use the full register without masking.
s32 func_800FD498_name_81(void);
void MBDVecDirGet(Vec *, Vec *, Vec *);
void func_80105CC0_duel01(void); // probably takes object as arg
Process *func_800EBF2C_name_81(Vec *, Vec *, Vec *, s32);
void func_80106308_duel01(void);
void func_80089A20_main(Vec *, s32);
void func_800F38DC_name_81(s32, s32, s32);
void func_8010D9F4_duel01(void);
void func_8010DCA8_duel01(void);
void func_8010DD3C_duel01(void);
void func_8010E348_duel01(void);
void func_8010E954_duel01(s16);
void func_8010EA74_duel01(void);
void func_800FF640_name_81(s32);
void func_8010B130_duel01(omObjData *);
void func_8010E1B4_duel01(void);
void func_8010E7C0_duel01(void);
void func_8010EAD4_duel01(s32);
void func_80110068_duel01(s32);
void func_80118320_duel01(s8 *, s8 *);
void func_80105F20_duel01(void);
void func_80106828_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80107188_duel01(s32, s32, Object *, Object *, s32, s32);
void func_801079B8_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80107EBC_duel01(s32, s32, Object *, Object *, s32, s32);
void func_801084A4_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80108550_duel01(s32, s32, Object *, Object *, s32, s32);
void func_80109888_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010A210_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010B54C_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010BCD4_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010CE68_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010D424_duel01(s32, s32, Object *, Object *, s32, s32);
void func_8010DDEC_duel01(void);
void func_8010E3F8_duel01(void);
void func_8011390C_duel01(void);
s32 func_80118328_duel01(void);
void func_80118414_duel01(void);
void func_800FAC94_name_81(PartnerFunc *, PartnerFunc *);
void func_800EA46C_name_81(event_table_entry *);
void func_800FC5A8_name_81(process_func);
void func_800FC59C_name_81(s32 (*)(void));
void func_800E18C0_name_81(void);
void func_800E1960_name_81(void);
void func_800E1F38_name_81(void);
void func_800E14D8_name_81(s32, s32);
void func_800F7378_name_81(s32, s32);
void func_800FAE18_name_81(Object *, s32, s32);
void func_800FADB4_name_81(void);
Object *func_800EDD50_name_81(Vec *);
void func_800EE0F4_name_81(s32);
void func_800EDF48_name_81(void);
void *func_800FFC2C_name_81(s16, s16, s32);
void func_800EE74C_name_81(s32);
void func_800FFCCC_name_81(void *);
void func_800EDF78_name_81(void);
void func_800EE468_name_81(s32);
void func_800EDDBC_name_81(void);
void func_800F3880_name_81(s32, s32, s32);
extern s32 D_80101200_shared_board[];
Process *func_800E0924_name_81(void);
Process *func_800DCE40_name_81(s32, Vec *, Vec *, f32);
s32 func_8010EB88_duel01(void);
Process *func_800FAB68_name_81(Object *, s32, s32, s32, s32);
void func_8010F12C_duel01(void);
void func_8010EFBC_duel01(void);
void func_800FC8DC_name_81(Object *);
void func_800EB7BC_name_81(Vec *);
Process *func_800EBC60_name_81(Vec *, Vec *, Vec *, s32);
void func_800D6CA0_name_81(UnkEA790Struct *win);
