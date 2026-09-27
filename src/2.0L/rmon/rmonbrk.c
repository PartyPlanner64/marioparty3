#include "common.h"

typedef struct {
    /* 0x00 */ s32 size; // 0x4C, also written by __rmonSendReply
    /* 0x04 */ u8 unk_04;
    /* 0x06 */ u16 unk_06;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ s32 unk_14;
    /* 0x18 */ s32 unk_18;
    /* 0x1C */ s32 unk_1C;
    /* 0x20 */ s32 unk_20;
    /* 0x24 */ u16 unk_24;
    /* 0x26 */ u16 unk_26;
    /* 0x28 */ s32 unk_28;
    /* 0x2C */ s32 unk_2C;
    /* 0x30 */ s32 unk_30;
} OSExceptionStatus; // size = 0x34, sent to the host by __rmonSendReply

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonSetBreak);

s32 __rmonListBreak(void *arg) {
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonClearBreak);

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonGetBranchTarget);

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonSetSingleStep);

void __rmonGetExceptionStatus(OSExceptionStatus *es) {
    es->unk_0C = 1;
    es->unk_10 = 2;
    es->unk_24 = 2;
    es->unk_26 = 4;
    es->unk_04 = 4;
    es->unk_12 = 0;
    es->unk_30 = 0;
    es->unk_06 = 0;
    es->size = 0x4C;
}

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonHitBreak);

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonHitSpBreak);

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", __rmonHitCpuFault);

INCLUDE_ASM("asm/nonmatchings/2.0L/rmon/rmonbrk", rmonFindFaultedThreads);
