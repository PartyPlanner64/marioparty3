#include "common.h"
#include "PR/sndp.h"

void func_8006F870_main(ALPlayer *player) {
    OSIntMask mask = osSetIntMask(OS_IM_NONE);
    AudioManager *manager = D_800A2884_main;

    player->samplesLeft = manager->lastSamples;
    player->next = manager->head;
    manager->head = player;

    osSetIntMask(mask);
}

INCLUDE_ASM("asm/nonmatchings/70470", func_8006F8BC_main);

INCLUDE_ASM("asm/nonmatchings/70470", func_8006F914_main);

INCLUDE_ASM("asm/nonmatchings/70470", func_8006F980_main);

INCLUDE_ASM("asm/nonmatchings/70470", func_8006F9D0_main);

INCLUDE_ASM("asm/nonmatchings/70470", func_8006FAE8_main);
