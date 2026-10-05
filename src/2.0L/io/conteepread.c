#include "common.h"
#include "gcc/memory.h"

INCLUDE_ASM("asm/nonmatchings/2.0L/io/conteepread", osEepromRead);

extern u8 D_800D0470_main[];
extern s32 D_800D04AC_main;

void func_8007FA88_main(u8 address) {
    u8 buf[12];
    u8 *ptr = D_800D0470_main;
    s32 i = 3;

    D_800D04AC_main = 1;
    buf[0] = 2;
    buf[1] = EEPROM_BLOCK_SIZE;
    buf[2] = 4;
    buf[3] = address;
    for (; i >= 0; i--) {
        *ptr++ = 0;
    }
    memcpy(ptr, buf, sizeof(buf));
    ptr[sizeof(buf)] = 0xFE;
}
