#include "common.h"

void alCopy(u8 *src, u8 *dest, s32 len) {
    s32 i;

    for (i = 0; i < len; i++) {
        *dest = *src;
        src++;
        dest++;
    }
}
