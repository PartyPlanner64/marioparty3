#include "common_duel.h"
#include "ovl_81.h"

RectF D_801014D0_name_81 = { 16.0f, 12.0f, 304.0f, 228.0f };

void func_800F413C_name_81(void);

void func_800F4208_name_81(void);

void func_800F4080_name_81(void) {
    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.y1 = 12.0f;
    D_801014D0_name_81.x2 = 304.0f;
    D_801014D0_name_81.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &D_801014D0_name_81);
}

void func_800F40E4_name_81(void) {
    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.y1 = 12.0f;
    D_801014D0_name_81.x2 = 16.0f;
    D_801014D0_name_81.y2 = 228.0f;
    Hu3DCameraScissorSet(0, &D_801014D0_name_81);
}

void func_800F413C_name_81(void) {
    s32 i;

    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.x2 = 304.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        D_801014D0_name_81.x1 += 32.0f;
        Hu3DCameraScissorSet(0, &D_801014D0_name_81);
    }
    omDelPrcObj(NULL);
}

Process *func_800F41DC_name_81(void) {
    return omAddPrcObj(func_800F413C_name_81, 0x1002, 0, 0);
}

void func_800F4208_name_81(void) {
    s32 i;

    D_801014D0_name_81.x1 = 16.0f;
    D_801014D0_name_81.x2 = 16.0f;

    for (i = 0; i < 9; i++) {
        HuPrcVSleep();
        D_801014D0_name_81.x2 += 32.0f;
        Hu3DCameraScissorSet(0, &D_801014D0_name_81);
    }
    omDelPrcObj(NULL);
}

Process *func_800F429C_name_81(void) {
    return omAddPrcObj(func_800F4208_name_81, 0x1002, 0, 0);
}

s32 func_800F42C8_name_81(void) {
    return D_801014D0_name_81.x2 == 304.0f;
}
