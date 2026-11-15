#include "game/menuflag.h"

static s8 fileSelEnteredF;
static s8 modeSelIntroShownF;

s32 FileSelEnteredGet(void) {
    return fileSelEnteredF;
}

void FileSelEnteredSet(s8 arg0) {
    fileSelEnteredF = arg0;
}

s32 ModeSelIntroShownGet(void) {
    return modeSelIntroShownF;
}

void ModeSelIntroShownSet(s8 arg0) {
    modeSelIntroShownF = arg0;
}
