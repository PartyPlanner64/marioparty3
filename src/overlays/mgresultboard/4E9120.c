#include "common.h"
#include "overlays/mgresultboard.h"

extern UnkTemp D_8010AEA8_mgresultboard[5][5];
extern UnkTemp D_8010AFE8_mgresultboard[];
extern PlayerResult D_8010B048_mgresultboard[4];

s32 func_801081F0_mgresultboard(omObjData *, s8, s8, s8);
void func_80108330_mgresultboard(omObjData *);
s32 func_80109744_mgresultboard(s32, s8, s16);
s32 func_80109DAC_mgresultboard(s32, s8, s16);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80107D00_mgresultboard);

void func_801080C4_mgresultboard(void) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AFE8_mgresultboard[i].unk_00 = 0;
        D_8010AFE8_mgresultboard[i].unk_02 = 0;
        D_8010AFE8_mgresultboard[i].unk_04 = -1;
        D_8010AFE8_mgresultboard[i].unk_06 = i;
        D_8010AFE8_mgresultboard[i].unk_08 = i + 4;
        D_8010AFE8_mgresultboard[i].unk_0A = 0;
    }
}

void func_80108150_mgresultboard(omObjData *arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_801081F0_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].unk_02, D_8010B048_mgresultboard[i].unk_03);
    }
}

void func_801081CC_mgresultboard(omObjData *arg0) {
    func_80108330_mgresultboard(arg0);
}

void func_801081E8_mgresultboard(void) {
}

s32 func_801081F0_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    D_8010AFE8_mgresultboard[arg1].unk_02 = arg2 * 3 + arg3;
    D_8010AFE8_mgresultboard[arg1].unk_04 = -1;
    D_8010AFE8_mgresultboard[arg1].unk_00 = 0;
    return 1;
}

s32 func_80108250_mgresultboard(omObjData *arg0, s8 arg1, s8 arg2, s8 arg3) {
    if (D_8010AFE8_mgresultboard[arg1].unk_04 >= 0) {
        return 0;
    }
    D_8010AFE8_mgresultboard[arg1].unk_04 = arg2 * 3 + arg3;
    if (D_8010AFE8_mgresultboard[arg1].unk_08 >= 0) {
        func_8001C258_main(arg0->model[D_8010AFE8_mgresultboard[arg1].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
    }
    D_8010AFE8_mgresultboard[arg1].unk_00 = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108330_mgresultboard);

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108700_mgresultboard);

void func_80108BBC_mgresultboard(void) {
}

void func_80108BC4_mgresultboard(s32 arg0) {
    s8 i;

    for (i = 0; i < 4; i++) {
        func_80109744_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].score);
        func_80109DAC_mgresultboard(arg0, i, D_8010B048_mgresultboard[i].coin);
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/mgresultboard/4E9120", func_80108C60_mgresultboard);

void func_8010913C_mgresultboard(void) {
}

void func_80109144_mgresultboard(void) {
    static const s16 D_8010AD58_mgresultboard[4][5] = {
        { 0, 1, 8, 9, 10 },
        { 2, 3, 11, 12, 13 },
        { 4, 5, 14, 15, 16 },
        { 6, 7, 17, 18, 19 },
    };
    s8 i;
    s8 j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            D_8010AEA8_mgresultboard[i][j].unk_00 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_02 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_04 = -1;
            D_8010AEA8_mgresultboard[i][j].unk_06 = D_8010AD58_mgresultboard[i][j];
            D_8010AEA8_mgresultboard[i][j].unk_08 = D_8010AD58_mgresultboard[i][j] + 20;
            D_8010AEA8_mgresultboard[i][j].unk_0A = 0;
        }
        for (; j < 5; j++) {
            D_8010AEA8_mgresultboard[i][j].unk_00 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_02 = 0;
            D_8010AEA8_mgresultboard[i][j].unk_04 = -1;
            D_8010AEA8_mgresultboard[i][j].unk_06 = D_8010AD58_mgresultboard[i][j];
            D_8010AEA8_mgresultboard[i][j].unk_08 = D_8010AD58_mgresultboard[i][j] + 20;
            D_8010AEA8_mgresultboard[i][j].unk_0A = 0;
        }
    }
}

s32 func_801092E0_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = digits[i];
        if (D_8010AEA8_mgresultboard[arg1][i].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109498_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 10;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = digits[i];
        if (D_8010AEA8_mgresultboard[arg1][i].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109650_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][0].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 func_801096E0_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 1;
    }
    return 1;
}

s32 func_80109744_mgresultboard(s32 arg0, s8 arg1, s16 arg2) {
    s16 digits[2];
    s16 value;
    s8 i;

    if (arg2 >= 100) {
        arg2 = 99;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 10) % 10;
    digits[1] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 2; i++) {
        D_8010AEA8_mgresultboard[arg1][i].unk_02 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i].unk_04 = -1;
        D_8010AEA8_mgresultboard[arg1][i].unk_00 = 0;
    }
    return 1;
}

s32 func_80109878_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_0A = 0;
    }
    return 1;
}

s32 func_80109A90_mgresultboard(omObjData *arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
        return 0;
    }
    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 10;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
        if (D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 >= 0) {
            func_8001C258_main(arg0->model[D_8010AEA8_mgresultboard[arg1][i + 2].unk_08 + 1], HU3D_ATTR_DISPOFF, HU3D_ATTR_NONE);
        }
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_0A = 1;
    }
    return 1;
}

s32 func_80109CB0_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    if (D_8010AEA8_mgresultboard[arg1][2].unk_04 >= 0) {
        return 0;
    }

    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

s32 func_80109D44_mgresultboard(s32 arg0, s8 arg1) {
    s8 i;

    for (i = 0; i < 4; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 1;
    }
    return 1;
}

s32 func_80109DAC_mgresultboard(s32 arg0, s8 arg1, s16 arg2) {
    s16 digits[3];
    s16 value;
    s8 i;

    if (arg2 >= 1000) {
        arg2 = 999;
    }
    value = (arg2 < 0) ? 0 : arg2;
    digits[0] = (value / 100) % 10;
    digits[1] = (value / 10) % 10;
    digits[2] = value % 10;
    if (digits[0] == 0) {
        digits[0] = 11;
    }
    for (i = 0; i < 3; i++) {
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_02 = digits[i];
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_04 = -1;
        D_8010AEA8_mgresultboard[arg1][i + 2].unk_00 = 0;
    }
    return 1;
}

void func_80109F30_mgresultboard(s16 model, s16 anim, s16 animIdx) {
    if (anim >= 0) {
        if (animIdx == -1) {
            func_80033910_main(HmfModelData[model].hmf);
        } else {
            HmfAnim *entry;

            func_80033970_main(HmfModelData[model].hmf);
            entry = &D_800D1714_main[anim];

            entry->animIdx = animIdx;
        }
    }
}
