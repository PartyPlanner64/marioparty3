#include "common.h"

void *func_80077290_main(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size) {
    s32 bytes;
    void *ptr = NULL;

    bytes = (num * size + 0xF) & ~0xF;

    if (hp->cur + bytes <= hp->base + hp->len) {
        ptr = hp->cur;
        hp->cur += bytes;
    }

    return ptr;
}
