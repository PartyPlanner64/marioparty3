#include "common.h"
#include "overlays/minigame.h"

// Grid position of a single marker in the "Beat Goes On" note field.
typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
} BeatGoesOnPos; // sizeof 0x4

// Note/scoring state block hanging off omObjData::data for one "Beat Goes On" grid.
typedef struct {
    /* 0x00 */ u8 unk_00[0x16];
    /* 0x16 */ s8 unk_16;
    /* 0x17 */ s8 unk_17;
    /* 0x18 */ s8 unk_18;
    /* 0x19 */ s8 unk_19;
    /* 0x1A */ s8 noteFlags[15];
    /* 0x29 */ u8 unk_29;
    /* 0x2A */ s8 btnB[16];
    /* 0x3A */ s8 btnC[16];
    /* 0x4A */ s8 btnA[16];
} BeatGoesOnNotes; // sizeof 0x5A

extern omObjData *D_8010C4E4_the_beat_goes_on;
extern s8 D_8010C4E9_the_beat_goes_on;

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_801059A0_the_beat_goes_on);

void func_80105C68_the_beat_goes_on(D_80111B50_vine_with_me_Struct *arg0) {
    s32 i;

    arg0->unk00 = 0;
    arg0->unk01 = 0;
    arg0->unk02 = 2;
    arg0->unk03 = 0;
    arg0->unk04 = 0;
    arg0->unk05 = 0;
    arg0->unk06 = 0;
    arg0->unk1C = 64;
    arg0->unk1E = -1;
    arg0->unk20 = 0;
    arg0->unk22 = -1;
    arg0->unk24 = 150;
    for (i = 0; i < 4; i++) {
        arg0->unk08[i] = 0;
        arg0->unk18[i] = 0xFF;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80105CDC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80105E0C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80105F60_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_801060B0_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106204_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106358_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106708_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106BE0_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80106E40_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80107504_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010775C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_801080DC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108198_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108324_the_beat_goes_on);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", D_8010C3B8_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_80108810_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A5FC_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A88C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010A94C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010AD60_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010AF10_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B058_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B0E0_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B17C_the_beat_goes_on);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010B6DC_the_beat_goes_on);

void func_8010C0F4_the_beat_goes_on(BeatGoesOnPos *pos) {
    if (D_8010C4E9_the_beat_goes_on < 8) {
        pos->x = D_8010C4E9_the_beat_goes_on * 30 + 55;
        pos->y = 30;
    } else {
        pos->x = (D_8010C4E9_the_beat_goes_on - 8) * 30 + 55;
        pos->y = 50;
    }
}

void func_8010C14C_the_beat_goes_on(void) {
    BeatGoesOnNotes *notes = (BeatGoesOnNotes *)D_8010C4E4_the_beat_goes_on->data;
    s32 i;

    notes->unk_19 = 0;
    notes->unk_18 = 0;
    notes->unk_17 = 0;
    notes->unk_16 = 0;
    for (i = 0; i < 16; i++) {
        // The note field only has 15 slots, but the button arrays have 16.
        if (i < 15) {
            notes->noteFlags[i] = 0;
        }
        notes->btnB[i] = 0;
        notes->btnC[i] = 0;
        notes->btnA[i] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_20_the_beat_goes_on/1FE4D0", func_8010C1A4_the_beat_goes_on);
