#include "common.h"
#include "malloc.h"
#include "../ovl_80_shared_board/FA250.h"
#include "../ovl_80_shared_board/105D50.h"
#include "../ovl_80_shared_board/106A50.h"
#include "../ovl_80_shared_board/F5E80.h"

typedef struct {
    /* 0x00 */ s16 spriteGroup;
    /* 0x02 */ s16 sprites[3];
} W10SprGroup; // sizeof 0x08

extern s16 D_8010BA4C_w10;
extern s16 D_8010BA4E_w10;
extern s16 D_8010BA54_w10;

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801059D0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105A0C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105AB8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105B70_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105B90_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105C28_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105C48_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105D6C_w10);

void func_80105DC4_w10(void) {
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    HuPrcVSleep();
    HuPrcSleep(3);
}

void func_80105E08_w10(void) {
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105E10_w10);

void func_80105F20_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBPlayerGet(i)->stat |= PLAYER_IS_CPU;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105F64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105FA0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80105FDC_w10);

void func_801061E8_w10(W10SprGroup *arg0) {
    HuSprKill(arg0->sprites[0]);
    HuSprKill(arg0->sprites[1]);
    HuSprKill(arg0->sprites[2]);
    HuSprGrpKill(arg0->spriteGroup);
    HuMemMemoryFreeTemp(arg0);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106230_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106314_w10);

void func_8010649C_w10(void) {
    HuSprKill(D_8010BA4E_w10);
    HuSprGrpKill(D_8010BA4C_w10);
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801064C8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106574_w10);

void func_80106670_w10(s16 arg0) {
    D_8010BA54_w10 = arg0;
    MBCameraSpeedSet(4.0f);
}

void func_8010669C_w10(void) {
    HuPrcSleep(3);
    while (MBCameraStopCheck() != 0) {
        HuPrcVSleep();
    }
    MBCameraSpeedSet(-1.0f);
}

void func_801066E8_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        GW_PLAYER *player = MBPlayerGet(i);
        player->color = 0;
        player->stat &= ~2;
    }
}

void func_80106730_w10(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        MBStatusColorSet(i, MBPlayerGet(i)->color);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106774_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010681C_w10);

void func_80106838_w10(void) {
    HuPrcChildLink(HuPrcCurrentGet(), MBTelopCreate(GwSystem.current_player_index));
    HuPrcChildWait();
}

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010687C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106908_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106DEC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106ED8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F40_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106F7C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80106FE0_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107028_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801070B8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010714C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107228_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107344_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107350_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801073C8_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107780_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107ABC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107D64_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80107F0C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_801084CC_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80108F28_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109050_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_80109444_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010AF68_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B12C_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B434_w10);

INCLUDE_ASM("asm/nonmatchings/overlays/w10/3B3620", func_8010B5A4_w10);
