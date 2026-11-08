#include "common.h"
#include "game/mallocblock.h"

// Work area allocated by func_8010BD30 (HuMemAllocTag 0x4C bytes) and stored at
// the process object's user_data (offset 0x8C). Total size is 0x4C; fields are
// added as functions are decompiled.
typedef struct BoardResultWork {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ s16 unk_04;
    /* 0x06 */ s16 unk_06;
    /* 0x08 */ s16 unk_08;
    /* 0x0A */ s16 unk_0A;
    /* 0x0C */ Vec unk_0C;
    /* 0x18 */ Vec pos;
    /* 0x24 */ char unk_24[0x28];
} BoardResultWork; // sizeof 0x4C

void func_8010BE14_boardresult(void); /* extern */
void func_8010DA30_boardresult(void); /* extern */

BoardResultWork *func_8010BD30_boardresult(s32 arg0) {
    Process *proc = omAddPrcObj(func_8010BE14_boardresult, 0x3F00, 0x2000, 0);
    BoardResultWork *work = proc->user_data = HuMemAllocTag(sizeof(BoardResultWork), TAG_OVERLAY);

    work->unk_06 = 60;
    work->unk_0A = 60;
    work->unk_0C.x = 0.0f;
    work->unk_0C.y = 500.0f;
    work->unk_0C.z = 0.0f;
    work->pos.x = 0.0f;
    work->pos.y = 0.0f;
    work->pos.z = 0.0f;
    work->unk_00 = arg0;
    work->unk_04 = 0;
    return work;
}

void func_8010BDBC_boardresult(BoardResultWork *arg0, s32 arg1) {
    arg0->unk_00 = arg1;
}

void func_8010BDC4_boardresult(BoardResultWork *arg0, f32 x, f32 y, f32 z) {
    arg0->unk_0C.x = x;
    arg0->unk_0C.y = y;
    arg0->unk_0C.z = z;
}

void func_8010BDD4_boardresult(BoardResultWork *arg0, f32 x, f32 y, f32 z) {
    arg0->pos.x = x;
    arg0->pos.y = y;
    arg0->pos.z = z;
}

void func_8010BDE4_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_0A = arg1;
}

void func_8010BDEC_boardresult(BoardResultWork *arg0, s32 mask, s32 flags) {
    arg0->unk_04 = flags | (arg0->unk_04 & ~mask);
}

s16 func_8010BE04_boardresult(BoardResultWork *arg0) {
    return arg0->unk_04;
}

void func_8010BE0C_boardresult(BoardResultWork *arg0, s16 arg1) {
    arg0->unk_06 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010BE14_boardresult);

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010CEF4_boardresult);

HmfModelData_UnkBC_Unk58_Struct *func_8010D28C_boardresult(s16 model, f32 x, f32 y, f32 z, f32 arg4, f32 arg5,
                                                           f32 arg6, u8 r, u8 g, u8 b) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Unk58_Struct *particle = HmfModelData[model].unkBC->unk58;
    s16 i;
    s16 count = hmf->unk1A;

    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 <= 0.0f) {
            particle->unk0C = x;
            particle->unk10 = y;
            particle->unk14 = z;
            particle->unk24 = arg4;
            particle->unk28 = arg5;
            particle->unk2C = arg6;
            particle->unk00[0] = r;
            particle->unk00[1] = g;
            particle->unk00[2] = b;
            particle->unk08 = 2.0f;
            break;
        }
    }
    return particle;
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010D36C_boardresult);

void func_8010D87C_boardresult(s16 model) {
    HmfData *hmf = HmfModelData[model].hmf;
    HmfModelData_UnkBC_Struct *effect = HmfModelData[model].unkBC;
    HmfModelData_UnkBC_Unk58_Struct *particle;
    s16 count = hmf->unk1A;
    s16 i;

    if (effect->unk02 == 0) {
        effect->unk04 &= ~4;
        particle = effect->unk58;
        for (i = 0; i < count; i++, particle++) {
            particle->unk08 = particle->unk0C = particle->unk10 = particle->unk14 = 0.0f;
        }
        effect->unk02++;
    }

    particle = effect->unk58;
    for (i = 0; i < count; i++, particle++) {
        if (particle->unk08 > 0.0f) {
            particle->unk0C += particle->unk24;
            particle->unk10 += particle->unk28;
            particle->unk14 += particle->unk2C;
            particle->unk10 -= 5.0f;
            particle->unk08 -= 0.05f;
        } else {
            particle->unk08 = 0.0f;
        }
    }
}

void func_8010D9D0_boardresult(void) {
    Process *proc = omAddPrcObj(func_8010DA30_boardresult, 0x3F00, 0x2000, 0);
    BoardResultWork *work = proc->user_data = HuMemAllocTag(sizeof(BoardResultWork), TAG_OVERLAY);

    work->pos.x = 0.0f;
    work->pos.y = 100.0f;
    work->pos.z = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/boardresult/3BFA00", func_8010DA30_boardresult);
