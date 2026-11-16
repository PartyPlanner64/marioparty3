#include "common_duel.h"
#include "ovl_81.h"

RectF mbdScissorRect = { 16.0f, 12.0f, 304.0f, 228.0f };

void MBDScissorWipeOutProc(void);

void MBDScissorWipeInProc(void);

void MBDScissorFullSet(void) {
    mbdScissorRect.x1 = 16.0f;
    mbdScissorRect.y1 = 12.0f;
    mbdScissorRect.x2 = 304.0f;
    mbdScissorRect.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &mbdScissorRect);
}

void MBDScissorEmptySet(void) {
    mbdScissorRect.x1 = 16.0f;
    mbdScissorRect.y1 = 12.0f;
    mbdScissorRect.x2 = 16.0f;
    mbdScissorRect.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &mbdScissorRect);
}

void MBDScissorWipeOutProc(void) {
    s32 i;

    mbdScissorRect.x1 = 16.0f;
    mbdScissorRect.x2 = 304.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        mbdScissorRect.x1 += 32.0f;
        Hu3DCameraScissorSet(0, &mbdScissorRect);
    }
    omDelPrcObj(NULL);
}

Process *MBDScissorWipeOutStart(void) {
    return omAddPrcObj(MBDScissorWipeOutProc, 0x1002, 0, 0);
}

void MBDScissorWipeInProc(void) {
    s32 i;

    mbdScissorRect.x1 = 16.0f;
    mbdScissorRect.x2 = 16.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        mbdScissorRect.x2 += 32.0f;
        Hu3DCameraScissorSet(0, &mbdScissorRect);
    }
    omDelPrcObj(NULL);
}

Process *MBDScissorWipeInStart(void) {
    return omAddPrcObj(MBDScissorWipeInProc, 0x1002, 0, 0);
}

s32 MBDScissorFullCheck(void) {
    return mbdScissorRect.x2 == 304.0f;
}
