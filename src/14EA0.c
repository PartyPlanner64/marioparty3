#include "common.h"

extern u8 D_800A0620_main;
extern s16 D_800A06FC_main[];
extern s32 D_800A0728_main[8];
extern u16 D_800A0748_main[172];
extern s32 *D_800CC080_main[8];
extern s32 *D_800CDD54_main;
extern u8 D_800D2008_main;
extern s32 *D_800D1F30_main;
extern u8 D_800D20B8_main[16][3];

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800142A0_main);

void func_800143F0_main(void) {
    if (D_800A0620_main) {
        s32 playerIdx = D_800D2008_main;

        D_800CDD54_main = D_800CC080_main[playerIdx];
        D_800D1F30_main = ((s32 *const *)&D_800D1360)[playerIdx];
    }
}

INCLUDE_ASM("asm/nonmatchings/14EA0", HmfSprModelCreate);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014618_main);

void func_800146DC_main(s16 arg0, u16 arg1, u16 arg2) {
    HmfModelEntry *entry = &D_800CBB60_main[arg0];
    entry->flags = (entry->flags & ~arg1) | arg2;
}

void func_80014714_main(s16 arg0, s16 arg1) {
    D_800CBB60_main[arg0].nodeIdx = arg1;
}

void func_8001473C_main(s16 arg0, s16 arg1) {
    D_800CBB60_main[arg0].pointIdx = arg1;
    D_800CBB60_main[arg0].nodeIdx = 0;
    D_800CBB60_main[arg0].unk_08 = 0;
}

u16 func_8001476C_main(s16 arg0) {
    return D_800CBB60_main[arg0].nodeIdx;
}

void func_80014794_main(s16 arg0, s16 arg1) {
    if (arg0 != -1) {
        s32 visible;

        D_800CBB60_main[arg0].unk_12 = arg1;
        visible = (u8)arg1 != 0xFF ? 0x10000 : 0;
        func_8001C2FC_main(D_800CBB60_main[arg0].modelId, 0x10000, visible);
    }
}

void func_800147FC_main(s16 arg0, u8 arg1, u8 arg2, u8 arg3) {
    if (arg0 != -1) {
        D_800CBB60_main[arg0].colorR = arg1;
        D_800CBB60_main[arg0].colorG = arg2;
        D_800CBB60_main[arg0].colorB = arg3;
    }
}

void func_80014850_main(s16 arg0) {
    HmfModelEntry *entry = &D_800CBB60_main[arg0];

    entry->unk_0A = 0;
    entry->nodeIdx = 0;
    entry->flags &= 0xFF7F;
    func_8001C258_main(entry->modelId, 4, 0);
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800148A8_main);

void func_800149D0_main(s16 arg0, u8 *arg1) {
    if (arg0 != -1) {
        func_800146DC_main(arg0, 0x40, 0x40);
        D_800CBB60_main[arg0].unk_20 = arg1;
        D_800CBB60_main[arg0].unk_0E = 0;
        D_800CBB60_main[arg0].unk_0C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80014A3C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016638_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800166D0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016784_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800168A8_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800169E0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016B00_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016C2C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80016FB4_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017128_main);

void func_80017320_main(HmfModelSet *set) {
    HuMemMemoryFreePerm(set->unk_08);
    HuMemMemoryFreePerm(set->unk_04);
    HuMemMemoryFreePerm(set);
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017358_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001766C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017790_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017954_main);

void func_80017A84_main(s16 arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    HmfAnim *anim = &D_800D1714_main[D_800D20B8_main[arg2][arg1]];

    anim->frame = arg3;
    anim->interp = arg4;
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017AD8_main);

void func_80017B20_main(s16 arg0, s16 arg1, u8 arg2, u8 arg3) {
    func_80032FC0_main(D_800D20B8_main[arg1][arg0], arg2, arg3);
}

s32 func_80017B6C_main(s16 chr, s16 arg1, s16 arg2) {
    return func_80017BB8_main(chr, D_800A06FC_main[arg2 * 3 + arg1]);
}

s32 func_80017BB8_main(s16 chr, s16 animId) {
    if (chr == 7) {
        u16 packed = D_800A0748_main[animId];
        return ((packed & 0xFF00) << 8) | (packed & 0xFF);
    }
    return D_800A0728_main[chr] | animId;
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017C10_main);

void func_80017CD0_main(HuMtx4F mtx, f32 x, f32 y, f32 z) {
    s32 i;

    for (i = 0; i < 3; i++) {
        mtx[0][i] *= x;
        mtx[1][i] *= y;
        mtx[2][i] *= z;
    }
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80017D24_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018044_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800183A0_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018544_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_800185A4_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_8001866C_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018978_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018ACC_main);

f32 func_80018D68_main(f32 mtx[3][3]) {
    f32 m10 = mtx[1][0], m11 = mtx[1][1], m12 = mtx[1][2];
    f32 m20 = mtx[2][0], m21 = mtx[2][1], m22 = mtx[2][2];

    return mtx[0][0] * (m11 * m22 - m12 * m21) +
           mtx[0][1] * (m12 * m20 - m10 * m22) +
           mtx[0][2] * (m10 * m21 - m11 * m20);
}

void func_80018DD8_main(f32 arg0[4][4], s32 arg1, s32 arg2, f32 arg3[3][3]) {
    s32 i, j, k, l;

    k = 0;
    for (i = 0; i < 4; i++) {
        if (i != arg1) {
            l = 0;
            for (j = 0; j < 4; j++) {
                if (j != arg2) {
                    arg3[k][l] = arg0[i][j];
                    l++;
                }
            }
            k++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E50_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018E74_main);

INCLUDE_ASM("asm/nonmatchings/14EA0", func_80018F18_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6A98_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AA4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AB0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6ABC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AC8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AD4_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AE0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AEC_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6AF8_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B04_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B10_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B1C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B28_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B34_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B40_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B4C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B58_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B64_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B70_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B7C_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B88_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6B94_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BA0_main);

INCLUDE_RODATA("asm/nonmatchings/14EA0", D_800A6BAC_main);
