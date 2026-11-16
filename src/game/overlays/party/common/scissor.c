#include "common_board.h"

RectF mbScissorRect = {
    16.0f, 12.0f, 304.0f, 228.0f
};

void MBScissorFullSet(void) {
    mbScissorRect.x1 = 16.0f;
    mbScissorRect.y1 = 12.0f;
    mbScissorRect.x2 = 304.0f;
    mbScissorRect.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &mbScissorRect);
}

void MBScissorEmptySet(void) {
    mbScissorRect.x1 = 16.0f;
    mbScissorRect.y1 = 12.0f;
    mbScissorRect.x2 = 16.0f;
    mbScissorRect.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &mbScissorRect);
}

static void MBScissorWipeOutProc(void) {
    s32 i;

    mbScissorRect.x1 = 16.0f;
    mbScissorRect.x2 = 304.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        mbScissorRect.x1 += 32.0f;
        Hu3DCameraScissorSet(0, &mbScissorRect);
    }
    omDelPrcObj(NULL);
}

Process *MBScissorWipeOutStart(void) {
    return omAddPrcObj(MBScissorWipeOutProc, 0x1002, 0, 0);
}

static void MBScissorWipeInProc(void) {
    s32 i;

    mbScissorRect.x1 = 16.0f;
    mbScissorRect.x2 = 16.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        mbScissorRect.x2 += 32.0f;
        Hu3DCameraScissorSet(0, &mbScissorRect);
    }

    omDelPrcObj(NULL);
}

Process *MBScissorWipeInStart(void) {
    return omAddPrcObj(MBScissorWipeInProc, 0x1002, 0, 0);
}

