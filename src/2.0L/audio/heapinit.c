#include "common.h"

void alHeapInit(ALHeap *hp, u8 *base, s32 len) {
    s32 pad = 0x10 - ((u32)base & 0xF);

    if (pad != 0x10) {
        hp->base = base + pad;
    } else {
        hp->base = base;
    }

    hp->len = len;
    hp->count = 0;
    hp->cur = hp->base;
}
