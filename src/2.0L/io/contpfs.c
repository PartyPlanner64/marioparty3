#include "common.h"

u16 __osSumcalc(u8 *data, s32 length) {
    s32 i;
    u32 sum = 0;

    for (i = 0; i < length; i++) {
        sum += *data++;
    }
    return sum;
}

u32 __osIdCheckSum(u8 *data, u16 *sum1, u16 *sum2) {
    u8 *end = data + 0x1C;
    u16 value;

    *sum2 = 0;
    *sum1 = 0;
    do {
        value = *(u16 *)data;
        *sum1 += value;
        *sum2 += ~value;
        data += 2;
    } while (data < end);

    return 0;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osRepairPackId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osCheckPackId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osGetId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osCheckId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osPfsRWInode);
