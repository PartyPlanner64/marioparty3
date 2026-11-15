#include "game/aura.h"
#include "game/hmfdraw.h"
#include "game/hu3d.h"
#include "game/mallocblock.h"
#include "game/object.h"
#include "game/process.h"
#include "humath.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
} AuraPrcData; // Size 6

static u8 D_800A1640_main[][4] = {
    { 255, 0, 0, 0 },
    { 255, 160, 40, 0 },
    { 255, 255, 0, 0 },
    { 160, 255, 50, 0 },
    { 0, 255, 0, 0 },
    { 0, 255, 255, 0 },
    { 50, 50, 255, 0 },
    { 150, 60, 255, 0 },
};

extern u8 D_800D2008_main;

static f32 D_800B23A0_main;
static f32 D_800B23A4_main;
static f32 D_800B23A8_main;

void func_80046030_main(s16 arg0, s16 arg1) {
    HmfData *temp_s0 = Hu3DData[arg0].hmf;
    HmfModelData_Unk64_Unk60_Unk54_Struct *var_a0;
    Process *temp_v0_4;
    AuraPrcData *temp_v0_5;
    s16 temp_v0;
    s16 temp_v1;
    s16 var_a1;

    temp_v0 = func_8002C834_main(temp_s0, "aura");
    temp_v1 = temp_s0->unk60[temp_v0].unk22;
    var_a0 = temp_s0->unk60[temp_v0].unk54;
    for (var_a1 = 0; var_a1 < temp_v1; var_a1++, var_a0++) {
        var_a0->unk00 |= 0x80;
    }
    Hu3DModelRemakeStatic(arg0);
    func_8001C514_main(arg0);
    func_8001C954_main(arg0);
    temp_v0_4 = omAddPrcObj(func_800461D8_main, 0x3F00, 0x1000, 0);
    omPrcSetStatBit(temp_v0_4, OM_STAT_NOPAUSE | OM_STAT_NOALLPAUSE);
    temp_v0_4->user_data = temp_v0_5 = HuMemAllocTag(sizeof(AuraPrcData), TAG_OVERLAY);
    temp_v0_5->unk00 = arg0;
    temp_v0_5->unk02 = temp_v0;
    temp_v0_5->unk04 = arg1;
    Hu3DData[arg0].unkBC = (void *)temp_v0_4; // TODO: is unkBC just a void* data?
    D_800B23A0_main = D_800B23A4_main = D_800B23A8_main = 1.0f;
}

void func_800461B4_main(s16 arg0) {
    func_80046030_main(arg0, 5);
}

// TODO: doesn't work with -Wa,--vr4300mul-off.
void func_800461D8_main(void) {
    s32 var_s1 = 0;
    AuraPrcData *temp_s4 = HuPrcCurrentGet()->user_data;
    HmfData *temp_s6 = Hu3DData[temp_s4->unk00].hmf;
    s16 temp_v0_2 = temp_s6->unk60[temp_s4->unk02].unk2A;
    s16 temp_v1_0 = temp_s6->unk60[temp_s4->unk02].unk28;

    while (TRUE) {
        Vtx *var_s0 = &temp_s6->unk44[D_800D2008_main][temp_v1_0];
        s16 var_s2;

        for (var_s2 = 0; var_s2 < temp_v0_2; var_s2++, var_s0++) {
            f32 temp_f12 = var_s0->v.ob[0];
            f32 temp_f0 = var_s0->v.ob[1];
            f32 temp_f2 = var_s0->v.ob[2];
            f32 temp_f0_2 = HuSqrtf(temp_f12 * temp_f12 + temp_f0 * temp_f0 + temp_f2 * temp_f2) + var_s1;
            f32 temp_f32 = (s16)temp_f0_2;
            f32 temp_f6 = ((s16)temp_f0_2 % 30) / 30.0f;
            s16 temp_v0_4 = (s16)(temp_f32 / 30.0f) % 8;
            s32 var_a1 = D_800A1640_main[temp_v0_4][0];
            s32 var_a2 = D_800A1640_main[temp_v0_4][1];
            s32 var_a3 = D_800A1640_main[temp_v0_4][2];
            s16 temp_v1 = (temp_v0_4 + 1) % 8;

            var_s0->v.cn[0] = (s32)((D_800A1640_main[temp_v1][0] * temp_f6 + (1.0f - temp_f6) * var_a1) * D_800B23A0_main);
            var_s0->v.cn[1] = (s32)((D_800A1640_main[temp_v1][1] * temp_f6 + (1.0f - temp_f6) * var_a2) * D_800B23A4_main);
            var_s0->v.cn[2] = (s32)((D_800A1640_main[temp_v1][2] * temp_f6 + (1.0f - temp_f6) * var_a3) * D_800B23A8_main);
        }
        var_s1 += temp_s4->unk04;
        if (var_s1 > 240) {
            var_s1 -= 240;
        } else if (var_s1 < 0) {
            var_s1 += 240;
        }
        HuPrcVSleep();
    }
}

void func_80046558_main(s16 arg0) {
    Process *temp_s0 = (void *)Hu3DData[arg0].unkBC; // TODO

    HuMemFree(temp_s0->user_data);
    omDelPrcObj(temp_s0);
}

void func_800465A8_main(s32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    D_800B23A0_main = arg1;
    D_800B23A4_main = arg2;
    D_800B23A8_main = arg3;
}
