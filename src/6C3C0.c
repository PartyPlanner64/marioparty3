#include "common.h"
#include "PR/sndp.h"

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006B7C0_main);

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006BA3C_main);

ALParam *func_8006BBBC_main(void) {
    AudioManager *manager = D_800A2884_main;
    ALParam *param = NULL;

    if (manager->freeParamList != NULL) {
        param = manager->freeParamList;
        manager->freeParamList = param->next;
        param->next = NULL;
    }

    return param;
}

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006BBE8_main);

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006BC00_main);

void func_8006BC60_main(ALLink *link) {
    alUnlink(link);
    alLink(link, &D_800A2884_main->pLameList);
}

s32 func_8006BC98_main(s32 duration) {
    f32 samples = ((f32)duration * D_800A2884_main->rate) / 1000000.0 + 0.5;
    return (s32)samples;
}

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006BCE8_main);

INCLUDE_ASM("asm/nonmatchings/6C3C0", func_8006BD3C_main);
