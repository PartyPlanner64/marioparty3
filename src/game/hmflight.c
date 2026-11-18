#include "game/hmflight.h"
#include "game/camera.h"
#include "game/hu3d.h"
#include "game/mallocblock.h"

extern HuCamMtxs *Hu3DCurCamMtx;

extern Light *Hu3DLightP;
extern s16 Hu3DHiliteLightNo;
extern UnkLightData *Hu3DLightData;
extern u8 Hu3DBufNo;

void Hu3DLighInit(void) {
    s16 var_a1;

    if (Hu3DLightData == NULL) {
        Hu3DLightData = HuMemAlloc(sizeof(UnkLightData));
    }
    for (var_a1 = 0; var_a1 < 8; var_a1++) {
        Hu3DLightData->unk02[var_a1].stat = 0;
        Hu3DLightData->unk02[var_a1].r =
            Hu3DLightData->unk02[var_a1].g =
                Hu3DLightData->unk02[var_a1].b = 0x40;
        Hu3DLightData->unk02[var_a1].unk04 =
            Hu3DLightData->unk02[var_a1].unk05 = 0;
        Hu3DLightData->unk02[var_a1].unk06 = 100;
    }
    Hu3DLightData->unk00 = 1;
    Hu3DLightModeSet(1);
}

void Hu3DLightClose(void) {
}

void Hu3DLightExec(s16 arg0) {
    s16 var_s1;

    Hu3DLightP = Hu3DLightData->unk40[Hu3DBufNo][arg0];
    for (var_s1 = 0; var_s1 < Hu3DLightData->unk00 + 1; var_s1++) {
        Light *temp_s0 = &Hu3DLightP[var_s1];

        temp_s0->l.col[0] = temp_s0->l.colc[0] = Hu3DLightData->unk02[var_s1].r;
        temp_s0->l.col[1] = temp_s0->l.colc[1] = Hu3DLightData->unk02[var_s1].g;
        temp_s0->l.col[2] = temp_s0->l.colc[2] = Hu3DLightData->unk02[var_s1].b;
        if (Hu3DLightData->unk02[var_s1].stat & 1) {
            f32 sp10[4][4];
            f32 temp_f24 = Hu3DLightData->unk02[var_s1].unk04;
            f32 temp_f26 = Hu3DLightData->unk02[var_s1].unk05;
            f32 temp_f28 = Hu3DLightData->unk02[var_s1].unk06;
            f32 temp_f22;
            f32 temp_f20;
            f32 temp_f24_2;
            f32 temp_f0;

            guMtxL2F(sp10, &Hu3DCurCamMtx->lookAtMtx);
            temp_f22 = temp_f24 * sp10[0][0] + temp_f26 * sp10[1][0] + temp_f28 * sp10[2][0];
            temp_f20 = temp_f24 * sp10[0][1] + temp_f26 * sp10[1][1] + temp_f28 * sp10[2][1];
            temp_f24_2 = temp_f24 * sp10[0][2] + temp_f26 * sp10[1][2] + temp_f28 * sp10[2][2];
            temp_f0 = temp_f22 * temp_f22 + temp_f20 * temp_f20 + temp_f24_2 * temp_f24_2;
            temp_f0 = HuSqrtf(temp_f0);
            temp_s0->l.dir[0] = (temp_f22 / temp_f0) * 120.0f;
            temp_s0->l.dir[1] = (temp_f20 / temp_f0) * 120.0f;
            temp_s0->l.dir[2] = (temp_f24_2 / temp_f0) * 120.0f;
        } else {
            temp_s0->l.dir[0] = Hu3DLightData->unk02[var_s1].unk04;
            temp_s0->l.dir[1] = Hu3DLightData->unk02[var_s1].unk05;
            temp_s0->l.dir[2] = Hu3DLightData->unk02[var_s1].unk06;
        }
    }
}

void Hu3DLightReset(void) {
    s16 var_a3;

    Hu3DLightP = Hu3DLightData->unk40[Hu3DBufNo][0];
    for (var_a3 = 0; var_a3 < Hu3DLightData->unk00 + 1; var_a3++) {
        Hu3DLightP[var_a3].l.col[0] = Hu3DLightP[var_a3].l.colc[0] = Hu3DLightData->unk02[var_a3].r;
        Hu3DLightP[var_a3].l.col[1] = Hu3DLightP[var_a3].l.colc[1] = Hu3DLightData->unk02[var_a3].g;
        Hu3DLightP[var_a3].l.col[2] = Hu3DLightP[var_a3].l.colc[2] = Hu3DLightData->unk02[var_a3].b;
    }
}

