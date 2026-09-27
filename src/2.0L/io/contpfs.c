#include "common.h"

u16 __osSumcalc(u8 *data, s32 length) {
    s32 i;
    u32 sum = 0;

    for (i = 0; i < length; i++) {
        sum += *data++;
    }
    return sum;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osIdCheckSum);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osRepairPackId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osCheckPackId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osGetId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osCheckId);

INCLUDE_ASM("asm/nonmatchings/2.0L/io/contpfs", __osPfsRWInode);
