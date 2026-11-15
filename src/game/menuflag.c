#include "game/menuflag.h"

static s8 D_800B23B0_main;
static s8 D_800B23B1_main;

s32 FileSelEnteredGet(void) {
    return D_800B23B0_main;
}

void FileSelEnteredSet(s8 arg0) {
    D_800B23B0_main = arg0;
}

s32 ModeSelIntroShownGet(void) {
    return D_800B23B1_main;
}

void ModeSelIntroShownSet(s8 arg0) {
    D_800B23B1_main = arg0;
}