void Hu3DGLightMaxSet(s16 arg0) {
    if (arg0 >= 8) {
        arg0 = 7;
    }
    Hu3DLightData->unk00 = arg0;
}

void Hu3DGLightStatSet(s16 arg0, u8 arg1, u8 arg2) {
    if (Hu3DLightData->unk00 >= arg0) {
        Hu3DLightData->unk02[arg0].stat &= ~arg1;
        Hu3DLightData->unk02[arg0].stat |= arg2;
    }
}

void Hu3DGLightColorSet(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    if (Hu3DLightData->unk00 >= arg0) {
        Hu3DLightData->unk02[arg0].r = arg1;
        Hu3DLightData->unk02[arg0].g = arg2;
        Hu3DLightData->unk02[arg0].b = arg3;
    }
}

void Hu3DGLightDirSet(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (Hu3DLightData->unk00 >= arg0) {
        f32 temp_f0 = arg1 * arg1 + arg2 * arg2 + arg3 * arg3;

        temp_f0 = HuSqrtf(temp_f0);
        Hu3DLightData->unk02[arg0].unk04 = (arg1 / temp_f0) * 120.0f;
        Hu3DLightData->unk02[arg0].unk05 = (arg2 / temp_f0) * 120.0f;
        Hu3DLightData->unk02[arg0].unk06 = (arg3 / temp_f0) * 120.0f;
    }
}

void Hu3DLLightSet(HmfData_UnkD0 *arg0) {
    Light *temp_s0 = &arg0->unk08[Hu3DBufNo];

    temp_s0->l.col[0] = temp_s0->l.colc[0] = arg0->unk00;
    temp_s0->l.col[1] = temp_s0->l.colc[1] = arg0->unk01;
    temp_s0->l.col[2] = temp_s0->l.colc[2] = arg0->unk02;
    if (arg0->unk03 & 1) {
        f32 sp10[4][4];
        f32 temp_f22 = arg0->unk04;
        f32 temp_f26 = arg0->unk05;
        f32 temp_f28 = arg0->unk06;
        f32 temp_f24;
        f32 temp_f20;
        f32 temp_f22_2;
        f32 temp_f0;

        guMtxL2F(sp10, &Hu3DCurCamMtx->lookAtMtx);
        temp_f24 = temp_f22 * sp10[0][0] + temp_f26 * sp10[1][0] + temp_f28 * sp10[2][0];
        temp_f20 = temp_f22 * sp10[0][1] + temp_f26 * sp10[1][1] + temp_f28 * sp10[2][1];
        temp_f22_2 = temp_f22 * sp10[0][2] + temp_f26 * sp10[1][2] + temp_f28 * sp10[2][2];
        temp_f0 = temp_f24 * temp_f24 + temp_f20 * temp_f20 + temp_f22_2 * temp_f22_2;
        temp_f0 = HuSqrtf(temp_f0);
        temp_s0->l.dir[0] = (temp_f24 / temp_f0) * 120.0f;
        temp_s0->l.dir[1] = (temp_f20 / temp_f0) * 120.0f;
        temp_s0->l.dir[2] = (temp_f22_2 / temp_f0) * 120.0f;
    } else {
        temp_s0->l.dir[0] = arg0->unk04;
        temp_s0->l.dir[1] = arg0->unk05;
        temp_s0->l.dir[2] = arg0->unk06;
    }
}

s16 Hu3DModelLightInfoSet(s16 arg0, s16 arg1) {
    HmfData *temp_v0_2 = Hu3DData[arg0].hmf;
    UnkLightData_unk02 *temp_s5 = temp_v0_2->unkC0;
    s16 temp_v0 = temp_v0_2->unk20;
    s16 var_s2;

    for (var_s2 = 0; var_s2 < temp_v0; var_s2++) {
        Hu3DGLightColorSet(arg1 + var_s2, temp_s5[var_s2].r, temp_s5[var_s2].g, temp_s5[var_s2].b);
        Hu3DGLightDirSet(arg1 + var_s2, temp_s5[var_s2].unk04, temp_s5[var_s2].unk05, temp_s5[var_s2].unk06);
        Hu3DGLightStatSet(arg1 + var_s2, 1, temp_s5[var_s2].stat);
    }
    return temp_v0;
}

void Hu3DLightModeSet(s16 arg0) {
    Hu3DHiliteLightNo = arg0;
}
