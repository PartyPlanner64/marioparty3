#include "common.h"
#include "overlays/mgresultboard.h"

extern UnkTemp D_8010AFB0_mgresultboard[];
extern PlayerResult D_8010B048_mgresultboard[4];

s32 func_8010A454_mgresultboard(omObjData *, s8, s8);
void func_8010A4A0_mgresultboard(omObjData *);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A000_mgresultboard);

void func_8010A334_mgresultboard(omObjData *arg0) {
    func_8010A4A0_mgresultboard(arg0);
}

void func_8010A350_mgresultboard(void) {
}

void func_8010A358_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFB0_mgresultboard[i].unk_00 = 0;
        D_8010AFB0_mgresultboard[i].unk_02 = 0;
        D_8010AFB0_mgresultboard[i].unk_04 = -1;
        D_8010AFB0_mgresultboard[i].unk_06 = i;
        D_8010AFB0_mgresultboard[i].unk_08 = i + 4;
        D_8010AFB0_mgresultboard[i].unk_0A = 0;
    }
}

void func_8010A3E4_mgresultboard(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_8010A454_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].unk_01);
    }
}

s32 func_8010A454_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2) {
    D_8010AFB0_mgresultboard[arg1].unk_02 = arg2;
    D_8010AFB0_mgresultboard[arg1].unk_04 = -1;
    D_8010AFB0_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4EB420", func_8010A4A0_mgresultboard);

s32 func_8010A864_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2) {
    if (D_8010AFB0_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }

    D_8010AFB0_mgresultboard[arg1].unk_04 = arg2;

    if (D_8010AFB0_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(arg0->model[D_8010AFB0_mgresultboard[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }

    D_8010AFB0_mgresultboard[arg1].unk_00 = 1;
    return 1;
}
