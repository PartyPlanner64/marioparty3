#include "common.h"
#include "overlays/minigame.h"

// Per-object data allocated for each entry of D_80109B00_all_fired_up, stored at omObjData->data
typedef struct {
    /* 0x00 */ char unk00[0x20];
    /* 0x20 */ Vec pos;
} AllFiredUpWork;

extern u8 D_801099C9_all_fired_up;
extern omObjData *D_80109B00_all_fired_up[];
extern s16 D_800EB932_minigame;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801059A0_all_fired_up);

void func_80105C54_all_fired_up(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    D_800EB932_minigame = 0xF;
    arg0->unk00 = 0;
    arg0->unk01 = 5;
    arg0->unk02 = 1;
    arg0->unk03 = 2;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 9;
    arg0->unk1C = 0x5A;
    arg0->unk1E = 0x708;
    arg0->unk20 = -1;
    arg0->unk22 = 0x4B;
    arg0->unk24 = 0x96;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80105CE8_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80105E1C_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80105F5C_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106348_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106584_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801067CC_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801068F8_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106B7C_all_fired_up);

void func_80106C68_all_fired_up(void) {
    AllFiredUpWork *work;
    s32 i;

    for (i = 0; i < (s8)D_801099C9_all_fired_up; i++) {
        work = D_80109B00_all_fired_up[i]->data;
        work->pos.x = D_80109B00_all_fired_up[i]->trans.x;
        work->pos.y = D_80109B00_all_fired_up[i]->trans.y;
        work->pos.z = D_80109B00_all_fired_up[i]->trans.z;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106CDC_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106F04_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80106FAC_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80107440_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80107578_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80107BD4_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80107DA4_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801080C8_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801085A4_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108710_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108958_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80108AA0_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_80109660_all_fired_up);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_29_all_fired_up/23C8F0", func_801097B0_all_fired_up);
