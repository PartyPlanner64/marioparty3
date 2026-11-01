#include "PR/ultratypes.h"
#include "PR/os_internal.h"
#include "PR/os_rcp.h"
#include "PR/R4300.h"

/*
 * libleo (64DD) LeoBootGame. Compiled with IDO.
 *
 * __LeoBootGame2 and __LeoBootGame3 are stored obfuscated in the ROM: in each
 * word, byte 2 has the key added and byte 3 has the key subtracted, where the
 * key is the sum of the bytes of __LeoBootGame2's address. LeoBootGame
 * restores both before calling into them. The build re-applies the
 * obfuscation to __LeoBootGame2 after linking (tools/leo_encrypt.py).
 * __LeoBootGame3 is hand-written assembly and kept as its original bytes.
 */

extern u32 _osPreNMI;

u8 D_800C1560_main[0xC10]; /* unreferenced */
u32 D_800C2170_main;

void __LeoBootGame2(void *entry);
extern void __LeoBootGame3(void *entry);

void LeoBootGame(void *entry) {
    u8 *p;
    u32 i;
    u8 key;

    key = ((((u32)__LeoBootGame2 & 0xFF000000) >> 24) + (((u32)__LeoBootGame2 & 0xFF0000) >> 16) +
           (((u32)__LeoBootGame2 & 0xFF00) >> 8) + ((u32)__LeoBootGame2 & 0xFF)) & 0xFF;

    p = (u8 *)__LeoBootGame2;
    for (i = 0; i < 0x344; i += 4) {
        p[2] -= key;
        p[3] += key;
        p += 4;
    }
    osWritebackDCacheAll();
    osInvalICache(__LeoBootGame2, 0x344);

    p = (u8 *)__LeoBootGame3;
    for (i = 0; i < 0x50; i += 4) {
        p[2] -= key;
        p[3] += key;
        p += 4;
    }
    osWritebackDCacheAll();
    osInvalICache((void *)__LeoBootGame3, 0x50);

    __LeoBootGame2(entry);
}

void __LeoBootGame2(void *entry) {
    u8 *src;
    u32 j;
    s32 i;
    u8 buf[0x100];
    vu32 *p;

    src = entry;
    i = 0;

    /* Erase the decoding routine. */
    bzero(LeoBootGame, 0x13C);
    osWritebackDCache(LeoBootGame, 0x13C);

    __osSetSR(SR_CU0 | SR_CU1);
    if (_osPreNMI) {
        for (;;) {
        }
    }

    *(u8 *)PHYS_TO_K1(0x10) = (D_800C2170_main & 0xFF000000) >> 24;
    while (!IO_READ(SP_STATUS_REG) & SP_STATUS_HALT) {
    }
    IO_WRITE(SP_STATUS_REG, SP_SET_HALT | SP_CLR_INTR);

    /* The entry code is unscrambled in stages while waiting on the hardware. */
    while (i < 0x50) {
        buf[(i * 17) % 256] = src[i];
        i++;
    }
    while (IO_READ(SP_DMA_BUSY_REG) & 1) {
    }
    IO_WRITE(PI_STATUS_REG, PI_STATUS_RESET | PI_STATUS_CLR_INTR);

    while (i < 0xAA) {
        buf[(i * 17) % 256] = src[i];
        i++;
    }
    while (IO_READ(VI_CURRENT_REG) > 10) {
    }
    IO_WRITE(VI_INTR_REG, 0x3FF);
    IO_WRITE(VI_H_START_REG, 0);
    IO_WRITE(VI_CURRENT_REG, 0);
    *(u8 *)PHYS_TO_K1(0x190) = D_800C2170_main & 0xFF;
    IO_WRITE(AI_DRAM_ADDR_REG, 0);
    IO_WRITE(AI_LEN_REG, 0);

    while (i < 0x100) {
        buf[(i * 17) % 256] = src[i];
        i++;
    }
    bcopy(buf, src, 0x100);

    *(u8 *)PHYS_TO_K1(0x110) = (D_800C2170_main & 0xFF00) >> 8;
    __osSetCause(0);
    __osSetCount(0);
    __osSetCompare(0);
    IO_WRITE(SP_STATUS_REG, 0xAAAAAE);
    *(u8 *)PHYS_TO_K1(0x90) = (D_800C2170_main & 0xFF0000) >> 16;
    IO_WRITE(MI_INTR_MASK_REG, 0);
    IO_WRITE(SI_STATUS_REG, 0);
    IO_WRITE(AI_STATUS_REG, 0);
    IO_WRITE(MI_MODE_REG, MI_CLR_DP_INTR);
    IO_WRITE(PI_STATUS_REG, PI_STATUS_CLR_INTR);
    osResetType = 2;

    p = (vu32 *)PHYS_TO_K1(SP_IMEM_START);
    for (j = 0; j < 0x100; j++) {
        *p++ = 0;
    }
    p = (vu32 *)PHYS_TO_K1(SP_DMEM_START);
    for (j = 0; j < 0x100; j++) {
        *p++ = 0;
    }

    /* Erase this function, except for the tail that is still executing. */
    bzero(__LeoBootGame2, 0x304);
    osWritebackDCache(__LeoBootGame2, 0x304);
    __LeoBootGame3(entry);
}
