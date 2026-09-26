#include "common.h"
#include "overlays/minigame.h"
#include "mallocblock.h"

typedef struct UnkLogJamSprites { // 0xC bytes, two entries
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} UnkLogJamSprites;

typedef struct LogJamPlayerWork { // 0x78 bytes, 0x20 entries allocated by func_80108D50_log_jam
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    f32 unk_10; // position
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C; // rotation
    f32 unk_20;
    f32 unk_24;
    f32 unk_28; // velocity
    f32 unk_2C;
    f32 unk_30;
    s16 unk_34[0x0F];
    s16 unk_52;
    s8 unk_54[0x20];
    void *unk_74; // callback
} LogJamPlayerWork;

typedef struct LogJamLogWork { // 0x38 bytes, 4 entries allocated by func_80106190_log_jam
    s16 unk_00;
    s16 unk_02;
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A[0x17];
} LogJamLogWork;

typedef union LogJamWorkBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} LogJamWorkBytes;

extern s32 D_8010E030_log_jam[9];
extern UnkLogJamSprites *D_8010E5D0_log_jam;
extern LogJamPlayerWork *D_8010E5C4_log_jam;
extern LogJamLogWork *D_8010E5B8_log_jam;
extern s16 *D_8010E5C8_log_jam;

void func_80109B8C_log_jam(omObjData *object);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801059A0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80105B9C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80105C10_log_jam);

void func_801060C4_log_jam(void) {
    func_8004A950_main();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801060E8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106190_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E1F0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801065E8_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E218_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106968_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106F48_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80106FAC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107080_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80107C84_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108840_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108A80_log_jam);

s32 func_80108CE0_log_jam(s16 arg0) {
    s32 i = 0;
    LogJamLogWork *work = D_8010E5B8_log_jam;

    do {
        if (work->unk_08 != arg0) {
            return 0;
        }
        work++;
    } while (++i < 4);

    return 1;
}

s16 func_80108D1C_log_jam(f32 arg0, f32 arg1) {
    f32 total = 0.0f;
    s16 frames = 0;
    f32 speed = arg0;

    do {
        total += speed;
        speed -= arg1;
        frames++;
    } while (0.0f < total);

    return frames;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108D50_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80108E54_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109044_log_jam);

LogJamPlayerWork *func_8010910C_log_jam(s16 arg0) {
    if (D_8010E5C4_log_jam == NULL) {
        return NULL;
    }

    return &D_8010E5C4_log_jam[arg0];
}

void func_80109140_log_jam(s16 arg0, f32 arg1, f32 arg2, f32 arg3) {
    if (D_8010E5C4_log_jam != NULL) {
        LogJamPlayerWork *work = &D_8010E5C4_log_jam[arg0];

        if (work->unk_08 != 0) {
            work->unk_10 = arg1;
            work->unk_14 = arg2;
            work->unk_18 = arg3;
        }
    }
}

void func_80109190_log_jam(s16 arg0, f32 arg1, f32 arg2) {
    if (D_8010E5C4_log_jam != NULL) {
        LogJamPlayerWork *work = &D_8010E5C4_log_jam[arg0];

        if (work->unk_08 != 0) {
            work->unk_1C = arg1;
            work->unk_20 = arg2;
            work->unk_24 = arg1;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801091DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010925C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109350_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2C0_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E2CC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_801094E4_log_jam);

void func_80109A00_log_jam(void) {
    s32 i;

    D_8010E5C8_log_jam = HuMemAllocTag(0x12, 0x7918);

    for (i = 0; i < 9; i++) {
        D_8010E5C8_log_jam[i] = func_8000B108_main(D_8010E030_log_jam[i], 0xBD);
    }
}

s16 func_80109A7C_log_jam(s16 arg0, s16 arg1) {
    if (D_8010E5C8_log_jam == NULL) {
        return -1;
    }

    return Hu3DModelLink(D_8010E5C8_log_jam[arg0 * 3 + arg1]);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109AD8_log_jam);

// Appends a new object to the shared minigame object list.
void func_80109B34_log_jam(void) {
    omObjData *obj = omAddObj(1, 0x10, 0, -1, func_80109B8C_log_jam);
    u16 index = D_800EBE28_minigame;

    D_800EBE28_minigame = index + 1;
    D_800EC1C0_minigame[index] = obj;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_80109B8C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A0B0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A300_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A344_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A4C0_log_jam);

void func_8010A6FC_log_jam(s16 arg0, s16 arg1) {
    UnkLogJamSprites *sprites = &D_8010E5D0_log_jam[arg0];

    sprites->unk_08 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A724_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A880_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010A9D4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010ABA4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010AD04_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010AE58_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B04C_log_jam);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", D_8010E370_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B17C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010B86C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010BCA8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010BE94_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C084_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C1D8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C2DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C49C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C4B4_log_jam);

f32 func_8010C514_log_jam(f32 arg0, f32 arg1, f32 arg2) {
    if (__builtin_fabs((f64)(arg0 - arg1)) < arg2) {
        return arg0;
    }

    if (arg0 < arg1) {
        arg2 = -arg2;
    }

    return arg1 + arg2;
}

void func_8010C55C_log_jam(omObjData *object, u32 arg1) {
    object->work[0] = arg1 >> 24;
    object->work[1] = (arg1 >> 16) & 0xFF;
    object->work[2] = (arg1 >> 8) & 0xFF;
    object->work[3] = arg1 & 0xFF;
}

u32 func_8010C588_log_jam(omObjData *object, s32 arg1, u32 arg2) {
    LogJamWorkBytes packed;

    packed.bytes.byte3 = (u8)object->work[0];
    packed.bytes.byte2 = (u8)object->work[1];
    packed.bytes.byte1 = (u8)object->work[2];
    packed.bytes.byte0 = (u8)object->work[3];
    return packed.word;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C5DC_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C6A4_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C714_log_jam);

void func_8010C7D0_log_jam(omObjData *object) {
    HmfModel *model = &HmfModelData[object->model[0]];

    model->unk44 = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C7F8_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C8B0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010C8E0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010CAC0_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010CB64_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010D74C_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010D950_log_jam);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_13_log_jam/1A3D80", func_8010DA84_log_jam);
