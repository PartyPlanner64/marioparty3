#include "common.h"
#include "mallocblock.h"

typedef struct UnkSlotSynch {
    char unk_00[0x16];
    u16 unk_16;
    char unk_18[0x8];
} UnkSlotSynch;

typedef struct UnkSlotMachine { // 0x3C bytes, four entries (one per player)
    s16 unk_00;
    s8 unk_02;
    u8 unk_03;
    s8 unk_04;
    s8 unk_05;
    s8 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s32 unk_10;
    f32 unk_14;
    f32 unk_18;
    f32 unk_1C;
    s32 unk_20;
    f32 unk_24;
    f32 unk_28;
    f32 unk_2C;
    f32 unk_30;
    f32 unk_34;
    f32 unk_38;
} UnkSlotMachine;

typedef struct UnkSlotReel { // 0x20 bytes, two entries
    char unk_00[0x4];
    s16 unk_04;
    char unk_06[0x2];
    s32 unk_08;
    char unk_0C[0x8];
    s32 unk_14;
    char unk_18[0x8];
} UnkSlotReel;

typedef union UnkSlotSynchBytes { // packs the top byte of each work word
    u32 word;
    struct {
        u32 byte3 : 8;
        u32 byte2 : 8;
        u32 byte1 : 8;
        u32 byte0 : 8;
    } bytes;
} UnkSlotSynchBytes;

typedef struct UnkSlotOvlData { // 0xC bytes
    omObjData *unk_00;
    s16 unk_04;
    s16 unk_06;
    void *unk_08;
} UnkSlotOvlData;

typedef struct UnkSlotSpin { // 0x58 bytes, five entries
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
    s16 unk_04[4];
    s16 unk_0C[12];
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s32 unk_2C;
    s32 unk_30;
    f32 unk_34[9];
} UnkSlotSpin;

extern UnkSlotSynch *D_8010DF5C_slot_synch;
extern UnkSlotOvlData D_8010DF70_slot_synch;
extern UnkSlotMachine *D_8010DF7C_slot_synch;
extern UnkSlotReel *D_8010DF80_slot_synch;
extern UnkSlotSpin *D_8010DF88_slot_synch;
extern u8 D_8010D854_slot_synch[2][4];

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801059A0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80105B98_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80105C08_slot_synch);

void func_80106080_slot_synch(void) {
    HuAudSeqStop();
    omOvlReturnEx(1);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801060A4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010614C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106560_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106878_slot_synch);

void func_80106CCC_slot_synch(s16 arg0, s32 arg1) {
    UnkSlotSynch *slot = &D_8010DF5C_slot_synch[arg0];
    slot->unk_16 += arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106CF0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106D0C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80106E8C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107108_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801075D4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107794_slot_synch);

void func_80107A80_slot_synch(void) {
}

void func_80107A88_slot_synch(void) {
    memset(&D_8010DF70_slot_synch, 0, sizeof(D_8010DF70_slot_synch));
    D_8010DF70_slot_synch.unk_06 = 0;
    D_8010DF70_slot_synch.unk_08 = HuMemAllocTag(0x420, 0x7918);
    memset(D_8010DF70_slot_synch.unk_08, 0, 0x420);
    D_8010DF70_slot_synch.unk_00 = omAddObj(0x1C, 0, 0, -1, NULL);
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107B00_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107BAC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80107D54_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010800C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108238_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108428_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108848_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801089F8_slot_synch);

s32 func_80108A7C_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    return machine->unk_0C == 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108AA8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108B74_slot_synch);

u8 func_80108C88_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    return D_8010D854_slot_synch[machine->unk_03][arg1];
}

void func_80108CD0_slot_synch(s16 arg0) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    if (machine->unk_0C != 4 && machine->unk_0C != 5) {
        machine->unk_0C = 4;
        machine->unk_0A = 0;
    }
}

void func_80108D14_slot_synch(s16 arg0, s16 arg1) {
    UnkSlotMachine *machine = &D_8010DF7C_slot_synch[arg0];

    machine->unk_08 = arg1;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80108D3C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801091D8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_801092B8_slot_synch);

void func_801094E0_slot_synch(s16 arg0, s32 arg1, s32 arg2) {
    UnkSlotReel *reel = &D_8010DF80_slot_synch[arg0];

    reel->unk_04 = 1;
    reel->unk_08 = arg1;
    reel->unk_14 = arg2;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109508_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC78_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DC7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109754_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_80109FA4_slot_synch);

s32 func_8010A178_slot_synch(s16 arg0) {
    UnkSlotSpin *spin;

    if (D_8010DF88_slot_synch == NULL) {
        return 1;
    }
    spin = &D_8010DF88_slot_synch[arg0];
    if (spin->unk_00 == 0) {
        goto ret_one;
    }
    if (spin->unk_02 == 0) {
        goto ret_zero;
    }
ret_one:
    return 1;
ret_zero:
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A1D0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A2C4_slot_synch);

void func_8010A308_slot_synch(s16 arg0, s16 arg1, f32 arg2, f32 arg3) {
    HuSprGrp *grp = HuSprGrpData[arg0];
    HuSprite *spr = HuSprGet(arg0, arg1);

    if (spr->pos.x != arg2 || spr->pos.y != arg3) {
        grp->dirty = 1;
        spr->pos.x = arg2;
        spr->pos.y = arg3;
    }
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A39C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A480_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010A7D0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AA9C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AAB8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AC14_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AD68_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010AF38_slot_synch);

INCLUDE_RODATA("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", D_8010DD28_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B064_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010B754_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BB90_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BD7C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010BF6C_slot_synch);

f32 func_8010C0C0_slot_synch(f32 arg0, f32 arg1) {
    if (arg0 >= 360.0f) {
        arg0 -= 360.0f;
    } else if (arg0 < 0.0f) {
        arg0 += 360.0f;
    }
    if (arg1 >= 360.0f) {
        arg1 -= 360.0f;
    } else if (arg1 < 0.0f) {
        arg1 += 360.0f;
    }
    arg0 = arg0 - arg1;
    if (arg0 <= -180.0f) {
        arg0 += 360.0f;
    } else if (arg0 >= 180.0f) {
        arg0 -= 360.0f;
    }
    return arg0;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C1C4_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C384_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C39C_slot_synch);

void func_8010C3FC_slot_synch(omObjData *arg0, u32 arg1) {
    arg0->work[0] = arg1 >> 24;
    arg0->work[1] = (arg1 >> 16) & 0xFF;
    arg0->work[2] = (arg1 >> 8) & 0xFF;
    arg0->work[3] = arg1 & 0xFF;
}

u32 func_8010C428_slot_synch(omObjData *arg0, s32 arg1, u32 arg2) {
    UnkSlotSynchBytes packed;

    packed.bytes.byte3 = (u8)arg0->work[0];
    packed.bytes.byte2 = (u8)arg0->work[1];
    packed.bytes.byte1 = (u8)arg0->work[2];
    packed.bytes.byte0 = (u8)arg0->work[3];
    return packed.word;
}

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C47C_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010C4C0_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D0A8_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D2AC_slot_synch);

INCLUDE_ASM("asm/nonmatchings/overlays/ovl_14_slot_synch/1AC970", func_8010D3E0_slot_synch);
